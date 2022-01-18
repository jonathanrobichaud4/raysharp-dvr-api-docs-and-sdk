#include "StdAfx.h"
#include "ProManage.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	ProManage* pThis = (ProManage*)userParam;
	RSNetNew_SoleCustomProtocol_t* proMnage = (RSNetNew_SoleCustomProtocol_t*)data;
	pThis->m_vec.push_back(*proMnage);
}

std::string ProManage::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamCustomProtocol;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNetNew_SoleCustomProtocol_t);
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;
	
	if (bDefault)
	{
		if(!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}
	else
	{

		if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}
	
	//处理数据
	Json::Value root(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void ProManage::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	m_obj["ProtocolName"] = (char*)m_vec[n].ProcotolName;
	m_obj["ProtocolMask"] = m_vec[n].ProtocolMask;
	m_obj["EnableSubStream"] = m_vec[n].EnableSubStream;

	m_obj["MainType"] = m_vec[n].MainStream.Type;
	m_obj["MainTransmisson"] = m_vec[n].MainStream.Transmisson;
	m_obj["MainPort"] = m_vec[n].MainStream.Port;
	m_obj["MainSourcePath"] = (char*)m_vec[n].MainStream.SourcePath;

	m_obj["SubType"] = m_vec[n].SubStream.Type;
	m_obj["SubTransmisson"] = m_vec[n].SubStream.Transmisson;
	m_obj["SubPort"] = m_vec[n].SubStream.Port;
	m_obj["SubSourcePath"] = (char*)m_vec[n].SubStream.SourcePath;
}

int ProManage::SaveAll(std::string strData)
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
	for(int i=0; i<obj.size(); i++)
	{
		int maxLen = sizeof(m_vec[i].ProcotolName);
		memset(m_vec[i].ProcotolName, '\0', maxLen);
		m_str = obj[i]["ProtocolName"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_vec[i].ProcotolName, m_str.c_str(), len);

		m_vec[i].ProtocolMask = obj[i]["ProtocolMask"].asInt();
		m_vec[i].EnableSubStream = obj[i]["EnableSubStream"].asInt();

		//Main
			m_vec[i].MainStream.Type = obj[i]["MainType"].asInt();
			m_vec[i].MainStream.Transmisson = obj[i]["MainTransmisson"].asInt();
			m_vec[i].MainStream.Port = obj[i]["MainPort"].asInt();

			maxLen = sizeof(m_vec[i].MainStream.SourcePath);
			memset(m_vec[i].MainStream.SourcePath, '\0', maxLen);
			m_str = obj[i]["MainSourcePath"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_vec[i].MainStream.SourcePath, m_str.c_str(), len);

		//Sub
			m_vec[i].SubStream.Type = obj[i]["SubType"].asInt();
			m_vec[i].SubStream.Transmisson = obj[i]["SubTransmisson"].asInt();
			m_vec[i].SubStream.Port = obj[i]["SubPort"].asInt();

			maxLen = sizeof(m_vec[i].SubStream.SourcePath);
			memset(m_vec[i].SubStream.SourcePath, '\0', maxLen);
			m_str = obj[i]["SubSourcePath"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_vec[i].SubStream.SourcePath, m_str.c_str(), len);

		m_vec[i].StructSize = sizeof(RSNetNew_SoleCustomProtocol_t);
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamCustomProtocol;
	param.Param = NULL;
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