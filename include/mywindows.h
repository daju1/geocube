//#ifdef _MY_WINDOWS_H_
//#define _MY_WINDOWS_H_

#pragma once

#include <stdint.h>

// https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-dtyp/efda8314-6e41-4837-8299-38ba0ee04b92
// https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types

typedef int BOOL, *PBOOL, *LPBOOL;
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


typedef wchar_t UNICODE;

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

typedef HANDLE HWND;
typedef HANDLE HDC;




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

#ifdef _UNICODE
        #define _T(x)      L ## x
        #define LPTSTR LPWSTR
        #define LPCTSTR LPCWSTR
        #define LOGFONT LOGFONTW
        #define TCHAR WCHAR
//#define __TEXT(q) L##q
#define __TEXT(q) q
#else /* _UNICODE */
        #define _T(x)      x
        #define LPTSTR LPSTR
        #define LPCTSTR LPCSTR
        #define LOGFONT LOGFONTA
        #define TCHAR CHAR
#define __TEXT(q) L
#endif /* _UNICODE */

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

//#endif //_MY_WINDOWS_H_





