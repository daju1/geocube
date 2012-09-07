// win_MAP_VIEWS.CPP

// Copyright (C) 2005 Tommi Hassinen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/
#include "stdafx.h"




#include "../resource.h"
//#include "../consol/winghemical.h"

#include "../src/win32_app.h"
#include "../src/win32_graphics_view.h"
#include "../src/win32_map_views.h"

#define g_print printf

	
ULONG_PTR           gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

LRESULT CALLBACK WndProcGDIplusMapView(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//static	HGLRC		m_hRC;				// Контекст OpenGL
	//static	HDC			m_hdc; 			// Контекст Windows


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
			case ID_MOUSE_ASSIGNGRIDDATA:

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
//			case ID_MOUSE_EDIT_WELL:
			case ID_MOUSE_EDIT_WELL_MOVEANDADD:
			case ID_MOUSE_EDIT_WELL_MOVESLOJ:
			case ID_MOUSE_EDIT_WELL_ADDSLOJ:
			case ID_MOUSE_EDIT_WELL_REMOVESLOJ:
			case ID_MOUSE_EDIT_LITOIGE:
//			case ID_MOUSE_EDIT_LINEBY_MOVINGEXISTINGPOINT:
//			case ID_MOUSE_EDIT_LINEBY_ADDNEWPOINT:
			case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDOUBLEPOINT:
			case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDELETEBOND:
			case ID_MOUSE_EDIT_CUTTINGOFLINEBY_DOUBLENEWPOINTONBOND:
			case ID_MOUSE_EDIT_CONNECTLINES:
			case ID_MOUSE_SELECT:
			case ID_MOUSE_ZOOM:
//			case ID_MOUSE_CLIPPING:
			case ID_MOUSE_TRANSLATEXY:
//			case ID_MOUSE_TRANSLATEZ:
//			case ID_MOUSE_ORBITXY:
//			case ID_MOUSE_ORBITZ:
//			case ID_MOUSE_ROTATEXY:
//			case ID_MOUSE_ROTATEZ:
			case ID_MOUSE_MEASURE:
				{
					//CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW,		MF_BYCOMMAND | MF_UNCHECKED);					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW_GRIDDATA,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW_SPHERES,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW_LINE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW_POLYGON,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW_RECT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_DRAW_CUBE,		MF_BYCOMMAND | MF_UNCHECKED);
					//CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE,		MF_BYCOMMAND | MF_UNCHECKED);
					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ASSIGNGRIDDATA,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_GRIDDATA,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_SPHERES,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_LINE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_LINE,		MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_WELL,		MF_BYCOMMAND | MF_UNCHECKED);					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_WELL_MOVEANDADD,		MF_BYCOMMAND | MF_UNCHECKED);					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_WELL_MOVESLOJ,		MF_BYCOMMAND | MF_UNCHECKED);					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_WELL_ADDSLOJ,		MF_BYCOMMAND | MF_UNCHECKED);					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_WELL_REMOVESLOJ,		MF_BYCOMMAND | MF_UNCHECKED);					
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_LITOIGE,		MF_BYCOMMAND | MF_UNCHECKED);					
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_LINEBY_MOVINGEXISTINGPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_LINEBY_ADDNEWPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDOUBLEPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDELETEBOND,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_CUTTINGOFLINEBY_DOUBLENEWPOINTONBOND,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_EDIT_CONNECTLINES,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_LINESPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_POLYGON,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_POLYGONSPOINT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_RECT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE_CUBE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ERASE,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_SELECT,		MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ZOOM,		MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_CLIPPING,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_TRANSLATEXY,MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_TRANSLATEZ, MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ORBITXY,	MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ORBITZ,		MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ROTATEXY,	MF_BYCOMMAND | MF_UNCHECKED);
//					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_ROTATEZ,	MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu( hWnd  ), ID_MOUSE_MEASURE,	MF_BYCOMMAND | MF_UNCHECKED);
					
					CheckMenuItem(GetMenu( hWnd ), wmId, MF_BYCOMMAND | MF_CHECKED);
					//######################################################
					gdiplus_map_view * wgrv = 
						(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
					if (wgrv)
					{
						///woglv->RealizeHandler(hWnd, NULL);
						project * prj = wgrv->GetProject();
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
								//	app->gditb_tool_Draw(NULL, NULL, NULL);
								//	break;

								case ID_MOUSE_ASSIGNGRIDDATA:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::GriddataAssign;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;

								case ID_MOUSE_DRAW_GRIDDATA:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::Griddata;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_SPHERES:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::Spheres;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_LINE:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::Line;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_POLYGON:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::Polygon;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_RECT:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::Rect;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;
								case ID_MOUSE_DRAW_CUBE:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_draw = draw_gdiplus_tool::Cube;
									app->gditb_tool_Draw(NULL, NULL, NULL);
									break;

								//case ID_MOUSE_ERASE:
								//	app->gditb_tool_Erase(NULL, NULL, NULL);
								//	break;
								case ID_MOUSE_ERASE_GRIDDATA:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Griddata;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_SPHERES:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Spheres;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_LINE:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Line;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_LINESPOINT:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Lines_point;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_POLYGON:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Polygon;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_POLYGONSPOINT:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Polygones_point;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_RECT:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Rect;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ERASE_CUBE:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::Cube;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;

								case ID_MOUSE_EDIT_LINE:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::what_to_edit::Line;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;	

//								case ID_MOUSE_EDIT_WELL:
//									wgrv->SetDigitizeCursor(true);
//									gdiplus_view::what_to_edit = edit_gdiplus_tool::what_to_edit::Well;
//									app->gditb_tool_Edit(NULL, NULL, NULL);
//									break;	


								case ID_MOUSE_EDIT_WELL_MOVEANDADD:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::what_to_edit::Well;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;	

								case ID_MOUSE_EDIT_WELL_MOVESLOJ:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::what_to_edit::Well_move_sloj;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;	

								case ID_MOUSE_EDIT_WELL_ADDSLOJ:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::what_to_edit::Well_add_sloj;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;	

								case ID_MOUSE_EDIT_WELL_REMOVESLOJ:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_erase = erase_gdiplus_tool::what_to_erase::Well_remove_sloj;
									app->gditb_tool_Erase(NULL, NULL, NULL);
									break;	

								case ID_MOUSE_EDIT_LITOIGE:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::what_to_edit::Lito_IGE_move_sloj;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;	

				


								/*case ID_MOUSE_EDIT_LINEBY_MOVINGEXISTINGPOINT:
									gdiplus_view:what_to_edit = edit_gdiplus_tool::what_to_edit::Line_by_moving_existing_point;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;								
								case ID_MOUSE_EDIT_LINEBY_ADDNEWPOINT:
									gdiplus_view:what_to_edit = edit_gdiplus_tool::what_to_edit::Line_by_add_new_point;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;*/
								case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDOUBLEPOINT:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::Line_cut_by_select_and_double_point;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;
								case ID_MOUSE_EDIT_CUTTINGOFLINEBY_SELECTANDDELETEBOND:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::Line_cut_by_select_and_delete_bond;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;
								case ID_MOUSE_EDIT_CUTTINGOFLINEBY_DOUBLENEWPOINTONBOND:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::Line_cut_by_double_new_point_on_bond;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;
								case ID_MOUSE_EDIT_CONNECTLINES:
									wgrv->SetDigitizeCursor(true);
									gdiplus_view::what_to_edit = edit_gdiplus_tool::Lines_connect;
									app->gditb_tool_Edit(NULL, NULL, NULL);
									break;


								case ID_MOUSE_SELECT:
									wgrv->SetDigitizeCursor(true);
									app->gditb_tool_Select(NULL, NULL, NULL);
									break;
								case ID_MOUSE_ZOOM:
									wgrv->SetDigitizeCursor(false);
									app->gditb_tool_Zoom(NULL, NULL, NULL);
									break;
//								case ID_MOUSE_CLIPPING:
//									wgrv->SetDigitizeCursor(false);
//									app->gditb_tool_Clipping(NULL, NULL, NULL);
//									break;
								case ID_MOUSE_TRANSLATEXY:
									wgrv->SetDigitizeCursor(false);
									app->gditb_tool_TranslXY(NULL, NULL, NULL);
									break;
//								case ID_MOUSE_TRANSLATEZ:
//									wgrv->SetDigitizeCursor(false);
//									app->gditb_tool_TranslZ(NULL, NULL, NULL);
//									break;
//								case ID_MOUSE_ORBITXY:
//									wgrv->SetDigitizeCursor(false);
//									app->gditb_tool_OrbitXY(NULL, NULL, NULL);
//									break;
//								case ID_MOUSE_ORBITZ:
//									wgrv->SetDigitizeCursor(false);
//									app->gditb_tool_OrbitZ(NULL, NULL, NULL);
//									break;
//								case ID_MOUSE_ROTATEXY:
//									wgrv->SetDigitizeCursor(false);
//									app->gditb_tool_RotateXY(NULL, NULL, NULL);
//									break;
//								case ID_MOUSE_ROTATEZ:
//									wgrv->SetDigitizeCursor(false);
//									app->gditb_tool_RotateZ(NULL, NULL, NULL);
//									break;
								case ID_MOUSE_MEASURE:
									wgrv->SetDigitizeCursor(true);
									app->gditb_tool_Measure(NULL, NULL, NULL);
									break;
								}

							}
						}
					}
					//######################################################
				}
				break;
		case ID_VIEW_UPDATEALLVIEWS:
			{
				//######################################################
				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					//wgrv->RealizeHandler(hWnd, NULL);
					project * prj = wgrv->GetProject();
					win_project * w_prj = dynamic_cast<win_project *>(prj);
					if (w_prj)
					{
						w_prj->UpdateAllViews();
					}
				}
				//######################################################
			}
			break;
		case ID_FILE_INITOG2:
			{
				//######################################################
				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					wgrv->RealizeHandler(hWnd, NULL);
					wgrv->InitGDI();
/*
					project * prj = wgrv->GetProject();
					win_project * w_prj = dynamic_cast<win_project *>(prj);
					if (w_prj)
					{
						w_prj->InitGL();
					}*/
				}
				//######################################################
			}
			break;

		case ID_FILE_INITOG:
			{
				gdiplus_map_view * wogv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (! wogv)
				{
					MessageBox(hWnd,"! gdiplus_map_view\nError","On Create",0);
					return 0;
				}
				wogv->InitDC(hWnd);
			}
			break;
		case ID_ZOOM_ZOOMIN:
			{
				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					wgrv->zoom_x *= sqrt(2.0);
					wgrv->zoom_y *= sqrt(2.0);
					wgrv->VScroll( hWnd, -1 );                    
					wgrv->HScroll( hWnd, -1 );
					//###############################
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				}
			}
			break;
		case ID_ZOOM_ZOOMOUT:
			{
				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					wgrv->zoom_x /= sqrt(2.0);
					wgrv->zoom_y /= sqrt(2.0);
					wgrv->VScroll( hWnd, -1 );                    
					wgrv->HScroll( hWnd, -1 );
					//###############################
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				}
			}
			break;
		case ID_ZOOM_ZOOMYIN:
			{
				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					//wgrv->zoom_x *= sqrt(2.0);
					wgrv->zoom_y *= sqrt(2.0);
					wgrv->VScroll( hWnd, -1 );                    
					wgrv->HScroll( hWnd, -1 );
					//###############################
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				}
			}
			break;
		case ID_ZOOM_ZOOMYOUT:
			{
				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					//wgrv->zoom_x /= sqrt(2.0);
					wgrv->zoom_y /= sqrt(2.0);
					wgrv->VScroll( hWnd, -1 );                    
					wgrv->HScroll( hWnd, -1 );
					//###############################
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				}
			}
			break;
			
		case ID_ZOOM_ZOOMXYEQUIVAL:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					wgrv->zoom_x = wgrv->zoom_y = max(wgrv->zoom_x, wgrv->zoom_y);						
					wgrv->VScroll( hWnd, -1 );                    
					wgrv->HScroll( hWnd, -1 );
					//###############################
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				}
			}
			break;

		case ID_PROFILE_REBUILDSURFACES:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				Object * obj; if (wgrv) obj = wgrv->GetObject(); else return -1;
				BlnProfile3D * bln_profile = dynamic_cast<BlnProfile3D *>(obj);
				if (bln_profile && prj)
				{					
					prj->RebuildByGridData_IfNeed();

					prj->NoBlank(false);
					prj->SurfacesAutoBlank();

					prj->ZoomView();
					prj->Draw();

					prj->Cutting();

					//bln_profile->Cutting();
					prj->UpdateAllViews();					
				}
			}
			break;

		case ID_PROFILE_CANCELBLANK:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				if (prj)
				{		
					prj->NoBlank(false);
					prj->ZoomView();
					prj->Draw();

					prj->UpdateAllViews();					
				}
			}
			break;

		case ID_PROFILE_AUTOBLANK:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				if (prj)
				{		
					prj->SurfacesAutoBlank();
					prj->ZoomView();
					prj->Draw();

					prj->UpdateAllViews();					
				}
			}
			break;

		case ID_PROFILE_CUTTING:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				Object * obj; if (wgrv) obj = wgrv->GetObject(); else return -1;
				BlnProfile3D * bln_profile = dynamic_cast<BlnProfile3D *>(obj);
				if (bln_profile && prj)
				{					
					bln_profile->Cutting();
					prj->UpdateAllViews();					
				}
			}
			break;

		case ID_PROFILE_CUTTINGALLPROFILES:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				if (prj)
				{					
					prj->Cutting();
					//prj->UpdateAllViews();					
				}
			}
			break;


		case ID_TREE_LAB_WELLELEMENTPROP:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabWellElementProp();
			}
			break;
		case ID_TREE_LAB_WELLELEMENTPROPSAVE:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabWellElementPropSave();
			}
			break;

		case ID_TREE_LAB_PASSPORT:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabWellElementPassport();
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
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabWellElementPropFont(wmId);
			}
			break;			
			
		case ID_TREE_LAB_GURVICH_Y_SECOND_DERIVATIVE_LIMIT:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabGurvichYSecondDerivativeLimit();
			}
			break;

		case ID_TREE_LAB_E_SECOND_DERIVATIVE_LIMIT:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabCompressionESecondDerivativeLimit();
			}
			break;	

		case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabCompressionPressure();
			}
			break;	
		case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE_INTERVAL:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabCompressionPressureInterval();
			}
			break;		
		case ID_TREE_LAB_WELLELEMENTCONTEXTPLOTHEIGHT:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabWellElementPropPlotHeight();
			}
			break;
		case ID_TREE_LAB_WATERSATURATEDPARTOFFULLWATERCAPACITY:
			{
				gdiplus_map_view * wgrv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
				prj->LabWaterSaturatedPartOfFullWaterCapacity();
			}
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
	  case WM_CREATE  :
		  {
			  //##################################################
			  CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			  SetWindowLong(hWnd,	GWL_USERDATA,(LONG)pcs->lpCreateParams);
			  //##################################################
			  //##################################################
			  gdiplus_map_view * wogv = 
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
			  if (wogv)
			  {
				  wogv->SetWindow(hWnd);

				  ShowScrollBar( hWnd, SB_HORZ, TRUE );
				  SetScrollRange( hWnd, SB_HORZ, 0, 100, TRUE );
				  SetScrollPos( hWnd, SB_HORZ, wogv->m_nCurHorzPos, TRUE );
				  
				  ShowScrollBar( hWnd, SB_VERT, TRUE );
				  SetScrollRange( hWnd, SB_VERT, 0, 100, TRUE );
				  SetScrollPos( hWnd, SB_VERT, wogv->m_nCurVertPos, TRUE );
			  }
			  //##################################################
		  }
		  break;
	  case WM_VSCROLL :
		  {
			  gdiplus_map_view * wogv = 
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
			  if (wogv)
			  {		
				  wogv->VScroll( hWnd, LOWORD( wParam ) );
				  // ###########################################################
				  RECT rect;
				  GetClientRect(hWnd,&rect);
				  InvalidateRect(hWnd,&rect, true);
			  }
		  }
		  break;
	  case WM_HSCROLL :
		  {
			  gdiplus_map_view * wogv = 
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
			  if (wogv)
			  {		
				  wogv->HScroll( hWnd, LOWORD( wParam ) );
				  // ###########################################################
				  RECT rect;
				  GetClientRect(hWnd,&rect);
				  InvalidateRect(hWnd,&rect, true);
			  }
		  }
		  break;
	  case WM_ERASEBKGND:
		  {
			  return false;
		  }
		  break;
	  case WM_SIZE:
		  {
			  // ###########################################################
			  gdiplus_map_view * woglv = 
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				
			  buff_gdiplus_map_view * bgmv = dynamic_cast< buff_gdiplus_map_view *>(woglv);
			  if (bgmv)
			  {
				  bgmv->ConfigureHandler(hWnd);
				  bgmv->VScroll( hWnd, -1 );
				  bgmv->HScroll( hWnd, -1 );
			  }
			  // ###########################################################
			  long lrez = DefWindowProc(hWnd, message, wParam, lParam);
			  return lrez;
		  }
		  break;
	  case WM_PAINT:
		  {
			  //printf("WM_PAINT \n\n");
			  hdc = BeginPaint(hWnd, &ps);
			  // ###########################################################
              
			  gdiplus_map_view * woglv = (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
              
			  if (woglv)
			  {	
				  woglv->ExposeEvent();
                  
			  }
			  // ###########################################################
			  EndPaint(hWnd, &ps);
		  }
		  break;
	  case WM_LBUTTONDBLCLK :
//		  printf("WM_LBUTTONDBLCLK\n");
	  case WM_RBUTTONDBLCLK :
	  case WM_MBUTTONDBLCLK :
	  case WM_LBUTTONDOWN :
//		  printf("WM_LBUTTONDOWN\n");
	  case WM_RBUTTONDOWN :
//		  printf("WM_RBUTTONDOWN\n");
	  case WM_MBUTTONDOWN :
	  case WM_LBUTTONUP :
	  case WM_RBUTTONUP :
	  case WM_MBUTTONUP :
		  {
			  // ###########################################################
			  gdiplus_map_view * woglv = 
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
			  if (woglv)
			  {
				  if (woglv->hDigitizeCursor)
					  SetCursor(woglv->hDigitizeCursor);
				  woglv->ButtonHandler(hWnd, message, wParam, lParam);
			  }
			  // ###########################################################
			  /*RECT rect;
			  GetClientRect(hWnd,&rect);
			  InvalidateRect(hWnd,&rect, true);*/
		  }
		  break;
	  case WM_MOUSEMOVE :
		  {
			  // ###########################################################
			  gdiplus_map_view * woglv =
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
			  if (woglv)
			  {
				  if (woglv->hDigitizeCursor)
					  SetCursor(woglv->hDigitizeCursor);
				  woglv->MotionNotifyHandler(hWnd, wParam, lParam);	
			  }
			  // ###########################################################
              
		  }
		  break;
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(hWnd, &pt);

				gdiplus_map_view * wgrv = 
					(gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (wgrv)
				{
					wgrv->MouseWhell(yDelta, pt.x, pt.y);

					//###############################
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				}

			}
			break;

		case WM_KEYUP :
		case WM_KEYDOWN :
			{
				// ###########################################################
				gdiplus_map_view * woglv = 
					(gdiplus_map_view *)GetWindowLongPtr(hWnd,GWL_USERDATA);
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
		case WM_DESTROY:
		  {
			  // ###########################################################
			  gdiplus_map_view * woglv =
				  (gdiplus_map_view *)GetWindowLong(hWnd,GWL_USERDATA);
			  if (woglv)
			  {
				  woglv->GetProject()->RemoveMapView(woglv);	
			  }
			  // ###########################################################
		  GdiplusShutdown(gdiplusToken);
		  }
		  break;
	  default:
		  return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
extern HINSTANCE hInst;   // текущий экземпляр

HWND MakeMapGDIplusView(HWND hWndParent, void * lParam, char * win_name)
{
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	printf("MakeMapGDIplusView lParam = %x\n", lParam);
	WNDCLASSEX wc;
	// Регистрация класса главного окна приложения.
	//............................................
	//........................................................................
	wc.style         	= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc   	= (WNDPROC)WndProcGDIplusMapView;
	wc.cbClsExtra    	= 0;
	wc.cbWndExtra    	= 0;
	wc.hInstance     	= hInst;
	wc.hIcon         	= LoadIcon(hInst, (LPCTSTR)IDI_ICON_SURF_CUBE);
	wc.hCursor       	= LoadCursor(NULL, IDC_ARROW);
	//wc.hbrBackground 	= (HBRUSH)(COLOR_WINDOW+1);
	wc.hbrBackground 	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU_GDIPLUS_MAP_VIEW);
	wc.lpszClassName	= "GDI plus Map View";
	wc.cbSize        	= sizeof(WNDCLASSEX);
	wc.hIconSm       	= LoadIcon(wc.hInstance, (LPCTSTR)IDI_SMALL);

//printf("MakeGhemicalPlot 2\n");

	//**************************************

	if ( !RegisterClassEx( &wc ) )
	{
		DWORD dwError = GetLastError();
		if(1410 != dwError)// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","PrintPreview",0);
			LPVOID lpMsgBuf;

			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwError,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
			);
			char str[100];
			sprintf(str, "RegisterClassEx dwError = %x",dwError);
			::MessageBox(NULL, (LPCTSTR)lpMsgBuf, str, MB_OK);
		}
		else
		{
			//MessageBox(0,"класс уже существует","WinSurf",0);
		}
	}






	RECT r;
	GetWindowRect(hWndParent, &r);

	LONG W = r.right - r.left;
	LONG H = r.bottom - r.top;
	LONG w = W;
	//LONG h = H/2;
	LONG h = H;




	HWND hMapWnd = CreateWindow( "GDI plus Map View",
		win_name,
		WS_OVERLAPPEDWINDOW,
		r.left, r.top+H-h,
		w, h,
		hWndParent,	
		NULL,
		hInst,
		(void *) lParam
		//(void *) GetWindowLongPtr(hwnd,GWLP_USERDATA)
		);

	if( ! hMapWnd)
	{
		MessageBox(0,"! hPlotWnd","",0);
	}

	ShowWindow(hMapWnd, 1);

	return hMapWnd;
}







