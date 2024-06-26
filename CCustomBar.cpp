#include "pch.h"
#include "CCustomBar.h"

void CCustomBar::OnOwnerDraw(NMHDR* pNotifyStruct, LRESULT* pResult) {
	NMTBCUSTOMDRAW* pCustomDraw = (NMTBCUSTOMDRAW*)pNotifyStruct;
	CDC  dc;
	dc.Attach(pCustomDraw->nmcd.hdc);
	pCustomDraw->clrText = m_TextColor;
	switch (pCustomDraw->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		if (pCustomDraw->nmcd.uItemState & CDIS_HOT)
			pCustomDraw->clrBtnFace = m_HotColor;
		DrawButton(&dc,pCustomDraw->nmcd.rc,pCustomDraw->nmcd.uItemState);
		*pResult = TBCDRF_NOEDGES;
		break;
	}
	dc.Detach();
}
void CCustomBar::DrawButton(CDC* pDC, const RECT& rect, UINT uState) {
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	CRect rect1;
	GetClientRect(rect1);
	if (rect1.PtInRect(pt)) {
		if (uState & CDIS_HOT) {
			CPen pen(PS_SOLID, 1, m_LineColor);
			CPen* pOldPen = pDC->SelectObject(&pen);
			CBrush brush(m_HotColor);
			CBrush* pOldBrush = pDC->SelectObject(&brush);
			pDC->Rectangle(&rect);
			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldPen);
		}
	}
}
BEGIN_MESSAGE_MAP(CCustomBar, CToolBar)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CCustomBar::OnOwnerDraw)

	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CCustomBar::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(rect, RGB(255, 250, 240));
	return CToolBar::OnEraseBkgnd(pDC);
}
