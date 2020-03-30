
//#include "StdAfx.h"
#include "../../resource.h"
#define WM_MOUSEWHEEL                   0x020A
#define RGBA(r,g,b,a)   ( (((DWORD)(BYTE)(a))<<24) | RGB(r,g,b))
//#include "StdAfx.h"

#include <time.h>
#include "wingeoid.h"
#include "../../array/src/sorting.h"
#include "../../array/src/interp.h"
#include "../../array/src/vdouble.h"
#include "../../array/src/matrixes.h"

#include "../../commonOG.h"

#include "../../surfdoc/src/points.h"
#include "../../tools/src/errorexit.h"

//#define USE_EARTH_ROTATE


extern HINSTANCE hInst;   // текущий экземпляр
//extern LPCTSTR lpszAppName;
LPCTSTR lpszGeoidTitle   = "Geoid";
LPCTSTR lpszWinGeoid   = "WINGEOID";
LPCTSTR lpszWinGeoidName   = "MyWINGeoid";
//extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);
extern bool getNorm(double v1[3], double v2[3], double out[3]);
extern BYTE **AllocByteMat (int size1, int size2);
extern void FreeByteMat(BYTE ** v);


WPARAM WinGeoid()
{
	MSG        msg;
	WNDCLASSEX wc;



	// Регистрация класса главного окна приложения.
	//............................................
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WinGeoidProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = LoadIcon( hInst, lpszWinGeoidName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
//	wc.lpszMenuName  = lpszAppName;
//	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_WINGeoid);
	wc.lpszMenuName  = lpszWinGeoidName;
	wc.lpszClassName = lpszWinGeoid;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = (HICON__ *) LoadImage( hInst, lpszWinGeoidName,
								 IMAGE_ICON, 16, 16,
								 LR_DEFAULTCOLOR );

//	wc.cbWndExtra    = sizeof(LONG);

	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","WinGeoid",0);
			return( FALSE );
		}
	}

	// Регистрация классов дочерних окон MDI.
	//.....................................................
#ifdef USE_OWN_DC
//	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
#endif


   //hInst = hInstance;
	HWND hGeoidWnd = NULL;

   hGeoidWnd = CreateWindow( lpszWinGeoid,
                    	lpszGeoidTitle,
                    	WS_OVERLAPPEDWINDOW,
                    	CW_USEDEFAULT, 0,
                    	CW_USEDEFAULT, 0,
                    	NULL,
                    	NULL,
                    	hInst,
                    	NULL
                    	);
   if ( !hGeoidWnd )
   {
	   ErrorExit("CreateWindow");
 	MessageBox(0,"!hGeoidWnd","WinGeoid",0);
     return( FALSE );
	}


	ShowWindow( hGeoidWnd, /*nCmdShow*/1 );
   UpdateWindow( hGeoidWnd );


   while( GetMessage( &msg, NULL, 0, 0) )
   {
     TranslateMessage( &msg );
     DispatchMessage( &msg );
   } 

   return( msg.wParam );
}
const UINT gnRings = 180;		// Количество колец (широта)
const UINT gnSects = 360;		// Количество секций (долгота)

//====== Общее количество треугольников
const UINT gnTria = (gnRings) * gnSects * 2;

//====== Общее количество вершин
const UINT gnVert = (gnRings) * gnSects + 2;

int ni = 1;
//====== Общее количество треугольников
	UINT gnRingsi = gnRings*ni;		// Количество колец (широта)
	UINT gnSectsi = gnSects*ni;		// Количество секций (долгота)
	UINT gnTriai = (gnRingsi) * gnSectsi * 2;

//====== Общее количество вершин
	UINT gnVerti = (gnRingsi) * gnSectsi + 2;

//====== Два цвета вершин
const COLORREF gClr1 = RGB(0, 255, 0);
const COLORREF gClr2 = RGB(0, 0, 255);

const double gRad = 2.5;			// Радиус сферы
const double gMax = 5.;			// Амплитуда сдвига
//const double PI = atan(1.)*4.; // Число пи

double vzoom = 25;



