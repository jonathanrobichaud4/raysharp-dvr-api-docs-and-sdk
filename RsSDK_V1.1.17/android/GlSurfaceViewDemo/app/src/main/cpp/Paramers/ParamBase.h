#pragma once

#include "../DeviceManager/RSDevice.h"

#ifdef _MSC_VER
#  define RS_WINDOWS
#elif defined(__APPLE__)
#  include <TargetConditionals.h>
#  if TARGET_OS_IPHONE
#    define RS_IPHONE
#  else
#    define RS_MACOS
#  endif
#elif defined(__ANDROID__)
#  define RS_ANDROID
#endif

#if defined(RS_IPHONE)||defined(RS_ANDROID)
#include "base64.h"
#endif

#define  GET_DATA_SUC   "suc"
typedef unsigned long long stdcUint64;

class CRSDevice;
class CParamBase
{
public:
	CParamBase(void);
	virtual ~CParamBase(void);
public:
	//刷新All
		virtual std::string QueryAll(bool bDefault=false)//查询所有通道
		{
			return (std::string)"err";
		}

		virtual std::string QueryAll(std::string strData)//查询所有通道，带条件的查询(DevLog页面)
		{
			return (std::string)"err";
		}

		virtual std::string GetAll()//把保存在插件里的数据，传给网页
		{
			return (std::string)"err";
		}

	//刷新One
		virtual std::string QueryOne(int n)//查询and获取单个通道
		{
			return (std::string)"err";
		}

		virtual std::string GetOne(int n)//获取单个通道
		{
			return (std::string)"err";
		}
	
	//特殊
	virtual std::string QueryAll2()//1个页面有两个刷新(IPC页面)
	{
		return "err";
	}	

	//保存
		virtual int SaveAll(std::string staData)
		{
			return 1;
		}

		virtual int SaveOne(int n,std::string staData)
		{
			return 1;
		}

		virtual int ModifyPassword(std::string staData)
		{
			return 1;
		}

	//查询 所有通道All 时的转换
	static inline void TransformChannelParamReq_All(ChannelParamReq* req);
	//查询 单个通道One 时的转换
	static inline void TransformChannelParamReq_One(ChannelParamReq* req, int nChannelNo);
public:
    CRSDevice* m_pDevice;
	Json::Value m_obj;
};

//查询 所有通道All 时的转换
void CParamBase::TransformChannelParamReq_All(ChannelParamReq* req) {
	int nStructSize = sizeof(ChannelParamReq);

	memset(req, 0xff, nStructSize); 

	req->StructSize = nStructSize;
}

//查询 单个通道One 时的转换
void CParamBase::TransformChannelParamReq_One(ChannelParamReq* req, int nChannelNo) {
	int nStructSize = sizeof(ChannelParamReq);

	memset(req, 0, nStructSize);
	req->StructSize = nStructSize;

	if (nChannelNo <= (nStructSize-4)*8) {//通道不能超过 256 //(36-4)*8=256
		//20路 req->ChannelMask[0] = 0x1 << (20);
		//40路 req->ChannelMask[1] = 0x1 << (8);
		req->ChannelMask[nChannelNo/32] = 0x1 << (nChannelNo%32);
	}else{
		//让它出错
		char* p = NULL;
		*p = 'A';
	}
}
