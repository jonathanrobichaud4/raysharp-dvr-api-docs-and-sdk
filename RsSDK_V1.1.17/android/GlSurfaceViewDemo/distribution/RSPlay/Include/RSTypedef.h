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

#define MsgPTZStartPriZoneSet		70          //��ʼ��˽�ڵ�����
#define MsgPTZStopPriZoneSet		71          //������˽�ڵ�����

#define Open_Screen_PTZ             97
#define Close_Screen_PTZ            98

#define MsgParamDevLog					 160608 //2016.06.08 �Լ�д��
#define MsgParamScheduleIPC				 160825 //2016.08.25 ����IPC¼��ƻ�
#define MsgParamExportIPC                161121//2016.11.21 ipc�������뵼��
#define MsgParamTour					 171109//2017.11.09 ZIP preset��tour����
#define MsgShowResolution				 171218//2017.12.18 Ԥ����ʾ�ֱ���
#define MsgShowFrameRate			     180704//2018.07.04 Ԥ����ʾ֡��

#define MsgSensorStatusReport_PIR       20161103	//���Լ����壬�Լ�ʹ�õ�
#define MsgSensorStatusReport_Smoke     20161104	//���Լ����壬�Լ�ʹ�õ�
#define MsgNewRecordDetail		        20170622	//���Լ����壬�Լ�ʹ�õ�
#define MsgP2PTunnelInfo                60000	    //���Լ����壬�Լ�ʹ�õ�

/*****�»ط�����*******/
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
#define NetbreakRec    0x800      //2018.08.23,��������ͬ��
#define SoundRec       0x1000      //2018.08.23,��������ͬ��

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
	IPCS_NETWRONG = 0,/*�޷����ӵ�IPC*/
	IPCS_UNAUTHER = 1,/*�û���֤ʧ��*/
	IPCS_ONLINE   = 2,/*��ʾ��¼���������ɹ�*/
	IPCS_CONNECT  = 3,/*��������*/
	IPCS_BANDLIMIT= 4,/*���������ƶ����Ͽ�*/
    IPCS_VIDEOLOSS = 5,
    IPCS_SLEEP     = 6
}IPChnStatus_e;

typedef enum _ChnStatus_{
	CHN_BOTTOM = -1,/*Did not add*/
	CHN_NETWRONG = 0,/*�޷����ӵ�IPC*/
	CHN_UNAUTHER = 1,/*�û���֤ʧ��*/
	CHN_ONLINE = 2,/*���ӳɹ����Զ�����Ԥ��*/
	CHN_CONNECT = 3,/*��������*/
	CHN_BANDLIMIT = 4,/*���������ƶ����Ͽ�*/
	CHN_VIDEOLOSS = 5,
	CHN_SLEEP = 6/*���ߵ�����������״̬�����ֶ�����Ԥ��*/
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
    ABILITY_TYPE_IO,/*ǰ���豸�Ƿ�֧��IO����*/
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
    ABILITY_TYPE_BINOCULARS,//˫Ŀ
    ABILITY_TYPE_OSDTRANSPARENCY,//OSD͸��������
    ABILITY_TYPE_CORRIDOR_ANGLEROTATION,//�Ƿ�֧������ģʽ�ͽǶ���ת
    ABILITY_TYPE_PIR,
	ABILITY_TYPE_SMART_MOTIION,
	ABILITY_TYPE_SUPPROT_WIREFREE,//wireless//wireless channel preview can not AutoReconnect
	ABILITY_TYPE_WHITE_LIGHT,
	ABILITY_TYPE_LOUD_SPEAKER,
	ABILITY_TYPE_TALK_HALF, //ABILITY_TYPE_AFOCUS
	ABILITY_TYPE_TALK_FULL,
	ABILITY_TYPE_EVENTSTREAM,
	ABILITY_TYPE_SOUNDDETECTION = 31, //��������
}Net_ABILITY_TYPE_E;

