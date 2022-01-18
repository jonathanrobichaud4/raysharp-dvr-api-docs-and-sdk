#include "StdAfx.h"
#include "SoundAlarm.h"

SoundAlarm::SoundAlarm(void)
{
	AlarmOutNum = 0;
}

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	SoundAlarm* pThis = (SoundAlarm*)userParam;
	RSNet_SoleSoundDetectionParam_t* SoleSoundAlarmSet = (RSNet_SoleSoundDetectionParam_t*)data;
	pThis->m_vec.push_back(*SoleSoundAlarmSet);
}

std::string SoundAlarm::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgSoundAlarmParam;
	
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleSoundDetectionParam_t);
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

void SoundAlarm::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["AudioAlarmSwitch"] = m_vec[n].AudioAlarmSwitch;
	m_obj["RiseSwitch"] = m_vec[n].RiseSwitch;
	m_obj["SoundIntensity"] = m_vec[n].SoundIntensity;
	m_obj["RiseSensitivity"] = m_vec[n].RiseSensitivity;
	m_obj["DeclineSensitivity"] = m_vec[n].DeclineSensitivity;
	m_obj["DeclineSwitch"] = m_vec[n].DeclineSwitch;
	m_obj["AlarmOut"] = m_vec[n].AlarmOut;
	m_obj["AlarmOutTime"] = m_vec[n].AlarmOutTime;
	m_obj["RecordSwitch"] = m_vec[n].RecordSwitch;
	m_obj["RecordDelayTime"] = m_vec[n].RecordDelayTime;
	m_obj["EmailLink"] = m_vec[n].EmailLink;
	m_obj["FtpUploadSwitch"] = m_vec[n].FtpUploadSwitch;
	m_obj["AudioInputEnable"] = m_vec[n].AudioInputEnable;
	m_obj["BuzzerMooTime"] = m_vec[n].BuzzerMooTime;
	m_obj["ShowMessage"] = m_vec[n].ShowMessage;
	m_obj["FullScreen"] = m_vec[n].FullScreen;
	for(int i=0; i<8; i++)
	{
		m_obj["RecordChannel"].append(m_vec[n].RecordChannel[i]);
	}
	AlarmOutNum = m_pDevice->GetLoginRsp()->AlarmOutNum;
	for(int i=0; i<AlarmOutNum; ++i)
	{
		m_obj["AlarmOutManager"].append(m_vec[n].AlarmOutManager[i]);
	}

	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].TimeSchedule[i][j]) & 1) << j;//0000000x
		}

		Json::Value obj(Json::objectValue);
		obj["SoundLo"] = (unsigned int)ull;
		obj["SoundHi"] = (unsigned int)(ull>>32);
		m_obj["Sound"].append(obj);
	}
	m_obj["FtpVideoLink"] = m_vec[n].FtpVideoLink;
	m_obj["CloudPicUpload"] = m_vec[n].CloudPicUpload;
	m_obj["CloudVideoUpload"] = m_vec[n].CloudVideoUpload;
}

int SoundAlarm::SaveAll(std::string strData)
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
		m_vec[i].AudioAlarmSwitch = obj[i]["AudioAlarmSwitch"].asInt();
		m_vec[i].RiseSwitch = obj[i]["RiseSwitch"].asInt();
		m_vec[i].SoundIntensity = obj[i]["SoundIntensity"].asInt();
		m_vec[i].RiseSensitivity = obj[i]["RiseSensitivity"].asInt();
		m_vec[i].DeclineSensitivity = obj[i]["DeclineSensitivity"].asInt();
		m_vec[i].DeclineSwitch = obj[i]["DeclineSwitch"].asInt();
		m_vec[i].AlarmOut = obj[i]["AlarmOut"].asInt();
		m_vec[i].AlarmOutTime = obj[i]["AlarmOutTime"].asInt();
		m_vec[i].RecordSwitch = obj[i]["RecordSwitch"].asInt();
		m_vec[i].RecordDelayTime = obj[i]["RecordDelayTime"].asInt();
		m_vec[i].EmailLink = obj[i]["EmailLink"].asInt();
		m_vec[i].FtpUploadSwitch = obj[i]["FtpUploadSwitch"].asInt();
		m_vec[i].AudioInputEnable = obj[i]["AudioInputEnable"].asInt();
        m_vec[i].BuzzerMooTime = obj[i]["BuzzerMooTime"].asInt();
		m_vec[i].ShowMessage = obj[i]["ShowMessage"].asInt();
		m_vec[i].FullScreen = obj[i]["FullScreen"].asInt();

		for(int j=0; j<8; j++)
		{
			m_vec[i].RecordChannel[j] = (unsigned int)obj[i]["RecordChannel"][j].asDouble();
		}
		for (int j=0; j<AlarmOutNum; j++)
		{
			m_vec[i].AlarmOutManager[j] = obj[i]["AlarmOutManager"][j].asInt();
		}

		unsigned int Lo;
		unsigned int Hi;
		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Sound"][xq]["SoundLo"].asDouble();
			Hi = (unsigned int)obj[i]["Sound"][xq]["SoundHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].TimeSchedule[xq][j] = 0;
				m_vec[i].TimeSchedule[xq][j] |= ull>>j&1;//0000000x
			}
		}
		m_vec[i].FtpVideoLink = obj[i]["FtpVideoLink"].asInt();
		m_vec[i].CloudPicUpload = obj[i]["CloudPicUpload"].asInt();
		m_vec[i].CloudVideoUpload = obj[i]["CloudVideoUpload"].asInt();

		m_vec[i].StructSize = sizeof(RSNet_SoleSoundDetectionParam_t);
	}

	//保存
	RSNetSetParamParam param;
	ZeroMemory(&param, sizeof(param));

	param.ParamType = MsgSoundAlarmParam;

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