#include "win32_map_views.h"

/*################################################################################################*/

/*GtkActionEntry gdiplus_map_view::entries[] =
{
	{ "AttachDetachPlot1D", NULL, "Attach/Detach This View", NULL, "Select whether this view is attached or in an independent window", (GCallback) gdiplus_map_view::popup_AttachDetach },
	{ "DeleteViewPlot1D", NULL, "Delete View", NULL, "Delete this view", (GCallback) gdiplus_map_view::popup_DeleteView }
};
*/
const char * gdiplus_map_view::ui_description =
"<ui>"
"  <popup name='gp1dvMenu'>"
"    <menuitem action='AttachDetachPlot1D'/>"
"    <separator/>"
"    <menuitem action='DeleteViewPlot1D'/>"
"  </popup>"
"</ui>";
	
buff_gdiplus_map_view::buff_gdiplus_map_view(win_project * p1, Object * ob)
: gdiplus_map_view(p1, ob), g(new Graphics(GetHDC())), selectBuffer1(new Bitmap(win_size[0],win_size[1], g)), selectBuffer2(new Bitmap(win_size[0],win_size[1], g))
{
}
buff_gdiplus_map_view::~buff_gdiplus_map_view()
{
}
gdiplus_map_view::gdiplus_map_view(win_project * p1, Object * ob)
	: win_gdiplus_view(p1), map_view(ob) 
	//,win_view::view_widget(MakeMapGDIplusView(prj->hSurfWnd, (void*)this, this->m_ob ? this->m_ob->GetName().c_str() : "profile view")),
	//selectBuffer(200, 200, PixelFormat32bppARGB)//PixelFormat48bppRGB)
{
	//this->view_widget = MakeMapGDIplusView(prj->GetWidget(), (void*) dynamic_cast<win_gdiplus_view*>(this), "plot 1D");
	this->view_widget = MakeMapGDIplusView(prj->hSurfWnd, (void*)this, this->m_ob ? this->m_ob->GetName().c_str() : "profile view");

	//cout << "view_widget = " << view_widget << endl;
	
	SendMessage(view_widget, WM_COMMAND, ID_FILE_INITOG, 0);
	SendMessage(view_widget, WM_COMMAND, ID_FILE_INITOG2, 0);

	ConfigureHandler(view_widget);

	

	RECT rect;
	GetClientRect(view_widget, &rect);
	this->x_center = double(rect.right - rect.left)/2.0;
	this->y_center = double(rect.bottom - rect.top)/2.0;

	this->zoom_x = max(double(rect.right - rect.left), double(rect.bottom - rect.top));
	this->zoom_y = max(double(rect.right - rect.left), double(rect.bottom - rect.top));


	if(this->m_ob && this->m_ob->GetDoc())
	{
		//m_zoomZ = m_zoomCoefXYZ * m_zoomX;
		this->zoom_y = this->m_ob->GetDoc()->m_zoomCoefXYZ * this->zoom_x;
	}

	printf("this->x_center = %f, this->y_center = %f\n", this->x_center, this->y_center);
	printf("this->zoom_x = %f, this->zoom_y = %f\n", this->zoom_x, this->zoom_y);
//	win_label_set_text(GTK_LABEL(label_widget), "1D plot view");	// fixme!!!
	
//	GtkActionGroup * action_group = win_action_group_new("gp1dvActions");
//	win_action_group_add_actions(action_group, entries, G_N_ELEMENTS(entries), win_WIDGET(view_widget));
	
//	win_ui_manager_insert_action_group(win_app::GetUIManager(), action_group, 0);
	
//	GError * error = NULL;
//	if (!win_ui_manager_add_ui_from_string(win_app::GetUIManager(), ui_description, -1, & error))
//	{
//		g_message("Building gp1dv menu failed : %s", error->message);
//		g_error_free(error); exit(EXIT_FAILURE);
//	}
	
	// set win_view::popupmenu so that win_gdiplus_view::ButtonHandler() will display it...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
//	popupmenu = win_ui_manager_get_widget(win_app::GetUIManager(), "/gp1dvMenu");
	useWellElementInContextMenu = false;
}

