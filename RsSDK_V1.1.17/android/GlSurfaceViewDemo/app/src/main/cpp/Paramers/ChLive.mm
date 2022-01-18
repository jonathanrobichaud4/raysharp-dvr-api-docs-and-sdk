#include "StdAfx.h"
#include "ChLive.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	ChLive* pThis = (ChLive*)userParam;
	RSNetNew_SoleLivingset_t *pData = (RSNetNew_SoleLivingset_t*)data;
	pThis->m_vec.push_back(*pData);
}

static void RSNET_CALL SingleDataCallback(void* data, void* userParam)
{
	ChLive* pThis = (ChLive*)userParam;
	RSNetNew_SoleLivingset_t *pData = (RSNetNew_SoleLivingset_t*)data;
	for(int i=0; i<pThis->m_vec.size(); i++)
	{
		if((pData->ChannelMask >> i & 0x1) == 1)
			pThis->m_vec[i] = *pData;
	}
}

std::string ChLive::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamModifyLiving;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNetNew_SoleLivingset_t);
	param.ListParamCallback = AllDataCallback;
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

std::string ChLive::QueryOne(int n)
{
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamModifyLiving;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNetNew_SoleLivingset_t);
	param.ListParamCallback = SingleDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	StructToJson(n);
	
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void ChLive::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	m_obj["ChnNamePos_X"] = m_vec[n].ChnNamePosX;
	m_obj["ChnNamePos_Y"] = m_vec[n].ChnNamePosY;
	m_obj["DateTimePos_X"] = m_vec[n].DateTimePosX;
	m_obj["DateTimePos_Y"] = m_vec[n].DateTimePosY;

#if defined(RS_IPHONE)||defined(RS_ANDROID)
    std::string str = Base64::Encode((unsigned char*)m_vec[n].ChnName, (int)strlen((char*)m_vec[n].ChnName));
	m_obj["ChnName"] = str.c_str();
#else
	m_obj["ChnName"] = (char*)m_vec[n].ChnName;
#endif

	m_obj["ChnNameFlag"] = m_vec[n].ShowChnNameFlag;
// 	int tmp = m_vec[n].ShowDateTimeFlag;
// 	if(m_pDevice->GetDeviceType() == DEV_HDVR){
// 		tmp = m_vec[0].ShowDateTimeFlag;//通道无关，总是看0通道
// 	}
	m_obj["PreviewTimeFlag"] = m_vec[n].ShowDateTimeFlag;
	m_obj["TimeMode"] = m_vec[n].TimeMode;
	m_obj["DateMode"] = m_vec[n].DateMode;
	m_obj["FlickerCtrl"] = m_vec[n].FlickerCtrl;
	m_obj["DisplayRule"] = m_vec[n].DisplayRule;
	m_obj["Covert"] = m_vec[n].Covert;
	m_obj["Transparent"] = m_vec[n].fgAlpha;
	m_obj["RecTimeFlag"] = m_vec[n].RecTimeFlag;
	m_obj["AHD_QESwitch"] = m_vec[n].AHD_QESwitch;

	m_obj["NewNameFlag"] = m_vec[n].NewNameFlag;
#if defined(RS_IPHONE)||defined(RS_ANDROID)
    str = Base64::Encode((unsigned char*)m_vec[n].NewChName, (int)strlen((char*)m_vec[n].NewChName));
    m_obj["NewChName"] = str.c_str();
#else
    m_obj["NewChName"] = (char*)m_vec[n].NewChName;
#endif
	m_obj["NewOsdLenEnable"] =  m_vec[n].NewOsdLenEnable;
	m_obj["NewChNameStrlen"] =  m_vec[n].NewChNameStrlen;

	m_obj["ChnName2Enable"] =  m_vec[n].ChnName2Enable;
	m_obj["ChnNamePosX2"] =  m_vec[n].ChnNamePosX2;
	m_obj["ChnNamePosY2"] =  m_vec[n].ChnNamePosY2;
	m_obj["ShowChnNameFlag2"] =  m_vec[n].ShowChnNameFlag2;
#if defined(RS_IPHONE)||defined(RS_ANDROID)
    str = Base64::Encode((unsigned char*)m_vec[n].ChnName2, (int)strlen((char*)m_vec[n].ChnName2));
    m_obj["ChnName2"] = str.c_str();
#else
    m_obj["ChnName2"] = (char*)m_vec[n].ChnName2;
#endif

	m_obj["MulitRowOsdPosX"] =  m_vec[n].MulitRowOsdPosX;
	m_obj["MulitRowOsdPosY"] =  m_vec[n].MulitRowOsdPosY;
	m_obj["ShowMulitRowOsdEnable"] =  m_vec[n].ShowMulitRowOsdEnable;
	m_obj["ShowMulitRowOsdFlag"] =  m_vec[n].ShowMulitRowOsdFlag;
	m_obj["TypeAlignment"] =  m_vec[n].TypeAlignment;
	m_obj["FontSize"] =  m_vec[n].FontSize;
	m_obj["WaterMark"] =  m_vec[n].WaterMark;
	m_obj["WaterMaskPosX"] =  m_vec[n].WaterMaskPosX;
	m_obj["WaterMaskPosY"] =  m_vec[n].WaterMaskPosY;

	//Json::Value obj(Json::arrayValue);

	for (int i=0; i<11;i++)
	{
		m_obj["MulitRowOsdContent"].append((char*)m_vec[n].MulitRowOsdContent[i]);
	}
	for (int i=0; i<9;i++)
	{
		m_obj["MulitRowOsdContent2"].append((char*)m_vec[n].MulitRowOsdContent2[i]);
	}

	Json::Value color(Json::arrayValue);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			color[j] = m_vec[n].ColorArr[i][j];
		}
		m_obj["ColorArr"].append(color);
	}

}

