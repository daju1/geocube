// RaschetSvaiList.h: interface for the RaschetSvaiList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RaschetSvai_LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
#define AFX_RaschetSvai_LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "MyListCtrl.h"
class CDatabase;
class Well_3D;
class CListRaschetSvai : public CMyListCtrl  
{
	CDatabase * p_database;
public:
	Well_3D * p_well;
	long ID_OBJ, ID_KT;
	void InitHeaders();
	void AddString(int & iActualItem, int iSubItem, CString & str);
	void FillCtrlList();
	void InSertTheItem(CString & str, int & iActualItem, int iSubItem);

	CListRaschetSvai(CDatabase * database, Well_3D * well);
	virtual ~CListRaschetSvai();



	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListRaschetSvai)
	protected:
	protected:
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CListRaschetSvai)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_RaschetSvai_LIST_H__5F61FB21_D526_4701_B954_D6B76A3111FA__INCLUDED_)
