#ifndef __RSNet_h__
#define __RSNet_h__

#include "RSTypedef.h"
#include "RSNetParameter.h"
#include "RSNetProtocol.h"

#ifdef _WIN32
#  ifdef RSNET_EXPORTS
#    define RSNET_API __declspec(dllexport)
#  else
#    define RSNET_API __declspec(dllimport)
#  endif
#  define RSNET_CALL __stdcall
#else
#  define RSNET_API
#  define RSNET_CALL
#endif

//////////////////////////////////////////////////////////////////////////
//搜索设备

//RSNetSearchDevParam.Callback
//dev为NULL，代表搜索结束；返回FALSE取消搜索，将不会再调用该回调函数
//注意：只有当搜索结束或是取消后，才能销毁搜索的回调函数涉及到的资源，否则可能会发生错误。
typedef BOOL (RSNET_CALL* RSNetSearchDevCallback)(const SearchDevRsp* dev, void* userParam);

typedef struct 
{
	RSNetSearchDevCallback Callback;
	void* UserParam;
    BYTE  LoginClientType;//1:电商 2:Zip  3:CDoubles    4:Raydin 6:optimus
    BYTE  reserve[3];
}RSNetSearchDevParam;

typedef struct 
{
    RSNetSearchDevCallback Callback;
    void* UserParam;
    BYTE  LoginClientType;//1:电商 2:Zip  3:CDoubles    4:Raydin 6:optimus
    BYTE  reserve[3];
    char  StartIP[64]; //such as "192.168.1.1"
    char  StopIP[64];  //such as "192.168.2.254"
    char  reserve2[256];
}RSNetSearchDevParamPoint2Point;

//////////////////////////////////////////////////////////////////////////
//http请求

//RSNetHttpReq.Callback
//buf为NULL，代表搜索结束；返回FALSE取消搜索，将不会再调用该回调函数
//注意：只有当搜索结束或是取消后，才能销毁搜索的回调函数涉及到的资源，否则可能会发生错误。
typedef BOOL (RSNET_CALL* RSNetHttpReqCallbackGeneral)(const void* buf, int len, void* userParam);

typedef struct 
{
	char*    buf;//http请求格式数据
	int      len;//数据长度
	PCSTR    IP; //域名或者IP地址
	UINT     Port; //IE 端口
	UINT     timeout; //超时时间(s)
	RSNetHttpReqCallbackGeneral Callback;
	void* UserParam;
	char szHeadFlag[32];   //回应信息结尾标识 
}RSNetHttpReqGeneral;

typedef struct
{
    char*    buf;//http请求格式数据
    int      len;//数据长度
    char*    IP; //域名或者IP地址
    UINT     Port; //IE 端口
    int      nRecvTimeout;
    int      nSendTimeOut;
    int      bReConnect;
    int      nReConnectCount;
    int      nIntervalTimeOut;
    char     szHeadFlag[32];   //回应信息结尾标识
    void*    UserParam;
    RSNetHttpReqCallbackGeneral Callback;
}RSNetHttpReqEx;

typedef void* RSNetIDConnection;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//P2P
typedef BOOL (RSNET_CALL* RSNetP2PTunnelReqCallback)(const void* buf, int len, void* userParam);

typedef struct
{
    char*    pID;
    int      nMediaPort;
    int      bReConnect;
    int      nReConnectCount;
    int      nIntervalTimeOut;
    void*    UserParam;
    RSNetP2PTunnelReqCallback Callback;
}RSNetP2PTunnelReq;

typedef void* RSNetP2PTunnelConnection;
//////////////////////////////////////////////////////////////////////////

//消息回调
//waram
//RSNetConnection msg
#define RSNetMsgConnectStart				0
#define RSNetMsgConnectSuccess				1
#define RSNetMsgConnectFail					2
#define RSNetMsgConnectClosed				3
#define RSNetMsgConnectStop                 4
#define RSNetMsgLoginRequest				100
#define RSNetMsgLoginSuccess				101
#define RSNetMsgLoginUserLogined			102
#define RSNetMsgLoginNoUserName				103
#define RSNetMsgLoginPasswordError			104
#define RSNetMsgLoginFail					105
#define RSNetMsgLoginNoRight                106
#define RSNetMsgIpFilter					107
#define RSNetMsgOverMaxUser                 108
#define RSNetMsgNotSupportLoginType         109
#define RSNetMsgLoginUserDisable			110
#define RSNetMsgLoginForceChangePWD			111
#define RSNetMsgLoginForceCloseBrowser		112
#define RSNetMsgLoginForbidIP               113
#define RSNetTypeP2P                        121
#define RSNetTypeP2PRelay                   122
#define RSNetMsgSendP2PInfoSuccess          123
#define RSNetMsgSendP2PInfoFailed           124
#define RSNetMsgSendInfoSuccess             125
#define RSNetMsgSendInfoFailed              126
#define RSNetMsgAdminIsLogin                150

//RSNetPreview msg
#define RSNetMsgPreviewWaitLogin			200
#define RSNetMsgPreviewOpenStream			201
#define RSNetMsgPreviewOpenStreamSuccess	202
#define RSNetMsgPreviewOpenStreamFail		203
#define RSNetMsgPreviewStreamClosed			204
#define RSNetMsgPreviewDevOffLine           205
#define RSNetMsgPreviewDevOnLine            206  
#define RSNetMsgPreviewCloseVideo           207
#define RSNetMsgPreviewMaxPrevNumErr        208
#define RSNetMsgPreviewNetworkFrameArrive   209
//RSNetDownloadRecord RSNetDownloadRecordStatusCallback.code
#define RSNetMsgDownloadRecordClosed		290 //所有下载结束
#define RSNetMsgDownloadRecordOK			291 //下载完一个文件
#define RSNetMsgDownloadRecordNoFile		292 //一个文件不存在
#define RSNetMsgDownloadRecordFail			293 //该文件下载失败
#define RSNetMsgDownloadRecordStoreFail		294 //该文件存储失败
#define RSNetMsgDownloadRecordPercent		295 //param = percent
//RSNetRecordPlay msg
#define RSNetMsgRecordPlayClosed			300
#define RSNetMsgRecordPlayNoData			301
#define RSNetMsgRecordPlayWaitLogin			302
#define RSNetMsgRecordPlayOpenStream		303
#define RSNetMsgRecordPlayOpenStreamSuccess	304
#define RSNetMsgRecordPlayOpenStreamFail	305
#define RSNetMsgRecordPlayDevicePlayback    306
#define RSNetMsgRecordPlayHDDFormat         307
#define RSNetMsgNoBandWidth                 308
#define RSNetMsgNoPreviewAuth               309
#define RSNetMsgRecordPlayIFrameEnd         309
#define RSNetMsgNoPlaybackAuth              310
#define RSNetMsgIsModifyHdd					311
#define RSNetMsgRecordPlayMutexPlayback     322
#define RSMetMsgPreviewActivateFaile        323
#define RSNetMsgRecordPlayNetworkFrameArrive 324

