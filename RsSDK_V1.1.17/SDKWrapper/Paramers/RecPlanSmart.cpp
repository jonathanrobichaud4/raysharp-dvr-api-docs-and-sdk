#include "StdAfx.h"
#include "RecPlanSmart.h"

RecPlanSmart::RecPlanSmart()
{
	bSmart = false;
}

static void RSNET_CALL soleParamCallback(void* data, void* userParam)
{
	RecPlanSmart* pThis = (RecPlanSmart*)userParam;
	RSNet_SoleIntelliRecSchedule_t* RecordSet_t = (RSNet_SoleIntelliRecSchedule_t*)data;
	pThis->m_vec.push_back(*RecordSet_t);
}

std::string RecPlanSmart::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIntelliRec;
	param.Req = &req;

	param.ParamSize = 0;
	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNet_SoleIntelliRecSchedule_t);
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

void RecPlanSmart::StructToJson(int n)
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
		tmpObj["SmartLo"] = (unsigned int)ull;
		tmpObj["SmartHi"] = (unsigned int)(ull>>32);
		m_obj["Smart"].append(tmpObj);
	}
}

int RecPlanSmart::SaveAll(std::string strData)
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
			Lo = (unsigned int)obj[i]["Smart"][xq]["SmartLo"].asDouble();
			Hi = (unsigned int)obj[i]["Smart"][xq]["SmartHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].HalfHour[xq][j] = 0;
				//m_vec[i].HalfHour[xq][j] |= ull>>j&1;
				for(int m=0;m<6;m++){
					m_vec[i].HalfHour[xq][j] |= (ull>>j&1)<<m;//兼容所有智能
				}
			}	
		}

		m_vec[i].StructSize = sizeof(RSNet_SoleIntelliRecSchedule_t);
	}

	///////////////////////////////////////////////////////////////////////
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamIntelliRec;
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