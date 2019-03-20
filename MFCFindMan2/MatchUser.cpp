// MatchUser.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCFindMan2.h"
#include "MatchUser.h"
#include "afxdialogex.h"
#include "TestOp.h"

#define NAMELEN 20



// MatchUser 对话框

IMPLEMENT_DYNAMIC(MatchUser, CDialogEx)

MatchUser::MatchUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

MatchUser::MatchUser(CWnd * pParent, std::vector<CString>* groups)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	this->groups = groups;
}

MatchUser::~MatchUser()
{
}

void MatchUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_userpaths);
	DDX_Control(pDX, IDC_LIST1, m_uinfo);
}


BEGIN_MESSAGE_MAP(MatchUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MatchUser::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST2, &MatchUser::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// MatchUser 消息处理程序


void MatchUser::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开图片选择 并且导入图片
	std::vector<CString>().swap(paths);
	m_userpaths.ResetContent();
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("Image Files(*.jpg)|*.jpg|"), NULL);
	dlg.m_ofn.lpstrTitle = _T("选择图片");
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		while (fileNamesPosition != NULL)
		{
			filename = dlg.GetNextPathName(fileNamesPosition);
			paths.push_back(filename);
		}
	}
	for (CString&c : paths)
	{
		m_userpaths.AddString(c);
	}
	if (paths.size() == 0)
	{
		return;
	}
	m_uinfo.ResetContent();

	//构建好组名数组 作为传入查询参数
	char ** group = (char**)malloc(sizeof(char*)*((*groups).size()));
	std::string tgroup;
	for (int i = 0; i < (*groups).size(); i++)
	{
		group[i] = (char*)malloc(((*groups)[i].GetLength()) + 1);
		memset(group[i], 0, (*groups)[i].GetLength() + 1);
		WideCharToMultiByte(CP_ACP, 0, (*groups)[i], -1, group[i], (*groups)[i].GetLength() + 1, NULL, NULL);

		std::string tmp(group[i]);
		tgroup += tmp;
		tgroup += ",";
	}



	//CString ss(tgroup.c_str());
	//MessageBox(ss);
	
	int ret = 0;
	int sucess = 0;
	int fail = 0;


	for (CString& path : paths)
	{

		char pname[NAMELEN];
		memset(pname, 0, sizeof(pname));
		WideCharToMultiByte(CP_ACP, 0, path, -1, pname, sizeof(pname), NULL, NULL);
		//CString ss(pname);
		//MessageBox(ss);
		//
		PerSon person;
		memset(&person, 0, sizeof(PerSon));
		//ret = MatchUse(pname, tgroup, person);

		if (ret == 0)
		{
			sucess++;
			memcpy(person.path, pname, sizeof(person.path));
			this->persons.push_back(person);

		}
		else if (ret == -5)
		{
			fail++;
			
		}
		else if (ret == -4)
		{
			fail++;
			

		}
		else if (ret == -6)
		{
			fail++;
			
		}


	}
	if (sucess > 0)
	{
		CString ss;
		ss.Format(TEXT("%d"), sucess);
		CString s1("比对成功");
		s1 += ss;

		MessageBox(s1);
	}
	else
	{
		MessageBox(TEXT("信息库没有和图片比对匹配人员"));
		return;
	}

	for (PerSon & person : persons)
	{

		CString path(person.path);
		CString group(person.group);
		CString name(person.name);
		CString age;
		age.Format(TEXT("%d"), person.age);
		if (name.IsEmpty() && (person.age!=0))
		{
			CString out = path + "图片组是:" + group + "  用户名是:" + "尚未输入" + "      年龄是:" + age;
			m_uinfo.AddString(out);
		}
		else if (person.age == 0 &&(!name.IsEmpty()))
		{
			CString out = path + "图片组是:" + group + "  用户名是:" + name + "      年龄是:" + "尚未输入";
			m_uinfo.AddString(out);

		}
		else if (name.IsEmpty() && (person.age == 0))
		{
			CString out = path + "图片组是:" + group + "  用户名是:" + "尚未输入" + "      年龄是:" + "尚未输入";
			m_uinfo.AddString(out);
		}
		else if(person.age!=0 && (!name.IsEmpty()))
		{
			CString out = path + "图片组是:" + group + "  用户名是:" + name + "      年龄是:" + age;
			m_uinfo.AddString(out);
		}
	}



	for (int i = 0; i < (*groups).size(); i++)
	{
		free(group[i]);
	}

	free(group);


	//for (int i = 0; i < groups.size(); i++)
	//{
	//	CString c;
	//	c.Format(TEXT("%s"), p[i]);
	//	MessageBox(c);
	//}



	std::vector<PerSon>().swap(persons);


}


void MatchUser::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
}
