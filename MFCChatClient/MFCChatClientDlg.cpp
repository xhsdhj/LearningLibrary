﻿
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"

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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconnectBtn)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCChatClientDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
	//ON_BN_CLICKED(IDC_AUTOSEND_RADIO, &CMFCChatClientDlg::OnBnClickedAutosendRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCChatClientDlg::OnBnClickedAutosendCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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

	//设置默认端口
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	//设置默认IP
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));
	// TODO: 在此添加额外的初始化代码

	//从配置文件里面获取昵称
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };		//路径 MAX_PATH == 260
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);
	TRACE(" #####strPath = %ls", strPath);
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);

	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, 
		wszName, MAX_PATH, strFilePath);
	if (dwNum > 0)
	{
		TRACE(" #####wszName = %ls", wszName);
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}else{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}

	//初始化控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);
	
	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));

	//设置当前下标为零
	m_WordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOUR_COMBO, _T("黑色"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
		//1.定义dc
		CPaintDC dc(this); // 用于绘制的设备上下文

		//2.确定绘制的区域
		CRect rect;
		GetClientRect(&rect);
		TRACE("width = %d, height = %d", rect.Width(), rect.Height());

		//3.定义并创建一个内存设备环境 创建兼容性DC 搭桥梁
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		//4.载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmap(IDB_CLOUD_BITMAP);

		//5.将图片资源载入到位图里面 bBitMap位图
		BITMAP bBitmap;
		bmpBackGround.GetBitmap(&bBitmap);


		//6.将位图选入临时的内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGround);

		//7.开始绘制

		dc.StretchBlt(0, 0, rect.Width(), rect.Height(),
			&dcBmp, 0, 0, bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectBtn()
{

	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);

	// TODO: 在此添加控件通知处理程序代码
	CString strPort, strIP;

	//从控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//CString 转 char *
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);

	TRACE(" #####szPort = %S, szIP = %S", strPort, strIP);

	//端口的字符串转换成数字
	int iPort = _ttoi(strPort);

	//创建一个 socket 对象
	m_client = new CMySocket;

	//创建套接字
	if (!m_client->Create()) {
		TRACE(" #####m_client Create errorCode = %d", GetLastError());
		return;
	}	

	//连接服务器
	if (m_client->Connect(strIP, iPort) != SOCKET_ERROR) {
		TRACE(" #####m_client Connect errorCode = %d", GetLastError());
		return;
	}

}


void CMFCChatClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.控制控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	//2.回收资源
	m_client->Close();
	if (m_client != NULL) {
		delete m_client;
		m_client = NULL;
	}

	//3.显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), _T("断开与服务器的连接成功!"));

	m_list.AddString(strShow);
	UpdateData(FALSE);

}


void CMFCChatClientDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}

CString CMFCChatClientDlg::CatShowString(CString strInfo,CString strMsg) 
{
	//时间 + 信息(昵称) + 消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);
	CString strName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);

	strTmpMsg =  strName + _T(":") + strTmpMsg;

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//2.发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	//3.显示到列表框
	CString strShow;
	CString strInfo = _T("");
	
	strShow = CatShowString(strInfo, strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(" "));
}


void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0)
	{
		MessageBox(L"昵称不能为空!");
		return;
	}

	if (IDOK == AfxMessageBox(_T("真的要修改昵称吗?"), MB_OKCANCEL)) 
	{
		//保存昵称		
		WCHAR strPath[MAX_PATH] = { 0 };		//路径 MAX_PATH == 260
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE(" #####strPath = %ls", strPath);
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		//读取用户输入的昵称
		GetDlgItemText(IDC_NAME_EDIT, strName);

		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}
	
}


// void CMFCChatClientDlg::OnBnClickedAutosendRadio()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck())
// 	{
// 		//TRACE(" #####选中");
// 		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(FALSE);
// 	}
// 	else {
// 		//TRACE(" #####不选中");
// 		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(TRUE);
// 	}
// }


void CMFCChatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//TRACE(" #####选中");
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else {
		//TRACE(" #####不选中");
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);
#if 0
	if (strColor == L"黑色")
	{
		if (IDC_LIST1 == pWnd->GetDlgCtrlID() ||
			IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID()) {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
	}
	if (strColor == L"红色")
	{
		if (IDC_LIST1 == pWnd->GetDlgCtrlID() ||
			IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID()) {
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	if (strColor == L"蓝色")
	{
		if (IDC_LIST1 == pWnd->GetDlgCtrlID() ||
			IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID()) {
			pDC->SetTextColor(RGB(0, 0, 255));
		}
	}
	if (strColor == L"绿色")
	{
		if (IDC_LIST1 == pWnd->GetDlgCtrlID() ||
			IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID()) {
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
#endif
	if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID()) 
	{
		if (strColor == L"黑色") 
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色") 
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色") 
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色") 
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}

	return hbr;
}


BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// 规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		TRACE("回车");
		return TRUE;
	}
	// 规避空格
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		TRACE("空格");
		return TRUE;
	}

	//添加快捷键 Ctrl + X 退出整个对话框
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL) < 0)//Ctrl 是否按下
		{
			TRACE("按下 Ctrl 键");
			if (pMsg->wParam == 'X')
			{
				TRACE("按下 Ctrl 键 + X 键");
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
