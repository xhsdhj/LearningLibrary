
// ClipboardDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Clipboard.h"
#include "ClipboardDlg.h"
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


// CClipboardDlg 对话框



CClipboardDlg::CClipboardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIPBOARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClipboardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CClipboardDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_RECV_BTN, &CClipboardDlg::OnBnClickedRecvBtn)
END_MESSAGE_MAP()


// CClipboardDlg 消息处理程序

BOOL CClipboardDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClipboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClipboardDlg::OnPaint()
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
HCURSOR CClipboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClipboardDlg::OnBnClickedSendBtn()
{
	//1. 打开剪切板
	if (OpenClipboard())
	{
		//2.清空剪切板
		EmptyClipboard();

		//要发送的数据
		char* szSendBuf;

		//3.获取编辑框的内容
		CStringW strSendW;
		GetDlgItemText(IDC_EDIT_SEND, strSendW);
		CStringA strSend = (CStringA)strSendW;

		//4.分配一个内存对象, 内存对象的句柄就是 hClip
		HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE, strSend.GetLength() + 1);

		if (hClip == 0)
		{
			TRACE("### hClip = %d", GetLastError());
			return;
		}

		//5.将剪切板句柄加锁
		szSendBuf = (char*)GlobalLock(hClip);
		if (szSendBuf == 0)
		{
			TRACE("### szSendBuf = %d", GetLastError());
			return;
		}
		TRACE("### strSend = %s", strSend);
		//要发送的数据		
		size_t len = strlen(strSend) + strlen(szSendBuf);
		TRACE("### size = %d", strlen(strSend) + strlen(szSendBuf));
		strcpy_s(szSendBuf, len, strSend);
		TRACE("### szSendBuf = %s", szSendBuf);
		GlobalUnlock(hClip);

		//6.将数据放入剪切板
		SetClipboardData(CF_TEXT, hClip);

		//7. 关闭剪切板
		CloseClipboard();
	}

}


void CClipboardDlg::OnBnClickedRecvBtn()
{
	//1. 打开剪切板
	if (OpenClipboard())
	{
		//2.确认剪切板是否可用
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			HANDLE hClip;
			char* pBuf;
			//向剪切板要数据
			hClip = GetClipboardData(CF_TEXT);
			pBuf = (char*)GlobalLock(hClip);
			GlobalUnlock(hClip);
			USES_CONVERSION;
			LPCWSTR strBuf = A2W(pBuf);
			SetDlgItemText(IDC_EDIT_RECV, strBuf);
		}

		// 关闭剪切板
		CloseClipboard();
	}
}
