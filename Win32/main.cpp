#include <stddef.h>
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <iostream>

#include "CThreadLocal.h"
#include "CWinThread.h"

/************************************************************************
	Note:	È«¾Öº¯Êý
*************************************************************************/
CThreadLocal<TagThreadState> g_ThreadLocal;

TagThreadState* GetThreadState()
{
	return g_ThreadLocal.GetData();
}

UINT MyFunc(void* param)
{
	printf("Thread Identify: %d \n", GetThread()->m_dwThreadID);
	return 0;
}

int main(int argc, char** argv)
{
	printf("Start!\n");
	for (int i = 0; i < 10; ++i)
		BeginThread(MyFunc, 0);
	printf("End! \n");
	return 0;
}

