// consumebiblioDlg.h : header file
//

#if !defined(AFX_CONSUMEBIBLIODLG_H__486A1B8A_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
#define AFX_CONSUMEBIBLIODLG_H__486A1B8A_0D94_11D2_8CAA_DF2C53524146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConsumebiblioDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CConsumebiblioDlg dialog

class CConsumebiblioDlg : public CDialog
{
	DECLARE_DYNAMIC(CConsumebiblioDlg);
	friend class CConsumebiblioDlgAutoProxy;

// Construction
public:
	CConsumebiblioDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CConsumebiblioDlg();

// Dialog Data
	//{{AFX_DATA(CConsumebiblioDlg)
	enum { IDD = IDD_CONSUMEBIBLIO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsumebiblioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CConsumebiblioDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CConsumebiblioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDoit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSUMEBIBLIODLG_H__486A1B8A_0D94_11D2_8CAA_DF2C53524146__INCLUDED_)