//RSNetDualtalk msg 
#define RSNetMsgDualtalkClosed				350
#define MsgLockFocusInfo		            356
//RSNetRemoteUpgrade RSNetRemoteUpgradeCallback.code
#define RSNetMsgRemoteUpgradeClosed			390 //升级断开
#define RSNetMsgRemoteUpgradeOK				391 //升级文件传输完成
#define RSNetMsgRemoteUpgradeReadFileFail	392 //读取升级文件失败
#define RSNetMsgRemoteUpgradeInvalidFile	393 //不合法的升级文件
#define RSNetMsgRemoteUpgradePercent		394 //param = percent
#define RSNetMsgRemoteUpgradeVerError		395 //升级文件跟设备不匹配或是版本太低
#define RSNetMsgRemoteUpgrading				396 //设备正在升级
#define RSNetMsgRemoteUpgradeVerSame        397 //升级文件版本和设备版本相同,不需要升级
#define RSNetMsgRemoteUpgradeLanguageError  398
#define RSNetMsgRemoteInUserInterface       399 //本地用户正在操作

#define RSNetMsgFtpIsUpgrade                400 //是否进行FTP升级
#define RSNetMsgFtpUpgrading                401 //升级中状态
#define RSNetMsgRemoteUpgradeIPCPercent     402 //IPC升级状态
#define RSNetMsgSensorRpt					403 //AlarmKit页面Sensor告警

//lparam = UserParam
#define RSNetTestBusy                       801
//////////////////////////////////////////////////////////////////////////
//错误码 RSNetGetLastError
#define RSNetSuccess					0
#define RSNetEDualtalkBusy				0xE1010001
#define RSNetEParam						0xE1010051
#define RSNetENoRight					0xE1010052

//////////////////////////////////////////////////////////////////////////
//设备连接

//RSNetConnectionParam.MotionAlarmRptCallback
typedef void (RSNET_CALL* RSNetAlarmRptCallback)(WORD type, void* data, UINT size, void* userParam);
//connection status callback function
typedef void (RSNET_CALL* RSNetConnectionCallback)(WPARAM wparam, LPARAM lparam);
typedef struct
{
	PCSTR IP;
	UINT Port;
	PCSTR UserName;
	PCSTR Password;
	HWND Wnd;
	UINT Message;
	void* UserParam;
	BOOL AutoReconnect;
	RSNetAlarmRptCallback AlarmRptCallback;
	BOOL AlarmRptDesired;
	RSNetConnectionCallback ConnCallback;
}RSNetConnectionParam;

typedef enum{
	LOGIN_TYPE_IP = 0,
	LOGIN_TYPE_ID,//anlian id and urmet id
	LOGIN_TYPE_TUTK_ID,
	LOGIN_TYPE_LANGTAO_ID,
	LOGIN_TYPE_LOREX_ID,
	LOGIN_TYPE_VVSEE_ID,
	LOGIN_TYPE_SHANGYUN_ID,
	LOGIN_TYPE_RSVV_ID,
	LOGIN_TYPE_HSD,
	LOGIN_TYPE_SHANGYUN_V2_ID,
	LOGIN_TYPE_SAMSUNG_DDNS_ID,
	LOGIN_TYPE_URMET_ID_V2, //urmet id start with ur
	LOGIN_TYPE_LIVEZON_ID,
	LOGIN_TYPE_BAXCOM_ID,		//BSC前缀判断，打开宏P2P_BASCOM
    LOGIN_TYPE_SATVISION_ID, 
	LOGIN_TYPE_LUX_ID, 
	LOGIN_TYPE_LUXVISION_ID, 
	LOGIN_TYPE_RDS_ID,
    LOGIN_TYPE_IMPOWER_TECH_ID,  //银瀑
    LOGIN_TYPE_VV_MAIN,
    LOGIN_TYPE_VV_SUB, 
	LOGIN_TYPE_Q_SEEQRVIEW_ID, 
	LOGIN_TYPE_LIVEZON_V2_ID,
    LOGIN_TYPE_DDNS
}LOGIN_TYPE;

enum {
    NET_NORMAL = 0,
    NET_P2P
};

enum {
    P2P_TYPE_NONE = 0,
    P2P_TYPE_LOREX   = 1,
    P2P_TYPE_LANGTAO,
    P2P_TYPE_TUTK,
    P2P_TYPE_VVSEE,
    P2P_TYPE_SHANGYUN
};

typedef struct
{
    PCSTR IP;
    UINT Port;
    PCSTR UserName;
    PCSTR Password;
    HWND Wnd;
    UINT Message;
    void* UserParam;
    BOOL AutoReconnect;
    RSNetAlarmRptCallback AlarmRptCallback;
    BOOL AlarmRptDesired;
    RSNetConnectionCallback ConnCallback;
    int   nLoginType;//value from LOGIN_TYPE
    PCSTR IDServerName;
	BYTE  language;//gy 12.18 IPC  回传用户选择的语言类型
    BYTE  reserve;
	BYTE  LoginClientType;//1:电商 2:Zip  3:CDoubles 4:Raydin  5:Hello CCTV 6:optimus 7:HDPRO
    BYTE  reserve1;
}RSNetConnectionParamEx;

//Email test  
typedef void (RSNET_CALL* RSRemoteTestCallback)(WORD type, void* data, UINT size, void* userParam);
typedef struct
{
	WORD  type;
	void* data;
	UINT  dataSize;
	void* UserParam;
	RSRemoteTestCallback remoteTestCallback;
	UINT TimeOut;      //超时时间
}RSNetRemoteTestParam;

typedef void* RSNetConnection;
typedef UINT  RSRemoteMsgHandle;
typedef UINT  RSRecordSearch;
typedef UINT  RSPictureSearch;
typedef UINT  RSQueryParamJson;
typedef UINT  RSSetParamJson;
typedef void* RSNetThumbnailsConn;
typedef void* RSNetTimingConn;
//////////////////////////////////////////////////////////////////////////
//预览

//RSNetPreviewParam.Protocol
#define RSNetPreviewTcp		0
#define RSNetPreviewUdp		1

//RSNetPreviewParam.DataCallback
typedef void (RSNET_CALL* RSNetPreviewDataCallback)(void* data, UINT size, void* userParam);
typedef void (RSNET_CALL* RSNetPreviewStatusCallback)(WPARAM wparam, LPARAM lparam);
typedef struct 
{
	PreviewParam Param;
	UINT Protocol; //TCP,UDP
	BOOL AutoReconnect;
	RSNetPreviewDataCallback DataCallback;
	void* UserParam;
    HWND Wnd;
    UINT Message;
    RSNetPreviewStatusCallback StatusCallback;
}RSNetPreviewParam;

