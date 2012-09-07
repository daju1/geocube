#if !defined(AFX_DLGLANGUAGE_H__2D7FF830_3326_48F3_A4BE_3BCC00BB21D4__INCLUDED_)
#define AFX_DLGLANGUAGE_H__2D7FF830_3326_48F3_A4BE_3BCC00BB21D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLanguage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage dialog

class CDlgLanguage : public CDialog
{
// Construction
public:
	CDlgLanguage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLanguage)
	enum { IDD = IDD_DIALOG_LANGUAGE };
	CComboBox	m_combo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLanguage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLanguage)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLANGUAGE_H__2D7FF830_3326_48F3_A4BE_3BCC00BB21D4__INCLUDED_)
