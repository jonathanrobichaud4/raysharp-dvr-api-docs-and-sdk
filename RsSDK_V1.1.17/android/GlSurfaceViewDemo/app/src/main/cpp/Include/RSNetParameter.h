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
   
	������Ϣ

* ******************** */

//TvSystem
#define RS_PAL 0
#define RS_NTSC 1
typedef struct {
	UINT StructSize; //�ýṹ���С

	//ϵͳ����
	BYTE DeviceName[MaxNameLen];
	UINT DeviceID;

	BYTE TvSystem; /*����ͷ��ʽ: <RS_PAL, RS_NTSC>*/

	//ϵͳ��Ϣ
	BYTE DeviceType[MaxNameLen]; //�豸����
	BYTE MacAddr[MaxNameLen];    
	BYTE SoftwareVer[MaxNameLen]; //ϵͳ����汾
	BYTE HardwareVer[MaxNameLen]; //Ӳ���汾
	BYTE IEVer[MaxNameLen]; 	  //IE�汾�ͺ�		/*Yiguang 11.06.15*/
	BYTE IpAddr[MaxIpLen];

	UINT MobilePort;//�ֻ��˿�
	UINT Port;
	UINT WebPort;

	BYTE DdnsHostStatus[MaxNameLen];	
	BYTE HddStatus[MaxNameLen];

	BYTE P2pKeyID[12];
	BYTE P2pUID[40];  // kguard�û�����
	BYTE Language;    // ��ӦLANGUAGE_Eֵ
	BYTE Audio;				/*0: close; 1: open*/
	BYTE MicInVolume;	/* ����������С(0 - 100) */
	BYTE LineOutVolume; /* ���������С(0 - 100) */
	BYTE AdecEncoding;	/* ��������� 0, PT_G711U;1,PT_G711A */
	BYTE AgentVer[16];  //agent �汾(���lorex)
	BYTE DongleVer[32]; //usb����ģ��(dongle)�汾(lorex)
	BYTE SerialNumber[16]; /*���ZIP�ͻ���ÿһ̨��������Ψһ�����к�*/
	BYTE P2pIDFlag;       /*whether if the p2p id valid, 0:valid, 1: invalid , 2016.10.21 add*/  
	BYTE DdnsEnabled;    /*Ddns�Ŀ���0:close 1:open (���zip)2017.11.28 add*/
	BYTE DhcpEnabled;    /*DHCP�Ŀ���0:close 1:open (���zip)2017.11.28 add*/
	BYTE UpnpEnabled;
	BYTE WifiIPAddr[MaxIpLen];
	BYTE EnableWifi;
	BYTE UseIPV6;	   /*�Ƿ�ʹ��IPV6��0-��ʹ�ã�1-ʹ��*/
	BYTE P2PSwitchFlag;   /*p2p���� 0:�رգ�1:��   2018.03.13 add */
	BYTE DrivesNumber;    /* hdd���� 2018.06.28 add */
	BYTE DomainName[36]; 
	BYTE AgentType[8];
	BYTE SerialNumberEX[32];//lorex use 32 bytes sid,2016.11.10 add
	BYTE WifiVer[MaxNameLen];
	BYTE NetMask[MaxIpLen];  /*��������(���zip),2017.11.28 add*/
	BYTE GateWay[MaxIpLen];  /*����(���zip),2017.11.28 add*/
	BYTE IPv6Addr[40];
	UINT ClientExtPort;  /*�ͻ��������˿ں�*/
	UINT WebExtPort;     /*Web�����˿ں�*/
	UINT MobileExtPort;  /*�ֻ������˿�*/
	BYTE resv[4];
	BYTE UseUPNP[16];     /*UPNP 0:�رգ�1:��   web��client��mobile��rtsp*/	
	UINT HttpsIntPort;       /* https�ڲ��˿� */
	UINT HttpsExtPort;       /* https�ⲿ�˿� */	
}RSNet_SystemBaseInfo_t;

//ipc systemInfoEx
typedef struct
{
	UINT StructSize; //�ýṹ���С
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
     UINT StructSize; //�ýṹ���С
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
   
		Ӳ��

* ******************** */

//HddState
#define RS_HDDS_NONE 		0
#define RS_HDDS_UNFORMAT 	1
#define RS_HDDS_OK 	    	2
#define RS_HDDS_BAD 		3
#define RS_HDDS_RONLR 		4
#define RS_HDDS_BACKUP  	5   //������
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
	UINT StructSize; //�ýṹ���С
	UINT HddMask; 		 //Ӳ������

	/*Ӳ��״̬*/
	unsigned long long HddState;  
	unsigned long long HddTotalSize;/*��λ:�ֽ�*/
	unsigned long long HddFreeSize;
	unsigned long long HddFreeRecord; //ʣ���¼ʱ��
    BYTE HddType;  //Ӳ������.0: SATA; 1 : ESATA(NVR ר�ó���)
    BYTE HddNo;    //Ӳ�����к�,����SATA��ESATA.  (NVR ר�ó���)  
	BYTE HddFreeRecord_Min;//HddFreeRecordΪ0����ȡ�����������ʾ���ٷ���
	BYTE reserved[5];
}RSNet_SoleHddInfo_t;

typedef struct {
	UINT StructSize; //�ýṹ���С

	//Ӳ������
	/*�Զ�����ѡ��*/
    BYTE  OverWrite;       
	BYTE RecordState;
	BYTE SupportOneHdd;
    BYTE ESataRecEnable;  //�Ƿ���ESATA¼��.0: disable; 1: enable(NVR)
	
    UINT Redundancy;      /*32��bit, ÿ��bit��Ӧһ��Ӳ�����ԣ�=0, ���̣�=1, ������*/
	UINT OverWritePeriod; /*�������ڣ���СʱΪ��λ*/
	BYTE RecordChn[16][32];

	BYTE OverWriteList[24][16];//24��option��ÿ��option�ǳ���Ϊ12���ַ���
}RSNet_HddInfo_t;




/* ******************** *
   
		��������

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
	UINT StructSize; //�ýṹ���С

    /*Э������*/
    BYTE Protocol;   
    /*������*/
    BYTE Baudrate;
    /*����λ*/
    BYTE DataBit;
    /*ֹͣλ*/
    BYTE StopBit;
    /*У��*/
    BYTE Check;
	/*PS:�����ݲ�ʹ�ã�͸��ͨ��OR�����ѡ�� 0:����̣�1:͸��ͨ��  */
	BYTE KbSwitch;
	BYTE FlowCtrl;/*����0-None��1-DTR/DSR��2-RTS/CTS��3-XON/XOFF*/
	BYTE Address;
}RSNet_SerialInfo_t;




//�û�����

#define RS_MAX_USER_NUMBER 7
//#define RS_USERRIGHT_MAX_PAGE 128


// ÿ���û�����Ϣ

//UserStatus
#define RS_UserLiveOff 0
#define RS_UserLiveOn  1

/*
//�û�Ȩ�޸�λ��ʾ
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
	UINT StructSize; 	//�ýṹ���С
	UINT UserMask; 	//���� ���������ΪMAX_USER_NUM

	BYTE Password[8];		// �û�����
	BYTE Password2[8];		// �û�����ȷ��
	BYTE UserName[10];		// �û���

	BYTE HaveSwitch;	// ��¼���뿪��	<RS_Open, RS_Close>

	BYTE HaveUser;		// �û��Ƿ�ʹ�� <RS_Open, RS_Close> 

	BYTE UserStatus;		// �û�״̬		//1Ϊ����,0Ϊ������
	BYTE reservel[3];

	UserRightWrap UserRights; //Ȩ��
	BYTE c32Password[32];		// �û�����
	BYTE c32UserName[32];		// �û�����ȷ��
	UINT PreviewChannel_EX[8];     //Ԥ��ͨ��
	UINT PlayBackChannel_EX[8];       //�ط�ͨ��
	UINT BackupChannel_EX[8];        //����ͨ��
	UINT PtzControlChannel_EX[8];     //��̨����ͨ��
}RSNet_SoleUserInfo_t;

typedef struct {
	UINT StructSize; 	//�ýṹ���С
	
	UINT MaxUerNum; 	//�ܹ��û���
	UINT DeviceID;
	S8   DeviceName[36];
}RSNet_UserSet_t;




//DST����
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
	UINT StructSize; //�ýṹ���С

    DateTime time; //ϵͳʱ��
    /*ʱ���ʽ*/
    BYTE TimeMode;
    /*���ڸ�ʽ��0ΪMM/DD/YY��1ΪYY-MM-DD��2ΪDD/MM/YY*/
    BYTE DateMode;
    /*����ʱ��<RS_Close, RS_Open>*/
    BYTE Dst;
	/* Dstƫ������ʱ��ֵ��0-1hour��1-2hour */
    BYTE Offset;
    /*����ʱģʽ��0-Week��1-Date*/
    BYTE DstMode;
	/*��ʼ�£���12����:0---11*/
    BYTE StartMonth;    
    /*��ʼ�ܣ�0-��һ�ܣ�1-�ڶ��ܣ�2-�����ܣ�3-������,4-������*/
    BYTE StartWeek;
	/*��ʼ�����ڼ���0-Sun,1-Mon, ...6-Sat*/
	BYTE StartWeekDay;
	/*�����£���12����:0---11*/
    BYTE EndMonth;
    /*�����ܣ�0-��һ�ܣ�1-�ڶ��ܣ�2-�����ܣ�3-������*/
    BYTE EndWeek;
	/*���������ڼ���0-Sun,1-Mon, ...6-Sat*/
	BYTE EndWeekDay;

	BYTE StartSecond;
	BYTE EndSecond;
	BYTE reservel[3];

	/*Dst ��ʼʱ�䣬����*/
    BYTE StartDate[4];
	/*Dst ��ʼʱ�䣬ʱ����*/
    BYTE StartHour[4];
	/*Dst ����ʱ�䣬���� */
    BYTE EndDate[4];
	/*Dst ����ʱ�䣬ʱ�� ��*/
    BYTE EndHour[4];
}RSNet_DSTSet_t;       // �˽ṹ����Ƕ�׳������ṹ���Ա������Э����������

//Ntp����

/*NtpIPAddr  NTP��������ַ*/
#define RS_Ntp_windows   0
#define RS_Ntp_nist 	 1
#define RS_Ntp_ntp 		 2
#define RS_Ntp_lorexddns 3
/*��Ӧ������ʾ
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


//IPCͨ��״̬����
typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask;//ͨ������

	/*IP��ַ*/   
	BYTE IPAddr[4];
	/*ý��˿�*/
	UINT Port;
	/*��½�û���*/
	BYTE UserName[36];
	/*��½�û�����*/
	BYTE UserPW[36];    
	/*��Ӧǰ���豸���Ǹ�ͨ��,���ǰ����dvr�����ж��ͨ��*/
	BYTE ChnNo;
	/*����0:raysharp,1:hikvison,2:sony*/
	BYTE Protocol;	
	/*�Ƿ����ã�ֻ�����*/
	BYTE Enable;
	/*��ǰip��Ӧ��ǰ���豸����ͨ����*/
	BYTE ChnMax;
	/*��ǰipͨ���ϵ�״̬, ֻ�����*/
	BYTE IPChnStatus;
	BYTE Version;
	BYTE switchmode; /*0 �Զ�ģʽ 1 �ֶ�ģʽ*/
	BYTE reservel;

	unsigned long long u64devType;  //�豸����
	BYTE macAddr[36];    //mac ��ַ
	BYTE IpcName[36];    //�豸���ƣ�ֻ�����

    S8 DevType[36];	     /*�豸����*/
    S8 Manufacturer[36]; /*����*/
    S8 SoftVersion[36];  /*�̼��汾*/
    BYTE mask[4];		 /*��������*/
    S8 DevAlias[36];     /* IP Camera�ı��� */
	BYTE AliasPos;       /* IPC�����ڷŵ�λ��, 0-���ϣ�1-���ϣ�2-���£�3-���£�4-����ʾ */
    BYTE reserve2[3];
	BYTE sIPAddr[64];
    BYTE GateWay[4]; 	 /*����*/
	BYTE dns1[4];
	BYTE dns2[4];
	UINT IEport;
    BYTE switchflag;     /*˽��ipc  1 ���������� 0 ��ʾû��*/
	BYTE portnum;        /*�������� ��[0  -MAX_POE_NUM) */	
    BYTE P2pUID[32];     /* IPC P2P2 ID */
	BYTE poeflag;        /*POEͨ��ģʽ: bit0 0--�ֶ� 1--�Զ� */
	BYTE CameraType;
	BYTE poePhyMode;		/*POE band mode 0��AUTO  1:10M*/
	BYTE reserved[3];
	BYTE MulChannel[8];     /*��ͨ��   ʹ�� */
}RSNet_SoleIPCSet_t;

typedef struct {
	UINT StructSize; //�ýṹ���С

//	/*�������˿�*/
//	UINT  NtpPort;
//	/*��������-��λ:���ӣ����ֵ65535*/
//	UINT SyncPeriod;
	/*�����������ַ*/
	BYTE NtpIPAddr[4];
	/*NTP ���ñ�ʶ��<RS_Close, RS_Open>*/
	BYTE UseNtp;
    /* ʱ������*/
    BYTE TimeZone;
	BYTE NtpSerFlag;
	BYTE reserver;
	UINT NtpPort;
	UINT SyncPeriod;

}RSNet_NtpSet_t;  // �˽ṹ����Ƕ�׳������ṹ���Ա������Э����������

// ͨ����Ϣ����
typedef struct {
	UINT StructSize; //�ýṹ���С
	RSNet_DSTSet_t DstSet;
	RSNet_NtpSet_t NtpSet;
	UINT           LanguageMask;
	BYTE           Language;    // ��ӦLANGUAGE_Eֵ
	BYTE           VideoFormat;
	BYTE           AutoLogout;
	BYTE           AllFlickerCtrl;
	BYTE		   DateMode;    /*���ڸ�ʽ��0ΪMM/DD/YY��1ΪYY-MM-DD��2ΪDD/MM/YY*/
	BYTE           TimeMode;    /*ʱ���ʽ��0Ϊ24Сʱ�ƣ�1Ϊ12Сʱ��*/
	BYTE           LastLanguage;
	BYTE           ShowWizard;
    BYTE           hybirdEnable;//�Ƿ����û��DVR
	BYTE           vgaresolution; //RCIר��
	BYTE		   bIEChangeTime;// indicates whether the client modifing the dev time
	BYTE           reserved[1]; //
	UINT           ExtendLanguageMask;  /*New 32-bit to extend Language for client*/  
    BYTE           NtpServAddr[64]; //
    WORD           TimeZone_EX;
	BYTE           WaterMark; /*0 : �ر� 1�� */
	BYTE           reserved2[1];
	UINT		   ClientAutoLogoutTime;
}RSNet_GeneralInfoSet_t;

typedef struct{
	BYTE Hour;
	BYTE Minute;
	BYTE Second;
	BYTE rev;
}RSNetTimeSet_t;

//��ʾ����
typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; //ͨ������
	BYTE Chroma; 		//ɫ��, <0-63>��<0 - 255>
	BYTE Brightness; 	//����, <0-63>��<0 - 255>
	BYTE contrast; 	//�Աȶ�, <0-63>��<0 - 255>
	BYTE saturation; 	//���Ͷ�, <0-63>��<0 - 255>
	BYTE DefaultColor; 	//�ָ���ɫĬ��ֵ
	BYTE Sharpness; 	 /* ���<0 - 255> */
	BYTE ColorMode:2;   /*0:0-63�� 1:0-255*/
	BYTE DisplayRule:4; //���ݲ�ͬIPCЭ��������ʾ��ͬ������
	BYTE ShowDefault:1; //Զ�˸���IPC�����Ƿ���ʾĬ�ϰ�ť
	BYTE reserved:1;
	BYTE LoadBalancing:2; /* 0:ʵʱ(����) 1: ���� (��ʱ)*/
	BYTE reserved2:6;
	BYTE Gamma;		 /* <0 - 255> */
	BYTE Chroma2; 		//ĿǰLUX�ͻ�ʹ��,ɫ��2, <0-63>��<0 - 255>
	BYTE Brightness2; 	//ĿǰLUX�ͻ�ʹ��,����2, <0-63>��<0 - 255>
	BYTE contrast2; 	//ĿǰLUX�ͻ�ʹ��,�Աȶ�2, <0-63>��<0 - 255>
	BYTE saturation2; 	//ĿǰLUX�ͻ�ʹ��,���Ͷ�2, <0-63>��<0 - 255>
	BYTE Sharpness2; 	 /* ĿǰLUX�ͻ�ʹ��,���2<0 - 255> */
	BYTE reserved3[66];
	RSNetTimeSet_t SunRiseTime;	//ĿǰLUX�ͻ�ʹ��,��ʾ����Ŀ�ʼʱ��
	RSNetTimeSet_t SunSetTime;	//ĿǰLUX�ͻ�ʹ��,��ʾ���ϵĿ�ʼʱ��
}RSNet_SoleColorSet_t;

//��Ƶ�ڵ�����
#define MAX_VIDEOCOVER_NUM  32
//�˽ṹ�岻���Ǻ����޸�,ֱ�Ӵ���
typedef struct {/*����*/
	UINT StructSize; //�ýṹ���С

	int CoverSwitch; //���ڵ����Ƿ�����, <RS_Open, RS_Close>
    int x, y, w, h;
}RSNet_VideoCoverArea_t;


typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 		 //ͨ������

	BYTE VideoCoverSwitch:2;/* ͨ���Ƿ�������Ƶ�ڵ�, <RS_Open, RS_Close>*/
	BYTE ShelterMode:2;//����1ʱ�����û�����ģʽ������0�������ο�
	BYTE reserved:4;
	BYTE VideoCoverNum;/* ֧��������Ƶ�ڵ���Ŀ,0:4�飬������Ŀ����ʵ��֧�ֵĿ���*/
	BYTE reservel;
	BYTE mosaicLevel;/*������ǿ�ȵȼ�*/	//������4λ��ʾѡ���� ; ��4λ(bit_4==0��64��bit_4==1��64 )
	union{
		struct
		{
			RSNet_VideoCoverArea_t VideoCoverArea[8]; //ֱ�Ӵ���, ���������б�
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


//PTZ����

/* ����������Serialһ��
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
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 		 //ͨ������

    /*Э������*/
    BYTE Protocol;
    /*������*/
    BYTE Baudrate;
    /*����λ*/
    BYTE DataBit;
    /*ֹͣλ*/
    BYTE StopBit;
    /*У��*/
    BYTE Check;
	/* PTZ �Զ�Ѳ������ RS_Close, RS_Open*/
	BYTE EnablePtzCruise;
	BYTE KeyboardFlag;//1����keyboard   0:PTZ
    BYTE reserved2:5;
	BYTE FocusMode:1;//1:���Զ���0��ȫ�Զ�
    BYTE SignalType:2; //0: ģ���ź�; 1: �����ź�.
    /*���,��UI�ϵ�ADDRESS����ΧΪ1-255*/
    UINT Number;
    ///*ͨ����ѯʱ��, ��ΧΪ1--255, ע�⵱ʱ��Ϊ0 ʱ��ʾ��Ԥ�õ�δ������! */
	BYTE ChnCruiseTime[RS_MAX_CRUISE_POINT];	
	NetPtzTour_t Tour[8];/*ÿ��ͨ��֧��8��Ѳ���ߣ�ÿ��Ѳ�������֧��32��Ԥ�õ�*/
}RSNet_SolePTZSet_t;

typedef struct {
	UINT StructSize; //�ýṹ���С

    /* PTZ �Զ�Ѳ������ RS_Close, RS_Open*/
    UINT  EnablePtzCruise;     /*This para is reserved for another page later!*/
}RSNet_PTZSet_t;



//OSD����
//Position
#define RS_PositionLeftUp 	 0
#define RS_PositionLeftDown  1
#define RS_PositionRightUp 	 2
#define RS_PositionRightDown 3

/* Ԥ��ҳ���������,�˽ṹ�����DVRʹ��*/

typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 		 //ͨ������

    /*ͨ������λ�� 0-���ϣ�1-���£�2-���ϣ�3-����*/
    BYTE Position;

    /*Ԥ��osd���� RS_Open, RS_Close*/
    BYTE Preview;

    /*�ֳ�ʱ��OSD RS_Open, RS_Close*/
    BYTE PreviewTimeSet;

    /*¼��ʱ��OSD RS_Open, RS_Close*/
    BYTE RecordTimeSet;

    /*ͨ������*/
    BYTE ChnName[20];

	BYTE FlickerCtrl;   //nvr��ipc����˸���� 0 :50HZ 1:60HZ
    BYTE resolution;    //�豸�ֱ���(RCI�ͻ�20150623)
    BYTE reserve[6];
    BYTE honeyChnName[64]; //honeywellͨ����,֧��8������(utf-8����)
}RSNet_SoleOsdSet_t;

typedef struct {
	UINT StructSize; //�ýṹ���С

    /*�ֳ�ʱ��OSD RS_Open, RS_Close*/
    BYTE PreviewTimeSet;
    /*¼��ʱ��OSD RS_Open, RS_Close*/
    BYTE RecordTimeSet;
	BYTE FlickerCtrl;   //nvr��ipc����˸���� 0 :50HZ 1:60HZ
    BYTE reservel;
}RSNet_OsdSet_t;

