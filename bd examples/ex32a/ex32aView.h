// ex32avw.h : interface of the CEx32aView class
//
/////////////////////////////////////////////////////////////////////////////
#include "RowView.h"

#if !defined(AFX_EX32AVIEW_H__87130E7F_8817_11D0_86C5_F5A2C72DE570__INCLUDED_)
#define AFX_EX32AVIEW_H__87130E7F_8817_11D0_86C5_F5A2C72DE570__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx32aView : public CRowView
{
private:
	int m_nSelectedRow;
	CDaoRecordset* m_pSet;
protected: // create from serialization only
	CEx32aView();
	DECLARE_DYNCREATE(CEx32aView)

// Attributes
public:
	CEx32aDoc* GetDocument();
	//{{AFX_VIRTUAL(CEx32aView)
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
	virtual ~CEx32aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	void DrawDataRow(CDC* pDC, int y);
// Generated message map functions
protected:
	//{{AFX_MSG(CEx32aView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex32avw.cpp
inline CEx32aDoc* CEx32aView::GetDocument()
   { return (CEx32aDoc*) m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX32AVIEW_H__87130E7F_8817_11D0_86C5_F5A2C72DE570__INCLUDED_)
