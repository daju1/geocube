// mfcGeneric.h : main header file for the MFCGENERIC application
//

#if !defined(AFX_MFCGENERIC_H__A8CAA9DD_194B_4CB9_B2F8_6EB3994B8AE0__INCLUDED_)
#define AFX_MFCGENERIC_H__A8CAA9DD_194B_4CB9_B2F8_6EB3994B8AE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcGenericApp:
// See mfcGeneric.cpp for the implementation of this class
//

class CMfcGenericApp : public CWinApp
{
public:
	CMfcGenericApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcGenericApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfcGenericApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCGENERIC_H__A8CAA9DD_194B_4CB9_B2F8_6EB3994B8AE0__INCLUDED_)
