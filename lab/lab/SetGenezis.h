#if !defined(AFX_SETGENEZIS_H__2F93B8C3_98B1_48CE_8B34_9EF59E601559__INCLUDED_)
#define AFX_SETGENEZIS_H__2F93B8C3_98B1_48CE_8B34_9EF59E601559__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGenezis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGenezis recordset

class SetGenezis : public CRecordset
{
public:
	SetGenezis(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGenezis)

// Field/Param Data
	//{{AFX_FIELD(SetGenezis, CRecordset)
	long	m_ID_GENEZIS;
	CString	m_NAZVA_U;
	CString	m_NAZVA_R;
	long	m_ID_NORMATYV;
	long	m_ID_GRMAIN;
	CString	m_INDEX;
	BYTE	m_R;
	BYTE	m_G;
	BYTE	m_B;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGenezis)
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

#endif // !defined(AFX_SETGENEZIS_H__2F93B8C3_98B1_48CE_8B34_9EF59E601559__INCLUDED_)
