#include "StdAfx.h"
#include "PlatformSet.h"

PlatformSet::PlatformSet(void)
{
	memset(&m_Struct,'\0',sizeof(RSNet_PlatformSet_t));
	m_Struct.StructSize = sizeof(RSNet_PlatformSet_t);
}

PlatformSet::~PlatformSet(void)
{
}

std::string PlatformSet::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0', sizeof(param));

	memset(&m_Struct,'\0', sizeof(RSNet_PlatformSet_t));
	m_Struct.StructSize = sizeof(RSNet_PlatformSet_t);
	param.Param = &m_Struct;

	param.ParamSize = sizeof(RSNet_PlatformSet_t);
	param.ParamType = MsgParamPlatform;

	if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["PlatEnable"] = m_Struct.PlatformEnable;
	m_obj["PlatAddr"] = (char*)m_Struct.PlatformAddr;
	m_obj["PlatPort"] = m_Struct.PlatformPort;
	m_obj["PlatSelect"] = m_Struct.PlatformSelect;
	m_obj["PlatProtocol"] = m_Struct.MediaConType;
	m_obj["PlatPuid"] = (char*)m_Struct.PuID;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int PlatformSet::SaveAll(std::string strData)
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
	int maxLen = sizeof(m_Struct.PuID);
	memset(m_Struct.PuID, '\0', maxLen);
	m_str = obj["PlatPuid"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Struct.PuID, m_str.c_str(), len);
	
	maxLen = sizeof(m_Struct.PlatformAddr);
	memset(m_Struct.PlatformAddr, '\0', maxLen);
	m_str = obj["PlatAddr"].asString();
	len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_Struct.PlatformAddr, m_str.c_str(), len);

	m_Struct.PlatformEnable = obj["PlatEnable"].asInt();
	m_Struct.PlatformPort = obj["PlatPort"].asInt();
	m_Struct.PlatformSelect = obj["PlatSelect"].asInt();
	m_Struct.MediaConType = obj["PlatProtocol"].asInt();
	m_Struct.StructSize = sizeof(RSNet_PlatformSet_t);

	//保存数据
	int ret = FALSE;
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamPlatform;
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