void Sphere3(VERT *v, TRIA* t, int alpha = 150)
{
	static char * pBitmap;
	static HPALETTE hPalette;
	static int      nColorData;
                           BITMAPINFOHEADER  bi;
                           BITMAPINFOHEADER* lpbi;
						HANDLE       hRes, hRes2;

					HRSRC hRsrc, hRsrc2;

					 //Данные палитры из ресурсов
					
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
					 BYTE maxP = pPaletteValues[0];
					 BYTE minP = pPaletteValues[0];

					int r,c;


					 BYTE dataP;
					 for( r = 0; r<RowsP; r++)
					 {
						 for( c=0;c<ColsP;c++)
						 {
							 dataP = pPaletteValues[ColsP*r+c];
							 if(dataP>maxP) maxP=dataP;
							 if(dataP<minP) minP=dataP;
						 }
					 }


					 // Загрузить relief data.
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




					int nx = Cols;
					int ny = Rows;

					int nxi = nx*ni;
					int nyi = ny*ni;

					double *x, *y, **xx, **yy, **zz;
					double *xi_, *yi_, **xxi, **yyi, **zzi;

					x = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						nx * sizeof (double));
					y = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						ny * sizeof (double));

					xi_ = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						nxi * sizeof (double));
					yi_ = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						nyi * sizeof (double));

	//====== Подготовка констант
	double	dB = PI / (gnRings),
			dL = 2.* PI / gnSects,
			Bf = PI/2.0 - dB/2.,
			Lf = 2.* PI - dL/2.0;

					//L = dL/2.0; L <= Lf; L += dL
					for (c = 0; c < nx; c++)
						x[c] = dL/2.0 + dL*c;
					//B = Bf;  B >= -Bf-.0000001;  B -= dB
					for(r = 0; r < ny; r++)
						y[r] = Bf - dB*r;

					for (c = 0; c < nxi; c++)
						xi_[c] = (dL/2.0 + dL*double(c))/double(ni);
					for(r = 0; r < nyi; r++)
						yi_[r] = Bf - dB*double(r)/double(ni);




					zz = AllocDoubleMat (ny, nx);
					xx = AllocDoubleMat (ny, nx);
					yy = AllocDoubleMat (ny, nx);

					for (r = 0; r < ny; r++)
					{
						for(c = 0; c < nx; c++)
						{														 
							int index  = Cols*r+c;
							zz[r][c] = pReliefValues[index];
						}
					}



					meshgrid( nx, ny, x, y, xx, yy);

					
					xxi = AllocDoubleMat (nyi, nxi);
					yyi = AllocDoubleMat (nyi, nxi);
					zzi = AllocDoubleMat (nyi, nxi);


					meshgrid( nxi, nyi, xi_, yi_, xxi, yyi);

					
					cubicInterp2( 
						nx, ny, xx,yy,zz,
						nxi, nyi, xxi, yyi, zzi,0.0);

					
					if (xxi) FreeDoubleMat(xxi);
					if (yyi) FreeDoubleMat(yyi);

					if(xx) FreeDoubleMat(xx);
					if(yy) FreeDoubleMat(yy);
					if(zz) FreeDoubleMat(zz);

					if (x) HeapFree( GetProcessHeap(), 0, x );
					if (y) HeapFree( GetProcessHeap(), 0, y );
					/*vdouble ZZI(nyi, nxi);

					for (r = 0; r < nyi; r++)
					{
						for(c = 0; c < nxi; c++)
						{
							ZZI(r,c) = zzi[r][c];
						}
					}*/


					  //ищем максимум и минимум
					 double max = zzi[0][0];
					 double min = zzi[0][0];
					 double data;
					 for(r = 0; r<Rows; r++)
					 {
						 for(int c=0;c<Cols;c++)
						 {
							 data = zzi[r][c];
							 if(data>max) max=data;
							 if(data<min) min=data;
						 }
					 }




					 //диапазон высот 
					 double delta=max-min;
					 double zero = 0;
					 int nCoastPalette = 36;
					 //диапазон палитры
					 int nColors = RowsP;
					 //int nColors = 2;
					 
					 //выделяем память для пиксельных данных рисунка
					 /*BYTE *pBits = (BYTE*)HeapAlloc(GetProcessHeap(),
						 HEAP_ZERO_MEMORY,Rows*Cols);*/

					 BYTE **pBits = AllocByteMat (nyi, nxi);

					 //заполняем пиксельные данные
					 for(r = 0; r<nyi/*Rows*/; r++)
					 {
						 for(int c=0;c<nxi/*Cols*/;c++)
						 {
							 //int index  = /*Cols*/nxi*r+c;
							 data = /*pReliefValues[index]*/zzi[r][c];
#if 0
							 pBits[r][c] = 
								 BYTE(double(data - min) 
								 / double(delta) 
								 * double(nColors));
#else
							 pBits[r][c] = data <= zero 
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

					 char sss[64];
					 sprintf(sss,"max=%d,min=%d",int(maxP),int(minP));
					 MessageBox(0,sss,"",0);

                       // Инициализировать структуру BITMAPINFOHEADER.
                       //...........................................
                       bi.biSize     = sizeof( BITMAPINFOHEADER );
                       bi.biWidth    = Cols*ni;
                       bi.biHeight   = Rows*ni;
                       bi.biPlanes   = 1;
                       bi.biBitCount = 8;//4;
                       bi.biCompression   = BI_RGB;
                       bi.biSizeImage     = 0;
                       bi.biXPelsPerMeter = 0;
                       bi.biYPelsPerMeter = 0;
                       bi.biClrUsed       = RowsP;
                       bi.biClrImportant  = 0;



                       // Распределить память для структуры BITMAPINFO.
                       //..........................................
                       lpbi = (BITMAPINFOHEADER*)HeapAlloc( GetProcessHeap(),
                                             HEAP_ZERO_MEMORY,
                                             sizeof(BITMAPINFOHEADER) + 
                                             256*sizeof(RGBQUAD) 
                                             //RowsP*sizeof(RGBQUAD) 
											 );

                       // Скопировать структуру bi в верхнюю часть 						   // структуры BITMAPINFO.
                       //........................................
                       *lpbi = bi;

					   LPBITMAPINFO lpBi = (LPBITMAPINFO)lpbi;

					   


					  for(r = 0; r<RowsP; r++)
						{
							lpBi->bmiColors[r].rgbRed = BYTE(pPaletteValues[ColsP*r+0]);
							lpBi->bmiColors[r].rgbGreen = BYTE(pPaletteValues[ColsP*r+1]);
							lpBi->bmiColors[r].rgbBlue  = BYTE(pPaletteValues[ColsP*r+2]);

						}
					 MessageBox(0,"2","",0);


	//====== Формирование массива вершин
	//====== Северный полюс
	double 
		a = 6378245.,
		b = 6356863.0188,
		e = sqrt(a*a - b*b) / a;

	double Npol = gRad / ( sqrt(1. - e*e) ),
		zpol = Npol * (1 - e*e);
//	double vzoom = 25;
	double d1[3],d2[3],norm[3];
	double 
		xi,yi,zi,
		xn,yn,zn,
		xj,yj,zj;
	int nB = 0,nL = 0, nn = 0, nnj,nnn;

	//=== Индекс вершины, следующей за северным полюсом
	double B,//геодезическая широта
		L,// геодезическая долгота
		N;// радиус кривизны первого вертикала в зависимости от широты
						

	double z;
	int ipalette = int(pBits[0][0]);//*((/*(BYTE*)*/)));
	v[0].c = RGB(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbGreen,
		lpBi->bmiColors[ipalette].rgbBlue);


			xi = 0.0;
			yi = 0.0;
			zi = zpol * (1. + vzoom*zzi[0][0] / a);

			N = gRad / ( sqrt(1. - e*e * sin(Bf)*sin(Bf)) ),

			nnj = 1;
			xj = N * cos(Bf) * cos(dL/2.0);
			yj = N * cos(Bf) * sin(dL/2.0);
			zj = N * sin(Bf) * (1 - e*e);;

			xj = xj * (1. + vzoom*zzi[0][1] / a);
			yj = yj * (1. + vzoom*zzi[0][1] / a);
			zj = zj * (1. + vzoom*zzi[0][1] / a);

			nnn = 2;
			xn = N * cos(Bf) * cos(dL+dL/2.0);
			yn = N * cos(Bf) * sin(dL+dL/2.0);
			zn = N * sin(Bf) * (1 - e*e);

			xn = xn * (1. + vzoom*zzi[0][2] / a);
			yn = yn * (1. + vzoom*zzi[0][2] / a);
			zn = zn * (1. + vzoom*zzi[0][2] / a);

			v[0].v = CPoint3 (
				xi, 
				yi, 
				zi);

			d1[0] = xn-xi;
			d1[1] = yn-yi;
			d1[2] = zn-zi;

			d2[0] = xi-xj;
			d2[1] = yi-yj;
			d2[2] = zi-zj;
			getNorm(d1,d2,norm);

			v[0].n = CPoint3 (norm[0], norm[1], norm[2]);




	UINT n = 0;


	//=== Цикл по широтам
//	for (B = Bf;  B >= -Bf-.0000001;  B -= dB)
					
		for (r = 0; r < nyi; r++)	
		{
			B = yi_[r];
		//N = a / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		//x = N * cos(B) * cos(L),
		//y = N * cos(B) * sin(L),
		//z = N * sin(B) * (1 - e*e);
		N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		nB++;
		//=== Координата z постоянна для всего кольца
	
			//z  = gRad * cos(B),
			z = N * sin(B) * (1 - e*e);
				//====== Вспомогательная точка
				//xy = gRad * sin(B);
		double	xy = N * cos(B);
		nL = 0;

		//====== Цикл по секциям (долгота)
//		for (L = dL/2.0; L <= Lf; L += dL)
		for (c = 0; c < nxi; c++)
		{
			L = xi_[c];
			nL++;
			nn++;
			n++;
			// Координаты проекции в экваториальной плоскости
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			double
			//		x = xz * sin(L),
			//		y = xz * cos(L);
					x = xy * cos(L),
					y = xy * sin(L);

			nn = (nB-1)*gnSects+nL;
			//====== Вершина, нормаль и цвет

			xi = x * (1. + vzoom*zzi[r][c] / a);
			yi = y * (1. + vzoom*zzi[r][c] / a);
			zi = z * (1. + vzoom*zzi[r][c] / a);

			//fprintf(stream, "n=%d, nn=%d, nB=%d, nL=%d, B=%lf, L=%lf, xi=%lf, yi=%lf, zi=%lf\n",n,nn,nB,nL,	B/PI*180.0,L/PI*180.0, xi,yi,zi);

			nnj = nL==1 ? (nB-1)*gnSects + gnSects : (nB-1)*gnSects+nL-1;

			xj = xy * cos(L-dL);
			yj = xy * sin(L-dL);
			zj = z;

			xj = xj * (1. + vzoom*zzi[r>0 ? r-1 : 0][c] / a);
			yj = yj * (1. + vzoom*zzi[r>0 ? r-1 : 0][c] / a);
			zj = zj * (1. + vzoom*zzi[r>0 ? r-1 : 0][c] / a);

			nnn = nB==1 ? 0 : (nB-2)*gnSects+nL;

			xn = N * cos(B-dB) * cos(L);
			yn = N * cos(B-dB) * sin(L);
			zn = N * sin(B-dB) * (1 - e*e);

			xn = xn * (1. + vzoom*zzi[r][c>0 ? c-1 : nxi-1] / a);
			yn = yn * (1. + vzoom*zzi[r][c>0 ? c-1 : nxi-1] / a);
			zn = zn * (1. + vzoom*zzi[r][c>0 ? c-1 : nxi-1] / a);

			v[n].v = CPoint3 (
				xi, 
				yi, 
				zi);

			d1[0] = xn-xi;
			d1[1] = yn-yi;
			d1[2] = zn-zi;

			d2[0] = xi-xj;
			d2[1] = yi-yj;
			d2[2] = zi-zj;
			getNorm(d1,d2,norm);

			v[n].n = CPoint3 (norm[0], norm[1], norm[2]);

			//ipalette = int(*(((BYTE*)pBits)+nn-1));
			ipalette = int(pBits[r][c]);//*((/*(BYTE*)*/)));

			v[n].c = RGB(
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbGreen,
				lpBi->bmiColors[ipalette].rgbBlue);

			v[n].c = RGBA(
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbGreen,
				lpBi->bmiColors[ipalette].rgbBlue,
				alpha);
		}
	}
	//====== Индекс последней вершины (на южном полюсе)
					 MessageBox(0,"5","",0);
	
//	UINT last = gnVert - 1;//((gnRings+1) * gnSects + 2) 
	UINT last = n + 1;
	//====== Южный полюс

	//ipalette = int(*(((BYTE*)pBits)+last-2));
	ipalette = int(pBits[nyi-1][nxi-1]);//*((/*(BYTE*)*/)));
	v[last].c = RGB(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbGreen,
		lpBi->bmiColors[ipalette].rgbBlue);

/*	char str[255];
	sprintf (str, "%d %d %d\n color = %d", 
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbGreen,
				lpBi->bmiColors[ipalette].rgbBlue,
		
		v[last].c);
	MessageBox(0, str, "",0);*/

			v[last].c = RGBA(
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbGreen,
				lpBi->bmiColors[ipalette].rgbBlue,
				alpha);
/*	sprintf (str, "%d %d %d %d\n color alpha = %d", 
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbGreen,
				lpBi->bmiColors[ipalette].rgbBlue,
				alpha,
		v[last].c);
	MessageBox(0, str, "",0);*/

					 MessageBox(0,"6","",0);

			xi = 0.0;
			yi = 0.0;
			zi = -zpol * (1. + vzoom*zzi[nyi-1][nxi-1] / a);

	//fprintf(stream, "gnVert - 1=%d, last=%d, dL=%lf, dB=%lf, Lf=%lf, Bf=%lf, xi=%lf, yi=%lf, zi=%lf\n",gnVert - 1,last,dL,dB,Lf/PI*180.0,Bf/PI*180.0, xi,yi,zi);

			N = gRad / ( sqrt(1. - e*e * sin(-Bf)*sin(-Bf)) ),

			nnj = last-3;
			xj = N * cos(-Bf) * cos(Lf-dL/2.);
			yj = N * cos(-Bf) * sin(Lf-dL/2.);
			zj = N * sin(-Bf) * (1 - e*e);

			xj = xj * (1. + vzoom*zzi[nyi-2][0] / a);
			yj = yj * (1. + vzoom*zzi[nyi-2][0] / a);
			zj = zj * (1. + vzoom*zzi[nyi-2][0] / a);

			nnn = last-4;
			xn = N * cos(-Bf) * cos(Lf-3.*dL/2.);
			yn = N * cos(-Bf) * sin(Lf-3.*dL/2.);
			zn = N * sin(-Bf) * (1 - e*e);

			xn = xn * (1. + vzoom*zzi[nyi-2][1] / a);
			yn = yn * (1. + vzoom*zzi[nyi-2][1] / a);
			zn = zn * (1. + vzoom*zzi[nyi-2][1] / a);

			v[last].v = CPoint3 (
				xi, 
				yi, 
				zi);

			d1[0] = xn-xi;
			d1[1] = yn-yi;
			d1[2] = zn-zi;

			d2[0] = xi-xj;
			d2[1] = yi-yj;
			d2[2] = zi-zj;
			getNorm(d1,d2,norm);

			v[last].n = CPoint3 (norm[0], norm[1], norm[2]);
					 MessageBox(0,"7","",0);

	//====== Формирование массива индексов
	//====== Треугольники вблизи полюсов
	for (n = 0; n < gnSectsi; n++)
	{
		//====== Индекс общей вершины (северный полюс)
		t[n].i1 = 0;
		//====== Индекс текущей вершины
		t[n].i2 = n + 1;
		//====== Замыкание
		t[n].i3 = n == gnSectsi - 1 ? 1 : n + 2;
		//====== Индекс общей вершины (южный полюс)
		t[gnTriai-gnSectsi+n].i1 = gnVerti - 1;
		t[gnTriai-gnSectsi+n].i2 = gnVerti - 2 - n;
		t[gnTriai-gnSectsi+n].i3 = gnVerti - 2
								- ((1 + n) % gnSectsi);
	}
	
	//====== Треугольники разбиения колец
	//====== Вершина, следующая за полюсом
	int k = 1;

	//====== gnSects - номер следующего треугольника
	n = gnSectsi;
	for (UINT i = 0; i < gnRingsi-1; i++, k += gnSectsi)
	{
		for (UINT j = 0; j < gnSectsi; j++, n += 2)
		{
			//======= Индекс общей вершины
			t[n].i1 = k + j;
			//======= Индекс текущей вершины
			t[n].i2 = k + gnSectsi + j;
			//======= Замыкание
			t[n].i3 = k + gnSectsi + ((j + 1) % gnSectsi);
			//======= То же для второго треугольника
			t[n + 1].i1 = t[n].i1;
			t[n + 1].i2 = t[n].i3;
			t[n + 1].i3 = k + ((j + 1) % gnSectsi);
		}
	}
					
					if (zzi) FreeDoubleMat(zzi);

					if (xi_) HeapFree( GetProcessHeap(), 0, xi_ );
					if (yi_) HeapFree( GetProcessHeap(), 0, yi_ );

					if (pBits)  FreeByteMat(pBits);
}




//====== Вектор углов вращения вокруг трех осей
CPoint3 gSpin;

//====== Вектор случайной девиации вектора gSpin
CPoint3 gShift;



/*inline double Rand(double x)
{
	//====== Случайное число в диапазоне (-x, x)
	return x - (x + x) * rand() / RAND_MAX;
}
*/
int Geo2xyz(double B, double L, double& x, double& y, double& z)
{
						
	HANDLE hRes;
	HRSRC hRsrc;
	int nB = 0,nL = 0, nn = 0;

	nL= L > 0.0 ? int(L+0.5) : int(360.5+L);
	nB=int(90.5-B);

	nn = (nB-1)*gnSects+nL-1;

	B = B / 180.0 * PI;
	L = L / 180.0 * PI;

	 // Загрузить relief data.
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

	//====== Северный полюс
	double 
		a = 6378245.,
		b = 6356863.0188,
		e = sqrt(a*a - b*b) / a;

	double 	N;// радиус кривизны первого вертикала в зависимости от широты
	N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) );
	//z  = gRad * cos(B),
	z = N * sin(B) * (1 - e*e);
				//====== Вспомогательная точка
				//xy = gRad * sin(B);
	double	xy = N * cos(B);
			// Координаты проекции в экваториальной плоскости
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			//		x = xz * sin(L),
			//		y = xz * cos(L);
	x = xy * cos(L)*(1. + vzoom*double(pReliefValues[nn]) / a);
	y = xy * sin(L)*(1. + vzoom*double(pReliefValues[nn]) / a);
	z = z * (1. + vzoom*double(pReliefValues[nn]) / a);
	return 0;
}


