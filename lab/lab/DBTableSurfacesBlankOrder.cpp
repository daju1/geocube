// DBTableSurfacesBlankOrder.cpp: implementation of the DBTableSurfacesBlankOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableSurfacesBlankOrder.h"
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

DBTableSurfacesBlankOrder::DBTableSurfacesBlankOrder(const char * tbnm) : DBTable (tbnm)
{

}

DBTableSurfacesBlankOrder::~DBTableSurfacesBlankOrder()
{

}
void DBTableSurfacesBlankOrder::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, npp, id_surf;
	BYTE podoshva;

	BYTE	check_blank_me;
	BYTE	check_blank_me_up;
	BYTE	check_blank_me_up_above;
	BYTE	check_blank_me_down;
	BYTE	check_blank_me_down_above;
	BYTE	check_blank_by_me_up;
	BYTE	check_blank_by_me_down;

	for (int iSubItem = 0; iSubItem < 11; iSubItem++) 
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
				//ID_SURF
				id_surf = var.m_lVal;
			}
			break;
		case 3:
			{
				//PODOSHVA
				podoshva = var.m_chVal;
			}
			break;
		case 4:
			{
				//check_blank_me
				check_blank_me = var.m_chVal;
			}
			break;
		case 5:
			{
				//check_blank_me_up
				check_blank_me_up = var.m_chVal;
			}
			break;
		case 6:
			{
				//check_blank_me_up_above
				check_blank_me_up_above = var.m_chVal;
			}
			break;
		case 7:
			{
				//check_blank_me_down
				check_blank_me_down = var.m_chVal;
			}
			break;
		case 8:
			{
				//check_blank_me_down_above
				check_blank_me_down_above = var.m_chVal;
			}
			break;
		case 9:
			{
				//check_blank_by_me_up
				check_blank_by_me_up = var.m_chVal;
			}
			break;
		case 10:
			{
				//check_blank_by_me_down
				check_blank_by_me_down = var.m_chVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->SurfacesBlankOrder(
				npp, id_surf, podoshva, 
				check_blank_me,
				check_blank_me_up,
				check_blank_me_up_above,
				check_blank_me_down, 
				check_blank_me_down_above,
				check_blank_by_me_up,
				check_blank_by_me_down);
		}
	}
}

