#pragma once
#include "afxwin.h"
#include "StaticWnd.h"

// CPlayWindow dialog
class CPreviewDlg;
class CPlayWindow : public CDialog
{
	DECLARE_DYNAMIC(CPlayWindow)

public:
	CPlayWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayWindow();

// Dialog Data
	enum { IDD = IDD_DLG_WINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
    afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()

public:
    HWND GetWindow() { return GetDlgItem(IDC_STATIC_WND)->GetSafeHwnd(); }
    void SetParent(CPreviewDlg* parent);
    void InvalidWnd() { GetDlgItem(IDC_STATIC_WND)->Invalidate(); }
    void SetDeviceInfo(DEVICE_INFO* info) { info_ = info; }
    DEVICE_INFO* GetDeviceInfo() { return info_; }
    void SetPlaySession(session_id play_id) { play_id_ = play_id; }

    BOOL         init_over_;
    BOOL         checked_;
    CStaticWnd   static_wnd_;
    CPreviewDlg* parent_;
    DEVICE_INFO* info_;
    session_id   play_id_;
};
