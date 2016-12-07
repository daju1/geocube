// BaseExcel.cpp: implementation of the BaseExcel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "BaseExcel.h"
#include "LabView.h"
#include "SetObject.h"
#include "../../tools/src/filedlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
string BaseExcel::s_xl_forms_dir = CLabDoc::GetWorkDir() + "\\LabForms";
bool BaseExcel::to_disconnect_exels_when_load_form = true;
bool BaseExcel::to_automatic_save_when_disconnect = true;

BaseExcel::BaseExcel()
{
	xl_forms_dir		= BaseExcel::s_xl_forms_dir;
	m_lab_view = NULL;
	m_lab_doc = NULL;
	p_database = NULL;

	use_compute_for_save = false;
	can_save_to_db = false;
	save_different_vyprob = false;
}

BaseExcel::~BaseExcel()
{

}

void BaseExcel::Init(CLabView * view, CLabDoc * doc, CDatabase * database)
{
	this->m_lab_view = view;
	this->m_lab_doc = doc;
	this->p_database = database;
}
bool file_exists(LPCTSTR strFileName)
{
	DWORD dwAttr = GetFileAttributes(strFileName);
	return (dwAttr != 0xFFFFFFFF) && (0 == (dwAttr & FILE_ATTRIBUTE_DIRECTORY));
}
CString BaseExcel::LoadFormNew(const char * initial_fn) 
{
	if (BaseExcel::to_disconnect_exels_when_load_form)
	{
		if (this->m_lab_view)
		{
			this->m_lab_view->DisconnectAllExcels();
		}
	}

	was_new_form_loaded = true;

	this->InitExt();

	can_save_to_db = false;

	TCHAR filter[4098];
	sprintf_s(filter, 4098, TEXT("%s Excel files (*.%s.xls)%%*.%s.xls%%All Files (*.*)%%*.*%%\0"),
		xl_filter_name.c_str(),	ext.c_str(), ext.c_str());

	// Replace occurrences of '%' string separator 
	// with '\0'. 

	for (int i=0; filter[i]!='\0'; i++) 
	{
		if (filter[i] == '%') 
				filter[i] = '\0'; 
	}

	char dir[4098];		
	char path_xls[4098];		
	char fn[4098];		
	sprintf(path_xls, "%s\0", initial_fn);

	char * p = NULL;

	DWORD nFilterIndex = 0;
	if (S_OK == SaveFileDlg(NULL, path_xls, filter, nFilterIndex))
	{
		switch (nFilterIndex)
		{
		case 1:
			break;
		}	

		strcpy(dir, path_xls);

		p = NULL;
		if (p = strrchr(dir, '/'))
			*p = '\0';
		else if (p = strrchr(dir, '\\'))
			*p = '\0';

		if (p)
		{
			strcpy(fn, p+1);
			if (p = strchr(fn, '.'))
				*p = '\0';
		}

		char file1[4098];
		sprintf(file1, "%s\\%s.xls", xl_forms_dir.c_str(), xl_form.c_str());
		char file2[4098];
		sprintf(file2, "%s\\%s.%s.xls", dir, fn, ext.c_str());

		if (file_exists(file2))
		{
			char str[4098];
			sprintf(str, "Файл %s уже существует\nВы уверены, что хотите перезаписать этот файл?", file2);
			if (IDNO == AfxMessageBox(str, MB_YESNO, 0))
				return "";
		}

		if (!CopyFile(file1, file2, FALSE))
		{
			char str[4098];
			sprintf(str, "Can not copy\n%s\nto\n%s", file1, file2);
			AfxMessageBox(str);
			return "";
		}
		/*else
		{
			char str[4098];
			sprintf(str, "Copied\n%s\nto\n%s", file1, file2);
			AfxMessageBox(str);
		}*/

		m_excel.ExcelOleLoad();
		if (m_excel.IsApplicationDispatch())
		{
			//try
			{
				m_excel.ExcelOleExecute(file2);
				this->xl_file = file2;  
				if (this->m_lab_view) this->m_lab_view->EnableObjectList(false);

				//m_excel.m_workbook.Save();
			}
			/*
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();
			}

			*/
			//m_excel.ExcelOleRelease();
		}
		else
			printf("!!!!! m_excel.IsApplicationDispatch()\n");
		return file2;
	}	
	return "";
}

