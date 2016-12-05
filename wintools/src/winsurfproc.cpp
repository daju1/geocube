// ghemical.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "../resource.h"
#include "winsurfproc.h"
#include "win32_app.h"
#include "win32_graphics_view.h"
// Windows Header Files:
#include "..\..\surfdoc\src\drawscene.h"
#include "GLPrintMan.h"
#include "PrintDlgBox.h"
#include "PrintDlgBox.h"
#include "winsurf.h"
#include "..\..\tools\src\errorexit.h"

#include "project.h"	// config.h is here -> we get ENABLE-macros here...


#include <math.h>
#define PI		3.14159265358979323846
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>

#define MAX_LOADSTRING 256
#define IDT_TIMER_1    1

// Global Variables:
extern HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];
								// The title bar text
extern HGLOBAL store_hDevMode;
extern HGLOBAL store_hDevNames;
extern RECT store_rtMargin;

int UseGLFont( HDC hDC,  IN CONST LOGFONTA * plf_Label)
{
	static GLYPHMETRICSFLOAT m_agmf[256];
	static HFONT m_fontLabel, m_fontLabelPrev;
	m_fontLabel = ::CreateFontIndirect(plf_Label);
	SelectObject (hDC, m_fontLabel);

	// create the bitmap display lists 
	// we're making images of glyphs 0 thru 255 
	// the display List numbering starts at 1000, an arbitrary choice 
	if ( !wglUseFontBitmaps (hDC, 0, 255, FIRST_FONT_LIST_BITMAPS))
	{
		ErrorExit("wglUseFontBitmaps");
		return -1;
	}  

	if ( !wglUseFontOutlines(hDC, 0, 255, FIRST_FONT_LIST_OUTLINES, 0.0f, 0.1f,
        //WGL_FONT_POLYGONS, 
		WGL_FONT_LINES,
		m_agmf))
	{
		ErrorExit("wglUseFontOutlines");
		return -1;
	}

	return 0;
}
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LOGFONT lf_Label;        // logical font structure
CGLPrintMan print;
LRESULT CALLBACK WndSurfProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//static	HGLRC		m_hRC;			// Контекст OpenGL
	//static	HDC			m_hdc; 			// Контекст Windows

	static DWORD rgbCurrent_fontLabel, rgbPrev_fontLabel;   // current text color

//	static bool		m_bShiftPressed;	// Признак нажатия Shift
//	static bool		m_bCtrlPressed;		// Признак нажатия Ctrl
	/*if (hWnd == GetDesktopWindow())
	{
		MessageBox(0, "hWnd == GetDesktopWindow()", "WndSurfProc", 0);
		return 0;
	}*/

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			//case ID_MOUSE_DRAW:
			case ID_MOUSE_DRAW_GRIDDATA:
			case ID_MOUSE_DRAW_SPHERES:
			case ID_MOUSE_DRAW_LINE:
			case ID_MOUSE_DRAW_POLYGON:
			case ID_MOUSE_DRAW_RECT:
			case ID_MOUSE_DRAW_CUBE:
			//case ID_MOUSE_ERASE:
			case ID_MOUSE_ERASE_GRIDDATA:
			case ID_MOUSE_ERASE_SPHERES:
			case ID_MOUSE_ERASE_LINE:
			case ID_MOUSE_ERASE_LINESPOINT:
			case ID_MOUSE_ERASE_POLYGON:
			case ID_MOUSE_ERASE_POLYGONSPOINT:
			case ID_MOUSE_ERASE_RECT:
			case ID_MOUSE_ERASE_CUBE:
			//case ID_MOUSE_EDIT:
			case ID_MOUSE_EDIT_LINE:
