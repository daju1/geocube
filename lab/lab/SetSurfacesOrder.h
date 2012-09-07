#if !defined(AFX_SETSURFACESORDER_H__89178731_44FB_4587_A0B5_98FCA4D955FD__INCLUDED_)
#define AFX_SETSURFACESORDER_H__89178731_44FB_4587_A0B5_98FCA4D955FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSurfacesOrder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesOrder recordset

class SetSurfacesOrder : public CRecordset
{
public:
	SetSurfacesOrder(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetSurfacesOrder)

// Field/Param Data
	//{{AFX_FIELD(SetSurfacesOrder, CRecordset)
	long	m_ID_OBJ;
	long	m_NPP;
	BYTE	m_check;
	long	m_ID_SURF;
	BYTE	m_PODOSHVA;
	BYTE	m_check2;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetSurfacesOrder)
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

#endif // !defined(AFX_SETSURFACESORDER_H__89178731_44FB_4587_A0B5_98FCA4D955FD__INCLUDED_)
