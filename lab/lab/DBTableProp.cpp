// DBTableProp.cpp: implementation of the DBTableProp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableProp.h"
#include "LabDoc.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableProp::DBTableProp(const char * tbnm) : DBTable (tbnm)
{

}

DBTableProp::~DBTableProp()
{

}
CString GetFizMehParamName(CDatabase * database, long id_param)
{
	CString str;
	CString strQuery;
	strQuery.Format("select * from [FizMehAllParam]");	

	CString where;
	where.Format("ID_PARAM = %ld", id_param);

	CRecordset * _pRecordset = new CRecordset(database);

	try {
		_pRecordset->m_strFilter = where;
		_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly);
	}
	catch (CDBException* pe) {
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		_pRecordset->Close();
		delete _pRecordset;
		str = "";
		return str;
	}

	if (!_pRecordset->IsBOF())
	{
		_pRecordset->MoveFirst();
		
		CDBVariant _var; // must declare this inside the loop
		_pRecordset->GetFieldValue("NAZVA_R", _var);

		str = CMyListCtrl::GetFieldString(_var);
	}
	

	_pRecordset->Close();

	delete _pRecordset;

	return str;
}


void DBTableProp::EnumCallBack(CRecordset * pRecordset)
{

	long id_obj, id_kt, id_prob, id_vyprob, id_param;
	double val;
	unsigned char bStat;

	for (int iSubItem = 0; iSubItem < 7; iSubItem++) 
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
				//ID_PARAM
				id_param = var.m_lVal;
			}
			break;
		case 5:
			{
				//VAL
				val = var.m_dblVal;
			}
			break;
		case 6:
			{
				// bSTAT
				bStat = var.m_chVal;
			}
			break;	
		}
	}
			
	CString param_name = GetFizMehParamName(this->p_database, id_param);

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->AddProp(
				id_kt,
				id_prob, id_vyprob,
				id_param, param_name, val, bStat);
		}
	}
}