gdiplus_map_view::~gdiplus_map_view(void)
{
}

void gdiplus_map_view::ExposeEvent(void)
{
//	GdkGLContext * glcontext = win_widget_get_gl_context(view_widget);
//	GdkGLDrawable * gldrawable = win_widget_get_gl_drawable(view_widget);

	SetCurrent(); Render(); //glFlush();
	
//	if (gdk_gl_drawable_is_double_buffered(gldrawable)) gdk_gl_drawable_swap_buffers(gldrawable);
//	else glFlush();
	
//win_gl_area_swapbuffers(win_GL_AREA(view_widget));	// older way??? see win_graphics_view::ExposeEvent()
}
void gdiplus_map_view::Update(bool directly)
{
//printf("win_gdiplus_view::Update = %d\n", directly);
	if (!is_realized) g_print("WARNING : Update() called before widget was realized ; skipping...\n");
	else
	{
#if 0
			RECT rect;
			GetClientRect(view_widget,&rect);
			InvalidateRect(view_widget,&rect, true);
#else
		if (directly) ExposeEvent();
//		else win_widget_queue_draw(view_widget);
		else
		{
			RECT rect;
			GetClientRect(view_widget,&rect);
			InvalidateRect(view_widget,&rect, true);
		}
#endif
	}
	// here we update always directly. should emit an update request for indirect rendering!?!?!?
	// here we update always directly. should emit an update request for indirect rendering!?!?!?
	// here we update always directly. should emit an update request for indirect rendering!?!?!?
}

