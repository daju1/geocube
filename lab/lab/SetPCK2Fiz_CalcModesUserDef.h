#if !defined(AFX_SETPCK2FIZ_USERCALCMODES_H__DC906C8A_778C_44B5_ADCE_CCB59F6FF742__INCLUDED_)
#define AFX_SETPCK2FIZ_USERCALCMODES_H__DC906C8A_778C_44B5_ADCE_CCB59F6FF742__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPCK2Fiz_CalcModesUserDef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcModesUserDef recordset

class SetPCK2Fiz_CalcModesUserDef : public CRecordset
{
public:
	SetPCK2Fiz_CalcModesUserDef(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPCK2Fiz_CalcModesUserDef)

// Field/Param Data
	//{{AFX_FIELD(SetPCK2Fiz_CalcModesUserDef, CRecordset)
	long	m_TYPGR;
	long	m_PODTYPGR;
	long	m_ID_CALC_PARAM;
	long	m_ID_CALC_METHOD;
	BYTE	m_VNUTR_TRENIE;
	CString	m_FORMULA;
	CString	m_FOR_TYPZONDS;
	double	m_K0;
	double	m_K1;
	double	m_KLOG;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPCK2Fiz_CalcModesUserDef)
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

#endif // !defined(AFX_SETPCK2FIZ_USERCALCMODES_H__DC906C8A_778C_44B5_ADCE_CCB59F6FF742__INCLUDED_)
