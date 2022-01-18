#ifndef __RSPLAY_H__
#define __RSPLAY_H__

#include "RSTypedef.h"
#include "common_type.h"
#include "correction_type.h"

#ifdef _MSC_VER
#  ifdef RSPLAY_EXPORTS
#    define RSPLAY_API __declspec(dllexport)
#  else
#    define RSPLAY_API __declspec(dllimport)
#  endif
#  define RSPLAY_CALL __stdcall
#else
#  define RSPLAY_API
#  define RSPLAY_CALL
#endif


//播放控制
#define PLAY_MODE_NORMAL			0x0001
#define PLAY_MODE_STOP				0x0002
#define PLAY_MODE_PAUSE				0x0003
#define PLAY_MODE_SLOW				0x0004
#define PLAY_MODE_SLOW4				0x0005	
#define PLAY_MODE_SLOW8				0x0006
#define PLAY_MODE_SLOW16			0x0007	
#define PLAY_MODE_FAST_FORWARD2		0x0010
#define PLAY_MODE_FAST_FORWARD4		0x0011
#define PLAY_MODE_FAST_FORWARD8		0x0012
#define PLAY_MODE_FAST_FORWARD16	0x0013
#define PLAY_MODE_FAST_FORWARD32	0x0014
#define PLAY_MODE_SINGLE_FRAME		0x0030
#define PLAY_MODE_NO_RIGHT          0x0031
#define PLAY_MODE_REVERSE           0x0032

//audio setting
#define BIT_PER_SAMPLE				16
#define PLAY_AUDIO_SAMPLE_POOR		8000
#define HI3510_TALK_DARABLOCK_SIZE	80
	
typedef struct{ 
	long nWidth; // 画面宽，单位为像素，如果是音频数据则为0
	long nHeight; // 画面高，单位为像素，如果是音频数据则为0
	long nStamp; // 时标信息，单位毫秒
	long nType; //数据类型
	long nFrameRate;// 编码时产生的图像帧率
}FRAME_INFO;

typedef struct{
    void* qImagebuf;
	void* qImageEvent;
}ImageHandle;

enum{
	IMAGE_RGB32 = 16,
	IMAGE_CAPTURE= 32,
	NSysPlay_PLAY = 64,
    SysPlay_PLAY = 128,
    Local_PLAY = 256
};

typedef struct {
    char reserve[128];
}SDKWRAPPER_DRAW_INFO;

typedef struct {
    char* data;
    int   data_length;
    unsigned long long frame_time;
    char  reserve[120];
}PICTURE_RENDER_INFO;

typedef int (CALLBACK *DECODE_CALLBACK) (char *pData, long lSize, FRAME_INFO *pInfo, void* dwUser); 
typedef ImageHandle* (CALLBACK *IMAGEINFO_CALLBACK)(int nWidth,int nHeight,void* dwObject);
typedef void (CALLBACK* DRAW_FUN_CALLBACK) (HDC hDC, DWORD with, DWORD height, void* pUser, DWORD left, DWORD top);
typedef int (CALLBACK* DUAL_SPEAK_CALLBACK)(int size, const char* data, void* dwUser);
typedef void (CALLBACK *IMAGEEVENT_CALLBACK)(void* qImageEvent,UINT ImageType,char*mfName, void* dwUser);
typedef void (CALLBACK *IMAGEFILE_CALLBACK)(UINT ImageType,int nWidth,int nHeight,long lSize,UCHAR* buf,char*mfName, void* dwUser);
typedef void (CALLBACK* CAPTURE_PICTURE_CALLBACK)(void* data, int size, ULONGLONG time, void* pUser);
typedef int  (CALLBACK* BEFORE_RENDER_CALLBACK)(void* data, void* user_param);
typedef void (CALLBACK* SDKWRAPPER_DRAW_CALLBACK) (SDKWRAPPER_DRAW_INFO* info, void* user_param);
typedef void (CALLBACK* PICTURE_RENDER_CALLBACK)(PICTURE_RENDER_INFO* info, void* user_param);

typedef struct {
	IMAGEINFO_CALLBACK ImageSizeCallback;
	IMAGEEVENT_CALLBACK ImageEventCallback;
	UINT ImageType;
	void* dwUser;
	void* pObject;
}IMAGE_INFO;

