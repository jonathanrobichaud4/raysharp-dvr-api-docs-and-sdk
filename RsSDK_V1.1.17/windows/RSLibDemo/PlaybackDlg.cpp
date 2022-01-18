// PlaybackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "PlaybackDlg.h"
#include "RSLibDemoDlg.h"


//#define SYNC_PLAYBACK_TEST

// CPlaybackDlg dialog

IMPLEMENT_DYNAMIC(CPlaybackDlg, CDialog)

int global_check_index[] = { IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4, IDC_CHECK5, IDC_CHECK6, \
                             IDC_CHECK7, IDC_CHECK8, IDC_CHECK9, IDC_CHECK10, IDC_CHECK11, IDC_CHECK12, \
                             IDC_CHECK13, IDC_CHECK14, IDC_CHECK15, IDC_CHECK16, IDC_CHECK17, IDC_CHECK18, \
                             IDC_CHECK19, IDC_CHECK20, IDC_CHECK21, IDC_CHECK22, IDC_CHECK23, IDC_CHECK24, \
                             IDC_CHECK25, IDC_CHECK26, IDC_CHECK27, IDC_CHECK28, IDC_CHECK29, IDC_CHECK30, \
                             IDC_CHECK31};

static const char* playback_mode[] = {
    "16 times slower",
    "8 times slower",
    "4 times slower",
    "2 times slower",
    "normal",
    "2 times faster",
    "4 times faster",
    "8 times faster",
    "16 times faster"
};

CPlaybackDlg::CPlaybackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlaybackDlg::IDD, pParent)
    , parent_(NULL)
    , init_over_(FALSE)
    , cursel_(-1)
    , playback_session_(0)
    , download_session_(0)
    , current_search_day_device_id_(0)
    , search_record_month_session_(0)
    , search_record_day_session_(0)
    , current_download_index_(-1)
{
    memset(&single_playback_session_, 0, sizeof(single_playback_session_));
}

CPlaybackDlg::~CPlaybackDlg()
{
}

void CPlaybackDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DOWNLOAD, listctrl_record_);
    DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, combo_record_type_);
    DDX_Control(pDX, IDC_MONTH_PICKER, month_picker_);
    DDX_Control(pDX, IDC_TIME_PICKER, seek_time_picker_);
}


BEGIN_MESSAGE_MAP(CPlaybackDlg, CDialog)
    ON_WM_SIZE()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_DOWNLOAD, &CPlaybackDlg::OnLbnSelchangeListCtrl)
    ON_BN_CLICKED(IDC_BTN_SEARCH_MONTH, &CPlaybackDlg::OnBnClickedBtnSearchMonth)
    ON_BN_CLICKED(IDC_BTN_SEARCH_DAY, &CPlaybackDlg::OnBnClickedBtnSearchDay)
    ON_BN_CLICKED(IDC_BTN_START, &CPlaybackDlg::OnBnClickedBtnStart)
    ON_BN_CLICKED(IDC_BTN_STOP, &CPlaybackDlg::OnBnClickedBtnStop)
    ON_BN_CLICKED(IDC_BTN_PAUSE, &CPlaybackDlg::OnBnClickedBtnPause)
    ON_BN_CLICKED(IDC_BTN_CAPTURE, &CPlaybackDlg::OnBnClickedBtnCapture)
    ON_BN_CLICKED(IDC_BTN_START_REC, &CPlaybackDlg::OnBnClickedBtnStartRec)
    ON_BN_CLICKED(IDC_BTN_STOP_REC, &CPlaybackDlg::OnBnClickedBtnStopRec)
    ON_BN_CLICKED(IDC_BTN_SLOW, &CPlaybackDlg::OnBnClickedBtnSlow)
    ON_BN_CLICKED(IDC_BTN_FAST, &CPlaybackDlg::OnBnClickedBtnFast)
    ON_BN_CLICKED(IDC_BTN_SEEK, &CPlaybackDlg::OnBnClickedBtnSeek)
    ON_BN_CLICKED(IDC_BTN_START_DOWNLOAD, &CPlaybackDlg::OnBnClickedBtnStartDownload)
    ON_BN_CLICKED(IDC_BTN_STOP_DOWNLOAD, &CPlaybackDlg::OnBnClickedBtnStopDownload)
