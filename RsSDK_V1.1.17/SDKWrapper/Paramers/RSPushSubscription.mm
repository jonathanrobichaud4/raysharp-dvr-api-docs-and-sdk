#include "StdAfx.h"
#include "RSPushSubscription.h"

RSPushSubscription::RSPushSubscription() {
    
}

RSPushSubscription::~RSPushSubscription() {
    
}

std::string RSPushSubscription::QueryAll(bool isDefault) {
    std::string strRet = "err";
    
    RSNet_VVPush_Subscrip pushSubscrip = {0};
    memset(&pushSubscrip, '\0', sizeof(RSNet_VVPush_Subscrip));
    pushSubscrip.StructSize = sizeof(RSNet_VVPush_Subscrip);
    
    RSNetQueryParamParamEx param;
    memset(&param, '\0', sizeof(param));
    param.Param = &pushSubscrip;
    param.ParamSize = sizeof(RSNet_VVPush_Subscrip);
    param.ParamType = MsgParamVVPush;
    
    if(isDefault)
    {
        if(!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param,MsgDefaultParam))
            return strRet;
    }else{
        if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
            return strRet;
    }
    
    m_obj.clear();
    m_obj["intellect"] = pushSubscrip.intellect;
    m_obj["hddPush"] = pushSubscrip.hddPush;
    m_obj["hddPushSub"] = pushSubscrip.hddPushSub;
    
    Json::Value motionAlarm;
    for (int i=0; i<8; i++)
    {
        motionAlarm.append(pushSubscrip.motionAlarm[i]);
    }
    m_obj["motionAlarm"] = motionAlarm;
    
    Json::Value pirAlarm;
    for (int i=0; i<8; i++)
    {
        pirAlarm.append(pushSubscrip.pirAlarm[i]);
    }
    m_obj["pirAlarm"] = pirAlarm;
    
    Json::Value videoLoss;
    for (int i=0; i<8; i++)
    {
        videoLoss.append(pushSubscrip.videoLoss[i]);
    }
    m_obj["videoLoss"] = videoLoss;
    
    Json::Value ioAlarm;
    for (int i=0; i<8; i++)
    {
        ioAlarm.append(pushSubscrip.ioAlarm[i]);
    }
    m_obj["ioAlarm"] = ioAlarm;
    
    Json::Value lowPower;
    for (int i=0; i<8; i++)
    {
        lowPower.append(pushSubscrip.lowPower[i]);
    }
    m_obj["lowPower"] = lowPower;
    
    Json::Value smartAlarm;
    for (int i=0; i<8; i++)
    {
        smartAlarm.append(pushSubscrip.smartAlarm[i]);
    }
    m_obj["smartAlarm"] = smartAlarm;
    
    Json::FastWriter writer;
    strRet = writer.write(m_obj);
    return strRet;
}

int RSPushSubscription::SaveAll(std::string strData) {
    if(strData == "null"){
        return false;
    }
    
    Json::Reader reader;
    Json::Value obj;
    if(!reader.parse(strData, obj)){
        return false;
    }
    
    RSNet_VVPush_Subscrip pushSubscrip = {0};
    memset(&pushSubscrip, '\0', sizeof(RSNet_VVPush_Subscrip));
    pushSubscrip.StructSize = sizeof(RSNet_VVPush_Subscrip);
    
    pushSubscrip.intellect = obj["intellect"].asInt();
    pushSubscrip.hddPush = obj["hddPush"].asInt();
    pushSubscrip.hddPushSub = obj["hddPushSub"].asInt();
    for (int i = 0; i < 8; i++) {
        pushSubscrip.motionAlarm[i] = obj["motionAlarm"][i].asInt();
    }
    for (int i = 0; i < 8; i++) {
        pushSubscrip.pirAlarm[i] = obj["pirAlarm"][i].asInt();
    }
    for (int i = 0; i < 8; i++) {
        pushSubscrip.videoLoss[i] = obj["videoLoss"][i].asInt();
    }
    for (int i = 0; i < 8; i++) {
        pushSubscrip.ioAlarm[i] = obj["ioAlarm"][i].asInt();
    }
    for (int i = 0; i < 8; i++) {
        pushSubscrip.lowPower[i] = obj["lowPower"][i].asInt();
    }
    for (int i = 0; i < 8; i++) {
        pushSubscrip.smartAlarm[i] = obj["smartAlarm"][i].asInt();
    }

    RSNetSetParamParam param;
    memset(&param, '\0', sizeof(param));
    param.ParamType = MsgParamVVPush;
    param.Param = &pushSubscrip;
    if(RSNetSetParam(m_pDevice->GetConnection(), &param))
    {
        return true;
    }
    
    return false;
}
