
#if defined (_MSC_VER) && !defined (QT_PROJECT)
#else
#include <mywindows.h>
#endif
void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false) ;
void ErrorExit(DWORD dwLastError, LPTSTR lpszFunction, bool toExitProcess = false);
void ErrorPrint(LPTSTR lpszFunction);
