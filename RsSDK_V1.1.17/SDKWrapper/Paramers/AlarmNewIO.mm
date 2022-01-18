#include "StdAfx.h"
#include "AlarmNewIO.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	AlarmNewIO* pThis = (AlarmNewIO*)userParam;
	RSNet_NewSoleIOAlarmSet_t* SoleIOAlarmSet = (RSNet_NewSoleIOAlarmSet_t*)data;
	pThis->m_vec.push_back(*SoleIOAlarmSet);
}

std::string AlarmNewIO::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgNewIOAlarm;//808
	
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_NewSoleIOAlarmSet_t);
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
	for(int i=0; i<m_vec.size()*3; i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
 	return strRet;
}

void AlarmNewIO::StructToJson(int n)
{
	m_obj.clear();
	//m_obj["ch"] = n;
	int i = n/m_vec.size();
	n = n%m_vec.size();

	for (int j=0;j<3;++j)
	{
		for(int k=0;k<32;++k)
		{
			m_obj["AlarmOutManager"][j][k] = m_vec[n].io[i].AlarmOutManager[j][k];
		}
	}
	for(int j = 0; j < 32;++j)
	{
		m_obj["RecordChannel"][j] = m_vec[n].io[i].RecordChannel[j];
		m_obj["AlarmLinkPtzEnable"][j] = m_vec[n].AlarmLinkPtzEnable[i][j];
	}
	for(int j = 0; j < 256;++j)
	{
		m_obj["LinkagePtzPresetIndex"][j] = m_vec[n].LinkagePtzPresetIndex[i][j];
		m_obj["LinkagePtzPatrolIndex"][j] = m_vec[n].LinkagePtzPatrolIndex[i][j];
		m_obj["LinkagePtzPatternIndex"][j] = m_vec[n].LinkagePtzPatternIndex[i][j];
		m_obj["LinkagePtzMode"][j] = m_vec[n].LinkagePtzMode[i][j];
	}
	m_obj["IoAlarmSet"] = m_vec[n].io[i].IoAlarmSet;
	m_obj["AlarmOutTime"] = m_vec[n].io[i].AlarmOutTime;
	m_obj["BuzzerMooTime"] = m_vec[n].io[i].BuzzerMooTime;
	m_obj["RecordDelayTime"] = m_vec[n].io[i].RecordDelayTime;
	m_obj["Record"] = m_vec[n].io[i].Record;
	m_obj["LinkFlag"] = m_vec[n].io[i].LinkFlag;
	m_obj["AlarmOut"] = m_vec[n].io[i].AlarmOut;
}

int AlarmNewIO::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	int n,ch;
	for(int i = 0;i < obj.size();++i)
	{
		n = i / m_vec.size();
		ch = i % m_vec.size();
		m_vec[ch].io[n].IoAlarmSet = obj[i]["IoAlarmSet"].asUInt();
		m_vec[ch].io[n].AlarmOutTime = obj[i]["AlarmOutTime"].asUInt();
		m_vec[ch].io[n].BuzzerMooTime = obj[i]["BuzzerMooTime"].asUInt();
		m_vec[ch].io[n].RecordDelayTime = obj[i]["RecordDelayTime"].asUInt();
		m_vec[ch].io[n].Record = obj[i]["Record"].asUInt();
		m_vec[ch].io[n].LinkFlag = obj[i]["LinkFlag"].asUInt();
		m_vec[ch].io[n].AlarmOut = obj[i]["AlarmOut"].asUInt();
		for (int j=0;j<3;++j)
		{
			for(int k=0;k<32;++k)
			{
				m_vec[ch].io[n].AlarmOutManager[j][k] = obj[i]["AlarmOutManager"][j][k].asUInt();
			}
		}
		for(int j = 0; j < 32;++j)
		{
			m_vec[ch].io[n].RecordChannel[j] = obj[i]["RecordChannel"][j].asUInt();
			m_vec[ch].AlarmLinkPtzEnable[n][j] = obj[i]["AlarmLinkPtzEnable"][j].asUInt();
		}
		for(int j = 0; j < 256;++j)
		{
			m_vec[ch].LinkagePtzPresetIndex[n][j] = obj[i]["LinkagePtzPresetIndex"][j].asUInt();
			m_vec[ch].LinkagePtzPatrolIndex[n][j] = obj[i]["LinkagePtzPatrolIndex"][j].asUInt();
			m_vec[ch].LinkagePtzPatternIndex[n][j] = obj[i]["LinkagePtzPatternIndex"][j].asUInt();
			m_vec[ch].LinkagePtzMode[n][j] = obj[i]["LinkagePtzMode"][j].asUInt();
		}
		m_vec[ch].StructSize = sizeof(RSNet_NewSoleIOAlarmSet_t);
	}

	//保存
	RSNetSetParamParam param;
	ZeroMemory(&param, sizeof(param));

	param.ParamType = MsgNewIOAlarm;//808

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