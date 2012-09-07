// DBTableSoils.cpp: implementation of the DBTableSoils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableSoils.h"
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

DBTableSoils::DBTableSoils(const char * tbnm) : DBTable (tbnm)
{

}

DBTableSoils::~DBTableSoils()
{

}
long GetKTIDType(CDatabase * database, long id_obj, long id_kt);
CString GetGruntName(CDatabase * database, long id_obj, long id_gr);
CString GetKTName(CDatabase * database, long id_obj, long id_kt);
void DBTableSoils::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, id_prob, lab_n, id_kodprob, id_gr, id_ige;
	int iActualItem = 0;
	double H;
	CString grunt_name;

	for (int iSubItem = 0; iSubItem < 9; iSubItem++) 
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
				//H
				H = var.m_dblVal;
			}
			break;
		case 4:
			{
				//LAB_N
				lab_n = var.m_lVal;
			}
			break;
		case 5:
			{
				//ID_KODPROB
				id_kodprob = var.m_lVal;
			}
			break;
		case 6:
			{
				// GRUNT_NAME
				grunt_name = CMyListCtrl::GetFieldString(var);
			}
			break;	
		case 7:
			{
				// ID_GR
				id_gr = var.m_lVal;
			}
			break;	
		case 8:
			{
				// ID_IGE
				id_ige = var.m_lVal;
			}
			break;	
		}
	}
	CString kt_name = GetKTName(this->p_database, id_obj, id_kt);
	long kt_idtyp = GetKTIDType(this->p_database, id_obj, id_kt);
	CString soil_name = GetGruntName(this->p_database, id_obj, id_gr);

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->AddPrGrunt(id_obj,
				id_kt, kt_name, kt_idtyp,
				id_prob, H,
				lab_n, id_kodprob, id_gr, soil_name, grunt_name,
				id_ige);
		}
	}
}

