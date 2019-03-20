#pragma once
#include "PerSon.h"
#include <vector>
// LMatchPerson 对话框

class LMatchPerson : public CDialogEx
{
	DECLARE_DYNAMIC(LMatchPerson)

public:
	LMatchPerson(CWnd* pParent = nullptr);   // 标准构造函数
	LMatchPerson(CWnd* pParent = nullptr , std::vector<CString>* groups = nullptr); // 重载构造函数
	virtual ~LMatchPerson();
	std::vector<CString>* groups;
	std::vector<CString> paths;
	std::vector<PerSon> persons;
	int pos;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_srcpath;
	afx_msg void OnLbnSelchangeList2();
	CListBox m_desuser;
	afx_msg void OnLbnSelchangeList3();
	CString m_mtname;
	CString m_mtage;
	CString m_mtgroup;
	CListCtrl m_listctr;
	ULONG_PTR m_gdiplusToken;
	CImageList m_imageList;
	virtual BOOL OnInitDialog();
//	afx_msg void OnHdnItemchangingList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnNMSetfocusList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_score;
};
