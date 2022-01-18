#include "StdAfx.h"
#include "SSL.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	SSL * pThis = (SSL*)userParam;
	memcpy(&pThis->m_SSL, data, sizeof(RSNet_HttpsParam_t));
}

std::string  SSL::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_SSL,0,sizeof(RSNet_HttpsParam_t));
	m_SSL.Structsize = sizeof(RSNet_HttpsParam_t);

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamHttps;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_HttpsParam_t);
	param.ParamCallback = ParamDataCallback;

	param.UserParam = this;

	if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["HttpsType"] = m_SSL.HttpsType;
	m_obj["HttpsSwitch"] = m_SSL.HttpsSwitch;
	m_obj["HttpsPort"] = m_SSL.HttpsPort;
	
	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int SSL::SaveAll(std::string strData)
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
		m_SSL.HttpsSwitch = obj["HttpsSwitch"].asInt();
		m_SSL.HttpsType = obj["HttpsType"].asInt();
		m_SSL.HttpsPort = obj["HttpsPort"].asInt();
		m_SSL.Structsize = sizeof(RSNet_HttpsParam_t);
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamHttps;
		param.Param = &m_SSL;
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