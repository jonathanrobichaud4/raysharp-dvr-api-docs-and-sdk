#include "StdAfx.h"
#include "EncodeStream.h"

static void RSNET_CALL ListParamMainCallback(void* data, void* userParam)
{
	MainEncode* pThis = (MainEncode*)userParam;
	RSNetNew_SoleStreamset_t* channelOsd = (RSNetNew_SoleStreamset_t*)data;
	pThis->m_vec.push_back(*channelOsd);
}

std::string MainEncode::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamModifyMainStream;
	param.Req = &req;

	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNetNew_SoleStreamset_t);
	param.ListParamCallback = ListParamMainCallback;
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

void MainEncode::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["BitRateMode"] = m_vec[n].BitRateMode;
	m_obj["CustomBitrate"] = m_vec[n].CustomBitrate;
	m_obj["Bitrate"] = m_vec[n].Bitrate;
	m_obj["VideoQuality"] = m_vec[n].VideoQuality;
	m_obj["Fps"] = m_vec[n].Fps,
	m_obj["AudioSwitch"] = m_vec[n].AudioSwitch;
	m_obj["ResolutionsetIndex"] = m_vec[n].ResolutionsetIndex;
	m_obj["Num"] = m_vec[n].Num;
	m_obj["HaveAudio"] = m_vec[n].HaveAudio;
	m_obj["BitrateType"] = m_vec[n].BitrateType;
	m_obj["VideoEncType"] = m_vec[n].VideoEncType;
	m_obj["UsedEncType"] = m_vec[n].UsedEncType;
	m_obj["AMRSwitch"] = m_vec[n].AMRSwitch;
	m_obj["SoleResolutionMode"] = m_vec[n].SoleResolutionMode;
	m_obj["ProfileLevel"] = m_vec[n].ProfileLevel;
	m_obj["IFrameInterval"] = m_vec[n].IFrameInterval;
	m_obj["UseJPEG"] = m_vec[n].UseJPEG;
	m_obj["HideEncType"] = m_vec[n].HideEncType;

	Json::Value obj(Json::objectValue);

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}
	
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);

	}
	
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
	
#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
#endif
}


int MainEncode::SaveAll(std::string strData)
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
		m_vec[i].BitRateMode = obj[i]["BitRateMode"].asInt();
		m_vec[i].CustomBitrate = obj[i]["CustomBitrate"].asInt();
		m_vec[i].Bitrate = obj[i]["Bitrate"].asInt();
		m_vec[i].VideoQuality = obj[i]["VideoQuality"].asInt();
		m_vec[i].Fps = obj[i]["Fps"].asInt();
		m_vec[i].AudioSwitch = obj[i]["AudioSwitch"].asInt();
		m_vec[i].ResolutionsetIndex = obj[i]["ResolutionsetIndex"].asInt();
		m_vec[i].BitrateType = obj[i]["BitrateType"].asInt();
		m_vec[i].IFrameInterval = obj[i]["IFrameInterval"].asInt();
		m_vec[i].AudioEncType = obj[i]["AudioEncType"].asInt();
		m_vec[i].VideoEncType = obj[i]["VideoEncType"].asInt();
		m_vec[i].ProfileLevel = obj[i]["ProfileLevel"].asInt();
		m_vec[i].UsedEncType = obj[i]["UsedEncType"].asInt();
		m_vec[i].AMRSwitch = obj[i]["AMRSwitch"].asInt();
		m_vec[i].StructSize = sizeof(RSNetNew_SoleStreamset_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamModifyMainStream;
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

/********************************************************************************************/
/*		报警码流，报警码流同时刷新保存主码流和报警码流参数
/*
/********************************************************************************************/

static void RSNET_CALL ListParamAlarmCallback(void* data, void* userParam)
{
	AlarmEncode* pThis = (AlarmEncode*)userParam;
	RSNetNew_SoleStreamset_t* channelOsd = (RSNetNew_SoleStreamset_t*)data;
	pThis->m_alarmvec.push_back(*channelOsd);
}

std::string AlarmEncode::QueryAll(bool bDefault)
{
	//请求报警码流数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_alarmvec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamModifyAlarmStream;
	param.Req = &req;

	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNetNew_SoleStreamset_t);
	param.ListParamCallback = ListParamAlarmCallback;
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

	//请求主码流数据
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamModifyMainStream;
	param.Req = &req;

	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNetNew_SoleStreamset_t);
	param.ListParamCallback = ListParamMainCallback;
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

