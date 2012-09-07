#if !defined(AFX_SETCOMPRESS_H__0A023370_4B15_43FC_8640_E5622D13E644__INCLUDED_)
#define AFX_SETCOMPRESS_H__0A023370_4B15_43FC_8640_E5622D13E644__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCompress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetCompress recordset

class SetCompress : public CRecordset
{
public:
	SetCompress(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetCompress)

// Field/Param Data
	//{{AFX_FIELD(SetCompress, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	double	m_SIGMA;
	double	m_DH1;
	double	m_DH2;
	BYTE	m_VODA;
	BYTE	m_bSTAT;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB,
		double SIGMA, double DH1, double DH2, BYTE VODA, BYTE bSTAT);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetCompress)
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

#endif // !defined(AFX_SETCOMPRESS_H__0A023370_4B15_43FC_8640_E5622D13E644__INCLUDED_)
