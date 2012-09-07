#if !defined(AFX_SETPTSTZOND_H__0FFCE20E_2416_45A1_82B1_1B7E2DD772C1__INCLUDED_)
#define AFX_SETPTSTZOND_H__0FFCE20E_2416_45A1_82B1_1B7E2DD772C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPtStZond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPtStZond recordset

class SetPtStZond : public CRecordset
{
public:
	SetPtStZond(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPtStZond)

// Field/Param Data
	//{{AFX_FIELD(SetPtStZond, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_UST;
	double	m_GLYB;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_UST, double GLYB);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPtStZond)
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

#endif // !defined(AFX_SETPTSTZOND_H__0FFCE20E_2416_45A1_82B1_1B7E2DD772C1__INCLUDED_)
