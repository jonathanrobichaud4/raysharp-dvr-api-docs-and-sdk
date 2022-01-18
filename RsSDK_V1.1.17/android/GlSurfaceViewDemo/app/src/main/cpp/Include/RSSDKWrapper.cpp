#include "RSSDKWrapper.h"
#include "../DeviceManager/RSDevice.h"
#include "../DeviceManager/authority_ability.h"



#include "../Paramers/RSPush.h"
#include "../Paramers/RSPushSubscription.h"
#include "../Paramers/ParamBase.h"
#include "../Paramers/IPCSet.h"
#include "../Paramers/ChLive.h"
#include "../Paramers/AnalogCh.h"
#include "../Paramers/ImgCtrl.h"
#include "../Paramers/VideoCover.h"
#include "../Paramers/RecConfig.h"
#include "../Paramers/RecPlan.h"
#include "../Paramers/EncodeStream.h"
#include "../Paramers/CaptureSet.h"
#include "../Paramers/CaptureJh.h"
#include "../Paramers/NetBase.h"
#include "../Paramers/NetEmail.h"
#include "../Paramers/NewNetEmail.h"
#include "../Paramers/EmailPlan.h"
#include "../Paramers/NetDNS.h"
#include "../Paramers/RTSP.h"
#include "../Paramers/FTP.h"
#include "../Paramers/AlarmMotion.h"
#include "../Paramers/AlarmIO.h"
#include "../Paramers/SysInfHdd.h"
#include "../Paramers/SysParamPTZ.h"
#include "../Paramers/NormalCloSto.h"
#include "../Paramers/SysParamDst.h"
#include "../Paramers/SysParamUSer.h"
#include "../Paramers/SysInfBase.h"
#include "../Paramers/ChnInfo.h"
#include "../Paramers/RecInfo.h"
#include "../Paramers/Defaultparam.h"
#include "../Paramers/AlarmAbnormity.h"
#include "../Paramers/SysMaintain.h"
#include "../Paramers/Devlog.h"
#include "../Paramers/ProManage.h"
#include "../Paramers/IntelligentPlan.h"
#include "../Paramers/PerimeterZone.h"
#include "../Paramers/PerimeterLine.h"
#include "../Paramers/GoodsLostLegacy.h"
#include "../Paramers/ShowIntell.h"
#include "../Paramers/VideoSet.h"
#include "../Paramers/HumanDetection.h"
#include "../Paramers/FaceDetection.h"
#include "../Paramers/PeopleCrossCounting.h"
#include "../Paramers/SwannCloSto.h"
#include "../Paramers/NetFilter.h"
#include "../Paramers/ALTEReport.h"
#include "../Paramers/AlarmPtz.h"
#include "../Paramers/LiveParam.h"
#include "../Paramers/AlarmNewIO.h"
#include "../Paramers/FloodLight.h"
#include "../Paramers/VideoOutput.h"
#include "../Paramers/ZeroChannel.h"
#include "../Paramers/SoundAlarm.h"
#include "../Paramers/SNMP.h"
#include "../Paramers/SXHTTPS.h"
#include "../Paramers/SystemID.h"
#include "../Paramers/Voicectrl.h"
#include "../Paramers/LensShade.h"
#include "../Paramers/VideoRoi.h"
#include "../Paramers/IPFilter.h"
#include "../Paramers/RecPlanIPC.h"
#include "../Paramers/AlarmPIR.h"
#include "../Paramers/Voicectrl.h"
#include "../Paramers/Alarmblock.h"
#include "../Paramers/LensShade.h"
#include "../Paramers/VideoRoi.h"
#include "../Paramers/IPFilter.h"
#include "../Paramers/PlatformSet.h"
#include "../Paramers/NormalCloStoEm.h"
#include "../Paramers/RecPlanIPC.h"
#include "../Paramers/RecPlanSmart.h"
#include "../Paramers/FishEye.h"
#include "../Paramers/EPlatform.h"
#include "../Paramers/SwannWifi.h"
#include "../Paramers/GB28181.h"
#include "../Paramers/SwitchSet.h"
#include "../Paramers/AlarmPIR.h"
#include "../Paramers/IntrusionDetection.h"
#include "../Paramers/RedMantleDetection.h"
#include "../Paramers/UserAF.h"
#include "../Paramers/TypeMeterRecognition.h"
#include "../Paramers/IntelligentNewUser.h"
#include "../Paramers/AutoUpgrade.h"
#include "../Paramers/FtpPlan.h"
#include "../Paramers/GetSetParam.h"
#include "../Paramers/XinQiaoFD.h"
#include "../Paramers/SysParamSerial.h"
#include "../Paramers/IEEEX.h"
#include "../Paramers/SSL.h"
#include "../Paramers/SendCertificate.h"
#include "../Paramers/AlarmPlan.h"
#include "../Paramers/ZeroChannel.h"
#include "../Paramers/IOAlarmManage.h"
#include "../Paramers/HttpSet.h"
#include "../Paramers/PtzSchedule.h"
#include "../Paramers/NetVPN.h"
#include "../Paramers/IPFilterList.h"
#include "../Paramers/EncodeStream.h"
#include "../Paramers/SysInfBase.h"
#include "../Paramers/JsonPage.h"
#include "../Paramers/DropboxParam.h"

