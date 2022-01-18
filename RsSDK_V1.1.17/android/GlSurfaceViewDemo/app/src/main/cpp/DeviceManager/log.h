#pragma once

extern log_sink_callback global_bugly_callback;
static rs_mutex s_global_sdk_wrapper_log_mutex;

static inline void sdk_wrapper_log(const char* format, ...) {
    if (global_bugly_callback) {
        char buf[256] = {0};
        va_list args;
        va_start(args, format);
#ifdef _MSC_VER
        vsnprintf_s(buf, 256, _TRUNCATE, format, args);
#else
        vsnprintf(buf, 256, format, args);
#endif
        va_end(args);

        rs_scoped_lock lock(s_global_sdk_wrapper_log_mutex);
        global_bugly_callback(buf, NULL);
    }
}
