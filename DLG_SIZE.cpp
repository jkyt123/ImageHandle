// DLG_SIZE.cpp: 实现文件
//

#include "pch.h"
#include "ImageHandle.h"
#include "DLG_SIZE.h"
#include "afxdialogex.h"


// DLG_SIZE 对话框

IMPLEMENT_DYNAMIC(DLG_SIZE, CDialogEx)

DLG_SIZE::DLG_SIZE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIZE, pParent)
	, m_wid(0)
	, m_hig(0)
{

}

DLG_SIZE::~DLG_SIZE()
{
}

void DLG_SIZE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_wid);
	DDX_Text(pDX, IDC_HEIGHT, m_hig);
	DDX_Control(pDX, IDC_LINK, m_btn_link);
}


BEGIN_MESSAGE_MAP(DLG_SIZE, CDialogEx)
	ON_BN_CLICKED(IDC_LINK, &DLG_SIZE::OnBnClickedLink)
	ON_EN_UPDATE(IDC_WIDTH, &DLG_SIZE::OnEnUpdateWidth)
	ON_EN_UPDATE(IDC_HEIGHT, &DLG_SIZE::OnEnUpdateHeight)
END_MESSAGE_MAP()


// DLG_SIZE 消息处理程序


void DLG_SIZE::OnBnClickedLink()
{
	// TODO: 在此添加控件通知处理程序代码
	m_link = m_btn_link.GetCheck();
	if (m_link) {
		UpdateData(TRUE);
		m_hig = (float)m_wid / m_c;
		UpdateData(FALSE);
	}
}


BOOL DLG_SIZE::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_btn_link.SetIcon(AfxGetApp()->LoadIconW(IDI_LINK));
	m_link = TRUE;
	m_btn_link.SetCheck(m_link);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void DLG_SIZE::OnEnUpdateWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。
	if (m_link) {
		UpdateData(TRUE);
		m_hig = (float)m_wid / m_c;
		UpdateData(FALSE);
	}
	// TODO:  在此添加控件通知处理程序代码
}


void DLG_SIZE::OnEnUpdateHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。
	if (m_link) {
		UpdateData(TRUE);
		m_wid = (float)m_hig / m_c;
		UpdateData(FALSE);
	}
	// TODO:  在此添加控件通知处理程序代码
}