typedef void* RSNetPreview;


//////////////////////////////////////////////////////////////////////////
//录像查询

typedef struct {
    char authority_fail;
    char reserve[255];
}QueryStatusCallbackInfo;
typedef void (RSNET_CALL* RSNetQueryRecordStatusCallback)(const QueryStatusCallbackInfo* info, void* user_param);

//RSNetQueryRecordParam.DetailCallback
typedef void (RSNET_CALL* RSNetQueryRecordDetailCallback)(const RecordDetailRsp* rsp, void* userParam);
typedef void (RSNET_CALL* RSNetNewQueryRecordDetailCallback)(const NewRecordDetailRsp* rsp, void* userParam);

//RSNetQueryRecordParam.DayOutlineCallback
typedef void (RSNET_CALL* RSNetQueryRecordDayOutlineCallback)(const RecordDayOutlineRsp* rsp, void* userParam);

typedef struct
{
	UINT Type; //MsgRecordDetail...
	QueryRecordReq Req;
	RSNetQueryRecordDetailCallback DetailCallback;
	RSNetQueryRecordDayOutlineCallback DayOutlineCallback;
	void* userParam;
}RSNetQueryRecordParam;

typedef struct
{
    UINT Type; //MsgRecordDetail...
    QueryRecordReq Req;
    RSNetQueryRecordDetailCallback DetailCallback;
    RSNetQueryRecordDayOutlineCallback DayOutlineCallback;
    void* userParam;
    BYTE StreamType; //0 main; 1 sub; 2 mobile;
    RSNetQueryRecordStatusCallback status_callback;
    BYTE reserve[7];
}RSNetQueryRecordParamEx;

typedef struct
{
    UINT Type; //MsgRecordDetail...
    QueryRecordReq Req;
    RSNetNewQueryRecordDetailCallback DetailCallback;
    RSNetQueryRecordDayOutlineCallback DayOutlineCallback;
    void* userParam;
    BYTE StreamType; //0 main; 1 sub; 2 mobile;
    RSNetQueryRecordStatusCallback status_callback;
    BYTE reserve[7];
}RSNetNewQueryRecordParamEx;

//图片查询或者删除
typedef void (RSNET_CALL* RSNetDelPictureCallback)(int msg, void* userParam);
typedef struct
{
    UINT Type; //MsgQueryJpgDetail or MsgDelJpg
    QueryRecordReq Req;
    RSNetQueryRecordDetailCallback QueryPictureCallback;
    RSNetDelPictureCallback        DelPictureCallback;
    void* userParam;
}RSNetQueryOrDelPictureParam;

//////////////////////////////////////////////////////////////////////////
//录像下载

//RSNetDownloadRecordParam.StatusCallback
typedef void (RSNET_CALL* RSNetDownloadRecordStatusCallback)(UINT code, UINT param, void* userParam);

#ifndef RSFileType
#  define RSFileType	   1 //.264  .rf
#endif
#ifndef RSAVIFileType
#  define RSAVIFileType	   2 //.avi
#endif
#ifndef RSTEKVFileType
#  define RSTEKVFileType   3 //only for tekversion
#endif
#ifndef RSMP4FileType
#  define RSMP4FileType    4 //.mp4
#endif

//RSNetDownloadRecordParam.LocalParam
typedef struct
{
	char FileName[MAX_PATH];
	UINT FileType;
}RSNetDownloadRecordLocalParam;

typedef struct
{
	UINT Channel;
	const RecordDetailRsp* DevRecordFile;
	const RSNetDownloadRecordLocalParam* LocalParam;
	RSNetDownloadRecordStatusCallback StatusCallback;
	void* UserParam;
}RSNetDownloadRecordParam;

typedef void (RSNET_CALL* RSNetDownloadRecordStatusCallbackEx)(UINT code, UINT param, UINT nIndex, void* userParam);

typedef struct 
{
    UINT Channel;
    const RecordDetailRsp* DevRecordFile;
    const RSNetDownloadRecordLocalParam* LocalParam;
    UINT nFileCount;
    BYTE nDownLoadType;//0:Download by file, 1:Download by time
    BYTE StreamType; //0 main; 1: sub; 2 mobile;
    BYTE reserve[2];
    RSNetDownloadRecordStatusCallbackEx StatusCallback;
    void* UserParam;
}RSNetDownloadRecordParamEx;

typedef struct
{
    char FileName[MAX_PATH];
    UINT FileType;
    char password[64];
    char reserve[256];
}RSNetNewDownloadRecordLocalParamEx;

typedef struct {
    UINT Channel;
    const RecordDetailRsp* DevRecordFile;
    const RSNetNewDownloadRecordLocalParamEx* LocalParam;
    UINT nFileCount;
    BYTE nDownLoadType;//0:Download by file, 1:Download by time
    BYTE StreamType; //0 main; 1: sub; 2 mobile;
    BYTE reserve[256];
    RSNetDownloadRecordStatusCallbackEx StatusCallback;
    void* UserParam;
}RSNetNewDownloadRecordParamEx;

typedef void* RSNetDownloadRecord;
typedef void* RSNetDownloadPicture;


//////////////////////////////////////////////////////////////////////////
//录像回放

//RSNetRecordPlayParam.DataCallback
typedef BOOL (RSNET_CALL* RSNetRecordPlayDataCallback)(void* data, UINT size, void* userParam);
typedef void (RSNET_CALL* RSNetRecordStatusCallback)(UINT code, void* userParam);
typedef struct
{
	UINT Channel;
	UINT Type; //NormalRecord...
	DateTime Begin;
	DateTime End;

	RSNetRecordPlayDataCallback DataCallback;
    RSNetRecordStatusCallback   StatusCallback;
	void* UserParam;
	HWND Wnd;
	UINT Message;
}RSNetRecordPlayParam;

typedef struct
{
    UINT Channel;
    UINT Type; //NormalRecord...
    DateTime Begin;
    DateTime End;

    RSNetRecordPlayDataCallback DataCallback;
    RSNetRecordStatusCallback   StatusCallback;
    void* UserParam;
    HWND Wnd;
    UINT Message;
    BYTE StreamType; //0 main; 1 sub; 2 mobile;
    BYTE speed;
    BYTE send_reset_msg;//send reset message as a frame to rsplay
    BYTE reserve[13];
}RSNetRecordPlayParamEx;

typedef void* RSNetRecordPlay;
typedef void* RSNetCaptureIFramePlay;


//////////////////////////////////////////////////////////////////////////
//对讲

//RSNetDualtalkParam.DataCallback
typedef void (RSNET_CALL* RSNetDualtalkDataCallback)(void* data, UINT size, void* userParam);
typedef void (RSNET_CALL* RSNetDualtalkStatusCallback)(int code, void* userParam);

