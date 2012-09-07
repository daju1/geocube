// EnGeoListCtrl.h: interface for the CEnGeoListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGEOLISTCTRL_H__53F9A007_07F6_487C_820F_7D9880B62FD3__INCLUDED_)
#define AFX_ENGEOLISTCTRL_H__53F9A007_07F6_487C_820F_7D9880B62FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyListCtrl.h"

class CEnGeologyView;
class CEnGeoListCtrl : public CMyListCtrl  
{
public:
	CEnGeologyView * m_geo_view;

	CEnGeoListCtrl();
	virtual ~CEnGeoListCtrl();

};

#endif // !defined(AFX_ENGEOLISTCTRL_H__53F9A007_07F6_487C_820F_7D9880B62FD3__INCLUDED_)
