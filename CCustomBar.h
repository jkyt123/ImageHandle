#pragma once
#include <afxext.h>
class CCustomBar :
    public CToolBar
{
public:
    COLORREF m_TextColor=RGB(0,0,102);
    COLORREF m_HotColor=RGB(230,230,250);
    COLORREF m_LineColor=RGB(0,0,0);
    BOOL m_IsDraw;
    
  
    void DrawButton(CDC *pDC, const RECT &rect,UINT uState);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnOwnerDraw(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

