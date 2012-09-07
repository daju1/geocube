// GPS_CRDDlg.h : header file
//

#if !defined(AFX_GPS_CRDDLG_H__64B34D6B_6689_4898_8CBC_E3777ECC46B4__INCLUDED_)
#define AFX_GPS_CRDDLG_H__64B34D6B_6689_4898_8CBC_E3777ECC46B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGPS_CRDDlg dialog
#include "./../excel_connect/src/myexcel.h"

class CGPS_CRDDlg : public CDialog
{
	MyExcel m_excel_out;
	MyExcel m_excel_gps;
	MyExcel m_excel_pribor;
	void LoadExcelFile(MyExcel &m_excel, const char * fn, bool & ole_loaded);
	void CloseExcelFile(MyExcel &m_excel, bool & ole_loaded, bool to_close = true);

	bool gps_fn_loaded, pribor_fn_loaded;
	bool gps_ole_loaded, pribor_ole_loaded, out_ole_loaded;

// Construction
public:
	CGPS_CRDDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGPS_CRDDlg)
	enum { IDD = IDD_GPS_CRD_DIALOG };
	CButton	m_button_calc;
	CButton	m_button_close;
	CButton	m_button_load_files;
	CString	m_edit_gps_fn;
	CString	m_edit_pribor_fn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPS_CRDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGPS_CRDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGpsBrose();
	afx_msg void OnButtonPriborBrose();
	virtual void OnOK();
	afx_msg void OnButtonLoadFiles();
	afx_msg void OnButtonCalc();
	afx_msg void OnButtonClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPS_CRDDLG_H__64B34D6B_6689_4898_8CBC_E3777ECC46B4__INCLUDED_)
