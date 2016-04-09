#include "INoTrackObject.h"



/************************************************************************	
	Note:	Base Structure
*************************************************************************/
INoTrackObject::INoTrackObject()
{

}
INoTrackObject::~INoTrackObject()
{

}

void* INoTrackObject::operator new(size_t nSize)
{
	return malloc(nSize);
}
void INoTrackObject::operator delete(void* p)
{
	free(p);
}
void INoTrackObject::operator delete[](void* p)
{
	free(p);
}