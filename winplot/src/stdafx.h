// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;


#include <stdio.h>
#include <commdlg.h>
#include <commctrl.h>


#include <vector>
#include <string>
using namespace std ;



#include "../../resource.h"

#define SCALE_FLAG_LEFT				0
#define SCALE_FLAG_RIGHT			1
#define SCALE_FLAG_COMMON			2
#define SCALE_FLAG_RGB				3
