// labDoc.cpp : implementation of the CLabDoc class
//

#include "stdafx.h"

#include "lab.h"
#include "labDoc.h"
#include "labView.h"
#include "MainFrm.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetGeoTables.h"

#include "DlgProbGrunt.h"


#include "SetGridData.h"
#include "SetGridDataSurfaces.h"

#include "SetSurfacesOrder.h"
#include "SetSurfacesBlankOrder1.h"
#include "SetSurfacesBlankFunctions.h"


#include "SetCubeSize.h"
#include "SetGridDataUsedAlgorothms.h"
#include "SetKT.h"
#include "SetLito.h"
#include "SetIGE.h"
#include "SetRozriz.h"
#include "SetRozrizy1.h"

#include "SetSurfLitoMapping.h"
#include "SetSurfIgeMapping.h"

#include "../../surfdoc/src/Grid.h"
#include "../../surfdoc/src/Geosurface.h"

#if INCLUDE_3D

//#include "../../surfdoc/src/SurfDoc.h"
//#include "../../wintools/src/winsurf.h"
//#include "../../wintools/src/utility.h"
//#include "../../laboratory/src/lab.h"
//#include "../../wintools/src/win32_app.h"
//#include "../../wintools/src/win32_project.h"
//#include "../../laboratory/src/lab.h"
//#include "../../test/test_lib/lab.h"

#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class StringHelper
{
public:
	static LPTSTR ReverseFindOneOf(LPTSTR p1, LPCTSTR p2) throw()
	{
		LPTSTR _p1 = p1;
		while (_p1 != NULL && *_p1 != NULL)
		{
			_p1 = CharNext(_p1);
		}

		while (_p1 != NULL)
		{
			LPCTSTR p = p2;
			while (p != NULL && *p != NULL)
			{
				if (*_p1 == *p)
					return CharNext(_p1);
				p = CharNext(p);
			}
			_p1 = CharPrev(p1, _p1);
		}
		return NULL;
	}
};

#ifndef _WIN64
// global helper function to display an error message
void DaoErrorMsg(CDaoException* e)
{
    CString errorMsg;
	errorMsg.Format("DAO error %d, SOURCE = %s, DESCR = %s",
		e->m_pErrorInfo ? e->m_pErrorInfo->m_lErrorCode : 0,
        (const char*) e->m_pErrorInfo ? e->m_pErrorInfo->m_strSource : "",
        (const char*) e->m_pErrorInfo ? e->m_pErrorInfo->m_strDescription : "");
   	AfxMessageBox(errorMsg);
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CLabDoc
CString CLabDoc::s_strConnect = "ODBC;DSN=Wen Geo DB";
//CString CLabDoc::s_strDatabase = "C:\\Program Files\\Mathematical Center\\WenGeo\\WenGeo";
CString CLabDoc::GetWorkDir(bool write_registry)
{
	// Get the executable file path
	const size_t FilePathSize = MAX_PATH + 2;
	TCHAR szDir[FilePathSize];
	TCHAR szExeFilePath[FilePathSize];
	TCHAR szExeFileName[FilePathSize];
	TCHAR szIniFilePath[FilePathSize];
	TCHAR szIniFileName[FilePathSize];

	DWORD dwFLen = ::GetModuleFileName(NULL, szExeFilePath, MAX_PATH);
	if( dwFLen == 0 || dwFLen == MAX_PATH )
		return _T("");

	{
		TCHAR szTokens[] = _T("/\\");
		LPTSTR lpszToken = StringHelper::ReverseFindOneOf(szExeFilePath, szTokens);
		strcpy(szExeFileName, lpszToken);
		strcpy(szIniFileName, lpszToken);
		if ( NULL != lpszToken)
		{
			(*lpszToken) = 0;
		}
	}

	{
		TCHAR szTokens[] = _T(".");
		LPTSTR lpszToken = StringHelper::ReverseFindOneOf(szIniFileName, szTokens);
		if ( NULL != lpszToken)
		{
			(*lpszToken) = 0;
		}
		strcat(szIniFileName, _T("ini"));
	}

	strcpy(szDir, szExeFilePath);
	strcpy(szIniFilePath, szExeFilePath);
	strcat(szIniFilePath, szIniFileName);

	CString work_dir(szDir);


	// Test 
	TCHAR   inBuf[4096];
	DWORD test = GetPrivateProfileString (TEXT("Lab"), 
		TEXT("WorkDir"), 
		0, 
		inBuf, 
		4096, 
		szIniFilePath); 
	if (0 == test)
	{
		// create and write ini file
		WritePrivateProfileSection(_T("Lab"), _T(""), szIniFilePath); 

		// Write added values 
		work_dir += _T("..\\..\\..\\lab\\disk_C\\Laboratory");
		WritePrivateProfileString (TEXT("Lab"), 
			TEXT("WorkDir"), 
			work_dir, 
			szIniFilePath);

		/*DWORD res = GetPrivateProfileString (TEXT("Lab"), 
			TEXT("WorkDir"), 
			work_dir, 
			inBuf, 
			4096, 
			szIniFilePath);*/ 
	}
	else
		work_dir = inBuf; 

	if (write_registry)
	{
		TCHAR   inBuf[1024]; 
		HKEY   hKey1, hKey2, hKey3, hKey4; 
		DWORD  dwDisposition; 
		LONG   lRetCode; 
		TCHAR   szData[1024] = TEXT("Microsoft Access Driver (*.mdb)");

		// Create the .ini file key. 
		lRetCode = RegOpenKeyEx ( HKEY_LOCAL_MACHINE, 
			TEXT("SOFTWARE\\Wow6432Node\\ODBC\\ODBC.INI\\ODBC Data Sources"), 
			0, KEY_ALL_ACCESS, &hKey1); 

		if (ERROR_ACCESS_DENIED == lRetCode)
		{
			AfxMessageBox("Для записи в реестр настроек соединения с базой\nперезапустите программу с правами администратора");
		}

		if (lRetCode != ERROR_SUCCESS)
		{ 
			printf ("Error in creating ODBC.INI\Wen Geo DB key (%d).\n", lRetCode); 
			return work_dir; 
		} 

		// Set a section value 
		lRetCode = RegSetValueEx ( hKey1, 
			TEXT("Wen Geo DB"), 
			0, REG_SZ, (BYTE *)szData, sizeof(szData));

		if (lRetCode != ERROR_SUCCESS) 
		{ 
			printf ("Error in setting Wen Geo DB value\n"); 
			// Close the key
			lRetCode = RegCloseKey( hKey1 );
			if( lRetCode != ERROR_SUCCESS )
			{
				printf("Error in RegCloseKey (%d).\n", lRetCode);
				return work_dir;
			}
		}

		// Create an App Name key 
		lRetCode = RegCreateKeyEx ( HKEY_LOCAL_MACHINE, 
			TEXT("SOFTWARE\\Wow6432Node\\ODBC\\ODBC.INI\\Wen Geo DB"), 
			0, 
			NULL, 
			REG_OPTION_NON_VOLATILE,
			KEY_WRITE, 
			NULL, 
			&hKey2, 
			&dwDisposition); 

		if (lRetCode != ERROR_SUCCESS) 
		{ 
			printf ("Error in creating Wen Geo DB key (%d).\n", lRetCode); 

			// Close the key
			lRetCode = RegCloseKey( hKey2 );
			if( lRetCode != ERROR_SUCCESS )
			{
				printf("Error in RegCloseKey (%d).\n", lRetCode);
				return work_dir; 
			}
		} 

		// Set a section values 
		sprintf(szData, _T("C:\\Windows\\system32\\odbcjt32.dll"));
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("Driver"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		sprintf(szData, _T("%s\\WenGeo.mdb"), work_dir.GetBuffer());
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("DBQ"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		sprintf(szData, _T("Geocube bd"));
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("Description"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		DWORD value = 0x00000019;
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("DriverId"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

		sprintf(szData, _T("MS Access;"));
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("FIL"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		value = 0x00000000;
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("SafeTransactions"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

		sprintf(szData, _T("admin"));
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("UID"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		sprintf(szData, _T("%s"), CLabDoc::s_strDBPassword);
		lRetCode = RegSetValueEx ( hKey2, 
			TEXT("PWD"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));


		// Create an App Name key 
		lRetCode = RegCreateKeyEx ( HKEY_LOCAL_MACHINE, 
			TEXT("SOFTWARE\\Wow6432Node\\ODBC\\ODBC.INI\\Wen Geo DB\\Engines"), 
			0, 
			NULL, 
			REG_OPTION_NON_VOLATILE,
			KEY_WRITE, 
			NULL, 
			&hKey3, 
			&dwDisposition); 

		if (lRetCode != ERROR_SUCCESS) 
		{ 
			printf ("Error in creating Wen Geo DB key (%d).\n", lRetCode); 

			// Close the key
			lRetCode = RegCloseKey( hKey3 );
			if( lRetCode != ERROR_SUCCESS )
			{
				printf("Error in RegCloseKey (%d).\n", lRetCode);
				return work_dir; 
			}
		} 


		// Create an App Name key 
		lRetCode = RegCreateKeyEx ( HKEY_LOCAL_MACHINE, 
			TEXT("SOFTWARE\\Wow6432Node\\ODBC\\ODBC.INI\\Wen Geo DB\\Engines\\Jet"), 
			0, 
			NULL, 
			REG_OPTION_NON_VOLATILE,
			KEY_WRITE, 
			NULL, 
			&hKey4, 
			&dwDisposition); 

		if (lRetCode != ERROR_SUCCESS) 
		{ 
			printf ("Error in creating Wen Geo DB key (%d).\n", lRetCode); 

			// Close the key
			lRetCode = RegCloseKey( hKey4 );
			if( lRetCode != ERROR_SUCCESS )
			{
				printf("Error in RegCloseKey (%d).\n", lRetCode);
				return work_dir; 
			}
		} 

		sprintf(szData, _T(""));
		lRetCode = RegSetValueEx ( hKey4, 
			TEXT("ImplicitCommitSync"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		value = 0x00000800;
		lRetCode = RegSetValueEx ( hKey4, 
			TEXT("MaxBufferSize"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

		value = 0x00000005;
		lRetCode = RegSetValueEx ( hKey4, 
			TEXT("PageTimeout"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

		value = 0x00000003;
		lRetCode = RegSetValueEx ( hKey4, 
			TEXT("Threads"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

		sprintf(szData, _T("Yes"));
		lRetCode = RegSetValueEx ( hKey4, 
			TEXT("ImplicitCommitSync"), 0, REG_SZ, (BYTE *)szData, sizeof(TCHAR) * strlen(szData));

		// Close the keys
		lRetCode = RegCloseKey( hKey1 );
		if( lRetCode != ERROR_SUCCESS )
		{
			printf("Error in RegCloseKey (%d).\n", lRetCode);
			return work_dir;
		}

		lRetCode = RegCloseKey( hKey2 );
		if( lRetCode != ERROR_SUCCESS )
		{
			printf("Error in RegCloseKey (%d).\n", lRetCode);
			return work_dir;
		}

		lRetCode = RegCloseKey( hKey3 );
		if( lRetCode != ERROR_SUCCESS )
		{
			printf("Error in RegCloseKey (%d).\n", lRetCode);
			return work_dir;
		}

		lRetCode = RegCloseKey( hKey4 );
		if( lRetCode != ERROR_SUCCESS )
		{
			printf("Error in RegCloseKey (%d).\n", lRetCode);
			return work_dir;
		}
	}

	return work_dir;
}


CString CLabDoc::s_strDBPassword = "madzima";
CString CLabDoc::s_strWorkDir = GetWorkDir();
CString CLabDoc::s_strDatabase = CLabDoc::s_strWorkDir + "\\WenGeo";
CString CLabDoc::s_strExportDatabaseTemplate = CLabDoc::s_strWorkDir + "\\Export\\Export.mdb";

#if USE_GET_LAB_DOC
IMPLEMENT_DYNCREATE(CLabDoc, CDocument)
#endif
BEGIN_MESSAGE_MAP(CLabDoc, CDocument)
	//{{AFX_MSG_MAP(CLabDoc)
	ON_COMMAND(ID_FILE_ODBCCONNECT, OnFileOdbcConnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_ODBCCONNECT, OnUpdateFileOdbcConnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_ODBCDISCONNECT, OnUpdateFileOdbcDisconnect)
	ON_COMMAND(ID_FILE_ODBCDISCONNECT, OnFileOdbcDisconnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_3D, OnUpdateFile3d)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_INSERTTO3D, OnUpdateObjectsInsertto3d)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLabDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CLabDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ILab to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F8CBCD3C-AD09-4C3D-8048-5D311000B3A4}
static const IID IID_ILab =
{ 0xf8cbcd3c, 0xad09, 0x4c3d, { 0x80, 0x48, 0x5d, 0x31, 0x10, 0x0, 0xb3, 0xa4 } };

BEGIN_INTERFACE_MAP(CLabDoc, CDocument)
	INTERFACE_PART(CLabDoc, IID_ILab, Dispatch)
END_INTERFACE_MAP()


CString GetIGEName(CDatabase * database, long id_obj, long id_ige)
{
	CString str = "";
	CString strQuery;
	strQuery.Format("select * from [IGE]");	

	CString where;
	where.Format("ID_OBJ = %d and ID_IGE = %ld", id_obj, id_ige);

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
		_pRecordset->GetFieldValue("IGE", _var);

		str = CMyListCtrl::GetFieldString(_var);
	}

	_pRecordset->Close();
	delete _pRecordset;

	return str;
}

/////////////////////////////////////////////////////////////////////////////
// CLabDoc construction/destruction
ATable::ATable(CLabDoc * lab_doc, const char * table_name)
{
	m_table_name = table_name;
	m_lab_doc = lab_doc;
    m_pRecordset = NULL;
    m_nFields = 0;
    m_nRowCount = 0;
}

ATable::~ATable()
{
    if (m_pRecordset)
	{
		if (m_pRecordset->IsOpen())
			m_pRecordset->Close();
		delete m_pRecordset;
	}
}
CLabDoc::CLabDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();

    m_bConnected = FALSE;


	dll_w_project = NULL;

	long table_key;
	CString table_name;

	table_key = table_key_Granular;
	table_name = "Granular";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_FizMeh;
	table_name = "FizMeh";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_Objects;
	table_name = "Objects";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_ProbGr;
	table_name = "ProbGr";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_KT;
	table_name = "KT";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_TSZ;
	table_name = "PtStZond";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_Palja;
	table_name = "PtPalja";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_IGE;
	table_name = "IGE";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_Litho;
	table_name = "Lito";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_Voda;
	table_name = "Voda";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_Zriz;
	table_name = "Zriz";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));
	
	table_key = table_key_Compress;
	table_name = "Cilce";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));


	table_key = table_key_Genezis;
	table_name = "Genezis";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));

	table_key = table_key_GranSklad;
	table_name = "GranSklad";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));

	table_key = table_key_GrMain;
	table_name = "GrMain";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));

	table_key = table_key_Grunty;
	table_name = "Grunty";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));

	table_key = table_key_PodTypyGr;
	table_name = "PodTypyGr";
	m_tables.insert(map<long, ATable *>::value_type(table_key, new ATable(this, table_name)));



}

