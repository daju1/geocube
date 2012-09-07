#if !defined(AFX_DLGPALJA_H__4C2776BE_16F7_42DE_9B3C_63A7A9B9FD64__INCLUDED_)
#define AFX_DLGPALJA_H__4C2776BE_16F7_42DE_9B3C_63A7A9B9FD64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPalja.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPalja dialog
class CLabView;
class CLabDoc;
class CDatabase;

#include "MyPalja.h"
#include "ListRaschetSvai.h"
#include "../../surfdoc/src/surfdoc.h"

class CDlgPalja : public CDialog
{
	CLabView * m_lab_view;
	CLabDoc * m_lab_doc;
	CDatabase * p_database;

	bool m_do_all;

// Construction
public:
	long ID_OBJ;
	SurfDoc m_SurfDoc;
	bool InitDoc();
	MyPalja my_palja;
	vector<MyPalja> v_my_palja;
	void FillPaljaHeader(MyPalja & mp);


	CDlgPalja(CLabView * lab_view, CLabDoc * lab_doc, CDatabase * database, bool do_all, CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CDlgPalja)
	enum { IDD = IDD_DIALOG_PALJA };
	CEdit	m_edit_step;
	CButton	m_button_to_excel;
	CButton	m_static_grunt_type_1zt;
	CButton	m_radio_type_grunt_1zt1;
	CButton	m_radio_type_grunt_1zt2;
	CButton	m_radio_type_grunt_1zt3;
	CButton	m_radio_type_grunt_1zt4;
	CEdit	m_edit_rostverk_H;
	CButton	m_check_razbivka_na_tolschi;
	CListRaschetSvai	m_list_svai;
	CEdit	m_edit_sech_Y;
	CEdit	m_edit_sech_X;
	CEdit	m_edit_r_svai;
	CComboBox	m_combo_svai_storona_kvadrata;
	CString	m_edit_contract;
	CString	m_edit_object;
	CString	m_edit_zond_type;
	CString	m_edit_tsz;
	int		m_radio_svai_sech;
	int		m_radio_rostverk_h;
	int		m_radio_snip1;
	int		m_radio_method_find_mean_pck;
	int		m_radio_typ_grunt_1_zond_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPalja)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPalja)
	afx_msg void OnButtonSaveToDb();
	virtual void OnOK();
	afx_msg void OnButtonToExcel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnRadioSvaiSech1();
	afx_msg void OnRadioSvaiSech2();
	afx_msg void OnRadioSvaiSech3();
	afx_msg void OnRadioRostverkH1();
	afx_msg void OnRadioRostverkH2();
	afx_msg void OnRadioSnip1();
	afx_msg void OnRadioSnip2();
	afx_msg void OnRadioTypGrunt1();
	afx_msg void OnRadioTypGrunt2();
	afx_msg void OnCheck1ZondTypeRazbivkaNaTolschi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPALJA_H__4C2776BE_16F7_42DE_9B3C_63A7A9B9FD64__INCLUDED_)
