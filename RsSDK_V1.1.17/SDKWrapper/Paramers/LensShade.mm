#include "StdAfx.h"
#include "LensShade.h"

LensShade::LensShade(void)
{
	AlarmOutNum = 0;
}

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	LensShade * pThis = (LensShade*)userParam;
	RSNet_SoleODParam_t* SoleOD = (RSNet_SoleODParam_t*)data;
	pThis->m_vec.push_back(*SoleOD);
}

std::string LensShade::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	param.ParamType = MsgParamOD;

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleODParam_t);
	param.ListParamCallback = ParamDataCallback;
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

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

int LensShade::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	//处理数据
	for(int i = 0;i < obj.size();++i)
	{
		m_vec[i].EmailLink = obj[i]["EmailLink"].asInt();
		m_vec[i].ODSwitch = obj[i]["ODSwitch"].asInt();
		m_vec[i].Sensitivity = obj[i]["Sensitivity"].asInt();
		m_vec[i].FtpLink = obj[i]["FtpLink"].asInt();
		m_vec[i].Alarmout = obj[i]["Alarmout"].asInt();
		m_vec[i].LatchTime = obj[i]["LatchTime"].asInt();
		m_vec[i].sendToFTP = obj[i]["sendToFTP"].asInt();

		m_vec[i].RecordDelayTime = obj[i]["RecordDelayTime"].asInt();
		m_vec[i].ShowMessage = obj[i]["ShowMessage"].asInt();
		m_vec[i].FullScreen = obj[i]["FullScreen"].asInt();
		m_vec[i].RecordSwitch = obj[i]["RecordSwitch"].asInt();
		m_vec[i].BuzzerMooTime = obj[i]["BuzzerMooTime"].asInt();
		for(int j=0; j<8; j++)
		{
			m_vec[i].RecordChannel[j] = (unsigned int)obj[i]["RecordChannel"][j].asDouble();
		}
		for (int j=0; j<AlarmOutNum; j++)
		{
			m_vec[i].AlarmOutManager[j] = obj[i]["AlarmOutManager"][j].asInt();
		}
		m_vec[i].FtpVideoLink = obj[i]["FtpVideoLink"].asInt();
		m_vec[i].CloudPicUpload = obj[i]["CloudPicUpload"].asInt();
		m_vec[i].CloudVideoUpload = obj[i]["CloudVideoUpload"].asInt();

		m_vec[i].StructSize = sizeof(RSNet_SoleODParam_t);
	}
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamOD;
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

void LensShade::StructToJson(int n)
{
	m_obj.clear();
	m_obj["EmailLink"] = m_vec[n].EmailLink;
	m_obj["ODSwitch"] = m_vec[n].ODSwitch;
	m_obj["Sensitivity"] = m_vec[n].Sensitivity;
	m_obj["FtpLink"] = m_vec[n].FtpLink;
	m_obj["Alarmout"] = m_vec[n].Alarmout;
	m_obj["LatchTime"] = m_vec[n].LatchTime;
	m_obj["sendToFTP"] = m_vec[n].sendToFTP;
	m_obj["RecordDelayTime"] = m_vec[n].RecordDelayTime;
	m_obj["ShowMessage"] = m_vec[n].ShowMessage;
	m_obj["FullScreen"] = m_vec[n].FullScreen;
	m_obj["RecordSwitch"] = m_vec[n].RecordSwitch;
	m_obj["BuzzerMooTime"] = m_vec[n].BuzzerMooTime;
	for(int i=0; i<8; i++)
	{
		m_obj["RecordChannel"].append(m_vec[n].RecordChannel[i]);
	}
	AlarmOutNum = m_pDevice->GetLoginRsp()->AlarmOutNum;
	for(int i=0; i<AlarmOutNum; ++i)
	{
		m_obj["AlarmOutManager"].append(m_vec[n].AlarmOutManager[i]);
	}
	m_obj["FtpVideoLink"] = m_vec[n].FtpVideoLink;
	m_obj["CloudPicUpload"] = m_vec[n].CloudPicUpload;
	m_obj["CloudVideoUpload"] = m_vec[n].CloudVideoUpload;
}
