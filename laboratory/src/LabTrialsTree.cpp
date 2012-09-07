#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include <commctrl.h>
#include "stdafx.h"
#include "lab.h"
#include "../../resource.h"
#include "LabTrialsTree.h"
#include "../../wintools/src/project.h"

extern HINSTANCE hInst;   // текущий экземпляр

int 
g_nOpen2 = 0, 
g_nClosed2 = 0, 
g_nDocument2 = 0;

int NUM_BITMAPS2 = 3;
#define CX_BITMAP2 16
#define CY_BITMAP2 16

BOOL g_fDragging2 = FALSE;

BOOL TreeView_SetCheckState2(HWND hwndTreeView, HTREEITEM hItem, bool * fCheck)
{
    TVITEM tvItem;

    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Image 1 in the tree-view check box image list is the
    // unchecked box. Image 2 is the checked box.

    if (fCheck)
		tvItem.state = INDEXTOSTATEIMAGEMASK((*fCheck ? 2 : 1));

    return TreeView_SetItem(hwndTreeView, &tvItem);
}

BOOL TreeView_GetCheckState2(HWND hwndTreeView, HTREEITEM hItem)
{
    TVITEM tvItem;

    // Prepare to receive the desired information.
    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Request the information.
    TreeView_GetItem(hwndTreeView, &tvItem);

    // Return zero if it's not checked, or nonzero otherwise.
    return ((BOOL)(tvItem.state >> 12) -1);
}



// AddItemToTree - adds items to a tree-view control. 
// Returns the handle to the newly added item. 
// hwndTV - handle to the tree-view control. 
// lpszItem - text of the item to add. 
// nLevel - level at which to add the item. 
#if 0
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, int nLevel)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
    HTREEITEM hti; 

    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
               | TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 

    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = g_nDocument2; 
    tvi.iSelectedImage = g_nDocument2; 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)nLevel; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hPrev; 

    // Set the parent item based on the specified level. 
    if (nLevel == 1) 
        tvins.hParent = TVI_ROOT; 
    else if (nLevel == 2) 
        tvins.hParent = hPrevRootItem; 
    else 
        tvins.hParent = hPrevLev2Item; 

    // Add the item to the tree-view control. 
    hPrev = (HTREEITEM)SendMessage(hwndTV, 
                                   TVM_INSERTITEM, 
                                   0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins); 

    // Save the handle to the item. 
    if (nLevel == 1) 
        hPrevRootItem = hPrev; 
    else if (nLevel == 2) 
        hPrevLev2Item = hPrev; 

    // The new item is a child item. Give the parent item a 
    // closed folder bitmap to indicate it now has child items. 
    if (nLevel > 1)
    { 
        hti = TreeView_GetParent(hwndTV, hPrev); 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.hItem = hti; 
        tvi.iImage = g_nClosed2; 
        tvi.iSelectedImage = g_nClosed2; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 

    return hPrev; 
} 
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
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
    tvi.iImage = g_nDocument2; 
    tvi.iSelectedImage = g_nDocument2; 

    // Save the heading level in the item's application-defined 
    // data area. 
//    tvi.lParam = (LPARAM)pObject; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hInsertAfter; 

    // Set the parent item based on the specified level. 
    tvins.hParent = hParent; 
//	pObject->parentTreeItem = hParent;

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
		tvi.iImage = g_nClosed2; 
        tvi.iSelectedImage = g_nClosed2; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
//	TreeView_MySetCheckState(hwndTV, hPrev, pObject->m_bChecked);

