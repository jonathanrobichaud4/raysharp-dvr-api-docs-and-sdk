#ifndef _CORRECTION_TYPE_H_
#define _CORRECTION_TYPE_H_

#include "common_type.h"
#include <time.h>
#ifndef WINDOWS_PLATFORM
#include <sys/time.h>
//#define CV_PI 3.1415926f
#endif
#define CV_PI 3.1415926f
#ifdef ANDROID_PLATFORM
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#define MAX_FISHEYE_CHN 9	//��������Ŀ
#define MAX_FISHEYE_DEV 1	//����豸��Ŀ

/*�̶�ģʽ����*/
typedef enum rsFISHEYE_COMB_TYPE_E
{
	FISH_CEILING_EYE = 0,		// ����+����                  [FishEye]
	FISH_CEILING_VR,	        // ����+VR��״                [VR]
	FISH_CEILING_CYLIND3D,      // ����+VR����                [Cylinder]
	FISH_CEILING_CYLIND360,		// ����+360ȫ��			      [Panorama 360]
	FISH_CEILING_CYLIND180,		// ����+180ȫ��               [Panorama 180]
	FISH_CEILING_2PTZ,			// ����+2��PTZ                [2 PTZ]
	FISH_CEILING_4PTZ,			// ����+4��PTZ         = 4    [4 PTZ]
	FISH_CEILING_CYLIND360_1PTZ,// ����+360ȫ��+1��PTZ        [Panorama 360 + 1 PTZ]
	FISH_CEILING_CYLIND360_3PTZ,// ����+360ȫ��+3��PTZ = 4    [Panorama 360 + 3 PTZ]
	FISH_CEILING_CYLIND360_6PTZ,// ����+360ȫ��+6��PTZ = 7    [Panorama 360 + 6 PTZ]
	FISH_CEILING_CYLIND360_8PTZ,// ����+360ȫ��+8��PTZ = 9    [Panorama 360 + 8 PTZ]
	FISH_CEILING_EYE_3PTZ,		// ����+����+3��PTZ	   = 4    [FishEye + 3 PTZ]
	FISH_CEILING_EYE_8PTZ,		// ����+����+8��PTZ    = 9    [FishEye + 8 PTZ]

	FISH_DESKTOP_EYE,			// ����+����                  [FishEye]
	FISH_DESKTOP_VR,	        // ����+VR��״                [VR]
	FISH_DESKTOP_CYLIND3D,      // ����+VR����                [Cylinder]
	FISH_DESKTOP_CYLIND360,		// ����+360ȫ��               [Panorama 360]
	FISH_DESKTOP_CYLIND180,		// ����+180ȫ��               [Panorama 180]
	FISH_DESKTOP_4PTZ,			// ����+4��PTZ         = 4    [4 PTZ]
	FISH_DESKTOP_CYLIND360_1PTZ,// ����+360ȫ��+1��PTZ        [Panorama 360 + 1 PTZ]
	FISH_DESKTOP_CYLIND360_3PTZ,// ����+360ȫ��+3��PTZ = 4    [Panorama 360 + 3 PTZ]
	FISH_DESKTOP_CYLIND360_6PTZ,// ����+360ȫ��+6��PTZ = 7    [Panorama 360 + 6 PTZ]
	FISH_DESKTOP_CYLIND360_8PTZ,// ����+360ȫ��+8��PTZ = 9    [Panorama 360 + 8 PTZ]
	FISH_DESKTOP_EYE_3PTZ,		// ����+����+3��PTZ    = 4    [FishEye + 3 PTZ]
	FISH_DESKTOP_EYE_8PTZ,		// ����+����+8��PTZ    = 9	  [FishEye + 8 PTZ]

	FISH_WALL_EYE,				// ��װ+����				  [FishEye]
	FISH_WALL_VR,               // ��װ+VRȫ��				  [VR]
	FISH_WALL_NORMAL,			// ��װ+normalȫ��			  [Panorama]
	FISH_WALL_4PTZ,				// ��װ+4��PTZ            = 4 [4 PTZ]
	FISH_WALL_NORMAL_3PTZ,		// ��װ+normalȫ��+3��PTZ = 4 [Panorama + 3 PTZ]
	FISH_WALL_NORMAL_8PTZ,		// ��װ+normalȫ��+8��PTZ = 9 [Panorama + 8 PTZ]
	FISH_WALL_EYE_3PTZ,			// ��װ+����+3��PTZ       = 4 [FishEye + 3 PTZ]
	FISH_WALL_EYE_8PTZ,			// ��װ+����+8��PTZ       = 9 [FishEye + 8 PTZ]

	FISH_TILT_EYE,				// ��б+����                  [FishEye]
	FISH_TILT_VR,               // ��б+VRȫ��				  [VR]
	FISH_TILT_NORMAL,			// ��б+normalȫ��            [Panorama]
	FISH_TILT_4PTZ,				// ��б+4��PTZ            = 4 [4 PTZ]
	FISH_TILT_NORMAL_3PTZ,		// ��б+normalȫ��+3��PTZ = 4 [Panorama + 3 PTZ]
	FISH_TILT_NORMAL_8PTZ,		// ��б+normalȫ��+8��PTZ = 9 [Panorama + 8 PTZ]
	FISH_TILT_EYE_3PTZ,			// ��б+����+3��PTZ       = 4 [FishEye + 3 PTZ]
	FISH_TILT_EYE_8PTZ,			// ��б+����+8��PTZ       = 9 [FishEye + 8 PTZ]

	FISH_COMB_TYPE_BUTT
}FISHEYE_COMB_TYPE_E;

