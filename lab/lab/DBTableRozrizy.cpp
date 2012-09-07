// DBTableRozrizy.cpp: implementation of the DBTableRozrizy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableRozrizy.h"
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

DBTableRozrizy::DBTableRozrizy(const char * tbnm) : DBTable (tbnm)
{

}

DBTableRozrizy::~DBTableRozrizy()
{

}

void DBTableRozrizy::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_rozriz;
	CString nomer;
	BYTE has_dxf;
	CString fn_dxf;
	BYTE acad_yscale_loaded;
	double z1w, y1a, z2w, y2a;

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
				//ID_ROZRIZ
				id_rozriz = var.m_lVal;
			}
			break;
		case 2:
			{
				//NOMER
				nomer = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 3:
			{
				//has_dxf
				has_dxf = var.m_chVal;
			}
			break;
		case 4:
			{
				//fn_dxf
				fn_dxf = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 5:
			{
				//acad_yscale_loaded
				acad_yscale_loaded = var.m_chVal;
			}
			break;
		case 6:
			{
				//z1w
				z1w = var.m_dblVal;
			}
			break;
		case 7:
			{
				//y1a
				y1a = var.m_dblVal;
			}
			break;
		case 8:
			{
				//z2w
				z2w = var.m_dblVal;
			}
			break;
		case 9:
			{
				//y2a
				y2a = var.m_dblVal;
			}
			break;
		
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Rozrizy(id_rozriz, nomer, has_dxf, fn_dxf, acad_yscale_loaded,
				z1w, y1a, z2w, y2a);
		}
	}
}
