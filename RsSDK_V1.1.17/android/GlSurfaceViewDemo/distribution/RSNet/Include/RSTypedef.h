#ifndef __RS_TYPEDEF_H__
#define __RS_TYPEDEF_H__

#ifdef _MSC_VER
#  include <Windows.h>
#else
#  include <netinet/in.h>
#endif

typedef    char               S8;
typedef    unsigned char      U8;
typedef    short              S16;
typedef    unsigned short     U16;
typedef    int                S32;
typedef    unsigned int       U32;
typedef    unsigned long long U64;

#ifndef _MSC_VER
#    ifdef __linux__
#      define BOOL                   bool
#    else
#      include <objc/objc.h>           //for BOOL
#    endif

#    define  MAX_PATH                260
#    define  WINAPI
#    define  CALLBACK
#    define  FALSE                   0
#    define  TRUE                    1
#    define  S_OK                   (int)0
#    define  S_FALSE                (int)1
#    define  FILE_BEGIN              SEEK_SET
#    define  FILE_CURRENT            SEEK_CUR
#    define  FILE_END                SEEK_END
#    define  ATLTRACE                printf
#    define  E_OUTOFMEMORY           (int)(-1)

     typedef char                    CHAR;
     typedef unsigned char           UCHAR;
     typedef unsigned char           BYTE;
     typedef const char*             PCSTR;
     typedef unsigned short          WORD;
     typedef unsigned short          USHORT;
     typedef unsigned int            DWORD;
     typedef unsigned int            UINT;
     typedef int                     HRESULT;
     typedef long                    LONG;
     typedef unsigned int            ULONG;
     typedef unsigned long long      ULONGLONG;

     typedef void*                   WPARAM;
     typedef void*                   LPARAM;
     typedef void*                   HDC;
     typedef void*                   HWND;
     typedef void*                   LPVOID;

     typedef struct {
         int left;
         int top;
         int right;
         int bottom;
     }RECT,*LPRECT;

     static inline void SetRectEmpty(LPRECT rect) {
         rect->left = 0;
         rect->top = 0;
         rect->right = 0;
         rect->bottom = 0;
     }

     static inline bool IsRectEmpty(LPRECT rect) {
         return ((rect->right - rect->left) == 0) || ((rect->bottom - rect->top) == 0);
     }

     static inline void SetRect(LPRECT rect, int left, int top, int right, int bottom) {
         rect->left = left;
         rect->top = top;
         rect->right = right;
         rect->bottom = bottom;
     }

     static inline void CopyRect(LPRECT dst, LPRECT src) {
         dst->left = src->left;
         dst->top = src->top;
         dst->right = src->right;
         dst->bottom = src->bottom;
     }

     static inline bool EqualRect(LPRECT lprc1, LPRECT lprc2) {
         if (lprc1->left == lprc2->left && \
             lprc1->top  == lprc2->top  && \
             lprc1->right == lprc2->right && \
             lprc1->bottom == lprc2->bottom)
             return true;
         return false;
     }
#endif // end of _MSC_VER

#define MsgPTZStartPriZoneSet		70          //开始隐私遮挡设置
#define MsgPTZStopPriZoneSet		71          //结束隐私遮挡设置

#define Open_Screen_PTZ             97
#define Close_Screen_PTZ            98

#define MsgParamDevLog					 160608 //2016.06.08 自己写的
#define MsgParamScheduleIPC				 160825 //2016.08.25 兼容IPC录像计划
#define MsgParamExportIPC                161121//2016.11.21 ipc参数导入导出
#define MsgParamTour					 171109//2017.11.09 ZIP preset和tour参数
#define MsgShowResolution				 171218//2017.12.18 预览显示分辨率
#define MsgShowFrameRate			     180704//2018.07.04 预览显示帧率

#define MsgSensorStatusReport_PIR       20161103	//我自己定义，自己使用的
#define MsgSensorStatusReport_Smoke     20161104	//我自己定义，自己使用的
#define MsgNewRecordDetail		        20170622	//我自己定义，自己使用的
#define MsgP2PTunnelInfo                60000	    //我自己定义，自己使用的

/*****新回放搜索*******/
#define NormalRec  0x1
#define MotionRec  0x2
#define IORec      0x4
#define PEALineRec 0x8
#define AVDRec     0x10
#define OSCRec     0x20
#define PEAAreaRec 0x40
#define HDRec      0x80 
#define FDRec      0x100 
#define PCCRec     0x200 
#define MotionAndIORec 0x400
#define PIRRec         0x400
#define NetbreakRec    0x800      //2018.08.23,与板端数据同步
#define SoundRec       0x1000      //2018.08.23,与板端数据同步

#define PIDRecord     0x200
#define LCDRecord     0x400
#define SODRecord     0x800

