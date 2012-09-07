#if !defined(AFX_SETT_V_H__52A9FE75_B600_41F8_9F99_E52455B68BDB__INCLUDED_)
#define AFX_SETT_V_H__52A9FE75_B600_41F8_9F99_E52455B68BDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetT_V.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetT_V recordset

class SetT_V : public CRecordset
{
public:
	SetT_V(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetT_V)

// Field/Param Data
	//{{AFX_FIELD(SetT_V, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_ROZRIZ;
	long	m_ID_KT;
	long	m_N;
	long	m_id_ige;
	long	m_pos_L;
	long	m_pos_T;
	long	m_pos_R;
	long	m_pos_B;
	long	m_iPerehid;
	double	m_X;
	double	m_Y;
	BYTE	m_typ;
	CString	m_Name;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetT_V)
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

#endif // !defined(AFX_SETT_V_H__52A9FE75_B600_41F8_9F99_E52455B68BDB__INCLUDED_)
