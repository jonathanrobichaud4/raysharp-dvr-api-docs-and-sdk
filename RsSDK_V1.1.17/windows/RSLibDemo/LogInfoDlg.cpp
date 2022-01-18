// LogInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "LogInfoDlg.h"


// CLogInfoDlg dialog

IMPLEMENT_DYNAMIC(CLogInfoDlg, CDialog)

CLogInfoDlg::CLogInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogInfoDlg::IDD, pParent)
    , init_over_(FALSE)
{

}

CLogInfoDlg::~CLogInfoDlg()
{
}

void CLogInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, listctrl_log_);
}


BEGIN_MESSAGE_MAP(CLogInfoDlg, CDialog)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CLogInfoDlg message handlers

BOOL CLogInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    listctrl_log_.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    listctrl_log_.InsertColumn(0, _T("Time"), LVCFMT_LEFT, 120);
    listctrl_log_.InsertColumn(1, _T("Info"), LVCFMT_LEFT, 560);
    
    g_dlg_log_info_ = this;

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogInfoDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        CRect rect;
        GetClientRect(&rect);
        listctrl_log_.MoveWindow(&rect);
    }
}

void CLogInfoDlg::AddMessage(CString& msg) {
    CString str_time;
    CTime tm = CTime::GetCurrentTime();
    str_time = tm.Format(_T("%Y-%m-%d %X"));

    int count = listctrl_log_.GetItemCount();
    int item = listctrl_log_.InsertItem(count, str_time);
    listctrl_log_.SetItemText(item, 1, msg);
}
