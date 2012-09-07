// tableDoc.h : interface of the CTableDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEDOC_H__F3E73F2B_50B4_4334_B776_097F16ADCE80__INCLUDED_)
#define AFX_TABLEDOC_H__F3E73F2B_50B4_4334_B776_097F16ADCE80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTableDoc : public CDocument
{
protected: // create from serialization only
	CTableDoc();
	DECLARE_DYNCREATE(CTableDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTableDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTableDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDOC_H__F3E73F2B_50B4_4334_B776_097F16ADCE80__INCLUDED_)
