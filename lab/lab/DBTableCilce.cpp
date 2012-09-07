// DBTableCilce.cpp: implementation of the DBTableCilce class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "LabDoc.h"
#include "DBTableCilce.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableCilce::DBTableCilce(const char * tbnm) : DBTable (tbnm)
{

}

DBTableCilce::~DBTableCilce()
{

}
void DBTableCilce::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, id_prob, id_vyprob;
	double h, d, es_l1, es_r1, es_l2, es_r2;
	double nju, nju_z;
	double m01, E1, m02, E2;
	double m01v, E1v, m02v, E2v;
	unsigned char id_method, bStat, bStatV;

	for (int iSubItem = 0; iSubItem < 24; iSubItem++) 
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
				//H
				h = var.m_dblVal;
			}
			break;
		case 6:
			{
				//D
				d = var.m_dblVal;
			}
			break;

		case 7:
			{
				//ES_L1
				es_l1 = var.m_dblVal;
			}
			break;
		case 8:
			{
				//ES_R1
				es_r1 = var.m_dblVal;
			}
			break;

		case 9:
			{
				//ES_L2
				es_l2 = var.m_dblVal;
			}
			break;
		case 10:
			{
				//ES_R2
				es_r2 = var.m_dblVal;
			}
			break;

		case 11:
			{
				//nju
				nju = var.m_dblVal;
			}
			break;
		case 12:
			{
				//nju_z
				nju_z = var.m_dblVal;
			}
			break;

		case 13:
			{
				//m01
				m01 = var.m_dblVal;
			}
			break;
		case 14:
			{
				//E1
				E1 = var.m_dblVal;
			}
			break;

		case 15:
			{
				//m02
				m02 = var.m_dblVal;
			}
			break;
		case 16:
			{
				//E2
				E2 = var.m_dblVal;
			}
			break;

		case 17:
			{
				//m01v
				m01v = var.m_dblVal;
			}
			break;
		case 18:
			{
				//E1v
				E1v = var.m_dblVal;
			}
			break;

		case 19:
			{
				//m02v
				m02v = var.m_dblVal;
			}
			break;
		case 20:
			{
				//E2v
				E2v = var.m_dblVal;
			}
			break;

		case 21:
			{
				//ID_METHOD
				id_method = var.m_chVal;
			}
			break;
		case 22:
			{
				// bSTAT
				bStat = var.m_chVal;
			}
			break;	
		case 23:
			{
				// bStatV
				bStatV = var.m_chVal;
			}
			break;	
		}
	}
			

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->Compress(
				id_kt, id_prob, id_vyprob,
				h*10.0, d*10.0, 
				es_l1, es_r1, es_l2, es_r2,
				nju, nju_z,
				m01, E1, m02, E2,
				m01v, E1v, m02v, E2v,
				id_method, bStat, bStatV);
		}
	}
}
