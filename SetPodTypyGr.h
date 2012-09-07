#if !defined(AFX_SETPODTYPYGR_H__4E42E1DA_B6B3_4BAB_91B1_3A0DC2E46446__INCLUDED_)
#define AFX_SETPODTYPYGR_H__4E42E1DA_B6B3_4BAB_91B1_3A0DC2E46446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPodTypyGr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGr recordset

class SetPodTypyGr : public CRecordset
{
public:
	SetPodTypyGr(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPodTypyGr)

// Field/Param Data
	//{{AFX_FIELD(SetPodTypyGr, CRecordset)
	long	m_TYPGR;
	long	m_PODTYPGR;
	CString	m_desc;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPodTypyGr)
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

#endif // !defined(AFX_SETPODTYPYGR_H__4E42E1DA_B6B3_4BAB_91B1_3A0DC2E46446__INCLUDED_)
