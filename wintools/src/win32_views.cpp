// WIN32_VIEWS.CPP

// Copyright (C) 1998 Tommi Hassinen, Jarno Huuskonen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/
#include "stdafx.h"
#include "..\resource.h"

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

win_view::win_view(win_project * p1) : view()
{
//printf("win_view::win_view(win_project * p1) : view()\n\n");
	prj = p1;
	
//	label_widget = win_label_new("this_view_has_no_title");
//	popupmenu = NULL;
}

win_view::~win_view(void)
{
}

project * win_view::GetProject(void)
{
	return prj;
}

void win_view::SetTitle(const char * p1)
{
	// if this a "detached" view, we should do the title setting differently than usual "attached" cases.
	// only gtk_graphics_view objects can be "detached". ok, this is a bit ugly solution, but see
	// gtk_graphics_view::popup_ViewsAttachDetach() for more comments...
	
// THIS IS BAD!!!!!!!!!!
// THIS IS BAD!!!!!!!!!!
// THIS IS BAD!!!!!!!!!!
// THIS IS BAD!!!!!!!!!!

/*	gtk_graphics_view * gv = dynamic_cast<gtk_graphics_view *>(this);
	if (gv != NULL && gv->detached != NULL)
	{
		char projfilename[256];
		prj->GetProjectFileName(projfilename, 256, true);
		
		char extended_title[256];
		ostrstream str(extended_title, sizeof(extended_title));
		str << projfilename << " : " << p1 << ends;
		
		gtk_window_set_title(GTK_WINDOW(gv->detached), extended_title);
		return;
	}	*/
	
//	gtk_label_set_text(GTK_LABEL(label_widget), p1);
}

/*################################################################################################*/

vector<win_ogl_view *> win_ogl_view::oglv_vector;
HGLRC * win_ogl_view::m_CurrentOGContext = NULL;

