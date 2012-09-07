#if !defined(AFX_OBJECTDIALOG_H__912D1E4C_366E_4F28_A33B_8D5FED4018F7__INCLUDED_)
#define AFX_OBJECTDIALOG_H__912D1E4C_366E_4F28_A33B_8D5FED4018F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgObject dialog
class CLabDoc;
class CLabView;
class CDlgObject : public CDialog
{
	CLabView * m_view;
	CLabDoc * m_doc;
	bool m_new_object;
// Construction
public:
	CDlgObject(CLabView * view, CLabDoc * doc, bool new_object, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgObject)
	enum { IDD = IDD_DIALOG_OBJECT };
	CString	m_contract;
	CString	m_object_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgObject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgObject)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTDIALOG_H__912D1E4C_366E_4F28_A33B_8D5FED4018F7__INCLUDED_)
