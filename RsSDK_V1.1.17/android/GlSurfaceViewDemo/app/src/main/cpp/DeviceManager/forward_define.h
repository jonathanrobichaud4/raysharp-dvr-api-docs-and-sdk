#pragma once

#undef min
#undef max
#include <string>
#include <time.h>
#include "../Include/RSSDKWrapper.h"
#include "../JsonCpp/json.h"

#if defined(_MSC_VER)
#elif defined(__ANDROID__)
#  include <android/log.h>
   static const char* kTAG = "SDKWrapper";
#  define TRACE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))
#else
#  define TRACE printf
#endif

#define SESSION_DEFAULT_VALUE    NULL // -1                 or NULL

/********************************************************************************/
//warning : never use these function in your app
enum {
    DEV_DVR = 0,
    DEV_MVR = 1,
    DEV_INTEL = 2,
    DEV_NVR = 3,
    DEV_IPC = 4,
    DEV_HDVR = 6
};

enum tag_UI_TYPE_E
{
    RS_UI_1_0 = 0,      //UI 1.0
    RS_UI_2_0,          //UI 2.0
    RS_UI_3_0,          //UI 3.0
    RS_UI_4_0,          //UI 4.0
    RS_UI_5_0 = 50
};

enum {
    MsgNoType = 0,
    MsgGetAndSetParamEvent = 5,
    MsgRemoteUpgradeEvent = 6,
    MsgRemoteTestEvent = 7,
    SubMsgSetParameter = 35,
};

#define SAFE_DELETE(p)  { if(p != NULL) { delete (p);     (p) = NULL; } }   //Delete object by New create 
#define SAFE_DELETEA(p) { if(p != NULL) { delete[] (p);   (p) = NULL; } }   //Delete Arrary

#ifndef FIELD_OFFSET
#  define FIELD_OFFSET(type,field)     ((long)(long)&(((type *)0)->field))
#  define RTL_FIELD_SIZE(type,field)   (sizeof(((type *)0)->field))
#  define UlongToPtr(ul)               ((void *)(unsigned long)((unsigned long)ul))
#  define PtrToUlong(ul)               ((long)(long)(ul))
#endif

#ifndef UNALIGNED
#  define  UNALIGNED
#endif
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
    template <typename _CountofType, unsigned long _SizeOfArray>
    char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) sizeof(*__countof_helper(_Array))
}
#endif
#endif

#ifdef _WIN32
static std::string UnicodeToUTF8(const std::wstring& str) {
    char*     pElementText;
    int    iTextLen;
    // wide char to multi char
    iTextLen = WideCharToMultiByte( CP_UTF8,
        0,
        str.c_str(),
        -1,
        NULL,
        0,
        NULL,
        NULL );
    pElementText = new char[iTextLen + 1];
    memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
    ::WideCharToMultiByte( CP_UTF8,
        0,
        str.c_str(),
        -1,
        pElementText,
        iTextLen,
        NULL,
        NULL );
    std::string strText;
    strText = pElementText;
    delete[] pElementText;
    return strText;
}

static std::wstring UTF8ToUnicode(const std::string& str) {
    int  len = 0;
    len = str.length();
    int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
        0,
        str.c_str(),
        -1,
        NULL,
        0 );  
    wchar_t *  pUnicode;  
    pUnicode = new  wchar_t[unicodeLen+1];  
    memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
    ::MultiByteToWideChar( CP_UTF8,
        0,
        str.c_str(),
        -1,
        (LPWSTR)pUnicode,
        unicodeLen );  
    std::wstring  rt;  
    rt = ( wchar_t* )pUnicode;
    delete[]  pUnicode;
    return  rt;  
}

static std::string UnicodeToAnsi(const std::wstring& str) {
    char*     pElementText;
    int    iTextLen;
    // wide char to multi char
    iTextLen = WideCharToMultiByte( CP_ACP,
        0,
        str.c_str(),
        -1,
        NULL,
        0,
        NULL,
        NULL );
    pElementText = new char[iTextLen + 1];
    memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
    ::WideCharToMultiByte( CP_ACP,
        0,
        str.c_str(),
        -1,
        pElementText,
        iTextLen,
        NULL,
        NULL );
    std::string strText;
    strText = pElementText;
    delete[] pElementText;
    return strText;
}

