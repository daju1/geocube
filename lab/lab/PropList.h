#if !defined(AFX_PROPLIST_H__EBD1175D_D939_4D34_B3C9_99A66E3232E1__INCLUDED_)
#define AFX_PROPLIST_H__EBD1175D_D939_4D34_B3C9_99A66E3232E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropList.h : header file
//
#include "EnGeoListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPropList window

class CPropList : public CEnGeoListCtrl
{
// Construction
public:
	CPropList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPLIST_H__EBD1175D_D939_4D34_B3C9_99A66E3232E1__INCLUDED_)
