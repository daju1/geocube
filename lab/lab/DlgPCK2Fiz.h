#if !defined(AFX_DLGPCK2FIZ_H__527A1B2F_9254_4134_B06A_2BCAA914DE05__INCLUDED_)
#define AFX_DLGPCK2FIZ_H__527A1B2F_9254_4134_B06A_2BCAA914DE05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPCK2Fiz.h : header file
//

#include "ListPCK2Fiz.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPCK2Fiz dialog
class CLabView;
class CLabDoc;
class CDatabase;

class CDlgPCK2Fiz : public CDialog
{
	CLabView * m_lab_view;
	CLabDoc * m_lab_doc;
	CDatabase * p_database;

	bool m_do_all;
// Construction
public:
	long m_ID_OBJ;
	long m_ID_IGE;
	long m_ID_CALC_PARAM;
	long m_ID_CALC_METHOD;
	BYTE m_ID_METHODY;
	BYTE m_TAB;
	CDlgPCK2Fiz(CLabView * lab_view, CLabDoc * lab_doc, CDatabase * database, bool do_all, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPCK2Fiz)
	enum { IDD = IDD_DIALOG_PCK2FIZ };
	CListPCK2Fiz m_list_pck2fiz;
	CButton	m_check_show_only_suitable_methods;
	CStatic	m_static_vid_formuly;
	CButton	m_button_tab_1;
	CButton	m_button_tab_2;
	CButton	m_button_tab_3;
	CStatic	m_static_pck;
	CStatic	m_static_pcb;
	CStatic	m_static_par;
	CStatic	m_static_KL;
	CStatic	m_static_K1;
	CStatic	m_static_K0;
	CEdit	m_edit_tab_row_pck;
	CEdit	m_edit_tab_row_pcb;
	CEdit	m_edit_tab_row_par;
	CButton	m_button_save_user_defined_method;
	CButton	m_static_vnutr_trenie;
	CButton	m_button_vnutr_trenie_1;
	CButton	m_button_vnutr_trenie_2;
	CEdit	m_edit_for_typzonds;
	CComboBox	m_combo_IGE;
	CComboBox	m_combo_calc_methods;
	CEdit	m_edit_KLOG;
	CEdit	m_edit_K1;
	CEdit	m_edit_K0;
	CEdit	m_edit_formula;
	CComboBox	m_combo_calc_params;
	CString	m_edit_contract;
	CString	m_edit_object;
	int		m_radio_method;
	int		m_vnutr_trenie;
	int		m_radio_tab;
	//}}AFX_DATA

	void FillCalcMode();
	void FillCalcModes();
	void FillCalcMethod();
	void FreeCalcMethod();
	void ApplyVnutrTrenieRadio(BYTE VNUTR_TRENIE);
	void ApplyTabRadio();

	bool CalcKT(long ID_KT);

	void Passport_all_KT(MyExcel & m_excel);
	void Passport_every_KT(MyExcel & m_excel);
	void Passport_every_IGE(MyExcel & m_excel);
	void InSertTheItem(MyExcel & m_excel, CString & str, int & iActualItem, int iSubItem);
	void InSertHeader(MyExcel & m_excel, int & iActualItem, int iSubItem);
	void InSertMeans(MyExcel & m_excel, int & iActualItem, int iSubItem);
	bool FillKT_or_IGE(MyExcel & m_excel, int & iActualItem, long ID, bool ige);
	void Passport(const char * fn);

	bool IsPtStZond(long ID_KT);


	void GetValuesFromExcelColomn(LabLayer * lab_layer, MyExcel & m_excel, char col, int sign, LabTrialValueType & vt, vector<trial_got_value> & vv, int rows);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPCK2Fiz)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPCK2Fiz)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCalcParams();
	afx_msg void OnSelchangeComboIge();
	afx_msg void OnSelchangeComboCalcMethods();
	afx_msg void OnButtonSetMethodForIge();
	virtual void OnOK();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnRadioMethod0();
	afx_msg void OnRadioMethod1();
	afx_msg void OnRadioMethod2();
	afx_msg void OnButtonUnsetMethodForIge();
	afx_msg void OnButtonSaveUserDefinedMethod();
	afx_msg void OnRadioFormulaOrTab1();
	afx_msg void OnRadioFormulaOrTab2();
	afx_msg void OnRadioFormulaOrTab3();
	afx_msg void OnButtonDeleteResults();
	afx_msg void OnCheckShowOnlySuitableMethods();
	afx_msg void OnButtonExportToExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPCK2FIZ_H__527A1B2F_9254_4134_B06A_2BCAA914DE05__INCLUDED_)
