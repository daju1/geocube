#if !defined(AFX_SETLITO_H__9B01F887_0DA6_441E_A108_307CD6742DB5__INCLUDED_)
#define AFX_SETLITO_H__9B01F887_0DA6_441E_A108_307CD6742DB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetLito.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetLito recordset

class SetLito : public CRecordset
{
	bool m_bUnEdited;
public:
	SetLito(bool bUnEdited, CDatabase* pDatabase/* = NULL*/);
	DECLARE_DYNAMIC(SetLito)

// Field/Param Data
	//{{AFX_FIELD(SetLito, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_IGE;
	double	m_H0;
	double	m_H1;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_IGER, double h0, double h1);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetLito)
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

#endif // !defined(AFX_SETLITO_H__9B01F887_0DA6_441E_A108_307CD6742DB5__INCLUDED_)
