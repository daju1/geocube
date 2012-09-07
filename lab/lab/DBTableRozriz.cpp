// DBTableRozriz.cpp: implementation of the DBTableRozriz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableRozriz.h"
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

DBTableRozriz::DBTableRozriz(const char * tbnm) : DBTable (tbnm)
{

}

DBTableRozriz::~DBTableRozriz()
{

}

void DBTableRozriz::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_rozriz, npp, id_kt;
	double dxf_x;

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
				//ID_ROZRIZ
				id_rozriz = var.m_lVal;
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
				//ID_KT
				id_kt = var.m_lVal;
			}
			break;
		case 4:
			{
				//dxf_x
				dxf_x = var.m_dblVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Rozriz(id_rozriz, npp, id_kt, dxf_x);
		}
	}
}
