// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here
#ifdef _MSC_VER
#include <windows.h>
#include <commctrl.h>
#include "tchar.h"
#else
#include <stdarg.h>
#include <stdio.h>
#include "mywindows.h"
inline int sprintf_s(char* buffer, size_t sizeOfBuffer, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsnprintf(buffer, sizeOfBuffer, format, ap);
    va_end(ap);
    return result;
}

template<size_t sizeOfBuffer>
inline int sprintf_s(char (&buffer)[sizeOfBuffer], const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsnprintf(buffer, sizeOfBuffer, format, ap);
    va_end(ap);
    return result;
}

#include <qmessagebox.h>
int MessageBox(void* hwnd, const char * title, const char * msg, int)
{
    QMessageBox mb(QMessageBox::Information, title, msg,  QMessageBox::Ok | QMessageBox::Cancel);
    if(mb.exec() == QMessageBox::Ok)
    {

    }
}
#endif

#ifdef _UNICODE
#define stprintf_s _snwprintf_s
#else
#define stprintf_s sprintf_s
#endif

#include <stdio.h>
#include <math.h>
#include <algorithm>

#include <iostream>
#include <vector>
#include <string>
using namespace std ;
