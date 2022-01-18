using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Newtonsoft.Json;
using SDKWrapper;
using SDKWrapperJsonValue;

using device_id = System.IntPtr;
using session_id = System.IntPtr;

namespace SDK_Demo_CSHARP
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            search_device_callback_ = new search_device_callback(search_device_callback_fun);
            connction_callback_ = new connction_callback(connction_callback_fun);
            alarm_callback_ = new alarm_callback(alarm_callback_fun);
            preivew_callback_ = new preivew_callback(preivew_callback_fun);

            device_id_ = NativeMethods.rs_create_device();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (preivew_id_ != IntPtr.Zero)
                stop_preview();
            if (device_id_ != IntPtr.Zero)
            {
                logout_device();
                NativeMethods.rs_destroy_device(device_id_);
            }
        }

        private void Login_Click(object sender, EventArgs e)
        {
            login_device();
        }

        private void Logout_Click(object sender, EventArgs e)
        {
            logout_device();
        }

        private void Start_Click(object sender, EventArgs e)
        {
            start_preview();
        }

        private void Stop_Click(object sender, EventArgs e)
        {
            stop_preview();
        }

        void search_device_callback_fun(String param, IntPtr user_param)
        {
            if (param != null)
            {
                Console.WriteLine("======<search_device_callback> {0}", param);
            }
            else
            {
                Console.WriteLine("======<search_device_callback> search done");
            }
        }

        private void search_device()
        {
            search_device_json json = new search_device_json { oem_type = "default" };
            string param = JsonConvert.SerializeObject(json);
            rs_error_code err = NativeMethods.rs_search_device(param, search_device_callback_, this.Handle);
            Console.WriteLine("======<rs_search_device> result:{0}", err);
        }

        void connction_callback_fun(String param, IntPtr user_param)
        {
            Console.WriteLine("======<connction_callback_fun> {0}", param);
        }

        void alarm_callback_fun(String alarm_type, String param, IntPtr user_param)
        {
            Console.WriteLine("======<alarm_callback_fun> {0}", alarm_type);
        }

        private void login_device()
        {
            device_login_json json = new device_login_json {
                ip_or_id = "172.18.12.63",
                media_port = 9988,
                user = "admin",
                password = "1111qqqq",
                ddns_id_server_addr = "",
                p2p_type = "ip",
                oem_type = "default"
            };

            string param = JsonConvert.SerializeObject(json);
            rs_error_code err = NativeMethods.rs_device_login(device_id_, param, connction_callback_, alarm_callback_, this.Handle);
            Console.WriteLine("======<rs_device_login> result:{0}", err);
        }

        private void logout_device()
        {
            rs_error_code result = NativeMethods.rs_device_logout(device_id_);
            Console.WriteLine("======<rs_device_logout> result:{0}\n", result);
        }

        void preivew_callback_fun(String param, IntPtr user_param)
        {
            Console.WriteLine("======<preivew_callback_fun> {0}", param);
        }

        private void start_preview()
        {
            start_preview_json json = new start_preview_json
            {
                channel = 0,
                stream_type = "sub stream",
                auto_connect = true,
            };
            string param = JsonConvert.SerializeObject(json);

            preview_param _preview_param = new preview_param();
            _preview_param.dev = device_id_;
            _preview_param.param = param;
            _preview_param.window = panel1.Handle;
            _preview_param.preview_cb = preivew_callback_fun;
            _preview_param.preview_user_param = this.Handle;
            preivew_id_ = NativeMethods.rs_start_preview(ref _preview_param);
            Console.WriteLine("======<rs_start_preview> preview_id:{0}\n", preivew_id_);
        }

        private void stop_preview()
        {
            NativeMethods.rs_stop_preview(preivew_id_);
            preivew_id_ = IntPtr.Zero;
        }

        search_device_callback search_device_callback_;
        connction_callback connction_callback_;
        alarm_callback alarm_callback_;
        preivew_callback preivew_callback_;

        device_id device_id_;
        session_id preivew_id_;
    }
}
