#pragma once
#include"CCustomBar.h"

#include "DLG_FONT.h"
class CMainFrame : public CFrameWnd
{

protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

	// 特性
public:

	// 操作
public:

	// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CCustomBar        m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CImageList		  m_ImageList;
	CMenu			  m_Menu;
	CToolBar		  m_ToolBar_mode;
	// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnToolTipsNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};