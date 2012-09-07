// DaoSetGeoObjects.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DaoSetGeoObjects.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DaoSetGeoObjects

IMPLEMENT_DYNAMIC(DaoSetGeoObjects, CRecordset)

DaoSetGeoObjects::DaoSetGeoObjects(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(DaoSetGeoObjects)
	m_ID = 0;
	m_NAZVA = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString DaoSetGeoObjects::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString DaoSetGeoObjects::GetDefaultSQL()
{
	return _T("[GeoTables]");
}

void DaoSetGeoObjects::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(DaoSetGeoObjects)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// DaoSetGeoObjects diagnostics

#ifdef _DEBUG
void DaoSetGeoObjects::AssertValid() const
{
	CRecordset::AssertValid();
}

void DaoSetGeoObjects::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
