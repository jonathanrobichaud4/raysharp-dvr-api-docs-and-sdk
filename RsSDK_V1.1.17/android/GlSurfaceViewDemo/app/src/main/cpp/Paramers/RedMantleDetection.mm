#include "StdAfx.h"
#include "RedMantleDetection.h"
#include <math.h>

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	RedMantleDetection* pThis = (RedMantleDetection*)userParam;
	RSNet_SoleJDVCARedMantleDetectionConfig_t* intrusionDec = (RSNet_SoleJDVCARedMantleDetectionConfig_t*)data;
	pThis->m_vec.push_back(*intrusionDec);
}

std::string RedMantleDetection::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamJDVCARedMantleDetection;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleJDVCARedMantleDetectionConfig_t);
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

void RedMantleDetection::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	m_obj["fImgResizeFactor"] = Round(m_vec[n].fImgResizeFactor,4);
	m_obj["minCircleConf"] = Round(m_vec[n].minCircleConf,4);
	m_obj["filterSeconds"] = Round(m_vec[n].filterSeconds,4);
	m_obj["minFilterSize"] = m_vec[n].minFilterSize;
	m_obj["nSkipFrames"] = m_vec[n].nSkipFrames;
	m_obj["bgsUpdateSecondsSlow"] = Round(m_vec[n].bgsUpdateSecondsSlow,4);
	m_obj["bgsUpdateSecondsFast"] = Round(m_vec[n].bgsUpdateSecondsFast,4);
	m_obj["fDetectRatioFixed"] = Round(m_vec[n].fDetectRatioFixed,4);
	m_obj["fDetectRatioLosted"] = Round(m_vec[n].fDetectRatioLosted,4);
	m_obj["fDetectRatioOcclusion"] = Round(m_vec[n].fDetectRatioOcclusion,4);
	m_obj["fDetectRatioNonOcclusion"] = Round(m_vec[n].fDetectRatioNonOcclusion,4);
	m_obj["vanishKeepSeconds"] = Round(m_vec[n].vanishKeepSeconds,4);
	m_obj["toFixKeepSeconds"] = Round(m_vec[n].toFixKeepSeconds,4);
	m_obj["occlusionKeepSeconds"] = Round(m_vec[n].occlusionKeepSeconds,4);
	m_obj["toMonitorWaitSeconds"] = Round(m_vec[n].toMonitorWaitSeconds,4);
	m_obj["reinitWaitSeconds"] = Round(m_vec[n].reinitWaitSeconds,4);
	m_obj["Enable"] = m_vec[n].Enable;
}

int RedMantleDetection::SaveAll(std::string strData)
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
		m_vec[i].fImgResizeFactor = obj[i]["fImgResizeFactor"].asDouble();
		m_vec[i].minCircleConf = obj[i]["minCircleConf"].asDouble();
		m_vec[i].filterSeconds = obj[i]["filterSeconds"].asDouble();
		m_vec[i].minFilterSize = obj[i]["minFilterSize"].asInt();
		m_vec[i].nSkipFrames = obj[i]["nSkipFrames"].asUInt();
		m_vec[i].bgsUpdateSecondsSlow = obj[i]["bgsUpdateSecondsSlow"].asDouble();
		m_vec[i].bgsUpdateSecondsFast = obj[i]["bgsUpdateSecondsFast"].asDouble();
		m_vec[i].fDetectRatioFixed = obj[i]["fDetectRatioFixed"].asDouble();
		m_vec[i].fDetectRatioLosted = obj[i]["fDetectRatioLosted"].asDouble();
		m_vec[i].fDetectRatioOcclusion = obj[i]["fDetectRatioOcclusion"].asDouble();
		m_vec[i].fDetectRatioNonOcclusion = obj[i]["fDetectRatioNonOcclusion"].asDouble();
		m_vec[i].vanishKeepSeconds = obj[i]["vanishKeepSeconds"].asDouble();
		m_vec[i].toFixKeepSeconds = obj[i]["toFixKeepSeconds"].asDouble();
		m_vec[i].occlusionKeepSeconds = obj[i]["occlusionKeepSeconds"].asDouble();
		m_vec[i].toMonitorWaitSeconds = obj[i]["toMonitorWaitSeconds"].asDouble();
		m_vec[i].reinitWaitSeconds = obj[i]["reinitWaitSeconds"].asDouble();
		m_vec[i].Enable = obj[i]["Enable"].asInt();
		m_vec[i].StructSize = sizeof(RSNet_SoleJDVCARedMantleDetectionConfig_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamJDVCARedMantleDetection;
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

double RedMantleDetection::Round(double dVal, short iPlaces) {
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
