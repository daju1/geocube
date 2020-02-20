// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <stdio.h>
#ifdef _MSC_VER
#include <io.h>
#include <cderr.h>
#include <commdlg.h>
#include <commctrl.h>
#endif
#include <vector>
#include <string>
using namespace std ;

#define PATH_STRING_SIZE 1024
