// MessageItem.h: interface for the CMessageItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEITEM_H__56D40E3E_9B18_4C13_B123_2517F9725EFD__INCLUDED_)
#define AFX_MESSAGEITEM_H__56D40E3E_9B18_4C13_B123_2517F9725EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessageItem
{
public:
	CMessageItem*	next;

	size_t			n;

	void*			msg_data;

	CMessageItem(void* msg, size_t size);
	~CMessageItem(void);
};
#endif // !defined(AFX_MESSAGEITEM_H__56D40E3E_9B18_4C13_B123_2517F9725EFD__INCLUDED_)
