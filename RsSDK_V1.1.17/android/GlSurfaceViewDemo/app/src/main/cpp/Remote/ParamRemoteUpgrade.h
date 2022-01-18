#pragma once

#include "../DeviceManager/RSDevice.h"

//#define  GET_DATA_SUC   "suc"
//typedef unsigned long long stdcUint64;

class CRSDevice;
class CParamRemoteUpgrade
{
public:
	CParamRemoteUpgrade(void);
	virtual ~CParamRemoteUpgrade(void);
public:
	LONG StartRemoteUpgrade(std::string strPath, LONG channelmask, LONG filetype,int time_sleep,UINT *channelmask_EX = NULL);
	LONG StopRemoteUpgrade();
	BOOL RemoteUpgradeEventProcess(UINT type, long percent);
private:
	static void  RSNET_CALL RemoteUpgradeCallback(UINT type, void* param, void* userParam);

public:
    CRSDevice* m_pDevice;
	RSNetRemoteUpgrade m_gUpgrade;
	int m_upgradeType;
};
