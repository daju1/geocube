#if !defined(AFX_SETGRANSKLAD1_H__F9B756E8_7DE8_4318_BDCA_5BB3B4513B66__INCLUDED_)
#define AFX_SETGRANSKLAD1_H__F9B756E8_7DE8_4318_BDCA_5BB3B4513B66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGranSklad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGranSklad recordset

class SetGranSklad : public CRecordset
{
public:
	SetGranSklad(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGranSklad)

// Field/Param Data
	//{{AFX_FIELD(SetGranSklad, CRecordset)
	long	m_ID_ROZMIR;
	long	m_ID_UKLAD;
	CString	m_NAZVA_U;
	CString	m_NAZVA_R;
	long	m_ID_UMPOZ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGranSklad)
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

#endif // !defined(AFX_SETGRANSKLAD1_H__F9B756E8_7DE8_4318_BDCA_5BB3B4513B66__INCLUDED_)
