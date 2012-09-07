// DBTableIGE.cpp: implementation of the DBTableIGE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableIGE0.h"
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

DBTableIGE0::DBTableIGE0(const char * tbnm) : DBTable (tbnm)
{

}

DBTableIGE0::~DBTableIGE0()
{

}
void DBTableIGE0::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_ige, id_gr;
	CString ige;
	double mk, mkz;
	CString strat, desc0;

	for (int iSubItem = 0; iSubItem < 8; iSubItem++) 
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
				//ID_IGE
				id_ige = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_GR
				id_gr = var.m_lVal;
			}
			break;
		case 3:
			{
				//IGE
				ige = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 4:
			{
				//mk
				mk = var.m_dblVal;
			}
			break;
		case 5:
			{
				//mkz
				mkz = var.m_dblVal;
			}
			break;
		case 6:
			{
				//strat
				strat = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 7:
			{
				//desc0
				desc0 = CMyListCtrl::GetFieldString(var);
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->IGE0(
				id_ige, id_gr,
				ige,
				mk, mkz,
				strat, desc0
			);
		}
	}
}

