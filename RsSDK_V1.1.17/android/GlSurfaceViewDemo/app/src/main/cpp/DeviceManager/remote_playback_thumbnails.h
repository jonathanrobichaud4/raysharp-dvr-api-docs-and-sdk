#pragma once

class remote_playback_thumbnails : public base_instance {
public:
    remote_playback_thumbnails(void* parent, connection& conn) 
        : base_instance(parent, REMOTE_PLAYBACK_THUMBNAILS_INSTANCE_TYPE, "remote_playback_thumbnails", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , search_handle_(NULL) 
        , picture_type_(JPEG_PICTURE)
        , reverse_callback_(false)
        , thumbnails_net_handle_(NULL)
        , channel_(0)
    {
    }

    ~remote_playback_thumbnails() {
        stop();
    }

    static void RSNET_CALL RSNetNewQueryRecordDetailThumbnailsCallbackFunEx(const NewRecordDetailRsp* rsp, int count, void* user_param) {
        remote_playback_thumbnails* _this = static_cast<remote_playback_thumbnails*>(user_param);
        if (_this)
            _this->search_record_callback(rsp, count);
    }

    static void RSNET_CALL RSNetPlaybackThumbnailsCallbackFun(ThumbnailsDecode* info, void* user_param) {
        remote_playback_thumbnails* _this = static_cast<remote_playback_thumbnails*>(user_param);
        if (_this)
            _this->RSNetPlaybackThumbnailsCallbackFun(info);
    }
    
    void RSNetPlaybackThumbnailsCallbackFun(ThumbnailsDecode* info) {
        if (base_running_ && thumbnails_callback_) {
            if (info) {
                Json::Value result;
                result["callback type"] = "thumbnail search";
                result["file name"] = info->file_name ? info->file_name : "";

                {
                    NewRecordDetailRsp* rsp = &info->rsp->rsp;
                    char buf[128] = {0};
#ifdef _MSC_VER
                    sprintf_s(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                        rsp->Begin.Year, rsp->Begin.Month, rsp->Begin.Day, rsp->Begin.Hour, rsp->Begin.Minute, rsp->Begin.Second, \
                        rsp->End.Year, rsp->End.Month, rsp->End.Day, rsp->End.Hour, rsp->End.Minute, rsp->End.Second);
#else
                    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                        rsp->Begin.Year, rsp->Begin.Month, rsp->Begin.Day, rsp->Begin.Hour, rsp->Begin.Minute, rsp->Begin.Second, \
                        rsp->End.Year, rsp->End.Month, rsp->End.Day, rsp->End.Hour, rsp->End.Minute, rsp->End.Second);
#endif

                    int index = 0;
                    uint64_t second_since_1970 = mktime_no_time_zone(rsp->Begin.Year,rsp->Begin.Month,\
                        rsp->Begin.Day,rsp->Begin.Hour,rsp->Begin.Minute,rsp->Begin.Second);
                    std::map<uint64_t, int>::iterator itor = record_info_index_.find(second_since_1970);
                    if (itor != record_info_index_.end())
                        index = itor->second;

                    Json::Value value;
                    value["index"] = index;
                    value["time"] = buf;
                    value["size"] = rsp->Size;
                    value["type"] = rsp->Type;
                    result["detail info"].append(value);
                }

                Json::StreamWriterBuilder writer;
                std::string _result = Json::writeString(writer, result);

                thumbnails_callback_(_result.c_str(), user_param_);
            } else {
                thumbnails_callback_(NULL, user_param_);
            }
        }
    }

