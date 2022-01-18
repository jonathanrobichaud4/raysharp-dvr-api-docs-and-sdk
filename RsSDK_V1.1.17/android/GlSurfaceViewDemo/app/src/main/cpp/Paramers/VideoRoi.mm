#include "StdAfx.h"
#include "VideoRoi.h"

#define MAX_ROI_AREA 8

VideoRoi::VideoRoi(void)
{
}

VideoRoi::~VideoRoi(void)
{
	m_vec.clear();
}

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	VideoRoi* pThis = (VideoRoi*)userParam;
	RSNet_SoleRoiParam_t* pData = (RSNet_SoleRoiParam_t*)data;
	pThis->m_vec.push_back(*pData);
}

std::string VideoRoi::QueryAll(bool bDefault)
{
	//ÇëÇóÊý¾Ý
	std::string strRst = "err";

	m_vec.clear();

	RSNetQueryParamParam param;
	memset(&param,'\0', sizeof(param));

	ChannelParamReq req = {0};
	req.StructSize = sizeof(req);
	req.ChannelMask[0] = 7;//111

	param.ParamType = MsgParamIPCROI;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleRoiParam_t);
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;

	if(RSNetQueryParam(m_pDevice->GetConnection(), &param))
	{
		int iCount = m_vec.size();
		if(iCount <= 0)
		{
			return strRst;
		}
	}

	int i = 0;
	RSNet_SoleRoiParam_t* pData = NULL;
	Json::Value data(Json::objectValue);
	Json::Value roi(Json::objectValue);
	m_obj.clear();
	BOOL bDataEmpty = FALSE;
	while(i < m_vec.size()){
		pData = &m_vec[i];
		if(pData != NULL){
			bDataEmpty = TRUE;
			data.clear();
			for (int n=0;n<8;n++)
			{
				roi.clear();
				roi["RoiIndex"] = pData->roi[n].RoiIndex;
				roi["RoiSwitch"] = pData->roi[n].RoiSwitch;
				roi["IsAbsQp"] = pData->roi[n].IsAbsQp;
				roi["ROILevel"] = pData->roi[n].ROILevel;
				roi["ROIBgFrameRate"] = pData->roi[n].ROIBgFrameRate;
				roi["Rect_x"] = pData->roi[n].Rect_x;
				roi["Rect_y"] = pData->roi[n].Rect_y;
				roi["Rect_w"] = pData->roi[n].Rect_w;
				roi["Rect_h"] = pData->roi[n].Rect_h;
				data["roi"].append(roi);
			}
			data["StreamType"] = pData->StreamType;
			data["Maxfps"] = pData->Maxfps;
			m_obj["data"].append(data);
		}
		i++;
	}

	if (bDataEmpty)
	{
		Json::FastWriter writer;
		strRst = writer.write(m_obj);
	}

	return strRst;
}

int VideoRoi::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj(Json::objectValue);
	if(!reader.parse(strData, obj)){
		return false;
	}

	int i = 0;
	RSNet_SoleRoiParam_t* pData = NULL;

	while(i < m_vec.size())
	{
		pData = &m_vec[i];
		for(int n=0;n<8;n++)
		{
			pData->roi[n].RoiIndex = n;
			pData->roi[n].IsAbsQp = obj["data"][i]["roi"][n]["IsAbsQp"].asInt();
			pData->roi[n].ROIBgFrameRate = obj["data"][i]["roi"][n]["ROIBgFrameRate"].asInt();
			pData->roi[n].ROILevel = obj["data"][i]["roi"][n]["ROILevel"].asInt();
			pData->roi[n].RoiSwitch = obj["data"][i]["roi"][n]["RoiSwitch"].asInt();
			pData->roi[n].Rect_x = obj["data"][i]["roi"][n]["Rect_x"].asInt();
			pData->roi[n].Rect_y = obj["data"][i]["roi"][n]["Rect_y"].asInt();
			pData->roi[n].Rect_h = obj["data"][i]["roi"][n]["Rect_h"].asInt();
			pData->roi[n].Rect_w = obj["data"][i]["roi"][n]["Rect_w"].asInt();
		}
		pData->StreamType = obj["data"][i]["StreamType"].asInt();
		pData->Maxfps = obj["data"][i]["Maxfps"].asInt();
		pData->StructSize = sizeof(RSNet_SoleRoiParam_t);
		i++;
	}

	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamIPCROI;
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

//RSNet_Roi_t* VideoRoi::GetParamData()
//{
//	int iCount = m_vec.size();
//	if(iCount <= 0 )
//	{
//		return NULL;
//	}
//
//	if(m_index < 0 || (m_index >= MAX_ROI_AREA))
//	{
//		m_index = 0;
//	}
//
//	int i = 0;
//	RSNet_SoleRoiParam_t* pData = NULL;
//	while(i < iCount)
//	{
//		pData = &m_vec[i];
//		if(pData->StreamType == m_StreamType)
//		{
//			return &(pData->roi[m_index]);
//		}
//		i++;
//	}
//
//	return NULL;
//}