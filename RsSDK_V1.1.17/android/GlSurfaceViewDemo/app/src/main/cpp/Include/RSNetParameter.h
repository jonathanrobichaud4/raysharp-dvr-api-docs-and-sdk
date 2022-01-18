/*********************************

  		RS NetParamether
		mai 20110224

*********************************/

#ifndef __RS_NETPARAMETHER_H__
#define __RS_NETPARAMETHER_H__

#include "RSTypedef.h"
#include "RSNetProtocol.h"
//#include "RSPLParameter.h" //RSPL_MAXNAMELEN
//#include "push.h" 

#define ParamToNet 1 // caiwang213 20110603
#define NetToParam 0
#define CheckParam 2
#define ParamToNetDefault 3 //default parameter 20141017
#define ParamError (-2)

#define RS_Open 1
#define RS_Close 0


/* ******************** *
   
	基本信息

* ******************** */

//TvSystem
#define RS_PAL 0
#define RS_NTSC 1
typedef struct {
	UINT StructSize; //该结构体大小

	//系统配置
	BYTE DeviceName[MaxNameLen];
	UINT DeviceID;

	BYTE TvSystem; /*摄像头制式: <RS_PAL, RS_NTSC>*/

	//系统信息
	BYTE DeviceType[MaxNameLen]; //设备类型
	BYTE MacAddr[MaxNameLen];    
	BYTE SoftwareVer[MaxNameLen]; //系统软件版本
	BYTE HardwareVer[MaxNameLen]; //硬件版本
	BYTE IEVer[MaxNameLen]; 	  //IE版本型号		/*Yiguang 11.06.15*/
	BYTE IpAddr[MaxIpLen];

	UINT MobilePort;//手机端口
	UINT Port;
	UINT WebPort;

	BYTE DdnsHostStatus[MaxNameLen];	
	BYTE HddStatus[MaxNameLen];

	BYTE P2pKeyID[12];
	BYTE P2pUID[40];  // kguard用户需求
	BYTE Language;    // 对应LANGUAGE_E值
	BYTE Audio;				/*0: close; 1: open*/
	BYTE MicInVolume;	/* 输入声音大小(0 - 100) */
	BYTE LineOutVolume; /* 输出声音大小(0 - 100) */
	BYTE AdecEncoding;	/* 编解码类型 0, PT_G711U;1,PT_G711A */
	BYTE AgentVer[16];  //agent 版本(针对lorex)
	BYTE DongleVer[32]; //usb无线模块(dongle)版本(lorex)
	BYTE SerialNumber[16]; /*针对ZIP客户给每一台机器分配唯一的序列号*/
	BYTE P2pIDFlag;       /*whether if the p2p id valid, 0:valid, 1: invalid , 2016.10.21 add*/  
	BYTE DdnsEnabled;    /*Ddns的开关0:close 1:open (针对zip)2017.11.28 add*/
	BYTE DhcpEnabled;    /*DHCP的开关0:close 1:open (针对zip)2017.11.28 add*/
	BYTE UpnpEnabled;
	BYTE WifiIPAddr[MaxIpLen];
	BYTE EnableWifi;
	BYTE UseIPV6;	   /*是否使用IPV6，0-不使用，1-使用*/
	BYTE P2PSwitchFlag;   /*p2p开关 0:关闭，1:打开   2018.03.13 add */
	BYTE DrivesNumber;    /* hdd个数 2018.06.28 add */
	BYTE DomainName[36]; 
	BYTE AgentType[8];
	BYTE SerialNumberEX[32];//lorex use 32 bytes sid,2016.11.10 add
	BYTE WifiVer[MaxNameLen];
	BYTE NetMask[MaxIpLen];  /*子网掩码(针对zip),2017.11.28 add*/
	BYTE GateWay[MaxIpLen];  /*网关(针对zip),2017.11.28 add*/
	BYTE IPv6Addr[40];
	UINT ClientExtPort;  /*客户端外网端口号*/
	UINT WebExtPort;     /*Web外网端口号*/
	UINT MobileExtPort;  /*手机外网端口*/
	BYTE resv[4];
	BYTE UseUPNP[16];     /*UPNP 0:关闭，1:打开   web、client、mobile、rtsp*/	
	UINT HttpsIntPort;       /* https内部端口 */
	UINT HttpsExtPort;       /* https外部端口 */	
}RSNet_SystemBaseInfo_t;

//ipc systemInfoEx
typedef struct
{
	UINT StructSize; //该结构体大小
	BYTE resv[4];
	BYTE DeviceIDEx[32]; //DeviceIDEx ipc use , 2016.12.15 add 

	BYTE AFVersion[16];// ipc auto foucs version 2016.12.15 add
	BYTE bP2pIDUsed;       /*whether if the p2p id open, 0:close, 1: open , 2016.12.21 add*/

	BYTE lorexModel[12]; // lorex model ,2017.01.13 add
	BYTE reserve[3];
	BYTE NVRVersion[64]; //2017.10.18 add .for nanrui 98C
	BYTE INTModelVersion[64];//2017.10.18 add .for nanrui intell version
}RSNet_SysParamInfoEx_t;
typedef struct
{
    char AlarmType; 
	char PostAlarmTime;
	char IntervalTime;
	char AlarmEnable;
	char reserved[4];
	char MessageInfo[80];
}RSNet_UrmetNotificationParam_t;

typedef struct
{
     UINT StructSize; //该结构体大小
     char UrmetNotificationSwitch;
	 char CurAlarmType;
	 char reserved[2];
	 UINT  UrmetAlarmBitEnable;
	 char UrmetName[32];
	 char UrmetURL[128];
	 char UserName[32];
	 char Password[32];
	 RSNet_UrmetNotificationParam_t UrmetNotificationAlarmInfo[9];
 }RSNet_UrmetHttpParam_t;

/* ******************** *
   
		硬盘

* ******************** */

//HddState
#define RS_HDDS_NONE 		0
#define RS_HDDS_UNFORMAT 	1
#define RS_HDDS_OK 	    	2
#define RS_HDDS_BAD 		3
#define RS_HDDS_RONLR 		4
#define RS_HDDS_BACKUP  	5   //冗余盘
#define RS_HDDS_INVALID 	6

//OverWrite
#define RS_OverWrite_Close 	0
#define RS_OverWrite_Auto 	1
#define RS_OverWrite_1Hour 	2
#define RS_OverWrite_3Hours 3
#define RS_OverWrite_1Day 	4
#define RS_OverWrite_7Days 	5
#define RS_OverWrite_30Days 6
#define RS_OverWrite_90Days 7

typedef struct{
	UINT StructSize; //该结构体大小
	UINT HddMask; 		 //硬盘掩码

	/*硬盘状态*/
	unsigned long long HddState;  
	unsigned long long HddTotalSize;/*单位:字节*/
	unsigned long long HddFreeSize;
	unsigned long long HddFreeRecord; //剩余可录时间
    BYTE HddType;  //硬盘类型.0: SATA; 1 : ESATA(NVR 专用程序)
    BYTE HddNo;    //硬盘序列号,区分SATA和ESATA.  (NVR 专用程序)  
	BYTE HddFreeRecord_Min;//HddFreeRecord为0，读取这个变量，表示多少分钟
	BYTE reserved[5];
}RSNet_SoleHddInfo_t;

typedef struct {
	UINT StructSize; //该结构体大小

	//硬盘配置
	/*自动覆盖选项*/
    BYTE  OverWrite;       
	BYTE RecordState;
	BYTE SupportOneHdd;
    BYTE ESataRecEnable;  //是否开启ESATA录像.0: disable; 1: enable(NVR)
	
    UINT Redundancy;      /*32个bit, 每个bit对应一个硬盘属性，=0, 主盘，=1, 冗余盘*/
	UINT OverWritePeriod; /*覆盖周期，以小时为单位*/
	BYTE RecordChn[16][32];

	BYTE OverWriteList[24][16];//24个option，每个option是长度为12的字符串
}RSNet_HddInfo_t;




/* ******************** *
   
		串口配置

* ******************** */

//Protocol
#define RS_PelcoD 0
#define RS_PelcoP 1

//Baudrate
#define RS_Baudrate_1200 0
#define RS_Baudrate_2400 1
#define RS_Baudrate_4800 2
#define RS_Baudrate_9600 3

//DataBit
#define RS_DataBit_8 0
#define RS_DataBit_7 1
#define RS_DataBit_6 2
#define RS_DataBit_5 3

//StopBit
#define RS_StopBit_1 0
#define RS_StopBit_2 1

//Check
#define RS_CheckBit_None  0
#define RS_CheckBit_Odd   1
#define RS_CheckBit_Even  2
#define RS_CheckBit_Mark  3
#define RS_CheckBit_Space 4

//KbSwitch
#define RS_SerialKB  0
#define RS_SerialChn 1

typedef struct {
	UINT StructSize; //该结构体大小

    /*协议类型*/
    BYTE Protocol;   
    /*波特率*/
    BYTE Baudrate;
    /*数据位*/
    BYTE DataBit;
    /*停止位*/
    BYTE StopBit;
    /*校验*/
    BYTE Check;
	/*PS:此项暂不使用，透明通道OR大键盘选择 0:大键盘，1:透明通道  */
	BYTE KbSwitch;
	BYTE FlowCtrl;/*流控0-None，1-DTR/DSR，2-RTS/CTS，3-XON/XOFF*/
	BYTE Address;
}RSNet_SerialInfo_t;




//用户配置

#define RS_MAX_USER_NUMBER 7
//#define RS_USERRIGHT_MAX_PAGE 128


// 每个用户的信息

//UserStatus
#define RS_UserLiveOff 0
#define RS_UserLiveOn  1

/*
//用户权限各位显示
enum RSNet_UserPageRight{
	RS_LIVE_PAGE = 0,
	RS_OUTPUT_PAGE,
	RS_RECPARA_PAGE,
	RS_SCHEDULE_PAGE,
	RS_RECSEARCH_PAGE,
	RS_NETWORK_PAGE,
	RS_DDNS_PAGE,
	RS_EMAIL_PAGE,
	RS_MOBILE_PAGE,
	RS_NTP_PAGE,
	RS_HDD_PAGE,
	RS_ALARM_PAGE,
	RS_PTZ_PAGE,
	RS_PTZ_CTRL,
	RS_SERIAL_PAGE,
	RS_GENERAL_PAGE,
	RS_MOTION_PAGE,
	RS_VERSION_PAGE,
	RS_STOP_RECORD,
	RS_MAINTAIN_PAGE,
	RS_REBOOT,
	RS_POWER_OFF,
	RS_ABNORMAL_PAGE,
	RS_LOG_PAGE,
	RS_MAINSTREAM_PAGE,
	RS_SUBSTREAM_PAGE,
	RS_START_RECORD,
	RS_VIDEOCOVER_PAGE,
	RS_BACKTOFACTORYSET_PAGE,
};
*/


typedef struct 
{
	UINT StructSize; 	//该结构体大小
	UINT UserMask; 	//掩码 该掩码最大为MAX_USER_NUM

	BYTE Password[8];		// 用户密码
	BYTE Password2[8];		// 用户密码确认
	BYTE UserName[10];		// 用户名

	BYTE HaveSwitch;	// 登录密码开关	<RS_Open, RS_Close>

	BYTE HaveUser;		// 用户是否使用 <RS_Open, RS_Close> 

	BYTE UserStatus;		// 用户状态		//1为在线,0为不在线
	BYTE reservel[3];

	UserRightWrap UserRights; //权限
	BYTE c32Password[32];		// 用户密码
	BYTE c32UserName[32];		// 用户密码确认
	UINT PreviewChannel_EX[8];     //预览通道
	UINT PlayBackChannel_EX[8];       //回放通道
	UINT BackupChannel_EX[8];        //备份通道
	UINT PtzControlChannel_EX[8];     //云台控制通道
}RSNet_SoleUserInfo_t;

typedef struct {
	UINT StructSize; 	//该结构体大小
	
	UINT MaxUerNum; 	//总共用户数
	UINT DeviceID;
	S8   DeviceName[36];
}RSNet_UserSet_t;




//DST配置
//TimeMode
#define RS_TimeMode_24 0
#define RS_TimeMode_12 1

//DateMode
#define RS_DateMode_MDY 0
#define RS_DateMode_YMD 1
#define RS_DateMode_DMY 2

//Offset
#define RS_Dst1Hour 0
#define RS_Dst2Hour 1

//DstMode
#define RS_DstWeek 0
#define RS_DstDate 1


//StartMonth, EndMonth
#define RS_DstMonth_January 	0
#define RS_DstMonth_February 	1
#define RS_DstMonth_March 		2
#define RS_DstMonth_April 		3
#define RS_DstMonth_May 		4
#define RS_DstMonth_June 		5
#define RS_DstMonth_July 		6
#define RS_DstMonth_August 		7
#define RS_DstMonth_September 	8
#define RS_DstMonth_October 	9
#define RS_DstMonth_November 	10
#define RS_DstMonth_December 	11

//StartWeek, EndWeek
#define RS_DstFristWeek 	0
#define RS_DstSecondWeek 	1
#define RS_DstThirdWeek 	2
#define RS_DstFourthWeek 	3
#define RS_DstFifthWeek 	4

//StartWeekDay, EndWeekDay
#define RS_DstSunday		0
#define RS_DstMonday 		1
#define RS_DstTuesday		2
#define RS_DstWednesday 	3
#define RS_DstThursday		4
#define RS_DstFriday		5
#define RS_DstSaturday		6


typedef struct {
	UINT StructSize; //该结构体大小

    DateTime time; //系统时间
    /*时间格式*/
    BYTE TimeMode;
    /*日期格式，0为MM/DD/YY，1为YY-MM-DD，2为DD/MM/YY*/
    BYTE DateMode;
    /*夏令时，<RS_Close, RS_Open>*/
    BYTE Dst;
	/* Dst偏移正常时间值，0-1hour，1-2hour */
    BYTE Offset;
    /*夏令时模式，0-Week，1-Date*/
    BYTE DstMode;
	/*开始月，共12个月:0---11*/
    BYTE StartMonth;    
    /*开始周，0-第一周，1-第二周，2-第三周，3-第四周,4-第五周*/
    BYTE StartWeek;
	/*开始于星期几，0-Sun,1-Mon, ...6-Sat*/
	BYTE StartWeekDay;
	/*结束月，共12个月:0---11*/
    BYTE EndMonth;
    /*结束周，0-第一周，1-第二周，2-第三周，3-第四周*/
    BYTE EndWeek;
	/*结束于星期几，0-Sun,1-Mon, ...6-Sat*/
	BYTE EndWeekDay;

	BYTE StartSecond;
	BYTE EndSecond;
	BYTE reservel[3];

	/*Dst 开始时间，日期*/
    BYTE StartDate[4];
	/*Dst 开始时间，时分秒*/
    BYTE StartHour[4];
	/*Dst 结束时间，日期 */
    BYTE EndDate[4];
	/*Dst 结束时间，时分 秒*/
    BYTE EndHour[4];
}RSNet_DSTSet_t;       // 此结构体有嵌套成其他结构体成员，慎重协商扩充问题

//Ntp配置

/*NtpIPAddr  NTP服务器地址*/
#define RS_Ntp_windows   0
#define RS_Ntp_nist 	 1
#define RS_Ntp_ntp 		 2
#define RS_Ntp_lorexddns 3
/*对应以下显示
time.windows.com
time.nist.gov
pool.ntp.org
ntp.lorexddns.net
*/

//TimeZone
//PS:b12 = GMT-12:00
//PS:f8  = GMT+8:00
//PS:b0430  = GMT-4:30
#define RS_TimeZone_GMT_b12 	0  
#define RS_TimeZone_GMT_b11 	1 
#define RS_TimeZone_GMT_b10 	2 
#define RS_TimeZone_GMT_b09 	3 
#define RS_TimeZone_GMT_b08 	4 
#define RS_TimeZone_GMT_b07 	5 
#define RS_TimeZone_GMT_b06 	6 
#define RS_TimeZone_GMT_b05 	7 
#define RS_TimeZone_GMT_b0430 	8 
#define RS_TimeZone_GMT_b04 	9 
#define RS_TimeZone_GMT_b0330 	10 
#define RS_TimeZone_GMT_b03 	11 
#define RS_TimeZone_GMT_b02 	12 
#define RS_TimeZone_GMT_b01 	13 
#define RS_TimeZone_GMT 		14
#define RS_TimeZone_GMT_f01 	15 
#define RS_TimeZone_GMT_f02 	16 
#define RS_TimeZone_GMT_f03 	17 
#define RS_TimeZone_GMT_f0330 	18 
#define RS_TimeZone_GMT_f04 	19 
#define RS_TimeZone_GMT_f0430 	20 
#define RS_TimeZone_GMT_f05 	21 
#define RS_TimeZone_GMT_f0530 	22 
#define RS_TimeZone_GMT_f0545 	23 
#define RS_TimeZone_GMT_f06 	24 
#define RS_TimeZone_GMT_f0630 	25 
#define RS_TimeZone_GMT_f07 	26 
#define RS_TimeZone_GMT_f08 	27 
#define RS_TimeZone_GMT_f09 	28 
#define RS_TimeZone_GMT_f0930 	29 
#define RS_TimeZone_GMT_f10 	30 
#define RS_TimeZone_GMT_f11 	31 
#define RS_TimeZone_GMT_f12 	32 
#define RS_TimeZone_GMT_f13 	33 


//IPC通道状态参数
typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask;//通道掩码

	/*IP地址*/   
	BYTE IPAddr[4];
	/*媒体端口*/
	UINT Port;
	/*登陆用户名*/
	BYTE UserName[36];
	/*登陆用户密码*/
	BYTE UserPW[36];    
	/*对应前端设备的那个通道,如果前端是dvr，则有多个通道*/
	BYTE ChnNo;
	/*厂家0:raysharp,1:hikvison,2:sony*/
	BYTE Protocol;	
	/*是否启用，只作输出*/
	BYTE Enable;
	/*当前ip对应的前端设备的总通道数*/
	BYTE ChnMax;
	/*当前ip通道上的状态, 只作输出*/
	BYTE IPChnStatus;
	BYTE Version;
	BYTE switchmode; /*0 自动模式 1 手动模式*/
	BYTE reservel;

	unsigned long long u64devType;  //设备类型
	BYTE macAddr[36];    //mac 地址
	BYTE IpcName[36];    //设备名称，只做输出

    S8 DevType[36];	     /*设备类型*/
    S8 Manufacturer[36]; /*厂商*/
    S8 SoftVersion[36];  /*固件版本*/
    BYTE mask[4];		 /*子网掩码*/
    S8 DevAlias[36];     /* IP Camera的别名 */
	BYTE AliasPos;       /* IPC别名摆放的位置, 0-左上，1-右上，2-左下，3-右下，4-不显示 */
    BYTE reserve2[3];
	BYTE sIPAddr[64];
    BYTE GateWay[4]; 	 /*网关*/
	BYTE dns1[4];
	BYTE dns2[4];
	UINT IEport;
    BYTE switchflag;     /*私有ipc  1 连交换机口 0 表示没有*/
	BYTE portnum;        /*交换机口 从[0  -MAX_POE_NUM) */	
    BYTE P2pUID[32];     /* IPC P2P2 ID */
	BYTE poeflag;        /*POE通道模式: bit0 0--手动 1--自动 */
	BYTE CameraType;
	BYTE poePhyMode;		/*POE band mode 0：AUTO  1:10M*/
	BYTE reserved[3];
	BYTE MulChannel[8];     /*多通道   使用 */
}RSNet_SoleIPCSet_t;

typedef struct {
	UINT StructSize; //该结构体大小

//	/*服务器端口*/
//	UINT  NtpPort;
//	/*更新周期-单位:分钟，最大值65535*/
//	UINT SyncPeriod;
	/*网络服务器地址*/
	BYTE NtpIPAddr[4];
	/*NTP 启用标识，<RS_Close, RS_Open>*/
	BYTE UseNtp;
    /* 时区设置*/
    BYTE TimeZone;
	BYTE NtpSerFlag;
	BYTE reserver;
	UINT NtpPort;
	UINT SyncPeriod;

}RSNet_NtpSet_t;  // 此结构体有嵌套成其他结构体成员，慎重协商扩充问题

// 通用信息配置
typedef struct {
	UINT StructSize; //该结构体大小
	RSNet_DSTSet_t DstSet;
	RSNet_NtpSet_t NtpSet;
	UINT           LanguageMask;
	BYTE           Language;    // 对应LANGUAGE_E值
	BYTE           VideoFormat;
	BYTE           AutoLogout;
	BYTE           AllFlickerCtrl;
	BYTE		   DateMode;    /*日期格式，0为MM/DD/YY，1为YY-MM-DD，2为DD/MM/YY*/
	BYTE           TimeMode;    /*时间格式，0为24小时制，1为12小时制*/
	BYTE           LastLanguage;
	BYTE           ShowWizard;
    BYTE           hybirdEnable;//是否启用混合DVR
	BYTE           vgaresolution; //RCI专用
	BYTE		   bIEChangeTime;// indicates whether the client modifing the dev time
	BYTE           reserved[1]; //
	UINT           ExtendLanguageMask;  /*New 32-bit to extend Language for client*/  
    BYTE           NtpServAddr[64]; //
    WORD           TimeZone_EX;
	BYTE           WaterMark; /*0 : 关闭 1打开 */
	BYTE           reserved2[1];
	UINT		   ClientAutoLogoutTime;
}RSNet_GeneralInfoSet_t;

typedef struct{
	BYTE Hour;
	BYTE Minute;
	BYTE Second;
	BYTE rev;
}RSNetTimeSet_t;

//显示配置
typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; //通道掩码
	BYTE Chroma; 		//色度, <0-63>或<0 - 255>
	BYTE Brightness; 	//亮度, <0-63>或<0 - 255>
	BYTE contrast; 	//对比度, <0-63>或<0 - 255>
	BYTE saturation; 	//饱和度, <0-63>或<0 - 255>
	BYTE DefaultColor; 	//恢复颜色默认值
	BYTE Sharpness; 	 /* 锐度<0 - 255> */
	BYTE ColorMode:2;   /*0:0-63， 1:0-255*/
	BYTE DisplayRule:4; //根据不同IPC协议类型显示不同的内容
	BYTE ShowDefault:1; //远端根据IPC决定是否显示默认按钮
	BYTE reserved:1;
	BYTE LoadBalancing:2; /* 0:实时(卡顿) 1: 均衡 (延时)*/
	BYTE reserved2:6;
	BYTE Gamma;		 /* <0 - 255> */
	BYTE Chroma2; 		//目前LUX客户使用,色度2, <0-63>或<0 - 255>
	BYTE Brightness2; 	//目前LUX客户使用,亮度2, <0-63>或<0 - 255>
	BYTE contrast2; 	//目前LUX客户使用,对比度2, <0-63>或<0 - 255>
	BYTE saturation2; 	//目前LUX客户使用,饱和度2, <0-63>或<0 - 255>
	BYTE Sharpness2; 	 /* 目前LUX客户使用,锐度2<0 - 255> */
	BYTE reserved3[66];
	RSNetTimeSet_t SunRiseTime;	//目前LUX客户使用,表示白天的开始时间
	RSNetTimeSet_t SunSetTime;	//目前LUX客户使用,表示晚上的开始时间
}RSNet_SoleColorSet_t;

//视频遮挡配置
#define MAX_VIDEOCOVER_NUM  32
//此结构体不考虑后续修改,直接传输
typedef struct {/*矩形*/
	UINT StructSize; //该结构体大小

	int CoverSwitch; //该遮挡区是否启用, <RS_Open, RS_Close>
    int x, y, w, h;
}RSNet_VideoCoverArea_t;


typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 		 //通道掩码

	BYTE VideoCoverSwitch:2;/* 通道是否启用视频遮挡, <RS_Open, RS_Close>*/
	BYTE ShelterMode:2;//等于1时，采用画网格模式，等于0，画矩形框
	BYTE reserved:4;
	BYTE VideoCoverNum;/* 支持最大的视频遮挡数目,0:4块，其它数目代表实际支持的块数*/
	BYTE reservel;
	BYTE mosaicLevel;/*马赛克强度等级*/	//整个低4位表示选中项 ; 高4位(bit_4==0有64，bit_4==1无64 )
	union{
		struct
		{
			RSNet_VideoCoverArea_t VideoCoverArea[8]; //直接传输, 不走三级列表
		};
		struct
		{
			BYTE regionSonix[48];
		};
	};
	RSNet_VideoCoverArea_t VideoCoverArea2[4]; 
	UINT resWidth;
	UINT resHeight;
}RSNet_SoleVideoCover_t;


