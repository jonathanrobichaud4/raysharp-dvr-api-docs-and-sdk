#include "StdAfx.h"
#include "RecPlan.h"

RecPlan::RecPlan()
{
	bSmart = false;
}

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	RecPlan* pThis = (RecPlan*)userParam;
	RSNet_SoleScheduleSet_t* RecordSet_t = (RSNet_SoleScheduleSet_t*)data;
	pThis->m_vec.push_back(*RecordSet_t);
}

std::string RecPlan::QueryAll(bool bDefault)
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

void RecPlan::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	m_obj["SmartScheduleEnable"] = m_vec[n].SmartScheduleEnable;
	m_obj["ScheduleMode"] = m_vec[n].ScheduleMode;
	m_obj["onlySDexit"] = m_vec[n].onlySDexit;
	m_obj["PageBit"] = m_vec[n].PageBit;

	Json::Value tmpObj(Json::objectValue);

	if (m_vec[n].SmartScheduleEnable != 0)//support smart 
	{
		for(int i=0; i<7; i++)
		{
			tmpObj["item"] = m_vec[n].SmartNormalResolution[i];
			m_obj["SmartNormalResolution"].append(tmpObj);

			tmpObj["item"] = m_vec[n].SmartAlarmResolution[i];
			m_obj["SmartAlarmResolution"].append(tmpObj);

			tmpObj["item"] = m_vec[n].SmartNormalHour[i];
			m_obj["SmartNormalHour"].append(tmpObj);

			tmpObj["item"] = m_vec[n].SmartAlarmHour[i];
			m_obj["SmartAlarmHour"].append(tmpObj);
		}

		bSmart = true;
	}

	for(int i=0; i<7; i++)
	{
		tmpObj["item"] = m_vec[n].SubMotionHour[i];
		m_obj["SubMotionHour"].append(tmpObj);

		tmpObj["item"] = m_vec[n].SubNormalHour[i];
		m_obj["SubNormalHour"].append(tmpObj);
	}

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
			ull |= (((unsigned long long)m_vec[n].HalfHourExt[i][j]) & 1) << j;
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["IntelligentLo"] = (unsigned int)ull;
		tmpObj["IntelligentHi"] = (unsigned int)(ull>>32);
		m_obj["Intelligent"].append(tmpObj);
	}
}

int RecPlan::SaveAll(std::string strData)
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
		m_vec[i].ScheduleMode = obj[i]["ScheduleMode"].asInt();

		if (bSmart && m_vec[i].ScheduleMode == RS_SmartScheduleMode)//smart mode
		{
			for (int xq=0; xq<7; xq++)
			{
				m_vec[i].SmartNormalResolution[xq] = obj[i]["SmartNormalResolution"][xq]["item"].asInt();
				m_vec[i].SmartAlarmResolution[xq] = obj[i]["SmartAlarmResolution"][xq]["item"].asInt();
				m_vec[i].SmartNormalHour[xq] = obj[i]["SmartNormalHour"][xq]["item"].asInt();
				m_vec[i].SmartAlarmHour[xq] = obj[i]["SmartAlarmHour"][xq]["item"].asInt();
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			m_vec[i].SubNormalHour[xq] = obj[i]["SubNormalHour"][xq]["item"].asInt();
			m_vec[i].SubMotionHour[xq] = obj[i]["SubMotionHour"][xq]["item"].asInt();
		}

		unsigned int Lo;
		unsigned int Hi;
		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Normal"][xq]["NormalLo"].asDouble();
			Hi = (unsigned int)obj[i]["Normal"][xq]["NormalHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] &= (~1);
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
				m_vec[i].HalfHour[xq][j] &= (~2);
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<1;////000000x0
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Alarm"][xq]["AlarmLo"].asDouble();
			Hi = (unsigned int)obj[i]["Alarm"][xq]["AlarmHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] &= (~4);
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
				m_vec[i].HalfHour[xq][j] &= (~128);
				m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<7;//x0000000
			}
		}

		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentLo"].asDouble();
			Hi = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHourExt[xq][j] &= (~1);
				m_vec[i].HalfHourExt[xq][j] |= (ull>>j&1);//x0000000
			}
		}


		m_vec[i].StructSize = sizeof(RSNet_SoleScheduleSet_t);
		m_vec[i].SmartScheduleEnable = bSmart;
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