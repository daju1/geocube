// SetGranular.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGranular.h"
#include "SetGranularAll_2.h"

#include <math.h>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

CString GetGranularFraction(CDatabase * database, long id_gran);


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGranular

IMPLEMENT_DYNAMIC(SetGranular, CRecordset)

SetGranular::SetGranular(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGranular)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_GRAN = 0;
	m_VAL = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGranular::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetGranular::GetDefaultSQL()
{
	return _T("[Granular]");
}

void SetGranular::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGranular)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_GRAN]"), m_ID_GRAN);
	RFX_Double(pFX, _T("[VAL]"), m_VAL);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGranular diagnostics

#ifdef _DEBUG
void SetGranular::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGranular::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetGranular::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_GRAN, double val)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_ID_GRAN = ID_GRAN;
	this->m_VAL = val;
	this->Update();
}
int SetGranular::ReplaceGranContent(long ID_OBJ, long ID_KT, long ID_PROB, long LAB_N, 
									GranVyprob & gran_vyprob)
{
	double digits_epsilon = 1e-8;

	map<long, GranVyprobData1> gran_content;
	gran_vyprob.FillGranContentMap(gran_content);

	bool found_values = false;

	size_t gran_content_size = gran_content.size();
	size_t my_size = 0;
	size_t found_size = 0;
	size_t equial_size = 0;

	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_OBJ == ID_OBJ && 
				this->m_ID_KT == ID_KT && 
				this->m_ID_PROB == ID_PROB)
			{
				found_values = true;
				my_size++;

				this->m_ID_GRAN;
				this->m_VAL;

				map<long, GranVyprobData1>::iterator found = gran_content.find(this->m_ID_GRAN);
				if (found != gran_content.end())
				{
					found_size++;
					if (fabs (this->m_VAL - (*found).second.val) < digits_epsilon)
					{
						equial_size++;
					}
				}
			}
			this->MoveNext();
		}
	}

	if (!found_values)
	{
		for (map<long, GranVyprobData1>::iterator it = gran_content.begin();
			it != gran_content.end(); it++)
		{
			if ((*it).second.val)
			{
				this->AddNewRow(ID_OBJ, ID_KT, ID_PROB, (*it).first, (*it).second.val);	
			}
		}
		
		return 2;
	}
	 
	bool the_same = gran_content_size == my_size
		&& my_size == found_size
		&& found_size == equial_size;

	if (the_same)
	{
		CString s;
		s.Format(
			"В базе под лабораторным номером %d\n уже имеется полностью аналогичный грансостав\n",
			LAB_N);

		AfxMessageBox(s);
		return 0;
	}

	/*CString str;
	str.Format(
		"gran_content_size = %d\n"
		"my_size = %d\n"
		"found_size = %d\n"
		"equial_size = %d\n"
		,
		gran_content_size,
		my_size,
		found_size,
		equial_size);
	AfxMessageBox(str);*/
	
	std::sort(gran_vyprob.data1.begin(), gran_vyprob.data1.end());
	CString description = gran_vyprob.GetDescription().c_str();

	GranVyprob my_gran_vyprob;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{			
			my_gran_vyprob.AddGranular(this->m_ID_GRAN, GetGranularFraction(this->m_pDatabase, this->m_ID_GRAN), this->m_VAL);
			this->MoveNext();
		}
	}

	std::sort(my_gran_vyprob.data1.begin(), my_gran_vyprob.data1.end());
	CString my_description = gran_vyprob.GetDescription().c_str();

	CString s;
	s.Format(
		"В базе под лабораторным номером %d\n уже имеется грансостав:\n"
		"%s\n"
		"Заменить ли его новым грансоставом:\n"
		"%s\n",
		LAB_N, my_description, description);

	bool to_replace = IDYES == AfxMessageBox(s, MB_YESNO);

	if (to_replace)
	{
		if (!this->IsBOF()) 
		{
			this->MoveFirst();

			while(!this->IsEOF()) 
			{
				this->Delete();
				this->MoveNext(); // to validate record count
			}
		}
		for (map<long, GranVyprobData1>::iterator it = gran_content.begin();
			it != gran_content.end(); it++)
		{
			//if ((*it).second.val)
			//{
				this->AddNewRow(ID_OBJ, ID_KT, ID_PROB, (*it).first, (*it).second.val);	
			//}
		}
		return 1;
	}


	return -1;
}

int SetGranular::GetGran(long ID_OBJ, long ID_KT, long ID_PROB, long ID_GRAN, 
							double &val)
{
	int res = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_OBJ == ID_OBJ && 
				this->m_ID_KT == ID_KT && 
				this->m_ID_PROB == ID_PROB &&
				this->m_ID_GRAN == ID_GRAN)
			{
				val = this->m_VAL;
				res = 1;	
				return res;
			}		
		
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}

int SetGranular::ReplaceGran(long ID_OBJ, long ID_KT, long ID_PROB, long LAB_N, 
							long ID_GRAN, 
							double val)
{
	double digits_epsilon = 1e-8;

	bool found_val = false;

	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_OBJ == ID_OBJ && 
				this->m_ID_KT == ID_KT && 
				this->m_ID_PROB == ID_PROB &&
				this->m_ID_GRAN == ID_GRAN)
			{
				found_val = true;
				if (fabs (this->m_VAL - val) >= digits_epsilon)	
				{
					CString sParam = "";
					sParam.Format("ID_GRAN = %d", ID_GRAN);
					SetGranularAll_2 setGranularAll_2(this->m_pDatabase);
					setGranularAll_2.m_strFilter.Format("ID_GRAN = %d", ID_GRAN);
					if (setGranularAll_2.Open(CRecordset::dynaset) )
					{
						if (!setGranularAll_2.IsBOF()) 
						{
							setGranularAll_2.MoveFirst();
							if(!setGranularAll_2.IsEOF()) 
							{
								sParam = setGranularAll_2.m_NAZVA;
							}
						}
					}


					CString s;
					s.Format(" %s = %f\n"
						"по лабораторному номеру %d\n"
						"уже имеются в базе значение грансостава\n"
						"Заменить на новое значение = %f?", 
						sParam, this->m_VAL, 
						LAB_N, 
						val);

					if (IDYES == MessageBox(0,s,"virSaveToDB()", MB_YESNO) )
					{
						this->Edit();
						this->m_VAL = val;
						this->Update();
						return 1;
					}
					else
						return -1;
				}
			}
			this->MoveNext();
		}
	}
	if (!found_val)
	{
		this->AddNewRow(ID_OBJ, ID_KT, ID_PROB, ID_GRAN, val);	
		return 2;
	}
	return 0;
}