#pragma once
#include "StdAfx.h"
#include "EPlatform.h"

static void RSNET_CALL ParamDataCallback(void* param, void* userParam)
{
	EPlatform* pThis = (EPlatform*)userParam;
	memcpy(&pThis->m_eplatform,param,sizeof(Eplateform_t));
}

int EPlatform::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	int maxLen = sizeof(m_eplatform.device_name);
	std::string m_str;
	memset(m_eplatform.device_name, '\0', maxLen);
	m_str = obj["device_name"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_eplatform.device_name, m_str.c_str(), len);

	maxLen = sizeof(m_eplatform.passwd);
	memset(m_eplatform.passwd, '\0', maxLen);
	m_str = obj["passwd"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_eplatform.passwd, m_str.c_str(), len);

	for(int i=0; i<4; i++)
	{
		m_eplatform.platform_ip[i] = obj["platform_ip"][i]["item"].asInt();
	}

	maxLen = sizeof(m_eplatform.device_id);
	memset(m_eplatform.device_id, '\0', maxLen);
	m_str = obj["device_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_eplatform.device_id, m_str.c_str(), len);

	maxLen = sizeof(m_eplatform.platform_id);
	memset(m_eplatform.platform_id, '\0', maxLen);
	m_str = obj["platform_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_eplatform.platform_id, m_str.c_str(), len);

	maxLen = sizeof(m_eplatform.scenes_id);
	memset(m_eplatform.scenes_id, '\0', maxLen);
	m_str = obj["scenes_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_eplatform.scenes_id, m_str.c_str(), len);

	m_eplatform.sip_port = obj["sip_port"].asInt();
	m_eplatform.rtsp_port = obj["rtsp_port"].asInt();

	maxLen = sizeof(m_eplatform.channel_id);
	memset(m_eplatform.channel_id, '\0', maxLen);
	m_str = obj["channel_id"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_eplatform.channel_id, m_str.c_str(), len);

	m_eplatform.expire = obj["expire"].asInt();
	m_eplatform.remotePort = obj["remotePort"].asInt();

	RSNetSetParamParam param;
	ZeroMemory(&param, sizeof(param));
	param.ParamType = MsgParamElectricityGrid;
	param.Param = &m_eplatform;
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

 
std::string EPlatform::QueryAll(bool bDefault)
{
	std::string strRet = "err";

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamElectricityGrid;
	param.Req = &req;

	param.ParamSize = sizeof(Eplateform_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(bDefault)
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
	m_obj.clear();
	Json::Value obj(Json::objectValue);
	m_obj["device_name"] = m_eplatform.device_name;
	m_obj["passwd"] = m_eplatform.passwd;
	for(int i=0; i<4; i++)
	{
		obj["item"] = (unsigned char)m_eplatform.platform_ip[i];
		m_obj["platform_ip"].append(obj);
	}
	m_obj["device_id"] = m_eplatform.device_id;
	m_obj["platform_id"] = m_eplatform.platform_id;
	m_obj["scenes_id"] = m_eplatform.scenes_id;
	m_obj["sip_port"] = m_eplatform.sip_port;
	m_obj["rtsp_port"] = m_eplatform.rtsp_port;
	m_obj["channel_id"] = m_eplatform.channel_id[0];

	m_obj["expire"] = m_eplatform.expire;
	m_obj["remotePort"] = m_eplatform.remotePort;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}
