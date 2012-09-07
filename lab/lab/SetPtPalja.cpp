// SetPtPalja.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPtPalja.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPtPalja

IMPLEMENT_DYNAMIC(SetPtPalja, CRecordset)

SetPtPalja::SetPtPalja(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPtPalja)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_TYP = 0;
	m_Pereriz_X = 0.0;
	m_Pereriz_Y = 0.0;
	m_A = 0.0;
	m_u = 0.0;
	m_GLYB = 0.0;
	m_RsA = 0.0;
	m_fhu = 0.0;
	m_PZ = 0.0;
	m_ID_SNIP = 1;
	m_Fu = 0.0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPtPalja::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetPtPalja::GetDefaultSQL()
{
	return _T("[PtPalja]");
}

void SetPtPalja::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPtPalja)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_TYP]"), m_ID_TYP);
	RFX_Double(pFX, _T("[Pereriz_X]"), m_Pereriz_X);
	RFX_Double(pFX, _T("[Pereriz_Y]"), m_Pereriz_Y);
	RFX_Double(pFX, _T("[A]"), m_A);
	RFX_Double(pFX, _T("[u]"), m_u);
	RFX_Double(pFX, _T("[GLYB]"), m_GLYB);
	RFX_Double(pFX, _T("[RsA]"), m_RsA);
	RFX_Double(pFX, _T("[fhu]"), m_fhu);
	RFX_Double(pFX, _T("[PZ]"), m_PZ);
	RFX_Long(pFX, _T("[ID_SNIP]"), m_ID_SNIP);
	RFX_Double(pFX, _T("[Fu]"), m_Fu);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPtPalja diagnostics

#ifdef _DEBUG
void SetPtPalja::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPtPalja::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
void SetPtPalja::AddNewRow(long ID_OBJ, long ID_KT, long ID_TYP, double Pereriz_X, double Pereriz_Y, double A, double u, double GLYB, double RsA, double fhu, double PZ, long ID_SNIP, double Fu)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_TYP = ID_TYP;
	this->m_Pereriz_X = Pereriz_X;
	this->m_Pereriz_Y = Pereriz_Y;
	this->m_A = A;
	this->m_u = u;
	this->m_GLYB = GLYB;
	this->m_RsA = RsA;
	this->m_fhu = fhu;
	this->m_PZ = PZ;
	this->m_ID_SNIP = ID_SNIP;
	this->m_Fu = Fu;

	this->Update();
}