//	pObject->myTreeItem = hPrev;

    return hPrev; 
} 
#endif
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, LabObject * lab_object, HTREEITEM hParent, HTREEITEM hInsertAfter)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 
    HTREEITEM h; 

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
	if (lab_object->m_bExpanded_LabObject) tvi.mask |= TVIS_EXPANDED;

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 

    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = g_nDocument2; 
    tvi.iSelectedImage = g_nDocument2; 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)lab_object; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hInsertAfter; 

    // Set the parent item based on the specified level. 
    tvins.hParent = hParent; 
	lab_object->parentTreeItem_LabObject = hParent;

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
		tvi.iImage = g_nClosed2; 
        tvi.iSelectedImage = g_nClosed2; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
	TreeView_SetCheckState2(hwndTV, hPrev, &lab_object->m_bChecked_LabObject);

	lab_object->myTreeItem_LabObject = hPrev;

    return hPrev; 
} 
/*HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, bool * fCheck, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter)
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
    tvi.iImage = g_nDocument2; 
    tvi.iSelectedImage = g_nDocument2; 

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
		tvi.iImage = g_nClosed2; 
        tvi.iSelectedImage = g_nClosed2; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
	TreeView_SetCheckState2(hwndTV, hPrev, fCheck);

//	pObject->myTreeItem = hPrev;

    return hPrev; 
} */




// InitTreeViewItems - extracts headings from the specified file and 
// passes them to a function that adds them to a tree-view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree-view control. 
// lpszFileName - name of file with headings.

BOOL InitTreeViewItems(HWND hwndTV, Laboratory * lab) 
{ 

	if (lab)
		lab->AddItem_ToTree(hwndTV, NULL);       

    return TRUE; 
} 


// InitLabTrialTreeViewImageLists - creates an image list, adds three bitmaps 
// to it, and associates the image list with a tree-view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree-view control. 
//
// Global variables and constants 
// g_nOpen, g_nClosed, and g_nDocument - integer variables for 
// indexes of the images. 
// CX_BITMAP and CY_BITMAP - width and height of an icon. 
// NUM_BITMAPS - number of bitmaps to add to the image list. 

BOOL InitLabTrialTreeViewImageLists(HWND hwndTV) 
{ 
    HIMAGELIST himl;  // handle to image list 
    HBITMAP hbmp;     // handle to bitmap 

    // Create the image list. 
    if ((himl = ImageList_Create(CX_BITMAP2, 
                                 CY_BITMAP2,
                                 FALSE, 
                                 NUM_BITMAPS2, 0)) == NULL) 
        return FALSE; 

    // Add the open file, closed file, and document bitmaps. 
    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_OPEN_FILE)); 
    g_nOpen2 = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CLOSED_FILE)); 
    g_nClosed2 = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DOCUMENT)); 
    g_nDocument2 = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(himl) < 3) 
        return FALSE; 

    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL); 

    return TRUE; 
} 

// CreateATreeView - creates a tree-view control. 
// Returns the handle to the new control if successful,
// or NULL otherwise. 
// hwndParent - handle to the control's parent window. 
// lpszFileName - name of the file to parse for tree-view items.
HWND CreateATreeView(HWND hwndParent, Laboratory * lab) 
{ 
    RECT rcClient;  // dimensions of client area 
    HWND hwndTV;    // handle to tree-view control 

    // Ensure that the common control DLL is loaded. 
    InitCommonControls(); 

    // Get the dimensions of the parent window's client area, and create 
    // the tree-view control. 
    GetClientRect(hwndParent, &rcClient); 
    hwndTV = CreateWindowEx(0,
                            WC_TREEVIEW,
                            "Lab Tree View",
#if 0
                            WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES,
#else
                            WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES 
							| TVS_HASBUTTONS | TVS_CHECKBOXES //| TVS_EDITLABELS
							| TVS_LINESATROOT | TVS_SHOWSELALWAYS, 
#endif
                            0, 
                            0, 
                            rcClient.right, 
                            rcClient.bottom,
                            hwndParent, 
#if 0
                            (HMENU)ID_TREEVIEW, 
#else
                            (HMENU)NULL, 
#endif
                            hInst, 
                            NULL); 

    // Initialize the image list, and add items to the control. 
    // InitLabTrialTreeViewImageLists and InitTreeViewItems are application- 
    // defined functions. 
    if (!InitLabTrialTreeViewImageLists(hwndTV) || 
                !InitTreeViewItems(hwndTV, lab))
    { 
        DestroyWindow(hwndTV); 
        return FALSE; 
    } 
    return hwndTV;
} 



