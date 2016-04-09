#ifndef __CTHREADSLOTDATA_H__
#define __CTHREADSLOTDATA_H__

#include <stddef.h>
#include <windows.h>
#include "CSimpleList.h"



/************************************************************************	
	Note:	TagThreadData
*************************************************************************/
struct TagThreadData
{
	TagThreadData* pNext;
	unsigned int uiCount;
	void** pData;
};



/************************************************************************	
	Note:	TagSlotData
*************************************************************************/
struct TagSlotData
{
	unsigned int uiState;
};



/************************************************************************
	Date:		2016/4/9  
	Time:		9:38
	Author:		Mr.Z
	
	Purpose:	管理线程数据
*************************************************************************/
class CThreadSlotData
{
/************************************************************************	
	Note:	Base Structure
*************************************************************************/
private:
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
	Note:	Public Interface
*************************************************************************/
public:
	void Init();
	void Destory();

	void AllocSlot(unsigned int* puiSlot);
	void FreeSlot(unsigned int uiSlot);

	void SetValue(unsigned int uiSlot, void* pValue);
	void* GetValue(unsigned int uiSlot);

	void DeleteValues(bool bAll);
	void DeleteValues(TagThreadData* pThreadData);
};

#endif
