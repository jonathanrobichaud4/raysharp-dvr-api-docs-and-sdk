#include "StdAfx.h"
#include "AlarmPlan.h"

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	AlarmPlan* pThis = (AlarmPlan*)userParam;
	RSNetNew_SoleAlarmOutScheduleset_t* AlarmSet_t = (RSNetNew_SoleAlarmOutScheduleset_t*)data;
	pThis->m_vec.push_back(*AlarmSet_t);
}

std::string AlarmPlan::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();
	
	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamAlarmOutScheduleset;
	param.Req = &req;
	param.ListParamSize = sizeof(RSNetNew_SoleAlarmOutScheduleset_t);
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

void AlarmPlan::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j]) & 1) << j;//0000000x
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm1"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>1 & 1) << j;//000000x0
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm2"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>2 & 1) << j;//00000x00
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm3"].append(obj);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>3 & 1) << j;//0000x000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm4"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>4 & 1) << j;//000x0000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm5"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>5 & 1) << j;//00x00000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm6"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>6 & 1) << j;//0x000000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm7"].append(obj);
	}
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].AlarmOutScHalfHour[i][j])>>7 & 1) << j;//x0000000
		}

		Json::Value obj(Json::objectValue);
		obj["AlarmLo"] = (unsigned int)ull;
		obj["AlarmHi"] = (unsigned int)(ull>>32);
		m_obj["Alarm8"].append(obj);
	}
}

int AlarmPlan::SaveAll(std::string strData)
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
		for(int k = 0;k < 8;++k)
		{
			char str[7] = {0};
			sprintf(str,"Alarm%d",k+1);
			for (int xq=0; xq<7; xq++)
			{
				Lo = (unsigned int)obj[i][(const char*)str][xq]["AlarmLo"].asDouble();
				Hi = (unsigned int)obj[i][(const char*)str][xq]["AlarmHi"].asDouble();
				stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
				for(int j=0; j<48; j++)
				{
					if(k == 0)
					{
						m_vec[i].AlarmOutScHalfHour[xq][j] = 0;
					}
					m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<k;//0000000x
				}
			}
		}

// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm1"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm1"][xq]["AlarmHi"].asDouble();
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] = 0;
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= ull>>j&1;//0000000x
// 			}
// 		}
// 
// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm2"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm2"][xq]["AlarmHi"].asDouble();
// 
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<1;//000000x0
// 			}
// 		}
// 
// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm3"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm3"][xq]["AlarmHi"].asDouble();
// 
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<2;//000000x0
// 			}
// 		}
// 
// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm4"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm4"][xq]["AlarmHi"].asDouble();
// 
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<3;//0000x000
// 			}
// 		}
// 
// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm5"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm5"][xq]["AlarmHi"].asDouble();
// 
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<4;//00x00000
// 			}
// 		}
// 
// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm6"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm6"][xq]["AlarmHi"].asDouble();
// 
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<5;//00x00000
// 			}
// 		}
// 
// 		for (int xq=0; xq<7; xq++)
// 		{
// 			Lo = (unsigned int)obj[i]["Alarm7"][xq]["AlarmLo"].asDouble();
// 			Hi = (unsigned int)obj[i]["Alarm7"][xq]["AlarmHi"].asDouble();
// 
// 			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
// 
// 			for(int j=0; j<48; j++)
// 			{
// 				m_vec[i].AlarmOutScHalfHour[xq][j] |= (ull>>j&1)<<6;//00x00000
// 			}
// 		}

		m_vec[i].StructSize = sizeof(RSNetNew_SoleEmailScheduleset_t);
	}

	///////////////////////////////////////////////////////////////////////

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamAlarmOutScheduleset;
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