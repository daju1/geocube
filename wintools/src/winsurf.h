#ifndef WINSURF_H_INCLUDED
#define WINSURF_H_INCLUDED
//#include "..\resource.h"
#include "..\..\array\src\sorting.h"
#include "..\..\array\src\vdouble.h"
class SurfDoc;
typedef struct
{
	HWND		hWnd;
	SurfDoc*	pSurfDoc;
}	
SURFDLGDATA, *LPSURFDLGDATA;


WPARAM WinSurf();
WPARAM WinSurf(vector<int>& lines_break_indexes, vector<double>& x, vector<double>& y, vector<double>& z);
WPARAM WinSurf(vector<cut_of_line>& line_cutting_vector, 
			vector<double>& x, vector<double>& y, vector<double>& z);
WPARAM WinSurf(Vector<vdouble>& vx, Vector<vdouble>& vy, Vector<vdouble>& vz);
WPARAM WinSurf(Vector<int>& lines_break_indexes, vdouble& x, vdouble& y, vdouble& z);
WPARAM WinSurf(HWND &hSurfWnd, vdouble& x, vdouble& y, vdouble& z, int type = 0);
WPARAM WinSurf(HWND &hSurfWnd, vector<double>& x, vector<double>& y, vector<double>& z, int type = 0);
WPARAM WinSurf(vdouble& x, vdouble& y, vdouble& z, int type = 0);
WPARAM WinSurf(vector<cut_of_line>& line_cutting_vector, 
			int ix, int iy,
			vector<vector<double> >& data);
LRESULT CALLBACK AboutSurfCube(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinSurfProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK WinSurfParentProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
int BeginWinSurf(WNDCLASSEX &wc);
WPARAM StartWinSurf(HWND &hSurfWnd, void * pSurfDoc);
HWND CreateWinSurfWnd(void * pDoc);
WPARAM StartWinSurfLoop();

#endif