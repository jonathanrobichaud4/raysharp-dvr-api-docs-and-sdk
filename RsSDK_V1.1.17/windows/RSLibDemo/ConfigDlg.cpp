// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "ConfigDlg.h"
#include "RSLibDemoDlg.h"


// CConfigDlg dialog

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
    , parent_(NULL)
    , init_over_(FALSE)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BTN_QUERY, &CConfigDlg::OnBnClickedBtnQuery)
    ON_BN_CLICKED(IDC_BTN_SET, &CConfigDlg::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_LIVE_CHANNEL, &CConfigDlg::OnBnClickedBtnLiveChannel)
    ON_BN_CLICKED(IDC_BTNUPGRADE, &CConfigDlg::OnBnClickedBtnupgrade)
	ON_BN_CLICKED(IDC_BTN_USER, &CConfigDlg::OnBnClickedBtnUser)
	ON_BN_CLICKED(IDC_BTN_HDD, &CConfigDlg::OnBnClickedBtnHdd)
    ON_BN_CLICKED(IDC_BTN_JSON, &CConfigDlg::OnBnClickedBtnJson)
    ON_BN_CLICKED(IDC_BTN_HUMAN_ALARM, &CConfigDlg::OnBnClickedBtnHumanAlarm)
    ON_BN_CLICKED(IDC_BTN_HUMAN_PARAM, &CConfigDlg::OnBnClickedBtnHumanParam)
END_MESSAGE_MAP()


// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    if (web_dlg_.GetSafeHwnd() == NULL) {
        web_dlg_.Create(CWebbrowserDlg::IDD, this);
        web_dlg_.ShowWindow(SW_SHOW);
    }

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        int width = 0;
        int height = 0;
        CRect rect_temp;
        CRect rect_client;
        GetClientRect(&rect_client);

        GetDlgItem(IDC_GROUP_LEFT)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        rect_temp.bottom = rect_client.bottom - 10;
        GetDlgItem(IDC_GROUP_LEFT)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_GROUP_RIGHT)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        rect_temp.bottom = rect_client.bottom - 10;
        rect_temp.right = rect_client.right - 10;
        GetDlgItem(IDC_GROUP_RIGHT)->MoveWindow(&rect_temp);

        rect_temp.DeflateRect(10, 10, 10, 10);
        web_dlg_.MoveWindow(&rect_temp);
    }
}

void CConfigDlg::SetParentWindow(CRSLibDemoDlg* parent) {
    parent_ = parent;
}

BOOL CConfigDlg::BindDeviceInfo()
{
    device_id dev = 0;
    DEVICE_INFO* channel_info = NULL;
    HTREEITEM item = g_device_tree_->GetSelectedItem();
    if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_CHANNEL) {
        dev = channel_info->device_info->device_session;
    } else if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_DEVICE) {
        dev = channel_info->device_session;
    }
    if (dev == 0) {
        MessageBox(_T("Please select at one device"), NULL, MB_OK | MB_ICONERROR);
        return FALSE;
    }

    return FALSE;
}

void CConfigDlg::OnBnClickedBtnQuery()
{
    // TODO: Add your control notification handler code here
    device_id dev = 0;
    DEVICE_INFO* channel_info = NULL;
    HTREEITEM item = g_device_tree_->GetSelectedItem();
    if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_CHANNEL) {
        dev = channel_info->device_info->device_session;
    } else if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_DEVICE) {
        dev = channel_info->device_session;
    }
    if (dev == 0) {
        MessageBox(_T("Please select at one device"), NULL, MB_OK | MB_ICONERROR);
        return;
    }
}

void CConfigDlg::OnBnClickedBtnSet()
{
    // TODO: Add your control notification handler code here
    device_id dev = 0;
    DEVICE_INFO* channel_info = NULL;
    HTREEITEM item = g_device_tree_->GetSelectedItem();
    if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_CHANNEL) {
        dev = channel_info->device_info->device_session;
    } else if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_DEVICE) {
        dev = channel_info->device_session;
    }
    if (dev == 0) {
        MessageBox(_T("Please select at one device"), NULL, MB_OK | MB_ICONERROR);
        return;
    }
}

void CConfigDlg::OnBnClickedBtnLiveChannel()
{
    // TODO: Add your control notification handler code here
}

void CConfigDlg::OnBnClickedBtnupgrade()
{
    // TODO: Add your control notification handler code here
}

void CConfigDlg::OnBnClickedBtnUser()
{
    // TODO: Add your control notification handler code here
}

void CConfigDlg::OnBnClickedBtnHdd()
{
    // TODO: Add your control notification handler code here
}

void CConfigDlg::OnBnClickedBtnJson()
{
    // TODO: Add your control notification handler code here
}

void CConfigDlg::OnBnClickedBtnHumanAlarm()
{
    // TODO: Add your control notification handler code here
}

void CConfigDlg::OnBnClickedBtnHumanParam()
{
    // TODO: Add your control notification handler code here
}
