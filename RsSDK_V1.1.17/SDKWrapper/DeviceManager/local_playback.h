#pragma once

class local_playback : public base_instance {
public:
    explicit local_playback(void* parent)
        : base_instance(parent, LOCAL_PLAYBACK_INSTANCE_TYPE, "local_playback")
        , play_handle_(NULL) 
        , playback_cb_(NULL)
        , user_param_(NULL)
        , sync_play_(false)
    {

    }

    ~local_playback() {
        stop();
    }

    static int CALLBACK BEFORE_RENDER_CALLBACK_FUN(void* data, void* user_param) {
        local_playback* _this = static_cast<local_playback*>(user_param);
        if (_this)
            return _this->BEFORE_RENDER_CALLBACK_FUN((RS_PICTURE_S*)data);
        return 0;
    }

    static void RSPLAY_CALL PLAY_FUN_CALLBACK_FUN(UINT message, void* userParam) {
        local_playback* _this = static_cast<local_playback*>(userParam);
        if (_this)
            _this->PLAY_FUN_CALLBACK_FUN(message);
    }

    int BEFORE_RENDER_CALLBACK_FUN(RS_PICTURE_S* frame) {
        if (frame && base_running_) {
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
            }
        }
        return 0;
    }
    
    void PLAY_FUN_CALLBACK_FUN(UINT message) {
        if (base_running_ && playback_cb_) {
            int64_t msg = (int64_t)message;
            std::string err;
            switch (msg)
            {
            case CREATE_DECODE_FAILED:
                err = "create decoder failed";
                break;
            case NET_FILE_DATA_NOT_ENOUGH:
                err = "net file not enough";
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
            default:
                err = "unknown error";
                break;
            }

            Json::Value value;
            value["status"] = err;
            Json::StreamWriterBuilder writer;
            std::string result = Json::writeString(writer, value);

            playback_cb_(result.c_str(), user_param_);
        }
    }

    rs_error_code start(const local_playback_param* param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param->param, &value, &err)) {
            sdk_wrapper_log("[:] call <local_playback start> error:rs_parse_json_error\n");
            return rs_parse_json_error;
        }

        sync_play_ = value["sync play"].asBool();
        play_handle_ = RSPlayCreatePlayInstance(PLAY_LOCALFILE_TYPE);
        base_play_handle_ = play_handle_;
        if (play_handle_) {
            playback_cb_ = param->playback_cb;
            user_param_ = param->playback_user_param;

            RSPlaySetPlayWnd(play_handle_, param->window);
#ifdef __ANDROID__
            RSPlayRegisterBeforeRenderCallback(play_handle_, BEFORE_RENDER_CALLBACK_FUN, this);
#endif
            
            PlayFileListInfo play_info = {0};
            PlayFileListInfo* play_info_pointer = &play_info;
            int play_info_size = 1;

            std::string file_name = value["file name"].asString();
            std::string password = value["password"].asString();
            if (!file_name.empty()) {
                memcpy(play_info_pointer->sFilePath, file_name.c_str(), std::min(sizeof(play_info.sFilePath)-1, (size_t)file_name.length()));
                memcpy(play_info_pointer->password, password.c_str(), std::min(sizeof(play_info.password)-1, password.length()));
            } else {
                Json::Value val(Json::arrayValue);
                val = value["file list"];
                play_info_size = val.size();
                if (play_info_size) {
                    play_info_pointer = new (std::nothrow) PlayFileListInfo[play_info_size];
                    if (play_info_pointer) {
                        memset(play_info_pointer, 0, sizeof(PlayFileListInfo) * play_info_size);
                    } else {
                        sdk_wrapper_log("[:] call <local_playback start> result:new failed\n");
                        return rs_fail;
                    }

                    int count = 0;
                    for (int i = 0; i < play_info_size; i++) {
                        file_name = val[i]["path"].asString();
                        play_info_pointer[i].nBeginTime = val[i]["begin time"].asUInt64();
                        play_info_pointer[i].nEndTime = val[i]["end time"].asUInt64();
                        memcpy(play_info_pointer[i].sFilePath, file_name.c_str(), std::min(sizeof(play_info.sFilePath)-1, (size_t)file_name.length()));
                        memcpy(play_info_pointer[i].password, password.c_str(), std::min(sizeof(play_info.password)-1, password.length()));
                        ++count;
                    }
                    if (play_info_size != count) {
                        sdk_wrapper_log("[:] call <local_playback start> result:drop %d files for get time failed\n", play_info_size-count);
                    }
                    play_info_size = count;
                } else {
                    sdk_wrapper_log("[:] call <local_playback start> result:\"file list\" is empty\n");
                    return rs_fail;
                }
            }

            RSPlayNewOpenPlayFileListExParam file_param = {0};
            file_param.info = play_info_pointer;
            file_param.count = play_info_size;

            int result = RSPlayNewOpenPlayFileListEx(play_handle_, &file_param);
            if (play_info_pointer && play_info_pointer != &play_info) {
                delete[] play_info_pointer;
            }

            switch (result)
            {
            case 0:
                RSPlaySetCallbackMessageEx(play_handle_, PLAY_FUN_CALLBACK_FUN, this);
                if (param->draw_cb)
                    RSPlayRegisterSdkwrapperDrawCallback(play_handle_, param->draw_cb, param->playback_user_param);
                if (!sync_play_)
                    RSPlayStartPlay(play_handle_);
                base_running_ = true;
                sdk_wrapper_log("[:] call <local_playback start> result:success\n");
                return rs_success;
            	break;
            case -2:
                sdk_wrapper_log("[:] call <local_playback start> error:rs_file_not_found\n");
                return rs_file_not_found;
                break;
            case -3:
                sdk_wrapper_log("[:] call <local_playback start> error:rs_file_access_error\n");
                return rs_file_access_error;
                break;
            case -4:
                sdk_wrapper_log("[:] call <local_playback start> error:rs_need_input_password\n");
                return rs_need_input_password;
                break;
            case -5:
                sdk_wrapper_log("[:] call <local_playback start> error:rs_hk_mp4_file\n");
                return rs_hk_mp4_file;
                break;
            case -6:
                sdk_wrapper_log("[:] call <local_playback start> error:rs_unknown_mp4_file\n");
                return rs_unknown_mp4_file;
                break;
            default:
                sdk_wrapper_log("[:] call <local_playback start> error:rs_unknown_error\n");
                return rs_unknown_error;
                break;
            }
        } else {
            sdk_wrapper_log("[:] call <local_playback start> result:fail\n");
            return rs_fail;
        }
    }

    rs_error_code stop() {
        if (!base_running_ && !play_handle_)
            return rs_success;

        base_running_ = false;

        if (play_handle_) {
            RSPlayStopPlay(play_handle_);
            RSPlayDestroyPlayInstance(play_handle_);
            play_handle_ = NULL;
            base_play_handle_ = play_handle_;
        }
        playback_cb_ = NULL;
        user_param_ = NULL;
        sync_play_ = false;
        
        rs_scoped_lock lock(decoded_frame_mutex_);
        while (!decoded_frame_list_.empty()) {
            RS_PICTURE_S* frame = decoded_frame_list_.front();
            decoded_frame_list_.pop_front();
            free(frame);
        }

        sdk_wrapper_log("[:] call <local_playback stop> result:success\n");
        return rs_success;
    }

    bool is_sync_play() {
        return sync_play_; 
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
    
    uint64_t convert_utc_to_microsecond(const char* param) {
        int year, month, day, hour, minute, second;
        sscanf(param, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
        month--;
        day--;
        
        int days = 0;
        for (int begin_year = 1970; begin_year < year; begin_year++) {
            if ((begin_year%4 == 0 && begin_year%100 != 0) || begin_year%400 == 0)
                days += 366;
            else
                days += 365;
        }
        
        static int global_rs_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        for (int begin_month = 0; begin_month < month; begin_month++) {
            if (begin_month == 1 && ((year%4 == 0 && year%100 != 0) || year%400 == 0))
                days += 29;
            else
                days += global_rs_month[begin_month];
        }
        days += day;
        
        uint64_t secons = (days*24*60*60 + hour*60*60 + minute*60 + second);
        secons *= 1000000;
        return secons;
    }
    
    rs_error_code seek_by_time(const char* param) {
        ULONGLONG current_time = convert_utc_to_microsecond(param);
        if (play_handle_ && RSPlaySetCurPlayedTimeEX(play_handle_, current_time) == 0) {
            return rs_success;
        }
        return rs_fail;
    }

    rs_error_code seek_by_key_frame_index(int key_frame_index) {
        if (play_handle_ && RSPlaySeekByKeyFrameIndex(play_handle_, key_frame_index) == 0) {
            return rs_success;
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
            } else {
                return rs_fail;
            }

            RSPlaySetPlayMode(play_handle_, play_mode, 0);
            return rs_success;
        }
        return rs_fail;
    }

private:
    RSPlayHandle             play_handle_;
    playback_callback        playback_cb_;
    void*                    user_param_;
    bool                     sync_play_;

    rs_mutex                 decoded_frame_mutex_;
    std::list<RS_PICTURE_S*> decoded_frame_list_;
};
