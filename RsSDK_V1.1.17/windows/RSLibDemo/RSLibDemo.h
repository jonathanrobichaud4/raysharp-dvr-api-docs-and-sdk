
// RSLibDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRSLibDemoApp:
// See RSLibDemo.cpp for the implementation of this class
//

class CLogInfoDlg;
class CRSLibDemoApp : public CWinAppEx
{
public:
	CRSLibDemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

void AddMsg(CString& msg);

extern CRSLibDemoApp theApp;
extern CTreeCtrl*    g_device_tree_;
extern CLogInfoDlg*  g_dlg_log_info_;
extern CString       g_appdata_path_;