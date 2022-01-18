#include "StdAfx.h"
#include "RTSP.h"

std::string RTSP::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Rtsp, '\0', sizeof(RSNet_Rtsp_t));
	m_Rtsp.StructSize = sizeof(RSNet_Rtsp_t);
	param.Param = &m_Rtsp;

	param.ParamSize = sizeof(RSNet_Rtsp_t);
	param.ParamType = MsgParamRtsp;

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
	m_obj["enAuthMode"] = m_Rtsp.enAuthMode;
	m_obj["RtspPort"] = m_Rtsp.RtspPort;
	m_obj["RtspEnable"] = m_Rtsp.RtspEnable;
	m_obj["RtspUserName"] = m_Rtsp.RtspUserName;
	m_obj["RtspPassword"] = m_Rtsp.RtspPassword;
	m_obj["anonymousLogin"] = m_Rtsp.anonymousLogin;
	m_obj["Checkflag"] = m_Rtsp.Checkflag;
	m_obj["IpEyeEnable"] = m_Rtsp.IpEyeEnable;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int RTSP::SaveAll(std::string strData)
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
		m_Rtsp.enAuthMode = obj["enAuthMode"].asInt();
		m_Rtsp.RtspPort = obj["RtspPort"].asInt();
		m_Rtsp.RtspEnable = obj["RtspEnable"].asInt();
		m_Rtsp.anonymousLogin = obj["anonymousLogin"].asInt();

		int maxLen = sizeof(m_Rtsp.RtspUserName);
		memset(m_Rtsp.RtspUserName, '\0', maxLen);
		m_str = obj["RtspUserName"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Rtsp.RtspUserName, m_str.c_str(), len);

		maxLen = sizeof(m_Rtsp.RtspPassword);
		memset(m_Rtsp.RtspPassword, '\0', maxLen);
		m_str = obj["RtspPassword"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Rtsp.RtspPassword, m_str.c_str(), len);

		m_Rtsp.Checkflag = obj["Checkflag"].asInt();
		m_Rtsp.IpEyeEnable = obj["IpEyeEnable"].asInt();

		m_Rtsp.StructSize = sizeof(RSNet_Rtsp_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));

	param.ParamType = MsgParamRtsp;
	param.Param = &m_Rtsp;

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