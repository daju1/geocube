// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <math.h>

// TODO: reference additional headers your program requires here

#include <vector>
#include <string>
using namespace std;

#define USE_GRINVICH_TIME


#ifdef USE_GRINVICH_TIME
#define GetTime GetSystemTime
#else
#define GetTime GetLocalTime
#endif
