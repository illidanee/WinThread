#include "INoTrackObject.h"

#include <windows.h>

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