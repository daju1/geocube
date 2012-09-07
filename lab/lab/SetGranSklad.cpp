// SetGranSklad.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGranSklad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGranSklad

IMPLEMENT_DYNAMIC(SetGranSklad, CRecordset)

SetGranSklad::SetGranSklad(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGranSklad)
	m_ID_ROZMIR = 0;
	m_ID_UKLAD = 0;
	m_NAZVA_U = _T("");
	m_NAZVA_R = _T("");
	m_ID_UMPOZ = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString SetGranSklad::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGranSklad::GetDefaultSQL()
{
	return _T("[GranSklad]");
}

void SetGranSklad::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGranSklad)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_ROZMIR]"), m_ID_ROZMIR);
	RFX_Long(pFX, _T("[ID_UKLAD]"), m_ID_UKLAD);
	RFX_Text(pFX, _T("[NAZVA_U]"), m_NAZVA_U);
	RFX_Text(pFX, _T("[NAZVA_R]"), m_NAZVA_R);
	RFX_Long(pFX, _T("[ID_UMPOZ]"), m_ID_UMPOZ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGranSklad diagnostics

#ifdef _DEBUG
void SetGranSklad::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGranSklad::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
