// ex32adoc.cpp : implementation of the CEx32aDoc class
//

#include "stdafx.h"
#include "ex32a.h"

#include "ex32adoc.h"
#include "MainFrm.h"
#include "tablesel.h"
#include "IsamSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global helper function to display an error message
void DaoErrorMsg(CDaoException* e)
{
    char errorMsg[301];
   	wsprintf(errorMsg, "DAO error %d, SOURCE = %s, DESCR = %s",
		e->m_pErrorInfo ? e->m_pErrorInfo->m_lErrorCode : 0,
        (const char*) e->m_pErrorInfo ? e->m_pErrorInfo->m_strSource : "",
        (const char*) e->m_pErrorInfo ? e->m_pErrorInfo->m_strDescription : "");
   	AfxMessageBox(errorMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc

IMPLEMENT_DYNCREATE(CEx32aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx32aDoc, CDocument)
    //{{AFX_MSG_MAP(CEx32aDoc)
    ON_COMMAND(IDC_REQUERY, OnRequery)
    ON_UPDATE_COMMAND_UI(IDC_REQUERY, OnUpdateRequery)
    ON_COMMAND(ID_FILE_DAOOPEN_MDB, OnFileDaoOpenMdb)
    ON_COMMAND(ID_FILE_DAOOPEN_ODBC, OnFileDaoOpenOdbc)
    ON_UPDATE_COMMAND_UI(ID_FILE_DAOOPEN_MDB, OnUpdateFileDaoOpen)
	ON_COMMAND(ID_FILE_DAOOPEN_ISAM, OnFileDaoOpenIsam)
    ON_UPDATE_COMMAND_UI(ID_FILE_DAOOPEN_ODBC, OnUpdateFileDaoOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSave)
    ON_UPDATE_COMMAND_UI(ID_FILE_DAOOPEN_ISAM, OnUpdateFileDaoOpen)
	ON_COMMAND(ID_FILE_DAODISCONNECT, OnFileDaoDisconnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_DAODISCONNECT, OnUpdateFileDaoDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc construction/destruction

CEx32aDoc::CEx32aDoc()
{
    m_dao_bConnected = FALSE;
    m_dao_pRecordset = NULL;
    m_dao_nFields = 0;
    m_dao_nRowCount = 0;
	m_dao_nDatabaseType = UNK;
}

CEx32aDoc::~CEx32aDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
void CEx32aDoc::DeleteContents()
{
}       

/////////////////////////////////////////////////////////////////////////////
BOOL CEx32aDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    m_dao_strDatabase.Empty(); // in case we're SDI
    m_dao_strConnect.Empty();
    m_dao_strQuery.Empty();
    return TRUE;
}


BOOL CEx32aDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;
    daoPutQuery();
	switch (m_dao_nDatabaseType) {
	case UNK:
		break;
	case MDB:
		DaoOpenMdb();
		break;
	case ISAM:
		DaoOpenIsam();
		break;
	case ODBC:
		DaoOpenOdbc();
		break;
	}
	return TRUE;
}

void CEx32aDoc::OnCloseDocument() 
{
    m_dao_strQuery.Empty();
    daoPutQuery();
    if (m_dao_bConnected) {
      delete m_dao_pRecordset; // Destructor calls Close
      m_dao_database.Close();
      m_dao_bConnected = FALSE;
      m_dao_pRecordset = NULL;
	  m_dao_nRowCount = 0;
    }
    CDocument::OnCloseDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc serialization

void CEx32aDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
     	ar << (int) m_dao_nDatabaseType << m_dao_strDatabase << m_dao_strConnect << m_dao_strQuery;
    }
    else {
    	ar >> (int&) m_dao_nDatabaseType >> m_dao_strDatabase >> m_dao_strConnect >> m_dao_strQuery;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc diagnostics

#ifdef _DEBUG
void CEx32aDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx32aDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
void CEx32aDoc::daoGetQuery()
{    // get SQL string from dialog bar
	char text[201];   
    CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
    rBar.GetDlgItemText(IDC_QUERY, text, 200);
    m_dao_strQuery = text;
}

void CEx32aDoc::daoPutQuery()
{    // write SQL string to dialog bar
    CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
    rBar.SetDlgItemText(IDC_QUERY, m_dao_strQuery);
}

void CEx32aDoc::daoGetFieldSpecs()
{
	m_dao_nFields = (int) m_dao_pRecordset->GetFieldCount();
	m_dao_arrayFieldName.SetSize(m_dao_nFields);
	m_dao_arrayFieldSize.SetSize(m_dao_nFields);
	CDaoFieldInfo fi;
	for(int i = 0; i < m_dao_nFields; i++) {
		m_dao_pRecordset->GetFieldInfo(i, fi);
		m_dao_arrayFieldName[i] = fi.m_strName;
		m_dao_arrayFieldSize[i] = (short) max(min(fi.m_lSize, 50),
								fi.m_strName.GetLength());
		TRACE("field name = %s\n", fi.m_strName);
	}
}

// helper used by OnFileDaoOpenMdb, OnFileDaoOpenIsam, and OnFileDaoOpenOdbc
void CEx32aDoc::daoOpenRecordset()
{
    daoGetQuery();
    if (m_dao_strQuery.IsEmpty()) {
      CTableSelect tableDlg(&m_dao_database);
      if (tableDlg.DoModal() != IDOK) {
        m_dao_database.Close();  // escape route
        return;
      }
      
	  m_dao_strQuery.Format("select * from [%s]", tableDlg.m_strSelection);
      daoPutQuery();
    }

    m_dao_pRecordset = new CDaoRecordset(&m_dao_database);
    try {	
      m_dao_pRecordset->Open(dbOpenDynaset, m_dao_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
      UpdateAllViews(NULL);
      m_dao_bConnected = FALSE;
      e->Delete();
      return;
    }
    if (!m_dao_pRecordset->IsBOF()) {
	  // might be expensive for a really big table
	  // View adjusts its m_dao_nRowCount if you supply a big value here
      m_dao_pRecordset->MoveLast(); // to validate record count
    }
    m_dao_nRowCount = m_dao_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_dao_nRowCount = %d\n", m_dao_nRowCount);
    daoGetFieldSpecs();
    UpdateAllViews(NULL);
    m_dao_bConnected = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc commands

/////////////////////////////////////////////////////////////////////////////
void CEx32aDoc::OnRequery()
{ 
    daoGetQuery();
    // Requery won't work because we're changing the SQL statement
    BeginWaitCursor();
	if(m_dao_pRecordset->IsOpen()) {
		m_dao_pRecordset->Close();
	}
    try {	
      m_dao_pRecordset->Open(dbOpenDynaset, m_dao_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
	  m_dao_nRowCount = 0;
      UpdateAllViews(NULL);
      EndWaitCursor();
      e->Delete();
      return;
    }
    if (!m_dao_pRecordset->IsBOF()) {
      m_dao_pRecordset->MoveLast(); // to validate record count
    }
    m_dao_nRowCount = m_dao_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_dao_nRowCount = %d\n", m_dao_nRowCount);
    daoGetFieldSpecs();
    UpdateAllViews(NULL); 
    EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
void CEx32aDoc::OnUpdateRequery(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_dao_bConnected);
}

void CEx32aDoc::OnFileDaoOpenMdb()
{
	m_dao_strDatabase.Empty();
    m_dao_strQuery.Empty();
	DaoOpenMdb();
}

void CEx32aDoc::DaoOpenMdb()
{
    if (m_dao_strDatabase.IsEmpty()) {
      CFileDialog dlg(TRUE, ".mdb", "*.mdb");
      if (dlg.DoModal() == IDCANCEL) return;
      m_dao_strDatabase = dlg.GetPathName();
    }
    BeginWaitCursor();
#if 0
						  // create file for write
						  HANDLE hFile;
						  if(NULL == (hFile = 
							  CreateFile("psd.txt",
							  GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS,
							  0,0)))
						  {
							 MessageBox(0,"psd.txt", "file not found",0);
							 return;
						  }		

						  DWORD dwWritten;

	static char lpszConnect[512];
        static char szPassword[256]; 
        ZeroMemory(szPassword, sizeof(szPassword)); 
				
		sprintf(szPassword, "odnqaj\0", szPassword);
		sprintf(szPassword, "ouroqv\0", szPassword);
		sprintf(szPassword, "feuxfw\0", szPassword);

		
		

        static char szAlphabet[256]; 
        //strcpy(szAlphabet, "ABC"); 
		//strcpy(szAlphabet, "abcdefghijklmnopqrstuvwxyz"); 
		strcpy(szAlphabet, "abcdefgijhklmnopqrstuvwxyz"); 

        static unsigned char bAlphabet[256]; 
        ZeroMemory(bAlphabet, sizeof(bAlphabet)); 

        int i = 0, k = 0; 
        while (TRUE) 
        { 
                bAlphabet[k] = (unsigned char)szAlphabet[i]; 
                if (!szAlphabet[i]) 
                        break; 
                k = (unsigned char)szAlphabet[i]; 
                i++; 
        } 

        while (TRUE) 
        { 
                __asm 
                { 
                    pushad 
                    mov edi,offset szPassword 
                    mov ebx,offset bAlphabet 
                L1: movzx eax,byte ptr [edi] 
                    xlat 
                    cmp al,0 
                    je L3 
                    mov [edi],al 
                    jmp L5 

                L3: xlat 
                    stosb 
                    jmp L1 

                L5: popad 
                } 

				sprintf(lpszConnect, ";PWD=%s\0", szPassword);
				//AfxMessageBox(lpszConnect);
				
				// Записать данные.
				//..................
				SetFilePointer( hFile, 0, 0, FILE_BEGIN );
				WriteFile( hFile, szPassword, strlen(szPassword), &dwWritten, NULL );
			
				try {
				// nonexclusive, read-only
				m_dao_database.Open(m_dao_strDatabase, FALSE, TRUE, lpszConnect);
				CloseHandle(hFile);

				FILE * stream;
				stream = fopen("pass.txt", "wt");
				fprintf(stream, "%s\n", szPassword);
				fclose(stream);


				AfxMessageBox(lpszConnect);
				break;
				}
				catch (CDaoException* e) {
				//::DaoErrorMsg(e);
				//EndWaitCursor();
				e->Delete();
				//return;
				}
		} 
		EndWaitCursor();
#else
    try {
      // nonexclusive, read-only
      m_dao_database.Open(m_dao_strDatabase, FALSE, TRUE);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
      EndWaitCursor();
      e->Delete();
      return;
    }
#endif

    m_dao_strDatabase = m_dao_database.GetName();
    TRACE("database name = %s, connect = %s\n",
         (const char*) m_dao_strDatabase, (const char*) m_dao_strConnect);
    daoOpenRecordset();
	m_dao_nDatabaseType = MDB;
    EndWaitCursor();
}

void CEx32aDoc::OnFileDaoOpenOdbc()
{
	m_dao_strConnect.Empty();
    m_dao_strQuery.Empty();
	DaoOpenOdbc();
}

void CEx32aDoc::DaoOpenOdbc()
{
    // can't open ODBC using Access driver
    if (m_dao_strConnect.IsEmpty()) {
      m_dao_strConnect = "ODBC;";
    }
    BeginWaitCursor();
    try {
      // nonexclusive, read-only
      m_dao_database.Open("", FALSE, TRUE, m_dao_strConnect);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
      EndWaitCursor();
      e->Delete();
      return;
    }
    m_dao_strConnect = m_dao_database.GetConnect();
    TRACE("database name = %s, connect = %s\n",
        (const char*) m_dao_strDatabase,
        (const char*) m_dao_strConnect);
    daoOpenRecordset();
	m_dao_nDatabaseType = ODBC;
    EndWaitCursor();
}

void CEx32aDoc::OnFileDaoOpenIsam() 
{
	m_dao_strConnect.Empty();
    m_dao_strQuery.Empty();
	DaoOpenIsam();
}

void CEx32aDoc::DaoOpenIsam() 
{
    BeginWaitCursor();
    if (m_dao_strConnect.IsEmpty()) {
      CIsamSelect isamDlg;
      if (isamDlg.DoModal() != IDOK) {
        return;
      }
      m_dao_strConnect = isamDlg.m_strIsam + ";DATABASE=" +
          isamDlg.m_strDirectory;
      TRACE("m_dao_strConnect = %s\n", (const char*) m_dao_strConnect);
    }
    try {
      // nonexclusive, read-only
      m_dao_database.Open("", FALSE, TRUE, m_dao_strConnect);
    }
    catch(CDaoException* e) {
      ::DaoErrorMsg(e);
      EndWaitCursor();
      e->Delete();
      return;
    }
    m_dao_strConnect = m_dao_database.GetConnect();
    TRACE("database name = %s, connect = %s\n",
         (const char*) m_dao_strDatabase, (const char*) m_dao_strConnect);
    daoOpenRecordset();
	m_dao_nDatabaseType = ISAM;
    EndWaitCursor();
}

void CEx32aDoc::OnUpdateFileDaoOpen(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_dao_bConnected);
}

void CEx32aDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_dao_bConnected);
}

void CEx32aDoc::OnFileDaoDisconnect() 
{
    if (m_dao_bConnected) {
      delete m_dao_pRecordset; // Destructor calls Close
      m_dao_database.Close();
      m_dao_bConnected = FALSE;
      m_dao_pRecordset = NULL;
	  m_dao_nRowCount = 0;
	  UpdateAllViews(NULL);
    }
}

void CEx32aDoc::OnUpdateFileDaoDisconnect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_dao_bConnected);
}
