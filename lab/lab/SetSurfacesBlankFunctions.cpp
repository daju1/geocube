// SetSurfacesBlankFunctions.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetSurfacesBlankFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesBlankFunctions

IMPLEMENT_DYNAMIC(SetSurfacesBlankFunctions, CRecordset)

SetSurfacesBlankFunctions::SetSurfacesBlankFunctions(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetSurfacesBlankFunctions)
	m_ID_OBJ = 0;
	//m_ID_ITEM = 0;
	m_ID_SURF_OBJ = 0;
	m_ID_SURF_PARAM = 0;
	m_ID_BLANK_FUN = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetSurfacesBlankFunctions::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetSurfacesBlankFunctions::GetDefaultSQL()
{
	return _T("[SurfacesBlankFunctions]");
}

void SetSurfacesBlankFunctions::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetSurfacesBlankFunctions)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	//RFX_Long(pFX, _T("[ID_ITEM]"), m_ID_ITEM);
	RFX_Long(pFX, _T("[ID_SURF_OBJ]"), m_ID_SURF_OBJ);
	RFX_Long(pFX, _T("[ID_SURF_PARAM]"), m_ID_SURF_PARAM);
	RFX_Byte(pFX, _T("[ID_BLANK_FUN]"), m_ID_BLANK_FUN);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetSurfacesBlankFunctions diagnostics

#ifdef _DEBUG
void SetSurfacesBlankFunctions::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetSurfacesBlankFunctions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
