#include "StdAfx.h"
#include "DropboxParam.h"

int DropBoxParam::SaveAll(std::string strData)
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
    memset(&m_Struct, 0, sizeof(m_Struct));
	m_str = obj["token"].asCString();
	size_t len = m_str.length();
	len = len > sizeof(m_Struct.token)? sizeof(m_Struct.token):len;
	memcpy(m_Struct.token,m_str.c_str(),len);
	m_Struct.StructSize = sizeof(RSNet_DropBoxParam_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgdropboxParam;
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
