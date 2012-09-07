// geocube.cpp : Defines the entry point for the console application.
//


#if 1

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "stdafx.h"
#include "../geocube_module/geocube_module.h"


#include <iostream>

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
//			AfxMessageBox(IDP_OLE_INIT_FAILED);
			return FALSE;
		}

		COleTemplateServer::RegisterAll();
		COleObjectFactory::UpdateRegistryAll();
		CoInitialize(NULL);

		// TODO: code your application's behavior here.
//		CString strHello;
//		strHello.LoadString(IDS_HELLO);
//		cout << (LPCTSTR)strHello << endl;

		hInst = AfxGetInstanceHandle();

		dll_WinSurf();

		CoUninitialize();

	}

	return nRetCode;
}

#else
int main(int argc, char* argv[])
{
	printf("Hello World! %d\n", fnGeocube_module());
	dll_WinSurf();
	return 0;
}
#endif