/*���۹һ�ģ��*/
typedef enum rsFISHEYE_MOUNT_MODE_E					
{
	RSFISHEYE_CEILING_MOUNT = 0,		//����/����
	RSFISHEYE_DESKTOP_MOUNT = 1,		//�׹�/����
	RSFISHEYE_WALL_MOUNT    = 2,		//�ڹ�/��װ
	RSFISHEYE_TILT_MOUNT    = 3,		//�ڹ�/��б
	RSFISHEYE_MOUNT_MODE_BUTT
}RSFISHEYE_MOUNT_MODE_E;

/*Ӧ��ģ��*/
typedef enum rsFISHEYE_MODEL_E						
{
	FISHEYE_SPHERE		= 0,		//����У�������ң��׹ң��ڹң�
	FISHEYE_LATITUDE	= 1,		//�ڹ�ģ�ͣ��Լ���ͼ������װ��ģ�� Latitude��
	FISHEYE_CYLINDER360 = 2,		//360�Ȼ�����ͼ�����ң��׹ң�
	FISHEYE_CYLIND3D    = 3,        //��������3d�����ң��׹ң�
	FISHEYE_SPHERE_VR   = 4,		//����VR��ͼ�����ң��׹ң�
	FISHEYE				= 5,        //����ԭͼ
	FISHEYE_SPHERE_RE   = 6,        //������ģ��[-1/2 1/2]��ȷ��ĳ���Ƕ����۷�Χ����Χ������
	FISHEYE_BOUNDARY    = 7,        //������ģ��[-1 1], ��ѡ�д��ڻ��߽�
	FISHEYE_CYLINDER180 = 8,		//180�Ȼ�����ͼ�����ң��׹ң�
//#if !defined (WINDOWS_PLATFORM)
	FISHEYE_FLIP = 9,				//flip����
	FISHEYE_ORIGNAL = 10,			//ԭͼ���
//#endif
	FISHEYE_MODEL_BUTT
}FISHEYE_MODEL_E;

typedef enum rsFISHEYE_RANGE_TYPE_E
{
	FISHEYE_RANGE_CURVE,				//���߷�Χ
	FISHEYE_RANGE_RECT,					//���η�Χ
	FISHEYE_RANGE_BUTT
}FISHEYE_RANGE_TYPE_E;

/*��ɫ����Ŀ����*/
typedef enum rsFISH_PROGRAM_E
{
	FISH_PROGRAM_NORMAL,
//	FISH_PROGRAM_SPHEREVR,				
//	FISH_PROGRAM_CYLINDVR,				//VRģ����Ŀ
	FISH_PROGRAM_SPHERERANGE,			//���淶Χ��Ŀ
	FISH_PROGRAM_CYLINDRANGE,			//���淶Χ��Ŀ
	FISH_PROGRAM_LATITUERANGE,			//��γ�ȷ�Χ
	FISH_PROGRAM_BOUNDARY,				//���α߽緶Χ��Ŀ
//#if !defined (WINDOWS_PLATFORM)
	FISH_PROGRAM_FLIP,					//flip
	FISH_PROGRAM_ORIGNAL,				//ԭͼ���
//#endif
	FISH_PROGRAM_BUTT
}FISH_PROGRAM_E;

