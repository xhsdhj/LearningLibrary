
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "邮槽学习.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	hReadPipe = NULL;
	hWritePipe = NULL;
	hNamedPipe = NULL;
}

CChildView::~CChildView()
{
	if (hReadPipe)
	{
		CloseHandle(hReadPipe);
		hReadPipe = NULL;
	}
	if (hWritePipe)
	{
		CloseHandle(hWritePipe);
		hWritePipe = NULL;
	}
	if (hNamedPipe)
	{
		CloseHandle(hNamedPipe);
		hNamedPipe = NULL;
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_SLOT, &CChildView::OnSlot)
	ON_COMMAND(ID_CONNECT_NAMED_PIPE, &CChildView::OnConnectNamedPipe)
	ON_COMMAND(ID_READ_NAMED_PIPE, &CChildView::OnReadNamedPipe)
	ON_COMMAND(ID_WRITE_NAMED_PIPE, &CChildView::OnWriteNamedPipe)
	ON_COMMAND(ID_PIPE_CREATE, &CChildView::OnPipeCreate)
	ON_COMMAND(ID_PIPE_READ, &CChildView::OnPipeRead)
	ON_COMMAND(ID_PIPE_WRITE, &CChildView::OnPipeWrite)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



void CChildView::OnSlot()
{
	//1. 创建邮槽
	LPCTSTR szSlotName = TEXT("\\\\.\\mailslot\\sample_mailslot");
	HANDLE hSlot = CreateMailslot(szSlotName,
			0,                             // 最大消息大小的设置 0 默认 
			MAILSLOT_WAIT_FOREVER,         // 永远不超时 
			NULL); // NULL 默认安全属性

	if (hSlot == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateMailslot failed with %d\n", GetLastError());
		return;
	}

	//2.读取数据
	char szBuf[100] = { 0 };
	DWORD dwRead;
	if (!ReadFile(hSlot, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取数据失败"));
		CloseHandle(hSlot);
		return;
	}
	MessageBox((CStringW)szBuf);
	CloseHandle(hSlot);
}


void CChildView::OnConnectNamedPipe()
{
	//1.创建一个命名管道
	LPCTSTR szPipeName = TEXT("\\\\.\\pipe\\mypipe");
	hNamedPipe = CreateNamedPipe(szPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_BYTE, 1, 1024, 1024, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateNamedPipe failed with %d\n", GetLastError());
		MessageBox(_T("创建命名管道失败!"));
		return;
	}
	else {
		MessageBox(_T("创建命名管道成功!"));
	}

	//2. 等待客户端的连接
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == hEvent)
	{
		MessageBox(_T("创建事件失败!"));
		CloseHandle(hNamedPipe);
		hNamedPipe = NULL;
		return;
	}

	OVERLAPPED ovlap;
	ZeroMemory(&ovlap, sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;

	//等待连接
	if (!ConnectNamedPipe(hNamedPipe, &ovlap))
	{
		if (ERROR_IO_PENDING != GetLastError())
		{
			MessageBox(_T("等待客户端连接失败!"));
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);
			hNamedPipe = NULL;
			hEvent = NULL;
			return;
		}
	}
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
	{
		MessageBox(_T("等待对象失败!"));
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);
		hNamedPipe = NULL;
		hEvent = NULL;
		return;
	}
}


void CChildView::OnReadNamedPipe()
{
	//读取数据
	char szBuf[100] = { 0 };
	DWORD dwRead;
	if (!ReadFile(hNamedPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取客户端数据失败!"));
		return;
	}
	MessageBox((CStringW)szBuf);
}


void CChildView::OnWriteNamedPipe()
{
	//写入数据
	char szBuf[] = "OnNamedPipe Server服务端";
	DWORD dwWrite;
	if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1, &dwWrite, NULL))
	{
		MessageBox(_T("写入数据失败!"));
		return;
	}
	else 
	{
		MessageBox(_T("写入数据成功!"));
		return;
	}
}


void CChildView::OnPipeCreate()
{
	// TODO: 在此添加命令处理程序代码
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
	{
		MessageBox(_T("匿名管道创建失败!"));
		return;
	}
	else
	{
		MessageBox(_T("匿名管道创建成功!"));
	}

	//创建子进程
	STARTUPINFO strStartupInfo;	//用来指定新进程窗口如何显示
	memset(&strStartupInfo, 0, sizeof(strStartupInfo));
	strStartupInfo.cb = sizeof(strStartupInfo);
	strStartupInfo.dwFlags = STARTF_USESTDHANDLES;
	strStartupInfo.hStdInput = hReadPipe;
	strStartupInfo.hStdOutput = hWritePipe;
	strStartupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION szProcessInformation;
	memset(&szProcessInformation, 0, sizeof(szProcessInformation));

	int iRet = CreateProcess(_T("邮槽学习客户端.exe"), NULL, NULL, NULL, TRUE,
		0, NULL, NULL, &strStartupInfo, &szProcessInformation);
	if(iRet)
	{
		//创建成功
		CloseHandle(szProcessInformation.hProcess);
		CloseHandle(szProcessInformation.hThread);
		szProcessInformation.dwProcessId = 0;
		szProcessInformation.dwThreadId = 0;
		szProcessInformation.hThread = NULL;
		szProcessInformation.hProcess = NULL;
	}
	else
	{
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);
		hReadPipe = NULL;
		hWritePipe = NULL;
		MessageBox(_T("创建子进程失败!"));
		return;
	}


}


void CChildView::OnPipeRead()
{
	char szBuf[100] = { 0 };
	DWORD dwRead;
	if (!ReadFile(hReadPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取数据失败!"));
		CloseHandle(hReadPipe);
		return;
	}
	else
	{
		MessageBox(_T("读取数据成功!"));
		MessageBox((CStringW)szBuf);
		return;
	}
	
}


void CChildView::OnPipeWrite()
{
	char szBuf[] = "黄海峰 服务端";
	DWORD dwWrite;
	if (!WriteFile(hWritePipe, szBuf, strlen(szBuf) + 1, &dwWrite, NULL))
	{
		MessageBox(_T("写入数据失败!"));
		//CloseHandle(hWritePipe);
		return;
	}
	else
	{
		MessageBox(_T("写入数据成功!"));
		return;
	}
	//MessageBox((CStringW)szBuf);
	//CloseHandle(hWritePipe);
}
