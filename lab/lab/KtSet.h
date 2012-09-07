#if !defined(AFX_KTSET_H__888F0D23_3831_43C2_AA6A_2C2D100E97C9__INCLUDED_)
#define AFX_KTSET_H__888F0D23_3831_43C2_AA6A_2C2D100E97C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KtSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKtSet recordset

class CKtSet : public CRecordset
{
public:
	CKtSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CKtSet)

// Field/Param Data
	//{{AFX_FIELD(CKtSet, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	CString	m_NAZVA;
	double	m_X;
	double	m_Y;
	double	m_Z;
	long	m_ID_TYP;
	long	m_ID_BUR;
	long	m_D_BUR;
	CTime	m_DTBUR;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKtSet)
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

#endif // !defined(AFX_KTSET_H__888F0D23_3831_43C2_AA6A_2C2D100E97C9__INCLUDED_)
