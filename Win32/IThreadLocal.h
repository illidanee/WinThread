#ifndef __ITHREADLOCAL_H__
#define __ITHREADLOCAL_H__

#include "CThreadSlotData.h"

class IThreadLocal
{
/************************************************************************	
	Note:	生命周期
*************************************************************************/
public:
	IThreadLocal();
	virtual ~IThreadLocal();

public:
	static CThreadSlotData* m_pThreadSlotData;

	unsigned int m_uiSlot;


/************************************************************************	
	Note:	逻辑
*************************************************************************/
public:
	void* GetData(void* (*pFunc)());
};

#endif
