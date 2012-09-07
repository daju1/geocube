// DBTableZriz.cpp: implementation of the DBTableZriz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableZriz.h"
#include "LabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableZriz::DBTableZriz(const char * tbnm) : DBTable (tbnm)
{

}

DBTableZriz::~DBTableZriz()
{

}


void DBTableZriz::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, id_prob, id_vyprob;
	long id_hid, id_shema, id_stan;
	double tgfi, c;
	double d, h;
	unsigned char bStat;

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
				//ID_PROB
				id_prob = var.m_lVal;
			}
			break;
		case 3:
			{
				//ID_VYPROB
				id_vyprob = var.m_lVal;
			}
			break;
		case 4:
			{
				//DTVYPROB
			}
			break;
		case 5:
			{
				//ID_HID
				id_hid = var.m_lVal;
			}
			break;
		case 6:
			{
				//ID_SHEMA
				id_shema = var.m_lVal;
			}
			break;
		case 7:
			{
				//ID_STAN
				id_stan = var.m_lVal;
			}
			break;
		case 8:
			{
				//tgFi
				tgfi = var.m_dblVal;
			}
			break;
		case 9:
			{
				//C
				c = var.m_dblVal;
			}
			break;
		case 10:
			{
				//D
				d = var.m_dblVal;
			}
			break;
		case 11:
			{
				//H
				h = var.m_dblVal;
			}
			break;
		case 12:
			{
				// bSTAT
				bStat = var.m_chVal;
			}
			break;	
		}
	}
			

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Zriz(
				id_kt,
				id_prob, id_vyprob,
				id_hid, id_shema, id_stan, tgfi, c, d, h, bStat);
		}
	}
}