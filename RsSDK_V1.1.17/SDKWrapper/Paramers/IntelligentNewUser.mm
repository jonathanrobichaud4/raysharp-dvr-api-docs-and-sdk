#include "StdAfx.h"
#include "IntelligentNewUser.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	IntelligentNewUser* pThis = (IntelligentNewUser*)userParam;
	RSNet_SoleHGIntParam_t* HGInt = (RSNet_SoleHGIntParam_t*)data;
	pThis->m_vec.push_back(*HGInt);
}

std::string IntelligentNewUser::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgHGIntParam;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleHGIntParam_t);
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

void IntelligentNewUser::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	
	m_obj["delaycount"] = m_vec[n].delaycount;
	m_obj["misscount"] = m_vec[n].misscount;
	m_obj["rminsize_w"] = m_vec[n].rminsize_w;
	m_obj["rminsize_h"] = m_vec[n].rminsize_h;
	m_obj["rmaxsize_w"] = m_vec[n].rmaxsize_w;
	m_obj["rmaxsize_h"] = m_vec[n].rmaxsize_h;
	m_obj["pminsize"] = m_vec[n].pminsize;
	m_obj["pmaxsize"] = m_vec[n].pmaxsize;
	m_obj["cropused"] = m_vec[n].cropused;
	m_obj["tframeNum"] = m_vec[n].tframeNum;
	m_obj["cropused"] = m_vec[n].cropused;
	Json::Value objRect;
	objRect["x"] = m_vec[n].croproi.x;
	objRect["y"] = m_vec[n].croproi.y;
	objRect["w"] = m_vec[n].croproi.w;
	objRect["h"] = m_vec[n].croproi.h;
	m_obj["Rect"] = objRect;
	m_obj["HGIntSwitch"] = m_vec[n].HGIntSwitch;
	m_obj["SnapShotMode"] = m_vec[n].SnapShotMode;
	for(int i=0; i<2; i++)
	{
		m_obj["SnapShotFrame"].append(m_vec[n].SnapShotFrame[i]);
	}
	m_obj["SavePic"] = m_vec[n].SavePic;
}

int IntelligentNewUser::SaveAll(std::string strData)
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
		m_vec[i].delaycount = obj[i]["delaycount"].asInt();
		m_vec[i].misscount = obj[i]["misscount"].asInt();
		m_vec[i].rminsize_w = obj[i]["rminsize_w"].asInt();
		m_vec[i].rminsize_h = obj[i]["rminsize_h"].asInt();
		m_vec[i].rmaxsize_w = obj[i]["rmaxsize_w"].asInt();
		m_vec[i].rmaxsize_h = obj[i]["rmaxsize_h"].asInt();
		m_vec[i].pminsize = obj[i]["pminsize"].asInt();
		m_vec[i].pmaxsize = obj[i]["pmaxsize"].asInt();
		m_vec[i].cropused = obj[i]["cropused"].asInt();
		m_vec[i].tframeNum = obj[i]["tframeNum"].asInt();
		m_vec[i].croproi.x = obj[i]["Rect"]["x"].asUInt();
		m_vec[i].croproi.y = obj[i]["Rect"]["y"].asUInt();
		m_vec[i].croproi.w = obj[i]["Rect"]["w"].asUInt();
		m_vec[i].croproi.h = obj[i]["Rect"]["h"].asUInt();
		m_vec[i].HGIntSwitch = obj[i]["HGIntSwitch"].asUInt();
		m_vec[i].SnapShotMode = obj[i]["SnapShotMode"].asUInt();
		for(int j = 0;j < obj[i]["SnapShotFrame"].size();++j)
		{
			m_vec[i].SnapShotFrame[j] = obj[i]["SnapShotFrame"][j].asUInt();
		}
		m_vec[i].SavePic = obj[i]["SavePic"].asUInt();
		m_vec[i].StructSize = sizeof(RSNet_SoleHGIntParam_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgHGIntParam;
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