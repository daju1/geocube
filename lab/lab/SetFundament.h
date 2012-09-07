#if !defined(AFX_SETFUNDAMENT_H__0BEC1EA3_EFDD_41FA_B396_868CE2D6D14F__INCLUDED_)
#define AFX_SETFUNDAMENT_H__0BEC1EA3_EFDD_41FA_B396_868CE2D6D14F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFundament.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetFundament recordset

class SetFundament : public CRecordset
{
public:
	SetFundament(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetFundament)

// Field/Param Data
	//{{AFX_FIELD(SetFundament, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PERERIZ;
	double	m_Z;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetFundament)
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

#endif // !defined(AFX_SETFUNDAMENT_H__0BEC1EA3_EFDD_41FA_B396_868CE2D6D14F__INCLUDED_)
