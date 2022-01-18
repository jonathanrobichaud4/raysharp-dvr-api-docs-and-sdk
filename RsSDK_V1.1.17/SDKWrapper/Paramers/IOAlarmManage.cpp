#include "StdAfx.h"
#include "IOAlarmManage.h"


IOAlarmManage::IOAlarmManage( void )
{
	memset(&m_IoAlarmManage, 0, sizeof(RSNet_IoAlarmManage_t));
}

IOAlarmManage::~IOAlarmManage( void )
{

}

std::string IOAlarmManage::QueryAll( bool bDefault /*= false*/ )
{
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_IoAlarmManage,'\0', sizeof(RSNet_IoAlarmManage_t));
	m_IoAlarmManage.Structsize = sizeof(RSNet_IoAlarmManage_t);
	param.Param = &m_IoAlarmManage;

	param.ParamSize = sizeof(RSNet_IoAlarmManage_t);
	param.ParamType = MsgParamIOAlarmManage;

	if (!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	m_obj.clear();
	m_obj["DispatchedFlag"] = m_IoAlarmManage.DispatchedFlag;
	
	for (int i=0; i<MAX_IO_INPUT_NUM; i++)
	{
		m_obj["ChangeDispatched"].append(m_IoAlarmManage.ChangeDispatched[i]);
		m_obj["SensorName"].append((char*)(m_IoAlarmManage.SensorName[i]));
	}

	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int IOAlarmManage::SaveAll( std::string strData )
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	m_IoAlarmManage.DispatchedFlag = obj["DispatchedFlag"].asInt();
	for (int i=0; i<MAX_IO_INPUT_NUM; i++)
	{
		m_IoAlarmManage.ChangeDispatched[i] = obj["ChangeDispatched"][i].asInt();
			
		int maxLen = sizeof(m_IoAlarmManage.SensorName[i]);
		memset(m_IoAlarmManage.SensorName[i], '\0', maxLen);
		std::string m_str;
		m_str = obj["SensorName"][i].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_IoAlarmManage.SensorName[i], m_str.c_str(), len);
	}


	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamIOAlarmManage;
	param.Param = &m_IoAlarmManage;
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
