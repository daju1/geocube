#if !defined(AFX_SETCILCE0_H__D08AC4D4_9BFC_4C99_886A_DAD344CB61A1__INCLUDED_)
#define AFX_SETCILCE0_H__D08AC4D4_9BFC_4C99_886A_DAD344CB61A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCilce0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetCilce0 recordset

class SetCilce0 : public CRecordset
{
public:
	SetCilce0(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetCilce0)

// Field/Param Data
	//{{AFX_FIELD(SetCilce0, CRecordset)
	long	m_ID_OBJ;
	double	m_M_GRUNTA;
	double	m_M_GRUNTA_POSLE;
	double	m_M_GRUNTA_VYSUSH;
	double	m_M_GRUNTA_ZAMOCH;
	double	m_M_KOLCA;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	long	m_ID_KOLCA;
	long	m_ID_PHYS_VYPROB;
	double	m_H;
	double	m_D;
	//}}AFX_FIELD

	long GetMaxPhysVyprobID();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetCilce0)
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

#endif // !defined(AFX_SETCILCE0_H__D08AC4D4_9BFC_4C99_886A_DAD344CB61A1__INCLUDED_)