win_ogl_view::win_ogl_view(win_project * p1) : ogl_view(), win_view(p1)
{
//printf("win_ogl_view::win_ogl_view(win_project * p1) : ogl_view(), win_view(p1)\n\n");


	hDigitizeCursor = NULL;
	detached = NULL;//pointer to window?
	
	is_realized = false;
	oglv_vector.push_back(this);

	/*
	HWND hWnd = p1->GetWindow();

	SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG, 0);

	printf("win_ogl_view ");
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

win_ogl_view::~win_ogl_view(void)
{
	vector<win_ogl_view *>::iterator it1;
	it1 = find(oglv_vector.begin(), oglv_vector.end(), this);
	
	if (it1 != oglv_vector.end())
	{
		oglv_vector.erase(it1);
	}
	else
	{
		cout << "WARNING : unknown view_widget at ~win_ogl_view()!!!" << endl;
	}
}

void win_ogl_view::Update(bool directly)
{
//printf("win_ogl_view::Update = %d\n", directly);
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
extern LOGFONT lf_Label;        // logical font structure
extern int UseGLFont( HDC hDC,  IN CONST LOGFONTA * plf_Label);
bool win_ogl_view::InitOG(HWND hWnd)
{
#if 1
//#define nplanes 24
#define nplanes 32
					PIXELFORMATDESCRIPTOR pfd =	// Описатель формата
					{
						sizeof(PIXELFORMATDESCRIPTOR),// Размер структуры
						1,							// Номер версии
						PFD_DRAW_TO_WINDOW |	// Поддержка GDI
						PFD_SUPPORT_OPENGL |	// Поддержка OpenGL
						PFD_DOUBLEBUFFER,		// Двойная буферизация
						PFD_TYPE_RGBA,			// Формат RGBA, не палитра
						nplanes, 					// Количество плоскостей
		 											// в каждом буфере цвета
						nplanes,	0,				// Для компоненты Red
						nplanes,	0,				// Для компоненты Green
						nplanes,	0,				// Для компоненты Blue
						nplanes,	0,				// Для компоненты Alpha
						0,							// Количество плоскостей
													// буфера Accumulation
						0,			 				// То же для компоненты Red
						0,			 				// для компоненты Green
						0,							// для компоненты Blue
						0,							// для компоненты Alpha
						32, 						// Глубина Z-буфера
						0,							// Глубина буфера Stencil
						0,							// Глубина буфера Auxiliary
						0,				 			// Теперь игнорируется
						0,							// Количество плоскостей
						0,							// Теперь игнорируется
						0,							// Цвет прозрачной маски
						0							// Теперь игнорируется
					};

					//====== Добываем дежурный контекст
					m_hdc = ::GetDC(hWnd);

					//====== Просим выбрать ближайший совместимый формат
					int iD = ChoosePixelFormat(m_hdc, &pfd);
					if ( !iD )
					{
						MessageBox(hWnd,"ChoosePixelFormat::Error","On Create",0);
						return 0;
					}

					//GL_RGBA

					//====== Пытаемся установить этот формат
					if ( !SetPixelFormat (m_hdc, iD, &pfd) )
					{
						MessageBox(hWnd,"SetPixelFormat::Error","On Create winsuf",0);
						return 0;
					}

					//====== Пытаемся создать контекст передачи OpenGL
					if ( !(m_hRC = wglCreateContext (m_hdc)))
					{
						const size_t s_len = 4096;
						char MsgBuf[s_len];
						DWORD dw = GetLastError(); 
						sprintf_s(MsgBuf, s_len, " 2 wglCreateContext::Error = %d", dw);
						MessageBox(hWnd, MsgBuf,"On Create",0);
						// сообщение об ошибке
						TCHAR szBuf[s_len]; 
						LPVOID lpMsgBuf;

						FormatMessage(
							FORMAT_MESSAGE_ALLOCATE_BUFFER | 
							FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							dw,
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
							(LPTSTR) &lpMsgBuf,
							0, NULL );

						sprintf_s(szBuf, s_len,
							"wglCreateContext failed with error %d: %s", 
							dw, lpMsgBuf); 
					 
						MessageBox(NULL, szBuf, "Error", MB_OK); 
						LocalFree(lpMsgBuf);


						return 0;
					}

					//====== Пытаемся выбрать его в качестве текущего
					if ( !wglMakeCurrent (m_hdc, m_hRC))
					{
						MessageBox(hWnd,"wglMakeCurrent::Error","On Create",0);
						return 0;
					}
/*
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/

					{

						lf_Label.lfHeight				= 14; // height of font
						lf_Label.lfWidth				= 0;  // average character width
						lf_Label.lfEscapement			= 0;  // angle of escapement
						lf_Label.lfOrientation			= 0;  // base-line orientation angle
						lf_Label.lfWeight				= 100;// font weight 
						lf_Label.lfItalic				= 0;  // italic attribute option
						lf_Label.lfUnderline			= 0;  // underline attribute option
						lf_Label.lfStrikeOut			= 0;  // strikeout attribute option
						lf_Label.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
						lf_Label.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
						lf_Label.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
						lf_Label.lfQuality				= DEFAULT_QUALITY;		// output quality
						lf_Label.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
						strcpy(lf_Label.lfFaceName,		"Times New Roman");				// typeface name

						UseGLFont( m_hdc,  &lf_Label);
					}


					{

						//int pixelFormat = ChoosePixelFormat (hDC, &pfd);
						int pixelFormat = iD;

						PIXELFORMATDESCRIPTOR pfd_new;
						DescribePixelFormat (m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd_new);

						int generic_format = pfd_new.dwFlags & PFD_GENERIC_FORMAT;
						int generic_accelerated = pfd_new.dwFlags & PFD_GENERIC_ACCELERATED;

						if (generic_format && ! generic_accelerated)
						{
							// режим программной эмуляции; всю работу выполняет центральный процессор
							//MessageBox(0,"режим программной эмуляции; всю работу выполняет центральный процессор","",0);
						}
						else if (generic_format && generic_accelerated)
						{	
							// MCD-драйвер; аппаратно реализуется только часть функций ускорения
							//MessageBox(0,"MCD-драйвер; аппаратно реализуется только часть функций ускорения","",0);
						}
						else if (! generic_format && ! generic_accelerated)
						{
							// полноценный ICD-драйвер с функциями ускорения
							//MessageBox(0,"полноценный ICD-драйвер с функциями ускорения","",0);
						}
					}
#else
	PIXELFORMATDESCRIPTOR pfd =	// Описатель формата
	{
		sizeof(PIXELFORMATDESCRIPTOR),// Размер структуры
		1,							// Номер версии
		PFD_DRAW_TO_WINDOW |	// Поддержка GDI
		PFD_SUPPORT_OPENGL |	// Поддержка OpenGL
		PFD_DOUBLEBUFFER,		// Двойная буферизация
		PFD_TYPE_RGBA,			// Формат RGBA, не палитра
		24, 						// Количество плоскостей
		 							// в каждом буфере цвета
		24,	0,						// Для компоненты Red
		24,	0,						// Для компоненты Green
		24,	0,						// Для компоненты Blue
		24,	0,						// Для компоненты Alpha
		0,							// Количество плоскостей
									// буфера Accumulation
		0,			 				// То же для компоненты Red
		0,			 				// для компоненты Green
		0,							// для компоненты Blue
		0,							// для компоненты Alpha
		32, 						// Глубина Z-буфера
		0,							// Глубина буфера Stencil
		0,							// Глубина буфера Auxiliary
		0,				 			// Теперь игнорируется
		0,							// Количество плоскостей
		0,							// Теперь игнорируется
		0,							// Цвет прозрачной маски
		0							// Теперь игнорируется
	};



	//====== Добываем дежурный контекст
	this->m_hdc = ::GetDC(hWnd);
//MessageBox(hWnd,"2","On Create",0);

	//====== Просим выбрать ближайший совместимый формат
	int iD = ChoosePixelFormat(this->m_hdc, &pfd);
	if ( !iD )
	{
		MessageBox(hWnd,"ChoosePixelFormat::Error","On Create",0);
		return 0;
	}

	//GL_RGBA

	//====== Пытаемся установить этот формат
	if ( !SetPixelFormat (this->m_hdc, iD, &pfd) )
	{
		MessageBox(hWnd,"SetPixelFormat::Error","On Create winsuf",0);
		return 0;
	}


	//====== Пытаемся создать контекст передачи OpenGL
	if ( !(this->m_hRC = wglCreateContext (this->m_hdc)))
	{
		MessageBox(hWnd," 1 wglCreateContext::Error","On Create",0);
		return 0;
	}

	//====== Пытаемся выбрать его в качестве текущего
	if ( !wglMakeCurrent (this->m_hdc, this->m_hRC))
	{
		MessageBox(hWnd,"wglMakeCurrent::Error","On Create",0);
		return 0;
	}
	else
		win_ogl_view::m_CurrentOGContext = &this->m_hRC;


	/*//====== Пытаемся выбрать его в качестве текущего
	if ( !wglMakeCurrent (m_hdc, m_hRC))
	{
		MessageBox(hWnd,"wglMakeCurrent::Error","On Create",0);
		return 0;
	}*/




//int pixelFormat = ChoosePixelFormat (hDC, &pfd);
int pixelFormat = iD;

PIXELFORMATDESCRIPTOR pfd_new;
DescribePixelFormat (m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd_new);


int generic_format = pfd_new.dwFlags & PFD_GENERIC_FORMAT;
int generic_accelerated = pfd_new.dwFlags & PFD_GENERIC_ACCELERATED;

if (generic_format && ! generic_accelerated)
{
// режим программной эмуляции; всю работу выполняет центральный процессор
// MessageBox(0,"режим программной эмуляции; всю работу выполняет центральный процессор","",0);
}
else if (generic_format && generic_accelerated)
{
// MCD-драйвер; аппаратно реализуется только часть функций ускорения
// MessageBox(0,"MCD-драйвер; аппаратно реализуется только часть функций ускорения","",0);
}
else if (! generic_format && ! generic_accelerated)
{
// полноценный ICD-драйвер с функциями ускорения
// MessageBox(0,"полноценный ICD-драйвер с функциями ускорения","",0);
}
#endif
}

