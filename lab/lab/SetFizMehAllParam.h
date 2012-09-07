#if !defined(AFX_SETFIZMEHALLPARAM_H__319479EC_0898_41D9_8273_526F71D918F9__INCLUDED_)
#define AFX_SETFIZMEHALLPARAM_H__319479EC_0898_41D9_8273_526F71D918F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFizMehAllParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetFizMehAllParam recordset

class SetFizMehAllParam : public CRecordset
{
public:
	SetFizMehAllParam(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetFizMehAllParam)

// Field/Param Data
	//{{AFX_FIELD(SetFizMehAllParam, CRecordset)
	long	m_ID_PARAM;
	CString	m_NAZVA_U;
	CString	m_NAZVA_R;
	BYTE	m_bDEFAULT;
	BYTE	m_bIN;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetFizMehAllParam)
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

#endif // !defined(AFX_SETFIZMEHALLPARAM_H__319479EC_0898_41D9_8273_526F71D918F9__INCLUDED_)
