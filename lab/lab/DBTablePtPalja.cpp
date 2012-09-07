// DBTablePtPalja.cpp: implementation of the DBTablePtPalja class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTablePtPalja.h"
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

DBTablePtPalja::DBTablePtPalja(const char * tbnm) : DBTable (tbnm)
{

}

DBTablePtPalja::~DBTablePtPalja()
{

}
void DBTablePtPalja::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt, id_typ;
	double pereriz_x, pereriz_y, A, u, glyb, RsA, fhu, pz;
	long id_snip;
	double Fu;

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
				//ID_KT
				id_kt = var.m_lVal;
			}
			break;
		case 2:
			{
				//ID_TYP
				id_typ = var.m_lVal;
			}
			break;
		case 3:
			{
				//Pereriz_X
				pereriz_x = var.m_dblVal;
			}
			break;
		case 4:
			{
				//Pereriz_Y
				pereriz_y = var.m_dblVal;
			}
			break;
		case 5:
			{
				//A
				A = var.m_dblVal;
			}
			break;
		case 6:
			{
				//u
				u = var.m_dblVal;
			}
			break;

		case 7:
			{
				//GLYB
				glyb = var.m_dblVal;
			}
			break;

		case 8:
			{
				//RsA
				RsA = var.m_dblVal;
			}
			break;
		case 9:
			{
				//fhu
				fhu = var.m_dblVal;
			}
			break;
		case 10:
			{
				//PZ
				pz = var.m_dblVal;
			}
			break;
		case 11:
			{
				//ID_SNIP
				id_snip = var.m_lVal;
			}
			break;
		case 12:
			{
				//Fu
				Fu = var.m_dblVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->PtPalja(
				id_kt, id_typ,
				pereriz_x, pereriz_y, A, u, glyb, RsA, fhu, pz, id_snip, Fu);
		}
	}
}

