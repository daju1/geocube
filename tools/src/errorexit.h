
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#else
#include <mywindows.h>
#endif
void ErrorExit(LPCTSTR lpszFunction, bool toExitProcess = false) ;
void ErrorExit(DWORD dwLastError, LPCTSTR lpszFunction, bool toExitProcess = false);
void ErrorPrint(LPCTSTR lpszFunction);
