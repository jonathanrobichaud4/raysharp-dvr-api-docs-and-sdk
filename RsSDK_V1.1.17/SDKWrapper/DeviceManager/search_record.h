#pragma once
#include <assert.h>

class search_record : public base_instance {
public:
    search_record(void* parent, connection& conn)
        : base_instance(parent, SEARCH_RECORD_INSTANCE_TYPE, "search_record", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , search_handle_(NULL) 
        , month_cb_(NULL) 
        , day_cb_(NULL) 
        , user_param_(NULL) 
        , channel_(0)
        , stream_type_(0)
    {

    }

    ~search_record() {
        stop();
    }

    static void RSNET_CALL RSNetQueryRecordDayOutlineCallbackFunEx(const RecordDayOutlineRsp* rsp, int count, void* userParam) {
        search_record* _this = static_cast<search_record*>(userParam);
        if (_this)
            _this->RSNetQueryRecordDayOutlineCallbackFunEx(rsp, count);
    }

    static void RSNET_CALL RSNetQueryRecordDetailCallbackFunEx(const RecordDetailRsp* rsp, int count, void* userParam) {
        search_record* _this = static_cast<search_record*>(userParam);
        if (_this)
            _this->RSNetQueryRecordDetailCallbackFunEx(rsp, count);
    }

    static void RSNET_CALL RSNetNewQueryRecordDetailCallbackFunEx(const NewRecordDetailRsp* rsp, int count, void* userParam) {
        search_record* _this = static_cast<search_record*>(userParam);
        if (_this)
            _this->RSNetNewQueryRecordDetailCallbackFunEx(rsp, count);
    }

    static void RSNET_CALL RSNetQueryRecordStatusCallbackFun(const QueryStatusCallbackInfo* info, void* user_param) {
        search_record* _this = static_cast<search_record*>(user_param);
        if (_this)
            _this->RSNetQueryRecordStatusCallbackFun(info);
    }

    void RSNetQueryRecordDayOutlineCallbackFunEx(const RecordDayOutlineRsp* rsp, int count) {
        if (base_running_ && month_cb_) {
            RecordDayOutlineRsp record_rsp = {0};
            
            std::string result;
            Json::Value value;
            Json::StreamWriterBuilder writer;
            
            if (rsp && count) {
                int struct_size = rsp->StructSize;
                char* begin_data = (char*)rsp;

                for (int i = 0; i < count && base_running_; i++) {
                    RecordDayOutlineRsp* temp_rsp = (RecordDayOutlineRsp*)(begin_data + i * struct_size);
                    if (sizeof(RecordDayOutlineRsp) > struct_size) {
                        memcpy(&record_rsp, temp_rsp, struct_size);
                        temp_rsp = &record_rsp;
                    }

                    value["day"] = temp_rsp->Day;
                    result = Json::writeString(writer, value);
                    month_cb_(result.c_str(), user_param_);
                }
            }
            month_cb_(NULL, user_param_);
        }
    }

    void RSNetQueryRecordDetailCallbackFunEx(const RecordDetailRsp* rsp, int count) {
        if (base_running_ && day_cb_) {
            RecordDetailRspInfo rsp_info = {0};
            RecordDetailRsp& record_rsp = rsp_info.rsp;
            rsp_info.channel = channel_;
            rsp_info.stream_type = stream_type_;
            
            char buf[128] = {0};
            std::string result;
            Json::Value value;
            Json::StreamWriterBuilder writer;
            
            if (rsp && count) {
                int struct_size = rsp->StructSize;
                char* begin_data = (char*)rsp;
                
                for (int i = 0; i < count && base_running_; i++) {
                    RecordDetailRsp* temp_rsp = (RecordDetailRsp*)(begin_data + i * struct_size);
                    if (sizeof(RecordDetailRsp) <= struct_size) {
                        memcpy(&record_rsp, temp_rsp, sizeof(RecordDetailRsp));
                    } else {
                        memcpy(&record_rsp, temp_rsp, struct_size);
                    }

#ifdef _MSC_VER
                    sprintf_s(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                        record_rsp.Begin.Year, record_rsp.Begin.Month, record_rsp.Begin.Day, \
                        record_rsp.Begin.Hour, record_rsp.Begin.Minute, record_rsp.Begin.Second, \
                        record_rsp.End.Year, record_rsp.End.Month, record_rsp.End.Day, \
                        record_rsp.End.Hour, record_rsp.End.Minute, record_rsp.End.Second);
#else
                    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                        record_rsp.Begin.Year, record_rsp.Begin.Month, record_rsp.Begin.Day, \
                        record_rsp.Begin.Hour, record_rsp.Begin.Minute, record_rsp.Begin.Second, \
                        record_rsp.End.Year, record_rsp.End.Month, record_rsp.End.Day, \
                        record_rsp.End.Hour, record_rsp.End.Minute, record_rsp.End.Second);
#endif

                    int index = generate_int_index();
                    map_record_detail_rsp_.insert(std::make_pair(index, rsp_info));
                    vec_record_detail_rsp_.push_back(rsp_info.rsp);

                    Json::Value value;
                    value["index"] = index;
                    value["time"] = buf;
                    value["size"] = temp_rsp->Size;
                    value["type"] = temp_rsp->Type;

                    result = Json::writeString(writer, value);
                    day_cb_(result.c_str(), user_param_);
                }
            }
            day_cb_(NULL, user_param_);
        }
    }

