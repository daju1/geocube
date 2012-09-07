// SetFizMeh.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetFizMeh.h"
#include "SetFizMehAllParam.h"
#include "SetZriz0.h"
#include "SetCilce0.h"

#include "../../excel_connect/src/MyExcel.h"

#define MEAN_PHYS_VYPROB 1

#include <math.h>

#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
long GetMaxPhysVyprobID(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB);
long GetFizMehVyprobForCut(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB, long id_cut_vyprob, long id_kolca)
{
	//return -6 * (id_cut_vyprob - 1) - 6 - id_kolca;
	long id_phys_vyprob = -1;
	SetZriz0 setZriz0(database);
	setZriz0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
		ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob);
	bool found_id_vyprob_for_first_kolco = false;
	long id_vyprob_for_first_kolco;
	if ( setZriz0.Open(CRecordset::dynaset) )
	{
		if (!setZriz0.IsBOF()) 
		{
			setZriz0.MoveFirst( );
			while(!setZriz0.IsEOF()) 
			{
				if (setZriz0.m_ID_KOLCA == 1)
				{
					found_id_vyprob_for_first_kolco = true;
					id_vyprob_for_first_kolco = setZriz0.m_ID_PHYS_VYPROB;
				}
				if (setZriz0.m_ID_KOLCA == id_kolca)
				{
					return setZriz0.m_ID_PHYS_VYPROB;
				}
				setZriz0.MoveNext(); // to validate record count
			}			
		}
	}
	if (found_id_vyprob_for_first_kolco)
	{
		return id_vyprob_for_first_kolco + id_kolca - 1;
	}
	else
	{
		long id_max_phys_vyprob = GetMaxPhysVyprobID(database, ID_OBJ, ID_KT, ID_PROB);
		if (id_max_phys_vyprob)
		{
			return id_max_phys_vyprob + id_kolca;
		}
		else
		{
			return MEAN_PHYS_VYPROB + id_kolca;
		}
	}
}

long GetFizMehVyprobForCompress(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB, long id_compress_vyprob, long id_kolca)
{
	//return 2 * (id_compress_vyprob - 1) + MEAN_PHYS_VYPROB + id_kolca;
	long id_phys_vyprob = -1;
	SetCilce0 setCilce0(database);
	setCilce0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
		ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob);
	bool found_id_vyprob_for_first_kolco = false;
	long id_vyprob_for_first_kolco;
	if ( setCilce0.Open(CRecordset::dynaset) )	
	{
		if (!setCilce0.IsBOF()) 
		{
			setCilce0.MoveFirst( );

			while(!setCilce0.IsEOF()) 
			{
				if (setCilce0.m_ID_KOLCA == 1)
				{
					found_id_vyprob_for_first_kolco = true;
					id_vyprob_for_first_kolco = setCilce0.m_ID_PHYS_VYPROB;
				}
				if (setCilce0.m_ID_KOLCA == id_kolca)
				{
					return setCilce0.m_ID_PHYS_VYPROB;
				}
				setCilce0.MoveNext(); // to validate record count
			}				
		}
	}
	if (found_id_vyprob_for_first_kolco)
	{
		return id_vyprob_for_first_kolco + id_kolca - 1;
	}
	else
	{
		long id_max_phys_vyprob = GetMaxPhysVyprobID(database, ID_OBJ, ID_KT, ID_PROB);
		if (id_max_phys_vyprob)
		{
			return id_max_phys_vyprob + id_kolca;
		}
		else
		{
			return MEAN_PHYS_VYPROB + id_kolca;
		}
	}
}

long GetMaxPhysVyprobID(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB)
{
	SetZriz0 setZriz0(database);
	setZriz0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, ID_KT, ID_PROB);
	if ( !setZriz0.Open(CRecordset::dynaset) )
		return NULL;

	long max_zriz_phys_vyprob = setZriz0.GetMaxPhysVyprobID();

	SetCilce0 setCilce0(database);
	setCilce0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, ID_KT, ID_PROB);
	if ( !setCilce0.Open(CRecordset::dynaset) )
		return NULL;

	long max_cilce_phys_vyprob = setCilce0.GetMaxPhysVyprobID();

	return max(max_zriz_phys_vyprob, max_cilce_phys_vyprob);
}

const char * GetPhysicalVyprobString(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB, long id_phys_vyprob)
{
	char str[128];

	if (id_phys_vyprob == MEAN_PHYS_VYPROB)
	{
		return "среднее";
	}

	SetZriz0 setZriz0(database);
	setZriz0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, ID_KT, ID_PROB);
	if ( !setZriz0.Open(CRecordset::dynaset) )
		return NULL;

	if (!setZriz0.IsBOF()) 
	{
		setZriz0.MoveFirst( );

		while(!setZriz0.IsEOF()) 
		{
			if (setZriz0.m_ID_PHYS_VYPROB == id_phys_vyprob)
			{
				sprintf(str, "%d-ое кольцо %d-го среза id_phys_vyprob = %d", setZriz0.m_ID_KOLCA, setZriz0.m_ID_VYPROB, id_phys_vyprob);
				return _strdup( str );
			}
			setZriz0.MoveNext(); // to validate record count
		}
		
	}

	SetCilce0 setCilce0(database);
	setCilce0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, ID_KT, ID_PROB);
	if ( !setCilce0.Open(CRecordset::dynaset) )
		return NULL;

	if (!setCilce0.IsBOF()) 
	{
		setCilce0.MoveFirst( );

		while(!setCilce0.IsEOF()) 
		{
			if (setCilce0.m_ID_PHYS_VYPROB == id_phys_vyprob)
			{
				sprintf(str, "%d-ое кольцо %d-й компр. id_phys_vyprob = %d", setCilce0.m_ID_KOLCA, setCilce0.m_ID_VYPROB, id_phys_vyprob);
				return _strdup( str );
			}		
			setCilce0.MoveNext(); // to validate record count
		}				
	}

	sprintf(str, "id_phys_vyprob = %d", id_phys_vyprob);
	return _strdup( str );
	return "";
}



