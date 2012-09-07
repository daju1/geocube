/* winsurftree.cpp */

#include "StdAfx.h"
#include "SurfDoc.h"
#include "winsurftree.h"
extern HINSTANCE hInst;   // текущий экземпляр



// Global variables and constants 
// g_nOpen, g_nClosed, and g_nDocument - integer variables for 
// indexes of the images. 
// CX_BITMAP and CY_BITMAP - width and height of an icon. 
// NUM_BITMAPS - number of bitmaps to add to the image list. 

int 
g_nOpen = 0, 
g_nClosed = 0, 
g_nDocument = 0;

int NUM_BITMAPS = 3;
#define CX_BITMAP 16
#define CY_BITMAP 16

BOOL g_fDragging = FALSE;


// AddItemToTree - adds items to a tree-view control. 
// Returns the handle to the newly added item. 
// hwndTV - handle to the tree-view control. 
// lpszItem - text of the item to add. 
// nLevel - level at which to add the item. 
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, Object * pObject, HTREEITEM hParent, HTREEITEM hInsertAfter)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 
    HTREEITEM h; 

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
	if (pObject->m_bExpanded) tvi.mask |= TVIS_EXPANDED;

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 

    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = g_nDocument; 
    tvi.iSelectedImage = g_nDocument; 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)pObject; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hInsertAfter; 

    // Set the parent item based on the specified level. 
    tvins.hParent = hParent; 
	pObject->parentTreeItem = hParent;

    // Add the item to the tree-view control. 
    hPrev = (HTREEITEM)SendMessage(hwndTV, 
                                   TVM_INSERTITEM, 
                                   0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins); 

    // The new item is a child item. Give the parent item a 
    // closed folder bitmap to indicate it now has child items. 
    if (hParent != TVI_ROOT)
    { 
        h = TreeView_GetParent(hwndTV, hPrev); 
        tvi.hItem = h; 
        //TreeView_GetItem(hwndTV, &tvi); 
		tvi.iImage = g_nClosed; 
        tvi.iSelectedImage = g_nClosed; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
	TreeView_MySetCheckState(hwndTV, hPrev, pObject->m_bChecked);

	pObject->myTreeItem = hPrev;

    return hPrev; 
} 
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, BOOL fCheck, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 
    HTREEITEM h; 

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
//	if (pObject->m_bExpanded) tvi.mask |= TVIS_EXPANDED;

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 

    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = g_nDocument; 
    tvi.iSelectedImage = g_nDocument; 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)lParam; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hInsertAfter; 

    // Set the parent item based on the specified level. 
    tvins.hParent = hParent; 
	//pObject->parentTreeItem = hParent;

    // Add the item to the tree-view control. 
    hPrev = (HTREEITEM)SendMessage(hwndTV, 
                                   TVM_INSERTITEM, 
                                   0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins); 

    // The new item is a child item. Give the parent item a 
    // closed folder bitmap to indicate it now has child items. 
    if (hParent != TVI_ROOT)
    { 
        h = TreeView_GetParent(hwndTV, hPrev); 
        tvi.hItem = h; 
        //TreeView_GetItem(hwndTV, &tvi); 
		tvi.iImage = g_nClosed; 
        tvi.iSelectedImage = g_nClosed; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
	TreeView_MySetCheckState(hwndTV, hPrev, fCheck);

//	pObject->myTreeItem = hPrev;

    return hPrev; 
} 
/*void ReDrawItemOnTree(HWND hwndTV, HTREEITEM h, LPSTR lpszItem, Object * pObject)
{ 
    TVITEM tvi; 
    //TVINSERTSTRUCT tvins; 
    //static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 

	tvi.hItem = h; 
	TreeView_GetItem(hwndTV, &tvi);

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
	if (pObject->m_bExpanded) tvi.mask |= TVIS_EXPANDED;

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)pObject;

	//?????????????????????
		tvi.iImage = g_nClosed; 
        tvi.iSelectedImage = g_nClosed; 
	//?????????????????????

	TreeView_SetItem(hwndTV, &tvi); 

	TreeView_MySetCheckState(hwndTV, h, pObject->m_bChecked);

	//pObject->myTreeItem = h;
}*/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL TreeView_DeleteMyItem(HWND hwndTV, HTREEITEM& hitem)
{

	BOOL status = FALSE;
	if (hitem != NULL)
	{
 // printf("TreeView_DeleteMyItem(HTREEITEM& hitem = 0x%08x)\n", hitem);
		status = TreeView_DeleteItem(hwndTV, hitem);
		hitem = NULL;
	}
	return status;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
HTREEITEM AddObjectListItem(HWND hwndTV, LPSTR lpszItem, ObjectList* pObjectList,
							HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	//TreeView_DeleteMyItem(hwndTV, pObjectList->myTreeItem);
	if(pObjectList->size() > 0)
	{
		Object * pObject = dynamic_cast<Object *> (pObjectList);
		return  AddItemToTree(hwndTV, lpszItem, pObject, hParent, hInsertAfter); 
	}
	//printf("AddObjectListItem return NULL; pObjectList->size() %d\n", pObjectList->size());
	return NULL;
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddCollectionsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_collections_ObjectList.myTreeItem);
	//TreeView_DeleteAllItems(hwndTV);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Collections", &pSurfDoc->m_collections_ObjectList); 
	if (pSurfDoc->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_collections.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_collections.IncrementCurrentMsg());
	}
	//=============================================================
}
void AddLastCollectionToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_collections.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_collections_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Collections", &pSurfDoc->m_collections_ObjectList); 
		pSurfDoc->m_collections.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void AddObjectsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_objects_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Objects", &pSurfDoc->m_objects_ObjectList); 
	if (pSurfDoc->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_objects.GetCurrentMsg().AddItem_ToTree(hwndTV, h1, "");
		}
		while(pSurfDoc->m_objects.IncrementCurrentMsg());
	}
	//=============================================================
}
void AddLastObjectToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_objects.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_objects_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Objects", &pSurfDoc->m_objects_ObjectList); 
		pSurfDoc->m_objects.GetCurrentMsg().AddItem_ToTree(hwndTV, h1, "");
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/*void AddCatPlaneLinesItem(HWND hwndTV, HTREEITEM h2, GeoSurface *p)
{
	//=============================================================
	if (p->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "CutPlaneLines", &p->m_cutplane_lines_ObjectList, h2); 
		do
		{
			p->m_cutplane_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(p->m_cutplane_lines.IncrementCurrentMsg());
	}
	//=============================================================
}*/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastGeoColomnToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	map<GeoElement::type, GeoColomn>::reverse_iterator riter;
	riter = pSurfDoc->m_geo_colomns.rbegin(); 
	if (riter != pSurfDoc->m_geo_colomns.rend())
	{
		HTREEITEM& h1 = pSurfDoc->m_geo_colomns_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "GeoColomns", &pSurfDoc->m_geo_colomns_ObjectList); 
		(*riter).second.AddItem_ToTree(hwndTV,	h1);
	}
}

void AddGeoColomnsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_geo_colomns_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "GeoColomns", &pSurfDoc->m_geo_colomns_ObjectList); 
	
	map<GeoElement::type, GeoColomn>::iterator iter;
	for ( iter = pSurfDoc->m_geo_colomns.begin(); 
		iter != pSurfDoc->m_geo_colomns.end(); iter++ )
	{
		(*iter).second.AddItem_ToTree(hwndTV,	h1);
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastSurfaceToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_surfaces.SetCurrentMsgOnLast())
	{
		HTREEITEM& h1 = pSurfDoc->m_surfaces_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Surfaces", &pSurfDoc->m_surfaces_ObjectList); 
		pSurfDoc->m_surfaces.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
	}
}

void AddSurfacesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_surfaces_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Surfaces", &pSurfDoc->m_surfaces_ObjectList); 
	
	if (GeoSurface::s_bInverse_order_in_the_tree)
	{
		if (pSurfDoc->m_surfaces.SetCurrentMsgOnLast())
		{
			do
			{
				pSurfDoc->m_surfaces.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
			}
			while(pSurfDoc->m_surfaces.DecrementCurrentMsg());
		}
	}
	else
	{
		if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{
				pSurfDoc->m_surfaces.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
			}
			while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
		}
	}
	//=============================================================
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastFaultToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_faults.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_faults_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Faults", &pSurfDoc->m_faults_ObjectList); 
		pSurfDoc->m_faults.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
	}
}

void AddFaultsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_faults_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Faults", &pSurfDoc->m_faults_ObjectList); 
	if (pSurfDoc->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_faults.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_faults.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastGeoCatchToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_geo_catches.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_geo_catches_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "GeoCatches", &pSurfDoc->m_geo_catches_ObjectList); 
		pSurfDoc->m_geo_catches.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddGeoCatchesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_geo_catches_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "GeoCatches", &pSurfDoc->m_geo_catches_ObjectList); 
	if (pSurfDoc->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_geo_catches.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_geo_catches.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddCubesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_cubes_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Cubes", &pSurfDoc->m_cubes_ObjectList); 
	if (pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_cubes.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_cubes.IncrementCurrentMsg());
	}
	//=============================================================
}


void AddLastCubeToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_cubes.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_cubes_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Cubes", &pSurfDoc->m_cubes_ObjectList); 
		pSurfDoc->m_cubes.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddGridDataToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_grid_data_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "GridData", &pSurfDoc->m_grid_data_ObjectList); 
	if (pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_grid_data.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_grid_data.IncrementCurrentMsg());
	}
	//=============================================================
}


void AddLastGridDataToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_grid_data.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_grid_data_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "GridData", &pSurfDoc->m_grid_data_ObjectList); 
		pSurfDoc->m_grid_data.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#if DFX_LAYER_FROM_OBJECT
void AddDxfToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_dxfConverters_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Dxf", &pSurfDoc->m_dxfConverters_ObjectList); 
	if (pSurfDoc->m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_dxfConverters.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_dxfConverters.IncrementCurrentMsg());
	}
	//=============================================================
}
void AddLastDxfToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_dxfConverters.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_dxfConverters_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Dxf", &pSurfDoc->m_dxfConverters_ObjectList); 
		pSurfDoc->m_dxfConverters.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}
#endif
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddAutoBuildProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_auto_build_profiles_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "AutoBuildProfiles", &pSurfDoc->m_auto_build_profiles_ObjectList); 
	if (pSurfDoc->m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_auto_build_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_auto_build_profiles.IncrementCurrentMsg());
	}
	//=============================================================
}
void AddLastAutoBuildProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_auto_build_profiles.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_auto_build_profiles_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "AutoBuildProfiles", &pSurfDoc->m_auto_build_profiles_ObjectList); 
		pSurfDoc->m_auto_build_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastGridProfileToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_grid_profiles.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_grid_profiles_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "GridProfile", &pSurfDoc->m_grid_profiles_ObjectList); 
		pSurfDoc->m_grid_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
	}
}

void AddGridProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_grid_profiles_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "GridProfile", &pSurfDoc->m_grid_profiles_ObjectList); 
	if (pSurfDoc->m_grid_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_grid_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
		}
		while(pSurfDoc->m_grid_profiles.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void AddLastLineToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_lines.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_lines_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Lines", &pSurfDoc->m_lines_ObjectList); 
		pSurfDoc->m_lines.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
	}
}
/*
void UpdateLastLineOnTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_lines.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_lines_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Lines", &pSurfDoc->m_lines_ObjectList); 
		TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_lines.GetCurrentMsg().myTreeItem);
		pSurfDoc->m_lines.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
	}
}
*/
void AddLinesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_lines_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Lines", &pSurfDoc->m_lines_ObjectList); 
	if (pSurfDoc->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_lines.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
		}
		while(pSurfDoc->m_lines.IncrementCurrentMsg());
	}
	//=============================================================
}
void AddLinesToTree(HWND hwndTV, 
					vect<Line3D>* pvect, 
					ObjectList* pLinesObjectList)
{
	if (pvect && pLinesObjectList)
	{
		TreeView_DeleteMyItem(hwndTV,pLinesObjectList->myTreeItem);
		//=============================================================
		HTREEITEM h1 = AddObjectListItem(hwndTV, 
			"Lines", 
			pLinesObjectList,
			pLinesObjectList->parentTreeItem); 
		if (pvect->SetCurrentMsgOnFirst())
		{
			do
			{
				pvect->GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
			}
			while(pvect->IncrementCurrentMsg());
		}
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastCutLineToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_cutlines.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_cutlines_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "CutLines", &pSurfDoc->m_cutlines_ObjectList); 
		pSurfDoc->m_cutlines.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
	}
}

void AddCutLinesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_cutlines_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "CutLines", &pSurfDoc->m_cutlines_ObjectList); 
	if (pSurfDoc->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_cutlines.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
		}
		while(pSurfDoc->m_cutlines.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastBlankLineToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_blanklines.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_blanklines_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "BlankLines", &pSurfDoc->m_blanklines_ObjectList); 
		pSurfDoc->m_blanklines.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddBlankLinesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_blanklines_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "BlankLines", &pSurfDoc->m_blanklines_ObjectList); 
	if (pSurfDoc->m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_blanklines.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_blanklines.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastWellToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_drills.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_drills_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Wells", &pSurfDoc->m_drills_ObjectList); 
		pSurfDoc->m_drills.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddWellsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_drills_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Wells", &pSurfDoc->m_drills_ObjectList); 
	if (pSurfDoc->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_drills.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_drills.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastBrokenPlaneToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_brokenPlanes.SetCurrentMsgOnLast())
	{
		HTREEITEM& h1 = pSurfDoc->m_brokenPlanes_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "BrokenPlanes", &pSurfDoc->m_brokenPlanes_ObjectList);
		pSurfDoc->m_brokenPlanes.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
	}
}

void AddBrokenPlanesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_brokenPlanes_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "BrokenPlanes", &pSurfDoc->m_brokenPlanes_ObjectList); 
	if (pSurfDoc->m_brokenPlanes.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_brokenPlanes.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
		}
		while(pSurfDoc->m_brokenPlanes.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastStringToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_strings.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_strings_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Strings", &pSurfDoc->m_strings_ObjectList); 
		pSurfDoc->m_strings.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddStringsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_strings_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Strings", &pSurfDoc->m_strings_ObjectList); 
	if (pSurfDoc->m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_strings.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_strings.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastPolygoneToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_polygones.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_polygones_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Polygones", &pSurfDoc->m_polygones_ObjectList);
		pSurfDoc->m_polygones.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddPolygonesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_polygones_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Polygones", &pSurfDoc->m_polygones_ObjectList); 
	if (pSurfDoc->m_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_polygones.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_polygones.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastGridDataToTree(HWND hwndTV, GridData* pGridData)
{
	if (pGridData->m_input_points.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pGridData->m_input_points_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "GridData", &pGridData->m_input_points_ObjectList); 
		pGridData->m_input_points.GetCurrentMsg().AddItem_ToTree(hwndTV, h1, "");
	}
}
void AddLastSphereToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_spheres.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_spheres_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Spheres", &pSurfDoc->m_spheres_ObjectList); 
		pSurfDoc->m_spheres.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddSpheresToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_spheres_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Spheres", &pSurfDoc->m_spheres_ObjectList); 
	if (pSurfDoc->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_spheres.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_spheres.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastBmpProfileToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_bmp_profiles.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_bmp_profiles_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "BmpProfiles", &pSurfDoc->m_bmp_profiles_ObjectList); 
		pSurfDoc->m_bmp_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddBmpProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_bmp_profiles_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "BmpProfiles", &pSurfDoc->m_bmp_profiles_ObjectList); 
	if (pSurfDoc->m_bmp_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_bmp_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV,h1);
		}
		while(pSurfDoc->m_bmp_profiles.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastBitmapToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_bitmaps.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_bitmaps_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Bitmaps", &pSurfDoc->m_bitmaps_ObjectList);  
		pSurfDoc->m_bitmaps.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddBitmapsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_bitmaps_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Bitmaps", &pSurfDoc->m_bitmaps_ObjectList);
	if (pSurfDoc->m_bitmaps.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_bitmaps.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_bitmaps.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastPointToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_points.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_points_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Points", &pSurfDoc->m_points_ObjectList); 
		pSurfDoc->m_points.GetCurrentMsg().AddItem_ToTree(hwndTV,h1, "");
	}
}

void AddPointsToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_points_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Points", &pSurfDoc->m_points_ObjectList); 
	if (pSurfDoc->m_points.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_points.GetCurrentMsg().AddItem_ToTree(hwndTV, h1, "");
		}
		while(pSurfDoc->m_points.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastTriangleToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_triangles.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_triangles_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "Triangles", &pSurfDoc->m_triangles_ObjectList); 
		pSurfDoc->m_triangles.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddTrianglesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_triangles_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "Triangles", &pSurfDoc->m_triangles_ObjectList); 
	if (pSurfDoc->m_triangles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_triangles.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_triangles.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastTriangulatedGridToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_tria_grid.SetCurrentMsgOnLast())
	{	
		HTREEITEM& h1 = pSurfDoc->m_tria_grid_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "TriangulatedGrids", &pSurfDoc->m_tria_grid_ObjectList); 
		pSurfDoc->m_tria_grid.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
	}
}

