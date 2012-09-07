// SetPCK2Fiz_CalcModesUserDef.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPCK2Fiz_CalcModesUserDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcModesUserDef

IMPLEMENT_DYNAMIC(SetPCK2Fiz_CalcModesUserDef, CRecordset)

SetPCK2Fiz_CalcModesUserDef::SetPCK2Fiz_CalcModesUserDef(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPCK2Fiz_CalcModesUserDef)
	m_TYPGR = 0;
	m_PODTYPGR = 0;
	m_ID_CALC_PARAM = 0;
	m_ID_CALC_METHOD = 0;
	m_VNUTR_TRENIE = 0;
	m_FORMULA = _T("");
	m_FOR_TYPZONDS = _T("");
	m_K0 = 0.0;
	m_K1 = 0.0;
	m_KLOG = 0.0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPCK2Fiz_CalcModesUserDef::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPCK2Fiz_CalcModesUserDef::GetDefaultSQL()
{
	return _T("[PCK2Fiz_CalcModesUserDef]");
}

void SetPCK2Fiz_CalcModesUserDef::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPCK2Fiz_CalcModesUserDef)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TYPGR]"), m_TYPGR);
	RFX_Long(pFX, _T("[PODTYPGR]"), m_PODTYPGR);
	RFX_Long(pFX, _T("[ID_CALC_PARAM]"), m_ID_CALC_PARAM);
	RFX_Long(pFX, _T("[ID_CALC_METHOD]"), m_ID_CALC_METHOD);
	RFX_Byte(pFX, _T("[VNUTR_TRENIE]"), m_VNUTR_TRENIE);	
	RFX_Text(pFX, _T("[FORMULA]"), m_FORMULA);
	RFX_Text(pFX, _T("[FOR_TYPZONDS]"), m_FOR_TYPZONDS);
	RFX_Double(pFX, _T("[K0]"), m_K0);
	RFX_Double(pFX, _T("[K1]"), m_K1);
	RFX_Double(pFX, _T("[KLOG]"), m_KLOG);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcModesUserDef diagnostics

#ifdef _DEBUG
void SetPCK2Fiz_CalcModesUserDef::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPCK2Fiz_CalcModesUserDef::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
