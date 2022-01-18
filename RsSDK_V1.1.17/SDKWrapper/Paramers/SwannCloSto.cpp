#include "StdAfx.h"
#include "SwannCloSto.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	SwannCloSto* pThis = (SwannCloSto*)userParam;
	RSNet_NewCloudStorage_t* CloudStorageSet = (RSNet_NewCloudStorage_t*)data;
	pThis->m_CloudStorageSet = *CloudStorageSet;
}

static void RSNET_CALL SoleParamDataCallback(void* data, void* userParam)
{
	SwannCloSto* pThis = (SwannCloSto*)userParam;
	RSNet_soleNewCloudStorage_t* SoleRecordSet = (RSNet_soleNewCloudStorage_t*)data;
	pThis->m_vec.push_back(*SoleRecordSet);
}

std::string SwannCloSto::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_CloudStorageSet,'\0', sizeof(RSNet_NewCloudStorage_t));
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamNewCloudestorage;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_NewCloudStorage_t);
	param.ParamCallback = ParamDataCallback;

	param.ListParamSize = sizeof(RSNet_soleNewCloudStorage_t);
	param.ListParamCallback = SoleParamDataCallback;

	param.UserParam = this;

	if(bDefault)
	{
		if(!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
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

void SwannCloSto::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["CloudType"] = m_CloudStorageSet.CloudType;
#if defined(RS_IPHONE) || defined(RS_ANDROID)
    std::string str = Base64::Encode((unsigned char *) m_CloudStorageSet.Dropboxtoken,
                                     (int) strlen((char *) m_CloudStorageSet.Dropboxtoken));
    m_obj["Dropboxtoken"] = str.c_str();
#else
    m_obj["Dropboxtoken"] = (char*)m_CloudStorageSet.Dropboxtoken;
#endif
	m_obj["cloudEnable"] = m_CloudStorageSet.cloudEnable;
	m_obj["HttpsEnable"] = m_CloudStorageSet.HttpsEnable;
	m_obj["SupportVideo"] = m_CloudStorageSet.SupportVideo;
	m_obj["MaxChnRecNum"] = m_CloudStorageSet.MaxChnRecNum;
	m_obj["CloudOverwrite"] = m_CloudStorageSet.CloudOverwrite;
    m_obj["VideoType"] = m_CloudStorageSet.VideoType;
    m_obj["CloudStatus"] = m_CloudStorageSet.CloudStatus;
	m_obj["IntervalTime"] = m_CloudStorageSet.IntervalTime;
	for(int i=0; i<8; ++i)
	{
		m_obj["ChnRecordEnable"].append(m_CloudStorageSet.ChnRecordEnable[i]);
	}

	for(int i = 0; i < 8;++i)
	{
		m_obj["ChannelMask"][i] = m_vec[n].ChannelMask[i];
	}
#if defined(RS_IPHONE) || defined(RS_ANDROID)
    str = Base64::Encode((unsigned char *) m_vec[n].DriveName,
                         (int) strlen((char *) m_vec[n].DriveName));
    m_obj["DriveName"] = str.c_str();
#else
    m_obj["DriveName"] = (char*)m_vec[n].DriveName;
#endif
	m_obj["MotionEnable"] = m_vec[n].MotionEnable;

	m_obj["VideoBKFormat"] = m_vec[n].VideoBKFormat;
	m_obj["StreamType"] = m_vec[n].StreamType;
	m_obj["RecordTime"] = m_vec[n].RecordTime;
	m_obj["MotionRecordEnable"] = m_vec[n].MotionRecordEnable;
	m_obj["IoAlamRecordEnable"] = m_vec[n].IoAlamRecordEnable;
	m_obj["PirRecordEnable"] = m_vec[n].PirRecordEnable;
	m_obj["IntelRecordEnable"] = m_vec[n].IntelRecordEnable;
}

int SwannCloSto::SaveAll(std::string strData)
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
		for(int j = 0;j < 8;++j)
		{
			m_vec[i].ChannelMask[j] = obj[i]["ChannelMask"][j].asUInt();
		}

		int maxLen = sizeof(m_vec[i].DriveName);
		memset(m_vec[i].DriveName, '\0', maxLen);
		m_str = obj[i]["DriveName"].asString();
#if defined(RS_IPHONE) || defined(RS_ANDROID)
        m_str = Base64::Decode(m_str.c_str(), m_str.length());
#endif
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_vec[i].DriveName, m_str.c_str(), len);

		m_vec[i].MotionEnable = obj[i]["MotionEnable"].asInt();

		m_vec[i].VideoBKFormat = obj[i]["VideoBKFormat"].asInt();
		m_vec[i].StreamType = obj[i]["StreamType"].asInt();
		m_vec[i].RecordTime = obj[i]["RecordTime"].asInt();
		m_vec[i].MotionRecordEnable = obj[i]["MotionRecordEnable"].asInt();
		m_vec[i].IoAlamRecordEnable = obj[i]["IoAlamRecordEnable"].asInt();
		m_vec[i].PirRecordEnable = obj[i]["PirRecordEnable"].asInt();
		m_vec[i].IntelRecordEnable = obj[i]["IntelRecordEnable"].asInt();
		
		m_vec[i].structsize = sizeof(RSNet_soleNewCloudStorage_t);
	}

	int i = 0;
	int curCh = obj[i]["curCh"].asUInt();
	//通道无关数据，只看当前通道
	m_CloudStorageSet.CloudType = obj[curCh]["CloudType"].asInt();
	m_CloudStorageSet.cloudEnable = obj[curCh]["cloudEnable"].asInt();
	m_CloudStorageSet.CloudOverwrite = obj[curCh]["CloudOverwrite"].asInt();
	m_CloudStorageSet.CloudStatus = obj[curCh]["CloudStatus"].asInt();
    m_CloudStorageSet.VideoType = obj[curCh]["VideoType"].asInt();
	m_CloudStorageSet.IntervalTime = obj[curCh]["IntervalTime"].asInt();
	for(int j = 0;j < 8;++j)
	{
		m_CloudStorageSet.ChnRecordEnable[j] = (unsigned int)obj[curCh]["ChnRecordEnable"][j].asDouble();
	}

	int maxLen = sizeof(m_CloudStorageSet.Dropboxtoken);
	memset(m_CloudStorageSet.Dropboxtoken, '\0', maxLen);
	m_str = obj[curCh]["Dropboxtoken"].asString();
#if defined(RS_IPHONE) || defined(RS_ANDROID)
    m_str = Base64::Decode(m_str.c_str(), m_str.length());
#endif
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_CloudStorageSet.Dropboxtoken, m_str.c_str(), len);

	m_CloudStorageSet.structsize = sizeof(RSNet_NewCloudStorage_t);

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamNewCloudestorage;
	param.Param = &m_CloudStorageSet;
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