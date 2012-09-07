#if !defined(AFX_SETPRESS_TBL_H__08840682_F055_4839_87D4_AB735AA29441__INCLUDED_)
#define AFX_SETPRESS_TBL_H__08840682_F055_4839_87D4_AB735AA29441__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPress_tbl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPress_tbl recordset

class SetPress_tbl : public CRecordset
{
public:
	SetPress_tbl(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPress_tbl)

// Field/Param Data
	//{{AFX_FIELD(SetPress_tbl, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	double	m_SIGMA;
	double	m_DH1;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPress_tbl)
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

#endif // !defined(AFX_SETPRESS_TBL_H__08840682_F055_4839_87D4_AB735AA29441__INCLUDED_)
