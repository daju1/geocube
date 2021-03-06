// WIN32_PROJECT.CPP

// Copyright (C) 1998 Tommi Hassinen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/
#include "stdafx.h"
//#include <windows.h>
#include "win32_project.h"	// config.h is here -> we get ENABLE-macros here...

#include "project.h"
#include "appdefine.h"
/*
#include "../libghemical/src/geomopt.h"
#include "../libghemical/src/moldyn.h"

#include "../libghemical/src/eng1_qm.h"
#include "../libghemical/src/eng1_mm.h"
#include "../libghemical/src/eng1_sf.h"
*/
#include "color.h"

#include "plane.h"
#include "surface.h"
//#include "ribbon.h"
#include "win32_app.h"
#include "..\..\tools\src\filedlg.h"
#include "win32_dialog.h"
#include "winsurf.h"

//#include "glade/trajview_dialog.h"

/*
#include "file_import_dialog.h"
#include "file_export_dialog.h"

#include "geomopt_dialog.h"
#include "moldyn_dialog.h"

#include "setup_dialog.h"
#include "progress_dialog.h"
*/
#include "win32_graphics_view.h"


//#include <sys/stat.h>	// for stat
//#include <dirent.h>	// for scandir

//#include <glade/glade.h>

#include <strstream>
using namespace std;

/*################################################################################################*/

win_project::win_project() : project()
{
//printf("win_project::win_project(win_class_factory & p2) : project(p2)\n\n");
	// only the control_factory() function from main.cpp should call this?!?!?!
	// only the control_factory() function from main.cpp should call this?!?!?!
	// only the control_factory() function from main.cpp should call this?!?!?!
	
//	importpdb_mdata = NULL;		// temporary?!?!?!

	this->app = NULL;
	
/*	char buffer[1024];
	GetFullProjectFileName(buffer, 1024);



	
	// the viewing widget is a vertically paned widget; it contains the notebook and the text log.
	// paned_widget = gtk_vpaned_new();
	WNDCLASSEX wc;
	if(!BeginWinSurf(wc))
			return;
	paned_widget = CreateWinSurfWnd((void *)this);
	
	// always add a project view and a graphics view by default.
	// add the project view first so that the graphics view remains on top...
	
	CreateProjectView();
	AddGraphicsView(NULL, false); //-> removed to WinSurfParentProc
	*/
	PrintToLog("A new project created.\n");
	
#ifdef ENABLE_BONOBO
	control = NULL;
#endif	// ENABLE_BONOBO
	
#ifdef ENABLE_THREADS
	pd = NULL;
#endif	// ENABLE_THREADS
	
/*	GtkMenuItem * mi = GTK_MENU_ITEM(build_submenu[1].widget);
	MakeLibraryWidgets(mi, "library/", 1);	*/
}

win_project::win_project(win_class_factory & p2) : project(p2)
{
//printf("win_project::win_project(win_class_factory & p2) : project(p2)\n\n");
	// only the control_factory() function from main.cpp should call this?!?!?!
	// only the control_factory() function from main.cpp should call this?!?!?!
	// only the control_factory() function from main.cpp should call this?!?!?!
	
//	importpdb_mdata = NULL;		// temporary?!?!?!

	this->app = NULL;
	
	char buffer[1024];
	GetFullProjectFileName(buffer, 1024);



	
	// the viewing widget is a vertically paned widget; it contains the notebook and the text log.
	// paned_widget = gtk_vpaned_new();
	WNDCLASSEX wc;
	if(!BeginWinSurf(wc))
			return;
	paned_widget = CreateWinSurfWnd((void *)this);
	
#if 0
	notebook_widget = gtk_notebook_new();
	
	txt_widget = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(txt_widget), false);
	
	txt_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt_widget));
	GtkTextIter txt_iter; gtk_text_buffer_get_end_iter(txt_buffer, & txt_iter);
	end_mark = gtk_text_buffer_create_mark(txt_buffer, NULL, & txt_iter, FALSE);	// right_gravity!
	
	scroll_widget = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scroll_widget), GTK_WIDGET(txt_widget));
	
	gtk_widget_show(txt_widget);
	
	gtk_paned_add1(GTK_PANED(paned_widget), GTK_WIDGET(notebook_widget));
	gtk_paned_add2(GTK_PANED(paned_widget), GTK_WIDGET(scroll_widget));

	gtk_widget_show(notebook_widget);
	gtk_widget_show(scroll_widget);
	
	gtk_widget_show(paned_widget);
