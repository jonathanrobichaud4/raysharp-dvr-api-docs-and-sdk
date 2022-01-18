#include "StdAfx.h"
#include "IntrusionDetection.h"
#include <math.h>

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	IntrusionDetection* pThis = (IntrusionDetection*)userParam;
	RSNet_SoleJDVCAIntrusionDetectionConfig_t* intrusionDec = (RSNet_SoleJDVCAIntrusionDetectionConfig_t*)data;
	pThis->m_vec.push_back(*intrusionDec);
}

std::string IntrusionDetection::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamJDVCAIntrusionDetection;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleJDVCAIntrusionDetectionConfig_t);
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

void IntrusionDetection::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	
	m_obj["totalPoints"] = m_vec[n].totalPoints;

	for(int i = 0;i < m_vec[n].totalPoints;++i)
	{
		Json::Value val(Json::objectValue);
		val["x"] = m_vec[n].points[i].x;
		val["y"] = m_vec[n].points[i].y;
		m_obj["points"].append(val);
	}

	m_obj["imgResizeFactor"] = Round(m_vec[n].imgResizeFactor,4);
	m_obj["minPersonConf"] = Round(m_vec[n].minPersonConf,4);
	m_obj["skipFrameNum"] = m_vec[n].skipFrameNum;
	m_obj["bgsUpdataFactor"] = m_vec[n].bgsUpdataFactor;
	m_obj["BBSInRoiThr"] = m_vec[n].BBSInRoiThr;
	m_obj["fgInRoiThr"] = m_vec[n].fgInRoiThr;
	m_obj["fgPesBBThr"] = m_vec[n].fgPesBBThr;
	m_obj["minOverlapRatio"] = Round(m_vec[n].minOverlapRatio,4);
	m_obj["pesRectRatio"] = Round(m_vec[n].pesRectRatio,4);
	m_obj["pesRectMaxRatio"] = Round(m_vec[n].pesRectMaxRatio,4);
	m_obj["footRectRatioFrom"] = Round(m_vec[n].footRectRatioFrom,4);
	m_obj["footRectRatioTo"] = Round(m_vec[n].footRectRatioTo,4);
	m_obj["Enable"] = m_vec[n].Enable;
}

int IntrusionDetection::SaveAll(std::string strData)
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
		m_vec[i].totalPoints = obj[i]["totalPoints"].asInt();
		for(int j = 0;j < m_vec[i].totalPoints;++j)
		{
			m_vec[i].points[j].x = obj[i]["points"][j]["x"].asUInt();
			m_vec[i].points[j].y = obj[i]["points"][j]["y"].asUInt();
		}
		m_vec[i].imgResizeFactor = obj[i]["imgResizeFactor"].asDouble();
		m_vec[i].minPersonConf = obj[i]["minPersonConf"].asDouble();
		m_vec[i].skipFrameNum = obj[i]["skipFrameNum"].asInt();
		m_vec[i].bgsUpdataFactor = obj[i]["bgsUpdataFactor"].asUInt();
		m_vec[i].BBSInRoiThr = obj[i]["BBSInRoiThr"].asInt();
		m_vec[i].fgInRoiThr = obj[i]["fgInRoiThr"].asInt();
		m_vec[i].fgPesBBThr = obj[i]["fgPesBBThr"].asInt();
		m_vec[i].minOverlapRatio = obj[i]["minOverlapRatio"].asDouble();
		m_vec[i].pesRectRatio = obj[i]["pesRectRatio"].asDouble();
		m_vec[i].pesRectMaxRatio = obj[i]["pesRectMaxRatio"].asDouble();
		m_vec[i].footRectRatioFrom = obj[i]["footRectRatioFrom"].asDouble();
		m_vec[i].footRectRatioTo = obj[i]["footRectRatioTo"].asDouble();
		m_vec[i].Enable = obj[i]["Enable"].asInt();
		m_vec[i].StructSize = sizeof(RSNet_SoleJDVCAIntrusionDetectionConfig_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamJDVCAIntrusionDetection;
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

double IntrusionDetection::Round(double dVal, short iPlaces) {
	double dRetval;
	double dMod = 0.0000001;
	if (dVal<0.0) dMod=-0.0000001;
	dRetval=dVal;
	dRetval+=(5.0/pow(10.0,iPlaces+1.0));
	dRetval*=pow(10.0,iPlaces);
	dRetval=floor(dRetval+dMod);
	dRetval/=pow(10.0,iPlaces);
	return(dRetval);
}
