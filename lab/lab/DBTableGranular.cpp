// DBTableGranular.cpp: implementation of the DBTableGranular class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableGranular.h"
#include "LabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableGranular::DBTableGranular(const char * tbnm) : DBTable (tbnm)
{

}

DBTableGranular::~DBTableGranular()
{

}

CString GetGranularFraction(CDatabase * database, long id_gran);

void DBTableGranular::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt, id_prob, id_gran;
	int iActualItem = 0;
	double val;

	for (int iSubItem = 0; iSubItem < 5; iSubItem++) 
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
				//ID_GRAN
				id_gran = var.m_lVal;
			}
			break;
		case 4:
			{
				//VAL
				val = var.m_dblVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->AddGranular(
				id_kt, id_prob, id_gran, GetGranularFraction(p_database, id_gran), val);
		}
	}
}



