//
//  PlayViewController.m
//  iosPlayWnd
//
//  Created by Raysharp on 2018/2/1.
//  Copyright © 2018年 Raysharp. All rights reserved.
//

#import "PlayViewController.h"
#import "PlayWindow.h"
#import "RSSDKWrapper.h"
#import <AVFoundation/AVFoundation.h>

#include "json.h"
#define TRACE printf

@interface PlayViewController ()<UICollectionViewDelegate, UICollectionViewDataSource>{
    device_id           device_id_;
    session_id          preview_id_[4];
    session_id          local_playback_id_[4];
    session_id          remote_playback_id_[4];
    int                 video_proportion;
    FISHEYE_COMB_TYPE_E fish_eye_mode;
    session_id          _talk_session;
}
@property (weak, nonatomic) IBOutlet UICollectionView *collectionView;
@property (weak, nonatomic) IBOutlet UICollectionViewFlowLayout *flowLayout;

@end

@implementation PlayViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    [self.collectionView registerNib:[UINib nibWithNibName:@"PlayWindow" bundle:nil] forCellWithReuseIdentifier:@"PlayWindow"];

    device_id_ = rs_create_device();
    fish_eye_mode = FISH_COMB_TYPE_BUTT;
}

-(void)viewWillAppear:(BOOL)animated{
    self.flowLayout.itemSize = CGSizeMake(self.collectionView.frame.size.width, self.collectionView.frame.size.width);
    [self.collectionView reloadData];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView{
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section{
    return 4;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath{
    PlayWindow *cell = (PlayWindow *)[collectionView dequeueReusableCellWithReuseIdentifier:@"PlayWindow" forIndexPath:indexPath];
    return cell;
}

- (PlayWindow *)windowAtIndex:(NSInteger) idx{
    return (PlayWindow *)[self.collectionView cellForItemAtIndexPath:[NSIndexPath indexPathForItem:idx inSection:0]];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)btn1:(id)sender {
    [self login];
}

- (IBAction)btn2:(id)sender {
    [self logout];
}

- (IBAction)btn3:(id)sender {
    [self start_preview:0];
}

- (IBAction)btn4:(id)sender {
    [self stop_preview:0];
}

- (IBAction)btn5:(id)sender {
    
}

static void RSNET_CALL search_device_callback_fun(const char* param, void* user_param) {
    TRACE("======<search_device> callback:%s\n", param ? param : "search done");
}

- (void)search_device {
    Json::Value value;
    value.clear();
    value["oem type"] = "default";
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_error_code result = rs_search_device(param.c_str(), search_device_callback_fun, NULL);
    TRACE("======<rs_search_device> result:%d\n", result);
}

static void RSNET_CALL connction_callback_fun(const char* param, void* user_param) {
    TRACE("======<login connection callback> callback:%s\n", param);
}

static void RSNET_CALL alarm_callback_fun(const char* alarm_type, const char* param, void* user_param) {
    TRACE("======<login alarm callback> callback:%s\n", alarm_type);
    
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return;
    
    if (!strcmp(alarm_type, "RSSDKChannelStatus")) {
        std::string str;
        for (Json::ArrayIndex i = 0; i < value.size(); i++) {
            char buf[128] = {0};
            sprintf(buf, "[ch:%d,%s] ", i, value[i]["online"].asBool() ? "on" : "off");
            str += buf;
        }
        TRACE("%s\n", str.c_str());
    }
}

- (void)login {
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
    rs_error_code result = rs_device_login(device_id_, param.c_str(), connction_callback_fun, alarm_callback_fun, (__bridge void*)self);
    TRACE("======<rs_device_login> result:%d\n", result);
}

- (void)logout {
    rs_error_code result = rs_device_logout(device_id_);
    TRACE("======<rs_device_logout> result:%d\n", result);
}

static void RSNET_CALL preivew_callback_fun(const char* param, void* user_param) {
    TRACE("======<preview callback> callback:%s\n", param);
}

- (void)start_preview:(int)index {
    PlayWindow *play_wnd = [self windowAtIndex:index];
    HWND wnd = (__bridge HWND)play_wnd;
    
    Json::Value value;
    value.clear();
    value["channel"] = index;
    value["stream type"] = "sub stream";
    value["auto connect"] = true;
    
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    preview_param _preview_param = {0};
    _preview_param.dev = device_id_;
    _preview_param.param = param.c_str();
    _preview_param.window = wnd;
    _preview_param.preview_cb = preivew_callback_fun;
    _preview_param.preview_user_param = (__bridge void*)self;
    preview_id_[index] = rs_start_preview(&_preview_param);
    rs_open_sound(preview_id_[index]);
    TRACE("======<rs_start_preview> preview_id:%d\n", preview_id_[index]);
}

- (void)stop_preview:(int) index {
    rs_close_sound(preview_id_[index]);
    rs_stop_preview(preview_id_[index]);
    TRACE("======<rs_stop_preview> preview_id:%d\n", preview_id_[index]);
    preview_id_[index] = 0;
}

- (void)set_fish_mode:(int) index {
    if (fish_eye_mode == FISH_COMB_TYPE_BUTT)
        fish_eye_mode = FISH_CEILING_4PTZ;
    else if (fish_eye_mode == FISH_CEILING_4PTZ)
        fish_eye_mode = FISH_COMB_TYPE_BUTT;
    rs_error_code ret = rs_set_fishsye_mode(preview_id_[index], fish_eye_mode);
    TRACE("======<rs_set_fishsye_mode> result:%d\n", ret);
}

- (void)set_video_proportion:(int) index {
     video_proportion++;
     if (video_proportion == 4)
     video_proportion = 0;
     std::string name = "full window";
     switch (video_proportion) {
     case 0:
     name = "full window";
     break;
     case 1:
     name = "picture proportion";
     break;
     case 2:
     name = "4:3 proportion";
     break;
     case 3:
     name = "16:9 proportion";
     break;
     }
     
     Json::Value value;
     value.clear();
     value["proportion"] = name;
     Json::StreamWriterBuilder writer;
     std::string param = Json::writeString(writer, value);
     
     rs_error_code result = rs_set_video_proportion(preview_id_[index], param.c_str());
     TRACE("======<rs_set_video_proportion> result:%d\n", result);
}

void RSNET_CALL local_playback_callback_fun(const char* param, void* user_param) {
    TRACE("======<local_playback_callback_fun>:%s\n", param);
}

- (void)start_local_playback:(int) index {
     PlayWindow *play_wnd = [self windowAtIndex:0];
     HWND wnd = (__bridge HWND)play_wnd;
     
     std::string home = NSHomeDirectory().UTF8String;
     std::string path = home + "/Documents/record/1920_1080_30_265_8192.mp4";
     
     Json::Value value;
     value.clear();
     value["file name"] = path;
     Json::StreamWriterBuilder writer;
     std::string _param = Json::writeString(writer, value);
     
     local_playback_param param = {0};
     param.param = _param.c_str();
     param.window = wnd;
     param.playback_cb = local_playback_callback_fun;
     param.playback_user_param = (__bridge void*)self;
     local_playback_id_[index] = rs_start_local_playback(&param);
}

- (void)stop_local_playback:(int) index {
    rs_stop_playback(local_playback_id_[index]);
    TRACE("======<rs_stop_playback> preview_id:%d\n", local_playback_id_[index]);
    local_playback_id_[index] = 0;
}

void RSNET_CALL talk_callback_fun(const char* param, void* user_param) {
    
}

- (void)start_talk {
    Json::Value value;
    value.clear();
    value["talk mode"] = "old mode";
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    
    //[[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error:nil];
    
    _talk_session = rs_start_talk_to_device(device_id_, param.c_str(), talk_callback_fun, NULL);
}

- (void)stop_talk {
    if (_talk_session)
        rs_stop_talk(_talk_session);
    _talk_session = NULL;
}

@end
