#ifndef _MY_WINDOWS_H_
#define _MY_WINDOWS_H_

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>

// https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-dtyp/efda8314-6e41-4837-8299-38ba0ee04b92
// https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types

typedef int BOOL, *PBOOL, *LPBOOL;
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char BYTE, *PBYTE, *LPBYTE;
typedef BYTE BOOLEAN, *PBOOLEAN;
typedef char CHAR, *PCHAR;


typedef double DOUBLE;
typedef unsigned long DWORD, *PDWORD, *LPDWORD;
typedef void* HANDLE;


typedef uint64_t ULONGLONG;
typedef uint64_t ULONG64;
typedef uint64_t UINT64;
typedef uint64_t QWORD;


typedef unsigned short WORD, *PWORD, *LPWORD;
typedef unsigned short USHORT;

typedef void VOID, *PVOID, *LPVOID;
typedef const void* LPCVOID;


//typedef wchar_t UNICODE;

typedef unsigned int ULONG32;



typedef long LONG, *PLONG, *LPLONG;
typedef unsigned long ULONG, *PULONG;


typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;
typedef unsigned int UINT;
typedef unsigned char UCHAR, *PUCHAR;
typedef UCHAR* STRING;

typedef short SHORT;
typedef void* RPC_BINDING_HANDLE;



typedef LONG HRESULT;

typedef wchar_t WCHAR, *PWCHAR;
typedef const char* LPCSTR;
typedef const wchar_t* LPCWSTR;
typedef char* PSTR, *LPSTR;
typedef wchar_t* LPWSTR, *PWSTR;
#if !defined (_MSC_VER) && !defined (__MINGW32__)
typedef HANDLE HWND;
typedef HANDLE HDC;
typedef HANDLE HINSTANCE;
#endif

#define FAR

typedef struct tagPALETTEENTRY {
  BYTE peRed;
  BYTE peGreen;
  BYTE peBlue;
  BYTE peFlags;
} PALETTEENTRY;

typedef struct tagLOGPALETTE {
  WORD         palVersion;
  WORD         palNumEntries;
  PALETTEENTRY palPalEntry[1];
} LOGPALETTE, *PLOGPALETTE, *NPLOGPALETTE, *LPLOGPALETTE;

#define LF_FACESIZE 32

typedef struct tagLOGFONTA {
  LONG lfHeight;
  LONG lfWidth;
  LONG lfEscapement;
  LONG lfOrientation;
  LONG lfWeight;
  BYTE lfItalic;
  BYTE lfUnderline;
  BYTE lfStrikeOut;
  BYTE lfCharSet;
  BYTE lfOutPrecision;
  BYTE lfClipPrecision;
  BYTE lfQuality;
  BYTE lfPitchAndFamily;
  CHAR lfFaceName[LF_FACESIZE];
} LOGFONTA, *PLOGFONTA, *NPLOGFONTA, *LPLOGFONTA;

