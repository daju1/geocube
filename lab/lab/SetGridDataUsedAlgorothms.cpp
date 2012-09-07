// SetGridDataUsedAlgorothms.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGridDataUsedAlgorothms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGridDataUsedAlgorothms

IMPLEMENT_DYNAMIC(SetGridDataUsedAlgorothms, CRecordset)

SetGridDataUsedAlgorothms::SetGridDataUsedAlgorothms(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGridDataUsedAlgorothms)
	m_ID_OBJ = 0;
	m_ID_SURF = 0;
	m_USE_SURFER = 0;
	m_ID_ALG = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGridDataUsedAlgorothms::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGridDataUsedAlgorothms::GetDefaultSQL()
{
	return _T("[GridDataUsedAlgorothms]");
}

void SetGridDataUsedAlgorothms::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGridDataUsedAlgorothms)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Byte(pFX, _T("[USE_SURFER]"), m_USE_SURFER);
	RFX_Long(pFX, _T("[ID_ALG]"), m_ID_ALG);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGridDataUsedAlgorothms diagnostics

#ifdef _DEBUG
void SetGridDataUsedAlgorothms::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGridDataUsedAlgorothms::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
