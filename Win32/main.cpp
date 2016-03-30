#include <stddef.h>
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <iostream>

#include "CThreadLocal.h"
#include "CWinThread.h"

/************************************************************************
	Note:	全局函数
*************************************************************************/
//保证IThreadLocal中的静态变量在g_ThreadLocal之前初始化
static IThreadLocal g_ExternThreadLocal;
CThreadLocal<TagThreadState> g_ThreadLocal;

TagThreadState* GetThreadState()
{
	return g_ThreadLocal.GetData();
}

long g_ThreadNum = 0;

UINT MyFunc(void* param)
{
	printf("Thread Identify: %d \n", GetThread()->m_dwThreadID);
	return 0;
}

int main(int argc, char** argv)
{
	for (int i = 0; i < 3; ++i)
		BeginThread(MyFunc, 0);
	
	while(g_ThreadNum != 3)
		Sleep(1);
	
	return 0;
}


//#include <stddef.h>
//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//
//#include "INoTrackObject.h"
//#include "CThreadLocal.h"
//
//CRITICAL_SECTION g_ms;
//
//struct TagMyThreadData : public INoTrackObject
//{
//	int data;
//};
//
//CThreadLocal<TagMyThreadData> g_threadLocal;
//
//UINT __stdcall ThreadFunc(void* p)
//{
//
//	g_threadLocal->data = *(int*)p;
//	LeaveCriticalSection(&g_ms);
//	Sleep(2000);
//	printf("OrderID: %d, Thread ID: %-5d, d = %d \n", (int)p, GetCurrentThreadId(), g_threadLocal->data);
//	
//	delete p;
//	return 0;
//}
//
//int main(int argc, char** argv)
//{
//	InitializeCriticalSection(&g_ms);
//
//	int* arr[10];
//
//	static int num = 10;
//	HANDLE h[10];
//	unsigned int id;
//	for (int i = 0; i < num; ++i)
//	{
//		EnterCriticalSection(&g_ms);
//		arr[i] = new int(i);
//		h[i] = (HANDLE *)::_beginthreadex(NULL, 0, ThreadFunc, (void*)arr[i],0, &id);
//	}
//	//WaitForMultipleObjects(num, h, TRUE, INFINITE);
//
//	//for (int i = 0; i < num; ++i)
//	//	CloseHandle(h[i]);
//
//	DeleteCriticalSection(&g_ms);
//	system("pause");
//	return 0;
//}
