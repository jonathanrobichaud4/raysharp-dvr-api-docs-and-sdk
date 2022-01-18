#pragma once

class capture_from_device {
public:
    capture_from_device() {

    }
    
    ~capture_from_device() {
        
    }
    
    /*
    * dev          ---> (device_id) see return value of <rs_create_device>
    * param        ---> "channel"         : (uin32_t) 0 1 2 3 4 and so on
    *              ---> "picture name"    : full path name of capture file, such as "C:\capture.jpeg", only suport jpg or jpeg
    * return value ---> see <rs_error_code>
    * attention    ---> this function is blocking
    */
    rs_error_code operator()(const char* param, connection& conn) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[%s] call <capture_from_device> error:rs_parse_json_error\n", conn.get_ip_or_id().c_str());
            return rs_parse_json_error;
        }

        uint32_t channel = value["channel"].asUInt();
        std::string picture_name = value["picture name"].asString();

        if (conn.get_connection()) {
            RSNetDevCaptureParam capture_param = {0};
            capture_param.Channel = channel;
            memcpy(capture_param.FileName, picture_name.c_str(), std::min(picture_name.length(), _countof(capture_param.FileName)));
            capture_param.FileName[_countof(capture_param.FileName)-1] = 0;
            capture_param.jpgParam.StructSize = sizeof(capture_param.jpgParam);
            capture_param.jpgParam.wPicSize = 0;
            capture_param.jpgParam.wPicQuality = 0;
            capture_param.UserParam = NULL;
            BOOL result = RSNetCapture(conn.get_connection(), &capture_param);

            //sdk_wrapper_log("[%s ch:%d] call <capture_from_device> result:%s\n", conn.get_ip_or_id().c_str(), channel, result ? "success" : "fail");
            return result ? rs_success : rs_fail;
        }
        sdk_wrapper_log("[%s ch:%d] call <capture_from_device> error:rs_need_login_first\n", conn.get_ip_or_id().c_str(), channel);
        return rs_need_login_first;
    }
};
