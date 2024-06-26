
// ImageHandleView.cpp: CImageHandleView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageHandle.h"
#endif

#include "ImageHandleDoc.h"
#include "ImageHandleView.h"
#include "marco.h"
#include"DLG_SIZE.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageHandleView

IMPLEMENT_DYNCREATE(CImageHandleView, CView)

BEGIN_MESSAGE_MAP(CImageHandleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageHandleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_OPENFILE, &CImageHandleView::OnButtonOpenfile)
	ON_COMMAND(ID_MENU_OPENFILE, &CImageHandleView::OnMenuOpenfile)
	ON_COMMAND(ID_BTN_SAVEBMP, &CImageHandleView::OnBtnSaveBmp)
	ON_COMMAND(ID_BTN_SAVEJPEG, &CImageHandleView::OnBtnSavejpeg)
	ON_COMMAND(ID_BTN_SAVEPNG, &CImageHandleView::OnBtnSavepng)
	ON_COMMAND(ID_BTN_SAVETIFF, &CImageHandleView::OnBtnSavetiff)
	ON_COMMAND(ID_BTN_SAVEGIF, &CImageHandleView::OnBtnSavegif)
	ON_COMMAND(ID_BTN_SAVEICON, &CImageHandleView::OnBtnSaveicon)
	ON_COMMAND(ID_BUTTON_ORSIZE, &CImageHandleView::OnButtonOrsize)
	ON_COMMAND(ID_BUTTON_HESIZE, &CImageHandleView::OnButtonHesize)
	ON_COMMAND(ID_BUTTON_FISIZE, &CImageHandleView::OnButtonFisize)
	ON_COMMAND(ID_BUTTON_WISIZE, &CImageHandleView::OnButtonWisize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ORSIZE, &CImageHandleView::OnUpdateButtonOrsize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_HESIZE, &CImageHandleView::OnUpdateButtonHesize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FISIZE, &CImageHandleView::OnUpdateButtonFisize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WISIZE, &CImageHandleView::OnUpdateButtonWisize)
	ON_COMMAND(ID_BUTTON_ROTATE, &CImageHandleView::OnButtonRotate)
	ON_COMMAND(ID_BUTTON_CUT, &CImageHandleView::OnButtonCut)
	ON_COMMAND(ID_BUTTON_MIRROR, &CImageHandleView::OnButtonMirror)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CUT, &CImageHandleView::OnUpdateButtonCut)
	ON_COMMAND(ID_BUTTON_SETFONT, &CImageHandleView::OnButtonSetfont)

	ON_COMMAND(ID_MENUGRAYHANDLE, &CImageHandleView::OnMenugrayhandle)
	ON_COMMAND(ID_BUTTON_SCALE, &CImageHandleView::OnButtonScale)
	ON_COMMAND(ID_MENUBMPSHARP, &CImageHandleView::OnMenubmpsharp)
	ON_COMMAND(ID_SMOOTH, &CImageHandleView::OnSmooth)
	ON_COMMAND(ID_MENUREVERSECOLOR, &CImageHandleView::OnMenureversecolor)
END_MESSAGE_MAP()

// CImageHandleView 构造/析构

CImageHandleView::CImageHandleView() noexcept
{
	// TODO: 在此处添加构造代码
	show_mode = FIT_SIZE;
	image = NULL;
	x = 0;
	y = 0;
	offsetx = 0;
	offsety = 0;
	viewHei = 0;
	viewWid = 0;
	mirror_flag = false;
	m_cut = FALSE;
	m_clik = FALSE;
	mul = 0.0f;
}

CImageHandleView::~CImageHandleView()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

BOOL CImageHandleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CImageHandleView 绘图

