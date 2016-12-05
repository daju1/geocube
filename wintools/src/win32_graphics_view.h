// GTK_GRAPHICS_VIEW.H : write a short description here...

// Copyright (C) 2005 Tommi Hassinen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/

#ifndef GTK_GRAPHICS_VIEW_H
#define GTK_GRAPHICS_VIEW_H

//#include "appconfig.h"

class win_graphics_view;

#include "win32_views.h"

/*################################################################################################*/

/// A GTK-version of "##graphics_view".

class win_graphics_view : public win_ogl_view, public graphics_view
{
	protected:
	
//	static GtkActionEntry entries[];
	static const char * ui_description;
	
//	GtkWidget * my_stereo_dialog;
	
	friend class win_ogl_view;
	friend class win_class_factory;		// no longer needed???
	
	friend class project;	// current implementation of gtk_project::~gtk_project() needs this???
	friend class win_project;	// current implementation of gtk_project::~gtk_project() needs this???
	friend class win_view;		// current implementation of gtk_view::SetTitle() needs this...
	
	friend class win_project_view;
	
	private:
	
	win_graphics_view(win_project *, camera *);
	
	public:
	
	~win_graphics_view(void);
	void ExposeEvent(void);		// virtual
	
	private:
	
	static win_graphics_view * GetGV(HWND);
	
	
	public:
	
	// the popup-menu callbacks related to graphics_view are here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	static void popup_ProjOrthographic(HWND, void*);
	static void popup_ProjPerspective(HWND, void*);
#if 0
	static void popup_ProjSterRedBlue(HWND, void*);
	static void popup_ProjSterRelaxed(HWND, void*);
	
	static void create_stereo_adj(gpointer, float);			// stereo adjustment box...
	static void callback_distance(GtkAdjustment *, gpointer);	// stereo adjustment box...
	static void callback_angle(GtkAdjustment *, gpointer);		// stereo adjustment box...
	static void callback_destroy(HWND, void*);		// stereo adjustment box...
	static void scale_set_default_values(GtkScale *);		// stereo adjustment box...
#endif
	
	static void popup_RenderQuickUpdate(HWND, void*);
	
//	static void popup_ViewsAttachDetach(HWND, void*);
	static void popup_ViewsNewCam(HWND, void*);
	static void popup_ViewsNewView(HWND, void*);
//	static void popup_ViewsDeleteView(HWND, void*);
	
//	static void popup_ViewsPushCRDSet(HWND, void*);	// ???
//	static void popup_ViewsSuperimpose(HWND, void*);
	
	static void popup_LightsNewLight(HWND, void*);
	static void popup_LightsNewLightLocDir(HWND widget, void * data);
	static void popup_LightsNewLightLocSpot(HWND widget, void * data);
	static void popup_LightsNewLightGlobDir(HWND widget, void * data);
	static void popup_LightsNewLightGlobSpot(HWND widget, void * data);
	static bool popup_LightsSwitchLoc(HWND, void*);
	static bool popup_LightsSwitchGlob(HWND, void*);

	static bool popup_LightsSwitchMovingLoc(HWND, void*);
	static bool popup_LightsSwitchMovingGlob(HWND, void*);

	static bool popup_LightsSwitchFixingLocGlob(HWND, void*);

};

/*################################################################################################*/

#endif	// GTK_GRAPHICS_VIEW_H

// eof
