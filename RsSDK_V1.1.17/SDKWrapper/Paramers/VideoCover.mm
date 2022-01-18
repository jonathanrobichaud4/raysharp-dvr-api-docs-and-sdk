#include "StdAfx.h"
#include "VideoCover.h"


static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	VideoCover* pThis = (VideoCover*)userParam;
	RSNet_SoleVideoCover_t *pData = (RSNet_SoleVideoCover_t*)data;
	pThis->m_vec.push_back(*pData);
}

static void RSNET_CALL OneDataCallback(void* data, void* userParam)
{
	VideoCover* pThis = (VideoCover*)userParam;
	RSNet_SoleVideoCover_t *pData = (RSNet_SoleVideoCover_t*)data;
	for(int i=0; i<pThis->m_vec.size(); i++)
	{
		if((pData->ChannelMask >> i & 0x1) == 1)
			pThis->m_vec[i] = *pData;
	}
}

std::string VideoCover::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamVideoCover;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleVideoCover_t);
	param.ListParamCallback = ParamDataCallback;
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

std::string VideoCover::QueryOne(int n)
{
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamVideoCover;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleVideoCover_t);
	param.ListParamCallback = OneDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	StructToJson(n);

	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

void VideoCover::StructToJson(int i)
{
	m_obj.clear();
	m_obj["ch"] = i;
	m_obj["VideoCoverSwitch"] = m_vec[i].VideoCoverSwitch;
	m_obj["ShelterMode"] = m_vec[i].ShelterMode;
	m_obj["VideoCoverNum"] = m_vec[i].VideoCoverNum;

	//attention:this is union
	if(m_vec[i].ShelterMode==0)//Draw rectangle
	{
		//rect data
		int nLen1 = sizeof(m_vec[i].VideoCoverArea)/sizeof(m_vec[i].VideoCoverArea[0]);//8
		for(int j = 0;j < nLen1;++j)
		{
			Json::Value val(Json::objectValue);
			val["CoverSwitch"] = m_vec[i].VideoCoverArea[j].CoverSwitch;
			val["x"] = m_vec[i].VideoCoverArea[j].x;
			val["y"] = m_vec[i].VideoCoverArea[j].y;
			val["w"] = m_vec[i].VideoCoverArea[j].w;
			val["h"] = m_vec[i].VideoCoverArea[j].h;
			m_obj["VideoCoverArea"].append(val);
		}
		
		//empty grid data
		int nLen2 = sizeof(m_vec[i].regionSonix)/sizeof(m_vec[i].regionSonix[0]);//48
		for(int k=0; k<nLen2; k++)
		{
			m_obj["regionSonix"].append(0);
		}
	}
	else if(m_vec[i].ShelterMode==1)//Draw grid
	{
		//empty rect data
		int nLen1 = sizeof(m_vec[i].VideoCoverArea)/sizeof(m_vec[i].VideoCoverArea[0]);//8
		for(int j = 0;j < nLen1;++j)
		{
			Json::Value val(Json::objectValue);
			val["CoverSwitch"] = 0;
			val["x"] = 0;
			val["y"] = 0;
			val["w"] = 0;
			val["h"] = 0;
			m_obj["VideoCoverArea"].append(val);
		}
		
		//grid data
		int nLen2 = sizeof(m_vec[i].regionSonix)/sizeof(m_vec[i].regionSonix[0]);//48
		for(int k=0; k<nLen2; k++)
		{
			m_obj["regionSonix"].append(m_vec[i].regionSonix[k]);
		}
	}
	
	//马赛克 data
	int nLen = sizeof(m_vec[i].VideoCoverArea2)/sizeof(m_vec[i].VideoCoverArea2[0]);//4
	for(int j = 0;j < nLen;++j)
	{
		Json::Value val(Json::objectValue);
		val["CoverSwitch"] = m_vec[i].VideoCoverArea2[j].CoverSwitch;
		val["x"] = m_vec[i].VideoCoverArea2[j].x;
		val["y"] = m_vec[i].VideoCoverArea2[j].y;
		val["w"] = m_vec[i].VideoCoverArea2[j].w;
		val["h"] = m_vec[i].VideoCoverArea2[j].h;
		m_obj["VideoCoverArea2"].append(val);
	}
	m_obj["resWidth"] = m_vec[i].resWidth;
	m_obj["resHeight"] = m_vec[i].resHeight;
	m_obj["mosaicLevel"] = m_vec[i].mosaicLevel;
}

int VideoCover::SaveAll(std::string strData)
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
		m_vec[i].VideoCoverSwitch = obj[i]["VideoCoverSwitch"].asUInt();

		//attention:this is union
		if(m_vec[i].ShelterMode==0)//Draw rectangle
		{
			for(int j = 0;j < obj[i]["VideoCoverArea"].size();++j)//8
			{
				Json::Value val = obj[i]["VideoCoverArea"][j];
				m_vec[i].VideoCoverArea[j].CoverSwitch = val["CoverSwitch"].asInt();
				m_vec[i].VideoCoverArea[j].x = val["x"].asInt();
				m_vec[i].VideoCoverArea[j].y = val["y"].asInt();
				m_vec[i].VideoCoverArea[j].w = val["w"].asInt();
				m_vec[i].VideoCoverArea[j].h = val["h"].asInt();
			}
			/*
			int nLen = sizeof(m_vec[i].regionSonix)/sizeof(m_vec[i].regionSonix[0]);//48
			for(int k=0; k<nLen; k++)
			{
				m_vec[i].regionSonix[k] = obj[i]["regionSonix"][k].asUInt();
			}*/
		}
		else if(m_vec[i].ShelterMode==1)//Draw grid
		{
			/*
			for(int j = 0;j < obj[i]["VideoCoverArea"].size();++j)//8
			{
				Json::Value val = obj[i]["VideoCoverArea"][j];
				m_vec[i].VideoCoverArea[j].CoverSwitch = val["CoverSwitch"].asInt();
				m_vec[i].VideoCoverArea[j].x = val["x"].asInt();
				m_vec[i].VideoCoverArea[j].y = val["y"].asInt();
				m_vec[i].VideoCoverArea[j].w = val["w"].asInt();
				m_vec[i].VideoCoverArea[j].h = val["h"].asInt();
			}*/

			int nLen = sizeof(m_vec[i].regionSonix)/sizeof(m_vec[i].regionSonix[0]);//48
			for(int k=0; k<nLen; k++)
			{
				m_vec[i].regionSonix[k] = obj[i]["regionSonix"][k].asUInt();
			}
		}

		//马赛克 data
		for(int j = 0;j < obj[i]["VideoCoverArea2"].size();++j)//4
		{
			Json::Value val = obj[i]["VideoCoverArea2"][j];
			m_vec[i].VideoCoverArea2[j].CoverSwitch = val["CoverSwitch"].asInt();
			m_vec[i].VideoCoverArea2[j].x = val["x"].asInt();
			m_vec[i].VideoCoverArea2[j].y = val["y"].asInt();
			m_vec[i].VideoCoverArea2[j].w = val["w"].asInt();
			m_vec[i].VideoCoverArea2[j].h = val["h"].asInt();
		}
		m_vec[i].mosaicLevel = obj[i]["mosaicLevel"].asUInt();

		m_vec[i].StructSize = sizeof(RSNet_SoleVideoCover_t);
	}
	
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamVideoCover;
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