void CImageHandleView::OnDraw(CDC* pDC/*pDC*/)
{
	CImageHandleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	::SetWindowText(GetParent()->m_hWnd, L"图像处理软件");
	CBitmap BMP;
	BMP.LoadBitmapW(IDB_BITMAP1);

	CRect rc;
	GetWindowRect(&rc);
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	if (image == NULL) {
		CBitmap* pOldBitmap = MemDC.SelectObject(&BMP);
		BITMAP bm;
		BMP.GetBitmap(&bm);
		dc.SetStretchBltMode(COLORONCOLOR);
		dc.StretchBlt(5, 5, rc.right - rc.left - 10, rc.bottom - rc.top, &MemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		MemDC.SelectObject(pOldBitmap);
	}
	else {
		drawpic();
	}
	MemDC.DeleteDC();
	ReleaseDC(&MemDC);
	ReleaseDC(&dc);
}


// CImageHandleView 打印




void CImageHandleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageHandleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageHandleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageHandleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImageHandleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//绘画
void CImageHandleView::drawpic()
{
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap MemLoad;
	CRect size(0, 0, image->GetWidth(), image->GetHeight());
	setviewsize();
	MemLoad.CreateCompatibleBitmap(&dc, viewWid, viewHei);
	MemDC.SelectObject(&MemLoad);
	switch (show_mode) {
	case ORIGIN_SIZE: {
		if (rect.Width() >= image->GetWidth()) {
			x = rect.Width() / 2 - image->GetWidth() / 2;
			viewWid = image->GetWidth();
		}
		else {
			x = 0;
			viewWid = rect.Width();
		}
		if (rect.Height() >= image->GetHeight()) {
			y = rect.Height() / 2 - image->GetHeight() / 2;
			viewHei = image->GetHeight();
		}
		else {
			y = 0;
			viewHei = rect.Height();
		}
		image->Draw(MemDC, 0, 0, viewWid, viewHei, offsetx, offsety, viewWid, viewHei);
		dc.BitBlt(x, y, image->GetWidth(), image->GetHeight(), &MemDC, 0, 0, SRCCOPY);
	}break;
	case WIDTHFIT_SIZE: {
		MemDC.SetStretchBltMode(HALFTONE);
		image->Draw(MemDC, 0, 0, viewWid, viewHei+10, offsetx, offsety, image->GetWidth(), image->GetHeight());
		dc.BitBlt(x, y, viewWid, viewHei+10, &MemDC, 0, 0, SRCCOPY);
	}break;
	case HEIGHTFIT_SIZE: {
		MemDC.SetStretchBltMode(HALFTONE);
		image->Draw(MemDC, 0, 0, viewWid + 10, viewHei, offsetx, offsety, image->GetWidth(), image->GetHeight());
		dc.BitBlt(x, y, viewWid + 10, viewHei, &MemDC, 0, 0, SRCCOPY);
	}break;
	case FIT_SIZE: {
		MemDC.SetStretchBltMode(HALFTONE);
		image->Draw(MemDC, 0, 0, viewWid, viewHei, offsetx, offsety, image->GetWidth(), image->GetHeight());
		dc.BitBlt(x, y, viewWid, viewHei, &MemDC, 0, 0, SRCCOPY);
	}break;
	default: break;
	}
	MemLoad.DeleteObject();
	MemDC.DeleteDC();
	ReleaseDC(&MemDC);
	ReleaseDC(&dc);
}

//根据显示模式，设置显示图片大小
void CImageHandleView::setviewsize()
{
	GetClientRect(&rect);
	switch (show_mode) {
	case ORIGIN_SIZE: {
		viewWid = image->GetWidth();
		viewHei = image->GetHeight();
	}break;
	case WIDTHFIT_SIZE: {
		viewWid = (REAL)rect.Width();
		REAL c = 0.0f;
		c = (REAL)viewWid / image->GetWidth();
		viewHei = image->GetHeight() * c -10;
	}break;
	case HEIGHTFIT_SIZE: {
		viewHei = (REAL)rect.Height();
		REAL c = 0.0f;
		c = (REAL)viewHei / image->GetHeight();
		viewWid = image->GetWidth() * c - 10;
	}break;
	case FIT_SIZE: {
		viewWid = (REAL)rect.Width()-8;
		REAL c = 0.0f;
		c = (REAL)viewWid / image->GetWidth();
		if (c * image->GetHeight() < rect.Height()) { 
			viewHei = image->GetHeight() * c; 
			mul = c;
		}
		else {
			viewHei = (REAL)rect.Height()-8;
			c = (REAL)viewHei / image->GetHeight();
			viewWid = image->GetWidth() * c - 10;
			mul = c;
		}
	}break;
	}
}

//根据图片设置滚动条
void CImageHandleView::setscroll()
{
	if (image == NULL)return;
	SCROLLINFO si;
	setviewsize();
	x = rect.Width() > viewWid ?
		rect.Width() / 2 - viewWid / 2 : 0;
	y = rect.Height() > viewHei ?
		rect.Height() / 2 - viewHei / 2 : 0;
	this->GetScrollInfo(SB_HORZ, &si);
	if (x == 0&& rect.Width()!=viewWid) {
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		si.nMin = 0;
		si.nMax = viewWid - rect.Width();
		si.nPage = 0;
		si.nPos = 0;
	}
	else {
		si.nMax = -1;
	}
	this->SetScrollInfo(SB_HORZ, &si);

	this->GetScrollInfo(SB_VERT, &si);
	if (y == 0&& rect.Height() != viewHei) {
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		si.nMin = 0;
		si.nMax = viewHei - rect.Height();
		si.nPage = 0;
		si.nPos = 0;
	}
	else si.nMax = -1;
	this->SetScrollInfo(SB_VERT, &si);
}

//清除背景
void CImageHandleView::clearbak()
{
	CClientDC dc(this);
	CDC MemDC;
	CBitmap MemBitmap;

	//清除上一图片内存，填充白色
	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(0);
	MemBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	MemDC.SelectObject(MemBitmap);
	MemDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
	BitBlt(dc, 0, 0, rect.Width(), rect.Height(), MemDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	ReleaseDC(&MemDC);
	ReleaseDC(&dc);
}

void CImageHandleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
#endif
}


// CImageHandleView 诊断

#ifdef _DEBUG
void CImageHandleView::AssertValid() const
{
	CView::AssertValid();
}

void CImageHandleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageHandleDoc* CImageHandleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageHandleDoc)));
	return (CImageHandleDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageHandleView 消息处理程序


//水平滚动条
void CImageHandleView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nCurpos, nMin, nMax, nThumbWidth;
	SCROLLINFO siInfo;                                      //定义滚动条信息
	CClientDC dc(this);
	GetScrollInfo(SB_HORZ, &siInfo);                        //获取滚动条信息
	nCurpos = siInfo.nPos;                                  //获取当前位置
	nMin = siInfo.nMin;                                     //获取最小值
	nMax = siInfo.nMax;                                     //获取最大滚动位置
	nThumbWidth = siInfo.nPage;                             //获取滚动快大小
	switch (nSBCode)
	{
		break;
	case SB_THUMBTRACK:										//拖动滚动块
		offsetx += (nPos - nCurpos);
		SetScrollPos(SB_HORZ, nPos);                        //设置水平滚动条的滚动位置
		OnDraw(&dc);
		break;
	case SB_LINELEFT:										//单击左箭头
		SetScrollPos(SB_HORZ, nCurpos - 1);                 //设置水平滚动条的滚动位置
		if (nCurpos != 0)
			offsetx -= 1;                                   //向左滚动一个位置
		OnDraw(&dc);
		break;
	case SB_LINERIGHT:										//单击右箭头
		SetScrollPos(SB_HORZ, nCurpos + 1);					//设置水平滚动条的滚动位置
		if(nCurpos + nThumbWidth < nMax)
			offsetx += 1;
		OnDraw(&dc);										//向右滚动一个位置
		break;
	case SB_PAGELEFT:										//在滚动块的左方空白滚动区域单击,增量为6
		SetScrollPos(SB_HORZ, nCurpos - 6);					//向左滚动6个单位
		offsetx -= nCurpos + nThumbWidth > 6 ? 6 : nCurpos + nThumbWidth;
		OnDraw(&dc);
		break;
	case SB_PAGERIGHT:										//在滚动块的右方空白滚动区域单击,增量为6
		SetScrollPos(SB_HORZ, nCurpos + 6);                 //设置水平滚动条的滚动位置	
		offsetx += nCurpos + nThumbWidth + 6 < nMax ?		//向右滚动6个单位
			6 : nMax - nCurpos - nThumbWidth;
		OnDraw(&dc);
		break;
	case SB_LEFT:                                           //滚动到最左边
		SetScrollPos(SB_HORZ, 0);                           //设置滚动位置为0
		offsetx = 0;										//设置窗口滚动位置
		OnDraw(&dc);
		break;
	}
	ReleaseDC(&dc);
	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

//垂直滚动条
void CImageHandleView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nCurpos, nMin, nMax, nThumbWidth;
	CClientDC dc(this);
	SCROLLINFO siInfo;
	GetScrollInfo(SB_VERT, &siInfo);
	nCurpos = siInfo.nPos;
	nMin = siInfo.nMin;
	nMax = siInfo.nMax;
	nThumbWidth = siInfo.nPage;
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		nCurpos = GetScrollPos(SB_VERT);
		offsety += (nPos - nCurpos);
		SetScrollPos(SB_VERT, nPos);						//设置垂直滚动条的滚动位置
		OnDraw(&dc);
		break;
	case SB_LINELEFT:
		nCurpos = GetScrollPos(SB_VERT);
		SetScrollPos(SB_VERT, nCurpos - 1);					//设置垂直滚动条的滚动位置
		if (nCurpos != 0)
			offsety -= 1;                                   //向上滚动一个位置
		OnDraw(&dc);
		break;
	case SB_LINERIGHT:
		nCurpos = GetScrollPos(SB_VERT);
		SetScrollPos(SB_VERT, nCurpos + 1);					//设置垂直滚动条的滚动位置
		if (nCurpos + nThumbWidth < nMax)
			offsety += 1;
		OnDraw(&dc);										//向下滚动一个位置
		break;
	case SB_PAGELEFT:										//在滚动块的上方空白滚动区域单击,增量为6
		SetScrollPos(SB_VERT, nCurpos - 6);					//向上滚动6个单位
		offsety -= nCurpos + nThumbWidth > 6 ? 
			6 : nCurpos + nThumbWidth;
		OnDraw(&dc);
		break;
	case SB_PAGERIGHT:										//在滚动块的下方空白滚动区域单击,增量为6
		SetScrollPos(SB_VERT, nCurpos + 6);                 //设置垂直滚动条的滚动位置	
		offsety += nCurpos + nThumbWidth + 6 < nMax ?		//向下滚动6个单位
			6 : nMax - nCurpos - nThumbWidth;
		OnDraw(&dc);
		break;
	case SB_LEFT:
		SetScrollPos(SB_VERT, 0);							//设置滚动位置为0
		offsety = 0;										//设置窗口滚动位置
		OnDraw(&dc);
		break;
	}
	ReleaseDC(&dc);
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