typedef struct 
{
	UINT StructSize;
	UINT ChannelMask; 		 //ͨ������

	UINT IntCrossSwitch;        /*���ܻ��߿��أ�BIT_1λΪ�������ܻ��߿��أ���Ϊ1����������Ϊ0��ر�*/
	BYTE PreviewAudioEnable;	/*Ԥ��������Ƶ���أ�0: �ر�,1:����*/
	BYTE FloodLightMode; /*�׹�� 0:disable 1:enable*/
	BYTE FloodLightValue;/*ֵ��Χ[1, 100]*/
	BYTE AudioAlarmSwitch;/*���ȱ���0:disable 1:enable*/
	BYTE FlashLight;   /*�����*/
	BYTE LineOutVolume;
	BYTE StrobeFrequency; /*���ص�Ƶ�� 0:�� 1:�� 2:��*/
	BYTE SirenSwitch;
	BYTE SirenValue;
	BYTE SirenTime;
	BYTE OperBtn;//����İ�ť���ĸ��� 1��sounds��2��light
	BYTE reserve[41];    		/*�����ֽ�*/
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

//ALARM OUT����
typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	BYTE  AlarmOutScHalfHour[8][48];  // ��¼��ƻ���ʾһ��
}RSNetNew_SoleAlarmOutScheduleset_t;

//�����������
//NetworkMode
#define RS_DHCP   0
#define RS_PPPOE  1
#define RS_Static 2

//PPPoEState
#define PPPOE_CONNECTING   0
#define PPPOE_SUCCESS      1
#define PPPOE_FAIL         2
/* �������ҳ������ṹ */
typedef struct {
	UINT StructSize; //�ýṹ���С

    /*IP��ַ*/
    BYTE IPAddr[4];
    /*��������*/
    BYTE NetMask[4];
    /*����*/
    BYTE GateWay[4];
    /*�ͻ��˶˿ں�*/
    UINT Port;
    /*Web�˿ں�*/
    UINT WebPort;
    /*������ʽ��<RS_DHCP, RS_PPPOE, RS_Static>*/
    BYTE NetworkMode;
    /* UPNP     RS_Open, RS_Close*/
    BYTE UseUPNP;
	/*�ֻ��˿�*/
	WORD MobilePort;
    /*DNS1*/
    BYTE dns1[4];
    /*DNS2*/
    BYTE dns2[4];
    //ppoe����
    /*PPPOE�û���*/
    BYTE PPPOEuser[MaxNameLen];
    /*PPPOE�û�����*/
	BYTE Password[MaxNameLen];

    //3G��Ϣ
	BYTE APN[MaxNameLen];
	BYTE DialCode[MaxNameLen];
	BYTE WirelessUser[MaxNameLen];
	BYTE WirelessPwd[MaxNameLen];
	
	BYTE EncodeFlag; //Enable:1 Disable:0
	/*WAN �ڹ�����: 0 WAN  ;1  LAN*/
	BYTE WANWkIn;
	
	/*PPPOE state  0:connecting.. 1:success 2:fail */
	BYTE PPPoEState;
	/*PPPoE IP */
	BYTE PPPoEIPaddr[4];
	BYTE BandWidth;
	BYTE  RtspAuthType;/*rtsp authority type(0:none 1:basic 2:digest)*/
	BYTE  UseVideoPwd; /* ��Ƶ���ܿ��� */
    WORD IpKBPort;     /*ip���̶˿ں�*/  //honywellר��
    BYTE UPnP_TMEnable;/*ʹ��UPnP_TM����1-����,0-�رգ���IPCά��*/ 
	BYTE UseIPV6;	   /*�Ƿ�ʹ��IPV6��0-��ʹ�ã�1-ʹ��*/
	BYTE EnablePPPOE;  /*UI5.0 �Ƿ�����pppoe*/
	BYTE Enable3G;     /*UI5.0 �Ƿ�����3G*/
	BYTE EnableDHCP;   /*UI5.0 0:static ip, 1:dhcp*/
	BYTE DownloadSpeed; /*0-40 Mbps*/
    BYTE P2Pswitch;   /*p2p���� 0:�رգ�1:��*/
	BYTE Connect_Procotol;/*UPNP Э��, 0:ONVIF; 1:SVNP*/
	BYTE WifiStation;
	BYTE EnableWifi;
	BYTE WifiIPAdrr[4];
	BYTE reserve[2];
	BYTE User3G[MaxNameLen];
	BYTE Pwd3G[MaxNameLen];
	BYTE switchIPAddr[4];      /*IP��ַ*/
	BYTE switchNetMask[4];     /*��������*/
	BYTE switchGateWay[4];     /*����*/
	WORD	ClientAutoExtPort;	/* UPnP auto ext port */
	WORD	WebAutoExtPort;	/* UPnP auto ext port */
	BYTE TransmissionMode[16]; /*������룬0-��ͨ*/
	BYTE SwitchMode;           /*������ģʽ 0-�Զ� 1-�ֶ�*/
	BYTE TOEFlag;              /*TOE���٣�0xa5ʱ��ʾ�����ã�����Ϊ����*/
	BYTE Reservel[14];		   /*�����ֽڲ��ֽڶ���*/
	BYTE ExternIP[16];            /* �ⲿIP��ַ 2018.3.6 add */
	BYTE ExternPortStatus;        /* �ⲿ�ͻ��˶˿�ӳ��״̬ 1:Active 0:Inactive 2018.3.6 add */
	BYTE ExternWebPortStatus;     /* �ⲿWeb�˿�ӳ��״̬ 1:Active 0:Inactive 2018.3.6 add */
	BYTE ExternMobilePortStatus;  /* �ⲿ�ֻ��˿�ӳ��״̬ 1:Active 0:Inactive 2018.3.6 add */
	BYTE ExternRtspPortStatus;    /* �ⲿRtsp�˿�ӳ��״̬ 1:Active 0:Inactive 2018.3.6 add */
    BYTE ExternHttpsPortStatus;   /* �ⲿHttps�˿�ӳ��״̬ 1:Active 0:Inactive 2018.3.6 add */
	BYTE reserve2;
	BYTE useUPnPStrategy;		/* ����UPNP���Կ��� */
	BYTE UPnPAutoSwitch;		/* ����UPnPӳ�䷽ʽ        1 auto 0 manual */
	UINT ClientExtPort;           /*�ͻ��������˿ں�*/
    UINT WebExtPort;              /*Web�����˿ں�*/
    UINT MobileExtPort;           /*�ֻ������˿�*/
    BYTE UseUPNPsingle[16];
	UINT HttpsIntPort;       /* https�ڲ��˿� */
    UINT HttpsExtPort;       /* https�ⲿ�˿� */

}RSNet_NetworkBaseSet_t;

typedef struct 
{
	UINT StructSize;

	BYTE Identity[32]; 
	BYTE Password[32];
	BYTE EapolVersion;  /*1 or 2 */
	BYTE TrapEnable;        /* (0,disable, 1 enable) */
	BYTE HasCaCrt; // �Ƿ���CA֤�� ����1������0 ��web�ж�ʹ��
	BYTE HasCliCrt; // �Ƿ��пͻ���֤�� ����1������0 ��web�ж�ʹ��
	BYTE HasCliPem; // �Ƿ��пͻ���˽Կ ����1������0 ��web�ж�ʹ��
	BYTE DelFile; // �Ƿ�Ҫɾ��ĳ���ļ� ��ɾ��0 1��CA 2ɾ�ͻ���֤�� 3ɾ�ͻ���˽Կ �������
	BYTE UpFile;  // �Ƿ�Ҫ����ĳ���ļ� ������0 1��CA 2��ͻ���֤�� 3��ͻ���˽Կ �������
	BYTE reserve1; // �����ֶΣ����ڶ��룩
	UINT FileLen; // �ļ���С
	BYTE FileBuff[19<<10]; // �ϴ��ļ����ݻ��壨�����ļ�<=90k�����ṹ���ܴ�СҪС��100k
	BYTE reserve[16];    // 8�ֽڶ��� 
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

//��������������
typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; //ͨ������
	//������
    int sub_bitrate;
	
	BYTE sub_video; 	/* �Ƿ���������,<RS_Close, RS_Open>*/ 

	/*RS_Encode720P��
	  RS_EncodeD1��
	  RS_EncodeHD1,
	  RS_EncodeCIF*/
	BYTE sub_resolution; //DVRΪCIF��IPCΪD1���ݲ��ṩ�޸�

	/*PAL = 1~25, NTSC = 1~30֡,
	  ֻ����һ��ͨ��֡��, ����ͨ��ΪPAL=1~5, NTSC=1~6
	  ѡ���Ӧ������û��0ֵ*/ 
	BYTE sub_fps;  

	BYTE sub_audio;/*������¼��:<RS_Close, RS_Open>*/
	
	BYTE Ipc_state; //ipc����״̬
	BYTE ResolutionType; // 0:720p 1:D1
	BYTE VBR;
	/*IPCʹ��*/
	BYTE BitrateType; /* 0 :������1:������2: ������ 3: QVBR*/
	BYTE VideoQuality; /* ͼ������0: ���1:����2:��3:��4:����5:���*/
	BYTE IFrameInterval; /* I ֡�����Χ��1-100  �� */
	unsigned short CustomSubBitrate; /* �Զ������� */
	/*IPCʹ�� END */
}RSNet_SoleSubStreamSet_t;

//�����ֻ�����
typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; //ͨ������

	//�ֻ�����
    int mobile_bitrate;

	BYTE mobile_video; 	/* �Ƿ���������,<RS_Close, RS_Open>*/ 

	/*RS_Encode720P��
	  RS_EncodeD1��
	  RS_EncodeHD1,
	  RS_EncodeCIF*/
	BYTE mobile_resolution;/*PS:��ʱֻ��ΪCIF, �ݲ��ṩ�޸�*/

	/*PAL = 1~25, NTSC = 1~30֡,
	  ֻ����һ��ͨ��֡��, ����ͨ��ΪPAL=1~5, NTSC=1~6
	  ѡ���Ӧ������û��0ֵ*/ 
	BYTE mobile_fps;  

	BYTE mobile_audio; /* �Ƿ������Ƶ,<RS_Close, RS_Open>*/

	BYTE Ipc_state; //ipc����״̬
	/*IPCʹ��*/
	BYTE BitrateType; /* 0 :������1:������2: ������ 3: QVBR*/
	BYTE VideoQuality; /* ͼ������0: ���1:����2:��3:��4:����5:���*/
	BYTE IFrameInterval; /* I ֡�����Χ��1-100  �� */
	unsigned short CustomSubBitrate; /* �Զ������� */
	/*IPCʹ�� END */
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
    BYTE steamnum; // 0 - ������ 1-˫���� 2-������
    BYTE resindx;  // �ֱ������õ�����
    BYTE reserve1[3];
    BYTE singleResNum;
    BYTE doubleResNum;
    BYTE triResNum;
    TI_IPC_SResolute sr[MAX_RESOLUTION_NUM]; // �������ֱ��ʷ�Χ
    TI_IPC_DResolute dr[MAX_RESOLUTION_NUM]; // ˫�����ֱ��ʷ�Χ
    TI_IPC_TResolute tr[MAX_RESOLUTION_NUM]; // �������ֱ��ʷ�Χ
}TI_IPC_Resolute;

/* HonneyWell�������� */
typedef struct
{
    UINT StructSize;
    UINT ChannelMask;
    BYTE StreamMode;	/*����ģʽ:0Ϊ��������1Ϊ˫����*/
    BYTE RefreshRate;	/*ˢ��Ƶ�ʣ�0:60HZ��1:50HZ*/
    BYTE Resolution;	/*ResRange������ֵ*/
    BYTE MainFps;		/*������֡�ʶ�ӦFrameRange������ֵ*/
    BYTE SubFps;		/*������֡�ʶ�ӦFrameRange������ֵ*/
    BYTE Audio:1;  		/*��Ƶ����: 0-�أ�1-��*/
    BYTE TIFlag:1;      /*��ʶ�Ƿ�ΪTI�豸: 1-��, 0-��*/
    BYTE reserved:6;
    WORD MainBit;		/*������������*/
    WORD SubBit;		/*������������*/
    WORD FrameRange[3];	/*[0]Ϊ��������[1]Ϊ��������[2]Ϊ�ֻ���������λȡ����ӦFrameRate_e*/
    TI_IPC_Resolute ResRange;/*������Χ*/
}RSNetSZ_SoleStreamset_t;

//DDNS����

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
	UINT StructSize; //�ýṹ���С

    /*HOST���֣����16�ֽ�*/
    BYTE HostName[MaxNameLen];
    /*�û��������16�ֽ�*/
    BYTE UserName[MaxNameLen];
    /*�û����룬���8�ֽ�*/
    BYTE UserPW[MaxNameLen];
	/*ÿһ��bit  ��Ӧһ��DDNS ,1:��ǰʹ��,0:��ǰû��ʹ��
	  һ������£�DDNS��ַѡ���ȫ����
	 ���ڿͻ�����汾ʱ�������Լ���DDNS
	 ��λ������ʾ������DDNSѡ��*/
    UINT DDNSUseFlag;
    /*��������ַѡ��*/
    BYTE ServerAddr;
    /*DDNS���ñ�ʶ��<RS_Close, RS_Open>*/
    BYTE UseDDNS;
    BYTE P2pState;      //�豸p2p����״̬(��������)
    BYTE CommaxUseLoginFlag;

	BYTE DDNSID[12];
    BYTE P2pKeyID[MaxNameLen]; //P2P ID(������ĺ�������)
    UINT extendDDNS;    //����DDNS����,֮ǰ�����32������
	BYTE IpType;          /*��Ϊluxvision�ͻ�ר�ã�0ΪIPV4��1ΪIPV6*/
	BYTE reserved[3];
	BYTE UserUrl[128];
}RSNet_DDNSSet_t;


//PPPOE����
typedef struct {
	UINT StructSize; //�ýṹ���С

    /*PPPOE�û���*/
    BYTE PPPOEuser[MaxNameLen];
    /*PPPOE�û�����*/
    BYTE Password[MaxNameLen];
    /*DNS1*/
    BYTE dns1[4];   // ����·���ϵ�PPPOE
    /*DNS2*/
    BYTE dns2[4];
}RSNet_PPPoESet_t;




//Email����
/* Email����ҳ������ṹ*/
//intervaltime
#define RS_IntervalTime_60  0
#define RS_IntervalTime_180 1
#define RS_IntervalTime_300 2
#define RS_IntervalTime_600 3
typedef struct {
	UINT StructSize; //�ýṹ���С

    /*SMTP������*/
    BYTE SMTP[MaxNameLen];
    /*�����˵�ַ*/
    BYTE SendEmail[MaxNameLen];
    /*����������*/
    BYTE SendEmailPW[MaxNameLen];
    /*�ռ��˵�ַ, ��ʱֻ�е�һ���ռ��˵�ַ*/
    BYTE RecvEmail[3][MaxNameLen];
    /*�˿ں�*/
    UINT Port;
    /*�Ƿ�ʹ��email,<RS_Close, RS_Open>*/
    BYTE EmailSwitch;
    /*SSL���أ�<RS_Close, RS_Open>*/
    BYTE SSLSwitch;
    /*�ʼ����ͼ��*/
    BYTE intervaltime;
	BYTE kgCheck;
	BYTE usename[MaxNameLen];
}RSNet_EmailSet_t;

typedef struct {
	UINT StructSize; //�ýṹ���С
	BYTE EnReceivePasswd[3]; /*�Ƿ�֧�ֽ������� 0--��֧��, 1--֧�� 2018.6.28 add */
	BYTE StreamType;//0--mainstream;1--substream

	/*SMTP������*/
	BYTE SMTP[128];
	/*�����˵�ַ*/
	BYTE SendEmail[128];
	/*����������*/
	BYTE SendEmailPW[128];
	/*�ռ��˵�ַ, ��ʱֻ�е�һ���ռ��˵�ַ*/
	BYTE RecvEmail[3][128];
	/*�˿ں�*/
	UINT Port;
	/*�Ƿ�ʹ��email,<RS_Close, RS_Open>*/
	BYTE EmailSwitch;
	/*SSL���أ�<RS_Close, RS_Open>*/
	BYTE SSLSwitch;
	/*�ʼ����ͼ��*/
	BYTE intervaltime;
	BYTE kgCheck;
	BYTE usename[128];
}RSNet_NewEmailSet_t;
typedef struct {
	UINT StructSize; 	//�ýṹ���С
	int MotionScheduleHour[16][8];
	int AlarmScheduleHour[16][8];
	int EventScheduleHour[8];
	BYTE reservel[4];
	int MotionScheduleHourEx[32][8];
	int AlarmScheduleHourEx[32][8];
}RSNet_EmailScheduleSet_t;

typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	
	BYTE  EmailScHalfHour[8][48];  // ��¼��ƻ���ʾһ��
}RSNetNew_SoleEmailScheduleset_t;

typedef struct {
	UINT StructSize; 	//�ýṹ���С

	BYTE  EventScHalfHour[8][48];     // 7days and 48 halfhours
    /* EventScHalfHour[8]�����գ���һ~����: 0~6����7λΪ����λ*/ //2016.03.09
    // 2013.03.09
	UINT  EventScHalfHourExt[8][48];  // 7days and 48 halfhours 
	/* EventScHalfHourExt[8]�����գ���һ~����: 0~6����7λΪ����λ*/
}RSNetNew_EmailScheduleset_t;



//Mobile����
typedef struct {
	UINT StructSize; //�ýṹ���С
	//�ֻ�����
    BYTE MobileUserName[MaxNameLen];/* �û��������16�ֽ�*/    
    BYTE MobileUserPwd[MaxNameLen];/* �û����룬���16�ֽ�*/     
    UINT MobilePort; /* ����˿�*/ 
	BYTE reservel[4];
}RSNet_MobileSet_t;


//Router Lan ������
typedef struct {
	UINT StructSize; //�ýṹ���С
    BYTE IPAddr[4];  /* IP��ַ */
    BYTE NetMask[4]; /* ��������*/
    BYTE SSID[MaxNameLen];  /* ���������ʶ */    
    BYTE Passwd[MaxNameLen];/* ���� */     
	BYTE SecureType;        /* ��ȫѡ�� */
	BYTE WiFiChannel; /*����ͨ��ѡ��*///add by st 20120509
	BYTE WpaAlgorithm;
	BYTE reservel[17];
}RSNet_RouterLanSet_t;

//�ƶ��������

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
//��ӦMotion,Abnormal,IOAlarm
#define RS_AlarmTime_10s 0
#define RS_AlarmTime_20s 1
#define RS_AlarmTime_40s 2
#define RS_AlarmTime_60s 3
#define RS_AlarmTime_30s 4
#define RS_AlarmTime_1min 5
#define RS_AlarmTime_2min 6


//BuzzerMooTime
//��ӦMotion,Abnormal,IOAlarm
#define RS_BuzzerTime_Off 0
#define RS_BuzzerTime_10s 1
#define RS_BuzzerTime_20s 2
#define RS_BuzzerTime_40s 3
#define RS_BuzzerTime_60s 4


//¼����ʱ RecordDelayTime
//��ӦMotion,IOAlarm
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

/* �ƶ����ҳ������ṹ */
typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 	//ͨ������

	/*���8���ȼ�*/
	BYTE Sensitivity;
	/*�Ƿ������ƶ����<RS_Close, RS_Open>*/
	BYTE ChnSwitch;
	/*Send Email ����<RS_Close, RS_Open>*/
	BYTE SendEmail;
	/*����������ʱ��*/
	BYTE BuzzerMooTime;
	/*Record Channel, ����ͨ��¼�񣬰�λ��¼*/
	UINT RecordChannel;
	/*¼����ʱʱ��*/
	BYTE RecordDelayTime;
	/*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE Record;
	/*Show Message <RS_Close, RS_Open>����*/
	BYTE ShowMessage;
	/*FullScreen ���� ����ȫ��<RS_Close, RS_Open>*/
	BYTE FullScreen;
	/*�������ã�180��������32���ֽڱ�ʾ��ÿλ��ʾһ������*/
	BYTE RegionSetting[32];	/* LoginRsp MotionMode�ֶ�:0,ʹ�õ�ǰ�ֶ�*/
	/* �������  ֻ�� LoginRsp MotionMode==2ʱ,���ֵ������Ч��*/
	BYTE MbRow; 
	/* ������� ֻ�� LoginRsp MotionMode==2ʱ,���ֵ������Ч��*/
	BYTE MbCol;
	/*Alarm Out ����<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*�������ʱ��*/
	BYTE AlarmOutTime;
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	/*�������ã�200��������32���ֽڱ�ʾ��ÿλ��ʾһ������*/
    //BYTE RegionSetting3531[200];  /* LoginRsp MotionMode�ֶ�:1��2,ʹ�õ�ǰ�ֶ�*/
    union {
        struct {
            BYTE RegionSetting3531[200];  /* LoginRsp MotionMode�ֶ�:1��2,ʹ�õ�ǰ�ֶ�*/
        }BlockRegion;
        struct
        {
            BYTE MotionNum[4];  /* ��Ӧ�����Ƿ����ã�Ϊ1���ã�Ϊ0������ */
            RSNet_Rect_t Rect[4];
            BYTE Sensitivities[4]; /*11���ȼ�:0-�ߣ�1-�ϸߣ�2-�У�10:���*/
            UINT  RectMaxNum;    /*motion max rect num 2016.10.19 add*/			
        }RectRegion;
    };
	
	BYTE FtpLink;			/*FTP���� ����*/
	BYTE PushSwitch;    /*�Ƿ����ƶ���ⱨ������, 0: close; 1: open.*/
	BYTE WirelessAlarmSensor; /*�ⲿsensor ���� ʹ��0, ��ʹ��, 1. ʹ��*/
	BYTE LlluminationRing; /* ���ջ�0, ��ʹ��, 1. ʹ��   */
	BYTE AudioAlert; /* ��Ƶ����0, ��ʹ��, 1. ʹ�� */
	BYTE AudioSelect; /* ��������ѡ�� 0, Doorbell 1.Ringtone, 2.Siren */
	BYTE AlarmDurationTime;/*0: 10s , 1: 30s, 2: 60s*/
	BYTE CloudNotify; /*Urmetר�ã��������ϴ�ʹ�ܿ���*/
	BYTE Pirflag;
	BYTE SensitivityExNight;
	BYTE onlySDexit;
	BYTE sendToFTP;/*���ͽ�ͼ��FTP��0����ʹ�ܣ�1��ʹ��*/
	BYTE LightLinkage;/*�׹��motion�������� 0:������ 1:����*/
    BYTE LoudSpeaker;/*���������� 0:�� 1:��*/
	BYTE Distance;	/*PIR ����*/
	BYTE PageBit;//BIT_0:NVR LOREX use,...
	BYTE FtpVideoLink;	/*FTP¼������ ����*/
	BYTE CloudPicUpload; /* �ƴ洢��Ƶ�ϴ� */
	BYTE CloudVideoUpload;
	BYTE FTPUpload; 		   /*FTP Upload ����*/
	BYTE Reservel[20];
	UINT RecordChannel_EX[8];	
	/*ȡbitλ:3��ʾһ��ͨ�����3���������,ÿ���������봥�������������
	32*8= 256·���κ�ͨ���������*/
	BYTE AlarmOutManagerEx[3][32];
}RSNet_SoleMotionSet_t;