//PTZ配置

/* 参数设置与Serial一致
//Protocol
#define RS_PelcoD 0
#define RS_PelcoP 1

//Baudrate
#define RS_Baudrate_1200 0
#define RS_Baudrate_2400 1
#define RS_Baudrate_4800 2
#define RS_Baudrate_9600 3

//DataBit
#define RS_DataBit_8 0
#define RS_DataBit_7 1
#define RS_DataBit_6 2
#define RS_DataBit_5 3

//StopBit
#define RS_StopBit_1 0
#define RS_StopBit_2 1

//Check
#define RS_CheckBit_None  0
#define RS_CheckBit_Odd   1
#define RS_CheckBit_Even  2
#define RS_CheckBit_Mark  3
#define RS_CheckBit_Space 4
*/

typedef struct _NET_TOUR_Point_{
	BYTE preset;/*1~255 default 1*/
	BYTE speed;/*1~100, default 30*/
	BYTE delay;/*0~120 secondm,  default 10*/
	BYTE reservel;
}NetTourPoint_t;

typedef struct _Net_PTZ_TOUR_{
	NetTourPoint_t points[32];
}NetPtzTour_t;

#define RS_MAX_CRUISE_POINT 256
typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 		 //通道掩码

    /*协议类型*/
    BYTE Protocol;
    /*波特率*/
    BYTE Baudrate;
    /*数据位*/
    BYTE DataBit;
    /*停止位*/
    BYTE StopBit;
    /*校验*/
    BYTE Check;
	/* PTZ 自动巡航开关 RS_Close, RS_Open*/
	BYTE EnablePtzCruise;
	BYTE KeyboardFlag;//1：用keyboard   0:PTZ
    BYTE reserved2:5;
	BYTE FocusMode:1;//1:半自动；0：全自动
    BYTE SignalType:2; //0: 模拟信号; 1: 数字信号.
    /*编号,即UI上的ADDRESS，范围为1-255*/
    UINT Number;
    ///*通道轮询时间, 范围为1--255, 注意当时间为0 时表示该预置点未被设置! */
	BYTE ChnCruiseTime[RS_MAX_CRUISE_POINT];	
	NetPtzTour_t Tour[8];/*每个通道支持8条巡航线，每条巡航线最大支持32个预置点*/
}RSNet_SolePTZSet_t;

typedef struct {
	UINT StructSize; //该结构体大小

    /* PTZ 自动巡航开关 RS_Close, RS_Open*/
    UINT  EnablePtzCruise;     /*This para is reserved for another page later!*/
}RSNet_PTZSet_t;



//OSD配置
//Position
#define RS_PositionLeftUp 	 0
#define RS_PositionLeftDown  1
#define RS_PositionRightUp 	 2
#define RS_PositionRightDown 3

/* 预览页面参数设置,此结构体仅限DVR使用*/

typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 		 //通道掩码

    /*通道名称位置 0-左上，1-左下，2-右上，3-右下*/
    BYTE Position;

    /*预览osd开关 RS_Open, RS_Close*/
    BYTE Preview;

    /*现场时间OSD RS_Open, RS_Close*/
    BYTE PreviewTimeSet;

    /*录像时间OSD RS_Open, RS_Close*/
    BYTE RecordTimeSet;

    /*通道名称*/
    BYTE ChnName[20];

	BYTE FlickerCtrl;   //nvr对ipc的闪烁控制 0 :50HZ 1:60HZ
    BYTE resolution;    //设备分辨率(RCI客户20150623)
    BYTE reserve[6];
    BYTE honeyChnName[64]; //honeywell通道名,支持8个中文(utf-8编码)
}RSNet_SoleOsdSet_t;

typedef struct {
	UINT StructSize; //该结构体大小

    /*现场时间OSD RS_Open, RS_Close*/
    BYTE PreviewTimeSet;
    /*录像时间OSD RS_Open, RS_Close*/
    BYTE RecordTimeSet;
	BYTE FlickerCtrl;   //nvr对ipc的闪烁控制 0 :50HZ 1:60HZ
    BYTE reservel;
}RSNet_OsdSet_t;

typedef struct 
{
	UINT StructSize;
	UINT ChannelMask; 		 //通道掩码

	UINT IntCrossSwitch;        /*智能画线开关，BIT_1位为所有智能画线开关，若为1，则开启，若为0则关闭*/
	BYTE PreviewAudioEnable;	/*预览界面音频开关，0: 关闭,1:开启*/
	BYTE FloodLightMode; /*白光灯 0:disable 1:enable*/
	BYTE FloodLightValue;/*值范围[1, 100]*/
	BYTE AudioAlarmSwitch;/*喇叭报警0:disable 1:enable*/
	BYTE FlashLight;   /*闪光灯*/
	BYTE LineOutVolume;
	BYTE StrobeFrequency; /*闪关灯频率 0:低 1:中 2:高*/
	BYTE SirenSwitch;
	BYTE SirenValue;
	BYTE SirenTime;
	BYTE OperBtn;//点击的按钮是哪个？ 1：sounds，2是light
	BYTE reserve[41];    		/*保留字节*/
}RSNet_SolePreviewCtrl_t;
typedef struct
{
    UINT structsize;
    UINT channelmask;
    int cx;
    int cy;
    int cRadii;
    BYTE reserved[60];
}RSNet_FishEyeCircle_t;

//ALARM OUT配置
typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	BYTE  AlarmOutScHalfHour[8][48];  // 和录像计划表示一致
}RSNetNew_SoleAlarmOutScheduleset_t;

//网络基本参数
//NetworkMode
#define RS_DHCP   0
#define RS_PPPOE  1
#define RS_Static 2

//PPPoEState
#define PPPOE_CONNECTING   0
#define PPPOE_SUCCESS      1
#define PPPOE_FAIL         2
/* 网络参数页面参数结构 */
typedef struct {
	UINT StructSize; //该结构体大小

    /*IP地址*/
    BYTE IPAddr[4];
    /*子网掩码*/
    BYTE NetMask[4];
    /*网关*/
    BYTE GateWay[4];
    /*客户端端口号*/
    UINT Port;
    /*Web端口号*/
    UINT WebPort;
    /*连网方式，<RS_DHCP, RS_PPPOE, RS_Static>*/
    BYTE NetworkMode;
    /* UPNP     RS_Open, RS_Close*/
    BYTE UseUPNP;
	/*手机端口*/
	WORD MobilePort;
    /*DNS1*/
    BYTE dns1[4];
    /*DNS2*/
    BYTE dns2[4];
    //ppoe设置
    /*PPPOE用户名*/
    BYTE PPPOEuser[MaxNameLen];
    /*PPPOE用户密码*/
	BYTE Password[MaxNameLen];

    //3G信息
	BYTE APN[MaxNameLen];
	BYTE DialCode[MaxNameLen];
	BYTE WirelessUser[MaxNameLen];
	BYTE WirelessPwd[MaxNameLen];
	
	BYTE EncodeFlag; //Enable:1 Disable:0
	/*WAN 口工作于: 0 WAN  ;1  LAN*/
	BYTE WANWkIn;
	
	/*PPPOE state  0:connecting.. 1:success 2:fail */
	BYTE PPPoEState;
	/*PPPoE IP */
	BYTE PPPoEIPaddr[4];
	BYTE BandWidth;
	BYTE  RtspAuthType;/*rtsp authority type(0:none 1:basic 2:digest)*/
	BYTE  UseVideoPwd; /* 视频加密开关 */
    WORD IpKBPort;     /*ip键盘端口号*/  //honywell专用
    BYTE UPnP_TMEnable;/*使能UPnP_TM功能1-开启,0-关闭，由IPC维护*/ 
	BYTE UseIPV6;	   /*是否使用IPV6，0-不使用，1-使用*/
	BYTE EnablePPPOE;  /*UI5.0 是否启用pppoe*/
	BYTE Enable3G;     /*UI5.0 是否启用3G*/
	BYTE EnableDHCP;   /*UI5.0 0:static ip, 1:dhcp*/
	BYTE DownloadSpeed; /*0-40 Mbps*/
    BYTE P2Pswitch;   /*p2p开关 0:关闭，1:打开*/
	BYTE Connect_Procotol;/*UPNP 协议, 0:ONVIF; 1:SVNP*/
	BYTE WifiStation;
	BYTE EnableWifi;
	BYTE WifiIPAdrr[4];
	BYTE reserve[2];
	BYTE User3G[MaxNameLen];
	BYTE Pwd3G[MaxNameLen];
	BYTE switchIPAddr[4];      /*IP地址*/
	BYTE switchNetMask[4];     /*子网掩码*/
	BYTE switchGateWay[4];     /*网关*/
	WORD	ClientAutoExtPort;	/* UPnP auto ext port */
	WORD	WebAutoExtPort;	/* UPnP auto ext port */
	BYTE TransmissionMode[16]; /*传输距离，0-普通*/
	BYTE SwitchMode;           /*交换机模式 0-自动 1-手动*/
	BYTE TOEFlag;              /*TOE加速，0xa5时表示不启用，其它为启用*/
	BYTE Reservel[14];		   /*保留字节并字节对齐*/
	BYTE ExternIP[16];            /* 外部IP地址 2018.3.6 add */
	BYTE ExternPortStatus;        /* 外部客户端端口映射状态 1:Active 0:Inactive 2018.3.6 add */
	BYTE ExternWebPortStatus;     /* 外部Web端口映射状态 1:Active 0:Inactive 2018.3.6 add */
	BYTE ExternMobilePortStatus;  /* 外部手机端口映射状态 1:Active 0:Inactive 2018.3.6 add */
	BYTE ExternRtspPortStatus;    /* 外部Rtsp端口映射状态 1:Active 0:Inactive 2018.3.6 add */
    BYTE ExternHttpsPortStatus;   /* 外部Https端口映射状态 1:Active 0:Inactive 2018.3.6 add */
	BYTE reserve2;
	BYTE useUPnPStrategy;		/* 启用UPNP策略控制 */
	BYTE UPnPAutoSwitch;		/* 控制UPnP映射方式        1 auto 0 manual */
	UINT ClientExtPort;           /*客户端外网端口号*/
    UINT WebExtPort;              /*Web外网端口号*/
    UINT MobileExtPort;           /*手机外网端口*/
    BYTE UseUPNPsingle[16];
	UINT HttpsIntPort;       /* https内部端口 */
    UINT HttpsExtPort;       /* https外部端口 */

}RSNet_NetworkBaseSet_t;

typedef struct 
{
	UINT StructSize;

	BYTE Identity[32]; 
	BYTE Password[32];
	BYTE EapolVersion;  /*1 or 2 */
	BYTE TrapEnable;        /* (0,disable, 1 enable) */
	BYTE HasCaCrt; // 是否有CA证书 有则1，无则0 给web判断使用
	BYTE HasCliCrt; // 是否有客户端证书 有则1，无则0 给web判断使用
	BYTE HasCliPem; // 是否有客户端私钥 有则1，无则0 给web判断使用
	BYTE DelFile; // 是否要删除某个文件 不删则0 1则CA 2删客户端证书 3删客户端私钥 给服务端
	BYTE UpFile;  // 是否要更新某个文件 不更则0 1则CA 2则客户端证书 3则客户端私钥 给服务端
	BYTE reserve1; // 保留字段（用于对齐）
	UINT FileLen; // 文件大小
	BYTE FileBuff[19<<10]; // 上传文件内容缓冲（假设文件<=90k），结构体总大小要小于100k
	BYTE reserve[16];    // 8字节对齐 
}RSNet_IEEE_8021X_t;


//sub_bitrate, mobile_bitrate
typedef enum{
	RS_SubBitrate_8	= 0,
	RS_SubBitrate_16,
	RS_SubBitrate_24,
	RS_SubBitrate_32,
	RS_SubBitrate_48,
	RS_SubBitrate_64,
	RS_SubBitrate_80,
	RS_SubBitrate_96,
	RS_SubBitrate_128,
	RS_SubBitrate_160,
	RS_SubBitrate_192, //10
	RS_SubBitrate_224,
	RS_SubBitrate_256,	
	RS_SubBitrate_320,	
	RS_SubBitrate_384,	
	RS_SubBitrate_448,	
	RS_SubBitrate_512,	
	RS_SubBitrate_768,	
	RS_SubBitrate_1024,	
	RS_SubBitrate_1536, //19
	RS_SubBitrate_2048,
	RS_SubBitrate_3072,
	RS_SubBitrate_4096,
	RS_SubBitrate_5120,
}RS_SubBitrate_e;

//网传子码流配置
typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; //通道掩码
	//子码流
    int sub_bitrate;
	
	BYTE sub_video; 	/* 是否传输子码流,<RS_Close, RS_Open>*/ 

	/*RS_Encode720P，
	  RS_EncodeD1，
	  RS_EncodeHD1,
	  RS_EncodeCIF*/
	BYTE sub_resolution; //DVR为CIF，IPC为D1，暂不提供修改

	/*PAL = 1~25, NTSC = 1~30帧,
	  只容许一个通道帧率, 其他通道为PAL=1~5, NTSC=1~6
	  选项对应侦数，没有0值*/ 
	BYTE sub_fps;  

	BYTE sub_audio;/*子码流录音:<RS_Close, RS_Open>*/
	
	BYTE Ipc_state; //ipc在线状态
	BYTE ResolutionType; // 0:720p 1:D1
	BYTE VBR;
	/*IPC使用*/
	BYTE BitrateType; /* 0 :定码率1:变码率2: 定质量 3: QVBR*/
	BYTE VideoQuality; /* 图像质量0: 最差1:更差2:差3:好4:更好5:最好*/
	BYTE IFrameInterval; /* I 帧间隔范围【1-100  】 */
	unsigned short CustomSubBitrate; /* 自定义码率 */
	/*IPC使用 END */
}RSNet_SoleSubStreamSet_t;

//网传手机码流
typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; //通道掩码

	//手机码流
    int mobile_bitrate;

	BYTE mobile_video; 	/* 是否传输子码流,<RS_Close, RS_Open>*/ 

	/*RS_Encode720P，
	  RS_EncodeD1，
	  RS_EncodeHD1,
	  RS_EncodeCIF*/
	BYTE mobile_resolution;/*PS:暂时只能为CIF, 暂不提供修改*/

	/*PAL = 1~25, NTSC = 1~30帧,
	  只容许一个通道帧率, 其他通道为PAL=1~5, NTSC=1~6
	  选项对应侦数，没有0值*/ 
	BYTE mobile_fps;  

	BYTE mobile_audio; /* 是否编制音频,<RS_Close, RS_Open>*/

	BYTE Ipc_state; //ipc在线状态
	/*IPC使用*/
	BYTE BitrateType; /* 0 :定码率1:变码率2: 定质量 3: QVBR*/
	BYTE VideoQuality; /* 图像质量0: 最差1:更差2:差3:好4:更好5:最好*/
	BYTE IFrameInterval; /* I 帧间隔范围【1-100  】 */
	unsigned short CustomSubBitrate; /* 自定义码率 */
	/*IPC使用 END */
	BYTE reserve[2];
}RSNet_SoleMobileStreamSet_t;

//honeywell frame rate only
typedef enum
{
    FrameRate_4, // 0
    FrameRate_5,
    FrameRate_8,
    FrameRate_10,
    FrameRate_12,
    FrameRate_15, // 5
    FrameRate_20,
    FrameRate_25,
    FrameRate_30 // 8
} FrameRate_e;

typedef struct
{
    WORD w;
    WORD h;
}TI_IPC_SResolute;

typedef struct
{
    TI_IPC_SResolute r1;
    TI_IPC_SResolute r2;
}TI_IPC_DResolute;

typedef struct
{
    TI_IPC_SResolute r1;
    TI_IPC_SResolute r2;
    TI_IPC_SResolute r3;
}TI_IPC_TResolute;

#define MAX_RESOLUTION_NUM 8
typedef struct
{
    BYTE steamnum; // 0 - 单码流 1-双码流 2-三码流
    BYTE resindx;  // 分辨率设置的索引
    BYTE reserve1[3];
    BYTE singleResNum;
    BYTE doubleResNum;
    BYTE triResNum;
    TI_IPC_SResolute sr[MAX_RESOLUTION_NUM]; // 单码流分辨率范围
    TI_IPC_DResolute dr[MAX_RESOLUTION_NUM]; // 双码流分辨率范围
    TI_IPC_TResolute tr[MAX_RESOLUTION_NUM]; // 三码流分辨率范围
}TI_IPC_Resolute;

/* HonneyWell定制码流 */
typedef struct
{
    UINT StructSize;
    UINT ChannelMask;
    BYTE StreamMode;	/*码流模式:0为单码流，1为双码流*/
    BYTE RefreshRate;	/*刷新频率，0:60HZ，1:50HZ*/
    BYTE Resolution;	/*ResRange的索引值*/
    BYTE MainFps;		/*主码流帧率对应FrameRange的索引值*/
    BYTE SubFps;		/*子码流帧率对应FrameRange的索引值*/
    BYTE Audio:1;  		/*音频开关: 0-关，1-开*/
    BYTE TIFlag:1;      /*标识是否为TI设备: 1-是, 0-否*/
    BYTE reserved:6;
    WORD MainBit;		/*主码流比特率*/
    WORD SubBit;		/*子码流比特率*/
    WORD FrameRange[3];	/*[0]为主码流，[1]为子码流，[2]为手机码流，按位取，对应FrameRate_e*/
    TI_IPC_Resolute ResRange;/*码流范围*/
}RSNetSZ_SoleStreamset_t;

//DDNS配置

//ServerAddr
#define RS_DDNS_MYQ_SEE     0
#define RS_DDNS_LTSCCTV     1
#define RS_DDNS_SystemPort  2
#define RS_DDNS_3322        3
#define RS_DDNS_DYNDNS      4
#define RS_DDNS_EASTERNDNS  5
#define RS_DDNS_NEWDDNS     6
#define RS_DDNS_NIGHTOWLDVR 7
#define RS_DDNS_LOREXDDNS   8

typedef struct {
	UINT StructSize; //该结构体大小

    /*HOST名字，最大16字节*/
    BYTE HostName[MaxNameLen];
    /*用户名，最大16字节*/
    BYTE UserName[MaxNameLen];
    /*用户密码，最大8字节*/
    BYTE UserPW[MaxNameLen];
	/*每一个bit  对应一种DDNS ,1:当前使用,0:当前没有使用
	  一般情况下，DDNS地址选项并非全开，
	 仅在客户需求版本时，打开其自己的DDNS
	 此位用作显示或隐藏DDNS选项*/
    UINT DDNSUseFlag;
    /*服务器地址选择*/
    BYTE ServerAddr;
    /*DDNS启用标识，<RS_Close, RS_Open>*/
    BYTE UseDDNS;
    BYTE P2pState;      //设备p2p连接状态(中性中文)
    BYTE CommaxUseLoginFlag;

	BYTE DDNSID[12];
    BYTE P2pKeyID[MaxNameLen]; //P2P ID(针对中文杭州威威)
    UINT extendDDNS;    //扩充DDNS长度,之前定义的32个不变
	BYTE IpType;          /*暂为luxvision客户专用，0为IPV4，1为IPV6*/
	BYTE reserved[3];
	BYTE UserUrl[128];
}RSNet_DDNSSet_t;


//PPPOE配置
typedef struct {
	UINT StructSize; //该结构体大小

    /*PPPOE用户名*/
    BYTE PPPOEuser[MaxNameLen];
    /*PPPOE用户密码*/
    BYTE Password[MaxNameLen];
    /*DNS1*/
    BYTE dns1[4];   // 设置路由上的PPPOE
    /*DNS2*/
    BYTE dns2[4];
}RSNet_PPPoESet_t;




//Email配置
/* Email配置页面参数结构*/
//intervaltime
#define RS_IntervalTime_60  0
#define RS_IntervalTime_180 1
#define RS_IntervalTime_300 2
#define RS_IntervalTime_600 3
typedef struct {
	UINT StructSize; //该结构体大小

    /*SMTP服务器*/
    BYTE SMTP[MaxNameLen];
    /*发件人地址*/
    BYTE SendEmail[MaxNameLen];
    /*发件人密码*/
    BYTE SendEmailPW[MaxNameLen];
    /*收件人地址, 现时只有第一个收件人地址*/
    BYTE RecvEmail[3][MaxNameLen];
    /*端口号*/
    UINT Port;
    /*是否使用email,<RS_Close, RS_Open>*/
    BYTE EmailSwitch;
    /*SSL开关，<RS_Close, RS_Open>*/
    BYTE SSLSwitch;
    /*邮件发送间隔*/
    BYTE intervaltime;
	BYTE kgCheck;
	BYTE usename[MaxNameLen];
}RSNet_EmailSet_t;

typedef struct {
	UINT StructSize; //该结构体大小
	BYTE EnReceivePasswd[3]; /*是否支持接收密码 0--不支持, 1--支持 2018.6.28 add */
	BYTE StreamType;//0--mainstream;1--substream

	/*SMTP服务器*/
	BYTE SMTP[128];
	/*发件人地址*/
	BYTE SendEmail[128];
	/*发件人密码*/
	BYTE SendEmailPW[128];
	/*收件人地址, 现时只有第一个收件人地址*/
	BYTE RecvEmail[3][128];
	/*端口号*/
	UINT Port;
	/*是否使用email,<RS_Close, RS_Open>*/
	BYTE EmailSwitch;
	/*SSL开关，<RS_Close, RS_Open>*/
	BYTE SSLSwitch;
	/*邮件发送间隔*/
	BYTE intervaltime;
	BYTE kgCheck;
	BYTE usename[128];
}RSNet_NewEmailSet_t;
typedef struct {
	UINT StructSize; 	//该结构体大小
	int MotionScheduleHour[16][8];
	int AlarmScheduleHour[16][8];
	int EventScheduleHour[8];
	BYTE reservel[4];
	int MotionScheduleHourEx[32][8];
	int AlarmScheduleHourEx[32][8];
}RSNet_EmailScheduleSet_t;

typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	
	BYTE  EmailScHalfHour[8][48];  // 和录像计划表示一致
}RSNetNew_SoleEmailScheduleset_t;

typedef struct {
	UINT StructSize; 	//该结构体大小

	BYTE  EventScHalfHour[8][48];     // 7days and 48 halfhours
    /* EventScHalfHour[8]，周日，周一~周六: 0~6，第7位为保留位*/ //2016.03.09
    // 2013.03.09
	UINT  EventScHalfHourExt[8][48];  // 7days and 48 halfhours 
	/* EventScHalfHourExt[8]，周日，周一~周六: 0~6，第7位为保留位*/
}RSNetNew_EmailScheduleset_t;



//Mobile配置
typedef struct {
	UINT StructSize; //该结构体大小
	//手机设置
    BYTE MobileUserName[MaxNameLen];/* 用户名，最大16字节*/    
    BYTE MobileUserPwd[MaxNameLen];/* 用户密码，最大16字节*/     
    UINT MobilePort; /* 服务端口*/ 
	BYTE reservel[4];
}RSNet_MobileSet_t;


//Router Lan 口配置
typedef struct {
	UINT StructSize; //该结构体大小
    BYTE IPAddr[4];  /* IP地址 */
    BYTE NetMask[4]; /* 子网掩码*/
    BYTE SSID[MaxNameLen];  /* 无线网络标识 */    
    BYTE Passwd[MaxNameLen];/* 密码 */     
	BYTE SecureType;        /* 安全选项 */
	BYTE WiFiChannel; /*无线通道选项*///add by st 20120509
	BYTE WpaAlgorithm;
	BYTE reservel[17];
}RSNet_RouterLanSet_t;

//移动侦测配置

//Sensitivity
#define RS_Sensitivity_8 0
#define RS_Sensitivity_7 1
#define RS_Sensitivity_6 2
#define RS_Sensitivity_5 3
#define RS_Sensitivity_4 4
#define RS_Sensitivity_3 5
#define RS_Sensitivity_2 6
#define RS_Sensitivity_1 7

//AlarmOutTime
//对应Motion,Abnormal,IOAlarm
#define RS_AlarmTime_10s 0
#define RS_AlarmTime_20s 1
#define RS_AlarmTime_40s 2
#define RS_AlarmTime_60s 3
#define RS_AlarmTime_30s 4
#define RS_AlarmTime_1min 5
#define RS_AlarmTime_2min 6


