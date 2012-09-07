#if !defined(AFX_SETPODTYPYGRUSER_H__03766B1C_20EE_4B76_985B_13A26B4CC350__INCLUDED_)
#define AFX_SETPODTYPYGRUSER_H__03766B1C_20EE_4B76_985B_13A26B4CC350__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPodTypyGrUserDef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGrUserDef recordset

class SetPodTypyGrUserDef : public CRecordset
{
public:
	SetPodTypyGrUserDef(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPodTypyGrUserDef)

// Field/Param Data
	//{{AFX_FIELD(SetPodTypyGrUserDef, CRecordset)
	long	m_TYPGR;
	long	m_PODTYPGR;
	CString	m_desc;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPodTypyGrUserDef)
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

#endif // !defined(AFX_SETPODTYPYGRUSER_H__03766B1C_20EE_4B76_985B_13A26B4CC350__INCLUDED_)
