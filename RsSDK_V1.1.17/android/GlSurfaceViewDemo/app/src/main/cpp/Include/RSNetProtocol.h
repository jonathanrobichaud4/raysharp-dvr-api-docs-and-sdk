/********************************************************************
	�ļ�������	�ͻ������豸������ͨѶЭ��
	created by ������ 2011.1.8
*********************************************************************/
#ifndef __RSNetProtocol_h__
#define __RSNetProtocol_h__

#pragma pack(4)

#define RS_DVR_NORMAL       0x0000000000000000ULL  

#define RS_DVR_D9104        0x5253000000010100ULL
#define RS_DVR_D9104B       0x5253000000010101ULL
#define RS_DVR_D9108        0x5253000000010200ULL
#define RS_DVR_D9108B       0x5253000000010201ULL
#define RS_DVR_D9016        0x5253000000010300ULL
#define RS_DVR_D9116        0x5253000000060300ULL
#define RS_DVR_D9116S       0x5253000300070300ULL

#define RS_DVR_D9216H       0x5253000000020300ULL

#define RS_DVR_ID9316H      0x5253000001020300ULL
#define RS_DVR_D9316H       0x5253000000020301ULL

#define RS_DVR_D9604L       0x5253000100010100ULL
#define RS_DVR_D9608L       0x5253000100020200ULL
#define RS_DVR_D9616L       0x5253000100020300ULL 
#define RS_DVR_D9608H       0x5253000100020201ULL
#define RS_DVR_D9616H       0x5253000100020301ULL
#define RS_DVR_D9608B       0x5253000100020202ULL
#define RS_DVR_D9616B       0x5253000100020302ULL

#define RS_DVR_D9704SDI		0x5253000200050100ULL
#define RS_DVR_D9704L	    0x5253000100060100ULL
#define RS_DVR_D9704        0x5253000300060100ULL
#define RS_DVR_D9704BP      0x5253000300060101ULL
#define RS_DVR_D9708L	    0x5253000100060200ULL
#define RS_DVR_D9708        0x5253000300060200ULL
#define RS_DVR_D9708BP      0x5253000300060201ULL
#define RS_DVR_D9708S       0x5253000300070200ULL
#define RS_DVR_D9716L       0x5253000300050300ULL

#define RS_HOME_H1002H      0x5253020100010100ULL
#define RS_HOME_H1002M      0x5253020100010101ULL

#define RS_NVR_N1004        0x5253030200010100ULL
#define RS_NVR_N1104        0x5253030200060100ULL
#define RS_NVR_N1108        0x5253030200060200ULL

#define RS_IPC_TI           0x5253040200030000ULL
#define RS_IPC_GM           0x5253040200040000ULL
#define RS_IPC_3518C      	0x5253040200050000ULL

#define RS_MDVR_D5704       0x5253010100010100ULL

#define RS_DECODER_A9001    0x5253050100010100ULL
#define MaxIpLen	16
#define MaxNameLen	36
#define MaxEncodeNameLen	256
#define MAX_NET_PARAMS_LEN  32


//////////////////////////////////////////////////////////////////////////
//MsgHead.Version
#define MsgHeadV1	0 
#define MsgHeadV2   2
#define MsgHeadV3   3

//MsgHead.AckFlag
#define AckSuccess					0
#define AckFail						1
#define AckNoMsgType 				2
#define AckAdminisLogin				3
#define AckLoginUserLogined			10
#define AckLoginNoUserName			11
#define AckLoginPasswordError		12
#define AckLoginIPFilerError		13
#define AckLoginUserDisable		    14
#define AckLoginForceChangePWD      15
#define AckLoginForceCloseBrowser   16
#define AckLoginVersionError		17
#define AckLoginForbidIP 			18
#define AckLoginMacFiler     		19

#define AckDualtalkBusy				20
#define AckAuthorityFail			50
#define AckParamError				51
#define AckUpgrading				60
#define AckUpgradeVersionError		61
#define AckPreviewNoStream          62
#define AckUpgradeVersionSame       63
#define AckUpgradeLanguageError     64 
#define AckOverMaxPrevNumErr		65 
#define AckOverMaxUser              66 
#define AckInUserInterface          67
#define AckNoBandWidth            68

//MsgHead.MsgType
#define MsgSearchDev			11
#define MsgDevNetCfg            12
#define MsgIPCSetDevName        13
#define MsgLogin				31
#define MsgHeartbeat			32
#define MsgTcpPreview			71
#define MsgGetUdpAddr			81
#define MsgStartUdpPreview		82
#define MsgStopUdpPreview		83
#define MsgReqIFrame		    87
#define MsgPTZControl			101
#define MsgQueryRecord			111
#define MsgNewQueryRecord		112
#define MsgRecordPlay			121
#define MsgRecordPlayFeedback	122
#define MsgReposRecordData		123
#define MsgRecordPlayControl    124
#define MsgDownloadRecordFile	131
#define MsgDualtalk				141
#define MsgTalkPassthrough      142
#define MsgTalkFullWithIpc      143
#define MsgDualtalkChannel		145


#define MsgQueryParam			211
#define MsgSetParam				216
#define MsgDefaultParam         217     //Ĭ�ϲ�������
#define MsgStatusRequest		890		//������������״̬�ϱ�
#define MsgAlarmReport			891
#define MsgAlarmSubscribe		896
#define MsgRemoteUpgrade		5139
#define MsgRemoteUpgsIpc        5140    //ͨ��Զ������IPC
#define MsgRemoteUpgradePowerSystem 5141 //��������

#define MsgEmailTest            301
#define MsgDDNSTest             302
#define MsgRemoteReboot         303
#define MsgSyncTimeCtl          304
#define MsgColorCtrl            305
#define MsgRemoteCapture        306
#define MsgGainSnaptReport      307
#define MsgQueryLog             308
#define MsgHddFormat            309
#define MsgSearchRemoteDev		310   //NVR�ã�����Զ���豸��
#define MsgSetRemoteDevNet		311   //NVR�ã�����Զ�˻������������
#define MsgAddAllDevice         312   // һ����ӹ�����Ϣ����
#define MsgFtpUpgrade           320   //Ftp Զ������
#define MsgActivateCloud        321   // ����Ӳ����֤
#define MsgDevicePlayback       322   // �طŻ���
#define MsgFtpWriteFileTest     323   // ftpд�ļ�������Ϣ
#define MsgQueryLog_IPC         324   //ipcר��
#define MsgIsFormatHdd          325   //��ʽ��Ӳ����ط�(����)����
#define MsgNoStreamType         326   //no
#define MsgCloudCheck           327   //kguard cloud check
#define MsgSearchLog            328   
#define MsgRebootIPC            329   //Զ������IPC
#define MsgIPCLoadDefault       330   //Զ��IPC�ָ�Ĭ������
#define MsgUpgradeFireware      331   //Զ���������ƹ̼�(kguard DVR)
#define MsgRemoteOneKeyAddIPC   333 //nvr one key add ipc
#define MsgSGManualUpload       334   //���ƽ̨�ֶ�ͼƬ�ϴ�
#define MsgRsPushParamHandle    335   //rspush handle appinfo
#define MsgZeroChnStatus        336   //��ȡ0ͨ��״̬(ZIP�ͻ�)
#define MsgRemoteCheck          337   //Զ��������(����)�ƴ洢
#define MsgIsModifyHdd          360   //�޸���������ط�(����)����
#define MsgHttpUpgrade          361
#define MsgValidIPTest          365
#define MsgClientAutoLogout     366
#define MsgDeleteLog            367
#define MsgRecordsLock          369

#define MsgAddSersorDev        338  //Զ�����sensor�豸
#define MsgDeleteSersorDev        339  //Զ��ɾ��sensor�豸
#define MsgSetMobileRemoteControlStatus       340  
#define MsgGetMobileRemoteControlStatus 341


#define MsgSetSensorRuleUpdate        342
#define MsgGetSensorRuleSwitch        343
#define MsgSetSensorDevName        344
#define MsgGetSensorDevName        345
#define MsgRFConnectUpdate        346
#define MsgGetRFConnnectState     347
#define MsgRemoteParamBackup      348

#define MsgDevTelnetOpen          349
#define MsgDevTelnetOff           350

#define MsgDevSerialOpen          351
#define MsgDevSerialOff           352
#define MsgRemoteParamImport      353
#define MsgFtpUpgradeSearchFile   354 //search ftp fle for upgrade 2016.03.24


//�޸Ĺؼ���������
#define MsgQueryKeyConf			400
#define MsgSetKeyConf			401

#define MsgReqVideoActivation   402
#define MsgGetDDNSID            403
#define MsgGetIFrame            404
#define MsgReposIFrameData      405
#define MsgDownLoadJpg          406
#define MsgNoPlaybackAuth       407
#define MsgNoPreviewAuth        408
#define MsgPreviewActivateFaile 409

//
#define PPPOE_SET_MSG           411
#define MsgStopEmailTest        412
#define MsgNewEmailTest         413

//�µĵ��뵼����2016.12.22add
#define MsgRemoteNewParamImport      414
#define MsgRemoteParamNewBackup     415
#define MsgSaveToDev				416
#define MsgSetIOAlarmStatus			417
#define MsgGetIOAlarmStatus			418
#define	MsgNEWEmailTest          419
#define MsgRoutePeat            420
#define MsgRouteAdd             421
#define MSgChannelPair		422
#define MsgForceIFrame		423
#define MsgTurnOffAlarm		424
#define MsgNewStreamset		425
#define MsgEmailTestNew     427
#define MsgJsonTypeMsg      429

#define MsgIMPReq           436
//MsgHead.MsgSubType 
#define MsgNoSubType	0

#define MsgGetSDAlarm       438

//MsgPTZControl sub type
#define MsgPTZUp			1
#define MsgPTZDown			2
#define MsgPTZLeft			3
#define MsgPTZRight			4
#define MsgPTZUpLeft		5
#define MsgPTZUpRight		6
#define MsgPTZDownLeft		7
#define MsgPTZDownRight		8
#define MsgPTZZoomIn		11 //������
#define MsgPTZZoomOut		12 //�����С
#define MsgPTZFocusNear		13 //����ǰ��
#define MsgPTZFocusFar		14 //������
#define MsgPTZIRISOpen		15 //��Ȧ����
#define MsgPTZIRISClose		16 //��Ȧ��С
#define MsgPTZAutoScan		21
#define MsgPTZCruise		51
#define MsgPTZGetPresetNum  52
#define MsgPTZSetPPCruise			53  //���ù켣Ѳ��
#define MsgPTZCallPPCruise			54  //���ù켣Ѳ��
#define MsgPTZStartPattermCruise		55  //����ɨ�迪ʼ
#define MsgPTZEndPattermCruise		56          //����ɨ�����
#define MsgPTZCallPattermCruise		57          //���û���ɨ��


#define MsgPTZGuard         90
#define MsgPTZSetPreset		91
#define MsgPTZClearPreset	92
#define MsgPTZCallPreset	93
#define MsgPTZSensorPresetInfoGet 94
#define MsgPTZSensorPresetInfoSet 95
#define MsgPTZLockFocus 96
#define MsgPTZLineScanA 98  //����ɨ�迪ʼ��
#define MsgPTZLineScanB 99   //����ɨ�������
#define MsgPTZDefault   100
#define MsgPTZ_ZOOM_POSITION   101
#define MsgPTZ_FOCUS_POSITION   102
#define MsgPTZ_ZOOM_MOVE   103
#define MsgPTZ_FOCUS_MOVE   104
#define MsgPTZ_AUTO_FOCUS   105
#define MsgPTZ_AREA_FOCUS   106
#define MsgPTZ_REFRESH_INFOR   107
#define MsgPTZ_CALIBRATION_SETTING   108

//MsgQueryRecord sub type
#define MsgRecordDetail		 101
#define MsgRecordDayOutline	 102
#define MsgRecordDayHalfHour 103
#define MsgQueryJpgDetail	 104  
#define MsgDelJpg            105

//MsgRecordPlayFeedback sub type
#define MsgRecordDataInsufficient		121
#define MsgRecordDataEnough				122

//MsgAlarmReport sub type
#define MsgPirAlarm 					187
#define MsgSnaptMotion                  188
#define MsgVLossAlarm                   189
#define MsgDevStatReport                190
#define MsgMotionAlarm			        191
#define MsgIOAlarm				        192
#define MsgAIAlarm				        193
#define MsgIntelligentAlarm		        194
#define MsgAvdAlarm				        195

#define MsgAlarmDesired			        196
#define MsgAlarmRefused			        198
#define MsgAIData                       199
#define MsgRecordAlarm          		201
#define MsgHddAlarm             		202
#define MsgFtpUpgradeAlarm              203   // Ftp �����澯
#define MsgUpgradeAlarm					203   // Ftp �����澯(new name)
#define MsgOscAlarm		                204
#define MsgIntelPeaAlarm                205
#define MsgOscRuleAlarm                 206
#define MsgVideoHideAlarm               207
#define MsgBitrateInfo                  208
#define MsgAllChnsAlarm                 209 //����ͨ������

//MsgAlarmSubscribe sub type
#define MsgTelModuleAlarm               210
#define MsgRemoteCHStatusReport         211
#define MsgRecordStatusReport			212
#define MsgHddStatusReport				213
#define MsgGpsInfoReport                214
#define MsgIntelIpcPeaAlarm             215 // ���� 2015.11.30
#define MsgIpcOSCAlarm                  216
#define MsgIntelIpcPeaAreaAlarm         218 // �ܽ� 2015.11.30
#define MsgSensorStatusReport           247  //sensor״̬

#define MsgAlarmIntHD                   248  // ���� 2016.03.09
#define MsgAlarmIntFD                   249  // ���� 2016.03.09
#define MsgAlarmIntPCC                  250  // ����ͳ�� 2016.03.09
#define MsgAlarmIntManage		        251  // ���ܹ��� 2016.03.09
#define MsgAlarmFishEyeIpcStat          252  
#define MsgAlarmPTZIpcStat				253 //autoFocus ipc 2017.04.25
#define MsgAlarmMotionSmart			    254
#define MsgChNameChange                   255
#define MsgDevNameChange                256
#define MsgDevParamChangeReport         257
#define MsgDevPreviewChangeReport    258 //liveParam 2017.12.15
#define MsgDevChModeReport               259
#define MsgAlarmImplReport               269
#define MsgSoundAlarmReport              272 //sound alarm 2018.04.23
#define MsgAudioReport                  274 //��Ƶ����״̬ 2018.4.24
#define MsgClientAutoLogoutTimeChangeReport 		275
#define MsgGetPic                       277
#define MsgSamPCAlarmReport             279
#define MsgNewDataLinkOpt               282
#define MsgNewDataLinkJson              283
#define MsgPWDChange                    285
/******************************
* ��������.SubType   -----start
*******************************/ 
#define MsgParamOsd				        501
#define MsgParamSystemBase		        502
#define MsgParamHdd				        503
#define MsgParamSerial			        504
#define MsgParamUser 			        505
#define MsgParamDst 			        506
#define MsgParamMainStream 	            507
#define MsgParamColor 			        508
#define MsgParamVideoCover 		        509
#define MsgParamPtz 			        510
#define MsgParamNetworkBase 	        511
#define MsgParamDDNS 			        512
#define MsgParamPPPOE 			        513
#define MsgParamEmail 			        514
#define MsgParamNtp 			        515
#define MsgParamMotion 			        516
#define MsgParamAbnormal 		        517
#define MsgParamIOAlarm 		        518
#define MsgParamRecord 			        519
#define MsgParamSchedule 		        520
#define MsgParamDefault 		        521
#define MsgParamIntelligent             522
#define MsgParamIntavd                  523 

#define MsgParamGeneral                 524
#define MsgParamMaintain                525
#define MsgParamSubStream               526
#define MsgParamMobile                  527
#define MsgParamEmailSchedule           528
#define MsgParamPlatform                529
#define MsgParamIpc                     530
#define MsgParamIpcIOAlarm              531
#define MsgParamIpcWifi                 532
#define MsgParam3G                      533
#define MsgParamRouterLan               534
#define MsgParamRouterWan               535
#define MsgParamTuobao                  537
#define MsgParamVehicleMng              538
#define MsgParamOutput			        539
#define MsgParamTelAlarmArea            540
#define MsgParamTelAlarmWireSensor      541
#define MsgParamTelAlarmWirelessSensor  542
#define MsgParamPhoneNumberSetting      543
#define MsgParamCameraSet               544
#define MsgParamMobileStream            545
#define MsgParamHuaweiPlatform          546
#define MsgParamIPFilter                547
#define MsgParamRtsp                    548
#define MsgParamFtp                     549
#define MsgParamElecLock             	550
#define MsgParamCloudStorage            551
#define MsgParamCloudEmail              552

