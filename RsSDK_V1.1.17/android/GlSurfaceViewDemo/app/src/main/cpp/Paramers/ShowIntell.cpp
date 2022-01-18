#include "StdAfx.h"
#include "ShowIntell.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	ShowIntell* pThis = (ShowIntell*)userParam;
	RSNet_SoleIntManage_t* SoleIntManage = (RSNet_SoleIntManage_t*)data;
	pThis->m_vec.push_back(*SoleIntManage);
}

std::string ShowIntell::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIntManage;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleIntManage_t);
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

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

void ShowIntell::StructToJson( int n )
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["FunSwitchDisplay"] = m_vec[n].FunSwitchDisplay;
	m_obj["AlramDisplay"] = m_vec[n].AlramDisplay;
	m_obj["RecordDisplay"] = m_vec[n].RecordDisplay;
	m_obj["EmailDisplay"] = m_vec[n].EmailDisplay;
	m_obj["AlarmOutDisplay"] = m_vec[n].AlarmOutDisplay;
	m_obj["SceneDisplay"] = m_vec[n].SceneDisplay;
	m_obj["InCountDisplay"] = m_vec[n].InCountDisplay;
	m_obj["OutCountDisplay"] = m_vec[n].OutCountDisplay;
	m_obj["CloudVideoIsUsed"] = m_vec[n].CloudVideoIsUsed;
}