void AlarmEncode::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["BitRateMode"] = m_vec[n].BitRateMode;
	m_obj["CustomBitrate"] = m_vec[n].CustomBitrate;
	m_obj["Bitrate"] = m_vec[n].Bitrate;
	m_obj["VideoQuality"] = m_vec[n].VideoQuality;
	m_obj["Fps"] = m_vec[n].Fps,
	m_obj["AudioSwitch"] = m_vec[n].AudioSwitch;
	m_obj["ResolutionsetIndex"] = m_vec[n].ResolutionsetIndex;
	m_obj["Num"] = m_vec[n].Num;
	m_obj["HaveAudio"] = m_vec[n].HaveAudio;
	m_obj["BitrateType"] = m_vec[n].BitrateType;
	m_obj["VideoEncType"] = m_vec[n].VideoEncType;
	m_obj["UsedEncType"] = m_vec[n].UsedEncType;
	m_obj["AMRSwitch"] = m_vec[n].AMRSwitch;
	m_obj["SoleResolutionMode"] = m_vec[n].SoleResolutionMode;
	m_obj["ProfileLevel"] = m_vec[n].ProfileLevel;
	m_obj["IFrameInterval"] = m_vec[n].IFrameInterval;
	m_obj["UseJPEG"] = m_vec[n].UseJPEG;
	m_obj["HideEncType"] = m_vec[n].HideEncType;

	Json::Value obj(Json::objectValue);

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);

	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
	
