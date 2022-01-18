#include "StdAfx.h"
#include "NetEmail.h"

std::string NetEmail::QueryAll(bool bDefault)
{
	//ÇëÇóÊý¾Ý
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_EmailSet, '\0', sizeof(RSNet_EmailSet_t));
	m_EmailSet.StructSize = sizeof(RSNet_EmailSet_t);
	param.Param = &m_EmailSet;

	param.ParamSize = sizeof(RSNet_EmailSet_t);
	param.ParamType = MsgParamEmail;

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

void NetEmail::StructToJson()
{
	m_obj.clear();
	
	m_obj["EmailSwitch"] = m_EmailSet.EmailSwitch;
	m_obj["SMTP"] = (char*)m_EmailSet.SMTP;
	m_obj["SendEmail"] = (char*)m_EmailSet.SendEmail;
	m_obj["SendEmailPW"] = (char*)m_EmailSet.SendEmailPW;
	m_obj["RecvEmail_0"] = (char*)m_EmailSet.RecvEmail[0];
	m_obj["RecvEmail_1"] = (char*)m_EmailSet.RecvEmail[1];
	m_obj["RecvEmail_2"] = (char*)m_EmailSet.RecvEmail[2];
	m_obj["SSLSwitch"] = m_EmailSet.SSLSwitch;
	m_obj["intervaltime"] = m_EmailSet.intervaltime;
	m_obj["Port"] = m_EmailSet.Port;
	m_obj["username"] = (char*)m_EmailSet.usename;
}


int NetEmail::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	m_EmailSet.EmailSwitch = obj["EmailSwitch"].asInt();
	m_EmailSet.intervaltime = obj["intervaltime"].asInt();
	m_EmailSet.Port = obj["Port"].asInt();
	m_EmailSet.SSLSwitch = obj["SSLSwitch"].asInt();

	int maxLen = sizeof(m_EmailSet.RecvEmail[0]);
	memset(m_EmailSet.RecvEmail[0], '\0', maxLen);
	m_str = obj["RecvEmail_0"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.RecvEmail[0], m_str.c_str(), len);

	maxLen = sizeof(m_EmailSet.RecvEmail[1]);
	memset(m_EmailSet.RecvEmail[1], '\0', maxLen);
	m_str = obj["RecvEmail_1"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.RecvEmail[1], m_str.c_str(), len);

	maxLen = sizeof(m_EmailSet.RecvEmail[2]);
	memset(m_EmailSet.RecvEmail[2], '\0', maxLen);
	m_str = obj["RecvEmail_2"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.RecvEmail[2], m_str.c_str(), len);

	maxLen = sizeof(m_EmailSet.SendEmail);
	memset(m_EmailSet.SendEmail, '\0', maxLen);
	m_str = obj["SendEmail"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.SendEmail, m_str.c_str(), len);

	maxLen = sizeof(m_EmailSet.SendEmailPW);
	memset(m_EmailSet.SendEmailPW, '\0', maxLen);
	m_str = obj["SendEmailPW"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.SendEmailPW, m_str.c_str(), len);

	maxLen = sizeof(m_EmailSet.SMTP);
	memset(m_EmailSet.SMTP, '\0', maxLen);
	m_str = obj["SMTP"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.SMTP, m_str.c_str(), len);

	maxLen = sizeof(m_EmailSet.usename);
	memset(m_EmailSet.usename, '\0', maxLen);
	m_str = obj["username"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_EmailSet.usename, m_str.c_str(), len);

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamEmail;
	param.Param = &m_EmailSet;
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