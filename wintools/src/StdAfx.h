#define VIEW_ONLY_VERSION 0


//#if !defined(COMMON_INCLUDED_)
//#define COMMON_INCLUDED_

//#define _WIN32_WINNT 0x0501



#include <windows.h>

//#define USE_PICK_FILTER
#pragma warning (disable:4786)
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std ;

#pragma warning( disable : 4250 )

// TODO: reference additional headers your program requires here
#define USE_MEMORY_TRACK 0
#if USE_MEMORY_TRACK

#ifdef _DEBUG
#include "memory_track.h"
#endif

#ifdef _DEBUG
#define DEBUG_NEW new(__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

#else //USE_MEMORY_TRACK
#define DEBUG_NEW new
#endif //USE_MEMORY_TRACK

#define new DEBUG_NEW

#define USE_GRINVICH_TIME


#ifdef USE_GRINVICH_TIME
#define GetTime GetSystemTime
#else
#define GetTime GetLocalTime
#endif


#define NEW_VECT_COMMON_PARAMS

#define USE_REALTIME_HANDLING
#undef USE_REALTIME_HANDLING

//#define DRAW_TO_META_FILE
//#define DRAW_TO_WINDOW
#define DRAW_WITH_MEM_TO_WINDOW

#ifdef DRAW_TO_META_FILE
#undef DRAW_TO_WINDOW
#undef DRAW_WITH_MEM_TO_WINDOW
#endif

#ifdef DRAW_TO_WINDOW
#undef DRAW_WITH_MEM_TO_WINDOW
#endif

#define HSCROLL_LENGTH 17280

#define USE_OWN_DC
//#define EXTERN_FONTS_AND_PENS
#define DRAW_SCALE_FAST_X_MAXMIN
#define DRAW_LINE_SIMPLE_LINEAR

//#define DRAW_OLD_VECTOR_VDPOINTS
#undef DRAW_OLD_VECTOR_VDPOINTS

//#define USE_EARTHQUAKES_ON_SURF


#define USE_WAVELETS
#undef USE_WAVELETS


#define WM_MOUSEWHEEL                   0x020A

#define RGBA(r,g,b,a)   ( (((DWORD)(BYTE)(a))<<24) | RGB(r,g,b))



#define SCALE_FLAG_LEFT				0
#define SCALE_FLAG_RIGHT			1
#define SCALE_FLAG_COMMON			2
#define SCALE_FLAG_RGB				3

#define GRID_POFILE_DIRECTION_NORTH 0
#define GRID_POFILE_DIRECTION_EAST	1
/*
typedef struct
{
	bool bIncludeX;
	bool bIncludeY;
	bool bIncludeZ;
	bool bPrinterNameFound;
	short dmCopies;
	short dmOrientation;
	short dmPaperSize;
	char  szPrinterName[32];
} PRINTDLGDATA, *LPPRINTDLGDATA;

*/
#define VECTITEM_IN_TWO_FILES 0
#define VECT_IN_TWO_FILES 0

#define PATH_STRING_SIZE 1024

#define TRACE NULL

#define SLOW_PREVIEW 0


//#include "generic.h"

#include <math.h>
#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <commctrl.h>

#include "..\resource.h"

//#endif
