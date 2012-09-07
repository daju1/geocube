// mailwriter.h : main header file for the MAILWRITER application
//

#if !defined(AFX_MAILWRITER_H__65A1BD90_C8BC_49A0_A76B_2B6D8773A1E5__INCLUDED_)
#define AFX_MAILWRITER_H__65A1BD90_C8BC_49A0_A76B_2B6D8773A1E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMailwriterApp:
// See mailwriter.cpp for the implementation of this class
//

class CMailwriterApp : public CWinApp
{
public:
	CMailwriterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailwriterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMailwriterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILWRITER_H__65A1BD90_C8BC_49A0_A76B_2B6D8773A1E5__INCLUDED_)
