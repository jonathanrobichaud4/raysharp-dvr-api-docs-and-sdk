#include "StdAfx.h"
#include "HttpSet.h"

void HttpSet::StructToJson()
{
	m_obj.clear();

	m_obj["Switch"] = m_HttpSet.UrmetNotificationSwitch;
	m_obj["CurAlarmType"] = m_HttpSet.CurAlarmType;
	m_obj["c2Name"] = m_HttpSet.UrmetName;
	m_obj["c2URL"] = m_HttpSet.UrmetURL;
	m_obj["UserName"] = m_HttpSet.UserName;
	m_obj["Password"] = m_HttpSet.Password;

	Json::Value data(Json::objectValue);
	for (int i=0;i<9;i++)
	{
		data["AlarmType"]= m_HttpSet.UrmetNotificationAlarmInfo[i].AlarmType;
		data["PostAlarmTime"]= m_HttpSet.UrmetNotificationAlarmInfo[i].PostAlarmTime;
		data["IntervalTime"]= m_HttpSet.UrmetNotificationAlarmInfo[i].IntervalTime;
		data["AlarmEnable"]= m_HttpSet.UrmetNotificationAlarmInfo[i].AlarmEnable;
		data["MessageInfo"]= m_HttpSet.UrmetNotificationAlarmInfo[i].MessageInfo;
		m_obj["data"].append(data);
	}
}

std::string HttpSet::QueryAll(bool bDefault)
{
	
	//ÇëÇóÊý¾Ý
	std::string strRet = "err";
	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_HttpSet, '\0', sizeof(RSNet_UrmetHttpParam_t));
	m_HttpSet.StructSize = sizeof(RSNet_UrmetHttpParam_t);
	param.Param = &m_HttpSet;

	param.ParamSize = sizeof(RSNet_UrmetHttpParam_t);
	param.ParamType = MsgParamUrmetHttp;

	if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	StructToJson();
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int HttpSet::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	m_HttpSet.UrmetNotificationSwitch = obj["Switch"].asInt();
	m_HttpSet.CurAlarmType = obj["CurAlarmType"].asInt();

	int maxLen = sizeof(m_HttpSet.UrmetName);
	memset(m_HttpSet.UrmetName, '\0', maxLen);
	m_str = obj["c2Name"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_HttpSet.UrmetName, m_str.c_str(), len);

	maxLen = sizeof(m_HttpSet.UrmetURL);
	memset(m_HttpSet.UrmetURL, '\0', maxLen);
	m_str = obj["c2URL"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_HttpSet.UrmetURL, m_str.c_str(), len);

	maxLen = sizeof(m_HttpSet.UserName);
	memset(m_HttpSet.UserName, '\0', maxLen);
	m_str = obj["UserName"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_HttpSet.UserName, m_str.c_str(), len);

	maxLen = sizeof(m_HttpSet.Password);
	memset(m_HttpSet.Password, '\0', maxLen);
	m_str = obj["Password"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_HttpSet.Password, m_str.c_str(), len);

	for (int i=0;i<9;i++)
	{
		m_HttpSet.UrmetNotificationAlarmInfo[i].AlarmType = obj["data"][i]["AlarmType"].asInt();
		m_HttpSet.UrmetNotificationAlarmInfo[i].PostAlarmTime = obj["data"][i]["PostAlarmTime"].asInt();
		m_HttpSet.UrmetNotificationAlarmInfo[i].IntervalTime = obj["data"][i]["IntervalTime"].asInt();
		m_HttpSet.UrmetNotificationAlarmInfo[i].AlarmEnable = obj["data"][i]["AlarmEnable"].asInt();
		maxLen = sizeof(m_HttpSet.UrmetNotificationAlarmInfo[i].MessageInfo);
		memset(m_HttpSet.UrmetNotificationAlarmInfo[i].MessageInfo, '\0', maxLen);
		m_str = m_str = obj["data"][i]["MessageInfo"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_HttpSet.UrmetNotificationAlarmInfo[i].MessageInfo, m_str.c_str(), len);
	}

	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamUrmetHttp;
	param.Param = &m_HttpSet;

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