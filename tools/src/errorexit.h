
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#else
#include <mywindows.h>
#endif
void ErrorExit(const char * lpszFunction, bool toExitProcess = false);
void LastErrorExit(DWORD dwLastError, LPCTSTR lpszFunction, bool toExitProcess = false);
void ErrorPrint(LPCTSTR lpszFunction);
