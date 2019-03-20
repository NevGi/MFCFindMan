// LMatchPerson.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCFindMan2.h"
#include "LMatchPerson.h"
#include "afxdialogex.h"
#include "TestOp.h"
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#define NAMELEN 40


// LMatchPerson 对话框

IMPLEMENT_DYNAMIC(LMatchPerson, CDialogEx)

LMatchPerson::LMatchPerson(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_mtname(_T(""))
	, m_mtage(_T(""))
	, m_mtgroup(_T(""))
	, m_score(_T(""))
{

}
LMatchPerson::LMatchPerson(CWnd * pParent, std::vector<CString>* groups)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	this->groups = groups;
	ULONG_PTR m_gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

}


LMatchPerson::~LMatchPerson()
{
}

void LMatchPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_srcpath);
	DDX_Control(pDX, IDC_LIST3, m_desuser);
	DDX_Text(pDX, IDC_TEXT1, m_mtname);
	DDX_Text(pDX, IDC_TEXT2, m_mtage);
	DDX_Text(pDX, IDC_TEXT3, m_mtgroup);
	DDX_Control(pDX, IDC_LIST1, m_listctr);
	DDX_Text(pDX, IDC_TEXT4, m_score);
}


BEGIN_MESSAGE_MAP(LMatchPerson, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LMatchPerson::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST2, &LMatchPerson::OnLbnSelchangeList2)
	ON_LBN_SELCHANGE(IDC_LIST3, &LMatchPerson::OnLbnSelchangeList3)
//	ON_NOTIFY(HDN_ITEMCHANGING, 0, &LMatchPerson::OnHdnItemchangingList1)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &LMatchPerson::OnLvnItemchangedList1)
ON_NOTIFY(HDN_ITEMCHANGED, 0, &LMatchPerson::OnHdnItemchangedList1)
//ON_NOTIFY(HDN_ITEMCLICK, 0, &LMatchPerson::OnHdnItemclickList1)
ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST1, &LMatchPerson::OnLvnItemActivateList1)
//ON_NOTIFY(HDN_ITEMCLICK, 0, &LMatchPerson::OnHdnItemclickList1)
//ON_NOTIFY(NM_SETFOCUS, IDC_LIST1, &LMatchPerson::OnNMSetfocusList1)
END_MESSAGE_MAP()


// LMatchPerson 消息处理程序


void LMatchPerson::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	std::vector<CString>().swap(paths);

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
	if (paths.size() != 0)
	{
		m_srcpath.ResetContent();
	}

	for (CString&c : paths)
	{
		m_srcpath.AddString(c);
	}
	if (paths.size() == 0)
	{
		return;
	}

	m_srcpath.SetCurSel(0);
	




	WPARAM wParam1 = MAKELPARAM(IDC_LIST2, CBN_SELCHANGE);
	HWND hWnd = AfxGetMainWnd()->m_hWnd;
	SendMessage(WM_COMMAND, wParam1, (LPARAM)hWnd);





}




void LMatchPerson::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取图片去比对
	CString Tpath;
	char path[NAMELEN] = {0};
	int c;
	int ret = 0;

	//获取组
	c = this->m_srcpath.GetCurSel();
	if (c != LB_ERR)
	{
		m_desuser.ResetContent();
		std::vector<PerSon>().swap(persons);

		m_srcpath.GetText(c, Tpath);
		//组名
		WideCharToMultiByte(CP_ACP, 0, Tpath, -1, path, sizeof(path), NULL, NULL);

		//CString ss(user);
		//MessageBox(ss);

		
		//构建查询用户组
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

		ret = MatchUse(path, tgroup, &(persons));

		for (PerSon& c : persons)
		{
			

			CString ss(c.user);
			m_desuser.AddString(ss);
		}
		if (persons.size() == 0)
		{
			m_desuser.AddString(TEXT("没有匹配用户"));
			CImage image;
			CWnd* pWnd;
			pWnd = GetDlgItem(IDC_STATIC2);
			CDC* pDC = pWnd->GetDC();
			HDC hDC = pDC->m_hDC;

			CRect rect_frame;
			pWnd->GetClientRect(&rect_frame);
			image.Load(_T("c:\/no.jpg"));
			if (!image.IsNull())
			{

				
				::SetStretchBltMode(hDC, HALFTONE);
				::SetBrushOrgEx(hDC, 0, 0, NULL);
				image.Draw(hDC, rect_frame);
			}
			m_mtname.SetString(TEXT(""));
			m_mtage.SetString(TEXT(""));
			m_mtgroup.SetString(TEXT(""));
			UpdateData(FALSE);

			return;
		}



		for (int i = 0; i < (*groups).size(); i++)
		{
			free(group[i]);
		}

		free(group);


		

		//
		m_imageList.DeleteImageList();
		m_listctr.DeleteAllItems();

		//显示匹配用户
		CBitmap bitmap;

		m_imageList.Create(130, 145, ILC_COLOR32 | ILC_COLORDDB | ILC_MASK, persons.size(), 8);

		m_listctr.SetImageList(&m_imageList, LVSIL_NORMAL);

		//63 - 65行重要  GDI + 初始化功能，如果不加，无法添加非bmp文件
		int i = 0;
		for (PerSon& c : persons)
		{
			

			CString FileName(c.path);
			HBITMAP       HBitmap;
			Gdiplus::Bitmap bmp(FileName.AllocSysString());
			int sourceWidth = 130;//非bmp文件的大小与创建的CImageList保持一致
			int sourceHeight = 145;//非bmp文件的大小与创建的CImageList保持一致
			Bitmap* pThumbnail = (Bitmap*)bmp.GetThumbnailImage(sourceWidth, sourceHeight, NULL, NULL); //设定缩略图的大小
			pThumbnail->GetHBITMAP(Color(255, 255, 255), &HBitmap);
			CBitmap *pImage= CBitmap::FromHandle(HBitmap);
			if (pImage == NULL)
			{
				break;
			}

		
		//CRect cr;
		//cr.top = 900;
		//cr.left = 300;
		//GetDlgItem(IDC_BUTTON1)->MoveWindow(&cr);

		int index = m_imageList.Add(pImage, (255, 255, 255));
		int count = m_imageList.GetImageCount();
		//ImageList_RemoveAll(m_imageList);
		//count = m_imageList.GetImageCount();
		
		CString user(c.user);
	
		m_listctr.InsertItem(i, user, index);
		
		i++;

		}



	}


	//此处打开 自动 定位到第一张匹配到的
	m_desuser.SetCurSel(0);
	HWND hwnd = AfxGetMainWnd()->m_hWnd;
	WPARAM wparam2 =MAKELPARAM(IDC_LIST3, CBN_SELCHANGE);
	SendMessage(WM_COMMAND, wparam2, (LPARAM)hwnd);



}


