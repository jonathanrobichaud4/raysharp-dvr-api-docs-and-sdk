#include "StdAfx.h"
#include "CaptureJh.h"

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	CaptureJh* pThis = (CaptureJh*)userParam;
	RSNet_SoleCapSchedule_t* RecordSet_t = (RSNet_SoleCapSchedule_t*)data;
	pThis->m_vec.push_back(*RecordSet_t);
}

std::string CaptureJh::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamCapSchedule;
	param.Req = &req;

	param.ParamSize = 0;
	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNet_SoleCapSchedule_t);
	param.ListParamCallback = soleParamCallback;
	param.UserParam = this;

	if(isDefault)
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

void CaptureJh::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j]) & 1) << j;//0000000x
		}

		Json::Value obj(Json::objectValue);
		obj["NormalLo"] = (unsigned int)ull;
		obj["NormalHi"] = (unsigned int)(ull>>32);
		m_obj["Normal"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>1 & 1) << j;//000000x0
		}

		Json::Value obj(Json::objectValue);
		obj["MotionLo"] = (unsigned int)ull;
		obj["MotionHi"] = (unsigned int)(ull>>32);
		m_obj["Motion"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>2 & 1) << j;//00000x00
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>3 & 1) << j;//00000x00
		}

		Json::Value obj(Json::objectValue);
		obj["IntelligentLo"] = (unsigned int)ull;
		obj["IntelligentHi"] = (unsigned int)(ull>>32);
		m_obj["Intelligent"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>7 & 1) << j;//x0000000
		}

		Json::Value obj(Json::objectValue);
		obj["PirLo"] = (unsigned int)ull;
		obj["PirHi"] = (unsigned int)(ull>>32);
		m_obj["Pir"].append(obj);
	}
}

int CaptureJh::SaveAll(std::string strData)
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
		unsigned int Lo;
		unsigned int Hi;
		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Normal"][xq]["NormalLo"].asDouble();
			Hi = (unsigned int)obj[i]["Normal"][xq]["NormalHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] = 0;
				m_vec[i].HalfHour[xq][j] |= ull>>j&1;//0000000x
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Motion"][xq]["MotionLo"].asDouble();
			Hi = (unsigned int)obj[i]["Motion"][xq]["MotionHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<1;//000000x0
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentLo"].asDouble();
			Hi = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<3;//00000x00
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Alarm"][xq]["AlarmLo"].asDouble();
			Hi = (unsigned int)obj[i]["Alarm"][xq]["AlarmHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<2;//00000x00
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Pir"][xq]["PirLo"].asDouble();
			Hi = (unsigned int)obj[i]["Pir"][xq]["PirHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<7;//x0000000
			}
		}

		m_vec[i].StructSize = sizeof(RSNet_SoleCapSchedule_t);
	}

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamCapSchedule;
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