typedef enum
{
	ABILITY_TYPE_ODDETECTION ,//�ڵ�����
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
    PROTO_TYPE_RSSZ,   /*����TI����˽��Э��*/
    PROTO_TYPE_SAMSUNG,/*����*/
    PROTO_TYPE_ZXNH  ,  /*�����޺�*/
    PROTO_TYPE_ONVIF = 4,  /*onvif */
    PROTO_TYPE_URMET,	/*urmetЭ��IPC*/
    PROTO_TYPE_AMTK,
    PROTO_TYPE_SHANY,
	PROTO_TYPE_ZHUOWEI,
    PROTO_TYPE_MINGJING,
	PROTO_TYPE_FSAN,
	PROTO_TYPE_QIHAN,
	PROTO_TYPE_GRANDMEDIA,/*DENAVO�ͻ�(�Խ�GRANDMEDIA˽��Э��)*/
	PROTO_TYPE_SONIX,	  /*�ɺ�Э��*/
	PROTO_TYPE_YCX,		  /*GW�ͻ�(�д���˽��Э��)*/
	PROTO_TYPE_HANHUI = 15, /*����˽��Э��*/
	PROTO_TYPE_GUOWEI,	   /*GIGAMEDIA�ͻ�(��Ϊ�Խ�Э��)*/
	PROTO_TYPE_HIKVISION,  /*����˽��Э��*/
	PROTO_TYPE_ZHINUO,	 /*��ŵ�Խ�Э��(δ����)*/
	PROTO_TYPE_JINGYANG,
    PROTO_TYPE_NULL, // ��С��32
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
    LANGUAGE_CHINESE		 = 0,	 //��������
    LANGUAGE_CHINESECOMPLEX  = 1,	 //��������
    LANGUAGE_CZECH			 = 2,	 //�ݿ���
    LANGUAGE_DANISH 		 = 3,	 //������
    LANGUAGE_ENGLISH		 = 4,	 //Ӣ��
    LANGUAGE_FINNISH		 = 5,	 //������
    LANGUAGE_FRENCH 		 = 6,	 //����
    LANGUAGE_GERMAN 		 = 7,	 //����
    LANGUAGE_GREEK			 = 8,	 //ϣ����
    LANGUAGE_HEBREW 		 = 9,	 //ϣ������
    LANGUAGE_HUNGARIAN		 = 10,	 //��������
    LANGUAGE_INTALIAN		 = 11,	 //�������
    LANGUAGE_JAPANESE		 = 12,	 //����
    LANGUAGE_POLISH 		 = 13,	 //������
    LANGUAGE_PORTUGUESE 	 = 14,	 //��������
    LANGUAGE_RUSSIAN		 = 15,	 //����
    LANGUAGE_SPANISH		 = 16,	 //��������
    LANGUAGE_THAI			 = 17,	 //̩��
    LANGUAGE_SLOVENIA		 = 18,	 //˹����������
    LANGUAGE_ROMANIAN		 = 19,	 //����������
    LANGUAGE_BULGARIAN		 = 20,	 //����������
    LANGUAGE_ARABIC          = 21,   //��������
    LANGUAGE_HINDI           = 22,   //ӡ����
    LANGUAGE_VIETNAM         = 23,   //Խ����
    LANGUAGE_HOLLAND         = 24,   //������
    LANGUAGE_TURKEY          = 25,   //��������
    LANGUAGE_PERSION         = 26,   //��˹��
    LANGUAGE_SVENSKA         = 27,   //�����
    LANGUAGE_KOREAN 		 = 28,  //����
    LANGUAGE_UKRAINIAN       = 29,  //�ڿ�����
    LANGUAGE_SLOVAK          = 30,  //˹�工����
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
    char RecState;               /* ¼��״̬ */
    char CurRecType;             /* ��ǰ¼������ */
    char MDSchedule;             /* �ƶ������ƻ�*/
	char MDRecEnable;           /* �Ƿ���MD����¼���� */
}MotionAlarmRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
    char RecState;               /* ¼��״̬ */
    char CurRecType;             /* ��ǰ¼������ */
    char AlarmSchedule;          /* IO�����ƻ�*/
	char Reserved[1];
}IOAlarmRpt;

