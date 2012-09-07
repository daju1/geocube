#if !defined(AFX_DLGSTATZOND_H__C545975A_00D5_48C8_9B74_ECB7C5EF0CFE__INCLUDED_)
#define AFX_DLGSTATZOND_H__C545975A_00D5_48C8_9B74_ECB7C5EF0CFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStatZond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStatZond dialog
class CLabView;
class CLabDoc;
class CDatabase;

class CDlgStatZond : public CDialog
{
	CLabView * m_lab_view;
	CLabDoc * m_lab_doc;
	CDatabase * p_database;
// Construction
public:
	long id_ust_selected;
	bool ok_pressed;
	// standard constructor
	CDlgStatZond(CLabView * lab_view, CLabDoc *	lab_doc, CDatabase * database, CWnd* pParent = NULL);   

// Dialog Data
	//{{AFX_DATA(CDlgStatZond)
	enum { IDD = IDD_DIALOG_STAT_ZOND };
	CComboBox	m_combo_ust;
	CString	m_edit_bf;
	CString	m_edit_bg;
	CString	m_edit_kf;
	CString	m_edit_kg;
	CString	m_edit_zong_type;
	CString	m_edit_tsz;
	CString	m_edit_object;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStatZond)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStatZond)
	afx_msg void OnSelchangeComboUst();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonToExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTATZOND_H__C545975A_00D5_48C8_9B74_ECB7C5EF0CFE__INCLUDED_)
