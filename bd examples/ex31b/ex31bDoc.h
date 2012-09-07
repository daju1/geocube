// ex31bDoc.h : interface of the CEx31bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31BDOC_H__A0805536_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
#define AFX_EX31BDOC_H__A0805536_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ex31bSet.h"


class CEx31bDoc : public CDocument
{
protected: // create from serialization only
	CEx31bDoc();
	DECLARE_DYNCREATE(CEx31bDoc)

// Attributes
public:
	CEx31bSet m_ex31bSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31bDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx31bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31BDOC_H__A0805536_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
