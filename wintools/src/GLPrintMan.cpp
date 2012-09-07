// GLPrintMan.cpp: implementation of the CGLPrintMan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLPrintMan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLPrintMan::CGLPrintMan()
{
	toReDraw			= true;
	toDisableOpenGL		= true;
	toEnableOpenGL		= true;

	m_hDib=NULL; // device independent bitmap
	m_pBitmapBuffer=NULL; // set up memory pointer
}


CGLPrintMan::~CGLPrintMan()
{

}


void CGLPrintMan::EnableOpenGL(RECT paper, HWND hWnd, HDC * hDC, HGLRC * hRC )
{
	if (toEnableOpenGL){
	try {
	// prepare bitmap
	m_pBitmapBuffer=NULL; // buffer to store bitmap (RGB, RGB , RGB etc..)

	// First of all, initialize the bitmap header information...
	memset(&m_BitmapInfo, 0, sizeof(BITMAPINFO));
	m_BitmapInfo.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
	m_BitmapInfo.bmiHeader.biWidth		= paper.right - paper.left;
	m_BitmapInfo.bmiHeader.biHeight		= paper.bottom - paper.top;
	m_BitmapInfo.bmiHeader.biPlanes		= 1;
	m_BitmapInfo.bmiHeader.biBitCount		= 32;
	m_BitmapInfo.bmiHeader.biCompression	= BI_RGB;
	m_BitmapInfo.bmiHeader.biSizeImage	=	
		m_BitmapInfo.bmiHeader.biWidth * 
		m_BitmapInfo.bmiHeader.biHeight * 
		m_BitmapInfo.bmiHeader.biBitCount / 8;

	//m_BitmapInfo.bmiColors - not defined ???

	// create Device Independent Bitmap (containing full RGB information regardless of graphic system)
	HDC hTmpDC;
	hTmpDC=::GetDC(hWnd);
	m_hDib= CreateDIBSection(hTmpDC, &m_BitmapInfo, DIB_RGB_COLORS, &m_pBitmapBuffer, NULL, (DWORD) 0);
	::ReleaseDC(hWnd, hTmpDC);
	// now, we got bitmap to draw , buffer is pBitmapBuffer

	// create memory device context
	*hDC=CreateCompatibleDC( GetDC(hWnd));
	if (*hDC==NULL) throw "CreateCompatibleDC: Error";
	
	// connect memeory device context with bitmap
	if (SelectObject(*hDC, m_hDib)==NULL) throw "SelectObject: Error" ;


	// now, we got bitmap and corresponding device context


	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_STEREO_DONTCARE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat( *hDC, &pfd );
	SetPixelFormat( *hDC, iFormat, &pfd );

	// create and enable the render context (RC)
	*hRC = wglCreateContext( *hDC );
	// wglMakeCurrent( *hDC, *hRC ); -> removed as not right used 
	// this used right in StartUpdate()

	int error=glGetError();

	}
	catch (char* error) {
		MessageBox(0, error, "EnableOpenGL",MB_OK | MB_ICONEXCLAMATION);
	}
	}

}


VOID CGLPrintMan::DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
	if (toDisableOpenGL)
	{
		//if (m_pBitmapBuffer) delete m_pBitmapBuffer;
		if (m_pBitmapBuffer) HeapFree(GetProcessHeap(), 0, m_pBitmapBuffer);

		DeleteObject(m_hDib); // delete DIB
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( hRC );
		ReleaseDC( hWnd, hDC );
	}  
}


//  save OpenGL back buffer to the disk directly
void CGLPrintMan::SaveBitmap2(char* name) 
{
	int i;

	char* buffer=(char*)m_pBitmapBuffer;   
	int width=m_BitmapInfo.bmiHeader.biWidth; 
	int height=m_BitmapInfo.bmiHeader.biHeight; 
	int size=m_BitmapInfo.bmiHeader.biSizeImage;

	//  write to disk

	FILE* file=fopen(name, "wb");
	if (file==NULL) throw "Cannot open file to save bitmap!";

	//  write header
	BITMAPFILEHEADER	hdr; //  file header
	//  set up file header
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	//  is always "BM"
	hdr.bfSize		=  sizeof( hdr ) + sizeof(m_BitmapInfo.bmiHeader) + size;
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + m_BitmapInfo.bmiHeader.biSize );

	//  write to disk
	fwrite(&hdr, sizeof(hdr), 1, file); //  file header
	fwrite(&m_BitmapInfo.bmiHeader, sizeof(m_BitmapInfo.bmiHeader), 1, file); //  info header

	//  write body

	for (i=0;i<size;i++)
	fputc(buffer[i], file);
	fclose(file);
}