//窗口大小事件
void CImageHandleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	GetClientRect(&rect);
	if (image != NULL) {
		clearbak();
		setscroll();
		offsetx = 0;
		offsety = 0;
	}
}

//打开图片的按钮事件
void CImageHandleView::OnButtonOpenfile()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fDlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"图片文件|*.bmp;*.jpg;*.jpeg;*.png;*.jftf;*.gif|所有文件(*.*)|*.*||");
	if (fDlg.DoModal() == IDOK) {
		CClientDC dc(this);
		clearbak();
		mirror_flag = false;
		m_FileName = fDlg.GetPathName();
		if (image != NULL) {
			SAFE_DELETE(image);
		}
		image = new CImage();
		image->Load(m_FileName);
		if (CImageHandleApp::GetFileExtendedName(m_FileName) == L"png") {
			int nPitch = image->GetPitch(), nBPP = image->GetBPP();
			LPBYTE lpBits = reinterpret_cast<LPBYTE>(image->GetBits());
			for (int yPos = 0; yPos < image->GetHeight(); yPos++)
			{
				LPBYTE lpBytes = lpBits + (yPos * nPitch);
				PDWORD lpLines = reinterpret_cast<PDWORD>(lpBytes);
				for (int xPos = 0; xPos < image->GetWidth(); xPos++)
				{
					if (nBPP == 32 && lpLines[xPos] >> 24 != 0x000000FF)
					{
						lpLines[xPos] |= 0xFFFFFFFF;
					}
				}
			}
		}
		setscroll();
		OnDraw(&dc);
		ReleaseDC(&dc);
	}
}