log_sink_callback global_bugly_callback = NULL;

static bool s_global_param_page_init = false;
static std::map<int, CParamBase*> s_global_param_page;
void init_global_param_page() {
    if (s_global_param_page_init)
        return;
    
    s_global_param_page.insert(std::make_pair(MsgParamModifyLiving, new ChLive));
    s_global_param_page.insert(std::make_pair(MsgParamPushInfo, new RSPush));
    s_global_param_page.insert(std::make_pair(MsgParamGeneral, new SysParamDst));
    s_global_param_page.insert(std::make_pair(MsgParamPir, new AlarmPIR));
    s_global_param_page.insert(std::make_pair(MsgParamPreviewCtrl, new LiveParam));
    s_global_param_page.insert(std::make_pair(MsgFloodLightParam, new FloodLight));
    s_global_param_page.insert(std::make_pair(MsgParamVVPush, new RSPushSubscription));
    s_global_param_page.insert(std::make_pair(MsgParamModifyMainStream, new MainEncode));
    s_global_param_page.insert(std::make_pair(MsgParamModifyAlarmStream, new AlarmEncode));
    s_global_param_page.insert(std::make_pair(MsgParamModifySubStream, new SubEncode));
    s_global_param_page.insert(std::make_pair(MsgParamModifyMobileStream, new MobileEncode));
    s_global_param_page.insert(std::make_pair(MsgParamIpc, new IPCSet));
    s_global_param_page.insert(std::make_pair(MsgParamMotion, new AlarmMotion));
    s_global_param_page.insert(std::make_pair(MsgParamIOAlarm, new AlarmIO));
    s_global_param_page.insert(std::make_pair(MsgParamNetworkBase, new NetBase));
    s_global_param_page.insert(std::make_pair(MsgParamHdd, new SysInfHdd));
    s_global_param_page.insert(std::make_pair(MsgParamSystemBase, new CSysInfBase));
    s_global_param_page.insert(std::make_pair(MsgParamSchedule, new RecPlan));
    s_global_param_page.insert(std::make_pair(MsgParamScheduleIPC, new RecPlanIPC));
    s_global_param_page.insert(std::make_pair(MsgJsonTypeMsg, new JsonPage));
    s_global_param_page.insert(std::make_pair(MsgParamUser, new SysParamUSer));
    s_global_param_page.insert(std::make_pair(MsgNewIOAlarm, new AlarmNewIO));
    s_global_param_page.insert(std::make_pair(MsgParamNewEmail, new NewNetEmail));
    s_global_param_page.insert(std::make_pair(MsgParamNewCloudestorage, new SwannCloSto));
    s_global_param_page.insert(std::make_pair(MsgdropboxParam, new DropBoxParam));
    
#ifdef EXPORT_SDKWRAPPER_AS_DLL
    s_global_param_page.insert(std::make_pair(MsgParamIntHD, new HumanDetection));
    s_global_param_page.insert(std::make_pair(MsgParamIntFD, new FaceDetection));
    s_global_param_page.insert(std::make_pair(MsgParamIntPCC, new PeopleCrossCounting));
    s_global_param_page.insert(std::make_pair(MsgParamAnalogCam, new AnalogCh));
    s_global_param_page.insert(std::make_pair(MsgParamIPCImageSet, new ImgCtrl));
    s_global_param_page.insert(std::make_pair(MsgParamVideoCover, new VideoCover));
    s_global_param_page.insert(std::make_pair(MsgParamRecord, new RecConfig));
    s_global_param_page.insert(std::make_pair(MsgParamSchedule, new RecPlan));
    s_global_param_page.insert(std::make_pair(MsgParamModifyMainStream, new MainEncode));
    s_global_param_page.insert(std::make_pair(MsgParamModifyAlarmStream, new AlarmEncode));
    s_global_param_page.insert(std::make_pair(MsgParamModifySubStream, new SubEncode));
    s_global_param_page.insert(std::make_pair(MsgParamModifyMobileStream, new MobileEncode));
    s_global_param_page.insert(std::make_pair(MsgParamCaptureSet, new CaptureSet));
    s_global_param_page.insert(std::make_pair(MsgParamCapSchedule, new CaptureJh));
    s_global_param_page.insert(std::make_pair(MsgParamNetworkBase, new NetBase));
    s_global_param_page.insert(std::make_pair(MsgParamEmail, new NetEmail));
    s_global_param_page.insert(std::make_pair(MsgParamNewEmail, new NewNetEmail));
    s_global_param_page.insert(std::make_pair(MsgParamModifyEmailSchedule, new EmailPlan));
    s_global_param_page.insert(std::make_pair(MsgParamDDNS, new NetDNS));
    s_global_param_page.insert(std::make_pair(MsgParamRtsp, new RTSP));
    s_global_param_page.insert(std::make_pair(MsgParamFtp, new FTP));
    s_global_param_page.insert(std::make_pair(MsgParamMotion, new AlarmMotion));
    s_global_param_page.insert(std::make_pair(MsgParamIOAlarm, new AlarmIO));
    s_global_param_page.insert(std::make_pair(MsgParamHdd, new SysInfHdd));
    s_global_param_page.insert(std::make_pair(MsgParamPtz, new SysParamPTZ));
    s_global_param_page.insert(std::make_pair(MsgParamCloudStorageInfo, new NormalCloSto));
    s_global_param_page.insert(std::make_pair(MsgParamGeneral, new SysParamDst));
    s_global_param_page.insert(std::make_pair(MsgParamUser, new SysParamUSer));
    s_global_param_page.insert(std::make_pair(MsgParamSystemBase, new CSysInfBase));
    s_global_param_page.insert(std::make_pair(MsgParamRecInfo, new RecInfo));
    s_global_param_page.insert(std::make_pair(MsgParamChnInfo, new ChnInfo));
    s_global_param_page.insert(std::make_pair(MsgParamDefault, new Defaultparam));
    s_global_param_page.insert(std::make_pair(MsgParamAbnormal, new AlarmAbnormity));
    s_global_param_page.insert(std::make_pair(MsgParamMaintain, new CSysMaintain));
    s_global_param_page.insert(std::make_pair(MsgParamDevLog, new Devlog));
    s_global_param_page.insert(std::make_pair(MsgParamCustomProtocol, new ProManage));
    s_global_param_page.insert(std::make_pair(MsgParamIntelligent, new IntelligentPlan));
    s_global_param_page.insert(std::make_pair(MsgParamPerimeter, new PerimeterZone));
    s_global_param_page.insert(std::make_pair(MsgParamPerimeterLine, new PerimeterLine));
    s_global_param_page.insert(std::make_pair(MsgParamGoodsLostLegacy, new GoodsLostLegacy));
    s_global_param_page.insert(std::make_pair(MsgParamIntManage, new ShowIntell));
    s_global_param_page.insert(std::make_pair(MsgParamColor, new VideoSet));
    s_global_param_page.insert(std::make_pair(MsgParamNewCloudestorage, new SwannCloSto));
    s_global_param_page.insert(std::make_pair(MsgParamNetFilter, new NetFilter));
    s_global_param_page.insert(std::make_pair(MsgParamALTEReport, new ALTEReport));
    s_global_param_page.insert(std::make_pair(MsgParamAlarmLinkagePTZ, new AlarmPtz));
    s_global_param_page.insert(std::make_pair(MsgParamPir, new AlarmPIR));
    s_global_param_page.insert(std::make_pair(MsgParamPreviewCtrl, new LiveParam));
    s_global_param_page.insert(std::make_pair(MsgFloodLightParam, new FloodLight));
    s_global_param_page.insert(std::make_pair(MsgParamOutPut, new VideoOutput));
    s_global_param_page.insert(std::make_pair(MsgParamZeroChn, new ZeroChannel));
    s_global_param_page.insert(std::make_pair(MsgParamSnmp, new SNMP));
    s_global_param_page.insert(std::make_pair(MsgHttpsFileParam, new SXHTTPS));
    s_global_param_page.insert(std::make_pair(MsgParamSystemIDCtrl, new CSystemID));
    s_global_param_page.insert(std::make_pair(MsgParamVoice, new VoiceCtrl));
    s_global_param_page.insert(std::make_pair(MsgParamOD, new LensShade));
    s_global_param_page.insert(std::make_pair(MsgParamIPCROI, new VideoRoi));
    s_global_param_page.insert(std::make_pair(MsgParamIPFilter, new IPFilter));
    s_global_param_page.insert(std::make_pair(MsgParamScheduleIPC, new RecPlanIPC));
    s_global_param_page.insert(std::make_pair(MsgParamVoice, new VoiceCtrl));
    s_global_param_page.insert(std::make_pair(MsgParamIDSet, new AlarmBlock));
    s_global_param_page.insert(std::make_pair(MsgParamOD, new LensShade));
    s_global_param_page.insert(std::make_pair(MsgParamIPCROI, new VideoRoi));
    s_global_param_page.insert(std::make_pair(MsgParamIPFilter, new IPFilter));
    s_global_param_page.insert(std::make_pair(MsgParamPlatform, new PlatformSet));
    s_global_param_page.insert(std::make_pair(MsgParamCloudStorageEmail, new NormalCloStoEm));
    s_global_param_page.insert(std::make_pair(MsgParamScheduleIPC, new RecPlanIPC));
    s_global_param_page.insert(std::make_pair(MsgParamIntelliRec, new RecPlanSmart));
    s_global_param_page.insert(std::make_pair(MsgParamFishEye, new FishEye));
    s_global_param_page.insert(std::make_pair(MsgParamElectricityGrid, new EPlatform));
    s_global_param_page.insert(std::make_pair(MsgParamSwannWifi, new SwannWifi));
    s_global_param_page.insert(std::make_pair(MsgParamGB28181, new GB28181));
    s_global_param_page.insert(std::make_pair(MsgParamSwitch, new SwitchSet));
    s_global_param_page.insert(std::make_pair(MsgParamJDVCAIntrusionDetection, new IntrusionDetection));
    s_global_param_page.insert(std::make_pair(MsgParamJDVCARedMantleDetection, new RedMantleDetection));
    s_global_param_page.insert(std::make_pair(MsgParamIPCCameaFocusInfo, new UserAF));
    s_global_param_page.insert(std::make_pair(MsgParamJDVCAMeterRecongition, new TypeMeterRecognition));
    s_global_param_page.insert(std::make_pair(MsgParamXINQIAOFaceDetection, new XinQiaoFD));
    s_global_param_page.insert(std::make_pair(MsgParamIeee8021xParam, new IEEEX));
    s_global_param_page.insert(std::make_pair(MsgParamHttps, new SSL));
    s_global_param_page.insert(std::make_pair(MsgParamCertificates, new SendCertificate));
    s_global_param_page.insert(std::make_pair(MsgHGIntParam, new IntelligentNewUser));
    s_global_param_page.insert(std::make_pair(MsgParamSerial, new SysParamSerial));
    s_global_param_page.insert(std::make_pair(MsgParamAlarmOutScheduleset, new AlarmPlan));
    s_global_param_page.insert(std::make_pair(MsgParamFtpAutoUpgrade, new AutoUpgrade));
    //s_global_param_page.insert(std::make_pair(MsgParamExportIPC, new CGetSetParam));
    s_global_param_page.insert(std::make_pair(MsgParamIOAlarmManage, new IOAlarmManage));
    s_global_param_page.insert(std::make_pair(MsgParamUrmetHttp, new HttpSet));
    s_global_param_page.insert(std::make_pair(MsgSoundAlarmParam, new SoundAlarm));
    s_global_param_page.insert(std::make_pair(MsgNewIpFilterParam, new IPFilterList));
#endif
    
    s_global_param_page_init = true;
}



