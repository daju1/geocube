#if !defined(AFX_SETWOPT_H__0B201A4A_C8DB_458E_A5FF_6ACBE3C9C52B__INCLUDED_)
#define AFX_SETWOPT_H__0B201A4A_C8DB_458E_A5FF_6ACBE3C9C52B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetWopt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetWopt recordset

class SetWopt : public CRecordset
{
public:
	SetWopt(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetWopt)

// Field/Param Data
	//{{AFX_FIELD(SetWopt, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	CTime	m_DTVYPROB;
	double	m_Wopt;
	double	m_Rod_max;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetWopt)
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

#endif // !defined(AFX_SETWOPT_H__0B201A4A_C8DB_458E_A5FF_6ACBE3C9C52B__INCLUDED_)