#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
#endif

	m_obj["AlarmStream"]["ch"] = n;

	m_obj["AlarmStream"]["BitRateMode"] = m_alarmvec[n].BitRateMode;
	m_obj["AlarmStream"]["CustomBitrate"] = m_alarmvec[n].CustomBitrate;
	m_obj["AlarmStream"]["Bitrate"] = m_alarmvec[n].Bitrate;
	m_obj["AlarmStream"]["VideoQuality"] = m_alarmvec[n].VideoQuality;
	m_obj["AlarmStream"]["Fps"] = m_alarmvec[n].Fps,
	m_obj["AlarmStream"]["AudioSwitch"] = m_alarmvec[n].AudioSwitch;
	m_obj["AlarmStream"]["ResolutionsetIndex"] = m_alarmvec[n].ResolutionsetIndex;
	m_obj["AlarmStream"]["Num"] = m_alarmvec[n].Num;
	m_obj["AlarmStream"]["HaveAudio"] = m_alarmvec[n].HaveAudio;
	m_obj["AlarmStream"]["BitrateType"] = m_alarmvec[n].BitrateType;
	m_obj["AlarmStream"]["VideoEncType"] = m_alarmvec[n].VideoEncType;
	m_obj["AlarmStream"]["UsedEncType"] = m_alarmvec[n].UsedEncType;
	m_obj["AlarmStream"]["AMRSwitch"] = m_alarmvec[n].AMRSwitch;
	m_obj["AlarmStream"]["SoleResolutionMode"] = m_alarmvec[n].SoleResolutionMode;
	m_obj["AlarmStream"]["ProfileLevel"] = m_alarmvec[n].ProfileLevel;
	m_obj["AlarmStream"]["IFrameInterval"] = m_alarmvec[n].IFrameInterval;
	m_obj["AlarmStream"]["UseJPEG"] = m_alarmvec[n].UseJPEG;
	m_obj["AlarmStream"]["HideEncType"] = m_alarmvec[n].HideEncType;

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range[i].BitrateRange;
		m_obj["AlarmStream"]["BitrateRange"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range[i].FrameRateMin;
		m_obj["AlarmStream"]["FrameRateMin"].append(obj);

	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range[i].FrameRateMax;
		m_obj["AlarmStream"]["FrameRateMax"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range[i].ResolutionWidth;
		m_obj["AlarmStream"]["ResolutionWidth"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range[i].ResolutionHight;
		m_obj["AlarmStream"]["ResolutionHight"].append(obj);
	}
	
#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range2[i].BitrateRange;
		m_obj["AlarmStream"]["BitrateRange"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range2[i].FrameRateMin;
		m_obj["AlarmStream"]["FrameRateMin"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range2[i].FrameRateMax;
		m_obj["AlarmStream"]["FrameRateMax"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range2[i].ResolutionWidth;
		m_obj["AlarmStream"]["ResolutionWidth"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_alarmvec[n].Range2[i].ResolutionHight;
		m_obj["AlarmStream"]["ResolutionHight"].append(obj);
	}
#endif
}


int AlarmEncode::SaveAll(std::string strData)
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
		m_vec[i].BitRateMode = obj[i]["BitRateMode"].asInt();
		m_vec[i].CustomBitrate = obj[i]["CustomBitrate"].asInt();
		m_vec[i].Bitrate = obj[i]["Bitrate"].asInt();
		m_vec[i].VideoQuality = obj[i]["VideoQuality"].asInt();
		m_vec[i].Fps = obj[i]["Fps"].asInt();
		m_vec[i].AudioSwitch = obj[i]["AudioSwitch"].asInt();
		m_vec[i].ResolutionsetIndex = obj[i]["ResolutionsetIndex"].asInt();
		m_vec[i].BitrateType = obj[i]["BitrateType"].asInt();
		m_vec[i].IFrameInterval = obj[i]["IFrameInterval"].asInt();
		m_vec[i].AudioEncType = obj[i]["AudioEncType"].asInt();
		m_vec[i].VideoEncType = obj[i]["VideoEncType"].asInt();
		m_vec[i].ProfileLevel = obj[i]["ProfileLevel"].asInt();
		m_vec[i].UsedEncType = obj[i]["UsedEncType"].asInt();
		m_vec[i].AMRSwitch = obj[i]["AMRSwitch"].asInt();
		m_vec[i].StructSize = sizeof(RSNetNew_SoleStreamset_t);
		m_alarmvec[i].BitRateMode = obj[i]["AlarmStream"]["BitRateMode"].asInt();
		m_alarmvec[i].CustomBitrate = obj[i]["AlarmStream"]["CustomBitrate"].asInt();
		m_alarmvec[i].Bitrate = obj[i]["AlarmStream"]["Bitrate"].asInt();
		m_alarmvec[i].VideoQuality = obj[i]["AlarmStream"]["VideoQuality"].asInt();
		m_alarmvec[i].Fps = obj[i]["AlarmStream"]["Fps"].asInt();
		m_alarmvec[i].AudioSwitch = obj[i]["AlarmStream"]["AudioSwitch"].asInt();
		m_alarmvec[i].ResolutionsetIndex = obj[i]["AlarmStream"]["ResolutionsetIndex"].asInt();
		m_alarmvec[i].BitrateType = obj[i]["AlarmStream"]["BitrateType"].asInt();
		m_alarmvec[i].IFrameInterval = obj[i]["AlarmStream"]["IFrameInterval"].asInt();
		m_alarmvec[i].AudioEncType = obj[i]["AlarmStream"]["AudioEncType"].asInt();
		m_alarmvec[i].VideoEncType = obj[i]["AlarmStream"]["VideoEncType"].asInt();
		m_alarmvec[i].ProfileLevel = obj[i]["AlarmStream"]["ProfileLevel"].asInt();
		m_alarmvec[i].UsedEncType = obj[i]["AlarmStream"]["UsedEncType"].asInt();
		m_alarmvec[i].AMRSwitch = obj[i]["AlarmStream"]["AMRSwitch"].asInt();
		m_alarmvec[i].StructSize = sizeof(RSNetNew_SoleStreamset_t);
	}

	RSNetSetParamParam alarmparam;
	memset(&alarmparam, '\0', sizeof(alarmparam));
	alarmparam.ParamType = MsgParamModifyAlarmStream;
	alarmparam.Param = NULL;
	alarmparam.ListParams = &m_alarmvec[0];
	alarmparam.ListParamNum = m_alarmvec.size();
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &alarmparam);
	if(2 == nRet){
		return 2;
	}else{
		if (nRet)
		{
			RSNetSetParamParam param;
			memset(&param, '\0', sizeof(param));
			param.ParamType = MsgParamModifyMainStream;
			param.Param = NULL;
			param.ListParams = &m_vec[0];
			param.ListParamNum = m_vec.size();
			if (RSNetSetParam(m_pDevice->GetConnection(), &param))
			{
				return true;
			}
			return false;
		}
		return false;
	}
}

/********************************************************************************************/
/*		子码流
/*
/********************************************************************************************/


static void RSNET_CALL ListParamSubCallback(void* data, void* userParam)
{
	SubEncode* pThis = (SubEncode*)userParam;
	RSNetNew_SoleStreamset_t* channelOsd = (RSNetNew_SoleStreamset_t*)data;
	pThis->m_vec.push_back(*channelOsd);
}

std::string SubEncode::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamModifySubStream;
	param.Req = &req;

	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNetNew_SoleStreamset_t);
	param.ListParamCallback = ListParamSubCallback;
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

