#if !defined(AFX_3DVIEW_H__64E1B9EF_DC98_420C_A953_22F2A1AECE96__INCLUDED_)
#define AFX_3DVIEW_H__64E1B9EF_DC98_420C_A953_22F2A1AECE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DView view

#include "../../excel_connect/src/MyExcel.h"

class C3DView : public CView
{

	MyExcel m_excel;

protected:
	C3DView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(C3DView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~C3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DView)
	afx_msg void OnExcelLoad();
	afx_msg void OnUpdateExcelLoad(CCmdUI* pCmdUI);
	afx_msg void OnExcelRelease();
	afx_msg void OnUpdateExcelRelease(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DVIEW_H__64E1B9EF_DC98_420C_A953_22F2A1AECE96__INCLUDED_)
