#if !defined(AFX_DAOSETGEOOBJECTS_H__ABB09A34_0DAC_4EB4_B833_F8C632BAC326__INCLUDED_)
#define AFX_DAOSETGEOOBJECTS_H__ABB09A34_0DAC_4EB4_B833_F8C632BAC326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoSetGeoObjects.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DaoSetGeoObjects recordset

class DaoSetGeoObjects : public CRecordset
{
public:
	DaoSetGeoObjects(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DaoSetGeoObjects)

// Field/Param Data
	//{{AFX_FIELD(DaoSetGeoObjects, CRecordset)
	long	m_ID;
	CString	m_NAZVA;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DaoSetGeoObjects)
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

#endif // !defined(AFX_DAOSETGEOOBJECTS_H__ABB09A34_0DAC_4EB4_B833_F8C632BAC326__INCLUDED_)