typedef struct {
	IMAGEFILE_CALLBACK ImageEventCallback;
	const char *recordfile_name;
	const char *pic_name;
	UINT fileType;
	UINT ImageType;
	void* dwUser;
    UINT recordMode;
}RSFILE_INFO;

typedef struct {
	const char *recordfile_name;
	const char *pic_name;
}RSFILE_INFOEx;

typedef struct {
    const char*                file_name;
    const char*                picture_name;
    int                        max_single_file_size;//MB
    const backupspecialinfo_t* backup_info;
    char                       reserve[248];
}RSFILE_INFO_EX;

//音量
#define VOLUM_MIN	0
#define VOLUM_MAX	100

//播放类型
#define PLAY_UNKNOW_TYPE     -1     //no file
#define PLAY_LOCALFILE_TYPE   0     //local file
#define PLAY_NETFILE_TYPE     1     //net file
#define PLAY_NETSTREAM_TYPE   2     //net stream
#define PLAY_DUALTALK_TYPE	  3	    //dual talk
#define PLAY_SYNC_TYPE		  4     //sync play
#define PLAY_CAL_SOUND_DB     5     //calculate audio db
#define PLAY_ONLY_DECODE_TYPE 6     //only decode function
#define PLAY_LOCAL_THUMBNAIL  7     //local file thumbnail

//声音控制类型
#define DST_SPEAKERS		0	//主音量  
#define SRC_WAVEOUT			1   //波形
#define SRC_SYNTHESIZER		2	//软件合成器
#define SRC_COMPACTDISC     3	//CD音量
#define SRC_MICROPHONE		4   //麦克风

#  define MAX_SET_OSD_NUM		36	//最多可设置OSD的数目

typedef struct __osd_info_t
{
	char font[24];
	int font_width;
	int font_height;
	unsigned char osd_color_red;		//0-255
	unsigned char osd_color_green;		//0-255
	unsigned char osd_color_blue;		//0-255
	RECT osd_rect;

	char osd_string[128];
}osd_info_t;

typedef struct{
	int iRate;
	int iWidth;
	int iFormat;//0x24 g726_16_asf, 0x25 g726_24_asf, 0x26 g726_32_asf, 0x27 g726_40_asf
	int iAmr_mode;//0 means "full duplex" or "old mode" or "analogue audio", 1 means "half duplex"
	int iAmr_format;
}AudioTalkConfig_t;

typedef struct {
    DUAL_SPEAK_CALLBACK AudioCaptureCallback;
    void* dwUser;
}AUDIO_CAPTURE_CALLBACK_INFO;

typedef struct {
    char		sFilePath[MAX_PATH];
    ULONGLONG	nBeginTime;
    ULONGLONG	nEndTime;
    ULONGLONG	nBeginPos;
    ULONGLONG    nEndPos;
    char        password[64];
    char        reserve[256];
}PlayFileListInfo;

typedef struct {
    PlayFileListInfo* info;
    int               count; // count of PlayFileListInfo
    char              reserve[256];
}RSPlayNewOpenPlayFileListExParam;

typedef struct {
    char      file_name[256];  //in
    ULONGLONG begin_time;      //out
    ULONGLONG end_time;        //out
    int       key_frame_count; //out
    int       channel;           //0  1  2  3  4...   
    char      mac_addr[32];      //"00-11-22-33-44-55"
    char      serial_number[32]; //"raysharp"
    char      device_type[32];   //"raysahrp"
    char      reserve[920];
}RSPlayGetFileInfoParam;

typedef struct {
    float r; //from 0~1
    float g; //from 0~1
    float b; //from 0~1
}rs_color;

typedef struct {
    float x1; //from 0~1, 0 means left or top, 1 means right or bottom
    float y1; //from 0~1, 0 means left or top, 1 means right or bottom
    float x2; //from 0~1, 0 means left or top, 1 means right or bottom
    float y2; //from 0~1, 0 means left or top, 1 means right or bottom
}rs_rect;

typedef struct {
    PICTURE_RENDER_CALLBACK cb;
    void*                   user_param;
    const char*             base64_bmp_picture;
    int                     base64_bmp_picture_size;
    char                    reserve[244];
}PictureCallbackParam;

//RSPlaySetCallbackMessage message wparam
#define NET_FILE_DATA_NOT_ENOUGH	1
#define FILE_PLAY_END				11
#define CREATE_DECODE_FAILED        21
#define FILE_CREATE_FAILED          31
#define FILE_WRITE_FAILED           32
#define DEL_FROM_SYNC               33
//lparm = userParam

