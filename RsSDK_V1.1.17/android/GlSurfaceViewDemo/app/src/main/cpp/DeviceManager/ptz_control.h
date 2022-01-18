#pragma once

class ptz_control {
public:
    ptz_control() {

    }
    
    ~ptz_control() {
        
    }

    rs_error_code operator()(const char* param, connection& conn) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[%s] call <ptz_control start> error:rs_parse_json_error\n", conn.get_ip_or_id().c_str());
            return rs_parse_json_error;
        }

        std::string ptz_type = value["ptz type"].asString();
        if (ptz_type == "normal") {
            int channel = value["channel"].asUInt();
            int speed = value["speed"].asInt();
            std::string operation = value["operation"].asString();
            std::string flag = value["flag"].asString();
            
            int _operation = 0;
            if (operation == "left")
                _operation = MsgPTZLeft;
            else if (operation == "up left")
                _operation = MsgPTZUpLeft;
            else if (operation == "up")
                _operation = MsgPTZUp;
            else if (operation == "up right")
                _operation = MsgPTZUpRight;
            else if (operation == "right")
                _operation = MsgPTZRight;
            else if (operation == "down right")
                _operation = MsgPTZDownRight;
            else if (operation == "down")
                _operation = MsgPTZDown;
            else if (operation == "down left")
                _operation = MsgPTZDownLeft;
            else if (operation == "zoom out")
                _operation = MsgPTZZoomOut;
            else if (operation == "zoom in")
                _operation = MsgPTZZoomIn;
            else if (operation == "focus near")
                _operation = MsgPTZFocusNear;
            else if (operation == "focus far")
                _operation = MsgPTZFocusFar;
            else if (operation == "iris open")
                _operation = MsgPTZIRISOpen;
            else if (operation == "iris close")
                _operation = MsgPTZIRISClose;
            else if (operation == "auto scan")
                _operation = MsgPTZAutoScan;
            else if (operation == "scan line")
                _operation = MsgPTZCruise;
            
            int _flag = 0;
            if (flag == "start")
                _flag = PTZControlStart;
            else if (flag == "stop")
                _flag = PTZControlStop;
            
            if (channel > -1 && _operation != 0 && conn.get_connection()) {
                PTZControlNormal normal;
                normal.Flag = _flag;
                normal.Speed = speed;
                PTZControlReq req;
                req.Channel = channel;
                req.Normal = normal;
                int result = RSNetPTZControl(conn.get_connection(), _operation, &req);

                sdk_wrapper_log("[%s] call <ptz_control start normal> result:%s\n", conn.get_ip_or_id().c_str(), result ? "success" : "fail");
                if (result == 1)
                    return rs_success;
                else if (result == 2)
                    return rs_no_permission;
                else
                    return rs_fail;
            }
        } else if (ptz_type == "preset") {
            int channel = value["channel"].asInt();
            int index = value["index"].asInt();
            std::string operation = value["operation"].asString();
            
            int _operation = 0;
            if (operation == "call")
                _operation = MsgPTZCallPreset;
            else if (operation == "set")
                _operation = MsgPTZSetPreset;
            else if (operation == "clear")
                _operation = MsgPTZClearPreset;
            
            if (channel > -1 && _operation != 0 && conn.get_connection()) {
                PTZControlPreset preset;
                preset.Index = index + 1;
                preset.Time = 3;
                PTZControlReq req;
                req.Channel = channel;
                req.Preset = preset;
                int result = RSNetPTZControl(conn.get_connection(), _operation, &req);

                sdk_wrapper_log("[%s] call <ptz_control start preset> result:%s\n", conn.get_ip_or_id().c_str(), result ? "success" : "fail");
                if (result == 1)
                    return rs_success;
                else if (result == 2)
                    return rs_no_permission;
                else
                    return rs_fail;
            }
		} else if(ptz_type == "cruise") {
			int _flag = 0;
			std::string flag = value["flag"].asString();
			if (flag == "start")
				_flag = PTZControlStart;
			else if (flag == "stop")
				_flag = PTZControlStop;
			int channel = -1;
			channel = value["channel"].asUInt();

			if(channel > -1 && conn.get_connection()) {
				PTZControlCruise cruise = {0};
				cruise.Flag = _flag;
				cruise.No = 1;
				cruise.LineSpeed = value["speed"].asUInt();
				cruise.Time = value["time"].asUInt();

				PTZControlReq req = {0};
				req.Channel = channel;
				req.Cruise = cruise;
				int result = RSNetPTZControl(conn.get_connection(), MsgPTZCruise, &req);
				sdk_wrapper_log("[%s] call <ptz_control start cruise> result:%s\n", conn.get_ip_or_id().c_str(), result ? "success" : "fail");
                if (result == 1)
                    return rs_success;
                else if (result == 2)
                    return rs_no_permission;
                else
                    return rs_fail;
			}
		}
        sdk_wrapper_log("[%s] call <ptz_control start> error:rs_parse_ptz_param_error\n", conn.get_ip_or_id().c_str());
        return rs_parse_ptz_param_error;
    }
};
