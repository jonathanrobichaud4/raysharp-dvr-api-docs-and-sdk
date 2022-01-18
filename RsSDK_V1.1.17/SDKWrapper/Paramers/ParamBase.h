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
	//ˢ��All
		virtual std::string QueryAll(bool bDefault=false)//��ѯ����ͨ��
		{
			return (std::string)"err";
		}

		virtual std::string QueryAll(std::string strData)//��ѯ����ͨ�����������Ĳ�ѯ(DevLogҳ��)
		{
			return (std::string)"err";
		}

		virtual std::string GetAll()//�ѱ����ڲ��������ݣ�������ҳ
		{
			return (std::string)"err";
		}

	//ˢ��One
		virtual std::string QueryOne(int n)//��ѯand��ȡ����ͨ��
		{
			return (std::string)"err";
		}

		virtual std::string GetOne(int n)//��ȡ����ͨ��
		{
			return (std::string)"err";
		}
	
	//����
	virtual std::string QueryAll2()//1��ҳ��������ˢ��(IPCҳ��)
	{
		return "err";
	}	

	//����
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

	//��ѯ ����ͨ��All ʱ��ת��
	static inline void TransformChannelParamReq_All(ChannelParamReq* req);
	//��ѯ ����ͨ��One ʱ��ת��
	static inline void TransformChannelParamReq_One(ChannelParamReq* req, int nChannelNo);
public:
    CRSDevice* m_pDevice;
	Json::Value m_obj;
};

//��ѯ ����ͨ��All ʱ��ת��
void CParamBase::TransformChannelParamReq_All(ChannelParamReq* req) {
	int nStructSize = sizeof(ChannelParamReq);

	memset(req, 0xff, nStructSize); 

	req->StructSize = nStructSize;
}

//��ѯ ����ͨ��One ʱ��ת��
void CParamBase::TransformChannelParamReq_One(ChannelParamReq* req, int nChannelNo) {
	int nStructSize = sizeof(ChannelParamReq);

	memset(req, 0, nStructSize);
	req->StructSize = nStructSize;

	if (nChannelNo <= (nStructSize-4)*8) {//ͨ�����ܳ��� 256 //(36-4)*8=256
		//20· req->ChannelMask[0] = 0x1 << (20);
		//40· req->ChannelMask[1] = 0x1 << (8);
		req->ChannelMask[nChannelNo/32] = 0x1 << (nChannelNo%32);
	}else{
		//��������
		char* p = NULL;
		*p = 'A';
	}
}
