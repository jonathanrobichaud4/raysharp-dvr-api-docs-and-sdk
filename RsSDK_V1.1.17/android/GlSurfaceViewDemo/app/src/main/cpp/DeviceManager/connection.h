#pragma once
#include <algorithm>
#include "md5.h"

typedef struct {
    char h;
    char r;
    char i;
    char m;
    char c;
    char l;
    char o;
    char p;
    char s;
    char pir;
    char v;
    char reserve[63];
}ALARM_FLAG;

typedef struct {
    char motion;
    char io;
    char pir;
    char reserve[64];
}ALARM_FLAG_TEMP;

class connection {
public:
    connection() 
        : conn_(NULL)
        , ip_or_id_("")
        , port_(0)
        , disable_auto_send_msg_(false)
        , channel_status_rpt_(NULL)
        , alarm_flag_(NULL)
        , alarm_status_changed_(false) 
        , base_running_(false)
        , conn_cb_(NULL)
        , alarm_cb_(NULL)
        , alarm_cb_ex_(NULL)
        , user_param_(NULL)
    {

    }

    ~connection() {
        SAFE_DELETEA(channel_status_rpt_);
        SAFE_DELETEA(alarm_flag_);
    }

    RSNetConnection get_connection() { return conn_;     }
    std::string     get_ip_or_id()   { return ip_or_id_; }
    std::string     get_password()   { return password_; }
    int             get_port()       { return port_;     }
    void set_connection(RSNetConnection conn) { conn_ = conn; }

    LoginRsp* get_login_rsp_struct() { return &rsp_;                    }
    int       get_device_type()      { return rsp_.DevType >> 40 & 0xf; }
    int       get_channel_num()      { return rsp_.ChannelNum;          }
    int       get_analog_num()       { return rsp_.AnalogChNum;         }
    int       get_is_wireless()      { return rsp_.ControlBit2 >> 3 & 0x1;}

    void get_channel_status_rpt(int channel, RemoteChnStatusRpt& channel_status_rpt) {
        memset(&channel_status_rpt, 0, sizeof(channel_status_rpt));
        if (channel_status_rpt_ && channel < get_channel_num())
            memcpy(&channel_status_rpt, &channel_status_rpt_[channel], sizeof(channel_status_rpt));
    }

    static Json::Value ChnStatusRptToJson(DevAllStatusRpt *pDevAlStatRpt) {
        Json::Value tempData;
        char time[30] = {0};
#ifdef _MSC_VER
        sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pDevAlStatRpt->AlarmTime.Year,
            pDevAlStatRpt->AlarmTime.Month, pDevAlStatRpt->AlarmTime.Day,
            pDevAlStatRpt->AlarmTime.Hour, pDevAlStatRpt->AlarmTime.Minute,
            pDevAlStatRpt->AlarmTime.Second);
#else
        sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pDevAlStatRpt->AlarmTime.Year,
            pDevAlStatRpt->AlarmTime.Month, pDevAlStatRpt->AlarmTime.Day,
            pDevAlStatRpt->AlarmTime.Hour, pDevAlStatRpt->AlarmTime.Minute,
            pDevAlStatRpt->AlarmTime.Second);
