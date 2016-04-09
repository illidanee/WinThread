#ifndef __ISIMPLELIST_H__
#define __ISIMPLELIST_H__



/************************************************************************
	Date:		2016/4/9  
	Time:		9:12
	Author:		Mr.Z
	
	Purpose:	简单链表接口
				说明：本接口只是负责管理对象，并不负责创建和删除对象。
				原则：
				1-外部创建对象。
				2-谁创建谁删除。
*************************************************************************/
class ISimpleList
{
/************************************************************************	
	Note:	Base Structure
*************************************************************************/
private:
	unsigned int m_uiNextOffset;
	void* m_pHead;

public:
	ISimpleList(unsigned int nextOffset);
	virtual ~ISimpleList();


/************************************************************************	
	Note:	Inner Logic
*************************************************************************/
private:
	void** GetNextPtr(void* p) const;


/************************************************************************	
	Note:	Public Interface
*************************************************************************/
public:
	void AddHead(void* p);
	int Remove(void* p);
	void* GetHead() const ;

	int IsEmpty() const;
	void Clear();


};

#endif
