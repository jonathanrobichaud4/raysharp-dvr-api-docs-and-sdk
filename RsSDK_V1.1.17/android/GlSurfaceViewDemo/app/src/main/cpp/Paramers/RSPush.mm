#include "StdAfx.h"
#include "RSPush.h"

RSPush::RSPush() {

}

RSPush::~RSPush() {
    
}

int RSPush::SaveAll(std::string strData)
{
    Json::Reader reader;
    Json::Value root(Json::objectValue);

    if(!reader.parse(strData, root))
        return false;

    RSNet_PushInfo_t pushInfo = {0};
    pushInfo.StructSize = sizeof(RSNet_PushInfo_t);
    pushInfo.msg_type = root["msg type"].asInt();
    pushInfo.device_type = root["device type"].asInt();
    pushInfo.push_flag = root["push flag"].asInt();
    pushInfo.push_type = root["push type"].asInt();
    pushInfo.status = root["status"].asInt();
    const char *device_token = root["device token"].asCString();
    memcpy(pushInfo.device_token, device_token, strlen(device_token)<sizeof(pushInfo.device_token)?strlen(device_token):sizeof(pushInfo.device_token));
    
    const char *channel_id = root["channel id"].asCString();
    memcpy(pushInfo.channel_id, channel_id, strlen(channel_id)<sizeof(pushInfo.channel_id)?strlen(channel_id):sizeof(pushInfo.channel_id));
    
    const char *api_key = root["api key"].asCString();
    memcpy(pushInfo.api_key, api_key, strlen(api_key)<sizeof(pushInfo.api_key)?strlen(api_key):sizeof(pushInfo.api_key));

    const char *secret_key = root["secret key"].asCString();
    memcpy(pushInfo.secret_key, secret_key, strlen(secret_key)<sizeof(pushInfo.secret_key)?strlen(secret_key):sizeof(pushInfo.secret_key));

    const char *deviece_name = root["deviece name"].asCString();
    memcpy(pushInfo.deviece_name, deviece_name, strlen(deviece_name)<sizeof(pushInfo.deviece_name)?strlen(deviece_name):sizeof(pushInfo.deviece_name));

    const char *phone_name = root["phone name"].asCString();
    memcpy(pushInfo.phone_name, phone_name, strlen(phone_name)<sizeof(pushInfo.phone_name)?strlen(phone_name):sizeof(pushInfo.phone_name));
    
    const char *phone_type = root["phone type"].asCString();
    memcpy(pushInfo.phone_type, phone_type, strlen(phone_type)<sizeof(pushInfo.phone_type)?strlen(phone_type):sizeof(pushInfo.phone_type));
    
    int timeOut = root["time out"].asInt();
    
    RSNetSetParamParam param;
    memset(&param, '\0', sizeof(param));
    param.ParamType = MsgParamPushInfo;
    param.Param = &pushInfo;
    param.ListParams = NULL;
    param.ListParamNum = 0;
    param.TimeOut = timeOut;

    if (RSNetSetParam(m_pDevice->GetConnection(), &param))
    {
        return true;
    }
    
    return false;
}