static std::string UTF8ToAnsi(const std::string& str) {
    int    nLen = ::MultiByteToWideChar (CP_UTF8, 0, str.c_str(), -1, NULL, 0) ;
    WCHAR   * pWstr = new WCHAR[nLen+1] ;
    ZeroMemory (pWstr, sizeof(WCHAR) * (nLen+1)) ;
    ::MultiByteToWideChar (CP_UTF8, 0, str.c_str(), -1, pWstr, nLen) ;
    std::string     strAnsi = UnicodeToAnsi(pWstr);
    delete[] pWstr ;
    return strAnsi ;
}

#endif
/********************************************************************************/

static int inet_pton4_(const char *src, unsigned char *dst) {
    static const char digits[] = "0123456789";
    int saw_digit, octets, ch;
    unsigned char tmp[4], *tp;

    saw_digit = 0;
    octets = 0;
    *(tp = tmp) = 0;
    while ((ch = *src++) != '\0') {
        const char *pch;

        if ((pch = strchr(digits, ch)) != NULL) {
            unsigned int value = static_cast<int>(*tp) * 10 + (int)(pch - digits);

            if (value > 255)
                return (0);
            *tp = value;
            if (! saw_digit) {
                if (++octets > 4)
                    return (0);
                saw_digit = 1;
            }
        } else if (ch == '.' && saw_digit) {
            if (octets == 4)
                return (0);
            *++tp = 0;
            saw_digit = 0;
        } else
            return (0);
    }
    if (octets < 4)
        return (0);
    memcpy(dst, tmp, 4);
    return (1);
}

static rs_error_code get_time_from_string(const std::string& time, DateTime& date_time) {
    size_t pos_one = time.find('-');
    if (pos_one == std::string::npos)
        return rs_fail;
    size_t pos_two = time.find('-', pos_one + 1);
    if (pos_two == std::string::npos)
        return rs_fail;
    size_t pos_three = time.find(' ', pos_two + 1);
    if (pos_three == std::string::npos)
        return rs_fail;

    date_time.Year = atoi(time.substr(0, pos_one).c_str());
    date_time.Month = atoi(time.substr(pos_one + 1, pos_two - pos_one - 1).c_str());
    date_time.Day = atoi(time.substr(pos_two + 1, pos_three - pos_two - 1).c_str());

    pos_one = time.find(':', pos_three + 1);
    if (pos_one == std::string::npos)
        return rs_fail;
    pos_two = time.find(':', pos_one + 1);
    if (pos_two == std::string::npos)
        return rs_fail;

    date_time.Hour = atoi(time.substr(pos_three, pos_one).c_str());
    date_time.Minute = atoi(time.substr(pos_one + 1, pos_two - pos_one - 1).c_str());
    date_time.Second = atoi(time.substr(pos_two + 1).c_str());
    return rs_success;
}

extern long s_global_index;
static session_id generate_index() {
#ifdef _MSC_VER
    return (session_id)(InterlockedIncrement(&s_global_index));
#else
    return (session_id)__sync_add_and_fetch(&s_global_index, 1);
#endif
}

static int generate_int_index() {
#ifdef _MSC_VER
    return (int)(InterlockedIncrement(&s_global_index));
#else
    return (int)__sync_add_and_fetch(&s_global_index, 1);
#endif
}