void Sphere2(VERT *v, TRIA* t, int alpha = 100)
{
	int r;
	static char * pBitmap;
	static HPALETTE hPalette;
	static int      nColorData;
	BITMAPINFOHEADER  bi;
	BITMAPINFOHEADER* lpbi;
	HANDLE       hRes, hRes2;
	HRSRC hRsrc, hRsrc2;
	
	//Данные палитры из ресурсов
					
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
	BYTE maxP = pPaletteValues[0];
	BYTE minP = pPaletteValues[0];

	
	BYTE dataP;
	for(r = 0; r<RowsP; r++)
	{
		for(int c=0;c<ColsP;c++)
		{
			dataP = pPaletteValues[ColsP*r+c];
			if(dataP>maxP) maxP=dataP;
			if(dataP<minP) minP=dataP;
		}
	}

	// Загрузить relief data.
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
	for(r = 0; r<Rows; r++)
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
				 
	//выделяем память для пиксельных данных рисунка
	BYTE *pBits = (BYTE*)HeapAlloc(GetProcessHeap(),
		HEAP_ZERO_MEMORY,Rows*Cols);
	//заполняем пиксельные данные
	for(r = 0; r<Rows; r++)
	{
		for(int c=0;c<Cols;c++)
		{
			int index  = Cols*r+c;
			data = pReliefValues[index];
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


	// Инициализировать структуру BITMAPINFOHEADER.
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



	// Распределить память для структуры BITMAPINFO.
	//..........................................
	lpbi = (BITMAPINFOHEADER*)HeapAlloc( GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		sizeof(BITMAPINFOHEADER) + 
		256*sizeof(RGBQUAD) 
		);

	// Скопировать структуру bi в верхнюю часть 
	// структуры BITMAPINFO.
	//........................................
	*lpbi = bi;

	LPBITMAPINFO lpBi = (LPBITMAPINFO)lpbi;
	for(r = 0; r<RowsP; r++)
	{
		lpBi->bmiColors[r].rgbRed = BYTE(pPaletteValues[ColsP*r+0]);
		lpBi->bmiColors[r].rgbGreen = BYTE(pPaletteValues[ColsP*r+1]);
		lpBi->bmiColors[r].rgbBlue  = BYTE(pPaletteValues[ColsP*r+2]);
	}


	//====== Формирование массива вершин
	//====== Северный полюс
	double 
		a = 6378245.,
		b = 6356863.0188,
		e = sqrt(a*a - b*b) / a;

	double Npol = gRad / ( sqrt(1. - e*e) ),
		zpol = Npol * (1 - e*e);

	double d1[3],d2[3],norm[3];
	double 
		xi,yi,zi,
		xn,yn,zn,
		xj,yj,zj;
	int nB = 0,nL = 0, nn = 0, nnj,nnn;
	//====== Подготовка констант
	double	dB = PI / (gnRings),
			dL = 2.* PI / gnSects,
			Bf = PI/2.0 - dB/2.,
			Lf = 2.* PI - dL/2.0;

	//=== Индекс вершины, следующей за северным полюсом
	double B,//геодезическая широта
		L,// геодезическая долгота
		N;// радиус кривизны первого вертикала в зависимости от широты
						
			

	double z;
	int ipalette = int(*(((BYTE*)pBits)));
	v[0].c = RGBA(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbGreen,
		lpBi->bmiColors[ipalette].rgbBlue,
		alpha);


	xi = 0.0;
	yi = 0.0;
	zi = zpol * (1. + vzoom*double(pReliefValues[0]) / a);

	N = gRad / ( sqrt(1. - e*e * sin(Bf)*sin(Bf)) ),

	nnj = 1;
	xj = N * cos(Bf) * cos(dL/2.0);
	yj = N * cos(Bf) * sin(dL/2.0);
	zj = N * sin(Bf) * (1 - e*e);;

	xj = xj * (1. + vzoom*double(pReliefValues[nnj]) / a);
	yj = yj * (1. + vzoom*double(pReliefValues[nnj]) / a);
	zj = zj * (1. + vzoom*double(pReliefValues[nnj]) / a);

	nnn = 2;
	xn = N * cos(Bf) * cos(dL+dL/2.0);
	yn = N * cos(Bf) * sin(dL+dL/2.0);
	zn = N * sin(Bf) * (1 - e*e);

	xn = xn * (1. + vzoom*double(pReliefValues[nnn]) / a);
	yn = yn * (1. + vzoom*double(pReliefValues[nnn]) / a);
	zn = zn * (1. + vzoom*double(pReliefValues[nnn]) / a);

	v[0].v = CPoint3 (
		xi, 
		yi, 
		zi);

	d1[0] = xn-xi;
	d1[1] = yn-yi;
	d1[2] = zn-zi;

	d2[0] = xi-xj;
	d2[1] = yi-yj;
	d2[2] = zi-zj;
	getNorm(d1,d2,norm);

	v[0].n = CPoint3 (norm[0], norm[1], norm[2]);

	UINT n = 0;

	//=== Цикл по широтам
	for (B = Bf;  B >= -Bf-.0000001;  B -= dB)
	{
		//N = a / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		//x = N * cos(B) * cos(L),
		//y = N * cos(B) * sin(L),
		//z = N * sin(B) * (1 - e*e);
		N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		nB++;
		//=== Координата z постоянна для всего кольца
	
			//z  = gRad * cos(B),
			z = N * sin(B) * (1 - e*e);
				//====== Вспомогательная точка
				//xy = gRad * sin(B);
		double	xy = N * cos(B);
		nL = 0;

		//====== Цикл по секциям (долгота)
		for (L = dL/2.0; L <= Lf; L += dL)
		{
			nL++;
			nn++;
			n++;
			// Координаты проекции в экваториальной плоскости
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			double
			//		x = xz * sin(L),
			//		y = xz * cos(L);
					x = xy * cos(L),
					y = xy * sin(L);

			nn = (nB-1)*gnSects+nL;
			//====== Вершина, нормаль и цвет

			xi = x * (1. + vzoom*double(pReliefValues[nn-1]) / a);
			yi = y * (1. + vzoom*double(pReliefValues[nn-1]) / a);
			zi = z * (1. + vzoom*double(pReliefValues[nn-1]) / a);

			//fprintf(stream, "n=%d, nn=%d, nB=%d, nL=%d, B=%lf, L=%lf, xi=%lf, yi=%lf, zi=%lf\n",n,nn,nB,nL,	B/PI*180.0,L/PI*180.0, xi,yi,zi);

			nnj = nL==1 ? (nB-1)*gnSects + gnSects : (nB-1)*gnSects+nL-1;

			xj = xy * cos(L-dL);
			yj = xy * sin(L-dL);
			zj = z;

			xj = xj * (1. + vzoom*double(pReliefValues[nnj-1]) / a);
			yj = yj * (1. + vzoom*double(pReliefValues[nnj-1]) / a);
			zj = zj * (1. + vzoom*double(pReliefValues[nnj-1]) / a);

			nnn = nB==1 ? 0 : (nB-2)*gnSects+nL;

			xn = N * cos(B-dB) * cos(L);
			yn = N * cos(B-dB) * sin(L);
			zn = N * sin(B-dB) * (1 - e*e);

			xn = xn * (1. + vzoom*double(pReliefValues[nnn-1]) / a);
			yn = yn * (1. + vzoom*double(pReliefValues[nnn-1]) / a);
			zn = zn * (1. + vzoom*double(pReliefValues[nnn-1]) / a);

			v[n].v = CPoint3 (
				xi, 
				yi, 
				zi);

			d1[0] = xn-xi;
			d1[1] = yn-yi;
			d1[2] = zn-zi;

			d2[0] = xi-xj;
			d2[1] = yi-yj;
			d2[2] = zi-zj;
			getNorm(d1,d2,norm);

			v[n].n = CPoint3 (norm[0], norm[1], norm[2]);

			ipalette = int(*(((BYTE*)pBits)+nn-1));

			v[n].c = RGBA(
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbGreen,
				lpBi->bmiColors[ipalette].rgbBlue,
				alpha);
		}
	}
	//====== Индекс последней вершины (на южном полюсе)
	
	UINT last = n + 1;
	//====== Южный полюс

	ipalette = int(*(((BYTE*)pBits)+last-2));

	v[last].c = RGBA(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbGreen,
		lpBi->bmiColors[ipalette].rgbBlue,
		alpha);


	xi = 0.0;
	yi = 0.0;
	zi = -zpol * (1. + vzoom*double(pReliefValues[last-2]) / a);


	N = gRad / ( sqrt(1. - e*e * sin(-Bf)*sin(-Bf)) ),

	nnj = last-3;
	xj = N * cos(-Bf) * cos(Lf-dL/2.);
	yj = N * cos(-Bf) * sin(Lf-dL/2.);
	zj = N * sin(-Bf) * (1 - e*e);

	xj = xj * (1. + vzoom*double(pReliefValues[nnj]) / a);
	yj = yj * (1. + vzoom*double(pReliefValues[nnj]) / a);
	zj = zj * (1. + vzoom*double(pReliefValues[nnj]) / a);

	nnn = last-4;
	xn = N * cos(-Bf) * cos(Lf-3.*dL/2.);
	yn = N * cos(-Bf) * sin(Lf-3.*dL/2.);
	zn = N * sin(-Bf) * (1 - e*e);

	xn = xn * (1. + vzoom*double(pReliefValues[nnn]) / a);
	yn = yn * (1. + vzoom*double(pReliefValues[nnn]) / a);
	zn = zn * (1. + vzoom*double(pReliefValues[nnn]) / a);

	v[last].v = CPoint3 (
		xi, 
		yi, 
		zi);

	d1[0] = xn-xi;
	d1[1] = yn-yi;
	d1[2] = zn-zi;

	d2[0] = xi-xj;
	d2[1] = yi-yj;
	d2[2] = zi-zj;
	getNorm(d1,d2,norm);

	v[last].n = CPoint3 (norm[0], norm[1], norm[2]);

	//====== Формирование массива индексов
	//====== Треугольники вблизи полюсов
	for (n = 0; n < gnSects; n++)
	{
		//====== Индекс общей вершины (северный полюс)
		t[n].i1 = 0;
		//====== Индекс текущей вершины
		t[n].i2 = n + 1;
		//====== Замыкание
		t[n].i3 = n == gnSects - 1 ? 1 : n + 2;
		//====== Индекс общей вершины (южный полюс)
		t[gnTria-gnSects+n].i1 = gnVert - 1;
		t[gnTria-gnSects+n].i2 = gnVert - 2 - n;
		t[gnTria-gnSects+n].i3 = gnVert - 2
								- ((1 + n) % gnSects);
	}
	
	//====== Треугольники разбиения колец
	//====== Вершина, следующая за полюсом
	int k = 1;

	//====== gnSects - номер следующего треугольника
	n = gnSects;
	for (UINT i = 0; i < gnRings-1; i++, k += gnSects)
	{
		for (UINT j = 0; j < gnSects; j++, n += 2)
		{
			//======= Индекс общей вершины
			t[n].i1 = k + j;
			//======= Индекс текущей вершины
			t[n].i2 = k + gnSects + j;
			//======= Замыкание
			t[n].i3 = k + gnSects + ((j + 1) % gnSects);
			//======= То же для второго треугольника
			t[n + 1].i1 = t[n].i1;
			t[n + 1].i2 = t[n].i3;
			t[n + 1].i3 = k + ((j + 1) % gnSects);
		}
	}
}

void Sphere(VERT *v, TRIA* t)
{
	static char * pBitmap;
	static HPALETTE hPalette;
	static int      nColorData;

	pBitmap = MAKEINTRESOURCE(IDB_BITMAP_POLITIC_MAP);					  			  

	HANDLE       hRes;
	LPBITMAPINFO lpBi;
	LPTSTR       lpBits;

	// Загрузить растровое изображение.
	//.................
	hRes = LoadResource( hInst,
			FindResource( hInst, pBitmap, RT_BITMAP ) );

	lpBi = (LPBITMAPINFO)LockResource( hRes );

	// Определить необходимое количество цветов.
	//..................................
	if ( lpBi->bmiHeader.biClrUsed != 0 )
	{
		nColorData = lpBi->bmiHeader.biClrUsed;
	}
	else
	{
		switch( lpBi->bmiHeader.biBitCount )
		{
			case 1  : { nColorData = 2;  }  break; // Монохромное 										    // изображение
			case 4  : { nColorData = 16; }  break; // VGA
			case 8  : { nColorData = 256;}  break; // SVGA
			case 24 : { nColorData = 0;  }  break; // Формат True Color
		}
	}

	// Найти данные растрового изображения.
	//........................
	lpBits  =  (LPSTR) lpBi;
	lpBits +=  lpBi->bmiHeader.biSize +
		( nColorData*sizeof(RGBQUAD) );

	int ngor = lpBi->bmiHeader.biWidth;
	int nver = lpBi->bmiHeader.biHeight;

	//====== Формирование массива вершин
	//====== Северный полюс
	double 
		a = 6378245.,
		b = 6356863.0188,
		e = sqrt(a*a - b*b) / a;

	double Npol = gRad / ( sqrt(1. - e*e) ),
		zpol = Npol * (1 - e*e);

			
	v[0].v = CPoint3 (0, 0, -zpol);
	v[0].n = CPoint3 (0, 0, -1);

	double z;
	int ipalette = int(*(((BYTE*)lpBits)+0));
	v[0].c = RGB(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbBlue,
		lpBi->bmiColors[ipalette].rgbBlue);

	//====== Подготовка констант
	double	dB = PI / (gnRings + 2.),
			dL = 2. * PI / gnSects,
			Bf = PI - dB/2.,
			Lf = 2. * PI - dL/2.;

	//=== Индекс вершины, следующей за северным полюсом
	UINT n = 1;
	double B,//геодезическая широта
		L,// геодезическая долгота
		N;// радиус кривизны первого вертикала в зависимости от широты


	//=== Цикл по широтам
	int nB = 0,nL = 0, nn = 0;
	for (B =  dB - Bf/2. ;  B < Bf/2.;  B += dB)
	{
		//N = a / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		//x = N * cos(B) * cos(L),
		//y = N * cos(B) * sin(L),
		//z = N * sin(B) * (1 - e*e);
		N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		nB++;
		//=== Координата z постоянна для всего кольца
	
			//z  = gRad * cos(B),
			z = N * sin(B) * (1 - e*e);
				//====== Вспомогательная точка
				//xy = gRad * sin(B);
		double	xy = N * cos(B);
		nL = 0;

		//====== Цикл по секциям (долгота)
		for (L = -Lf/2.; L < Lf/2.; n++, L += dL)
		{
			nL++;
			nn++;
			// Координаты проекции в экваториальной плоскости
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			double
			//		x = xz * sin(L),
			//		y = xz * cos(L);
					x = xy * cos(L),
					y = xy * sin(L);
			//====== Вершина, нормаль и цвет
			v[n].v = CPoint3 (x, y, z);
			v[n].n = CPoint3 (x / gRad, y / gRad, z / gRad);
			//v[n].n = CPoint3f (-sin(B) * cos(L), -sin(B), -sin(B) * sin(L));
			//v[n].n = CPoint3f (sin(B) * sin(L), sin(B), sin(B) * cos(L));
			nn = nB*360+(360-nL);
			ipalette = int(*(((BYTE*)lpBits)+nn));
			v[n].c = RGB(
				lpBi->bmiColors[ipalette].rgbRed,
				lpBi->bmiColors[ipalette].rgbBlue,
				lpBi->bmiColors[ipalette].rgbBlue);
		}
	}
	//====== Индекс последней вершины (на южном полюсе)
	UINT last = gnVert - 1;
	//====== Южный полюс
	v[last].v = CPoint3 (0, 0, zpol);
	v[last].n = CPoint3 (0, 0, 1);
	//v[last].c = gnVert & 1 ? gClr2 : gClr1;
	ipalette = int(*(((BYTE*)lpBits)+last));
	v[last].c = RGB(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbBlue,
		lpBi->bmiColors[ipalette].rgbBlue);

	//====== Формирование массива индексов
	//====== Треугольники вблизи полюсов
	for (n = 0; n < gnSects; n++)
	{
		//====== Индекс общей вершины (северный полюс)
		t[n].i1 = 0;
		//====== Индекс текущей вершины
		t[n].i2 = n + 1;
		//====== Замыкание
		t[n].i3 = n == gnSects - 1 ? 1 : n + 2;
		//====== Индекс общей вершины (южный полюс)
		t[gnTria-gnSects+n].i1 = gnVert - 1;
		t[gnTria-gnSects+n].i2 = gnVert - 2 - n;
		t[gnTria-gnSects+n].i3 = gnVert - 2
								- ((1 + n) % gnSects);
	}
	
	//====== Треугольники разбиения колец
	//====== Вершина, следующая за полюсом
	int k = 1;

	//====== gnSects - номер следующего треугольника
	n = gnSects;
	for (UINT i = 0; i < gnRings; i++, k += gnSects)
	{
		for (UINT j = 0; j < gnSects; j++, n += 2)
		{
			//======= Индекс общей вершины
			t[n].i1 = k + j;
			//======= Индекс текущей вершины
			t[n].i2 = k + gnSects + j;
			//======= Замыкание
			t[n].i3 = k + gnSects + ((j + 1) % gnSects);
			//======= То же для второго треугольника
			t[n + 1].i1 = t[n].i1;
			t[n + 1].i2 = t[n].i3;
			t[n + 1].i3 = k + ((j + 1) % gnSects);
		}
	}
}
void InitSphere(int nlist = 1, int alpha = 255)
{
	//=== Цвет фона (на сей раз традиционно черный)
	glClearColor (0.00f, 0.0f, 0.45f, 0.1f);

#if 0
	glShadeModel (GL_FLAT);
#else
	glShadeModel (GL_SMOOTH);
#endif
	//======== Установка режима заполнения полигонов
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем первый и единственный источник света
	glEnable(GL_LIGHT0);
	//====== Необходимо учитывать глубину (ось Z)
	glEnable(GL_DEPTH_TEST);

	//====== Включаем учет цвета материала объекта
	glEnable(GL_COLOR_MATERIAL);

	// Вектор для задания различных параметров освещенности
	float v[4] =
	{
		0.05f, 0.05f, 0.05f, 1.f
	};

	//=== Сначала задаем величину окружающей освещенности
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, v);

	//====== Изменяем вектор
	v[0] = 0.9f;
	v[1] = 0.9f;
	v[2] = 0.9f;

	//====== Задаем величину диффузной освещенности
	glLightfv(GL_LIGHT0, GL_DIFFUSE, v);

	//======= Изменяем вектор
	v[0] = 0.6f;
	v[1] = 0.6f;
	v[2] = 0.6f;

	//====== Задаем отражающие свойства материчала
	glMaterialfv(GL_FRONT, GL_SPECULAR, v);

	//====== Задаем степень блесткости материала
	glMateriali(GL_FRONT, GL_SHININESS, 40);

	//====== Изменяем вектор
	v[0] = 1.f;
	v[1] = 1.f;
	v[2] = 5.f;
	v[3] = 0.f;

	//====== Задаем позицию источника света
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	//====== Переключаемся на матрицу проекции
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//====== Задаем тип проекции
	gluPerspective(45, 1, .0001, 100);

	//=== Сдвигаем точку наблюдения, отодвигаясь от
	//=== центра сцены в направлении оси z на 8 единиц
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

	//====== Переключаемся на матрицу моделирования
	glMatrixMode(GL_MODELVIEW);


	//====== Непосредственное стирание
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//====== Настройка OpenGL на использование массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//====== Захват памяти под динамические массивы
	VERT *Vert = new VERT[gnVerti];
	TRIA *Tria = new TRIA[gnTriai];

	//====== Создание изображения
	//Sphere(Vert, Tria);
	Sphere2(Vert, Tria, alpha);
	//Sphere3(Vert, Tria, alpha);


	//====== Задание адресов трех массивов (вершин,
	//====== нормалей и цветов),
	//====== а также шага перемещения по ним
	glVertexPointer(3, GL_PRECISION, sizeof(VERT), &Vert->v);
	glNormalPointer(GL_PRECISION, sizeof(VERT), &Vert->n);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT),
													&Vert->c);
	
	srand((unsigned int)time(0));		// Подготовка ГСЧ
	gShift = CPoint3 (Rand(gMax),Rand(gMax),Rand(gMax));
	gShift = CPoint3 (0,0,-1);


	//====== Формирование списка рисующих команд
	glNewList(nlist, GL_COMPILE);
		glDrawElements(GL_TRIANGLES, gnTriai*3,
							GL_UNSIGNED_INT, Tria);
	glEndList();

	//== Освобождение памяти, так как список сформирован
	delete [] Vert;
	delete [] Tria;
}

