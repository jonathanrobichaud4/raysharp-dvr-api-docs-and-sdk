// PreviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "PreviewDlg.h"
#include "RSLibDemoDlg.h"

// CPreviewDlg dialog

IMPLEMENT_DYNAMIC(CPreviewDlg, CDialog)

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
    , parent_(NULL)
    , init_over_(FALSE)
{

}

CPreviewDlg::~CPreviewDlg()
{
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ALARM, listctrl_alarm_);
    DDX_Control(pDX, IDC_COMBO_FISHEYE, combo_fisheye_);
    DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, combo_record_type_);
    DDX_Control(pDX, IDC_COMBO_CAPTURE_TYPE, combo_capture_type_);
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BTN_CAPTURE, &CPreviewDlg::OnBnClickedBtnCapture)
    ON_BN_CLICKED(IDC_BTN_START_REC, &CPreviewDlg::OnBnClickedBtnStartRec)
    ON_BN_CLICKED(IDC_BTN_STOP_REC, &CPreviewDlg::OnBnClickedBtnStopRec)
    ON_BN_CLICKED(IDC_BTN_OPEN, &CPreviewDlg::OnBnClickedBtnOpen)
    ON_CBN_SELCHANGE(IDC_COMBO_FISHEYE, &CPreviewDlg::OnCbnSelchangeComboFisheye)
    ON_BN_CLICKED(IDC_BTN_CAPTURE_FROM_DEVICE, &CPreviewDlg::OnBnClickedBtnCaptureFromDevice)
	ON_BN_CLICKED(IDC_BTN_CAPTURE_TO_BUF, &CPreviewDlg::OnBnClickedBtnCaptureToBuf)
END_MESSAGE_MAP()


// CPreviewDlg message handlers

