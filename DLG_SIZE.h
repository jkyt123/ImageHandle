#pragma once


// DLG_SIZE 对话框
class DLG_SIZE : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_SIZE)

public:
	DLG_SIZE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DLG_SIZE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_wid;
	int m_hig;
	float m_c;
	afx_msg void OnBnClickedLink();
	CButton m_btn_link;
	BOOL m_link;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnUpdateWidth();
	afx_msg void OnEnUpdateHeight();
};
