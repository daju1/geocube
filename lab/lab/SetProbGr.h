#if !defined(AFX_SETPROBGR_H__CC350187_2EDB_4329_B851_12DCB4D45223__INCLUDED_)
#define AFX_SETPROBGR_H__CC350187_2EDB_4329_B851_12DCB4D45223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetProbGr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetProbGr recordset

class SetProbGr : public CRecordset
{
public:
	SetProbGr(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetProbGr)

// Field/Param Data
	//{{AFX_FIELD(SetProbGr, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	double	m_H;
	long	m_LAB_N;
	long	m_ID_KODPROB;
	CString m_GRUNT_NAME;
	long	m_ID_GR;
	long	m_ID_IGE;
	//}}AFX_FIELD

	long GetNewKeyID();
	bool Have_LAB_N(long lab_n, long & ID_PROB);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetProbGr)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB,
		double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME);

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB,
		double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME, long ID_IGE);
	
	bool Having_LAB_N_Edit(long lab_n, 
		long ID_OBJ, long ID_KT, long ID_PROB,
		double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME,
		long ID_IGE);

	bool Having_LAB_N_Edit(long lab_n, 
		long ID_OBJ, long ID_KT, long ID_PROB,
		double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME);


// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPROBGR_H__CC350187_2EDB_4329_B851_12DCB4D45223__INCLUDED_)