RSSDKWRAPPER_API rs_error_code rs_sdk_wrapper_init(const char* param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return rs_parse_json_error;

    std::string lorex_p2p_directory = value["lorex p2p directory"].asString();
    if (!lorex_p2p_directory.empty()) {
        RSNetInitLX2PPath(lorex_p2p_directory.c_str());
    }

    if (!value["max hardware decode num"].isNull()) {
        int num = value["max hardware decode num"].asInt();
        RSPlaySetMaxHardwareDecodeNumber(num);
    }

    RSNetP2PServerInfo info = {0};
    std::string vv_main_server_addr = value["vv main server addr"].asString();
    int vv_main_server_port = value["vv main server port"].asInt();
    if (!vv_main_server_addr.empty() && vv_main_server_port) {
        memcpy(info.main_vv_server_addr, vv_main_server_addr.c_str(), vv_main_server_addr.length());
        info.main_vv_server_port = vv_main_server_port;

        std::string vv_sub_server_addr = value["vv sub server addr"].asString();
        int vv_sub_server_port = value["vv sub server port"].asInt();
        if (!vv_sub_server_addr.empty() && vv_sub_server_port) {
            memcpy(info.sub_vv_server_addr, vv_sub_server_addr.c_str(), vv_sub_server_addr.length());
            info.sub_vv_server_port = vv_sub_server_port;
        }

        RSNetInitP2PServerInfo(&info);
    }
    return rs_success;
}