#ifdef _MSC_VER
class rs_mutex {
public:
    rs_mutex()      { InitializeCriticalSectionAndSpinCount(&mCriSec, 1500);   }
    ~rs_mutex()     { DeleteCriticalSection(&mCriSec);                         }
    void lock()     { EnterCriticalSection(&mCriSec);                          }
    bool try_lock() { return TryEnterCriticalSection(&mCriSec) ? true : false; }
    void unlock()   { LeaveCriticalSection(&mCriSec);                          }
private:
    CRITICAL_SECTION mCriSec;
};
#else
#include <pthread.h>
class rs_mutex {
public:
    rs_mutex()                  { pthread_mutex_init(&mCriSec,NULL);                       }
    ~rs_mutex()                 { pthread_mutex_destroy(&mCriSec);                         }
    void lock()                 { pthread_mutex_lock(&mCriSec);                            }
    bool try_lock()             { return !pthread_mutex_trylock(&mCriSec) ? true : false;  }
    void unlock()               { pthread_mutex_unlock(&mCriSec);                          }
    pthread_mutex_t* GetMutex() { return &mCriSec;                                         }
private:
    pthread_mutex_t mCriSec;
};

static inline long InterlockedIncrement(long* value) {
    return __sync_add_and_fetch(value, 1);
}
#endif

template <class T>
class rs_lock_guard {
public:
    typedef T mutex_type;
    explicit rs_lock_guard(mutex_type &aMutex) : mMutex(aMutex) { mMutex.lock(); }
    ~rs_lock_guard() { mMutex.unlock(); }

private:
    mutex_type& mMutex;
};
typedef rs_lock_guard<rs_mutex> rs_scoped_lock;

typedef struct
{
    WORD Width;
    WORD Height;
    BYTE FrameRate;
    BYTE System;
    WORD WaterMark : 1;//2013-03-04 10:37:18
    WORD bRefFrame : 1;
    WORD IFrameNoOffset : 11;
    WORD bFishEye : 1;
    WORD Reserved : 2;
}RSVideoHead;

typedef struct
{
    UINT SampleRate;
    BYTE Channels;
    BYTE BitsPerSample;
    WORD PackLen;
}RSAudioHead;

typedef struct
{
    BYTE ReportType;
    BYTE Version;
    BYTE Reserved[2];
} RSReportHead;

typedef struct
{
    UINT FrameTag;

    BYTE FrameType;
    BYTE EncodeType;
    BYTE Channel : 7;
    BYTE Encrypted : 1;
    BYTE bHide : 1;
    BYTE Reserved : 7;

    UINT FrameNo;
    UINT FrameSize;
    ULONGLONG Time; //(microseconds) Time/1000,000 = the number of seconds after January 1, 1970 UTC
    ULONGLONG Pts;

    union
    {
        RSVideoHead VideoHead;
        RSAudioHead AudioHead;
        RSReportHead ReportHead;
    };
}RSFrameHead;

typedef struct __RS_DEC_FRAME_S__
{
    union {
        unsigned char*  pY;                   //Y plane base address of the picture
        char            reserve_y[8];
    };
    union {
        unsigned char*  pU;                   //U plane base address of the picture
        char            reserve_u[8];
    };
    union {
        unsigned char*  pV;                   //V plane base address of the picture
        char            reserve_v[8];
    };
    union {
        unsigned char*  ffmpeg_av_frame;      //Not used
        char            reserve_ffmpeg[8];
    };
    unsigned int        uWidth;               //The width of output picture in pixel
    unsigned int        uHeight;              //The height of output picture in pixel
    unsigned int        uYStride;             //Luma plane stride in pixel
    unsigned int        uUVStride;            //Chroma plane stride in pixel
    char                forbidden_move;
    char                is_rgba32;
    unsigned char       channel;
    char                reserve[5];
} RS_DEC_FRAME_S;

typedef struct __RS_PICTURE_S__
{
    RSFrameHead    frame_head;
    RS_DEC_FRAME_S dec_frame_head;
    unsigned char  picture_data[8];
}RS_PICTURE_S;

typedef struct _RecordDetailRspInfo_ {
    uint32_t        channel;
    int             stream_type;
    RecordDetailRsp rsp;
}RecordDetailRspInfo;

typedef struct _NewRecordDetailRspInfo_ {
    uint32_t           channel;
    int                stream_type;
    NewRecordDetailRsp rsp;
}NewRecordDetailRspInfo;

