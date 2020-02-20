#pragma once
#ifdef _MSC_VER
#include <windows.h>
#endif



#define XBITMAP3 16
#define YBITMAP3 24

#define USE_LISTVIEW_STANDART 1
#define _ListViewTab_ ListViewTab 
#include "ListViewTab_h.h"
#pragma warning (disable:4005)

#define USE_LISTVIEW_STANDART 0
#define  _ListViewTab_ ListViewTab2
#include "ListViewTab_h.h"
#pragma warning (default:4005)
