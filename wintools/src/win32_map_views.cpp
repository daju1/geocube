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

#define g_print printf

LRESULT CALLBACK WndProcMapView(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//static	HGLRC		m_hRC;				// Контекст OpenGL
	//static	HDC			m_hdc; 			// Контекст Windows
	static COLORREF acrCustClr[16]; // array of custom colors 
	static DWORD rgbCurrent;        // initial color selection


	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
/*			case ID_FILE_SAVEAS32867:
				{			
					//######################################################
					win_ogl_view * wgrv = 
						(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
					if (wgrv)
					{
						plot1d_view * p1dv = dynamic_cast<plot1d_view *>(wgrv);
						if (p1dv)
						{
							p1dv->SaveAs();
						}
					}
					//######################################################
				}
				break;*/
			case ID_SURF_FON_COLOR:
				{
					CHOOSECOLOR cc;                 // common dialog box structure 
					HBRUSH hbrush;                  // brush handle
					//static COLORREF acrCustClr[16]; // array of custom colors 
					//static DWORD rgbCurrent;        // initial color selection

					// Initialize CHOOSECOLOR 
					ZeroMemory(&cc, sizeof(cc));
					cc.lStructSize = sizeof(cc);
					cc.hwndOwner = hWnd;
					cc.lpCustColors = (LPDWORD) acrCustClr;
					cc.rgbResult = rgbCurrent;
					cc.Flags = CC_FULLOPEN | CC_RGBINIT;

					if (ChooseColor(&cc)==TRUE) {
						hbrush = CreateSolidBrush(cc.rgbResult);
						rgbCurrent = cc.rgbResult; 
					}
					glClearColor (float(GetRValue(rgbCurrent))/255.f, float(GetGValue(rgbCurrent))/255.f,float(GetBValue(rgbCurrent))/255.f, 1.f); 
					//====== Перерисовываем Вид с учетом изменений
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);

				}
				break;
			case ID_VIEW_UPDATEALLVIEWS:
				{
					//######################################################
					win_ogl_view * wgrv = 
						(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
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
					win_ogl_view * wgrv = 
						(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
					if (wgrv)
					{
						wgrv->RealizeHandler(hWnd, NULL);
						wgrv->InitGL();
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
//				  printf("WM_CREATE ");
//				  cout << "hWnd = " << hWnd << endl << endl;
//				  SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG, 0);
				  //##################################################
				  //##################################################
				  win_ogl_view * wogv = 
					  (win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
				  if (wogv)
				  {
					  wogv->SetWindow(hWnd);

					  /*project * prj = wogv->GetProject();
					  win_project * w_prj = dynamic_cast<win_project *>(prj);
					  if (w_prj)
					  {
						  w_prj->paned_widget = hWnd;
						  printf("w_prj->paned_widget = 0x%08x\n", w_prj->paned_widget);
					  }*/
				  }
				  //##################################################


              }
              break;
		case WM_ERASEBKGND:
			{
				return true;
			}
			break;
		case WM_SIZE:
			{
				// ###########################################################
				win_ogl_view * woglv = 
					(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (woglv)
				{
					woglv->ConfigureHandler(hWnd);
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

				win_ogl_view * woglv = (win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);

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
		case WM_LBUTTONDBLCLK :
		case WM_RBUTTONDBLCLK :
		case WM_MBUTTONDBLCLK :
		case WM_LBUTTONDOWN :
		case WM_RBUTTONDOWN :
		case WM_MBUTTONDOWN :
		case WM_LBUTTONUP :
		case WM_RBUTTONUP :
		case WM_MBUTTONUP :
			{
				// ###########################################################
				win_ogl_view * woglv = 
					(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (woglv)
				{
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
				win_ogl_view * woglv = 
					(win_ogl_view *)GetWindowLong(hWnd,GWL_USERDATA);
				if (woglv)
				{
					woglv->MotionNotifyHandler(hWnd, wParam, lParam);	
				}
				// ###########################################################
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
						
			}
			break;

		case WM_DESTROY:
			//PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
extern HINSTANCE hInst;   // текущий экземпляр

HWND MakeMapView(HWND hwnd, void * lParam, char * win_name)
{
//	printf("MakeGhemicalPlot lParam = %x\n", lParam);
	WNDCLASSEX wc;
	// Регистрация класса главного окна приложения.
	//............................................
	//........................................................................
	wc.style         	= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   	= (WNDPROC)WndProcMapView;
	wc.cbClsExtra    	= 0;
	wc.cbWndExtra    	= 0;
	wc.hInstance     	= hInst;
	wc.hIcon         	= LoadIcon(hInst, (LPCTSTR)IDI_ICON_SURF_CUBE);
	wc.hCursor       	= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground 	= (HBRUSH)(COLOR_WINDOW+1);
	//wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU_MAP_VIEW);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU_GDIPLUS_MAP_VIEW);
	wc.lpszClassName	= "Map View";
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
	GetWindowRect(hwnd, &r);

	LONG W = r.right - r.left;
	LONG H = r.bottom - r.top;
	LONG w = W/4;
	LONG h = H/2;




	HWND hMapWnd = CreateWindow( "Map View",
		win_name,
		WS_OVERLAPPEDWINDOW,
		r.left+W-w, r.top+H-h,
		w, h,
		hwnd,	
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

/*GtkActionEntry win_map_view::entries[] =
{
	{ "AttachDetachPlot1D", NULL, "Attach/Detach This View", NULL, "Select whether this view is attached or in an independent window", (GCallback) win_map_view::popup_AttachDetach },
	{ "DeleteViewPlot1D", NULL, "Delete View", NULL, "Delete this view", (GCallback) win_map_view::popup_DeleteView }
};
*/
const char * win_map_view::ui_description =
"<ui>"
"  <popup name='gp1dvMenu'>"
"    <menuitem action='AttachDetachPlot1D'/>"
"    <separator/>"
"    <menuitem action='DeleteViewPlot1D'/>"
"  </popup>"
"</ui>";

win_map_view::win_map_view(win_project * p1, Object * ob)
	: win_ogl_view(p1), map_view(ob)
{
//printf("win_map_view\n");
	//здесь надо создать окно графика !!! наподобие как в конструкторе класса 
	//win_graphics_view::win_graphics_view(win_project * p1, camera * p2) 
	//:	win_ogl_view(p1), graphics_view(p2), ogl_view()
	

	select_buffer = new iGLu[SB_SIZE];



	this->view_widget = MakeMapView(prj->GetWidget(), (void*) dynamic_cast<win_ogl_view*>(this), this->m_ob ? this->m_ob->GetName().c_str() : "profile view");

	//cout << "view_widget = " << view_widget << endl;
	
	SendMessage(view_widget, WM_COMMAND, ID_FILE_INITOG, 0);
	SendMessage(view_widget, WM_COMMAND, ID_FILE_INITOG2, 0);

	ConfigureHandler(view_widget);
	
	
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
	
	// set win_view::popupmenu so that win_ogl_view::ButtonHandler() will display it...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
//	popupmenu = win_ui_manager_get_widget(win_app::GetUIManager(), "/gp1dvMenu");
}

win_map_view::~win_map_view(void)
{
	delete[] select_buffer;
}
void win_map_view::InitGL(void)
{
	SetCurrent();
	
//	prefs * model_prefs = mdl->model_prefs;		// needed elsewhere???

//	const fGL background[4] = { 0.0, 0.0, 0.0, 1.0};
//  const fGL background[4] = { 0.5, 1.0, 0.5, 0.1};
    const fGL background[4] = { 1.0, 1.0, 1.0, 1.0};
//	fGL * background = model_prefs->ColorRGBA("Graphics/BkgndColor", default_background);
	glClearColor(background[0], background[1], background[2], background[3]);
//delete[] background;
	glDepthFunc(GL_LESS); glEnable(GL_DEPTH_TEST);
	
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	const fGL specular_reflectance[4] = { 0.9, 0.9, 0.9, 1.0 };
//	fGL * specular_reflectance = model_prefs->ColorRGBA("Graphics/SpecularReflectance", default_reflectance);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_reflectance);
//delete[] specular_reflectance;
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glSelectBuffer(SB_SIZE, select_buffer);
}


void win_map_view::ExposeEvent(void)
{
//	GdkGLContext * glcontext = win_widget_get_gl_context(view_widget);
//	GdkGLDrawable * gldrawable = win_widget_get_gl_drawable(view_widget);

	SetCurrent(); Render(); glFlush();
	
//	if (gdk_gl_drawable_is_double_buffered(gldrawable)) gdk_gl_drawable_swap_buffers(gldrawable);
//	else glFlush();
	
//win_gl_area_swapbuffers(win_GL_AREA(view_widget));	// older way??? see win_graphics_view::ExposeEvent()
}

void win_map_view::Render(void)
{
	if (size[0] < 0) return;			// skip rendering if invalid window!!!
//	prefs * model_prefs = mdl->model_prefs;		// needed elsewhere???

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set projection and call gluLookAt() to set up our "eye".
	
	i32s width = size[0]; i32s height = size[1]; glViewport(0, 0, width, height);
	glOrtho(-0.1, +1.1, -0.1, +1.1, -0.5, +1.5);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
//	const fGL default_label_color[3] = { 1.0, 1.0, 1.0 };
//	fGL * label_color = model_prefs->ColorRGB("Graphics/LabelColor", default_label_color);

	glInitNames();


//	this->m_ob->DrawGDIplus(this);

//	this->m_ob->Draw2D(this);

/*	for (i32s n1 = 0;n1 < ((i32s) dv.size()) - 1;n1++)
	{
		glColor3f(1.0, 0.0, 0.0);	// red
		//glColor3f(0.0, 1.0, 0.0);	// green
		glBegin(GL_LINES); fGL x; fGL y;
		
		x = (dv[n1].c1 - min1) / (max1 - min1);
		y = (dv[n1].v - minv) / (maxv - minv);
		glVertex3f(x, y, 0.1);
		
		x = (dv[n1 + 1].c1 - min1) / (max1 - min1);
		y = (dv[n1 + 1].v - minv) / (maxv - minv);
		glVertex3f(x, y, 0.1);
		
		glEnd();
	}*/
}


void win_map_view::Update(bool directly)
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
void win_map_view::popup_AttachDetach(HWND widget, void *)
{
	win_ogl_view * oglv = GetOGLV(widget);
	map_view * old_p1dv = dynamic_cast<map_view *>(oglv);
	if (old_p1dv == NULL)
	{
		cout << "cast failed at win_map_view::popup_AttachDetach()." << endl;
		return;
	}
	
	// first we create a new view using the requested mode...
#if 0
//	i32s ud1 = old_p1dv->getUD1();
//	const char * s1 = old_p1dv->getN1();
//	const char * sv = old_p1dv->getNV();
	bool flag = (oglv->detached == NULL);
	
	map_view * new_p1dv = oglv->prj->AddMapView(flag);
	
	// try to retain as much data/settings as possible.
	
//	new_p1dv->ImportData(old_p1dv);
#endif
	// ...and then simply destroy the old one; calling popup_ViewsDeleteView()
	// below this is the same as selecting "Delete This View" from the popup-menu.
	
	popup_DeleteView(widget, NULL);
//	new_p1dv->GetProject()->UpdateAllWindowTitles();
}

void win_map_view::popup_DeleteView(HWND widget, void *)
{
	win_ogl_view * oglv = GetOGLV(widget);
	
	if (oglv->detached != NULL)
	{
//		win_widget_destroy(win_WIDGET(oglv->detached));
	}
	else
	{
//		gint page = win_notebook_page_num(win_NOTEBOOK(oglv->prj->notebook_widget), oglv->view_widget);
//		win_notebook_remove_page(win_NOTEBOOK(oglv->prj->notebook_widget), page);
	}
	
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv == NULL) { cout << "cast failed at win_map_view::popup_DeleteView()!" << endl; exit(EXIT_FAILURE); }
	
	oglv->prj->RemovePlottingView(pv);
	// TODO : delete the object and release memory ; is it done already???
}
void win_map_view::CreateMyPopupMenu(HWND hWnd)
{
	HMENU hMenu = CreatePopupMenu();
	//AppendMenu( hMenu, MFT_STRING, 4000, "&Prop..." );
	//AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	MENUITEMINFO   mii;				
	mii.cbSize = sizeof( MENUITEMINFO );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


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
}




/*################################################################################################*/

// eof
