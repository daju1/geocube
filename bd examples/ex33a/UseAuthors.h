#if !defined(AFX_USEAUTHORS_H__486A1B98_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
#define AFX_USEAUTHORS_H__486A1B98_0D94_11D2_8CAA_DF2C53524146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UseAuthors.h : header file
//

#include "authors.h"

/////////////////////////////////////////////////////////////////////////////
// CUseAuthors dialog

class CUseAuthors : public CDialog
{

	CAuthors m_authors;
// Construction
public:
	CUseAuthors(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUseAuthors)
	enum { IDD = IDD_USEAUTHORS };
	CString	m_strAuthor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseAuthors)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUseAuthors)
	afx_msg void OnNext();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEAUTHORS_H__486A1B98_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