typedef struct tagLOGFONTW {
  LONG  lfHeight;
  LONG  lfWidth;
  LONG  lfEscapement;
  LONG  lfOrientation;
  LONG  lfWeight;
  BYTE  lfItalic;
  BYTE  lfUnderline;
  BYTE  lfStrikeOut;
  BYTE  lfCharSet;
  BYTE  lfOutPrecision;
  BYTE  lfClipPrecision;
  BYTE  lfQuality;
  BYTE  lfPitchAndFamily;
  WCHAR lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW, *NPLOGFONTW, *LPLOGFONTW;
#if 0
//#ifdef _UNICODE
        #define _T(x)      L ## x
        #define LPTSTR LPWSTR
        #define LPCTSTR LPCWSTR
        #define LOGFONT LOGFONTW
        #define TCHAR WCHAR
//#define __TEXT(q) L##q
#define __TEXT(q) q
//#else /* _UNICODE */
#endif
        #define _T(x)      x
        #define LPTSTR LPSTR
        #define LPCTSTR LPCSTR
        #define LOGFONT LOGFONTA
        #define TCHAR CHAR
#define __TEXT(q) q
//#endif /* _UNICODE */


//#if defined( _UNICODE) || defined (UNICODE)
//#define stprintf_s _snwprintf
//#else
#define stprintf_s sprintf_s
//#endif

typedef TCHAR *PTCHAR;
#define TEXT(q) __TEXT(q)

/* Types use for passing & returning polymorphic values */
typedef UINT WPARAM;
typedef LONG LPARAM;
typedef LONG LRESULT;

typedef DWORD COLORREF;
typedef DWORD* LPCOLORREF;

typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

typedef struct tagSIZE {
  LONG cx;
  LONG cy;
} SIZE, *PSIZE, *LPSIZE;

typedef struct tagRECT {
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

//#define CALLBACK __stdcall

#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

#define GENERIC_READ 1
#define GENERIC_WRITE 2

#define MB_OK               0x00000000L
#define MB_OKCANCEL         0x00000001L
#define MB_ABORTRETRYIGNORE 0x00000002L
#define MB_YESNOCANCEL      0x00000003L
#define MB_YESNO            0x00000004L
#define MB_RETRYCANCEL      0x00000005L

#define MB_ICONEXCLAMATION  0x00000030L
#define MB_ICONINFORMATION  0x00000040L

#define S_OK        ((HRESULT)0L)
#define S_FALSE     ((HRESULT)1L)

#define  FILE_BEGIN   0
#define  FILE_CURRENT 1
#define  FILE_END     2

#define  HEAP_ZERO_MEMORY 0x00000008

#define IDOK     1
#define IDCANCEL 2
#define IDABORT  3
#define IDRETRY  4
#define IDIGNORE 5
#define IDYES    6
#define IDNO     7


HANDLE GetProcessHeap();

LPVOID HeapAlloc(HANDLE, DWORD /*dwFlags*/, size_t dwBytes);

BOOL HeapFree(HANDLE, DWORD /*dwFlags*/, LPVOID lpMem);
;

/*#ifdef _UNICODE
BOOL CreateDirectoryW(
  LPCWSTR                lpPathName,
  void *  //LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
BOOL DeleteFileW(
  LPCWSTR lpFileName
);
#define CreateDirectory CreateDirectoryW
#define DeleteFile DeleteFileW
#else*/
BOOL CreateDirectoryA(
  LPCSTR                lpPathName,
  void *   //LPSECURITY_ATTRIBUTES lpSecurityAttributes
);

BOOL DeleteFileA(
  LPCSTR lpFileName
);
#define CreateDirectory CreateDirectoryA
#define DeleteFile DeleteFileA
//#endif

#ifndef _LDBL_RADIX
#define _LDBL_RADIX 2
#endif
#if !defined (_MSC_VER) && !defined (__MINGW32__)
int sprintf_s(char* buffer, size_t sizeOfBuffer, const char* format, ...);
#if 0
template<size_t sizeOfBuffer>
inline int sprintf_s(char (&buffer)[sizeOfBuffer], const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsnprintf(buffer, sizeOfBuffer, format, ap);
    va_end(ap);
    return result;
}
#endif
#endif

#include <qmessagebox.h>
int MessageBox(void* /*hwnd*/, const char * title, const char * msg, int /*flags*/);

int AfxMessageBox(const char * msg );

#define WINGDIAPI 
#define APIENTRY
// From gl.h
/*
 * Datatypes
 */
typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void		GLvoid;
typedef signed char	GLbyte;		/* 1-byte signed */
typedef short		GLshort;	/* 2-byte signed */
typedef int		GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int		GLsizei;	/* 4-byte signed */
typedef float		GLfloat;	/* single precision float */
typedef float		GLclampf;	/* single precision float in [0,1] */
typedef double		GLdouble;	/* double precision float */
typedef double		GLclampd;	/* double precision float in [0,1] */

/* Polygons */
#define GL_POINT				0x1B00
#define GL_LINE					0x1B01
#define GL_FILL					0x1B02

#endif //_MY_WINDOWS_H_





