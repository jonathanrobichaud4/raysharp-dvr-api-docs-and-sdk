#ifndef __SDK_WRAPPER_H__
#define __SDK_WRAPPER_H__

#include <jni.h>
#include <string.h>

#define JNI_HELP_CLASS        "com/raysharp/camviewplus/functions/JniHandler"
#define JNI_FUNCTION(NAME)    Java_com_raysharp_camviewplus_functions_JniHandler_##NAME
#define JNI_INT_RETURN        extern "C" JNIEXPORT jint    JNICALL
#define JNI_STR_RETURN        extern "C" JNIEXPORT jstring JNICALL
#define JNI_BOL_RETURN        extern "C" JNIEXPORT jboolean JNICALL
#define JNI_LON_RETURN        extern "C" JNIEXPORT jlong JNICALL
#define JNI_DEFAULT_PARAM     JNIEnv *env, jobject instance

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved);
JNI_LON_RETURN JNI_FUNCTION(rs_1android_1surface_1create)(JNI_DEFAULT_PARAM);
JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1destory)(JNI_DEFAULT_PARAM, jlong surface_id);
JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1change)(JNI_DEFAULT_PARAM, jlong surface_id, int width, int height, jlong preview_id);
JNI_INT_RETURN JNI_FUNCTION(rs_1android_1surface_1draw)(JNI_DEFAULT_PARAM, jlong surface_id, jlong preview_id);

JNI_INT_RETURN JNI_FUNCTION(rs_1init_1log)(JNI_DEFAULT_PARAM, jstring param);
JNI_INT_RETURN JNI_FUNCTION(rs_1init_1log_1ex)(JNI_DEFAULT_PARAM, jstring param, jobject user_param);

JNI_INT_RETURN JNI_FUNCTION(rs_1search_1device)(JNI_DEFAULT_PARAM, jstring param, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1modify_1device)(JNI_DEFAULT_PARAM, jstring param);

JNI_LON_RETURN JNI_FUNCTION(rs_1create_1device)(JNI_DEFAULT_PARAM);
JNI_INT_RETURN JNI_FUNCTION(rs_1destroy_1device)(JNI_DEFAULT_PARAM, jlong dev);

JNI_INT_RETURN JNI_FUNCTION(rs_1device_1login)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1device_1logout)(JNI_DEFAULT_PARAM, jlong dev);
JNI_STR_RETURN JNI_FUNCTION(rs_1get_1login_1rsp)(JNI_DEFAULT_PARAM, jlong dev);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1preview)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1preview)(JNI_DEFAULT_PARAM, jlong sess);

JNI_LON_RETURN JNI_FUNCTION(rs_1search_1record_1by_1month)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_LON_RETURN JNI_FUNCTION(rs_1search_1record_1by_1day)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1search_1record)(JNI_DEFAULT_PARAM, jlong sess);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1download_1by_1file)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_LON_RETURN JNI_FUNCTION(rs_1start_1download_1by_1time)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1download)(JNI_DEFAULT_PARAM, jlong sess);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1local_1playback)(JNI_DEFAULT_PARAM, jstring param, jobject user_param);
JNI_LON_RETURN JNI_FUNCTION(rs_1start_1remote_1playback)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);
JNI_LON_RETURN JNI_FUNCTION(rs_1start_1sync_1playback)(JNI_DEFAULT_PARAM, jstring user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1playback)(JNI_DEFAULT_PARAM, jlong sess);

JNI_INT_RETURN JNI_FUNCTION(rs_1open_1sound)(JNI_DEFAULT_PARAM, jlong sess);
JNI_INT_RETURN JNI_FUNCTION(rs_1close_1sound)(JNI_DEFAULT_PARAM, jlong sess);
JNI_INT_RETURN JNI_FUNCTION(rs_1set_1volume)(JNI_DEFAULT_PARAM, jlong sess, jint volume);
JNI_INT_RETURN JNI_FUNCTION(rs_1set_1mute_1on)(JNI_DEFAULT_PARAM, jlong sess);
JNI_INT_RETURN JNI_FUNCTION(rs_1set_1mute_1off)(JNI_DEFAULT_PARAM, jlong sess);

JNI_INT_RETURN JNI_FUNCTION(rs_1start_1record)(JNI_DEFAULT_PARAM, jlong sess, jstring param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1record)(JNI_DEFAULT_PARAM, jlong sess);

JNI_INT_RETURN JNI_FUNCTION(rs_1capture_1picture)(JNI_DEFAULT_PARAM, jlong sess, jstring param);