RSSDKWRAPPER_API rs_error_code rs_sdk_wrapper_uninit(const char* param) {
    std::map<int, CParamBase*>::iterator itor = s_global_param_page.begin();
    while (itor != s_global_param_page.end()) {
        delete itor->second;
        ++itor;
    }
    return rs_success;
}

RSSDKWRAPPER_API rs_error_code rs_init_log(const char* param) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return rs_parse_json_error;
    
    std::string log_directory = value["directory"].asString();
    int max_size = value["max size"].asInt();
    bool enable_p2p_log = value["enable p2p log"].asBool();
    
    {
        RSNetLogParam log_param = {0};
        std::string temp_path = log_directory + "/RSNetLog.txt";
        memcpy(log_param.log_path, temp_path.c_str(), sizeof(log_param.log_path)-1);
        log_param.log_directory = log_directory.c_str();
        if (max_size) {
            FILE* file = fopen(log_param.log_path, "r");
            if (file) {
                fseek(file, 0, SEEK_END);
                long log_file_size = ftell(file);
                fclose(file);
                
                if (log_file_size > max_size)
                    remove(log_param.log_path);
            }
        }
        log_param.gEnableP2PStatus = enable_p2p_log;
        RSNetInitLog(&log_param);
    }
    
    return rs_success;
}

