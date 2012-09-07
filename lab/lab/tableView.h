// tableView.h : interface of the CTableView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEVIEW_H__899D8B7B_997E_4A39_B61B_9E7367F512A7__INCLUDED_)
#define AFX_TABLEVIEW_H__899D8B7B_997E_4A39_B61B_9E7367F512A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTableView : public CListView
{
protected: // create from serialization only
	CTableView();
	DECLARE_DYNCREATE(CTableView)

// Attributes
public:
	CTableDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableView)
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
	virtual ~CTableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTableView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in tableView.cpp
inline CTableDoc* CTableView::GetDocument()
   { return (CTableDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEVIEW_H__899D8B7B_997E_4A39_B61B_9E7367F512A7__INCLUDED_)