typedef enum 
{
    PLAY_TYPE_UNKNOWN = -1,
    PLAY_TYPE_NORMAL = 0,//all I frame and P frame
    PLAY_TYPE_I_CONTINUOUS = 1,//Continuous I frame
    PLAY_TYPE_I_SKIP_ONE = 2,//Skip one I frame
    PLAY_TYPE_I_SKIP_TWO = 3,//Skip two I frame
    PLAY_TYPE_I_SKIP_THREE = 4,//Skip three I frame
    PLAY_TYPE_I_SKIP_FOUR = 5,//Skip four I frame
    PLAY_TYPE_I_SKIP_FIVE = 6,//Skip five I frame
    PLAY_TYPE_I_SKIP_SIX = 7,//Skip six I frame
    PLAY_TYPE_I_SKIP_SEVEN = 8,//Skip seven I frame
    PLAY_TYPE_I_SKIP_EIGHT = 9,//Skip eight I frame
    PLAY_REVERSE_I_CONTINUOUS = 20,
    PLAY_REVERSE_I_SKIP_ONE = 21,
    PLAY_REVERSE_I_SKIP_TWO = 22,
    PLAY_REVERSE_I_SKIP_THREE = 23,
    PLAY_REVERSE_I_SKIP_FOUR = 24,
    PLAY_REVERSE_I_SKIP_FIVE = 25,
    PLAY_REVERSE_I_SKIP_SIX = 26,
}PlaySpeedCtrl;
typedef enum _IPChnStatus_{
	IPCS_BOTTOM   = -1,
	IPCS_NETWRONG = 0,/*无法连接到IPC*/
	IPCS_UNAUTHER = 1,/*用户认证失败*/
	IPCS_ONLINE   = 2,/*表示登录并流开启成功*/
	IPCS_CONNECT  = 3,/*正在连接*/
	IPCS_BANDLIMIT= 4,/*码流受限制而被断开*/
    IPCS_VIDEOLOSS = 5,
    IPCS_SLEEP     = 6
}IPChnStatus_e;

typedef enum _ChnStatus_{
	CHN_BOTTOM = -1,/*Did not add*/
	CHN_NETWRONG = 0,/*无法连接到IPC*/
	CHN_UNAUTHER = 1,/*用户认证失败*/
	CHN_ONLINE = 2,/*连接成功，自动开启预览*/
	CHN_CONNECT = 3,/*正在连接*/
	CHN_BANDLIMIT = 4,/*码流受限制而被断开*/
	CHN_VIDEOLOSS = 5,
	CHN_SLEEP = 6/*在线但正处于休眠状态，需手动开启预览*/
}ChnStatus_e;

typedef enum
{
    ABILITY_TYPE_MAINSTREAM,
    ABILITY_TYPE_SUBSTREAM,
    ABILITY_TYPE_SNAPSTREAM,
    ABILITY_TYPE_OSD,
    ABILITY_TYPE_COLOR,
    ABILITY_TYPE_TIME,
    ABILITY_TYPE_COVER,
    ABILITY_TYPE_MOTIONSET,
    ABILITY_TYPE_MOTIONAREA,
    ABILITY_TYPE_IO,/*前端设备是否支持IO报警*/
    ABILITY_TYPE_PTZ,
    ABILITY_TYPE_IMAGE,
    ABILITY_TYPE_TIIPC,
    ABILITY_TYPE_NOSUPMAINSTREAMPARAM,
    ABILITY_TYPE_NOSUPSUBSTREAMPARAM,
    ABILITY_TYPE_NOSUPMOBILESTREAMPARAM,
    ABILITY_TYPE_INTELLIGENT,
    ABILITY_TYPE_IMAGE_IRIS,
    ABILITY_TYPE_H265,
    ABILITY_TYPE_FISH_EYE,
    ABILITY_TYPE_BINOCULARS,//双目
    ABILITY_TYPE_OSDTRANSPARENCY,//OSD透明度设置
    ABILITY_TYPE_CORRIDOR_ANGLEROTATION,//是否支持走廊模式和角度旋转
    ABILITY_TYPE_PIR,
	ABILITY_TYPE_SMART_MOTIION,
	ABILITY_TYPE_SUPPROT_WIREFREE,//wireless//wireless channel preview can not AutoReconnect
	ABILITY_TYPE_WHITE_LIGHT,
	ABILITY_TYPE_LOUD_SPEAKER,
	ABILITY_TYPE_TALK_HALF, //ABILITY_TYPE_AFOCUS
	ABILITY_TYPE_TALK_FULL,
	ABILITY_TYPE_EVENTSTREAM,
	ABILITY_TYPE_SOUNDDETECTION = 31, //音量报警
}Net_ABILITY_TYPE_E;

typedef enum
{
	ABILITY_TYPE_ODDETECTION ,//遮挡报警
	ABILITY_TYPE_DL,
	ABILITY_TYPE_IVALINES,
	ABILITY_TYPE_HKPTZ,
	ABILITY_TYPE_NEWPTZ,
	ABILITY_TYPE_INTELLIGENT_PLUS_PIR,
	ABILITY_TYPE_MOTION_PIR,
	ABILITY_TYPE_IR_LED,
	ABILITY_TYPE_IR_SCHEDULE,
	ABILITY_TYPE_IR_TRIGGER,
	ABILITY_TYPE_CH256_IPC,
	ABILITY_TYPE_IFRAME_INTERVAL,
	ABILITY_TYPE_AFOCUS,
    ABILITY_TYPE_IMAGE_DAY_AND_NIGHT,
    ABILITY_TYPE_Support_VBR_CBR,
    ABILITY_TYPE_Show_DLFD_PAGE,
    ABILITY_TYPE_SUPPORT_WATHERMARK,
    ABILITY_TYPE_DISSUPPORT_OSD_CUSTOM,
    ABILITY_TYPE_SHOW_DLPD_PAGE,
    ABILITY_TYPE_DISSUPPORT_IRCUT_VIDEOAUTO,
}Net_ABILITYEX_TYPE_E;