RSSDKWRAPPER_API rs_error_code rs_init_log_ex(const init_log_ex_param* param)
{
    rs_error_code result = rs_fail;
    if (param) {
        if (param->param)
            result = rs_init_log(param->param);
        global_bugly_callback = param->bugly_callback;
    }
    return result;
}

RSSDKWRAPPER_API rs_error_code rs_search_device(const char* param, search_device_callback callback, void* user_param) {
    return CRSDevice::search_device(param, callback, user_param);
}

RSSDKWRAPPER_API rs_error_code rs_modify_device(const char* param) {
    return CRSDevice::modify_device(param);
}

RSSDKWRAPPER_API device_id rs_create_device() {
    CRSDevice* device = new CRSDevice;
    return CRSDevice::add_device(device);
}

RSSDKWRAPPER_API rs_error_code rs_destroy_device(device_id dev) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device)
        delete device;
    return rs_success;
}

RSSDKWRAPPER_API rs_error_code rs_device_login(device_id dev, const char* param, connction_callback conn_cb, alarm_callback alarm_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        device_login_param info = {0};
        info.dev = dev;
        info.param = param;
        info.conn_cb = conn_cb;
        info.alarm_cb = alarm_cb;
        info.user_param = user_param;
        return device->login(&info);
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_device_login_ex(const device_login_param* param) {
    CRSDevice* device = CRSDevice::get_device(param->dev);
    if (device)
        return device->login(param);
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_device_logout(device_id dev) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device)
        return device->logout();
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_get_login_rsp(device_id dev, char* buf, int length) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        std::string result = device->get_login_rsp();
        int result_length = (int)result.length();
        if (!result.empty() && result_length < length) {
            memcpy(buf, result.c_str(), result_length);
            buf[result_length] = '\0';
            return rs_success;
        }
        return rs_buffer_too_small;
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API int rs_get_device_type(device_id dev) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return device->GetDeviceType();
    }
    return -1;
}

RSSDKWRAPPER_API int rs_get_channel_number(device_id dev) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return device->GetChannelNum();
    }
    return -1;
}

RSSDKWRAPPER_API int rs_get_analogy_channel_number(device_id dev) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return device->GetAnalogChNum();
    }
    return -1;
}

RSSDKWRAPPER_API bool rs_has_authority(device_id dev, const char* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return has_authority(device, param);
    }
    return false;
}

RSSDKWRAPPER_API bool rs_has_ability(device_id dev, const char* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return has_ability(device, param);
    }
    return false;
}

