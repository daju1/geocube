#if !defined(AFX_SETZRIZ0_H__EA5BADFA_76D0_4730_A127_E421F40594F1__INCLUDED_)
#define AFX_SETZRIZ0_H__EA5BADFA_76D0_4730_A127_E421F40594F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetZriz0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetZriz0 recordset

class SetZriz0 : public CRecordset
{
public:
	SetZriz0(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetZriz0)

// Field/Param Data
	//{{AFX_FIELD(SetZriz0, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	long	m_ID_KOLCA;
	long	m_ID_PHYS_VYPROB;
	double	m_H;
	double	m_D;
	double	m_DH_PO_UPL;
	double	m_M_KOLCA;
	double	m_M_GRUNTA;
	double	m_M_GRUNTA_ZAMOCH;
	double	m_M_GRUNTA_POSLE_UPLOT;
	double	m_M_GRUNTA_POSLE;
	double	m_M_GRUNTA_VYSUSH;
	//}}AFX_FIELD

	long GetMaxPhysVyprobID();
	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, 
						long ID_KOLCA, long ID_PHYS_VYPROB,
						double H, double D, double DH_PO_UPL,						
						double M_KOLCA = 0.0, double M_GRUNTA = 0.0, double M_GRUNTA_ZAMOCH = 0.0, double M_GRUNTA_POSLE_UPLOT = 0.0, double M_GRUNTA_POSLE = 0.0, double M_GRUNTA_VYSUSH = 0.0);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetZriz0)
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

#endif // !defined(AFX_SETZRIZ0_H__EA5BADFA_76D0_4730_A127_E421F40594F1__INCLUDED_)
