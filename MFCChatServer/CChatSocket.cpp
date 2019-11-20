#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"
#include "MFCChatServer.h"

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	//1. 接收数据到 szRecvBuf
	TRACE(" ######Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_SERVER_BUF] = { 0 };
	Receive(szRecvBuf, SEND_SERVER_BUF, 0);
	TRACE(" ######Server szRecvBuf = %s", szRecvBuf);

	//2.显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3.显示到列表框

	CString strShow;
	CString strInfo = _T("");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
