package com.example.glsurfaceviewdemo;

import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("SDKWrapper");
    }

    private Button button1, button2, button3, button4,button5,button6,button7,button8;

    long[] preview_sess = new long[4];
    long[] local_playback_sess = new long[4];
    long[] remote_playback_sess = new long[4];
    long[] talk_to_channel_id = new long[4];
    private ArrayList<OpenGLSurfaceView> window = new ArrayList<>();

    public long device_id, talk_to_device_id;
    public int video_proportion, fisyeye_mode;

    public static final String SDCARDPATH = Environment.getExternalStorageDirectory().getAbsolutePath();
    private String dataPath = "/camviewplus";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main_one);
        setContentView(R.layout.activity_main_four);

        initView();

        makeDir();

    }

    private void initView() {
        OpenGLSurfaceView view1 = findViewById(R.id.glsv1);
        OpenGLSurfaceView view2 = findViewById(R.id.glsv2);
        OpenGLSurfaceView view3 = findViewById(R.id.glsv3);
        OpenGLSurfaceView view4= findViewById(R.id.glsv4);
        window.add(view1);
        window.add(view2);
        window.add(view3);
        window.add(view4);

        button1 = findViewById(R.id.btn1);
        button2 = findViewById(R.id.btn2);
        button3 = findViewById(R.id.btn3);
        button4 = findViewById(R.id.btn4);
        button5 = findViewById(R.id.btn5);
        button6 = findViewById(R.id.btn6);
        button7 = findViewById(R.id.btn7);
        button8 = findViewById(R.id.btn8);

        button1.setOnClickListener(this);
        button2.setOnClickListener(this);
        button3.setOnClickListener(this);
        button4.setOnClickListener(this);
        button5.setOnClickListener(this);
        button6.setOnClickListener(this);
        button7.setOnClickListener(this);
        button8.setOnClickListener(this);

        device_id = JniHandler.rs_create_device();
        fisyeye_mode = 41;
        Log.e("======","rs_create_device:"+device_id);
    }

    public void makeDir() {
        File file = new File(SDCARDPATH + dataPath);
        if(!file.exists()) {
            file.mkdirs();
        }

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn1:
                login();
                break;
            case R.id.btn2:
                logout();
                break;
            case R.id.btn3:
                start_preview(0, 0);
                break;
            case R.id.btn4:
                stop_preview(0);
                break;
            case R.id.btn5:
                start_talk_to_device();
                break;
            case R.id.btn6:
                stop_talk_to_device();
                break;
            case R.id.btn7:
                break;
            case R.id.btn8:
                break;
            default:
                break;
        }
    }

    public void search_device() {
        try {
            JSONObject json = new JSONObject();
            json.put("oem type","default");
            int result = JniHandler.rs_search_device(json.toString(),this);
            Log.e("======","rs_search_device:"+result);
        }catch (JSONException ex) {

        }
    }

    public void search_device_callback(String param) {
        Log.e("======","search_device_callback:"+param);
    }

    public void connction_callback(String param) {
        Log.e("======","connction_callback:"+param);
    }

    public void alarm_callback(String alarm_type, String param) {
        Log.e("======","alarm_callback:"+alarm_type);
    }

    public void login() {
        try {
            JSONObject json = new JSONObject();
            json.put("ip or id","172.18.12.63");
            json.put("media port",9988);
            json.put("user","admin");
            json.put("password","1111qqqq");
            json.put("ddns id server addr","");
            json.put("p2p type","ip");
            json.put("oem type","default");
            int result = JniHandler.rs_device_login(device_id, json.toString(), this);
            Log.e("======","rs_device_login:"+result);
        }catch (JSONException ex) {

        }
    }

    public void logout() {
        int result = JniHandler.rs_device_logout(device_id);
        Log.e("======","rs_device_logout:"+result);
    }

    public void start_preview(int index, int channel) {
        try {
            JSONObject json = new JSONObject();
            json.put("channel",channel);
            json.put("stream type","sub stream");
            json.put("auto connect", true);
            preview_sess[index] = JniHandler.rs_start_preview(device_id, json.toString(),this);
            window.get(index).SetPreviewID(preview_sess[index]);
            Log.e("======","rs_start_preview:"+preview_sess[index]);
        } catch (JSONException ex) {

        }
    }

    public void stop_preview(int index) {
        int result = JniHandler.rs_stop_preview(preview_sess[index]);
        window.get(index).SetPreviewID(0);
        preview_sess[index] = 0;
        Log.e("======","rs_stop_preview:"+result);
    }

    public void capture(int index) {
        try {
            String capture_name = SDCARDPATH + dataPath + "/" + index + "_capture.jpeg";

            JSONObject json = new JSONObject();
            json.put("picture name", capture_name);

            int result = JniHandler.rs_capture_picture(preview_sess[index], json.toString());
            Log.e("======", "<rs_capture_picture>:result:" + result + ", path:" + capture_name);
        }catch (JSONException ex) {

        }
    }

    public void start_record(int index) {
        try {
            String capture_name = SDCARDPATH + dataPath + "/" + index + "_capture.jpeg";
            String record_name = SDCARDPATH + dataPath + "/" + index + "_record.mp4";

            JSONObject json = new JSONObject();
            json.put("picture name", capture_name);
            json.put("file name", record_name);

            int result = JniHandler.rs_start_record(preview_sess[index], json.toString());
            Log.e("======", "<rs_start_record>:result:" + result);
        }catch (JSONException ex) {

        }
    }

    public void stop_record(int index) {
        int result = JniHandler.rs_stop_record(preview_sess[index]);
        Log.e("======", "<rs_stop_record>:result:" + result);
    }

    public void start_local_playback(int index) {
        try {
            String record_name = SDCARDPATH + dataPath + "/" + index + "_record.mp4";

            JSONObject json = new JSONObject();
            json.put("file name",record_name);
            local_playback_sess[index] = JniHandler.rs_start_local_playback(json.toString(),this);
            JniHandler.rs_open_sound(local_playback_sess[index]);
            window.get(index).SetPreviewID(local_playback_sess[index]);
            Log.e("======","rs_start_local_playback:"+local_playback_sess[index]);
        }catch (JSONException ex) {

        }
    }

    public void stop_local_playback(int index) {
        int result = JniHandler.rs_stop_playback(local_playback_sess[index]);
        local_playback_sess[index] = 0;
        Log.e("======","rs_stop_local_playback:"+result);
    }

    public void set_play_mode(int index, String mode) {
        try {
            JSONObject json = new JSONObject();
            json.put("operation type",mode);
            int result = JniHandler.rs_set_play_mode(local_playback_sess[index], json.toString());
            Log.e("======","rs_set_play_mode:"+mode + ", result:"+result);
        }catch (JSONException ex) {

        }
    }

    public void set_video_proportion(int index) {
        try {
            //"proportion" : "full window" "picture proportion" "4:3 proportion" "16:9 proportion"
            video_proportion++;
            if (video_proportion == 4)
                video_proportion = 0;
            String name = "full window";
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
            JSONObject json = new JSONObject();
            json.put("proportion", name);
            int result = JniHandler.rs_set_video_proportion(preview_sess[index], json.toString());
            Log.e("======","rs_set_video_proportion:"+result + "   " + name);
        }catch (JSONException ex) {

        }

    }

    public void start_remote_playback(int index, int channel) {
        try {

            JSONObject json = new JSONObject();
            json.put("channel",channel);
            json.put("stream type","main stream");
            json.put("record type",0);
            json.put("begin time","2018-04-02 00:00:00");
            json.put("end time","2018-04-02 23:59:59");
            remote_playback_sess[index] = JniHandler.rs_start_remote_playback(device_id, json.toString(),this);
            window.get(index).SetPreviewID(remote_playback_sess[index]);
            Log.e("======","rs_start_remote_playback:"+remote_playback_sess[index]);
        } catch (JSONException ex) {

        }
    }

    public void stop_remote_playback(int index) {
        {
            int result = JniHandler.rs_stop_playback(remote_playback_sess[index]);
            window.get(index).SetPreviewID(0);
            remote_playback_sess[index] = 0;
            Log.e("======","rs_stop_playback:"+result);
        }
    }

    public void set_fish_mode(int index) {
        fisyeye_mode = 34;
        int result = JniHandler.rs_set_fishsye_mode(preview_sess[index], fisyeye_mode);
        Log.e("======","rs_set_fishsye_mode:"+result);
    }

    public void start_fisheye_ptz(int index) {
        try {

            JSONObject json = new JSONObject();
            json.put("operation","auto scan");
            json.put("flag","start");
            json.put("speed",50);
            int ret = JniHandler.rs_fisheye_ptz_control(preview_sess[index], json.toString());
            Log.e("======","rs_fisheye_ptz_control stop:"+ret);
        } catch (JSONException ex) {

        }
    }

    public void stop_fisheye_ptz(int index) {
        try {

            JSONObject json = new JSONObject();
            json.put("operation","auto scan");
            json.put("flag","stop");
            json.put("speed",50);
            int ret = JniHandler.rs_fisheye_ptz_control(preview_sess[index], json.toString());
            Log.e("======","rs_fisheye_ptz_control stop:"+ret);
        } catch (JSONException ex) {

        }
    }

    public void start_talk_to_device() {
        try {
            JSONObject json = new JSONObject();
            json.put("talk mode" , "old mode");
            talk_to_device_id = JniHandler.rs_start_talk_to_device(device_id, json.toString(), null);
            Log.e("======","rs_start_talk_to_device start:"+talk_to_device_id);
        } catch (JSONException ex) {

        }
    }

    public void stop_talk_to_device() {
        int result = JniHandler.rs_stop_talk(talk_to_device_id);
        Log.e("======", "<rs_stop_talk>:result:" + result);
        talk_to_device_id = 0;
    }
}