CString BaseExcel::LoadFormNew(const char * dir, const char * fn) 
{
	if (BaseExcel::to_disconnect_exels_when_load_form)
	{
		if (this->m_lab_view)
		{
			this->m_lab_view->DisconnectAllExcels();
		}
	}

	was_new_form_loaded = true;

	this->InitExt();

	can_save_to_db = false;


		char file1[4098];
		sprintf(file1, "%s\\%s.xls", xl_forms_dir.c_str(), xl_form.c_str());
		char file2[4098];
		sprintf(file2, "%s\\%s.%s.xls", dir, fn, ext.c_str());

		if (file_exists(file2))
		{
			char str[4098];
			sprintf(str, "Файл %s уже существует\nВы уверены, что хотите перезаписать этот файл?", file2);
			if (IDNO == AfxMessageBox(str, MB_YESNO, 0))
				return "";
		}

		if (!CopyFile(file1, file2, FALSE))
		{
			char str[4098];
			sprintf(str, "Can not copy\n%s\nto\n%s", file1, file2);
			AfxMessageBox(str);
			return "";
		}
		/*else
		{
			char str[4098];
			sprintf(str, "Copied\n%s\nto\n%s", file1, file2);
			AfxMessageBox(str);
		}*/

		m_excel.ExcelOleLoad();
		if (m_excel.IsApplicationDispatch())
		{
			//try
			{
				m_excel.ExcelOleExecute(file2);
				this->xl_file = file2;  
				if (this->m_lab_view) this->m_lab_view->EnableObjectList(false);

				//m_excel.m_workbook.Save();
			}
			/*
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();
			}

			*/
			//m_excel.ExcelOleRelease();
		}
		else
			printf("!!!!! m_excel.IsApplicationDispatch()\n");

		return file2;
}

void BaseExcel::UpdateLoadFormNew(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(!this->m_excel.IsApplicationDispatch());
   
}

void BaseExcel::LoadFormExisting(const char * fn) 
{
	if (BaseExcel::to_disconnect_exels_when_load_form)
	{
		if (this->m_lab_view)
		{
			this->m_lab_view->DisconnectAllExcels();
		}
	}

	was_new_form_loaded = false;

	this->InitExt();

	can_save_to_db = false;

	char fn_xls[4098];		
	if (fn)
	{
		sprintf(fn_xls, "%s\0", fn);
	}
	else
	{
		sprintf(fn_xls, "\0");

		TCHAR filter[4098];
		sprintf_s(filter, 4098, TEXT("%s Excel files (*.%s.xls)%%*.%s.xls%%All Files (*.*)%%*.*%%\0"),
			xl_filter_name.c_str(),	ext.c_str(), ext.c_str());

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
	}
	m_excel.ExcelOleLoad();
	if (m_excel.IsApplicationDispatch())
	{
		try
		{
			m_excel.ExcelOleExecute(fn_xls);
			this->xl_file = fn_xls;  
			if (this->m_lab_view) this->m_lab_view->EnableObjectList(false);

			//m_excel.m_workbook.Save();
		}

		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

			printf("catched\n");
			m_excel.ExcelOleRelease();
		}
		//m_excel.ExcelOleRelease();
	}
	else
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
}

void BaseExcel::UpdateLoadFormExisting(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(!this->m_excel.IsApplicationDispatch());	
}
void BaseExcel::Fill() 
{
	can_save_to_db = false;

	if (m_excel.IsApplicationDispatch())
	{
		//try
		{
#if 0
			CString DecimalSeparator = m_excel.m_app.GetDecimalSeparator();
			m_excel.m_app.SetDecimalSeparator(",");

			BOOL UseSystemSeparators = m_excel.m_app.GetUseSystemSeparators();
			m_excel.m_app.SetUseSystemSeparators(TRUE);
#else
			CString DecimalSeparator = m_excel.m_app.GetDecimalSeparator();
			m_excel.m_app.SetDecimalSeparator(".");

			BOOL UseSystemSeparators = m_excel.m_app.GetUseSystemSeparators();
			m_excel.m_app.SetUseSystemSeparators(FALSE);
#endif
			can_save_to_db = this->virFill();
			//m_excel.m_workbook.Save();
			m_excel.m_app.SetDecimalSeparator(DecimalSeparator);
			m_excel.m_app.SetUseSystemSeparators(UseSystemSeparators);
		}
		/*
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

			m_excel.ExcelOleRelease();
		}
		
		*/
		//m_excel.ExcelOleRelease();
	}
	else
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
	
}

