#include "ISimpleList.h"

ISimpleList::ISimpleList(unsigned int nextOffset)
{
	m_uiNextOffset = nextOffset;
	m_pHead = 0;
}
ISimpleList::~ISimpleList()
{

}

int ISimpleList::IsEmpty() const
{
	return m_pHead == 0;
}
void ISimpleList::AddHead(void* p)
{
	*GetNextPtr(p) = m_pHead;
	m_pHead = p;
}
int ISimpleList::Remove(void* p)
{
	if (p == 0)
		return -2;

	if (p == m_pHead)
	{
		m_pHead = *GetNextPtr(p);
		return 0;
	}
	else
	{
		void* pTemp = m_pHead;
		while (pTemp != 0 && *GetNextPtr(pTemp) != p)
			pTemp = *GetNextPtr(pTemp);

		if (pTemp != 0)
		{
			*GetNextPtr(pTemp) = *GetNextPtr(p);
			return 1;
		}
	}
	return -1;
}
void* ISimpleList::GetHead() const
{
	return m_pHead;
}
void** ISimpleList::GetNextPtr(void* p) const
{
	return (void**)((char*)p + m_uiNextOffset);
}