/* new device abilities */
typedef enum
{
    PROTO_TYPE_RS = 0,
    PROTO_TYPE_RSSZ,   /*深圳TI方案私有协议*/
    PROTO_TYPE_SAMSUNG,/*三星*/
    PROTO_TYPE_ZXNH  ,  /*中西霓虹*/
    PROTO_TYPE_ONVIF = 4,  /*onvif */
    PROTO_TYPE_URMET,	/*urmet协议IPC*/
    PROTO_TYPE_AMTK,
    PROTO_TYPE_SHANY,
	PROTO_TYPE_ZHUOWEI,
    PROTO_TYPE_MINGJING,
	PROTO_TYPE_FSAN,
	PROTO_TYPE_QIHAN,
	PROTO_TYPE_GRANDMEDIA,/*DENAVO客户(对接GRANDMEDIA私有协议)*/
	PROTO_TYPE_SONIX,	  /*松翰协议*/
	PROTO_TYPE_YCX,		  /*GW客户(研创兴私有协议)*/
	PROTO_TYPE_HANHUI = 15, /*翰辉私有协议*/
	PROTO_TYPE_GUOWEI,	   /*GIGAMEDIA客户(国为对接协议)*/
	PROTO_TYPE_HIKVISION,  /*海康私有协议*/
	PROTO_TYPE_ZHINUO,	 /*智诺对接协议(未对完)*/
	PROTO_TYPE_JINGYANG,
    PROTO_TYPE_NULL, // 需小于32
    PROTO_TYPE_CUSTOM1 = 32,
    PROTO_TYPE_CUSTOM2,
    PROTO_TYPE_CUSTOM3,
    PROTO_TYPE_CUSTOM4,
    PROTO_TYPE_CUSTOM5,
    PROTO_TYPE_CUSTOM6,
    PROTO_TYPE_CUSTOM7,
    PROTO_TYPE_CUSTOM8,
    PROTO_TYPE_CUSTOM9,
    PROTO_TYPE_CUSTOM10,
    PROTO_TYPE_CUSTOM11,
    PROTO_TYPE_CUSTOM12,
    PROTO_TYPE_CUSTOM13,
    PROTO_TYPE_CUSTOM14,
    PROTO_TYPE_CUSTOM15,
    PROTO_TYPE_CUSTOM16
} PROTO_TYPE_E;

typedef enum
{
    DEV_RESERVE,
    DEV_TYPE_PRIVATE_H264,
    DEV_TYPE_PRIVATE_H265,
    DEV_TYPE_ONVIF_H264,
    DEV_TYPE_ONVIF_H265
}IPC_DEV_TYPE_E;

enum {
    BAIDU_ANDROID = 0,              /* push baidu android */
    BAIDU_IOS,
    QQ_XG_ANDROID,
    QQ_XG_IOS
};

typedef enum _KEYBACKUP_TYPE_E
{
    KEYTYPE_MAINBOARDNAME = 0,
    KEYTYPE_PASSWORD,
    KEYTYPE_SERIALNUMBER,
    KEYTYPE_PROUUCTTYPE,
    KEYTYPE_DEVICETYPE,
    KEYTYPE_DEVICENAME,
    KEYTYPE_CUSTOMTYPE,
    KEYTYPE_FUNCTIONCODE,
    KEYTYPE_SUPPORTFOURHDDDISK,
    KEYTYPE_LANGUAGECONFIG,
    KEYTYPE_LANGUAGE,
    KEYTYPE_SERIALNUMBEREX,
    KEYTYPE_PRODUCTCODE,
    KEYTYPE_VIDEOFORMAT,
	KEYTYPE_ANGLEROTATION,
	KEYTYPE_ALARMOUTPUTNUM,
	KEYTYPE_ALARMINPUTNUM,
	KEYTYPE_AUDIONUM,
	KEYTYPE_POEPOWER,
	KEYTYPE_HDDGROUP,
	KEYTYPE_ESATAENABLE,
    KEYTYPE_MAX
}KEYBACKUP_TYPE_E;

typedef enum _LANGUAG_E
{
    LANGUAGE_CHINESE		 = 0,	 //简体中文
    LANGUAGE_CHINESECOMPLEX  = 1,	 //繁体中文
    LANGUAGE_CZECH			 = 2,	 //捷克语
    LANGUAGE_DANISH 		 = 3,	 //丹麦语
    LANGUAGE_ENGLISH		 = 4,	 //英文
    LANGUAGE_FINNISH		 = 5,	 //芬兰语
    LANGUAGE_FRENCH 		 = 6,	 //法语
    LANGUAGE_GERMAN 		 = 7,	 //德语
    LANGUAGE_GREEK			 = 8,	 //希腊语
    LANGUAGE_HEBREW 		 = 9,	 //希伯来语
    LANGUAGE_HUNGARIAN		 = 10,	 //匈牙利语
    LANGUAGE_INTALIAN		 = 11,	 //意大利语
    LANGUAGE_JAPANESE		 = 12,	 //日语
    LANGUAGE_POLISH 		 = 13,	 //波兰语
    LANGUAGE_PORTUGUESE 	 = 14,	 //葡萄牙语
    LANGUAGE_RUSSIAN		 = 15,	 //俄语
    LANGUAGE_SPANISH		 = 16,	 //西班牙语
    LANGUAGE_THAI			 = 17,	 //泰文
    LANGUAGE_SLOVENIA		 = 18,	 //斯洛文尼亚语
    LANGUAGE_ROMANIAN		 = 19,	 //罗马尼亚语
    LANGUAGE_BULGARIAN		 = 20,	 //保加利亚文
    LANGUAGE_ARABIC          = 21,   //阿拉伯语
    LANGUAGE_HINDI           = 22,   //印度语
    LANGUAGE_VIETNAM         = 23,   //越南语
    LANGUAGE_HOLLAND         = 24,   //荷兰语
    LANGUAGE_TURKEY          = 25,   //土耳其语
    LANGUAGE_PERSION         = 26,   //波斯语
    LANGUAGE_SVENSKA         = 27,   //瑞典语
    LANGUAGE_KOREAN 		 = 28,  //韩语
    LANGUAGE_UKRAINIAN       = 29,  //乌克兰语
    LANGUAGE_SLOVAK          = 30,  //斯洛伐克语
    LANGUAGE_MAX,
}LANGUAG_E;

