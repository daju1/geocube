// DBTableSurfLitoMapping.cpp: implementation of the DBTableSurfLitoMapping class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableSurfLitoMapping.h"
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

DBTableSurfLitoMapping::DBTableSurfLitoMapping(const char * tbnm) : DBTable (tbnm)
{

}

DBTableSurfLitoMapping::~DBTableSurfLitoMapping()
{

}
void DBTableSurfLitoMapping::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_surf, id_ige;

	for (int iSubItem = 0; iSubItem < 3; iSubItem++) 
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
				//ID_SURF
				id_surf = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_IGE
				id_ige = var.m_lVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->SurfLitoMapping(id_surf, id_ige);
		}
	}
}

