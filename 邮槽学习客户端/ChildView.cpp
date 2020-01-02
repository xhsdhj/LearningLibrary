
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "邮槽学习客户端.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	hReadPipe = GetStdHandle(STD_INPUT_HANDLE);
	hWritePipe = GetStdHandle(STD_OUTPUT_HANDLE);
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
	ON_COMMAND(ID_SEND, &CChildView::OnSend)
	ON_COMMAND(ID_CONNECT_NAMED_PIPE, &CChildView::OnConnectNamedPipe)
	ON_COMMAND(ID_READ_NAMED_PIPE, &CChildView::OnReadNamedPipe)
	ON_COMMAND(ID_WRITE_NAMED_PIPE, &CChildView::OnWriteNamedPipe)
	ON_COMMAND(ID_CLI_PIPE_READ, &CChildView::OnCliPipeRead)
	ON_COMMAND(ID_CLI_PIPE_WRITE, &CChildView::OnCliPipeWrite)
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



void CChildView::OnSend()
{
	//1.创建一个文件句柄
	LPCTSTR szSlotName = TEXT("\\\\.\\mailslot\\sample_mailslot");
	HANDLE hMailSlot = CreateFile(szSlotName, FILE_GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateFile failed with %d\n", GetLastError());
		return;
	}

	//2. 写入数据
	char szBuf[] = "黄海峰";
	DWORD dwWrite;
	if (!WriteFile(hMailSlot, szBuf, strlen(szBuf) + 1, &dwWrite, NULL))
	{
		MessageBox(_T("读取数据失败"));
		CloseHandle(hMailSlot);
		return;
	}
	//MessageBox((CStringW)szBuf);
	CloseHandle(hMailSlot);
}


void CChildView::OnConnectNamedPipe()
{
	LPCTSTR szNamedPipeName = TEXT("\\\\.\\pipe\\mypipe");
	
	if (0 == WaitNamedPipe(szNamedPipeName, NMPWAIT_WAIT_FOREVER))
	{
		MessageBox(_T("当前没有可利用的管道!"));
		return;
	}
	hNamedPipe = CreateFile(szNamedPipeName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateFile failed with %d\n", GetLastError());
		MessageBox(_T("打开命名管道失败!"));
		return;
	}
	else {
		MessageBox(_T("打开命名管道成功!"));
	}
}


void CChildView::OnReadNamedPipe()
{
	//读取数据
	char szBuf[100] = { 0 };
	DWORD dwRead;
	if (!ReadFile(hNamedPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取服务端数据失败"));
		return;
	}
	MessageBox((CStringW)szBuf);
}


void CChildView::OnWriteNamedPipe()
{
	//写入数据
	char szBuf[] = "OnNamedPipe 客户端";
	DWORD dwWrite;
	if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1, &dwWrite, NULL))
	{
		MessageBox(_T("写入数据失败"));
		//CloseHandle(hNamedPipe);
		return;
	}
	//CloseHandle(hNamedPipe);
}


void CChildView::OnCliPipeRead()
{
	char szBuf[100] = { 0 };
	DWORD dwRead;
	if (!ReadFile(hReadPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取数据失败!"));
		//CloseHandle(hReadPipe);
		return;
	}
	else
	{
		MessageBox(_T("读取数据成功!"));
		MessageBox((CStringW)szBuf);
		return;
	}
	
}


void CChildView::OnCliPipeWrite()
{
	char szBuf[] = "黄海峰 客户端";
	DWORD dwWrite;
	if (!WriteFile(hWritePipe, szBuf, strlen(szBuf) + 1, &dwWrite, NULL))
	{
		MessageBox(_T("写入数据失败!"));
		CloseHandle(hWritePipe);
		return;
	}
	else 
	{
		MessageBox(_T("写入数据成功!"));
		CloseHandle(hWritePipe);
		return;
	}
}
