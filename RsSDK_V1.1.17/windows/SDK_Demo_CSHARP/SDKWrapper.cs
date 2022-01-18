using System;
using System.Runtime.InteropServices;

namespace SDKWrapper
{
    using HWND = System.IntPtr;
    using device_id = System.IntPtr;
    using session_id = System.IntPtr;

    enum rs_error_code
    {
        rs_no_permission = -18,
        rs_not_defined = -17,
        rs_unknown_mp4_file = -16,
        rs_hk_mp4_file = -15,
        rs_param_error = -14,
        rs_need_login_first = -13,
        rs_parse_ptz_param_error = -12,
        rs_param_page_not_found = -11,
        rs_need_input_password = -10,
        rs_file_access_error = -9,
        rs_file_not_found = -8,
        rs_record_not_found = -7,
        rs_buffer_too_small = -6,
        rs_session_not_found = -5,
        rs_device_not_found = -4,
        rs_parse_json_error = -3,
        rs_unknown_error = -2,
        rs_fail = -1,
        rs_success = 0
    }

    [UnmanagedFunctionPointerAttribute(CallingConvention.StdCall)]
    public delegate void search_device_callback(String param, IntPtr user_param);

    [UnmanagedFunctionPointerAttribute(CallingConvention.StdCall)]
    public delegate void connction_callback(String param, IntPtr user_param);

    [UnmanagedFunctionPointerAttribute(CallingConvention.StdCall)]
    public delegate void alarm_callback(String alarm_type, String param, IntPtr user_param);

    [UnmanagedFunctionPointerAttribute(CallingConvention.StdCall)]
    public delegate void preivew_callback(String param, IntPtr user_param);

    struct preview_param
    {
        public device_id dev;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)]
        public string param;
        public HWND window;
        public preivew_callback preview_cb;
        public IntPtr preview_user_param;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public char[] reserve;
    }
        partial class NativeMethods
    {
        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_search_device", CallingConvention = CallingConvention.Cdecl)]
        public static extern rs_error_code rs_search_device(String param, search_device_callback callback, IntPtr user_param);

        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_create_device", CallingConvention = CallingConvention.Cdecl)]
        public static extern device_id rs_create_device();

        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_destroy_device", CallingConvention = CallingConvention.Cdecl)]
        public static extern rs_error_code rs_destroy_device(device_id dev);

        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_device_login", CallingConvention = CallingConvention.Cdecl)]
        public static extern rs_error_code rs_device_login(device_id dev, String param, connction_callback conn_cb, alarm_callback alarm_cb, IntPtr user_param);

        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_device_logout", CallingConvention = CallingConvention.Cdecl)]
        public static extern rs_error_code rs_device_logout(device_id dev);

        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_start_preview", CallingConvention = CallingConvention.Cdecl)]
        public static extern session_id rs_start_preview(ref preview_param param);

        [DllImport("RSSDKWrapper.dll", EntryPoint = "rs_stop_preview", CallingConvention = CallingConvention.Cdecl)]
        public static extern rs_error_code rs_stop_preview(session_id sess);
    }
}
