#if !defined(AFX_SETFUNDAMENT_TBL_H__B04514E9_8F5A_4A51_B5F4_F6DC7DE7F6CA__INCLUDED_)
#define AFX_SETFUNDAMENT_TBL_H__B04514E9_8F5A_4A51_B5F4_F6DC7DE7F6CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFundament_tbl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetFundament_tbl recordset

class SetFundament_tbl : public CRecordset
{
public:
	SetFundament_tbl(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetFundament_tbl)

// Field/Param Data
	//{{AFX_FIELD(SetFundament_tbl, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PERERIZ;
	long	m_NPP;
	double	m_Z;
	double	m_R;
	double	m_FI;
	CString	m_NAZVA;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetFundament_tbl)
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

#endif // !defined(AFX_SETFUNDAMENT_TBL_H__B04514E9_8F5A_4A51_B5F4_F6DC7DE7F6CA__INCLUDED_)
