// DBTableGenezis.cpp: implementation of the DBTableGenezis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableGenezis.h"
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

DBTableGenezis::DBTableGenezis(const char * tbnm) : DBTable (tbnm)
{

}

DBTableGenezis::~DBTableGenezis()
{

}
void DBTableGenezis::EnumCallBack(CRecordset * pRecordset)
{
	long id_genezis;
	CString nazva_u, nazva_r;
	long id_normatyv, id_grmain;
	CString index;
	BYTE r,g,b;
	for (int iSubItem = 0; iSubItem < 9; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem, var);
			
		switch (iSubItem)
		{
		case 0:
			{
				//ID_GENEZIS
				id_genezis = var.m_lVal;
			}
			break;
		case 1:
			{
				//NAZVA_U
				nazva_u = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 2:
			{
				//NAZVA_R
				nazva_r = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 3:
			{
				//ID_NORMATYV
				id_normatyv = var.m_lVal;
			}
			break;
		case 4:
			{
				//ID_GRMAIN
				id_grmain = var.m_lVal;
			}
			break;
		case 5:
			{
				//INDEX
				index = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 6:
			{
				//R
				r = var.m_chVal;
			}
			break;
		case 7:
			{
				//G
				g = var.m_chVal;
			}
			break;
		case 8:
			{
				//B
				b = var.m_chVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Genezis(id_genezis,
				nazva_u, nazva_r,
				id_normatyv, id_grmain,
				index,
				r, g, b);
		}
	}
}

