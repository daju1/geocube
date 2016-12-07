// ExcelTSZList.cpp: implementation of the ExcelTSZList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelTSZList.h"

#include "SetObject.h"
#include "SetKT.h"

#include "labView.h"
#include "../../tools/src/filedlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelTSZList::ExcelTSZList()
{

}

ExcelTSZList::~ExcelTSZList()
{

}
void ExcelTSZList::InitExt()
{
	ext					= "tszl";
	xl_filter_name		= "Список соответствия КТ и TSZ";
	xl_form				= "TSZList";
}
void ExcelTSZList::SaveTSZList(long ID_OBJ, long ID_KT, CString dir, CString fn)
{
	CString filename = dir + "\\" + fn + "." + this->m_excel_stat_zond.ext.c_str() + ".xls";

	this->m_excel_stat_zond.LoadFormExisting(filename);
	this->m_excel_stat_zond.Save(ID_OBJ, ID_KT);
	this->m_excel_stat_zond.DisconnectExcel();
}

bool ExcelTSZList::virFill()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		int r = fr;
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			while(!setKT.IsEOF()) 
			{
				sprintf(S, "B%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_ID_KT));
				sprintf(S, "C%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));

				setKT.MoveNext();
				r++;
			}
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
		
	return true;
}

void ExcelTSZList::virSaveToDB()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return;
	}

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;	

		AfxMessageBox("Сейчас Вам нужно будет выбрать один из файлов статзондирования\nчтобы указать директорию в которой лежат все файлы из списка");

		this->m_excel_stat_zond.InitExt();

#if 0

		TCHAR filter[4098];
		sprintf_s(filter, 4098, TEXT(".%s.xls"),
			this->m_excel_stat_zond.ext.c_str());

		//CFileDialog dlg(TRUE, ".stz.xls", "*.stz.xls");
		CFileDialog dlg(TRUE, filter, filter);
		if (dlg.DoModal() == IDCANCEL) return;
		CString path = dlg.GetPathName();
#else
		char fn_xls[4098];		
		sprintf(fn_xls, "\0");

		TCHAR filter[4098];
		sprintf_s(filter, 4098, TEXT("%s Excel files (*.%s.xls)%%*.%s.xls%%All Files (*.*)%%*.*%%\0"),
			this->m_excel_stat_zond.xl_filter_name.c_str(),	
			this->m_excel_stat_zond.ext.c_str(), 
			this->m_excel_stat_zond.ext.c_str());

		// Replace occurrences of '%' string separator 
		// with '\0'. 

		for (int i=0; filter[i]!='\0'; i++) 
		{
			if (filter[i] == '%') 
					filter[i] = '\0'; 
		}	
		if (S_OK != OpenFileDlg(NULL, filter, fn_xls))
		{
			return;
		}
		CString path = fn_xls;
#endif
		int iflash = path.ReverseFind('\\');
		CString dir = path.Left(iflash);


		for (int r = fr; ;r++)
		{
			double val;
			long ID_KT = -1;
			sprintf(S, "B%d", r);				
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				ID_KT = long(val);
			}			
			else
			{
				break;
			}

			CString fn;
			sprintf(S, "D%d", r);				
			if (ExcelRange_GetStringValue(m_excel, S, fn))
			{
				SaveTSZList(ID_OBJ, ID_KT, dir, fn);
			}
		}

		CString where;
		//if (this->is_geo)
		//	where.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, id_kt);
			
		//if (this->is_lab)
			where.Format("ID_OBJ = %d", ID_OBJ);
		//this->m_lab_view->UpdateProbGruntListCtrl(where, "ID_KT, ID_PROB");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}