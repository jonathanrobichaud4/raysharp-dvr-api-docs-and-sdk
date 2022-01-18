#include "StdAfx.h"
#include "TypeMeterRecognition.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	TypeMeterRecognition* pThis = (TypeMeterRecognition*)userParam;
	RSNet_SoleJDVCAMeterRecongitionConfig_t* intrusionDec = (RSNet_SoleJDVCAMeterRecongitionConfig_t*)data;
	pThis->m_vec.push_back(*intrusionDec);
}

std::string TypeMeterRecognition::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamJDVCAMeterRecongition;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleJDVCAMeterRecongitionConfig_t);
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;

	if(bDefault)
	{
		if (!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}
	else
	{
		if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
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

void TypeMeterRecognition::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	
	m_obj["left"] = m_vec[n].left;
	m_obj["top"] = m_vec[n].top;
	m_obj["width"] = m_vec[n].width;
	m_obj["height"] = m_vec[n].height;
	m_obj["begangle"] = m_vec[n].begangle;
	m_obj["anglescale"] = m_vec[n].anglescale;
	m_obj["initv"] = m_vec[n].initv;
	m_obj["valuescale"] = m_vec[n].valuescale;
	m_obj["Enable"] = m_vec[n].Enable;
}

int TypeMeterRecognition::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	for(int i=0; i<obj.size(); i++)
	{
		m_vec[i].left = obj[i]["left"].asInt();
		m_vec[i].top = obj[i]["top"].asInt();
		m_vec[i].width = obj[i]["width"].asInt();
		m_vec[i].height = obj[i]["height"].asInt();
		m_vec[i].begangle = obj[i]["begangle"].asInt();
		m_vec[i].anglescale = obj[i]["anglescale"].asInt();
		m_vec[i].initv = obj[i]["initv"].asInt();
		m_vec[i].valuescale = obj[i]["valuescale"].asInt();
		m_vec[i].Enable = obj[i]["Enable"].asInt();
		m_vec[i].StructSize = sizeof(RSNet_SoleJDVCAMeterRecongitionConfig_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamJDVCAMeterRecongition;
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