#include "CThreadSlotData.h"

CThreadSlotData::CThreadSlotData()
{
	m_pSlotData = 0;
	m_uiMax = 0;
	m_uiIndex = 0;		//0保留
	
	m_pList = 0;
	
	m_tlsIndex = 0;

	Init();
}
CThreadSlotData::~CThreadSlotData()
{
	Destory();
}
void* CThreadSlotData::operator new(size_t, void* q)
{
	return q;
}
void CThreadSlotData::operator delete(void* p, void* q)
{
	p = 0;
}
void CThreadSlotData::operator delete[](void* p, void* q)
{
	p = 0;
}
void CThreadSlotData::Init()
{
	m_pList = new CSimpleList<TagThreadData>(offsetof(TagThreadData, pNext));

	m_tlsIndex = TlsAlloc();

	InitializeCriticalSection(&m_cs);
}
void CThreadSlotData::Destory()
{
	TagThreadData* pTempList = m_pList->GetHead();
	while (pTempList)
	{
		TagThreadData* pNext = pTempList->pNext;
		delete pTempList;
		pTempList = pNext;
	}
	delete m_pList;

	TlsFree(m_tlsIndex);
	
	DeleteCriticalSection(&m_cs);
}


unsigned int CThreadSlotData::AllocSlot()
{
	EnterCriticalSection(&m_cs);

	++m_uiIndex;

	if (m_uiIndex >= m_uiMax || m_pSlotData[m_uiIndex].uiState == 1)
	{
		for (m_uiIndex = 1; m_uiIndex < m_uiMax && m_pSlotData[m_uiIndex].uiState == 1; ++m_uiIndex)
		{
			;
		}

		if (m_uiIndex >= m_uiMax)
		{
			unsigned int uiNewMax = m_uiMax + 32;

			if (m_pSlotData == 0)
			{
				m_pSlotData = (TagSlotData*)malloc(uiNewMax * sizeof(TagSlotData));
			}
			else
			{
				TagSlotData* pTempSlotData = (TagSlotData*)realloc(m_pSlotData, uiNewMax * sizeof(TagSlotData));
				m_pSlotData = pTempSlotData;
			}

			memset(m_pSlotData + m_uiMax, 0, (uiNewMax - m_uiMax) * sizeof(TagSlotData));
			
			m_uiMax = uiNewMax;
		}
	}

	m_pSlotData[m_uiIndex].uiState = 1;

	LeaveCriticalSection(&m_cs);

	return m_uiIndex;
}

void CThreadSlotData::FreeSlot(unsigned int uiSlot)
{
	EnterCriticalSection(&m_cs);

	TagThreadData* pData = m_pList->GetHead();
	while (pData)
	{
		if (uiSlot < pData->uiCount)
		{
			delete pData->pData[uiSlot];
			pData->pData[uiSlot] = 0;
		}
		pData = pData->pNext;
	}
	
	m_pSlotData[uiSlot].uiState = 0;

	LeaveCriticalSection(&m_cs);
}

void CThreadSlotData::SetValue(unsigned int uiSlot, void* pValue)
{
	TagThreadData* pThreadData = (TagThreadData*)TlsGetValue(m_tlsIndex);

	if (pThreadData == 0)
	{
		pThreadData = new TagThreadData();
		pThreadData->uiCount = 0;
		pThreadData->pData = 0;


		EnterCriticalSection(&m_cs);
		m_pList->AddHead(pThreadData);
		LeaveCriticalSection(&m_cs);

		TlsSetValue(m_tlsIndex, pThreadData);
	}

	if (pThreadData->pData == 0)
	{
		pThreadData->pData = (void**)malloc(m_uiMax * sizeof(void*));
		memset(pThreadData->pData, 0, m_uiMax * sizeof(void*));
		pThreadData->uiCount = m_uiMax;
	}
	else if (pThreadData->uiCount <= uiSlot)
	{
		pThreadData->pData = (void**)realloc(pThreadData->pData, m_uiMax * sizeof(void*));
		memset(pThreadData->pData + pThreadData->uiCount, 0, (m_uiMax - pThreadData->uiCount) * sizeof(void*));
		pThreadData->uiCount = m_uiMax;
	}

	pThreadData->pData[uiSlot] = pValue;
}

void* CThreadSlotData::GetValue(unsigned int uiSlot)
{
	TagThreadData* pThreadData = (TagThreadData*)TlsGetValue(m_tlsIndex);

	if (pThreadData == 0 || uiSlot >= pThreadData->uiCount)
		return 0;

	return pThreadData->pData[uiSlot];
}

void CThreadSlotData::DeleteValues(bool bAll)
{
	if (bAll)
	{
		TagThreadData* pThreadData = m_pList->GetHead();
		while (pThreadData)
		{
			TagThreadData* pNext = pThreadData->pNext;
			DeleteValues(pThreadData);
			pThreadData = pNext;
		}
	}
	else
	{
		TagThreadData* pThreadData = (TagThreadData*)TlsGetValue(m_tlsIndex);
		if (pThreadData)
			DeleteValues(pThreadData);
	}
}

void CThreadSlotData::DeleteValues(TagThreadData* pThreadData)
{
	if (pThreadData == 0)
		return;
	
	for (unsigned int i = 1; i < pThreadData->uiCount; ++i)
	{
		delete pThreadData->pData[i];
		pThreadData->pData[i] = 0;
	}

	EnterCriticalSection(&m_cs);

	m_pList->Remove(pThreadData);
	
	LeaveCriticalSection(&m_cs);

	free(pThreadData->pData);
	delete pThreadData;
	pThreadData = 0;
	TlsSetValue(m_tlsIndex, 0);
}









