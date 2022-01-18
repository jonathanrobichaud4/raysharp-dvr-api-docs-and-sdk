#include "StdAfx.h"
#include "ImgCtrl.h"

static void RSNET_CALL ListParamCallback(void* data, void* userParam)
{
	ImgCtrl* pThis = (ImgCtrl*)userParam;
	RSNetNew_CameraSet_t* channelCam = (RSNetNew_CameraSet_t*)data;
	pThis->m_vec.push_back(*channelCam);
}

static void RSNET_CALL CamModeParamCallback(void* data, void* userParam)
{
	ImgCtrl* pThis = (ImgCtrl*)userParam;
	RSNetNew_CameraModeSet_t* channelCam = (RSNetNew_CameraModeSet_t*)data;
	pThis->m_vecMode.push_back(*channelCam);
}

static void RSNET_CALL ListParamSingleCallback(void* data, void* userParam)
{
	ImgCtrl* pThis = (ImgCtrl*)userParam;
	RSNetNew_CameraSet_t* channelCam = (RSNetNew_CameraSet_t*)data;
	for(int i = 0;i < pThis->m_vec.size(); ++i)
	{
		if((channelCam->ChannelMask >> i & 0x1) == 1)
			pThis->m_vec[i] = *channelCam;
	}
}

std::string ImgCtrl::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIPCImageSet;
	param.Req = &req;
	
	param.ListParamSize = sizeof(RSNetNew_CameraSet_t);
	param.ListParamCallback = ListParamCallback;
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

std::string ImgCtrl::QueryAll(std::string strData)
{
	//请求数据1
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	m_vecMode.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIPCCamearMode;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNetNew_CameraModeSet_t);
	param.ListParamCallback = CamModeParamCallback;
	param.UserParam = this;

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return strRet;
	}

	bool isDefault = obj["isDefault"].asBool();

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
	for(int i=0; i<m_vecMode.size(); i++)
	{
		CamModeStructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);

	return strRet;
}

std::string ImgCtrl::QueryOne(int n)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamIPCImageSet;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNetNew_CameraSet_t);
	param.ListParamCallback = ListParamSingleCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	StructToJson(n);

	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void ImgCtrl::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["IRCutMode"] = m_vec[n].IRCutMode;
	m_obj["IRCutDelay"] = m_vec[n].IRCutDelay;
	m_obj["IRCutSensitive"] = m_vec[n].IRCutSensitive;
	m_obj["Mirror"] = m_vec[n].Mirror;
	m_obj["Flip"] = m_vec[n].Flip;
	m_obj["Rotate"] = m_vec[n].Rotate;
	m_obj["BackLightMode"] = m_vec[n].BackLightMode;
	m_obj["BackLightLevel"] = m_vec[n].BackLightLevel;
	m_obj["R3dnrMode"] = m_vec[n].R3dnrMode;
	m_obj["R3dnrThreshTarget"] = m_vec[n].R3dnrThreshTarget;
	m_obj["DwdrMode"] = m_vec[n].DwdrMode;
	m_obj["DwdrStrength"] = m_vec[n].DwdrStrength;
	m_obj["GainControlMode"] = m_vec[n].GainControlMode;
	m_obj["WBMode"] = m_vec[n].WBMode;
	m_obj["Rgain"] = m_vec[n].Rgain;
	m_obj["Ggain"] = m_vec[n].Ggain;
	m_obj["Bgain"] = m_vec[n].Bgain;
	m_obj["ShutterMode"] = m_vec[n].ShutterMode;
	m_obj["eShutterSpeed"] = m_vec[n].eShutterSpeed;
	m_obj["FlickerCtrl"] = m_vec[n].FlickerCtrl;
	m_obj["DefogMode"] = m_vec[n].DefogMode;
	m_obj["DefogStrength"] = m_vec[n].DefogStrength;
	m_obj["IRISMode"] = m_vec[n].IRISMode;
	m_obj["autoFocus"] = m_vec[n].autoFocus;
	m_obj["LEDEnable"] = m_vec[n].LEDEnable;
	m_obj["HideRotate"] = m_vec[n].HideRotate;
	m_obj["GainSwitch"] = m_vec[n].GainSwitch;
	m_obj["ColorGain"] = m_vec[n].ColorGain;
	m_obj["BrightGain"] = m_vec[n].BrightGain;
	m_obj["R2dnrMode"] = m_vec[n].R2dnrMode;
	m_obj["DefogFakeLottery"] = m_vec[n].DefogFakeLottery;
	m_obj["BackLightZone"] = m_vec[n].BackLightZone;
	m_obj["AgcMode"] = m_vec[n].AgcMode;
	m_obj["AntiShakeEnable"] = m_vec[n].AntiShakeEnable;
	m_obj["AntiShakeLevel"] = m_vec[n].AntiShakeLevel;
	m_obj["AntiShakeLevelFlag"] = m_vec[n].AntiShakeLevelFlag;
	m_obj["BackLightLevelCheck"] = m_vec[n].BackLightLevelCheck;
	m_obj["WDRFlag"] = m_vec[n].WDRFlag;
	m_obj["HLCSwitch"] = m_vec[n].HLCSwitch;
	m_obj["HLCStrength"] = m_vec[n].HLCStrength;

	Json::Value Stime(Json::objectValue);
	Stime["Hour"] = m_vec[n].StartTime.Hour;
	Stime["Minute"] = m_vec[n].StartTime.Minute;
	Stime["Second"] = m_vec[n].StartTime.Second;
	m_obj["StartTime"] = Stime;

	Json::Value Etime(Json::objectValue);
	Etime["Hour"] = m_vec[n].EndTime.Hour;
	Etime["Minute"] = m_vec[n].EndTime.Minute;
	Etime["Second"] = m_vec[n].EndTime.Second;
	m_obj["EndTime"] = Etime;
}

