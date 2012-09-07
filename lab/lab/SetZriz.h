#if !defined(AFX_SETZRIZ_H__5FC550AF_1A93_4DEF_A096_6EB610702C11__INCLUDED_)
#define AFX_SETZRIZ_H__5FC550AF_1A93_4DEF_A096_6EB610702C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetZriz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetZriz recordset

class SetZriz : public CRecordset
{
public:
	SetZriz(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetZriz)

// Field/Param Data
	//{{AFX_FIELD(SetZriz, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	CTime	m_DTVYPROB;
	long	m_ID_HID;
	long	m_ID_SHEMA;
	long	m_ID_STAN;
	double	m_tgFi;
	double	m_C;
	double	m_D;
	double	m_H;
	BYTE	m_bSTAT;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, 
		long ID_HID, long ID_SHEMA, long ID_STAN, 
		double tgFi, double C,
		double D, double H);

	long GetNewKeyID();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetZriz)
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

#endif // !defined(AFX_SETZRIZ_H__5FC550AF_1A93_4DEF_A096_6EB610702C11__INCLUDED_)
