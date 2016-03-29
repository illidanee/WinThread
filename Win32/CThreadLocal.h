#ifndef __CTHREADLOCAL_H__
#define __CTHREADLOCAL_H__

#include "IThreadLocal.h"

template<class T>
class CThreadLocal : public IThreadLocal
{
/************************************************************************	
	Note:	生命周期
*************************************************************************/
public:
	operator T*();
	T* operator->();


/************************************************************************	
	Note:	逻辑
*************************************************************************/
public:
	static T* CreateObject();
	T* GetData();
};



/************************************************************************	
	Note:	生命周期
*************************************************************************/
template<class T>
CThreadLocal<T>::operator T*()
{
	return GetData();
}
template<class T>
T* CThreadLocal<T>::operator->()
{
	return GetData();
}


/************************************************************************	
	Note:	逻辑
*************************************************************************/
template<class T>
T* CThreadLocal<T>::CreateObject()
{
	return new T;
}
template<class T>
T* CThreadLocal<T>::GetData() 
{
	return (T*)IThreadLocal::GetData((void* (*)())&CreateObject);
}

#endif