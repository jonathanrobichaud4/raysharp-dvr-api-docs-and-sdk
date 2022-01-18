#pragma once
#include <algorithm>

class search_modify {
public:
    search_modify()  {}
    ~search_modify() {}

    static BOOL RSNET_CALL RSNetSearchDevCallbackFun(const SearchDevRsp* dev, void* userParam) {
        SEARCH_DEVICE_INFO* info = (SEARCH_DEVICE_INFO*)(userParam);
        if (info && info->callback) {
            search_device_callback& callback = info->callback;
            if (dev) {
                Json::Value value;
                value.clear();
                value["ip"] = dev->IP;
                value["netmask"] = dev->NetMask;
                value["gateway"] = dev->GateWay;
                value["dns1"] = dev->DNS1;
                value["dns2"] = dev->DNS2;
                value["media port"] = dev->Port;
                value["web port"] = dev->IEPort;
                switch (dev->NetworkMode)
                {
                case 0:
                    value["network mode"] = "dhcp";
                    break;
                case 1:
                    value["network mode"] = "pppoe";
                    break;
                case 2:
                    value["network mode"] = "static";
                    break;
                default:
                    value["network mode"] = "unknown";
                    break;
                }
                Json::UInt64 temp_DevTypeULL = dev->DevTypeULL;
                value["device type"] = dev->DevType;
                value["device type ull"] = temp_DevTypeULL;
                value["device version"] = dev->DevVer;
                value["device name"] = dev->DeviceName;
                value["mac addr"] = dev->MacAddr;
                value["channel number"] = dev->ChannelNum;
                char first_char = dev->P2pID[0];
                if ((first_char > 47 && first_char < 58) || \
                    (first_char > 64 && first_char < 91) || \
                    (first_char > 96 && first_char < 123))
                    value["p2p id"] = dev->P2pID;
                else
                    value["p2p id"] = "";

                Json::StreamWriterBuilder writer;
                std::string result = Json::writeString(writer, value);
                callback(result.c_str(), info->user_param);
            }else{
                callback(NULL, info->user_param);
                delete info;
            }
        }
        return TRUE;
    }

    static rs_error_code search_device(const char* param, search_device_callback callback, void* user_param) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)){
            sdk_wrapper_log("[:] call <searh_device> error:rs_parse_json_error\n");
            return rs_parse_json_error;
        }

        uint8_t type = 0;
        std::string oem_type = value["oem type"].asString();
        if (oem_type == "default")
            type = 0;
        else if (oem_type == "tev")
            type = 1;
        else if (oem_type == "zip")
            type = 2;
        else if (oem_type == "cdoubles")
            type = 3;
        else if (oem_type == "raydin")
            type = 4;
        else if (oem_type == "hello cctv")
            type = 0;
        else if (oem_type == "optimus")
            type = 6;
        else if (oem_type == "hdpro")
            type = 7;

        std::string start_ip = value["start ip"].isNull() ? "" : value["start ip"].asString();
        std::string stop_ip = value["stop ip"].isNull() ? "" : value["stop ip"].asString();

        SEARCH_DEVICE_INFO* _search_info = new SEARCH_DEVICE_INFO;
        memset(_search_info, 0, sizeof(*_search_info));
        _search_info->callback = callback;
        _search_info->user_param = user_param;

        if (start_ip.empty() || stop_ip.empty()) {
            RSNetSearchDevParam _param = {0};
            _param.Callback = RSNetSearchDevCallbackFun;
            _param.UserParam = _search_info;
            _param.LoginClientType = type;
            RSNetSearchDev(&_param);
            sdk_wrapper_log("[:] call <searh_device normal> result:success\n");
            return rs_success;
        } else {
            RSNetSearchDevParamPoint2Point _param = {0};
            _param.Callback = RSNetSearchDevCallbackFun;
            _param.UserParam = _search_info;
            _param.LoginClientType = type;
            memcpy(&_param.StartIP[0], start_ip.c_str(), std::min(sizeof(_param.StartIP), start_ip.length()));
            memcpy(&_param.StopIP[0], stop_ip.c_str(), std::min(sizeof(_param.StopIP), stop_ip.length()));
            RSNetSearchDevPoint2Point(&_param);
            sdk_wrapper_log("[:] call <searh_device udp_point_to_point> result:success\n");
            return rs_success;
        }
    }

    static rs_error_code modify_device(const char* param) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)){
            sdk_wrapper_log("[:] call <modify_device> error:rs_parse_json_error\n");
            return rs_parse_json_error;
        }

        std::string temp;
        RsNetSearchDevReq_t _param = {0};
        memcpy(_param.msgid, "12", sizeof(_param.msgid));
        temp = value["user"].asString();
        memcpy(_param.user, temp.c_str(), std::min(temp.length(), sizeof(_param.user)));
        temp = value["password"].asString();
        memcpy(_param.pwd, temp.c_str(), std::min(temp.length(), sizeof(_param.pwd)));
        temp = value["original ip"].asString();
        inet_pton4_(temp.c_str(), _param.cip);
        temp = value["change ip"].asString();
        inet_pton4_(temp.c_str(), _param.ip);
        temp = value["netmask"].asString();
        inet_pton4_(temp.c_str(), _param.mask);
        temp = value["gateway"].asString();
        inet_pton4_(temp.c_str(), _param.gw);
        temp = value["dns1"].asString();
        inet_pton4_(temp.c_str(), _param.dns1);
        temp = value["dns2"].asString();
        inet_pton4_(temp.c_str(), _param.dns2);
        temp = value["mac addr"].asString();
        memcpy(_param.macAddr, temp.c_str(), std::min(temp.length(), sizeof(_param.macAddr)));
        _param.devTypeULL = value["device type ull"].asUInt64();
        _param.mport = value["media port"].asInt();  
        _param.wport = value["web port"].asInt();
        temp = value["network mode"].asString();
        if (temp == "dhcp")
            _param.wMode = 0;
        else if (temp == "pppoe")
            _param.wMode = 1;
        else if (temp == "static")
            _param.wMode = 2;
        _param.wNewFlag = 1;
        _param.SonixSetMac = 0;

        bool user_point_point = value["point to point"].isNull() ? false : value["point to point"].asBool();
        if (user_point_point)
            _param.CMSUsePoint2Point = 1;

        if (RSNetSetNewDevInfoEx(&_param)) {
            sdk_wrapper_log("[:] call <modify_device> result:success\n");
            return rs_success;
        }
        sdk_wrapper_log("[:] call <modify_device> result:fail\n");
        return rs_fail;
    }

private:

};
