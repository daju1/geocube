// GraphsView.cpp : implementation of the CGraphsView class
//

#include "StdAfx.h"
#include "GraphsView.h"
#include "raporto.h"

#include "GraphsDoc.h"
#include "GraphsView.h"
#include "XYZBuffer.h"
#include "Graph.h"
#include "../../tools/src/errorexit.h"

#ifdef COMMON_RAPORT
extern void WriteRaportoB(LPCTSTR s);
#else
extern void WriteRaportoA(LPCTSTR file, LPCTSTR s);
#endif
//extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);

extern bool g_btoDisplayWavelet;

#define DRAW_TIME_FOR_WAIT 0
/////////////////////////////////////////////////////////////////////////////
// CGraphsView construction/destruction

CGraphsView::CGraphsView()
{
}

CGraphsView::~CGraphsView()
{
	if( hMemDC  )
		DeleteDC( hMemDC );
	if( hBitmap )
		DeleteObject( hBitmap );
	if( hMetaFile )
		DeleteEnhMetaFile(hMetaFile);
#ifdef EXTERN_FONTS_AND_PENS
	if(m_linePen) 
		DeleteObject(m_linePen);
	if(m_boxPen) 
		DeleteObject(m_boxPen);
	if(m_gridPen) 
		DeleteObject(m_gridPen);
	if(m_hTitleFont) 
		DeleteObject(m_hTitleFont);
	if(m_hFont) 
		DeleteObject(m_hFont);
	if(m_hPrintTitleFont) 
		DeleteObject(m_hPrintTitleFont);
	if(m_hPrintFont) 
		DeleteObject(m_hPrintFont);
#endif
}

