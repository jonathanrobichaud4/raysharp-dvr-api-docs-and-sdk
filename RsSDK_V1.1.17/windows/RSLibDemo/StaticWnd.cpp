// ShowStaic.cpp : implementation file
//

#include "stdafx.h"
#include "StaticWnd.h"

CStaticWnd::CStaticWnd() : color_(RGB(rand()%256,rand()%256,rand()%256))
{
}

CStaticWnd::~CStaticWnd()
{
}

BEGIN_MESSAGE_MAP(CStaticWnd, CStatic)
	ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowStaic message handlers


BOOL CStaticWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    CRect rc; 
    GetClientRect(rc); 
    pDC->FillSolidRect(rc,color_);
	return TRUE;
	return CStatic::OnEraseBkgnd(pDC);
}

HBRUSH CStaticWnd::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)GetStockObject(NULL_BRUSH);
}