//BuzzerMooTime
//对应Motion,Abnormal,IOAlarm
#define RS_BuzzerTime_Off 0
#define RS_BuzzerTime_10s 1
#define RS_BuzzerTime_20s 2
#define RS_BuzzerTime_40s 3
#define RS_BuzzerTime_60s 4


//录像延时 RecordDelayTime
//对应Motion,IOAlarm
#define RS_RecordDelayTime_10   0
#define RS_RecordDelayTime_30   1
#define RS_RecordDelayTime_1Min 2
#define RS_RecordDelayTime_2Min 3
#define RS_RecordDelayTime_5Min 4

#define MAX_ALARMOUT_NUM 16

typedef struct
{
    S16 x;
    S16 y;
    S16 w;
    S16 h;
}RSNet_Rect_t;

/* 移动侦测页面参数结构 */
typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 	//通道掩码

	/*侦测8个等级*/
	BYTE Sensitivity;
	/*是否启用移动侦测<RS_Close, RS_Open>*/
	BYTE ChnSwitch;
	/*Send Email 开关<RS_Close, RS_Open>*/
	BYTE SendEmail;
	/*蜂鸣器鸣叫时间*/
	BYTE BuzzerMooTime;
	/*Record Channel, 触发通道录像，按位记录*/
	UINT RecordChannel;
	/*录像延时时间*/
	BYTE RecordDelayTime;
	/*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE Record;
	/*Show Message <RS_Close, RS_Open>开关*/
	BYTE ShowMessage;
	/*FullScreen 开关 报警全屏<RS_Close, RS_Open>*/
	BYTE FullScreen;
	/*区域设置，180个区域，用32个字节表示，每位表示一个区域*/
	BYTE RegionSetting[32];	/* LoginRsp MotionMode字段:0,使用当前字段*/
	/* 宏块行数  只有 LoginRsp MotionMode==2时,这个值才是有效的*/
	BYTE MbRow; 
	/* 宏块列数 只有 LoginRsp MotionMode==2时,这个值才是有效的*/
	BYTE MbCol;
	/*Alarm Out 开关<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*报警输出时间*/
	BYTE AlarmOutTime;
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	/*区域设置，200个区域，用32个字节表示，每位表示一个区域*/
    //BYTE RegionSetting3531[200];  /* LoginRsp MotionMode字段:1或2,使用当前字段*/
    union {
        struct {
            BYTE RegionSetting3531[200];  /* LoginRsp MotionMode字段:1或2,使用当前字段*/
        }BlockRegion;
        struct
        {
            BYTE MotionNum[4];  /* 对应区域是否启用，为1启用，为0不启用 */
            RSNet_Rect_t Rect[4];
            BYTE Sensitivities[4]; /*11个等级:0-高，1-较高，2-中，10:最低*/
            UINT  RectMaxNum;    /*motion max rect num 2016.10.19 add*/			
        }RectRegion;
    };
	
	BYTE FtpLink;			/*FTP联动 开关*/
	BYTE PushSwitch;    /*是否开启移动侦测报警推送, 0: close; 1: open.*/
	BYTE WirelessAlarmSensor; /*外部sensor 触发 使能0, 不使能, 1. 使能*/
	BYTE LlluminationRing; /* 光照环0, 不使能, 1. 使能   */
	BYTE AudioAlert; /* 音频警报0, 不使能, 1. 使能 */
	BYTE AudioSelect; /* 报警声音选择 0, Doorbell 1.Ringtone, 2.Siren */
	BYTE AlarmDurationTime;/*0: 10s , 1: 30s, 2: 60s*/
	BYTE CloudNotify; /*Urmet专用，报警云上传使能控制*/
	BYTE Pirflag;
	BYTE SensitivityExNight;
	BYTE onlySDexit;
	BYTE sendToFTP;/*发送截图到FTP，0：不使能；1：使能*/
	BYTE LightLinkage;/*白光灯motion联动开关 0:不联动 1:联动*/
    BYTE LoudSpeaker;/*扬声器开关 0:关 1:开*/
	BYTE Distance;	/*PIR 距离*/
	BYTE PageBit;//BIT_0:NVR LOREX use,...
	BYTE FtpVideoLink;	/*FTP录像联动 开关*/
	BYTE CloudPicUpload; /* 云存储视频上传 */
	BYTE CloudVideoUpload;
	BYTE FTPUpload; 		   /*FTP Upload 开关*/
	BYTE Reservel[20];
	UINT RecordChannel_EX[8];	
	/*取bit位:3表示一个通道最多3个报警输出,每个报警输入触发后可以联动到
	32*8= 256路的任何通道报警输出*/
	BYTE AlarmOutManagerEx[3][32];
}RSNet_SoleMotionSet_t;

/* 遮挡告警页面参数结构 */

typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 	//通道掩码

	/*侦测8个等级*/
	BYTE Sensitivity;
	/*是否启用移动侦测<0:RS_Close, 1:RS_Open>*/
	BYTE ChnSwitch;
	/*Send Email 开关<0:RS_Close, 1:RS_Open>*/
	BYTE SendEmail;
	/*蜂鸣器鸣叫时间*/
	BYTE BuzzerMooTime;
	/*Record Channel, 触发通道录像，按位记录*/
	UINT RecordChannel;
	/*录像延时时间*/
	BYTE RecordDelayTime;
	/*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE Record;

	BYTE AlarmOut;	/* 0. 不触发IO 输出, 1. 触发IO 输出edit by jazhu */
	

	BYTE Reservel[41];
}RSNet_OcclusionSet_t;

//异常报警配置
/*
   异常报警三大项,按通道形式传输
0：videoloss
1:HddInvalidAlarm
2:HddNoSpaceAlarm
*/
typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT EventTypeMask; 	//通道掩码

	//异常报警是否开启 RS_Close, RS_Open
	BYTE Enable;
	/*蜂鸣器鸣叫时间*/
	BYTE BuzzerMooTime;

	/*是否显示标志位 <RS_Close, RS_Open>开关*/
	BYTE ShowMessage;
	/*Send Email 开关<RS_Close, RS_Open>*/
	BYTE SendEmail;

	/*Alarm Out 总开关<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*报警输出时间*/
	BYTE AlarmOutTime;	
	BYTE UrmetCloudNotify; /*Urmet专用，报警云上传使能控制*/
	BYTE reservel[1];
	/*如果有多个继电器时Alarm Out 开关<RS_Close, RS_Open>*/
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];

	BYTE AlarmOutManagerEx[3][32];
}RSNet_SoleAbnormalSet_t;


//IO报警配置

//IoAlarmSet
#define RS_IOAlarm_NO    0
#define RS_IOAlarm_NC    1
#define RS_IOAlarm_Close 2

typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码

	//IO口报警状态
	BYTE IoAlarmSet;
	/*Alarm Out 总开关<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*报警输出时间*/
	BYTE AlarmOutTime;
	/*蜂鸣器鸣叫时间*/
	BYTE BuzzerMooTime;
	/*Record Channel, 触发通道录像，PS:按位记录, 1:触发, 0:不触发*/
	UINT RecordChannel;
	/*录像延时*/
	BYTE RecordDelayTime;
	/*是否显示标志位 <RS_Close, RS_Open>开关*/
	BYTE ShowMessage;
	/*Send Email 开关<RS_Close, RS_Open>*/
	BYTE SendEmail;
	/*FullScreen 开关 报警全屏<RS_Close, RS_Open>*/
	BYTE FullScreen;
	/*如果有多个继电器时Alarm Out 开关<RS_Close, RS_Open>*/
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	/*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE Record;
	/*Yiguang 2012.02.16 报警源选择,0-IPC;1-本地端*/
	BYTE AlarmIO;
	BYTE FtpLink;			/*FTP联动 开关*/
	BYTE UrmetCloudNotify; /*Urmet专用，报警云上传使能控制*/	
	UINT RecordChannel_EX[8];
	BYTE PushSwitch;
	BYTE sendToFTP;/*发送截图到FTP，0：不使能；1：使能*/
	BYTE FtpVideoLink;	   /*FTP录像联动 开关*/
	BYTE CloudPicUpload; /* 云存储视频上传 */
	BYTE CloudVideoUpload;
	BYTE FTPUpload;            /*FTP Upload 开关*/
	BYTE reserved[58];

}RSNet_SoleIOAlarmSet_t;

typedef struct {
	/*I/O状态报警,0-常开，1-常关，2-关闭*/
	BYTE IoAlarmSet;	
	/*报警输出时间*/
	BYTE AlarmOutTime;
	/*蜂鸣器鸣叫时间*/
	BYTE BuzzerMooTime;
	/*录像延时*/
	BYTE RecordDelayTime;
	/*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE Record;
	/*bit0-ShowMessage, 1-SendEmail, 2-FullScreen, 3-ftp upload,*/
	BYTE LinkFlag;
	BYTE reserve[2];
	/*取bit位:每个报警输入可以联动到32*8= 256路的任何通道录像*/
	BYTE RecordChannel[32];
	/*取bit位:3表示一个通道最多3个报警输出,每个报警输入触发后可以联动到
	32*8= 256路的任何通道报警输出*/
	BYTE AlarmOutManager[3][32];
	/*AlarmOut开关*/
	BYTE AlarmOut;
	BYTE reserved2[15];
}IOAlarmSet_t;

typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	IOAlarmSet_t io[3]; //0-表示本地io; 1-表示ipc的io输入1; 2-表示ipc的io输入2
	BYTE AlarmLinkPtzEnable[3][32];       /* only for zip 当前通道联动开关 取bit位:每个报警输入可以联动到32*8= 256路的任何通道录像 2018.3.6 add, 2018.4.17 changed  */
	BYTE LinkagePtzPresetIndex[3][256];   /* only for zip 当前预置点 2018.3.6 add, 2018.4.17 changed */
	BYTE LinkagePtzPatrolIndex[3][256];   /* only for zip 当前巡航线 2018.3.6 add, 2018.4.17 changed */
	BYTE LinkagePtzPatternIndex[3][256];  /* only for zip 当前巡迹线 2018.3.6 add, 2018.4.17 changed */
	BYTE LinkagePtzMode[3][256];          /* only for zip 联动方式，0-preset，1-partol，2-pattern 2018.2.6 add, 2018.4.17 changed */
}RSNet_NewSoleIOAlarmSet_t;


/*模式计划页面参数,仅EyeHome-Host版本有效*/
/*最大支持地域数目8个*/
#define MAX_AREA_NUMBER         8
/*模式的控制方式,0-计划表控制;1-手动控制*/
//ControlWay
#define RS_SCHEDULE_CONTROL   	0
#define RS_MANUAL_CONTROL	  	1

/*模式为手动控制时的模式,0-离家模式;1-睡眠模式;2-在家模式;注意:当模式的控制方式为计划表控制时,不需处理此值*/
//ControlMode
#define RS_MANUAL_LEAVEHOME		0
#define RS_MANUAL_SLEEP			1
#define RS_MANUAL_ATHOME		2

typedef struct {
	UINT StructSize;
    BYTE ControlWay;            /*控制方式,0-计划表控制,1-手动控制*/
    BYTE ControlMode;           /*手动控制时的模式,0-离家模式;1-睡眠模式;2-在家模式*/
	BYTE ModeSchedule[8][24];   /*计划表控制时的模式,0-离家模式;1-睡眠模式;2-在家模式*/
	BYTE AreaSwitch[4];         /*模式设置,字节0-离家模式;1-睡眠模式;2-在家模式;每个字节的0到7位分别表示地域1到8的开关状态,0-关;1-开*/   	
	BYTE Reserved[6];
}RSNet_TELALARM_AreaParameter_t;

/*地域参数设置,设置每个地域的参数,系统最大支持8个地域,仅EyeHome-Host版本有效*/
typedef struct {
	UINT StoreSize;
	BYTE Name[20];
	BYTE AlarmOut;				/*Alarm Out 总开关<RS_Close, RS_Open>*/
	BYTE AlarmOutTime[8];		/*报警输出时间*/
	BYTE BuzzerMooTime[8];		/*蜂鸣器鸣叫时间*/
	BYTE DialNumber[8];			/*拨打的号码组*/
	UINT RecordChannel[8];		/*Record Channel, 触发通道录像，PS:按位记录, 1:触发, 0:不触发*/
	UINT FullScreen[8];			/*FullScreen 开关 报警全屏<RS_Close, RS_Open>*/
	BYTE RecordDelayTime[8];	/*录像延时*/
	BYTE ShowMessage;			/*是否显示标志位 <RS_Close, RS_Open>开关*/
	BYTE SendEmail;				/*Send Email 开关<RS_Close, RS_Open>*/
	BYTE Record;				/*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE Reserved[4];
}RSNet_TELALARM_SoleAreaParameter_t;

/*探测器参数设置,仅EyeHome-Host版本有效*/
#define MAX_WIRE_SENSOR_NUMBER  4       /*最多支持的有线探测器的数目*/
#define MAX_WIRELESS_SENSOR_NUMBER  12  /*最多支持的无线探测器的数目*/

#define RS_TRIGGLE_NC    0
#define RS_TRIGGLE_NO    1

#define RS_ALARMTYPE_DOOR   0           /*门磁触发*/
#define RS_ALARMTYPE_RAY    1           /*红外触发*/
#define RS_ALARMTYPE_SILENT 2           /*无声报警*/
#define RS_ALARMTYPE_FIRE   3           /*火警报警*/
#define RS_ALARMTYPE_GAS    4           /*气感报警*/

typedef struct {
	UINT StoreSize;
    BYTE Triggle;                   /*触发特性*/
    BYTE AlarmType;                 /*警情类型*/
    BYTE Area;                      /*所属防区*/
    BYTE AlarmDisplay;              /*是否显示警情*/
	BYTE Reserved[4];
}RSNet_TELALARM_SoleWireSensor_t;

typedef struct {
	UINT StoreSize;
    BYTE LearnCode;                 /*是否已经对码*/
    BYTE AlarmType;                 /*警情类型*/
    BYTE Area;                      /*所属防区*/
    BYTE AlarmDisplay;              /*是否显示警情*/
	BYTE Reserved[4];
}RSNet_TELALARM_SoleWirelessSensor_t;


//智能分析
/****************  huoxiaolong20110512  *****************************/

typedef struct{
	UINT StructSize;//该结构体大小
	/*轨迹长度，*/
	BYTE ContrailLength;
    BYTE reservel[3];
}RSNet_IntelligentSet_t;



typedef struct{
	UINT StructSize; 	//该结构体大小
	BYTE AlarmOut;
	/*Show Message 开关*/
	BYTE ShowMessage;
	/*Send Email 开关*/
	BYTE SendEmail;
	/*FullScreen 开关*/
	BYTE FullScreen;
	/*Record Channel*/
	BYTE Record;
	/*Record Delay Time*/
	BYTE RecordDelayTime;/*录像延时，延时时间:30s，1min,2min,5min*/
	BYTE BuzzerMooTime;/*蜂鸣器鸣叫，鸣叫时间:0,10，20，40，60s*/
	BYTE AlarmOutTime;/*报警输出，输出时间:10，20，40，60s*/
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	UINT RecordChannel;
	BYTE reservel[4];

}RSNet_SoleIntAlarmSet_t;


#define RS_MAX_RULENUM  4

#define RS_Intelligent_Tripwire  0
#define RS_Intelligent_Perimeter 1
#define MAX_PERIMETER_POINT 8
#define MAX_TRIPWIRE  2
typedef struct{
	UINT StructSize; 	//该结构体大小
	/*使能开关*/
	BYTE RuleEnable;
	/*规则类型，0-绊线，1-周界*/
	BYTE RuleType;
	/*方向限制*/
	BYTE Direction;
	/*周界限制角度值*/
	short Forbidden;
	BYTE reservel[3];
}RSNet_RuleNum_t;

//点的结构体added by zgm 20110118
typedef struct{
	short x;//X轴坐标
	short y;//Y轴坐标
	short RuleNum;//所属规则号
	short ForbiddenDirection;//方向限制角度
	BYTE reservel[4];
}RSNet_Point_t;

typedef struct{
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	/*功能开启，0-关闭，1-打开*/
	BYTE Enable;
	BYTE reservel[3];
	RSNet_SoleIntAlarmSet_t IntAlarm;
	/*绊线*/
	RSNet_Point_t TriWire[2 * RS_MAX_RULENUM];//add 20110118
	/*周界*/
	RSNet_Point_t Perimeter[MAX_PERIMETER_POINT * RS_MAX_RULENUM];//add 20110118
	/*每个通道规则数*/
	RSNet_RuleNum_t RuleNumber[RS_MAX_RULENUM];
	//RSNet_SoleIntAlarmSet_t IntAlarm;
}RSNet_SoleIntelligentSet_t;

//level
#define  RS_level_1 0
#define  RS_level_2 1
#define  RS_level_3 2
#define  RS_level_4 3
#define  RS_level_5 4

//Avdtype
#define RS_MAXAVDTYPE_NUM   8

#define RS_Avdtype_BrightAbnormal   0
#define RS_Avdtype_ClarityAbnormal  1
#define RS_Avdtype_ColorAbnormal    2
#define RS_Avdtype_NoiseAbnormal    3
#define RS_Avdtype_MenuFreeze       4
#define RS_Avdtype_Nosignal         5
#define RS_Avdtype_StageChange      6
#define RS_Avdtype_Interfere        7
#define RS_Avdtype_PtzLoseControl   8
typedef struct{
	UINT StructSize; 	//该结构体大小
	/*AVD类型开关*/
	BYTE TypeEnable;
	/*灵敏度5 个等级1-最低，5-最高*/
	BYTE level;
	BYTE reservel[2];
}RSNet_Avdtype_t;   




typedef struct{
	UINT StructSize; 	//该结构体大小
	/*Alarm Out 开关*/
	BYTE AlarmOut;
	/*Show Message 开关*/
	BYTE ShowMessage;
	/*Send Email 开关*/
	BYTE SendEmail;
	/*FullScreen 开关*/
	BYTE FullScreen;
	/*Record Channel*/
	BYTE Record;
	/*Record Delay Time*/
	BYTE RecordDelayTime;/*录像延时，延时时间:30s,1min,2min,5min*/
	BYTE AlarmOutTime;/*报警输出，输出时间:10，20，40，60s*/
	BYTE BuzzerMooTime;/*蜂鸣器鸣叫，鸣叫时间:0，10，20，40，60s*/
	UINT RecordChannel;
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	BYTE reservel[4];

}RSNet_SoleAvdAlarmSet_t;



typedef struct{
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	/*通道开关，0-关闭，1-打开*/
	BYTE Enable;
	BYTE reservel[3];
	/*通道轮训时间，最小为1秒，最大为60秒*/
	ULONG  RotateTime;
	RSNet_Avdtype_t Avdtype[RS_MAXAVDTYPE_NUM];
	RSNet_SoleAvdAlarmSet_t AvdAlarm;
}RSNet_SoleIntAvdSet_t;
//暂缺

//MediaConType
#define RSPlat_UDP 0
#define RSPlat_TCP 1
#define RSPL_MAXNAMELEN 36

#define RSPL_FORM_SHOW *(UINT*)"PLEn"
#define RSPL_FORM_HIDE 0x00000000
typedef struct{
	UINT StructSize;   		//该结构体大小
	
	//RsPlatform
	BYTE PuID[RSPL_MAXNAMELEN];
	BYTE PlatformAddr[RSPL_MAXNAMELEN]; //接入服务器地址
	UINT PlatformPort;     //接入服务器端口
	BYTE PlatformSelect;
	BYTE PlatformEnable;
	BYTE MediaConType;     //0(udp) 1(tcp)
	BYTE reservel[1];
	UINT PlatFormShowTag; //是否显示平台参数页面
}RSNet_PlatformSet_t;

//HUAWEI_Platform
#define RSPL_STATUS_OFFLINE  	0
#define RSPL_STATUS_ONLINE 		1

typedef struct{
	UINT StructSize;   		//该结构体大小
	
	BYTE Enable;			/* RS_Open, RS_Close*/
	BYTE CenterStatus;		/*RSPL_STATUS_OFFLINE, RSPL_STATUS_ONLINE*/

	BYTE ProtocolType;		/* RSPlat_UDP, RSPlat_TCP */
	BYTE DelayTime;			/*延时连接时间 0～100 s */

	BYTE MainDevID[24];
	BYTE CenterIP[16];
	UINT CenterPort;
}RSNet_HuaweiPlatformSet_t;

typedef struct{
	UINT StructSize;   		//该结构体大小
	UINT ChannelMask;		//通道掩码
	
	BYTE LensEnable;
	BYTE AlarmInEnable;
	BYTE AlarmOutEnable;
	BYTE SerialEnable;

	BYTE LensStatus;		/*RSPL_STATUS_OFFLINE, RSPL_STATUS_ONLINE*/
	BYTE AlarmInStatus;		/*RSPL_STATUS_OFFLINE, RSPL_STATUS_ONLINE*/
	BYTE AlarmOutStatus;	/*RSPL_STATUS_OFFLINE, RSPL_STATUS_ONLINE*/
	BYTE SerialStatus;		/*RSPL_STATUS_OFFLINE, RSPL_STATUS_ONLINE*/
	
	BYTE Reservel[8];
	
	BYTE LensID[24];
	BYTE LensName[48];

	BYTE AlarmInID[24];
	BYTE AlarmInName[48];
	
	BYTE AlarmOutID[24];
	BYTE AlarmOutName[48];
	
	BYTE SerialID[24];
	BYTE SerialName[48];
}RSNet_SoleHuaweiPlatformSet_t;


//编码配置
//main_resolution, sub_resolution
#define RS_EncodeD1   0
#define RS_EncodeHD1  1
#define RS_EncodeCIF  2
#define RS_Encode720P 3
#define RS_Encode960P 4

//new define of resolution mode (added 2014-05-13)
typedef enum
{
    RSMode_D1 = 0,          //D1模式
    RSMode_D1_960H,         //D1和960H模式
    RSMode_CIF,             //纯CIF模式
    RSMode_CIF_DISABLE_FPS, //纯CIF但是不禁用帧率
    RSMode_720P,            //纯720P模式
    RSMode_720P_960P,       //720P和960H
    RSMode_1080P,           //纯1080P模式
    RSMode_720P_1080P,      //720P和1080P模式
    RSMode_VI_AUTO_DETECT,  //目前只支持720P和960H自动识别
    RSMode_1080P_720P_WX,   //IE显示1080P,720P和WD1,WHD1,WCIF
    RSMode_720P_WX,         //IE显示720P和WD1,WHD1,WCIF
    RSMode_720P_AxB,        //720P和960*480 960*240 480*240.(lorex专用)
    RSMode_1080PCIF_720P_WX,//IE显示1080PCIF,720P和WD1,WHD1,WCIF
    RSMode_1080P_720P_960H,  //3种分辨率模式均支持，小于或等于所选模式的分辨率均可选    
    RSMode_3W
}ResolutionMode_e;

//main_bitrate
typedef enum{
	RS_MainBitrate_32    =	0,
	RS_MainBitrate_48,	
	RS_MainBitrate_64,	
	RS_MainBitrate_80,	
	RS_MainBitrate_96,	
	RS_MainBitrate_128,	
	RS_MainBitrate_160,	
	RS_MainBitrate_192,	
	RS_MainBitrate_224,	
	RS_MainBitrate_256,	
	RS_MainBitrate_320,	
	RS_MainBitrate_384,	
	RS_MainBitrate_448,	
	RS_MainBitrate_512,	
	RS_MainBitrate_640,	
	RS_MainBitrate_768,	
	RS_MainBitrate_896,	
	RS_MainBitrate_1024 = 17,	
	RS_MainBitrate_1280,	
	RS_MainBitrate_1536,	
	RS_MainBitrate_1792,	
	RS_MainBitrate_2048 = 21,	
	RS_MainBitrate_4096 = 22,	//4M
	RS_MainBitrate_5120 = 23,	//5M
	RS_MainBitrate_6144 = 24,	//6M
	RS_MainBitrate_8192 = 25,	//8M
	RS_MainBitrate_10240 = 26,	//10M
	RS_MainBitrate_12288 = 27,	//12M
	RS_MainBitrate_3072 = 28,   //3M
	RS_MainBitrate_16384= 29,   //16M
}RS_MainBitrate_e;
#define MAX_BITRATE_INDEX 30

/* DVR特定系列产品型号(D98 AHD系列,TVI系列;D99系列), 远端显示的码率选项类型 */
typedef enum
{
    BIT_INVALID = 0,
    BIT_1_2_4,        //1M、2M、4M
    BIT_1_2_4_6,      //1M、2M、4M、6M
    BIT_1_2_4_6_8    //1M、2M、4M、6M、8M
}D9X_Bitrate_Mode_E;

//SWAN 客户定制使用
#define RS_MainBitrate_Normal	RS_MainBitrate_4096;
#define RS_MainBitrate_Good		RS_MainBitrate_5120;
#define RS_MainBitrate_Better	RS_MainBitrate_6144;
#define RS_MainBitrate_Best		RS_MainBitrate_8192;

/* 码流设置页面参数结构 */

typedef struct
{
	UINT StructSize; //该结构体大小

	BYTE ResolutionMode; /*0-D1, 1-960*/
	
	BYTE StreamType;   // 0 main 1 sub
	BYTE reservel[2];
}RSNet_MainStreamSet_t;

typedef struct{
	UINT StructSize; //该结构体大小
	UINT ChannelMask; //通道掩码

	/*主码流: */
    int main_bitrate;
	
	/*
	  RS_Encode720P-720P，
	  RS_EncodeD1-精细，
	  RS_EncodeHD1-丰富，
	  RS_EncodeCIF-普通*/
	BYTE main_resolution;
	
	/* 	单通道录像帧率:
		PAL:1~25 NTSC:30帧
		选项对应侦数，没有0值 
		PAL制总侦数＝400，NTSC制总侦数＝480*/
	BYTE main_fps;	
	
	BYTE main_audio;/*主码流录音:<RS_Close, RS_Open>*/	
	BYTE main_resolution960; 

	BYTE ResolutionType; // 0:720p 1:D1
	BYTE VBR; 
	/*IPC使用*/
	BYTE BitrateType; /* 0 :定码率1:变码率2: 定质量 3: QVBR*/
	BYTE VideoQuality; /* 图像质量0: 最差1:更差2:差3:好4:更好5:最好*/
	unsigned short CustomMainBitrate; /* 自定义码率 */
	BYTE IFrameInterval; /* I 帧间隔范围【1-100  】 */
	/*IPC使用 END */
	BYTE AMRSwitch; /*AMR 编解码开关(DENAVO客户专用). 0:disable, 1:enable*/
}RSNet_SoleMainStreamSet_t;

/* stream */
typedef struct 
{
    BYTE FrameRateMin;/*支持的帧率范围，Min,两项均为0则未填充*/
    BYTE FrameRateMax;/*支持的帧率范围，Max,两项均为0则未填充*/
    WORD DefBitrate; /*save default bitrate*/
    WORD ResolutionWidth;/*支持的分辨率，宽或高为0则未填充*/
    WORD ResolutionHight;/*支持的分辨率，宽或高为0则未填充*/
    UINT BitrateRange;   /*按位取 RS_MainBitrate_e或RS_SubBitrate_e，1:表示支持，0:表示不支持，并且确定相应的区间*/
}RSNetNew_ResolutionRateRange_t;


//录像配置
//RecordMood
#define RS_RecordSchedule 0  //计划表录像
#define RS_RecordAlaways  1  //开机录像
#define RS_RecordManual   2  //手动录像

//PackTime
#define RS_PackTime_15Min 0
#define RS_PackTime_30Min 1
#define RS_PackTime_45Min 2
#define RS_PackTime_60Min 3

//PreRecordTime
#define RS_PreRecordTime_0s  0
#define RS_PreRecordTime_10s 1

typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码

	/*通道的打开关闭，一个通道对应<RS_Close, RS_Open>*/
    BYTE ChnCloseOrOpen;    //Qt ui 通道录像开关
	BYTE RecordStreamMode;  // main,sub    
    BYTE PreRecSwitch;      //Qt ui 通道预录像开关
	BYTE RecordAudioEnable; //0:close 1:open
	RSNetNew_ResolutionRateRange_t Range[8];	/* lorex电池record页面分辨率设置*/
	BYTE Num;/*支持的分辨率个数,最多选择8个*/
	BYTE ResolutionIndex; /* whice one resolution index has been choose to set */
	BYTE ManualRecSwitch;/*Manual_Record*/
	BYTE OffLineRecSwitch;	/* 断网录像开关 */
	BYTE Reserved;
	BYTE EncTypeList;//按位表示,为1时显示	//H.264,H.265,H.264+,H.265+,MJPEG
	BYTE EncTypeVal;
	BYTE pageBit;//bit_0:preRecord,bit_1:resolution,bit_2:encType
}RSNet_SoleRecordSet_t;

