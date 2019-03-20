
// MFCFindMan2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCFindMan2.h"
#include "MFCFindMan2Dlg.h"
#include "afxdialogex.h"
#include "TestOp.h"

#include "AddGroup.h"
#include "LMatchPerson.h"
#include "DaoUtils.h"
#include "Test.h"

#define MAXLEN 50
#define NAMELEN 20

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_32771, &CAboutDlg::On32771)
END_MESSAGE_MAP()


// CMFCFindMan2Dlg 对话框



CMFCFindMan2Dlg::CMFCFindMan2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCFINDMAN2_DIALOG, pParent)
	, m_OutName(_T(""))
	, m_outage(0)
	, m_outpath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	std::vector<CString>().swap(groups);
	this->start = 0;
	this->end = 50;
	//调用用户组查询
	int a = 0;
	int ret = GetGroup(&(this->p), &a);
	if (ret == 0)
	{


		for (int i = 0; i < a; i++)
		{
			CString ss(p[i]);
			groups.push_back(ss);

		}

	}
	
	for (int i = 0; i < a; i++)
	{
		free(p[i]);
	}
	free(p);
	this->p = NULL;


}

void CMFCFindMan2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_NewG);
	DDX_Control(pDX, IDC_COMBO2, m_OutGroup);
	DDX_Control(pDX, IDC_LIST2, m_UInfoList);
	DDX_Text(pDX, IDC_EDIT2, m_OutName);
	DDX_Text(pDX, IDC_EDIT4, m_outage);
	DDX_Text(pDX, IDC_EDIT5, m_outpath);
}

BEGIN_MESSAGE_MAP(CMFCFindMan2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCFindMan2Dlg::OnCbnSelchangeCombo2)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMFCFindMan2Dlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCFindMan2Dlg::OnBnClickedButton3)
//	ON_STN_CLICKED(IDC_TEXT, &CMFCFindMan2Dlg::OnStnClickedText)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCFindMan2Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCFindMan2Dlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCFindMan2Dlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCFindMan2Dlg::OnEnChangeEdit4)
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32771, &CMFCFindMan2Dlg::On32771)
	ON_COMMAND(ID_32772, &CMFCFindMan2Dlg::On32772)
	ON_COMMAND(ID_32774, &CMFCFindMan2Dlg::On32774)
	ON_COMMAND(ID_32773, &CMFCFindMan2Dlg::On32773)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCFindMan2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCFindMan2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCFindMan2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCFindMan2Dlg::OnBnClickedButton6)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCFindMan2Dlg 消息处理程序

BOOL CMFCFindMan2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCFindMan2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCFindMan2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	int c = this->m_OutGroup.GetCurSel();

	m_OutGroup.ResetContent();


	for (CString& c : this->groups)
	{
		this->m_OutGroup.AddString(c);
	}

	this->m_OutGroup.AddString(TEXT("添加用户组"));

	if (c != LB_ERR)
	{
		this->m_OutGroup.SetCurSel(c);
	}
	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCFindMan2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCFindMan2Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->start = 0;
	this->end = 50;
	int c = this->m_OutGroup.GetCurSel();
	m_UInfoList.ResetContent();
	int a = 0;
	int ret = 0;
	if (c != LB_ERR)
	{
		
		CString Tgroup;
		m_OutGroup.GetLBText(c, Tgroup);

		if (Tgroup == TEXT("添加用户组"))
		{
			AddGroup dailog;
			dailog.DoModal();
			//刷新组
			std::vector<CString>().swap(groups);

			//调用用户组查询
			int a = 0;
			int ret = GetGroup(&(this->p), &a);
			if (ret == 0)
			{


				for (int i = 0; i < a; i++)
				{
					CString ss(p[i]);
					groups.push_back(ss);

				}

			}

			for (int i = 0; i < a; i++)
			{
				free(p[i]);
			}
			free(p);
			this->p = NULL;
			Invalidate();
			return;
		}

		//组名
		char group[NAMELEN];
		memset(group, 0, sizeof(group));
		WideCharToMultiByte(CP_ACP, 0, Tgroup, -1, group, sizeof(group), NULL, NULL);

		ret = GetUsers(group, &a, &(this->p),this->start,this->end);


		if (ret == 0)
		{
			for (int i = 0; i < a; i++)
			{
				CString ss(p[i]);
				m_UInfoList.AddString(ss);
			}

		}

		
	}

	for (int i = 0; i < a; i++)
	{
		free(p[i]);
	}
	free(p);
	this->p = NULL;

}


