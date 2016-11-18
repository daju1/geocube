#if !defined(AFX_DLGCOPYGRUNTY_H__84E590B5_3512_4B31_A102_327A9A281310__INCLUDED_)
#define AFX_DLGCOPYGRUNTY_H__84E590B5_3512_4B31_A102_327A9A281310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCopyGrunty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCopyGrunty dialog
class CLabView;
class CLabDoc;
class CDatabase;

// Construction
class DlgCopyGrunty : public CDialog
{
	CLabView * m_lab_view;
	CLabDoc * m_lab_doc;
	CDatabase * p_database;
	long ID_OBJ;
	long id_dest_obj;
// Construction
public:
	DlgCopyGrunty(CLabView * lab_view, CLabDoc * lab_doc, CDatabase * database, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCopyGrunty)
	enum { IDD = IDD_DIALOG_COPY_GRUNTY };
	CComboBox	m_combo_dest_object;
	BOOL	m_check_also_ige;
	BOOL	m_check_also_cube_size;
	CString	m_edit_source_object;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCopyGrunty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCopyGrunty)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDestObject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOPYGRUNTY_H__84E590B5_3512_4B31_A102_327A9A281310__INCLUDED_)