void BaseExcel::UpdateFill(CCmdUI* pCmdUI, bool may_fill_only_new_form) 
{
	if (may_fill_only_new_form)
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch() && this->was_new_form_loaded);	
	else
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
}


void BaseExcel::Compute() 
{
	can_save_to_db = false;

	if (m_excel.IsApplicationDispatch())
	{
		//try
		{
#if 0
			CString DecimalSeparator = m_excel.m_app.GetDecimalSeparator();
			m_excel.m_app.SetDecimalSeparator(",");

			BOOL UseSystemSeparators = m_excel.m_app.GetUseSystemSeparators();
			m_excel.m_app.SetUseSystemSeparators(TRUE);
#else
			CString DecimalSeparator = m_excel.m_app.GetDecimalSeparator();
			m_excel.m_app.SetDecimalSeparator(".");

			BOOL UseSystemSeparators = m_excel.m_app.GetUseSystemSeparators();
			m_excel.m_app.SetUseSystemSeparators(FALSE);
#endif
			can_save_to_db = this->virCompute(false);
			//m_excel.m_workbook.Save();
			m_excel.m_app.SetDecimalSeparator(DecimalSeparator);
			m_excel.m_app.SetUseSystemSeparators(UseSystemSeparators);
		}
		/*
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

			m_excel.ExcelOleRelease();
		}*/
		//m_excel.ExcelOleRelease();
	}
	else
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
	
}

void BaseExcel::UpdateCompute(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
}

void BaseExcel::SaveToDB() 
{
	int nItem = this->m_lab_view ? this->m_lab_view->GetObjectItem() : -1;
	if (nItem > -1)
	{
		try
		{
			long ID_OBJ = -1;

			SetObject setObject(p_database);
			if ( !setObject.Open(CRecordset::dynaset) )
				return;
			setObject.SetAbsolutePosition(nItem+1);

			ID_OBJ = setObject.m_ID_OBJ;

			char str[4098];
			sprintf(str, 
				"Вы действительно хотите произвести сохранение данных из формы\n"
				"%s\n"
				"в объект?\n"
				"ID_OBJ = %d\n"
				"CONTRACT = %s\n"
				"NAZVA = %s", 
				this->xl_file.c_str(),
				ID_OBJ, 
				setObject.m_CONTRACT, 
				setObject.m_NAZVA);
	        
			if (IDYES != MessageBox(0, str, "BaseExcel::SaveToDB()", MB_YESNO))
				return;

		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return;
		}
	}
	if (m_excel.IsApplicationDispatch())
	{
		//try
		{
			if (use_compute_for_save)
				this->virCompute(true);
			else
				this->virSaveToDB();
			
			can_save_to_db = false;
		}
		/*
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

			m_excel.ExcelOleRelease();
		}
		*/
		//m_excel.ExcelOleRelease();
	}
	else
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
	
}

void BaseExcel::UpdateSaveToDB(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(this->m_excel.IsApplicationDispatch() && can_save_to_db);	
}

void BaseExcel::DisconnectExcel() 
{
	can_save_to_db = false;
	if (m_excel.IsApplicationDispatch())
	{
		try
		{
			if (BaseExcel::to_automatic_save_when_disconnect )
				m_excel.m_workbook.Save();
			m_excel.m_workbook.Close();
			//m_excel.m_app.Quit();
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

		}
		m_excel.ExcelOleRelease();
	}
	else
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
}

void BaseExcel::UpdateDisconnectExcel(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
}

