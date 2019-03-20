#pragma once


// AddGroup 对话框

class AddGroup : public CDialogEx
{
	DECLARE_DYNAMIC(AddGroup)

public:
	AddGroup(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddGroup();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_NewGroup;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
};
