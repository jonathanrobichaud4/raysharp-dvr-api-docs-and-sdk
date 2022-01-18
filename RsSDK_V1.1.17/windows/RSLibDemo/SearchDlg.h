#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSearchDlg dialog
class CRSLibDemoDlg;
class CSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchDlg();

// Dialog Data
	enum { IDD = IDD_DLG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnLbnSelchangeListCtrl(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnRefresh();
    afx_msg void OnBnClickedBtnAdd();
    afx_msg void OnBnClickedBtnModify();
    afx_msg LRESULT OnSearchDone(WPARAM wparam, LPARAM lparam);
    DECLARE_MESSAGE_MAP()

public:
    void search_device_callback(const char* param);
    void SetParentWindow(CRSLibDemoDlg* parent);

    int                       cursel_;
    CListCtrl                 listctrl_;
    CComboBox                 combo_netmode_;
    CRSLibDemoDlg*            parent_;
    typedef struct {
        std::string* data;
        std::string  ip;
    }SearchDeviceInfo;
    std::vector<SearchDeviceInfo> vec_search_info_;
};
