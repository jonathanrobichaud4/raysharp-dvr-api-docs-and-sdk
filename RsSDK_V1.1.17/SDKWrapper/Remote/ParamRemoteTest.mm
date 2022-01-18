#include "StdAfx.h"
#include "ParamRemoteTest.h"

CParamRemoteTest::CParamRemoteTest(void)
{
	m_pDevice = NULL;
	m_RemoteMsgHandle = 0;
}

CParamRemoteTest::~CParamRemoteTest(void)
{
}

void RSNET_CALL CParamRemoteTest::RSRemoteTestCallback(WORD type, void* data, UINT size, void* userParam)
{
	CParamRemoteTest* pThis = (CParamRemoteTest*)userParam;
	if (pThis != NULL){
		pThis->RemoteTestEventProcess(type,data,size);
	}

// 	RemoteTestInfo* pRemoteTestInfo = (RemoteTestInfo*)userParam;
// 	if(pRemoteTestInfo != NULL){
// 		int devid = pRemoteTestInfo->DevId;
// 		CParamRemoteTest* pThis = (CParamRemoteTest*)pRemoteTestInfo->UserParam;
// 		if (pThis != NULL){
// 			pThis->RemoteTestEventProcess(type,data,size,devid);
// 		}
// 	}
}

BOOL CParamRemoteTest::RemoteTestEventProcess(UINT type , void* data , int size)
{
	if (data == NULL)
	{
		return FALSE;
	}
	if (size == 0)
	{
		if(MsgRoutePeat == type || MsgNewStreamset == type || MsgRemoteOneKeyAddIPC == type)
		{
			//大小为0时，表示搜索到的数据的条数为0
		}
		else
		{
			return FALSE;
		}
	}
	
	Json::FastWriter writer;
	Json::Value rspData(Json::objectValue);

	if(type == MsgHddFormat)//309
	{
		HddFormatRsp  hddRsp = {0};
		memcpy(&hddRsp,data,sizeof(HddFormatRsp)>size?size:sizeof(HddFormatRsp));
		rspData["State"] = hddRsp.HddFormatStatue;
		rspData["Process"] = hddRsp.HddFormatProcess;
		rspData["HddNO"] = hddRsp.HddNO;
	}
	else if(type == MsgActivateCloud)//321
	{
		ActivateCloudRsp Cloudrsp = {0};
		memcpy(&Cloudrsp,data,sizeof(ActivateCloudRsp)>size?size:sizeof(ActivateCloudRsp));
		rspData["ErrCode"] = Cloudrsp.ErrCode;
		rspData["InfoFlag"] = Cloudrsp.InfoFlag;
		rspData["RetMsg"] = (char*)Cloudrsp.RetMsgInfo;
	}	
	else if(type == MsgClientAutoLogout)//366
	{
		int test = 6;
	}
	else if(type == MsgRemoteCheck)//337
	{
		RemoteCheckRsp  CheckRsp = {0};
		memcpy(&CheckRsp,data,sizeof(RemoteCheckRsp)>size?size:sizeof(RemoteCheckRsp));
		rspData["MainType"] = CheckRsp.MainType;
		rspData["SubType"] = CheckRsp.SubType;
		rspData["RetValue"] = CheckRsp.RetValue;
	}
	else if(type == MsgGetDDNSID)//403
	{
		GetDDNSIDRsp DDNSrsp = {0};
		memcpy(&DDNSrsp,data,sizeof(GetDDNSIDRsp)>size?size:sizeof(GetDDNSIDRsp));
		rspData["ErrCode"] = DDNSrsp.ErrCode;
		rspData["RetMsg"] = (char*)DDNSrsp.ddnsid;
	}
	else if(type == MsgRoutePeat)//420
	{
		int COUNT = size/sizeof(Routpeat_t);
		rspData["COUNT"] = COUNT;
		
		if(0 == COUNT)
		{
			//no data
		}
		else
		{
			Routpeat_t *p = new Routpeat_t[COUNT];
			memcpy(p,data,sizeof(Routpeat_t)*COUNT);

			Json::Value AllRows(Json::arrayValue);
			for(int i=0; i<COUNT; i++)
			{
				Json::Value OneRow(Json::objectValue);
				OneRow["ssid"] = (char*)p[i].ssid;
				OneRow["mac"] = (char*)p[i].mac;
				OneRow["security"] = (char*)p[i].security;
				OneRow["rssi"] = p[i].rssi;
				OneRow["pskValue"] = (char*)p[i].pskValue;
				AllRows.append(OneRow);
			}
			
			rspData["DATA"] = AllRows;

			delete [] p;
		}
	}
	else if(type == MsgNewStreamset)//425
	{
		RSNetNew_Streamset_t  streamRsp = {0};
		memcpy(&streamRsp,data,sizeof(SearchSmartCountResp)>size?size:sizeof(RSNetNew_Streamset_t));
		rspData["TotalBandWidth"] = (double)streamRsp.TotalBandWidth;
		rspData["UsedBandWidth"] = (double)streamRsp.UsedBandWidth;

	}
	else if (type == MsgSearchSmartCount)//710
	{
		SearchSmartCountResp  smartRsp = {0};
		memcpy(&smartRsp,data,sizeof(SearchSmartCountResp)>size?size:sizeof(SearchSmartCountResp));
		Json::Value data(Json::objectValue);
		for ( int i=0;i < 32; ++i ){
			data["item"] = smartRsp.report[i];
			rspData["report"].append(data);
		}
		for ( int i=0;i < 32; ++i ){
			data["item"] = smartRsp.reportExt[i];
			rspData["reportExt"].append(data);
		}
		rspData["alarmType"] = smartRsp.alarmType;
		rspData["channel"] = smartRsp.channel;
		rspData["version"] = smartRsp.version;
		rspData["filename"] = smartRsp.filename;
	}
	else if(type == MsgZeroChnStatus)	//336
	{
		ZeroChnStatRsp  zeroRsp = {0};
		memcpy(&zeroRsp,data,sizeof(ZeroChnStatRsp)>size?size:sizeof(ZeroChnStatRsp));
		rspData["SplitMode"] = zeroRsp.SplitMode;
		rspData["PreviewMode"] = zeroRsp.PreviewMode;
		Json::Value data(Json::objectValue);
		for(int i = 0;i < 32;++i)
		{
			data = zeroRsp.ChnList[i];
			rspData["ChnList"].append(data);
		}
	}
	else if(type == MSgChannelPair) //422
	{
		Channel_Pair_Return channel_pair_return = {0};
		memcpy(&channel_pair_return, data, sizeof(Channel_Pair_Return) > size? size:sizeof(Channel_Pair_Return));
		rspData["ErrorCode"] = channel_pair_return.error_code;
	}
	else if(type == MsgParamPir)
	{
        RSNet_SolePirMotionSet_t* temp_pir_data = (RSNet_SolePirMotionSet_t*)data;
        int struct_size = temp_pir_data->StructSize;
        int total_size = 0;
        char* begin_data = (char*)data;
        Json::Value data(Json::objectValue);
        while (total_size < size) {
            RSNet_SolePirMotionSet_t* pir_data = (RSNet_SolePirMotionSet_t*)begin_data;
            data = pir_data->PIRFlag;
            rspData["PirFlag"].append(data);
            total_size += struct_size;
            begin_data += struct_size;
        }
    }
	else if(type == MsgIMPReq)	//436
	{
		RS_ImpInfo_t  impRsp = {0};
		memcpy(&impRsp,data,sizeof(RS_ImpInfo_t)>size?size:sizeof(RS_ImpInfo_t));
		int getOrset = impRsp.getOrset;
		int type = impRsp.type;
		rspData["subType"] = getOrset;
		rspData["type"] = type;
		if (getOrset == 0)//get
		{
			if (type == 0)
			{
				rspData["CtrlAlgName"] = (char*)impRsp.ImpCtrl.algName;
				rspData["CtrlAlgEnable"] = impRsp.ImpCtrl.algCtrl;
			}
			else if (type == 1)
			{
				Json::Value data(Json::objectValue);
				for(int i = 0;i < 4;++i)
				{
					data["type"] = impRsp.ImpMode.mode[i].type;
					data["isSet"] = impRsp.ImpMode.mode[i].isSet;
					data["param"] = (char*)impRsp.ImpMode.mode[i].param;
					rspData["modeParam"].append(data);
				}
			}
			else if (type == 2)
			{
				rspData["alg_num"] = impRsp.ImpList.alg_num;
				Json::Value temp(Json::objectValue);
				for(int i = 0;i < 8;++i)
				{
					temp["alg_list"] = (char*)impRsp.ImpList.alg_list[i];
					temp["alg_status"] = impRsp.ImpList.alg_status[i];
					rspData["statusParam"].append(temp);
				}
			}
			else if (type == 3)
			{
				rspData["paramAlgName"] = (char*)impRsp.ImpLive.AlgName;
				rspData["algParam"] = (char*)impRsp.ImpLive.algParam;
			}
		}
		else if (getOrset == 1) //set
		{
			
		}
	}
	else if(type == MsgValidIPTest)	//365
	{
		RSNet_IsValidIP_t  ipRsp = {0};
		memcpy(&ipRsp,data,sizeof(RSNet_IsValidIP_t)>size?size:sizeof(RSNet_IsValidIP_t));
		rspData["ipValid"] = ipRsp.valid;
	}
	else if (type == MsgDeleteLog)
	{
		DeleteLogRsp logRsp = {0};
		memcpy(&logRsp,data,sizeof(DeleteLogRsp)>size?size:sizeof(DeleteLogRsp));
		rspData["RetVal"] = logRsp.ack;
	}
	else if (type == MsgGetSDAlarm)
	{
		RsNet_GetSDAlarmValueReq_t sdAlarmRsp = {0};
		memcpy(&sdAlarmRsp,data,sizeof(RsNet_GetSDAlarmValueReq_t)>size?size:sizeof(RsNet_GetSDAlarmValueReq_t));
		rspData["RetVal"] = sdAlarmRsp.sdvalue;
	}
	else if (type == FtpUpgradeTest) //626
    {
        FtpUpgradeStatus ftpUpgradeStatus = {0};
        memcpy(&ftpUpgradeStatus, data,
               sizeof(FtpUpgradeStatus) > size ? size : sizeof(FtpUpgradeStatus));
        rspData["status"] = ftpUpgradeStatus.status;
    }
	else
	{
		TestRsp  rsp = {0};
		memcpy(&rsp,data,sizeof(TestRsp)>size?size:sizeof(TestRsp));
		rspData["RetVal"] = rsp.RetVal;
		rspData["RetMsg"] = (char*)rsp.RetMsg;
	}

	//m_strRemoteTestRsp = writer.write(rspData).c_str();
	//CRSDevice* pDevice = NULL;
	//CRSDeviceManager& DeviceManager = Singleton<CRSDeviceManager>::instance();
	//pDevice = DeviceManager.GetDevice(devid);
	if( m_pDevice != NULL){
		m_pDevice->SendMsgToWeb(type,MsgRemoteTestEvent,rspData,NULL);//子，主，json，void* param
	}

	return TRUE;
}

