// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FD5EA789_5520_45EA_98AB_648A8824BE7C__INCLUDED_)
#define AFX_STDAFX_H__FD5EA789_5520_45EA_98AB_648A8824BE7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>			  // MFC template classes
#include <afxsock.h>        // MFC Sockets
#include <afxdisp.h>        // Required by afxpriv.h
#include <afxpriv.h>        // to get access to the T2A macro

//void WriteRaporto(LPCTSTR s);

#define WriteRaporto NULL
//#define TRACE AfxMessageBox
#define TRACE WriteRaporto
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FD5EA789_5520_45EA_98AB_648A8824BE7C__INCLUDED_)