//菜单栏打开按钮
void CImageHandleView::OnMenuOpenfile()
{
	// TODO: 在此添加命令处理程序代码
	OnButtonOpenfile();
}


//菜单栏另存为按钮
//bmp
void CImageHandleView::OnBtnSaveBmp()
{
	// TODO: 在此添加命令处理程序代码
	if (image!=NULL) {
		CFileDialog fDlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			L"图片文件|*.bmp|所有文件(*.*)|*.*||");
		if (fDlg.DoModal() == IDOK) {
			saveFileName = fDlg.GetPathName();
			if (CImageHandleApp::GetFileExtendedName(saveFileName) != L"bmp")
				saveFileName += L".bmp";
			image->Save(saveFileName,ImageFormatBMP);
			MessageBox(_T("保存成功"));
		}
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//jpeg
void CImageHandleView::OnBtnSavejpeg()
{
	// TODO: 在此添加命令处理程序代码
	if (image != NULL) {
		CFileDialog fDlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			L"图片文件|*.jpg|所有文件(*.*)|*.*||");
		if (fDlg.DoModal() == IDOK) {
			saveFileName = fDlg.GetPathName();
			if (CImageHandleApp::GetFileExtendedName(saveFileName) != L"jpg")
				saveFileName += L".jpg";
			image->Save(saveFileName, ImageFormatJPEG);
			MessageBox(_T("保存成功"));
		}
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//png
void CImageHandleView::OnBtnSavepng()
{
	// TODO: 在此添加命令处理程序代码
	if (image != NULL) {
		CFileDialog fDlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			L"图片文件|*.jpg|所有文件(*.*)|*.*||");
		if (fDlg.DoModal() == IDOK) {
			saveFileName = fDlg.GetPathName();
			if (CImageHandleApp::GetFileExtendedName(saveFileName) != L"png")
				saveFileName += L".png";
			image->Save(saveFileName, ImageFormatPNG);
			MessageBox(_T("保存成功"));
		}
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//tiff
void CImageHandleView::OnBtnSavetiff()
{
	// TODO: 在此添加命令处理程序代码
	if (image != NULL) {
		CFileDialog fDlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			L"图片文件|*.tiff|所有文件(*.*)|*.*||");
		if (fDlg.DoModal() == IDOK) {
			saveFileName = fDlg.GetPathName();
			if (CImageHandleApp::GetFileExtendedName(saveFileName) != L"tiff")
				saveFileName += L".tiff";
			image->Save(saveFileName, ImageFormatTIFF);
			MessageBox(_T("保存成功"));
		}
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//gif
void CImageHandleView::OnBtnSavegif()
{
	// TODO: 在此添加命令处理程序代码
	if (image != NULL) {
		CFileDialog fDlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			L"图片文件|*.gif|所有文件(*.*)|*.*||");
		if (fDlg.DoModal() == IDOK) {
			saveFileName = fDlg.GetPathName();
			if (CImageHandleApp::GetFileExtendedName(saveFileName) != L"gif")
				saveFileName += L".gif";
			image->Save(saveFileName, ImageFormatGIF);
			MessageBox(_T("保存成功"));
		}
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//icon
void CImageHandleView::OnBtnSaveicon()
{
	// TODO: 在此添加命令处理程序代码
	if (image != NULL) {
		CFileDialog fDlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			L"图片文件|*.ico|所有文件(*.*)|*.*||");
		if (fDlg.DoModal() == IDOK) {
			saveFileName = fDlg.GetPathName();
			if (CImageHandleApp::GetFileExtendedName(saveFileName) != L"ico")
				saveFileName += L".ico";
			image->Save(saveFileName, ImageFormatIcon);
			MessageBox(_T("保存成功"));
		}
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//底部显示模式
//原始大小
void CImageHandleView::OnButtonOrsize()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	show_mode = ORIGIN_SIZE;
	offsetx = offsety = 0;
	clearbak();
	setscroll();
	OnDraw(&dc);
	ReleaseDC(&dc);
}

//适应高度
void CImageHandleView::OnButtonHesize()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	show_mode = HEIGHTFIT_SIZE;
	offsetx = offsety = 0;
	clearbak();
	setscroll();
	OnDraw(&dc);
	ReleaseDC(&dc);
}

//适应大小
void CImageHandleView::OnButtonFisize()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	show_mode = FIT_SIZE;
	offsetx = offsety = 0;
	clearbak();
	setscroll();
	OnDraw(&dc);
	ReleaseDC(&dc);
}

//适应宽度
void CImageHandleView::OnButtonWisize()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	show_mode = WIDTHFIT_SIZE;
	offsetx = offsety = 0;
	clearbak();
	setscroll();
	OnDraw(&dc);
	ReleaseDC(&dc);
}

//显示模式，状态高亮显示，//原始大小
void CImageHandleView::OnUpdateButtonOrsize(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(show_mode == ORIGIN_SIZE);
}

//适应高度高亮
void CImageHandleView::OnUpdateButtonHesize(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(show_mode == HEIGHTFIT_SIZE);
}

//适应大小高亮
void CImageHandleView::OnUpdateButtonFisize(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(show_mode == FIT_SIZE);
}

//适应宽度高亮
void CImageHandleView::OnUpdateButtonWisize(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(show_mode == WIDTHFIT_SIZE);
}

//顺时针90度旋转图片按钮
void CImageHandleView::OnButtonRotate()
{
	// TODO: 在此添加命令处理程序代码
	if (image) {
		CImage* srcImg = image;
		CClientDC dc(this);
		BYTE* srcPtr = (BYTE*)srcImg->GetBits();
		int srcBitsCount = srcImg->GetBPP();
		int srcWidth = srcImg->GetWidth();
		int srcHeight = srcImg->GetHeight();
		int srcPitch = srcImg->GetPitch();

		//创建新图像  

		CImage* dstImg = new CImage();
		dstImg->Create(srcHeight, srcWidth, srcBitsCount, 0);

		//加载调色板
		if (srcBitsCount <= 8 && srcImg->IsIndexed())//需要调色板  
		{
			RGBQUAD pal[256];
			int nColors = srcImg->GetMaxColorTableEntries();
			if (nColors > 0)
			{
				srcImg->GetColorTable(0, nColors, pal);
				dstImg->SetColorTable(0, nColors, pal);//复制调色板程序  
			}
		}
		//目标图像参数  
		BYTE* destPtr = (BYTE*)dstImg->GetBits();
		int destPitch = dstImg->GetPitch();
		int width = dstImg->GetWidth();
		int height = dstImg->GetHeight();
		int k, m;
		//复制图像数据  
		for (int i = 0; i < srcHeight; i++) {
			for (int j = 0; j < srcWidth; j++) {
				int times = srcBitsCount / 8;
				k = srcHeight - i - 1;
				m = srcWidth - j - 1;
				for (int l = 0; l < times; ++l) {
					*(destPtr + (srcWidth - 1 - j) * destPitch + times * i+l) = 
						*(srcPtr + k * srcPitch + times * m+l);
				}
			}
		}

		//保存新图像
		//dstImg->Save(m_FileName);
		image->Destroy();
		image = dstImg;
		delete srcImg;
		srcImg = NULL;
		//delete dstImg;
		clearbak();
		setscroll();
		OnDraw(&dc);
		ReleaseDC(&dc);
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}


//裁剪按钮
void CImageHandleView::OnButtonCut()
{
	// TODO: 在此添加命令处理程序代码
	if (image) {
		OnButtonFisize();
		m_cut = TRUE;
		CClientDC dc(this);
		CRect cr;
		GetWindowRect(&cr);
		RECT rect_cur;
		rect_cur.left = x + cr.left;
		rect_cur.right = viewWid + x + cr.left;
		rect_cur.top = y + cr.top;
		rect_cur.bottom = viewHei + y + cr.top;
		ClipCursor(&rect_cur);
		ReleaseDC(&dc);
	}
	else {
		MessageBox(_T("未打开图片"));
	}
}

//裁剪状态
void CImageHandleView::OnUpdateButtonCut(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_cut);
}

//画矩形
void CImageHandleView::drawrangle()
{
	CClientDC dc(this);
	OnDraw(&dc);
	CRect rect(m_StartPoint, m_EndPoint);
	rect.NormalizeRect();//规范化矩形   
	CBrush bruPen(RGB(0, 0, 0));//矩形边框颜色   
	dc.FrameRect(&rect, &bruPen);
	ReleaseDC(&dc);
}

//裁剪
void CImageHandleView::roicut()
{
	CImage* dst = new CImage();
	byte* pImg = (byte*)image->GetBits();
	int step = image->GetPitch();
	m_StartPoint.x = (REAL)(m_StartPoint.x - x) / mul;
	m_StartPoint.y = (REAL)(m_StartPoint.y - y) / mul;
	m_EndPoint.x = (REAL)(m_EndPoint.x - x) / mul;
	m_EndPoint.y = (REAL)(m_EndPoint.y - y) / mul;
	if (m_StartPoint.x > m_EndPoint.x) {
		int temp = m_StartPoint.x;
		m_StartPoint.x = m_EndPoint.x;
		m_EndPoint.x = temp;
	}
	if (m_StartPoint.y > m_EndPoint.y) {
		int temp = m_StartPoint.y;
		m_StartPoint.y = m_EndPoint.y;
		m_EndPoint.y = temp;
	}
	int width = m_EndPoint.x - m_StartPoint.x;
	int height = m_EndPoint.y - m_StartPoint.y;
	if (width == 0 || height == 0) {
		MessageBox(_T("所裁剪区域无像素")); return;
	}
	int srcBitsCount = image->GetBPP();
	dst->Create(width, height, srcBitsCount, 0);
	byte* pRoi = (byte*)dst->GetBits();
	int destPitch = dst->GetPitch();
	int index = 0;
	for (int i = m_StartPoint.y; i < m_EndPoint.y; ++i) {
		for (int j = m_StartPoint.x; j < m_EndPoint.x; ++j) {
			int times = srcBitsCount / 8;
			for (int l = 0; l < times; ++l) {
				*(pRoi + (i - m_StartPoint.y) * destPitch + times * (j - m_StartPoint.x) + l) 
					=*(pImg + i * step + times * j + l);
			}
		}
	}
	CImage* old = image;
	image->Destroy();
	image = dst;
	delete old;
	old = NULL;
}

//图片镜面对称
void CImageHandleView::OnButtonMirror()
{
	// TODO: 在此添加命令处理程序代码
	if (image&&mirror_flag==false) {
		OnButtonFisize();
		mirror_flag = true;
		CImage* srcImg = image;
		CClientDC dc(this);
		BYTE* srcPtr = (BYTE*)srcImg->GetBits();
		int srcBitsCount = srcImg->GetBPP();
		int srcWidth = srcImg->GetWidth();
		int srcHeight = srcImg->GetHeight();
		int srcPitch = srcImg->GetPitch();

		//创建新图像  

		CImage* dstImg = new CImage();
		dstImg->Create(srcWidth*2, srcHeight, srcBitsCount, 0);

		//加载调色板
		if (srcBitsCount <= 8 && srcImg->IsIndexed())//需要调色板  
		{
			RGBQUAD pal[256];
			int nColors = srcImg->GetMaxColorTableEntries();
			if (nColors > 0)
			{
				srcImg->GetColorTable(0, nColors, pal);
				dstImg->SetColorTable(0, nColors, pal);//复制调色板程序  
			}
		}
		//目标图像参数  
		BYTE* destPtr = (BYTE*)dstImg->GetBits();
		int destPitch = dstImg->GetPitch();
		int width = dstImg->GetWidth();
		int height = dstImg->GetHeight();
		//复制图像数据  
		for (int i = 0; i < height; i++) {
			memcpy(destPtr + i * destPitch, srcPtr + i * srcPitch, abs(srcPitch));
		}
		for (int i = 0; i < height; i++){
			for (int j = 0; j < srcWidth; j++){
				int times = srcBitsCount / 8;
				for (int l = 0; l < times; ++l) {
					*(destPtr + i * destPitch + times * (width -1 - j) + l) 
						= *(srcPtr + i * srcPitch + times * j + l);
				}
			}
		}
		image = dstImg;
		clearbak();
		setscroll();
		OnDraw(&dc);
		delete srcImg;
		srcImg = NULL;
		ReleaseDC(&dc);
	}
	else if(!image) {
		MessageBox(_T("未打开图片"));
	}
}

//添加文字
void CImageHandleView::OnButtonSetfont()
{
	// TODO: 在此添加命令处理程序代码
	if (image) {
		DLG_FONT dlg;
		if (dlg.DoModal() == IDOK) {
			CClientDC dc(this);
			HDC hdcim = image->GetDC();
			CDC* imagedc = CDC::FromHandle(hdcim);
			CString text = dlg.m_text;
			COLORREF col = dlg.m_col;
			CString fonttype = dlg.m_fonttype;
			float ofx = (float)dlg.m_x / 100.0;
			float ofy = (float)dlg.m_y / 100.0;
			int fontsize = dlg.m_size;
			CFont font;
			VERIFY(font.CreatePointFont(fontsize, fonttype, imagedc));
			CFont* def_font = imagedc->SelectObject(&font);
			imagedc->SetTextColor(col);
			RECT rc;
			rc.left = ofx * image->GetWidth();
			rc.right = ofx * image->GetWidth() + 1 + fontsize / 10 * text.GetLength() * 2;
			rc.top = ofy * image->GetHeight();
			rc.bottom = ofy * image->GetHeight() + 1 + fontsize / 5;
			imagedc->SetBkMode(TRANSPARENT);//设置字体背景为透明
			DrawText(hdcim, text, text.GetLength(), &rc, DT_LEFT | DT_SINGLELINE | DT_TOP);
			CRect rcs(rc);
			font.DeleteObject();//释放font对象

			imagedc->SelectObject(def_font);//恢复PDC的缺省字体
			DWORD h = GetLastError();
			OnDraw(&dc);
			ReleaseDC(&dc);
			image->ReleaseDC();
			ReleaseDC(imagedc);

		}
	}
	else {
		MessageBox(_T("图片未打开"));
	}
}


//灰度化
void CImageHandleView::OnMenugrayhandle()
{
	// TODO: 在此添加命令处理程序代码
	if (image && image->GetBPP() != 8) {
		CClientDC dc(this);
		CImage* imgSrc = image;
		int maxY = imgSrc->GetHeight();
		int maxX = imgSrc->GetWidth();

		CImage* imgDst = new CImage();
		imgDst->Create(maxX, maxY, 8, 0);//图像大小与imgSrc相同，每个像素占1字节

		//为imgDst构造256阶灰度调色表
		RGBQUAD ColorTab[256];
		for (int i = 0; i < 256; i++)
		{
			ColorTab[i].rgbBlue = ColorTab[i].rgbGreen = ColorTab[i].rgbRed = i;
		}
		imgDst->SetColorTable(0, 256, ColorTab);

		byte* pDataSrc = (byte*)imgSrc->GetBits(); //获取指向图像数据的指针
		byte* pDataDst = (byte*)imgDst->GetBits();
		int pitchSrc = imgSrc->GetPitch(); //获取每行图像占用的字节数 +：top-down；-：bottom-up DIB
		int pitchDst = imgDst->GetPitch();
		int bitCountSrc = imgSrc->GetBPP() / 8;  // 获取每个像素占用的字节数
		int bitCountDst = imgDst->GetBPP() / 8;
		int tmpR, tmpG, tmpB, avg;
		float a;
		for (int i = 0; i < maxX; i++)
		{
			for (int j = 0; j < maxY; j++)
			{
				tmpR = *(pDataSrc + pitchSrc * j + i * bitCountSrc);
				tmpG = *(pDataSrc + pitchSrc * j + i * bitCountSrc + 1);
				tmpB = *(pDataSrc + pitchSrc * j + i * bitCountSrc + 2);
				avg = (int)(tmpR + tmpG + tmpB) / 3;
				*(pDataDst + pitchDst * j + i * bitCountDst) = avg;
			}
		}
		image = imgDst;
		clearbak();
		setscroll();
		OnDraw(&dc);
		delete imgSrc;
		imgSrc = NULL;
		ReleaseDC(&dc);
	}
	else if (!image) {
		MessageBox(_T("图片未打开"));
	}
}

//缩放伸缩
void CImageHandleView::OnButtonScale()
{
	// TODO: 在此添加命令处理程序代码
	if (image) {
		DLG_SIZE dlg;
		int wid = image->GetWidth();
		int hig = image->GetHeight();
		float c = (float)wid / (float)hig;
		dlg.m_wid = wid;
		dlg.m_hig = hig;
		dlg.m_c = c;
		if (dlg.DoModal() == IDOK) {
			CClientDC dc(this);
			wid = dlg.m_wid;
			hig = dlg.m_hig;
			CImage* dst = new CImage();
			CImage* old = image;
			dst->Create(wid, hig, image->GetBPP());
			HDC hdcim = dst->GetDC();
			CDC* imagedc = CDC::FromHandle(hdcim);
			imagedc->SetStretchBltMode(HALFTONE);
			image->Draw(hdcim, 0, 0, wid, hig);
			ReleaseDC(imagedc);
			dst->ReleaseDC();
			image = dst;
			SAFE_DELETE(old);
			clearbak();
			setscroll();
			OnDraw(&dc);
			ReleaseDC(&dc);
		}
	}
	else {
		MessageBox(_T("图片未打开"));
	}
}



///---------------------///
///------鼠标事件-------///
//左键按下
void CImageHandleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_cut) {
		m_StartPoint = point;
		m_EndPoint = point;
		m_clik = TRUE;
		SetCapture();
	}

	CView::OnLButtonDown(nFlags, point);
}

