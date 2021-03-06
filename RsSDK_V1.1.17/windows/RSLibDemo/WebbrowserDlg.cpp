// CWebbrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebbrowserDlg.h"


// CWebbrowserDlg dialog

IMPLEMENT_DYNAMIC(CWebbrowserDlg, CDialog)

CWebbrowserDlg::CWebbrowserDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CWebbrowserDlg::IDD, pParent)
    , init_over_(FALSE)
{

}

CWebbrowserDlg::~CWebbrowserDlg()
{
}

void CWebbrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EXPLORER1, web_);
}


BEGIN_MESSAGE_MAP(CWebbrowserDlg, CDialog)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CWebbrowserDlg message handlers

BOOL CWebbrowserDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    //web_.Navigate(_T("www.baidu.com"), NULL, NULL, NULL, NULL);

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CWebbrowserDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        CRect rect;
        GetClientRect(&rect);
        web_.MoveWindow(&rect);
    }
}

