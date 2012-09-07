// DBTableSurfacesOrder.cpp: implementation of the DBTableSurfacesOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableSurfacesOrder.h"
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

DBTableSurfacesOrder::DBTableSurfacesOrder(const char * tbnm) : DBTable (tbnm)
{

}

DBTableSurfacesOrder::~DBTableSurfacesOrder()
{

}
void DBTableSurfacesOrder::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, npp, id_surf;
	BYTE podoshva, check, check2;

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
				//NPP
				npp = var.m_lVal;
			}
			break;
		case 2:
			{
				//check
				check = var.m_chVal;
			}
			break;
		case 3:
			{
				//ID_SURF
				id_surf = var.m_lVal;
			}
			break;
		case 4:
			{
				//PODOSHVA
				podoshva = var.m_chVal;
			}
			break;
		case 5:
			{
				//check2
				check2 = var.m_chVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->SurfacesOrder(npp, check, id_surf, podoshva, check2);
		}
	}
}

