#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

#define IP "127.0.0.1"		//IP地址
#define NAME_SIZE 32		//名字最大长度
#define BUF_SIZE 256

using namespace std;

char szName[NAME_SIZE] = "[DEFAULT]";
char szMsg[BUF_SIZE];

//发送消息给服务端的函数
unsigned WINAPI SendMsg(void* arg)
{
	if (arg == NULL)
	{
		return -1;
	}
	//1. 接收传递过来的参数
	SOCKET hClntSock = *((SOCKET*)arg);
	char szNameMsg[NAME_SIZE + BUF_SIZE];	//又有名字,又有消息

	//循环接收来自于控制台的消息
	while (true)
	{
		fgets(szMsg, BUF_SIZE, stdin);//阻塞在这一句

		//退出机制 当收到q或Q
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n"))
		{
			closesocket(hClntSock);
			exit(0);
		}

		sprintf_s(szNameMsg, "%s %s", szName, szMsg);//字符串拼接
		send(hClntSock, szNameMsg, strlen(szNameMsg), 0);//发送

	}

	return 0;
}

//接收消息给服务端的函数
unsigned WINAPI RecvMsg(void* arg)
{
	if (arg == NULL)
	{
		return -1;
	}
	//1. 接收传递过来的参数
	SOCKET hClntSock = *((SOCKET*)arg);
	char szNameMsg[NAME_SIZE + BUF_SIZE];	//又有名字,又有消息
	int iLen = 0;

	while (true)
	{
		iLen = recv(hClntSock, szNameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		//服务器断开
		if (iLen == -1)
		{
			return -1;
		}
		// szNameMsg 的下标0到iLen-1都是收到的数据 iLen个
		szNameMsg[iLen] = 0;

		//接收到的数据输出到控制台
		fputs(szNameMsg, stdout);
	}
	

	return 0;
}

//带参数的main函数,用命令行启动 在当前目录按下shift + 鼠标右键
int main(int argc, char *argv[]) 
{
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	SOCKET hSock;
	SOCKADDR_IN servAddr;
	HANDLE hSendThread, hRecvThread;

	wVersionRequested = MAKEWORD(1, 1);
	//初始化套接字库
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
	//1. 建立socket
	hSock = socket(AF_INET, SOCK_STREAM, 0);

	//2. 配置地址
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9190);

	//3. 连接服务器
	if (connect(hSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) 
	{
		printf("connect error error code = %d\n", GetLastError());
	}

	//4. 发送服务器的消息 安排一个线程发送消息
	hSendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg,
		(void*)&hSock, 0, NULL);

	//5. 接收服务器的消息 安排一个线程接收消息	
	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg,
		(void*)&hSock, 0, NULL);

	//等待内核对象的信号发生变化
	if (hSendThread != 0)
	{
		WaitForSingleObject(hSendThread, INFINITE);
	}
	if (hRecvThread != 0)
	{
		WaitForSingleObject(hRecvThread, INFINITE);
	}

	
	//6. 关闭套接字
	closesocket(hSock);
	return 0;
}