#if !defined(AFX_MYLISTCTRL_H__41CE5ADB_BB64_448A_A5DD_379D4CABB3E0__INCLUDED_)
#define AFX_MYLISTCTRL_H__41CE5ADB_BB64_448A_A5DD_379D4CABB3E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
	friend struct ATable;
// Construction
public:
	CMyListCtrl();

// Attributes
public:
	BOOL m_bFullRowSel;
	BOOL m_bClientWidthSel;
// Implementation - client area width
	int m_cxClient;

// Implementation - state icon width
	int m_cxStateImageOffset;
//	afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);

// Implementation - list view colors
	COLORREF m_clrText;
	COLORREF m_clrTextBk;
	COLORREF m_clrBkgnd;
	//afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
//afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);
	static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);

	static CString CMyListCtrl::GetFieldString(CDBVariant & var);
	static CString CMyListCtrl::GetFieldString2(CDBVariant & var);
// Operations
public:
	bool to_fill_colomns;
	void DeleteAllItemsAndColomns();
	void RenewListCtrl();

	virtual BOOL OnInitCtrl();
	virtual void Fill_Ctrl_List(ATable *, CString where, CString order_by);
	virtual void FillCtrlList(CRecordset * pRecordset);
	virtual void DrawDataRow(CRecordset * pRecordset);
protected:
	//CImageList * m_pImageHdrSmall;
	//CImageList * m_pImageList;
	//CImageList * m_pImageListSmall;
	void ModifyHeaderItems(int ncol);
	virtual void FillListCtrl(){}
	void ChangeListCtrlStyle(DWORD dwStyle, BOOL bSetBits);
	BOOL m_bHotCursor;
	HCURSOR m_hStdHotCursor;
	HCURSOR m_hMyHotCursor;
	HICON m_hIcon;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetSelected();
	virtual ~CMyListCtrl();

	// Generated message map functions
//protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnPaint();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__41CE5ADB_BB64_448A_A5DD_379D4CABB3E0__INCLUDED_)
