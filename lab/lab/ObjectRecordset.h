#if !defined(AFX_OBJECTRECORDSET_H__362B8795_35AD_4746_8EC5_EBFB8AEACCA7__INCLUDED_)
#define AFX_OBJECTRECORDSET_H__362B8795_35AD_4746_8EC5_EBFB8AEACCA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectRecordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectRecordset recordset

class CObjectRecordset : public CRecordset
{
public:
	CObjectRecordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CObjectRecordset)

// Field/Param Data
	//{{AFX_FIELD(CObjectRecordset, CRecordset)
	long	m_ID_OBJ;
	CString	m_CONTRACT;
	CString	m_NAZVA;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectRecordset)
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

#endif // !defined(AFX_OBJECTRECORDSET_H__362B8795_35AD_4746_8EC5_EBFB8AEACCA7__INCLUDED_)
