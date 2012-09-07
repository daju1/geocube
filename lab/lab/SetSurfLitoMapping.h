#if !defined(AFX_SETSURFLITOMAPPING_H__99BD4C8F_19C7_44EC_A5A3_1FB63E325EBB__INCLUDED_)
#define AFX_SETSURFLITOMAPPING_H__99BD4C8F_19C7_44EC_A5A3_1FB63E325EBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSurfLitoMapping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetSurfLitoMapping recordset

class SetSurfLitoMapping : public CRecordset
{
public:
	SetSurfLitoMapping(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetSurfLitoMapping)

// Field/Param Data
	//{{AFX_FIELD(SetSurfLitoMapping, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_SURF;
	long	m_ID_IGE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetSurfLitoMapping)
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

#endif // !defined(AFX_SETSURFLITOMAPPING_H__99BD4C8F_19C7_44EC_A5A3_1FB63E325EBB__INCLUDED_)