typedef struct
{
	RSNetDualtalkDataCallback DataCallback;
	void* UserParam;
	HWND Wnd;
	UINT Message;
    BYTE UseChannelDualtalk; //是否启用通道对讲,0为设备对讲, 1为通道对讲
    BYTE UseChannelTwoWayTalk; //开启通道对讲的时候是否启用全双工的对讲,0半双工 1全双工
    BYTE UseDeviceAnalogueAudioTalk;//是否使用设备的模拟音频来进行全双工对讲，0不支持, 1支持
    BYTE reserve;
    UINT Channel;//通道对讲对应的通道号0,1,2,3...
    RSNetDualtalkStatusCallback StatusCallback;
    BYTE reserve1[24];
}RSNetDualtalkParam;

typedef void* RSNetDualtalk;


//////////////////////////////////////////////////////////////////////////
//参数配置

//RSNetQueryParamParam.ParamCallback
typedef void (RSNET_CALL* RSNetParamCallback)(void* param, void* userParam);

//RSNetQueryParamParam.ListParamCallback
typedef void (RSNET_CALL* RSNetListParamCallback)(void* listParam, void* userParam); 

typedef struct
{
	UINT ParamType; //类型
	void* Req;
	UINT ParamSize; //参数对应的结构体的大小
	RSNetParamCallback ParamCallback;
	UINT ListParamSize; //参数对应的结构体的大小
	RSNetListParamCallback ListParamCallback;
	void* UserParam;
	UINT TimeOut;      //超时时间
}RSNetQueryParamParam;

typedef struct
{
	UINT ParamMainType; //主消息类型
	UINT ParamSubType; //子消息类型
	void* Req;
	void* Param;
	UINT ReqLen;
	UINT ParamSize; //参数对应的结构体的大小
	RSNetParamCallback ParamCallback;
	UINT ListParamSize; //参数对应的结构体的大小
	RSNetListParamCallback ListParamCallback;
	void* UserParam;
}RSNetQueryTemporaryParamParam;

typedef struct
{
	UINT ParamType; //类型
	void* Req;
	void* Param;
	UINT ParamSize; //参数对应的结构体的大小
	void* ListParam;
	UINT ListParamSize; //参数对应的结构体的大小
	UINT ListParamNum;
	UINT TimeOut;      //超时时间
}RSNetQueryParamParamEx;

typedef struct
{
	UINT ParamType;
	void* Param;
	void* ListParams;
	UINT ListParamNum;
	UINT TimeOut;      //超时时间
}RSNetSetParamParam;

typedef struct
{
	UINT ParamMainType; //主消息类型
	UINT ParamSubType; //子消息类型
	void* Param;
	UINT ParamSize; //参数对应的结构体的大小
	void* ListParams;
	UINT ListParamNum;
	BOOL  bNeedSize; //结构体前要不要大小
}RSNetSetParamParamEx;

//////////////////////////////////////////////////////////////////////////
//远程升级

//RSNetRemoteUpgradeParam.Callback
typedef void (RSNET_CALL* RSNetRemoteUpgradeCallback)(UINT code, void* param, void* userParam);

typedef struct
{
	PCSTR FileName;
	RSNetRemoteUpgradeCallback Callback;
	void* UserParam;
	int filetype;//if it's new upgrade, then set filetype = 3; 
                 //if it's urmet ipc upgrade, then set filetype = 4
                 //if it's raysharp ipc upgrade, then set filetype = 5
                 //if it's 98c upgrade, then set filetype = 6
	             //if it's srp6 upgrade, then set filetype = 7
    UINT nChannelMask;// for ipc
}RSNetRemoteUpgradeParam;

typedef struct
{
    PCSTR FileName;
    RSNetRemoteUpgradeCallback Callback;
    void* UserParam;
    int filetype;//if it's new upgrade, then set filetype = 3; 
                 //if it's urmet ipc upgrade, then set filetype = 4
                 //if it's raysharp ipc upgrade, then set filetype = 5
                 //if it's 98c upgrade, then set filetype = 6
                 //if it's srp6 upgrade, then set filetype = 7
    UINT nChannelMask;// for ipc

    int  time_sleep; //sleep time for p2p, in millisecond, 0 for not sleep
    char reserve[4];
    UINT ChannelMask_EX[8];
    char reserve1[32];
}RSNetRemoteUpgradeParamEx;

typedef void* RSNetRemoteUpgrade;
//////////////////////////////////////////////////////////////////////////
//板端抓图
typedef struct
{
	UINT Channel;
	void* UserParam;
	char FileName[MAX_PATH];
	NET_DVR_JPEGPARA jpgParam;
}RSNetDevCaptureParam;

typedef void* RSNetDeviceCaptureHandle;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//简单命令发送
typedef struct
{
	UINT ParamMainType; //主消息类型
	UINT ParamSubType; //子消息类型
	void* Param;
	UINT ParamSize; //参数对应的结构体的大小
}RSNetCmdParam;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//发送推送相关
typedef struct
{
    PCSTR                   IP;
    UINT                    Port;
    int                     nLoginType;//value from LOGIN_TYPE
    PCSTR                   IDServerName;

    void*                   UserParam;
    RSNetConnectionCallback ConnCallback;

    void*                   SendParam;
    int                     SendParamSize;
    BYTE                    reserve[4];
}RSNetSendParam;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//查询日志
typedef void (RSNET_CALL* RSNetQueryLogCallback)(void* data, UINT size, void* userParam);
typedef struct
{
    LogSearchInput_t *param;
    void* UserParam;
    RSNetQueryLogCallback DataCallback;
}RSNetQueryLogParam;

typedef struct
{
    UINT  ParamMainType; //主消息类型
    UINT  ParamSubType;  //子消息类型
    void* Req;
    UINT  ReqLen;
    void* Param;
    UINT  ParamSize;    //参数对应的结构体的大小
    UINT  TimeOut;      //超时时间
    BYTE  reserve[4];
}RSNetReqParam;

typedef void (RSNET_CALL* RSNetExportBackupCallback)(void* data, UINT size, void* userParam);
typedef struct
{
    void* UserParam;
    RSNetExportBackupCallback DataCallback;
}RSNetExportBackupParam;


/********************************************/
typedef enum THUMBNAILS_DECODE_TYPE_E{
    UNKNOWN_ERROR = 0,
    UNKNOWN_TYPE,
    SAVE_FILE_ERROR,
    NOT_FOUND,
    DECODE_FAILED,
    JPEG_PICTURE,
    PNG_PICTURE,
    I_FRAME
}THUMBNAILS_DECODE_TYPE;
typedef struct {
    ThumbnailRsp*          rsp;
    void*                  frame_head;
    THUMBNAILS_DECODE_TYPE type;
    const char*            file_name;//full name of picture
    char                   reserve[16];
}ThumbnailsDecode;
//attention if info == NULL means over
typedef void (RSNET_CALL* RSNetPlaybackThumbnailsCallback)(ThumbnailsDecode* info, void* user_param);

