#if !defined(AFX_KTLISTCTRL_H__BA8A1048_F7FA_4863_A6ED_7CA41C08011E__INCLUDED_)
#define AFX_KTLISTCTRL_H__BA8A1048_F7FA_4863_A6ED_7CA41C08011E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KTListCtrl.h : header file
//
#include "EnGeoListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CKTListCtrl window

class CKTList : public CEnGeoListCtrl
{
// Construction
public:
	CKTList();

// Attributes
public:
	virtual void FillCtrlList(CRecordset * pRecordset);
	virtual void DrawDataRow(CRecordset * pRecordset);



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKTList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKTList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CKTList)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KTLISTCTRL_H__BA8A1048_F7FA_4863_A6ED_7CA41C08011E__INCLUDED_)