#endif
        tempData["AlarmTime"] = time;
        tempData["RecordEnable"] = pDevAlStatRpt->RecordEnable;
        tempData["RecordStatus"] = pDevAlStatRpt->RecordStatus;
        tempData["MotionEnable"] = pDevAlStatRpt->MotionEnable;
        tempData["MotionStatus"] = pDevAlStatRpt->MotionStatus;
        for(int i=0; i<8; i++){
            tempData["MotionStatusExt"].append(pDevAlStatRpt->MotionStatusExt[i]);
        }
        tempData["IOEnable"] = pDevAlStatRpt->IOEnable;
        tempData["IOStatus"] = pDevAlStatRpt->IOStatus;
        for(int i=0; i<8; i++){
            tempData["IOStatusExt"].append(pDevAlStatRpt->IOStatusExt[i]);
        }
        tempData["VLossStatus"] = pDevAlStatRpt->VLossStatus;

        for(int i = 0;i < 8;++i)
        {
            tempData["HddStatus"].append(pDevAlStatRpt->HddStatus[i]);
        }

        for (int i=0; i<32; ++i)
        {
            tempData["RecordAllStatus"].append(pDevAlStatRpt->RecordAllStatus[i]);
        }

        for(int i=0; i<8; ++i)
        {
            Json::Value arrObj(Json::arrayValue);
            for (int j=0; j<32; ++j)
            {
                arrObj.append(pDevAlStatRpt->RecordAllStatusExt[i][j]);
            }
            tempData["RecordAllStatusExt"].append(arrObj);
        }
        tempData["PirEnable"] = pDevAlStatRpt->PirEnable;
        tempData["PirStatus"] = pDevAlStatRpt->PirStatus;
        for(int i = 0;i < 8;++i)
        {
            tempData["PIRStatusExt"].append(pDevAlStatRpt->PIRStatusExt[i]);
        }

        for(int i = 0;i < 8;++i)
        {
            tempData["SmokeStatusExt"].append(pDevAlStatRpt->SmokeStatusExt[i]);
        }

        tempData["FtpNewVersFlag"] = pDevAlStatRpt->FtpNewVersFlag;
        tempData["FtpNewVersFlag"] = pDevAlStatRpt->FtpNewVersFlag;
        tempData["AudioStatus"] = pDevAlStatRpt->AudioStatus;

        tempData["IntelligentStatus"] = pDevAlStatRpt->IntelligentStatus;
        tempData["CameraCoverSwitch"] = pDevAlStatRpt->CameraCoverSwitch;
        tempData["CameraCoverState"] = pDevAlStatRpt->CameraCoverState;
        for(int i = 0;i < 256;++i)
        {
            if(i<128)
            {
                tempData["PageIntelligentChn"].append(pDevAlStatRpt->PageIntelligentChn[i]);
                tempData["PageIntelligentChnExt"].append(pDevAlStatRpt->PageIntelligentChnExt[i]);
            }else{
                tempData["PageIntelligentChn"].append(0);
                tempData["PageIntelligentChnExt"].append(0);
            }
            tempData["InputNum"].append(pDevAlStatRpt->InputNum[i]);
            tempData["OutputNum"].append(pDevAlStatRpt->OutputNum[i]);
        }
        tempData["IntelligentChnStatus"] = pDevAlStatRpt->IntelligentChnStatus;
        for(int i=0; i<6; i++){
            tempData["IntelligentChnStatusExt"].append(pDevAlStatRpt->IntelligentChnStatusExt[i]);
        }
        tempData["zeroChSwitch"] = pDevAlStatRpt->zeroChSwitch;

        return tempData;
    }

    static Json::Value RemoteChnStatusRptToJson(DevChnInfo pDevChnInfo) {
        Json::Value tempData;

        ULONGLONG type = pDevChnInfo.DevType;
        UINT nDevTypeH = type>>32;
        UINT nDevTypeL = type&0xffffffff;

        tempData["DevTypeH"] = nDevTypeH;
        tempData["DevTypeL"] = nDevTypeL;
        tempData["CurChnName"] = pDevChnInfo.CurChnName;
        tempData["CurChnState"] = pDevChnInfo.CurChnState;
        tempData["RecState"] = pDevChnInfo.RecState;
        tempData["CurRecType"] = pDevChnInfo.CurRecType;
        tempData["MDState"] = pDevChnInfo.MDState;
        tempData["IOState"] = pDevChnInfo.IOState;
        tempData["VLossState"] = pDevChnInfo.VLossState;
        tempData["HddState"] = pDevChnInfo.HddState;
        tempData["MDSchedule"] = pDevChnInfo.MDSchedule;
        tempData["AlarmSchedule"] = pDevChnInfo.AlarmSchedule;
        tempData["ChannelNum"] = pDevChnInfo.ChannelNum;
        tempData["IPCDevTypeFlag"] = pDevChnInfo.IPCDevTypeFlag;
        tempData["ProtocolType"] = pDevChnInfo.ProtocolType;
        tempData["Abilities"] = pDevChnInfo.Abilities;
        tempData["AbilitiesEx"] = pDevChnInfo.AbilitiesEx;
        tempData["chnMode"] = pDevChnInfo.chnMode;
        tempData["chnName_EX"] = pDevChnInfo.chnName_EX;

        return tempData;
    }

    static void RSNET_CALL RSNetConnectionCallbackFun(WPARAM wparam, LPARAM lparam) {
        connection* _this = (connection*)(lparam);
        if (_this)
            _this->RSNetConnectionCallbackFun((int64_t)wparam);
    }

    static void RSNET_CALL RSNetAlarmRptCallbackFun(WORD type, void* data, UINT size, void* userParam) {
        connection* _this = (connection*)(userParam);
        if (_this)
            _this->RSNetAlarmRptCallbackFun(type, data, size);
    }

    void RSNetConnectionCallbackFun(int64_t msg) {
        if (base_running_ && conn_cb_) {
            std::string err;
            switch (msg)
            {
            case RSNetMsgConnectStart:
                err = "connecting";
                break;
            case RSNetMsgConnectFail:
            case RSNetMsgConnectClosed:
            case RSNetMsgConnectStop:
                err = "close";
                break;
            case RSNetMsgLoginSuccess:
                InitDeviceAndChannelInfo();
                err = "success";
                break;
            case RSNetMsgLoginUserLogined:
                err = "user logined";
                break;
            case RSNetMsgLoginNoUserName:
            case RSNetMsgLoginPasswordError:
                err = "user or password error";
                break;
            case RSNetMsgLoginNoRight:
                err = "user no right";
                break;
            case RSNetMsgIpFilter:
                err = "ip filter";
                break;
            case RSNetMsgOverMaxUser:
                err = "max user";
                break;
            case RSNetMsgLoginUserDisable:
                err = "user disabled";
                break;
            case RSNetMsgLoginForceChangePWD:
                err = "force change password";
                break;
            case RSNetMsgLoginForceCloseBrowser:
                err = "force close brower";
                break;
            case RSNetMsgLoginForbidIP:
                err = "forbidden ip";
                break;
            case RSNetTypeP2P:
                err = "p2p mode";
                break;
            case RSNetTypeP2PRelay:
                err = "relay mode";
                break;
            default:
                err = "";
                break;
            }

            if (!err.empty()) {
                Json::Value value;
                value["status"] = err;
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);

                conn_cb_(result.c_str(), user_param_);
            }

            int device_type = get_device_type();
            if (alarm_cb_ && msg == RSNetMsgLoginSuccess && device_type != DEV_NVR && device_type != DEV_HDVR) {
                Json::Value value(Json::arrayValue);
                int channel_num = get_channel_num();
                for (int i = 0; i < channel_num; i++) {
                    Json::Value temp;
                    temp["online"] = true;
                    value.append(temp);
                    channel_online_status_[i] = 1;
                }

                if (!value.empty()) {
                    Json::StreamWriterBuilder writer;
                    std::string result = Json::writeString(writer, value);

                    alarm_cb_("RSSDKChannelStatus", result.c_str(), user_param_);
                }
            }
        }
    }

    void RSNetAlarmRptCallbackFun(WORD type, void* data, UINT size) {
        if (base_running_ && alarm_cb_) {
            process_alarm_to_json(type, data, size);
            process_channel_status(type, data, size);
            process_alarm_tag(type, data, size);
        }

        if (base_running_ && alarm_cb_ex_)
            alarm_cb_ex_(type, data, size, user_param_);
    }

    rs_error_code login(const device_login_param* param) {
        logout();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param->param, &value, &err)){
            sdk_wrapper_log("[%s] call <connection login> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        disable_auto_send_msg_ = value["disable auto send msg"].asBool();
        conn_cb_ = param->conn_cb;
        alarm_cb_ = param->alarm_cb;
        alarm_cb_ex_ = param->alarm_cb_ex;
        user_param_ = param->user_param;

        std::string str_ip = value["ip or id"].asString();
        int port = value["media port"].asInt();
        ip_or_id_ = MD5(str_ip).hexdigest().substr(0, 16);

        memset(&channel_online_status_[0], 0, sizeof(channel_online_status_));
        memset(&rsp_, 0, sizeof(rsp_));
        RSNetConnectionParamEx _param = {0};
        _param.IP = str_ip.c_str();
        _param.Port = port;
        std::string user = value["user"].asString();
        _param.UserName = user.c_str();
        std::string password = value["password"].asString();
        password_ = password;
        _param.Password = password.c_str();
        _param.Wnd = NULL;
        _param.Message = 0;
        _param.UserParam = this;
        _param.AutoReconnect = true;
        _param.AlarmRptCallback = RSNetAlarmRptCallbackFun;
        _param.AlarmRptDesired = true;
        _param.ConnCallback = RSNetConnectionCallbackFun;

        int login_type = LOGIN_TYPE_IP;
        std::string p2p_type = value["p2p type"].asString();
        if (p2p_type == "ip")
            login_type = LOGIN_TYPE_IP;
        else if (p2p_type == "id")
            login_type = LOGIN_TYPE_ID;
        else if (p2p_type == "tutk")
            login_type = LOGIN_TYPE_TUTK_ID;
        else if (p2p_type == "lorex")
            login_type = LOGIN_TYPE_LOREX_ID;
        else if (p2p_type == "vv")
            login_type = LOGIN_TYPE_VVSEE_ID;
        else if (p2p_type == "rsvv")
            login_type = LOGIN_TYPE_RSVV_ID;
        else if (p2p_type == "samsung")
            login_type = LOGIN_TYPE_SAMSUNG_DDNS_ID;
        else if (p2p_type == "urmet ur")
            login_type = LOGIN_TYPE_URMET_ID_V2;
        else if (p2p_type == "livezon")
            login_type = LOGIN_TYPE_LIVEZON_ID;
		else if(p2p_type == "qsee")
			login_type = LOGIN_TYPE_Q_SEEQRVIEW_ID;
        else if (p2p_type == "ddns")
            login_type = LOGIN_TYPE_DDNS;
        _param.nLoginType = login_type;

        std::string ddns_id_server_addr = value["ddns id server addr"].asString();
        _param.IDServerName = ddns_id_server_addr.empty() ? NULL : ddns_id_server_addr.c_str();

        uint8_t type = 0;
        std::string oem_type = value["oem type"].asString();
        if (oem_type == "default")
            type = 0;
        else if (oem_type == "tev")
            type = 1;
        else if (oem_type == "zip")
            type = 2;
        else if (oem_type == "cdoubles")
            type = 3;
        else if (oem_type == "raydin")
            type = 4;
        else if (oem_type == "hello cctv")
            type = 5;
        else if (oem_type == "optimus")
            type = 6;
        else if (oem_type == "hdpro")
            type = 7;
        _param.LoginClientType = type;
        conn_ = RSNetConnectionStartEx(&_param);

        base_running_ = conn_ ? true : false;
        sdk_wrapper_log("[%s] call <connection login> result:%s\n", ip_or_id_.c_str(), conn_ ? "success" : "fail");
        return conn_ ? rs_success : rs_fail;
    }

    rs_error_code logout() {
        if (!base_running_ && !conn_)
            return rs_success;

        base_running_ = false;

        if (conn_) {
            RSNetConnectionStop(&conn_);
            conn_ = NULL;
        }

        conn_ = NULL;
        SAFE_DELETEA(channel_status_rpt_);
        SAFE_DELETEA(alarm_flag_);
        alarm_status_changed_ = false; 
        conn_cb_ = NULL;
        alarm_cb_ = NULL;
        alarm_cb_ex_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[%s] call <connection logout> result:success\n", ip_or_id_.c_str());
        return rs_success;
    }

    void reset_connection() {
        if (conn_) {
            RSNetResetConnection(conn_);
            sdk_wrapper_log("[%s] call <connection reset_connection> result:success\n", ip_or_id_.c_str());
        }
    }

    rs_error_code send_simple_command(const simple_command_param* param) {
        if (conn_) {
            RSNetCmdParam temp_param;
            memset(&temp_param, 0, sizeof(temp_param));
            temp_param.ParamMainType = param->main_msg;
            temp_param.ParamSubType = param->sub_msg;
            temp_param.Param = param->param;
            temp_param.ParamSize = param->param_size;
            RSNetSimpleCmd(conn_,&temp_param);
            return rs_success;
        }
        return rs_fail;
    }

    session_id start_async_query_json(const async_query_json_param* param) {
        if (conn_) {
            QueryParamJsonInfo temp_param;
            memset(&temp_param, 0, sizeof(temp_param));

            temp_param.main_msg_type = param->main_msg;
            temp_param.param = param->param;
            temp_param.param_size = param->param_size;
            temp_param.callback = param->callback;
            temp_param.user_param = param->user_param;
            temp_param.erase_after_callback = param->erase_after_callback;

            return (session_id)RSNetAsyncStartQueryParamJson(conn_, &temp_param);
        }
        return NULL;
    }

    session_id start_async_set_json(const async_set_json_param* param) {
        if (conn_) {
            SetParamJsonInfo temp_param;
            memset(&temp_param, 0, sizeof(temp_param));

            temp_param.main_msg_type = param->main_msg;
            temp_param.param = param->param;
            temp_param.param_size = param->param_size;
            temp_param.callback = (RSNetSetParamJsonCallback)param->callback;
            temp_param.user_param = param->user_param;
            temp_param.erase_after_callback = param->erase_after_callback;

            return (session_id)RSNetAsyncStartSetParamJson(conn_, &temp_param);
        }
        return NULL;
    }

    rs_error_code stop_async_json(session_id sess) {
        if (conn_) {
            long seq = (long)(sess);
            RSNetAsyncStopQueryParamJson(conn_, seq);
            return rs_success;
        }
        return rs_fail;
    }

public:
    void InitDeviceAndChannelInfo() {
        memset(&channel_online_status_[0], 0, sizeof(channel_online_status_));
        memset(&rsp_,0,sizeof(rsp_));
        memset(&device_status_rpt_, 0 ,sizeof(DevAllStatusRpt));
        
        if (!disable_auto_send_msg_ && RSNetGetDevInfo(conn_, &rsp_, sizeof(rsp_))) {
            SAFE_DELETEA(alarm_flag_);
            alarm_flag_ = new ALARM_FLAG[get_channel_num()];
            memset(alarm_flag_, 0, sizeof(ALARM_FLAG) * get_channel_num());
            memset(&alarm_flag_temp_, 0, sizeof(alarm_flag_temp_));

            int device_type = rsp_.DevType >> 40 & 0xf;
            if (device_type == DEV_DVR) {
                ;
            } else if (device_type == DEV_NVR || device_type == DEV_HDVR) {
                RSNetCmdParam param;
                memset(&param, 0, sizeof(param));
                param.ParamMainType = MsgStatusRequest;
                param.ParamSubType = MsgRemoteCHStatusReq;
                RSNetSimpleCmd(conn_,&param);

                memset(&param, 0, sizeof(param));
                param.ParamMainType = MsgStatusRequest;
                param.ParamSubType = MsgDevAllStatusReq;
                RSNetSimpleCmd(conn_,&param);
            } else if (device_type == DEV_IPC) {
                RSNetCmdParam param;
                memset(&param, 0, sizeof(param));
                param.ParamMainType = MsgStatusRequest;
                param.ParamSubType = MsgDevAllStatusReq;
                RSNetSimpleCmd(conn_,&param);
            }

            if(rsp_.IntelligentAnalysis) {
                RSNetCmdParam param;
                memset(&param, 0, sizeof(param));
                param.ParamMainType = MsgStatusRequest;

                param.ParamSubType = MsgPeaAlarmReq;  
                RSNetSimpleCmd(conn_,&param);

                param.ParamSubType = MsgGoodsLostAlarmReq;  
                RSNetSimpleCmd(conn_,&param);
            }
        }
    }

    std::string get_login_rsp() {
        Json::Value value(Json::objectValue);
        unsigned long long ullDeviceType = rsp_.DevType;
        unsigned int nDevTypeH = ullDeviceType >> 32;
        unsigned int nDevTypeL = ullDeviceType & 0xFFFFFFFF;

        value["HighType"] = nDevTypeH;
        value["LowType"] = nDevTypeL;
        value["DevVer"] = rsp_.DevVer;
        value["DeviceName"] = rsp_.DeviceName;    
        value["MacAddr"] = rsp_.MacAddr;
        value["DeviceID"] = rsp_.DeviceID;

        value["UserSetRight"] = rsp_.UserRight.UserSetRight;
        value["PreviewChannel"] = rsp_.UserRight.PreviewChannel;
        value["PlayBackChannel"] = rsp_.UserRight.PlayBackChannel;
        value["BackupChannel"] = rsp_.UserRight.BackupChannel;
        value["PtzControlChannel"] = rsp_.UserRight.PtzControlChannel;
        value["UserPreview"] = rsp_.UserRight.UserPreview;
        value["UserPlayBack"] = rsp_.UserRight.UserPlayBack;
        value["UserBackup"] = rsp_.UserRight.UserBackup;
        value["UserPtzControl"] = rsp_.UserRight.UserPtzControl;

        value["UserKey"] = rsp_.UserKey;
        value["TotalFPS"] = rsp_.TotalFPS_D1;
        value["ChannelNum"] = rsp_.ChannelNum;
        value["VideoFormat"] = rsp_.VideoFormat;

        value["AlarmInNum"] = rsp_.AlarmInNum;
        value["AlarmOutNum"] = rsp_.AlarmOutNum;
        value["AIAnalyzeCap"] = rsp_.AIAnalyzeCap;
        value["AIAnalyzeChannels"] = rsp_.AIAnalyzeChannels;

        value["SerialNum"] = rsp_.SerialNum;
        value["ISAdmin"] = rsp_.ISAdmin;
        value["AudioNum"] = rsp_.AudioNum;
        value["ResolutioFrameFix"] = rsp_.ResolutioFrameFix;

        value["PreviewOff"] = rsp_.PreviewOff;
        value["VideoCoverNum"] = rsp_.VideoCoverNum;
        value["SupportSpot"] = rsp_.SupportSpot;
        value["SubStreamMin"] = rsp_.SubStreamMin;

        value["SubStreamMax"] = rsp_.SubStreamMax;
        value["PlatformSupport"] = rsp_.PlatformSupport;
        value["ChnInfoSize"] = rsp_.ChnInfoSize;

        value["SubStreamRestrict"] = rsp_.SubStreamRestrict;
        value["DualtalkShowTag"] = rsp_.DualtalkShowTag;
        value["TalkMode"] = rsp_.TalkMode;
        value["RouterShowTag"] = rsp_.RouterShowTag;
        value["LANShowTag"] = rsp_.LanShowTag;

        value["PlatFormShowTag"] = rsp_.PlatFormShowTag;
        value["ProductName"] = rsp_.ProductName;
        value["PlatFormSwitch"] = rsp_.PlatFormSwitch;

        value["VideoActivateSwitch"] = rsp_.VideoActivateSwitch;
        value["MotionMode"] = rsp_.MotionMode;
        value["ResolutionMode"] = rsp_.ResolutionMode;
        value["HidePhonePage"] = rsp_.HidePhonePage;

        value["UpgradeType"] = rsp_.UpgradeType;
        value["ElecLockFlag"] = rsp_.ElecLockFlag;
        value["TotalFPS_960"] = rsp_.TotalFPS_960;

        value["WifiStatus"] = rsp_.WifiStatus;
        value["RtspPageEnable"] = rsp_.RtspPageEnable;
        value["FtpPageFlag"] = rsp_.FtpPageFlag;
        value["c32PasswordFlag"] = rsp_.c32PasswordFlag;
        value["UrmetDevStatusFlag"] = rsp_.UrmetDevStatusFlag;
        value["FileSystemFlag"] = rsp_.FileSystemFlag;
        value["KguardP2pUidFlag"] = rsp_.KguardP2pUidFlag;
        value["EmailFlagSwitch"] = rsp_.EmailFlagSwitch;

        value["EmailScheduleFlag"] = rsp_.EmailScheduleFlag;
        value["PtzHiddenFlag"] = rsp_.PtzHiddenFlag;
        value["c3GFlagSwitch"] = rsp_.c3GFlagSwitch;
        value["c3GFlag"] = rsp_.c3GFlag;
        value["RecordTypeFlag"] = rsp_.RecordTypeFlag;
        value["SystemIDCtrl"] = rsp_.SystemIDCtrl;
        value["FtpPcSendFlag"] = rsp_.FtpPcSendFlag;
        value["CloudStorageFlag"] = rsp_.CloudStorageFlag;

        value["AutoMaintenance"] = rsp_.AutoMaintenance;
        value["CloudSGSerSwitch"] = rsp_.CloudSGSerSwitch;
        value["ShieldColorSetFlag"] = rsp_.ShieldColorSetFlag;
        value["IntelligentAnalysis"] = rsp_.IntelligentAnalysis;
        value["RemoteUpgradeMode"] = rsp_.RemoteUpgradeMode;

        value["CloudeSGType"] = rsp_.CloudeSGType;
        value["CloudeStorageMode"] = rsp_.CloudeStorageMode;
        value["VBRFlag"] = rsp_.VBRFlag;
        value["RemoteFtpUpgradeSupport"] = rsp_.RemoteFtpUpgradeSupport;
        value["MainStreamMutex"] = rsp_.MainStreamMutex;

        value["NewAapterQTParamFlag"] = rsp_.NewAapterQTParamFlag;
        value["PtzSupported"] = rsp_.PtzSupported;
        value["PasswordSwitch"] = rsp_.PasswordSwitch;
        value["NvrFlag"] = rsp_.NvrFlag;
        value["MaintainUserEnabled"] = rsp_.MaintainUserEnabled;

        value["MaxPOENum"] = rsp_.MaxPOENum;
        value["UiType"] = rsp_.UiType;
        value["ChipNum"] = rsp_.ChipNum;
        value["ProtocolType"] = rsp_.ProtocolType;
        value["PageControl"] = rsp_.PageControl;
        value["PreviewNum"] = rsp_.PreviewNum;
        value["AnalogChNum"] = rsp_.AnalogChNum;
        value["GetAlarmChns"] = rsp_.GetAlarmChns;
        value["NewEmailTest"] = rsp_.NewEmailTest;
        value["UserNameFlag"] = rsp_.c32UserNameFlag;

        value["eSATAEnabled"] = rsp_.eSATAEnabled;
        value["RemoteSearchLogFlag"] = rsp_.RemoteSearchLogFlag;//1:show Dev_log page
        value["hybirdDVRFlag"] = rsp_.hybirdDVRFlag;
        value["customProtolFlag"] = rsp_.customProtolFlag;
        value["showVersionFlag"] = rsp_.showVersionFlag;

        value["CoaxialFlag"] = rsp_.CoaxialFlag;
        value["DefualtStream"] = rsp_.DefualtStream;
        value["PageControl2"] = rsp_.PageControl2;

        value["HkDomeFlag"] = rsp_.HKDemoFlag;
        value["PirAreaMode"] = rsp_.PirAreaMode;

        Json::Value arrValue;
        for(int i=0; i<8; i++) {
            arrValue.append(rsp_.PreviewChannel_EX[i]);
        }
        value["PreviewChannel_EX"] = arrValue;

        arrValue = Json::nullValue;
        for(int i=0; i<8; i++) {
            arrValue.append(rsp_.PlayBackChannel_EX[i]);
        }
        value["PlayBackChannel_EX"] = arrValue;

        arrValue = Json::nullValue;
        for(int i=0; i<8; i++) {
            arrValue.append(rsp_.BackupChannel_EX[i]);
        }
        value["BackupChannel_EX"] = arrValue;

        arrValue = Json::nullValue;
        for(int i=0; i<8; i++) {
            arrValue.append(rsp_.PtzControlChannel_Ex[i]);
        }
        value["PtzControlChannel_Ex"] = arrValue;
        
        arrValue = Json::nullValue;
        for(int i=0; i<8; i++) {
            arrValue.append(rsp_.ControlBitArray[i]);
        }
        value["ControlBitArray"] = arrValue;

        Json::Value fishEyeValue;
        fishEyeValue["isFishEye"] = rsp_.FishEyeIpcCap.isFishEye;
        fishEyeValue["isSupportHard_dec"] = rsp_.FishEyeIpcCap.isSupportHard_dec;
        fishEyeValue["curShowMode"] = rsp_.FishEyeIpcCap.curShowMode;
        fishEyeValue["curStreamNum"] = rsp_.FishEyeIpcCap.curStreamNum;
        fishEyeValue["fishEyeflag"] = rsp_.FishEyeIpcCap.fishEyeflag;
        value["FishEye"] = fishEyeValue;

        Json::Value autoFocusValue;
        autoFocusValue["PTZVersion"] = rsp_.AutoFocusDefault.PTZVersion;
        autoFocusValue["mixZoomPosition"] = rsp_.AutoFocusDefault.mixZoomPosition;
        autoFocusValue["maxZoomPosition"] = rsp_.AutoFocusDefault.maxZoomPosition;
        autoFocusValue["mixFocusPosition"] = rsp_.AutoFocusDefault.mixFocusPosition;
        autoFocusValue["maxFocusPosition"] = rsp_.AutoFocusDefault.maxFocusPosition;
        value["autoFocus"] = autoFocusValue;
        value["ZeroChFlag"] = rsp_.ZeroChFlag;
        value["ControlBit"] = rsp_.ControlBit;
        value["ControlBit2"] = rsp_.ControlBit2;
        value["MaxCloudVideoUploadNum"] = rsp_.MaxCloudVideoUploadNum;
        char first_char = rsp_.p2pId[0];
        if ((first_char > 47 && first_char < 58) || \
            (first_char > 64 && first_char < 91) || \
            (first_char > 96 && first_char < 123))
            value["p2pId"] = rsp_.p2pId;
        else
            value["p2pId"] = "";
        value["PushType"] = rsp_.PushType;
        value["PushInfoType"] = rsp_.PushInfoType;
        
        Json::StreamWriterBuilder writer;
        std::string result = Json::writeString(writer, value);
        return result;
    }

    int get_device_playback_capability() {
        return rsp_.DevPlayBackCap;
    }

    bool support_reverse_playback() {
        if (rsp_.ControlBit2 & (0x1 << COBIT1_E))
            return true;
        else
            return false;
    }

private:
    void process_alarm_to_json(WORD type, void* data, UINT size) {
        unsigned int nSize= 0;
        int nDeviceType = get_device_type();

        std::string alarm_type;
        Json::Value Data;
        Json::Value tempData;

        switch (type)
        {
        case MsgVLossAlarm:
            {
                alarm_type = "MsgVLossAlarm";
                if(nDeviceType == DEV_HDVR)
                {
                    RsNetAlarmRpt *pRpt = new RsNetAlarmRpt;
                    nSize = sizeof(RsNetAlarmRpt);
                    memset(pRpt, 0, nSize);
                    memcpy(pRpt,data,nSize <= size ? nSize:size);

                    Json::Value arrChnLoss(Json::arrayValue);
                    int chnNum = get_channel_num();

                    for(int i=0; i<chnNum; i++)
                    {
                        if(i < 32)
                        {
                            if(pRpt->Channel >> i & 1)
                            {
                                Json::Value temp(Json::objectValue);
                                temp["ch"] = i;
                                temp["state"] = ((pRpt->Status >> i) & 1);

                                arrChnLoss.append(temp);
                            }
                        }
                        else
                        {
                            if(pRpt->Channel_EX[(i - 32)/32] >> (i-32)%32 & 1)
                            {
                                Json::Value temp(Json::objectValue);
                                temp["ch"] = i;
                                temp["state"] = ((pRpt->Status_EX[(i - 32)/32] >> (i-32)%32) & 1);

                                arrChnLoss.append(temp);
                            }
                        }
                    }
                    Data = arrChnLoss;

                    SAFE_DELETE(pRpt);
                }

                RSNetCmdParam param;
                memset(&param, 0, sizeof(param));
                param.ParamMainType = MsgStatusRequest;
                param.ParamSubType = MsgDevAllStatusReq;
                RSNetSimpleCmd(get_connection(), &param);
            }
            break;
        case MsgDevStatReport:
            {
                alarm_type = "MsgDevStatReport";
                LoginRsp *pLoginRsp = get_login_rsp_struct();
                if(pLoginRsp->GetAlarmChns==1){
                    RsNetAlarmRpt* pAlarmRpt = new RsNetAlarmRpt;
                    nSize = sizeof(RsNetAlarmRpt);
                    memset(pAlarmRpt, 0, nSize);
                    memcpy(pAlarmRpt, data, nSize <= size ? nSize:size);
                    if(1)
                    {
                        Data["Channel"] = pAlarmRpt->Channel;
                        Data["Status"] = pAlarmRpt->Status;
                        char time[20] = {0};
#ifdef _MSC_VER
                        sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pAlarmRpt->AlarmTime.Year,
                            pAlarmRpt->AlarmTime.Month, pAlarmRpt->AlarmTime.Day,
                            pAlarmRpt->AlarmTime.Hour, pAlarmRpt->AlarmTime.Minute,
                            pAlarmRpt->AlarmTime.Second);
#else
                        sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pAlarmRpt->AlarmTime.Year,
                            pAlarmRpt->AlarmTime.Month, pAlarmRpt->AlarmTime.Day,
                            pAlarmRpt->AlarmTime.Hour, pAlarmRpt->AlarmTime.Minute,
                            pAlarmRpt->AlarmTime.Second);
#endif
                        Data["AlarmTime"] = time;

                        Data["RecState"] = pAlarmRpt->RecState;
                        Data["CurRecType"] = pAlarmRpt->CurRecType;
                        Data["Schedule"] = pAlarmRpt->Schedule;
                        Data["RecEnable"] = pAlarmRpt->RecEnable;
                        Data["ProtocolType"] = pAlarmRpt->ProtocolType;
                        Data["Abilities"] = pAlarmRpt->Abilities;
                        Data["AbilitiesEx"] = pAlarmRpt->AbilitiesEx;
                        Data["IPCDevTypeFlag"] = pAlarmRpt->IPCDevTypeFlag;
                        Data["InputNum"] = pAlarmRpt->InputNum;
                        Data["OutputNum"] = pAlarmRpt->OutputNum;
                        Data["chnMode"] = pAlarmRpt->bChnMode;
                        SAFE_DELETE(pAlarmRpt);
                    }
                }
                else
                {
                    DevStatRpt* DevStatus = new DevStatRpt;
                    nSize = sizeof(DevStatRpt);
                    memset(DevStatus, 0, nSize);
                    memcpy(DevStatus, data, nSize <= size ? nSize:size);
                    if(get_device_type() == DEV_NVR)
                    {
                        tempData["Channel"] = DevStatus->Channel;
                        tempData["Status"] = DevStatus->Status;
                        char time[20] = {0};
#ifdef _MSC_VER
                        sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",DevStatus->AlarmTime.Year,
                            DevStatus->AlarmTime.Month, DevStatus->AlarmTime.Day,
                            DevStatus->AlarmTime.Hour, DevStatus->AlarmTime.Minute,
                            DevStatus->AlarmTime.Second);
#else
                        sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",DevStatus->AlarmTime.Year,
                            DevStatus->AlarmTime.Month, DevStatus->AlarmTime.Day,
                            DevStatus->AlarmTime.Hour, DevStatus->AlarmTime.Minute,
                            DevStatus->AlarmTime.Second);
#endif
                        tempData["AlarmTime"] = time;

                        tempData["ProtocolType"] = DevStatus->ProtocolType;
                        tempData["Abilities"] = DevStatus->Abilities;
                        tempData["AbilitiesEx"] = DevStatus->AbilitiesEx;
                        tempData["IPCDevTypeFlag"] = DevStatus->IPCDevTypeFlag;
                        Data["Data"] = tempData;
                        SAFE_DELETE(DevStatus);
                    }
                }
            }
            break;
        case MsgMotionAlarm:
        case MsgIOAlarm:
        case MsgIntelIpcPeaAlarm:
        case MsgIpcOSCAlarm:
        case MsgIntelIpcPeaAreaAlarm:
        case MsgAlarmIntManage:
        case MsgPirAlarm:
            {
                switch (type)
                {
                case MsgMotionAlarm:
                    alarm_type = "MsgMotionAlarm";
                    break;
                case MsgIOAlarm:
                    alarm_type = "MsgIOAlarm";
                    break;
                case MsgIntelIpcPeaAlarm:
                    alarm_type = "MsgIntelIpcPeaAlarm";
                    break;
                case MsgIpcOSCAlarm:
                    alarm_type = "MsgIpcOSCAlarm";
                    break;
                case MsgIntelIpcPeaAreaAlarm:
                    alarm_type = "MsgIntelIpcPeaAreaAlarm";
                    break;
                case MsgAlarmIntManage:
                    alarm_type = "MsgAlarmIntManage";
                    break;
                case MsgPirAlarm:
                    alarm_type = "MsgPirAlarm";
                    break;
                default:
                    alarm_type = "";
                    break;
                }
                if(nDeviceType == DEV_IPC || (get_is_wireless() && alarm_type == "MsgPirAlarm"))
                {
                    LoginRsp *pLoginRsp = get_login_rsp_struct();
                    if (pLoginRsp->GetAlarmChns==1)
                    {
                        RsNetAlarmRpt* pDevMoiton = new RsNetAlarmRpt;
                        nSize = sizeof(RsNetAlarmRpt);
                        memset(pDevMoiton, 0, nSize);
                        memcpy(pDevMoiton, data, nSize <= size ? nSize:size);

                        tempData["Channel"] = pDevMoiton->Channel;
                        tempData["Status"] = pDevMoiton->Status;
                        char time[20] = {0};
#ifdef _MSC_VER
                        sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pDevMoiton->AlarmTime.Year,
                            pDevMoiton->AlarmTime.Month, pDevMoiton->AlarmTime.Day,
                            pDevMoiton->AlarmTime.Hour, pDevMoiton->AlarmTime.Minute,
                            pDevMoiton->AlarmTime.Second);
#else
                        sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pDevMoiton->AlarmTime.Year,
                            pDevMoiton->AlarmTime.Month, pDevMoiton->AlarmTime.Day,
                            pDevMoiton->AlarmTime.Hour, pDevMoiton->AlarmTime.Minute,
                            pDevMoiton->AlarmTime.Second);
#endif
                        tempData["AlarmTime"] = time;

                        tempData["ProtocolType"] = pDevMoiton->ProtocolType;
                        tempData["Abilities"] = pDevMoiton->Abilities;
                        tempData["AbilitiesEx"] = pDevMoiton->AbilitiesEx;
                        tempData["AlarmType"] = pDevMoiton->AlarmType;
                        tempData["IPCDevTypeFlag"] = pDevMoiton->IPCDevTypeFlag;
                        tempData["MsgValidFlagIPCWeb"] = pDevMoiton->MsgValidFlagIPCWeb;
                        tempData["bBoxEnable"] = pDevMoiton->bBoxEnable;
                        tempData["bBoxDisplay"] = pDevMoiton->bBoxDisplay;

                        Data = tempData;
                        SAFE_DELETE(pDevMoiton);
                    }
                    else
                    {
                        DevStatRpt* pDevMoiton = new DevStatRpt;
                        nSize = sizeof(DevStatRpt);
                        memset(pDevMoiton, 0, nSize);
                        memcpy(pDevMoiton, data, nSize <= size ? nSize:size);

                        tempData["Channel"] = pDevMoiton->Channel;
                        tempData["Status"] = pDevMoiton->Status;
                        char time[20] = {0};
#ifdef _MSC_VER
                        sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pDevMoiton->AlarmTime.Year,
                            pDevMoiton->AlarmTime.Month, pDevMoiton->AlarmTime.Day,
                            pDevMoiton->AlarmTime.Hour, pDevMoiton->AlarmTime.Minute,
                            pDevMoiton->AlarmTime.Second);
