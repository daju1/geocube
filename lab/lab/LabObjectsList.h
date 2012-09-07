#if !defined(AFX_LABOBJECTSLIST_H__AD1FD54A_9E73_4FC3_8947_3B9D43F84FA8__INCLUDED_)
#define AFX_LABOBJECTSLIST_H__AD1FD54A_9E73_4FC3_8947_3B9D43F84FA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnGeoObjectsList.h : header file
//
#include "LabListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CLabObjectsList window

class CLabObjectsList : public CLabListCtrl
{
	friend class CLabView;
// Construction
public:
	CLabObjectsList();

// Attributes
public:
// Operations
public:
//	BOOL OnInitCtrl();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabObjectsList)
	protected:
	protected:
	//}}AFX_VIRTUAL

public:
	virtual void FillCtrlList(CRecordset * pRecordset);
	virtual void DrawDataRow(CRecordset * pRecordset);

// Implementation
public:
	virtual ~CLabObjectsList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLabObjectsList)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.





#endif // !defined(AFX_LABOBJECTSLIST_H__AD1FD54A_9E73_4FC3_8947_3B9D43F84FA8__INCLUDED_)
