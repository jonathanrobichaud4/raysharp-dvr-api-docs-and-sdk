#include "StdAfx.h"
#include "SysParamSerial.h"

std::string SysParamSerial::QueryAll(bool isDefault)
{
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_SerialInfo, '\0', sizeof(RSNet_SerialInfo_t));
	m_SerialInfo.StructSize = sizeof(RSNet_SerialInfo_t);

	param.ParamType = MsgParamSerial;
	param.ParamSize = sizeof(RSNet_SerialInfo_t);
	param.Param = &m_SerialInfo;


	if(isDefault)
	{
		if(!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	Json::Value root(Json::objectValue);
	root["Protocol"] = m_SerialInfo.Protocol;
	root["Baudrate"] = m_SerialInfo.Baudrate;
	root["DataBit"] = m_SerialInfo.DataBit;
	root["StopBit"] = m_SerialInfo.StopBit;
	root["Check"] = m_SerialInfo.Check;
	root["KbSwitch"] = m_SerialInfo.KbSwitch;
	root["FlowCtrl"] = m_SerialInfo.FlowCtrl;
	//root["reservel"] = m_SerialInfo.reservel;

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

int SysParamSerial::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	m_SerialInfo.Protocol = obj["Protocol"].asUInt();
	m_SerialInfo.Baudrate = obj["Baudrate"].asUInt();
	m_SerialInfo.DataBit = obj["DataBit"].asUInt();
	m_SerialInfo.StopBit = obj["StopBit"].asUInt();
	m_SerialInfo.Check = obj["Check"].asUInt();
	m_SerialInfo.KbSwitch = obj["KbSwitch"].asUInt();
	m_SerialInfo.FlowCtrl = obj["FlowCtrl"].asUInt();
	//m_SerialInfo.reservel = obj["reservel"].asUInt();

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamSerial;
	param.Param = &m_SerialInfo;
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

