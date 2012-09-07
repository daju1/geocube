#if !defined(AFX_SETFIZMEHPARAM_H__FDEA0BA4_4AD9_443A_B5A0_58954F882B8D__INCLUDED_)
#define AFX_SETFIZMEHPARAM_H__FDEA0BA4_4AD9_443A_B5A0_58954F882B8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFizMehParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetFizMehParam recordset

class SetFizMehParam : public CRecordset
{
public:
	SetFizMehParam(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetFizMehParam)

// Field/Param Data
	//{{AFX_FIELD(SetFizMehParam, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_PARAM;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetFizMehParam)
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

#endif // !defined(AFX_SETFIZMEHPARAM_H__FDEA0BA4_4AD9_443A_B5A0_58954F882B8D__INCLUDED_)
