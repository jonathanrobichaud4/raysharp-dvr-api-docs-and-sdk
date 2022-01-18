#include "StdAfx.h"
#include "ZeroChannel.h"

static void RSNET_CALL ParamDataCallback(void* param, void* userParam)
{
	ZeroChannel * pThis = (ZeroChannel*)userParam;
	memcpy(&pThis->m_Struct, param, sizeof(RSNet_ZeroChnSet_t));
}

std::string ZeroChannel::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_ZeroChnSet_t));
	m_Struct.StructSize = sizeof(RSNet_ZeroChnSet_t);

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));
	param.ParamType = MsgParamZeroChn;
	param.Req = &m_Struct;

	param.ParamSize = sizeof(RSNet_ZeroChnSet_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["ChnName"] = (char*)m_Struct.ChnName;
	m_obj["Position"] = m_Struct.Position;
	m_obj["fps"] = m_Struct.fps;
	m_obj["resolution"] = m_Struct.resolution;
	m_obj["zeroChnSwitch"] = m_Struct.zeroChnSwitch;
	m_obj["bitrate"] = m_Struct.bitrate;
	m_obj["SplitMode"] = m_Struct.SplitMode;
	m_obj["DwellTime"] = m_Struct.DwellTime;
	for(int i = 0;i < 256;++i)
	{
		m_obj["ChnList"][i] = m_Struct.ChnList[i];
	}

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int ZeroChannel::SaveAll(std::string strData)
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
	int maxLen = sizeof(m_Struct.ChnName);
	memset(m_Struct.ChnName, '\0', maxLen);
	std::string str = obj["ChnName"].asString();
	int len = str.length() < maxLen ? str.length() : maxLen;
	memcpy(m_Struct.ChnName, str.c_str(), len);
	m_Struct.Position = obj["Position"].asUInt();
	m_Struct.fps = obj["fps"].asUInt();
	m_Struct.resolution = obj["resolution"].asUInt();
	m_Struct.zeroChnSwitch = obj["zeroChnSwitch"].asUInt();
	m_Struct.bitrate = obj["bitrate"].asUInt();
	m_Struct.SplitMode = obj["SplitMode"].asUInt();
	 m_Struct.DwellTime = obj["DwellTime"].asUInt();
	for(int i = 0;i < 256;++i)
	{
		m_Struct.ChnList[i] = obj["ChnList"][i].asUInt();
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamZeroChn;
	param.Param = &m_Struct;
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}