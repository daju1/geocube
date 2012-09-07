// DBTableGrunty.cpp: implementation of the DBTableGrunty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableGrunty.h"
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

DBTableGrunty::DBTableGrunty(const char * tbnm) : DBTable (tbnm)
{

}

DBTableGrunty::~DBTableGrunty()
{

}
void DBTableGrunty::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_gr;
	CString nazva_u, nazva_r;
	long typgr, typgr_pck, id_normatyv, id_grcons, id_uklad, id_nju, id_grmain, id_umpoz, id_genezis;

	for (int iSubItem = 0; iSubItem < 13; iSubItem++) 
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
				//ID_GR
				id_gr = var.m_lVal;
			}
			break;
		case 2:
			{
				//NAZVA_U
				nazva_u = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 3:
			{
				//NAZVA_R
				nazva_r = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 4:
			{
				//TYPGR
				typgr = var.m_lVal;
			}
			break;
		case 5:
			{
				//TYPGR_PCK
				typgr_pck = var.m_lVal;
			}
			break;
		case 6:
			{
				//ID_NORMATYV
				id_normatyv = var.m_lVal;
			}
			break;
		case 7:
			{
				//ID_GRCONS
				id_grcons = var.m_lVal;
			}
			break;
		case 8:
			{
				//ID_UKLAD
				id_uklad = var.m_lVal;
			}
			break;
		case 9:
			{
				//ID_NJU
				id_nju = var.m_lVal;
			}
			break;
		case 10:
			{
				//ID_GRMAIM
				id_grmain = var.m_lVal;
			}
			break;
		case 11:
			{
				//ID_UMPOZ
				id_umpoz = var.m_lVal;
			}
			break;
		case 12:
			{
				//ID_GENEZIS
				id_genezis = var.m_lVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Grunty(
				id_gr,
				nazva_u, nazva_r,
				typgr, typgr_pck, id_normatyv, id_grcons, id_uklad, id_nju, id_grmain, id_umpoz, id_genezis);
		}
	}
}

