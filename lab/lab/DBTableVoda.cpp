// DBTableVoda.cpp: implementation of the DBTableVoda class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableVoda.h"
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

DBTableVoda::DBTableVoda(const char * tbnm) : DBTable (tbnm)
{

}

DBTableVoda::~DBTableVoda()
{

}
void DBTableVoda::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt, horizont;
	double hv_z, hv_v;
	SYSTEMTIME dv;

	for (int iSubItem = 0; iSubItem < 6; iSubItem++) 
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
				//HORIZONT
				horizont = var.m_lVal;
			}
			break;
		case 3:
			{
				//HV_Z
				hv_z = var.m_dblVal;
			}
			break;
		case 4:
			{
				//HV_V
				hv_v = var.m_dblVal;
			}
			break;
		case 5:
			{
				//DV
				if (var.m_pdate)
				{
					dv.wYear = var.m_pdate->year; 
					dv.wMonth = var.m_pdate->month; 
					dv.wDay = var.m_pdate->day; 
					dv.wHour = var.m_pdate->hour; 
					dv.wMinute = var.m_pdate->minute;
					dv.wSecond = var.m_pdate->second;
				}
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Voda(id_kt, horizont, hv_z, hv_v, dv);
		}
	}
}

