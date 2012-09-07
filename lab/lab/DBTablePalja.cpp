// DBTablePalja.cpp: implementation of the DBTablePalja class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTablePalja.h"
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

DBTablePalja::DBTablePalja(const char * tbnm) : DBTable (tbnm)
{

}

DBTablePalja::~DBTablePalja()
{

}
void DBTablePalja::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj, id_kt;
	double h, 
		qc, beta1, Rs, fs, beta2, f,
		RsA, fhu, Fu;

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
				//H
				h = var.m_dblVal;
			}
			break;
		case 3:
			{
				//qc
				qc = var.m_dblVal;
			}
			break;		
		case 4:
			{
				//beta1
				beta1 = var.m_dblVal;
			}
			break;		
		case 5:
			{
				//Rs
				Rs = var.m_dblVal;
			}
			break;		
		case 6:
			{
				//fs
				fs = var.m_dblVal;
			}
			break;		
		case 7:
			{
				//beta2
				beta2 = var.m_dblVal;
			}
			break;		
		case 8:
			{
				//f
				f = var.m_dblVal;
			}
			break;		
		case 9:
			{
				//RsA
				RsA = var.m_dblVal;
			}
			break;
		case 10:
			{
				//fhu
				fhu = var.m_dblVal;
			}
			break;
		case 11:
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
			this->lab_doc->dll_w_project->Palja(
				id_kt,
				h, qc, beta1, Rs, fs, beta2, f, RsA, fhu, Fu);
		}
	}
}

