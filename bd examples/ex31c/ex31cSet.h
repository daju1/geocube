// ex31cSet.h : interface of the CEx31cSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31CSET_H__6FE9FA91_957D_11D0_AAA2_444553540000__INCLUDED_)
#define AFX_EX31CSET_H__6FE9FA91_957D_11D0_AAA2_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx31cSet : public CRecordset
{
public:
	CEx31cSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEx31cSet)

// Field/Param Data
	//{{AFX_FIELD(CEx31cSet, CRecordset)
	CString	m_InstructorID;
	CString	m_Name;
	CString	m_RoomNo;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31cSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31CSET_H__6FE9FA91_957D_11D0_AAA2_444553540000__INCLUDED_)
