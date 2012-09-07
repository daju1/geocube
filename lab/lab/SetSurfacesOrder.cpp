// SetSurfacesOrder.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetSurfacesOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesOrder

IMPLEMENT_DYNAMIC(SetSurfacesOrder, CRecordset)

SetSurfacesOrder::SetSurfacesOrder(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetSurfacesOrder)
	m_ID_OBJ = 0;
	m_NPP = 0;
	m_check = 0;
	m_ID_SURF = 0;
	m_check2 = 0;
	m_PODOSHVA = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetSurfacesOrder::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetSurfacesOrder::GetDefaultSQL()
{
	return _T("[SurfacesOrder]");
}

void SetSurfacesOrder::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetSurfacesOrder)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Byte(pFX, _T("[check]"), m_check);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Byte(pFX, _T("[PODOSHVA]"), m_PODOSHVA);
	RFX_Byte(pFX, _T("[check2]"), m_check2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesOrder diagnostics

#ifdef _DEBUG
void SetSurfacesOrder::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetSurfacesOrder::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
