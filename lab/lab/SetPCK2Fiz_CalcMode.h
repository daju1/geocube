#if !defined(AFX_SETPCK2FIZ_CALCMODE_H__98EE59E1_C38C_4A7D_BF85_ED5815E07B30__INCLUDED_)
#define AFX_SETPCK2FIZ_CALCMODE_H__98EE59E1_C38C_4A7D_BF85_ED5815E07B30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPCK2Fiz_CalcMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcMode recordset

class SetPCK2Fiz_CalcMode : public CRecordset
{
public:
	SetPCK2Fiz_CalcMode(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPCK2Fiz_CalcMode)

// Field/Param Data
	//{{AFX_FIELD(SetPCK2Fiz_CalcMode, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_IGE;
	long	m_ID_CALC_PARAM;
	BYTE	m_ID_METHODY;
	long	m_ID_CALC_METHOD;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPCK2Fiz_CalcMode)
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

#endif // !defined(AFX_SETPCK2FIZ_CALCMODE_H__98EE59E1_C38C_4A7D_BF85_ED5815E07B30__INCLUDED_)
