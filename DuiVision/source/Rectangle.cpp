#include "StdAfx.h"
#include "Rectangle.h"

CRectangle::CRectangle(HWND hWnd, CDuiObject* pDuiObject)
			: CControlBase(hWnd, pDuiObject)
{
	m_clr = Color(254, 255, 255, 255);
	m_clrFrame = RGB(0, 0, 0);
	m_nFrameWidth = 1;
	m_nDashStyle = DashStyleSolid;
}

CRectangle::CRectangle(HWND hWnd, CDuiObject* pDuiObject, UINT uControlID, CRect rc, 
			 Color clr/* = Color(254, 255, 255, 255)*/, BOOL bIsVisible/* = TRUE*/)
			: CControlBase(hWnd, pDuiObject, uControlID, rc, bIsVisible, FALSE, FALSE)
{
	m_clr = clr;
	m_clrFrame = RGB(0, 0, 0);
	m_nFrameWidth = 1;
	m_nDashStyle = DashStyleSolid;
}

CRectangle::~CRectangle(void)
{
}

void CRectangle::DrawControl(CDC &dc, CRect rcUpdate)
{
	int nWidth = m_rc.Width();
	int nHeight = m_rc.Height();

	if(!m_bUpdate)
	{
		UpdateMemDC(dc, nWidth, nHeight);

		m_memDC.BitBlt(0, 0, nWidth, nHeight, &dc, m_rc.left ,m_rc.top, SRCCOPY);
		
		Graphics graphics(m_memDC);
		// ���������ɫ
		graphics.Clear(m_clr);

		// ����߿򻭱�
		Pen pen(m_clrFrame, (Gdiplus::REAL)m_nFrameWidth);
		pen.SetDashStyle((Gdiplus::DashStyle)m_nDashStyle);

		RectF rect((Gdiplus::REAL)(m_nFrameWidth), (Gdiplus::REAL)(m_nFrameWidth), (Gdiplus::REAL)(nWidth-m_nFrameWidth*2), (Gdiplus::REAL)(nHeight-m_nFrameWidth*2));
		graphics.DrawRectangle(&pen, rect);
	}

	dc.BitBlt(m_rc.left, m_rc.top, m_rc.Width(), m_rc.Height(), &m_memDC, 0, 0, SRCCOPY);
}