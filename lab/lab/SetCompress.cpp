// SetCompress.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetCompress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetCompress

IMPLEMENT_DYNAMIC(SetCompress, CRecordset)

SetCompress::SetCompress(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetCompress)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_SIGMA = 0.0;
	m_DH1 = 0.0;
	m_DH2 = 0.0;
	m_VODA = 0;
	m_bSTAT = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetCompress::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetCompress::GetDefaultSQL()
{
	return _T("[Compress]");
}

void SetCompress::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetCompress)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Double(pFX, _T("[SIGMA]"), m_SIGMA);
	RFX_Double(pFX, _T("[DH1]"), m_DH1);
	RFX_Double(pFX, _T("[DH2]"), m_DH2);
	RFX_Byte(pFX, _T("[VODA]"), m_VODA);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetCompress diagnostics

#ifdef _DEBUG
void SetCompress::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetCompress::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetCompress::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB,
	double SIGMA, double DH1, double DH2, BYTE VODA, BYTE bSTAT)
{
	this->AddNew();

	m_ID_OBJ		= ID_OBJ;
	m_ID_KT			= ID_KT;
	m_ID_PROB		= ID_PROB;
	m_ID_VYPROB		= ID_VYPROB;

	m_SIGMA			= SIGMA;
	m_DH1			= DH1;
	m_DH2			= DH2;
	m_VODA			= VODA;
	m_bSTAT			= bSTAT;

	this->Update();

}