BOOL CPreviewDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    for (int i = 0; i < MAX_PREIVEW_WINDOW; i++) {
        preview_session_[i] = NULL;
        picture_id_[i] = 0;
        picture_id2_[i] = 0;
        if (window_[i].GetSafeHwnd() == NULL) {
            window_[i].Create(CPlayWindow::IDD, GetDlgItem(IDC_STA_PREVIEW_WND));
            window_[i].SetParent(this);
        }
        draw_callback_info_[i]._this = this;
        draw_callback_info_[i]._index = i;
    }

    listctrl_alarm_.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
    listctrl_alarm_.InsertColumn(0, _T("No."), LVCFMT_CENTER, 50);
    listctrl_alarm_.InsertColumn(1, _T("IP"), LVCFMT_CENTER, 120);
    listctrl_alarm_.InsertColumn(2, _T("Info"), LVCFMT_CENTER, 200);
    listctrl_alarm_.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

    combo_capture_type_.InsertString(0, _T("jpeg"));
    combo_capture_type_.InsertString(1, _T("png"));
    combo_capture_type_.SetCurSel(0);

    combo_record_type_.InsertString(0, _T("mp4"));
    combo_record_type_.InsertString(1, _T("avi"));
    combo_record_type_.InsertString(2, _T("rf"));
    combo_record_type_.SetCurSel(0);

    int index = 0;
    combo_fisheye_.InsertString(index, _T("CEILING_EYE"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_EYE));
    combo_fisheye_.InsertString(index, _T("CEILING_VR"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_VR));
    combo_fisheye_.InsertString(index, _T("CEILING_3D"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND3D));
    combo_fisheye_.InsertString(index, _T("CEILING_360"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND360));
    combo_fisheye_.InsertString(index, _T("CEILING_180"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND180));
    combo_fisheye_.InsertString(index, _T("CEILING_2PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_2PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_4PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_4PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_360_1PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND360_1PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_360_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND360_3PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_360_6PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND360_6PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_360_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_CYLIND360_8PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_EYE_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_EYE_3PTZ));
    combo_fisheye_.InsertString(index, _T("CEILING_EYE_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_CEILING_EYE_8PTZ));

    combo_fisheye_.InsertString(index, _T("DESKTOP_EY"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_EYE));
    combo_fisheye_.InsertString(index, _T("DESKTOP_VR"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_VR));
    combo_fisheye_.InsertString(index, _T("DESKTOP_3D"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND3D));
    combo_fisheye_.InsertString(index, _T("DESKTOP_360"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND360));
    combo_fisheye_.InsertString(index, _T("DESKTOP_180"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND180));
    combo_fisheye_.InsertString(index, _T("DESKTOP_4PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_4PTZ));
    combo_fisheye_.InsertString(index, _T("DESKTOP_360_1PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND360_1PTZ));
    combo_fisheye_.InsertString(index, _T("DESKTOP_360_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND360_3PTZ));
    combo_fisheye_.InsertString(index, _T("DESKTOP_360_6PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND360_6PTZ));
    combo_fisheye_.InsertString(index, _T("DESKTOP_360_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_CYLIND360_8PTZ));
    combo_fisheye_.InsertString(index, _T("DESKTOP_EYE_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_EYE_3PTZ));
    combo_fisheye_.InsertString(index, _T("DESKTOP_EYE_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_DESKTOP_EYE_8PTZ));

    combo_fisheye_.InsertString(index, _T("WALL_EYE"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_EYE));
    combo_fisheye_.InsertString(index, _T("WALL_VR"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_VR));
    combo_fisheye_.InsertString(index, _T("WALL_NORMAL"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_NORMAL));
    combo_fisheye_.InsertString(index, _T("WALL_4PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_4PTZ));
    combo_fisheye_.InsertString(index, _T("WALL_NORMAL_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_NORMAL_3PTZ));
    combo_fisheye_.InsertString(index, _T("WALL_NORMAL_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_NORMAL_8PTZ));
    combo_fisheye_.InsertString(index, _T("WALL_EYE_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_EYE_3PTZ));
    combo_fisheye_.InsertString(index, _T("WALL_EYE_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_WALL_EYE_8PTZ));

    combo_fisheye_.InsertString(index, _T("TILT_EYE"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_EYE));
    combo_fisheye_.InsertString(index, _T("TILT_VR"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_VR));
    combo_fisheye_.InsertString(index, _T("TILT_NORMAL"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_NORMAL));
    combo_fisheye_.InsertString(index, _T("TILT_4PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_4PTZ));
    combo_fisheye_.InsertString(index, _T("TILT_NORMAL_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_NORMAL_3PTZ));
    combo_fisheye_.InsertString(index, _T("TILT_NORMAL_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_NORMAL_8PTZ));
    combo_fisheye_.InsertString(index, _T("TILT_EYE_3PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_EYE_3PTZ));
    combo_fisheye_.InsertString(index, _T("TILT_EYE_8PTZ"));
    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_TILT_EYE_8PTZ));
    combo_fisheye_.InsertString(index, _T("NONE"));

    combo_fisheye_.SetItemData(index++, (DWORD_PTR)(FISH_COMB_TYPE_BUTT));
    combo_fisheye_.SetCurSel(combo_fisheye_.GetCount()-1);

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreviewDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        int width = 0;
        int height = 0;
        CRect rect_client;
        GetClientRect(&rect_client);

        CRect rect_temp;
        GetDlgItem(IDC_STA_PREVIEW_WND)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        rect_temp.right = rect_client.right - 147;
        rect_temp.bottom = rect_client.bottom - 154;
        GetDlgItem(IDC_STA_PREVIEW_WND)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_LIST_ALARM)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.bottom = rect_client.bottom - 14;
        rect_temp.right = rect_client.right - 12;
        rect_temp.top = rect_temp.bottom - height;
        GetDlgItem(IDC_LIST_ALARM)->MoveWindow(&rect_temp);
        listctrl_alarm_.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

        GetDlgItem(IDC_STATIC_PTZ)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.right = rect_client.right - 8;
        rect_temp.left = rect_temp.right - width;
        GetDlgItem(IDC_STATIC_PTZ)->MoveWindow(&rect_temp);

        GetDlgItem(IDC_STATIC_FISHEYE)->GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        width = rect_temp.Width();
        height = rect_temp.Height();
        rect_temp.right = rect_client.right - 8;
        rect_temp.left = rect_temp.right - width;
        GetDlgItem(IDC_STATIC_FISHEYE)->MoveWindow(&rect_temp);

        CRect rect;
        GetDlgItem(IDC_STA_PREVIEW_WND)->GetClientRect(&rect);

        int count = 2;
        if (MAX_PREIVEW_WINDOW <= 4) {
            count = 2;
        } else if (MAX_PREIVEW_WINDOW <= 9) {
            count = 3;
        } else if (MAX_PREIVEW_WINDOW <= 16) {
            count = 4;
        } else if (MAX_PREIVEW_WINDOW <= 25) {
            count = 5;
        } else if (MAX_PREIVEW_WINDOW <= 36) {
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

        for (int i = 0; i < MAX_PREIVEW_WINDOW; i++) {
            window_[i].MoveWindow(vec_rect.at(i));
            window_[i].ShowWindow(SW_SHOW);
        }

        move_window(IDC_BTN_LU, -96, 0);
        move_window(IDC_BTN_L, -96, 0);
        move_window(IDC_BTN_LD, -96, 0);
        move_window(IDC_BTN_U, -60, 0);
        move_window(IDC_BTN_A, -60, 0);
        move_window(IDC_BTN_D, -60, 0);
        move_window(IDC_BTN_RU, -26, 0);
        move_window(IDC_BTN_R, -26, 0);
        move_window(IDC_BTN_RD, -26, 0);

        move_window(IDC_BTN_ZOOM_D, -80, 0);
        move_window(IDC_BTN_FOCUS_D, -80, 0);
        move_window(IDC_BTN_IRIS_D, -80, 0);
        move_window(IDC_BTN_ZOOM_I, -27, 0);
        move_window(IDC_BTN_FOCUS_I, -27, 0);
        move_window(IDC_BTN_IRIS_I, -27, 0);

        move_window(IDC_COMBO_FISHEYE, -12, 0);
        move_window(IDC_BTN_CAPTURE, -60, 0);
        move_window(IDC_BTN_START_REC, -60, 0);
        move_window(IDC_BTN_STOP_REC, -60, 0);
        move_window(IDC_COMBO_CAPTURE_TYPE, -12, 0);
        move_window(IDC_COMBO_RECORD_TYPE, -12, 0);
        move_window(IDC_BTN_OPEN, -12, 0);
        move_window(IDC_BTN_CAPTURE_FROM_DEVICE, -12, 0);
        move_window(IDC_BTN_CAPTURE_TO_BUF, -12, 0);
    }
}

void CPreviewDlg::SetParentWindow(CRSLibDemoDlg* parent) {
    parent_ = parent;
}

static void RSNET_CALL preivew_callback_fun(const char* param, void* user_param) {
    TRACE("======<preview callback> callback:%s\n", param);
}

static void CALLBACK draw_callback_fun(SDKWRAPPER_DRAW_INFO* info, void* user_param) {
    DRAW_CALLBACK_INFO* cb_param = (DRAW_CALLBACK_INFO*)user_param;
    if (cb_param->_this)
        cb_param->_this->draw(cb_param->_index);
}

void CPreviewDlg::draw(int index) {
    CRect rect;
    window_[index].GetClientRect(&rect);
    if (rect.Width() > 100) {
        rs_color color1 = {1.0f, 0.0f, 0.0f};
        rs_set_color(preview_session_[index], &color1);
        rs_rect rect1[6] = {{0.0f, 0.25f, 1.0f, 0.25f}, {0.0f, 0.5f, 1.0f, 0.5f}, {0.0f, 0.75f, 1.0f, 0.75f},
        {0.25f, 0.0f, 0.25f, 1.0f}, {0.5f, 0.0f, 0.5f, 1.0f}, {0.75f, 0.0f, 0.75f, 1.0f}};
        rs_draw_line(preview_session_[index], rect1, 6);

        rs_color color2 = {0.0f, 0.0f, 1.0f};
        rs_set_color(preview_session_[index], &color2);
        rs_rect rect2[2] = {{0.1f, 0.1f, 0.25f, 0.25f}, {0.3f, 0.3f, 0.45f, 0.45f}};
        rs_draw_rect(preview_session_[index], &rect2[0], 2);

        rs_color color3 = {0.0f, 1.0f, 0.0f};
        rs_set_color(preview_session_[index], &color3);
        rs_rect rect3[2] = {{0.1f, 0.6f, 0.25f, 0.75f}, {0.3f, 0.8f, 0.45f, 0.95f}};
        rs_draw_solid_rect(preview_session_[index], &rect3[0], 2, 0.3f);

        if (picture_id_[index] > 0) {
            rs_rect rect3 = {0.5f, 0.3f, 0.7f, 0.5f};
            rs_draw_picture(preview_session_[index], picture_id_[index], &rect3, 0.3f);
        }

        if (picture_id2_[index] > 0) {
            rs_rect rect3 = {0.5f, 0.1f, 0.9f, 0.3f};
            rs_draw_picture(preview_session_[index], picture_id2_[index], &rect3, 0.8f);
        }
    }
}

void CPreviewDlg::StartPreview(DEVICE_INFO* info) {
    if (info->type != TYPE_CHANNEL)
        return;
    StopPreview(info);

    Json::Value value;
    value.clear();
    value["channel"] = info->channel;
    value["stream type"] = "sub stream";
    value["auto connect"] = true;

    int index = info->channel % MAX_PREIVEW_WINDOW;
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    preview_param _preview_param = {0};
    _preview_param.dev = info->device_info->device_session;
    _preview_param.param = param.c_str();
    _preview_param.window = window_[index].GetWindow();
    _preview_param.preview_cb = preivew_callback_fun;
    _preview_param.preview_user_param = &draw_callback_info_[index];
    //_preview_param.draw_cb = draw_callback_fun;
    preview_session_[index] = rs_start_preview(&_preview_param);
    TRACE("======<rs_start_preview> preview_id:%d\n", preview_session_[index]);
    if (index == 0) {
        rs_open_sound(preview_session_[index]);
        TRACE("======<rs_open_sound> preview_id:%d\n", preview_session_[index]);
    }

    {
        char path[MAX_PATH] = {0};
        GetModuleFileNameA(NULL, path, MAX_PATH);
        *strrchr(path, ('\\')) = ('\0');

        strcat(path, ("\\watermark.png"));//watermark
        FILE* file = fopen(path, "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            size_t size = ftell(file);
            fseek(file, 0, SEEK_SET);

            char* data = new char[size];
            fread(data, size, 1, file);
            fclose(file);
            picture_id_[index] = rs_upload_picture_from_memory(preview_session_[index], data, size);
            delete[] data;
        }
    }

    {
        char path[MAX_PATH] = {0};
        GetModuleFileNameA(NULL, path, MAX_PATH);
        *strrchr(path, ('\\')) = ('\0');

        strcat(path, ("\\logo.png"));//watermark
        FILE* file = fopen(path, "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            size_t size = ftell(file);
            fseek(file, 0, SEEK_SET);

            char* data = new char[size];
            fread(data, size, 1, file);
            fclose(file);
            picture_id2_[index] = rs_upload_picture_from_memory(preview_session_[index], data, size);
            delete[] data;
        }
    }
    

    if (preview_session_[index] > 0) {
        window_[index].SetPlaySession(preview_session_[index]);
        window_[index].SetDeviceInfo(info);
    }

    info->in_preview_status = true;
    info->preview_session = preview_session_[index];
    if (init_over_) {
        if (info->online_status)
            g_device_tree_->SetItemImage(info->item, ICO_CH_ONLINE_PREIVEW, ICO_CH_ONLINE_PREIVEW);
        else
            g_device_tree_->SetItemImage(info->item, ICO_CH_OFFLINE_PREIVEW, ICO_CH_OFFLINE_PREIVEW);
    }
}

void CPreviewDlg::StopPreview(DEVICE_INFO* info) {
    if (info->type != TYPE_CHANNEL)
        return;

    int index = info->channel % MAX_PREIVEW_WINDOW;
    DEVICE_INFO* pre_info = window_[index].GetDeviceInfo();
    if (pre_info && preview_session_[index]) {
        rs_stop_record(preview_session_[index]);
        TRACE("======<rs_stop_record> preview_id:%d\n", preview_session_[index]);

        if (index == 0) {
            rs_close_sound(preview_session_[index]);
            TRACE("======<rs_close_sound> preview_id:%d\n", preview_session_[index]);

            if (picture_id_[index]) {
                rs_delete_picture(preview_session_[index], picture_id_[index]);
                picture_id_[index] = 0;
            }

            if (picture_id2_[index]) {
                rs_delete_picture(preview_session_[index], picture_id2_[index]);
                picture_id2_[index] = 0;
            }
        }

        rs_stop_preview(preview_session_[index]);
        TRACE("======<rs_stop_preview> preview_id:%d\n", preview_session_[index]);

        preview_session_[index] = 0;
        window_[index].SetPlaySession(0);
        window_[index].SetDeviceInfo(NULL);

        pre_info->in_preview_status = false;
        pre_info->preview_session = 0;
        if (init_over_) {
            window_[index].InvalidWnd();
            if (pre_info->online_status)
                g_device_tree_->SetItemImage(pre_info->item, ICO_CH_ONLINE, ICO_CH_ONLINE);
            else
                g_device_tree_->SetItemImage(pre_info->item, ICO_CH_OFFLINE, ICO_CH_OFFLINE);
        }
    }
}

void CPreviewDlg::StopAll(BOOL update_init_over_value/* = TRUE*/) {
    if (update_init_over_value)
        init_over_ = FALSE;

    for (int i = 0; i < MAX_PREIVEW_WINDOW; i++) {
        if (preview_session_[i]) {
            rs_stop_record(preview_session_[i]);
            TRACE("======<rs_stop_record> preview_id:%d\n", preview_session_[i]);

            rs_stop_preview(preview_session_[i]);
            TRACE("======<rs_stop_preview> preview_id:%d\n", preview_session_[i]);
            preview_session_[i] = 0;
            window_[i].SetPlaySession(0);

            DEVICE_INFO* pre_info = window_[i].GetDeviceInfo();
            window_[i].SetDeviceInfo(NULL);
            pre_info->in_preview_status = false;
            pre_info->preview_session = 0;
            if (init_over_) {
                window_[i].InvalidWnd();
                if (pre_info->online_status)
                    g_device_tree_->SetItemImage(pre_info->item, ICO_CH_ONLINE, ICO_CH_ONLINE);
                else
                    g_device_tree_->SetItemImage(pre_info->item, ICO_CH_OFFLINE, ICO_CH_OFFLINE);
            }
        }
    }
}

void CPreviewDlg::SetCurSel(CPlayWindow* window) {
    for (int i = 0; i < MAX_PREIVEW_WINDOW; i++) {
        if (&window_[i] == window)
            window_[i].checked_ = TRUE;
        else
            window_[i].checked_ = FALSE;
        window_[i].RedrawWindow();
    }
}

void CPreviewDlg::SetDoubleClick(CPlayWindow* window) {
    BOOL all_show = TRUE;
    for (int i = 0; i < MAX_PREIVEW_WINDOW; i++) {
        if (!window_[i].IsWindowVisible()) {
            all_show = FALSE;
            break;
        }
    }

    if (all_show) {
        CRect rect;
        GetDlgItem(IDC_STA_PREVIEW_WND)->GetClientRect(&rect);
        window->MoveWindow(&rect);
        window->InvalidWnd();

        for (int i = 0; i < MAX_PREIVEW_WINDOW; i++) {
            if (&window_[i] != window) {
                window_[i].ShowWindow(SW_HIDE);
            } else {
                window_[i].ShowWindow(SW_SHOW);
            }
        }
    } else {
        PostMessage(WM_SIZE, NULL, NULL);
    }
}

void CPreviewDlg::alarm_callback(const char* alarm_type, const char* param, DEVICE_INFO* info) {
    //index, ip, channel, alarm, info
    CString str_index, str_ip, str_info;
    str_index.Format(_T("%d"), listctrl_alarm_.GetItemCount());
    str_ip = info->ip;
    str_info = CA2CT(alarm_type);

    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return;

    if (!strcmp(alarm_type, "RSSDKAlarmStatus")) {
        //0:stop 1:green color 2:red color
        for (Json::ArrayIndex i = 0 ; i < value.size(); i++) {
            value[i]["hdd"].asInt();
            value[i]["record"].asInt();
            value[i]["io"].asInt();
            value[i]["motion"].asInt();
            value[i]["lens cover"].asInt();
            value[i]["lcd"].asInt();
            value[i]["sod"].asInt();
            value[i]["pid"].asInt();
            value[i]["smart"].asInt();
            value[i]["pir"].asInt();
        }

        {
            rs_app_scoped_lock lock(mutex_);
            listctrl_alarm_.InsertItem(0, str_index);
            listctrl_alarm_.SetItemText(0, 1, str_ip);
            listctrl_alarm_.SetItemText(0, 2, str_info);
        }
    }
}

BOOL CPreviewDlg::IsFisheyeMode() {
    return (FISH_COMB_TYPE_BUTT == FISHEYE_COMB_TYPE_E(combo_fisheye_.GetItemData(combo_fisheye_.GetCurSel()))) ? FALSE : TRUE;
}

void CPreviewDlg::OnBnClickedBtnCapture()
{
    // TODO: Add your control notification handler code here
    for (int i = 0; i < _countof(window_); i++) {
        if (window_[i].checked_ && preview_session_[i]) {
            CString pic_name;
            pic_name.Format(_T("%spreview_%d.%s"), g_appdata_path_, GetTickCount(), combo_capture_type_.GetCurSel() == 0 ? _T("jpeg") : _T("png"));

            Json::Value value;
            value.clear();
            value["picture name"] = std::string(CT2CA(pic_name));
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            rs_capture_picture(preview_session_[i], param.c_str());
            TRACE("======<rs_capture_picture> preview_id:%d\n", preview_session_[i]);
            break;
        }
    }
}

void CPreviewDlg::OnBnClickedBtnStartRec()
{
    // TODO: Add your control notification handler code here
    for (int i = 0; i < _countof(window_); i++) {
        if (window_[i].checked_ && preview_session_[i]) {
            CString capture_name;
            CString record_name;
            CString temp_name;
            temp_name.Format(_T("%spreview_%d"), g_appdata_path_, GetTickCount());
            switch (combo_capture_type_.GetCurSel())
            {
            case 0:
                capture_name = temp_name + _T(".jpeg");
            	break;
            case 1:
                capture_name = temp_name + _T(".png");
                break;
            default:
                capture_name = temp_name + _T(".jpeg");
                break;
            }

            switch (combo_record_type_.GetCurSel())
            {
            case 0:
                record_name = temp_name + _T(".mp4");
                break;
            case 1:
                record_name = temp_name + _T(".avi");
                break;
            case 2:
                record_name = temp_name + _T(".rf");
                break;
            default:
                record_name = temp_name + _T(".rf");
                break;
            }

            Json::Value value;
            value.clear();
            value["file name"] = std::string(CT2CA(record_name));
            value["picture name"] = std::string(CT2CA(capture_name));
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            rs_start_record(preview_session_[i], param.c_str());
            TRACE("======<rs_start_record> preview_id:%d\n", preview_session_[i]);
            break;
        }
    }
}

void CPreviewDlg::OnBnClickedBtnStopRec()
{
    // TODO: Add your control notification handler code here
    for (int i = 0; i < _countof(window_); i++) {
        if (window_[i].checked_ && preview_session_[i]) {
            rs_stop_record(preview_session_[i]);
            TRACE("======<rs_stop_record> preview_id:%d\n", preview_session_[i]);
            break;
        }
    }
}

void CPreviewDlg::OnCbnSelchangeComboFisheye()
{
    // TODO: Add your control notification handler code here
    for (int i = 0; i < _countof(window_); i++) {
        if (window_[i].checked_ && preview_session_[i]) {
            rs_set_fishsye_mode(preview_session_[i], FISHEYE_COMB_TYPE_E(combo_fisheye_.GetItemData(combo_fisheye_.GetCurSel())));
            break;
        }
    }
}

void CPreviewDlg::OnBnClickedBtnOpen()
{
    // TODO: Add your control notification handler code here
    TCHAR szAppName[_MAX_PATH] = TEXT("C:\\Windows\\Explorer.exe");
    TCHAR szCmdLine[_MAX_PATH] = {0};
    szCmdLine[0] = _T(' ');
    wmemcpy(&szCmdLine[1], g_appdata_path_.GetBuffer(0), g_appdata_path_.GetLength());
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi = {0};
    CreateProcess(szAppName, szCmdLine, NULL, NULL,FALSE, 0, NULL, NULL, &si, &pi); 
}

BOOL CPreviewDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        {
            for (int i = 0; i < _countof(window_); i++) {
                if (window_[i].checked_ && preview_session_[i]) {
                    DEVICE_INFO* info = window_[i].GetDeviceInfo();
                    if (info && info->device_info && info->device_info->device_session > 0) {
                        session_id device_session = info->device_info->device_session;
                        if (pMsg->hwnd == GetDlgItem(IDC_BTN_LU)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "up left";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_U)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "up";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_RU)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "up right";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_L)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "left";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_A)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "auto scan";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_R)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "right";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_LD)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "down left";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "down";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_RD)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "down right";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "zoom out";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_I)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "zoom in";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "focus far";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_I)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "focus near";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_IRIS_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "iris open";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_IRIS_I)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "iris close";
                            value["flag"] = "start";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        }
                    }
                    break;
                }
            }
        }
        break;
    case WM_LBUTTONUP:
        {
            for (int i = 0; i < _countof(window_); i++) {
                if (window_[i].checked_ && preview_session_[i]) {
                    DEVICE_INFO* info = window_[i].GetDeviceInfo();
                    if (info && info->device_info && info->device_info->device_session > 0) {
                        session_id device_session = info->device_info->device_session;
                        if (pMsg->hwnd == GetDlgItem(IDC_BTN_LU)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "up left";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_U)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "up";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_RU)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "up right";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_L)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "left";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_A)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "auto scan";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_R)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "right";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_LD)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "down left";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "down";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_RD)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "down right";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "zoom out";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_I)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "zoom in";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "focus far";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_I)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "focus near";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_IRIS_D)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "iris open";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        } else if (pMsg->hwnd == GetDlgItem(IDC_BTN_IRIS_I)->GetSafeHwnd()) {
                            Json::Value value;
                            value.clear();
                            if (!IsFisheyeMode()) {
                                value["ptz type"] = "normal";
                                value["channel"] = info->channel;
                            }
                            value["operation"] = "iris close";
                            value["flag"] = "stop";
                            value["speed"] = 50;

                            Json::StreamWriterBuilder writer;
                            std::string param = Json::writeString(writer, value);
                            if (!IsFisheyeMode()) {
                                rs_ptz_control(device_session, param.c_str());
                                TRACE("======<rs_ptz_control> device_id:%d\n", device_session);
                            } else {
                                rs_fisheye_ptz_control(preview_session_[i], param.c_str());
                                TRACE("======<rs_fisheye_ptz_control> preview_session:%d\n", preview_session_[i]);
                            }
                        }
                    }
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CPreviewDlg::OnBnClickedBtnCaptureFromDevice()
{
    // TODO: Add your control notification handler code here
    HTREEITEM item = g_device_tree_->GetSelectedItem();
    if (item == NULL) return;
    DEVICE_INFO* info = (DEVICE_INFO*)g_device_tree_->GetItemData(item);
    if (info->type != TYPE_CHANNEL)
        return;

    CString pic_name;
    pic_name.Format(_T("%s%d.jpg"), g_appdata_path_, GetTickCount());

    Json::Value value;
    value.clear();
    value["channel"] = info->channel;
    value["picture name"] = std::string(CT2CA(pic_name));
    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);
    rs_error_code result = rs_capture_picture_from_device(info->device_info->device_session, param.c_str());
    TRACE("======<rs_capture_picture_from_device> result:%d\n", result);
}

void RSNET_CALL capture_buf_callback_fun(unsigned char* data, unsigned int size, int type, void* pUuser){
	// picutre type 0:BMP file£¬1:png file£¬2:jpg file
	FILE* pFile = fopen("D:\\picture.jpg", "ab");
	fwrite(data, size, 1, pFile);
	fclose(pFile);
}

void CPreviewDlg::OnBnClickedBtnCaptureToBuf()
{
	for (int i = 0; i < _countof(window_); i++) {
		if (window_[i].checked_ && preview_session_[i]) {
			capture_picture_buf_param param;
			param.capture_buf_cb = capture_buf_callback_fun;
			param.type = 2;
			param.capture_buf_user_param = this;
			rs_capture_picture_to_buf(preview_session_[i], &param);
			break;
		}
	}
}

void CPreviewDlg::move_window(int index, int x, int y)
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