typedef struct {
	UINT StructSize; 	//该结构体大小

    BYTE RecordMode;/*录像模式:0-定时录像，1-开机录像，2-手动录像*/
    BYTE PackTime;/*录像打包时间，0-15分钟，1-30分钟，2-45分钟，3-60分钟*/    
    BYTE PreRecordTime;/*预录像，预录时间:0，10s*/
	BYTE RedundanceRec;      //是否冗余录像:0-close 1-open
}RSNet_RecordSet_t;



//录像计划

//hour
/*为0表示不录象，为2表示正常录像，1-报警录像*/
#define RS_NoRecord     0
#define RS_AlarmRecord  1
#define RS_NormalRecord 2

#define RS_NormalScheduleMode 0
#define RS_SmartScheduleMode 1

#define RS_ScheduleResolution_720P	0
#define RS_ScheduleResolution_D1   1
#define RS_ScheduleResolution_CIF  2
typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	
	//MainStream, For MainStream Record Schedule
	int NormalHour[8]; 
	int MotionHour[8];
	int AlarmHour[8];
	int IntelligentHour[8];
	
	//Smart版本
	BYTE SmartScheduleEnable; //1:为有smart功能,反之为没有
	BYTE ScheduleMode; 
	BYTE onlySDexit;
	BYTE PageBit;//Bit_0:是否是Continous模式
	BYTE SmartNormalResolution[8];
	BYTE SmartAlarmResolution[8]; 
	int SmartNormalHour[8]; 
	int SmartAlarmHour[8];
	
	//SubStream, For SubStream Record Schedule
	int SubNormalHour[8]; 
	int SubMotionHour[8];
	int SubAlarmHour[8];
	int SubIntelligentHour[8];
	
	BYTE HalfHour[8][48]; // 7 days and 48 halfhours	
	/* bit 0 为普通录像，bit 1 为动检录像，bit 2 为报警录像，
	 * bit 3 为OSC，bit 4 为LCD，bit 5 为PID   bit 6 为Sensor录像   bit 7 为PIR录像
	 * 对应的bit位为1表示设置，为0表示清零
	 * HalfHour[8]，周日，周一~周六: 0~6，第7位为保留位 //2016.03.09
	 */
	//2016.03.09
	UINT HalfHourExt[8][48]; // 7 days and 48 halfhours
	/* bit 0为HD，bit 1为FD，bit 2为PCC
	 * 对应的bit位为1表示设置，为0表示清零
	 * HalfHourExt[8]，周日，周一~周六: 0~6，第7位为保留位
	 *2018.04.27---与板端数据验证为ipc智能不使用HalfHour字段，只使用HalfHourExt字段
	 *bit 0 为LCD录像，bit 1 为PID录像，bit 2 为OSC录像，
	 * bit 3 为PD，bit 4 为FD，bit 5 为CC
	 *add bit 6 Sound Alarm
	 */		 
	
}RSNet_SoleScheduleSet_t;

//智能录像计划表 Qt v2
typedef struct
{
    UINT StructSize; 	//该结构体大小
    UINT ChannelMask; 	//通道掩码

    BYTE HalfHour[8][48]; // 7days and 48 halfhours
    /* bit 1为PEA录像, bit 2 为AVD录像, bit 3 为OSC录像
     * 对应的bit位为1表示设置，为0表示清零
	 *2018.04.27---与板端数据验证为
	 *bit 0 为LCD录像，bit 1 为PID录像，bit 2 为OSC录像，
	 * bit 3 为PD，bit 4 为FD，bit 5 为CC
     */
}RSNet_SoleIntelliRecSchedule_t;


//系统维护页面
//maintainperiod1
#define RS_EveryDay 0
#define RS_EveryWeek 1
#define RS_EveryMonth 2

//maintainperiod2
#define RS_Monday 		0
#define RS_Tuesday		1
#define RS_Wednesday 	2
#define RS_Thursday		3
#define RS_Friday		4
#define RS_Saturday		5
#define RS_Sunday		6

typedef struct {
	UINT StructSize; 	//该结构体大小

	//自动维护重启
    /*维护的具体时间，时分*/
    BYTE time[4];
    
    BYTE automaintain; /*自动维护开关，<RS_Open, RS_Close>*/

	/*维护周期
	  RS_EveryDay
	  RS_EveryWeek
	  RS_EveryMonth
	 */
	BYTE maintainperiod1; 
	/*维护周期二，0--6每周的周几，7--37每月的几号
	  RS_Monday 		
	  RS_Tuesday		
	  RS_Wednesday 	
	  RS_Thursday		
	  RS_Friday		
	  RS_Saturday		
	  RS_Sunday		
	 */
    BYTE maintainperiod2; 
	
	/*默认用户登录用户配置
	255:表示不启用次功能
	0-off; 1-admin, 2~7表示6个普通用户
	 */
	BYTE defaultuserid;
	BYTE EnabledUserList;/*	已开启用0bit-admin; 1~6bit表示6个普通用户*/
	BYTE EnableUser;/*是否启用默认用户功能*/
    BYTE TimeFormat;  //(0)24小时制,(1)12小时制
    BYTE P2PSwitch;
	BYTE UserName[8][32];
	BYTE IRLed;
	BYTE resver[127];
}RSNet_MaintainSet_t;

//3G
typedef struct {
	UINT StructSize;
	UINT SignalLevel;
	BYTE SignalType[32];
	BYTE IpAddr[16];
}RSNet_SystemBase3GInfo_t;

//系统升级
//暂缺




//硬盘管理
//与<硬盘信息>同一结构体


//高级控制

//远程重启

//恢复默认设置
//各位定义值


typedef struct {
	UINT StructSize;
	BYTE DevicePuid[64];
	UINT Result;
}RSNet_TuobaoInfo_t;


typedef struct {
	UINT StructSize; 	//该结构体大小

	BYTE DisplaySet_flag;
	BYTE RecordSet_flag;
	BYTE NetworkSet_flag;
	BYTE AlarmSet_flag;
	BYTE DeviceSet_flag;
	BYTE SystemSet_flag;
	BYTE AdvanceSet_flag;
	BYTE IntelligentSet_flag;
	BYTE Pairing_flag;
	BYTE resver[11];
}RSNet_DefaultSet_t;


typedef struct
{
	UINT StructSize; 	// 该结构体大小

	BYTE Switch;         	// 是否要启动WIFI的开关
	BYTE EncryptType;		// 加密方式  0 -不加密 1:WEP 2:WPA-PSK 3:WPA2-PSK 4:WPA-AUTO
	BYTE AuthMode;			// 认证模式 	WEP认证模式:1:OPEN, 2:SHARED   WPA族认证模式:3-TKIP, 4-AES 

	BYTE Reserve1[1];
	
	//密钥.
	//ps:WEP认证模式,密码长度只有5/10/13/26 四种长度.
	//WPA认证族则无限制
	//密钥长度必须根据认证模式的规则长度才能有效设置wifi
	BYTE Pwd[32];
	BYTE SSID[32];
}RSNet_WifiSet_t;


////wifi热点搜索功能参数传递结构体
typedef struct
{
	UINT StructSize; 	// 该结构体大小
	UINT ChannelMask;
	
	BYTE MacAddr[6];	
	BYTE reserve1[2];

	BYTE SSID[32];
	BYTE Protocol[16];	  	// 802.11带宽模式
	
	BYTE EncryptType;		// 加密方式  0:不加密 1:WEP 2:WPA-PSK 3:WPA2-PSK 4:WPA-AUTO
	BYTE AuthMode;			// 认证模式 	WEP认证模式:1:OPEN, 2:SHARED   WPA族认证模式:3-TKIP, 4-AES 
	
	BYTE SignalQuality;   	//信号强度
	BYTE Frequency;       	// 频率 

}RSNet_SoleWifiSet_t;


//车载功能管理
typedef struct {
	UINT StructSize; //该结构体大小
	/*录像车牌叠加*/
	BYTE RecordCarNumber;
	/*预览车牌显示*/
	BYTE PreviewCarNumber;
	/*录像GPS叠加*/
	BYTE RecordGps;
	/*速度测量来源*/
	BYTE SpeedSource;
	/*车牌号码*/
	BYTE CarNumber[MaxNameLen];
	/*已存脉冲数*/
	UINT Pulse;
	/*延时关机时间*/
	BYTE DelayTime;
	BYTE Reserved[11];	
}RSNet_VehicleMng_t;


#define RSNet_OD_NUM 3
//StaticOrDynamic
#define RS_ViewMode_Static	0
#define RS_ViewMode_Dynamic	1
//OutputMode
#define RS_OutputMode_Single	0
#define RS_OutputMode_Quarter	1
#define RS_OutputMode_Ninth		2
#define RS_OutputMode_Sixth		3
#define RS_OutputMode_Thirtysecond		4

//IsVoutOrSpot
#define RS_Output_Vout   0
#define RS_Output_Spot	 1
//Resolution
#define RS_Resolution_800_600		0
#define RS_Resolution_1024_768		1
#define RS_Resolution_1280_1024		2
#define RS_Resolution_1440_900		3
#define RS_Resolution_HDMI			4
//InitGuiDev
#define RS_InitGuiDev_VOUT		0
#define RS_InitGuiDev_VGA		1
#define RS_InitGuiDev_AUTO		2

typedef struct{
	struct tag_ChannelSelect{
		unsigned char twentychn[20]; //二十画面
		unsigned char sixteenchn[16]; //十六画面
		unsigned char eightchn[8]; //1+7画面
		unsigned char sixchn[6]; //1+5画面
		unsigned char fourchn[4]; //四画面
		unsigned char ninechn[9]; //九画面
		unsigned char onechn;    //一画面
		unsigned char thirtysixchn[36];
		unsigned char reserve[28];
	}ChannelSelect;/*定制预览通道，只能选择其中一种预览模式*/
	unsigned char Margin[4];  /*0:左边距, 1:右边距, 2:上边距, 3:下边距, 2像素为单位*/
	unsigned char PollingTime;/*输出轮询时间间隔: 数值:0~300，0表示不轮询*/
	unsigned char StaticOrDynamic;/*0-static，1-dynamic(用户手动设置)*/
	unsigned char OutputMode;/*主输出预览模式:0-一画面，1-四画面，2-九画面，3-十六画面*/
	unsigned char spotAudio;/*辅输出音频通道选择:0-关闭, 1-ch1, 2-ch2, 3-ch3, 4-ch4 ... ... 16-ch16*/
	unsigned char reserve[24];/*保留字节*/
}RSNet_OutputAttr_t;

typedef struct{
	UINT StructSize; //该结构体大小
	
	RSNet_OutputAttr_t OutputAttr[RSNet_OD_NUM]; /*voattr[0]-OD_VOUT, voattr[1]-OD_VSPOT, voattr[2]-OD_VGA*/
	unsigned char Transparency;/*透明度 数值：0~128 数值越大越透明*/
	unsigned char IsVoutOrSpot;/*0-Vout,1-Spot*/
	unsigned char Resolution;/*4为输出到高清设备*/
	unsigned char InitGuiDev;/*开机时的默认GUI 显示设备:0-VOUT, 1-VGA ,2-AUTO*/
	unsigned char OutputDev;/*输出设备:0-CVBS,1-VGA,2-HDMI*/
	unsigned char reserve1[15];/*保留字节*/
}RSNet_OutputSet_t;

//IRCutMode
#define IRCUTMODE_AUTO   0
#define IRCUTMODE_DAY    1
#define IRCUTMODE_NIGHT  2

//IRCutSensitive
#define SENSITIVE_LENGTH_HIGHT 0
#define SENSITIVE_LENGTH_MIDD  1
#define SENSITIVE_LENGTH_LOW   2

//Flip
#define FLIP_CLOSE 0
#define FLIP_OPEN  1

//Mirror
#define MIRROR_CLOSE  0
#define MIRROR_OPEN   1

typedef struct {
	UINT StoreSize;
	UINT ChannelMask;

	BYTE IRCutMode;            //0:auto;1:day;2:night
	BYTE IRCutDelay;           //0~30;unit:s 
	BYTE IRCutSensitive;       //0:Hight;1:Midd;2:Low 
	//predefine 预定义，未实现 
	BYTE Mirror;        	//水平翻转  	0:close; 1:open	
	
	BYTE Flip;           	//垂直翻转 	0:close; 1:open

	BYTE Rotate;    /* 0~不旋转;1~顺时针旋转90。2~顺时针旋转180。3~顺时针旋转270。 */

	BYTE reservel[2];
}RSNet_SoleCameraSet_t;

//shenzhen ipc image control
/* ShutterSpeed */
typedef enum
{
	RS_Shutter_Speed_1_5 = 0,
	RS_Shutter_Speed_1_8,
	RS_Shutter_Speed_1_15,
    RS_Shutter_Speed_1_25 = 3,
    RS_Shutter_Speed_1_30,
    RS_Shutter_Speed_1_50,
    RS_Shutter_Speed_1_60,
    RS_Shutter_Speed_1_100,
    RS_Shutter_Speed_1_120 = 8,
    RS_Shutter_Speed_1_150,
    RS_Shutter_Speed_1_180,
    RS_Shutter_Speed_1_200,
    RS_Shutter_Speed_1_240,
    RS_Shutter_Speed_1_250 = 13,
    RS_Shutter_Speed_1_300,
    RS_Shutter_Speed_1_360,
    RS_Shutter_Speed_1_480,
    RS_Shutter_Speed_1_500,
    RS_Shutter_Speed_1_600 = 18,
    RS_Shutter_Speed_1_700,
    RS_Shutter_Speed_1_1000,
    RS_Shutter_Speed_1_1500,
    RS_Shutter_Speed_1_2500,
    RS_Shutter_Speed_1_5000 = 23,
    RS_Shutter_Speed_1_10000,
    RS_Shutter_Speed_1_12000,
    RS_Shutter_Speed_1_20000
}NET_SHUTTER_SPEED_E;

/* 图像控制 参数页面设置新结构 */
typedef struct
{
    UINT StructSize;
    UINT ChannelMask;

    BYTE IRCutMode;			/* 0:auto;1:day;2:night;3: 视频自动,4:IO trigger,5: schedule*/
    BYTE IRCutDelay;		/* 1~36;unit:s */
    BYTE IRCutSensitive;	/* 0:Hight;1:Midd;2:Low */
    BYTE Mirror;        	/* 水平翻转  	0:close; 1:open	*/

    BYTE Flip;           	/* 垂直翻转 	0:close; 1:open */
    BYTE Rotate;			/* 0~不旋转;1~顺时针旋转90。2~顺时针旋转180。3~顺时针旋转270。 */

    /* 背光补偿 */
    BYTE BackLightMode; /* 0:disable, 1:enable */
    BYTE BackLightLevel; /* 0:low, 1:middle, 2:high   for  bpl  range is 1 - 15*/

    /* 3D降噪 */
    BYTE R3dnrMode; /* 0:disable, 1:auto, 2:manual */
    BYTE R3dnrThreshTarget; /* the thresh value when manual [1,0xff] */

    /* 数字宽动态 */
    BYTE DwdrMode;  /* 0:disable, 1:enable */
    BYTE DwdrStrength;	/* 值范围[1,0xff]  */

    /* 增益控制 */
    BYTE GainControlMode; /* 0:off, 1:low, 2:middle, 3:high */

    /* 白平衡 */
    BYTE WBMode; /* 0:auto, 1:manual, 2:indoor */
    BYTE Rgain;	/* 值范围[1,0xff]  */
    BYTE Ggain; /* 值范围[1,0xff]  */

    BYTE Bgain; /* 值范围[1,0xff]  */

    /* 快门*/
    BYTE ShutterMode; /* 0 auto, 1 manual  */
	BYTE IRFuncType;       /*红外功能开启或者关闭,0:关闭，1:自动*/
	BYTE AgcMode;          /*1:GainControlMode new mode (0~128),0:GainControlMode old mode (0:off, 1:low, 2:middle, 3:high)*/
    S32  eShutterSpeed; /* the ShutterUsecs value when manual
                                            50HZ 下最大1/25
                                            60HZ, disable 下最大1/30
                                        */
    BYTE FlickerCtrl;   /* 闪烁控制  0:50HZ   1:60HZ  2:disable */
	BYTE DefogMode;/* 0:disable, 1:auto, 2:manual */
	BYTE DefogStrength;/*去雾强度,在手动时有用，0~255*/
	BYTE IRISMode;/* 0:disable, 1:auto */
	BYTE autoFocus;/*0:disable; 1:enable; NOVUS 自动对焦*/
	BYTE LEDEnable;/*0:OFF; 1:ON;2:auto,Novus IR LED Light*/
	RSNetTimeSet_t StartTime;
	RSNetTimeSet_t EndTime;
	BYTE HideRotate; /*0:不做处理 1:隐藏90和270*/
	BYTE GainSwitch; /*Gain switch,0:OFF,1:ON*/
	BYTE ColorGain;	/* Color Gain,[1-0xff]*/
	BYTE BrightGain;/* Bright Gain, [1-0xff]*/
	BYTE R2dnrMode; /* 2D降噪,0:Low, 1:Medium, 2:High */
	BYTE DefogFakeLottery;/* 去伪彩，值范围[1,0xff]*/
	BYTE FloodLightMode; /*白光灯 0:disable 1:enable*/
	BYTE FloodLightValue;/*值范围[0, 100]*/
	BYTE BackLightZone;		/* 0 --> 全局    1 --> 中心    for bpl */
	BYTE AntiShakeEnable;  	/* 0 关  1 开*/
	BYTE AntiShakeLevel;	/*等级0-7，防抖强度级别，级别越大，防抖效果越好*/
	BYTE AntiShakeLevelFlag;/*0：不显示Level,1:显示level */
	BYTE BackLightLevelCheck;	/* 1: 新模式 1-15 数值设置，0：旧模式（0:low, 1:middle, 2:high）*/
	BYTE WDRFlag;/*0:IE显示WDR,1:IE显示DWDR*/
	BYTE HLCSwitch; /*强光抑制开光 0:disable,1:enable*/
	BYTE HLCStrength; /*强光抑制值范围[1-255]*/
	BYTE reverser2[42];
}RSNetNew_CameraSet_t;
///////////////////////////////////////////////////////////////////////////
//关键配置区参数传递结构体, 仅提供公司内部实现关键参数配置使用。不向外提供。
///////////////////////////////////////////////////////////////////////////
typedef struct {
    UINT StructSize;
    UINT ChannelMask;
    BYTE mode;// 0:normal,1:daylight,2:night
    BYTE reverser[15];
    RSNetNew_CameraSet_t cameraSet[3];
}RSNetNew_CameraModeSet_t;

typedef struct {
	UINT StructSize; 	//该结构体大小
	
	BYTE Mac[6];
	BYTE reservel[2];
	BYTE model[32];
	BYTE serialNum[32];
    BYTE reservel2[2];
    BYTE WifiMac[6];
	BYTE SnNum[32];
}RSNet_KeyConf_t;

//////////////////////////////////////
//IP黑白名单过滤参数传递结构体
#define MAX_IPFILTER_NUM 16

#define FILTERSWITCH_OPEN  0
#define FILTERSWITCH_RELYON_ENABLE 1
#define FILTERSWITCH_CLOSE   2

typedef struct {
	UINT StructSize;
	
	BYTE FilterSwitch; //0 忽略所有的IP 的检查(所有设置IP都能通行）1所有IP 开启白名单(需检查SingleLock 是否开启) -1 所有IP 开启黑名单（拦截所有设置IP)

	BYTE reserve[3];
}RSNet_IPFilter_t;

typedef struct {
	UINT StructSize;
	UINT ChannelMask;
	
	BYTE IPAddr[4];
	BYTE Enable;//单个IP地址检查开关 RS_OPEN  1 ; RS_CLOSE 0 

	BYTE reservel[3];
}RSNet_SoleIPFilter_t;

//////////////////////////////////////
//RTSP服务参数
//////////////////////////////////////

