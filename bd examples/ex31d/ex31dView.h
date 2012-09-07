// ex31dvw.h : interface of the CEx31dView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_EX31DVIEW_H__BA9E33F2_958A_11D0_AAA2_444553540000__INCLUDED_)
#define AFX_EX31DVIEW_H__BA9E33F2_958A_11D0_AAA2_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "rowview.h"

class CEx31dView : public CRowView
{
private:
	int m_nSelectedRow;
	CRecordset* m_pSet;
protected: // create from serialization only
	CEx31dView();
	DECLARE_DYNCREATE(CEx31dView)

// Attributes
public:
	CEx31dDoc* GetDocument();
	//{{AFX_VIRTUAL(CEx31dView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView*, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL


// Overrides of CRowView
	void OnDrawRow(CDC* pDC, int nRowNo, int y, BOOL bSelected);
	void GetRowWidthHeight(CDC* pDC, int& nRowWidth, 
		int& nRowHeight, int& nCharWidth);
	int GetActiveRow();
	int GetRowCount();
	void ChangeSelectionNextRow(BOOL bNext);
	void ChangeSelectionToRow(int nRow);

// Implementation
public:
	virtual ~CEx31dView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	void DrawDataRow(CDC* pDC, int y);
// Generated message map functions
protected:
	//{{AFX_MSG(CEx31dView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex31dView.cpp
inline CEx31dDoc* CEx31dView::GetDocument()
   { return (CEx31dDoc*) m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31DVIEW_H__BA9E33F2_958A_11D0_AAA2_444553540000__INCLUDED_)
