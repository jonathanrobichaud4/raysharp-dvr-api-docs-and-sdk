#include "StdAfx.h"
#include "RecInfo.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	RecInfo* pThis = (RecInfo*)userParam;
	RSNet_SoleRecInfo_t* SoleRecInfo = (RSNet_SoleRecInfo_t*)data;
	pThis->m_vec.push_back(*SoleRecInfo);
}

std::string RecInfo::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamRecInfo;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleRecInfo_t);
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

void RecInfo::StructToJson(int i)
{
	m_obj.clear();
	m_obj["ch"] = i;

	//通道号
	int ChnNo = m_vec[i].ChannelMask;//1 2 4 8 16 32 0 128
	if(ChnNo==0){
		return;
	}else{
		m_obj["ChnNo"] = i;
	}

	m_obj["RecStatus"] = m_vec[i].RecStatus;
	m_obj["RecType"] = m_vec[i].RecType;
	m_obj["Fps"] = m_vec[i].Fps;
	m_obj["Bitrate"] = m_vec[i].Bitrate;
	m_obj["RecordSwitch"] = m_vec[i].RecordSwitch;

	char buf[256] = {0};
	sprintf(buf, "%d x %d", m_vec[i].ResWidth,m_vec[i].ResHeight);
	m_obj["Resolution"] = buf;

	m_obj["RecStreamMode"] = m_vec[i].RecStreamMode;
}