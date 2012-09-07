// LabListCtrl.h: interface for the CLabListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABLISTCTRL_H__3912F2DA_6626_4F12_9A65_8C04DDDF3867__INCLUDED_)
#define AFX_LABLISTCTRL_H__3912F2DA_6626_4F12_9A65_8C04DDDF3867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyListCtrl.h"

class CLaboratoryView;
class CLabListCtrl : public CMyListCtrl  
{
public:
	CLaboratoryView * m_lab_view;

	CLabListCtrl();
	virtual ~CLabListCtrl();

};

#endif // !defined(AFX_LABLISTCTRL_H__3912F2DA_6626_4F12_9A65_8C04DDDF3867__INCLUDED_)