typedef enum {
    UNKNOWN_INSTANCE_TYPE = -1,
    CONVERT_FILE_TYPE_INSTANCE_TYPE,
    DOWNLOAD_RECORD_INSTANCE_TYPE,
    HUMAN_FACE_ALARM_REPORT_INSTANCE_TYPE,
    HUMAN_FACE_REMOTE_PARAM_INSTANCE_TYPE,
    LOCAL_PLAYBACK_INSTANCE_TYPE,
    LOCAL_PLAYBACK_THUMBNAILS_INSTANCE_TYPE,
    PREVIEW_INSTANCE_TYPE,
    REMOTE_PLAYBACK_INSTANCE_TYPE,
    REMOTE_PLAYBACK_THUMBNAILS_INSTANCE_TYPE,
    SEARCH_RECORD_INSTANCE_TYPE,
    TALK_INSTANCE_TYPE,
    UPGRADE_INSTANCE_TYPE,
    SYNC_PLAYBACK_INSTANCE_TYPE
}INSTANCE_TYPE;

class base_instance {
public:
    explicit base_instance(void* parent, INSTANCE_TYPE type, const char* name, const char* ip_or_id = NULL, int port = 0) 
    : parent_(parent)
    , base_running_(false)
    , base_play_handle_(NULL) 
    , ip_or_id_(ip_or_id ? ip_or_id : "")
    , port_(port)
    , type_(type)
    , name_(name ? name : "")
    {
    }
    virtual ~base_instance() {}

    device_id     get_device() { return parent_; }
    INSTANCE_TYPE get_instance_type() { return type_; }
    std::string   get_name() { return name_; }
    RSPlayHandle  get_play_handle() { return base_play_handle_; }

    virtual rs_error_code stop() = 0;
    virtual RS_PICTURE_S* get_decoded_frame() { return NULL; }
    virtual rs_error_code switch_stream_type(const char* param) { return rs_fail; }
    virtual rs_error_code seek_by_time(const char* param) { return rs_fail; }
    virtual rs_error_code set_play_mode(const char* param) { return rs_fail; }
    virtual bool get_record_detail_rsp(int index, RecordDetailRspInfo& rsp) { return false; }
    virtual int64_t get_record_total_size(const DateTime& begin_time, const DateTime& end_time) { return 0; }
    virtual int64_t get_new_record_total_size(const DateTime& begin_time, const DateTime& end_time) { return 0; }
    virtual bool get_new_record_detail_rsp(int index, NewRecordDetailRspInfo& rsp) { return false; }
    virtual rs_error_code seek_by_key_frame_index(int key_frame_index) { return rs_fail; }
    virtual rs_error_code input_local_playback_time(ULONGLONG millisecond) { return rs_fail; }
    virtual rs_error_code send_human_face_param(const char* param, int param_size) { return rs_fail; }
    virtual rs_error_code start_net() { return rs_fail; }
    virtual rs_error_code stop_net()  { return rs_fail; }
    virtual bool is_sync_play() { return false; }
    virtual void remote_self_from_device_list() {}
    virtual rs_error_code add_session(base_instance* instance) { return rs_fail; }
    virtual rs_error_code del_session(base_instance* instance) { return rs_fail; }
    virtual rs_error_code stop_callback() { return rs_fail; }

    rs_error_code open_sound() { 
        if (base_play_handle_ && RSPlayOpenSound(base_play_handle_) == 0)
            return rs_success;
        return rs_fail; 
    }
    rs_error_code close_sound() { 
        if (base_play_handle_ && RSPlayCloseSound(base_play_handle_) == 0)
            return rs_success;
        return rs_fail; 
    }
    rs_error_code set_volume(int volume) { 
        if (base_play_handle_ && RSPlaySetPlayVolume_s(base_play_handle_, volume) == 0)
            return rs_success;
        return rs_fail; 
    }
    int get_volume() {
        if(base_play_handle_)
        {
            int ret = RSPlayGetPlayVolume_s(base_play_handle_);
            return ret;
        }
        return rs_fail;
    }
    rs_error_code set_mute_on() { 
        if (base_play_handle_ && RSPlaySetMute_s(base_play_handle_, TRUE) == 0)
            return rs_success;
        return rs_fail; 
    }
    rs_error_code set_mute_off() { 
        if (base_play_handle_ && RSPlaySetMute_s(base_play_handle_, FALSE) == 0)
            return rs_success;
        return rs_fail; 
    }

