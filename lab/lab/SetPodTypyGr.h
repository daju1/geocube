#if !defined(AFX_SETPODTYPYGR_H__3CE40DEF_9D80_45DB_A43F_D793A8C78721__INCLUDED_)
#define AFX_SETPODTYPYGR_H__3CE40DEF_9D80_45DB_A43F_D793A8C78721__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPodTypyGr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGr recordset

class SetPodTypyGr : public CRecordset
{
	bool m_bUserDefined;
public:
	SetPodTypyGr(bool bUserDefined, CDatabase* pDatabase /*= NULL*/);
	DECLARE_DYNAMIC(SetPodTypyGr)

// Field/Param Data
	//{{AFX_FIELD(SetPodTypyGr, CRecordset)
	long	m_TYPGR_PCK;
	long	m_PODTYPGR;
	CString	m_desc;
	//}}AFX_FIELD

	long GetNewPodTypyGr();
	void AddNewRow(long TYPGR_PCK, long PODTYPGR, CString	desc);


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

#endif // !defined(AFX_SETPODTYPYGR_H__3CE40DEF_9D80_45DB_A43F_D793A8C78721__INCLUDED_)
