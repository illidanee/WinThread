#ifndef __ISIMPLELIST_H__
#define __ISIMPLELIST_H__

class ISimpleList
{
/************************************************************************	
	Note:	生命周期
*************************************************************************/
public:
	ISimpleList(unsigned int nextOffset);
	virtual ~ISimpleList();

private:
	unsigned int m_uiNextOffset;
	void* m_pHead;

/************************************************************************	
	Note:	逻辑
*************************************************************************/
public:
	void AddHead(void* p);
	int Remove(void* p);
	void* GetHead() const ;

	int IsEmpty() const;

private:
	void** GetNextPtr(void* p) const;
};

#endif