//左键弹起
void CImageHandleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_cut) {
		if (this == GetCapture())
		{
			ReleaseCapture();
		}
		CClientDC dc(this);
		m_clik = FALSE;
		m_EndPoint = point;
		roicut();
		clearbak();
		setscroll();
		OnDraw(&dc);
		ClipCursor(NULL);
		m_cut = FALSE;
		ReleaseDC(&dc);
	}
	CView::OnLButtonUp(nFlags, point);
}

//鼠标移动
void CImageHandleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_cut) { 
		SetCursor(LoadCursor(NULL, IDC_CROSS)); 
		SetClassLong(this->GetSafeHwnd(),
			GCL_HCURSOR,
			(LONG)LoadCursor(NULL, IDC_CROSS));//使光标在该区域不再闪烁
	}
	else {
		SetClassLong(this->GetSafeHwnd(),
			GCL_HCURSOR,
			(LONG)LoadCursor(NULL, IDC_ARROW));
	}
	if (m_clik) {
		CClientDC dc(this);
		m_EndPoint = point;
		drawrangle();
		ReleaseDC(&dc);
	}
	CView::OnMouseMove(nFlags, point);
}

//鼠标右键
void CImageHandleView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_cut) {
		ClipCursor(NULL);
		m_cut = FALSE;
	}
	CView::OnRButtonDown(nFlags, point);
}

