// DBTableCompress.cpp: implementation of the DBTableCompress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableCompress.h"
#include "LabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableCompress::DBTableCompress(const char * tbnm) : DBTable (tbnm)
{

}

DBTableCompress::~DBTableCompress()
{

}

void DBTableCompress::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, id_prob, id_vyprob;
	double sigma, dh1, dh2;
	unsigned char voda, bStat;

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
				//ID_VYPROB
				id_vyprob = var.m_lVal;
			}
			break;
		case 4:
			{
				//SIGMA
				sigma = var.m_dblVal;
			}
			break;
		case 5:
			{
				//DH1
				dh1 = var.m_dblVal;
			}
			break;
		case 6:
			{
				//DH2
				dh2 = var.m_dblVal;
			}
			break;
		case 7:
			{
				//VODA
				voda = var.m_chVal;
			}
			break;
		case 8:
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
			this->lab_doc->dll_w_project->Compress(
				id_kt, id_prob, id_vyprob,
				sigma, dh1*10, dh2*10, voda, bStat);

			/*this->lab_doc->dll_w_project->
			Compress(
				id_kt, id_prob, id_vyprob,
				long(0), long(0), long(0), 2.47*10, 8.74*10, bStat);*/
		}
	}
}