#pragma once
#include "StdAfx.h"
#include "SysInfBase.h"

std::string CSysInfBase::QueryAll(std::string strData)
{
	//请求数据1
	std::string strRet = "err";
		
	RSNetQueryParamParamEx param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_BaseInfo,'\0', sizeof(RSNet_SystemBaseInfo_t));
	m_BaseInfo.StructSize = sizeof(RSNet_SystemBaseInfo_t);
	param.Param = &m_BaseInfo;

	param.ParamSize = sizeof(RSNet_SystemBaseInfo_t);
	param.ParamType = MsgParamSystemBase;//502
		
// 	if(isDefault)
// 	{
// 		if (!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param,MsgDefaultParam))
// 			return strRet;
// 	}
// 	else
// 	{
		if (!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
/*	}*/
	// 处理BaseInfo数据
	StructToJson();
		
	//请求数据2

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return strRet;
	}

	bool bQuery2Suc = false;
	m_bQueryExParam = obj["bQuerySecondParam"].asBool();
	if (m_bQueryExParam)
	{
		RSNetQueryParamParamEx param2;
		memset(&param2,'\0',  sizeof(param2));

		memset(&m_BaseInfoEx,'\0', sizeof(RSNet_SysParamInfoEx_t));
		m_BaseInfoEx.StructSize = sizeof(RSNet_SysParamInfoEx_t);
		param2.Param = &m_BaseInfoEx;

		param2.ParamSize = sizeof(RSNet_SysParamInfoEx_t);
		param2.ParamType = MsgSysParamEx;//803

		if (RSNetQueryParamEx(m_pDevice->GetConnection(), &param2))
			bQuery2Suc = true;
	}
		

	//处理数据
	//P2pUID 只能有字母、数字、中划线
	bool bToWeb = true;
	for(int i=0; i<40; i++)
	{
		char temp = m_BaseInfo.P2pUID[i];
		if(temp == '\0')
		{
			break;
		}
		else
		{
			if( !((temp>='0' && temp<='9') || (temp>='a' && temp<='z') || (temp>='A' && temp<='Z') || (temp=='-')) )
			{
				bToWeb = false;
				break;
			}
		}
	}
	if(bToWeb==false)
	{
		memset(m_BaseInfo.P2pUID, 0, sizeof(m_BaseInfo.P2pUID));
	}

	
	if(bQuery2Suc){
		m_obj["P2PSwitch"] = m_BaseInfoEx.bP2pIDUsed;
		m_obj["DeviceIDEx"] = (char*)m_BaseInfoEx.DeviceIDEx;
		m_obj["AFVersion"] = (char*)m_BaseInfoEx.AFVersion;
		m_obj["c0Model"] = (char*)m_BaseInfoEx.lorexModel;
		m_obj["NVRVersion"] = (char*)m_BaseInfoEx.NVRVersion;
		m_obj["INTModelVersion"] = (char*)m_BaseInfoEx.INTModelVersion;
	}

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}
void CSysInfBase::StructToJson()
{
	m_obj.clear();
	m_obj["StructSize"] = m_BaseInfo.StructSize;
#if defined(RS_IPHONE)||defined(RS_ANDROID)
    std::string str = Base64::Encode((unsigned char*)m_BaseInfo.DeviceName, (int)strlen((char*)m_BaseInfo.DeviceName));
    m_obj["DeviceName"] = str.c_str();
#else
    m_obj["DeviceName"] = (char*)m_BaseInfo.DeviceName;
#endif
	m_obj["DeviceID"] = m_BaseInfo.DeviceID;
	m_obj["Port"] = m_BaseInfo.Port;
	m_obj["WebPort"] = m_BaseInfo.WebPort;
	m_obj["DdnsHostStatus"] = (char*)m_BaseInfo.DdnsHostStatus;
	m_obj["DdnsHostStatusFirst"] = m_BaseInfo.DdnsHostStatus[0];
	m_obj["IsZIPDDNS"] =(m_BaseInfo.DdnsHostStatus[35] == 0xaa);
	m_obj["HddStatus"] = (char*)m_BaseInfo.HddStatus;
	m_obj["TvSystem"] = m_BaseInfo.TvSystem;
	m_obj["DeviceType"] = (char*)m_BaseInfo.DeviceType;
	m_obj["MacAddr"] = (char*)m_BaseInfo.MacAddr;
	m_obj["SoftwareVer"] = (char*)m_BaseInfo.SoftwareVer;
	m_obj["HardwareVer"] = (char*)m_BaseInfo.HardwareVer;
	m_obj["IEVer"] = (char*)m_BaseInfo.IEVer;
	m_obj["MobilePort"] = m_BaseInfo.MobilePort;
	m_obj["IpAddr"] = (char*)m_BaseInfo.IpAddr;
	m_obj["P2pKeyID"] = (char*)m_BaseInfo.P2pKeyID;
	m_obj["P2pUID"] = (char*)m_BaseInfo.P2pUID;
	m_obj["AgentVer"] = (char*)m_BaseInfo.AgentVer;
	m_obj["DongleVer"] = (char*)m_BaseInfo.DongleVer;
	m_obj["DomainName"] = (char*)m_BaseInfo.DomainName;
	m_obj["UpnpEnabled"] = m_BaseInfo.UpnpEnabled;
	m_obj["DdnsEnabled"] = m_BaseInfo.DdnsEnabled;
	m_obj["DhcpEnabled"] = m_BaseInfo.DhcpEnabled;
	m_obj["WifiIPAddr"] = (char*)m_BaseInfo.WifiIPAddr;
	m_obj["EnableWifi"] = m_BaseInfo.EnableWifi;
	m_obj["UseIPV6"] = m_BaseInfo.UseIPV6;
	m_obj["P2PSwitchFlag"] = m_BaseInfo.P2PSwitchFlag;
	m_obj["AgentType"] = (char*)m_BaseInfo.AgentType;
	m_obj["SerialNumberEX"] = (char*)m_BaseInfo.SerialNumberEX;
	m_obj["WifiVer"] = (char*)m_BaseInfo.WifiVer;
	m_obj["NetMask"] = (char*)m_BaseInfo.NetMask;
	char gateway[16] = {0};
	sprintf(gateway,"%03d.%03d.%03d.%03d",m_BaseInfo.GateWay[0],m_BaseInfo.GateWay[1],m_BaseInfo.GateWay[2],m_BaseInfo.GateWay[3]);
	m_obj["GateWay"] = gateway;
	m_obj["IPv6Addr"] = (char*)m_BaseInfo.IPv6Addr;
	m_obj["DrivesNumber"] = m_BaseInfo.DrivesNumber;
	m_obj["SerialNumber"] = (char*)m_BaseInfo.SerialNumber;
	m_obj["ClientExtPort"] = m_BaseInfo.ClientExtPort;
	m_obj["WebExtPort"] = m_BaseInfo.WebExtPort;
	m_obj["MobileExtPort"] = m_BaseInfo.MobileExtPort;
#if defined(RS_IPHONE)||defined(RS_ANDROID)
#else
	m_obj["UseUPNP"] = (char*)m_BaseInfo.UseUPNP;
#endif
	m_obj["HttpsIntPort"] = m_BaseInfo.HttpsIntPort;
	m_obj["HttpsExtPort"] = m_BaseInfo.HttpsExtPort;
}

