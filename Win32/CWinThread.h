#ifndef __CWINTHREAD_H__
#define __CWINTHREAD_H__

#include <windows.h>
#include <process.h>

#include "CThreadLocal.h"



/************************************************************************
	Note:	��������
*************************************************************************/
typedef UINT (__cdecl* TpfThreadPro)(void*);
typedef void* tppThreadParam;



/************************************************************************
	Note:	ȫ�ֺ���
*************************************************************************/
struct TagThreadState;
extern TagThreadState* GetThreadState();
extern long  g_ThreadNum;


/************************************************************************
	Note:	ȫ�ֺ����ӿ�
*************************************************************************/
class CWinThread;
struct TagThreadStartUp
{
	CWinThread* pThread;
	HANDLE event1;
	HANDLE event2;
	bool err;
};

CWinThread* BeginThread(TpfThreadPro pFunc, tppThreadParam pParam, LPSECURITY_ATTRIBUTES lpSecurityAttribute = 0, UINT nStackSize = 0, DWORD dwFlag = 0, int priority = THREAD_PRIORITY_NORMAL);
CWinThread* GetThread();
void EndThread(UINT nExitCode, BOOL bDel = TRUE);



/************************************************************************
	Note:	�߳�״̬
*************************************************************************/
struct TagThreadState
{
	CWinThread* m_pCurrentThread;
};



/************************************************************************
	Note:	�߳���
*************************************************************************/
class CWinThread
{
/************************************************************************	
	Note:	�����������������
*************************************************************************/
public:
	TpfThreadPro m_pThreadPro;
	tppThreadParam m_pThreadParam;
	bool m_bAutoDel;
	HANDLE m_hThread;
	DWORD m_dwThreadID;

public:
	CWinThread(TpfThreadPro pThreadPro, tppThreadParam pThreadParam, bool del = true);
	virtual ~CWinThread();

	operator HANDLE();


/************************************************************************
	Note:	��������
*************************************************************************/
private:
	static UINT __stdcall ThreadEntry(void* pParam);
public:
	int CreatThread(LPSECURITY_ATTRIBUTES lpSecurityAttribute, UINT nStackSize, DWORD dwFlag);
	void Delete();
	

/************************************************************************	
	Note:	�߼�
*************************************************************************/
public:
	int GetThreadPriority();
	void SetThreadPriority(int priority);

	DWORD SuspendThread();
	DWORD ResumeThread();
};


#endif