// DBTableKT.cpp: implementation of the DBTableKT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableKT.h"
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

DBTableKT::DBTableKT(const char * tbnm) : DBTable (tbnm)
{
	m_wdli_podoshva_lito = NULL;
	m_wdli_podoshva_ige = NULL;
	m_wdli_hydro = NULL;

}

DBTableKT::~DBTableKT()
{

}
void DBTableKT::EnumCallBack(CRecordset * pRecordset)
{
	CString dtbur;
	long id_obj, id_kt;
	long id_bur, d_bur;
	int iActualItem = 0;
	double X,Y,Z;
	CString nazva;
	long kt_idtyp;
	for (int iSubItem = 0; iSubItem < 10; iSubItem++) 
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
				//NAZVA
				nazva = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 3:
			{
				//X
				X = var.m_dblVal;
			}
			break;
		case 4:
			{
				//Y
				Y = var.m_dblVal;
			}
			break;
		case 5:
			{
				//Z
				Z = var.m_dblVal;
			}
			break;
		case 6:
			{
				//ID_TYP
				kt_idtyp = var.m_lVal;
			}
			break;		
		case 7:
			{
				//ID_BUR
				id_bur = var.m_lVal;
			}
			break;
		case 8:
			{
				//D_BUR
				if (var.m_dwType == DBVT_LONG)
					d_bur = var.m_lVal;
				else
					d_bur = 0;
			}
			break;
		case 9:
			{
				//DTBUR
				dtbur = CMyListCtrl::GetFieldString(var);
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->AddWell(id_kt, nazva, kt_idtyp, X, Y, Z, Z, id_bur, d_bur, dtbur.GetBuffer(dtbur.GetLength()),
					this->m_wdli_podoshva_lito,
					this->m_wdli_podoshva_ige,
					this->m_wdli_hydro);
		}
	}
}
