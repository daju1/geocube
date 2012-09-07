// lab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "lab.h"


#include "MainFrm.h"

#include "ChildFrm.h"

#include "laboratoryDoc.h"
#include "engeologyDoc.h"

#include "laboratoryView.h"
#include "EnGeologyView.h"

#include "EnGeoFrame.h"
#include "3DFrame.h"
#include "3DDoc.h"
#include "3DView.h"


#include "TableFrm.h"
#include "TableDoc.h"
#include "TableView.h"

#include <map>
using namespace std;
#include "../../laboratory/src/lab.h"

#include "../../tools/src/errorexit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool RegisterLabViewPropertyWindowClass(int type);

HINSTANCE hInst;

/////////////////////////////////////////////////////////////////////////////
// CLabApp

BEGIN_MESSAGE_MAP(CLabApp, CWinApp)
	//{{AFX_MSG_MAP(CLabApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabApp construction

CLabApp::CLabApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLabApp object
CLabApp theApp;
// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {6BA2EE4C-3D87-442B-A459-59CFB8F2A162}
static const CLSID clsid =
{ 0x6ba2ee4c, 0x3d87, 0x442b, { 0xa4, 0x59, 0x59, 0xcf, 0xb8, 0xf2, 0xa1, 0x62 } };

/////////////////////////////////////////////////////////////////////////////
// CLabApp initialization
void Registry()
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

	switch(dwDisposition)
	{
	case REG_CREATED_NEW_KEY:
		toRegSetValue = true;
		break;
	case REG_OPENED_EXISTING_KEY:
		toRegSetValue = false;
		break;
	}

	char strDatabase[4096];
	char strConnect[4096];
	char baseExcelFormsDir[4096];
	char exportDatabaseTemplate[4096];
	char laboratoryFormsDir[4096];

	sprintf(strDatabase, "\0");
	sprintf(strConnect, "\0");
	sprintf(baseExcelFormsDir, "\0");
	sprintf(exportDatabaseTemplate, "\0");
	sprintf(laboratoryFormsDir, "\0");

		
	printf("toRegSetValue = %d\n", toRegSetValue);

	if(toRegSetValue)
	{
		// Присвоить значение
		//..................................
		if ( lResult == ERROR_SUCCESS )
		{
			sprintf(strDatabase, "%s\0", CLabDoc::s_strDatabase);
			sprintf(strConnect, "%s\0", CLabDoc::s_strConnect);
			sprintf(baseExcelFormsDir, "%s\0", BaseExcel::s_xl_forms_dir.c_str());
			sprintf(exportDatabaseTemplate, "%s\0", CLabDoc::s_strExportDatabaseTemplate);
			sprintf(laboratoryFormsDir, "%s\0", Laboratory::FormsDir.c_str());


#if 0
			lResult = RegSetValue( hKeyResult, "DestFileBD", REG_SZ, strDatabase, DWORD(strlen(strDatabase)));
			lResult = RegSetValue( hKeyResult, "ConnectString", REG_SZ,	strConnect, DWORD(strlen(strConnect)));
			lResult = RegSetValue( hKeyResult, "ExcelForms", REG_SZ, baseExcelFormsDir, DWORD(strlen(baseExcelFormsDir)));
			lResult = RegSetValue( hKeyResult, "ExportTemplate", REG_SZ, exportDatabaseTemplate, DWORD(strlen(exportDatabaseTemplate)));
			lResult = RegSetValue( hKeyResult, "LaboratoryFormsDir", REG_SZ, laboratoryFormsDir, DWORD(strlen(laboratoryFormsDir)));
#else
			lResult = RegSetValueEx( hKeyResult, "DestFileBD", 0, REG_SZ,
				(const BYTE *)strDatabase, DWORD(strlen(strDatabase))+1);
			lResult = RegSetValueEx( hKeyResult, "ConnectString", 0, REG_SZ,
				(const BYTE *)strConnect, DWORD(strlen(strConnect))+1);
			lResult = RegSetValueEx( hKeyResult, "ExcelForms", 0, REG_SZ,
				(const BYTE *)baseExcelFormsDir, DWORD(strlen(baseExcelFormsDir))+1);
			lResult = RegSetValueEx( hKeyResult, "ExportTemplate", 0, REG_SZ,
				(const BYTE *)exportDatabaseTemplate, DWORD(strlen(exportDatabaseTemplate))+1);
			lResult = RegSetValueEx( hKeyResult, "LaboratoryFormsDir", 0, REG_SZ,
				(const BYTE *)laboratoryFormsDir, DWORD(strlen(laboratoryFormsDir))+1);
#endif
			


			RegCloseKey( hKeyResult );
		}
	}
	else
	{
		if ( lResult == ERROR_SUCCESS )
		{

            
#if 0
			LONG dwBytes;           

			// Выбрать значение
			//........................
			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValue( hKeyResult, "DestFileBD", strDatabase, &dwBytes ))
			{
				CLabApp::s_strDatabase = strDatabase;
			}
			else
				MessageBox(0, strDatabase, "CLabApp::s_strDatabase", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValue( hKeyResult, "ConnectString", strConnect, &dwBytes ))	
			{
				CLabDoc::s_strConnect = strConnect;
			}
			else
				MessageBox(0, strConnect, "CLabDoc::s_strConnect", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValue( hKeyResult, "ExcelForms", baseExcelFormsDir, &dwBytes ))	
			{
				BaseExcel::s_xl_forms_dir = baseExcelFormsDir;
			}
			else
				MessageBox(0, baseExcelFormsDir, "BaseExcel::s_xl_forms_dir", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValue( hKeyResult, "ExportTemplate", exportDatabaseTemplate, &dwBytes ))	
			{
				CLabApp::s_strExportDatabaseTemplate = exportDatabaseTemplate;
			}
			else
				MessageBox(0, exportDatabaseTemplate, "CLabApp::s_strExportDatabaseTemplate", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValue( hKeyResult, "LaboratoryFormsDir", laboratoryFormsDir, &dwBytes ))	
			{
				Laboratory::FormsDir = laboratoryFormsDir;
			}	
			else
				MessageBox(0, laboratoryFormsDir, "Laboratory::FormsDir", 0);
#else
			DWORD dwType;
			DWORD dwBytes;           
			// Выбрать значение
			//........................
			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValueEx( hKeyResult, "DestFileBD", 0, &dwType,
				(BYTE *)strDatabase, &dwBytes ))
			{
				CLabDoc::s_strDatabase = strDatabase;
			}
			else
				MessageBox(0, strDatabase, "CLabApp::s_strDatabase", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValueEx( hKeyResult, "ConnectString", 0, &dwType,
				(BYTE *)strConnect, &dwBytes ))	
			{
				CLabDoc::s_strConnect = strConnect;
			}
			else
				MessageBox(0, strConnect, "CLabDoc::s_strConnect", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValueEx( hKeyResult, "ExcelForms", 0, &dwType,
				(BYTE *)baseExcelFormsDir, &dwBytes ))	
			{
				BaseExcel::s_xl_forms_dir = baseExcelFormsDir;
			}
			else
				MessageBox(0, baseExcelFormsDir, "BaseExcel::s_xl_forms_dir", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValueEx( hKeyResult, "ExportTemplate", 0, &dwType,
				(BYTE *)exportDatabaseTemplate, &dwBytes ))	
			{
				CLabDoc::s_strExportDatabaseTemplate = exportDatabaseTemplate;
			}
			else
				MessageBox(0, exportDatabaseTemplate, "CLabApp::s_strExportDatabaseTemplate", 0);

			dwBytes = 4096;
			if (ERROR_SUCCESS == RegQueryValueEx( hKeyResult, "LaboratoryFormsDir", 0, &dwType,
				(BYTE *)laboratoryFormsDir, &dwBytes ))	
			{
				Laboratory::FormsDir = laboratoryFormsDir;
			}	
			else
				MessageBox(0, laboratoryFormsDir, "Laboratory::FormsDir", 0);
