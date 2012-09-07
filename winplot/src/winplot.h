//#include "..\..\resource.h"
//#include <windows.h>
#include "Graph2.h"
WPARAM WinPlot(vdouble& x, vdouble& y);
WPARAM WinPlot(vdouble& x, vdouble& y);
WPARAM WinPlot(Vector<vdouble>& vx, Vector<vdouble>& vy);
WPARAM WinPlot(vector<vector<double> >& vx, vector<vector<double> >& vy);
WPARAM WinPlot(vector<double>& vx, vector<double>& vy);
WPARAM WinPlot(vector<double>& vx, vector<double>& vy, size_t i1, size_t i2);
LRESULT CALLBACK WinPlotProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );