#if !defined(AFX_DLGPROBGR_DBLCLICKMODE_H__47DC522A_F93B_4687_98E6_D7AFF70C774D__INCLUDED_)
#define AFX_DLGPROBGR_DBLCLICKMODE_H__47DC522A_F93B_4687_98E6_D7AFF70C774D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProbGr_DblClickMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProbGr_DblClickMode dialog

class CDlgProbGr_DblClickMode : public CDialog
{
// Construction
public:
	CDlgProbGr_DblClickMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProbGr_DblClickMode)
	enum { IDD = IDD_DIALOG_PROBGR_DBL_CLICK_MODE };
	int		m_radio;
	//}}AFX_DATA

	static int selected_mode; 


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProbGr_DblClickMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProbGr_DblClickMode)
	afx_msg void OnRadioLabNumber();
	afx_msg void OnRadioGruntName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROBGR_DBLCLICKMODE_H__47DC522A_F93B_4687_98E6_D7AFF70C774D__INCLUDED_)
