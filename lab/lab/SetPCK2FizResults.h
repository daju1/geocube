#if !defined(AFX_SETPCK2FIZRESULTS_H__A70F4466_40E1_4133_9EEC_27B00CF69E85__INCLUDED_)
#define AFX_SETPCK2FIZRESULTS_H__A70F4466_40E1_4133_9EEC_27B00CF69E85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPCK2FizResults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPCK2FizResults recordset

class SetPCK2FizResults : public CRecordset
{
public:
	SetPCK2FizResults(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPCK2FizResults)

// Field/Param Data
	//{{AFX_FIELD(SetPCK2FizResults, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_NPP;
	long	m_ID_CALC_PARAM;
	double	m_param;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long NPP, long ID_CALC_PARAM, double param);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPCK2FizResults)
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

#endif // !defined(AFX_SETPCK2FIZRESULTS_H__A70F4466_40E1_4133_9EEC_27B00CF69E85__INCLUDED_)