bool win_ogl_view::SetCurrent(void)
{
//printf("win_ogl_view::SetCurrent(void)\n\n");
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
		if (win_ogl_view::m_CurrentOGContext != &this->m_hRC)
		{
			//====== Пытаемся выбрать его в качестве текущего
			if ( wglMakeCurrent (this->m_hdc, this->m_hRC))
			{
				win_ogl_view::m_CurrentOGContext = &this->m_hRC;
				return true;
			}
			else
			{
				MessageBox(this->detached,"wglMakeCurrent::Error","On Create",0);
				g_print("ERROR : wglMakeCurrent() failed in SetCurrent().\n");
				return false;
			}
		}
		else 
			return true;

		if (false)
		{
			g_print("ERROR : gdk_gl_drawable_make_current() failed in SetCurrent().\n");
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}
BYTE ANDmaskCursor[] = 
{ 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 1 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 2 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 3 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 4 
 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 5 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 6 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 7 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 8 
 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 9 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 10 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 11 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 12 
 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 13 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 14 
    0x00, 0x0F, 0xE0, 0x01,   // line 15 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 16 
 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 17 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 18 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 19 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 20 
 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 21 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 22 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 23 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 24 
 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 25 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 26 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 27 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 28 
 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 29 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 30 
    0xFF, 0xFE, 0xFF, 0xFF,   // line 31 
    0xFF, 0xFF, 0xFF, 0xFF    // line 32 
};
 
// Yin-shaped cursor XOR mask 
 
BYTE XORmaskCursor[] = 
{ 
    0x00, 0x00, 0x00, 0x00,   // line 1 
    0x00, 0x00, 0x00, 0x00,   // line 2 
    0x00, 0x00, 0x00, 0x00,   // line 3 
    0x00, 0x00, 0x00, 0x00,   // line 4 
 
    0x00, 0x00, 0x00, 0x00,   // line 5 
    0x00, 0x00, 0x00, 0x00,   // line 6 
    0x00, 0x00, 0x00, 0x00,   // line 7 
    0x00, 0x00, 0x00, 0x00,   // line 8 
 
    0x00, 0x00, 0x00, 0x00,   // line 9 
    0x00, 0x00, 0x00, 0x00,   // line 10 
    0x00, 0x00, 0x00, 0x00,   // line 11 
    0x00, 0x00, 0x00, 0x00,   // line 12 
 
    0x00, 0x00, 0x00, 0x00,   // line 13 
    0x00, 0x00, 0x00, 0x00,   // line 14 
    0x00, 0x00, 0x00, 0x00,   // line 15 
    0x00, 0x00, 0x00, 0x00,   // line 16 
 
    0x00, 0x00, 0x00, 0x00,   // line 17 
    0x00, 0x00, 0x00, 0x00,   // line 18 
    0x00, 0x00, 0x00, 0x00,   // line 19 
    0x00, 0x00, 0x00, 0x00,   // line 20 
 
    0x00, 0x00, 0x00, 0x00,   // line 21 
    0x00, 0x00, 0x00, 0x00,   // line 22 
    0x00, 0x00, 0x00, 0x00,   // line 23 
    0x00, 0x00, 0x00, 0x00,   // line 24 
 
    0x00, 0x00, 0x00, 0x00,   // line 25 
    0x00, 0x00, 0x00, 0x00,   // line 26 
    0x00, 0x00, 0x00, 0x00,   // line 27 
    0x00, 0x00, 0x00, 0x00,   // line 28 
 
    0x00, 0x00, 0x00, 0x00,   // line 29 
    0x00, 0x00, 0x00, 0x00,   // line 30 
    0x00, 0x00, 0x00, 0x00,   // line 31 
    0x00, 0x00, 0x00, 0x00    // line 32 
};

void win_ogl_view::SetDigitizeCursor(bool to_set)
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


void win_ogl_view::RealizeHandler(HWND widget, void *)
{
	win_ogl_view * oglv = GetOGLV(widget);
	if (!oglv) cout << "Unknown ID in RealizeHandler !!!" << endl;
	else
	{
		oglv->is_realized = true;
		oglv->InitGL();
	}
}

int win_ogl_view::ExposeHandler(HWND widget/*, GdkEventExpose * */)		// EVENT_HANDLER
{
	win_ogl_view * oglv = GetOGLV(widget);
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

int button_event_lost_counter = 0;


int win_ogl_view::ButtonHandler(HWND widget, UINT message, WPARAM wParam, LPARAM lParam)

// EVENT_HANDLER

{
	int x = LOWORD(lParam); // horizontal position of pointer 
	int y = HIWORD(lParam); // vertical position of pointer 		}
	if (x > 32768) x -= 65536;
	if (y > 32768) y -= 65536;
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
	win_ogl_view * oglv = GetOGLV(widget);
	if (!oglv) cout << "Unknown ID in ButtonHandler !!!" << endl;
	else
	{
		mouse_tool::button tmpb; i32u tmps1;
		if( wParam &  MK_LBUTTON)
		{
			tmpb = mouse_tool::Left;
			tmps1 = MK_LBUTTON;
		}
		if( wParam &  MK_RBUTTON)
		{			
			tmpb = mouse_tool::Right;
			tmps1 = MK_RBUTTON;
		}
		if( wParam &  MK_MBUTTON)
		{			
			tmpb = mouse_tool::Middle;
			tmps1 = MK_MBUTTON;
		}
		
		mouse_tool::state tmps2;// = (eb->state & tmps1) ? mouse_tool::Up : mouse_tool::Down;
		switch(message)
		{
		case WM_LBUTTONDOWN:
			tmpb = mouse_tool::Left;
			tmps2 = mouse_tool::Down;
			break;
		case WM_LBUTTONDBLCLK:										
			tmpb = mouse_tool::Left;
			tmps2 = mouse_tool::DblClk;
			break;
		case WM_LBUTTONUP:
			tmpb = mouse_tool::Left;
			tmps2 = mouse_tool::Up;
			break;
		case WM_RBUTTONDOWN:
			tmpb = mouse_tool::Right;
			tmps2 = mouse_tool::Down;
			break;
		case WM_RBUTTONDBLCLK:
			tmpb = mouse_tool::Right;
			tmps2 = mouse_tool::DblClk;
			break;
		case WM_RBUTTONUP:
			tmpb = mouse_tool::Right;
			tmps2 = mouse_tool::Up;
			break;
		case WM_MBUTTONDOWN:
			tmpb = mouse_tool::Middle;
			tmps2 = mouse_tool::Down;
			break;
		case WM_MBUTTONDBLCLK:
			tmpb = mouse_tool::Middle;
			tmps2 = mouse_tool::DblClk;
			break;
		case WM_MBUTTONUP:
			tmpb = mouse_tool::Middle;
			tmps2 = mouse_tool::Up;
			break;
		}
		
		if (tmps2 == mouse_tool::Down)
		{
			if (button == mouse_tool::None)
			{
				if (tmpb == mouse_tool::Right)
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
					win_ogl_view * oglv = GetOGLV(widget);
					oglv->CreateMyPopupMenu(widget);
					//graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
					//if (gv != NULL)
					//{
					//}
				
/*					if (oglv != NULL && oglv->popupmenu != NULL)
					{
						win_menu_popup(win_MENU(oglv->popupmenu), NULL, NULL, NULL, NULL, eb->button, eb->time);
					}
*/					
					return TRUE;
				}
				
				button = tmpb;
				
				shift_down = (wParam & MK_SHIFT) ? true : false;
				ctrl_down = (wParam & MK_CONTROL) ? true : false;
				
				state = mouse_tool::Down;
				
			//	cout << "button_event_D " << button << " " << state << " " << (ogl_view *) window << endl;
				current_tool->ButtonEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
				button_event_lost_counter = 0;	// this is for exceptions, see below...
			}
		}
		else
		{
			if (button == mouse_tool::Left && tmpb != mouse_tool::Left) return TRUE;
			if (button == mouse_tool::Middle && tmpb != mouse_tool::Middle) return TRUE;
			if (button == mouse_tool::Right && tmpb != mouse_tool::Right) return TRUE;
			
			state = mouse_tool::Up;
			
		//	cout << "button_event_U " << button << " " << state << " " << (ogl_view *) window << endl;
			current_tool->ButtonEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
			
			button = mouse_tool::None;
		}
	}
	
	return TRUE;
}

int win_ogl_view::KeyButtonHandler(HWND widget, UINT message, WPARAM wParam, LPARAM lParam)

// EVENT_HANDLER

{	
	static int x = 0; // horizontal position of pointer 
	static int y = 0; // vertical position of pointer 		}
	
	win_ogl_view * oglv = GetOGLV(widget);
	if (!oglv) cout << "Unknown ID in ButtonHandler !!!" << endl;
	else
	{
		key_tool::key_state tmps2;// = (eb->state & tmps1) ? mouse_tool::Up : mouse_tool::Down;
		switch(message)
		{
		case WM_KEYDOWN:
			tmps2 = key_tool::key_state::KeyDown;
	printf("WM_KEYDOWN wParam = %d lParam = 0x%08x previous key state = %d\n", wParam, lParam, int(lParam & 0x40000000));
			break;
		case WM_KEYUP:
			tmps2 = key_tool::key_state::KeyUp;
			break;
		}
		
		key_tool::key tmpk;// i32u tmps1;
		switch (wParam)
		{
		case 97:
		case 49://1
			{
				key_tool::speed = 1;
			}
			break;
		case 98:
		case 50://2
			{
				key_tool::speed = 2;
			}
			break;
		case 99:
		case 51://3
			{
				key_tool::speed = 3;
			}
			break;
		case 100:
		case 52://4
			{
				key_tool::speed = 4;
			}
			break;
		case 101:
		case 53://5
			{
				key_tool::speed = 5;
			}
			break;
		case 102:
		case 54://6
			{
				key_tool::speed = 6;
			}
			break;
		case 103:
		case 55://7
			{
				key_tool::speed = 7;
			}
			break;
		case 104:
		case 56://8
			{
				key_tool::speed = 8;
			}
			break;
		case 105:
		case 57://9
			{
				key_tool::speed = 9;
			}
			break;
		case 96:
		case 48://0
			{
				key_tool::speed = 10;
			}
			break;
		case 90://z
			{
				tmpk = key_tool::key::keyZ;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_zoom;
					key_tool::speed = 25;
				}
				return TRUE;
			}
			break;		
		case 67://c
			{
				tmpk = key_tool::key::keyC;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_clipping;
					key_tool::speed = 25;
				}
				return TRUE;
			}
			break;
		case 84://t
			{
				tmpk = key_tool::key::keyT;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_translate_xy;
					key_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 71://g
			{
				tmpk = key_tool::key::keyG;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_translate_z;
					key_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 79://o
			{
				tmpk = key_tool::key::keyO;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_orbit_xy;
					key_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 76://l
			{
				tmpk = key_tool::key::keyL;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_orbit_z;
					key_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 82://r
			{
				tmpk = key_tool::key::keyR;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_rotate_xy;
					key_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		case 70://f
			{
				tmpk = key_tool::key::keyF;
				if (tmps2 == key_tool::key_state::KeyDown)
				{
					ogl_view::current_key_tool = & ogl_view::key_tool_rotate_z;
					key_tool::speed = 1;
				}
				return TRUE;
			}
			break;
		}

		if (tmps2 == key_tool::key_state::KeyDown)
		{
			ogl_view::key_state = key_tool::key_state::KeyDown;
			
			if (!(lParam & 0x40000000))// previous key state
				current_key_tool->KeyButtonEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
			
			ogl_view::key_state = key_tool::key_state::KeyUnknown;
		}
		switch (wParam)
		{
		case 16:// Shift
			{
				//m_bShiftPressed = true;
				tmpk = key_tool::key::keyShift;
			}
			break;
		case 17:// Ctrl
			{
				//m_bCtrlPressed = true;
				tmpk = key_tool::key::keyCtrl;
			}
			break;
		case 38:// up
			{
				y+=key_tool::speed;
				//m_zTrans += 0.05f;
				tmpk = key_tool::key::keyUp;
			}
			break;
		case 40:// down
			{
				y-=key_tool::speed;
				//m_zTrans -= 0.05f;
				tmpk = key_tool::key::keyDown;
			}
			break;
		case 37:// left
			{
				x+=key_tool::speed;
				tmpk = key_tool::key::keyLeft;
			}
			break;
		case 39:// right
			{
				x-=key_tool::speed;
				tmpk = key_tool::key::keyRight;
			}
			break;
		case 33:// page up
			{
				tmpk = key_tool::key::keyUp;
			}
			break;
		case 34:// page down
			{
				tmpk = key_tool::key::keyDown;
			}
			break;
		}
		
		if (tmps2 == key_tool::key_state::KeyDown)
		{
			ogl_view::key_state = key_tool::key_state::KeyDown;
			
			if (x > 32768) x -= 65536;
			if (y > 32768) y -= 65536;

			current_key_tool->KeyMotionEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
			
			ogl_view::key_state = key_tool::key_state::KeyUnknown;
		}
	}
	
	return TRUE;
}

int win_ogl_view::ConfigureHandler(HWND widget/*, GdkEventConfigure * */)		// EVENT_HANDLER
{
	win_ogl_view * oglv = GetOGLV(widget);
	if (!oglv) cout << "Unknown ID in ConfigureHandler !!!" << endl;
	else
	{
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS
		
		oglv->SetCurrent();
		RECT rect;
		GetClientRect(widget, &rect);
		oglv->SetSize(rect.right - rect.left, rect.bottom - rect.top);
		
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	}
	
	return TRUE;
}

int win_ogl_view::MotionNotifyHandler(HWND widget, WPARAM wParam, LPARAM lParam)	// EVENT_HANDLER
{
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS

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

	if (no_buttons_down )
	{
		win_ogl_view * oglv = GetOGLV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
			//cout << "motion_event " << button << " " << state << endl;
			//current_tool->ContextMotionEvent((ogl_view *) oglv, x, y);
			{
				graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
				if (gv != NULL)
				{
					gv->cam->RenderWindow(gv, camera::ContextMotion, x, y);
				}
			}
		}	
	}



	if (no_buttons_down && button != mouse_tool::None)
	{
		button_event_lost_counter++;
		if (button_event_lost_counter > 1)
		{
			win_ogl_view * oglv = GetOGLV(widget);
			if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
			else
			{
				cout << "WARNING ; a mouse-button-up event was lost!" << endl;
				
				state = mouse_tool::Up;
				
			//	cout << "button_event_U " << button << " " << state << " " << (ogl_view *) window << endl;
				current_tool->ButtonEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
				
				button = mouse_tool::None;
			}
		}
	}
	
	// the normal operation starts here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	if (button != mouse_tool::None)
	{
		win_ogl_view * oglv = GetOGLV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
		//	cout << "motion_event " << button << " " << state << endl;
			current_tool->MotionEvent((ogl_view *) oglv, x, y);
		}
	}



#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	
	return TRUE;
}

int win_ogl_view::KeyMotionNotifyHandler(HWND widget, WPARAM wParam, LPARAM lParam)	// EVENT_HANDLER
{
#ifdef ENABLE_THREADS
//gdk_threads_enter();
#endif	// ENABLE_THREADS

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
	if (no_buttons_down && button != mouse_tool::None)
	{
		button_event_lost_counter++;
		if (button_event_lost_counter > 1)
		{
			win_ogl_view * oglv = GetOGLV(widget);
			if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
			else
			{
				cout << "WARNING ; a mouse-button-up event was lost!" << endl;
				
				state = mouse_tool::Up;
				
			//	cout << "button_event_U " << button << " " << state << " " << (ogl_view *) window << endl;
				current_tool->ButtonEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
				
				button = mouse_tool::None;
			}
		}
	}
	
	// the normal operation starts here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	if (button != mouse_tool::None)
	{
		win_ogl_view * oglv = GetOGLV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
		//	cout << "motion_event " << button << " " << state << endl;
			current_tool->MotionEvent((ogl_view *) oglv, x, y);
		}
	}
	
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	
	return TRUE;
}

int win_ogl_view::MouseWhellNotifyHandler(HWND widget, WPARAM wParam, LPARAM lParam)	// EVENT_HANDLER
{
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

	

	win_ogl_view * oglv = win_ogl_view::GetOGLV(widget);
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
	if (no_buttons_down && button != mouse_tool::None)
	{
		button_event_lost_counter++;
		if (button_event_lost_counter > 1)
		{
			win_ogl_view * oglv = GetOGLV(widget);
			if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
			else
			{
				cout << "WARNING ; a mouse-button-up event was lost!" << endl;
				
				state = mouse_tool::Up;
				
			//	cout << "button_event_U " << button << " " << state << " " << (ogl_view *) window << endl;
				current_tool->ButtonEvent((ogl_view *) oglv, (i32s) x, (i32s) y);
				
				button = mouse_tool::None;
			}
		}
	}*/
	
	// the normal operation starts here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	/*if (button != mouse_tool::None)
	{
		win_ogl_view * oglv = GetOGLV(widget);
		if (!oglv) cout << "Unknown ID in MotionNotifyHandler !!!" << endl;
		else
		{
		//	cout << "motion_event " << button << " " << state << endl;
			current_tool->MotionEvent((ogl_view *) oglv, x, y);
		}
	}*/
#ifdef ENABLE_THREADS
//gdk_threads_leave();
#endif	// ENABLE_THREADS
	
	return TRUE;
}

int win_ogl_view::DetachedDeleteHandler(HWND)
{
	// when we create detached view windows as win_WINDOW_TOPLEVEL, the window will have the "close" button
	// at titlebar. now if the user presses the "close" button, the window-closing sequence will start.
	// we will grab the resulting delete_event here and return TRUE, that will deny the user's request to
	// close the window. the user should use the stardard popup-way of closing the window...
	
	return TRUE;
}

win_ogl_view * win_ogl_view::GetOGLV(HWND widget)
{
//printf("win_ogl_view * win_ogl_view::GetOGLV(HWND widget)\n");
//cout << "widget = " << widget << endl;
	vector<win_ogl_view *>::iterator it1 = oglv_vector.begin();
	while (it1 != oglv_vector.end())
	{
		vector<win_ogl_view *>::iterator it2 = it1++;
//cout << "(* it2)->view_widget " << (* it2)->view_widget << endl;
		if ((* it2)->view_widget == widget) return (* it2);
	}
	
	// return NULL if the search failed...
	// return NULL if the search failed...
	// return NULL if the search failed...
	
	return NULL;
}
/*################################################################################################*/
/*################################################################################################*/

win_class_factory * win_class_factory::instance = NULL;
singleton_cleaner<win_class_factory> win_class_factory_cleaner(win_class_factory::GetInstance());

win_class_factory::win_class_factory(void) : graphics_class_factory()
{
}

win_class_factory::~win_class_factory(void)
{
}

win_class_factory * win_class_factory::GetInstance(void)
{
	if (instance != NULL) return instance;
	else return (instance = new win_class_factory());
}

project_view * win_class_factory::ProduceProjectView(project * prj1)
{
	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	
	win_project_view * pv = new win_project_view(prj2);
//	win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), pv->view_widget, pv->label_widget);
//	win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page. // currently has no effect...
	
//	win_widget_show(win_WIDGET(prj2->notebook_widget));
	return pv;
}
graphics_view * win_class_factory::ProduceGraphicsView(project * prj1, camera * cam, bool detach)
{
//printf("graphics_view * win_class_factory::ProduceGraphicsView(project * prj1, camera * cam, bool detach)\n\n");

	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	win_graphics_view * wgv = new win_graphics_view(prj2, cam);
	win_ogl_view * woglv = dynamic_cast<win_ogl_view *>(wgv);


	if (detach)
	{
		woglv->view_widget = CreateWindow( lpszWinSurf,
			lpszSurfTitle,
			WS_OVERLAPPED,
			0,0,
			400,400,

			NULL,
			NULL,
			hInst,
			(void *)woglv
			);
//		gv->detached = win_window_new(win_WINDOW_TOPLEVEL);
		woglv->detached = woglv->view_widget;
//		win_window_set_default_size(win_WINDOW(gv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(gv->detached), gv->view_widget);
//		win_signal_connect(win_OBJECT(gv->detached), "delete_event", win_SIGNAL_FUNC(win_graphics_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(gv->detached);



	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), gv->view_widget, gv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
		woglv->view_widget = CreateWindow( lpszWinSurf,
			lpszSurfTitle,
			WS_CHILD | WS_BORDER,
			0,0,
			100,100,

			prj2->GetWidget(),
			NULL,
			hInst,
			(void *)woglv
			);
	}
	SendMessage(woglv->view_widget, WM_COMMAND, ID_FILE_INITOG2, 0);
	SendMessage(prj2->paned_widget, WM_USER+1, 0, (LPARAM)&woglv->view_widget);

	prj2->hSurfWnd = woglv->view_widget;
	return wgv;
}

