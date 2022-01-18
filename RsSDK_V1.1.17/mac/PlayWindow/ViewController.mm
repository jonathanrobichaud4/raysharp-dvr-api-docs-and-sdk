//
//  ViewController.m
//  PlayWindow
//
//  Created by lovingc2009 on 17/3/9.
//  Copyright © 2017年 YHO. All rights reserved.
//

#import "ViewController.h"
#import "RSSDKWrapper.h"
#import "json.h"

static std::string g_modify_str;

#define MAX_WINDOW_NUM 4

typedef struct {
    ViewController* _this;
    int             _index;
}DRAW_CALLBACK_INFO;

@implementation ViewController{
    PlayWindow*     _windowArray[MAX_WINDOW_NUM];
    device_id       _device_id;
    session_id      _preview_sess[MAX_WINDOW_NUM];
    session_id      _picture_id[MAX_WINDOW_NUM];
    DRAW_CALLBACK_INFO _draw_callback_info[MAX_WINDOW_NUM];
    bool               _not_picture_size;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    _windowArray[0] = _window1;
    _windowArray[1] = _window2;
    _windowArray[2] = _window3;
    _windowArray[3] = _window4;
    
    _device_id = rs_create_device();
}

- (instancetype)initWithCoder:(NSCoder *)coder{
    return [super initWithCoder:coder];
}


- (void)viewWillAppear{

}

- (void)awakeFromNib{
    
    
}

- (IBAction)b1:(id)sender {
    [self login_device];
}

- (IBAction)b2:(id)sender {
    [self logout_device];
}

- (IBAction)b3:(id)sender {
    [self start_preview:0];
}

- (IBAction)b4:(id)sender {
    [self stop_preview:0];
}

- (IBAction)b5:(id)sender {
    [self zoom:0];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

static void RSNET_CALL search_device_callback_fun(const char* param, void* user_param) {
    if (param) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if (!Json::parseFromStream(reader, param, &value, &err))
            return;
        
        g_modify_str = param;
        printf("===ip:%s, mode:%s\n", value["ip"].asCString(), value["network mode"].asCString());
    } else {
        printf("===search done\n");
    }
    return;
}

- (void)search_devic {
    Json::Value value;
    value.clear();
    value["oem type"] = "default";
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_error_code err = rs_search_device(param.c_str(), search_device_callback_fun, NULL);
    printf("======<rs_search_device> result:%d\n", err);
}

- (void)modify_devic {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, g_modify_str.c_str(), &value, &err))
        return;
    
    Json::Value _value;
    _value.clear();
    
    _value["user"] = std::string("admin");
    _value["password"] = std::string("admin");
    _value["original ip"] = value["ip"].asString();
    _value["change ip"] = value["ip"].asString();
    _value["netmask"] = value["netmask"].asString();
    _value["gateway"] = value["gateway"].asString();
    _value["dns1"] = value["dns1"].asString();
    _value["dns2"] = value["dns2"].asString();
    _value["mac addr"] = value["mac addr"].asString();
    _value["device type ull"] = value["device type ull"].asUInt64();
    _value["media port"] = value["media port"].asInt();
    _value["web port"] = value["web port"].asInt();
    _value["network mode"] = value["network mode"].asString();
    
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, _value);
    rs_error_code error_code = rs_modify_device(param.c_str());
    printf("======<rs_modify_device> result:%d\n", error_code);
}

static void RSNET_CALL connction_callback_fun(const char* param, void* user_param) {
    printf("======<connction_callback_fun>:%s\n", param);
}

static void RSNET_CALL alarm_callback_fun(const char* alarm_type, const char* param, void* user_param) {
    printf("======<alarm_callback_fun>:%s\n", alarm_type);
}

- (void)login_device {
    [self logout_device];
    
    Json::Value value;
    value.clear();
    value["ip or id"] = "172.18.12.63";
    value["media port"] = 9988;
    value["user"] = "admin";
    value["password"] = "1111qqqq";
    value["ddns id server addr"] = "";
    value["p2p type"] = "ip";
    value["oem type"] = "default";
    
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_error_code result = rs_device_login(_device_id, param.c_str(), connction_callback_fun, alarm_callback_fun, NULL);
    printf("======<rs_device_login> result:%d\n", result);
}

- (void)logout_device {
    rs_error_code result = rs_device_logout(_device_id);
    printf("======<rs_device_logout> result:%d\n", result);
}

static void RSNET_CALL preivew_callback_fun(const char* param, void* user_param) {
    printf("======<preview callback> callback:%s\n", param);
}

