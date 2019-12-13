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
	CString strMsg = _T("����������ӳɹ�!");
	strShow = dlg->CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	//1. �������ݵ� szRecvBuf
	TRACE(" ######Server OnReceive");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE(" ######Server szRecvBuf = %s", szRecvBuf);

	//2.��ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3.��ʾ���б��
	CString strShow;
	CString strInfo = _T("�����: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);

	//ѡ�е�ѡ��ť
	if (((CButton *)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//�Զ��ظ�
		//1.���༭������
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);

		//2.���+���ʽ ʱ��+�ǳ�+[�Զ��ظ�]+����,���͸�����˵���Ϣ
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		CString strMsg = strName + _T("[�Զ��ظ�]") + strAutoSendMsg;
		
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

		//ʱ�� + �ǳ� + strMsg
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
