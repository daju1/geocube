// GLPrintMan.h: interface for the CGLPrintMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CUBIC_ZSTAMP_POSTPROCESSOR_GLPRINT_MAN)
#define CUBIC_ZSTAMP_POSTPROCESSOR_GLPRINT_MAN

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glman.h"

class  CGLPrintMan  
: public CGLMan
{
public:
	bool toReDraw;
	bool toDisableOpenGL;
	bool toEnableOpenGL;
	// prepare bitmap
	BITMAPINFO m_BitmapInfo;
	void* m_pBitmapBuffer; // buffer to store bitmap (RGB, RGB , RGB etc..)

	HBITMAP m_hDib; // bitmap handle

	void SaveBitmap2(char* name);
	void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC );
	void EnableOpenGL(RECT paper, HWND hWnd, HDC * hDC, HGLRC * hRC );
	CGLPrintMan();
	virtual ~CGLPrintMan();

};

#endif // !defined(AFX_GLPRINTMAN_H__1A10666F_8144_4CBE_811A_2B71FD6443A9__INCLUDED_)