#endif	
	// always add a project view and a graphics view by default.
	// add the project view first so that the graphics view remains on top...
	
	CreateProjectView();
	AddGraphicsView(NULL, false); //-> removed to WinSurfParentProc
	
	PrintToLog("A new project created.\n");
	
#ifdef ENABLE_BONOBO
	control = NULL;
#endif	// ENABLE_BONOBO
	
#ifdef ENABLE_THREADS
	pd = NULL;
#endif	// ENABLE_THREADS
	
/*	GtkMenuItem * mi = GTK_MENU_ITEM(build_submenu[1].widget);
	MakeLibraryWidgets(mi, "library/", 1);	*/
}

win_project::~win_project(void)
{
	// check the graphics_view_vector for any "detached" views, and call gtk_widget_destroy for them.
	// the "attached" views, the ones that are linked to the GtkNotebook, will be destroyed with the notebook.
	// ok, this is a bit ugly solution, but see gtk_graphics_view::popup_ViewsAttachDetach() for more comments...
	
// THIS IS BAD!!!!!!!!!!!!!!!!!!
// THIS IS BAD!!!!!!!!!!!!!!!!!!
// THIS IS BAD!!!!!!!!!!!!!!!!!!

	for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
	{
		win_graphics_view * gv = dynamic_cast<win_graphics_view *>(graphics_view_vector[n1]);
//		if (gv != NULL && gv->detached != NULL) gtk_widget_destroy(GTK_WIDGET(gv->detached));
	}

#ifdef ENABLE_THREADS
	if (pd != NULL) cout << "MEM-LEAK pd" << endl;
#endif	// ENABLE_THREADS

}

#ifdef ENABLE_BONOBO

BonoboControl * gtk_project::GetControl(void)
{
	if (!control) control = bonobo_control_new(paned_widget);
	return control;
}

#endif	// ENABLE_BONOBO
/*
HWND win_project::GetWindow(void)
{
	return paned_widget;
}
*/
void win_project::ThreadLock(void)
{
#ifdef ENABLE_THREADS
	gdk_threads_enter();
#endif	// ENABLE_THREADS
}

void win_project::ThreadUnlock(void)
{
#ifdef ENABLE_THREADS
	gdk_threads_leave();
#endif	// ENABLE_THREADS
}

bool win_project::SetProgress(double progress, double * graphdata)
{
#ifdef ENABLE_THREADS
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pd->progressbar_job), progress);
	
	if (graphdata != NULL)
	{
		int f = (pd->g_fill % pd->g_sz);
		for (int i = 0;i < pd->g_n;i++)
		{
			pd->g_data[i * pd->g_sz + f] = graphdata[i];
		}
		
		pd->g_fill++;
		
		gtk_widget_queue_draw_area(pd->drawingarea_job, 0, 0, pd->da_w, pd->da_h);
	}
	
	return pd->cancel;
#else	// ENABLE_THREADS
	return false;
#endif	// ENABLE_THREADS
}

#ifdef ENABLE_THREADS

void win_project::CreateProgressDialog(const char * title, bool show_pbar, int graphs_n, int graphs_s)
{
	pd = new progress_dialog(title, show_pbar, graphs_n, graphs_s);
}

void win_project::DestroyProgressDialog(void)
{
	gtk_widget_destroy(pd->dialog);
	delete pd; pd = NULL;
}

#endif	// ENABLE_THREADS

// Print the message (no problems).
void win_project::Message(const char * msg)
{
	MessageBox(0,msg, "win_project::Message", 0);
/*
	GtkWidget * message_dialog = gtk_message_dialog_new(NULL,
	GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", msg);
	
	gtk_dialog_run(GTK_DIALOG(message_dialog));
	gtk_widget_destroy(message_dialog);*/
}

