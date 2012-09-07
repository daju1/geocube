#if !defined(AFX_SETOBJECT_H__B7B4C722_1715_4FF4_813A_B67A7CC1BB6D__INCLUDED_)
#define AFX_SETOBJECT_H__B7B4C722_1715_4FF4_813A_B67A7CC1BB6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetObject.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetObject recordset

class SetObject : public CRecordset
{
public:
	SetObject(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetObject)

// Field/Param Data
	//{{AFX_FIELD(SetObject, CRecordset)
	long	m_ID_OBJ;
	CString	m_CONTRACT;
	CString	m_NAZVA;
	double	m_zoomCoefXYZ;
	double	m_zoomCoefXY;
	//}}AFX_FIELD

	long GetNewKeyID();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetObject)
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

#endif // !defined(AFX_SETOBJECT_H__B7B4C722_1715_4FF4_813A_B67A7CC1BB6D__INCLUDED_)
