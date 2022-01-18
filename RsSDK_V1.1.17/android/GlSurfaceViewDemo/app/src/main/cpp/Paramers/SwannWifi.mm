#include "StdAfx.h"
#include "SwannWifi.h"

std::string SwannWifi::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Wifiset, '\0', sizeof(RSNet_CountryCode_t));
	m_Wifiset.StructSize = sizeof(RSNet_CountryCode_t);
	param.Param = &m_Wifiset;

	param.ParamSize = sizeof(RSNet_CountryCode_t);
	param.ParamType = MsgParamSwannWifi;

	if(bDefault)
	{
		if (!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}
	else
	{
		if (!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	m_obj.clear(); 
	m_obj["channel"] = m_Wifiset.channel;
	m_obj["region"] = m_Wifiset.region;
	m_obj["wifiVersion"] = (char*)m_Wifiset.wifiVersion;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}


int SwannWifi::SaveAll(std::string strData)
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
	m_Wifiset.channel = obj["channel"].asInt();
	m_Wifiset.region = obj["region"].asInt();

	//int maxLen = sizeof(m_Wifiset.wifiVersion);
	//memset(m_Wifiset.wifiVersion, '\0', maxLen);
	//m_str = obj["wifiVersion"].asString();
	//int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	//memcpy(m_Wifiset.wifiVersion, m_str.c_str(), len);

	m_Wifiset.StructSize = sizeof(RSNet_CountryCode_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));

	param.ParamType = MsgParamSwannWifi;
	param.Param = &m_Wifiset;

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