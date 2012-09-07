#if !defined(AFX_SETKT_H__986BA74B_E365_4EF6_9EF9_9D036745E993__INCLUDED_)
#define AFX_SETKT_H__986BA74B_E365_4EF6_9EF9_9D036745E993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetKT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetKT recordset

class SetKT : public CRecordset
{
public:
	SetKT(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetKT)

// Field/Param Data
	//{{AFX_FIELD(SetKT, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	CString	m_NAZVA;
	double	m_X;
	double	m_Y;
	double	m_Z;
	long	m_ID_TYP;
	long	m_ID_BUR;
	long	m_D_BUR;
	CTime	m_DTBUR;
	//}}AFX_FIELD

	long GetNewKeyID();
	bool Have_ID_KT(long id_kt);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetKT)
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

#endif // !defined(AFX_SETKT_H__986BA74B_E365_4EF6_9EF9_9D036745E993__INCLUDED_)