//enAuthMode
#define RTSP_HTTP_AUTH_NONE   0
#define RTSP_HTTP_AUTH_BASIC  1
#define RTSP_HTTP_AUTH_DIGEST 2

typedef struct {
	UINT StructSize;

	UINT RtspPort;
	UINT enAuthMode;//验证模式 
	UINT RtspEnable;
	char  RtspUserName[32];
	char  RtspPassword[32];
	
	BYTE Checkflag;  /*1 = true, 0 = false */
	BYTE anonymousLogin; /*1 = true, 0 = false */
	BYTE IpEyeEnable;
	BYTE resever;
	UINT RtspExtPort;
}RSNet_Rtsp_t;


//////////////////////////////////////
//FTP服务参数
//////////////////////////////////////
#define    FTP_RECTYP_NORMAL  1                                           
#define    FTP_RECTYP_ALARM   2                                                 
#define    FTP_RECTYP_ALL     3     

#define    FTP_LAST_ONE_H   0                                           
#define    FTP_LAST_TWO_H   1                                                 
#define    FTP_LAST_FOUR_H  2 
#define    FTP_LAST_ONE_D   3            
typedef struct
{
	UINT StructSize;
	UINT ChannelMask;
	BYTE TimeMode;    /*上传录像的时间周期*/
	BYTE ReqTypeMask; /*请求类型掩码：一个位对应一个请求类型，置位表示开启，0表示关闭*/
	BYTE RecType;     /*1:正常录像,2:报警录像,3:所有录像*/
	BYTE Reserve;
}RSNet_SoleFtpSet_t;

typedef struct
{
	UINT StructSize;
	BYTE FtpIpAddr[16];
	BYTE FtpLoginName[64];
	BYTE FtpLoginPwd[64];
	UINT FtpPort;	
	BYTE UseFtp;
	BYTE VideoSwitch;//是否开启视频
	BYTE Reserved; 
	BYTE useFtpIpAddr2; //1：使用FtpIpAddr2   0：不使用
	UINT SendFileSize;   // 以 字节 为大小单位
	BYTE FilePath[96];   // 写文件的文件路径
    BYTE FtpServer[32];  //FTP域名(shenzhen extend)
    BYTE FtpServer2[64];
	BYTE FtpIpAddr2[64]; //2018.2.6
	BYTE CertPem[1024 * 4];    // cert pem
	BYTE CertPwd[64];          // cert password
	BYTE PrivateKey[1024 * 4]; // private key
	BYTE PrivateKeyPwd[64];    // private key password
	BYTE EncMode;
	BYTE PicResolution;     //图片分辨率　对应RESOLUTION_E的枚举值
	BYTE PicQulity;         //图片质量  90 75 65 50 35 20
	BYTE VideoStreamType;   //视频码流类型 0:Mainstream 1:Substream
	BYTE EnNormalVideo;     //Normal Video上传总开关
	BYTE MaxPackInterval;   //unit: Min 10 20 30 45 60
	BYTE NormalVideoSwitch[32]; //Normal Video单通道开关
	BYTE VideoFormat;	// 0：p制    1：N制
	BYTE resever[25];
}RSNet_FtpSet_t;

#define LOCKNUM_MAX      12
#define NET_LOCKID_LEN   16
//LockFlag
#define LOCKSTATE_LOCK   1
#define LOCKSTATE_UNLCOK 0

typedef struct{
	UINT StructSize;
	UINT ChannelMask;
	
	BYTE LockFlag;
	BYTE Reservel[3];
	
	BYTE LockId[NET_LOCKID_LEN];	
}RSNet_SoleElecLockSet_t;


typedef struct
{
	UINT StructSize;
	UINT ChannelMask;
	BYTE DriveName[16];
	BYTE TimeTrigger;	////时间间隔
	BYTE Enable;		////云存储是否开启
	BYTE MotionEnable;	////移动侦测是否开启
	BYTE CloudType;		////云的种类
	BYTE Reserved[4];
	BYTE RecvEmail[3][36];  //收件人地址
}RSNet_CloudStorageSet_t;

typedef struct {
	UINT StructSize;
    /*SMTP服务器*/
    BYTE SMTP[36];

    /*发件人地址*/
    BYTE SendEmail[36];

    /*发件人密码*/
    BYTE SendEmailPW[36];

    /*收件人地址*/
    BYTE RecvEmail[3][36];

    /*端口号*/
    UINT Port;

    /*SSL开关，0--关闭，1--打开*/
    BYTE SSLSwitch;

    /*是否使用email,0--关闭，1--启用*/
    BYTE EmailSwitch;

    /*邮件发送间隔*/
    BYTE intervaltime;/*0:60,1:180,2:300,3:600s*/
    BYTE reserve[1];
} RSNet_cloudemailsetting_t;

//typedef struct 
//{
//	UINT StructSize;
//	BYTE p2pUid[36];
//	BYTE p2pUser[36];
//	BYTE p2pPwd[36];
//	BYTE resev[4];
//} RSNet_P2pMobileSet_t;

// 二维码扫描P2p ID 结构体
typedef struct 
{
	UINT StructSize;

	BYTE QrCodeID[48];
	BYTE reserved[24];
}RSNet_P2pQrCodeIdSet_t;

typedef struct{
	UINT StructSize;
	UINT ChannelMask;
	
	BYTE RecordEnable;
	BYTE MotionEnable;
	BYTE IoAlarmEnable;
	BYTE Reservel[9];
}RSNet_SoleDevAllStatusSet_t;

typedef struct {
	UINT StructSize;
	
	BYTE IDNumber[24];
	BYTE KeyContent[2048];     
    BYTE reserver[4];
}RSNet_LorexP2pParamSet_t;

typedef struct {
	UINT StructSize;

	BYTE AutoUpgradeEnable; 
	BYTE AutoUpgradePrompt; 
    BYTE Reserve[10];
    BYTE DeviceType[MaxNameLen]; //设备类型
    BYTE SoftwareVer[MaxNameLen]; //系统软件版本	
}RSNet_FtpAutoUpgrade_t;

// MasterSwitch 
#define MASTER_SWITCH_OFF     0
#define MASTER_SWITCH_ON      1
#define MASTER_SWITCH_FORBID  2
typedef struct {
	UINT StructSize;

	BYTE MasterSwitch;   // 0 - 关闭手动录像 1- 开启手动录像  2- 不启用此开关
	BYTE Reserve[3];   // 预留字节，单个通道手动开关控制
	UINT ChannelEx[8];
	BYTE reserve2[256];
}RSNet_ManualRecordSet_t;
#define LOGNUM_MAX  15*20
typedef enum{
		SYSTEM_LOG = 0,
		PARAMETER_LOG,
		/*PTZ_LOG,*/
		ALARM_LOG,
		STORAGE_LOG,
		ALLTYPE_LOG,
}LogType_E;

typedef struct {
	char  event[32];		///< event description
	char time[32];
}RSNet_Log_t;

typedef struct {
	UINT StructSize;
	UINT begintime[6];
	UINT endtime[6];
	UINT logtype;
}RSNet_LimitLogSet_t;

typedef struct {
	UINT StructSize;
	UINT lognum;
	RSNet_Log_t  Loglist[LOGNUM_MAX];
}RSNet_QureyLogSet_t;

typedef enum
{
	AT_G711A=0,
	AT_G711U,
	AT_ADPCM,
	AT_G726_16K,
	AT_G726_24K,
	AT_G726_32K,
	AT_G726_40K,
	AT_MAX
}Audio_Type_E;

#if 1
typedef struct {
	UINT StructSize;
	BYTE Audio;			/*0: close; 1: open */
	BYTE MicInVolume;	/* 输入声音大小(0 - 10) */
	BYTE LineOutVolume; /* 输出声音大小(0 - 10) */
	BYTE AdecEncoding;	/* 编解码类型 0, PT_G711U;1,PT_G711A */
	BYTE InputMode;		/* 0: line in  1:mic */
	BYTE Bitrate;/* 码率G726 编码下有效，0,16kbps; 1,24kbps;2,32kbps;3,40kbps;4,64kbps*/
	BYTE AudioSampleRate;/*音频采样率，0-8KHZ,1-16KHZ*/
	BYTE AudioSampleEnable; /*音频采样率使能开关，0-关，1-开*/
	U8 AdecEncodingSupport;	/*  AdecEncoding 支持情况，按位取值，以Audio_Type_E为顺序  */
	BYTE Reserve[11];
}RSNet_VoiceSet_t;
#endif

// MsgParamSystemIDCtrl
typedef struct {
	UINT StructSize;

	UINT SystemID;
	BYTE Reserve[16];
}RSNet_SystemIDCtrl_t;

//IPCFRAMEINFO_S
typedef struct {
	UINT FrameRate;   //当前帧率,1~30
	UINT BitRate;     // Bit rate

	U64 FrameSelect;  //按位取帧
}IPCFRAMEINFO_S;

typedef struct {
	UINT StructSize;
	UINT ChannelMask;

	BYTE OsdMask;   	// osd显示     0:no 1:yes
	BYTE TimeMask;  	// time显示，  0:no, 1:yes
	BYTE Frequency;     // 频率        0:60hz, 1:50hz
	BYTE StreamType;    //码流类型，   0:sigle, 1:double

	BYTE EncodeType;   //当前编码,    when sigle streame; 0:D1,  1:720P,  2:1080P, when double streame; 0:1080p+cif,  1:720P+D1,  2:720p+cif
	BYTE Reserve[3];

	IPCFRAMEINFO_S FrameInfo;     //帧信息
	IPCFRAMEINFO_S FrameInfoExt;  //when is sigle streame ,it is no vaild
}RSNet_SoleIPCFrameSet_t;

typedef struct
{
	UINT StructSize;
	
	BYTE DriveName[16];
    BYTE RecvEmail[3][36];
    BYTE Account[3][64];
    BYTE AccountPW[3][64];
	BYTE Enable;
	BYTE ServerType;
	BYTE SnapEnable;
	BYTE VideoEnable;
}RSNet_NewCloudStorageSet_t;

typedef struct
{
	UINT StructSize;

	UINT ChnNoChoice; // 按位取对应通道标志位
	BYTE TimeTrigger;
	BYTE MotionSnapEnable;
	BYTE Reserved[2];
}RSNet_UploadPhotoSet_t;

typedef struct
{
	UINT StructSize;
	
    UINT MotionScheduleHour[32][8];//通道相关,7天,小时按位取
    BYTE MotionVideoChannel;
	BYTE Reserved[3];
}RSNet_UploadVideoSet_t;

typedef struct
{
    UINT StructSize;
    UINT ChannelMask;       //通道掩码
    BYTE HalfHour[8][48];   // 7days and 48 halfhours
    BYTE Reserved[16];
}RSNet_SoleUploadVideoSet_t;

typedef struct 
{    
	UINT StructSize;

	BYTE key[3][64];      /*用户KEY*/
    BYTE secret[3][64];   /*用户KEY密码*/
    BYTE Enable;
    BYTE CloudType;       /*云端服务类型，0-DROPBOX,1-GOOGLE*/
    BYTE TimeTrigger;
    BYTE MotionEnable;
    BYTE DriveName[32];   /*上传目录*/
    UINT Channel;
    BYTE FTPPATH[36];     /*FTP路径*/    
    UINT Channel_EX[8];
}RSNet_NormalCloudStorageInfo_t;

typedef struct 
{
	UINT StructSize;

	BYTE SMTP[36];        /*SMTP服务器*/
    BYTE SendEmail[36];   /*发件人地址*/
    BYTE SendEmailPW[36]; /*发件人密码*/
    BYTE RecvEmail[3][36];/*收件人地址*/
    UINT Port;           /*端口号*/
    BYTE SSLSwitch;   /*SSL开关，0--关闭，1--打开*/
    BYTE EmailSwitch; /*是否使用email,0--关闭，1--启用*/
    BYTE intervaltime;/*邮件发送间隔0:60,1:180,2:300,3:600s*/ 
	BYTE reserve[11];
}RSNet_NormalCloudStorageEmail_t; 

typedef struct{
	UINT StructSize;

	BYTE FtpIpAddr[16];
	BYTE FtpLoginName[32];
	BYTE FtpLoginPwd[32];
	UINT FtpPort;
	BYTE FilePath[64]; 
	BYTE Reserved[64];
}RSNet_NomalCloudStorageFtp_t;

/*********************************************************************
 * Description: Intelligent Param Adapter 
 * 8 Bytes Alignment， 9*32 = 288 bytes 
 * start
 * ******************************************************************/

typedef struct{
    S16 x1; //must S16 here,can't be U16
    S16 y1;
    S16 x2;
    S16 y2;
}Net_Line_S;

/* 高级设置-周界伴线 */
typedef struct {
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;          /*0-关闭，1-打开*/
    BYTE BuzzerMooTime;      /*蜂鸣器鸣叫，鸣叫时间:0，10，20，40，60s*/
    BYTE AlarmOutTime;       /*报警输出，输出时间:0，10，20，40，60s*/
    BYTE RecordDelayTime;    /*录像延时，延时时间:0，10，20，40，60s*/
    BYTE AlarmOutManager[4];   /*只有一个报警输出的，用AlarmOutManager[0]即可*/
    UINT RecordChannel;
    BYTE Record;               /*Record channel switch*/
    BYTE ShowMessage;          /*Show Message 开关*/
    BYTE SendEmail;            /*Send Email 开关*/
    BYTE FullScreen;           /*FullScreen 开关*/
    BYTE RuleSwitch;        /*每个通道用一个字节表示最多8条规则，0-关闭，1-使用*/
    BYTE RuleType;          /*DVR专用: 每个通道用一个字节表示最多8条-规则类型，0-伴线，1-周界*/
    BYTE LineTwoWay;        /*DVR专用: 每个通道用一个字节表示最多8条-伴线类型双向，0-否，1-双向*/
    BYTE RuleScene;	   		/*场景类型，0-室内场景，1-室外*/
    BYTE Sensitive;	        /*算法灵敏度0-9*/
    BYTE NewRuleType;  		/*IPC专用：规则的方向，两个bit表示一个规则的方向 0-a->b，1-b->a,2-a<->b*/ //2015.11.12
    
    S8   AIChannel;         /*当前使用智能通道的模拟通道是第几通道,-1:没有模拟通道使用智能功能*/
    BYTE IsSpot;             //改成判断是否开启spotAudio
    Net_Line_S RuleLine[32];	/*每通道最多有64个点坐标,即32条线，如果是伴线则只使用第1条线，
                                  如果是周界则将这8条线依次连接起来组成闭合图形 */
	UINT RecordChannel_EX[8];

	BYTE DrawLineEnable;/*是否开启预览绘线 20170313 add*/
	BYTE FtpLink;
	BYTE sendToFTP;/*发送截图到FTP，0：不使能；1：使能*/
	BYTE IVALines;/*预览和回放是否需要划线，0-不画线，1-画线*/
	BYTE PushSwitch;
	BYTE FtpVideoLink;         /*FTP录像联动 开关*/
	BYTE CloudPicUpload; 
	BYTE CloudVideoUpload; /* 云存储视频上传 */
	//BYTE reserved[2];
	/*取bit位:3表示一个通道最多3个报警输出,每个报警输入触发后可以联动到
	32*8= 256路的任何通道报警输出*/
	BYTE AlarmOutManagerEx[3][32];
}RSNet_SolePerimeterLine_t;

/* 高级设置-视频诊断 */
typedef struct{
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;                   /*0-关闭，1-打开*/
    BYTE ChnCruiseTime;               /*轮询时间*/
    BYTE BuzzerMooTime;               /*蜂鸣器鸣叫，鸣叫时间:0，10，20，40，60s*/
    BYTE AlarmOutTime;                /*报警输出，输出时间:0，10，20，40，60s*/
    UINT CheckTypeSwitch;             /*检测类型开关*/
    BYTE AlarmOutManager[4];            /*只有一个报警输出的，用AlarmOutManager[0]即可*/
    UINT RecordChannel;
    BYTE Record;                        /*Record channel switch*/
    BYTE RecordDelayTime;             /*录像延时，延时时间:0，10，20，40，60s*/
    BYTE ShowMessage;                   /*Show Message 开关*/
    BYTE SendEmail;                     /*Send Email 开关*/
    BYTE FullScreen;                    /*FullScreen 开关*/
	BYTE CheckType;                   /*检测类型*/
    BYTE IsSpot;             //改成判断是否开启spotAudio
    BYTE reserve[9];
}RSNet_SoleVideoDiagnostics_t;

/* 高级设置-物品遗留丢失*/
typedef struct{
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;          /*0-关闭，1-打开*/
    BYTE BuzzerMooTime;      /*蜂鸣器鸣叫，鸣叫时间:0，10，20，40，60s*/
    BYTE AlarmOutTime;       /*报警输出，输出时间:0，10，20，40，60s*/
    BYTE RecordDelayTime;    /*录像延时，延时时间:0，10，20，40，60s*/
    BYTE AlarmOutManager[4];   /*只有一个报警输出的，用AlarmOutManager[0]即可*/
    UINT RecordChannel;
    BYTE Record;               /*Record channel switch*/
    BYTE ShowMessage;          /*Show Message 开关*/
    BYTE SendEmail;            /*Send Email 开关*/
    BYTE FullScreen;           /*FullScreen 开关*/

    BYTE RuleSwitch;        /*每个通道用一个字节表示最多8条规则，0-关闭，1-使用*/
    BYTE RuleType;          /*DVR专用: 每个通道用一个字节表示最多8条-规则类型，0-遗留，1-丢失*/
    BYTE RuleScene;         /*每个通道用一个字节表示最多8条-场景类型，0-室内场景，1-室外*/
    BYTE Sensitive;			/*算法灵敏度0-9*/
    BYTE NewRuleType;       /*IPC专用：每个通道用一个字节表示最多4条-规则类型，2bit表示一种类型，0-检测遗留，1-检测丢失，2-同时检测丢失和遗留*/ //2015.11.12	
    S8   AIChannel;         /*当前使用智能通道的模拟通道是第几通道,-1:没有模拟通道使用智能功能*/
	BYTE IsSpot;             //改成判断是否开启spot
    BYTE DrawLineEnable;/*是否开启预览绘线 20170313 add*/
    BYTE RuleRectEnable[8];  /*IPC 2.0不再使用，每通道最多有8条规则，每规则最多有4区域.每一位代表一个区域的使能，目前只用前四位*/
    Net_Line_S RuleRect[32];	/*每规则最多有4区域,即每通道最多有8＊4＝32个区域*/
	UINT RecordChannel_EX[8];
	/*取bit位:3表示一个通道最多3个报警输出,每个报警输入触发后可以联动到
	32*8= 256路的任何通道报警输出*/
	BYTE AlarmOutManagerEx[3][32];
	BYTE FtpLink;
	BYTE sendToFTP;/*发送截图到FTP，0：不使能；1：使能*/
	BYTE IVALines;/*预览和回放是否需要划线，0-不画线，1-画线*/
	BYTE PushSwitch;
	BYTE DetonateTime;		/*触发时间，可选10s，20s，30s，40s，50s，60s，70s，80s，90s*/
	BYTE FtpVideoLink;         /*FTP录像联动 开关*/
	BYTE CloudPicUpload; 
	BYTE CloudVideoUpload; /* 云存储视频上传 */
}RSNet_SoleGoodsLostLegacy_t;

/* 高级设置-人体/人脸/过线统计 2016.03.09*/
typedef struct {
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;          	/*0-关闭，1-打开*/
    BYTE BuzzerMooTime;      	/*蜂鸣器鸣叫，鸣叫时间:0，10，20，40，60s*/
    BYTE AlarmOutTime;       	/*报警输出，输出时间:0，10，20，40，60s*/
    BYTE RecordDelayTime;    	/*录像延时，延时时间:0，10，20，40，60s*/
    BYTE AlarmOutManager[4]; 	/*只有一个报警输出的，用AlarmOutManager[0]即可*/
    UINT RecordChannel;
    BYTE Record;                /*Record channel switch*/
    BYTE ShowMessage;           /*Show Message 开关*/
    BYTE SendEmail;             /*Send Email 开关*/
    BYTE FullScreen;            /*FullScreen 开关*/

    BYTE RuleSwitch;            /*每个通道用一个字节表示最多8条规则，0-关闭，1-使用*/					  	
    BYTE RuleScene;	   		    /*场景类型，0-室内场景，1-室外
								            *人脸智能已废弃场景，使用该字段作为Detection Range
								           */
    BYTE Sensitive;	            /*算法灵敏度0-3,对于深度学习智能行人车辆，0-100灵敏度，默认50*/
    BYTE RuleType;       		/*每个通道用一个字节表示最多8条-规则类型，
    						  		0-人脸、人体-常规模式，过线统计-双向，1-其他模式
									对于新人脸程序，0：全屏模式，1：自定义模式*/	
	BYTE RuleTypeAdd;       	/*控制过线统计的方向0-a->b 1-b->a*/	
    BYTE DrawLineEnable;/*是否开启预览绘线 20170313 add*/
	BYTE sendToFTP;/*发送截图到FTP，0：不使能；1：使能*/
	BYTE FtpLink;
    Net_Line_S RuleLine[32];	/*每通道最多有64个点坐标,即32条线，每规则最多有1个区域/1个线，
                              			如果是伴线则只使用第1条线，如果是四边形，则使用第1和第2条线
										*******************************************************************
										20181024 add
										最多有4个规则，则使用0-15画四边形，
										16-31用来绘制统计线（分为4个规则，则16-19为规则1,20-23为规则2......，一个Net_Line_S有两点，可以为一条线，
										因此，16,20,24,28数组号分别是各规则的第一条线）
										*******************************************************************
										*/
	UINT RecordChannel_EX[8];
	/*取bit位:3表示一个通道最多3个报警输出,每个报警输入触发后可以联动到
	32*8= 256路的任何通道报警输出*/
	BYTE AlarmOutManagerEx[3][32];
	BYTE IVALines;/*预览和回放是否需要划线，0-不画线，1-画线*/
	BYTE PushSwitch;
	BYTE FtpVideoLink;            /*FTP录像联动 开关*/
	BYTE SnapInterval;		/*抓图间隔时间单位为s,1~255,默认2s*/
	BYTE CloudPicUpload; 
	BYTE CloudVideoUpload; /* 云存储视频上传 */	
	BYTE SnapModel;			/*抓拍模式，0:自动模式，1:最优模式，2.快速模式，3.自定义模式*/
	BYTE FaceType;		
	BYTE RollRange;			/*自定义模式下，人脸旋转角度,范围0~180，默认180*/
	BYTE PitchRange;			/*自定义模式下，人脸俯仰角度,范围0~180，默认180*/
	BYTE YawRange;			/*自定义模式下，人脸侧脸角度,范围0~180，默认180*/
	BYTE BlurStage;			/*自定义模式下，人脸模糊程度, 范围0~100, 默认为100*/
	WORD MinPixel;         /*人脸检测最小像素， 范围32-1080，默认64*/
	BYTE RuleKind;        /*人脸检测方式，0：区域，1：绊线*/
	BYTE SnapNum;			/*抓图图片上限 1~3张*/
	BYTE DetectType;		/*检测类型，按位判断，0：行人，1：车辆，其他位未定*/
	BYTE MotionDet;			/*是否利用运动区域状态，0-静止检测模式，1-运动检测模式*/
	BYTE reserved[6];
}RSNet_SoleIntHumanFace_t;/*IPC 专用*/

/* 高级设置-智能管理 2016.03.09*/
/*智能模块目前有: 1)PID 2)LCD 3)SOD 4)HD 5)FD 6)PCC，最多有32个智能，按位传输，从0到31位*/
typedef struct {
	UINT StructSize;          /*方便IE验证数据大小*/
	UINT ChannelMask;         /*通道掩码*/

    UINT FunSwitchDisplay;    /*功能开关是否有开 0-关闭，1-打开*/
	UINT RecordDisplay;		  /*录像开关是否有开 0-关闭，1-打开*/

	UINT EmailDisplay;		  /*邮件开关是否有开 0-关闭，1-打开*/
	UINT AlarmOutDisplay;	  /*输出开关是否有开 0-关闭，1-打开*/

	UINT AlramDisplay;        /*实时是否有报警 0-有，1-无*/         
	UINT InCountDisplay;	  /*CC 结果显示，进入*/

	UINT OutCountDisplay;	  /*CC 结果显示，出去*/

	BYTE SceneDisplay;	      /*当前场景 0-室内，1-室外*/
    BYTE CloudVideoIsUsed;	/* 当前通道是否已使能云视频上传 */
    BYTE reserved[250];
}RSNet_SoleIntManage_t;/*IPC 专用*/

