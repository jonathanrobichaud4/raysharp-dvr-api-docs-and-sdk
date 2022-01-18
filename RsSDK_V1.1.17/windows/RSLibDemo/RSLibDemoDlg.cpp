
// RSLibDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "RSLibDemoDlg.h"
#include "MiniDumper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRSLibDemoDlg dialog

CRSLibDemoDlg::CRSLibDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRSLibDemoDlg::IDD, pParent)
    , init_over_(FALSE)
	, dump_(true)
    , human_face_alarm_id_(0)
    , human_face_param_id_(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRSLibDemoDlg::~CRSLibDemoDlg() {
    
}

void CRSLibDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_GLOBAL, tabctrl_);
    DDX_Control(pDX, IDC_TREE_DEVICE, treectrl_device_);
}

BEGIN_MESSAGE_MAP(CRSLibDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_SIZE()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_GLOBAL, &CRSLibDemoDlg::OnTcnSelchangeTabGlobal)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEVICE, &CRSLibDemoDlg::OnNMDblclkTreeDev)
    ON_NOTIFY(NM_RCLICK, IDC_TREE_DEVICE, &CRSLibDemoDlg::OnNMRClickTreeDevice)
    ON_COMMAND(ID_STARTPREVIEW, &CRSLibDemoDlg::OnStartpreview)
    ON_COMMAND(ID_STOPPREVIEW, &CRSLibDemoDlg::OnStoppreview)
    ON_COMMAND(ID_STARTTALK, &CRSLibDemoDlg::OnStartTalk)
    ON_COMMAND(ID_STOPTALK, &CRSLibDemoDlg::OnStopTalk)
    ON_COMMAND(ID_MAIN_STREAM, &CRSLibDemoDlg::OnMainStream)
    ON_COMMAND(ID_SUBSTREAM, &CRSLibDemoDlg::OnSubStream)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRSLibDemoDlg message handlers