//#define MsgParamP2pMobile               553
#define MsgParamP2pQrCodeID             553
#define MsgParamDevAllStatusSet         554   // URMET �ͻ�Զ�̿���ͨ����Ϣ
#define MsgParamLorexP2pParam           555   // Lorex�ͻ���������
#define MsgParamFtpAutoUpgrade          556   // 
#define MsgParamManualRecord            557   // �ֶ�¼��

#define MsgParamSystemIDCtrl             558  // �豸id��
#define MsgParamIPCFrameInfo             559  // nvr��ȡipc֡��Ϣ
#define MsgParamNewCloudStorage          560
#define MsgParamUpLoadPhoto              561
#define MsgParamUpLoadVideo              562
#define MsgParamCloudStorageInfo         563
#define MsgParamCloudStorageEmail        564
#define MsgParamCloudStorageFTP          565
#define MsgParamPerimeterLine            566
#define MsgParamVideoDiagnostics         567
#define MsgParamGoodsLostLegacy          568
#define MsgParamKGWireless               569/* ����KG  Wireless ��������*/

/*******************************************************************
��������,subType,���ڱ�Ų����ã����Դ�703��ʼ��ţ����ݹ��ܰڷţ�
�����Ǳ��.����µĶ��������ע�����޸ġ�ע�������� ----2016.03.10
********************************************************************/

#define MsgParamPerimeter                703 // �ܽ� 2015.11.12
#define MsgParamAreaStream               704 // ipc ��������
#define MsgParamIntHD				 	 705 //���� 2016.03.09
#define MsgParamIntFD				     706 //���� 2016.03.09
#define MsgParamIntPCC				     707 //����ͳ�� 2016.03.09
#define MsgParamIntManage                708 //���ܹ��� 2016.03.09

/*���õ���˽�в�����Ӧ�ṹ��Eplateform_t*/
#define MsgParamElectricityGrid			 709 //2016.05.25
#define MsgSearchSmartCount              710 //ͳ�����ܹ��ߵĸ��� 2016.05.31
#define MsgParamFishEye                  711  //ipc fisheye
#define MsgParamIPCCamearMode            712

/*���ý�����ҳ�����,��Ӧ�ṹ�� RSNet_SoleSwitch_t*/
#define MsgParamSwitch					 713
#define MsgParamIPCCameaFocusInfo		 714
/*��������.SubType   -----end*/ 

/*Ԥ������������ã���Ӧ�ṹ�� RSNet_SolePreviewCtrl_t,PARAM_PAGE_PREVIEWCTRL*/
#define MsgParamPreviewCtrl  715
#define MsgParamAlarmOutScheduleset  716

/*͸��ͨ������Э��*/

/*Swann*/
#define MsgParamSwannWifi  717 //����swann wifiҳ��
#define MsgParamSwannIpcRepeat  718 //����swann IpcRepeat
#define MsgParamSwannRouterRepeat  719 //����swann RouterRepeat

/*APPԶ�̿�����*/
#define MsgParamWizard  720
#define MsgParamTiming  721//Уʱָ��

/*GB28181 ҳ�����*/
#define MsgParamGB28181 722

/*PIR ҳ�����*/
#define MsgParamPir		723

/*����ƽ̨�����㷨��������*/
#define MsgParamJDVCAMeterRecongition	724 //����ƽ̨���ܶ������� JD_VAC_TYPE_METER_RECOGNITION
#define MsgParamJDVCAIntrusionDetection	725 //����ƽ̨���������㷨���� JD_VAC_TYPE_INTRUSION_DETECTION
#define MsgParamJDVCARedMantleDetection	726 //����ƽ̨����첼᣼����� JD_VCA_RED_MANTLE_DETECTION


/*����OSD ����*/
#define MsgParamCarInfo 727

#define MsgParamVVPush  728

#define Msg98cUpgrade  729

#define MsgRemoteUpgrade2 730

/*************͸��ͨ������Э��****************/
#define MsgSerialTransport          355

/*��������.SubType   -----end*/ 


/***********************************
 * new nvr param  adapter message
 **********************************/
#define MsgParamModifyMainStream         570
#define MsgParamModifySubStream          571
#define MsgParamModifyMobileStream       572
#define MsgParamModifyLiving             573
#define MsgParamModifyOutput             574
#define MsgParamModifyKBSet              575
#define MsgParamModifyFtpUpgrade         576 
#define MsgParamModifyState              577
#define MsgParamModifyEmailSchedule      578
#define MsgParamLogDeletes				 579
#define MsgParamLogTerm					 580
#define MsgParamVoice					 581
#define MsgParamIDSet                    582
#define MsgParamStreamSet                583 //honeywell only. (20140516)
#define MsgParamSoleUploadVideo          584 //��Ƶ�ϴ� 7day*48halfhour
#define MsgParamIntelliRec               585 //����¼��ƻ�(Qt v2)
#define MsgParamIPCImageSet              587 //IPCͼ������
#define MsgParamRenewFactory             588 //shenzhen renew factory
#define MsgParamCustomProtocol           589 //�Զ�����������Э��(nvr)
#define MsgParamSGPlatform               590 //���ƽ̨����
#define MsgParamIPCROI                   591 
#define MsgParamOD                       592 
#define MsgParamIPCWireless              593 //Lorex����IPCר�ò���
#define MsgParamKguardP2p                594 //Kguard ShangYun P2P (DVR)
#define MsgParamSensorAlarm              595 //Kguard Sensor Alarm (DVR)
#define MsgParamPushInfo                 596 //push info 
#define MsgParamAnalogCam                597 //���DVRģ��ͨ����Ϣ
#define MsgParamCaptureSet               598 //���DVRץͼ����
#define MsgParamCapSchedule              599 //���DVRץͼ�ƻ���
#define MsgParamIPV6Info                 600 //ipv6 info 
#define MsgParamZeroChn                  601 //��ͨ������
#define MsgParamSensorAlarmSingle        602 //Kguard single Sensor Alarm (DVR)
#define MsgParamSensorCtrl			     603 //sensor control Alarm(���dvr ĿǰKguardʹ��)


#define MsgParamKeyParamSet              700 //Զ����д�ؼ�����
#define MsgParamChnInfo                  701 //���DVRͨ����Ϣ
#define MsgParamRecInfo                  702 //���DVR¼����Ϣ

/*GB28181 ҳ�����*/
#define MsgParamGB28181 722

#define MsgSysParamEx                  803 
#define MsgParamUrmetHttp   		   804
#define MsgParamNewCloudestorage       805
#define MsgParamIPCIOAlarm 		       806
#define MsgParamOutPut 		       807
#define MsgNewIOAlarm              808
#define MsgParamNetFilter		   809
#define MsgParamALTEReport		   810
#define MsgParamThumbnail		   811
#define MsgParamSnapPicForP2P	   812
#define MsgParamNewEmail			813
#define MsgParamAlarmLinkagePTZ    814
#define MsgParamModifyAlarmStream		 815
#define MsgParamModifyAlarmState		816
#define MsgParamXINQIAOFaceDetection		817
#define MsgParamIOAlarmManage		818
#define MsgParamIeee8021xParam		819
#define MsgParamHttps				822
#define MsgParamCertificates			823
#define MsgParamiot_cert				824
#define MsgParamSnmp			825
#define MsgHGIntParam           826
#define MsgHttpsFileParam		827
#define MsgdropboxParam         828
#define MsgFloodLightParam      838
#define MsgIPCNetInfoParam      848
#define MsgIPCImpParam         858
#define MsgSoundAlarmParam     861
#define MsgNewIpFilterParam    863
#define MsgFtpScheduleParam    866
#define MsgParamFaceIdentify        867
#define MsgPtzScheduleParam    868
#define MsgParamAmazonAccountInfo		869
#define MsgParamAmazonPushConfig		870
#define MsgParamFocusPointSet           871
#define MsgParamVpnSet           872
#define MsgDefaultFaceFrontalView 873
#define MsgDefaultFaceMultiView   874

/**********************************************************
ע��:703-708�ѱ�"��������"ռ�ã���#define MsgParamPerimeter��
����µĶ��������ע�����޸ġ�ע���������� ----2016.03.21
**********************************************************/

//
#define MsgParamOccSet_IPC               1000 
#define MsgParamModifySnmpSet			 1001 
#define MsgParamModifyGb28181			 1002 
#define MsgParamModifyIeeeSet			 1003 
#define MsgParamModifyCameraSet_IPC      1004  
#define MsgParamModifyNetBeakSet         1010  
#define MsgParamSoundRecord              1012
#define MsgParamLightSchedule            1013  /* KG �����ƺ���schedule����*/
#define MsgParamSnapshot                 1014   //KG���չ���
#define MsgParamFishEyeCircle            1015

//���� sub type
#define MsgRemoteUpgradeData	761
#define MsgRemoteUpgradeEnd		762
#define MsgRemoteUpgradePartEnd 763
#define MsgRemoteUpgradeWriteFlashInProgress 764
#define MsgRemoteUpgradeWriteFlashEnd 765


#define MsgRSPlatform           800
#define MsgParamFocusPointSet   871

//sync time sub type
#define MsgSyncSetTime          331
#define MsgSyncGetTime          332

//MsgStatusAlarmRequest	Sub Type 
#define MsgDevAllStatusReq			610
#define MsgRemoteCHStatusReq		611  //��ѯԶ������ͨ����״̬,��ҪָNVR���ӵ�IPC״̬

//Msg PEA , GoodsLost Sub Type
#define MsgPeaAlarmReq              612
#define MsgGoodsLostAlarmReq        613
//ֻ��ȡ�豸״̬,����lorexͬʱ��ȡ״̬�ͼ������
#define MsgDevStatusOnlyReq         614
#define MsgGetRemoteParam           615 //��ȡlorex http��������
#define MsgLastRecordReq            616 //�豸���һ�μ�¼��Ϣ.(ALTE�ͻ�)


#define EMsgLogin				    617
#define EMsgSearchDev			    618

#define CdoublesMsgLogin			619
#define CdoublesMsgSearchDev		620
#define CryptoMsgLogin 			    621

#define RaydinMsgLogin				622
#define RaydinMsgSearchDev			623

#define OPTIMUSMsgLogin             624
#define OPTIMUSMsgSearchDev         625
#define FtpUpgradeTest              626

typedef struct
{
	BYTE Version : 2; 	//��Ϣͷ�汾
	BYTE ExtSize : 6; 	//��Ϣͷ��չ��С��ʵ����չ��С = ExtSize * 4
	BYTE Reserved;
	WORD AckFlag; 		//��Ϣ��Ӧ��
	WORD MsgType; 		//��Ϣ����
	WORD MsgSubType; 	//��Ϣ������
	UINT MsgSize;  		//��Ϣͷ��������ݴ�С
	UINT Seq;  		    //��Ϣ���кţ���ʶһ����Ϣ��Ψһ�ԣ������󷽴�������Ӧ��ԭֵ����
}MsgHead;			 	//��Ϣͷ��sizeof(MsgHead) = 16
//����ͨ����·�����ʹ��������������Ӧ����
typedef struct 
{
	int res; //0 failed  1 success 
	int reserve;
}RSSerialRes_t;

//232���ݷ���������Ϣ��
typedef struct 
{
	int datatype; //0 play control ,1 user commind ,2 ��չ����
	int datasize; 
	char buf[1];
}RSSerialReqData_t;


//////////////////////////////////////////////////////////////////////////
//�����豸
//���� MsgType=MsgSearchDev
//��Ӧ MsgSize=sizeof(SearchDevRsp)

#define SearchDevPort	9333

//SearchDevRsp.NetworkMode
#define NetworkModeDHCP		0
#define NetworkModePPPOE	1
#define NetworkModeManual	2

typedef struct
{
	char IP[MaxIpLen]; //IP
	char HostName[MaxNameLen]; //����
	char NetMask[MaxIpLen]; //����
	char GateWay[MaxIpLen]; //����
	char DNS1[MaxIpLen]; //dns������1
	char DNS2[MaxIpLen]; //dns������2

	UINT Port; //�ͻ��������豸�˿�
	UINT IEPort; //IE�˿�

	UINT NetworkMode; //������ʽ

	char DevType[MaxNameLen - 8]; //�豸����
	unsigned long long DevTypeULL;
	char DevVer[MaxNameLen]; //�豸�汾
	UINT DeviceID;  //�������
   	char DeviceName[MaxNameLen]; //�豸���ƣ������޸�        
	char MacAddr[MaxNameLen]; //�豸MAC��ַ

	UINT ChannelNum; //ͨ����
	
	unsigned char Version;//�汾
	char cNetInterface;// 0 eth0 1 eth1
	char P2pID[38];

    char manufacture[32];
	unsigned short rtspport;
	char DisplayChannelNum; // ģ��ͨ����
    char reserved[93];
}SearchDevRsp;


//////////////////////////////////////////////////////////////////////////
//��¼
//���� MsgType=MsgLogin, MsgSize=sizeof(LoginReq)
//��Ӧ �ɹ�AckFlag=AckSuccess,MsgSize=sizeof(LoginRsp) ʧ��AckFlag=AckLoginUserLogined,AckLoginNoUserName,AckLoginPasswordError,AckFail

//VideoFormat
#define RS_PAL  0
#define RS_NTSC 1

typedef struct
{
	char UserName[MaxNameLen];
	char Password[MaxNameLen];
	UINT UserKey; //�״ε�¼Ϊ0�������������ϴγɹ���¼���ص�UserKey���Է���ռ�û������û��ѵ�¼�Ĵ��󷵻�
	UINT AlarmReportDesired : 1;
	UINT ZipLogin: 1;//zip login falg
	UINT Reserved : 22;
	UINT Language : 8; /* 1,����2.Ӣ�� */
}LoginReq;

typedef struct
{
    char UserName[256];
    char Password[256];
    UINT UserKey; //�״ε�¼Ϊ0�������������ϴγɹ���¼���ص�UserKey���Է���ռ�û������û��ѵ�¼�Ĵ��󷵻�
    UINT AlarmReportDesired : 1;
    UINT ZipLogin: 1;//zip login falg
    UINT Reserved : 22;
    UINT Language : 8; /* 1,����2.Ӣ�� */
}LoginCryptoReq;

typedef struct
{
    int  structsize;
    char reserve[4];
    char uuid[24];
    char reserve1[128];
}LoginReponse;

//�û�Ȩ�޸�λ��ʾ
typedef struct
{
	UINT UserSetRight;/*��������0 ,���̹���1,Զ�̵���2,ϵͳά��3,��־�鿴4,(Ѳ������5)����ѯ����6, �ֶ�¼��7,�ֶ�׽ͼ8,��ƵȨ��9*/
//	UINT ManualRecordChannel;  //�ֶ�¼��ͨ�� 
	UINT PreviewChannel;     //Ԥ��ͨ��
	UINT PlayBackChannel;       //�ط�ͨ��
	UINT BackupChannel;        //����ͨ��
	UINT PtzControlChannel;     //��̨����ͨ��
	BYTE UserPreview;        //Ԥ��Ȩ��
//	BYTE UserManualRecord;   //�ֶ�¼��Ȩ��
	BYTE UserPlayBack;        //¼��ط�Ȩ��
	BYTE UserBackup;          //����Ȩ��
	BYTE UserPtzControl;       //��̨����Ȩ��
	
	BYTE MainStream:1;       //��Ȩ�ޣ���λȡֵ        
	BYTE SbuStream:1;		//��Ȩ�ޣ���λȡֵ        
	BYTE MobileStream:1;	//��Ȩ�ޣ���λȡֵ     
	BYTE UserAlarmSensorControl:1;       //alarm sensor control
	BYTE UserRtsp:1;	//RTSPȨ�ޣ���λȡֵ 
	BYTE Reser:3;
         
	BYTE OnivfRight;		////0:����ԱȨ�ޣ�1:����ԱȨ�ޣ�2:��Ƶ�û�    
	BYTE Reserved[14];
}UserRightWrap;
//C_ASSERT(sizeof(UserRightWrap) == 40);

typedef enum
{
	PLATF_SWITCH_RS_PLATFORM = 0,
	PLATF_SWITCH_HUAWEI_PLATFORM,
}PlatformSwitch_E;

