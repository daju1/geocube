#if !defined(AFX_SETPCK2FIZTABLE_H__14C4E3EA_4368_44EF_BD43_439B654C1919__INCLUDED_)
#define AFX_SETPCK2FIZTABLE_H__14C4E3EA_4368_44EF_BD43_439B654C1919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPCK2FizTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPCK2FizTable recordset

class SetPCK2FizTable : public CRecordset
{
	bool m_bUserDefined;
public:
	SetPCK2FizTable(bool bUserDefined, CDatabase* pDatabase/* = NULL*/);
	DECLARE_DYNAMIC(SetPCK2FizTable)

// Field/Param Data
	//{{AFX_FIELD(SetPCK2FizTable, CRecordset)
	long	m_ID_CALC_METHOD;
	double	m_PCK;
	double	m_PCB;
	double	m_PAR;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPCK2FizTable)
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
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPCK2FIZTABLE_H__14C4E3EA_4368_44EF_BD43_439B654C1919__INCLUDED_)