//record
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

enum {
	YUV_444 = 1,
	YUV_422,
	YUV_420,
	YUV_411,
	RGB_565,
	RGB_555,
	RGB_24,
	RGB_32,
	ADPCM,
	IMAGE_INIT = 512
};

enum{
    DEV_TYPE_RSNEW = 0,
    DEV_TYPE_HK,
    DEV_TYPE_RSOLD
};

enum{
    DRAW_TYPE_DDRAW =0,
    DRAW_TYPE_D2D1
};

enum {
    APP_UNKNOWN = 0,
    /*
    *此宏定义和APP_UNKNOWN的区别主要如下
    *1.关闭了264和265的多线程解码，注：多线程的解码只有在1080p的时候才会开启
    *2.关闭了如果40ms没有帧数据渲染主动调用上一次解码的数据渲染
    *3.调整解码后的缓冲区为1，默认为4
    *4.调整预缓存帧的缓冲区为150，默认为250
    *5.关闭利用显卡将yuv420转换为rgb的功能，因为在部分测试电脑反馈此功能会导致花屏
    */
    APP_QT_CMS,
    APP_BROWER_PLUGIN,
    APP_MOBILE,
    APP_SDK_WRAPPER
};

typedef enum _RSPLAY_FLAG_{
    //1 2 4 8...
    LACK_RESOURCE_FLAG = 1,
}RSPLAY_FLAG;

typedef enum {
    rs_mouse_unknown = -1,
    rs_mouse_move = 0,
    rs_mouse_wheel,
    rs_mouse_down,
    rs_mouse_up,
    rs_mouse_double_click
}rs_mouse_event;

#ifndef _WIN64
typedef unsigned long RSPlayHandle;
#else
typedef void*         RSPlayHandle;
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (CALLBACK* PLAY_FUN_CALLBACK)(UINT message, void* userParam);
typedef void (CALLBACK* CROSS_DAY_CALLBACK)(UINT message, void* userParam);
typedef void (CALLBACK* PLAY_DATA_CALLBACK)(const char* data, const UINT width, const UINT height, void* userParam);
typedef void (CALLBACK* CAPTURE_CALLBACK)(BYTE* data, UINT size, int type, void* pUuser);
RSPLAY_API int RSPLAY_CALL RSPlayInitPlayLib(int nAppType/* = APP_UNKNOWN*/, int nDrawType/* = DRAW_TYPE_DDRAW*/, const char* strPath/* = NULL*/);
RSPLAY_API int RSPLAY_CALL RSPlayDeinitPlayLib(void);

RSPLAY_API RSPlayHandle RSPLAY_CALL RSPlayCreatePlayInstance(int play_type); 
RSPLAY_API int RSPLAY_CALL RSPlayDestroyPlayInstance(RSPlayHandle player_id);

RSPLAY_API int RSPLAY_CALL RSPlaySetCallbackMessage(RSPlayHandle player_id, HWND hwnd, UINT message, void* userParam); //NET_FILE_DATA_NOT_ENOUGH...

RSPLAY_API int RSPLAY_CALL RSPlaySetCallbackMessageEx(RSPlayHandle player_id, PLAY_FUN_CALLBACK callback, void* userParam);

//跨天的回调函数
RSPLAY_API int RSPLAY_CALL RSPlaySetCrossDayCallbackMessageEx(RSPlayHandle player_id, CROSS_DAY_CALLBACK callback, void* userParam);

RSPLAY_API int RSPLAY_CALL RSPlayAddSyncPlayInstance(RSPlayHandle sync_play, RSPlayHandle player_id);

RSPLAY_API int RSPLAY_CALL RSPlaySetNetPlayBufNum(RSPlayHandle player_id, int num);
//添加一个播放窗口到指定的播放实例中，用于一次解码多窗口渲染的模式下
RSPLAY_API int RSPLAY_CALL RSPlaySetPlayWnd(RSPlayHandle player_id, HWND hwnd);
//从指定的播放实例中删除一个播放窗口，用于一次解码多窗口渲染的模式下
RSPLAY_API int RSPLAY_CALL RSPlayDelPlayWnd(RSPlayHandle player_id, HWND hwnd);

