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

#define MAX_FISHEYE_CHN 9	//最大分屏数目
#define MAX_FISHEYE_DEV 1	//最大设备数目

/*固定模式搭配*/
typedef enum rsFISHEYE_COMB_TYPE_E
{
	FISH_CEILING_EYE = 0,		// 吸顶+鱼眼                  [FishEye]
	FISH_CEILING_VR,	        // 吸顶+VR碗状                [VR]
	FISH_CEILING_CYLIND3D,      // 吸顶+VR柱面                [Cylinder]
	FISH_CEILING_CYLIND360,		// 吸顶+360全景			      [Panorama 360]
	FISH_CEILING_CYLIND180,		// 吸顶+180全景               [Panorama 180]
	FISH_CEILING_2PTZ,			// 吸顶+2个PTZ                [2 PTZ]
	FISH_CEILING_4PTZ,			// 吸顶+4个PTZ         = 4    [4 PTZ]
	FISH_CEILING_CYLIND360_1PTZ,// 吸顶+360全景+1个PTZ        [Panorama 360 + 1 PTZ]
	FISH_CEILING_CYLIND360_3PTZ,// 吸顶+360全景+3个PTZ = 4    [Panorama 360 + 3 PTZ]
	FISH_CEILING_CYLIND360_6PTZ,// 吸顶+360全景+6个PTZ = 7    [Panorama 360 + 6 PTZ]
	FISH_CEILING_CYLIND360_8PTZ,// 吸顶+360全景+8个PTZ = 9    [Panorama 360 + 8 PTZ]
	FISH_CEILING_EYE_3PTZ,		// 吸顶+鱼眼+3个PTZ	   = 4    [FishEye + 3 PTZ]
	FISH_CEILING_EYE_8PTZ,		// 吸顶+鱼眼+8个PTZ    = 9    [FishEye + 8 PTZ]

	FISH_DESKTOP_EYE,			// 桌面+鱼眼                  [FishEye]
	FISH_DESKTOP_VR,	        // 桌面+VR碗状                [VR]
	FISH_DESKTOP_CYLIND3D,      // 桌面+VR柱面                [Cylinder]
	FISH_DESKTOP_CYLIND360,		// 桌面+360全景               [Panorama 360]
	FISH_DESKTOP_CYLIND180,		// 桌面+180全景               [Panorama 180]
	FISH_DESKTOP_4PTZ,			// 桌面+4个PTZ         = 4    [4 PTZ]
	FISH_DESKTOP_CYLIND360_1PTZ,// 桌面+360全景+1个PTZ        [Panorama 360 + 1 PTZ]
	FISH_DESKTOP_CYLIND360_3PTZ,// 桌面+360全景+3个PTZ = 4    [Panorama 360 + 3 PTZ]
	FISH_DESKTOP_CYLIND360_6PTZ,// 桌面+360全景+6个PTZ = 7    [Panorama 360 + 6 PTZ]
	FISH_DESKTOP_CYLIND360_8PTZ,// 桌面+360全景+8个PTZ = 9    [Panorama 360 + 8 PTZ]
	FISH_DESKTOP_EYE_3PTZ,		// 桌面+鱼眼+3个PTZ    = 4    [FishEye + 3 PTZ]
	FISH_DESKTOP_EYE_8PTZ,		// 桌面+鱼眼+8个PTZ    = 9	  [FishEye + 8 PTZ]

	FISH_WALL_EYE,				// 壁装+鱼眼				  [FishEye]
	FISH_WALL_VR,               // 壁装+VR全景				  [VR]
	FISH_WALL_NORMAL,			// 壁装+normal全景			  [Panorama]
	FISH_WALL_4PTZ,				// 壁装+4个PTZ            = 4 [4 PTZ]
	FISH_WALL_NORMAL_3PTZ,		// 壁装+normal全景+3个PTZ = 4 [Panorama + 3 PTZ]
	FISH_WALL_NORMAL_8PTZ,		// 壁装+normal全景+8个PTZ = 9 [Panorama + 8 PTZ]
	FISH_WALL_EYE_3PTZ,			// 壁装+鱼眼+3个PTZ       = 4 [FishEye + 3 PTZ]
	FISH_WALL_EYE_8PTZ,			// 壁装+鱼眼+8个PTZ       = 9 [FishEye + 8 PTZ]

	FISH_TILT_EYE,				// 倾斜+鱼眼                  [FishEye]
	FISH_TILT_VR,               // 倾斜+VR全景				  [VR]
	FISH_TILT_NORMAL,			// 倾斜+normal全景            [Panorama]
	FISH_TILT_4PTZ,				// 倾斜+4个PTZ            = 4 [4 PTZ]
	FISH_TILT_NORMAL_3PTZ,		// 倾斜+normal全景+3个PTZ = 4 [Panorama + 3 PTZ]
	FISH_TILT_NORMAL_8PTZ,		// 倾斜+normal全景+8个PTZ = 9 [Panorama + 8 PTZ]
	FISH_TILT_EYE_3PTZ,			// 倾斜+鱼眼+3个PTZ       = 4 [FishEye + 3 PTZ]
	FISH_TILT_EYE_8PTZ,			// 倾斜+鱼眼+8个PTZ       = 9 [FishEye + 8 PTZ]

	FISH_COMB_TYPE_BUTT
}FISHEYE_COMB_TYPE_E;