LRESULT CALLBACK WinGeoidProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static	HGLRC		m_hRC;				// Контекст OpenGL
	static	HDC			m_hdc; 			// Контекст Windows
	static char * pBitmap;
	static HPALETTE hPalette;
	static int      nColorData;

	static GLfloat	m_dx;				// Квант смещения вдоль X
	static GLfloat	m_dy;				// Квант смещения вдоль Y
	static GLfloat	m_dz;				// Квант смещения вдоль Z
	
	static bool		m_bCaptured;		// Признак захвата мыши
	static bool		m_bRightButton;	// Флаг правой кнопки мыши
	static bool		m_bQuad;			// Флаг использования GL_QUAD
	static tagPOINT		m_pt;				// Текущая позиция мыши
	
	static GLfloat	m_AngleView;		// Угол перспективы
	static GLfloat	m_xTrans;			// Cмещение вдоль X
	static GLfloat	m_yTrans;			// Cмещение вдоль Y
	static GLfloat	m_zTrans;			// Cмещение вдоль Z
	static GLfloat	m_AngleX;			// Угол поворота вокруг оси X
	static GLfloat	m_AngleY;			// Угол поворота вокруг оси Y
	static GLfloat	m_AngleZ;			// Угол поворота вокруг оси Z

	static GLdouble	m_fRangeX;		// Размер объекта вдоль X
	static GLdouble	m_fRangeY;		// Размер объекта вдоль Y
	static GLdouble	m_fRangeZ;		// Размер объекта вдоль Z

	int wmId, wmEvent;
	PAINTSTRUCT ps;