typedef enum
{
  BIT0_E = 0,//Bit0 indicates whether or not  display image control page, 0 means showed that 1 is hidden
  BIT1_E,    //Bit1 indicates whether or not display IRIS function , 1 display , 0 not display 
  BIT2_E,    //Bit2 indicates samsung dedicated h. 265 ipc image page parameter, 0 indicates not samsung customer, 1 indicates samsung customer
  BIT3_E,    //Indicates whether or not the display intelligence analysis page.0 means hide, 1 display
  BIT4_E,    //area encode page for ipc
  BIT5_E,    //Whether show intelligent management function
  BIT6_E,	 //Whether show Analog channelpage(DVR PRODUCT)
  BIT7_E,	 //Wheher PTZ  Page show COAX1 COAX2, or just show COAX
  BIT8_E,    //display or hide the import-export page
  BIT9_E,    //display or hide power grid page;
  BIT10_E,   //snap picture 
  BIT11_E,   //substream playback
  BIT12_E,   //fisheye ipc
  BIT13_E,   //hydvr whether display sharpness pic
  BIT14_E,   //whether or not use dynamic occlusion  
  BIT15_E,   //display or hide sensercontrol page
  BIT16_E,   // 1:show new rtsp page, 0:show old rtsp page
  BIT17_E,   // 1:show new NTP page, 0:show old ntp page
  BIT18_E,   //1:IE recoed flag enable, 0: IE recoed flag disable  
  BIT19_E,	 //Whether use AMR function , 1 use ,0 not used  
  BIT20_E,   //0:old , 1:all alarm status and device capbiliti use DevAllStatusRpt struct(2016,11.17 add)
  BIT21_E,	 //whether or not allow Disable admin password. 0:allow 1:not allow
  BIT22_E,   //1: show format hdd , 0:not show
  BIT23_E,   //1: add NTP  user defined, 0 not add
  BIT24_E,   //display or hide p2p swith ,0:hide, 1:display
  BIT25_E,   //1:support I/O Alarm,0 not support
  BIT26_E,   //1:support Audio In/Out��0 not
  BIT27_E,   //When the device needs to be forced to set the password, tell the client in the first login or restore default to make a prompt, 1:prompt
  BIT28_E,   //DEFENDER mars,control Motion erae
  BIT29_E,   //download speed 0,not support, 1:support
  BIT30_E,   //0:v100, 1:v300
  BIT31_E,   //1:double eye ipc
}PageControl_E;

typedef enum
{
    PBIT0_E = 0,//1:use NewIOAlarmParamAdapter, 0 : use old
    PBIT1_E,    // 1: no support Mobile stream  0: support Mobile stream
    PBIT2_E,    // 1: no support corridor mode and Angle Rotation    0: support corridor mode and Angle Rotation
    PBIT3_E,    //1: no support Transparency    0: support Transparency
    PBIT4_E,    //1:support thumbnail , 0: no support ;
    PBIT5_E,    //1:support PIR and MOTION , 0: no support
    PBIT6_E,    // 1: no support Mobile stream  0: support Mobile stream
    PBIT7_E,    // 1: no support corridor mode and Angle Rotation    0: support corridor mode and Angle Rotation
    PBIT8_E,    // 1: support GB28181    0: no support
    PBIT9_E,    //1:use new email struct
    PBIT10_E,   //1:Hide Switch Mode 0:show Switch Mode
    PBIT11_E,	//1��support alarmLink page  0:no support alarmLink page;
    PBIT12_E,   //1:support  PIR     0: no support
    PBIT13_E,   //1:Supports poe independent settings, 0: no support
    PBIT14_E,   //1��support 3070 old sonix wireless, not live page; 0:not
    PBIT15_E,   //1:support 4K , 0: no support
    PBIT16_E,   //1:support ��˹�� , 0: no support
    PBIT17_E,   //1:support USB DONGLE, 0: not support
    PBIT18_E,	//Intel Page Is Need Hide Half AnalogCh
    PBIT19_E,   //1:support Alarm Stream , 0: no support
    PBIT20_E,   //playback search whether support IO and motion cross part
    PBIT21_E,	//1:support  DF interface for URmet display engineering  0:no support
    PBIT22_E,   //Is Support Web Change Resolution.  0:no suppot,1:support( show change resolution row)
    PBIT23_E,   //default page is show pairing,1:show,0:hide
    PBIT24_E,   // cms new ftp upgrade test
	PBIT25_E,	//DF Mode No AF version number is shown 0:Display 1: No Display 
	PBIT26_E,   //1:SUPPORT I/O Trigger 0:NOT SUPPORT
    PBIT27_E,   //0 no support FloodLigh  1 support FloodLigh
    PBIT28_E,   //0 no support the speaker  1 support the speaker
    PBIT29_E,   //0 support ROI   1 no support ROI
    PBIT30_E,   //1��Support  snmp interface  0: no Support
    PBIT31_E,	//1:SUPPORT IRCutMode Video  Auto 0:NOT SUPPORT
}PageControl2_E;
typedef struct
{
	BYTE isFishEye;
	BYTE isSupportHard_dec;
	BYTE curShowMode;
	BYTE curStreamNum;
	BYTE fishEyeflag;// 0 not support fish eye ipc, 1 suport fish eye ipc
	BYTE unused[3];
} FishEyeIpc_Cap_t;

//�Զ��Խ�Zoom��Focus������Сλ��
typedef struct
{
	UINT mixZoomPosition;
	UINT maxZoomPosition;
	UINT mixFocusPosition;
	UINT maxFocusPosition;
	BYTE PTZVersion;//ʹ��PTZ ����İ汾��0:�ɽ��棬1:�½���
	BYTE unused[7];
} AutoFocus_Default_t;
typedef struct 
{
	UINT StructSize; //�ýṹ���С
	UINT ChannelMask;//ͨ������
    UINT curZoomValue;//zoom��ǰ��λ��
    UINT zoomStep;//0��1��  1��5��  2��20��
    UINT curFocusValue;//focus��ǰλ��
    UINT focusStep;//0��1��  1��5��  2��20��
    BYTE autoFocusState;//0:�Խ�������1�����жԽ���
    char ShiftRange;//0:����Χ��1��������Ƭ
    BYTE unused[30];//����
}AUTOFOCUS_CONTROL_S;

typedef struct
{
	unsigned long long DevType; //�豸����
	char DevVer[MaxNameLen]; //�豸�汾
	char DeviceName[MaxNameLen]; //�豸���ƣ������޸�        
	char MacAddr[MaxNameLen]; //�豸MAC��ַ
	UINT DeviceID;  //�������
 
 	UserRightWrap UserRight; //�û�Ȩ��

	UINT UserKey; //�û���Կ
 	WORD TotalFPS_D1; //�豸D1ģʽÿ�������֡��������TotalFPS=100, ��������4��CIF 25f/s��2��HD1 25f/s��1��D1 25f/s
 	BYTE ChannelNum; //ͨ����
 	BYTE VideoFormat; //����ͷ��ʽ

 	BYTE AlarmInNum;  //����������
 	BYTE AlarmOutNum; //���������(�̵�������)
	BYTE AIAnalyzeCap; //�Ƿ�֧�����ܷ���
	BYTE AIAnalyzeChannels; //���ܷ�����·��

	BYTE SerialNum;	//�豸ʹ�ô��ڵ���Ŀ��û�о���0��(������ǲ��ô���ͨѶ)
	BYTE ISAdmin;   //�Ƿ��ǹ���Ա
	BYTE AudioNum;         //��Ƶͨ����
	BYTE ResolutioFrameFix;//֡�ʷֱ����Ƿ�̶�:0-�ɵ�,1-���̶���2-������չΪ���ߵ����

	BYTE PreviewOff;       //Ԥ���Ƿ���Թرգ���Ҫ���D9016����������0-���ԣ�1-������
	BYTE VideoCoverNum;    //��ͨ��֧�ֵ������Ƶ�ڵ���������Ҫ���D9016��������
	BYTE SupportSpot;      //�Ƿ�֧��spot�ӿڵ���ع���
	BYTE SubStreamMin;     //С��������ȡֵ��Χ��Ӧ������ֵ��������Ʒ����ʵ�������ֵ

	BYTE SubStreamMax;     //����:0     1     2     3     4    5     6     7    8       9       10      11     12
	BYTE PlatformSupport; //0(��֧��ƽ̨) 1(֧��ƽ̨)
	
    WORD ChnInfoSize;		//��ʾ��¼�ṹ���������ͨ����ϢDevChnInfo�ṹ��Ĵ�С
							//�����汾������ʹ��ͨ����Ϣ�ṹ�塣��Ϊ��Ϣ����MsgRemoteCHStatusReq��ȡͨ����Ϣ��

	BYTE SubStreamRestrict; // 0(������) 1 (��������)
	BYTE DualtalkShowTag;  //0(����ʾ:���ܲ�֧�ֶԽ�) 1(��ʾ��֧�ֶԽ�)
	BYTE RouterShowTag;    //�Ƿ���ʾ·�ɲ�������ҳ��
	BYTE LanShowTag;		//�Ƿ���ʾ·��Lan������ҳ��

	UINT PlatFormShowTag;   //�Ƿ���ʾƽ̨���ò���ҳ�棬Value�� Show Plat��*(UINT*)"PLEn" ��Hide Plat��0x00000000 ��
	char ProductName[24];
	UINT PlatFormSwitch;   //��PlatformSupport = 1��PlatFormShowTag = "PLEn"�� ���жϴ��ƽ̨֧������, ��λ��ʾ��ʹ�� PlatformSwitch_E ����, ��ȫΪ0��ΪĬ�ϵ�RS_PLATFORM��
	
	BYTE VideoActivateSwitch; // �Ƿ�֧�� �����û���ѡ��ͨ����Ƶ��������С������������
	BYTE MotionMode;          //0����ɵ�ģʽ��1 ���� 44*36 ��ʽģʽ
    BYTE ResolutionMode;      //0 ����D1ģʽ,1����D1��960Pģʽ, 2����CIFģʽ, 3����CIF���ǲ�����֡��
                              //4 ����720P�� 5����720P��960
	BYTE HidePhonePage;        //0�������أ�1��������
	
	BYTE UpgradeType;         //0 ������豸���� 1 �������豸����
	BYTE ElecLockFlag;         //0 ����δ����״̬ 1 �������״̬
 	WORD TotalFPS_960;			//�豸960ģʽÿ�������֡��������TotalFPS=100, ��������4��CIF 25f/s��2��HD1 25f/s��1��D1 25f/s

	// one byte
	BYTE WifiStatus:1;           //0 ����û�м�⵽wifiģ��, 1 ������ģ�����
	BYTE RtspPageEnable:1;           //�Ƿ���RTSP����ҳ�濪�� 0����ر�, 1 ������
	BYTE FtpPageFlag:1;          //Ftp���ܱ�ʶ����1 �д˹��ܣ�0Ϊû��
	BYTE c32PasswordFlag:1;     // ʹ�ó������ʶ����1Ϊʹ��32�ֽڵ����룬0Ϊ��ʹ��
	BYTE UrmetDevStatusFlag:1;   // ;UEMET�ͻ����� �豸״̬��Ϣҳ����ʾ��ʶ��	
	BYTE FileSystemFlag:1;       // ;0 ��˼ϵͳ 1 ����ϵͳ
	BYTE KguardP2pUidFlag:1;      // 0 ����ʾUid, 1��ʾUid
	BYTE EmailFlagSwitch:1;     // EmailScheduleFlag ��ʶλ�Ŀ��ƿ����Ƿ���Ч��1����Ч��0:��Ч.
	
	BYTE EmailScheduleFlag:1;     // �Ƿ���¼��ƻ�ҳ�棬0 ��������1����
	BYTE PtzHiddenFlag:1;	     // �Ƿ�����PTZ���ܣ� 0 ������(����), 1 ����(�ر�)
                                 // Ϊͬʱ������ǰ�豸�汾������3g���ܣ�����û��3g����	
	BYTE c3GFlagSwitch:1;         // 3GFlag ��ʶλ�Ŀ��ƿ����Ƿ���Ч��1����Ч��0:��Ч.
	BYTE c3GFlag:1;               // 0 ������3G����, 1 ����3G���� 
	BYTE RecordTypeFlag:1;	 //�ط�¼�����ͱ�־ 
	BYTE SystemIDCtrl:1;     // systemID 	
	BYTE FtpPcSendFlag:1;     // Ftp����ץ��ͼƬ���ܱ�־λ 0 �ر�  1 ����	
	BYTE CloudStorageFlag:1;  // �ƴ洢����0 �ر� 1 ���� 	
	
	BYTE AutoMaintenance:1;   //�Զ�ά��ҳ�����أ�0 �� 1 ����
	BYTE CloudSGSerSwitch:4;  //  �ƴ洢����������
	BYTE ShieldColorSetFlag:1; 
	BYTE IntelligentAnalysis:1;  // ���ܷ���ҳ�棬0 close 1 open
	BYTE RemoteUpgradeMode:1;   // 0: old Mode, 1: new Mode

	BYTE CloudeSGType:4;      // 0 dropbox and google 1: only dropbox 2: only google��20181024�����ƴ洢����λȡ��0֧��dropbox��1֧��google��
	BYTE CloudeStorageMode:1; // 0:old param struct , 1: new param struct
	BYTE VBRFlag:1;
	BYTE RemoteFtpUpgradeSupport:1;  // 0:not support , 1: support to upgrade
	BYTE MainStreamMutex:1; 

	BYTE NewAapterQTParamFlag:1;  // ����Qt������־λ
	BYTE PtzSupported:1;		  // only for nvr set IPC ptz param 
	BYTE PasswordSwitch:2;        //First bits for this function, Second for password switch
	BYTE NvrFlag:2;               //n1104:0,others:1
    BYTE MaintainUserEnabled:1;   //just in compatible with former version
    BYTE MdStreamFlag:1;         //������Ȩ�޿���

	BYTE MaxPOENum;
    BYTE UiType;             //ui 1.0, 2.0, 3.0, 3.1
    BYTE ChipNum;            //�豸оƬ��
    UINT ProtocolType;       //ÿһλ����һ��Э�飬0��֧�֣�1֧��

    BYTE QueryRHMIFlag:1;    //��ѯ¼��Ӳ�̡��ƶ���⡢IO״̬����ʱlorex(flir)
    BYTE compatUpgrade:1;    //����lorex�ͻ��˼�������ͻ�ȡ�豸״̬
    BYTE supportMutiEmail:3; //�Ƿ�֧�ֶ��ʼ�����.0:1���ʼ�;1:3���ʼ�(lorex)
    BYTE showVersionFlag:1;  //�Ƿ���ʾ���汾��Ϣ����ʾ��(lorex).0:����ʾ;1:��ʾ
    BYTE honeyNewChName:1;   //honeywell OSDͨ����,֧��8������(utf-8����)
    BYTE pppoeFlag:1;        //0 ������PPPoE����, 1 ����PPPoE����
    BYTE maxChFps;           //��ͨ�����������֡��.1:720P 15FPS; 2:1080P 15FPS;Ĭ��Ϊ0
    WORD maxTotalFPS;        //����ͨ�������֡���ܺ�
    BYTE hybirdDVRFlag:4;    //���dvr��־
    BYTE FrameAutoFlag:1;    //֡���Զ����ڿ���(ĿǰΪ��Qt DVR)
    BYTE customProtolFlag:1; //Զ���Ƿ���ʾ�Զ�������Э��ҳ��(NVR)
    BYTE sgPlatformFlag:1;   //Զ���Ƿ���ʾ���ƽ̨ҳ��(NVR)
    BYTE PushEnabled:1;      //�Ƿ����������͹���.0: close, 1: open.
    BYTE AnalogChNum;        //���DVR ��ģ��ͨ���ĸ���
    BYTE BitrateMode;        //����ѡ������, ���DVR�ض�ϵ�в�Ʒ�ͺ�
    BYTE ShowSensorAlarm:1;  //Զ���Ƿ���ʾ����������ҳ��,0: ����ʾ;1: ��ʾ(DVR)
    BYTE ZeroChFlag:1;       //0ͨ�����ܿ���(ZIP�ͻ�)
    BYTE GetAlarmChns:1;     //�±����ϸ淽ʽ,1:һ�λ�ȡĳ�¼���Ӧ������ͨ��������Ϣ,(Ĭ��0)
    BYTE CoaxialFlag:1;      //�Ƿ�֧��ͬ�Ṧ��. 1:support, 0:not support    
    BYTE eSATAEnabled:4;     //�豸�Ƿ�����ESATA����.(NVR)

    char p2pId[32];         //P2P Id(OWL�ֻ�����)
    WORD totalFrameRes;     //֡������Դ (ĿǰΪ��Qt DVR)
    BYTE DevPlayBackCap;    //0:�ɵĻط�ģʽ��1:�������ֻȡI֡ģʽ��2:���������I֡ģʽ
    BYTE PushType;          //0:tutktype(������tutk�����Գ���OWL�ɷ�����64.91.227.90), 1:rstype,  2: tpns2.0 �·�����ר��(host.nightowldvr04.com)
    BYTE DLMode;
    BYTE ZipFlag;           //0:nozip , 1:zip
    BYTE RemoteSearchLogFlag;           //�Ƿ�֧��Զ��������־1:enable, 0:disable
	BYTE KguardDomeFlag:1; //kgҪͶ����ǣ�0��no�� 1��yes
	BYTE HKDemoFlag:1; //���������ʶ��0��no�� 1��yes
	BYTE AIFlag:1;     //new AI :1 , old AI :0
	BYTE RSDomeFlag:1;//ңͷ�������ǣ�0��no�� 1��yes	
	
	BYTE NewEmailTest:1;
	BYTE c32UserNameFlag:1;// ʹ�ó��û�����ʶ����1Ϊʹ��32�ֽڵ��û�����0Ϊ��ʹ��
	BYTE reserv:2;
	UINT PreviewChannel_EX[8];     //Ԥ��ͨ��
	UINT PlayBackChannel_EX[8];       //�ط�ͨ��
	UINT BackupChannel_EX[8];        //����ͨ��
	UINT PtzControlChannel_Ex[8];     //��̨����ͨ��
	U32  PageControl; // 0)display image 1)IRIS 2)samsung customer 3)intelligent analysis 4)area encode 5) intelligent manage
	FishEyeIpc_Cap_t FishEyeIpcCap;
	WORD CustomerVal;//CustomVal_E
	BYTE PreviewNum; //����Զ��������Ԥ��ͨ����
	BYTE DefualtStream;//ipcĬ��IE��¼��ʾ����0:������ 1: ������2: �ֻ�����
    U32 PageControl2;//PageControl2_E
    AutoFocus_Default_t  AutoFocusDefault;
	BYTE WizardFlag:1;
	BYTE reserv3:7;
	BYTE PirAreaMode;//1Ϊʹ��������PIR�������� 0Ϊ����ģʽ
	BYTE TalkMode;//0: old device , 1: audio talkback with ipc use half-duplex mode . 2 :full duplex mode, 3 : all mode 
	BYTE HddOverWriteMode; //0: Ĭ���б� 1: URMET �б�(1day/2days/3days/4days/5days/6days/7days/14days/30days/90days)
	U32  ControlBit;//ControlBit_E

	BYTE s8SIAIntVersion[16];
	BYTE s8SIAModelsVersion[16];
	U32  ControlBit2;//ControlBit2_E
	U32  SNSUsrInfoID;
	UINT ClientAutoLogoutTime;
    BYTE MaxCloudVideoUploadNum;  /* ��ͨ�������ϴ���Ƶ������ */
    BYTE UserId;//0:admin,1:user1,2:user2....
    BYTE reserv4[2];
    UINT PreviewCovert[8];
    UINT PushInfoType; //APP����Ҫ��ʾ����������(PushType_E)
    U32  ControlBitArray[8];//ControlBitArray_E
    UINT SupportEncAbility;	//֧�����õ���Ƶ�����ʽ,bit0:H264 bit1:H265 bit3:H264+ bit4:H265+
	char DeviceType[MaxNameLen];
	char SerialNumber[32];
	BYTE reserv5[8*100-224];
}LoginRsp;
//C_ASSERT(sizeof(LoginRsp) == 1232);

