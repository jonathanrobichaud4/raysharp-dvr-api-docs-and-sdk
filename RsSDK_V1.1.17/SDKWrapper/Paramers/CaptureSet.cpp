#include "StdAfx.h"
#include "CaptureSet.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	CaptureSet* pThis = (CaptureSet*)userParam;
	RSNet_SoleCaptureSet_t* channelCap = (RSNet_SoleCaptureSet_t*)data;
	pThis->m_vec.push_back(*channelCap);
}

std::string CaptureSet::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamCaptureSet;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleCaptureSet_t);
	param.ListParamCallback = AllDataCallback;
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

void CaptureSet::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["ChnEnable"] = m_vec[n].ChnEnable;
	m_obj["ManualEnable"] = m_vec[n].ManualEnable;
	m_obj["StreamType"] = m_vec[n].StreamType;
	m_obj["NormalCapInterv"] = m_vec[n].NormalCapInterv;
	m_obj["AlarmCapInterv"] = m_vec[n].AlarmCapInterv;
	m_obj["AlarmCapEncIndex"] = m_vec[n].AlarmCapEncType;
	m_obj["AlarmCapQuality"] = m_vec[n].AlarmCapQuality;

	for (int i=0; i<3;i++)
	{
		m_obj["MainResolutionWidth"].append(m_vec[n].BigRange[i].ResolutionWidth);
	}

	for (int i=0; i<3;i++)
	{
		m_obj["MainResolutionHeight"].append(m_vec[n].BigRange[i].ResolutionHight);
	}
	for (int i=0; i<3;i++)
	{
		m_obj["SubResolutionWidth"].append(m_vec[n].LittleRange[i].ResolutionWidth);
	}

	for (int i=0; i<3;i++)
	{
		m_obj["SubResolutionHeight"].append(m_vec[n].LittleRange[i].ResolutionHight);
	}
}


int CaptureSet::SaveAll(std::string strData)
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
		m_vec[i].ChnEnable = obj[i]["ChnEnable"].asInt();
		m_vec[i].ManualEnable = obj[i]["ManualEnable"].asInt();
		m_vec[i].StreamType = obj[i]["StreamType"].asInt();
		m_vec[i].NormalCapInterv = obj[i]["NormalCapInterv"].asInt();
		m_vec[i].AlarmCapInterv = obj[i]["AlarmCapInterv"].asInt();
		if(!obj[i]["AlarmCapEncIndex"].isNull()){
			m_vec[i].AlarmCapEncType = obj[i]["AlarmCapEncIndex"].asInt();
		}
		if(!obj[i]["AlarmCapQuality"].isNull()){
			m_vec[i].AlarmCapQuality = obj[i]["AlarmCapQuality"].asInt();
		}

		m_vec[i].StructSize = sizeof(RSNet_SoleCaptureSet_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamCaptureSet;
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