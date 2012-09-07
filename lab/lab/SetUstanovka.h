#if !defined(AFX_SETUSTANOVKA_H__C7B5B0F5_E836_412A_8EB5_40D69CE62947__INCLUDED_)
#define AFX_SETUSTANOVKA_H__C7B5B0F5_E836_412A_8EB5_40D69CE62947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUstanovka.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetUstanovka recordset

class SetUstanovka : public CRecordset
{
public:
	SetUstanovka(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetUstanovka)

// Field/Param Data
	//{{AFX_FIELD(SetUstanovka, CRecordset)
	long	m_ID_UST;
	CString	m_NAZVA;
	long	m_TYP_ZOND;
	long	m_N_SHEMA;
	double	m_Kg;
	double	m_Kf;
	double	m_Bg;
	double	m_Bf;
	double	m_Shtanga_d;
	//}}AFX_FIELD

	void AddNewRow(long ID_UST, CString	NAZVA, long	TYP_ZOND,
		long N_SHEMA, double Kg, double Kf,
		double Bg, double Bf, double Shtanga_d);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetUstanovka)
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

#endif // !defined(AFX_SETUSTANOVKA_H__C7B5B0F5_E836_412A_8EB5_40D69CE62947__INCLUDED_)