/////////////////////////////////////////////////////////////////////////////
// SetFizMeh

IMPLEMENT_DYNAMIC(SetFizMeh, CRecordset)

SetFizMeh::SetFizMeh(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetFizMeh)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_ID_PARAM = 0;
	m_VAL = 0.0;
	m_bSTAT = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetFizMeh::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetFizMeh::GetDefaultSQL()
{
	return _T("[FizMeh]");
}

void SetFizMeh::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetFizMeh)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Long(pFX, _T("[ID_PARAM]"), m_ID_PARAM);
	RFX_Double(pFX, _T("[VAL]"), m_VAL);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetFizMeh diagnostics

#ifdef _DEBUG
void SetFizMeh::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetFizMeh::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
void SetFizMeh::AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, long ID_PARAM, double val)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_PROB = ID_PROB;
	this->m_ID_VYPROB = ID_VYPROB;
	this->m_ID_PARAM = ID_PARAM;
	this->m_VAL = val;
	this->m_bSTAT = 1;
	this->Update();
}

int SetFizMeh::GetMeanParam(long ID_OBJ, long ID_KT, long ID_PROB, long ID_PARAM, 
							double &val_from_db, double &mean_of_vyprob)
{
	int res = 0;
	vector<double> vyprob;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_OBJ == ID_OBJ && this->m_ID_KT == ID_KT && this->m_ID_PROB == ID_PROB)
			{
				if (this->m_ID_PARAM == ID_PARAM)
				{
					if (this->m_ID_VYPROB == MEAN_PHYS_VYPROB)
					{
						val_from_db = this->m_VAL;
						res = 1;
					}
					else
					{
						vyprob.push_back(this->m_VAL);
					}
				}		
			}
			this->MoveNext(); // to validate record count
		}
	}
	mean_of_vyprob = 0.0;
	int n = 0;
	for (vector<double>::iterator it = vyprob.begin();
		it != vyprob.end(); it++)
	{
		n++;
		mean_of_vyprob += (*it);
	}
	if (n)
	{
		mean_of_vyprob /= n;
		if (!res)
		{
			res = 2;//возвращЄн только второй параметр среднее испытаний
		}
		else
		{
			res = 3;// возвращены и первый и второй параметры: среднее из базы и среднее испытаний
		}
	}
	return res;
}

int SetFizMeh::GetParam(long ID_OBJ, long ID_KT, long ID_PROB, long ID_PARAM, long ID_VYPROB, 
							double &val)
{
	int res = 0;
	vector<double> vyprob;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_OBJ == ID_OBJ && 
				this->m_ID_KT == ID_KT && 
				this->m_ID_PROB == ID_PROB &&
				this->m_ID_PARAM == ID_PARAM &&
				this->m_ID_VYPROB == ID_VYPROB)
			{
				val = this->m_VAL;
				res = 1;
			}
			
			this->MoveNext(); // to validate record count
		}
	}
	return res;
}

int SetFizMeh::ReplaceParam(long ID_OBJ, long ID_KT, long ID_PROB, long LAB_N, 
							long ID_PARAM, long ID_VYPROB, 
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
				this->m_ID_PARAM == ID_PARAM &&
				this->m_ID_VYPROB == ID_VYPROB)
			{
				found_val = true;
				if (fabs (this->m_VAL - val) >= digits_epsilon)	
				{
					CString sParam = "";
					sParam.Format("ID_PARAM = %d", ID_PARAM);
					SetFizMehAllParam setFizMehAllParam(this->m_pDatabase);
					setFizMehAllParam.m_strFilter.Format("ID_PARAM = %d", ID_PARAM);
					if (setFizMehAllParam.Open(CRecordset::dynaset) )
					{
						if (!setFizMehAllParam.IsBOF()) 
						{
							setFizMehAllParam.MoveFirst();
							if(!setFizMehAllParam.IsEOF()) 
							{
								sParam = setFizMehAllParam.m_NAZVA_R;
							}
						}
					}


					CString s;
					s.Format(" %s = %f\n"
						"по лабораторному номеру %d\n"
						"ID_VYPROB = %d\n"
						"%s\n"
						"уже имеютс€ в базе\n"
						"«аменить на новое значение = %f?", 
						sParam, this->m_VAL, LAB_N, ID_VYPROB, 
						GetPhysicalVyprobString(this->m_pDatabase, ID_OBJ, ID_KT, ID_PROB, ID_VYPROB), 
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
		this->AddNewRow(ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM, val);	
		return 2;
	}
	return 0;
}