#if !defined(AFX_SETPRES_H__93F6D650_7F69_406D_AFA3_4E11F41F0EB8__INCLUDED_)
#define AFX_SETPRES_H__93F6D650_7F69_406D_AFA3_4E11F41F0EB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPres.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPres recordset

class SetPres : public CRecordset
{
public:
	SetPres(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPres)

// Field/Param Data
	//{{AFX_FIELD(SetPres, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	CTime	m_DTVYPROB;
	double	m_L;
	double	m_b;
	double	m_P0;
	double	m_S0;
	double	m_Pn;
	double	m_Sn;
	double	m_nju;
	double	m_K;
	double	m_w;
	BYTE	m_bSTAT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPres)
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

#endif // !defined(AFX_SETPRES_H__93F6D650_7F69_406D_AFA3_4E11F41F0EB8__INCLUDED_)
