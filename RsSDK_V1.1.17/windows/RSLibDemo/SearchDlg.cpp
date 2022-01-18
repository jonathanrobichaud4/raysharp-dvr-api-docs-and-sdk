// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "SearchDlg.h"
#include "RSLibDemoDlg.h"
#include <algorithm>

#define WM_SEARCH_DONE (WM_USER+200)

// CSearchDlg dialog

IMPLEMENT_DYNAMIC(CSearchDlg, CDialog)

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
    , parent_(NULL)
    , cursel_(-1)
{

}

CSearchDlg::~CSearchDlg()
{
    for (size_t i = 0; i < vec_search_info_.size(); i++)
        delete vec_search_info_.at(i).data;
    vec_search_info_.clear();
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DEVICE, listctrl_);
    DDX_Control(pDX, IDC_COMBO_NET_MODE, combo_netmode_);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
    ON_NOTIFY(NM_CLICK, IDC_LIST_DEVICE, &CSearchDlg::OnLbnSelchangeListCtrl)
    ON_BN_CLICKED(IDC_BTN_ADD, &CSearchDlg::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_REFRESH, &CSearchDlg::OnBnClickedBtnRefresh)
    ON_BN_CLICKED(IDC_BTN_MODIFY, &CSearchDlg::OnBnClickedBtnModify)
    ON_MESSAGE(WM_SEARCH_DONE, &CSearchDlg::OnSearchDone)
END_MESSAGE_MAP()


// CSearchDlg message handlers

void RSNET_CALL search_device_callback_fun(const char* param, void* user_param) {
    CSearchDlg* this_ = (CSearchDlg*)(user_param);
    if (this_)
        this_->search_device_callback(param);
}

BOOL CSearchDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    listctrl_.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
    listctrl_.InsertColumn(0, _T("No."), LVCFMT_CENTER, 50);
    listctrl_.InsertColumn(1, _T("IP"), LVCFMT_CENTER, 120);
    listctrl_.InsertColumn(2, _T("Media Port"), LVCFMT_CENTER,80);
    listctrl_.InsertColumn(3, _T("Web Port"), LVCFMT_CENTER, 80);
    listctrl_.InsertColumn(4, _T("Channel"), LVCFMT_CENTER, 80);
    listctrl_.InsertColumn(5, _T("Net Mode"), LVCFMT_CENTER, 80);
    listctrl_.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

    SetDlgItemText(IDC_EDIT_NAME, _T("admin"));
    SetDlgItemText(IDC_EDIT_PASSWORD, _T("admin"));

    combo_netmode_.AddString(_T("dhcp"));
    combo_netmode_.AddString(_T("static"));
    combo_netmode_.SetCurSel(0);

    OnBnClickedBtnRefresh();
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchDlg::OnLbnSelchangeListCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    cursel_ = pNMListView->iItem;
    SetDlgItemText(IDC_EDIT_IP, listctrl_.GetItemText(cursel_, 1));
    SetDlgItemText(IDC_EDIT_PORT, listctrl_.GetItemText(cursel_, 2));
    SetDlgItemText(IDC_EDIT_WEB_PORT, listctrl_.GetItemText(cursel_, 3));

    CString str_net_mode;
    listctrl_.GetItemText(cursel_, 4);
    if (str_net_mode.CompareNoCase(_T("dhcp")) == 0) {
        combo_netmode_.SetCurSel(0);
    }else{
        combo_netmode_.SetCurSel(1);
    }
}

void CSearchDlg::search_device_callback(const char* param) {
    if (param) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err))
            return;

        SearchDeviceInfo info;
        info.data = new std::string(param);
        info.ip = value["ip"].asCString();
        vec_search_info_.push_back(info);
    }else{
        ::PostMessage(this->GetSafeHwnd(), WM_SEARCH_DONE, NULL, NULL);
    }
}

void CSearchDlg::SetParentWindow(CRSLibDemoDlg* parent) {
    parent_ = parent;
}

void CSearchDlg::OnBnClickedBtnRefresh()
{
    // TODO: Add your control notification handler code here
    GetDlgItem(IDC_BTN_REFRESH)->EnableWindow(FALSE);

    for (size_t i = 0; i < vec_search_info_.size(); i++)
        delete vec_search_info_.at(i).data;
    vec_search_info_.clear();
    cursel_ = -1;
    listctrl_.DeleteAllItems();

    Json::Value value;
    value.clear();
    value["oem type"] = "default";
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_error_code err = rs_search_device(param.c_str(), search_device_callback_fun, this);
    TRACE("======<rs_search_device> result:%d\n", err);
}

