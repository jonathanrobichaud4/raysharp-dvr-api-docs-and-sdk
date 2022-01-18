#pragma once

class remote_playback : public base_instance {
public:
    remote_playback(void* parent, connection& conn)
        : base_instance(parent, REMOTE_PLAYBACK_INSTANCE_TYPE, "remote_playback", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , device_((CRSDevice*)parent)
        , last_play_mode_(PLAY_MODE_NORMAL)
        , net_handle_(NULL)
        , play_handle_(NULL)
        , channel_(0)
        , playback_cb_(NULL)
        , user_param_(NULL) 
        , sync_play_(false)
        , reverse_playback_(false)
    {
        memset(&record_param_, 0, sizeof(record_param_));
    }

    ~remote_playback() {
        stop();
    }

    static int CALLBACK BEFORE_RENDER_CALLBACK_FUN(void* data, void* user_param) {
        remote_playback* _this = static_cast<remote_playback*>(user_param);
        if (_this)
            return _this->BEFORE_RENDER_CALLBACK_FUN((RS_PICTURE_S*)data);
        return 0;
    }
    
    static void RSPLAY_CALL PLAY_FUN_CALLBACK_FUN(UINT message, void* userParam) {
        remote_playback* _this = static_cast<remote_playback*>(userParam);
        if (_this)
            _this->PLAY_FUN_CALLBACK_FUN(message);
    }

    static BOOL RSNET_CALL RSNetRecordPlayDataCallbackFun(void* data, UINT size, void* userParam) {
        remote_playback* _this = static_cast<remote_playback*>(userParam);
        if (_this)
            return _this->RSNetRecordPlayDataCallbackFun(data, size);
        return FALSE;
    }

    static void RSNET_CALL RSNetRecordStatusCallbackFun(UINT code, void* userParam) {
        remote_playback* _this = static_cast<remote_playback*>(userParam);
        if (_this)
            _this->RSNetRecordStatusCallbackFun(code);
    }

    int BEFORE_RENDER_CALLBACK_FUN(RS_PICTURE_S* frame) {
        if (base_running_ && frame) {
            if (!frame->dec_frame_head.forbidden_move) {
                rs_scoped_lock lock(decoded_frame_mutex_);
                decoded_frame_list_.push_back(frame);
                return 1;
            } else {
                const RS_DEC_FRAME_S& src_dec_frame = frame->dec_frame_head;
                unsigned long nYSize = src_dec_frame.uYStride * src_dec_frame.uHeight;
                unsigned long nUVSize = src_dec_frame.uUVStride * src_dec_frame.uHeight / 2;
                unsigned long frameDataSize = nYSize + nUVSize * 2 + sizeof(RS_PICTURE_S);

                RS_PICTURE_S* pPicture = static_cast<RS_PICTURE_S*>(malloc(frameDataSize));
                if (pPicture) {
                    memcpy(pPicture, frame, sizeof(RS_PICTURE_S));
                    RS_DEC_FRAME_S& dec_frame = pPicture->dec_frame_head;
                    if (dec_frame.uYStride == dec_frame.uWidth &&
                        dec_frame.uYStride == dec_frame.uUVStride * 2) {
                        uint8_t *p = src_dec_frame.pY;
                        dec_frame.pY = pPicture->picture_data;
                        memcpy(dec_frame.pY, p, nYSize);

                        p = src_dec_frame.pU;
                        dec_frame.pU = dec_frame.pY + nYSize;
                        memcpy(dec_frame.pU, p, nUVSize);

                        p = src_dec_frame.pV;
                        dec_frame.pV = dec_frame.pU + nUVSize;
                        memcpy(dec_frame.pV, p, nUVSize);
                    } else {
                        int width = (int) dec_frame.uWidth;
                        int height = (int) dec_frame.uHeight;

                        uint8_t *p = src_dec_frame.pY;
                        dec_frame.pY = pPicture->picture_data;
                        for (int i = 0; i < height; i++)
                            memcpy(dec_frame.pY + width * i, p + dec_frame.uYStride * i, width);

                        p = src_dec_frame.pU;
                        dec_frame.pU = dec_frame.pY + width * height;
                        for (int i = 0; i < height / 2; i++)
                            memcpy(dec_frame.pU + width / 2 * i, p + dec_frame.uUVStride * i,
                                   width / 2);

                        p = src_dec_frame.pV;
                        dec_frame.pV = dec_frame.pU + width * height / 4;
                        for (int i = 0; i < height / 2; i++)
                            memcpy(dec_frame.pV + width / 2 * i, p + dec_frame.uUVStride * i,
                                   width / 2);

                        dec_frame.uYStride = width;
                        dec_frame.uUVStride = dec_frame.uYStride / 2;
                    }
                    rs_scoped_lock lock(decoded_frame_mutex_);
                    decoded_frame_list_.push_back(pPicture);
                }
                return 0;
            }
        }
        return 0;
    }
    
    void PLAY_FUN_CALLBACK_FUN(UINT message) {
        int64_t msg = (int64_t)message;
        std::string err;
        switch (msg)
        {
        case CREATE_DECODE_FAILED:
            err = "create decoder failed";
            break;
        case NET_FILE_DATA_NOT_ENOUGH:
            if (net_handle_)
                RSNetReqRecordData(net_handle_);
            break;
        case FILE_PLAY_END:
            err = "file play end";
            break;
        case FILE_CREATE_FAILED:
            err = "file create failed";
            break;
        case FILE_WRITE_FAILED:
            err = "file write failed";
            break;
        case DEL_FROM_SYNC:
            stop_net();
            stop_play();
            break;
        default:
            err = "unknown error";
            break;
        }

        rs_scoped_lock lock(base_mutex_);
        if (base_running_ && !err.empty() && playback_cb_) {
            send_msg_to_app(err.c_str(), channel_);
        }
    }

    inline BOOL RSNetRecordPlayDataCallbackFun(void* data, UINT size) {
        if (base_running_ && play_handle_) {
            HRESULT hr= RSPlayInputNetFrame(play_handle_, data, size);
            if (hr == E_OUTOFMEMORY)
                return FALSE;
            return TRUE;
        }
        return FALSE;
    }

    void RSNetRecordStatusCallbackFun(UINT code) {
        std::string err;
        switch (code)
        {
        case RSNetMsgRecordPlayWaitLogin:
            err = "";
            break;
        case RSNetMsgRecordPlayOpenStream:
            err = "start open stream";
            break;
        case RSNetMsgRecordPlayOpenStreamSuccess:
            err = "open stream success";
            break;
        case RSNetMsgRecordPlayOpenStreamFail:
            err = "open stream failed";
            break;
        case RSNetMsgRecordPlayClosed:
            err = "preivew closed";
            break;
        case RSNetMsgRecordPlayDevicePlayback:
            err = "device playback";
            break;
        case RSNetMsgRecordPlayHDDFormat:
            err = "hdd format";
            break;
        case RSNetMsgNoBandWidth:
            err = "not enough bandwidth";
            break;
        case RSNetMsgNoPlaybackAuth:
            err = "no authority";
            break;
        case RSNetMsgIsModifyHdd:
            err = "modify hdd";
            break;
        case RSMetMsgPreviewActivateFaile:
            err = "preview active failed";
            break;
        case RSNetMsgRecordPlayNoData:
            err = "record no data";
            break;
        case RSNetMsgRecordPlayIFrameEnd:
            err = "record I frame end";
            break;
        case RSNetMsgRecordPlayNetworkFrameArrive:
            err = "network frame arrieved";
            break;
        default:
            err = "unknown error";
            break;
        }

        rs_scoped_lock lock(base_mutex_);
        if (base_running_ && !err.empty() && playback_cb_) {
            send_msg_to_app(err.c_str(), channel_);
        }
    }

    rs_error_code start(const remote_playback_param* param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param->param, &value, &err)) {
            sdk_wrapper_log("[%s] call <remote_playback start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        sync_play_ = value["sync play"].asBool();
        playback_cb_ = param->playback_cb;
        user_param_ = param->playback_user_param;
        play_handle_ = RSPlayCreatePlayInstance(PLAY_NETFILE_TYPE);
        base_play_handle_ = play_handle_;
        if (play_handle_) {
            channel_ = value["channel"].asUInt();

            RSPlaySetCallbackMessageEx(play_handle_, PLAY_FUN_CALLBACK_FUN, this);
            RSPlaySetPlayWnd(play_handle_, param->window);
#ifdef __ANDROID__
            RSPlayRegisterBeforeRenderCallback(play_handle_, BEFORE_RENDER_CALLBACK_FUN, this);
#endif
            if (param->draw_cb)
                RSPlayRegisterSdkwrapperDrawCallback(play_handle_, param->draw_cb, param->playback_user_param);
            if (!sync_play_)
                RSPlayStartPlay(play_handle_);
        } else {
            return rs_fail;
        }

        int type = 0;
        std::string stream_type = value["stream type"].asString();
        if (stream_type == "main stream") {
            type = 0;
        } else if (stream_type == "sub stream") {
            type = 1;
        } else if (stream_type == "mobile stream") {
            type = 2;
        }

        memset(&record_param_, 0, sizeof(record_param_));
        {
            std::string begin_time_str = value["begin time"].asString();
            std::string end_time_str = value["end time"].asString();
            if (!begin_time_str.empty() && !end_time_str.empty()) {
                DateTime begin_time = {0};
                DateTime end_time = {0};
                rs_error_code result = rs_fail;
                if ((result = get_time_from_string(begin_time_str, begin_time)) || \
                    (result = get_time_from_string(end_time_str, end_time)))
                    return result;

                record_param_.Begin = begin_time;
                record_param_.End = end_time;
            }
        }
        record_param_.Channel = value["channel"].asUInt();
        record_param_.Type = value["record type"].asUInt();
        record_param_.DataCallback = RSNetRecordPlayDataCallbackFun;
        record_param_.StatusCallback = RSNetRecordStatusCallbackFun;
        record_param_.UserParam = this;
        record_param_.StreamType = type;

        if (!sync_play_) {
            net_handle_ = RSNetStartRecordPlayEx(conn_, &record_param_);
            base_running_ = net_handle_ ? true : false;
            sdk_wrapper_log("[%s ch:%d] call <remote_playback start> result:%s\n", ip_or_id_.c_str(), channel_, net_handle_ ? "success" : "fail");
            return net_handle_ ? rs_success : rs_fail;
        } else {
            base_running_ = true;
            sdk_wrapper_log("[%s ch:%d] call <remote_playback start> result:success\n", ip_or_id_.c_str(), channel_);
            return rs_success;
        }
    }

    rs_error_code stop() {
        {
            rs_scoped_lock lock(base_mutex_);
            base_running_ = false;
        }

        stop_net();
        stop_play();

        rs_scoped_lock lock(decoded_frame_mutex_);
        while (!decoded_frame_list_.empty()) {
            RS_PICTURE_S* frame = decoded_frame_list_.front();
            decoded_frame_list_.pop_front();
            free(frame);
        }
        
        last_play_mode_ = PLAY_MODE_NORMAL;
        sync_play_ = false;
        reverse_playback_ = false;
        
        sdk_wrapper_log("[%s ch:%d] call <remote_playback stop> result:success\n", ip_or_id_.c_str(), channel_);
        return rs_success;
    }

    rs_error_code start_net() {
        assert(sync_play_);
        net_handle_ = RSNetStartRecordPlayEx(conn_, &record_param_);
        return net_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop_net() {
        rs_scoped_lock lock(stop_mutex_);
        if (net_handle_) {
            RSNetStopRecordPlay(&net_handle_);
            net_handle_ = NULL;
        }
        return rs_success;
    }

    rs_error_code stop_play() {
        rs_scoped_lock lock(stop_mutex_);
        if (play_handle_) {
            RSPlayStopPlay(play_handle_);
            RSPlayDestroyPlayInstance(play_handle_);
            play_handle_ = NULL;
            base_play_handle_ = play_handle_;
        }
        return rs_success;
    }

    bool is_sync_play() {
        return sync_play_; 
    }

    void remote_self_from_device_list() {
        CRSDevice* dev = (CRSDevice*)parent_;
        if (dev)
            dev->remote_self_from_device_list(this);
    }

    RS_PICTURE_S* get_decoded_frame() {
        RS_PICTURE_S* frame = NULL;
        rs_scoped_lock lock(decoded_frame_mutex_);
        if (!decoded_frame_list_.empty()) {
            frame = decoded_frame_list_.front();
            decoded_frame_list_.pop_front();
        }
        return frame;
    }
    
    void send_msg_to_app(const char* err, uint32_t channel) {
        Json::Value value;
        value["channel"] = channel;
        value["status"] = err;
        Json::StreamWriterBuilder writer;
        std::string result = Json::writeString(writer, value);

        playback_cb_(result.c_str(), user_param_);
    }

    rs_error_code seek_by_time(const char* param) {
        if (net_handle_ && play_handle_) {
            DateTime begin_time = {0};
            std::string str_begin_time = param;
            rs_error_code result = rs_fail;
            if (result = get_time_from_string(str_begin_time, begin_time))
                return result;
            record_param_.Begin = begin_time;
            record_param_.End.Hour = 23;
            record_param_.End.Minute = 59;
            record_param_.End.Second = 59;
            RSNetStopRecordPlay(&net_handle_);
            net_handle_ = NULL;
            RSPlayClearFrameBuffer(play_handle_);
            RSPlayClearTime(play_handle_);

            int playback_capability = device_->get_device_playback_capability();
            PlaySpeedCtrl speed = get_play_speed_ctrl(last_play_mode_, playback_capability);
            record_param_.speed = (BYTE)speed;

            net_handle_ = RSNetStartRecordPlayEx(conn_, &record_param_);
            if (net_handle_)
                return rs_success;
        }
        return rs_fail;
    }

    rs_error_code switch_stream_type(const char* param) {
        if (net_handle_ && play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            int type = 0;
            std::string stream_type = value["stream type"].asString();
            if (stream_type == "main stream") {
                type = 0;
            } else if (stream_type == "sub stream") {
                type = 1;
            } else if (stream_type == "mobile stream") {
                type = 2;
            }

            if (record_param_.StreamType != type) {
                record_param_.StreamType = type;
                RSNetStopRecordPlay(&net_handle_);
                net_handle_ = NULL;
                RSPlayClearFrameBuffer(play_handle_);
                
                ULONGLONG current_time = RSPlayGetCurPlayedTime(play_handle_);
                if (current_time) {
                    current_time += 500000;
                    time_t now = (time_t)(current_time / 1000000);
                    struct tm gmtTime;
#ifdef _MSC_VER
                    gmtime_s(&gmtTime, &now);
#else
                    gmtime_r(&now, &gmtTime);
#endif
                    DateTime begin_time = {0};
                    begin_time.Year = gmtTime.tm_year+1900;
                    begin_time.Month = gmtTime.tm_mon+1;
                    begin_time.Day = gmtTime.tm_mday;
                    begin_time.Hour = gmtTime.tm_hour;
                    begin_time.Minute = gmtTime.tm_min;
                    begin_time.Second = gmtTime.tm_sec;
                    record_param_.Begin = begin_time;
                }

                net_handle_ = RSNetStartRecordPlayEx(conn_, &record_param_);
                if (net_handle_)
                    return rs_success;
                else
                    return rs_fail;
            } else {
                return rs_success;
            }
        }
        return rs_fail;
    }

    rs_error_code set_play_mode(const char* param) {
        if (play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            int play_mode = -1;
            bool temp_reverse_playback = false;
            std::string type = value["operation type"].asString();
            if (type == "normal") {
                play_mode = PLAY_MODE_NORMAL;
            } else if (type == "pause") {
                play_mode = PLAY_MODE_PAUSE;
            } else if (type == "single frame") {
                play_mode = PLAY_MODE_SINGLE_FRAME;
            } else if (type == "16 times slower") {
                play_mode = PLAY_MODE_SLOW16;
            } else if (type == "8 times slower") {
                play_mode = PLAY_MODE_SLOW8;
            } else if (type == "4 times slower") {
                play_mode = PLAY_MODE_SLOW4;
            } else if (type == "2 times slower") {
                play_mode = PLAY_MODE_SLOW;
            } else if (type == "2 times faster") {
                play_mode = PLAY_MODE_FAST_FORWARD2;
            } else if (type == "4 times faster") {
                play_mode = PLAY_MODE_FAST_FORWARD4;
            } else if (type == "8 times faster") {
                play_mode = PLAY_MODE_FAST_FORWARD8;
            } else if (type == "16 times faster") {
                play_mode = PLAY_MODE_FAST_FORWARD16;
            } else if (type == "1 times reverse") {
                play_mode = PLAY_MODE_REVERSE;
                temp_reverse_playback = true;
            } else if (type == "2 times reverse") {
                play_mode = PLAY_MODE_REVERSE2;
                temp_reverse_playback = true;
            } else if (type == "4 times reverse") {
                play_mode = PLAY_MODE_REVERSE4;
                temp_reverse_playback = true;
            } else if (type == "8 times reverse") {
                play_mode = PLAY_MODE_REVERSE8;
                temp_reverse_playback = true;
            } else if (type == "16 times reverse") {
                play_mode = PLAY_MODE_REVERSE16;
                temp_reverse_playback = true;
            } else {
                return rs_fail;
            }

            if (temp_reverse_playback && !device_->support_reverse_playback())
                return rs_not_support;

            int playback_capability = device_->get_device_playback_capability();
            if (need_switch_playback_ctrl(play_mode, last_play_mode_, playback_capability)) {
                if (play_mode != PLAY_MODE_PAUSE)
                    last_play_mode_ = play_mode;

                ULONGLONG current_time = 0;
                RSNetStopRecordPlay(&net_handle_);
                net_handle_ = NULL;
                RSPlayClearFrameBuffer(play_handle_);
                current_time = RSPlayGetCurPlayedTime(play_handle_);
                RSPlaySetPlayMode(play_handle_, process_play_mode(play_mode), 0);

                current_time += 500000;
                time_t now = (time_t)(current_time / 1000000);
                struct tm gmtTime;
#ifdef _MSC_VER
                gmtime_s(&gmtTime, &now);
#else
                gmtime_r(&now, &gmtTime);
#endif
                BYTE temp_speed = record_param_.speed;
                BYTE temp_send_reset_msg = record_param_.send_reset_msg;
                DateTime begin_time = {0};
                begin_time.Year = gmtTime.tm_year+1900;
                begin_time.Month = gmtTime.tm_mon+1;
                begin_time.Day = gmtTime.tm_mday;
                begin_time.Hour = gmtTime.tm_hour;
                begin_time.Minute = gmtTime.tm_min;
                begin_time.Second = gmtTime.tm_sec;
                record_param_.Begin = begin_time;
                record_param_.send_reset_msg = 1;

                PlaySpeedCtrl speed = get_play_speed_ctrl(play_mode, playback_capability);
                record_param_.speed = (BYTE)speed;

                net_handle_ = RSNetStartRecordPlayEx(conn_, &record_param_);
                record_param_.speed = temp_speed;
                record_param_.send_reset_msg = temp_send_reset_msg;

                if (net_handle_) {
                    return rs_success;
                } else {
                    return rs_fail;
                }
            } else {
                if (play_mode != PLAY_MODE_PAUSE)
                    last_play_mode_ = play_mode;
                RSPlaySetPlayMode(play_handle_, process_play_mode(play_mode), 0);
                return rs_success;
            }
        }
        return rs_fail;
    }

private:
    bool need_switch_playback_ctrl(int current_play_mode, int last_play_mode, int playback_capability) {
        if ((current_play_mode == last_play_mode) || \
            (current_play_mode == PLAY_MODE_REVERSE && last_play_mode == PLAY_MODE_REVERSE2) || \
            (last_play_mode == PLAY_MODE_REVERSE && current_play_mode == PLAY_MODE_REVERSE2))
            return false;

        if (((playback_capability > 0) && \
              ((in_reverse_interval(current_play_mode) && (in_slow_interval(last_play_mode) || in_fast_interval(last_play_mode))) || \
              (in_slow_interval(current_play_mode) && (in_reverse_interval(last_play_mode) || in_fast_interval(last_play_mode))) || \
              (in_fast_interval(current_play_mode) && (in_reverse_interval(last_play_mode) || in_slow_interval(last_play_mode))) || \
              (in_reverse_interval(last_play_mode) && (in_slow_interval(current_play_mode) || in_fast_interval(current_play_mode))) || \
              (in_slow_interval(last_play_mode) && (in_reverse_interval(current_play_mode) || in_fast_interval(current_play_mode))) || \
              (in_fast_interval(last_play_mode) && (in_reverse_interval(current_play_mode) || in_slow_interval(current_play_mode))))) || \
             (playback_capability == 2 && ((in_reverse_interval(current_play_mode) && in_reverse_interval(last_play_mode_)) || \
             (in_fast_interval(current_play_mode) && in_fast_interval(last_play_mode_)))))
        {
            return true;
        }
        return false;
    }

    bool in_slow_interval(int play_mode) {
        static const int slow_interval[] = { PLAY_MODE_SLOW16, PLAY_MODE_SLOW8, PLAY_MODE_SLOW4, PLAY_MODE_SLOW, PLAY_MODE_NORMAL, PLAY_MODE_FAST_FORWARD2 };
        for (int i = 0; i < _countof(slow_interval); i++) {
            if (slow_interval[i] == play_mode)
                return true;
        }
        return false;
    }

    bool in_fast_interval(int play_mode) {
        static const int fast_interval[] = { PLAY_MODE_FAST_FORWARD4, PLAY_MODE_FAST_FORWARD8, PLAY_MODE_FAST_FORWARD16 };
        for (int i = 0; i < _countof(fast_interval); i++) {
            if (fast_interval[i] == play_mode)
                return true;
        }
        return false;
    }

    bool in_reverse_interval(int play_mode) {
        static const int reverse_interval[] = { PLAY_MODE_REVERSE, PLAY_MODE_REVERSE2, PLAY_MODE_REVERSE4, PLAY_MODE_REVERSE8, PLAY_MODE_REVERSE16 };
        for (int i = 0; i < _countof(reverse_interval); i++) {
            if (reverse_interval[i] == play_mode)
                return true;
        }
        return false;
    }

    PlaySpeedCtrl get_play_speed_ctrl(int play_mode, int playback_capability)
    {
        if (playback_capability == 1){
            switch (play_mode)
            {
            case PLAY_MODE_FAST_FORWARD4:
            case PLAY_MODE_FAST_FORWARD8:
            case PLAY_MODE_FAST_FORWARD16:
                return PLAY_TYPE_I_CONTINUOUS;
            default:
                break;
            }
        } else if (playback_capability == 2) {
            switch (play_mode)
            {
            case PLAY_MODE_FAST_FORWARD4:
                return PLAY_TYPE_I_SKIP_ONE;
            case PLAY_MODE_FAST_FORWARD8:
                return PLAY_TYPE_I_SKIP_THREE;
            case PLAY_MODE_FAST_FORWARD16:
                return PLAY_TYPE_I_SKIP_FOUR;

            case PLAY_MODE_REVERSE:
            case PLAY_MODE_REVERSE2:
                return PLAY_REVERSE_I_CONTINUOUS;
            case PLAY_MODE_REVERSE4:
                return PLAY_REVERSE_I_SKIP_ONE;
            case PLAY_MODE_REVERSE8:
                return PLAY_REVERSE_I_SKIP_TWO;
            case PLAY_MODE_REVERSE16:
                return PLAY_REVERSE_I_SKIP_THREE;
            default:
                break;
            }
        }
        return PLAY_TYPE_NORMAL;
    }

    rs_error_code stop_callback() {
        rs_scoped_lock lock(base_mutex_);
        base_running_ = false;
        return rs_success;
    }

    int process_play_mode(int play_mode) {
        int _play_mode = play_mode;
        switch (play_mode)
        {
        case PLAY_MODE_REVERSE:
            if (!reverse_playback_) {
                RSPlaySetPlayMode(play_handle_, PLAY_MODE_REVERSE, 0);
                reverse_playback_ = true;
            }
            _play_mode = PLAY_MODE_NORMAL;
        	break;
        case PLAY_MODE_REVERSE2:
            if (!reverse_playback_) {
                RSPlaySetPlayMode(play_handle_, PLAY_MODE_REVERSE, 0);
                reverse_playback_ = true;
            }
            _play_mode = PLAY_MODE_FAST_FORWARD2;
            break;
        case PLAY_MODE_REVERSE4:
            if (!reverse_playback_) {
                RSPlaySetPlayMode(play_handle_, PLAY_MODE_REVERSE, 0);
                reverse_playback_ = true;
            }
            _play_mode = PLAY_MODE_FAST_FORWARD4;
            break;
        case PLAY_MODE_REVERSE8:
            if (!reverse_playback_) {
                RSPlaySetPlayMode(play_handle_, PLAY_MODE_REVERSE, 0);
                reverse_playback_ = true;
            }
            _play_mode = PLAY_MODE_FAST_FORWARD8;
            break;
        case PLAY_MODE_REVERSE16:
            if (!reverse_playback_) {
                RSPlaySetPlayMode(play_handle_, PLAY_MODE_REVERSE, 0);
                reverse_playback_ = true;
            }
            _play_mode = PLAY_MODE_FAST_FORWARD16;
            break;
        case PLAY_MODE_PAUSE:
            break;
        default:
            if (reverse_playback_) {
                RSPlaySetPlayMode(play_handle_, PLAY_MODE_STOP, 0);
                reverse_playback_ = false;
            }
            break;
        }
        return _play_mode;
    }

private:
    CRSDevice*               device_;
    RSNetConnection          conn_;
    RSNetRecordPlayParamEx   record_param_;
    int                      last_play_mode_;

    rs_mutex                 decoded_frame_mutex_;
    std::list<RS_PICTURE_S*> decoded_frame_list_;

    RSPlayHandle             play_handle_;
    RSNetRecordPlay          net_handle_;
    uint32_t                 channel_;
    playback_callback        playback_cb_;
    void*                    user_param_;
    bool                     sync_play_;

    rs_mutex                 stop_mutex_;
    bool                     reverse_playback_;
};
