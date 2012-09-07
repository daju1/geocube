// DBTableGridDataSurfaces.cpp: implementation of the DBTableGridDataSurfaces class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableGridDataSurfaces.h"
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

DBTableGridDataSurfaces::DBTableGridDataSurfaces(const char * tbnm) : DBTable (tbnm)
{

}

DBTableGridDataSurfaces::~DBTableGridDataSurfaces()
{

}
void DBTableGridDataSurfaces::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_surf, id_umpoz, id_ige;
	CString nazva;
	BYTE podoshva;
	BYTE r,g,b;
	short z_flag;

	for (int iSubItem = 0; iSubItem < 10; iSubItem++) 
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
				//NAZVA
				nazva = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 3:
			{
				//podoshva
				podoshva = var.m_chVal;
			}
			break;
		case 4:
			{
				//r
				r = var.m_chVal;
			}
			break;
		case 5:
			{
				//g
				g = var.m_chVal;
			}
			break;
		case 6:
			{
				//b
				b = var.m_chVal;
			}
			break;
		case 7:
			{
				//z_flag
				z_flag = var.m_iVal;
			}
			break;
		case 8:
			{
				//ID_UMPOZ
				id_umpoz = var.m_lVal;
			}
			break;
		case 9:
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
			this->lab_doc->dll_w_project->GridDataSurfaces(id_surf, nazva, podoshva, r, g, b, z_flag, id_umpoz, id_ige);
		}
	}
}

