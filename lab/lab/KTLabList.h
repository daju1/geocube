// KTLabList.h: interface for the CKTLabList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KTLABLIST_H__38498300_8D51_43A1_896E_D92354F59DC3__INCLUDED_)
#define AFX_KTLABLIST_H__38498300_8D51_43A1_896E_D92354F59DC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LabListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CKTLabListCtrl window

class CKTLabList : public CLabListCtrl
{
// Construction
public:
	CKTLabList();

// Attributes
public:
	virtual void FillCtrlList(CRecordset * pRecordset);
	virtual void DrawDataRow(CRecordset * pRecordset);



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKTLabList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKTLabList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CKTLabList)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KTLABLIST_H__38498300_8D51_43A1_896E_D92354F59DC3__INCLUDED_)