/*鱼眼挂机模型*/
typedef enum rsFISHEYE_MOUNT_MODE_E					
{
	RSFISHEYE_CEILING_MOUNT = 0,		//顶挂/吸顶
	RSFISHEYE_DESKTOP_MOUNT = 1,		//底挂/桌面
	RSFISHEYE_WALL_MOUNT    = 2,		//壁挂/壁装
	RSFISHEYE_TILT_MOUNT    = 3,		//壁挂/倾斜
	RSFISHEYE_MOUNT_MODE_BUTT
}RSFISHEYE_MOUNT_MODE_E;

/*应用模型*/
typedef enum rsFISHEYE_MODEL_E						
{
	FISHEYE_SPHERE		= 0,		//球面校正（顶挂，底挂，壁挂）
	FISHEYE_LATITUDE	= 1,		//壁挂模型，以及截图的三种装机模型 Latitude法
	FISHEYE_CYLINDER360 = 2,		//360度环形视图（顶挂，底挂）
	FISHEYE_CYLIND3D    = 3,        //环形柱面3d（顶挂，底挂）
	FISHEYE_SPHERE_VR   = 4,		//球形VR视图（顶挂，底挂）
	FISHEYE				= 5,        //鱼眼原图
	FISHEYE_SPHERE_RE   = 6,        //反球面模型[-1/2 1/2]，确定某个角度鱼眼范围，范围区域划线
	FISHEYE_BOUNDARY    = 7,        //反球面模型[-1 1], 对选中窗口画边界
	FISHEYE_CYLINDER180 = 8,		//180度环形视图（顶挂，底挂）
//#if !defined (WINDOWS_PLATFORM)
	FISHEYE_FLIP = 9,				//flip操作
	FISHEYE_ORIGNAL = 10,			//原图输出
//#endif
	FISHEYE_MODEL_BUTT
}FISHEYE_MODEL_E;

typedef enum rsFISHEYE_RANGE_TYPE_E
{
	FISHEYE_RANGE_CURVE,				//曲线范围
	FISHEYE_RANGE_RECT,					//方形范围
	FISHEYE_RANGE_BUTT
}FISHEYE_RANGE_TYPE_E;

/*着色器项目类型*/
typedef enum rsFISH_PROGRAM_E
{
	FISH_PROGRAM_NORMAL,
//	FISH_PROGRAM_SPHEREVR,				
//	FISH_PROGRAM_CYLINDVR,				//VR模型项目
	FISH_PROGRAM_SPHERERANGE,			//球面范围项目
	FISH_PROGRAM_CYLINDRANGE,			//柱面范围项目
	FISH_PROGRAM_LATITUERANGE,			//经纬度范围
	FISH_PROGRAM_BOUNDARY,				//矩形边界范围项目
//#if !defined (WINDOWS_PLATFORM)
	FISH_PROGRAM_FLIP,					//flip
	FISH_PROGRAM_ORIGNAL,				//原图输出
//#endif
	FISH_PROGRAM_BUTT
}FISH_PROGRAM_E;

