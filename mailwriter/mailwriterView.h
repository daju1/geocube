// mailwriterView.h : interface of the CMailwriterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILWRITERVIEW_H__55B4940D_41C2_49A6_B02E_045740AE6241__INCLUDED_)
#define AFX_MAILWRITERVIEW_H__55B4940D_41C2_49A6_B02E_045740AE6241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DlgSendMail;

class CMailwriterView : public CEditView
{
protected: // create from serialization only
	CMailwriterView();
	DECLARE_DYNCREATE(CMailwriterView)

// Attributes
public:
	CMailwriterDoc* GetDocument();
	DlgSendMail * dlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailwriterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMailwriterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMailwriterView)
	afx_msg void OnMailSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mailwriterView.cpp
inline CMailwriterDoc* CMailwriterView::GetDocument()
   { return (CMailwriterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILWRITERVIEW_H__55B4940D_41C2_49A6_B02E_045740AE6241__INCLUDED_)
