// DBTableUmPoz.cpp: implementation of the DBTableUmPoz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableUmPoz.h"
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

DBTableUmPoz::DBTableUmPoz(const char * tbnm) : DBTable (tbnm)
{

}

DBTableUmPoz::~DBTableUmPoz()
{

}
void DBTableUmPoz::EnumCallBack(CRecordset * pRecordset)
{
	long id_umpoz;
	CString umpoz, hatchacad;
	double angle, scale;
	for (int iSubItem = 0; iSubItem < 5; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem, var);

		switch (iSubItem)
		{
		case 0:
			{
				//ID_UMPOZ
				id_umpoz = var.m_lVal;
			}
			break;
		case 1:
			{
				//UMPOZ
				umpoz = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 2:
			{
				//HATCHACAD
				hatchacad = CMyListCtrl::GetFieldString(var);
			}
			break;
		case 3:
			{
				//Angle
				angle = var.m_dblVal;
			}
			break;
		case 4:
			{
				//Scale
				scale = var.m_dblVal;
			}
			break;

		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->UmPoz(id_umpoz,
				umpoz, hatchacad,
				angle, scale);	
		}
	}
}