typedef enum _LANGUAGE_TYPE_E
{
    LANGUAGE_SAMSUNG_MLANG_EIGHT=0,
    LANGUAGE_SAMSUNG_KOREAN,
    LANGUAGE_SAMSUNG_MLANG_FIVE,
    LANGUAGE_SAMSUNG_KOREAN_ENGLISH,
    LANGUAGE_SAMSUNG_ENG_FRE_SPA,
	LANGUAGE_SAMSUNG_MLANG_NINE,
	LANGUAGE_SAMSUNG_MLANG_KOREAN_AMERICAN_SIX,
	LANGUAGE_SAMSUNG_MLANG_FOUR,
    LANGUAGE_SAMSUNG_MAX
}LANGUAGE_TYPE_E;

typedef enum _ANGLEROTATION_TYPE_E
{
	ANGLEROTATION_0 = 0,
	ANGLEROTATION_90,
	ANGLEROTATION_180,
	ANGLEROTATION_270,
}ANGLEROTATION_TYPE_E;

typedef enum _POESET_TYPE_E
{
	POECLOSE = 0,
	POEOPEN,
}POESET_TYPE_E;

typedef struct
{
    WORD Year; //2011
    BYTE Month; //1 ~ 12
    BYTE Day; //1 ~ 31
    BYTE Hour; //0 ~ 23
    BYTE Minute; //0 ~ 59
    BYTE Second; //0 ~ 59
    BYTE Reserved;
}DateTime;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
    char RecState;               /* 录像状态 */
    char CurRecType;             /* 当前录像类型 */
    char MDSchedule;             /* 移动报警计划*/
	char MDRecEnable;           /* 是否开启MD触发录像功能 */
}MotionAlarmRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
    char RecState;               /* 录像状态 */
    char CurRecType;             /* 当前录像类型 */
    char AlarmSchedule;          /* IO报警计划*/
	char Reserved[1];
}IOAlarmRpt;

/* 远程升级IPC当前状态 */
typedef struct
{
    int structsize; //结构体大小
    int channelNo;  //通道号
    char status;    //IPC状态. 对应RS_UGIpcStatus_e
    char progress;  //升级进度
    char reserved[6];
}RS_UGIpcRsp_t;

/* 远程升级IPC状态类型 */
typedef enum
{
    Stat_Err = -2,   //检验等错误
    Stat_Failed = -1,//升级失败
    Stat_Inprogress, //升级进行中
    Stat_Success     //升级成功
}RS_UGIpcStatus_e;

/* 远程升级尚云固件返回类型(kguard DVR) */
typedef enum _upgrade_fw_e_
{
    FW_DONOT_NEED       = -1,//不需要升级
    FW_DISCONNECTED     = 0, //连接失败
    FW_DOWNLOADING      = 1, //正在下载
    FW_MD5_NOT_MATCHED  = 2, //下载完成但MD5不匹配,停止升级
    FW_DEV_REBOOT       = 3  //下载完成且MD5已匹配,重启设备
}RS_UGFireware_E;

//////////////////////////***log***////////////////////////////
typedef enum _log_type_e_
{
	LOG_SYSTEM = 0,
	LOG_CONFIG,
	LOG_ALARM,
	LOG_USER,
	LOG_RECORD,
	LOG_STORAGE,
	LOG_NETWORK,

	LOG_MAINTYPE_MAX,
	LOG_ALL = 0xff 	/*所有日志，日志主类型最多255种*/
}LogMainType_E;

typedef enum _system_log_type_e_
{
	SYS_STARTUP = 0,
	SYS_SHUTDOWN,
	SYS_REBOOT,
	SYS_MAINTAIN,
	SYS_UPGRADE,
	SYS_TIME_MODIFY,
	SYS_NTP,
	SYS_DEFAULT,

	SYS_MAX,
	SYS_ALL = 0xff
}SysLogType_E;

typedef enum _network_log_type_e_
{
	NET_DOWN = 0,	/*网络断开*/
	NET_UP, 		/*网络连接*/
	NET_ERROR,		/*网络异常*/
	NET_CHANGEMODE, /*联网方式改变*/

	NET_MAX,
	NET_ALL =  0xff
}NetLogType_E;

