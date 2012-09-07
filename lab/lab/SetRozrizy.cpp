// SetRozrizy.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetRozrizy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetRozrizy

IMPLEMENT_DYNAMIC(SetRozrizy, CRecordset)

SetRozrizy::SetRozrizy(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetRozrizy)
	m_ID_OBJ = 0;
	m_ID_ROZRIZ = 0;
	m_NOMER = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetRozrizy::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetRozrizy::GetDefaultSQL()
{
	return _T("[Rozrizy]");
}

void SetRozrizy::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetRozrizy)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_ROZRIZ]"), m_ID_ROZRIZ);
	RFX_Text(pFX, _T("[NOMER]"), m_NOMER);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetRozrizy diagnostics

#ifdef _DEBUG
void SetRozrizy::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetRozrizy::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
long SetRozrizy::GetNewKeyID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_ROZRIZ > id)
				id = this->m_ID_ROZRIZ;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}
void SetRozrizy::AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NOMER = NOMER;

	this->Update();
}