#else
                        sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pDevMoiton->AlarmTime.Year,
                            pDevMoiton->AlarmTime.Month, pDevMoiton->AlarmTime.Day,
                            pDevMoiton->AlarmTime.Hour, pDevMoiton->AlarmTime.Minute,
                            pDevMoiton->AlarmTime.Second);
#endif
                        tempData["AlarmTime"] = time;

                        tempData["ProtocolType"] = pDevMoiton->ProtocolType;
                        tempData["AbilitiesEx"] = pDevMoiton->AbilitiesEx;
                        tempData["AlarmType"] = pDevMoiton->AlarmType;
                        tempData["IPCDevTypeFlag"] = pDevMoiton->IPCDevTypeFlag;
                        tempData["MsgValidFlagIPCWeb"] = pDevMoiton->MsgValidFlagIPCWeb;

                        Data = tempData;
                        SAFE_DELETE(pDevMoiton);
                    }
                }
                else
                {
                    return;
                }
            }
            break;
        case MsgDevChModeReport:
            {
                RsNetAlarmRpt* alarm_rpt = new RsNetAlarmRpt;
                nSize = sizeof(RsNetAlarmRpt);
                memset(alarm_rpt, 0, nSize);
                memcpy(alarm_rpt, data, nSize <= size ? nSize:size);
                for(int i = 0; i < get_channel_num(); i++){
                    if(i < 32){
                        if(alarm_rpt->Channel >> i & 0x1){
                            tempData["Channel"] = i;
                            tempData["bChnMode"] = alarm_rpt->bChnMode;
                        }
                    }else{
                        UINT nIndex = (i - 32) / 32;
                        UINT pos = (i - 32) % 32;
                        if(alarm_rpt->Channel_EX[nIndex] >> pos & 0x1){
                            tempData["Channel"] = i;
                            tempData["bChnMode"] = alarm_rpt->bChnMode;
                        }
                    }
                }
                Data = tempData;
                SAFE_DELETE(alarm_rpt);
            }
                break;
        case MsgIntelPeaAlarm:
            {
                alarm_type = "MsgIntelPeaAlarm";
                SolePEAAlarmRpt* pDevPea = new SolePEAAlarmRpt;
                nSize = sizeof(SolePEAAlarmRpt);
                memset(pDevPea, 0, nSize);
                memcpy(pDevPea, data, nSize <= size ? nSize:size);


                SAFE_DELETE(pDevPea);
            }
            break;
        case MsgOscRuleAlarm:
            {
                alarm_type = "MsgOscRuleAlarm";
                SoleGoodsLostMsg* pDevGoods = new SoleGoodsLostMsg;
                nSize = sizeof(SoleGoodsLostMsg);
                memset(pDevGoods, 0, nSize);
                memcpy(pDevGoods, data, nSize <= size ? nSize:size);


                SAFE_DELETE(pDevGoods);
            }
            break;
        case MsgHddStatusReport:
            {
                alarm_type = "MsgHddStatusReport";
                HddStatusRpt* pDevHdd = new HddStatusRpt;
                nSize = sizeof(HddStatusRpt);
                memset(pDevHdd, 0, nSize);
                memcpy(pDevHdd, data, nSize <= size ? nSize:size);

                tempData["HddStatus"]  = pDevHdd->HddStatus;
                tempData["HddSN"]  = pDevHdd->HddSN;

                char time[20] = {0};
#ifdef _MSC_VER
                sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pDevHdd->AlarmTime.Year,
                    pDevHdd->AlarmTime.Month, pDevHdd->AlarmTime.Day,
                    pDevHdd->AlarmTime.Hour, pDevHdd->AlarmTime.Minute,
                    pDevHdd->AlarmTime.Second);