typedef enum
{
	CTBIT0_E = 0,//lorex
	CTBIT1_E = 1,//1:support H264+, 265+, 0 :
	CTBIT2_E, /*�Ƿ�֧��SD��1:֧��0:��֧��*/
	CTBIT3_E, /*�Ƿ�֧��Google home*/    
	CTBIT4_E, /*network �� switch ҳ��ϲ� 1:�ϲ� 0�����ϲ�*/
	CTBIT5_E, /*�Ƿ�֧�ַ�����ʱ���������ɫֵ*/
	CTBIT6_E, /*�Ƿ���ʾoutput����ҳ��*/
    CTBIT7_E, /*�Ƿ�֧���޸�IPC�������*/
	CTBIT8_E, /*�Ƿ�֧�ֶ�ͨ���豸IP�����*/
	CTBIT9_E, /*�Ƿ�֧��HTTPS 0:��֧�� 1��֧��*/
	CTBIT10_E,/*�Ƿ�֧��IR�ƿ������� 0:��֧�� 1��֧��*/
	CTBIT11_E,/*�Ƿ�֧��IRʱ������ 0:��֧�� 1��֧��*/
	CTBIT12_E,  /* IRCUT MODE �Ƿ�ȡ����ʾGPIO AUTO ѡ�� ��0: ��ȡ����ʾ; 1: ȡ����ʾ*/
	CTBIT13_E,/*�Ƿ���ʾI֡���,0:��ʾ��1������*/
	CTBIT14_E,/*֧������ѷIOT����ҳ��*/
	CTBIT15_E,/*sound alarm��ʾ��־λ��0���أ�1����ʾ*/
	CTBIT16_E,/*ftp video��ʾ��־λ��0���أ�1����ʾ*/
	CTBIT17_E,/*�Ƿ�֧���ֶ�¼�����͵�����*/
	CTBIT18_E,/*�Ƿ����� ������ҳ��,Ĭ������ʾ,1:hide, 0:show*/
	CTBIT19_E,/*�Ƿ����� ������ҳ��,Ĭ������ʾ,1:hide, 0:show*/
	CTBIT20_E,/*�Ƿ����� �ֻ���ҳ��,Ĭ������ʾ,1:hide, 0:show*/
	CTBIT21_E,/*ץͼ��չ��ʾ��־λ��0���أ�1����ʾ*/
	CTBIT22_E,/*IP Filter��ʾ��־λ��0���أ�1����ʾ*/
	CTBIT23_E, /* �Ƿ�֧��ģ��ͨ��MJPEG���� */
	CTBIT24_E,/*FTP������ʾ��־λ��0���أ�1����ʾ*/
	CTBIT25_E,/*�Ƿ��ֻ���֧��http����*/
	CTBIT26_E,/*�Ƿ�֧����Ƶ�����쳣��⹦�ܣ�0�����أ�1����ʾ*/
	CTBIT27_E,/*�Ƿ���ʾPTZ����ҳ�棺0��ʾ��1����*/
	CTBIT28_E,/* �Ƿ�֧�ֿͻ���smart����, 0:��֧�� 1��֧�� */
	CTBIT29_E,/* �Ƿ�֧�ֶ���¼��, 0:��֧�� 1��֧�� */
	CTBIT30_E,/* HDVRĬ��ʹ��264¼���ʽ��D31����ϵ��HDVRĬ��ʹ��RF��ʽ  0:264��1��RF*/
	CTBIT31_E,/*FTP Video Upload�ͼƻ�����,0:���� 1:��ʾ*/
}ControlBit_E;

typedef enum
{
    COBIT0_E = 0,///*�Ƿ���ʾ��Ƶ�ڵ�����*/
    COBIT1_E = 1,//�Ƿ�֧�ֵ��򲥷ţ�0��֧�֣�1֧��
    COBIT2_E ,   //IE�ط�ҳ���Ƿ�֧�ֶ�·�طţ�����4·��1֧��
    COBIT3_E ,   //1:����nvr��0�������豸
    COBIT4_E,    //����OD���ܣ���1��  not display,	 ��0�� display
    COBIT5_E ,	 // ���ptz��ʱ������  1:���� 0:�ر�
    COBIT6_E ,	 // ���ptz��ά��λ����  1:���� 0:�ر�
    COBIT7_E,    //1:֧��NewRecordDetailRsp (New_GetRecFileList)������0����֧��
    COBIT8_E,    //1:֧��NewRecordDetailRsp (New_GetRecFileList)¼�����أ�֧��¼���ļ�������ѯ�Լ��������� ,0����֧��
	COBIT9_E,	 // ����������ܣ�1:������0:�ر�
	COBIT10_E,   //�Ƿ�֧�ֱ�����������  1:֧�� 0:��֧��
	COBIT11_E,   //ģ��ͨ���Ƿ�����P/DЭ��  1:���� 0:��ʾ
	COBIT12_E,   //cmsͼƬ�طŹ���   1������ 0���ر�
    COBIT13_E,  //�Ƿ�ʹ���µı����ṹ��0: RSNet_SoleIOAlarmSet_t, 1:RSNet_NewSoleIOAlarmSet_t
    COBIT14_E,  //�ƴ洢�ϴ���Ƶ 1:֧�� 0:��֧�� (ֻ����alarm_motion,alarm_pir,alarm_ioҳ��)
	COBIT15_E,  //�Ƿ�֧��toe���ٹ��ܣ�0����֧�֣�1��֧��
	COBIT16_E,   //�Ƿ�ȡ��WB����ģʽ   1��ȡ�� 0����ȡ��
	COBIT17_E,   //�Ƿ�֧��ipeye ��0����֧�֣�1��֧��
	COBIT18_E,	 //�Ƿ�֧�����ܼ�PIR�Ŀ��� ��0����֧�֣�1��֧��
	COBIT19_E,	 //�Ƿ�֧��QVBR���� 1��֧�֣�0����֧��
	COBIT20_E,   //User Page SEQ Control,  0:hide, 1:show
	COBIT21_E,   //   0:413, 1:427(MsgEmailTestNew)
    COBIT22_E,    //�ƴ洢�ϴ�ͼƬ 1:��֧�� 0:֧�֣�Ϊ�˼���֮ǰ�İ汾��
	COBIT23_E,   // ʹ��upnp��������
	COBIT24_E,   // ʹ��FTP��չ��ַ����16λ����64λ
	COBIT25_E,  //�Ƿ��OSD ͸��������1:֧�� 0:��֧��
    COBIT26_E,  //�Ƿ�֧���µ���־���������� 1:֧�� 0:��֧�� ---IPC
    COBIT27_E,  //�Ƿ�֧�ָ澯����ƻ������� 1:֧�� 0:��֧��
    COBIT28_E,  //�Ƿ�֧��NAS���� 1:֧�� 0:��֧��
    COBIT29_E,   //�Ƿ�֧��RAID���� 1:֧�� 0:��֧��
    COBIT30_E   //�Ƿ�֧��log���������� 1:֧�� 0:��֧��  ---dvr/nvr.
}ControlBit2_E;

typedef enum
{
    CoBitAry_0,  //�Ƿ�֧��3��1���� 1:֧�� 0:��֧��
    CoBitAry_1,  //�Ƿ���ʾwireless cameraҳ�� 1:��ʾ 0:����ʾ
    CoBitAry_2,   //�Ƿ���ʾchannel configҳ�� 1:��ʾ 0:����ʾ
    CoBitAry_3,	//�Ƿ���ʾ�µ�FD����ҳ�� 1����ʾ 0������ʾ
    CoBitAry_4,	//�Ƿ�֧��FTP���� 1��֧�� 0����֧��
    CoBitAry_5, //�Ƿ�֧��imageҳ������ҹ����
    CoBitAry_6, //���������ϱ���1��֧�֣�0����֧��
	CoBitAry_7,	// ����������ѯ������, 1:֧�֣�0����֧��
	CoBitAry_8, //�Ƿ�֧�����ܷ���������Ƶ�����ѯ��Motion��PIR��Ӳ��״̬/VIDEO LOSSS��IO��6�����ܼ��������ڵ�����  1:֧�֣�0����֧��
	CoBitAry_9,//NotificationSchedule ҳ��, 1:��ʾ��0:���ء�
	CoBitAry_10, //�Ƿ�֧�ְ׹�ǿ�Ʋʹ⹦��  1:֧�֣�0����֧��
	CoBitAry_11, //�Ƿ�֧��IE���ذ��ץͼ
	CoBitAry_12, //�Ƿ�֧��IE���뵼��IPC����
	CoBitAry_13, //���Ͳ���֧��json��ʽ����
	CoBitAry_14, //�Ƿ�֧��ipeye����������1:֧�֣�0����֧��
    CoBitAry_15,  //�Ƿ�֧��Alarm�ƻ���, 1:֧�֣�0����֧��
	CoBitAry_16, //�Ƿ�֧�ְ���ͺ�ҹ���ײ����ֿ����ã�1:֧�֣�0����֧��
	CoBitAry_17, //�Ƿ�֧��ǿ�����ƹ���HLC��1:֧�֣�0:��֧��
	CoBitAry_18, //�������ܷ����� PID LCD SOD������Ŀ
	CoBitAry_19, //�������ܷ����� PD ��Ŀ
	CoBitAry_20, //�������ܷ����� CC ��Ŀ
	CoBitAry_21, //�������ܷ����� FD ��Ŀ	 1 ���� 0 ��ʾ
	CoBitAry_22, //����Image Control��Angle Rotation��  1 ���� 0 ��ʾ	
	CoBitAry_23, //�Ƿ�֧����־����ҳ��json͸�� 1:֧�֣�0����֧��
	CoBitAry_24, //�Ƿ�֧��Ӳ��ҳ��json͸�� 1:֧�֣�0����֧��
	CoBitAry_25, //�Ƿ���ʾ���ܷ���ͳ��ҳ�棬0:��ʾ��1:����ʾ
	CoBitAry_26,	  //�Ƿ���ʾ�µ�PD����ҳ�� 1����ʾ 0������ʾ
	CoBitAry_27, //�Ƿ���ʾONVIFҳ�� 1:��ʾ  0:����ʾ
    CoBitAry_28, /*֧��google IOT����ҳ��*/
    CoBitAry_29, //1:support watermask
    CoBitAry_30, //PTZ Linkage����֧��json��ʽ����
    CoBitAry_31, //ץͼҳ��ץͼ�����ȼ� 0:(good/better/best) 1:(best/better/good/bad/worse/worst)
	CoBitAry_32,// �Ƿ�֧�����ˡ������������ܣ� 1��֧��   0����֧��
	CoBitAry_33 , //�Ƿ�֧���ֻ��ƴ洢���1Ϊ֧��
	CoBitAry_34, //�Ƿ�����DDNSҳ�棬1Ϊ����
	CoBitAry_35, //�Ƿ���ʾCC Ruletype(A->B)��1Ϊ��ʾ    
	CoBitAry_36,	//�Ƿ�����NETWORK�����UPnP���棬 1 ���� 0 ������
	CoBitAry_37,	//�Ƿ�����NETWORK�����Email���棬 1 ���� 0 ������
    CoBitAry_38,	//�Ƿ�����NETWORK�����IPFliter���棬 1 ���� 0 ������
    CoBitAry_39,   // IPC������ʶ���Ƿ�֧������ֵ���㹦�ܣ�1��֧�֣� 0����֧��
    CoBitAry_40,  //���� 1:͸�� 0:��͸��
    CoBitAry_41, //user Ȩ�� 1:����ж� 0: �ͻ����ж�
    CoBitAry_42,//1 :single channel playback 0:normal playback
	CoBitAry_43,//1:liteos_net����
	CoBitAry_44,    //֧��POE��������
}ControlBitArray_E;

typedef enum
{
    SHOW_HDD,
    SHOW_MOTION,
    SHOW_IO,
    SHOW_PIR,
    SHOW_SMART,
    SHOW_VIDEOLOSS,
    SHOW_FACEALARM,
    SHOW_HumanVechicle
}PushType_E;

//////////////////////////////////////////////////////////////////////////
//����
//���� MsgType=MsgHeartbeat
//��Ӧ 


//////////////////////////////////////////////////////////////////////////
//��

//PackHead.Version
#define PackHeadV1		0
#define PackHeadV2      1

#define MaxPackSize		    1400
#define MaxPackSize_2       (8*1024)

//PackHead.Type
#define FramePack				0 //֡��ֵİ�
#define ReposPack				1 //�ط�ʱ�ض�λ��������������͵����ض�λ�������
#define NoDataPack				2 //�ط�ʱ��ʾ��ǰ�ط�ʱ�������Ѿ�û��¼������
#define FileEndPack				3 //¼������ʱ��ʾһ���ļ��������
#define IFrameEndPack  			4 //I ֡���ݽ���
#define IsThumbnailsPack        5 //����ͼ
#define TalkPassthroughHeart    6
#define ReversePack             7 // ���򲥷ſ�ʼ

typedef struct
{
	BYTE Version : 2; //��ͷ�汾
	BYTE ExtSize : 6; //��ͷ��չ��С��ʵ����չ��С = ExtSize * 4
	BYTE Type;
	WORD PackNum;
	UINT FrameNo;
	WORD PackNo; //0,1,2,3...
	WORD PackSize;
}PackHead; //��ͷ, sizeof(PackHead) = 12