static void CALLBACK draw_callback_fun(SDKWRAPPER_DRAW_INFO* info, void* user_param) {
    DRAW_CALLBACK_INFO* cb_param = (DRAW_CALLBACK_INFO*)user_param;
    if (cb_param->_this)
        [cb_param->_this draw:cb_param->_index];
}

- (void)draw:(int) index {
    if (1) {
        rs_color color1 = {1.0f, 0.0f, 0.0f};
        rs_set_color(_preview_sess[index], &color1);
        rs_rect rect1[6] = {{0.0f, 0.25f, 1.0f, 0.25f}, {0.0f, 0.5f, 1.0f, 0.5f}, {0.0f, 0.75f, 1.0f, 0.75f},
            {0.25f, 0.0f, 0.25f, 1.0f}, {0.5f, 0.0f, 0.5f, 1.0f}, {0.75f, 0.0f, 0.75f, 1.0f}};
        rs_draw_line(_preview_sess[index], rect1, 6);
        
        rs_color color2 = {0.0f, 0.0f, 1.0f};
        rs_set_color(_preview_sess[index], &color2);
        rs_rect rect2[2] = {{0.1f, 0.1f, 0.25f, 0.25f}, {0.3f, 0.3f, 0.45f, 0.45f}};
        rs_draw_rect(_preview_sess[index], &rect2[0], 2);
        
        rs_color color3 = {0.0f, 1.0f, 0.0f};
        rs_set_color(_preview_sess[index], &color3);
        rs_rect rect3[2] = {{0.1f, 0.6f, 0.25f, 0.75f}, {0.3f, 0.8f, 0.45f, 0.95f}};
        rs_draw_solid_rect(_preview_sess[index], &rect3[0], 2, 0.3f);
        
        if (_picture_id[index]) {
            rs_rect rect3 = {0.5f, 0.3f, 0.7f, 0.5f};
            rs_draw_picture(_preview_sess[index], _picture_id[index], &rect3, 0.3f);
        }
    }
}

- (void)start_preview:(int)channel {
    [self stop_preview:channel];
    
    Json::Value value;
    value.clear();
    value["channel"] = channel;
    value["stream type"] = "main stream";
    value["auto connect"] = true;
    
    _draw_callback_info[channel]._this = self;
    _draw_callback_info[channel]._index = channel;
    
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    preview_param _preview_param = {0};
    _preview_param.dev = _device_id;
    _preview_param.param = param.c_str();
    _preview_param.window = (__bridge void *)_windowArray[channel];;
    _preview_param.preview_cb = preivew_callback_fun;
    _preview_param.preview_user_param = &_draw_callback_info[channel];
    //_preview_param.draw_cb = draw_callback_fun;
    _preview_sess[channel] = rs_start_preview(&_preview_param);
    printf("======<rs_start_preview> preview_id:%d\n", _preview_sess[channel]);
    
    {
        char path[MAX_PATH] = "/Users/raysharp/zhangwenhuan/PlayWindow/watermark.png";
        FILE* file = fopen(path, "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            size_t size = ftell(file);
            fseek(file, 0, SEEK_SET);
            
            char* data = new char[size];
            fread(data, size, 1, file);
            fclose(file);
            _picture_id[channel] = rs_upload_picture_from_memory(_preview_sess[channel], data, size);
            delete[] data;
        }
    }
}

- (void)stop_preview:(int)channel {
    if (_preview_sess[channel]) {
        if (_picture_id[channel]) {
            rs_delete_picture(_preview_sess[channel], _picture_id[channel]);
            _picture_id[channel] = 0;
        }
        
        rs_stop_preview(_preview_sess[channel]);
		_preview_sess[channel] = NULL;
        printf("======<rs_stop_preview> preview_id:%d\n", _preview_sess[channel]);
    }
}

- (void)capture_picture:(int)channel {
    Json::Value value;
    value.clear();
    value["picture name"] = "/Users/raysharp/Desktop/test.jpeg";
    
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_error_code result = rs_capture_picture(_preview_sess[channel], param.c_str());
    printf("======<rs_capture_picture> result:%d\n", result);
}

- (void)zoom:(int) channel {
    if (_not_picture_size) {
        _not_picture_size = false;
        rs_rect rect1 = {0.0f, 0.0f, 1.0f, 1.0f};
        rs_error_code result = rs_adjust_render_frame_rect(_preview_sess[channel], &rect1);
        printf("======<rs_adjust_render_frame_rect> result:%d\n", result);
    } else {
        _not_picture_size = true;
        rs_rect rect1 = {0.25f, 0.25f, 0.75f, 0.75f};
        rs_error_code result = rs_adjust_render_frame_rect(_preview_sess[channel], &rect1);
        printf("======<rs_adjust_render_frame_rect> result:%d\n", result);
    }
}

@end
