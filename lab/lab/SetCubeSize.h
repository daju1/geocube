#if !defined(AFX_SETCUBESIZE_H__88B7ACD8_B8D4_4072_A426_3937344FDEF6__INCLUDED_)
#define AFX_SETCUBESIZE_H__88B7ACD8_B8D4_4072_A426_3937344FDEF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCubeSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetCubeSize recordset
struct CubeSize;

class SetCubeSize : public CRecordset
{
public:
	SetCubeSize(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetCubeSize)

// Field/Param Data
	//{{AFX_FIELD(SetCubeSize, CRecordset)
	long	m_ID_OBJ;
	long	m_nPag;
	long	m_nRow;
	long	m_nCol;
	double	m_xLL;
	double	m_yLL;
	double	m_zLL;
	double	m_xSize;
	double	m_ySize;
	double	m_zSize;
	//}}AFX_FIELD

	void Init(CubeSize & cube_size);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetCubeSize)
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

#endif // !defined(AFX_SETCUBESIZE_H__88B7ACD8_B8D4_4072_A426_3937344FDEF6__INCLUDED_)
