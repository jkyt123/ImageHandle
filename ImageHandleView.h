
// ImageHandleView.h: CImageHandleView 类的接口
//
#pragma once
#define ORIGIN_SIZE 3131
#define WIDTHFIT_SIZE 3232
#define HEIGHTFIT_SIZE 3132
#define FIT_SIZE 3231
#include "DLG_FONT.h"

class CImageHandleView : public CView
{
protected: // 仅从序列化创建
	CImageHandleView() noexcept;
	DECLARE_DYNCREATE(CImageHandleView)

// 特性
public:
	CImageHandleDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImageHandleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_FileName;			//打开图片的目录
	CString saveFileName;		//保存图片的目录
	CImage* image;				//加载的图片
	CRect rect;
	BOOL mirror_flag;           //限制镜面对称次数，限一次
	BOOL m_cut;					//是否裁剪
	BOOL m_clik;				//左键点起
	CPoint m_StartPoint;		//裁剪起始坐标
	CPoint m_EndPoint;			//结束坐标
	REAL mul;					//适应屏幕的比例
	int show_mode;				//显示模式
	int x;						//图片居中显示水平值
	int y;						//图片居中显示垂直值
	int offsetx;				//图片加载偏移值x水平
	int offsety;				//图片加载偏移值y垂直
	int viewWid;				//图片显示宽度
	int	viewHei;				//高度
	void drawpic();				//画图函数
	void setviewsize();			//设置图片显示大小
	void setscroll();			//设置滚动条
	void clearbak();			//清空背景
	void drawrangle();			//画矩形框
	void roicut();				//裁剪
	void impore(int*,float);
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonOpenfile();
	afx_msg void OnMenuOpenfile();
	afx_msg void OnBtnSaveBmp();
	afx_msg void OnBtnSavejpeg();
	afx_msg void OnBtnSavepng();
	afx_msg void OnBtnSavetiff();
	afx_msg void OnBtnSavegif();
	afx_msg void OnBtnSaveicon();
	afx_msg void OnButtonOrsize();
	afx_msg void OnButtonHesize();
	afx_msg void OnButtonFisize();
	afx_msg void OnButtonWisize();
	afx_msg void OnUpdateButtonOrsize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonHesize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonFisize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonWisize(CCmdUI* pCmdUI);
	afx_msg void OnButtonRotate();
	afx_msg void OnButtonCut();
	afx_msg void OnButtonMirror();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateButtonCut(CCmdUI* pCmdUI);
	afx_msg void OnButtonSetfont();

	afx_msg void OnMenugrayhandle();
	afx_msg void OnButtonScale();
	afx_msg void OnMenubmpsharp();
	afx_msg void OnSmooth();
	afx_msg void OnMenureversecolor();
};

#ifndef _DEBUG  // ImageHandleView.cpp 中的调试版本
inline CImageHandleDoc* CImageHandleView::GetDocument() const
   { return reinterpret_cast<CImageHandleDoc*>(m_pDocument); }
#endif

