#include "StdAfx.h"
#include "FtpPlan.h"

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	FtpPlan* pThis = (FtpPlan*)userParam;
	RSNet_SoleFtpScheduleset_t* FtpSet_t = (RSNet_SoleFtpScheduleset_t*)data;
	pThis->m_vec.push_back(*FtpSet_t);
}

std::string FtpPlan::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgFtpScheduleParam;
	param.Req = &req;

	param.ParamSize = 0;
	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNet_SoleFtpScheduleset_t);
	param.ListParamCallback = soleParamCallback;

	param.UserParam = this;

	if(bDefault)
	{
		if(!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
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

void FtpPlan::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	Json::Value tmpObj(Json::objectValue);


	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].FtpScHalfHour[i][j]) & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["NormalLo"] = (unsigned int)ull;
		tmpObj["NormalHi"] = (unsigned int)(ull>>32);
		m_obj["Normal"].append(tmpObj);
	}
	
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].FtpScHalfHour[i][j])>>1 & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["MotionLo"] = (unsigned int)ull;
		tmpObj["MotionHi"] = (unsigned int)(ull>>32);
		m_obj["Motion"].append(tmpObj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].FtpScHalfHour[i][j])>>2 & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["AlarmLo"] = (unsigned int)ull;
		tmpObj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm"].append(tmpObj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].FtpScHalfHour[i][j])>>3 & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["PirLo"] = (unsigned int)ull;
		tmpObj["PirHi"] = (unsigned int)(ull>>32);
		m_obj["Pir"].append(tmpObj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].FtpScHalfHour[i][j])>>4 & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["IntelligentLo"] = (unsigned int)ull;
		tmpObj["IntelligentHi"] = (unsigned int)(ull>>32);
		m_obj["Intelligent"].append(tmpObj);
	}
}

int FtpPlan::SaveAll(std::string strData)
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
				m_vec[i].FtpScHalfHour[xq][j] &= (~1);
				m_vec[i].FtpScHalfHour[xq][j] |= ull>>j&1;//0000000x
			}	
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Motion"][xq]["MotionLo"].asDouble();
			Hi = (unsigned int)obj[i]["Motion"][xq]["MotionHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].FtpScHalfHour[xq][j] &= (~2);
				m_vec[i].FtpScHalfHour[xq][j] |= (ull>>j&1)<<1;////000000x0
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Alarm"][xq]["AlarmLo"].asDouble();
			Hi = (unsigned int)obj[i]["Alarm"][xq]["AlarmHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].FtpScHalfHour[xq][j] &= (~4);
				m_vec[i].FtpScHalfHour[xq][j] |= (ull>>j&1)<<2;//00000x00
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Pir"][xq]["PirLo"].asDouble();
			Hi = (unsigned int)obj[i]["Pir"][xq]["PirHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].FtpScHalfHour[xq][j] &= (~8);
				m_vec[i].FtpScHalfHour[xq][j] |= (ull>>j&1)<<3;//x0000000
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentLo"].asDouble();
			Hi = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].FtpScHalfHour[xq][j] &= (~16);
				m_vec[i].FtpScHalfHour[xq][j] |= (ull>>j&1)<<4;//x0000000
			}
		}


		m_vec[i].StructSize = sizeof(RSNet_SoleFtpScheduleset_t);
	}

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgFtpScheduleParam;
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