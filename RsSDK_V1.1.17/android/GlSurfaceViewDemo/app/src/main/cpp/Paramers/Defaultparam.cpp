#include "StdAfx.h"
#include "Defaultparam.h"

int Defaultparam::SaveAll(std::string strData)
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
	memset(&m_Def, '\0', sizeof(RSNet_DefaultSet_t));

	m_Def.AdvanceSet_flag = obj["AdvanceSet_flag"].asInt();
	m_Def.AlarmSet_flag = obj["AlarmSet_flag"].asInt();
	m_Def.DisplaySet_flag = obj["DisplaySet_flag"].asInt();
	m_Def.NetworkSet_flag = obj["NetworkSet_flag"].asInt();
	m_Def.RecordSet_flag = obj["RecordSet_flag"].asInt();
	m_Def.SystemSet_flag = obj["SystemSet_flag"].asInt();
	m_Def.DeviceSet_flag = obj["DeviceSet_flag"].asInt();
	m_Def.IntelligentSet_flag = obj["IntelligentSet_flag"].asInt();
	m_Def.Pairing_flag = obj["Pairing_flag"].asInt();
	m_Def.StructSize = sizeof(RSNet_DefaultSet_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamDefault;
	param.Param = &m_Def;
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
