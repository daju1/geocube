#include "stdafx.h"
//#include <windows.h>
#include "winmap.h"
#include "../../resource.h"

extern HINSTANCE hInst;   // текущий экземпл€р
//extern LPCTSTR lpszAppName;
LPCTSTR lpszMapTitle   = "Map";
LPCTSTR lpszWinMap   = "WINMAP";
LPCTSTR lpszWinMapName   = "MyWINMap";
extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);


int WinMap()
{
	MSG        msg;
	WNDCLASSEX wc;



	// –егистраци€ класса главного окна приложени€.
	//............................................
//	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = (WNDPROC)WinMapProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = LoadIcon( hInst, lpszWinMapName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
//	wc.lpszMenuName  = lpszAppName;
//	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_WINMap);
	wc.lpszMenuName  = lpszWinMapName;
	wc.lpszClassName = lpszWinMap;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = (HICON__ *) LoadImage( hInst, lpszWinMapName,
								 IMAGE_ICON, 16, 16,
								 LR_DEFAULTCOLOR );

	wc.cbWndExtra    = sizeof(LONG);

	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","WinMap",0);
			return( FALSE );
		}
	}

	// –егистраци€ классов дочерних окон MDI.
	//.....................................................
#ifdef USE_OWN_DC
//	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
#endif


   //hInst = hInstance;
	HWND hMapWnd = NULL;

   hMapWnd = CreateWindow( lpszWinMap,
                    	lpszMapTitle,
                    	WS_OVERLAPPEDWINDOW,
                    	CW_USEDEFAULT, 0,
                    	CW_USEDEFAULT, 0,
                    	NULL,
                    	NULL,
                    	hInst,
                    	NULL
                    	);
   if ( !hMapWnd )
   {
	   ErrorExit("CreateWindow");
 	MessageBox(0,"!hMapWnd","WinMap",0);
     return( FALSE );
	}


	ShowWindow( hMapWnd, /*nCmdShow*/1 );
   UpdateWindow( hMapWnd );


   while( GetMessage( &msg, NULL, 0, 0) )
   {
     TranslateMessage( &msg );
     DispatchMessage( &msg );
   } 

   return( msg.wParam );
}

