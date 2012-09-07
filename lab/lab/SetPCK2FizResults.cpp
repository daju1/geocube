// SetPCK2FizResults.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPCK2FizResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPCK2FizResults

IMPLEMENT_DYNAMIC(SetPCK2FizResults, CRecordset)

SetPCK2FizResults::SetPCK2FizResults(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPCK2FizResults)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_NPP = 0;
	m_ID_CALC_PARAM = 0;
	m_param = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPCK2FizResults::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPCK2FizResults::GetDefaultSQL()
{
	return _T("[PCK2FizResults]");
}

void SetPCK2FizResults::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPCK2FizResults)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Long(pFX, _T("[ID_CALC_PARAM]"), m_ID_CALC_PARAM);
	RFX_Double(pFX, _T("[param]"), m_param);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPCK2FizResults diagnostics

#ifdef _DEBUG
void SetPCK2FizResults::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPCK2FizResults::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
void SetPCK2FizResults::AddNewRow(long ID_OBJ, long ID_KT, long NPP, long ID_CALC_PARAM, double param)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_NPP = NPP;
	this->m_ID_CALC_PARAM = ID_CALC_PARAM;
	this->m_param = param;

	this->Update();
}