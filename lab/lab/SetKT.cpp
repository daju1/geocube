// SetKT.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetKT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetKT

IMPLEMENT_DYNAMIC(SetKT, CRecordset)

SetKT::SetKT(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetKT)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_NAZVA = _T("");
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
	m_ID_TYP = 0;
	m_ID_BUR = 0;
	m_D_BUR = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetKT::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetKT::GetDefaultSQL()
{
	return _T("[KT]");
}

void SetKT::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetKT)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	RFX_Double(pFX, _T("[X]"), m_X);
	RFX_Double(pFX, _T("[Y]"), m_Y);
	RFX_Double(pFX, _T("[Z]"), m_Z);
	RFX_Long(pFX, _T("[ID_TYP]"), m_ID_TYP);
	RFX_Long(pFX, _T("[ID_BUR]"), m_ID_BUR);
	RFX_Long(pFX, _T("[D_BUR]"), m_D_BUR);
	RFX_Date(pFX, _T("[DTBUR]"), m_DTBUR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetKT diagnostics

#ifdef _DEBUG
void SetKT::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetKT::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
long SetKT::GetNewKeyID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_KT > id)
				id = this->m_ID_KT;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}

bool SetKT::Have_ID_KT(long id_kt)
{
	bool res = false;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_KT == id_kt)
				res = true;
			
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}