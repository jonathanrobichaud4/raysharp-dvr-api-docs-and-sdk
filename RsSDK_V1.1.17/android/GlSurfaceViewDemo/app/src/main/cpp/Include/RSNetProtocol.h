/********************************************************************
	文件描述：	客户端与设备端网络通讯协议
	created by 黄李明 2011.1.8
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
#define MsgDefaultParam         217     //默认参数设置
#define MsgStatusRequest		890		//请求立即产生状态上报
#define MsgAlarmReport			891
#define MsgAlarmSubscribe		896
#define MsgRemoteUpgrade		5139
#define MsgRemoteUpgsIpc        5140    //通用远程升级IPC
#define MsgRemoteUpgradePowerSystem 5141 //电网升级

#define MsgEmailTest            301
#define MsgDDNSTest             302
#define MsgRemoteReboot         303
#define MsgSyncTimeCtl          304
#define MsgColorCtrl            305
#define MsgRemoteCapture        306
#define MsgGainSnaptReport      307
#define MsgQueryLog             308
#define MsgHddFormat            309
#define MsgSearchRemoteDev		310   //NVR用，搜索远端设备。
#define MsgSetRemoteDevNet		311   //NVR用，设置远端基本网络参数。
#define MsgAddAllDevice         312   // 一键添加功能消息信令
#define MsgFtpUpgrade           320   //Ftp 远程升级
#define MsgActivateCloud        321   // 网络硬盘认证
#define MsgDevicePlayback       322   // 回放互斥
#define MsgFtpWriteFileTest     323   // ftp写文件测试消息
#define MsgQueryLog_IPC         324   //ipc专用
#define MsgIsFormatHdd          325   //格式化硬盘与回放(下载)互斥
#define MsgNoStreamType         326   //no
#define MsgCloudCheck           327   //kguard cloud check
#define MsgSearchLog            328   
#define MsgRebootIPC            329   //远程重启IPC
#define MsgIPCLoadDefault       330   //远端IPC恢复默认设置
#define MsgUpgradeFireware      331   //远程升级尚云固件(kguard DVR)
#define MsgRemoteOneKeyAddIPC   333 //nvr one key add ipc
#define MsgSGManualUpload       334   //深广平台手动图片上传
#define MsgRsPushParamHandle    335   //rspush handle appinfo
#define MsgZeroChnStatus        336   //获取0通道状态(ZIP客户)
#define MsgRemoteCheck          337   //远程请求检测(升级)云存储
#define MsgIsModifyHdd          360   //修改盘组与与回放(下载)互斥
#define MsgHttpUpgrade          361
#define MsgValidIPTest          365
#define MsgClientAutoLogout     366
#define MsgDeleteLog            367
#define MsgRecordsLock          369

#define MsgAddSersorDev        338  //远端添加sensor设备
#define MsgDeleteSersorDev        339  //远端删除sensor设备
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


//修改关键参数命令
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

//新的导入导出，2016.12.22add
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
#define MsgPTZZoomIn		11 //焦距变大
#define MsgPTZZoomOut		12 //焦距变小
#define MsgPTZFocusNear		13 //焦点前调
#define MsgPTZFocusFar		14 //焦点后调
#define MsgPTZIRISOpen		15 //光圈扩大
#define MsgPTZIRISClose		16 //光圈缩小
#define MsgPTZAutoScan		21
#define MsgPTZCruise		51
#define MsgPTZGetPresetNum  52
#define MsgPTZSetPPCruise			53  //设置轨迹巡航
#define MsgPTZCallPPCruise			54  //调用轨迹巡航
#define MsgPTZStartPattermCruise		55  //花样扫描开始
#define MsgPTZEndPattermCruise		56          //花样扫描结束
#define MsgPTZCallPattermCruise		57          //调用花样扫描


#define MsgPTZGuard         90
#define MsgPTZSetPreset		91
#define MsgPTZClearPreset	92
#define MsgPTZCallPreset	93
#define MsgPTZSensorPresetInfoGet 94
#define MsgPTZSensorPresetInfoSet 95
#define MsgPTZLockFocus 96
#define MsgPTZLineScanA 98  //线性扫描开始点
#define MsgPTZLineScanB 99   //线性扫描结束点
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
#define MsgFtpUpgradeAlarm              203   // Ftp 升级告警
#define MsgUpgradeAlarm					203   // Ftp 升级告警(new name)
#define MsgOscAlarm		                204
#define MsgIntelPeaAlarm                205
#define MsgOscRuleAlarm                 206
#define MsgVideoHideAlarm               207
#define MsgBitrateInfo                  208
#define MsgAllChnsAlarm                 209 //所有通道报警

//MsgAlarmSubscribe sub type
#define MsgTelModuleAlarm               210
#define MsgRemoteCHStatusReport         211
#define MsgRecordStatusReport			212
#define MsgHddStatusReport				213
#define MsgGpsInfoReport                214
#define MsgIntelIpcPeaAlarm             215 // 绊线 2015.11.30
#define MsgIpcOSCAlarm                  216
#define MsgIntelIpcPeaAreaAlarm         218 // 周界 2015.11.30
#define MsgSensorStatusReport           247  //sensor状态

#define MsgAlarmIntHD                   248  // 人体 2016.03.09
#define MsgAlarmIntFD                   249  // 人脸 2016.03.09
#define MsgAlarmIntPCC                  250  // 过线统计 2016.03.09
#define MsgAlarmIntManage		        251  // 智能管理 2016.03.09
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
#define MsgAudioReport                  274 //音频开关状态 2018.4.24
#define MsgClientAutoLogoutTimeChangeReport 		275
#define MsgGetPic                       277
#define MsgSamPCAlarmReport             279
#define MsgNewDataLinkOpt               282
#define MsgNewDataLinkJson              283
#define MsgPWDChange                    285
/******************************
* 参数配置.SubType   -----start
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
#define MsgParamDevAllStatusSet         554   // URMET 客户远程控制通道信息
#define MsgParamLorexP2pParam           555   // Lorex客户参数信令
#define MsgParamFtpAutoUpgrade          556   // 
#define MsgParamManualRecord            557   // 手动录像

#define MsgParamSystemIDCtrl             558  // 设备id号
#define MsgParamIPCFrameInfo             559  // nvr获取ipc帧信息
#define MsgParamNewCloudStorage          560
#define MsgParamUpLoadPhoto              561
#define MsgParamUpLoadVideo              562
#define MsgParamCloudStorageInfo         563
#define MsgParamCloudStorageEmail        564
#define MsgParamCloudStorageFTP          565
#define MsgParamPerimeterLine            566
#define MsgParamVideoDiagnostics         567
#define MsgParamGoodsLostLegacy          568
#define MsgParamKGWireless               569/* 新增KG  Wireless 参数信令*/

/*******************************************************************
参数配置,subType,由于编号不够用，所以从703开始编号，根据功能摆放，
而不是编号.添加新的定义请务必注意且修改、注明相关情况 ----2016.03.10
********************************************************************/

#define MsgParamPerimeter                703 // 周界 2015.11.12
#define MsgParamAreaStream               704 // ipc 裁切码流
#define MsgParamIntHD				 	 705 //人体 2016.03.09
#define MsgParamIntFD				     706 //人脸 2016.03.09
#define MsgParamIntPCC				     707 //过线统计 2016.03.09
#define MsgParamIntManage                708 //智能管理 2016.03.09

/*设置电网私有参数对应结构体Eplateform_t*/
#define MsgParamElectricityGrid			 709 //2016.05.25
#define MsgSearchSmartCount              710 //统计智能过线的个数 2016.05.31
#define MsgParamFishEye                  711  //ipc fisheye
#define MsgParamIPCCamearMode            712

/*设置交换机页面参数,对应结构体 RSNet_SoleSwitch_t*/
#define MsgParamSwitch					 713
#define MsgParamIPCCameaFocusInfo		 714
/*参数配置.SubType   -----end*/ 

/*预览界面参数设置，对应结构体 RSNet_SolePreviewCtrl_t,PARAM_PAGE_PREVIEWCTRL*/
#define MsgParamPreviewCtrl  715
#define MsgParamAlarmOutScheduleset  716

/*透明通道传输协议*/

/*Swann*/
#define MsgParamSwannWifi  717 //设置swann wifi页面
#define MsgParamSwannIpcRepeat  718 //设置swann IpcRepeat
#define MsgParamSwannRouterRepeat  719 //设置swann RouterRepeat

/*APP远程开机向导*/
#define MsgParamWizard  720
#define MsgParamTiming  721//校时指令

/*GB28181 页面参数*/
#define MsgParamGB28181 722

/*PIR 页面参数*/
#define MsgParamPir		723

/*电网平台智能算法参数配置*/
#define MsgParamJDVCAMeterRecongition	724 //电网平台智能读表配置 JD_VAC_TYPE_METER_RECOGNITION
#define MsgParamJDVCAIntrusionDetection	725 //电网平台区域入侵算法参数 JD_VAC_TYPE_INTRUSION_DETECTION
#define MsgParamJDVCARedMantleDetection	726 //电网平台区域红布幔检测参数 JD_VCA_RED_MANTLE_DETECTION


/*车载OSD 叠加*/
#define MsgParamCarInfo 727

#define MsgParamVVPush  728

#define Msg98cUpgrade  729

#define MsgRemoteUpgrade2 730

/*************透明通道传输协议****************/
#define MsgSerialTransport          355

/*参数配置.SubType   -----end*/ 


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
#define MsgParamSoleUploadVideo          584 //视频上传 7day*48halfhour
#define MsgParamIntelliRec               585 //智能录像计划(Qt v2)
#define MsgParamIPCImageSet              587 //IPC图像设置
#define MsgParamRenewFactory             588 //shenzhen renew factory
#define MsgParamCustomProtocol           589 //自定义主子码流协议(nvr)
#define MsgParamSGPlatform               590 //深广平台参数
#define MsgParamIPCROI                   591 
#define MsgParamOD                       592 
#define MsgParamIPCWireless              593 //Lorex无线IPC专用参数
#define MsgParamKguardP2p                594 //Kguard ShangYun P2P (DVR)
#define MsgParamSensorAlarm              595 //Kguard Sensor Alarm (DVR)
#define MsgParamPushInfo                 596 //push info 
#define MsgParamAnalogCam                597 //混合DVR模拟通道信息
#define MsgParamCaptureSet               598 //混合DVR抓图设置
#define MsgParamCapSchedule              599 //混合DVR抓图计划表
#define MsgParamIPV6Info                 600 //ipv6 info 
#define MsgParamZeroChn                  601 //零通道功能
#define MsgParamSensorAlarmSingle        602 //Kguard single Sensor Alarm (DVR)
#define MsgParamSensorCtrl			     603 //sensor control Alarm(混合dvr 目前Kguard使用)


