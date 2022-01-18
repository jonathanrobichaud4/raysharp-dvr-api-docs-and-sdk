#include "RSDevice.h"
#include "preview.h"
#include "search_record.h"
#include "download_record.h"
#include "local_playback.h"
#include "remote_playback.h"
#include "talk.h"
#include "convert_file_type.h"
#include "remote_playback_thumbnails.h"
#include "local_playback_thumbnails.h"
#include "human_face.h"
#include "upgrade.h"
#include "sync_playback.h"
#include "../Remote/ParamRemoteTest.h"

long s_global_index = 10;
//1 is reserved for android search lan device user param

class init_lib {
public:
    init_lib() {
        RSNetInit();
        RSPlayInitPlayLib(APP_SDK_WRAPPER, 0, 0);
    }

    ~init_lib() {
        RSPlayDeinitPlayLib();
        RSNetRelease();
    }
};
static init_lib s_global_init_lib;

CRSDevice::CRSDevice(void) : remote_test_(new CParamRemoteTest), remote_test_cb_(NULL), remote_test_user_param_(NULL)
{
    remote_test_->m_pDevice = this;
}

CRSDevice::~CRSDevice(void)
{
    logout();
    SAFE_DELETE(remote_test_);
}

void CRSDevice::SendMsgToWeb(unsigned int msg_type, unsigned int event_type, const Json::Value& value, void *) {
    if (event_type == MsgRemoteTestEvent && remote_test_cb_) {
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        remote_test_cb_(msg_type, param.c_str(), remote_test_user_param_);
    }
}

void CRSDevice::SendMsgToWeb(unsigned int msg_type, unsigned int event_type, void *) {
    if (event_type == MsgRemoteTestEvent && remote_test_cb_) {
        remote_test_cb_(msg_type, NULL, remote_test_user_param_);
    }
}

device_id CRSDevice::add_device(CRSDevice* device) {
    return device;
}

CRSDevice* CRSDevice::get_device(device_id dev) {
    return (CRSDevice*)dev;
}

rs_error_code CRSDevice::search_device(const char* param, search_device_callback callback, void* user_param) {
    return search_modify::search_device(param, callback, user_param);
}

rs_error_code CRSDevice::modify_device(const char* param) {
    return search_modify::modify_device(param);
}

rs_error_code CRSDevice::stop_session(session_id sess) {
    if (sess) {
        base_instance* instance = NULL;
        {
            rs_scoped_lock lock(mutex_);
            base_itor itor = base_instances_.find(sess);
            if (itor != base_instances_.end()) {
                instance = itor->second;
                base_instances_.erase(itor);
            }
        }
        if (instance) {
            if (instance->is_sync_play()) {
                instance->stop_callback();
            } else {
                instance->stop();
                delete instance;
            }
        }
    }
    return rs_success;
}

rs_error_code CRSDevice::login(const device_login_param* param) {
    logout();
    rs_error_code err = conn_.login(param);
    m_strPassword = conn_.get_password();
    return err;
}

rs_error_code CRSDevice::logout() {
    rs_scoped_lock lock(mutex_);
    base_itor itor = base_instances_.begin();
    while (itor != base_instances_.end()) {
        base_instance* instance = itor->second;
        if (instance) {
            sdk_wrapper_log("[%s] call <logout_clear_instance> name:%s\n", conn_.get_ip_or_id().c_str(), instance->get_name().c_str());
            instance->stop();
            delete instance;
        }
        ++itor;
    }
    base_instances_.clear();

    m_strPassword.clear();
    return conn_.logout();
}

std::string CRSDevice::get_login_rsp() {
    return conn_.get_login_rsp();
}

int CRSDevice::get_device_playback_capability() {
    return conn_.get_device_playback_capability();
}

void CRSDevice::get_channel_status_rpt(int channel, RemoteChnStatusRpt& channel_status_rpt) {
    return conn_.get_channel_status_rpt(channel, channel_status_rpt);
}

