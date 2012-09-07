#if !defined(AFX_DATABASETALBLESLIST_H__9BA020AE_2FCF_46E5_AEC8_D944E3EFD1B9__INCLUDED_)
#define AFX_DATABASETALBLESLIST_H__9BA020AE_2FCF_46E5_AEC8_D944E3EFD1B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataBaseTalblesList.h : header file
//
#include "EnGeoListCtrl.h"

#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDataBaseTalblesList window
class CDataBaseTalblesList : public CEnGeoListCtrl
{
// Construction
public:
	CDataBaseTalblesList();

	vector<CString> names;

// Attributes
public:

// Operations
public:
	virtual void FillListCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataBaseTalblesList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataBaseTalblesList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataBaseTalblesList)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASETALBLESLIST_H__9BA020AE_2FCF_46E5_AEC8_D944E3EFD1B9__INCLUDED_)
