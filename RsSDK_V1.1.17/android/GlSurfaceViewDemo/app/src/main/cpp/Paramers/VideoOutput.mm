#include "StdAfx.h"
#include "VideoOutput.h"

static void RSNET_CALL ParamDataCallback(void* param, void* userParam)
{
	VideoOutput * pThis = (VideoOutput*)userParam;
	memcpy(&pThis->m_Struct, param, sizeof(RSNet_Output_t));
}

std::string VideoOutput::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_Output_t));
	m_Struct.StructSize = sizeof(RSNet_Output_t);

	RSNetQueryParamParam param;
	ZeroMemory(&param, sizeof(param));
	param.ParamType = MsgParamOutPut;
	param.Req = &m_Struct;

	param.ParamSize = sizeof(RSNet_Output_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["OutputDevFlag"] = m_Struct.OutputDevFlag;
	m_obj["HDMIOverscan"] = m_Struct.HDMIOverscan;
	m_obj["HideNCD"] =  m_Struct.HideNCD;
	m_obj["IsSpot"] = m_Struct.IsSpot;
	for(int i = 0;i < 2;++i)
	{
		m_obj["SpotOutSplitModeMask"][i] = m_Struct.SpotOutSplitModeMask[i];
		m_obj["SpotOutSplitModeMode"][i] = m_Struct.SpotOutSplitModeMode[i];
	}
	for(int i = 0;i < 4;++i)
	{
		m_obj["UseMask"][i] = m_Struct.UseMask[i];
		m_obj["ResolutionMask"][i] = m_Struct.ResolutionMask[i];
		m_obj["SplitModeMask"][i] = m_Struct.SplitModeMask[i];
		m_obj["AutoSEQTime"][i] = m_Struct.AutoSEQTime[i];
		m_obj["SeqSplitMode"][i] = m_Struct.SeqSplitMode[i];
		m_obj["resolution"][i] = m_Struct.resolution[i];
		m_obj["transparency"][i] = m_Struct.transparency[i];
		m_obj["IsStaticMode"][i] = m_Struct.IsStaticMode[i];
		m_obj["IsEnFullScreen"][i] = m_Struct.IsEnFullScreen[i];
		for(int j = 0;j < 265;++j)
		{
			m_obj["VideoIndex"][i][j] = m_Struct.VideoIndex[i][j];
		}
	}
	for(int i = 0;i < 8;++i)
	{
		m_obj["SpotPollFlag"][i] = m_Struct.SpotPollFlag[i];
	}

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int VideoOutput::SaveAll(std::string strData)
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
	m_Struct.HDMIOverscan = obj["HDMIOverscan"].asUInt();
	if(!obj["HideNCD"].isNull())
	{
		m_Struct.HideNCD = obj["HideNCD"].asUInt();
	}
	for(int i = 0;i < 2;++i){
		m_Struct.SpotOutSplitModeMask[i] = obj["SpotOutSplitModeMask"][i].asUInt();
		m_Struct.SpotOutSplitModeMode[i] = obj["SpotOutSplitModeMode"][i].asUInt();
	}
	for(int i = 0;i < 4;++i)
	{
		m_Struct.AutoSEQTime[i] = obj["AutoSEQTime"][i].asUInt();
		m_Struct.SeqSplitMode[i] = obj["SeqSplitMode"][i].asUInt();
		m_Struct.resolution[i] = obj["resolution"][i].asUInt();
		m_Struct.transparency[i] = obj["transparency"][i].asUInt();
		m_Struct.IsStaticMode[i] = obj["IsStaticMode"][i].asUInt();
		m_Struct.IsEnFullScreen[i] = obj["IsEnFullScreen"][i].asUInt();
		for(int j = 0;j < 265;++j)
		{
			m_Struct.VideoIndex[i][j] = (char)obj["VideoIndex"][i][j].asUInt();
		}
	}

	for(int i = 0;i < 8;++i)
	{
		m_Struct.SpotPollFlag[i] = obj["SpotPollFlag"][i].asUInt();
	}

	if(!obj["IsSpot"].isNull())
	{
		m_Struct.IsSpot = obj["IsSpot"].asUInt();
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param,'\0', sizeof(param));
	param.ParamType = MsgParamOutPut;
	param.Param = &m_Struct;
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