session_id CRSDevice::start_preview(const preview_param* param) {
    preview* instance = new preview(this, conn_);
    if (instance && (instance->start(param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_preview(session_id sess) {
    return stop_session(sess);
}

session_id CRSDevice::search_record_by_month(const char* param, search_record_month_callback month_cb, void* user_param) {
    search_record* instance = new search_record(this, conn_);
    if (instance && (instance->start(param, month_cb, NULL, user_param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

session_id CRSDevice::search_record_by_day(const char* param, search_record_day_callback day_cb, void* user_param) {
    search_record* instance = new search_record(this, conn_);
    if (instance && (instance->start(param, NULL, day_cb, user_param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_search_record(session_id sess) {
    return stop_session(sess);
}

session_id CRSDevice::start_download_by_file(const char* param, download_callback download_cb, void* user_param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return NULL;

    //0: not found   1: RecordDetailRspInfo   2: NewRecordDetailRspInfo
    int find = 0;
    int index = value["index"].asInt();
    RecordDetailRspInfo detail_rsp = {0};
    NewRecordDetailRspInfo new_detail_rsp = {0};

    {
        rs_scoped_lock lock(mutex_);
        base_itor itor = base_instances_.begin();
        while (itor != base_instances_.end()) {
            base_instance* instance = itor->second;
            if (instance && instance->get_record_detail_rsp(index, detail_rsp)) {
                find = 1;
                break;
            }
            ++itor;
        }

        if (!find) {
            itor = base_instances_.begin();
            while (itor != base_instances_.end()) {
                base_instance* instance = itor->second;
                if (instance && instance->get_new_record_detail_rsp(index, new_detail_rsp)) {
                    find = 2;
                    break;
                }
                ++itor;
            }
        }
    }

    if (!find)
        return NULL;

    download_record* instance = new download_record(this, conn_);
    if (instance && (instance->start(find == 1 ? (void*)&detail_rsp : (void*)&new_detail_rsp, param, download_cb, user_param, true, find == 1 ? false : true, 0) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

session_id CRSDevice::start_download_by_time(const char* param, download_callback download_cb, void* user_param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return NULL;

    int64_t total_size = 0;
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
    
    //0: not found   1: RecordDetailRspInfo   2: NewRecordDetailRspInfo
    int find = 0;
    int index = value["index"].asInt();
    RecordDetailRspInfo detail_rsp = {0};
    NewRecordDetailRspInfo new_detail_rsp = {0};

    {
        rs_scoped_lock lock(mutex_);
        base_itor itor = base_instances_.begin();
        while (itor != base_instances_.end()) {
            base_instance* instance = itor->second;
            if (instance && instance->get_record_detail_rsp(index, detail_rsp)) {
                total_size = instance->get_record_total_size(begin_time, end_time);
                find = 1;
                break;
            }
            ++itor;
        }

        if (!find) {
            itor = base_instances_.begin();
            while (itor != base_instances_.end()) {
                base_instance* instance = itor->second;
                if (instance && instance->get_new_record_detail_rsp(index, new_detail_rsp)) {
                    total_size = instance->get_new_record_total_size(begin_time, end_time);
                    find = 2;
                    break;
                }
                ++itor;
            }
        }
    }

    if (!find)
        return NULL;

    download_record* instance = new download_record(this, conn_);
    if (instance && (instance->start(find == 1 ? (void*)&detail_rsp : (void*)&new_detail_rsp, param, download_cb, user_param, false, find == 1 ? false : true, total_size) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_download(session_id sess) {
    return stop_session(sess);
}

session_id CRSDevice::start_local_playback(const local_playback_param* param) {
    local_playback* instance = new local_playback(NULL);
    if (instance && (instance->start(param) == rs_success)) {
        return instance;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_local_playback(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance && !instance->is_sync_play()) {
        rs_error_code code = instance->stop();
        delete instance;
        return code;
    }
    return rs_session_not_found;
}

session_id CRSDevice::start_sync_playback(const sync_playback_param* param) {
    sync_playback* instance = new sync_playback(NULL);
    if (instance && (instance->start(param) == rs_success)) {
        return instance;
    }
    SAFE_DELETE(instance);
    return NULL;
}

session_id CRSDevice::start_remote_playback(const remote_playback_param* param) {
    remote_playback* instance = new remote_playback(this, conn_);
    if (instance && (instance->start(param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

session_id CRSDevice::start_sync_remote_playback(const char* param, HWND* window, playback_callback playback_cb, void* user_param) {
    return NULL;
}

rs_error_code CRSDevice::stop_playback(session_id sess) {
    return stop_session(sess);
}

rs_error_code CRSDevice::ptz_operation(const char* param) {
    return ptz_control_(param, conn_);
}

rs_error_code CRSDevice::capture_picture_from_device(const char* param) {
    return capture_from_device_(param, conn_);
}

session_id CRSDevice::start_talk(const char* param, talk_callback talk_cb, void* user_param) {
    talk* instance = new talk(this, conn_);
    if (instance && (instance->start(param, talk_cb, user_param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_talk(session_id sess) {
    return stop_session(sess);
}

session_id CRSDevice::start_convert_file(const char* param, convert_callback convert_cb, void* user_param) {
	convert_file_type* instance = new convert_file_type(NULL);
	if(instance && (instance->start(param, convert_cb, user_param) == rs_success)){
		return instance;
	}
	SAFE_DELETE(instance);
	return NULL;
}

rs_error_code CRSDevice::stop_convert_file(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance) {
        rs_error_code code = instance->stop();
        delete instance;
        return code;
    }
    return rs_session_not_found;
}

rs_error_code CRSDevice::remote_test(unsigned int msg_type, const char* param, remote_test_callback remote_test_cb, void* user_param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err)){
        return rs_parse_json_error;
    }

    remote_test_cb_ = remote_test_cb;
    remote_test_user_param_ = user_param;

    return (remote_test_->ParamRemoteTest(msg_type, value) > 0) ? rs_success : rs_fail;
}

session_id CRSDevice::start_playback_thumbnails(const char* param, playback_thumbnails_callback cb, void* user_param) {
    remote_playback_thumbnails* instance = new remote_playback_thumbnails(this, conn_);
    if (instance && (instance->start(param, cb, user_param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_playback_thumbnails(session_id sess) {
    return stop_session(sess);
}

session_id CRSDevice::start_local_playback_thumbnails(const char* param, local_playback_thumbnails_callback cb, void* user_param) {
    local_playback_thumbnails* instance = new local_playback_thumbnails(NULL);
    if(instance && (instance->start(param, cb, user_param) == rs_success)){
        return instance;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::input_local_playback_time(session_id sess, ULONGLONG millisecond) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->input_local_playback_time(millisecond);
    return rs_session_not_found;
}

rs_error_code CRSDevice::stop_local_playback_thumbnails(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance) {
        rs_error_code code = instance->stop();
        delete instance;
        return code;
    }
    return rs_session_not_found;
}

session_id CRSDevice::start_human_face_alarm_report(const human_face_alarm_report_param* param) {
    {
        rs_scoped_lock lock(mutex_);
        base_itor itor = base_instances_.begin();
        while (itor != base_instances_.end()) {
            base_instance* instance = itor->second;
            if (instance && instance->get_instance_type() == HUMAN_FACE_ALARM_REPORT_INSTANCE_TYPE)
                return NULL;
            ++itor;
        }
    }

    human_face_alarm_report* instance = new human_face_alarm_report(this, conn_);
    if (instance && (instance->start(param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_human_face_alarm_report(session_id sess) {
    return stop_session(sess);
}

session_id CRSDevice::start_human_face_param(const human_face_param* param) {
    {
        rs_scoped_lock lock(mutex_);
        base_itor itor = base_instances_.begin();
        while (itor != base_instances_.end()) {
            base_instance* instance = itor->second;
            if (instance && instance->get_instance_type() == HUMAN_FACE_REMOTE_PARAM_INSTANCE_TYPE)
                return NULL;
            ++itor;
        }
    }

    human_face_remote_param* instance = new human_face_remote_param(this, conn_);
    if (instance && (instance->start(param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_human_face_param(session_id sess) {
    return stop_session(sess);
}

void CRSDevice::reset_connection() {
    return conn_.reset_connection();
}

rs_error_code CRSDevice::send_simple_command(const simple_command_param* param) {
    return conn_.send_simple_command(param);
}

bool CRSDevice::is_session_exist(session_id sess) {
    rs_scoped_lock lock(mutex_);
    return (base_instances_.find(sess) != base_instances_.end()) ? true : false;
}

session_id CRSDevice::start_upgrade(const char* param, upgrade_callback cb, void* user_param) {
    upgrade* instance = new upgrade(this, conn_);
    if (instance && (instance->start(param, cb, user_param) == rs_success)) {
        session_id sess = instance;
        {
            rs_scoped_lock lock(mutex_);
            base_instances_.insert(std::make_pair(sess, instance));
        }
        return sess;
    }
    SAFE_DELETE(instance);
    return NULL;
}

rs_error_code CRSDevice::stop_upgrade(session_id sess) {
    return stop_session(sess);
}

void CRSDevice::remote_self_from_device_list(base_instance* sess) {
    rs_scoped_lock lock(mutex_);
    base_itor itor = base_instances_.find(sess);
    if (itor != base_instances_.end())
        base_instances_.erase(itor);
}

rs_error_code CRSDevice::sync_playback_add_session(session_id sync_sess, session_id sess) {
    base_instance* sync_instace = (base_instance*)sync_sess;
    base_instance* instance = (base_instance*)sess;
    if (sync_instace && instance)
        return sync_instace->add_session(instance);
    return rs_fail;
}

rs_error_code CRSDevice::sync_playback_del_session(session_id sync_sess, session_id sess) {
    base_instance* sync_instace = (base_instance*)sync_sess;
    base_instance* instance = (base_instance*)sess;
    if (sync_instace && instance)
        return sync_instace->del_session(instance);
    return rs_fail;
}

session_id CRSDevice::start_async_query_json(const async_query_json_param* param) {
    return conn_.start_async_query_json(param);
}

session_id CRSDevice::start_async_set_json(const async_set_json_param* param) {
    return conn_.start_async_set_json(param);
}

rs_error_code CRSDevice::stop_async_json(session_id sess) {
    return conn_.stop_async_json(sess);
}
