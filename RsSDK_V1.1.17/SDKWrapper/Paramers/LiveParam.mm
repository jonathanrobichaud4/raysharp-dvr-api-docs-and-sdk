#include "StdAfx.h"
#include "LiveParam.h"

static void RSNET_CALL ListParamOneCallback(void* data, void* userParam)
{
	LiveParam* pThis = (LiveParam*)userParam;
	memcpy(&pThis->m_Struct,data,sizeof(RSNet_SolePreviewCtrl_t));
}

static void RSNET_CALL ListParamAllCallback(void* data, void* userParam)
{
    LiveParam* pThis = (LiveParam*)userParam;
    RSNet_SolePreviewCtrl_t *channelOsd = (RSNet_SolePreviewCtrl_t *)data;
    pThis->m_vec.push_back(*channelOsd);
}

std::string LiveParam::QueryAll(std::string strData){
    std::string strRet = "err";

    RSNetQueryParamParam param;
    memset(&param, '\0', sizeof(param));

    m_vec.clear();

    ChannelParamReq req;
    TransformChannelParamReq_All(&req);

    param.ParamType = MsgParamPreviewCtrl;
    param.Req = &req;

    param.ListParamSize = sizeof(RSNet_SolePreviewCtrl_t);
    param.ListParamCallback = ListParamAllCallback;
    param.UserParam = this;

    if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
        return strRet;

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

void LiveParam::StructToJson(int n){
    m_obj.clear();
    m_obj["chn"] = n;
    m_obj["IntCrossSwitch"] = m_vec[n].IntCrossSwitch;
    m_obj["PreviewAudioEnable"] = m_vec[n].PreviewAudioEnable;
    m_obj["FloodLightMode"] = m_vec[n].FloodLightMode;
    m_obj["FloodLightValue"] = m_vec[n].FloodLightValue;
    m_obj["AudioAlarmSwitch"] = m_vec[n].AudioAlarmSwitch;
    m_obj["FlashLight"] = m_vec[n].FlashLight;
	m_obj["FlashFrequency"] = m_vec[n].StrobeFrequency;//对应预览上告INTF_PREVIEW_CHANGE_S结构体FlashFrequency的字段
    m_obj["LineOutVolume"] = m_vec[n].LineOutVolume;
}

std::string LiveParam::QueryOne(int n)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Struct, '\0', sizeof(RSNet_SolePreviewCtrl_t));

	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamPreviewCtrl;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SolePreviewCtrl_t);
	param.ListParamCallback = ListParamOneCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["chn"] = n;
	m_obj["IntCrossSwitch"] = m_Struct.IntCrossSwitch;
	m_obj["PreviewAudioEnable"] = m_Struct.PreviewAudioEnable;
	m_obj["FloodLightMode"] = m_Struct.FloodLightMode;
	m_obj["FloodLightValue"] = m_Struct.FloodLightValue;
	m_obj["AudioAlarmSwitch"] = m_Struct.AudioAlarmSwitch;
	m_obj["FlashLight"] = m_Struct.FlashLight;
	m_obj["FlashFrequency"] = m_Struct.StrobeFrequency;//对应预览上告INTF_PREVIEW_CHANGE_S结构体FlashFrequency的字段
	m_obj["LineOutVolume"] = m_Struct.LineOutVolume;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int LiveParam::SaveOne(int n,std::string strData)
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
	m_Struct.StructSize = sizeof(RSNet_SolePreviewCtrl_t);

	if(n <32){
		m_Struct.ChannelMask =  (0x1<<n);
	}else{
		m_Struct.ChannelMask =  0xFFFF0000 + n;
	}

	m_Struct.IntCrossSwitch = obj["IntCrossSwitch"].asInt();
	m_Struct.FloodLightMode = obj["FloodLightMode"].asInt();
	m_Struct.FloodLightValue = obj["FloodLightValue"].asInt();
	m_Struct.AudioAlarmSwitch = obj["AudioAlarmSwitch"].asInt();
	m_Struct.FlashLight = obj["FlashLight"].asInt();
	if(!obj["FlashFrequency"].isNull()){
		m_Struct.StrobeFrequency = obj["FlashFrequency"].asInt();//对应上告的FlashFrequency字段
	}
	m_Struct.LineOutVolume = obj["LineOutVolume"].asInt();
	if(!obj["OperBtn"].isNull()){
		m_Struct.OperBtn = obj["OperBtn"].asInt();
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamPreviewCtrl;
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