typedef struct
{
    const NewRecordDetailRsp* list_param;//start of RecordDetailRsp
    int                       list_param_size;//the number of RecordDetailRsp

    RSNetPlaybackThumbnailsCallback callback;
    void*                           user_param;

    const char*             file_directory;
    THUMBNAILS_DECODE_TYPE  picture_type;//JPEG_PICTURE or PNG_PICTURE

    unsigned char           reserve[12];
}RSNetPlaybackThumbnailsParam;
/********************************************/

/********************************************/
typedef struct {
    SnapPicForP2PResp*     rsp;
    THUMBNAILS_DECODE_TYPE type;
    const char*            file_name;//full name of picture
    char                   reserve[16];
}SnapPicRespInfo;
typedef void (RSNET_CALL* RSNetChannelThumbnailsCallback)(SnapPicRespInfo* info, void* user_param);
typedef struct
{
    SnapPicForP2PReq*       list_param;//start of SnapPicForP2PReq
    int                     list_param_size;//the number of SnapPicForP2PReq

    RSNetChannelThumbnailsCallback callback;
    void*                          user_param;

    const char*             file_directory;
    THUMBNAILS_DECODE_TYPE  picture_type;//JPEG_PICTURE or PNG_PICTURE

    unsigned char           reserve[12];
}RSNetChannelThumbnailsParam;
/********************************************/

/********************************************/
typedef void (RSNET_CALL* RSNetTimingCallback)(RSNet_WizardInfo_t* info, void* user_param);
typedef struct {
    RSNetTimingCallback callback;
    void*               user_param;
    RSNet_WizardInfo_t* info;
    unsigned char       reserve[16];
}RSNetTimingParam;
/********************************************/

/********************************************/
typedef struct {
    char main_vv_server_addr[128]; //LOGIN_TYPE_VV_MAIN
    int  main_vv_server_port; //just fill 8000
    char sub_vv_server_addr[128]; //LOGIN_TYPE_VV_SUB
    int  sub_vv_server_port; //just fill 8000
    char reserve[256];
}RSNetP2PServerInfo;
/********************************************/

/********************************************/
/*
RSNetMsgRecordPlayNoData
RSNetMsgRecordPlayIFrameEnd
RSNetMsgRecordPlayDevicePlayback
RSNetMsgRecordPlayHDDFormat
RSNetMsgNoBandWidth
RSNetMsgNoPlaybackAuth
RSNetMsgIsModifyHdd
RSMetMsgPreviewActivateFaile
RSNetMsgRecordPlayClosed
*/

typedef struct {
    void*                  data;
    int                    size;
    THUMBNAILS_DECODE_TYPE type;
    ULONGLONG              time;
    char                   reserve[64];
}RSNetGetPictureInfo;

typedef void (RSNET_CALL* RSNetGetPictureStatusCallback)(int msg, void* user_param);
typedef void (RSNET_CALL* RSNetGetPictureDataCallback)(const RSNetGetPictureInfo* info, void* user_param);

typedef struct {
    const RSNet_GetPicStreamReq_t* req;
    RSNetGetPictureDataCallback    data_callback;
    RSNetGetPictureStatusCallback  status_callback;
    void*                          user_param;
    unsigned char                  reserve[64];
}RSNetGetPictureParam;
typedef void* RSNetGetPicture;
/********************************************/

/********************************************/
typedef struct {
    int  sturct_size;
    int  ack;
    char reserve[64];
}DeleteLogRsp;
/********************************************/

/********************************************/
typedef void (RSNET_CALL* RSNetQueryRecordDetailCallbackEx)(const RecordDetailRsp* rsp, int count, void* userParam);
typedef void (RSNET_CALL* RSNetNewQueryRecordDetailCallbackEx)(const NewRecordDetailRsp* rsp, int count, void* userParam);
typedef void (RSNET_CALL* RSNetQueryRecordDayOutlineCallbackEx)(const RecordDayOutlineRsp* rsp, int count, void* userParam);
typedef struct {
    UINT                                 channel[8];  //1 2 4 8 
    UINT                                 record_type;
    char                                 stream_type; //0 main 1 sub 2 mobile
    char                                 reserve[6];
    char                                 enable_smart_search;
    UINT                                 smart_region[18];
    DateTime                             begin_time;
    DateTime                             end_time;
    RSNetQueryRecordDayOutlineCallback   month_search_callback;
    void*                                user_param;
    RSNetQueryRecordDayOutlineCallbackEx month_search_callback_ex;
    RSNetQueryRecordStatusCallback       status_callback;
    char                                 reserve1[240];
}RSNetQueryRecordFileByMonthParam;

typedef struct {
    UINT                                channel;     //0 1 2 3 4 5 6
    UINT                                record_type;
    char                                stream_type; //0 main 1 sub 2 mobile
    char                                reserve[6];
    char                                enable_smart_search;
    UINT                                smart_region[18];
    DateTime                            begin_time;
    DateTime                            end_time;
    int                                 union_flag;
    union {
        RSNetQueryRecordDetailCallback      day_search_callback;     //union_flag = 1;
        RSNetNewQueryRecordDetailCallback   new_day_search_callback; //union_flag = 2;
        RSNetQueryRecordDetailCallbackEx    day_search_callback_ex;     //union_flag = 3;
        RSNetNewQueryRecordDetailCallbackEx new_day_search_callback_ex; //union_flag = 4;
    };
    void*                               user_param;
    RSNetQueryRecordStatusCallback      status_callback;
    char                                reserve1[248];
}RSNetQueryRecordFileByDayParam;

typedef struct {
    char file_name[256];
    char reserve[256];
}RSNetDownloadFileInfo;

typedef struct {
    UINT                                channel;     //0 1 2 3 4 5 6
    char                                stream_type; //0 main 1 sub 2 mobile
    char                                reserve[3];
    int                                 union_flag;
    union {
        const RecordDetailRsp*          rsp;     //union_flag = 1;
        const NewRecordDetailRsp*       rspnew;  //union_flag = 2;
    };
    const RSNetDownloadFileInfo*        file_info;
    int                                 file_count;
    RSNetDownloadRecordStatusCallbackEx status_callback;
    void*                               user_param;
    int                                 max_single_file_size;//MB
    const backupspecialinfo_t*          backup_info;
    char                                reserve1[244];
}RSNetDownloadByFileParam;

