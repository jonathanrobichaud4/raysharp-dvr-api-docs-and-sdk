
#ifndef _COMMON_TYPE_H_
#define _COMMON_TYPE_H_

/*platform type*/
#if defined (_MSC_VER)
#define WINDOWS_PLATFORM 
#elif defined (__APPLE__)
#include <TargetConditionals.h>
#define APPLE_PLATFORM
#if TARGET_OS_IPHONE
#define FISHEYE_OPENGL_ES
#else
#define FISHEYE_OPENGL
#endif
#elif defined (__ANDROID__)
#define ANDROID_PLATFORM
#define FISHEYE_OPENGL_ES
#else
//#define HI_PLATFORM
#define FISHEYE_OPENGL_ES
#endif

#ifdef _MSC_VER
#include <Windows.h>
#if (defined WIN32 || defined _WIN32 || defined WINCE)
#define INT_EXPORTS _declspec(dllexport)
#else
#define INT_EXPORTS _declspec(dllimport)
#endif
#else
#define INT_EXPORTS
#endif

typedef enum rsFISHEYE_PIXEL_FORMAT_E
{
    RSFISHPIXEL_FORMAT_RGB_1BPP = 0,
    RSFISHPIXEL_FORMAT_RGB_2BPP,
    RSFISHPIXEL_FORMAT_RGB_4BPP,
    RSFISHPIXEL_FORMAT_RGB_8BPP,
    RSFISHPIXEL_FORMAT_RGB_444,

    RSFISHPIXEL_FORMAT_RGB_4444,
    RSFISHPIXEL_FORMAT_RGB_555,
    RSFISHPIXEL_FORMAT_RGB_565,
    RSFISHPIXEL_FORMAT_RGB_1555,

    /*  9 reserved */
    RSFISHPIXEL_FORMAT_RGB_888,
    RSFISHPIXEL_FORMAT_RGB_8888,

    RSFISHPIXEL_FORMAT_RGB_PLANAR_888,
    RSFISHPIXEL_FORMAT_RGB_BAYER_8BPP,
    RSFISHPIXEL_FORMAT_RGB_BAYER_10BPP,
    RSFISHPIXEL_FORMAT_RGB_BAYER_12BPP,
    RSFISHPIXEL_FORMAT_RGB_BAYER_14BPP,

    RSFISHPIXEL_FORMAT_RGB_BAYER,         /* 16 bpp */

    RSFISHPIXEL_FORMAT_YUV_A422,
    RSFISHPIXEL_FORMAT_YUV_A444,

    RSFISHPIXEL_FORMAT_YUV_PLANAR_422,
    RSFISHPIXEL_FORMAT_YUV_PLANAR_420,

    RSFISHPIXEL_FORMAT_YUV_PLANAR_444,

    RSFISHPIXEL_FORMAT_YUV_SEMIPLANAR_422,
    RSFISHPIXEL_FORMAT_YUV_SEMIPLANAR_420,
    RSFISHPIXEL_FORMAT_YUV_SEMIPLANAR_444,

    RSFISHPIXEL_FORMAT_UYVY_PACKAGE_422,
    RSFISHPIXEL_FORMAT_YUYV_PACKAGE_422,
    RSFISHPIXEL_FORMAT_VYUY_PACKAGE_422,
    RSFISHPIXEL_FORMAT_YCbCr_PLANAR,

    RSFISHPIXEL_FORMAT_YUV_400,

    RSFISHPIXEL_FORMAT_BUTT
} FISHEYE_PIXEL_FORMAT_E;

typedef enum rsFISHEYE_FRAME_FORMAT_E
{
    RSFISHFRAME_TYPE_FISHEYE = 0,
    RSFISHFRAME_TYPE_NORMAL = 1,
    RSFISHFRAME_TYPE_BUTT
}FISHEYE_FRAME_FORMAT_E;

typedef struct rsPersProjInfo
{
    float FOV;
    float Width; 
    float Height;
    float zNear;
    float zFar;
}PersProjInfo;

typedef struct rsOrthoProjInfo_S
{
    float l;        // left
    float r;        // right
    float b;        // bottom
    float t;        // top
    float n;        // z near
    float f;        // z far
}OrthoProjInfo_S;

#endif