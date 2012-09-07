#if !defined(AFX_SETIGE_H__710EF1D4_B2C4_4731_B1A3_16D1C3BCA5D0__INCLUDED_)
#define AFX_SETIGE_H__710EF1D4_B2C4_4731_B1A3_16D1C3BCA5D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetIGE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetIGE recordset

class SetIGE : public CRecordset
{
	bool m_bUnEdited;
public:
	SetIGE(bool bUnEdited, CDatabase* pDatabase /*= NULL*/);
	DECLARE_DYNAMIC(SetIGE)

// Field/Param Data
	//{{AFX_FIELD(SetIGE, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_IGE;
	long	m_ID_GR;
	CString	m_IGE;
	double	m_mk;
	double	m_mkz;
	CString	m_strat;
	CString	m_desc0;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_IGE, long ID_GR, CString IGE, double mk, double mkz, CString strat, CString desc0);
	void AddNewRow(long ID_OBJ, long ID_IGE);

	bool Have_ID_IGE(long id_ige);




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetIGE)
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

#endif // !defined(AFX_SETIGE_H__710EF1D4_B2C4_4731_B1A3_16D1C3BCA5D0__INCLUDED_)
