#if !defined(AFX_SETPALJA1_H__C5410C5E_ED9D_4ED2_A591_55E8F0142CA5__INCLUDED_)
#define AFX_SETPALJA1_H__C5410C5E_ED9D_4ED2_A591_55E8F0142CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPalja1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPalja1 recordset

class SetPalja : public CRecordset
{
public:
	SetPalja(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPalja)

// Field/Param Data
	//{{AFX_FIELD(SetPalja1, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	double	m_H;
	double	m_qc;
	double	m_beta1;
	double	m_Rs;
	double	m_fs;
	double	m_beta2;
	double	m_f;
	double	m_RsA;
	double	m_fhu;
	double	m_Fu;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, double H, double qc, double beta1, double Rs, double fs, double beta2, double f, double RsA, double fhu, double Fu);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPalja1)
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

#endif // !defined(AFX_SETPALJA1_H__C5410C5E_ED9D_4ED2_A591_55E8F0142CA5__INCLUDED_)
