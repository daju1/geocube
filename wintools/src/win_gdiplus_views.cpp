// WIN32_VIEWS.CPP

// Copyright (C) 1998 Tommi Hassinen, Jarno Huuskonen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/
#include "stdafx.h"
#include "../resource.h"
#include "../../wintools/src/appdefine.h"

#include "win32_views.h"	// config.h is here -> we get ENABLE-macros here...

//#include "../libghemical/src/engine.h"
#include "utility.h"
//#include "../consol/winghemical.h"

#include "win32_project.h"
#include "win32_project_view.h"	// temporary ; attach/detach
#include "win32_graphics_view.h"	// temporary ; attach/detach
#include "win32_plot_views.h"	// temporary ; attach/detach
#include "win32_map_views.h"	// temporary ; attach/detach

//#include <gnome.h>
//#include <gdk/gdkglconfig.h>

//#include <gtk/gtk.h>

#include <strstream>
#include <algorithm>
using namespace std;


#define g_print printf
/*################################################################################################*/
extern LPCTSTR lpszWinSurf;
extern LPCTSTR lpszSurfTitle;
extern HINSTANCE hInst;


/*################################################################################################*/
/*################################################################################################*/

vector<win_gdiplus_view *> win_gdiplus_view::gdi_vector;
//HGLRC * win_gdiplus_view::m_CurrentOGContext = NULL;


win_gdiplus_view::win_gdiplus_view(win_project * p1) : gdiplus_view(), win_view(p1)
{
printf("win_gdiplus_view::win_gdiplus_view(win_project * p1) : gdiplus_view(), win_view(p1)\n\n");

	hDigitizeCursor = NULL;
	detached = NULL;//pointer to window?
	
	is_realized = false;
	gdi_vector.push_back(this);

	/*
	HWND hWnd = p1->GetWindow();

	SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG, 0);

	printf("win_gdiplus_view ");
	cout << "hWnd = " << hWnd << endl << endl;*/


#if 0
	
	gint major; gint minor;
	gdk_gl_query_version(& major, & minor);
	g_print("OpenGL extension version - %d.%d\n", major, minor);
	
	GdkGLConfig * glconfig; GdkGLConfigMode mode;
	
	mode = (GdkGLConfigMode) (GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE);
	glconfig = gdk_gl_config_new_by_mode(mode);	// try double-buffered visual...
	
	if (glconfig == NULL)
	{
		g_print("*** Cannot find the double-buffered visual.\n");
		g_print("*** Trying single-buffered visual.\n");
		
		mode = (GdkGLConfigMode) (GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH);
		glconfig = gdk_gl_config_new_by_mode(mode);	// try single-buffered visual...
		
		if (glconfig == NULL)
		{
			g_print("*** No appropriate OpenGL-capable visual found.\n");
			exit (1);
		}
	}
	
	view_widget = gtk_drawing_area_new();
	gtk_widget_set_size_request(view_widget, 400, 400);	// minimum size...
	
	gtk_widget_set_gl_capability(view_widget, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);
	
	int events = GDK_EXPOSURE_MASK;
	events |= GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK;
	events |= GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK;
	gtk_widget_set_events(GTK_WIDGET(view_widget), events);
	
	gtk_signal_connect_after(GTK_OBJECT(view_widget), "realize", GTK_SIGNAL_FUNC(RealizeHandler), NULL);	// after!!!
	
	gtk_signal_connect(GTK_OBJECT(view_widget), "expose_event", GTK_SIGNAL_FUNC(ExposeHandler), NULL);
	gtk_signal_connect(GTK_OBJECT(view_widget), "motion_notify_event", GTK_SIGNAL_FUNC(MotionNotifyHandler), NULL);
	gtk_signal_connect(GTK_OBJECT(view_widget), "button_press_event", GTK_SIGNAL_FUNC(ButtonHandler), NULL);
	gtk_signal_connect(GTK_OBJECT(view_widget), "button_release_event", GTK_SIGNAL_FUNC(ButtonHandler), NULL);
	gtk_signal_connect(GTK_OBJECT(view_widget), "configure_event", GTK_SIGNAL_FUNC(ConfigureHandler), NULL);
	
	gtk_widget_show(GTK_WIDGET(view_widget));
#endif
}

