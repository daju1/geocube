// ex31aView.h : interface of the CEx31aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31AVIEW_H__4C4C2526_6EAD_11D0_8609_F283035DC070__INCLUDED_)
#define AFX_EX31AVIEW_H__4C4C2526_6EAD_11D0_8609_F283035DC070__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx31aView : public CScrollView
{
protected: // create from serialization only
	CEx31aView();
	DECLARE_DYNCREATE(CEx31aView)

// Attributes
public:
	CEx31aDoc* GetDocument();

private:
	CEx31aSet* m_pSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx31aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex31aView.cpp
inline CEx31aDoc* CEx31aView::GetDocument()
   { return (CEx31aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31AVIEW_H__4C4C2526_6EAD_11D0_8609_F283035DC070__INCLUDED_)
