#include "StdAfx.h"
#include "ChnInfo.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	ChnInfo* pThis = (ChnInfo*)userParam;
	RSNet_SoleChnInfo_t* SoleChnInfo = (RSNet_SoleChnInfo_t*)data;
	pThis->m_vec.push_back(*SoleChnInfo);
}

std::string ChnInfo::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamChnInfo;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleChnInfo_t);
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

void ChnInfo::StructToJson(int i)
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
	//0 使用32位
    m_obj["NewChnAliasFlag"] = m_vec[i].NewChnAliasFlag;

	//别名
	m_obj["ChnAlias"] = (char *)m_vec[i].ChnAlias;

	m_obj["ExtendChnAliasMask"] = (char *)m_vec[i].ExtendChnAliasMask;

	//状态
	m_obj["ChnStatus"] = m_vec[i].ChnStatus;

	if( (m_vec[i].SupportTypes>>0)&1 ){//支持Mainstream
		//Mainstream
		char buf[256] = {0};
		sprintf(buf, "%d x %d,%dFps,%dKbps",m_vec[i].ResWidth[0],m_vec[i].ResHeight[0],m_vec[i].Fps[0],m_vec[i].Bitrate[0]);
		m_obj["Mainstream"] = buf;
	}else{
		m_obj["Mainstream"] = 0;
	}

	if( (m_vec[i].SupportTypes>>1)&1 ){//支持Substream
		//Substream
		char buf[256] = {0};
		sprintf(buf, "%d x %d,%dFps,%dKbps", m_vec[i].ResWidth[1],m_vec[i].ResHeight[1],m_vec[i].Fps[1],m_vec[i].Bitrate[1]);
		m_obj["Substream"] = buf;
	}else{
		m_obj["Substream"] = 0;
	}

	if( (m_vec[i].SupportTypes>>2)&1 ){//支持Mobilestream
		//Mobilestream
		char buf[256] = {0};
		sprintf(buf, "%d x %d,%dFps,%dKbps", m_vec[i].ResWidth[2],m_vec[i].ResHeight[2],m_vec[i].Fps[2],m_vec[i].Bitrate[2]);
		m_obj["Mobilestream"] = buf;
	}else{
		m_obj["Mobilestream"] = 0;
	}

	//MotionDetection
	m_obj["MotionDetection"] = (m_vec[i].ConfigStatus>>0)&1;
	//PrivacyZone
	m_obj["PrivacyZone"] = (m_vec[i].ConfigStatus>>1)&1;
}