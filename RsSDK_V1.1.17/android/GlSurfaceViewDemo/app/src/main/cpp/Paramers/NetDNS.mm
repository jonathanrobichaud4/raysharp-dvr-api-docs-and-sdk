#include "StdAfx.h"
#include "NetDNS.h"

std::string NetDNS::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_DDNSSet,'\0',  sizeof(RSNet_DDNSSet_t));
	m_DDNSSet.StructSize = sizeof(RSNet_DDNSSet_t);
	param.Param = &m_DDNSSet;

	param.ParamSize = sizeof(RSNet_DDNSSet_t);
	param.ParamType = MsgParamDDNS;

	if(isDefault)
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
	m_obj["HostName"] = (char*)m_DDNSSet.HostName;
	m_obj["UserName"] = (char*)m_DDNSSet.UserName;
	m_obj["UserPW"] = (char*)m_DDNSSet.UserPW;
	m_obj["UseDDNS"] = m_DDNSSet.UseDDNS;
	m_obj["c112UseLoginFlag"] = m_DDNSSet.CommaxUseLoginFlag;
	m_obj["ServerAddr"] = m_DDNSSet.ServerAddr;
	m_obj["DDNSUseFlag"] = m_DDNSSet.DDNSUseFlag;
	m_obj["DDNSID"] = (char*)m_DDNSSet.DDNSID;
	m_obj["extendDDNS"] = m_DDNSSet.extendDDNS;
	m_obj["P2pKeyID"] = (char*)m_DDNSSet.P2pKeyID;
	m_obj["IpType"] = m_DDNSSet.IpType;
	m_obj["UserUrl"] = (char*)m_DDNSSet.UserUrl;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int NetDNS::SaveAll(std::string strData)
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
		m_DDNSSet.ServerAddr = obj["ServerAddr"].asInt();
		m_DDNSSet.UseDDNS = obj["UseDDNS"].asInt();
		m_DDNSSet.CommaxUseLoginFlag = obj["c112UseLoginFlag"].asInt();
		if(!obj["IpType"].isNull()){
			m_DDNSSet.IpType = obj["IpType"].asInt();
		}
		

		int maxLen = sizeof(m_DDNSSet.UserName);
		memset(m_DDNSSet.UserName, '\0', maxLen);
		m_str = obj["UserName"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_DDNSSet.UserName, m_str.c_str(), len);

		maxLen = sizeof(m_DDNSSet.UserPW);
		memset(m_DDNSSet.UserPW, '\0', maxLen);
		m_str = obj["UserPW"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_DDNSSet.UserPW, m_str.c_str(), len);

		maxLen = sizeof(m_DDNSSet.DDNSID);
		memset(m_DDNSSet.DDNSID, '\0', maxLen);
		m_str = obj["DDNSID"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_DDNSSet.DDNSID, m_str.c_str(), len);

		maxLen = sizeof(m_DDNSSet.HostName);
		memset(m_DDNSSet.HostName, '\0', maxLen);
		m_str = obj["HostName"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_DDNSSet.HostName, m_str.c_str(), len);

		if(!obj["UserUrl"].isNull()){
			maxLen = sizeof(m_DDNSSet.UserUrl);
			memset(m_DDNSSet.UserUrl, '\0', maxLen);
			m_str = obj["UserUrl"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_DDNSSet.UserUrl, m_str.c_str(), len);
		}
		
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamDDNS;
		param.Param = &m_DDNSSet;
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