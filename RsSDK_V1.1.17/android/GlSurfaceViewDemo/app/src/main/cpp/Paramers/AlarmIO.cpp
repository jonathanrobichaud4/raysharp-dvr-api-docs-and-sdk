#include "StdAfx.h"
#include "AlarmIO.h"

AlarmIO::AlarmIO(void)
{
	AlarmOutNum = 0;
}

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	AlarmIO* pThis = (AlarmIO*)userParam;
	RSNet_SoleIOAlarmSet_t* SoleIOAlarmSet = (RSNet_SoleIOAlarmSet_t*)data;
	pThis->m_vec.push_back(*SoleIOAlarmSet);
}

std::string AlarmIO::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	if(m_pDevice->GetDeviceType() == 4){
		param.ParamType = MsgParamIpcIOAlarm;//531
	}else{
		param.ParamType = MsgParamIOAlarm;//518
	}
	
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleIOAlarmSet_t);
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;

	if(isDefault)
	{
		if (!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
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

void AlarmIO::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	AlarmOutNum = m_pDevice->GetLoginRsp()->AlarmOutNum;
	if(AlarmOutNum > 1)
	{
		for(int i=0; i<AlarmOutNum; ++i)
		{
			m_obj["AlarmOutManager"].append(m_vec[n].AlarmOutManager[i]);
		}
	}

	for(int i=0; i<8; ++i)
	{
		m_obj["RecordChannel_EX"].append(m_vec[n].RecordChannel_EX[i]);
	}

	m_obj["AlarmOut"] = m_vec[n].AlarmOut;
	m_obj["AlarmOutTime"] = m_vec[n].AlarmOutTime;
	m_obj["BuzzerMooTime"] = m_vec[n].BuzzerMooTime;
	m_obj["FullScreen"] = m_vec[n].FullScreen;
	m_obj["Record"] = m_vec[n].Record;
	m_obj["IoAlarmSet"] = m_vec[n].IoAlarmSet;
	m_obj["RecordChannel"] = m_vec[n].RecordChannel;
	m_obj["RecordDelayTime"] = m_vec[n].RecordDelayTime;
	m_obj["SendEmail"] = m_vec[n].SendEmail;
	m_obj["ShowMessage"] = m_vec[n].ShowMessage;
	m_obj["AlarmIO"] = m_vec[n].AlarmIO;
	m_obj["StructSize"] = m_vec[n].StructSize;
	m_obj["FtpLink"] = m_vec[n].FtpLink;
	m_obj["PushSwitch"] = m_vec[n].PushSwitch;
	m_obj["c2CloudNotify"] = m_vec[n].UrmetCloudNotify;
	m_obj["sendToFTP"] = m_vec[n].sendToFTP;
	m_obj["FtpVideoLink"] = m_vec[n].FtpVideoLink;
	m_obj["CloudPicUpload"] = m_vec[n].CloudPicUpload;
	m_obj["CloudVideoUpload"] = m_vec[n].CloudVideoUpload;
	m_obj["FTPUpload"] = m_vec[n].FTPUpload;
}

int AlarmIO::SaveAll(std::string strData)
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
		m_vec[i].AlarmOut = obj[i]["AlarmOut"].asInt();
		m_vec[i].AlarmOutTime = obj[i]["AlarmOutTime"].asInt();
		m_vec[i].BuzzerMooTime = obj[i]["BuzzerMooTime"].asInt();
		m_vec[i].Record = obj[i]["Record"].asInt();
		m_vec[i].FullScreen = obj[i]["FullScreen"].asInt();
		m_vec[i].IoAlarmSet = obj[i]["IoAlarmSet"].asInt();
		m_vec[i].RecordChannel = (unsigned int)obj[i]["RecordChannel"].asDouble();
		m_vec[i].RecordDelayTime = obj[i]["RecordDelayTime"].asInt();
		m_vec[i].SendEmail = obj[i]["SendEmail"].asInt();
		m_vec[i].ShowMessage = obj[i]["ShowMessage"].asInt();
		m_vec[i].AlarmIO = obj[i]["AlarmIO"].asInt();
		m_vec[i].FtpLink = obj[i]["FtpLink"].asInt();
		m_vec[i].PushSwitch = obj[i]["PushSwitch"].asInt();
		if(!obj[i]["c2CloudNotify"].isNull()) {
			m_vec[i].UrmetCloudNotify = obj[i]["c2CloudNotify"].asInt();
		}
		m_vec[i].sendToFTP = obj[i]["sendToFTP"].asInt();

		for(int j=0; j<AlarmOutNum; j++)
		{
			m_vec[i].AlarmOutManager[j] = obj[i]["AlarmOutManager"][j].asInt();
		}

		for(int j=0; j<8; ++j)
		{
			m_vec[i].RecordChannel_EX[j] = obj[i]["RecordChannel_EX"][j].asInt();
		}
		m_vec[i].FtpVideoLink = obj[i]["FtpVideoLink"].asInt();
		m_vec[i].CloudPicUpload = obj[i]["CloudPicUpload"].asInt();
		m_vec[i].CloudVideoUpload = obj[i]["CloudVideoUpload"].asInt();
		m_vec[i].FTPUpload = obj[i]["FTPUpload"].asInt();
		m_vec[i].StructSize = sizeof(RSNet_SoleIOAlarmSet_t);
	}

	//保存
	RSNetSetParamParam param;
	ZeroMemory(&param, sizeof(param));

	if(m_pDevice->GetDeviceType() == 4){
		param.ParamType = MsgParamIpcIOAlarm;//531
	}else{
		param.ParamType = MsgParamIOAlarm;//518
	}

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