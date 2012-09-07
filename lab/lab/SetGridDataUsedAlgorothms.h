#if !defined(AFX_SETGRIDDATAUSEDALGOROTHMS_H__CCC55509_D2F3_4640_A604_48CAE6C4C05A__INCLUDED_)
#define AFX_SETGRIDDATAUSEDALGOROTHMS_H__CCC55509_D2F3_4640_A604_48CAE6C4C05A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGridDataUsedAlgorothms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGridDataUsedAlgorothms recordset

class SetGridDataUsedAlgorothms : public CRecordset
{
public:
	SetGridDataUsedAlgorothms(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGridDataUsedAlgorothms)

// Field/Param Data
	//{{AFX_FIELD(SetGridDataUsedAlgorothms, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_SURF;
	BYTE	m_USE_SURFER;
	long	m_ID_ALG;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGridDataUsedAlgorothms)
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

#endif // !defined(AFX_SETGRIDDATAUSEDALGOROTHMS_H__CCC55509_D2F3_4640_A604_48CAE6C4C05A__INCLUDED_)
