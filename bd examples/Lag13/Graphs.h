// Graphs.h : main header file for the GRAPHS application
//

#if !defined(AFX_GRAPHS_H__98C6F4D6_3136_4B52_B79A_7371E4FF5AEF__INCLUDED_)
#define AFX_GRAPHS_H__98C6F4D6_3136_4B52_B79A_7371E4FF5AEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "MainFrm.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CGraphsApp:
// See Graphs.cpp for the implementation of this class
//

class CGraphsApp : public CWinApp
{
	friend class CMainFrame;
public:
	CGraphsApp();
	CMultiDocTemplate* m_pDocTemplate;
	CMultiDocTemplate* m_pDocTemplate3;
//	CRITICAL_SECTION cs;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CGraphsApp)
	afx_msg void OnFileImport();
	afx_msg void OnFileImport2();
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew3d();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHS_H__98C6F4D6_3136_4B52_B79A_7371E4FF5AEF__INCLUDED_)
