// EnGeologyDoc.cpp: implementation of the CEnGeologyDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "EnGeologyDoc.h"
#include "EnGeologyView.h"
#include "tableset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CEnGeologyDoc, CDocument)

CEnGeologyDoc::CEnGeologyDoc()
{

}

CEnGeologyDoc::~CEnGeologyDoc()
{

}
bool CEnGeologyDoc::OpenOdbc(const char * connect_str, bool to_rewrite_list)
{
    // can't open ODBC via Access driver
    if (m_strConnect.IsEmpty()) {
		m_strConnect = connect_str;
    }
    BeginWaitCursor();
	BOOL bRet;
    try {
		// non-exclusive, read-only, no cursor library (dynaset)
        //bRet = m_database.Open("", FALSE, TRUE, m_strConnect, FALSE);
        bRet = m_database.Open("", FALSE, FALSE, m_strConnect, FALSE);
//		bRet = m_database.OpenEx(m_strConnect, CDatabase::openReadOnly);
	}
    catch (CDBException* pe) {
		AfxMessageBox(pe->m_strError);
		EndWaitCursor();
		pe->Delete();
		return false;
    }
	if(bRet) {
		m_strConnect = m_database.GetConnect();
		TRACE("connect = %s\n", m_strConnect);
		m_strDatabaseName = m_database.GetDatabaseName();
		m_bConnected = TRUE;

		EnumTables(to_rewrite_list);

		CEnGeologyView * geo_view = this->GetEnGeologyView();
		
		if (geo_view)
		{
			geo_view->m_EnGeoObjectsList.Fill_Ctrl_List(this->m_tables[table_key_Objects], "", "");
		}
		


	}
    EndWaitCursor();
	return true;
}
// helper used by OnFileOdbcConnect
void CEnGeologyDoc::EnumTables(bool to_rewrite_list)
{
	if (m_strQuery.IsEmpty()) {

		CEnGeologyView * lab_view = this->GetEnGeologyView();
		
		CTables tables(&m_database);  // db passed via constructor
		tables.Open();                // closed on table's
		//  destruction
		while (!tables.IsEOF()) {
			TRACE("table name = %s\n", tables.m_strName);
			
			// reject queries and system tables
			if (_stricmp(tables.m_strType, "TABLE") == 0) {
				// pLB->AddString(tables.m_strName);
				if(lab_view)
					//lab_view->m_DataBaseTablesList.AddString(tables.m_strName);
					lab_view->m_DataBaseTablesList.names.push_back(tables.m_strName);
			}
			tables.MoveNext();
		}
		
		if(to_rewrite_list && lab_view)
			lab_view->m_DataBaseTablesList.RenewListCtrl();


		//m_strQuery.Format("select * from [%s]", tableDlg.m_strSelection);
		m_strQuery.Format("select * from [%s]", tables.m_strName);
    }
}
CEnGeologyView * CEnGeologyDoc::GetEnGeologyView()
{

	CEnGeologyView * lab_view = NULL;
	
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		lab_view = dynamic_cast<CEnGeologyView *>(pView);
		if (lab_view)
			break;
	}

	return lab_view;
		
}

void CEnGeologyDoc::OnDisconnect()
{
	CEnGeologyView * lab_view = this->GetEnGeologyView();

	if (lab_view) lab_view->m_DataBaseTablesList.names.clear();
	if(lab_view)  lab_view->m_DataBaseTablesList.RenewListCtrl();
}