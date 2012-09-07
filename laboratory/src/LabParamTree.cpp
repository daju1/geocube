#include "../../surfer_connect/stdafx.h"
#include "../resource.h"
#include "../../surfdoc/src/DlgAddingGeoCube.h"

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include <commctrl.h>
#include "stdafx.h"
#include "lab.h"
#include "../../resource.h"
#include "LabParamTree.h"
#include "../../wintools/src/project.h"

extern HINSTANCE hInst;   // текущий экземпляр

int 
g_nOpen3 = 0, 
g_nClosed3 = 0, 
g_nDocument3 = 0;

int NUM_BITMAPS3 = 3;
#define CX_BITMAP2 16
#define CY_BITMAP2 16

BOOL g_fDragging3 = FALSE;

BOOL TreeView_SetCheckState3(HWND hwndTreeView, HTREEITEM hItem, bool * fCheck)
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

BOOL TreeView_GetCheckState3(HWND hwndTreeView, HTREEITEM hItem)
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

HTREEITEM AddParamToTree(HWND hwndTV, LPSTR lpszItem, LabParam * lab_param, HTREEITEM hParent, HTREEITEM hInsertAfter)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 
    HTREEITEM h; 

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
	if (lab_param->m_bExpanded_LabParam) tvi.mask |= TVIS_EXPANDED;

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 

    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = g_nDocument3; 
    tvi.iSelectedImage = g_nDocument3; 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)lab_param; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hInsertAfter; 

    // Set the parent item based on the specified level. 
    tvins.hParent = hParent; 
	lab_param->parentTreeItem_LabParam = hParent;

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
		tvi.iImage = g_nClosed3; 
        tvi.iSelectedImage = g_nClosed3; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
	TreeView_SetCheckState3(hwndTV, hPrev, &lab_param->m_bChecked_LabParam);

	lab_param->myTreeItem_LabParam = hPrev;

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
    tvi.iImage = g_nDocument3; 
    tvi.iSelectedImage = g_nDocument3; 

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
		tvi.iImage = g_nClosed3; 
        tvi.iSelectedImage = g_nClosed3; 
        //tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
	
	TreeView_SetCheckState3(hwndTV, hPrev, fCheck);

//	pObject->myTreeItem = hPrev;

    return hPrev; 
} */




// InitTreeViewParam - extracts headings from the specified file and 
// passes them to a function that adds them to a tree-view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree-view control. 
// lpszFileName - name of file with headings.

BOOL InitTreeViewParam(HWND hwndTV, Laboratory * lab) 
{ 
	if (lab)
		lab->AddParam_ToTree(hwndTV, NULL);       

    return TRUE; 
} 


// InitLabParamTreeViewImageLists - creates an image list, adds three bitmaps 
// to it, and associates the image list with a tree-view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree-view control. 
//
// Global variables and constants 
// g_nOpen, g_nClosed, and g_nDocument - integer variables for 
// indexes of the images. 
// CX_BITMAP and CY_BITMAP - width and height of an icon. 
// NUM_BITMAPS - number of bitmaps to add to the image list. 

BOOL InitLabParamTreeViewImageLists(HWND hwndTV) 
{ 
    HIMAGELIST himl;  // handle to image list 
    HBITMAP hbmp;     // handle to bitmap 

    // Create the image list. 
    if ((himl = ImageList_Create(CX_BITMAP2, 
                                 CY_BITMAP2,
                                 FALSE, 
                                 NUM_BITMAPS3, 0)) == NULL) 
        return FALSE; 

    // Add the open file, closed file, and document bitmaps. 
    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_OPEN_FILE)); 
    g_nOpen3 = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CLOSED_FILE)); 
    g_nClosed3 = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DOCUMENT)); 
    g_nDocument3 = ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(himl) < 3) 
        return FALSE; 

    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL); 

    return TRUE; 
} 

// CreateATreeView_LabParam - creates a tree-view control. 
// Returns the handle to the new control if successful,
// or NULL otherwise. 
// hwndParent - handle to the control's parent window. 
// lpszFileName - name of the file to parse for tree-view items.
HWND CreateATreeView_LabParam(HWND hwndParent, Laboratory * lab) 
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
                            "Lab Param Tree View",
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
    // InitLabParamTreeViewImageLists and InitTreeViewItems are application- 
    // defined functions. 
    if (!InitLabParamTreeViewImageLists(hwndTV) || 
                !InitTreeViewParam(hwndTV, lab))
    { 
        DestroyWindow(hwndTV); 
        return FALSE; 
    } 
    return hwndTV;
} 



// Main_OnBeginDrag - begins dragging an item in a tree-view control. 
// hwndTV - handle to the image list. 
// lpnmtv - address of information about the item being dragged. 

void Main_OnBeginDrag3(HWND hwndTV, LPNMTREEVIEW lpnmtv) 
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
    g_fDragging3 = TRUE; 

    return; 

} 
// Main_OnMouseMove - drags an item in a tree-view control, 
// highlighting the item that is the target. 
// hwndParent - handle to the parent window. 
// hwndTV - handle to the tree-view control.
// xCur and yCur - x- and y-coordinates of the mouse pointer. 

