#if !defined(AFX_DLGZONDUSTPARAM_H__22427E22_9850_466D_9913_8E3156EAF75B__INCLUDED_)
#define AFX_DLGZONDUSTPARAM_H__22427E22_9850_466D_9913_8E3156EAF75B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgZondUstParam.h : header file
//

#include "UstList.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgZondUstParam dialog
class CLabView;
class CLabDoc;
class CDatabase;


class CDlgZondUstParam : public CDialog
{
	CLabView * m_lab_view;
	CLabDoc * m_lab_doc;
	CDatabase * p_database;

	int nItem, nSubItem;
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
//	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
// Construction
public:
	CDlgZondUstParam(CLabView * lab_view, CLabDoc * lab_doc, CDatabase * database, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgZondUstParam)
	enum { IDD = IDD_DIALOG_ZOND_UST_PARAM };
	CUstList	m_ust_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZondUstParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgZondUstParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnClickListUst(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditListUst(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditListUst(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnButtonAddUst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGZONDUSTPARAM_H__22427E22_9850_466D_9913_8E3156EAF75B__INCLUDED_)
