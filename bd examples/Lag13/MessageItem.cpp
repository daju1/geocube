// MessageItem.cpp: implementation of the CMessageItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphs.h"
#include "MessageItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#pragma once
//#include "StdAfx.h"
//#include "messageitem.h"
//#include "stdio.h"
CMessageItem::CMessageItem(void* msg, size_t size)
{
	this->n		= size;
	
	this->msg_data = (XYZ*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, this->n);
	memcpy(this->msg_data, msg, this->n);
	this->next = NULL;
}

CMessageItem::~CMessageItem(void)
{
	if(this->msg_data) HeapFree(GetProcessHeap(), 0, this->msg_data);
}