    void RSNetNewQueryRecordDetailCallbackFunEx(const NewRecordDetailRsp* rsp, int count) {
        if (base_running_ && day_cb_) {
            NewRecordDetailRspInfo rsp_info = {0};
            NewRecordDetailRsp& record_rsp = rsp_info.rsp;
            rsp_info.channel = channel_;
            rsp_info.stream_type = stream_type_;
            
            char buf[128] = {0};
            std::string result;
            Json::Value value;
            Json::StreamWriterBuilder writer;
            
            if (rsp && count) {
                int struct_size = rsp->StructSize;
                char* begin_data = (char*)rsp;

                for (int i = 0; i < count && base_running_; i++) {
                    NewRecordDetailRsp* temp_rsp = (NewRecordDetailRsp*)(begin_data + i * struct_size);
                    if (sizeof(NewRecordDetailRsp) <= struct_size) {
                        memcpy(&record_rsp, temp_rsp, sizeof(NewRecordDetailRsp));
                    } else {
                        memcpy(&record_rsp, temp_rsp, struct_size);
                    }

#ifdef _MSC_VER
                    sprintf_s(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                        record_rsp.Begin.Year, record_rsp.Begin.Month, record_rsp.Begin.Day, \
                        record_rsp.Begin.Hour, record_rsp.Begin.Minute, record_rsp.Begin.Second, \
                        record_rsp.End.Year, record_rsp.End.Month, record_rsp.End.Day, \
                        record_rsp.End.Hour, record_rsp.End.Minute, record_rsp.End.Second);
#else
                    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d", \
                        record_rsp.Begin.Year, record_rsp.Begin.Month, record_rsp.Begin.Day, \
                        record_rsp.Begin.Hour, record_rsp.Begin.Minute, record_rsp.Begin.Second, \
                        record_rsp.End.Year, record_rsp.End.Month, record_rsp.End.Day, \
                        record_rsp.End.Hour, record_rsp.End.Minute, record_rsp.End.Second);
#endif

                    int index = generate_int_index();
                    map_new_record_detail_rsp_.insert(std::make_pair(index, rsp_info));
                    vec_new_record_detail_rsp_.push_back(rsp_info.rsp);

                    Json::Value value;
                    value["index"] = index;
                    value["time"] = buf;
                    value["size"] = temp_rsp->Size;
                    value["type"] = temp_rsp->Type;

                    result = Json::writeString(writer, value);
                    day_cb_(result.c_str(), user_param_);
                }
            }
            day_cb_(NULL, user_param_);
        }
    }
    
