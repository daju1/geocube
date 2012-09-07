#if !defined(AFX_SETSHTAMP_DETAIL_H__54908C2F_BF4D_48D3_A8CB_CCD06A3FA59A__INCLUDED_)
#define AFX_SETSHTAMP_DETAIL_H__54908C2F_BF4D_48D3_A8CB_CCD06A3FA59A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetShtamp_detail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetShtamp_detail recordset

class SetShtamp_detail : public CRecordset
{
public:
	SetShtamp_detail(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetShtamp_detail)

// Field/Param Data
	//{{AFX_FIELD(SetShtamp_detail, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	double	m_SIGMA;
	double	m_DH1;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetShtamp_detail)
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

#endif // !defined(AFX_SETSHTAMP_DETAIL_H__54908C2F_BF4D_48D3_A8CB_CCD06A3FA59A__INCLUDED_)
