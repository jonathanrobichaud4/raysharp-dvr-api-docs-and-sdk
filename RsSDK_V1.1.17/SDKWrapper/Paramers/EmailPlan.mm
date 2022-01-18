#include "StdAfx.h"
#include "EmailPlan.h"

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	EmailPlan* pThis = (EmailPlan*)userParam;
	RSNetNew_SoleEmailScheduleset_t* EmailSet_t = (RSNetNew_SoleEmailScheduleset_t*)data;
	pThis->m_vec.push_back(*EmailSet_t);
}

static void RSNET_CALL oneParamCallback(void* param, void* userParam)
{
	EmailPlan* pThis = (EmailPlan*)userParam;
	RSNetNew_EmailScheduleset_t* emailEventScheduleSet = (RSNetNew_EmailScheduleset_t*)param;
	pThis->m_Email = *emailEventScheduleSet;
}

std::string EmailPlan::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Email, '\0', sizeof(RSNetNew_EmailScheduleset_t));
	m_vec.clear();
	
	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamModifyEmailSchedule;
	param.Req = &req;

	param.ParamSize = sizeof(RSNetNew_EmailScheduleset_t);;
	param.ParamCallback = oneParamCallback;

	param.ListParamSize = sizeof(RSNetNew_SoleEmailScheduleset_t);
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

void EmailPlan::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j]) & 1) << j;//0000000x
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
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>1 & 1) << j;//000000x0
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
			ull |= (((unsigned long long)m_Email.EventScHalfHour[i][j]) & 1) << j;
		}

		Json::Value obj(Json::objectValue);
		obj["EventLo"] = (unsigned int)ull;
		obj["EventHi"] = (unsigned int)(ull>>32);
		m_obj["Event"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>2 & 1) << j;
		}

		Json::Value obj(Json::objectValue);
		obj["EventLo"] = (unsigned int)ull;
		obj["EventHi"] = (unsigned int)(ull>>32);
		m_obj["ZIPEvent"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>3 & 1) << j;//0000x000
		}

		Json::Value obj(Json::objectValue);
		obj["IntelliLo"] = (unsigned int)ull;
		obj["IntelliHi"] = (unsigned int)(ull>>32);
		m_obj["Intelli"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>4 & 1) << j;//0000x000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["ZIPAlarm1"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>5 & 1) << j;//0000x000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["ZIPAlarm2"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>6 & 1) << j;//0000x000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["ZIPAlarm3"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].EmailScHalfHour[i][j])>>5 & 1) << j;//00x00000
		}

		Json::Value obj(Json::objectValue);
		obj["PirLo"] = (unsigned int)ull;
		obj["PirHi"] = (unsigned int)(ull>>32);
		m_obj["Pir"].append(obj);
	}
}

int EmailPlan::SaveAll(std::string strData)
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
			Lo = (unsigned int)obj[i]["Motion"][xq]["MotionLo"].asDouble();
			Hi = (unsigned int)obj[i]["Motion"][xq]["MotionHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] = 0;
				m_vec[i].EmailScHalfHour[xq][j] |= ull>>j&1;//0000000x
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Alarm"][xq]["AlarmLo"].asDouble();
			Hi = (unsigned int)obj[i]["Alarm"][xq]["AlarmHi"].asDouble();

			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] |= (ull>>j&1)<<1;//000000x0
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["ZIPEvent"][xq]["EventLo"].asDouble();
			Hi = (unsigned int)obj[i]["ZIPEvent"][xq]["EventHi"].asDouble();

			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] |= (ull>>j&1)<<2;//000000x0
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Intelli"][xq]["IntelliLo"].asDouble();
			Hi = (unsigned int)obj[i]["Intelli"][xq]["IntelliHi"].asDouble();

			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] |= (ull>>j&1)<<3;//0000x000
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["ZIPAlarm1"][xq]["AlarmLo"].asDouble();
			Hi = (unsigned int)obj[i]["ZIPAlarm1"][xq]["AlarmHi"].asDouble();

			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] |= (ull>>j&1)<<4;//00x00000
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["ZIPAlarm3"][xq]["AlarmLo"].asDouble();
			Hi = (unsigned int)obj[i]["ZIPAlarm3"][xq]["AlarmHi"].asDouble();

			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] |= (ull>>j&1)<<6;//00x00000
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Pir"][xq]["PirLo"].asDouble();
			Hi = (unsigned int)obj[i]["Pir"][xq]["PirHi"].asDouble();

			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].EmailScHalfHour[xq][j] |= (ull>>j&1)<<5;//00x00000
			}
		}

		m_vec[i].StructSize = sizeof(RSNetNew_SoleEmailScheduleset_t);
	}

	//通道无关-不循环，只看0通道
	{
		unsigned int Lo;
		unsigned int Hi;
		int i = 0;

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Event"][xq]["EventLo"].asDouble();
			Hi = (unsigned int)obj[i]["Event"][xq]["EventHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_Email.EventScHalfHour[xq][j] = 0;
				m_Email.EventScHalfHour[xq][j] |= ull>>j&1;
			}
		}
		m_Email.StructSize = sizeof(RSNetNew_EmailScheduleset_t);
	}

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamModifyEmailSchedule;
	param.Param = &m_Email;
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