BOOL CRSLibDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    SetWindowText(_T("RSLibDemo-1.1.17"));
    g_device_tree_ = &treectrl_device_;

    CBitmap bmp;
    bmp.LoadBitmap(IDB_BITMAP_LIST);
    image_list_.Create(18,18,ILC_MASK |ILC_COLOR32,2,2);
    image_list_.Add(&bmp, RGB(205,205,207));
    treectrl_device_.SetImageList(&image_list_, TVSIL_NORMAL);
    DWORD dwStyles=GetWindowLong(treectrl_device_.m_hWnd,GWL_STYLE);
    dwStyles|=TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS;
    SetWindowLong(treectrl_device_.m_hWnd,GWL_STYLE,dwStyles);

    int index = 0;
    if (search_dlg_.GetSafeHwnd() == NULL)
        search_dlg_.Create(CSearchDlg::IDD, &tabctrl_);
    tabctrl_.InsertItem(index++, _T("Search"));
    search_dlg_.SetParentWindow(this);
    search_dlg_.ShowWindow(SW_HIDE);
    vec_dialog_.push_back(&search_dlg_);

    if (preview_dlg_.GetSafeHwnd() == NULL)
        preview_dlg_.Create(CPreviewDlg::IDD, &tabctrl_);
    tabctrl_.InsertItem(index++, _T("Preview"));
    preview_dlg_.SetParentWindow(this);
    preview_dlg_.ShowWindow(SW_HIDE);
    vec_dialog_.push_back(&preview_dlg_);

    if (playback_dlg_.GetSafeHwnd() == NULL)
        playback_dlg_.Create(CPlaybackDlg::IDD, &tabctrl_);
    tabctrl_.InsertItem(index++, _T("Playback"));
    playback_dlg_.SetParentWindow(this);
    playback_dlg_.ShowWindow(SW_HIDE);
    vec_dialog_.push_back(&playback_dlg_);

    if (config_dlg_.GetSafeHwnd() == NULL)
        config_dlg_.Create(CConfigDlg::IDD, &tabctrl_);
    tabctrl_.InsertItem(index++, _T("Config"));
    config_dlg_.SetParentWindow(this);
    config_dlg_.ShowWindow(SW_HIDE);
    vec_dialog_.push_back(&config_dlg_);

    if (player_dlg_.GetSafeHwnd() == NULL)
        player_dlg_.Create(CPlayerDlg::IDD, &tabctrl_);
    tabctrl_.InsertItem(index++, _T("Player"));
    player_dlg_.SetParentWindow(this);
    player_dlg_.ShowWindow(SW_HIDE);
    vec_dialog_.push_back(&player_dlg_);

    if (log_dlg_.GetSafeHwnd() == NULL)
        log_dlg_.Create(CLogInfoDlg::IDD, &tabctrl_);
    tabctrl_.InsertItem(index++, _T("Log"));
    log_dlg_.ShowWindow(SW_HIDE);
    vec_dialog_.push_back(&log_dlg_);

    tabctrl_.SetCurSel(1);
    vec_dialog_.at(1)->ShowWindow(SW_SHOW);
    init_over_ = TRUE;
    PostMessage(WM_SIZE);

    ReadDeviceInfo();

    //ShowWindow(SW_SHOWMAXIMIZED);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRSLibDemoDlg::OnClose()
{
    preview_dlg_.StopAll();
    playback_dlg_.StopAll();
    player_dlg_.StopAll();

    WriteDeviceInfo();

    init_over_ = FALSE;
    for (size_t i = 0; i < vec_info_.size(); i++) {
        LogOutDevice(vec_info_.at(i));
        if (vec_info_.at(i)->device_session)
            rs_destroy_device(vec_info_.at(i)->device_session);
        delete vec_info_.at(i);
    }

    CDialog::OnClose();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRSLibDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRSLibDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRSLibDemoDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        CRect rect_client;
        GetClientRect(&rect_client);

        CRect rect_temp;
        treectrl_device_.GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        rect_temp.bottom = rect_client.bottom - 10;
        treectrl_device_.MoveWindow(&rect_temp);

        tabctrl_.GetWindowRect(&rect_temp);
        ScreenToClient(&rect_temp);
        rect_temp.right = rect_client.right - 10;
        rect_temp.bottom = rect_client.bottom - 10;
        tabctrl_.MoveWindow(&rect_temp);

        CRect rect_tabctrl;
        tabctrl_.GetClientRect(&rect_tabctrl);
        rect_tabctrl.DeflateRect(1, 21, 3, 2);
        if (search_dlg_.GetSafeHwnd())
            search_dlg_.MoveWindow(&rect_tabctrl);
        if (preview_dlg_.GetSafeHwnd())
            preview_dlg_.MoveWindow(&rect_tabctrl);
        if (playback_dlg_.GetSafeHwnd())
            playback_dlg_.MoveWindow(&rect_tabctrl);
        if (config_dlg_.GetSafeHwnd())
            config_dlg_.MoveWindow(&rect_tabctrl);
        if (player_dlg_.GetSafeHwnd())
            player_dlg_.MoveWindow(&rect_tabctrl);
        if (log_dlg_.GetSafeHwnd())
            log_dlg_.MoveWindow(&rect_tabctrl);
    }
}

void CRSLibDemoDlg::OnTcnSelchangeTabGlobal(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    int index = tabctrl_.GetCurSel();
    int count = vec_dialog_.size();
    for (int i = 0; i < count; i++) {
        if (i != index)
            vec_dialog_.at(i)->ShowWindow(SW_HIDE);
        else
            vec_dialog_.at(i)->ShowWindow(SW_SHOW);
    }

    *pResult = 0;
}

void CRSLibDemoDlg::InitDevice(DEVICE_INFO* info) {
    info->type = TYPE_DEVICE;
    info->ip = _T("");
    info->ip_type = _T("");
    info->mediaport = 0;
    info->username = _T("");
    info->password = _T("");
    info->channel = -1;
    info->device_session = 0;
    info->talk_session = 0;
    info->preview_session = 0;
    info->device_info = NULL;
    info->item = NULL;
    info->online_status = false;
    info->in_preview_status = false;
}

