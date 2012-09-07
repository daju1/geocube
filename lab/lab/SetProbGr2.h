#if !defined(AFX_SETPROBGR2_H__F07BCEEC_5438_4A35_BD0D_6235ED2CAD46__INCLUDED_)
#define AFX_SETPROBGR2_H__F07BCEEC_5438_4A35_BD0D_6235ED2CAD46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetProbGr2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetProbGr2 recordset

class SetProbGr2 : public CRecordset
{
public:
	SetProbGr2(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetProbGr2)

// Field/Param Data
	//{{AFX_FIELD(SetProbGr2, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	double	m_H;
	long	m_LAB_N;
	long	m_ID_KODPROB;
	CString	m_GRUNT_NAME;
	long	m_ID_GR;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetProbGr2)
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

#endif // !defined(AFX_SETPROBGR2_H__F07BCEEC_5438_4A35_BD0D_6235ED2CAD46__INCLUDED_)