void AddTriangulatedGrid3DToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_tria_grid_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "TriangulatedGrids", &pSurfDoc->m_tria_grid_ObjectList); 
	if (pSurfDoc->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_tria_grid.GetCurrentMsg().AddItem_ToTree(hwndTV, h1);
		}
		while(pSurfDoc->m_tria_grid.IncrementCurrentMsg());
	}
	//=============================================================
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void AddLastBlnProfileToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	if (pSurfDoc->m_bln_profiles.SetCurrentMsgOnLast())
	{
		HTREEITEM& h1 = pSurfDoc->m_bln_profiles_ObjectList.myTreeItem; 
		if (h1 == NULL)
			h1 = AddObjectListItem(hwndTV, "bln profiles", &pSurfDoc->m_bln_profiles_ObjectList); 
		pSurfDoc->m_bln_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
	}
}

void AddBlnProfilesToTree(HWND hwndTV, SurfDoc* pSurfDoc)
{
	//TreeView_DeleteMyItem(hwndTV,pSurfDoc->m_bln_profiles_ObjectList.myTreeItem);
	//=============================================================
	HTREEITEM h1 = AddObjectListItem(hwndTV, "bln profiles", &pSurfDoc->m_bln_profiles_ObjectList); 
	if (pSurfDoc->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_bln_profiles.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
		}
		while(pSurfDoc->m_bln_profiles.IncrementCurrentMsg());
	}
	//=============================================================
}

// InitTreeViewItems - extracts headings from the specified file and 
// passes them to a function that adds them to a tree-view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree-view control. 
// lpszFileName - name of file with headings.

BOOL InitTreeViewItems(HWND hwndTV, SurfDoc* pSurfDoc) 
{ 
//    char szItemText[1024]; // label text of tree-view item 
	TreeView_DeleteAllItems(hwndTV);

	AddGeoColomnsToTree(hwndTV, pSurfDoc);

	AddSurfacesToTree(hwndTV, pSurfDoc);
	AddFaultsToTree(hwndTV, pSurfDoc);
	AddGridProfilesToTree(hwndTV, pSurfDoc);
	AddLinesToTree(hwndTV, pSurfDoc);
	AddCutLinesToTree(hwndTV, pSurfDoc);
	AddWellsToTree(hwndTV, pSurfDoc);
	AddBrokenPlanesToTree(hwndTV, pSurfDoc);
	AddStringsToTree(hwndTV, pSurfDoc);
	AddPolygonesToTree(hwndTV, pSurfDoc);
	AddSpheresToTree(hwndTV, pSurfDoc);
	AddPointsToTree(hwndTV, pSurfDoc);	
	AddTrianglesToTree(hwndTV, pSurfDoc);
	AddTriangulatedGrid3DToTree(hwndTV, pSurfDoc);
	AddBlnProfilesToTree(hwndTV, pSurfDoc);
	AddBitmapsToTree(hwndTV, pSurfDoc);
	AddBmpProfilesToTree(hwndTV, pSurfDoc);

    return TRUE; 
} 




// InitTreeViewImageLists - creates an image list, adds three bitmaps 
// to it, and associates the image list with a tree-view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree-view control. 
//
BOOL InitTreeViewImageLists(HWND hwndTV) 
{ 
    HIMAGELIST himl;  // handle to image list 
    HBITMAP hbmp;     // handle to bitmap 

    // Create the image list. 
    if ((himl = ImageList_Create(CX_BITMAP, 
                                 CY_BITMAP,
                                 FALSE, 
                                 NUM_BITMAPS, 0)) == NULL) 
        return FALSE; 

    // Add the open file, closed file, and document bitmaps. 
    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_OPEN_FILE)); 
    g_nOpen = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CLOSED_FILE)); 
    g_nClosed = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DOCUMENT)); 
    g_nDocument = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(himl) < 3) 
        return FALSE; 

    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL); 

    return TRUE; 
} 


