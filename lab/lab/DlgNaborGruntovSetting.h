#if !defined(AFX_DLGNABORGRUNTOVSETTING_H__82B706E4_E025_4DC1_8E24_4835485C2B34__INCLUDED_)
#define AFX_DLGNABORGRUNTOVSETTING_H__82B706E4_E025_4DC1_8E24_4835485C2B34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNaborGruntovSetting.h : header file
//
#include "MyListCtrl.h"
#include "ListGrunty.h"
#include "ListNaborGruntov.h"
#include "ListGruntGran.h"
#include "ListGenezis.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgNaborGruntovSetting dialog

class CDlgNaborGruntovSetting : public CDialog
{
	CLabView * m_view;
	CLabDoc * m_doc;
	CDatabase * p_database;
		
	long m_ID_OBJ;
	
	int nItem, nSubItem;
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;

// Construction
public:
	CDlgNaborGruntovSetting(CLabView * view, CLabDoc * doc, CDatabase * database, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNaborGruntovSetting)
	enum { IDD = IDD_DIALOG_NABOR_GRUNTOV_SETTING };
	CEdit	m_edit1;
	CListGrunty	m_list_grunt;
	CListNaborGruntov	m_list_nabor_gruntov;
	CListGruntGran	m_list_grunt_gran;
	CListGenezis	m_list_genezis;
	CComboBox	m_combo_grunt_vid;
	CComboBox	m_combo_grunt_typ;
	CComboBox	m_combo_grunt_raznovidnost;
	CComboBox	m_combo_grunt_podgruppa;
	CComboBox	m_combo_grunt_gruppa;
	CComboBox	m_combo_grunt_class;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNaborGruntovSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNaborGruntovSetting)
	afx_msg void OnOK();
	virtual void OnCancel();
	afx_msg void OnEditchangeComboGruntClass();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeComboGruntGruppa();
	afx_msg void OnEditchangeComboGruntPodgruppa();
	afx_msg void OnEditchangeComboGruntTyp();
	afx_msg void OnEditchangeComboGruntVid();
	afx_msg void OnEditchangeComboGruntRaznovidnost();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnButtonSelectedGruntToList();
	afx_msg void OnButtonCancelGruntSelecting();
	afx_msg void OnEndlabeleditListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeydownListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OK();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNABORGRUNTOVSETTING_H__82B706E4_E025_4DC1_8E24_4835485C2B34__INCLUDED_)