//			case ID_MOUSE_EDIT_LINEBY_MOVINGEXISTINGPOINT:
//			case ID_MOUSE_EDIT_LINEBY_ADDNEWPOINT:
			case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDOUBLEPOINT:
			case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDELETEBOND:
			case ID_MOUSE_EDIT_CUTTINGOFLINEBY_DOUBLENEWPOINTONBOND:
			case ID_MOUSE_EDIT_CONNECTLINES:
			case ID_MOUSE_SELECT:
			case ID_MOUSE_ZOOM:
			case ID_MOUSE_CLIPPING:
			case ID_MOUSE_TRANSLATEXY:
			case ID_MOUSE_TRANSLATEZ:
			case ID_MOUSE_ORBITXY:
			case ID_MOUSE_ORBITZ:
			case ID_MOUSE_ROTATEXY:
			case ID_MOUSE_ROTATEZ:
			case ID_MOUSE_MEASURE:
				{
					//CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW_GRIDDATA,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW_SPHERES,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW_LINE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW_POLYGON,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW_RECT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_DRAW_CUBE,		MF_BYCOMMAND | MF_UNCHECKED);
					//CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_GRIDDATA,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_SPHERES,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_LINE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_LINE,		MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_LINEBY_MOVINGEXISTINGPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_LINEBY_ADDNEWPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDOUBLEPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDELETEBOND,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_CUTTINGOFLINEBY_DOUBLENEWPOINTONBOND,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_EDIT_CONNECTLINES,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_LINESPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_POLYGON,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_POLYGONSPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_RECT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE_CUBE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ERASE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_SELECT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ZOOM,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_CLIPPING,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_TRANSLATEXY,MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_TRANSLATEZ, MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ORBITXY,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ORBITZ,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ROTATEXY,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_ROTATEZ,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_MOUSE_MEASURE,	MF_BYCOMMAND | MF_UNCHECKED);
					
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						///woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							//if (wmId != ID_MOUSE_DRAW_LINE)
							//	w_prj->SetLineForDraw(NULL);

							win_app * app = w_prj->GetApp();
							if (app)
							{
								switch (wmId)
								{
								//case ID_MOUSE_DRAW:
								//	app->maintb_tool_Draw(NULL, NULL, NULL);
								//	break;
								case ID_MOUSE_DRAW_GRIDDATA:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_draw = draw_tool::Griddata;
									app->maintb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_SPHERES:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_draw = draw_tool::Spheres;
									app->maintb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_LINE:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_draw = draw_tool::Line;
									app->maintb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_POLYGON:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_draw = draw_tool::Polygon;
									app->maintb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_RECT:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_draw = draw_tool::Rect;
									app->maintb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_CUBE:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_draw = draw_tool::Cube;
									app->maintb_tool_Draw(NULL, NULL, NULL);
									break;

								//case ID_MOUSE_ERASE:
								//	app->maintb_tool_Erase(NULL, NULL, NULL);
								//	break;
								case ID_MOUSE_ERASE_GRIDDATA:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Griddata;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_SPHERES:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Spheres;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_LINE:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Line;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_LINESPOINT:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Lines_point;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_POLYGON:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Polygon;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_POLYGONSPOINT:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Polygones_point;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_RECT:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Rect;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_CUBE:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_erase = erase_tool::Cube;
									app->maintb_tool_Erase(NULL, NULL, NULL);
									break;

								case ID_MOUSE_EDIT_LINE:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_edit = edit_tool::what_to_edit::Line;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;								
								/*case ID_MOUSE_EDIT_LINEBY_MOVINGEXISTINGPOINT:
									ogl_view::what_to_edit = edit_tool::what_to_edit::Line_by_moving_existing_point;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;								
								case ID_MOUSE_EDIT_LINEBY_ADDNEWPOINT:
									ogl_view::what_to_edit = edit_tool::what_to_edit::Line_by_add_new_point;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;*/
								case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDOUBLEPOINT:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_edit = edit_tool::Line_cut_by_select_and_double_point;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;
								case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDELETEBOND:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_edit = edit_tool::Line_cut_by_select_and_delete_bond;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;
								case ID_MOUSE_EDIT_CUTTINGOFLINEBY_DOUBLENEWPOINTONBOND:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_edit = edit_tool::Line_cut_by_double_new_point_on_bond;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;
								case ID_MOUSE_EDIT_CONNECTLINES:
									woglv->SetDigitizeCursor(true);
									ogl_view::what_to_edit = edit_tool::Lines_connect;
									app->maintb_tool_Edit(NULL, NULL, NULL);
									break;


								case ID_MOUSE_SELECT:
									woglv->SetDigitizeCursor(true);
									app->maintb_tool_Select(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ZOOM:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_Zoom(NULL, NULL, NULL);
									break;
								case ID_MOUSE_CLIPPING:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_Clipping(NULL, NULL, NULL);
									break;
								case ID_MOUSE_TRANSLATEXY:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_TranslXY(NULL, NULL, NULL);
									break;
								case ID_MOUSE_TRANSLATEZ:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_TranslZ(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ORBITXY:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_OrbitXY(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ORBITZ:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_OrbitZ(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ROTATEXY:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_RotateXY(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ROTATEZ:
									woglv->SetDigitizeCursor(false);
									app->maintb_tool_RotateZ(NULL, NULL, NULL);
									break;
								case ID_MOUSE_MEASURE:
									woglv->SetDigitizeCursor(true);
									app->maintb_tool_Measure(NULL, NULL, NULL);
									break;
								}

							}
						}
					}
					//######################################################
				}
				break;
			case ID_FILE_PRINTPREVIEW:
				{
					PrintPreview(hWnd);
				}
				break;
			case ID_FILE_PAGESETUP:
				{
					SurfPrintedPageSetup(hWnd);
				}
				break;
			case ID_WINSURF_FILE_PRINT_SETUP:
				{
#if 0
					DisplayPrintPropertySheet(hWnd);
#else
					DisplayPrintSurfDialogBox(hWnd);
#endif
				}
				break;
			case ID_WINSURF_FILE_PRINT:
				{
					PrintDefault(hWnd);
				}
				break;
			case ID_LIGHTS_ADDLIGHT_LIGHT:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);

					if (wgrv)
					{
						wgrv->popup_LightsNewLight(hWnd, NULL);
					}
					//######################################################
				}
				break;
			case ID_LIGHTS_ADDLIGHT_LOCALDIRECTIONAL:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						wgrv->popup_LightsNewLightLocDir(hWnd, NULL);
					}
					//######################################################
				}
				break;
			case ID_LIGHTS_ADDLIGHT_LOCALSPOTLIGHT:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						wgrv->popup_LightsNewLightLocSpot(hWnd, NULL);
					}
					//######################################################
				}
				break;
			case ID_LIGHTS_ADDLIGHT_GLOBALDIRECTIONAL:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						wgrv->popup_LightsNewLightGlobDir(hWnd, NULL);
					}
					//######################################################
				}
				break;
			case ID_LIGHTS_ADDLIGHT_GLOBALSPOTLIGHT:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						wgrv->popup_LightsNewLightGlobSpot(hWnd, NULL);
					}
					//######################################################
				}
				break;
			case ID_LIGHTS_ENABLELOCALLIGHTS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						if (wgrv->popup_LightsSwitchLoc(hWnd, NULL))
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
						else							
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_UNCHECKED);
					}
					//######################################################
				}
				break;
			case ID_LIGHTS_ENABLEGLOBALLIGHTS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						if (wgrv->popup_LightsSwitchGlob(hWnd, NULL))
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
						else
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_UNCHECKED);
					}
					//######################################################
				}
				break;

			case ID_LIGHTS_MOVELOCALLIGHTS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						if (wgrv->popup_LightsSwitchMovingLoc(hWnd, NULL))
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
						else							
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_UNCHECKED);
					}
					//######################################################
				}
				break;

			case ID_LIGHTS_MOVEGLOBALLIGHTS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						if (wgrv->popup_LightsSwitchMovingGlob(hWnd, NULL))
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
						else
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_UNCHECKED);
					}
					//######################################################
				}
				break;

			case ID_LIGHTS_FIXLOCALANDGLOBALLIGHTS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
					if (wgrv)
					{
						if (wgrv->popup_LightsSwitchFixingLocGlob(hWnd, NULL))
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
						else
							CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_UNCHECKED);
					}
					//######################################################
				}
				break;

			case ID_SELECT_SELECTALL:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectAll(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;


			case ID_SELECT_SELECTALL_EMPTY_WELLS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectAllEmptyWells(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;

			case ID_SELECT_SELECTNONE:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectNone(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_INVERSESELECTION:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_InvertSelection(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_DELETESELECTION:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_DeleteSelection(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_UNCHECKSELECTION:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_UncheckSelection(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_UNCHECKUNSELECTION:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_UncheckUnselection(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_SELECTIONSETCOLOR:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionSetColor(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	

			case ID_SELECT_SELECTIONSETCOLORFROMCURRENTWELLSSLOJ:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionSetColor_FromCurrentWellsSloj(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	


			case ID_SELECT_SELECTIONTOGRIDDATA:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionToGridData(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;					
				
			case ID_SELECT_SELECTIONWITHCURRENTWELLSSLOJTOGRIDDATA:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_Selection_With_CurrentWellsSloj_ToGridData(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			
			case ID_SELECT_SELECTIONTOLAYER:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionToLayer(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;
			case ID_SELECT_SELECTIONGETNAMES_AND_ID:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionGetNamesAndID(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_SELECTIONSETIDINT:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionSetID(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_SELECTIONSETNAME:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_SelectionSetName(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SURFTEST_ENTERCOMMAND:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_EnterCommand(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;
			case ID_SELECT_CHECKSELECTION:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_CheckSelection(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_CHECKUNSELECTION:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_CheckUnselection(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;	
			case ID_SELECT_OBJECT:
			case ID_SELECT_OBJECTSWITHSAMEID:
			case ID_SELECT_OBJECTSWITHSAMENAME:
			case ID_SELECT_POINT:
			case ID_SELECT_EDGE:
			case ID_SELECT_TRIANGLE:
			case ID_SELECT_QUAD:
			case ID_SELECT_POLYGON:
				{
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_OBJECT,				MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_OBJECTSWITHSAMEID,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_OBJECTSWITHSAMENAME,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_POINT,					MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_EDGE,					MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_TRIANGLE,				MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_QUAD,					MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_SELECT_POLYGON,				MF_BYCOMMAND | MF_UNCHECKED);
					
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
					//######################################################
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							switch (wmId)
							{
							case ID_SELECT_OBJECT:
								w_prj->popup_SelectModeObject(hWnd, NULL);
								break;
							case ID_SELECT_OBJECTSWITHSAMEID:
								w_prj->popup_SelectModeObjectsSameID(hWnd, NULL);
								break;
							case ID_SELECT_OBJECTSWITHSAMENAME:
								w_prj->popup_SelectModeObjectsSameName(hWnd, NULL);
								break;
							case ID_SELECT_POINT:
								w_prj->popup_SelectModePoint(hWnd, NULL);
								break;
							case ID_SELECT_EDGE:
								w_prj->popup_RModeCylinders(hWnd, NULL);
								break;
							case ID_SELECT_TRIANGLE:
								w_prj->popup_RModeWireframe(hWnd, NULL);
								break;
							case ID_SELECT_QUAD:
								w_prj->popup_RModeNothing(hWnd, NULL);
								break;
							case ID_SELECT_POLYGON:
								w_prj->popup_RModeNothing(hWnd, NULL);
								break;
							}
						}
					}
				}
				break;
#if 0
			case ID_RENDER_BALLANDSTICK:
			case ID_RENDER_VANDERVAALS:
			case ID_RENDER_CYLINDERS:
			case ID_RENDER_WIREFRAME:
			case ID_RENDER_NOTHING:
				{
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_RENDER_BALLANDSTICK,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_RENDER_VANDERVAALS,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_RENDER_CYLINDERS,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_RENDER_WIREFRAME,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_RENDER_NOTHING,		MF_BYCOMMAND | MF_UNCHECKED);
					
					CheckMenuItem(GetMenu( GetParent(hWnd)  ), wmId, MF_BYCOMMAND | MF_CHECKED);
					//######################################################
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							switch (wmId)
							{
							case ID_RENDER_BALLANDSTICK:
								w_prj->popup_RModeBallStick(hWnd, NULL);
								break;
							case ID_RENDER_VANDERVAALS:
								w_prj->popup_RModeVanDerWaals(hWnd, NULL);
								break;
							case ID_RENDER_CYLINDERS:
								w_prj->popup_RModeCylinders(hWnd, NULL);
								break;
							case ID_RENDER_WIREFRAME:
								w_prj->popup_RModeWireframe(hWnd, NULL);
								break;
							case ID_RENDER_NOTHING:
								w_prj->popup_RModeNothing(hWnd, NULL);
								break;
							}
						}
					}
				}
				break; 
			case ID_BUILD_CLEAR:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_Clear(hWnd,NULL);
						}
					}
					//######################################################
				}
				break;
			case ID_FILE_OPEN:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_FileOpen(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;
			case ID_FILE_SAVEAS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->popup_FileSaveAs(hWnd, NULL);
						}
					}
					//######################################################
				}
				break;

			case ID_VIEW_UPDATEALLVIEWS:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						//woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->UpdateAllViews();
						}
					}
					//######################################################
				}
				break;
#endif
			case ID_FILE_INITOG2:
				{
					//######################################################
					win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					if (woglv)
					{
						woglv->RealizeHandler(hWnd, NULL);
						project * prj = woglv->GetProject();
						win_project * w_prj = dynamic_cast<win_project *>(prj);
						if (w_prj)
						{
							w_prj->InitGL();
						}
					}
					//######################################################
				}
				break;
			case ID_FILE_INITOG:
				{
					win_ogl_view * wogv = 
						(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
					if (! wogv)
					{
						MessageBox(hWnd,"! win_ogl_view\nError","On Create",0);
						return 0;
					}
					wogv->InitOG(hWnd);
				}
				break;

			  case ID_SURFTEST_FONT:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
					  CHOOSEFONT cf;            // common dialog box structure
					  
					  // Initialize CHOOSEFONT
					  ZeroMemory(&cf, sizeof(cf));
					  cf.lStructSize = sizeof (cf);
					  cf.hwndOwner = hWnd;
					  cf.lpLogFont = &lf_Label;
					  cf.rgbColors = rgbCurrent_fontLabel;
					  cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_TTONLY | CF_INITTOLOGFONTSTRUCT ;
					  
					  if (ChooseFont(&cf)==TRUE) {
						  rgbCurrent_fontLabel= cf.rgbColors;
#if 0
						  m_fontLabel = CreateFontIndirect(cf.lpLogFont);
						  m_fontLabelPrev = (HFONT__ *)SelectObject(m_hdc, m_fontLabel);
						  rgbPrev_fontLabel = SetTextColor(m_hdc, rgbCurrent_fontLabel);
#endif
						  if (woglv) UseGLFont( woglv->m_hdc,  &lf_Label);
						  UseGLFont( print.m_hDC,  &lf_Label);

						  RECT rect;
						  //====== Перерисовываем Вид с учетом изменений
						  GetClientRect(hWnd,&rect);
						  InvalidateRect(hWnd,&rect, true);
					  }
				  }
				  break;
#if 0
			  case ID_VIEW_SAVEBITMAP:
				  {
					  //Save Screen 					  
					  //CGLPrintMan print;					  
					  // save
					  print.SaveBitmap("D:\\screen.bmp");
				  }
				  break;
			  case ID_VIEW_SAVEBITMAP_2:
				  {
					  // ###########################################################
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
					  // ###########################################################
					  if (woglv) 
					  {
						  //задаём размер рисунка
					  RECT paper;
					  paper.left	= 0;
					  paper.top		= 0;
					  paper.right	= 2000;
					  paper.bottom	= 2000;

					  print.toEnableOpenGL	= true;
					  print.toReDraw		= true;
					  print.toDisableOpenGL	= true;
					  
					  long width=paper.right - paper.left;
					  long height=paper.bottom - paper.top;
					  
					  //CGLPrintMan print;//объект - печатник
					  // здесь создаём:
					  // 1) битмап уазанного размера для рисования
					  // 2) контекст устройства памяти, совместимый с окном
					  //	связываем контекст устройства памяти, с битмап изображением
					  // 3) контест реализации OpenGL, который может писать в битмап
					  print.EnableOpenGL(paper, hWnd, &print.m_hDC, &print.m_hRC);
					  // сохраняем теущие как старые контексты окна и реализации OpenGL
					  // выбираем контест реализации OpenGL (3) в качестве текущего для 
					  // контекст устройства памяти (2), 
					  // который в свою очередь уже связан с битмап (1)
					  print.StartUpdate();
					  UseGLFont( print.m_hDC,  &lf_Label);

					  // теперь мы подготовили такой контекст реализации OpenGL 
					  // который будет рисовать в битмап объекта print
					  
					  SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG2, 0);
					  glDrawBuffer(GL_FRONT);
					  

						  if (print.toReDraw)
						  {
							  project * prj = woglv->GetProject();
							  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
							  //pSurfDoc->ZoomView();
							  //====== Формирование списка рисующих команд
							  pSurfDoc->Draw();
						  }

						  // Set new size of viwport as picture's paper size
						  woglv->SetSize(width,height);

						  woglv->ExposeEvent();

						  // Restore size of viwport as window size
						  woglv->ConfigureHandler(hWnd);
					  }
					  
					  // save
					  print.SaveBitmap2("D:\\screen2.bmp");
					  print.DisableOpenGL(hWnd, print.m_hDC, print.m_hRC);
					  // возобновляем старые установки OpenGL
					  print.EndUpdate();
				  }
				  break;
#endif
#if 0
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
#endif
				default://WM_COMMAND
					return WinSurfProc(hWnd, message, wParam, lParam);
			}
			break;
      case WM_CREATE  :
              {
				  //##################################################
				  CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
				  SetWindowLongPtr(hWnd,	GWLP_USERDATA, LONG_PTR(pcs->lpCreateParams));
				  //##################################################

				  SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG, 0);
				  
				  //##################################################
				  CheckMenuItem(GetMenu( GetParent(hWnd) ), ID_MOUSE_ORBITXY,
					  MF_BYCOMMAND | MF_CHECKED);
				  CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_LIGHTS_ENABLELOCALLIGHTS,                        
					  MF_BYCOMMAND | MF_CHECKED);
				  CheckMenuItem(GetMenu( GetParent(hWnd)  ), ID_LIGHTS_ENABLEGLOBALLIGHTS,                        
					  MF_BYCOMMAND | MF_CHECKED);
				  //##################################################
				  WinSurfProc(hWnd, message, wParam, lParam);

				  store_rtMargin.top = 2500;
				  store_rtMargin.left = 2500;
				  store_rtMargin.right = 2500;
				  store_rtMargin.bottom = 2500;

              }
              break;