    rs_error_code start_record(const char* param) {
        if (base_play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            std::string file_name = value["file name"].asString();
            std::string picture_name = value["picture name"].asString();
            RSFILE_INFO_EX info = {0};
            info.file_name = file_name.c_str();
            info.picture_name = picture_name.c_str();
            info.max_single_file_size = value["max single file size"].asInt();
            if (RSPlayStartlocalrecordFileEx(base_play_handle_, &info) == 0)
                return rs_success;
        }
        return rs_fail;
    }

    rs_error_code stop_record() {
        if (base_play_handle_) {
            ULONGLONG begin_time = 0;
            ULONGLONG end_time = 0;
            if (RSPlayStoplocalrecord(base_play_handle_, &begin_time, &end_time) == 0)
                return rs_success;
        }
        return rs_fail;
    }

    rs_error_code stop_record(record_ex_param* param) {
        if (base_play_handle_) {
            if (param) {
                if (RSPlayStoplocalrecord(base_play_handle_, &(param->begin_time), &(param->end_time)) == 0)
                    return rs_success;
            } else {
                ULONGLONG begin_time = 0;
                ULONGLONG end_time = 0;
                if (RSPlayStoplocalrecord(base_play_handle_, &begin_time, &end_time) == 0)
                    return rs_success;
            }
        }
        return rs_fail;
    }

    rs_error_code capture_picture(const char* param) {
        if (base_play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            std::string picture_name = value["picture name"].asString();
            if (RSPlayCapturePicture(base_play_handle_, const_cast<char*>(picture_name.c_str())) == 0)
                return rs_success;
        }
        return rs_fail;
    }

	rs_error_code capture_picture_to_buf(capture_picture_buf_param* param) {
		if (base_play_handle_) {
			std::string err = "";
			if(RSPlayCapturePictureToBuf(base_play_handle_, param->capture_buf_cb, param->capture_buf_user_param, param->type) == 0)
				return rs_success;
		}
		return rs_fail;
	}



