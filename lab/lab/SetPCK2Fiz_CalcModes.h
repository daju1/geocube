#if !defined(AFX_SETPCK2FIZ_CALCMODES_H__6CC3FA82_9F7E_4324_9430_0BC15C4EFEFF__INCLUDED_)
#define AFX_SETPCK2FIZ_CALCMODES_H__6CC3FA82_9F7E_4324_9430_0BC15C4EFEFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPCK2Fiz_CalcModes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcModes recordset

class SetPCK2Fiz_CalcModes : public CRecordset
{
	bool m_bUserDefined;
public:
	SetPCK2Fiz_CalcModes(bool bUserDefined, CDatabase* pDatabase /*= NULL*/);
	DECLARE_DYNAMIC(SetPCK2Fiz_CalcModes)

// Field/Param Data
	//{{AFX_FIELD(SetPCK2Fiz_CalcModes, CRecordset)
	long	m_TYPGR_PCK;
	long	m_PODTYPGR;
	long	m_ID_CALC_PARAM;
	long	m_ID_CALC_METHOD;
	BYTE	m_TAB;
	BYTE	m_VNUTR_TRENIE;
	CString	m_FORMULA;
	CString	m_FOR_TYPZONDS;
	double	m_K0;
	double	m_K1;
	double	m_KLOG;
	//}}AFX_FIELD

	long GetNewCalcMethodID();

	void AddNewRow(long TYPGR_PCK, long PODTYPGR, 
		long ID_CALC_PARAM, long ID_CALC_METHOD,
		BYTE TAB, BYTE VNUTR_TRENIE, CString FORMULA, CString FOR_TYPZONDS,
		double m_K0, double m_K1, double m_KLOG);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPCK2Fiz_CalcModes)
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

#endif // !defined(AFX_SETPCK2FIZ_CALCMODES_H__6CC3FA82_9F7E_4324_9430_0BC15C4EFEFF__INCLUDED_)
