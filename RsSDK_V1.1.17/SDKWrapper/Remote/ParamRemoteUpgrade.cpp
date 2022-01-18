#include "StdAfx.h"
#include "ParamRemoteUpgrade.h"

CParamRemoteUpgrade::CParamRemoteUpgrade(void)
{
	m_pDevice = NULL;
	m_gUpgrade = NULL;
	m_upgradeType = 0;
}

CParamRemoteUpgrade::~CParamRemoteUpgrade(void)
{
}

BOOL CParamRemoteUpgrade::RemoteUpgradeEventProcess(UINT type, long percent)
{
	int status = -1;
	switch(type)
	{
	case RSNetMsgRemoteUpgradeClosed://升级断开
		{
			status = RSNetMsgRemoteUpgradeClosed;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgradeOK://升级完成
		{
			status = RSNetMsgRemoteUpgradeOK;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgradeReadFileFail://读取升级文件失败
		{
			status = RSNetMsgRemoteUpgradeReadFileFail;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgradeInvalidFile://不合法的升级文件
		{
			status = RSNetMsgRemoteUpgradeInvalidFile;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgradePercent:
	case RSNetMsgRemoteUpgradeIPCPercent:
		{
			status = percent;
		}
		break;
	case RSNetMsgRemoteUpgradeVerError://升级文件跟设备部匹配或是版本太低
		{
			status = RSNetMsgRemoteUpgradeVerError;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgrading://设备正在升级
		{
			status = RSNetMsgRemoteUpgrading;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgradeVerSame://版本是最新的，没必要升级
		{
			status = RSNetMsgRemoteUpgradeVerSame;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteUpgradeLanguageError://无法升级为多国语言
		{
			status = RSNetMsgRemoteUpgradeLanguageError;
			//StopRemoteUpgrade();
		}
		break;
	case RSNetMsgRemoteInUserInterface: //本地用户正在操作
		{
			status = RSNetMsgRemoteInUserInterface;
			//StopRemoteUpgrade();
		}
		break;
	case MsgRemoteUpgradeWriteFlashInProgress://开始写flash
		{
			status = MsgRemoteUpgradeWriteFlashInProgress;
		}
		break;
	default:
		break;
	}	

	if( m_pDevice != NULL){
		Json::Value obj(Json::objectValue);
		obj["status"] = status;
		obj["upgradetype"] = m_upgradeType;
		m_pDevice->SendMsgToWeb(MsgNoType,MsgRemoteUpgradeEvent,obj,NULL);//×ó￡??÷￡?json,void* param
	}
	return TRUE;
}

void  RSNET_CALL CParamRemoteUpgrade::RemoteUpgradeCallback(UINT type, void* param, void* userParam)
{
	CParamRemoteUpgrade* pThis = (CParamRemoteUpgrade*)userParam;
	if (pThis != NULL){
		UINT pos = UINT(param);
		if(type == RSNetMsgRemoteUpgradeIPCPercent && pThis->m_upgradeType == 1)
		{
			RS_UGIpcRsp_t *ugipc = (RS_UGIpcRsp_t*)param;
			pos = (ugipc->channelNo) | ugipc->status<<16;
		}
		pThis->RemoteUpgradeEventProcess(type,(long)pos);
	}
}

LONG CParamRemoteUpgrade::StartRemoteUpgrade( std::string strPath, LONG channelmask, LONG filetype, int time_sleep ,UINT *channenlmask_EX)
{
	if (m_gUpgrade == NULL){

		RSNetRemoteUpgradeParamEx param = {0};
		param.FileName = strPath.c_str();
		param.UserParam = this;
		param.Callback = RemoteUpgradeCallback;
		param.time_sleep = time_sleep;
		if(m_pDevice != NULL){
			LoginRsp* logRsp = m_pDevice->GetLoginRsp();
			if(filetype == 0){
				m_upgradeType = 0;
				if( logRsp != NULL && logRsp->UpgradeType)
					param.filetype = 3;//3 NVR new upgrade,4 urmet ipc,5 raysharp ipc
			}else if(filetype == 7){
				m_upgradeType = 0;
				param.filetype = filetype;//sxEncryptionUpgrade(srp6 upgrade)
			}else{
				m_upgradeType = 1;
				param.filetype = filetype;
				param.nChannelMask = channelmask;
				memcpy(param.ChannelMask_EX,channenlmask_EX,sizeof(param.ChannelMask_EX));
			}
			m_gUpgrade = RSNetStartRemoteUpgradeEx(m_pDevice->GetConnection(), &param);
			if (m_gUpgrade != NULL){
				return 0;
			}
		}
	}
	return -1;
}

LONG CParamRemoteUpgrade::StopRemoteUpgrade()
{
	if (m_gUpgrade != NULL){
		RSNetStopRemoteUpgrade(&m_gUpgrade);
		m_gUpgrade = NULL;
	}
	return 0;
}
