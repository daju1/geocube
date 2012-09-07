#if !defined(AFX_DLGSOILNAME_H__9783FE80_D4C3_4A8D_A64D_1C1091F00B49__INCLUDED_)
#define AFX_DLGSOILNAME_H__9783FE80_D4C3_4A8D_A64D_1C1091F00B49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSoilName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSoilName dialog

class LabNumber;
class CLabView;

class CDlgSoilName : public CDialog
{
	LabNumber * m_lab_number;
	CLabView * m_lab_view;
// Construction
public:
	CDlgSoilName(CLabView * lab_view, LabNumber * lab_number, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSoilName)
	enum { IDD = IDD_DIALOG_SOIL_NAME };
	CString	m_edit_soil_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSoilName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSoilName)
	virtual void OnOK();
	afx_msg void OnButtonGenerateSoilName();
	afx_msg void OnButtonSoilNameFromDb();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOILNAME_H__9783FE80_D4C3_4A8D_A64D_1C1091F00B49__INCLUDED_)
