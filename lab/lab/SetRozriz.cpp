// SetRozriz.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetRozriz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetRozriz

IMPLEMENT_DYNAMIC(SetRozriz, CRecordset)

SetRozriz::SetRozriz(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetRozriz)
	m_ID_OBJ = 0;
	m_ID_ROZRIZ = 0;
	m_NPP = 0;
	m_ID_KT = 0;
	m_dxf_x = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetRozriz::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetRozriz::GetDefaultSQL()
{
	return _T("[Rozriz]");
}

void SetRozriz::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetRozriz)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_ROZRIZ]"), m_ID_ROZRIZ);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Double(pFX, _T("[dxf_x]"), m_dxf_x);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetRozriz diagnostics

#ifdef _DEBUG
void SetRozriz::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetRozriz::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetRozriz::AddNewRow(long ID_OBJ, long ID_ROZRIZ, long NPP, long ID_KT)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NPP = NPP;
	this->m_ID_KT = ID_KT;

	this->Update();
}

void SetRozriz::AddNewRow(long ID_OBJ, long ID_ROZRIZ, long NPP, long ID_KT, double dxf_x)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NPP = NPP;
	this->m_ID_KT = ID_KT;
	this->m_dxf_x = dxf_x;

	this->Update();
}