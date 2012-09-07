#if !defined(AFX_SETPOLYGONS_H__CF3A604E_660A_4B49_91F4_95DCE901D030__INCLUDED_)
#define AFX_SETPOLYGONS_H__CF3A604E_660A_4B49_91F4_95DCE901D030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPolygons.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetPolygons recordset

class SetPolygons : public CRecordset
{
public:
	SetPolygons(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetPolygons)

// Field/Param Data
	//{{AFX_FIELD(SetPolygons, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_ROZRIZ;
	long	m_N;
	long	m_id_ige;
	long	m_nv;
	long	m_pos_L;
	long	m_pos_T;
	long	m_pos_R;
	long	m_pos_B;
	CString	m_Name;
	BYTE	m_bShowName;
	long	m_ptArrow_x;
	long	m_ptArrow_y;
	long	m_iPoly;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetPolygons)
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

#endif // !defined(AFX_SETPOLYGONS_H__CF3A604E_660A_4B49_91F4_95DCE901D030__INCLUDED_)
