// DBTablePCK2Fiz_Results.cpp: implementation of the DBTablePCK2Fiz_Results class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTablePCK2Fiz_Results.h"
#include "LabDoc.h"
#include "myListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTablePCK2Fiz_Results::DBTablePCK2Fiz_Results(const char * tbnm) : DBTable (tbnm)
{

}

DBTablePCK2Fiz_Results::~DBTablePCK2Fiz_Results()
{

}

void DBTablePCK2Fiz_Results::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt, npp, id_calc_param;
	double param;

	for (int iSubItem = 0; iSubItem < 5; iSubItem++) 
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
				//NPP
				npp = var.m_lVal;
			}
			break;
		case 3:
			{
				//id_calc_param
				id_calc_param = var.m_lVal;
			}
			break;
		case 4:
			{
				//PARAM
				param = var.m_dblVal;
			}
			break;
		
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->PCK2FizResults(id_kt, npp, id_calc_param, param);
		}
	}
}
