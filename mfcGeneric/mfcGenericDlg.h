// mfcGenericDlg.h : header file
//

#if !defined(AFX_MFCGENERICDLG_H__2F25E5C9_20BD_413E_A704_911FEB6E0F5E__INCLUDED_)
#define AFX_MFCGENERICDLG_H__2F25E5C9_20BD_413E_A704_911FEB6E0F5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfcGenericDlg dialog

class CMfcGenericDlg : public CDialog
{
// Construction
public:
	CMfcGenericDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfcGenericDlg)
	enum { IDD = IDD_MFCGENERIC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcGenericDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMfcGenericDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCGENERICDLG_H__2F25E5C9_20BD_413E_A704_911FEB6E0F5E__INCLUDED_)
