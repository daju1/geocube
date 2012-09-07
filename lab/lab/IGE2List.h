// UstList.h: interface for the UstList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IGE2LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
#define AFX_IGE2LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "MyListCtrl.h"
class CDatabase;
class CIGE2List : public CMyListCtrl  
{
	friend class DlgIGEList;
	long m_ID_OBJ;

	CDatabase * p_database;
public:
	void FillCtrlList();
	void InSertTheItem(CString & str, int & iActualItem, int iSubItem);

	CIGE2List(CDatabase * database);
	virtual ~CIGE2List();

	BOOL OnInitCtrl();


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIGE2List)
	protected:
	protected:
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CIGE2List)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_IGE2LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
