#pragma once
/////////////////////////////////////////////////////////////////////////////
// CStaticWnd window

class CStaticWnd : public CStatic
{
public:
	CStaticWnd();

public:
	virtual ~CStaticWnd();

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

    DECLARE_MESSAGE_MAP()

private:
    COLORREF color_;
};

