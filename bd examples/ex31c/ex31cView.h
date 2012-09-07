// ex31cView.h : interface of the CEx31cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31CVIEW_H__6FE9FA8F_957D_11D0_AAA2_444553540000__INCLUDED_)
#define AFX_EX31CVIEW_H__6FE9FA8F_957D_11D0_AAA2_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx31cSet;

class CEx31cView : public CRecordView
{
protected: // create from serialization only
	CEx31cView();
	DECLARE_DYNCREATE(CEx31cView)

public:
	//{{AFX_DATA(CEx31cView)
	enum { IDD = IDD_EX31C_FORM };
	CEx31cSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CEx31cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31cView)
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
	virtual ~CEx31cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	void LoadListbox();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31cView)
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordClearfields();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordUpdate();
	afx_msg void OnUpdateRecordUpdate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex31cView.cpp
inline CEx31cDoc* CEx31cView::GetDocument()
   { return (CEx31cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31CVIEW_H__6FE9FA8F_957D_11D0_AAA2_444553540000__INCLUDED_)