void CMFCFindMan2Dlg::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
	//查询用户信息 包括 姓名 和 图片 放在 框框中


	int c;
	int ret;
	person = new PerSon();
	memset(person, 0, sizeof(PerSon));
	CString Tgroup;
	char group[NAMELEN];
	CString Tuser;
	char user[MAXLEN];


	CString ipath;
	//获取组
	c = this->m_OutGroup.GetCurSel();
	if (c != LB_ERR)
	{
		m_OutGroup.GetLBText(c, Tgroup);
		//组名
		WideCharToMultiByte(CP_ACP, 0, Tgroup, -1, group, sizeof(group), NULL, NULL);
	}
	c = this->m_UInfoList.GetCurSel();

	if (c != LB_ERR)
	{
		CString Tuser;
		memset(user, 0, sizeof(user));
		this->m_UInfoList.GetText(c, Tuser);
		WideCharToMultiByte(CP_ACP, 0, Tuser, -1, user, sizeof(user), NULL, NULL);
		ret = GetUserInfo(group, user, person);
		
		if (ret != 0)
		{
			MessageBox(TEXT("用户信息获取失败"));
			return;
		}

		char src[30] = { 0 };
		memcpy(src, person->path,strlen(person->path));
		for (unsigned int i = 0; i < strlen(person->path); i++)
		{
			if (src[i] == '/')
			{
				src[i] = '\\';
			}
		}


		
		CString outpath(src);
		ipath = outpath;

		CString outgroup(person->group);

		CString outname(person->name);
		
		m_OutName.SetString(outname);

		m_outpath.SetString(outpath);


		m_outage = person->age;


		UpdateData(FALSE);
		
		//free(person);

	}

	c = this->m_UInfoList.GetCurSel();
	if (c != LB_ERR)
	{
		memset(user, 0, sizeof(user));
		this->m_UInfoList.GetText(c, Tuser);
		WideCharToMultiByte(CP_ACP, 0, Tuser, -1, user, sizeof(user), NULL, NULL);
		int pos = 0;
		for (int i = 0; user[i] != '\0'; i++)
		{
			if (pos == 0 && user[i] == '_')
			{
				user[i] = ':';
				pos++;
			}
			if (pos == 1 && user[i] == '_')
			{
				user[i] = '\\';
				pos++;
			}
			else if (user[i] == '_')
			{
				user[i] = '\\';
				pos++;
			}
	
		}

		char * jj = strstr(user, "\\jpg");
		*(--jj) = '.';


	}
	//读取图片
	CString imagepath(ipath);

	CImage image;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_STATICI);
	CDC* pDC = pWnd->GetDC();
	HDC hDC = pDC->m_hDC;

	CRect rect_frame;
	pWnd->GetClientRect(&rect_frame);
	image.Load(imagepath);
	if (image.IsNull())
	{

		image.Load(_T("c:\\no.jpg"));
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



	CString ss(user);
	UpdateData(FALSE);

}