void SubEncode::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["BitRateMode"] = m_vec[n].BitRateMode;
	m_obj["CustomBitrate"] = m_vec[n].CustomBitrate;
	m_obj["Bitrate"] = m_vec[n].Bitrate;
	m_obj["VideoQuality"] = m_vec[n].VideoQuality;
	m_obj["Fps"] = m_vec[n].Fps;
	m_obj["AudioSwitch"] = m_vec[n].AudioSwitch;
	m_obj["ResolutionsetIndex"] = m_vec[n].ResolutionsetIndex;
	m_obj["Num"] = m_vec[n].Num;
	m_obj["HaveAudio"] = m_vec[n].HaveAudio;
	m_obj["BitrateType"] = m_vec[n].BitrateType,
	m_obj["VideoEncType"] = m_vec[n].VideoEncType;
	m_obj["UsedEncType"] = m_vec[n].UsedEncType;
	m_obj["ProfileLevel"] = m_vec[n].ProfileLevel;
	m_obj["IFrameInterval"] = m_vec[n].IFrameInterval;
	m_obj["UseJPEG"] = m_vec[n].UseJPEG;
	m_obj["HideEncType"] = m_vec[n].HideEncType;
	m_obj["VideoSwitch"] = m_vec[n].VideoSwitch;
	
	Json::Value obj(Json::objectValue);
	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}

	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}

	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
	
#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range2[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}
	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}
	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
#endif
}

