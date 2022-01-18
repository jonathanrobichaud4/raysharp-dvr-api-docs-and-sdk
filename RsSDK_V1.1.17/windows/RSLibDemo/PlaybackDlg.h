#pragma once
#include "PlayWindow.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

typedef struct _SEARCH_RECORD_INFO_ {
    session_id device_id;
    int        index;
}SEARCH_RECORD_INFO;

// CPlaybackDlg dialog
class CRSLibDemoDlg;
class CPlaybackDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlaybackDlg)

public:
	CPlaybackDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlaybackDlg();

// Dialog Data
	enum { IDD = IDD_DLG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLbnSelchangeListCtrl(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnSearchMonth();
    afx_msg void OnBnClickedBtnSearchDay();
    afx_msg void OnBnClickedBtnStart();
    afx_msg void OnBnClickedBtnStop();
    afx_msg void OnBnClickedBtnPause();
    afx_msg void OnBnClickedBtnCapture();
    afx_msg void OnBnClickedBtnStartRec();
    afx_msg void OnBnClickedBtnStopRec();
    afx_msg void OnBnClickedBtnSlow();
    afx_msg void OnBnClickedBtnFast();
    afx_msg void OnBnClickedBtnSeek();
    afx_msg void OnBnClickedBtnStartDownload();
    afx_msg void OnBnClickedBtnStopDownload();

	DECLARE_MESSAGE_MAP()

public:
    void StopAll();
    void SetParentWindow(CRSLibDemoDlg* parent);
    void search_record_month_callback(const char* param);
    void search_record_day_callback(const char* param);
    void download_callback(const char* param);
    void move_window(int index, int x, int y);

    BOOL                              init_over_;
    CRSLibDemoDlg*                    parent_;
    CListCtrl                         listctrl_record_;
    CComboBox                         combo_record_type_;
    CDateTimeCtrl                     month_picker_;
    CDateTimeCtrl                     seek_time_picker_;
    CPlayWindow                       window_[4];
    int                               cursel_;
    session_id                        playback_session_;
    session_id                        download_session_;

    session_id                        current_search_day_device_id_;
    session_id                        search_record_month_session_;
    session_id                        search_record_day_session_;
    int                               current_download_index_;
    std::map<int, SEARCH_RECORD_INFO> search_record_map_info_;

    session_id                        single_playback_session_[4];
};