/* Զ������IPC��ǰ״̬ */
typedef struct
{
    int structsize; //�ṹ���С
    int channelNo;  //ͨ����
    char status;    //IPC״̬. ��ӦRS_UGIpcStatus_e
    char progress;  //��������
    char reserved[6];
}RS_UGIpcRsp_t;

/* Զ������IPC״̬���� */
typedef enum
{
    Stat_Err = -2,   //����ȴ���
    Stat_Failed = -1,//����ʧ��
    Stat_Inprogress, //����������
    Stat_Success     //�����ɹ�
}RS_UGIpcStatus_e;

/* Զ���������ƹ̼���������(kguard DVR) */
typedef enum _upgrade_fw_e_
{
    FW_DONOT_NEED       = -1,//����Ҫ����
    FW_DISCONNECTED     = 0, //����ʧ��
    FW_DOWNLOADING      = 1, //��������
    FW_MD5_NOT_MATCHED  = 2, //������ɵ�MD5��ƥ��,ֹͣ����
    FW_DEV_REBOOT       = 3  //���������MD5��ƥ��,�����豸
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
	LOG_ALL = 0xff 	/*������־����־���������255��*/
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
	NET_DOWN = 0,	/*����Ͽ�*/
	NET_UP, 		/*��������*/
	NET_ERROR,		/*�����쳣*/
	NET_CHANGEMODE, /*������ʽ�ı�*/

	NET_MAX,
	NET_ALL =  0xff
}NetLogType_E;

typedef enum _config_log_type_e_ /*������������ҳ��*/
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
    CFG_CAPTRUE_MODIFY,/*ץͼҳ������޸�*/
    CFG_POS_ADD,/*POS�����*/
    CFG_POS_DELETE,/*POS��ɾ��*/
    CFG_POS_MODIFY,/*POS���޸�*/
    CFG_PIRALARM,/*PIR����ҳ���޸�*/
	CFG_ALARM_LINKAGE_PTZ,/*PTZ linkage����ҳ���޸�*/
    CFG_SD_MODIFY,/*�����澯����ҳ���޸�*/
    CFG_OD_MODIFY,/*��ͷ�ڵ�����ҳ���޸�*/
	CFG_ZEROCHN,/*��ͨ��ҳ���޸�*/
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
	ALARM_SHELL_BROKEN, /*��Ǳ���*/
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
	STOR_AUTO_COVER,/*�Զ�����*/
    STOR_CHANGE_PARTITION,
    STOR_HDD_SMART,

	STOR_MAX,
	STOR_ALL = 0xff
}StorageLogType_E;

typedef enum _priority_level_e_ /*��־���ȼ�*/
{
	PRIORITY_LEVEL_NORMAL = 0,
	PRIORITY_LEVEL_MIDDLE,
	PRIORITY_LEVEL_HIGH
}PriorityLevel_E;

