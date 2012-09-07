#if !defined(AFX_SETCHEMVD_TBL_H__280C7D22_27DB_47A2_9B47_A93E8C22DBDA__INCLUDED_)
#define AFX_SETCHEMVD_TBL_H__280C7D22_27DB_47A2_9B47_A93E8C22DBDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetChemVD_tbl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetChemVD_tbl recordset

class SetChemVD_tbl : public CRecordset
{
public:
	SetChemVD_tbl(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetChemVD_tbl)

// Field/Param Data
	//{{AFX_FIELD(SetChemVD_tbl, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_HORIZONT;
	long	m_ID_CHEM;
	double	m_MG;
	double	m_MGECV;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetChemVD_tbl)
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

#endif // !defined(AFX_SETCHEMVD_TBL_H__280C7D22_27DB_47A2_9B47_A93E8C22DBDA__INCLUDED_)