END_MESSAGE_MAP()


// CPlaybackDlg message handlers

BOOL CPlaybackDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    for (int i = 0; i < _countof(window_); i++) {
        if (window_[i].GetSafeHwnd() == NULL) {
            window_[i].Create(CPlayWindow::IDD, GetDlgItem(IDC_STATIC_PLAYBACK_WND));
        }
    }
    
    int index = 0;
    combo_record_type_.InsertString(index++, _T("Normal"));
    combo_record_type_.InsertString(index++, _T("Motion"));
    combo_record_type_.InsertString(index++, _T("All"));
    combo_record_type_.SetCurSel(combo_record_type_.GetCount()-1);

    listctrl_record_.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES|LVS_EX_CHECKBOXES);
    listctrl_record_.InsertColumn(0, _T(""), LVCFMT_CENTER, 28);
    listctrl_record_.InsertColumn(1, _T("No."), LVCFMT_CENTER, 50);
    listctrl_record_.InsertColumn(2, _T("Time"), LVCFMT_CENTER,250);
    listctrl_record_.InsertColumn(3, _T("Size"), LVCFMT_CENTER, 100);
    listctrl_record_.InsertColumn(4, _T("Type"), LVCFMT_CENTER, 88);
    listctrl_record_.InsertColumn(5, _T("Progress"), LVCFMT_CENTER, 120);

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlaybackDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        int width = 0;
        int height = 0;
        CRect rect_client;
        GetClientRect(&rect_client);

        CRect rect_temp;
        GetDlgItem(IDC_STATIC_PLAYBACK_WND)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        rect_temp.right = rect_client.right - 96;
        rect_temp.bottom = rect_client.bottom - 230;
        GetDlgItem(IDC_STATIC_PLAYBACK_WND)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_STATIC_DAY_SEARCH)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.bottom = rect_client.bottom - 14;
        rect_temp.right = rect_client.right - 12;
        rect_temp.top = rect_temp.bottom - height;
        GetDlgItem(IDC_STATIC_DAY_SEARCH)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_LIST_DOWNLOAD)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.bottom = rect_client.bottom - 46;
        rect_temp.right = rect_client.right - 23;
        rect_temp.top = rect_temp.bottom - height;
        GetDlgItem(IDC_LIST_DOWNLOAD)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_STATIC_MONTH_SEARCH)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.bottom = rect_client.bottom - 221;
        GetDlgItem(IDC_STATIC_MONTH_SEARCH)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_STATIC_PLAYBACK_CONTROL)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.right = rect_client.right - 8;
        rect_temp.bottom = rect_client.bottom - 221;
        GetDlgItem(IDC_STATIC_PLAYBACK_CONTROL)->MoveWindow(&rect_temp);

        CRect rect;
        GetDlgItem(IDC_STATIC_PLAYBACK_WND)->GetClientRect(&rect);
#ifndef SYNC_PLAYBACK_TEST
        for (int i = 0; i < _countof(window_); i++) {
            window_[i].MoveWindow(&rect);
            if (i == 0)
                window_[i].ShowWindow(SW_SHOW);
            else
                window_[i].ShowWindow(SW_HIDE);
        }
#else
        int window_count = _countof(window_);
        int count = 2;
        if (window_count <= 4) {
            count = 2;
        } else if (window_count <= 9) {
            count = 3;
        } else if (window_count <= 16) {
            count = 4;
        } else if (window_count <= 25) {
            count = 5;
        } else if (window_count <= 36) {
            count = 6;
        } else {
            MessageBox(_T("Too many preview window"), NULL, MB_OK | MB_ICONERROR);
            return;
        }

        std::vector<CRect> vec_rect;
        int minx = rect.Width()/count;
        int miny = rect.Height()/count;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                CRect rect_temp;
                rect_temp.left = rect.left + j * minx;
                rect_temp.right = rect_temp.left + minx;
                rect_temp.top = rect.top + i * miny;
                rect_temp.bottom = rect_temp.top + miny;
                vec_rect.push_back(rect_temp);
            }
        }

        for (int i = 0; i < window_count; i++) {
            window_[i].MoveWindow(vec_rect.at(i));
            window_[i].ShowWindow(SW_SHOW);
        }
#endif

        move_window(IDC_BTN_SEARCH_DAY, 0, -18);
        move_window(IDC_BTN_START_DOWNLOAD, 0, -18);
        move_window(IDC_BTN_STOP_DOWNLOAD, 0, -18);

        move_window(IDC_BTN_START, -16, 0);
        move_window(IDC_BTN_STOP, -16, 0);
        move_window(IDC_BTN_PAUSE, -16, 0);
        move_window(IDC_BTN_CAPTURE, -16, 0);
        move_window(IDC_BTN_START_REC, -16, 0);
        move_window(IDC_BTN_STOP_REC, -16, 0);
        move_window(IDC_BTN_SLOW, -58, 0);
        move_window(IDC_BTN_FAST, -16, 0);
        move_window(IDC_STATIC_INFO, -16, 0);
        move_window(IDC_TIME_PICKER, -16, 0);
        move_window(IDC_BTN_SEEK, -16, 0);
    }
}

void CPlaybackDlg::StopAll() {
    init_over_ = FALSE;

    if (search_record_month_session_) {
        rs_stop_search_record(search_record_month_session_);
        search_record_month_session_ = NULL;
    }
    if (search_record_day_session_) {
        rs_stop_search_record(search_record_day_session_);
        search_record_day_session_ = NULL;
    }
    current_search_day_device_id_ = NULL;

    OnBnClickedBtnStop();
    OnBnClickedBtnStopRec();
    OnBnClickedBtnStopDownload();
}

void CPlaybackDlg::SetParentWindow(CRSLibDemoDlg* parent) {
    parent_ = parent;
}

void CPlaybackDlg::OnLbnSelchangeListCtrl(NMHDR *pNMHDR, LRESULT *pResult) {
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int cursel = pNMListView->iItem;
    OnBnClickedBtnStop();
    cursel_ = cursel;
    OnBnClickedBtnStart();
}
static void RSNET_CALL search_record_month_callback_fun(const char* param, void* user_param) {
    TRACE("======search record month callback reuslt:%s\n", param ? param : "seach done");
    CPlaybackDlg* this_ = (CPlaybackDlg*)user_param;
    if (param && this_) {
        this_->search_record_month_callback(param);
    }
}

void CPlaybackDlg::search_record_month_callback(const char* param) {
    if (param == NULL)
        return;

    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return;

    int month = value["day"].asInt(); month--;
    if (month < _countof(global_check_index))
        ((CButton*)(GetDlgItem(global_check_index[month])))->SetCheck(1);
}

void CPlaybackDlg::OnBnClickedBtnSearchMonth()
{
    // TODO: Add your control notification handler code here
    for (int i = 0; i < _countof(global_check_index); i++)
        ((CButton*)(GetDlgItem(global_check_index[i])))->SetCheck(0);

    DEVICE_INFO* channel_info = NULL;
    HTREEITEM item = g_device_tree_->GetSelectedItem();
    if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_CHANNEL) {
        COleDateTime data_time;
        month_picker_.GetTime(data_time);

        char temp_time[32] = {0};
        sprintf(temp_time, "%04d-%02d", data_time.GetYear(), data_time.GetMonth());
        char temp_channel[32] = {0};
        sprintf(temp_channel, "%d", channel_info->channel);

        int device_type = rs_get_device_type(channel_info->device_info->device_session);
        unsigned int record_type = AllRecord;
        switch (combo_record_type_.GetCurSel())
        {
        case 0:
            record_type = NormalRecord;
            if (device_type == 4)
                record_type = NormalRec;
        	break;
        case 1:
            record_type = MotionRecord;
            if (device_type == 4)
                record_type = MotionRec;
            break;
        case 2:
            record_type = AllRecord;
            break;
        default:
            break;
        }

        Json::Value value;
        value.clear();
        value["channel"] = temp_channel;
        value["stream type"] = "main stream";
        value["record type"] = record_type;
        value["time"] = temp_time;

        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_stop_search_record(search_record_month_session_);
        search_record_month_session_ = rs_search_record_by_month(channel_info->device_info->device_session, param.c_str(), search_record_month_callback_fun, this);
        TRACE("======<rs_search_record_by_month> result:%d\n", search_record_month_session_);
    }
}

