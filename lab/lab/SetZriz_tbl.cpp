// SetZriz_tbl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetZriz_tbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetZriz_tbl

IMPLEMENT_DYNAMIC(SetZriz_tbl, CRecordset)

SetZriz_tbl::SetZriz_tbl(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetZriz_tbl)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_ID_KOLCA = 0;
	m_SIGMA = 0.0;
	m_TAU = 0.0;
	m_W_do = 0.0;
	m_Ro_do = 0.0;
	m_W_po_upl = 0.0;
	m_Ro_po_upl = 0.0;
	m_W_after = 0.0;
	m_Ro_after = 0.0;
	m_bSTAT = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetZriz_tbl::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetZriz_tbl::GetDefaultSQL()
{
	return _T("[Zriz_tbl]");
}

void SetZriz_tbl::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetZriz_tbl)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Long(pFX, _T("[ID_KOLCA]"), m_ID_KOLCA);
	RFX_Double(pFX, _T("[SIGMA]"), m_SIGMA);
	RFX_Double(pFX, _T("[TAU]"), m_TAU);
	RFX_Double(pFX, _T("[W_do]"), m_W_do);
	RFX_Double(pFX, _T("[Ro_do]"), m_Ro_do);
	RFX_Double(pFX, _T("[W_po_upl]"), m_W_po_upl);
	RFX_Double(pFX, _T("[Ro_po_upl]"), m_Ro_po_upl);
	RFX_Double(pFX, _T("[W_after]"), m_W_after);
	RFX_Double(pFX, _T("[Ro_after]"), m_Ro_after);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetZriz_tbl diagnostics

#ifdef _DEBUG
void SetZriz_tbl::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetZriz_tbl::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetZriz_tbl::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, long ID_KOLCA, 
							double SIGMA, double TAU,
							double W_do, double Ro_do, 
							double W_po_upl, double Ro_po_upl, 
							double W_after, double Ro_after)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_ID_VYPROB = ID_VYPROB;
	this->m_ID_KOLCA = ID_KOLCA;

	this->m_SIGMA = SIGMA;
	this->m_TAU = TAU;

	this->m_W_do = W_do;
	this->m_Ro_do = Ro_do;

	this->m_W_po_upl = W_po_upl;
	this->m_Ro_po_upl = Ro_po_upl;

	this->m_W_after = W_after;
	this->m_Ro_after = Ro_after;

	this->m_bSTAT = 1;

	this->Update();
}