// Main_OnBeginDrag - begins dragging an item in a tree-view control. 
// hwndTV - handle to the image list. 
// lpnmtv - address of information about the item being dragged. 

void Main_OnBeginDrag2(HWND hwndTV, LPNMTREEVIEW lpnmtv) 
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
    ShowCursor(FALSE); 
    SetCapture(GetParent(hwndTV)); 
    g_fDragging2 = TRUE; 

    return; 

} 
// Main_OnMouseMove - drags an item in a tree-view control, 
// highlighting the item that is the target. 
// hwndParent - handle to the parent window. 
// hwndTV - handle to the tree-view control.
// xCur and yCur - x- and y-coordinates of the mouse pointer. 

void Main_OnMouseMove2(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle to target item 
    TVHITTESTINFO tvht;  // hit test information 

    if (g_fDragging2) 
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

void Main_OnLButtonUp2(void) 
{ 
    if (g_fDragging2) 
    { 
        ImageList_EndDrag(); 
        ReleaseCapture(); 
        ShowCursor(TRUE); 
        g_fDragging2 = FALSE; 
    } 
    return; 
} 
WNDPROC wpOrigTreeWndProc2; 
 
// Subclass procedure 
LRESULT APIENTRY TreeWndSubclassProc2(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 

    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      // Control wants all keys - All keyboard input         
	} 
	else
    if (uMsg == WM_RBUTTONDOWN || uMsg == WM_LBUTTONDOWN ) 
	{
		int xPos = LOWORD(lParam); // horizontal position of pointer 
		int yPos = HIWORD(lParam); // vertical position of pointer 		}
		if (xPos > 32768) xPos -= 65536;
		if (yPos > 32768) yPos -= 65536;

		//TreeNode* tn = GetNodeAt( xPos, yPos);
		HTREEITEM htiTarget;  // handle to target item 
		TVHITTESTINFO tvht;  // hit test information 
        // Find out if the pointer is on the item. If it is, 
        // highlight the item as a drop target. 
        tvht.pt.x = xPos; 
        tvht.pt.y = yPos; 
        if ((htiTarget = TreeView_HitTest(hwnd, &tvht)) != NULL) 
        { 
            TreeView_SelectDropTarget(hwnd, htiTarget); 
			SendMessage(GetParent(hwnd), WM_USER, 0, (LPARAM) htiTarget);
		}
		if (uMsg == WM_LBUTTONDOWN ) 
		{
			int xPos = LOWORD(lParam); // horizontal position of pointer 
			int yPos = HIWORD(lParam); // vertical position of pointer 		}
			if (xPos > 32768) xPos -= 65536;
			if (yPos > 32768) yPos -= 65536;

			//TreeNode* tn = GetNodeAt( xPos, yPos);
			HTREEITEM htiTarget;  // handle to target item 
			TVHITTESTINFO tvht;  // hit test information 
			// Find out if the pointer is on the item. If it is, 
			// highlight the item as a drop target. 
			tvht.pt.x = xPos; 
			tvht.pt.y = yPos; 
			if ((htiTarget = TreeView_HitTest(hwnd, &tvht)) != NULL) 
			{ 
				if (tvht.flags == TVHT_ONITEMLABEL)
					SendMessage(GetParent(hwnd), WM_USER+1, 0, (LPARAM) htiTarget);
			}			
			if ((htiTarget = TreeView_HitTest(hwnd, &tvht)) != NULL) 
			{ 
				if (tvht.flags == TVHT_ONITEMSTATEICON)
				{
					SendMessage(GetParent(hwnd), WM_USER+3, 0, (LPARAM) htiTarget);
				}
			}	
		}
	}
	else
    if (uMsg == WM_MOUSEMOVE ) 
	{
		int xPos = LOWORD(lParam); // horizontal position of pointer 
		int yPos = HIWORD(lParam); // vertical position of pointer 		}
		if (xPos > 32768) xPos -= 65536;
		if (yPos > 32768) yPos -= 65536;

		//TreeNode* tn = GetNodeAt( xPos, yPos);
		HTREEITEM htiTarget;  // handle to target item 
		TVHITTESTINFO tvht;  // hit test information 
        // Find out if the pointer is on the item. If it is, 
        // highlight the item as a drop target. 
        tvht.pt.x = xPos; 
        tvht.pt.y = yPos;
        if ((htiTarget = TreeView_HitTest(hwnd, &tvht)) != NULL) 
        {
			if (tvht.flags == TVHT_ONITEMLABEL)
				SendMessage(GetParent(hwnd), WM_USER+2, 0, (LPARAM) htiTarget);
		}		
	}
    return CallWindowProc(wpOrigTreeWndProc2, hwnd, uMsg, 
        wParam, lParam); 
} 

