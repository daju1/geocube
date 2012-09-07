// SetZriz0.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetZriz0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetZriz0

IMPLEMENT_DYNAMIC(SetZriz0, CRecordset)

SetZriz0::SetZriz0(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetZriz0)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_ID_KOLCA = 0;
	m_ID_PHYS_VYPROB = 0;
	m_H = 0.0;
	m_D = 0.0;
	m_DH_PO_UPL = 0.0;
	m_M_KOLCA = 0.0;
	m_M_GRUNTA = 0.0;
	m_M_GRUNTA_ZAMOCH = 0.0;
	m_M_GRUNTA_POSLE_UPLOT = 0.0;
	m_M_GRUNTA_POSLE = 0.0;
	m_M_GRUNTA_VYSUSH = 0.0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetZriz0::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetZriz0::GetDefaultSQL()
{
	return _T("[Zriz0]");
}

void SetZriz0::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetZriz0)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Long(pFX, _T("[ID_KOLCA]"), m_ID_KOLCA);
	RFX_Long(pFX, _T("[ID_PHYS_VYPROB]"), m_ID_PHYS_VYPROB);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Double(pFX, _T("[D]"), m_D);
	RFX_Double(pFX, _T("[DH_PO_UPL]"), m_DH_PO_UPL);
	RFX_Double(pFX, _T("[M_KOLCA]"), m_M_KOLCA);
	RFX_Double(pFX, _T("[M_GRUNTA]"), m_M_GRUNTA);
	RFX_Double(pFX, _T("[M_GRUNTA_ZAMOCH]"), m_M_GRUNTA_ZAMOCH);
	RFX_Double(pFX, _T("[M_GRUNTA_POSLE_UPLOT]"), m_M_GRUNTA_POSLE_UPLOT);
	RFX_Double(pFX, _T("[M_GRUNTA_POSLE]"), m_M_GRUNTA_POSLE);
	RFX_Double(pFX, _T("[M_GRUNTA_VYSUSH]"), m_M_GRUNTA_VYSUSH);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetZriz0 diagnostics

#ifdef _DEBUG
void SetZriz0::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetZriz0::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
long SetZriz0::GetMaxPhysVyprobID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_PHYS_VYPROB > id)
				id = this->m_ID_PHYS_VYPROB;
			
			this->MoveNext(); // to validate record count
		}
	}
	return id;
}

void SetZriz0::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, 
						long ID_KOLCA, long ID_PHYS_VYPROB,
						double H, double D, double DH_PO_UPL,						
						double M_KOLCA, double M_GRUNTA, double M_GRUNTA_ZAMOCH, double M_GRUNTA_POSLE_UPLOT, double M_GRUNTA_POSLE, double M_GRUNTA_VYSUSH)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_ID_VYPROB = ID_VYPROB;

	this->m_ID_KOLCA = ID_KOLCA;
	this->m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;

	this->m_H = H;
	this->m_D = D;
	this->m_DH_PO_UPL = DH_PO_UPL;

	this->m_M_KOLCA = M_KOLCA;
	this->m_M_GRUNTA = M_GRUNTA;
	this->m_M_GRUNTA_ZAMOCH = M_GRUNTA_ZAMOCH;
	this->m_M_GRUNTA_POSLE_UPLOT = M_GRUNTA_POSLE_UPLOT;
	this->m_M_GRUNTA_POSLE = M_GRUNTA_POSLE;
	this->m_M_GRUNTA_VYSUSH = M_GRUNTA_VYSUSH;

	this->Update();
}


