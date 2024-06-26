// DLG_FONT.cpp: 实现文件
//

#include "pch.h"
#include "ImageHandle.h"
#include "DLG_FONT.h"
#include "afxdialogex.h"


// DLG_FONT 对话框

IMPLEMENT_DYNAMIC(DLG_FONT, CDialogEx)

DLG_FONT::DLG_FONT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETFONT, pParent)
	, m_text(_T(""))
	, m_test(_T(""))
	, m_x(0)
	, m_y(0)
{

}

DLG_FONT::~DLG_FONT()
{
}

void DLG_FONT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_text);
	DDX_Control(pDX, IDC_FONTTYPE, m_cb);
	DDX_Control(pDX, IDC_FONTSIZE, m_sc);
	DDX_Text(pDX, IDC_TEST, m_test);
	DDX_Control(pDX, IDC_FONTCOLOR, m_col_btn);
	DDX_Control(pDX, IDC_SETX, m_sx);
	DDX_Control(pDX, IDC_SETY, m_sy);
	DDX_Slider(pDX, IDC_SETX, m_x);
	DDX_Slider(pDX, IDC_SETY, m_y);
}


BEGIN_MESSAGE_MAP(DLG_FONT, CDialogEx)
	ON_BN_CLICKED(ID_BTN_OK, &DLG_FONT::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FONTSIZE, &DLG_FONT::OnNMCustomdrawFontsize)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &DLG_FONT::OnEnChangeEditText)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()


ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_FONTSIZE, &DLG_FONT::OnTRBNThumbPosChangingFontsize)
ON_WM_CTLCOLOR()
ON_CBN_SELCHANGE(IDC_FONTTYPE, &DLG_FONT::OnCbnSelchangeFonttype)

ON_BN_CLICKED(IDC_FONTCOLOR, &DLG_FONT::OnBnClickedFontcolor)
END_MESSAGE_MAP()


// DLG_FONT 消息处理程序



void DLG_FONT::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);                       //这个函数的使用请参考数据交换UpdateData
	UpdateData(FALSE);

	CDialogEx::OnOK();
}


void DLG_FONT::OnNMCustomdrawFontsize(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL DLG_FONT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_sc.SetRange(60, 560);
	m_sx.SetRange(0, 100);
	m_sy.SetRange(0, 100);
	m_cb.SetCurSel(0);
	m_size= 60;
	int index = m_cb.GetCurSel();
	m_cb.GetLBText(index, m_fonttype);
	m_font.CreatePointFont(m_sc.GetPos(), m_fonttype);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DLG_FONT::OnEnChangeEditText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	m_test = m_text;
	UpdateData(FALSE);
	// TODO:  在此添加控件通知处理程序代码
}


void DLG_FONT::flash()
{
	CRect rect;
	GetDlgItem(IDC_TEST)->GetWindowRect(&rect); //获取控件区域  
	ScreenToClient(&rect); //屏幕区域对客户区域的转换    
	InvalidateRect(rect,FALSE);//刷新 
}
void DLG_FONT::OnTRBNThumbPosChangingFontsize(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_size = m_sc.GetPos();
	m_font.DeleteObject();
	m_font.CreatePointFont(m_size, m_fonttype);
	flash();
	*pResult = 0;
}


HBRUSH DLG_FONT::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_TEST) {
		pDC->SetTextColor(m_col);//用RGB宏改变颜色
		pDC->SelectObject(&m_font);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void DLG_FONT::OnCbnSelchangeFonttype()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_cb.GetCurSel();
	m_cb.GetLBText(index, m_fonttype);
	m_font.DeleteObject();
	m_font.CreatePointFont(m_sc.GetPos(), m_fonttype);
	flash();
}


void DLG_FONT::OnBnClickedFontcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_col = m_col_btn.GetColor();
	flash();
}