CLabDoc::~CLabDoc()
{
	AfxOleUnlockApp();
}

BOOL CLabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;



	return TRUE;
}
void RegistryODBCDatabaseName()
{

	LONG  lResult;
	HKEY  hKeyResult = 0;
	DWORD dwDisposition = 0;

	bool toRegSetValue;

	// Создать или открыть ключ
	//................................
	lResult = RegCreateKeyEx( HKEY_CURRENT_USER,
      		"Software\\Ukr NII NTIZ\\Laboratory\\Settings", 0, "",
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			NULL, &hKeyResult, &dwDisposition );
		
	toRegSetValue = true;

	if(toRegSetValue)
	{
		// Присвоить значение
		//..................................
		if ( lResult == ERROR_SUCCESS )
		{
			lResult = RegSetValueEx( hKeyResult, "DestFileBD", 0, REG_SZ,
				(const BYTE *)CLabDoc::s_strDatabase.GetBuffer(CLabDoc::s_strDatabase.GetLength()), CLabDoc::s_strDatabase.GetLength()+1);
			RegCloseKey( hKeyResult );
		}
	}
}
void RegistryODBCConnectString()
{

	LONG  lResult;
	HKEY  hKeyResult = 0;
	DWORD dwDisposition = 0;

	bool toRegSetValue;

	// Создать или открыть ключ
	//................................
	lResult = RegCreateKeyEx( HKEY_CURRENT_USER,
      		"Software\\Ukr NII NTIZ\\Laboratory\\Settings", 0, "",
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			NULL, &hKeyResult, &dwDisposition );
		
	toRegSetValue = true;

	if(toRegSetValue)
	{
		// Присвоить значение
		//..................................
		if ( lResult == ERROR_SUCCESS )
		{
			lResult = RegSetValueEx( hKeyResult, "ConnectString", 0, REG_SZ,
				(const BYTE *)CLabDoc::s_strConnect.GetBuffer(CLabDoc::s_strConnect.GetLength()), CLabDoc::s_strConnect.GetLength()+1);
			RegCloseKey( hKeyResult );
		}
	}
}

void CLabDoc::FirstOdbcConnect()
{
	m_strConnect.Empty();
    m_strQuery.Empty();
	
	if (OpenOdbc(CLabDoc::s_strConnect, true))
		return;

	GetWorkDir(true);

	if (OpenOdbc(CLabDoc::s_strConnect, true))
		return;

	m_strConnect.Empty();
	m_strQuery.Empty();
	if (OpenOdbc("ODBC;", true))
	{
		CLabDoc::s_strConnect = m_strConnect;
		RegistryODBCConnectString();
		CLabDoc::s_strDatabase = m_strDatabaseName;
		RegistryODBCDatabaseName();
	}

}



/////////////////////////////////////////////////////////////////////////////
// CLabDoc serialization

void CLabDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLabDoc diagnostics

#ifdef _DEBUG
void CLabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLabDoc commands
void CLabDoc::OnUpdateFileOdbcConnect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_bConnected);	
}
void CLabDoc::OnFileOdbcConnect() 
{
	m_strConnect.Empty();
	m_strQuery.Empty();
	if (!OpenOdbc("ODBC;", true))
	{
	}
	else
	{
		CLabDoc::s_strConnect = m_strConnect;
		RegistryODBCConnectString();
		CLabDoc::s_strDatabase = m_strDatabaseName;
		RegistryODBCDatabaseName();
	}
}



