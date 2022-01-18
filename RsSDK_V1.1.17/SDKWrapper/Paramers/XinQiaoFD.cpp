#include "StdAfx.h"
#include "XinQiaoFD.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	XinQiaoFD* pThis = (XinQiaoFD*)userParam;
	RSNet_SoleSiaIntParam_t* XQFDSet = (RSNet_SoleSiaIntParam_t*)data;
	pThis->m_vec.push_back(*XQFDSet);
}

std::string XinQiaoFD::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ListParamSize = sizeof(RSNet_SoleSiaIntParam_t);
	param.ParamType = MsgParamXINQIAOFaceDetection;
	param.Req = &req;
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;

	if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

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

void XinQiaoFD::StructToJson(int n)
{
	m_obj.clear();
	m_obj["faceSensitivity"] = m_vec[n].faceSensitivity;
	m_obj["faceQualityEnhancement"] = m_vec[n].faceQualityEnhancement;
	m_obj["picQuality"] = m_vec[n].picQuality;
	m_obj["ploy"] = m_vec[n].ploy;
	m_obj["bigSourceImageWidth"] = m_vec[n].bigSourceImageWidth;
	m_obj["bigSourceImageHeight"] = m_vec[n].bigSourceImageHeight;
	m_obj["smallSourceImageWidth"] = m_vec[n].smallSourceImageWidth;
	m_obj["smallSourceImageHeight"] = m_vec[n].smallSourceImageHeight;
	m_obj["sceneNumber"] = m_vec[n].sceneNumber;
	m_obj["minFaceWidth"] = m_vec[n].minFaceWidth;
	m_obj["maxFaceWidth"] = m_vec[n].maxFaceWidth;
	m_obj["minFaceHeight"] = m_vec[n].minFaceHeight;
	m_obj["maxFaceHeight"] = m_vec[n].maxFaceHeight;
	m_obj["isSendFullImage"] = m_vec[n].isSendFullImage;
	m_obj["isPreviewFaceInfo"] = m_vec[n].isPreviewFaceInfo;
	m_obj["faceImageType"] = m_vec[n].faceImageType;
	m_obj["fullImageType"] = m_vec[n].fullImageType;
	m_obj["bigSourceImageType"] = m_vec[n].bigSourceImageType;
	m_obj["smallSourceImageType"] = m_vec[n].smallSourceImageType;
	m_obj["SiaIntSwitch"] = m_vec[n].SiaIntSwitch;
}

int XinQiaoFD::SaveAll(std::string strData)
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
	for(int i=0; i<obj.size(); i++)
	{
		m_vec[i].faceSensitivity = obj[i]["faceSensitivity"].asUInt();
		m_vec[i].faceQualityEnhancement = obj[i]["faceQualityEnhancement"].asUInt();
		m_vec[i].picQuality = obj[i]["picQuality"].asUInt();
		m_vec[i].ploy = obj[i]["ploy"].asUInt();
		m_vec[i].bigSourceImageWidth = obj[i]["bigSourceImageWidth"].asUInt();
		m_vec[i].bigSourceImageHeight = obj[i]["bigSourceImageHeight"].asUInt();
		m_vec[i].smallSourceImageWidth = obj[i]["smallSourceImageWidth"].asUInt();
		m_vec[i].smallSourceImageHeight = obj[i]["smallSourceImageHeight"].asUInt();
		m_vec[i].sceneNumber = obj[i]["sceneNumber"].asUInt();
		m_vec[i].minFaceWidth = obj[i]["minFaceWidth"].asUInt();
		m_vec[i].maxFaceWidth = obj[i]["maxFaceWidth"].asUInt();
		m_vec[i].minFaceHeight = obj[i]["minFaceHeight"].asUInt();
		m_vec[i].maxFaceHeight = obj[i]["maxFaceHeight"].asUInt();
		m_vec[i].isSendFullImage = obj[i]["isSendFullImage"].asUInt();
		m_vec[i].isPreviewFaceInfo = obj[i]["isPreviewFaceInfo"].asUInt();
		m_vec[i].faceImageType = obj[i]["faceImageType"].asInt();
		m_vec[i].fullImageType = obj[i]["fullImageType"].asUInt();
		m_vec[i].bigSourceImageType = obj[i]["bigSourceImageType"].asUInt();
		m_vec[i].smallSourceImageType = obj[i]["smallSourceImageType"].asUInt();
		m_vec[i].SiaIntSwitch = obj[i]["SiaIntSwitch"].asUInt();

		m_vec[i].StructSize = sizeof(RSNet_SoleSiaIntParam_t);
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));

	//param.ParamType = MsgParamXINQIAOFaceDetection;
	//param.Param = &m_Struct;
	param.ParamType = MsgParamXINQIAOFaceDetection;
	param.Param = NULL;
	param.ListParams = &m_vec[0];
	param.ListParamNum = m_vec.size();
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;
	}else{
		if (nRet){
			return true;
		}else{
			return false;
		}
	}
}