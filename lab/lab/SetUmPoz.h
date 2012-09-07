#if !defined(AFX_SETUMPOZ_H__432C86B3_E64E_45CB_81C8_3CBBB1C9F33E__INCLUDED_)
#define AFX_SETUMPOZ_H__432C86B3_E64E_45CB_81C8_3CBBB1C9F33E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUmPoz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetUmPoz recordset

class SetUmPoz : public CRecordset
{
public:
	SetUmPoz(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetUmPoz)

// Field/Param Data
	//{{AFX_FIELD(SetUmPoz, CRecordset)
	long	m_ID_UMPOZ;
	CString	m_UMPOZ;
	CString	m_HATCHACAD;
	double	m_Angle;
	double	m_Scale;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetUmPoz)
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

#endif // !defined(AFX_SETUMPOZ_H__432C86B3_E64E_45CB_81C8_3CBBB1C9F33E__INCLUDED_)
