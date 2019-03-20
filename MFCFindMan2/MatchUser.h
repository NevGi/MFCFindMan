#pragma once
#include <vector>
#include "PerSon.h"

// MatchUser 对话框

class MatchUser : public CDialogEx
{
	DECLARE_DYNAMIC(MatchUser)

public:
	MatchUser(CWnd* pParent = nullptr);   // 标准构造函数
	MatchUser(CWnd* pParent = nullptr, std::vector<CString>* groups = nullptr); // 重载构造函数
	virtual ~MatchUser();
	std::vector<CString>* groups;
	std::vector<CString> paths;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	afx_msg void OnLbnSelchangeList2();
	CListBox m_userpaths;
	CListBox m_uinfo;
	std::vector<PerSon> persons;
};
