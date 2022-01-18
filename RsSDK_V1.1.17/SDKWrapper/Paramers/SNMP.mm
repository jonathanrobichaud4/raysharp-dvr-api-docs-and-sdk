#include "StdAfx.h"
#include "SNMP.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	SNMP * pThis = (SNMP*)userParam;
	memcpy(&pThis->m_Snmp, data, sizeof(RSNet_Snmp_t));
}

std::string  SNMP::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_Snmp,'\0', sizeof(RSNet_Snmp_t));
	m_Snmp.StructSize = sizeof(RSNet_Snmp_t);

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.Req = &req;
	param.ParamCallback = ParamDataCallback;
	param.ParamType = MsgParamSnmp;
	param.ParamSize = sizeof(RSNet_Snmp_t);
	param.UserParam = this;

	if(isDefault)
	{
		if (!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}
	else
	{
		if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}	

	//处理数据
	m_obj.clear();
	m_obj["SnmpEnable"] = m_Snmp.SnmpEnable;
	m_obj["SnmpPort"] = m_Snmp.SnmpPort;
	m_obj["Trapport"] = m_Snmp.Trapport;
	m_obj["SnmpVersions"] = m_Snmp.SnmpVersions;

	Json::Value Mac(Json::arrayValue);
	for(int i=0; i<6; i++)
	{
		Mac.append(m_Snmp.Mac[i]);
	}
	m_obj["Mac"] = Mac;

	m_obj["readcommunity"] = (char*)m_Snmp.readcommunity;
	m_obj["writecommunity"] = (char*)m_Snmp.writecommunity;
	m_obj["TrapIPAddr"] = (char*)m_Snmp.TrapIPAddr;
	m_obj["IpcIp"] = (char*)m_Snmp.IpcIp;

	Json::Value objUserR;
	objUserR["Authentication"] = m_Snmp.Authentication[0].Authentication;
	objUserR["EncryptedType"] = m_Snmp.Authentication[0].EncryptedType;
	objUserR["Username"] = (char*)m_Snmp.Authentication[0].Username;
	objUserR["AuthenticationPassword"] = (char*)m_Snmp.Authentication[0].AuthenticationPassword;
	objUserR["EncryptedPassword"] = (char*)m_Snmp.Authentication[0].EncryptedPassword;
	m_obj["UserR"] = objUserR;

	Json::Value objUserRW;
	objUserRW["Authentication"] = m_Snmp.Authentication[1].Authentication;
	objUserRW["EncryptedType"] = m_Snmp.Authentication[1].EncryptedType;
	objUserRW["Username"] = (char*)m_Snmp.Authentication[1].Username;
	objUserRW["AuthenticationPassword"] = (char*)m_Snmp.Authentication[1].AuthenticationPassword;
	objUserRW["EncryptedPassword"] = (char*)m_Snmp.Authentication[1].EncryptedPassword;
	m_obj["UserRW"] = objUserRW;
	
	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int SNMP::SaveAll(std::string strData)
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
		if(!obj["SnmpEnable"].isNull()){
			m_Snmp.SnmpEnable = obj["SnmpEnable"].asInt();
		}
		m_Snmp.SnmpPort = obj["SnmpPort"].asInt();
		m_Snmp.Trapport = obj["Trapport"].asInt();
		m_Snmp.SnmpVersions = obj["SnmpVersions"].asInt();

		for(int k=0;k<6;++k)
		{
			m_Snmp.Mac[k] = obj["Mac"][k].asUInt();
		}

		int maxLen = sizeof(m_Snmp.readcommunity);
		memset(m_Snmp.readcommunity, '\0', maxLen);
		m_str = obj["readcommunity"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.readcommunity, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.writecommunity);
		memset(m_Snmp.writecommunity, '\0', maxLen);
		m_str = obj["writecommunity"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.writecommunity, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.TrapIPAddr);
		memset(m_Snmp.TrapIPAddr, '\0', maxLen);
		m_str = obj["TrapIPAddr"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.TrapIPAddr, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.IpcIp);
		memset(m_Snmp.IpcIp, '\0', maxLen);
		m_str = obj["IpcIp"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.IpcIp, m_str.c_str(), len);

		m_Snmp.Authentication[0].Authentication = obj["UserR"]["Authentication"].asInt();
		m_Snmp.Authentication[0].EncryptedType = obj["UserR"]["EncryptedType"].asInt();

		maxLen = sizeof(m_Snmp.Authentication[0].Username);
		memset(m_Snmp.Authentication[0].Username, '\0', maxLen);
		m_str = obj["UserR"]["Username"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.Authentication[0].Username, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.Authentication[0].AuthenticationPassword);
		memset(m_Snmp.Authentication[0].AuthenticationPassword, '\0', maxLen);
		m_str = obj["UserR"]["AuthenticationPassword"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.Authentication[0].AuthenticationPassword, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.Authentication[0].EncryptedPassword);
		memset(m_Snmp.Authentication[0].EncryptedPassword, '\0', maxLen);
		m_str = obj["UserR"]["EncryptedPassword"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.Authentication[0].EncryptedPassword, m_str.c_str(), len);

		m_Snmp.Authentication[1].Authentication = obj["UserRW"]["Authentication"].asInt();
		m_Snmp.Authentication[1].EncryptedType = obj["UserRW"]["EncryptedType"].asInt();

		maxLen = sizeof(m_Snmp.Authentication[1].Username);
		memset(m_Snmp.Authentication[1].Username, '\0', maxLen);
		m_str = obj["UserRW"]["Username"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.Authentication[1].Username, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.Authentication[1].AuthenticationPassword);
		memset(m_Snmp.Authentication[1].AuthenticationPassword, '\0', maxLen);
		m_str = obj["UserRW"]["AuthenticationPassword"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.Authentication[1].AuthenticationPassword, m_str.c_str(), len);

		maxLen = sizeof(m_Snmp.Authentication[1].EncryptedPassword);
		memset(m_Snmp.Authentication[1].EncryptedPassword, '\0', maxLen);
		m_str = obj["UserRW"]["EncryptedPassword"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Snmp.Authentication[1].EncryptedPassword, m_str.c_str(), len);
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamSnmp;
		param.Param = &m_Snmp;
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