typedef enum _config_log_type_e_ /*各个参数设置页面*/
{
	CFG_LIVE = 0,
	CFG_VIDEO_SETUP,
	CFG_PRIVACY_ZONE,
	CFG_REC_PARAM,
	CFG_REC_SCHEDULE,
	CFG_MAINSTREAM,
	CFG_NET_SETTING ,
	CFG_SUBSTREAM,
	CFG_EMAIL,
	CFG_EMAIL_SCHEDULE,
	CFG_DDNS,
	CFG_PLATFORM,
	CFG_COLOR,
	CFG_MOTION,
	CFG_IOALARM,
	CFG_STORAGE,
	CFG_PTZ,
	CFG_SYSTEM,
	CFG_USER,
	CFG_INFO,
	CFG_MAINTAIN,
	CFG_ABNORMAL,
	CFG_DST,
	CFG_NTP,
	CFG_IPC_ADD,		
	CFG_IPC_DELETE,
	CFG_IPC_MODIFY,
	CFG_IMAGE_CONTROL,
	CFG_MOBILESTREAM,
	CFG_FTP_UPLOAD,
	CFG_FTP_UPGRADE,
	CFG_RTSP,
	CFG_IPFILTER,
	CFG_LENS_COVER,
	CFG_LOG,
	CFG_DATE_TIME,
	CFG_UPGRADE,
	CFG_DEFAULT,
	CFG_ROI,
	CFG_AUDIO,
    CFG_CAPTRUE_MODIFY,/*抓图页面参数修改*/
    CFG_POS_ADD,/*POS机添加*/
    CFG_POS_DELETE,/*POS机删除*/
    CFG_POS_MODIFY,/*POS机修改*/
    CFG_PIRALARM,/*PIR参数页面修改*/
	CFG_ALARM_LINKAGE_PTZ,/*PTZ linkage参数页面修改*/
    CFG_SD_MODIFY,/*声音告警参数页面修改*/
    CFG_OD_MODIFY,/*镜头遮挡参数页面修改*/
	CFG_ZEROCHN,/*零通道页面修改*/
	CFG_MAX,
	CFG_ALL = 0xff
}ConfigLogType_E;

typedef enum _alarm_log_type_e_
{
	ALARM_MOTION_START = 0,
	ALARM_MOTION_STOP,
	ALARM_IO_START,
	ALARM_IO_STOP,
	ALARM_VIDEO_LOSS,
	ALARM_OD_START,
	ALARM_OD_STOP,
	ALARM_PID_START,
	ALARM_PID_STOP,
	ALARM_LCD_START,
	ALARM_LCD_STOP,
	ALARM_SOD_START,
	ALARM_SOD_STOP,
	ALARM_PD_START,
	ALARM_PD_STOP,
	ALARM_FD_START,
	ALARM_FD_STOP,
	ALARM_CC_START,
	ALARM_CC_STOP,
	ALARM_PIR_START,
	ALARM_PIR_STOP,
	ALARM_SHELL_BROKEN, /*外壳被拆*/
    ALARM_SD_START,
    ALARM_SD_STOP,

	ALM_MAX,
	ALARM_ALL = 0xff
}AlarmLogType_E;

typedef enum _user_log_type_e_
{
	USER_LOGIN = 0,
	USER_LOGOUT,
	USER_ADD,
	USER_DEL,
    USER_MODIFY,
    USER_LOCK,
    USER_UNLOCK,

	USER_MAX,
	USER_ALL = 0xff
}UserLogType_E;

typedef enum _rec_log_type_e_
{
	REC_START_SCHEDULE = 0,
	REC_START_MANUAL,
	REC_STOP,
	REC_SEARCH,
	REC_PLAYBACK,
	REC_BACKUP,	
    REC_PIC_SEARCH,
    REC_PIC_PLAYBACK,
    REC_PIC_BACKUP,

	REC_MAX,
	RECORD_ALL = 0xff
}RecordLogType_E;

typedef enum _storage_log_type_e_
{
	STOR_FORMAT = 0,
	STOR_NOSPACE,
	STOR_ERR,
	STOR_AUTO_COVER,/*自动覆盖*/
    STOR_CHANGE_PARTITION,
    STOR_HDD_SMART,

	STOR_MAX,
	STOR_ALL = 0xff
}StorageLogType_E;

typedef enum _priority_level_e_ /*日志优先级*/
{
	PRIORITY_LEVEL_NORMAL = 0,
	PRIORITY_LEVEL_MIDDLE,
	PRIORITY_LEVEL_HIGH
}PriorityLevel_E;

