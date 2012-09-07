#if !defined(AFX_SETROZRIZY1_H__CD5C81BD_4515_485E_A7D7_D866D51E07A8__INCLUDED_)
#define AFX_SETROZRIZY1_H__CD5C81BD_4515_485E_A7D7_D866D51E07A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRozrizy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetRozrizy recordset

class SetRozrizy : public CRecordset
{
public:
	SetRozrizy(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetRozrizy)

// Field/Param Data
	//{{AFX_FIELD(SetRozrizy, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_ROZRIZ;
	CString	m_NOMER;
	BYTE	m_has_dxf;
	CString	m_fn_dxf;
	BYTE	m_acad_yscale_loaded;
	double	m_z1w;
	double	m_y1a;
	double	m_z2w;
	double	m_y2a;
	//}}AFX_FIELD

	long GetNewKeyID();
	void AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER);
	void AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER, CString fn_dxf, double z1w, double y1a, double z2w, double y2a);
	void AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER, CString fn_dxf);
	void AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER, double z1w, double y1a, double z2w, double y2a);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetRozrizy)
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

#endif // !defined(AFX_SETROZRIZY1_H__CD5C81BD_4515_485E_A7D7_D866D51E07A8__INCLUDED_)