void CRSLibDemoDlg::AddDevice(CString& str_ip, CString& str_port, CString& str_name, CString& str_password, CString ip_type) {
    DEVICE_INFO* info = new DEVICE_INFO;
    InitDevice(info);
    {
        rs_app_scoped_lock lock(mutex_);
        vec_info_.push_back(info);
    }

    info->type = TYPE_DEVICE;
    info->ip = str_ip;
    info->ip_type = ip_type;
    info->mediaport = _ttoi(str_port);
    info->username = str_name;
    info->password = str_password;
    info->device_session = rs_create_device();
    info->user_param = this;
    info->item = treectrl_device_.InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE, \
        str_ip, ICO_DEV_LOGOUT, ICO_DEV_LOGOUT, 0, 0, (LPARAM)info, TVI_ROOT, TVI_LAST);
    LoginDevice(info);
}

void RSNET_CALL connction_callback_fun(const char* param, void* user_param) {
    DEVICE_INFO* info = (DEVICE_INFO*)(user_param);
    if (param && info && info->user_param) {
        CRSLibDemoDlg* this_ = (CRSLibDemoDlg*)(info->user_param);
        if (this_ && this_->InitOver())
            this_->connction_callback(param, info);
    }
}

void RSNET_CALL alarm_callback_fun(const char* alarm_type, const char* param, void* user_param) {
    DEVICE_INFO* info = (DEVICE_INFO*)(user_param);
    if (param && info && info->user_param) {
        CRSLibDemoDlg* this_ = (CRSLibDemoDlg*)(info->user_param);
        if (this_ && this_->InitOver())
            this_->alarm_callback(alarm_type, param, info);
    }
}

void RSNET_CALL human_face_alarm_report_data_callback_fun(const char* param, int size, void* user_param) {
    TRACE("======<human_face_alarm_report_data_callback_fun> size:%d\n", size);
}

void RSNET_CALL human_face_alarm_report_status_callback_fun(const char* param, void* user_param) {
    TRACE("======<human_face_alarm_report_status_callback_fun> param:%s\n", param);
}

void RSNET_CALL human_face_param_data_callback_fun(const char* param, int size, void* user_param) {
    TRACE("======<human_face_param_data_callback_fun> size:%d\n", size);
}

void RSNET_CALL human_face_param_status_callback_fun(const char* param, void* user_param) {
    TRACE("======<human_face_param_status_callback_fun> param:%s\n", param);
}

void CRSLibDemoDlg::LoginDevice(DEVICE_INFO* info) {
    if (info->type != TYPE_DEVICE)
        return;
    LogOutDevice(info);

    Json::Value value;
    value.clear();
    value["ip or id"] = std::string(CT2CA(info->ip));
    value["media port"] = info->mediaport;
    value["user"] = std::string(CT2CA(info->username));
    value["password"] = std::string(CT2CA(info->password));
    value["ddns id server addr"] = "";
    value["p2p type"] = std::string(CT2CA(info->ip_type));
    value["oem type"] = "default";

    /*
    //for p2p begin with RSV
    Json::Value value;
    value.clear();
    value["ip or id"] = "RSV1234567891011";
    value["media port"] = 9000;
    value["user"] = "admin";
    value["password"] = "admin";
    value["ddns id server addr"] = "";
    value["p2p type"] = "rsvv";
    value["oem type"] = "default";
    */

    Json::StreamWriterBuilder writer;
    std::string param = Json::writeString(writer, value);

    device_login_param login_info = {0};
    login_info.dev = info->device_session;
    login_info.param = param.c_str();
    login_info.conn_cb = connction_callback_fun;
    login_info.alarm_cb = alarm_callback_fun;
    login_info.user_param = info;
    rs_error_code result = rs_device_login_ex(&login_info);
    TRACE("======<rs_device_login> result:%d\n", result);

#if 0
    {
        human_face_alarm_report_param temp_param = {0};
        temp_param.dev = info->device_session;
        temp_param.data_callback = human_face_alarm_report_data_callback_fun;
        temp_param.status_callback = human_face_alarm_report_status_callback_fun;
        temp_param.user_param = info;
        human_face_alarm_id_ = rs_start_human_face_alarm_report(&temp_param);
    }

    {
        human_face_param temp_param = {0};
        temp_param.dev = info->device_session;
        temp_param.data_callback = human_face_param_data_callback_fun;
        temp_param.status_callback = human_face_param_status_callback_fun;
        temp_param.user_param = info;
        human_face_param_id_ = rs_start_human_face_param(&temp_param);

        //never call these function
        //if (human_face_param_id_) {
        //    Json::Value data(Json::objectValue);        //    data["msgType"] = "AI_getGroupConfig";
        //    Json::Value objectVal(Json::objectValue);
        //    objectVal["TypeFlags"] = 1;
        //    objectVal["DefaultVal"] = 0;
        //    objectVal["WithInternal"] = 1;
        //    data["data"] = objectVal;
        //    Json::StreamWriterBuilder writer;
        //    std::string _param = Json::writeString(writer, data);
        //    rs_send_human_face_param(human_face_param_id_, _param.c_str(), _param.length());
        //}
    }
#endif
}

