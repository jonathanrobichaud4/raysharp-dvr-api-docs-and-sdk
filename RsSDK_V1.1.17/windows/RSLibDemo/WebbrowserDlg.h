#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "CWebBrowser.h"

// CWebbrowserDlg dialog

class CWebbrowserDlg : public CDialog
{
	DECLARE_DYNAMIC(CWebbrowserDlg)

public:
	CWebbrowserDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CWebbrowserDlg();

// Dialog Data
	enum { IDD = IDD_DLG_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
    BOOL        init_over_;
    CWebBrowser web_;
};