typedef enum _log_operation_e_/*日志的具体操作，对应翻译*/
{
	SYSTEM_SETUP = 0,	 /*系统启动*/
	SYSTEM_SHUTDOWN,	 /*系统关闭*/
	SYSTEM_REBOOT,		 /*系统重启*/
	SYSTEM_UPGRADE, 	 /*系统升级*/
	SYSTEM_DEFAULT, 	 /*系统恢复默认值*/
	SYSTEM_MAINTANI,	 /*系统自动维护*/
	SYSTEM_TIMEMODIFY,	 /*系统时间改变*/
	USER_LOGIN_SUCCESS,  /*用户登录成功*/
	USER_LOGIN_FAILED,	 /*用户登录失败*/
	USER_QUIT,			 /*用户登出*/
	USER_MODIFIED = 10,	 /*用户被修改*/
	MOTION_BEGIN,		 /*MOTION告警开始*/
	MOTION_END, 		 /*MOTION告警结束*/
	IOALARM_BEGIN,		 /*IO报警开始*/
	IOALARM_END,		 /*IO报警结束*/
	LENSCOVER_BEGIN,	 /*镜头遮挡告警开始*/
	LENSCOVER_END,		 /*镜头遮挡告警结束*/
	LOG_SEARCH, 		 /*日志查询*/
	LOG_DELETE, 		 /*日志删除*/
	NETWORK_DOWN,		 /*网络断开*/
	NETWORK_UP = 20, 	 /*网络连接*/
	NETWORK_ERROR,		 /*网络异常*/
	NETWORK_CHANGEMODE,  /*联网方式改变*/
	LIVE_MODIFY,         /*预览参数修改*/
	IMAGE_CONTROL_MODIFY,/*ISP参数修改*/
	PRIVACY_ZONE_MODIFY, /*遮挡区域参数修改*/
	REC_PARAM_MODIFY,    /*录像参数修改*/
	NET_SETTING_MODIFY,  /*网络设置参数修改*/
	SYSTEM_MODIFY,       /*系统参数修改*/
	EMAIL_MODIFY,        /*邮件参数修改*/
	DDNS_MODIFY = 30,    /*DDNS参数修改*/
	FTP_UPLOAD_MODIFY,   /*FTP上传参数修改*/
	FTP_UPGRADE_MODIFY,  /*FTP升级参数修改*/
	RTSP_MODIFY,         /*RTSP参数修改*/
	IPFILTER_MODIFY,     /*IP过滤参数修改*/
	MOTION_MODIFY,       /*移动侦测参数修改*/
	IOALARM_MODIFY,      /*IO报警参数修改*/
	LENS_COVER_MODIFY,   /*镜头遮挡参数修改*/
	LOG_MODIFY,          /*日志修改*/
	STORAGE_MODIFY,      /*存储设备参数修改*/
	DATE_TIME_MODIFY = 40, /*时间参数修改*/
	USERPARA_MODIFY,     /*用户参数修改*/
	INFO_MODIFY,         /*系统信息参数修改*/
	MAINTAIN_MODIFY,     /*自动维护参数修改*/
	UPGRADE_MODIFY,      /*升级参数修改*/
	DEFAULT_MODIFY,      /*回复默认参数修改*/
	COLOR_MODIFY,        /*颜色参数修改*/
	NTP_MODIFY,          /*NTP参数修改*/
	DST_MODIFY,          /*DST参数修改*/
	MAINSTREAM_MODIFY,   /*主码流参数修改*/
	SUBSTREAM_MODIFY = 50,/*子码流参数修改*/
	MOBILESTREAM_MODIFY, /*手机码流参数修改*/
	ROI_MODIFY,          /*感兴趣区域参数修改*/
	AUDIO_MODIFY,        /*音量设置参数修改*/
	REC_SCHEDULE_MODIDY, /*录像计划参数修改*/
	STORAGE_FORMAT,      /*格式化硬盘*/
	LCD_BEGIN,		     /*pea告警开始------2018.08.27 pea->LCD*/
	LCD_END, 		     /*pea告警结束------2018.08.27 pea->LCD*/
	SOD_BEGIN,		     /*osc告警开始------2018.08.27 osc->SOD*/
	SOD_END, 		     /*osc告警结束------2018.08.27 osc->SOD*/
	VIDEO_LOSS_BEGIN = 60,/*VIDEO LOSS告警开始*/
	VIDEO_LOSS_END,      /*VIDEO LOSS告警结束*/
	SYSTEM_NTP_UPDATE,    /*NTP校时*/
	VIDEO_MODIFY,        /*输出设置参数修改*/
	PLARFORM_MODIFY,	 /*平台参数修改*/
	PTZ_MODIFY,          /*云台参数修改*/
	ABNORMAL_MODIFY,     /*事件处理参数修改*/
	MANUAL_RECORD_START, /*手动录像开启*/
	MANUAL_RECORD_STOP,  /*手动录像关闭*/
	RECORD_SEARCH,       /*录像搜索*/
	RECORD_PLAYBACK = 70,     /*录像回放*/
	RECORD_BACKUP,       /*录像备份*/
	STORAGE_NOSPACE,     /*硬盘空间不足*/
	STORAGE_ERR,          /*硬盘出错*/
	PID_BEGIN,		     /*PEAAREA_BEGIN,  pea area告警开始*/ // 2015.11.30------2018.08.27 pea area->PID*/
	PID_END, 		     /*PEAAREA_END   pea area告警结束*/ // 2015.11.30------2018.08.27 pea area->PID*/
	PD_BEGIN,
	PD_END,
	FD_BEGIN,
	FD_END,
	CC_BEGIN = 80,
	CC_END,	
	CHN_IPC_ADD ,        /*添加IPC*/
	CHN_IPC_DEL,         /*删除IPC*/
	CHN_IPC_MODIFY,      /*修改IPC参数*/
	CAPTRUE_MODIFY,      /*抓图参数修改*/
	POS_ADD,             /*添加POS机*/
	POS_DELETE,          /*移除POS机*/
	POS_MODIFY,          /*POS机参数修改*/
	USER_ACCOUNT_ADD,    /*添加用户*/
	USER_ACCOUNT_DEL = 90,    /*删除用户*/
	USER_ACCOUNT_MODIFY, /*用户参数修改*/
	USER_LOCK_SCREEN,    /*屏幕锁定*/
	USER_UNLOCK_SCREEN,  /*屏幕解锁*/
	SCHEDULE_REC_START,  /*计划录像开启*/
	PIC_SEARCH,          /*图片搜索*/
	PIC_PLAYBACK,        /*图片回放*/
	PIC_BACKUP,          /*图片备份*/
	STORAGE_AUTO_COVER,  /*硬盘自动覆盖*/
	STORAGE_CHANGE_PAR,  /*硬盘分区改变*/
	STORAGE_HDD_SMART = 100,   /*硬盘S.M.A.R.T*/
	PIRALARM_MODIFY,     /*PIR报警参数修改*/
	PIR_BEGIN,          /*PIR告警开始*/
	PIR_END,            /*PIR告警结束*/
	PTZ_LINKAGE_MODIFY, /*PTZLinkage 联动参数修改*/
	SD_MODIFY,          /*声音报警参数修改*/
	OD_MODIFY,          /*视频遮挡报警参数修改*/
	SHELL_BROKEN,
	SD_BEGIN,           /*声音异常告警开始*/
	SD_END,             /*声音异常告警结束*/
	OD_BEGIN = 110,           /*新镜头遮挡告警开始*/
	OD_END,              /*新镜头遮挡告警开始*/
	ZEROCHN_SET          /*0通道设置*/
}LogOperation_E;