void CRSLibDemoDlg::LogOutDevice(DEVICE_INFO* info) {
    if (info->type != TYPE_DEVICE)
        return;

    if (human_face_alarm_id_)
        rs_stop_human_face_alarm_report(human_face_alarm_id_);
    if (human_face_param_id_)
        rs_stop_human_face_param(human_face_param_id_);
    human_face_alarm_id_ = 0;
    human_face_param_id_ = 0;

    rs_error_code result = rs_device_logout(info->device_session);
    TRACE("======<rs_device_logout> result:%d\n", result);
}

void CRSLibDemoDlg::connction_callback(const char* param, DEVICE_INFO* info) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return;

    int ico_num = -1;
    const char* status = value["status"].asCString();
    if (!strcmp(status, "connecting")) {
        ico_num = ICO_DEV_LOGOUT;
    } else if (!strcmp(status, "success")) {
        ico_num = ICO_DEV_LOGIN;
    } else if (!strcmp(status, "p2p mode")) {
        ico_num = -1;
    } else if (!strcmp(status, "relay mode")) {
        ico_num = -1;
    } else {
        ico_num = ICO_DEV_LOGOUT;
    }
    if (info->type == TYPE_DEVICE && ico_num != -1) {
        if (ico_num == ICO_DEV_LOGIN)
            info->online_status = true;
        else
            info->online_status = false;

        treectrl_device_.SetItemImage(info->item,ico_num,ico_num);
        if (ico_num == ICO_DEV_LOGIN) {
            HTREEITEM sub_item = treectrl_device_.GetChildItem(info->item);
            if (sub_item == NULL) {
                int dev_type = rs_get_device_type(info->device_session);
                if (dev_type != 6) {
                    int channel = rs_get_channel_number(info->device_session);
                    for (int i = 0; i < channel; i++) {
                        DEVICE_INFO* channel_info = new DEVICE_INFO;
                        InitDevice(channel_info);
                        {
                            rs_app_scoped_lock lock(mutex_);
                            vec_info_.push_back(channel_info);
                        }

                        channel_info->type = TYPE_CHANNEL;
                        channel_info->user_param = this;
                        channel_info->device_info = info;
                        channel_info->channel = i;
                        CString str_channel;
                        str_channel.Format(_T("CH%02d"), i+1);
                        channel_info->online_status = false;

                        channel_info->item = treectrl_device_.InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE, \
                            str_channel, ICO_CH_OFFLINE, ICO_CH_OFFLINE, 0, 0, (LPARAM)channel_info, info->item, TVI_LAST);
                    }
                } else { //DEV_HDVR
                    int channel = rs_get_channel_number(info->device_session);
                    int analogy_channle = rs_get_analogy_channel_number(info->device_session);
                    int digital_channel = channel - analogy_channle;
                    for (int i = 0; i < analogy_channle; i++) {
                        DEVICE_INFO* channel_info = new DEVICE_INFO;
                        InitDevice(channel_info);
                        {
                            rs_app_scoped_lock lock(mutex_);
                            vec_info_.push_back(channel_info);
                        }

                        channel_info->type = TYPE_CHANNEL;
                        channel_info->user_param = this;
                        channel_info->device_info = info;
                        channel_info->channel = i;
                        CString str_channel;
                        str_channel.Format(_T("CH%02d"), i+1);

                        channel_info->online_status = false;
                        channel_info->item = treectrl_device_.InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE, \
                            str_channel, ICO_CH_OFFLINE, ICO_CH_OFFLINE, 0, 0, (LPARAM)channel_info, info->item, TVI_LAST);
                    }

                    for (int i = 0; i < digital_channel; i++) {
                        DEVICE_INFO* channel_info = new DEVICE_INFO;
                        InitDevice(channel_info);
                        {
                            rs_app_scoped_lock lock(mutex_);
                            vec_info_.push_back(channel_info);
                        }

                        channel_info->type = TYPE_CHANNEL;
                        channel_info->user_param = this;
                        channel_info->device_info = info;
                        channel_info->channel = analogy_channle+i;
                        CString str_channel;
                        str_channel.Format(_T("IP CH%02d"), i+1);

                        channel_info->online_status = false;
                        channel_info->item = treectrl_device_.InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE, \
                            str_channel, ICO_CH_OFFLINE, ICO_CH_OFFLINE, 0, 0, (LPARAM)channel_info, info->item, TVI_LAST);
                    }
                }
                treectrl_device_.Expand(info->item,TVE_EXPAND);
            }
        } else { //logout
            HTREEITEM sub_item = treectrl_device_.GetChildItem(info->item);
            while (sub_item) {
                DEVICE_INFO* channel_info = (DEVICE_INFO*)(treectrl_device_.GetItemData(sub_item));
                channel_info->online_status = false;
                treectrl_device_.SetItemImage(sub_item,ICO_CH_OFFLINE,ICO_CH_OFFLINE);
                sub_item = treectrl_device_.GetNextSiblingItem(sub_item);
            }
        }
    }
}

