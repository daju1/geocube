// SetSurfacesBlankOrder.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetSurfacesBlankOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesBlankOrder

IMPLEMENT_DYNAMIC(SetSurfacesBlankOrder, CRecordset)

SetSurfacesBlankOrder::SetSurfacesBlankOrder(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetSurfacesBlankOrder)
	m_ID_OBJ = 0;
	m_NPP = 0;
	m_check = 0;
	m_ID_SURF = 0;
	m_PODOSHVA = 0;
	m_check2 = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetSurfacesBlankOrder::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetSurfacesBlankOrder::GetDefaultSQL()
{
	return _T("[SurfacesBlankOrder]");
}

void SetSurfacesBlankOrder::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetSurfacesBlankOrder)
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
// SetSurfacesBlankOrder diagnostics

#ifdef _DEBUG
void SetSurfacesBlankOrder::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetSurfacesBlankOrder::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
