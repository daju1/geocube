#if !defined(AFX_MYLIST_H__E10E4190_0DDE_4F15_8F59_B0BE852657DF__INCLUDED_)
#define AFX_MYLIST_H__E10E4190_0DDE_4F15_8F59_B0BE852657DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyList view
#include "ListVwEx.h"   // base class for RightView
class CLabView;

class CMyList : public CListViewEx
{
	friend struct ATable;
protected:
	CMyList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyList)

// Attributes
public:
	CLabView * m_lab_view;

// Operations
public:
	void DeleteAllItemsAndColomns();

	BOOL OnInitCtrl();
//	virtual void FillCtrlList(ATable *, CString where, CString order_by);
//	virtual void FillCtrlList(CRecordset * pRecordset){}
	virtual void DrawDataRow(CRecordset * pRecordset);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//CImageList * m_pImageHdrSmall;
//	CImageList * m_pImageList;
//	CImageList * m_pImageListSmall;
	virtual void FillListCtrl(){}
	void ChangeListCtrlStyle(DWORD dwStyle, BOOL bSetBits);
//	BOOL m_bHotCursor;

//	HCURSOR m_hStdHotCursor;
//	HCURSOR m_hMyHotCursor;
//	HICON m_hIcon;
//	CImageList m_LargeImageList;
//	CImageList m_SmallImageList;
//	CImageList m_StateImageList;

	
	virtual ~CMyList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLIST_H__E10E4190_0DDE_4F15_8F59_B0BE852657DF__INCLUDED_)
