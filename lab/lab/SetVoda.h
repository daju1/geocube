#if !defined(AFX_SETVODA_H__3864FF90_331C_4254_8E52_4D48BF4496CF__INCLUDED_)
#define AFX_SETVODA_H__3864FF90_331C_4254_8E52_4D48BF4496CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetVoda.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetVoda recordset

class SetVoda : public CRecordset
{
public:
	SetVoda(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetVoda)

// Field/Param Data
	//{{AFX_FIELD(SetVoda, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_HORIZONT;
	double	m_HV_Z;
	double	m_HV_V;
	CTime	m_DV;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long HORIZONT, double HV_Z, double HV_V, CTime time);
	void AddNewRow(long ID_OBJ, long ID_KT, long HORIZONT, double HV_Z, double HV_V);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetVoda)
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

#endif // !defined(AFX_SETVODA_H__3864FF90_331C_4254_8E52_4D48BF4496CF__INCLUDED_)
