#if !defined(AFX_LISTGENEZIS_H__EB021B65_4005_431A_BE9C_6C91CEF6BC37__INCLUDED_)
#define AFX_LISTGENEZIS_H__EB021B65_4005_431A_BE9C_6C91CEF6BC37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListGenezis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListGenezis window
#include "LabListView.h"

class CListGenezis : public CLabListView
{
// Construction
public:
	CListGenezis();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListGenezis)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListGenezis();
	void FillCtrlList(CRecordset * pRecordset);
	void DrawDataRow(CRecordset * pRecordset);

	// Generated message map functions
protected:
	//{{AFX_MSG(CListGenezis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTGENEZIS_H__EB021B65_4005_431A_BE9C_6C91CEF6BC37__INCLUDED_)