JNI_STR_RETURN JNI_FUNCTION(rs_1get_1file_1time)(JNI_DEFAULT_PARAM, jstring filename);
JNI_STR_RETURN JNI_FUNCTION(rs_1get_1current_1time)(JNI_DEFAULT_PARAM, jlong sess);
JNI_LON_RETURN JNI_FUNCTION(rs_1get_1current_1time_1millisecond)(JNI_DEFAULT_PARAM, jlong sess);
JNI_INT_RETURN JNI_FUNCTION(rs_1seek_1by_1time)(JNI_DEFAULT_PARAM, jlong sess, jstring param);

JNI_INT_RETURN JNI_FUNCTION(rs_1get_1file_1key_1frame_1count)(JNI_DEFAULT_PARAM, jstring filename);
JNI_INT_RETURN JNI_FUNCTION(rs_1seek_1by_1key_1frame_1index)(JNI_DEFAULT_PARAM, jlong sess, jint key_frame_index);

JNI_INT_RETURN JNI_FUNCTION(rs_1switch_1stream_1type)(JNI_DEFAULT_PARAM, jlong sess, jstring param);

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1play_1mode)(JNI_DEFAULT_PARAM, jlong sess, jstring param);

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1video_1proportion)(JNI_DEFAULT_PARAM, jlong sess, jstring param);

JNI_INT_RETURN JNI_FUNCTION(rs_1video_1mouse_1event)(JNI_DEFAULT_PARAM, jfloat x, jfloat y, jfloat s, jint mouse_event, jlong sess);

JNI_INT_RETURN JNI_FUNCTION(rs_1set_1fishsye_1mode)(JNI_DEFAULT_PARAM, jlong sess, jint type);
JNI_INT_RETURN JNI_FUNCTION(rs_1fisheye_1ptz_1control)(JNI_DEFAULT_PARAM, jlong sess, jstring param);

JNI_BOL_RETURN JNI_FUNCTION(rs_1window_1in_1zoom_1status)(JNI_DEFAULT_PARAM, jlong sess);
JNI_INT_RETURN JNI_FUNCTION(rs_1window_1set_1scale_1size)(JNI_DEFAULT_PARAM, jlong sess, jfloat scaleSize);

JNI_STR_RETURN JNI_FUNCTION(rs_1query_1param)(JNI_DEFAULT_PARAM, jlong dev, jstring param);
JNI_INT_RETURN JNI_FUNCTION(rs_1set_1param)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jstring buf);

JNI_INT_RETURN JNI_FUNCTION(rs_1ptz_1control)(JNI_DEFAULT_PARAM, jlong dev, jstring param);

JNI_INT_RETURN JNI_FUNCTION(rs_1remote_1test)(JNI_DEFAULT_PARAM, jlong dev, jint type, jstring param, jobject user_param);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1talk_1to_1device)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1talk_1to_1channel)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1talk)(JNI_DEFAULT_PARAM, jlong sess);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong dev, jstring param, jobject user_param);

JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong sess);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1local_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jstring param, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1input_1local_1playback_1time)(JNI_DEFAULT_PARAM, jlong sess, jlong millisecond);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1local_1playback_1thumbnails)(JNI_DEFAULT_PARAM, jlong sess);
JNI_INT_RETURN JNI_FUNCTION(rs_1reset_1connection)(JNI_DEFAULT_PARAM, jlong dev);

JNI_LON_RETURN JNI_FUNCTION(rs_1start_1human_1face_1alarm_1report)(JNI_DEFAULT_PARAM, jlong dev, jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1human_1face_1alarm_1report)(JNI_DEFAULT_PARAM, jlong sess);
JNI_LON_RETURN JNI_FUNCTION(rs_1start_1human_1face_1param)(JNI_DEFAULT_PARAM,jlong dev,jobject user_param);
JNI_INT_RETURN JNI_FUNCTION(rs_1send_1human_1face_1param)(JNI_DEFAULT_PARAM,jlong sess,jstring param);
JNI_INT_RETURN JNI_FUNCTION(rs_1stop_1human_1face_1param)(JNI_DEFAULT_PARAM,jlong sess);

JNI_INT_RETURN JNI_FUNCTION(rs_1send_1simple_1command)(JNI_DEFAULT_PARAM,jlong dev,jint main_msg,jint sub_msg);

JNI_INT_RETURN JNI_FUNCTION(rs_1sync_1playback_1add_1session)(JNI_DEFAULT_PARAM,jlong sync_sess,jlong session);
JNI_INT_RETURN JNI_FUNCTION(rs_1sync_1playback_1del_1session)(JNI_DEFAULT_PARAM,jlong sync_sess,jlong session);

#endif // end of __SDK_WRAPPER_H__