map_view * win_class_factory::ProduceGDIMapView(project * prj1, Object * ob, bool detach)
{
	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	buff_gdiplus_map_view * p1dv = new buff_gdiplus_map_view(prj2, ob);
	
	if (detach)
	{
//		p1dv->detached = win_window_new(win_WINDOW_TOPLEVEL);
//		win_window_set_default_size(win_WINDOW(p1dv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(p1dv->detached), p1dv->view_widget);
//		win_signal_connect(win_OBJECT(p1dv->detached), "delete_event", win_SIGNAL_FUNC(win_plot1d_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(p1dv->detached);
	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), p1dv->view_widget, p1dv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
	}
	
	return p1dv;
}

map_view * win_class_factory::ProduceMapView(project * prj1, Object * ob, bool detach)
{
	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	win_map_view * p1dv = new win_map_view(prj2, ob);
	
	if (detach)
	{
//		p1dv->detached = win_window_new(win_WINDOW_TOPLEVEL);
//		win_window_set_default_size(win_WINDOW(p1dv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(p1dv->detached), p1dv->view_widget);
//		win_signal_connect(win_OBJECT(p1dv->detached), "delete_event", win_SIGNAL_FUNC(win_plot1d_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(p1dv->detached);
	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), p1dv->view_widget, p1dv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
	}
	
	return p1dv;
}

