// LabElementList.h: interface for the LabElementList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABELEMENTLIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
#define AFX_LABELEMENTLIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "MyListCtrl.h"

class LabElement;
class SoilDescriptionPtr;
class CLabElementList : public CMyListCtrl  
{
	LabElement * m_lab_element;
public:
	void FillCtrlList();
	void DrawDataRow(vector<SoilDescriptionPtr>::iterator & it);
	void InSertTheItem(CString & str, int & iActualItem, int iSubItem);

	void SetLabElement(LabElement * lab_element);
	CLabElementList();
	virtual ~CLabElementList();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabElementList)
	protected:
	protected:
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CLabElementList)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_LABELEMENTLIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