/*********************************************************************
 * Description: Intelligent Param Adapter 
 * 8 Bytes Alignment， 9*32 = 288 bytes 
 * end
 * ******************************************************************/

/* 通过远程设置board id, key id */
typedef struct 
{
	UINT StructSize;

	UINT KeyID;
	BYTE BoardID[16];
    BYTE DeviceType;//设备型号,由远端传递的枚举值决定(DVR OWL 20150129)
    BYTE reserved[7];
}RSNet_IDset_t;

/*********************************************************************
 * kegurd新增信令FTP升级需要首先查询当前是否有新fw可用
 * 查找ftp服务器上是否有可升级文件。
 * #define MsgFtpUpgradeSearchFile    324  //get ftp server newversion info 
*********************************************************************/
//ftp server upgradfile version info
typedef struct
{
	int  NewVersion;	//0:no ,1: yes，-1，errno
	int  Filesize;
	char Versioninfo[128];	//version name
}FtpUpgradFileVersionRsp;

/*********************************************************************
 * Description:New NVR Device Param Adapter 
 * 8 Bytes Alignment 
 * add by zy 20140213
 * ******************************************************************/

#if defined(OCX_FOR_IEPACK_UI5_SAMSUNGWisenet) || defined(OCX_FOR_NetViewer_UI5_SAMSUNGWisenet)
	typedef struct 
	{
		UINT StructSize;
		UINT ChannelMask;

		BYTE BitRateMode;    //stream mode:0-预置 1-自定义
		BYTE Bitrate;        //索引 ，对应码流大小参见RS_MainBitrate_e
		WORD CustomBitrate;   // 自定义码流数值，在预制码流值bitrate无法满足前端IPC时使用 

		BYTE BitrateType; /* 0 :定码率1:变码率2: 定质量 3: QVBR*/
		BYTE VideoQuality; /* 图像质量0: 最差1:更差2:差3:好4:更好5:最好*/
		BYTE AudioSwitch;    //前端设备的音频流是否启用 0: close 1: open
		BYTE Num;/*支持的分辨率个数,最多选择8个*/

		BYTE IFrameInterval; /* I 帧间隔范围【1-100  】 */
		BYTE Fps;      
		BYTE ResolutionsetIndex; /* whice one resolution index has been choose to set */
		BYTE HaveAudio;/*前端设备是否支持音频编码，0不支持，1支持*/
		RSNetNew_ResolutionRateRange_t Range[8];
		BYTE VideoSwitch; /* 此码流视频编码是否打开0, 关, 1,开 */
		BYTE AudioEncType;
		BYTE VideoEncType;
		BYTE ProfileLevel;/*编码级别0-2，0：Baseline，1：Main Profile，2：High Profile*/
		BYTE UsedEncType; /*可用的编码类型0-同时支持H264和H265,1-只支持H264，使用IPC_Dev_Type_e枚举来表示*/

		BYTE AMRSwitch; /*AMR 编解码开关(DENAVO客户专用). 0:disable, 1:enable*/
		BYTE SoleResolutionMode;
		//BYTE UseJPEG;	   /*是否使用JPEG编码，0-不使用，1-使用----2170208update,使用位来表示*/
		BYTE UseJPEG:1;	   /*是否使用JPEG编码，0-不使用，1-使用*/
		BYTE HideEncType:1;/*是否显示编码格式, 0:显示，1：不显示*/
		BYTE unused:6;
		BYTE CameraMaxRes;/*记录枪机最大支持的分辨率类型，具体值参照DEV_RES_E*/

		BYTE reserver[7];
		RSNetNew_ResolutionRateRange_t Range2[8];
	}RSNetNew_SoleStreamset_t;
#else
	typedef struct 
	{
		UINT StructSize;
		UINT ChannelMask;
	
		BYTE BitRateMode;    //stream mode:0-预置 1-自定义
		BYTE Bitrate;        //索引 ，对应码流大小参见RS_MainBitrate_e
		WORD CustomBitrate;   // 自定义码流数值，在预制码流值bitrate无法满足前端IPC时使用 

		BYTE BitrateType; /* 0 :定码率1:变码率2: 定质量 3: QVBR*/
		BYTE VideoQuality; /* 图像质量0: 最差1:更差2:差3:好4:更好5:最好*/
		BYTE AudioSwitch;    //前端设备的音频流是否启用 0: close 1: open
		BYTE Num;/*支持的分辨率个数,最多选择8个*/
	
		BYTE IFrameInterval; /* I 帧间隔范围【1-100  】 */
		BYTE Fps;      
		BYTE ResolutionsetIndex; /* whice one resolution index has been choose to set */
		BYTE HaveAudio;/*前端设备是否支持音频编码，0不支持，1支持*/
		RSNetNew_ResolutionRateRange_t Range[8];
		BYTE VideoSwitch; /* 此码流视频编码是否打开0, 关, 1,开 */
		BYTE AudioEncType;
		BYTE VideoEncType;
		BYTE ProfileLevel;/*编码级别0-2，0：Baseline，1：Main Profile，2：High Profile*/
		BYTE UsedEncType; /*可用的编码类型0-同时支持H264和H265,1-只支持H264，使用IPC_Dev_Type_e枚举来表示*/
	
		BYTE AMRSwitch; /*AMR 编解码开关(DENAVO客户专用). 0:disable, 1:enable*/
		BYTE SoleResolutionMode;
		//BYTE UseJPEG;	   /*是否使用JPEG编码，0-不使用，1-使用----2170208update,使用位来表示*/
		BYTE UseJPEG:1;	   /*是否使用JPEG编码，0-不使用，1-使用*/
		BYTE HideEncType:1;/*是否显示编码格式, 0:显示，1：不显示*/
		BYTE unused:6;
		BYTE CameraMaxRes;/*记录枪机最大支持的分辨率类型，具体值参照DEV_RES_E*/

		BYTE reserver[7];
	}RSNetNew_SoleStreamset_t;
#endif

typedef struct 
{
	UINT StructSize;
	UINT ChannelMask;
	
	S16 res_w;			////裁剪源分辨率宽
	S16 res_h;			////裁剪源分辨率高
	RSNet_Rect_t rect;
	RSNetNew_SoleStreamset_t rsAreaStreamSet;
	BYTE areaSwitch;	////是否开启区域裁剪
	BYTE reserver[7];
}RSNetNew_AreaStreamset_t;

/* 不同IPC的OSD显示规则,按位表示,对应RSNetNew_SoleLivingset_t */
typedef enum
{
    RSOSD_HideFliker = 0,	// 隐藏闪烁控制
    RSOSD_HideFormat,		// 隐藏时间日期格式
    RSOSD_HidePosition,		// 隐藏OSD位置设置
    RSOSD_hideShowName,		// 隐藏是否显示名称
    RSOSD_HideShowTime,		// 隐藏是否显示日期
    RSOSD_SupportUpper		// 小写字母需主动转换为大写并自动刷新显示
}RSOSD_DispRule_e;

/* preview  */
#define NET_STD_RES_X 704
#define NET_STD_RES_Y 576
typedef struct 
{
	UINT StructSize;
	UINT ChannelMask;
    
	/* ChannelName通道名位置，相对于NET_STD_RES_X * STD_RES_Y的值 */
	U16 ChnNamePosX; 
	U16 ChnNamePosY; 
	/* Date时间日期位置，同上 */
    U16 DateTimePosX;
    U16 DateTimePosY;
	
	char   ChnName[40];        /*通道名称*/
    BYTE ShowChnNameFlag;    /* OSD是否显示通道名：1-显示，0-不显示 */
    BYTE ShowDateTimeFlag;   /* OSD是否显示日期  ：1-显示，0-不显示 */
    BYTE TimeMode:4; /* 时间模式：0为24小时制，1为12小时制*/
    BYTE DateMode:4; /* 日期模式:0为MM/DD/YYYY，1为YYYY-MM-DD，2为DD/MM/YYYY；*/
                                                            
	BYTE FlickerCtrl;  // ipc 闪烁控制 0:50 Hz 1:60Hz 2 disable
    BYTE DisplayRule;   //根据不同IPC协议类型显示不同的内容
	BYTE Covert;         /*通道隐藏*/
	BYTE fgAlpha;	/* OSD 透明度[0-128] */
    BYTE RecTimeFlag;/*录像时间OSD: 1-显示, 0-不显示 (只用于混合DVR)*/
    BYTE AHD_QESwitch;
    BYTE  NewNameFlag;//0xa5表示使用新的通道名
    BYTE  ChnName2Enable;//是否使用第二个通道名称
	BYTE  NewOsdLenEnable;//是否使用板端控制NewChName的输入长度
	BYTE  NewChNameStrlen;//板端控制具体osd长度
	BYTE Protocol; /*协议类型，仅BALTER 客户使用*/
    BYTE  reserve1[2];
	BYTE  NewChName[128];//

	U16 ChnNamePosX2;  /*第二个通道名称位置*/
	U16 ChnNamePosY2; 
	U16 WaterMaskPosX; 
	U16 WaterMaskPosY;
	BYTE ShowChnNameFlag2;      /* OSD是否显示第二个通道名：1-显示，0-不显示 used by 2017.7.13*/
	BYTE ShowCarNumFlag;		/*OSD是否显示车牌号*/
	BYTE ShowGPSFlag;			/*OSD是否显示GPS信息*/
	BYTE ShowSpeedFlag;			/*OSD是否显示车速*/
	BYTE reser2[4];
	char ChnName2[40];        /*第二个通道名称used by ipc 2017.7.13*/

	//多行osd信息 2018.01.16
	UINT MulitRowOsdPosX; 		/*OSD X坐标*/
	UINT MulitRowOsdPosY; 		/*OSD Y坐标*/
	char MulitRowOsdContent[11][64];/*多行OSD 数据*/
	BYTE ShowMulitRowOsdEnable;	/*是否使用多行OSD*/
	BYTE ShowMulitRowOsdFlag;	/*多行OSD显示*/
	BYTE TypeAlignment;			/*多行OSD 对齐方式0:左对齐 1:右对齐 2:居中*/
	BYTE WaterMark; /*0 : 关闭 1打开 */
	BYTE FontSize; /*字体大小 0:小，1:中，2:大*/
	BYTE reser3[3];
	char MulitRowOsdContent2[9][64];/*客户扩展为20行OSD 数据     2018.02.05*/

	//2018.03.22 add color
	BYTE ColorArr[4][4];/*rgba, 0:DateTimeColor, 1:ChnNameColor, 2:ChName2Color, 3:MulitRowOsdColor */
	BYTE reser4[128];
}RSNetNew_SoleLivingset_t;

/* output */

typedef struct 
{
    BYTE VideoIndex[32]; /* 每个通道所在的窗口号，数组下标为通道号，值为窗口号 */
    BYTE StreamType[32]; /* 每个通道预览的码流类型， 0-主码流，1-子码流 */

    UINT Margin[4];
    UINT AutoSEQTime; /* 轮循时间间隔 */
    BYTE PreviewMode; /* 预览模式，0-系统预设模式，1-用户自定义模式 */
	BYTE SplitMode;   /* 分屏模式，由UI分屏管理器提供 */
	BYTE CurrentPage; /* 预览通道数大于分屏数时会有多页，该参数记录当前页的索引 */
	BYTE SeletedVideo; /* 当前选中窗口的索引 */
	BYTE IsEnlarged;   /* 记录当前选中的窗口是否处于双击后的放大状态 */
	BYTE SpotAudio;
    BYTE reserve[14];
}Net_voattr_t; // outputset 子结构体

typedef struct 
{
	UINT StructSize;

	Net_voattr_t voattr[4];     /*voattr[0]-HDMI, voattr[1]-VGA, voattr[2]-VOUT, voattr[3]-VSPOT*/ 
	UINT transparency;      /*透明度*/
	BYTE IsVoutOrSpot;    /*0-Vout,1-Spot*/
	BYTE vgaresolution;   /*VGA 分辨率*/
	BYTE initGuiDev;      /*开机时的默认GUI 显示设备:0-VOUT, 1-VGA ,2-AUTO*/
	BYTE ChangeResolutionFlag;/* REVERT_VGARESOLUTION:    0:无改动, 1:有改动, 2:已恢复*/
	BYTE oldvgaresolution;    /*保留更改前的分辨率*/
	BYTE AutoSEQFlag;     /*记录是否轮询，以便重启继续上次状态*/
	BYTE OutputDev;       /*输出设备:0-HDMI,1-VGA,2-VOUT*/
	BYTE voice;
	BYTE EnablePreview[32];        /*预览开关 0-关闭, 1-开启 */
	BYTE reserve[16];    /*保留字节*/
}RSNetNew_Outputset_t;

/* KB setting */
typedef struct 
{
	UINT StructSize;

	BYTE Protocol; /*协议类型，0-Pelco-D，1-Pelco-P*/
	BYTE Baudrate; /*波特率，0-1200，1-2400，2-4800，3-9600*/
	BYTE DataBit;  /*数据位，0-8，1-7，2-6，3-5*/
	BYTE StopBit;  /*停止位，0-1，1-2*/
	BYTE Check;    /*校验，0-None，1-Odd，2-Even，3-Mark，4-Space*/
	BYTE reserver[7];
}RSNetNew_KBset_t;

/* Ftp upgrade */
typedef struct 
{
	UINT StructSize;

	BYTE FtpAddr[16];
	BYTE UserName[32];
	BYTE UserPwd[32];
	BYTE FtpPath[64];
	BYTE ProductName[32];
	UINT FtpPort;
	BYTE FtpUpgradeEnableFlag;/*0==false,  1 == true*/
	BYTE FtpUpgradeTips;      /*0 == false,  1 == true*/
	BYTE resev[6];
}RSNetNew_FtpUpgradset_t;

/* Version info */
typedef struct 
{
	UINT StructSize;
	BYTE reverser[4];

	S8 DeviceType[24];
	S8 AppVer[24];/* 系统升级时使用*/
	S8 UbootVer[24];
	S8 KernelVer[24];
	S8 RootfsVer[24];
	S8 SlaveUbootVer[24];
	S8 SlaveKernelVer[24];
	S8 SlaveRootfsVer[24];
	S8 LogoVer[24];
	S8 MacAddr[24];
	S8 SerialNum[24];
	S8 SWVertion[24];/*UI 上显示使用*/
	S8 IEVertion[24];
	S8 HWVertion[24];
	S8 KBVertion[24];
}RSNetNew_StateParamset_t;



#define MAX_CUSTOMPROTO_NUM 16
/* 自定义码流协议界面 (NVR)*/
typedef struct
{
    UINT Port;
    BYTE Type;           /* 类型 0 RTSP */
    BYTE Transmisson ;	 /*传输协议 0 自动 1 UDP 2 RTP over RTSP*/
    BYTE reserve[2];
    BYTE SourcePath[120];/*资源路径*/
}Net_CustomStream_t;

/* GB28181页面设置结构 */
typedef struct 
{
	UINT StructSize;
	BYTE bIsUsed;
	BYTE szDevId[64];
	BYTE szAlarmId[64];
	BYTE szSipSrvId[64];
	BYTE szSipSrvIp[64];
	UINT nSipSrvPort;
	BYTE szSipSrvPwd[64];
	BYTE reverser[63];
}RSNetNew_Gb28181_t;

/* 自定义码流设置参数 */
typedef struct
{
    UINT StructSize;
    UINT ProtocolMask; 		 //协议掩码
    BYTE EnableSubStream;    //是否启用子码流
    BYTE reserved[3];
    BYTE ProcotolName[16];   //协议名称
    Net_CustomStream_t MainStream;
    Net_CustomStream_t SubStream;
}RSNetNew_SoleCustomProtocol_t;

/* 深广平台远程参数 */
typedef struct
{
    UINT StructSize;          //该结构体大小

    BYTE HostName[MaxNameLen];//Url
    UINT Port;                //端口号
    BYTE AgentId[16];         //12位编码.SSJC开头的任意12位字符
    BYTE Enabled;             //使能开关. 1:enable, 0:disable
    BYTE BeforeTrigger;       //报警触发前时间. 10 ~ 60
    BYTE AfterTrigger;        //报警触发后时间. 10 ~ 60
    BYTE ImgInterval;         //图片时间间隔. 1 ~ 3        
    BYTE reserved[8];
}RSNet_SGPlatform_t;
typedef struct
{
    UINT StructSize;          //该结构体大小
    UINT ChannelMask;         //通道掩码
    BYTE UploadTime1[4];      //定时上传时间点1
    BYTE UploadTime2[4];      //定时上传时间点2
    BYTE Time1Enable;         //时间点1开关
    BYTE Time2Enable;         //时间点2开关
    BYTE reserved[6];
}RSNet_SoleSGPlat_t;

typedef struct
{
	BYTE 	RoiIndex;/*ROI区域的索引,同样也是ROI区域的优先级，索引越大优先级越高*/
	BYTE    RoiSwitch;/*该ROI区域是否使能*/
	BYTE    IsAbsQp;/*是否使用绝对图像质量，0:使用相对质量，1:使用绝对质量*/
	BYTE    ROILevel;/*ROI值的大小，1-6,值越大图像质量越好*/
	BYTE 	ROIBgFrameRate; /*非ROI区域的帧率，在0和最大帧率之间*/
	BYTE    reserve[3];
	UINT    Rect_x;/*ROI所在的矩形区域信息*/
	UINT    Rect_y;/*ROI所在的矩形区域信息*/
	UINT    Rect_w;/*ROI所在的矩形区域信息*/
	UINT    Rect_h;/*ROI所在的矩形区域信息*/
}RSNet_Roi_t;
typedef struct
{
    UINT    StructSize;          //该结构体大小
	UINT    StreamType;          /*1:main 2:sub 4:mobile*/
	RSNet_Roi_t roi[8];
	BYTE	Maxfps;
	BYTE    reserve[7];
}RSNet_SoleRoiParam_t;


typedef struct 
{
    UINT    StructSize;          //该结构体大小
	UINT    ChannelMask; //通道掩码
	BYTE    ODSwitch;          /*镜头遮挡开关0-关闭，1-打开*/
	BYTE    Sensitivity;       /*6个等级:6-高，5-较高..........  1-低*/
	BYTE    EmailLink;         /*邮件联动 开关*/
	BYTE    FtpLink;			/*FTP联动 开关*/
	BYTE    Alarmout;         /*警告 开关*/
	BYTE    LatchTime;			/*延迟时间*/
	BYTE    sendToFTP;/*发送截图到FTP，0：不使能；1：使能*/
	BYTE    RecordDelayTime;     /*post recording*/ /*录像延时，延时时间:10s,30s,1min,2min,5mins*/
	BYTE    ShowMessage;      /*Show Message 开关*/
	BYTE    FullScreen;       /*全屏 开关*/
	BYTE    RecordSwitch;      /*Record  switch*/
	BYTE 	BuzzerMooTime;      /*蜂鸣器鸣叫，鸣叫时间:0，10，20，40，60s*/
	BYTE	res[4];

	UINT    RecordChannel[8];
	BYTE    AlarmOutManager[MAX_ALARMOUT_NUM];
	BYTE    res1;
	BYTE    FtpVideoLink;	/*FTP录像联动 开关*/
	BYTE    CloudPicUpload; /* 云存储视频上传 */
	BYTE    CloudVideoUpload;
	BYTE    reserve[12];
}RSNet_SoleODParam_t;

/* Lorex IPC 无线参数 */
typedef struct
{
    UINT  StructSize;     //该结构体大小
    UINT  ChannelMask;    //通道掩码
    BYTE  SubstreamBrite; //子码流码率
    BYTE  Bright;         //亮度
    BYTE  ChannelEnable;  //通道开关
    BYTE  MotionEnable;   //motion开关
    BYTE  TVSystem;       /*0-PAL; 1-NTSC*/
    BYTE  reserve[3];
}RSNet_SoleIpcWireless_t;

/* Kguard (DVR) P2P ID Used ShangYun */
typedef struct
{
BYTE QrcordWhetherFill;// Sensor Qrcord是否填充标记，1：填充， 0:为不填充
BYTE reserved[7];
BYTE QrcordSY[128]; //sensor qrcord

}SENSORQRCORD;

/* Kguard (DVR) P2P ID Used ShangYun */
typedef struct
{
    UINT StructSize;

    BYTE P2pIdSY[128]; //
    BYTE reserve[4];
	
	BYTE RFIdSY[128]; //RF did
	SENSORQRCORD QrcordSY[8];
	BYTE reserved[8];
}RSNet_KguardP2pParam_t;

/*****电网项目私有参数 2016.05.25*****start*/

typedef struct Eplateform_s
{	
	UINT StructSize;			//结构体大小

	char device_name[128];		// 设备名称
	char device_ip[32];			// 设备IP
	char passwd[64];			// 用户密码
	char device_id[32];			// 设备编码/sip user
	char channel_id[64][32]; 	// 设备通道编码ID
	char platform_ip[16];		// 电网平台IP
	char platform_id[32];		// 电网平台编码ID
	char scenes_id[32];			// 电网平台场景编码ID
	int  sip_port;				// 电网平台SIP 端口
	int  rtsp_port;				// 电网平台RTSP 回放端口

	BYTE expire;				//心跳时间， 0~120
	BYTE reserve;			//预留位
	short remotePort;			//远程端口
}Eplateform_t;

/*************电网项目私有参数**********end*/

typedef struct
{
    BYTE schedule[8][48];      //计划表
}SirenSetup_t;
typedef struct
{    
    WORD DurationTime;     //报警铃声持续时间: 0～5000
    BYTE RecDelayTime;     //录像延时，延时时间:0, 10, 20, 40, 60s
    BYTE SirenEnable;      //Siren 开关
    UINT RecChannel;       //录像通道,按位表示通道号
    BYTE ShowMessage;      //Show Message 开关
    BYTE SendEmail;        //Send Email 开关
    BYTE Record;           //通道录像开关
    BYTE PushEnable;       //推送开关
    UINT SirenIdSel;       //当前选择的传感器ID
    
    BYTE SendFTP;          //Send FTP 开关
    BYTE IlluminationRing; //光照环0, 不使能, 1. 使能
    BYTE AudioAlert;       //音频警报0, 不使能, 1. 使能
    BYTE AudioSelect;      //报警声音选择 0, Doorbell 1.Ringtone, 2.Siren
    BYTE AlarmDurationTime; //警报持续时间0-10s/1-30s/2-60s
    BYTE reserved1[3];  
}SensorActionSetup_t;

typedef struct
{
    UINT StructSize;
    BYTE SensorName[24];//报警类型名称
    BYTE SensorState; //无线连接状态显示0: connnected, 1: Disconnected, 2: Error
    BYTE SensorOutTime;    //Sensor报警延迟时间,延迟时间为10, 20, 40, 60s
    BYTE SensorNo;		   //Sensor 序号
    BYTE SensorRuleEnable;  //Sensor 报警类型开关
    UINT NodeId;      	   //报警类型ID
    BYTE AlarmType;        //设备类型0-Door, 1-PIR, 2-Smoke Alarm,
    BYTE SensorNum;        //报警设备总个数
    BYTE reserved[2];
    union
    {
        SirenSetup_t Siren;
        SensorActionSetup_t  SensorAction;
    };
}RSNet_SoleKGSensorParam_t;

/* 网线断开告警页面参数结构 */
typedef struct {
	UINT StructSize; /* 该结构体大小*/
	UINT ChannelMask; 	
	BYTE ChnSwitch;/*是否启用网线断开告警 0. 不启用，1. 启用*/
	BYTE SendEmail;
	BYTE BuzzerMooTime;
	BYTE Reservel[5];
	UINT RecordChannel;
	BYTE RecordDelayTime; /*录像延时时间*/
	BYTE Record; /* 触发录像开启总开关  0. 不启用，1. 启用*/
	BYTE AlarmOut;
	BYTE IPPushableSwitch;
	BYTE IPPushableAlarmOut;
	BYTE Reservel2[39];
}RSNet_NetBreakSet_t;