WNDPROC wpOrigTreeViewWndProc;

// Новый отработчик сообщений TreeView 
LRESULT APIENTRY TreeViewWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
	else
	if (uMsg == WM_WINDOWPOSCHANGING)
	{
MessageBox(0, "WM_WINDOWPOSCHANGING 0", "Tree", 0);
		long lrez = CallWindowProc(wpOrigTreeViewWndProc, hwnd, uMsg, wParam, lParam);
MessageBox(0, "WM_WINDOWPOSCHANGING end", "Tree", 0);
		return lrez;
	}
	else
	if (uMsg == WM_WINDOWPOSCHANGED)
	{
printf("Tree WM_WINDOWPOSCHANGED 0\n");
MessageBox(0, "WM_WINDOWPOSCHANGED 0", "Tree", 0);
		long lrez = CallWindowProc(wpOrigTreeViewWndProc, hwnd, uMsg, wParam, lParam);
MessageBox(0, "WM_WINDOWPOSCHANGED end", "Tree", 0);
		return lrez;
	}

	//Вызываем старый отработчик 
    return CallWindowProc(wpOrigTreeViewWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 





// CreateATreeView - creates a tree-view control. 
// Returns the handle to the new control if successful,
// or NULL otherwise. 
// hwndParent - handle to the control's parent window. 
// lpszFileName - name of the file to parse for tree-view items.

HWND CreateATreeView(HWND hwndParent, SurfDoc* pSurfDoc) 
{ 
    RECT rcClient;  // dimensions of client area 
    HWND hwndTV;    // handle to tree-view control 

    // Ensure that the common control DLL is loaded. 
    InitCommonControls(); 

    // Get the dimensions of the parent window's client area, and create 
    // the tree-view control. 
    GetClientRect(hwndParent, &rcClient); 
    hwndTV = CreateWindowEx(WS_EX_CLIENTEDGE,
                            WC_TREEVIEW,
                            "Tree View",
                            WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES 
							| TVS_CHECKBOXES | TVS_HASBUTTONS | TVS_EDITLABELS
							| TVS_LINESATROOT | TVS_SHOWSELALWAYS, 
                            0, 
                            0, 
                            rcClient.right/4, 
                            rcClient.bottom/2,
                            hwndParent, 
#if 0
                            (HMENU)ID_TREEVIEW, 
#else
                            (HMENU)NULL, 
#endif
                            hInst, 
                            NULL); 

    // Initialize the image list, and add items to the control. 
    // InitTreeViewImageLists and InitTreeViewItems are application- 
    // defined functions. 
	BOOL itvil = InitTreeViewImageLists(hwndTV);
	char str[32];
	sprintf(str, "itvil = %d ", itvil);
//	MessageBox(0,str, "",0);
	BOOL itvi = InitTreeViewItems(hwndTV, pSurfDoc);
	sprintf(str, "itvi = %d ", itvi);
//	MessageBox(0,str, "",0);
    if (
//		!InitTreeViewImageLists(hwndTV) || 
		!itvil || !itvi
//                !InitTreeViewItems(hwndTV, lpszFileName)
				)
    { 
#if 0
        DestroyWindow(hwndTV); 
        return FALSE; 
#endif
    } 
	//--------------------------------------------------------------
	// Subclass the control. 
/*	wpOrigTreeViewWndProc = (WNDPROC) SetWindowLongPtr(hwndTV, 
		GWLP_WNDPROC, (LONG_PTR) TreeViewWndSubclassProc); 
*/
	//--------------------------------------------------------------
    return hwndTV;
} 

// Main_OnBeginDrag - begins dragging an item in a tree-view control. 
// hwndTV - handle to the image list. 
// lpnmtv - address of information about the item being dragged. 

void Main_OnBeginDrag(HWND hwndTV, LPNMTREEVIEW lpnmtv) 
{ 
    HIMAGELIST himl;    // handle to image list 
    RECT rcItem;        // bounding rectangle of item 
    DWORD dwLevel;      // heading level of item 
    DWORD dwIndent;     // amount that child items are indented 

    // Tell the tree-view control to create an image to use 
    // for dragging. 
    himl = TreeView_CreateDragImage(hwndTV, lpnmtv->itemNew.hItem); 

    // Get the bounding rectangle of the item being dragged. 
    TreeView_GetItemRect(hwndTV, lpnmtv->itemNew.hItem, &rcItem, TRUE); 

    // Get the heading level and the amount that the child items are 
    // indented. 
    dwLevel = lpnmtv->itemNew.lParam; 
    dwIndent = (DWORD)SendMessage(hwndTV, TVM_GETINDENT, 0, 0); 

    // Start the drag operation. 
    ImageList_BeginDrag(himl, 0, 0, 0);
    ImageList_DragEnter(hwndTV, 50, 50);  

    // Hide the mouse pointer, and direct mouse input to the 
    // parent window. 
#if 1
    ShowCursor(FALSE); 
#endif
    SetCapture(GetParent(hwndTV)); 
    g_fDragging = TRUE; 

    return; 

} 


// Main_OnMouseMove - drags an item in a tree-view control, 
// highlighting the item that is the target. 
// hwndParent - handle to the parent window. 
// hwndTV - handle to the tree-view control.
// xCur and yCur - x- and y-coordinates of the mouse pointer. 

void Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle to target item 
    TVHITTESTINFO tvht;  // hit test information 

    if (g_fDragging) 
    { 
        // Drag the item to the current position of the mouse pointer. 
        ImageList_DragMove(xCur, yCur); 

        // Find out if the pointer is on the item. If it is, 
        // highlight the item as a drop target. 
        tvht.pt.x = xCur; 
        tvht.pt.y = yCur; 
        if ((htiTarget = TreeView_HitTest(hwndTV, &tvht)) != NULL) 
        { 
            TreeView_SelectDropTarget(hwndTV, htiTarget); 
        } 
    } 
    return; 
} 