typedef enum _log_operation_e_/*��־�ľ����������Ӧ����*/
{
	SYSTEM_SETUP = 0,	 /*ϵͳ����*/
	SYSTEM_SHUTDOWN,	 /*ϵͳ�ر�*/
	SYSTEM_REBOOT,		 /*ϵͳ����*/
	SYSTEM_UPGRADE, 	 /*ϵͳ����*/
	SYSTEM_DEFAULT, 	 /*ϵͳ�ָ�Ĭ��ֵ*/
	SYSTEM_MAINTANI,	 /*ϵͳ�Զ�ά��*/
	SYSTEM_TIMEMODIFY,	 /*ϵͳʱ��ı�*/
	USER_LOGIN_SUCCESS,  /*�û���¼�ɹ�*/
	USER_LOGIN_FAILED,	 /*�û���¼ʧ��*/
	USER_QUIT,			 /*�û��ǳ�*/
	USER_MODIFIED = 10,	 /*�û����޸�*/
	MOTION_BEGIN,		 /*MOTION�澯��ʼ*/
	MOTION_END, 		 /*MOTION�澯����*/
	IOALARM_BEGIN,		 /*IO������ʼ*/
	IOALARM_END,		 /*IO��������*/
	LENSCOVER_BEGIN,	 /*��ͷ�ڵ��澯��ʼ*/
	LENSCOVER_END,		 /*��ͷ�ڵ��澯����*/
	LOG_SEARCH, 		 /*��־��ѯ*/
	LOG_DELETE, 		 /*��־ɾ��*/
	NETWORK_DOWN,		 /*����Ͽ�*/
	NETWORK_UP = 20, 	 /*��������*/
	NETWORK_ERROR,		 /*�����쳣*/
	NETWORK_CHANGEMODE,  /*������ʽ�ı�*/
	LIVE_MODIFY,         /*Ԥ�������޸�*/
	IMAGE_CONTROL_MODIFY,/*ISP�����޸�*/
	PRIVACY_ZONE_MODIFY, /*�ڵ���������޸�*/
	REC_PARAM_MODIFY,    /*¼������޸�*/
	NET_SETTING_MODIFY,  /*�������ò����޸�*/
	SYSTEM_MODIFY,       /*ϵͳ�����޸�*/
	EMAIL_MODIFY,        /*�ʼ������޸�*/
	DDNS_MODIFY = 30,    /*DDNS�����޸�*/
	FTP_UPLOAD_MODIFY,   /*FTP�ϴ������޸�*/
	FTP_UPGRADE_MODIFY,  /*FTP���������޸�*/
	RTSP_MODIFY,         /*RTSP�����޸�*/
	IPFILTER_MODIFY,     /*IP���˲����޸�*/
	MOTION_MODIFY,       /*�ƶ��������޸�*/
	IOALARM_MODIFY,      /*IO���������޸�*/
	LENS_COVER_MODIFY,   /*��ͷ�ڵ������޸�*/
	LOG_MODIFY,          /*��־�޸�*/
	STORAGE_MODIFY,      /*�洢�豸�����޸�*/
	DATE_TIME_MODIFY = 40, /*ʱ������޸�*/
	USERPARA_MODIFY,     /*�û������޸�*/
	INFO_MODIFY,         /*ϵͳ��Ϣ�����޸�*/
	MAINTAIN_MODIFY,     /*�Զ�ά�������޸�*/
	UPGRADE_MODIFY,      /*���������޸�*/
	DEFAULT_MODIFY,      /*�ظ�Ĭ�ϲ����޸�*/
	COLOR_MODIFY,        /*��ɫ�����޸�*/
	NTP_MODIFY,          /*NTP�����޸�*/
	DST_MODIFY,          /*DST�����޸�*/
	MAINSTREAM_MODIFY,   /*�����������޸�*/
	SUBSTREAM_MODIFY = 50,/*�����������޸�*/
	MOBILESTREAM_MODIFY, /*�ֻ����������޸�*/
	ROI_MODIFY,          /*����Ȥ��������޸�*/
	AUDIO_MODIFY,        /*�������ò����޸�*/
	REC_SCHEDULE_MODIDY, /*¼��ƻ������޸�*/
	STORAGE_FORMAT,      /*��ʽ��Ӳ��*/
	LCD_BEGIN,		     /*pea�澯��ʼ------2018.08.27 pea->LCD*/
	LCD_END, 		     /*pea�澯����------2018.08.27 pea->LCD*/
	SOD_BEGIN,		     /*osc�澯��ʼ------2018.08.27 osc->SOD*/
	SOD_END, 		     /*osc�澯����------2018.08.27 osc->SOD*/
	VIDEO_LOSS_BEGIN = 60,/*VIDEO LOSS�澯��ʼ*/
	VIDEO_LOSS_END,      /*VIDEO LOSS�澯����*/
	SYSTEM_NTP_UPDATE,    /*NTPУʱ*/
	VIDEO_MODIFY,        /*������ò����޸�*/
	PLARFORM_MODIFY,	 /*ƽ̨�����޸�*/
	PTZ_MODIFY,          /*��̨�����޸�*/
	ABNORMAL_MODIFY,     /*�¼���������޸�*/
	MANUAL_RECORD_START, /*�ֶ�¼����*/
	MANUAL_RECORD_STOP,  /*�ֶ�¼��ر�*/
	RECORD_SEARCH,       /*¼������*/
	RECORD_PLAYBACK = 70,     /*¼��ط�*/
	RECORD_BACKUP,       /*¼�񱸷�*/
	STORAGE_NOSPACE,     /*Ӳ�̿ռ䲻��*/
	STORAGE_ERR,          /*Ӳ�̳���*/
	PID_BEGIN,		     /*PEAAREA_BEGIN,  pea area�澯��ʼ*/ // 2015.11.30------2018.08.27 pea area->PID*/
	PID_END, 		     /*PEAAREA_END   pea area�澯����*/ // 2015.11.30------2018.08.27 pea area->PID*/
	PD_BEGIN,
	PD_END,
	FD_BEGIN,
	FD_END,
	CC_BEGIN = 80,
	CC_END,	
	CHN_IPC_ADD ,        /*���IPC*/
	CHN_IPC_DEL,         /*ɾ��IPC*/
	CHN_IPC_MODIFY,      /*�޸�IPC����*/
	CAPTRUE_MODIFY,      /*ץͼ�����޸�*/
	POS_ADD,             /*���POS��*/
	POS_DELETE,          /*�Ƴ�POS��*/
	POS_MODIFY,          /*POS�������޸�*/
	USER_ACCOUNT_ADD,    /*����û�*/
	USER_ACCOUNT_DEL = 90,    /*ɾ���û�*/
	USER_ACCOUNT_MODIFY, /*�û������޸�*/
	USER_LOCK_SCREEN,    /*��Ļ����*/
	USER_UNLOCK_SCREEN,  /*��Ļ����*/
	SCHEDULE_REC_START,  /*�ƻ�¼����*/
	PIC_SEARCH,          /*ͼƬ����*/
	PIC_PLAYBACK,        /*ͼƬ�ط�*/
	PIC_BACKUP,          /*ͼƬ����*/
	STORAGE_AUTO_COVER,  /*Ӳ���Զ�����*/
	STORAGE_CHANGE_PAR,  /*Ӳ�̷����ı�*/
	STORAGE_HDD_SMART = 100,   /*Ӳ��S.M.A.R.T*/
	PIRALARM_MODIFY,     /*PIR���������޸�*/
	PIR_BEGIN,          /*PIR�澯��ʼ*/
	PIR_END,            /*PIR�澯����*/
	PTZ_LINKAGE_MODIFY, /*PTZLinkage ���������޸�*/
	SD_MODIFY,          /*�������������޸�*/
	OD_MODIFY,          /*��Ƶ�ڵ����������޸�*/
	SHELL_BROKEN,
	SD_BEGIN,           /*�����쳣�澯��ʼ*/
	SD_END,             /*�����쳣�澯����*/
	OD_BEGIN = 110,           /*�¾�ͷ�ڵ��澯��ʼ*/
	OD_END,              /*�¾�ͷ�ڵ��澯��ʼ*/
	ZEROCHN_SET          /*0ͨ������*/
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
	char           UserName[12];		/*��ǰ�û�*/
	LogTimeVal_t   TimeSrc;
	LogTimeVal_t   TimeDst;
	char           IPaddr[16]; 		/*IP��ַ,����󣬷����Ժ�����ΪIPV6*/
	char           reserve[4];
}SystemLog_t;

