#if !defined(AFX_SETCONSOBJ_H__5624C6ED_6C34_4371_9BF0_E3DDC532B5F2__INCLUDED_)
#define AFX_SETCONSOBJ_H__5624C6ED_6C34_4371_9BF0_E3DDC532B5F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetConsObj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetConsObj recordset

class SetConsObj : public CRecordset
{
public:
	SetConsObj(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetConsObj)

// Field/Param Data
	//{{AFX_FIELD(SetConsObj, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_CONSIST;
	double	m_H0;
	double	m_H1;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetConsObj)
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

#endif // !defined(AFX_SETCONSOBJ_H__5624C6ED_6C34_4371_9BF0_E3DDC532B5F2__INCLUDED_)