/*截图保存格式类型*/
typedef enum rsFISH_SNAPSHOT_E
{
	FISH_SNAPSHOT_BMP = 0, //D3DXIFF_BMP
	FISH_SNAPSHOT_JPG = 1, //D3DXIFF_JPG
	FISH_SNAPSHOT_TGA = 2, //D3DXIFF_TGA
	FISH_SNAPSHOT_PNG = 3, //D3DXIFF_PNG
	FISH_SNAPSHOT_DDS = 4, //D3DXIFF_DDS   
	FISH_SNAPSHOT_BUTT
}FISH_SNAPSHOT_E;

/*鱼眼ptz控制类型*/
typedef enum rsFISH_PTZ_E
{
	FISH_PTZ_LEFT = 0,					//左
	FISH_PTZ_RIGHT,						//右
	FISH_PTZ_UP,						//上
	FISH_PTZ_DOWN,						//下
	FISH_PTZ_LEFTUP,					//左上
	FISH_PTZ_RIGHTUP,					//右上
	FISH_PTZ_LEFTDOWN,					//左下
	FISH_PTZ_RIGHTDOWN,					//右下
	FISH_PTZ_ZOOMINC,					//放大
	FISH_PTZ_ZOOMDEC,					//缩小
	FISH_PTZ_CURISE,					//轮寻
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
/*鱼眼内参*/
typedef struct rsFISH_INTRIC_PARA_S
{
	float r;								//鱼眼半径
	float cx;								//鱼眼中心 x坐标
	float cy;								//鱼眼中心 y坐标
	float ang;								//初始化角度
#if defined (HI_PLATFORM) || defined (WINDOWS_PLATFORM)
	int width[3];
	int height[3];							//图像宽高
#endif
#if defined (WINDOWS_PLATFORM)
	HWND hWnd;
#endif
	char resvd[4];
}FISH_INTRIC_PARA_S;	

/*ptz参数*/
typedef struct rsFISH_MOVE_S
{
	FISH_PTZ_E ePtz;					//ptz控制类型
	float dx;							//鼠标拖动的x大小 或 ptz单位移动的x大小，包含左右方向
	float dy;							//鼠标拖动的y大小 或 ptz单位移动的y大小，包含上下方向
	float dk;							//鼠标滚动放大缩小或 ptz当次操作放大缩小变化值

	float v;							//ptz当前单位移动的速度

	float x;							//预置位x位置
	float y;							//预置位y位置
	float k;							//预置位放大缩小倍数

	char CruiseNum;                     //第几个分屏开启巡航(1~MAX_FISHEYE_CHN, 0为没有巡航)
	char EnableNum;                     //第几个分屏开启PTZ (1~MAX_FISHEYE_CHN, 0为没有开启)
	bool bSlowDown;						//是否是处于减速状态
	char resvd[1];
}FISH_MOVE_S;

/*漫游参数*/
typedef struct rsFISH_ROAM_PARA_S
{
	float x;							//漫游中心x
	float y;							//漫游中心y
	float k;							//放大缩小倍数
//#if !defined (WINDOWS_PLATFORM)
	bool bFullScreen;					//是否为全屏
	bool bCruise;						//是否发生轮询
//#endif
	bool bDefault;                      //是否是默认参数
	char resvd[3];
}FISH_ROAM_PARA_S;

typedef struct rsFISH_RENDER_RANGE_S
{
	float x;						//渲染平面初始位置x
	float y;						//渲染平面初始位置y
	float w;						//渲染平面初始位置宽度
	float h;						//渲染平面初始位置高度
#if defined (WINDOWS_PLATFORM)
	int screen_width;               //每个分屏的宽度
	int screen_height;				//每个分屏的高度
#endif
	char resvd[4];
}FISH_RENDER_RANGE_S;

typedef struct rsROMA_ATTR_S
{
	FISHEYE_MODEL_E eModel;           //模型类型	
	FISH_ROAM_PARA_S astRoamPara;     //漫游参数
	FISH_RENDER_RANGE_S stRenderRange;//分屏范围
	OrthoProjInfo_S stOrthoProjInfo;  //正交投影参数
	float fAngle;					  //角度变化
	char resvd[4];
}ROMA_ATTR_S;

/*校正范围作图信息*/
typedef struct rsFISHEYE_RANGE_MAP_S
{
	FISH_PROGRAM_E	eFishProgramRange;		//画图所要使用的项目类型
	bool bActivate;							//画范围是否被激活

//#if 0
	//#ifdef WINDOWS_PLATFORM

	//FISHEYE_RANGE_TYPE_E enRangeType;       //画范围曲线类型
	//time_t clickTimeVal;					//单击时间
	//unsigned char u8DrawScreenNum;			//在第几个分屏上画范围
	//char resvd[2];

	//#else
//#endif

	FISHEYE_MODEL_E	eFishEyeModel;			//全景图像类型
#ifdef WINDOWS_PLATFORM
	time_t clickTimeVal;
	//timeval clickTimeVal;
#else
	struct timeval clickTimeVal;			//单击时间
#endif
	bool bDraw;								//是否要进行校正区域范围图
	unsigned char u8SelectScreenNum;		//单击选择的第几个屏幕
	unsigned char u8ScreenNum;				//在第几个分屏上进行作图
	char resvd[1];

	//#endif

}FISHEYE_RANGE_MAP_S;

/*附加功能信息*/
typedef struct rsFISHEYE_FUNC_S
{
	char String[256];				  //保存截图的路径及其名称 
	FISH_SNAPSHOT_E enSnapShotType;   //截图图片的格式
	bool bIsSnapShot;                 //是否截图，默认不截图
	bool bIsRender;                   //是否渲染，默认渲染

}FISHEYE_FUNC_S;

/*模型动态变化效果*/
typedef struct rsFISHEYE_DYNAMIC_S
{
	/*由参数0变换到参数1*/
	ROMA_ATTR_S stRoma0;		//模型0的参数(当前的模型)
	ROMA_ATTR_S stRoma1;		//模型1的参数
	float fCoef;				//两个模型变化系数，从0->1，0为当前模型，1为将要的模型,中间值为动态变化
	unsigned char u8DynamicType;//动态变化类型，0:为模型内部切换，1:为模式切换
	bool bActivate;				//动态效果是否被激活
	char resvd[2];

}FISHEYE_DYNAMIC_S;

/*鱼眼校正初始角度*/
typedef struct rsFISHEYE_INITANGLE_S
{
	bool bActivate;					//是否被激活
	float x;						//渲染平面初始位置x
	float y;						//渲染平面初始位置y
	float w;						//渲染平面初始位置宽度
	float h;						//渲染平面初始位置高度
	float fInitAngle;				//初始角度
	RSFISHEYE_MOUNT_MODE_E enFishMountMode;
}FISHEYE_INITANGLE_S;

typedef struct rsFISHEYE_ATTR_S 
{
	RSFISHEYE_MOUNT_MODE_E enFishMountMode;			//鱼眼挂机模型
	FISHEYE_COMB_TYPE_E  enFishCombType;		    //组合模式类型	
	
	unsigned char u8MultiScreen;				    //分屏数目
	unsigned char u8SelectScreenNum;		        //单击选择的第几个屏幕
	unsigned char u8FullScreen;						//第几个分屏处于全屏
	char resvd[1];
	ROMA_ATTR_S astRegionAttr[MAX_FISHEYE_CHN];     //分屏参数
	FISH_MOVE_S stFishMove;                         //PTZ操作
	FISHEYE_RANGE_MAP_S stFishRangeMap;			    //校正的范围图
	FISHEYE_DYNAMIC_S   stFishDynamic;              //动态效果
	FISHEYE_FUNC_S astFishFunc[MAX_FISHEYE_CHN];    //附加的功能
	FISHEYE_INITANGLE_S stFishInitAngle;			//初始角度控制
}RSFISHEYE_ATTR_S; 

typedef struct rsIMAGE_S
{
	FISHEYE_PIXEL_FORMAT_E ePixFormat;					//像素类型
#if !defined (WINDOWS_PLATFORM)
	FISHEYE_FRAME_FORMAT_E eFrameFormat;				//帧类型，普通frame,鱼眼frame
#endif
	unsigned char* pDataAddr[3];						//虚拟地址
	unsigned int u32PhyAddr[3];							//物理地址
	int width[3];										//图像宽
	int height[3];										//图像高
	int stride[3];										//跨度
	int timeRef;										//时间参考
	void* pPrivate;										//
	char resvd[4];
}IMAGE_S;

typedef struct rsFISH_OUT_INFO_S
{
	int imgNum;									//输出图像数目
	IMAGE_S stFishImgOut[MAX_FISHEYE_CHN];		//输出图像信息
	char resvd[4];
}FISH_OUT_INFO_S;



	//HGLRC hglrc;  // rendering context
	//HDC   hdc;    // device context


/*鱼眼鼠标控制类型*/
typedef enum rsFISH_MOUSE_E
{
	FISH_MOUSE_MOVE = 0,               //滑动
	FISH_MOUSE_WHEEL,                  //滚轮
	FISH_MOUSE_LBUTTONDOWN,            //左键单击
	FISH_MOUSE_LBUTTONUP,              //左键释放
	FISH_MOUSE_LBUTTONDBLCLK,          //左键双击left button double click
	FISH_MOUSE_RBUTTONDBLCLK,          //右键双击right button double click
	FISH_MOUSE_BUTT
}FISH_MOUSE_E;

/*功能按钮控制类型*/
typedef enum rsFISH_FUNC_E
{
	FISH_FUNC_SNAPSHOT = 0, 		  //截图保存
	FISH_FUNC_PREVIEW,                //通道预览控制
	FISH_FUNC_CHNSELECT,			  //查询当前选中的分屏窗口号
	FISH_FUNC_BUTT
}FISH_FUNC_E;

/*设备控制类型*/
typedef enum _FishControlFlag_E 
{
    FISH_EYE_PTZ_E   = 0,              //PTZ
    FISH_EYE_MOUSE_E = 1,              //鼠标
	FISH_EYE_FUNC_E  = 2,              //功能按钮
    FISH_EYE_BUTT
}FishControlFlag_E;

typedef struct 
{
    FISH_PTZ_E eFlag;                   //FISH_PTZ_LEFT --- FISH_PTZ_RIGHTDOWN
    float      speed;                   //ptz当前单位移动的速度 1~10
	float      k;                       //ptz缩放-1~+1 	FISH_PTZ_ZOOMINC --- FISH_PTZ_ZOOMDEC
	bool       bEnable;                 //使能开关
}FISH_EYE_PTZ_S;

typedef struct 
{
	FISH_MOUSE_E eFlag;                 //FISH_MOUSE_MOVE --- FISH_MOUSE_LBUTTONDBLCLK
    float        x;						//鼠标拖动的x大小
    float        y;						//鼠标拖动的y大小
	float        value;                 //当次操作放大缩小变化值
}FISH_EYE_MOUSE_S;

typedef struct
{
	FISH_FUNC_E eFlag;                  //FISH_FUNC_CHNSELECT --- FISH_FUNC_PREVIEW
	bool bEnable;                       //FISH_FUNC_PREVIEW 使能
	FISH_SNAPSHOT_E enSnapShotType;     //FISH_FUNC_SNAPSHOT
	char String[256];                   //FISH_FUNC_SNAPSHOT
	unsigned char ChnSelect;            //FISH_FUNC_CHNSELECT 选中的窗口
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