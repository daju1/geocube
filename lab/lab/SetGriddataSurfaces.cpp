// SetGriddataSurfaces.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGriddataSurfaces.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGriddataSurfaces

IMPLEMENT_DYNAMIC(SetGriddataSurfaces, CRecordset)

SetGriddataSurfaces::SetGriddataSurfaces(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGriddataSurfaces)
	m_ID_OBJ = 0;
	m_ID_SURF = 0;
	m_NAZVA = _T("");
	m_PODOSHVA = 0;
	m_r = 0;
	m_g = 0;
	m_b = 0;
	m_z_flag = -1;
	m_ID_UMPOZ = 0;
	m_ID_IGE = -1;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGriddataSurfaces::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGriddataSurfaces::GetDefaultSQL()
{
	return _T("[GriddataSurfaces]");
}

void SetGriddataSurfaces::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGriddataSurfaces)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	RFX_Byte(pFX, _T("[PODOSHVA]"), m_PODOSHVA);
	RFX_Byte(pFX, _T("[r]"), m_r);
	RFX_Byte(pFX, _T("[g]"), m_g);
	RFX_Byte(pFX, _T("[b]"), m_b);
	RFX_Int(pFX, _T("[z_flag]"), m_z_flag);
	RFX_Long(pFX, _T("[ID_UMPOZ]"), m_ID_UMPOZ);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGriddataSurfaces diagnostics

#ifdef _DEBUG
void SetGriddataSurfaces::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGriddataSurfaces::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
