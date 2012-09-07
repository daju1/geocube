// SetProbGr.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetProbGr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetProbGr

IMPLEMENT_DYNAMIC(SetProbGr, CRecordset)

SetProbGr::SetProbGr(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetProbGr)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_H = 0.0;
	m_LAB_N = 0;
	m_ID_KODPROB = 0;
	m_ID_GR = 0;
	m_GRUNT_NAME = _T("");
	m_nFields = 9;
	m_ID_IGE = 0;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetProbGr::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetProbGr::GetDefaultSQL()
{
	return _T("[ProbGr]");
}

void SetProbGr::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetProbGr)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Long(pFX, _T("[LAB_N]"), m_LAB_N);
	RFX_Long(pFX, _T("[ID_KODPROB]"), m_ID_KODPROB);
	RFX_Text(pFX, _T("[GRUNT_NAME]"), m_GRUNT_NAME);
	RFX_Long(pFX, _T("[ID_GR]"), m_ID_GR);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetProbGr diagnostics

#ifdef _DEBUG
void SetProbGr::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetProbGr::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
long SetProbGr::GetNewKeyID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_PROB > id)
				id = this->m_ID_PROB;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}
bool SetProbGr::Have_LAB_N(long lab_n, long & ID_PROB)
{
	bool res = false;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_LAB_N == lab_n)
			{
				ID_PROB = this->m_ID_PROB;
				res = true;
				break;
			}
			
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}
void SetProbGr::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB,
                          double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_H = H;
	this->m_LAB_N = LAB_N;
	this->m_ID_KODPROB = ID_KODPROB;
	this->m_GRUNT_NAME = GRUNT_NAME;
	this->m_ID_GR = ID_GR;
	this->Update();
}


void SetProbGr::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB,
                          double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME, 
						  long ID_IGE)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_H = H;
	this->m_LAB_N = LAB_N;
	this->m_ID_KODPROB = ID_KODPROB;
	this->m_GRUNT_NAME = GRUNT_NAME;
	this->m_ID_GR = ID_GR;
	this->m_ID_IGE = ID_IGE;
	this->Update();
}

bool SetProbGr::Having_LAB_N_Edit(long lab_n, 
	long ID_OBJ, long ID_KT, long ID_PROB,
	double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME,
    long ID_IGE)
{
	bool res = false;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_LAB_N == lab_n)
			{
				this->Edit();
				this->m_ID_OBJ = ID_OBJ;
				this->m_ID_KT = ID_KT;
				this->m_ID_PROB = ID_PROB;
				this->m_H = H;
				this->m_LAB_N = LAB_N;
				this->m_ID_KODPROB = ID_KODPROB;
				this->m_GRUNT_NAME = GRUNT_NAME;
				this->m_ID_GR = ID_GR;
				this->m_ID_IGE = ID_IGE;
				this->Update();
			}
			
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}


bool SetProbGr::Having_LAB_N_Edit(long lab_n, 
	long ID_OBJ, long ID_KT, long ID_PROB,
	double H, long LAB_N, long ID_KODPROB, long ID_GR, CString GRUNT_NAME)
{
	bool res = false;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_LAB_N == lab_n)
			{
				this->Edit();
				this->m_ID_OBJ = ID_OBJ;
				this->m_ID_KT = ID_KT;
				this->m_ID_PROB = ID_PROB;
				this->m_H = H;
				this->m_LAB_N = LAB_N;
				this->m_ID_KODPROB = ID_KODPROB;
				this->m_GRUNT_NAME = GRUNT_NAME;
				this->m_ID_GR = ID_GR;

				this->Update();
			}
			
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}