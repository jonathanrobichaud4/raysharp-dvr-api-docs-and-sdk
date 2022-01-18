#pragma once

#include "../DeviceManager/RSDevice.h"

//#define  GET_DATA_SUC   "suc"
//typedef unsigned long long stdcUint64;

class CRSDevice;
class CParamRemoteTest
{
public:
	CParamRemoteTest(void);
	virtual ~CParamRemoteTest(void);
public:
	LONG ParamRemoteTest(int nSubType, const Json::Value& val);
private:
	static void RSNET_CALL RSRemoteTestCallback(WORD type, void* data, UINT size, void* userParam);
	BOOL RemoteTestEventProcess(UINT type , void* data , int size);

public:
    CRSDevice* m_pDevice;
private:
	RSRemoteMsgHandle m_RemoteMsgHandle;
};