typedef struct _log_time_val_t_
{
	unsigned char  week; 
	unsigned char  second; 
	unsigned char  minute; 
	unsigned char  hour; 
	unsigned char  day; 
	unsigned char  month; 
	unsigned short year; 
}LogTimeVal_t;

typedef union _log_time_t_
{
	LogTimeVal_t time;
	unsigned long long	     timeVal;
}LogTime_t;

typedef struct _log_system_t_
{
	char           UserName[12];		/*当前用户*/
	LogTimeVal_t   TimeSrc;
	LogTimeVal_t   TimeDst;
	char           IPaddr[16]; 		/*IP地址,放最后，方便以后扩充为IPV6*/
	char           reserve[4];
}SystemLog_t;

typedef struct _log_config_t_
{
	char			UserName[12];		/*当前用户*/
	unsigned int    ChnID;				/*通道按位取值*/
	char			IPaddr[16]; 		/*IP地址,放最后，方便以后扩充为IPV6*/
	char			reserve[16]; 	
}ConfigLog_t;

typedef struct _log_alarm_t_
{
	unsigned int    ChnID;				/*通道按位取值*/
	unsigned char   Record; 			/*是否有录像, 1 有， 0 没有*/
	char			reserve[43]; 	
}AlarmLog_t;

typedef struct _log_user_t_
{
	char		    UserName[12];		/*当前用户*/
	char		    DstUser[12]; 	    /*被操作用户*/
	char		    IPaddr[16]; 		/*IP地址,放最后，方便以后扩充为IPV6*/
	char            reserve[8];         
}UserLog_t;

typedef struct _log_record_t_
{
	char			UserName[12];		/*当前用户*/
	unsigned int    ChnID;				/*通道按位取值*/
	LogTimeVal_t    StartTime;       /*录像开始时间 年月日时分秒*/
	char            EndTime[6];         /*录像结束时间，不带年*/
	unsigned short  RecordSize;         /*录像大小 以M为单位*/          
	char			IPaddr[16]; 		/*IP地址,放最后，方便以后扩充为IPV6*/
}RecordLog_t;

typedef struct _log_storage_t_
{
	char			UserName[12];		/*当前用户*/
	unsigned int	HddID;				/*硬盘ID,标识第几个硬盘，按位取*/
	char			SeriorNo[15];       /*序列号*/	
	char			Result;             /*格式化结果 0 success*/	
	char			IPaddr[16]; 		/*IP地址,放最后，方便以后扩充为IPV6*/
}StorageLog_t;

typedef struct _log_network_t_
{
	char			UserName[12];		/*当前用户*/
	UINT            ChnID;               //通道按位取值
	BYTE            Record;             //是否有录像，0：没有，1：有
	char			reserve[15];
	char			IPaddr[16]; 		/*IP地址,放最后，方便以后扩充为IPV6*/
}NetworkLog_t;

typedef struct _ipc_log_t_
{
	LogTime_t		    time;				/*时间*/
	unsigned char		Level;				/*优先级，暂时不用*/
	unsigned char		MainType;			/*日志主类型*/
	unsigned short		SubType;			/*日志子类型*/
	unsigned short		Operation;			/*日志对应的详细信息 所有日志子类型中"ALL"的和不能大于65535*/
	unsigned short		StructSize;         /*结构体大小，字节*/
	union
	{
		SystemLog_t  SystemLog;
		NetworkLog_t NetworkLog;
		ConfigLog_t  ConfigLog;
		AlarmLog_t	 AlarmLog;
		UserLog_t	 UserLog;
		RecordLog_t  RecordLog;
		StorageLog_t StorageLog;
		char        MaxSize[48];       /*共用体大小*/
	}LogInfo;
}IpcLog_t;

typedef struct _log_search_input_t_
{
	LogTime_t	   Start;
	LogTime_t	   End;
	LogMainType_E  MainType;   /*日志主类型*/
	unsigned short		   SubType;    /*日志子类型*/
	unsigned char          reserve[2];
}LogSearchInput_t;

typedef struct _log_search_output_t_
{
	int	   TotalNum;	   /*实际查找的条数*/
	unsigned int	   StructSize;	   /*sizeof(IpcLog_t)*/
	IpcLog_t   *pLog;
}LogSearchOutput_t;

typedef struct _log_search_para_t_
{
	LogSearchInput_t  Input;   /*查询条件*/
	LogSearchOutput_t Output;  /*日志搜索结果*/
	int			  Result;  /*搜索线程返回结果*/
}LogSearchPara_t;

typedef struct 
{
	int UserKey;
	int Reserve;
	LogSearchInput_t inputinfo;
}SearchLogReq_t;
//////////////////////////***log***////////////////////////////

//////////////////////////////////////////////////////////////////////////
//远程升级
#define UPGRADE_PACKET_MAGIC    0x08122515
#define SOFTWARE_VERSION_LEN    7
#define MAX_DEVICENAME_LEN 128

/*升级机型*/
#define GEN_DVR16H  "DVR16H"
#define GEN_DVR16D1 "DVR16D1"
#define GEN_DVR8D1  "DVR8D1"
#define GEN_DVR4D1  "DVR4D1"
#define GEN_DVR16CIF	"DVR16C"
#define GEN_DVR8CIF "DVR08C"
#define GEN_DVR4CIF	"DVR04C"


