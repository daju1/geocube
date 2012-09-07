
// ex31d.h : main header file for the EX31D application
//
#if !defined(AFX_EX31D_H__BA9E33E8_958A_11D0_AAA2_444553540000__INCLUDED_)
#define AFX_EX31D_H__BA9E33E8_958A_11D0_AAA2_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx31dApp:
// See ex31d.cpp for the implementation of this class
//

class CEx31dApp : public CWinApp
{
public:
	CEx31dApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31dApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx31dApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31D_H__BA9E33E8_958A_11D0_AAA2_444553540000__INCLUDED_)
