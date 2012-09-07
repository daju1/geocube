// GTK_PLOT_VIEWS.H : write a short description here...

// Copyright (C) 2005 Tommi Hassinen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/

#ifndef WIN_MAP_VIEWS_H
#define WIN_MAP_VIEWS_H

//#include "appconfig.h"

class win_map_view;

#include "win32_views.h"

/*################################################################################################*/

class win_map_view : public win_ogl_view, public map_view
{
	protected:
	
//	static GtkActionEntry entries[];
	static const char * ui_description;
	iGLu * select_buffer;

	private:
	
	win_map_view(win_project *, Object *);
	
	friend class win_class_factory;
	
	public:
	
	~win_map_view(void);
	
	private:
	
	void InitGL(void);	// virtual

	void Update(bool);			// virtual
	void ExposeEvent(void);		// virtual
	
	public:

	void Render(void);		// virtual
	
	static void popup_AttachDetach(HWND, void *);
	static void popup_DeleteView(HWND, void *);

	void CreateMyPopupMenu(HWND hWnd);
};
//class Object;
/*################################################################################################*/
class gdiplus_map_view : public win_gdiplus_view, public map_view
{
	friend LRESULT CALLBACK WndProcGDIplusMapView(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	protected:
	
//	static GtkActionEntry entries[];
	static const char * ui_description;

		

	
	private:
	
	
	public:
	
	gdiplus_map_view(win_project *, Object *);
	friend class win_class_factory;
	~gdiplus_map_view(void);
	
	private:
	
	void Update(bool);			// virtual
	void ExposeEvent(void);		// virtual
	
	public:

	bool SetCurrent(void);		// virtual
	void InitGDI(void);
	
	static void popup_AttachDetach(HWND, void *);
	static void popup_DeleteView(HWND, void *);

	void CreateMyPopupMenu(HWND hWnd);
	bool useWellElementInContextMenu;

};

class buff_gdiplus_map_view : public gdiplus_map_view
{
	Graphics * g;
	
public:	

	Bitmap * selectBuffer1;
	Bitmap * selectBuffer2;

	int buff_gdiplus_map_view::ConfigureHandler(HWND widget);		// EVENT_HANDLER


	void Render(void);		// virtual
	buff_gdiplus_map_view(win_project *, Object *);
	~buff_gdiplus_map_view(void);
};


void FillCircle(Graphics * graphics, fGL xc, fGL yc, fGL r, Color & gdi_color);
void DrawCircle(Graphics * graphics, fGL xc, fGL yc, fGL r, Color & gdi_color);
void HatchFillCircle(Graphics * graphics, fGL xc, fGL yc, fGL r, HatchStyle hs, Color & foreColor, Color & backColor = Color());


#endif	// WIN_MAP_VIEWS_H

// eof
