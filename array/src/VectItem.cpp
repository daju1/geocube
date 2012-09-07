// VectItem.cpp: implementation of the CVectItem class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if VECTITEM_IN_TWO_FILES

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#pragma once
//#include "StdAfx.h"
//#include "messageitem.h"
//#include "stdio.h"
template <class T>
CVectItem<T>::CVectItem(T* msg, size_t size, int _index, bool useDestructor)
{
	m_useDestructor = useDestructor;
	this->n		= size;
	index = _index;
	
	this->msg_data = (T*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, this->n);
#if 0
	memcpy(this->msg_data, msg, this->n);
#else
	for (size_t i = 0; i < size/sizeof(T); i ++)
	{
		msg_data[i] = msg[i];
	}
#endif
	this->next = NULL;
	this->pre  = NULL;
}

template <class T>
CVectItem<T>::CVectItem(size_t size, int _index, bool useDestructor)
{
	m_useDestructor = useDestructor;
	this->n		= size;
	index = _index;
	
	this->msg_data = (T*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, this->n);
	//memcpy(this->msg_data, msg, this->n);
	this->next = NULL;
	this->pre  = NULL;
}

template <class T>
CVectItem<T>::~CVectItem(void)
{
	if(this->msg_data && m_useDestructor)
	{
		for (size_t i = 0; i < this->n/sizeof(T); i ++)
		{
		MessageBox(0, "this->msg_data->~T()", "~CVectItem(void)", 0);
//			(reinterpret_cast<T*>(msg_data))[i].~T();
//			(reinterpret_cast<T*>(msg_data))[i].OnDestroy();
		}
	}
	if(this->msg_data) HeapFree(GetProcessHeap(), 0, this->msg_data);
}

template <class T>
int CVectItem<T>::GetIndex()
{
	return index;
}
#endif /*VECTITEM_IN_TWO_FILES*/

