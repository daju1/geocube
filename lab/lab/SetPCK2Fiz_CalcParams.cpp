// SetPCK2Fiz_CalcParams.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPCK2Fiz_CalcParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcParams

IMPLEMENT_DYNAMIC(SetPCK2Fiz_CalcParams, CRecordset)

SetPCK2Fiz_CalcParams::SetPCK2Fiz_CalcParams(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPCK2Fiz_CalcParams)
	m_ID_CALC_PARAM = 0;
	m_CALC_PARAM = _T("");
	m_desc = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPCK2Fiz_CalcParams::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPCK2Fiz_CalcParams::GetDefaultSQL()
{
	return _T("[PCK2Fiz_CalcParams]");
}

void SetPCK2Fiz_CalcParams::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPCK2Fiz_CalcParams)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_CALC_PARAM]"), m_ID_CALC_PARAM);
	RFX_Text(pFX, _T("[CALC_PARAM]"), m_CALC_PARAM);
	RFX_Text(pFX, _T("[desc]"), m_desc);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcParams diagnostics

#ifdef _DEBUG
void SetPCK2Fiz_CalcParams::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPCK2Fiz_CalcParams::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
