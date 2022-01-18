#include "StdAfx.h"
#include "IPFilter.h"

IPFilter::IPFilter(void)
{
	memset(&m_Filter,'\0',sizeof(m_Filter));
	m_vec.clear();
}

IPFilter::~IPFilter(void)
{
	memset(&m_Filter,'\0',sizeof(m_Filter));
	m_vec.clear();
}

static void RSNET_CALL OneDataCallback(void* data, void* userParam)
{
	IPFilter* pThis = (IPFilter*)userParam;
	RSNet_IPFilter_t* pData = (RSNet_IPFilter_t*)data;
	pThis->m_Filter = *pData;
}

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	IPFilter* pThis = (IPFilter*)userParam;
	RSNet_SoleIPFilter_t* pData = (RSNet_SoleIPFilter_t*)data;
	pThis->m_vec.push_back(*pData);
}

std::string IPFilter::QueryAll(bool bDefault)//old
{

	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param,'\0', sizeof(param));

	memset(&m_Filter,'\0', sizeof(RSNet_IPFilter_t));
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIPFilter;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_IPFilter_t);	
	param.ParamCallback = OneDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleIPFilter_t);
	param.ListParamCallback = AllDataCallback;

	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	Json::Value root(Json::objectValue);

	int len = 0; 
	while(len<m_vec.size() && m_vec[len++].IPAddr[0] != '\0');

	root["Count"] = --len < 0 ? 0 : len;
	root["FilterSwitch"] = m_Filter.FilterSwitch;

	for(int i=0; i<len; i++)
	{
		m_obj.clear();
		m_obj["IPAddr_0"] = m_vec[i].IPAddr[0];
		m_obj["IPAddr_1"] = m_vec[i].IPAddr[1];
		m_obj["IPAddr_2"] = m_vec[i].IPAddr[2];
		m_obj["IPAddr_3"] = m_vec[i].IPAddr[3];
		m_obj["Enable"] = m_vec[i].Enable;

		root["IpInfo"].append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

std::string IPFilter::QueryAll(std::string strData)//new : cut down queryparam
{
	//请求数据
	std::string strRet = "err";

	if(strData == "null"){
		return strRet;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData,obj)){
		return strRet;
	}

	RSNetQueryParamParam param;
	memset(&param,'\0', sizeof(param));

	memset(&m_Filter,'\0', sizeof(RSNet_IPFilter_t));
	m_vec.clear();

	ChannelParamReq req;
	int ch = obj["ch"].asInt();
	if (ch == 0)
	{
		int nStructSize = sizeof(ChannelParamReq);
		memset(&req, 0x0, nStructSize); 
		req.ChannelMask[0] = 0xffff;//ipc
		req.StructSize = nStructSize;
	}else
	{
		TransformChannelParamReq_All(&req);
	}

	param.ParamType = MsgParamIPFilter;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_IPFilter_t);	
	param.ParamCallback = OneDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleIPFilter_t);
	param.ListParamCallback = AllDataCallback;

	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据	
	Json::Value root(Json::objectValue);
	
	int len = 0; 
	while(len<m_vec.size() && m_vec[len++].IPAddr[0] != '\0');
	
	root["Count"] = --len < 0 ? 0 : len;
	root["FilterSwitch"] = m_Filter.FilterSwitch;
	
	for(int i=0; i<len; i++)
	{
		m_obj.clear();
		m_obj["IPAddr_0"] = m_vec[i].IPAddr[0];
		m_obj["IPAddr_1"] = m_vec[i].IPAddr[1];
		m_obj["IPAddr_2"] = m_vec[i].IPAddr[2];
		m_obj["IPAddr_3"] = m_vec[i].IPAddr[3];
		m_obj["Enable"] = m_vec[i].Enable;
		
		root["IpInfo"].append(m_obj);
	}
	
	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

int IPFilter::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData,obj)){
		return false;
	}

	//1、
		int nSize = m_vec.size();
		int nIPNum  = obj["IpInfo"].size();
		int k=0;
		for(; k<nIPNum && k<nSize; k++)
		{
			m_vec[k].Enable = obj["IpInfo"][k]["Enable"].asInt();

			m_vec[k].IPAddr[0] = obj["IpInfo"][k]["IPAddr_0"].asInt();
			m_vec[k].IPAddr[1] = obj["IpInfo"][k]["IPAddr_1"].asInt();
			m_vec[k].IPAddr[2] = obj["IpInfo"][k]["IPAddr_2"].asInt();
			m_vec[k].IPAddr[3] = obj["IpInfo"][k]["IPAddr_3"].asInt();
		}

		for(;k<nSize;k++){
			m_vec[k].IPAddr[0] = '\0';
		}

		for(int i=0;i<nSize;i++){
			m_vec[i].StructSize = sizeof(RSNet_SoleIPFilter_t);
		}

	//2、
		m_Filter.FilterSwitch = obj["FilterSwitch"].asInt();
		m_Filter.StructSize = sizeof(RSNet_IPFilter_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamIPFilter;
	param.Param = &m_Filter;
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