typedef struct _log_config_t_
{
	char			UserName[12];		/*��ǰ�û�*/
	unsigned int    ChnID;				/*ͨ����λȡֵ*/
	char			IPaddr[16]; 		/*IP��ַ,����󣬷����Ժ�����ΪIPV6*/
	char			reserve[16]; 	
}ConfigLog_t;

typedef struct _log_alarm_t_
{
	unsigned int    ChnID;				/*ͨ����λȡֵ*/
	unsigned char   Record; 			/*�Ƿ���¼��, 1 �У� 0 û��*/
	char			reserve[43]; 	
}AlarmLog_t;

typedef struct _log_user_t_
{
	char		    UserName[12];		/*��ǰ�û�*/
	char		    DstUser[12]; 	    /*�������û�*/
	char		    IPaddr[16]; 		/*IP��ַ,����󣬷����Ժ�����ΪIPV6*/
	char            reserve[8];         
}UserLog_t;

typedef struct _log_record_t_
{
	char			UserName[12];		/*��ǰ�û�*/
	unsigned int    ChnID;				/*ͨ����λȡֵ*/
	LogTimeVal_t    StartTime;       /*¼��ʼʱ�� ������ʱ����*/
	char            EndTime[6];         /*¼�����ʱ�䣬������*/
	unsigned short  RecordSize;         /*¼���С ��MΪ��λ*/          
	char			IPaddr[16]; 		/*IP��ַ,����󣬷����Ժ�����ΪIPV6*/
}RecordLog_t;

