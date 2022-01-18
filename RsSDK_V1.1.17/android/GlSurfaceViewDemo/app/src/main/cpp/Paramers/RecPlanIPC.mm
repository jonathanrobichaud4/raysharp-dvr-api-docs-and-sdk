#include "StdAfx.h"
#include "RecPlanIPC.h"

RecPlanIPC::RecPlanIPC()
{
	bSmart = false;
}

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	RecPlanIPC* pThis = (RecPlanIPC*)userParam;
	RSNet_SoleScheduleSet_t* RecordSet_t = (RSNet_SoleScheduleSet_t*)data;
	pThis->m_vec.push_back(*RecordSet_t);
}

std::string RecPlanIPC::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamSchedule;
	param.Req = &req;

	param.ParamSize = 0;
	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNet_SoleScheduleSet_t);
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

void RecPlanIPC::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	Json::Value tmpObj(Json::objectValue);
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j]) & 1) << j;
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
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>1 & 1) << j;
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
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>2 & 1) << j;
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
			ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>7 & 1) << j;
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
			ull |= (((unsigned long long)m_vec[n].HalfHourExt[i][j])>>6 & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["SoundLo"] = (unsigned int)ull;
		tmpObj["SoundHi"] = (unsigned int)(ull>>32);
		m_obj["Sound"].append(tmpObj);
	}
}

int RecPlanIPC::SaveAll(std::string strData)
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
			Lo = (unsigned int)obj[i]["NormalLo"][xq].asDouble();
			Hi = (unsigned int)obj[i]["NormalHi"][xq].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] = 0;
				m_vec[i].HalfHour[xq][j] |= ull>>j&1;
			}	
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["MotionLo"][xq].asDouble();
			Hi = (unsigned int)obj[i]["MotionHi"][xq].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<1;
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["AlarmLo"][xq].asDouble();
			Hi = (unsigned int)obj[i]["AlarmHi"][xq].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<2;
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["PirLo"][xq].asDouble();
			Hi = (unsigned int)obj[i]["PirHi"][xq].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<7;
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["SoundLo"][xq].asDouble();
			Hi = (unsigned int)obj[i]["SoundHi"][xq].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHourExt[xq][j] = 0;
				m_vec[i].HalfHourExt[xq][j] |= (ull>>j&1)<<6;
			}
		}

		m_vec[i].StructSize = sizeof(RSNet_SoleScheduleSet_t);
	}

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamSchedule;
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