// Print the message (lower severity).
void win_project::WarningMessage(const char * msg)
{
	MessageBox(0,msg, "win_project::WarningMessage", 0);
/*	GtkWidget * message_dialog = gtk_message_dialog_new(NULL,
	GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, "%s", msg);
	
	gtk_dialog_run(GTK_DIALOG(message_dialog));
	gtk_widget_destroy(message_dialog);*/
}

// Print the message (higher severity).
void win_project::ErrorMessage(const char * msg)
{
	MessageBox(0,msg, "win_project::ErrorMessage", 0);
/*	GtkWidget * message_dialog = gtk_message_dialog_new(NULL,
	GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", msg);
	
	gtk_dialog_run(GTK_DIALOG(message_dialog));
	gtk_widget_destroy(message_dialog);*/
}

// Print the message and wait for a yes/no response.
bool win_project::Question(const char * msg)
{
	return 
		MessageBox(0, msg, "win_project::Question", 
		MB_OKCANCEL | MB_ICONQUESTION) == IDOK;
/*	GtkWidget * question_dialog = gtk_message_dialog_new(NULL,
	GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "%s", msg);
	
	gint response = gtk_dialog_run(GTK_DIALOG(question_dialog));
	gtk_widget_destroy(question_dialog);
	
	switch (response)
	{
		case GTK_RESPONSE_YES:
		return true;
		
		default:
		return false;
	}*/
}

void win_project::PrintToLog(const char * message)
{
	printf (" PrintToLog: %s", message);
/*	GtkTextIter txt_iter;
	gtk_text_buffer_get_iter_at_mark(txt_buffer, & txt_iter, end_mark);
	
	gtk_text_buffer_insert(txt_buffer, & txt_iter, message, -1);
	
	gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(txt_widget), end_mark);*/
}

void win_project::UpdateAllWindowTitles()
{
	// mdi_child_name and view titles are somewhat different issues now; check this!!!
	// we should change mdi_child_name when the project name changes, but this function is for setting the view titles.
	
	char buffer[1024];
	GetProjectFileName(buffer, 1024, true);
	
	//gnome_mdi_child_set_name(GNOME_MDI_CHILD(child), buffer);
	project::UpdateAllWindowTitles();
}
#if 0

void gtk_project::MakeLibraryWidgets(GtkMenuItem * menu, const char * directory_path, int recursion)
{
  struct stat stat_buf;

  if ( stat(directory_path, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode) )
    {
      struct dirent *namelist;
      DIR *dirList;
      GtkWidget *library_item;

       if (( dirList = opendir(directory_path) ))
	 {
//	   char *filename = new char[1024];		// OLD
	   while (( namelist = readdir(dirList) ))
	     {
	       char *filename = new char[1024];		// a new string for each item???
	       
	       strncpy(filename, directory_path, 512);
	       strncat(filename, namelist->d_name, 511);
	       
	       if ( namelist->d_name[0] != '.' &&
		    stat(filename, &stat_buf) == 0 &&
		    strstr(namelist->d_name, ".gpr") != NULL)
		 {
		   library_item = gtk_menu_item_new_with_label(namelist->d_name);
		   
		   // we pass the string "filename" here as user data.
		   // "filename" must be unique for each item, and it must stay in memory.
		   
		   gtk_signal_connect(GTK_OBJECT(library_item), "activate",
				      GTK_SIGNAL_FUNC(popup_Library),
				      filename);
		   
		   gtk_object_set_user_data(GTK_OBJECT(library_item), 
					    (project *) this);

		   gtk_widget_show(library_item);

		   gtk_menu_append(GTK_MENU(menu->submenu),
				   library_item);
		 }
	       else if ( namelist->d_name[0] != '.' &&
			 stat(filename, &stat_buf) == 0 &&
			 S_ISDIR(stat_buf.st_mode) &&
			 recursion != 0)
		 {
		   library_item = gtk_menu_item_new_with_label(namelist->d_name);
		   gtk_menu_item_set_submenu(GTK_MENU_ITEM(library_item),
					     gtk_menu_new());

		   gtk_widget_show(library_item);
		   
		   gtk_menu_append(GTK_MENU(menu->submenu),
				   library_item);
		   
		   strcat(filename, "/");
		   MakeLibraryWidgets(GTK_MENU_ITEM(library_item), filename, recursion-1);
		 }
	// this would be the correct place to delete the string, if it were temporary.
	// however, we must retain the strings in memory because we will use them later, so this will create a (small) memory leak.
	// we should either store the strings to a static block of memory, or someway arrange the memory release when program stops.
//	   delete [] filename;		// can't do this, or we might use freed (and possibly overwritten) memory later...
	     }
//	   delete [] filename;		// OLD
	   closedir(dirList);
	 }

     }
}
#endif
#if 0
void win_project::GeomOptGetParam(geomopt_param & param)
{
	MessageBox(0,"new geomopt_dialog(& param)","",0);
//	new geomopt_dialog(& param);		// the object will call delete itself...
param.confirm = true;	
	// the above dialog is a modal one; we will return from the function only after the dialog is closed.
//	cout << "now returning from gtk_project::GeomOptGetParam()." << endl;
}
#include "./glade/moldyn_dialog.h"