typedef struct _log_storage_t_
{
	char			UserName[12];		/*��ǰ�û�*/
	unsigned int	HddID;				/*Ӳ��ID,��ʶ�ڼ���Ӳ�̣���λȡ*/
	char			SeriorNo[15];       /*���к�*/	
	char			Result;             /*��ʽ����� 0 success*/	
	char			IPaddr[16]; 		/*IP��ַ,����󣬷����Ժ�����ΪIPV6*/
}StorageLog_t;

typedef struct _log_network_t_
{
	char			UserName[12];		/*��ǰ�û�*/
	UINT            ChnID;               //ͨ����λȡֵ
	BYTE            Record;             //�Ƿ���¼��0��û�У�1����
	char			reserve[15];
	char			IPaddr[16]; 		/*IP��ַ,����󣬷����Ժ�����ΪIPV6*/
}NetworkLog_t;

typedef struct _ipc_log_t_
{
	LogTime_t		    time;				/*ʱ��*/
	unsigned char		Level;				/*���ȼ�����ʱ����*/
	unsigned char		MainType;			/*��־������*/
	unsigned short		SubType;			/*��־������*/
	unsigned short		Operation;			/*��־��Ӧ����ϸ��Ϣ ������־��������"ALL"�ĺͲ��ܴ���65535*/
	unsigned short		StructSize;         /*�ṹ���С���ֽ�*/
	union
	{
		SystemLog_t  SystemLog;
		NetworkLog_t NetworkLog;
		ConfigLog_t  ConfigLog;
		AlarmLog_t	 AlarmLog;
		UserLog_t	 UserLog;
		RecordLog_t  RecordLog;
		StorageLog_t StorageLog;
		char        MaxSize[48];       /*�������С*/
	}LogInfo;
}IpcLog_t;

typedef struct _log_search_input_t_
{
	LogTime_t	   Start;
	LogTime_t	   End;
	LogMainType_E  MainType;   /*��־������*/
	unsigned short		   SubType;    /*��־������*/
	unsigned char          reserve[2];
}LogSearchInput_t;

typedef struct _log_search_output_t_
{
	int	   TotalNum;	   /*ʵ�ʲ��ҵ�����*/
	unsigned int	   StructSize;	   /*sizeof(IpcLog_t)*/
	IpcLog_t   *pLog;
}LogSearchOutput_t;

