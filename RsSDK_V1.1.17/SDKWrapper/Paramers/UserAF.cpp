#pragma once
#include "StdAfx.h"
#include "UserAF.h"

static void RSNET_CALL ListParamCallback(void* data, void* userParam)
{
	UserAF * pThis = (UserAF*)userParam;
	RSNet_IPCAutoFocusInfo_t* SoleAutoFocus = (RSNet_IPCAutoFocusInfo_t*)data;
	pThis->m_vec.push_back(*SoleAutoFocus);
}

static void RSNET_CALL ListParamOneCallback(void* data, void* userParam)
{
	UserAF* pThis = (UserAF*)userParam;
	memcpy(&pThis->m_Struct,data,sizeof(RSNet_IPCAutoFocusInfo_t));
}

std::string UserAF::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	m_vec.clear();

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamIPCCameaFocusInfo;

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_IPCAutoFocusInfo_t);
	param.ListParamCallback = ListParamCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(),&param))
		return strRet;

	//处理数据
	Json::Value root(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

int UserAF::SaveAll(std::string strData)
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
	for(int i = 0;i < obj.size();++i)
	{
		m_vec[i].AFMode = obj[i]["AFMode"].asInt();
		m_vec[i].PowerMode = obj[i]["PowerMode"].asInt();
		m_vec[i].TDNAFSwitch = obj[i]["TDNAFSwitch"].asInt();
		m_vec[i].structsize = sizeof(RSNet_IPCAutoFocusInfo_t);
	}
	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType =MsgParamIPCCameaFocusInfo;
	param.ListParams = &m_vec[0];
	param.ListParamNum = m_vec.size();

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

void UserAF::StructToJson(int n)
{
	m_obj.clear();
	m_obj["AFMode"] = m_vec[n].AFMode;
	m_obj["PowerMode"] = m_vec[n].PowerMode;
	m_obj["TDNAFSwitch"] = m_vec[n].TDNAFSwitch;
}

int UserAF::SaveOne(int n,std::string strData)
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
	m_Struct.structsize = sizeof(RSNet_IPCAutoFocusInfo_t);

	if(n <32){
		m_Struct.channel =  (0x1<<n);
	}else{
		m_Struct.channel =  0xFFFF0000 + n;
	}

	m_Struct.AFMode = obj["AFMode"].asInt();
	m_Struct.PowerMode = obj["PowerMode"].asInt();
	m_Struct.TDNAFSwitch = obj["TDNAFSwitch"].asInt();

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamIPCCameaFocusInfo;
	param.ListParams = &m_Struct;
	param.ListParamNum = 1;

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

std::string UserAF::QueryOne(int n)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Struct, '\0', sizeof(RSNet_IPCAutoFocusInfo_t));

	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamIPCCameaFocusInfo;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_IPCAutoFocusInfo_t);
	param.ListParamCallback = ListParamOneCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["chn"] = n;
	m_obj["AFMode"] = m_Struct.AFMode;
	m_obj["PowerMode"] = m_Struct.PowerMode;
	m_obj["TDNAFSwitch"] = m_Struct.TDNAFSwitch;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}