    rs_error_code get_current_time(char* buf, int length) {
        ULONGLONG current_time = 0;
        if (base_play_handle_ && (current_time = RSPlayGetCurPlayedTime(base_play_handle_))) {
            memset(buf, 0, length);
            current_time += 500000;
            time_t now = (time_t)(current_time / 1000000);
            struct tm gmtTime;
#ifdef _MSC_VER
            gmtime_s(&gmtTime, &now);
            sprintf_s(buf, length, "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                                                                    gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
#else
            gmtime_r(&now, &gmtTime);
            sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                                                          gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
#endif
            return rs_success;
        }
        return rs_fail;
    }

    ULONGLONG get_current_time_millisecond() {
        ULONGLONG current_time = 0;
        if (base_play_handle_ && (current_time = RSPlayGetCurPlayedTime(base_play_handle_))) {
            current_time += 500;
            current_time /= 1000;
        }
        return current_time;
    }

    rs_error_code set_video_proportion(const char* param) {
        if (base_play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            int proportion = 0;
            std::string video_proportion = value["proportion"].asString();
            if (video_proportion == "full window") {
                proportion = RP_ORIGINAL;
            } else if (video_proportion == "picture proportion") {
                proportion = RP_PICTURE;
            } else if (video_proportion == "4:3 proportion") {
                proportion = RP_4_3;
            } else if (video_proportion == "16:9 proportion") {
                proportion = RP_16_9;
            }
            RSPlayRenderActualProportion(base_play_handle_, proportion);
            return rs_success;
        }
        return rs_fail;
    }

    rs_error_code set_fishsye_mode(FISHEYE_COMB_TYPE_E type) {
        if (base_play_handle_) {
            RSPlayFishSetMode(base_play_handle_, type);
            return rs_success;
        }
        return rs_fail;
    }
    
    rs_error_code fisheye_mouse_control(const char* param) {
        if (base_play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            FISH_MOUSE_E flag = FISH_MOUSE_BUTT;
            std::string mouse_flag = value["mouse flag"].asString();
            if (mouse_flag == "mouse move") {
                flag = FISH_MOUSE_MOVE;
            } else if (mouse_flag == "mouse wheel") {
                flag = FISH_MOUSE_WHEEL;
            } else if (mouse_flag == "mouse lbutton down") {
                flag = FISH_MOUSE_LBUTTONDOWN;
            } else if (mouse_flag == "mouse lbutton up") {
                flag = FISH_MOUSE_LBUTTONUP;
            } else if (mouse_flag == "mouse lbutton dbclick") {
                flag = FISH_MOUSE_LBUTTONDBLCLK;
            } else if (mouse_flag == "mouse rbutton dbclick") {
                flag = FISH_MOUSE_RBUTTONDBLCLK;
            }
            if (flag == FISH_MOUSE_BUTT)
                return rs_parse_json_error;

            FISH_CONTROL_REQ_S req = {0};
            req.eFlag = FISH_EYE_MOUSE_E;
            req.stMouse.eFlag = flag;
            req.stMouse.x = value["mouse x"].asFloat();
            req.stMouse.y = value["mouse y"].asFloat();
            req.stMouse.value = value["mouse delta"].asFloat();
            RSPlayFishControl(base_play_handle_, &req);

            return rs_success;
        }
        return rs_fail;
    }

    rs_error_code fisheye_ptz_control(const char* param) {
        if (base_play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            int speed = value["speed"].asInt();
            std::string operation = value["operation"].asString();
            std::string flag = value["flag"].asString();

            FISH_PTZ_E _operation = FISH_PTZ_BUTT;
            if (operation == "left")
                _operation = FISH_PTZ_LEFT;
            else if (operation == "up left")
                _operation = FISH_PTZ_LEFTUP;
            else if (operation == "up")
                _operation = FISH_PTZ_UP;
            else if (operation == "up right")
                _operation = FISH_PTZ_RIGHTUP;
            else if (operation == "right")
                _operation = FISH_PTZ_RIGHT;
            else if (operation == "down right")
                _operation = FISH_PTZ_RIGHTDOWN;
            else if (operation == "down")
                _operation = FISH_PTZ_DOWN;
            else if (operation == "down left")
                _operation = FISH_PTZ_LEFTDOWN;
            else if (operation == "zoom out")
                _operation = FISH_PTZ_ZOOMDEC;
            else if (operation == "zoom in")
                _operation = FISH_PTZ_ZOOMINC;
            else if (operation == "auto scan")
                _operation = FISH_PTZ_CURISE;

            bool _flag = false;
            if (flag == "start")
                _flag = true;
            else if (flag == "stop")
                _flag = false;

            if (_operation == FISH_PTZ_BUTT)
                return rs_parse_json_error;

            FISH_CONTROL_REQ_S req = {0};
            req.eFlag = FISH_EYE_PTZ_E;
            req.stPtz.eFlag = _operation;
            req.stPtz.speed = (float)speed/10;
            if(_operation == FISH_PTZ_ZOOMDEC)
                req.stPtz.k = -1;
            else if(_operation == FISH_PTZ_ZOOMINC)
                req.stPtz.k = 1;
            req.stPtz.bEnable = _flag;
            RSPlayFishControl(base_play_handle_, &req);

            return rs_success;
        }
        return rs_fail;
    }

    bool window_in_zoom_status() {
        if (base_play_handle_)
            return RSPlayWindowInZoomStatus(base_play_handle_);
        return false;
    }
    
    rs_error_code set_color(const rs_color* color_value) {
        if (base_play_handle_)
            RSPlaySetColor(base_play_handle_, color_value);
        return rs_success;
    }

    rs_error_code draw_line(const rs_rect* line_value, int line_count) {
        if (base_play_handle_)
            RSPlayDrawLine(base_play_handle_, line_value, line_count);
        return rs_success;
    }

    rs_error_code draw_rect(const rs_rect* rect_value, int rect_count) {
        if (base_play_handle_)
            RSPlayDrawRect(base_play_handle_, rect_value, rect_count);
        return rs_success;
    }

    rs_error_code draw_solid_rect(const rs_rect* rect_value, int rect_count, float transparency) {
        if (base_play_handle_)
            RSPlayDrawSolidRect(base_play_handle_, rect_value, rect_count, transparency);
        return rs_success;
    }

    rs_error_code draw_hollow_circle(const rs_rect* rect_value, int rect_count) {
        if (base_play_handle_)
            RSPlayDrawHollowCircle(base_play_handle_, rect_value, rect_count);
        return rs_success;
    }

    rs_error_code draw_text(const char* text_value, const rs_rect* rect_value) {
        if (base_play_handle_)
            RSPlayDrawText(base_play_handle_, text_value, rect_value);
        return rs_success;
    }

    session_id upload_picture_from_memory(const char* data, int size) {
        if (base_play_handle_) {
            int result = RSPlayUploadPictureFromMemory(base_play_handle_, data, size);
            if (result > 0)
                return (session_id)result;
        }
        return SESSION_DEFAULT_VALUE;
    }

    rs_error_code delete_picture(session_id picture_sess_id) {
        long sess = (long)picture_sess_id;
        if (base_play_handle_)
            RSPlayDeletePicture(base_play_handle_, sess);
        return rs_success;
    }

    rs_error_code draw_picture(session_id picture_sess_id, const rs_rect* rect_value, float transparency) {
        long sess = (long)picture_sess_id;
        if (base_play_handle_)
            RSPlayDrawPicture(base_play_handle_, sess, rect_value, transparency);
        return rs_success;
    }

    rs_error_code get_frame_width_and_height(int* width, int* height) {
        if (base_play_handle_)
            RSPlayGetPlayPicSize(base_play_handle_, width, height);
        return rs_success;
    }

    rs_error_code adjust_render_frame_rect(const rs_rect* rect_value) {
        if (base_play_handle_) {
            int width = 0;
            int height = 0;
            RSPlayGetPlayPicSize(base_play_handle_, &width, &height);
            if (width && height) {
#ifdef _MSC_VER
                RSPlayAdjustViewArea(base_play_handle_, 
                    (int)(width*rect_value->x1), 
                    (int)(width*(1.0f-rect_value->x2)), 
                    (int)(height*rect_value->y1), 
                    (int)(height*(1.0f-rect_value->y2)));
#else
                RSPlayAdjustViewArea(base_play_handle_, 
                    (int)(width*rect_value->x1), 
                    (int)(width*rect_value->x2), 
                    (int)(height*rect_value->y1), 
                    (int)(height*rect_value->y2));
#endif
            }
        }
        return rs_success;
    }

    rs_error_code manual_switch_record(const char* param) {
        if (base_play_handle_) {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;

            std::string file_name    = value["file name"].asString();
            std::string picture_name = value["picture name"].asString();
            int max_single_file_size = value["max single file size"].asInt();

            if (RSPlaySwitchRecordFile(base_play_handle_, file_name.c_str(), 0, 0) == 0)
                return rs_success;
        }
        return rs_fail;
    }

protected:
    void*         parent_;
    volatile bool base_running_;
    rs_mutex      base_mutex_;
    RSPlayHandle  base_play_handle_;
    std::string   ip_or_id_;
    int           port_;
    INSTANCE_TYPE type_;
    std::string   name_;
};

typedef struct _SEARCH_DEVICE_INFO_ {
    search_device_callback callback;
    void*                  user_param;
    char                   reserve[64];
}SEARCH_DEVICE_INFO;
