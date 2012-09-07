#if !defined(AFX_SETZRIZ_TBL_H__309C75CD_840B_4BC4_92F5_AAA60C5E2742__INCLUDED_)
#define AFX_SETZRIZ_TBL_H__309C75CD_840B_4BC4_92F5_AAA60C5E2742__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetZriz_tbl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetZriz_tbl recordset

class SetZriz_tbl : public CRecordset
{
public:
	SetZriz_tbl(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetZriz_tbl)

// Field/Param Data
	//{{AFX_FIELD(SetZriz_tbl, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	long	m_ID_KOLCA;
	double	m_SIGMA;
	double	m_TAU;
	double	m_W_do;
	double	m_Ro_do;
	double	m_W_po_upl;
	double	m_Ro_po_upl;
	double	m_W_after;
	double	m_Ro_after;
	BYTE	m_bSTAT;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, long ID_KOLCA, 
		double SIGMA, double TAU,
		double W_do, double Ro_do, 
		double W_po_upl, double Ro_po_upl, 
		double W_after, double Ro_after);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetZriz_tbl)
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

#endif // !defined(AFX_SETZRIZ_TBL_H__309C75CD_840B_4BC4_92F5_AAA60C5E2742__INCLUDED_)
