#if !defined(AFX_SETSURFACESBLANKORDER1_H__2C4C5C58_D729_4A82_B640_5F6534F94671__INCLUDED_)
#define AFX_SETSURFACESBLANKORDER1_H__2C4C5C58_D729_4A82_B640_5F6534F94671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSurfacesBlankOrder1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesBlankOrder1 recordset
struct surface_blank_order_list_item;

class SetSurfacesBlankOrder : public CRecordset
{
public:
	SetSurfacesBlankOrder(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetSurfacesBlankOrder)

// Field/Param Data
	//{{AFX_FIELD(SetSurfacesBlankOrder, CRecordset)
	long	m_ID_OBJ;
	long	m_NPP;
	long	m_ID_SURF;
	BYTE	m_PODOSHVA;
	BYTE	m_check_blank_me;
	BYTE	m_check_blank_me_up;
	BYTE	m_check_blank_me_up_above;
	BYTE	m_check_blank_me_down;
	BYTE	m_check_blank_me_down_above;
	BYTE	m_check_blank_by_me_up;
	BYTE	m_check_blank_by_me_down;
	//}}AFX_FIELD

	void Init(long ID_OBJ, long NPP, surface_blank_order_list_item * soli);
	void InitChecks(surface_blank_order_list_item * soli);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetSurfacesBlankOrder)
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

#endif // !defined(AFX_SETSURFACESBLANKORDER1_H__2C4C5C58_D729_4A82_B640_5F6534F94671__INCLUDED_)