#define MsgParamKeyParamSet              700 //远程烧写关键参数
#define MsgParamChnInfo                  701 //混合DVR通道信息
#define MsgParamRecInfo                  702 //混合DVR录像信息

/*GB28181 页面参数*/
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
注意:703-708已被"参数配置"占用，见#define MsgParamPerimeter，
添加新的定义请务必注意且修改、注明相关情况。 ----2016.03.21
**********************************************************/

//
#define MsgParamOccSet_IPC               1000 
#define MsgParamModifySnmpSet			 1001 
#define MsgParamModifyGb28181			 1002 
#define MsgParamModifyIeeeSet			 1003 
#define MsgParamModifyCameraSet_IPC      1004  
#define MsgParamModifyNetBeakSet         1010  
#define MsgParamSoundRecord              1012
#define MsgParamLightSchedule            1013  /* KG 新增灯呼吸schedule信令*/
#define MsgParamSnapshot                 1014   //KG快照功能
#define MsgParamFishEyeCircle            1015

//升级 sub type
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
#define MsgRemoteCHStatusReq		611  //查询远端连接通道的状态,主要指NVR连接的IPC状态

//Msg PEA , GoodsLost Sub Type
#define MsgPeaAlarmReq              612
#define MsgGoodsLostAlarmReq        613
//只获取设备状态,兼容lorex同时获取状态和检测升级
#define MsgDevStatusOnlyReq         614
#define MsgGetRemoteParam           615 //获取lorex http升级内容
#define MsgLastRecordReq            616 //设备最后一次记录信息.(ALTE客户)


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
	BYTE Version : 2; 	//消息头版本
	BYTE ExtSize : 6; 	//消息头扩展大小，实际扩展大小 = ExtSize * 4
	BYTE Reserved;
	WORD AckFlag; 		//消息回应码
	WORD MsgType; 		//消息类型
	WORD MsgSubType; 	//消息子类型
	UINT MsgSize;  		//消息头后面的数据大小
	UINT Seq;  		    //消息序列号，标识一次消息的唯一性，由请求方创建，回应方原值返回
}MsgHead;			 	//消息头，sizeof(MsgHead) = 16
//串口通信链路，发送串口命令后，网络层回应数据
typedef struct 
{
	int res; //0 failed  1 success 
	int reserve;
}RSSerialRes_t;

//232数据发送请求消息体
typedef struct 
{
	int datatype; //0 play control ,1 user commind ,2 扩展命令
	int datasize; 
	char buf[1];
}RSSerialReqData_t;


//////////////////////////////////////////////////////////////////////////
//搜索设备
//请求 MsgType=MsgSearchDev
//回应 MsgSize=sizeof(SearchDevRsp)

#define SearchDevPort	9333

//SearchDevRsp.NetworkMode
#define NetworkModeDHCP		0
#define NetworkModePPPOE	1
#define NetworkModeManual	2

typedef struct
{
	char IP[MaxIpLen]; //IP
	char HostName[MaxNameLen]; //域名
	char NetMask[MaxIpLen]; //掩码
	char GateWay[MaxIpLen]; //网关
	char DNS1[MaxIpLen]; //dns服务器1
	char DNS2[MaxIpLen]; //dns服务器2

	UINT Port; //客户端连接设备端口
	UINT IEPort; //IE端口

	UINT NetworkMode; //连网方式

	char DevType[MaxNameLen - 8]; //设备类型
	unsigned long long DevTypeULL;
	char DevVer[MaxNameLen]; //设备版本
	UINT DeviceID;  //本机编号
   	char DeviceName[MaxNameLen]; //设备名称，可以修改        
	char MacAddr[MaxNameLen]; //设备MAC地址

	UINT ChannelNum; //通道数
	
	unsigned char Version;//版本
	char cNetInterface;// 0 eth0 1 eth1
	char P2pID[38];

    char manufacture[32];
	unsigned short rtspport;
	char DisplayChannelNum; // 模拟通道数
    char reserved[93];
}SearchDevRsp;


//////////////////////////////////////////////////////////////////////////
//登录
//请求 MsgType=MsgLogin, MsgSize=sizeof(LoginReq)
//回应 成功AckFlag=AckSuccess,MsgSize=sizeof(LoginRsp) 失败AckFlag=AckLoginUserLogined,AckLoginNoUserName,AckLoginPasswordError,AckFail

//VideoFormat
#define RS_PAL  0
#define RS_NTSC 1

typedef struct
{
	char UserName[MaxNameLen];
	char Password[MaxNameLen];
	UINT UserKey; //首次登录为0，断线重连填上次成功登录返回的UserKey，以防独占用户出现用户已登录的错误返回
	UINT AlarmReportDesired : 1;
	UINT ZipLogin: 1;//zip login falg
	UINT Reserved : 22;
	UINT Language : 8; /* 1,中文2.英文 */
}LoginReq;

typedef struct
{
    char UserName[256];
    char Password[256];
    UINT UserKey; //首次登录为0，断线重连填上次成功登录返回的UserKey，以防独占用户出现用户已登录的错误返回
    UINT AlarmReportDesired : 1;
    UINT ZipLogin: 1;//zip login falg
    UINT Reserved : 22;
    UINT Language : 8; /* 1,中文2.英文 */
}LoginCryptoReq;

typedef struct
{
    int  structsize;
    char reserve[4];
    char uuid[24];
    char reserve1[128];
}LoginReponse;

