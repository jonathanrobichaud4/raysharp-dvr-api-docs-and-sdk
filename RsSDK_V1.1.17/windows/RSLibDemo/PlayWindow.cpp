// PlayWindow.cpp : implementation file
//

#include "stdafx.h"
#include "RSLibDemo.h"
#include "PlayWindow.h"
#include "PreviewDlg.h"

// CPlayWindow dialog

IMPLEMENT_DYNAMIC(CPlayWindow, CDialog)

CPlayWindow::CPlayWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayWindow::IDD, pParent)
    , parent_(NULL)
    , init_over_(FALSE)
    , checked_(FALSE)
    , info_(NULL)
    , play_id_(0)
{

}

CPlayWindow::~CPlayWindow()
{
}

void CPlayWindow::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_WND, static_wnd_);
}


BEGIN_MESSAGE_MAP(CPlayWindow, CDialog)
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_PAINT()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()


// CPlayWindow message handlers

BOOL CPlayWindow::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here

    init_over_ = TRUE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPlayWindow::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default
    return TRUE;
    return CDialog::OnEraseBkgnd(pDC);
}

void CPlayWindow::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (init_over_) {
        CRect rect;
        GetClientRect(&rect);
        rect.DeflateRect(2, 2, 2, 2);
        GetDlgItem(IDC_STATIC_WND)->MoveWindow(&rect);
    }
}

void CPlayWindow::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: Add your message handler code here
    // Do not call CDialog::OnPaint() for painting messages
    if (checked_) {
        CDC *pDC = &dc;

        CRect rect;
        GetClientRect(&rect);

        CPen myPen(PS_SOLID, 4, RGB(255,0,0));
        CPen *oldPen = pDC->SelectObject(&myPen);
        pDC->MoveTo(rect.left, rect.top);
        pDC->LineTo(rect.right, rect.top);
        pDC->LineTo(rect.right, rect.bottom);
        pDC->LineTo(rect.left, rect.bottom);
        pDC->LineTo(rect.left, rect.top);
        pDC->SelectObject(oldPen);
        myPen.DeleteObject();
    } else {
        CDC *pDC = &dc;

        CRect rect;
        GetClientRect(&rect);

        CPen myPen(PS_SOLID, 4, RGB(240,240,240));
        CPen *oldPen = pDC->SelectObject(&myPen);
        pDC->MoveTo(rect.left, rect.top);
        pDC->LineTo(rect.right, rect.top);
        pDC->LineTo(rect.right, rect.bottom);
        pDC->LineTo(rect.left, rect.bottom);
        pDC->LineTo(rect.left, rect.top);
        pDC->SelectObject(oldPen);
        myPen.DeleteObject();
    }
}

void CPlayWindow::SetParent(CPreviewDlg* parent) {
    parent_ = parent;
}

void CPlayWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (parent_) {
        if (parent_->IsFisheyeMode() && play_id_) {
            CRect ClientRect;
            GetWindowRect(ClientRect);
            ClipCursor(ClientRect);

            Json::Value value;
            value.clear();
            value["mouse flag"] = "mouse lbutton down";
            value["mouse x"] = (float)point.x/ClientRect.Width();
            value["mouse y"] = (float)point.y/ClientRect.Height();
            value["mouse delta"] = (float)0.0;
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            rs_fisheye_mouse_control(play_id_, param.c_str());
        }else{
            parent_->SetCurSel(this);
        }
    }
    CDialog::OnLButtonDown(nFlags, point);
}

void CPlayWindow::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (parent_) {
        if (parent_->IsFisheyeMode() && play_id_) {
            CRect ClientRect;
            GetWindowRect(ClientRect);

            Json::Value value;
            value.clear();
            value["mouse flag"] = "mouse lbutton dbclick";
            value["mouse x"] = (float)point.x/ClientRect.Width();
            value["mouse y"] = (float)point.y/ClientRect.Height();
            value["mouse delta"] = (float)0.0;
            Json::StreamWriterBuilder writer;
            std::string param = Json::writeString(writer, value);
            rs_fisheye_mouse_control(play_id_, param.c_str());
        }else{
            parent_->SetDoubleClick(this);
        }
    }
    CDialog::OnLButtonDblClk(nFlags, point);
}

void CPlayWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (parent_ && parent_->IsFisheyeMode() && play_id_) {
        CRect ClientRect;
        GetWindowRect(ClientRect);

        Json::Value value;
        value.clear();
        value["mouse flag"] = "mouse lbutton up";
        value["mouse x"] = (float)point.x/ClientRect.Width();
        value["mouse y"] = (float)point.y/ClientRect.Height();
        value["mouse delta"] = (float)0.0;
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_fisheye_mouse_control(play_id_, param.c_str());

        ClipCursor(NULL);
    }
    CDialog::OnLButtonUp(nFlags, point);
}

void CPlayWindow::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (parent_ && parent_->IsFisheyeMode() && play_id_) {
        CRect ClientRect;
        GetWindowRect(ClientRect);

        Json::Value value;
        value.clear();
        value["mouse flag"] = "mouse move";
        value["mouse x"] = (float)point.x/ClientRect.Width();
        value["mouse y"] = (float)point.y/ClientRect.Height();
        value["mouse delta"] = (float)0.0;
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_fisheye_mouse_control(play_id_, param.c_str());
    }
    CDialog::OnMouseMove(nFlags, point);
}

BOOL CPlayWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (parent_ && parent_->IsFisheyeMode() && play_id_) {
        CRect ClientRect;
        GetWindowRect(ClientRect);

        Json::Value value;
        value.clear();
        value["mouse flag"] = "mouse wheel";
        value["mouse x"] = (float)point.x/ClientRect.Width();
        value["mouse y"] = (float)point.y/ClientRect.Height();
        value["mouse delta"] = (float)zDelta;
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_fisheye_mouse_control(play_id_, param.c_str());
    }
    return CDialog::OnMouseWheel(nFlags, zDelta, point);
}

void CPlayWindow::OnRButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (parent_ && parent_->IsFisheyeMode() && play_id_) {
        CRect ClientRect;
        GetWindowRect(ClientRect);

        Json::Value value;
        value.clear();
        value["mouse flag"] = "mouse rbutton dbclick";
        value["mouse x"] = (float)point.x/ClientRect.Width();
        value["mouse y"] = (float)point.y/ClientRect.Height();
        value["mouse delta"] = (float)0.0;
        Json::StreamWriterBuilder writer;
        std::string param = Json::writeString(writer, value);
        rs_fisheye_mouse_control(play_id_, param.c_str());
    }
    CDialog::OnRButtonDblClk(nFlags, point);
}
