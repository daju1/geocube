
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


extern HINSTANCE hInst;   // ������� ���������
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



	// ����������� ������ �������� ���� ����������.
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
		if(1410 != GetLastError())// ����� ��� ����������
		{
			MessageBox(0,"!RegisterClassEx","WinGeoid",0);
			return( FALSE );
		}
	}

	// ����������� ������� �������� ���� MDI.
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
const UINT gnRings = 180;		// ���������� ����� (������)
const UINT gnSects = 360;		// ���������� ������ (�������)

//====== ����� ���������� �������������
const UINT gnTria = (gnRings) * gnSects * 2;

//====== ����� ���������� ������
const UINT gnVert = (gnRings) * gnSects + 2;

int ni = 1;
//====== ����� ���������� �������������
	UINT gnRingsi = gnRings*ni;		// ���������� ����� (������)
	UINT gnSectsi = gnSects*ni;		// ���������� ������ (�������)
	UINT gnTriai = (gnRingsi) * gnSectsi * 2;

//====== ����� ���������� ������
	UINT gnVerti = (gnRingsi) * gnSectsi + 2;

//====== ��� ����� ������
const COLORREF gClr1 = RGB(0, 255, 0);
const COLORREF gClr2 = RGB(0, 0, 255);

const double gRad = 2.5;			// ������ �����
const double gMax = 5.;			// ��������� ������
//const double PI = atan(1.)*4.; // ����� ��

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

					 //������ ������� �� ��������
					
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


				 // ��  ��������� ��������� ����� ����� � �������
					 int RowsP, ColsP;
					 RowsP = *((int *)pPaletteData);
					 ColsP = *((int *)pPaletteData+1);
					 //�������� ��������� �� ������ palette


					 BYTE*  pPaletteValues = 
						 (BYTE*)((int*)pPaletteData + 2);
					  //���� �������� � �������
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


					 // ��������� relief data.
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

					 // ��  ��������� ��������� ����� ����� � �������
					 int Rows, Cols;
					 Rows = *((int *)pReliefData);
					 Cols = *((int *)pReliefData+1);

					 //�������� ��������� �� ������ �������

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

	//====== ���������� ��������
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


					  //���� �������� � �������
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




					 //�������� ����� 
					 double delta=max-min;
					 double zero = 0;
					 int nCoastPalette = 36;
					 //�������� �������
					 int nColors = RowsP;
					 //int nColors = 2;
					 
					 //�������� ������ ��� ���������� ������ �������
					 /*BYTE *pBits = (BYTE*)HeapAlloc(GetProcessHeap(),
						 HEAP_ZERO_MEMORY,Rows*Cols);*/

					 BYTE **pBits = AllocByteMat (nyi, nxi);

					 //��������� ���������� ������
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

                       // ���������������� ��������� BITMAPINFOHEADER.
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



                       // ������������ ������ ��� ��������� BITMAPINFO.
                       //..........................................
                       lpbi = (BITMAPINFOHEADER*)HeapAlloc( GetProcessHeap(),
                                             HEAP_ZERO_MEMORY,
                                             sizeof(BITMAPINFOHEADER) + 
                                             256*sizeof(RGBQUAD) 
                                             //RowsP*sizeof(RGBQUAD) 
											 );

                       // ����������� ��������� bi � ������� ����� 						   // ��������� BITMAPINFO.
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


	//====== ������������ ������� ������
	//====== �������� �����
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

	//=== ������ �������, ��������� �� �������� �������
	double B,//������������� ������
		L,// ������������� �������
		N;// ������ �������� ������� ��������� � ����������� �� ������
						

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


	//=== ���� �� �������
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
		//=== ���������� z ��������� ��� ����� ������
	
			//z  = gRad * cos(B),
			z = N * sin(B) * (1 - e*e);
				//====== ��������������� �����
				//xy = gRad * sin(B);
		double	xy = N * cos(B);
		nL = 0;

		//====== ���� �� ������� (�������)