static void RSNET_CALL search_record_day_callback_fun(const char* param, void* user_param) {
    CPlaybackDlg* this_ = (CPlaybackDlg*)user_param;
    if (param && this_) {
        this_->search_record_day_callback(param);
    }
}

void CPlaybackDlg::search_record_day_callback(const char* param) {
    if (param == NULL)
        return;

    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return;

    int count = listctrl_record_.GetItemCount();
    CString str_item, str_time, str_size, str_type;
    str_item.Format(_T("%d"), count);
    str_time = CA2CT(value["time"].asCString());
    double size = 1.0 * value["size"].asInt() / 1024 / 1024;
    str_size.Format(_T("%.02fM"), size);
    str_type.Format(_T("%d"), value["type"].asUInt());

    int item = listctrl_record_.InsertItem(count, _T(""));
    listctrl_record_.SetItemText(item, 1, str_item);
    listctrl_record_.SetItemText(item, 2, str_time);
    listctrl_record_.SetItemText(item, 3, str_size);
    listctrl_record_.SetItemText(item, 4, str_type);
    
    SEARCH_RECORD_INFO info = {0};
    info.device_id = current_search_day_device_id_;
    info.index = value["index"].asInt();
    search_record_map_info_.insert(std::make_pair(item, info));
}

void CPlaybackDlg::OnBnClickedBtnSearchDay()
{
    // TODO: Add your control notification handler code here
    DEVICE_INFO* channel_info = NULL;
    HTREEITEM item = g_device_tree_->GetSelectedItem();
    if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_CHANNEL) {
        COleDateTime data_time;
        month_picker_.GetTime(data_time);

        char begin_time[128] = {0};
        sprintf(begin_time, "%04d-%02d-%02d 00:00:00", data_time.GetYear(), data_time.GetMonth(), data_time.GetDay());
        char end_time[128] = {0};
        sprintf(end_time, "%04d-%02d-%02d 23:59:59", data_time.GetYear(), data_time.GetMonth(), data_time.GetDay());

        int device_type = rs_get_device_type(channel_info->device_info->device_session);
        unsigned int record_type = AllRecord;
        switch (combo_record_type_.GetCurSel())
        {
        case 0:
            record_type = NormalRecord;
            if (device_type == 4)
                record_type = NormalRec;
            break;
        case 1:
            record_type = MotionRecord;
            if (device_type == 4)
                record_type = MotionRec;
            break;
        case 2:
            record_type = AllRecord;
            break;
        default:
            break;
        }

        Json::Value value;
        value.clear();
        value["channel"] = channel_info->channel;
        value["stream type"] = "main stream";
        value["record type"] = record_type;
        value["begin time"] = begin_time;
        value["end time"] = end_time;
        value["detail info"] = false;

        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_stop_search_record(search_record_day_session_);

        listctrl_record_.DeleteAllItems();
        search_record_map_info_.clear();

        current_search_day_device_id_ = channel_info->device_info->device_session;
        search_record_day_session_ = rs_search_record_by_day(current_search_day_device_id_, param.c_str(), search_record_day_callback_fun, this);
        TRACE("======<rs_search_record_by_day> result:%d\n", search_record_day_session_);
    }
}

void RSNET_CALL playback_callback_fun(const char* param, void* user_param) {
    TRACE("======playback callback:%s\n", param);
}