//////////////////////////////////////////////////////////////////////////
//Ԥ��

//Type
#define PreviewMain	0
#define PreviewSub	1
#define PreviewMobile 2

//Content
#define PreviewComposite	0
#define PreviewVideoOnly	1

typedef struct
{
	UINT Channel; //ͨ���� 0,1,2,3...
	BYTE Type; //��������
	BYTE Content; //����������Ƶ��
    BYTE timepos; //��ȡ¼���ʱ��㣺0 ��ǰʱ��� 1 ����¼��ʱ���
    BYTE bufsize; //���֡���ݴ�С,ʵ�ʴ�С = bufsize*1024*10; 
}PreviewParam;


//////////////////////////////////////////////////////////////////////////
//TCPԤ��
//���� MsgType=MsgTcpPreview, MsgSize=sizeof(TcpPreviewReq)
//��Ӧ �ɹ�AckFlag=AckSuccess ʧ��AckFlag=AckFail

typedef struct
{
	PreviewParam Param;
	UINT UserKey;
}TcpPreviewReq;


//////////////////////////////////////////////////////////////////////////
//UDP̽��
//���� MsgType=MsgGetUdpAddr
//��Ӧ MsgSize=size(GetUdpAddrRsp)

typedef struct
{
	struct sockaddr_in ClientAddr;
	UINT socketfd;
	BYTE Addr[44];
}GetUdpAddrRsp;


//////////////////////////////////////////////////////////////////////////
//UDP��ʼԤ��
//���� MsgType=MsgStartUdpPreview, MsgSize=sizeof(UdpStartPreviewReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=sizeof(UdpStartPreviewRsp) ʧ��AckFlag=AckFail

typedef struct
{
	GetUdpAddrRsp Rsp;
	PreviewParam Param;
}UdpStartPreviewReq;

typedef struct
{
	UINT UdpPreviewKey;
}UdpStartPreviewRsp;


//////////////////////////////////////////////////////////////////////////
//UDPֹͣԤ��
//���� MsgType=MsgStopUdpPreview, MsgSize=sizeof(UdpStopPreviewReq)
//��Ӧ 

typedef struct
{
	UINT UdpPreviewKey;
}UdpStopPreviewReq;


//////////////////////////////////////////////////////////////////////////
//ǿ��I֡
//���� MsgType=MsgForceIFrame, MsgSize=sizeof(PreviewParam)
//����Ҫ��Ӧ
typedef struct 
{       
	UINT Channel; //ͨ���� 0,1,2,3...
	BYTE Type;    //��������,ͬԤ��
	BYTE Reserved[7];
} IFrameReq;

//////////////////////////////////////////////////////////////////////////
//��̨����
//���� MsgType=MsgPTZControl, MsgSubtype=MsgPTZUp..., MsgSize=sizeof(PTZControlReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, ʧ��AckFlag=AckFail

#define PTZMinSpeed			0
#define PTZMaxSpeed			100
#define PTZMinCruiseNo		0
#define PTZMaxCruiseNo		63
#define PTZMinPresetIndex	1
#define PTZMaxPresetIndex	255

//Flag
#define PTZControlStart	0
#define PTZControlStop	1

typedef struct
{
	UINT Flag;
	UINT Speed;
}PTZControlNormal;

typedef struct
{
	UINT Flag;
	UINT No;
	UINT Time; /* Ԥ�õ�Ѳ�����ʱ��
				  0  ��ʾ5S ; 1 ��ʾ10S; 2 ��ʾ15S */
	UINT LineSpeed;
}PTZControlCruise;

typedef struct
{
	UINT Index;
    UINT Time;  /* Ԥ�õ�Ѳ�����ʱ�� */
}PTZControlPreset;
typedef struct
{
	UINT  CruiseIndex; // ???,??4??? 1-4
	BYTE PpCount; //?????
	BYTE PauseSecs; // ???????
	BYTE Speed; //????
	BYTE Reserved[1];
	BYTE Pps[32]; //?????,????32?
}PTZControlSetPPCruise;

typedef struct
{
	UINT CruiseIndex;//???,1-4
	BYTE Reserved[4];
	
}PTZControlCallCruise;

typedef struct
{
    int PresetNum;
    int reserv[7];
}PTZPresetNum_t;
typedef struct
{
	/*base on 704 * 576 position*/
	int x;
	int y;
	int w;
	int h;
}PTZ3DPosition;
typedef struct
{
	UINT Channel;
	union
	{
		PTZControlNormal Normal; //MsgPTZUp...MsgPTZAutoScan
		PTZControlCruise Cruise; //MsgPTZCruise
		PTZControlPreset Preset; //MsgPTZSetPreset...MsgPTZCallPreset
        PTZPresetNum_t PresetNum; //MsgPTZGetPresetNum
		PTZControlSetPPCruise ppsCruise;//MsgPTZSetPPCruise
		PTZControlCallCruise idxCruise;//MsgPTZCallPattermCruise,MsgPTZCallPPCruise,MsgPTZStartPattermCruise,MsgPTZEndPattermCruise
		PTZ3DPosition Position3D;
	};
}PTZControlReq;

/*ipc, kg����*/
typedef struct
{
	BYTE Sensor_id[32]; /* ��ѯָ��sensor ID Ԥ��λ */
	UINT PresetIndex;  /* ָ��sensor ID Ԥ��λ��Χ(0 -16)*/ 
}PTZSensorPresetInfo;
//////////////////////////////////////////////////////////////////////////
//ɫ�ʿ���
typedef struct
{
	UINT Channel;
	BYTE Chroma;       /* ɫ��, <0 - 63> */
	BYTE Brightness;   /* ����, <0 - 63> */
	BYTE Contrast;     /* �Աȶ�, <0 - 63> */
	BYTE Saturation;   /* ���Ͷ�, <0 - 63> */
	BYTE reservel[20];
}ColorCtrlReq;

//////////////////////////////////////////////////////////////////////////
//ʱ��ṹ

//typedef struct
//{
//	WORD Year; //2011
//	BYTE Month; //1 ~ 12
//	BYTE Day; //1 ~ 31
//	BYTE Hour; //0 ~ 23
//	BYTE Minute; //0 ~ 59
//	BYTE Second; //0 ~ 59
//	BYTE Reserved;
//}DateTime;


//////////////////////////////////////////////////////////////////////////
//¼���ѯ ��λ��ѯ��һ��32λ

//RecordType
//#define NormalRecord	0x1
//#define AlarmRecord		0x2
//#define AllRecord		0xFFFFFFFF //Only for req, equal to NormalRecord|AlarmRecord...

#define NoRecord            0x0
#define NormalRecord        0x1
#define AlarmRecord         0x2
#define MotionRecord        0x4
#define IORecord            0x8
#define PEARecord           0x10   // �����ܣ������ܲ���ʹ��
#define PEALineRecord       0x10   // 2015.11.30
#define AVDRecord           0x20
#define OSCRecord           0x40
#define AllIntelliRec       0x80
#define SensorRecord        0x100
#define PEAAreaRecord       0x200   // 2015.11.30/2016.03.09
#define OCCRecord           0x400   //private zone
#define NetbreakRecord      0x800   //netbreak
#define HDRecord            0x1000  // 2016.03.09
#define FDRecord            0x2000  // 2016.03.09
#define PCCRecord           0x4000  // 2016.03.09
#define MothionAndIo        0x8000  // 2017.02.09
#define PIRRecord           0x10000 //2017.05.09
#define SoundRecord         0x20000 //2018.05.03
#define ManualRecord        0x40000 //2018.05.09
#define SmartRecord         0x80000 //2018.05.30
#define INE_ALL_RECORD      (PEARecord|PEALineRecord|AVDRecord|OSCRecord|PEAAreaRecord|HDRecord|FDRecord|PCCRecord|ManualRecord)
#define AlarmAssemble       0x7FFFFFFF//���������������ϵı�������ʱ���ϴ���ֵ
#define AllRecord           0xFFFFFFFF

//typedef struct
//{
//    UINT Channel;
//    DateTime Begin;
//    DateTime End;
//    UINT Type; //RecordType
//    UINT Channel_EX[8];
//    U8 StreamType;//PLAY_BACK_STREAMTYPE_E
//    U8 reserved[7];
//}QueryRecordReq;

//�������ַ�ʽ��ѯ,��Ӧʱ,����ʱ�������¼��,ҲӦ���سɹ�AckFlag=AckSuccess, MsgSize=0

//���� MsgType=MsgQueryRecord, MsgSubtype=MsgRecordDetail, MsgSize=sizeof(QueryRecordReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=n*sizeof(RecordDetailRsp) ʧ��AckFlag=AckFail

typedef struct
{
    UINT Channel;
    DateTime Begin;
    DateTime End;
    UINT Type;              //RecordType
    UINT Channel_EX[8];
    U8 StreamType;          //PLAY_BACK_STREAMTYPE_E
    U8 SmartSearch;         //1: enable smart search, 0: disable
    U8 reserved[6];
    UINT SmartRegion[18];	//smart search area

}QueryRecordReq;

//�������ַ�ʽ��ѯ,��Ӧʱ,����ʱ�������¼��,ҲӦ���سɹ�AckFlag=AckSuccess, MsgSize=0

//���� MsgType=MsgQueryRecord, MsgSubtype=MsgRecordDetail, MsgSize=sizeof(QueryRecordReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=n*sizeof(RecordDetailRsp) ʧ��AckFlag=AckFail

typedef struct
{
	UINT StructSize; //sizeof(RecordDetailRsp)
	DateTime Begin;
	DateTime End;
	UINT Type; //RecordType
	UINT Size; //�ļ���С
}RecordDetailRsp;

//���� MsgType=MsgQueryRecord, MsgSubtype=MsgRecordDayOutline, MsgSize=sizeof(QueryRecordReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=n*sizeof(RecordDayOutlineRsp) ʧ��AckFlag=AckFail

typedef struct
{
	UINT StructSize; //sizeof(RecordDayOutlineRsp)
	WORD Year; //2011
	BYTE Month; //1 ~ 12
	BYTE Day; //1 ~ 31
	BYTE Hour; //0 ~ 23
	BYTE Minute; //0 ~ 59
	BYTE Second; //0 ~ 59
	BYTE Type;
}RecordDayOutlineRsp;

typedef struct
{
	UINT StructSize; //sizeof(RecordDayHalfHourRsp)
	WORD Year;       //2011
	BYTE Month;      //1 ~ 12
	BYTE Day;        //1 ~ 31
	BYTE HarfHour;   //0 ~ 47
	BYTE Minute;     //0 ~ 59
	BYTE Second;     //0 ~ 59
	BYTE Type;
}RecordDayHalfHourRsp;


//////////////////////////////////////////////////////////////////////////
//¼������
//���� MsgType=MsgDownloadRecordFile, MsgSize=sizeof(DownloadRecordFileReq)+n*sizeof(RecordDetailRsp)
//��Ӧ �ɹ�AckFlag=AckSuccess ʧ��AckFlag=AckFail
//��������: file1,FileEndPack; file2,FileEndPack; ... filen,FileEndPack
typedef struct
{
	UINT StructSize; //sizeof(DownloadRecordFileReq)
	UINT UserKey;
	UINT Channel;
	BYTE StreamType;//PLAY_BACK_STREAMTYPE_E
    BYTE useNewRsp;
	BYTE reserv[10];
}DownloadRecordFileReq;


//////////////////////////////////////////////////////////////////////////
//¼��ط�

//��ʼ�ط�
//���� MsgType=MsgRecordPlay, MsgSize=sizeof(RecordPlayReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, ʧ��AckFlag=AckFail, ��Ӧ�󲻷�������,ͳһ���յ�MsgRecordDataInsufficient����

typedef struct
{
	UINT UserKey;
	UINT Channel;
	UINT Type; //RecordType
	DateTime Begin;
	DateTime End;
	BYTE StreamType;//PLAY_BACK_STREAMTYPE_E
	BYTE ExactFrame[39]; 
}RecordPlayReq;

//�طŷ���
//���� MsgType=MsgRecordPlayFeedback, MsgSubType=MsgRecordDataInsufficient,MsgRecordDataEnough
//����Ҫ��Ӧ

//�ض�λ¼������
//���� MsgType=MsgReposRecordData, MsgSize=sizeof(ReposRecordDataReq)
//����Ҫ��Ӧ,�յ�����Ϣ��,����ֹͣ����֮ǰ������(���������Ƿ�����һ�������İ�֮��),���ŷ���ReposPack,����Ƿ����µ�����
typedef struct
{
	DateTime Begin;
	DateTime End;
}ReposRecordDataReq;

//���� �ڽ�������ʱ,���ᷢ�ʹ���Ϣ
//���� MsgType=MsgHeartbeat
//����Ҫ��Ӧ


//////////////////////////////////////////////////////////////////////////
//�Խ�
//���� MsgType=MsgDualtalk, MsgSize=sizeof(DualtalkReq)
//��Ӧ �ɹ�AckFlag=AckSuccess ʧ��AckFlag=AckFail

typedef struct
{
	UINT UserKey;
}DualtalkReq;

typedef struct
{
	UINT structSize;

	UINT UserKey;
	UINT ch;
	BYTE resver[4];
}DualtalkChannelReq;

typedef struct
{
    UINT structSize;
    UINT UserKey;
    UINT ch;
    BYTE resver[4];
}DualtalkPassthroughReq;

//////////////////////////////////////////////////////////////////////////
//��־��ѯ

//LogType
#define LOG_TYPE_IO         0x0
#define LOG_TYPE_MD         0x1
#define LOG_TYPE_HDD        0x2
#define LOG_TYPE_VLOSS      0x3
#define LOG_TYPE_OPERA      0x4  // ��ѯʹ��
#define LOG_TYPE_ALARM      0x5  // ��ѯʹ��, ����io��md����Ƶ��ʧ��Ӳ��     
#define LOG_TYPE_ALL        0x6  // ��ѯʹ��, ȫ��

//Operation type
#define LOG_OPT_FIRST  0x0
#define LOG_OPT_NEXT   0x1
#define LOG_OPT_PREV   0x2 
#define LOG_OPT_LAST   0x3
typedef struct
{   
    DateTime Begin;
    DateTime End;
    UINT Type; 
    UINT Operation;  // �û�����:��һ����ʾ;��һҳ;��һҳ;���һҳ
    UINT ExpectNum;  // ϣ�����صĸ���
}QueryLogReq;

/*����DVRʹ��*/
typedef struct
{
    UINT StructSize; //sizeof(QueryLogRsp)
    UINT Channel;
    UINT Type;
    DateTime Point;
    BYTE Reserved[4];
}QueryLogRsp;

/*����IPCʹ��*/
typedef struct
{
	UINT StructSize;
	char event[64];		///< event description
	BYTE Reserved[4];
}QueryLogRsp_IPC;

//////////////////////////////////////////////////////////////////////////
//��������

//Element : ElementSize + ExtensibleStruct + zero or more List
//List : ListSize + one or more Element
//ExtensibleStruct : StructSize + other member define
//ע��: Element���ٱ�����һ���ǿյ�ExtensibleStruct��ֻ��һ��StructSize=4�Ľṹ��ʾ�յ�)��ǿյ�List�������Element��ʾ�յģ������壩Ӧɾȥ
//		List���ٱ�����һ��������һ����Element

//��Ӧ �ɹ�AckFlag=AckSuccess ʧ��AckFlag=AckFail ��������AckFlag=AckParamError, Ȩ�޲���AckFlag=AckAuthorityFail



typedef struct
{
	UINT StructSize;
	UINT ChannelMask[8];
}ChannelParamReq;

//////////////////////////////////////////////////////////////////////////
//�澯�ϱ�
//���ֱ���ϱ����ͻ��������Ӧ
//
//MsgType=MsgAlarmReport
//�ƶ����: MsgSubType = MsgMotionAlarm, MsgSize = sizeof(MotionAlarmRpt)
//IO����: 	MsgSubType = MsgIOAlarm, MsgSize = sizeof(MotionIORpt)
//���ܷ���: MsgSubType = MsgAIAlarm, MsgSize = sizeof(MotionAIRpt)

//Status
#define AlarmOn  1 
#define AlarmOff 0 

