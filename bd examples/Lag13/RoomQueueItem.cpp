// RoomQueueItem.cpp: implementation of the CRoomQueueItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphs.h"
#include "RoomQueueItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoomQueueItem::CRoomQueueItem(/*CATLCameraOb*	pCtrl*/)
{
//	m_pCtrl			= pCtrl;
	this->first		= NULL;
	this->last		= NULL;

	this->max_count	= 1000;
	this->count		= 0;
	this->start		= FALSE;
	// событие - "записан" - несигнальное
	hEventWrote = CreateEvent( NULL, 
		TRUE, 
		FALSE, 
		"Wrote At Least One Message Item");

	// Initialize the critical section one time only.
    InitializeCriticalSection(&CriticalSection); 
}

CRoomQueueItem::~CRoomQueueItem(void)
{
}

int CRoomQueueItem::AddMsg(void* msg, size_t size)
{
	int retCount;
//	if (m_pCtrl->m_bFirstReceive)
//		return;
	CMessageItem* pnew;

    EnterCriticalSection(&CriticalSection);

//	if(this->count < max_count)
//	{
		pnew = new CMessageItem(msg, size);
		if(!pnew)
		{
			LeaveCriticalSection(&CriticalSection);
			return -1;
		}

		// Critical section
		if(this->first == NULL)
		{
			this->first				= pnew;
			this->last				= pnew;
		}
		else
		{
			if(this->last)
			{
				this->last->next	= pnew;
				this->last			= this->last->next;
			}
		}
		retCount = int(++count);
#ifdef RAPORT
		TCHAR buf[64];
		wsprintf(buf,"CRoomQueueItem::AddMsg count = %d \n", (int)count);
		raport.Write3(buf);
#endif
		// End section
		// Release ownership of the critical section.
//	}
//	else
//		MessageBox(NULL, "max", "Add", MB_OK);

    LeaveCriticalSection(&CriticalSection);
	if (count > 0)
		SetEvent(hEventWrote);
 	return retCount;
}

bool CRoomQueueItem::ReadNext(CMessageItem* & current)
{
	if(current == NULL) return false;

	if(current->next)
	{
		current = current->next;
		return true;
	}

	return false;
}


bool CRoomQueueItem::Copy(void *dest,long bufferLen)
{
	if (WAIT_OBJECT_0 == WaitForSingleObject( hEventWrote, 5000))
	{
		ResetEvent(hEventWrote);
		if( (this->first == NULL) || (!this->start) )
		{
			ZeroMemory(dest, bufferLen);
			if(this->count>1) this->start = true;
			return false;
		}
		else
		{
			CopyMemory(dest, this->first->msg_data, bufferLen);	
			this->Delete();
			return true;
		}
	}
	return false;
}

bool CRoomQueueItem::Delete()
{
	CMessageItem*	pold;

	if(this->first == NULL) return false;

	pold = this->first;
	
	if(this->ReadNext(this->first))
	{
		EnterCriticalSection(&CriticalSection);
		this->count--;
		if (pold) delete pold;
		LeaveCriticalSection(&CriticalSection);
		if (count > 0)
			SetEvent(hEventWrote);
	}
	else
	{
		EnterCriticalSection(&CriticalSection);
		this->first = NULL;
		this->last  = NULL;
		this->count--;

		if (pold) delete pold;
		LeaveCriticalSection(&CriticalSection);
		if (count > 0)
			SetEvent(hEventWrote);
		return false;
	}

#ifdef RAPORT
		TCHAR buf[64];
		wsprintf(buf,"CRoomQueueItem::Delete count = %d \n", (int)count);
		raport.Write3(m_pCtrl->m_n, buf);
#endif

	return true;
}

void CRoomQueueItem::DeleteAll()
{
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() Begin\n");
#endif
	EnterCriticalSection(&CriticalSection);
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() EnterCriticalSection\n");
#endif
	if (WAIT_OBJECT_0 == WaitForSingleObject( hEventWrote, 100))
	{
		ResetEvent(hEventWrote);
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() WaitForSingleObject\n");
#endif
		CMessageItem*	pold;

		ResetEvent(hEventWrote);

		while(this->first != NULL) 
		{
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() while\n");
#endif
			pold = this->first;
			
			if(this->ReadNext(this->first))
			{
				this->count--;
			}
			else
			{
				this->first = NULL;
				this->last  = NULL;
				this->count--;
			}
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() before delete pold\n");
#endif
			if (pold)
				delete pold;
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() after delete pold\n");
#endif
		}
		this->first		= NULL;
		this->last		= NULL;

		this->max_count	= 1000;
		this->count		= 0;
		this->start		= FALSE;
	}
	LeaveCriticalSection(&CriticalSection);
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::DeleteAll() End\n");
#endif
}

void CRoomQueueItem::OnDestroy()
{
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::OnDestroy() Begin(output_data)\n");
#endif
	// Release resources used by the critical section object.
    DeleteCriticalSection(&CriticalSection);
#ifdef RAPORT
	raport.Write3(m_pCtrl->m_n, "CRoomQueueItem::OnDestroy() End(output_data)\n");
#endif

}


bool CRoomQueueItem::empty()
{
	bool answer;
	EnterCriticalSection(&CriticalSection);
	answer = count == 0;
	LeaveCriticalSection(&CriticalSection);
	return answer;

}
