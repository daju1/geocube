// excel_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "resource.h"
#include "MyDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;


#define TRACE              printf


HINSTANCE hInst;								// current instance

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// Initialize OLE libraries
		if (!AfxOleInit())
		{
			AfxMessageBox(IDP_OLE_INIT_FAILED);
			return FALSE;
		}

		COleTemplateServer::RegisterAll();
		COleObjectFactory::UpdateRegistryAll();
		CoInitialize(NULL);

		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;

		hInst = AfxGetInstanceHandle();

	//	OnSomeAction();

		MyDlg * dlg = new MyDlg(true);

		CoUninitialize();

	}

	return nRetCode;
}


