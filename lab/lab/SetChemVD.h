#if !defined(AFX_SETCHEMVD_H__6F5FE5EF_AA23_4CFB_8146_2E9CFC973ABF__INCLUDED_)
#define AFX_SETCHEMVD_H__6F5FE5EF_AA23_4CFB_8146_2E9CFC973ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetChemVD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetChemVD recordset

class SetChemVD : public CRecordset
{
public:
	SetChemVD(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetChemVD)

// Field/Param Data
	//{{AFX_FIELD(SetChemVD, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_HORIZONT;
	CTime	m_DTLAB;
	CString	m_PIB;
	CString	m_COLOR;
	CString	m_PROZORIST;
	CString	m_OSAD;
	CString	m_ZAPAH;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetChemVD)
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

#endif // !defined(AFX_SETCHEMVD_H__6F5FE5EF_AA23_4CFB_8146_2E9CFC973ABF__INCLUDED_)