void CRSLibDemoDlg::alarm_callback(const char* alarm_type, const char* param, DEVICE_INFO* info) {
    std::string err = "";
    Json::CharReaderBuilder reader;
    Json::Value value;
    if(!Json::parseFromStream(reader, param, &value, &err))
        return;

    if (!strcmp(alarm_type, "RSSDKChannelStatus")) {
        for (Json::ArrayIndex i = 0 ; i < value.size(); i++) {
            int ico_num = value[i]["online"].asBool() ? ICO_CH_ONLINE : ICO_CH_OFFLINE;
            if (info->type == TYPE_DEVICE) {
                HTREEITEM sub_item = treectrl_device_.GetChildItem(info->item);
                while (sub_item) {
                    DEVICE_INFO* channel_info = (DEVICE_INFO*)(treectrl_device_.GetItemData(sub_item));
                    if (channel_info->channel == i) {
                        if (ico_num == ICO_CH_ONLINE)
                            channel_info->online_status = true;
                        else
                            channel_info->online_status = false;

                        int real_ico_num = ICO_CH_ONLINE;
                        if (ico_num == ICO_CH_ONLINE)
                            real_ico_num = channel_info->in_preview_status ? ICO_CH_ONLINE_PREIVEW : ICO_CH_ONLINE;
                        else if (ico_num == ICO_CH_OFFLINE)
                            real_ico_num = channel_info->in_preview_status ? ICO_CH_OFFLINE_PREIVEW : ICO_CH_OFFLINE;
                        treectrl_device_.SetItemImage(sub_item,real_ico_num,real_ico_num);
                        break;
                    }
                    sub_item = treectrl_device_.GetNextSiblingItem(sub_item);
                }
            }
        }
    }

    preview_dlg_.alarm_callback(alarm_type, param, info);
}

