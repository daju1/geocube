// RaschetSvaiList.h: interface for the RaschetSvaiList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCK2Fiz_LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
#define AFX_PCK2Fiz_LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "MyListCtrl.h"
class CDatabase;
class Well_3D;
class CListPCK2Fiz : public CMyListCtrl  
{
	CDatabase * p_database;
	bool FillKT(int & iActualItem, long ID_KT, CString KT_NAME);
	void InsertingColumn(int & icol, CString str, int width);

public:

	long m_ID_OBJ;
	void InitHeaders();
	void AddString(int & iActualItem, int iSubItem, CString & str);
	void FillCtrlList();
	void InSertTheItem(CString & str, int & iActualItem, int iSubItem);

	CListPCK2Fiz(CDatabase * database);
	virtual ~CListPCK2Fiz();



	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListPCK2Fiz)
	protected:
	protected:
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CListPCK2Fiz)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PCK2Fiz_LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
