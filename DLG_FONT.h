#pragma once



// DLG_FONT 对话框

class DLG_FONT : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_FONT)

public:
	DLG_FONT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DLG_FONT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETFONT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_text;
	CString m_fonttype;
	int m_size;
	afx_msg void OnBnClickedOk();
	CMFCFontComboBox m_cb;
	CSliderCtrl m_sc;
	afx_msg void OnNMCustomdrawFontsize(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditText();
	CString m_test;
	CFont m_font;
	void flash();
	afx_msg void OnTRBNThumbPosChangingFontsize(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeFonttype();
	COLORREF m_col;
	CMFCColorButton m_col_btn;
	afx_msg void OnBnClickedFontcolor();
	CSliderCtrl m_sx;
	CSliderCtrl m_sy;
	int m_x;
	int m_y;
};
