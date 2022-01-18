#include "StdAfx.h"
#include "VideoSet.h"


static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	VideoSet* pThis = (VideoSet*)userParam;
	RSNet_SoleColorSet_t *pData = (RSNet_SoleColorSet_t*)data;
	pThis->m_vec.push_back(*pData);
}
static void RSNET_CALL OneDataCallback(void* data, void* userParam)
{
	VideoSet* pThis = (VideoSet*)userParam;
	memcpy(&pThis->m_Struct,data,sizeof(RSNet_SoleColorSet_t));
}

std::string VideoSet::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamColor;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleColorSet_t);
	param.ListParamCallback = AllDataCallback;
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

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void VideoSet::StructToJson(int n)
{
	m_obj.clear();
	m_obj["Chroma"] = m_vec[n].Chroma;
	m_obj["Brightness"] = m_vec[n].Brightness;
	m_obj["contrast"] = m_vec[n].contrast;
	m_obj["saturation"] = m_vec[n].saturation;
	//m_obj["sound"] = RSPlayGetPlayVolume();
	m_obj["DisplayRule"] = m_vec[n].DisplayRule;
	m_obj["ShowDefault"] = m_vec[n].ShowDefault;
	m_obj["Sharpness"] = m_vec[n].Sharpness;
	//m_obj["ColorMode"] = m_vec[n].ColorMode;
	m_obj["Gamma"] = m_vec[n].Gamma;

	//lux
	m_obj["Chroma2"] = m_vec[n].Chroma2;
	m_obj["Brightness2"] = m_vec[n].Brightness2;
	m_obj["contrast2"] = m_vec[n].contrast2;
	m_obj["saturation2"] = m_vec[n].saturation2;
	m_obj["Sharpness2"] = m_vec[n].Sharpness2;

	Json::Value Stime(Json::objectValue);
	Stime["Hour"] = m_vec[n].SunRiseTime.Hour;
	Stime["Minute"] = m_vec[n].SunRiseTime.Minute;
	Stime["Second"] = m_vec[n].SunRiseTime.Second;
	m_obj["SunRiseTime"] = Stime;

	Json::Value Etime(Json::objectValue);
	Etime["Hour"] = m_vec[n].SunSetTime.Hour;
	Etime["Minute"] = m_vec[n].SunSetTime.Minute;
	Etime["Second"] = m_vec[n].SunSetTime.Second;
	m_obj["SunSetTime"] = Etime;
}

int VideoSet::SaveAll(std::string strData)
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
		m_vec[i].Brightness = obj[i]["Brightness"].asInt();
		m_vec[i].contrast = obj[i]["contrast"].asInt();
		m_vec[i].saturation = obj[i]["saturation"].asInt();
		m_vec[i].Sharpness = obj[i]["Sharpness"].asInt();
		m_vec[i].Gamma = obj[i]["Gamma"].asInt();
		m_vec[i].Chroma = obj[i]["Chroma"].asInt();
		m_vec[i].Brightness2 = obj[i]["Brightness2"].asInt();
		m_vec[i].contrast2 = obj[i]["contrast2"].asInt();
		m_vec[i].saturation2 = obj[i]["saturation2"].asInt();
		m_vec[i].Sharpness2 = obj[i]["Sharpness2"].asInt();
		m_vec[i].Chroma2 = obj[i]["Chroma2"].asInt();

		m_vec[i].SunRiseTime.Hour = obj[i]["SunRiseTime"]["Hour"].asInt();
		m_vec[i].SunRiseTime.Minute = obj[i]["SunRiseTime"]["Minute"].asInt();
		m_vec[i].SunSetTime.Hour = obj[i]["SunSetTime"]["Hour"].asInt();
		m_vec[i].SunSetTime.Minute = obj[i]["SunSetTime"]["Minute"].asInt();


		m_vec[i].StructSize = sizeof(RSNet_SoleColorSet_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamColor;
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
std::string VideoSet::QueryOne(int n)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Struct, '\0', sizeof(RSNet_SoleColorSet_t));
	m_Struct.StructSize = sizeof(RSNet_SoleColorSet_t);
	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamColor;
	param.Req = &req;

	param.ParamSize = 0;
	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNet_SoleColorSet_t);
	param.ListParamCallback = OneDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["Chroma"] = m_Struct.Chroma;
	m_obj["Brightness"] = m_Struct.Brightness;
	m_obj["contrast"] = m_Struct.contrast;
	m_obj["saturation"] = m_Struct.saturation;
	m_obj["sound"] = RSPlayGetPlayVolume();
	m_obj["DisplayRule"] = m_Struct.DisplayRule;
	m_obj["ShowDefault"] = m_Struct.ShowDefault;
	m_obj["Sharpness"] = m_Struct.Sharpness;
	m_obj["ColorMode"] = m_Struct.ColorMode;
	m_obj["Gamma"] = m_Struct.Gamma;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int VideoSet::SaveOne(int n, std::string strData)
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
		int key = obj["key"].asInt();
		m_Struct.StructSize = sizeof(RSNet_SoleColorSet_t);
		m_Struct.DefaultColor = 0;

		if(key == 1){//亮度
			m_Struct.Brightness = obj["Brightness"].asInt() ;
		}else if (key == 2){//对比度
			m_Struct.contrast = obj["contrast"].asInt();
		}else if (key == 3){
			m_Struct.saturation = obj["saturation"].asInt() ;
		}else if (key == 4){
			m_Struct.Chroma = obj["Chroma"].asInt();
		}else if(key == 7){
			m_Struct.Sharpness = obj["Sharpness"].asInt();
		}else if(key ==8){
			m_Struct.LoadBalancing = obj["LoadBalancing"].asInt();
		}else if (key == 5){
			RSPlaySetPlayVolume(obj["Chroma"].asInt());
		}else if (key == 6){
			m_Struct.DefaultColor = 1;
		}else if(key ==9){
			m_Struct.Gamma = obj["Gamma"].asInt();
		}else if (key == 10){
			m_Struct.Brightness2 = obj["ColorBright2"].asInt();
		}else if(key == 11){
			m_Struct.contrast2 = obj["contrast2"].asInt();
		}else if(key ==12){
			m_Struct.saturation2 = obj["saturation2"].asInt();
		}else if (key == 13){
			m_Struct.Chroma2 = obj["Chroma2"].asInt();
		}else if (key == 14){
			m_Struct.Sharpness2 = obj["Sharpness2"].asInt();
		}
		m_Struct.SunRiseTime.Hour = obj["SunRiseTime"]["Hour"].asInt();
		m_Struct.SunRiseTime.Minute = obj["SunRiseTime"]["Minute"].asInt();
		m_Struct.SunSetTime.Hour = obj["SunSetTime"]["Hour"].asInt();
		m_Struct.SunSetTime.Minute = obj["SunSetTime"]["Minute"].asInt();
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		if(n <32)
		{
			m_Struct.ChannelMask =  (0x1<<n);
		}
		else
		{
			m_Struct.ChannelMask =  0xFFFF0000 + n;
		}
		param.ParamType = MsgParamColor;
		param.Param = NULL;
		param.ListParams = &m_Struct;
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