RSPLAY_API int RSPLAY_CALL RSPlaySetPlayPicSize(RSPlayHandle player_id, int width, int height);
RSPLAY_API int RSPLAY_CALL RSPlayGetNetPlayBufNum(RSPlayHandle player_id);
RSPLAY_API HWND RSPLAY_CALL RSPlayGetPlayWnd(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlayGetPlayPicSize(RSPlayHandle player_id, int *width, int *height);

//0: success   -1:unknown error   -2:file not exist   -3:file access permission denied   -4:password error, need input password
RSPLAY_API int RSPLAY_CALL RSPlayOpenPlayFile(RSPlayHandle player_id, const char *file_name);
RSPLAY_API int RSPLAY_CALL RSPlayOpenPlayFileList(RSPlayHandle player_id,const char* fileList, size_t strBufLen, size_t count);
RSPLAY_API int RSPLAY_CALL RSPlayOpenPlayFileListEx(RSPlayHandle player_id,const char* fileList, size_t count);
RSPLAY_API int RSPLAY_CALL RSPlayClosePlayFile(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlayGetPlayFileTimeRange(RSPlayHandle player_id, ULONGLONG* beginTime, ULONGLONG* endTime);
RSPLAY_API ULONGLONG RSPLAY_CALL RSPlayGetCurPlayedTime(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlaySetCurPlayedTime(RSPlayHandle player_id, ULONGLONG time);
RSPLAY_API int RSPLAY_CALL RSPlaySetCurPlayedTimeEX(RSPlayHandle player_id, ULONGLONG time);
RSPLAY_API int RSPLAY_CALL RSPlayGetPosImage(RSPlayHandle player_id, ULONGLONG time,IMAGE_INFO *imageInfo);

RSPLAY_API int RSPLAY_CALL RSPlayGetFrameRate(RSPlayHandle player_id, BOOL bFrame_rate);
RSPLAY_API int RSPLAY_CALL RSPlayGetBitRate(RSPlayHandle player_id, BOOL bBit_rate);
RSPLAY_API long RSPLAY_CALL RSPlayGetTotalFrames(RSPlayHandle player_id);
RSPLAY_API long RSPLAY_CALL RSPlayRefreshImage(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL  RSPlayHardwareStretch(RSPlayHandle player_id,BOOL benable,HWND hwnd/* = NULL*/);
RSPLAY_API int RSPLAY_CALL RSPlayGetImageiBpp(RSPlayHandle player_id);

RSPLAY_API int RSPLAY_CALL RSPlayStartPlay(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlayStopPlay(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlaySetPlayMode(RSPlayHandle player_id, int play_mode, int reserved/* = 0*/);
RSPLAY_API int RSPLAY_CALL RSPlayGetPlayMode(RSPlayHandle player_id);


RSPLAY_API int RSPLAY_CALL RSPlayStartlocalrecord(RSPlayHandle player_id, const char *recordfile_name, UINT fileType, UINT record_mode/* = 0*/);
RSPLAY_API int RSPLAY_CALL RSPlaySwitchRecordFile(RSPlayHandle player_id, const char *recordfile_name, UINT fileType, UINT record_mode/* = 0*/);
RSPLAY_API int RSPLAY_CALL RSPlayStoplocalrecord(RSPlayHandle player_id, ULONGLONG* begintime, ULONGLONG* endtime);
RSPLAY_API int RSPLAY_CALL RSPlayStartlocalrecordFile(RSPlayHandle player_id, RSFILE_INFO *fileinfo);
RSPLAY_API int RSPLAY_CALL RSPlayCreatePicbylocalFile(RSPlayHandle player_id,RSFILE_INFOEx *fileinfo);

RSPLAY_API int RSPLAY_CALL RSPlayInputNetFrame(RSPlayHandle player_id, void *buf, int size);
RSPLAY_API int RSPLAY_CALL RSPlayGetListFrameNum(RSPlayHandle player_id);

RSPLAY_API int RSPLAY_CALL RSPlayOpenSound(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL  RSPlayCloseSound(RSPlayHandle player_id);
//Control the system volume,cannot use in win7 OS
RSPLAY_API int RSPLAY_CALL RSPlaySetPlayVolume(int volume);
RSPLAY_API int RSPLAY_CALL RSPlayGetPlayVolume();
RSPLAY_API int RSPLAY_CALL RSPlaySetMute(BOOL bMute);
RSPLAY_API BOOL RSPLAY_CALL RSPlayGetMute();
//
//Only control volume on one play instance
RSPLAY_API int RSPLAY_CALL RSPlaySetPlayVolume_s(RSPlayHandle player_id,int volume);
RSPLAY_API int RSPLAY_CALL RSPlayGetPlayVolume_s(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlaySetMute_s(RSPlayHandle player_id,BOOL bMute);
RSPLAY_API BOOL RSPLAY_CALL RSPlayGetMute_s(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlaySetPlayVolume_bysoft(RSPlayHandle player_id,int volume);
//

RSPLAY_API int RSPLAY_CALL RSPlaySetMicPlayVolume(int volume);
RSPLAY_API int RSPLAY_CALL RSPlayGetMicPlayVolume();
RSPLAY_API int RSPLAY_CALL RSPlaySetMicMute(BOOL bMute);
RSPLAY_API BOOL RSPLAY_CALL RSPlayGetMicMute();

RSPLAY_API int RSPLAY_CALL RSPlaySetOsdString(RSPlayHandle player_id, int index, osd_info_t *p_osd_info);
RSPLAY_API int RSPLAY_CALL RSPlayRemoveOsdstring(RSPlayHandle player_id, int index);
RSPLAY_API int RSPLAY_CALL RSPlayGetAllOsdstring(RSPlayHandle player_id, osd_info_t *p_osd_info,bool* p_bOsd); //max size:MAX_SET_OSD_NUM

RSPLAY_API int RSPLAY_CALL RSPlayCapturePicture(RSPlayHandle player_id, char *file_name);
//type:0为BMP文件，1为png文件，2为jpg文件
RSPLAY_API int RSPLAY_CALL RSPlayCapturePictureToBuf(RSPlayHandle player_id, CAPTURE_CALLBACK callback, void *pUser, int type);
RSPLAY_API int RSPLAY_CALL RSPlayCapturePictureBuf(RSPlayHandle player_id, char *buf);
RSPLAY_API int RSPLAY_CALL RSPlayCapturePictureCallUser(RSPlayHandle player_id, void *usr);

RSPLAY_API int RSPLAY_CALL RSPlayGetSDKVesion(char *ver_string);
RSPLAY_API int RSPLAY_CALL RSPlayGetLastError(RSPlayHandle player_id, char *err_string);

//0: success  -1: fail  -2: open audio player failed  -3: open audio capture failed
RSPLAY_API int RSPLAY_CALL RSPlayStartDualTalk(RSPlayHandle player_id, AudioTalkConfig_t *pAudioTalk/* = NULL*/);
RSPLAY_API int RSPLAY_CALL RSPlayStopDualTalk(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlayRegisterSetDualCallback(RSPlayHandle player_id, DUAL_SPEAK_CALLBACK callback, void* dwUser);

RSPLAY_API int RSPLAY_CALL RSPlayGetCurrentFrameNo(RSPlayHandle player_id); 
RSPLAY_API int RSPLAY_CALL RSPlayAdjustViewArea(RSPlayHandle player_id, int left, int right, int top, int bottom);
//注册指定播放窗口的屏幕绘图回调函数，用于一次解码多窗口渲染的模式下
RSPLAY_API int RSPLAY_CALL RSPlayRegisterDrawFun_s(RSPlayHandle player_id, DRAW_FUN_CALLBACK DrawFun, void* pUser,HWND hwnd);
//注册指定播放实例的屏幕绘图回调函数，用于单次解码单窗口渲染的模式下
RSPLAY_API int RSPLAY_CALL RSPlayRegisterDrawFun(RSPlayHandle player_id, DRAW_FUN_CALLBACK DrawFun, void* pUser);
//bEnable = 0, 实时
//bEnable = 1, iMax = 0，库将按帧数据的时间放，缓冲的帧要由你来控制，这也是net_file模式。
//bEnable = 1, iMax（150～5000）,iMax为缓冲多久的帧数据
RSPLAY_API int RSPLAY_CALL  RSPlaySetCushionRange(RSPlayHandle player_id, BOOL bEnable, int iMax);
RSPLAY_API int RSPLAY_CALL RSPlayRegisterDecCallback(RSPlayHandle player_id, DECODE_CALLBACK DecCallback, void* dwUser);
RSPLAY_API int RSPLAY_CALL RSPlayImageCallback(RSPlayHandle player_id,IMAGE_INFO *pInfo,HWND hwnd/* = NULL*/);
#define RE_NORMAL			0
#define RE_MIRROR_LEFTRIGHT	1
#define RE_MIRROR_UPDOWN	2
RSPLAY_API int RSPLAY_CALL RSPlaySetRenderEffect(RSPlayHandle player_id, int type);

//enable 0:平铺到整个窗口 其他：按实际图像比例显示，创建实例时默认为0
#define RP_ORIGINAL         0
#define RP_PICTURE          1
#define RP_4_3              2
#define RP_16_9             3
RSPLAY_API void RSPLAY_CALL RSPlayRenderActualProportion(RSPlayHandle player_id, int enable); 
//设置是否使用水印解码器解码
RSPLAY_API void RSPLAY_CALL RSUseWaterMarkDecorder(BOOL bUse);

//是否可以显示水印，FALSE表示视频流解密验证失败，视频可能被篡改过
RSPLAY_API BOOL RSPLAY_CALL RSShowWaterMark(RSPlayHandle player_id);

RSPLAY_API BOOL RSPLAY_CALL RSPlayRePaint(RSPlayHandle player_id);
RSPLAY_API BOOL RSPLAY_CALL RSPlayNSynchroRePaint(RSPlayHandle player_id);
/*add by huijun 20110801*/
typedef int (CALLBACK *CONVERT_STATUS_CALLBACK) (int progress,void* param); 
RSPLAY_API int RSPLAY_CALL RSPlay264ToAviStart(RSPlayHandle player_id,PCSTR _264FileName,PCSTR aviFileName,void* param,CONVERT_STATUS_CALLBACK status_callback);
RSPLAY_API int RSPLAY_CALL RSPlay264ToAviStop(RSPlayHandle player_id);
    
RSPLAY_API int RSPLAY_CALL RSPlayConvertFileStart(RSPlayHandle player_id,PCSTR src_file,PCSTR dst_file,void* param,CONVERT_STATUS_CALLBACK status_callback);
RSPLAY_API int RSPLAY_CALL RSPlayConvertFileStop(RSPlayHandle player_id);

//回放抓图回调函数
//type:0为BMP文件(only for windows)，1为png文件，2为jpg文件
RSPLAY_API int RSPLAY_CALL RSPlaySetCapturePictureCallback(RSPlayHandle player_id, int imageType, CAPTURE_PICTURE_CALLBACK callback, void* pUser);
  
RSPLAY_API void RSPLAY_CALL RSPlayClearFlag(RSPLAY_FLAG mask);

RSPLAY_API void RSPLAY_CALL RSPlaySetRenderStatus(BOOL bStop, BOOL bLock);

//for android to send record audio data to DVR or NVR
RSPLAY_API int RSPLAY_CALL RSPlayGetAudioCaptureInfo(RSPlayHandle player_id, AUDIO_CAPTURE_CALLBACK_INFO* info);

//set hardware decode,only for ios and h264 frame
RSPLAY_API int RSPLAY_CALL RSPlaySetHardWareDecode(BOOL bEnable);

//for fish eye
RSPLAY_API int RSPLAY_CALL RSPlayFishGetChnNums(FISHEYE_COMB_TYPE_E enFishEyeType);
RSPLAY_API int RSPLAY_CALL RSPlayFishSetMode(RSPlayHandle player_id, FISHEYE_COMB_TYPE_E enFishEyeType);
RSPLAY_API int RSPLAY_CALL RSPlayFishControl(RSPlayHandle player_id, FISH_CONTROL_REQ_S* req);

RSPLAY_API int RSPLAY_CALL RSPlayDelSyncPlayInstance(RSPlayHandle sync_play, RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlayClearFrameBuffer(RSPlayHandle player_id);

//0 : success   
//-1: unknown error   
//-2: file not exist   
//-3: file access permission denied   
//-4: password error, need input password
//-5: hk mp4 file
//-6: unknown mp4 file
RSPLAY_API int RSPLAY_CALL RSPlayNewOpenPlayFileListEx(RSPlayHandle player_id, const RSPlayNewOpenPlayFileListExParam* param);
RSPLAY_API int RSPLAY_CALL RSPlayGetFileInfo(RSPlayGetFileInfoParam* param);

//this function for android to notify app to render, you shoulud never call it
RSPLAY_API int RSPLAY_CALL RSPlayRegisterBeforeRenderCallback(RSPlayHandle player_id, BEFORE_RENDER_CALLBACK before_render_cb, void* user_param);

#ifdef __ANDROID__
RSPLAY_API void RSPLAY_CALL RSPlayAndroidSetJVM(void* jvm);
RSPLAY_API RSPlayHandle RSPLAY_CALL RSPlayAndroidSurfaceCreate();
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceDestory(RSPlayHandle handle);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceChange(RSPlayHandle handle, int width, int height);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceDraw(RSPlayHandle handle, void* picture);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceDrawWithBlack(RSPlayHandle handle);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceCapturePicture(RSPlayHandle handle, const char* picture_name);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceSetVideoProportion(RSPlayHandle handle, int proportion);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSurfaceVideoMouseEvent(RSPlayHandle handle, float x, float y, float s, rs_mouse_event mouse_event);

RSPLAY_API int RSPLAY_CALL RSPlayAndroidSetFishMode(RSPlayHandle handle, FISHEYE_COMB_TYPE_E type);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSetFishContro(RSPlayHandle handle, FISH_CONTROL_REQ_S* req);

RSPLAY_API bool RSPLAY_CALL RSPlayAndroidWindowInZoomStatus(RSPlayHandle handle);
RSPLAY_API int RSPLAY_CALL RSPlayAndroidSetScaleSize(RSPlayHandle handle, float scaleSize);
#endif

RSPLAY_API bool RSPLAY_CALL RSPlayWindowInZoomStatus(RSPlayHandle player_id);
    
RSPLAY_API int RSPLAY_CALL RSPlayGetKeyFrameCount(RSPlayHandle player_id);
RSPLAY_API int RSPLAY_CALL RSPlaySeekByKeyFrameIndex(RSPlayHandle player_id, int index);

RSPLAY_API int RSPLAY_CALL RSPlayClearTime(RSPlayHandle player_id);

//warning:never call these function in your app
/************************************************************************/
RSPLAY_API int RSPLAY_CALL RSPlayRegisterSdkwrapperDrawCallback(RSPlayHandle player_id, SDKWRAPPER_DRAW_CALLBACK cb, void* user_param);

RSPLAY_API int RSPLAY_CALL RSPlaySetColor(RSPlayHandle player_id, const rs_color* color_value);
RSPLAY_API int RSPLAY_CALL RSPlayDrawLine(RSPlayHandle player_id, const rs_rect* line_value, int line_count);
RSPLAY_API int RSPLAY_CALL RSPlayDrawRect(RSPlayHandle player_id, const rs_rect* rect_value, int rect_count);
RSPLAY_API int RSPLAY_CALL RSPlayDrawSolidRect(RSPlayHandle player_id, const rs_rect* rect_value, int rect_count, float alpha_value);
RSPLAY_API int RSPLAY_CALL RSPlayDrawHollowCircle(RSPlayHandle player_id, const rs_rect* rect_value, int rect_count);
RSPLAY_API int RSPLAY_CALL RSPlayDrawText(RSPlayHandle player_id, const char* text_value, const rs_rect* rect_value);

//only support png, the return value means session id
RSPLAY_API int RSPLAY_CALL RSPlayUploadPictureFromMemory(RSPlayHandle player_id, const char* picture_data, int picture_length);
//sess_id: the return value of RSPlayUploadPictureFromMemory
RSPLAY_API int RSPLAY_CALL RSPlayDeletePicture(RSPlayHandle player_id, int sess_id);
//sess_id: the return value of RSPlayUploadPictureFromMemory
RSPLAY_API int RSPLAY_CALL RSPlayDrawPicture(RSPlayHandle player_id, int sess_id, const rs_rect* rect_value, float alpha_value);
/************************************************************************/

//this function for android to notify app to render, you shoulud never call it
RSPLAY_API int RSPLAY_CALL RSPlayRegisterPictureCallback(RSPlayHandle player_id, const PictureCallbackParam* param);

RSPLAY_API int RSPLAY_CALL RSPlayStartlocalrecordFileEx(RSPlayHandle player_id, RSFILE_INFO_EX *fileinfo);

RSPLAY_API void RSPLAY_CALL RSPlaySetMaxHardwareDecodeNumber(int num);

#ifdef __cplusplus
}
#endif // end of extern "C"

#endif // end of __RSPLAY_H__
