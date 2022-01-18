#pragma once

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel" : (uin32_t) 0 1 2 3 4 and so on
*                   "term"    : "preview"
*                             : "remote playback"
*                             : "download"
*                             : "ptz"
*/
static bool has_authority(CRSDevice* dev, const char* param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return false;
    
    LoginRsp* rsp = dev->GetLoginRsp();
    std::string term = value["term"].asString();
    uint32_t channel = value["channel"].asUInt();

    if (term == "preview") {
        if (channel < 32) {
            return (rsp->UserRight.UserPreview >> channel & 1) ? true : false;
        } else {
            int index = (channel - 32) / 32;
            int pos = channel % 32;
            return (rsp->PreviewChannel_EX[index] >> pos & 1) ? true : false;
        }
    } else if (term == "remote playback") {
        if (channel < 32) {
            return (rsp->UserRight.PlayBackChannel >> channel & 1) ? true : false;
        } else {
            int index = (channel - 32) / 32;
            int pos = channel % 32;
            return (rsp->PlayBackChannel_EX[index] >> pos & 1) ? true : false;
        }
    } else if (term == "download") {
        if (channel < 32) {
            return (rsp->UserRight.BackupChannel >> channel & 1) ? true : false;
        } else {
            int index = (channel - 32) / 32;
            int pos = channel % 32;
            return (rsp->BackupChannel_EX[index] >> pos & 1) ? true : false;
        }
    } else if (term == "ptz") {
        if (channel < 32) {
            return (rsp->UserRight.PtzControlChannel >> channel & 1) ? true : false;
        } else {
            int index = (channel - 32) / 32;
            int pos = channel % 32;
            return (rsp->PtzControlChannel_Ex[index] >> pos & 1) ? true : false;
        }
    }
    return false;
}

/*
* dev          ---> (device_id) see return value of <rs_create_device>
* param        ---> "channel" : (uin32_t) 0 1 2 3 4 and so on
*                   "term"    : "main stream"
*                             : "sub stream"
*                             : "mobile stream"
*                             : "ptz"
*                             : "talk to device" (don't need to fill "channel")
*                             : "talk to device analogue audio" (need to fill "channel", "channel" means which audio channel)
*                             : "talk to channel half duplex"
*                             : "talk to channel full duplex"
*                             : "fisheye"
*                             : "reverse playback"
*                             : "human face alarm"
*                             : "human face param"
*/
static bool has_ability(CRSDevice* dev, const char* param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return false;

    LoginRsp* rsp = dev->GetLoginRsp();
    std::string term = value["term"].asString();
    uint32_t channel = value["channel"].asUInt();
    RemoteChnStatusRpt channel_status_rpt;
    dev->get_channel_status_rpt(channel, channel_status_rpt);

    if (term == "main stream") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_MAINSTREAM & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return true;
        } else {
            return true;
        }
    } else if (term == "sub stream") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_SUBSTREAM & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return true;
        } else {
            return true;
        }
    } else if (term == "mobile stream") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_SNAPSTREAM & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return (rsp->PageControl2 >> PBIT6_E & 1) ? true : false; 
        } else {
            return true;
        }
    } else if (term == "ptz") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_PTZ & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return rsp->PtzHiddenFlag ? false : true;
        } else {
            return false;
        }
    } else if (term == "talk to device") {
        return rsp->DualtalkShowTag ? true : false;
    } else if (term == "talk to device analogue audio") {
        return (rsp->DualtalkShowTag && rsp->TalkMode == 4) ? true : false; // max audio channel number = rsp->AudioNum;
    } else if (term == "talk to channel half duplex") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_TALK_HALF & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return (rsp->TalkMode == 1 || rsp->TalkMode == 3) ? true : false;
        } else {
            return false;
        }
    } else if (term == "talk to channel full duplex") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_TALK_FULL & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return (rsp->TalkMode == 2 || rsp->TalkMode == 3) ? true : false;
        } else {
            return false;
        }
    } else if (term == "fisheye") {
        if (dev->GetDeviceType() == DEV_NVR || dev->GetDeviceType() == DEV_HDVR) {
            return (channel_status_rpt.ChnInfo.Abilities >> ABILITY_TYPE_FISH_EYE & 1) ? true : false;
        } else if (dev->GetDeviceType() == DEV_IPC) {
            return rsp->FishEyeIpcCap.isFishEye ? true : false;
        } else {
            return false;
        }
    } else if (term == "reverse playback") {
        if (rsp->ControlBit2 & (0x1 << COBIT1_E))
            return true;
        else
            return false;
    } else if (term == "human face alarm") {
        BYTE ControlBitArray[8*32] = {0};
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 32; j++)
                ControlBitArray[i*8+j] = rsp->ControlBitArray[i] & (0x1 << j);
        }
        if (ControlBitArray[CoBitAry_6])
            return true;
        else
            return false;
    } else if (term == "human face param") {
        BYTE ControlBitArray[8*32] = {0};
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 32; j++)
                ControlBitArray[i*8+j] = rsp->ControlBitArray[i] & (0x1 << j);
        }
        if (ControlBitArray[CoBitAry_7])
            return true;
        else
            return false;
    }
    return false;
}
