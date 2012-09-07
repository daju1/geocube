// ex31bView.h : interface of the CEx31bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31BVIEW_H__A0805538_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
#define AFX_EX31BVIEW_H__A0805538_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEx31bSet;

class CEx31bView : public CRecordView
{
protected: // create from serialization only
	CEx31bView();
	DECLARE_DYNCREATE(CEx31bView)

public:
	//{{AFX_DATA(CEx31bView)
	enum { IDD = IDD_EX31B_FORM };
	CEx31bSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CEx31bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31bView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnMove(UINT nIDMoveCommand);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx31bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31bView)
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordClearfields();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordUpdate();
	afx_msg void OnUpdateRecordUpdate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex31bView.cpp
inline CEx31bDoc* CEx31bView::GetDocument()
   { return (CEx31bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31BVIEW_H__A0805538_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