int ChLive::SaveAll(std::string strData)
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
		m_vec[i].ChnNamePosX = obj[i]["ChnNamePos_X"].asInt();
		m_vec[i].ChnNamePosY = obj[i]["ChnNamePos_Y"].asInt();
		m_vec[i].DateTimePosX = obj[i]["DateTimePos_X"].asInt();
		m_vec[i].DateTimePosY = obj[i]["DateTimePos_Y"].asInt();
		
		int maxLen = sizeof(m_vec[i].ChnName);
		memset(m_vec[i].ChnName, '\0', maxLen);
		m_str = obj[i]["ChnName"].asString();
#if defined(RS_IPHONE)||defined(RS_ANDROID)
		m_str = Base64::Decode(m_str.c_str(),m_str.length());
#endif
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_vec[i].ChnName, m_str.c_str(), len);
		
		m_vec[i].ShowChnNameFlag = obj[i]["ChnNameFlag"].asInt();

// 		int tmp = obj[i]["PreviewTimeFlag"].asInt();
// 		if(m_pDevice->GetDeviceType() == DEV_HDVR){
// 			int ch = 0;
// 			tmp = obj[ch]["PreviewTimeFlag"].asInt();//通道无关，总是看0通道
// 		}
		m_vec[i].ShowDateTimeFlag = obj[i]["PreviewTimeFlag"].asInt();

		m_vec[i].TimeMode = obj[i]["TimeMode"].asInt();
		m_vec[i].DateMode = obj[i]["DateMode"].asInt();
		m_vec[i].FlickerCtrl = obj[i]["FlickerCtrl"].asInt();
		m_vec[i].DisplayRule = obj[i]["DisplayRule"].asInt();
		m_vec[i].Covert = obj[i]["Covert"].asInt();
		m_vec[i].fgAlpha = obj[i]["Transparent"].asInt();
		m_vec[i].RecTimeFlag = obj[i]["RecTimeFlag"].asInt();
		m_vec[i].AHD_QESwitch = obj[i]["AHD_QESwitch"].asInt();

		maxLen = sizeof(m_vec[i].NewChName);
		memset(m_vec[i].NewChName, '\0', maxLen);
		m_str = obj[i]["NewChName"].asString();
#if defined(RS_IPHONE)||defined(RS_ANDROID)
		m_str = Base64::Decode(m_str.c_str(),m_str.length());
#endif
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_vec[i].NewChName, m_str.c_str(), len);

		m_vec[i].ChnNamePosX2 = obj[i]["ChnNamePosX2"].asInt();
		m_vec[i].ChnNamePosY2 = obj[i]["ChnNamePosY2"].asInt();
		m_vec[i].ShowChnNameFlag2 = obj[i]["ShowChnNameFlag2"].asInt();
		maxLen = sizeof(m_vec[i].ChnName2);
		memset(m_vec[i].ChnName2, '\0', maxLen);
		m_str = obj[i]["ChnName2"].asString();
#if defined(RS_IPHONE)||defined(RS_ANDROID)
		m_str = Base64::Decode(m_str.c_str(),m_str.length());
#endif
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_vec[i].ChnName2, m_str.c_str(), len);

		m_vec[i].MulitRowOsdPosX = obj[i]["MulitRowOsdPosX"].asInt();
		m_vec[i].MulitRowOsdPosY = obj[i]["MulitRowOsdPosY"].asInt();
		m_vec[i].ShowMulitRowOsdFlag = obj[i]["ShowMulitRowOsdFlag"].asInt();
		m_vec[i].TypeAlignment = obj[i]["TypeAlignment"].asInt();
		m_vec[i].FontSize = obj[i]["FontSize"].asInt();
		m_vec[i].WaterMark = obj[i]["WaterMark"].asInt();
		m_vec[i].WaterMaskPosX = obj[i]["WaterMaskPosX"].asInt();
		m_vec[i].WaterMaskPosY = obj[i]["WaterMaskPosY"].asInt();
		for (int m = 0;m<11;m++)
		{
			maxLen = sizeof(m_vec[i].MulitRowOsdContent[m]);
			memset(m_vec[i].MulitRowOsdContent[m], '\0', maxLen);
			m_str = obj[i]["MulitRowOsdContent"][m].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_vec[i].MulitRowOsdContent[m], m_str.c_str(), len);
		}

		for (int x = 0;x<9;x++)
		{
			maxLen = sizeof(m_vec[i].MulitRowOsdContent2[x]);
			memset(m_vec[i].MulitRowOsdContent2[x], '\0', maxLen);
			m_str = obj[i]["MulitRowOsdContent2"][x].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_vec[i].MulitRowOsdContent2[x], m_str.c_str(), len);
		}

		for(int p=0;p<4;p++){
			for (int q=0;q<4;q++)
			{
				m_vec[i].ColorArr[p][q] = obj[i]["ColorArr"][p][q].asInt();
			}
		}

		m_vec[i].StructSize = sizeof(RSNetNew_SoleLivingset_t);
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamModifyLiving;
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
