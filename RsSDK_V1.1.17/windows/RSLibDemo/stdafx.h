
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include "../../SDKWrapper/Include/RSSDKWrapper.h"
#include "../../SDKWrapper/JsonCpp/json.h"
#include "./Markup.h"
#include <afxwin.h>
#include <afxwin.h>

#define ICO_DEV_LOGIN          1
#define ICO_DEV_LOGOUT         2
#define ICO_CH_ONLINE          4
#define ICO_CH_OFFLINE         13
#define ICO_CH_ONLINE_PREIVEW  5
#define ICO_CH_OFFLINE_PREIVEW 8

typedef enum {
    TYPE_DEVICE = 0,
    TYPE_CHANNEL
}NodeType;

typedef struct _DEVICE_INFO_ {
    NodeType  type;
    HTREEITEM item;
    void*     user_param;
    bool      online_status;
    bool      in_preview_status;

    CString  ip;
    CString  ip_type;
    int      mediaport;
    CString  username;
    CString  password;
    session_id device_session;
    session_id talk_session;
    session_id preview_session;

    int      channel;
    _DEVICE_INFO_* device_info;
}DEVICE_INFO;

class rs_app_mutex {
public:
    rs_app_mutex()      { InitializeCriticalSectionAndSpinCount(&mCriSec, 1500);   }
    ~rs_app_mutex()     { DeleteCriticalSection(&mCriSec);                         }
    void lock()         { EnterCriticalSection(&mCriSec);                          }
    bool try_lock()     { return TryEnterCriticalSection(&mCriSec) ? true : false; }
    void unlock()       { LeaveCriticalSection(&mCriSec);                          }
private:
    CRITICAL_SECTION mCriSec;
};

class rs_app_scoped_lock {
public:
    explicit rs_app_scoped_lock(rs_app_mutex &aMutex) : mMutex(aMutex) { mMutex.lock(); }
    ~rs_app_scoped_lock() { mMutex.unlock(); }

private:
    rs_app_mutex& mMutex;
};


static char* CreateUTF8TextInitWithString(CString strValue)
{
    char *buffer = NULL;
    int  length;

#ifdef _UNICODE
    length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1, NULL, 0, NULL, NULL);
#else
    return NULL;
#endif
    if (length <= 0)
    {
        return NULL;
    }

    buffer = new char[length];
    if (buffer == NULL)
    {
        return NULL;
    }

    ZeroMemory(buffer, length);

#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, strValue, -1, buffer, length, NULL, NULL);
#else
    strcpy_s(buffer, length, strValue);
#endif

    return buffer;
}


static BOOL CreateString_InitWithUTF8Text(CString& str, char* pUTF8Text)
{
    if (NULL == pUTF8Text)
    {
        return FALSE;
    }

    int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
        0,
        pUTF8Text,
        -1,
        NULL,
        0 ); 

    wchar_t*  pUnicode = new  wchar_t[unicodeLen+1];
    if (NULL == pUnicode)
    {
        return FALSE;
    }

    MultiByteToWideChar( CP_UTF8, 0, pUTF8Text, -1, (LPWSTR)pUnicode, unicodeLen );

    str = pUnicode;

    delete []pUnicode;
    return TRUE;
}

#define SAFE_DELETEA(p) { if(p != NULL) { delete[] (p);   (p) = NULL; } }   //Delete Arrary

static inline char* rs_format(const char* format, ...)
{
    static const int rs_format_length = 256;
    char* temp = new char[rs_format_length];
    va_list args;
    va_start(args, format);
    int length = vsnprintf_s(temp, rs_format_length-1, rs_format_length-1, format, args);
    va_end(args);

    if (length > 0) {
        temp[length] = '\0';
        return temp;
    } else {
        SAFE_DELETEA(temp);
        return NULL;
    }    
}
