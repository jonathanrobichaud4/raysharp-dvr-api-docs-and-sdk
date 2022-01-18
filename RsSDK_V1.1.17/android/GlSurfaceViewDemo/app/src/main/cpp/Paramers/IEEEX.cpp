#include "StdAfx.h"
#include "IEEEX.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	IEEEX * pThis = (IEEEX*)userParam;
	memcpy(&pThis->m_IeeeX, data, sizeof(RSNet_Ieee8021xParam_t));
}

std::string  IEEEX::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_IeeeX,0,sizeof(RSNet_Ieee8021xParam_t));
	m_IeeeX.Structsize = sizeof(RSNet_Ieee8021xParam_t);

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIeee8021xParam;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_Ieee8021xParam_t);;
	param.ParamCallback = ParamDataCallback;

	param.UserParam = this;

	if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["Ieee8021xSwitch"] = m_IeeeX.Ieee8021xSwitch;
	m_obj["EapolVersion"] = m_IeeeX.EapolVersion;
	m_obj["EapId"] = (char*)m_IeeeX.EapId;
	m_obj["Password"] = (char*)m_IeeeX.Password;
	
	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int IEEEX::SaveAll(std::string strData)
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
		m_IeeeX.Ieee8021xSwitch = obj["Ieee8021xSwitch"].asInt();
		m_IeeeX.EapolVersion = obj["EapolVersion"].asInt();

		int maxLen = sizeof(m_IeeeX.EapId);
		memset(m_IeeeX.EapId, '\0', maxLen);
		m_str = obj["EapId"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_IeeeX.EapId, m_str.c_str(), len);

		maxLen = sizeof(m_IeeeX.Password);
		memset(m_IeeeX.Password, '\0', maxLen);
		m_str = obj["Password"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_IeeeX.Password, m_str.c_str(), len);

		m_IeeeX.Structsize = sizeof(RSNet_Ieee8021xParam_t);
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamIeee8021xParam;
		param.Param = &m_IeeeX;
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