static void CALLBACK log_sink_callback_fun(const char* message, void* reserve) {
    OutputDebugStringA(message);
}

void CRSLibDemoDlg::ReadDeviceInfo() {
    TCHAR path[MAX_PATH] = {0};
    GetModuleFileName(NULL, path, MAX_PATH - 1);
    *_tcsrchr(path, _T('\\')) = _T('\0');
    {
        Json::Value value;
        value.clear();
        value["directory"] = std::string(CT2CA(path));
        value["max size"] = 0;
        value["enable p2p log"] = true;
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);

        init_log_ex_param _param = {0};
        _param.param = param.c_str();
        _param.bugly_callback = log_sink_callback_fun;
        rs_init_log_ex(&_param);
    }
    _tcscat(path, _T("\\deviceinfo.xml"));

    CString str_type = _T("ip");
    CString str_ip, str_port, str_username, str_password;
    CMarkup xml;
    if (xml.Load(path)) {
        xml.ResetPos();
        if (xml.FindElem(TEXT("DEVICEINFOS"))) {
            xml.IntoElem();
            while(xml.FindElem(TEXT("DEVICEINFO"))) {
                xml.IntoElem();

                if (xml.FindElem(TEXT("IP")))
                    str_ip = xml.GetData();
                if (xml.FindElem(TEXT("TYPE")))
                    str_type = xml.GetData();
                if (xml.FindElem(TEXT("PORT")))
                    str_port = xml.GetData();
                if (xml.FindElem(TEXT("USERNAME")))
                    str_username = xml.GetData();
                if (xml.FindElem(TEXT("PASSWORD")))
                    str_password = xml.GetData();
                if (!str_ip.IsEmpty() && !str_port.IsEmpty())
                    AddDevice(str_ip, str_port, str_username, str_password, str_type);

                xml.OutOfElem();
            }
            xml.OutOfElem();
        }
    }
}

void CRSLibDemoDlg::WriteDeviceInfo() {
    CMarkup xml;
    xml.SetDoc(TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"));
    xml.AddElem(TEXT("DEVICEINFOS"));
    xml.IntoElem();

    std::size_t size = vec_info_.size();
    for (size_t i = 0; i < size; i++) {
        DEVICE_INFO* device = vec_info_.at(i);
        if (device && device->type == TYPE_DEVICE && !device->ip.IsEmpty()) {
            CString str_port;
            str_port.Format(_T("%d"), device->mediaport);

            xml.AddElem(TEXT("DEVICEINFO"));
            xml.IntoElem();
            xml.AddElem(TEXT("IP"), device->ip);
            xml.AddElem(TEXT("TYPE"), device->ip_type);
            xml.AddElem(TEXT("PORT"), str_port);
            xml.AddElem(TEXT("USERNAME"), device->username);
            xml.AddElem(TEXT("PASSWORD"), device->password);
            xml.OutOfElem();
        }
    }

    xml.OutOfElem();

    TCHAR path[MAX_PATH] = {0};
    GetModuleFileName(NULL, path, MAX_PATH - 1);
    *_tcsrchr(path, _T('\\')) = _T('\0');
    _tcscat(path, _T("\\deviceinfo.xml"));
    const CString& write_doc = xml.GetDoc();
    {
        CMarkup read_xml;
        if (read_xml.Load(path)) {
            const CString& read_doc = read_xml.GetDoc();
            if (read_doc == write_doc)
                return;
        }
    }
    xml.Save(path);
}

void CRSLibDemoDlg::OnNMDblclkTreeDev(NMHDR *pNMHDR, LRESULT *pResult) {
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
    if (info->type == TYPE_CHANNEL) {
        if (info->in_preview_status) {
            preview_dlg_.StopPreview(info);
        } else {
            preview_dlg_.StartPreview(info);
        }
    }
}

void CRSLibDemoDlg::OnNMRClickTreeDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    UINT flag;
    CPoint pt;
    GetCursorPos(&pt);
    treectrl_device_.ScreenToClient(&pt);

    HTREEITEM item = treectrl_device_.HitTest(pt, &flag);
    if (item) {
        treectrl_device_.SelectItem(item);
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_DEVICE && info->online_status) {
            CPoint point;
            GetCursorPos(&point);

            CMenu menu, *p_menu;
            menu.LoadMenu(IDR_MENU_DEVICE_TREECTRL);
            p_menu = menu.GetSubMenu(0);
            p_menu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
            p_menu->Detach();
            menu.DestroyMenu();
        } else if (info->type == TYPE_CHANNEL && info->online_status && info->in_preview_status) {
            CPoint point;
            GetCursorPos(&point);

            CMenu menu, *p_menu;
            menu.LoadMenu(IDR_MENU_STREAM_TYPE);
            p_menu = menu.GetSubMenu(0);
            p_menu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
            p_menu->Detach();
            menu.DestroyMenu();
        }
    }

    *pResult = 0;
}


