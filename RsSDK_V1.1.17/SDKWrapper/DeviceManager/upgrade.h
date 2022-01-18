#pragma once

class upgrade : public base_instance {
public:
    upgrade(void* parent, connection& conn)
        : base_instance(parent, UPGRADE_INSTANCE_TYPE, "upgrade", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , upgrade_handle_(NULL)
        , upgrade_cb_(NULL)
        , user_param_(NULL)
    {

    }

    ~upgrade() {
        stop();
    }

    static void RSNET_CALL RSNetRemoteUpgradeCallbackFun(UINT code, void* param, void* userParam) {
        upgrade* _this = static_cast<upgrade*>(userParam);
        if (_this)
            _this->RSNetRemoteUpgradeCallbackFun(code, param);
    }

    void RSNetRemoteUpgradeCallbackFun(UINT code, void* param) {
        if (base_running_ && upgrade_cb_) {
            long percent = -1;
            int channel = -1;
            std::string err;
            switch (code)
            {
            case RSNetMsgRemoteUpgradeClosed:
                err = "upgrade close";
                break;
            case RSNetMsgRemoteUpgradeOK:
                err = "upgrade ok";
                break;
            case RSNetMsgRemoteUpgradeReadFileFail:
                err = "read file error";
                break;
            case RSNetMsgRemoteUpgradeInvalidFile:
                err = "invalid file";
                break;
            case RSNetMsgRemoteUpgradePercent:
                err = "percent";
                percent = (long)param;
                break;
            case RSNetMsgRemoteUpgradeIPCPercent:
                {
                    RS_UGIpcRsp_t *ugipc = (RS_UGIpcRsp_t*)param;
                    channel = ugipc->channelNo;
                    if (ugipc->status = Stat_Err)
                        err = "ipc upgrade error";
                    else if (ugipc->status = Stat_Failed)
                        err = "ipc upgrade fail";
                    else if (ugipc->status = Stat_Inprogress) {
                        err = "ipc upgrade percent";
                        percent = ugipc->progress;
                    } else if (ugipc->status = Stat_Success)
                        err = "ipc upgrade success";
                    else
                        err = "ipc upgrade unknown error";
                }
                break;
            case RSNetMsgRemoteUpgradeVerError:
                err = "version error";
                break;
            case RSNetMsgRemoteUpgrading:
                err = "upgrading";
                break;
            case RSNetMsgRemoteUpgradeVerSame:
                err = "version same";
                break;
            case RSNetMsgRemoteUpgradeLanguageError:
                err = "language error";
                break;
            case RSNetMsgRemoteInUserInterface:
                err = "user interface";
                break;
            case MsgRemoteUpgradeWriteFlashInProgress:
                err = "write flash progress";
                break;
            default:
                err = "unknown error";
                break;
            }

            Json::Value value;
            value["status"] = err;
            if (percent != -1)
                value["percent"] = (int) percent;
            if (channel != -1)
                value["channel"] = channel;

            Json::StreamWriterBuilder writer;
            std::string result = Json::writeString(writer, value);

            upgrade_cb_(result.c_str(), NULL, user_param_);
        }
    }

    rs_error_code start(const char* param, upgrade_callback cb, void* user_param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[%s] call <upgrade start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        upgrade_cb_ = cb;
        user_param_ = user_param;

        std::string file = value["file name"].asString();
        assert(!file.empty());

        int file_type = 3;
        std::string str_file_type = value["file type"].asString();
        if (str_file_type == "normal") {
            file_type = 3;
        } else if (str_file_type == "urmet ipc") {
            file_type = 4;
        } else if (str_file_type == "raysharp ipc") {
            file_type = 5;
        } else if (str_file_type == "98c") {
            file_type = 6;
        } else if (str_file_type == "srp6") {
            file_type = 7;
        } else {
            return rs_fail;
        }

        RSNetRemoteUpgradeParamEx _param = {0};
        std::string channel = value["channel"].asString();
        if (channel.empty() || channel == "all") {
            return rs_param_error;
        } else {
            std::vector<int> vec_channels;
            std::string::size_type prev_pos = 0;
            std::string::size_type pos = 0;
            std::string sub_string;

            while((pos = channel.find(' ', pos)) != std::string::npos) {
                sub_string = channel.substr(prev_pos, pos-prev_pos);
                int temp_channle = atoi(sub_string.c_str());
                vec_channels.push_back(temp_channle);
                prev_pos = ++pos;
            }
            sub_string = channel.substr(prev_pos, pos-prev_pos);
            int temp_channle = atoi(sub_string.c_str());
            vec_channels.push_back(temp_channle);

            int channel_no = 0;
            for (size_t i = 0 ; i < vec_channels.size(); i ++) {
                channel_no = vec_channels.at(i);
                if (channel_no < 32) {
                    _param.nChannelMask = 0x1 << channel_no;
                } else {
                    _param.ChannelMask_EX[channel_no/32-1] |= (0x1 << (channel_no%32));
                }
            }
        }

        _param.FileName = file.c_str();
        _param.Callback = RSNetRemoteUpgradeCallbackFun;
        _param.UserParam = this;
        _param.filetype = file_type;
        _param.time_sleep = value["sleep time"].asInt();
        upgrade_handle_ = RSNetStartRemoteUpgradeEx(conn_, &_param);

        base_running_ = upgrade_handle_ ? true : false;
        sdk_wrapper_log("[%s] call <upgrade start> result:%s\n", ip_or_id_.c_str(), upgrade_handle_ ? "success" : "fail");
        return upgrade_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !upgrade_handle_)
            return rs_success;

        base_running_ = false;

        if (upgrade_handle_) {
            RSNetStopRemoteUpgrade(&upgrade_handle_);
            upgrade_handle_ = NULL;
        }
        upgrade_cb_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[%s] call <upgrade stop> result:success\n", ip_or_id_.c_str());
        return rs_success;
    }

private:
    RSNetConnection     conn_;
    RSNetRemoteUpgrade  upgrade_handle_;
    upgrade_callback    upgrade_cb_;
    void*               user_param_;
};
