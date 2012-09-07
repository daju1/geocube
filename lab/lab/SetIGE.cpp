// SetIGE.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetIGE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetIGE

IMPLEMENT_DYNAMIC(SetIGE, CRecordset)

SetIGE::SetIGE(bool bUnEdited, CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetIGE)
	m_ID_OBJ = 0;
	m_ID_IGE = 0;
	m_ID_GR = 0;
	m_IGE = _T("");
	m_mk = 1.0;
	m_mkz = 1.0;
	m_strat = _T("");
	m_desc0 = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	this->m_bUnEdited = bUnEdited;
}


CString SetIGE::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetIGE::GetDefaultSQL()
{
	if (this->m_bUnEdited)
        return _T("[IGE0]");
	else
        return _T("[IGE]");
}

void SetIGE::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetIGE)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	RFX_Long(pFX, _T("[ID_GR]"), m_ID_GR);
	RFX_Text(pFX, _T("[IGE]"), m_IGE);
	RFX_Double(pFX, _T("[mk]"), m_mk);
	RFX_Double(pFX, _T("[mkz]"), m_mkz);
	RFX_Text(pFX, _T("[strat]"), m_strat);
	RFX_Text(pFX, _T("[desc0]"), m_desc0);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetIGE diagnostics

#ifdef _DEBUG
void SetIGE::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetIGE::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
void SetIGE::AddNewRow(long ID_OBJ, long ID_IGE, long ID_GR, CString IGE, double mk, double mkz, CString strat, CString desc0)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_IGE = ID_IGE;
	this->m_ID_GR = ID_GR;
	this->m_IGE = IGE;
	this->m_mk = mk;
	this->m_mkz = mkz;
	this->m_strat = strat;
	this->m_desc0 = desc0;

	this->Update();
}

void SetIGE::AddNewRow(long ID_OBJ, long ID_IGE)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_IGE = ID_IGE;
	m_mk = 1.0;
	m_mkz = 1.0;

	this->Update();
}
bool SetIGE::Have_ID_IGE(long id_ige)
{
	bool res = false;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_IGE == id_ige)
				res = true;
			
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}
