// DBTableStZond.cpp: implementation of the DBTableStZond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "LabDoc.h"
#include "DBTableStZond.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableStZond::DBTableStZond(const char * tbnm) : DBTable (tbnm)
{

}

DBTableStZond::~DBTableStZond()
{

}
void DBTableStZond::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, npp, typgr;
	double h, q0, f0, dh, fsr;
	unsigned char bStat;
	long id_ige;
	double pck;

	for (int iSubItem = 0; iSubItem < 12; iSubItem++) 
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
				//NPP
				npp = var.m_lVal;
			}
			break;
		case 3:
			{
				//TYPGR
				typgr = var.m_lVal;
			}
			break;
		case 4:
			{
				//H
				h = var.m_dblVal;
			}
			break;
		case 5:
			{
				//q0
				q0 = var.m_dblVal;
			}
			break;
		case 6:
			{
				//f0
				f0 = var.m_dblVal;
			}
			break;
		case 7:
			{
				//dH
				dh = var.m_dblVal;
			}
			break;
		case 8:
			{
				//fsr
				fsr = var.m_dblVal;
			}
			break;
		case 9:
			{
				// bSTAT
				bStat = var.m_chVal;
			}
			break;	
		case 10:
			{
				// ID_IGE
				id_ige = var.m_lVal;
			}
			break;	
		case 11:
			{
				// pck
				pck = var.m_dblVal;
			}
			break;	
		}
	}
			

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->StZond(
				id_kt, npp, typgr,
				h, q0, f0, 
				dh, fsr, bStat,
				id_ige, pck);
		}
	}
}