void ImgCtrl::CamModeStructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	m_obj["mode"] = m_vecMode[n].mode;

	Json::Value data(Json::objectValue);
	Json::FastWriter writer;
	for (int i=0;i<3;i++)
	{
		data["IRCutMode"] = m_vecMode[n].cameraSet[i].IRCutMode;
		data["IRCutDelay"] = m_vecMode[n].cameraSet[i].IRCutDelay;
		data["IRCutSensitive"] = m_vecMode[n].cameraSet[i].IRCutSensitive;
		data["Mirror"] = m_vecMode[n].cameraSet[i].Mirror;
		data["Flip"] = m_vecMode[n].cameraSet[i].Flip;
		data["Rotate"] = m_vecMode[n].cameraSet[i].Rotate;
		data["BackLightMode"] = m_vecMode[n].cameraSet[i].BackLightMode;
		data["BackLightLevel"] = m_vecMode[n].cameraSet[i].BackLightLevel;
		data["R3dnrMode"] = m_vecMode[n].cameraSet[i].R3dnrMode;
		data["R3dnrThreshTarget"] = m_vecMode[n].cameraSet[i].R3dnrThreshTarget;
		data["DwdrMode"] = m_vecMode[n].cameraSet[i].DwdrMode;
		data["DwdrStrength"] = m_vecMode[n].cameraSet[i].DwdrStrength;
		data["GainControlMode"] = m_vecMode[n].cameraSet[i].GainControlMode;
		data["WBMode"] = m_vecMode[n].cameraSet[i].WBMode;
		data["Rgain"] = m_vecMode[n].cameraSet[i].Rgain;
		data["Ggain"] = m_vecMode[n].cameraSet[i].Ggain;
		data["Bgain"] = m_vecMode[n].cameraSet[i].Bgain;
		data["ShutterMode"] = m_vecMode[n].cameraSet[i].ShutterMode;
		data["eShutterSpeed"] = m_vecMode[n].cameraSet[i].eShutterSpeed;
		data["FlickerCtrl"] = m_vecMode[n].cameraSet[i].FlickerCtrl;
		data["DefogMode"] = m_vecMode[n].cameraSet[i].DefogMode;
		data["DefogStrength"] = m_vecMode[n].cameraSet[i].DefogStrength;
		data["IRISMode"] = m_vecMode[n].cameraSet[i].IRISMode;
		data["autoFocus"] = m_vecMode[n].cameraSet[i].autoFocus;
		data["LEDEnable"] = m_vecMode[n].cameraSet[i].LEDEnable;
		data["HideRotate"] = m_vecMode[n].cameraSet[i].HideRotate;
		data["GainSwitch"] = m_vecMode[n].cameraSet[i].GainSwitch;
		data["ColorGain"] = m_vecMode[n].cameraSet[i].ColorGain;
		data["BrightGain"] = m_vecMode[n].cameraSet[i].BrightGain;
		data["R2dnrMode"] = m_vecMode[n].cameraSet[i].R2dnrMode;
		data["DefogFakeLottery"] = m_vecMode[n].cameraSet[i].DefogFakeLottery;
		data["BackLightZone"] = m_vecMode[n].cameraSet[i].BackLightZone;
		data["AgcMode"] = m_vecMode[n].cameraSet[i].AgcMode;
		data["AntiShakeEnable"] = m_vecMode[n].cameraSet[i].AntiShakeEnable;
		data["AntiShakeLevel"] = m_vecMode[n].cameraSet[i].AntiShakeLevel;
		data["AntiShakeLevelFlag"] = m_vecMode[n].cameraSet[i].AntiShakeLevelFlag;
		data["BackLightLevelCheck"] = m_vecMode[n].cameraSet[i].BackLightLevelCheck;
		data["WDRFlag"] = m_vecMode[n].cameraSet[i].WDRFlag;
		data["HLCSwitch"] = m_vecMode[n].cameraSet[i].HLCSwitch;
		data["HLCStrength"] = m_vecMode[n].cameraSet[i].HLCStrength;

		Json::Value time(Json::objectValue);
		time["Hour"] = m_vecMode[n].cameraSet[i].StartTime.Hour;
		time["Minute"] = m_vecMode[n].cameraSet[i].StartTime.Minute;
		time["Second"] = m_vecMode[n].cameraSet[i].StartTime.Second;
		data["StartTime"] = time;

		time["Hour"] = m_vecMode[n].cameraSet[i].EndTime.Hour;
		time["Minute"] = m_vecMode[n].cameraSet[i].EndTime.Minute;
		time["Second"] = m_vecMode[n].cameraSet[i].EndTime.Second;
		data["EndTime"] = time;

		m_obj["item"].append(data);
	}
}

