// DBTableCubeSize.cpp: implementation of the DBTableCubeSize class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "DBTableCubeSize.h"
#include "LabDoc.h"
#include "myListCtrl.h"
#include "../../surfdoc/src/Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBTableCubeSize::DBTableCubeSize(const char * tbnm) : DBTable (tbnm)
{

}

DBTableCubeSize::~DBTableCubeSize()
{

}
void DBTableCubeSize::EnumCallBack(CRecordset * pRecordset)
{
	long id_obj;
	CubeSize cube_size;

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
				//nPag
				cube_size.nPag = var.m_lVal;
			}
			break;
		case 2:
			{
				//nRow
				cube_size.nRow = var.m_lVal;
			}
			break;
		case 3:
			{
				//nCol
				cube_size.nCol = var.m_lVal;
			}
			break;
		case 4:
			{
				//xLL
				cube_size.xLL = var.m_dblVal;
			}
			break;
		case 5:
			{
				//yLL
				cube_size.yLL = var.m_dblVal;
			}
			break;
		case 6:
			{
				//zLL
				cube_size.zLL = var.m_dblVal;
			}
			break;
		case 7:
			{
				//xSize
				cube_size.xSize = var.m_dblVal;
			}
			break;
		case 8:
			{
				//ySize
				cube_size.ySize = var.m_dblVal;
			}
			break;
		case 9:
			{
				//zSize
				cube_size.zSize = var.m_dblVal;
			}
			break;
		}
	}

	if (this->lab_doc)
	{
		if (this->lab_doc->dll_w_project)
		{
			this->lab_doc->dll_w_project->DefineCubeSize(cube_size);
		}
	}
}

