// RoomQueueItem.h: interface for the CRoomQueueItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROOMQUEUEITEM_H__F4E87F32_7EE5_45AB_A2FD_61E44ED83FCF__INCLUDED_)
#define AFX_ROOMQUEUEITEM_H__F4E87F32_7EE5_45AB_A2FD_61E44ED83FCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MessageItem.h"

class CRoomQueueItem
{
public:
	bool empty();
	void OnDestroy();
	void DeleteAll();
	unsigned long	count;
	unsigned long	max_count;
	bool			start;

	CRITICAL_SECTION CriticalSection;

	CMessageItem*	first;
	CMessageItem*	last;

	CRoomQueueItem(/*CATLCameraOb*	pCtrl*/);
	~CRoomQueueItem(void);
	HANDLE  hEventWrote;

	int AddMsg(void* msg, size_t size);
	bool ReadNext(CMessageItem* & current);
	bool Copy(void *dest,long bufferLen);
	bool Delete();
};

#endif // !defined(AFX_ROOMQUEUEITEM_H__F4E87F32_7EE5_45AB_A2FD_61E44ED83FCF__INCLUDED_)
