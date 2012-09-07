// DBTableGridDataUsedAlg.cpp: implementation of the DBTableGridDataUsedAlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableGridDataUsedAlg.h"
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

DBTableGridDataUsedAlg::DBTableGridDataUsedAlg(const char * tbnm) : DBTable (tbnm)
{

}

DBTableGridDataUsedAlg::~DBTableGridDataUsedAlg()
{

}
void DBTableGridDataUsedAlg::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_surf, id_alg;
	//BYTE use_surfer;
	BYTE griddata_app;

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
		case 1:
			{
				//ID_SURF
				id_surf = var.m_lVal;
			}
			break;
		case 2:
			{
				//use_surfer
				//griddata_app
				griddata_app = var.m_chVal;
			}
			break;
		case 3:
			{
				//id_alg
				id_alg = var.m_lVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->GridDataUsedAlg(id_surf, griddata_app, id_alg);
		}
	}
}