LRESULT CALLBACK WinMapProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static HPALETTE hPalette;
static int      nColorData;
static char * pBitmap;
static char         szMsg[128];

   switch( uMsg )
   {
      case WM_CREATE  :
              {
              }
              break;

      case WM_PAINT :
              {
                 PAINTSTRUCT  ps;
                 BeginPaint( hWnd, &ps );

                           BITMAPINFOHEADER  bi;
                           BITMAPINFOHEADER* lpbi;
                           HBITMAP           hBitmap;
                           HDC               hDC, hMemDC;
						HANDLE       hRes, hRes2;

					HRSRC hRsrc, hRsrc2;

					 //ƒанные палитры из ресурсов
					
					if(!(hRsrc2 = FindResource( hInst, 
						//	MAKEINTRESOURCE(IDR_TOPOMAP_DATA1), 
							"IDR_TOPOMAP_DATA1", 
							RT_RCDATA  )))
					{
						ErrorExit("FindResource2",1);
					}
					if(!(hRes2 = LoadResource( hInst, hRsrc2)))
					{
						ErrorExit("LoadResourse2",1);
					}
					LPVOID pPaletteData = LockResource( hRes2 );
					if (!pPaletteData)
						ErrorExit("LockResource2",1);


				 // из  заголовка считываем число строк и колонок
					 int RowsP, ColsP;
					 RowsP = *((int *)pPaletteData);
					 ColsP = *((int *)pPaletteData+1);
					 //получаем указатель на данные palette


					 BYTE*  pPaletteValues = 
						 (BYTE*)((int*)pPaletteData + 2);
					  //ищем максимум и минимум
					 double maxP = pPaletteValues[0];
					 double minP = pPaletteValues[0];



					 double dataP;
					 for(int r = 0; r<RowsP; r++)
					 {
						 for(int c=0;c<ColsP;c++)
						 {
							 dataP = pPaletteValues[ColsP*r+c];
							 if(dataP>maxP) maxP=dataP;
							 if(dataP<minP) minP=dataP;
						 }
					 }


					 // «агрузить relief data.
					 //.................

					if(!(hRsrc = FindResource( hInst, 
							//MAKEINTRESOURCE(IDR_RELIEF_DATA1), 
							"IDR_RELIEF_DATA1", 
							RT_RCDATA  )))
					{
						ErrorExit("FindResource",1);
					}
					if(!(hRes = LoadResource( hInst, hRsrc)))
					{
						ErrorExit("LoadResourse",1);
					}
					LPVOID pReliefData = LockResource( hRes );
					if (!pReliefData)
						ErrorExit("LockResource",1);

					 // из  заголовка считываем число строк и колонок
					 int Rows, Cols;
					 Rows = *((int *)pReliefData);
					 Cols = *((int *)pReliefData+1);
					 //получаем указатель на данные рельефа

					 int*  pReliefValues = 
						 (int*)((int*)pReliefData + 2);
					  //ищем максимум и минимум
					 int max = pReliefValues[0];
					 int min = pReliefValues[0];
					 int data;
					 for(int r = 0; r<Rows; r++)
					 {
						 for(int c=0;c<Cols;c++)
						 {
							 data = pReliefValues[Cols*r+c];
							 if(data>max) max=data;
							 if(data<min) min=data;
						 }
					 }
					 //диапазон высот 
					 int delta=max-min;
					 int zero = 0;
					 int nCoastPalette = 36;
					 //диапазон палитры
					 int nColors = RowsP;
					 //int nColors = 2;
					 
					 //выдел€ем пам€ть дл€ пиксельных данных рисунка
					 BYTE *pBits = (BYTE*)HeapAlloc(GetProcessHeap(),
						 HEAP_ZERO_MEMORY,Rows*Cols);
					 //заполн€ем пиксельные данные
					 for(int r = 0; r<Rows; r++)
					 {
						 for(int c=0;c<Cols;c++)
						 {
							 int index  = Cols*r+c;
#if 0
							 int index2  = Cols * (Rows - r) + c;
#else
							 int index2  = Cols * (Rows - r) + c - Cols/2;
#endif

							 data = pReliefValues[index2];
#if 0
							 pBits[index] = 
								 BYTE(double(data - min) 
								 / double(delta) 
								 * double(nColors));
#else
							 pBits[index] = data <= zero 
								 ? 								 
								 BYTE(double(data - min) 
								 / double(zero-min) 
								 * double(nCoastPalette))
								 :
								 BYTE(nCoastPalette + double(data - zero) 
								 / double(max-zero) 
								 * double(nColors - nCoastPalette))
								 ;
#endif
						 }
					 }

//					 char sss[64];
//					 sprintf(sss,"max=%f,min=%f",maxP,minP);
//					 MessageBox(0,sss,"",0);

                       // »нициализировать структуру BITMAPINFOHEADER.
                       //...........................................
                       bi.biSize     = sizeof( BITMAPINFOHEADER );
                       bi.biWidth    = Cols;
                       bi.biHeight   = Rows;
                       bi.biPlanes   = 1;
                       bi.biBitCount = 8;//4;
                       bi.biCompression   = BI_RGB;
                       bi.biSizeImage     = 0;
                       bi.biXPelsPerMeter = 0;
                       bi.biYPelsPerMeter = 0;
                       bi.biClrUsed       = RowsP;
                       bi.biClrImportant  = 0;

                       hDC = GetDC( hWnd );


                       // –аспределить пам€ть дл€ структуры BITMAPINFO.
                       //..........................................
                       lpbi = (BITMAPINFOHEADER*)HeapAlloc( GetProcessHeap(),
                                             HEAP_ZERO_MEMORY,
                                             sizeof(BITMAPINFOHEADER) + 
                                             256*sizeof(RGBQUAD) 
                                             //RowsP*sizeof(RGBQUAD) 
											 );

                       // —копировать структуру bi в верхнюю часть 						   // структуры BITMAPINFO.
                       //........................................
                       *lpbi = bi;

					   LPBITMAPINFO lpBi = (LPBITMAPINFO)lpbi;

					  for(int r = 0; r<RowsP; r++)
						{
							lpBi->bmiColors[r].rgbRed = BYTE(pPaletteValues[ColsP*r+0]);
							lpBi->bmiColors[r].rgbGreen = BYTE(pPaletteValues[ColsP*r+1]);
							lpBi->bmiColors[r].rgbBlue  = BYTE(pPaletteValues[ColsP*r+2]);
						}


                           // —оздать изображение DIB.
                           //............
                           //hBitmap = CreateDIBitmap( hDC, &bi, 0L, NULL,
                           //                          NULL, 0 );

                           hBitmap = CreateDIBitmap( 
							   hDC, &bi, 
							   CBM_INIT, (LPVOID)pBits,                                                     
							   lpBi, 
							   //DIB_PAL_COLORS 
							   DIB_RGB_COLORS 
							   );

                           // »нициализировать данные структуры bi 						   // с использованием функции GetDIBits().
                           //........................................
                           GetDIBits( hDC, hBitmap, 0, 50, NULL,
                                      lpBi, 
									  //DIB_PAL_COLORS 
									  DIB_RGB_COLORS 
									  );

                           // —оздать контекст устройства пам€ти и выбрать 
							// дл€ него это изображение DIB.
                           //...............................
                           hMemDC = CreateCompatibleDC( hDC );
                           SelectObject( hMemDC, hBitmap );




                           // ¬ывести растровое изображение на дисплей.
                           //.................................
                           BitBlt( hDC, 0, 0, Cols, Rows,
                                   hMemDC, 0, 0, SRCCOPY );

                           DeleteDC( hMemDC );

                           HeapFree( GetProcessHeap(), 0, lpbi );
                           ReleaseDC( hWnd, hDC );


                 EndPaint( hWnd, &ps );
              }
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case ID_WINMAP_FILE_EXIT :
                        DestroyWindow( hWnd );
                        break;
              }
              break;

      case WM_DESTROY :
              PostQuitMessage(0);
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}
