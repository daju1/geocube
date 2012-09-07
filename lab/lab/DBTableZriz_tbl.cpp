// DBTableZriz_tbl.cpp: implementation of the DBTableZriz_tbl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableZriz_tbl.h"
#include "LabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableZriz_tbl::DBTableZriz_tbl(const char * tbnm) : DBTable (tbnm)
{

}

DBTableZriz_tbl::~DBTableZriz_tbl()
{

}

void DBTableZriz_tbl::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, id_prob, id_vyprob, id_kolca;
	double sigma, tau, w_do, ro_do, w_po_upl, ro_po_upl, w_after, ro_after;
	unsigned char bStat;

	for (int iSubItem = 0; iSubItem < 14; iSubItem++) 
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
				//ID_KOLCA
				id_kolca = var.m_lVal;
			}
			break;
		case 5:
			{
				//SIGMA
				sigma = var.m_dblVal;
			}
			break;
		case 6:
			{
				//TAU
				tau = var.m_dblVal;
			}
			break;
		case 7:
			{
				//W_do
				w_do = var.m_dblVal;
			}
			break;
		case 8:
			{
				//Ro_do
				ro_do = var.m_dblVal;
			}
			break;
		case 9:
			{
				//W_po_upl
				w_po_upl = var.m_dblVal;
			}
			break;
		case 10:
			{
				//Ro_po_upl
				ro_po_upl = var.m_dblVal;
			}
			break;
		case 11:
			{
				//W_after
				w_after = var.m_dblVal;
			}
			break;
		case 12:
			{
				//Ro_after
				ro_after = var.m_dblVal;
			}
			break;
		case 13:
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
			this->lab_doc->dll_w_project->Zriz_tbl(
				id_kt,
				id_prob, id_vyprob, id_kolca,
				sigma, tau, w_do, ro_do, w_po_upl, ro_po_upl, w_after, ro_after, bStat);
		}
	}
}