#ifdef USE_EARTH_ROTATE
	HDC hdc;
#endif
//	TCHAR szHello[MAX_LOADSTRING];
//	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
	case WM_CREATE :
		{
			PIXELFORMATDESCRIPTOR pfd =	// Описатель формата
			{
				sizeof(PIXELFORMATDESCRIPTOR),// Размер структуры
				1,							// Номер версии
				PFD_DRAW_TO_WINDOW |	// Поддержка GDI
				PFD_SUPPORT_OPENGL |	// Поддержка OpenGL
				PFD_DOUBLEBUFFER,		// Двойная буферизация
				PFD_TYPE_RGBA,			// Формат RGBA, не палитра
				24, 						// Количество плоскостей
		 									// в каждом буфере цвета
				24,	0,						// Для компоненты Red
				24,	0,						// Для компоненты Green
				24,	0,						// Для компоненты Blue
				24,	0,						// Для компоненты Alpha
				0,							// Количество плоскостей
											// буфера Accumulation
				0,			 				// То же для компоненты Red
				0,			 				// для компоненты Green
				0,							// для компоненты Blue
				0,							// для компоненты Alpha
				32, 						// Глубина Z-буфера
				0,							// Глубина буфера Stencil
				0,							// Глубина буфера Auxiliary
				0,				 			// Теперь игнорируется
				0,							// Количество плоскостей
				0,							// Теперь игнорируется
				0,							// Цвет прозрачной маски
				0							// Теперь игнорируется
			};

			//====== Добываем дежурный контекст
			m_hdc = ::GetDC(hWnd);

			//====== Просим выбрать ближайший совместимый формат
			int iD = ChoosePixelFormat(m_hdc, &pfd);
			if ( !iD )
			{
				MessageBox(hWnd,"ChoosePixelFormat::Error","On Create",0);
				return 0;
			}

			//====== Пытаемся установить этот формат
			if ( !SetPixelFormat (m_hdc, iD, &pfd) )
			{
				MessageBox(hWnd,"SetPixelFormat::Error","On Create Wingeoid",0);
				return 0;
			}

			//====== Пытаемся создать контекст передачи OpenGL
			if ( !(m_hRC = wglCreateContext (m_hdc)))
			{
				MessageBox(hWnd,"wglCreateContext::Error","On Create",0);
				return 0;
			}

			//====== Пытаемся выбрать его в качестве текущего
			if ( !wglMakeCurrent (m_hdc, m_hRC))
			{
				MessageBox(hWnd,"wglMakeCurrent::Error","On Create",0);
				return 0;
			}


MessageBox(0,"1","",0);
			InitSphere();
MessageBox(0,"2","",0);

			glNewList(2, GL_COMPILE);

			GLUquadricObj* pSphere = gluNewQuadric();
			gluQuadricDrawStyle(pSphere, GLU_FILL);

			//glRotated(5.0, 0.0, 1.0, 5.0);//повернём
			glPushMatrix();//перейдём к новым координатам, сохранив старые
			//glRotated(-90,1.0,1.0,5.0);//ещё раз повернём
			glTranslated(1,1,1);
			gluSphere(pSphere, 1.0, 10, 10) ;//рисуем сферу 
			glPopMatrix(); //возвращаемся к старым координатам 
			gluDeleteQuadric(pSphere);

			GLUquadricObj* pCylinder = gluNewQuadric();
			gluQuadricDrawStyle(pCylinder, GLU_LINE);
			//glRotated(5.0, 0.0, 1.0, 5.0);//повернём
			glPushMatrix();//перейдём к новым координатам, сохранив старые
			//glRotated(-90,1.0,1.0,5.0);//ещё раз повернём
			glTranslated(2,2,2);
			gluCylinder(pCylinder, 2., 0., 2., 10, 10);
			glPopMatrix(); //возвращаемся к старым координатам 
			gluDeleteQuadric(pCylinder);

			glEndList();



#ifdef USE_EARTH_ROTATE
			SetTimer(hWnd,             // handle to main window 
				IDT_TIMER_GEOID,            // timer identifier 
				100,                 // 10-second interval 
				(TIMERPROC) NULL);     // no timer callback 
			gSpin.x = -90;
			gSpin.y = 23;

#endif
			//?????====== Вычисление размаха изображаемого объекта
			m_fRangeY = 2*gRad;
			m_fRangeX = 2*gRad;
			m_fRangeZ = 2*gRad;

			//== Начальные значения квантов смещения (для анимации)
//			m_dx = m_dy = m_dz = 0.f;
			//====== Угол зрения для матрицы проекции
//			m_AngleView = 45.f;
			//====== Начальное смещение относительно центра сцены
			//====== Сдвиг назад на полуторный размер объекта
//			m_zTrans = -1.5f*(float)m_fRangeX;
			m_xTrans = 0.f;
			m_yTrans = 0.f;


			m_AngleX = -90;
			m_AngleY = 23;
			//====== Начальный разворот изображения
			m_AngleX = 90.f;
			m_AngleY = 180.f;
			m_AngleZ = 0.f;
MessageBox(0,"3","",0);

		}
		break;
	case WM_TIMER:
		{
			switch(wParam)
			{
#ifdef USE_EARTH_ROTATE
			case IDT_TIMER_GEOID:
				{
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
				}
				break;
#endif
			case IDT_TIMER_SURF:
			//====== Если это был наш таймер
				//====== Увеличиваем углы поворота
				m_AngleX += m_dy;
				m_AngleY += m_dx;
				//====== Ограничители роста углов
				if (m_AngleX > 360)
					m_AngleX -= 360;
				if (m_AngleX <-360)
					m_AngleX += 360;

				if (m_AngleY > 360)
					m_AngleY -= 360;
				if (m_AngleY <-360)
					m_AngleY += 360;

				//====== Просим перерисовать окно
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
				break;
			}
		}
		break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