/* �ڵ��澯ҳ������ṹ */

typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 	//ͨ������

	/*���8���ȼ�*/
	BYTE Sensitivity;
	/*�Ƿ������ƶ����<0:RS_Close, 1:RS_Open>*/
	BYTE ChnSwitch;
	/*Send Email ����<0:RS_Close, 1:RS_Open>*/
	BYTE SendEmail;
	/*����������ʱ��*/
	BYTE BuzzerMooTime;
	/*Record Channel, ����ͨ��¼�񣬰�λ��¼*/
	UINT RecordChannel;
	/*¼����ʱʱ��*/
	BYTE RecordDelayTime;
	/*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE Record;

	BYTE AlarmOut;	/* 0. ������IO ���, 1. ����IO ���edit by jazhu */
	

	BYTE Reservel[41];
}RSNet_OcclusionSet_t;

//�쳣��������
/*
   �쳣����������,��ͨ����ʽ����
0��videoloss
1:HddInvalidAlarm
2:HddNoSpaceAlarm
*/
typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT EventTypeMask; 	//ͨ������

	//�쳣�����Ƿ��� RS_Close, RS_Open
	BYTE Enable;
	/*����������ʱ��*/
	BYTE BuzzerMooTime;

	/*�Ƿ���ʾ��־λ <RS_Close, RS_Open>����*/
	BYTE ShowMessage;
	/*Send Email ����<RS_Close, RS_Open>*/
	BYTE SendEmail;

	/*Alarm Out �ܿ���<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*�������ʱ��*/
	BYTE AlarmOutTime;	
	BYTE UrmetCloudNotify; /*Urmetר�ã��������ϴ�ʹ�ܿ���*/
	BYTE reservel[1];
	/*����ж���̵���ʱAlarm Out ����<RS_Close, RS_Open>*/
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];

	BYTE AlarmOutManagerEx[3][32];
}RSNet_SoleAbnormalSet_t;


//IO��������

//IoAlarmSet
#define RS_IOAlarm_NO    0
#define RS_IOAlarm_NC    1
#define RS_IOAlarm_Close 2

typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������

	//IO�ڱ���״̬
	BYTE IoAlarmSet;
	/*Alarm Out �ܿ���<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*�������ʱ��*/
	BYTE AlarmOutTime;
	/*����������ʱ��*/
	BYTE BuzzerMooTime;
	/*Record Channel, ����ͨ��¼��PS:��λ��¼, 1:����, 0:������*/
	UINT RecordChannel;
	/*¼����ʱ*/
	BYTE RecordDelayTime;
	/*�Ƿ���ʾ��־λ <RS_Close, RS_Open>����*/
	BYTE ShowMessage;
	/*Send Email ����<RS_Close, RS_Open>*/
	BYTE SendEmail;
	/*FullScreen ���� ����ȫ��<RS_Close, RS_Open>*/
	BYTE FullScreen;
	/*����ж���̵���ʱAlarm Out ����<RS_Close, RS_Open>*/
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	/*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE Record;
	/*Yiguang 2012.02.16 ����Դѡ��,0-IPC;1-���ض�*/
	BYTE AlarmIO;
	BYTE FtpLink;			/*FTP���� ����*/
	BYTE UrmetCloudNotify; /*Urmetר�ã��������ϴ�ʹ�ܿ���*/	
	UINT RecordChannel_EX[8];
	BYTE PushSwitch;
	BYTE sendToFTP;/*���ͽ�ͼ��FTP��0����ʹ�ܣ�1��ʹ��*/
	BYTE FtpVideoLink;	   /*FTP¼������ ����*/
	BYTE CloudPicUpload; /* �ƴ洢��Ƶ�ϴ� */
	BYTE CloudVideoUpload;
	BYTE FTPUpload;            /*FTP Upload ����*/
	BYTE reserved[58];

}RSNet_SoleIOAlarmSet_t;

typedef struct {
	/*I/O״̬����,0-������1-���أ�2-�ر�*/
	BYTE IoAlarmSet;	
	/*�������ʱ��*/
	BYTE AlarmOutTime;
	/*����������ʱ��*/
	BYTE BuzzerMooTime;
	/*¼����ʱ*/
	BYTE RecordDelayTime;
	/*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE Record;
	/*bit0-ShowMessage, 1-SendEmail, 2-FullScreen, 3-ftp upload,*/
	BYTE LinkFlag;
	BYTE reserve[2];
	/*ȡbitλ:ÿ�������������������32*8= 256·���κ�ͨ��¼��*/
	BYTE RecordChannel[32];
	/*ȡbitλ:3��ʾһ��ͨ�����3���������,ÿ���������봥�������������
	32*8= 256·���κ�ͨ���������*/
	BYTE AlarmOutManager[3][32];
	/*AlarmOut����*/
	BYTE AlarmOut;
	BYTE reserved2[15];
}IOAlarmSet_t;

typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	IOAlarmSet_t io[3]; //0-��ʾ����io; 1-��ʾipc��io����1; 2-��ʾipc��io����2
	BYTE AlarmLinkPtzEnable[3][32];       /* only for zip ��ǰͨ���������� ȡbitλ:ÿ�������������������32*8= 256·���κ�ͨ��¼�� 2018.3.6 add, 2018.4.17 changed  */
	BYTE LinkagePtzPresetIndex[3][256];   /* only for zip ��ǰԤ�õ� 2018.3.6 add, 2018.4.17 changed */
	BYTE LinkagePtzPatrolIndex[3][256];   /* only for zip ��ǰѲ���� 2018.3.6 add, 2018.4.17 changed */
	BYTE LinkagePtzPatternIndex[3][256];  /* only for zip ��ǰѲ���� 2018.3.6 add, 2018.4.17 changed */
	BYTE LinkagePtzMode[3][256];          /* only for zip ������ʽ��0-preset��1-partol��2-pattern 2018.2.6 add, 2018.4.17 changed */
}RSNet_NewSoleIOAlarmSet_t;


/*ģʽ�ƻ�ҳ�����,��EyeHome-Host�汾��Ч*/
/*���֧�ֵ�����Ŀ8��*/
#define MAX_AREA_NUMBER         8
/*ģʽ�Ŀ��Ʒ�ʽ,0-�ƻ������;1-�ֶ�����*/
//ControlWay
#define RS_SCHEDULE_CONTROL   	0
#define RS_MANUAL_CONTROL	  	1

/*ģʽΪ�ֶ�����ʱ��ģʽ,0-���ģʽ;1-˯��ģʽ;2-�ڼ�ģʽ;ע��:��ģʽ�Ŀ��Ʒ�ʽΪ�ƻ������ʱ,���账���ֵ*/
//ControlMode
#define RS_MANUAL_LEAVEHOME		0
#define RS_MANUAL_SLEEP			1
#define RS_MANUAL_ATHOME		2

typedef struct {
	UINT StructSize;
    BYTE ControlWay;            /*���Ʒ�ʽ,0-�ƻ������,1-�ֶ�����*/
    BYTE ControlMode;           /*�ֶ�����ʱ��ģʽ,0-���ģʽ;1-˯��ģʽ;2-�ڼ�ģʽ*/
	BYTE ModeSchedule[8][24];   /*�ƻ������ʱ��ģʽ,0-���ģʽ;1-˯��ģʽ;2-�ڼ�ģʽ*/
	BYTE AreaSwitch[4];         /*ģʽ����,�ֽ�0-���ģʽ;1-˯��ģʽ;2-�ڼ�ģʽ;ÿ���ֽڵ�0��7λ�ֱ��ʾ����1��8�Ŀ���״̬,0-��;1-��*/   	
	BYTE Reserved[6];
}RSNet_TELALARM_AreaParameter_t;

/*�����������,����ÿ������Ĳ���,ϵͳ���֧��8������,��EyeHome-Host�汾��Ч*/
typedef struct {
	UINT StoreSize;
	BYTE Name[20];
	BYTE AlarmOut;				/*Alarm Out �ܿ���<RS_Close, RS_Open>*/
	BYTE AlarmOutTime[8];		/*�������ʱ��*/
	BYTE BuzzerMooTime[8];		/*����������ʱ��*/
	BYTE DialNumber[8];			/*����ĺ�����*/
	UINT RecordChannel[8];		/*Record Channel, ����ͨ��¼��PS:��λ��¼, 1:����, 0:������*/
	UINT FullScreen[8];			/*FullScreen ���� ����ȫ��<RS_Close, RS_Open>*/
	BYTE RecordDelayTime[8];	/*¼����ʱ*/
	BYTE ShowMessage;			/*�Ƿ���ʾ��־λ <RS_Close, RS_Open>����*/
	BYTE SendEmail;				/*Send Email ����<RS_Close, RS_Open>*/
	BYTE Record;				/*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE Reserved[4];
}RSNet_TELALARM_SoleAreaParameter_t;

/*̽������������,��EyeHome-Host�汾��Ч*/
#define MAX_WIRE_SENSOR_NUMBER  4       /*���֧�ֵ�����̽��������Ŀ*/
#define MAX_WIRELESS_SENSOR_NUMBER  12  /*���֧�ֵ�����̽��������Ŀ*/

#define RS_TRIGGLE_NC    0
#define RS_TRIGGLE_NO    1

#define RS_ALARMTYPE_DOOR   0           /*�ŴŴ���*/
#define RS_ALARMTYPE_RAY    1           /*���ⴥ��*/
#define RS_ALARMTYPE_SILENT 2           /*��������*/
#define RS_ALARMTYPE_FIRE   3           /*�𾯱���*/
#define RS_ALARMTYPE_GAS    4           /*���б���*/

typedef struct {
	UINT StoreSize;
    BYTE Triggle;                   /*��������*/
    BYTE AlarmType;                 /*��������*/
    BYTE Area;                      /*��������*/
    BYTE AlarmDisplay;              /*�Ƿ���ʾ����*/
	BYTE Reserved[4];
}RSNet_TELALARM_SoleWireSensor_t;

typedef struct {
	UINT StoreSize;
    BYTE LearnCode;                 /*�Ƿ��Ѿ�����*/
    BYTE AlarmType;                 /*��������*/
    BYTE Area;                      /*��������*/
    BYTE AlarmDisplay;              /*�Ƿ���ʾ����*/
	BYTE Reserved[4];
}RSNet_TELALARM_SoleWirelessSensor_t;


//���ܷ���
/****************  huoxiaolong20110512  *****************************/

typedef struct{
	UINT StructSize;//�ýṹ���С
	/*�켣���ȣ�*/
	BYTE ContrailLength;
    BYTE reservel[3];
}RSNet_IntelligentSet_t;



typedef struct{
	UINT StructSize; 	//�ýṹ���С
	BYTE AlarmOut;
	/*Show Message ����*/
	BYTE ShowMessage;
	/*Send Email ����*/
	BYTE SendEmail;
	/*FullScreen ����*/
	BYTE FullScreen;
	/*Record Channel*/
	BYTE Record;
	/*Record Delay Time*/
	BYTE RecordDelayTime;/*¼����ʱ����ʱʱ��:30s��1min,2min,5min*/
	BYTE BuzzerMooTime;/*���������У�����ʱ��:0,10��20��40��60s*/
	BYTE AlarmOutTime;/*������������ʱ��:10��20��40��60s*/
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
	UINT StructSize; 	//�ýṹ���С
	/*ʹ�ܿ���*/
	BYTE RuleEnable;
	/*�������ͣ�0-���ߣ�1-�ܽ�*/
	BYTE RuleType;
	/*��������*/
	BYTE Direction;
	/*�ܽ����ƽǶ�ֵ*/
	short Forbidden;
	BYTE reservel[3];
}RSNet_RuleNum_t;

//��Ľṹ��added by zgm 20110118
typedef struct{
	short x;//X������
	short y;//Y������
	short RuleNum;//���������
	short ForbiddenDirection;//�������ƽǶ�
	BYTE reservel[4];
}RSNet_Point_t;

typedef struct{
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	/*���ܿ�����0-�رգ�1-��*/
	BYTE Enable;
	BYTE reservel[3];
	RSNet_SoleIntAlarmSet_t IntAlarm;
	/*����*/
	RSNet_Point_t TriWire[2 * RS_MAX_RULENUM];//add 20110118
	/*�ܽ�*/
	RSNet_Point_t Perimeter[MAX_PERIMETER_POINT * RS_MAX_RULENUM];//add 20110118
	/*ÿ��ͨ��������*/
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
	UINT StructSize; 	//�ýṹ���С
	/*AVD���Ϳ���*/
	BYTE TypeEnable;
	/*������5 ���ȼ�1-��ͣ�5-���*/
	BYTE level;
	BYTE reservel[2];
}RSNet_Avdtype_t;   




typedef struct{
	UINT StructSize; 	//�ýṹ���С
	/*Alarm Out ����*/
	BYTE AlarmOut;
	/*Show Message ����*/
	BYTE ShowMessage;
	/*Send Email ����*/
	BYTE SendEmail;
	/*FullScreen ����*/
	BYTE FullScreen;
	/*Record Channel*/
	BYTE Record;
	/*Record Delay Time*/
	BYTE RecordDelayTime;/*¼����ʱ����ʱʱ��:30s,1min,2min,5min*/
	BYTE AlarmOutTime;/*������������ʱ��:10��20��40��60s*/
	BYTE BuzzerMooTime;/*���������У�����ʱ��:0��10��20��40��60s*/
	UINT RecordChannel;
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	BYTE reservel[4];

}RSNet_SoleAvdAlarmSet_t;



typedef struct{
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	/*ͨ�����أ�0-�رգ�1-��*/
	BYTE Enable;
	BYTE reservel[3];
	/*ͨ����ѵʱ�䣬��СΪ1�룬���Ϊ60��*/
	ULONG  RotateTime;
	RSNet_Avdtype_t Avdtype[RS_MAXAVDTYPE_NUM];
	RSNet_SoleAvdAlarmSet_t AvdAlarm;
}RSNet_SoleIntAvdSet_t;
//��ȱ

//MediaConType
#define RSPlat_UDP 0
#define RSPlat_TCP 1
#define RSPL_MAXNAMELEN 36

#define RSPL_FORM_SHOW *(UINT*)"PLEn"
#define RSPL_FORM_HIDE 0x00000000
typedef struct{
	UINT StructSize;   		//�ýṹ���С
	
	//RsPlatform
	BYTE PuID[RSPL_MAXNAMELEN];
	BYTE PlatformAddr[RSPL_MAXNAMELEN]; //�����������ַ
	UINT PlatformPort;     //����������˿�
	BYTE PlatformSelect;
	BYTE PlatformEnable;
	BYTE MediaConType;     //0(udp) 1(tcp)
	BYTE reservel[1];
	UINT PlatFormShowTag; //�Ƿ���ʾƽ̨����ҳ��
}RSNet_PlatformSet_t;

//HUAWEI_Platform
#define RSPL_STATUS_OFFLINE  	0
#define RSPL_STATUS_ONLINE 		1

typedef struct{
	UINT StructSize;   		//�ýṹ���С
	
	BYTE Enable;			/* RS_Open, RS_Close*/
	BYTE CenterStatus;		/*RSPL_STATUS_OFFLINE, RSPL_STATUS_ONLINE*/

	BYTE ProtocolType;		/* RSPlat_UDP, RSPlat_TCP */
	BYTE DelayTime;			/*��ʱ����ʱ�� 0��100 s */

	BYTE MainDevID[24];
	BYTE CenterIP[16];
	UINT CenterPort;
}RSNet_HuaweiPlatformSet_t;

typedef struct{
	UINT StructSize;   		//�ýṹ���С
	UINT ChannelMask;		//ͨ������
	
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


//��������
//main_resolution, sub_resolution
#define RS_EncodeD1   0
#define RS_EncodeHD1  1
#define RS_EncodeCIF  2
#define RS_Encode720P 3
#define RS_Encode960P 4

//new define of resolution mode (added 2014-05-13)
typedef enum
{
    RSMode_D1 = 0,          //D1ģʽ
    RSMode_D1_960H,         //D1��960Hģʽ
    RSMode_CIF,             //��CIFģʽ
    RSMode_CIF_DISABLE_FPS, //��CIF���ǲ�����֡��
    RSMode_720P,            //��720Pģʽ
    RSMode_720P_960P,       //720P��960H
    RSMode_1080P,           //��1080Pģʽ
    RSMode_720P_1080P,      //720P��1080Pģʽ
    RSMode_VI_AUTO_DETECT,  //Ŀǰֻ֧��720P��960H�Զ�ʶ��
    RSMode_1080P_720P_WX,   //IE��ʾ1080P,720P��WD1,WHD1,WCIF
    RSMode_720P_WX,         //IE��ʾ720P��WD1,WHD1,WCIF
    RSMode_720P_AxB,        //720P��960*480 960*240 480*240.(lorexר��)
    RSMode_1080PCIF_720P_WX,//IE��ʾ1080PCIF,720P��WD1,WHD1,WCIF
    RSMode_1080P_720P_960H,  //3�ֱַ���ģʽ��֧�֣�С�ڻ������ѡģʽ�ķֱ��ʾ���ѡ    
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

/* DVR�ض�ϵ�в�Ʒ�ͺ�(D98 AHDϵ��,TVIϵ��;D99ϵ��), Զ����ʾ������ѡ������ */
typedef enum
{
    BIT_INVALID = 0,
    BIT_1_2_4,        //1M��2M��4M
    BIT_1_2_4_6,      //1M��2M��4M��6M
    BIT_1_2_4_6_8    //1M��2M��4M��6M��8M
}D9X_Bitrate_Mode_E;

//SWAN �ͻ�����ʹ��
#define RS_MainBitrate_Normal	RS_MainBitrate_4096;
#define RS_MainBitrate_Good		RS_MainBitrate_5120;
#define RS_MainBitrate_Better	RS_MainBitrate_6144;
#define RS_MainBitrate_Best		RS_MainBitrate_8192;

/* ��������ҳ������ṹ */

typedef struct
{
	UINT StructSize; //�ýṹ���С

	BYTE ResolutionMode; /*0-D1, 1-960*/
	
	BYTE StreamType;   // 0 main 1 sub
	BYTE reservel[2];
}RSNet_MainStreamSet_t;

typedef struct{
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; //ͨ������

	/*������: */
    int main_bitrate;
	
	/*
	  RS_Encode720P-720P��
	  RS_EncodeD1-��ϸ��
	  RS_EncodeHD1-�ḻ��
	  RS_EncodeCIF-��ͨ*/
	BYTE main_resolution;
	
	/* 	��ͨ��¼��֡��:
		PAL:1~25 NTSC:30֡
		ѡ���Ӧ������û��0ֵ 
		PAL����������400��NTSC����������480*/
	BYTE main_fps;	
	
	BYTE main_audio;/*������¼��:<RS_Close, RS_Open>*/	
	BYTE main_resolution960; 

	BYTE ResolutionType; // 0:720p 1:D1
	BYTE VBR; 
	/*IPCʹ��*/
	BYTE BitrateType; /* 0 :������1:������2: ������ 3: QVBR*/
	BYTE VideoQuality; /* ͼ������0: ���1:����2:��3:��4:����5:���*/
	unsigned short CustomMainBitrate; /* �Զ������� */
	BYTE IFrameInterval; /* I ֡�����Χ��1-100  �� */
	/*IPCʹ�� END */
	BYTE AMRSwitch; /*AMR ����뿪��(DENAVO�ͻ�ר��). 0:disable, 1:enable*/
}RSNet_SoleMainStreamSet_t;

/* stream */
typedef struct 
{
    BYTE FrameRateMin;/*֧�ֵ�֡�ʷ�Χ��Min,�����Ϊ0��δ���*/
    BYTE FrameRateMax;/*֧�ֵ�֡�ʷ�Χ��Max,�����Ϊ0��δ���*/
    WORD DefBitrate; /*save default bitrate*/
    WORD ResolutionWidth;/*֧�ֵķֱ��ʣ�����Ϊ0��δ���*/
    WORD ResolutionHight;/*֧�ֵķֱ��ʣ�����Ϊ0��δ���*/
    UINT BitrateRange;   /*��λȡ RS_MainBitrate_e��RS_SubBitrate_e��1:��ʾ֧�֣�0:��ʾ��֧�֣�����ȷ����Ӧ������*/
}RSNetNew_ResolutionRateRange_t;


//¼������
//RecordMood
#define RS_RecordSchedule 0  //�ƻ���¼��
#define RS_RecordAlaways  1  //����¼��
#define RS_RecordManual   2  //�ֶ�¼��

//PackTime
#define RS_PackTime_15Min 0
#define RS_PackTime_30Min 1
#define RS_PackTime_45Min 2
#define RS_PackTime_60Min 3

//PreRecordTime
#define RS_PreRecordTime_0s  0
#define RS_PreRecordTime_10s 1

typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������

	/*ͨ���Ĵ򿪹رգ�һ��ͨ����Ӧ<RS_Close, RS_Open>*/
    BYTE ChnCloseOrOpen;    //Qt ui ͨ��¼�񿪹�
	BYTE RecordStreamMode;  // main,sub    
    BYTE PreRecSwitch;      //Qt ui ͨ��Ԥ¼�񿪹�
	BYTE RecordAudioEnable; //0:close 1:open
	RSNetNew_ResolutionRateRange_t Range[8];	/* lorex���recordҳ��ֱ�������*/
	BYTE Num;/*֧�ֵķֱ��ʸ���,���ѡ��8��*/
	BYTE ResolutionIndex; /* whice one resolution index has been choose to set */
	BYTE ManualRecSwitch;/*Manual_Record*/
	BYTE OffLineRecSwitch;	/* ����¼�񿪹� */
	BYTE Reserved;
	BYTE EncTypeList;//��λ��ʾ,Ϊ1ʱ��ʾ	//H.264,H.265,H.264+,H.265+,MJPEG
	BYTE EncTypeVal;
	BYTE pageBit;//bit_0:preRecord,bit_1:resolution,bit_2:encType
}RSNet_SoleRecordSet_t;

typedef struct {
	UINT StructSize; 	//�ýṹ���С

    BYTE RecordMode;/*¼��ģʽ:0-��ʱ¼��1-����¼��2-�ֶ�¼��*/
    BYTE PackTime;/*¼����ʱ�䣬0-15���ӣ�1-30���ӣ�2-45���ӣ�3-60����*/    
    BYTE PreRecordTime;/*Ԥ¼��Ԥ¼ʱ��:0��10s*/
	BYTE RedundanceRec;      //�Ƿ�����¼��:0-close 1-open
}RSNet_RecordSet_t;



//¼��ƻ�

//hour
/*Ϊ0��ʾ��¼��Ϊ2��ʾ����¼��1-����¼��*/
#define RS_NoRecord     0
#define RS_AlarmRecord  1
#define RS_NormalRecord 2

#define RS_NormalScheduleMode 0
#define RS_SmartScheduleMode 1

#define RS_ScheduleResolution_720P	0
#define RS_ScheduleResolution_D1   1
#define RS_ScheduleResolution_CIF  2
typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	
	//MainStream, For MainStream Record Schedule
	int NormalHour[8]; 
	int MotionHour[8];
	int AlarmHour[8];
	int IntelligentHour[8];
	
	//Smart�汾
	BYTE SmartScheduleEnable; //1:Ϊ��smart����,��֮Ϊû��
	BYTE ScheduleMode; 
	BYTE onlySDexit;
	BYTE PageBit;//Bit_0:�Ƿ���Continousģʽ
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
	/* bit 0 Ϊ��ͨ¼��bit 1 Ϊ����¼��bit 2 Ϊ����¼��
	 * bit 3 ΪOSC��bit 4 ΪLCD��bit 5 ΪPID   bit 6 ΪSensor¼��   bit 7 ΪPIR¼��
	 * ��Ӧ��bitλΪ1��ʾ���ã�Ϊ0��ʾ����
	 * HalfHour[8]�����գ���һ~����: 0~6����7λΪ����λ //2016.03.09
	 */
	//2016.03.09
	UINT HalfHourExt[8][48]; // 7 days and 48 halfhours
	/* bit 0ΪHD��bit 1ΪFD��bit 2ΪPCC
	 * ��Ӧ��bitλΪ1��ʾ���ã�Ϊ0��ʾ����
	 * HalfHourExt[8]�����գ���һ~����: 0~6����7λΪ����λ
	 *2018.04.27---����������֤Ϊipc���ܲ�ʹ��HalfHour�ֶΣ�ֻʹ��HalfHourExt�ֶ�
	 *bit 0 ΪLCD¼��bit 1 ΪPID¼��bit 2 ΪOSC¼��
	 * bit 3 ΪPD��bit 4 ΪFD��bit 5 ΪCC
	 *add bit 6 Sound Alarm
	 */		 
	
}RSNet_SoleScheduleSet_t;

//����¼��ƻ��� Qt v2
typedef struct
{
    UINT StructSize; 	//�ýṹ���С
    UINT ChannelMask; 	//ͨ������

    BYTE HalfHour[8][48]; // 7days and 48 halfhours
    /* bit 1ΪPEA¼��, bit 2 ΪAVD¼��, bit 3 ΪOSC¼��
     * ��Ӧ��bitλΪ1��ʾ���ã�Ϊ0��ʾ����
	 *2018.04.27---����������֤Ϊ
	 *bit 0 ΪLCD¼��bit 1 ΪPID¼��bit 2 ΪOSC¼��
	 * bit 3 ΪPD��bit 4 ΪFD��bit 5 ΪCC
     */
}RSNet_SoleIntelliRecSchedule_t;


//ϵͳά��ҳ��
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
	UINT StructSize; 	//�ýṹ���С

	//�Զ�ά������
    /*ά���ľ���ʱ�䣬ʱ��*/
    BYTE time[4];
    
    BYTE automaintain; /*�Զ�ά�����أ�<RS_Open, RS_Close>*/

	/*ά������
	  RS_EveryDay
	  RS_EveryWeek
	  RS_EveryMonth
	 */
	BYTE maintainperiod1; 
	/*ά�����ڶ���0--6ÿ�ܵ��ܼ���7--37ÿ�µļ���
	  RS_Monday 		
	  RS_Tuesday		
	  RS_Wednesday 	
	  RS_Thursday		
	  RS_Friday		
	  RS_Saturday		
	  RS_Sunday		
	 */
    BYTE maintainperiod2; 
	
	/*Ĭ���û���¼�û�����
	255:��ʾ�����ôι���
	0-off; 1-admin, 2~7��ʾ6����ͨ�û�
	 */
	BYTE defaultuserid;
	BYTE EnabledUserList;/*	�ѿ�����0bit-admin; 1~6bit��ʾ6����ͨ�û�*/
	BYTE EnableUser;/*�Ƿ�����Ĭ���û�����*/
    BYTE TimeFormat;  //(0)24Сʱ��,(1)12Сʱ��
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

//ϵͳ����
//��ȱ




//Ӳ�̹���
//��<Ӳ����Ϣ>ͬһ�ṹ��


//�߼�����

//Զ������

//�ָ�Ĭ������
//��λ����ֵ


typedef struct {
	UINT StructSize;
	BYTE DevicePuid[64];
	UINT Result;
}RSNet_TuobaoInfo_t;


typedef struct {
	UINT StructSize; 	//�ýṹ���С

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
	UINT StructSize; 	// �ýṹ���С

	BYTE Switch;         	// �Ƿ�Ҫ����WIFI�Ŀ���
	BYTE EncryptType;		// ���ܷ�ʽ  0 -������ 1:WEP 2:WPA-PSK 3:WPA2-PSK 4:WPA-AUTO
	BYTE AuthMode;			// ��֤ģʽ 	WEP��֤ģʽ:1:OPEN, 2:SHARED   WPA����֤ģʽ:3-TKIP, 4-AES 

	BYTE Reserve1[1];
	
	//��Կ.
	//ps:WEP��֤ģʽ,���볤��ֻ��5/10/13/26 ���ֳ���.
	//WPA��֤����������
	//��Կ���ȱ��������֤ģʽ�Ĺ��򳤶Ȳ�����Ч����wifi
	BYTE Pwd[32];
	BYTE SSID[32];
}RSNet_WifiSet_t;


////wifi�ȵ��������ܲ������ݽṹ��
typedef struct
{
	UINT StructSize; 	// �ýṹ���С
	UINT ChannelMask;
	
	BYTE MacAddr[6];	
	BYTE reserve1[2];

	BYTE SSID[32];
	BYTE Protocol[16];	  	// 802.11����ģʽ
	
	BYTE EncryptType;		// ���ܷ�ʽ  0:������ 1:WEP 2:WPA-PSK 3:WPA2-PSK 4:WPA-AUTO
	BYTE AuthMode;			// ��֤ģʽ 	WEP��֤ģʽ:1:OPEN, 2:SHARED   WPA����֤ģʽ:3-TKIP, 4-AES 
	
	BYTE SignalQuality;   	//�ź�ǿ��
	BYTE Frequency;       	// Ƶ�� 

}RSNet_SoleWifiSet_t;


//���ع��ܹ���
typedef struct {
	UINT StructSize; //�ýṹ���С
	/*¼���Ƶ���*/
	BYTE RecordCarNumber;
	/*Ԥ��������ʾ*/
	BYTE PreviewCarNumber;
	/*¼��GPS����*/
	BYTE RecordGps;
	/*�ٶȲ�����Դ*/
	BYTE SpeedSource;
	/*���ƺ���*/
	BYTE CarNumber[MaxNameLen];
	/*�Ѵ�������*/
	UINT Pulse;
	/*��ʱ�ػ�ʱ��*/
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
		unsigned char twentychn[20]; //��ʮ����
		unsigned char sixteenchn[16]; //ʮ������
		unsigned char eightchn[8]; //1+7����
		unsigned char sixchn[6]; //1+5����
		unsigned char fourchn[4]; //�Ļ���
		unsigned char ninechn[9]; //�Ż���
		unsigned char onechn;    //һ����
		unsigned char thirtysixchn[36];
		unsigned char reserve[28];
	}ChannelSelect;/*����Ԥ��ͨ����ֻ��ѡ������һ��Ԥ��ģʽ*/
	unsigned char Margin[4];  /*0:��߾�, 1:�ұ߾�, 2:�ϱ߾�, 3:�±߾�, 2����Ϊ��λ*/
	unsigned char PollingTime;/*�����ѯʱ����: ��ֵ:0~300��0��ʾ����ѯ*/
	unsigned char StaticOrDynamic;/*0-static��1-dynamic(�û��ֶ�����)*/
	unsigned char OutputMode;/*�����Ԥ��ģʽ:0-һ���棬1-�Ļ��棬2-�Ż��棬3-ʮ������*/
	unsigned char spotAudio;/*�������Ƶͨ��ѡ��:0-�ر�, 1-ch1, 2-ch2, 3-ch3, 4-ch4 ... ... 16-ch16*/
	unsigned char reserve[24];/*�����ֽ�*/
}RSNet_OutputAttr_t;

