#include <mywindows.h>
void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false) ;
void ErrorExit(DWORD dwLastError, LPTSTR lpszFunction, bool toExitProcess = false);
void ErrorPrint(LPTSTR lpszFunction);