/*��ͼ�����ʽ����*/
typedef enum rsFISH_SNAPSHOT_E
{
	FISH_SNAPSHOT_BMP = 0, //D3DXIFF_BMP
	FISH_SNAPSHOT_JPG = 1, //D3DXIFF_JPG
	FISH_SNAPSHOT_TGA = 2, //D3DXIFF_TGA
	FISH_SNAPSHOT_PNG = 3, //D3DXIFF_PNG
	FISH_SNAPSHOT_DDS = 4, //D3DXIFF_DDS   
	FISH_SNAPSHOT_BUTT
}FISH_SNAPSHOT_E;

/*����ptz��������*/
typedef enum rsFISH_PTZ_E
{
	FISH_PTZ_LEFT = 0,					//��
	FISH_PTZ_RIGHT,						//��
	FISH_PTZ_UP,						//��
	FISH_PTZ_DOWN,						//��
	FISH_PTZ_LEFTUP,					//����
	FISH_PTZ_RIGHTUP,					//����
	FISH_PTZ_LEFTDOWN,					//����
	FISH_PTZ_RIGHTDOWN,					//����
	FISH_PTZ_ZOOMINC,					//�Ŵ�
	FISH_PTZ_ZOOMDEC,					//��С
	FISH_PTZ_CURISE,					//��Ѱ
	FISH_PTZ_BUTT
}FISH_PTZ_E;

#ifdef WINDOWS_PLATFORM
typedef struct rsFISH_SHADER_PATH_S
{
	char* Path[100];
}FISH_SHADER_PATH_S;
typedef struct rsFISH_DEVICE_S
{
	FISH_SHADER_PATH_S* Path;
	HWND hWnd;    // window handle
}FISH_DEV_S;
#endif
/*�����ڲ�*/
typedef struct rsFISH_INTRIC_PARA_S
{
	float r;								//���۰뾶
	float cx;								//�������� x����
	float cy;								//�������� y����
	float ang;								//��ʼ���Ƕ�
#if defined (HI_PLATFORM) || defined (WINDOWS_PLATFORM)
	int width[3];
	int height[3];							//ͼ����
#endif
#if defined (WINDOWS_PLATFORM)
	HWND hWnd;
#endif
	char resvd[4];
}FISH_INTRIC_PARA_S;	

/*ptz����*/
typedef struct rsFISH_MOVE_S
{
	FISH_PTZ_E ePtz;					//ptz��������
	float dx;							//����϶���x��С �� ptz��λ�ƶ���x��С���������ҷ���
	float dy;							//����϶���y��С �� ptz��λ�ƶ���y��С���������·���
	float dk;							//�������Ŵ���С�� ptz���β����Ŵ���С�仯ֵ

	float v;							//ptz��ǰ��λ�ƶ����ٶ�

	float x;							//Ԥ��λxλ��
	float y;							//Ԥ��λyλ��
	float k;							//Ԥ��λ�Ŵ���С����

	char CruiseNum;                     //�ڼ�����������Ѳ��(1~MAX_FISHEYE_CHN, 0Ϊû��Ѳ��)
	char EnableNum;                     //�ڼ�����������PTZ (1~MAX_FISHEYE_CHN, 0Ϊû�п���)
	bool bSlowDown;						//�Ƿ��Ǵ��ڼ���״̬
	char resvd[1];
}FISH_MOVE_S;

/*���β���*/
typedef struct rsFISH_ROAM_PARA_S
{
	float x;							//��������x
	float y;							//��������y
	float k;							//�Ŵ���С����
//#if !defined (WINDOWS_PLATFORM)
	bool bFullScreen;					//�Ƿ�Ϊȫ��
	bool bCruise;						//�Ƿ�����ѯ
//#endif
	bool bDefault;                      //�Ƿ���Ĭ�ϲ���
	char resvd[3];
}FISH_ROAM_PARA_S;

typedef struct rsFISH_RENDER_RANGE_S
{
	float x;						//��Ⱦƽ���ʼλ��x
	float y;						//��Ⱦƽ���ʼλ��y
	float w;						//��Ⱦƽ���ʼλ�ÿ��
	float h;						//��Ⱦƽ���ʼλ�ø߶�
#if defined (WINDOWS_PLATFORM)
	int screen_width;               //ÿ�������Ŀ��
	int screen_height;				//ÿ�������ĸ߶�
#endif
	char resvd[4];
}FISH_RENDER_RANGE_S;

