// SetSurfacesBlankOrder1.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetSurfacesBlankOrder1.h"
#include "../../surfdoc/src/Geosurface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesBlankOrder1

IMPLEMENT_DYNAMIC(SetSurfacesBlankOrder, CRecordset)

SetSurfacesBlankOrder::SetSurfacesBlankOrder(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetSurfacesBlankOrder1)
	m_ID_OBJ = 0;
	m_NPP = 0;
	m_ID_SURF = 0;
	m_PODOSHVA = 0;
	m_check_blank_me = 0;
	m_check_blank_me_up = 0;
	m_check_blank_me_up_above = 0;
	m_check_blank_me_down = 0;
	m_check_blank_me_down_above = 0;
	m_check_blank_by_me_up = 0;
	m_check_blank_by_me_down = 0;
	m_nFields = 11;
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
	//{{AFX_FIELD_MAP(SetSurfacesBlankOrder1)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Byte(pFX, _T("[PODOSHVA]"), m_PODOSHVA);
	RFX_Byte(pFX, _T("[check_blank_me]"), m_check_blank_me);
	RFX_Byte(pFX, _T("[check_blank_me_up]"), m_check_blank_me_up);
	RFX_Byte(pFX, _T("[check_blank_me_up_above]"), m_check_blank_me_up_above);
	RFX_Byte(pFX, _T("[check_blank_me_down]"), m_check_blank_me_down);
	RFX_Byte(pFX, _T("[check_blank_me_down_above]"), m_check_blank_me_down_above);
	RFX_Byte(pFX, _T("[check_blank_by_me_up]"), m_check_blank_by_me_up);
	RFX_Byte(pFX, _T("[check_blank_by_me_down]"), m_check_blank_by_me_down);
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
	
void SetSurfacesBlankOrder::Init(long ID_OBJ, long NPP, surface_blank_order_list_item * soli)
{
	m_ID_OBJ = ID_OBJ;
	m_NPP = NPP;
	m_ID_SURF					= soli->id_surf;
	m_PODOSHVA					= soli->podoshva;

	InitChecks(soli);
}
void SetSurfacesBlankOrder::InitChecks(surface_blank_order_list_item * soli)
{
	m_check_blank_me			= soli->check_blank_me;
	m_check_blank_me_up			= soli->check_blank_me_up;
	m_check_blank_me_up_above	= soli->check_blank_me_up_above;
	m_check_blank_me_down		= soli->check_blank_me_down;
	m_check_blank_me_down_above = soli->check_blank_me_down_above;
	m_check_blank_by_me_up		= soli->check_blank_by_me_up;
	m_check_blank_by_me_down	= soli->check_blank_by_me_down;
}
