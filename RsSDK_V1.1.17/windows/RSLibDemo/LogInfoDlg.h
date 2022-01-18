#pragma once
#include "afxcmn.h"


// CLogInfoDlg dialog

class CLogInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogInfoDlg)

public:
	CLogInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLogInfoDlg();

// Dialog Data
	enum { IDD = IDD_DLG_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

public:
    void AddMessage(CString& msg);

private:
    BOOL      init_over_;
    CListCtrl listctrl_log_;
};
