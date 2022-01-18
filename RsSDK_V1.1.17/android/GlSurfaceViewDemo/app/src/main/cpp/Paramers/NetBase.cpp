#include "StdAfx.h"
#include "NetBase.h"

std::string NetBase::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_Net,'\0',  sizeof(RSNet_NetworkBaseSet_t));
	m_Net.StructSize = sizeof(RSNet_NetworkBaseSet_t);
	param.Param = &m_Net;

	param.ParamSize = sizeof(RSNet_NetworkBaseSet_t);
	param.ParamType = MsgParamNetworkBase;

	if(isDefault)
	{
		if (!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if (!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//IPv4 处理数据
	StructToJson();
	
	//IPv6查询、处理数据
	RSNetQueryParamParamEx param2;
	ZeroMemory(&param2, sizeof(param2));

	ZeroMemory(&m_NetIPv6, sizeof(RSNet_IPV6_t));
	m_NetIPv6.StructSize = sizeof(RSNet_IPV6_t);
	param2.Param = &m_NetIPv6;

	param2.ParamSize = sizeof(RSNet_IPV6_t);
	param2.ParamType = MsgParamIPV6Info;

	if (RSNetQueryParamEx(m_pDevice->GetConnection(), &param2))
	{
		m_obj["Local_ipv6_addr"] = (char*)m_NetIPv6.Local_ipv6_addr;
		m_obj["Global_ipv6_addr"] = (char*)m_NetIPv6.Global_ipv6_addr;
		m_obj["ipv6_dns_addr"] = (char*)m_NetIPv6.ipv6_dns_addr;
		m_obj["prefixlen"] = m_NetIPv6.prefixlen;
	}

	// rstp 查询
	RSNetQueryParamParamEx param3;
	memset(&param3,'\0',  sizeof(param3));

	memset(&m_Rstp,'\0',  sizeof(RSNet_Rtsp_t));
	m_Net.StructSize = sizeof(RSNet_Rtsp_t);
	param3.Param = &m_Rstp;

	param3.ParamSize = sizeof(RSNet_Rtsp_t);
	param3.ParamType = MsgParamRtsp;

	if (RSNetQueryParamEx(m_pDevice->GetConnection(), &param3))
	{
        m_obj["IpEyeEnable"] = m_Rstp.IpEyeEnable;
		m_obj["RtspPort"] = m_Rstp.RtspPort;
		m_obj["RtspExtPort"] = m_Rstp.RtspExtPort;
	}

	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void NetBase::StructToJson()
{
	m_obj.clear();

	Json::Value obj(Json::objectValue);

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.IPAddr[i];
		m_obj["IPAddr"].append(obj);
	}

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.WifiIPAdrr[i];
		m_obj["WifiIPAdrr"].append(obj);
	}

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.NetMask[i];
		m_obj["NetMask"].append(obj);
	}

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.GateWay[i];
		m_obj["GateWay"].append(obj);
	}

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.dns1[i];
		m_obj["dns1"].append(obj);
	}

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.dns2[i];
		m_obj["dns2"].append(obj);
	}

	for(int i=0; i<4; i++)
	{
		obj["item"] = m_Net.PPPoEIPaddr[i];
		m_obj["PPPoEIPaddr"].append(obj);
	}

	m_obj["Port"] = m_Net.Port;
	m_obj["WebPort"] = m_Net.WebPort;
	m_obj["NetworkMode"] = m_Net.NetworkMode;
	m_obj["UseUPNP"] = m_Net.UseUPNP;
	m_obj["P2Pswitch"] = m_Net.P2Pswitch;
	m_obj["PPPOEuser"] = (char*)m_Net.PPPOEuser;
	m_obj["Password"] = (char*)m_Net.Password;
	m_obj["MobilePort"] = m_Net.MobilePort;
	m_obj["APN"] = (char*)m_Net.APN;
	m_obj["DialCode"] = (char*)m_Net.DialCode;
	m_obj["WirelessUser"] = (char*)m_Net.WirelessUser;
	m_obj["WirelessPwd"] = (char*)m_Net.WirelessPwd;
	m_obj["User3G"] = (char*)m_Net.User3G;
	m_obj["Pwd3G"] = (char*)m_Net.Pwd3G;
	m_obj["EncodeFlag"] = m_Net.EncodeFlag;
	m_obj["PPPoEState"] = m_Net.PPPoEState;
	m_obj["BandWidth"] = m_Net.BandWidth;
	m_obj["IpKBPort"] = m_Net.IpKBPort;
	m_obj["EnablePPPOE"] = m_Net.EnablePPPOE;
	m_obj["Enable3G"] = m_Net.Enable3G;
	m_obj["EnableDHCP"] = m_Net.EnableDHCP;
	m_obj["DownloadSpeed"] = m_Net.DownloadSpeed;
	m_obj["Connect_Procotol"] = m_Net.Connect_Procotol;
	m_obj["UseIPV6"] = m_Net.UseIPV6;
	m_obj["WifiStation"] = m_Net.WifiStation;
	m_obj["EnableWifi"] = m_Net.EnableWifi;
	for(int i = 0; i < 4;++i)
	{
		m_obj["switchIPAddr"][i] = m_Net.switchIPAddr[i];
		m_obj["switchNetMask"][i] = m_Net.switchNetMask[i];
		m_obj["switchGateWay"][i] = m_Net.switchGateWay[i];
	}
	for(int i = 0;i < 16;++i)
	{
		m_obj["TransmissionMode"][i] = m_Net.TransmissionMode[i];
		m_obj["UseUPNPsingle"][i] = m_Net.UseUPNPsingle[i];
	}
	m_obj["SwitchMode"] = m_Net.SwitchMode;
	m_obj["ExternIP"] = (char*)m_Net.ExternIP;
	m_obj["ExternMobilePortStatus"] = m_Net.ExternMobilePortStatus;
	m_obj["ExternPortStatus"] = m_Net.ExternPortStatus;
	m_obj["ExternRtspPortStatus"] = m_Net.ExternRtspPortStatus;
    m_obj["ExternHttpsPortStatus"] = m_Net.ExternHttpsPortStatus;
	m_obj["ExternWebPortStatus"] = m_Net.ExternWebPortStatus;
	m_obj["TOEFlag"] = m_Net.TOEFlag;
	m_obj["ClientExtPort"] = m_Net.ClientExtPort;
	m_obj["WebExtPort"] = m_Net.WebExtPort;
	m_obj["MobileExtPort"] = m_Net.MobileExtPort;
	m_obj["HttpsIntPort"] = m_Net.HttpsIntPort;
	m_obj["HttpsExtPort"] = m_Net.HttpsExtPort;
	m_obj["useUPnPStrategy"] = m_Net.useUPnPStrategy;
	m_obj["UPnPAutoSwitch"] = m_Net.UPnPAutoSwitch;
	m_obj["ClientAutoExtPort"] = m_Net.ClientAutoExtPort;
	m_obj["WebAutoExtPort"] = m_Net.WebAutoExtPort;
}

