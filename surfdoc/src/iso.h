#include "points.h"
#include "Grid.h"


CPoint3 VertexInterp(double isolevel, Grid4 * cube, 
				  long nx1, long ny1, long nz1, 
				  long nx2, long ny2, long nz2, 
				  bool view);

void Polygonise(double isolevel, Grid4 * cube, 
				long nx, long ny, long nz, 
				long **** Ivert,
				int& ntria, TRIA * tria, 
				int& nvert, VERT * vert, 
				COLORREF c,
				bool  view);

void DrawIzoSurface(double isolevel, Grid4 * cube, COLORREF c);

// DIME: needed include files.
#include <dime/Model.h>
#include <dime/dxfwriter.h>
bool DrawIzoSurfaceToDxf(dimeModel & model, const dimeLayer * layer,
						 dimeBlock * block,
						 double isolevel, Grid4 * cube, COLORREF c, bool view);