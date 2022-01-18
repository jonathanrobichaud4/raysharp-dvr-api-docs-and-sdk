import android.util.Log;

import com.raysharp.camviewplus.MainActivity;
import com.raysharp.camviewplus.model.data.RSDevice;

/**
 * Created by raysharp on 2018/3/8.
 */

public class JniHandler {

    private static final String TAG = JniHandler.class.getSimpleName();

    static {
        try {
            System.loadLibrary("SDKWrapper");
        } catch (UnsatisfiedLinkError e) {
            Log.i(TAG, "can't load SDKWrapper library");
        }
    }

    public static void search_device_callback(String param, Object user_param) {
        Log.e("======","search_device_callback:"+param);
    }

    public static void connction_callback(String param, Object user_param) {
        ((MainActivity)user_param).connction_callback(param);
    }

    public static void alarm_callback(String alarm_type, String param, Object user_param) {
        ((MainActivity)user_param).alarm_callback(alarm_type, param);
    }

    public static void preview_callback(String param, Object user_param) {
        Log.e("======","preview_callback:"+param);
    }

    public static void search_record_month_callback(String param, Object user_param) {
        Log.e("======","search_record_month_callback:"+param);
    }

    public static void search_record_day_callback(String param, Object user_param) {
        Log.e("======","search_record_day_callback:"+param);
    }

    public static void download_callback_by_file(String param, Object user_param) {
        Log.e("======","download_callback_by_file:"+param);
    }

    public static void download_callback_by_time(String param, Object user_param) {
        Log.e("======","download_callback_by_time:"+param);
    }

    public static void playback_callback_local(String param, Object user_param) {
        Log.e("======","playback_callback_local:"+param);
    }

    public static void playback_callback_remote(String param, Object user_param) {
        Log.e("======","playback_callback_remote:"+param);
    }

    public static void remote_test_callback(int type, String param, Object user_param) {
        Log.e("======","remote_test_callback:"+param);
    }

    public static void talk_callback(String param, Object user_param) {
        Log.e("======","talk_callback:"+param);
    }

    public static void playback_thumbnails_callback(String param, Object user_param) {
        Log.e("======","playback_thumbnails_callback:"+param);
    }

    public static void local_thumbnails_callback(byte[] data, Object user_param) {
        Log.e("======","local_thumbnails_callback:");
    }
	
	public static void log_sink_callback(String param, Object user_param) {
	    Log.e("======","log_sink_callback:"+param);
	}

    public static void human_face_alarm_report_data_callback(String param, Object user_param) {
        Log.e(TAG, "===========human_face_alarm_report_data_callback========>> param: ");
    }

    public static void human_face_alarm_report_status_callback(String param, Object user_param) {
        Log.e(TAG, "==========human_face_alarm_report_status_callback=========>> param: ");
    }

    public static void human_face_param_status_callback(String param, Object user_param) {
        Log.e(TAG, "==========human_face_param_status_callback=========>>  ");
    }

    public static void human_face_param_data_callback(byte[] data, Object user_param) {
        Log.e(TAG, "==========human_face_param_data_callback=========>>  ");
    }


    public native static long rs_android_surface_create();
    public native static int rs_android_surface_destory(long surface_id);
    public native static int rs_android_surface_change(long surface_id, int width, int height, long preview_id);
    public native static int rs_android_surface_draw(long surface_id, long preview_id);

    public native static int rs_init_log(String param);

    public native static int rs_init_log_ex(String param, Object user_param);

    public native static int rs_search_device(String param, Object user_param);
    public native static int rs_modify_device(String param);

    public native static long rs_create_device();
    public native static int rs_destroy_device(long dev);

    public native static int rs_device_login(long dev, String param, Object user_param);
    public native static int rs_device_logout(long dev);
    public native static String rs_get_login_rsp(long dev);

    public native static long rs_start_preview(long dev, String param, Object user_param);
    public native static int rs_stop_preview(long sess);

    public native static long rs_search_record_by_month(long dev, String param, Object user_param);
    public native static long rs_search_record_by_day(long dev, String param, Object user_param);
    public native static int rs_stop_search_record(long sess);
    
    public native static long rs_start_download_by_file(long dev, String param, Object user_param);
    public native static long rs_start_download_by_time(long dev, String param, Object user_param);
    public native static int rs_stop_download(long sess);

    public native static long rs_start_local_playback(String param, Object user_param);
    public native static long rs_start_remote_playback(long dev, String param, Object user_param);
    public native static long rs_start_sync_playback(String user_param);
    public native static int rs_stop_playback(long sess);

    public native static int rs_open_sound(long sess);
    public native static int rs_close_sound(long sess);
    public native static int rs_set_volume(long sess, int volume);
    public native static int rs_set_mute_on(long sess);
    public native static int rs_set_mute_off(long sess);

    public native static int rs_start_record(long sess, String param);
    public native static int rs_stop_record(long sess);

    public native static int rs_capture_picture(long sess, String param);

    public native static String rs_get_file_time(String filename);
    public native static String rs_get_current_time(long sess);
    public native static long rs_get_current_time_millisecond(long sess);
    public native static int rs_seek_by_time(long sess, String param);

    public native static int rs_get_file_key_frame_count(String param);
    public native static int rs_seek_by_key_frame_index(long sess, int key_frame_index);

    public native static int rs_switch_stream_type(long sess, String param);

    public native static int rs_set_play_mode(long sess, String param);

    public native static int rs_set_video_proportion(long sess, String param);

    public native static int rs_video_mouse_event(float x, float y, float s, int mode, long sess);
	public native static int rs_set_fishsye_mode(long sess, int type);
    public native static int rs_fisheye_ptz_control(long sess, String param);

    public native static boolean rs_window_in_zoom_status(long sess);
    public native static int rs_window_set_scale_size(long sess, float scaleSize);

	public native static String rs_query_param(long dev, String param);
    public native static int rs_set_param(long dev, String param, String buf);
	
	public native static int rs_ptz_control(long dev, String param);

	public native static int rs_remote_test(long dev, int type, String param, Object user_param);

    public native static long rs_start_talk_to_device(long dev, String param, Object user_param);

    public native static long rs_start_talk_to_channel(long dev, String param, Object user_param);

    public native static int rs_stop_talk(long sess);

    public native static long rs_start_playback_thumbnails(long dev, String param, Object user_param);

    public native static int rs_stop_playback_thumbnails(long sess);

    public native static long rs_start_local_playback_thumbnails(String param, Object user_param);
    public native static int rs_input_local_playback_time(long sess, long millisecond);
    public native static int rs_stop_local_playback_thumbnails(long sess);
    public native static int rs_reset_connection(long dev);

    public native static long rs_start_human_face_alarm_report(long dev, Object user_param);
    public native static int rs_stop_human_face_alarm_report(long sess);
    public native static long rs_start_human_face_param(long dev, Object user_param);
    public native static int rs_send_human_face_param(long sess, String param);
    public native static int rs_stop_human_face_param(long sess);

    public native static int rs_send_simple_command(long dev,int main_msg,int sub_msg);

    public native static int rs_sync_playback_add_session(long sync_sess, long session);
    public native static int rs_sync_playback_del_session(long sync_sess, long session);
}