typedef struct{
	UINT StructSize; //�ýṹ���С
	
	RSNet_OutputAttr_t OutputAttr[RSNet_OD_NUM]; /*voattr[0]-OD_VOUT, voattr[1]-OD_VSPOT, voattr[2]-OD_VGA*/
	unsigned char Transparency;/*͸���� ��ֵ��0~128 ��ֵԽ��Խ͸��*/
	unsigned char IsVoutOrSpot;/*0-Vout,1-Spot*/
	unsigned char Resolution;/*4Ϊ����������豸*/
	unsigned char InitGuiDev;/*����ʱ��Ĭ��GUI ��ʾ�豸:0-VOUT, 1-VGA ,2-AUTO*/
	unsigned char OutputDev;/*����豸:0-CVBS,1-VGA,2-HDMI*/
	unsigned char reserve1[15];/*�����ֽ�*/
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
	//predefine Ԥ���壬δʵ�� 
	BYTE Mirror;        	//ˮƽ��ת  	0:close; 1:open	
	
	BYTE Flip;           	//��ֱ��ת 	0:close; 1:open

	BYTE Rotate;    /* 0~����ת;1~˳ʱ����ת90��2~˳ʱ����ת180��3~˳ʱ����ת270�� */

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

/* ͼ����� ����ҳ�������½ṹ */
typedef struct
{
    UINT StructSize;
    UINT ChannelMask;

    BYTE IRCutMode;			/* 0:auto;1:day;2:night;3: ��Ƶ�Զ�,4:IO trigger,5: schedule*/
    BYTE IRCutDelay;		/* 1~36;unit:s */
    BYTE IRCutSensitive;	/* 0:Hight;1:Midd;2:Low */
    BYTE Mirror;        	/* ˮƽ��ת  	0:close; 1:open	*/

    BYTE Flip;           	/* ��ֱ��ת 	0:close; 1:open */
    BYTE Rotate;			/* 0~����ת;1~˳ʱ����ת90��2~˳ʱ����ת180��3~˳ʱ����ת270�� */

    /* ���ⲹ�� */
    BYTE BackLightMode; /* 0:disable, 1:enable */
    BYTE BackLightLevel; /* 0:low, 1:middle, 2:high   for  bpl  range is 1 - 15*/

    /* 3D���� */
    BYTE R3dnrMode; /* 0:disable, 1:auto, 2:manual */
    BYTE R3dnrThreshTarget; /* the thresh value when manual [1,0xff] */

    /* ���ֿ�̬ */
    BYTE DwdrMode;  /* 0:disable, 1:enable */
    BYTE DwdrStrength;	/* ֵ��Χ[1,0xff]  */

    /* ������� */
    BYTE GainControlMode; /* 0:off, 1:low, 2:middle, 3:high */

    /* ��ƽ�� */
    BYTE WBMode; /* 0:auto, 1:manual, 2:indoor */
    BYTE Rgain;	/* ֵ��Χ[1,0xff]  */
    BYTE Ggain; /* ֵ��Χ[1,0xff]  */

    BYTE Bgain; /* ֵ��Χ[1,0xff]  */

    /* ����*/
    BYTE ShutterMode; /* 0 auto, 1 manual  */
	BYTE IRFuncType;       /*���⹦�ܿ������߹ر�,0:�رգ�1:�Զ�*/
	BYTE AgcMode;          /*1:GainControlMode new mode (0~128),0:GainControlMode old mode (0:off, 1:low, 2:middle, 3:high)*/
    S32  eShutterSpeed; /* the ShutterUsecs value when manual
                                            50HZ �����1/25
                                            60HZ, disable �����1/30
                                        */
    BYTE FlickerCtrl;   /* ��˸����  0:50HZ   1:60HZ  2:disable */
	BYTE DefogMode;/* 0:disable, 1:auto, 2:manual */
	BYTE DefogStrength;/*ȥ��ǿ��,���ֶ�ʱ���ã�0~255*/
	BYTE IRISMode;/* 0:disable, 1:auto */
	BYTE autoFocus;/*0:disable; 1:enable; NOVUS �Զ��Խ�*/
	BYTE LEDEnable;/*0:OFF; 1:ON;2:auto,Novus IR LED Light*/
	RSNetTimeSet_t StartTime;
	RSNetTimeSet_t EndTime;
	BYTE HideRotate; /*0:�������� 1:����90��270*/
	BYTE GainSwitch; /*Gain switch,0:OFF,1:ON*/
	BYTE ColorGain;	/* Color Gain,[1-0xff]*/
	BYTE BrightGain;/* Bright Gain, [1-0xff]*/
	BYTE R2dnrMode; /* 2D����,0:Low, 1:Medium, 2:High */
	BYTE DefogFakeLottery;/* ȥα�ʣ�ֵ��Χ[1,0xff]*/
	BYTE FloodLightMode; /*�׹�� 0:disable 1:enable*/
	BYTE FloodLightValue;/*ֵ��Χ[0, 100]*/
	BYTE BackLightZone;		/* 0 --> ȫ��    1 --> ����    for bpl */
	BYTE AntiShakeEnable;  	/* 0 ��  1 ��*/
	BYTE AntiShakeLevel;	/*�ȼ�0-7������ǿ�ȼ��𣬼���Խ�󣬷���Ч��Խ��*/
	BYTE AntiShakeLevelFlag;/*0������ʾLevel,1:��ʾlevel */
	BYTE BackLightLevelCheck;	/* 1: ��ģʽ 1-15 ��ֵ���ã�0����ģʽ��0:low, 1:middle, 2:high��*/
	BYTE WDRFlag;/*0:IE��ʾWDR,1:IE��ʾDWDR*/
	BYTE HLCSwitch; /*ǿ�����ƿ��� 0:disable,1:enable*/
	BYTE HLCStrength; /*ǿ������ֵ��Χ[1-255]*/
	BYTE reverser2[42];
}RSNetNew_CameraSet_t;
///////////////////////////////////////////////////////////////////////////
//�ؼ��������������ݽṹ��, ���ṩ��˾�ڲ�ʵ�ֹؼ���������ʹ�á��������ṩ��
///////////////////////////////////////////////////////////////////////////
typedef struct {
    UINT StructSize;
    UINT ChannelMask;
    BYTE mode;// 0:normal,1:daylight,2:night
    BYTE reverser[15];
    RSNetNew_CameraSet_t cameraSet[3];
}RSNetNew_CameraModeSet_t;

typedef struct {
	UINT StructSize; 	//�ýṹ���С
	
	BYTE Mac[6];
	BYTE reservel[2];
	BYTE model[32];
	BYTE serialNum[32];
    BYTE reservel2[2];
    BYTE WifiMac[6];
	BYTE SnNum[32];
}RSNet_KeyConf_t;

//////////////////////////////////////
//IP�ڰ��������˲������ݽṹ��
#define MAX_IPFILTER_NUM 16

#define FILTERSWITCH_OPEN  0
#define FILTERSWITCH_RELYON_ENABLE 1
#define FILTERSWITCH_CLOSE   2

typedef struct {
	UINT StructSize;
	
	BYTE FilterSwitch; //0 �������е�IP �ļ��(��������IP����ͨ�У�1����IP ����������(����SingleLock �Ƿ���) -1 ����IP ������������������������IP)

	BYTE reserve[3];
}RSNet_IPFilter_t;

typedef struct {
	UINT StructSize;
	UINT ChannelMask;
	
	BYTE IPAddr[4];
	BYTE Enable;//����IP��ַ��鿪�� RS_OPEN  1 ; RS_CLOSE 0 

	BYTE reservel[3];
}RSNet_SoleIPFilter_t;

//////////////////////////////////////
//RTSP�������
//////////////////////////////////////

//enAuthMode
#define RTSP_HTTP_AUTH_NONE   0
#define RTSP_HTTP_AUTH_BASIC  1
#define RTSP_HTTP_AUTH_DIGEST 2

typedef struct {
	UINT StructSize;

	UINT RtspPort;
	UINT enAuthMode;//��֤ģʽ 
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
//FTP�������
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
	BYTE TimeMode;    /*�ϴ�¼���ʱ������*/
	BYTE ReqTypeMask; /*�����������룺һ��λ��Ӧһ���������ͣ���λ��ʾ������0��ʾ�ر�*/
	BYTE RecType;     /*1:����¼��,2:����¼��,3:����¼��*/
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
	BYTE VideoSwitch;//�Ƿ�����Ƶ
	BYTE Reserved; 
	BYTE useFtpIpAddr2; //1��ʹ��FtpIpAddr2   0����ʹ��
	UINT SendFileSize;   // �� �ֽ� Ϊ��С��λ
	BYTE FilePath[96];   // д�ļ����ļ�·��
    BYTE FtpServer[32];  //FTP����(shenzhen extend)
    BYTE FtpServer2[64];
	BYTE FtpIpAddr2[64]; //2018.2.6
	BYTE CertPem[1024 * 4];    // cert pem
	BYTE CertPwd[64];          // cert password
	BYTE PrivateKey[1024 * 4]; // private key
	BYTE PrivateKeyPwd[64];    // private key password
	BYTE EncMode;
	BYTE PicResolution;     //ͼƬ�ֱ��ʡ���ӦRESOLUTION_E��ö��ֵ
	BYTE PicQulity;         //ͼƬ����  90 75 65 50 35 20
	BYTE VideoStreamType;   //��Ƶ�������� 0:Mainstream 1:Substream
	BYTE EnNormalVideo;     //Normal Video�ϴ��ܿ���
	BYTE MaxPackInterval;   //unit: Min 10 20 30 45 60
	BYTE NormalVideoSwitch[32]; //Normal Video��ͨ������
	BYTE VideoFormat;	// 0��p��    1��N��
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
	BYTE TimeTrigger;	////ʱ����
	BYTE Enable;		////�ƴ洢�Ƿ���
	BYTE MotionEnable;	////�ƶ�����Ƿ���
	BYTE CloudType;		////�Ƶ�����
	BYTE Reserved[4];
	BYTE RecvEmail[3][36];  //�ռ��˵�ַ
}RSNet_CloudStorageSet_t;

typedef struct {
	UINT StructSize;
    /*SMTP������*/
    BYTE SMTP[36];

    /*�����˵�ַ*/
    BYTE SendEmail[36];

    /*����������*/
    BYTE SendEmailPW[36];

    /*�ռ��˵�ַ*/
    BYTE RecvEmail[3][36];

    /*�˿ں�*/
    UINT Port;

    /*SSL���أ�0--�رգ�1--��*/
    BYTE SSLSwitch;

    /*�Ƿ�ʹ��email,0--�رգ�1--����*/
    BYTE EmailSwitch;

    /*�ʼ����ͼ��*/
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

// ��ά��ɨ��P2p ID �ṹ��
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
    BYTE DeviceType[MaxNameLen]; //�豸����
    BYTE SoftwareVer[MaxNameLen]; //ϵͳ����汾	
}RSNet_FtpAutoUpgrade_t;

// MasterSwitch 
#define MASTER_SWITCH_OFF     0
#define MASTER_SWITCH_ON      1
#define MASTER_SWITCH_FORBID  2
typedef struct {
	UINT StructSize;

	BYTE MasterSwitch;   // 0 - �ر��ֶ�¼�� 1- �����ֶ�¼��  2- �����ô˿���
	BYTE Reserve[3];   // Ԥ���ֽڣ�����ͨ���ֶ����ؿ���
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
	BYTE MicInVolume;	/* ����������С(0 - 10) */
	BYTE LineOutVolume; /* ���������С(0 - 10) */
	BYTE AdecEncoding;	/* ��������� 0, PT_G711U;1,PT_G711A */
	BYTE InputMode;		/* 0: line in  1:mic */
	BYTE Bitrate;/* ����G726 ��������Ч��0,16kbps; 1,24kbps;2,32kbps;3,40kbps;4,64kbps*/
	BYTE AudioSampleRate;/*��Ƶ�����ʣ�0-8KHZ,1-16KHZ*/
	BYTE AudioSampleEnable; /*��Ƶ������ʹ�ܿ��أ�0-�أ�1-��*/
	U8 AdecEncodingSupport;	/*  AdecEncoding ֧���������λȡֵ����Audio_Type_EΪ˳��  */
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
	UINT FrameRate;   //��ǰ֡��,1~30
	UINT BitRate;     // Bit rate

	U64 FrameSelect;  //��λȡ֡
}IPCFRAMEINFO_S;

typedef struct {
	UINT StructSize;
	UINT ChannelMask;

	BYTE OsdMask;   	// osd��ʾ     0:no 1:yes
	BYTE TimeMask;  	// time��ʾ��  0:no, 1:yes
	BYTE Frequency;     // Ƶ��        0:60hz, 1:50hz
	BYTE StreamType;    //�������ͣ�   0:sigle, 1:double

	BYTE EncodeType;   //��ǰ����,    when sigle streame; 0:D1,  1:720P,  2:1080P, when double streame; 0:1080p+cif,  1:720P+D1,  2:720p+cif
	BYTE Reserve[3];

	IPCFRAMEINFO_S FrameInfo;     //֡��Ϣ
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

	UINT ChnNoChoice; // ��λȡ��Ӧͨ����־λ
	BYTE TimeTrigger;
	BYTE MotionSnapEnable;
	BYTE Reserved[2];
}RSNet_UploadPhotoSet_t;

typedef struct
{
	UINT StructSize;
	
    UINT MotionScheduleHour[32][8];//ͨ�����,7��,Сʱ��λȡ
    BYTE MotionVideoChannel;
	BYTE Reserved[3];
}RSNet_UploadVideoSet_t;

typedef struct
{
    UINT StructSize;
    UINT ChannelMask;       //ͨ������
    BYTE HalfHour[8][48];   // 7days and 48 halfhours
    BYTE Reserved[16];
}RSNet_SoleUploadVideoSet_t;

typedef struct 
{    
	UINT StructSize;

	BYTE key[3][64];      /*�û�KEY*/
    BYTE secret[3][64];   /*�û�KEY����*/
    BYTE Enable;
    BYTE CloudType;       /*�ƶ˷������ͣ�0-DROPBOX,1-GOOGLE*/
    BYTE TimeTrigger;
    BYTE MotionEnable;
    BYTE DriveName[32];   /*�ϴ�Ŀ¼*/
    UINT Channel;
    BYTE FTPPATH[36];     /*FTP·��*/    
    UINT Channel_EX[8];
}RSNet_NormalCloudStorageInfo_t;

typedef struct 
{
	UINT StructSize;

	BYTE SMTP[36];        /*SMTP������*/
    BYTE SendEmail[36];   /*�����˵�ַ*/
    BYTE SendEmailPW[36]; /*����������*/
    BYTE RecvEmail[3][36];/*�ռ��˵�ַ*/
    UINT Port;           /*�˿ں�*/
    BYTE SSLSwitch;   /*SSL���أ�0--�رգ�1--��*/
    BYTE EmailSwitch; /*�Ƿ�ʹ��email,0--�رգ�1--����*/
    BYTE intervaltime;/*�ʼ����ͼ��0:60,1:180,2:300,3:600s*/ 
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
 * 8 Bytes Alignment�� 9*32 = 288 bytes 
 * start
 * ******************************************************************/

typedef struct{
    S16 x1; //must S16 here,can't be U16
    S16 y1;
    S16 x2;
    S16 y2;
}Net_Line_S;

/* �߼�����-�ܽ���� */
typedef struct {
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;          /*0-�رգ�1-��*/
    BYTE BuzzerMooTime;      /*���������У�����ʱ��:0��10��20��40��60s*/
    BYTE AlarmOutTime;       /*������������ʱ��:0��10��20��40��60s*/
    BYTE RecordDelayTime;    /*¼����ʱ����ʱʱ��:0��10��20��40��60s*/
    BYTE AlarmOutManager[4];   /*ֻ��һ����������ģ���AlarmOutManager[0]����*/
    UINT RecordChannel;
    BYTE Record;               /*Record channel switch*/
    BYTE ShowMessage;          /*Show Message ����*/
    BYTE SendEmail;            /*Send Email ����*/
    BYTE FullScreen;           /*FullScreen ����*/
    BYTE RuleSwitch;        /*ÿ��ͨ����һ���ֽڱ�ʾ���8������0-�رգ�1-ʹ��*/
    BYTE RuleType;          /*DVRר��: ÿ��ͨ����һ���ֽڱ�ʾ���8��-�������ͣ�0-���ߣ�1-�ܽ�*/
    BYTE LineTwoWay;        /*DVRר��: ÿ��ͨ����һ���ֽڱ�ʾ���8��-��������˫��0-��1-˫��*/
    BYTE RuleScene;	   		/*�������ͣ�0-���ڳ�����1-����*/
    BYTE Sensitive;	        /*�㷨������0-9*/
    BYTE NewRuleType;  		/*IPCר�ã�����ķ�������bit��ʾһ������ķ��� 0-a->b��1-b->a,2-a<->b*/ //2015.11.12
    
    S8   AIChannel;         /*��ǰʹ������ͨ����ģ��ͨ���ǵڼ�ͨ��,-1:û��ģ��ͨ��ʹ�����ܹ���*/
    BYTE IsSpot;             //�ĳ��ж��Ƿ���spotAudio
    Net_Line_S RuleLine[32];	/*ÿͨ�������64��������,��32���ߣ�����ǰ�����ֻʹ�õ�1���ߣ�
                                  ������ܽ�����8������������������ɱպ�ͼ�� */
	UINT RecordChannel_EX[8];

	BYTE DrawLineEnable;/*�Ƿ���Ԥ������ 20170313 add*/
	BYTE FtpLink;
	BYTE sendToFTP;/*���ͽ�ͼ��FTP��0����ʹ�ܣ�1��ʹ��*/
	BYTE IVALines;/*Ԥ���ͻط��Ƿ���Ҫ���ߣ�0-�����ߣ�1-����*/
	BYTE PushSwitch;
	BYTE FtpVideoLink;         /*FTP¼������ ����*/
	BYTE CloudPicUpload; 
	BYTE CloudVideoUpload; /* �ƴ洢��Ƶ�ϴ� */
	//BYTE reserved[2];
	/*ȡbitλ:3��ʾһ��ͨ�����3���������,ÿ���������봥�������������
	32*8= 256·���κ�ͨ���������*/
	BYTE AlarmOutManagerEx[3][32];
}RSNet_SolePerimeterLine_t;

/* �߼�����-��Ƶ��� */
typedef struct{
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;                   /*0-�رգ�1-��*/
    BYTE ChnCruiseTime;               /*��ѯʱ��*/
    BYTE BuzzerMooTime;               /*���������У�����ʱ��:0��10��20��40��60s*/
    BYTE AlarmOutTime;                /*������������ʱ��:0��10��20��40��60s*/
    UINT CheckTypeSwitch;             /*������Ϳ���*/
    BYTE AlarmOutManager[4];            /*ֻ��һ����������ģ���AlarmOutManager[0]����*/
    UINT RecordChannel;
    BYTE Record;                        /*Record channel switch*/
    BYTE RecordDelayTime;             /*¼����ʱ����ʱʱ��:0��10��20��40��60s*/
    BYTE ShowMessage;                   /*Show Message ����*/
    BYTE SendEmail;                     /*Send Email ����*/
    BYTE FullScreen;                    /*FullScreen ����*/
	BYTE CheckType;                   /*�������*/
    BYTE IsSpot;             //�ĳ��ж��Ƿ���spotAudio
    BYTE reserve[9];
}RSNet_SoleVideoDiagnostics_t;

/* �߼�����-��Ʒ������ʧ*/
typedef struct{
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;          /*0-�رգ�1-��*/
    BYTE BuzzerMooTime;      /*���������У�����ʱ��:0��10��20��40��60s*/
    BYTE AlarmOutTime;       /*������������ʱ��:0��10��20��40��60s*/
    BYTE RecordDelayTime;    /*¼����ʱ����ʱʱ��:0��10��20��40��60s*/
    BYTE AlarmOutManager[4];   /*ֻ��һ����������ģ���AlarmOutManager[0]����*/
    UINT RecordChannel;
    BYTE Record;               /*Record channel switch*/
    BYTE ShowMessage;          /*Show Message ����*/
    BYTE SendEmail;            /*Send Email ����*/
    BYTE FullScreen;           /*FullScreen ����*/

    BYTE RuleSwitch;        /*ÿ��ͨ����һ���ֽڱ�ʾ���8������0-�رգ�1-ʹ��*/
    BYTE RuleType;          /*DVRר��: ÿ��ͨ����һ���ֽڱ�ʾ���8��-�������ͣ�0-������1-��ʧ*/
    BYTE RuleScene;         /*ÿ��ͨ����һ���ֽڱ�ʾ���8��-�������ͣ�0-���ڳ�����1-����*/
    BYTE Sensitive;			/*�㷨������0-9*/
    BYTE NewRuleType;       /*IPCר�ã�ÿ��ͨ����һ���ֽڱ�ʾ���4��-�������ͣ�2bit��ʾһ�����ͣ�0-���������1-��ⶪʧ��2-ͬʱ��ⶪʧ������*/ //2015.11.12	
    S8   AIChannel;         /*��ǰʹ������ͨ����ģ��ͨ���ǵڼ�ͨ��,-1:û��ģ��ͨ��ʹ�����ܹ���*/
	BYTE IsSpot;             //�ĳ��ж��Ƿ���spot
    BYTE DrawLineEnable;/*�Ƿ���Ԥ������ 20170313 add*/
    BYTE RuleRectEnable[8];  /*IPC 2.0����ʹ�ã�ÿͨ�������8������ÿ���������4����.ÿһλ����һ�������ʹ�ܣ�Ŀǰֻ��ǰ��λ*/
    Net_Line_S RuleRect[32];	/*ÿ���������4����,��ÿͨ�������8��4��32������*/
	UINT RecordChannel_EX[8];
	/*ȡbitλ:3��ʾһ��ͨ�����3���������,ÿ���������봥�������������
	32*8= 256·���κ�ͨ���������*/
	BYTE AlarmOutManagerEx[3][32];
	BYTE FtpLink;
	BYTE sendToFTP;/*���ͽ�ͼ��FTP��0����ʹ�ܣ�1��ʹ��*/
	BYTE IVALines;/*Ԥ���ͻط��Ƿ���Ҫ���ߣ�0-�����ߣ�1-����*/
	BYTE PushSwitch;
	BYTE DetonateTime;		/*����ʱ�䣬��ѡ10s��20s��30s��40s��50s��60s��70s��80s��90s*/
	BYTE FtpVideoLink;         /*FTP¼������ ����*/
	BYTE CloudPicUpload; 
	BYTE CloudVideoUpload; /* �ƴ洢��Ƶ�ϴ� */
}RSNet_SoleGoodsLostLegacy_t;

/* �߼�����-����/����/����ͳ�� 2016.03.09*/
typedef struct {
	UINT StructSize;
	UINT ChannelMask;

    BYTE ChnSwitch;          	/*0-�رգ�1-��*/
    BYTE BuzzerMooTime;      	/*���������У�����ʱ��:0��10��20��40��60s*/
    BYTE AlarmOutTime;       	/*������������ʱ��:0��10��20��40��60s*/
    BYTE RecordDelayTime;    	/*¼����ʱ����ʱʱ��:0��10��20��40��60s*/
    BYTE AlarmOutManager[4]; 	/*ֻ��һ����������ģ���AlarmOutManager[0]����*/
    UINT RecordChannel;
    BYTE Record;                /*Record channel switch*/
    BYTE ShowMessage;           /*Show Message ����*/
    BYTE SendEmail;             /*Send Email ����*/
    BYTE FullScreen;            /*FullScreen ����*/

    BYTE RuleSwitch;            /*ÿ��ͨ����һ���ֽڱ�ʾ���8������0-�رգ�1-ʹ��*/					  	
    BYTE RuleScene;	   		    /*�������ͣ�0-���ڳ�����1-����
								            *���������ѷ���������ʹ�ø��ֶ���ΪDetection Range
								           */
    BYTE Sensitive;	            /*�㷨������0-3,�������ѧϰ�������˳�����0-100�����ȣ�Ĭ��50*/
    BYTE RuleType;       		/*ÿ��ͨ����һ���ֽڱ�ʾ���8��-�������ͣ�
    						  		0-����������-����ģʽ������ͳ��-˫��1-����ģʽ
									��������������0��ȫ��ģʽ��1���Զ���ģʽ*/	
	BYTE RuleTypeAdd;       	/*���ƹ���ͳ�Ƶķ���0-a->b 1-b->a*/	
    BYTE DrawLineEnable;/*�Ƿ���Ԥ������ 20170313 add*/
	BYTE sendToFTP;/*���ͽ�ͼ��FTP��0����ʹ�ܣ�1��ʹ��*/
	BYTE FtpLink;
    Net_Line_S RuleLine[32];	/*ÿͨ�������64��������,��32���ߣ�ÿ���������1������/1���ߣ�
                              			����ǰ�����ֻʹ�õ�1���ߣ�������ı��Σ���ʹ�õ�1�͵�2����
										*******************************************************************
										20181024 add
										�����4��������ʹ��0-15���ı��Σ�
										16-31��������ͳ���ߣ���Ϊ4��������16-19Ϊ����1,20-23Ϊ����2......��һ��Net_Line_S�����㣬����Ϊһ���ߣ�
										��ˣ�16,20,24,28����ŷֱ��Ǹ�����ĵ�һ���ߣ�
										*******************************************************************
										*/
	UINT RecordChannel_EX[8];
	/*ȡbitλ:3��ʾһ��ͨ�����3���������,ÿ���������봥�������������
	32*8= 256·���κ�ͨ���������*/
	BYTE AlarmOutManagerEx[3][32];
	BYTE IVALines;/*Ԥ���ͻط��Ƿ���Ҫ���ߣ�0-�����ߣ�1-����*/
	BYTE PushSwitch;
	BYTE FtpVideoLink;            /*FTP¼������ ����*/
	BYTE SnapInterval;		/*ץͼ���ʱ�䵥λΪs,1~255,Ĭ��2s*/
	BYTE CloudPicUpload; 
	BYTE CloudVideoUpload; /* �ƴ洢��Ƶ�ϴ� */	
	BYTE SnapModel;			/*ץ��ģʽ��0:�Զ�ģʽ��1:����ģʽ��2.����ģʽ��3.�Զ���ģʽ*/
	BYTE FaceType;		
	BYTE RollRange;			/*�Զ���ģʽ�£�������ת�Ƕ�,��Χ0~180��Ĭ��180*/
	BYTE PitchRange;			/*�Զ���ģʽ�£����������Ƕ�,��Χ0~180��Ĭ��180*/
	BYTE YawRange;			/*�Զ���ģʽ�£����������Ƕ�,��Χ0~180��Ĭ��180*/
	BYTE BlurStage;			/*�Զ���ģʽ�£�����ģ���̶�, ��Χ0~100, Ĭ��Ϊ100*/
	WORD MinPixel;         /*���������С���أ� ��Χ32-1080��Ĭ��64*/
	BYTE RuleKind;        /*������ⷽʽ��0������1������*/
	BYTE SnapNum;			/*ץͼͼƬ���� 1~3��*/
	BYTE DetectType;		/*������ͣ���λ�жϣ�0�����ˣ�1������������λδ��*/
	BYTE MotionDet;			/*�Ƿ������˶�����״̬��0-��ֹ���ģʽ��1-�˶����ģʽ*/
	BYTE reserved[6];
}RSNet_SoleIntHumanFace_t;/*IPC ר��*/

/* �߼�����-���ܹ��� 2016.03.09*/
/*����ģ��Ŀǰ��: 1)PID 2)LCD 3)SOD 4)HD 5)FD 6)PCC�������32�����ܣ���λ���䣬��0��31λ*/
typedef struct {
	UINT StructSize;          /*����IE��֤���ݴ�С*/
	UINT ChannelMask;         /*ͨ������*/

    UINT FunSwitchDisplay;    /*���ܿ����Ƿ��п� 0-�رգ�1-��*/
	UINT RecordDisplay;		  /*¼�񿪹��Ƿ��п� 0-�رգ�1-��*/

	UINT EmailDisplay;		  /*�ʼ������Ƿ��п� 0-�رգ�1-��*/
	UINT AlarmOutDisplay;	  /*��������Ƿ��п� 0-�رգ�1-��*/

	UINT AlramDisplay;        /*ʵʱ�Ƿ��б��� 0-�У�1-��*/         
	UINT InCountDisplay;	  /*CC �����ʾ������*/

	UINT OutCountDisplay;	  /*CC �����ʾ����ȥ*/

	BYTE SceneDisplay;	      /*��ǰ���� 0-���ڣ�1-����*/
    BYTE CloudVideoIsUsed;	/* ��ǰͨ���Ƿ���ʹ������Ƶ�ϴ� */
    BYTE reserved[250];
}RSNet_SoleIntManage_t;/*IPC ר��*/

/*********************************************************************
 * Description: Intelligent Param Adapter 
 * 8 Bytes Alignment�� 9*32 = 288 bytes 
 * end
 * ******************************************************************/

/* ͨ��Զ������board id, key id */
typedef struct 
{
	UINT StructSize;

	UINT KeyID;
	BYTE BoardID[16];
    BYTE DeviceType;//�豸�ͺ�,��Զ�˴��ݵ�ö��ֵ����(DVR OWL 20150129)
    BYTE reserved[7];
}RSNet_IDset_t;

/*********************************************************************
 * kegurd��������FTP������Ҫ���Ȳ�ѯ��ǰ�Ƿ�����fw����
 * ����ftp���������Ƿ��п������ļ���
 * #define MsgFtpUpgradeSearchFile    324  //get ftp server newversion info 
*********************************************************************/
//ftp server upgradfile version info
typedef struct
{
	int  NewVersion;	//0:no ,1: yes��-1��errno
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

		BYTE BitRateMode;    //stream mode:0-Ԥ�� 1-�Զ���
		BYTE Bitrate;        //���� ����Ӧ������С�μ�RS_MainBitrate_e
		WORD CustomBitrate;   // �Զ���������ֵ����Ԥ������ֵbitrate�޷�����ǰ��IPCʱʹ�� 

		BYTE BitrateType; /* 0 :������1:������2: ������ 3: QVBR*/
		BYTE VideoQuality; /* ͼ������0: ���1:����2:��3:��4:����5:���*/
		BYTE AudioSwitch;    //ǰ���豸����Ƶ���Ƿ����� 0: close 1: open
		BYTE Num;/*֧�ֵķֱ��ʸ���,���ѡ��8��*/

		BYTE IFrameInterval; /* I ֡�����Χ��1-100  �� */
		BYTE Fps;      
		BYTE ResolutionsetIndex; /* whice one resolution index has been choose to set */
		BYTE HaveAudio;/*ǰ���豸�Ƿ�֧����Ƶ���룬0��֧�֣�1֧��*/
		RSNetNew_ResolutionRateRange_t Range[8];
		BYTE VideoSwitch; /* ��������Ƶ�����Ƿ��0, ��, 1,�� */
		BYTE AudioEncType;
		BYTE VideoEncType;
		BYTE ProfileLevel;/*���뼶��0-2��0��Baseline��1��Main Profile��2��High Profile*/
		BYTE UsedEncType; /*���õı�������0-ͬʱ֧��H264��H265,1-ֻ֧��H264��ʹ��IPC_Dev_Type_eö������ʾ*/

		BYTE AMRSwitch; /*AMR ����뿪��(DENAVO�ͻ�ר��). 0:disable, 1:enable*/
		BYTE SoleResolutionMode;
		//BYTE UseJPEG;	   /*�Ƿ�ʹ��JPEG���룬0-��ʹ�ã�1-ʹ��----2170208update,ʹ��λ����ʾ*/
		BYTE UseJPEG:1;	   /*�Ƿ�ʹ��JPEG���룬0-��ʹ�ã�1-ʹ��*/
		BYTE HideEncType:1;/*�Ƿ���ʾ�����ʽ, 0:��ʾ��1������ʾ*/
		BYTE unused:6;
		BYTE CameraMaxRes;/*��¼ǹ�����֧�ֵķֱ������ͣ�����ֵ����DEV_RES_E*/

		BYTE reserver[7];
		RSNetNew_ResolutionRateRange_t Range2[8];
	}RSNetNew_SoleStreamset_t;
#else
	typedef struct 
	{
		UINT StructSize;
		UINT ChannelMask;
	
		BYTE BitRateMode;    //stream mode:0-Ԥ�� 1-�Զ���
		BYTE Bitrate;        //���� ����Ӧ������С�μ�RS_MainBitrate_e
		WORD CustomBitrate;   // �Զ���������ֵ����Ԥ������ֵbitrate�޷�����ǰ��IPCʱʹ�� 

		BYTE BitrateType; /* 0 :������1:������2: ������ 3: QVBR*/
		BYTE VideoQuality; /* ͼ������0: ���1:����2:��3:��4:����5:���*/
		BYTE AudioSwitch;    //ǰ���豸����Ƶ���Ƿ����� 0: close 1: open
		BYTE Num;/*֧�ֵķֱ��ʸ���,���ѡ��8��*/
	
		BYTE IFrameInterval; /* I ֡�����Χ��1-100  �� */
		BYTE Fps;      
		BYTE ResolutionsetIndex; /* whice one resolution index has been choose to set */
		BYTE HaveAudio;/*ǰ���豸�Ƿ�֧����Ƶ���룬0��֧�֣�1֧��*/
		RSNetNew_ResolutionRateRange_t Range[8];
		BYTE VideoSwitch; /* ��������Ƶ�����Ƿ��0, ��, 1,�� */
		BYTE AudioEncType;
		BYTE VideoEncType;
		BYTE ProfileLevel;/*���뼶��0-2��0��Baseline��1��Main Profile��2��High Profile*/
		BYTE UsedEncType; /*���õı�������0-ͬʱ֧��H264��H265,1-ֻ֧��H264��ʹ��IPC_Dev_Type_eö������ʾ*/
	
		BYTE AMRSwitch; /*AMR ����뿪��(DENAVO�ͻ�ר��). 0:disable, 1:enable*/
		BYTE SoleResolutionMode;
		//BYTE UseJPEG;	   /*�Ƿ�ʹ��JPEG���룬0-��ʹ�ã�1-ʹ��----2170208update,ʹ��λ����ʾ*/
		BYTE UseJPEG:1;	   /*�Ƿ�ʹ��JPEG���룬0-��ʹ�ã�1-ʹ��*/
		BYTE HideEncType:1;/*�Ƿ���ʾ�����ʽ, 0:��ʾ��1������ʾ*/
		BYTE unused:6;
		BYTE CameraMaxRes;/*��¼ǹ�����֧�ֵķֱ������ͣ�����ֵ����DEV_RES_E*/

		BYTE reserver[7];
	}RSNetNew_SoleStreamset_t;
#endif

typedef struct 
{
	UINT StructSize;
	UINT ChannelMask;
	
	S16 res_w;			////�ü�Դ�ֱ��ʿ�
	S16 res_h;			////�ü�Դ�ֱ��ʸ�
	RSNet_Rect_t rect;
	RSNetNew_SoleStreamset_t rsAreaStreamSet;
	BYTE areaSwitch;	////�Ƿ�������ü�
	BYTE reserver[7];
}RSNetNew_AreaStreamset_t;

/* ��ͬIPC��OSD��ʾ����,��λ��ʾ,��ӦRSNetNew_SoleLivingset_t */
typedef enum
{
    RSOSD_HideFliker = 0,	// ������˸����
    RSOSD_HideFormat,		// ����ʱ�����ڸ�ʽ
    RSOSD_HidePosition,		// ����OSDλ������
    RSOSD_hideShowName,		// �����Ƿ���ʾ����
    RSOSD_HideShowTime,		// �����Ƿ���ʾ����
    RSOSD_SupportUpper		// Сд��ĸ������ת��Ϊ��д���Զ�ˢ����ʾ
}RSOSD_DispRule_e;

/* preview  */
#define NET_STD_RES_X 704
#define NET_STD_RES_Y 576
typedef struct 
{
	UINT StructSize;
	UINT ChannelMask;
    
	/* ChannelNameͨ����λ�ã������NET_STD_RES_X * STD_RES_Y��ֵ */
	U16 ChnNamePosX; 
	U16 ChnNamePosY; 
	/* Dateʱ������λ�ã�ͬ�� */
    U16 DateTimePosX;
    U16 DateTimePosY;
	
	char   ChnName[40];        /*ͨ������*/
    BYTE ShowChnNameFlag;    /* OSD�Ƿ���ʾͨ������1-��ʾ��0-����ʾ */
    BYTE ShowDateTimeFlag;   /* OSD�Ƿ���ʾ����  ��1-��ʾ��0-����ʾ */
    BYTE TimeMode:4; /* ʱ��ģʽ��0Ϊ24Сʱ�ƣ�1Ϊ12Сʱ��*/
    BYTE DateMode:4; /* ����ģʽ:0ΪMM/DD/YYYY��1ΪYYYY-MM-DD��2ΪDD/MM/YYYY��*/
                                                            
	BYTE FlickerCtrl;  // ipc ��˸���� 0:50 Hz 1:60Hz 2 disable
    BYTE DisplayRule;   //���ݲ�ͬIPCЭ��������ʾ��ͬ������
	BYTE Covert;         /*ͨ������*/
	BYTE fgAlpha;	/* OSD ͸����[0-128] */
    BYTE RecTimeFlag;/*¼��ʱ��OSD: 1-��ʾ, 0-����ʾ (ֻ���ڻ��DVR)*/
    BYTE AHD_QESwitch;
    BYTE  NewNameFlag;//0xa5��ʾʹ���µ�ͨ����
    BYTE  ChnName2Enable;//�Ƿ�ʹ�õڶ���ͨ������
	BYTE  NewOsdLenEnable;//�Ƿ�ʹ�ð�˿���NewChName�����볤��
	BYTE  NewChNameStrlen;//��˿��ƾ���osd����
	BYTE Protocol; /*Э�����ͣ���BALTER �ͻ�ʹ��*/
    BYTE  reserve1[2];
	BYTE  NewChName[128];//

	U16 ChnNamePosX2;  /*�ڶ���ͨ������λ��*/
	U16 ChnNamePosY2; 
	U16 WaterMaskPosX; 
	U16 WaterMaskPosY;
	BYTE ShowChnNameFlag2;      /* OSD�Ƿ���ʾ�ڶ���ͨ������1-��ʾ��0-����ʾ used by 2017.7.13*/
	BYTE ShowCarNumFlag;		/*OSD�Ƿ���ʾ���ƺ�*/
	BYTE ShowGPSFlag;			/*OSD�Ƿ���ʾGPS��Ϣ*/
	BYTE ShowSpeedFlag;			/*OSD�Ƿ���ʾ����*/
	BYTE reser2[4];
	char ChnName2[40];        /*�ڶ���ͨ������used by ipc 2017.7.13*/

	//����osd��Ϣ 2018.01.16
	UINT MulitRowOsdPosX; 		/*OSD X����*/
	UINT MulitRowOsdPosY; 		/*OSD Y����*/
	char MulitRowOsdContent[11][64];/*����OSD ����*/
	BYTE ShowMulitRowOsdEnable;	/*�Ƿ�ʹ�ö���OSD*/
	BYTE ShowMulitRowOsdFlag;	/*����OSD��ʾ*/
	BYTE TypeAlignment;			/*����OSD ���뷽ʽ0:����� 1:�Ҷ��� 2:����*/
	BYTE WaterMark; /*0 : �ر� 1�� */
	BYTE FontSize; /*�����С 0:С��1:�У�2:��*/
	BYTE reser3[3];
	char MulitRowOsdContent2[9][64];/*�ͻ���չΪ20��OSD ����     2018.02.05*/

	//2018.03.22 add color
	BYTE ColorArr[4][4];/*rgba, 0:DateTimeColor, 1:ChnNameColor, 2:ChName2Color, 3:MulitRowOsdColor */
	BYTE reser4[128];
}RSNetNew_SoleLivingset_t;

/* output */

typedef struct 
{
    BYTE VideoIndex[32]; /* ÿ��ͨ�����ڵĴ��ںţ������±�Ϊͨ���ţ�ֵΪ���ں� */
    BYTE StreamType[32]; /* ÿ��ͨ��Ԥ�����������ͣ� 0-��������1-������ */

    UINT Margin[4];
    UINT AutoSEQTime; /* ��ѭʱ���� */
    BYTE PreviewMode; /* Ԥ��ģʽ��0-ϵͳԤ��ģʽ��1-�û��Զ���ģʽ */
	BYTE SplitMode;   /* ����ģʽ����UI�����������ṩ */
	BYTE CurrentPage; /* Ԥ��ͨ�������ڷ�����ʱ���ж�ҳ���ò�����¼��ǰҳ������ */
	BYTE SeletedVideo; /* ��ǰѡ�д��ڵ����� */
	BYTE IsEnlarged;   /* ��¼��ǰѡ�еĴ����Ƿ���˫����ķŴ�״̬ */
	BYTE SpotAudio;
    BYTE reserve[14];
}Net_voattr_t; // outputset �ӽṹ��

typedef struct 
{
	UINT StructSize;

	Net_voattr_t voattr[4];     /*voattr[0]-HDMI, voattr[1]-VGA, voattr[2]-VOUT, voattr[3]-VSPOT*/ 
	UINT transparency;      /*͸����*/
	BYTE IsVoutOrSpot;    /*0-Vout,1-Spot*/
	BYTE vgaresolution;   /*VGA �ֱ���*/
	BYTE initGuiDev;      /*����ʱ��Ĭ��GUI ��ʾ�豸:0-VOUT, 1-VGA ,2-AUTO*/
	BYTE ChangeResolutionFlag;/* REVERT_VGARESOLUTION:    0:�޸Ķ�, 1:�иĶ�, 2:�ѻָ�*/
	BYTE oldvgaresolution;    /*��������ǰ�ķֱ���*/
	BYTE AutoSEQFlag;     /*��¼�Ƿ���ѯ���Ա����������ϴ�״̬*/
	BYTE OutputDev;       /*����豸:0-HDMI,1-VGA,2-VOUT*/
	BYTE voice;
	BYTE EnablePreview[32];        /*Ԥ������ 0-�ر�, 1-���� */
	BYTE reserve[16];    /*�����ֽ�*/
}RSNetNew_Outputset_t;

/* KB setting */
typedef struct 
{
	UINT StructSize;

	BYTE Protocol; /*Э�����ͣ�0-Pelco-D��1-Pelco-P*/
	BYTE Baudrate; /*�����ʣ�0-1200��1-2400��2-4800��3-9600*/
	BYTE DataBit;  /*����λ��0-8��1-7��2-6��3-5*/
	BYTE StopBit;  /*ֹͣλ��0-1��1-2*/
	BYTE Check;    /*У�飬0-None��1-Odd��2-Even��3-Mark��4-Space*/
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
	S8 AppVer[24];/* ϵͳ����ʱʹ��*/
	S8 UbootVer[24];
	S8 KernelVer[24];
	S8 RootfsVer[24];
	S8 SlaveUbootVer[24];
	S8 SlaveKernelVer[24];
	S8 SlaveRootfsVer[24];
	S8 LogoVer[24];
	S8 MacAddr[24];
	S8 SerialNum[24];
	S8 SWVertion[24];/*UI ����ʾʹ��*/
	S8 IEVertion[24];
	S8 HWVertion[24];
	S8 KBVertion[24];
}RSNetNew_StateParamset_t;



#define MAX_CUSTOMPROTO_NUM 16
/* �Զ�������Э����� (NVR)*/
typedef struct
{
    UINT Port;
    BYTE Type;           /* ���� 0 RTSP */
    BYTE Transmisson ;	 /*����Э�� 0 �Զ� 1 UDP 2 RTP over RTSP*/
    BYTE reserve[2];
    BYTE SourcePath[120];/*��Դ·��*/
}Net_CustomStream_t;

/* GB28181ҳ�����ýṹ */
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

/* �Զ����������ò��� */
typedef struct
{
    UINT StructSize;
    UINT ProtocolMask; 		 //Э������
    BYTE EnableSubStream;    //�Ƿ�����������
    BYTE reserved[3];
    BYTE ProcotolName[16];   //Э������
    Net_CustomStream_t MainStream;
    Net_CustomStream_t SubStream;
}RSNetNew_SoleCustomProtocol_t;

/* ���ƽ̨Զ�̲��� */
typedef struct
{
    UINT StructSize;          //�ýṹ���С

    BYTE HostName[MaxNameLen];//Url
    UINT Port;                //�˿ں�
    BYTE AgentId[16];         //12λ����.SSJC��ͷ������12λ�ַ�
    BYTE Enabled;             //ʹ�ܿ���. 1:enable, 0:disable
    BYTE BeforeTrigger;       //��������ǰʱ��. 10 ~ 60
    BYTE AfterTrigger;        //����������ʱ��. 10 ~ 60
    BYTE ImgInterval;         //ͼƬʱ����. 1 ~ 3        
    BYTE reserved[8];
}RSNet_SGPlatform_t;
typedef struct
{
    UINT StructSize;          //�ýṹ���С
    UINT ChannelMask;         //ͨ������
    BYTE UploadTime1[4];      //��ʱ�ϴ�ʱ���1
    BYTE UploadTime2[4];      //��ʱ�ϴ�ʱ���2
    BYTE Time1Enable;         //ʱ���1����
    BYTE Time2Enable;         //ʱ���2����
    BYTE reserved[6];
}RSNet_SoleSGPlat_t;

typedef struct
{
	BYTE 	RoiIndex;/*ROI���������,ͬ��Ҳ��ROI��������ȼ�������Խ�����ȼ�Խ��*/
	BYTE    RoiSwitch;/*��ROI�����Ƿ�ʹ��*/
	BYTE    IsAbsQp;/*�Ƿ�ʹ�þ���ͼ��������0:ʹ�����������1:ʹ�þ�������*/
	BYTE    ROILevel;/*ROIֵ�Ĵ�С��1-6,ֵԽ��ͼ������Խ��*/
	BYTE 	ROIBgFrameRate; /*��ROI�����֡�ʣ���0�����֡��֮��*/
	BYTE    reserve[3];
	UINT    Rect_x;/*ROI���ڵľ���������Ϣ*/
	UINT    Rect_y;/*ROI���ڵľ���������Ϣ*/
	UINT    Rect_w;/*ROI���ڵľ���������Ϣ*/
	UINT    Rect_h;/*ROI���ڵľ���������Ϣ*/
}RSNet_Roi_t;
typedef struct
{
    UINT    StructSize;          //�ýṹ���С
	UINT    StreamType;          /*1:main 2:sub 4:mobile*/
	RSNet_Roi_t roi[8];
	BYTE	Maxfps;
	BYTE    reserve[7];
}RSNet_SoleRoiParam_t;


typedef struct 
{
    UINT    StructSize;          //�ýṹ���С
	UINT    ChannelMask; //ͨ������
	BYTE    ODSwitch;          /*��ͷ�ڵ�����0-�رգ�1-��*/
	BYTE    Sensitivity;       /*6���ȼ�:6-�ߣ�5-�ϸ�..........  1-��*/
	BYTE    EmailLink;         /*�ʼ����� ����*/
	BYTE    FtpLink;			/*FTP���� ����*/
	BYTE    Alarmout;         /*���� ����*/
	BYTE    LatchTime;			/*�ӳ�ʱ��*/
	BYTE    sendToFTP;/*���ͽ�ͼ��FTP��0����ʹ�ܣ�1��ʹ��*/
	BYTE    RecordDelayTime;     /*post recording*/ /*¼����ʱ����ʱʱ��:10s,30s,1min,2min,5mins*/
	BYTE    ShowMessage;      /*Show Message ����*/
	BYTE    FullScreen;       /*ȫ�� ����*/
	BYTE    RecordSwitch;      /*Record  switch*/
	BYTE 	BuzzerMooTime;      /*���������У�����ʱ��:0��10��20��40��60s*/
	BYTE	res[4];

	UINT    RecordChannel[8];
	BYTE    AlarmOutManager[MAX_ALARMOUT_NUM];
	BYTE    res1;
	BYTE    FtpVideoLink;	/*FTP¼������ ����*/
	BYTE    CloudPicUpload; /* �ƴ洢��Ƶ�ϴ� */
	BYTE    CloudVideoUpload;
	BYTE    reserve[12];
}RSNet_SoleODParam_t;

/* Lorex IPC ���߲��� */
typedef struct
{
    UINT  StructSize;     //�ýṹ���С
    UINT  ChannelMask;    //ͨ������
    BYTE  SubstreamBrite; //����������
    BYTE  Bright;         //����
    BYTE  ChannelEnable;  //ͨ������
    BYTE  MotionEnable;   //motion����
    BYTE  TVSystem;       /*0-PAL; 1-NTSC*/
    BYTE  reserve[3];
}RSNet_SoleIpcWireless_t;

/* Kguard (DVR) P2P ID Used ShangYun */
typedef struct
{
BYTE QrcordWhetherFill;// Sensor Qrcord�Ƿ�����ǣ�1����䣬 0:Ϊ�����
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

/*****������Ŀ˽�в��� 2016.05.25*****start*/

typedef struct Eplateform_s
{	
	UINT StructSize;			//�ṹ���С

	char device_name[128];		// �豸����
	char device_ip[32];			// �豸IP
	char passwd[64];			// �û�����
	char device_id[32];			// �豸����/sip user
	char channel_id[64][32]; 	// �豸ͨ������ID
	char platform_ip[16];		// ����ƽ̨IP
	char platform_id[32];		// ����ƽ̨����ID
	char scenes_id[32];			// ����ƽ̨��������ID
	int  sip_port;				// ����ƽ̨SIP �˿�
	int  rtsp_port;				// ����ƽ̨RTSP �طŶ˿�

	BYTE expire;				//����ʱ�䣬 0~120
	BYTE reserve;			//Ԥ��λ
	short remotePort;			//Զ�̶˿�
}Eplateform_t;

/*************������Ŀ˽�в���**********end*/

typedef struct
{
    BYTE schedule[8][48];      //�ƻ���
}SirenSetup_t;
typedef struct
{    
    WORD DurationTime;     //������������ʱ��: 0��5000
    BYTE RecDelayTime;     //¼����ʱ����ʱʱ��:0, 10, 20, 40, 60s
    BYTE SirenEnable;      //Siren ����
    UINT RecChannel;       //¼��ͨ��,��λ��ʾͨ����
    BYTE ShowMessage;      //Show Message ����
    BYTE SendEmail;        //Send Email ����
    BYTE Record;           //ͨ��¼�񿪹�
    BYTE PushEnable;       //���Ϳ���
    UINT SirenIdSel;       //��ǰѡ��Ĵ�����ID
    
    BYTE SendFTP;          //Send FTP ����
    BYTE IlluminationRing; //���ջ�0, ��ʹ��, 1. ʹ��
    BYTE AudioAlert;       //��Ƶ����0, ��ʹ��, 1. ʹ��
    BYTE AudioSelect;      //��������ѡ�� 0, Doorbell 1.Ringtone, 2.Siren
    BYTE AlarmDurationTime; //��������ʱ��0-10s/1-30s/2-60s
    BYTE reserved1[3];  
}SensorActionSetup_t;

typedef struct
{
    UINT StructSize;
    BYTE SensorName[24];//������������
    BYTE SensorState; //��������״̬��ʾ0: connnected, 1: Disconnected, 2: Error
    BYTE SensorOutTime;    //Sensor�����ӳ�ʱ��,�ӳ�ʱ��Ϊ10, 20, 40, 60s
    BYTE SensorNo;		   //Sensor ���
    BYTE SensorRuleEnable;  //Sensor �������Ϳ���
    UINT NodeId;      	   //��������ID
    BYTE AlarmType;        //�豸����0-Door, 1-PIR, 2-Smoke Alarm,
    BYTE SensorNum;        //�����豸�ܸ���
    BYTE reserved[2];
    union
    {
        SirenSetup_t Siren;
        SensorActionSetup_t  SensorAction;
    };
}RSNet_SoleKGSensorParam_t;

/* ���߶Ͽ��澯ҳ������ṹ */
typedef struct {
	UINT StructSize; /* �ýṹ���С*/
	UINT ChannelMask; 	
	BYTE ChnSwitch;/*�Ƿ��������߶Ͽ��澯 0. �����ã�1. ����*/
	BYTE SendEmail;
	BYTE BuzzerMooTime;
	BYTE Reservel[5];
	UINT RecordChannel;
	BYTE RecordDelayTime; /*¼����ʱʱ��*/
	BYTE Record; /* ����¼�����ܿ���  0. �����ã�1. ����*/
	BYTE AlarmOut;
	BYTE IPPushableSwitch;
	BYTE IPPushableAlarmOut;
	BYTE Reservel2[39];
}RSNet_NetBreakSet_t;

typedef struct /* �ֻ�APP ��Ϣ */
{
	UINT StructSize; /* �ýṹ���С*/
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

/* ���DVRģ��ͨ��ҳ����Ϣ */
typedef struct
{
    UINT StructSize; /*�ýṹ���С*/
	UINT ChannelMask;/*ͨ������*/    
    BYTE ChnName[20];/*ͨ������*/
    BYTE Status;     /*ͨ��ʹ��״̬. 0 : close; 1 : open*/
    BYTE reserved[2];
	BYTE NewNameFlag; //1��ʾʹ��ExtendChnNameMask,0��ʾʹ��ChnName
	BYTE ExtendChnNameMask[64];/*ͨ��������չ*/
}RSNet_SoleAnalogCam_t;

/* ���DVRץͼ���ò����ṹ */
typedef struct
{
	UINT StructSize;     /*�ýṹ���С*/
	UINT ChannelMask;    /*ͨ������*/
	BYTE ChnEnable;      /*ͨ������ 0:close, 1:open*/
	BYTE ManualEnable;   /*�ֶ�ץͼ���� 0:close, 1:open*/
	BYTE StreamType;     /*�������� 0:������, 1:������*/
	BYTE NormalCapInterv;/*��ͨץͼʱ����*/
	BYTE AlarmCapInterv; /*����ץͼʱ����*/
	BYTE reserved;
	BYTE AlarmCapEncType;/*alarm����ץͼ�ֱ���, 0-960,1-720,2-1080*/
	BYTE AlarmCapQuality;/*alarm����ץͼ����, 0-60,1-75,2-90*/
	RSNetNew_ResolutionRateRange_t BigRange[3];/*�������б�*/
	RSNetNew_ResolutionRateRange_t LittleRange[3];/*С�����б�*/
	BYTE reser[256];
}RSNet_SoleCaptureSet_t;

/* ���DVRץͼ�ƻ��� */
typedef struct
{
    UINT StructSize; 	//�ýṹ���С
    UINT ChannelMask; 	//ͨ������

    /* bit 1ΪNormalץͼ, bit 2 ΪMotionץͼ, bit 3 ΪIOץͼ
     * ��Ӧ��bitλΪ1��ʾ���ã�Ϊ0��ʾ����
     */
    BYTE HalfHour[8][48]; //7days, 48 halfhours    
}RSNet_SoleCapSchedule_t;

/* 0ͨ������ģʽ */
typedef enum 
{
    ZeroCh_One,
    ZeroCh_Four,
    ZeroCh_Six,
    ZeroCh_Eight,
    ZeroCh_Nine,
    ZeroCh_Sixteen
}ZeroChSplitMode_e;

/* 0 ͨ��¼������ */
typedef struct 
{
    UINT  StructSize;   /*�ýṹ���С*/
    BYTE  ChnName[64];  /*ͨ������*/
    BYTE  Position;     /*0-���ϣ�1-���£�2-���ϣ�3-����*/
    BYTE  fps; 	        /*֡��: 1~25/30֡*/
    BYTE  resolution;   /*�ֱ��ʲμ�RESOLUTION_E */
    BYTE  zeroChnSwitch;/* 0 ͨ������ : 1-��,0-�� */
    BYTE  bitrate;      /*¼������32 ~8192kbps : ��Ӧ����0~27*/
    BYTE  SplitMode;    /* ����ģʽ,��Ӧ ZeroChSplitMode_e */    
    BYTE  DwellTime;    /*��ѭʱ��. 0-no switch, 1-5s, 2-10s, 3-20s,
                          4-60s, 5-120s, 6-300s*/
    BYTE  reserved[5];
    BYTE  ChnList[256];  /*ͨ�������б�, 0xff-������ͨ��,ʵ��ͨ���Ŵ�0��ʼ
                                           ��Ч�����±�< ���ͨ����*/
    BYTE  reserved2[16];
}RSNet_ZeroChnSet_t;

/* ͨ��Զ������ϵͳ�ؼ����� */
typedef struct 
{
	UINT StructSize;

	UINT ParamTypes;     /*Զ�����õĲ�������,�ɰ�˾���*/
	UINT reserve;
	UINT AngleRotation; /*IPCͼ����ת���� 0-����ת��1-˳ʱ����ת90�ȣ�2-˳ʱ����ת180�ȣ� 3-˳ʱ����ת270��*/

	BYTE MainBoardName[16]; /*�����ͺ� RS-DM-XXXX*/
	BYTE Password[24]; /*���ITEX�ͻ���ÿһ̨��������Ψһ��admin����*/
	BYTE SerialNumber[16]; /*���ZIP�ͻ���ÿһ̨��������Ψһ�����к�*/
	BYTE ProductType[64];	/*��Ʒ�ͺ�	*/
	BYTE DeviceType[32];	/*�豸�ͺ�	*/
	BYTE DeviceName[32];    /*�豸����	*/
	BYTE CustomType[32];	/*�ͻ�����	*/
	ULONGLONG FunctionCode;	/*��Ʒ������	*/
	BYTE SupportFourHddDisk;/*֧��4��Ӳ��*/
	BYTE languageConfig;/*�����������ѡ��*/
	BYTE language;/*�����������ѡ��*/
	BYTE SerialNumberEX[32]; /*���кţ���ʱ��Lorex�ͻ�����*/
	BYTE ProductCode; /*���ݴ˲�������ͬһ����ͬ���豸���ƻ�����������APP����*/
	BYTE Videoformat; /*��Ƶ��ʽ �ο�TVSYSTEM_T*/
	BYTE reservedl[1];
	BYTE EnableEsata;
	BYTE EnableHddGroup;
	BYTE AlarmOutputNum;
	BYTE AlarmInputNum;
	BYTE AudioNum;
	BYTE reserved;
	BYTE PoePowerFlag;  /*����POE��������, 1:���� 0:������*/
	BYTE res[3];
	WORD PoePower;      /*POE����*/
	BYTE KeyParams[742];/*�ؼ�������,�ɰ�˾���*/
}RSNet_KeyBackupSet_t;

/* ���DVRͨ����Ϣ���� */
typedef struct
{
    UINT StructSize;    /*�ýṹ���С*/
	UINT ChannelMask;   /*ͨ������*/
    
    BYTE ChnStatus;     /*ͨ��״̬.*/
    BYTE ConfigStatus;  /*��λ��ʾ,bit1:�ƶ����״̬, bit2:��Ƶ�ڵ�״̬.0-disable, 1-enable*/
    BYTE SupportTypes;  /*֧�ֵ���������.��λ��ʾ,bit1:main, bit2:sub, bit3:moile
                          ,bit4~bit8֮����, 0-disable, 1-enable*/
    BYTE reserved;
    BYTE ChnAlias[36];  /*ͨ������*/
    
    WORD ResWidth[4];   /*�ֱ��ʿ�,��������Ϊmain, sub, mobile*/
    WORD ResHeight[4];  /*�ֱ��ʸ�,��������Ϊmain, sub, mobile*/        
    UINT Bitrate[4];    /*������,��������Ϊmain, sub, mobile*/
    BYTE Fps[4];        /*��Ƶ֡��,��������Ϊmain, sub, mobile*/
    BYTE reserved1[11];
	BYTE NewChnAliasFlag; //1��ʾʹ��ExtendChnNameMask,0��ʾʹ��ChnAlias
	BYTE ExtendChnAliasMask[64];/*ͨ��������չ*/
}RSNet_SoleChnInfo_t;

/* ���DVR¼����Ϣ���� */
typedef struct
{
    UINT StructSize;    /*�ýṹ���С*/
	UINT ChannelMask;   /*ͨ������*/
    
    BYTE RecStatus;     /*¼��״̬*/
    BYTE RecType;       /*¼������*/
    BYTE Fps;           /*��Ƶ֡��*/
    BYTE reserved;
    UINT Bitrate;       /*������*/
    WORD ResWidth;      /*�ֱ��ʿ�*/
    WORD ResHeight;     /*�ֱ��ʸ�*/
	BYTE RecStreamMode;
	BYTE RecordSwitch;
    BYTE reserved1[10];
}RSNet_SoleRecInfo_t;

typedef struct {
	UINT StructSize; /* �ýṹ���С*/
	UINT ChannelMask; /* ͨ������*/

	/* event */

	BYTE WirelessAlarmSensor; /*�ⲿsensor ���� ʹ��0, ��ʹ��, 1. ʹ��*/

	/* actions */
	BYTE Record; 			  /*  ¼������ʹ��0, ��ʹ��, 1. ʹ�� */
	BYTE RecordDelayTime;/* ¼����ʱʱ��0-5s , 1-10s , 2-20s , 3-30s  */
	BYTE SendEmail; /*  SendEmail ����ʹ��0, ��ʹ��, 1. ʹ�� */
	BYTE FtpLink;/*FTP ����ʹ��0, ��ʹ��, 1. ʹ��*/
	BYTE PushSwitch;   		/*��������ʹ��0, ��ʹ��, 1. ʹ��*/

	/* away */
	BYTE IlluminationRing; /* ���ջ�0, ��ʹ��, 1. ʹ��   */
	BYTE AudioAlert; /* ��Ƶ����0, ��ʹ��, 1. ʹ�� */
	BYTE AudioSelect; /* ��������ѡ�� 0, Doorbell 1.Ringtone, 2.Siren */
	BYTE AlarmDurationTime; /* ��������ʱ��0-10s/1-30s/2-60s */

	BYTE RecordTime; /* ¼��ʱ�� 0-5s/1-10s/2-20s /3-30s */

	BYTE SensorOutTime;    //Sensor�����ӳ�ʱ��,�ӳ�ʱ��Ϊ0, 10, 20, 40, 60s

	BYTE Reservel[36];

}RSNet_SoleSensorSet_t;

typedef struct 
{
	BYTE mount_mode;
	BYTE show_mode;
	BYTE Reservel[2];
	float init_angle; //������⣬��ʼ�Ƕ�
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

/*������ҳ������*/
typedef struct{
    UINT StructSize;    		/*�ýṹ���С*/	
	
	BYTE  IPAddr[4];   			/*IP��ַ*/
	BYTE  NetMask[4];  			/*��������*/
	BYTE  GateWay[4];  			/*����*/
	BYTE  TransmissionMode[16]; /*������룬0-��ͨ*/	
	BYTE  SwitchMode;	 		/*������ģʽ 0-�Զ� 1-�ֶ�*/
	BYTE  Reservel[15];			/*�����ֽڲ��ֽڶ���*/
}RSNet_SwitchSet_t;

/* Sensor Controlҳ������ṹ */
typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	BYTE SensorType;  /*Sensor����(ֻ��,�û������޸�)*/
	BYTE ChnSwitch; /*�Ƿ�����Sensor<RS_Close, RS_Open>*/
	BYTE SendEmail; /*Send Email ����<RS_Close, RS_Open>*/
	BYTE BuzzerMooTime; /*����������ʱ��*/
	UINT RecordChannel; /*Record Channel, ����ͨ��¼�񣬰�λ��¼*/
	BYTE SirenTime; /*������ʱ��*/
	BYTE RecordDelayTime; /*¼����ʱʱ��*/
	BYTE Record; /*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE ShowMessage; /*Show Message <RS_Close, RS_Open>����*/
	BYTE FullScreen; /*FullScreen ���� ����ȫ��<RS_Close, RS_Open>*/
	BYTE PushSwitch;    /*�Ƿ���Sensor������������, 0: close; 1: open.*/
	BYTE Reservel[2];
	UINT RecordChannel_EX[8];
}RSNet_SoleSensorCtrlSet_t;

typedef struct 
{
	UINT  structsize;    //�ṹ���С
	UINT  channel;		//ͨ����
	BYTE  AFMode;		//AFģʽ��3-SEMI / 2-AUTO / 1-MANUAL / 0-OFF*/
	BYTE PowerMode;   //ͨ��ģʽ��2-WIDE /1-SAVE POSI / 0-OFF
	BYTE TDNAFSwitch; //ģʽ�л���0-OFF-����-���� /1-ON-����-����
	BYTE LensInitSwitch;//��ͷ��ʼ�����أ����³�ʼ������ѧ�ͻ�ȡ��ѧ��0-OFF 1-ON
	BYTE Reserved[20];
}RSNet_IPCAutoFocusInfo_t;

typedef struct _newcloudstorage_t
{
	UINT  structsize;    //�ṹ���С
	BYTE CloudType;       /*�ƴ洢����DropBox ---0  */

	BYTE Dropboxtoken[128];
	BYTE cloudEnable;
	BYTE HttpsEnable;
	BYTE SupportVideo;			/* �Ƿ�֧����Ƶ�ϴ����� */	
	BYTE MaxChnRecNum;			/* ���¼��ͨ���� */	
	BYTE CloudOverwrite;		/*�Զ����ǹ���¼������ʶ��0-�رգ�1-auto,2..1-3-5-7-14-30-90days */
	BYTE CloudStatus;			/* �ƴ洢��״̬ 0.����, 1.�ռ���, 2.δ����, 3.������� */
	BYTE IntervalTime;			/*��Ƶ�ϴ����*/
    BYTE VideoType;			    /* ��Ƶ��ʽ, ��ӦRS_VIDEO_TYPE_E */
	BYTE reserve[23];
	UINT ChnRecordEnable[8];		 /* ¼��ͨ���Ƿ���¼�� */

}RSNet_NewCloudStorage_t;

typedef struct _clodusole_t
{
	UINT  structsize;    //�ṹ���С
	UINT  ChannelMask[8]; 	//ͨ������

	BYTE DriveName[64];   /*�ϴ�Ŀ¼*/
	BYTE MotionEnable;
	
	BYTE VideoBKFormat;	/* ��Ƶ��������,ֵ��ӦRS_VIDEO_BACKUP_FORMAT_E */
	BYTE StreamType;	/* ��Ƶ������������, ��ӦSTREAM_TYPE_E */
	BYTE RecordTime; 	/* ¼��ʱ��0:10s, 1:20s, 2:30s, 3:60s */
	
	BYTE MotionRecordEnable; /* ¼��motion����ʹ�� */
	BYTE IoAlamRecordEnable; /* ¼��IO����ʹ�� */
	BYTE PirRecordEnable;    /* ¼��PIR����ʹ�� */
	BYTE IntelRecordEnable;  /* ¼�����ܷ�������ʹ�� */
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
    UINT StructSize;     /*�ýṹ���С*/
    UINT UseMask[4];      /*��OutputDevFlag�ֶο�ʼÿ�������Ƿ���ʾ bit0��ʾOutputDevFlag */
    UINT ResolutionMask[4]; /*FB_RESOLUTION_E, ����bit��1��ʾ��ʾ*/
    UINT SplitModeMask[4]; /*��ѭ����ģʽ����: ��ӦSeqSplitMode, bit��1��ʾ��ʾ */
    UINT OutputDevFlag;   /*����豸����:bit0-HDMI,bit1-VGA/VGASOPT, bit2-VOUT*/
    UINT AutoSEQTime[4];  /* ��ѭʱ���� 5~300*/
    BYTE SeqSplitMode[4]; /* ��ѭ����ģʽ0~20 ��Ӧ�ı�:" 1,4,6,8,9,10,10-1,12,13,13-1,14,16,17,19,20,22,25,32,36,42,49 " */
    BYTE resolution[4];   /*FB_RESOLUTION_E*/
    BYTE transparency[4]; /*͸���� 0~128*/
	BYTE HDMIOverscan;	  /*��ɨ��*/
	BYTE HideNCD;
	BYTE SpotOutSplitModeMode[2];/*0-dynamic 1-static*/
	BYTE IsStaticMode[4]; /*0-dynamic, 1-static -------->> View SetUp��UI�����Ӧ�ģ�*/
	BYTE IsEnFullScreen[4];/*0-Disable, 1-Enable ----->> FULL Screen��UI�����Ӧ�ģ�*/
	UINT SpotPollFlag[8]; /*��¼�Ƿ�SPOT������ÿλ���һ��ͨ�� ------>> Dynamicģʽ�µ�Select Cameras��UI�����Ӧ�ģ�*/
	BYTE VideoIndex[4][256];/*ÿ�����ڶ�Ӧ������ͨ���ţ���������Ϊ���ںţ�����Ԫ��Ϊͨ����------>> Staticģʽ�µ�Select Cameras��UI�����Ӧ�ģ�*/ 
	UINT SpotOutSplitModeMask[2];/*0-dynamic 1-static*/
	BYTE IsSpot;   /*SPOT-OUT��ʹ�ܿ���*/
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
	char mac[32];   //mac��ַ
	char ssid[32];  //·��AP ����
	char psw[32];   //·������
}RSNet_SwannRouterMacSSIDPSW_t;


typedef struct 
{   
	UINT  StructSize;   //�ṹ���С
	UINT  ChannelMask; 	//ͨ������
    RSNet_SwannRepeat_t  Sr[5];
    RSNet_SwannRepeat_t  Sc[3];
	RSNet_SwannRouterMacSSIDPSW_t RouterInfo;
	UINT  signalIntensity;
	BYTE  reserve[164];
}RSNet_SoleSwannIpcRepeat_t;

typedef struct 
{     
	UINT  StructSize;     //�ṹ���С
    BYTE  ssid[32];      //·������   
	BYTE  pskValue[32]; //·������
	BYTE  security[48];  //���ܷ�ʽ
	BYTE  reserve[84];
}RSNet_SwannRouterRepeat_t;


typedef struct 
{     
	UINT  StructSize;     //�ṹ���С
    BYTE  ssid[32];      //ap����
	BYTE  mac[32];      
	BYTE  security[48];  //���ܷ�ʽ
	UINT  rssi;         //�ź�ǿ��
	BYTE  reserve[80];
}RSNet_SoleSwannRouterRepeat_t;
typedef struct 
{
      int   structsize;
	UINT RuleCnt;				/*����ӵĹ��˹�������*/

	BYTE RuleAddr[16][16];		/*���˹��������ַ*/
	BYTE RuleMode[16];			/*�������ģʽ: 0~IP����, 1~MAC����*/
	BYTE FilterEnable;			/*���˿���: 0~��, 1~��*/
	BYTE FilterMode;			/*����ģʽ: 0~�����б�, 1~������*/
	BYTE reversed[22];
}RSNet_NetFilter_t;
typedef struct 
{
	int   structsize;
	char  ReportIpAddr1[64];   /*��������ַ*/
    char  ReportIpAddr2[64];   /*���÷�������ַ*/
    UINT Port1;               /*�������˿�*/
    UINT Port2;               /*���÷������˿�*/
    UINT ReportTypeMask;		/*���õı�������, ��λ��ʾ���ж���λΪ1���ж�����*/
								/*bit0Ϊ1����ʾidΪ00��һ��,ReportType��ֵΪö��0 ALTE_REPORT_TYPE_E*/
								/*bit1Ϊ1����ʾidΪ01��һ��,ReportType��ֵΪö��1 ALTE_REPORT_TYPE_E*/
	UINT ReportType;			/*���濪�أ���bit0Ϊ1��idΪ00��״̬Ϊon*/
    BYTE  ReportPeriod;        /*������: OFF, 1,2,5,10,30min, 1,2,6,12h, 1,2,7day*/
	char  EnableReport;        /*����ʹ��: 0-Disable, 1-Enable*/
    BYTE  reserve[10];
}RSNet_ALTEReport_t;

typedef enum _ALTE_REPORT_TYPE_
{
	ALTE_REPORT_ONLINE = 0,
	ALTE_REPORT_HDD,
	ALTE_REPORT_RECORD,			/*¼��״̬*/
	ALTE_REPORT_VIDEOLOSS,
	ALTE_REPORT_CHNINFO = 8,
	ALTE_REPORT_RECINFO,		/*¼����Ϣ����ӦSystem�˵��е�Record Info*/
	ALTE_REPORT_MAX
}ALTE_REPORT_TYPE_E;

/* GB28181ҳ������ṹ */

/* GB28181ҳ������ṹ */
typedef struct 
{
	UINT	StructSize; 			//�ýṹ���С
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
	UINT StructSize; 			//�ýṹ���С
	BYTE Reserve1[4];			//�����ֽ�
	DateTime time; 				//ϵͳʱ��
	unsigned long long LanguageMask;		//�豸֧�ֵ�����,��λ����
	unsigned long long AreaMask;			//�豸֧�����õ����򣬰�λ����
	BYTE selLanguage;			//��ǰѡ�������
	BYTE selArea;               //��ǰѡ�������
    BYTE TimeMode;				//ʱ���ʽ: 0:24Hour  1:12Hour
	BYTE TimeDisplayMode;       //ʱ����ʾģʽ��0:AM  1:PM
	BYTE DateMode;				//���ڸ�ʽ: 0:MM/DD/YY 1:YY-MM-DD 2:DD/MM/YY
    BYTE TimeZone;				//ʱ��
	BYTE Frequency;             //Ƶ��
	BYTE NetworkTimeCheck;		//����Уʱ���: 0:�ɹ� ������ʧ��
	BYTE Reserve2[16];
	BYTE cityName[128];
}RSNet_WizardInfo_t;

typedef struct _UI_POINT_S {
	unsigned short x;
	unsigned short y;
} RSNet_POINT_t;

typedef struct {
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 	//ͨ������

	/*���8���ȼ�*/
	BYTE Sensitivity;
	/*�Ƿ�����PIR �� �ƶ����<RS_Close, RS_Open>*/
	BYTE ChnSwitch;
	/*Send Email ����<RS_Close, RS_Open>*/
	BYTE SendEmail;
	/*����������ʱ��*/
	BYTE BuzzerMooTime;
	/*Record Channel, ����ͨ��¼�񣬰�λ��¼*/
	UINT RecordChannel;
	/*¼����ʱʱ��*/
	BYTE RecordDelayTime;
	/*Record channel switch ����¼�����ܿ��� <RS_Close, RS_Open>*/
	BYTE Record;
	/*Show Message <RS_Close, RS_Open>����*/
	BYTE ShowMessage;
	/*FullScreen ���� ����ȫ��<RS_Close, RS_Open>*/
	BYTE FullScreen;
	/*�������ã�180��������32���ֽڱ�ʾ��ÿλ��ʾһ������*/
	BYTE RegionSetting[32];	/* LoginRsp MotionMode�ֶ�:0,ʹ�õ�ǰ�ֶ�*/
	/* �������  ֻ�� LoginRsp MotionMode==2ʱ,���ֵ������Ч��*/
	BYTE MbRow;
	/* ������� ֻ�� LoginRsp MotionMode==2ʱ,���ֵ������Ч��*/
	BYTE MbCol;
	/*Alarm Out ����<RS_Close, RS_Open>*/
	BYTE AlarmOut;
	/*�������ʱ��*/
	BYTE AlarmOutTime;
	BYTE AlarmOutManager[MAX_ALARMOUT_NUM];
	/*�������ã�200��������32���ֽڱ�ʾ��ÿλ��ʾһ������*/
    //BYTE RegionSetting3531[200];  /* LoginRsp MotionMode�ֶ�:1��2,ʹ�õ�ǰ�ֶ�*/
    union {
        struct {
            BYTE RegionSetting3531[200];  /* LoginRsp MotionMode�ֶ�:1��2,ʹ�õ�ǰ�ֶ�*/
        }BlockRegion;
        struct
        {
            BYTE MotionNum[4];  /* ��Ӧ�����Ƿ����ã�Ϊ1���ã�Ϊ0������ */
            RSNet_Rect_t Rect[4];
            BYTE Sensitivities[4]; /*11���ȼ�:0-�ߣ�1-�ϸߣ�2-�У�10:���*/
            UINT  RectMaxNum;    /*motion max rect num 2016.10.19 add*/
        }RectRegion;
    };

	BYTE FtpLink;			/*FTP���� ����*/
	BYTE PushSwitch;    /*�Ƿ����ƶ���ⱨ������, 0: close; 1: open.*/
	BYTE WirelessAlarmSensor; /*�ⲿsensor ���� ʹ��0, ��ʹ��, 1. ʹ��*/
	BYTE LlluminationRing; /* ���ջ�0, ��ʹ��, 1. ʹ��   */
	BYTE AudioAlert; /* ��Ƶ����0, ��ʹ��, 1. ʹ�� */
	BYTE AudioSelect; /* ��������ѡ�� 0, Doorbell 1.Ringtone, 2.Siren */
	BYTE AlarmDurationTime;/*0: 10s , 1: 30s, 2: 60s*/
	BYTE CloudNotify; /*�������ϴ�ʹ�ܿ���*/
	
	BYTE PIRFlag;
	BYTE SensitivityMode;//0:8���ȼ�ģʽ��1:1-100ģʽ
	BYTE PIRTestEnable;	//�Ƿ�����PIR����ģʽ, 0: ������, 1������

	BYTE LightLinkage;/*�׹��motion�������� 0:������ 1:����*/
	BYTE LoudSpeaker;/*���������� 0:�� 1:��*/
	BYTE FtpVideoLink;         /*FTP¼������ ����*/
	BYTE CloudPicUpload; /* �ƴ洢ͼƬ�ϴ� */
	BYTE CloudVideoUpload;
	BYTE Reservel[24];
	UINT RecordChannel_EX[8];
	/*ȡbitλ:3��ʾһ��ͨ�����3���������,ÿ���������봥�������������
	32*8= 256·���κ�ͨ���������*/
	BYTE AlarmOutManagerEx[3][32];
	RSNet_POINT_t DetectArea[8];  /* Ԥ��֧��8����������ʹ��6������ */
}RSNet_SolePirMotionSet_t;


//����ƽ̨�����㷨ʶ�����Ͷ���
typedef enum 
{
	JD_VAC_TYPE_OBJECT_ABANDONED_DETECTION = 0, //�������� 
	JD_VAC_TYPE_OBJECT_REMOVED_DETECTION = 1, //�����Ƴ���� 
	JD_VAC_TYPE_TRIPWIRE_DETECTION = 2, //���߼�� 
	JD_VAC_TYPE_INTRUSION_DETECTION = 3, //���ּ�� 
	JD_VAC_TYPE_RETROGRADE_DETECTION = 4, //���м�� 
	JD_VAC_TYPE_LOITERING_DETECTION = 5, //�ǻ���� 
	JD_VAC_TYPE_LICENSE_PLATE_RECOGNITION = 6, //����ʶ�� 
	JD_VAC_TYPE_METER_RECOGNITION = 7, //���ܶ��� 
	JD_VAC_TYPE_SWITCH_RECOGNITION = 8, //��բ״̬���� 
	JD_VAC_TYPE_BREAKER_RECOGNITION = 9, //��·��״̬���� 
	JD_VAC_TYPE_HELMET_RECOGNITION = 10, //��ȫñ������ 
	JD_VAC_TYPE_SMOKE_FIRE_RECOGNITION = 11, //�̻��� 
	JD_VAC_TYPE_METAL_CORROSION_DETECTION = 12, //�����ʴ��� 
	JD_VAC_TYPE_BIRD_NEST_DETECTION = 13, //�����񳲼�� 
	JD_VAC_TYPE_LEAVE_OFFICE_CHECK = 14, //��ڻ��� 
	JD_VAC_TYPE_OBJECT_CLASSIFICATION = 15, //Ŀ����� 
	JD_VAC_TYPE_VIDEO_DIAGNOSIS = 16, //��Ƶ��� 
	JD_VCA_RED_MANTLE_DETECTION = 101 //�첼᣼��,�Ǳ�׼��������(ʶ�����ɹ����������Ƴ�JD_VAC_TYPE_OBJECT_REMOVED_DETECTION)
}JD_VCA_TYPE_ENUM;

//����ƽ̨���ܶ������� JD_VAC_TYPE_METER_RECOGNITION
typedef struct
{	
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	int left;		//�Ǳ������ص�
	int top;		//�Ǳ������ص�
	int width;		//�Ǳ��
	int height;		//�Ǳ��
	int begangle;	//��ʼ�Ƕ�
	int anglescale;	//�Ƕȷ�Χ
	int initv;		//��ʼֵ
	int valuescale;	//����
	char Enable;
	char reserve[7];
}RSNet_SoleJDVCAMeterRecongitionConfig_t;



//����ƽ̨����㶨��
typedef struct
{
	int x;
	int y;
}JD_VCA_Point;

#define MAX_VCA_POINTS  16		//�㷨�����õ������������

//����ƽ̨���������㷨���� JD_VAC_TYPE_INTRUSION_DETECTION
typedef struct
{
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	int totalPoints;						//��������
	JD_VCA_Point points[MAX_VCA_POINTS]; 	//�����
	float imgResizeFactor;					//ͼ�����ű���(���Ӹ�ֵ�����СĿ��ļ����)
	float minPersonConf;					//���������Ŷ���ֵ
	int skipFrameNum;						//����������ʼ֡������������ͷǰ��֡���ȶ���
	int bgsUpdataFactor;					//�����������ʣ�������Խ�����Խ����
	int BBSInRoiThr;						//�ж�ROI�����������ֵ����������
	int fgInRoiThr;							//�ж�ROI����ǰ������ֵ����������
	int fgPesBBThr;							//ǰ����ߴ���ֵ
	float minOverlapRatio;					//ǰ���������ص���ֵ
	float pesRectRatio;						//����߶������Ĭ�ϱ�ֵ
	float pesRectMaxRatio;					//����߶����������ֵ
	float footRectRatioFrom;				//�Ų�����������ֵ��ʼ�㣨Ԥ����
	float footRectRatioTo;					//�Ų�����������ֵ��ֹ�㣨Ԥ����
	char Enable;
	char reserve[11];
}RSNet_SoleJDVCAIntrusionDetectionConfig_t;



//����ƽ̨����첼᣼����� JD_VCA_RED_MANTLE_DETECTION
typedef struct
{
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask; 	//ͨ������
	float fImgResizeFactor;			//ͼ�����ű���(���Ӹ�ֵ�����СĿ��ļ����)
	float minCircleConf;			//��־���������Ŷȣ����˵����ŶȽ����
	float filterSeconds;			//�˲�ʱ��
	int minFilterSize;				//��С�˲�������
	int nSkipFrames;				//�������ӵ�skipFrameNum֡��ʼ����ǰ��֡���ȶ���
	float bgsUpdateSecondsSlow;		//����������������
	float bgsUpdateSecondsFast;		//�챳������������
	float fDetectRatioFixed;		//ȷ��Ϊ�ȶ���־�ļ������ֵ
	float fDetectRatioLosted;		//ȷ��Ϊ��ʧ״̬�ļ������ֵ
	float fDetectRatioOcclusion;	//ȷ��Ϊ�ڵ�״̬�ļ������ֵ
	float fDetectRatioNonOcclusion;	//ȷ��Ϊ���ڵ�״̬�ļ������ֵ
	float vanishKeepSeconds;		//��ʧ״̬������ɾ����ʱ��
	float toFixKeepSeconds;			//���̶��ȴ�ʱ��
	float occlusionKeepSeconds;		//�ڵ�������ת��ʧ״̬��ʱ��
	float toMonitorWaitSeconds;		//��ʼ���׶ν�����׶ε�ʱ����
	float reinitWaitSeconds;		//���½����ʼ���׶ε�ʱ����
	char Enable;
	char reserve[7];
}RSNet_SoleJDVCARedMantleDetectionConfig_t;



//о����������㷨�����ṹ��
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
	UINT  	faceSensitivity;			/*������������ȣ���Χ0-100*/
	UINT	faceQualityEnhancement;		/*����������ǿ����/�أ�Ĭ�Ͽ�*/
	UINT	picQuality ;			/* ����ͼƬ������������Χ0-100��ֵԽ���������Խ��*/
	UINT 	ploy;/*���Ա�ţ���Χ��1~3*/
	UINT	bigSourceImageWidth;/*ͼ�����ģ���ȡ��ԭʼ��ͼͼ����*/
	UINT 	bigSourceImageHeight;/*ͼ�����ģ���ȡ��ԭʼ��ͼͼ��߶�*/
	UINT 	smallSourceImageWidth;/*ͼ�����ģ���ȡ��ԭʼСͼͼ����*/
	UINT 	smallSourceImageHeight;/*smallSourceImageHeight��ͼ�����ģ���ȡ��ԭʼСͼͼ��߶�*/
	UINT 	sceneNumber;/*����ģʽ��ţ���Χ��>=1*/
	UINT 	minFaceWidth;/*�������ʱ��������С���ؿ��*/
	UINT 	maxFaceWidth; /*�������ʱ������������ؿ��*/
	UINT 	minFaceHeight;/*�������ʱ��������С���ظ߶�*/
	UINT 	maxFaceHeight;/*�������ʱ������������ظ߶�*/
	UINT 	isSendFullImage;/*�ڷ���ѡ�ź������ͼ��ʱ���Ƿ��Ͷ�Ӧ��ȫ��ͼ��*/
	UINT 	isPreviewFaceInfo;/*�Ƿ���Ԥ��ʱ����������0�������ӣ�1������*/
	int faceImageType;/*ͼ�����ģ�鷵�ص�����ͼ������*/
	int fullImageType;/*ͼ�����ģ�鷵�ص�����ͼ���Ӧ��ȫ��ͼ�������*/
	int  bigSourceImageType;/*ͼ�����ģ���ȡ��ԭʼ��ͼͼ������*/
	int  smallSourceImageType;/*ͼ�����ģ���ȡ��ԭʼСͼͼ������*/
	BYTE  	SiaIntSwitch;          	/*0-�رգ�1-��*/
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
	UINT HttpsType;  /*0: ������HTTPS 1: �����ͻ���HTTPS*/
	BYTE  HttpsSwitch;
	BYTE  reserve[3];
	UINT HttpsPort;
}RSNet_HttpsParam_t;

typedef struct
{
	BYTE Authentication; /*0: MD5��Ȩ��ʽ  1��SHA��Ȩ��ʽ*/
	CHAR EncryptedType;   /* �����㷨��չ��*/
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
	CHAR  readcommunity[16];		/*����IPC����ͬ����	  ������ʹ�øù�ͬ������ֻ�ɶ�IPC�ϵ�snmp��Ϣ*/
	CHAR  writecommunity[16];	 /*����IPC��д��ͬ����	������ʹ�øù�ͬ���������Զ�дIPC�ϵ�snmp��Ϣ*/
	CHAR  TrapIPAddr[32]; 	  /*�����������ַ*/
	CHAR  IpcIp[32];
	EncryptionParam_t Authentication[2]; /*0 ���ö��û������룻 1�����ö�д�û�������*/
}RSNet_Snmp_t;

typedef struct
{
	UINT StructSize;
	UINT ChannelMask;
	UINT delaycount; //Ŀ�������ٶ�,/Ĭ��ֵΪ10/����ֵ��0~10
	UINT misscount;	//Ŀ�궪ʧ�ٶ� /Ĭ��ֵΪ5/����ֵ��3~5
	UINT rminsize_w; //ɸ����С���������ȣ��̶����ص�ߴ磬��ϴ���ͼ��ߴ�ʹ�ã���С40��/Ĭ��ֵΪ40/����ֵ��40~50
	UINT rminsize_h; //ɸ����С��������߶ȣ��̶����ص�ߴ磬��ϴ���ͼ��ߴ�ʹ�ã���С40��/Ĭ��ֵΪ40/����ֵ��40~50
	UINT rmaxsize_w; //�����/Ĭ��ֵΪ400/���ڸÿ�߱ȵ�������������/����ֵ��400~500��1080P��
	UINT rmaxsize_h;	//���߶�/Ĭ��ֵΪ400/���ڸÿ�߱ȵ�������������/����ֵ��400~500��1080P��
	UINT pminsize;   //��������Ԥ��⣬��С�������߶ȣ��̶����ص�ߴ磬��ϴ���ͼ��ߴ�ʹ�ã�ֵӦΪrminsize��rmaxsize֮�䣩/Ĭ��ֵΪ30��360P��/����ֵ��80~90��1080P��
	UINT pmaxsize;	//��������Ԥ��⣬����������߶ȣ��̶����ص�ߴ磬��ϴ���ͼ��ߴ�ʹ�ã�ֵӦΪrminsize��rmaxsize֮�䣩/Ĭ��ֵΪ80��360P��/����ֵ��200~300��1080P��
	UINT cropused;	//���þֲ�������Ŀ��أ�����������Ϊ1��/��ʼֵΪ0��ֵΪ1ʱ��Ч
	UINT tframeNum;       //ÿ�μ��/���������������׷�ٵ�֡��/Ĭ��ֵΪ3/����ֵ��3~5
	RSNet_Rect_t croproi;	//���þֲ������������꣬��Դ���ߴ�/ֻ��cropused��Чʱ���˲�������Ч/��ʼֵΪ{0,0,0,0}
	BYTE HGIntSwitch;
	BYTE Reservel[7];

	UINT SnapShotMode;//0)����ץ��ģʽ 1)���ץ��ģʽ
	UINT SnapShotFrame[2];//0)����ץ��ģʽ���趨��֡���ڽ��� 1)���ץ��ģʽ���趨�ļ��֡��
	UINT SavePic;//�Ƿ�ץ��ʱ�򣬱�������ͼƬ
	BYTE Reserved[128];
}RSNet_SoleHGIntParam_t;

typedef struct{
	UINT  StructSize;  // �ýṹ���С
	UINT  ChannelMask;  // ͨ������
	BYTE  BrightTime; // �׹�ʱ���� �Զ���׹�ʱ������λ sec ����Χ  1-120��Ĭ��5 sec
	BYTE  FloodLightMode; // �׹�ģʽ�� 0��������1����˸
	BYTE  FloodLightValue; // ͬRSNet_SolePreviewCtrl_t��FloodLightValue��Ĭ��100
	BYTE  FloodLightSwitch; // ���ÿ��أ� 0 �ر�  1 ����
	BYTE  StrobeFrequency;// ��˸ģʽ�����ã�0 -- low ��1 -- middle �� 2 -- high
	BYTE  MbRow;
	BYTE  MbCol;
	BYTE Sensitivity;       /*8���ȼ�:8-�ߣ�7-�ϸ�..........  1-��*/
	BYTE  TimeSchedule[8][48]; // �׹�ƻ��� �׹��б�  ��   7*48�� Ԫ�صĵ�һ��λ��Ӧ�ſ��ء� 0�� ��  1����
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
	BYTE AlarmOutTime;      /*������������ʱ��:10s,20s,40s,60s,30s,1min,2min*/
	BYTE RecordDelayTime;   /*¼����ʱ����ʱʱ��:10s,30s,1min,2min,5mins*/
	BYTE EmailLink;			/*�ʼ����� ����*/
	BYTE RecordSwitch;		/*Record  switch*/
	BYTE AlarmOut;			/*ֻ��һ����������ģ���AlarmOutManager[0]����*/
	BYTE SensitivityExNight;
	BYTE loudAlarmLink;	
	BYTE SirenSwitch;
	BYTE SirenValue;
	BYTE SirenTime;
	BYTE DualTalkVolume;
	BYTE ColorImageCtrl;//  �׹�����ʱ��ǿ�Ʋ�ɫ���ܣ�  1 -> on            0 -> off
	BYTE  reserved[12];
}RSNet_SoleFloodLightSet_t;

#define MAX_IO_INPUT_NUM  16

typedef struct _ioalarmmanage_
{
	UINT Structsize;
	UINT DispatchedFlag;   /*������־,1Ϊ������0Ϊ����*/
	UINT DispatchedDelayTime;  /*������ʱʱ��*/
	BYTE reserve[4];
	BYTE ChangeDispatched[MAX_IO_INPUT_NUM]; /*�ɱ䶯������IOͨ����־��1��ʾ�ɱ䶯������0��ʾ24Сʱ����*/
	BYTE SensorName[MAX_IO_INPUT_NUM][64];  /*����������*/
}RSNet_IoAlarmManage_t;

typedef struct {
	UINT StructSize;
	UINT ChannelMask;
	ULONGLONG DevTypeULL;
	UINT httpPort;
	UINT mediaPort;
	UINT Protocol; /*Э��*/
	BYTE Version;
	BYTE netMode;
	BYTE res[30];
	BYTE DevType[64];/*�豸����*/
	BYTE Manufacturer[64];/*����*/
	BYTE DevVersion[64];/*�豸�汾*/
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
	UINT       ChannelMask; 	//ͨ������

	BYTE       AudioAlarmSwitch;      /*0-�رգ�1-��*/
	BYTE       RiseSwitch;      /*��ǿ����ʹ�ܣ�0-�رգ�1-��*/
	BYTE 	   SoundIntensity;		 /*����ǿ����ֵ��1-100*/
	BYTE       RiseSensitivity;       /*��ǿ���������ȣ�1-100*/
	BYTE       DeclineSensitivity;       /*��ǿ���������ȣ�1-100*/
	BYTE       DeclineSwitch;  /*��ǿ����ʹ�ܣ�0-�رգ�1-��*/

	BYTE       AlarmOut;   /*�������ʱ��*/
	BYTE       AlarmOutTime;      /*������������ʱ��:10s,20s,40s,60s,30s,1min,2min*/
	BYTE       RecordSwitch;      /*Record  switch*/
	BYTE       RecordDelayTime;   /*¼����ʱ����ʱʱ��:10s,30s,1min,2min,5mins*/

	BYTE       EmailLink;         /*�ʼ����� ����*/
	BYTE	   FtpUploadSwitch;   /*�ϴ�FTP����*/
	BYTE       AudioInputEnable;/*��Ƶ�����쳣�������� 0:�رգ�1:����*/
    BYTE       BuzzerMooTime;
	BYTE       reserve1[2];
	BYTE	   TimeSchedule[8][48];	// ��Ƶ����ʱ��ƻ���
	UINT       RecordChannel[8];
	BYTE       ShowMessage;      /*Show Message ����*/
	BYTE       FullScreen;       /*ȫ�� ����*/
	BYTE       AlarmOutManager[MAX_ALARMOUT_NUM];
	BYTE       res;
	BYTE       FtpVideoLink;	/*FTP¼������ ����*/
	BYTE       CloudPicUpload; /* �ƴ洢��Ƶ�ϴ� */
	BYTE       CloudVideoUpload;
	BYTE       reserve2[202];
}RSNet_SoleSoundDetectionParam_t;

typedef struct  {
	BYTE StartIPAddress[16]; 	/*��ʼIP��ַ*/
	BYTE EndIPAddress[16];   	/*����IP��ַ*/
	BYTE IPType;                 /*ip���� 0:ipv4 1:ipv6*/
	BYTE reserve[7];
}RSNet_NetworkIPAddress_t;

typedef struct  {
	UINT StructSize;
	BYTE EnableIPFilter;	/*�Ƿ�ʹ��IP�ڰ��������ƣ�0-no��1-yes*/
	BYTE ChooseIPFilter;	/*�������Ʒ�ʽ��0-���ð�������1-���ú�����*/
	BYTE RestrictedType;      	/*�ڰ�����������:0-��������1-������*/
	BYTE reserve[1];
	UINT BlacklistCount;      	/*����������*/
	UINT WhitelistCount;      	/*����������*/
	RSNet_NetworkIPAddress_t Blacklist[64];  /*�������б�, �������64��*/
	RSNet_NetworkIPAddress_t Whitelist[64];  /*�������б�, �������64��*/
}RSNet_NetworkIPFilter_t;

typedef struct {
    UINT StructSize; 	//�ýṹ���С
    UINT ChannelMask; 	//ͨ������

    BYTE  FtpScHalfHour[8][48];  // 7 days and 48 halfhours
    /* bit 0 Ϊ��ͨftp�ϴ���bit 1 Ϊ����¼��bit 2 Ϊ����ftp�ϴ���
     * bit 3 Ϊ�������PIR ftp�ϴ���bit 4 ΪIn-Analysis
     * ��Ӧ��bitλΪ1��ʾ���ã�Ϊ0��ʾ���� */
    //*2018.05.25
}RSNet_SoleFtpScheduleset_t;


typedef struct {
	UINT StructSize; 	//�ýṹ���С
	UINT ChannelMask; 
	UINT EventScHalfHour[8][48];     // 7days and 48 halfhours
	/*
	  ��Զ�ʱѲ���ƻ���1���ֽڹ�8λ��
	  ��bitȡλ bit 0 Ԥ�õ�Ѳ����  bit 1Ϊ����ɨ�裬	bit2�켣Ѳ����bit3����ɨ�裬bit 4Ϊ�ָ�����λ����
	  **********2019.03.27����Ѳ���ƻ�λ������ͳһ************
	  ��Ӧ��bitλΪ1��ʾ�мƻ���Ϊ0��ʾ�޼ƻ�
	  EventScHalfHour[8]�����գ���һ~����: 0~6����7λΪ����λ 
	*/	
	UINT Recovertime;		//5s-720s  ����ָ�ʱ��
	BYTE  CruiseSwhich;      //0��ʾ�����ö�ʱѲ������1��ʾ���ö�ʱѲ������
	BYTE   reserve[11];
}RSNet_SolePTZScheduleSet_t;

typedef struct
{
	UINT  StructSize;
	BYTE  VpnSwitch;
	BYTE  VpnTlsKeySwitch;	//tls-authԿ�׿��أ�0��ʾ�أ�1��ʾ��
	BYTE  VpnNetDev;	//���������豸��0��ʾTUN,1��ʾTAP
	BYTE  VpnProtocol; //�����Э�飬0��ʾTCP��1��ʾUDP
	UINT  VpnPort; 	//VPN�������˿�
	BYTE  reserve[4];
	BYTE  VpnServerIP[32];		//VPN������IP
	BYTE  VpnUserName[32]; 	//VPN�ͻ����û�
	BYTE  VpnPassword[32]; //VPN�ͻ�������
	BYTE  VpnCipher[16];	//�����㷨��Ĭ��BF-CBC
	BYTE  VpnAddOptions[256];	//׷�ӵĿͻ�������ѡ��
	BYTE  VpnCompLzo;	//�Ƿ���LZOѹ��
	BYTE  reserve1[7];     //8�ֽڶ���
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

