// ex31b.h : main header file for the EX31B application
//

#if !defined(AFX_EX31B_H__A0805530_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
#define AFX_EX31B_H__A0805530_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx31bApp:
// See ex31b.cpp for the implementation of this class
//

class CEx31bApp : public CWinApp
{
public:
	CEx31bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx31bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31B_H__A0805530_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
