#if !defined(AFX_SETSTZOND1_H__5B11F8E2_E031_4D6F_B66E_58590ED51D47__INCLUDED_)
#define AFX_SETSTZOND1_H__5B11F8E2_E031_4D6F_B66E_58590ED51D47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetStZond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetStZond recordset

class SetStZond : public CRecordset
{
public:
	SetStZond(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetStZond)

// Field/Param Data
	//{{AFX_FIELD(SetStZond, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_NPP;
	long	m_TYPGR;
	double	m_H;
	double	m_q0;
	double	m_f0;
	double	m_dH;
	double	m_fsr;
	BYTE	m_bSTAT;
	long	m_ID_IGE;
	double	m_pck;
	//}}AFX_FIELD

	void AddNewRow_(long ID_OBJ, long ID_KT, long NPP, long TYPGR, double H, double q0, double f0, double dH, double fsr, BYTE bSTAT, long ID_IGE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetStZond)
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

#endif // !defined(AFX_SETSTZOND1_H__5B11F8E2_E031_4D6F_B66E_58590ED51D47__INCLUDED_)
