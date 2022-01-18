#pragma once
#include <list>

class preview : public base_instance {
public:
    explicit preview(void* parent, connection& conn)
        : base_instance(parent, PREVIEW_INSTANCE_TYPE, "preview", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection()) 
        , play_handle_(NULL)
        , net_handle_(NULL)
        , preview_cb_(NULL)
        , user_param_(NULL)
        , channel_(0)
    {
        memset(&preview_param_, 0, sizeof(preview_param_));
    }

    ~preview() {
        stop();
    }

    static int CALLBACK BEFORE_RENDER_CALLBACK_FUN(void* data, void* user_param) {
        preview* _this = static_cast<preview*>(user_param);
        if (_this)
            return _this->BEFORE_RENDER_CALLBACK_FUN((RS_PICTURE_S*)data);
        return 0;
    }

    static void RSNET_CALL RSNetPreviewDataCallbackFun(void* data, UINT size, void* userParam) {
        preview* _this = static_cast<preview*>(userParam);
        if (_this)
            _this->RSNetPreviewDataCallbackFun(data, size);
    }

    static void RSNET_CALL RSNetPreviewStatusCallbackFun(WPARAM wparam, LPARAM lparam) {
        preview* _this = (preview*)(lparam);
        if (_this)
            _this->RSNetPreviewStatusCallbackFun((int64_t)wparam);
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
            }
        }
        return 0;
    }

    inline void RSNetPreviewDataCallbackFun(void* data, UINT size) {
        if (base_running_ && play_handle_) {
            //RSFrameHead* head = (RSFrameHead*)data;
            //if (head)
            //    printf("frame no:%d, frame type:%c, frame size:%d, time:%lld\n", \
            //            head->FrameNo, head->FrameType, head->FrameSize, head->Time);
            RSPlayInputNetFrame(play_handle_, data, size);
        }
    }

    void RSNetPreviewStatusCallbackFun(int64_t msg) {
        if (base_running_ && preview_cb_) {
            std::string err;
            switch (msg)
            {
            case RSNetMsgPreviewWaitLogin:
                err = "";
            	break;
            case RSNetMsgPreviewOpenStream:
                err = "start open stream";
                break;
            case RSNetMsgPreviewOpenStreamSuccess:
                err = "open stream success";
                break;
            case RSNetMsgPreviewOpenStreamFail:
                err = "open stream failed";
                break;
            case RSNetMsgPreviewStreamClosed:
                err = "preivew closed";
                break;
            case RSNetMsgPreviewMaxPrevNumErr:
                err = "max preivew number";
                break;
            case RSNetMsgRecordPlayDevicePlayback:
                err = "device playback";
                break;
            case RSNetMsgNoBandWidth:
                err = "not enough bandwidth";
                break;
            case RSNetMsgNoPreviewAuth:
                err = "no authority";
                break;
            case RSMetMsgPreviewActivateFaile:
                err = "preview active failed";
                break;
            case RSNetMsgPreviewNetworkFrameArrive:
                err = "network frame arrieved";
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

                preview_cb_(result.c_str(), user_param_);
            }
        }
    }

    rs_error_code start(const preview_param* param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param->param, &value, &err)) {
            sdk_wrapper_log("[%s] call <preview start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        play_handle_ = RSPlayCreatePlayInstance(PLAY_NETSTREAM_TYPE);
        base_play_handle_ = play_handle_;
        if (play_handle_) {
            preview_cb_ = param->preview_cb;
            user_param_ = param->preview_user_param;

            RSPlaySetPlayWnd(play_handle_, (param->picture_cb == NULL) ? param->window : NULL);
#ifdef __ANDROID__
            RSPlayRegisterBeforeRenderCallback(play_handle_, BEFORE_RENDER_CALLBACK_FUN, this);
#endif
            RSPlaySetCushionRange(play_handle_, true, 200);
            if (param->draw_cb)
                RSPlayRegisterSdkwrapperDrawCallback(play_handle_, param->draw_cb, param->preview_user_param);

            bool enable = false;
            PictureCallbackParam picture_param = {0};
            if (param->picture_cb) {
                picture_param.cb = param->picture_cb;
                picture_param.user_param = param->preview_user_param;
                enable = true;
            }

            if (param->background_picture && param->background_picture_size) {
                picture_param.base64_bmp_picture = param->background_picture;
                picture_param.base64_bmp_picture_size = param->background_picture_size;
                enable = true;
            }

            if (enable)
                RSPlayRegisterPictureCallback(play_handle_, &picture_param);
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

        memset(&preview_param_, 0, sizeof(preview_param_));
        preview_param_.Param.Channel = value["channel"].asUInt();
        channel_ = preview_param_.Param.Channel;
        preview_param_.Param.Type = type;
        preview_param_.Protocol = 0;
        preview_param_.AutoReconnect = value["auto connect"].asBool();
        preview_param_.DataCallback = RSNetPreviewDataCallbackFun;
        preview_param_.UserParam = this;
        preview_param_.Wnd = NULL;
        preview_param_.Message = 0;
        preview_param_.StatusCallback = RSNetPreviewStatusCallbackFun;
        net_handle_ = RSNetStartPreview(conn_, &preview_param_);

        base_running_ = net_handle_ ? true : false;
        sdk_wrapper_log("[%s ch:%d] call <preview start> result:%s\n", ip_or_id_.c_str(), channel_, net_handle_ ? "success" : "fail");
        return net_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !net_handle_ && !play_handle_)
            return rs_success;

        base_running_ = false;

        if (net_handle_) {
            RSNetStopPreview(conn_, &net_handle_);
            net_handle_ = NULL;
        }

        if (play_handle_) {
            RSPlayStopPlay(play_handle_);
            RSPlayDestroyPlayInstance(play_handle_);
            play_handle_ = NULL;
            base_play_handle_ = play_handle_;
        }

        preview_cb_ = NULL;
        user_param_ = NULL;

        rs_scoped_lock lock(decoded_frame_mutex_);
        while (!decoded_frame_list_.empty()) {
            RS_PICTURE_S* frame = decoded_frame_list_.front();
            decoded_frame_list_.pop_front();
            free(frame);
        }

        sdk_wrapper_log("[%s ch:%d] call <preview stop> result:success\n", ip_or_id_.c_str(), channel_);
        return rs_success;
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

            if (preview_param_.Param.Type != type) {
                preview_param_.Param.Type = type;
                RSNetStopPreview(conn_, &net_handle_);
                net_handle_ = NULL;
                RSPlayClearFrameBuffer(play_handle_);
                net_handle_ = RSNetStartPreview(conn_, &preview_param_);
                if (net_handle_)
                    return rs_success;
            } else {
                return rs_success;
            }
        }
        return rs_fail;
    }

private:
    RSNetConnection          conn_;
    RSNetPreviewParam        preview_param_;

    RSPlayHandle             play_handle_;
    RSNetPreview             net_handle_;
    preivew_callback         preview_cb_;
    void*                    user_param_;
    uint32_t                 channel_;

    rs_mutex                 decoded_frame_mutex_;
    std::list<RS_PICTURE_S*> decoded_frame_list_;
};