RSSDKWRAPPER_API session_id rs_start_preview(const preview_param* param) {
    CRSDevice* device = CRSDevice::get_device(param->dev);
    if (device) {
        session_id sess = device->start_preview(param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_preview(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_preview(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API void* rs_get_decoded_frame(session_id sess, bool* find_preview_session) {
    *find_preview_session = true;
    base_instance* instance = (base_instance*)sess;
    if (instance) {
        CRSDevice* device = (CRSDevice*)instance->get_device();
        if (device && device->is_session_exist(sess)) {
            return instance->get_decoded_frame();
        } else if (!device) {
            return instance->get_decoded_frame();
        }
    }
    *find_preview_session = false;
    return NULL;
}

RSSDKWRAPPER_API session_id rs_search_record_by_month(device_id dev, const char* param, search_record_month_callback month_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->search_record_by_month(param, month_cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API session_id rs_search_record_by_day(device_id dev, const char* param, search_record_day_callback day_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->search_record_by_day(param, day_cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_search_record(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_search_record(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_start_download_by_file(device_id dev, const char* param, download_callback download_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->start_download_by_file(param, download_cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API session_id rs_start_download_by_time(device_id dev, const char* param, download_callback download_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->start_download_by_time(param, download_cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_download(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_download(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_start_local_playback(const local_playback_param* param) {
    session_id sess = CRSDevice::start_local_playback(param);
    return sess;
}

RSSDKWRAPPER_API session_id rs_start_remote_playback(const remote_playback_param* param) {
    CRSDevice* device = CRSDevice::get_device(param->dev);
    if (device) {
        session_id sess = device->start_remote_playback(param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API session_id rs_start_sync_playback(const sync_playback_param* param) {
    session_id sess = CRSDevice::start_sync_playback(param);
    return sess;
}

RSSDKWRAPPER_API rs_error_code rs_stop_playback(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_playback(sess);
        else
            return CRSDevice::stop_local_playback(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_open_sound(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->open_sound();
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_close_sound(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->close_sound();
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_volume(session_id sess, int volume) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_volume(volume);
    return rs_session_not_found;
}

RSSDKWRAPPER_API int rs_get_volume(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->get_volume();
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_mute_on(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_mute_on();
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_mute_off(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_mute_off();
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_start_record(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->start_record(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_stop_record(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->stop_record();
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_capture_picture_from_device(device_id dev, const char* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device)
        return device->capture_picture_from_device(param);
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_capture_picture(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->capture_picture(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_capture_picture_to_buf(session_id sess, capture_picture_buf_param* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->capture_picture_to_buf(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_get_file_time(const char* file_name, char* buf, int length) {
    RSPlayHandle play_handle_ = RSPlayCreatePlayInstance(PLAY_LOCALFILE_TYPE);
    if (play_handle_) {
        int result = RSPlayOpenPlayFile(play_handle_, file_name);
        switch (result)
        {
            case 0:
            {
                ULONGLONG begin_time = 0;
                ULONGLONG end_time = 0;
                RSPlayGetPlayFileTimeRange(play_handle_, &begin_time, &end_time);
                RSPlayClosePlayFile(play_handle_);
                RSPlayDestroyPlayInstance(play_handle_);
                
                Json::Value value;
                {
                    char temp_buf[32] = {0};
                    ULONGLONG temp = begin_time + 500000;
                    time_t now = (time_t)(temp / 1000000);
                    struct tm gmtTime;
#ifdef _MSC_VER
                    gmtime_s(&gmtTime, &now);
                    sprintf_s(temp_buf, _countof(temp_buf), "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                              gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
#else
                    gmtime_r(&now, &gmtTime);
                    sprintf(temp_buf, "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                            gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
#endif
                    value["begin time"] = temp_buf;
                }
                
                {
                    char temp_buf[32] = {0};
                    ULONGLONG temp = end_time + 500000;
                    time_t now = (time_t)(temp / 1000000);
                    struct tm gmtTime;
#ifdef _MSC_VER
                    gmtime_s(&gmtTime, &now);
                    sprintf_s(temp_buf, _countof(temp_buf), "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                              gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
#else
                    gmtime_r(&now, &gmtTime);
                    sprintf(temp_buf, "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                            gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
#endif
                    value["end time"] = temp_buf;
                }
                
                {
                    Json::UInt64 temp_begin_time = (begin_time + 500)/1000;
                    Json::UInt64 temp_end_time = (end_time + 500)/1000;

                    value["begin time millisecond"] = temp_begin_time;
                    value["end time millisecond"] = temp_end_time;
                }
                
                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);
                int result_length = (int)result.length();
                if (!result.empty() && result_length < length) {
                    memcpy(buf, result.c_str(), result_length);
                    buf[result_length] = '\0';
                    return rs_success;
                }
                return rs_buffer_too_small;
            }
                break;
            case -2:
                return rs_file_not_found;
                break;
            case -3:
                return rs_file_access_error;
                break;
            case -4:
                return rs_need_input_password;
                break;
            case -5:
                return rs_hk_mp4_file;
                break;
            case -6:
                return rs_unknown_mp4_file;
                break;
            default:
                return rs_unknown_error;
                break;
        }
    }
    return rs_fail;
}

RSSDKWRAPPER_API rs_error_code rs_get_current_time(session_id sess, char* buf, int length) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->get_current_time(buf, length);
    return rs_session_not_found;
}

RSSDKWRAPPER_API ULONGLONG rs_get_current_time_millisecond(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->get_current_time_millisecond();
    return 0;
}

RSSDKWRAPPER_API rs_error_code rs_seek_by_time(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->seek_by_time(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API int rs_get_file_key_frame_count(const char* file_name) {
    int key_frame_count = 0;
    RSPlayHandle play_handle_ = RSPlayCreatePlayInstance(PLAY_LOCALFILE_TYPE);
    if (play_handle_ && (RSPlayOpenPlayFile(play_handle_, file_name) == 0)) {
        key_frame_count = RSPlayGetKeyFrameCount(play_handle_);
        RSPlayClosePlayFile(play_handle_);
        RSPlayDestroyPlayInstance(play_handle_);
    }
    return key_frame_count;
}

RSSDKWRAPPER_API rs_error_code rs_seek_by_key_frame_index(session_id sess, int key_frame_index) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->seek_by_key_frame_index(key_frame_index);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_switch_stream_type(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->switch_stream_type(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_play_mode(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_play_mode(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_video_proportion(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_video_proportion(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_fishsye_mode(session_id sess, FISHEYE_COMB_TYPE_E type) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_fishsye_mode(type);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_fisheye_mouse_control(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->fisheye_mouse_control(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_fisheye_ptz_control(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->fisheye_ptz_control(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API bool rs_window_in_zoom_status(session_id sess) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->window_in_zoom_status();
    return false;
}

RSSDKWRAPPER_API rs_error_code rs_query_param(device_id dev, const char* param, char* buf, int length) {
    init_global_param_page();
    
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        int message = 0;
        int subType = 0;
        std::string strData;
        {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;
            message = value["message"].asInt();
            subType = value["type"].asInt();
            strData = value["data"].asString();
        }
        
        std::map<int, CParamBase*>::iterator itor = s_global_param_page.find(message);
        if (itor == s_global_param_page.end())
            return rs_param_page_not_found;
        
        std::string strRst = "err";
        CParamBase* pbase = itor->second;
        pbase->m_pDevice = device;
        
        if (subType == QUERY_ALL)//1000，查询所有通道
            strRst = pbase->QueryAll(false);
        else if(subType == QUERY_ALL_WITHDATA)//查询所有通道，带条件的查询(DevLog页面)
            strRst = pbase->QueryAll(strData);
        else if(subType == QUERY_ALL_DEFAULT)//1200，查询所有通道，获取默认数据
            strRst = pbase->QueryAll(true);
        else if(subType == QUERY_ALL2)//1100，查询所有通道，1个页面有两个刷新(IPC页面)
            strRst = pbase->QueryAll2();
        else if(subType == GET_ALL)//1300，获取所有通道。把保存在插件里的数据，传给网页
            strRst = pbase->GetAll();
        else if(subType>=300 && subType<300+MAX_CHANNEL)//300-555，获取单个通道数据。把保存在插件里的数据，传给网页
            strRst = pbase->GetOne(subType);
        else if(subType>=0 && subType<MAX_CHANNEL)//0-255，查询单个通道数据
            strRst = pbase->QueryOne(subType);
        
        if (strRst == "err")
            return rs_fail;
        
        int result_length = (int)strRst.length();
        if (!strRst.empty() && result_length < length) {
            memcpy(buf, strRst.c_str(), result_length);
            buf[result_length] = '\0';
            return rs_success;
        }
        return rs_buffer_too_small;
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_param(device_id dev, const char* param, const char* buf) {
    init_global_param_page();
    
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        int message = 0;
        int subType = 0;
        {
            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, param, &value, &err))
                return rs_parse_json_error;
            message = value["message"].asInt();
            subType = value["type"].asInt();
        }
        
        std::map<int, CParamBase*>::iterator itor = s_global_param_page.find(message);
        if (itor == s_global_param_page.end())
            return rs_param_page_not_found;
        
        int iResult = 0;
        CParamBase* pbase = itor->second;
        pbase->m_pDevice = device;
        
        if(subType == SAVE_ALL)//保存所有通道数据
            iResult = pbase->SaveAll(buf);
        else if(subType == MODIFY_PSW)
            iResult = pbase->ModifyPassword(buf);
        else if(subType>=0 && subType<MAX_CHANNEL)//保存单个通道数据
            iResult = pbase->SaveOne(subType,buf);
        
        if (iResult == 1)
            return rs_success;
        else if (iResult == 2)
            return rs_no_permission;
        else
            return rs_fail;
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_ptz_control(device_id dev, const char* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device)
        return device->ptz_operation(param);
    return rs_device_not_found;
}

RSSDKWRAPPER_API session_id rs_start_talk_to_device(device_id dev, const char* param, talk_callback talk_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->start_talk(param, talk_cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API session_id rs_start_talk_to_channel(device_id dev, const char* param, talk_callback talk_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->start_talk(param, talk_cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_talk(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_talk(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_start_convert_file(const char* param, convert_callback convert_cb, void* user_param) {
    return CRSDevice::start_convert_file(param, convert_cb, user_param);
}

RSSDKWRAPPER_API rs_error_code rs_stop_convert_file(session_id sess) {
    return CRSDevice::stop_convert_file(sess);
}

RSSDKWRAPPER_API rs_error_code rs_remote_test(device_id dev, unsigned int msg_type, const char* param, remote_test_callback remote_test_cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return device->remote_test(msg_type, param, remote_test_cb, user_param);
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API session_id rs_start_playback_thumbnails(device_id dev, const char* param, playback_thumbnails_callback cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->start_playback_thumbnails(param, cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_playback_thumbnails(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_playback_thumbnails(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_start_local_playback_thumbnails(const char* param, local_playback_thumbnails_callback cb, void* user_param) {
    return CRSDevice::start_local_playback_thumbnails(param, cb, user_param);
}

RSSDKWRAPPER_API rs_error_code rs_input_local_playback_time(session_id sess, ULONGLONG millisecond) {
    return CRSDevice::input_local_playback_time(sess, millisecond);
}

RSSDKWRAPPER_API rs_error_code rs_stop_local_playback_thumbnails(session_id sess) {
    return CRSDevice::stop_local_playback_thumbnails(sess);
    
}

RSSDKWRAPPER_API rs_error_code rs_destroy_p2p_resource_enter_background() {
    RSNetP2PEnterBackgroundDestroy();
    return rs_success;
}

RSSDKWRAPPER_API session_id rs_start_human_face_alarm_report(const human_face_alarm_report_param* param) {
    CRSDevice* device = CRSDevice::get_device(param->dev);
    if (device) {
        session_id sess = device->start_human_face_alarm_report(param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_human_face_alarm_report(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_human_face_alarm_report(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_start_human_face_param(const human_face_param* param) {
    CRSDevice* device = CRSDevice::get_device(param->dev);
    if (device) {
        session_id sess = device->start_human_face_param(param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_send_human_face_param(session_id sess, const char* param, int param_size) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->send_human_face_param(param, param_size);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_stop_human_face_param(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_human_face_param(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_reset_connection(device_id dev) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        device->reset_connection();
        return rs_success;
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_send_simple_command(device_id dev, const simple_command_param* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        device->send_simple_command(param);
        return rs_success;
    }
    return rs_device_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_set_color(session_id sess, const rs_color* color_value) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->set_color(color_value);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_draw_line(session_id sess, const rs_rect* line_value, int line_count) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->draw_line(line_value, line_count);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_draw_rect(session_id sess, const rs_rect* rect_value, int rect_count) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->draw_rect(rect_value, rect_count);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_draw_solid_rect(session_id sess, const rs_rect* rect_value, int rect_count, float transparency) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->draw_solid_rect(rect_value, rect_count, transparency);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_draw_hollow_circle(session_id sess, const rs_rect* rect_value, int rect_count) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->draw_hollow_circle(rect_value, rect_count);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_draw_text(session_id sess, const char* text_value, const rs_rect* rect_value) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->draw_text(text_value, rect_value);
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_upload_picture_from_memory(session_id sess, const char* data, int size) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->upload_picture_from_memory(data, size);
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_delete_picture(session_id sess, session_id picture_sess_id) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->delete_picture(picture_sess_id);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_draw_picture(session_id sess, session_id picture_sess_id, const rs_rect* rect_value, float transparency) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->draw_picture(picture_sess_id, rect_value, transparency);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_get_frame_width_and_height(session_id sess, int* width, int* height) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->get_frame_width_and_height(width, height);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_adjust_render_frame_rect(session_id sess, const rs_rect* rect_value) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->adjust_render_frame_rect(rect_value);
    return rs_session_not_found;
}

RSSDKWRAPPER_API session_id rs_start_upgrade(device_id dev, const char* param, upgrade_callback cb, void* user_param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        session_id sess = device->start_upgrade(param, cb, user_param);
        return sess;
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_upgrade(session_id sess) {
    if (sess) {
        CRSDevice* device = (CRSDevice*)((base_instance*)sess)->get_device();
        if (device)
            return device->stop_upgrade(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_sync_playback_add_session(session_id sync_sess, session_id sess) {
    return CRSDevice::sync_playback_add_session(sync_sess, sess);
}

RSSDKWRAPPER_API rs_error_code rs_sync_playback_del_session(session_id sync_sess, session_id sess) {
    return CRSDevice::sync_playback_del_session(sync_sess, sess);
}

RSSDKWRAPPER_API session_id rs_start_async_query_json(device_id dev, const async_query_json_param* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return device->start_async_query_json(param);
    }
    return NULL;
}

RSSDKWRAPPER_API session_id rs_start_async_set_json(device_id dev, const async_set_json_param* param) {
    CRSDevice* device = CRSDevice::get_device(dev);
    if (device) {
        return device->start_async_set_json(param);
    }
    return NULL;
}

RSSDKWRAPPER_API rs_error_code rs_stop_async_json(device_id dev, session_id sess) {
    if (sess) {
        CRSDevice* device = CRSDevice::get_device(dev);
        if (device)
            return device->stop_async_json(sess);
    }
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_manual_switch_record(session_id sess, const char* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->manual_switch_record(param);
    return rs_session_not_found;
}

RSSDKWRAPPER_API rs_error_code rs_stop_record_ex(session_id sess, record_ex_param* param) {
    base_instance* instance = (base_instance*)sess;
    if (instance)
        return instance->stop_record(param);
    return rs_session_not_found;
}