//		for (L = dL/2.0; L <= Lf; L += dL)
		for (c = 0; c < nxi; c++)
		{
			L = xi_[c];
			nL++;
			nn++;
			n++;
			// ���������� �������� � �������������� ���������
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			double
			//		x = xz * sin(L),
			//		y = xz * cos(L);
					x = xy * cos(L),
					y = xy * sin(L);

			nn = (nB-1)*gnSects+nL;
			//====== �������, ������� � ����

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
	//====== ������ ��������� ������� (�� ����� ������)
					 MessageBox(0,"5","",0);
	
//	UINT last = gnVert - 1;//((gnRings+1) * gnSects + 2) 
	UINT last = n + 1;
	//====== ����� �����

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

	//====== ������������ ������� ��������
	//====== ������������ ������ �������
	for (n = 0; n < gnSectsi; n++)
	{
		//====== ������ ����� ������� (�������� �����)
		t[n].i1 = 0;
		//====== ������ ������� �������
		t[n].i2 = n + 1;
		//====== ���������
		t[n].i3 = n == gnSectsi - 1 ? 1 : n + 2;
		//====== ������ ����� ������� (����� �����)
		t[gnTriai-gnSectsi+n].i1 = gnVerti - 1;
		t[gnTriai-gnSectsi+n].i2 = gnVerti - 2 - n;
		t[gnTriai-gnSectsi+n].i3 = gnVerti - 2
								- ((1 + n) % gnSectsi);
	}
	
	//====== ������������ ��������� �����
	//====== �������, ��������� �� �������
	int k = 1;

	//====== gnSects - ����� ���������� ������������
	n = gnSectsi;
	for (UINT i = 0; i < gnRingsi-1; i++, k += gnSectsi)
	{
		for (UINT j = 0; j < gnSectsi; j++, n += 2)
		{
			//======= ������ ����� �������
			t[n].i1 = k + j;
			//======= ������ ������� �������
			t[n].i2 = k + gnSectsi + j;
			//======= ���������
			t[n].i3 = k + gnSectsi + ((j + 1) % gnSectsi);
			//======= �� �� ��� ������� ������������
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




//====== ������ ����� �������� ������ ���� ����
CPoint3 gSpin;

//====== ������ ��������� �������� ������� gSpin
CPoint3 gShift;



/*inline double Rand(double x)
{
	//====== ��������� ����� � ��������� (-x, x)
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

	 // ��������� relief data.
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

	 // ��  ��������� ��������� ����� ����� � �������
	 int Rows, Cols;
	 Rows = *((int *)pReliefData);
	 Cols = *((int *)pReliefData+1);
	 //�������� ��������� �� ������ �������

	 int*  pReliefValues = 
		 (int*)((int*)pReliefData + 2);

	//====== �������� �����
	double 
		a = 6378245.,
		b = 6356863.0188,
		e = sqrt(a*a - b*b) / a;

	double 	N;// ������ �������� ������� ��������� � ����������� �� ������
	N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) );
	//z  = gRad * cos(B),
	z = N * sin(B) * (1 - e*e);
				//====== ��������������� �����
				//xy = gRad * sin(B);
	double	xy = N * cos(B);
			// ���������� �������� � �������������� ���������
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
	
	//������ ������� �� ��������
					
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
	
	// ��  ��������� ��������� ����� ����� � �������
	int RowsP, ColsP;
	RowsP = *((int *)pPaletteData);
	ColsP = *((int *)pPaletteData+1);
	
	//�������� ��������� �� ������ palette
	BYTE*  pPaletteValues = 
		(BYTE*)((int*)pPaletteData + 2);
	//���� �������� � �������
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

	// ��������� relief data.
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

	// ��  ��������� ��������� ����� ����� � �������
	int Rows, Cols;
	Rows = *((int *)pReliefData);
	Cols = *((int *)pReliefData+1);

	//�������� ��������� �� ������ �������
	int*  pReliefValues = 
	 (int*)((int*)pReliefData + 2);
	//���� �������� � �������
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
	//�������� ����� 
	int delta=max-min;
	int zero = 0;
	int nCoastPalette = 36;
	//�������� �������
	int nColors = RowsP;
				 
	//�������� ������ ��� ���������� ������ �������
	BYTE *pBits = (BYTE*)HeapAlloc(GetProcessHeap(),
		HEAP_ZERO_MEMORY,Rows*Cols);
	//��������� ���������� ������
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


	// ���������������� ��������� BITMAPINFOHEADER.
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



	// ������������ ������ ��� ��������� BITMAPINFO.
	//..........................................
	lpbi = (BITMAPINFOHEADER*)HeapAlloc( GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		sizeof(BITMAPINFOHEADER) + 
		256*sizeof(RGBQUAD) 
		);

	// ����������� ��������� bi � ������� ����� 
	// ��������� BITMAPINFO.
	//........................................
	*lpbi = bi;

	LPBITMAPINFO lpBi = (LPBITMAPINFO)lpbi;
	for(r = 0; r<RowsP; r++)
	{
		lpBi->bmiColors[r].rgbRed = BYTE(pPaletteValues[ColsP*r+0]);
		lpBi->bmiColors[r].rgbGreen = BYTE(pPaletteValues[ColsP*r+1]);
		lpBi->bmiColors[r].rgbBlue  = BYTE(pPaletteValues[ColsP*r+2]);
	}


	//====== ������������ ������� ������
	//====== �������� �����
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
	//====== ���������� ��������
	double	dB = PI / (gnRings),
			dL = 2.* PI / gnSects,
			Bf = PI/2.0 - dB/2.,
			Lf = 2.* PI - dL/2.0;

	//=== ������ �������, ��������� �� �������� �������
	double B,//������������� ������
		L,// ������������� �������
		N;// ������ �������� ������� ��������� � ����������� �� ������
						
			

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

	//=== ���� �� �������
	for (B = Bf;  B >= -Bf-.0000001;  B -= dB)
	{
		//N = a / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		//x = N * cos(B) * cos(L),
		//y = N * cos(B) * sin(L),
		//z = N * sin(B) * (1 - e*e);
		N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		nB++;
		//=== ���������� z ��������� ��� ����� ������
	
			//z  = gRad * cos(B),
			z = N * sin(B) * (1 - e*e);
				//====== ��������������� �����
				//xy = gRad * sin(B);
		double	xy = N * cos(B);
		nL = 0;

		//====== ���� �� ������� (�������)
		for (L = dL/2.0; L <= Lf; L += dL)
		{
			nL++;
			nn++;
			n++;
			// ���������� �������� � �������������� ���������
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			double
			//		x = xz * sin(L),
			//		y = xz * cos(L);
					x = xy * cos(L),
					y = xy * sin(L);

			nn = (nB-1)*gnSects+nL;
			//====== �������, ������� � ����

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
	//====== ������ ��������� ������� (�� ����� ������)
	
	UINT last = n + 1;
	//====== ����� �����

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

	//====== ������������ ������� ��������
	//====== ������������ ������ �������
	for (n = 0; n < gnSects; n++)
	{
		//====== ������ ����� ������� (�������� �����)
		t[n].i1 = 0;
		//====== ������ ������� �������
		t[n].i2 = n + 1;
		//====== ���������
		t[n].i3 = n == gnSects - 1 ? 1 : n + 2;
		//====== ������ ����� ������� (����� �����)
		t[gnTria-gnSects+n].i1 = gnVert - 1;
		t[gnTria-gnSects+n].i2 = gnVert - 2 - n;
		t[gnTria-gnSects+n].i3 = gnVert - 2
								- ((1 + n) % gnSects);
	}
	
	//====== ������������ ��������� �����
	//====== �������, ��������� �� �������
	int k = 1;

	//====== gnSects - ����� ���������� ������������
	n = gnSects;
	for (UINT i = 0; i < gnRings-1; i++, k += gnSects)
	{
		for (UINT j = 0; j < gnSects; j++, n += 2)
		{
			//======= ������ ����� �������
			t[n].i1 = k + j;
			//======= ������ ������� �������
			t[n].i2 = k + gnSects + j;
			//======= ���������
			t[n].i3 = k + gnSects + ((j + 1) % gnSects);
			//======= �� �� ��� ������� ������������
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

	// ��������� ��������� �����������.
	//.................
	hRes = LoadResource( hInst,
			FindResource( hInst, pBitmap, RT_BITMAP ) );

	lpBi = (LPBITMAPINFO)LockResource( hRes );

	// ���������� ����������� ���������� ������.
	//..................................
	if ( lpBi->bmiHeader.biClrUsed != 0 )
	{
		nColorData = lpBi->bmiHeader.biClrUsed;
	}
	else
	{
		switch( lpBi->bmiHeader.biBitCount )
		{
			case 1  : { nColorData = 2;  }  break; // ����������� 										    // �����������
			case 4  : { nColorData = 16; }  break; // VGA
			case 8  : { nColorData = 256;}  break; // SVGA
			case 24 : { nColorData = 0;  }  break; // ������ True Color
		}
	}

	// ����� ������ ���������� �����������.
	//........................
	lpBits  =  (LPSTR) lpBi;
	lpBits +=  lpBi->bmiHeader.biSize +
		( nColorData*sizeof(RGBQUAD) );

	int ngor = lpBi->bmiHeader.biWidth;
	int nver = lpBi->bmiHeader.biHeight;

	//====== ������������ ������� ������
	//====== �������� �����
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

	//====== ���������� ��������
	double	dB = PI / (gnRings + 2.),
			dL = 2. * PI / gnSects,
			Bf = PI - dB/2.,
			Lf = 2. * PI - dL/2.;

	//=== ������ �������, ��������� �� �������� �������
	UINT n = 1;
	double B,//������������� ������
		L,// ������������� �������
		N;// ������ �������� ������� ��������� � ����������� �� ������


	//=== ���� �� �������
	int nB = 0,nL = 0, nn = 0;
	for (B =  dB - Bf/2. ;  B < Bf/2.;  B += dB)
	{
		//N = a / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		//x = N * cos(B) * cos(L),
		//y = N * cos(B) * sin(L),
		//z = N * sin(B) * (1 - e*e);
		N = gRad / ( sqrt(1. - e*e * sin(B)*sin(B)) ),
		nB++;
		//=== ���������� z ��������� ��� ����� ������
	
			//z  = gRad * cos(B),
			z = N * sin(B) * (1 - e*e);
				//====== ��������������� �����
				//xy = gRad * sin(B);
		double	xy = N * cos(B);
		nL = 0;

		//====== ���� �� ������� (�������)
		for (L = -Lf/2.; L < Lf/2.; n++, L += dL)
		{
			nL++;
			nn++;
			// ���������� �������� � �������������� ���������
			//x = N * cos(B) * cos(L),
			//y = N * cos(B) * sin(L),
			double
			//		x = xz * sin(L),
			//		y = xz * cos(L);
					x = xy * cos(L),
					y = xy * sin(L);
			//====== �������, ������� � ����
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
	//====== ������ ��������� ������� (�� ����� ������)
	UINT last = gnVert - 1;
	//====== ����� �����
	v[last].v = CPoint3 (0, 0, zpol);
	v[last].n = CPoint3 (0, 0, 1);
	//v[last].c = gnVert & 1 ? gClr2 : gClr1;
	ipalette = int(*(((BYTE*)lpBits)+last));
	v[last].c = RGB(
		lpBi->bmiColors[ipalette].rgbRed,
		lpBi->bmiColors[ipalette].rgbBlue,
		lpBi->bmiColors[ipalette].rgbBlue);

	//====== ������������ ������� ��������
	//====== ������������ ������ �������
	for (n = 0; n < gnSects; n++)
	{
		//====== ������ ����� ������� (�������� �����)
		t[n].i1 = 0;
		//====== ������ ������� �������
		t[n].i2 = n + 1;
		//====== ���������
		t[n].i3 = n == gnSects - 1 ? 1 : n + 2;
		//====== ������ ����� ������� (����� �����)
		t[gnTria-gnSects+n].i1 = gnVert - 1;
		t[gnTria-gnSects+n].i2 = gnVert - 2 - n;
		t[gnTria-gnSects+n].i3 = gnVert - 2
								- ((1 + n) % gnSects);
	}
	
	//====== ������������ ��������� �����
	//====== �������, ��������� �� �������
	int k = 1;

	//====== gnSects - ����� ���������� ������������
	n = gnSects;
	for (UINT i = 0; i < gnRings; i++, k += gnSects)
	{
		for (UINT j = 0; j < gnSects; j++, n += 2)
		{
			//======= ������ ����� �������
			t[n].i1 = k + j;
			//======= ������ ������� �������
			t[n].i2 = k + gnSects + j;
			//======= ���������
			t[n].i3 = k + gnSects + ((j + 1) % gnSects);
			//======= �� �� ��� ������� ������������
			t[n + 1].i1 = t[n].i1;
			t[n + 1].i2 = t[n].i3;
			t[n + 1].i3 = k + ((j + 1) % gnSects);
		}
	}
}
void InitSphere(int nlist = 1, int alpha = 255)
{
	//=== ���� ���� (�� ��� ��� ����������� ������)
	glClearColor (0.00f, 0.0f, 0.45f, 0.1f);

#if 0
	glShadeModel (GL_FLAT);
#else
	glShadeModel (GL_SMOOTH);
#endif
	//======== ��������� ������ ���������� ���������
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//====== ����������� ������������� ����� �����
	glEnable(GL_LIGHTING);
	//====== ����������� ������ � ������������ �������� �����
	glEnable(GL_LIGHT0);
	//====== ���������� ��������� ������� (��� Z)
	glEnable(GL_DEPTH_TEST);

	//====== �������� ���� ����� ��������� �������
	glEnable(GL_COLOR_MATERIAL);

	// ������ ��� ������� ��������� ���������� ������������
	float v[4] =
	{
		0.05f, 0.05f, 0.05f, 1.f
	};

	//=== ������� ������ �������� ���������� ������������
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, v);

	//====== �������� ������
	v[0] = 0.9f;
	v[1] = 0.9f;
	v[2] = 0.9f;

	//====== ������ �������� ��������� ������������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, v);

	//======= �������� ������
	v[0] = 0.6f;
	v[1] = 0.6f;
	v[2] = 0.6f;

	//====== ������ ���������� �������� ����������
	glMaterialfv(GL_FRONT, GL_SPECULAR, v);

	//====== ������ ������� ���������� ���������
	glMateriali(GL_FRONT, GL_SHININESS, 40);

	//====== �������� ������
	v[0] = 1.f;
	v[1] = 1.f;
	v[2] = 5.f;
	v[3] = 0.f;

	//====== ������ ������� ��������� �����
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	//====== ������������� �� ������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//====== ������ ��� ��������
	gluPerspective(45, 1, .0001, 100);

	//=== �������� ����� ����������, ����������� ��
	//=== ������ ����� � ����������� ��� z �� 8 ������
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

	//====== ������������� �� ������� �������������
	glMatrixMode(GL_MODELVIEW);


	//====== ���������������� ��������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//====== ��������� OpenGL �� ������������� ��������
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//====== ������ ������ ��� ������������ �������
	VERT *Vert = new VERT[gnVerti];
	TRIA *Tria = new TRIA[gnTriai];

	//====== �������� �����������
	//Sphere(Vert, Tria);
	Sphere2(Vert, Tria, alpha);
	//Sphere3(Vert, Tria, alpha);


	//====== ������� ������� ���� �������� (������,
	//====== �������� � ������),
	//====== � ����� ���� ����������� �� ���
	glVertexPointer(3, GL_PRECISION, sizeof(VERT), &Vert->v);
	glNormalPointer(GL_PRECISION, sizeof(VERT), &Vert->n);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT),
													&Vert->c);
	
	srand((unsigned int)time(0));		// ���������� ���
	gShift = CPoint3 (Rand(gMax),Rand(gMax),Rand(gMax));
	gShift = CPoint3 (0,0,-1);


	//====== ������������ ������ �������� ������
	glNewList(nlist, GL_COMPILE);
		glDrawElements(GL_TRIANGLES, gnTriai*3,
							GL_UNSIGNED_INT, Tria);
	glEndList();

	//== ������������ ������, ��� ��� ������ �����������
	delete [] Vert;
	delete [] Tria;
}

LRESULT CALLBACK WinGeoidProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static	HGLRC		m_hRC;				// �������� OpenGL
	static	HDC			m_hdc; 			// �������� Windows
	static char * pBitmap;
	static HPALETTE hPalette;
	static int      nColorData;

	static GLfloat	m_dx;				// ����� �������� ����� X
	static GLfloat	m_dy;				// ����� �������� ����� Y
	static GLfloat	m_dz;				// ����� �������� ����� Z
	
	static bool		m_bCaptured;		// ������� ������� ����
	static bool		m_bRightButton;	// ���� ������ ������ ����
	static bool		m_bQuad;			// ���� ������������� GL_QUAD
	static tagPOINT		m_pt;				// ������� ������� ����
	
	static GLfloat	m_AngleView;		// ���� �����������
	static GLfloat	m_xTrans;			// C������� ����� X
	static GLfloat	m_yTrans;			// C������� ����� Y
	static GLfloat	m_zTrans;			// C������� ����� Z
	static GLfloat	m_AngleX;			// ���� �������� ������ ��� X
	static GLfloat	m_AngleY;			// ���� �������� ������ ��� Y
	static GLfloat	m_AngleZ;			// ���� �������� ������ ��� Z

	static GLdouble	m_fRangeX;		// ������ ������� ����� X
	static GLdouble	m_fRangeY;		// ������ ������� ����� Y
	static GLdouble	m_fRangeZ;		// ������ ������� ����� Z

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
			PIXELFORMATDESCRIPTOR pfd =	// ��������� �������
			{
				sizeof(PIXELFORMATDESCRIPTOR),// ������ ���������
				1,							// ����� ������
				PFD_DRAW_TO_WINDOW |	// ��������� GDI
				PFD_SUPPORT_OPENGL |	// ��������� OpenGL
				PFD_DOUBLEBUFFER,		// ������� �����������
				PFD_TYPE_RGBA,			// ������ RGBA, �� �������
				24, 						// ���������� ����������
		 									// � ������ ������ �����
				24,	0,						// ��� ���������� Red
				24,	0,						// ��� ���������� Green
				24,	0,						// ��� ���������� Blue
				24,	0,						// ��� ���������� Alpha
				0,							// ���������� ����������
											// ������ Accumulation
				0,			 				// �� �� ��� ���������� Red
				0,			 				// ��� ���������� Green
				0,							// ��� ���������� Blue
				0,							// ��� ���������� Alpha
				32, 						// ������� Z-������
				0,							// ������� ������ Stencil
				0,							// ������� ������ Auxiliary
				0,				 			// ������ ������������
				0,							// ���������� ����������
				0,							// ������ ������������
				0,							// ���� ���������� �����
				0							// ������ ������������
			};

			//====== �������� �������� ��������
			m_hdc = ::GetDC(hWnd);

			//====== ������ ������� ��������� ����������� ������
			int iD = ChoosePixelFormat(m_hdc, &pfd);
			if ( !iD )
			{
				MessageBox(hWnd,"ChoosePixelFormat::Error","On Create",0);
				return 0;
			}

			//====== �������� ���������� ���� ������
			if ( !SetPixelFormat (m_hdc, iD, &pfd) )
			{
				MessageBox(hWnd,"SetPixelFormat::Error","On Create Wingeoid",0);
				return 0;
			}

			//====== �������� ������� �������� �������� OpenGL
			if ( !(m_hRC = wglCreateContext (m_hdc)))
			{
				MessageBox(hWnd,"wglCreateContext::Error","On Create",0);
				return 0;
			}

			//====== �������� ������� ��� � �������� ��������
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

			//glRotated(5.0, 0.0, 1.0, 5.0);//�������
			glPushMatrix();//������� � ����� �����������, �������� ������
			//glRotated(-90,1.0,1.0,5.0);//��� ��� �������
			glTranslated(1,1,1);
			gluSphere(pSphere, 1.0, 10, 10) ;//������ ����� 
			glPopMatrix(); //������������ � ������ ����������� 
			gluDeleteQuadric(pSphere);

			GLUquadricObj* pCylinder = gluNewQuadric();
			gluQuadricDrawStyle(pCylinder, GLU_LINE);
			//glRotated(5.0, 0.0, 1.0, 5.0);//�������
			glPushMatrix();//������� � ����� �����������, �������� ������
			//glRotated(-90,1.0,1.0,5.0);//��� ��� �������
			glTranslated(2,2,2);
			gluCylinder(pCylinder, 2., 0., 2., 10, 10);
			glPopMatrix(); //������������ � ������ ����������� 
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
			//?????====== ���������� ������� ������������� �������
			m_fRangeY = 2*gRad;
			m_fRangeX = 2*gRad;
			m_fRangeZ = 2*gRad;

			//== ��������� �������� ������� �������� (��� ��������)
//			m_dx = m_dy = m_dz = 0.f;
			//====== ���� ������ ��� ������� ��������
//			m_AngleView = 45.f;
			//====== ��������� �������� ������������ ������ �����
			//====== ����� ����� �� ���������� ������ �������
//			m_zTrans = -1.5f*(float)m_fRangeX;
			m_xTrans = 0.f;
			m_yTrans = 0.f;


			m_AngleX = -90;
			m_AngleY = 23;
			//====== ��������� �������� �����������
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
			//====== ���� ��� ��� ��� ������
				//====== ����������� ���� ��������
				m_AngleX += m_dy;
				m_AngleY += m_dx;
				//====== ������������ ����� �����
				if (m_AngleX > 360)
					m_AngleX -= 360;
				if (m_AngleX <-360)
					m_AngleX += 360;

				if (m_AngleY > 360)
					m_AngleY -= 360;
				if (m_AngleY <-360)
					m_AngleY += 360;

				//====== ������ ������������ ����
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
				//=== ������ ������� �������� ������� �������������
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				//====== ���� ��������	
				glRotated(gSpin.x, 1., 0,  0.);
				glRotated(gSpin.y, 0., 1., 0.);
				glRotated(gSpin.z, 0., 0., 1.);

				//====== ����� ������ �������� ������	
				glCallList(1);
				
				//====== ���������� ��������� ������� �����
				gSpin += gShift;

				SwapBuffers(m_hdc);
			EndPaint(hWnd, &ps);
#else
                 BeginPaint( hWnd, &ps );
				 				
				 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();


				//====== ������������ ������� �������������
				glTranslatef(m_xTrans,m_yTrans,m_zTrans);
				
				//====== ���� ��������	
				glRotatef (-m_AngleX, 1.0f, 0.0f, 0.0f );
				glRotatef (m_AngleZ, 0.0f, 1.0f, 0.0f );
				glRotatef (-m_AngleY, 0.0f, 0.0f, 1.0f );

				//====== ����� ������ �������� ������	
				glCallList(1);
				//glCallList(2);

				

				SwapBuffers(m_hdc);

                 EndPaint( hWnd, &ps );
#endif
			break;
		case WM_LBUTTONDBLCLK:
			{
				MessageBox(0,"","WM_LBUTTONDBLCLK",0);
				//====== ��������� �������� ������������ ������ �����
				//====== ����� ����� �� ���������� ������ �������
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
				//====== ���������� ���� ������� ������ ������
				m_bRightButton = true;

				//====== ������������� ������� �� ����� ������
				//====== ������������� ������
				KillTimer(hWnd,IDT_TIMER_SURF);

				//====== �������� ������ �����������
				m_dx = 0.f;
				m_dy = 0.f;

				//====== ����������� ��������� ����,
				//====== ��������� �� � ���� ����
				SetCapture(hWnd);
				//====== ���������� ���� �������
				m_bCaptured = true;
				//====== ���������� ���������� �������
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
				//====== ������������� ������
				KillTimer(hWnd,IDT_TIMER_SURF);

				//====== �������� ������ �����������
				m_dx = 0.f;
				m_dy = 0.f;

				//====== ����������� ��������� ����,
				//====== ��������� �� � ���� ����
				SetCapture(hWnd);
				//====== ���������� ���� �������
				m_bCaptured = true;
				//====== ���������� ���������� �������
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
					//=== �� ����������� �������� ����� �����������
					//=== �� ���������� ������ ����������������
					if (fabs(m_dx) > 0.5f || fabs(m_dy) > 0.5f)
						//=== �������� ����� ����������� ��������
						SetTimer(hWnd,
						/*m_nView * 2 + 1*/IDT_TIMER_SURF,
						33,	                // 10-second interval 
					(TIMERPROC) NULL);     // no timer callback 

					else
						//=== ��������� ����� ����������� ��������
						KillTimer(hWnd, /*m_nView * 2 +1*/IDT_TIMER_SURF);

					//====== ������� ���� ������� ����
					m_bCaptured = false;
					//====== ��������� ��������� ����
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
				//====== ������ ������ ��������
				m_bRightButton = false;
				//====== ������� ���� ������� ����
				m_bCaptured = false;
				//====== ��������� ��������� ����
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
					if (m_bCaptured)		// ���� ��� ������,
					{
						// ��������� ���������� �������� �������� ��������
						m_dy = float(yPos - m_pt.y)/40.f;
						m_dx = float(xPos - m_pt.x)/40.f;

						//====== ���� ������������ ���� ������ Ctrl,
						if (wParam & MK_CONTROL)
						{
							//=== �������� ������������ ������ �����������
							m_xTrans += m_dx;
							m_yTrans -= m_dy;
						}
						else
						{
							//====== �����, �������� ���� ��������
							m_AngleX += m_dy;
							m_AngleY += m_dx;
						}
						//=== � ����� ������ ���������� ����� ��������� ����
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
						if (m_bCaptured)		// ���� ��� ������,
						{
							// ��������� ���������� �������� �������� ��������
							m_dy = float(yPos - m_pt.y)/40.f;
							m_dx = float(xPos - m_pt.x)/40.f;

							//====== ���� ������������ ���� ������ Ctrl,
							if (wParam & MK_CONTROL)
							{
								//=== �������� ������������ ������ �����������
								m_xTrans += m_dx;
								m_yTrans -= m_dy;
							}
							else
							{
								//====== ��������� �������� ������
								m_zTrans += (m_dx + m_dy)/2.f;
							}
							//=== � ����� ������ ���������� ����� ��������� ����
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
