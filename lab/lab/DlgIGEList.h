#if !defined(AFX_DLGIGELIST_H__D0471DC7_D021_4155_BA26_DA9351A423DC__INCLUDED_)
#define AFX_DLGIGELIST_H__D0471DC7_D021_4155_BA26_DA9351A423DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIGEList.h : header file
//

#include "IGE2List.h"

/////////////////////////////////////////////////////////////////////////////
// DlgIGEList dialog

class DlgIGEList : public CDialog
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
	DlgIGEList(CLabView * view, CLabDoc * doc, CDatabase * database, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgIGEList)
	enum { IDD = IDD_DIALOG_IGE };
	CEdit	m_edit1;
	CComboBox	m_combo1;
	CIGE2List	m_list_ige;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgIGEList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgIGEList)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnClickListIge(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnKeydownListIge(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIGELIST_H__D0471DC7_D021_4155_BA26_DA9351A423DC__INCLUDED_)