typedef struct rsROMA_ATTR_S
{
	FISHEYE_MODEL_E eModel;           //ģ������	
	FISH_ROAM_PARA_S astRoamPara;     //���β���
	FISH_RENDER_RANGE_S stRenderRange;//������Χ
	OrthoProjInfo_S stOrthoProjInfo;  //����ͶӰ����
	float fAngle;					  //�Ƕȱ仯
	char resvd[4];
}ROMA_ATTR_S;

/*У����Χ��ͼ��Ϣ*/
typedef struct rsFISHEYE_RANGE_MAP_S
{
	FISH_PROGRAM_E	eFishProgramRange;		//��ͼ��Ҫʹ�õ���Ŀ����
	bool bActivate;							//����Χ�Ƿ񱻼���

//#if 0
	//#ifdef WINDOWS_PLATFORM

	//FISHEYE_RANGE_TYPE_E enRangeType;       //����Χ��������
	//time_t clickTimeVal;					//����ʱ��
	//unsigned char u8DrawScreenNum;			//�ڵڼ��������ϻ���Χ
	//char resvd[2];

	//#else
//#endif

	FISHEYE_MODEL_E	eFishEyeModel;			//ȫ��ͼ������
#ifdef WINDOWS_PLATFORM
	time_t clickTimeVal;
	//timeval clickTimeVal;
#else
	struct timeval clickTimeVal;			//����ʱ��
#endif
	bool bDraw;								//�Ƿ�Ҫ����У������Χͼ
	unsigned char u8SelectScreenNum;		//����ѡ��ĵڼ�����Ļ
	unsigned char u8ScreenNum;				//�ڵڼ��������Ͻ�����ͼ
	char resvd[1];

	//#endif

}FISHEYE_RANGE_MAP_S;

/*���ӹ�����Ϣ*/
typedef struct rsFISHEYE_FUNC_S
{
	char String[256];				  //�����ͼ��·���������� 
	FISH_SNAPSHOT_E enSnapShotType;   //��ͼͼƬ�ĸ�ʽ
	bool bIsSnapShot;                 //�Ƿ��ͼ��Ĭ�ϲ���ͼ
	bool bIsRender;                   //�Ƿ���Ⱦ��Ĭ����Ⱦ

}FISHEYE_FUNC_S;

/*ģ�Ͷ�̬�仯Ч��*/
typedef struct rsFISHEYE_DYNAMIC_S
{
	/*�ɲ���0�任������1*/
	ROMA_ATTR_S stRoma0;		//ģ��0�Ĳ���(��ǰ��ģ��)
	ROMA_ATTR_S stRoma1;		//ģ��1�Ĳ���
	float fCoef;				//����ģ�ͱ仯ϵ������0->1��0Ϊ��ǰģ�ͣ�1Ϊ��Ҫ��ģ��,�м�ֵΪ��̬�仯
	unsigned char u8DynamicType;//��̬�仯���ͣ�0:Ϊģ���ڲ��л���1:Ϊģʽ�л�
	bool bActivate;				//��̬Ч���Ƿ񱻼���
	char resvd[2];

}FISHEYE_DYNAMIC_S;

/*����У����ʼ�Ƕ�*/
typedef struct rsFISHEYE_INITANGLE_S
{
	bool bActivate;					//�Ƿ񱻼���
	float x;						//��Ⱦƽ���ʼλ��x
	float y;						//��Ⱦƽ���ʼλ��y
	float w;						//��Ⱦƽ���ʼλ�ÿ��
	float h;						//��Ⱦƽ���ʼλ�ø߶�
	float fInitAngle;				//��ʼ�Ƕ�
	RSFISHEYE_MOUNT_MODE_E enFishMountMode;
}FISHEYE_INITANGLE_S;

typedef struct rsFISHEYE_ATTR_S 
{
	RSFISHEYE_MOUNT_MODE_E enFishMountMode;			//���۹һ�ģ��
	FISHEYE_COMB_TYPE_E  enFishCombType;		    //���ģʽ����	
	
	unsigned char u8MultiScreen;				    //������Ŀ
	unsigned char u8SelectScreenNum;		        //����ѡ��ĵڼ�����Ļ
	unsigned char u8FullScreen;						//�ڼ�����������ȫ��
	char resvd[1];
	ROMA_ATTR_S astRegionAttr[MAX_FISHEYE_CHN];     //��������
	FISH_MOVE_S stFishMove;                         //PTZ����
	FISHEYE_RANGE_MAP_S stFishRangeMap;			    //У���ķ�Χͼ
	FISHEYE_DYNAMIC_S   stFishDynamic;              //��̬Ч��
	FISHEYE_FUNC_S astFishFunc[MAX_FISHEYE_CHN];    //���ӵĹ���
	FISHEYE_INITANGLE_S stFishInitAngle;			//��ʼ�Ƕȿ���
}RSFISHEYE_ATTR_S; 

