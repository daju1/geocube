#if !defined(AFX_SETROZRIZ_H__E6FD81DD_5227_4949_B02C_2F6E597B2EC5__INCLUDED_)
#define AFX_SETROZRIZ_H__E6FD81DD_5227_4949_B02C_2F6E597B2EC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRozriz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetRozriz recordset

class SetRozriz : public CRecordset
{
public:
	SetRozriz(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetRozriz)

// Field/Param Data
	//{{AFX_FIELD(SetRozriz, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_ROZRIZ;
	long	m_NPP;
	long	m_ID_KT;
	double	m_dxf_x;
	//}}AFX_FIELD
	
	void AddNewRow(long ID_OBJ, long ID_ROZRIZ, long NPP, long ID_KT);
	void AddNewRow(long ID_OBJ, long ID_ROZRIZ, long NPP, long ID_KT, double dxf_x);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetRozriz)
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

#endif // !defined(AFX_SETROZRIZ_H__E6FD81DD_5227_4949_B02C_2F6E597B2EC5__INCLUDED_)
