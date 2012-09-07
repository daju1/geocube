// ExcelRozrizList.cpp: implementation of the ExcelRozrizList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelRozrizList.h"

#include "SetObject.h"
#include "SetKT.h"
#include "SetRozriz.h"
#include "SetRozrizy1.h"

#include "labView.h"
#include "../../excel_connect/src/ExcelColChar.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelRozrizList::ExcelRozrizList()
{
	m_fc = 'G';
}

ExcelRozrizList::~ExcelRozrizList()
{

}
void ExcelRozrizList::InitExt()
{
	ext					= "rzl";
	xl_filter_name		= "Список разрезов";
	xl_form				= "RozrizList";
}
bool FindRozriz(CDatabase * database, long ID_OBJ, long & ID_ROZRIZ, CString NOMER)
{
	bool found = false;

	SetRozrizy setRozrizy(database);
	setRozrizy.m_strFilter.Format("ID_OBJ = %d and NOMER = '%s'", ID_OBJ, NOMER);
	setRozrizy.m_strSort.Format("");
	if (setRozrizy.Open(CRecordset::dynaset) )
	{
		if (!setRozrizy.IsBOF()) 
		{
			setRozrizy.MoveFirst( );
			if (!setRozrizy.IsEOF()) 
			{
				ID_ROZRIZ = setRozrizy.m_ID_ROZRIZ;
				found = 1;
			}
		}
	}





	return found;
}
void SaveRozriz(CDatabase * database, MyExcel & m_excel, long ID_OBJ, long & ID_ROZRIZ, CString NOMER, int r, char fc)
{
	if ( !FindRozriz(database, ID_OBJ, ID_ROZRIZ, NOMER) )
	{
		SetRozrizy setRozrizy(database);
		setRozrizy.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setRozrizy.m_strSort.Format("");
		if ( !setRozrizy.Open(CRecordset::dynaset) )
			return;	

		ID_ROZRIZ = setRozrizy.GetNewKeyID();
		setRozrizy.AddNewRow(ID_OBJ, ID_ROZRIZ, NOMER);
	}
	else
	{
		SetRozrizy setRozrizy(database);
		setRozrizy.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", ID_OBJ, ID_ROZRIZ);
		setRozrizy.m_strSort.Format("");
		if (setRozrizy.Open(CRecordset::dynaset) )
		{
			if (!setRozrizy.IsBOF()) 
			{
				setRozrizy.MoveFirst( );
				if (!setRozrizy.IsEOF()) 
				{
					setRozrizy.Edit();
					setRozrizy.m_NOMER = NOMER;
					setRozrizy.Update();
				}
			}
		}

		SetRozriz setRozriz(database);
		setRozriz.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", ID_OBJ, ID_ROZRIZ);
		setRozriz.m_strSort.Format("ID_ROZRIZ, NPP");
		if (setRozriz.Open(CRecordset::dynaset) )
		{
			if (!setRozriz.IsBOF()) 
			{
				setRozriz.MoveFirst( );
				while (!setRozriz.IsEOF()) 
				{
					setRozriz.Edit();
					setRozriz.m_NPP = -1;
					setRozriz.Update();

					setRozriz.MoveNext();
				}
			}
		}

	}

	char S[64];


	double val;
	ExcelColChar ecc(fc);

	long NPP = 1;
	while (true)
	{
		sprintf(S, "%s%d", ecc.Get(), r);		
		if (!ExcelRange_GetValue(m_excel, S, val))
		{
			break;
		}
		long ID_KT = long(val);

		SetRozriz setRozriz(database);
		setRozriz.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d and ID_KT = %d", ID_OBJ, ID_ROZRIZ, ID_KT);
		setRozriz.m_strSort.Format("");
		if ( setRozriz.Open(CRecordset::dynaset) )
		{
			bool found_kt = false;
			if (!setRozriz.IsBOF()) 
			{
				setRozriz.MoveFirst( );
				if (!setRozriz.IsEOF()) 
				{
					found_kt = true;

					setRozriz.Edit();

					setRozriz.m_ID_OBJ = ID_OBJ;
					setRozriz.m_ID_ROZRIZ = ID_ROZRIZ;
					setRozriz.m_NPP = NPP;
					setRozriz.m_ID_KT = ID_KT;

					setRozriz.Update();
				}
			}
			if (!found_kt)
				setRozriz.AddNewRow(ID_OBJ, ID_ROZRIZ, NPP, ID_KT);
		}
		
		ecc.Increment();
		NPP++;
	}
	
	
	SetRozriz setRozriz(database);
	setRozriz.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d and NPP = -1", ID_OBJ, ID_ROZRIZ);
	setRozriz.m_strSort.Format("ID_ROZRIZ, NPP");
	if (setRozriz.Open(CRecordset::dynaset) )
	{
		if (!setRozriz.IsBOF()) 
		{
			setRozriz.MoveFirst( );
			while (!setRozriz.IsEOF()) 
			{
				setRozriz.Delete();
				setRozriz.MoveNext();
			}
		}
	}
}

