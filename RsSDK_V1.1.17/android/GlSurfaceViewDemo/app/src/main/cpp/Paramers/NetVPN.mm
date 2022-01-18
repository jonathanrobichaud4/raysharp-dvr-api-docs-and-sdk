#include "StdAfx.h"
#include "NetVPN.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	NetVPN * pThis = (NetVPN*)userParam;
	memcpy(&pThis->m_VPN, data, sizeof(RSNet_OpenVpnParam_t));
}

std::string  NetVPN::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_VPN,0,sizeof(RSNet_OpenVpnParam_t));
	m_VPN.StructSize = sizeof(RSNet_OpenVpnParam_t);

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamVpnSet;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_OpenVpnParam_t);;
	param.ParamCallback = ParamDataCallback;

	param.UserParam = this;

	if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["VpnSwitch"] = m_VPN.VpnSwitch;
	m_obj["VpnTlsKeySwitch"] = m_VPN.VpnTlsKeySwitch;
	m_obj["VpnNetDev"] = m_VPN.VpnNetDev;
	m_obj["VpnProtocol"] = m_VPN.VpnProtocol;
	m_obj["VpnPort"] = m_VPN.VpnPort;
	m_obj["VpnServerIP"] =  (char*)m_VPN.VpnServerIP;
	m_obj["VpnUserName"] =  (char*)m_VPN.VpnUserName;
	m_obj["VpnPassword"] =  (char*)m_VPN.VpnPassword;
	m_obj["VpnCipher"] =  (char*)m_VPN.VpnCipher;
	m_obj["VpnAddOptions"] =  (char*)m_VPN.VpnAddOptions;
	m_obj["VpnCompLzo"] = m_VPN.VpnCompLzo;
	
	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int NetVPN::SaveAll(std::string strData)
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
		m_VPN.VpnSwitch = obj["VpnSwitch"].asInt();
		m_VPN.VpnTlsKeySwitch = obj["VpnTlsKeySwitch"].asInt();
		m_VPN.VpnNetDev = obj["VpnNetDev"].asInt();
		m_VPN.VpnProtocol = obj["VpnProtocol"].asInt();
		m_VPN.VpnPort = obj["VpnPort"].asInt();

		int maxLen = sizeof(m_VPN.VpnServerIP);
		memset(m_VPN.VpnServerIP, '\0', maxLen);
		m_str = obj["VpnServerIP"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_VPN.VpnServerIP, m_str.c_str(), len);

		maxLen = sizeof(m_VPN.VpnUserName);
		memset(m_VPN.VpnUserName, '\0', maxLen);
		m_str = obj["VpnUserName"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_VPN.VpnUserName, m_str.c_str(), len);

		maxLen = sizeof(m_VPN.VpnPassword);
		memset(m_VPN.VpnPassword, '\0', maxLen);
		m_str = obj["VpnPassword"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_VPN.VpnPassword, m_str.c_str(), len);

		maxLen = sizeof(m_VPN.VpnCipher);
		memset(m_VPN.VpnCipher, '\0', maxLen);
		m_str = obj["VpnCipher"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_VPN.VpnCipher, m_str.c_str(), len);

		maxLen = sizeof(m_VPN.VpnAddOptions);
		memset(m_VPN.VpnAddOptions, '\0', maxLen);
		m_str = obj["VpnAddOptions"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_VPN.VpnAddOptions, m_str.c_str(), len);

		m_VPN.VpnCompLzo = obj["VpnCompLzo"].asInt();
		m_VPN.StructSize = sizeof(RSNet_OpenVpnParam_t);
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamVpnSet;
		param.Param = &m_VPN;
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