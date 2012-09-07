// SetUstanovka.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetUstanovka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetUstanovka

IMPLEMENT_DYNAMIC(SetUstanovka, CRecordset)

SetUstanovka::SetUstanovka(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetUstanovka)
	m_ID_UST = 0;
	m_NAZVA = _T("");
	m_TYP_ZOND = 0;
	m_N_SHEMA = 0;
	m_Kg = 0.0;
	m_Kf = 0.0;
	m_Bg = 0.0;
	m_Bf = 0.0;
	m_Shtanga_d = 0.036;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetUstanovka::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetUstanovka::GetDefaultSQL()
{
	return _T("[Ustanovka]");
}

void SetUstanovka::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetUstanovka)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_UST]"), m_ID_UST);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	RFX_Long(pFX, _T("[TYP_ZOND]"), m_TYP_ZOND);
	RFX_Long(pFX, _T("[N_SHEMA]"), m_N_SHEMA);
	RFX_Double(pFX, _T("[Kg]"), m_Kg);
	RFX_Double(pFX, _T("[Kf]"), m_Kf);
	RFX_Double(pFX, _T("[Bg]"), m_Bg);
	RFX_Double(pFX, _T("[Bf]"), m_Bf);
	RFX_Double(pFX, _T("[Shtanga_d]"), m_Shtanga_d);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetUstanovka diagnostics

#ifdef _DEBUG
void SetUstanovka::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetUstanovka::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetUstanovka::AddNewRow(long ID_UST, CString NAZVA, long TYP_ZOND,
		long N_SHEMA, double Kg, double Kf,
		double Bg, double Bf, double Shtanga_d)
{
	this->AddNew();

	this->m_ID_UST = ID_UST;
	this->m_NAZVA = NAZVA;
	this->m_TYP_ZOND = TYP_ZOND;
	this->m_N_SHEMA = N_SHEMA;
	this->m_Kg = Kg;
	this->m_Kf = Kf;
	this->m_Bg = Bg;
	this->m_Bf = Bf;
	this->m_Shtanga_d = Shtanga_d;

	this->Update();
}