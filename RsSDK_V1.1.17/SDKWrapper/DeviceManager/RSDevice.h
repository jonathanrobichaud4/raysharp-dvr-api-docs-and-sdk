#pragma once

#include "../JsonCpp/json.h"
#include "../Include/RSSDKWrapper.h"
#include "./forward_define.h"
#include "./log.h"
#include "./connection.h"
#include "./search_modify.h"
#include "./ptz_control.h"
#include "./capture_from_device.h"
#include "./convert_file_type.h"

#ifdef _MSC_VER
#if defined(EXPORT_SDKWRAPPER_AS_DLL)
#ifdef _WIN64
#  pragma comment(lib, "../windows/Bin64/RSNet.lib")
#  pragma comment(lib, "../windows/Bin64/RSPlay.lib")
#else
#  pragma comment(lib, "../windows/Bin/RSNet.lib")
#  pragma comment(lib, "../windows/Bin/RSPlay.lib")
#endif
#else
#ifdef _WIN64
#  pragma comment(lib, "../Bin64/RSNet.lib")
#  pragma comment(lib, "../Bin64/RSPlay.lib")
#else
#  pragma comment(lib, "../Bin/RSNet.lib")
#  pragma comment(lib, "../Bin/RSPlay.lib")
#endif
#endif
#endif

class CParamRemoteTest;
class CRSDevice
{
public:
    CRSDevice(void);
    ~CRSDevice(void);

    /********************************************************************************/
    //warning : never use these function in your app
    RSNetConnection GetConnection()  { return conn_.get_connection();       }
    LoginRsp*       GetLoginRsp()    { return conn_.get_login_rsp_struct(); }
    int             GetDeviceType()  { return conn_.get_device_type();      }
    int             GetChannelNum()  { return conn_.get_channel_num();      }
    int             GetAnalogChNum() { return conn_.get_analog_num();       }
    void            SetServerInfo(RSNetConnection conn) { conn_.set_connection(conn); }
    void            SendMsgToWeb(unsigned int, unsigned int, const Json::Value&, void *);
    void            SendMsgToWeb(unsigned int, unsigned int, void *);
    /********************************************************************************/

    static device_id add_device(CRSDevice* device);
    static CRSDevice* get_device(device_id dev);

    static rs_error_code search_device(const char* param, search_device_callback callback, void* user_param);
    static rs_error_code modify_device(const char* param);

    rs_error_code login(const device_login_param* param);
    rs_error_code logout();

    std::string get_login_rsp();
    int get_device_playback_capability();
    void get_channel_status_rpt(int channel, RemoteChnStatusRpt& channel_status_rpt);

    session_id start_preview(const preview_param* param);
    rs_error_code stop_preview(session_id sess);

    session_id search_record_by_month(const char* param, search_record_month_callback month_cb, void* user_param);
    session_id search_record_by_day(const char* param, search_record_day_callback day_cb, void* user_param);
    rs_error_code stop_search_record(session_id sess);

    session_id start_download_by_file(const char* param, download_callback download_cb, void* user_param);
    session_id start_download_by_time(const char* param, download_callback download_cb, void* user_param);
    rs_error_code stop_download(session_id sess);

    static session_id start_local_playback(const local_playback_param* param);
    static rs_error_code stop_local_playback(session_id sess);
    static session_id start_sync_playback(const sync_playback_param* param);

    session_id start_remote_playback(const remote_playback_param* param);
    session_id start_sync_remote_playback(const char* param, HWND* window, playback_callback playback_cb, void* user_param);
    rs_error_code stop_playback(session_id sess);
    
    rs_error_code ptz_operation(const char* param);

    rs_error_code capture_picture_from_device(const char* param);

    session_id start_talk(const char* param, talk_callback talk_cb, void* user_param);
    rs_error_code stop_talk(session_id sess);

    static session_id start_convert_file(const char* param, convert_callback convert_cb, void* user_param);
    static rs_error_code stop_convert_file(session_id sess);

    rs_error_code remote_test(unsigned int msg_type, const char* param, remote_test_callback remote_test_cb, void* user_param);

    session_id start_playback_thumbnails(const char* param, playback_thumbnails_callback cb, void* user_param);
    rs_error_code stop_playback_thumbnails(session_id sess);

    static session_id start_local_playback_thumbnails(const char* param, local_playback_thumbnails_callback cb, void* user_param);
    static rs_error_code input_local_playback_time(session_id sess, ULONGLONG millisecond);
    static rs_error_code stop_local_playback_thumbnails(session_id sess);

    session_id start_human_face_alarm_report(const human_face_alarm_report_param* param);
    rs_error_code stop_human_face_alarm_report(session_id sess);

    session_id start_human_face_param(const human_face_param* param);
    rs_error_code stop_human_face_param(session_id sess);

    void reset_connection();

    rs_error_code send_simple_command(const simple_command_param* param);

    bool is_session_exist(session_id sess);

    session_id start_upgrade(const char* param, upgrade_callback cb, void* user_param);
    rs_error_code stop_upgrade(session_id sess);

    void remote_self_from_device_list(base_instance* sess);

    static rs_error_code sync_playback_add_session(session_id sync_sess, session_id sess);
    static rs_error_code sync_playback_del_session(session_id sync_sess, session_id sess);

    session_id start_async_query_json(const async_query_json_param* param);
    session_id start_async_set_json(const async_set_json_param* param);
    rs_error_code stop_async_json(session_id sess);
    
    bool support_reverse_playback() {
        return conn_.support_reverse_playback();
    }

public:
    std::string                             m_strPassword;

private:
    rs_error_code stop_session(session_id sess);

    connection                              conn_;
    ptz_control                             ptz_control_;
    capture_from_device                     capture_from_device_;
	
    rs_mutex                                mutex_;
    std::map<session_id, base_instance*>    base_instances_;
    typedef std::map<session_id, base_instance*>::iterator base_itor;

    CParamRemoteTest*                       remote_test_;
    remote_test_callback                    remote_test_cb_;
    void*                                   remote_test_user_param_;
};
