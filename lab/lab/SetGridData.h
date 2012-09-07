#if !defined(AFX_SETGRIDDATA_H__8D753927_80F8_4DB2_8498_75F41F1DF001__INCLUDED_)
#define AFX_SETGRIDDATA_H__8D753927_80F8_4DB2_8498_75F41F1DF001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGridData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGridData recordset

class SetGridData : public CRecordset
{
public:
	SetGridData(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGridData)

// Field/Param Data
	//{{AFX_FIELD(SetGridData, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_SURF;
	long	m_ID_POINT;	
	double	m_X;
	double	m_Y;
	double	m_Z;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGridData)
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

#endif // !defined(AFX_SETGRIDDATA_H__8D753927_80F8_4DB2_8498_75F41F1DF001__INCLUDED_)
