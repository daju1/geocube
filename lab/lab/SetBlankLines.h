#if !defined(AFX_SETBLANKLINES_H__323A57A7_B58C_4358_BF33_AFAB841A0307__INCLUDED_)
#define AFX_SETBLANKLINES_H__323A57A7_B58C_4358_BF33_AFAB841A0307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetBlankLines.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetBlankLines recordset

class SetBlankLines : public CRecordset
{
public:
	SetBlankLines(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetBlankLines)

// Field/Param Data
	//{{AFX_FIELD(SetBlankLines, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_SURF;
	long	m_ID_LINE;
	long	m_NPP;
	double	m_X;
	double	m_Y;
	double	m_Z;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetBlankLines)
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

#endif // !defined(AFX_SETBLANKLINES_H__323A57A7_B58C_4358_BF33_AFAB841A0307__INCLUDED_)