plot1d_view * win_class_factory::ProducePlot1DView(project * prj1, i32s ud1, const char * tit, const char * s1, const char * sv, bool detach)
{
	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	win_plot1d_view * p1dv = new win_plot1d_view(prj2, ud1, tit, s1, sv);
	
	if (detach)
	{
//		p1dv->detached = win_window_new(win_WINDOW_TOPLEVEL);
//		win_window_set_default_size(win_WINDOW(p1dv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(p1dv->detached), p1dv->view_widget);
//		win_signal_connect(win_OBJECT(p1dv->detached), "delete_event", win_SIGNAL_FUNC(win_plot1d_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(p1dv->detached);
	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), p1dv->view_widget, p1dv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
	}
	
	return p1dv;
}

plot2d_view * win_class_factory::ProducePlot2DView(project * prj1, i32s ud2, const char * s1, const char * s2, const char * sv, bool detach)
{
	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	win_plot2d_view * p2dv = new win_plot2d_view(prj2, ud2, s1, s2, sv);
	
	if (detach)
	{
//		p2dv->detached = win_window_new(win_WINDOW_TOPLEVEL);
//		win_window_set_default_size(win_WINDOW(p2dv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(p2dv->detached), p2dv->view_widget);
//		win_signal_connect(win_OBJECT(p2dv->detached), "delete_event", win_SIGNAL_FUNC(win_plot2d_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(p2dv->detached);
	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), p2dv->view_widget, p2dv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
	}
	
	return p2dv;
}

