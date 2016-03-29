#ifndef __CSIMPLELIST_H__
#define __CSIMPLELIST_H__

#include "ISimpleList.h"

template<typename T>
class CSimpleList : public ISimpleList 
{
/************************************************************************	
	Note:	生命周期
*************************************************************************/
public:
	CSimpleList(unsigned int nextOffset);
	~CSimpleList();

	operator T();


/************************************************************************	
	Note:	逻辑
*************************************************************************/
public:
	void AddHead(T* p);
	int Remove(T* p);
	T* GetHead() const;
};



/************************************************************************	
	Note:	生命周期
*************************************************************************/
template<typename T>
CSimpleList<T>::CSimpleList(unsigned int nextOffset)
	:
	ISimpleList(nextOffset)
{
}
template<typename T>
CSimpleList<T>::~CSimpleList()
{

}
template<typename T>
CSimpleList<T>::operator T()
{
	return (T*)ISimpleList::GetHead();
}


/************************************************************************	
	Note:	逻辑
*************************************************************************/
template<typename T>
void CSimpleList<T>::AddHead(T* p)
{
	ISimpleList::AddHead((void*)p);
}
template<typename T>
int CSimpleList<T>::Remove(T* p)
{
	return ISimpleList::Remove((void*)p);
}
template<typename T>
T* CSimpleList<T>::GetHead() const
{
	return (T*)ISimpleList::GetHead();
}

#endif