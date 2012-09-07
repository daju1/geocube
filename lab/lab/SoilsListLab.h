#if !defined(AFX_SoilsListLabLAB_H__48C6BCD5_6EFA_4099_A601_82CF7F1DC76E__INCLUDED_)
#define AFX_SoilsListLabLAB_H__48C6BCD5_6EFA_4099_A601_82CF7F1DC76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoilsListLab.h : header file
//
#include "LabListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSoilsListLab window

class CSoilsListLab : public CLabListCtrl
{
// Construction
public:
	CSoilsListLab();

// Attributes
public:
	virtual void FillCtrlList(CRecordset * pRecordset);
	virtual void DrawDataRow(CRecordset * pRecordset);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoilsListLab)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoilsListLab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSoilsListLab)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SoilsListLabLAB_H__48C6BCD5_6EFA_4099_A601_82CF7F1DC76E__INCLUDED_)
