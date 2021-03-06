// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <windows.h>
#include <commctrl.h>
#include "tchar.h"
#else
#include <stdarg.h>
#include <stdio.h>
#include "mywindows.h"
#endif


#include <stdio.h>
#include <math.h>
#include <algorithm>

#include <iostream>
#include <vector>
#include <string>
using namespace std ;

#if defined( _UNICODE) || defined (UNICODE)
#define stprintf_s _snwprintf
#else
#define stprintf_s sprintf_s
#endif
