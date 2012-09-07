// ex25d.h : main header file for the EX25d application
//

#if !defined(AFX_EX25d_H__A9515B1A_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX25d_H__A9515B1A_5B85_11D0_848F_00400526305B__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx25dApp:
// See ex25d.cpp for the implementation of this class
//

class CEx25dApp : public CWinApp
{
public:
	CEx25dApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25dApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx25dApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25d_H__A9515B1A_5B85_11D0_848F_00400526305B__INCLUDED_)
