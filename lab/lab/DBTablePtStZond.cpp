// DBTablePtStZond.cpp: implementation of the DBTablePtStZond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "LabDoc.h"
#include "myListCtrl.h"
#include "DBTablePtStZond.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTablePtStZond::DBTablePtStZond(const char * tbnm) : DBTable (tbnm)
{

}

DBTablePtStZond::~DBTablePtStZond()
{

}

bool GetUstanovka(CDatabase * database, 
				  long id_ust, 

				  CString & ust_name,
				  long & typ_zond,
				  long & n_shema,

				  double & Kg,
				  double & Kf,

				  double & Bg,
				  double & Bf,

				  double & shtanga_d
				  )
{
	CString strQuery;
	strQuery.Format("select * from [Ustanovka]");	

	CString where;
	where.Format("ID_UST = %ld", id_ust);

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
		return false;
	}

	if (!_pRecordset->IsBOF())
	{
		_pRecordset->MoveFirst();


		for (int iSubItem = 1; iSubItem < 9; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop
			_pRecordset->GetFieldValue(iSubItem, var);
				

			switch (iSubItem)
			{
			case 0:
				{
					//ID_UST
				}
				break;
			case 1:
				{
					//NAZVA
					ust_name = CMyListCtrl::GetFieldString(var);
				}
				break;
			case 2:
				{
					//TYP_ZOND
					typ_zond = var.m_lVal;
				}
				break;
			case 3:
				{
					//N_SHEMA
					n_shema = var.m_lVal;
				}
				break;
			case 4:
				{
					//Kg
					Kg = var.m_dblVal;
				}
				break;
			case 5:
				{
					//Kf
					Kf = var.m_dblVal;
				}
				break;
			case 6:
				{
					//Bg
					Bg = var.m_dblVal;
				}
				break;
			case 7:
				{
					//Bf
					Bf = var.m_dblVal;
				}
				break;
			case 8:
				{
					//Shtanga_d
					shtanga_d = var.m_dblVal;
				}
				break;

			}
		}
	}

	delete _pRecordset;

	return true;
}



void DBTablePtStZond::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt, id_ust;
	double glyb;

	for (int iSubItem = 0; iSubItem < 4; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem, var);
			

		switch (iSubItem)
		{
		case 0:
			{
				//ID_OBJ
				id_obj = var.m_lVal;
			}
			break;
		case 1:
			{
				//ID_KT
				id_kt = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_UST
				id_ust = var.m_lVal;
			}
			break;
		case 3:
			{
				//GLYB
				glyb = var.m_dblVal;
			}
			break;
		}
	}

	CString ust_name;
	long typ_zond, n_shema;
	double  Kg, Kf, Bg, Bf;
	double shtanga_d;
	
	GetUstanovka(this->p_database,
		id_ust, 
		ust_name,
		typ_zond,
		n_shema,
		Kg,Kf,Bg,Bf, 
		shtanga_d);

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->PtStZond(
				id_kt, id_ust, glyb, 
				ust_name,
				typ_zond,
				n_shema,
				Kg, Kf, Bg, Bf,
				shtanga_d);
		}
	}
}