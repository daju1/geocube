// SetPolygons.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPolygons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPolygons

IMPLEMENT_DYNAMIC(SetPolygons, CRecordset)

SetPolygons::SetPolygons(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPolygons)
	m_ID_OBJ = 0;
	m_ID_ROZRIZ = 0;
	m_N = 0;
	m_id_ige = 0;
	m_nv = 0;
	m_pos_L = 0;
	m_pos_T = 0;
	m_pos_R = 0;
	m_pos_B = 0;
	m_Name = _T("");
	m_bShowName = 0;
	m_ptArrow_x = 0;
	m_ptArrow_y = 0;
	m_iPoly = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPolygons::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPolygons::GetDefaultSQL()
{
	return _T("[Polygons]");
}

void SetPolygons::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPolygons)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_ROZRIZ]"), m_ID_ROZRIZ);
	RFX_Long(pFX, _T("[N]"), m_N);
	RFX_Long(pFX, _T("[id_ige]"), m_id_ige);
	RFX_Long(pFX, _T("[nv]"), m_nv);
	RFX_Long(pFX, _T("[pos_L]"), m_pos_L);
	RFX_Long(pFX, _T("[pos_T]"), m_pos_T);
	RFX_Long(pFX, _T("[pos_R]"), m_pos_R);
	RFX_Long(pFX, _T("[pos_B]"), m_pos_B);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Byte(pFX, _T("[bShowName]"), m_bShowName);
	RFX_Long(pFX, _T("[ptArrow_x]"), m_ptArrow_x);
	RFX_Long(pFX, _T("[ptArrow_y]"), m_ptArrow_y);
	RFX_Long(pFX, _T("[iPoly]"), m_iPoly);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPolygons diagnostics

#ifdef _DEBUG
void SetPolygons::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPolygons::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
