// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(COMMON_INCLUDED_)
#define COMMON_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <commctrl.h>
#define RGBA(r,g,b,a)   ( (((DWORD)(BYTE)(a))<<24) | RGB(r,g,b))


#endif // !defined(COMMON_INCLUDED_)
