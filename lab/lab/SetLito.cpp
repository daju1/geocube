// SetLito.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetLito.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetLito

IMPLEMENT_DYNAMIC(SetLito, CRecordset)

SetLito::SetLito(bool bUnEdited, CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetLito)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_IGE = 0;
	m_H0 = 0.0;
	m_H1 = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	this->m_bUnEdited = bUnEdited;
}


CString SetLito::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetLito::GetDefaultSQL()
{
	if (this->m_bUnEdited)
        return _T("[Lito0]");
	else
        return _T("[Lito]");
}

void SetLito::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetLito)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	RFX_Double(pFX, _T("[H0]"), m_H0);
	RFX_Double(pFX, _T("[H1]"), m_H1);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetLito diagnostics

#ifdef _DEBUG
void SetLito::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetLito::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetLito::AddNewRow(long ID_OBJ, long ID_KT, long ID_IGE, double h0, double h1)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_IGE = ID_IGE;
	this->m_H0 = h0;
	this->m_H1 = h1;

	this->Update();
}