typedef struct _log_search_para_t_
{
	LogSearchInput_t  Input;   /*��ѯ����*/
	LogSearchOutput_t Output;  /*��־�������*/
	int			  Result;  /*�����̷߳��ؽ��*/
}LogSearchPara_t;

typedef struct 
{
	int UserKey;
	int Reserve;
	LogSearchInput_t inputinfo;
}SearchLogReq_t;
//////////////////////////***log***////////////////////////////

//////////////////////////////////////////////////////////////////////////
//Զ������
#define UPGRADE_PACKET_MAGIC    0x08122515
#define SOFTWARE_VERSION_LEN    7
#define MAX_DEVICENAME_LEN 128

/*��������*/
#define GEN_DVR16H  "DVR16H"
#define GEN_DVR16D1 "DVR16D1"
#define GEN_DVR8D1  "DVR8D1"
#define GEN_DVR4D1  "DVR4D1"
#define GEN_DVR16CIF	"DVR16C"
#define GEN_DVR8CIF "DVR08C"
#define GEN_DVR4CIF	"DVR04C"


typedef struct _upgradefileheaderentry_{
	/*���ﶨ��İ汾�ų����ǰ����ַ���������־�ģ�
	���潫��������ַ���������־��ͬʱ4�ֽڶ���*/
	char version[(SOFTWARE_VERSION_LEN + 1 +  3) / 4 * 4]; 
	unsigned long start;/*�ļ��ڵ�ƫ����*/
	unsigned long len;/*�������ݵĳ���*/
}upgradefileheaderentry_t;

typedef struct _upgradefileheader_{
	unsigned long magic;/*�ṹ�����*/
	unsigned long crc;/*�����CRCֵ�Ǹýṹ���������򼰳������ݵ�CRCУ��ֵ*/
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
	unsigned long magic;/*�ṹ�����*/
	unsigned long crc;/*�����CRCֵ�Ǹýṹ���������򼰳������ݵ�CRCУ��ֵ*/
	unsigned short version;/*�ṹ��汾*/
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
	/*���ﶨ��İ汾�ų����ǰ����ַ���������־�ģ�
	 ���潫��������ַ���������־��ͬʱ4�ֽڶ���*/
	char         version[(SOFTWARE_VERSION_LEN + 1 +  3) / 4 * 4];
	unsigned int bufStart;/*�ļ��ڵ�ƫ����*/
	unsigned int bufLen;/*�������ݵĳ���*/
	unsigned int partname;  //�ļ������ƣ���bitmap��ʾ
	unsigned int partStart; //�����ļ���flash��������ʼ��ַ	
	unsigned int partLen; //�����ļ���flash�����ĳ���
    char         reserve[64]; //�����ֽ�
}upgradefileheaderentry_ex_t;

typedef struct {
    unsigned int StructSize;
    char         DeviceType[MAX_DEVICENAME_LEN];
}RS_UpgradeExtInfo_t;

typedef struct _upgradefileheader_ex_
{
    unsigned int   upgradeTag; //������ʶ����־�ǰ����İ�
    unsigned int   crc;/*�����CRCֵ�Ǹýṹ���������򼰳������ݵ�CRCУ��ֵ*/
    unsigned short version;/*�ṹ��汾*/
    unsigned short Language_flag; /*1:CHINESE ONLY, 0 MLANG*/
    int            partnum;  //��Ҫ�������ļ�����	
    char           aPacketPreFix[64];  //�ļ���ͷ��������У��
    char           reserve[64]; //�����ֽ�
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

//�ָ�����״̬�Ľṹ��
typedef struct{
    UINT StructSize;	/* �ýṹ���С*/
    DateTime Time;	/* ϵͳʱ��*/
    BYTE FactoryMod;	/* 0, ���ָ�����1, �ָ����� */
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
