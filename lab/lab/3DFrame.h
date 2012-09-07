#if !defined(AFX_3DFRAME_H__AA66B580_C817_4791_9B15_99B4E91F57F1__INCLUDED_)
#define AFX_3DFRAME_H__AA66B580_C817_4791_9B15_99B4E91F57F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DFrame frame

class C3DFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(C3DFrame)
protected:
	C3DFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~C3DFrame();

	// Generated message map functions
	//{{AFX_MSG(C3DFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DFRAME_H__AA66B580_C817_4791_9B15_99B4E91F57F1__INCLUDED_)
