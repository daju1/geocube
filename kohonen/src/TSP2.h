// TSP2.h : main header file for the TSP2 application
//

#if !defined(AFX_TSP2_H__406BA0FA_05CC_420B_A69D_3D4F2882CEE2__INCLUDED_)
#define AFX_TSP2_H__406BA0FA_05CC_420B_A69D_3D4F2882CEE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifndef __AFXWIN_H__
//	#error include 'stdafx.h' before including this file for PCH
//#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTSP2App:
// See TSP2.cpp for the implementation of this class
//

class CTSP2App : public CWinApp
{
public:
	CTSP2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTSP2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTSP2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSP2_H__406BA0FA_05CC_420B_A69D_3D4F2882CEE2__INCLUDED_)
