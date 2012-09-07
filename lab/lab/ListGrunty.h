#if !defined(AFX_LISTGRUNTY_H__270CC112_19D1_44CD_BE16_1861BED2F931__INCLUDED_)
#define AFX_LISTGRUNTY_H__270CC112_19D1_44CD_BE16_1861BED2F931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListGrunty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListGrunty window
#include "LabListView.h"

class CListGrunty : public CLabListView
{
// Construction
public:
	CListGrunty();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListGrunty)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListGrunty();
	void FillCtrlList(CRecordset * pRecordset);
	void DrawDataRow(CRecordset * pRecordset);
	// Generated message map functions
protected:
	//{{AFX_MSG(CListGrunty)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTGRUNTY_H__270CC112_19D1_44CD_BE16_1861BED2F931__INCLUDED_)