typedef struct _upgradefileheaderentry_{
	/*这里定义的版本号长度是包括字符串结束标志的，
	下面将加上这个字符串结束标志，同时4字节对齐*/
	char version[(SOFTWARE_VERSION_LEN + 1 +  3) / 4 * 4]; 
	unsigned long start;/*文件内的偏移量*/
	unsigned long len;/*升级数据的长度*/
}upgradefileheaderentry_t;

typedef struct _upgradefileheader_{
	unsigned long magic;/*结构体幻数*/
	unsigned long crc;/*这里的CRC值是该结构体的下面的域及程序数据的CRC校验值*/
	unsigned short version;
	unsigned short Language_flag; /*1:CHINESE ONLY 0:MLANG */ 
	upgradefileheaderentry_t boot;
	upgradefileheaderentry_t kernel;
	upgradefileheaderentry_t rootfs;
	upgradefileheaderentry_t app;
	upgradefileheaderentry_t slave_boot;
	upgradefileheaderentry_t slave_kernel;
	upgradefileheaderentry_t slave_rootfs;
	upgradefileheaderentry_t logo;
}upgradefileheader_t;

typedef struct _upgradefileheaderEx_{
	unsigned long magic;
	unsigned long crc;
	unsigned short version;
	unsigned short Language_flag; /*1:CHINESE ONLY 0:MLANG */ 
	upgradefileheaderentry_t boot;
	upgradefileheaderentry_t kernel;
	upgradefileheaderentry_t rootfs;
	upgradefileheaderentry_t app;
	upgradefileheaderentry_t slave_boot;
	upgradefileheaderentry_t slave_kernel;
	upgradefileheaderentry_t slave_rootfs;
	upgradefileheaderentry_t logo;
	upgradefileheaderentry_t www;
}upgradefileheaderEx_t;

typedef struct _Newupgradefileheader_{
	unsigned long magic;/*结构体幻数*/
	unsigned long crc;/*这里的CRC值是该结构体的下面的域及程序数据的CRC校验值*/
	unsigned short version;/*结构体版本*/
	unsigned short Language_flag; /*1:CHINESE ONLY 0:MLANG */ 
	upgradefileheaderentry_t boot;
	upgradefileheaderentry_t kernel;
	upgradefileheaderentry_t rootfs;
	upgradefileheaderentry_t app;
	upgradefileheaderentry_t slave_boot;
	upgradefileheaderentry_t slave_kernel;
	upgradefileheaderentry_t slave_rootfs;
	upgradefileheaderentry_t logo;
	upgradefileheaderentry_t www;
	upgradefileheaderentry_t fpga;
}Newupgradefileheader_t;

/******new upgrade    filetype = 3******/
typedef struct _upgradefileheaderentry_ex_
{
	/*这里定义的版本号长度是包括字符串结束标志的，
	 下面将加上这个字符串结束标志，同时4字节对齐*/
	char         version[(SOFTWARE_VERSION_LEN + 1 +  3) / 4 * 4];
	unsigned int bufStart;/*文件内的偏移量*/
	unsigned int bufLen;/*升级数据的长度*/
	unsigned int partname;  //文件的名称，用bitmap表示
	unsigned int partStart; //升级文件在flash分区的起始地址	
	unsigned int partLen; //升级文件在flash分区的长度
    char         reserve[64]; //保留字节
}upgradefileheaderentry_ex_t;

typedef struct {
    unsigned int StructSize;
    char         DeviceType[MAX_DEVICENAME_LEN];
}RS_UpgradeExtInfo_t;

typedef struct _upgradefileheader_ex_
{
    unsigned int   upgradeTag; //新增标识，标志是安联的包
    unsigned int   crc;/*这里的CRC值是该结构体的下面的域及程序数据的CRC校验值*/
    unsigned short version;/*结构体版本*/
    unsigned short Language_flag; /*1:CHINESE ONLY, 0 MLANG*/
    int            partnum;  //需要升级的文件个数	
    char           aPacketPreFix[64];  //文件包头名，用于校检
    char           reserve[64]; //保留字节
}upgradefileheader_ex_t;

typedef struct {
    upgradefileheader_ex_t UpGradeHead;
    RS_UpgradeExtInfo_t    UpgradeExtInfo;
}RSMode_UpgradeFileHeader_EX_t;
/******end new upgrade******/

typedef struct
{
    UINT StructSize; //sizeof(DownloadRecordFileReq)
    UINT UserKey;
    UINT Channel;
}DownloadRecordFileReqOld;

//恢复出荷状态的结构体
typedef struct{
    UINT StructSize;	/* 该结构体大小*/
    DateTime Time;	/* 系统时间*/
    BYTE FactoryMod;	/* 0, 不恢复出厂1, 恢复出厂 */
    BYTE Reserve[15];
}RSNet_New_Factory_Default;

typedef struct {
    unsigned int  struct_size;
    int           file_length;
    char          file_name[64];
    unsigned char reserve[64];
}upgrade_power_system_file;

typedef struct {
    unsigned int  struct_size;
    int           file_num;
    unsigned char reserve[64];
}upgrade_power_system_head;

#define RSBackupSpecialiInfoTag *(unsigned long long*)"BackInfo"
typedef struct {
    unsigned long long tag;               //RSBackupSpecialiInfoTag
    unsigned int       struct_size;       //sizeof(backupspecialinfo_t)
    int                channel;           //0  1  2  3  4...   
    char               mac_addr[32];      //"00-11-22-33-44-55"
    char               serial_number[32]; //"raysharp"
    char               device_type[32];   //"raysahrp"
    unsigned long long begin_time;        //microsecond
    unsigned long long end_time;          //microsecond
    char               reserve[384];
}backupspecialinfo_t;

#endif
