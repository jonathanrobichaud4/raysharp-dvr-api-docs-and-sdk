#include "StdAfx.h"
#include "GB28181.h"

std::string GB28181::QueryAll(bool bDefault)
{
	//ÇëÇóÊý¾Ý
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Gb28181, '\0', sizeof(RSNet_GB28181Param_t));
	m_Gb28181.StructSize = sizeof(RSNet_GB28181Param_t);
	param.Param = &m_Gb28181;

	param.ParamSize = sizeof(RSNet_GB28181Param_t);
	param.ParamType = MsgParamGB28181;

	if(bDefault)
	{
		if(!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	StructToJson();
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void GB28181::StructToJson()
{
	m_obj.clear();
	
	m_obj["server_port"] = m_Gb28181.server_port;
	m_obj["local_port"] = m_Gb28181.local_port;
	m_obj["server_ip"] = (char*)m_Gb28181.server_ip;
	m_obj["server_id"] = (char*)m_Gb28181.server_id;
	m_obj["device_id"] = (char*)m_Gb28181.device_id;
	for(int i = 0;i < 64;++i)
	{
		m_obj["channel_nvr_id"][i] = (char*)m_Gb28181.channel_nvr_id[i];
	}
	m_obj["pwd"] = (char*)m_Gb28181.pwd;
	m_obj["alarm_id"] = (char*)m_Gb28181.alarm_id;
	m_obj["enableflag"] = m_Gb28181.enableflag;
	m_obj["transprotocol"] = m_Gb28181.transprotocol;
}


int GB28181::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	m_Gb28181.server_port = obj["server_port"].asInt();
	m_Gb28181.local_port = obj["local_port"].asInt();
	int maxLen = sizeof(m_Gb28181.server_ip);
	memset(m_Gb28181.server_ip, '\0', maxLen);
	m_str = obj["server_ip"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Gb28181.server_ip, m_str.c_str(), len);

	maxLen = sizeof(m_Gb28181.server_id);
	memset(m_Gb28181.server_id, '\0', maxLen);
	m_str = obj["server_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Gb28181.server_id, m_str.c_str(), len);

	maxLen = sizeof(m_Gb28181.device_id);
	memset(m_Gb28181.device_id, '\0', maxLen);
	m_str = obj["device_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Gb28181.device_id, m_str.c_str(), len);
	
	for(int i = 0;i < 64;++i)
	{
		maxLen = sizeof(m_Gb28181.channel_nvr_id[i]);
		memset(m_Gb28181.channel_nvr_id[i], '\0', maxLen);
		m_str = obj["channel_nvr_id"][i].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Gb28181.channel_nvr_id[i], m_str.c_str(), len);
	}

	maxLen = sizeof(m_Gb28181.pwd);
	memset(m_Gb28181.pwd, '\0', maxLen);
	m_str = obj["pwd"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Gb28181.pwd, m_str.c_str(), len);
	
	maxLen = sizeof(m_Gb28181.alarm_id);
	memset(m_Gb28181.alarm_id, '\0', maxLen);
	m_str = obj["alarm_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Gb28181.alarm_id, m_str.c_str(), len);

	m_Gb28181.enableflag = obj["enableflag"].asInt();
	m_Gb28181.transprotocol = obj["transprotocol"].asInt();
	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamGB28181;
	param.Param = &m_Gb28181;
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