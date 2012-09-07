// GPS_CRD.h : main header file for the GPS_CRD application
//

#if !defined(AFX_GPS_CRD_H__8F2FB5E0_6C14_44D7_99FE_038C7AD157D1__INCLUDED_)
#define AFX_GPS_CRD_H__8F2FB5E0_6C14_44D7_99FE_038C7AD157D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGPS_CRDApp:
// See GPS_CRD.cpp for the implementation of this class
//

class CGPS_CRDApp : public CWinApp
{
public:
	CGPS_CRDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPS_CRDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGPS_CRDApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPS_CRD_H__8F2FB5E0_6C14_44D7_99FE_038C7AD157D1__INCLUDED_)
