#if !defined(AFX_SETSHTAMP_H__91DBC316_156F_434F_8A50_7202951E4687__INCLUDED_)
#define AFX_SETSHTAMP_H__91DBC316_156F_434F_8A50_7202951E4687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetShtamp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetShtamp recordset

class SetShtamp : public CRecordset
{
public:
	SetShtamp(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetShtamp)

// Field/Param Data
	//{{AFX_FIELD(SetShtamp, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	CTime	m_DTVYPROB;
	double	m_TRYVALIST;
	double	m_D;
	double	m_P0;
	double	m_S0;
	double	m_Pn;
	double	m_Sn;
	double	m_nju;
	double	m_KP;
	double	m_K;
	double	m_q;
	BYTE	m_ID_METHOD;
	BYTE	m_bSTAT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetShtamp)
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

#endif // !defined(AFX_SETSHTAMP_H__91DBC316_156F_434F_8A50_7202951E4687__INCLUDED_)