rcp_view * win_class_factory::ProduceRCPView(project * prj1, i32s ud1, const char * tit, const char * s1, const char * sv, bool detach)
{
	win_project * prj2 = dynamic_cast<win_project *>(prj1);
	win_rcp_view * rcpv = new win_rcp_view(prj2, ud1, tit, s1, sv);
	
	if (detach)
	{
//		rcpv->detached = win_window_new(win_WINDOW_TOPLEVEL);
//		win_window_set_default_size(win_WINDOW(rcpv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(rcpv->detached), rcpv->view_widget);
//		win_signal_connect(win_OBJECT(rcpv->detached), "delete_event", win_SIGNAL_FUNC(win_rcp_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(rcpv->detached);
	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), rcpv->view_widget, rcpv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
	}
	
	return rcpv;
}

eld_view * win_class_factory::ProduceELDView(project * mdl, bool detach)
{
	win_project * prj2 = dynamic_cast<win_project *>(mdl);
	win_eld_view * eldv = new win_eld_view(prj2);
	
	if (detach)
	{
//		eldv->detached = win_window_new(win_WINDOW_TOPLEVEL);
//		win_window_set_default_size(win_WINDOW(eldv->detached), 400, 400);
		
//		win_container_add(win_CONTAINER(eldv->detached), eldv->view_widget);
//		win_signal_connect(win_OBJECT(eldv->detached), "delete_event", win_SIGNAL_FUNC(win_rcp_view::DetachedDeleteHandler), NULL);
		
//		win_widget_show(eldv->detached);
	}
	else
	{
//		win_notebook_append_page(win_NOTEBOOK(prj2->notebook_widget), eldv->view_widget, eldv->label_widget);
//		win_notebook_set_page(win_NOTEBOOK(prj2->notebook_widget), -1);		// activate the last page.
	}
	
//	win_widget_show(win_WIDGET(prj2->notebook_widget));
	
	return eldv;
}
/*################################################################################################*/

// eof
