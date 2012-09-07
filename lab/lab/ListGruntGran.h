#if !defined(AFX_LISTGRUNTGRAN_H__3C45E5A9_7A01_4CF7_8342_CAEABF543CC0__INCLUDED_)
#define AFX_LISTGRUNTGRAN_H__3C45E5A9_7A01_4CF7_8342_CAEABF543CC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListGruntGran.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListGruntGran window
#include "LabListView.h"

class CListGruntGran : public CLabListView
{
// Construction
public:
	CListGruntGran();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListGruntGran)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListGruntGran();
	void FillCtrlList(CRecordset * pRecordset);
	void DrawDataRow(CRecordset * pRecordset);

	// Generated message map functions
protected:
	//{{AFX_MSG(CListGruntGran)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTGRUNTGRAN_H__3C45E5A9_7A01_4CF7_8342_CAEABF543CC0__INCLUDED_)