/*		case WM_ERASEBKGND:
			{
printf("WM_ERASEBKGND\n");
				return true;
			}
			break;
		case WM_WINDOWPOSCHANGING:
			{
/*MessageBox(0, "WM_WINDOWPOSCHANGING 0", "Surf", 0);
				long lrez = DefWindowProc(hWnd, message, wParam, lParam);
MessageBox(0, "WM_WINDOWPOSCHANGING end", "Surf", 0);
				return lrez;
				return false;
			}
			break;
		case WM_NCCALCSIZE:
			{
MessageBox(0, "WM_NCCALCSIZE 0", "Surf", 0);
				long lrez = DefWindowProc(hWnd, message, wParam, lParam);
MessageBox(0, "WM_NCCALCSIZE end", "Surf", 0);
printf( "Surf WM_NCCALCSIZE end\n", 0);
				return lrez;
			}
			break;
		case WM_NCPAINT:
			{
printf("WM_NCPAINT 0\n");
				long lrez = DefWindowProc(hWnd, message, wParam, lParam);
printf("WM_NCPAINT end\n");
				return lrez;
			}
			break;
		case WM_WINDOWPOSCHANGED:
			{
MessageBox(0, "WM_WINDOWPOSCHANGED 0", "Surf", 0);
				long lrez = DefWindowProc(hWnd, message, wParam, lParam);
MessageBox(0, "WM_WINDOWPOSCHANGED end", "Surf", 0);
				return lrez;
			}
			break;*/
		case WM_SIZE:
			{
//MessageBox(0, "WM_SIZE 0", "Surf", 0);
//printf("GetDesktopWindow() = 0x%08x\n", GetDesktopWindow());
				/*if (hWnd == GetDesktopWindow())
				{
					MessageBox(0, "WM_SIZE hWnd == GetDesktopWindow()", "Surf", 0);
					return 0;
				}
				else*/
				//{
				// ###########################################################
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
//MessageBox(0, "WM_SIZE 2", "Surf", 0);
				if (woglv)
				{
//MessageBox(0, "WM_SIZE 3", "Surf", 0);
					woglv->ConfigureHandler(hWnd);
//MessageBox(0, "WM_SIZE 4", "Surf", 0);
				}
				// ###########################################################
				LRESULT lrez = DefWindowProc(hWnd, message, wParam, lParam);
//MessageBox(0, "WM_SIZE end", "Surf", 0);
				return lrez;
				//}
			}
			break;

		case WM_PAINT:
			{
				//printf("WM_PAINT \n\n");
				hdc = BeginPaint(hWnd, &ps);
				// ###########################################################
				win_ogl_view * woglv = 
					(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (woglv)
				{	
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();

					woglv->ExposeEvent();

					SwapBuffers(woglv->m_hdc);
				}

				// ###########################################################
				EndPaint(hWnd, &ps);
			}
			break;

		case WM_LBUTTONDOWN :
			SetFocus(hWnd);
		case WM_RBUTTONDOWN :
		case WM_RBUTTONUP :
		case WM_LBUTTONUP :
			{
				// ###########################################################
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
				if (woglv)
				{
					if (woglv->hDigitizeCursor)
						SetCursor(woglv->hDigitizeCursor);
					woglv->ButtonHandler(hWnd, message, wParam, lParam);
				}
				// ###########################################################
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
			}
			break;
		case WM_MOUSEMOVE :
			{
				// ###########################################################
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
				if (woglv)
				{
					if (woglv->hDigitizeCursor)
						SetCursor(woglv->hDigitizeCursor);

					woglv->MotionNotifyHandler(hWnd, wParam, lParam);	
				}
				// ###########################################################
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);						
			}
			break;
		case WM_MOUSEWHEEL :
			{
				// ###########################################################
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
				if (woglv)
				{
					woglv->MouseWhellNotifyHandler(hWnd, wParam, lParam);	
				}
				// ###########################################################


				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
			}
			break;
		case WM_KEYUP :
		case WM_KEYDOWN :
			{
				// ###########################################################
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
				if (woglv)
				{
					woglv->KeyButtonHandler(hWnd, message, wParam, lParam);
				}
				// ###########################################################
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
			}
			break;

/*		case WM_KEYUP :
			{
				//char str[255];
				//sprintf(str,"wParam = %d lParam = %d", wParam, lParam);
				//MessageBox(0,str,"WM_KEYUP",0);
				switch (wParam)
				{
				case 16:// Shift
					{
						//m_bShiftPressed = false;
					}
					break;
				case 17:// Ctrl
					{
						//m_bCtrlPressed = false;
					}
					break;
				}
			}
			break;
*/

		case WM_DESTROY:
			if (store_hDevMode) GlobalFree(store_hDevMode); 
			if (store_hDevNames) GlobalFree(store_hDevNames); 
			PostQuitMessage(0);
			break;
		default:
			return WinSurfProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
