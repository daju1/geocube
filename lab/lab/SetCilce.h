#if !defined(AFX_SETCILCE_H__209F9D4E_9AC9_4AF4_8627_9A1D8A6DCEE9__INCLUDED_)
#define AFX_SETCILCE_H__209F9D4E_9AC9_4AF4_8627_9A1D8A6DCEE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCilce.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetCilce recordset

class SetCilce : public CRecordset
{
public:
	SetCilce(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetCilce)

// Field/Param Data
	//{{AFX_FIELD(SetCilce, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	CTime	m_DTVYPROB;
	double	m_H;
	double	m_D;
	double	m_ES_L1;
	double	m_ES_R1;
	double	m_ES_L2;
	double	m_ES_R2;
	double	m_nju;
	double	m_nju_z;
	double	m_m01;
	double	m_E1;
	double	m_m02;
	double	m_E2;
	double	m_m01v;
	double	m_E1v;
	double	m_m02v;
	double	m_E2v;
	BYTE	m_ID_METHOD;
	BYTE	m_bSTAT;
	BYTE	m_bStatV;
	//}}AFX_FIELD

	long GetNewKeyID();
	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB,
		double H, double D,	double ES_L1, double ES_R1, double ES_L2, double ES_R2,
		double nju,	double nju_z, 
		double m01, double E1, double m02, double E2,
		double m01v, double E1v, double m02v, double E2v, 
		BYTE ID_METHOD, BYTE bSTAT, BYTE bStatV);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetCilce)
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

#endif // !defined(AFX_SETCILCE_H__209F9D4E_9AC9_4AF4_8627_9A1D8A6DCEE9__INCLUDED_)
