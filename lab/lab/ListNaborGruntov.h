#if !defined(AFX_LISTNABORGRUNTOV_H__0830DC76_40F1_4E83_88D3_96E36B8D0FBA__INCLUDED_)
#define AFX_LISTNABORGRUNTOV_H__0830DC76_40F1_4E83_88D3_96E36B8D0FBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListNaborGruntov.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListNaborGruntov window
#include "LabListView.h"

class CListNaborGruntov : public CLabListView
{
// Construction
public:
	CListNaborGruntov();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListNaborGruntov)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListNaborGruntov();
	BOOL OnInitCtrl();
	void FillCtrlList(CRecordset * pRecordset);
	void DrawDataRow(CRecordset * pRecordset);

	// Generated message map functions
protected:
	//{{AFX_MSG(CListNaborGruntov)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTNABORGRUNTOV_H__0830DC76_40F1_4E83_88D3_96E36B8D0FBA__INCLUDED_)