LONG CParamRemoteTest::ParamRemoteTest(int nSubType, const Json::Value& data)
{
	RSNetRemoteTestParam param;
	ZeroMemory(&param,sizeof(param));

	EmailTestReq EmailReq;
	ZeroMemory(&EmailReq,sizeof(EmailReq));

	NewEmailTestReq NewEmailReq;
	ZeroMemory(&NewEmailReq,sizeof(NewEmailReq));

	DDNSTestReq DDNSReq;
	ZeroMemory(&DDNSReq,sizeof(DDNSReq));

	FtpWriteFileTestReq FtpReq;
	ZeroMemory(&FtpReq,sizeof(FtpReq));

	HddFormatReq HddReq;
	ZeroMemory(&HddReq,sizeof(HddReq));

	RebootIpcReq IpcRemoteReq;
	ZeroMemory(&IpcRemoteReq,sizeof(IpcRemoteReq));

	SGManualUploadReq SGReq;
	ZeroMemory(&SGReq,sizeof(SGReq));

	RemoteCheckReq CheckReq;
	ZeroMemory(&CheckReq,sizeof(CheckReq));

	SearchSmartCountReq SCReq;
	ZeroMemory(&SCReq,sizeof(SCReq));

	Routpeat_t routP;
	ZeroMemory(&routP,sizeof(routP));

	ZeroChnStatReq ZeroReq;
	ZeroMemory(&ZeroReq,sizeof(ZeroReq));

	Channel_Pair channel_pair;
	ZeroMemory(&channel_pair,sizeof(channel_pair));
	
	ChannelParamReq pir_req;
    memset(&pir_req, 0xff, sizeof(pir_req));

	RS_ImpInfoReq_t IMPGetReq;
	ZeroMemory(&IMPGetReq,sizeof(IMPGetReq));

	RS_ImpInfo_t IMPSetReq;
	ZeroMemory(&IMPSetReq,sizeof(IMPSetReq));

	RSNet_IsValidIP_t ValidIPReq;
	ZeroMemory(&ValidIPReq,sizeof(ValidIPReq));

	RsNet_GetSDAlarmValueReq_t soundAlarmReq;
	ZeroMemory(&soundAlarmReq,sizeof(soundAlarmReq));

	ActivateCloudRsp ActivateCloudReq;
	ZeroMemory(&ActivateCloudReq,sizeof(ActivateCloudReq));

// 	if(m_pRemoteTestInfo == NULL){
// 		m_pRemoteTestInfo = new RemoteTestInfo;
// 	}
// 	m_pRemoteTestInfo->DevId = devid ;
// 	m_pRemoteTestInfo->UserParam = this ;

	if(MsgEmailTest == nSubType || MsgNewEmailTest==nSubType  || MsgStopEmailTest==nSubType)//301
	{
		if(!data["TestType"].isNull())
			EmailReq.TestType = data["TestType"].asUInt();
		if(!data["SSLSwitch"].isNull())
			EmailReq.Ssl = data["SSLSwitch"].asInt();
		if(!data["Port"].isNull())
			EmailReq.Port = data["Port"].asInt();

		int maxLen = 0;
		if(!data["SMTP"].isNull())
		{
			maxLen = sizeof(EmailReq.Server);
			memset(EmailReq.Server, 0, maxLen);
			std::string str = data["SMTP"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.Server, str.c_str(), len);
		}

		if(!data["username"].isNull())
		{
			maxLen = sizeof(EmailReq.username);
			memset(EmailReq.username, 0, maxLen);
			std::string str = data["username"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.username, str.c_str(), len);
		}

		if(!data["SendEmail"].isNull())
		{
			maxLen = sizeof(EmailReq.Sender);
			memset(EmailReq.Sender, 0, maxLen);
			std::string str = data["SendEmail"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.Sender, str.c_str(), len);
		}

		if(!data["SendEmailPW"].isNull())
		{
			maxLen = sizeof(EmailReq.Password);
			memset(EmailReq.Password, 0, maxLen);
			std::string str = data["SendEmailPW"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.Password, str.c_str(), len);
		}

		if(!data["RecvEmail"].isNull())
		{
			maxLen = sizeof(EmailReq.Receiver);
			memset(EmailReq.Receiver, 0, maxLen);
			std::string str = data["RecvEmail"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.Receiver, str.c_str(), len);
		}

		if(!data["RecvEmail"].isNull())
		{
			maxLen = sizeof(EmailReq.RecvEmail[0]);
			memset(EmailReq.RecvEmail[0], 0, maxLen);
			std::string str = data["RecvEmail"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.RecvEmail[0], str.c_str(), len);
		}

		if(!data["RecvEmail_1"].isNull())
		{
			maxLen = sizeof(EmailReq.RecvEmail[1]);
			memset(EmailReq.RecvEmail[1], 0, maxLen);
			std::string str = data["RecvEmail_1"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.RecvEmail[1], str.c_str(), len);
		}

		if(!data["RecvEmail_2"].isNull())
		{
			maxLen = sizeof(EmailReq.RecvEmail[2]);
			memset(EmailReq.RecvEmail[2], 0, maxLen);
			std::string str = data["RecvEmail_2"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(EmailReq.RecvEmail[2], str.c_str(), len);
		}

		if(!data["StopTest"].isNull())
		{
			EmailReq.StopTest = data["StopTest"].asUInt();
		}

		param.data = &EmailReq;
		param.dataSize = sizeof(EmailReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;

		if(m_pDevice!=NULL)
		{
			if(MsgEmailTest==nSubType || MsgNewEmailTest==nSubType)//Start
			{
				m_RemoteMsgHandle =RSNetRemoteTestEx(m_pDevice->GetConnection(), &param);
				return TRUE;
			}
			else if(MsgStopEmailTest==nSubType)//Stop
			{
				RSNetRemoteTestStopEx(m_pDevice->GetConnection(), &param,m_RemoteMsgHandle);
				return TRUE;
			}
		}
		return -1;
	}
	else if(MsgEmailTestNew == nSubType)//427    new email test 
	{
		if(!data["TestType"].isNull())
			NewEmailReq.TestType = data["TestType"].asUInt();
		if(!data["SSLSwitch"].isNull())
			NewEmailReq.Ssl = data["SSLSwitch"].asInt();
		if(!data["Port"].isNull())
			NewEmailReq.Port = data["Port"].asInt();

		int maxLen = 0;
		if(!data["SMTP"].isNull())
		{
			maxLen = sizeof(NewEmailReq.Server);
			memset(NewEmailReq.Server, 0, maxLen);
			std::string str = data["SMTP"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.Server, str.c_str(), len);
		}

		if(!data["username"].isNull())
		{
			maxLen = sizeof(NewEmailReq.username);
			memset(NewEmailReq.username, 0, maxLen);
			std::string str = data["username"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.username, str.c_str(), len);
		}

		if(!data["SendEmail"].isNull())
		{
			maxLen = sizeof(NewEmailReq.Sender);
			memset(NewEmailReq.Sender, 0, maxLen);
			std::string str = data["SendEmail"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.Sender, str.c_str(), len);
		}

		if(!data["SendEmailPW"].isNull())
		{
			maxLen = sizeof(NewEmailReq.Password);
			memset(NewEmailReq.Password, 0, maxLen);
			std::string str = data["SendEmailPW"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.Password, str.c_str(), len);
		}

		if(!data["RecvEmail"].isNull())
		{
			maxLen = sizeof(NewEmailReq.Receiver);
			memset(NewEmailReq.Receiver, 0, maxLen);
			std::string str = data["RecvEmail"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.Receiver, str.c_str(), len);
		}

		if(!data["RecvEmail"].isNull())
		{
			maxLen = sizeof(NewEmailReq.RecvEmail[0]);
			memset(NewEmailReq.RecvEmail[0], 0, maxLen);
			std::string str = data["RecvEmail"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.RecvEmail[0], str.c_str(), len);
		}

		if(!data["RecvEmail_1"].isNull())
		{
			maxLen = sizeof(NewEmailReq.RecvEmail[1]);
			memset(NewEmailReq.RecvEmail[1], 0, maxLen);
			std::string str = data["RecvEmail_1"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.RecvEmail[1], str.c_str(), len);
		}

		if(!data["RecvEmail_2"].isNull())
		{
			maxLen = sizeof(NewEmailReq.RecvEmail[2]);
			memset(NewEmailReq.RecvEmail[2], 0, maxLen);
			std::string str = data["RecvEmail_2"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(NewEmailReq.RecvEmail[2], str.c_str(), len);
		}

		if(!data["StopTest"].isNull())
		{
			NewEmailReq.StopTest = data["StopTest"].asUInt();
		}

		param.data = &NewEmailReq;
		param.dataSize = sizeof(NewEmailReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;

		if(m_pDevice!=NULL)
		{
			m_RemoteMsgHandle =RSNetRemoteTestEx(m_pDevice->GetConnection(), &param);
			return TRUE;
		}
		return -1;
	}
	else if(MsgDDNSTest == nSubType)//302
	{
		DDNSReq.Serveraddr = data["ServerAddr"].asInt();

		int maxLen = sizeof(DDNSReq.Hostname);
		memset(DDNSReq.Hostname, '\0', maxLen);
		std::string str = data["HostName"].asString();
		int len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(DDNSReq.Hostname, str.c_str(), len);
		
		maxLen = sizeof(DDNSReq.Username);
		memset(DDNSReq.Username, '\0', maxLen);
		str = data["UserName"].asString();
		len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(DDNSReq.Username, str.c_str(), len);

		maxLen = sizeof(DDNSReq.Password);
		memset(DDNSReq.Password, '\0', maxLen);
		str = data["UserPW"].asString();
		len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(DDNSReq.Password, str.c_str(), len);

		DDNSReq.s8UseDDNS = data["s8UseDDNS"].asInt();
		DDNSReq.s8CommaxUseLoginFlag = data["s8C112UseLoginFlag"].asInt();
		
		if(!data["s8IpType"].isNull()){
			DDNSReq.s8IpType = data["s8IpType"].asInt();
		}
		if(!data["s8UserUrl"].isNull()){
			maxLen = sizeof(DDNSReq.s8UserUrl);
			memset(DDNSReq.s8UserUrl, '\0', maxLen);
			str = data["s8UserUrl"].asString();
			len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(DDNSReq.s8UserUrl, str.c_str(), len);
		}

		param.data = &DDNSReq;
		param.dataSize = sizeof(DDNSReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgDDNSTest;
		param.TimeOut = 12000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgRemoteReboot == nSubType)//303
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgRemoteReboot;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgHddFormat == nSubType)//309
	{
		HddReq.ChannelBitmap = data["ChBitmap"].asUInt();
		HddReq.HddBitmap = data["HddBitmap"].asUInt();

		param.data = &HddReq;
		param.dataSize = sizeof(HddReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgHddFormat;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgAddAllDevice == nSubType)//312
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgAddAllDevice;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgActivateCloud == nSubType)//321
	{
		if(!data["RetMsgInfo"].isNull()){
			std::string str = data["RetMsgInfo"].asString();
			int len = str.length() < sizeof(ActivateCloudReq.RetMsgInfo) ? str.length() : sizeof(ActivateCloudReq.RetMsgInfo);
			memcpy(ActivateCloudReq.RetMsgInfo, str.c_str(), len);

			param.data = &ActivateCloudReq;
			param.dataSize = sizeof(ActivateCloudReq);
		}else{
			param.data = NULL;
			param.dataSize = 0;
		}
		
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgActivateCloud;
		param.TimeOut = 30000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgClientAutoLogout == nSubType)//366
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgClientAutoLogout;
		param.TimeOut = 30000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgFtpWriteFileTest == nSubType)//323
	{
		int maxLen = sizeof(FtpReq.FtpAddr);
		memset(FtpReq.FtpAddr, '\0', maxLen);
		std::string str = data["FtpIpAddr"].asString();
		int len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(FtpReq.FtpAddr, str.c_str(), len);

		FtpReq.FtpPort = data["FtpPort"].asInt();

		maxLen = sizeof(FtpReq.Username);
		memset(FtpReq.Username, '\0', maxLen);
		str = data["FtpLoginName"].asString();
		len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(FtpReq.Username, str.c_str(), len);

		maxLen = sizeof(FtpReq.Password);
		memset(FtpReq.Password, '\0', maxLen);
		str = data["FtpLoginPwd"].asString();
		len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(FtpReq.Password, str.c_str(), len);

		param.data = &FtpReq;  
		param.dataSize = sizeof(FtpReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgFtpWriteFileTest;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if (MsgCloudCheck == nSubType)//327
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgCloudCheck;
		param.TimeOut = 6000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgRebootIPC == nSubType)//329
	{
		IpcRemoteReq.ChannelMask = data["ChannelMask"].asUInt();
		if(!(data["ChannelMask_EX"].isNull())){
			for(int j = 0;j < 8;++j)
			{
				IpcRemoteReq.ChannelMask_EX[j] = (unsigned int)data["ChannelMask_EX"][j].asDouble();
			}
		}
		
		IpcRemoteReq.StructSize = sizeof(RebootIpcReq);

		param.data = &IpcRemoteReq;
		param.dataSize = sizeof(IpcRemoteReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgRebootIPC;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgIPCLoadDefault == nSubType)//330
	{
		IpcRemoteReq.ChannelMask = data["ChannelMask"].asUInt();
		if(!(data["ChannelMask_EX"].isNull())){
			for(int j = 0;j < 8;++j)
			{
				IpcRemoteReq.ChannelMask_EX[j] = (unsigned int)data["ChannelMask_EX"][j].asDouble();
			}
		}
		
		IpcRemoteReq.StructSize = sizeof(RebootIpcReq);

		param.data = &IpcRemoteReq;
		param.dataSize = sizeof(IpcRemoteReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgIPCLoadDefault;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgRemoteOneKeyAddIPC == nSubType)//333
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgRemoteOneKeyAddIPC;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgSGManualUpload == nSubType)//334
	{
		SGReq.mode = data["mode"].asUInt();
		SGReq.StructSize = sizeof(SGManualUploadReq);

		if(SGReq.mode == 0)
		{
			SGReq.Repaire.RepaireType = data["RepaireType"].asUInt();
			SGReq.Repaire.ErrorType = data["ErrorType"].asUInt();

			int maxLen = sizeof(SGReq.Repaire.caption);
			memset(SGReq.Repaire.caption, '\0', maxLen);
			std::string str = data["caption"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(SGReq.Repaire.caption, str.c_str(), len);

		}
		else if(SGReq.mode == 1)
		{
			SGReq.Maintain.EquipMaintain = data["EquipMaintain"].asUInt();
			SGReq.Maintain.MaintainRes = data["MaintainRes"].asUInt();

			int maxLen = sizeof(SGReq.Maintain.caption);
			memset(SGReq.Maintain.caption, '\0', maxLen);
			std::string str = data["caption"].asString();
			int len = str.length() < maxLen ? str.length() : maxLen;
			memcpy(SGReq.Maintain.caption, str.c_str(), len);
		}
		else if(SGReq.mode == 2)
		{
			SGReq.PicUpload.ChannelMask = data["ChannelMask"].asUInt();
			SGReq.PicUpload.type = data["type"].asUInt();
		}

		param.data = &SGReq;
		param.dataSize = sizeof(SGManualUploadReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 6000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	if(MsgRemoteCheck == nSubType)//337
	{
		CheckReq.ReqType = data["ReqType"].asUInt();
		CheckReq.ReqSubType = data["ReqSubType"].asUInt();
		CheckReq.ReqMsgSize = 0;

		param.data = &CheckReq;
		param.dataSize = sizeof(CheckReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgRemoteCheck;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgGetDDNSID == nSubType)//403
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgRoutePeat == nSubType)//420
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgRouteAdd == nSubType)//421
	{
		std::string str = data["ssid"].asString();
		int len = str.length() < sizeof(routP.ssid) ? str.length() : sizeof(routP.ssid);
		memcpy(routP.ssid, str.c_str(), len);

		std::string str2 = data["pskValue"].asString();
		int len2 = str2.length() < sizeof(routP.pskValue) ? str2.length() : sizeof(routP.pskValue);
		memcpy(routP.pskValue, str2.c_str(), len2);

		param.data = &routP;
		param.dataSize = sizeof(routP);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 60000;
		param.UserParam = this;
	}
	else if(MSgChannelPair == nSubType)// 422
	{
		channel_pair.StructSize = sizeof(channel_pair);
		channel_pair.channel = data["channel"].asInt();
		param.data = &channel_pair;
		param.dataSize = sizeof(channel_pair);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MSgChannelPair;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if (MsgParamPir == nSubType)//367
    {
        pir_req.StructSize = sizeof(pir_req);
        
        param.data = &pir_req;
        param.dataSize = sizeof(pir_req);
        param.remoteTestCallback = RSRemoteTestCallback;
        param.type = MsgParamPir;
        param.TimeOut = 10000;
        param.UserParam = this;
    }
	else if(MsgNewStreamset == nSubType)//425
	{
		param.data = NULL;
		param.dataSize = 0;
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = nSubType;
		param.TimeOut = 60000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
	else if(MsgSearchSmartCount == nSubType){//710
		std::string startTime = data["startTime"].asString();
		std::size_t index = startTime.find("-");
		std::string strYear = startTime.substr(0,index);
		startTime.erase(0,index + 1) ;
		index = startTime.find("-");
		std::string strMonth = startTime.substr(0,index);
		startTime.erase(0,index + 1) ;
		std::string strDay = startTime;

		SCReq.starTime.Year = atoi(strYear.c_str());
		SCReq.starTime.Month = atoi(strMonth.c_str());
		SCReq.starTime.Day = atoi(strDay.c_str());
		SCReq.alarmType = data["alarmType"].asUInt();
		SCReq.reportType = data["reportType"].asUInt();
		SCReq.censusType = data["censusType"].asUInt();
		SCReq.channel = data["channel"].asUInt();

		param.data = &SCReq;
		param.dataSize = sizeof(SCReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgSearchSmartCount;
		param.TimeOut = 10000;
		param.UserParam = this;
	}else if(MsgZeroChnStatus == nSubType)//336
	{
		memset(&ZeroReq,0,sizeof(ZeroChnStatReq));
		ZeroReq.ReqType = 0;
		param.data = &ZeroReq;
		param.dataSize = sizeof(ZeroChnStatReq);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgZeroChnStatus;
		param.TimeOut = 10000;
		param.UserParam = this;
	}
	else if(MsgIMPReq == nSubType)//436
	{
		int subType = data["subType"].asInt();
		if (subType == 1)
		{
			IMPSetReq.getOrset = subType;
			IMPSetReq.type = data["type"].asInt();

			int maxLen;
			int len;
			std::string str;
			if (IMPSetReq.type == 0)
			{
				maxLen = sizeof(IMPSetReq.ImpCtrl.algName);
				memset(IMPSetReq.ImpCtrl.algName, '\0', maxLen);
				str = data["CtrlAlgName"].asString();
				len = str.length() < maxLen ? str.length() : maxLen;
				memcpy(IMPSetReq.ImpCtrl.algName, str.c_str(), len);

				IMPSetReq.ImpCtrl.algCtrl = data["CtrlAlgEnable"].asInt();
			}
			else if (IMPSetReq.type == 1)
			{
				for (int i=0;i<4;i++)
				{
					IMPSetReq.ImpMode.mode[i].type = data["modeParam"][i]["type"].asInt();

					maxLen = sizeof(IMPSetReq.ImpMode.mode[i].param);
					memset(IMPSetReq.ImpMode.mode[i].param, '\0', maxLen);
					str = data["modeParam"][i]["param"].asString();
					len = str.length() < maxLen ? str.length() : maxLen;
					memcpy(IMPSetReq.ImpMode.mode[i].param, str.c_str(), len);
				}
			}
			else if (IMPSetReq.type == 3)
			{
				maxLen = sizeof(IMPSetReq.ImpLive.AlgName);
				memset(IMPSetReq.ImpLive.AlgName, '\0', maxLen);
				str = data["paramAlgName"].asString();
				len = str.length() < maxLen ? str.length() : maxLen;
				memcpy(IMPSetReq.ImpLive.AlgName, str.c_str(), len);

				maxLen = sizeof(IMPSetReq.ImpLive.algParam);
				memset(IMPSetReq.ImpLive.algParam, '\0', maxLen);
				str = data["algParam"].asString();
				len = str.length() < maxLen ? str.length() : maxLen;
				memcpy(IMPSetReq.ImpLive.algParam, str.c_str(), len);

				IMPSetReq.ImpLive.param_size = len;
			}
			param.data = &IMPSetReq;
			param.dataSize = sizeof(IMPSetReq);
			param.remoteTestCallback = RSRemoteTestCallback;
			param.type = MsgIMPReq;
			param.TimeOut = 12000;
			param.UserParam = this;
		}
		else if (subType == 0)
		{
			memset(&IMPGetReq,0,sizeof(RS_ImpInfoReq_t));
			IMPGetReq.getOrset = subType;
			IMPGetReq.type = data["type"].asInt();

			param.data = &IMPGetReq;
			param.dataSize = sizeof(IMPGetReq);
			param.remoteTestCallback = RSRemoteTestCallback;
			param.type = MsgIMPReq;
			param.TimeOut = 12000;
			param.UserParam = this;
		}
		
	}
	else if (MsgValidIPTest == nSubType)//365
	{
		memset(&ValidIPReq,0,sizeof(RSNet_IsValidIP_t));
		int maxLen;
		int len;
		std::string str;
		maxLen = sizeof(ValidIPReq.TestIP);
		memset(ValidIPReq.TestIP, '\0', maxLen);
		str = data["IP"].asString();
		len = str.length() < maxLen ? str.length() : maxLen;
		memcpy(ValidIPReq.TestIP, str.c_str(), len);
		param.data = &ValidIPReq;
		param.dataSize = sizeof(RSNet_IsValidIP_t);
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgValidIPTest;
		param.TimeOut = 10000;
		param.UserParam = this;
	}
	else if (MsgDeleteLog == nSubType)//367
	{
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgDeleteLog;
		param.TimeOut = 10000;
		param.UserParam = this;
	}
	else if(MsgGetSDAlarm == nSubType)
	{
		param.remoteTestCallback = RSRemoteTestCallback;
		param.type = MsgGetSDAlarm;
		param.TimeOut = 10000;
		param.UserParam = this;//m_pRemoteTestInfo;
	}
    else if(FtpUpgradeTest == nSubType) //626
    {
        param.remoteTestCallback = RSRemoteTestCallback;
        param.type = FtpUpgradeTest;
        param.TimeOut = 12000;
        param.UserParam = this;
    }

	if(m_pDevice != NULL ){
		return RSNetRemoteTest(m_pDevice->GetConnection(), &param);
	}

	return -1;
}