void CMFCFindMan2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int ret = 0;
	if (m_OutName.IsEmpty())
	{
		MessageBox(TEXT("请输入用户名"));
		return;
	}
	if (m_outpath.IsEmpty())
	{
		MessageBox(TEXT("请输入图片路径"));
		return;
	}
	if (m_outage>=100 ||m_outage<=0)
	{
		MessageBox(TEXT("请输入年龄 年龄应当大于0 小于100"));
		return;
	}


	//获取修改的图片 用户名 年龄 组
	PerSon* person = new PerSon();
	memset(person, 0, sizeof(PerSon));
	WideCharToMultiByte(CP_ACP, 0, m_OutName, -1, person->name, sizeof(person->name), NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, m_outpath, -1, person->path, sizeof(person->path), NULL, NULL);
	
	
	int c;
	CString group;
	c = this->m_OutGroup.GetCurSel();
	if (c != LB_ERR)
	{
		m_OutGroup.GetLBText(c, group);
		
	}
	WideCharToMultiByte(CP_ACP, 0, group, -1, person->group, sizeof(person->group), NULL, NULL);
	person->age = m_outage;


	CString user;
	c = this->m_UInfoList.GetCurSel();
	if (c != LB_ERR)
	{
		this->m_UInfoList.GetText(c, user);
	}
	WideCharToMultiByte(CP_ACP, 0, user, -1, person->user, sizeof(person->user), NULL, NULL);



	ret = UpdateInfo(person);
	if (ret == 0)
	{
		MessageBox(TEXT("修改成功"));
	}
	else if (ret == -5)
	{
		MessageBox(TEXT("修改失败"));
	}
	else if (ret == -7)
	{
		MessageBox(TEXT("数据库修改失败"));
	}

	delete person;

}


void CMFCFindMan2Dlg::OnStnClickedText()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCFindMan2Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCFindMan2Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_UInfoList.GetCount() < 50)
	{
		MessageBox(TEXT("没有更多数据 请勿点击下一页"));
		this->start = 0;
		this->end = 50;
		return;
		
	}

	this->start += 50;
	this->end += 50;
	int c = this->m_OutGroup.GetCurSel();
	m_UInfoList.ResetContent();
	int a = 0;
	int ret = 0;
	if (c != LB_ERR)
	{

		CString Tgroup;
		m_OutGroup.GetLBText(c, Tgroup);
		//组名
		char group[NAMELEN];
		memset(group, 0, sizeof(group));
		WideCharToMultiByte(CP_ACP, 0, Tgroup, -1, group, sizeof(group), NULL, NULL);

		ret = GetUsers(group, &a, &(this->p), this->start, this->end);

		if (ret == 0)
		{
			for (int i = 0; i < a; i++)
			{
				CString ss(p[i]);
				m_UInfoList.AddString(ss);

			}

		}


	}
	m_OutName.SetString(TEXT(""));
	m_outpath.SetString(TEXT(""));
	m_outage = 0;
	UpdateData(FALSE);


	for (int i = 0; i < a; i++)
	{
		free(p[i]);
	}
	free(p);
	this->p = NULL;

}


void CMFCFindMan2Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCFindMan2Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCFindMan2Dlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCFindMan2Dlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CDialogEx::OnRButtonDblClk(nFlags, point);
}


void CMFCFindMan2Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//CMenu   menu;   //定义下面要用到的cmenu对象
	//menu.LoadMenu(IDR_MENU1); //装载自定义的右键菜单 
	//CMenu   *pContextMenu = menu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 
	//ClientToScreen(&point);
	//pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CAboutDlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(TEXT("新建用户组"));
}


void CMFCFindMan2Dlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
	AddGroup addgroup;
	addgroup.DoModal();



	//刷新组
	std::vector<CString>().swap(groups);
	//调用用户组查询
	int a = 0;
	int ret = GetGroup(&(this->p), &a);
	if (ret == 0)
	{


		for (int i = 0; i < a; i++)
		{
			CString ss(p[i]);
			groups.push_back(ss);

		}

	}

	for (int i = 0; i < a; i++)
	{
		free(p[i]);
	}
	free(p);
	this->p = NULL;

	Invalidate();

}