/*			case IDM_OPEN_EARTHQUAKES:
				{
					OpenEarhquakes(hWnd);
				}
				break;*/
				case ID_GEOID_EARTHQUAKES:
					{
					}
				   break;
/*				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;*/
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_ERASEBKGND:
			{
				return true;
			}
			break;
		case WM_SIZE:
			{
				LRESULT lrez = DefWindowProc(hWnd, message, wParam, lParam);
#if 0
				glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
#else
				int wh;
				if (true)
					wh = LOWORD(lParam) < HIWORD(lParam) ?
						LOWORD(lParam) : HIWORD(lParam);
				else
					wh = LOWORD(lParam) > HIWORD(lParam) ?
						LOWORD(lParam) : HIWORD(lParam);


				glViewport(0, 0, wh, wh);
#endif
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
				return lrez;
			}
			break;
		case WM_PAINT:
#ifdef USE_EARTH_ROTATE
			hdc = BeginPaint(hWnd, &ps);
				 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				//=== Сейчас текущей является матрица моделирования
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				//====== Учет вращения	
				glRotated(gSpin.x, 1., 0,  0.);
				glRotated(gSpin.y, 0., 1., 0.);
				glRotated(gSpin.z, 0., 0., 1.);

				//====== Вызов списка рисующих команд	
				glCallList(1);
				
				//====== Подготовка следующей позиции сферы
				gSpin += gShift;

				SwapBuffers(m_hdc);
			EndPaint(hWnd, &ps);
