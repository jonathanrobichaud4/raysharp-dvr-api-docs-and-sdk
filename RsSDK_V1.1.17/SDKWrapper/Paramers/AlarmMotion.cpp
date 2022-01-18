#include "StdAfx.h"
#include "AlarmMotion.h"

AlarmMotion::AlarmMotion(void)
{
	AlarmOutNum = 0;
}

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	AlarmMotion* pThis = (AlarmMotion*)userParam;
	RSNet_SoleMotionSet_t* MotionSet = (RSNet_SoleMotionSet_t*)data;
	pThis->m_vec.push_back(*MotionSet);
}

static void RSNET_CALL SingleDataCallback(void* data, void* userParam)
{
	AlarmMotion* pThis = (AlarmMotion*)userParam;
	RSNet_SoleMotionSet_t* MotionSet = (RSNet_SoleMotionSet_t*)data;
	for(int i=0; i<pThis->m_vec.size(); i++)
	{
		if((MotionSet->ChannelMask >> i & 0x1) == 1)
			pThis->m_vec[i] = *MotionSet;
	}
}

std::string AlarmMotion::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();
	
	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamMotion;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleMotionSet_t);
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

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

std::string AlarmMotion::QueryOne(int n)
{
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamMotion;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleMotionSet_t);
	param.ListParamCallback = SingleDataCallback;
	param.UserParam = this;

	if (RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	StructToJson(n);

	//给Cover赋值
	//DataToCover_One(n);

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void AlarmMotion::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["Sensitivity"] = m_vec[n].Sensitivity;
	m_obj["ChnSwitch"] = m_vec[n].ChnSwitch;
	m_obj["SendEmail"] = m_vec[n].SendEmail;
	m_obj["BuzzerMooTime"] = m_vec[n].BuzzerMooTime;
	m_obj["RecordChannel"] = m_vec[n].RecordChannel;
	m_obj["RecordDelayTime"] = m_vec[n].RecordDelayTime;
	m_obj["Record"] = m_vec[n].Record;
	m_obj["ShowMessage"] = m_vec[n].ShowMessage;
	m_obj["FullScreen"] = m_vec[n].FullScreen;
	Json::Value tempRegionSetting(Json::arrayValue);
	for(int i = 0;i < 32;++i)
	{
		tempRegionSetting.append(m_vec[n].RegionSetting[i]);
	}
	m_obj["RegionSetting"] = tempRegionSetting;
	m_obj["MbRow"] = m_vec[n].MbRow;
	m_obj["MbCol"] = m_vec[n].MbCol;
	m_obj["AlarmOut"] = m_vec[n].AlarmOut;
	m_obj["AlarmOutTime"] = m_vec[n].AlarmOutTime;

	AlarmOutNum = m_pDevice->GetLoginRsp()->AlarmOutNum;
	for(int i=0; i<AlarmOutNum; ++i)
	{
		m_obj["AlarmOutManager"].append(m_vec[n].AlarmOutManager[i]);
	}
	for(int i = 0;i < 200;++i)
	{
		m_obj["BlockRegion"].append(m_vec[n].BlockRegion.RegionSetting3531[i]);
	}
	Json::Value tempMotionNum(Json::arrayValue);
	Json::Value tempRect(Json::arrayValue);
	Json::Value tempSensitivities(Json::arrayValue);
	for(int i = 0;i < 4;++i)
	{
		tempMotionNum.append(m_vec[n].RectRegion.MotionNum[i]);
		Json::Value obj(Json::objectValue);
		obj["x"] = m_vec[n].RectRegion.Rect[i].x;
		obj["y"] = m_vec[n].RectRegion.Rect[i].y;
		obj["w"] = m_vec[n].RectRegion.Rect[i].w;
		obj["h"] = m_vec[n].RectRegion.Rect[i].h;
		tempRect.append(obj);
		tempSensitivities.append(m_vec[n].RectRegion.Sensitivities[i]);
	}
	m_obj["RectRegion"]["MotionNum"] = tempMotionNum;
	m_obj["RectRegion"]["Rect"] = tempRect;
	m_obj["RectRegion"]["Sensitivities"] = tempSensitivities;
	m_obj["FtpLink"] = m_vec[n].FtpLink;
	m_obj["PushSwitch"] = m_vec[n].PushSwitch;
	m_obj["CloudNotify"] = m_vec[n].CloudNotify;
	m_obj["WirelessAlarmSensor"] = m_vec[n].WirelessAlarmSensor;
	m_obj["LlluminationRing"] = m_vec[n].LlluminationRing;
	m_obj["AudioAlert"] = m_vec[n].AudioAlert;
	m_obj["AudioSelect"] = m_vec[n].AudioSelect;
	m_obj["AlarmDurationTime"] = m_vec[n].AlarmDurationTime;
	m_obj["Pirflag"] = m_vec[n].Pirflag;
	m_obj["SensitivityExNight"] = m_vec[n].SensitivityExNight;
	m_obj["onlySDexit"] = m_vec[n].onlySDexit;
	m_obj["sendToFTP"] = m_vec[n].sendToFTP;
	m_obj["LightLinkage"] = m_vec[n].LightLinkage;
	m_obj["LoudSpeaker"] = m_vec[n].LoudSpeaker;
    m_obj["Distance"] = m_vec[n].Distance;
	m_obj["PageBit"] = m_vec[n].PageBit;
	m_obj["FtpVideoLink"] = m_vec[n].FtpVideoLink;
	m_obj["CloudPicUpload"] = m_vec[n].CloudPicUpload;
	m_obj["CloudVideoUpload"] = m_vec[n].CloudVideoUpload;
	m_obj["FTPUpload"] = m_vec[n].FTPUpload;

	for(int i=0; i<8; ++i)
	{
		m_obj["RecordChannel_EX"].append(m_vec[n].RecordChannel_EX[i]);
	}
	
	for (int i=0;i<3;++i)
	{
		Json::Value tempMotionmang(Json::arrayValue);
		for(int j=0;j<32;++j)
		{
			tempMotionmang.append(m_vec[n].AlarmOutManagerEx[i][j]);
			
		}
		m_obj["AlarmOutManagerEx"].append(tempMotionmang);
	}	
}

