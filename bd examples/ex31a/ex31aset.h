#if !defined(AFX_EX31ASET_H__4C4C252E_6EAD_11D0_8609_F283035DC070__INCLUDED_)
#define AFX_EX31ASET_H__4C4C252E_6EAD_11D0_8609_F283035DC070__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ex31aset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx31aSet recordset

class CEx31aSet : public CRecordset
{
public:
	CEx31aSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEx31aSet)

// Field/Param Data
	//{{AFX_FIELD(CEx31aSet, CRecordset)
	long	m_StudentID;
	CString	m_Name;
	int		m_GradYear;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31aSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31ASET_H__4C4C252E_6EAD_11D0_8609_F283035DC070__INCLUDED_)
