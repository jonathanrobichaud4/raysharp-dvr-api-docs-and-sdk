#include "StdAfx.h"
#include "AutoUpgrade.h"

std::string AutoUpgrade::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0', sizeof(param));

	memset(&m_Struct,'\0', sizeof(RSNet_FtpAutoUpgrade_t));
	m_Struct.StructSize = sizeof(RSNet_FtpAutoUpgrade_t);
	param.Param = &m_Struct;

	param.ParamSize = sizeof(RSNet_FtpAutoUpgrade_t);
	param.ParamType = MsgParamFtpAutoUpgrade;

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
	m_obj["AutoUpgradeEnable"] = m_Struct.AutoUpgradeEnable;
	m_obj["AutoUpgradePrompt"] = m_Struct.AutoUpgradePrompt;
	m_obj["DeviceType"] = (char*)m_Struct.DeviceType;
	m_obj["SoftwareVer"] = (char*)m_Struct.SoftwareVer;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int AutoUpgrade::SaveAll(std::string strData)
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
	m_Struct.AutoUpgradeEnable = obj["AutoUpgradeEnable"].asInt();
	m_Struct.AutoUpgradePrompt = obj["AutoUpgradePrompt"].asInt();
	m_Struct.StructSize = sizeof(RSNet_FtpAutoUpgrade_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0',sizeof(param));
	param.ParamType = MsgParamFtpAutoUpgrade;
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