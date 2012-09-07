#ifndef WINSURFTREE_H
#define WINSURFTREE_H

class SurfDoc;
class Line3D;
class Poligon3D;
class GeoCatch;
class ThePoint3D;
class GeoSurface;
class GridData;

#include "..\..\array\src\vect.h"

HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, BOOL fCheck, LPARAM lParam,
						HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, Object * pObject,
						HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
HTREEITEM AddObjectListItem(HWND hwndTV, LPSTR lpszItem, ObjectList* pObjectList,
							HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);

//void ReDrawItemOnTree(HWND hwndTV, HTREEITEM h, LPSTR lpszItem, Object * pObject);

BOOL TreeView_DeleteMyItem(HWND hwndTV, HTREEITEM& hitem);


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastGeoColomnToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddGeoColomnsToTree(HWND hwndTV, SurfDoc* pSurfDoc);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddCollectionsToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastCollectionToTree(HWND hwndTV, SurfDoc* pSurfDoc);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddObjectsToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastObjectToTree(HWND hwndTV, SurfDoc* pSurfDoc);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddAutoBuildProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastAutoBuildProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastSurfaceToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddSurfacesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#if DFX_LAYER_FROM_OBJECT
void AddDxfToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastDxfToTree(HWND hwndTV, SurfDoc* pSurfDoc);
#endif
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastGeoSurfaceToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddGeoSurfacesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastFaultToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddFaultsToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddLastGeoCatchToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddGeoCatchesToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddGridDataToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastGridDataToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddCubesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastCubeToTree(HWND hwndTV, SurfDoc* pSurfDoc);


void AddLastGridProfileToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddGridProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc);

//void UpdateLastLineOnTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLastLineToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLinesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddLinesToTree(HWND hwndTV, 
					vect<Line3D>* pvect, 
					ObjectList* pLinesObjectList);

//void AddCatPlaneLinesItem(HWND hwndTV, HTREEITEM h2, GeoSurface *p);

void AddLastCutLineToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddCutLinesToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddLastBlankLineToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddBlankLinesToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddWellsToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddBrokenPlanesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddStringsToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddPolygonesToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddLastGridDataToTree(HWND hwndTV, GridData* pGridData);
void AddLastSphereToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddSpheresToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddLastBitmapToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddBitmapsToTree(HWND hwndTV, SurfDoc* pSurfDoc);

void AddLastBmpProfileToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddBmpProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc);



void AddPointsToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddTrianglesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddTriangulatedGrid3DToTree(HWND hwndTV, SurfDoc* pSurfDoc);
void AddBlnProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc);
BOOL InitTreeViewItems(HWND hwndTV, SurfDoc* pSurfDoc) ;
BOOL InitTreeViewImageLists(HWND hwndTV) ;
HWND CreateATreeView(HWND hwndParent, SurfDoc* pSurfDoc) ;
void Main_OnBeginDrag(HWND hwndTV, LPNMTREEVIEW lpnmtv) ;
void Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) ;
void Main_OnLButtonUp(void) ;
BOOL TreeView_MySetCheckState(HWND hwndTreeView, HTREEITEM hItem, BOOL fCheck);
BOOL TreeView_MyGetCheckState(HWND hwndTreeView, HTREEITEM hItem);

LPARAM TreeView_GetLParam(HWND hwndTreeView, HTREEITEM hItem);
LPSTR TreeView_GetText(HWND hwndTreeView, HTREEITEM hItem);

void TreeView_EnumCheckedItems(HWND hwndTreeView, HTREEITEM hParentItem, LPARAM id, 
							   void (*  draw_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, LPARAM /*lParam*/),
							   void  (*  checking_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, BOOL /*bCheck*/, LPARAM /*lParam*/)
							   );
void TreeView_EnumCheckedItems(HWND hwndTreeView, HTREEITEM hParentItem, LPARAM id, 
							   void  (*  checking_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, BOOL /*bCheck*/, LPARAM /*lParam*/)
							   );
void TreeView_EnumCheckedItems(HWND hwndTreeView, HTREEITEM hParentItem, LPARAM id, 
							   void (*  draw_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, LPARAM /*lParam*/)
							   );

BOOL TreeView_DeleteMyItem(HWND hwndTV, HTREEITEM& hitem);

#endif