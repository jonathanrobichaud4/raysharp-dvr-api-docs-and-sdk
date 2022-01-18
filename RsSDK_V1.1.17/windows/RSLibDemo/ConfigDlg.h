#pragma once
#include "CWebBrowser.h"
#include "WebbrowserDlg.h"

// CConfigDlg dialog
class CRSLibDemoDlg;
class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnQuery();
    afx_msg void OnBnClickedBtnSet();
    afx_msg void OnBnClickedBtnLiveChannel();
    afx_msg void OnBnClickedBtnupgrade();
    afx_msg void OnBnClickedBtnUser();
    afx_msg void OnBnClickedBtnHdd();
    afx_msg void OnBnClickedBtnJson();
    afx_msg void OnBnClickedBtnHumanAlarm();
    afx_msg void OnBnClickedBtnHumanParam();
	DECLARE_MESSAGE_MAP()

public:
    void SetParentWindow(CRSLibDemoDlg* parent);
    BOOL BindDeviceInfo();

    BOOL                  init_over_;
    CRSLibDemoDlg*        parent_;
    CWebbrowserDlg        web_dlg_;
};