void gdiplus_map_view::InitGDI(void)
{
	// Initialize GDI+.
	//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

bool gdiplus_map_view::SetCurrent(void)
{
	return true;
}
int buff_gdiplus_map_view::ConfigureHandler(HWND widget)		// EVENT_HANDLER
{
	int res = this->win_gdiplus_view::ConfigureHandler(widget);
//printf("buff_gdiplus_map_view::Render win_size[0] %d win_size[1] %d\n",
//	   win_size[0], win_size[1]);

	if (g) delete g;
	if (selectBuffer1) delete selectBuffer1;
	if (selectBuffer2) delete selectBuffer2;

	g = new Graphics(GetHDC());
	selectBuffer1 = new Bitmap(win_size[0],win_size[1], g);
	selectBuffer2 = new Bitmap(win_size[0],win_size[1], g);
	
	return res;
}
void buff_gdiplus_map_view::Render(void)
{
	//RECT rc;
	//GetClientRect(view_widget, &rc);    
	//Bitmap backBuffer(rc.right, rc.bottom, &g);
//printf("buff_gdiplus_map_view::Render win_size[0] %d win_size[1] %d\n",
//	   win_size[0], win_size[1]);

	Bitmap backBuffer(win_size[0], win_size[1], g);
    Graphics temp(&backBuffer);
			
    Graphics select1(selectBuffer1);
    Graphics select2(selectBuffer2);

	Graphics * select[2];
	select[0] = &select1;
	select[1] = &select2;
			
	select1.Clear(Color(0,0,0));
	select2.Clear(Color(0,0,0));	

	temp.Clear(Color(255,255,255));

	this->m_ob->DrawGDIplus(select, temp, this);
	//g.DrawImage(&backBuffer, 0, 0, 0, 0, rc.right, rc.bottom, UnitPixel);
	//g.DrawImage(&backBuffer, 0, 0, rc.right, rc.bottom);
//	if(g) g->DrawImage(selectBuffer1, 0, 0, 0, 0, win_size[0], win_size[1], UnitPixel);
	if(g) g->DrawImage(&backBuffer, 0, 0, win_size[0], win_size[1]);

}
void gdiplus_map_view::popup_AttachDetach(HWND widget, void *)
{
	win_gdiplus_view * oglv = GetGDIV(widget);
	gdiplus_view * old_p1dv = dynamic_cast<gdiplus_view *>(oglv);
	if (old_p1dv == NULL)
	{
		cout << "cast failed at gdiplus_map_view::popup_AttachDetach()." << endl;
		return;
	}
	
	// first we create a new view using the requested mode...
	
#if 0
	i32s ud1 = old_p1dv->getUD1();
	const char * s1 = old_p1dv->getN1();
	const char * sv = old_p1dv->getNV();
	bool flag = (oglv->detached == NULL);
	
	gdiplus_view * new_p1dv = oglv->prj->AddGDIMapView(ud1, s1, sv, flag);
	
	// try to retain as much data/settings as possible.
	
	new_p1dv->ImportData(old_p1dv);
#endif
	// ...and then simply destroy the old one; calling popup_ViewsDeleteView()
	// below this is the same as selecting "Delete This View" from the popup-menu.
	
	popup_DeleteView(widget, NULL);
//	new_p1dv->GetProject()->UpdateAllWindowTitles();
}

void gdiplus_map_view::popup_DeleteView(HWND widget, void *)
{
	win_gdiplus_view * oglv = GetGDIV(widget);
	
	if (oglv->detached != NULL)
	{
//		win_widget_destroy(win_WIDGET(oglv->detached));
	}
	else
	{
//		gint page = win_notebook_page_num(win_NOTEBOOK(oglv->prj->notebook_widget), oglv->view_widget);
//		win_notebook_remove_page(win_NOTEBOOK(oglv->prj->notebook_widget), page);
	}
	
	gdiplus_map_view * gv = dynamic_cast<gdiplus_map_view *>(oglv);
	if (gv == NULL) { cout << "cast failed at gdiplus_map_view::popup_DeleteView()!" << endl; exit(EXIT_FAILURE); }
	
	//oglv->prj->RemovePlottingView(pv);
	oglv->prj->RemoveMapView(gv);
	// TODO : delete the object and release memory ; is it done already???
}
void gdiplus_map_view::CreateMyPopupMenu(HWND hWnd)
{
	HMENU hMenu = CreatePopupMenu();
	//AppendMenu( hMenu, MFT_STRING, 4000, "&Prop..." );
	//AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	MENUITEMINFO   mii;				
	mii.cbSize = sizeof( MENUITEMINFO );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	HMENU hSubMenu = NULL;
	HMENU hSubMenu2 = NULL;
	if (useWellElementInContextMenu)
	{
		Well_Laboratory_Analize::FillPopupMenu(hMenu, hSubMenu, hSubMenu2);

		mii.fMask  = MIIM_ID | MIIM_TYPE;
		mii.fType  = MFT_SEPARATOR;
		InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_SURF_FON_COLOR;
	mii.dwTypeData = "&Fon color";
    InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_SURFTEST_FONT;
	mii.dwTypeData = "Fon&t";
    InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	POINT point;
	GetCursorPos(&point);
	
	TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
		TPM_TOPALIGN |
		TPM_LEFTALIGN, 
		point.x,
		point.y, 0, hWnd, NULL );
	
	DestroyMenu( hMenu );
	if(hSubMenu)
		DestroyMenu( hSubMenu );
	if(hSubMenu2)
		DestroyMenu( hSubMenu2 );

}


void FillCircle(Graphics * graphics, fGL xc, fGL yc, fGL r, Color & gdi_color)
{
   // Create a SolidBrush object.
   SolidBrush gdi_Brush(gdi_color);

   // Initialize the variables that define the ellipse.
   int x = xc - r;
   int y = yc - r;
   int width = 2*r;
   int height = 2*r;

   // Fill the ellipse.
   graphics->FillEllipse(&gdi_Brush, x, y, width, height);
}
void HatchFillCircle(Graphics * graphics, fGL xc, fGL yc, fGL r, HatchStyle hs, Color & foreColor, Color & backColor)
{
   // Create a HatchBrush object.

   HatchBrush brush(hs, foreColor, backColor);

   // Initialize the variables that define the ellipse.
   int x = xc - r;
   int y = yc - r;
   int width = 2*r;
   int height = 2*r;

   // Fill the ellipse.
   graphics->FillEllipse(&brush, x, y, width, height);
}

void DrawCircle(Graphics * graphics, fGL xc, fGL yc, fGL r, Color & gdi_color)
{
   // Create a pen.
   Pen      pen(gdi_color);

   // Initialize the variables that define the ellipse.
   int x = xc - r;
   int y = yc - r;
   int width = 2*r;
   int height = 2*r;

   // Fill the ellipse.
   graphics->DrawEllipse(&pen, x, y, width, height);
}

/*################################################################################################*/

// eof
