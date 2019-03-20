#pragma once


// Test 对话框

class Test : public CDialogEx
{
	DECLARE_DYNAMIC(Test)

public:
	Test(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Test();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