void CSearchDlg::OnBnClickedBtnAdd()
{
    // TODO: Add your control notification handler code here
    CString str_ip, str_port, str_name, str_password;
    GetDlgItemText(IDC_EDIT_IP, str_ip);
    GetDlgItemText(IDC_EDIT_PORT, str_port);
    GetDlgItemText(IDC_EDIT_NAME, str_name);
    GetDlgItemText(IDC_EDIT_PASSWORD, str_password);

    if (str_ip.IsEmpty() || str_port.IsEmpty() || str_name.IsEmpty())
        return;

    if (parent_) {
        CString ip_type = _T("ip");
        if (str_ip.Find(_T('.')) == -1) {
            CString left3 = str_ip.Left(3);
            if (left3.CompareNoCase(_T("rsv")) == 0) {
                ip_type = _T("rsvv");
            } else if (str_ip.GetLength() == 16 || str_ip.GetLength() == 17) {
                ip_type = _T("vv");
            } else {
                ip_type = _T("tutk");
            }
        }
        parent_->AddDevice(str_ip, str_port, str_name, str_password, ip_type);
    }
}

void CSearchDlg::OnBnClickedBtnModify()
{
    // TODO: Add your control notification handler code here
    CString str_ip, str_port, str_name, str_password, str_web_port;
    GetDlgItemText(IDC_EDIT_IP, str_ip);
    GetDlgItemText(IDC_EDIT_PORT, str_port);
    GetDlgItemText(IDC_EDIT_NAME, str_name);
    GetDlgItemText(IDC_EDIT_PASSWORD, str_password);
    GetDlgItemText(IDC_EDIT_WEB_PORT, str_web_port);

    if (str_ip.IsEmpty() || str_port.IsEmpty() || str_name.IsEmpty() || str_web_port.IsEmpty() || cursel_ == -1)
        return;

    std::string* data = (std::string*)listctrl_.GetItemData(cursel_);
    if (data) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, data->c_str(), &value, &err))
            return;

        Json::Value _value;
        _value.clear();

        _value["user"] = std::string(CT2CA(str_name));
        _value["password"] = std::string(CT2CA(str_password));
        _value["original ip"] = value["ip"].asString();
        _value["change ip"] = std::string(CT2CA(str_ip));
        _value["netmask"] = value["netmask"].asString();
        _value["gateway"] = value["gateway"].asString();
        _value["dns1"] = value["dns1"].asString();
        _value["dns2"] = value["dns2"].asString();
        _value["mac addr"] = value["mac addr"].asString();
        _value["device type ull"] = value["device type ull"].asUInt64();
        _value["media port"] = _ttoi(str_port);
        _value["web port"] = _ttoi(str_web_port);
        if (combo_netmode_.GetCurSel() == 0)
            _value["network mode"] = "dhcp";
        else
            _value["network mode"] = "static";

        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, _value);
        rs_error_code error_code = rs_modify_device(param.c_str());
        TRACE("======<rs_modify_device> result:%d\n", error_code);

        if (error_code == rs_success) {
            MessageBox(_T("Modify Device Success"), NULL, MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(_T("Modify Device Failed"), NULL, MB_OK | MB_ICONERROR);
        }
    }
}

LRESULT CSearchDlg::OnSearchDone(WPARAM wparam, LPARAM lparam) {
    if (!vec_search_info_.empty()) {
        struct {
            bool operator()(const SearchDeviceInfo& a, const SearchDeviceInfo& b) const {
                u_long temp_a = htonl(inet_addr(a.ip.c_str()));
                u_long temp_b = htonl(inet_addr(b.ip.c_str()));
                return temp_a < temp_b ? true : false;
            }
        }custom_compare;
        std::sort(vec_search_info_.begin(), vec_search_info_.end(), custom_compare);
    }

    for (size_t i = 0; i < vec_search_info_.size(); i++) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, vec_search_info_.at(i).data->c_str(), &value, &err)) {
            GetDlgItem(IDC_BTN_REFRESH)->EnableWindow(TRUE);
            return 0;
        }

        int count = listctrl_.GetItemCount();
        CString str_item, str_ip, str_media_port, str_web_port, str_channel, str_net_mode;
        str_item.Format(_T("%d"), count);
        str_ip = CA2CT(value["ip"].asCString());
        str_media_port.Format(_T("%d"), value["media port"].asInt());
        str_web_port.Format(_T("%d"), value["web port"].asInt());
        str_channel.Format(_T("%d"), value["channel number"].asInt());
        str_net_mode = CA2CT(value["network mode"].asCString());

        int item = listctrl_.InsertItem(count, str_item);
        listctrl_.SetItemText(item, 1, str_ip);
        listctrl_.SetItemText(item, 2, str_media_port);
        listctrl_.SetItemText(item, 3, str_web_port);
        listctrl_.SetItemText(item, 4, str_channel);
        listctrl_.SetItemText(item, 5, str_net_mode);


        listctrl_.SetItemData(item, (DWORD_PTR)vec_search_info_.at(i).data);
    }

    GetDlgItem(IDC_BTN_REFRESH)->EnableWindow(TRUE);
    return 0;
}