#else
                 BeginPaint( hWnd, &ps );
				 				
				 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();


				//====== Формирование матрицы моделирования
				glTranslatef(m_xTrans,m_yTrans,m_zTrans);
				
				//====== Учет вращения	
				glRotatef (-m_AngleX, 1.0f, 0.0f, 0.0f );
				glRotatef (m_AngleZ, 0.0f, 1.0f, 0.0f );
				glRotatef (-m_AngleY, 0.0f, 0.0f, 1.0f );

				//====== Вызов списка рисующих команд	
				glCallList(1);
				//glCallList(2);

				

				SwapBuffers(m_hdc);

                 EndPaint( hWnd, &ps );
#endif
			break;
		case WM_LBUTTONDBLCLK:
			{
				MessageBox(0,"","WM_LBUTTONDBLCLK",0);
				//====== Начальное смещение относительно центра сцены
				//====== Сдвиг назад на полуторный размер объекта
				m_zTrans = -1.5f*(float)m_fRangeX;
				m_xTrans = 0.f;
				m_yTrans = 0.f;
			}
			break;
		case WM_RBUTTONDOWN :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//====== Запоминаем факт нажатия правой кнопки
				m_bRightButton = true;

				//====== Воспроизводим реакцию на левую кнопку
				//====== Останавливаем таймер
				KillTimer(hWnd,IDT_TIMER_SURF);

				//====== Обнуляем кванты перемещения
				m_dx = 0.f;
				m_dy = 0.f;

				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				m_pt.x = xPos;
				m_pt.y = yPos;
			}
			break;

		case WM_LBUTTONDOWN :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//====== Останавливаем таймер
				KillTimer(hWnd,IDT_TIMER_SURF);

				//====== Обнуляем кванты перемещения
				m_dx = 0.f;
				m_dy = 0.f;

				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				m_pt.x = xPos;
				m_pt.y = yPos;
			}
			break;
		case WM_LBUTTONUP :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				if (m_bCaptured)
				{
					//=== то анализируем желаемый квант перемещения
					//=== на превышение порога чувствительности
					if (fabs(m_dx) > 0.5f || fabs(m_dy) > 0.5f)
						//=== Включаем режим постоянного вращения
						SetTimer(hWnd,
						/*m_nView * 2 + 1*/IDT_TIMER_SURF,
						33,	                // 10-second interval 
					(TIMERPROC) NULL);     // no timer callback 

					else
						//=== Выключаем режим постоянного вращения
						KillTimer(hWnd, /*m_nView * 2 +1*/IDT_TIMER_SURF);

					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
		case WM_RBUTTONUP :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//====== Правая кнопка отпущена
				m_bRightButton = false;
				//====== Снимаем флаг захвата мыши
				m_bCaptured = false;
				//====== Отпускаем сообщения мыши
				ReleaseCapture();
			}
			break;
		case WM_MOUSEMOVE :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;

				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						// Вычисляем компоненты желаемой скорости вращения
						m_dy = float(yPos - m_pt.y)/40.f;
						m_dx = float(xPos - m_pt.x)/40.f;

						//====== Если одновременно была нажата Ctrl,
						if (wParam & MK_CONTROL)
						{
							//=== Изменяем коэффициенты сдвига изображения
							m_xTrans += m_dx;
							m_yTrans -= m_dy;
						}
						else
						{
							//====== Иначе, изменяем углы поворота
							m_AngleX += m_dy;
							m_AngleY += m_dx;
						}
						//=== В любом случае запоминаем новое положение мыши
						m_pt.x = xPos;
						m_pt.y = yPos;
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
					}
				}
				else
				{
					if	(wParam &  MK_RBUTTON )
					{
						if (m_bCaptured)		// Если был захват,
						{
							// Вычисляем компоненты желаемой скорости вращения
							m_dy = float(yPos - m_pt.y)/40.f;
							m_dx = float(xPos - m_pt.x)/40.f;

							//====== Если одновременно была нажата Ctrl,
							if (wParam & MK_CONTROL)
							{
								//=== Изменяем коэффициенты сдвига изображения
								m_xTrans += m_dx;
								m_yTrans -= m_dy;
							}
							else
							{
								//====== Усредняем величину сдвига
								m_zTrans += (m_dx + m_dy)/2.f;
							}
							//=== В любом случае запоминаем новое положение мыши
							m_pt.x = xPos;
							m_pt.y = yPos;
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
						}
					}
				}
			}
			break;
		case WM_MOUSEWHEEL :
			{
				int zDelta = (int) wParam; // wheel rotation 
				m_dz = float(zDelta) / 3000000.f;
				m_AngleZ += m_dz;

				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
			}
			break;
		case WM_DESTROY:
			if (m_hRC)
			{
				wglDeleteContext(m_hRC);
				m_hRC = 0;
			}
#ifdef USE_EARTH_ROTATE
			KillTimer(hWnd,IDT_TIMER_GEOID);
#endif
			KillTimer(hWnd,IDT_TIMER_SURF);

			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
