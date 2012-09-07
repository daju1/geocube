#if !defined(AFX_DLGPROBGRUNT_H__B0DC4E93_2432_4F55_B9A2_E4D7E06AF09D__INCLUDED_)
#define AFX_DLGPROBGRUNT_H__B0DC4E93_2432_4F55_B9A2_E4D7E06AF09D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProbGrunt.h : header file
//
#include "ComboProbGrKT.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgProbGrunt dialog
class CLabDoc;
class CLabView;

class CDlgProbGrunt : public CDialog
{
	CLabView * m_view;
	CLabDoc * m_doc;
	bool m_new_prob;
// Construction
public:
	//int m_nItem;
	int i_kod_prob;
	int i_kt;
	long id_prob;
	long id_kt;
	int r_SoilsList;
	int r_SoilsListLab;
	CDlgProbGrunt(CLabView * view, CLabDoc * doc, bool new_prob, CWnd* pParent = NULL);   // standard constructor
 
	bool is_geo, is_lab;
// Dialog Data
	//{{AFX_DATA(CDlgProbGrunt)
	enum { IDD = IDD_DIALOG_PROB_GR_NEW };
	CComboBox	m_combo_kod_proby_grunta;
	ComboProbGrKT	m_combo_prob_gr_kt;
	CString	m_lab_n;
	CString	m_prob_gr_h;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProbGrunt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProbGrunt)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROBGRUNT_H__B0DC4E93_2432_4F55_B9A2_E4D7E06AF09D__INCLUDED_)