int NetBase::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	//IPv4 数据
		for(int i=0; i<4; i++)
		{
			m_Net.dns1[i] = obj["dns1"][i]["item"].asInt();
			m_Net.dns2[i] = obj["dns2"][i]["item"].asInt();
			m_Net.GateWay[i] = obj["GateWay"][i]["item"].asInt();
			m_Net.IPAddr[i] = obj["IPAddr"][i]["item"].asInt();
			m_Net.NetMask[i] = obj["NetMask"][i]["item"].asInt();
			m_Net.WifiIPAdrr[i] = obj["WifiIPAdrr"][i]["item"].asInt();
		}

		for(int i=0;i<16;i++){
           m_Net.UseUPNPsingle[i] = obj["UseUPNPsingle"][i].asInt();
		}

		m_Net.NetworkMode = obj["NetworkMode"].asInt();

		if (m_Net.NetworkMode == 1 || obj["curPage"].asInt() == 1)//PPPOE
		{
			int maxLen = sizeof(m_Net.Password);
			memset(m_Net.Password, '\0', maxLen);
			m_str = obj["Password"].asString();
			int len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.Password, m_str.c_str(), len);

			maxLen = sizeof(m_Net.PPPOEuser);
			memset(m_Net.PPPOEuser, '\0', maxLen);
			m_str = obj["PPPOEuser"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.PPPOEuser, m_str.c_str(), len);
		}
		else if (m_Net.NetworkMode == 3 || obj["curPage"].asInt() == 2)//3G
		{
			int maxLen = sizeof(m_Net.APN);
			memset(m_Net.APN, '\0', maxLen);
			m_str = obj["APN"].asString();
			int len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.APN, m_str.c_str(), len);

			maxLen = sizeof(m_Net.DialCode);
			memset(m_Net.DialCode, '\0', maxLen);
			m_str = obj["DialCode"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.DialCode, m_str.c_str(), len);

			maxLen = sizeof(m_Net.WirelessUser);
			memset(m_Net.WirelessUser, '\0', maxLen);
			m_str = obj["WirelessUser"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.WirelessUser, m_str.c_str(), len);

			maxLen = sizeof(m_Net.WirelessPwd);
			memset(m_Net.WirelessPwd, '\0', maxLen);
			m_str = obj["WirelessPwd"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.WirelessPwd, m_str.c_str(), len);

			maxLen = sizeof(m_Net.User3G);
			memset(m_Net.User3G, '\0', maxLen);
			m_str = obj["User3G"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.User3G, m_str.c_str(), len);

			maxLen = sizeof(m_Net.Pwd3G);
			memset(m_Net.Pwd3G, '\0', maxLen);
			m_str = obj["Pwd3G"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.Pwd3G, m_str.c_str(), len);
		}
		else if (m_Net.NetworkMode == 4 || obj["curPage"].asInt() == 3)//wireless
		{
			int maxLen = sizeof(m_Net.WirelessUser);
			memset(m_Net.WirelessUser, '\0', maxLen);
			m_str = obj["WirelessUser"].asString();
			int len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.WirelessUser, m_str.c_str(), len);

			maxLen = sizeof(m_Net.WirelessPwd);
			memset(m_Net.WirelessPwd, '\0', maxLen);
			m_str = obj["WirelessPwd"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_Net.WirelessPwd, m_str.c_str(), len);
		}

		m_Net.Port = obj["Port"].asInt();
		m_Net.UseUPNP = obj["UseUPNP"].asInt();
		if(!obj["P2Pswitch"].isNull()){
			m_Net.P2Pswitch = obj["P2Pswitch"].asInt();
		}
		m_Net.WebPort = obj["WebPort"].asInt();
		m_Net.MobilePort = obj["MobilePort"].asInt();
		m_Net.EncodeFlag = obj["EncodeFlag"].asInt();
		m_Net.BandWidth = obj["BandWidth"].asInt();
		m_Net.IpKBPort = obj["IpKBPort"].asInt();
		m_Net.EnablePPPOE = obj["EnablePPPOE"].asInt();
		m_Net.Enable3G = obj["Enable3G"].asInt();
		m_Net.EnableDHCP = obj["EnableDHCP"].asInt();
		m_Net.DownloadSpeed = obj["DownloadSpeed"].asInt();
		m_Net.Connect_Procotol = obj["Connect_Procotol"].asInt();
		m_Net.EnableWifi = obj["EnableWifi"].asInt();
		m_Net.SwitchMode = obj["SwitchMode"].asUInt();
		m_Net.ClientExtPort = obj["ClientExtPort"].asUInt();
		m_Net.WebExtPort = obj["WebExtPort"].asUInt();
		m_Net.MobileExtPort = obj["MobileExtPort"].asUInt();
		m_Net.HttpsIntPort = obj["HttpsIntPort"].asUInt();
		m_Net.HttpsExtPort = obj["HttpsExtPort"].asUInt();
		m_Net.UPnPAutoSwitch = obj["UPnPAutoSwitch"].asUInt();
		m_Net.ClientAutoExtPort = obj["ClientAutoExtPort"].asUInt();
		m_Net.WebAutoExtPort = obj["WebAutoExtPort"].asUInt();
		if(!obj["switchIPAddr"].isNull())
		{
			for(int i = 0;i < 4;++i)
			{
				m_Net.switchIPAddr[i] = obj["switchIPAddr"][i].asUInt();
				m_Net.switchNetMask[i] = obj["switchNetMask"][i].asUInt();
				m_Net.switchGateWay[i] = obj["switchGateWay"][i].asUInt();
			}
		}
		if(!obj["TOEFlag"].isNull()){
			m_Net.TOEFlag = obj["TOEFlag"].asInt();
		}
		m_Net.StructSize = sizeof(RSNet_NetworkBaseSet_t);
	//IPv4 数据

	//IPv6 数据
		if(m_Net.UseIPV6)
		{
			int maxLen = sizeof(m_NetIPv6.Local_ipv6_addr);
			memset(m_NetIPv6.Local_ipv6_addr, '\0', maxLen);
			m_str = obj["Local_ipv6_addr"].asString();
			int len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_NetIPv6.Local_ipv6_addr, m_str.c_str(), len);

			maxLen = sizeof(m_NetIPv6.Global_ipv6_addr);
			memset(m_NetIPv6.Global_ipv6_addr, '\0', maxLen);
			m_str = obj["Global_ipv6_addr"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_NetIPv6.Global_ipv6_addr, m_str.c_str(), len);

			maxLen = sizeof(m_NetIPv6.ipv6_dns_addr);
			memset(m_NetIPv6.ipv6_dns_addr, '\0', maxLen);
			m_str = obj["ipv6_dns_addr"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_NetIPv6.ipv6_dns_addr, m_str.c_str(), len);

			m_NetIPv6.prefixlen = obj["prefixlen"].asInt();
			m_NetIPv6.StructSize = sizeof(RSNet_IPV6_t);
		}
	//IPv6 数据

	// RSTP 数据 
        m_Rstp.IpEyeEnable = obj["IpEyeEnable"].asInt();
		m_Rstp.RtspPort = obj["RtspPort"].asInt();
		m_Rstp.RtspExtPort = obj["RtspExtPort"].asInt();
		m_Rstp.StructSize = sizeof(RSNet_Rtsp_t);

	//保存 RSTP（先保存MsgParamRtsp，再保存MsgParamNetworkBase  重启生效）
		bool retRSTP = false;
		RSNetSetParamParam param3;
		memset(&param3, '\0', sizeof(param3));
		param3.ParamType = MsgParamRtsp;
		param3.Param = &m_Rstp;
		int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param3);
		if(2 == nRet){
			return 2;
		}else{
			if(nRet){
				retRSTP = true;
			}
		}
		

	//保存 IPv4
		bool retV4 = false;
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamNetworkBase;
		param.Param = &m_Net;
		if (RSNetSetParam(m_pDevice->GetConnection(), &param))
			retV4 = true;

	//保存 IPv6
		bool retV6 = false;
		if(m_Net.UseIPV6)
		{
			RSNetSetParamParam param2;
			memset(&param2, '\0', sizeof(param2));
			param2.ParamType = MsgParamIPV6Info;
			param2.Param = &m_NetIPv6;
			if (RSNetSetParam(m_pDevice->GetConnection(), &param2))
				retV6 = true;
		}

	//返回结果
		if(m_Net.UseIPV6)
		{
			return (retV4 && retV6);
		}
		else
		{
			return (retV4 && retRSTP);
		}
}