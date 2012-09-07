//DrawScene.h
#ifndef DRAWSCENE_H
#define DRAWSCENE_H
class SurfDoc;


#include "StdAfx.h"
#include "DrawScene.h"
#include "SurfDoc.h"

#include "winsurftree.h"



#define LARGE_CUBE 0
void DrawCube(SurfDoc* pSurfDoc);

void DrawXYZCutPlanes(SurfDoc* pSurfDoc);

void DrawCutPlane(SurfDoc* pSurfDoc);

int Scale(double v[3]);

#define DRAW_ELEMENTS

void DrawPolygones(SurfDoc* pSurfDoc );

void DrawTriangles(SurfDoc* pSurfDoc );
void DrawObjects(SurfDoc* pSurfDoc );
void DrawCollections(SurfDoc* pSurfDoc );
void DrawNewSurf(SurfDoc* pSurfDoc);
void DrawNewFault(SurfDoc* pSurfDoc);

void DrawCubes(SurfDoc* pSurfDoc );
void DrawNewCube(SurfDoc* pSurfDoc);
void DrawSurfs(SurfDoc* pSurfDoc);
void DrawFaults(SurfDoc* pSurfDoc);
#if DFX_LAYER_FROM_OBJECT
void DrawDxf(SurfDoc* pSurfDoc );
#endif

void DrawGeoCatches(SurfDoc* pSurfDoc );
void DrawAutoBuildProfiles(SurfDoc* pSurfDoc );
void DrawGridData(SurfDoc* pSurfDoc );
void ReDrawGridData(SurfDoc* pSurfDoc );

void DrawGridProfiles(SurfDoc* pSurfDoc);

void DrawCutLines(SurfDoc* pSurfDoc);

void DrawLines(SurfDoc* pSurfDoc);
void DrawBlankLines(SurfDoc* pSurfDoc);

void DrawPoints(SurfDoc* pSurfDoc);

void DrawDrills(SurfDoc* pSurfDoc);
void ReDrawDrills(SurfDoc* pSurfDoc);

void DrawTriaGrid(SurfDoc* pSurfDoc);


void DrawStrings(SurfDoc* pSurfDoc);

//void ReDrawNewLine(SurfDoc* pSurfDoc);
void DrawNewLine(SurfDoc* pSurfDoc);

void DrawBrokenPlanes(SurfDoc* pSurfDoc);

void DrawBlnProfiles(SurfDoc* pSurfDoc);

void DrawNewSphere(SurfDoc* pSurfDoc);
void DrawNewGridDataItem(SurfDoc* pSurfDoc, GridData* pGridData);
void DrawSpheres(SurfDoc* pSurfDoc);

void DrawBitmaps(SurfDoc* pSurfDoc );
void DrawBmpProfiles(SurfDoc* pSurfDoc );
#endif