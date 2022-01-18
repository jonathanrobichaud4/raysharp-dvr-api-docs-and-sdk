#include "StdAfx.h"
#include "IPFilterList.h"

std::string IPFilterList::QueryAll(bool isDefault)
{
	//ÇëÇóÊý¾Ý
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_IPFilter,'\0',  sizeof(RSNet_NetworkIPFilter_t));
	m_IPFilter.StructSize = sizeof(RSNet_NetworkIPFilter_t);
	param.Param = &m_IPFilter;

	param.ParamSize = sizeof(RSNet_NetworkIPFilter_t);
	param.ParamType = MsgNewIpFilterParam;

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

	StructToJson();
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void IPFilterList::StructToJson()
{
	m_obj.clear();

	Json::Value obj(Json::objectValue);

	for(int i = 0;i < 64;++i)
	{
		for(int j=0; j<16; ++j)
		{
			m_obj["Blacklist"][i]["StartIPAddress"][j] = m_IPFilter.Blacklist[i].StartIPAddress[j];
			m_obj["Blacklist"][i]["EndIPAddress"][j] = m_IPFilter.Blacklist[i].EndIPAddress[j];
			m_obj["Whitelist"][i]["StartIPAddress"][j] = m_IPFilter.Whitelist[i].StartIPAddress[j];
			m_obj["Whitelist"][i]["EndIPAddress"][j] = m_IPFilter.Whitelist[i].EndIPAddress[j];
		}
		m_obj["Blacklist"][i]["IPType"] = m_IPFilter.Blacklist[i].IPType;
		m_obj["Whitelist"][i]["IPType"] = m_IPFilter.Whitelist[i].IPType;
	}
	m_obj["EnableIPFilter"] = m_IPFilter.EnableIPFilter;
	m_obj["BlacklistCount"] = m_IPFilter.BlacklistCount;
	m_obj["WhitelistCount"] = m_IPFilter.WhitelistCount;
	m_obj["ChooseIPFilter"] = m_IPFilter.ChooseIPFilter;
	m_obj["RestrictedType"] = m_IPFilter.RestrictedType;
}

int IPFilterList::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}
	for(int i = 0;i < 64;++i)
	{
		for(int j=0; j<16; ++j)
		{
			m_IPFilter.Blacklist[i].StartIPAddress[j] = obj["Blacklist"][i]["StartIPAddress"][j].asUInt();
			m_IPFilter.Blacklist[i].EndIPAddress[j] = obj["Blacklist"][i]["EndIPAddress"][j].asUInt();
			m_IPFilter.Whitelist[i].StartIPAddress[j] = obj["Whitelist"][i]["StartIPAddress"][j].asUInt();
			m_IPFilter.Whitelist[i].EndIPAddress[j] = obj["Whitelist"][i]["EndIPAddress"][j].asUInt();
		}
		m_IPFilter.Blacklist[i].IPType = obj["Blacklist"][i]["IPType"].asUInt();
		m_IPFilter.Whitelist[i].IPType = obj["Whitelist"][i]["IPType"].asUInt();
	}
	m_IPFilter.EnableIPFilter = obj["EnableIPFilter"].asUInt();
	m_IPFilter.BlacklistCount = obj["BlacklistCount"].asUInt();
	m_IPFilter.WhitelistCount = obj["WhitelistCount"].asUInt();
	m_IPFilter.ChooseIPFilter = obj["ChooseIPFilter"].asUInt();
	m_IPFilter.RestrictedType = obj["RestrictedType"].asUInt();
	m_IPFilter.StructSize = sizeof(RSNet_NetworkIPFilter_t);

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgNewIpFilterParam;
	param.Param = &m_IPFilter;
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