void FillRozriz(CDatabase * database, MyExcel & m_excel, long ID_OBJ, long ID_ROZRIZ, int r, char fc)
{
	char S[64];

	SetRozrizy setRozrizy(database);
	setRozrizy.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", ID_OBJ, ID_ROZRIZ);
	setRozrizy.m_strSort.Format("");
	if (setRozrizy.Open(CRecordset::dynaset) )
	{
		if (!setRozrizy.IsBOF()) 
		{
			setRozrizy.MoveFirst( );
			if (!setRozrizy.IsEOF()) 
			{
				sprintf(S, "E%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_NOMER));
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);
			}
		}
	}

	sprintf(S, "F%d", r);
	ExcelRange_SetValue(m_excel, S, COleVariant(ID_ROZRIZ));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);

	ExcelColChar ecc(fc);

	SetRozriz setRozriz(database);
	setRozriz.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", ID_OBJ, ID_ROZRIZ);
	setRozriz.m_strSort.Format("ID_ROZRIZ, NPP");
	if ( !setRozriz.Open(CRecordset::dynaset) )
		return;	


	if (!setRozriz.IsBOF()) 
	{
		setRozriz.MoveFirst( );
		while (!setRozriz.IsEOF()) 
		{
			sprintf(S, "%s%d", ecc.Get(), r);
			ExcelRange_SetValue(m_excel, S, COleVariant(setRozriz.m_ID_KT));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			ecc.Increment();
			setRozriz.MoveNext();
		}
	}
}

bool ExcelRozrizList::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		int r = fr;
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			while(!setKT.IsEOF()) 
			{
				sprintf(S, "B%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_ID_KT));
				sprintf(S, "C%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));

				setKT.MoveNext();
				r++;
			}
		}


		SetRozriz setRozriz(this->p_database);
		setRozriz.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setRozriz.m_strSort.Format("ID_ROZRIZ, NPP");
		if ( !setRozriz.Open(CRecordset::dynaset) )
			return false;	

		long ID_ROZRIZ = -1;

		r = fr;
		char fc = m_fc;

		if (!setRozriz.IsBOF()) 
		{
			setRozriz.MoveFirst( );
			while (!setRozriz.IsEOF()) 
			{
				if (ID_ROZRIZ != setRozriz.m_ID_ROZRIZ)
				{
					ID_ROZRIZ = setRozriz.m_ID_ROZRIZ;


					FillRozriz(this->p_database, m_excel, ID_OBJ, ID_ROZRIZ, r, fc);
					r++;
				}
				setRozriz.MoveNext();
			}
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
		
	return true;
}

void ExcelRozrizList::virSaveToDB()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return;
	}

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		char fc = m_fc;

		for (int r = fr; ;r++)
		{
			CString NOMER;
			sprintf(S, "E%d", r);				
			if (ExcelRange_GetStringValue(m_excel, S, NOMER))
			{
				long ID_ROZRIZ = -1;
				double val;
				sprintf(S, "F%d", r);				
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					ID_ROZRIZ = long(val);
				}
				SaveRozriz(this->p_database, m_excel, ID_OBJ, ID_ROZRIZ, NOMER, r, fc);
				ExcelRange_SetValue(m_excel, S, COleVariant(ID_ROZRIZ));
			}
			else
			{
				break;		
			}
		}

		CString where;
		//if (this->is_geo)
		//	where.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, id_kt);
			
		//if (this->is_lab)
			where.Format("ID_OBJ = %d", ID_OBJ);
		//this->m_lab_view->UpdateProbGruntListCtrl(where, "ID_KT, ID_PROB");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}