// SetPCK2Fiz_CalcModes.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPCK2Fiz_CalcModes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcModes

IMPLEMENT_DYNAMIC(SetPCK2Fiz_CalcModes, CRecordset)

SetPCK2Fiz_CalcModes::SetPCK2Fiz_CalcModes(bool bUserDefined, CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPCK2Fiz_CalcModes)
	m_TYPGR_PCK = 0;
	m_PODTYPGR = 0;
	m_ID_CALC_PARAM = 0;
	m_ID_CALC_METHOD = 0;
	m_TAB = 0;
	m_VNUTR_TRENIE = 0;
	m_FORMULA = _T("");
	m_FOR_TYPZONDS = _T("");
	m_K0 = 0.0;
	m_K1 = 0.0;
	m_KLOG = 0.0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	this->m_bUserDefined = bUserDefined;
}


CString SetPCK2Fiz_CalcModes::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPCK2Fiz_CalcModes::GetDefaultSQL()
{
	if (this->m_bUserDefined)
		return _T("[PCK2Fiz_CalcModesUserDef]");
	else
		return _T("[PCK2Fiz_CalcModes]");
}

void SetPCK2Fiz_CalcModes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPCK2Fiz_CalcModes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TYPGR_PCK]"), m_TYPGR_PCK);
	RFX_Long(pFX, _T("[PODTYPGR]"), m_PODTYPGR);
	RFX_Long(pFX, _T("[ID_CALC_PARAM]"), m_ID_CALC_PARAM);
	RFX_Long(pFX, _T("[ID_CALC_METHOD]"), m_ID_CALC_METHOD);
	RFX_Byte(pFX, _T("[TAB]"), m_TAB);	
	RFX_Byte(pFX, _T("[VNUTR_TRENIE]"), m_VNUTR_TRENIE);	
	RFX_Text(pFX, _T("[FORMULA]"), m_FORMULA);
	RFX_Text(pFX, _T("[FOR_TYPZONDS]"), m_FOR_TYPZONDS);
	RFX_Double(pFX, _T("[K0]"), m_K0);
	RFX_Double(pFX, _T("[K1]"), m_K1);
	RFX_Double(pFX, _T("[KLOG]"), m_KLOG);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPCK2Fiz_CalcModes diagnostics

#ifdef _DEBUG
void SetPCK2Fiz_CalcModes::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPCK2Fiz_CalcModes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
long SetPCK2Fiz_CalcModes::GetNewCalcMethodID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_CALC_METHOD > id)
				id = this->m_ID_CALC_METHOD;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}
void SetPCK2Fiz_CalcModes::AddNewRow(long TYPGR_PCK, long PODTYPGR, 
									 long ID_CALC_PARAM, long ID_CALC_METHOD,
									 BYTE TAB, BYTE VNUTR_TRENIE, CString FORMULA, CString FOR_TYPZONDS,
									 double K0, double K1, double KLOG)
{
	this->AddNew();

	this->m_TYPGR_PCK = TYPGR_PCK;
	this->m_PODTYPGR = PODTYPGR;
	this->m_ID_CALC_PARAM = ID_CALC_PARAM;
	this->m_ID_CALC_METHOD = ID_CALC_METHOD;
	this->m_TAB = TAB;
	this->m_VNUTR_TRENIE = VNUTR_TRENIE;
	this->m_FORMULA = FORMULA;
	this->m_FOR_TYPZONDS = FOR_TYPZONDS;
	this->m_K0 = K0;
	this->m_K1 = K1;
	this->m_KLOG = KLOG;

	this->Update();
}