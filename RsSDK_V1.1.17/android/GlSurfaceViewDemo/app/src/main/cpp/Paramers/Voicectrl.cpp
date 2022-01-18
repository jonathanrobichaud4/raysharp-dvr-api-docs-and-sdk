#include "StdAfx.h"
#include "VoiceCtrl.h"

static void RSNET_CALL ParamDataCallback(void* param, void* userParam)
{
	VoiceCtrl * pThis = (VoiceCtrl*)userParam;
	memcpy(&pThis->m_Struct, param, sizeof(RSNet_VoiceSet_t));
}

std::string VoiceCtrl::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_VoiceSet_t));
	m_Struct.StructSize = sizeof(RSNet_VoiceSet_t);

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));
	param.ParamType = MsgParamVoice;
	param.Req = &m_Struct;

	param.ParamSize = sizeof(RSNet_VoiceSet_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["VoiceCtrl"] = m_Struct.Audio;
	m_obj["MicInVolume"] = m_Struct.MicInVolume;
	m_obj["LineOutVolume"] = m_Struct.LineOutVolume;
	m_obj["AdecEncoding"] = m_Struct.AdecEncoding;
	m_obj["AudioSampleEnable"] = m_Struct.AudioSampleEnable;
	m_obj["AudioSampleRate"] = m_Struct.AudioSampleRate;
	m_obj["AdecEncodingSupport"] = m_Struct.AdecEncodingSupport;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int VoiceCtrl::SaveAll(std::string strData)
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
	m_Struct.LineOutVolume = obj["LineOutVolume"].asInt();
	m_Struct.MicInVolume = obj["MicInVolume"].asInt();
	m_Struct.Audio = obj["VoiceCtrl"].asInt();
	m_Struct.AdecEncoding = obj["AdecEncoding"].asInt();
	m_Struct.AudioSampleRate = obj["AudioSampleRate"].asInt();

	//保存数据
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamVoice;
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