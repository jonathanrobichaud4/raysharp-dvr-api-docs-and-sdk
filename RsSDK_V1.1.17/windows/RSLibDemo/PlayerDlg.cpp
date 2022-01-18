// PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "PlayerDlg.h"
#include "RSLibDemoDlg.h"


// CPlayerDlg dialog

IMPLEMENT_DYNAMIC(CPlayerDlg, CDialog)

CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerDlg::IDD, pParent)
    , parent_(NULL)
    , init_over_(FALSE)
    , local_playback_sess_(0)
    , slider_previous_pos_(-1)
    , begin_second_(0)
    , end_second_(0)
{

}

CPlayerDlg::~CPlayerDlg()
{
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_PLAYER, slider_player_);
}


BEGIN_MESSAGE_MAP(CPlayerDlg, CDialog)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BTN_START, &CPlayerDlg::OnBnClickedBtnStart)
    ON_BN_CLICKED(IDC_BTN_STOP, &CPlayerDlg::OnBnClickedBtnStop)
    ON_BN_CLICKED(IDC_BTN_OPEN_SOUND, &CPlayerDlg::OnBnClickedBtnOpenSound)
    ON_BN_CLICKED(IDC_BTN_CLOSE_SOUND, &CPlayerDlg::OnBnClickedBtnCloseSound)
    ON_BN_CLICKED(IDC_BTN_FILE, &CPlayerDlg::OnBnClickedBtnFile)
    ON_MESSAGE(WM_SLIDER_POSITION, &CPlayerDlg::OnSliderPosition)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CPlayerDlg message handlers

BOOL CPlayerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    for (int i = 0; i < MAX_PLAYER_WINDOW; i++) {
        local_playback_sess_ = NULL;
        if (window_[i].GetSafeHwnd() == NULL) {
            window_[i].Create(CPlayWindow::IDD, GetDlgItem(IDC_STATIC_PLAYER_WND));
        }
    }
    slider_player_.SetParentHwnd(this->GetSafeHwnd());
    slider_player_.SetRange(0, 100);
    slider_player_.SetTicFreq(10);
    slider_player_.SetPos(0);

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayerDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        if (init_over_) {
            CRect rect;
            GetDlgItem(IDC_STATIC_PLAYER_WND)->GetClientRect(&rect);

            int count = 1;
            if (MAX_PLAYER_WINDOW == 1) {
                count = 1;
            } else if (MAX_PLAYER_WINDOW <= 4) {
                count = 2;
            } else if (MAX_PLAYER_WINDOW <= 9) {
                count = 3;
            } else if (MAX_PLAYER_WINDOW <= 16) {
                count = 4;
            } else if (MAX_PLAYER_WINDOW <= 25) {
                count = 5;
            } else if (MAX_PLAYER_WINDOW <= 36) {
                count = 6;
            } else {
                MessageBox(_T("Too many player window"), NULL, MB_OK | MB_ICONERROR);
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

            for (int i = 0; i < MAX_PLAYER_WINDOW; i++) {
                window_[i].MoveWindow(vec_rect.at(i));
                window_[i].ShowWindow(SW_SHOW);
            }
        }
    }
}

void CPlayerDlg::SetParentWindow(CRSLibDemoDlg* parent) {
    parent_ = parent;
}

void CPlayerDlg::StopAll() {
    init_over_ = FALSE;

    OnBnClickedBtnStop();
}

void RSNET_CALL local_playback_callback_fun(const char* param, void* user_param) {
    TRACE("======local playback callback:%s\n", param);
}

void CPlayerDlg::OnBnClickedBtnStart()
{
    // TODO: Add your control notification handler code here
    OnBnClickedBtnStop();

    CString path;
    GetDlgItemText(IDC_EDT_FILE, path);
    if (!path.IsEmpty()) {
        char* temp_path = CreateUTF8TextInitWithString(path);
        std::string file_name = std::string(temp_path);
        delete[] temp_path;

        {
            char buf_time[256] = {0};
            rs_get_file_time(file_name.c_str(), buf_time, _countof(buf_time));

            std::string err = "";
            Json::CharReaderBuilder reader;
            Json::Value value;
            if(!Json::parseFromStream(reader, buf_time, &value, &err))
                return;

            std::string str_time = value["begin time"].asString();
            begin_second_ = convert_utc_to_microsecond(str_time.c_str());
            str_time = value["end time"].asString();
            end_second_ = convert_utc_to_microsecond(str_time.c_str());
        }

        Json::Value value;
        value.clear();
        value["file name"] = file_name;

        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);

        local_playback_param _param = {0};
        _param.param = param.c_str();
        _param.window = window_[0].GetWindow();
        _param.playback_cb = local_playback_callback_fun;
        _param.playback_user_param = this;
        local_playback_sess_ = rs_start_local_playback(&_param);
        if (local_playback_sess_ > 0)
            rs_open_sound(local_playback_sess_);
        SetTimer(1000, 1000, NULL);

        TRACE("======<rs_start_local_playback> local_id:%d\n", local_playback_sess_);
    }
}

