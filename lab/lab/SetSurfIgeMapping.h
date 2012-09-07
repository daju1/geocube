#if !defined(AFX_SetSurfIgeMapping_H__A5E2A781_33CA_43C7_B725_3A7E743823E3__INCLUDED_)
#define AFX_SetSurfIgeMapping_H__A5E2A781_33CA_43C7_B725_3A7E743823E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSurfIgeMapping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetSurfIgeMapping recordset

class SetSurfIgeMapping : public CRecordset
{
public:
	SetSurfIgeMapping(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetSurfIgeMapping)

// Field/Param Data
	//{{AFX_FIELD(SetSurfIgeMapping, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_SURF;
	long	m_ID_IGE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetSurfIgeMapping)
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

#endif // !defined(AFX_SetSurfIgeMapping_H__A5E2A781_33CA_43C7_B725_3A7E743823E3__INCLUDED_)