    void RSNetQueryRecordStatusCallbackFun(const QueryStatusCallbackInfo* info) {
        if (base_running_ && info && info->authority_fail) {
            std::string result;
            Json::Value value;
            Json::StreamWriterBuilder writer;

            value["status"] = "no authority";
            result = Json::writeString(writer, value);

            if (day_cb_)
                day_cb_(result.c_str(), user_param_);
            if (month_cb_)
                month_cb_(result.c_str(), user_param_);
        }
    }

    rs_error_code start(const char* param, search_record_month_callback month_cb, search_record_day_callback day_cb, void* user_param) {
        stop();

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)){
            sdk_wrapper_log("[%s] call <search_record start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        std::string temp = value["stream type"].asString();
        if (temp == "main stream")
            stream_type_ = 0;
        else if (temp == "sub stream")
            stream_type_ = 1;
        else if (temp == "mobile stream")
            stream_type_ = 2;
        UINT record_type = value["record type"].asUInt();
        bool detail_info = value["detail info"].asBool();

        DateTime begin_time = {0};
        DateTime end_time = {0};
        if (month_cb) {
            sscanf(value["time"].asCString(), "%d-%d", &begin_time.Year, &begin_time.Month);
            end_time = begin_time;

            begin_time.Day = 1;
            begin_time.Hour = 0;
            begin_time.Minute = 0;
            begin_time.Second = 0;

            end_time.Day = get_days_in_month(begin_time.Year, begin_time.Month);
            end_time.Hour = 23;
            end_time.Minute = 59;
            end_time.Second = 59;
        } else {
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

        month_cb_ = month_cb;
        day_cb_ = day_cb;
        user_param_ = user_param;

        if (month_cb_) {
            RSNetQueryRecordFileByMonthParam _param = {0};

            std::string channel = value["channel"].asString();
            if (channel.empty() || channel == "all") {
                for (int i = 0; i < _countof(_param.channel); i++)
                    _param.channel[i] = 0xffffffff;
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
                    _param.channel[channel_no/32] |= (0x1 << (channel_no%32));
                }
            }

            _param.channel[8];
            _param.record_type = record_type;
            _param.stream_type = stream_type_;
            _param.enable_smart_search;
            _param.smart_region[18];
            _param.begin_time = begin_time;
            _param.end_time = end_time;
            _param.month_search_callback_ex = RSNetQueryRecordDayOutlineCallbackFunEx;
            _param.status_callback = RSNetQueryRecordStatusCallbackFun;
            _param.user_param = this;

            search_handle_ = RSNetAsyncQueryRecordFileByMonth(conn_, &_param);
        } else {
            RSNetQueryRecordFileByDayParam _param = {0};
            channel_ = value["channel"].asUInt();

            _param.channel = channel_;
            _param.record_type = record_type;
            _param.stream_type = stream_type_; //0 main 1 sub 2 mobile
            _param.enable_smart_search;
            _param.smart_region[18];
            _param.begin_time = begin_time;
            _param.end_time = end_time;
            _param.union_flag = detail_info ? 4 : 3;
            if (detail_info)
                _param.new_day_search_callback_ex = RSNetNewQueryRecordDetailCallbackFunEx; //union_flag = 4;
            else
                _param.day_search_callback_ex = RSNetQueryRecordDetailCallbackFunEx; //union_flag = 3;
            _param.status_callback = RSNetQueryRecordStatusCallbackFun;
            _param.user_param = this;

            search_handle_ = RSNetAsyncQueryRecordFileByDay(conn_, &_param);
        }
        
        base_running_ = search_handle_ ? true : false;
        if (month_cb_)
            sdk_wrapper_log("[%s ch:%d] call <search_record_month start> result:%s\n", ip_or_id_.c_str(), channel_, search_handle_ ? "success" : "fail");
        else
            sdk_wrapper_log("[%s ch:%d] call <search_record_day start> result:%s\n", ip_or_id_.c_str(), channel_, search_handle_ ? "success" : "fail");
        return search_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !search_handle_)
            return rs_success;

        base_running_ = false;

        if (conn_ && search_handle_)
            RSNetAsyncQueryRecordFileStop(conn_, search_handle_);
        conn_ = NULL;
        search_handle_ = NULL;

        bool month_search = month_cb_ ? true : false;
        month_cb_ = NULL;
        day_cb_ = NULL;
        user_param_ = NULL;
        stream_type_ = 0;

        if (month_search)
            sdk_wrapper_log("[%s ch:%d] call <search_record_month stop> result:success\n", ip_or_id_.c_str(), channel_);
        else
            sdk_wrapper_log("[%s ch:%d] call <search_record_day stop> result:success\n", ip_or_id_.c_str(), channel_);
        return rs_success;
    }

    bool get_record_detail_rsp(int index, RecordDetailRspInfo& rsp) {
        std::map<int, RecordDetailRspInfo>::iterator itor = map_record_detail_rsp_.find(index);
        if (itor != map_record_detail_rsp_.end()) {
            memset(&rsp, 0, sizeof(rsp));
            memcpy(&rsp, &itor->second, sizeof(rsp));
            return true;
        }
        return false;
    }

    bool get_new_record_detail_rsp(int index, NewRecordDetailRspInfo& rsp) {
        std::map<int, NewRecordDetailRspInfo>::iterator itor = map_new_record_detail_rsp_.find(index);
        if (itor != map_new_record_detail_rsp_.end()) {
            memset(&rsp, 0, sizeof(rsp));
            memcpy(&rsp, &itor->second, sizeof(rsp));
            return true;
        }
        return false;
    }

    int64_t get_record_total_size(const DateTime& begin_time, const DateTime& end_time) {
        int64_t total_size = 0;
        uint64_t begin_total = mktime_no_time_zone(begin_time.Year,begin_time.Month,\
                                             begin_time.Day,begin_time.Hour,\
                                             begin_time.Minute,begin_time.Second);
        uint64_t end_total = mktime_no_time_zone(end_time.Year,end_time.Month,\
                                           end_time.Day,end_time.Hour,\
                                           end_time.Minute,end_time.Second);
        for (size_t i = 0; i < vec_record_detail_rsp_.size(); i++) {
            const RecordDetailRsp& rsp = vec_record_detail_rsp_.at(i);
            uint64_t begin_single = mktime_no_time_zone(rsp.Begin.Year,rsp.Begin.Month,\
                                                      rsp.Begin.Day,rsp.Begin.Hour,\
                                                      rsp.Begin.Minute,rsp.Begin.Second);
            uint64_t end_single = mktime_no_time_zone(rsp.End.Year,rsp.End.Month,\
                                                    rsp.End.Day,rsp.End.Hour,\
                                                    rsp.End.Minute,rsp.End.Second);
            
            if(begin_single > end_total || end_single < begin_total)
                continue;

            if(begin_single < begin_total && end_single <= end_total) { //front
                uint64_t partialRatio = end_single - begin_total;
                uint64_t blockRatio   = end_single - begin_single;
                float partialSize = 1.0f*partialRatio/blockRatio*rsp.Size;
                total_size += (int64_t)partialSize;
            } else if(begin_single > begin_total && end_single > end_total) { //rear
                uint64_t  partialRatio = end_total - begin_single;
                uint64_t blockRatio = end_single - begin_single;
                float partialSize = 1.0f*partialRatio/blockRatio*rsp.Size;
                total_size += (int64_t)partialSize;
            } else if(begin_single < begin_total && end_single > end_total) { //midddle
                uint64_t  partialRatio = end_total - begin_total;
                uint64_t blockRatio = end_single - begin_single;
                float partialSize = 1.0f*partialRatio/blockRatio*rsp.Size;
                total_size += (int64_t)partialSize;
            } else { //full
                total_size += rsp.Size;
            }
        }
        return total_size;
    }

    int64_t get_new_record_total_size(const DateTime& begin_time, const DateTime& end_time) {
        int64_t total_size = 0;
        uint64_t begin_total = mktime_no_time_zone(begin_time.Year,begin_time.Month,\
                                             begin_time.Day,begin_time.Hour,\
                                             begin_time.Minute,begin_time.Second);
        uint64_t end_total = mktime_no_time_zone(end_time.Year,end_time.Month,\
                                           end_time.Day,end_time.Hour,\
                                           end_time.Minute,end_time.Second);
        for (size_t i = 0; i < vec_new_record_detail_rsp_.size(); i++) {
            const NewRecordDetailRsp& rsp = vec_new_record_detail_rsp_.at(i);
            uint64_t begin_single = mktime_no_time_zone(rsp.Begin.Year,rsp.Begin.Month,\
                                                      rsp.Begin.Day,rsp.Begin.Hour,\
                                                      rsp.Begin.Minute,rsp.Begin.Second);
            uint64_t end_single = mktime_no_time_zone(rsp.End.Year,rsp.End.Month,\
                                                    rsp.End.Day,rsp.End.Hour,\
                                                    rsp.End.Minute,rsp.End.Second);

            if(begin_single > end_total || end_single < begin_total)
                continue;

            if(begin_single < begin_total && end_single <= end_total) { //front
                uint64_t partialRatio = end_single - begin_total;
                uint64_t blockRatio   = end_single - begin_single;
                float partialSize = 1.0f*partialRatio/blockRatio*rsp.Size;
                total_size += (int64_t)partialSize;
            } else if(begin_single > begin_total && end_single > end_total) { //rear
                uint64_t  partialRatio = end_total - begin_single;
                uint64_t blockRatio = end_single - begin_single;
                float partialSize = 1.0f*partialRatio/blockRatio*rsp.Size;
                total_size += (int64_t)partialSize;
            } else if(begin_single < begin_total && end_single > end_total) { //midddle
                uint64_t  partialRatio = end_total - begin_total;
                uint64_t blockRatio = end_single - begin_single;
                float partialSize = 1.0f*partialRatio/blockRatio*rsp.Size;
                total_size += (int64_t)partialSize;
            } else { //full
                total_size += rsp.Size;
            }
		}
        return total_size;
    }

public:
    std::map<int, RecordDetailRspInfo>    map_record_detail_rsp_;
    std::map<int, NewRecordDetailRspInfo> map_new_record_detail_rsp_;

    std::vector<RecordDetailRsp>          vec_record_detail_rsp_;
    std::vector<NewRecordDetailRsp>       vec_new_record_detail_rsp_;

private:
    static inline uint64_t mktime_no_time_zone(int year, int mon, int day, int hour, int min, int sec) {
        if (0 >= (int) (mon -= 2)){
            mon += 12;
            year -= 1;
        }
        return ((((uint64_t)(year/4 - year/100 + year/400 + 367*mon/12 + day) + year*365 - 719499)*24 + hour)*60 + min)*60 + sec;
    }

    unsigned char get_days_in_month(int year,int month) {
        static unsigned char days[]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (2 == month) {
            return ((((0 == year%4) && (0 != year%100)) || (0 == year % 400)) ? 29 : 28);
        } else {
            return days[month - 1];
        }
    }

    RSNetConnection              conn_;
    RSRecordSearch               search_handle_;

    search_record_month_callback month_cb_;
    search_record_day_callback   day_cb_;
    void*                        user_param_;
    int                          channel_;
    int                          stream_type_;
};
