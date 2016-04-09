#include "IThreadLocal.h"

static char threadSlotDataBuff[sizeof(CThreadSlotData)] = {};

CThreadSlotData* IThreadLocal::m_pThreadSlotData = new(threadSlotDataBuff)CThreadSlotData;

IThreadLocal::IThreadLocal()
{
	 m_pThreadSlotData->AllocSlot(&m_uiSlot);
}

IThreadLocal::~IThreadLocal()
{
	m_pThreadSlotData->FreeSlot(m_uiSlot);
	m_uiSlot = 0;
}




void* IThreadLocal::GetData(void* (*pFunc)())
{
	void* pValue = (void*)m_pThreadSlotData->GetValue(m_uiSlot);
	if (pValue == 0)
	{
		pValue = (*pFunc)();
		m_pThreadSlotData->SetValue(m_uiSlot, pValue);
	}
	return pValue;
}