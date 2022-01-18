#pragma once

class human_face_alarm_report : public base_instance {
public:
    human_face_alarm_report(void* parent, connection& conn)
        : base_instance(parent, HUMAN_FACE_ALARM_REPORT_INSTANCE_TYPE, "human_face_alarm_report", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , alarm_handle_(NULL)
        , data_callback_(NULL)
        , status_callback_(NULL)
        , user_param_(NULL)
    {

    }

    ~human_face_alarm_report() {
        stop();
    }

    static void RSNET_CALL RSNetAlarmRequestInfoDataCallbackFun(const char* data, int size, const RSReportHeadOut* report_head, void* user_param) {
        human_face_alarm_report* _this = static_cast<human_face_alarm_report*>(user_param);
        if (_this)
            _this->RSNetAlarmRequestInfoDataCallbackFun(data, size, report_head);
    }

    static void RSNET_CALL RSNetAlarmRequestStatusCallbackFun(WPARAM wparam/*uint32_t msg*/, LPARAM lparam/*void* user_param*/) {
        human_face_alarm_report* _this = (human_face_alarm_report*)(lparam);
        if (_this)
            _this->RSNetAlarmRequestStatusCallbackFun((uint64_t)wparam);
    }

    void RSNetAlarmRequestInfoDataCallbackFun(const char* data, int size, const RSReportHeadOut* report_head) {
        if (base_running_ && data_callback_) {
            Json::Value value;
            value["report type"] = report_head->ReportType;
            value["version"] = report_head->Version;
            Json::StreamWriterBuilder writer;
            std::string result = Json::writeString(writer, value);

            data_callback_(data, size, result.c_str(), user_param_);
        }
    }

    void RSNetAlarmRequestStatusCallbackFun(uint64_t msg) {
        if (base_running_ && status_callback_) {
            std::string err;

            if (!err.empty()) {
                Json::Value value;
                value["status"] = err;
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);

                status_callback_(result.c_str(), user_param_);
            }
        }
    }

    rs_error_code start(const human_face_alarm_report_param* param) {
        stop();

        data_callback_ = param->data_callback;
        status_callback_ = param->status_callback;
        user_param_ = param->user_param;

        AlarmRequestInfo info = {0};
        info.data_callback = RSNetAlarmRequestInfoDataCallbackFun;
        info.status_callback = RSNetAlarmRequestStatusCallbackFun;
        info.user_param = this;
        alarm_handle_ = RSNetStartAlarmRequestInfo(conn_, &info);

        base_running_ = alarm_handle_ ? true : false;
        sdk_wrapper_log("[%s] call <human_face_alarm_report start> result:%s\n", ip_or_id_.c_str(), alarm_handle_ ? "success" : "fail");
        return alarm_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !alarm_handle_)
            return rs_success;

        base_running_ = false;

        if (alarm_handle_) {
            RSNetStopAlarmRequestInfo(&alarm_handle_);
            alarm_handle_ = NULL;
        }
        data_callback_ = NULL;
        status_callback_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[%s] call <human_face_alarm_report stop> result:success\n", ip_or_id_.c_str());
        return rs_success;
    }

private:
    RSNetConnection                         conn_;
    RSAlarmRequestHandle                    alarm_handle_;
    human_face_alarm_report_data_callback   data_callback_;
    human_face_alarm_report_status_callback status_callback_;
    void*                                   user_param_;
};

class human_face_remote_param : public base_instance {
public:
    human_face_remote_param(void* parent, connection& conn)
        : base_instance(parent, HUMAN_FACE_REMOTE_PARAM_INSTANCE_TYPE, "human_face_remote_param", conn.get_ip_or_id().c_str())
        , conn_(conn.get_connection())
        , alarm_handle_(NULL)
        , data_callback_(NULL)
        , status_callback_(NULL)
        , user_param_(NULL)
    {

    }

    ~human_face_remote_param() {
        stop();
    }

    static void RSNET_CALL RSNetAlarmParamInfoDataCallbackFun(const char* param, int size, void* user_param) {
        human_face_remote_param* _this = static_cast<human_face_remote_param*>(user_param);
        if (_this)
            _this->RSNetAlarmParamInfoDataCallbackFun(param, size);
    }

    static void RSNET_CALL RSNetAlarmRequestStatusCallbackFun(WPARAM wparam/*uint32_t msg*/, LPARAM lparam/*void* user_param*/) {
        human_face_remote_param* _this = (human_face_remote_param*)(lparam);
        if (_this)
            _this->RSNetAlarmRequestStatusCallbackFun((uint64_t)wparam);
    }

    void RSNetAlarmParamInfoDataCallbackFun(const char* param, int size) {
        if (base_running_ && data_callback_) {
            data_callback_(param, size, user_param_);
        }
    }

    void RSNetAlarmRequestStatusCallbackFun(uint64_t msg) {
        if (base_running_ && status_callback_) {
            std::string err;

            switch (msg)
            {
            case RSNetMsgConnectSuccess:
                err = "success";
            	break;
            case RSNetMsgConnectFail:
                err = "fail";
                break;
            default:
                break;
            }
            if (!err.empty()) {
                Json::Value value;
                value["status"] = err;
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);

                status_callback_(result.c_str(), user_param_);
            }
        }
    }

    rs_error_code start(const human_face_param* param) {
        stop();

        data_callback_ = param->data_callback;
        status_callback_ = param->status_callback;
        user_param_ = param->user_param;

        AlarmParamInfo info = {0};
        info.data_callback = RSNetAlarmParamInfoDataCallbackFun;
        info.status_callback = RSNetAlarmRequestStatusCallbackFun;
        info.user_param = this;

        alarm_handle_ = RSNetStartAlarmParamInfo(conn_, &info);

        base_running_ = alarm_handle_ ? true : false;
        sdk_wrapper_log("[%s] call <human_face_remote_param start> result:%s\n", ip_or_id_.c_str(), alarm_handle_ ? "success" : "fail");
        return alarm_handle_ ? rs_success : rs_fail;
    }

    rs_error_code stop() {
        if (!base_running_ && !alarm_handle_)
            return rs_success;

        base_running_ = false;

        if (alarm_handle_) {
            RSNetStopAlarmParamInfo(&alarm_handle_);
            alarm_handle_ = NULL;
        }
        data_callback_ = NULL;
        status_callback_ = NULL;
        user_param_ = NULL;

        sdk_wrapper_log("[%s] call <human_face_remote_param stop> result:success\n", ip_or_id_.c_str());
        return rs_success;
    }

    rs_error_code send_human_face_param(const char* param, int param_size) {
        if (base_running_ && alarm_handle_ && param && param_size) {
            AlarmParamJson info = {0};
            info.param = param;
            info.param_size = param_size;
            RSNetSendAlarmParamJson(alarm_handle_, &info);
        }
        return rs_success;
    }

private:
    RSNetConnection                         conn_;
    RSAlarmParamHandle                      alarm_handle_;
    human_face_param_data_callback          data_callback_;
    human_face_param_status_callback        status_callback_;
    void*                                   user_param_;
};