// Main_OnLButtonUp - stops dragging a tree-view item, releases the 
// mouse capture, and shows the mouse pointer.
//
// Global variable g_fDragging - indicates whether
// a drag operation is underway. 

void Main_OnLButtonUp(void) 
{ 
    if (g_fDragging) 
    { 
        ImageList_EndDrag(); 
        ReleaseCapture(); 
        ShowCursor(TRUE); 
        g_fDragging = FALSE; 
    } 
    return; 
} 

BOOL TreeView_MySetCheckState(HWND hwndTreeView, HTREEITEM hItem, BOOL fCheck)
{
	//TreeView_SetCheckState Macro
	//Sets the item's state image to "checked" or "unchecked." 
	//You can also use the TVM_SETITEM message directly.


    TVITEM tvItem;

    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Image 1 in the tree-view check box image list is the
    // unchecked box. Image 2 is the checked box.

   tvItem.state = INDEXTOSTATEIMAGEMASK((fCheck ? 2 : 1));
 //    tvItem.state = INDEXTOSTATEIMAGEMASK(fCheck);

    return TreeView_SetItem(hwndTreeView, &tvItem);
}

BOOL TreeView_MyGetCheckState(HWND hwndTreeView, HTREEITEM hItem)
{
	//TreeView_GetCheckState Macro
	//Gets the check state of the specified item. 
	//You can also use the TVM_GETITEMSTATE message directly. 

    TVITEM tvItem;

    // Prepare to receive the desired information.
    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Request the information.
    TreeView_GetItem(hwndTreeView, &tvItem);

    // Return zero if it's not checked, or nonzero otherwise.
//    return (BOOL)(tvItem.state >> 12);
    return ((BOOL)(tvItem.state >> 12) -1);
}

LPARAM TreeView_GetLParam(HWND hwndTreeView, HTREEITEM hItem)
{

	TVITEM tvItem;

	// Prepare to receive the desired information.
	tvItem.mask = TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | TVIF_CHILDREN;
	tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

	// Request the information.
	TreeView_GetItem(hwndTreeView, &tvItem);
	return tvItem.lParam;
}

LPSTR TreeView_GetText(HWND hwndTreeView, HTREEITEM hItem)
{

	TVITEM tvItem;

	// Prepare to receive the desired information.
	tvItem.mask = TVIF_HANDLE | TVIF_TEXT | TVIF_STATE | TVIF_CHILDREN;
	tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

	// Request the information.
	TreeView_GetItem(hwndTreeView, &tvItem);

	if (tvItem.mask & TVIF_TEXT && tvItem.cchTextMax > 0)
		return tvItem.pszText;
	else
		return NULL;
}

