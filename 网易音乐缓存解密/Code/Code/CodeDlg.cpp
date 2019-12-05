
// CodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Code.h"
#include "CodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCodeDlg* g_Code;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCodeDlg �Ի���



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
// CCodeDlg ��Ϣ�������

BOOL CCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	g_Code = this;
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeDlg::OnBnClickedButton2()
{
	TCHAR szPath[MAX_PATH] = { 0 };//MAX_PATH ��·������󳤶�
	BROWSEINFO mBroInfo = { 0 };
	mBroInfo.hwndOwner = m_hWnd;
	ITEMIDLIST *pidl = SHBrowseForFolder(&mBroInfo);//���Ŀ¼�Ի���

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
		AfxMessageBox("��ر��������ֺ����ԣ�");
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
@ Brief:		�����ļ���
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
		//cout << "����ʧ��" << endl;
	}
	while (FindNextFile(handle, &FindData))
	{
		//����.��..
		if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}
		CString strFile;
		strFile.Format("%s\\%s", path, FindData.cFileName);
		//�ж��Ƿ����ļ���
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
	g_Code->SetWindowTextA("������ɣ�");
	AfxMessageBox("���ܺ�ı���·��:" + g_strPath);
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
		AfxMessageBox("��ѡ����ܺ��MP3����·��!");
		return;
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	CloseHandle(CreateThread(NULL, 0, PROCCode, strPath.GetBuffer(), 0, NULL));
	strPath.ReleaseBuffer();
}


void CCodeDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCodeDlg::OnBnClickedButton4()
{
	TCHAR szPath[MAX_PATH] = { 0 };//MAX_PATH ��·������󳤶�
	BROWSEINFO mBroInfo = { 0 };
	mBroInfo.hwndOwner = m_hWnd;
	ITEMIDLIST *pidl = SHBrowseForFolder(&mBroInfo);//���Ŀ¼�Ի���

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
		//���ÿؼ�����ʾ������ɫ
		pDC->SetTextColor(RGB(255, 65, 255));
		pDC->SetBkMode(TRANSPARENT);
		//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
		return hbr;
		break;
	}
	return hbr;
}