//用户权限各位显示
typedef struct
{
	UINT UserSetRight;/*参数设置0 ,磁盘管理1,远程登入2,系统维护3,日志查看4,(巡航控制5)，轮询控制6, 手动录像7,手动捉图8,音频权限9*/
//	UINT ManualRecordChannel;  //手动录像通道 
	UINT PreviewChannel;     //预览通道
	UINT PlayBackChannel;       //回放通道
	UINT BackupChannel;        //备份通道
	UINT PtzControlChannel;     //云台控制通道
	BYTE UserPreview;        //预览权限
//	BYTE UserManualRecord;   //手动录像权限
	BYTE UserPlayBack;        //录像回放权限
	BYTE UserBackup;          //备份权限
	BYTE UserPtzControl;       //云台控制权限
	
	BYTE MainStream:1;       //流权限，按位取值        
	BYTE SbuStream:1;		//流权限，按位取值        
	BYTE MobileStream:1;	//流权限，按位取值     
	BYTE UserAlarmSensorControl:1;       //alarm sensor control
	BYTE UserRtsp:1;	//RTSP权限，按位取值 
	BYTE Reser:3;
         
	BYTE OnivfRight;		////0:管理员权限，1:操作员权限，2:视频用户    
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
  BIT26_E,   //1:support Audio In/Out，0 not
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
    PBIT11_E,	//1：support alarmLink page  0:no support alarmLink page;
    PBIT12_E,   //1:support  PIR     0: no support
    PBIT13_E,   //1:Supports poe independent settings, 0: no support
    PBIT14_E,   //1：support 3070 old sonix wireless, not live page; 0:not
    PBIT15_E,   //1:support 4K , 0: no support
    PBIT16_E,   //1:support 波斯历 , 0: no support
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
    PBIT30_E,   //1：Support  snmp interface  0: no Support
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

//自动对焦Zoom和Focus最大和最小位置
typedef struct
{
	UINT mixZoomPosition;
	UINT maxZoomPosition;
	UINT mixFocusPosition;
	UINT maxFocusPosition;
	BYTE PTZVersion;//使用PTZ 界面的版本，0:旧界面，1:新界面
	BYTE unused[7];
} AutoFocus_Default_t;
typedef struct 
{
	UINT StructSize; //该结构体大小
	UINT ChannelMask;//通道掩码
    UINT curZoomValue;//zoom当前的位置
    UINT zoomStep;//0：1步  1：5步  2：20步
    UINT curFocusValue;//focus当前位置
    UINT focusStep;//0：1步  1：5步  2：20步
    BYTE autoFocusState;//0:对焦结束，1：进行对焦中
    char ShiftRange;//0:合理范围，1：增减垫片
    BYTE unused[30];//保留
}AUTOFOCUS_CONTROL_S;

typedef struct
{
	unsigned long long DevType; //设备类型
	char DevVer[MaxNameLen]; //设备版本
	char DeviceName[MaxNameLen]; //设备名称，可以修改        
	char MacAddr[MaxNameLen]; //设备MAC地址
	UINT DeviceID;  //本机编号
 
 	UserRightWrap UserRight; //用户权限

	UINT UserKey; //用户密钥
 	WORD TotalFPS_D1; //设备D1模式每秒最大总帧数，例如TotalFPS=100, 可以设置4个CIF 25f/s或2个HD1 25f/s或1个D1 25f/s
 	BYTE ChannelNum; //通道数
 	BYTE VideoFormat; //摄像头制式

 	BYTE AlarmInNum;  //报警输入数
 	BYTE AlarmOutNum; //报警输出数(继电器个数)
	BYTE AIAnalyzeCap; //是否支持智能分析
	BYTE AIAnalyzeChannels; //智能分析的路数

	BYTE SerialNum;	//设备使用串口的数目，没有就填0。(大键盘是采用串口通讯)
	BYTE ISAdmin;   //是否是管理员
	BYTE AudioNum;         //音频通道数
	BYTE ResolutioFrameFix;//帧率分辨率是否固定:0-可调,1-都固定，2-可以扩展为两者的组合

	BYTE PreviewOff;       //预览是否可以关闭，主要针对D9016特殊的情况，0-可以，1-不可以
	BYTE VideoCoverNum;    //单通道支持的最大视频遮挡块数，主要针对D9016特殊的情况
	BYTE SupportSpot;      //是否支持spot接口的相关功能
	BYTE SubStreamMin;     //小码流可以取值范围对应的索引值，各个产品根据实际情况赋值

	BYTE SubStreamMax;     //索引:0     1     2     3     4    5     6     7    8       9       10      11     12
	BYTE PlatformSupport; //0(不支持平台) 1(支持平台)
	
    WORD ChnInfoSize;		//表示登录结构体后所跟的通道信息DevChnInfo结构体的大小
							//后续版本将不再使用通道信息结构体。改为消息命令MsgRemoteCHStatusReq获取通道信息。

	BYTE SubStreamRestrict; // 0(受限制) 1 (不受限制)
	BYTE DualtalkShowTag;  //0(不显示:可能不支持对讲) 1(显示：支持对讲)
	BYTE RouterShowTag;    //是否显示路由参数设置页面
	BYTE LanShowTag;		//是否显示路由Lan口设置页面

	UINT PlatFormShowTag;   //是否显示平台设置参数页面，Value（ Show Plat：*(UINT*)"PLEn" ；Hide Plat：0x00000000 ）
	char ProductName[24];
	UINT PlatFormSwitch;   //当PlatformSupport = 1，PlatFormShowTag = "PLEn"， 则判断此项。平台支持类型, 按位显示，使用 PlatformSwitch_E 定义, 若全为0则为默认的RS_PLATFORM。
	
	BYTE VideoActivateSwitch; // 是否支持 增大用户所选中通道视频码流，减小其他码流功能
	BYTE MotionMode;          //0代表旧的模式，1 代表 44*36 格式模式
    BYTE ResolutionMode;      //0 代表D1模式,1代表D1和960P模式, 2代表纯CIF模式, 3代表纯CIF但是不禁用帧率
                              //4 代表720P， 5代表720P和960
	BYTE HidePhonePage;        //0代表不隐藏，1代表隐藏
	
	BYTE UpgradeType;         //0 代表旧设备升级 1 代表新设备升级
	BYTE ElecLockFlag;         //0 代表未加锁状态 1 代表加锁状态
 	WORD TotalFPS_960;			//设备960模式每秒最大总帧数，例如TotalFPS=100, 可以设置4个CIF 25f/s或2个HD1 25f/s或1个D1 25f/s

	// one byte
	BYTE WifiStatus:1;           //0 代表没有检测到wifi模块, 1 代表有模块存在
	BYTE RtspPageEnable:1;           //是否开启RTSP服务页面开关 0代表关闭, 1 代表开启
	BYTE FtpPageFlag:1;          //Ftp功能标识量，1 有此功能，0为没有
	BYTE c32PasswordFlag:1;     // 使用长密码标识量，1为使用32字节的密码，0为不使用
	BYTE UrmetDevStatusFlag:1;   // ;UEMET客户需求 设备状态信息页面显示标识量	
	BYTE FileSystemFlag:1;       // ;0 海思系统 1 安联系统
	BYTE KguardP2pUidFlag:1;      // 0 不显示Uid, 1显示Uid
	BYTE EmailFlagSwitch:1;     // EmailScheduleFlag 标识位的控制开关是否有效，1：有效，0:无效.
	
	BYTE EmailScheduleFlag:1;     // 是否开启录像计划页面，0 不开启，1开启
	BYTE PtzHiddenFlag:1;	     // 是否隐藏PTZ功能， 0 不隐藏(开启), 1 隐藏(关闭)
                                 // 为同时兼容以前设备版本部分有3g功能，部分没有3g功能	
	BYTE c3GFlagSwitch:1;         // 3GFlag 标识位的控制开关是否有效，1：有效，0:无效.
	BYTE c3GFlag:1;               // 0 不启用3G功能, 1 启用3G功能 
	BYTE RecordTypeFlag:1;	 //回放录像类型标志 
	BYTE SystemIDCtrl:1;     // systemID 	
	BYTE FtpPcSendFlag:1;     // Ftp发送抓拍图片功能标志位 0 关闭  1 开启	
	BYTE CloudStorageFlag:1;  // 云存储开关0 关闭 1 开启 	
	
	BYTE AutoMaintenance:1;   //自动维护页面隐藏，0 打开 1 隐藏
	BYTE CloudSGSerSwitch:4;  //  云存储服务器类型
	BYTE ShieldColorSetFlag:1; 
	BYTE IntelligentAnalysis:1;  // 智能分析页面，0 close 1 open
	BYTE RemoteUpgradeMode:1;   // 0: old Mode, 1: new Mode

	BYTE CloudeSGType:4;      // 0 dropbox and google 1: only dropbox 2: only google（20181024：新云存储，按位取，0支持dropbox，1支持google）
	BYTE CloudeStorageMode:1; // 0:old param struct , 1: new param struct
	BYTE VBRFlag:1;
	BYTE RemoteFtpUpgradeSupport:1;  // 0:not support , 1: support to upgrade
	BYTE MainStreamMutex:1; 

	BYTE NewAapterQTParamFlag:1;  // 适配Qt参数标志位
	BYTE PtzSupported:1;		  // only for nvr set IPC ptz param 
	BYTE PasswordSwitch:2;        //First bits for this function, Second for password switch
	BYTE NvrFlag:2;               //n1104:0,others:1
    BYTE MaintainUserEnabled:1;   //just in compatible with former version
    BYTE MdStreamFlag:1;         //车载流权限开关

	BYTE MaxPOENum;
    BYTE UiType;             //ui 1.0, 2.0, 3.0, 3.1
    BYTE ChipNum;            //设备芯片数
    UINT ProtocolType;       //每一位代表一种协议，0不支持，1支持

    BYTE QueryRHMIFlag:1;    //查询录像、硬盘、移动侦测、IO状态。暂时lorex(flir)
    BYTE compatUpgrade:1;    //兼容lorex客户端检测升级和获取设备状态
    BYTE supportMutiEmail:3; //是否支持多邮件发送.0:1个邮件;1:3个邮件(lorex)
    BYTE showVersionFlag:1;  //是否显示带版本信息的提示语(lorex).0:不显示;1:显示
    BYTE honeyNewChName:1;   //honeywell OSD通道名,支持8个中文(utf-8编码)
    BYTE pppoeFlag:1;        //0 不启用PPPoE功能, 1 启用PPPoE功能
    BYTE maxChFps;           //单通道最大主码流帧率.1:720P 15FPS; 2:1080P 15FPS;默认为0
    WORD maxTotalFPS;        //所有通道的最大帧率总和
    BYTE hybirdDVRFlag:4;    //混合dvr标志
    BYTE FrameAutoFlag:1;    //帧率自动调节开关(目前为非Qt DVR)
    BYTE customProtolFlag:1; //远端是否显示自定义码流协议页面(NVR)
    BYTE sgPlatformFlag:1;   //远端是否显示深广平台页面(NVR)
    BYTE PushEnabled:1;      //是否开启报警推送功能.0: close, 1: open.
    BYTE AnalogChNum;        //混合DVR 接模拟通道的个数
    BYTE BitrateMode;        //码率选项类型, 针对DVR特定系列产品型号
    BYTE ShowSensorAlarm:1;  //远程是否显示传感器报警页面,0: 不显示;1: 显示(DVR)
    BYTE ZeroChFlag:1;       //0通道功能开关(ZIP客户)
    BYTE GetAlarmChns:1;     //新报警上告方式,1:一次获取某事件对应的所有通道报警信息,(默认0)
    BYTE CoaxialFlag:1;      //是否支持同轴功能. 1:support, 0:not support    
    BYTE eSATAEnabled:4;     //设备是否启用ESATA功能.(NVR)

    char p2pId[32];         //P2P Id(OWL手机推送)
    WORD totalFrameRes;     //帧率总资源 (目前为非Qt DVR)
    BYTE DevPlayBackCap;    //0:旧的回放模式，1:快进快退只取I帧模式，2:快进快退跳I帧模式
    BYTE PushType;          //0:tutktype(包括带tutk的中性程序、OWL旧服务器64.91.227.90), 1:rstype,  2: tpns2.0 新服务器专用(host.nightowldvr04.com)
    BYTE DLMode;
    BYTE ZipFlag;           //0:nozip , 1:zip
    BYTE RemoteSearchLogFlag;           //是否支持远程搜索日志1:enable, 0:disable
	BYTE KguardDomeFlag:1; //kg要投机标记，0：no， 1：yes
	BYTE HKDemoFlag:1; //汉威球机标识，0：no， 1：yes
	BYTE AIFlag:1;     //new AI :1 , old AI :0
	BYTE RSDomeFlag:1;//遥头机公版标记，0：no， 1：yes	
	
	BYTE NewEmailTest:1;
	BYTE c32UserNameFlag:1;// 使用长用户名标识量，1为使用32字节的用户名，0为不使用
	BYTE reserv:2;
	UINT PreviewChannel_EX[8];     //预览通道
	UINT PlayBackChannel_EX[8];       //回放通道
	UINT BackupChannel_EX[8];        //备份通道
	UINT PtzControlChannel_Ex[8];     //云台控制通道
	U32  PageControl; // 0)display image 1)IRIS 2)samsung customer 3)intelligent analysis 4)area encode 5) intelligent manage
	FishEyeIpc_Cap_t FishEyeIpcCap;
	WORD CustomerVal;//CustomVal_E
	BYTE PreviewNum; //限制远端主码流预览通道数
	BYTE DefualtStream;//ipc默认IE登录显示码流0:主码流 1: 子码流2: 手机码流
    U32 PageControl2;//PageControl2_E
    AutoFocus_Default_t  AutoFocusDefault;
	BYTE WizardFlag:1;
	BYTE reserv3:7;
	BYTE PirAreaMode;//1为使用六边形PIR区域设置 0为正常模式
	BYTE TalkMode;//0: old device , 1: audio talkback with ipc use half-duplex mode . 2 :full duplex mode, 3 : all mode 
	BYTE HddOverWriteMode; //0: 默认列表 1: URMET 列表(1day/2days/3days/4days/5days/6days/7days/14days/30days/90days)
	U32  ControlBit;//ControlBit_E

	BYTE s8SIAIntVersion[16];
	BYTE s8SIAModelsVersion[16];
	U32  ControlBit2;//ControlBit2_E
	U32  SNSUsrInfoID;
	UINT ClientAutoLogoutTime;
    BYTE MaxCloudVideoUploadNum;  /* 云通道允许上传视频最大个数 */
    BYTE UserId;//0:admin,1:user1,2:user2....
    BYTE reserv4[2];
    UINT PreviewCovert[8];
    UINT PushInfoType; //APP端需要显示的推送类型(PushType_E)
    U32  ControlBitArray[8];//ControlBitArray_E
    UINT SupportEncAbility;	//支持设置的视频编码格式,bit0:H264 bit1:H265 bit3:H264+ bit4:H265+
	char DeviceType[MaxNameLen];
	char SerialNumber[32];
	BYTE reserv5[8*100-224];
}LoginRsp;
//C_ASSERT(sizeof(LoginRsp) == 1232);

typedef enum
{
	CTBIT0_E = 0,//lorex
	CTBIT1_E = 1,//1:support H264+, 265+, 0 :
	CTBIT2_E, /*是否支持SD卡1:支持0:不支持*/
	CTBIT3_E, /*是否支持Google home*/    
	CTBIT4_E, /*network 和 switch 页面合并 1:合并 0：不合并*/
	CTBIT5_E, /*是否支持分两个时间段设置颜色值*/
	CTBIT6_E, /*是否显示output参数页面*/
    CTBIT7_E, /*是否支持修改IPC网络参数*/
	CTBIT8_E, /*是否支持多通道设备IP的添加*/
	CTBIT9_E, /*是否支持HTTPS 0:不支持 1：支持*/
	CTBIT10_E,/*是否支持IR灯开关设置 0:不支持 1：支持*/
	CTBIT11_E,/*是否支持IR时间设置 0:不支持 1：支持*/
	CTBIT12_E,  /* IRCUT MODE 是否取消显示GPIO AUTO 选项 ，0: 不取消显示; 1: 取消显示*/
	CTBIT13_E,/*是否显示I帧间隔,0:显示，1：隐藏*/
	CTBIT14_E,/*支持亚马逊IOT激活页面*/
	CTBIT15_E,/*sound alarm显示标志位：0隐藏，1：显示*/
	CTBIT16_E,/*ftp video显示标志位：0隐藏，1：显示*/
	CTBIT17_E,/*是否支持手动录像类型的搜索*/
	CTBIT18_E,/*是否隐藏 主码流页面,默认是显示,1:hide, 0:show*/
	CTBIT19_E,/*是否隐藏 子码流页面,默认是显示,1:hide, 0:show*/
	CTBIT20_E,/*是否隐藏 手机流页面,默认是显示,1:hide, 0:show*/
	CTBIT21_E,/*抓图拓展显示标志位：0隐藏，1：显示*/
	CTBIT22_E,/*IP Filter显示标志位：0隐藏，1：显示*/
	CTBIT23_E, /* 是否支持模拟通道MJPEG码流 */
	CTBIT24_E,/*FTP加密显示标志位：0隐藏，1：显示*/
	CTBIT25_E,/*是否手机端支持http升级*/
	CTBIT26_E,/*是否支持音频输入异常检测功能，0：隐藏，1：显示*/
	CTBIT27_E,/*是否显示PTZ参数页面：0显示，1隐藏*/
	CTBIT28_E,/* 是否支持客户端smart搜索, 0:不支持 1：支持 */
	CTBIT29_E,/* 是否支持断网录像, 0:不支持 1：支持 */
	CTBIT30_E,/* HDVR默认使用264录像格式，D31以上系列HDVR默认使用RF格式  0:264，1：RF*/
	CTBIT31_E,/*FTP Video Upload和计划表功能,0:隐藏 1:显示*/
}ControlBit_E;

typedef enum
{
    COBIT0_E = 0,///*是否显示视频遮挡报警*/
    COBIT1_E = 1,//是否支持倒序播放，0不支持，1支持
    COBIT2_E ,   //IE回放页面是否支持多路回放（超过4路）1支持
    COBIT3_E ,   //1:无线nvr，0：有线设备
    COBIT4_E,    //隐藏OD功能，置1是  not display,	 置0是 display
    COBIT5_E ,	 // 球机ptz定时任务功能  1:开启 0:关闭
    COBIT6_E ,	 // 球机ptz三维定位功能  1:开启 0:关闭
    COBIT7_E,    //1:支持NewRecordDetailRsp (New_GetRecFileList)搜索，0：不支持
    COBIT8_E,    //1:支持NewRecordDetailRsp (New_GetRecFileList)录像下载，支持录像文件上锁查询以及上锁设置 ,0：不支持
	COBIT9_E,	 // 球机防抖功能，1:开启，0:关闭
	COBIT10_E,   //是否支持报警推送配置  1:支持 0:不支持
	COBIT11_E,   //模拟通道是否隐藏P/D协议  1:隐藏 0:显示
	COBIT12_E,   //cms图片回放功能   1：开启 0：关闭
    COBIT13_E,  //是否使用新的报警结构体0: RSNet_SoleIOAlarmSet_t, 1:RSNet_NewSoleIOAlarmSet_t
    COBIT14_E,  //云存储上传视频 1:支持 0:不支持 (只控制alarm_motion,alarm_pir,alarm_io页面)
	COBIT15_E,  //是否支持toe加速功能，0：不支持，1：支持
	COBIT16_E,   //是否取消WB室内模式   1：取消 0：不取消
	COBIT17_E,   //是否支持ipeye ，0：不支持，1：支持
	COBIT18_E,	 //是否支持智能加PIR的开关 ，0：不支持，1：支持
	COBIT19_E,	 //是否支持QVBR功能 1：支持，0：不支持
	COBIT20_E,   //User Page SEQ Control,  0:hide, 1:show
	COBIT21_E,   //   0:413, 1:427(MsgEmailTestNew)
    COBIT22_E,    //云存储上传图片 1:不支持 0:支持（为了兼容之前的版本）
	COBIT23_E,   // 使用upnp单独控制
	COBIT24_E,   // 使用FTP扩展地址，从16位扩到64位
	COBIT25_E,  //是否带OSD 透明度设置1:支持 0:不支持
    COBIT26_E,  //是否支持新的日志子类型搜索 1:支持 0:不支持 ---IPC
    COBIT27_E,  //是否支持告警输出计划表设置 1:支持 0:不支持
    COBIT28_E,  //是否支持NAS功能 1:支持 0:不支持
    COBIT29_E,   //是否支持RAID功能 1:支持 0:不支持
    COBIT30_E   //是否支持log子类型搜索 1:支持 0:不支持  ---dvr/nvr.
}ControlBit2_E;

typedef enum
{
    CoBitAry_0,  //是否支持3合1功能 1:支持 0:不支持
    CoBitAry_1,  //是否显示wireless camera页面 1:显示 0:不显示
    CoBitAry_2,   //是否显示channel config页面 1:显示 0:不显示
    CoBitAry_3,	//是否显示新的FD智能页面 1：显示 0：不显示
    CoBitAry_4,	//是否支持FTP升级 1：支持 0：不支持
    CoBitAry_5, //是否支持image页面白天黑夜设置
    CoBitAry_6, //人脸报警上报，1：支持，0：不支持
	CoBitAry_7,	// 人脸参数查询和设置, 1:支持，0：不支持
	CoBitAry_8, //是否支持智能分析、云视频情况查询、Motion、PIR、硬盘状态/VIDEO LOSSS、IO、6个智能加声音与遮挡报警  1:支持，0：不支持
	CoBitAry_9,//NotificationSchedule 页面, 1:显示、0:隐藏。
	CoBitAry_10, //是否支持白光强制彩光功能  1:支持，0：不支持
	CoBitAry_11, //是否支持IE下载板端抓图
	CoBitAry_12, //是否支持IE导入导出IPC参数
	CoBitAry_13, //推送参数支持json格式传输
	CoBitAry_14, //是否支持ipeye开启重启，1:支持，0：不支持
    CoBitAry_15,  //是否支持Alarm计划表, 1:支持，0：不支持
	CoBitAry_16, //是否支持白天和黑夜两套参数分开设置，1:支持，0：不支持
	CoBitAry_17, //是否支持强光抑制功能HLC，1:支持，0:不支持
	CoBitAry_18, //隐藏智能分析中 PID LCD SOD三个项目
	CoBitAry_19, //隐藏智能分析中 PD 项目
	CoBitAry_20, //隐藏智能分析中 CC 项目
	CoBitAry_21, //隐藏智能分析中 FD 项目	 1 隐藏 0 显示
	CoBitAry_22, //隐藏Image Control下Angle Rotation项  1 隐藏 0 显示	
	CoBitAry_23, //是否支持日志搜索页面json透传 1:支持，0：不支持
	CoBitAry_24, //是否支持硬盘页面json透传 1:支持，0：不支持
	CoBitAry_25, //是否显示智能分析统计页面，0:显示，1:不显示
	CoBitAry_26,	  //是否显示新的PD智能页面 1：显示 0：不显示
	CoBitAry_27, //是否显示ONVIF页面 1:显示  0:不显示
    CoBitAry_28, /*支持google IOT激活页面*/
    CoBitAry_29, //1:support watermask
    CoBitAry_30, //PTZ Linkage参数支持json格式传输
    CoBitAry_31, //抓图页面抓图质量等级 0:(good/better/best) 1:(best/better/good/bad/worse/worst)
	CoBitAry_32,// 是否支持行人、车辆搜索功能， 1：支持   0：不支持
	CoBitAry_33 , //是否支持手机云存储激活，1为支持
	CoBitAry_34, //是否隐藏DDNS页面，1为隐藏
	CoBitAry_35, //是否显示CC Ruletype(A->B)，1为显示    
	CoBitAry_36,	//是否隐藏NETWORK下面的UPnP界面， 1 隐藏 0 不隐藏
	CoBitAry_37,	//是否隐藏NETWORK下面的Email界面， 1 隐藏 0 不隐藏
    CoBitAry_38,	//是否隐藏NETWORK下面的IPFliter界面， 1 隐藏 0 不隐藏
    CoBitAry_39,   // IPC能力标识，是否支持特征值计算功能，1：支持， 0：不支持
    CoBitAry_40,  //升级 1:透传 0:非透传
    CoBitAry_41, //user 权限 1:板端判断 0: 客户端判断
    CoBitAry_42,//1 :single channel playback 0:normal playback
	CoBitAry_43,//1:liteos_net无线
	CoBitAry_44,    //支持POE带宽设置
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
//心跳
//请求 MsgType=MsgHeartbeat
//回应 


//////////////////////////////////////////////////////////////////////////
//包

//PackHead.Version
#define PackHeadV1		0
#define PackHeadV2      1

#define MaxPackSize		    1400
#define MaxPackSize_2       (8*1024)

//PackHead.Type
#define FramePack				0 //帧拆分的包
#define ReposPack				1 //回放时重定位包，代表后续发送的是重定位后的数据
#define NoDataPack				2 //回放时表示当前回放时间点后面已经没有录像数据
#define FileEndPack				3 //录像下载时表示一个文件传输结束
#define IFrameEndPack  			4 //I 帧数据结束
#define IsThumbnailsPack        5 //缩略图
#define TalkPassthroughHeart    6
#define ReversePack             7 // 倒序播放开始

typedef struct
{
	BYTE Version : 2; //包头版本
	BYTE ExtSize : 6; //包头扩展大小，实际扩展大小 = ExtSize * 4
	BYTE Type;
	WORD PackNum;
	UINT FrameNo;
	WORD PackNo; //0,1,2,3...
	WORD PackSize;
}PackHead; //包头, sizeof(PackHead) = 12


//////////////////////////////////////////////////////////////////////////
//预览

//Type
#define PreviewMain	0
#define PreviewSub	1
#define PreviewMobile 2

//Content
#define PreviewComposite	0
#define PreviewVideoOnly	1

typedef struct
{
	UINT Channel; //通道号 0,1,2,3...
	BYTE Type; //主从码流
	BYTE Content; //复合流或视频流
    BYTE timepos; //获取录像的时间点：0 当前时间点 1 更早录像时间点
    BYTE bufsize; //最大帧数据大小,实际大小 = bufsize*1024*10; 
}PreviewParam;


//////////////////////////////////////////////////////////////////////////
//TCP预览
//请求 MsgType=MsgTcpPreview, MsgSize=sizeof(TcpPreviewReq)
//回应 成功AckFlag=AckSuccess 失败AckFlag=AckFail

typedef struct
{
	PreviewParam Param;
	UINT UserKey;
}TcpPreviewReq;


//////////////////////////////////////////////////////////////////////////
//UDP探测
//请求 MsgType=MsgGetUdpAddr
//回应 MsgSize=size(GetUdpAddrRsp)

typedef struct
{
	struct sockaddr_in ClientAddr;
	UINT socketfd;
	BYTE Addr[44];
}GetUdpAddrRsp;


//////////////////////////////////////////////////////////////////////////
//UDP开始预览
//请求 MsgType=MsgStartUdpPreview, MsgSize=sizeof(UdpStartPreviewReq)
//回应 成功AckFlag=AckSuccess, MsgSize=sizeof(UdpStartPreviewRsp) 失败AckFlag=AckFail

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
//UDP停止预览
//请求 MsgType=MsgStopUdpPreview, MsgSize=sizeof(UdpStopPreviewReq)
//回应 

typedef struct
{
	UINT UdpPreviewKey;
}UdpStopPreviewReq;


//////////////////////////////////////////////////////////////////////////
//强制I帧
//请求 MsgType=MsgForceIFrame, MsgSize=sizeof(PreviewParam)
//不需要回应
typedef struct 
{       
	UINT Channel; //通道号 0,1,2,3...
	BYTE Type;    //主从码流,同预览
	BYTE Reserved[7];
} IFrameReq;

//////////////////////////////////////////////////////////////////////////
//云台控制
//请求 MsgType=MsgPTZControl, MsgSubtype=MsgPTZUp..., MsgSize=sizeof(PTZControlReq)
//回应 成功AckFlag=AckSuccess, 失败AckFlag=AckFail

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
	UINT Time; /* 预置点巡航间隔时间
				  0  表示5S ; 1 表示10S; 2 表示15S */
	UINT LineSpeed;
}PTZControlCruise;

typedef struct
{
	UINT Index;
    UINT Time;  /* 预置点巡航间隔时间 */
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

/*ipc, kg需求*/
typedef struct
{
	BYTE Sensor_id[32]; /* 查询指定sensor ID 预置位 */
	UINT PresetIndex;  /* 指定sensor ID 预置位范围(0 -16)*/ 
}PTZSensorPresetInfo;
//////////////////////////////////////////////////////////////////////////
//色彩控制
typedef struct
{
	UINT Channel;
	BYTE Chroma;       /* 色度, <0 - 63> */
	BYTE Brightness;   /* 亮度, <0 - 63> */
	BYTE Contrast;     /* 对比度, <0 - 63> */
	BYTE Saturation;   /* 饱和度, <0 - 63> */
	BYTE reservel[20];
}ColorCtrlReq;

//////////////////////////////////////////////////////////////////////////
//时间结构

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
//录像查询 按位查询，一共32位

//RecordType
//#define NormalRecord	0x1
//#define AlarmRecord		0x2
//#define AllRecord		0xFFFFFFFF //Only for req, equal to NormalRecord|AlarmRecord...

#define NoRecord            0x0
#define NormalRecord        0x1
#define AlarmRecord         0x2
#define MotionRecord        0x4
#define IORecord            0x8
#define PEARecord           0x10   // 旧智能，新智能不再使用
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
#define AlarmAssemble       0x7FFFFFFF//两个或者两个以上的报警类型时，上传此值
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

//无论哪种方式查询,回应时,若该时间段内无录像,也应返回成功AckFlag=AckSuccess, MsgSize=0

//请求 MsgType=MsgQueryRecord, MsgSubtype=MsgRecordDetail, MsgSize=sizeof(QueryRecordReq)
//回应 成功AckFlag=AckSuccess, MsgSize=n*sizeof(RecordDetailRsp) 失败AckFlag=AckFail

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

//无论哪种方式查询,回应时,若该时间段内无录像,也应返回成功AckFlag=AckSuccess, MsgSize=0

//请求 MsgType=MsgQueryRecord, MsgSubtype=MsgRecordDetail, MsgSize=sizeof(QueryRecordReq)
//回应 成功AckFlag=AckSuccess, MsgSize=n*sizeof(RecordDetailRsp) 失败AckFlag=AckFail

typedef struct
{
	UINT StructSize; //sizeof(RecordDetailRsp)
	DateTime Begin;
	DateTime End;
	UINT Type; //RecordType
	UINT Size; //文件大小
}RecordDetailRsp;

//请求 MsgType=MsgQueryRecord, MsgSubtype=MsgRecordDayOutline, MsgSize=sizeof(QueryRecordReq)
//回应 成功AckFlag=AckSuccess, MsgSize=n*sizeof(RecordDayOutlineRsp) 失败AckFlag=AckFail

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
//录像下载
//请求 MsgType=MsgDownloadRecordFile, MsgSize=sizeof(DownloadRecordFileReq)+n*sizeof(RecordDetailRsp)
//回应 成功AckFlag=AckSuccess 失败AckFlag=AckFail
//传输数据: file1,FileEndPack; file2,FileEndPack; ... filen,FileEndPack
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
//录像回放

//开始回放
//请求 MsgType=MsgRecordPlay, MsgSize=sizeof(RecordPlayReq)
//回应 成功AckFlag=AckSuccess, 失败AckFlag=AckFail, 回应后不发送数据,统一在收到MsgRecordDataInsufficient后发送

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

//回放反馈
//请求 MsgType=MsgRecordPlayFeedback, MsgSubType=MsgRecordDataInsufficient,MsgRecordDataEnough
//不需要回应

//重定位录像数据
//请求 MsgType=MsgReposRecordData, MsgSize=sizeof(ReposRecordDataReq)
//不需要回应,收到此消息后,即刻停止发送之前的数据(不过必须是发送完一个完整的包之后),接着发送ReposPack,最后是发送新的数据
typedef struct
{
	DateTime Begin;
	DateTime End;
}ReposRecordDataReq;

//心跳 在接收数据时,不会发送此消息
//请求 MsgType=MsgHeartbeat
//不需要回应


//////////////////////////////////////////////////////////////////////////
//对讲
//请求 MsgType=MsgDualtalk, MsgSize=sizeof(DualtalkReq)
//回应 成功AckFlag=AckSuccess 失败AckFlag=AckFail

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
//日志查询

//LogType
#define LOG_TYPE_IO         0x0
#define LOG_TYPE_MD         0x1
#define LOG_TYPE_HDD        0x2
#define LOG_TYPE_VLOSS      0x3
#define LOG_TYPE_OPERA      0x4  // 查询使用
#define LOG_TYPE_ALARM      0x5  // 查询使用, 包括io、md、视频丢失和硬盘     
#define LOG_TYPE_ALL        0x6  // 查询使用, 全部

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
    UINT Operation;  // 用户操作:第一次显示;下一页;上一页;最后一页
    UINT ExpectNum;  // 希望返回的个数
}QueryLogReq;

/*仅限DVR使用*/
typedef struct
{
    UINT StructSize; //sizeof(QueryLogRsp)
    UINT Channel;
    UINT Type;
    DateTime Point;
    BYTE Reserved[4];
}QueryLogRsp;

/*仅限IPC使用*/
typedef struct
{
	UINT StructSize;
	char event[64];		///< event description
	BYTE Reserved[4];
}QueryLogRsp_IPC;

//////////////////////////////////////////////////////////////////////////
//参数配置

//Element : ElementSize + ExtensibleStruct + zero or more List
//List : ListSize + one or more Element
//ExtensibleStruct : StructSize + other member define
//注意: Element至少必须有一个非空的ExtensibleStruct（只有一个StructSize=4的结构表示空的)或非空的List，否则该Element表示空的（无意义）应删去
//		List至少必须有一个满足上一条件Element

//回应 成功AckFlag=AckSuccess 失败AckFlag=AckFail 参数错误AckFlag=AckParamError, 权限不够AckFlag=AckAuthorityFail



typedef struct
{
	UINT StructSize;
	UINT ChannelMask[8];
}ChannelParamReq;

//////////////////////////////////////////////////////////////////////////
//告警上报
//板端直接上报，客户端无须回应
//
//MsgType=MsgAlarmReport
//移动侦测: MsgSubType = MsgMotionAlarm, MsgSize = sizeof(MotionAlarmRpt)
//IO报警: 	MsgSubType = MsgIOAlarm, MsgSize = sizeof(MotionIORpt)
//智能分析: MsgSubType = MsgAIAlarm, MsgSize = sizeof(MotionAIRpt)

//Status
#define AlarmOn  1 
#define AlarmOff 0 

typedef struct
{
	UINT Channel;
	int Status;
	DateTime AlarmTime;
    char RecState;               /* 录像状态 */
    char CurRecType;             /* 当前录像类型 */
    char Schedule;             /* 报警计划*/
	char RecEnable;           /* 是否开启触发录像功能 */
    UINT ProtocolType;  /* IPC协议类型 */
	UINT Abilities;     /* IPC设备能力 */
	UINT Channel_EX[8];
	UINT Status_EX[8];
	UINT IPCDevTypeFlag; /*IPC设备类型*/
	U8 MsgValidFlagIPCWeb; // whether the msg is valid for IPC IE , 0:valid , 1:invalid (2016.10.28 add)
	U8  InputNum;                 /*ipc io报警输入路数*/
	U8  OutputNum;                /*ipc io报警输出路数*/
	U8  bBoxEnable : 1; //弹窗使能 20170928 板端是否控制web弹窗
	U8  bBoxDisplay : 1;//弹窗显示 20170928 触发报警时是否显示弹窗
	U8  Reserve : 6;
	UINT AlarmType;
	/*0:NORMAL;    1:MDALARM;   2:IOALARM;   3:SMART_PEALINE;   4:SMART_AVD;     5:SMART_OSC;
	6:SMART_PEAAREA;  7:SMART_HD;  8:SMART_FD;    9:SMART_CC;*/
	BYTE PowerStat[256];
	BYTE DevName[128];
	BYTE IOName[64];
	U8  bChnMode;  /*0:睡眠模式,1:常开模式*/
	BYTE res[3];
	UINT ClientAutoLogoutTime ;
	UINT AbilitiesEx;
	BYTE resver[52];
}RsNetAlarmRpt;

typedef struct
{
	UINT StructSize;
	UINT chn;       /* 0xffffffff 表示所有通道，其他值表示具体数值指定的通道 */
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


/* 周界伴线 */
typedef struct {

    BYTE ChnSwitch;          /*0-关闭，1-打开*/
    BYTE RuleSwitch;         /*每个通道用一个字节表示最多8条规则，0-关闭，1-使用*/
    BYTE RuleType;           /*每个通道用一个字节表示最多8条-规则类型，0-伴线，1-周界*/
    BYTE LineTwoWay;         /*每个通道用一个字节表示最多8条-伴线类型双向，0-否，1-双向*/
    BYTE reserver[4];
    Net_Rule_Line_S RuleLine[32];	/*每通道最多有64个点坐标,即32条线，如果是伴线则只使用第1条线，
                                 如果是周界则将这8条线依次连接起来组成闭合图形 */
}SolePEALineMsg;

typedef struct
{
    SolePEALineMsg RuleLine[32];

}SolePEAAlarmRpt;


/* 物品遗留丢失*/
typedef struct{
    BYTE ChnSwitch;         	 /*0-关闭，1-打开*/
    BYTE RuleSwitch;        	 /*每个通道用一个字节表示最多8条规则，0-关闭，1-使用*/
    BYTE reserve[6];
    BYTE RuleRectEnable[8];  	 /*每通道最多有8条规则，每规则最多有4区域.每一位代表一个区域的使能，目前只用前四位*/
    Net_Rule_Line_S RuleRect[32];/*每规则最多有4区域,即每通道最多有8＊4＝32个区域*/
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
	U8 IPCDevTypeFlag; /*IPC设备类型*/	
	U8 MsgValidFlagIPCWeb;//whether the msg is valid for IPC IE , 0:valid , 1:invalid (2016.10.28 add);
	S8 s8Reserve[2];
    UINT AbilitiesEx;
}DevStatRpt;

typedef struct
{
	UINT Channel;
	UINT Status;
	DateTime AlarmTime;
    char RecState;               /* 录像状态 */
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
#define AIPerimeterAlarm 0 //周界报警
#define AITripwireAlarm 1 //绊线报警

typedef struct
{
	UINT Channel;
	UINT Status;
	UINT AIType;
	DateTime AlarmTime;
}AIAlarmRpt;

/*通过报警机制实时传递智能分析规则数据*/
#define MAX_AI_POS_COUNT  16
typedef struct  
{
	/*通道号*/
	BYTE Channel;
	/*规则号*/
	BYTE RuleNo;
	/*使能开关*/
	BYTE RuleEnable;
	/*规则类型，0-绊线，1-周界*/
	BYTE RuleType;
	/*方向限制*/
	BYTE Direction;
	/*保留位*/
	BYTE reservel[3];
	/*拌线或周界的坐标值，拌线仅使用前四个单元，偶数下标为x坐标，奇数下标为y坐标*/
	unsigned short aiPoints[MAX_AI_POS_COUNT]; 
} AIDataRpt;

//MsgRecordStatusReport
//录像告警类型定义
#define RECORDSTATUSTYPE_NORMAL      0 
#define RECORDSTATUSTYPE_MANUAL      1 
#define RECORDSTATUSTYPE_MOTION      2 
#define RECORDSTATUSTYPE_IO          3 
#define RECORDSTATUSTYPE_MOTION_IO   4  //移动侦测和IO告警
#define RECORDSTATUSTYPE_MOTION_END  5  //移动侦测停止  
#define RECORDSTATUSTYPE_IO_END      6  //IO停止 
#define RECORDSTATUSTYPE_PEA         7 
#define RECORDSTATUSTYPE_OSC         8 
#define RECORDSTATUSTYPE_PEA_END     9 
#define RECORDSTATUSTYPE_OSC_END     10 
#define RECORDSTATUSTYPE_PEAAREA     11 // PEA-Area 2015.11.26
#define RECORDSTATUSTYPE_PEAAREA_END 12 // PEA-Area 2015.11.26

#define RECORDSTATUSTYPE_SMART       13 // 所有智能告警标识统一成一个 2016.05.12
#define RECORDSTATUSTYPE_SMART_END   14 // 所有智能告警标识统一成一个 2016.05.12

#define RECORDSTATUSTYPE_PIR         15  // PIR 2017.08.07
#define RECORDSTATUSTYPE_PIR_END     16  // PIR 2017.08.07

typedef struct
{
	UINT Type;  //报警的类型
	DateTime AlarmTime;//报警时间
	
	UINT ChannelNum;     //对应告警通道号 如果为0xffffffff则为所有通道
	BYTE RecordStatus;   //录像状态 ， 1 开始录像 0 停止录像
	U8  bBoxEnable : 1; //弹窗使能 20170928
	U8  bBoxDisplay : 1;//弹窗显示 20170928
	U8  Reserve : 6;
	BYTE reservel[2];
    UINT AllChanRecState;    //所有通道的录像状态	
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
	DateTime AlarmTime;	//报警时间
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
	
	BYTE HddStatus;	//硬盘状态，取RS_HDDSTATUS_E值
	BYTE reserve[3];
	char HddSN[32];		//磁盘出厂序列号
	DateTime AlarmTime;	//报警时间
}HddStatusRpt;


//////////////////////////////////////////////////////////////////////////
//为了保存此协议文件的独立性，添加Gps信息上告的时候，
//也并把PuInfoHead_t和GpsINfo_t从RSFrame.h文件中拷贝过来 
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
	float SensorSpeed;          //传感器速度，作为可选模块，可能该值无效
	float Azimuth;    			//方向角 正北为0，顺时针方向 0~360
	int Signal3G;               //3G信号
	unsigned int TotalMileage;  //  总行程
	int Temperature;
	char LatitudeDir;       	// 南北半球 'N' or 'S'
	char LongitudeDir;      	// 东西半球 'E' or 'W'
	char Rectified;             // 是否已经检验
	char Status;   				//状态, 'A' 为有效位置, 'V'为非有效接收警告，即当前天线视野上方的卫星个数少于3颗。
	unsigned char IgnitionFlag; //点火标志位。1:点火，0：熄火
	char Reserved[3];
	double LongitudeOffset;
	double LatitudeOffset;
}GpsInfoRpt_t;

//GPS信息上告结构体
//MsgGpsInfoReport
typedef struct 
{
	PuInfoHeadRpt_t stHeadRpt;
	GpsInfoRpt_t stBodyRpt;
	
	DateTime AlarmTime;
}GpsInfoPacketRpt;


//////////////////////////////////////////////////////////////////////////
//请求状态

//请求 MsgType=MsgStatusRequest, MsgSubtype	= MsgDevAllStatusReq; MsgSize=0
//回应 成功AckFlag=AckSuccess, MsgSize=sizeof(DevAllStatusRpt) 失败AckFlag=AckFail

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
	
	UINT RecordEnable;	//录像使能，按位表示, 低位为通道0
	UINT RecordStatus;	//录像状态，按位表示, 低位为通道0

	UINT MotionEnable;	//移动使能，按位表示, 低位为通道0
	UINT MotionStatus;	//移动侦测状态，按位表示, 低位为通道0
	
	UINT IOEnable;		//IO告警使能，按位表示, 低位为通道0
	UINT IOStatus;		//IO告警状态，按位表示, 低位为通道0
	
	UINT VLossStatus;	//视频丢失状态，按位表示, 低位为通道0
	
	BYTE HddStatus[8];	//录像状态，取RS_HDDSTATUS_E值
	BYTE HddSN[8][32];	//磁盘出厂序列号
	
	//32个通道的不同的录像状态的标识, 取宏 RS_RECORD_STATUS_E 的值
	BYTE RecordAllStatus[32]; 
    BYTE FtpNewVersFlag;    //是否有新的升级文件标识量:1 有;0 没有, 2: 完成
                            //5: emergency(lorex 专用),IE不弹框显示
	BYTE reserve2[2];
	BYTE zeroChSwitch;//1:零通道开启,0:关闭
    UINT AudioStatus;   //音频状态,按位表示,低位为通道0.(ALTE客户)
    U32  PageIntelligent; 	 //ipc intelligent analysis capability sets (see PageIntelligent_E) add 2016.10.27
	UINT IntelligentChnStatus;	//ui5.0, 表示总的智能录像状态
	UINT IntelligentChnStatusExt[6];//ui5.0这里保留192路，总共224路，应该够用了
	UINT IntelligentStatus;/*only for ipc used , bit value*/
	/*0:NORMAL;1:MDALARM;2:IOALARM;3:SMART_PEALINE;4:SMART_AVD;5:SMART_OSC;
	  6:SMART_PEAAREA;7:SMART_HD;8:SMART_FD;9:SMART_CC;*/
	UINT CameraCoverSwitch;
	UINT CameraCoverState;
	UINT MotionStatusExt[8];  //移动侦测状态
	UINT IOStatusExt[8];      //IO告警状态
	BYTE RecordAllStatusExt[8][32];
	UINT PIRStatusExt[8];//PIR状态，按位表示, 低位为通道0 (2016.11.01 add for hydvr)
	UINT SmokeStatusExt[8];//Smoke状态，按位表示, 低位为通道0  (2016.11.01 add for hydvr)
	BYTE PageIntelligentChn[128];//每个通道的智能分析能力，按位表示(see PageIntelligent_E,2016.11.23 add for nvr)
	BYTE  InputNum[256];                 /*ipc io报警输入路数*/
	BYTE  OutputNum[256];                /*ipc io报警输出路数*/
	UINT PirEnable;		//红外使能，按位表示, 低位为通道0
	UINT PirStatus;     //红外侦测状态，按位表示, 低位为通道0
	BYTE PowerStateChange[256];
	BYTE PowerChargeState[256];
	UINT AudioStatusExt[8];      //音频开关状态
	BYTE PlaybackState;   //板端是否正在回放

	BYTE HddStatus_ex[32];	//录像状态，取RS_HDDSTATUS_E值
	BYTE PageIntelligentChnExt[128];//每个通道的智能分析能力，比特位从PageIntelligentChn开始算
	BYTE res[95];
}DevAllStatusRpt;

typedef struct
{
	BYTE code_mode;
	BYTE curShowMode;
	BYTE curStreamNum;
	BYTE unused[13];
}FishEyeIpcStatusRpt;

/* 设备最后一次事件记录 (ALTE客户专用) */
typedef struct
{    
    DateTime LastTime; //录像时间
    BYTE ChannelNo;    //录像通道
    BYTE RecType;      //录像类型
    BYTE reserved[22];
}DevLastRecordRpt;

/* lorex http检测升级，需要传递到远端的参数 2014-10-13*/
typedef struct
{
    BYTE OldVersion[8];     //旧版本号
    BYTE NewVersion[8];     //新版本号
    BYTE model[16];         //设备型号
    BYTE message[256];      //提示语
    BYTE reserved[32];
}HttpUpgsRemoteParam_S;

//请求 MsgType=MsgStatusRequest, MsgSubtype	= MsgRemoteCHStatusReq; MsgSize=0
//回应 成功AckFlag=AckSuccess, MsgSize=MAX_CHN_NUM * sizeof(RemoteChnStatusRpt) 失败AckFlag=AckFail

//MsgRemoteCHStatusReport
//MsgRemoteCHStatusReq
typedef struct
{
	unsigned long long DevType;  /* 设备类型 */
	char CurChnName[20];         /* 设备名称 */

	char CurChnState;            /* 当前通道设备状态 */
    char RecState;               /* 录像状态 */
    char CurRecType;             /* 当前录像类型 */
    char MDState;                /* Motion报警状态 */

    char IOState;                /* IO报警状态 */
    char VLossState;             /* 视频丢失状态 */
	char HddState;               /* 硬盘阙状态 */
    char MDSchedule;             /* 移动报警计划*/

    char AlarmSchedule;          /* 报警计划*/
	
    unsigned char ChannelNum;		/*当前设备拥有的通道数*/
    BYTE  IPCDevTypeFlag;        /*IPC类型标志,用于兼容性3516D,对应IPC_Dev_Type_e*/
    char  NewDevAbilityModeFlag;      /*此标志用于区分私有IPC能力修改为先取0再置位*/
	
    UINT ProtocolType;/*当前的协议类型，对应PROTO_TYPE_E*/
	UINT Abilities;   /*每一位代表一种能力，0不支持，1支持，对应ABILITY_TYPE_E*/
	char chnName_EX[128];
	char chnMode;//0:睡眠(不能自动重连)  1:常开(可以自动重连)
	char res[7];
	U32 AbilitiesEx;             /*扩展位，每一位代表一种能力，0不支持，1支持，对应Net_ABILITYEX_TYPE_E*/
	char resver[116];
}DevChnInfo;
//C_ASSERT(sizeof(DevChnInfo) == 56);

/* IPC设备类型,用于兼容RS 3516D IPC升级 */
typedef enum
{
    IPC_Reserve_e = 0,    
    IPC_RS_H264_e = 1,
    IPC_RS_H265_e,
    IPC_Onvif_H264_e,
    IPC_Onvif_H265_e,
	IPC_ENCODE_H265_e,/*In view of the third party manufacturer, whether to support h264 / h265 coding*/
	IPC_RS_H264_plus_e,//支持安联H264，H264+
	IPC_RS_H265_plus_e,//支持安联H265，H265+
	IPC_RS_H264_H265_plus_e,//支持安联H264，H265，H264+，H265+
	IPC_RS_H264_AVBR_e,//支持安联H264，假H264+，目前模拟通道使用
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
	UINT PreviewChannel[8];  /*预览通道*/
	unsigned char UserPreview;     /*预览权限*/
	unsigned char Reserv[7];     
}RsSamsungPreview;

typedef struct
{
	RsSamsungPreview alluser[7];			//user1、user2、user3、user4、user5、user6、user7，不放admin
	unsigned  int PreviewCovert[8];			/*预览开关*/
}RsNetSamsungPCAlarmRpt;

// MsgFtpUpgradeAlarm 告警回复
#define FTPUPGRADE_SUCCESS    0
#define FTPUPGRADE_UPGRADEING 1
#define FTPUPGRADE_PRE_REBOOT 2 
#define FTPUPGRADE_ERROR      3 

typedef struct {
	BYTE UpgradeProcess;  // 完成进度 100 为升级完成	
	BYTE UpgradeStatus;    // 当前升级状态
	BYTE reserved[2];	
}FtpUpgradeRpt;
typedef struct {
	BYTE UpgradeProcess;  // 完成进度 100 为升级完成	
	BYTE UpgradeStatus;    // 当前升级状态
	BYTE reserved[2];	
}UpgradeRpt;//new name



//////////////////////////////////////////////////////////////////////////
//告警订阅
//请求 MsgType=MsgAlarmSubscribe, MsgSubType=MsgAlarmDesired, MsgAlarmRefused
//回应 成功AckFlag=AckSuccess 失败AckFlag=AckFail


//////////////////////////////////////////////////////////////////////////
//远程升级

//请求 MsgType=MsgRemoteUpgrade, MsgSize=sizeof(RS_UpgradeReq)
//回应 成功AckFlag=AckSuccess, MsgSize=RS_UpgradeRsp 失败AckFlag=AckUpgrading,AckUpgradeVersionError,AckFail

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

/* 远程升级 IPC */
typedef struct
{
    UINT UserKey;      //用户 id
    UINT FileSize;     //升级文件大小
    UINT ChannelMask;  //通道掩码.按位取,1:需要升级;0:不需要
    BYTE reserved[4];
    BYTE FileName[256];//升级文件名
    UINT ChannelMask_EX[8];  //通道掩码.按位取,1:需要升级;0:不需要
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

//数据传输 
//MsgType=MsgRemoteUpgrade, MsgSubType=MsgRemoteUpgradeData,MsgSize=MaxUpgradeFileHead
#define MaxUpgradeDataSize	4096 //一个模块最后可能会有小于MaxUpgradeDataSize的数据

//一个模块传输结束
//请求 MsgType=MsgRemoteUpgrade, MsgSubType=MsgRemoteUpgradePartEnd
//不需要回应

//结束
//请求 MsgType=MsgRemoteUpgrade,MsgSubType=MsgRemoteUpgradeEnd, MsgSize=sizeof(RemoteUpgradeEndCheck)
//回应 成功AckFlag=AckSuccess, 失败AckFlag=AckFail ,MsgSize=sizeof(RemoteUpgradeEndWriteFlash)

typedef struct
{
	ULONG Crc;
}RemoteUpgradeEndCheck;

typedef struct
{
    BYTE WriteFlashFlag; //是否有烧写flash进度显示  1: 有  0: 无
    BYTE reserved[3];
}RemoteUpgradeEndWriteFlash;

//回应 MsgType=MsgRemoteUpgrade,MsgSubType=MsgRemoteUpgradeWriteFlashInProgress, MsgSize=sizeof(WriteFlashProgress)  (0 < progress <= 100)
//回应 MsgType=MsgRemoteUpgrade,MsgSubType=MsgRemoteUpgradeWriteFlashEnd 表示升级完成
typedef struct 
{
    unsigned char Progress;//表示进度
    char reserved[3];
}WriteFlashProgress;

//Email测试
typedef struct
{
	WORD Ssl;
	WORD Port;
	BYTE Server[MaxNameLen];
	BYTE Sender[MaxNameLen];  
	BYTE Receiver[MaxNameLen];
	BYTE Password[MaxNameLen];
    BYTE TestType;            //0: 普通测试, 1: Kguard 云邮件测试
	BYTE StopTest;
	BYTE Reserved[14];
	BYTE RecvEmail[3][MaxNameLen];
	BYTE username[MaxNameLen];
} EmailTestReq;

//新Email测试
typedef struct
{
	WORD Ssl;
	WORD Port;
	BYTE Server[128];
	BYTE Sender[128];  
	BYTE Receiver[128];
	BYTE Password[128];
    BYTE TestType;            //0: 普通测试, 1: Kguard 云邮件测试
	BYTE StopTest;
	BYTE Reserved[14];
	BYTE RecvEmail[3][128];
	BYTE username[128];
} NewEmailTestReq;


//DDNS测试
typedef struct
{
	BYTE Serveraddr;
	BYTE Hostname[MaxNameLen];
	BYTE Username[MaxNameLen];
	BYTE Password[MaxNameLen];
    BYTE s8TestType;
	BYTE s8CommaxUseLoginFlag;
	BYTE s8UseDDNS;
	BYTE s8IpType;//LUXVISION加的DDNS选择IP模式（IPV4/IPV6）
    BYTE Reserved[11];
	BYTE s8UserUrl[128];
} DDNSTestReq;

/* ftp远程升级请求 */
typedef struct
{
    UINT UserKey;
    BYTE reserv[60];
}RS_FtpUpgradeStatusReq;

/* ftp远程升级回应结果 */
typedef struct
{
    UINT structSize;
    int status;
    BYTE resver[256];
}FtpUpgradeStatus;

/* 远程请求具体类型 */
typedef struct
{
    BYTE ReqType;   /*请求主类型,1:云存储.2:固件升级(扩展)*/
    BYTE ReqSubType;/*请求子类型,1:云存储升级检测.2:云存储升级*/
    WORD ReqMsgSize;/*请求携带的数据大小*/
    BYTE reserved[28];
}RemoteCheckReq;

/* 远程请求回应结果 */
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

//硬盘格式化
#define HDDFORMAT_SUCCESS            0
#define HDDFORMAT_FORMATTING         1 
#define HDDFORMAT_FAIL               2 
#define CANNOT_HDDFORMAT_RECDOWNLOAD 3
typedef struct
{
	UINT HddBitmap;
	UINT ChannelBitmap;	//只格式化该通道内容
		
	BYTE Reserved[12];
} HddFormatReq;

typedef struct 
{
	BYTE HddNO;     // 格式化盘号 
	BYTE HddFormatProcess; //  格式化进度  10秒获取一次格式进度，状态
	BYTE HddFormatStatue;  // 格式化状态 0-格式化成功 1正在格式化 2 格式化失败

	 BYTE Reserved[13];
}HddFormatRsp;
//////////////////////////////////////////////////////////////////////////
//时间同步
#define MaxTimeZoneSize  10
typedef struct 
{   
    DateTime Time;
    char     TimeZone[MaxTimeZoneSize];
    char     Reserved[42];
}TimeSyncReq;

//////////////////////////////////////////////////////////////////////////
//远程抓图
typedef struct 
{
	/*注意：当图像压缩分辨率为VGA时，支持0=CIF, 1=QCIF, 2=D1抓图，
	当分辨率为3=UXGA(1600x1200), 4=SVGA(800x600), 5=HD720p(1280x720),6=VGA,7=XVGA, 8=HD900p
	仅支持当前分辨率的抓图*/
	UINT    StructSize;
	WORD	wPicSize;				/* 0=CIF, 1=QCIF, 2=D1 3=UXGA(1600x1200), 4=SVGA(800x600), 5=HD720p(1280x720),6=VGA*/
	WORD	wPicQuality;			/* 图片质量系数 0-最好 1-较好 2-一般 */
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
//设置远端设备网络态
//NVR

//请求 MsgType=MsgDevNetCfg, MsgSubType=MsgNoSubType, MsgSize=sizeof(NetMDevInfoReq)
//回应 成功AckFlag=AckSuccess, MsgSize=sizeof(NetMDevInfoRsp) 失败AckFlag=AckFail, MsgSize=sizeof(NetMDevInfoRsp);
#define MAX_UNAME_LEN 10
#define MAX_PWD_LEN   14

typedef struct _NetMDevInfoReq_ //请求
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

// New NetMDevInfoReq, 为了兼容 旧版本
typedef struct _NewNetMDevInfoReq_ //请求
{
    union
	{
		NetMDevInfoReq DevInfoReq;//旧版本结构体  
		BYTE IpcName[64];
	};
	U64  devTypeULL;            
	BYTE macAddr[36];   //设备MAC地址      
}NewNetMDevInfoReq;

struct NetMDevInfoRsp //设备回复
{
	BYTE msgid[16];  //请求方给出msgid,设备原值返回
};

typedef struct _RsNetSearchReq_t //请求
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
    BYTE macAddr[40];   //设备MAC地址   
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
//查询搜索远端设备状态
//NVR

//请求 MsgType=MsgSearchRemoteDev, MsgSubType=MsgNoSubType, MsgSize=sizeof(SearchRemDevReq)
//回应 成功AckFlag=AckSuccess, MsgSize=n*sizeof(SearchRemDevRe) 失败AckFlag=AckFail, MsgSize=0;

typedef struct
{
	UINT UserKey;
}SearchRemDevReq;

typedef struct
{
    UINT StructSize;		//sizeof(SearchRemDevRe)
    BYTE IPAddr[4];			/*IP地址*/
    BYTE Netmask[4];
    BYTE GateWay[4];
    BYTE Dns1[4];
    BYTE Dns2[4];

    UINT Port;				/*媒体端口*/
    UINT WebPort;

    BYTE DevType[8];
    char UserName[36];		/*登陆用户名*/
    char UserPW[36];		/*登陆用户密码*/
    char DeviceName[36];	/*设备名称，可以修改*/

    BYTE Protocol;		  //0:RS, 1:HiK, 2:DaH, 3:HH, 4:Onvif
    BYTE ChnMax;			/*当前ip对应的前端设备的总通道数*/
    BYTE Version ;
    BYTE switchmode; /*0 自动模式 1 自动模式*/

    BYTE MacAddr[36];
    U8 switchflag; /*1 连交换机口 0 表示没有*/
    U8 portnum;    /*交换机口 从[0  -MAX_POE_NUM) */
    U8 FrontEndChnnal;
    U8 reserved;
	unsigned long long DevTypeULL;

	//onvif协议，ie远程搜索添加信息
	char hardware[36];
	char software[36];
	char devicetype[24];
	char manufacturer[36];
    U8 reserved2[4];
	U8 MulChannel[8];//多通道使用

}SearchRemDevRep;


//////////////////////////////////////////////////////////////////////////
//设置远端设备网络参数
//NVR

//请求 MsgType=MsgSetRemoteDevNet, MsgSubType=MsgNoSubType, MsgSize=n*sizeof(SetRemDevNetReq)
//回应 成功AckFlag=AckSuccess, MsgSize=n*sizeof(SetRemDevNetRep) 失败AckFlag=AckFail, MsgSize=0;
typedef struct
{
	UINT StructSize;		//sizeof(SetRemDevNetRe)

	UINT UserKey;
	
	BYTE TargetIPAddr[4];			/*目标IP地址*/
	UINT TargetPort;				/*目标媒体端口*/    
	
    /*IP地址*/
    BYTE IPAddr[4];
    /*子网掩码*/
    BYTE NetMask[4];
    /*网关*/
    BYTE GateWay[4];
    /*客户端端口号*/
    UINT Port;
    /*Web端口号*/
    UINT WebPort;
    /*DNS1*/
    BYTE Dns1[4];
    /*DNS2*/
    BYTE Dns2[4];
	
	char UserName[36];		/*修改参数需登陆用户名*/    
	char UserPW[36];		/*修改参数需登陆用户密码*/    
	
	BYTE MacAddr[36];
	unsigned long long DevTypeULL;
	BYTE Version ;
	BYTE reserved[3];
}SetRemDevNetReq;

typedef struct
{
	UINT StructSize;		//sizeof(SetRemDevNetRep)
	UINT ErrCode;			//0则成功，其他则为sdk返回错误码
}SetRemDevNetRep;


//////////////////////////////////////////////////////////////////////////
//视频激活
//请求 MsgType=MsgReqVideoActivation;MsgSize=sizeof(VideoActivationReq);无子消息类型
//回应 成功AckFlag=AckSuccess,MsgSize= 0  失败 AckFlag=AckFail;
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
	char InfoFlag;  //判断网络硬盘认证转发路线 :0 客户服务器路线 ,1 EmaliTest路线，
	char ErrCode;   //  
	char reserve[2];
	char RetMsgInfo[500];
}ActivateCloudRsp;

//FtpWriteFile测试
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
    UINT ChannelMask;//通道掩码
	UINT UserKey;    //User key
    BYTE reserved[4];
    UINT ChannelMask_EX[8];//通道掩码
}RebootIpcReq;
typedef struct
{    
    BYTE caption[128];  //说明
    BYTE RepaireType;   //报修类型
    BYTE ErrorType;     //故障类型
    BYTE reserved[6];
}SG_Repaire_t;

/* 深广平台手动上传 -> 维保 */
typedef struct
{    
    BYTE caption[128];  //说明
    BYTE EquipMaintain; //设备维护
    BYTE MaintainRes;   //维修结果
    BYTE reserved[6];
}SG_Maintenance_t;

/* 深广平台手动上传 -> 图片 */
typedef struct
{    
    UINT ChannelMask;   //需上传图片的通道掩码
    BYTE type;          //类型
    BYTE reserved[3];
}SG_PicUpload_t;

/* 深广平台远程参数 -> 手动图片上传 */
typedef struct
{
    UINT StructSize;  //该结构体大小
    BYTE mode;        //维护模式.0:报修; 1:维保; 2:图片
    BYTE reserved[3];
    union
    {
        SG_Repaire_t Repaire;
        SG_Maintenance_t Maintain;
        SG_PicUpload_t PicUpload;
    };
}SGManualUploadReq;

/* 零通道重新编码请求 */
typedef struct
{
    UINT StructSize; //该结构体大小
    BYTE ReqType;    //请求类型, 0-获取零通道状态,1-通道重编码
    BYTE PreviewMode;//预览模式.1--单画面,0--多画面
    BYTE EncodeCh;   //重新编码通道,多画面为200
    BYTE reserved[25];
}ZeroChnStatReq;

/* 远程获取零通道预览状态 */
typedef struct
{
    UINT StructSize; //该结构体大小
    BYTE SplitMode;  //分屏模式,单分屏时双击不重新编码.1--单画面,4--四画面,...
    BYTE PreviewMode;//预览模式.1--单画面,0--多画面
    BYTE reserved[2];
    BYTE ChnList[32];//通道号列表
}ZeroChnStatRsp;

/*添加/删除设备请求*/
typedef struct
{
	UINT devId; //sensor设备号
	BYTE sensorType;  //sensor设备类型
	S8   Sensorname[24]; //sensor设备名
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

//新的导入导出，便于扩充文件大小，原来的为了兼容保留
typedef struct 
{
	int structSize;
	int  paramLen;
	char filename[32];
	char respInfo[384*1024];
}RemoteNewParamBackupResp_t;

typedef struct 
{
	DateTime starTime;//开始时间
	DateTime endTime; //结束时间
	BYTE alarmType;//可能将来用于伴线等告警
	BYTE reportType;//报表类型
	BYTE censusType;//统计类型
	BYTE reserve;
	UINT channel;
}SearchSmartCountReq;

typedef struct
{
	BYTE alarmType;//可能将来用于伴线等告警
	BYTE version;  //0-旧的查询1-新的查询
	BYTE reserve[2];
	UINT channel;
	int  report[32];
	int  reportExt[32]; 
	BYTE filename[32];//heat mapping name
}SearchSmartCountResp;

typedef struct 
{
    UINT StructSize; 	//该结构体大小
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
    UINT Size;          //文件大小
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
	char security[128]; //加密
	int  rssi;			//信号强度
	char pskValue[36];	//Password
}Routpeat_t;

/*swann专用,用于查询带宽使用情况*/
typedef struct
{
    UINT StructSize;
    BYTE reserve[4];
    ULONGLONG TotalBandWidth;   /*总带宽*/
    ULONGLONG UsedBandWidth;    /*已使用带宽*/
}RSNetNew_Streamset_t;

typedef struct
{
	UINT StructSize;
	UINT chn;
	BYTE FloodLightMode; /*白光灯 0:disable 1:enable*/
	BYTE FloodLightValue;/*值范围[1, 100]*/
	BYTE AudioAlarmSwitch;/*喇叭报警0:disable 1:enable*/
	BYTE FlashLight;   /*闪光灯*/
	BYTE LineOutVolume;  /*扬声器音量[1,10]*/
	BYTE FlashFrequency; /*闪光灯频率等级*/
	BYTE isDualtalkWorking;/*是否正在对讲*/
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
	UINT param_size;	// 参数长度
	BYTE resevered[4];
	BYTE AlgName[8];	// 算法名称，例如“ssc”
	BYTE algParam[255*1024];
}RS_ImpLive_t;

/* Dev Info */
typedef struct tagAlgList
{
	int alg_num;		//数组里算法个数
	char resevered[4];
	char alg_list[8][8];	//存储算法名称数组
	int alg_status[8];	//对应的算法状态，1-run,0-stop
}ImpAlgList_t;

/* 算法模式 */
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

/* 算法控制 */
typedef struct
{
	BYTE algName[8];
	BYTE algCtrl;
	BYTE resevered[7];
}ImpControl_t;

/* 银瀑total */
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
    UINT interval;          //图片时间间隔
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
