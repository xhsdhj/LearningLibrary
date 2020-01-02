#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

#define IP "127.0.0.1"		//IP��ַ
#define NAME_SIZE 32		//������󳤶�
#define BUF_SIZE 256

using namespace std;

char szName[NAME_SIZE] = "[DEFAULT]";
char szMsg[BUF_SIZE];

//������Ϣ������˵ĺ���
unsigned WINAPI SendMsg(void* arg)
{
	if (arg == NULL)
	{
		return -1;
	}
	//1. ���մ��ݹ����Ĳ���
	SOCKET hClntSock = *((SOCKET*)arg);
	char szNameMsg[NAME_SIZE + BUF_SIZE];	//��������,������Ϣ

	//ѭ�����������ڿ���̨����Ϣ
	while (true)
	{
		fgets(szMsg, BUF_SIZE, stdin);//��������һ��

		//�˳����� ���յ�q��Q
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n"))
		{
			closesocket(hClntSock);
			exit(0);
		}

		sprintf_s(szNameMsg, "%s %s", szName, szMsg);//�ַ���ƴ��
		send(hClntSock, szNameMsg, strlen(szNameMsg), 0);//����

	}

	return 0;
}

//������Ϣ������˵ĺ���
unsigned WINAPI RecvMsg(void* arg)
{
	if (arg == NULL)
	{
		return -1;
	}
	//1. ���մ��ݹ����Ĳ���
	SOCKET hClntSock = *((SOCKET*)arg);
	char szNameMsg[NAME_SIZE + BUF_SIZE];	//��������,������Ϣ
	int iLen = 0;

	while (true)
	{
		iLen = recv(hClntSock, szNameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		//�������Ͽ�
		if (iLen == -1)
		{
			return -1;
		}
		// szNameMsg ���±�0��iLen-1�����յ������� iLen��
		szNameMsg[iLen] = 0;

		//���յ����������������̨
		fputs(szNameMsg, stdout);
	}
	

	return 0;
}

//��������main����,������������ �ڵ�ǰĿ¼����shift + ����Ҽ�
int main(int argc, char *argv[]) 
{
	//�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	SOCKET hSock;
	SOCKADDR_IN servAddr;
	HANDLE hSendThread, hRecvThread;

	wVersionRequested = MAKEWORD(1, 1);
	//��ʼ���׽��ֿ�
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return err;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}
	sprintf_s(szName, "[%s]", argv[1]);
	//1. ����socket
	hSock = socket(AF_INET, SOCK_STREAM, 0);

	//2. ���õ�ַ
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9190);

	//3. ���ӷ�����
	if (connect(hSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) 
	{
		printf("connect error error code = %d\n", GetLastError());
	}

	//4. ���ͷ���������Ϣ ����һ���̷߳�����Ϣ
	hSendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg,
		(void*)&hSock, 0, NULL);

	//5. ���շ���������Ϣ ����һ���߳̽�����Ϣ	
	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg,
		(void*)&hSock, 0, NULL);

	//�ȴ��ں˶�����źŷ����仯
	if (hSendThread != 0)
	{
		WaitForSingleObject(hSendThread, INFINITE);
	}
	if (hRecvThread != 0)
	{
		WaitForSingleObject(hRecvThread, INFINITE);
	}

	
	//6. �ر��׽���
	closesocket(hSock);
	return 0;
}