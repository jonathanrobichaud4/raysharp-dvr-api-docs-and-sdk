#pragma once

class convert_file_type : public base_instance {
public:
    explicit convert_file_type(void* parent)
        : base_instance(parent, CONVERT_FILE_TYPE_INSTANCE_TYPE, "convert_file_type")
        , local_file_play_handle_(NULL)
        , user_param_(NULL)
        , convert_cb_(NULL)
    {
    }
    
    ~convert_file_type() {
        
    }

    static int RSNET_CALL CONVERT_STATUS_CALLBACK_FUN(int progress, void* userParam) {
        convert_file_type* _this = static_cast<convert_file_type*>(userParam);
        if (_this)
            return _this->CONVERT_STATUS_CALLBACK_FUN(progress);
        return 0;
    }

    int CONVERT_STATUS_CALLBACK_FUN(int progress) {
		if (base_running_ && convert_cb_){
			Json::Value value;
			value["progress"] = progress;
			Json::StreamWriterBuilder writer;
			std::string status = Json::writeString(writer, value);

			convert_cb_(status.c_str(), user_param_);
		}
        return 0;
	}

	rs_error_code start(const char* param, convert_callback convert_cb, void* user_param){
        stop();

		std::string err = "";
		Json::CharReaderBuilder reader;
		Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err)) {
            sdk_wrapper_log("[:] call <convert_file_type start> error:rs_parse_json_error\n");
            return rs_parse_json_error;
        }
		
		std::string source_file = value["source file"].asString();
		std::string target_file = value["target file"].asString();
		
        convert_cb_ = convert_cb;
        user_param_ = user_param;
        local_file_play_handle_ = RSPlayCreatePlayInstance(PLAY_LOCALFILE_TYPE);
        int result = RSPlayConvertFileStart(local_file_play_handle_, source_file.c_str(), target_file.c_str(), this, CONVERT_STATUS_CALLBACK_FUN);
        
        base_running_ = result == 0 ? true : false;
        sdk_wrapper_log("[:] call <convert_file_type start> result:%s\n", result == 0 ? "success" : "fail");
        return result == 0 ? rs_success : rs_fail;
	}

	rs_error_code stop(){
        if (!base_running_ && !local_file_play_handle_)
            return rs_success;

        base_running_ = false;

        if (local_file_play_handle_) {
            RSPlayConvertFileStop(local_file_play_handle_);
            RSPlayDestroyPlayInstance(local_file_play_handle_);
            local_file_play_handle_ = NULL;
        }
        user_param_ = NULL;
        convert_cb_ = NULL;

        sdk_wrapper_log("[:] call <convert_file_type stop> result:success\n");
        return rs_success;
	}

private:
    RSPlayHandle           local_file_play_handle_;
    void*                  user_param_;
    convert_callback       convert_cb_;
};