void CRSLibDemoDlg::OnStartpreview()
{
    // TODO: Add your command handler code here
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    if (item) {
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_DEVICE && info->online_status) {
            HTREEITEM sub_item = treectrl_device_.GetChildItem(info->item);
            while (sub_item) {
                DEVICE_INFO* channel_info = (DEVICE_INFO*)(treectrl_device_.GetItemData(sub_item));
                if (!channel_info->in_preview_status && channel_info->online_status)
                    preview_dlg_.StartPreview(channel_info);
                sub_item = treectrl_device_.GetNextSiblingItem(sub_item);
            }
        }
    }
}

void CRSLibDemoDlg::OnStoppreview()
{
    // TODO: Add your command handler code here
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    if (item) {
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_DEVICE && info->online_status) {
            HTREEITEM sub_item = treectrl_device_.GetChildItem(info->item);
            while (sub_item) {
                DEVICE_INFO* channel_info = (DEVICE_INFO*)(treectrl_device_.GetItemData(sub_item));
                if (channel_info->in_preview_status)
                    preview_dlg_.StopPreview(channel_info);
                sub_item = treectrl_device_.GetNextSiblingItem(sub_item);
            }
        }
    }
}

void RSNET_CALL talk_callback_fun(const char* param, void* user_param) {
    TRACE("======talk_callback_fun:%s\n", param);
}

void CRSLibDemoDlg::OnStartTalk() {
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    if (item) {
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_DEVICE && info->online_status) {
            Json::Value value;
            value.clear();
            value["talk mode"] = "old mode";
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);

            info->talk_session = rs_start_talk_to_device(info->device_session, param.c_str(), talk_callback_fun, this);
            TRACE("======rs_start_talk_to_device: talk_session:%d\n", info->talk_session);
        }
    }
}

void CRSLibDemoDlg::OnStopTalk() {
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    if (item) {
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_DEVICE && info->online_status) {
            if (info->talk_session > 0) {
                rs_stop_talk(info->talk_session);
                info->talk_session = 0;
            }
        }
    }
}

void CRSLibDemoDlg::OnMainStream() {
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    if (item) {
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_CHANNEL && info->online_status && info->in_preview_status) {
            if (info->preview_session > 0) {
                Json::Value value;
                value.clear();
                value["stream type"] = "main stream";
                Json::StreamWriterBuilder writer;
                std::string param = Json::writeString(writer, value);
                rs_switch_stream_type(info->preview_session, param.c_str());
            }
        }
    }
}

void CRSLibDemoDlg::OnSubStream() {
    HTREEITEM item = treectrl_device_.GetSelectedItem();
    if (item) {
        DEVICE_INFO* info = (DEVICE_INFO*)treectrl_device_.GetItemData(item);
        if (info->type == TYPE_CHANNEL && info->online_status && info->in_preview_status) {
            if (info->preview_session > 0) {
                Json::Value value;
                value.clear();
                value["stream type"] = "sub stream";
                Json::StreamWriterBuilder writer;
                std::string param = Json::writeString(writer, value);
                rs_switch_stream_type(info->preview_session, param.c_str());
            }
        }
    }
}