    void search_record_callback(const NewRecordDetailRsp* rsp, int count) {
        if (base_running_ && rsp && count) {
            int struct_size = rsp->StructSize;
            char* begin_data = (char*)rsp;

            char buf[128] = {0};
            Json::Value value;
            Json::Value result;
            result["callback type"] = "day search";
            Json::StreamWriterBuilder writer;
            NewRecordDetailRsp record_rsp = {0};
            std::vector<NewRecordDetailRsp> vec_record_rsp;
            vec_record_rsp.reserve(count);

            for (int i = 0; i < count; i++) {
                NewRecordDetailRsp* temp_rsp = (NewRecordDetailRsp*)(begin_data + i * struct_size);
                if (sizeof(NewRecordDetailRsp) > struct_size) {
                    memcpy(&record_rsp, temp_rsp, struct_size);
                    temp_rsp = &record_rsp;
                }
                vec_record_rsp.push_back(*temp_rsp);
            }
            if (reverse_callback_)
                std::reverse(vec_record_rsp.begin(), vec_record_rsp.end());

            for (int i = 0; i < count; i++) {
                NewRecordDetailRsp* temp_rsp = &vec_record_rsp.at(i);
#ifdef _MSC_VER
                sprintf_s(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                    temp_rsp->Begin.Year, temp_rsp->Begin.Month, temp_rsp->Begin.Day, \
                    temp_rsp->Begin.Hour, temp_rsp->Begin.Minute, temp_rsp->Begin.Second, \
                    temp_rsp->End.Year, temp_rsp->End.Month, temp_rsp->End.Day, \
                    temp_rsp->End.Hour, temp_rsp->End.Minute, temp_rsp->End.Second);
#else
                sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                    temp_rsp->Begin.Year, temp_rsp->Begin.Month, temp_rsp->Begin.Day, \
                    temp_rsp->Begin.Hour, temp_rsp->Begin.Minute, temp_rsp->Begin.Second, \
                    temp_rsp->End.Year, temp_rsp->End.Month, temp_rsp->End.Day, \
                    temp_rsp->End.Hour, temp_rsp->End.Minute, temp_rsp->End.Second);
#endif

                int index = generate_int_index();
                uint64_t second_since_1970 = mktime_no_time_zone(temp_rsp->Begin.Year,temp_rsp->Begin.Month,\
                    temp_rsp->Begin.Day,temp_rsp->Begin.Hour,temp_rsp->Begin.Minute,temp_rsp->Begin.Second);
                record_info_index_.insert(std::make_pair(second_since_1970, index));

                value["index"] = index;
                value["time"] = buf;
                value["size"] = rsp->Size;
                value["type"] = rsp->Type;
                result["detail info"].append(value);
            }
            
            std::string _result = Json::writeString(writer, result);
            thumbnails_callback_(_result.c_str(), user_param_);

            RSNetPlaybackThumbnailsParam _param = {0};
            _param.list_param = &vec_record_rsp.at(0);
            _param.list_param_size = count;
            _param.callback = RSNetPlaybackThumbnailsCallbackFun;
            _param.user_param = this;
            _param.file_directory = file_directory_.c_str();
            _param.picture_type = picture_type_;

            if (base_running_)
                thumbnails_net_handle_ = RSNetStartGetPlaybackThumbnails(conn_, &_param);
        }
    }

    rs_error_code start(const char* param, playback_thumbnails_callback cb, void* user_param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[%s] call <remote_playback_thumbnails start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        thumbnails_callback_ = cb;
        user_param_ = user_param;

        file_directory_ = value["file directory"].asString();
        picture_type_ = JPEG_PICTURE;
        std::string str_picture_type = value["picture type"].asString();
        if (str_picture_type == "png")
            picture_type_ = PNG_PICTURE;
        reverse_callback_ = value["reverse callback"].asBool();

        UINT channel = value["channel"].asUInt();
        UINT record_type = value["record type"].asUInt();
        char stream_type = 0;
        std::string temp = value["stream type"].asString();
        if (temp == "main stream")
            stream_type = 0;
        else if (temp == "sub stream")
            stream_type = 1;
        else if (temp == "mobile stream")
            stream_type = 2;

        DateTime begin_time = {0};
        DateTime end_time = {0};
        {
            int year, month, day, hour, minute, second;
            sscanf(value["begin time"].asCString(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            begin_time.Year = year;
            begin_time.Month = month;
            begin_time.Day = day;
            begin_time.Hour = hour;
            begin_time.Minute = minute;
            begin_time.Second = second;

            sscanf(value["end time"].asCString(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            end_time.Year = year;
            end_time.Month = month;
            end_time.Day = day;
            end_time.Hour = hour;
            end_time.Minute = minute;
            end_time.Second = second;
        }

        RSNetQueryRecordFileByDayParam _param = {0};
        _param.channel = channel;
        channel_ = _param.channel;
        _param.record_type = record_type;
        _param.stream_type = stream_type; //0 main 1 sub 2 mobile
        _param.enable_smart_search;
        _param.smart_region[18];
        _param.begin_time = begin_time;
        _param.end_time = end_time;
        _param.union_flag = 4;
        _param.new_day_search_callback_ex = RSNetNewQueryRecordDetailThumbnailsCallbackFunEx;
        _param.user_param = this;
        search_handle_ = RSNetAsyncQueryRecordFileByDay(conn_, &_param);

        base_running_ = search_handle_ ? true : false;
        sdk_wrapper_log("[%s ch:%d] call <remote_playback_thumbnails start> result:%s\n", ip_or_id_.c_str(), channel_, search_handle_ ? "success" : "fail");
        return search_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !search_handle_ && !thumbnails_net_handle_)
            return rs_success;

        base_running_ = false;

        if (conn_ && search_handle_)
            RSNetAsyncQueryRecordFileStop(conn_, search_handle_);
        search_handle_ = NULL;

        if (thumbnails_net_handle_) {
            RSNetStopGetPlaybackThumbnails(&thumbnails_net_handle_);
            thumbnails_net_handle_ = NULL;
        }

        picture_type_ = JPEG_PICTURE;
        thumbnails_callback_ = NULL;
        user_param_ = NULL;
        reverse_callback_ = false;

        record_info_index_.clear();

        sdk_wrapper_log("[%s ch:%d] call <remote_playback_thumbnails stop> result:success\n", ip_or_id_.c_str(), channel_);
        return rs_success;
    }

private:
    static inline uint64_t mktime_no_time_zone(int year, int mon, int day, int hour, int min, int sec) {
        if (0 >= (int) (mon -= 2)){
            mon += 12;
            year -= 1;
        }
        return ((((uint64_t)(year/4 - year/100 + year/400 + 367*mon/12 + day) + year*365 - 719499)*24 + hour)*60 + min)*60 + sec;
    }

    RSNetConnection                 conn_;
    RSRecordSearch                  search_handle_;

    std::string                     file_directory_;
    THUMBNAILS_DECODE_TYPE          picture_type_;
    bool                            reverse_callback_;

    RSNetThumbnailsConn             thumbnails_net_handle_;
    playback_thumbnails_callback    thumbnails_callback_;
    void*                           user_param_;
    std::map<uint64_t, int>         record_info_index_;

    uint32_t                        channel_;
};