void CPlayerDlg::OnBnClickedBtnStop()
{
    // TODO: Add your control notification handler code here
    if (local_playback_sess_) {
        if (init_over_)
            KillTimer(1000);

        rs_stop_playback(local_playback_sess_);
        local_playback_sess_ = 0;

        if (init_over_)
            window_[0].InvalidWnd();
    }

    if (init_over_) {
        slider_player_.SetPos(0);
        slider_previous_pos_ = -1;
    }
}

void CPlayerDlg::OnBnClickedBtnOpenSound()
{
    // TODO: Add your control notification handler code here
    if (local_playback_sess_) {
        rs_open_sound(local_playback_sess_);
    }
}

void CPlayerDlg::OnBnClickedBtnCloseSound()
{
    // TODO: Add your control notification handler code here
    if (local_playback_sess_) {
        rs_close_sound(local_playback_sess_);
    }
}

void CPlayerDlg::OnBnClickedBtnFile()
{
    // TODO: Add your control notification handler code here
    CString str_fliter = _T("Video Files (*.rf;*.avi;*.mp4)|*.rf;*.avi;*.mp4|All Files (*.*)|*.*|");
    CFileDialog dlg(TRUE,NULL,NULL,OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,str_fliter);   
    if ( IDOK == dlg.DoModal()) {
        CString path = dlg.GetPathName();
        SetDlgItemText(IDC_EDT_FILE, path);

        OnBnClickedBtnStart();
    }
}

LRESULT CPlayerDlg::OnSliderPosition(WPARAM wparam, LPARAM lparam) {
    if (slider_player_.GetPos() != slider_previous_pos_) {
        slider_previous_pos_ = slider_player_.GetPos();

        if (local_playback_sess_) {
            int current_time = begin_second_+(int)(slider_previous_pos_/100.0*(end_second_-begin_second_));
            char buf[32] = {0};
            time_t now = (time_t)(current_time);
            struct tm gmtTime;
            gmtime_s(&gmtTime, &now);
            sprintf_s(buf, _countof(buf), "%04d-%02d-%02d %02d:%02d:%02d", gmtTime.tm_year+1900, gmtTime.tm_mon+1, gmtTime.tm_mday, \
                gmtTime.tm_hour, gmtTime.tm_min, gmtTime.tm_sec);
            rs_seek_by_time(local_playback_sess_, buf);
        }
    }
    return NULL;
}

int CPlayerDlg::convert_utc_to_microsecond(const char* param) {
    int year, month, day, hour, minute, second;
    sscanf(param, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    month--;
    day--;

    int days = 0;
    for (int begin_year = 1970; begin_year < year; begin_year++) {
        if ((begin_year%4 == 0 && begin_year%100 != 0) || begin_year%400 == 0)
            days += 366;
        else
            days += 365;
    }

    static int global_rs_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    for (int begin_month = 0; begin_month < month; begin_month++) {
        if (begin_month == 1 && ((year%4 == 0 && year%100 != 0) || year%400 == 0))
            days += 29;
        else
            days += global_rs_month[begin_month];
    }
    days += day;

    int secons = (days*24*60*60 + hour*60*60 + minute*60 + second);
    return secons;
}

void CPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if (local_playback_sess_) {
        char buf[32] = {0};
        if (rs_get_current_time(local_playback_sess_, buf, _countof(buf)) == rs_success) {
            int current_time = convert_utc_to_microsecond(buf);
            slider_player_.SetPos((int)(100.0*(current_time-begin_second_)/(end_second_-begin_second_)));
        }
    }
    CDialog::OnTimer(nIDEvent);
}