void win_project::MolDynGetParam(moldyn_param & param)
{
	new moldyn_dialog(& param);		// the object will call delete itself...
	
	// the above dialog is a modal one; we will return from the function only after the dialog is closed.

}
#endif
// the popup-menu callbacks are here...
// the popup-menu callbacks are here...
// the popup-menu callbacks are here...

void win_project::popup_FileOpen(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
//	if (prj) new file_open_dialog(prj);	// will call delete itself...
	char filename[512];
	if (OpenFileDlg(widget, "Ghemical Project File (*.gpr)\0*.gpr\0All files \0*.*\0", filename) == S_OK)
	{			
		if (prj == NULL)
		{
			// set a the new project object ; this is only for a stand-alone app ; FIXME bonobo.
			// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			
//			gtk_container_remove(GTK_CONTAINER(gtk_app::main_vbox), gtk_app::prj->GetWidget());
			
			delete win_app::prj;
			win_app::prj = NULL;
			
			win_app::prj = new win_project(* win_class_factory::GetInstance());
//			GtkWidget * widget = prj->GetWidget();
			
//			gtk_container_add(GTK_CONTAINER(gtk_app::main_vbox), widget);
		}
#if 0
		bool open = prj->IsEmpty();	// open, not insert
		
		ifstream ifile;
		ifile.open(filename, ios::in);
		ReadGPR(* prj, ifile, !open);
		ifile.close();
		
		if (open) 	// we're "switching" to this file
		{
			prj->ParseProjectFileNameAndPath(filename);
			
			char buffer[256];
			prj->GetProjectFileName(buffer, 256, true);
			
		// the file name change here is not yet properly working.
		// the project notebook widget should be stored (if not already) in gtk_project and
		// a call of UpdateAllWindowTitles() should change the labels.
			
			prj->UpdateAllWindowTitles();
		}
		else		// we append this file to the current project
		{
			if (prj->selected_object != NULL)		// if an object was selected, remove
			{						// that selection and leave the newly added
				prj->selected_object = NULL;		// atoms as selection; now the mouse tools
			}						// also affect the newly added atoms!
		}
#endif
		
	prj->UpdateAllGraphicsViews();
	}
//	return true;
}
#if 0
void win_project::popup_FileClose(HWND widget, void * data)
{
	// win_graphics_view * gv = GetGV(widget);
	
	// apparently, it is not necessary to call gnome_mdi_remove_view() for the view here...
	// apparently, it is not necessary to call gnome_mdi_remove_view() for the view here...
	// apparently, it is not necessary to call gnome_mdi_remove_view() for the view here...
	
	//gnome_mdi_remove_child(gnome_mdi_app::mdi, GNOME_MDI_CHILD(gv->prj->child), FALSE);
}

