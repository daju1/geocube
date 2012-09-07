#if !defined(AFX_SETPTPALJA_H__72374C49_ABB9_4E01_B507_71CCF319976C__INCLUDED_)
#define AFX_SETPTPALJA_H__72374C49_ABB9_4E01_B507_71CCF319976C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPtPalja.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPtPalja recordset

class SetPtPalja : public CRecordset
{
public:
	SetPtPalja(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPtPalja)

// Field/Param Data
	//{{AFX_FIELD(SetPtPalja, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_TYP;
	double	m_Pereriz_X;
	double	m_Pereriz_Y;
	double	m_A;
	double	m_u;
	double	m_GLYB;
	double	m_RsA;
	double	m_fhu;
	double	m_PZ;
	long	m_ID_SNIP;
	double	m_Fu;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_TYP, double Pereriz_X, double Pereriz_Y, double A, double u, double GLYB, double RsA, double fhu, double PZ, long ID_SNIP, double Fu);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPtPalja)
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

#endif // !defined(AFX_SETPTPALJA_H__72374C49_ABB9_4E01_B507_71CCF319976C__INCLUDED_)