#else
                sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pDevHdd->AlarmTime.Year,
                    pDevHdd->AlarmTime.Month, pDevHdd->AlarmTime.Day,
                    pDevHdd->AlarmTime.Hour, pDevHdd->AlarmTime.Minute,
                    pDevHdd->AlarmTime.Second);
#endif
                tempData["AlarmTime"] = time;

                Data = tempData;
                SAFE_DELETE(pDevHdd);
            }
            break;
        case MsgRecordStatusReport:
            {
                alarm_type = "MsgRecordStatusReport";
                RecordStatusRpt* pDevRecord = new RecordStatusRpt;
                nSize = sizeof(RecordStatusRpt);
                memset(pDevRecord, 0, nSize);
                memcpy(pDevRecord, data, nSize <= size ? nSize:size);

                tempData["Type"]  = pDevRecord->Type;

                char time[20] = {0};
#ifdef _MSC_VER
                sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pDevRecord->AlarmTime.Year,
                    pDevRecord->AlarmTime.Month, pDevRecord->AlarmTime.Day,
                    pDevRecord->AlarmTime.Hour, pDevRecord->AlarmTime.Minute,
                    pDevRecord->AlarmTime.Second);
#else
                sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pDevRecord->AlarmTime.Year,
                    pDevRecord->AlarmTime.Month, pDevRecord->AlarmTime.Day,
                    pDevRecord->AlarmTime.Hour, pDevRecord->AlarmTime.Minute,
                    pDevRecord->AlarmTime.Second);