void Main_OnMouseMove3(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle to target item 
    TVHITTESTINFO tvht;  // hit test information 

    if (g_fDragging3) 
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

void Main_OnLButtonUp3(void) 
{ 
    if (g_fDragging3) 
    { 
        ImageList_EndDrag(); 
        ReleaseCapture(); 
        ShowCursor(TRUE); 
        g_fDragging3 = FALSE; 
    } 
    return; 
} 

LPARAM TreeView_GetLParam3(HWND hwndTreeView, HTREEITEM hItem)
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



WNDPROC wpOrigTreeWndProc3; 
 
// Subclass procedure 
LRESULT APIENTRY TreeWndSubclassProc3(
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
    return CallWindowProc(wpOrigTreeWndProc3, hwnd, uMsg, 
        wParam, lParam); 
} 

WNDPROC wpOrigProcLabParamTree; 
LRESULT CALLBACK DlgProcLabParamTree(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			hwndTV = CreateATreeView_LabParam(hwnd, lab);
#if 1
			// Subclass the control. 
			wpOrigTreeWndProc3 = (WNDPROC) SetWindowLongPtr(hwndTV, 
				GWLP_WNDPROC, (LONG_PTR) TreeWndSubclassProc3); 
#endif
			SetWindowLongPtr(hwndTV, GWLP_USERDATA,(LONG_PTR)lab);

			if (lab)
				lab->hwndTV2 = hwndTV;
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
						if(hTreeItem)
						{
							LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hTreeItem);
							LabParam * lab_param = reinterpret_cast<LabParam *> (lParam3);
							LabObject * lab_object = dynamic_cast<LabObject *> (lab_param);
							if (lab_object)
							{
								lab->DestroyContextWindow();								
#if LABORATORY_WITH_SURFDOC
								SurfDoc * doc = (SurfDoc *)lab->GetDoc();
								if(doc)
#endif
									lab->SelectLabObject(
										Laboratory::context_window_pt.x,
										Laboratory::context_window_pt.y,
										lab_object, hwnd);
								
								hMouseClickedTreeItem = hTreeItem;
							}
						}
					}
				}
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
							LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hTreeItem);
							LabParam * lab_param = reinterpret_cast<LabParam *> (lParam3);
//							lab->SelectLabObject(lab_object);
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
						LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hTreeItem);
						LabParam * lab_param = reinterpret_cast<LabParam *> (lParam3);
						lab->SelectLabParam(lab_param, hwndTV, hTreeItem);
					}
				}
				hMouseClickedTreeItem = hTreeItem;
			}
			break;

		case WM_CONTEXTMENU :
			{
				if(hCurrentTreeItem)
				{
					LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hCurrentTreeItem);
					LabParam * lab_param = reinterpret_cast<LabParam *> (lParam3);
					if (lab_param)lab_param->CreateContextMenuParam(hwnd, lParam);
				}
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_LAB_PARAM_ADDCUBE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hCurrentTreeItem);
						LabParameter * lab_parameter = reinterpret_cast<LabParameter *> (lParam3);
						//if (lab_parameter) lab_parameter->AddCube();
						if (lab_parameter && lab && lab->GetDoc())
						{
							SurfDoc * pSurfdoc = reinterpret_cast<SurfDoc *>(lab->GetDoc());
							if (pSurfdoc)
							{
								DlgAddingGeoCube dlg;
								dlg.m_edit_param_name.Format("%s", lab_parameter->m_vt.GetValueTypeString());
								dlg.DoModal();
								if (dlg.ob_button_pressed && dlg.m_radio_normative_type > -1)
								{
									//CString s;
									//s.Format("dlg.m_radio_normative_type = %d", dlg.m_radio_normative_type);
									//AfxMessageBox(s);
									pSurfdoc->AddGeoCube(dlg.m_check_full_cube_filling, lab_parameter->m_vt, LabNormatives::type(dlg.m_radio_normative_type));
								}
							}
						}
					}
				}
				break;
			case ID_TREE_LAB_PARAMCHECK:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hCurrentTreeItem);
						LabParam * lab_param = reinterpret_cast<LabParam *> (lParam3);
						if (lab_param) lab_param->ParamCheck(hwndTV);
						if (lab) lab->ReCreateContextWindow();
					}
				}
				break;
			case ID_TREE_LAB_PARAMUNCHECK:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam3 = TreeView_GetLParam3(hwndTV, hCurrentTreeItem);
						LabParam * lab_param = reinterpret_cast<LabParam *> (lParam3);
						if (lab_param) lab_param->ParamUnCheck(hwndTV);
						if (lab) lab->ReCreateContextWindow();
					}
				}
				break;

			case ID_TREE_LAB_PARAMCHECKALL:
				{
					if (lab) lab->ParamCheck(hwndTV);
				}
				break;
			case ID_TREE_LAB_PARAMUNCHECKALL:
				{
					if (lab) lab->ParamUnCheck(hwndTV);
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
			case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE_INTERVAL:
				{
					if (lab)
						lab->LabCompressionPressureInterval();
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
					Main_OnBeginDrag3(hwndTV, (LPNMTREEVIEW)lParam);
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
   return CallWindowProc(wpOrigProcLabParamTree, hwnd, message, 
	   wParam, lParam);}

LRESULT CALLBACK DlgProcLaboratoryParamTree(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Laboratory * lab;
	static HWND hWndLabParamTree   = NULL;
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
				hWndLabParamTree = GetDlgItem(hDlg, IDC_STATIC_LAB_TRIAL_TREE); 

				// Subclass the picture control. 
				wpOrigProcLabParamTree = (WNDPROC) SetWindowLongPtr(hWndLabParamTree, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcLabParamTree); 

				SendMessage(hWndLabParamTree, WM_INITDIALOG, wParam, lParam);
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

