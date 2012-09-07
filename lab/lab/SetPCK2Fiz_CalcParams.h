#if !defined(AFX_SETPCK2FIZ_CALCPARAMS_H__FEA57B68_4FCD_4489_A825_CB78474B6617__INCLUDED_)
#define AFX_SETPCK2FIZ_CALCPARAMS_H__FEA57B68_4FCD_4489_A825_CB78474B6617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPCK2Fiz_CalcParams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcParams recordset

class SetPCK2Fiz_CalcParams : public CRecordset
{
public:
	SetPCK2Fiz_CalcParams(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPCK2Fiz_CalcParams)

// Field/Param Data
	//{{AFX_FIELD(SetPCK2Fiz_CalcParams, CRecordset)
	long	m_ID_CALC_PARAM;
	CString	m_CALC_PARAM;
	CString	m_desc;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPCK2Fiz_CalcParams)
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

#endif // !defined(AFX_SETPCK2FIZ_CALCPARAMS_H__FEA57B68_4FCD_4489_A825_CB78474B6617__INCLUDED_)
