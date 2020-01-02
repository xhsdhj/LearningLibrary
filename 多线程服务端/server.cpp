#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

#define MAX_CLNT 256
#define MAX_BUF_SIZE 256

using namespace std;

//ȫ�ֱ���
SOCKET clntSocks[MAX_CLNT];	//���е����ӵĿͻ���socket
HANDLE hMutex;				//������
int clntCnt = 0;			//��ǰ������

//���͸����еĿͻ���
void SendMsg(char *szMsg, int iLen)
{
	int i = 0;
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)
	{
		send(clntSocks[i], szMsg, iLen, 0);
	}
	ReleaseMutex(hMutex);
}

//����ͻ��˵ĺ���
unsigned WINAPI HandleCln(void* arg) 
{
	if (arg == NULL)
	{
		return -1;
	}
	//1. ���մ��ݹ����Ĳ���
	SOCKET hClntSock = *((SOCKET*)arg);
	int iLen = 0, i = 0;
	char szMsg[MAX_BUF_SIZE] = { 0 };

	//2. �������ݵ��շ� ѭ������
// 	while ((iLen = recv(hClntSock, szMsg, sizeof(szMsg), 0)) != 0)
// 	{
// 		//�յ����������������пͻ���
// 		SendMsg(szMsg, iLen);
// 	}

	while (true)
	{
		iLen = recv(hClntSock, szMsg, sizeof(szMsg), 0);
		//printf("recv msg = %s, iLen = %d\n", szMsg, iLen);
		if (iLen != -1)
		{
			//�յ����������������пͻ���
			SendMsg(szMsg, iLen);
		}
		else 
		{
			break;
		}
	}
	printf("��ʱ������Ŀ %d\n", clntCnt);
	//3. ĳ�����ӶϿ�, ��Ҫ����Ͽ�������
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)
	{
		if (hClntSock == clntSocks[i])
		{
			//��λ
			while (i++ < clntCnt)
			{
				clntSocks[i] = clntSocks[i + 1];
			}
			break;
		}
	}
	clntCnt--;
	printf("�Ͽ����Ӻ�, ��ʱ������Ŀ %d\n", clntCnt);
	ReleaseMutex(hMutex);
	closesocket(hClntSock);
	return 0;
}


int main() {
	//�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	HANDLE hThread;

	wVersionRequested = MAKEWORD(1, 1);
	//��ʼ���׽��ֿ�
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return err;
	}

	if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		return -1;
	}

	//�����������
	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (hMutex == 0)	//�������������� ��ʾ�����������ʧ��
	{
		return -1;
	}

	//�½��׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(9190);

	//���׽��ֵ�����IP��ַ,�˿ں� 9190
	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == SOCKET_ERROR) 
	{
		printf("bind error num = %d\n", GetLastError());
		return -1;
	}

	//��ʼ����
	if (listen(sockSrv, 5) == SOCKET_ERROR)
	{
		printf("listen error num = %d\n", GetLastError());
		return -1;
	}

	printf("start listen\n");

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	while (true)
	{
		//���տͻ�����
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrCli, &len);
		//ÿ��һ������, ȫ������Ӧ�ü�һ����Ա,�����������һ
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = sockConn;
		ReleaseMutex(hMutex);
		//ÿ��һ������,��������һ���߳� ά���ͻ�������
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleCln,
			(void*)&sockConn, 0, NULL);
		printf("Connect client IP: %s\n", inet_ntoa(addrCli.sin_addr));
		printf("Connect client num: %d\n", clntCnt);
	}

	closesocket(sockSrv);
	WSACleanup();
	return 0;
}