LPARAM TreeView_GetLParam2(HWND hwndTreeView, HTREEITEM hItem)
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
WNDPROC wpOrigProcLabTrialTree; 
LRESULT CALLBACK DlgProcLabTrialTree(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Laboratory * lab;
	static HWND hwndTV   = NULL;
	int wmId, wmEvent;
//	char str[1024];

	static HTREEITEM hCurrentTreeItem;
	static HTREEITEM hMouseMovedTreeItem;
	static HTREEITEM hMouseClickedTreeItem;

	static int context_menu_item;
	static int xPos; // horizontal position of pointer 
	static int yPos; // vertical position of pointer 		}

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			//printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lab = (Laboratory *)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			// create left window
			hwndTV = CreateATreeView(hwnd, lab);
#if 1
			// Subclass the control. 
			wpOrigTreeWndProc2 = (WNDPROC) SetWindowLongPtr(hwndTV, 
				GWLP_WNDPROC, (LONG_PTR) TreeWndSubclassProc2); 
#endif
			SetWindowLongPtr(hwndTV, GWLP_USERDATA,(LONG_PTR)lab);

			if (lab)
				lab->hwndTV = hwndTV;
			// #############################################################
			// #############################################################
			hMouseMovedTreeItem = NULL;
			hMouseClickedTreeItem = NULL;
		}
		break;
	case WM_MOUSEMOVE: 
		{
			xPos = LOWORD(lParam); // horizontal position of pointer 
			yPos = HIWORD(lParam); // vertical position of pointer
			if (xPos > 32768) xPos -= 65536;
			if (yPos > 32768) yPos -= 65536;
		}
		break;

		case WM_USER:
			{
				hCurrentTreeItem = (HTREEITEM)lParam;
			}
			break;
		case WM_USER+1:
			{
				HTREEITEM hTreeItem = (HTREEITEM)lParam;
				if (lab)
				{
					if (hTreeItem != hMouseClickedTreeItem)
					{
						lab->DestroyContextWindow();
						if(hTreeItem)
						{
							LPARAM lParam2 = TreeView_GetLParam2(hwndTV, hTreeItem);
							LabObject * lab_object = reinterpret_cast<LabObject *> (lParam2);
#if LABORATORY_WITH_SURFDOC
							SurfDoc * doc = (SurfDoc *)lab->GetDoc();
							if(doc)
#endif
								lab->SelectLabObject(
									Laboratory::context_window_pt.x,
									Laboratory::context_window_pt.y,
									lab_object, hwnd);
						}
					}
				}
				hMouseClickedTreeItem = hTreeItem;
			}
			break;
		case WM_USER+2:
			{
				HTREEITEM hTreeItem = (HTREEITEM)lParam;
				if (lab)
				{
					if (hTreeItem != hMouseMovedTreeItem)
					{
						if(hTreeItem)
						{
							LPARAM lParam2 = TreeView_GetLParam2(hwndTV, hTreeItem);
							LabObject * lab_object = reinterpret_cast<LabObject *> (lParam2);
							//lab->SelectLabObject(lab_object);
						}
					}
				}
				hMouseMovedTreeItem = hTreeItem;
			}
			break;
		case WM_USER+3:
			{
				HTREEITEM hTreeItem = (HTREEITEM)lParam;
				if (lab)
				{
					if(hTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam2(hwndTV, hTreeItem);
						LabObject * lab_object = reinterpret_cast<LabObject *> (lParam2);
						lab->SelectLabObject(lab_object, hwndTV, hTreeItem);
					}
				}
			}
			break;
		case WM_CONTEXTMENU :
			{
				if(hCurrentTreeItem)
				{
					LPARAM lParam2 = TreeView_GetLParam2(hwndTV, hCurrentTreeItem);
					LabObject * lab_object = reinterpret_cast<LabObject *> (lParam2);
					if (lab_object)lab_object->CreateContextMenu(hwnd, lParam);
				}
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_OBJECTSAVEAS:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam2(hwndTV, hCurrentTreeItem);
						LabObject * lab_object = reinterpret_cast<LabObject *> (lParam2);

						if (lab_object)
							lab_object->SaveAs();

						//LPARAM lParam = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						//Object * pObject = reinterpret_cast<Object *> (lParam);
						//if(lab_object)lab_object->SaveAs();
					}
				}
				break;
			case ID_TREE_LAB_WELLELEMENTPROP:
				{
					if (lab)
						lab->LabWellElementProp();
				}
				break;
			case ID_TREE_LAB_WELLELEMENTPROPSAVE:
				{
					if (lab)
						lab->LabWellElementPropSave();
				}
				break;
			case ID_TREE_LAB_PASSPORT:
				{
					if (lab)
						lab->LabWellElementPassport();
				}
				break;
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT0:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT1:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT2:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT3:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_TITLE:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XLABEL:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YLABEL:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XAXES:
			case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YAXES:
				{
					if (lab)
						lab->LabWellElementPropFont(wmId);
				}
				break;
			case ID_TREE_LAB_WELLELEMENTCONTEXTPLOTHEIGHT:
				{
					if (lab)
						lab->LabWellElementPropPlotHeight();
				}
				break;
			case ID_TREE_LAB_GURVICH_Y_SECOND_DERIVATIVE_LIMIT:
				{
					if (lab)
						lab->LabGurvichYSecondDerivativeLimit();
				}
				break;	
			case ID_TREE_LAB_E_SECOND_DERIVATIVE_LIMIT:
				{
					if (lab)
						lab->LabCompressionESecondDerivativeLimit();
				}
				break;	
			case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE:
				{
					if (lab)
						lab->LabCompressionPressure();
				}
				break;
			case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE_INTERVAL:
				{
					if (lab)
						lab->LabCompressionPressureInterval();
				}
				break;
			case ID_TREE_LAB_WATERSATURATEDPARTOFFULLWATERCAPACITY:
				{
					if (lab)
						lab->LabWaterSaturatedPartOfFullWaterCapacity();
				}
				break;
			}
			break;