void win_project::popup_FileImport(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj) new file_import_dialog(prj);		// will call delete itself...
}

void win_project::popup_FileExport(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj) new file_export_dialog(prj);		// will call delete itself...
}

void win_project::popup_FileExportGraphic(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj) new file_save_graphics_dialog(prj);	// will call delete itself...
}
#endif
void win_project::popup_FileSaveAs(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	//if (prj) new file_save_dialog(prj);		// will call delete itself...
	TCHAR filter[] =     TEXT("Ghemical Project File (*.gpr)\0*.gpr\0")
						 TEXT("All Files (*.*)\0*.*\0");
	TCHAR filename[256];

	sprintf(filename, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, filename, filter, nFilterIndex) == S_OK)
	{
		if (prj == NULL)
		{
			prj->ErrorMessage("BUG: file_save_dialog::OkEvent() failed.");
			exit(EXIT_FAILURE);
		}
		
		// should check to see if file already exists...
		
		prj->ParseProjectFileNameAndPath(filename);
		
		char buffer[256];
		prj->GetProjectFileName(buffer, 256, true);
		
		//gnome_mdi_child_set_name(GNOME_MDI_CHILD(prj->child), buffer);
		prj->UpdateAllWindowTitles();
		
		char tmp_filename[256];
		prj->GetFullProjectFileName(tmp_filename, 256);
#if 0
		ofstream ofile;
		ofile.open(tmp_filename, ios::out);
		WriteGPR_v100(* prj, ofile);
		ofile.close();
#endif
//		return true;
	}
}
#if 0
void win_project::popup_FileExtra1(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj) new importpdb_dialog(prj);		// will call delete itself???
}

void win_project::popup_FileExtra2(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (prj->importpdb_mdata == NULL)
		{
			prj->Message("Please import a PDB file first;\nSee File/ExtraTools/ImportPDB...");
			return;
		}
		
prj->Message("sorry, this is under construction now...");
//		prj->aa2sf_ConvertAll(prj->importpdb_mdata);
//		prj->UpdateAllGraphicsViews();
	}
}
#endif
void win_project::popup_SelectAllEmptyWells(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectAllEmptyWells();
}

void win_project::popup_SelectAll(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectAll();
}

void win_project::popup_SelectNone(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectNone();		// should call the base class function to prevent the flash!!!
}

void win_project::popup_InvertSelection(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->InvertSelection();
}

void win_project::popup_DeleteSelection(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->DeleteSelection();
}

void win_project::popup_CheckSelection(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->CheckSelection();
}

void win_project::popup_UncheckSelection(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->UncheckSelection();
}

void win_project::popup_UncheckUnselection(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->UncheckUnselection();
}

void win_project::popup_CheckUnselection(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->CheckUnselection();
}

void win_project::popup_SelectionSetColor(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionSetColor();
}

void win_project::popup_SelectionSetColor_FromCurrentWellsSloj(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionSetColor_FromCurrentWellsSloj();
}
void win_project::popup_SelectionToGridData(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionToGridData();
}
void win_project::popup_Selection_With_CurrentWellsSloj_ToGridData(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->Selection_With_WellsCurrentSloj_ToGridData();
}
void win_project::popup_SelectionToLayer(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionToLayer();
}
void win_project::popup_SelectModeObject(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::Object;
cout << "select_mode = obj" << endl;
}
void win_project::popup_SelectionGetNamesAndID(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionGetNamesAndID();
}

void win_project::popup_SelectionSetName(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionSetName(widget, data);
}
void win_project::popup_SelectionSetID(HWND widget, void * data)
{
	win_graphics_view::GetGV(widget)->prj->SelectionSetID(widget, data);
}

void win_project::popup_SelectModeObjectsSameID(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::Objects_with_the_same_ID;
cout << "select_mode = ObjectsSameID" << endl;
}

void win_project::popup_SelectModeObjectsSameName(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::Objects_with_the_same_name;
cout << "select_mode = ObjectsSameName" << endl;
}

void win_project::popup_SelectModePoint(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::point_of_primitive;
cout << "select_mode = point" << endl;
}

