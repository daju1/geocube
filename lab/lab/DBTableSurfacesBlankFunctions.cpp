// DBTableSurfacesBlankFunctions.cpp: implementation of the DBTableSurfacesBlankFunctions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableSurfacesBlankFunctions.h"
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

DBTableSurfacesBlankFunctions::DBTableSurfacesBlankFunctions(const char * tbnm) : DBTable (tbnm)
{

}

DBTableSurfacesBlankFunctions::~DBTableSurfacesBlankFunctions()
{

}
void DBTableSurfacesBlankFunctions::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, 
		//id_item, 
		id_surf_obj, id_surf_param;
	BYTE id_blank_fun;

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
		//case 1:
		//	{
		//		//ID_OBJ
		//		id_item = var.m_lVal;
		//	}
		//	break;
		case 1:
			{
				//ID_SURF_OBJ
				id_surf_obj = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_SURF_PARAM
				id_surf_param = var.m_lVal;
			}
			break;
		case 3:
			{
				//ID_BLANK_FUN
				id_blank_fun = var.m_chVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->SurfacesBlankFuntions(//id_item, 
				id_surf_obj, id_surf_param, id_blank_fun);
		}
	}
}

