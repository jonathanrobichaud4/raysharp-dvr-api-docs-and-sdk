#pragma once
#include "afxcmn.h"
#include "PlayWindow.h"
#include "RSSliderCtrl.h"

#define MAX_PLAYER_WINDOW    1

// CPlayerDlg dialog
class CRSLibDemoDlg;
class CPlayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlayerDlg)

public:
	CPlayerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayerDlg();

// Dialog Data
	enum { IDD = IDD_DLG_PLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnStart();
    afx_msg void OnBnClickedBtnStop();
    afx_msg void OnBnClickedBtnOpenSound();
    afx_msg void OnBnClickedBtnCloseSound();
    afx_msg void OnBnClickedBtnFile();
    afx_msg LRESULT OnSliderPosition(WPARAM wparam, LPARAM lparam);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
    void SetParentWindow(CRSLibDemoDlg* parent);
    void StopAll();
    int convert_utc_to_microsecond(const char* param);

    BOOL           init_over_;
    CRSLibDemoDlg* parent_;
    CRSSliderCtrl  slider_player_;
    CPlayWindow    window_[MAX_PLAYER_WINDOW];
    session_id     local_playback_sess_;
    int            slider_previous_pos_;

    int            begin_second_;
    int            end_second_;
};
