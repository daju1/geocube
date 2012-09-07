#if !defined(AFX_DLGNROWS_H__4CF3C7F7_092C_440C_A393_264F7F2AE397__INCLUDED_)
#define AFX_DLGNROWS_H__4CF3C7F7_092C_440C_A393_264F7F2AE397__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNRows.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNRows dialog

class CDlgNRows : public CDialog
{
// Construction
public:

	bool ok_pressed;
	CDlgNRows(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNRows)
	enum { IDD = IDD_DIALOG_N_ROWS };
	CString	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNRows)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNRows)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNROWS_H__4CF3C7F7_092C_440C_A393_264F7F2AE397__INCLUDED_)
