// ex25dView.h : interface of the CEx25dView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25dVIEW_H__A9515B22_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX25dVIEW_H__A9515B22_5B85_11D0_848F_00400526305B__INCLUDED_


#include "AutoDriver.h"
#include "BankDriver.h"
#include "ClockDriver.h"
#include "excel8.h"

#include "AlarmDialog.h"

class CEx25dView : public CView
{
private:
   IAlarm m_alarm;
   IEx25bAuto m_auto;
   IBank m_bank;
   IEx25c m_clock;
   
   _Application m_app;
   Range    m_range[5];
   _Worksheet   m_worksheet;
   Workbooks   m_workbooks;
   Worksheets   m_worksheets;
   
protected: // create from serialization only
   CEx25dView();
   DECLARE_DYNCREATE(CEx25dView)

// Attributes
public:
   CEx25dDoc* GetDocument();

// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CEx25dView)
   public:
   virtual void OnDraw(CDC* pDC);  // overridden to draw this view
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   protected:
   //}}AFX_VIRTUAL

// Implementation
public:
   virtual ~CEx25dView();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
   //{{AFX_MSG(CEx25dView)
   afx_msg void OnBankoleLoad();
   afx_msg void OnUpdateBankoleLoad(CCmdUI* pCmdUI);
   afx_msg void OnBankoleTest();
   afx_msg void OnUpdateBankoleTest(CCmdUI* pCmdUI);
   afx_msg void OnBankoleUnload();
   afx_msg void OnUpdateBankoleUnload(CCmdUI* pCmdUI);
   afx_msg void OnClockoleCreatealarm();
   afx_msg void OnUpdateClockoleCreatealarm(CCmdUI* pCmdUI);
   afx_msg void OnClockoleLoad();
   afx_msg void OnUpdateClockoleLoad(CCmdUI* pCmdUI);
   afx_msg void OnClockoleRefreshtime();
   afx_msg void OnUpdateClockoleRefreshtime(CCmdUI* pCmdUI);
   afx_msg void OnClockoleUnload();
   afx_msg void OnUpdateClockoleUnload(CCmdUI* pCmdUI);
   afx_msg void OnDlloleGetdata();
   afx_msg void OnUpdateDlloleGetdata(CCmdUI* pCmdUI);
   afx_msg void OnDlloleLoad();
   afx_msg void OnUpdateDlloleLoad(CCmdUI* pCmdUI);
   afx_msg void OnDlloleUnload();
   afx_msg void OnUpdateDlloleUnload(CCmdUI* pCmdUI);
   afx_msg void OnExceloleExecute();
   afx_msg void OnUpdateExceloleExecute(CCmdUI* pCmdUI);
   afx_msg void OnExceloleLoad();
   afx_msg void OnUpdateExceloleLoad(CCmdUI* pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex25dView.cpp
inline CEx25dDoc* CEx25dView::GetDocument()
   { return (CEx25dDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25dVIEW_H__A9515B22_5B85_11D0_848F_00400526305B__INCLUDED_)
