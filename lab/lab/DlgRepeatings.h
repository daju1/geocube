#if !defined(AFX_DLGREPEATINGS_H__5641EC5D_75C3_435F_AF83_725CC4764101__INCLUDED_)
#define AFX_DLGREPEATINGS_H__5641EC5D_75C3_435F_AF83_725CC4764101__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRepeatings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatings dialog

class CDlgRepeatings : public CDialog
{
// Construction
public:
	CDlgRepeatings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRepeatings)
	enum { IDD = IDD_DIALOG_REPEATINGS };
	int		m_repeatings;
	//}}AFX_DATA

	static int s_repeatings;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRepeatings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRepeatings)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioTwoRepeatings();
	afx_msg void OnRadioThreeRepeatings();
	afx_msg void OnRadioSixRepeatings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPEATINGS_H__5641EC5D_75C3_435F_AF83_725CC4764101__INCLUDED_)
