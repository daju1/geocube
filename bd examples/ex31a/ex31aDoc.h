// ex31aDoc.h : interface of the CEx31aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31ADOC_H__4C4C2524_6EAD_11D0_8609_F283035DC070__INCLUDED_)
#define AFX_EX31ADOC_H__4C4C2524_6EAD_11D0_8609_F313035DC070__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx31aDoc : public CDocument
{
protected: // create from serialization only
	CEx31aDoc();
	DECLARE_DYNCREATE(CEx31aDoc)

// Attributes
public:
	CEx31aSet m_ex31aSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx31aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31ADOC_H__4C4C2524_6EAD_11D0_8609_F283035DC070__INCLUDED_)
