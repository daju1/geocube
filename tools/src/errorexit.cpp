#include "../StdAfx.h"
#include "errorexit.h"
#if defined (_MSC_VER)
void ErrorExit(LPTSTR lpszFunction, bool toExitProcess) 
{
#define BUF_LEN 200
    TCHAR szBuf[BUF_LEN]; 
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    stprintf_s(szBuf, BUF_LEN,
        _T("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
 
    MessageBox(NULL, szBuf, _T("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
	if(toExitProcess)
		ExitProcess(dw); 
}


void ErrorPrint(LPTSTR lpszFunction) 
{ 
    TCHAR szBuf[BUF_LEN]; 
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    stprintf_s(szBuf, BUF_LEN,
		_T("Error: %s failed with error %d: %s\n"), 
        lpszFunction, dw, lpMsgBuf); 
 
    printf(szBuf); 

    LocalFree(lpMsgBuf);

}

void ErrorExit(DWORD dwLastError, LPTSTR lpszFunction, bool toExitProcess) 
{ 
    TCHAR szBuf[BUF_LEN]; 
    LPVOID lpMsgBuf;
    

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dwLastError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    sprintf_s(szBuf, BUF_LEN,
        "%s failed with error %d: %s", 
        lpszFunction, dwLastError, lpMsgBuf); 
 
    MessageBox(NULL, szBuf, "Error", MB_OK); 

    LocalFree(lpMsgBuf);
	if(toExitProcess)
		ExitProcess(dwLastError); 
}
#else
void ErrorExit(LPTSTR lpszFunction, bool toExitProcess)
{
}


void ErrorPrint(LPTSTR lpszFunction)
{
}

void ErrorExit(DWORD dwLastError, LPTSTR lpszFunction, bool toExitProcess)
{
}
#endif
