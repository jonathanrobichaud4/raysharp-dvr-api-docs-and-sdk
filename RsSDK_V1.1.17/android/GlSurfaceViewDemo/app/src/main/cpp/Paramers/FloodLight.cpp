#include "StdAfx.h"
#include "FloodLight.h"

FloodLight::FloodLight(void)
{
}

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	FloodLight* pThis = (FloodLight*)userParam;
	RSNet_SoleFloodLightSet_t* SoleFloodLightSet = (RSNet_SoleFloodLightSet_t*)data;
	pThis->m_vec.push_back(*SoleFloodLightSet);
}

std::string FloodLight::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgFloodLightParam;
	
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleFloodLightSet_t);
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

void FloodLight::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["BrightTime"] = m_vec[n].BrightTime;
	m_obj["FloodLightMode"] = m_vec[n].FloodLightMode;
	m_obj["FloodLightValue"] = m_vec[n].FloodLightValue;
	m_obj["FloodLightSwitch"] = m_vec[n].FloodLightSwitch;
	m_obj["StrobeFrequency"] = m_vec[n].StrobeFrequency;
	m_obj["Sensitivity"] = m_vec[n].Sensitivity;
	m_obj["AlarmOutTime"] = m_vec[n].AlarmOutTime;
	m_obj["RecordDelayTime"] = m_vec[n].RecordDelayTime;
	m_obj["EmailLink"] = m_vec[n].EmailLink;
	m_obj["RecordSwitch"] = m_vec[n].RecordSwitch;
	m_obj["AlarmOut"] = m_vec[n].AlarmOut;
	m_obj["SensitivityExNight"] = m_vec[n].SensitivityExNight;
	m_obj["loudAlarmLink"] = m_vec[n].loudAlarmLink;
	m_obj["SirenSwitch"] = m_vec[n].SirenSwitch;
	m_obj["SirenValue"] = m_vec[n].SirenValue;
	m_obj["SirenTime"] = m_vec[n].SirenTime;
	m_obj["ColorImageCtrl"] = m_vec[n].ColorImageCtrl;
	for(int i=0; i<7; i++)
	{
		unsigned long long ull = 0;
		for(int j=0; j<48; j++)
		{
			ull |= (((unsigned long long)m_vec[n].TimeSchedule[i][j]) & 1) << j;//0000000x
		}

		Json::Value obj(Json::objectValue);
		obj["FloodLo"] = (unsigned int)ull;
		obj["FloodHi"] = (unsigned int)(ull>>32);
		m_obj["Flood"].append(obj);
	}

	m_obj["MbRow"] = m_vec[n].MbRow;
	m_obj["MbCol"] = m_vec[n].MbCol;
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
}

int FloodLight::SaveAll(std::string strData)
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
		m_vec[i].BrightTime = obj[i]["BrightTime"].asInt();
		m_vec[i].FloodLightMode = obj[i]["FloodLightMode"].asInt();
		m_vec[i].FloodLightValue = obj[i]["FloodLightValue"].asInt();
		m_vec[i].FloodLightSwitch = obj[i]["FloodLightSwitch"].asInt();
		m_vec[i].StrobeFrequency = obj[i]["StrobeFrequency"].asInt();

		m_vec[i].Sensitivity = obj[i]["Sensitivity"].asInt();
		m_vec[i].AlarmOutTime = obj[i]["AlarmOutTime"].asInt();
		m_vec[i].RecordDelayTime = obj[i]["RecordDelayTime"].asInt();
		m_vec[i].EmailLink = obj[i]["EmailLink"].asInt();
		m_vec[i].RecordSwitch = obj[i]["RecordSwitch"].asInt();
		m_vec[i].AlarmOut = obj[i]["AlarmOut"].asInt();
		m_vec[i].SensitivityExNight = obj[i]["SensitivityExNight"].asInt();
		m_vec[i].loudAlarmLink = obj[i]["loudAlarmLink"].asInt();
		m_vec[i].SirenSwitch = obj[i]["SirenSwitch"].asInt();
		m_vec[i].SirenValue = obj[i]["SirenValue"].asInt();
		m_vec[i].SirenTime = obj[i]["SirenTime"].asInt();
		m_vec[i].ColorImageCtrl = obj[i]["ColorImageCtrl"].asInt();

		unsigned int Lo;
		unsigned int Hi;
		for (int xq=0; xq<7; xq++)
		{
			Lo = (unsigned int)obj[i]["Flood"][xq]["FloodLo"].asDouble();
			Hi = (unsigned int)obj[i]["Flood"][xq]["FloodHi"].asDouble();
			stdcUint64 ull = (((stdcUint64)Hi)<<32) | ((stdcUint64)Lo & 0xffffffff);

			for(int j=0; j<48; j++)
			{
				m_vec[i].TimeSchedule[xq][j] = 0;
				m_vec[i].TimeSchedule[xq][j] |= ull>>j&1;//0000000x
			}
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

		m_vec[i].StructSize = sizeof(RSNet_SoleFloodLightSet_t);
	}

	//保存
	RSNetSetParamParam param;
	ZeroMemory(&param, sizeof(param));

	param.ParamType = MsgFloodLightParam;

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