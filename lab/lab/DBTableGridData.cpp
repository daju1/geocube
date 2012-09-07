// DBTableGridData.cpp: implementation of the DBTableGridData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableGridData.h"
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

DBTableGridData::DBTableGridData(const char * tbnm) : DBTable (tbnm)
{

}

DBTableGridData::~DBTableGridData()
{

}
void DBTableGridData::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_surf, id_point;
	double x, y, z;

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
				//ID_SURF
				id_surf = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_POINT
				id_point = var.m_lVal;
			}
			break;
		case 3:
			{
				//X
				x = var.m_dblVal;
			}
			break;
		case 4:
			{
				//Y
				y = var.m_dblVal;
			}
			break;
		case 5:
			{
				//Z
				z = var.m_dblVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->GridData(id_surf, id_point, x, y, z);
		}
	}
}

