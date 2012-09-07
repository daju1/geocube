// ExcelDxfRozrizList.cpp: implementation of the ExcelDxfRozrizList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelDxfRozrizList.h"

#include "SetObject.h"
#include "SetKT.h"
#include "SetRozriz.h"
#include "SetRozrizy1.h"

#include "labView.h"
#include "../../excel_connect/src/ExcelColChar.h"

#include "DlgNRows.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelDxfRozrizList::ExcelDxfRozrizList()
{
	m_fc = 'J';
}

ExcelDxfRozrizList::~ExcelDxfRozrizList()
{

}
void ExcelDxfRozrizList::InitExt()
{
	ext					= "drl";
	xl_filter_name		= "Список Dxf разрезов";
	xl_form				= "DxfRozrizList";
}
bool FindDxfRozriz(CDatabase * database, long ID_OBJ, long & ID_ROZRIZ, CString NOMER)
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
long GetID_KT(CDatabase * database, long id_obj, CString nazva)
{
	long ID_KT = -1;
	CString strQuery;
	strQuery.Format("select * from [KT]");	

	CString where;
	where.Format("ID_OBJ = %d and NAZVA = '%s'", id_obj, nazva);

	CRecordset * _pRecordset = new CRecordset(database);

	try {
		_pRecordset->m_strFilter = where;
		_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly);
	}
	catch (CDBException* pe) {
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		_pRecordset->Close();
		delete _pRecordset;
		return ID_KT;
	}

	if (!_pRecordset->IsBOF())
	{
		_pRecordset->MoveFirst();
		
		CDBVariant _var; // must declare this inside the loop
		_pRecordset->GetFieldValue("ID_KT", _var);

		ID_KT = _var.m_lVal;
	}

	_pRecordset->Close();
	delete _pRecordset;

	return ID_KT;
}









void SaveDxfRozriz(CDatabase * database, MyExcel & m_excel, long ID_OBJ, long & ID_ROZRIZ, CString NOMER, int r, char fc, 
				   CString fn_dxf, double z1w, double y1a, double z2w, double y2a)
{
	if ( !FindDxfRozriz(database, ID_OBJ, ID_ROZRIZ, NOMER) )
	{
		SetRozrizy setRozrizy(database);
		setRozrizy.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setRozrizy.m_strSort.Format("");
		if ( !setRozrizy.Open(CRecordset::dynaset) )
			return;	

		ID_ROZRIZ = setRozrizy.GetNewKeyID();
		setRozrizy.AddNewRow(ID_OBJ, ID_ROZRIZ, NOMER, fn_dxf, z1w, y1a, z2w, y2a);
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
					setRozrizy.m_has_dxf = 1;
					setRozrizy.m_fn_dxf = fn_dxf;
					setRozrizy.m_acad_yscale_loaded = 1;
					setRozrizy.m_z1w = z1w;
					setRozrizy.m_y1a = y1a;
					setRozrizy.m_z2w = z2w;
					setRozrizy.m_y2a = y2a;
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
		CString kt_nazva;
		if (!ExcelRange_GetStringValue(m_excel, S, kt_nazva))
		{
			break;
		}
		long ID_KT = GetID_KT(database, ID_OBJ, kt_nazva);

		double dxf_x = 0.0;
		bool dxf_x_defined = false;
		sprintf(S, "%s%d", ecc.Get(), r+1);		
		if (ExcelRange_GetValue(m_excel, S, dxf_x))
		{
			dxf_x_defined = true;
		}

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
					if (dxf_x_defined)
						setRozriz.m_dxf_x = dxf_x;

					setRozriz.Update();
				}
			}
			if (!found_kt)
			{
				if (dxf_x_defined)
					setRozriz.AddNewRow(ID_OBJ, ID_ROZRIZ, NPP, ID_KT, dxf_x);
				else
					setRozriz.AddNewRow(ID_OBJ, ID_ROZRIZ, NPP, ID_KT);
			}
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

CString GetKTName(CDatabase * database, long id_obj, long id_kt);