//保存
int ImgCtrl::SaveAll(std::string strData)
{	
	int ret = false;
	if(strData == "null"){
		return ret;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return ret;
	}

	bool isCamMode = false;
	int i = 0;
	if (!obj[i]["mode"].isNull())
	{
		isCamMode = true;
	}

	if (isCamMode)
	{
		int sel = obj[i]["ch"].asInt();
		if(sel >= m_vecMode.size() || m_vecMode.size() <= 0)
			return ret;

		m_vecMode[sel].mode = obj[i]["mode"].asInt();
		for(int i=0;i<3;i++)
		{
			m_vecMode[sel].cameraSet[i].IRCutMode = obj[sel]["item"][i]["IRCutMode"].asInt();
			m_vecMode[sel].cameraSet[i].IRCutSensitive = obj[sel]["item"][i]["IRCutSensitive"].asInt();
			m_vecMode[sel].cameraSet[i].IRCutDelay = obj[sel]["item"][i]["IRCutDelay"].asInt();
			m_vecMode[sel].cameraSet[i].Flip = obj[sel]["item"][i]["Flip"].asInt();
			m_vecMode[sel].cameraSet[i].Mirror = obj[sel]["item"][i]["Mirror"].asInt();
			m_vecMode[sel].cameraSet[i].BackLightMode = obj[sel]["item"][i]["BackLightMode"].asInt();
			m_vecMode[sel].cameraSet[i].BackLightLevel = obj[sel]["item"][i]["BackLightLevel"].asInt();
			m_vecMode[sel].cameraSet[i].R3dnrMode = obj[sel]["item"][i]["R3dnrMode"].asInt();
			m_vecMode[sel].cameraSet[i].R3dnrThreshTarget = obj[sel]["item"][i]["R3dnrThreshTarget"].asInt();
			m_vecMode[sel].cameraSet[i].DwdrMode = obj[sel]["item"][i]["DwdrMode"].asInt();
			m_vecMode[sel].cameraSet[i].DwdrStrength = obj[sel]["item"][i]["DwdrStrength"].asInt();
			m_vecMode[sel].cameraSet[i].GainControlMode = obj[sel]["item"][i]["GainControlMode"].asInt();
			m_vecMode[sel].cameraSet[i].WBMode = obj[sel]["item"][i]["WBMode"].asInt();
			m_vecMode[sel].cameraSet[i].Rgain = obj[sel]["item"][i]["Rgain"].asInt();
			m_vecMode[sel].cameraSet[i].Ggain = obj[sel]["item"][i]["Ggain"].asInt();
			m_vecMode[sel].cameraSet[i].Bgain = obj[sel]["item"][i]["Bgain"].asInt();
			m_vecMode[sel].cameraSet[i].ShutterMode = obj[sel]["item"][i]["ShutterMode"].asInt();
			m_vecMode[sel].cameraSet[i].eShutterSpeed = obj[sel]["item"][i]["eShutterSpeed"].asInt();
			m_vecMode[sel].cameraSet[i].FlickerCtrl = obj[sel]["item"][i]["FlickerCtrl"].asInt();
			m_vecMode[sel].cameraSet[i].DefogMode = obj[sel]["item"][i]["DefogMode"].asInt();
			m_vecMode[sel].cameraSet[i].DefogStrength = obj[sel]["item"][i]["DefogStrength"].asInt();
			m_vecMode[sel].cameraSet[i].Rotate = obj[sel]["item"][i]["Rotate"].asInt();
			m_vecMode[sel].cameraSet[i].IRISMode = obj[sel]["item"][i]["IRISMode"].asInt();
			m_vecMode[sel].cameraSet[i].autoFocus = obj[sel]["item"][i]["autoFocus"].asInt();
			m_vecMode[sel].cameraSet[i].LEDEnable = obj[sel]["item"][i]["LEDEnable"].asInt();
			m_vecMode[sel].cameraSet[i].StartTime.Hour = obj[sel]["item"][i]["StartTime"]["Hour"].asInt();
			m_vecMode[sel].cameraSet[i].StartTime.Minute = obj[sel]["item"][i]["StartTime"]["Minute"].asInt();
			m_vecMode[sel].cameraSet[i].EndTime.Hour = obj[sel]["item"][i]["EndTime"]["Hour"].asInt();
			m_vecMode[sel].cameraSet[i].EndTime.Minute = obj[sel]["item"][i]["EndTime"]["Minute"].asInt();
			m_vecMode[sel].cameraSet[i].GainSwitch = obj[sel]["item"][i]["GainSwitch"].asInt();
			m_vecMode[sel].cameraSet[i].ColorGain = obj[sel]["item"][i]["ColorGain"].asInt();
			m_vecMode[sel].cameraSet[i].BrightGain = obj[sel]["item"][i]["BrightGain"].asInt();
			m_vecMode[sel].cameraSet[i].R2dnrMode = obj[sel]["item"][i]["R2dnrMode"].asInt();
			m_vecMode[sel].cameraSet[i].DefogFakeLottery = obj[sel]["item"][i]["DefogFakeLottery"].asInt();
			m_vecMode[sel].cameraSet[i].BackLightZone = obj[sel]["item"][i]["BackLightZone"].asInt();
			m_vecMode[sel].cameraSet[i].AntiShakeEnable = obj[sel]["item"][i]["AntiShakeEnable"].asInt();
			m_vecMode[sel].cameraSet[i].AntiShakeLevel = obj[sel]["item"][i]["AntiShakeLevel"].asInt();
			m_vecMode[sel].cameraSet[i].HLCSwitch = obj[sel]["item"][i]["HLCSwitch"].asInt();
			m_vecMode[sel].cameraSet[i].HLCStrength = obj[sel]["item"][i]["HLCStrength"].asInt();
		}
		m_vecMode[sel].StructSize = sizeof(RSNetNew_CameraModeSet_t);

		//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamIPCCamearMode;
		param.ListParams = &m_vecMode[sel];
		param.ListParamNum = 1;

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
	else
	{
		if(obj.size() > 1)
		{
			//ImgCtrl页面，如果用户点击Copy、Save，需要保存所有通道

			//处理数据
			for(int i=0; i<obj.size(); i++)
			{
				m_vec[i].IRCutMode = obj[i]["IRCutMode"].asInt();
				m_vec[i].IRCutSensitive = obj[i]["IRCutSensitive"].asInt();
				m_vec[i].IRCutDelay = obj[i]["IRCutDelay"].asInt();
				m_vec[i].Flip = obj[i]["Flip"].asInt();
				m_vec[i].Mirror = obj[i]["Mirror"].asInt();
				m_vec[i].BackLightMode = obj[i]["BackLightMode"].asInt();
				m_vec[i].BackLightLevel = obj[i]["BackLightLevel"].asInt();
				m_vec[i].R3dnrMode = obj[i]["R3dnrMode"].asInt();
				m_vec[i].R3dnrThreshTarget = obj[i]["R3dnrThreshTarget"].asInt();
				m_vec[i].DwdrMode = obj[i]["DwdrMode"].asInt();
				m_vec[i].DwdrStrength = obj[i]["DwdrStrength"].asInt();
				m_vec[i].GainControlMode = obj[i]["GainControlMode"].asInt();
				m_vec[i].WBMode = obj[i]["WBMode"].asInt();
				m_vec[i].Rgain = obj[i]["Rgain"].asInt();
				m_vec[i].Ggain = obj[i]["Ggain"].asInt();
				m_vec[i].Bgain = obj[i]["Bgain"].asInt();
				m_vec[i].ShutterMode = obj[i]["ShutterMode"].asInt();
				m_vec[i].eShutterSpeed = obj[i]["eShutterSpeed"].asInt();
				m_vec[i].FlickerCtrl = obj[i]["FlickerCtrl"].asInt();
				m_vec[i].DefogMode = obj[i]["DefogMode"].asInt();
				m_vec[i].DefogStrength = obj[i]["DefogStrength"].asInt();
				m_vec[i].Rotate = obj[i]["Rotate"].asInt();
				m_vec[i].IRISMode = obj[i]["IRISMode"].asInt();
				m_vec[i].autoFocus = obj[i]["autoFocus"].asInt();
				m_vec[i].LEDEnable = obj[i]["LEDEnable"].asInt();
				m_vec[i].HideRotate = obj[i]["HideRotate"].asInt();
				m_vec[i].GainSwitch = obj[i]["GainSwitch"].asInt();
				m_vec[i].ColorGain = obj[i]["ColorGain"].asInt();
				m_vec[i].BrightGain = obj[i]["BrightGain"].asInt();
				m_vec[i].R2dnrMode = obj[i]["R2dnrMode"].asInt();
				m_vec[i].DefogFakeLottery = obj[i]["DefogFakeLottery"].asInt();
				m_vec[i].BackLightZone = obj[i]["BackLightZone"].asInt();
				m_vec[i].AntiShakeEnable = obj[i]["AntiShakeEnable"].asInt();
				m_vec[i].AntiShakeLevel = obj[i]["AntiShakeLevel"].asInt();
				m_vec[i].HLCSwitch = obj[i]["HLCSwitch"].asInt();
				m_vec[i].HLCStrength = obj[i]["HLCStrength"].asInt();

				m_vec[i].StartTime.Hour = obj[i]["StartTime"]["Hour"].asInt();
				m_vec[i].StartTime.Minute = obj[i]["StartTime"]["Minute"].asInt();
				m_vec[i].StartTime.Second = obj[i]["StartTime"]["Second"].asInt();
				m_vec[i].EndTime.Hour = obj[i]["EndTime"]["Hour"].asInt();
				m_vec[i].EndTime.Minute = obj[i]["EndTime"]["Minute"].asInt();
				m_vec[i].EndTime.Second = obj[i]["EndTime"]["Second"].asInt();
				m_vec[i].StructSize = sizeof(RSNetNew_CameraSet_t);
			}

			//保存数据
			RSNetSetParamParam param;
			memset(&param, '\0', sizeof(param));
			param.ParamType = MsgParamIPCImageSet;
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
		else
		{
			//ImgCtrl页面，修改参数，立即保存。一次保存一个通道

			//处理数据
			int i = 0;
			int sel = obj[i]["ch"].asInt();
			if(sel >= m_vec.size() || m_vec.size() <= 0)
				return ret;

			m_vec[sel].IRCutMode = obj[i]["IRCutMode"].asInt();
			m_vec[sel].IRCutSensitive = obj[i]["IRCutSensitive"].asInt();
			m_vec[sel].IRCutDelay = obj[i]["IRCutDelay"].asInt();
			m_vec[sel].Flip = obj[i]["Flip"].asInt();
			m_vec[sel].Mirror = obj[i]["Mirror"].asInt();
			m_vec[sel].BackLightMode = obj[i]["BackLightMode"].asInt();
			m_vec[sel].BackLightLevel = obj[i]["BackLightLevel"].asInt();
			m_vec[sel].R3dnrMode = obj[i]["R3dnrMode"].asInt();
			m_vec[sel].R3dnrThreshTarget = obj[i]["R3dnrThreshTarget"].asInt();
			m_vec[sel].DwdrMode = obj[i]["DwdrMode"].asInt();
			m_vec[sel].DwdrStrength = obj[i]["DwdrStrength"].asInt();
			m_vec[sel].GainControlMode = obj[i]["GainControlMode"].asInt();
			m_vec[sel].WBMode = obj[i]["WBMode"].asInt();
			m_vec[sel].Rgain = obj[i]["Rgain"].asInt();
			m_vec[sel].Ggain = obj[i]["Ggain"].asInt();
			m_vec[sel].Bgain = obj[i]["Bgain"].asInt();
			m_vec[sel].ShutterMode = obj[i]["ShutterMode"].asInt();
			m_vec[sel].eShutterSpeed = obj[i]["eShutterSpeed"].asInt();
			m_vec[sel].FlickerCtrl = obj[i]["FlickerCtrl"].asInt();
			m_vec[sel].DefogMode = obj[i]["DefogMode"].asInt();
			m_vec[sel].DefogStrength = obj[i]["DefogStrength"].asInt();
			m_vec[sel].Rotate = obj[i]["Rotate"].asInt();
			m_vec[sel].IRISMode = obj[i]["IRISMode"].asInt();
			m_vec[sel].autoFocus = obj[i]["autoFocus"].asInt();
			m_vec[sel].LEDEnable = obj[i]["LEDEnable"].asInt();
			m_vec[sel].HideRotate = obj[i]["HideRotate"].asInt();
			m_vec[sel].GainSwitch = obj[i]["GainSwitch"].asInt();
			m_vec[sel].ColorGain = obj[i]["ColorGain"].asInt();
			m_vec[sel].BrightGain = obj[i]["BrightGain"].asInt();
			m_vec[sel].R2dnrMode = obj[i]["R2dnrMode"].asInt();
			m_vec[sel].DefogFakeLottery = obj[i]["DefogFakeLottery"].asInt();
			m_vec[sel].BackLightZone = obj[i]["BackLightZone"].asInt();
			m_vec[sel].AntiShakeEnable = obj[i]["AntiShakeEnable"].asInt();
			m_vec[sel].AntiShakeLevel = obj[i]["AntiShakeLevel"].asInt();
			m_vec[sel].HLCSwitch = obj[i]["HLCSwitch"].asInt();
			m_vec[sel].HLCStrength = obj[i]["HLCStrength"].asInt();

			m_vec[i].StartTime.Hour = obj[i]["StartTime"]["Hour"].asInt();
			m_vec[i].StartTime.Minute = obj[i]["StartTime"]["Minute"].asInt();
			m_vec[i].StartTime.Second = obj[i]["StartTime"]["Second"].asInt();
			m_vec[i].EndTime.Hour = obj[i]["EndTime"]["Hour"].asInt();
			m_vec[i].EndTime.Minute = obj[i]["EndTime"]["Minute"].asInt();
			m_vec[i].EndTime.Second = obj[i]["EndTime"]["Second"].asInt();
			m_vec[sel].StructSize = sizeof(RSNetNew_CameraSet_t);

			//保存数据
			RSNetSetParamParam param;
			memset(&param, '\0', sizeof(param));
			param.ParamType = MsgParamIPCImageSet;
			param.ListParams = &m_vec[sel];
			param.ListParamNum = 1;

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

	}
}