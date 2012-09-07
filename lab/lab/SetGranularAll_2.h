#if !defined(AFX_SETGRANULARALL_2_H__05E83AB6_4A04_4D35_881E_37EA4C3FD3D6__INCLUDED_)
#define AFX_SETGRANULARALL_2_H__05E83AB6_4A04_4D35_881E_37EA4C3FD3D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGranularAll_2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGranularAll_2 recordset

class SetGranularAll_2 : public CRecordset
{
public:
	SetGranularAll_2(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGranularAll_2)

// Field/Param Data
	//{{AFX_FIELD(SetGranularAll_2, CRecordset)
	long	m_ID_GRAN;
	CString	m_NAZVA;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGranularAll_2)
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

#endif // !defined(AFX_SETGRANULARALL_2_H__05E83AB6_4A04_4D35_881E_37EA4C3FD3D6__INCLUDED_)
