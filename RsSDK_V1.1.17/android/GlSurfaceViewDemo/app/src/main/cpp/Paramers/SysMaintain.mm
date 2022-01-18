#include "StdAfx.h"
#include "SysMaintain.h"

std::string CSysMaintain::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0',sizeof(param));

	memset(&m_Struct, '\0', sizeof(RSNet_MaintainSet_t));
	m_Struct.StructSize = sizeof(RSNet_MaintainSet_t);
	param.Param = &m_Struct;

	param.ParamSize = sizeof(RSNet_MaintainSet_t);
	param.ParamType = MsgParamMaintain;

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

	//处理数据
		m_obj.clear();
		
		m_obj["time_0"] = m_Struct.time[0];
		m_obj["time_1"] = m_Struct.time[1];
		m_obj["time_2"] = m_Struct.time[2];

		m_obj["automaintain"] = m_Struct.automaintain;
		m_obj["maintainperiod1"] = m_Struct.maintainperiod1;
		m_obj["maintainperiod2"] = m_Struct.maintainperiod2;
		m_obj["defaultuserid"] = m_Struct.defaultuserid;
		m_obj["EnabledUserList"] = m_Struct.EnabledUserList;
		m_obj["EnableUser"] = m_Struct.EnableUser;
		m_obj["TimeFormat"] = m_Struct.TimeFormat;
		m_obj["IRLed"] = m_Struct.IRLed;

		m_obj["UserName_0"] = (char*)m_Struct.UserName[0];
		m_obj["UserName_1"] = (char*)m_Struct.UserName[1];
		m_obj["UserName_2"] = (char*)m_Struct.UserName[2];
		m_obj["UserName_3"] = (char*)m_Struct.UserName[3];
		m_obj["UserName_4"] = (char*)m_Struct.UserName[4];
		m_obj["UserName_5"] = (char*)m_Struct.UserName[5];
		m_obj["UserName_6"] = (char*)m_Struct.UserName[6];

	//返回数据
		Json::FastWriter writer;
		strRet = writer.write(m_obj);
		return strRet;
}

int CSysMaintain::SaveAll(std::string strData)
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
	m_Struct.time[0] = obj["time_0"].asInt();
	m_Struct.time[1] = obj["time_1"].asInt();
	m_Struct.time[2] = obj["time_2"].asInt();

	m_Struct.automaintain = obj["automaintain"].asInt();
	m_Struct.maintainperiod1 = obj["maintainperiod1"].asInt();
	m_Struct.maintainperiod2 = obj["maintainperiod2"].asInt();
	m_Struct.defaultuserid = obj["defaultuserid"].asInt();
	m_Struct.IRLed = obj["IRLed"].asInt();

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamMaintain;
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