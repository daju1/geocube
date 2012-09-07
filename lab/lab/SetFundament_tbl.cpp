// SetFundament_tbl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetFundament_tbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetFundament_tbl

IMPLEMENT_DYNAMIC(SetFundament_tbl, CRecordset)

SetFundament_tbl::SetFundament_tbl(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetFundament_tbl)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PERERIZ = 0;
	m_NPP = 0;
	m_Z = 0.0;
	m_R = 0.0;
	m_FI = 0.0;
	m_NAZVA = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetFundament_tbl::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetFundament_tbl::GetDefaultSQL()
{
	return _T("[Fundament_tbl]");
}

void SetFundament_tbl::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetFundament_tbl)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PERERIZ]"), m_ID_PERERIZ);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Double(pFX, _T("[Z]"), m_Z);
	RFX_Double(pFX, _T("[R]"), m_R);
	RFX_Double(pFX, _T("[FI]"), m_FI);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetFundament_tbl diagnostics

#ifdef _DEBUG
void SetFundament_tbl::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetFundament_tbl::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
