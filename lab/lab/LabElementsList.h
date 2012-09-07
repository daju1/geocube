// LabElementsList.h: interface for the CLabElementsList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABELEMENTSLIST_H__D4447767_9D43_4545_9897_751151FF96E1__INCLUDED_)
#define AFX_LABELEMENTSLIST_H__D4447767_9D43_4545_9897_751151FF96E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyListCtrl.h"

class LabElement;
class LabElements;
class CDlgLabElements;

class CLabElementsList : public CMyListCtrl  
{
	CDlgLabElements * m_dlg;
	LabElements * m_lab_elements;
public:

	void FillCtrlList();
	void DrawDataRow(LabElement & le);

	CLabElementsList(CDlgLabElements * dlg, LabElements * lab_elements);
	virtual ~CLabElementsList();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabElementList)
	protected:
	protected:
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CLabElementsList)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_LABELEMENTSLIST_H__D4447767_9D43_4545_9897_751151FF96E1__INCLUDED_)