int SubEncode::SaveAll(std::string strData)
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
		m_vec[i].BitRateMode = obj[i]["BitRateMode"].asInt();
		m_vec[i].CustomBitrate = obj[i]["CustomBitrate"].asInt();
		m_vec[i].Bitrate = obj[i]["Bitrate"].asInt();
		m_vec[i].VideoQuality = obj[i]["VideoQuality"].asInt();
		m_vec[i].Fps = obj[i]["Fps"].asInt();
		m_vec[i].AudioSwitch = obj[i]["AudioSwitch"].asInt();
		m_vec[i].ResolutionsetIndex = obj[i]["ResolutionsetIndex"].asInt();
		m_vec[i].BitrateType = obj[i]["BitrateType"].asInt();
		m_vec[i].VideoEncType = obj[i]["VideoEncType"].asInt();
		m_vec[i].UsedEncType = obj[i]["UsedEncType"].asInt();
		m_vec[i].ProfileLevel = obj[i]["ProfileLevel"].asInt();
		m_vec[i].IFrameInterval = obj[i]["IFrameInterval"].asInt();
		m_vec[i].VideoSwitch = obj[i]["VideoSwitch"].asInt();
		m_vec[i].StructSize = sizeof(RSNetNew_SoleStreamset_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamModifySubStream;
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

/********************************************************************************************/
/*		手机码流
/*
/********************************************************************************************/

MobileEncode::MobileEncode(void)
{
	nArea = 0;
}

static void RSNET_CALL ListParamMobileCallback(void* data, void* userParam)
{
	MobileEncode* pThis = (MobileEncode*)userParam;
	RSNetNew_SoleStreamset_t* pData = (RSNetNew_SoleStreamset_t*)data;
	pThis->m_vec.push_back(*pData);
}

static void RSNET_CALL SoleParamThirdCallback(void* data, void* userParam)
{
	MobileEncode* pThis = (MobileEncode*)userParam;
	RSNetNew_AreaStreamset_t* pData = (RSNetNew_AreaStreamset_t*)data;
	pThis->m_vecArea.push_back(*pData);
}

std::string MobileEncode::QueryAll(bool isDefault)
{
	unsigned int PageControl = m_pDevice->GetLoginRsp()->PageControl;
	nArea = (PageControl >>4) & 1;

	if(nArea == 1)
	{
		//请求数据
		std::string strRet = "err";

		RSNetQueryParamParam param;
		memset(&param, '\0',sizeof(param));

		m_vecArea.clear();

		ChannelParamReq req;
		TransformChannelParamReq_All(&req);

		param.ParamType = MsgParamAreaStream;
		param.Req = &req;

		param.ListParamSize = sizeof(RSNetNew_AreaStreamset_t);
		param.ListParamCallback = SoleParamThirdCallback;
		param.UserParam = this;

		if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;

		//处理数据
		Json::Value root(Json::arrayValue);
		for(int i=0; i<m_vecArea.size(); i++)
		{
			StructToJson_Area(i);
			root.append(m_obj);
		}

		//返回数据
		Json::FastWriter writer;
		strRet = writer.write(root);
		return strRet;
	}
	else
	{
		//请求数据
		std::string strRet = "err";

		RSNetQueryParamParam param;
		memset(&param, '\0', sizeof(param));

		m_vec.clear();

		ChannelParamReq req;
		TransformChannelParamReq_All(&req);

		param.ParamType = MsgParamModifyMobileStream;
		param.Req = &req;

		param.ParamCallback = NULL;

		param.ListParamSize = sizeof(RSNetNew_SoleStreamset_t);
		param.ListParamCallback = ListParamMobileCallback;
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

		//返回数据
		Json::FastWriter writer;
		strRet = writer.write(root);
		return strRet;
	}
}

void MobileEncode::StructToJson_Area(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["TvSystem"] = m_pDevice->GetLoginRsp()->VideoFormat;
	m_obj["BitRateMode"] = m_vecArea[n].rsAreaStreamSet.BitRateMode;
	m_obj["CustomBitrate"] = m_vecArea[n].rsAreaStreamSet.CustomBitrate;
	m_obj["Bitrate"] = m_vecArea[n].rsAreaStreamSet.Bitrate;
	m_obj["VideoQuality"] = m_vecArea[n].rsAreaStreamSet.VideoQuality;
	m_obj["Fps"] = m_vecArea[n].rsAreaStreamSet.Fps;
	m_obj["AudioSwitch"] = m_vecArea[n].rsAreaStreamSet.AudioSwitch;
	m_obj["VideoSwitch"] = m_vecArea[n].rsAreaStreamSet.VideoSwitch;
	m_obj["ResolutionsetIndex"] = m_vecArea[n].rsAreaStreamSet.ResolutionsetIndex;
	m_obj["Num"] = m_vecArea[n].rsAreaStreamSet.Num;
	m_obj["HaveAudio"] = m_vecArea[n].rsAreaStreamSet.HaveAudio;
	m_obj["BitrateType"] = m_vecArea[n].rsAreaStreamSet.BitrateType;
	m_obj["IFrameInterval"] = m_vecArea[n].rsAreaStreamSet.IFrameInterval;
	m_obj["AudioEncType"] = m_vecArea[n].rsAreaStreamSet.AudioEncType;
	m_obj["VideoEncType"] = m_vecArea[n].rsAreaStreamSet.VideoEncType;
	m_obj["ProfileLevel"] = m_vecArea[n].rsAreaStreamSet.ProfileLevel;
	m_obj["UsedEncType"] = m_vecArea[n].rsAreaStreamSet.UsedEncType;
	m_obj["UseJPEG"] = m_vecArea[n].rsAreaStreamSet.UseJPEG;
	m_obj["HideEncType"] = m_vecArea[n].rsAreaStreamSet.HideEncType;

	Json::Value obj(Json::objectValue);

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
	
#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range2[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}
	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range2[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}
	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range2[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}
	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range2[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}
	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vecArea[n].rsAreaStreamSet.Range2[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
#endif

	m_obj["areaSwitch"] = m_vecArea[n].areaSwitch;
	m_obj["rect"]["h"] = m_vecArea[n].rect.h;
	m_obj["rect"]["w"] = m_vecArea[n].rect.w;
	m_obj["rect"]["x"] = m_vecArea[n].rect.x;
	m_obj["rect"]["y"] = m_vecArea[n].rect.y;
	m_obj["res_w"] = m_vecArea[n].res_w;
	m_obj["res_h"] = m_vecArea[n].res_h;
}

void MobileEncode::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["TvSystem"] = m_pDevice->GetLoginRsp()->VideoFormat;
	m_obj["BitRateMode"] = m_vec[n].BitRateMode;
	m_obj["CustomBitrate"] = m_vec[n].CustomBitrate;
	m_obj["Bitrate"] = m_vec[n].Bitrate;
	m_obj["VideoQuality"] = m_vec[n].VideoQuality;
	m_obj["Fps"] = m_vec[n].Fps;
	m_obj["AudioSwitch"] = m_vec[n].AudioSwitch;
	m_obj["ResolutionsetIndex"] = m_vec[n].ResolutionsetIndex;
	m_obj["Num"] = m_vec[n].Num;
	m_obj["HaveAudio"] = m_vec[n].HaveAudio;
	m_obj["BitrateType"] = m_vec[n].BitrateType;
	m_obj["IFrameInterval"] = m_vec[n].IFrameInterval;
	m_obj["AudioEncType"] = m_vec[n].AudioEncType;
	m_obj["VideoEncType"] = m_vec[n].VideoEncType;
	m_obj["ProfileLevel"] = m_vec[n].ProfileLevel;
	m_obj["UsedEncType"] = m_vec[n].UsedEncType;
	m_obj["VideoSwitch"] = m_vec[n].VideoSwitch;
	m_obj["UseJPEG"] = m_vec[n].UseJPEG;
	m_obj["HideEncType"] = m_vec[n].HideEncType;

	Json::Value obj(Json::objectValue);

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}

	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}

	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}


	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
	
