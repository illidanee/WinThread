#ifndef __INOTRACKOBJECT_H__
#define __INOTRACKOBJECT_H__

class INoTrackObject
{
/************************************************************************	
	Note:	生命周期
*************************************************************************/
public:
	INoTrackObject();
	virtual ~INoTrackObject();

	void* operator new(size_t nSize);
	void operator delete(void* p);
};


#endif
