// lab.h : main header file for the LAB application
//

#if !defined(AFX_LAB_H__EE2C9718_A0AE_460E_8161_330CFD05E32B__INCLUDED_)
#define AFX_LAB_H__EE2C9718_A0AE_460E_8161_330CFD05E32B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#define PI		3.14159265358979323846

/////////////////////////////////////////////////////////////////////////////
// CLabApp:
// See lab.cpp for the implementation of this class
//
#define UPDATE_LISTS_ON_CLICK 0

#include "labdoc.h"	

class /*AFX_EXT_CLASS*/ CLabApp : public CWinApp
{
public:
	CLabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CLabApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAB_H__EE2C9718_A0AE_460E_8161_330CFD05E32B__INCLUDED_)
