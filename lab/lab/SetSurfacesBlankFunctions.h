#if !defined(AFX_SETSURFACESBLANKFUNCTIONS_H__923774AD_D267_4766_8394_052065D0354F__INCLUDED_)
#define AFX_SETSURFACESBLANKFUNCTIONS_H__923774AD_D267_4766_8394_052065D0354F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSurfacesBlankFunctions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesBlankFunctions recordset

class SetSurfacesBlankFunctions : public CRecordset
{
public:
	SetSurfacesBlankFunctions(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetSurfacesBlankFunctions)

// Field/Param Data
	//{{AFX_FIELD(SetSurfacesBlankFunctions, CRecordset)
	long	m_ID_OBJ;
	//long	m_ID_ITEM;
	long	m_ID_SURF_OBJ;
	long	m_ID_SURF_PARAM;
	BYTE	m_ID_BLANK_FUN;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetSurfacesBlankFunctions)
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

#endif // !defined(AFX_SETSURFACESBLANKFUNCTIONS_H__923774AD_D267_4766_8394_052065D0354F__INCLUDED_)