win_gdiplus_view::~win_gdiplus_view(void)
{
	vector<win_gdiplus_view *>::iterator it1;
	it1 = find(gdi_vector.begin(), gdi_vector.end(), this);
	
	if (it1 != gdi_vector.end())
	{
		gdi_vector.erase(it1);
	}
	else
	{
		cout << "WARNING : unknown view_widget at ~win_gdiplus_view()!!!" << endl;
	}
}


//extern LOGFONT lf_Label;        // logical font structure
//extern int UseGLFont( HDC hDC,  IN CONST LOGFONTA * plf_Label);
bool win_gdiplus_view::InitDC(HWND hWnd)
{
	//====== Добываем дежурный контекст
	this->m_hdc = ::GetDC(hWnd);
	if (this->m_hdc)
		return true;
	else
		return false;
}

bool win_gdiplus_view::SetCurrent(void)
{
//printf("win_gdiplus_view::SetCurrent(void)\n\n");
	if (!is_realized)
	{
		g_print("WARNING : SetCurrent() called before widget was realized ; skipping...\n");
		return false;
	}
	else
	{
//		GdkGLContext * glcontext = win_widget_get_gl_context(view_widget);
//		GdkGLDrawable * gldrawable = win_widget_get_gl_drawable(view_widget);
		
	//	gdk_gl_drawable_wait_gl()	what are these???
	//	gdk_gl_drawable_wait_gdk()	what are these???
		
	//	if (!gdk_gl_drawable_make_current(gldrawable, glcontext))
/*		if (win_gdiplus_view::m_CurrentOGContext != &this->m_hRC)
		{
			//====== Пытаемся выбрать его в качестве текущего
			if ( wglMakeCurrent (this->m_hdc, this->m_hRC))
			{
				win_gdiplus_view::m_CurrentOGContext = &this->m_hRC;
				return true;
			}
			else
			{
				MessageBox(this->detached,"wglMakeCurrent::Error","On Create",0);
				g_print("ERROR : wglMakeCurrent() _gdiplus_gdiplus_tool in SetCurrent().\n");
				return false;
			}
		}
		else 
			return true;*/

		if (false)
		{
			g_print("ERROR : gdk_gl_drawable_make_current() _gdiplus_gdiplus_tool in SetCurrent().\n");
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}
extern BYTE ANDmaskCursor[];
extern BYTE XORmaskCursor[];

void win_gdiplus_view::SetDigitizeCursor(bool to_set)
{
	if (to_set)
	{
		this->hDigitizeCursor = CreateCursor( hInst,   // app. instance 
				15,                // horizontal position of hot spot 
				15,                 // vertical position of hot spot 
				32,                // cursor width 
				32,                // cursor height 
				ANDmaskCursor,     // AND mask 
				XORmaskCursor );   // XOR mask */
	}
	else
	{
		if(this->hDigitizeCursor)
			DestroyCursor(this->hDigitizeCursor);
		this->hDigitizeCursor = NULL;
	}
}


void win_gdiplus_view::RealizeHandler(HWND widget, void *)
{
	win_gdiplus_view * oglv = GetGDIV(widget);
	if (!oglv) cout << "Unknown ID in RealizeHandler !!!" << endl;
	else
	{
		oglv->is_realized = true;
		oglv->InitGDI();
	}
}

int win_gdiplus_view::ExposeHandler(HWND widget/*, GdkEventExpose * */)		// EVENT_HANDLER
{
	win_gdiplus_view * oglv = GetGDIV(widget);
	if (!oglv) cout << "Unknown ID in ExposeHandler !!!" << endl;
	else
	{
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS
		
		oglv->ExposeEvent();
		
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	}
	
//	return FALSE;	// why is that???
	return TRUE;	// why is that???
}


int button_event_lost_counter_gdi = 0;

int win_gdiplus_view::ButtonHandler(HWND widget, UINT message, WPARAM wParam, LPARAM lParam)

// EVENT_HANDLER

{
//printf("win_gdiplus_view::ButtonHandler\n");
	int x = LOWORD(lParam); // horizontal position of pointer, relative to the upper-left corner of the client area.
	int y = HIWORD(lParam); // vertical position of pointer 		}
	if (x > 32768) x -= 65536;
	if (y > 32768) y -= 65536;

	//printf("win_gdiplus_view::ButtonHandler x = %d y = %d\n", x, y); 
/*
	if( wParam &  MK_LBUTTON)
	{
	}
	//====== Если одновременно была нажата Ctrl,
	if (wParam & MK_CONTROL)
	{
	}
	if (wParam & MK_SHIFT )
	{
	}
	if	(wParam &  MK_RBUTTON )
	{
	}
*/	
	win_gdiplus_view * oglv = GetGDIV(widget);
	if (!oglv) cout << "Unknown ID in ButtonHandler !!!" << endl;
	else
	{
		mouse_gdiplus_tool::button tmpb; i32u tmps1;
		if( wParam &  MK_LBUTTON)
		{
			tmpb = mouse_gdiplus_tool::Left;
			tmps1 = MK_LBUTTON;
		}
		if( wParam &  MK_RBUTTON)
		{			
			tmpb = mouse_gdiplus_tool::Right;
			tmps1 = MK_RBUTTON;
		}
		if( wParam &  MK_MBUTTON)
		{			
			tmpb = mouse_gdiplus_tool::Middle;
			tmps1 = MK_MBUTTON;
		}
		
		mouse_gdiplus_tool::state tmps2;// = (eb->state & tmps1) ? mouse_gdiplus_tool::Up : mouse_gdiplus_tool::Down;
		switch(message)
		{
		case WM_LBUTTONDOWN:
			tmpb = mouse_gdiplus_tool::Left;
			tmps2 = mouse_gdiplus_tool::Down;
			break;
		case WM_LBUTTONDBLCLK:
			printf("WM_LBUTTONDBLCLK win_gdiplus_view::ButtonHandler\n");
			tmpb = mouse_gdiplus_tool::Left;
			tmps2 = mouse_gdiplus_tool::DblClk;
			break;
		case WM_LBUTTONUP:
			tmpb = mouse_gdiplus_tool::Left;
			tmps2 = mouse_gdiplus_tool::Up;
			break;
		case WM_RBUTTONDOWN:
			tmpb = mouse_gdiplus_tool::Right;
			tmps2 = mouse_gdiplus_tool::Down;
			break;
		case WM_RBUTTONDBLCLK:
			tmpb = mouse_gdiplus_tool::Right;
			tmps2 = mouse_gdiplus_tool::DblClk;
			break;
		case WM_RBUTTONUP:
			tmpb = mouse_gdiplus_tool::Right;
			tmps2 = mouse_gdiplus_tool::Up;
			break;
		case WM_MBUTTONDOWN:
			tmpb = mouse_gdiplus_tool::Middle;
			tmps2 = mouse_gdiplus_tool::Down;
			break;
		case WM_MBUTTONDBLCLK:
			tmpb = mouse_gdiplus_tool::Middle;
			tmps2 = mouse_gdiplus_tool::DblClk;
			break;
		case WM_MBUTTONUP:
			tmpb = mouse_gdiplus_tool::Middle;
			tmps2 = mouse_gdiplus_tool::Up;
			break;
		}
		
		if (tmps2 == mouse_gdiplus_tool::Down)
		{
			if (button == mouse_gdiplus_tool::None)
			{
				if (tmpb == mouse_gdiplus_tool::Right)
				{
// the popup menu is created here. pointer to the win_drawing_area
// widget is given as "user_data", and it is also passed to the popup
// hander callback function (instead of the original value).
// 2001-08-22 quick fix : check that we open the popup for
// a graphics view only (not for energy level diagrams).
//					graphics_view * gv = dynamic_cast<graphics_view *>(window);
//					if (gv == NULL) return TRUE;	// was not a graphics_view!!!
//					win_graphics_view * ggv = dynamic_cast<win_graphics_view *>(gv);
//					if (ggv == NULL) return TRUE;	// FIXME so that all views have their own popups!!!
//				//	win_popup_menu_do_popup(,NULL, NULL, NULL, window->view_widget, NULL);
//				//	win_menu_popup(win_MENU(GetWindow(widget)->prj->popupmenu), NULL, NULL, NULL, NULL, eb->button, eb->time);
//					win_menu_popup(win_MENU(ggv->popupmenu), NULL, NULL, NULL, NULL, eb->button, eb->time);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					win_gdiplus_view * oglv = GetGDIV(widget);
					oglv->CreateMyPopupMenu(widget);
/*					if (oglv != NULL && oglv->popupmenu != NULL)
					{
						win_menu_popup(win_MENU(oglv->popupmenu), NULL, NULL, NULL, NULL, eb->button, eb->time);
					}
*/					
					//return TRUE;
				}
				
				button = tmpb;
				
				shift_down = (wParam & MK_SHIFT) ? true : false;
				ctrl_down = (wParam & MK_CONTROL) ? true : false;
				
				state = mouse_gdiplus_tool::Down;
				
			//	cout << "button_event_D " << button << " " << state << " " << (gdiplus_view *) window << endl;
				current_gdiplus_tool->ButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
				button_event_lost_counter_gdi = 0;	// this is for exceptions, see below...
			}
		}
		else if (tmps2 == mouse_gdiplus_tool::DblClk)
		{
			if (button == mouse_gdiplus_tool::None)
			{				
				button = tmpb;
				
				shift_down = (wParam & MK_SHIFT) ? true : false;
				ctrl_down = (wParam & MK_CONTROL) ? true : false;
				
				state = mouse_gdiplus_tool::DblClk;
				
			//	cout << "button_event_D " << button << " " << state << " " << (gdiplus_view *) window << endl;
				current_gdiplus_tool->ButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
				button_event_lost_counter_gdi = 0;	// this is for exceptions, see below...
			}
		}
		else
		{
			if (button == mouse_gdiplus_tool::Left && tmpb != mouse_gdiplus_tool::Left) return TRUE;
			if (button == mouse_gdiplus_tool::Middle && tmpb != mouse_gdiplus_tool::Middle) return TRUE;
			if (button == mouse_gdiplus_tool::Right && tmpb != mouse_gdiplus_tool::Right) return TRUE;
			
			state = mouse_gdiplus_tool::Up;
			
		//	cout << "button_event_U " << button << " " << state << " " << (gdiplus_view *) window << endl;
			current_gdiplus_tool->ButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
			
			button = mouse_gdiplus_tool::None;
		}
	}
	
	return TRUE;
}

int win_gdiplus_view::KeyButtonHandler(HWND widget, UINT message, WPARAM wParam, LPARAM lParam)

// EVENT_HANDLER

{	
	static int x = 0; // horizontal position of pointer 
	static int y = 0; // vertical position of pointer 		}
	
	win_gdiplus_view * oglv = GetGDIV(widget);
	if (!oglv) cout << "Unknown ID in ButtonHandler !!!" << endl;
	else
	{
		key_gdiplus_tool::key_state tmps2;// = (eb->state & tmps1) ? mouse_gdiplus_tool::Up : mouse_gdiplus_tool::Down;
		switch(message)
		{
		case WM_KEYDOWN:
			tmps2 = key_gdiplus_tool::key_state::KeyDown;
	printf("WM_KEYDOWN wParam = %d lParam = 0x%08x previous key state = %d\n", wParam, lParam, int(lParam & 0x40000000));
			break;
		case WM_KEYUP:
			tmps2 = key_gdiplus_tool::key_state::KeyUp;
			break;
		}
		
		key_gdiplus_tool::key tmpk;// i32u tmps1;
		switch (wParam)
		{
		case 97:
		case 49://1
			{
				key_gdiplus_tool::speed = 1;
			}
			break;
		case 98:
		case 50://2
			{
				key_gdiplus_tool::speed = 2;
			}
			break;
		case 99:
		case 51://3
			{
				key_gdiplus_tool::speed = 3;
			}
			break;
		case 100:
		case 52://4
			{
				key_gdiplus_tool::speed = 4;
			}
			break;
		case 101:
		case 53://5
			{
				key_gdiplus_tool::speed = 5;
			}
			break;
		case 102:
		case 54://6
			{
				key_gdiplus_tool::speed = 6;
			}
			break;
		case 103:
		case 55://7
			{
				key_gdiplus_tool::speed = 7;
			}
			break;
		case 104:
		case 56://8
			{
				key_gdiplus_tool::speed = 8;
			}
			break;
		case 105:
		case 57://9
			{
				key_gdiplus_tool::speed = 9;
			}
			break;
		case 96:
		case 48://0
			{
				key_gdiplus_tool::speed = 10;
			}
			break;
		case 90://z
			{
				tmpk = key_gdiplus_tool::key::keyZ;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_zoom;
					key_gdiplus_tool::speed = 25;
				}
				return TRUE;
			}
			break;		
		case 67://c
			{
				tmpk = key_gdiplus_tool::key::keyC;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_clipping;
					key_gdiplus_tool::speed = 25;
				}
				return TRUE;
			}
			break;
		case 84://t
			{
				tmpk = key_gdiplus_tool::key::keyT;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_translate_xy;
					key_gdiplus_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 71://g
			{
				tmpk = key_gdiplus_tool::key::keyG;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_translate_z;
					key_gdiplus_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 79://o
			{
				tmpk = key_gdiplus_tool::key::keyO;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_orbit_xy;
					key_gdiplus_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 76://l
			{
				tmpk = key_gdiplus_tool::key::keyL;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_orbit_z;
					key_gdiplus_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 82://r
			{
				tmpk = key_gdiplus_tool::key::keyR;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_rotate_xy;
					key_gdiplus_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 70://f
			{
				tmpk = key_gdiplus_tool::key::keyF;
				if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
				{
					gdiplus_view::current_key_gdiplus_tool = & gdiplus_view::key_gdiplus_tool_rotate_z;
					key_gdiplus_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		}

		if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
		{
			gdiplus_view::key_state = key_gdiplus_tool::key_state::KeyDown;
			
			if (!(lParam & 0x40000000))// previous key state
			{
				if (!this->current_gdiplus_tool->KeyButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y))
					current_key_gdiplus_tool->KeyButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
			}
			
			gdiplus_view::key_state = key_gdiplus_tool::key_state::KeyUnknown;
		}
		switch (wParam)
		{
		case 16:// Shift
			{
				//m_bShiftPressed = true;
				tmpk = key_gdiplus_tool::key::keyShift;
			}
			break;
		case 17:// Ctrl
			{
				//m_bCtrlPressed = true;
				tmpk = key_gdiplus_tool::key::keyCtrl;
			}
			break;
		case 38:// up
			{
				y+=key_gdiplus_tool::speed;
				//m_zTrans += 0.05f;
				tmpk = key_gdiplus_tool::key::keyUp;
			}
			break;
		case 40:// down
			{
				y-=key_gdiplus_tool::speed;
				//m_zTrans -= 0.05f;
				tmpk = key_gdiplus_tool::key::keyDown;
			}
			break;
		case 37:// left
			{
				x+=key_gdiplus_tool::speed;
				tmpk = key_gdiplus_tool::key::keyLeft;
			}
			break;
		case 39:// right
			{
				x-=key_gdiplus_tool::speed;
				tmpk = key_gdiplus_tool::key::keyRight;
			}
			break;
		case 33:// page up
			{
				tmpk = key_gdiplus_tool::key::keyUp;
			}
			break;
		case 34:// page down
			{
				tmpk = key_gdiplus_tool::key::keyDown;
			}
			break;
		}
		
		if (tmps2 == key_gdiplus_tool::key_state::KeyDown)
		{
			gdiplus_view::key_state = key_gdiplus_tool::key_state::KeyDown;
			
			if (x > 32768) x -= 65536;
			if (y > 32768) y -= 65536;

			current_key_gdiplus_tool->KeyMotionEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
			
			gdiplus_view::key_state = key_gdiplus_tool::key_state::KeyUnknown;
		}
	}
	
	return TRUE;
}

int win_gdiplus_view::ConfigureHandler(HWND widget/*, GdkEventConfigure * */)		// EVENT_HANDLER
{
	win_gdiplus_view * oglv = GetGDIV(widget);
	if (!oglv) cout << "Unknown ID in ConfigureHandler !!!" << endl;
	else
	{		
		oglv->SetCurrent();
		RECT rect;
		GetClientRect(widget, &rect);
		oglv->SetSize(rect.right - rect.left, rect.bottom - rect.top);
		//InvalidateRect(widget, &rect, true);
	}
	
	return TRUE;
}

int win_gdiplus_view::MotionNotifyHandler(HWND widget, WPARAM wParam, LPARAM lParam)	// EVENT_HANDLER
{
//printf("win_gdiplus_view::MotionNotifyHandler\n");
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS
	//int x = GET_X_LPARAM(lParam); 
	//int y = GET_Y_LPARAM(lParam); 
	int x = LOWORD(lParam); // horizontal position of pointer 
	int y = HIWORD(lParam); // vertical position of pointer 		}
	if (x > 32768) x -= 65536;
	if (y > 32768) y -= 65536;

	static COLORREF buff_color = 0;

//	int x; int y; GdkModifierType mbstate;
//	if (event->is_hint) gdk_window_get_pointer(event->window, & x, & y, & mbstate);
//	else { x = (int) event->x; y = (int) event->y; mbstate = (GdkModifierType) event->state; }
	
	// here it is good to check if we have lost a "mouse button up" message.
	// it can happen if a user moves the mouse outside to the graphics window,
	// and then changes the mousebutton state.
	
	// if we think that a mouse button should be down, but GTK+ says it's not,
	// then immediately send a "mouse button down" message...
	
	bool no_buttons_down = !(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON));
	
	if (no_buttons_down )
	{
		win_gdiplus_view * oglv = GetGDIV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{

			buff_gdiplus_map_view * gmv = dynamic_cast<buff_gdiplus_map_view *>(oglv);
			if (gmv && gmv->selectBuffer1 && gmv->selectBuffer2)
			{
				Color select_color[2];
				gmv->selectBuffer1->GetPixel(x,y, &select_color[0]);
				gmv->selectBuffer2->GetPixel(x,y, &select_color[1]);
				COLORREF color =  RGBA(select_color[0].GetRed(),select_color[0].GetGreen(),select_color[0].GetBlue(),select_color[1].GetBlue());
				BYTE id1 = select_color[1].GetRed();
				BYTE id2 = select_color[1].GetGreen();
						
				//printf("COLORREF color =  %x\n", color);
				//printf("BYTE id1 = %x\n", id1);
				//printf("BYTE id2 = %x\n", id2);

				if (!color || color != buff_color)			
				{
					gmv->GetProject()->DestroyContextWindow();
					gmv->useWellElementInContextMenu = false;
				}	

				if (color)
				{
					//bool test = (name_vector[0] & GLNAME_MODEL_DEPENDENT);
					//if (test)
					//{
					//}
					//else
					//{
						switch (id1)
						{
							case GLNAME_MD_TYPE_WELL_ELEMENT:
								{
									gmv->GetProject()->SelectWellElement(x,y, (const WellElement *) color, widget);
									gmv->useWellElementInContextMenu = true;
								}
								break;
						} // switch
					//} // test
				}	
				buff_color = color;				
			}


			//cout << "motion_event " << button << " " << state << endl;
			//current_tool->ContextMotionEvent((ogl_view *) oglv, x, y);
			/*{
				graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
				if (gv != NULL)
				{
					gv->cam->RenderWindow(gv, camera::ContextMotion, x, y);
				}
			}*/
		}	
	}


	if (no_buttons_down && button != mouse_gdiplus_tool::None)
	{
		button_event_lost_counter_gdi++;
		if (button_event_lost_counter_gdi > 1)
		{
			win_gdiplus_view * oglv = GetGDIV(widget);
			if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
			else
			{
				cout << "WARNING ; a mouse-button-up event was lost!" << endl;
				
				state = mouse_gdiplus_tool::Up;
				
			//	cout << "button_event_U " << button << " " << state << " " << (gdiplus_view *) window << endl;
				current_gdiplus_tool->ButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
				
				button = mouse_gdiplus_tool::None;
			}
		}
	}
	
	// the normal operation starts here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	//if (button != mouse_gdiplus_tool::None)
	{
		win_gdiplus_view * oglv = GetGDIV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
		//	cout << "motion_event " << button << " " << state << endl;
			current_gdiplus_tool->MotionEvent((gdiplus_view *) oglv, x, y);
		}
	}
	
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	
	return TRUE;
}

int win_gdiplus_view::KeyMotionNotifyHandler(HWND widget, WPARAM wParam, LPARAM lParam)	// EVENT_HANDLER
{
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS

	//int x = GET_X_LPARAM(lParam); 
	//int y = GET_Y_LPARAM(lParam); 

	int x = LOWORD(lParam); // horizontal position of pointer 
	int y = HIWORD(lParam); // vertical position of pointer 		}
	if (x > 32768) x -= 65536;
	if (y > 32768) y -= 65536;

//	int x; int y; GdkModifierType mbstate;
//	if (event->is_hint) gdk_window_get_pointer(event->window, & x, & y, & mbstate);
//	else { x = (int) event->x; y = (int) event->y; mbstate = (GdkModifierType) event->state; }
	
	// here it is good to check if we have lost a "mouse button up" message.
	// it can happen if a user moves the mouse outside to the graphics window,
	// and then changes the mousebutton state.
	
	// if we think that a mouse button should be down, but GTK+ says it's not,
	// then immediately send a "mouse button down" message...
	
	bool no_buttons_down = !(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON));
	if (no_buttons_down && button != mouse_gdiplus_tool::None)
	{
		button_event_lost_counter_gdi++;
		if (button_event_lost_counter_gdi > 1)
		{
			win_gdiplus_view * oglv = GetGDIV(widget);
			if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
			else
			{
				cout << "WARNING ; a mouse-button-up event was lost!" << endl;
				
				state = mouse_gdiplus_tool::Up;
				
			//	cout << "button_event_U " << button << " " << state << " " << (gdiplus_view *) window << endl;
				current_gdiplus_tool->ButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
				
				button = mouse_gdiplus_tool::None;
			}
		}
	}
	
	// the normal operation starts here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	if (button != mouse_gdiplus_tool::None)
	{
		win_gdiplus_view * oglv = GetGDIV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
		//	cout << "motion_event " << button << " " << state << endl;
			current_gdiplus_tool->MotionEvent((gdiplus_view *) oglv, x, y);
		}
	}
	
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	
	return TRUE;
}

int win_gdiplus_view::MouseWhellNotifyHandler(HWND widget, WPARAM wParam, LPARAM lParam)	// EVENT_HANDLER
{
#if 0
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS

	int zDelta = (int) wParam; // wheel rotation 
	i32s x = zDelta / 1000000;


	//====== Если одновременно была нажата Ctrl,
	if (wParam & MK_CONTROL)
	{
		//=== Изменяем коэффициенты сдвига изображения
		//m_AngleX += m_dz;
	}
	else
	{
		if (wParam & MK_SHIFT )
		{
			//m_AngleY += m_dz;
		}
		else
		{
			//m_AngleZ += m_dz;
		}
	}

	

	win_gdiplus_view * oglv = win_gdiplus_view::GetGDIV(widget);
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		//***********************************************
		// insertion ftom ButtonEvent
		dummy_object * ref_to_object = gv->cam; 
		bool local_object = true;
		const camera * rdata;
		rdata = gv->cam;
		//***********************************************		
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[2] = 180.0 * (fGL) (x) / (fGL) gv->size[0];
			ref_to_object->OrbitObject(ang, * rdata, 1);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllGraphicsViews();
			}
		}
	}