typedef struct
{
	UINT Channel;
	int Status;
	DateTime AlarmTime;
    char RecState;               /* ¼��״̬ */
    char CurRecType;             /* ��ǰ¼������ */
    char Schedule;             /* �����ƻ�*/
	char RecEnable;           /* �Ƿ�������¼���� */
    UINT ProtocolType;  /* IPCЭ������ */
	UINT Abilities;     /* IPC�豸���� */
	UINT Channel_EX[8];
	UINT Status_EX[8];
	UINT IPCDevTypeFlag; /*IPC�豸����*/
	U8 MsgValidFlagIPCWeb; // whether the msg is valid for IPC IE , 0:valid , 1:invalid (2016.10.28 add)
	U8  InputNum;                 /*ipc io��������·��*/
	U8  OutputNum;                /*ipc io�������·��*/
	U8  bBoxEnable : 1; //����ʹ�� 20170928 ����Ƿ����web����
	U8  bBoxDisplay : 1;//������ʾ 20170928 ��������ʱ�Ƿ���ʾ����
	U8  Reserve : 6;
	UINT AlarmType;
	/*0:NORMAL;    1:MDALARM;   2:IOALARM;   3:SMART_PEALINE;   4:SMART_AVD;     5:SMART_OSC;
	6:SMART_PEAAREA;  7:SMART_HD;  8:SMART_FD;    9:SMART_CC;*/
	BYTE PowerStat[256];
	BYTE DevName[128];
	BYTE IOName[64];
	U8  bChnMode;  /*0:˯��ģʽ,1:����ģʽ*/
	BYTE res[3];
	UINT ClientAutoLogoutTime ;
	UINT AbilitiesEx;
	BYTE resver[52];
}RsNetAlarmRpt;

typedef struct
{
	UINT StructSize;
	UINT chn;       /* 0xffffffff ��ʾ����ͨ��������ֵ��ʾ������ֵָ����ͨ�� */
	UINT pageType;
	char reser[128];
}INTF_DEVPARAM_CHANGE_S;

typedef struct{
    short x1;
    short y1;
    short x2;
    short y2;
}Net_Rule_Line_S;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
}IntelligentAlarmRpt;


/* �ܽ���� */
typedef struct {

    BYTE ChnSwitch;          /*0-�رգ�1-��*/
    BYTE RuleSwitch;         /*ÿ��ͨ����һ���ֽڱ�ʾ���8������0-�رգ�1-ʹ��*/
    BYTE RuleType;           /*ÿ��ͨ����һ���ֽڱ�ʾ���8��-�������ͣ�0-���ߣ�1-�ܽ�*/
    BYTE LineTwoWay;         /*ÿ��ͨ����һ���ֽڱ�ʾ���8��-��������˫��0-��1-˫��*/
    BYTE reserver[4];
    Net_Rule_Line_S RuleLine[32];	/*ÿͨ�������64��������,��32���ߣ�����ǰ�����ֻʹ�õ�1���ߣ�
                                 ������ܽ�����8������������������ɱպ�ͼ�� */
}SolePEALineMsg;

typedef struct
{
    SolePEALineMsg RuleLine[32];

}SolePEAAlarmRpt;


/* ��Ʒ������ʧ*/
typedef struct{
    BYTE ChnSwitch;         	 /*0-�رգ�1-��*/
    BYTE RuleSwitch;        	 /*ÿ��ͨ����һ���ֽڱ�ʾ���8������0-�رգ�1-ʹ��*/
    BYTE reserve[6];
    BYTE RuleRectEnable[8];  	 /*ÿͨ�������8������ÿ���������4����.ÿһλ����һ�������ʹ�ܣ�Ŀǰֻ��ǰ��λ*/
    Net_Rule_Line_S RuleRect[32];/*ÿ���������4����,��ÿͨ�������8��4��32������*/
}SoleGoodsLostMsg;

typedef struct
{
    SoleGoodsLostMsg RuleLostLegacy[32];

}SoleGoodsLostAlarmRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
}AvdAlarmRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
}VLossAlarmRpt;


//MsgDevStatReport
//MsgNormalStatusReq
typedef struct
{
	UINT Channel;
	int Status;
	DateTime AlarmTime;
	
	UINT ProtocolType;
	UINT Abilities;
	UINT AlarmType;
	/*0:NORMAL;    1:MDALARM;   2:IOALARM;   3:SMART_PEALINE;   4:SMART_AVD;     5:SMART_OSC;
	6:SMART_PEAAREA;  7:SMART_HD;  8:SMART_FD;    9:SMART_CC;*/
	U8 IPCDevTypeFlag; /*IPC�豸����*/	
	U8 MsgValidFlagIPCWeb;//whether the msg is valid for IPC IE , 0:valid , 1:invalid (2016.10.28 add);
	S8 s8Reserve[2];
    UINT AbilitiesEx;
}DevStatRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
    char RecState;               /* ¼��״̬ */
}VideoHideAlarmRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	UINT AreaNum;
	UINT SensorNum; 
	DateTime AlarmTime;
}TelModuleAlarmRpt;


//AIType
#define AIPerimeterAlarm 0 //�ܽ籨��
#define AITripwireAlarm 1 //���߱���

typedef struct
{
	UINT Channel;
	UINT Status;
	UINT AIType;
	DateTime AlarmTime;
}AIAlarmRpt;

/*ͨ����������ʵʱ�������ܷ�����������*/
#define MAX_AI_POS_COUNT  16
typedef struct  
{
	/*ͨ����*/
	BYTE Channel;
	/*�����*/
	BYTE RuleNo;
	/*ʹ�ܿ���*/
	BYTE RuleEnable;
	/*�������ͣ�0-���ߣ�1-�ܽ�*/
	BYTE RuleType;
	/*��������*/
	BYTE Direction;
	/*����λ*/
	BYTE reservel[3];
	/*���߻��ܽ������ֵ�����߽�ʹ��ǰ�ĸ���Ԫ��ż���±�Ϊx���꣬�����±�Ϊy����*/
	unsigned short aiPoints[MAX_AI_POS_COUNT]; 
} AIDataRpt;

//MsgRecordStatusReport
//¼��澯���Ͷ���
#define RECORDSTATUSTYPE_NORMAL      0 
#define RECORDSTATUSTYPE_MANUAL      1 
#define RECORDSTATUSTYPE_MOTION      2 
#define RECORDSTATUSTYPE_IO          3 
#define RECORDSTATUSTYPE_MOTION_IO   4  //�ƶ�����IO�澯
#define RECORDSTATUSTYPE_MOTION_END  5  //�ƶ����ֹͣ  
#define RECORDSTATUSTYPE_IO_END      6  //IOֹͣ 
#define RECORDSTATUSTYPE_PEA         7 
#define RECORDSTATUSTYPE_OSC         8 
#define RECORDSTATUSTYPE_PEA_END     9 
#define RECORDSTATUSTYPE_OSC_END     10 
#define RECORDSTATUSTYPE_PEAAREA     11 // PEA-Area 2015.11.26
#define RECORDSTATUSTYPE_PEAAREA_END 12 // PEA-Area 2015.11.26

#define RECORDSTATUSTYPE_SMART       13 // �������ܸ澯��ʶͳһ��һ�� 2016.05.12
#define RECORDSTATUSTYPE_SMART_END   14 // �������ܸ澯��ʶͳһ��һ�� 2016.05.12

#define RECORDSTATUSTYPE_PIR         15  // PIR 2017.08.07
#define RECORDSTATUSTYPE_PIR_END     16  // PIR 2017.08.07

typedef struct
{
	UINT Type;  //����������
	DateTime AlarmTime;//����ʱ��
	
	UINT ChannelNum;     //��Ӧ�澯ͨ���� ���Ϊ0xffffffff��Ϊ����ͨ��
	BYTE RecordStatus;   //¼��״̬ �� 1 ��ʼ¼�� 0 ֹͣ¼��
	U8  bBoxEnable : 1; //����ʹ�� 20170928
	U8  bBoxDisplay : 1;//������ʾ 20170928
	U8  Reserve : 6;
	BYTE reservel[2];
    UINT AllChanRecState;    //����ͨ����¼��״̬	
	UINT AlarmType;
	/*0:NORMAL;    1:MDALARM;   2:IOALARM;   3:SMART_PEALINE;   4:SMART_AVD;     5:SMART_OSC;
	6:SMART_PEAAREA;  7:SMART_HD;  8:SMART_FD;    9:SMART_CC;*/
	BYTE  reservel2[4];    
}RecordStatusRpt;

typedef struct
{
	int  SensorNodeId;
	char SensorCmd;
	char OperationType;/*1--modfiy, 2--update,3--add,4--delete*/
	BYTE reserver[2];
	char SensorName[24];
	DateTime AlarmTime;	//����ʱ��
}SensorStatusRpt;

typedef enum{
	RSNET_HDDSTATUS_NULL		= 0,
	RSNET_HDDSTATUS_OK			= 1,
	RSNET_HDDSTATUS_UNFORMAT	= 2,
	RSNET_HDDSTATUS_FERROR		= 3,
	RSNET_HDDSTATUS_FULL		= 4,
	RSNET_HDDSTATUS_BAD
}RS_HDDSTATUS_E;

//MsgHddStatusReport
typedef struct
{
	
	BYTE HddStatus;	//Ӳ��״̬��ȡRS_HDDSTATUS_Eֵ
	BYTE reserve[3];
	char HddSN[32];		//���̳������к�
	DateTime AlarmTime;	//����ʱ��
}HddStatusRpt;


//////////////////////////////////////////////////////////////////////////
//Ϊ�˱����Э���ļ��Ķ����ԣ����Gps��Ϣ�ϸ��ʱ��
//Ҳ����PuInfoHead_t��GpsINfo_t��RSFrame.h�ļ��п������� 
//RSInfo
#define RSPuInfoTag *(unsigned int*)"RSI"
#define RSPuInfoTypeGPS 'G'
#define RSPuInfoTypeRepos 'R'
#define RSPuInfoTypeEnd 'E'

typedef struct __PuInfoHeadRpt_t
{
	unsigned int Tag : 24;
	unsigned int Type : 8;
	unsigned int InfoSize;
	unsigned long long Time; //(microseconds) Time/1000,000 = the number of seconds after January 1, 1970 UTC
}PuInfoHeadRpt_t;

//pu_info_head_t.type = RSPuInfoTypeGPS, pu_info_head_t.info_size = sizeof(gps_info_t)
typedef struct __GpsInfoRpt_t
{
	double Longitude;
	double Latitude;
	float Speed;
	float SensorSpeed;          //�������ٶȣ���Ϊ��ѡģ�飬���ܸ�ֵ��Ч
	float Azimuth;    			//����� ����Ϊ0��˳ʱ�뷽�� 0~360
	int Signal3G;               //3G�ź�
	unsigned int TotalMileage;  //  ���г�
	int Temperature;
	char LatitudeDir;       	// �ϱ����� 'N' or 'S'
	char LongitudeDir;      	// �������� 'E' or 'W'
	char Rectified;             // �Ƿ��Ѿ�����
	char Status;   				//״̬, 'A' Ϊ��Чλ��, 'V'Ϊ����Ч���վ��棬����ǰ������Ұ�Ϸ������Ǹ�������3�š�
	unsigned char IgnitionFlag; //����־λ��1:���0��Ϩ��
	char Reserved[3];
	double LongitudeOffset;
	double LatitudeOffset;
}GpsInfoRpt_t;

//GPS��Ϣ�ϸ�ṹ��
//MsgGpsInfoReport
typedef struct 
{
	PuInfoHeadRpt_t stHeadRpt;
	GpsInfoRpt_t stBodyRpt;
	
	DateTime AlarmTime;
}GpsInfoPacketRpt;


//////////////////////////////////////////////////////////////////////////
//����״̬

//���� MsgType=MsgStatusRequest, MsgSubtype	= MsgDevAllStatusReq; MsgSize=0
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=sizeof(DevAllStatusRpt) ʧ��AckFlag=AckFail

typedef enum {
	RECORD_STATUS_STOP_E = 0,
	RECORD_STATUS_NORMAL_E,
	RECORD_STATUS_MANUAL_E,   
	RECORD_STATUS_MOTION_E,
	RECORD_STATUS_IOALARM_E,
	RECORD_STATUS_MOTION_IO_E,
	RECORD_STATUS_INTELLIGENTALL_E,
	RECORD_STATUS_PIR_E,
	RECORD_STATUS_MOTION_PIR_E,
	RECORD_STATUS_PIR_IO_E,
	RECORD_STATUS_MOTION_PIR_IO_E,
	RECORD_STATUS_IO_INTELLIGENTALL_E,//I S
	RECORD_STATUS_MOTION_INTELLIGENTALLE_E,//M S
	RECORD_STATUS_MOTION_IO_INTELLIGENTALLE_E,//M I S
	RECORD_STATUS_PIR_INTELLIGENTALL_E,//P S
	RECORD_STATUS_MOTION_PIR_INTELLIGENTALL_E,//M P S
	RECORD_STATUS_PIR_IO_INTELLIGENTALL_E,//P I S
	RECORD_STATUS_MOTION_PIR_IO_INTELLIGENTALL_E,//M P I S
    RECORD_STATUS_MAX_E
}RS_RECORD_STATUS_E;

typedef enum
{
	IPCBIT0_E = 0,//wether display PID intelligent function, 1 : show that ;
	IPCBIT1_E,    //wether display LCD intelligent function, 1 : show that ;
	IPCBIT2_E,    //wether display SOD intelligent function, 1 : show that ;
	IPCBIT3_E,    //wether display PD intelligent function, 1 : show that ;
	IPCBIT4_E,    //wether display FD intelligent function, 1 : show that ;
	IPCBIT5_E,    //wether display CC intelligent function, 1 : show that ;
	IPCBIT6_E,	  // smart motion
	IPCBIT7_E,	  // deep learning pd
	IPCBIT8_E,	  // deep learning fd
	IPCBIT9_E,

}PageIntelligent_E;
typedef struct
{
	DateTime AlarmTime;
	
	UINT RecordEnable;	//¼��ʹ�ܣ���λ��ʾ, ��λΪͨ��0
	UINT RecordStatus;	//¼��״̬����λ��ʾ, ��λΪͨ��0

	UINT MotionEnable;	//�ƶ�ʹ�ܣ���λ��ʾ, ��λΪͨ��0
	UINT MotionStatus;	//�ƶ����״̬����λ��ʾ, ��λΪͨ��0
	
	UINT IOEnable;		//IO�澯ʹ�ܣ���λ��ʾ, ��λΪͨ��0
	UINT IOStatus;		//IO�澯״̬����λ��ʾ, ��λΪͨ��0
	
	UINT VLossStatus;	//��Ƶ��ʧ״̬����λ��ʾ, ��λΪͨ��0
	
	BYTE HddStatus[8];	//¼��״̬��ȡRS_HDDSTATUS_Eֵ
	BYTE HddSN[8][32];	//���̳������к�
	
	//32��ͨ���Ĳ�ͬ��¼��״̬�ı�ʶ, ȡ�� RS_RECORD_STATUS_E ��ֵ
	BYTE RecordAllStatus[32]; 
    BYTE FtpNewVersFlag;    //�Ƿ����µ������ļ���ʶ��:1 ��;0 û��, 2: ���
                            //5: emergency(lorex ר��),IE��������ʾ
	BYTE reserve2[2];
	BYTE zeroChSwitch;//1:��ͨ������,0:�ر�
    UINT AudioStatus;   //��Ƶ״̬,��λ��ʾ,��λΪͨ��0.(ALTE�ͻ�)
    U32  PageIntelligent; 	 //ipc intelligent analysis capability sets (see PageIntelligent_E) add 2016.10.27
	UINT IntelligentChnStatus;	//ui5.0, ��ʾ�ܵ�����¼��״̬
	UINT IntelligentChnStatusExt[6];//ui5.0���ﱣ��192·���ܹ�224·��Ӧ�ù�����
	UINT IntelligentStatus;/*only for ipc used , bit value*/
	/*0:NORMAL;1:MDALARM;2:IOALARM;3:SMART_PEALINE;4:SMART_AVD;5:SMART_OSC;
	  6:SMART_PEAAREA;7:SMART_HD;8:SMART_FD;9:SMART_CC;*/
	UINT CameraCoverSwitch;
	UINT CameraCoverState;
	UINT MotionStatusExt[8];  //�ƶ����״̬
	UINT IOStatusExt[8];      //IO�澯״̬
	BYTE RecordAllStatusExt[8][32];
	UINT PIRStatusExt[8];//PIR״̬����λ��ʾ, ��λΪͨ��0 (2016.11.01 add for hydvr)
	UINT SmokeStatusExt[8];//Smoke״̬����λ��ʾ, ��λΪͨ��0  (2016.11.01 add for hydvr)
	BYTE PageIntelligentChn[128];//ÿ��ͨ�������ܷ�����������λ��ʾ(see PageIntelligent_E,2016.11.23 add for nvr)
	BYTE  InputNum[256];                 /*ipc io��������·��*/
	BYTE  OutputNum[256];                /*ipc io�������·��*/
	UINT PirEnable;		//����ʹ�ܣ���λ��ʾ, ��λΪͨ��0
	UINT PirStatus;     //�������״̬����λ��ʾ, ��λΪͨ��0
	BYTE PowerStateChange[256];
	BYTE PowerChargeState[256];
	UINT AudioStatusExt[8];      //��Ƶ����״̬
	BYTE PlaybackState;   //����Ƿ����ڻط�

	BYTE HddStatus_ex[32];	//¼��״̬��ȡRS_HDDSTATUS_Eֵ
	BYTE PageIntelligentChnExt[128];//ÿ��ͨ�������ܷ�������������λ��PageIntelligentChn��ʼ��
	BYTE res[95];
}DevAllStatusRpt;

