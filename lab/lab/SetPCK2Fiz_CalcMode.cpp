// SetPCK2Fiz_CalcMode.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPCK2Fiz_CalcMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcMode

IMPLEMENT_DYNAMIC(SetPCK2Fiz_CalcMode, CRecordset)

SetPCK2Fiz_CalcMode::SetPCK2Fiz_CalcMode(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPCK2Fiz_CalcMode)
	m_ID_OBJ = 0;
	m_ID_IGE = 0;
	m_ID_CALC_PARAM = 0;
	m_ID_METHODY = 0;
	m_ID_CALC_METHOD = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPCK2Fiz_CalcMode::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPCK2Fiz_CalcMode::GetDefaultSQL()
{
	return _T("[PCK2Fiz_CalcMode]");
}

void SetPCK2Fiz_CalcMode::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPCK2Fiz_CalcMode)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	RFX_Long(pFX, _T("[ID_CALC_PARAM]"), m_ID_CALC_PARAM);
	RFX_Byte(pFX, _T("[ID_METHODY]"), m_ID_METHODY);
	RFX_Long(pFX, _T("[ID_CALC_METHOD]"), m_ID_CALC_METHOD);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcMode diagnostics

#ifdef _DEBUG
void SetPCK2Fiz_CalcMode::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPCK2Fiz_CalcMode::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