void ATable::Open_Recordset(CMyListCtrl * my_list_ctrl, CString where, CString order_by)
{
	if (my_list_ctrl)
	{
		my_list_ctrl->DeleteAllItems();

		if (this->m_lab_doc)
		{		
			this->m_lab_doc->m_strQuery.Format("select * from [%s]", m_table_name);		
			 
			if (!m_pRecordset) m_pRecordset = new CRecordset(&this->m_lab_doc->m_database);
			
			if (m_pRecordset->IsOpen())
				m_pRecordset->Close();

			try {
				m_pRecordset->m_strFilter = where;
				m_pRecordset->m_strSort = order_by;
				m_pRecordset->Open(CRecordset::dynaset, this->m_lab_doc->m_strQuery, CRecordset::readOnly);
			}
			catch (CDBException* pe) {
				AfxMessageBox(pe->m_strError);
				pe->Delete();
				return;
			}

			if (!m_pRecordset->IsBOF()) {
				while(!m_pRecordset->IsEOF()) {
					m_pRecordset->MoveNext(); // to validate record count
				}
			}

			m_nRowCount = m_pRecordset->GetRecordCount() + 1;
			TRACE("m_nRowCount = %d\n", m_nRowCount);	

			my_list_ctrl->FillCtrlList(m_pRecordset);
		}
	}
}

void CLabDoc::OnUpdateFileOdbcDisconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bConnected);
}

void CLabDoc::OnFileOdbcDisconnect() 
{
	if (m_bConnected) {

		this->m_tables.clear();
		m_database.Close();
		m_bConnected = FALSE; 

		OnDisconnect();

		
		UpdateAllViews(NULL);
    }
}




void CLabDoc::OnUpdateFile3d(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(true);	
}

void CLabDoc::OnUpdateObjectsInsertto3d(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(true);	
}
long SetObject::GetNewKeyID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_OBJ > id)
				id = this->m_ID_OBJ;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}
bool CLabDoc::AddNewObject(const char * contract, const char * object_name)
{

	SetObject setObject(&this->m_database);

	if ( !setObject.Open(CRecordset::dynaset) )
        return false;

	try
	{
		long id_for_new_object = setObject.GetNewKeyID();

		setObject.AddNew();

		setObject.m_ID_OBJ = id_for_new_object;
		setObject.m_CONTRACT = contract;
		setObject.m_NAZVA = object_name;

		setObject.Update();
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}

	this->UpdateAllViews(NULL);

	return true;
}

bool CLabDoc::AddNewProbGrunt(CDlgProbGrunt * dlg, long ID_OBJ)
{
	try
	{		
		long LAB_N = atoi(dlg->m_lab_n);

		SetProbGr setProbGr0(&this->m_database);
		setProbGr0.m_strFilter.Format("ID_OBJ = %d and LAB_N = %d", ID_OBJ, LAB_N);
		if ( !setProbGr0.Open(CRecordset::dynaset) )
			return false;

		if (!setProbGr0.IsBOF()) 
		{
			while(!setProbGr0.IsEOF()) 
			{
				setProbGr0.MoveNext();
			}
		}
		if (setProbGr0.GetRecordCount() > 0)
		{
			CString s;
			s.Format("Лабораторный номер %d уже существует в базе\n"
				"Он не может быть продублирован", LAB_N);
			AfxMessageBox(s);
			return false;
		}




		SetProbGr setProbGr(&this->m_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, dlg->id_kt);
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return false;

		long id_for_new_ProbGr = setProbGr.GetNewKeyID();

		setProbGr.AddNew();

		setProbGr.m_ID_OBJ = ID_OBJ;
		setProbGr.m_ID_KT = dlg->id_kt;
		setProbGr.m_ID_PROB = id_for_new_ProbGr;
		setProbGr.m_H = atof(dlg->m_prob_gr_h);
		setProbGr.m_LAB_N = LAB_N;
		setProbGr.m_ID_KODPROB = dlg->i_kod_prob+1;
		setProbGr.m_ID_GR;

		setProbGr.Update();
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}

	this->UpdateAllViews(NULL);

	return true;
}




bool CLabDoc::EditProbGrunt(CDlgProbGrunt * dlg, long ID_OBJ)
{
	try
	{			
		long LAB_N = atoi(dlg->m_lab_n);

		SetProbGr setProbGr0(&this->m_database);
		setProbGr0.m_strFilter.Format("ID_OBJ = %d and LAB_N = %d", ID_OBJ, LAB_N);
		if ( !setProbGr0.Open(CRecordset::dynaset) )
			return false;

		if (!setProbGr0.IsBOF()) 
		{
			setProbGr0.MoveFirst();
			while(!setProbGr0.IsEOF()) 
			{
				bool the_same = setProbGr0.m_ID_OBJ == ID_OBJ &&
					setProbGr0.m_ID_KT == dlg->id_kt &&
					setProbGr0.m_ID_PROB == dlg->id_prob;
				if (!the_same)
				{
					CString s;
					s.Format("Лабораторный номер %d уже существует в базе\n"
						"Он не может быть продублирован", LAB_N);
					AfxMessageBox(s);
					return false;
				}


				setProbGr0.MoveNext();
			}
		}

		SetProbGr setProbGr(&this->m_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
			ID_OBJ, dlg->id_kt, dlg->id_prob);
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return false;

		if (!setProbGr.IsBOF()) 
		{
			setProbGr.MoveFirst( );

			if(!setProbGr.IsEOF()) 
			{

				setProbGr.Edit();

		//		setProbGr.m_ID_OBJ = ID_OBJ;
		//		setProbGr.m_ID_KT = dlg->id_kt;
		//		setProbGr.m_ID_PROB = dlg->id_prob;
				setProbGr.m_H = atof(dlg->m_prob_gr_h);
				setProbGr.m_LAB_N = atoi(dlg->m_lab_n);
				setProbGr.m_ID_KODPROB = dlg->i_kod_prob+1;
				setProbGr.m_ID_GR;

						
				setProbGr.Update();
			}
		}




	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}

	this->UpdateAllViews(NULL);

	return true;
}

// helper used by OnFileDaoOpenMdb, OnFileDaoOpenIsam, and OnFileDaoOpenOdbc





