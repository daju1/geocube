// OG.h : main header file for the OG application
//

#if !defined(AFX_OG_H__DA052798_4335_4BE3_AD1D_B03C298DC0ED__INCLUDED_)
#define AFX_OG_H__DA052798_4335_4BE3_AD1D_B03C298DC0ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COGApp:
// See OG.cpp for the implementation of this class
//

class COGApp : public CWinApp
{
public:
	COGApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COGApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OG_H__DA052798_4335_4BE3_AD1D_B03C298DC0ED__INCLUDED_)