void FillDxfRozriz(CDatabase * database, MyExcel & m_excel, long ID_OBJ, long ID_ROZRIZ, int r, char fc)
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
				sprintf(S, "A%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_NOMER));
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);
			}
		}
	}

	sprintf(S, "B%d", r);
	ExcelRange_SetValue(m_excel, S, COleVariant(ID_ROZRIZ));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);

	if (setRozrizy.m_has_dxf)
	{
		sprintf(S, "C%d", r);
		ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_fn_dxf));
		ExcelRange_SetThinContinuousBorders(m_excel, S);
		ExcelRange_CenterHorizontalAlignment(m_excel, S);
	}

	if (setRozrizy.m_acad_yscale_loaded)
	{
		sprintf(S, "D%d", r);
		ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_z1w));
		ExcelRange_SetThinContinuousBorders(m_excel, S);
		ExcelRange_CenterHorizontalAlignment(m_excel, S);

		sprintf(S, "E%d", r);
		ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_y1a));
		ExcelRange_SetThinContinuousBorders(m_excel, S);
		ExcelRange_CenterHorizontalAlignment(m_excel, S);

		sprintf(S, "F%d", r);
		ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_z2w));
		ExcelRange_SetThinContinuousBorders(m_excel, S);
		ExcelRange_CenterHorizontalAlignment(m_excel, S);

		sprintf(S, "G%d", r);
		ExcelRange_SetValue(m_excel, S, COleVariant(setRozrizy.m_y2a));
		ExcelRange_SetThinContinuousBorders(m_excel, S);
		ExcelRange_CenterHorizontalAlignment(m_excel, S);
	}

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
			ExcelRange_SetValue(m_excel, S, COleVariant(GetKTName(database, ID_OBJ, setRozriz.m_ID_KT)));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "%s%d", ecc.Get(), r+1);
			ExcelRange_SetValue(m_excel, S, COleVariant(setRozriz.m_dxf_x));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			ecc.Increment();
			setRozriz.MoveNext();
		}
	}
}
void FillRozrizHeader(MyExcel & m_excel, int r, char fc)
{
	char S[64];

	sprintf(S, "%c%d:%c%d", fc-2, r, fc-1, r);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("Выработка"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);

	sprintf(S, "%c%d:%c%d", fc-2, r+1, fc-1, r+1);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("Её X коорд.в Acad"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);
}


bool ExcelDxfRozrizList::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];
	int fr = 11;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		int r = fr;

		int max_rows_user_def = 0;

		CDlgNRows dialog;
		dialog.DoModal();
		if (dialog.ok_pressed)
		{
			max_rows_user_def = fr + 2 * atoi(dialog.m_edit);
		}

		/*SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

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
		}*/


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


					FillDxfRozriz(this->p_database, m_excel, ID_OBJ, ID_ROZRIZ, r, fc);
					r+=2;

				}
				setRozriz.MoveNext();
			}
		}	
		
		int max_rows = max(max_rows_user_def, r);

		for( r = fr; r < max_rows; r+=2)
		{
			for (char c = 'A'; c <= 'G'; c++)
			{
				sprintf(S, "%c%d:%c%d", c, r, c, r+1);
				ExcelRange_SetMerge(m_excel, S);
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterVerticalAlignment(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);
			}
			FillRozrizHeader(m_excel, r, fc);
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

void ExcelDxfRozrizList::virSaveToDB()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return;
	}

	char S[64];
	int fr = 11;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		char fc = m_fc;

		for (int r = fr; ;r+=2)
		{
			CString NOMER;
			sprintf(S, "A%d", r);				
			if (ExcelRange_GetStringValue(m_excel, S, NOMER))
			{
				long ID_ROZRIZ = -1;
				double val;
				sprintf(S, "B%d", r);				
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					ID_ROZRIZ = long(val);
				}
				double z1w = 0.0;
				double y1a = 0.0;
				double z2w = 1.0;
				double y2a = 1.0;

				CString fn_dxf;
				sprintf(S, "C%d", r);				
				if (ExcelRange_GetStringValue(m_excel, S, fn_dxf))
				{
				}

				sprintf(S, "D%d", r);				
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					z1w = val;
				}
				sprintf(S, "E%d", r);				
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					y1a = val;
				}

				sprintf(S, "F%d", r);				
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					z2w = val;
				}
				sprintf(S, "G%d", r);				
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					y2a = val;
				}


				SaveDxfRozriz(this->p_database, m_excel, ID_OBJ, ID_ROZRIZ, NOMER, r, fc, fn_dxf, z1w, y1a, z2w, y2a);
				sprintf(S, "B%d", r);				
				ExcelRange_SetValue(m_excel, S, COleVariant(ID_ROZRIZ));
			}
			else
			{
				break;		
			}
		}

		//CString where;
		//if (this->is_geo)
		//	where.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, id_kt);
			
		//if (this->is_lab)
		//	where.Format("ID_OBJ = %d", ID_OBJ);
		//this->m_lab_view->UpdateProbGruntListCtrl(where, "ID_KT, ID_PROB");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}