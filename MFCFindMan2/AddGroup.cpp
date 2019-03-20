// AddGroup.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCFindMan2.h"
#include "AddGroup.h"
#include "afxdialogex.h"
#include "TestOp.h"


// AddGroup 对话框

IMPLEMENT_DYNAMIC(AddGroup, CDialogEx)

AddGroup::AddGroup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_NewGroup(_T(""))
{

}

AddGroup::~AddGroup()
{
}

void AddGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_NewGroup);
}


BEGIN_MESSAGE_MAP(AddGroup, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddGroup::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// AddGroup 消息处理程序


void AddGroup::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//创建新组
	UpdateData(TRUE);
	if (m_NewGroup.IsEmpty())
	{
		MessageBox(TEXT("请输入新组名"));
		return;
	}
	int ret = 0;
	char group[20];
	memset(group, 0, sizeof(group));
	WideCharToMultiByte(CP_ACP, 0, m_NewGroup, -1, group, sizeof(group), NULL, NULL);

	ret = CreateGroup(group);
	if (ret == 0)
	{
		MessageBox(TEXT("创建新用户组成功"));
	}


	SendMessage(WM_CLOSE);

}


void AddGroup::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}
