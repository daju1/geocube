// consumebiblio.h : main header file for the CONSUMEBIBLIO application
//

#if !defined(AFX_CONSUMEBIBLIO_H__486A1B88_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
#define AFX_CONSUMEBIBLIO_H__486A1B88_0D94_11D2_8CAA_DF2C53524146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Consumebiblio_i.h"

/////////////////////////////////////////////////////////////////////////////
// CConsumebiblioApp:
// See consumebiblio.cpp for the implementation of this class
//

class CConsumebiblioApp : public CWinApp
{
public:
	CConsumebiblioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsumebiblioApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConsumebiblioApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSUMEBIBLIO_H__486A1B88_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
