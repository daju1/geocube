#if !defined(AFX_SETGEOTABLES_H__95CB56EE_7CE0_4A32_AA92_DECCD0F846DA__INCLUDED_)
#define AFX_SETGEOTABLES_H__95CB56EE_7CE0_4A32_AA92_DECCD0F846DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGeoTables.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGeoTables recordset

class SetGeoTables : public CRecordset
{
public:
	SetGeoTables(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGeoTables)

// Field/Param Data
	//{{AFX_FIELD(SetGeoTables, CRecordset)
	long	m_ID;
	CString	m_NAZVA;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGeoTables)
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

#endif // !defined(AFX_SETGEOTABLES_H__95CB56EE_7CE0_4A32_AA92_DECCD0F846DA__INCLUDED_)
