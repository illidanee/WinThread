#ifndef __CTHREADSLOTDATA_H__
#define __CTHREADSLOTDATA_H__

#include "CSimpleList.h"
#include <stddef.h>
#include <windows.h>

#define SLOTSTATE_

struct TagThreadData
{
	TagThreadData* pNext;
	unsigned int uiCount;
	void** pData;
};

struct TagSlotData
{
	unsigned int uiState;
};

class CThreadSlotData
{
/************************************************************************	
	Note:	生命周期
*************************************************************************/
	TagSlotData* m_pSlotData;
	unsigned int m_uiMax;
	unsigned int m_uiIndex;

	CSimpleList<TagThreadData>* m_pList;

	unsigned long m_tlsIndex;

	CRITICAL_SECTION m_cs;

public:
	CThreadSlotData();
	virtual ~CThreadSlotData();

	void* operator new(size_t, void* q);
	void operator delete(void* p, void* q);
	void operator delete[](void* p, void* q);
/************************************************************************	
	Note:	逻辑
*************************************************************************/
public:
	void Init();
	void Destory();

	unsigned int AllocSlot();
	void FreeSlot(unsigned int uiSlot);

	void SetValue(unsigned int uiSlot, void* pValue);
	void* GetValue(unsigned int uiSlot);

	void DeleteValues(bool bAll);
	void DeleteValues(TagThreadData* pThreadData);
};

#endif