void CMFCFindMan2Dlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	int c = this->m_OutGroup.GetCurSel();
	int ret = 0;
	//组名
	char group[NAMELEN];
	memset(group, 0, sizeof(group));
	if (c != LB_ERR)
	{
		CString cgroup;
		m_OutGroup.GetLBText(c, cgroup);
		WideCharToMultiByte(CP_ACP, 0, cgroup, -1, group, sizeof(group), NULL, NULL);
	}
	else
	{
		MessageBox(TEXT("请选中要删除的组"));
		return;
	}
	ret = DelGroup(group);
	if (ret != 0)
	{
		MessageBox(TEXT("删除失败"));
		
	}
	//录入数据库 插入 face_token name age
	MYSQL* mysql;
	//初始化链接数据库
	InitMsql(&mysql, "localhost", "root", "kzh971104", "xs_db");

	//向数据库插入数据
	char sqlbuf[1024] = { 0 };

	//strcpy(sqlbuf, "insert into `userinfo`(`face_token`,`path`,`user`,`group`,`name`,`age`) values ('fdsaf', 'fadf', 'fad', 'fda', 'fad', 8)");

	sprintf_s(sqlbuf, "delete from userinfo where `group` = '%s'", \
		group);

	InSertInfo(mysql, sqlbuf);

	m_UInfoList.ResetContent();
	m_OutName.SetString(TEXT(""));
	m_outpath.SetString(TEXT(""));
	m_outage = 0;
	UpdateData(FALSE);

	MessageBox(TEXT("删除成功"));
	//刷新组
	std::vector<CString>().swap(groups);

	//调用用户组查询
	int a = 0;
	ret = GetGroup(&(this->p), &a);
	if (ret == 0)
	{


		for (int i = 0; i < a; i++)
		{
			CString ss(p[i]);
			groups.push_back(ss);

		}

	}

	for (int i = 0; i < a; i++)
	{
		free(p[i]);
	}
	free(p);
	this->p = NULL;

	Invalidate();

}


void CMFCFindMan2Dlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
	//打开图片选择 并且导入图片
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
			this->paths.push_back(filename);
		}
	}

	//for (CString& c: paths)
	//{
	//	MessageBox(c);
	//}

	int ret = 0;
	int count = 0;
	//组名
	char group[NAMELEN];
	memset(group, 0, sizeof(group));
	//图片路径
	char path[MAXLEN];
	memset(path, 0, sizeof(path));

	int c = this->m_OutGroup.GetCurSel();
	if (paths.size() != 0 && (c == LB_ERR))
	{
		MessageBox(TEXT("请选择用户组"));
		return;
	}

	if (c != LB_ERR)
	{
		CString cgroup;
		m_OutGroup.GetLBText(c, cgroup);
		WideCharToMultiByte(CP_ACP, 0, cgroup, -1, group, sizeof(group), NULL, NULL);
		//导入图片
		for (CString& Tpath : paths)
		{


			WideCharToMultiByte(CP_ACP, 0, Tpath, -1, path, sizeof(path), NULL, NULL);
			//调用百度AI 人脸注册
			ret = InputAnCheck(path, group);
			if (ret != 0)
			{
				if (ret == -5)
				{
					CString out;
					out.Format(TEXT("%s已存在"), Tpath);
					MessageBox(out);
					count++;
				}
				else if (ret == -4)
				{
					CString out;
					out.Format(TEXT("%s未检测到人脸"), Tpath);
					MessageBox(out);
					count++;
				}
				else
				{
					count++;
				}

			}
			memset(path, 0, sizeof(path));
		}

		memset(group, 0, sizeof(group));
	}


	//判断成功个数
	if (count == 0 && (paths.size()!=0))
	{
		MessageBox(TEXT("录入成功"));
	}
	else if(paths.size()!=0)
	{
		CString ss;
		ss.Format(TEXT("图片录入失败张数：%d"), count);
		MessageBox(ss);
	}
	WPARAM wParam = MAKELPARAM(IDC_COMBO2, CBN_SELCHANGE);
	HWND hWnd = AfxGetMainWnd()->m_hWnd;
	SendMessage(WM_COMMAND, wParam, (LPARAM)hWnd);

}