void LMatchPerson::OnLbnSelchangeList3()
{
	// TODO: 在此添加控件通知处理程序代码
	//
	//获取图片去比对
	int c = m_desuser.GetCurSel();
	char user[NAMELEN] = {0};
	int ret = 0;

	if (c != LB_ERR)
	{
		CString Tuser;
		m_desuser.GetText(c, Tuser);
		WideCharToMultiByte(CP_ACP, 0, Tuser, -1, user, sizeof(user), NULL, NULL);
		PerSon person;
		memset(&person, 0, sizeof(PerSon));

		//数据库查找用户信息
		ret = MatchUserInfo(user, &person);

		if (ret != 0)
		{
			MessageBox(TEXT("查询失败"));
			return;
		}

		CString name(person.name);
		CString age;
		age.Format(TEXT("%d"), person.age);
		CString group(person.group);

		m_mtname.SetString(name);
		m_mtage.SetString(age);
		m_mtgroup.SetString(group);
		
		for (PerSon& c : persons)
		{
			if (strcmp(c.user, person.user)==0)
			{
				CString score;
				score.Format(TEXT("%f"),c.score);
				m_score.SetString(score);

			}
		}


		//读取图片
		CString imagepath(person.path);

		CImage image;
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_STATIC2);
		CDC* pDC = pWnd->GetDC();
		HDC hDC = pDC->m_hDC;

		CRect rect_frame;
		pWnd->GetClientRect(&rect_frame);
		image.Load(imagepath);
		if (image.IsNull())
		{

			image.Load(_T("c:\/no.jpg"));
			::SetStretchBltMode(hDC, HALFTONE);
			::SetBrushOrgEx(hDC, 0, 0, NULL);
			image.Draw(hDC, rect_frame);
		}
		else
		{
			::SetStretchBltMode(hDC, HALFTONE);
			::SetBrushOrgEx(hDC, 0, 0, NULL);
			image.Draw(hDC, rect_frame);

		}
		ReleaseDC(pDC);


		
		UpdateData(FALSE);


	}

}


BOOL LMatchPerson::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//void LMatchPerson::OnHdnItemchangingList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox(TEXT("sdgas"));
//	*pResult = 0;
//}


void LMatchPerson::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMLV->uChanged == LVIF_STATE &&
		pNMLV->uNewState == (LVIS_FOCUSED | LVIS_SELECTED)) {
		int nItem = pNMLV->iItem;
		pos = nItem;

		//获取信息
		PerSon person;
		memset(&person, 0, sizeof(PerSon));
		//数据库查找用户信息
		int ret = 0;
		ret = MatchUserInfo(persons[pos].user, &person);
		if (ret != 0)
		{
			MessageBox(TEXT("查询失败"));
			return;
		}

		CString name(person.name);
		CString age;
		age.Format(TEXT("%d"), person.age);
		CString group(person.group);

		m_mtname.SetString(name);
		m_mtage.SetString(age);
		m_mtgroup.SetString(group);
		//读取图片
		CString imagepath(person.path);

		CImage image;
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_STATIC2);
		CDC* pDC = pWnd->GetDC();
		HDC hDC = pDC->m_hDC;

		CRect rect_frame;
		pWnd->GetClientRect(&rect_frame);
		image.Load(imagepath);
		if (image.IsNull())
		{

			image.Load(_T("c:\/no.jpg"));
			::SetStretchBltMode(hDC, HALFTONE);
			::SetBrushOrgEx(hDC, 0, 0, NULL);
			image.Draw(hDC, rect_frame);
		}
		else
		{
			::SetStretchBltMode(hDC, HALFTONE);
			::SetBrushOrgEx(hDC, 0, 0, NULL);
			image.Draw(hDC, rect_frame);

		}
		ReleaseDC(pDC);



		UpdateData(FALSE);


		

	}

	*pResult = 0;
}


void LMatchPerson::OnHdnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	*pResult = 0;
}


//void LMatchPerson::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//
//	*pResult = 0;
//}


void LMatchPerson::OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	*pResult = 0;
}


//void LMatchPerson::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox(TEXT("fdsa"));
//	*pResult = 0;
//}


//void LMatchPerson::OnNMSetfocusList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox(TEXT("fdsf"));
//	*pResult = 0;
//}