typedef struct /* 手机APP 信息 */
{
	UINT StructSize; /* 该结构体大小*/
	int	msg_type;				/* push message type 0-3, default 0(message) */
	int device_type;			/* device tpye 1-5, 3->android 4->IOS */
	int	push_flag;				/* 1->push  other->not push */	
	int push_type;				/* BAIDU_ANDROID, and so on */
	int status;					/* only IOS , Android default 0
									baidu:  1---> Develop status
											2---> Produce status
									QQ   :  1---> Produce status
									        2---> Develop status
								*/
	unsigned int access_id;	    /* qq xg: access ID */
	int resev;
	char device_token[256];		/* device token 
								   */
	char channel_id[256];		/* baidu: channelID
								*/
	char api_key[256];			/* baidu or qq  app apiky */
	char secret_key[256];		/* baidu or qq  app  secretkey */
	char deviece_name[256];		//device alias in phone
	char phone_name[256];
	char phone_type[256];
}RSNet_PushInfo_t;

typedef struct 
{
	UINT StructSize;
	int prefixlen;
	char Local_ipv6_addr[40];
	char Global_ipv6_addr[40];
	char ipv6_dns_addr[40];
	char relsove[8];
}RSNet_IPV6_t;

/* 混合DVR模拟通道页面信息 */
typedef struct
{
    UINT StructSize; /*该结构体大小*/
	UINT ChannelMask;/*通道掩码*/    
    BYTE ChnName[20];/*通道名称*/
    BYTE Status;     /*通道使用状态. 0 : close; 1 : open*/
    BYTE reserved[2];
	BYTE NewNameFlag; //1表示使用ExtendChnNameMask,0表示使用ChnName
	BYTE ExtendChnNameMask[64];/*通道名称扩展*/
}RSNet_SoleAnalogCam_t;

/* 混合DVR抓图设置参数结构 */
typedef struct
{
	UINT StructSize;     /*该结构体大小*/
	UINT ChannelMask;    /*通道掩码*/
	BYTE ChnEnable;      /*通道开关 0:close, 1:open*/
	BYTE ManualEnable;   /*手动抓图开关 0:close, 1:open*/
	BYTE StreamType;     /*码流类型 0:主码流, 1:子码流*/
	BYTE NormalCapInterv;/*普通抓图时间间隔*/
	BYTE AlarmCapInterv; /*报警抓图时间间隔*/
	BYTE reserved;
	BYTE AlarmCapEncType;/*alarm类型抓图分辨率, 0-960,1-720,2-1080*/
	BYTE AlarmCapQuality;/*alarm类型抓图质量, 0-60,1-75,2-90*/
	RSNetNew_ResolutionRateRange_t BigRange[3];/*大码流列表*/
	RSNetNew_ResolutionRateRange_t LittleRange[3];/*小码流列表*/
	BYTE reser[256];
}RSNet_SoleCaptureSet_t;

/* 混合DVR抓图计划表 */
typedef struct
{
    UINT StructSize; 	//该结构体大小
    UINT ChannelMask; 	//通道掩码

    /* bit 1为Normal抓图, bit 2 为Motion抓图, bit 3 为IO抓图
     * 对应的bit位为1表示设置，为0表示清零
     */
    BYTE HalfHour[8][48]; //7days, 48 halfhours    
}RSNet_SoleCapSchedule_t;

/* 0通道分屏模式 */
typedef enum 
{
    ZeroCh_One,
    ZeroCh_Four,
    ZeroCh_Six,
    ZeroCh_Eight,
    ZeroCh_Nine,
    ZeroCh_Sixteen
}ZeroChSplitMode_e;

/* 0 通道录像设置 */
typedef struct 
{
    UINT  StructSize;   /*该结构体大小*/
    BYTE  ChnName[64];  /*通道名称*/
    BYTE  Position;     /*0-左上，1-左下，2-右上，3-右下*/
    BYTE  fps; 	        /*帧率: 1~25/30帧*/
    BYTE  resolution;   /*分辨率参见RESOLUTION_E */
    BYTE  zeroChnSwitch;/* 0 通道开关 : 1-开,0-关 */
    BYTE  bitrate;      /*录像码率32 ~8192kbps : 对应索引0~27*/
    BYTE  SplitMode;    /* 分屏模式,对应 ZeroChSplitMode_e */    
    BYTE  DwellTime;    /*轮循时间. 0-no switch, 1-5s, 2-10s, 3-20s,
                          4-60s, 5-120s, 6-300s*/
    BYTE  reserved[5];
    BYTE  ChnList[256];  /*通道索引列表, 0xff-不配置通道,实际通道号从0开始
                                           有效索引下标< 最大通道数*/
    BYTE  reserved2[16];
}RSNet_ZeroChnSet_t;

/* 通过远程设置系统关键参数 */
typedef struct 
{
	UINT StructSize;

	UINT ParamTypes;     /*远程设置的参数类型,由板端决定*/
	UINT reserve;
	UINT AngleRotation; /*IPC图像旋转度数 0-不旋转，1-顺时针旋转90度，2-顺时针旋转180度， 3-顺时针旋转270度*/

	BYTE MainBoardName[16]; /*主板型号 RS-DM-XXXX*/
	BYTE Password[24]; /*针对ITEX客户给每一台机器分配唯一的admin密码*/
	BYTE SerialNumber[16]; /*针对ZIP客户给每一台机器分配唯一的序列号*/
	BYTE ProductType[64];	/*产品型号	*/
	BYTE DeviceType[32];	/*设备型号	*/
	BYTE DeviceName[32];    /*设备名称	*/
	BYTE CustomType[32];	/*客户类型	*/
	ULONGLONG FunctionCode;	/*产品功能码	*/
	BYTE SupportFourHddDisk;/*支持4个硬盘*/
	BYTE languageConfig;/*韩华板端语言选择*/
	BYTE language;/*韩华板端语言选择*/
	BYTE SerialNumberEX[32]; /*序列号，暂时有Lorex客户在用*/
	BYTE ProductCode; /*依据此参数配置同一程序不同的设备名称或者其他，由APP决定*/
	BYTE Videoformat; /*视频制式 参考TVSYSTEM_T*/
	BYTE reservedl[1];
	BYTE EnableEsata;
	BYTE EnableHddGroup;
	BYTE AlarmOutputNum;
	BYTE AlarmInputNum;
	BYTE AudioNum;
	BYTE reserved;
	BYTE PoePowerFlag;  /*启动POE功率配置, 1:启用 0:不启用*/
	BYTE res[3];
	WORD PoePower;      /*POE功率*/
	BYTE KeyParams[742];/*关键参数项,由板端决定*/
}RSNet_KeyBackupSet_t;

/* 混合DVR通道信息参数 */
typedef struct
{
    UINT StructSize;    /*该结构体大小*/
	UINT ChannelMask;   /*通道掩码*/
    
    BYTE ChnStatus;     /*通道状态.*/
    BYTE ConfigStatus;  /*按位表示,bit1:移动侦测状态, bit2:视频遮挡状态.0-disable, 1-enable*/
    BYTE SupportTypes;  /*支持的码流类型.按位表示,bit1:main, bit2:sub, bit3:moile
                          ,bit4~bit8之后保留, 0-disable, 1-enable*/
    BYTE reserved;
    BYTE ChnAlias[36];  /*通道别名*/
    
    WORD ResWidth[4];   /*分辨率宽,索引依次为main, sub, mobile*/
    WORD ResHeight[4];  /*分辨率高,索引依次为main, sub, mobile*/        
    UINT Bitrate[4];    /*比特率,索引依次为main, sub, mobile*/
    BYTE Fps[4];        /*视频帧率,索引依次为main, sub, mobile*/
    BYTE reserved1[11];
	BYTE NewChnAliasFlag; //1表示使用ExtendChnNameMask,0表示使用ChnAlias
	BYTE ExtendChnAliasMask[64];/*通道名称扩展*/
}RSNet_SoleChnInfo_t;

/* 混合DVR录像信息参数 */
typedef struct
{
    UINT StructSize;    /*该结构体大小*/
	UINT ChannelMask;   /*通道掩码*/
    
    BYTE RecStatus;     /*录像状态*/
    BYTE RecType;       /*录像类型*/
    BYTE Fps;           /*视频帧率*/
    BYTE reserved;
    UINT Bitrate;       /*比特率*/
    WORD ResWidth;      /*分辨率宽*/
    WORD ResHeight;     /*分辨率高*/
	BYTE RecStreamMode;
	BYTE RecordSwitch;
    BYTE reserved1[10];
}RSNet_SoleRecInfo_t;

typedef struct {
	UINT StructSize; /* 该结构体大小*/
	UINT ChannelMask; /* 通道掩码*/

	/* event */

	BYTE WirelessAlarmSensor; /*外部sensor 触发 使能0, 不使能, 1. 使能*/

	/* actions */
	BYTE Record; 			  /*  录像联动使能0, 不使能, 1. 使能 */
	BYTE RecordDelayTime;/* 录像延时时间0-5s , 1-10s , 2-20s , 3-30s  */
	BYTE SendEmail; /*  SendEmail 联动使能0, 不使能, 1. 使能 */
	BYTE FtpLink;/*FTP 联动使能0, 不使能, 1. 使能*/
	BYTE PushSwitch;   		/*推送联动使能0, 不使能, 1. 使能*/

	/* away */
	BYTE IlluminationRing; /* 光照环0, 不使能, 1. 使能   */
	BYTE AudioAlert; /* 音频警报0, 不使能, 1. 使能 */
	BYTE AudioSelect; /* 报警声音选择 0, Doorbell 1.Ringtone, 2.Siren */
	BYTE AlarmDurationTime; /* 警报持续时间0-10s/1-30s/2-60s */

	BYTE RecordTime; /* 录像时间 0-5s/1-10s/2-20s /3-30s */

	BYTE SensorOutTime;    //Sensor报警延迟时间,延迟时间为0, 10, 20, 40, 60s

	BYTE Reservel[36];

}RSNet_SoleSensorSet_t;

typedef struct 
{
	BYTE mount_mode;
	BYTE show_mode;
	BYTE Reservel[2];
	float init_angle; //鱼眼软解，初始角度
	BYTE unused[8];
}FishEyeMode_t;

typedef struct
{
	short x;
	short y;
	short w;
	short h;
}PtzPos_t;

typedef struct
{ 
	UINT StructSize;
	BYTE code_mode;
    BYTE cur_pos;
    BYTE bsave_pos;//	
	BYTE unused[9];
	FishEyeMode_t mode[2];
    PtzPos_t	pos[4];
}RSNet_FishEye_t;

/*交换机页面配置*/
typedef struct{
    UINT StructSize;    		/*该结构体大小*/	
	
	BYTE  IPAddr[4];   			/*IP地址*/
	BYTE  NetMask[4];  			/*子网掩码*/
	BYTE  GateWay[4];  			/*网关*/
	BYTE  TransmissionMode[16]; /*传输距离，0-普通*/	
	BYTE  SwitchMode;	 		/*交换机模式 0-自动 1-手动*/
	BYTE  Reservel[15];			/*保留字节并字节对齐*/
}RSNet_SwitchSet_t;

/* Sensor Control页面参数结构 */
typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 	//通道掩码
	BYTE SensorType;  /*Sensor类型(只读,用户不可修改)*/
	BYTE ChnSwitch; /*是否启用Sensor<RS_Close, RS_Open>*/
	BYTE SendEmail; /*Send Email 开关<RS_Close, RS_Open>*/
	BYTE BuzzerMooTime; /*蜂鸣器鸣叫时间*/
	UINT RecordChannel; /*Record Channel, 触发通道录像，按位记录*/
	BYTE SirenTime; /*报警器时间*/
	BYTE RecordDelayTime; /*录像延时时间*/
	BYTE Record; /*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE ShowMessage; /*Show Message <RS_Close, RS_Open>开关*/
	BYTE FullScreen; /*FullScreen 开关 报警全屏<RS_Close, RS_Open>*/
	BYTE PushSwitch;    /*是否开启Sensor触发报警推送, 0: close; 1: open.*/
	BYTE Reservel[2];
	UINT RecordChannel_EX[8];
}RSNet_SoleSensorCtrlSet_t;

typedef struct 
{
	UINT  structsize;    //结构体大小
	UINT  channel;		//通道数
	BYTE  AFMode;		//AF模式：3-SEMI / 2-AUTO / 1-MANUAL / 0-OFF*/
	BYTE PowerMode;   //通电模式：2-WIDE /1-SAVE POSI / 0-OFF
	BYTE TDNAFSwitch; //模式切换：0-OFF-白天-晚上 /1-ON-晚上-白天
	BYTE LensInitSwitch;//镜头初始化开关，重新初始化，光学和获取光学。0-OFF 1-ON
	BYTE Reserved[20];
}RSNet_IPCAutoFocusInfo_t;

typedef struct _newcloudstorage_t
{
	UINT  structsize;    //结构体大小
	BYTE CloudType;       /*云存储类型DropBox ---0  */

	BYTE Dropboxtoken[128];
	BYTE cloudEnable;
	BYTE HttpsEnable;
	BYTE SupportVideo;			/* 是否支持视频上传功能 */	
	BYTE MaxChnRecNum;			/* 最大录像通道数 */	
	BYTE CloudOverwrite;		/*自动覆盖过期录像开启标识，0-关闭，1-auto,2..1-3-5-7-14-30-90days */
	BYTE CloudStatus;			/* 云存储的状态 0.正常, 1.空间满, 2.未激活, 3.网络堵塞 */
	BYTE IntervalTime;			/*视频上传间隔*/
    BYTE VideoType;			    /* 视频格式, 对应RS_VIDEO_TYPE_E */
	BYTE reserve[23];
	UINT ChnRecordEnable[8];		 /* 录像通道是否开启录像 */

}RSNet_NewCloudStorage_t;

typedef struct _clodusole_t
{
	UINT  structsize;    //结构体大小
	UINT  ChannelMask[8]; 	//通道掩码

	BYTE DriveName[64];   /*上传目录*/
	BYTE MotionEnable;
	
	BYTE VideoBKFormat;	/* 视频备份类型,值对应RS_VIDEO_BACKUP_FORMAT_E */
	BYTE StreamType;	/* 视频备份码流类型, 对应STREAM_TYPE_E */
	BYTE RecordTime; 	/* 录像时间0:10s, 1:20s, 2:30s, 3:60s */
	
	BYTE MotionRecordEnable; /* 录像motion类型使能 */
	BYTE IoAlamRecordEnable; /* 录像IO类型使能 */
	BYTE PirRecordEnable;    /* 录像PIR类型使能 */
	BYTE IntelRecordEnable;  /* 录像智能分析类型使能 */
    BYTE reserve[56];
}RSNet_soleNewCloudStorage_t;

typedef enum _FB_RESOLUTION_E
{
    FB_RES_800X600 = 0,
    FB_RES_1024X768,
    FB_RES_1280X1024,
    FB_RES_1440X900,
    FB_RES_1280X720,
    FB_RES_1920X1080 = 5,
    FB_RES_1680X1050,
    FB_RES_1600X1200,
    FB_RES_1900X1200,
    FB_RES_2560X1440,
    FB_RES_3840X2160 = 10
} FB_RESOLUTION_E;

typedef struct {
    UINT StructSize;     /*该结构体大小*/
    UINT UseMask[4];      /*从OutputDevFlag字段开始每个功能是否显示 bit0表示OutputDevFlag */
    UINT ResolutionMask[4]; /*FB_RESOLUTION_E, 对于bit置1表示显示*/
    UINT SplitModeMask[4]; /*轮循分屏模式能力: 对应SeqSplitMode, bit置1表示显示 */
    UINT OutputDevFlag;   /*输出设备能力:bit0-HDMI,bit1-VGA/VGASOPT, bit2-VOUT*/
    UINT AutoSEQTime[4];  /* 轮循时间间隔 5~300*/
    BYTE SeqSplitMode[4]; /* 轮循分屏模式0~20 对应文本:" 1,4,6,8,9,10,10-1,12,13,13-1,14,16,17,19,20,22,25,32,36,42,49 " */
    BYTE resolution[4];   /*FB_RESOLUTION_E*/
    BYTE transparency[4]; /*透明度 0~128*/
	BYTE HDMIOverscan;	  /*过扫描*/
	BYTE HideNCD;
	BYTE SpotOutSplitModeMode[2];/*0-dynamic 1-static*/
	BYTE IsStaticMode[4]; /*0-dynamic, 1-static -------->> View SetUp（UI界面对应的）*/
	BYTE IsEnFullScreen[4];/*0-Disable, 1-Enable ----->> FULL Screen（UI界面对应的）*/
	UINT SpotPollFlag[8]; /*记录是否SPOT轮跳，每位标记一个通道 ------>> Dynamic模式下点Select Cameras（UI界面对应的）*/
	BYTE VideoIndex[4][256];/*每个窗口对应的物理通道号，数组索引为窗口号，数组元素为通道号------>> Static模式下点Select Cameras（UI界面对应的）*/ 
	UINT SpotOutSplitModeMask[2];/*0-dynamic 1-static*/
	BYTE IsSpot;   /*SPOT-OUT的使能开关*/
	BYTE reserve2[55];
}RSNet_Output_t;

typedef struct 
{   
	UINT  StructSize;
	UINT  channel;
	UINT  county;
	UINT  reg;
	BYTE  region;
	BYTE  wifiVersion[32];
	BYTE  reserve[7];
}RSNet_CountryCode_t;
typedef struct 
{
	char ssid[32];
	char pwd[32];
	char bssid[32];
}RSNet_SwannRepeat_t;

typedef struct 
{
	char mac[32];   //mac地址
	char ssid[32];  //路由AP 名字
	char psw[32];   //路由密码
}RSNet_SwannRouterMacSSIDPSW_t;


typedef struct 
{   
	UINT  StructSize;   //结构体大小
	UINT  ChannelMask; 	//通道掩码
    RSNet_SwannRepeat_t  Sr[5];
    RSNet_SwannRepeat_t  Sc[3];
	RSNet_SwannRouterMacSSIDPSW_t RouterInfo;
	UINT  signalIntensity;
	BYTE  reserve[164];
}RSNet_SoleSwannIpcRepeat_t;

typedef struct 
{     
	UINT  StructSize;     //结构体大小
    BYTE  ssid[32];      //路由名字   
	BYTE  pskValue[32]; //路由密码
	BYTE  security[48];  //加密方式
	BYTE  reserve[84];
}RSNet_SwannRouterRepeat_t;


typedef struct 
{     
	UINT  StructSize;     //结构体大小
    BYTE  ssid[32];      //ap名字
	BYTE  mac[32];      
	BYTE  security[48];  //加密方式
	UINT  rssi;         //信号强度
	BYTE  reserve[80];
}RSNet_SoleSwannRouterRepeat_t;
typedef struct 
{
      int   structsize;
	UINT RuleCnt;				/*已添加的过滤规则条数*/

	BYTE RuleAddr[16][16];		/*过滤规则网络地址*/
	BYTE RuleMode[16];			/*规则过滤模式: 0~IP过滤, 1~MAC过滤*/
	BYTE FilterEnable;			/*过滤开关: 0~关, 1~开*/
	BYTE FilterMode;			/*过滤模式: 0~允许列表, 1~黑名单*/
	BYTE reversed[22];
}RSNet_NetFilter_t;
typedef struct 
{
	int   structsize;
	char  ReportIpAddr1[64];   /*服务器地址*/
    char  ReportIpAddr2[64];   /*备用服务器地址*/
    UINT Port1;               /*服务器端口*/
    UINT Port2;               /*备用服务器端口*/
    UINT ReportTypeMask;		/*可用的报告类型, 按位表示。有多少位为1就有多少行*/
								/*bit0为1则显示id为00的一行,ReportType的值为枚举0 ALTE_REPORT_TYPE_E*/
								/*bit1为1则显示id为01的一行,ReportType的值为枚举1 ALTE_REPORT_TYPE_E*/
	UINT ReportType;			/*报告开关，如bit0为1则id为00的状态为on*/
    BYTE  ReportPeriod;        /*报告间隔: OFF, 1,2,5,10,30min, 1,2,6,12h, 1,2,7day*/
	char  EnableReport;        /*报告使能: 0-Disable, 1-Enable*/
    BYTE  reserve[10];
}RSNet_ALTEReport_t;

typedef enum _ALTE_REPORT_TYPE_
{
	ALTE_REPORT_ONLINE = 0,
	ALTE_REPORT_HDD,
	ALTE_REPORT_RECORD,			/*录像状态*/
	ALTE_REPORT_VIDEOLOSS,
	ALTE_REPORT_CHNINFO = 8,
	ALTE_REPORT_RECINFO,		/*录像信息，对应System菜单中的Record Info*/
	ALTE_REPORT_MAX
}ALTE_REPORT_TYPE_E;

/* GB28181页面参数结构 */

/* GB28181页面参数结构 */
typedef struct 
{
	UINT	StructSize; 			//该结构体大小
	UINT	server_port;		
	BYTE	server_ip[32];   
	BYTE	server_id[64];
	BYTE	device_id[64];
	BYTE	channel_nvr_id[64][64];
	BYTE	pwd[32];
	BYTE 	alarm_id[32];
	BYTE    enableflag;     // 1:Enable , 0:Disable
	BYTE    transprotocol;  // 1:UDP , 0:TCP
	UINT    local_port;
	BYTE    reserved2[10];
}RSNet_GB28181Param_t;

typedef struct {
	UINT StructSize;
	UINT chanmask;
	BYTE ChnSwitch;
	BYTE MotionLinkage;
	BYTE IOLinkage;	
	BYTE PIRLinkage;
	BYTE IntelliLinkage;
	BYTE  reserve[3];
	BYTE AlarmLinkagePtzChn[32];
	BYTE LinkagePtzPointIndex[32];
	BYTE AlarmLinkPtzEnable[32];
}RSNet_SoleAlarmLinkagePtz_t;

typedef struct {
	UINT StructSize;
	BYTE reserve[4];
	BYTE ChnCruiseTime[256][256];
}RSNet_AlarmLinkagePtz_t;

typedef struct 
{
	UINT StructSize; 			//该结构体大小
	BYTE Reserve1[4];			//保留字节
	DateTime time; 				//系统时间
	unsigned long long LanguageMask;		//设备支持的语言,按位设置
	unsigned long long AreaMask;			//设备支持设置的区域，按位设置
	BYTE selLanguage;			//当前选择的语言
	BYTE selArea;               //当前选择的区域
    BYTE TimeMode;				//时间格式: 0:24Hour  1:12Hour
	BYTE TimeDisplayMode;       //时间显示模式：0:AM  1:PM
	BYTE DateMode;				//日期格式: 0:MM/DD/YY 1:YY-MM-DD 2:DD/MM/YY
    BYTE TimeZone;				//时区
	BYTE Frequency;             //频率
	BYTE NetworkTimeCheck;		//网络校时结果: 0:成功 其它：失败
	BYTE Reserve2[16];
	BYTE cityName[128];
}RSNet_WizardInfo_t;

typedef struct _UI_POINT_S {
	unsigned short x;
	unsigned short y;
} RSNet_POINT_t;

