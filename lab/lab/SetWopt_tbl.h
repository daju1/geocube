#if !defined(AFX_SETWOPT_TBL_H__F02CEE63_30BD_4E4F_90B9_B303A3E6F41B__INCLUDED_)
#define AFX_SETWOPT_TBL_H__F02CEE63_30BD_4E4F_90B9_B303A3E6F41B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetWopt_tbl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetWopt_tbl recordset

class SetWopt_tbl : public CRecordset
{
public:
	SetWopt_tbl(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetWopt_tbl)

// Field/Param Data
	//{{AFX_FIELD(SetWopt_tbl, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	double	m_W;
	double	m_Ro;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetWopt_tbl)
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

#endif // !defined(AFX_SETWOPT_TBL_H__F02CEE63_30BD_4E4F_90B9_B303A3E6F41B__INCLUDED_)