void CMFCFindMan2Dlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	//查询用户利用图片 比对

	LMatchPerson lmatchperson(NULL, &(this->groups));
	lmatchperson.DoModal();

}


void CMFCFindMan2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前用户 组 和用户
	int c;
	int ret = 0;

	CString Tgroup;
	char group[NAMELEN];
	CString Tuser;
	char user[NAMELEN];

	CString ipath;
	//获取组
	c = this->m_OutGroup.GetCurSel();
	if (c != LB_ERR)
	{
		m_OutGroup.GetLBText(c, Tgroup);
		//组名
		WideCharToMultiByte(CP_ACP, 0, Tgroup, -1, group, sizeof(group), NULL, NULL);

	}
	else
	{
		MessageBox(TEXT("请选择组"));
		return;
	}
	
	c = this->m_UInfoList.GetCurSel();
	if (c != LB_ERR)
	{
		CString Tuser;
		memset(user, 0, sizeof(user));
		this->m_UInfoList.GetText(c, Tuser);
		WideCharToMultiByte(CP_ACP, 0, Tuser, -1, user, sizeof(user), NULL, NULL);

		//调用删除用户

		ret = DelUser(group, user);
		if (ret == 0)
		{
			MessageBox(TEXT("删除成功"));
			WPARAM wParam = MAKELPARAM(IDC_COMBO2, CBN_SELCHANGE);
			HWND hWnd = AfxGetMainWnd()->m_hWnd;
			SendMessage(WM_COMMAND, wParam, (LPARAM)hWnd);
			
			//录入数据库 插入 face_token name age
			MYSQL* mysql;
			//初始化链接数据库
			InitMsql(&mysql, "localhost", "root", "kzh971104", "xs_db");
			
			//向数据库插入数据
			char sqlbuf[1024] = { 0 };

			//strcpy(sqlbuf, "insert into `userinfo`(`face_token`,`path`,`user`,`group`,`name`,`age`) values ('fdsaf', 'fadf', 'fad', 'fda', 'fad', 8)");

			sprintf_s(sqlbuf, "delete from userinfo where `group` = '%s' and `user`='%s'", \
				group,user);

			InSertInfo(mysql, sqlbuf);

			DeMysql(mysql);

			return;
		}
		else
		{
			MessageBox(TEXT("删除失败"));
			return;
		}


	}
	else
	{
		MessageBox(TEXT("请选中用户"));
		return;
	}

}


BOOL CMFCFindMan2Dlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类


	return CDialogEx::PreCreateWindow(cs);
}