#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].BitrateRange;
		m_obj["BitrateRange"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMin;
		m_obj["FrameRateMin"].append(obj);
	}
	for (int i=0; i<8;i++)
	{
		obj["item"] = m_vec[n].Range2[i].FrameRateMax;
		m_obj["FrameRateMax"].append(obj);
	}
	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionWidth;
		m_obj["ResolutionWidth"].append(obj);
	}
	for (int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].Range2[i].ResolutionHight;
		m_obj["ResolutionHight"].append(obj);
	}
#endif
}


int MobileEncode::SaveAll(std::string strData)
{
	if(nArea == 1)
	{
		if(strData == "null"){
			return false;
		}

		Json::Reader reader;
		Json::Value obj(Json::objectValue);
		if(!reader.parse(strData,obj)){
			return false;
		}

		for(int i=0; i<obj.size(); i++)
		{
			m_vecArea[i].rsAreaStreamSet.BitrateType = obj[i]["BitrateType"].asInt();
			m_vecArea[i].rsAreaStreamSet.IFrameInterval = obj[i]["IFrameInterval"].asInt();
			m_vecArea[i].rsAreaStreamSet.BitRateMode = obj[i]["BitRateMode"].asInt();
			m_vecArea[i].rsAreaStreamSet.CustomBitrate = obj[i]["CustomBitrate"].asInt();
			m_vecArea[i].rsAreaStreamSet.Bitrate = obj[i]["Bitrate"].asInt();
			m_vecArea[i].rsAreaStreamSet.VideoQuality = obj[i]["VideoQuality"].asInt();
			m_vecArea[i].rsAreaStreamSet.Fps = obj[i]["Fps"].asInt();
			m_vecArea[i].rsAreaStreamSet.AudioSwitch = obj[i]["AudioSwitch"].asInt();
			m_vecArea[i].rsAreaStreamSet.ResolutionsetIndex = obj[i]["ResolutionsetIndex"].asInt();
			m_vecArea[i].rsAreaStreamSet.VideoSwitch = obj[i]["VideoSwitch"].asInt();
			m_vecArea[i].rsAreaStreamSet.AudioEncType = obj[i]["AudioEncType"].asInt();
			m_vecArea[i].rsAreaStreamSet.VideoEncType = obj[i]["VideoEncType"].asInt();
			m_vecArea[i].rsAreaStreamSet.ProfileLevel = obj[i]["ProfileLevel"].asInt();
			m_vecArea[i].rsAreaStreamSet.UsedEncType = obj[i]["UsedEncType"].asInt();
			m_vecArea[i].areaSwitch = obj[i]["areaSwitch"].asInt();
			m_vecArea[i].rect.h = obj[i]["rect"]["h"].asUInt();
			m_vecArea[i].rect.w = obj[i]["rect"]["w"].asUInt();
			m_vecArea[i].rect.x = obj[i]["rect"]["x"].asUInt();
			m_vecArea[i].rect.y = obj[i]["rect"]["y"].asUInt();
			m_vecArea[i].StructSize = sizeof(RSNetNew_AreaStreamset_t);
		}

		RSNetSetParamParam param;
		memset(&param,'\0', sizeof(param));
		param.ParamType = MsgParamAreaStream;
		param.Param = NULL;
		param.ListParams = &m_vecArea[0];
		param.ListParamNum = m_vecArea.size();

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
			m_vec[i].BitRateMode = obj[i]["BitRateMode"].asInt();
			m_vec[i].CustomBitrate = obj[i]["CustomBitrate"].asInt();
			m_vec[i].Bitrate = obj[i]["Bitrate"].asInt();
			m_vec[i].VideoQuality = obj[i]["VideoQuality"].asInt();
			m_vec[i].Fps = obj[i]["Fps"].asInt();
			m_vec[i].AudioSwitch = obj[i]["AudioSwitch"].asInt();
			m_vec[i].ResolutionsetIndex = obj[i]["ResolutionsetIndex"].asInt();
			m_vec[i].VideoSwitch = obj[i]["VideoSwitch"].asInt();
			m_vec[i].BitrateType = obj[i]["BitrateType"].asInt();
			m_vec[i].VideoEncType = obj[i]["VideoEncType"].asInt();
			m_vec[i].IFrameInterval = obj[i]["IFrameInterval"].asInt();
			m_vec[i].AudioEncType = obj[i]["AudioEncType"].asInt();
			m_vec[i].ProfileLevel = obj[i]["ProfileLevel"].asInt();
			m_vec[i].UsedEncType = obj[i]["UsedEncType"].asInt();
			m_vec[i].StructSize = sizeof(RSNetNew_SoleStreamset_t);
		}

		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamModifyMobileStream;
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
}