void CPlaybackDlg::OnBnClickedBtnStart()
{
    // TODO: Add your control notification handler code here
    if (cursel_ == -1) {
        for(int i = 0; i < listctrl_record_.GetItemCount(); i++) {
            if(listctrl_record_.GetCheck(i)) {
                cursel_ = i;
                break;
            }
        }

        if (cursel_ == -1) {
            if (listctrl_record_.GetItemCount())
                cursel_ = 0;
        }
    }

    if (cursel_ != -1) {
        DEVICE_INFO* channel_info = NULL;
        HTREEITEM item = g_device_tree_->GetSelectedItem();
        if (item && (channel_info = (DEVICE_INFO*)(g_device_tree_->GetItemData(item))) && channel_info->type == TYPE_CHANNEL) {
            int device_type = rs_get_device_type(channel_info->device_info->device_session);
            unsigned int record_type = AllRecord;
            switch (combo_record_type_.GetCurSel())
            {
            case 0:
                record_type = NormalRecord;
                if (device_type == 4)
                    record_type = NormalRec;
                break;
            case 1:
                record_type = MotionRecord;
                if (device_type == 4)
                    record_type = MotionRec;
                break;
            case 2:
                record_type = AllRecord;
                break;
            default:
                break;
            }

            CString str_time = listctrl_record_.GetItemText(cursel_, 2);
            std::string begin_time;
            std::string end_time;
            {
                int index = str_time.Find(_T(" - "));
                begin_time = CT2CA(str_time.Mid(0, index));
                end_time = CT2CA(str_time.Mid(index+3, str_time.GetLength()-index-3));
            }

#ifndef SYNC_PLAYBACK_TEST
            Json::Value value;
            value.clear();
            value["channel"] = channel_info->channel;
            value["stream type"] = "main stream";
            value["record type"] = record_type;
            value["begin time"] = begin_time;
            value["end time"] = end_time;
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);

            remote_playback_param _param = {0};
            _param.dev = channel_info->device_info->device_session;
            _param.param = param.c_str();
            _param.window = window_[0].GetWindow();
            _param.playback_cb = playback_callback_fun;
            _param.playback_user_param = this;
            playback_session_ = rs_start_remote_playback(&_param);
            TRACE("======<rs_start_remote_playback> remote_id:%d\n", playback_session_);
#else
            for (int i = 0; i < _countof(single_playback_session_); i++) {
                Json::Value value;
                value.clear();
                value["channel"] = i;
                value["stream type"] = "main stream";
                value["record type"] = record_type;
                value["begin time"] = begin_time;
                value["end time"] = end_time;
                value["sync play"] = true;
                Json::StreamWriterBuilder writer;
                std::string param = Json::writeString(writer, value);

                remote_playback_param _param = {0};
                _param.dev = channel_info->device_info->device_session;
                _param.param = param.c_str();
                _param.window = window_[i].GetWindow();
                _param.playback_cb = playback_callback_fun;
                _param.playback_user_param = this;
                single_playback_session_[i] = rs_start_remote_playback(&_param);
                TRACE("======<rs_start_remote_playback> remote_id:%d\n", single_playback_session_[i]);
            }

            sync_playback_param sync_param = {0};
            sync_param.sess = &single_playback_session_[0];
            sync_param.sess_count = _countof(single_playback_session_);
            playback_session_ = rs_start_sync_playback(&sync_param);
            TRACE("======<rs_start_sync_playback> remote_id:%d\n", playback_session_);
#endif
        }
    }
}

void CPlaybackDlg::OnBnClickedBtnStop()
{
    // TODO: Add your control notification handler code here
    if (playback_session_ > 0) {
#ifndef SYNC_PLAYBACK_TEST
        rs_stop_record(playback_session_);
        rs_close_sound(playback_session_);
#else
        for (int i = 0; i < _countof(single_playback_session_); i++) {
            if (single_playback_session_[i])
                rs_stop_playback(single_playback_session_[i]);
        }
#endif
        rs_stop_playback(playback_session_);
        memset(single_playback_session_, 0, sizeof(single_playback_session_));
        playback_session_ = 0;

        if (init_over_) {
            for (int i = 0; i < _countof(window_); i++)
                window_[i].InvalidWnd();
        }
    }
    playback_session_ = 0;
    cursel_ = -1;
}

void CPlaybackDlg::OnBnClickedBtnPause()
{
    if (playback_session_ > 0) {
        CString str_text;
        GetDlgItemText(IDC_BTN_PAUSE, str_text);
        if (str_text.CompareNoCase(_T("Pause")) == 0) {
            Json::Value value;
            value.clear();
            value["operation type"] = "pause";
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            rs_set_play_mode(playback_session_, param.c_str());

            SetDlgItemText(IDC_STATIC_INFO, _T("pause"));
            SetDlgItemText(IDC_BTN_PAUSE, _T("Resume"));
        } else {
            Json::Value value;
            value.clear();
            value["operation type"] = "normal";
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            rs_set_play_mode(playback_session_, param.c_str());

            SetDlgItemText(IDC_STATIC_INFO, _T("normal"));
            SetDlgItemText(IDC_BTN_PAUSE, _T("Pause"));
        }
    }
}

