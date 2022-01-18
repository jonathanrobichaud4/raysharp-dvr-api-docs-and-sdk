#pragma once
#include <list>

class talk : public base_instance {
public:
    talk(void* parent, connection& conn)
        : base_instance(parent, TALK_INSTANCE_TYPE, "talk", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection()) 
        , play_handle_(NULL)
        , net_handle_(NULL)
        , talk_cb_(NULL)
        , user_param_(NULL)
    {
    }

    ~talk() {
        stop();
    }

    static void RSNET_CALL RSNetDualtalkDataCallbackFun(void* data, UINT size, void* userParam) {
        talk* _this = static_cast<talk*>(userParam);
        if (_this)
            _this->RSNetDualtalkDataCallbackFun(data, size);
    }

    static void RSNET_CALL RSNetDualtalkStatusCallbackFun(int code, void* userParam) {
        talk* _this = static_cast<talk*>(userParam);
        if (_this)
            _this->RSNetDualtalkStatusCallbackFun(code);
    }

    static int CALLBACK DUAL_SPEAK_CALLBACK_FUN(int size, const char* data, void* user_param) {
        talk* _this = static_cast<talk*>(user_param);
        if (_this)
            return _this->DUAL_SPEAK_CALLBACK_FUN(size, data);
        return 0;
    }

    inline void RSNetDualtalkDataCallbackFun(void* data, UINT size) {
        if (base_running_ && play_handle_)
            RSPlayInputNetFrame(play_handle_, data, size);
    }

    void RSNetDualtalkStatusCallbackFun(int code) {
        if (base_running_ && talk_cb_) {
            uint64_t temp_code = code;
            std::string err;
            switch (temp_code)
            {
            case RSNetEDualtalkBusy:
                err = "talk busy";
                break;
            case RSNetMsgDualtalkClosed:
                err = "talk close";
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
                
                talk_cb_(result.c_str(), user_param_);
            }
        }
    }

    inline int DUAL_SPEAK_CALLBACK_FUN(int size, const char* data) {
        if (base_running_ && net_handle_)
            RSNetSendDualtalkData(net_handle_, const_cast<char*>(data), size);
        return 0;
    }

    rs_error_code start(const char* param, talk_callback talk_cb, void* user_param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[%s] call <talk start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        play_handle_ = RSPlayCreatePlayInstance(PLAY_DUALTALK_TYPE);
        base_play_handle_ = play_handle_;
        if (play_handle_) {
            talk_cb_ = talk_cb;
            user_param_ = user_param;
        } else {
            return rs_fail;
        }

        UINT channel = value["channel"].asUInt();
        std::string talk_mode = value["talk mode"].asString();
        int sample_rate = value["sample rate"].asInt();
        if (sample_rate == 0)
            sample_rate = 8000;

        int mode = 0;//0 means "full duplex" or "old mode" or "analogue audio", 1 means "half duplex"
        bool talk_to_device = false;
        BYTE UseChannelTwoWayTalk = 0;
        BYTE UseDeviceAnalogueAudioTalk = 0;
        //"talk mode" : "half duplex" or "full duplex" or "old mode" or "analogue audio"
        if (talk_mode == "half duplex") {
            talk_to_device = false;
            UseChannelTwoWayTalk = 0;
            UseDeviceAnalogueAudioTalk = 0;
            mode = 1;
        } else if (talk_mode == "full duplex") {
            talk_to_device = false;
            UseChannelTwoWayTalk = 1;
            UseDeviceAnalogueAudioTalk = 0;
        } else if (talk_mode == "old mode") {
            talk_to_device = true;
            UseChannelTwoWayTalk = 0;
            UseDeviceAnalogueAudioTalk = 0;
        } else if (talk_mode == "analogue audio") {
            talk_to_device = true;
            UseChannelTwoWayTalk = 0;
            UseDeviceAnalogueAudioTalk = 1;
        }

        RSNetDualtalkParam talk_param;
        memset(&talk_param, 0, sizeof(talk_param));
        talk_param.DataCallback = RSNetDualtalkDataCallbackFun;
        talk_param.UserParam = this;
        talk_param.Wnd = NULL;
        talk_param.Message = 0;
        talk_param.UseChannelDualtalk = talk_to_device ? 0 : 1;
        talk_param.UseChannelTwoWayTalk = UseChannelTwoWayTalk;
        talk_param.UseDeviceAnalogueAudioTalk = UseDeviceAnalogueAudioTalk;
        talk_param.Channel = channel;
        talk_param.StatusCallback = RSNetDualtalkStatusCallbackFun;

        base_running_ = true;
        net_handle_ = RSNetStartDualtalk(conn_, &talk_param);
        if (net_handle_) {
            RSPlayRegisterSetDualCallback(play_handle_, DUAL_SPEAK_CALLBACK_FUN, this);
            AudioTalkConfig_t config = {0};
            config.iRate = sample_rate;
            config.iWidth = 16;
            config.iFormat = 1;
            config.iAmr_mode = mode;
            RSPlayStartDualTalk(play_handle_, &config);

            sdk_wrapper_log("[%s] call <talk start> result:success\n", ip_or_id_.c_str());
            return rs_success;
        } else {
            base_running_ = false;
            sdk_wrapper_log("[%s] call <talk start> result:fail\n", ip_or_id_.c_str());
            return rs_fail;
        }
    }

    rs_error_code stop() {
        if (!base_running_ && !net_handle_ && !play_handle_)
            return rs_success;

        base_running_ = false;

        if (net_handle_) {
            RSNetStopDualtalk(&net_handle_);
            net_handle_ = NULL;
        }

        if (play_handle_) {
            RSPlayStopDualTalk(play_handle_);
            RSPlayDestroyPlayInstance(play_handle_);
            play_handle_ = NULL;
            base_play_handle_ = play_handle_;
        }

        talk_cb_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[%s] call <talk stop> result:success\n", ip_or_id_.c_str());
        return rs_success;
    }

private:
    RSNetConnection   conn_;
    RSPlayHandle      play_handle_;
    RSNetDualtalk     net_handle_;
    talk_callback     talk_cb_;
    void*             user_param_;
};