void CLabDoc::DaoOpenOdbc()
{
#if 0
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
//    daoOpenRecordset();
//	m_dao_nDatabaseType = ODBC;
    EndWaitCursor();
#endif
}
void CLabDoc::ImportObject()
{
	SetObject setObject(&this->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
        return;
	long id_for_new_object = setObject.GetNewKeyID();
#ifndef _WIN64
 	CString m_dao_strDatabase;
	CString m_dao_strConnect;
	CString m_dao_strQuery;

	m_dao_strDatabase.Empty();
    m_dao_strQuery.Empty();

	CDaoRecordset* m_dao_pRecordset;
	CDaoDatabase m_dao_database;
	
	//DaoOpenMdb();
    if (m_dao_strDatabase.IsEmpty()) {
		CFileDialog dlg(TRUE, ".mdb", "*.mdb");
		if (dlg.DoModal() == IDCANCEL) return;
		m_dao_strDatabase = dlg.GetPathName();
    }
    BeginWaitCursor();

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
	m_dao_strDatabase = m_dao_database.GetName();
	TRACE("database name = %s, connect = %s\n",
		(const char*) m_dao_strDatabase, (const char*) m_dao_strConnect);

	long ID_OBJ = -1;
	VARIANT id_obj;
	if (true)
	{
		m_dao_strQuery.Format("select * from [Objects]");
		m_dao_pRecordset = new CDaoRecordset(&m_dao_database);
		try {	
			m_dao_pRecordset->Open(dbOpenDynaset, m_dao_strQuery, dbReadOnly);
		}
		catch (CDaoException* e) {
			::DaoErrorMsg(e);
			e->Delete();
			return;
		}

		if (!m_dao_pRecordset->IsBOF()) {
			m_dao_pRecordset->MoveFirst(); 
			if (!m_dao_pRecordset->IsEOF())
			{  
				COleVariant m_var; // must declare this inside the loop
				m_dao_pRecordset->GetFieldValue("ID_OBJ", m_var);
				id_obj = m_var;
			}
		}
		m_dao_pRecordset->Close();
		delete m_dao_pRecordset;
	}

	if (id_obj.vt == VT_I4)
	{
		ID_OBJ = id_obj.lVal;
	}
	else
	{
		return;
	}

	if (ID_OBJ < 0)
		return;

	CString m_dao_strConnect_1;
	m_dao_strConnect_1.Format(";PWD=%s\0", CLabDoc::s_strDBPassword);
	CDaoDatabase m_dao_database_1;
	try {
		// nonexclusive, no read-only
		m_dao_database_1.Open(
			CLabDoc::s_strDatabase, 
			FALSE, FALSE, m_dao_strConnect_1);
	}
	catch (CDaoException* e) {
		::DaoErrorMsg(e);
		EndWaitCursor();
		e->Delete();
		return;
	}

	SetGeoTables setGeoTables(&this->m_database);
	if (!setGeoTables.Open())
	{
		return;
	}
	if (!setGeoTables.IsBOF()) 
	{
		setGeoTables.MoveFirst( );
		while(!setGeoTables.IsEOF()) 
		{
			long ID = setGeoTables.m_ID;
			CString table_nazva = setGeoTables.m_NAZVA;
			//MessageBox(table_nazva, "table_nazva", 0);

			if (true)
			{
				//  таблица - источник
				m_dao_strQuery.Format("select * from [%s]", table_nazva);
				m_dao_pRecordset = new CDaoRecordset(&m_dao_database);
				try {	
					m_dao_pRecordset->m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
					m_dao_pRecordset->Open(dbOpenDynaset, m_dao_strQuery, dbReadOnly);
				}
				catch (CDaoException* e) {
					// В таблице источнике мы не можем найти нужную таблицу
					// возможно мы импортируем файл устаревшей версии
					e->m_nAfxDaoError;//-842150451
					e->m_scode;//-2146825210
					::DaoErrorMsg(e);
					e->Delete();
					setGeoTables.MoveNext(); // to validate record count
					continue;
				}

				// таблица - приёмник

				CString m_strQuery_1;
				m_strQuery_1.Format("select * from [%s]", table_nazva);

				CDaoRecordset* m_pRecordset_1;					
				m_pRecordset_1 = new CDaoRecordset(&m_dao_database_1);

				try {
					m_pRecordset_1->Open(dbOpenDynaset, m_strQuery_1, dbAppendOnly);
				}
				catch (CDaoException* pe) {
					::DaoErrorMsg(pe);
					pe->Delete();
					EndWaitCursor();
					m_pRecordset_1->Close();
					delete m_pRecordset_1;
					return ;
				}

				// имена полей в таблице - приёмнике
				int m_nFields_1 = (int) m_pRecordset_1->GetFieldCount();
				CDaoFieldInfo fi_1;
				CStringArray m_arrayFieldName_1;
				CWordArray m_arrayFieldSize_1;
				vector<bool> m_arrayFieldWarningsMsg(m_nFields_1);
				m_arrayFieldName_1.SetSize(m_nFields_1);
				m_arrayFieldSize_1.SetSize(m_nFields_1);
				for(int i = 0; i < m_nFields_1; i++) {
					m_arrayFieldWarningsMsg[i] = true;
					m_pRecordset_1->GetFieldInfo(i, fi_1);
					m_arrayFieldName_1[i] = fi_1.m_strName;
					m_arrayFieldSize_1[i] = (short) max(min(fi_1.m_lSize, 250),
						fi_1.m_strName.GetLength());
					TRACE("field name = %s\n", fi_1.m_strName);
				}

				// перебираем строки (записи) в таблице - источнике
				if (!m_dao_pRecordset->IsBOF())
				{
					m_dao_pRecordset->MoveFirst();
					while (!m_dao_pRecordset->IsEOF())
					{      
						// добавляем строку (запись) в таблицу приёмник
						m_pRecordset_1->AddNew();
						for(int i = 0; i < m_nFields_1; i++) 
						{
							COleVariant m_var; // must declare this inside the loop		

							// из таблицы - источника запрашиваем значение поля по данному имени
							try {
								m_dao_pRecordset->GetFieldValue(m_arrayFieldName_1[i], m_var);
							}
							// на тот случай, когда в таблице источника нет этого поля
							// (это может быть если таблица источника более ранней версии,
							// а в таблицу приёмника уже добавлена новая колонка)
							// используем отлов исключения
							catch (CDaoException* pe) {
								if (pe->m_scode == -2146825023){
								if (m_arrayFieldWarningsMsg[i])
								{
									CString swarning;
									swarning.Format("Предупреждение:\nв импортируемой таблице %s\nотсутствует столбец %s\nОн не будет заполнен в загруженном объекте\nПри необходимости Вы должны заполнить этот столбец вручную", table_nazva, m_arrayFieldName_1[i]);

									AfxMessageBox(swarning);
									m_arrayFieldWarningsMsg[i] = false;
								}}else
								::DaoErrorMsg(pe);
								pe->Delete();
								// если поймали исключение продолжаем цикл,
								// не заполняя поле в таблице приёмника
								continue;
							}
							if (m_arrayFieldName_1[i] == "ID_OBJ")
							{
								m_var = id_for_new_object;
							}
							m_pRecordset_1->SetFieldValue(m_arrayFieldName_1[i], m_var);
						}
						m_pRecordset_1->Update();								
						m_dao_pRecordset->MoveNext();
					}
				}

				m_pRecordset_1->Close();
				delete m_pRecordset_1;

				m_dao_pRecordset->Close();
				delete m_dao_pRecordset;
			}
			setGeoTables.MoveNext(); // to validate record count
		}
	}




	m_dao_database.Close();
	m_dao_database_1.Close();
#endif


//	m_dao_nDatabaseType = MDB;
    EndWaitCursor();
}


bool CLabDoc::ClearGridData(long ID_OBJ)
{
	SetGriddataSurfaces setGridDataSurfaces(&this->m_database);
	setGridDataSurfaces.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( !setGridDataSurfaces.Open(CRecordset::dynaset) )
        return false;
	if (!setGridDataSurfaces.IsBOF()) 
	{
		setGridDataSurfaces.MoveFirst();
		while(!setGridDataSurfaces.IsEOF()) 
		{
			setGridDataSurfaces.Delete();
			setGridDataSurfaces.MoveNext();
		}
	}	
	
	SetGridData setGridData(&this->m_database);
	setGridData.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( !setGridData.Open(CRecordset::dynaset) )
        return false;
	if (!setGridData.IsBOF()) 
	{
		setGridData.MoveFirst();
		while(!setGridData.IsEOF()) 
		{
			setGridData.Delete();
			setGridData.MoveNext();
		}
	}
	return true;
}
bool CLabDoc::ClearGridData(long ID_OBJ, long ID_SURF)
{
	SetGriddataSurfaces setGridDataSurfaces(&this->m_database);
	setGridDataSurfaces.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( !setGridDataSurfaces.Open(CRecordset::dynaset) )
        return false;
	if (!setGridDataSurfaces.IsBOF()) 
	{
		setGridDataSurfaces.MoveFirst();
		while(!setGridDataSurfaces.IsEOF()) 
		{
			setGridDataSurfaces.Delete();
			setGridDataSurfaces.MoveNext();
		}
	}

	SetGridData setGridData(&this->m_database);
	setGridData.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( !setGridData.Open(CRecordset::dynaset) )
        return false;
	if (!setGridData.IsBOF()) 
	{
		setGridData.MoveFirst();
		while(!setGridData.IsEOF()) 
		{
			setGridData.Delete();
			setGridData.MoveNext();
		}
	}
	return true;
}
bool CLabDoc::ClearGridDataPoint(long ID_OBJ, long ID_SURF, long ID_POINT)
{
	SetGridData setGridData(&this->m_database);
	setGridData.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d and ID_POINT = %d", ID_OBJ, ID_SURF, ID_POINT);
	if ( !setGridData.Open(CRecordset::dynaset) )
        return false;
	if (!setGridData.IsBOF()) 
	{
		setGridData.MoveFirst();
		while(!setGridData.IsEOF()) 
		{
			setGridData.Delete();
			setGridData.MoveNext();
		}
	}
	return true;
}
	
bool CLabDoc::ReNameGridDataSurface(long ID_OBJ, long ID_SURF, CString NAZVA)
{
	try
	{
		SetGriddataSurfaces setGridDataSurfaces(&this->m_database);
		setGridDataSurfaces.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGridDataSurfaces.Open(CRecordset::dynaset) )
			return false;

		if (!setGridDataSurfaces.IsBOF()) 
		{
			setGridDataSurfaces.MoveFirst();
			if(!setGridDataSurfaces.IsEOF()) 
			{
				setGridDataSurfaces.Edit();
				setGridDataSurfaces.m_NAZVA = NAZVA;
				setGridDataSurfaces.Update();
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

bool CLabDoc::ReColorGridDataSurface(long ID_OBJ, long ID_SURF, COLORREF color)
{
	try
	{
		SetGriddataSurfaces setGridDataSurfaces(&this->m_database);
		setGridDataSurfaces.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGridDataSurfaces.Open(CRecordset::dynaset) )
			return false;

		if (!setGridDataSurfaces.IsBOF()) 
		{
			setGridDataSurfaces.MoveFirst();
			if(!setGridDataSurfaces.IsEOF()) 
			{
				setGridDataSurfaces.Edit();
				setGridDataSurfaces.m_r = GetRValue(color);
				setGridDataSurfaces.m_g = GetGValue(color);
				setGridDataSurfaces.m_b = GetBValue(color);
				setGridDataSurfaces.Update();
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


bool CLabDoc::AddGridDataSurface(long ID_OBJ, long ID_SURF, CString	NAZVA, BYTE PODOSHVA, COLORREF rgb, long ID_UMPOZ, long ID_IGE)
{
	try
	{
		SetGriddataSurfaces setGridDataSurfaces(&this->m_database);
		setGridDataSurfaces.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGridDataSurfaces.Open(CRecordset::dynaset) )
			return false;

		setGridDataSurfaces.AddNew();

		setGridDataSurfaces.m_ID_OBJ = ID_OBJ;
		setGridDataSurfaces.m_ID_SURF = ID_SURF;
		setGridDataSurfaces.m_NAZVA = NAZVA;
		setGridDataSurfaces.m_PODOSHVA = PODOSHVA;

		setGridDataSurfaces.m_r = GetRValue(rgb);
		setGridDataSurfaces.m_g = GetGValue(rgb);
		setGridDataSurfaces.m_b = GetBValue(rgb);

		setGridDataSurfaces.m_ID_UMPOZ = ID_UMPOZ;
		setGridDataSurfaces.m_ID_IGE = ID_IGE;

		setGridDataSurfaces.Update();
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}


	return true;
}
bool CLabDoc::EditGridData(long ID_OBJ, long ID_SURF, long ID_POINT, double X, double Y, double Z)
{
	try
	{
		SetGridData setGridData(&this->m_database);
		setGridData.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d and ID_POINT = %d", 
			ID_OBJ, ID_SURF, ID_POINT);
		if ( !setGridData.Open(CRecordset::dynaset) )
			return false;

		if (!setGridData.IsBOF()) 
		{
			setGridData.MoveFirst();
			if(!setGridData.IsEOF()) 
			{
				setGridData.Edit();

				setGridData.m_X = X;
				setGridData.m_Y = Y;
				setGridData.m_Z = Z;

				setGridData.Update();
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
CString GetKTName(CDatabase * database, long ID_OBJ, long ID_KT)
{
	CString str = "";
	SetKT setKT(database);
	setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	if ( setKT.Open(CRecordset::dynaset) )
	{
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			if(!setKT.IsEOF()) 
			{
				str = setKT.m_NAZVA;
			}
		}
	}		
	return str;
}








void CLabDoc::ProbgrIGEautoFill(bool to_msg_box, long ID_OBJ, long ID_KT) 
{
	CString str, str_list, str_undet, s;
	int det = 0, undet = 0;

	SetProbGr setProbGr(&this->m_database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return;
	if (!setProbGr.IsBOF()) 
	{
		setProbGr.MoveFirst();
		while(!setProbGr.IsEOF()) 
		{
//			long ID_KT = setProbGr.m_ID_KT;
			double H = setProbGr.m_H;
			long ID_IGE = setProbGr.m_ID_IGE;

			bool ige_determined = false;

			if (true)
			{
				SetLito setLito(false, &this->m_database);
				setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
				setLito.m_strSort.Format("");
				if ( !setLito.Open(CRecordset::dynaset) )
					return;

				if (!setLito.IsBOF()) 
				{
					setLito.MoveFirst( );
					while(!setLito.IsEOF()) 
					{
						if (H > setLito.m_H0 && H <= setLito.m_H1)
						{
							setProbGr.Edit();
							setProbGr.m_ID_IGE = setLito.m_ID_IGE;
							setProbGr.Update();
							ige_determined = true;
							det++;
							break;
						}
						setLito.MoveNext();
					}
				}

				if (to_msg_box && !ige_determined)
				{
					undet++;
					s.Format("скважина %s глубина %0.1f\n", 
						GetKTName(&this->m_database, ID_OBJ, ID_KT),
						H);
					str_undet += s;
				}
			}
			setProbGr.MoveNext();
		}
	}	

	if (to_msg_box)
	{
		UINT nType;
		if (!undet)
		{
			nType = MB_OK;
			str.Format("На основе разбивки скважин\n"
//				"для объекта %s контракт %s\n"
				"было заполено ИГЭ для %d проб грунта", 
//				setObject.m_NAZVA, setObject.m_CONTRACT, 
				det);
		}
		else
		{
			nType = MB_YESNO;
			str_list.Format("На основе разбивки скважин\n"
//				"для объекта %s контракт %s\n"
				"было заполено ИГЭ для %d проб грунта\n"
				"Нижеследующие %d проб грунта оказались с неопределённым ИГЭ:\n"
				"%s\n",
//				setObject.m_NAZVA, setObject.m_CONTRACT, 
				det, undet, str_undet);

			str.Format(
				"%s\n"
				"Вы хотите записать этот список в текстовый файл?", 
				str_list);
		}
		if (IDYES == AfxMessageBox(str, nType))
		{
			TCHAR filter[4098];
			sprintf_s(filter, 4098, TEXT("txt"));
			CFileDialog dlg(FALSE, filter);
			if (dlg.DoModal() == IDCANCEL) return;
			CString path = dlg.GetPathName();

			FILE * txt = fopen(path, "wt");
			if (txt)
			{
				fprintf(txt, "%s\n", str_list);
				fclose(txt);
			}
		}
	}
}



bool CLabDoc::AddGridData(long ID_OBJ, long ID_SURF, long ID_POINT, double X, double Y, double Z)
{
	try
	{
		SetGridData setGridData(&this->m_database);
		setGridData.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGridData.Open(CRecordset::dynaset) )
			return false;

		setGridData.AddNew();

		setGridData.m_ID_OBJ = ID_OBJ;
		setGridData.m_ID_SURF = ID_SURF;
		setGridData.m_ID_POINT = ID_POINT;
		setGridData.m_X = X;
		setGridData.m_Y = Y;
		setGridData.m_Z = Z;

		setGridData.Update();
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}


	return true;
}


long CLabDoc::AddKT(long ID_OBJ, long ID_TYP, const char * nazva, double X, double Y, double Z)
{
	SetKT setKT(&this->m_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( !setKT.Open(CRecordset::dynaset) )
		return -1;

	long id_for_new_KT = -1;

	SetKT setKT_2(&this->m_database);
	setKT_2.m_strFilter.Format("ID_OBJ = %d and NAZVA = '%s'", ID_OBJ, nazva);
	if ( !setKT_2.Open(CRecordset::dynaset) )
		return -1;

	if (!setKT_2.IsBOF()) {
		while(!setKT_2.IsEOF()) {
			setKT_2.MoveNext(); // to validate record count
		}
	}

    bool found = setKT_2.GetRecordCount() > 0;

	if (!found)
	{
		id_for_new_KT = setKT.GetNewKeyID();

		setKT.AddNew();

		setKT.m_ID_OBJ = ID_OBJ;
		setKT.m_ID_KT = id_for_new_KT;
		setKT.m_NAZVA = nazva;
		setKT.m_X = X;
		setKT.m_Y = Y;
		setKT.m_Z = Z;
		setKT.m_ID_TYP = ID_TYP;
		setKT.m_ID_BUR;
		setKT.m_D_BUR;
		setKT.m_DTBUR;

		setKT.Update();	
	}
	else
	{
		id_for_new_KT = setKT_2.m_ID_KT;


		if (!setKT_2.IsBOF()) 
		{
			setKT_2.MoveFirst( );

			if(!setKT_2.IsEOF()) 
			{
				setKT_2.Edit();

				setKT_2.m_X = X;
				setKT_2.m_Y = Y;
				setKT_2.m_Z = Z;

				setKT_2.Update();	
			}
		}
	}

	return id_for_new_KT;

}

long GetID_IGE(bool bUnEdited, CDatabase * database, long ID_OBJ, CString IGE)
{
	SetIGE setIGE(bUnEdited, database);
	setIGE.m_strFilter.Format("ID_OBJ = %d and IGE = '%s'", ID_OBJ, IGE);
	setIGE.m_strSort.Format("");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return 0;

	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		if(!setIGE.IsEOF()) 
		{
			return setIGE.m_ID_IGE;
		}
	}
	return 0;
}

bool CLabDoc::ClearLito(bool bUnEdited, long ID_OBJ, long ID_KT)
{
	SetLito setLito(bUnEdited, &this->m_database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	if ( !setLito.Open(CRecordset::dynaset) )
		return false;

	if (!setLito.IsBOF()) {
		setLito.MoveFirst();
		while(!setLito.IsEOF()) {
			setLito.Delete();
			setLito.MoveNext(); 
		}
	}
	return true;
}

bool CLabDoc::EditLito(long ID_OBJ, long ID_KT, double key_H0, double H0, double H1, bool edit_H0, bool edit_H1)
{
	double epsilon = 1e-6;

	bool bUnEdited = false;
	SetLito setLito(bUnEdited, &this->m_database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	if ( !setLito.Open(CRecordset::dynaset) )
		return false;

	// find by key_H0 
	// we can not do this using m_strFilter because H0 is double
	// so we must apply epsilon
	if (!setLito.IsBOF())
	{
		setLito.MoveFirst( );
		while(!setLito.IsEOF()) 
		{
			if (fabs(setLito.m_H0 - key_H0) < epsilon)
			{
				setLito.Edit();

				if (edit_H0)
					setLito.m_H0 = 1.e-6*(double(long(1.0e6*H0)));
				if (edit_H1)
					setLito.m_H1 = 1.e-6*(double(long(1.0e6*H1)));

				setLito.Update();
				return true;
			}
			setLito.MoveNext(); // to validate record count
		}
	}
	return false;
}
bool CLabDoc::EditLito(bool bUnEdited, long ID_OBJ, long ID_KT, CString IGE, double H0, double H1)
{
	long ID_IGE = GetID_IGE(bUnEdited, &this->m_database, ID_OBJ, IGE);

	SetLito setLito(bUnEdited, &this->m_database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_IGE = %d", ID_OBJ, ID_KT, ID_IGE);
	if ( !setLito.Open(CRecordset::dynaset) )
		return false;

	if (!setLito.IsBOF())
	{
		setLito.MoveFirst( );
		while(!setLito.IsEOF()) 
		{
			setLito.Edit();
			setLito.m_H0 = H0;
			setLito.m_H1 = H1;
			setLito.Update();
			return true;

			setLito.MoveNext(); // to validate record count
		}
	}
	return false;

}
bool CLabDoc::AddLito(bool bUnEdited, long ID_OBJ, long ID_KT, CString IGE, double H0, double H1)
{
	long ID_IGE = GetID_IGE(bUnEdited, &this->m_database, ID_OBJ, IGE);

	SetLito setLito(bUnEdited, &this->m_database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	if ( !setLito.Open(CRecordset::dynaset) )
		return false;

	setLito.AddNew();

	setLito.m_ID_OBJ = ID_OBJ;
	setLito.m_ID_KT = ID_KT;
	setLito.m_ID_IGE = ID_IGE;
	setLito.m_H0 = H0;
	setLito.m_H1 = H1;

	setLito.Update();

	return true;
}
bool CLabDoc::ClearSurfIgeMapping(long ID_OBJ)
{
	SetSurfIgeMapping Set(&this->m_database);

	Set.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( Set.Open(CRecordset::dynaset) )
	{
		if (!Set.IsBOF()) 
		{
			Set.MoveFirst();
			while(!Set.IsEOF()) 
			{
				Set.Delete();
				Set.MoveNext();
			}
		}
	}
	return true;
}
bool CLabDoc::ClearSurfLitoMapping(long ID_OBJ)
{
	SetSurfLitoMapping Set(&this->m_database);

	Set.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( Set.Open(CRecordset::dynaset) )
	{
		if (!Set.IsBOF()) 
		{
			Set.MoveFirst();
			while(!Set.IsEOF()) 
			{
				Set.Delete();
				Set.MoveNext();
			}
		}
	}
	return true;
}


bool CLabDoc::ClearSurfIgeMappingItem(long ID_OBJ, long ID_SURF)
{
	SetSurfIgeMapping Set(&this->m_database);

	Set.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( Set.Open(CRecordset::dynaset) )
	{
		if (!Set.IsBOF()) 
		{
			Set.MoveFirst();
			while(!Set.IsEOF()) 
			{
				Set.Delete();
				Set.MoveNext();
			}
		}
	}
	return true;
}
bool CLabDoc::ClearSurfLitoMappingItem(long ID_OBJ, long ID_SURF)
{
	SetSurfLitoMapping Set(&this->m_database);

	Set.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( Set.Open(CRecordset::dynaset) )
	{
		if (!Set.IsBOF()) 
		{
			Set.MoveFirst();
			while(!Set.IsEOF()) 
			{
				Set.Delete();
				Set.MoveNext();
			}
		}
	}
	return true;
}

void CLabDoc::AddSurfIgeMappingItem(long ID_OBJ, long ID_SURF, long ID_IGE)
{
	SetSurfIgeMapping Set(&this->m_database);

	Set.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( Set.Open(CRecordset::dynaset) )
	{
		if (!Set.IsBOF()) 
		{
			Set.MoveFirst();
			while(!Set.IsEOF()) 
			{
				Set.MoveNext();
			}
		}	
		if (Set.GetRecordCount() > 0)
		{
			if (!Set.IsBOF()) 
			{
				Set.MoveFirst();
				if(!Set.IsEOF()) 
				{
					Set.Edit();
					Set.m_ID_OBJ = ID_OBJ;
					Set.m_ID_SURF = ID_SURF;
					Set.m_ID_IGE = ID_IGE;
					Set.Update();
				}
			}
		}
		else
		{
			Set.AddNew();
			Set.m_ID_OBJ = ID_OBJ;
			Set.m_ID_SURF = ID_SURF;
			Set.m_ID_IGE = ID_IGE;
			Set.Update();
		}
	}
}
void CLabDoc::AddSurfLitoMappingItem(long ID_OBJ, long ID_SURF, long ID_IGE)
{
	SetSurfLitoMapping Set(&this->m_database);
	Set.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( Set.Open(CRecordset::dynaset) )
	{
		if (!Set.IsBOF()) 
		{
			Set.MoveFirst();
			while(!Set.IsEOF()) 
			{
				Set.MoveNext();
			}
		}	
		if (Set.GetRecordCount() > 0)
		{
			if (!Set.IsBOF()) 
			{
				Set.MoveFirst();
				if(!Set.IsEOF()) 
				{
					Set.Edit();
					Set.m_ID_OBJ = ID_OBJ;
					Set.m_ID_SURF = ID_SURF;
					Set.m_ID_IGE = ID_IGE;
					Set.Update();
				}
			}
		}
		else
		{
			Set.AddNew();
			Set.m_ID_OBJ = ID_OBJ;
			Set.m_ID_SURF = ID_SURF;
			Set.m_ID_IGE = ID_IGE;
			Set.Update();
		}
	}
}

bool CLabDoc::ClearSurfacesOrder(long ID_OBJ)
{
	SetSurfacesOrder setSurfacesOrder(&this->m_database);
	setSurfacesOrder.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( !setSurfacesOrder.Open(CRecordset::dynaset) )
        return false;
	if (!setSurfacesOrder.IsBOF()) 
	{
		setSurfacesOrder.MoveFirst();
		while(!setSurfacesOrder.IsEOF()) 
		{
			setSurfacesOrder.Delete();
			setSurfacesOrder.MoveNext();
		}
	}	
	return true;
}


bool CLabDoc::ClearSurfacesBlankOrder(long ID_OBJ)
{
	SetSurfacesBlankOrder setSurfacesBlankOrder(&this->m_database);
	setSurfacesBlankOrder.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	if ( !setSurfacesBlankOrder.Open(CRecordset::dynaset) )
        return false;
	if (!setSurfacesBlankOrder.IsBOF()) 
	{
		setSurfacesBlankOrder.MoveFirst();
		while(!setSurfacesBlankOrder.IsEOF()) 
		{
			setSurfacesBlankOrder.Delete();
			setSurfacesBlankOrder.MoveNext();
		}
	}	
	return true;
}
bool CLabDoc::ClearSurfacesOrderItem(long ID_OBJ, long ID_SURF)
{
	if (true)
	{
		SetSurfacesOrder setSurfacesOrder(&this->m_database);
		setSurfacesOrder.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setSurfacesOrder.Open(CRecordset::dynaset) )
			return false;
		if (!setSurfacesOrder.IsBOF()) 
		{
			setSurfacesOrder.MoveFirst();
			while(!setSurfacesOrder.IsEOF()) 
			{
				setSurfacesOrder.Delete();
				setSurfacesOrder.MoveNext();
			}
		}
	}
	if (true)
	{
		SetSurfacesOrder setSurfacesOrder(&this->m_database);
		setSurfacesOrder.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setSurfacesOrder.m_strSort.Format("NPP");
		if ( !setSurfacesOrder.Open(CRecordset::dynaset) )
			return false;

		long npp = 1;
		if (!setSurfacesOrder.IsBOF()) 
		{
			setSurfacesOrder.MoveFirst();
			while(!setSurfacesOrder.IsEOF()) 
			{
				setSurfacesOrder.Edit();
				setSurfacesOrder.m_NPP = npp;
				setSurfacesOrder.Update();

				setSurfacesOrder.MoveNext();
				npp++;
			}
		}	
	}
	return true;
}
bool CLabDoc::ClearSurfacesBlankOrderItem(long ID_OBJ, long ID_SURF)
{
	if (true)
	{
		SetSurfacesBlankOrder setSurfacesBlankOrder(&this->m_database);
		setSurfacesBlankOrder.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setSurfacesBlankOrder.Open(CRecordset::dynaset) )
			return false;
		if (!setSurfacesBlankOrder.IsBOF()) 
		{
			setSurfacesBlankOrder.MoveFirst();
			while(!setSurfacesBlankOrder.IsEOF()) 
			{
				setSurfacesBlankOrder.Delete();
				setSurfacesBlankOrder.MoveNext();
			}
		}	
	}
	if (true)
	{
		SetSurfacesBlankOrder setSurfacesBlankOrder(&this->m_database);
		setSurfacesBlankOrder.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setSurfacesBlankOrder.m_strSort.Format("NPP");
		if ( !setSurfacesBlankOrder.Open(CRecordset::dynaset) )
			return false;

		long npp = 1;
		if (!setSurfacesBlankOrder.IsBOF()) 
		{
			setSurfacesBlankOrder.MoveFirst();
			while(!setSurfacesBlankOrder.IsEOF()) 
			{
				setSurfacesBlankOrder.Edit();
				setSurfacesBlankOrder.m_NPP = npp;
				setSurfacesBlankOrder.Update();

				setSurfacesBlankOrder.MoveNext();
				npp++;
			}
		}	
	}
	return true;
}

bool CLabDoc::AddSurfacesOrderItem(long ID_OBJ, long NPP, BYTE check, long ID_SURF, BYTE podoshva, BYTE check2)
{
	try
	{
		SetSurfacesOrder setSurfacesOrder(&this->m_database);
		setSurfacesOrder.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setSurfacesOrder.Open(CRecordset::dynaset) )
			return false;

		setSurfacesOrder.AddNew();

		setSurfacesOrder.m_ID_OBJ = ID_OBJ;
		setSurfacesOrder.m_NPP = NPP;
		setSurfacesOrder.m_check = check;
		setSurfacesOrder.m_ID_SURF = ID_SURF;
		setSurfacesOrder.m_PODOSHVA = podoshva;
		setSurfacesOrder.m_check2 = check2;

		setSurfacesOrder.Update();
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}


	return true;
}



void CLabDoc::SurfaceBlankFunctionsList_SwapItemSurfaces(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE ID_BLANK_FUN)
{
	try
	{
		SetSurfacesBlankFunctions setSurfacesBlankFunctions(&this->m_database);
		setSurfacesBlankFunctions.m_strFilter.
			Format("ID_OBJ = %d and ID_SURF_OBJ = %d and ID_SURF_PARAM = %d and ID_BLANK_FUN = %d", 
			ID_OBJ, ID_SURF_OBJ, ID_SURF_PARAM, ID_BLANK_FUN);

		if ( setSurfacesBlankFunctions.Open(CRecordset::dynaset) )
		{
			if (!setSurfacesBlankFunctions.IsBOF()) 
			{
				setSurfacesBlankFunctions.MoveFirst();
				if(!setSurfacesBlankFunctions.IsEOF()) 
				{					
					setSurfacesBlankFunctions.Edit();
					setSurfacesBlankFunctions.m_ID_SURF_OBJ = ID_SURF_PARAM;
					setSurfacesBlankFunctions.m_ID_SURF_PARAM = ID_SURF_OBJ;
					setSurfacesBlankFunctions.Update();
				}
			}
		}		
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
	}
}
void CLabDoc::SurfaceBlankFunctionsList_SwapItemMethod(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE ID_BLANK_FUN)
{
	try
	{
		SetSurfacesBlankFunctions setSurfacesBlankFunctions(&this->m_database);
		setSurfacesBlankFunctions.m_strFilter.
			Format("ID_OBJ = %d and ID_SURF_OBJ = %d and ID_SURF_PARAM = %d and ID_BLANK_FUN = %d", 
			ID_OBJ, ID_SURF_OBJ, ID_SURF_PARAM, ID_BLANK_FUN);

		if ( setSurfacesBlankFunctions.Open(CRecordset::dynaset) )
		{
			if (!setSurfacesBlankFunctions.IsBOF()) 
			{
				setSurfacesBlankFunctions.MoveFirst();
				if(!setSurfacesBlankFunctions.IsEOF()) 
				{	
					if (ID_BLANK_FUN != 0)
					{
						BYTE id_blank_fun = ID_BLANK_FUN == 1 ? 2 : 1;
						setSurfacesBlankFunctions.Edit();
						setSurfacesBlankFunctions.m_ID_BLANK_FUN = id_blank_fun;
						setSurfacesBlankFunctions.Update();
					}
				}
			}
		}		
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
	}
}

bool CLabDoc::AddSurfacesBlankFunctionsItem(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE ID_BLANK_FUN)
{
	try
	{
		SetSurfacesBlankFunctions setSurfacesBlankFunctions(&this->m_database);
		setSurfacesBlankFunctions.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setSurfacesBlankFunctions.Open(CRecordset::dynaset) )
			return false;

		setSurfacesBlankFunctions.AddNew();
		//setSurfacesBlankFunctions.m_ID_ITEM = -1;
		setSurfacesBlankFunctions.m_ID_OBJ = ID_OBJ;
		setSurfacesBlankFunctions.m_ID_SURF_OBJ = ID_SURF_OBJ;
		setSurfacesBlankFunctions.m_ID_SURF_PARAM = ID_SURF_PARAM;
		setSurfacesBlankFunctions.m_ID_BLANK_FUN = ID_BLANK_FUN;
		setSurfacesBlankFunctions.Update();
		
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}


	return true;
}


bool CLabDoc::DeleteSurfacesBlankFunctionsItem(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE ID_BLANK_FUN)
{
	try
	{
		SetSurfacesBlankFunctions setSurfacesBlankFunctions(&this->m_database);
		setSurfacesBlankFunctions.m_strFilter.
			Format("ID_OBJ = %d and ID_SURF_OBJ = %d and ID_SURF_PARAM = %d and ID_BLANK_FUN = %d", 
			ID_OBJ, ID_SURF_OBJ, ID_SURF_PARAM, ID_BLANK_FUN);

		if ( setSurfacesBlankFunctions.Open(CRecordset::dynaset) )
		{
			if (!setSurfacesBlankFunctions.IsBOF()) 
			{
				setSurfacesBlankFunctions.MoveFirst();
				if(!setSurfacesBlankFunctions.IsEOF()) 
				{
					setSurfacesBlankFunctions.Delete();
				}
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


bool CLabDoc::AddSurfacesBlankOrderItem(long ID_OBJ, long NPP, long ID_SURF, BYTE podoshva, surface_blank_order_list_item * sboli)
{
	try
	{
		SetSurfacesBlankOrder setSurfacesBlankOrder(&this->m_database);
		setSurfacesBlankOrder.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setSurfacesBlankOrder.Open(CRecordset::dynaset) )
			return false;

		if (sboli)
		{
			setSurfacesBlankOrder.AddNew();
			setSurfacesBlankOrder.Init(ID_OBJ, NPP, sboli);
			setSurfacesBlankOrder.Update();
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


bool CLabDoc::SurfaceOrderList_UpdateChecking(long ID_OBJ, long ID_SURF, BYTE check)
{
	SetSurfacesOrder setSurfacesOrder(&this->m_database);
	setSurfacesOrder.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( !setSurfacesOrder.Open(CRecordset::dynaset) )
        return false;

	if (!setSurfacesOrder.IsBOF()) 
	{
		setSurfacesOrder.MoveFirst();
		if(!setSurfacesOrder.IsEOF()) 
		{
			setSurfacesOrder.Edit();
			setSurfacesOrder.m_check = check;
			setSurfacesOrder.Update();
		}
	}
}
bool CLabDoc::SurfaceBlankOrderList_UpdateChecking(long ID_OBJ, long ID_SURF, surface_blank_order_list_item * sboli)
{
	SetSurfacesBlankOrder setSurfacesOrder(&this->m_database);
	setSurfacesOrder.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
	if ( !setSurfacesOrder.Open(CRecordset::dynaset) )
        return false;

	if (!setSurfacesOrder.IsBOF()) 
	{
		setSurfacesOrder.MoveFirst();
		if(!setSurfacesOrder.IsEOF()) 
		{
			if (sboli)
			{
				setSurfacesOrder.Edit();
				setSurfacesOrder.InitChecks(sboli);
				setSurfacesOrder.Update();
			}
		}
	}
}
bool CLabDoc::SurfaceOrderList_MoveItemUp(long ID_OBJ, long NPP)
{
	SetSurfacesOrder setSurfacesOrder1(&this->m_database);
	setSurfacesOrder1.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP);
	if ( !setSurfacesOrder1.Open(CRecordset::dynaset) )
        return false;

	SetSurfacesOrder setSurfacesOrder2(&this->m_database);
	setSurfacesOrder2.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP-1);
	if ( !setSurfacesOrder2.Open(CRecordset::dynaset) )
        return false;

	if (!setSurfacesOrder1.IsBOF() && !setSurfacesOrder2.IsBOF()) 
	{
		setSurfacesOrder1.MoveFirst();
		setSurfacesOrder2.MoveFirst();
		if(!setSurfacesOrder1.IsEOF() && !setSurfacesOrder2.IsEOF()) 
		{
			setSurfacesOrder1.Edit();
			setSurfacesOrder1.m_NPP = NPP-1;
			setSurfacesOrder1.Update();

			setSurfacesOrder2.Edit();
			setSurfacesOrder2.m_NPP = NPP;
			setSurfacesOrder2.Update();
		}
	}	
	return false;
}
bool CLabDoc::SurfaceBlankOrderList_MoveItemUp(long ID_OBJ, long NPP)
{
	SetSurfacesBlankOrder setSurfacesOrder1(&this->m_database);
	setSurfacesOrder1.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP);
	if ( !setSurfacesOrder1.Open(CRecordset::dynaset) )
        return false;

	SetSurfacesBlankOrder setSurfacesOrder2(&this->m_database);
	setSurfacesOrder2.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP-1);
	if ( !setSurfacesOrder2.Open(CRecordset::dynaset) )
        return false;

	if (!setSurfacesOrder1.IsBOF() && !setSurfacesOrder2.IsBOF()) 
	{
		setSurfacesOrder1.MoveFirst();
		setSurfacesOrder2.MoveFirst();
		if(!setSurfacesOrder1.IsEOF() && !setSurfacesOrder2.IsEOF()) 
		{
			setSurfacesOrder1.Edit();
			setSurfacesOrder1.m_NPP = NPP-1;
			setSurfacesOrder1.Update();

			setSurfacesOrder2.Edit();
			setSurfacesOrder2.m_NPP = NPP;
			setSurfacesOrder2.Update();
		}
	}
}

bool CLabDoc::SurfaceOrderList_MoveItemDown(long ID_OBJ, long NPP)
{
	SetSurfacesOrder setSurfacesOrder1(&this->m_database);
	setSurfacesOrder1.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP);
	if ( !setSurfacesOrder1.Open(CRecordset::dynaset) )
        return false;

	SetSurfacesOrder setSurfacesOrder2(&this->m_database);
	setSurfacesOrder2.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP+1);
	if ( !setSurfacesOrder2.Open(CRecordset::dynaset) )
        return false;

	if (!setSurfacesOrder1.IsBOF() && !setSurfacesOrder2.IsBOF()) 
	{
		setSurfacesOrder1.MoveFirst();
		setSurfacesOrder2.MoveFirst();
		if(!setSurfacesOrder1.IsEOF() && !setSurfacesOrder2.IsEOF()) 
		{
			setSurfacesOrder1.Edit();
			setSurfacesOrder1.m_NPP = NPP+1;
			setSurfacesOrder1.Update();

			setSurfacesOrder2.Edit();
			setSurfacesOrder2.m_NPP = NPP;
			setSurfacesOrder2.Update();
		}
	}
}
bool CLabDoc::SurfaceBlankOrderList_MoveItemDown(long ID_OBJ, long NPP)
{
	SetSurfacesBlankOrder setSurfacesOrder1(&this->m_database);
	setSurfacesOrder1.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP);
	if ( !setSurfacesOrder1.Open(CRecordset::dynaset) )
        return false;

	SetSurfacesBlankOrder setSurfacesOrder2(&this->m_database);
	setSurfacesOrder2.m_strFilter.Format("ID_OBJ = %d and NPP = %d", ID_OBJ, NPP+1);
	if ( !setSurfacesOrder2.Open(CRecordset::dynaset) )
        return false;

	if (!setSurfacesOrder1.IsBOF() && !setSurfacesOrder2.IsBOF()) 
	{
		setSurfacesOrder1.MoveFirst();
		setSurfacesOrder2.MoveFirst();
		if(!setSurfacesOrder1.IsEOF() && !setSurfacesOrder2.IsEOF()) 
		{
			setSurfacesOrder1.Edit();
			setSurfacesOrder1.m_NPP = NPP+1;
			setSurfacesOrder1.Update();

			setSurfacesOrder2.Edit();
			setSurfacesOrder2.m_NPP = NPP;
			setSurfacesOrder2.Update();
		}
	}
}

bool CLabDoc::UnDefineCubeSize(long ID_OBJ)
{
	try
	{
		SetCubeSize setCubeSize(&this->m_database);
		setCubeSize.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setCubeSize.Open(CRecordset::dynaset) )
			return false;

		if (!setCubeSize.IsBOF()) 
		{
			setCubeSize.MoveFirst();
			while(!setCubeSize.IsEOF()) 
			{
				setCubeSize.Delete();
				setCubeSize.MoveNext();
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
bool CLabDoc::DefineZoom(long ID_OBJ, double zoomCoefXYZ, double zoomCoefXY)
{
	try
	{
		SetObject setObject(&this->m_database);
		setObject.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		bool edited = false;

		if (!setObject.IsBOF()) 
		{
			setObject.MoveFirst();
			if(!setObject.IsEOF()) 
			{
				setObject.Edit();
				setObject.m_zoomCoefXYZ = zoomCoefXYZ;
				setObject.m_zoomCoefXY = zoomCoefXY;
				setObject.Update();
				edited = true;
			}
		}
		return edited;
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
	return true;
}

bool CLabDoc::DefineCubeSize(long ID_OBJ, const CubeSize & cube_size)
{
	try
	{
		SetCubeSize setCubeSize(&this->m_database);
		setCubeSize.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setCubeSize.Open(CRecordset::dynaset) )
			return false;

		bool edited = false;

		if (!setCubeSize.IsBOF()) 
		{
			setCubeSize.MoveFirst();
			if(!setCubeSize.IsEOF()) 
			{
				setCubeSize.Edit();
				setCubeSize.Init(cube_size);
				setCubeSize.Update();
				edited = true;
			}
		}
		if(!edited)
		{
			setCubeSize.AddNew();
			setCubeSize.m_ID_OBJ = ID_OBJ;
			setCubeSize.Init(cube_size);
			setCubeSize.Update();
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
bool CLabDoc::ClearGridDataUsedAlgorothms(long ID_OBJ)
{
	try
	{
		SetGridDataUsedAlgorothms setGridDataUsedAlgorothms(&this->m_database);
		setGridDataUsedAlgorothms.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setGridDataUsedAlgorothms.Open(CRecordset::dynaset) )
			return false;

		if (!setGridDataUsedAlgorothms.IsBOF()) 
		{
			setGridDataUsedAlgorothms.MoveFirst();
			while(!setGridDataUsedAlgorothms.IsEOF()) 
			{
				setGridDataUsedAlgorothms.Delete();
				setGridDataUsedAlgorothms.MoveNext();
			}
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
}


bool CLabDoc::ClearGridDataUsedAlgorothm(long ID_OBJ, long ID_SURF)
{
	try
	{
		SetGridDataUsedAlgorothms setGridDataUsedAlgorothms(&this->m_database);
		setGridDataUsedAlgorothms.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGridDataUsedAlgorothms.Open(CRecordset::dynaset) )
			return false;

		if (!setGridDataUsedAlgorothms.IsBOF()) 
		{
			setGridDataUsedAlgorothms.MoveFirst();
			if(!setGridDataUsedAlgorothms.IsEOF()) 
			{
				setGridDataUsedAlgorothms.Delete();
			}
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
}



bool CLabDoc::DefineGridDataZflag(long ID_OBJ, long ID_SURF, short zflag)
{
	try
	{
		SetGriddataSurfaces setGriddataSurfaces(&this->m_database);
		setGriddataSurfaces.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGriddataSurfaces.Open(CRecordset::dynaset) )
			return false;

		if (!setGriddataSurfaces.IsBOF()) 
		{
			setGriddataSurfaces.MoveFirst();
			if(!setGriddataSurfaces.IsEOF()) 
			{
				setGriddataSurfaces.Edit();
				setGriddataSurfaces.m_z_flag = zflag;
				setGriddataSurfaces.Update();
			}
		}

	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
}
bool CLabDoc::DefineGridDataUsedAlgorothm(long ID_OBJ, long ID_SURF, BYTE GRIDDATA_APP, long ID_ALG)
{
	try
	{
		SetGridDataUsedAlgorothms setGridDataUsedAlgorothms(&this->m_database);
		setGridDataUsedAlgorothms.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", ID_OBJ, ID_SURF);
		if ( !setGridDataUsedAlgorothms.Open(CRecordset::dynaset) )
			return false;

		bool edited = false;

		if (!setGridDataUsedAlgorothms.IsBOF()) 
		{
			setGridDataUsedAlgorothms.MoveFirst();
			if(!setGridDataUsedAlgorothms.IsEOF()) 
			{
				setGridDataUsedAlgorothms.Edit();

				setGridDataUsedAlgorothms.m_ID_OBJ = ID_OBJ;
				setGridDataUsedAlgorothms.m_ID_SURF = ID_SURF;
				setGridDataUsedAlgorothms.m_USE_SURFER = GRIDDATA_APP;
				setGridDataUsedAlgorothms.m_ID_ALG = ID_ALG;

				setGridDataUsedAlgorothms.Update();
				edited = true;
			}
		}
		if(!edited)
		{
			setGridDataUsedAlgorothms.AddNew();
			setGridDataUsedAlgorothms.m_ID_OBJ = ID_OBJ;
			setGridDataUsedAlgorothms.m_ID_SURF = ID_SURF;
			setGridDataUsedAlgorothms.m_USE_SURFER = GRIDDATA_APP;
			setGridDataUsedAlgorothms.m_ID_ALG = ID_ALG;
			setGridDataUsedAlgorothms.Update();
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
}
	
void CLabDoc::LabNumberResetting(vector<lab_numbers_reset_item> lab_numbers_reset_items)
{
	if (this->dll_w_project)
	{
		this->dll_w_project->LabNumberResetting(lab_numbers_reset_items);
	}
}

long CLabDoc::AddNewRozriz(long ID_OBJ, CString NOMER, CString fn_dxf, 
						   bool m_acad_yscale_loaded,
						   double z1w, double y1a, double z2w, double y2a,
						   bool dxf_x_defined, vector<double> * v_xProfile, 
						   vector<long> v_ID_KT)
{
	SetRozrizy setRozrizy(&this->m_database);
	setRozrizy.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setRozrizy.m_strSort.Format("");
	if ( !setRozrizy.Open(CRecordset::dynaset) )
		return -1;	

	long ID_ROZRIZ = setRozrizy.GetNewKeyID();
	if (m_acad_yscale_loaded)
	{
		if (dxf_x_defined)
			setRozrizy.AddNewRow(ID_OBJ, ID_ROZRIZ, NOMER, fn_dxf, z1w, y1a, z2w, y2a);
		else
			setRozrizy.AddNewRow(ID_OBJ, ID_ROZRIZ, NOMER, z1w, y1a, z2w, y2a);
	}
	else
	{
		if (dxf_x_defined)
			setRozrizy.AddNewRow(ID_OBJ, ID_ROZRIZ, NOMER, fn_dxf);
		else
			setRozrizy.AddNewRow(ID_OBJ, ID_ROZRIZ, NOMER);
	}

	SetRozriz setRozriz(&this->m_database);
	setRozriz.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", 
		ID_OBJ, ID_ROZRIZ);
	setRozriz.m_strSort.Format("");
	if ( setRozriz.Open(CRecordset::dynaset) )
	{
		vector<long>::iterator it = v_ID_KT.begin();
		long i = 0;
		for( ;it != v_ID_KT.end(); it++, i++)
		{
			long NPP = i + 1;
			long ID_KT = (*it);

			if (ID_KT < 0) 
				continue;

			if (dxf_x_defined && v_xProfile && i < v_xProfile->size())
			{
				double dxf_x = v_xProfile->operator [](i);
				setRozriz.AddNewRow(ID_OBJ, ID_ROZRIZ, NPP, ID_KT, dxf_x);
			}
			else
				setRozriz.AddNewRow(ID_OBJ, ID_ROZRIZ, NPP, ID_KT);
		}
	}


	return ID_ROZRIZ;
}


void CLabDoc::DeleteRozriz(long ID_OBJ, long ID_ROZRIZ)
{
	SetRozrizy setRozrizy(&this->m_database);
	setRozrizy.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", 
		ID_OBJ, ID_ROZRIZ);
	setRozrizy.m_strSort.Format("");
	if ( setRozrizy.Open(CRecordset::dynaset) )
	{
		if (!setRozrizy.IsBOF()) 
		{
			setRozrizy.MoveFirst();
			while(!setRozrizy.IsEOF()) 
			{
				setRozrizy.Delete();
				setRozrizy.MoveNext();
			}
		}
	}

	SetRozriz setRozriz(&this->m_database);
	setRozriz.m_strFilter.Format("ID_OBJ = %d and ID_ROZRIZ = %d", 
		ID_OBJ, ID_ROZRIZ);
	setRozriz.m_strSort.Format("");
	if ( setRozriz.Open(CRecordset::dynaset) )
	{
		if (!setRozriz.IsBOF()) 
		{
			setRozriz.MoveFirst();
			while(!setRozriz.IsEOF()) 
			{
				setRozriz.Delete();
				setRozriz.MoveNext();
			}
		}
	}
}

void CLabDoc::GridDataSurfacesSetPodoshva(long ID_OBJ, long ID_SURF, BYTE podoshva)
{
	SetGriddataSurfaces setGriddataSurfaces(&this->m_database);
	setGriddataSurfaces.m_strFilter.Format("ID_OBJ = %d and ID_SURF = %d", 
		ID_OBJ, ID_SURF);
	setGriddataSurfaces.m_strSort.Format("");
	if ( setGriddataSurfaces.Open(CRecordset::dynaset) )
	{
		if (!setGriddataSurfaces.IsBOF()) 
		{
			setGriddataSurfaces.MoveFirst();
			if(!setGriddataSurfaces.IsEOF()) 
			{
				setGriddataSurfaces.Edit();
				setGriddataSurfaces.m_PODOSHVA = podoshva;
				setGriddataSurfaces.Update();
			}
		}
	}
}
