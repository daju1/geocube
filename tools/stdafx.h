// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here
#if defined (_MSC_VER) && !defined (QT_PROJECT)
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <cderr.h>
#include <commdlg.h>
#include <commctrl.h>
#else
#include <stdio.h>
#include <mywindows.h>
#endif
#include <vector>
#include <string>
using namespace std;

#define PATH_STRING_SIZE 1024

#if defined( _UNICODE) || defined (UNICODE)
#define stprintf_s _snwprintf
#else
#define stprintf_s sprintf_s
#endif