#include "CWinThread.h"





/************************************************************************
	Note:	全局函数接口
*************************************************************************/
CWinThread* BeginThread(TpfThreadPro pFunc, tppThreadParam pParam, LPSECURITY_ATTRIBUTES lpSecurityAttribute, UINT nStackSize, DWORD dwFlag, int priority)
{
	CWinThread* pThread = new CWinThread(pFunc, pParam);
	if (pThread->CreatThread(lpSecurityAttribute, nStackSize, dwFlag | CREATE_SUSPENDED) != 0)
	{
		delete pThread;
		return 0;
	}
	pThread->SetThreadPriority(priority);

	if (!(dwFlag & CREATE_SUSPENDED))
		pThread->ResumeThread();

	return pThread;
}
CWinThread* GetThread()
{
	TagThreadState* pState = GetThreadState();
	return pState->m_pCurrentThread;
}
void EndThread(UINT nExitCode, BOOL bDel)
{
	TagThreadState* pState = GetThreadState();
	CWinThread* pThread = pState->m_pCurrentThread;
	if (pThread)
	{
		if (bDel)
		{
			delete pThread;
			pState->m_pCurrentThread = 0;
		}
	}

	if (IThreadLocal::m_pThreadSlotData)
	{
		IThreadLocal::m_pThreadSlotData->DeleteValues(false);
	}

	InterlockedIncrement(&g_ThreadNum);
	_endthreadex(nExitCode);
}



/************************************************************************
	Note:	线程类
*************************************************************************/
CWinThread::CWinThread(TpfThreadPro pThreadPro, tppThreadParam pThreadParam, bool del)
{
	m_pThreadPro = pThreadPro;
	m_pThreadParam = pThreadParam;
	m_bAutoDel = del;
	m_hThread = 0;
	m_dwThreadID = 0;
}
CWinThread::~CWinThread()
{
	if (m_hThread)
		CloseHandle(m_hThread);

	TagThreadState* pState = GetThreadState();
	if (pState && pState->m_pCurrentThread == this)
		pState->m_pCurrentThread = 0;
}
CWinThread::operator HANDLE()
{
	return this == 0 ? 0 : m_hThread; 
}


UINT __stdcall CWinThread::ThreadEntry(void* pParam)
{
	TagThreadStartUp* pThreadStartUp = (TagThreadStartUp*) pParam;
	CWinThread* pThread = pThreadStartUp->pThread;

	try
	{
		TagThreadState* pState = GetThreadState();
		pState->m_pCurrentThread = pThread;
	}
	catch (...)
	{
		pThreadStartUp->err = true;
		::SetEvent(pThreadStartUp->event1);
		EndThread(-1, FALSE);
	}

	HANDLE hEvent2 = pThreadStartUp->event2;
	::SetEvent(pThreadStartUp->event1);

	::WaitForSingleObject(hEvent2, INFINITE);
	::CloseHandle(hEvent2);

	DWORD nResult = (pThread->m_pThreadPro)(&pThread->m_pThreadParam);

	EndThread(nResult);
	return 0;
}
int CWinThread::CreatThread(LPSECURITY_ATTRIBUTES lpSecurityAttribute, UINT nStackSize, DWORD dwFlag)
{
	TagThreadStartUp startUp;
	startUp.pThread = this;
	startUp.event1 = ::CreateEvent(0, 1, 0, 0);
	startUp.event2 = ::CreateEvent(0, 1, 0, 0);
	startUp.err = false;

	m_hThread = (HANDLE)_beginthreadex(lpSecurityAttribute, nStackSize, ThreadEntry, &startUp, dwFlag | CREATE_SUSPENDED, (UINT*)&m_dwThreadID);
	if (m_hThread == 0)
		return -1;

	::ResumeThread(m_hThread);
	::WaitForSingleObject(startUp.event1, INFINITE);
	::CloseHandle(startUp.event1);

	if (dwFlag & CREATE_SUSPENDED)
		::SuspendThread(m_hThread);

	if (startUp.err)
	{
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = 0;
		::CloseHandle(startUp.event2);
		return -2;
	}

	::SetEvent(startUp.event2);
	return 0;
}

void CWinThread::Delete()
{
	if (m_bAutoDel)
		delete this;
}

int CWinThread::GetThreadPriority()
{
	return ::GetThreadPriority(m_hThread);

}
void CWinThread::SetThreadPriority(int priority)
{
	::SetThreadPriority(m_hThread, priority);
}

DWORD CWinThread::SuspendThread()
{
	return ::SuspendThread(m_hThread);
}
DWORD CWinThread::ResumeThread()
{
	return ::ResumeThread(m_hThread);
}




