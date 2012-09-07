// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__271736E0_AE68_4E47_9578_9F22E8259A08__INCLUDED_)
#define AFX_MAINFRM_H__271736E0_AE68_4E47_9578_9F22E8259A08__INCLUDED_

#include "ComPort.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_sTextFilePath;
	bool m_bToWriteTextFile;
	CComPort m_comPort;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnComConnect();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateComConnect(CCmdUI* pCmdUI);
	afx_msg void OnComRead();
	afx_msg void OnUpdateComRead(CCmdUI* pCmdUI);
	afx_msg void OnComDisconnect();
	afx_msg void OnUpdateComDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnComSetFilename();
	afx_msg void OnUpdateComSetFilename(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnPumpingMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnComPortErrorMessage(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__271736E0_AE68_4E47_9578_9F22E8259A08__INCLUDED_)
