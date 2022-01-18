#include "StdAfx.h"
#include "RecConfig.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	RecConfig* pThis = (RecConfig*)userParam;
	RSNet_RecordSet_t* RecordSet = (RSNet_RecordSet_t*)data;
	pThis->m_RecordSet = *RecordSet;
}

static void RSNET_CALL SoleParamDataCallback(void* data, void* userParam)
{
	RecConfig* pThis = (RecConfig*)userParam;
	RSNet_SoleRecordSet_t* SoleRecordSet = (RSNet_SoleRecordSet_t*)data;
	pThis->m_vec.push_back(*SoleRecordSet);
}

std::string RecConfig::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_RecordSet,'\0', sizeof(RSNet_RecordSet_t));
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamRecord;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_RecordSet_t);
	param.ParamCallback = ParamDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleRecordSet_t);
	param.ListParamCallback = SoleParamDataCallback;

	param.UserParam = this;

	if(bDefault)
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

void RecConfig::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["RecordMode"] = m_RecordSet.RecordMode;
	m_obj["PackTime"] = m_RecordSet.PackTime;
	m_obj["PreRecordTime"] = m_RecordSet.PreRecordTime;
	m_obj["RedundanceRec"] = m_RecordSet.RedundanceRec;

	m_obj["ChnCloseOrOpen"] = m_vec[n].ChnCloseOrOpen;
	m_obj["RecordStreamMode"] = m_vec[n].RecordStreamMode;
	m_obj["PreRecSwitch"] = m_vec[n].PreRecSwitch;
	m_obj["RecordAudioEnable"] = m_vec[n].RecordAudioEnable;
    m_obj["Num"] = m_vec[n].Num;
    m_obj["ResolutionIndex"] = m_vec[n].ResolutionIndex;
	m_obj["OffLineRecSwitch"] = m_vec[n].OffLineRecSwitch;

	m_obj["EncTypeList"] = m_vec[n].EncTypeList;
	m_obj["EncTypeVal"] = m_vec[n].EncTypeVal;
	m_obj["pageBit"] = m_vec[n].pageBit;

    Json::Value obj(Json::objectValue);

    for (int i=0; i<8;i++)
    {
        obj["item"] = m_vec[n].Range[i].BitrateRange;
        m_obj["BitrateRange"].append(obj);
    }

    for (int i=0; i<8;i++)
    {
        obj["item"] = m_vec[n].Range[i].FrameRateMin;
        m_obj["FrameRateMin"].append(obj);

    }

    for (int i=0; i<8;i++)
    {
        obj["item"] = m_vec[n].Range[i].FrameRateMax;
        m_obj["FrameRateMax"].append(obj);
    }

    for (int i=0; i<8;i++)
    {
        obj["item"] = m_vec[n].Range[i].ResolutionWidth;
        m_obj["ResolutionWidth"].append(obj);
    }

    for (int i=0; i<8;i++)
    {
        obj["item"] = m_vec[n].Range[i].ResolutionHight;
        m_obj["ResolutionHight"].append(obj);
    }
}

int RecConfig::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	for(int i=0; i<obj.size(); i++)
	{
		m_vec[i].ChnCloseOrOpen = obj[i]["ChnCloseOrOpen"].asInt();
		m_vec[i].RecordStreamMode = obj[i]["RecordStreamMode"].asInt();
		m_vec[i].PreRecSwitch = obj[i]["PreRecSwitch"].asInt();
		m_vec[i].RecordAudioEnable = obj[i]["RecordAudioEnable"].asInt();
        m_vec[i].ResolutionIndex = obj[i]["ResolutionIndex"].asInt();
		m_vec[i].OffLineRecSwitch = obj[i]["OffLineRecSwitch"].asInt();

		//tt
		if(!obj[i]["EncTypeVal"].isNull()){
			m_vec[i].EncTypeVal = obj[i]["EncTypeVal"].asInt();
		}
		//tt

		m_vec[i].StructSize = sizeof(RSNet_SoleRecordSet_t);
	}

	int i = 0;
	int curCh = obj[i]["curCh"].asUInt();
	//通道无关数据，只看当前通道
	m_RecordSet.PackTime = obj[curCh]["PackTime"].asInt();
	m_RecordSet.PreRecordTime = obj[curCh]["PreRecordTime"].asInt();
	m_RecordSet.RecordMode = obj[curCh]["RecordMode"].asInt();
	m_RecordSet.RedundanceRec = obj[curCh]["RedundanceRec"].asInt();
	m_RecordSet.StructSize = sizeof(RSNet_RecordSet_t);

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamRecord;
	param.Param = &m_RecordSet;
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