typedef struct {
    UINT                                channel;     //0 1 2 3 4 5 6
    UINT                                record_type;
    char                                stream_type; //0 main 1 sub 2 mobile
    char                                reserve[7];
    DateTime                            begin_time;
    DateTime                            end_time;
    char                                file_name[256];
	int                                 file_count;
	ULONGLONG                           file_total_size;
    RSNetDownloadRecordStatusCallbackEx status_callback;
    void*                               user_param;
    int                                 max_single_file_size;//MB
    const backupspecialinfo_t*          backup_info;
    char                                reserve1[244];
}RSNetDownloadByTimeParam;
typedef void* RSNetDownloadFile;
/********************************************/

/********************************************/
typedef struct _RSNetLogParam_{
    char  log_path[256];//log file path
    char  gEnableNetErr;
    char  gEnableBroadcastStatus;
    char  gEnableConnStatus;
    char  gEnableLoginStatus;
    char  gEnableMsgStatus;
    char  gEnablePreviewStatus;
    char  gEnableFrameData;
    char  gEnableRecordPlayStatus;
    char  gEnableDualtalkStatus;
    char  gEnableDownloadRecordStatus;
    char  gEnableRemoteUpgradeStatus;
    char  gEnableRemoteParamImportStatus;
    char  gEnableP2PStatus;
    char  reserve[64];
    const char* log_directory; //log file directory
    char  reserve1[184];
}RSNetLogParam;
/********************************************/

/********************************************/
typedef struct _P2PTunnelInfo_{
    int  struct_size;
    int  p2p_mapping_port;
    char reserve[128];
}P2PTunnelInfo;
/********************************************/

/********************************************/
typedef void (RSNET_CALL* RSNetQueryParamJsonCallback)(const char* param, int size, void* user_param);
typedef void (RSNET_CALL* RSNetSetParamJsonCallback)(int status, const char* param, int size, void* user_param);

typedef struct {
	UINT                        main_msg_type;
	const char*                 param;
	int							param_size;
	RSNetQueryParamJsonCallback callback;
	void*                       user_param;
    char                        erase_after_callback;
	char                        reserve[255];
}QueryParamJsonInfo;

typedef struct {
	UINT                        main_msg_type;
	const char*                 param;
	int                         param_size;
	RSNetSetParamJsonCallback   callback;
	void*                       user_param;
    char                        erase_after_callback;
    char                        reserve[247];
}SetParamJsonInfo;
/********************************************/

/********************************************/
typedef struct
{
    BYTE ReportType;
    BYTE Version;
    BYTE Reserved[2];
} RSReportHeadOut;

typedef void (RSNET_CALL* RSNetAlarmRequestInfoDataCallback)(const char* data, int size, const RSReportHeadOut* report_head, void* user_param);
typedef void (RSNET_CALL* RSNetAlarmParamInfoDataCallback)(const char* param, int size, void* user_param);
typedef void (RSNET_CALL* RSNetAlarmRequestStatusCallback)(WPARAM wparam/*uint32_t msg*/, LPARAM lparam/*void* user_param*/);
typedef struct {
    RSNetAlarmRequestInfoDataCallback data_callback;
    RSNetAlarmRequestStatusCallback   status_callback;
    void*                             user_param;
    char                              reserve[256];
}AlarmRequestInfo;
typedef void* RSAlarmRequestHandle;

typedef struct {
    RSNetAlarmParamInfoDataCallback data_callback;
    RSNetAlarmRequestStatusCallback status_callback;
    void*                           user_param;
    char                            reserve[256];
}AlarmParamInfo;

typedef struct {
    const char* param;
    int         param_size;
    char        reserve[256];
}AlarmParamJson;

typedef void* RSAlarmParamHandle;
/********************************************/

