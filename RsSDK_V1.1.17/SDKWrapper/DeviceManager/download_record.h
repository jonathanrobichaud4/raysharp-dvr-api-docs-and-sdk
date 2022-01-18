#pragma once
#include "search_record.h"

class download_record : public base_instance {
public:
    download_record(void* parent, connection& conn)
        : base_instance(parent, DOWNLOAD_RECORD_INSTANCE_TYPE, "download_record", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , download_handle_(NULL)
        , download_cb_(NULL)
        , user_param_(NULL)
        , channel_(0)
    {

    }

    ~download_record() {
        stop();
    }

    static void RSNET_CALL RSNetDownloadRecordStatusCallbackExFun(UINT code, UINT param, UINT nIndex, void* userParam) {
        download_record* _this = static_cast<download_record*>(userParam);
        if (_this)
            _this->RSNetDownloadRecordStatusCallbackExFun(code, param, nIndex);
    }

    void RSNetDownloadRecordStatusCallbackExFun(UINT code, UINT param, UINT nIndex) {
        if (base_running_ && download_cb_) {
            std::string err;
            switch (code)
            {
            case RSNetMsgRecordPlayHDDFormat:
                err = "hdd format";
            	break;
            case RSNetMsgRecordPlayDevicePlayback:
                err = "device playback";
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
            case RSNetMsgDownloadRecordClosed:
                err = "download close";
                break;
            case RSNetMsgDownloadRecordStoreFail:
                err = "storage record file err";
                break;
            case RSNetMsgDownloadRecordNoFile:
                err = "no file";
                break;
            case RSNetMsgDownloadRecordOK:
                err = "download ok";
                break;
            case RSNetMsgDownloadRecordPercent:
                err = "download percent";
                break;
            default:
                err = "unknown error";
                break;
            }

            Json::Value value;
            value["status"] = err;
            value["percent"] = param;
            Json::StreamWriterBuilder writer;
            std::string result = Json::writeString(writer, value);

            download_cb_(result.c_str(), user_param_);
        }
    }

    rs_error_code start(void* rsp, const char* param, download_callback download_cb, void* user_param, bool by_file, bool new_rsp, int64_t total_size) {
        stop();

        RecordDetailRspInfo& detail_rsp = *(RecordDetailRspInfo*)rsp;
        NewRecordDetailRspInfo& new_detail_rsp = *(NewRecordDetailRspInfo*)rsp;

        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[%s] call <download_record start> error:rs_parse_json_error\n", ip_or_id_.c_str());
            return rs_parse_json_error;
        }

        std::string file = value["file name"].asString();
        assert(!file.empty());

        download_cb_ = download_cb;
        user_param_ = user_param;

        if (by_file) {
            RSNetDownloadFileInfo file_info = {0};
            memcpy(file_info.file_name, file.c_str(), std::min(file.length(), _countof(file_info.file_name) - 1));

            RSNetDownloadByFileParam _param = {0};
            _param.channel = new_rsp ? new_detail_rsp.channel : detail_rsp.channel;
            channel_ = _param.channel;
            _param.stream_type = new_rsp ? new_detail_rsp.stream_type : detail_rsp.stream_type;
            _param.union_flag = new_rsp ? 2 : 1;
            if (_param.union_flag == 1)
                _param.rsp = &detail_rsp.rsp;
            else
                _param.rspnew = &new_detail_rsp.rsp;
            _param.file_info = &file_info;
            _param.file_count = 1;
            _param.max_single_file_size = value["max single file size"].asInt();
            _param.status_callback = RSNetDownloadRecordStatusCallbackExFun;
            _param.user_param = this;

            download_handle_ = RSNetStartDownloadByFile(conn_, &_param);
        } else {
            RSNetDownloadByTimeParam _param = {0};

            int year, month, day, hour, minute, second;
            sscanf(value["begin time"].asCString(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            _param.begin_time.Year = year;
            _param.begin_time.Month = month;
            _param.begin_time.Day = day;
            _param.begin_time.Hour = hour;
            _param.begin_time.Minute = minute;
            _param.begin_time.Second = second;

            sscanf(value["end time"].asCString(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            _param.end_time.Year = year;
            _param.end_time.Month = month;
            _param.end_time.Day = day;
            _param.end_time.Hour = hour;
            _param.end_time.Minute = minute;
            _param.end_time.Second = second;

            _param.channel = new_rsp ? new_detail_rsp.channel : detail_rsp.channel;
            channel_ = _param.channel;
            _param.record_type = new_rsp ? new_detail_rsp.rsp.Type : detail_rsp.rsp.Type;
            _param.stream_type = new_rsp ? new_detail_rsp.stream_type : detail_rsp.stream_type;
            memcpy(_param.file_name, file.c_str(), std::min(file.length(), _countof(_param.file_name) - 1));
            _param.file_count = 1;
            _param.file_total_size = total_size;
            _param.max_single_file_size = value["max single file size"].asInt();
            _param.status_callback = RSNetDownloadRecordStatusCallbackExFun;
            _param.user_param = this;
            download_handle_ = RSNetStartDownloadByTime(conn_, &_param);
        }

        base_running_ = download_handle_ ? true : false;
        sdk_wrapper_log("[%s ch:%d] call <download_record start> result:%s\n", ip_or_id_.c_str(), channel_, download_handle_ ? "success" : "fail");
        return download_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !download_handle_)
            return rs_success;

        base_running_ = false;

        if (download_handle_) {
            RSNetStopDownloadFile(&download_handle_);
            download_handle_ = NULL;
        }
        download_cb_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[%s ch:%d] call <download_record stop> result:success\n", ip_or_id_.c_str(), channel_);
        return rs_success;
    }

private:
    RSNetConnection     conn_;
    RSNetDownloadFile   download_handle_;
    download_callback   download_cb_;
    void*               user_param_;
    uint32_t            channel_;
};
