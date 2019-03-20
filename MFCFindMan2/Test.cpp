// Test.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCFindMan2.h"
#include "Test.h"
#include "afxdialogex.h"


// Test 对话框

IMPLEMENT_DYNAMIC(Test, CDialogEx)

Test::Test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

Test::~Test()
{
}

void Test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Test, CDialogEx)
END_MESSAGE_MAP()


// Test 消息处理程序
