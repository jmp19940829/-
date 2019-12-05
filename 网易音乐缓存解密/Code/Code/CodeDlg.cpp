
// CodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Code.h"
#include "CodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCodeDlg* g_Code;
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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCodeDlg 对话框



CCodeDlg::CCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CODE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CCodeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCodeDlg::OnBnClickedButton3)
//	ON_BN_CLICKED(IDC_BUTTON5, &CCodeDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CCodeDlg::OnBnClickedButton4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

CString g_strPath;
// CCodeDlg 消息处理程序

BOOL CCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	g_Code = this;
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCodeDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeDlg::OnBnClickedButton2()
{
	TCHAR szPath[MAX_PATH] = { 0 };//MAX_PATH 是路径的最大长度
	BROWSEINFO mBroInfo = { 0 };
	mBroInfo.hwndOwner = m_hWnd;
	ITEMIDLIST *pidl = SHBrowseForFolder(&mBroInfo);//浏览目录对话框

	if (SHGetPathFromIDList(pidl, szPath)) {
		SetDlgItemText(IDC_EDIT1, szPath);
	}
	CoTaskMemFree(pidl);
}

BOOL IsDirExist(char* csDir)
{
	DWORD dwAttrib = GetFileAttributes(csDir);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}
bool CodeMP3(BYTE *byEnCode,BYTE* byBuf,DWORD dwLen)
{
	for (int i=0;i<dwLen;i++)
	{
		byBuf[i]=byEnCode[i] ^ 0xA3;
	}
	return true;
}
BOOL CodeFileMp3(CString strPath)
{
	
	g_Code->SetWindowTextA(strPath);
	CFile file;
	if (!file.Open(strPath, CFile::modeReadWrite ))
	{
		AfxMessageBox("请关闭网易音乐后再试！");
		return FALSE;
	}
	
	DWORD dwLen=file.GetLength();
	BYTE* arrBuf = new BYTE[dwLen];
	BYTE* arrDecode=new BYTE[dwLen];
	file.Read(arrBuf, dwLen);
	CodeMP3(arrBuf, arrDecode, dwLen);
	CFile file2;
	strPath.Format("%s\\%d.mp3", g_strPath, GetTickCount());
	HANDLE handle=CreateFile(strPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (handle== INVALID_HANDLE_VALUE)
	{
		int nErr=GetLastError();
		delete[] arrBuf;
		delete[] arrDecode;
		return FALSE;
	}
	DWORD dwByte;
	if (!WriteFile(handle, arrDecode, dwLen, &dwByte, NULL))
	{
		delete[] arrBuf;
		delete[] arrDecode;
		int nErr = GetLastError();
		return FALSE;
	}
	delete[] arrBuf;
	delete[] arrDecode;
	file.Close();
	return TRUE;
}



/************************************
@ Brief:		遍历文件夹
@ Author:		woniu201
@ Created:		2018/09/13
@ Return:
************************************/
BOOL DirectoryList(char* path)
{
	WIN32_FIND_DATA FindData;
	HANDLE handle;


	char fullName[2048] = { 0 };

	char filePathName[2048] = { 0 };
	strcpy(filePathName, path);
	strcat(filePathName, "\\*.*");
	handle = FindFirstFile(filePathName, &FindData);
	if (handle == INVALID_HANDLE_VALUE)
	{
		//cout << "搜索失败" << endl;
	}
	while (FindNextFile(handle, &FindData))
	{
		//过滤.和..
		if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}
		CString strFile;
		strFile.Format("%s\\%s", path, FindData.cFileName);
		//判断是否是文件夹
		if (IsDirExist(fullName))
		{
			DirectoryList(fullName);
		}
		if (strFile.Find(".uc")!=-1)
		{
			CodeFileMp3(strFile);
		}
	}
	FindClose(handle);
	CCodeDlg* th = (CCodeDlg*)AfxGetMainWnd();
	g_Code->SetWindowTextA("解密完成！");
	AfxMessageBox("解密后的保存路径:" + g_strPath);
	g_Code->GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	return TRUE;
}
DWORD WINAPI PROCCode(LPVOID th)
{
	DirectoryList((char*)th);
	return 0;
}
void CCodeDlg::OnBnClickedButton3()
{
	CString strPath;
	GetDlgItemText(IDC_EDIT1, strPath);
	GetDlgItemText(IDC_EDIT2, g_strPath);
	if (g_strPath.IsEmpty())
	{
		AfxMessageBox("请选择解密后的MP3保存路径!");
		return;
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	CloseHandle(CreateThread(NULL, 0, PROCCode, strPath.GetBuffer(), 0, NULL));
	strPath.ReleaseBuffer();
}


void CCodeDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCodeDlg::OnBnClickedButton4()
{
	TCHAR szPath[MAX_PATH] = { 0 };//MAX_PATH 是路径的最大长度
	BROWSEINFO mBroInfo = { 0 };
	mBroInfo.hwndOwner = m_hWnd;
	ITEMIDLIST *pidl = SHBrowseForFolder(&mBroInfo);//浏览目录对话框

	if (SHGetPathFromIDList(pidl, szPath)) {
		SetDlgItemText(IDC_EDIT2, szPath);
	}
	CoTaskMemFree(pidl);
}


HBRUSH CCodeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATISHI:
		//设置控件的显示背景颜色
		pDC->SetTextColor(RGB(255, 65, 255));
		pDC->SetBkMode(TRANSPARENT);
		//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
		return hbr;
		break;
	}
	return hbr;
}