typedef struct
{
	BYTE code_mode;
	BYTE curShowMode;
	BYTE curStreamNum;
	BYTE unused[13];
}FishEyeIpcStatusRpt;

/* �豸���һ���¼���¼ (ALTE�ͻ�ר��) */
typedef struct
{    
    DateTime LastTime; //¼��ʱ��
    BYTE ChannelNo;    //¼��ͨ��
    BYTE RecType;      //¼������
    BYTE reserved[22];
}DevLastRecordRpt;

/* lorex http�����������Ҫ���ݵ�Զ�˵Ĳ��� 2014-10-13*/
typedef struct
{
    BYTE OldVersion[8];     //�ɰ汾��
    BYTE NewVersion[8];     //�°汾��
    BYTE model[16];         //�豸�ͺ�
    BYTE message[256];      //��ʾ��
    BYTE reserved[32];
}HttpUpgsRemoteParam_S;

//���� MsgType=MsgStatusRequest, MsgSubtype	= MsgRemoteCHStatusReq; MsgSize=0
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=MAX_CHN_NUM * sizeof(RemoteChnStatusRpt) ʧ��AckFlag=AckFail

//MsgRemoteCHStatusReport
//MsgRemoteCHStatusReq
typedef struct
{
	unsigned long long DevType;  /* �豸���� */
	char CurChnName[20];         /* �豸���� */

	char CurChnState;            /* ��ǰͨ���豸״̬ */
    char RecState;               /* ¼��״̬ */
    char CurRecType;             /* ��ǰ¼������ */
    char MDState;                /* Motion����״̬ */

    char IOState;                /* IO����״̬ */
    char VLossState;             /* ��Ƶ��ʧ״̬ */
	char HddState;               /* Ӳ����״̬ */
    char MDSchedule;             /* �ƶ������ƻ�*/

    char AlarmSchedule;          /* �����ƻ�*/
	
    unsigned char ChannelNum;		/*��ǰ�豸ӵ�е�ͨ����*/
    BYTE  IPCDevTypeFlag;        /*IPC���ͱ�־,���ڼ�����3516D,��ӦIPC_Dev_Type_e*/
    char  NewDevAbilityModeFlag;      /*�˱�־��������˽��IPC�����޸�Ϊ��ȡ0����λ*/
	
    UINT ProtocolType;/*��ǰ��Э�����ͣ���ӦPROTO_TYPE_E*/
	UINT Abilities;   /*ÿһλ����һ��������0��֧�֣�1֧�֣���ӦABILITY_TYPE_E*/
	char chnName_EX[128];
	char chnMode;//0:˯��(�����Զ�����)  1:����(�����Զ�����)
	char res[7];
	U32 AbilitiesEx;             /*��չλ��ÿһλ����һ��������0��֧�֣�1֧�֣���ӦNet_ABILITYEX_TYPE_E*/
	char resver[116];
}DevChnInfo;
//C_ASSERT(sizeof(DevChnInfo) == 56);

/* IPC�豸����,���ڼ���RS 3516D IPC���� */
typedef enum
{
    IPC_Reserve_e = 0,    
    IPC_RS_H264_e = 1,
    IPC_RS_H265_e,
    IPC_Onvif_H264_e,
    IPC_Onvif_H265_e,
	IPC_ENCODE_H265_e,/*In view of the third party manufacturer, whether to support h264 / h265 coding*/
	IPC_RS_H264_plus_e,//֧�ְ���H264��H264+
	IPC_RS_H265_plus_e,//֧�ְ���H265��H265+
	IPC_RS_H264_H265_plus_e,//֧�ְ���H264��H265��H264+��H265+
	IPC_RS_H264_AVBR_e,//֧�ְ���H264����H264+��Ŀǰģ��ͨ��ʹ��
}IPC_Dev_Type_e;

//MsgRemoteCHStatusReport
//MsgRemoteCHStatusReq
typedef struct
{
	int StructSize;
	int channel;
	DevChnInfo ChnInfo;
}RemoteChnStatusRpt;

typedef struct 
{
	UINT PreviewChannel[8];  /*Ԥ��ͨ��*/
	unsigned char UserPreview;     /*Ԥ��Ȩ��*/
	unsigned char Reserv[7];     
}RsSamsungPreview;

typedef struct
{
	RsSamsungPreview alluser[7];			//user1��user2��user3��user4��user5��user6��user7������admin
	unsigned  int PreviewCovert[8];			/*Ԥ������*/
}RsNetSamsungPCAlarmRpt;

// MsgFtpUpgradeAlarm �澯�ظ�
#define FTPUPGRADE_SUCCESS    0
#define FTPUPGRADE_UPGRADEING 1
#define FTPUPGRADE_PRE_REBOOT 2 
#define FTPUPGRADE_ERROR      3 

typedef struct {
	BYTE UpgradeProcess;  // ��ɽ��� 100 Ϊ�������	
	BYTE UpgradeStatus;    // ��ǰ����״̬
	BYTE reserved[2];	
}FtpUpgradeRpt;
typedef struct {
	BYTE UpgradeProcess;  // ��ɽ��� 100 Ϊ�������	
	BYTE UpgradeStatus;    // ��ǰ����״̬
	BYTE reserved[2];	
}UpgradeRpt;//new name



//////////////////////////////////////////////////////////////////////////
//�澯����
//���� MsgType=MsgAlarmSubscribe, MsgSubType=MsgAlarmDesired, MsgAlarmRefused
//��Ӧ �ɹ�AckFlag=AckSuccess ʧ��AckFlag=AckFail


//////////////////////////////////////////////////////////////////////////
//Զ������

//���� MsgType=MsgRemoteUpgrade, MsgSize=sizeof(RS_UpgradeReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=RS_UpgradeRsp ʧ��AckFlag=AckUpgrading,AckUpgradeVersionError,AckFail

#define MaxUpgradeFileHead 1024*5

typedef struct
{
	UINT UserKey;
	BYTE FileHead[MaxUpgradeFileHead];
}RS_UpgradeReq;

typedef struct 
{
	unsigned int UpgradeBitmap; //must be int here,can't be long
	unsigned int UpgradeFileSize;
}RSNewMode_UpgradeRsp;

/* Զ������ IPC */
typedef struct
{
    UINT UserKey;      //�û� id
    UINT FileSize;     //�����ļ���С
    UINT ChannelMask;  //ͨ������.��λȡ,1:��Ҫ����;0:����Ҫ
    BYTE reserved[4];
    BYTE FileName[256];//�����ļ���
    UINT ChannelMask_EX[8];  //ͨ������.��λȡ,1:��Ҫ����;0:����Ҫ
}RS_UpgsIpcReq;

typedef struct
{
    UINT StructSize;
    UINT UserKey;
    UINT ChannelMask_EX[8];
    BYTE FileName[256];
    UINT FileSize;
    BYTE reserve[28];
}RS_UpgradeReq2;

typedef enum
{
	UpgradeReq2_Success = 0,
	UpgradeReq2_Faile,
	UpgradeReq2_FileNameErr,
}RS_UpgradeReq2_E;

#define MaxUpgradeModules  32

typedef struct
{
	upgradefileheaderentry_t NeedUpgrade[MaxUpgradeModules];
}RS_UpgradeRsp;

//���ݴ��� 
//MsgType=MsgRemoteUpgrade, MsgSubType=MsgRemoteUpgradeData,MsgSize=MaxUpgradeFileHead
#define MaxUpgradeDataSize	4096 //һ��ģ�������ܻ���С��MaxUpgradeDataSize������

//һ��ģ�鴫�����
//���� MsgType=MsgRemoteUpgrade, MsgSubType=MsgRemoteUpgradePartEnd
//����Ҫ��Ӧ

//����
//���� MsgType=MsgRemoteUpgrade,MsgSubType=MsgRemoteUpgradeEnd, MsgSize=sizeof(RemoteUpgradeEndCheck)
//��Ӧ �ɹ�AckFlag=AckSuccess, ʧ��AckFlag=AckFail ,MsgSize=sizeof(RemoteUpgradeEndWriteFlash)

typedef struct
{
	ULONG Crc;
}RemoteUpgradeEndCheck;

typedef struct
{
    BYTE WriteFlashFlag; //�Ƿ�����дflash������ʾ  1: ��  0: ��
    BYTE reserved[3];
}RemoteUpgradeEndWriteFlash;

//��Ӧ MsgType=MsgRemoteUpgrade,MsgSubType=MsgRemoteUpgradeWriteFlashInProgress, MsgSize=sizeof(WriteFlashProgress)  (0 < progress <= 100)
//��Ӧ MsgType=MsgRemoteUpgrade,MsgSubType=MsgRemoteUpgradeWriteFlashEnd ��ʾ�������
typedef struct 
{
    unsigned char Progress;//��ʾ����
    char reserved[3];
}WriteFlashProgress;

//Email����
typedef struct
{
	WORD Ssl;
	WORD Port;
	BYTE Server[MaxNameLen];
	BYTE Sender[MaxNameLen];  
	BYTE Receiver[MaxNameLen];
	BYTE Password[MaxNameLen];
    BYTE TestType;            //0: ��ͨ����, 1: Kguard ���ʼ�����
	BYTE StopTest;
	BYTE Reserved[14];
	BYTE RecvEmail[3][MaxNameLen];
	BYTE username[MaxNameLen];
} EmailTestReq;

//��Email����
typedef struct
{
	WORD Ssl;
	WORD Port;
	BYTE Server[128];
	BYTE Sender[128];  
	BYTE Receiver[128];
	BYTE Password[128];
    BYTE TestType;            //0: ��ͨ����, 1: Kguard ���ʼ�����
	BYTE StopTest;
	BYTE Reserved[14];
	BYTE RecvEmail[3][128];
	BYTE username[128];
} NewEmailTestReq;


//DDNS����
typedef struct
{
	BYTE Serveraddr;
	BYTE Hostname[MaxNameLen];
	BYTE Username[MaxNameLen];
	BYTE Password[MaxNameLen];
    BYTE s8TestType;
	BYTE s8CommaxUseLoginFlag;
	BYTE s8UseDDNS;
	BYTE s8IpType;//LUXVISION�ӵ�DDNSѡ��IPģʽ��IPV4/IPV6��
    BYTE Reserved[11];
	BYTE s8UserUrl[128];
} DDNSTestReq;

/* ftpԶ���������� */
typedef struct
{
    UINT UserKey;
    BYTE reserv[60];
}RS_FtpUpgradeStatusReq;

/* ftpԶ��������Ӧ��� */
typedef struct
{
    UINT structSize;
    int status;
    BYTE resver[256];
}FtpUpgradeStatus;

/* Զ������������� */
typedef struct
{
    BYTE ReqType;   /*����������,1:�ƴ洢.2:�̼�����(��չ)*/
    BYTE ReqSubType;/*����������,1:�ƴ洢�������.2:�ƴ洢����*/
    WORD ReqMsgSize;/*����Я�������ݴ�С*/
    BYTE reserved[28];
}RemoteCheckReq;

/* Զ�������Ӧ��� */
typedef struct
{
    BYTE MainType;
    BYTE SubType;
    int  RetValue;
    BYTE reserved[502];
}RemoteCheckRsp;

typedef struct
{
	int  RetVal;
	BYTE RetMsg[500];
} TestRsp;

//Ӳ�̸�ʽ��
#define HDDFORMAT_SUCCESS            0
#define HDDFORMAT_FORMATTING         1 
#define HDDFORMAT_FAIL               2 
#define CANNOT_HDDFORMAT_RECDOWNLOAD 3
typedef struct
{
	UINT HddBitmap;
	UINT ChannelBitmap;	//ֻ��ʽ����ͨ������
		
	BYTE Reserved[12];
} HddFormatReq;

typedef struct 
{
	BYTE HddNO;     // ��ʽ���̺� 
	BYTE HddFormatProcess; //  ��ʽ������  10���ȡһ�θ�ʽ���ȣ�״̬
	BYTE HddFormatStatue;  // ��ʽ��״̬ 0-��ʽ���ɹ� 1���ڸ�ʽ�� 2 ��ʽ��ʧ��

	 BYTE Reserved[13];
}HddFormatRsp;
//////////////////////////////////////////////////////////////////////////
//ʱ��ͬ��
#define MaxTimeZoneSize  10
typedef struct 
{   
    DateTime Time;
    char     TimeZone[MaxTimeZoneSize];
    char     Reserved[42];
}TimeSyncReq;

//////////////////////////////////////////////////////////////////////////
//Զ��ץͼ
typedef struct 
{
	/*ע�⣺��ͼ��ѹ���ֱ���ΪVGAʱ��֧��0=CIF, 1=QCIF, 2=D1ץͼ��
	���ֱ���Ϊ3=UXGA(1600x1200), 4=SVGA(800x600), 5=HD720p(1280x720),6=VGA,7=XVGA, 8=HD900p
	��֧�ֵ�ǰ�ֱ��ʵ�ץͼ*/
	UINT    StructSize;
	WORD	wPicSize;				/* 0=CIF, 1=QCIF, 2=D1 3=UXGA(1600x1200), 4=SVGA(800x600), 5=HD720p(1280x720),6=VGA*/
	WORD	wPicQuality;			/* ͼƬ����ϵ�� 0-��� 1-�Ϻ� 2-һ�� */
} NET_DVR_JPEGPARA, *LPNET_DVR_JPEGPARA;

typedef struct 
{
	UINT StructSize; //sizeof(RemoteCaptureReq)
	UINT UserKey;  //User key
	UINT Channel;  //Channel No.
	NET_DVR_JPEGPARA jpgPara;//Picture quality parameters
} RemoteCaptureReq;

typedef struct
{
	UINT picSize;
	BYTE Reserved[16];
} RemoteCaptureRsp;

///////////////////////////////////////////////////////////////////////////
//Snapt Report
//Request
typedef struct 
{
	UINT UserKey;
	WORD reserved1;
	WORD reserved2;
} SnaptReportReq;

typedef struct 
{
	DateTime snaptTime; 
	UINT     picSize;
}SnaptCommInfo;
//Motion Report
typedef struct
{
	SnaptCommInfo cmInfo;
	WORD          ch; //0,1,2
	WORD          reserved;
} SnaptMotionReport;

//////////////////////////////////////////////////////////////////////////
//����Զ���豸����̬
//NVR

//���� MsgType=MsgDevNetCfg, MsgSubType=MsgNoSubType, MsgSize=sizeof(NetMDevInfoReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=sizeof(NetMDevInfoRsp) ʧ��AckFlag=AckFail, MsgSize=sizeof(NetMDevInfoRsp);
#define MAX_UNAME_LEN 10
#define MAX_PWD_LEN   14

typedef struct _NetMDevInfoReq_ //����
{
   BYTE msgid[16];  //message id
   BYTE user[MAX_UNAME_LEN]; //user name (for device's authority)
   BYTE pwd[MAX_PWD_LEN];    //password  (for device's authority)
   BYTE cip[4];     //current device ip
   
   BYTE ip[4];     //the device ip what the client wants to change into
   BYTE mask[4];   //the device net mask
   BYTE gw[4];      //the device default gateway
   BYTE dns1[4];    //DNS1
   BYTE dns2[4];    //DNS2
   WORD mport;      //media port   
   WORD wport;      //web port
   BYTE wMode;      //net mode 2:static
   BYTE wNewFlag;   //1:new, 0:old
   BYTE SonixSetMac;//1:setmac
   BYTE reserved;
}NetMDevInfoReq;

// New NetMDevInfoReq, Ϊ�˼��� �ɰ汾
typedef struct _NewNetMDevInfoReq_ //����
{
    union
	{
		NetMDevInfoReq DevInfoReq;//�ɰ汾�ṹ��  
		BYTE IpcName[64];
	};
	U64  devTypeULL;            
	BYTE macAddr[36];   //�豸MAC��ַ      
}NewNetMDevInfoReq;

