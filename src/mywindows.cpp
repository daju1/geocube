#include <mywindows.h>

HANDLE GetProcessHeap()
{
    return NULL;
}

LPVOID HeapAlloc(HANDLE, DWORD /*dwFlags*/, size_t dwBytes)
{
    return malloc(dwBytes);
}

BOOL HeapFree(HANDLE, DWORD /*dwFlags*/, LPVOID lpMem)
{
    free(lpMem);
    return TRUE;
}
#include <QDir>

#ifdef _UNICODE
BOOL CreateDirectoryW(
  LPCWSTR                lpPathName,
  void *  //LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
{
    QDir().mkdir(QStringW(lpPathName));
    return TRUE;
}
BOOL DeleteFileW(
  LPCWSTR lpFileName
)
{
    QFile file (lpFileName);
    file.remove();
    return TRUE;
}
#define CreateDirectory CreateDirectoryW
#define DeleteFile DeleteFileW
#else
BOOL CreateDirectoryA(
  LPCSTR                lpPathName,
  void *   //LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
{
    QDir().mkdir(QString(lpPathName));
    return TRUE;
}

BOOL DeleteFileA(
  LPCSTR lpFileName
)
{
    QFile file (lpFileName);
    file.remove();
    return TRUE;
}
#define CreateDirectory CreateDirectoryA
#define DeleteFile DeleteFileA
#endif

#define _LDBL_RADIX 2

int sprintf_s(char* buffer, size_t sizeOfBuffer, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsnprintf(buffer, sizeOfBuffer, format, ap);
    va_end(ap);
    return result;
}



#include <qmessagebox.h>
int MessageBox(void* /*hwnd*/, const char * title, const char * msg, int /*flags*/)
{
    QMessageBox mb(QMessageBox::Information, title, msg,  QMessageBox::Ok | QMessageBox::Cancel);
    if(mb.exec() == QMessageBox::Ok)
    {

    }
    return 0;
}

int AfxMessageBox(const char * msg )
{
    QMessageBox mb(QMessageBox::Information, "", msg,  QMessageBox::Ok);
    mb.exec();
    return 0;
}
