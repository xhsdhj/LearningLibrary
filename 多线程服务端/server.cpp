#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

#define MAX_CLNT 256
#define MAX_BUF_SIZE 256

using namespace std;

//全局变量
SOCKET clntSocks[MAX_CLNT];	//所有的连接的客户端socket
HANDLE hMutex;				//互斥体
int clntCnt = 0;			//当前连接数

//发送给所有的客户端
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

//处理客户端的函数
unsigned WINAPI HandleCln(void* arg) 
{
	if (arg == NULL)
	{
		return -1;
	}
	//1. 接收传递过来的参数
	SOCKET hClntSock = *((SOCKET*)arg);
	int iLen = 0, i = 0;
	char szMsg[MAX_BUF_SIZE] = { 0 };

	//2. 进行数据的收发 循环接收
// 	while ((iLen = recv(hClntSock, szMsg, sizeof(szMsg), 0)) != 0)
// 	{
// 		//收到的数据立马发给所有客户端
// 		SendMsg(szMsg, iLen);
// 	}

	while (true)
	{
		iLen = recv(hClntSock, szMsg, sizeof(szMsg), 0);
		//printf("recv msg = %s, iLen = %d\n", szMsg, iLen);
		if (iLen != -1)
		{
			//收到的数据立马发给所有客户端
			SendMsg(szMsg, iLen);
		}
		else 
		{
			break;
		}
	}
	printf("此时连接数目 %d\n", clntCnt);
	//3. 某个连接断开, 需要处理断开的连接
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)
	{
		if (hClntSock == clntSocks[i])
		{
			//移位
			while (i++ < clntCnt)
			{
				clntSocks[i] = clntSocks[i + 1];
			}
			break;
		}
	}
	clntCnt--;
	printf("断开连接后, 此时连接数目 %d\n", clntCnt);
	ReleaseMutex(hMutex);
	closesocket(hClntSock);
	return 0;
}


int main() {
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	HANDLE hThread;

	wVersionRequested = MAKEWORD(1, 1);
	//初始化套接字库
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

	//创建互斥对象
	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (hMutex == 0)	//如果互斥体等于零 表示创建互斥对象失败
	{
		return -1;
	}

	//新建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(9190);

	//绑定套接字到本地IP地址,端口号 9190
	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == SOCKET_ERROR) 
	{
		printf("bind error num = %d\n", GetLastError());
		return -1;
	}

	//开始监听
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
		//接收客户连接
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrCli, &len);
		//每来一个连接, 全局数组应该加一个成员,最大连接数加一
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = sockConn;
		ReleaseMutex(hMutex);
		//每来一个连接,服务器起一个线程 维护客户端连接
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleCln,
			(void*)&sockConn, 0, NULL);
		printf("Connect client IP: %s\n", inet_ntoa(addrCli.sin_addr));
		printf("Connect client num: %d\n", clntCnt);
	}

	closesocket(sockSrv);
	WSACleanup();
	return 0;
}