int AlarmMotion::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	//从网页传来的数据
	for(int i=0; i<obj.size(); i++)
	{
		m_vec[i].Sensitivity = obj[i]["Sensitivity"].asInt();
		m_vec[i].ChnSwitch = obj[i]["ChnSwitch"].asInt();
		m_vec[i].SendEmail = obj[i]["SendEmail"].asInt();
		m_vec[i].BuzzerMooTime = obj[i]["BuzzerMooTime"].asInt();
		m_vec[i].RecordChannel = (unsigned int)obj[i]["RecordChannel"].asDouble();
		m_vec[i].RecordDelayTime = obj[i]["RecordDelayTime"].asInt();
		m_vec[i].Record = obj[i]["Record"].asInt();
		m_vec[i].ShowMessage = obj[i]["ShowMessage"].asInt();
		m_vec[i].FullScreen = obj[i]["FullScreen"].asInt();
		for(int j = 0;j < obj[i]["RegionSetting"].size();++j)
		{
			m_vec[i].RegionSetting[j] = obj[i]["RegionSetting"][j].asUInt();
		}
		m_vec[i].AlarmOut = obj[i]["AlarmOut"].asInt();
		m_vec[i].AlarmOutTime = obj[i]["AlarmOutTime"].asInt();
		for (int j=0; j<AlarmOutNum; j++)
		{
			m_vec[i].AlarmOutManager[j] = obj[i]["AlarmOutManager"][j].asInt();
		}
		if(m_vec[i].MbRow == 200
			|| m_vec[i].MbRow == 201
			|| m_vec[i].MbRow == 202)
		{
			
			for(int j=0; j<4; j++)
			{
				m_vec[i].RectRegion.MotionNum[j] = obj[i]["RectRegion"]["MotionNum"][j].asInt();
				m_vec[i].RectRegion.Sensitivities[j] = obj[i]["RectRegion"]["Sensitivities"][j].asInt();
				m_vec[i].RectRegion.Rect[j].x = obj[i]["RectRegion"]["Rect"][j]["x"].asInt();
				m_vec[i].RectRegion.Rect[j].y = obj[i]["RectRegion"]["Rect"][j]["y"].asInt();
				m_vec[i].RectRegion.Rect[j].w = obj[i]["RectRegion"]["Rect"][j]["w"].asInt();
				m_vec[i].RectRegion.Rect[j].h = obj[i]["RectRegion"]["Rect"][j]["h"].asInt();
			}
		}
		else
		{
			for(int j = 0;j < obj[i]["BlockRegion"].size();++j)
			{
				m_vec[i].BlockRegion.RegionSetting3531[j] = obj[i]["BlockRegion"][j].asInt();
			}
		}
		m_vec[i].FtpLink = obj[i]["FtpLink"].asInt();
		m_vec[i].PushSwitch = obj[i]["PushSwitch"].asInt();
		m_vec[i].CloudNotify = obj[i]["CloudNotify"].asInt();
		m_vec[i].WirelessAlarmSensor = obj[i]["WirelessAlarmSensor"].asInt();
		m_vec[i].LlluminationRing = obj[i]["LlluminationRing"].asInt();
		m_vec[i].AudioAlert = obj[i]["AudioAlert"].asInt();
		m_vec[i].AudioSelect = obj[i]["AudioSelect"].asInt();
		m_vec[i].AlarmDurationTime = obj[i]["AlarmDurationTime"].asInt();
		m_vec[i].SensitivityExNight = obj[i]["SensitivityExNight"].asInt();
		m_vec[i].sendToFTP = obj[i]["sendToFTP"].asInt();
		m_vec[i].LightLinkage = obj[i]["LightLinkage"].asInt();
		m_vec[i].LoudSpeaker = obj[i]["LoudSpeaker"].asInt();
        m_vec[i].Distance = obj[i]["Distance"].asInt();
		m_vec[i].FtpVideoLink = obj[i]["FtpVideoLink"].asInt();
		m_vec[i].CloudVideoUpload = obj[i]["CloudVideoUpload"].asInt();
		m_vec[i].CloudPicUpload = obj[i]["CloudPicUpload"].asInt();
		m_vec[i].FTPUpload = obj[i]["FTPUpload"].asInt();
		for(int j = 0;j < 8;++j)
		{
			m_vec[i].RecordChannel_EX[j] = (unsigned int)obj[i]["RecordChannel_EX"][j].asDouble();
		}
		for (int j=0;j<3;++j)
		{
			for(int k=0;k<32;++k)
			{
				m_vec[i].AlarmOutManagerEx[j][k] = obj[i]["AlarmOutManagerEx"][j][k].asUInt();
			}
		}	

		m_vec[i].StructSize = sizeof(RSNet_SoleMotionSet_t);
	}

	//保存
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamMotion;
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