int CSysInfBase::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//处理数据
	bool bSave1 = false;	//是否保存 m_BaseInfo 结构体。有值过来就保存
	bool bSave1_Suc = false;//是否保存成功

	if(!obj["DeviceID"].isNull())
	{
		bSave1 = true;
		m_BaseInfo.DeviceID = obj["DeviceID"].asInt();
	}

	if(!obj["DeviceName"].isNull())
	{
		bSave1 = true;

		int maxLen = sizeof(m_BaseInfo.DeviceName);
		memset(m_BaseInfo.DeviceName, '\0', maxLen);
		m_str = obj["DeviceName"].asString();
#if defined(RS_IPHONE)||defined(RS_ANDROID)
		m_str = Base64::Decode(m_str.c_str(),m_str.length());
#endif
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_BaseInfo.DeviceName, m_str.c_str(), len);
	}

	//保存数据
	if(bSave1)
	{
		RSNetSetParamParam param1;
		memset(&param1, '\0', sizeof(param1));
		param1.ParamType = MsgParamSystemBase;
		param1.Param = &m_BaseInfo;
		int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param1);
		if(2 == nRet){
			return 2;
		}else{
			if (nRet){
				bSave1_Suc = true;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool bSave2 = false;	//是否保存 m_BaseInfoEx 结构体。有值过来就保存
	bool bSave2_Suc = false;//是否保存成功

	if(!obj["P2PSwitch"].isNull())
	{
		bSave2 = true;
		m_BaseInfoEx.bP2pIDUsed = obj["P2PSwitch"].asInt();
	}

	if(bSave2 && m_bQueryExParam)//如果不查询，m_BaseInfoEx地址为空
	{
		//保存数据
		RSNetSetParamParam param2;
		memset(&param2, '\0', sizeof(param2));
		param2.ParamType = MsgSysParamEx;
		param2.Param = &m_BaseInfoEx;
		int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param2);
		if(2 == nRet){
			return 2;
		}else{
			if (nRet){
				bSave2_Suc = true;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(bSave1){
		if(false == bSave1_Suc){
			return false;
		}
	}
	if(bSave2 && m_bQueryExParam){
		if(false == bSave2_Suc){
			return false;
		}
	}
	return true;
}