typedef struct {
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 	//通道掩码

	/*侦测8个等级*/
	BYTE Sensitivity;
	/*是否启用PIR 和 移动侦测<RS_Close, RS_Open>*/
	BYTE ChnSwitch;
	/*Send Email 开关<RS_Close, RS_Open>*/
	BYTE SendEmail;
	/*蜂鸣器鸣叫时间*/
	BYTE BuzzerMooTime;
	/*Record Channel, 触发通道录像，按位记录*/
	UINT RecordChannel;
	/*录像延时时间*/
	BYTE RecordDelayTime;
	/*Record channel switch 触发录像开启总开关 <RS_Close, RS_Open>*/
	BYTE Record;
	/*Show Message <RS_Close, RS_Open>开关*/
	BYTE ShowMessage;
	/*FullScreen 开关 报警全屏<RS_Close, RS_Open>*/
	BYTE FullScreen;
	/*区域设置，180个区域，用32个字节表示，每位表示一个区域*/
	BYTE RegionSetting[32];	/* LoginRsp MotionMode字段:0,使用当前字段*/
	/* 宏块行数  只有 LoginRsp MotionMode==2时,这个值才是有效的*/
	BYTE MbRow;
	/* 宏块列数 只有 LoginRsp MotionMode==2时,这个值才是有效的*/
	BYTE MbCol;
	/*Alarm Out 开关<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*报警输出时间*/
	BYTE AlarmOutTime;
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	/*区域设置，200个区域，用32个字节表示，每位表示一个区域*/
    //BYTE RegionSetting3531[200];  /* LoginRsp MotionMode字段:1或2,使用当前字段*/
    union {
        struct {
            BYTE RegionSetting3531[200];  /* LoginRsp MotionMode字段:1或2,使用当前字段*/
        }BlockRegion;
        struct
        {
            BYTE MotionNum[4];  /* 对应区域是否启用，为1启用，为0不启用 */
            RSNet_Rect_t Rect[4];
            BYTE Sensitivities[4]; /*11个等级:0-高，1-较高，2-中，10:最低*/
            UINT  RectMaxNum;    /*motion max rect num 2016.10.19 add*/
        }RectRegion;
    };

	BYTE FtpLink;			/*FTP联动 开关*/
	BYTE PushSwitch;    /*是否开启移动侦测报警推送, 0: close; 1: open.*/
	BYTE WirelessAlarmSensor; /*外部sensor 触发 使能0, 不使能, 1. 使能*/
	BYTE LlluminationRing; /* 光照环0, 不使能, 1. 使能   */
	BYTE AudioAlert; /* 音频警报0, 不使能, 1. 使能 */
	BYTE AudioSelect; /* 报警声音选择 0, Doorbell 1.Ringtone, 2.Siren */
	BYTE AlarmDurationTime;/*0: 10s , 1: 30s, 2: 60s*/
	BYTE CloudNotify; /*报警云上传使能控制*/
	
	BYTE PIRFlag;
	BYTE SensitivityMode;//0:8个等级模式，1:1-100模式
	BYTE PIRTestEnable;	//是否允许PIR测试模式, 0: 不允许, 1：允许

	BYTE LightLinkage;/*白光灯motion联动开关 0:不联动 1:联动*/
	BYTE LoudSpeaker;/*扬声器开关 0:关 1:开*/
	BYTE FtpVideoLink;         /*FTP录像联动 开关*/
	BYTE CloudPicUpload; /* 云存储图片上传 */
	BYTE CloudVideoUpload;
	BYTE Reservel[24];
	UINT RecordChannel_EX[8];
	/*取bit位:3表示一个通道最多3个报警输出,每个报警输入触发后可以联动到
	32*8= 256路的任何通道报警输出*/
	BYTE AlarmOutManagerEx[3][32];
	RSNet_POINT_t DetectArea[8];  /* 预留支持8点区域，现在使用6点区域 */
}RSNet_SolePirMotionSet_t;


//电网平台智能算法识别类型定义
typedef enum 
{
	JD_VAC_TYPE_OBJECT_ABANDONED_DETECTION = 0, //遗留物检测 
	JD_VAC_TYPE_OBJECT_REMOVED_DETECTION = 1, //物体移除检测 
	JD_VAC_TYPE_TRIPWIRE_DETECTION = 2, //绊线检测 
	JD_VAC_TYPE_INTRUSION_DETECTION = 3, //入侵检测 
	JD_VAC_TYPE_RETROGRADE_DETECTION = 4, //逆行检测 
	JD_VAC_TYPE_LOITERING_DETECTION = 5, //徘徊检测 
	JD_VAC_TYPE_LICENSE_PLATE_RECOGNITION = 6, //车牌识别 
	JD_VAC_TYPE_METER_RECOGNITION = 7, //智能读表 
	JD_VAC_TYPE_SWITCH_RECOGNITION = 8, //刀闸状态分析 
	JD_VAC_TYPE_BREAKER_RECOGNITION = 9, //断路器状态分析 
	JD_VAC_TYPE_HELMET_RECOGNITION = 10, //安全帽佩戴检测 
	JD_VAC_TYPE_SMOKE_FIRE_RECOGNITION = 11, //烟火检测 
	JD_VAC_TYPE_METAL_CORROSION_DETECTION = 12, //金具锈蚀检测 
	JD_VAC_TYPE_BIRD_NEST_DETECTION = 13, //杆塔鸟巢检测 
	JD_VAC_TYPE_LEAVE_OFFICE_CHECK = 14, //离岗稽查 
	JD_VAC_TYPE_OBJECT_CLASSIFICATION = 15, //目标分类 
	JD_VAC_TYPE_VIDEO_DIAGNOSIS = 16, //视频诊断 
	JD_VCA_RED_MANTLE_DETECTION = 101 //红布幔检测,非标准定义类型(识别结果可归类至物体移除JD_VAC_TYPE_OBJECT_REMOVED_DETECTION)
}JD_VCA_TYPE_ENUM;

//电网平台智能读表配置 JD_VAC_TYPE_METER_RECOGNITION
typedef struct
{	
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 	//通道掩码
	int left;		//仪表左像素点
	int top;		//仪表上像素点
	int width;		//仪表宽
	int height;		//仪表高
	int begangle;	//起始角度
	int anglescale;	//角度范围
	int initv;		//起始值
	int valuescale;	//量程
	char Enable;
	char reserve[7];
}RSNet_SoleJDVCAMeterRecongitionConfig_t;



//电网平台坐标点定义
typedef struct
{
	int x;
	int y;
}JD_VCA_Point;

#define MAX_VCA_POINTS  16		//算法可设置的最多坐标点个数

//电网平台区域入侵算法参数 JD_VAC_TYPE_INTRUSION_DETECTION
typedef struct
{
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 	//通道掩码
	int totalPoints;						//坐标点个数
	JD_VCA_Point points[MAX_VCA_POINTS]; 	//坐标点
	float imgResizeFactor;					//图像缩放比率(增加该值可提高小目标的检测率)
	float minPersonConf;					//人体检测置信度阈值
	int skipFrameNum;						//背景更新起始帧数（部分摄像头前几帧不稳定）
	int bgsUpdataFactor;					//背景检测更新率（整数、越大更新越慢）
	int BBSInRoiThr;						//判断ROI内有人体的阈值（像素数）
	int fgInRoiThr;							//判断ROI内有前景的阈值（像素数）
	int fgPesBBThr;							//前景框尺寸阈值
	float minOverlapRatio;					//前景与人体重叠阈值
	float pesRectRatio;						//人体高度与检测框默认比值
	float pesRectMaxRatio;					//人体高度与检测框最大比值
	float footRectRatioFrom;				//脚部区域与检测框比值起始点（预留）
	float footRectRatioTo;					//脚部区域与检测框比值截止点（预留）
	char Enable;
	char reserve[11];
}RSNet_SoleJDVCAIntrusionDetectionConfig_t;



//电网平台区域红布幔检测参数 JD_VCA_RED_MANTLE_DETECTION
typedef struct
{
	UINT StructSize; //该结构体大小
	UINT ChannelMask; 	//通道掩码
	float fImgResizeFactor;			//图像缩放比率(增加该值可提高小目标的检测率)
	float minCircleConf;			//标志检测最低置信度（过滤低置信度结果）
	float filterSeconds;			//滤波时长
	int minFilterSize;				//最小滤波数据量
	int nSkipFrames;				//背景检测从第skipFrameNum帧初始化（前几帧不稳定）
	float bgsUpdateSecondsSlow;		//慢背景检测更新周期
	float bgsUpdateSecondsFast;		//快背景检测更新周期
	float fDetectRatioFixed;		//确定为稳定标志的检测率阈值
	float fDetectRatioLosted;		//确定为丢失状态的检测率阈值
	float fDetectRatioOcclusion;	//确定为遮挡状态的检测率阈值
	float fDetectRatioNonOcclusion;	//确定为非遮挡状态的检测率阈值
	float vanishKeepSeconds;		//丢失状态持续到删除的时间
	float toFixKeepSeconds;			//待固定等待时间
	float occlusionKeepSeconds;		//遮挡持续到转丢失状态的时间
	float toMonitorWaitSeconds;		//初始化阶段进入监测阶段的时间间隔
	float reinitWaitSeconds;		//重新进入初始化阶段的时间间隔
	char Enable;
	char reserve[7];
}RSNet_SoleJDVCARedMantleDetectionConfig_t;



//芯桥人脸检测算法参数结构体
typedef enum SIA_ImageType
{
	SIA_ImageType_YUV420sp=1,
	SIA_ImageType_YUV420p,
	SIA_ImageType_YUV420p_Y,
	SIA_ImageType_RGB,
	SIA_ImageType_BMP,
	SIA_ImageType_JPG,
	SIA_ImageType_PNG,
	SIA_ImageType_GIF
}RSNet_SIA_ImageType;
typedef struct _sia_int_param_t_
{
	UINT 	StructSize;
	UINT 	ChannelMask;
	UINT  	faceSensitivity;			/*人脸检测灵敏度，范围0-100*/
	UINT	faceQualityEnhancement;		/*人脸质量增强，开/关，默认开*/
	UINT	picQuality ;			/* 人脸图片编码质量，范围0-100，值越大编码质量越高*/
	UINT 	ploy;/*策略编号，范围：1~3*/
	UINT	bigSourceImageWidth;/*图像分析模块获取的原始大图图像宽度*/
	UINT 	bigSourceImageHeight;/*图像分析模块获取的原始大图图像高度*/
	UINT 	smallSourceImageWidth;/*图像分析模块获取的原始小图图像宽度*/
	UINT 	smallSourceImageHeight;/*smallSourceImageHeight：图像分析模块获取的原始小图图像高度*/
	UINT 	sceneNumber;/*场景模式编号；范围：>=1*/
	UINT 	minFaceWidth;/*人脸检测时人脸的最小像素宽度*/
	UINT 	maxFaceWidth; /*人脸检测时人脸的最大像素宽度*/
	UINT 	minFaceHeight;/*人脸检测时人脸的最小像素高度*/
	UINT 	maxFaceHeight;/*人脸检测时人脸的最大像素高度*/
	UINT 	isSendFullImage;/*在发送选优后的人脸图像时，是否发送对应的全局图像*/
	UINT 	isPreviewFaceInfo;/*是否在预览时叠加人脸框。0：不叠加；1：叠加*/
	int faceImageType;/*图像分析模块返回的人脸图像类型*/
	int fullImageType;/*图像分析模块返回的人脸图像对应的全局图像的类型*/
	int  bigSourceImageType;/*图像分析模块获取的原始大图图像类型*/
	int  smallSourceImageType;/*图像分析模块获取的原始小图图像类型*/
	BYTE  	SiaIntSwitch;          	/*0-关闭，1-打开*/
	BYTE	reserve[11];
}RSNet_SoleSiaIntParam_t;

typedef struct
{
	UINT Structsize;
	BYTE  Ieee8021xSwitch;
	BYTE  reserve[31];
	UINT EapolVersion;
	BYTE  EapId[32];
	BYTE  Password[32];
}RSNet_Ieee8021xParam_t;

typedef enum
{
	CA_Certificates = 0,
	Client_Certificates,
	Private_Key,
	HTTPs_Certificate,
	HTTps_Key
}RSNet_Certificates_e;

typedef struct
{
	UINT Structsize;
	int Certype; //RSNet_Certificates_e
	BYTE Cerbuf[5*1024];
	UINT CerLen;
	BYTE reserve [12];
}RSNet_CertificatesParam_t;

typedef enum _https_file_
{
	HTTPS_CA_PEM,
	HTTPS_KEY_PEM,
	HTTPS_MAX
}Https_File_E;

typedef struct
{
	UINT  StructSize;
	BYTE  HttpsEnable;
	BYTE  FileType;
	BYTE  FileExist;
	BYTE  reserve[9];
	UINT  FileSize[10];
	BYTE  Filebuff[10 * 1024];
}RSNet_HttpsFileParam_t;

typedef struct
{
	UINT Structsize;
	BYTE reserve[12];
	BYTE EndPoint[64];  // iot endPoint
	BYTE CertPem[1024 * 4]; // access key id
	BYTE PrivateKey[1024 * 4]; // secret access key
	BYTE ThingName[32];       // thing name
}RSNet_iot_cert_t;

typedef struct
{
	UINT Structsize;
	UINT HttpsType;  /*0: 安联的HTTPS 1: 其他客户的HTTPS*/
	BYTE  HttpsSwitch;
	BYTE  reserve[3];
	UINT HttpsPort;
}RSNet_HttpsParam_t;

typedef struct
{
	BYTE Authentication; /*0: MD5鉴权方式  1：SHA鉴权方式*/
	CHAR EncryptedType;   /* 加密算法扩展用*/
	BYTE reserve[6];
	CHAR Username[16];
	CHAR AuthenticationPassword[16];
	CHAR EncryptedPassword[16];
}EncryptionParam_t;

typedef struct
{
	UINT  StructSize;
	UINT  SnmpPort;/*snmp port ;The default value is 161*/
	UINT  Trapport;
	BYTE  SnmpEnable; /*0:disable  1:enable*/
	BYTE  reserve[68];
	BYTE  SnmpVersions;/*0:off  1:snmp v1   2:snmp v2    3:snmp v1 v2    4:snmp v3*/
	unsigned char  Mac[6];
	CHAR  readcommunity[16];		/*设置IPC读共同体名	  服务器使用该共同名名，只可读IPC上的snmp信息*/
	CHAR  writecommunity[16];	 /*设置IPC读写共同体名	服务器使用该共同体名，可以读写IPC上的snmp信息*/
	CHAR  TrapIPAddr[32]; 	  /*管理服务器地址*/
	CHAR  IpcIp[32];
	EncryptionParam_t Authentication[2]; /*0 设置读用户的密码； 1：设置读写用户的密码*/
}RSNet_Snmp_t;

typedef struct
{
	UINT StructSize;
	UINT ChannelMask;
	UINT delaycount; //目标生成速度,/默认值为10/建议值：0~10
	UINT misscount;	//目标丢失速度 /默认值为5/建议值：3~5
	UINT rminsize_w; //筛除最小待检区域宽度；固定像素点尺寸，配合传入图像尺寸使用（最小40）/默认值为40/建议值：40~50
	UINT rminsize_h; //筛除最小待检区域高度；固定像素点尺寸，配合传入图像尺寸使用（最小40）/默认值为40/建议值：40~50
	UINT rmaxsize_w; //最大宽度/默认值为400/大于该宽高比的人脸将被过滤/建议值：400~500（1080P）
	UINT rmaxsize_h;	//最大高度/默认值为400/大于该宽高比的人脸将被过滤/建议值：400~500（1080P）
	UINT pminsize;   //人脸区域预检测，最小人脸检测尺度，固定像素点尺寸，配合传入图像尺寸使用（值应为rminsize与rmaxsize之间）/默认值为30（360P）/建议值：80~90（1080P）
	UINT pmaxsize;	//人脸区域预检测，最大人脸检测尺度，固定像素点尺寸，配合传入图像尺寸使用（值应为rminsize与rmaxsize之间）/默认值为80（360P）/建议值：200~300（1080P）
	UINT cropused;	//设置局部区域检测的开关，可设置区域为1个/初始值为0，值为1时生效
	UINT tframeNum;       //每次检测/更新完坐标后，连续追踪的帧数/默认值为3/建议值：3~5
	RSNet_Rect_t croproi;	//设置局部检测区域的坐标，相对传入尺寸/只有cropused生效时，此参数才生效/初始值为{0,0,0,0}
	BYTE HGIntSwitch;
	BYTE Reservel[7];

	UINT SnapShotMode;//0)最优抓拍模式 1)间隔抓拍模式
	UINT SnapShotFrame[2];//0)最优抓拍模式，设定的帧数内进行 1)间隔抓拍模式，设定的间隔帧数
	UINT SavePic;//是否抓拍时候，保存整张图片
	BYTE Reserved[128];
}RSNet_SoleHGIntParam_t;

typedef struct{
	UINT  StructSize;  // 该结构体大小
	UINT  ChannelMask;  // 通道掩码
	BYTE  BrightTime; // 白光时长， 自定义白光时长，单位 sec ，范围  1-120，默认5 sec
	BYTE  FloodLightMode; // 白光模式， 0：常亮，1：闪烁
	BYTE  FloodLightValue; // 同RSNet_SolePreviewCtrl_t中FloodLightValue，默认100
	BYTE  FloodLightSwitch; // 启用开关， 0 关闭  1 启用
	BYTE  StrobeFrequency;// 闪烁模式下启用，0 -- low 、1 -- middle 、 2 -- high
	BYTE  MbRow;
	BYTE  MbCol;
	BYTE Sensitivity;       /*8个等级:8-高，7-较高..........  1-低*/
	BYTE  TimeSchedule[8][48]; // 白光计划表， 白光列表  。   7*48个 元素的第一个位对应着开关。 0： 关  1：开
	union {
		struct {
			BYTE RegionSetting3531[200];
		}BlockRegion;
		struct
		{
			BYTE MotionNum[4];
			RSNet_Rect_t Rect[4];
			BYTE Sensitivities[4];
			UINT  RectMaxNum;
		}RectRegion;
	};
	BYTE AlarmOutTime;      /*报警输出，输出时间:10s,20s,40s,60s,30s,1min,2min*/
	BYTE RecordDelayTime;   /*录像延时，延时时间:10s,30s,1min,2min,5mins*/
	BYTE EmailLink;			/*邮件联动 开关*/
	BYTE RecordSwitch;		/*Record  switch*/
	BYTE AlarmOut;			/*只有一个报警输出的，用AlarmOutManager[0]即可*/
	BYTE SensitivityExNight;
	BYTE loudAlarmLink;	
	BYTE SirenSwitch;
	BYTE SirenValue;
	BYTE SirenTime;
	BYTE DualTalkVolume;
	BYTE ColorImageCtrl;//  白光亮起时，强制彩色功能，  1 -> on            0 -> off
	BYTE  reserved[12];
}RSNet_SoleFloodLightSet_t;

#define MAX_IO_INPUT_NUM  16

typedef struct _ioalarmmanage_
{
	UINT Structsize;
	UINT DispatchedFlag;   /*布防标志,1为布防，0为撤防*/
	UINT DispatchedDelayTime;  /*布防延时时间*/
	BYTE reserve[4];
	BYTE ChangeDispatched[MAX_IO_INPUT_NUM]; /*可变动布防的IO通道标志，1表示可变动布防，0表示24小时布防*/
	BYTE SensorName[MAX_IO_INPUT_NUM][64];  /*传感器别名*/
}RSNet_IoAlarmManage_t;

typedef struct {
	UINT StructSize;
	UINT ChannelMask;
	ULONGLONG DevTypeULL;
	UINT httpPort;
	UINT mediaPort;
	UINT Protocol; /*协议*/
	BYTE Version;
	BYTE netMode;
	BYTE res[30];
	BYTE DevType[64];/*设备类型*/
	BYTE Manufacturer[64];/*厂商*/
	BYTE DevVersion[64];/*设备版本*/
	BYTE oldIPAddr[64];
	BYTE ipaddr[64];
	BYTE submask[64];
	BYTE gateway[64];
	BYTE macaddr[64];
	BYTE dns1[64];
	BYTE dns2[64];
	BYTE UserName[32];
	BYTE Password[32];
}RSNet_SoleIPCNetInfo_t;


typedef struct
{
	UINT	   StructSize;
	UINT       ChannelMask; 	//通道掩码

	BYTE       AudioAlarmSwitch;      /*0-关闭，1-打开*/
	BYTE       RiseSwitch;      /*声强陡升使能：0-关闭，1-打开*/
	BYTE 	   SoundIntensity;		 /*声音强度阈值，1-100*/
	BYTE       RiseSensitivity;       /*声强陡升灵敏度，1-100*/
	BYTE       DeclineSensitivity;       /*声强陡降灵敏度，1-100*/
	BYTE       DeclineSwitch;  /*声强陡降使能：0-关闭，1-打开*/

	BYTE       AlarmOut;   /*报警输出时间*/
	BYTE       AlarmOutTime;      /*报警输出，输出时间:10s,20s,40s,60s,30s,1min,2min*/
	BYTE       RecordSwitch;      /*Record  switch*/
	BYTE       RecordDelayTime;   /*录像延时，延时时间:10s,30s,1min,2min,5mins*/

	BYTE       EmailLink;         /*邮件联动 开关*/
	BYTE	   FtpUploadSwitch;   /*上传FTP开关*/
	BYTE       AudioInputEnable;/*音频输入异常报警开关 0:关闭，1:开启*/
    BYTE       BuzzerMooTime;
	BYTE       reserve1[2];
	BYTE	   TimeSchedule[8][48];	// 音频布防时间计划表
	UINT       RecordChannel[8];
	BYTE       ShowMessage;      /*Show Message 开关*/
	BYTE       FullScreen;       /*全屏 开关*/
	BYTE       AlarmOutManager[MAX_ALARMOUT_NUM];
	BYTE       res;
	BYTE       FtpVideoLink;	/*FTP录像联动 开关*/
	BYTE       CloudPicUpload; /* 云存储视频上传 */
	BYTE       CloudVideoUpload;
	BYTE       reserve2[202];
}RSNet_SoleSoundDetectionParam_t;

typedef struct  {
	BYTE StartIPAddress[16]; 	/*起始IP地址*/
	BYTE EndIPAddress[16];   	/*结束IP地址*/
	BYTE IPType;                 /*ip类型 0:ipv4 1:ipv6*/
	BYTE reserve[7];
}RSNet_NetworkIPAddress_t;

typedef struct  {
	UINT StructSize;
	BYTE EnableIPFilter;	/*是否使用IP黑白名单限制：0-no，1-yes*/
	BYTE ChooseIPFilter;	/*启用限制方式：0-启用白名单，1-启用黑名单*/
	BYTE RestrictedType;      	/*黑白名单的类型:0-白名单，1-黑名单*/
	BYTE reserve[1];
	UINT BlacklistCount;      	/*黑名单条数*/
	UINT WhitelistCount;      	/*白名单条数*/
	RSNet_NetworkIPAddress_t Blacklist[64];  /*黑名单列表, 最多能有64条*/
	RSNet_NetworkIPAddress_t Whitelist[64];  /*白名单列表, 最多能有64条*/
}RSNet_NetworkIPFilter_t;

typedef struct {
    UINT StructSize; 	//该结构体大小
    UINT ChannelMask; 	//通道掩码

    BYTE  FtpScHalfHour[8][48];  // 7 days and 48 halfhours
    /* bit 0 为普通ftp上传，bit 1 为动检录像，bit 2 为报警ftp上传，
     * bit 3 为红外侦测PIR ftp上传，bit 4 为In-Analysis
     * 对应的bit位为1表示设置，为0表示清零 */
    //*2018.05.25
}RSNet_SoleFtpScheduleset_t;


typedef struct {
	UINT StructSize; 	//该结构体大小
	UINT ChannelMask; 
	UINT EventScHalfHour[8][48];     // 7days and 48 halfhours
	/*
	  针对定时巡航计划，1个字节共8位，
	  按bit取位 bit 0 预置点巡航，  bit 1为线性扫描，	bit2轨迹巡航，bit3花样扫描，bit 4为恢复，后几位保留
	  **********2019.03.27更新巡航计划位，与板端统一************
	  对应的bit位为1表示有计划，为0表示无计划
	  EventScHalfHour[8]，周日，周一~周六: 0~6，第7位为保留位 
	*/	
	UINT Recovertime;		//5s-720s  任务恢复时间
	BYTE  CruiseSwhich;      //0表示不启用定时巡航任务，1表示启用定时巡航任务
	BYTE   reserve[11];
}RSNet_SolePTZScheduleSet_t;

typedef struct
{
	UINT  StructSize;
	BYTE  VpnSwitch;
	BYTE  VpnTlsKeySwitch;	//tls-auth钥匙开关，0表示关，1表示开
	BYTE  VpnNetDev;	//虚拟网络设备，0表示TUN,1表示TAP
	BYTE  VpnProtocol; //传输层协议，0表示TCP，1表示UDP
	UINT  VpnPort; 	//VPN服务器端口
	BYTE  reserve[4];
	BYTE  VpnServerIP[32];		//VPN服务器IP
	BYTE  VpnUserName[32]; 	//VPN客户端用户
	BYTE  VpnPassword[32]; //VPN客户端密码
	BYTE  VpnCipher[16];	//加密算法，默认BF-CBC
	BYTE  VpnAddOptions[256];	//追加的客户端配置选项
	BYTE  VpnCompLzo;	//是否开启LZO压缩
	BYTE  reserve1[7];     //8字节对齐
}RSNet_OpenVpnParam_t;

typedef struct
{
    UINT StructSize; //
    BYTE reserved[6];
    BYTE intellect;
    BYTE hddPush;
    UINT hddPushSub; //
    UINT resv[15];
    int motionAlarm[8];
    int pirAlarm[8];
    int videoLoss[8];
    int ioAlarm[8];
    int lowPower[8];
    int smartAlarm[8];
    int reser[11][8];
}RSNet_VVPush_Subscrip;

typedef struct
{
	UINT StructSize;
	UINT reserver;

	BYTE token[256];
	BYTE reserver1[512];
}RSNet_DropBoxParam_t;

#endif

