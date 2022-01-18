#pragma once

class local_playback_thumbnails : public base_instance {
public:
    explicit local_playback_thumbnails(void* parent)
        : base_instance(parent, LOCAL_PLAYBACK_THUMBNAILS_INSTANCE_TYPE, "local_playback_thumbnails")
        , play_handle_(NULL)
        , local_thumbnails_cb_(NULL)
        , user_param_(NULL)
    {

    }

    ~local_playback_thumbnails() {
        stop();
    }

    static void RSPLAY_CALL THUMBNAILS_PLAY_FUN_CALLBACK_FUN(UINT message, void* userParam) {
        local_playback_thumbnails* _this = static_cast<local_playback_thumbnails*>(userParam);
        if (_this)
            _this->THUMBNAILS_PLAY_FUN_CALLBACK_FUN(message);
    }

    static void CALLBACK CAPTURE_PICTURE_CALLBACK_FUN(void* data, int size, ULONGLONG time, void* pUser) {
        local_playback_thumbnails* _this = static_cast<local_playback_thumbnails*>(pUser);
        if (_this)
            _this->CAPTURE_PICTURE_CALLBACK_FUN(data, size, time);
    }

    void THUMBNAILS_PLAY_FUN_CALLBACK_FUN(UINT message) {
        if (base_running_ && local_thumbnails_cb_) {
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

            //callback err to app
            Json::Value value;
            value["status"] = err;
            Json::StreamWriterBuilder writer;
            std::string result = Json::writeString(writer, value);
        }
    }

    void CAPTURE_PICTURE_CALLBACK_FUN(void* data, int size, ULONGLONG time) {
        if (base_running_ && data && size && local_thumbnails_cb_) {
            local_thumbnails_cb_(static_cast<unsigned char*>(data), size, NULL, user_param_);
        }
    }

    rs_error_code start(const char* param, local_playback_thumbnails_callback cb, void* user_param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_parse_json_error\n");
            return rs_parse_json_error;
        }

        int picture_type = 2;
        std::string str_picture_type = value["picture type"].asString();
        if (str_picture_type == "png")
            picture_type = 1;

        int width = value["width"].asInt();
        int height = value["height"].asInt();

        play_handle_ = RSPlayCreatePlayInstance(PLAY_LOCAL_THUMBNAIL);
        base_play_handle_ = play_handle_;
        if (play_handle_) {
            local_thumbnails_cb_ = cb;
            user_param_ = user_param;

            std::string file_name = value["file name"].asString();
            std::string password = value["password"].asString();
            PlayFileListInfo play_info = {0};
            memcpy(play_info.sFilePath, file_name.c_str(), std::min(sizeof(play_info.sFilePath)-1, (size_t)file_name.length()));
            memcpy(play_info.password, password.c_str(), std::min(sizeof(play_info.password)-1, password.length()));
            RSPlayNewOpenPlayFileListExParam file_param = {0};
            file_param.info = &play_info;
            file_param.count = 1;

            int result = RSPlayNewOpenPlayFileListEx(play_handle_, &file_param);
            switch (result)
            {
            case 0:
                RSPlaySetCapturePictureCallback(play_handle_, picture_type, CAPTURE_PICTURE_CALLBACK_FUN, this);
                RSPlaySetCallbackMessageEx(play_handle_, THUMBNAILS_PLAY_FUN_CALLBACK_FUN, this);
                RSPlayStartPlay(play_handle_);
                base_running_ = true;
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> result:success\n");
                return rs_success;
                break;
            case -2:
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_file_not_found\n");
                return rs_file_not_found;
                break;
            case -3:
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_file_access_error\n");
                return rs_file_access_error;
                break;
            case -4:
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_need_input_password\n");
                return rs_need_input_password;
                break;
            case -5:
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_hk_mp4_file\n");
                return rs_hk_mp4_file;
                break;
            case -6:
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_unknown_mp4_file\n");
                return rs_unknown_mp4_file;
                break;
            default:
                sdk_wrapper_log("[:] call <local_playback_thumbnails start> error:rs_unknown_error\n");
                return rs_unknown_error;
                break;
            }
        } else {
            sdk_wrapper_log("[:] call <local_playback_thumbnails start> result:fail\n");
            return rs_fail;
        }
    }

    rs_error_code input_local_playback_time(ULONGLONG millisecond) {
        if (base_running_ && play_handle_ && RSPlaySetCurPlayedTime(play_handle_, millisecond*1000) == 0) {
            return rs_success;
        }
        return rs_fail;
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
        local_thumbnails_cb_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[:] call <local_playback_thumbnails stop> result:success\n");
        return rs_success;
    }

private:
    RSPlayHandle                       play_handle_;
    local_playback_thumbnails_callback local_thumbnails_cb_;
    void*                              user_param_;
};
