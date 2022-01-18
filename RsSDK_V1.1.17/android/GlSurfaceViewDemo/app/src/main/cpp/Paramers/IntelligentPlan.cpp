#include "StdAfx.h"
#include "IntelligentPlan.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	IntelligentPlan* pThis = (IntelligentPlan*)userParam;
	RSNet_SoleScheduleSet_t* RecordSet_t = (RSNet_SoleScheduleSet_t*)data;
	pThis->m_vec.push_back(*RecordSet_t);
}

std::string IntelligentPlan::QueryAll(bool bDefault)
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
	param.ListParamCallback = AllDataCallback;

	param.UserParam = this;

	if(bDefault)
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

void IntelligentPlan::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			UINT uitype = m_pDevice->GetLoginRsp()->UiType;
			if(uitype == 50 || uitype == 52){//5.0根据pagecontrol来区分使用哪个变量
				if((m_pDevice->GetLoginRsp()->PageControl >> 3) & 1 == 1 &&
					(m_pDevice->GetLoginRsp()->PageControl >> 5) & 1 != 1)
				{
					ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>3 & 1) << j;
				}
				else
				{
					ull |= (((unsigned long long)m_vec[n].HalfHourExt[i][j]) & 0x1) << j;
				}
			}else{
				if(m_pDevice->GetDeviceType() == DEV_HDVR)
				{
					ull |= (((unsigned long long)m_vec[n].HalfHour[i][j])>>3 & 1) << j;
				}
				else
				{
					ull |= (((unsigned long long)m_vec[n].HalfHourExt[i][j]) & 0x1) << j;
				}
			}
		}

		Json::Value tmpObj(Json::objectValue);
		tmpObj["IntelligentLow"] = (unsigned int)ull;
		tmpObj["IntelligentHi"] = (unsigned int)(ull>>32);
		m_obj["Intelligent"].append(tmpObj);
	}
}

int IntelligentPlan::SaveAll(std::string strData)
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
			Lo = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentLow"].asDouble();
			Hi = (unsigned int)obj[i]["Intelligent"][xq]["IntelligentHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				UINT uitype = m_pDevice->GetLoginRsp()->UiType;
				if(uitype == 50 || uitype == 52){//5.0根据pagecontrol来区分使用哪个变量
					if((m_pDevice->GetLoginRsp()->PageControl >> 3) & 1 == 1 &&
						(m_pDevice->GetLoginRsp()->PageControl >> 5) & 1 != 1){
							m_vec[i].HalfHour[xq][j] &= ~(0x8);
							m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<3;
					}else{
						m_vec[i].HalfHourExt[xq][j] &= ~(0x01);
						m_vec[i].HalfHourExt[xq][j] |= (ull>>j&0x01);
					}
				}else{
					if(m_pDevice->GetDeviceType() == DEV_HDVR)
					{
						m_vec[i].HalfHour[xq][j] &= ~(0x8);
						m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<3;
					}
					else
					{
						m_vec[i].HalfHourExt[xq][j] &= ~(0x01);
						m_vec[i].HalfHourExt[xq][j] |= (ull>>j&0x01);
					}
				}
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