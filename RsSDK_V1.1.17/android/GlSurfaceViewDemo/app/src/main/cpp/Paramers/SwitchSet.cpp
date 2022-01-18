#include "StdAfx.h"
#include "SwitchSet.h"

static void RSNET_CALL ParamDataCallback(void* param, void* userParam)
{
	SwitchSet * pThis = (SwitchSet*)userParam;
	memcpy(&pThis->m_Struct, param, sizeof(RSNet_SwitchSet_t));
}

std::string SwitchSet::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_SwitchSet_t));
	m_Struct.StructSize = sizeof(RSNet_SwitchSet_t);

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));
	param.ParamType = MsgParamSwitch;
	param.Req = &m_Struct;

	param.ParamSize = sizeof(RSNet_SwitchSet_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	for(int i = 0; i < 4;++i)
	{
		m_obj["IPAddr"][i] = m_Struct.IPAddr[i];
		m_obj["NetMask"][i] = m_Struct.NetMask[i];
		m_obj["GateWay"][i] = m_Struct.GateWay[i];
	}
	for(int i = 0;i < 16;++i)
	{
		m_obj["TransmissionMode"][i] = m_Struct.TransmissionMode[i];
	}
	m_obj["SwitchMode"] = m_Struct.SwitchMode;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int SwitchSet::SaveAll(std::string strData)
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
	m_Struct.SwitchMode = obj["SwitchMode"].asUInt();
	for(int i = 0;i < 4;++i)
	{
		m_Struct.IPAddr[i] = obj["IPAddr"][i].asUInt();
		m_Struct.NetMask[i] = obj["NetMask"][i].asUInt();
		m_Struct.GateWay[i] = obj["GateWay"][i].asUInt();
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamSwitch;
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