//图像模版
void CImageHandleView::impore(int* opTemp, float aver)
{
	CClientDC dc(this);

	CImage* dst = new CImage();
	CImage* old = image;
	BYTE* lpBits = reinterpret_cast<BYTE*>(image->GetBits());
	int nPitch = image->GetPitch();
	int srcBitsCount = image->GetBPP();
	int nbitC = srcBitsCount / 8;
	int nWidth = image->GetWidth();
	int nHeight = image->GetHeight();

	dst->Create(nWidth, nHeight, srcBitsCount);
	BYTE* lpBits2 = reinterpret_cast<BYTE*>(dst->GetBits());
	int nPitch2 = dst->GetPitch();

	int i, j;

	if (srcBitsCount <= 8 && image->IsIndexed())//需要调色板  
	{
		RGBQUAD pal[256];
		int nColors = image->GetMaxColorTableEntries();
		if (nColors > 0)
		{
			image->GetColorTable(0, nColors, pal);
			dst->GetColorTable(0, nColors, pal);
		}
	}
	for (i = 0; i < nWidth ; i++) {
		for (j = 0; j < nHeight ; j++) {

			int rr = 0, gg = 0, bb = 0;
			int index = 0;
			for (int col = -1; col <= 1; col++) {
				if (j + col >= nHeight || j + col <= 0)continue;
				for (int row = -1; row <= 1; row++) {
					if (i + row >= nWidth || i + row <= 0)continue;
					rr += (*(lpBits + nPitch * (j + col) + (i + row) * nbitC + 2)) * opTemp[index];
					gg += (*(lpBits + nPitch * (j + col) + (i + row) * nbitC + 1)) * opTemp[index];
					bb += (*(lpBits + nPitch * (j + col) + (i + row) * nbitC)) * opTemp[index];
					index++;
				}
			}
			rr = (int)(rr * aver);
			gg = (int)(gg * aver);
			bb = (int)(bb * aver);
			// 处理溢出点
			if (rr > 255) rr = 255;
			else if (rr < 0) rr = -rr;
			if (gg > 255) gg = 255;
			else if (gg < 0) gg = -gg;
			if (bb > 255) bb = 255;
			else if (bb < 0) bb = -bb;

			(*(lpBits2 + nPitch2 * j  + i  * nbitC + 2)) = rr;
			(*(lpBits2 + nPitch2 * j  + i * nbitC + 1)) = gg;
			(*(lpBits2 + nPitch2 * j  + i * nbitC)) = bb;
		}
	}
	image = dst;
	old->Destroy();
	SAFE_DELETE(old);
	clearbak();
	setscroll();
	OnDraw(&dc);
	ReleaseDC(&dc);
}

