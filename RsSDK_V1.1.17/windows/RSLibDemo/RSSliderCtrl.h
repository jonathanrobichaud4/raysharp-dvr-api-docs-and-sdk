#pragma once


// CRSSliderCtrl
#define WM_SLIDER_POSITION (WM_USER+100)

class CRSSliderCtrl : public CSliderCtrl
{
	DECLARE_DYNAMIC(CRSSliderCtrl)

public:
	CRSSliderCtrl();
	virtual ~CRSSliderCtrl();

protected:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

public:
    void SetParentHwnd(HWND parent) { m_hwndParent = parent; }

private:
    bool SetThumb(const CPoint& pt);
    void PostMessageToParent(const int nTBCode) const;
    bool m_bDragging;
    bool m_bDragChanged;
    HWND m_hwndParent;
};


