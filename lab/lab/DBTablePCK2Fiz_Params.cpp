// DBTablePCK2Fiz_Params.cpp: implementation of the DBTablePCK2Fiz_Params class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTablePCK2Fiz_Params.h"
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

DBTablePCK2Fiz_Params::DBTablePCK2Fiz_Params(const char * tbnm) : DBTable (tbnm)
{

}

DBTablePCK2Fiz_Params::~DBTablePCK2Fiz_Params()
{

}

void DBTablePCK2Fiz_Params::EnumCallBack(CRecordset * pRecordset)
{
	long id_calc_param;
	CString calc_param, desc;

	for (int iSubItem = 0; iSubItem < 3; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem, var);
			

		switch (iSubItem)
		{
		case 0:
			{
				//id_calc_param
				id_calc_param = var.m_lVal;
			}
			break;
		case 1:
			{
				//calc_param
				calc_param = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 2:
			{
				//desc
				desc = CMyListCtrl::GetFieldString(var);
			}
			break;
		
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->PCK2Fiz_CalcParams(id_calc_param, calc_param, desc);
		}
	}
}
