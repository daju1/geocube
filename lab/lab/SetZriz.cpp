// SetZriz.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetZriz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetZriz

IMPLEMENT_DYNAMIC(SetZriz, CRecordset)

SetZriz::SetZriz(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetZriz)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_ID_HID = 0;
	m_ID_SHEMA = 0;
	m_ID_STAN = 0;
	m_tgFi = 0.0;
	m_C = 0.0;
	m_D = 0.0;
	m_H = 0.0;
	m_bSTAT = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetZriz::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetZriz::GetDefaultSQL()
{
	return _T("[Zriz]");
}

void SetZriz::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetZriz)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Date(pFX, _T("[DTVYPROB]"), m_DTVYPROB);
	RFX_Long(pFX, _T("[ID_HID]"), m_ID_HID);
	RFX_Long(pFX, _T("[ID_SHEMA]"), m_ID_SHEMA);
	RFX_Long(pFX, _T("[ID_STAN]"), m_ID_STAN);
	RFX_Double(pFX, _T("[tgFi]"), m_tgFi);
	RFX_Double(pFX, _T("[C]"), m_C);
	RFX_Double(pFX, _T("[D]"), m_D);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetZriz diagnostics

#ifdef _DEBUG
void SetZriz::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetZriz::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
void SetZriz::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, 
						long ID_HID, long ID_SHEMA, long ID_STAN, 
						double tgFi, double C,
						double D, double H)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_ID_VYPROB = ID_VYPROB;

	this->m_ID_HID = ID_HID;
	this->m_ID_SHEMA = ID_SHEMA;
	this->m_ID_STAN = ID_STAN;

	this->m_tgFi = tgFi;
	this->m_C = C;

	this->m_D = D;
	this->m_H = H;

	this->m_bSTAT = 1;

	this->Update();
}


long SetZriz::GetNewKeyID()
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