void TreeView_EnumCheckedItems(HWND hwndTreeView, HTREEITEM hParentItem, LPARAM id, 
							   void (*  draw_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, LPARAM /*id*/),
							   void  (*  checking_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, BOOL /*bCheck*/, LPARAM /*lParam*/)
							   )
{
//printf("TreeView_EnumCheckedItems\n");
	HTREEITEM h = TreeView_GetChild(hwndTreeView,  hParentItem);
	while (h)
	{
		LPARAM lParam = TreeView_GetLParam(hwndTreeView, h);
		BOOL check = TreeView_MyGetCheckState(hwndTreeView, h);
		// call checking func for change checking flag in the object
		(*checking_func)(hwndTreeView, hParentItem, h, check, lParam);

		HTREEITEM h2 = TreeView_GetChild(hwndTreeView,  h);
		if (check)
		{
			// работаем с ветвью или с элементом, если он выделен
			if (h2) 
				// если данный элемент имеет детей, рекурсивно применяем 
				// эту же функцию перечисления
				// передаём текущий lParam как идентификатор объекта
				TreeView_EnumCheckedItems(hwndTreeView, h, lParam, draw_func, checking_func);
			else
				// если элемент не имеет детей -
				// это ризнак того , что данный итем олицетворяет единичный объект
				// значит мы вызываем здесь функцию обратного вызова для 
				// изображения объекта, а текущий lParam передаём 
				// как указатель на изображаемый объект
			{
				if (draw_func)
					(*draw_func)(hwndTreeView, hParentItem, h, lParam);
			}
		}
		h = TreeView_GetNextItem(hwndTreeView, h, TVGN_NEXT);
	}
}

void TreeView_EnumCheckedItems(HWND hwndTreeView, HTREEITEM hParentItem, LPARAM id, 
							   void  (*  checking_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, BOOL /*bCheck*/, LPARAM /*lParam*/)
							   )
{
//printf("TreeView_EnumCheckedItems\n");
	HTREEITEM h = TreeView_GetChild(hwndTreeView,  hParentItem);
	while (h)
	{
		LPARAM lParam = TreeView_GetLParam(hwndTreeView, h);
		BOOL check = TreeView_MyGetCheckState(hwndTreeView, h);
		// call checking func for change checking flag in the object
		(*checking_func)(hwndTreeView, hParentItem, h, check, lParam);

		HTREEITEM h2 = TreeView_GetChild(hwndTreeView,  h);
		if (h2)
		{
			// работаем с ветвью или с элементом, если он выделен
			// если данный элемент имеет детей, рекурсивно применяем 
			// эту же функцию перечисления
			// передаём текущий lParam как идентификатор объекта
			TreeView_EnumCheckedItems(hwndTreeView, h, lParam, checking_func);
		}
		h = TreeView_GetNextItem(hwndTreeView, h, TVGN_NEXT);
	}
}

void TreeView_EnumCheckedItems(HWND hwndTreeView, HTREEITEM hParentItem, LPARAM id, 
							   void (*  draw_func)(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, LPARAM /*id*/)
							   )
{
//printf("TreeView_EnumCheckedItems\n");
	HTREEITEM h = TreeView_GetChild(hwndTreeView,  hParentItem);
	while (h)
	{
		LPARAM lParam = TreeView_GetLParam(hwndTreeView, h);
		BOOL check = TreeView_MyGetCheckState(hwndTreeView, h);

		HTREEITEM h2 = TreeView_GetChild(hwndTreeView,  h);
		if (check)
		{
			// работаем с ветвью или с элементом, если он выделен
			if (h2) 
				// если данный элемент имеет детей, рекурсивно применяем 
				// эту же функцию перечисления
				// передаём текущий lParam как идентификатор объекта
				TreeView_EnumCheckedItems(hwndTreeView, h, lParam, draw_func);
			else
				// если элемент не имеет детей -
				// это ризнак того , что данный итем олицетворяет единичный объект
				// значит мы вызываем здесь функцию обратного вызова для 
				// изображения объекта, а текущий lParam передаём 
				// как указатель на изображаемый объект
			{
				if (draw_func)
					(*draw_func)(hwndTreeView, hParentItem, h, lParam);
			}
		}
		h = TreeView_GetNextItem(hwndTreeView, h, TVGN_NEXT);
	}
}
