// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "ImageHandle.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipsNotify)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->hMenu = LoadMenu(AfxGetResourceHandle(), MAKEINTRESOURCE(lpCreateStruct));

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this)||
		!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 1, 1);
	m_ImageList.SetBkColor(CLR_NONE);
	//
	CBitmap bmp;
	for (int i = 0; i < 7; i++)
	{
		bmp.LoadBitmap(IDB_BITMAP2 + i);
		m_ImageList.Add(&bmp, RGB(255, 255, 255));
		bmp.DeleteObject();
	}




	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR);
	m_wndToolBar.SetButtonText(0, L"打开图片");
	m_wndToolBar.SetButtonText(2, L"旋转图片");
	m_wndToolBar.SetButtonText(3, L"剪切图片");
	m_wndToolBar.SetButtonText(4, L"插入文字");
	m_wndToolBar.SetButtonText(5, L"图片镜面对称");
	m_wndToolBar.SetButtonText(6, L"缩放拉伸");

	m_wndToolBar.SetSizes(CSize(80, 50), CSize(28,30));
	// TODO: 如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	//m_Menu.AttatchMenu(GetMenu()->GetSafeHmenu());
	//m_Menu.SetMenuItemInfo(&m_Menu,TRUE);
	if (!m_ToolBar_mode.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE 
		|CBRS_BORDER_LEFT| CBRS_ALIGN_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) {
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_ToolBar_mode.LoadToolBar(IDR_TOOLBAR_MODE);
	return 0;
}

BOOL CMainFrame::OnToolTipsNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	TOOLTIPTEXT* pT = (TOOLTIPTEXT*)pNMHDR; //将pNMHDR转换成TOOLTIPTEXT指针类型数据

	UINT    nID = pNMHDR->idFrom;  //获取工具条上按钮的ID
	switch (nID) {
	case ID_BUTTON_ORSIZE:pT->lpszText = L"原始大小"; break;
	case ID_BUTTON_WISIZE:pT->lpszText = L"适合宽度"; break;
	case ID_BUTTON_HESIZE:pT->lpszText = L"适合高度"; break;
	case ID_BUTTON_FISIZE:pT->lpszText = L"适应大小"; break;
	}
	return FALSE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG




void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
