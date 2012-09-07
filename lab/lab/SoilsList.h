#if !defined(AFX_SOILSLIST_H__48C6BCD5_6EFA_4099_A601_82CF7F1DC76E__INCLUDED_)
#define AFX_SOILSLIST_H__48C6BCD5_6EFA_4099_A601_82CF7F1DC76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoilsList.h : header file
//
#include "EnGeoListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSoilsList window

class CSoilsList : public CEnGeoListCtrl
{
// Construction
public:
	CSoilsList();

// Attributes
public:
	virtual void FillCtrlList(CRecordset * pRecordset);
	virtual void DrawDataRow(CRecordset * pRecordset);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoilsList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoilsList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSoilsList)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLaboratoryGranularLoadform();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOILSLIST_H__48C6BCD5_6EFA_4099_A601_82CF7F1DC76E__INCLUDED_)
