#if !defined(AFX_3DDOC_H__6004A120_3B98_4A14_826D_77CF1E654AE8__INCLUDED_)
#define AFX_3DDOC_H__6004A120_3B98_4A14_826D_77CF1E654AE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DDoc document

class C3DDoc : public CDocument
{
protected:
	C3DDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(C3DDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DDOC_H__6004A120_3B98_4A14_826D_77CF1E654AE8__INCLUDED_)
