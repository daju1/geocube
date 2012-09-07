// SetCilce.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetCilce.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetCilce

IMPLEMENT_DYNAMIC(SetCilce, CRecordset)

SetCilce::SetCilce(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetCilce)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_H = 0.0;
	m_D = 0.0;
	m_ES_L1 = 0.0;
	m_ES_R1 = 0.0;
	m_ES_L2 = 0.0;
	m_ES_R2 = 0.0;
	m_nju = 0.0;
	m_nju_z = 0.0;
	m_m01 = 0.0;
	m_E1 = 0.0;
	m_m02 = 0.0;
	m_E2 = 0.0;
	m_m01v = 0.0;
	m_E1v = 0.0;
	m_m02v = 0.0;
	m_E2v = 0.0;
	m_ID_METHOD = 0;
	m_bSTAT = 0;
	m_bStatV = 0;
	m_nFields = 24;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetCilce::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetCilce::GetDefaultSQL()
{
	return _T("[Cilce]");
}

void SetCilce::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetCilce)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Date(pFX, _T("[DTVYPROB]"), m_DTVYPROB);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Double(pFX, _T("[D]"), m_D);
	RFX_Double(pFX, _T("[ES_L1]"), m_ES_L1);
	RFX_Double(pFX, _T("[ES_R1]"), m_ES_R1);
	RFX_Double(pFX, _T("[ES_L2]"), m_ES_L2);
	RFX_Double(pFX, _T("[ES_R2]"), m_ES_R2);
	RFX_Double(pFX, _T("[nju]"), m_nju);
	RFX_Double(pFX, _T("[nju_z]"), m_nju_z);
	RFX_Double(pFX, _T("[m01]"), m_m01);
	RFX_Double(pFX, _T("[E1]"), m_E1);
	RFX_Double(pFX, _T("[m02]"), m_m02);
	RFX_Double(pFX, _T("[E2]"), m_E2);
	RFX_Double(pFX, _T("[m01v]"), m_m01v);
	RFX_Double(pFX, _T("[E1v]"), m_E1v);
	RFX_Double(pFX, _T("[m02v]"), m_m02v);
	RFX_Double(pFX, _T("[E2v]"), m_E2v);
	RFX_Byte(pFX, _T("[ID_METHOD]"), m_ID_METHOD);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	RFX_Byte(pFX, _T("[bStatV]"), m_bStatV);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetCilce diagnostics

#ifdef _DEBUG
void SetCilce::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetCilce::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetCilce::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB,
	double H, double D,	double ES_L1, double ES_R1, double ES_L2, double ES_R2,
	double nju,	double nju_z, 
	double m01, double E1, double m02, double E2,
	double m01v, double E1v, double m02v, double E2v, 
	BYTE ID_METHOD, BYTE bSTAT, BYTE bStatV)
{
	this->AddNew();

	m_ID_OBJ		= ID_OBJ;
	m_ID_KT			= ID_KT;
	m_ID_PROB		= ID_PROB;
	m_ID_VYPROB		= ID_VYPROB;
	m_DTVYPROB;
	m_H				= H;
	m_D				= D;
	m_ES_L1			= ES_L1;
	m_ES_R1			= ES_R1;
	m_ES_L2			= ES_L2;
	m_ES_R2			= ES_R2;
	m_nju			= nju;
	m_nju_z			= nju_z;
	m_m01			= m01;
	m_E1			= E1;
	m_m02			= m02;
	m_E2			= E2;
	m_m01v			= m01v;
	m_E1v			= E1v;
	m_m02v			= m02v;
	m_E2v			= E2v;
	m_ID_METHOD		= ID_METHOD;
	m_bSTAT			= bSTAT;
	m_bStatV		= bStatV;

	this->Update();
}
long SetCilce::GetNewKeyID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_VYPROB > id)
				id = this->m_ID_VYPROB;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}