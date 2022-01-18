
// RSLibDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "RSLibDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRSLibDemoApp

BEGIN_MESSAGE_MAP(CRSLibDemoApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRSLibDemoApp construction

CRSLibDemoApp::CRSLibDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CRSLibDemoApp object

CRSLibDemoApp theApp;
CTreeCtrl*    g_device_tree_ = NULL;
CLogInfoDlg*  g_dlg_log_info_ = NULL;
CString       g_appdata_path_;

// CRSLibDemoApp initialization

BOOL CRSLibDemoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

    AfxEnableControlContainer();

    Json::Value value;
    value.clear();
    /*
    //for your own p2p server
    value["vv main server addr"] = "www.helloworld.com";
    value["vv main server port"] = 8000;
    */
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_sdk_wrapper_init(param.c_str());

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    TCHAR common_dir[MAX_PATH] = {0};   
    SHGetSpecialFolderPath(NULL, common_dir , CSIDL_APPDATA, 0);
    g_appdata_path_.Format(_T("%s\\RSLibDemo\\"), common_dir);
    SHCreateDirectoryEx(NULL, g_appdata_path_, NULL);

    srand(time(NULL));
	CRSLibDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CRSLibDemoApp::ExitInstance()
{
    // TODO: Add your specialized code here and/or call the base class
    rs_sdk_wrapper_uninit(NULL);
    return CWinAppEx::ExitInstance();
}

void AddMsg(CString& msg) {
    if (g_dlg_log_info_)
        g_dlg_log_info_->AddMessage(msg);
}