#if 0
		case WM_NOTIFY: 
			switch (((LPNMHDR)lParam)->code) 
			{
				case TVN_BEGINDRAG:
					//Main_OnBeginDrag is an application-defined function
					Main_OnBeginDrag2(hwndTV, (LPNMTREEVIEW)lParam);
					break;
				
				// Handle other cases here. 
			}
			break; 
#endif
		case WM_CLOSE:
			{
				if (lab) lab->DestroyContextWindow();
				return DefWindowProc(hwnd, message, wParam, lParam);
			}
			break;
   }
   return CallWindowProc(wpOrigProcLabTrialTree, hwnd, message, 
	   wParam, lParam);
}

LRESULT CALLBACK DlgProcLaboratoryTrialTree(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Laboratory * lab;
	static HWND hWndLabTrialTree   = NULL;
//	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				lab = (Laboratory *)lParam;
				//**************************************
#if 1
				// #############################################################
				// #############################################################
				// Retrieve the handle to the Map control. 
				hWndLabTrialTree = GetDlgItem(hDlg, IDC_STATIC_LAB_TRIAL_TREE); 

				// Subclass the picture control. 
				wpOrigProcLabTrialTree = (WNDPROC) SetWindowLongPtr(hWndLabTrialTree, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcLabTrialTree); 

				SendMessage(hWndLabTrialTree, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################		
#else

#endif
			}
			break;
#if 0
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			/*case ID_TREE_OBJECTSAVEAS:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam);
						if(pObject)pObject->SaveAs();
					}
				}
				break;*/
			}
			break;
#endif
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}