void CPlaybackDlg::OnBnClickedBtnCapture()
{
    // TODO: Add your control notification handler code here
    if (playback_session_ > 0) {
        CString pic_name;
        pic_name.Format(_T("%s%d.jpeg"), g_appdata_path_, GetTickCount());

        Json::Value value;
        value.clear();
        value["picture name"] = std::string(CT2CA(pic_name));
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_capture_picture(playback_session_, param.c_str());
        TRACE("======<rs_capture_picture> playback_id:%d\n", playback_session_);
    }
}

void CPlaybackDlg::OnBnClickedBtnStartRec()
{
    // TODO: Add your control notification handler code here
    if (playback_session_ > 0) {
        CString temp_name;
        temp_name.Format(_T("%sremote_playback_%d"), g_appdata_path_, GetTickCount());
        CString record_name = temp_name + _T(".mp4");
        CString capture_name = temp_name + _T(".jpeg");

        Json::Value value;
        value.clear();
        value["file name"] = std::string(CT2CA(record_name));
        value["picture name"] = std::string(CT2CA(capture_name));
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_start_record(playback_session_, param.c_str());
        TRACE("======<rs_start_record> playback_id:%d\n", playback_session_);
    }
}

void CPlaybackDlg::OnBnClickedBtnStopRec()
{
    // TODO: Add your control notification handler code here
    if (playback_session_) {
        rs_stop_record(playback_session_);
        TRACE("======<rs_stop_record> playback_id:%d\n", playback_session_);
    }
}

void CPlaybackDlg::OnBnClickedBtnSlow()
{
    // TODO: Add your control notification handler code here
    if (playback_session_ > 0) {
        CString str_text;
        GetDlgItemText(IDC_STATIC_INFO, str_text);
        std::string str_value = std::string(CT2CA(str_text));
        for (int i = 0; i < _countof(playback_mode); i++) {
            if (strcmp(str_value.c_str(), playback_mode[i]) == 0) {
                i--;
                if (i < 0)
                    i = 0;

                Json::Value value;
                value.clear();
                value["operation type"] = playback_mode[i];
                Json::StreamWriterBuilder writer;
                std::string param = Json::writeString(writer, value);

                rs_set_play_mode(playback_session_, param.c_str());

                CString str_info;
                str_info = CA2CT(playback_mode[i]);
                SetDlgItemText(IDC_STATIC_INFO, str_info);
                break;
            }
        }
    }
}

void CPlaybackDlg::OnBnClickedBtnFast()
{
    // TODO: Add your control notification handler code here
    if (playback_session_ > 0) {
        CString str_text;
        GetDlgItemText(IDC_STATIC_INFO, str_text);
        std::string str_value = std::string(CT2CA(str_text));
        for (int i = 0; i < _countof(playback_mode); i++) {
            if (strcmp(str_value.c_str(), playback_mode[i]) == 0) {
                i++;
                if (i >= _countof(playback_mode))
                    i = _countof(playback_mode)-1;

                Json::Value value;
                value.clear();
                value["operation type"] = playback_mode[i];
                Json::StreamWriterBuilder writer;
                std::string param = Json::writeString(writer, value);

                rs_set_play_mode(playback_session_, param.c_str());

                CString str_info;
                str_info = CA2CT(playback_mode[i]);
                SetDlgItemText(IDC_STATIC_INFO, str_info);
                break;
            }
        }
    }
}

void CPlaybackDlg::OnBnClickedBtnSeek()
{
    // TODO: Add your control notification handler code here
    if (playback_session_ > 0) {
        char buf[128] = {0};
        if (rs_success == rs_get_current_time(playback_session_, buf, _countof(buf))) {
            *strchr(buf, ' ') = '\0';

            char* start = &buf[0] + strlen(buf);
            COleDateTime data_time;
            seek_time_picker_.GetTime(data_time);
            sprintf(start, " %02d:%02d:%02d", data_time.GetHour(), data_time.GetMinute(), data_time.GetSecond());
            rs_seek_by_time(playback_session_, buf);
        }
    }
}

