#if !defined(AFX_SETGRMAIN_H__189DD42B_D557_40FC_9A52_2019625B82C4__INCLUDED_)
#define AFX_SETGRMAIN_H__189DD42B_D557_40FC_9A52_2019625B82C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGrMain.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGrMain recordset

class SetGrMain : public CRecordset
{
public:
	SetGrMain(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGrMain)

// Field/Param Data
	//{{AFX_FIELD(SetGrMain, CRecordset)
	long	m_ID_GRMAIN;
	CString	m_NAZVA_U;
	CString	m_NAZVA_R;
	long	m_TYPGR;
	long	m_TYPGR_PCK;
	long	m_ID_NORMATYV;
	long	m_ID_GRCONS;
	long	m_ID_NJU;
	long	m_ID_UMPOZ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGrMain)
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

#endif // !defined(AFX_SETGRMAIN_H__189DD42B_D557_40FC_9A52_2019625B82C4__INCLUDED_)
