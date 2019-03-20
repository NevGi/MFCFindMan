
// MFCFindMan2Dlg.h: 头文件
//

#pragma once


#include<vector>
#include "PerSon.h"

// CMFCFindMan2Dlg 对话框
class CMFCFindMan2Dlg : public CDialogEx
{
// 构造
public:
	CMFCFindMan2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCFINDMAN2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	std::vector<CString> paths;
	std::vector<CString> groups;
	std::vector<CString> users;
	int start;
	int end;
	char** p;
	PerSon* person;
	CMenu m_Menu;

//	CEdit m_NewG;
	CComboBox m_OutGroup;
	afx_msg void OnCbnSelchangeCombo2();
	CListBox m_UInfoList;
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton3();
	CString m_OutName;
	afx_msg void OnStnClickedText();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton4();
	int m_outage;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	CString m_outpath;
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32774();
	afx_msg void On32773();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