/*
 * param      ---> "status"  : "hdd format"
 *                           : "device playback"
 *                           : "not enough bandwidth"
 *                           : "no authority"
 *                           : "modify hdd"
 *                           : "download close"
 *                           : "storage record file err"
 *                           : "no file"
 *                           : "download ok"
 *                           : "download percent"
 *                           : "unknown error"
 *            ---> "percent" : (int) from 0 to 100
 * user_param ---> value you pass to function <start_preview>
 */
static void RSNET_CALL download_callback_fun(const char* param, void* user_param) {
    TRACE("======download_callback_fun:%s\n", param);
    CPlaybackDlg* pthis = (CPlaybackDlg*)user_param;
    if (pthis && param)
        pthis->download_callback(param);
}

void CPlaybackDlg::download_callback(const char* param) {
    if (current_download_index_ != -1) {
        std::string err = "";
        Json::CharReaderBuilder reader;
        Json::Value value;
        if(!Json::parseFromStream(reader, param, &value, &err))
            return;

        std::string status = value["status"].asString();
        if (strcmp(status.c_str(),"download percent") == 0) {
            CString str;
            str.Format(_T("percent:%d"), value["percent"].asInt());
            listctrl_record_.SetItemText(current_download_index_, 5, str);
        } else {
            CString str = CA2CT(status.c_str());
            listctrl_record_.SetItemText(current_download_index_, 5, str);
        }
    }
}

void CPlaybackDlg::OnBnClickedBtnStartDownload()
{
    // TODO: Add your control notification handler code here
    OnBnClickedBtnStopDownload();

    current_download_index_ = -1;
    for(int i = 0; i < listctrl_record_.GetItemCount(); i++) {
        if(listctrl_record_.GetCheck(i)) {
            current_download_index_ = i;
            break;
        }
    }

    if (current_download_index_ != -1) {
        SEARCH_RECORD_INFO info = {0};
        std::map<int, SEARCH_RECORD_INFO>::iterator itor  = search_record_map_info_.find(current_download_index_);
        if (itor != search_record_map_info_.end()) {
            CString downdload_name;
            downdload_name.Format(_T("%sdownload_%d.%s"), g_appdata_path_, GetTickCount(), _T("mp4"));

            SEARCH_RECORD_INFO& info = itor->second;
            listctrl_record_.SetItemText(current_download_index_, 5, _T(""));

            Json::Value value;
            value.clear();
            value["index"] = info.index;
            value["file name"] = std::string(CT2CA(downdload_name));
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            download_session_ = rs_start_download_by_file(info.device_id, param.c_str(), download_callback_fun, this);
            TRACE("======<rs_start_download_by_file> download_session:%d\n", download_session_);
            GetDlgItem(IDC_BTN_SEARCH_DAY)->EnableWindow(FALSE);
        }
    }
}

void CPlaybackDlg::OnBnClickedBtnStopDownload()
{
    // TODO: Add your control notification handler code here
    if (download_session_) {
        rs_stop_download(download_session_);
        TRACE("======<rs_stop_download> download_session:%d\n", download_session_);
        download_session_ = 0;
    }
    GetDlgItem(IDC_BTN_SEARCH_DAY)->EnableWindow(TRUE);
    if (current_download_index_ != -1)
        listctrl_record_.SetItemText(current_download_index_, 5, _T(""));
    current_download_index_ = -1;
}

void CPlaybackDlg::move_window(int index, int x, int y)
{
    int width = 0;
    int height = 0;
    CRect rect_temp;
    CRect rect_client;
    GetClientRect(&rect_client);

    GetDlgItem(index)->GetWindowRect(&rect_temp);
    ScreenToClient(&rect_temp);
    width = rect_temp.Width();
    height = rect_temp.Height();
    if (x) {
        rect_temp.right = rect_client.right + x;
        rect_temp.left = rect_temp.right - width;
    }

    if (y) {
        rect_temp.bottom = rect_client.bottom + y;
        rect_temp.top = rect_temp.bottom - height;
    }
    GetDlgItem(index)->MoveWindow(&rect_temp);
}