#endif
                tempData["AlarmTime"] = time;

                tempData["ChannelNum"]  = pDevRecord->ChannelNum;
                tempData["RecordStatus"]  = pDevRecord->RecordStatus;
                tempData["AllChanRecState"]  = pDevRecord->AllChanRecState;
                Data = tempData;
                SAFE_DELETE(pDevRecord);
            }
            break;
        case MsgDevAllStatusReq:
            {
                alarm_type = "MsgDevAllStatusReq";
                DevAllStatusRpt *pDevAlStatRpt = &device_status_rpt_;
                memset(pDevAlStatRpt, 0, sizeof(DevAllStatusRpt));

                nSize = sizeof(DevAllStatusRpt);
                memset(pDevAlStatRpt, 0, nSize);
                memcpy(pDevAlStatRpt,data,nSize <= size ? nSize:size);

                Data = ChnStatusRptToJson(pDevAlStatRpt);

                if(nDeviceType == DEV_HDVR) 
                {
                    Data["OldVer"] = (char*)(pDevAlStatRpt->HddSN[0]);
                    Data["NewVer"] = (char*)(pDevAlStatRpt->HddSN[1]);
                    Data["DevType"] = (char*)(pDevAlStatRpt->HddSN[2]);
                    Data["VersFlag"] = (int)pDevAlStatRpt->FtpNewVersFlag;
                }
            }
            break;
        case MsgRemoteCHStatusReq:
            {
                alarm_type = "MsgRemoteCHStatusReq";
                unsigned char* pDataHead = (unsigned char*)data;
                int nStructSize = *(int*)pDataHead;
                int ChNum = get_channel_num();

                SAFE_DELETEA(channel_status_rpt_);
                channel_status_rpt_ = new RemoteChnStatusRpt[ChNum];
                RemoteChnStatusRpt *pChnstatus = channel_status_rpt_; 
                memset(pChnstatus, 0, sizeof(RemoteChnStatusRpt)*ChNum);
                for(int i = 0; i<ChNum; ++i)
                {
                    memcpy(pChnstatus+i, pDataHead+nStructSize*i, nStructSize>sizeof(RemoteChnStatusRpt)?sizeof(RemoteChnStatusRpt):nStructSize);
                }

                Json::Value temp(Json::objectValue);
                for (int i=0; i<get_channel_num(); ++i)
                {
                    temp = RemoteChnStatusRptToJson(pChnstatus[i].ChnInfo);
                    tempData.append(temp);
                }

                Data = tempData;
            }
            break;
        case MsgAlarmFishEyeIpcStat:
            {
                alarm_type = "MsgAlarmFishEyeIpcStat";
                FishEyeIpcStatusRpt* pFishEyeData = new FishEyeIpcStatusRpt;
                nSize = sizeof(FishEyeIpcStatusRpt);
                memset(pFishEyeData, 0, nSize);
                memcpy(pFishEyeData, data, nSize <= size ? nSize:size);
                Json::Value temp(Json::objectValue);
                temp["curStreamNum"] = pFishEyeData->curStreamNum;
                Data = temp;
                SAFE_DELETE(pFishEyeData);
            }
            break;
        case MsgVideoHideAlarm:
            {
                alarm_type = "MsgVideoHideAlarm";
                VideoHideAlarmRpt* pVideoHideData = new VideoHideAlarmRpt;
                nSize = sizeof(VideoHideAlarmRpt);
                memset(pVideoHideData, 0, nSize);
                memcpy(pVideoHideData, data, nSize <= size ? nSize:size);
                Json::Value tempData(Json::objectValue);
                tempData["Channel"] = pVideoHideData->Channel;
                tempData["Status"] = pVideoHideData->Status;
                char time[20] = {0};
#ifdef _MSC_VER
                sprintf_s(time, sizeof(time), "%04d-%02d-%02d-%02d-%02d-%02d",pVideoHideData->AlarmTime.Year,
                    pVideoHideData->AlarmTime.Month, pVideoHideData->AlarmTime.Day,
                    pVideoHideData->AlarmTime.Hour, pVideoHideData->AlarmTime.Minute,
                    pVideoHideData->AlarmTime.Second);
#else
                sprintf(time, "%04d-%02d-%02d-%02d-%02d-%02d",pVideoHideData->AlarmTime.Year,
                    pVideoHideData->AlarmTime.Month, pVideoHideData->AlarmTime.Day,
                    pVideoHideData->AlarmTime.Hour, pVideoHideData->AlarmTime.Minute,
                    pVideoHideData->AlarmTime.Second);
#endif
                tempData["AlarmTime"] = time;

                tempData["RecState"] = pVideoHideData->RecState;
                Data = tempData;
                SAFE_DELETE(pVideoHideData);
            }
            break;
        case MsgFtpUpgradeAlarm:
            {
                alarm_type = "MsgFtpUpgradeAlarm";
                FtpUpgradeRpt FtpUpgrade = {0};
                memcpy(&FtpUpgrade, data, sizeof(FtpUpgradeRpt) <= size ? sizeof(FtpUpgradeRpt):size);

                Data["pos"] = FtpUpgrade.UpgradeProcess;
                Data["status"] = FtpUpgrade.UpgradeStatus;
            }
            break;
        case RSNetMsgLoginForbidIP:
            {
                alarm_type = "RSNetMsgLoginForbidIP";
                LoginRep_Time loginTime = {0};
                memcpy(&loginTime, data, sizeof(LoginRep_Time) <= size ? sizeof(LoginRep_Time):size);

                Data["times"] = loginTime.times;
                break;
            }
        case MsgAlarmPTZIpcStat:
            {
                alarm_type = "MsgAlarmPTZIpcStat";
                AUTOFOCUS_CONTROL_S* pAutoFocusData = new AUTOFOCUS_CONTROL_S;
                nSize = sizeof(AUTOFOCUS_CONTROL_S);
                memset(pAutoFocusData, 0, nSize);
                memcpy(pAutoFocusData, data, nSize <= size ? nSize:size);
                Json::Value temp(Json::objectValue);
                temp["ChannelMask"] = pAutoFocusData->ChannelMask;
                temp["curZoomValue"] = pAutoFocusData->curZoomValue;
                temp["zoomStep"] = pAutoFocusData->zoomStep;
                temp["curFocusValue"] = pAutoFocusData->curFocusValue;
                temp["focusStep"] = pAutoFocusData->focusStep;
                temp["autoFocusState"] = pAutoFocusData->autoFocusState;
                Data = temp;
                SAFE_DELETE(pAutoFocusData);
            }
            break;
        case MsgDevPreviewChangeReport:
            {
                alarm_type = "MsgDevPreviewChangeReport";
                INTF_PREVIEW_CHANGE_S* pPreviewParamData = new INTF_PREVIEW_CHANGE_S;
                nSize = sizeof(INTF_PREVIEW_CHANGE_S);
                memset(pPreviewParamData, 0, nSize);
                memcpy(pPreviewParamData, data, nSize <= size ? nSize:size);
                Json::Value temp(Json::objectValue);
                temp["chn"] = pPreviewParamData->chn;
                temp["FloodLightMode"] = pPreviewParamData->FloodLightMode;
                temp["FloodLightValue"] = pPreviewParamData->FloodLightValue;
                temp["AudioAlarmSwitch"] = pPreviewParamData->AudioAlarmSwitch;
                temp["FlashLight"] = pPreviewParamData->FlashLight;
                temp["LineOutVolume"] = pPreviewParamData->LineOutVolume;
                Data = temp;
                SAFE_DELETE(pPreviewParamData);
            }
            break;
        case MsgChNameChange:
            {
                alarm_type = "MsgChNameChange";
                INTF_NAME_CHANGE_S* pNameChangeData = new INTF_NAME_CHANGE_S;
                nSize = sizeof(INTF_NAME_CHANGE_S);
                memset(pNameChangeData, 0, nSize);
                memcpy(pNameChangeData, data, nSize <= size ? nSize:size);
                Json::Value temp(Json::objectValue);
                temp["chn"] = pNameChangeData->chn;
                temp["Name"] = pNameChangeData->Name;
                Data = temp;
                SAFE_DELETE(pNameChangeData);
            }
            break;
        case MsgDevNameChange:
            {
                alarm_type = "MsgDevNameChange";
                INTF_NAME_CHANGE_S* pNameChangeData = new INTF_NAME_CHANGE_S;
                nSize = sizeof(INTF_NAME_CHANGE_S);
                memset(pNameChangeData, 0, nSize);
                memcpy(pNameChangeData, data, nSize <= size ? nSize:size);
                Json::Value temp(Json::objectValue);
                temp["Name"] = pNameChangeData->Name;
                Data = temp;
                SAFE_DELETE(pNameChangeData);
            }
                break;
        case MsgDevParamChangeReport:
            {
                alarm_type = "MsgDevParamChangeReport";
                INTF_DEVPARAM_CHANGE_S *pDevparamChangeData = new INTF_DEVPARAM_CHANGE_S;
                nSize = sizeof(INTF_DEVPARAM_CHANGE_S);
                memset(pDevparamChangeData, 0, nSize);
                memcpy(pDevparamChangeData, data, nSize < size ? nSize : size);
                Json::Value temp(Json::objectValue);
                temp["chn"] = pDevparamChangeData->chn;
                temp["pageType"] = pDevparamChangeData->pageType;
                Data = temp;
                SAFE_DELETE(pDevparamChangeData);
                break;
            }
        default:
            alarm_type = "";
            break;
        }

        if (!alarm_type.empty() && !Data.empty() && base_running_) {
            Json::StreamWriterBuilder writer;
            std::string result = Json::writeString(writer, Data);

            alarm_cb_(alarm_type.c_str(), result.c_str(), user_param_);
        }
    }

    void process_channel_status(WORD type, void* data, size_t size) {
        if (type == MsgRemoteCHStatusReq && channel_status_rpt_) {
            Json::Value value(Json::arrayValue);
            int channel_num = get_channel_num();
            for (int i = 0; i < channel_num; i++) {
                Json::Value temp;
                if (channel_status_rpt_[i].ChnInfo.CurChnState == 2 && channel_status_rpt_[i].ChnInfo.VLossState != 1) {
                    channel_online_status_[i] = 1;
                    temp["online"] = true;
                } else {
                    channel_online_status_[i] = 0;
                    temp["online"] = false;
                }
                value.append(temp);
            }

            if (!value.empty() && base_running_) {
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);

                alarm_cb_("RSSDKChannelStatus", result.c_str(), user_param_);
            }
        } else if(type == MsgVLossAlarm) {
            RsNetAlarmRpt alarm_rpt = {0};
            memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));

            bool channel_status_has_changed = false;
            Json::Value value(Json::arrayValue);
            for (int i = 0; i < get_channel_num(); i++) {
                int nIndex, pos;
                if (i <= 31) {

                } else {
                    nIndex = (int)((i - 32) / 32);
                    pos = (i - 32) % 32;
                }

                UINT Channel = 0;
                UINT Status = 0;
                if (i <= 31) {
                    Channel = alarm_rpt.Channel >> i & 1;
                    Status = alarm_rpt.Status >> i & 1;
                } else {
                    Channel = alarm_rpt.Channel_EX[nIndex] >> pos & 1;
                    Status = alarm_rpt.Status_EX[nIndex] >> pos & 1;
                }

                if (Channel) {
                    if (Status)
                        channel_online_status_[i] = 0;
                    else
                        channel_online_status_[i] = 1;
                    channel_status_has_changed = true;
                }

                Json::Value temp(Json::objectValue);
                if (channel_online_status_[i])
                    temp["online"] = true;
                else
                    temp["online"] = false;
                value.append(temp);
            }

            if (!value.empty() && channel_status_has_changed && base_running_) {
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);

                alarm_cb_("RSSDKChannelStatus", result.c_str(), user_param_);
            }
        }
    }

    void process_alarm_tag(WORD type, void* data, size_t size) {
        alarm_status_changed_ = false;

        switch (type)
        {
        case MsgDevAllStatusReq:
            {
                if (rsp_.PageControl >> BIT18_E & 1) {//Open video identification plate side						
                    if (device_status_rpt_.HddStatus[0] != 1) { //red H
                        SetPreviewRecordStatus(0, MsgHddStatusReport, true, 255, 0, 0);
                    } else {
                        SetPreviewRecordStatus(0, MsgHddStatusReport, false, 0, 0, 0);
                    }
                    for (int i = 0; i < get_channel_num(); ++i) {
                        alarm_flag_[i].m = 0;
                        alarm_flag_[i].i = 0;
                        alarm_flag_[i].r = 0;
                        alarm_flag_[i].s = 0;
                        alarm_flag_[i].pir = 0;

                        int nIndex, pos;
                        if (i <= 31) {

                        } else {
                            nIndex = (int)((i - 32) / 32);
                            pos = (i - 32) % 32;
                        }

                        UINT RedM = 0;//red M
                        if (i <= 31) {
                            RedM = device_status_rpt_.RecordAllStatus[i];
                        } else {
                            RedM = device_status_rpt_.RecordAllStatusExt[nIndex][pos];
                        }
                        if (RedM == RECORD_STATUS_MOTION_E
                            || RedM == RECORD_STATUS_MOTION_IO_E
                            || RedM == RECORD_STATUS_MOTION_PIR_E
                            || RedM == RECORD_STATUS_MOTION_PIR_IO_E
                            || RedM == RECORD_STATUS_MOTION_INTELLIGENTALLE_E
                            || RedM == RECORD_STATUS_MOTION_IO_INTELLIGENTALLE_E
                            || RedM == RECORD_STATUS_MOTION_PIR_INTELLIGENTALL_E
                            || RedM == RECORD_STATUS_MOTION_PIR_IO_INTELLIGENTALL_E
                            ) 
                        {
                            SetPreviewRecordStatus(i, MsgMotionAlarm, true, 255, 0, 0);
                        }

                        UINT RedI = 0;//red I
                        if (i <= 31) {
                            RedI = device_status_rpt_.RecordAllStatus[i];
                        } else {
                            RedI = device_status_rpt_.RecordAllStatusExt[nIndex][pos];
                        }
                        if (RedI == RECORD_STATUS_IOALARM_E
                            || RedI == RECORD_STATUS_MOTION_IO_E
                            || RedI == RECORD_STATUS_MOTION_PIR_IO_E
                            || RedI == RECORD_STATUS_PIR_IO_E
                            || RedI == RECORD_STATUS_IO_INTELLIGENTALL_E
                            || RedI == RECORD_STATUS_MOTION_IO_INTELLIGENTALLE_E
                            || RedI == RECORD_STATUS_PIR_IO_INTELLIGENTALL_E
                            || RedI == RECORD_STATUS_MOTION_PIR_IO_INTELLIGENTALL_E
                            ) 
                        {
                            SetPreviewRecordStatus(i, MsgIOAlarm, true, 255, 0, 0);
                        }

                        UINT RedR = 0;//red R
                        if (i <= 31) {
                            RedR = device_status_rpt_.RecordAllStatus[i];
                        } else {
                            RedR = device_status_rpt_.RecordAllStatusExt[nIndex][pos];
                        }
                        if (RedR == RECORD_STATUS_NORMAL_E) {
                            SetPreviewRecordStatus(i, MsgRecordStatusReport, true, 255, 0, 0);
                        }

                        UINT GreenM = 0;//green M
                        if (i <= 31) {
                            GreenM = device_status_rpt_.MotionStatus >> i & 1;
                        } else {
                            GreenM = device_status_rpt_.MotionStatusExt[nIndex] >> pos & 1;
                        }
                        if (GreenM == 1) {
                            SetPreviewRecordStatus(i, MsgMotionAlarm, true, 0, 255, 0);
                        }

                        UINT GreenPir = 0;//green pir
                        if (i <= 31) {
                            GreenPir = device_status_rpt_.PirStatus >> i & 1;
                        } else {
                            GreenPir = device_status_rpt_.PIRStatusExt[nIndex] >> pos & 1;
                        }
                        if (GreenPir == 1) {
                            SetPreviewRecordStatus(i, MsgPirAlarm, true, 0, 255, 0);
                        }

                        UINT GreenI = 0;//green I
                        if (i <= 31) {
                            GreenI = device_status_rpt_.IOStatus >> i & 1;
                        } else {
                            GreenI = device_status_rpt_.IOStatusExt[nIndex] >> pos & 1;
                        }
                        if (GreenI == 1) {
                            SetPreviewRecordStatus(i, MsgIOAlarm, true, 0, 255, 0);
                        }

                        UINT GreenS = 0;//green S
                        if (i <= 31) {
                            GreenS = device_status_rpt_.IntelligentChnStatus >> i & 1;
                        } else {
                            GreenS = device_status_rpt_.IntelligentChnStatusExt[nIndex] >> pos & 1;
                        }
                        if (GreenS == 1) {
                            SetPreviewRecordStatus(i, MsgAlarmIntManage, true, 0, 255, 0);
                        }

                        UINT RedS = 0;//red S
                        if (i <= 31) {
                            RedS = device_status_rpt_.RecordAllStatus[i];
                        } else {
                            RedS = device_status_rpt_.RecordAllStatusExt[nIndex][pos];
                        }
                        if (RedS == RECORD_STATUS_INTELLIGENTALL_E
                            || RedS == RECORD_STATUS_IO_INTELLIGENTALL_E
                            || RedS == RECORD_STATUS_MOTION_INTELLIGENTALLE_E
                            || RedS == RECORD_STATUS_MOTION_IO_INTELLIGENTALLE_E
                            || RedS == RECORD_STATUS_PIR_INTELLIGENTALL_E
                            || RedS == RECORD_STATUS_MOTION_PIR_INTELLIGENTALL_E
                            || RedS == RECORD_STATUS_PIR_IO_INTELLIGENTALL_E
                            || RedS == RECORD_STATUS_MOTION_PIR_IO_INTELLIGENTALL_E
                            ) 
                        {//red S
                            SetPreviewRecordStatus(i, MsgAlarmIntManage, true, 255, 0, 0);
                        } else {
                            if (device_status_rpt_.IntelligentStatus > 0) {
                                SetPreviewRecordStatus(i, MsgAlarmIntManage, true, 0, 255, 0);
                            }
                        }

                        UINT RedPIR = 0;//red PIR
                        if (i <= 31) {
                            RedPIR = device_status_rpt_.RecordAllStatus[i];
                        } else {
                            RedPIR = device_status_rpt_.RecordAllStatusExt[nIndex][pos];
                        }
                        if (RedPIR == RECORD_STATUS_PIR_E
                            || RedPIR == RECORD_STATUS_MOTION_PIR_E
                            || RedPIR == RECORD_STATUS_MOTION_PIR_IO_E
                            || RedPIR == RECORD_STATUS_PIR_IO_E
                            || RedPIR == RECORD_STATUS_PIR_INTELLIGENTALL_E
                            || RedPIR == RECORD_STATUS_PIR_IO_INTELLIGENTALL_E
                            || RedPIR == RECORD_STATUS_MOTION_PIR_INTELLIGENTALL_E
                            || RedPIR == RECORD_STATUS_MOTION_PIR_IO_INTELLIGENTALL_E
                            ) 
                        {
                            SetPreviewRecordStatus(i, MsgPirAlarm, true, 255, 0, 0);
                        }
                    }
                }
            }
            break;
        case MsgMotionAlarm:
            {
                if (get_device_type() == DEV_IPC) {
                    if (alarm_flag_temp_.motion != 1) {
                        int channel = 0;
                        int status = 0;
                        if (rsp_.GetAlarmChns == 1) {
                            RsNetAlarmRpt alarm_rpt = {0};
                            memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                            channel = alarm_rpt.Channel;
                            status = alarm_rpt.Status;
                        } else {
                            DevStatRpt dev_status_rpt = {0};
                            memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                            channel = dev_status_rpt.Channel;
                            status = dev_status_rpt.Status;
                        }

                        SetPreviewRecordStatus(getIpcCh(channel), MsgMotionAlarm, false, 0, 0, 0);
                        if (status == 1) {//green M
                            alarm_flag_[getIpcCh(channel)].m = 1;
                            SetPreviewRecordStatus(getIpcCh(channel), MsgMotionAlarm, true, 0, 255, 0);
                        }
                    }
                }
            }
            break;
        case MsgIOAlarm:
            {
                if (get_device_type() == DEV_IPC) {
                    if (alarm_flag_temp_.io != 1) {
                        int channel = 0;
                        int status = 0;
                        if (rsp_.GetAlarmChns == 1) {
                            RsNetAlarmRpt alarm_rpt = {0};
                            memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                            channel = alarm_rpt.Channel;
                            status = alarm_rpt.Status;
                        } else {
                            DevStatRpt dev_status_rpt = {0};
                            memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                            channel = dev_status_rpt.Channel;
                            status = dev_status_rpt.Status;
                        }

                        SetPreviewRecordStatus(getIpcCh(channel), MsgIOAlarm, false, 0, 0, 0);
                        if (status == 1) {//green I
                            SetPreviewRecordStatus(getIpcCh(channel), MsgIOAlarm, true, 0, 255, 0);
                        }
                    }
                }
            }
            break;
        case MsgIntelIpcPeaAlarm:
            {
                int channel = 0;
                int status = 0;
                if (rsp_.GetAlarmChns == 1) {
                    RsNetAlarmRpt alarm_rpt = {0};
                    memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                    channel = alarm_rpt.Channel;
                    status = alarm_rpt.Status;
                } else {
                    DevStatRpt dev_status_rpt = {0};
                    memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                    channel = dev_status_rpt.Channel;
                    status = dev_status_rpt.Status;
                }

                SetPreviewRecordStatus(getIpcCh(channel), MsgIntelIpcPeaAlarm, false, 0, 0, 0);
                if (status == 1) {//green L
                    SetPreviewRecordStatus(getIpcCh(channel), MsgIntelIpcPeaAlarm, true, 0, 255, 0);
                }
            }
            break;
        case MsgIpcOSCAlarm:
            {
                int channel = 0;
                int status = 0;
                if (rsp_.GetAlarmChns == 1) {
                    RsNetAlarmRpt alarm_rpt = {0};
                    memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                    channel = alarm_rpt.Channel;
                    status = alarm_rpt.Status;
                } else {
                    DevStatRpt dev_status_rpt = {0};
                    memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                    channel = dev_status_rpt.Channel;
                    status = dev_status_rpt.Status;
                }

                SetPreviewRecordStatus(getIpcCh(channel), MsgIpcOSCAlarm, false, 0, 0, 0);
                if (status == 1) {//green O
                    SetPreviewRecordStatus(getIpcCh(channel), MsgIpcOSCAlarm, true, 0, 255, 0);
                }
            }
            break;
        case MsgIntelIpcPeaAreaAlarm:
            {
                int channel = 0;
                int status = 0;
                if (rsp_.GetAlarmChns == 1) {
                    RsNetAlarmRpt alarm_rpt = {0};
                    memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                    channel = alarm_rpt.Channel;
                    status = alarm_rpt.Status;
                } else {
                    DevStatRpt dev_status_rpt = {0};
                    memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                    channel = dev_status_rpt.Channel;
                    status = dev_status_rpt.Status;
                }

                SetPreviewRecordStatus(getIpcCh(channel), MsgIntelIpcPeaAreaAlarm, false, 0, 0, 0);
                if (status == 1) {//green P
                    SetPreviewRecordStatus(getIpcCh(channel), MsgIntelIpcPeaAreaAlarm, true, 0, 255, 0);
                }
            }
            break;
        case MsgAlarmIntManage:
            {
                if (get_device_type() == DEV_IPC) {
                    int channel = 0;
                    int status = 0;
                    int msg_valid_flag_ipc_web = 0;
                    if (rsp_.GetAlarmChns == 1) {
                        RsNetAlarmRpt alarm_rpt = {0};
                        memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                        channel = alarm_rpt.Channel;
                        status = alarm_rpt.Status;
                        msg_valid_flag_ipc_web = alarm_rpt.MsgValidFlagIPCWeb;
                    } else {
                        DevStatRpt dev_status_rpt = {0};
                        memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                        channel = dev_status_rpt.Channel;
                        status = dev_status_rpt.Status;
                    }

                    if (msg_valid_flag_ipc_web == 1) {
                    } else {
                        SetPreviewRecordStatus(getIpcCh(channel), MsgAlarmIntManage, false, 0, 0, 0);
                        if (status == 1) {//green S
                            SetPreviewRecordStatus(getIpcCh(channel), MsgAlarmIntManage, true, 0, 255, 0);
                        }
                    }
                }
            }
            break;
        case MsgPirAlarm:
            {
                if (get_device_type() == DEV_IPC) {
                    if (alarm_flag_temp_.pir != 1) {
                        int channel = 0;
                        int status = 0;
                        if (rsp_.GetAlarmChns == 1) {
                            RsNetAlarmRpt alarm_rpt = {0};
                            memcpy(&alarm_rpt, data, std::min(sizeof(alarm_rpt), size));
                            channel = alarm_rpt.Channel;
                            status = alarm_rpt.Status;
                        } else {
                            DevStatRpt dev_status_rpt = {0};
                            memcpy(&dev_status_rpt, data, std::min(sizeof(dev_status_rpt), size));
                            channel = dev_status_rpt.Channel;
                            status = dev_status_rpt.Status;
                        }

                        SetPreviewRecordStatus(getIpcCh(channel), MsgPirAlarm, false, 0, 0, 0);
                        if (status == 1) {//green PIR
                            SetPreviewRecordStatus(getIpcCh(channel), MsgPirAlarm, true, 0, 255, 0);
                        }
                    }
                }
            }
            break;
        case MsgRecordStatusReport:
            {
                if (get_device_type() == DEV_IPC) {
                    RecordStatusRpt record_status = {0};
                    memcpy(&record_status, data, std::min(sizeof(record_status), size));

                    SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgRecordStatusReport, false, 0, 0, 0);
                    if (device_status_rpt_.RecordStatus == 1) {//red R
                        switch (record_status.Type) {
                            case 0://r
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgRecordStatusReport, true, 255, 0, 0);
                                break;
                            case 2://m
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgMotionAlarm, true, 255, 0, 0);
                                alarm_flag_temp_.motion = 1;
                                break;
                            case 3://i
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgIOAlarm, true, 255, 0, 0);
                                alarm_flag_temp_.io = 1;
                                break;
                            case 13://s
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgAlarmIntManage, true, 255, 0, 0);
                                break;
                            case 15://pir
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgPirAlarm, true, 255, 0, 0);
                                alarm_flag_temp_.pir = 1;
                                break;
                        }
                    } else {
                        switch (record_status.Type) {
                            case 5://stop m
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgMotionAlarm, false, 0, 0, 0);
                                alarm_flag_temp_.motion = 0;
                                break;
                            case 6://stop i
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgIOAlarm, false, 0, 0, 0);
                                alarm_flag_temp_.io = 0;
                                break;
                            case 13://s
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum),MsgAlarmIntManage,true,255,0,0);
                                break;
                            case 14://stop s
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgAlarmIntManage, false, 0, 0, 0);
                                break;
                            case 15://pir
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum),MsgPirAlarm,true,255,0,0);
                                alarm_flag_temp_.pir = 1;
                                break;
                            case 16://stop pir
                                SetPreviewRecordStatus(getIpcCh(record_status.ChannelNum), MsgPirAlarm, false, 0, 0, 0);
                                alarm_flag_temp_.pir = 0;
                                break;
                        }
                    }
                }
            }
            break;
        default:
            break;
        }

        if (alarm_status_changed_) {
            Json::Value value(Json::arrayValue);
            int channel_num = get_channel_num();
            for (int i = 0; i < channel_num; i++) {
                Json::Value temp;
                temp["hdd"] = (int)alarm_flag_[i].h;
                temp["record"] = (int)alarm_flag_[i].r;
                temp["io"] = (int)alarm_flag_[i].i;
                temp["motion"] = (int)alarm_flag_[i].m;
                temp["lens cover"] = (int)alarm_flag_[i].c;
                temp["lcd"] = (int)alarm_flag_[i].l;
                temp["sod"] = (int)alarm_flag_[i].o;
                temp["pid"] = (int)alarm_flag_[i].p;
                temp["smart"] = (int)alarm_flag_[i].s;
                temp["pir"] = (int)alarm_flag_[i].pir;
                value.append(temp);
            }

            if (!value.empty() && base_running_) {
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);

                alarm_cb_("RSSDKAlarmStatus", result.c_str(), user_param_);
            }
        }
    }

    int getIpcCh(int chValue) {
        for (int i = 0; i < get_channel_num(); i++) {
            if(chValue & (1<<i))
                return i;
        }
        return 0;
    }

    void SetPreviewRecordStatus(int channel, int alarm_type, bool show, int r, int g, int b) {
        alarm_status_changed_ = true;
        switch(alarm_type)
        {
        case MsgRecordStatusReport://R
            if (show) {
                if (r)
                    alarm_flag_[channel].r = 2;
                else
                    alarm_flag_[channel].r = 1;
            } else {
                alarm_flag_[channel].r = 0;
            }
            break;
        case MsgMotionAlarm: //M
            if (show) {
                if (r)
                    alarm_flag_[channel].m = 2;
                else
                    alarm_flag_[channel].m = 1;
            } else {
                alarm_flag_[channel].m = 0;
            }
            break;
        case MsgIOAlarm: //I
            if (show) {
                if (r)
                    alarm_flag_[channel].i = 2;
                else
                    alarm_flag_[channel].i = 1;
            } else {
                alarm_flag_[channel].i = 0;
            }
            break;
        case MsgHddStatusReport: //H
            if (show) {
                if (r)
                    alarm_flag_[channel].h = 2;
                else
                    alarm_flag_[channel].h = 1;
            } else {
                alarm_flag_[channel].h = 0;
            }
            break;
        case MsgVideoHideAlarm: //C
            if (show) {
                if (r)
                    alarm_flag_[channel].c = 2;
                else
                    alarm_flag_[channel].c = 1;
            } else {
                alarm_flag_[channel].c = 0;
            }
            break;
        case MsgIntelIpcPeaAlarm: //L
            if (show) {
                if (r)
                    alarm_flag_[channel].l = 2;
                else
                    alarm_flag_[channel].l = 1;
            } else {
                alarm_flag_[channel].l = 0;
            }
            break;
        case MsgIpcOSCAlarm: //O
            if (show) {
                if (r)
                    alarm_flag_[channel].o = 2;
                else
                    alarm_flag_[channel].o = 1;
            } else {
                alarm_flag_[channel].o = 0;
            }
            break;
        case MsgIntelIpcPeaAreaAlarm: //P
            if (show) {
                if (r)
                    alarm_flag_[channel].p = 2;
                else
                    alarm_flag_[channel].p = 1;
            } else {
                alarm_flag_[channel].p = 0;
            }
            break;
        case MsgAlarmIntManage: //S
            if (show) {
                if (r)
                    alarm_flag_[channel].s = 2;
                else
                    alarm_flag_[channel].s = 1;
            } else {
                alarm_flag_[channel].s = 0;
            }
            break;
        case MsgPirAlarm: //PIR
            if (show) {
                if (r)
                    alarm_flag_[channel].pir = 2;
                else
                    alarm_flag_[channel].pir = 1;
            } else {
                alarm_flag_[channel].pir = 0;
            }
            break;
        default:
            alarm_status_changed_ = false;
            break;
        }
    }

private:
    RSNetConnection     conn_;
    std::string         ip_or_id_;
    std::string         password_;
    int                 port_;
    bool                disable_auto_send_msg_;
    LoginRsp            rsp_;
    RemoteChnStatusRpt* channel_status_rpt_;
    DevAllStatusRpt     device_status_rpt_;
    ALARM_FLAG*         alarm_flag_;
    ALARM_FLAG_TEMP     alarm_flag_temp_;
    bool                alarm_status_changed_;
    char                channel_online_status_[256];

    volatile bool       base_running_;
    connction_callback  conn_cb_;
    alarm_callback      alarm_cb_;
    alarm_callback_ex   alarm_cb_ex_;
    void*               user_param_;
};
