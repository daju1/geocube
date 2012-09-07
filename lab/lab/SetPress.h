#if !defined(AFX_SETPRESS_H__44DEE4A9_5EAA_4FAE_878B_F7D415E9F1C0__INCLUDED_)
#define AFX_SETPRESS_H__44DEE4A9_5EAA_4FAE_878B_F7D415E9F1C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPress recordset

class SetPress : public CRecordset
{
public:
	SetPress(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPress)

// Field/Param Data
	//{{AFX_FIELD(SetPress, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPress)
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

#endif // !defined(AFX_SETPRESS_H__44DEE4A9_5EAA_4FAE_878B_F7D415E9F1C0__INCLUDED_)