BOOL CMFCFindMan2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCFindMan2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("Image Files(*.jpg)|*.jpg|"), NULL);
	dlg.m_ofn.lpstrTitle = _T("选择图片");
	CString filename;
	
	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		while (fileNamesPosition != NULL)
		{
			filename = dlg.GetNextPathName(fileNamesPosition);
		}
	}
	char filepath[NAMELEN];
	memset(filepath, 0, sizeof(filepath));

	WideCharToMultiByte(CP_ACP, 0, filename, -1, filepath, sizeof(filepath), NULL, NULL);

	memcpy(person->path, filepath, sizeof(filepath));

	if (!filename.IsEmpty())
	{
		m_outpath.SetString(filename);
	}
	//读取图片 
	CString imagepath(filename);

	CImage image;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_STATICI);
	CDC* pDC = pWnd->GetDC();
	HDC hDC = pDC->m_hDC;

	CRect rect_frame;
	pWnd->GetClientRect(&rect_frame);
	image.Load(imagepath);
	if (image.IsNull())
	{

		/*image.Load(_T("c:\/no.jpg"));
		::SetStretchBltMode(hDC, HALFTONE);
		::SetBrushOrgEx(hDC, 0, 0, NULL);
		image.Draw(hDC, rect_frame);*/
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


void CMFCFindMan2Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开图片选择 并且导入图片
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
			this->paths.push_back(filename);
		}
	}

	//for (CString& c: paths)
	//{
	//	MessageBox(c);
	//}

	int ret = 0;
	int count = 0;
	//组名
	char group[NAMELEN];
	memset(group, 0, sizeof(group));
	//图片路径
	char path[MAXLEN];
	memset(path, 0, sizeof(path));

	int c = this->m_OutGroup.GetCurSel();
	if (paths.size() != 0 && (c == LB_ERR))
	{
		MessageBox(TEXT("请选择用户组"));
		return;
	}

	if (c != LB_ERR)
	{
		CString cgroup;
		m_OutGroup.GetLBText(c, cgroup);
		if (cgroup == TEXT("添加用户组"))
		{
			MessageBox(TEXT("请选中添加的组"));
			return;
		}

		WideCharToMultiByte(CP_ACP, 0, cgroup, -1, group, sizeof(group), NULL, NULL);
		//导入图片
		for (CString& Tpath : paths)
		{


			WideCharToMultiByte(CP_ACP, 0, Tpath, -1, path, sizeof(path), NULL, NULL);
			//调用百度AI 人脸注册
			CString str;
			long t1 = GetTickCount();//程序段开始前取得系统运行时间(ms)
			ret = InputAnCheck(path, group);
			long t2 = GetTickCount();
			str.Format(TEXT("time:%dms"), t2 - t1);
			MessageBox(str);

			if (ret != 0)
			{
				if (ret == -5)
				{
					CString out;
					out.Format(TEXT("%s已存在"), Tpath);
					MessageBox(out);
					count++;
				}
				else if (ret == -4)
				{
					CString out;
					out.Format(TEXT("%s未检测到人脸"), Tpath);
					MessageBox(out);
					count++;
				}
				else
				{
					count++;
				}

			}
			memset(path, 0, sizeof(path));
		}

		memset(group, 0, sizeof(group));
	}


	//判断成功个数
	if (count == 0 && (paths.size() != 0))
	{
		MessageBox(TEXT("录入成功"));
	}
	else if (paths.size() != 0)
	{
		CString ss;
		ss.Format(TEXT("图片录入失败张数：%d"), count);
		MessageBox(ss);
	}
	WPARAM wParam = MAKELPARAM(IDC_COMBO2, CBN_SELCHANGE);
	HWND hWnd = AfxGetMainWnd()->m_hWnd;
	SendMessage(WM_COMMAND, wParam, (LPARAM)hWnd);
}


void CMFCFindMan2Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->start == 0)
	{
		MessageBox(TEXT("已经是最前"));
		return;
	}

	this->start -= 50;
	this->end -= 50;
	int c = this->m_OutGroup.GetCurSel();
	m_UInfoList.ResetContent();
	int a = 0;
	int ret = 0;
	if (c != LB_ERR)
	{

		CString Tgroup;
		m_OutGroup.GetLBText(c, Tgroup);
		//组名
		char group[NAMELEN];
		memset(group, 0, sizeof(group));
		WideCharToMultiByte(CP_ACP, 0, Tgroup, -1, group, sizeof(group), NULL, NULL);

		ret = GetUsers(group, &a, &(this->p), this->start, this->end);

		if (ret == 0)
		{
			for (int i = 0; i < a; i++)
			{
				CString ss(p[i]);
				m_UInfoList.AddString(ss);

			}

		}


	}
	for (int i = 0; i < a; i++)
	{
		free(p[i]);
	}
	free(p);
	this->p = NULL;


	m_OutName.SetString(TEXT(""));
	m_outpath.SetString(TEXT(""));
	m_outage = 0;
	UpdateData(FALSE);



}


void CMFCFindMan2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}
