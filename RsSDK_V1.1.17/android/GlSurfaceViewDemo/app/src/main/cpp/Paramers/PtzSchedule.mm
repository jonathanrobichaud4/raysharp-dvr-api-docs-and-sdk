#include "StdAfx.h"
#include "PtzSchedule.h"

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	PtzSchedule* pThis = (PtzSchedule*)userParam;
	RSNet_SolePTZScheduleSet_t* PtzSet_t = (RSNet_SolePTZScheduleSet_t*)data;
	pThis->m_vec.push_back(*PtzSet_t);
}

std::string PtzSchedule::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();
	
	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgPtzScheduleParam;
	param.Req = &req;
	param.ListParamSize = sizeof(RSNet_SolePTZScheduleSet_t);
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

void PtzSchedule::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	for(int k=0;k<8;k++)//type
	{
		char str[7] = {0};
		sprintf(str,"PTZ%d",k);
		for(int i=0; i<7; i++)
		{
			unsigned long long ull = 0;
			for(int j=0; j<48; j++)
			{
				ull |= (((unsigned long long)m_vec[n].EventScHalfHour[i][j])>>k & 1) << j;
			}

			Json::Value obj(Json::objectValue);
			obj["PTZLo"] = (unsigned int)ull;
			obj["PTZHi"] = (unsigned int)(ull>>32);
			m_obj[(const char*)str].append(obj);
		}
	}

	m_obj["Recovertime"] = m_vec[n].Recovertime;
	m_obj["CruiseSwhich"] = m_vec[n].CruiseSwhich;
}

int PtzSchedule::SaveAll(std::string strData)
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
			sprintf(str,"PTZ%d",k);
			for (int xq=0; xq<7; xq++)
			{
				Lo = (unsigned int)obj[i][(const char*)str][xq]["PTZLo"].asDouble();
				Hi = (unsigned int)obj[i][(const char*)str][xq]["PTZHi"].asDouble();
				stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);
				for(int j=0; j<48; j++)
				{
					if(k == 0)
					{
						m_vec[i].EventScHalfHour[xq][j] = 0;
					}
					m_vec[i].EventScHalfHour[xq][j] |= (ull>>j&1)<<k;//0000000x
				}
			}
		}

		m_vec[i].Recovertime = obj[i]["Recovertime"].asInt();
		m_vec[i].CruiseSwhich = obj[i]["CruiseSwhich"].asInt();
		m_vec[i].StructSize = sizeof(RSNet_SolePTZScheduleSet_t);
	}

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgPtzScheduleParam;
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