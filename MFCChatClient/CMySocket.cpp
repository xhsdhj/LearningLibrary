#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"


CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("与服务器连接成功!");
	strShow = dlg->CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	//1. 接收数据到 szRecvBuf
	TRACE(" ######Server OnReceive");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE(" ######Server szRecvBuf = %s", szRecvBuf);

	//2.显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3.显示到列表框
	CString strShow;
	CString strInfo = _T("服务端: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
