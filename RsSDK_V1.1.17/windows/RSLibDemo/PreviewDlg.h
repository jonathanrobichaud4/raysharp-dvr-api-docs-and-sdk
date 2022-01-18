#pragma once
#include "afxcmn.h"
#include "PlayWindow.h"
#include "afxwin.h"

#define MAX_PREIVEW_WINDOW    36

class CPreviewDlg;
typedef struct {
    CPreviewDlg* _this;
    int          _index;
}DRAW_CALLBACK_INFO;

// CPreviewDlg dialog
class CRSLibDemoDlg;
class CPreviewDlg : public CDialog
{
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	CPreviewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPreviewDlg();

// Dialog Data
	enum { IDD = IDD_DLG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnCapture();
    afx_msg void OnBnClickedBtnStartRec();
    afx_msg void OnBnClickedBtnStopRec();
    afx_msg void OnBnClickedBtnOpen();
    afx_msg void OnCbnSelchangeComboFisheye();
    afx_msg void OnBnClickedBtnCaptureFromDevice();
	afx_msg void OnBnClickedBtnCaptureToBuf();

	DECLARE_MESSAGE_MAP()

public:
    void SetParentWindow(CRSLibDemoDlg* parent);
    void StartPreview(DEVICE_INFO* info);
    void StopPreview(DEVICE_INFO* info);
    void StopAll(BOOL update_init_over_value = TRUE);
    void SetCurSel(CPlayWindow* window);
    void SetDoubleClick(CPlayWindow* window);
    void alarm_callback(const char* alarm_type, const char* param, DEVICE_INFO* info);
    BOOL IsFisheyeMode();
    void draw(int index);
    void move_window(int index, int x, int y);

    BOOL               init_over_;
    CRSLibDemoDlg*     parent_;
    rs_app_mutex       mutex_;
    CListCtrl          listctrl_alarm_;
    CComboBox          combo_fisheye_;
    CComboBox          combo_capture_type_;
    CComboBox          combo_record_type_;
    CPlayWindow        window_[MAX_PREIVEW_WINDOW];
    session_id         preview_session_[MAX_PREIVEW_WINDOW];
    DRAW_CALLBACK_INFO draw_callback_info_[MAX_PREIVEW_WINDOW];
    session_id         picture_id_[MAX_PREIVEW_WINDOW];
    session_id         picture_id2_[MAX_PREIVEW_WINDOW];
};
