// ex31bSet.h : interface of the CEx31bSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31BSET_H__A080553A_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)
#define AFX_EX31BSET_H__A080553A_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEx31bSet : public CRecordset
{
public:
	CEx31bSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEx31bSet)

// Field/Param Data
	//{{AFX_FIELD(CEx31bSet, CRecordset)
	CString	m_InstructorID;
	CString	m_Name;
	CString	m_RoomNo;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31bSet)
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
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31BSET_H__A080553A_01E1_11D2_9E4D_00A0C9B1AF6D__INCLUDED_)

