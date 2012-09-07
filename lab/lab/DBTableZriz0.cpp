// DBTableZriz.cpp: implementation of the DBTableZriz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableZriz0.h"
#include "LabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableZriz0::DBTableZriz0(const char * tbnm) : DBTable (tbnm)
{

}

DBTableZriz0::~DBTableZriz0()
{

}


void DBTableZriz0::EnumCallBack(CRecordset * pRecordset)
{			
	long id_obj, id_kt, id_prob, id_vyprob, id_kolca, id_phys_vyprob;
	double h, d;
	double dh_po_upl,
		m_kolca,
		m_grunta,
		m_grunta_zamoch,
		m_grunta_posle_uplot,
		m_grunta_posle,
		m_grunta_vysush;

	for (int iSubItem = 0; iSubItem < 15; iSubItem++) 
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
				//ID_PHYS_VYPROB
				id_phys_vyprob = var.m_lVal;
			}
			break;
		case 6:
			{
				//H
				h = var.m_dblVal;
			}
			break;
		case 7:
			{
				//D
				d = var.m_dblVal;
			}
			break;
		case 8:
			{
				//DH_PO_UPL
				dh_po_upl = var.m_dblVal;
			}
			break;
		case 9:
			{
				//M_KOLCA
				m_kolca = var.m_dblVal;
			}
			break;
		case 10:
			{
				//M_GRUNTA
				m_grunta = var.m_dblVal;
			}
			break;
		case 11:
			{
				//M_GRUNTA_ZAMOCH
				m_grunta_zamoch = var.m_dblVal;
			}
			break;
		case 12:
			{
				//M_GRUNTA_POSLE_UPLOT
				m_grunta_posle_uplot = var.m_dblVal;
			}
			break;
		case 13:
			{
				//M_GRUNTA_POSLE
				m_grunta_posle = var.m_dblVal;
			}
			break;
		case 14:
			{
				//M_GRUNTA_VYSUSH
				m_grunta_vysush = var.m_dblVal;
			}
			break;
		}
	}
	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Zriz0(
				id_kt, id_prob, id_vyprob, id_kolca, id_phys_vyprob,
				10.0*h, 10.0*d, dh_po_upl,
				m_kolca,
				m_grunta,
				m_grunta_zamoch,
				m_grunta_posle_uplot,
				m_grunta_posle,
				m_grunta_vysush);
		}
	}
}