#ifdef __cplusplus
extern "C" {
#endif

RSNET_API BOOL RSNET_CALL RSNetInit();
RSNET_API void RSNET_CALL RSNetRelease();

RSNET_API UINT RSNET_CALL RSNetGetLastError();

RSNET_API void RSNET_CALL RSNetSetEncription(BOOL bEncription);

//搜索设备
RSNET_API void RSNET_CALL RSNetSearchDev(const RSNetSearchDevParam* param);

//设置设备IP信息
RSNET_API BOOL RSNET_CALL RSNetSetDevInfo(const NetMDevInfoReq* param);
RSNET_API BOOL RSNET_CALL RSNetSetNewDevInfo(const NewNetMDevInfoReq* param);

//Http请求
RSNET_API void RSNET_CALL RSNetHttpReqDev(RSNetHttpReqGeneral* param);
RSNET_API RSNetIDConnection RSNET_CALL RSNetHttpReqDevStart(RSNetHttpReqEx* param);
RSNET_API void RSNET_CALL RSNetHttpReqDevStop(RSNetIDConnection* conn);

//设备连接
RSNET_API RSNetConnection RSNET_CALL RSNetConnectionStart(const RSNetConnectionParam* param);
RSNET_API RSNetConnection RSNET_CALL RSNetConnectionStartEx(const RSNetConnectionParamEx* param);
RSNET_API void RSNET_CALL RSNetConnectionStop(RSNetConnection* conn);
RSNET_API BOOL RSNET_CALL RSNetSetIPAndPort(RSNetConnection* conn,PCSTR strIP,UINT Port);

RSNET_API BOOL RSNET_CALL RSNetGetDevInfo(RSNetConnection conn, LoginRsp* info, UINT infoSize/*=sizeof(LoginRsp)*/);
RSNET_API BOOL RSNET_CALL RSNetGetDevInfoEx(RSNetConnection conn, void* info, UINT infoSize/*=sizeof(LoginRsp)*/);
//预览
RSNET_API RSNetPreview RSNET_CALL RSNetStartPreview(RSNetConnection conn, const RSNetPreviewParam* param);
RSNET_API void RSNET_CALL RSNetStopPreview(RSNetConnection conn, RSNetPreview* preview);
RSNET_API ULONGLONG RSNET_CALL RSNetGetPreviewBitRate(RSNetConnection conn, RSNetPreview preview);
RSNET_API BOOL  RSNET_CALL RSNetForceIFrame(RSNetConnection conn,BYTE channel,BYTE codeStreamType );//Force I frame

//云台控制 type=MsgPTZUp...
RSNET_API BOOL RSNET_CALL RSNetPTZControl(RSNetConnection conn, UINT type, PTZControlReq* req);

//Email,ddns,Remote reboot Test
RSNET_API BOOL RSNET_CALL RSNetRemoteTest(RSNetConnection conn, const RSNetRemoteTestParam* param);
RSNET_API RSRemoteMsgHandle RSNET_CALL RSNetRemoteTestEx(RSNetConnection conn, const RSNetRemoteTestParam* param);
RSNET_API void RSNET_CALL RSNetRemoteTestStopEx(RSNetConnection conn, const RSNetRemoteTestParam* param, RSRemoteMsgHandle  handle);

//录像查询
RSNET_API BOOL RSNET_CALL RSNetQueryRecord(RSNetConnection conn, const RSNetQueryRecordParam* param);
RSNET_API RSRecordSearch RSNET_CALL RSNetAsyncQueryRecord(RSNetConnection conn, const RSNetQueryRecordParam* param);
RSNET_API BOOL RSNET_CALL RSNetQueryRecordEx(RSNetConnection conn, const RSNetQueryRecordParamEx* param);
RSNET_API RSRecordSearch RSNET_CALL RSNetAsyncQueryRecordEx(RSNetConnection conn, const RSNetQueryRecordParamEx* param);
RSNET_API void RSNET_CALL RSNetAsyncQueryRecordStop(RSNetConnection conn, RSRecordSearch  handle);

//设备抓图
RSNET_API BOOL RSNET_CALL RSNetCapture(RSNetConnection conn, const RSNetDevCaptureParam* param);
//录像下载
RSNET_API RSNetDownloadRecord RSNET_CALL RSNetStartDownloadRecord(RSNetConnection conn, const RSNetDownloadRecordParam* param);
RSNET_API RSNetDownloadRecord RSNET_CALL RSNetStartDownloadRecordEx(RSNetConnection conn, const RSNetDownloadRecordParamEx* param);
RSNET_API void RSNET_CALL RSNetStopDownloadRecord(RSNetDownloadRecord* downloadRecord);
//录像回放
RSNET_API RSNetRecordPlay RSNET_CALL RSNetStartRecordPlay(RSNetConnection conn, const RSNetRecordPlayParam* param);
RSNET_API RSNetRecordPlay RSNET_CALL RSNetStartRecordPlayEx(RSNetConnection conn, const RSNetRecordPlayParamEx* param);
RSNET_API void RSNET_CALL RSNetStopRecordPlay(RSNetRecordPlay* recordPlay);
RSNET_API void RSNET_CALL RSNetReqRecordData(RSNetRecordPlay recordPlay);
RSNET_API void RSNET_CALL RSNetReposRecordData(RSNetRecordPlay recordPlay, const ReposRecordDataReq* req);
RSNET_API void RSNET_CALL RSNetReplayRecordData(RSNetRecordPlay recordPlay);
RSNET_API void RSNET_CALL RSNetReqRecordPlayCtrol(RSNetRecordPlay recordPlay, WORD msgSubtype);

//对讲
//如果RSNetStartDualtalk返回NULL, 可以调用RSNetGetLastError获取失败原因
RSNET_API RSNetDualtalk RSNET_CALL RSNetStartDualtalk(RSNetConnection conn, const RSNetDualtalkParam* param);
RSNET_API void RSNET_CALL RSNetStopDualtalk(RSNetDualtalk* dualtalk);
RSNET_API void RSNET_CALL RSNetSendDualtalkData(RSNetDualtalk dualtalk, void* data, UINT size);

//参数配置
RSNET_API BOOL RSNET_CALL RSNetQueryParam(RSNetConnection conn, const RSNetQueryParamParam* param);
RSNET_API BOOL RSNET_CALL RSNetQueryParamEx(RSNetConnection conn, const RSNetQueryParamParamEx* param);
RSNET_API BOOL RSNET_CALL RSNetQueryDefaultParam(RSNetConnection conn, const RSNetQueryParamParam* param, UINT nMainMsgType/* = MsgDefaultParam*/);
RSNET_API BOOL RSNET_CALL RSNetQueryDefaultParamEx(RSNetConnection conn, const RSNetQueryParamParamEx* param, UINT nMainMsgType/* = MsgDefaultParam*/);
RSNET_API BOOL RSNET_CALL RSNetQueryTemporaryParam(RSNetConnection conn, const RSNetQueryTemporaryParamParam* param);
RSNET_API BOOL RSNET_CALL RSNetSetParam(RSNetConnection conn, const RSNetSetParamParam* param);
RSNET_API BOOL RSNET_CALL RSNetSetParamEx(RSNetConnection conn, const RSNetSetParamParamEx* param);

//远程升级
RSNET_API RSNetRemoteUpgrade RSNET_CALL RSNetStartRemoteUpgrade(RSNetConnection conn, const RSNetRemoteUpgradeParam* param);
RSNET_API void RSNET_CALL RSNetStopRemoteUpgrade(RSNetRemoteUpgrade* remoteUpgrade);


//告警订阅
RSNET_API void RSNET_CALL RSNetAlarmSubscribe(RSNetConnection conn, BOOL desired);

//简单信令发送
RSNET_API void RSNET_CALL RSNetSimpleCmd(RSNetConnection conn,RSNetCmdParam *param);

//查询日志 阻塞的
RSNET_API BOOL RSNET_CALL RSNetQueryLog(RSNetConnection conn,RSNetQueryLogParam *param);

//Req查询与设置
RSNET_API BOOL RSNET_CALL RSNetReqControl(RSNetConnection conn, RSNetReqParam* param);

//导出配置文件 阻塞的
RSNET_API BOOL RSNET_CALL RSNetExportBackup(RSNetConnection conn,RSNetExportBackupParam *param);

//导入参数配置文件
RSNET_API BOOL RSNET_CALL RSNetRemoteParamImport(RSNetConnection conn, const RemoteBackupResp_t* param);

//新的导入导出文件->更换了结构体和消息
//导入
RSNET_API BOOL RSNET_CALL RSNetRemoteParamImportNew(RSNetConnection conn, const RemoteNewParamBackupResp_t* param);
//导出
RSNET_API BOOL RSNET_CALL RSNetExportBackupNew(RSNetConnection conn, const RSNetExportBackupParam* param);

//发送推送相关接口
RSNET_API RSNetConnection RSNET_CALL RSNetStartSendPushParam(RSNetSendParam *param);
RSNET_API void RSNET_CALL RSNetStopSendPushParam(RSNetConnection *conn);

//I帧回放抓图 KG
RSNET_API RSNetCaptureIFramePlay RSNET_CALL RSNetStartCaptureIFrame(RSNetConnection conn, const RSNetRecordPlayParam* param);
RSNET_API void RSNET_CALL RSNetStopCaptureIFrame(RSNetCaptureIFramePlay* captureIFrame);
RSNET_API void RSNET_CALL RSNetReposIFrameData(RSNetCaptureIFramePlay captureIFrame, const ReposRecordDataReq* req);
RSNET_API void RSNET_CALL RSNetReplayIFrameData(RSNetCaptureIFramePlay captureIFrame);

//回放查询或者删除图片 KG
RSNET_API RSPictureSearch RSNET_CALL RSNetQueryOrDelPicture(RSNetConnection conn, const RSNetQueryOrDelPictureParam* param);
RSNET_API void RSNET_CALL RSNetQueryOrDelPictureStop(RSNetConnection conn, RSPictureSearch  handle);

//回放图片下载 KG
RSNET_API RSNetDownloadPicture RSNET_CALL RSNetStartDownloadPictureEx(RSNetConnection conn, const RSNetDownloadRecordParamEx* param);
RSNET_API void RSNET_CALL RSNetStopDownloadPicture(RSNetDownloadPicture* downloadPicture);

//only for mac lorex p2p
RSNET_API void RSNET_CALL RSNetInitLX2PPath(const char* path);

RSNET_API RSNetConnection RSNET_CALL RSNetStartSavePasword(RSNetSendParam *param);
RSNET_API void RSNET_CALL RSNetStopSavePasword(RSNetConnection *conn);

//query playback record
RSNET_API BOOL RSNET_CALL RSNetNewQueryRecordEx(RSNetConnection conn, const RSNetNewQueryRecordParamEx* param);

//playback thumbnails
RSNET_API RSNetThumbnailsConn RSNET_CALL RSNetStartGetPlaybackThumbnails(RSNetConnection conn, const RSNetPlaybackThumbnailsParam* param);
RSNET_API void RSNET_CALL RSNetStopGetPlaybackThumbnails(RSNetThumbnailsConn* thumbnailsConn);

//channel picture
RSNET_API RSNetThumbnailsConn RSNET_CALL RSNetStartGetChannelThumbnails(RSNetConnection conn, const RSNetChannelThumbnailsParam* param);
RSNET_API void RSNET_CALL RSNetStopGetChannelThumbnails(RSNetThumbnailsConn* thumbnailsConn);

//timing
RSNET_API RSNetTimingConn RSNET_CALL RSNetStartTiming(RSNetConnection conn, const RSNetTimingParam* param);
RSNET_API void RSNET_CALL RSNetStopTiming(RSNetTimingConn* timingConn);

//set device info in lan
RSNET_API BOOL RSNET_CALL RSNetSetNewDevInfoEx(const RsNetSearchDevReq_t* param);

//新的升级方式，针对p2p模式在内网以及外网传输速度过快而板端还未收到所有的数据就断开链路的问题
RSNET_API RSNetRemoteUpgrade RSNET_CALL RSNetStartRemoteUpgradeEx(RSNetConnection conn, const RSNetRemoteUpgradeParamEx* param);

RSNET_API RSNetDeviceCaptureHandle RSNET_CALL RSNetAsyncCapture(RSNetConnection conn, const RSNetDevCaptureParam* param);
RSNET_API void RSNET_CALL RSNetStopCapture(RSNetDeviceCaptureHandle* handle);

//录像下载 需要传密码或者默认空密码进去
RSNET_API RSNetDownloadRecord RSNET_CALL RSNetStartNewDownloadRecordEx(RSNetConnection conn, const RSNetNewDownloadRecordParamEx* param);

//录像回放向板端发送倒帧播放消息，和定位功能类似，只是发送消息后收到的数据帧是倒叙的
RSNET_API void RSNET_CALL RSNetReverseRecordData(RSNetRecordPlay recordPlay, const ReposRecordDataReq* req, PlaySpeedCtrl speed);

RSNET_API void RSNET_CALL RSNetInitP2PServerInfo(const RSNetP2PServerInfo* param);

RSNET_API RSNetGetPicture RSNET_CALL RSNetStartGetPicture(RSNetConnection conn, const RSNetGetPictureParam* param);
RSNET_API void RSNET_CALL RSNetStopGetPicture(RSNetGetPicture* picture_instance);

RSNET_API BOOL RSNET_CALL RSNetSyncQueryRecordFileByMonth(RSNetConnection conn, const RSNetQueryRecordFileByMonthParam* param);
RSNET_API BOOL RSNET_CALL RSNetSyncQueryRecordFileByDay(RSNetConnection conn, const RSNetQueryRecordFileByDayParam* param);

RSNET_API RSRecordSearch RSNET_CALL RSNetAsyncQueryRecordFileByMonth(RSNetConnection conn, const RSNetQueryRecordFileByMonthParam* param);
RSNET_API RSRecordSearch RSNET_CALL RSNetAsyncQueryRecordFileByDay(RSNetConnection conn, const RSNetQueryRecordFileByDayParam* param);
RSNET_API void RSNET_CALL RSNetAsyncQueryRecordFileStop(RSNetConnection conn, RSRecordSearch handle);

RSNET_API RSNetDownloadFile RSNET_CALL RSNetStartDownloadByFile(RSNetConnection conn, const RSNetDownloadByFileParam* param);
RSNET_API RSNetDownloadFile RSNET_CALL RSNetStartDownloadByTime(RSNetConnection conn, const RSNetDownloadByTimeParam* param);
RSNET_API void RSNET_CALL RSNetStopDownloadFile(RSNetDownloadFile* instance);

RSNET_API void RSNET_CALL RSNetInitLog(const RSNetLogParam* param);

RSNET_API void RSNET_CALL RSNetSearchDevPoint2Point(const RSNetSearchDevParamPoint2Point* param);

RSNET_API BOOL RSNET_CALL RSNetQueryParamJson(RSNetConnection conn, const QueryParamJsonInfo* param);
RSNET_API BOOL RSNET_CALL RSNetSetParamJson(RSNetConnection conn, const SetParamJsonInfo* param);

RSNET_API void RSNET_CALL RSNetP2PEnterBackgroundDestroy();

RSNET_API RSAlarmRequestHandle RSNET_CALL RSNetStartAlarmRequestInfo(RSNetConnection conn, const AlarmRequestInfo* info);
RSNET_API void RSNET_CALL RSNetStopAlarmRequestInfo(RSAlarmRequestHandle* handle);

RSNET_API RSAlarmParamHandle RSNET_CALL RSNetStartAlarmParamInfo(RSNetConnection conn, const AlarmParamInfo* info);
RSNET_API void RSNET_CALL RSNetSendAlarmParamJson(RSAlarmParamHandle handle, const AlarmParamJson* info);
RSNET_API void RSNET_CALL RSNetStopAlarmParamInfo(RSAlarmParamHandle* handle);

RSNET_API void RSNET_CALL RSNetResetConnection(RSNetConnection conn);

RSNET_API RSQueryParamJson RSNET_CALL RSNetAsyncStartQueryParamJson(RSNetConnection conn, const QueryParamJsonInfo* param);
RSNET_API void RSNET_CALL RSNetAsyncStopQueryParamJson(RSNetConnection conn, RSQueryParamJson handle);

RSNET_API RSSetParamJson RSNET_CALL RSNetAsyncStartSetParamJson(RSNetConnection conn, const SetParamJsonInfo* param);
RSNET_API void RSNET_CALL RSNetAsyncStopSetParamJson(RSNetConnection conn, RSSetParamJson handle);

#ifdef __cplusplus
}
#endif


#endif
