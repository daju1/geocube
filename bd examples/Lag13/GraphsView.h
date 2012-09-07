// GraphsView.h : interface of the CGraphsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHSVIEW_H__9DBD1EAD_FF8D_4FF9_906A_B2FC1D4C91CC__INCLUDED_)
#define AFX_GRAPHSVIEW_H__9DBD1EAD_FF8D_4FF9_906A_B2FC1D4C91CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphsView : public CScrollView
{
	HANDLE  m_hEventDrawReady;

protected: // create from serialization only
	CGraphsView();
	DECLARE_DYNCREATE(CGraphsView)

// Attributes
public:
	CSize m_SizeTotal;
	CGraphsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphsView)
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
	virtual ~CGraphsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphsView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphsView.cpp
inline CGraphsDoc* CGraphsView::GetDocument()
   { return (CGraphsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHSVIEW_H__9DBD1EAD_FF8D_4FF9_906A_B2FC1D4C91CC__INCLUDED_)