typedef struct rsIMAGE_S
{
	FISHEYE_PIXEL_FORMAT_E ePixFormat;					//��������
#if !defined (WINDOWS_PLATFORM)
	FISHEYE_FRAME_FORMAT_E eFrameFormat;				//֡���ͣ���ͨframe,����frame
#endif
	unsigned char* pDataAddr[3];						//�����ַ
	unsigned int u32PhyAddr[3];							//�����ַ
	int width[3];										//ͼ���
	int height[3];										//ͼ���
	int stride[3];										//���
	int timeRef;										//ʱ��ο�
	void* pPrivate;										//
	char resvd[4];
}IMAGE_S;

typedef struct rsFISH_OUT_INFO_S
{
	int imgNum;									//���ͼ����Ŀ
	IMAGE_S stFishImgOut[MAX_FISHEYE_CHN];		//���ͼ����Ϣ
	char resvd[4];
}FISH_OUT_INFO_S;



	//HGLRC hglrc;  // rendering context
	//HDC   hdc;    // device context


/*��������������*/
typedef enum rsFISH_MOUSE_E
{
	FISH_MOUSE_MOVE = 0,               //����
	FISH_MOUSE_WHEEL,                  //����
	FISH_MOUSE_LBUTTONDOWN,            //�������
	FISH_MOUSE_LBUTTONUP,              //����ͷ�
	FISH_MOUSE_LBUTTONDBLCLK,          //���˫��left button double click
	FISH_MOUSE_RBUTTONDBLCLK,          //�Ҽ�˫��right button double click
	FISH_MOUSE_BUTT
}FISH_MOUSE_E;

/*���ܰ�ť��������*/
typedef enum rsFISH_FUNC_E
{
	FISH_FUNC_SNAPSHOT = 0, 		  //��ͼ����
	FISH_FUNC_PREVIEW,                //ͨ��Ԥ������
	FISH_FUNC_CHNSELECT,			  //��ѯ��ǰѡ�еķ������ں�
	FISH_FUNC_BUTT
}FISH_FUNC_E;

/*�豸��������*/
typedef enum _FishControlFlag_E 
{
    FISH_EYE_PTZ_E   = 0,              //PTZ
    FISH_EYE_MOUSE_E = 1,              //���
	FISH_EYE_FUNC_E  = 2,              //���ܰ�ť
    FISH_EYE_BUTT
}FishControlFlag_E;

typedef struct 
{
    FISH_PTZ_E eFlag;                   //FISH_PTZ_LEFT --- FISH_PTZ_RIGHTDOWN
    float      speed;                   //ptz��ǰ��λ�ƶ����ٶ� 1~10
	float      k;                       //ptz����-1~+1 	FISH_PTZ_ZOOMINC --- FISH_PTZ_ZOOMDEC
	bool       bEnable;                 //ʹ�ܿ���
}FISH_EYE_PTZ_S;

typedef struct 
{
	FISH_MOUSE_E eFlag;                 //FISH_MOUSE_MOVE --- FISH_MOUSE_LBUTTONDBLCLK
    float        x;						//����϶���x��С
    float        y;						//����϶���y��С
	float        value;                 //���β����Ŵ���С�仯ֵ
}FISH_EYE_MOUSE_S;

typedef struct
{
	FISH_FUNC_E eFlag;                  //FISH_FUNC_CHNSELECT --- FISH_FUNC_PREVIEW
	bool bEnable;                       //FISH_FUNC_PREVIEW ʹ��
	FISH_SNAPSHOT_E enSnapShotType;     //FISH_FUNC_SNAPSHOT
	char String[256];                   //FISH_FUNC_SNAPSHOT
	unsigned char ChnSelect;            //FISH_FUNC_CHNSELECT ѡ�еĴ���
}FISH_EYE_FUNC_S;

typedef struct _FISH_CONTROL_REQ_S_ 
{
    int                 channel;
    FishControlFlag_E   eFlag;
    int                 width;         // UI width
    int                 height;        // UI height
    union 
	{
        FISH_EYE_PTZ_S   stPtz;
        FISH_EYE_MOUSE_S stMouse;
		FISH_EYE_FUNC_S  stFunc;
    };
}FISH_CONTROL_REQ_S;

#endif