void win_project::popup_SelectModeEdge(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::edge_or_line;
cout << "select_mode = Edge" << endl;
}

void win_project::popup_SelectModeTriangle(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::triangle;
cout << "select_mode = Triangle" << endl;
}

void win_project::popup_SelectModeQuad(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::quad;
cout << "select_mode = Quad" << endl;
}

void win_project::popup_SelectModePolygon(HWND widget, void * data)
{
	ogl_view::select_mode = select_tool::select_mode::polygon;
cout << "select_mode = Polygon" << endl;
}

void win_project::popup_ViewsNewELD(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		prj->AddEnergyLevelDiagramView(true);
	}
}

void win_project::popup_RModeBallStick(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->render = RENDER_BALL_AND_STICK; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_RModeVanDerWaals(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->render = RENDER_VAN_DER_WAALS; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_RModeCylinders(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->render = RENDER_CYLINDERS; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_RModeWireframe(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->render = RENDER_WIREFRAME; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_RModeNothing(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->render = RENDER_NOTHING; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_CModeElement(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->colormode = & project::cm_element; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_CModeSecStruct(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->colormode = & project::cm_secstruct; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_CModeHydPhob(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->colormode = & project::cm_hydphob; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeIndex(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_INDEX; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeElement(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_ELEMENT; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeFCharge(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_F_CHARGE; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModePCharge(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_P_CHARGE; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeAtomType(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_ATOMTYPE; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeBuilderID(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_BUILDER_ID; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeBondType(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_BONDTYPE; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeResidue(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_RESIDUE; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeSecStruct(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_SEC_STRUCT; gv->prj->UpdateAllGraphicsViews();
}

void win_project::popup_LModeNothing(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->label = LABEL_NOTHING; gv->prj->UpdateAllGraphicsViews();
}
#if 0
void win_project::popup_ObjRibbon(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->ref_civ) prj->UpdateChains();
		vector<chn_info> & ci_vector = (* prj->ref_civ);
		for (i32u n1 = 0;n1 < ci_vector.size();n1++)
		{
			if (ci_vector[n1].GetType() != chn_info::amino_acid) continue;
			if (ci_vector[n1].GetLength() < 3) continue;
			
			if (ci_vector[n1].GetSecStrStates() == NULL) DefineSecondaryStructure(prj);
			
			prj->AddObject(new ribbon(prj, gv->colormode, n1, 4));		// min. order is 2!!!
		}
		
		prj->UpdateAllGraphicsViews();
	}
}
void win_project::popup_ObjEPlane(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add plane esp rb1 138.0 AUTO 1.0 50 1 0.75";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjEVolume(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add volrend esp rb2 138.0 0.0 1.0 25 0.50";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjESurface(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add surf2 esp unity red blue +35.0 -35.0 1.0 0.0 2.0 50 0 0 0.50";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjEVDWSurface(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add surf1 vdws esp rb1 1.0 70.0 AUTO 2.0 50 1 1 0.65";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjEDPlane(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add plane eldens rb1 0.05 0.0 0.75 50 1 0.75";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjEDSurface(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add surf1 eldens unity red 0.01 1.0 0.0 1.5 50 0 0 0.65";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjMOPlane(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add plane mo rb1 0.05 0.0 0.75 50 1 0.75";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjMOVolume(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add volrend mo rb2 0.025 0.0 1.5 25 0.50";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjMOSurface(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add surf2 mo unity red blue +0.025 -0.025 1.0 0.0 1.5 50 0 0 0.50";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjMODPlane(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add plane mod rb1 0.005 0.0 0.75 50 1 0.75";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjMODVolume(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add volrend mod rb2 0.0025 0.0 1.5 25 0.35";
			new command_dialog(prj, gv, command);
		}
	}
}

void win_project::popup_ObjMODSurface(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (!prj->GetCurrentSetup()->GetCurrentEngine())
		{
			prj->Message("Please calculate energy first!");
		}
		else
		{
			static const char command[] = "add surf1 mod unity red 0.0025 1.0 0.0 1.5 50 0 0 0.65";
			new command_dialog(prj, gv, command);
		}
	}
}
#endif

void win_project::popup_ObjectsDeleteCurrent(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	gv->prj->DoDeleteCurrentObject();
}
#if 0
void win_project::popup_CompSetup(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	
	new setup_dialog(prj);		// will call delete itself...
}
void win_project::popup_CompEnergy(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj) prj->DoEnergy();
}
void win_project::popup_CompGeomOpt(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		setup * su = prj->GetCurrentSetup();
		static jobinfo_GeomOpt ji;
		
		ji.prj = prj;
		ji.go = geomopt_param(su);
		
		prj->start_job_GeomOpt(& ji);
	}
}

void win_project::popup_CompMolDyn(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		setup * su = prj->GetCurrentSetup();
		static jobinfo_MolDyn ji;
		
		ji.prj = prj;
		ji.md = moldyn_param(su);
		
		prj->start_job_MolDyn(& ji);
	}
}
#endif

void win_project::popup_CompRandomSearch(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "random_search 100 250";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompSystematicSearch(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "systematic_search 6 250";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompMonteCarloSearch(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "montecarlo_search 10 100 250";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompTorsionEnergyPlot1D(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
prj->Message("PLEASE NOTE!\nThe command string, which is displayed in the next dialog, is incomplete.\nYou should replace the letters A-D with atom indices that define the torsion.\n\nALSO NOTE: structure refinement is always done using molecular mechanics (optsteps).");
		
		static const char command[] = "make_plot1 A B C D 36 0.0 360.0 250";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompTorsionEnergyPlot2D(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
prj->Message("PLEASE NOTE!\nThe command string, which is displayed in the next dialog, is incomplete.\nYou should replace the letters A-D and I-L with atom indices that define the torsions.\n\nALSO NOTE: structure refinement is always done using molecular mechanics (optsteps).");
		
		static const char command[] = "make_plot2 A B C D 36 0.0 360.0 I J K L 36 0.0 360.0 250";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompPopAnaElectrostatic(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "population_analysis_ESP";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompTransitionStateSearch(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "transition_state_search 10.0 500.0";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_CompStationaryStateSearch(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "stationary_state_search 100";
		new command_dialog(prj, gv, command);
	}
}
#if 0
void win_project::popup_CompFormula(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj) prj->DoFormula();
}
void win_project::popup_CompSetFormalCharge(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "set_formal_charge X +0";
		new command_dialog(prj, gv, command);
	}
}
void win_project::popup_CompCreateRS(HWND widget, void * data)	// todo : this is only for testing?!?!?!?
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		if (prj->GetRS() == NULL) prj->CreateRS();
	}
}

void win_project::popup_CompCycleRS(HWND widget, void * data)	// todo : this is only for testing?!?!?!?
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj && prj->GetRS() != NULL)
	{
	//	prj->GetRS()->CycleStructures();
		prj->UpdateAllGraphicsViews();
	}
	else cout << "ERROR" << endl;
}

void win_project::popup_TrajView(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (!prj->GetTrajectoryFile())
	{
		if (prj)// new trajfile_dialog(prj);	// will call delete itself...
		{
			char filename[512];
			if (OpenFileDlg(widget, "Ghemical Trajectory File (*.traj)\0*.traj\0All files \0*.*\0", filename) == S_OK)
			{
				cout << "trying to open \"" << filename << "\"." << endl;
				prj->OpenTrajectory(filename);
				// check if there were problems with OpenTrajectory()?!?!?!
				// check if there were problems with OpenTrajectory()?!?!?!
				// check if there were problems with OpenTrajectory()?!?!?!
				
				static trajview_dialog * tvd = NULL;
				
				if (tvd != NULL) delete tvd;		// how to safely release the memory...
				tvd = new trajview_dialog(prj);		// ...right after the dialog is closed?
				
				// the dialog will call prj->CloseTrajectory() itself when closed!!!
				// the dialog will call prj->CloseTrajectory() itself when closed!!!
				// the dialog will call prj->CloseTrajectory() itself when closed!!!
			}
		}
	}
	else prj->ErrorMessage("Trajectory already open?!?!?!");
}

void win_project::popup_SetOrbital(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		prj->Message("PLEASE NOTE!\nThe command string, which is displayed in the next dialog, is incomplete.\nYou should replace the letter X with the orbital index that will become the current orbital.");
		
		static const char command[] = "set_current_orbital X";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_HAdd(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		prj->AddH();
		prj->UpdateAllGraphicsViews();
	}
}

void win_project::popup_HRemove(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		prj->RemoveH();
		prj->UpdateAllGraphicsViews();
	}
}

void win_project::popup_SolvateBox(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static char command[256];
		sprintf(command, "solvate_box %f %f %f 0.8 2", 
			prj->periodic_box_HALFdim[0],
			prj->periodic_box_HALFdim[1],
			prj->periodic_box_HALFdim[2]);
		//= "solvate_box 3.0 3.0 3.0";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_SolvateSphere(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		static const char command[] = "solvate_sphere 1.2 1.6";
		new command_dialog(prj, gv, command);
	}
}
#endif
void win_project::popup_Clear(HWND widget, void* data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj && 
	    prj->Question("Are you sure you want to clear everything?"))
	{
	  prj->ClearModel();
	  prj->UpdateAllGraphicsViews();
	}
}
#if 0

void win_project::popup_Library(GtkWidget *item, void * data)
{
  project * prj1 = (project *) win_object_get_user_data(GTK_OBJECT(item));
  win_project * prj = dynamic_cast<win_project *>(prj1);
  
  static char buffer[256];
  g_snprintf(buffer, 256, "%s", data);
  cout << "preparing to open a library file : " << buffer << endl;	// just for debugging...
  
  bool open = prj->IsEmpty();	// open, not insert
  
  ifstream ifile;
  ifile.open(buffer, ios::in);
  ReadGPR(* prj, ifile, true);
  
  // This should probably go into the prjiew class 
  // that is, the prjiew::ReadGPR() should override 
  // the model::ReadGPR() and the rest
  	
  if (!open)	// we append this file to the current project
    {
      if (prj->selected_object != NULL)
	{
	  prj->selected_object = NULL;
	}
    }
	
  ifile.close();
}
void win_project::popup_BuilderAmino(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
prj->Message("PLEASE NOTE!\nThe command string, which is displayed in the next dialog, is incomplete.\nYou should replace the default sequence AAA with the sequence to be built.");
		
		static const char command[] = "build_amino AAA";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_BuilderNucleic(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
prj->Message("PLEASE NOTE!\nThe command string, which is displayed in the next dialog, is incomplete.\nYou should replace the default sequence AGTCaguc with the sequence to be built.");
		
		static const char command[] = "build_nucleic AGTCaguc";
		new command_dialog(prj, gv, command);
	}
}

void win_project::popup_Center(HWND widget, void * data)
{
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		prj->CenterCRDSet(0, true);
		
		// Which is the current Coord Set?
		// usually it's 0, but it could be any/all. the crdset-system is not yet in GUI...
		
		// 2001-06-18 TH: yes, this is not quite ready. but i guess in the end we will
		// move ALL crd-sets...
		
// sometimes this centering won't work, if the camera won't point to the origo.
// so, here we try to turn it there. ANY EFFECTS TO LIGHTS, ETC??????

	//	for (i32u n1 = 0;n1 < prj->camera_vector.size();n1++)
	//	{
			// rotation or translation???
			// translation would affect less to lights (since it's accurate)????
	//	}
		
		prj->UpdateAllGraphicsViews();
	}
}
#endif //0

void win_project::popup_EnterCommand(HWND widget, void * data)
{
	printf ("win_project::popup_EnterCommand\n");
	win_graphics_view * gv = win_graphics_view::GetGV(widget);
	win_project * prj = dynamic_cast<win_project *>(gv->prj);
	if (prj)
	{
		new command_dialog(prj, gv, NULL);
	}
}
/*################################################################################################*/

// eof