void CGraphsView::OnCreate(int iDoc, CGraphsDoc* pDoc)
{
WriteRaporto("CGraphsView::OnCreate\n");
	m_pDocument = pDoc;
	m_iDoc = iDoc;

//	bBitmapCreated = false;
	hMemDC = NULL;
	hBitmap = NULL;

	if (iDoc < 3)
		m_bRight = true;
	else
		m_bRight = false;


	m_iFirst = 0;
	m_iLast = 0;
	//m_Len = m_pDocument->m_T.Length();

	m_shift_yb = 75+45;
	m_scale_y = m_shift_yb - 45;
	m_shift_ya = m_shift_yb/2+10;

	m_SizeTotal.cx = 50;
	m_SizeTotal_cy = m_shift_yb+10+10;
	m_SizeTotal.cy = (long)m_SizeTotal_cy;


	m_nCurVertPos = 0;
	m_nCurHorzPos = 0;



	// событие - "Ready" - сигнальное
	m_hEventDrawReady = CreateEvent( NULL, TRUE, TRUE, "DrawReadyEvent" );
	hMetaFile = NULL;


//	m_TotalRect.left = 0;
//	m_TotalRect.top = 0;
//	m_TotalRect.right = m_SizeTotal.cx;
//	m_TotalRect.bottom = m_SizeTotal.cy;
#ifdef EXTERN_FONTS_AND_PENS
		//======= Создаем шрифт для оцифровки осей
	m_hFont = CreateFont(12,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	if(!m_hFont){
ErrorExit("CreateFont", false);
		return;
	}
	//======= Создаем шрифт для оцифровки осей
	m_hPrintFont = CreateFont(36,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	if(!m_hPrintFont)
	{
ErrorExit("CreateFont", false);
		DeleteObject(m_hFont);
		return;
	}
	//======= Создаем шрифт для вывода заголовка
	m_hTitleFont = CreateFont(15,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	if(!m_hTitleFont)
	{
ErrorExit("CreateFont", false);
		DeleteObject(m_hFont);
		DeleteObject(m_hPrintFont);
		return;
	}
	//======= Создаем шрифт для вывода заголовка
	m_hPrintTitleFont = CreateFont(150,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	if(!m_hPrintTitleFont)
	{
ErrorExit("CreateFont", false);

		DeleteObject(m_hTitleFont);
		DeleteObject(m_hFont);
		DeleteObject(m_hPrintFont);
		return;
	}

	//====== Создаем черное перо для изображения рамки
	HPEN m_boxPen = CreatePen(PS_SOLID, 0, COLORREF(0));
	if(!m_boxPen)
	{
ErrorExit("CreatePen", false);
		DeleteObject(m_hTitleFont);
		DeleteObject(m_hFont);
		DeleteObject(m_hPrintTitleFont);
		DeleteObject(m_hPrintFont);
		return;
	}
	HPEN m_gridPen = CreatePen(PS_SOLID, 0, RGB(92,200,178));
	if(!m_gridPen)
	{
ErrorExit("CreatePen", false);
		DeleteObject(m_boxPen);
		DeleteObject(m_hTitleFont);
		DeleteObject(m_hFont);
		DeleteObject(m_hPrintTitleFont);
		DeleteObject(m_hPrintFont);
		return;
	}
	HPEN m_linePen = CreatePen(PS_SOLID, 1, RGB(255,100,0));
	if(!m_linePen)
	{
ErrorExit("CreatePen", false);
		DeleteObject(m_gridPen);
		DeleteObject(m_boxPen);
		DeleteObject(m_hTitleFont);
		DeleteObject(m_hFont);
		DeleteObject(m_hPrintTitleFont);
		DeleteObject(m_hPrintFont);
		return;
	}
#endif
	SetEvent(m_hEventDrawReady);
WriteRaporto("CGraphsView::OnCreate End\n");

}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView drawing

void CGraphsView::DrawToMetaFile(HWND hWnd)
{
WriteRaporto("DrawToMetaFile 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                DrawToMetaFile return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);


	HDC  hMetaDC;
	HDC  hRefDC;
	RECT rect;
	int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
	int  iMMPerPelX, iMMPerPelY;

	hRefDC = GetDC( hWnd );

	// Вычислить размер клиентской области в единицах 
	// длины 0,01 мм.
	//................................................
	iWidthMM    = GetDeviceCaps(hRefDC, HORZSIZE);
	iHeightMM   = GetDeviceCaps(hRefDC, VERTSIZE);
	iWidthPels  = GetDeviceCaps(hRefDC, HORZRES);
	iHeightPels = GetDeviceCaps(hRefDC, VERTRES);

	iMMPerPelX = (iWidthMM * 100)/iWidthPels;
	iMMPerPelY = (iHeightMM * 100)/iHeightPels;

	GetClientRect(hWnd, &rect);

	RECT rectM;
	rectM.top = 0;
	rectM.left = 0;

	rectM.right = rect.right * iMMPerPelX;
	rectM.bottom = rect.bottom * iMMPerPelY;

	// Создать расширенный метафайл.
	//.............................

	hMetaDC = CreateEnhMetaFile( hRefDC, NULL, &rectM,
							  "Test Metafile" );
	if ( hMetaDC )
	{
		Draw(hMetaDC,rect);

		if(hMetaFile)
		{
			DeleteEnhMetaFile(hMetaFile);
		}

		hMetaFile = CloseEnhMetaFile( hMetaDC );
	}
	else
		ErrorExit("CreateEnhMetaFile",false);
	ReleaseDC(hWnd, hMetaDC);
#ifndef USE_OWN_DC
	ReleaseDC(hWnd, hRefDC);
#endif
	InvalidateRect(hWnd,NULL,TRUE);

	UpdateWindow(hWnd);

	SetEvent(m_hEventDrawReady);

WriteRaporto("DrawToMetaFile end\n");

}
void CGraphsView::DrawToMetaFile2(HWND hWnd)
{
WriteRaporto("DrawToMetaFile 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                DrawToMetaFile return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);


	HDC  hMetaDC;
	HDC  hRefDC;
	RECT rect;
	int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
	int  iMMPerPelX, iMMPerPelY;

	hRefDC = GetDC( hWnd );

	// Вычислить размер клиентской области в единицах 
	// длины 0,01 мм.
	//................................................
	iWidthMM    = GetDeviceCaps(hRefDC, HORZSIZE);
	iHeightMM   = GetDeviceCaps(hRefDC, VERTSIZE);
	iWidthPels  = GetDeviceCaps(hRefDC, HORZRES);
	iHeightPels = GetDeviceCaps(hRefDC, VERTRES);

	iMMPerPelX = (iWidthMM * 100)/iWidthPels;
	iMMPerPelY = (iHeightMM * 100)/iHeightPels;

	GetClientRect(hWnd, &rect);
	//rect.top = 0;
	//rect.left = 0;
	//rect.right = m_SizeTotal.cx;
	rect.bottom = m_SizeTotal.cy;


	RECT rectM;
	rectM.top = 0;
	rectM.left = 0;

	rectM.right = rect.right * iMMPerPelX;
	rectM.bottom = rect.bottom * iMMPerPelY;

	// Создать расширенный метафайл.
	//.............................
	hMetaDC = CreateEnhMetaFile( hRefDC, NULL, &rectM,
							  "Test Metafile" );
	if ( hMetaDC )
	{
		Draw(hMetaDC,rect);

		if(hMetaFile)
		{
			DeleteEnhMetaFile(hMetaFile);
		}

		hMetaFile = CloseEnhMetaFile( hMetaDC );
	}
	else
		ErrorExit("CreateEnhMetaFile",false);
	ReleaseDC(hWnd, hMetaDC);
#ifndef USE_OWN_DC
	ReleaseDC(hWnd, hRefDC);
#endif
	InvalidateRect(hWnd,NULL,TRUE);
	UpdateWindow(hWnd);

	SetEvent(m_hEventDrawReady);

}

void CGraphsView::DrawToWindow(HWND hWnd, bool toInvalidate)
{
WriteRaporto("DrawToWindow 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
if (wt != WAIT_OBJECT_0)
WriteRaporto("                                wt != WAIT_OBJECT_0\n" );
if (wt == WAIT_TIMEOUT)
WriteRaporto("                                wt == WAIT_TIMEOUT\n" );
WriteRaporto("                                DrawToWindow return 1\n" );

		return;
	}
	ResetEvent(m_hEventDrawReady);
	RECT rect;

	GetClientRect(hWnd, &rect);

	if(toInvalidate)
		InvalidateRect(hWnd,&rect,TRUE);

	HDC  hDC = GetDC( hWnd );

	Draw(hDC,rect);

#ifndef USE_OWN_DC
	ReleaseDC(hWnd, hDC);
#endif

	UpdateWindow(hWnd);
	SetEvent(m_hEventDrawReady);
}

void CGraphsView::DrawWithMemToWindow(HWND hWnd)
{
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                DrawWithMemToWindow return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);
	HDC  hDC = GetDC( hWnd );
	if (hDC == NULL)
	{
		ErrorExit("GetDC");
		SetEvent(m_hEventDrawReady);
		return;
	}

	RECT rect;
	GetClientRect(hWnd, &rect);
	bool toSelectObject = false;
	// Создать совместимый контекст устройства.
	//........................
	if (!hMemDC)
	{
		hMemDC = CreateCompatibleDC( hDC );
		if (hMemDC == NULL)
		{
			ErrorExit("CreateCompatibleDC");
			SetEvent(m_hEventDrawReady);
			return;
		}
		else
			toSelectObject = true;
	}

	if(!hBitmap)
	{

		// Создать совместимое растровое изображение.
		//............................
		hBitmap = CreateCompatibleBitmap( hDC, rect.right, m_SizeTotal.cy );
		if (hBitmap == NULL)
		{
			ErrorExit("CreateCompatibleBitmap");
			SetEvent(m_hEventDrawReady);
			return;
		}
		else
			toSelectObject = true;

		bmWidth		= rect.right;
		bmHeight	= m_SizeTotal.cy;
		//bBitmapCreated = true;

	}
	else
	{
		if (bmWidth != rect.right || bmHeight != m_SizeTotal.cy)
		{
			if (!DeleteObject( hBitmap ))
			{
				ErrorExit("DeleteObject");
				SetEvent(m_hEventDrawReady);
				return;
			}
			// Создать совместимое растровое изображение.
			//............................
			hBitmap = CreateCompatibleBitmap( hDC, rect.right, m_SizeTotal.cy);
			if (hBitmap == NULL)
			{
				ErrorExit("CreateCompatibleBitmap2");
				SetEvent(m_hEventDrawReady);
				return;
			}
			else
				toSelectObject = true;

			bmWidth		= rect.right;
			bmHeight	= m_SizeTotal.cy;

		}
	}
	if (toSelectObject)
	{
		// Выбрать растровое изображение для совместимого
		// контекста устройства и начертить на нем
		// графический объект.
		//..............................
		SelectObject( hMemDC, hBitmap );
	}
	Rectangle( hMemDC, 0, 0, rect.right, m_SizeTotal.cy);



	Draw(hMemDC,rect);

	GetClientRect( hWnd, &rect );
	if(!BitBlt(hDC, 0/*rect.left*/, 0/*rect.top*/,
		rect.right, rect.bottom,
		hMemDC, 0, 0, SRCCOPY))
		ErrorExit("BitBlt");
#ifndef USE_OWN_DC
	ReleaseDC(hWnd, hDC);
#endif

	SetEvent(m_hEventDrawReady);
}

VOID CGraphsView::VScroll( HWND hWnd, WORD wScroll )
{
WriteRaporto("VScroll 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                VScroll return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);
   SCROLLINFO si;

   // Использовать функцию GetScrollInfo() для получения информации о 	
   // линейке прокрутки.
   //.......................................
   si.cbSize = sizeof( SCROLLINFO );
//   si.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS;
   si.fMask  = SIF_ALL;
   GetScrollInfo( hWnd, SB_VERT, &si );
   RECT cltRect;
   GetClientRect( hWnd, &cltRect );

   bool isTrack = false;
   int delta;

   switch( wScroll )
   {
      case SB_LINEDOWN :
              if ( m_nCurVertPos <= (int)(si.nMax - si.nPage) )
                 m_nCurVertPos += 
				 (int)(si.nMax - si.nPage) - m_nCurVertPos < cltRect.bottom/20 ?
				 (int)(si.nMax - si.nPage) - m_nCurVertPos : cltRect.bottom/20;

              break;

      case SB_LINEUP :
              if ( m_nCurVertPos > 0 )
                 m_nCurVertPos -= 
				 cltRect.bottom/20 <= m_nCurVertPos
				 ? cltRect.bottom/20 : m_nCurVertPos;
              break;

      case SB_PAGEDOWN :
              if ( m_nCurVertPos <= (int)(si.nMax - si.nPage) )
                 m_nCurVertPos += 
				 (int)(si.nMax - si.nPage) - m_nCurVertPos < cltRect.bottom ?
				 (int)(si.nMax - si.nPage) - m_nCurVertPos : cltRect.bottom;

              break;

      case SB_PAGEUP :
              if ( m_nCurVertPos > 0 )
                 m_nCurVertPos -= cltRect.bottom <= m_nCurVertPos
				 ? cltRect.bottom : m_nCurVertPos;
              break;

      case SB_THUMBTRACK :
		  m_nCurVertPos -= si.nPos - si.nTrackPos;
              break;
   }
   bool toDraw = false;

   if (si.nPos != m_nCurVertPos )
   {
	  toDraw = true;
	  delta = (si.nPos-m_nCurVertPos);


//	  m_TotalRect.top -= delta;
//	  m_TotalRect.bottom -= delta;
	  
#ifndef DRAW_WITH_MEM_TO_WINDOW
	  m_shift_ya += delta;
#endif
      si.nPos  = m_nCurVertPos;
		si.nMin   = 0;
		si.nMax   = m_SizeTotal.cy - 1;
		si.nPage  = cltRect.bottom;

      HDC  hDC  = GetDC( hWnd );
//	  RECT rectUpdate;
  //    ScrollDC( hDC, 0, delta, NULL, &cltRect,
    //            NULL, &rectUpdate );
#ifdef DRAW_WITH_MEM_TO_WINDOW

	if(!BitBlt( hDC, 
		 0, 0, cltRect.right, cltRect.bottom,
              hMemDC, 0, m_nCurVertPos, SRCCOPY ))
			  ErrorExit("BitBlt - VSCroll");
#endif
//	BitBlt( hDC, 
//		rectUpdate.left, rectUpdate.top, 
//		rectUpdate.right - rectUpdate.left, 
//		rectUpdate.bottom - rectUpdate.top,
  //            hMemDC, 0, m_nCurVertPos + rectUpdate.top  , SRCCOPY );
#ifdef DO_RAPORT

char str[255];
sprintf(str,
		"m_SizeTotal.cy=%d m_nCurVertPos=%d m_shift_ya=%f m_shift_yb=%f m_scale_y=%f rect.bottom=%d\n",
		 m_SizeTotal.cy, m_nCurVertPos, m_shift_ya, m_shift_yb, m_scale_y, cltRect.bottom);
WriteRaporto(str);

#endif
      SetScrollInfo( hWnd, SB_VERT, &si, TRUE );
   }
	SetEvent(m_hEventDrawReady);
	if(toDraw)
	{

#ifdef DRAW_TO_META_FILE
	  DrawToMetaFile(hWnd);
#else

#ifdef DRAW_TO_WINDOW
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd,&rect,TRUE);
#else
#ifdef DRAW_WITH_MEM_TO_WINDOW
//	  DrawWithMemToWindow(hWnd);
#endif
#endif
#endif
	}
WriteRaporto("VScroll end\n");
}


VOID CGraphsView::HScroll( HWND hWnd, WORD wScroll )
{
WriteRaporto("HScroll 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                HScroll return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);

	SCROLLINFO si;

   // Использовать функцию GetScrollInfo() для получения информации о 	
   // линейке прокрутки.
   //.......................................
   si.cbSize = sizeof( SCROLLINFO );
//   si.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS;
   si.fMask  = SIF_ALL;
   GetScrollInfo( hWnd, SB_HORZ, &si );
   RECT cltRect;
   GetClientRect( hWnd, &cltRect );

   bool isTrack = false;
   int delta;

   int pageStep = int(double(int(si.nPage))*0.8);
   if (pageStep<1)
	   pageStep=1;
   int lineStep = pageStep/10;
   if (lineStep<1)
	   lineStep=1;

   switch( wScroll )
   {
      case SB_LINERIGHT :
              if ( m_nCurHorzPos <= (int)(si.nMax - si.nPage) )
                 m_nCurHorzPos += 
				 (int)(si.nMax - si.nPage) - m_nCurHorzPos + 1 < lineStep ?
				 (int)(si.nMax - si.nPage) - m_nCurHorzPos + 1 : lineStep;

              break;

      case SB_LINELEFT :
              if ( m_nCurHorzPos > 0 )
                 m_nCurHorzPos -= 
				 lineStep < m_nCurHorzPos
				 ? lineStep : m_nCurHorzPos;
              break;

      case SB_PAGERIGHT :
              if ( m_nCurHorzPos <= (int)(si.nMax - si.nPage) )
                 m_nCurHorzPos += 
				 (int)(si.nMax - si.nPage) - m_nCurHorzPos + 1  < pageStep ?
				 (int)(si.nMax - si.nPage) - m_nCurHorzPos + 1 : pageStep;

              break;

      case SB_PAGELEFT :
              if ( m_nCurHorzPos > 0 )
                 m_nCurHorzPos -= 
				 pageStep <= m_nCurHorzPos ? 
				 pageStep : m_nCurHorzPos;
              break;

      case SB_THUMBTRACK :
		  m_nCurHorzPos -= si.nPos - si.nTrackPos;
              break;
   }
   bool toDraw = false;

   if (si.nPos != m_nCurHorzPos )
   {
	   toDraw = true;
	  delta = (si.nPos-m_nCurHorzPos);


	  
	  m_iFirst -= delta;
	  m_iLast += delta;

/*	  if (m_nCurHorzPos == 0)
		  m_iFirst = 0;
	  if (int(si.nMax - si.nPage) - m_nCurHorzPos == 0)
		  m_iLast  = 0;*/

        si.nPos  = m_nCurHorzPos;
		si.nMin   = 0;
		si.nMax   = HSCROLL_LENGTH - 1;
		si.nPage  = HSCROLL_LENGTH - (m_iFirst + m_iLast);

		SetScrollInfo( hWnd, SB_HORZ, &si, TRUE );
#ifdef DO_RAPORT
		/*
char ss[200];
sprintf(ss,
		"m_iFirst = %d m_iLast = %d m_iFirst + m_iLast = %d\n ",
		m_iFirst, m_iLast, m_iFirst + m_iLast);
WriteRaporto(ss);
sprintf(ss,
		"si.nPos = %d si.nPage = %d m_nCurHorzPos = %d si.nMin = %d si.nMax = %d\n ",
		si.nPos, si.nPage, m_nCurHorzPos, si.nMin, si.nMax);
WriteRaporto(ss);*/
#endif
   }
	SetEvent(m_hEventDrawReady);
	if(toDraw)
	{

#ifdef DRAW_TO_META_FILE
	  DrawToMetaFile(hWnd);
#else

#ifdef DRAW_TO_WINDOW
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd,&rect,TRUE);
#else
#ifdef DRAW_WITH_MEM_TO_WINDOW
	  DrawWithMemToWindow(hWnd);
#endif
#endif
#endif
	}
WriteRaporto("HScroll end\n");
}

void CGraphsView::VerticalZoom(HWND hWnd, int zDelta, bool isButton)
{
WriteRaporto("MouseWheel 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                MouseWheel return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);

	double prod;
	if (zDelta < 0)
	{
		if (isButton)
			prod = 1.02;
		else
			prod = 1.05; 
	}
	else
	{
		if (isButton)
			prod = 1./1.02;
		else
		prod = 1./1.05; 
	}

	double delta_shift_yb = -m_shift_yb;

	m_shift_yb *= prod;
	delta_shift_yb += m_shift_yb;
//	int nGraphs = 1 + m_pDocument->m_vPoints.vectSize();
	int nGraphs = 
#ifdef DRAW_VECTOR_VPOINTS1
		1 + 
#endif
		m_pDocument->m_vPoints.vectCheckedSize();


	m_SizeTotal_cy = m_shift_yb * nGraphs+10+10;
	m_SizeTotal.cy = (long)m_SizeTotal_cy;
	m_scale_y = m_shift_yb - 45;

	RECT rect;
	GetClientRect(hWnd, &rect);

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;

	GetScrollInfo( hWnd, SB_VERT, &si );

	double pos_part = (double)m_nCurVertPos / (double)si.nMax;
	si.nMin   = 0;
	si.nMax   = m_SizeTotal.cy - 1;
	si.nPage  = rect.bottom;

//	int delta = (si.nPos-m_nCurVertPos);
	m_nCurVertPos = int(pos_part * (double)si.nMax);

	if (m_nCurVertPos > si.nMax)
		m_nCurVertPos = si.nMax;


//	m_TotalRect.top -= delta;
//	m_TotalRect.bottom -= delta;

//	m_shift_ya += delta;


	si.nPos   = m_nCurVertPos;

#ifndef DRAW_WITH_MEM_TO_WINDOW
	m_shift_ya = m_shift_yb/2+10-si.nPos; // координата центра нулевого графика
#endif
	SetScrollInfo( hWnd, SB_VERT, &si , TRUE);


	SetEvent(m_hEventDrawReady);
#ifdef DRAW_TO_META_FILE
	  DrawToMetaFile(hWnd);
#else

#ifdef DRAW_TO_WINDOW
	InvalidateRect(hWnd,&rect,TRUE);
#else
#ifdef DRAW_WITH_MEM_TO_WINDOW
	  DrawWithMemToWindow(hWnd);
#endif
#endif
#endif
WriteRaporto("MouseWheel end\n");

}
void CGraphsView::HorizontalZoom(HWND hWnd, int zDelta)
{
WriteRaporto("HorizontalZoom 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                HorizontalZoom return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);

	/*double prod = 0.05;
	int currlen = HSCROLL_LENGTH-m_iFirst-m_iLast;
	if (currlen < int(2/prod))
		currlen = int(2/prod);


	int plus = int(double(currlen) * prod);*/


	/*char s[50];
	wsprintf(s, "%d", plus);
		MessageBox(0, s, "", 0);*/

	int plus = HSCROLL_LENGTH/10;


	if (zDelta < 0)
	{
		if (HSCROLL_LENGTH-m_iFirst-m_iLast <= 2*plus)
			plus = (HSCROLL_LENGTH-m_iFirst-m_iLast)/2;

		if (m_bRight)
			m_iFirst += plus;
		else
			m_iLast  += plus;
	}
	else
	{
		if (m_bRight)
			m_iFirst -= plus;
		else
			m_iLast  -= plus;
	}


	if (m_iFirst < 0)
		m_iFirst = 0;
	if (m_iLast < 0)
		m_iLast = 0;

/*	if (HSCROLL_LENGTH-m_iFirst-m_iLast < 1)
	{
		int corr = HSCROLL_LENGTH-m_iFirst-m_iLast - 1;

		if(m_iFirst>m_iLast)
			m_iFirst += corr;
		else
			m_iLast += corr;
	}*/


	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;

	GetScrollInfo( hWnd, SB_HORZ, &si );

	m_nCurHorzPos = m_iFirst;

	if (m_nCurHorzPos > int(si.nMax))
		m_iFirst = m_nCurHorzPos = int(si.nMax);

	si.nMin   = 0;
	si.nMax   = HSCROLL_LENGTH - 1;
	si.nPos   = m_nCurHorzPos;
	si.nPage  = HSCROLL_LENGTH - (m_iFirst + m_iLast);



	SetScrollInfo( hWnd, SB_HORZ, &si , TRUE);
#ifdef DO_RAPORT
/*char ss[200];
sprintf(ss,
		"m_iFirst = %d m_iLast = %d m_iFirst + m_iLast = %d\n ",
		m_iFirst, m_iLast, m_iFirst + m_iLast);
WriteRaporto(ss);
sprintf(ss,
		"si.nPos = %d si.nPage = %d m_nCurHorzPos = %d si.nMin = %d si.nMax = %d\n ",
		si.nPos, si.nPage, m_nCurHorzPos, si.nMin, si.nMax);
WriteRaporto(ss);*/
#endif

	SetEvent(m_hEventDrawReady);
#ifdef DRAW_TO_META_FILE
	  DrawToMetaFile(hWnd);
#else

#ifdef DRAW_TO_WINDOW
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd,&rect,TRUE);
#else
#ifdef DRAW_WITH_MEM_TO_WINDOW
	  DrawWithMemToWindow(hWnd);
#endif
#endif
#endif
WriteRaporto("HorizontalZoom end\n");

}

void CGraphsView::OnRButtonDown(HWND hWnd, unsigned short xPos, unsigned short yPos)
{
WriteRaporto("OnRButtonDown 1\n");
	m_yPos = yPos;
	m_xPos = xPos;
WriteRaporto("OnRButtonDown end\n");
}

void CGraphsView::OnLButtonDown(HWND hWnd, unsigned short xPos, unsigned short yPos)
{
WriteRaporto("OnLButtonDown 1\n");
	m_yPos = yPos;
	m_xPos = xPos;
WriteRaporto("OnLButtonDown end\n");
}

void CGraphsView::OnLButtonDownMouseMove(HWND hWnd, unsigned short xPos, unsigned short yPos)
{
WriteRaporto("OnLButtonDownMouseMove 1\n");
	int xDelta = int(m_xPos) - int(xPos);
	if (m_bRight)
		xDelta *= -1;
	HorizontalZoom(hWnd, xDelta);
	m_yPos = yPos;
	m_xPos = xPos;
WriteRaporto("OnLButtonDownMouseMove end\n");
}
void CGraphsView::OnRButtonDownMouseMove(HWND hWnd, unsigned short xPos, unsigned short yPos)
{
WriteRaporto("OnRButtonDownMouseMove 1\n");
	int yDelta = int(yPos) - int(m_yPos);

	VerticalZoom(hWnd, -yDelta, true);
	m_yPos = yPos;
	m_xPos = xPos;
WriteRaporto("OnRButtonDownMouseMove end\n");
}

void CGraphsView::SetFullZoom(HWND hWnd)
{
WriteRaporto("SetFullZoom 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		DRAW_TIME_FOR_WAIT);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                SetFullZoom return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);

	m_iFirst = 0;
	m_iLast = 0;

	{
		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_ALL;

		GetScrollInfo( hWnd, SB_HORZ, &si );

		si.nMin   = 0;
		si.nMax   = HSCROLL_LENGTH - 1;
		si.nPos   = m_nCurHorzPos;
		si.nPage  = HSCROLL_LENGTH - (m_iFirst + m_iLast);

		m_nCurHorzPos = m_iFirst;

		if (m_nCurHorzPos > int(si.nMax))
			m_nCurHorzPos = si.nMax;


		SetScrollInfo( hWnd, SB_HORZ, &si , TRUE);
	}
	SetEvent(m_hEventDrawReady);
#ifdef DRAW_TO_META_FILE
	  DrawToMetaFile(hWnd);
#else

#ifdef DRAW_TO_WINDOW
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd,&rect,TRUE);
#else
#ifdef DRAW_WITH_MEM_TO_WINDOW
	  DrawWithMemToWindow(hWnd);
#endif
#endif
#endif
WriteRaporto("SetFullZoom end\n");
}

void CGraphsView::DrawToPrinter(HDC hDC)
{
	RECT rect;
	Draw(hDC,rect);
}

void CGraphsView::OnResizeGraphsCount(HWND hWnd)
{
WriteRaporto("OnResizeGraphsCount 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		INFINITE/*DRAW_TIME_FOR_WAIT*/);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
if (wt != WAIT_OBJECT_0)
WriteRaporto("                                wt != WAIT_OBJECT_0\n" );
if (wt == WAIT_TIMEOUT)
WriteRaporto("                                wt == WAIT_TIMEOUT\n" );
WriteRaporto("                                OnResizeGraphsCount return 1\n" );

		return;
	}
	ResetEvent(m_hEventDrawReady);
		RECT rect;

		GetClientRect(hWnd, &rect);
//		int nGraphs = 1 + m_pDocument->m_vPoints.vectSize();
		int nGraphs = 
#ifdef DRAW_VECTOR_VPOINTS1
			1 + 
#endif
			m_pDocument->m_vPoints.vectCheckedSize();



		m_SizeTotal_cy = m_shift_yb * nGraphs + 10 + 10;
		m_SizeTotal.cy = (long)m_SizeTotal_cy;


		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_ALL;

		if(GetScrollInfo( hWnd, SB_VERT, &si ))
		{

			si.nMin   = 0;
			si.nMax   = m_SizeTotal.cy - 1;
			si.nPage  = rect.bottom;
			m_nCurVertPos = si.nPos;

			if (m_nCurVertPos < 0)
				m_nCurVertPos = 0;

			if (m_nCurVertPos > si.nMax)
				m_nCurVertPos = si.nMax;

			si.nPos   = m_nCurVertPos;

			// m_margin_top = 10;
#ifndef DRAW_WITH_MEM_TO_WINDOW
			m_shift_ya = m_shift_yb/2+10-si.nPos; // координата центра нулевого графика
#endif
			SetScrollInfo( hWnd, SB_VERT, &si , TRUE);
		}
		else
			m_shift_ya = m_shift_yb/2+10; // координата центра нулевого графика
	SetEvent(m_hEventDrawReady);

#ifdef DO_RAPORT

char str[255];
sprintf(str,
		"nGraphs=%d m_SizeTotal.cy=%d m_nCurVertPos=%d m_shift_ya=%f m_shift_yb=%f m_scale_y=%f rect.bottom=%d\n",
		 nGraphs, m_SizeTotal.cy, m_nCurVertPos, m_shift_ya, m_shift_yb, m_scale_y, rect.bottom);
WriteRaporto(str);

WriteRaporto("OnResizeGraphsCount end\n");
#endif
}

BOOL CGraphsView::OnPaint(HWND hWnd, LPPAINTSTRUCT lpPaint)
{
#ifdef DRAW_WITH_MEM_TO_WINDOW
	RECT        rect;
	GetClientRect(hWnd,&rect);
	return BitBlt( lpPaint->hdc, 0, 0, rect.right, rect.bottom,
              hMemDC, 0, m_nCurVertPos, SRCCOPY );
#endif
#ifdef DRAW_TO_META_FILE
	RECT        rect;
	GetClientRect(hWnd,&rect);
	return PlayEnhMetaFile( lpPaint->hdc, hMetaFile, &rect );
#endif
return false;
}

bool CGraphsView::OnSize(HWND hWnd)
{
WriteRaporto("OnSize 1\n");
/*	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 
		INFINITE);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT)
	{
if (wt != WAIT_OBJECT_0)
WriteRaporto("                                wt != WAIT_OBJECT_0\n" );
if (wt == WAIT_TIMEOUT)
WriteRaporto("                                wt == WAIT_TIMEOUT\n" );
WriteRaporto("                                OnSize return 1\n" );

		return;
	}
	ResetEvent(m_hEventDrawReady);*/
	RECT rect;
     GetClientRect( hWnd, &rect );

     if ( rect.bottom < m_SizeTotal.cy - 1 )
     {
        SCROLLINFO si;
WriteRaporto("cld WM_SIZE if\n");

        si.cbSize = sizeof( SCROLLINFO );
        si.fMask  = SIF_POS | SIF_RANGE | SIF_PAGE;
        si.nMin   = 0;
        si.nMax   = m_SizeTotal.cy - 1;
        si.nPage  = rect.bottom;


		if (m_nCurVertPos < 0)
			m_nCurVertPos = 0;

		if (m_nCurVertPos > si.nMax)
			m_nCurVertPos = si.nMax;


        si.nPos   = m_nCurVertPos;

		// m_margin_top = 10;
#ifndef DRAW_WITH_MEM_TO_WINDOW
		m_shift_ya = m_shift_yb/2+10-si.nPos; // координата центра нулевого графика
#endif

#ifdef DO_RAPORT

char str[255];
sprintf(str,
" si.nMax=%d si.nPage=%d si.nPos=%d rect.bottom=%d\n",
si.nMax, si.nPage, si.nPos, rect.bottom);
WriteRaporto(str);
#endif
        EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );
        SetScrollInfo( hWnd, SB_VERT, &si, TRUE );
     }
     else
	 {
		m_nCurVertPos = 0;
		m_shift_ya = m_shift_yb/2+10; // координата центра нулевого графика
		EnableScrollBar( hWnd, SB_VERT, ESB_DISABLE_BOTH );
	 }

//	SetEvent(m_hEventDrawReady);

#ifdef DO_RAPORT

char str[255];
sprintf(str,
		"m_SizeTotal.cy=%d m_nCurVertPos=%d m_shift_ya=%f m_shift_yb=%f m_scale_y=%f rect.bottom=%d\n",
		 m_SizeTotal.cy, m_nCurVertPos, m_shift_ya, m_shift_yb, m_scale_y, rect.bottom);
WriteRaporto(str);
WriteRaporto("OnSize end\n");
#endif

	 if(bmWidth == rect.right)
		 return false;
	 else
		 return true;
}



void CGraphsView::Draw(HDC hdc, RECT &rect)
{
WriteRaporto("CGraphsView::Draw(HDC hdc, RECT &rect) 1\n");
	TData DataX, 
		DataY;
	int j = 0;
	if (m_pDocument->m_vPoints.SetCurrentVectOnFirst())
	{
		do
		{
			if (m_pDocument->m_vPoints.GetCurrentVect().GetVectorCheck())
			{
				if(m_pDocument->m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst())
				{
					do
					{						
						if(m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().toScaleX == 2)
						{
							if(j == 0)
							{
								DataX.Min = m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().minX;
								DataX.Max = m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().maxX;
							}
							else
							{
								if(DataX.Min > m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().minX)
									DataX.Min = m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().minX;
								
								if (DataX.Max < m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().maxX)
									DataX.Max = m_pDocument->m_vPoints.GetCurrentVect().GetCurrentMsg().maxX;
							}
							j++;
						}
					}							
					while(m_pDocument->m_vPoints.GetCurrentVect().IncrementCurrentMsg());
				}

			}
		}
		// Перемещаем текущий внутренний вектор
		while(m_pDocument->m_vPoints.IncrementCurrentVect());
	}

	if (m_pDocument->m_vPoints.SetCurrentVectOnFirst())
	{
		int g = 0;
		do
		{
			if (m_pDocument->m_vPoints.GetCurrentVect().GetVectorCheck())
			{
			CGraph(m_pDocument->m_vPoints.GetCurrentVect(),
				//"","t","", 
				m_shift_ya+g*m_shift_yb, m_scale_y, m_SizeTotal)
				.Draw(hdc,DataX, DataY, rect, m_iFirst, m_iLast,
#ifdef EXTERN_FONTS_AND_PENS
				m_boxPen, m_gridPen, m_linePen, m_hFont, m_hTitleFont, m_hPrintFont, m_hPrintTitleFont, 
#endif
				m_pDocument->m_vPoints.GetCurrentVect().GetFirstMsg().toScaleX, 
				m_pDocument->m_vPoints.GetCurrentVect().GetFirstMsg().toScaleY); 
			g++;
			}
		}
		// Перемещаем текущий внутренний вектор
		while(m_pDocument->m_vPoints.IncrementCurrentVect());
	}
WriteRaporto("CGraphsView::Draw(HDC hdc, RECT &rect) nd\n");

}
