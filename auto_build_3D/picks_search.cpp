// picks_search.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "stdafx.h"
#include "../tools/src/readfile.h"
#include "../tools/src/filedlg.h"
#include "../winplot/src/winplot.h"

#include "./../array/src/LocalExtremumsFiltering.h"

#include "picks_search.h"
#include "./../surfdoc/src/AutoBuildProfileDlg.h"

extern char szPath[];
extern char directory[];
extern char dir_out[1024];
HINSTANCE hInst;

int _tmain(int argc, _TCHAR* argv[])
{
	hInst = GetModuleHandle(NULL);

#if 0
	return AutoBuildProfile_main(true, NULL);
#else
	AutoBuildProfile::auto_build_parametrs_Init();
	AutoBuildProfileDlg * abpd = new AutoBuildProfileDlg(true, NULL, AutoBuildProfile::ab);		// ...right after the dialog is closed?
	if (abpd != NULL) delete abpd;		// how to safely release the memory...
#endif

}
