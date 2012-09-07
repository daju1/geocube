// excel_test_win32_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../excel_test/resource.h"
#include "../excel_test/MyDialog.h"

#include <iostream>
using namespace std;

HINSTANCE hInst;

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
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
	return 0;
}

