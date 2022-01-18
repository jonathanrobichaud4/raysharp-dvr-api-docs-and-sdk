
// RSLibDemoDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <vector>

#include "SearchDlg.h"
#include "PreviewDlg.h"
#include "PlaybackDlg.h"
#include "ConfigDlg.h"
#include "PlayerDlg.h"
#include "LogInfoDlg.h"
#include "MiniDumper.h"

// CRSLibDemoDlg dialog
class CRSLibDemoDlg : public CDialog
{
// Construction
public:
	CRSLibDemoDlg(CWnd* pParent = NULL);	// standard constructor
    ~CRSLibDemoDlg();

// Dialog Data
	enum { IDD = IDD_RSLIBDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
    afx_msg void OnClose();
    afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTcnSelchangeTabGlobal(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkTreeDev(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMRClickTreeDevice(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnStartpreview();
    afx_msg void OnStoppreview();
    afx_msg void OnStartTalk();
    afx_msg void OnStopTalk();
    afx_msg void OnMainStream();
    afx_msg void OnSubStream();
    DECLARE_MESSAGE_MAP()
    
public:
    void InitDevice(DEVICE_INFO* info);
    void AddDevice(CString& str_ip, CString& str_port, CString& str_name, CString& str_password, CString ip_type = _T("ip"));
    void LoginDevice(DEVICE_INFO* info);
    void LogOutDevice(DEVICE_INFO* info);

    void connction_callback(const char* param, DEVICE_INFO* info);//not thread safe
    void alarm_callback(const char* alarm_type, const char* param, DEVICE_INFO* info);//not thread safe
    BOOL InitOver() { return init_over_; }

private:
    void ReadDeviceInfo();
    void WriteDeviceInfo();

    BOOL                      init_over_;
    CImageList                image_list_;
    CTreeCtrl                 treectrl_device_;

    CTabCtrl                  tabctrl_;
    CSearchDlg                search_dlg_;
    CPreviewDlg               preview_dlg_;
    CPlaybackDlg              playback_dlg_;
    CConfigDlg                config_dlg_;
    CPlayerDlg                player_dlg_;
    CLogInfoDlg               log_dlg_;
    std::vector<CDialog*>     vec_dialog_;

    rs_app_mutex              mutex_;
    std::vector<DEVICE_INFO*> vec_info_;

	CMiniDumper               dump_;
    session_id                human_face_alarm_id_;
    session_id                human_face_param_id_;
};