//锐化
void CImageHandleView::OnMenubmpsharp()
{
	if (image) {
		int sharpLaplacian[9] = { -1,-1,-1,-1,9,-1,-1,-1,-1 }; // 拉普拉斯模板
		float aver = 1;
		impore(sharpLaplacian, aver);
	}
	else
		MessageBox(_T("图片未打开"));
}


//高斯平滑
void CImageHandleView::OnSmooth()
{
	// TODO: 在此添加命令处理程序代码
	if (image) {
		int smoothGauss[9] = { 1,2,1,2,4,2,1,2,1 }; // 高斯模板
		float aver = (float)(1.0 / 16.0);
		impore(smoothGauss, aver);
	}
	else
		MessageBox(_T("图片未打开"));
}

//反色
void CImageHandleView::OnMenureversecolor()
{
	// TODO: 在此添加命令处理程序代码
	if (image) {
		CImage* m_Image = image;
		CClientDC dc(this);
		CImage* m_Image1 = new CImage();
		m_Image1->Create(m_Image->GetWidth(), m_Image->GetHeight(), m_Image->GetBPP(), 0);
		int r = 0, g = 0, b = 0;
		int width = m_Image->GetWidth();
		int height = m_Image->GetHeight();
		byte* pDataSrc = (byte*)m_Image->GetBits(); //获取指向图像数据的指针
		byte* pDataDst = (byte*)m_Image1->GetBits();
		int pitchSrc = m_Image->GetPitch(); //获取每行图像占用的字节数 +：top-down；-：bottom-up DIB
		int pitchDst = m_Image1->GetPitch();
		int bitCountSrc = m_Image->GetBPP() / 8;  // 获取每个像素占用的字节数
		int bitCountDst = m_Image1->GetBPP() / 8;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				r = *(pDataSrc + pitchSrc * y + x * bitCountSrc);
				g = *(pDataSrc + pitchSrc * y + x * bitCountSrc + 1);
				b = *(pDataSrc + pitchSrc * y + x * bitCountSrc + 2);
				*(pDataDst + pitchDst * y + x * bitCountDst) = 255 - r;
				*(pDataDst + pitchDst * y + x * bitCountDst + 1) = 255 - g;
				*(pDataDst + pitchDst * y + x * bitCountDst + 2) = 255 - b;
			}
		}
		image = m_Image1;
		clearbak();
		setscroll();
		OnDraw(&dc);
		delete m_Image;
		m_Image = NULL;
		ReleaseDC(&dc);
	}
	else {
		MessageBox(_T("图片未打开"));
	}
}
