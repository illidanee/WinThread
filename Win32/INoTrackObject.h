#ifndef __INOTRACKOBJECT_H__
#define __INOTRACKOBJECT_H__

#include <windows.h>



/************************************************************************
	Date:		2016/4/9  
	Time:		9:24
	Author:		Mr.Z
	
	Purpose:	对象接口
				说明：重载了对象的new和delete操作符。
*************************************************************************/
class INoTrackObject
{
/************************************************************************	
	Note:	Base Structure
*************************************************************************/
public:
	INoTrackObject();
	virtual ~INoTrackObject();

	void* operator new(size_t nSize);
	void operator delete(void* p);
	void operator delete[](void* p);
};


#endif