//	int x; int y; GdkModifierType mbstate;
//	if (event->is_hint) gdk_window_get_pointer(event->window, & x, & y, & mbstate);
//	else { x = (int) event->x; y = (int) event->y; mbstate = (GdkModifierType) event->state; }
	
	// here it is good to check if we have lost a "mouse button up" message.
	// it can happen if a user moves the mouse outside to the graphics window,
	// and then changes the mousebutton state.
	
	// if we think that a mouse button should be down, but GTK+ says it's not,
	// then immediately send a "mouse button down" message...
	
/*	bool no_buttons_down = !(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON));
	if (no_buttons_down && button != mouse_gdiplus_tool::None)
	{
		button_event_lost_counter_gdi++;
		if (button_event_lost_counter_gdi > 1)
		{
			win_gdiplus_view * oglv = GetGDIV(widget);
			if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
			else
			{
				cout << "WARNING ; a mouse-button-up event was lost!" << endl;
				
				state = mouse_gdiplus_tool::Up;
				
			//	cout << "button_event_U " << button << " " << state << " " << (gdiplus_view *) window << endl;
				current_gdiplus_tool->ButtonEvent((gdiplus_view *) oglv, (i32s) x, (i32s) y);
				
				button = mouse_gdiplus_tool::None;
			}
		}
	}*/
	
	// the normal operation starts here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	/*if (button != mouse_gdiplus_tool::None)
	{
		win_gdiplus_view * oglv = GetGDIV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
		//	cout << "motion_event " << button << " " << state << endl;
			current_gdiplus_tool->MotionEvent((gdiplus_view *) oglv, x, y);
		}
	}*/
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
#endif
	return TRUE;
}

int win_gdiplus_view::DetachedDeleteHandler(HWND)
{
	// when we create detached view windows as win_WINDOW_TOPLEVEL, the window will have the "close" button
	// at titlebar. now if the user presses the "close" button, the window-closing sequence will start.
	// we will grab the resulting delete_event here and return TRUE, that will deny the user's request to
	// close the window. the user should use the stardard popup-way of closing the window...
	
	return TRUE;
}

win_gdiplus_view * win_gdiplus_view::GetGDIV(HWND widget)
{
//printf("win_gdiplus_view * win_gdiplus_view::GetGDIV(HWND widget)\n");
//cout << "widget = " << widget << endl;
	vector<win_gdiplus_view *>::iterator it1 = gdi_vector.begin();
	while (it1 != gdi_vector.end())
	{
		vector<win_gdiplus_view *>::iterator it2 = it1++;
//cout << "(* it2)->view_widget " << (* it2)->view_widget << endl;
		if ((* it2)->view_widget == widget) return (* it2);
	}
	
	// return NULL if the search _gdiplus_gdiplus_tool...
	// return NULL if the search _gdiplus_gdiplus_tool...
	// return NULL if the search _gdiplus_gdiplus_tool...
	
	return NULL;
}


/*################################################################################################*/

// eof
