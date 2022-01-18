#include "StdAfx.h"
#include "AlarmPtz.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	AlarmPtz* pThis = (AlarmPtz*)userParam;
	RSNet_AlarmLinkagePtz_t* pData = (RSNet_AlarmLinkagePtz_t*)data;
	pThis->m_ptz = *pData;
}

static void RSNET_CALL SoleParamCallback(void* data, void* userParam)
{
	AlarmPtz* pThis = (AlarmPtz*)userParam;
	RSNet_SoleAlarmLinkagePtz_t* pData = (RSNet_SoleAlarmLinkagePtz_t*)data;
	pThis->m_vec.push_back(*pData);
}

std::string AlarmPtz::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_ptz,'\0', sizeof(RSNet_AlarmLinkagePtz_t));
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamAlarmLinkagePTZ;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_AlarmLinkagePtz_t);
	param.ParamCallback = ParamDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleAlarmLinkagePtz_t);
	param.ListParamCallback = SoleParamCallback;

	param.UserParam = this;

	if(isDefault)
	{
		if (!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//通道有关数据-(所有通道数据(数组))
	Json::Value AllChData(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		StructToJson(i);
		AllChData.append(m_obj);
	}

	//通道无关数据-(一个结构体数据(单个))
	Json::Value NoChData(Json::arrayValue);
	for(int i=0; i<256; i++)
	{
		Json::Value arrTmp(Json::arrayValue);
		for(int j=0; j<256; j++)
		{
			arrTmp.append(m_ptz.ChnCruiseTime[i][j]);
		}

		NoChData.append(arrTmp);
	}	

	Json::Value root;
	root["AllChData"] = AllChData;
	root["NoChData"] = NoChData;

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void AlarmPtz::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["ChnSwitch"] = m_vec[n].ChnSwitch;
	m_obj["MotionLinkage"] = m_vec[n].MotionLinkage;
	m_obj["IOLinkage"] = m_vec[n].IOLinkage;
	m_obj["PIRLinkage"] = m_vec[n].PIRLinkage;
	m_obj["IntelliLinkage"] = m_vec[n].IntelliLinkage;

		Json::Value arrValue1(Json::arrayValue);
		for(int i=0; i<32; i++)
		{
			arrValue1.append(m_vec[n].AlarmLinkagePtzChn[i]);
		}
	m_obj["AlarmLinkagePtzChn"] = arrValue1;

		Json::Value arrValue2(Json::arrayValue);
		for(int i=0; i<32; i++)
		{
			arrValue2.append(m_vec[n].LinkagePtzPointIndex[i]);
		}
	m_obj["LinkagePtzPointIndex"] = arrValue2;

		Json::Value arrValue3(Json::arrayValue);
		for(int i=0; i<32; i++)
		{
			arrValue3.append(m_vec[n].AlarmLinkPtzEnable[i]);
		}
	m_obj["AlarmLinkPtzEnable"] = arrValue3;
}

int AlarmPtz::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	//通道有关数据
	for(int i=0; i<obj.size(); i++)
	{
		m_vec[i].ChnSwitch = obj[i]["ChnSwitch"].asUInt();
		m_vec[i].MotionLinkage = obj[i]["MotionLinkage"].asUInt();
		m_vec[i].IOLinkage = obj[i]["IOLinkage"].asUInt();
		m_vec[i].PIRLinkage = obj[i]["PIRLinkage"].asUInt();
		m_vec[i].IntelliLinkage = obj[i]["IntelliLinkage"].asUInt();

		for(int j=0; j<32; j++)
		{
			m_vec[i].AlarmLinkagePtzChn[j] = obj[i]["AlarmLinkagePtzChn"][j].asUInt();
		}
		for(int j=0; j<32; j++)
		{
			m_vec[i].LinkagePtzPointIndex[j] = obj[i]["LinkagePtzPointIndex"][j].asUInt();
		}
		for(int j=0; j<32; j++)
		{
			m_vec[i].AlarmLinkPtzEnable[j] = obj[i]["AlarmLinkPtzEnable"][j].asUInt();
		}

		m_vec[i].StructSize = sizeof(RSNet_SoleAlarmLinkagePtz_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamAlarmLinkagePTZ;
	param.Param = NULL;
	param.ListParams = &m_vec[0];
	param.ListParamNum = m_vec.size();
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