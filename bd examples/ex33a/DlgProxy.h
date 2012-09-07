// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__486A1B8C_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
#define AFX_DLGPROXY_H__486A1B8C_0D94_11D2_8CAA_DF2C53524146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConsumebiblioDlg;

/////////////////////////////////////////////////////////////////////////////
// CConsumebiblioDlgAutoProxy command target

class CConsumebiblioDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CConsumebiblioDlgAutoProxy)

	CConsumebiblioDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CConsumebiblioDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsumebiblioDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CConsumebiblioDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CConsumebiblioDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CConsumebiblioDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CConsumebiblioDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__486A1B8C_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