struct NetMDevInfoRsp //�豸�ظ�
{
	BYTE msgid[16];  //���󷽸���msgid,�豸ԭֵ����
};

typedef struct _RsNetSearchReq_t //����
{
    BYTE msgid[16];  //message id
    BYTE user[64]; //user name (for device's authority)
    BYTE pwd[64];    //password  (for device's authority)
    BYTE cip[4];     //current device ip

    BYTE ip[4];     //the device ip what the client wants to change into
    BYTE mask[4];   //the device net mask
    BYTE gw[4];      //the device default gateway
    BYTE dns1[4];    //DNS1
    BYTE dns2[4];    //DNS2
    BYTE macAddr[40];   //�豸MAC��ַ   
    U64  devTypeULL;
    S32  mport;      //media port   
    S32  wport;      //web port
    BYTE wMode;      //net mode 2:static
    BYTE wNewFlag;   //1:new, 0:old
    BYTE SonixSetMac;//1:setmac
    BYTE CMSUsePoint2Point; //0:broadcast 1:udp point to point 
    BYTE reserve1[4];
    BYTE reserved[512];
}RsNetSearchDevReq_t;
//////////////////////////////////////////////////////////////////////////
//��ѯ����Զ���豸״̬
//NVR

//���� MsgType=MsgSearchRemoteDev, MsgSubType=MsgNoSubType, MsgSize=sizeof(SearchRemDevReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=n*sizeof(SearchRemDevRe) ʧ��AckFlag=AckFail, MsgSize=0;

typedef struct
{
	UINT UserKey;
}SearchRemDevReq;

typedef struct
{
    UINT StructSize;		//sizeof(SearchRemDevRe)
    BYTE IPAddr[4];			/*IP��ַ*/
    BYTE Netmask[4];
    BYTE GateWay[4];
    BYTE Dns1[4];
    BYTE Dns2[4];

    UINT Port;				/*ý��˿�*/
    UINT WebPort;

    BYTE DevType[8];
    char UserName[36];		/*��½�û���*/
    char UserPW[36];		/*��½�û�����*/
    char DeviceName[36];	/*�豸���ƣ������޸�*/

    BYTE Protocol;		  //0:RS, 1:HiK, 2:DaH, 3:HH, 4:Onvif
    BYTE ChnMax;			/*��ǰip��Ӧ��ǰ���豸����ͨ����*/
    BYTE Version ;
    BYTE switchmode; /*0 �Զ�ģʽ 1 �Զ�ģʽ*/

    BYTE MacAddr[36];
    U8 switchflag; /*1 ���������� 0 ��ʾû��*/
    U8 portnum;    /*�������� ��[0  -MAX_POE_NUM) */
    U8 FrontEndChnnal;
    U8 reserved;
	unsigned long long DevTypeULL;

	//onvifЭ�飬ieԶ�����������Ϣ
	char hardware[36];
	char software[36];
	char devicetype[24];
	char manufacturer[36];
    U8 reserved2[4];
	U8 MulChannel[8];//��ͨ��ʹ��

}SearchRemDevRep;


//////////////////////////////////////////////////////////////////////////
//����Զ���豸�������
//NVR

//���� MsgType=MsgSetRemoteDevNet, MsgSubType=MsgNoSubType, MsgSize=n*sizeof(SetRemDevNetReq)
//��Ӧ �ɹ�AckFlag=AckSuccess, MsgSize=n*sizeof(SetRemDevNetRep) ʧ��AckFlag=AckFail, MsgSize=0;
typedef struct
{
	UINT StructSize;		//sizeof(SetRemDevNetRe)

	UINT UserKey;
	
	BYTE TargetIPAddr[4];			/*Ŀ��IP��ַ*/
	UINT TargetPort;				/*Ŀ��ý��˿�*/    
	
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
    /*DNS1*/
    BYTE Dns1[4];
    /*DNS2*/
    BYTE Dns2[4];
	
	char UserName[36];		/*�޸Ĳ������½�û���*/    
	char UserPW[36];		/*�޸Ĳ������½�û�����*/    
	
	BYTE MacAddr[36];
	unsigned long long DevTypeULL;
	BYTE Version ;
	BYTE reserved[3];
}SetRemDevNetReq;

typedef struct
{
	UINT StructSize;		//sizeof(SetRemDevNetRep)
	UINT ErrCode;			//0��ɹ���������Ϊsdk���ش�����
}SetRemDevNetRep;


//////////////////////////////////////////////////////////////////////////
//��Ƶ����
//���� MsgType=MsgReqVideoActivation;MsgSize=sizeof(VideoActivationReq);������Ϣ����
//��Ӧ �ɹ�AckFlag=AckSuccess,MsgSize= 0  ʧ�� AckFlag=AckFail;
typedef struct
{
	UINT StructSize;
	UINT ChannelBitmap[8]; 
}VideoActivationReq;

// ErrCode 
#define E_SUCCESS    0        /** < succeed > **/
#define E_FAILED     -1       /** < failed  > **/
#define E_CONTENT    -101     /** < content failed > **/
#define E_CONNECT    -102     /** < connect failed > **/
#define E_SEND       -103     /** < send faile > **/
#define E_RECV       -104     /** < recv faile > **/
typedef struct 
{
	char InfoFlag;  //�ж�����Ӳ����֤ת��·�� :0 �ͻ�������·�� ,1 EmaliTest·�ߣ�
	char ErrCode;   //  
	char reserve[2];
	char RetMsgInfo[500];
}ActivateCloudRsp;

//FtpWriteFile����
typedef struct
{
	BYTE FtpAddr[MaxNameLen];
	UINT FtpPort;
	BYTE Username[MaxNameLen];
	BYTE Password[MaxNameLen];
	BYTE CloudSGFtpTestFlag;
	BYTE Reserved[15];
} FtpWriteFileTestReq;

typedef struct
{
	char ddnsid[MaxNameLen];
	int ErrCode;
}GetDDNSIDRsp;

typedef struct
{
    UINT StructSize; //sizeof(RebootIpcReq)
    UINT ChannelMask;//ͨ������
	UINT UserKey;    //User key
    BYTE reserved[4];
    UINT ChannelMask_EX[8];//ͨ������
}RebootIpcReq;
typedef struct
{    
    BYTE caption[128];  //˵��
    BYTE RepaireType;   //��������
    BYTE ErrorType;     //��������
    BYTE reserved[6];
}SG_Repaire_t;

/* ���ƽ̨�ֶ��ϴ� -> ά�� */
typedef struct
{    
    BYTE caption[128];  //˵��
    BYTE EquipMaintain; //�豸ά��
    BYTE MaintainRes;   //ά�޽��
    BYTE reserved[6];
}SG_Maintenance_t;

/* ���ƽ̨�ֶ��ϴ� -> ͼƬ */
typedef struct
{    
    UINT ChannelMask;   //���ϴ�ͼƬ��ͨ������
    BYTE type;          //����
    BYTE reserved[3];
}SG_PicUpload_t;

/* ���ƽ̨Զ�̲��� -> �ֶ�ͼƬ�ϴ� */
typedef struct
{
    UINT StructSize;  //�ýṹ���С
    BYTE mode;        //ά��ģʽ.0:����; 1:ά��; 2:ͼƬ
    BYTE reserved[3];
    union
    {
        SG_Repaire_t Repaire;
        SG_Maintenance_t Maintain;
        SG_PicUpload_t PicUpload;
    };
}SGManualUploadReq;

/* ��ͨ�����±������� */
typedef struct
{
    UINT StructSize; //�ýṹ���С
    BYTE ReqType;    //��������, 0-��ȡ��ͨ��״̬,1-ͨ���ر���
    BYTE PreviewMode;//Ԥ��ģʽ.1--������,0--�໭��
    BYTE EncodeCh;   //���±���ͨ��,�໭��Ϊ200
    BYTE reserved[25];
}ZeroChnStatReq;

/* Զ�̻�ȡ��ͨ��Ԥ��״̬ */
typedef struct
{
    UINT StructSize; //�ýṹ���С
    BYTE SplitMode;  //����ģʽ,������ʱ˫�������±���.1--������,4--�Ļ���,...
    BYTE PreviewMode;//Ԥ��ģʽ.1--������,0--�໭��
    BYTE reserved[2];
    BYTE ChnList[32];//ͨ�����б�
}ZeroChnStatRsp;

/*���/ɾ���豸����*/
typedef struct
{
	UINT devId; //sensor�豸��
	BYTE sensorType;  //sensor�豸����
	S8   Sensorname[24]; //sensor�豸��
	S8 sensorCmd;
	BOOL ruleSwitch;
}SensorDevReq;

typedef struct 
{
	S32 remoteCmd;
}MobileRemoteControlStatusReq;


typedef struct 
{
	S8 connectStatus;
}RFConnectReq;
typedef struct
{
	UINT Channel;
	
	UINT delayTime;

	BYTE status;
	BYTE reservel[7];
}SetIOAlarmReq;

typedef struct 
{
	int   UserKey;
	char  Reserve[4];
}RemoteBackupReq_t;

typedef struct 
{
	char msgHead[16];
    char respInfo[40*1024-16];
	char filename[32];
	int  paramLen;
}RemoteBackupResp_t;

//�µĵ��뵼�������������ļ���С��ԭ����Ϊ�˼��ݱ���
typedef struct 
{
	int structSize;
	int  paramLen;
	char filename[32];
	char respInfo[384*1024];
}RemoteNewParamBackupResp_t;

typedef struct 
{
	DateTime starTime;//��ʼʱ��
	DateTime endTime; //����ʱ��
	BYTE alarmType;//���ܽ������ڰ��ߵȸ澯
	BYTE reportType;//��������
	BYTE censusType;//ͳ������
	BYTE reserve;
	UINT channel;
}SearchSmartCountReq;

typedef struct
{
	BYTE alarmType;//���ܽ������ڰ��ߵȸ澯
	BYTE version;  //0-�ɵĲ�ѯ1-�µĲ�ѯ
	BYTE reserve[2];
	UINT channel;
	int  report[32];
	int  reportExt[32]; 
	BYTE filename[32];//heat mapping name
}SearchSmartCountResp;

typedef struct 
{
    UINT StructSize; 	//�ýṹ���С
    BYTE Password[256];
    BYTE reservel[256];
}RSNet_SoleSavetoDev_t;

typedef struct
{
    int  structsize;
    int  times;
}LoginRep_Time;
typedef struct
{
	UINT StructSize;
	int times;
	DateTime dtm;
	BYTE mac[32];
	BYTE serialNumber[32];
	BYTE res[448];
}RS_loginFailedInfo_t;

typedef struct
{
    UINT StructSize;    //sizeof(RecordDetailRsp)
	DateTime Begin;
	DateTime End;
    UINT Type;          //RecordType
    UINT Size;          //�ļ���С
    int  recordId;
    int  diskEventId;  
    BYTE ReqType;       //0: jpeg 1: png 2:  I frame
    BYTE lockstat;      //0: unlock 1: lock
    BYTE reservel[10];
}NewRecordDetailRsp;

typedef struct
{
    UINT StructSize;
    UINT FrameSize;
    BYTE Type;//0: jpeg 1: png 2:  I frame
    BYTE reserve[55];
    NewRecordDetailRsp rsp;
}ThumbnailRsp;

typedef struct
{
    UINT structSize;
    BYTE reserve[12];
    UINT ch[8];
    DateTime eventTime;
}SnapPicForP2PReq;

typedef struct
{
    UINT structSize;
    UINT width;
    UINT height;
    UINT picSize;
    BYTE ch;
    BYTE Type;//0: jpeg 1: png 2:  I frame
    BYTE reserve[14];
    DateTime eventTime;
}SnapPicForP2PResp;

typedef struct 
{
	char ssid[36];		//SSID
	char mac[32];
	char security[128]; //����
	int  rssi;			//�ź�ǿ��
	char pskValue[36];	//Password
}Routpeat_t;

/*swannר��,���ڲ�ѯ����ʹ�����*/
typedef struct
{
    UINT StructSize;
    BYTE reserve[4];
    ULONGLONG TotalBandWidth;   /*�ܴ���*/
    ULONGLONG UsedBandWidth;    /*��ʹ�ô���*/
}RSNetNew_Streamset_t;

typedef struct
{
	UINT StructSize;
	UINT chn;
	BYTE FloodLightMode; /*�׹�� 0:disable 1:enable*/
	BYTE FloodLightValue;/*ֵ��Χ[1, 100]*/
	BYTE AudioAlarmSwitch;/*���ȱ���0:disable 1:enable*/
	BYTE FlashLight;   /*�����*/
	BYTE LineOutVolume;  /*����������[1,10]*/
	BYTE FlashFrequency; /*�����Ƶ�ʵȼ�*/
	BYTE isDualtalkWorking;/*�Ƿ����ڶԽ�*/
	BYTE reserve[57];
}INTF_PREVIEW_CHANGE_S;

typedef enum
{
	DELETE_OK = 0,
	DELETE_FAILE_1,
	DELETE_FAILE_2,
	DELETE_FAILE_3,
}DeleteStatus_E;

typedef struct  
{
	UINT StructSize;
	DeleteStatus_E DeleteStatus;
	BYTE reserver[64];
	NewRecordDetailRsp recordinfo;
}DeleteRecordsRsp;

typedef enum
{
	IMP_PARAM_CTRL = 0,
	IMP_PARAM_MODE,
	IMP_PARAM_LIST,
	IMP_PARAM_LIVE,
	IMP_PARAM_BUTTON,
}ImpParam_E;

typedef struct
{
	UINT StructSize;
	UINT ChannelMask;
	UINT type;
	BYTE getOrset;//0:get , 1:set
	BYTE resevered[3];
}RS_ImpInfoReq_t;

typedef struct
{
	UINT param_size;	// ��������
	BYTE resevered[4];
	BYTE AlgName[8];	// �㷨���ƣ����硰ssc��
	BYTE algParam[255*1024];
}RS_ImpLive_t;

/* Dev Info */
typedef struct tagAlgList
{
	int alg_num;		//�������㷨����
	char resevered[4];
	char alg_list[8][8];	//�洢�㷨��������
	int alg_status[8];	//��Ӧ���㷨״̬��1-run,0-stop
}ImpAlgList_t;

/* �㷨ģʽ */
typedef struct
{
	UINT isSet;
	UINT type;
	BYTE param[512];
}ImpAlarmMode;

typedef struct
{
	ImpAlarmMode mode[4];
}ImpAlarmMode_t;

/* �㷨���� */
typedef struct
{
	BYTE algName[8];
	BYTE algCtrl;
	BYTE resevered[7];
}ImpControl_t;

/* ����total */
typedef struct
{
	UINT StructSize;
	UINT ChannelMask;
	UINT type;//ImpParam_E
	BYTE getOrset;//0:get , 1:set, 2: get faild,3:set faild
	BYTE resevered[3];
	union
	{
		ImpControl_t ImpCtrl;
		ImpAlarmMode_t ImpMode;
		ImpAlgList_t ImpList;
		RS_ImpLive_t ImpLive;
	};
}RS_ImpInfo_t;

typedef struct  
{
	UINT StructSize;
	UINT channel;
	UINT PictureLen;
	UINT JsonLen;
	DateTime Time;
	BYTE res[128];
}RS_AlarmPicReport;

typedef struct
{
	UINT StructSize;
	UINT valid;
	char TestIP[32];
	char reserve[32];
}RSNet_IsValidIP_t;

typedef struct
{
	UINT StructSize;
    UINT interval;          //ͼƬʱ����
	DateTime startTime;	
	DateTime endTime;
	UINT channel;
	UINT recordType;
    UINT userkey;
	char res[28];
}RSNet_GetPicStreamReq_t;

typedef struct
{
    UINT StructSize;
    UINT channel;
    BYTE reserve[16];
}Channel_Pair;

typedef struct
{
    UINT StructSize;
    int error_code;
    BYTE reserve[16];
}Channel_Pair_Return;

typedef struct
{
	UINT structSize;
	U32 sdvalue;
	char res[64];
}RsNet_GetSDAlarmValueReq_t;

typedef struct
{
    UINT StructSize;
    UINT chn;
    char Name[128];
    char reserve[128];
}INTF_NAME_CHANGE_S;

typedef struct
{
  UINT StructSize;
  int UserKey;
  char res[256];
} RsNet_NewDataLinkReq_t;

typedef enum {
    SRT_AISnapPicture,
    SRT_AIFaceAlarm,
    SRT_AIObjectAlarm,
    SRT_Count
} StreamReportType_E;

#pragma pack()

#endif
