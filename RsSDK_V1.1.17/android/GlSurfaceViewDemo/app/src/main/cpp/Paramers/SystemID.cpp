#include "StdAfx.h"
#include "SystemID.h"

std::string CSystemID::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_Struct,'\0',  sizeof(RSNet_SystemIDCtrl_t));
	m_Struct.StructSize = sizeof(RSNet_SystemIDCtrl_t);
	param.Param = &m_Struct;

	param.ParamSize = sizeof(RSNet_SystemIDCtrl_t);
	param.ParamType = MsgParamSystemIDCtrl;

	if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["systemID"] = m_Struct.SystemID;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int CSystemID::SaveAll(std::string strData)
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
	m_Struct.SystemID = obj["systemID"].asUInt();
	m_Struct.StructSize = sizeof(RSNet_SystemIDCtrl_t);

	//保存数据
	RSNetSetParamParam param;
	param.TimeOut = 10000;
	memset(&param,'\0',  sizeof(param));
	param.ParamType = MsgParamSystemIDCtrl;
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