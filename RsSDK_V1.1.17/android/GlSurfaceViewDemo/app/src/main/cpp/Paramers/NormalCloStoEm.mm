#include "StdAfx.h"
#include "NormalCloStoEm.h"

std::string NormalCloStoEm::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0', sizeof(param));

	memset(&m_Struct, '\0',sizeof(RSNet_NormalCloudStorageEmail_t));
	m_Struct.StructSize = sizeof(RSNet_NormalCloudStorageEmail_t);
	param.Param = &m_Struct;

	param.ParamSize = sizeof(RSNet_NormalCloudStorageEmail_t);
	param.ParamType = MsgParamCloudStorageEmail;

	if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["EmailSwitch"] = m_Struct.EmailSwitch;
	m_obj["SSLSwitch"] = m_Struct.SSLSwitch;
	m_obj["Port"] = m_Struct.Port;
	m_obj["SMTP"] = (char*)m_Struct.SMTP;
	m_obj["SendEmail"] = (char*)m_Struct.SendEmail;
	m_obj["SendEmailPW"] = (char*)m_Struct.SendEmailPW;
	m_obj["RecvEmail"] = (char*)m_Struct.RecvEmail[0];

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int NormalCloStoEm::SaveAll(std::string strData)
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
	m_Struct.EmailSwitch = obj["EmailSwitch"].asInt();
	m_Struct.SSLSwitch = obj["SSLSwitch"].asInt();	
	m_Struct.Port = obj["Port"].asInt();

	int maxLen = sizeof(m_Struct.SMTP);
	memset(m_Struct.SMTP, '\0', maxLen);
	m_str = obj["SMTP"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Struct.SMTP, m_str.c_str(), len);
	
	maxLen = sizeof(m_Struct.SendEmail);
	memset(m_Struct.SendEmail, '\0', maxLen);
	m_str = obj["SendEmail"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Struct.SendEmail, m_str.c_str(), len);
	
	maxLen = sizeof(m_Struct.SendEmailPW);
	memset(m_Struct.SendEmailPW, '\0', maxLen);
	m_str = obj["SendEmailPW"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Struct.SendEmailPW, m_str.c_str(), len);
	
	maxLen = sizeof(m_Struct.RecvEmail[0]);
	memset(m_Struct.RecvEmail[0], '\0', maxLen);
	m_str = obj["RecvEmail"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Struct.RecvEmail[0], m_str.c_str(), len);

	//保存数据
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamCloudStorageEmail;
	param.Param = &m_Struct;
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