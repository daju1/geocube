#if !defined(AFX_SETGRIDDATASURFACES_H__0587452E_4463_4A02_8419_848AF665379B__INCLUDED_)
#define AFX_SETGRIDDATASURFACES_H__0587452E_4463_4A02_8419_848AF665379B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGriddataSurfaces.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGriddataSurfaces recordset

class SetGriddataSurfaces : public CRecordset
{
public:
	SetGriddataSurfaces(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGriddataSurfaces)

// Field/Param Data
	//{{AFX_FIELD(SetGriddataSurfaces, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_SURF;
	CString	m_NAZVA;
	BYTE	m_PODOSHVA;
	BYTE	m_r;
	BYTE	m_g;
	BYTE	m_b;
	int	m_z_flag;
	long	m_ID_UMPOZ;
	long	m_ID_IGE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGriddataSurfaces)
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

#endif // !defined(AFX_SETGRIDDATASURFACES_H__0587452E_4463_4A02_8419_848AF665379B__INCLUDED_)
