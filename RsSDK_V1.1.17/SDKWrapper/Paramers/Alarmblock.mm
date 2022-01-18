#pragma once
#include "StdAfx.h"
#include "Alarmblock.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	AlarmBlock * pThis = (AlarmBlock*)userParam;
	memcpy(&pThis->m_Struct, data, sizeof(RSNet_OcclusionSet_t));
}

std::string AlarmBlock::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_OcclusionSet_t));
	m_Struct.StructSize = sizeof(RSNet_OcclusionSet_t);

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamIDSet;
	param.Req = &m_Struct;

	param.ParamSize = sizeof(RSNet_OcclusionSet_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(),&param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["EnableBlock"] = m_Struct.ChnSwitch;
	m_obj["EnableEmail"] = m_Struct.SendEmail;
	m_obj["EnableIOout"] = m_Struct.AlarmOut;
	m_obj["EnableRecord"] = m_Struct.Record;
	m_obj["RecordDelayTime"] = m_Struct.RecordDelayTime;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int AlarmBlock::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	//处理数据
		m_Struct.ChnSwitch = obj["EnableBlock"].asInt();
		m_Struct.SendEmail = obj["EnableEmail"].asInt();
		m_Struct.AlarmOut = obj["EnableIOout"].asInt();
		m_Struct.Record = obj["EnableRecord"].asInt();
		m_Struct.RecordDelayTime = atoi(obj["RecordDelayTime"].asCString());

	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType =MsgParamIDSet;
		param.Param = &m_Struct;
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