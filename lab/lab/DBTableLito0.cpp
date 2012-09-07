// DBTableLito.cpp: implementation of the DBTableLito class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableLito0.h"
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

DBTableLito0::DBTableLito0(const char * tbnm) : DBTable (tbnm)
{

}

DBTableLito0::~DBTableLito0()
{

}

void DBTableLito0::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt, id_ige;
	double h0, h1;

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
				//ID_KT
				id_kt = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_IGE
				id_ige = var.m_lVal;
			}
			break;
		case 3:
			{
				//H0
				h0 = var.m_dblVal;
			}
			break;
		case 4:
			{
				//H1
				h1 = var.m_dblVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Lito0(id_kt, id_ige, h0, h1);
		}
	}
}
