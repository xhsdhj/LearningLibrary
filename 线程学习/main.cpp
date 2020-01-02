#include <stdio.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex;

unsigned int WINAPI ThreadFun(LPVOID p)
{
	int cnt = 1;
	int cnt1 = 0;
	if (p != NULL)
	{
		cnt = *((int*)p);
	}
	WaitForSingleObject(hMutex, INFINITE);
	puts("��ʼ");
	for (int i = 0; i < cnt; i++)
	{
		Sleep(1000);
		printf("cnt = %d\n", cnt1 += i);
	}
	puts("����");
	ReleaseMutex(hMutex);
	return 0;
}

int main()
{
	HANDLE hThread[5];

	unsigned int threadID;
	int iparam = 5;
	DWORD wr;
	hMutex = CreateMutex(NULL, FALSE, NULL);
	for (int i=0;i<5;i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, &iparam, 0, &threadID);
	}
	
	
	if (hThread == NULL)
	{
		puts("_beginthreadex ����");
		return -1;
	}

	printf("WaitForSingleObject ��ʼ\n");
	if ((wr = WaitForMultipleObjects(5, hThread, TRUE, INFINITE)) == WAIT_FAILED)
	{
		puts("error");
		return -1;
	}
	printf("WaitForSingleObject ����\n");
	if (hMutex)
	{
		CloseHandle(hMutex);
	}
	
	system("pause");
	return 0;
}