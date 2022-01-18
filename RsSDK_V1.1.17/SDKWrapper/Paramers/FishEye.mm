#pragma once
#include "StdAfx.h"
#include "FishEye.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	FishEye * pThis = (FishEye*)userParam;
	memcpy(&pThis->m_Struct, data, sizeof(RSNet_FishEye_t));
}

std::string FishEye::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_FishEye_t));
	m_Struct.StructSize = sizeof(RSNet_FishEye_t);

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamFishEye;
	param.Req = &m_Struct;

	param.ParamSize = sizeof(RSNet_FishEye_t);
	param.ParamCallback = ParamDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(),&param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["mount_mode_0"] = m_Struct.mode[0].mount_mode;
	m_obj["show_mode_0"] = m_Struct.mode[0].show_mode;
	m_obj["mount_mode_1"] = m_Struct.mode[1].mount_mode;
	m_obj["show_mode_1"] = m_Struct.mode[1].show_mode;
	m_obj["code_mode"] = m_Struct.code_mode;

	Json::Value root(Json::arrayValue);
	Json::Value posObj(Json::objectValue);
	for (int i=0; i<4;i++)
	{
		posObj["x"] = m_Struct.pos[i].x;
		posObj["y"] = m_Struct.pos[i].y;
		posObj["w"] = m_Struct.pos[i].w;
		posObj["h"] = m_Struct.pos[i].h;
		root.append(posObj);
	}

	m_obj["pos"] = root;

	m_obj["cur_pos"] = m_Struct.cur_pos;
	m_obj["bsave_pos"] = m_Struct.bsave_pos;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int FishEye::SaveAll(std::string strData)
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
		m_Struct.mode[0].mount_mode = obj["mount_mode_0"].asInt();
		m_Struct.mode[0].show_mode = obj["show_mode_0"].asInt();
		m_Struct.mode[1].mount_mode = obj["mount_mode_1"].asInt();
		m_Struct.mode[1].show_mode = obj["show_mode_1"].asInt();
		m_Struct.code_mode = obj["code_mode"].asInt();
		Json::Value root(Json::arrayValue);
		for(int i=0; i<4; i++)
		{
			m_Struct.pos[i].x = obj["pos"][i]["x"].asInt();
			m_Struct.pos[i].y = obj["pos"][i]["y"].asInt();
			m_Struct.pos[i].w = obj["pos"][i]["w"].asInt();
			m_Struct.pos[i].h = obj["pos"][i]["h"].asInt();
		}

		m_Struct.cur_pos = obj["cur_pos"].asInt();
		m_Struct.bsave_pos = obj["bsave_pos"].asInt();

	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType =MsgParamFishEye;
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