// SetPalja1.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPalja1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPalja1

IMPLEMENT_DYNAMIC(SetPalja, CRecordset)

SetPalja::SetPalja(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPalja1)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_H = 0.0;
	m_qc = 0.0;
	m_beta1 = 0.0;
	m_Rs = 0.0;
	m_fs = 0.0;
	m_beta2 = 0.0;
	m_f = 0.0;
	m_RsA = 0.0;
	m_fhu = 0.0;
	m_Fu = 0.0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPalja::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPalja::GetDefaultSQL()
{
	return _T("[Palja]");
}

void SetPalja::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPalja1)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Double(pFX, _T("[qc]"), m_qc);
	RFX_Double(pFX, _T("[beta1]"), m_beta1);
	RFX_Double(pFX, _T("[Rs]"), m_Rs);
	RFX_Double(pFX, _T("[fs]"), m_fs);
	RFX_Double(pFX, _T("[beta2]"), m_beta2);
	RFX_Double(pFX, _T("[f]"), m_f);
	RFX_Double(pFX, _T("[RsA]"), m_RsA);
	RFX_Double(pFX, _T("[fhu]"), m_fhu);
	RFX_Double(pFX, _T("[Fu]"), m_Fu);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPalja1 diagnostics

#ifdef _DEBUG
void SetPalja::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPalja::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetPalja::AddNewRow(long ID_OBJ, long ID_KT, double H, double qc, double beta1, double Rs, double fs, double beta2, double f, double RsA, double fhu, double Fu)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_H = H;
	this->m_qc = qc;
	this->m_beta1 = beta1;
	this->m_Rs = Rs;
	this->m_fs = fs;
	this->m_beta2 = beta2;
	this->m_f = f;
	this->m_RsA = RsA;
	this->m_fhu = fhu;
	this->m_Fu = Fu;

	this->Update();
}