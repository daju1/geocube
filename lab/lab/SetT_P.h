#if !defined(AFX_SETT_P_H__743B351B_FC6C_43CB_96F8_73E9886261FB__INCLUDED_)
#define AFX_SETT_P_H__743B351B_FC6C_43CB_96F8_73E9886261FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetT_P.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetT_P recordset

class SetT_P : public CRecordset
{
public:
	SetT_P(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetT_P)

// Field/Param Data
	//{{AFX_FIELD(SetT_P, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_ROZRIZ;
	long	m_N;
	long	m_iv;
	long	m_v;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetT_P)
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

#endif // !defined(AFX_SETT_P_H__743B351B_FC6C_43CB_96F8_73E9886261FB__INCLUDED_)
