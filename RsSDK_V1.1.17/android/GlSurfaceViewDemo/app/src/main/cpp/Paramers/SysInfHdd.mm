#include "StdAfx.h"
#include "SysInfHdd.h"

static void RSNET_CALL ParamCallback(void* data, void* userParam)
{
	SysInfHdd* pThis = (SysInfHdd*)userParam;
	RSNet_HddInfo_t* HddInfo = (RSNet_HddInfo_t*)data;
	pThis->m_HddInfo = *HddInfo;
}

static void RSNET_CALL SoleParamCallback(void* data, void* userParam)
{
	SysInfHdd* pThis = (SysInfHdd*)userParam;
	RSNet_SoleHddInfo_t* SoleHddInfo = (RSNet_SoleHddInfo_t*)data;
	pThis->m_vec.push_back(*SoleHddInfo);
}

std::string SysInfHdd::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	memset(&m_HddInfo, '\0', sizeof(RSNet_HddInfo_t));
	m_HddInfo.StructSize = sizeof(RSNet_HddInfo_t);

	param.ParamType = MsgParamHdd;

	param.ParamSize = sizeof(RSNet_HddInfo_t);
	param.ParamCallback = ParamCallback;

	param.ListParamSize = sizeof(RSNet_SoleHddInfo_t);
	param.ListParamCallback = SoleParamCallback;

	param.UserParam = this;
	
	
	if(isDefault)
	{
		if(!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	Json::Value root(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void SysInfHdd::StructToJson(int n)
{
	m_obj.clear();

	m_obj["OverWrite"] = m_HddInfo.OverWrite;
	m_obj["RecordState"] = m_HddInfo.RecordState;
	m_obj["ESataRecEnable"] = m_HddInfo.ESataRecEnable;

	Json::Value listItem(Json::arrayValue);
	for(int i=0;i<24;++i){
		listItem.append((char*)m_HddInfo.OverWriteList[i]);
	}
	m_obj["OverWriteList"] = listItem;

	//以M为单位，让网页做处理
	unsigned int uintTmp;

	uintTmp = m_vec[n].HddTotalSize/(1024);
	m_obj["HddTotalSize"] = uintTmp;

	uintTmp = m_vec[n].HddFreeSize/(1024);
	m_obj["HddFreeSize"] = uintTmp;
	
	uintTmp = m_vec[n].HddFreeRecord;
	m_obj["HddFreeRecord"] = uintTmp;

	uintTmp = m_vec[n].HddFreeRecord_Min;
	m_obj["HddFreeRecord_Min"] = uintTmp;

	uintTmp = m_vec[n].HddState;
	m_obj["HddState"] = uintTmp;

	m_obj["HddType"] = m_vec[n].HddType;
	m_obj["HddNo"] = m_vec[n].HddNo;
}

int SysInfHdd::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	int i = 0;
	m_HddInfo.OverWrite = obj[i]["OverWrite"].asInt();
	m_HddInfo.ESataRecEnable = obj[i]["ESataRecEnable"].asInt();
	m_HddInfo.StructSize = sizeof(RSNet_HddInfo_t);

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamHdd;
	param.Param = &m_HddInfo;
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;//no right
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}