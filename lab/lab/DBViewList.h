#if !defined(AFX_DBVIEWLIST_H__3EC3426C_8923_477E_8921_A147EA8F8BDD__INCLUDED_)
#define AFX_DBVIEWLIST_H__3EC3426C_8923_477E_8921_A147EA8F8BDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBViewList.h : header file
//
#include "EnGeoListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDBViewList window

class CDBViewList : public CEnGeoListCtrl
{
// Construction
public:
	CDBViewList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBViewList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDBViewList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBViewList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBVIEWLIST_H__3EC3426C_8923_477E_8921_A147EA8F8BDD__INCLUDED_)