#endif
			RegCloseKey( hKeyResult );
		}
	}
}
void RegistryODBCConnectString();
void RegistryODBCDatabaseName();

BOOL CLabApp::InitInstance()
{
		
	Registry();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_LABTYPE,
		RUNTIME_CLASS(CLaboratoryDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLaboratoryView));
	AddDocTemplate(pDocTemplate);
	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);



	CMultiDocTemplate* pDocTemplateEG;
	pDocTemplateEG = new CMultiDocTemplate(
#if 1
		IDR_GEOTYPE,
#else
		IDR_3DTYPE,
#endif
		RUNTIME_CLASS(CEnGeologyDoc),
		RUNTIME_CLASS(CEnGeologyFrame), // custom MDI child frame
		RUNTIME_CLASS(CEnGeologyView));
	AddDocTemplate(pDocTemplateEG);
	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplateEG, FALSE);

#if 1

	CMultiDocTemplate* pDocTemplate3D;
	pDocTemplate3D = new CMultiDocTemplate(
		IDR_3DTYPE,
		RUNTIME_CLASS(C3DDoc),
		RUNTIME_CLASS(C3DFrame), // custom MDI child frame
		RUNTIME_CLASS(C3DView));
	AddDocTemplate(pDocTemplate3D);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate3D, FALSE);




	CMultiDocTemplate* pDocTemplateTab;
	pDocTemplateTab = new CMultiDocTemplate(
		IDR_TABLETYPE,
		RUNTIME_CLASS(CTableDoc),
		RUNTIME_CLASS(CTableFrame), // custom MDI child frame
		RUNTIME_CLASS(CTableView));
	AddDocTemplate(pDocTemplateTab);

	m_server.ConnectTemplate(clsid, pDocTemplateTab, FALSE);

#endif


	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	//pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	hInst = this->m_hInstance;

	RegisterLabViewPropertyWindowClass(1);
	RegisterLabViewPropertyWindowClass(2);




	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLabApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLabApp message handlers

