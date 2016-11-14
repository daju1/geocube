
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#include "../../lab/lab/labdoc.h"

// PROJECT.CPP

// Copyright (C) 1998 Tommi Hassinen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/
#include "StdAfx.h"

#include "project.h"	// config.h is here -> we get ENABLE-macros here...

#include "views.h"

#include "v3d.h"
#include "SelectLine.h"
#include "..\..\surfdoc\src\texture.h"

#define GDIPLUS_SELECTION_3D 0

//#include "../libghemical/src/atom.h"
//#include "../libghemical/src/bond.h"

//#include "../libghemical/src/engine.h"
//#include "../libghemical/src/eng1_qm.h"
//#include "../libghemical/src/eng1_mm.h"
//#include "../libghemical/src/eng1_sf.h"
//#include "../libghemical/src/eng2_qm_mm.h"
//#include "../libghemical/src/eng2_mm_sf.h"

//#include "../libghemical/src/geomopt.h"
//#include "../libghemical/src/intcrd.h"

//#include "../libghemical/src/pop_ana.h"

//#include "../libghemical/src/search.h"

#include "win32_dialog.h"
#include "win32_graphics_view.h"
#include "win32_map_views.h"

#include "utility.h"

#include "appdefine.h"

#include "plane.h"
#include "surface.h"

#include "color.h"
#include "views.h"

#include "..\..\surfdoc\src\whatselected.h"
#include "..\..\surfdoc\src\winsurftree.h"
#include "..\..\surfdoc\src\drawscene.h"
#include "..\..\wintools\src\SelectLayerDlg.h"

//#include "filetrans.h"

//#include <gdk/gdk.h>
#include "..\..\surfdoc\src\distance3D.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "../../glut37/glut-3.7/include/GL/glut.h"

#include <iomanip>
#include <algorithm>
#include <fstream>
#include <strstream>
using namespace std;

/*################################################################################################*/
#define APPVERSION "1.90"
#define APPDATA_PATH "/usr/local/share/ghemical"

const char project::appversion[16] = APPVERSION;
const char project::appdata_path[256] = APPDATA_PATH;

iGLu project::list_counter = 1;		// zero is not a valid display list number...

color_mode_element project::cm_element = color_mode_element();
color_mode_secstruct project::cm_secstruct = color_mode_secstruct();
color_mode_hydphob project::cm_hydphob = color_mode_hydphob();

extern HINSTANCE hInst;								// current instance
bool RegisterContextWindowClass(int);
bool RegisterContextWindowClass2(int);
bool RegisterPropertyWindowClass(int type);



project::project() : SurfDoc(false)
{

	//printf("project::project(graphics_class_factory & p1) : model()\n\n");



	graphics_factory = NULL;
	
	project_path = NULL;
	project_filename = NULL;

	select_buffer = NULL;
/*
	SetDefaultProjectFileName();
	
	select_buffer = new iGLu[SB_SIZE];
	selected_object = NULL;
	
	camera_counter = 1;
	object_counter = 1;
	*/
	pv = NULL;
	/*
//	trajfile = NULL;
	traj_num_atoms = NOT_DEFINED;
	total_traj_frames = NOT_DEFINED;
	current_traj_frame = NOT_DEFINED;
*/	
	mt_a1 = mt_a2 = mt_a3 = NULL;


	hContextWindow = NULL;
	RegisterContextWindowClass(1);
	RegisterContextWindowClass(2);

	RegisterContextWindowClass2(1);
	RegisterContextWindowClass2(2);

	RegisterPropertyWindowClass(1);
	RegisterPropertyWindowClass(2);

	selected_well_element = NULL;
	selected_well_element_x = 0;
	selected_well_element_y = 0;

	project::InitFonts();

	Laboratory::context_window_pt.x = 0;
	Laboratory::context_window_pt.y = 0;
}

project::project(graphics_class_factory & p1) : SurfDoc()
{
//printf("project::project(graphics_class_factory & p1) : model()\n\n");



	graphics_factory = & p1;
	
	project_path = NULL;
	project_filename = NULL;
	
	SetDefaultProjectFileName();
	
	select_buffer = new iGLu[SB_SIZE];
	selected_object = NULL;
	
	camera_counter = 1;
	object_counter = 1;
	
	pv = NULL;
	
//	trajfile = NULL;
	traj_num_atoms = NOT_DEFINED;
	total_traj_frames = NOT_DEFINED;
	current_traj_frame = NOT_DEFINED;
	
	mt_a1 = mt_a2 = mt_a3 = NULL;


	hContextWindow = NULL;
	RegisterContextWindowClass(1);
	RegisterContextWindowClass(2);

	RegisterContextWindowClass2(1);
	RegisterContextWindowClass2(2);

	RegisterPropertyWindowClass(1);
	RegisterPropertyWindowClass(2);

	selected_well_element = NULL;
	selected_well_element_x = 0;
	selected_well_element_y = 0;

	project::InitFonts();

	Laboratory::context_window_pt.x = 0;
	Laboratory::context_window_pt.y = 0;
}
void project::InitFonts()
{
#if TO_INIT_FONT 
	BaseLab::InitFont();

	PlotData::InitTitleFont();
	PlotData::InitXLabelFont();
	PlotData::InitYLabelFont();
	PlotData::InitXAxesFont();
	PlotData::InitYAxesFont();

	fmtstr::InitFont0();
	fmtstr::InitFont1();
	fmtstr::InitFont2();
	fmtstr::InitFont3();
#endif
}
project::~project(void)
{
	selected_object = NULL;
	
	if (pv != NULL) DestroyProjectView();
	
	while (graphics_view_vector.size() > 0)
	{
		graphics_view * ref;
		ref = graphics_view_vector.back();
		RemoveGraphicsView(ref, true);
	}
	
	while (object_vector.size() > 0)
	{
		smart_object * ref;
		ref = object_vector.back();
		RemoveObject(ref);
	}
	
	if (project_path != NULL) delete[] project_path;
	if (project_filename != NULL) delete[] project_filename;
	
	if (select_buffer) delete[] select_buffer;
	
//	if (trajfile != NULL) WarningMessage("Warning : trajectory file was not closed!");
}

bool project::AddTP(void * owner, transparent_primitive & tp)
{
	if (!tp.TestOwner(owner)) return false;		// this is just a double check, to make
	tp_vector.push_back(tp); return true;		// sure that we have correct "owner"...
}

void project::UpdateMPsForAllTPs(void * owner)
{
	for (i32u n1 = 0;n1 < tp_vector.size();n1++)
	{
		if (tp_vector[n1].TestOwner(owner)) tp_vector[n1].GetData()->UpdateMP();
	}
}

void project::RemoveAllTPs(void * owner)
{
	i32u n1 = 0;
	while (n1 < tp_vector.size())
	{
		vector<transparent_primitive>::iterator iter;
		
		if (!tp_vector[n1].TestOwner(owner))
		{
			n1++;
		}
		else
		{
			delete tp_vector[n1].GetData();		// destroy the data object!!!
			
			iter = (tp_vector.begin() + n1);
			tp_vector.erase(iter);
		}
	}
}

const char * project::GetProjectFileNameExtension(void)
{
	static const char ext[] = "gpr";
	return ext;
}

void project::SetProjectPath(const char * path)
{
	if (project_path != NULL) delete[] project_path;
	
	project_path = new char[strlen(path) + 1];
	strcpy(project_path, path);
}

void project::SetProjectFileName(const char * filename)
{
	if (project_filename != NULL) delete[] project_filename;
	
	project_filename = new char[strlen(filename) + 1];
	strcpy(project_filename, filename);
}

void project::SetDefaultProjectFileName(void)
{
	static i32s id_counter = 1;
	
	char buffer[1024];
	ostrstream str(buffer, sizeof(buffer));
	str << "untitled" << setw(2) << setfill('0') << id_counter++ << ends;
	
	SetProjectFileName(buffer);
}

void project::ParseProjectFileNameAndPath(const char * string)
{
	char * localstring1 = new char[strlen(string) + 1];
	strcpy(localstring1, string);
	
	i32s n1, lastdir = NOT_DEFINED;
	for (/*i32s*/ n1 = 0;n1 < (i32s) strlen(localstring1);n1++)
	{
		if (localstring1[n1] == DIR_SEPARATOR) lastdir = n1;
	}
	
	char * localstring2 = localstring1;
	
	// set project_path if needed...
	// set project_path if needed...
	// set project_path if needed...
	
	if (lastdir != NOT_DEFINED)
	{
		localstring2[lastdir] = 0;
		SetProjectPath(localstring2);
		
		localstring2 = & localstring2[lastdir + 1];
	}
	
	// and now set project_filename, without extension...
	// and now set project_filename, without extension...
	// and now set project_filename, without extension...
	
	i32s lastext = NOT_DEFINED;
	for (/*i32s*/ n1 = 0;n1 < (i32s) strlen(localstring2);n1++)
	{
		if (localstring2[n1] == EXT_SEPARATOR) lastext = n1;
	}
	
	if (lastext != NOT_DEFINED)
	{
	  // This only removes an extension if it matches *our* extension,
	  // which makes problems for imported files e.g. nh3.mol.mmg1p (!) instead of nh3.mol or nh3.mm1gp
	  //		char * localstring3 = & localstring2[lastext + 1];
	  //		bool has_extension = !strcmp(localstring3, GetProjectFileNameExtension());
	  //		if (has_extension) localstring2[lastext] = 0;

	  // instead
	  localstring2[lastext] = 0;
	}
	
	SetProjectFileName(localstring2);
	
	delete[] localstring1;
}

void project::GetProjectFileName(char * buffer, int buffer_size, bool with_extension)
{
	ostrstream ostr(buffer, buffer_size);
	
	ostr << project_filename;
	if (with_extension) ostr << EXT_SEPARATOR << GetProjectFileNameExtension();
	ostr << ends;
}

void project::GetFullProjectFileName(char * buffer, int buffer_size)
{
	ostrstream ostr(buffer, buffer_size);
	
	if (project_path != NULL) ostr << project_path << DIR_SEPARATOR;
	ostr << project_filename << EXT_SEPARATOR << GetProjectFileNameExtension() << ends;
}

/*##############################################*/
/*##############################################*/

#ifdef ENABLE_OPENBABEL

bool project::ImportFile(const char * filename, int index)
{
	ifstream ifile;
	ostrstream intermed;
	file_trans translator;
	
	if (index == 0)		// Automatic detection
	{
		if (!translator.CanImport(filename))
		{
			ErrorMessage("Cannot import that file type.");
			return false;
		}
		
		ifile.open(filename, ios::in);
		translator.Import(filename, ifile, intermed);
		ifile.close();
	}
	else			// By type picked by the user
	{
		ifile.open(filename, ios::in);
		translator.Import(filename, index - 1, ifile, intermed);
		ifile.close();
	}
	
	istrstream interInput(intermed.str());
	return ReadGPR((* this), interInput, false);
}

bool project::ExportFile(const char * filename, int index)
{
	ofstream ofile;
	strstream intermed;
	file_trans translator;
	
	WriteGPR_v100((* this), intermed);		// this is for openbabel-1.100.2
	istrstream interInput(intermed.str());
	
	if (index == 0) 	// Automatic detection
	{
		if (!translator.CanExport(filename))
		{
			ErrorMessage("Cannot export that file type.");
			return false;
		}
		
		ofile.open(filename, ios::out);
		translator.Export(filename, interInput, ofile);
		ofile.close();
	}
	else			// By type picked by the user
	{
		ofile.open(filename, ios::out);
		translator.Export(filename, index - 1, interInput, ofile);
		ofile.close();
	}
	
	return true;
}

#endif	// ENABLE_OPENBABEL

/*##############################################*/
/*##############################################*/
#if 0
void project::OpenTrajectory(const char * fn)
{
	if (!trajfile)
	{
		traj_num_atoms = GetAtomCount();
	/*	for (iter_al it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
		{
			if (!((* it1).flags & ATOMFLAG_IS_HIDDEN)) traj_num_atoms++;
		}	*/
		
		trajfile = new ifstream(fn, ios::in | ios::binary);
		trajfile->seekg(8, ios::beg);	// skip the file id...
		
		int natoms;
		trajfile->read((char *) & natoms, sizeof(natoms));
		
		if (natoms != traj_num_atoms)
		{
			ErrorMessage("The trajectory is incompatible with the current structure/setup!!!");
			PrintToLog("incompatible file : different number of atoms!\n");
			CloseTrajectory(); return;
		}
		
		trajfile->read((char *) & total_traj_frames, sizeof(total_traj_frames));
		
		char mbuff1[256]; strstream str1(mbuff1, sizeof(mbuff1));
		str1 << "the trajectory file contains " << total_traj_frames << " frames." << endl << ends;
		PrintToLog(mbuff1);
		
		current_traj_frame = 0;
	}
	else PrintToLog("trajectory already exists!\n");
}

void project::CloseTrajectory(void)
{
	if (trajfile != NULL)
	{
		trajfile->close();
		delete trajfile;
		
		trajfile = NULL;
	}
}

void project::ReadFrame(void)
{
	i32s place = 8 + 2 * sizeof(int);						// skip the header...
	place += (2 + 3 * traj_num_atoms) * sizeof(float) * current_traj_frame;		// get the correct frame...
	place += 2 * sizeof(float);							// skip epot and ekin...
	
	trajfile->seekg(place, ios::beg);
	
	for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
	{
	//	if ((* it1).flags & ATOMFLAG_IS_HIDDEN) continue;	// currently all coordinates are written...
		
		fGL cdata[3];
		for (i32s t4 = 0;t4 < 3;t4++)
		{
			float t1a; trajfile->read((char *) & t1a, sizeof(t1a));
			cdata[t4] = t1a;
		}
		
		(* it1).SetCRD(0, cdata[0], cdata[1], cdata[2]);
	}
}
i32s project::GetTotalFrames(void)
{
	return total_traj_frames;
}

ifstream * project::GetTrajectoryFile(void)
{
	return trajfile;
}

i32s project::GetCurrentFrame(void)
{
	return current_traj_frame;
}

void project::SetCurrentFrame(i32s p1)
{
	current_traj_frame = p1;
}

// todo : move all these trajectory-related things into a separate class? 20040610 TH

void project::EvaluateBFact(void)
{
	if (!trajfile)
	{
		PrintToLog("EvaluateBFact() : trajectory file not open!\n");
		return;
	}
	
	vector<atom *> av;	// pick all selected atoms here...
	for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
	{
		if ((* it1).flags & ATOMFLAG_SELECTED) av.push_back(& (* it1));
	}
	
	if (!av.size())
	{
		PrintToLog("EvaluateBFact() : no selected atoms!\n");
		return;
	}
	
	fGL * avrg_str = new fGL[av.size() * 3];
	fGL * b_tab = new fGL[av.size()];
	
	for (i32u ac = 0;ac < av.size();ac++)
	{
		avrg_str[ac * 3 + 0] = 0.0;
		avrg_str[ac * 3 + 1] = 0.0;
		avrg_str[ac * 3 + 2] = 0.0;
		
		b_tab[ac] = 0.0;
	}
	
	for (i32s n1 = 0;n1 < GetTotalFrames();n1++)
	{
		SetCurrentFrame(n1);
		ReadFrame();
		
		for (i32u ac = 0;ac < av.size();ac++)
		{
			const fGL * tmpc = av[ac]->GetCRD(0);
			
			avrg_str[ac * 3 + 0] += tmpc[0];
			avrg_str[ac * 3 + 1] += tmpc[1];
			avrg_str[ac * 3 + 2] += tmpc[2];
		}
	}
	
	for (/*i32u*/ ac = 0;ac < av.size();ac++)
	{
		avrg_str[ac * 3 + 0] /= (fGL) GetTotalFrames();
		avrg_str[ac * 3 + 1] /= (fGL) GetTotalFrames();
		avrg_str[ac * 3 + 2] /= (fGL) GetTotalFrames();
	}
	
	for (/*i32s*/ n1 = 0;n1 < GetTotalFrames();n1++)
	{
		SetCurrentFrame(n1);
		ReadFrame();
		
		for (i32u ac = 0;ac < av.size();ac++)
		{
			const fGL * tmpc = av[ac]->GetCRD(0);
			
			fGL dx = avrg_str[ac * 3 + 0] - tmpc[0];
			fGL dy = avrg_str[ac * 3 + 1] - tmpc[1];
			fGL dz = avrg_str[ac * 3 + 2] - tmpc[2];
			
			b_tab[ac] += dx * dx;
			b_tab[ac] += dy * dy;
			b_tab[ac] += dz * dz;
		}
	}
	
	for (/*i32u*/ ac = 0;ac < av.size();ac++)
	{
		b_tab[ac] /= (fGL) GetTotalFrames();
	}
	
	for (/*i32u*/ ac = 0;ac < av.size();ac++)
	{
		char txtbuff[1024];
		ostrstream txts(txtbuff, sizeof(txtbuff));
		
		txts << "atom " << av[ac]->index << " ";
		txts << "displacement " << b_tab[ac] << " nm^2 = " << (b_tab[ac] * 100.0) << " Е^2 ";
		txts << " -> Bfact " << 78.957 * (b_tab[ac] * 100.0) << endl << ends;
		
		PrintToLog(txtbuff);
	}
	
	delete[] avrg_str;
	delete[] b_tab;
}

void project::EvaluateDiffConst(double dt)
{
	if (!trajfile)
	{
		PrintToLog("EvaluateDiffConst() : trajectory file not open!\n");
		return;
	}
	
	vector<atom *> av;	// pick all selected atoms here...
	for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
	{
		if ((* it1).flags & ATOMFLAG_SELECTED) av.push_back(& (* it1));
	}
	
	if (!av.size())
	{
		PrintToLog("EvaluateDiffConst() : no selected atoms!\n");
		return;
	}
	
	fGL * init_loc = new fGL[av.size() * 3];
	double * dc_tab = new double[av.size()];
	
	SetCurrentFrame(0);
	ReadFrame();
	
	for (i32u ac = 0;ac < av.size();ac++)
	{
		const fGL * tmpc = av[ac]->GetCRD(0);
		
		init_loc[ac * 3 + 0] = tmpc[0];
		init_loc[ac * 3 + 1] = tmpc[1];
		init_loc[ac * 3 + 2] = tmpc[2];
		
		dc_tab[ac] = 0.0;
	}
	
	double time = 0.0;
	for (i32s n1 = 1;n1 < GetTotalFrames();n1++)
	{
		time += dt;
		
		SetCurrentFrame(n1);
		ReadFrame();
		
		for (i32u ac = 0;ac < av.size();ac++)
		{
			const fGL * tmpc = av[ac]->GetCRD(0);
			
			double dist = 0.0; double tmpd;
			tmpd = tmpc[0] - init_loc[ac * 3 + 0]; dist += tmpd * tmpd;
			tmpd = tmpc[1] - init_loc[ac * 3 + 1]; dist += tmpd * tmpd;
			tmpd = tmpc[2] - init_loc[ac * 3 + 2]; dist += tmpd * tmpd;
			
			// convert nm^2 into cm^2 ; 10^-14
			// convert fs into s ; 10^-15
			
			double dc = (dist * 1.0e-14) / (time * 1.0e-15);
			dc_tab[ac] += dc;
		}
	}
	
	for (/*i32u*/ ac = 0;ac < av.size();ac++)
	{
		dc_tab[ac] /= (double) (GetTotalFrames() - 1);
	}
	
	for (/*i32u*/ ac = 0;ac < av.size();ac++)
	{
		char txtbuff[1024];
		ostrstream txts(txtbuff, sizeof(txtbuff));
		
		txts << "atom " << av[ac]->index << " ";
		txts << "diffconst " << (dc_tab[ac] * 1.0e+5) << " * 10^-5 cm^2/s" << endl << ends;
		
		PrintToLog(txtbuff);
	}
	
	delete[] init_loc;
	delete[] dc_tab;
}

/*##############################################*/
/*##############################################*/

void project::AddH(void)
{
/*	file_trans ft;
	OBMol * obm = ft.CopyAll(this);
	obm->AddHydrogens(false, false);
	ft.Synchronize();	*/
	
// above is the OpenBabel implementation of hydrogen adding.
// it seems to use bond length information to determine how many H's to add,
// which is problematic for protein X-ray structures (that often are not precise enough).
// TODO : make all these alternative add_h implementations available!!!!!!!!!!!!!!!

	AddHydrogens();		// this is the library implementation...
	
	PrintToLog("Hydrogens added.\n");
}

void project::RemoveH(void)
{
	RemoveHydrogens();
	
	PrintToLog("Hydrogens removed.\n");
}
#endif

iGLu project::GetDisplayListIDs(iGLu p1)
{
	iGLu first = list_counter;
	list_counter += p1;
	
	return first;
}

void project::DeleteDisplayLists(iGLu p1, iGLu p2)
{
	for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
	{
		graphics_view_vector[n1]->SetCurrent();
		glDeleteLists(p1, p2);
	}
}

/*##############################################*/
/*##############################################*/
#if 0
void project::Add_Atom(atom & p1)
{
//	printf("project::Add_Atom(atom & p1)\n");
	model::Add_Atom(p1);
	if (pv != NULL) pv->AtomAdded(& atom_list.back());
}

void project::RemoveAtom(iter_al p1)
{
	if (pv != NULL) pv->AtomRemoved(& (* p1));
	model::RemoveAtom(p1);
}

void project::AddBond(bond & p1)
{
	model::AddBond(p1);
	if (pv != NULL) pv->BondAdded(& bond_list.back());
}

void project::RemoveBond(iter_bl p1)
{
	if (pv != NULL) pv->BondRemoved(& (* p1));
	model::RemoveBond(p1);
}
void project::InvalidateGroups(void)
{
	model::InvalidateGroups();
	if (pv != NULL) pv->ClearChainsView();
}

void project::UpdateChains(void)
{
	model::UpdateChains();
	if (pv != NULL) pv->BuildChainsView();
}
#endif
/*##############################################*/
/*##############################################*/
bool project::IsWellElement(const WellElement * p1)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_drills.GetCurrentMsg().IsWellElement(p1))
				return true;
		}
		while(this->m_drills.IncrementCurrentMsg());
	}	
	return false;
}

bool project::SelectWellElement(const WellElement * p1)
{
	if (!IsWellElement(p1))
		return false;
	
	//selected_object = p1;
	selected_well_element = (WellElement *)p1;

	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					wlap->PrintfProperties();
				}
			}
			break;
		}
	}	
	return true;
}
LRESULT CALLBACK ContextWndProc1( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	static vector<fmtstr> text;
	static SIZE sz;						
	static SIZE text_size;

	static RECT margin; 


	static bool		m_bCaptured;		// Признак захвата мыши
	static tagPOINT		m_pt;				// Текущая позиция мыши

	switch (message) 
	{
	case WM_CREATE :
		{
			text.clear();
			text_size.cx = 0;
			text_size.cy = 0;
			//##################################################
			margin.left = 10;
			margin.right = 10;
			margin.top = 10;
			margin.bottom = 10;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLong(hWnd,	GWL_USERDATA,(LONG)pcs->lpCreateParams);
			//##################################################
			//##################################################
			WellElement * selected_well_element = (WellElement *)GetWindowLong(hWnd, GWL_USERDATA);

			if (selected_well_element)
			{
				switch(selected_well_element->w_type)
				{
				case WellElement::type::laboratory_analizes:
					{
						Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
						if(wlap)
						{
							wlap->PrintfProperties(text);
							hdc = GetWindowDC(hWnd);								
							wlap->Paint(text, hWnd, hdc, margin, text_size, true);
						}
					}
					break;
				}
			}	
		}
		break;

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);

				WellElement * selected_well_element = (WellElement *)GetWindowLong(hWnd, GWL_USERDATA);

				if (selected_well_element)
				{
					switch(selected_well_element->w_type)
					{
					case WellElement::type::laboratory_analizes:
						{
							Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
							if(wlap)
							{
								wlap->Paint(text, hWnd, hdc, margin, text_size, false);
							}
						}
						break;
					}
				}
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN :
			{
				GetCursorPos(&m_pt);
				ScreenToClient(hWnd, &m_pt);

				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				if (m_bCaptured)
				{
					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				RECT rect;
				GetWindowRect(hWnd,&rect);

				rect.top -= (long)yDelta;

				SetWindowPos(hWnd, HWND_TOP, 
					rect.left, 
					rect.top, 
					0, 0, SWP_NOSIZE);

				//GetClientRect(hWnd,&rect);
				//InvalidateRect(hWnd,&rect, true);
			}
			break;
		case WM_MOUSEMOVE :
			{
				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						POINT pt;
						GetCursorPos(&pt);

						SetWindowPos(hWnd, HWND_TOP, 
							pt.x - m_pt.x, 
							pt.y - m_pt.y - 1, 
							0, 0, SWP_NOSIZE);

						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
					}
				}
			}
			break;
		case WM_RBUTTONDOWN:
			{
				WellElement * selected_well_element = (WellElement *)GetWindowLong(hWnd, GWL_USERDATA);
				if (selected_well_element)
				{
					switch(selected_well_element->w_type)
					{
					case WellElement::type::laboratory_analizes:
						{
							Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
							if(wlap)
							{
								wlap->CreateMyPopupMenu(hWnd);
							}
						}
						break;
					}
				}
			}
			break;
		case WM_COMMAND:
			{
				SendMessage(::GetParent(hWnd), message, wParam, lParam);
			}
			break;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
LRESULT CALLBACK ContextWndProc2( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	static vector<LabData> labdata;
	static SIZE sz;						
	static SIZE text_size;

	static RECT margin;  

	static bool		m_bCaptured;		// Признак захвата мыши
	static tagPOINT		m_pt;				// Текущая позиция мыши

	switch (message) 
	{
	case WM_CREATE :
		{
			labdata.clear();
			text_size.cx = 0;
			text_size.cy = 0;
			//##################################################
			margin.left = 10;
			margin.right = 10;
			margin.top = 10;
			margin.bottom = 10;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLong(hWnd,	GWL_USERDATA,(LONG)pcs->lpCreateParams);
			//##################################################
			//##################################################
			WellElement * selected_well_element = (WellElement *)GetWindowLong(hWnd, GWL_USERDATA);

			if (selected_well_element)
			{
				switch(selected_well_element->w_type)
				{
				case WellElement::type::laboratory_analizes:
					{
						Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
						if(wlap)
						{
							wlap->PrintfProperties(labdata);
							hdc = GetWindowDC(hWnd);								
							wlap->Paint(labdata, hWnd, hdc, margin, text_size, true);
						}
					}
					break;
				}
			}	
		}
		break;

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				WellElement * selected_well_element = (WellElement *)GetWindowLong(hWnd, GWL_USERDATA);

				if (selected_well_element)
				{
					switch(selected_well_element->w_type)
					{
					case WellElement::type::laboratory_analizes:
						{
							Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
							if(wlap)
							{
								wlap->Paint(labdata, hWnd, hdc, margin, text_size, false);
							}
						}
						break;
					}
				}
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN :
			{
				GetCursorPos(&m_pt);
				ScreenToClient(hWnd, &m_pt);
				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				if (m_bCaptured)
				{
					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				RECT rect;
				GetWindowRect(hWnd,&rect);

				rect.top -= (long)yDelta;

				SetWindowPos(hWnd, HWND_TOP, 
					rect.left, 
					rect.top, 
					0, 0, SWP_NOSIZE);

				//GetClientRect(hWnd,&rect);
				//InvalidateRect(hWnd,&rect, true);
			}
			break;
		case WM_MOUSEMOVE :
			{
				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						POINT pt;
						GetCursorPos(&pt);						
					
						SetWindowPos(hWnd, HWND_TOP, 
							pt.x - m_pt.x, 
							pt.y - m_pt.y - 1, 
							0, 0, SWP_NOSIZE);

						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
					}
				}
			}
			break;
		case WM_RBUTTONDOWN:
			{
				WellElement * selected_well_element = (WellElement *)GetWindowLong(hWnd, GWL_USERDATA);
				if (selected_well_element)
				{
					switch(selected_well_element->w_type)
					{
					case WellElement::type::laboratory_analizes:
						{
							Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
							if(wlap)
							{
								wlap->CreateMyPopupMenu(hWnd);
							}
						}
						break;
					}
				}
			}
			break;
		case WM_COMMAND:
			{
				SendMessage(::GetParent(hWnd), message, wParam, lParam);
			}
			break;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
LPCTSTR lpszContextWindow1   = "ContextWindow1";
LPCTSTR lpszContextWindow2   = "ContextWindow2";
bool RegisterContextWindowClass(int type)
{
	WNDCLASSEX wc;
	// Регистрация класса главного окна приложения.
	//............................................
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	switch(type)
	{
	case 1:
		{
			wc.lpfnWndProc   = (WNDPROC)ContextWndProc1;
			wc.lpszClassName = lpszContextWindow1;
		}
		break;
	case 2:
		{
			wc.lpfnWndProc   = (WNDPROC)ContextWndProc2;
			wc.lpszClassName = lpszContextWindow2;
		}
		break;
	}
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = NULL;//LoadIcon( hInst, lpszWinGeoidName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = NULL;

	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","ContextWindow",0);
			return( FALSE );
		}
	}
	return true;
}
bool project::SelectWellElement(int x, int y, const WellElement * p1, HWND hWndParent)
{
	if (!IsWellElement(p1))
		return false;

	selected_well_element = (WellElement *)p1;
	selected_well_element_x = x;
	selected_well_element_y = y;

	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					if (!hContextWindow)
					{
						/*RECT rect;
						GetWindowRect(this->hSurfWnd, &rect);

						RECT rectParent;
						GetWindowRect(::GetParent(this->hSurfWnd), &rectParent);*/

						hContextWindow = CreateWindow(Laboratory::context_with_plot ? lpszContextWindow2 : lpszContextWindow1,
							"",//    LPCTSTR lpWindowName,
							WS_POPUP | WS_BORDER, //DWORD dwStyle,
							x,y,
							1,//int nWidth,
							1,//   int nHeight,
							hWndParent,//this->hSurfWnd,//HWND hWndParent,
							NULL,//    HMENU hMenu,
							hInst,//HINSTANCE hInstance,
							LPVOID(p1)//LPVOID lpParam
							);

						ShowWindow(hContextWindow, 1);
					}

				}
			}
			break;
		}
	}	


	return true;
}
void project::DestroyContextWindow()
{
	DestroyWindow(hContextWindow);
	hContextWindow = NULL; 
	selected_well_element = NULL;
}

bool project::LabWellElementProp()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					wlap->Properties();
				}
			}
			break;
		}
	}	
	return true;
}

bool project::LabWellElementPropSave()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					wlap->PropSave(Laboratory::context_with_plot);
				}
			}
			break;
		}
	}	
	return true;
}


bool project::LabWellElementPassport()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					wlap->Passport();
				}
			}
			break;
		}
	}	
	return true;
}
bool project::LabWellElementPropFont(int wmId)
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	  
				CHOOSEFONT cf;            // common dialog box structure					  
				// Initialize CHOOSEFONT
				ZeroMemory(&cf, sizeof(cf));
				cf.lStructSize = sizeof (cf);
				//cf.hwndOwner = hWnd;
				cf.hwndOwner = this->hContextWindow;
				cf.hDC = GetDC(this->hContextWindow);
				switch (wmId)
				{                    
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT:
					cf.lpLogFont = &Well_Laboratory_Analize::lf_Label;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT0:
					cf.lpLogFont = &fmtstr::LogFont0;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT1:
					cf.lpLogFont = &fmtstr::LogFont1;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT2:
					cf.lpLogFont = &fmtstr::LogFont2;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT3:
					cf.lpLogFont = &fmtstr::LogFont3;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_TITLE:
					cf.lpLogFont = &PlotData::TitleFont;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XLABEL:
					cf.lpLogFont = &PlotData::XLabelFont;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YLABEL:
					cf.lpLogFont = &PlotData::YLabelFont;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XAXES:
					cf.lpLogFont = &PlotData::XAxesFont;
					break;
				case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YAXES:
					cf.lpLogFont = &PlotData::YAxesFont;
					break;
				}
				cf.rgbColors = 0;
				cf.Flags = CF_BOTH | CF_EFFECTS | CF_TTONLY | CF_INITTOLOGFONTSTRUCT ;
				
				if (ChooseFont(&cf)==TRUE) 
				{
					if (ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YLABEL == wmId)
					{
						PlotData::YLabelFont.lfEscapement = 900;
					}
					return true;
				}

			}
			break;
		}
	}	
	return false;
}
bool project::LabGurvichYSecondDerivativeLimit()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					if (wlap->lab_number)
					{
						LabLayer * lab_layer = (LabLayer *)wlap->lab_number->GetLabLayer();
						if (lab_layer)
						{
							char s1[1024];
							sprintf(s1, "%f", Gurvich::y_SecondDerivativeLimit);
							DeleteEndZeros(s1);

							static char command[1024] = "";
							sprintf(command, "%s\0", s1);
							command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
							if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

							if (cmnd_dlg && cmnd_dlg->WasOk())
							{
								istrstream istr(command);

								char kw0[32]; istr >> kw0;

								printf("%s\n", kw0);

								if (
									strlen(kw0) > 0 
									)
								{
									Gurvich::y_SecondDerivativeLimit = atof(kw0);
									Laboratory * plaboratory = (Laboratory *)lab_layer->GetLaboratory();
									if(plaboratory)
										plaboratory->ReCalcProperties(false, true);
									ReCreateContextWindow();
								}
							}

							if (cmnd_dlg)
							{
								delete cmnd_dlg;
								cmnd_dlg = NULL;
							}
						}
					}
				}
			}
			break;
		}
	}	
	return true;
}


bool project::LabCompressionESecondDerivativeLimit()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					if (wlap->lab_number)
					{
						LabLayer * lab_layer = (LabLayer *)wlap->lab_number->GetLabLayer();
						if (lab_layer)
						{
							char s1[1024];
							sprintf(s1, "%f", CompressionLabTrialResults::e_SecondDerivativeLimit);
							DeleteEndZeros(s1);

							static char command[1024] = "";
							sprintf(command, "%s\0", s1);
							command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
							if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

							if (cmnd_dlg && cmnd_dlg->WasOk())
							{
								istrstream istr(command);

								char kw0[32]; istr >> kw0;

								printf("%s\n", kw0);

								if (
									strlen(kw0) > 0 
									)
								{
									CompressionLabTrialResults::e_SecondDerivativeLimit = atof(kw0);
									Laboratory * plaboratory = (Laboratory *)lab_layer->GetLaboratory();
									if(plaboratory)
										plaboratory->ReCalcProperties(false, true);
									ReCreateContextWindow();
								}
							}

							if (cmnd_dlg)
							{
								delete cmnd_dlg;
								cmnd_dlg = NULL;
							}
						}
					}
				}
			}
			break;
		}
	}	
	return true;
}


bool project::LabCompressionPressure()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					if (wlap->lab_number)
					{
						LabLayer * lab_layer = (LabLayer *)wlap->lab_number->GetLabLayer();
						if (lab_layer)
						{
							char s1[1024];
							sprintf(s1, "%f", lab_layer->deformation_module_defined_pressure);
							DeleteEndZeros(s1);

							static char command[1024] = "";
							sprintf(command, "%s\0", s1);
							command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
							if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

							if (cmnd_dlg && cmnd_dlg->WasOk())
							{
								istrstream istr(command);

								char kw0[32]; istr >> kw0;

								printf("%s\n", kw0);

								if (
									strlen(kw0) > 0 
									)
								{
									lab_layer->deformation_module_defined_pressure = atof(kw0);
									
									lab_layer->ReCalcProperties(false, false);
									ReCreateContextWindow();
								}
							}

							if (cmnd_dlg)
							{
								delete cmnd_dlg;
								cmnd_dlg = NULL;
							}
						}
					}
				}
			}
			break;
		}
	}	
	return true;
}


bool project::LabCompressionPressureInterval()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	
				Well_Laboratory_Analize * wlap = dynamic_cast<Well_Laboratory_Analize *>(selected_well_element);
				if(wlap)
				{
					if (wlap->lab_number)
					{
						LabLayer * lab_layer = (LabLayer *)wlap->lab_number->GetLabLayer();
						if (lab_layer)
						{
							char s1[1024];
							char s2[1024];
							sprintf(s1, "%f", lab_layer->deformation_module_defined_pressure_interval[0]);
							sprintf(s2, "%f", lab_layer->deformation_module_defined_pressure_interval[1]);
							DeleteEndZeros(s1);
							DeleteEndZeros(s2);

							static char command[1024] = "";
							sprintf(command, "%s %s\0", s1, s2);
							command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
							if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

							if (cmnd_dlg && cmnd_dlg->WasOk())
							{
								istrstream istr(command);

								char kw0[32]; istr >> kw0;
								char kw1[32]; istr >> kw1;

								printf("%s\n", kw0);
								printf("%s\n", kw1);

								if (
									strlen(kw0) > 0 &&
									strlen(kw1) > 0 
									)
								{
									lab_layer->deformation_module_defined_pressure_interval[0] = atof(kw0);
									lab_layer->deformation_module_defined_pressure_interval[1] = atof(kw1);
									
									lab_layer->ReCalcProperties(false, false);
									ReCreateContextWindow();
								}
							}

							if (cmnd_dlg)
							{
								delete cmnd_dlg;
								cmnd_dlg = NULL;
							}
						}
					}
				}
			}
			break;
		}
	}	
	return true;
}


bool project::LabWellElementPropPlotHeight()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	



				static char command[1024] = "";
				sprintf(command, "%d\0", PlotData::plot_height);
				command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
				if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

				if (cmnd_dlg && cmnd_dlg->WasOk())
				{
					PlotData::plot_height = atoi(command);;
				}

				if (cmnd_dlg)
				{
					delete cmnd_dlg;
					cmnd_dlg = NULL;
				}					

				ReCreateContextWindow();
			}
			break;
		}
	}	
	return true;
}
void project::ReCreateContextWindow()
{
	HWND hWndParent = ::GetParent(hContextWindow);
	RECT rect;
	GetWindowRect(hContextWindow, &rect);

	DestroyWindow(hContextWindow);
	hContextWindow = CreateWindow(Laboratory::context_with_plot ? lpszContextWindow2 : lpszContextWindow1,
		"",//    LPCTSTR lpWindowName,
		WS_POPUP | WS_BORDER, //DWORD dwStyle,
		rect.left,
		rect.top,
		1,//int nWidth,
		1,//   int nHeight,
		hWndParent,//this->hSurfWnd,//HWND hWndParent,
		NULL,//    HMENU hMenu,
		hInst,//HINSTANCE hInstance,
		LPVOID(selected_well_element)//LPVOID lpParam
		);

	ShowWindow(hContextWindow, 1);
}
void project::ReDrawContextWindow()
{
	RECT rect;
	GetClientRect(hContextWindow, &rect);
	InvalidateRect(hContextWindow, &rect, true);
	UpdateWindow(hContextWindow);
}
bool project::LabWaterSaturatedPartOfFullWaterCapacity()
{
	if (selected_well_element)
	{
		switch(selected_well_element->w_type)
		{
		case WellElement::type::laboratory_analizes:
			{	
				static char command[1024] = "";
				sprintf(command, "%f\0", PhysicalLabTrialResults::water_saturated_part_of_full_water_capacity);
				DeleteEndZeros(command);

				command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
				if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

				if (cmnd_dlg && cmnd_dlg->WasOk())
				{
					PhysicalLabTrialResults::water_saturated_part_of_full_water_capacity = atof(command);;
				}

				if (cmnd_dlg)
				{
					delete cmnd_dlg;
					cmnd_dlg = NULL;
				}

				this->m_laboratory.ReCalcProperties(false,false);

				ReCreateContextWindow();
			}
			break;
		}
	}	
	return true;
}


/*##############################################*/
/*##############################################*/

i32s project::IsLight(const dummy_object * p1)
{
	i32s index = NOT_DEFINED;
	for (i32u n1 = 0;n1 < light_vector.size();n1++)
	{
		if (light_vector[n1] == p1) index = n1;
	}
	
	return index;
}

bool project::SelectLight(const dummy_object * p1)
{
	i32s n1 = IsLight(p1);
	if (n1 < 0) return false;
	
	selected_object = light_vector[n1];
	
	return true;
}

bool project::AddGlobalLight(light * p1)
{
	iGLs max_local_size = 0;
	i32u n1;
	for (/*i32u*/ n1 = 0;n1 < camera_vector.size();n1++)
	{
		iGLs local_size = CountLocalLights(camera_vector[n1]);
		if (local_size > max_local_size) max_local_size = local_size;
	}
	
	iGLs total_lights = CountGlobalLights() + max_local_size;
	
// we really can't do this test here ; see SetupLights()...
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//iGLs max_lights; glGetIntegerv(GL_MAX_LIGHTS, & max_lights);
//if (total_lights == max_lights) return false;
	
	light_vector.push_back(p1);
	SetGlobalLightNumbers();
	
	for (/*i32u*/ n1 = 0;n1 < camera_vector.size();n1++)
	{
		SetLocalLightNumbers(camera_vector[n1]);
		SetupLights(camera_vector[n1]);
	}
	
	if (pv != NULL) pv->LightAdded(p1);
	
	selected_object = light_vector.back();
	
	cout << "added global light." << endl;
	return true;
}

bool project::AddLocalLight(light * p1, camera * p2)
{
//printf("project::AddLocalLight(light * p1, camera * p2)\n\n");

	iGLs total_lights = CountGlobalLights() + CountLocalLights(p2);

// we really can't do this test here ; see SetupLights()...
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//iGLs max_lights; glGetIntegerv(GL_MAX_LIGHTS, & max_lights);
//if (total_lights == max_lights) return false;
	
	p1->owner = p2; light_vector.push_back(p1);
	SetLocalLightNumbers(p2); SetupLights(p2);
	
	if (pv != NULL) pv->LightAdded(p1);
	
	selected_object = light_vector.back();
	
	cout << "added local light." << endl;
	return true;
}

bool project::RemoveLight(dummy_object * p1)
{
	i32s n1 = IsLight(p1);
	if (n1 < 0) return false;
	
	if (pv != NULL) pv->LightRemoved(light_vector[n1]);
	
	camera * owner = light_vector[n1]->owner;
	light_vector.erase(light_vector.begin() + n1);
	delete p1;
	
	if (owner != NULL)
	{
		SetLocalLightNumbers(owner);
		SetupLights(owner);
	}
	else
	{
		SetGlobalLightNumbers();
		for (i32u n1 = 0;n1 < camera_vector.size();n1++)
		{
			SetLocalLightNumbers(camera_vector[n1]);
			SetupLights(camera_vector[n1]);
		}
	}
	
	return true;
}

iGLs project::CountGlobalLights(void)
{
	iGLs sum = 0; i32u n1 = 0;
	while (n1 < light_vector.size())
	{
		if (light_vector[n1++]->owner == NULL) sum++;
	}
	
	return sum;
}

iGLs project::CountLocalLights(camera * p1)
{
	iGLs sum = 0; i32u n1 = 0;
	while (n1 < light_vector.size())
	{
		if (light_vector[n1++]->owner == p1) sum++;
	}
	
	return sum;
}

bool project::SetupLights(camera * p1)
{
printf("project::SetupLights(camera * p1 = %x)\n\n", p1);

	if (p1->prj != this) return false;
	
	for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
	{
		if (graphics_view_vector[n1]->cam != p1) continue;
		
		// the following call to SetCurrent() might work, or might not work.
		// it is really difficult to know, since it depends on whether the graphics
		// system is properly initialized or not (widget realized in GTK+).
		
		// if the call fails, we just skip everything...
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		
		bool failed = !graphics_view_vector[n1]->SetCurrent();
		if (failed) { cout << "GL is not yet initialized -> skipping light setup!" << endl; continue; }
		
		iGLs max_lights;
		glGetIntegerv(GL_MAX_LIGHTS, & max_lights);
		
		for (iGLs n2 = 0;n2 < max_lights;n2++)
		{
			glDisable((GLenum) (GL_LIGHT0 + n2));
		}
		{
		for (i32u n2 = 0;n2 < light_vector.size();n2++)
		{
			bool test1 = (light_vector[n2]->owner != NULL);
			bool test2 = (light_vector[n2]->owner != p1);
			if (test1 && test2) continue;
			
			light_vector[n2]->SetupProperties(); bool test = false;
			if (light_vector[n2]->owner == NULL && p1->use_global_lights)
			{
				printf("light_vector[n2]->number = %d global_light\n", light_vector[n2]->number);
				test = true;
			}
			if (light_vector[n2]->owner == p1 && p1->use_local_lights)
			{
				printf("light_vector[n2]->number = %d local_light\n", light_vector[n2]->number);
				test = true;
			}
			if (test)
			{
				printf("glEnable((GLenum) light_vector[n2]->number = %d\n", light_vector[n2]->number);
				glEnable((GLenum) light_vector[n2]->number);
			}
		}
		}
	}
	
	return true;
}

void project::SetGlobalLightNumbers(void)
{
	iGLs counter = 0;
	for (i32u n1 = 0;n1 < light_vector.size();n1++)
	{
		if (light_vector[n1]->owner != NULL) continue;
		light_vector[n1]->number = GL_LIGHT0 + counter++;
	}
}

void project::SetLocalLightNumbers(camera * p1)
{
//printf("project::SetLocalLightNumbers(camera * p1)\n\n");

	iGLs counter = CountGlobalLights();
	for (i32u n1 = 0;n1 < light_vector.size();n1++)
	{
		if (light_vector[n1]->owner != p1) continue;
		light_vector[n1]->number = GL_LIGHT0 + counter++;
	}
}

/*##############################################*/
/*##############################################*/

i32s project::IsObject(const dummy_object * p1)
{
	i32s index = NOT_DEFINED;
	for (i32u n1 = 0;n1 < object_vector.size();n1++)
	{
		if (object_vector[n1] == p1) index = n1;
	}
	
	return index;
}

bool project::SelectObject(const dummy_object * p1)
{
	i32s n1 = IsObject(p1);
	if (n1 < 0) return false;
	
	selected_object = object_vector[n1];
	
	return true;
}

void project::AddObject(smart_object * p1)
{
	object_vector.push_back(p1);
	selected_object = object_vector.back();
	
	if (pv != NULL) pv->ObjectAdded(p1);
}

bool project::RemoveObject(dummy_object * p1)
{
	i32s n1 = IsObject(p1);
	if (n1 < 0) return false;
	
	if (pv != NULL) pv->ObjectRemoved(object_vector[n1]);
	
	object_vector.erase(object_vector.begin() + n1);
	delete p1; return true;
}

// these are the measuring functions, that only take coordinates as input (so they are model-independent)...
// these are the measuring functions, that only take coordinates as input (so they are model-independent)...
// these are the measuring functions, that only take coordinates as input (so they are model-independent)...

float measure_len(float * c1, float * c2)
{
	v3d<float> v1(c1, c2);
	return v1.len();
}

float measure_ang(float * c1, float * c2, float * c3)
{
/*	Vector v1, v2;
	v1 = Vector(c1[0] - c2[0], c1[1] - c2[1], c1[2] - c2[2]);
	v2 = Vector(c3[0] - c2[0], c3[1] - c2[1], c3[2] - c2[2]);
	return VectorAngle(v1, v2);	*/
	
	v3d<float> v1(c2, c1);
	v3d<float> v2(c2, c3);
	return v1.ang(v2) * 180.0 / M_PI;
}

float measure_tor(float * c1, float * c2, float * c3, float * c4)
{
/*	Vector v1, v2, v3, v4;
	v1 = Vector(c1[0], c1[1], c1[2]) * 10.0f;
	v2 = Vector(c2[0], c2[1], c2[2]) * 10.0f;
	v3 = Vector(c3[0], c3[1], c3[2]) * 10.0f;
	v4 = Vector(c4[0], c4[1], c4[2]) * 10.0f;
	return CalcTorsionAngle(v1, v2, v3, v4);	*/
	
	v3d<float> v1(c2, c1);
	v3d<float> v2(c2, c3);
	v3d<float> v3(c3, c4);
	return v1.tor(v2, v3) * 180.0 / M_PI;
}

/*##############################################*/
/*##############################################*/

project_view * project::CreateProjectView(void)
{
//printf("project_view * project::CreateProjectView(void)\n\n");
	if (pv != NULL) return pv;
	else
	{
		pv = GetGraphicsFactory()->ProduceProjectView(this);
		return pv;
	}
}

bool project::DestroyProjectView(void)
{
	if (!pv) return false;
	else
	{
		delete pv;
		pv = NULL;
		
		return true;
	}
}

graphics_view * project::AddGraphicsView(camera * p1, bool detached)
{
//printf("SurfCube project::AddGraphicsView() begin\n");

	camera * cam = p1;
	
	if (!p1)
	{
		fGL focus = GetDefaultFocus();
		camera_vector.push_back(new camera(ol_static(), focus, this));
		cam = camera_vector.back();
		
		if (pv != NULL) pv->CameraAdded(camera_vector.back());
	}
	
	graphics_view_vector.push_back(GetGraphicsFactory()->ProduceGraphicsView(this, cam, detached));
	
	if (pv != NULL) pv->GraphicsViewAdded(graphics_view_vector.back());
#if 0
#else
	if (!p1)
	{
		// also add a default light, so that we can see something...
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		
		AddLocalLight(new spot_light(ol_static(), GetNewObjectID()), cam);
		AddLocalLight(new directional_light(ol_static(), GetNewObjectID()), cam);
	}
	else
	{
		// setup the old lights that we already have...
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		
		SetupLights(cam);
	}
	//this->SetLight();
#endif
	UpdateAllWindowTitles();
	return graphics_view_vector.back();
}

bool project::RemoveGraphicsView(graphics_view * p1, bool force)
{
	i32s n1 = NOT_DEFINED;
	for (i32u n2 = 0;n2 < camera_vector.size();n2++)
	{
		if (camera_vector[n2] == p1->cam) n1 = n2;
	}
	
	if (n1 == NOT_DEFINED)		// this should never happen...
	{
		cout << "WARNING: could not find the camera at project::RemoveGraphicsView()." << endl;
		return false;
	}
	
	i32s other_views_for_this_cam = 0;	// this is also calculated at IsThisLastGraphicsView().
	{
	i32s n2 = NOT_DEFINED;
	for (i32u n3 = 0;n3 < graphics_view_vector.size();n3++)
	{
		if (graphics_view_vector[n3] == p1) n2 = n3;
		else if (graphics_view_vector[n3]->cam == p1->cam) other_views_for_this_cam++;
	}
	
	if (n2 == NOT_DEFINED)		// this should never happen...
	{
		cout << "WARNING: could not find the view at project::RemoveGraphicsView()." << endl;
		return false;
	}
	
	if (!force && (!other_views_for_this_cam && camera_vector.size() < 2))	// refuse to close the last window!!!
	{
		ErrorMessage("This is the last graphics view for\nthis project - can't close it.");
		return false;
	}
	
	// if this was the last view for a camera, we have to remove also the camera.
	// but before that we must remove all local lights that relate to the camera...
	
	// a light object can also be selected_object, so we must compare the pointers
	// and invalidate selected_object if necessary...
	
	if (!other_views_for_this_cam)
	{
		i32u n3 = 0;
		while (n3 < light_vector.size())
		{
			if (light_vector[n3]->owner == camera_vector[n1])
			{
				if (selected_object != NULL)
				{
					if (selected_object == light_vector[n3])
					{
						selected_object = NULL;
					}
				}
				
				if (pv != NULL) pv->LightRemoved(light_vector[n3]);
				
				delete light_vector[n3];
				light_vector.erase(light_vector.begin() + n3);
			}
			else n3++;
		}
		
		SetGlobalLightNumbers();
		for (n3 = 0;n3 < camera_vector.size();n3++)
		{
			if (n1 == (i32s) n3) continue;
			
			SetLocalLightNumbers(camera_vector[n3]);
			SetupLights(camera_vector[n3]);
		}
	}
	
	// now it's time to remove the window...
	
	if (pv != NULL) pv->GraphicsViewRemoved(graphics_view_vector[n2]);
	
	delete graphics_view_vector[n2];
	graphics_view_vector.erase(graphics_view_vector.begin() + n2);
	
	// and now we finally can remove the camera, if needed...
	
	if (!other_views_for_this_cam)
	{
		if (pv != NULL) pv->CameraRemoved(camera_vector[n1]);
		
		delete camera_vector[n1];
		camera_vector.erase(camera_vector.begin() + n1);
	}
	
	UpdateAllWindowTitles();
	}
	return true;
}
/*
bool project::RemoveGDIplusView(gdiplus_view * p1, bool force)
{
	delete graphics_view_vector[n2];
	graphics_view_vector.erase(graphics_view_vector.begin() + n2);
	return true;
}
*/
bool project::IsThisLastGraphicsView(graphics_view * p1)
{
	i32s other_views_for_this_cam = 0;
	for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
	{
		bool test1 = (graphics_view_vector[n1] == p1);
		bool test2 = (graphics_view_vector[n1]->cam == p1->cam);
		
		if (!test1 && test2) other_views_for_this_cam++;
	}
	
	if (!other_views_for_this_cam && camera_vector.size() < 2) return true;
	else return false;
}

plot1d_view * project::AddPlot1DView(i32s ud1, const char * title, const char * s1, const char * sv, bool detached)
{
	plot1d_view * p1dv = graphics_factory->ProducePlot1DView(this, ud1, title, s1, sv, detached);
	plotting_view_vector.push_back(p1dv);
	
	if (pv != NULL) pv->PlottingViewAdded(plotting_view_vector.back());
	
	return p1dv;
}

map_view * project::AddMapView(Object * ob, bool detached)
{
	map_view * p1dv = graphics_factory->ProduceMapView(this, ob, detached);
	map_view_vector.push_back(p1dv);
	
	p1dv->UpdateExtremums();

	if (pv != NULL) pv->MapViewAdded(map_view_vector.back());
	
	return p1dv;
}

map_view * project::AddGDIMapView(Object * ob, bool detached)
{
	map_view * p1dv = graphics_factory->ProduceGDIMapView(this, ob, detached);
	//plotting_view_vector.push_back(p1dv);
	map_view_vector.push_back(p1dv);

	p1dv->UpdateExtremums();

	if (pv != NULL) pv->MapViewAdded(map_view_vector.back());
	//if (pv != NULL) pv->PlottingViewAdded(plotting_view_vector.back());
	
	return p1dv;
}

plot2d_view * project::AddPlot2DView(i32s ud2, const char * s1, const char * s2, const char * sv, bool detached)
{
	plot2d_view * p2dv = graphics_factory->ProducePlot2DView(this, ud2, s1, s2, sv, detached);
	plotting_view_vector.push_back(p2dv);
	
	if (pv != NULL) pv->PlottingViewAdded(plotting_view_vector.back());
	
	return p2dv;
}

rcp_view * project::AddReactionCoordinatePlotView(i32s ud1, const char * tit, const char * s1, const char * sv, bool detached)
{
	rcp_view * rcpv = graphics_factory->ProduceRCPView(this, ud1, tit, s1, sv, detached);
	plotting_view_vector.push_back(rcpv);
	
	if (pv != NULL) pv->PlottingViewAdded(plotting_view_vector.back());
	
	return rcpv;
}

eld_view * project::AddEnergyLevelDiagramView(bool detached)
{
	eld_view * eldv = graphics_factory->ProduceELDView(this, detached);
	plotting_view_vector.push_back(eldv);
	
	if (pv != NULL) pv->PlottingViewAdded(plotting_view_vector.back());
	
	return eldv;
}

bool project::RemovePlottingView(plotting_view * p1)
{
	i32s n1 = NOT_DEFINED;
	for (i32u n2 = 0;n2 < plotting_view_vector.size();n2++)
	{
		if (plotting_view_vector[n2] == p1) n1 = n2;
	}
	
	if (n1 == NOT_DEFINED)		// this should never happen...
	{
		cout << "WARNING: could not find the view at project::RemovePlottingView()." << endl;
		return false;
	}
	
	if (pv != NULL) pv->PlottingViewRemoved(plotting_view_vector[n1]);
	
	delete plotting_view_vector[n1];
	plotting_view_vector.erase(plotting_view_vector.begin() + n1);
	
	return true;
}

bool project::RemoveMapView(map_view * p1)
{
	i32s n1 = NOT_DEFINED;
	for (i32u n2 = 0;n2 < map_view_vector.size();n2++)
	{
		if (map_view_vector[n2] == p1) n1 = n2;
	}
	
	if (n1 == NOT_DEFINED)		// this should never happen...
	{
		cout << "WARNING: could not find the view at project::RemoveGDIplusView()." << endl;
		return false;
	}
	
	if (pv != NULL) pv->MapViewRemoved(map_view_vector[n1]);
	
	delete map_view_vector[n1];
	map_view_vector.erase(map_view_vector.begin() + n1);
	
	return true;
}

void project::UpdateAllViews(bool flag)
{
//printf("project::UpdateAllViews(void)\n");
	UpdateAllGraphicsViews(flag);
	UpdateAllMapViews(flag);
}

void project::UpdateAllWindowTitles(void)	// is still needed in attach/detach stuff...
{
        char buffer[1024];

	for (i32u n1 = 0;n1 < camera_vector.size();n1++)
	{
		for (i32u n2 = 0;n2 < graphics_view_vector.size();n2++)
		{
			if (graphics_view_vector[n2]->cam != camera_vector[n1]) continue;
			
			ostrstream str(buffer, sizeof(buffer));
			str << "camera #" << camera_vector[n1]->my_c_number << " view #" << graphics_view_vector[n2]->my_gv_number << ends;
			graphics_view_vector[n2]->SetTitle(buffer);
		}
	}
	
	if (pv != NULL) pv->UpdateAllWindowTitles();
}

void project::UpdateAllGraphicsViews(bool flag)
{
	for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
	{
		graphics_view_vector[n1]->Update(flag);
	}
}

void project::UpdateAllMapViews(bool flag)
{
	for (i32u n1 = 0;n1 < map_view_vector.size();n1++)
	{
		map_view_vector[n1]->Update(flag);
	}
}

void project::UpdateAllMapExtremums()
{
	for (i32u n1 = 0;n1 < map_view_vector.size();n1++)
	{
		map_view_vector[n1]->UpdateExtremums();
	}
}

void project::UpdateGraphicsViews(camera * cam, bool flag)
{
	for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
	{
		if (graphics_view_vector[n1]->cam != cam) continue;
		graphics_view_vector[n1]->Update(flag);
	}
}

void project::UpdateGraphicsView(graphics_view * gv, bool flag)
{
	gv->Update(flag);
}

void project::UpdatePlottingViews(void)
{
	for (i32u n1 = 0;n1 < plotting_view_vector.size();n1++)
	{
	// energy-level diagrams might require scaling here?!?!?!
	// detect them and call the scaling function... ANY BETTER WAY TO DO THIS???
		eld_view * eldv = dynamic_cast<eld_view *>(plotting_view_vector[n1]);
		if (eldv != NULL) eldv->SetCenterAndScale();
		
		plotting_view_vector[n1]->Update();
	}
}

void project::RenderAllTPs(graphics_view * gv, rmode)
{
	// here we will render those transparent primitives...
	// all models should call this before returning from their versions!!!
	
	// first we must update the distances for all TP's, and sort them...
	
	const fGL * ref1 = gv->cam->GetLocData()->crd;
	const fGL * ref2 = gv->cam->GetLocData()->zdir.data;
	
	i32u n1;
	for (/*i32u*/ n1 = 0;n1 < tp_vector.size();n1++)
	{
		tp_vector[n1].UpdateDistance(ref1, ref2);
	}
	
	sort(tp_vector.begin(), tp_vector.end());
	
	// and then we will just render them...
	// it looks better if we disable depth buffer changes...
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false); glEnable(GL_BLEND);
	
	for (/*i32u*/ n1 = 0;n1 < tp_vector.size();n1++)
	{
		tp_vector[n1].GetData()->Render();
	}
	
	glDisable(GL_BLEND); glDepthMask(true);
}

void Print_Name_ID_Layer(Object * pOb, WPARAM, LPARAM, void * )
{
	if (pOb)
	{
		fprintf(stdout,"object(\"%s\") name = %s ID = %d LayerID = %d bChecked = %d\n",
			Object::ObjectTypeToString(pOb->GetObjectType()), 
			pOb->GetName().c_str(),
			pOb->GetUserID(),
			//pOb->GetLayer(), 
			pOb->GetLayerID(), 
			pOb->GetLayer() == NULL ? -2 : pOb->GetLayer()->bChecked
			);
	}
}
/*##############################################*/
/*##############################################*/
extern long g_FindMeanPCK_id_method;
void project::ProcessCommandString(graphics_view * gv, const char * command)
{
	char mbuff1[512];
	ostrstream str1(mbuff1, sizeof(mbuff1));
	str1 << "Processing Command : " << command << endl << ends;
	PrintToLog(mbuff1);
	
	istrstream istr(command);
	char kw1[32]; istr >> kw1;	// the 1st keyword.
	if (!strcmp("point_size", kw1))
	{
		char kw3[32]; istr >> kw3;
		printf("%s\n", kw3);
		bool redraw = false;

		if (strlen(kw3) > 0)
		{
			ThePoint3D::point_size = atof(kw3);
			redraw = true;
		}

		printf("ThePoint3D::point_size = %f\n", 
			ThePoint3D::point_size);


		if (redraw)
		{
			this->Draw();
			this->UpdateAllViews();
		}
		return;

	}


	if (!strcmp("bln_plane", kw1))
	{
		char kw3[32]; istr >> kw3;
		char kw4[32]; istr >> kw4;
		char kw5[32]; istr >> kw5;
		char kw6[32]; istr >> kw6;
		char kw7[32]; istr >> kw7;
		char kw8[32]; istr >> kw8;
		char kw9[32]; istr >> kw9;
		char kwA[32]; istr >> kwA;

		printf("%s\n", kw3);
		printf("%s\n", kw4);
		printf("%s\n", kw5);
		printf("%s\n", kw6);
		printf("%s\n", kw7);
		printf("%s\n", kw8);
		printf("%s\n", kw9);
		printf("%s\n", kwA);


		bool redraw = false;

		if (
			strlen(kw3) > 0 &&
			strlen(kw4) > 0 &&
			strlen(kw5) > 0 &&
			strlen(kw6) > 0 &&
			strlen(kw7) > 0 &&
			strlen(kw8) > 0 &&
			strlen(kw9) > 0
			)
		{
//			BlnProfilePlane3D::noth_vertical_coordinate_priorirty = atoi(kw3);
			BlnProfilePlane3D::first_x	= atof(kw4);
			BlnProfilePlane3D::step_x	= atof(kw5);

			BlnProfilePlane3D::first_y	= atof(kw6);
			BlnProfilePlane3D::step_y	= atof(kw7); 

			BlnProfilePlane3D::first_z	= atof(kw8);
			BlnProfilePlane3D::step_z	= atof(kw9); 

			redraw = true;
		}
		else
		{
			if (
				strlen(kw3) > 0 &&
				strlen(kw4) == 0 &&
				strlen(kw5) == 0 &&
				strlen(kw6) == 0 &&
				strlen(kw7) == 0 &&
				strlen(kw8) == 0 &&
				strlen(kw9) == 0 &&
				strlen(kwA) == 0 )
			{
				BlnProfilePlane3D::use_grid_on_plane = atoi(kw3);
				redraw = true;
			}
			else
			{
				printf("Using command \"bln_plane\" :\n");
				printf("\n");
				printf("if command \"bln_plane\" have 7 arguments:\n");
				printf("bln_plane [noth_vertical_coordinate_priorirty 0/1]\n");
				printf("[first_x] [step_x] [first_y] [step_y] [first_z] [step_z]\n");
				printf("\n");
				printf("if command \"bln_plane\" have 1 argument:\n");
				printf("bln_plane [use_grid_on plane 0/1]\n");
				printf("\n");
			}
		}

		printf("BlnProfilePlane3D::use_grid_on_plane  = %d\n", 
			BlnProfilePlane3D::use_grid_on_plane);

//		printf("BlnProfilePlane3D::noth_vertical_coordinate_priorirty  = %d\n", 
//			BlnProfilePlane3D::noth_vertical_coordinate_priorirty);
		printf("BlnProfilePlane3D::first_x  = %f\n", BlnProfilePlane3D::first_x);
		printf("BlnProfilePlane3D::step_x  = %f\n",  BlnProfilePlane3D::step_x);

		printf("BlnProfilePlane3D::first_y  = %f\n", BlnProfilePlane3D::first_y);
		printf("BlnProfilePlane3D::step_y  = %f\n",  BlnProfilePlane3D::step_y);

		printf("BlnProfilePlane3D::first_z  = %f\n", BlnProfilePlane3D::first_z);
		printf("BlnProfilePlane3D::step_z  = %f\n",  BlnProfilePlane3D::step_z);

		if (redraw)
		{
			if(this->m_bln_profiles.SetCurrentMsgOnFirst())
			{
				do
				{
					this->m_bln_profiles.GetCurrentMsg().m_plane.ReDraw();
				}
				while(this->m_bln_profiles.IncrementCurrentMsg());
			}
			this->UpdateAllViews();
		}
		return;

	}

	
	if (!strcmp("well", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; type of the object to add.
		if (strlen(kw2) != 0)
		{
			Well_3D::s_sloj_number_to_save = atoi(kw2);
		}

		printf("Well_3D::s_sloj_number_to_save = %d\n", Well_3D::s_sloj_number_to_save);
		if (this->m_drills.SetCurrentMsgOnFirst())
		{
			do
			{
				int i = Well_3D::s_sloj_number_to_save;
				if (i >=0 && i < (int)this->m_drills.GetCurrentMsg().GetPointsNumber())
				{
					CPoint3 pt			= this->m_drills.GetCurrentMsg().GetDocumentPoint(i);
					COLORREF color		= this->m_drills.GetCurrentMsg().GetColor(i);
					string sloj_name	= this->m_drills.GetCurrentMsg().GetSlojName(i);
					string well_id		= this->m_drills.GetCurrentMsg().GetWellID();
                    
					if (pt.bVisible)
						printf("%s\t%s\t[%lf, %lf, %lf] color = %d\n", 
						well_id.c_str(), 
						sloj_name.c_str(),
						pt.x, 
						pt.y, 
						pt.z, color);
				}

				this->m_drills.GetCurrentMsg().ReDraw();
			}
			while (this->m_drills.IncrementCurrentMsg());
		}
		this->UpdateAllViews();
		return;
	}

	if (!strcmp("enum", kw1))
	{
		this->EnumObjects(0, 0, 0, 
			&Object::ReturnTrue,
			Print_Name_ID_Layer);

		return;
	}



	if (!strcmp("lights", kw1))
	{
e_lights:
		for (i32u n1 = 0;n1 < this->light_vector.size();n1++)
		{
			printf("light %d number %d owner %x \n",
				n1, this->light_vector[n1]->number,  this->light_vector[n1]->owner);
			const obj_loc_data * ol = this->light_vector[n1]->GetLocData();
			printf("crd[%f %f %f %f] lock_count = %d\n"
				"ydir[%f %f %f] zdir[%f %f %f]\n\n",	
				ol->crd[0],
				ol->crd[1],
				ol->crd[2],
				ol->crd[3],
				ol->lock_count,
				ol->ydir.operator [](0),
				ol->ydir.operator [](1),
				ol->ydir.operator [](2),
				ol->zdir.operator [](0),
				ol->zdir.operator [](1),
				ol->zdir.operator [](2)
				);
			
			
		}

		return;
	}

	if (!strcmp("light", kw1))
	{
		char kw2[32]; istr >> kw2;	
		int i = atoi(kw2);
		if (i < 0 || i >= this->light_vector.size())
			return;

		obj_loc_data * ol = const_cast<obj_loc_data *>(this->light_vector[i]->GetLocData());

		char kw3[32]; istr >> kw3;
		char kw4[32]; istr >> kw4;
		int j = atoi(kw4);

		char kw5[32]; istr >> kw5;
		float v = atof(kw5);

		if (!strcmp("c", kw3))
		{
			if (j < 0 || j >= 4)
				return;

			ol->crd[j] = v;
		}

		if (!strcmp("y", kw3))
		{
			if (j < 0 || j >= 3)
				return;

			ol->ydir[j] = v;
		}

		if (!strcmp("z", kw3))
		{
			if (j < 0 || j >= 3)
				return;

			ol->zdir[j] = v;

		}
		for (i32u n1 = 0;n1 < graphics_view_vector.size();n1++)
		{
			SetupLights(graphics_view_vector[n1]->cam);
		}
		UpdateAllGraphicsViews();

		goto e_lights;


		return;
	}

	if (!strcmp("layers", kw1))
	{
		printf("LayersNames\n");
		printf("%s bChecked = %d\n", m_defaut_layer.GetName().c_str(), m_defaut_layer.bChecked);

		for (map<int, Layer>::iterator i_layer = m_layers.begin(); i_layer != m_layers.end(); i_layer++)
		{
			printf("%s bChecked = %d\n", i_layer->second.GetName().c_str(), i_layer->second.bChecked);
		}

		return;
	}
	if (!strcmp("N_quad", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; type of the object to add.
		int i = atoi(kw2);
		if (i>0)
			Surface3D::s_N_quad = i;
		printf("Surface3D::s_N_quad = %u\n", Surface3D::s_N_quad);
		return;
	}

	if (!strcmp("pck", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; type of the object to add.
		g_FindMeanPCK_id_method = atoi(kw2);	
		
		printf("g_FindMeanPCK_id_method = %d\n", g_FindMeanPCK_id_method);
		return;
	}

	if (!strcmp("blank", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; type of the object to add.
		int i = atoi(kw2);
		
		Surface3D::s_do_not_build_blank_polygones_on_continue_lines = bool(i);
		
		printf("Surface3D::s_do_not_build_blank_polygones_on_continue_lines = %u\n", Surface3D::s_do_not_build_blank_polygones_on_continue_lines);
		return;
	}

	if (!strcmp("help", kw1))
	{
		PrintToLog("> AVAILABLE COMMANDS:\n");		// use alphabetical order???

		PrintToLog("> help -- print all available commands in command strings.\n");
		
		PrintToLog("> add light (local/global) (directional/spotlight) -- add a new light object.\n");

		PrintToLog("> lights -- print all lights.\n");

		PrintToLog("> saveas <filename> -- save as *.gsf document\n");

		PrintToLog("> enum -- print all objects.\n");

		PrintToLog("> layers -- print all layers.\n");
		
		PrintToLog("> well (sloj number to save) -- sets sloj number of wells to save as dat file.\n");
		
		PrintToLog("> N_quad (interpolated points number) -- sets (or gets if second parametr is dismiss) points number for quad interpolation in the Cut command.\n");
		
		PrintToLog("> pck (id_method) -- sets g_FindMeanPCK_id_method\n");
		
		PrintToLog("> blank (0 or 1) -- sets value of Surface3D::s_do_not_build_blank_polygones_on_continue_lines.\n");
		
		PrintToLog("> bln_plane - set grid on BlnBrokenPlane. For help print this command without any arguments\n");
		
		PrintToLog("> point_size - set size of points. \n");

		

		
		return;
	}

	if (!strcmp("saveas", kw1))
	{
		char filename[4096]; istr >> filename;	// the 2nd keyword; filename.
		if ((dynamic_cast<SurfDoc*>(this))->SaveFile(filename, 4096, filename))
		{
		}
		return;
	}
	if (!strcmp("add", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; type of the object to add.
		char object_name[128];
		
		if (!strcmp("light", kw2))
		{
			char kw3[32]; istr >> kw3;
			char kw4[32]; istr >> kw4;
			
			bool is_local = true;
			if (kw3[0] == 'g') is_local = false;
			
			bool is_directional = true;
			if (kw4[0] == 's') is_directional = false;
			
			light * new_light;
			if (is_directional) new_light = new directional_light(ol_static(), GetNewObjectID());
			else
			{
				new_light = new spot_light(ol_static(), GetNewObjectID());
				
				const fGL trans[3] = { 0.0, 0.0, -1.0 };
				new_light->TranslateObject((const fGL *) trans, gv->cam->GetLocData());
			}
			
			if (!is_local) AddGlobalLight(new_light);
			else AddLocalLight(new_light, gv->cam);
			
			if (!is_local || graphics_view::draw_info) UpdateAllGraphicsViews();
			else if (is_local) UpdateGraphicsViews(gv->cam);
			
			ostrstream strR(mbuff1, sizeof(mbuff1));
			strR << "Added a new object : light (";
			strR << (is_local ? "local" : "global") << " ";
			strR << (is_directional ? "directional" : "spotlight") << ")." << endl << ends;
			PrintToLog(mbuff1);
			return;
		}
		
		PrintToLog("ERROR : could not process a command : \"add\".\n");
		return;
	}


#if 0
	if (!strcmp("help", kw1))
	{
		PrintToLog("> AVAILABLE COMMANDS:\n");		// use alphabetical order???
		
		PrintToLog("> add light (local/global) (directional/spotlight) -- add a new light object.\n");
		
		PrintToLog("> add plane <vf> <cf> <cscale1> <AUTO/cscale2> <dim> <res> <tp> <alpha> -- add a plane object.\n");
		PrintToLog(">   where: <vf> = value function : esp vdws eldens mo mod unity\n");
		PrintToLog(">          <cf> = colour function : red green blue rb1 rb2\n");
		PrintToLog(">          <cscale1> = scaling value for calculating the colours\n");
		PrintToLog(">          <cscale2> = scaling offset for calculating the colours\n");
		PrintToLog(">          <dim> = dimension of the plane object (in nm units)\n");
		PrintToLog(">          <res> = resolution of the plane object\n");
		PrintToLog(">          <tp> = 0 or 1 telling if the object is transparent\n");
		PrintToLog(">          <alpha> = transparency alpha value\n");
		
		PrintToLog("> add volrend <vf> <cf> <cscale1> <AUTO/cscale2> <dim> <res> <alpha> -- add a volume-rendering object.\n");
		PrintToLog(">   where: <vf> = value function : esp vdws eldens mo mod unity\n");
		PrintToLog(">          <cf> = colour function : red green blue rb1 rb2\n");
		PrintToLog(">          <cscale1> = scaling value for calculating the colours\n");
		PrintToLog(">          <cscale2> = scaling offset for calculating the colours\n");
		PrintToLog(">          <dim> = dimension of the plane object (in nm units)\n");
		PrintToLog(">          <res> = resolution of the plane object\n");
		PrintToLog(">          <alpha> = transparency alpha value\n");
		
		PrintToLog("> add surf1 <vf1> <vf2> <cf> <sscale> <cscale1> <AUTO/cscale2> <dim> <res> <solid> <tp> <alpha> -- add a single surface object.\n");
		PrintToLog(">   where: <vf1> = value function for calculating the surface : esp vdws eldens mo mod unity\n");
		PrintToLog(">          <vf2> = value function for calculating the colours : esp vdws eldens mo mod unity\n");
		PrintToLog(">          <cf> = colour function : red green blue rb1 rb2\n");
		PrintToLog(">          <sscale> = scaling value for calculating the surface\n");
		PrintToLog(">          <cscale1> = scaling value for calculating the colours\n");
		PrintToLog(">          <cscale2> = scaling offset for calculating the colours\n");
		PrintToLog(">          <dim> = dimension of the plane object (in nm units)\n");
		PrintToLog(">          <res> = resolution of the plane object\n");
		PrintToLog(">          <solid> = 0 or 1 telling if the object is solid\n");
		PrintToLog(">          <tp> = 0 or 1 telling if the object is transparent\n");
		PrintToLog(">          <alpha> = transparency alpha value\n");
		
		PrintToLog("> add surf2 <vf1> <vf2> <cf1> <cf2> <sscale1> <sscale2> <cscale1> <AUTO/cscale2> <dim> <res> <solid> <tp> <alpha> -- add a pair of surface objects.\n");
		PrintToLog(">   where: <vf1> = value function for calculating the surface : esp vdws eldens mo mod unity\n");
		PrintToLog(">          <vf2> = value function for calculating the colours : esp vdws eldens mo mod unity\n");
		PrintToLog(">          <cf1> = colour function for 1st surface : red green blue rb1 rb2\n");
		PrintToLog(">          <cf2> = colour function for 2nd surface : red green blue rb1 rb2\n");
		PrintToLog(">          <sscale1> = scaling value for calculating the surface for 1st surface\n");
		PrintToLog(">          <sscale2> = scaling value for calculating the surface for 2nd surface\n");
		PrintToLog(">          <cscale1> = scaling value for calculating the colours\n");
		PrintToLog(">          <cscale2> = scaling offset for calculating the colours\n");
		PrintToLog(">          <dim> = dimension of the plane object (in nm units)\n");
		PrintToLog(">          <res> = resolution of the plane object\n");
		PrintToLog(">          <solid> = 0 or 1 telling if the object is solid\n");
		PrintToLog(">          <tp> = 0 or 1 telling if the object is transparent\n");
		PrintToLog(">          <alpha> = transparency alpha value\n");
		
		PrintToLog("> help -- print all available commands in command strings.\n");
		
		PrintToLog("> energy -- calculate a single-point energy.\n");
		PrintToLog("> geom_opt -- do a geometry optimization run using default options.\n");
		PrintToLog("> mol_dyn -- do a molecular dynamics run using default options.\n");
		
		PrintToLog("> random_search <cycles> <optsteps> -- perform a random conformational search.\n");
		PrintToLog("> systematic_search <divisions> <optsteps> -- perform a systematic conformational search.\n");
		PrintToLog("> montecarlo_search <init_cycles> <simul_cycles> <optsteps> -- perform a MonteCarlo search.\n");
		
		PrintToLog("> make_plot1 A B C D <div> <start_ang> <end_ang> <optsteps> -- create a 1D energy vs. torsion plot.\n");
		PrintToLog("> make_plot2 A B C D <div> <start_ang> <end_ang> I J K L <div> <start_ang> <end_ang> <optsteps> -- create a 2D energy vs. torsions plot.\n");
		
		PrintToLog("> population_analysis_ESP -- determine atomic charges using an ESP fit (for QM methods only).\n");
		
		PrintToLog("> transition_state_search <delta_e> <initial_fc> -- perform a transition state search (for QM methods only).\n");
		PrintToLog("> stationary_state_search <steps> -- perform a search for a structure with no forces.\n");
		
		PrintToLog("> set_current_orbital <orbital_index> -- set the current orbtal index for plotting the orbitals.\n");

		PrintToLog("> build_amino <sequence> (helix/strand) -- amino acid sequence builder.\n");
		PrintToLog("> build_nucleic <sequence> -- nucleic acid sequence builder.\n");
		
		PrintToLog("> solvate_box <x-dim> <y-dim> <z-dim> (<density> <filename> (export)) -- setup a solvation box ; UNDER_CONSTRUCTION.\n");
		PrintToLog("> solvate_sphere <rad_solute> <rad_solvent> (<density> <filename>) -- setup a solvation sphere.\n");
		
		PrintToLog("> set_formal_charge <index> <charge> -- set formal charges to atoms.\n");
		
		PrintToLog("> evaluate_Bfact -- evaluate B-factors for selected atoms (a trajectory file must be open).\n");
		PrintToLog("> evaluate_diffconst <dt> -- evaluate diffusion constants for selected atoms (a trajectory file must be open, dt = time difference between frames [fs]).\n");
		
		return;
	}
	
	if (!strcmp("add", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; type of the object to add.
		char object_name[128];
		
		if (!strcmp("light", kw2))
		{
			char kw3[32]; istr >> kw3;
			char kw4[32]; istr >> kw4;
			
			bool is_local = true;
			if (kw3[0] == 'g') is_local = false;
			
			bool is_directional = true;
			if (kw4[0] == 's') is_directional = false;
			
			light * new_light;
			if (is_directional) new_light = new directional_light(ol_static(), GetNewObjectID());
			else
			{
				new_light = new spot_light(ol_static(), GetNewObjectID());
				
				const fGL trans[3] = { 0.0, 0.0, -1.0 };
				new_light->TranslateObject((const fGL *) trans, gv->cam->GetLocData());
			}
			
			if (!is_local) AddGlobalLight(new_light);
			else AddLocalLight(new_light, gv->cam);
			
			if (!is_local || graphics_view::draw_info) UpdateAllGraphicsViews();
			else if (is_local) UpdateGraphicsViews(gv->cam);
			
			ostrstream strR(mbuff1, sizeof(mbuff1));
			strR << "Added a new object : light (";
			strR << (is_local ? "local" : "global") << " ";
			strR << (is_directional ? "directional" : "spotlight") << ")." << endl << ends;
			PrintToLog(mbuff1);
			return;
		}
		
		if (!strcmp("plane", kw2))
		{
			char kw3[32]; istr >> kw3;
			char kw4[32]; istr >> kw4;
			char kw5[32]; istr >> kw5;
			char kw6[32]; istr >> kw6;
			char kw7[32]; istr >> kw7;
			char kw8[32]; istr >> kw8;
			char kw9[32]; istr >> kw9;
			char kwA[32]; istr >> kwA;
			char ** endptr = NULL;
			
			cp_param cpp;
			cpp.prj = this; 
			
			//cpp.ref = GetCurrentSetup()->GetCurrentEngine();
			
			if (!strcmp(kw3, "esp")) cpp.vf = (ValueFunction *) value_ESP;
			else if (!strcmp(kw3, "vdws")) cpp.vf = (ValueFunction *) value_VDWSurf;
			else if (!strcmp(kw3, "eldens")) cpp.vf = (ValueFunction *) value_ElDens;
			else if (!strcmp(kw3, "mo")) cpp.vf = (ValueFunction *) value_Orbital;
			else if (!strcmp(kw3, "mod")) cpp.vf = (ValueFunction *) value_OrbDens;
			else if (!strcmp(kw3, "unity")) cpp.vf = (ValueFunction *) GetUnity;
			else { PrintToLog("ERROR : add plane : unknown value function.\n"); return; }
			
			if (!strcmp(kw4, "red")) cpp.cf = (ColorFunction *) GetRedColor;
			else if (!strcmp(kw4, "green")) cpp.cf = (ColorFunction *) GetGreenColor;
			else if (!strcmp(kw4, "blue")) cpp.cf = (ColorFunction *) GetBlueColor;
			else if (!strcmp(kw4, "rb1")) cpp.cf = (ColorFunction *) GetRBRange1;
			else if (!strcmp(kw4, "rb2")) cpp.cf = (ColorFunction *) GetRBRange2;
			else { PrintToLog("ERROR : add plane : unknown colour function.\n"); return; }
			
			f64 cscale1 = strtod(kw5, endptr);
			
			f64 cscale2 = 0.0; bool auto_cv2 = false;
			if (!strcmp(kw6, "AUTO")) auto_cv2 = true;
			else cscale2 = strtod(kw6, endptr);
			
			f64 dim = strtod(kw7, endptr);
			
			i32s res = strtol(kw8, endptr, 10);
			if (res < 2) res = 2;
			
			i32s tp = strtol(kw9, endptr, 10);
			if (tp < 0) tp = 0; if (tp > 1) tp = 1;
			
			f64 alpha = strtod(kwA, endptr);
			
			cpp.dim = dim; cpp.np = res;
			cpp.transparent = tp; cpp.automatic_cv2 = auto_cv2;
			
			cpp.cvalue1 = cscale1;
			cpp.cvalue2 = cscale2;
			cpp.alpha = alpha;
			
			ostrstream strN(object_name, sizeof(object_name));
			strN << kw3 << "-" << ends;
			
			AddObject(new color_plane_object(ol_static(), cpp, object_name));
			UpdateAllGraphicsViews();
			
			ostrstream strR(mbuff1, sizeof(mbuff1));
			strR << "Added a new object : plane (" << kw3 << " " << kw4 << ")." << endl << ends;
			PrintToLog(mbuff1);
			return;
		}
		
		if (!strcmp("volrend", kw2))
		{
			char kw3[32]; istr >> kw3;
			char kw4[32]; istr >> kw4;
			char kw5[32]; istr >> kw5;
			char kw6[32]; istr >> kw6;
			char kw7[32]; istr >> kw7;
			char kw8[32]; istr >> kw8;
			char kw9[32]; istr >> kw9;
			char ** endptr = NULL;
			
			cp_param cpp;
			cpp.prj = this; cpp.ref = GetCurrentSetup()->GetCurrentEngine();
			
			if (!strcmp(kw3, "esp")) cpp.vf = (ValueFunction *) value_ESP;
			else if (!strcmp(kw3, "vdws")) cpp.vf = (ValueFunction *) value_VDWSurf;
			else if (!strcmp(kw3, "eldens")) cpp.vf = (ValueFunction *) value_ElDens;
			else if (!strcmp(kw3, "mo")) cpp.vf = (ValueFunction *) value_Orbital;
			else if (!strcmp(kw3, "mod")) cpp.vf = (ValueFunction *) value_OrbDens;
			else if (!strcmp(kw3, "unity")) cpp.vf = (ValueFunction *) GetUnity;
			else { PrintToLog("ERROR : add volrend : unknown value function.\n"); return; }
			
			if (!strcmp(kw4, "red")) cpp.cf = (ColorFunction *) GetRedColor;
			else if (!strcmp(kw4, "green")) cpp.cf = (ColorFunction *) GetGreenColor;
			else if (!strcmp(kw4, "blue")) cpp.cf = (ColorFunction *) GetBlueColor;
			else if (!strcmp(kw4, "rb1")) cpp.cf = (ColorFunction *) GetRBRange1;
			else if (!strcmp(kw4, "rb2")) cpp.cf = (ColorFunction *) GetRBRange2;
			else { PrintToLog("ERROR : add volrend : unknown colour function.\n"); return; }
			
			f64 cscale1 = strtod(kw5, endptr);
			
			f64 cscale2 = 0.0; bool auto_cv2 = false;
			if (!strcmp(kw6, "AUTO")) auto_cv2 = true;
			else cscale2 = strtod(kw6, endptr);
			
			f64 dim = strtod(kw7, endptr);
			
			i32s res = strtol(kw8, endptr, 10);
			if (res < 4) res = 4;
			
			f64 alpha = strtod(kw9, endptr);
			
			cpp.dim = dim; cpp.np = res;
			cpp.transparent = true; cpp.automatic_cv2 = auto_cv2;
			
			cpp.cvalue1 = cscale1;
			cpp.cvalue2 = cscale2;
			cpp.alpha = alpha;
			
			ostrstream strN(object_name, sizeof(object_name));
			strN << kw3 << "-" << ends;
			
			AddObject(new volume_rendering_object(ol_static(), cpp, res / 2, dim / 2.0, (* gv->cam), object_name));
			UpdateAllGraphicsViews();
			
			ostrstream strR(mbuff1, sizeof(mbuff1));
			strR << "Added a new object : volrend (" << kw3 << " " << kw4 << ")." << endl << ends;
			PrintToLog(mbuff1);
			return;
		}
		
		if (!strcmp("surf1", kw2))
		{
			char kw3[32]; istr >> kw3;	// vf1
			char kw4[32]; istr >> kw4;	// vf2
			char kw5[32]; istr >> kw5;	// cf
			char kw6[32]; istr >> kw6;	// sscale
			char kw7[32]; istr >> kw7;	// cscale1
			char kw8[32]; istr >> kw8;	// AUTO/cscale2
			char kw9[32]; istr >> kw9;	// dim
			char kwA[32]; istr >> kwA;	// res
			char kwB[32]; istr >> kwB;	// solid
			char kwC[32]; istr >> kwC;	// tp
			char kwD[32]; istr >> kwD;	// alpha
			char ** endptr = NULL;
			
			cs_param csp1;

			csp1.prj = this; csp1.ref = GetCurrentSetup()->GetCurrentEngine(); csp1.next = NULL;
			
			if (!strcmp(kw3, "esp")) csp1.vf1 = (ValueFunction *) value_ESP;
			else if (!strcmp(kw3, "vdws")) csp1.vf1 = (ValueFunction *) value_VDWSurf;
			else if (!strcmp(kw3, "eldens")) csp1.vf1 = (ValueFunction *) value_ElDens;
			else if (!strcmp(kw3, "mo")) csp1.vf1 = (ValueFunction *) value_Orbital;
			else if (!strcmp(kw3, "mod")) csp1.vf1 = (ValueFunction *) value_OrbDens;
			else if (!strcmp(kw3, "unity")) csp1.vf1 = (ValueFunction *) GetUnity;
			else { PrintToLog("ERROR : add surf1 : unknown value function 1.\n"); return; }
			
			if (!strcmp(kw4, "esp")) csp1.vf2 = (ValueFunction *) value_ESP;
			else if (!strcmp(kw4, "vdws")) csp1.vf2 = (ValueFunction *) value_VDWSurf;
			else if (!strcmp(kw4, "eldens")) csp1.vf2 = (ValueFunction *) value_ElDens;
			else if (!strcmp(kw4, "mo")) csp1.vf2 = (ValueFunction *) value_Orbital;
			else if (!strcmp(kw4, "mod")) csp1.vf2 = (ValueFunction *) value_OrbDens;
			else if (!strcmp(kw4, "unity")) csp1.vf2 = (ValueFunction *) GetUnity;
			else { PrintToLog("ERROR : add surf1 : unknown value function 2.\n"); return; }
			
			if (!strcmp(kw5, "red")) csp1.cf = (ColorFunction *) GetRedColor;
			else if (!strcmp(kw5, "green")) csp1.cf = (ColorFunction *) GetGreenColor;
			else if (!strcmp(kw5, "blue")) csp1.cf = (ColorFunction *) GetBlueColor;
			else if (!strcmp(kw5, "rb1")) csp1.cf = (ColorFunction *) GetRBRange1;
			else if (!strcmp(kw5, "rb2")) csp1.cf = (ColorFunction *) GetRBRange2;
			else { PrintToLog("ERROR : add surf1 : unknown colour function.\n"); return; }
			
			f64 sscale = strtod(kw6, endptr);
			f64 cscale1 = strtod(kw7, endptr);
			
			f64 cscale2 = 0.0; bool auto_cv2 = false;
			if (!strcmp(kw8, "AUTO")) auto_cv2 = true;
			else cscale2 = strtod(kw8, endptr);
			
			f64 dim = strtod(kw9, endptr);
			
			i32s res = strtol(kwA, endptr, 10);
			if (res < 4) res = 4;
			
			i32s solid = strtol(kwB, endptr, 10);
			if (solid < 0) solid = 0; if (solid > 1) solid = 1;

			i32s tp = strtol(kwC, endptr, 10);
			if (tp < 0) tp = 0; if (tp > 1) tp = 1;
			
			f64 alpha = strtod(kwD, endptr);
			
			static fGL dim_arr[3];
			dim_arr[0] = dim_arr[1] = dim_arr[2] = dim;
			
			static i32s res_arr[3];
			res_arr[0] = res_arr[1] = res_arr[2] = res;
			
			csp1.dim = dim_arr; csp1.np = res_arr;
			csp1.transparent = tp; csp1.automatic_cv2 = auto_cv2; csp1.wireframe = !solid;
			
			csp1.svalue = sscale;
			csp1.cvalue1 = cscale1;
			csp1.cvalue2 = cscale2;
			csp1.alpha = alpha;
			
			csp1.toler = fabs(1.0e-6 * sscale); csp1.maxc = 250;
			
			ostrstream strN(object_name, sizeof(object_name));
			strN << kw3 << "-" << kw4 << "-" << ends;
			
			AddObject(new color_surface_object(ol_static(), csp1, object_name));
			UpdateAllGraphicsViews();
			
			ostrstream strR(mbuff1, sizeof(mbuff1));
			strR << "Added a new object : surf1 (" << kw3 << " " << kw4 << " " << kw5 << ")." << endl << ends;
			PrintToLog(mbuff1);
			return;
		}
		
		if (!strcmp("surf2", kw2))
		{
			char kw3[32]; istr >> kw3;	// vf1
			char kw4[32]; istr >> kw4;	// vf2
			char kw5[32]; istr >> kw5;	// cf1
			char kw6[32]; istr >> kw6;	// cf2
			char kw7[32]; istr >> kw7;	// sscale1
			char kw8[32]; istr >> kw8;	// sscale2
			char kw9[32]; istr >> kw9;	// cscale1
			char kwA[32]; istr >> kwA;	// AUTO/cscale2
			char kwB[32]; istr >> kwB;	// dim
			char kwC[32]; istr >> kwC;	// res
			char kwD[32]; istr >> kwD;	// solid
			char kwE[32]; istr >> kwE;	// tp
			char kwF[32]; istr >> kwF;	// alpha
			char ** endptr = NULL;
			
			cs_param csp2a; cs_param csp2b;
			
			csp2a.prj = this; csp2a.ref = GetCurrentSetup()->GetCurrentEngine(); csp2a.next = & csp2b;

			csp2b.prj = this; csp2b.ref = GetCurrentSetup()->GetCurrentEngine(); csp2b.next = NULL;
			
			if (!strcmp(kw3, "esp")) csp2a.vf1 = csp2b.vf1 = (ValueFunction *) value_ESP;
			else if (!strcmp(kw3, "vdws")) csp2a.vf1 = csp2b.vf1 = (ValueFunction *) value_VDWSurf;
			else if (!strcmp(kw3, "eldens")) csp2a.vf1 = csp2b.vf1 = (ValueFunction *) value_ElDens;
			else if (!strcmp(kw3, "mo")) csp2a.vf1 = csp2b.vf1 = (ValueFunction *) value_Orbital;
			else if (!strcmp(kw3, "mod")) csp2a.vf1 = csp2b.vf1 = (ValueFunction *) value_OrbDens;
			else if (!strcmp(kw3, "unity")) csp2a.vf1 = csp2b.vf1 = (ValueFunction *) GetUnity;
			else { PrintToLog("ERROR : add surf2 : unknown value function 1.\n"); return; }
			
			if (!strcmp(kw4, "esp")) csp2a.vf2 = csp2b.vf2 = (ValueFunction *) value_ESP;
			else if (!strcmp(kw4, "vdws")) csp2a.vf2 = csp2b.vf2 = (ValueFunction *) value_VDWSurf;
			else if (!strcmp(kw4, "eldens")) csp2a.vf2 = csp2b.vf2 = (ValueFunction *) value_ElDens;
			else if (!strcmp(kw4, "mo")) csp2a.vf2 = csp2b.vf2 = (ValueFunction *) value_Orbital;
			else if (!strcmp(kw4, "mod")) csp2a.vf2 = csp2b.vf2 = (ValueFunction *) value_OrbDens;
			else if (!strcmp(kw4, "unity")) csp2a.vf2 = csp2b.vf2 = (ValueFunction *) GetUnity;
			else { PrintToLog("ERROR : add surf2 : unknown value function 2.\n"); return; }
			
			if (!strcmp(kw5, "red")) csp2a.cf = (ColorFunction *) GetRedColor;
			else if (!strcmp(kw5, "green")) csp2a.cf = (ColorFunction *) GetGreenColor;
			else if (!strcmp(kw5, "blue")) csp2a.cf = (ColorFunction *) GetBlueColor;
			else if (!strcmp(kw5, "rb1")) csp2a.cf = (ColorFunction *) GetRBRange1;
			else if (!strcmp(kw5, "rb2")) csp2a.cf = (ColorFunction *) GetRBRange2;
			else { PrintToLog("ERROR : add surf2 : unknown colour function 1.\n"); return; }
			
			if (!strcmp(kw6, "red")) csp2b.cf = (ColorFunction *) GetRedColor;
			else if (!strcmp(kw6, "green")) csp2b.cf = (ColorFunction *) GetGreenColor;
			else if (!strcmp(kw6, "blue")) csp2b.cf = (ColorFunction *) GetBlueColor;
			else if (!strcmp(kw6, "rb1")) csp2b.cf = (ColorFunction *) GetRBRange1;
			else if (!strcmp(kw6, "rb2")) csp2b.cf = (ColorFunction *) GetRBRange2;
			else { PrintToLog("ERROR : add surf2 : unknown colour function 2.\n"); return; }
			
			f64 sscale1 = strtod(kw7, endptr);
			f64 sscale2 = strtod(kw8, endptr);
			f64 cscale1 = strtod(kw9, endptr);
			
			f64 cscale2 = 0.0; bool auto_cv2 = false;
			if (!strcmp(kwA, "AUTO")) auto_cv2 = true;
			else cscale2 = strtod(kwA, endptr);
			
			f64 dim = strtod(kwB, endptr);
			
			i32s res = strtol(kwC, endptr, 10);
			if (res < 4) res = 4;
			
			i32s solid = strtol(kwD, endptr, 10);
			if (solid < 0) solid = 0; if (solid > 1) solid = 1;

			i32s tp = strtol(kwE, endptr, 10);
			if (tp < 0) tp = 0; if (tp > 1) tp = 1;
			
			f64 alpha = strtod(kwF, endptr);
			
			static fGL dim_arr[3];
			dim_arr[0] = dim_arr[1] = dim_arr[2] = dim;
			
			static i32s res_arr[3];
			res_arr[0] = res_arr[1] = res_arr[2] = res;
			
			csp2a.dim = dim_arr; csp2a.np = res_arr;
			csp2a.transparent = tp; csp2a.automatic_cv2 = auto_cv2; csp2a.wireframe = !solid;
			
			csp2a.svalue = sscale1;
			csp2a.cvalue1 = cscale1;
			csp2a.cvalue2 = cscale2;
			csp2a.alpha = alpha;
			
			csp2a.toler = fabs(1.0e-6 * sscale1); csp2a.maxc = 250;
			
			csp2b.dim = dim_arr; csp2b.np = res_arr;
			csp2b.transparent = tp; csp2b.automatic_cv2 = auto_cv2; csp2b.wireframe = !solid;
			
			csp2b.svalue = sscale2;
			csp2b.cvalue1 = cscale1;
			csp2b.cvalue2 = cscale2;
			csp2b.alpha = alpha;
			
			csp2b.toler = fabs(1.0e-6 * sscale2); csp2b.maxc = 250;
			
			ostrstream strN(object_name, sizeof(object_name));
			strN << kw3 << "-" << kw4 << "-" << ends;
			
			AddObject(new color_surface_object(ol_static(), csp2a, object_name));
			UpdateAllGraphicsViews();
			
			ostrstream strR(mbuff1, sizeof(mbuff1));
			strR << "Added a new object : surf2 (" << kw3 << " " << kw4 << " " << kw5 << " " << kw6 << ")." << endl << ends;
			PrintToLog(mbuff1);
			return;
		}
		
		PrintToLog("ERROR : could not process a command : \"add\".\n");
		return;
	}
	
	if (!strcmp("energy", kw1))
	{
		DoEnergy();
		return;
	}
	
	if (!strcmp("geom_opt", kw1))				// todo: how to set the options here?
	{
		setup * su = GetCurrentSetup();
		static jobinfo_GeomOpt ji;
		
		ji.prj = this;
		ji.go = geomopt_param(su);
		ji.go.show_dialog = false;
		
		start_job_GeomOpt(& ji);
		return;
	}
	
	if (!strcmp("mol_dyn", kw1))				// todo: how to set the options here?
	{
		setup * su = GetCurrentSetup();
		static jobinfo_MolDyn ji;
		
		ji.prj = this;
		ji.md = moldyn_param(su);
		ji.md.show_dialog = false;
		
		start_job_MolDyn(& ji);
		return;
	}
	
	if (!strcmp("random_search", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; cycles.
		char kw3[32]; istr >> kw3;	// the 3rd keyword; optsteps.
		
		static jobinfo_RandomSearch ji;
		char ** endptr = NULL;
		
		ji.prj = this;
		ji.cycles = strtol(kw2, endptr, 10);
		ji.optsteps = strtol(kw3, endptr, 10);
		
#ifdef ENABLE_THREADS
		
		CreateProgressDialog("Random Search", true, NOT_DEFINED, NOT_DEFINED);
		GThread * t = g_thread_create(pcs_job_RandomSearch, (gpointer) & ji, FALSE, NULL);
		if (t == NULL) { DestroyProgressDialog(); ErrorMessage("Thread failed!"); }
		
#else	// ENABLE_THREADS
		
//		pcs_job_RandomSearch((gpointer) & ji);
		pcs_job_RandomSearch((void*) & ji);
		
#endif	// ENABLE_THREADS
		
		return;
	}

	if (!strcmp("systematic_search", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; divisions.
		char kw3[32]; istr >> kw3;	// the 3rd keyword; optsteps.
		
		char ** endptr = NULL;
		i32s divisions = strtol(kw2, endptr, 10);
		i32s optsteps = strtol(kw3, endptr, 10);
		
		DoSystematicSearch(divisions, optsteps, true);
		return;
	}

	if (!strcmp("montecarlo_search", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; n_init_steps.
		char kw3[32]; istr >> kw3;	// the 3rd keyword; n_simul_steps.
		char kw4[32]; istr >> kw4;	// the 4th keyword; optsteps.
		
		char ** endptr = NULL;
		i32s n_init_steps = strtol(kw2, endptr, 10);
		i32s n_simul_steps = strtol(kw3, endptr, 10);
		i32s optsteps = strtol(kw4, endptr, 10);
		
		DoMonteCarloSearch(n_init_steps, n_simul_steps, optsteps, true);
		return;
	}
	
	if (!strcmp("make_plot1", kw1))
	{
		char kw2[32]; istr >> kw2;	// A
		char kw3[32]; istr >> kw3;	// B
		char kw4[32]; istr >> kw4;	// C
		char kw5[32]; istr >> kw5;	// D
		char kw6[32]; istr >> kw6;	// div
		char kw7[32]; istr >> kw7;	// start_ang
		char kw8[32]; istr >> kw8;	// end_ang
		char kw9[32]; istr >> kw9;	// optsteps
		char ** endptr = NULL;
		
		i32s ia = strtol(kw2, endptr, 10);
		i32s ib = strtol(kw3, endptr, 10);
		i32s ic = strtol(kw4, endptr, 10);
		i32s id = strtol(kw5, endptr, 10);
		i32s div1 = strtol(kw6, endptr, 10);
		fGL start1 = strtod(kw7, endptr);
		fGL end1 = strtod(kw8, endptr);
		
		i32s optsteps = strtol(kw9, endptr, 10);
		
		DoEnergyPlot1D(ia, ib, ic, id, div1, start1, end1, optsteps);
		return;
	}
	
	if (!strcmp("make_plot2", kw1))
	{
		char kw2[32]; istr >> kw2;	// A
		char kw3[32]; istr >> kw3;	// B
		char kw4[32]; istr >> kw4;	// C
		char kw5[32]; istr >> kw5;	// D
		char kw6[32]; istr >> kw6;	// div
		char kw7[32]; istr >> kw7;	// start_ang
		char kw8[32]; istr >> kw8;	// end_ang
		char kw9[32]; istr >> kw9;	// I
		char kwA[32]; istr >> kwA;	// J
		char kwB[32]; istr >> kwB;	// K
		char kwC[32]; istr >> kwC;	// L
		char kwD[32]; istr >> kwD;	// div
		char kwE[32]; istr >> kwE;	// start_ang
		char kwF[32]; istr >> kwF;	// end_ang
		char kwG[32]; istr >> kwG;	// optsteps
		char ** endptr = NULL;
		
		i32s ia = strtol(kw2, endptr, 10);
		i32s ib = strtol(kw3, endptr, 10);
		i32s ic = strtol(kw4, endptr, 10);
		i32s id = strtol(kw5, endptr, 10);
		i32s div1 = strtol(kw6, endptr, 10);
		fGL start1 = strtod(kw7, endptr);
		fGL end1 = strtod(kw8, endptr);
		
		i32s ii = strtol(kw9, endptr, 10);
		i32s ij = strtol(kwA, endptr, 10);
		i32s ik = strtol(kwB, endptr, 10);
		i32s il = strtol(kwC, endptr, 10);
		i32s div2 = strtol(kwD, endptr, 10);
		fGL start2 = strtod(kwE, endptr);
		fGL end2 = strtod(kwF, endptr);
		
		i32s optsteps = strtol(kwG, endptr, 10);
		
		DoEnergyPlot2D(ia, ib, ic, id, div1, start1, end1, ii, ij, ik, il, div2, start2, end2, optsteps);
		return;
	}
	
	if (!strcmp("population_analysis_ESP", kw1))
	{
		setup1_qm * suqm = dynamic_cast<setup1_qm *>(current_setup);
		if (suqm == NULL) Message("Sorry, this is for QM models only!");
		else
		{
			pop_ana_electrostatic pa(suqm);
			pa.DoPopAna();
			
			// how to set the charge labels on in graphics?
		}
		
		return;
	}
	
	if (!strcmp("transition_state_search", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; delta-E per step.
		char kw3[32]; istr >> kw3;	// the 3rd keyword; initial force constant.
		char ** endptr = NULL;
		
		fGL deltae = strtod(kw2, endptr);
		fGL initfc = strtod(kw3, endptr);
		
		DoTransitionStateSearch(deltae, initfc);
		return;
	}
	
	if (!strcmp("stationary_state_search", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; steps.
		char ** endptr = NULL;
		
		i32s steps = strtol(kw2, endptr, 10);
		
		DoStationaryStateSearch(steps);
		return;
	}
	
	if (!strcmp("set_current_orbital", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; the orbital index.
		
		char ** endptr = NULL;
		int index = strtol(kw2, endptr, 10);
		if (index < 0) index = 0;
		
		qm_current_orbital = index;
		
		ostrstream strR(mbuff1, sizeof(mbuff1));
		strR << "The current orbital is now " << qm_current_orbital << "." << endl << ends;
		PrintToLog(mbuff1);
		return;
	}
	
	if (!strcmp("build_amino", kw1))
	{
		char kw2[4096]; istr >> kw2;	// sequence
		char kw3[32]; istr >> kw3;	// helix/sheet (optional)
		
		f64 aab_ah[] = { 302.0 * M_PI / 180.0, 313.0 * M_PI / 180.0, M_PI };
		f64 aab_bs[] = { 180.0 * M_PI / 180.0, 180.0 * M_PI / 180.0, M_PI };
		
		model::amino_builder.Build(this, kw2, kw3[0] == 'h' || kw3[0] == 'H' ? aab_ah : aab_bs);
		UpdateAllGraphicsViews();
		
		ostrstream strR(mbuff1, sizeof(mbuff1));
		strR << "built a sequence : " << kw2 << endl << ends;
		PrintToLog(mbuff1);
		return;
	}
	
	if (!strcmp("build_nucleic", kw1))
	{
		char kw2[4096]; istr >> kw2;	// sequence
		
		f64 nab[] =
		{
			44.6 * M_PI / 180.0, 261.0 * M_PI / 180.0, 320.8 * M_PI / 180.0, 208.6 * M_PI / 180.0,
			273.8 * M_PI / 180.0, 105.6 * M_PI / 180.0, 356.0 * M_PI / 180.0, 24.7 * M_PI / 180.0,
			88.7 * M_PI / 180.0, 264.6 * M_PI / 180.0
		};
		
		model::nucleic_builder.Build(this, kw2, nab);
		UpdateAllGraphicsViews();
		
		ostrstream strR(mbuff1, sizeof(mbuff1));
		strR << "built a sequence : " << kw2 << endl << ends;
		PrintToLog(mbuff1);
		return;
	}
	
	if (!strcmp("solvate_box", kw1))
	{
		char kw2[32]; istr >> kw2;		// xdim
		char kw3[32]; istr >> kw3;		// ydim
		char kw4[32]; istr >> kw4;		// zdim
		char kw5[32] = ""; istr >> kw5;		// density (optional)
		char kw5_[32] = ""; istr >> kw5_;	// atom number (optional)
		char kw6[256] = ""; istr >> kw6;	// filename (optional)
		char kw7[64] = ""; istr >> kw7;		// export (optional)
		
		char ** endptr = NULL;
		fGL xdim = strtod(kw2, endptr);
		fGL ydim = strtod(kw3, endptr);
		fGL zdim = strtod(kw4, endptr);
		
		fGL density = 1.00; if (strlen(kw5) > 0) density = strtod(kw5, endptr);
		char * export_fn = NULL; if (!strcmp(kw7, "export")) export_fn = kw6;

		int element_number = 2; if (strlen(kw5_) > 0) element_number = atoi(kw5_);

		dummy_project * solvent = NULL;
		if (strlen(kw6) > 0)
		{
			solvent = new dummy_project(NULL);
			
			char fn[256];
			ostrstream fns(fn, sizeof(fn));
			fns << kw6 << ".gpr" << ends;
			
			ifstream ifile(fn, ios::in);
			ReadGPR(* solvent, ifile, false);
			ifile.close();
		}
		
		SolvateBox(xdim, ydim, zdim, density, element_number, solvent, export_fn);
		UpdateAllGraphicsViews();
		return;
	}
	
	if (!strcmp("solvate_sphere", kw1))
	{
		char kw2[32]; istr >> kw2;		// rad_solute
		char kw3[32]; istr >> kw3;		// rad_solvent
		char kw4[32] = ""; istr >> kw4;		// density (optional)
		char kw5[256] = ""; istr >> kw5;	// filename (optional)
		
		char ** endptr = NULL;
		fGL rad1 = strtod(kw2, endptr);
		fGL rad2 = strtod(kw3, endptr);
		
		fGL density = 1.00;	// in kg/liter as usual...
		if (strlen(kw4) > 0) density = strtod(kw4, endptr);
		
		dummy_project * solvent = NULL;
		if (strlen(kw5) > 0)
		{
			solvent = new dummy_project(NULL);
			
			char fn[256];
			ostrstream fns(fn, sizeof(fn));
			fns << kw5 << ".gpr" << ends;
			
			ifstream ifile(fn, ios::in);
			ReadGPR(* solvent, ifile, false);
			ifile.close();
		}
		
		SolvateSphere(rad1, rad2, density, solvent);
		UpdateAllGraphicsViews();
		return;
	}
	
	if (!strcmp("set_formal_charge", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; index.
		char kw3[32]; istr >> kw3;	// the 3rd keyword; charge.
		char ** endptr = NULL;
		
		i32s index = strtol(kw2, endptr, 10);
		i32s charge = strtol(kw3, endptr, 10);
		
		if (!IsIndexClean()) UpdateIndex();
		
		atom * atmr = NULL;
		for (iter_al it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
		{
			if ((* it1).index == index) { atmr = & (* it1); break; }
		}
		
		if (atmr != NULL)
		{
			atmr->formal_charge = charge;
			UpdateAllGraphicsViews();	// update the labels...
		}
		else
		{
			PrintToLog("Sorry, atom not found!\n");
		}
		return;
	}
	
	if (!strcmp("evaluate_Bfact", kw1))
	{
		EvaluateBFact();
		return;
	}
	
	if (!strcmp("evaluate_diffconst", kw1))
	{
		char kw2[32]; istr >> kw2;	// the 2nd keyword; dt.
		
		char ** endptr = NULL;
		fGL dt = strtod(kw2, endptr);
		
		EvaluateDiffConst(dt);
		return;
	}
	
#endif
	// if the command is not recognized above, we will print out an error message here.
	
	ostrstream strE(mbuff1, sizeof(mbuff1)); strE << "ERROR : Unknown command : " << command << endl << ends;
	PrintToLog(mbuff1); PrintToLog("The \"help\" command will give more information about command strings.\n");
}
#if 0
void project::start_job_GeomOpt(jobinfo_GeomOpt * ji)
{
#ifdef ENABLE_THREADS
	
	CreateProgressDialog("Geometry Optimization", true, 1, 20);
	GThread * t = g_thread_create(pcs_job_GeomOpt, (gpointer) ji, FALSE, NULL);
	if (t == NULL) { DestroyProgressDialog(); ErrorMessage("Thread failed!"); }
	
#else	// ENABLE_THREADS

	DWORD dwChildID;
	HANDLE hThread;
	hThread = ::CreateThread(NULL, 0, 
		pcs_job_GeomOpt, 
		reinterpret_cast<LPVOID>(ji), 
		0,
		&dwChildID );
	
//	pcs_job_GeomOpt((gpointer) ji);
//	pcs_job_GeomOpt((void*) ji);
	
#endif	// ENABLE_THREADS
}

//gpointer project::pcs_job_GeomOpt(gpointer p)
DWORD WINAPI project::pcs_job_GeomOpt(void* p)
{
	jobinfo_GeomOpt * ji = (jobinfo_GeomOpt *) p;
	
#ifdef ENABLE_THREADS
	const bool updt = false;
#else	// ENABLE_THREADS
	const bool updt = true;
#endif	// ENABLE_THREADS
	
	ji->prj->DoGeomOpt(ji->go, updt);
	
#ifdef ENABLE_THREADS
	ji->prj->ThreadLock();
	ji->prj->DestroyProgressDialog();
	ji->prj->ThreadUnlock();
#endif	// ENABLE_THREADS
	
	return NULL;
}

void project::start_job_MolDyn(jobinfo_MolDyn * ji)
{
#ifdef ENABLE_THREADS
	
	CreateProgressDialog("Molecular Dynamics", true, NOT_DEFINED, NOT_DEFINED);
	GThread * t = g_thread_create(pcs_job_MolDyn, (gpointer) ji, FALSE, NULL);
	if (t == NULL) { DestroyProgressDialog(); ErrorMessage("Thread failed!"); }
	
#else	// ENABLE_THREADS
	
//	pcs_job_MolDyn((gpointer) ji);
//	pcs_job_MolDyn((void*) ji);
	DWORD dwChildID;
	HANDLE hThread;
	hThread = ::CreateThread(NULL, 0, 
		pcs_job_MolDyn, 
		reinterpret_cast<LPVOID>(ji), 
		0,
		&dwChildID );
	
#endif	// ENABLE_THREADS
}

//gpointer project::pcs_job_MolDyn(gpointer p)
DWORD WINAPI project::pcs_job_MolDyn(void* p)
{
	jobinfo_MolDyn * ji = (jobinfo_MolDyn *) p;
	
#ifdef ENABLE_THREADS
	const bool updt = false;
#else	// ENABLE_THREADS
	const bool updt = true;
#endif	// ENABLE_THREADS
	
	ji->prj->DoMolDyn(ji->md, updt);
	
#ifdef ENABLE_THREADS
	ji->prj->ThreadLock();
	ji->prj->DestroyProgressDialog();
	ji->prj->ThreadUnlock();
#endif	// ENABLE_THREADS
	
	return NULL;
}

//gpointer project::pcs_job_RandomSearch(gpointer p)
void* project::pcs_job_RandomSearch(void* p)
{
	jobinfo_RandomSearch * ji = (jobinfo_RandomSearch *) p;
	
#ifdef ENABLE_THREADS
	const bool updt = false;
#else	// ENABLE_THREADS
	const bool updt = true;
#endif	// ENABLE_THREADS
	
	ji->prj->DoRandomSearch(ji->cycles, ji->optsteps, updt);
	
#ifdef ENABLE_THREADS
	ji->prj->ThreadLock();
	ji->prj->DestroyProgressDialog();
	ji->prj->ThreadUnlock();
#endif	// ENABLE_THREADS
	
	return NULL;
}
#endif
/*##############################################*/
/*##############################################*/

void project::DoDeleteCurrentObject(void)
{
	if (selected_object != NULL)
	{
		bool test1 = RemoveLight(selected_object);
		bool test2 = test1; if (!test1) test2 = RemoveObject(selected_object);
		
		if (test2)
		{
			selected_object = NULL;
			UpdateAllGraphicsViews();
		}
	}
}

bool project::DoSwitchLocalLights(camera * cam, bool report)
{
	cam->use_local_lights = !cam->use_local_lights;
	if (report) cout << "local lights = " << (cam->use_local_lights ? "on" : "off") << endl;
	SetupLights(cam); UpdateGraphicsViews(cam);
	return cam->use_local_lights;
}

bool project::DoSwitchGlobalLights(camera * cam, bool report)
{
	cam->use_global_lights = !cam->use_global_lights;
	if (report) cout << "global lights = " << (cam->use_global_lights ? "on" : "off") << endl;
	SetupLights(cam); UpdateGraphicsViews(cam);
	return cam->use_global_lights;
}

bool project::DoSwitchMovingLocalLights(camera * cam, bool report)
{
	cam->move_local_lights = !cam->move_local_lights;
	if (report) cout << "move local lights = " << (cam->move_local_lights ? "on" : "off") << endl;
	return cam->move_local_lights;
}

bool project::DoSwitchMovingGlobalLights(camera * cam, bool report)
{
	cam->move_global_lights = !cam->move_global_lights;
	if (report) cout << "move global lights = " << (cam->move_global_lights ? "on" : "off") << endl;
	return cam->move_global_lights;
}



void project::InitGL(void)
{
//	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
//	{
//		printf("If Texture Didn't Load Return FALSE\n");
//		return;									// If Texture Didn't Load Return FALSE
//	}

//	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )

//	printf("project::InitGL(void)\n\n");
    const fGL background[4] = { 1.0, 1.0, 1.0, 1.0};
//    const fGL background[4] = { 0.5, 1.0, 0.5, 0.1};
//	fGL *background = model_prefs->ColorRGBA("Graphics/BkgndColor", default_background);
	glClearColor(background[0], background[1], background[2], background[3]);
//	delete [] background;
	
	glDepthFunc(GL_LESS); glEnable(GL_DEPTH_TEST);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	
	const fGL specular_reflectance[4] = { 0.9, 0.9, 0.9, 1.0 };
//	fGL *specular_reflectance = model_prefs->ColorRGBA("Graphics/SpecularReflectance", default_reflectance);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_reflectance);
//	delete [] specular_reflectance;
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	const fGL ambient_intensity[4] = { 0.2, 0.2, 0.2, 1.0 };
//	fGL *ambient_intensity = model_prefs->ColorRGBA("Graphics/AmbientIntensity", default_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
//	delete [] ambient_intensity;
#if 0	
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, true);
#else
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
#endif
#if 0	
	glFogi(GL_FOG_MODE, GL_EXP);
//	glFogf(GL_FOG_DENSITY, model_prefs->Double("Graphics/FogDensity",0.15));
	glFogf(GL_FOG_DENSITY, 0.15);
	
	const fGL fog_color[4] = { 0.0, 0.0, 0.0, 0.0 };
//	fGL *fog_color = model_prefs->ColorRGBA("Graphics/FogColor", default_fog);
	glFogfv(GL_FOG_COLOR, fog_color);
//	delete [] fog_color;
#endif	
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


glSelectBuffer(SB_SIZE, select_buffer);
	
	// also setup the lights, just to make sure it always happens...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#if 1
	//SetLight();
//#else
	for (i32u n1 = 0;n1 < camera_vector.size();n1++)
	{
		cout << "InitGL : setting up lights for cam " << n1 << endl;
		SetupLights(camera_vector[n1]);
	}
#endif
}

fGL project::GetDefaultFocus(void)
{
	return 10.0;
	//return 2.0;
}

color_mode * project::GetDefaultColorMode(void)
{
	return & project::cm_element;
}
void Select_Object(Object * pOb, WPARAM, LPARAM lParam, void * )
{
	printf("Select_Object\t");
	if (pOb)
	{
		fprintf(stdout,"object(type = \"%s\") name = %s\n",
			Object::ObjectTypeToString(pOb->GetObjectType()), 
			pOb->GetName().c_str());

		if (lParam & OBJECT_FLAG_SELECTED_BIT)
		{
			// UN SELECT OBJECT - выключаем 2-й бит 
			// в пользовательских данных объекта
			pOb->m_lParam &= ~OBJECT_FLAG_SELECTED_BIT;
			//ogl_view::what_selected.RemoveSelectedObject(pOb);
		}
		else
		{
			// SELECT OBJECT - включаем 2-й бит 
			// в пользовательских данных объекта 
			pOb->m_lParam |= OBJECT_FLAG_SELECTED_BIT;
			//ogl_view::what_selected.AddSelectedObject(pOb);
		}
		pOb->ReDraw();
	}
}
void Check_Object(Object * pOb, WPARAM, LPARAM lParam, void * p)
{
	if (pOb && p)
	{
		if (lParam)
		{
			pOb->m_bChecked = true;
			//printf("Check_Object pOb->m_bChecked = true\n"); 
		}
		else
		{
			pOb->m_bChecked = false;
			//printf("Check_Object pOb->m_bChecked = false\n"); 
		}
		project * pDoc = reinterpret_cast<project*>(p);
		TreeView_MySetCheckState(pDoc->hwndTV, 
			pOb->myTreeItem, pOb->m_bChecked);
	}
}
void Select_All(Object * pOb, WPARAM, LPARAM, void * )
{
	if (pOb)
	{
		// SELECT OBJECT - включаем 2-й бит 
		// в пользовательских данных объекта 
		pOb->m_lParam |= OBJECT_FLAG_SELECTED_BIT;
		pOb->ReDraw();
	}
}


void Set_Name(Object * pOb, WPARAM, LPARAM lParam, void * )
{
	if (pOb)
	{
		fprintf(stdout,"Selected object(type = \"%s\") name before = %s\t",
			Object::ObjectTypeToString(pOb->GetObjectType()), 
			pOb->GetName().c_str());

		pOb->SetName((char*)lParam);

		fprintf(stdout,"name after = %s\n",
			pOb->GetName().c_str());
	}
}

void Set_ID(Object * pOb, WPARAM, LPARAM lParam, void * )
{
	if (pOb)
	{
		fprintf(stdout,"Selected object(type = \"%s\") ID before = %d\t",
			Object::ObjectTypeToString(pOb->GetObjectType()), 
			pOb->GetUserID());

		pOb->SetUserID((int)lParam);

		fprintf(stdout,"ID after = %d\n",
			pOb->GetUserID());
	}
}

void Inverse_Selection(Object * pOb, WPARAM, LPARAM, void * )
{
	if (pOb)
	{
		if (pOb->m_lParam & OBJECT_FLAG_SELECTED_BIT)
		{
			// UN SELECT OBJECT - выключаем 2-й бит 
			// в пользовательских данных объекта
			pOb->m_lParam &= ~OBJECT_FLAG_SELECTED_BIT;
		}
		else
		{
			// SELECT OBJECT - включаем 2-й бит 
			// в пользовательских данных объекта 
			pOb->m_lParam |= OBJECT_FLAG_SELECTED_BIT;
		}
		pOb->ReDraw();
	}
}
void Select_None(Object * pOb, WPARAM, LPARAM, void * )
{
	if (pOb)
	{
		if (pOb->m_lParam & OBJECT_FLAG_SELECTED_BIT)
		{
			// UN SELECT OBJECT - выключаем 2-й бит 
			// в пользовательских данных объекта
			pOb->m_lParam &= ~OBJECT_FLAG_SELECTED_BIT;
			pOb->ReDraw();
		}
	}
}

void Select_All_Empty_Wells(Object * pOb, WPARAM, LPARAM, void * )
{
   if (pOb)
   {
      Well_3D * pwell = dynamic_cast<Well_3D *>(pOb);
      if (pwell)
      {
         WellColomn * pwell_colomn = pwell->FindWellColomn(WellElement::type::IGE_podoshva);
         if (pwell_colomn && pwell_colomn->GetWellElementSize() == 0)
         {
            // SELECT OBJECT - включаем 2-й бит 
            // в пользовательских данных объекта
            pwell->m_lParam |= OBJECT_FLAG_SELECTED_BIT;
            pwell->ReDraw();
         }
      }
   }
}

void project::SelectAllEmptyWells(void)
{
	if (selected_object != NULL)
	{
		selected_object = NULL;
	}

	this->EnumObjects(0, 0, NULL, 
		&Object::ReturnTrue,
		Select_All_Empty_Wells);

	UpdateAllViews();
}


void project::SelectAll(void)
{
	if (selected_object != NULL)
	{
		selected_object = NULL;
	}

	this->EnumObjects(0, 0, NULL, 
		&Object::ReturnTrue,
		Select_All);

	UpdateAllViews();
}

void project::SelectNone(void)
{
	if (selected_object != NULL)
	{
		selected_object = NULL;
	}
	
	this->EnumObjects(0, 0, NULL, 
		&Object::ReturnTrue,
		Select_None);

	UpdateAllViews(false);
}

void project::InvertSelection(void)
{
	if (selected_object != NULL)
	{
		selected_object = NULL;
	}
	
//	iter_al it1 = atom_list.begin();
//	while (it1 != atom_list.end()) (* it1++).flags ^= ATOMFLAG_SELECTED;
	this->EnumObjects(0, 0, NULL, 
		&Object::ReturnTrue,
		Inverse_Selection);	
	UpdateAllViews(false);
}

void project::DeleteSelection(void)
{
	if (selected_object != NULL)
	{
		selected_object = NULL;
	}
	
/*	iter_al it1 = atom_list.begin();
	while (it1 != atom_list.end())
	{
		if ((* it1).flags & ATOMFLAG_SELECTED)
		{
			RemoveAtom(it1);
			it1 = atom_list.begin();	// reset the search!!!
		}
		else it1++;
	}*/
	
	UpdateAllViews();
}

void project::UncheckSelection(void)
{
	this->EnumObjects(0, 0, (void*) this, 
		&Object::IsSelected,
		Check_Object);	
	UpdateAllViews(false);
}

void project::UncheckUnselection(void)
{
	//printf("project::UncheckUnselection(void)\n");
	this->EnumObjects(0, 0, (void*) this, 
		&Object::IsUnselected,
		Check_Object);	
	UpdateAllViews();
}

void project::CheckUnselection(void)
{
	//printf("project::UncheckUnselection(void)\n");
	this->EnumObjects(0, 1, (void*) this, 
		&Object::IsUnselected,
		Check_Object);	
	UpdateAllViews();
}

void project::CheckSelection(void)
{
	this->EnumObjects(0, 1, (void*) this, 
		&Object::IsSelected,
		Check_Object);		
	UpdateAllViews();
}

void Set_Color(Object * pOb, WPARAM, LPARAM lParam, void * )
{
	COLORREF color = COLORREF(lParam);
	if (pOb)
	{
		pOb->SetColor(color);
		pOb->ReDraw();
	}
}

void project::SelectionSetColor(void)
{
	COLORREF color = RGB(255,0,0);
	if (0 == ChooseSurfColor(this->hSurfWnd, color))
	{
		this->EnumObjects(0, LPARAM(color), (void*) this, 
			&Object::IsSelected,
			Set_Color);		
		UpdateAllViews();
	}
}
void project::SelectionSetColor_FromCurrentWellsSloj(void)
{
	COLORREF color;
	bool got_color = false;
	//printf("Well_3D::s_sloj_number_to_save = %d\n", Well_3D::s_sloj_number_to_save);
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			int i = Well_3D::s_sloj_number_to_save;
			if (i >=0 && i < (int)this->m_drills.GetCurrentMsg().GetPointsNumber())
			{
				CPoint3 pt			= this->m_drills.GetCurrentMsg().GetDocumentPoint(i);
				color		= this->m_drills.GetCurrentMsg().GetColor(i);
				string sloj_name	= this->m_drills.GetCurrentMsg().GetSlojName(i);
				string well_id		= this->m_drills.GetCurrentMsg().GetWellID();
                
				if (pt.bVisible)
				{
					printf("%s\t%s\t[%lf, %lf, %lf] color = %d\n", 
					well_id.c_str(), 
					sloj_name.c_str(),
					pt.x, 
					pt.y, 
					pt.z, color);

					got_color = true;
					break;
				}
			}
		}
		while (this->m_drills.IncrementCurrentMsg());
	}

	if (got_color)
	{
		this->EnumObjects(0, LPARAM(color), (void*) this, 
			&Object::IsSelected,
			Set_Color);		
		UpdateAllViews();
	}
}

void To_GridData(Object * pOb, WPARAM, LPARAM, void * p)
{
	if (pOb)
	{
		Line3D * line = dynamic_cast<Line3D *>(pOb);
		if (line)
		{
			GridData * pData = reinterpret_cast<GridData *>(p);
			if (pData)
			{
				pData->AddLineToInput(line);
				pData->SetName(line->GetName().c_str());
			}
		}
		else
		{
			Primitive3D<CPoint3> * prim = dynamic_cast<Primitive3D<CPoint3> *>(pOb);
			if (prim)
			{
				GridData * pData = reinterpret_cast<GridData *>(p);
				if (pData)
				{
					pData->AddInput(prim);
					pData->SetName(prim->GetName().c_str());
				}
			}
		}
	}
}


void project::SelectionToGridData(void)
{
	this->CreateNewGridData();

	this->EnumObjects(0, 0, (void*) &this->m_grid_data.GetLastMsg(), 
		&Object::IsSelected,
		To_GridData);

	//this->Zoom<GridData>(this->m_grid_data);

	this->SelectNone();
	
	this->m_grid_data.GetLastMsg().Zooming();		
	this->m_grid_data.GetLastMsg().Draw();
#if 0
	if (this->m_pSurfDoc->m_grid_data_ObjectList.myTreeItem == NULL)
	{
		HTREEITEM h1 = AddObjectListItem(this->m_pSurfDoc->hwndTV, "GridData", &this->m_grid_data_ObjectList);
	}
	this->m_grid_data.GetLastMsg().AddItem_ToTree(this->hwndTV, this->m_grid_data_ObjectList.myTreeItem);
#else
	this->Zoom<GridData>(this->m_grid_data);
	ReDrawGridData(this);
#endif
	UpdateAllViews();
	this->m_grid_data.GetLastMsg().GrDtSaveToDB(0);
}

void project::Selection_With_WellsCurrentSloj_ToGridData(void)
{
	this->CreateNewGridData();

	this->EnumObjects(0, 0, (void*) &this->m_grid_data.GetLastMsg(), 
		&Object::IsSelected,
		To_GridData);

	printf("Well_3D::s_sloj_number_to_save = %d\n", Well_3D::s_sloj_number_to_save);
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			int i = Well_3D::s_sloj_number_to_save;
			if (i >=0 && i < (int)this->m_drills.GetCurrentMsg().GetPointsNumber())
			{
				CPoint3 pt			= this->m_drills.GetCurrentMsg().GetDocumentPoint(i);
				COLORREF color		= this->m_drills.GetCurrentMsg().GetColor(i);
				string sloj_name	= this->m_drills.GetCurrentMsg().GetSlojName(i);
				string well_id		= this->m_drills.GetCurrentMsg().GetWellID();
                
				if (pt.bVisible)
				{
					printf("%s\t%s\t[%lf, %lf, %lf] color = %d\n", 
					well_id.c_str(), 
					sloj_name.c_str(),
					pt.x, 
					pt.y, 
					pt.z, color);

					this->m_grid_data.GetLastMsg().AddInput(pt, color);
				}
			}
		}
		while (this->m_drills.IncrementCurrentMsg());
	}

	this->Zoom<GridData>(this->m_grid_data);
	ReDrawGridData(this);

	UpdateAllViews();
	this->m_grid_data.GetLastMsg().GrDtSaveToDB(1);
}

void Set_LayerPtr(Object * pOb, WPARAM, LPARAM, void * p)
{
	if (pOb)
	{
		pOb->SetLayer_NonVirtual(reinterpret_cast<Layer *>(p));
		if (pOb->m_lParam & OBJECT_FLAG_SELECTED_BIT)
		{
			// UN SELECT OBJECT - выключаем 2-й бит 
			// в пользовательских данных объекта
			pOb->m_lParam &= ~OBJECT_FLAG_SELECTED_BIT;
		}
		pOb->ReDraw();
	}
}


void project::SelectionToLayer(void)
{
	new select_layer_dialog(dynamic_cast<SurfDoc *>(this), "New Layer name");
	if (this->m_selected_layer)
	{
		this->EnumObjects(0, 0, (void*) this->m_selected_layer, 
			&Object::IsSelected,
			Set_LayerPtr);
		UpdateAllViews();
	}

	this->m_selected_layer = NULL;
}

void Get_Name_ID(Object * pOb, WPARAM, LPARAM, void * )
{
	if (pOb)
	{
		fprintf(stdout,"Selected object(type = \"%s\") name = %s ID = %d layer = \"%s\" %d\n",
			Object::ObjectTypeToString(pOb->GetObjectType()), 
			pOb->GetName().c_str(),
			pOb->GetUserID(),
			pOb->GetLayer() == NULL ? "" : pOb->GetLayer()->GetName().c_str(),
			pOb->GetLayer() == NULL ? -2 : pOb->GetLayerID()
			);
	}
}

void project::SelectionGetNamesAndID(void)
{
	//printf("project::SelectionGetNames\n");
	this->EnumObjects(0, 0, 0, 
		&Object::IsSelected,
		Get_Name_ID);
}

void project::SelectionSetName(HWND widget, void * data)
{
//printf("project::SelectionSetName()\n");

	win_graphics_view * gv = win_graphics_view::GetGV(widget);	
	
	static char command[1024] = "";
	command_dialog * cmnd_dlg = new command_dialog(gv->prj, gv, command, false);
	if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

	if (cmnd_dlg && cmnd_dlg->WasOk())
	{
		this->EnumObjects(0, (LPARAM)command, 0, 
			&Object::IsSelected,
			Set_Name);

		this->Draw();// only for redraw tree items
	}

	if (cmnd_dlg)
	{
		delete cmnd_dlg;
		cmnd_dlg = NULL;
	}

}

void project::SelectionSetID(HWND widget, void * data)
{
//printf("project::SelectionSetID()\n");

	win_graphics_view * gv = win_graphics_view::GetGV(widget);	
	static char command[512] = "";
	command_dialog * cmnd_dlg = new command_dialog(gv->prj, gv, command, false);
	if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

	if (cmnd_dlg && cmnd_dlg->WasOk())
	{
		this->EnumObjects(0, (LPARAM)atoi(command), 0, 
			&Object::IsSelected,
			Set_ID);
	}

	if (cmnd_dlg)
	{
		delete cmnd_dlg;
		cmnd_dlg = NULL;
	}

//	DrawScene(this);// only for redraw tree items
}

#if 0
bool project::TestAtom(atom * ref, rmode rm)
{
	if (ref->flags & ATOMFLAG_IS_HIDDEN) return false;
	
	if (rm == Transform1 && (ref->flags & ATOMFLAG_SELECTED)) return false;
	if (rm == Transform2 && !(ref->flags & ATOMFLAG_SELECTED)) return false;
	
	return true;
}

bool project::TestBond(bond * ref, rmode rm)
{
	if (ref->atmr[0]->flags & ATOMFLAG_IS_HIDDEN) return false;
	if (ref->atmr[1]->flags & ATOMFLAG_IS_HIDDEN) return false;
	
	if (rm == Transform1 && (ref->atmr[0]->flags & ATOMFLAG_SELECTED)) return false;	// no need to study the another...
	if (rm == Transform2 && !(ref->atmr[0]->flags & ATOMFLAG_SELECTED)) return false;	// ...atom due to the test below?
	
	bool test1 = (ref->atmr[0]->flags & ATOMFLAG_SELECTED) ? true : false;
	bool test2 = (ref->atmr[1]->flags & ATOMFLAG_SELECTED) ? true : false;
	if (rm != Normal && test1 != test2) return false;
	
if (ref->do_not_render_TSS_fixmelater) return false;	// temporary, for transition_state_search only...
	
	return true;
}
void project::SetColor(color_mode * cm, atom * ref, bool black_and_white)
{
	fGL select_color[3] = { 1.0, 0.0, 1.0 };	// this can no longer be const...
//	fGL *select_color = model_prefs->ColorRGB("Graphics/SelectColor", default_sel_color);

	if (ref->flags & ATOMFLAG_SELECTED)
	{
		if (black_and_white)	// if we have a red/blue stereo mode, average the colours to shades of gray!
		{
			fGL average = (select_color[0] + select_color[1] + select_color[2]) / 3.0;
			select_color[0] = select_color[1] = select_color[2] = average;
		}
		
		glColor3f(select_color[0], select_color[1], select_color[2]);
	}
	else
	{
		static fGL color[4];
		cm->GetColor4(ref, -1, color);
		
		if (black_and_white)	// if we have a red/blue stereo mode, average the colours to shades of gray!
		{
			fGL average = (color[0] + color[1] + color[2]) / 3.0;
			color[0] = color[1] = color[2] = average;
		}
		
		glColor3fv(color);
	}
	
//	delete [] select_color;
}
#endif

void project::DrawCylinder1(const fGL ** crd, const fGL ** col, const fGL * rad)
{
	fGL rsum = rad[0] + rad[1];
	
	for (i32s n1 = 0;n1 < 2;n1++)
	{
		glColor3fv(col[n1]);
		
		v3d<fGL> crt = v3d<fGL>(crd[n1], crd[!n1]);
		fGL pol[3]; crt2pol(crt.data, pol);
		
	//	const float radius = 0.1;	//model_prefs->Double("MM2Graphics/CylinderSize", 0.1);
		const int resolution = 10;	//model_prefs->Value("MM2Graphics/CylinderResolution", 10);
		
		GLUquadricObj * qo = gluNewQuadric();
		gluQuadricDrawStyle(qo, (GLenum) GLU_FILL); glPushMatrix();
		
		glTranslated(crd[n1][0], crd[n1][1], crd[n1][2]);
		
		glRotated(180.0 * pol[1] / M_PI, 0.0, 1.0, 0.0);
		glRotated(180.0 * pol[2] / M_PI, sin(-pol[1]), 0.0, cos(-pol[1]));
		
		fGL length = crt.len() * rad[n1] / rsum;
		gluCylinder(qo, 0.1*rad[n1], 0.1*rad[!n1], length, resolution, resolution / 2);
		
		glPopMatrix(); gluDeleteQuadric(qo);
	}
}
#include "..\..\surfdoc\src\drawscene.h"
void project::Render(graphics_view * gv, rmode rm)
{
	const fGL label_color[3] = { 0.0, 1.0, 1.0 };	// looks bad but won't fade easily into other colours...
//	fGL *label_color = model_prefs->ColorRGB("Graphics/LabelColor", default_label_color);
	
	bool accum = gv->accumulate; if (rm != Normal) accum = false;
//if (accum) { glClear(GL_ACCUM_BUFFER_BIT); UpdateAccumValues(); }
//else if (rm != Transform2) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SurfDoc *pSurfDoc;
	pSurfDoc = dynamic_cast<SurfDoc *> (this);


	if (!pSurfDoc->m_bDrawGeoid)
	{
		//pSurfDoc->SetLight();
	}


	glListBase(0); // Indicates the start of display lists for the glyphs 
	//GL_LIST_BASE 
		
	//The params parameter returns one value: 
	//the base offset added to all names in arrays presented 
	//to glCallLists. See glListBase. 
	
	int list_base;
	glGetIntegerv(GL_LIST_BASE,  &list_base);


	//====== Вызов списка рисующих команд
	if (pSurfDoc->m_bDrawCube)
	{
		glDisable(GL_CLIP_PLANE0);
		glCallList(FIRST_HARD_LIST + 1);
	}
	
	if (pSurfDoc->m_bDrawCutPlane)
	{
		glCallList(FIRST_HARD_LIST + 2);
		if (pSurfDoc->m_bFastCutting)
		{
			glClipPlane(GL_CLIP_PLANE0, pSurfDoc->m_cut_plane_v);
			glEnable(GL_CLIP_PLANE0);
		}
		else
			glDisable(GL_CLIP_PLANE0);
	}
	else
		glDisable(GL_CLIP_PLANE0);

	if (pSurfDoc->m_bDrawXYZCutPlanes)
		glCallList(FIRST_HARD_LIST + 3);
	if (pSurfDoc->m_bDrawGeoid)
		glCallList(FIRST_HARD_LIST + 4);

	DrawListArray::glCallLists();


#if 0
	if (use_boundary_potential && rm == Normal)
	{
		for (int loop = 0;loop < 2;loop++)
		{
			fGL radius;
			
			if (!loop) { glColor3f(0.5, 0.0, 0.5); radius = boundary_potential_radius1; }
			else { glColor3f(1.0, 0.0, 1.0); radius = boundary_potential_radius2; }
			
			glPushMatrix();
			glTranslated(0.0, 0.0, 0.0);	// TODO : set the engine::bp_center[] here!!!
			
			glBegin(GL_LINES);
			
			fGL ang1 = 0.0;
			fGL ca1 = radius * cos(ang1);
			fGL sa1 = radius * sin(ang1);
			
			const i32s divisions = 12;
			for (i32s n1 = 0;n1 < divisions;n1++)
			{
				fGL ang2 = 2.0 * M_PI * ((fGL) (n1 + 1)) / (fGL) divisions;
				fGL ca2 = radius * cos(ang2);
				fGL sa2 = radius * sin(ang2);
				
				glVertex3f(ca1, sa1, 0.0);
				glVertex3f(ca2, sa2, 0.0);
				
				glVertex3f(ca1, 0.0, sa1);
				glVertex3f(ca2, 0.0, sa2);
				
				glVertex3f(0.0, ca1, sa1);
				glVertex3f(0.0, ca2, sa2);
				
				ang1 = ang2; ca1 = ca2; sa1 = sa2;
			}
			
			glEnd();
			
			glPopMatrix();
		}
	}
	
	if (use_periodic_boundary_conditions && rm == Normal)
	{
		glLineWidth(1.0);
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINES);
		
		glVertex3f(-periodic_box_HALFdim[0], -periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], -periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], +periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], +periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], -periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], -periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], +periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], +periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], -periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(-periodic_box_HALFdim[0], -periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], +periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(-periodic_box_HALFdim[0], +periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(+periodic_box_HALFdim[0], -periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], -periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(+periodic_box_HALFdim[0], +periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], +periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], -periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(-periodic_box_HALFdim[0], +periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		
		glVertex3f(-periodic_box_HALFdim[0], -periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		glVertex3f(-periodic_box_HALFdim[0], +periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glVertex3f(+periodic_box_HALFdim[0], -periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], +periodic_box_HALFdim[1], -periodic_box_HALFdim[2]);
		
		glVertex3f(+periodic_box_HALFdim[0], -periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		glVertex3f(+periodic_box_HALFdim[0], +periodic_box_HALFdim[1], +periodic_box_HALFdim[2]);
		
		glEnd();
	}
	if (gv->enable_fog) glEnable(GL_FOG);
	
	i32s layers = 0;
//	if (use_periodic_boundary_conditions && rm == Normal) layers = 1;	// un-comment this to render the periodic images...
	
	for (i32s r1 = -layers;r1 < (layers + 1);r1++)
	{
		for (i32s r2 = -layers;r2 < (layers + 1);r2++)
		{
			for (i32s r3 = -layers;r3 < (layers + 1);r3++)
			{
				glPushMatrix();
				
				fGL trans1 = r1 * 2.0 * periodic_box_HALFdim[0];
				fGL trans2 = r2 * 2.0 * periodic_box_HALFdim[1];
				fGL trans3 = r3 * 2.0 * periodic_box_HALFdim[2];
				
				glTranslated(trans1, trans2, trans3);
				
				RenderScene(gv, rm, accum);
				
				glPopMatrix();
			}
		}
	}
	
	if (accum) glAccum(GL_RETURN, 1.0);
	else if (rm != Transform2) gv->cam->RenderObjects(gv);
	
	if (gv->label == LABEL_INDEX)
	{
		char string[32]; i32s tmp1 = 0;
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
		{
			if ((* it1).flags & ATOMFLAG_IS_HIDDEN) { tmp1++; continue; }
			
			ostrstream str(string, sizeof(string));
			str << tmp1++ << ends;
			
			const fGL * cdata = (* it1).GetCRD(0);
			fGL x = cdata[0]; fGL y = cdata[1]; fGL z = cdata[2];
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_F_CHARGE)
	{
		char string[32];
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
		{
			if ((* it1).flags & ATOMFLAG_IS_HIDDEN) continue;
			
			ostrstream str(string, sizeof(string));
			str.setf(ios::fixed | ios::showpos); str << (* it1).formal_charge << ends;

			const fGL * cdata = (* it1).GetCRD(0);
			fGL x = cdata[0]; fGL y = cdata[1]; fGL z = cdata[2];
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_P_CHARGE)
	{
		char string[32];
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
		{
			if ((* it1).flags & ATOMFLAG_IS_HIDDEN) continue;
			
			ostrstream str(string, sizeof(string));
			str.setf(ios::fixed | ios::showpos); str.precision(4); str << (* it1).charge << ends;

			const fGL * cdata = (* it1).GetCRD(0);
			fGL x = cdata[0]; fGL y = cdata[1]; fGL z = cdata[2];
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_ELEMENT)
	{
		char string[32];
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
		{
			if ((* it1).flags & ATOMFLAG_IS_HIDDEN) continue;
			
			ostrstream str(string, sizeof(string));
			str << (* it1).el.GetSymbol() << ends;

			const fGL * cdata = (* it1).GetCRD(0);
			fGL x = cdata[0]; fGL y = cdata[1]; fGL z = cdata[2];
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_BUILDER_ID)
	{
		char string[32];
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
		{
			if ((* it1).flags & ATOMFLAG_IS_HIDDEN) continue;
			
			ostrstream str(string, sizeof(string));
			str << "0x" << hex << (* it1).builder_res_id << ends;

			const fGL * cdata = (* it1).GetCRD(0);
			fGL x = cdata[0]; fGL y = cdata[1]; fGL z = cdata[2];
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_ATOMTYPE)
	{
		char string[32];
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
		{
			if ((* it1).flags & ATOMFLAG_IS_HIDDEN) continue;
			
			ostrstream str(string, sizeof(string));
			str << "0x" << hex << (* it1).atmtp << ends;
			
		//	str << "0x" << hex << (* it1).atmtp_E << ends;		// debug...
		//	str << (* it1).atmtp_s << ends;				// debug...
			
		/*	if (!(* it1).atRS) str << "none" << ends;
			else
			{
				atomtype_mmRS * atmtp = (* it1).atRS;
				if (!atmtp) str << "0x" << hex << (* it1).atmtp << ends;
				
				for (int n1 = 0;n1 < atmtp->GetSize();n1++)
				{
					str << "0x" << hex << atmtp->GetAtomType(n1) << " (" << atmtp->GetWeight(n1) << ")" << endl;
				}	str << ends;
			}	*/
			
			const fGL * cdata = (* it1).GetCRD(0);
			fGL x = cdata[0]; fGL y = cdata[1]; fGL z = cdata[2];
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_BONDTYPE)
	{
		char string[32];
		
		glColor3f(label_color[0], label_color[1], label_color[2]);
		for (iter_bl it1 = bond_list.begin();it1 != bond_list.end();it1++)
		{
			if ((* it1).atmr[0]->flags & ATOMFLAG_IS_HIDDEN) continue;
			if ((* it1).atmr[1]->flags & ATOMFLAG_IS_HIDDEN) continue;
			
			ostrstream str(string, sizeof(string));
			str << (* it1).bt.GetSymbol1() << ends;
			
			const fGL * cd1 = (* it1).atmr[0]->GetCRD(0); const fGL * cd2 = (* it1).atmr[1]->GetCRD(0);
			fGL x = (cd1[0] + cd2[0]) / 2.0; fGL y = (cd1[1] + cd2[1]) / 2.0; fGL z = (cd1[2] + cd2[2]) / 2.0;
			
			gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
		}
	}
	else if (gv->label == LABEL_RESIDUE)
	{
		if (ref_civ != NULL)
		{
			char string[32];
			glColor3f(label_color[0], label_color[1], label_color[2]);
			
			vector<chn_info> & ci_vector = (* ref_civ);
			for (i32u chn = 0;chn < ci_vector.size();chn++)
			{
				iter_al range1[2]; GetRange(1, chn, range1);
				const char * tmp_seq = ci_vector[chn].GetSequence();
				
				for (i32s res = 0;res < ci_vector[chn].GetLength();res++)
				{
					iter_al range2[2]; GetRange(2, range1, res, range2);
					fGL rescrd[3] = { 0.0, 0.0, 0.0 }; i32s counter = 0;
					
				// SLOW because coordinates calculated on-the-fly!!! save them somewhere???
				// SLOW because coordinates calculated on-the-fly!!! save them somewhere???
				// SLOW because coordinates calculated on-the-fly!!! save them somewhere???
					
					for (iter_al it1 = range2[0];it1 != range2[1];it1++)
					{
						const fGL * atmcrd = (* it1).GetCRD(0);
						rescrd[0] += atmcrd[0]; rescrd[1] += atmcrd[1]; rescrd[2] += atmcrd[2];
						counter++;
					}
					
					fGL x = rescrd[0] / (fGL) counter;
					fGL y = rescrd[1] / (fGL) counter;
					fGL z = rescrd[2] / (fGL) counter;
					
					ostrstream str(string, sizeof(string));
					str << tmp_seq[res] << " (" << (chn + 1) << "/" << (res + 1) << ")" << ends;
					
					gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
				}
			}
		}
	}
	else if (gv->label == LABEL_SEC_STRUCT)
	{
		if (ref_civ != NULL)
		{
			char string[32];
			glColor3f(label_color[0], label_color[1], label_color[2]);
			
			vector<chn_info> & ci_vector = (* ref_civ);
			for (i32u chn = 0;chn < ci_vector.size();chn++)
			{
				iter_al range1[2]; GetRange(1, chn, range1);
				const char * tmp_states = ci_vector[chn].GetSecStrStates();
				
				for (i32s res = 0;res < ci_vector[chn].GetLength();res++)
				{
					iter_al range2[2]; GetRange(2, range1, res, range2);
					fGL rescrd[3] = { 0.0, 0.0, 0.0 }; i32s counter = 0;
					
				// SLOW because coordinates calculated on-the-fly!!! save them somewhere???
				// SLOW because coordinates calculated on-the-fly!!! save them somewhere???
				// SLOW because coordinates calculated on-the-fly!!! save them somewhere???
					
					for (iter_al it1 = range2[0];it1 != range2[1];it1++)
					{
						const fGL * atmcrd = (* it1).GetCRD(0);
						rescrd[0] += atmcrd[0]; rescrd[1] += atmcrd[1]; rescrd[2] += atmcrd[2];
						counter++;
					}
					
					fGL x = rescrd[0] / (fGL) counter;
					fGL y = rescrd[1] / (fGL) counter;
					fGL z = rescrd[2] / (fGL) counter;
					
					ostrstream str(string, sizeof(string));
					str << tmp_states[res] << ends;
					
					gv->WriteGlutString3D(string, x, y, z, gv->cam->GetLocData(), GLUT_BITMAP_9_BY_15);
				}
			}
		}
	}
#endif
	
	if (gv->enable_fog) glDisable(GL_FOG);
	
	// finally call this to handle transparency...
	// finally call this to handle transparency...
	// finally call this to handle transparency...
	
	RenderAllTPs(gv, rm);

//	delete [] label_color;
}

void project::RenderScene(graphics_view * gv, rmode rm, bool accum)
{
	bool do_bw = (gv->cam->stereo_mode && !gv->cam->stereo_relaxed);
#if 0
	for (i32u n1 = 0;n1 < 1 cs_vector.size();n1++)
	{
		if (!GetCRDSetVisible(n1)) continue;
if (accum) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// FIXME!!!

		if (gv->render == RENDER_WIREFRAME)
		{
			glPointSize(3.0); glLineWidth(1.0);
			for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)		// wireframe atoms
			{
				if (!TestAtom(& (* it1), rm)) continue;
				glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
				
				glBegin(GL_POINTS);
				SetColor(gv->colormode, & (* it1), do_bw);
				glVertex3fv((* it1).GetCRD(n1));
				glEnd();
				
				glPopName(); glPopName();
			}
			
			glEnable(GL_LINE_STIPPLE);
			for (iter_bl it2 = bond_list.begin();it2 != bond_list.end();it2++)		// wireframe bonds
			{
				if (!TestBond(& (* it2), rm)) continue;
				
				switch ((* it2).bt.GetSymbol1())
				{
					case 'S': glLineStipple(1, 0xFFFF); break;
					case 'C': glLineStipple(1, 0x3FFF); break;
					case 'D': glLineStipple(1, 0x3F3F); break;
					case 'T': glLineStipple(1, 0x3333); break;
				}
				
				glBegin(GL_LINES);
				SetColor(gv->colormode, (* it2).atmr[0], do_bw);
				glVertex3fv((* it2).atmr[0]->GetCRD(n1));
				SetColor(gv->colormode, (* it2).atmr[1], do_bw);
				glVertex3fv((* it2).atmr[1]->GetCRD(n1));
				glEnd();
			}
			glDisable(GL_LINE_STIPPLE);
		}
		
		if (gv->render != RENDER_WIREFRAME && gv->render != RENDER_NOTHING)
		{
			glEnable(GL_LIGHTING);
			
			for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)		// atoms as spheres
			{
				if (!TestAtom(& (* it1), rm)) continue;
				
				SetColor(gv->colormode, & (* it1), do_bw);
				
				float rad = 0.0; int res = 0;
				switch (gv->render)
				{
					case RENDER_BALL_AND_STICK:
					rad = 0.035;	//model_prefs->Double("MM1Graphics/BallSize", 0.035);
					//if (model_prefs->Boolean("MM1Graphics/BallVdWScale", false)) rad *= (* it1).vdwr * 4.0;
					res = 12;	//model_prefs->Value("MM1Graphics/BallResolution", 12);
					break;
					
					case RENDER_VAN_DER_WAALS:
					rad = (* it1).vdwr;
					res = 22;	//model_prefs->Value("MM1Graphics/VdWResolution", 22);
					break;
					
					case RENDER_CYLINDERS:
					rad = 0.035;	//model_prefs->Double("MM1Graphics/CylinderSize", 0.035);
					res = 12;	//model_prefs->Value("MM1Graphics/CylinderResolution", 12);
					break;
				}
				
				glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
				
				GLUquadricObj * qo = gluNewQuadric();
				gluQuadricDrawStyle(qo, (GLenum) GLU_FILL);
				
				glPushMatrix();
				const fGL * cdata = (* it1).GetCRD(n1);
				glTranslated(cdata[0], cdata[1], cdata[2]);
				gluSphere(qo, rad, res, res / 2);
				glPopMatrix();
				gluDeleteQuadric(qo);
				
				glPopName(); glPopName();
			}
			
			glDisable(GL_LIGHTING);
		}
		
		if (gv->render == RENDER_BALL_AND_STICK || gv->render == RENDER_CYLINDERS)
		{
			glEnable(GL_LIGHTING);
			
			for (iter_bl it1 = bond_list.begin();it1 != bond_list.end();it1++)		// bonds as cylinders
			{
				if (!TestBond(& (* it1), rm)) continue;
				
				fGL vdwr[2] =
				{
					(* it1).atmr[0]->vdwr,
					(* it1).atmr[1]->vdwr
				};
				
				fGL vdwrsum = vdwr[0] + vdwr[1];
				
				for (i32s n2 = 0;n2 < 2;n2++)
				{
					const fGL * crd1 = (* it1).atmr[n2]->GetCRD(n1);
					const fGL * crd2 = (* it1).atmr[!n2]->GetCRD(n1);
					v3d<fGL> crt1 = v3d<fGL>(crd1);
					v3d<fGL> crt2 = v3d<fGL>(crd2);
					v3d<fGL> crt = crt2 - crt1;
					
					fGL pol[3]; crt2pol(crt.data, pol);
					
					SetColor(gv->colormode, (* it1).atmr[n2], do_bw);
					
					float trans, rad = 0.0; int res = 0;
					switch (gv->render)
					{
						case RENDER_BALL_AND_STICK:
						rad = 0.01;	//model_prefs->Double("MM1Graphics/StickSize", 0.01);
						res = 6;	//model_prefs->Value("MM1Graphics/StickResolution", 6);
						break;
						
						case RENDER_CYLINDERS:
						rad = 0.035;	//model_prefs->Double("MM1Graphics/CylinderSize", 0.035);
						res = 12;	//model_prefs->Value("MM1Graphics/CylinderResolution", 12);
						break;
					}
					
					glPushName(GLNAME_MD_TYPE1); glPushName((i32u) (* it1).atmr[n2]);
					
					GLUquadricObj * qo = gluNewQuadric();
					gluQuadricDrawStyle(qo, (GLenum) GLU_FILL);
					glPushMatrix();
					
					glTranslated(crd1[0], crd1[1], crd1[2]);
					
					glRotated(180.0 * pol[1] / M_PI, 0.0, 1.0, 0.0);
					glRotated(180.0 * pol[2] / M_PI, sin(-pol[1]), 0.0, cos(-pol[1]));
					
					// any chance to further define the orientation of, for example, double bonds???
					// one more rotation would be needed. but what is the axis, and how much to rotate???
					
					fGL length = crt.len() * vdwr[n2] / vdwrsum;
					
					if (gv->render == RENDER_BALL_AND_STICK)
					switch ((* it1).bt.GetValue())
					{
						case BONDTYPE_DOUBLE:
						trans = rad;
						rad = rad / 1.5;
						
						if (n2)
							glTranslated(0.0, trans, 0.0);
						else
							glTranslated(0.0, -trans, 0.0);
						gluCylinder(qo, rad, rad, length, res, 1);					
						if (n2)
							glTranslated(0.0, -2.0 * trans, 0.0);
						else
							glTranslated(0.0, 2.0 * trans, 0.0);
						gluCylinder(qo, rad, rad, length, res, 1);
						break;
						
						case BONDTYPE_CNJGTD:
						trans = rad;
						rad = rad / 1.5;
						
						if (n2)
							glTranslated(0.0, trans, 0.0);
						else
							glTranslated(0.0, -trans, 0.0);
						gluCylinder(qo, rad, rad, length, res, 1);
						if (n2)
							glTranslated(0.0, -2.0 * trans, 0.0);
						else
							glTranslated(0.0, 2.0 * trans, 0.0);
						
						glEnable(GL_LINE_STIPPLE);
						glLineStipple(1, 0x3F3F);
						gluQuadricDrawStyle(qo, (GLenum) GLU_LINE);
						gluCylinder(qo, rad, rad, length, res, 1);
						glDisable(GL_LINE_STIPPLE);
						break;
						
						case BONDTYPE_TRIPLE:
						trans = rad;
						rad = rad / 2.0;
						
						if (n2)
							glTranslated(0.0, trans, 0.0);
						else
							glTranslated(0.0, -trans, 0.0);
						gluCylinder(qo, rad, rad, length, res, 1);
						if (n2)
							glTranslated(0.0, -trans, 0.0);
						else
							glTranslated(0.0, trans, 0.0);
						gluCylinder(qo, rad, rad, length, res, 1);
						if (n2)
							glTranslated(0.0, -trans, 0.0);
						else
							glTranslated(0.0, trans, 0.0);
						gluCylinder(qo, rad, rad, length, res,1);
						break;
						
						default:
						gluCylinder(qo, rad, rad, length, res, 1);
					}
					else
						gluCylinder(qo, rad, rad, length, res, 1);
					
					glPopMatrix();
					gluDeleteQuadric(qo);
					
					glPopName(); glPopName();
				}
			}
			
			glDisable(GL_LIGHTING);
		}
		
		// render the additional stuff related to SF.
		// render the additional stuff related to SF.
		// render the additional stuff related to SF.
		
		setup1_sf * susf = dynamic_cast<setup1_sf *>(current_setup);
		if (susf != NULL)
		{
			for (i32u n2 = 0;n2 < susf->hi_vector.size();n2++)	// visualize the helix4 hbonds...
			{
				vector<atom *> * vect = & susf->hi_vector[n2].cg_donacc;
				if (susf->united_atoms) vect = & susf->hi_vector[n2].ua_donacc;
				
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(1, 0x3333);
				
				glBegin(GL_LINES);
				glColor3f(0.20, 1.00, 0.10);
				
				for (i32u n3 = 0;n3 < (* vect).size() / 2;n3++)
				{
					const fGL * crd1 = (* vect)[n3 * 2 + 0]->GetCRD(n1);
					const fGL * crd2 = (* vect)[n3 * 2 + 1]->GetCRD(n1);
					
					glVertex3fv(crd1);
					glVertex3fv(crd2);
				}
				
				glEnd();
				glDisable(GL_LINE_STIPPLE);
			}
			
			if (susf->united_atoms)		// the UA-specific rendering starts here...
			{
				for (i32u n2 = 0;n2 < susf->sp_vector.size();n2++)
				{
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1, 0x3333);
					
					glBegin(GL_LINES);
					glColor3f(0.20, 1.00, 0.10);
					
					for (i32u n3 = 0;n3 < susf->sp_vector[n2].ua_donacc.size() / 2;n3++)
					{
						const fGL * crd1 = susf->sp_vector[n2].ua_donacc[n3 * 2 + 0]->GetCRD(n1);
						const fGL * crd2 = susf->sp_vector[n2].ua_donacc[n3 * 2 + 1]->GetCRD(n1);
						
						glVertex3fv(crd1);
						glVertex3fv(crd2);
					}
					
					glEnd();
					glDisable(GL_LINE_STIPPLE);
				}
			}
			else	// the CG-specific rendering starts here...
			{
				for (i32u n2 = 0;n2 < susf->sp_vector.size();n2++)
				{
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1, 0x3333);
					
					glBegin(GL_LINES);
					glColor3f(0.20, 1.00, 0.10);
					
					for (i32u n3 = 0;n3 < susf->sp_vector[n2].cg_straight.size() / 2;n3++)
					{
						const fGL * crd1 = susf->sp_vector[n2].cg_straight[n3 * 2 + 0]->GetCRD(n1);
						const fGL * crd2 = susf->sp_vector[n2].cg_straight[n3 * 2 + 1]->GetCRD(n1);
						
						glVertex3fv(crd1);
						glVertex3fv(crd2);
					}
					
					glEnd();
					glDisable(GL_LINE_STIPPLE);
				}
				
				for (/*i32u*/ n2 = 0;n2 < susf->sp_vector.size();n2++)
				{
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1, 0x1111);
					
					glBegin(GL_LINES);
					glColor3f(0.20, 1.00, 0.10);
					
					for (i32u n3 = 0;n3 < susf->sp_vector[n2].cg_crossed.size() / 2;n3++)
					{
						const fGL * crd1 = susf->sp_vector[n2].cg_crossed[n3 * 2 + 0]->GetCRD(n1);
						const fGL * crd2 = susf->sp_vector[n2].cg_crossed[n3 * 2 + 1]->GetCRD(n1);
						
						glVertex3fv(crd1);
						glVertex3fv(crd2);
					}
					
					glEnd();
					glDisable(GL_LINE_STIPPLE);
				}
				
				// protein chains...
				
				for (/*i32u*/ n2 = 0;n2 < susf->chn_vector.size();n2++)
				{
					for (i32s n3 = 0;n3 < ((i32s) susf->chn_vector[n2].res_vector.size()) - 1;n3++)
					{
						i32s ind1[3] = { n2, n3 + 0, 0 };
						i32s ind2[3] = { n2, n3 + 1, 0 };
						
						const fGL * crd1 = susf->chn_vector[ind1[0]].res_vector[ind1[1]].GetRefA(ind1[2])->GetCRD(n1);
						const fGL * crd2 = susf->chn_vector[ind2[0]].res_vector[ind2[1]].GetRefA(ind2[2])->GetCRD(n1);
						const fGL * crd[2] = { crd1, crd2 };
						
						fGL col1[4] = { 0.8, 0.8, 0.6, 1.0 };	// todo...
						fGL col2[4] = { 0.8, 0.8, 0.6, 1.0 };	// todo...
						const fGL * col[2] = { col1, col2 };
						
						fGL rad[2] =
						{
							susf->chn_vector[ind1[0]].res_vector[ind1[1]].GetRefA(ind1[2])->vdwr,
							susf->chn_vector[ind2[0]].res_vector[ind2[1]].GetRefA(ind2[2])->vdwr
						};
						
						if (gv->render == RENDER_WIREFRAME)
						{
							glBegin(GL_LINES);
							glColor3fv(col1); glVertex3fv(crd1);
							glColor3fv(col2); glVertex3fv(crd2);
							glEnd();
						}
						else if (gv->render != RENDER_NOTHING)
						{
							glEnable(GL_LIGHTING);
							DrawCylinder1(crd, col, rad);
							glDisable(GL_LIGHTING);
						}
					}
					{
					for (i32u n3 = 0;n3 < susf->chn_vector[n2].res_vector.size();n3++)
					{
						for (i32s n4 = 0;n4 < susf->chn_vector[n2].res_vector[n3].GetNumA() - 1;n4++)
						{
							i32s ind1[3] = { n2, n3, n4 + 0 };
							i32s ind2[3] = { n2, n3, n4 + 1 };
							
							const fGL * crd1 = susf->chn_vector[ind1[0]].res_vector[ind1[1]].GetRefA(ind1[2])->GetCRD(n1);
							const fGL * crd2 = susf->chn_vector[ind2[0]].res_vector[ind2[1]].GetRefA(ind2[2])->GetCRD(n1);
							const fGL * crd[2] = { crd1, crd2 };
							
							fGL col1[4] = { 0.6, 0.8, 0.8, 1.0 };	// todo...
							fGL col2[4] = { 0.6, 0.8, 0.8, 1.0 };	// todo...
							const fGL * col[2] = { col1, col2 };
							
							fGL rad[2] =
							{
								susf->chn_vector[ind1[0]].res_vector[ind1[1]].GetRefA(ind1[2])->vdwr,
								susf->chn_vector[ind2[0]].res_vector[ind2[1]].GetRefA(ind2[2])->vdwr
							};
							
							if (gv->render == RENDER_WIREFRAME)
							{
								glBegin(GL_LINES);
								glColor3fv(col1); glVertex3fv(crd1);
								glColor3fv(col2); glVertex3fv(crd2);
								glEnd();
							}
							else if (gv->render != RENDER_NOTHING)
							{
								glEnable(GL_LIGHTING);
								DrawCylinder1(crd, col, rad);
								glDisable(GL_LIGHTING);
							}
						}
					}
					}
				}
				
				// disulphide bridges.
				{
				for (i32s n2 = 0;n2 < (i32s) susf->dsb_vector.size();n2++)
				{
					i32s ind1[3] = { susf->dsb_vector[n2].chn[0], susf->dsb_vector[n2].res[0], 1 };
					i32s ind2[3] = { susf->dsb_vector[n2].chn[1], susf->dsb_vector[n2].res[1], 1 };
					
					const fGL * crd1 = susf->chn_vector[ind1[0]].res_vector[ind1[1]].GetRefA(ind1[2])->GetCRD(n1);
					const fGL * crd2 = susf->chn_vector[ind2[0]].res_vector[ind2[1]].GetRefA(ind2[2])->GetCRD(n1);
					const fGL * crd[2] = { crd1, crd2 };
					
					fGL col1[4] = { 1.0, 1.0, 0.0, 1.0 };	// todo...
					fGL col2[4] = { 1.0, 1.0, 0.0, 1.0 };	// todo...
					const fGL * col[2] = { col1, col2 };
					
					fGL rad[2] =
					{
						susf->chn_vector[ind1[0]].res_vector[ind1[1]].GetRefA(ind1[2])->vdwr,
						susf->chn_vector[ind2[0]].res_vector[ind2[1]].GetRefA(ind2[2])->vdwr
					};
					
					if (gv->render == RENDER_WIREFRAME)
					{
						glBegin(GL_LINES);
						glColor3fv(col1); glVertex3fv(crd1);
						glColor3fv(col2); glVertex3fv(crd2);
						glEnd();
					}
					else
					{
						glEnable(GL_LIGHTING);
						DrawCylinder1(crd, col, rad);
						glDisable(GL_LIGHTING);
					}
				}
				}
			}
		}
		
/*//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_LIGHTING); glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, true); glBegin(GL_QUADS);
	// do not take the direction from any array, but calculate it using N/C/O???
	for (iter_bl it1 = bond_list.begin();it1 != bond_list.end();it1++)	// sf peptide dipoles...
	{
		if ((* it1).sf_pbdd < -1000.0) continue;
		
	//char symbol2 = chn_vector[n2].res_vector[n3 + 1].symbol;
	//if (symbol2 == 'P') continue;	// skip all X-pro cases !!!
		
		atom * prev = NULL;
		atom * curr = (* it1).atmr[0];
		atom * next = (* it1).atmr[1];
		
		// WARNING!!! this is pretty slow!!! need to find the previous c-alpha.
		iter_cl it2;
		for (it2 = curr->cr_list.begin();it2 != curr->cr_list.end();it2++)
		{
			if ((* it2).atmr == next) continue;
			
			if ((* it2).atmr->el.GetAtomicNumber() > 0) continue;
			if ((* it2).atmr->sf_atmtp & 0xFF) continue;
			
			prev = (* it2).atmr;
			break;
		}
		
		if (!prev) continue;
		
		v3d<fGL> v1(prev->GetCRD(n1), curr->GetCRD(n1));
		v3d<fGL> v2(curr->GetCRD(n1), next->GetCRD(n1));
		
		v3d<fGL> v3 = v1.vpr(v2); v3 = v3 * (0.075 / v3.len());
		v3d<fGL> v4 = v3.vpr(v2); v4 = v4 * (0.075 / v4.len());
		
		fGL peptide = (* it1).sf_pbdd;	// this is the same for all crd_sets!!!
		v3d<fGL> v5 = (v3 * sin(peptide)) + (v4 * cos(peptide));
		
		fGL peptnorm = peptide - M_PI / 2.0;
		v3d<fGL> normal = (v3 * sin(peptnorm)) + (v4 * cos(peptnorm));
		normal = normal / normal.len(); glNormal3fv(normal.data);
		
		v3d<fGL> pvc(curr->GetCRD(n1));
		v3d<fGL> pv1 = pvc + (v2 * 0.5) + v5; v3d<fGL> pv2 = pvc + (v2 * 0.90);
		v3d<fGL> pv3 = pvc + (v2 * 0.5) - v5; v3d<fGL> pv4 = pvc + (v2 * 0.10);
		
		glColor3f(1.0, 0.0, 0.0); glVertex3fv(pv1.data);
		glColor3f(0.0, 1.0, 0.0); glVertex3fv(pv2.data);
		glColor3f(0.0, 0.0, 1.0); glVertex3fv(pv3.data);
		glColor3f(0.0, 1.0, 0.0); glVertex3fv(pv4.data);
	}
	glEnd();	// GL_QUADS
	glDisable(GL_LIGHTING); glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, false);
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////*/
		if (accum)
		{
			gv->cam->RenderObjects(gv);
			glAccum(GL_ACCUM, cs_vector[n1]->accum_value);
		}
	}
#endif
}

void project::Center(transformer * p1)
{
	i32s sum = 0;
	p1->GetLocDataRW()->crd[0] = 0.0;
	p1->GetLocDataRW()->crd[1] = 0.0;
	p1->GetLocDataRW()->crd[2] = 0.0;
#if 0
	for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
	{
		if (!((* it1).flags & ATOMFLAG_SELECTED)) continue;
		for (i32u n1 = 0;n1 < cs_vector.size();n1++)
		{
			sum++;
			const fGL * cdata = (* it1).GetCRD(n1);
			p1->GetLocDataRW()->crd[0] += cdata[0];
			p1->GetLocDataRW()->crd[1] += cdata[1];
			p1->GetLocDataRW()->crd[2] += cdata[2];
		}
	}
#endif
	if (!sum) return;
	
	p1->GetLocDataRW()->crd[0] /= (fGL) sum;
	p1->GetLocDataRW()->crd[1] /= (fGL) sum;
	p1->GetLocDataRW()->crd[2] /= (fGL) sum;

#if 0	
	for (/*iter_al*/ it1 = atom_list.begin();it1 != atom_list.end();it1++)
	{
		if (!((* it1).flags & ATOMFLAG_SELECTED)) continue;
		for (i32u n1 = 0;n1 < cs_vector.size();n1++)
		{
			const fGL * cdata = (* it1).GetCRD(n1);
			
			fGL x = cdata[0] - p1->GetLocData()->crd[0];
			fGL y = cdata[1] - p1->GetLocData()->crd[1];
			fGL z = cdata[2] - p1->GetLocData()->crd[2];
			
			(* it1).SetCRD(n1, x, y, z);
		}
	}
#endif
}

void project::Transform(transformer * p1)
{
	fGL matrix[16]; p1->GetMatrix(matrix);
#if 0
	for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++)
	{
		if (!((* it1).flags & ATOMFLAG_SELECTED)) continue;
		
		for (i32u n1 = 0;n1 < cs_vector.size();n1++)
		{
			v3d<fGL> posv = v3d<fGL>((* it1).GetCRD(n1));
			TransformVector(posv, matrix);
			
			(* it1).SetCRD(n1, posv[0], posv[1], posv[2]);
		}
	}
#endif
	UpdateAllGraphicsViews();	// re-draw the bonds across selection boundary!!!
}
void project::DrawEvent(graphics_view * gv, vector<iGLu> & names)
{
	if (ogl_view::button == mouse_tool::Right) return;	// the right button is for popup menus...
	
	i32s mouse[2] =
	{
		gv->current_tool->latest_x,
		gv->current_tool->latest_y
	};
	if (ogl_view::state == mouse_tool::Down)
	{
		if (names.size() > 1 && names[0] == GLNAME_MD_TYPE1)
		{
//			draw_data[0] = (atom *) names[1];
		}
		else
		{
			bool can_disable_depth_test = Object::CanDisableDepthTest();
			if (can_disable_depth_test)
			{
				Object::CanDisableDepthTest(false);
				UpdateAllViews(true);
			}

			if (ogl_view::what_to_draw == draw_tool::Griddata)
			{
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					if (m_pGridDataForDraw)
					{
						m_pGridDataForDraw->AddInput(pt3, m_pGridDataForDraw->GetColor());
						m_pGridDataForDraw->m_input_points.GetLastMsg().ZoomInv(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
							m_xd_zoom_center,
							m_yd_zoom_center,
							m_zd_zoom_center);
						DrawNewGridDataItem(dynamic_cast<SurfDoc *>(this), m_pGridDataForDraw);
						
						if (m_pGridDataForDraw->built)
							m_pGridDataForDraw->built = 2;


						this->UpdateAllViews();

						if (this->m_pLabDoc)
						{
							long id_surf = m_pGridDataForDraw->id_surf;											
							long id_point = m_pGridDataForDraw->m_input_points.GetLastMsg().id_point;
							double X = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().x;
							double Y = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().y;
							double Z = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().z;
							
							this->m_pLabDoc->AddGridData(id_obj, id_surf, id_point, X, Y, Z);
						}

					}
					else 
					{
						printf("!!!! this->m_pGridDataForDraw\n");
						MessageBox(0,"Вы не выбрали объект GridData для добавления точек","project::DrawEvent",0);
					}
					
				}
			}

			if (ogl_view::what_to_draw == draw_tool::Spheres)
			{
				//fGL tmp1[3]; gv->GetCRD(mouse, tmp1);
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					this->AddSphere(pt3,RGB(255,255,0));
					this->m_spheres.GetLastMsg().ZoomInv(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
						m_xd_zoom_center,
						m_yd_zoom_center,
						m_zd_zoom_center);
					DrawNewSphere(dynamic_cast<SurfDoc *>(this));
				}
			}
			if (ogl_view::what_to_draw == draw_tool::Line)
			{
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					//printf("if(calc_select_line\n");
					if(this->m_pLineForDraw)
					{
						printf("this->m_pLineForDraw\n");

						this->m_pLineForDraw->PushBack(pt3);
						this->m_pLineForDraw->ZoomInv(
							this->m_pLineForDraw->GetPointsNumber()-1,
							this->m_zoomX, this->m_zoomY, this->m_zoomZ,
							m_xd_zoom_center,
							m_yd_zoom_center,
							m_zd_zoom_center);

						this->CorrectDrawingPoint(this->m_pLineForDraw, this->m_pLineForDraw->GetPointsNumber()-1);



						this->m_pLineForDraw->ReDraw();
					}
					else 
					{
						printf("!!!! this->m_pLineForDraw\n");
						MessageBox(0,"You have not created empty line Object for draw\nFirst create this object and then you can draw a line","project::DrawEvent",0);
					}
				}
			}
//			atom newatom(element::current_element, tmp1, cs_vector.size());
//			Add_Atom(newatom); draw_data[0] = & atom_list.back();
			Object::CanDisableDepthTest(can_disable_depth_test);
		}
	}
	else
	{
		if (names.size() > 1 && names[0] == GLNAME_MD_TYPE1)
		{
//			draw_data[1] = (atom *) names[1];
		}
		else
		{
			//fGL tmp1[3]; gv->GetCRD(mouse, tmp1);
			//this->AddSphere(tmp1[0],tmp1[1],tmp1[2],RGB(255,0,255));
//			atom newatom(element::current_element, tmp1, cs_vector.size());
//			Add_Atom(newatom); draw_data[1] = & atom_list.back();
		}
		
		// if different: update bondtype or add a new bond.
		// if not different: change atom to different element.
#if 0	
		if (draw_data[0] != draw_data[1])
		{
			bond newbond(draw_data[0], draw_data[1], bondtype::current_bondtype);
			iter_bl it1 = find(bond_list.begin(), bond_list.end(), newbond);
			if (it1 != bond_list.end())
			{
				SystemWasModified();
				
				(* it1).bt = bondtype::current_bondtype;
				
				if (pv != NULL) pv->BondUpdateItem(& (* it1));
			}
			else AddBond(newbond);
		}
		else
		{
			SystemWasModified();
			
			draw_data[0]->el = element::current_element;
			draw_data[0]->mass = element::current_element.GetAtomicMass();		// also need to update these...
			draw_data[0]->vdwr = element::current_element.GetVDWRadius();		// also need to update these...
			
			if (pv != NULL) pv->AtomUpdateItem(draw_data[0]);
		}
#endif
		UpdateAllViews();
	}
}
void project::GDIplusDrawEvent(gdiplus_map_view * gv)//, vector<iGLu> & names)
{
	if (!gv) return;

	i32s mouse[2] =
	{
		gv->current_gdiplus_tool->latest_x,
		gv->current_gdiplus_tool->latest_y
	};

	BlnProfile3D * profile = dynamic_cast<BlnProfile3D *>(gv->GetObject());
	if (!profile) return;

	if (gdiplus_view::what_to_draw == draw_gdiplus_tool::GriddataAssign)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down
			&& 
			gdiplus_view::button == mouse_gdiplus_tool::Left)
		{			
			{
#if GDIPLUS_SELECTION_3D
				CPoint3 pt3;
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
				double dist_to_line = DBL_MAX;
				GridData * pGridData = NULL;
				if (profile->IsSelectedGridDataPoint(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected, pGridData)
					&& dist_to_line <= fabs(gv->lines_points_radius)
					)
#endif
				{
					if (m_pGridDataForDraw)
					{
						ThePoint3D * point = dynamic_cast<ThePoint3D *>(gdiplus_view::what_selected.GetObject());
						if (point && pGridData)
						{
							CPoint3 pt3_cpy;
							pt3_cpy.x = point->GetDocumentPoint(0).x;
							pt3_cpy.y = point->GetDocumentPoint(0).y;
							pt3_cpy.z = point->GetDocumentPoint(0).z;

							//Object * parent = point->GetObjectList()->GetParent();							
							long id_surf = pGridData->id_surf;										
							long id_point = point->id_point;						
							if (this->m_pLabDoc)
								this->m_pLabDoc->ClearGridDataPoint(id_obj, id_surf, id_point);

							gdiplus_view::what_selected.
								EraseSelectedObject<ThePoint3D>
								(hwndTV,Object::object_type::thepoint3d);

							if (pGridData->built)
								pGridData->built = 2;


							m_pGridDataForDraw->AddInput(pt3_cpy, m_pGridDataForDraw->GetColor());
							m_pGridDataForDraw->m_input_points.GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
								m_xd_zoom_center,
								m_yd_zoom_center,
								m_zd_zoom_center);
							DrawNewGridDataItem(dynamic_cast<SurfDoc *>(this), m_pGridDataForDraw);	

							if (m_pGridDataForDraw->built)
								m_pGridDataForDraw->built = 2;

							this->UpdateAllViews();

							if (this->m_pLabDoc)
							{
								long id_surf = m_pGridDataForDraw->id_surf;											
								long id_point = m_pGridDataForDraw->m_input_points.GetLastMsg().id_point;
								double X = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().x;
								double Y = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().y;
								double Z = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().z;
								
								this->m_pLabDoc->AddGridData(id_obj, id_surf, id_point, X, Y, Z);
							}
						}

					}
					else 
					{
						printf("!!!! this->m_pGridDataForDraw\n");
						MessageBox(0,"Вы не выбрали объект GridData для добавления точек","project::DrawEvent",0);
					}


					UpdateAllViews();

				}

			}
			//fGL tmp1[3]; gv->GetCRD(mouse, tmp1);
			CPoint3 pt3;
			if (gv->calc_select_line(mouse[0], mouse[1], pt3))
			{
				//this->m_pLineForDraw
			}
		}
	}

	if (gdiplus_view::what_to_draw == draw_gdiplus_tool::Griddata)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down
			&& 
			gdiplus_view::button == mouse_gdiplus_tool::Left)
		{			
			//fGL tmp1[3]; gv->GetCRD(mouse, tmp1);
			CPoint3 pt3;
			if (gv->calc_select_line(mouse[0], mouse[1], pt3))
			{
				//this->m_pLineForDraw
				if (m_pGridDataForDraw)
				{
					m_pGridDataForDraw->AddInput(pt3, m_pGridDataForDraw->GetColor());
					m_pGridDataForDraw->m_input_points.GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
						m_xd_zoom_center,
						m_yd_zoom_center,
						m_zd_zoom_center);
					DrawNewGridDataItem(dynamic_cast<SurfDoc *>(this), m_pGridDataForDraw);	

					if (m_pGridDataForDraw->built)
						m_pGridDataForDraw->built = 2;

					this->UpdateAllViews();

					if (this->m_pLabDoc)
					{
						long id_surf = m_pGridDataForDraw->id_surf;											
						long id_point = m_pGridDataForDraw->m_input_points.GetLastMsg().id_point;
						double X = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().x;
						double Y = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().y;
						double Z = m_pGridDataForDraw->m_input_points.GetLastMsg().GetFirstDocumentPoint().z;
						
						this->m_pLabDoc->AddGridData(id_obj, id_surf, id_point, X, Y, Z);
					}

				}
				else 
				{
					printf("!!!! this->m_pGridDataForDraw\n");
					MessageBox(0,"Вы не выбрали объект GridData для добавления точек","project::DrawEvent",0);
				}
			}
		}
	}

	if (gdiplus_view::what_to_draw == draw_gdiplus_tool::Spheres)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down
			&& 
			gdiplus_view::button == mouse_gdiplus_tool::Left)
		{			
			//fGL tmp1[3]; gv->GetCRD(mouse, tmp1);
			CPoint3 pt3;
			if (gv->calc_select_line(mouse[0], mouse[1], pt3))
			{
				this->AddSphere(pt3,RGB(255,255,0));
				this->m_spheres.GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
					m_xd_zoom_center,
					m_yd_zoom_center,
					m_zd_zoom_center);
				DrawNewSphere(dynamic_cast<SurfDoc *>(this));
				this->UpdateAllViews();
			}
		}
	}
	if (gdiplus_view::what_to_draw == draw_gdiplus_tool::Line)
	{
		if(gdiplus_view::button == mouse_gdiplus_tool::Left)
		{
			if (gdiplus_view::state == mouse_gdiplus_tool::Down
				||
				gdiplus_view::state == mouse_gdiplus_tool::DblClk)
			{	
				CPoint3 pt3;
				if (gv->calc_select_line(mouse[0], mouse[1], pt3))
				{
					//printf("if(calc_select_line\n");
					if(!this->m_pLineForDraw) 
					{
						//printf("!!!! this->m_pLineForDraw\n");
						//MessageBox(0,"You have not created empty line Object for draw\nFirst create this object and then you can draw a line","project::DrawEvent",0);
						if (gdiplus_view::state == mouse_gdiplus_tool::Down)
						{
							// create new line Object
							//void SetLineForDraw(Line3D* pLine){m_pLineForDraw = pLine;}
							this->SetLineForDraw(profile->AddLine());

							if (this->m_pLineForDraw)
							{
								this->m_pLineForDraw->SetNameDlg();
								return;
							}
						}
					}
					if(this->m_pLineForDraw)
					{
						//printf("this->m_pLineForDraw\n");
						if (this->m_pLineForDraw->GetPointsNumber() == 0)
						{	
							if (gdiplus_view::state == mouse_gdiplus_tool::Down)
							{
								for (int i = 0; i < 2; i++)
								{
									this->m_pLineForDraw->PushBack(pt3);
									this->m_pLineForDraw->Zoom(
										this->m_pLineForDraw->GetPointsNumber()-1,
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
										m_xd_zoom_center,
										m_yd_zoom_center,
										m_zd_zoom_center);
								}
							}
						}
						else
						{
							//printf("this->m_pLineForDraw->GetPointsNumber()\n");

							size_t index_of_last_point = this->m_pLineForDraw->GetPointsNumber()-1;

							if(gdiplus_view::state == mouse_gdiplus_tool::DblClk)
							{
								// do not Add second point
								//printf("gdiplus_view::state == mouse_gdiplus_tool::DblClk\n");
								this->m_pLineForDraw->ErasePoint(index_of_last_point);

							}
							else
							{
								this->m_pLineForDraw->GetDocumentPoint(index_of_last_point) = pt3;
								this->m_pLineForDraw->Zoom(
									index_of_last_point,
									this->m_zoomX, this->m_zoomY, this->m_zoomZ,
									m_xd_zoom_center,
									m_yd_zoom_center,
									m_zd_zoom_center);	

								this->m_pLineForDraw->PushBack(pt3);
								this->m_pLineForDraw->Zoom(
									this->m_pLineForDraw->GetPointsNumber()-1,
									this->m_zoomX, this->m_zoomY, this->m_zoomZ,
									m_xd_zoom_center,
									m_yd_zoom_center,
									m_zd_zoom_center);

								if (this->m_pLineForDraw->AddBrokePoints(profile))
								{
									this->m_pLineForDraw->Zoom(
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
										m_xd_zoom_center,
										m_yd_zoom_center,
										m_zd_zoom_center);
								}
							}
						}

						//this->CorrectDrawingPoint(this->m_pLineForDraw, this->m_pLineForDraw->GetPointsNumber()-1);

						this->m_pLineForDraw->ReDraw();
						if(gdiplus_view::state == mouse_gdiplus_tool::DblClk)
						{							
							//printf("gdiplus_view::state == mouse_gdiplus_tool::DblClk    2\n");
							this->m_pLineForDraw = NULL;
						}				
					}
				}
			}
		}
		if(gdiplus_view::button == mouse_gdiplus_tool::Right)
		{
			//printf("gdiplus_view::button == mouse_gdiplus_tool::Right\n");
			if (gdiplus_view::state == mouse_gdiplus_tool::Down)
			{	
			//printf("gdiplus_view::state == mouse_gdiplus_tool::Down\n");
				if(this->m_pLineForDraw)
				{
					//printf("this->m_pLineForDraw\n");
					if (this->m_pLineForDraw->GetPointsNumber() > 1)
					{
						//printf("this->m_pLineForDraw->GetPointsNumber()\n");

						size_t index_of_pre_last_point = this->m_pLineForDraw->GetPointsNumber()-2;
						this->m_pLineForDraw->ErasePoint(index_of_pre_last_point);
						this->m_pLineForDraw->ReDraw();
						UpdateAllMapViews();
					}				
				}
			}
		}
	}
}
void project::GDIplusDrawMotionEvent(gdiplus_map_view * gv/*, vector<iGLu> & names*/)
{
	if (!gv) return;
	if (gdiplus_view::button == mouse_gdiplus_tool::Right) return;	// the right button is for popup menus...

	i32s mouse[2] =
	{
		gv->current_gdiplus_tool->latest_x,
		gv->current_gdiplus_tool->latest_y
	};

	BlnProfile3D * profile = dynamic_cast<BlnProfile3D *>(gv->GetObject());
	if (!profile) return;

	if (gdiplus_view::what_to_draw == draw_gdiplus_tool::what_to_draw::Line)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
		{
			if (this->m_pLineForDraw)
			{
				if (this->m_pLineForDraw->GetPointsNumber() > 1)
				{			
					size_t index_of_last_point = this->m_pLineForDraw->GetPointsNumber()-1;
					if(gv->calc_select_line(mouse[0], mouse[1], this->m_pLineForDraw->GetDocumentPoint(index_of_last_point)))
					{
						this->m_pLineForDraw->Zoom(index_of_last_point,
							this->m_zoomX, this->m_zoomY, this->m_zoomZ,
								m_xd_zoom_center,
								m_yd_zoom_center,
								m_zd_zoom_center);

						this->m_pLineForDraw->ReDrawWithoutTree();
						UpdateAllMapViews();		
					}
				}
			}
		}
	}
}





void project::GDIplusDrawKeyButtonEvent(gdiplus_map_view * gv/*, vector<iGLu> & names*/)
{
	if (!gv) return;

	if (gdiplus_view::what_to_draw == draw_gdiplus_tool::what_to_draw::Line)
	{
		if (this->m_pLineForDraw)
		{
			if (this->m_pLineForDraw->GetPointsNumber() > 1)
			{	
				size_t index_of_last_point = this->m_pLineForDraw->GetPointsNumber()-1;

				this->m_pLineForDraw->ErasePoint(index_of_last_point);
				
				this->m_pLineForDraw->ReDraw();
				UpdateAllMapViews();
				this->m_pLineForDraw = NULL;
			}
		}
	}
}





bool project::CorrectDrawingPoint(Object *pObject, int pointIndex)
{
	if(pObject && pObject->GetParent()) 
	{
		Primitive3D<CPoint3> * primitive3 
			= dynamic_cast<Primitive3D<CPoint3>*>
			(pObject);

		switch(pObject->GetParent()->GetObjectType())
		{
		case Object::object_type::bln_profile3d:
            {
				BlnProfile3D * bln_profile 
					= dynamic_cast<BlnProfile3D *>
					(pObject->GetParent());
				if (bln_profile && primitive3)
				{
					CPoint3 out = primitive3->GetDocumentPoint(pointIndex);
					//printf("in  = [%f %f %f]\n", out.x,out.y,out.z);
					if (bln_profile->m_plane.Projection(
						primitive3->GetDocumentPoint(pointIndex), 
						out))
					{
						//printf("out = [%f %f %f]\n", out.x,out.y,out.z);
						primitive3->GetDocumentPoint(pointIndex) = out;
						primitive3->Zoom(pointIndex,
							this->m_zoomX, this->m_zoomY, this->m_zoomZ,
							m_xd_zoom_center,
							m_yd_zoom_center,
							m_zd_zoom_center);

						if (primitive3->AddBrokePoints(bln_profile))
						{
							primitive3->Zoom(
								this->m_zoomX, this->m_zoomY, this->m_zoomZ,
								m_xd_zoom_center,
								m_yd_zoom_center,
								m_zd_zoom_center);
						}

						return true;
					}
					return false;
				}
				return false;
			}
			break;
		}
	}
	return true;
}

bool project::CorrectDrawingPoint(Object *pObject, CPoint3 & pt_doc)
{
	CPoint3 pt_in = pt_doc;
	if(pObject && pObject->GetParent()) 
	{
		switch(pObject->GetParent()->GetObjectType())
		{
		case Object::object_type::bln_profile3d:
            {
				BlnProfile3D * bln_profile 
					= dynamic_cast<BlnProfile3D *>
					(pObject->GetParent());

				if (bln_profile)
				{
					if (bln_profile->m_plane.Projection(
						pt_in, 
						pt_doc))
					{
						/*if (to_add_broke_points)
						{
							Primitive3D<CPoint3> * primitive3 = dynamic_cast<Primitive3D<CPoint3>*>(pObject);	
							if (primitive3->AddBrokePoints(bln_profile))
							{
								primitive3->Zoom(
									this->m_zoomX, this->m_zoomY, this->m_zoomZ,
									m_xd_zoom_center,
									m_yd_zoom_center,
									m_zd_zoom_center);
							}
						}*/
						return true;
					}
					return false;
				}
				return false;
			}
			break;
		}
	}
	return true;
}
void project::EraseEvent(graphics_view * gv, vector<iGLu> & names)
{
	if (ogl_view::button == mouse_tool::Right) return;	// the right button is for popup menus...
//printf("project::EraseEvent\n");
	
	i32s mouse[2] =
	{
		gv->current_tool->latest_x,
		gv->current_tool->latest_y
	};

	if (ogl_view::state == mouse_tool::Down)
	{
		/*if (names.size() > 1 && names[0] == GLNAME_MD_TYPE1)
		{
//			draw_data[0] = (atom *) names[1];
		}
		else*/
		{

			if (ogl_view::what_to_erase == erase_tool::Griddata)
			{
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					GridData * pGridData = NULL;
					if (this->IsSelectedGridDataPoint(pt3, this->m_sphere_radius, ogl_view::what_selected, pGridData))
					{
						if (this->m_pLabDoc)
						{
							ThePoint3D * point = dynamic_cast<ThePoint3D *>(ogl_view::what_selected.GetObject());
							if (point && pGridData)
							{
								//Object * parent = point->GetObjectList()->GetParent();
								long id_surf = pGridData->id_surf;
								long id_point = point->id_point;
								this->m_pLabDoc->ClearGridDataPoint(id_obj, id_surf, id_point);

								if (pGridData->built)
									pGridData->built = 2;

							}
						}

						ogl_view::what_selected.
							EraseSelectedObject<ThePoint3D>
							(hwndTV,Object::object_type::thepoint3d);
						UpdateAllViews();

					}
				}
			}

			if (ogl_view::what_to_erase == erase_tool::Spheres)
			{
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
					{
						ogl_view::what_selected.
							EraseSelectedObject<Sphere3D>
							(hwndTV,Object::object_type::sphere3d);
						UpdateAllViews();

					}
				}
			}
			if (ogl_view::what_to_erase == erase_tool::Line)
			{
				ogl_view::what_selected.m_what_to_select = 
					WhatSelected::selected_objects_element_type::sel_no_element;
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
					{
						ogl_view::what_selected.
							EraseSelectedObject<Line3D>
							(hwndTV,Object::object_type::line3d);
						UpdateAllViews();

					}
				}
			}
			if (ogl_view::what_to_erase == erase_tool::Lines_point)
			{
				ogl_view::what_selected.m_what_to_select = 
					WhatSelected::selected_objects_element_type::sel_point;
				CPoint3 pt3;
				if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
						pt3))
				{
					if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
					{
						ogl_view::what_selected.PrintInfo();
						if (ogl_view::what_selected.GetObject())
						{
							if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
							{
								Line3D * pline = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
								if (ogl_view::what_selected.m_selected_objects_element_type == WhatSelected::selected_objects_element_type::sel_point)
								{
									if (ogl_view::what_selected.GetIndex() > -1)
									{
										pline->ErasePoint(ogl_view::what_selected.GetIndex());
										pline->ReDraw();
									}
								}
							}
						}
					}
				}
			}
		}
	}
#if 0
	else
	{
		if (names.size() > 1 && names[0] == GLNAME_MD_TYPE1)
		{
//			draw_data[1] = (atom *) names[1];
		}
		else
		{
//			draw_data[1] = NULL;
		}
		
		if (!draw_data[0] || !draw_data[1]) return;
		
		// if different: try to find and remove a bond.
		// if not different: remove atom.
		if (draw_data[0] != draw_data[1])
		{
			bond tmpbond(draw_data[0], draw_data[1], bondtype::current_bondtype);
			iter_bl it1 = find(bond_list.begin(), bond_list.end(), tmpbond);
			if (it1 != bond_list.end()) RemoveBond(it1); else return;
		}
		else
		{
			iter_al it1 = find(atom_list.begin(), atom_list.end(), (* draw_data[0]));
			if (it1 != atom_list.end())
			{
				RemoveAtom(it1);
				
				// removing an atom will cause changes in atom indexing -> must update all atoms and bonds in pv!!!
				// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				
				for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++) if (pv != NULL) pv->AtomUpdateItem(& (* it1));
				{
				for (iter_bl it1 = bond_list.begin();it1 != bond_list.end();it1++) if (pv != NULL) pv->BondUpdateItem(& (* it1));
				}
			}
			else
			{
				cout << "BUG: project::EraseEvent()." << endl;
				exit(EXIT_FAILURE);
			}
		}
		//DrawScene(dynamic_cast<SurfDoc *>(this));
//		if (ogl_view::what_to_erase == erase_tool::Spheres)
//			DrawSpheres(dynamic_cast<SurfDoc *>(this));
//		if (ogl_view::what_to_erase == erase_tool::Line)
//			DrawLines(dynamic_cast<SurfDoc *>(this));
//		if (ogl_view::what_to_erase == erase_tool::Lines_point)
//			DrawLines(dynamic_cast<SurfDoc *>(this));

		//DrawLines(dynamic_cast<SurfDoc *>(this));

		//this->ZoomView();
		UpdateAllViews();
	}
#endif
}


void project::GDIplusEraseEvent(gdiplus_map_view * gv/*, vector<iGLu> & names*/)
{
	BlnProfile3D * profile = dynamic_cast<BlnProfile3D *>(gv->GetObject());
	if (!profile) return;

	if (gdiplus_view::button == mouse_tool::Right) return;	// the right button is for popup menus...
//printf("project::GDIplusEraseEvent\n");
	
	i32s mouse[2] =
	{
		gv->current_gdiplus_tool->latest_x,
		gv->current_gdiplus_tool->latest_y
	};

	if (gdiplus_view::state == mouse_gdiplus_tool::Down)
	{
		/*if (names.size() > 1 && names[0] == GLNAME_MD_TYPE1)
		{
//			draw_data[0] = (atom *) names[1];
		}
		else*/
		{

			if (gdiplus_view::what_to_erase == erase_gdiplus_tool::Griddata)
			{
#if GDIPLUS_SELECTION_3D
				CPoint3 pt3;
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
				double dist_to_line = DBL_MAX;
				GridData * pGridData = NULL;
				if (profile->IsSelectedGridDataPoint(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected, pGridData)
					&& dist_to_line <= fabs(gv->lines_points_radius)
					)
#endif
				{
					if (this->m_pLabDoc)
					{
						ThePoint3D * point = dynamic_cast<ThePoint3D *>(gdiplus_view::what_selected.GetObject());
						if (point && pGridData)
						{
							//Object * parent = point->GetObjectList()->GetParent();							
							long id_surf = pGridData->id_surf;										
							long id_point = point->id_point;						
							this->m_pLabDoc->ClearGridDataPoint(id_obj, id_surf, id_point);



							if (pGridData->built)
								pGridData->built = 2;

						}
					}

					gdiplus_view::what_selected.
						EraseSelectedObject<ThePoint3D>
						(hwndTV,Object::object_type::thepoint3d);
					UpdateAllViews();

				}

			}
			if (gdiplus_view::what_to_erase == erase_gdiplus_tool::Spheres)
			{
#if 0
				CPoint3 pt3;
#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
				double dist_to_line = DBL_MAX;
				if (profile->IsSelectedSphere(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected)
					&& dist_to_line <= fabs(gv->lines_points_radius)
					)
#endif
				{
					if (this->IsSelected(pt3,this->m_sphere_radius,gdiplus_view::what_selected))
					{
						gdiplus_view::what_selected.
							EraseSelectedObject<Sphere3D>
							(hwndTV,Object::object_type::sphere3d);
						UpdateAllViews();

					}
				}
#endif
			}
			if (gdiplus_view::what_to_erase == erase_gdiplus_tool::Line)
			{
				gdiplus_view::what_selected.m_what_to_select = 
					WhatSelected::selected_objects_element_type::sel_no_element;	
				CPoint3 pt3;
#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && 
					profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
				double dist_to_line = DBL_MAX;
				if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected)
					&& dist_to_line <= fabs(gv->lines_points_radius)
					)
#endif
				{
					//if (this->IsSelected(pt3,this->m_sphere_radius,gdiplus_view::what_selected))
					{
						gdiplus_view::what_selected.
							EraseSelectedObject<Line3D>
							(hwndTV,Object::object_type::line3d);
						UpdateAllViews();

					}
				}
			}
			if (gdiplus_view::what_to_erase == erase_gdiplus_tool::Lines_point)
			{
				ogl_view::what_selected.m_what_to_select = 
					WhatSelected::selected_objects_element_type::sel_point;
				CPoint3 pt3;
#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && 
					profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
				double dist_to_line = DBL_MAX;
				if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected)
					&& dist_to_line <= fabs(gv->lines_points_radius)
					)
#endif
				{
					//if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
					{
						ogl_view::what_selected.PrintInfo();
						if (ogl_view::what_selected.GetObject())
						{
							if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
							{
								Line3D * pline = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
								if (pline && ogl_view::what_selected.m_selected_objects_element_type == WhatSelected::selected_objects_element_type::sel_point)
								{
									if (ogl_view::what_selected.GetIndex() > -1)
									{
										pline->ErasePoint(ogl_view::what_selected.GetIndex());
										pline->ReDraw();
									}
								}
							}
						}
					}
				}
			}
			if (gdiplus_view::what_to_erase == erase_gdiplus_tool::Well_remove_sloj)
			{
//printf("erase_gdiplus_tool::Well_remove_sloj\n");
				gdiplus_view::what_selected.m_what_to_select = 
					WhatSelected::selected_objects_element_type::sel_point;
				CPoint3 pt3;
#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
				double dist_to_line = DBL_MAX;
				if (profile->IsSelectedWell(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected)
					&& dist_to_line <= fabs(gv->lines_points_radius)
					)
#endif
				{
//printf("IsSelectedWell\n");
					//if (this->IsSelected(pt3,this->m_sphere_radius,gdiplus_view::what_selected))
					{
						gdiplus_view::what_selected.PrintInfo();
						if (gdiplus_view::what_selected.GetObject())
						{
							if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::well_3d)
							{
								Well_3D * pwell = dynamic_cast<Well_3D*>(gdiplus_view::what_selected.GetObject());
								if (gdiplus_view::what_selected.m_selected_objects_element_type == WhatSelected::selected_objects_element_type::sel_point)
								{
									if (gdiplus_view::what_selected.GetIndex() > -1)
									{
										pwell->ErasePoint(gdiplus_view::what_selected.GetIndex());
										pwell->ReDraw();
									}
								}
							}
						}
					}
				}
			}
		}
	}
#if 0
	else
	{
		if (names.size() > 1 && names[0] == GLNAME_MD_TYPE1)
		{
//			draw_data[1] = (atom *) names[1];
		}
		else
		{
//			draw_data[1] = NULL;
		}
		
		if (!draw_data[0] || !draw_data[1]) return;
		
		// if different: try to find and remove a bond.
		// if not different: remove atom.
		if (draw_data[0] != draw_data[1])
		{
			bond tmpbond(draw_data[0], draw_data[1], bondtype::current_bondtype);
			iter_bl it1 = find(bond_list.begin(), bond_list.end(), tmpbond);
			if (it1 != bond_list.end()) RemoveBond(it1); else return;
		}
		else
		{
			iter_al it1 = find(atom_list.begin(), atom_list.end(), (* draw_data[0]));
			if (it1 != atom_list.end())
			{
				RemoveAtom(it1);
				
				// removing an atom will cause changes in atom indexing -> must update all atoms and bonds in pv!!!
				// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				
				for (iter_al it1 = atom_list.begin();it1 != atom_list.end();it1++) if (pv != NULL) pv->AtomUpdateItem(& (* it1));
				{
				for (iter_bl it1 = bond_list.begin();it1 != bond_list.end();it1++) if (pv != NULL) pv->BondUpdateItem(& (* it1));
				}
			}
			else
			{
				cout << "BUG: project::EraseEvent()." << endl;
				exit(EXIT_FAILURE);
			}
		}
		//DrawScene(dynamic_cast<SurfDoc *>(this));
//		if (gdiplus_view::what_to_erase == erase_tool::Spheres)
//			DrawSpheres(dynamic_cast<SurfDoc *>(this));
//		if (gdiplus_view::what_to_erase == erase_tool::Line)
//			DrawLines(dynamic_cast<SurfDoc *>(this));
//		if (gdiplus_view::what_to_erase == erase_tool::Lines_point)
//			DrawLines(dynamic_cast<SurfDoc *>(this));

		//DrawLines(dynamic_cast<SurfDoc *>(this));

		//this->ZoomView();
		UpdateAllViews();
	}
#endif
}

template <class T> void EraseObject(HWND hwndTV, T * pob, 
									Object::object_type ob_type
									) 
{
	//this->PrintInfo();
	if (pob)
	{
		ObjectList * oblist = pob->GetObjectList();
		void * pContainer = pob->GetObjectList()->GetContainer();
		Object * parent = pob->GetObjectList()->GetParent();

		if (oblist && pContainer && parent && pob->GetObjectType() == ob_type)
		{
			if (pob && pContainer)
			{
				if (oblist->GetContainerType() == Object::container_type::container_vect)
				{
					vect<T> * pvect = reinterpret_cast<vect<T> *>(pContainer);
					if(TreeView_DeleteItem(hwndTV, pob->myTreeItem))
					{
						if (pvect->SetCurrentMsgOnFirst())
						{
							do
							{
								//if (!pvect->CheckCurrentMsg()) break;
								if (pob == &pvect->GetCurrentMsg())
								{
									pvect->EraseCurrentMsg();
									break;
								}
							}
							while(pvect->IncrementCurrentMsg());
						}
						oblist->Init(*pvect, parent);
					}
				}
			}
		}
	}
};



/*#if 0
#define MyEditEvent GDIplusEditEvent
#define NAMES
#define current_my_tool current_gdiplus_tool
#define my_view gdiplus_map_view
#define edit_my_tool edit_gdiplus_tool
#define mouse_my_tool mouse_gdiplus_tool
#include "project_events.h"

#define MyEditEvent EditEvent
#define NAMES , vector<iGLu> & names
#define current_my_tool current_tool
#define my_view graphics_view
#define edit_my_tool edit_tool
#define mouse_my_tool mouse_tool
#include "project_events.h"
#else*/
void ResetZoomRedraw(project * prj, GridDataPointRef * gdpr, double z)
{
printf("ResetZoomRedraw()\n");
	GridData * pGridData = prj->FindGridData(gdpr->id_surf);
printf("gdpr->id_surf = %d\n", gdpr->id_surf);
	if (pGridData)
	{
printf("if (pGridData)\n");
		ThePoint3D * _pt = pGridData->FindThePoint3D(gdpr->id_point);
printf("gdpr->id_point = %d\n", gdpr->id_point);
		if (_pt && _pt->GetPointsNumber())
		{
printf("_pt && _pt->GetPointsNumber()\n");
			_pt->GetDocumentPoint(0).z = z;
			_pt->Primitive3D<CPoint3>::Zoom(
				prj->m_zoomX, prj->m_zoomY, prj->m_zoomZ,
				prj->m_xd_zoom_center,
				prj->m_yd_zoom_center,
				prj->m_zd_zoom_center);
			_pt->ReDraw();

			if (prj->GetLabDoc())
			{
				prj->GetLabDoc()->EditGridData(prj->Get_ID_OBJ(), gdpr->id_surf, gdpr->id_point,
					_pt->GetDocumentPoint(0).x,
					_pt->GetDocumentPoint(0).y,
					_pt->GetDocumentPoint(0).z);


			}
		}
	}
}


void project::LabNumberResetting(WellColomn * IGE_WellColomn, Well_3D * pwell, CPoint3 & ustje, int sel_ind)
{
	vector<lab_numbers_reset_item> lab_numbers_reset_items;

	typedef Well_IGE_Podoshva * Well_IGE_Podoshva_POINTER;

	Well_IGE_Podoshva_POINTER ige_well_elements[2];

	ige_well_elements[0] = 
		dynamic_cast<Well_IGE_Podoshva *>
		(IGE_WellColomn->well_elements[sel_ind]);
	ige_well_elements[1] = 
		dynamic_cast<Well_IGE_Podoshva *>
		(IGE_WellColomn->well_elements[sel_ind+1]);

	typedef LabLayer * LAB_LAYER_POINTER;

	LAB_LAYER_POINTER lab_layers[] = {NULL, NULL};

	if (ige_well_elements[0] && ige_well_elements[1])
	{
		for (vector<LabLayer *>::iterator 
			it_layer = this->m_laboratory.m_layers.begin();
			it_layer != this->m_laboratory.m_layers.end();
		it_layer++)
		{
			if ((*it_layer))
			{
				for (short i = 0; i < 2; i++) 
				{
					if ((*it_layer)->id_ige == ige_well_elements[i]->Get_ID_IGE())
					{
						lab_layers[i] = (*it_layer);
					}															
				}
			}
		}
		if (lab_layers[0] && lab_layers[1])
		{
			short i_another_layer = 1;
			for (short i_layer = 0; i_layer < 2; i_layer++, i_another_layer--) 
			{
				//long lab_layer_id_ige = lab_layers[i_layer]->id_ige;

				for (vector<LabNumber*>::iterator 
					it_number = lab_layers[i_layer]->lab_numbers.begin();
					it_number != lab_layers[i_layer]->lab_numbers.end();
				it_number++)
				{
					LabNumber * lab_number = (*it_number); 
					
					if (lab_number->id_kt == pwell->GetIdKt())
					{
						double H = lab_number->depth;

						//long lab_number_id_ige = lab_number->id_ige;


						double setLito_m_H0 = ustje.z - ige_well_elements[i_layer]->zk;//альтитуда кровли
						double setLito_m_H1 = ustje.z - ige_well_elements[i_layer]->zp;//альтитуда подошвы


						if (H > setLito_m_H0 && H <= setLito_m_H1)
						{
							// здесь мы по разбивке нашли, что текущий лабораторный номер 
							// по глубине попал в уже изменённый интервал
							// ige_well_elements[i_layer] поэтому ничего не меняем
						}
						else
						{
							// иначе 
							// произошло перепопадание номера в другой ИГЭ
							lab_numbers_reset_item lnri;

							//lnri.lab_number = lab_number;
							//lnri.old_lablayer = lab_number->lab_layer;
							//lnri.new_lablayer = lab_layers[i_layer];
							//lnri.new_id_ige = lab_layer_id_ige;

							lnri.lab_number_n = lab_number->lab_n;
							lnri.old_lablayer_id_ige = lab_layers[i_layer]->id_ige;
							lnri.new_lablayer_id_ige = lab_layers[i_another_layer]->id_ige;

							lab_numbers_reset_items.push_back(lnri);															
						}
					}
				}
			}
			this->LabNumberResetting(lab_numbers_reset_items);
			this->WellElementsResetting(pwell, lab_numbers_reset_items);
			if (this->GetLabDoc())
			{
				this->GetLabDoc()->LabNumberResetting(lab_numbers_reset_items);
			}
		}
	}
}

void project::LabNumberResetting(vector<lab_numbers_reset_item> & lab_numbers_reset_items)
{
	for (vector<lab_numbers_reset_item>::iterator 
		it_item = lab_numbers_reset_items.begin();
		it_item != lab_numbers_reset_items.end();
	it_item++)
	{


		LabLayer * old_lablayer = NULL;
		LabLayer * new_lablayer = NULL;
		for (vector<LabLayer *>::iterator 
			it_lablayer = this->m_laboratory.m_layers.begin();
			it_lablayer != this->m_laboratory.m_layers.end();
		it_lablayer++)
		{
			if ((*it_lablayer) && (*it_lablayer)->id_ige == (*it_item).old_lablayer_id_ige)
			{
				old_lablayer = (*it_lablayer);
			}
			if ((*it_lablayer) && (*it_lablayer)->id_ige == (*it_item).new_lablayer_id_ige)
			{
				new_lablayer = (*it_lablayer);
			}
		}

		LabNumber * lab_number = NULL;
		if (old_lablayer && new_lablayer)
		{
			vector<LabNumber*>::iterator it_to_erase = 
			old_lablayer->lab_numbers.begin();
			for ( ; it_to_erase != old_lablayer->lab_numbers.end();
				it_to_erase++)
			{
				if ((*it_to_erase) && (*it_to_erase)->lab_n == (*it_item).lab_number_n)
				{
					lab_number = (*it_to_erase);

					old_lablayer->lab_numbers.erase(it_to_erase);
					bool inserted = false;
					if (true)
					{
						if (new_lablayer->lab_numbers.size() > 1)
						{
							vector<LabNumber*>::iterator it_to_insert_1 = new_lablayer->lab_numbers.begin();
							vector<LabNumber*>::iterator it_to_insert_2 = it_to_insert_1 + 1;
							for ( ; it_to_insert_1 != new_lablayer->lab_numbers.end() 
								&& it_to_insert_2 != new_lablayer->lab_numbers.end();
								it_to_insert_1++, it_to_insert_2++)
							{
								if ((*it_to_insert_1) && (*it_to_insert_2))
								{
									if ( (*it_to_insert_1)->lab_n > (*it_item).lab_number_n
										&& (*it_to_insert_2)->lab_n > (*it_item).lab_number_n)
									{
										new_lablayer->lab_numbers.insert(it_to_insert_1, lab_number);
										inserted = true;
										break;
									}
									else 
									if ( (*it_to_insert_1)->lab_n < (*it_item).lab_number_n
										&& (*it_to_insert_2)->lab_n > (*it_item).lab_number_n)
									{
										new_lablayer->lab_numbers.insert(it_to_insert_2, lab_number);
										inserted = true;
										break;
									}
									if ( (*it_to_insert_1)->lab_n < (*it_item).lab_number_n
										&& (*it_to_insert_2)->lab_n < (*it_item).lab_number_n)
									{
										new_lablayer->lab_numbers.push_back(lab_number);
										inserted = true;
										break;
									}
								}
							}
						}
						else
						if (new_lablayer->lab_numbers.size() == 1)
						{
							vector<LabNumber*>::iterator it_to_insert = new_lablayer->lab_numbers.begin();
							for ( ; it_to_insert != new_lablayer->lab_numbers.end();
								it_to_insert++)
							{
								if ((*it_to_insert))
								{
									if ( (*it_to_insert)->lab_n > (*it_item).lab_number_n)
									{
										new_lablayer->lab_numbers.insert(it_to_insert, lab_number);
										inserted = true;
										break;
									}
									else 
									{
										new_lablayer->lab_numbers.push_back(lab_number);
										inserted = true;
										break;
									}
								}
							}
						}
					}
					if (!inserted) 
						new_lablayer->lab_numbers.push_back(lab_number);

					lab_number->id_ige = (*it_item).new_lablayer_id_ige;
					lab_number->lab_layer = new_lablayer;



					old_lablayer->Normatives(NULL,NULL);
					new_lablayer->Normatives(NULL,NULL);


					break;
				}
			}
		}
		
	}
	
}

void project::WellElementsResetting(Well_3D * pwell, vector<lab_numbers_reset_item> & lab_numbers_reset_items)
{
	if (pwell)
	{
		WellColomn * Lab_WellColomn = NULL;
		for (vector<WellColomn>::iterator it_c = pwell->well_colomns.begin();
			it_c != pwell->well_colomns.end(); it_c++)
		{
			if ( (*it_c).GetWellElementType() == WellElement::type::laboratory_analizes)
			{
				Lab_WellColomn = &(*it_c);
			}		
		}

		for (vector<lab_numbers_reset_item>::iterator 
			it_item = lab_numbers_reset_items.begin();
			it_item != lab_numbers_reset_items.end();
		it_item++)
		{
			if (Lab_WellColomn)
			{
				for (vector<WellElement*>::iterator 
					it_lab_elm = Lab_WellColomn->well_elements.begin();
					it_lab_elm != Lab_WellColomn->well_elements.end();
				it_lab_elm++)
				{
					Well_Laboratory_Analize * wla = dynamic_cast<Well_Laboratory_Analize *>(*it_lab_elm);
					if (wla && wla->lab_number && 
						wla->lab_number->lab_n == (*it_item).lab_number_n)
					{
						wla->ReInitByOwnLabNumber();						
					}
				}
			}		
		}
	}	
}

void project::GDIplusEditEvent(gdiplus_map_view * gv/*, vector<iGLu> & names*/)
{
	if (!gv) return;
	if (gdiplus_view::button == mouse_gdiplus_tool::Right) return;	// the right button is for popup menus...
		
//printf("void project::GDIplusEditEvent(gdiplus_map_view * gv)\n");
	
	i32s mouse[2] =
	{
		gv->current_gdiplus_tool->latest_x,
		gv->current_gdiplus_tool->latest_y
	};

	if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
	{
		edit_zp_lito = NULL;
		edit_zp_ige = NULL;

		edit_zk_lito = NULL;
		edit_zk_ige = NULL;

		edit_point = NULL;
		to_edit_line = false;
		to_insert = false;
	}

//	double epsilon = 0.000001;
				
	BlnProfile3D * profile = dynamic_cast<BlnProfile3D *>(gv->GetObject());
	if (!profile) return;
				
	double dist_to_object = DBL_MAX;				
	double search_radius = 3.0 * this->m_sphere_radius / (this->m_zoomX + this->m_zoomY + this->m_zoomZ);

	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Line)
	{
		//if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Line_by_moving_existing_point)
		//{
		//printf("edit_gdiplus_tool::Line\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{		
//printf("if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)\n");
			// если мы попали мышью по объекту
#if GDIPLUS_SELECTION_3D
			if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
			double dist_to_line = DBL_MAX;
			if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected)
				&& dist_to_line <= fabs(gv->lines_points_radius)
				)
#endif
			{
//printf("if (profile->IsSelectedDoc\n");
				gdiplus_view::what_selected.PrintInfo();

				gdiplus_view::what_selected.PrintInfo();
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_point
					&& gdiplus_view::what_selected.GetObject())
				{	
//printf("if (m_selected_objects_element_type == sel_point\n");
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
//printf("if (this->IsPrimitive3()\n");
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
//printf("if (primitive3)\n");
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
//printf("if GetIndex() CPOINT3_FLAG_HIDE\n");
								edit_point = &primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								
								/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								// HIDE POINT - включаем 3-й бит 
								// в пользовательских данных point 
								ptd.flag |= CPOINT3_FLAG_HIDE;
								gdiplus_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
								Line3D::s_line3d_draw_mode = old_line3d_draw_mode;*/

//printf("pre ReDraw %s\n", Object::ObjectTypeToString(gdiplus_view::what_selected.GetObject()->GetObjectType()));

								gdiplus_view::what_selected.GetObject()->ReDraw();
								UpdateAllViews();
								return;
							}
						}
					}
				}
		
			}

#if !GDIPLUS_SELECTION_3D
			else
			{
				printf("dist_to_line = %f\n", dist_to_line);
			}
#endif

		}
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
		{
//printf("edit_gdiplus_tool::Line Up\n");
			if( gdiplus_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_point
				&& gdiplus_view::what_selected.GetObject())
			{
				if (edit_point)
				{
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								
								if(gv->calc_select_line(mouse[0], mouse[1], pt3))
								{
									*edit_point = pt3;
									primitive3->Zoom(gdiplus_view::what_selected.GetIndex(),
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
											m_xd_zoom_center,
											m_yd_zoom_center,
											m_zd_zoom_center);

									//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
									//	gdiplus_view::what_selected.GetIndex());

								}

								/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								// UN HIDE POINT - выключаем 3-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE;
								gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
*/
								gdiplus_view::what_selected.GetObject()->ReDraw();

								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}
		//if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Line_by_add_new_point)
		//{
		//printf("edit_gdiplus_tool::Line_by_add_new_point\n");
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;


		// при нажатии кнопки мыши
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{			
			// если мы попали мышью по объекту
#if GDIPLUS_SELECTION_3D
			if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
			double dist_to_line = DBL_MAX;
			if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected) && dist_to_line <= fabs(gv->lines_points_radius))
#endif
			{
				gdiplus_view::what_selected.PrintInfo();
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_line
					&& gdiplus_view::what_selected.GetObject())
				{	
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								//printf("to_edit = true\n");
								to_edit_line = true;
								to_insert = true;
								//edit_point = &primitive3->GetViewPoint(gdiplus_view::what_selected.GetIndex());
								/*
								CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								// HIDE LINE - включаем 4-й бит 
								// в пользовательских данных point 
								ptd.flag |= CPOINT3_FLAG_HIDE_LINE;
								gdiplus_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
								//Line3D::s_line3d_draw_mode = old_line3d_draw_mode;*/


								gdiplus_view::what_selected.GetObject()->ReDraw();
								UpdateAllViews();
								return;
							}
						}
					}
				}
			}
#if !GDIPLUS_SELECTION_3D
			else
			{
				printf("dist_to_line = %f\n", dist_to_line);
			}
#endif
		}
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
		{
			if( gdiplus_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_line
				&& gdiplus_view::what_selected.GetObject())
			{
				if (to_edit_line)
				{
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								if(gv->calc_select_line(mouse[0], mouse[1], pt3))
								{
									if(to_insert)
									{
										//printf("insert\n");
										primitive3->Insert(gdiplus_view::what_selected.GetIndex()+1,pt3);
										to_insert = false;
									}
									else
									{
										primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex()+1) = pt3;
									}

									//primitive3->Insert(gdiplus_view::what_selected.GetIndex()+1,pt3);
									primitive3->Zoom(gdiplus_view::what_selected.GetIndex()+1,
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
											m_xd_zoom_center,
											m_yd_zoom_center,
											m_zd_zoom_center);

									/*this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
										gdiplus_view::what_selected.GetIndex());*/
								}
/*
								CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								// UN HIDE LINE - выключаем 4-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
								gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
*/
								gdiplus_view::what_selected.GetObject()->ReDraw();
								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}


	}

//	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well)
	{
		if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Lito_IGE_move_sloj)
		{
			static double key_zk_up = 0.0, key_zk_dw = 0.0;

			//printf("edit_gdiplus_tool::Well_move_sloj\n");
			//Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
			gdiplus_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_lito_ige;

			CPoint3 pt3;
			// при нажатии кнопки мыши
			if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
			{		
	//printf("if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)\n");
				// если мы попали мышью по объекту
	#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
	#else
				double dist_to_well = DBL_MAX;
				if (profile->IsSelectedWell(gv, mouse[0], mouse[1], dist_to_well, gdiplus_view::what_selected)
					&& dist_to_well <= fabs(gv->lines_points_radius)
					)
	#endif
				{
	//printf("if (profile->IsSelectedWell\n");
					gdiplus_view::what_selected.PrintInfo();

					gdiplus_view::what_selected.PrintInfo();
					if( gdiplus_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_lito_ige
						&& gdiplus_view::what_selected.GetObject())
					{	
	//printf("if (m_selected_objects_element_type == sel_point\n");
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
	//printf("if (this->IsPrimitive3()\n");
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
								WellColomn * Lito_WellColomn = NULL;
								WellColomn * IGE_WellColomn = NULL;
								for (vector<WellColomn>::iterator it_c = pwell->well_colomns.begin();
									it_c != pwell->well_colomns.end(); it_c++)
								{
									if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
									{
										IGE_WellColomn = &(*it_c);
									}
									if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
									{
										Lito_WellColomn = &(*it_c);
									}
								}

								if ( Lito_WellColomn && IGE_WellColomn)
								{
									int sel_ind = gdiplus_view::what_selected.GetIndex();
									if (sel_ind > -1 
										&& 
										// здесь мы добавили 1 + чтобы не редактировать забой скважины
										1 + sel_ind < (int)Lito_WellColomn->well_elements.size()
										&& 
										1 + sel_ind < (int)IGE_WellColomn->well_elements.size()
										)
									{
		//printf("if GetIndex()\n");
										if (IGE_WellColomn->well_elements[sel_ind] &&
											IGE_WellColomn->well_elements[sel_ind+1] &&
											Lito_WellColomn->well_elements[sel_ind] &&
											Lito_WellColomn->well_elements[sel_ind+1])
										{
										//edit_point = &pwell->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
											key_zk_up = IGE_WellColomn->well_elements[sel_ind]->zk;
											key_zk_dw = IGE_WellColomn->well_elements[sel_ind+1]->zk;

											this->edit_zp_ige = &(IGE_WellColomn->well_elements[sel_ind]->zp);
											this->edit_zp_lito = &(Lito_WellColomn->well_elements[sel_ind]->zp);

											this->edit_zk_ige = &(IGE_WellColomn->well_elements[sel_ind+1]->zk);
											this->edit_zk_lito = &(Lito_WellColomn->well_elements[sel_ind+1]->zk);

										}
										

										/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
										// HIDE POINT - включаем 3-й бит 
										// в пользовательских данных point 
										ptd.flag |= CPOINT3_FLAG_HIDE;
										gdiplus_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
										Line3D::s_line3d_draw_mode = old_line3d_draw_mode;*/

		//printf("pre ReDraw %s\n", Object::ObjectTypeToString(gdiplus_view::what_selected.GetObject()->GetObjectType()));

										gdiplus_view::what_selected.GetObject()->ReDraw();
										UpdateAllViews();
										return;
									}
								}

	//printf("if (pwell)\n");
							}
						}
					}
			
				}

	#if !GDIPLUS_SELECTION_3D
				else
				{
					printf("dist_to_well = %f\n", dist_to_well);
				}
	#endif

			}
			if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
			{
	//printf("edit_gdiplus_tool::Well_move_sloj Up\n");
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_lito_ige
					&& gdiplus_view::what_selected.GetObject())
				{
	//printf("sel_point\n");
					if (this->edit_zp_ige && this->edit_zp_lito
						&& this->edit_zk_ige && this->edit_zk_lito)
					{
	//printf("edit_point\n");
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
	//printf("IsPrimitive3\n");
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
								WellColomn * Lito_WellColomn = NULL;
								WellColomn * IGE_WellColomn = NULL;
								for (vector<WellColomn>::iterator it_c = pwell->well_colomns.begin();
									it_c != pwell->well_colomns.end(); it_c++)
								{
									if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
									{
										IGE_WellColomn = &(*it_c);
									}
									if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
									{
										Lito_WellColomn = &(*it_c);
									}
								}

								if ( Lito_WellColomn && IGE_WellColomn)
								{
									int sel_ind = gdiplus_view::what_selected.GetIndex();
									if (sel_ind > -1 
										&&																				
										// здесь мы добавили 1 + чтобы не редактировать забой скважины
										1 + sel_ind < (int)Lito_WellColomn->well_elements.size()
										&& 
										1 + sel_ind < (int)IGE_WellColomn->well_elements.size()
										)
									{
		//printf("if GetIndex()\n");
										if(gv->calc_select_line(mouse[0], mouse[1], pt3))
										{
										//edit_point = &pwell->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());

											//double z_before_edit = (*this->edit_zp_ige);

											(*this->edit_zp_ige) = pt3.z;
											(*this->edit_zp_lito) = pt3.z;

											(*this->edit_zk_ige) = pt3.z;
											(*this->edit_zk_lito) = pt3.z;

											CPoint3 ustje;
											if (pwell->GetUstje(ustje) 
												&& IGE_WellColomn->well_elements[sel_ind]
												&& IGE_WellColomn->well_elements[sel_ind+1]
												&& Lito_WellColomn->well_elements[sel_ind]
												&& Lito_WellColomn->well_elements[sel_ind+1]
												)
											{
												double key_H0_up = ustje.z - key_zk_up;
												double key_H0_dw = ustje.z - key_zk_dw;
												bool edit_H0, edit_H1;
												edit_H0 = false; edit_H1 = true;
												IGE_WellColomn->well_elements[sel_ind]->EditLitoInDB(this, pwell->GetIdKt(), ustje.z, key_H0_up, edit_H0, edit_H1);
												edit_H0 = true; edit_H1 = false;
												IGE_WellColomn->well_elements[sel_ind+1]->EditLitoInDB(this, pwell->GetIdKt(), ustje.z, key_H0_dw, edit_H0, edit_H1);

												GridDataPointRef * ige_up_pt_zp = &IGE_WellColomn->well_elements[sel_ind]->grid_data_point_zp;
												GridDataPointRef * ige_dw_pt_zk = &IGE_WellColomn->well_elements[sel_ind+1]->grid_data_point_zk;

												//GridDataPointRef * lito_up_pt_zp = &Lito_WellColomn->well_elements[sel_ind]->grid_data_point_zp;
												//GridDataPointRef * lito_dw_pt_zk = &Lito_WellColomn->well_elements[sel_ind+1]->grid_data_point_zk;

												ResetZoomRedraw(this, ige_up_pt_zp, pt3.z);
												ResetZoomRedraw(this, ige_dw_pt_zk, pt3.z);
												//ResetZoomRedraw(this, lito_up_pt_zp, pt3.z);
												//ResetZoomRedraw(this, lito_dw_pt_zk, pt3.z);

												// теперь надо произвести вызов команды
												//Пробы грунта -> Автозаполнение ИГЭ по разбивке скважин
												//	почему? 
												//	потому что необходимость редактирования границ ИГЭ,
												//	которое мы только что осуществили
												//	обычно возникает у пользователя если пользователь видит 
												//	несоответствие между разбивкой и данными лабораторных анализов
												//	поэтому в результате редактирования границ ИГЭ 
												//	весьма вероятно изменение отнесения 
												//	того или иного лабораторного номера к тому или иному ИГЭ

												//	Итак мы должны изменить 
												//	соответствие ИГЭ и лабораторных номеров в базе
												//	(это достаточно сделать только для текущей КТ)
												
												if (this->GetLabDoc())
												{
													this->GetLabDoc()->ProbgrIGEautoFill(false, 
														this->Get_ID_OBJ(), 
														pwell->GetIdKt());
												}

												//	А затем мы должны тоже самое сделать для объекта Лаборатория
												//	вернее для двух объектов - во первых для объекта Лаборатория,
												//	принадлежащего текущему документу
												//	а во-вторых если текущий документ принадлежит ДЛЛ трёхмерного окна 
												//	надо обратиться из ДЛЛ к программе ЛАБ, чтобы программа ЛАБ 
												//	установила соответствие ИГЭ и лабораторных номеров
												//	в том документе, который (если он создан) создан для отображения ИГЭ 
												//	в контекстном меню и в таблицах нормативных значений 

												//	поэтому нижеследующий код надо обернуть в функцию, которую вызвать дважды для 
												//	документов обоих видов



												this->LabNumberResetting(IGE_WellColomn, pwell, ustje, sel_ind);

											}


										
		//printf("calc_select_line\n");
											/*pwell->Primitive3D<CPoint3>::Zoom(gdiplus_view::what_selected.GetIndex(),
												this->m_zoomX, this->m_zoomY, this->m_zoomZ,
													m_xd_zoom_center,
													m_yd_zoom_center,
													m_zd_zoom_center);*/

											//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
											//	gdiplus_view::what_selected.GetIndex());

										}


										/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
										// HIDE POINT - включаем 3-й бит 
										// в пользовательских данных point 
										ptd.flag |= CPOINT3_FLAG_HIDE;
										gdiplus_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
										Line3D::s_line3d_draw_mode = old_line3d_draw_mode;*/

		//printf("pre ReDraw %s\n", Object::ObjectTypeToString(gdiplus_view::what_selected.GetObject()->GetObjectType()));

										gdiplus_view::what_selected.GetObject()->ReDraw();
										UpdateAllViews();
										return;
									}
								}

	//printf("if (pwell)\n");
							}
						}
					}
				}
			}
		}
		if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well_move_sloj || gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well)
		{
			//printf("edit_gdiplus_tool::Well_move_sloj\n");
			//Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
			gdiplus_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_point;

			CPoint3 pt3;
			// при нажатии кнопки мыши
			if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
			{		
	//printf("if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)\n");
				// если мы попали мышью по объекту
	#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
	#else
				double dist_to_well = DBL_MAX;
				if (profile->IsSelectedWell(gv, mouse[0], mouse[1], dist_to_well, gdiplus_view::what_selected)
					&& dist_to_well <= fabs(gv->lines_points_radius)
					)
	#endif
				{
	//printf("if (profile->IsSelectedWell\n");
					gdiplus_view::what_selected.PrintInfo();

					gdiplus_view::what_selected.PrintInfo();
					if( gdiplus_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& gdiplus_view::what_selected.GetObject())
					{	
	//printf("if (m_selected_objects_element_type == sel_point\n");
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
	//printf("if (this->IsPrimitive3()\n");
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
	//printf("if (pwell)\n");
								if (gdiplus_view::what_selected.GetIndex() > 1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)pwell->GetPointsNumber())
								{
	//printf("if GetIndex()\n");
									edit_point = &pwell->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									
									/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									// HIDE POINT - включаем 3-й бит 
									// в пользовательских данных point 
									ptd.flag |= CPOINT3_FLAG_HIDE;
									gdiplus_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
									Line3D::s_line3d_draw_mode = old_line3d_draw_mode;*/

	//printf("pre ReDraw %s\n", Object::ObjectTypeToString(gdiplus_view::what_selected.GetObject()->GetObjectType()));

									gdiplus_view::what_selected.GetObject()->ReDraw();
									UpdateAllViews();
									return;
								}
							}
						}
					}
			
				}

	#if !GDIPLUS_SELECTION_3D
				else
				{
					printf("dist_to_well = %f\n", dist_to_well);
				}
	#endif

			}
			if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
			{
	//printf("edit_gdiplus_tool::Well_move_sloj Up\n");
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_point
					&& gdiplus_view::what_selected.GetObject())
				{
	//printf("sel_point\n");
					if (edit_point)
					{
	//printf("edit_point\n");
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
	//printf("IsPrimitive3\n");
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
	//printf("pwell\n");
								if (gdiplus_view::what_selected.GetIndex() > 1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)pwell->GetPointsNumber())
								{
	//printf("GetIndex()\n");
									/*bool can_disable_depth_test = Object::CanDisableDepthTest();
									if (can_disable_depth_test)
									{
										Object::CanDisableDepthTest(false);
										UpdateAllViews(true);
									}*/
									
									if(gv->calc_select_line(mouse[0], mouse[1], pt3))
									{
	//printf("calc_select_line\n");
										(*edit_point).z = pt3.z;
										pwell->Primitive3D<CPoint3>::Zoom(gdiplus_view::what_selected.GetIndex(),
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);

										//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
										//	gdiplus_view::what_selected.GetIndex());

									}

									/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									// UN HIDE POINT - выключаем 3-й бит 
									// в пользовательских данных point
									ptd.flag &= ~CPOINT3_FLAG_HIDE;
									gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
	*/
									gdiplus_view::what_selected.GetObject()->ReDraw();

									//Object::CanDisableDepthTest(can_disable_depth_test);
									UpdateAllViews();
								}
							}
						}
					}
				}
			}
		}
		if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well_add_sloj || gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well)
		{
//printf("edit_gdiplus_tool::Well_add_sloj\n");
			gdiplus_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_line;


			CPoint3 pt3;
			// при нажатии кнопки мыши
			if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
			{			
//printf("Down\n");
				// если мы попали мышью по объекту
	#if GDIPLUS_SELECTION_3D
				if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
	#else
				double dist_to_well = DBL_MAX;
				if (profile->IsSelectedWell(gv, mouse[0], mouse[1], dist_to_well, gdiplus_view::what_selected) && dist_to_well <= fabs(gv->lines_points_radius))
	#endif
				{
//printf("IsSelectedWell\n");
					gdiplus_view::what_selected.PrintInfo();
					if( gdiplus_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_line
						&& gdiplus_view::what_selected.GetObject())
					{	
//printf("sel_line && GetObject()\n");
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
//printf("IsPrimitive3\n");
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
//printf("pwell\n");
								if (gdiplus_view::what_selected.GetIndex() > 1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)pwell->GetPointsNumber())
								{
//printf("to_edit_line = true;\tto_insert = true;\n");
									to_edit_line = true;
									to_insert = true;
									//edit_point = &primitive3->GetViewPoint(gdiplus_view::what_selected.GetIndex());
									/*
									CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									// HIDE LINE - включаем 4-й бит 
									// в пользовательских данных point 
									ptd.flag |= CPOINT3_FLAG_HIDE_LINE;
									gdiplus_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
									//Line3D::s_line3d_draw_mode = old_line3d_draw_mode;*/


									gdiplus_view::what_selected.GetObject()->ReDraw();
									UpdateAllViews();
									return;
								}
							}
						}
					}
				}
	#if !GDIPLUS_SELECTION_3D
				else
				{
					printf("dist_to_well = %f\n", dist_to_well);
				}
	#endif
			}
			if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
			{
//printf("edit_gdiplus_tool::Well_add_sloj Up!!\n");
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_line
					&& gdiplus_view::what_selected.GetObject())
				{
//printf("sel_line to_edit_line = %d\n", to_edit_line );
					if (to_edit_line)
					{
//printf("to_edit_line\n");
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
//printf("IsPrimitive3\n");
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
//printf("pwell\n");
								if (gdiplus_view::what_selected.GetIndex() > 1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)pwell->GetPointsNumber())
								{
//printf("GetIndex()\n");
									/*bool can_disable_depth_test = Object::CanDisableDepthTest();
									if (can_disable_depth_test)
									{
										Object::CanDisableDepthTest(false);
										UpdateAllViews(true);
									}*/
									if(gv->calc_select_line(mouse[0], mouse[1], pt3))
									{
//printf("gv->calc_select_line\n");
										if(to_insert)
										{
											CPoint3 ustje;
											if (pwell->GetUstje(ustje))
											{
												pt3.x = ustje.x;
												pt3.y = ustje.y;
											}
											//printf("insert\n");
											pwell->Insert(gdiplus_view::what_selected.GetIndex()+1,pt3);
											to_insert = false;
										}
										else
										{
//printf("do not insert -> move\n");
											pwell->GetDocumentPoint(gdiplus_view::what_selected.GetIndex()+1).z = pt3.z;
										}

										pwell->Primitive3D<CPoint3>::Zoom(gdiplus_view::what_selected.GetIndex()+1,
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);

										/*this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
											gdiplus_view::what_selected.GetIndex());*/
									}
	/*
									CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									// UN HIDE LINE - выключаем 4-й бит 
									// в пользовательских данных point
									ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
									gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
	*/
									gdiplus_view::what_selected.GetObject()->ReDraw();
									//Object::CanDisableDepthTest(can_disable_depth_test);
									UpdateAllViews();
								}
							}
						}
					}
				}
			}
		}


	}

	/*if (gdiplus_view::what_to_edit == edit_gdiplus_tool::Line_cut_by_double_new_point_on_bond)
	{
		//printf("edit_gdiplus_tool::Line_cut_by_double_new_point_on_bond\n");
	}*/
	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::Line_cut_by_select_and_delete_bond)
	{
		//printf("edit_gdiplus_tool::Line_cut_by_select_and_delete_bond\n");

		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;

		CPoint3 pt3;

		// при нажатии кнопки мыши
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{			
			// если мы попали мышью по объекту
#if GDIPLUS_SELECTION_3D
			if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
			double dist_to_line = DBL_MAX;
			if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected) && dist_to_line <= fabs(gv->lines_points_radius))
#endif
			{
				gdiplus_view::what_selected.PrintInfo();
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_line
					&& gdiplus_view::what_selected.GetObject())
				{	
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								//printf("to_edit = true\n");

								if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
								{
									Line3D * pob = dynamic_cast<Line3D*>(gdiplus_view::what_selected.GetObject());
									if (pob && gdiplus_view::what_selected.GetObject()->GetObjectList() && gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer())
									{
										if (gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
										{
											vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer());
											if (gdiplus_view::what_selected.GetIndex() > 0)
											{
												//----------------------------------------
												Line3D line(this);
												pvect->AddMsg(&line);
												for (unsigned int i = 0; 
													i <= gdiplus_view::what_selected.GetIndex() && 
													i < pob->GetPointsNumber(); i++)
													pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
												pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																		m_xd_zoom_center,
																		m_yd_zoom_center,
																		m_zd_zoom_center);
												pvect->GetLastMsg().SetColor(gdiplus_view::what_selected.GetObject()->GetColor());
												pvect->GetLastMsg().SetName(gdiplus_view::what_selected.GetObject()->GetName());
												pvect->GetLastMsg().SetLayer(gdiplus_view::what_selected.GetObject()->GetLayer());
												pvect->GetLastMsg().Select(false);
												pvect->GetLastMsg().Draw();
												pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
												//----------------------------------------
											}
											if (pob->GetPointsNumber() - (gdiplus_view::what_selected.GetIndex()+1) > 1)
											{
												//----------------------------------------
												Line3D line2(this);
												pvect->AddMsg(&line2);
												for (unsigned int i = gdiplus_view::what_selected.GetIndex()+1; i < pob->GetPointsNumber(); i++)
													pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
												pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																		m_xd_zoom_center,
																		m_yd_zoom_center,
																		m_zd_zoom_center);
												pvect->GetLastMsg().SetColor(gdiplus_view::what_selected.GetObject()->GetColor());
												pvect->GetLastMsg().SetName(gdiplus_view::what_selected.GetObject()->GetName());
												pvect->GetLastMsg().SetLayer(gdiplus_view::what_selected.GetObject()->GetLayer());

												pvect->GetLastMsg().Select(false);
												pvect->GetLastMsg().Draw();
												pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
												//----------------------------------------
											}
											gdiplus_view::what_selected.GetObject()->GetObjectList()->Init(*pvect, gdiplus_view::what_selected.GetObject()->GetObjectList()->GetParent());

											gdiplus_view::what_selected.GetObject()->m_bChecked = false;
											TreeView_MySetCheckState(this->hwndTV, 
												gdiplus_view::what_selected.GetObject()->myTreeItem, 
												gdiplus_view::what_selected.GetObject()->m_bChecked);
				
																	
											gdiplus_view::what_selected.
												EraseSelectedObject<Line3D>
												(hwndTV,Object::object_type::line3d);
					
											UpdateAllViews();
											return;
										}
									}
								}
							}
						}
					}
				}
			}

		}
	}
	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::Line_cut_by_select_and_double_point)
	{
		//printf("edit_gdiplus_tool::Line_cut_by_select_and_double_point\n");
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;

		// при нажатии кнопки мыши
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{				
			// если мы попали мышью по объекту
#if GDIPLUS_SELECTION_3D
			if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
			double dist_to_line = DBL_MAX;
			if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected) && dist_to_line <= fabs(gv->lines_points_radius))
#endif
			{
				gdiplus_view::what_selected.PrintInfo();
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_point
					&& gdiplus_view::what_selected.GetObject())
				{	
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								//printf("to_edit = true\n");

								if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
								{
									Line3D * pob = dynamic_cast<Line3D*>(gdiplus_view::what_selected.GetObject());
									if (pob && gdiplus_view::what_selected.GetObject()->GetObjectList() && gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer())
									{
										if (gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
										{
											vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer());
											if (gdiplus_view::what_selected.GetIndex() > 0)
											{
												//----------------------------------------
												Line3D line(this);
												pvect->AddMsg(&line);
												for (unsigned int i = 0; 
													i <= gdiplus_view::what_selected.GetIndex() && 
													i < pob->GetPointsNumber(); i++)
													pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
												pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																		m_xd_zoom_center,
																		m_yd_zoom_center,
																		m_zd_zoom_center);
												pvect->GetLastMsg().SetColor(gdiplus_view::what_selected.GetObject()->GetColor());
												pvect->GetLastMsg().SetName(gdiplus_view::what_selected.GetObject()->GetName());
												pvect->GetLastMsg().Select(true);
												pvect->GetLastMsg().Draw();
												pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
												//----------------------------------------
											}
											if (pob->GetPointsNumber() - (gdiplus_view::what_selected.GetIndex()+1) > 1)
											{
												//----------------------------------------
												Line3D line2(this);
												pvect->AddMsg(&line2);
												for (unsigned int i = gdiplus_view::what_selected.GetIndex()+1; i < pob->GetPointsNumber(); i++)
													pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
												pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																		m_xd_zoom_center,
																		m_yd_zoom_center,
																		m_zd_zoom_center);
												pvect->GetLastMsg().SetColor(gdiplus_view::what_selected.GetObject()->GetColor());
												pvect->GetLastMsg().SetName(gdiplus_view::what_selected.GetObject()->GetName());
												pvect->GetLastMsg().Select(false);
												pvect->GetLastMsg().Draw();
												pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
												//----------------------------------------
											}
											gdiplus_view::what_selected.GetObject()->GetObjectList()->Init(*pvect, gdiplus_view::what_selected.GetObject()->GetObjectList()->GetParent());

											gdiplus_view::what_selected.GetObject()->m_bChecked = false;
											TreeView_MySetCheckState(this->hwndTV, 
												gdiplus_view::what_selected.GetObject()->myTreeItem, 
												gdiplus_view::what_selected.GetObject()->m_bChecked);

																	
											gdiplus_view::what_selected.
												EraseSelectedObject<Line3D>
												(hwndTV,Object::object_type::line3d);
					
				
											UpdateAllViews();
											return;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}



	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Lines_connect)
	{
		//printf("edit_gdiplus_tool::Line_connect\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{
//printf("edit_gdiplus_tool::Line_connect Down\n");
			this->connect_lines[0] = NULL;
			this->connect_vect_lines[0] = NULL;
			this->connect_lines_ind[0] = -1;

		
			// если мы попали мышью по объекту
#if GDIPLUS_SELECTION_3D
			if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
#else
			double dist_to_line = DBL_MAX;
			if (profile->IsSelectedLine(gv, mouse[0], mouse[1], dist_to_line, gdiplus_view::what_selected) && dist_to_line <= fabs(gv->lines_points_radius))
#endif
			{
				gdiplus_view::what_selected.PrintInfo();
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_point
					&& gdiplus_view::what_selected.GetObject())
				{	
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								//printf("to_edit = true\n");

								if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
								{
									Line3D * pob = dynamic_cast<Line3D*>(gdiplus_view::what_selected.GetObject());
									this->connect_lines[0] = pob;

									if (pob && gdiplus_view::what_selected.GetObject()->GetObjectList() && gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer())
									{
										if (gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
										{
											vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer());
											this->connect_vect_lines[0] = pvect;
											this->connect_lines_ind[0] = gdiplus_view::what_selected.GetIndex();



											return;
										}
									}
								}
							}
						}
					}
				}
			}

		}
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
		{
//printf("edit_gdiplus_tool::Line_connect Up\n");
			this->connect_lines[1] = NULL;
			this->connect_vect_lines[1] = NULL;
			this->connect_lines_ind[1] = -1;


			if (gv->calc_select_line(mouse[0], mouse[1], pt3) && profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
				//if (this->IsSelected(pt3,this->m_sphere_radius,gdiplus_view::what_selected))
			{
				gdiplus_view::what_selected.PrintInfo();
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_point
					&& gdiplus_view::what_selected.GetObject())
				{	
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								//printf("to_edit = true\n");

								if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
								{
									Line3D * pob = dynamic_cast<Line3D*>(gdiplus_view::what_selected.GetObject());
									this->connect_lines[1] = pob;

									if (pob && gdiplus_view::what_selected.GetObject()->GetObjectList() && gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer())
									{
										if (gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
										{
											vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer());
											this->connect_vect_lines[1] = pvect;
											this->connect_lines_ind[1] = gdiplus_view::what_selected.GetIndex();


											
										}
									}
								}
							}
						}
					}
				}
			}

/*printf("edit_gdiplus_tool::Line_connect 2\n");//*/
/*printf("this->connect_lines[0] 0x%08x\n"
		"this->connect_vect_lines[0] 0x%08x\n"
		"this->connect_lines_ind[0] %d\n"
		,
				this->connect_lines[0],
				this->connect_vect_lines[0],
				this->connect_lines_ind[0]
				);
printf("this->connect_lines[1] 0x%08x\n"
		"this->connect_vect_lines[1] 0x%08x\n"
		"this->connect_lines_ind[1] %d\n"
		,
				this->connect_lines[1],
				this->connect_vect_lines[1],
				this->connect_lines_ind[1]
				);//*/

			if (this->connect_lines[0] && this->connect_lines[1] &&
				this->connect_vect_lines[0] && this->connect_vect_lines[1])
			{
//printf("edit_gdiplus_tool::Line_connect 3\n");
				if (this->connect_lines[0] == this->connect_lines[1])
				{		
					if(
						(this->connect_lines_ind[0] == 0 && this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						||
						(this->connect_lines_ind[1] == 0 && this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						)
					{
						if(this->connect_lines[0]->GetPointsNumber() > 2)
						{
							this->connect_lines[0]->PushBack(this->connect_lines[0]->GetDocumentPoint(0));
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
						}
					}
				}
				if (this->connect_lines[0] != this->connect_lines[1])
				{
//printf("edit_gdiplus_tool::Line_connect 4\n");
					if(
						(this->connect_lines_ind[0] == 0 || this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						&&
						(this->connect_lines_ind[1] == 0 || this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						)
					{
//printf("edit_gdiplus_tool::Line_connect 5\n");
						// нулевую линию сливаем к первой

						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = 0; i < (int)this->connect_lines[0]->GetPointsNumber(); i++)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}

							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_gdiplus_tool::Line_connect 6\n");
							return;

						}						
						
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = (int)this->connect_lines[0]->GetPointsNumber()-1; i >=0; i--)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}
							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_gdiplus_tool::Line_connect 7\n");
							return;
						}
						// первую линию сливаем к нулевой 
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == 0)
						{
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
//printf("edit_gdiplus_tool::Line_connect 8\n");
							return;
						}						
						
						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == 0)
						{
							this->connect_lines[0]->Reverse();
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_gdiplus_tool::Line_connect 9\n");
							return;
						}
						
					}
				}
			}
		}


	}

//printf("GdiPlusEditEvent End() to_edit_line = false; edit_point = NULL;\n");

	to_edit_line = false;
	edit_point = NULL;

	edit_zp_lito = NULL;
	edit_zp_ige = NULL;

	edit_zk_lito = NULL;
	edit_zk_ige = NULL;

}





void project::GDIplusEditMotionEvent(gdiplus_map_view * gv/*, vector<iGLu> & names*/)
{
	if (!gv) return;
	if (gdiplus_view::button == mouse_gdiplus_tool::Right) return;	// the right button is for popup menus...

	i32s mouse[2] =
	{
		gv->current_gdiplus_tool->latest_x,
		gv->current_gdiplus_tool->latest_y
	};
//	double epsilon = 0.000001;
				
	BlnProfile3D * profile = dynamic_cast<BlnProfile3D *>(gv->GetObject());
	if (!profile) return;
				
	//double dist_to_object = DBL_MAX;				
	//double search_radius = 3.0 * this->m_sphere_radius / (this->m_zoomX + this->m_zoomY + this->m_zoomZ);

	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Line)
	{
		//if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Line_by_moving_existing_point)
		//{
		//printf("edit_gdiplus_tool::Line\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		//CPoint3 pt3;
		// при нажатии кнопки мыши

		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{
//printf("edit_gdiplus_tool::Line Up\n");
			if( gdiplus_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_point
				&& gdiplus_view::what_selected.GetObject())
			{
				if (edit_point)
				{
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								
								if(gv->calc_select_line(mouse[0], mouse[1], *edit_point))
								{
									primitive3->Zoom(gdiplus_view::what_selected.GetIndex(),
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
											m_xd_zoom_center,
											m_yd_zoom_center,
											m_zd_zoom_center);

									//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
									//	gdiplus_view::what_selected.GetIndex());

								}

								/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								// UN HIDE POINT - выключаем 3-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE;
								gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
*/
								gdiplus_view::what_selected.GetObject()->ReDraw();

								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}
		//if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Line_by_add_new_point)
		//{
		//printf("edit_gdiplus_tool::Line_by_add_new_point\n");
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;


		// при нажатии кнопки мыши

		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{
			if( gdiplus_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_line
				&& gdiplus_view::what_selected.GetObject())
			{
				if (to_edit_line)
				{
					if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(gdiplus_view::what_selected.GetObject());

						if (primitive3)
						{
							if (gdiplus_view::what_selected.GetIndex() > -1 
								&& 
								gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								CPoint3 pt3;
								if(gv->calc_select_line(mouse[0], mouse[1], pt3))
								{
									//*edit_point = pt3;
									if(to_insert)
									{
										//printf("insert\n");
										primitive3->Insert(gdiplus_view::what_selected.GetIndex()+1,pt3);
										to_insert = false;
									}
									else
									{
										primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex()+1) = pt3;
									}
									primitive3->Zoom(gdiplus_view::what_selected.GetIndex()+1,
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
											m_xd_zoom_center,
											m_yd_zoom_center,
											m_zd_zoom_center);

									//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
									//	gdiplus_view::what_selected.GetIndex());
								}

								CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
								// UN HIDE LINE - выключаем 4-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
								gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;

								gdiplus_view::what_selected.GetObject()->ReDraw();
								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}


	}

	//if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well)
	{
		if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well_move_sloj || gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well)
		{
			//printf("edit_gdiplus_tool::Well_move_sloj\n");
			//Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
			gdiplus_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_point;

			//CPoint3 pt3;
			// при нажатии кнопки мыши

			if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
			{
	//printf("edit_gdiplus_tool::Line Up\n");
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_point
					&& gdiplus_view::what_selected.GetObject())
				{
					if (edit_point)
					{
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
								if (gdiplus_view::what_selected.GetIndex() > 1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)pwell->GetPointsNumber())
								{
									/*bool can_disable_depth_test = Object::CanDisableDepthTest();
									if (can_disable_depth_test)
									{
										Object::CanDisableDepthTest(false);
										UpdateAllViews(true);
									}*/

									CPoint3 pt3;
									
									if(gv->calc_select_line(mouse[0], mouse[1], pt3))
									{
										(*edit_point).z = pt3.z;
										pwell->Primitive3D<CPoint3>::Zoom(gdiplus_view::what_selected.GetIndex(),
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);

										//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
										//	gdiplus_view::what_selected.GetIndex());

									}

									/*CPoint3& ptd = primitive3->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									// UN HIDE POINT - выключаем 3-й бит 
									// в пользовательских данных point
									ptd.flag &= ~CPOINT3_FLAG_HIDE;
									gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
	*/
									gdiplus_view::what_selected.GetObject()->ReDraw();

									//Object::CanDisableDepthTest(can_disable_depth_test);
									UpdateAllViews();
								}
							}
						}
					}
				}
			}
		}
		if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well_add_sloj || gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Well)
		{
			//printf("edit_gdiplus_tool::Well_add_sloj\n");
			gdiplus_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_line;


			// при нажатии кнопки мыши

			if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
			{
				if( gdiplus_view::what_selected.m_selected_objects_element_type 
					== WhatSelected::selected_objects_element_type::sel_line
					&& gdiplus_view::what_selected.GetObject())
				{
					if (to_edit_line)
					{
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
							Well_3D * pwell 
								= dynamic_cast<Well_3D *>
								(gdiplus_view::what_selected.GetObject());

							if (pwell)
							{
								if (gdiplus_view::what_selected.GetIndex() > 1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)pwell->GetPointsNumber())
								{
									/*bool can_disable_depth_test = Object::CanDisableDepthTest();
									if (can_disable_depth_test)
									{
										Object::CanDisableDepthTest(false);
										UpdateAllViews(true);
									}*/
									CPoint3 pt3;
									if(gv->calc_select_line(mouse[0], mouse[1], pt3))
									{										
										if(to_insert)
										{
											CPoint3 ustje;
											if (pwell->GetUstje(ustje))
											{
												pt3.x = ustje.x;
												pt3.y = ustje.y;
											}
											printf("insert\n");
											pwell->Insert(gdiplus_view::what_selected.GetIndex()+1,pt3);
											to_insert = false;
										}
										else
										{
											pwell->GetDocumentPoint(gdiplus_view::what_selected.GetIndex()+1).z = pt3.z;
										}
										pwell->Primitive3D<CPoint3>::Zoom(gdiplus_view::what_selected.GetIndex()+1,
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);

										//this->CorrectDrawingPoint(gdiplus_view::what_selected.GetObject(), 
										//	gdiplus_view::what_selected.GetIndex());
									}

									CPoint3& ptd = pwell->GetDocumentPoint(gdiplus_view::what_selected.GetIndex());
									// UN HIDE LINE - выключаем 4-й бит 
									// в пользовательских данных point
									ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
									gdiplus_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;

									gdiplus_view::what_selected.GetObject()->ReDraw();
									//Object::CanDisableDepthTest(can_disable_depth_test);
									UpdateAllViews();
								}
							}
						}
					}
				}
			}
		}


	}

	/*if (gdiplus_view::what_to_edit == edit_gdiplus_tool::Line_cut_by_double_new_point_on_bond)
	{
		//printf("edit_gdiplus_tool::Line_cut_by_double_new_point_on_bond\n");
	}*/
#if 0
	if (gdiplus_view::what_to_edit == edit_gdiplus_tool::what_to_edit::Lines_connect)
	{
		//printf("edit_gdiplus_tool::Line_connect\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		gdiplus_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Down)
		{
//printf("edit_gdiplus_tool::Line_connect Down\n");
			this->connect_lines[0] = NULL;
			this->connect_vect_lines[0] = NULL;
			this->connect_lines_ind[0] = -1;

			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				if (profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
					//if (this->IsSelected(pt3,this->m_sphere_radius,gdiplus_view::what_selected))
				{
					gdiplus_view::what_selected.PrintInfo();
					if( gdiplus_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& gdiplus_view::what_selected.GetObject())
					{	
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(gdiplus_view::what_selected.GetObject());

							if (primitive3)
							{
								if (gdiplus_view::what_selected.GetIndex() > -1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(gdiplus_view::what_selected.GetObject());
										this->connect_lines[0] = pob;

										if (pob && gdiplus_view::what_selected.GetObject()->GetObjectList() && gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[0] = pvect;
												this->connect_lines_ind[0] = gdiplus_view::what_selected.GetIndex();



												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (gdiplus_view::state == mouse_gdiplus_tool::state::Up)
		{
//printf("edit_gdiplus_tool::Line_connect Up\n");
			this->connect_lines[1] = NULL;
			this->connect_vect_lines[1] = NULL;
			this->connect_lines_ind[1] = -1;

			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				
				if (profile->IsSelectedDoc(pt3, search_radius, dist_to_object, gdiplus_view::what_selected))
					//if (this->IsSelected(pt3,this->m_sphere_radius,gdiplus_view::what_selected))
				{
					gdiplus_view::what_selected.PrintInfo();
					if( gdiplus_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& gdiplus_view::what_selected.GetObject())
					{	
						if(gdiplus_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(gdiplus_view::what_selected.GetObject());

							if (primitive3)
							{
								if (gdiplus_view::what_selected.GetIndex() > -1 
									&& 
									gdiplus_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (gdiplus_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(gdiplus_view::what_selected.GetObject());
										this->connect_lines[1] = pob;

										if (pob && gdiplus_view::what_selected.GetObject()->GetObjectList() && gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(gdiplus_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[1] = pvect;
												this->connect_lines_ind[1] = gdiplus_view::what_selected.GetIndex();


												
											}
										}
									}
								}
							}
						}
					}
				}
			}
/*printf("edit_gdiplus_tool::Line_connect 2\n");//*/
/*printf("this->connect_lines[0] 0x%08x\n"
		"this->connect_vect_lines[0] 0x%08x\n"
		"this->connect_lines_ind[0] %d\n"
		,
				this->connect_lines[0],
				this->connect_vect_lines[0],
				this->connect_lines_ind[0]
				);
printf("this->connect_lines[1] 0x%08x\n"
		"this->connect_vect_lines[1] 0x%08x\n"
		"this->connect_lines_ind[1] %d\n"
		,
				this->connect_lines[1],
				this->connect_vect_lines[1],
				this->connect_lines_ind[1]
				);//*/

			if (this->connect_lines[0] && this->connect_lines[1] &&
				this->connect_vect_lines[0] && this->connect_vect_lines[1])
			{
//printf("edit_gdiplus_tool::Line_connect 3\n");
				if (this->connect_lines[0] == this->connect_lines[1])
				{		
					if(
						(this->connect_lines_ind[0] == 0 && this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						||
						(this->connect_lines_ind[1] == 0 && this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						)
					{
						if(this->connect_lines[0]->GetPointsNumber() > 2)
						{
							this->connect_lines[0]->PushBack(this->connect_lines[0]->GetDocumentPoint(0));
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
						}
					}
				}
				if (this->connect_lines[0] != this->connect_lines[1])
				{
//printf("edit_gdiplus_tool::Line_connect 4\n");
					if(
						(this->connect_lines_ind[0] == 0 || this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						&&
						(this->connect_lines_ind[1] == 0 || this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						)
					{
//printf("edit_gdiplus_tool::Line_connect 5\n");
						// нулевую линию сливаем к первой

						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = 0; i < (int)this->connect_lines[0]->GetPointsNumber(); i++)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}

							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_gdiplus_tool::Line_connect 6\n");
							return;

						}						
						
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = (int)this->connect_lines[0]->GetPointsNumber()-1; i >=0; i--)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}
							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_gdiplus_tool::Line_connect 7\n");
							return;
						}
						// первую линию сливаем к нулевой 
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == 0)
						{
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
//printf("edit_gdiplus_tool::Line_connect 8\n");
							return;
						}						
						
						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == 0)
						{
							this->connect_lines[0]->Reverse();
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_gdiplus_tool::Line_connect 9\n");
							return;
						}
						
					}
				}
			}
		}
	}
#endif
}





void project::EditEvent(graphics_view * gv, vector<iGLu> & names)
{
	if (ogl_view::button == mouse_tool::Right) return;	// the right button is for popup menus...

	i32s mouse[2] =
	{
		gv->current_tool->latest_x,
		gv->current_tool->latest_y
	};

	if (ogl_view::state == mouse_tool::state::Down)
	{
		edit_point = NULL;
		to_edit_line = false;
		to_insert = false;
	}

//	double epsilon = 0.000001;

	if (ogl_view::what_to_edit == edit_tool::what_to_edit::Line)
	{
		//if (ogl_view::what_to_edit == edit_tool::what_to_edit::Line_by_moving_existing_point)
		//{
		//printf("edit_tool::Line\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{		
//printf("if (ogl_view::state == mouse_tool::state::Down)\n");
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
				pt3))
			{
//printf("if (calc_select_line\n");
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
//printf("if (this->IsSelected\n");
					ogl_view::what_selected.PrintInfo();
					// если режим отображения линий с шариками - то меняем этот режим на тонкие без шариков
					/*if (old_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
					{
						Line3D::s_line3d_draw_mode = Line3D::line3d_draw_mode::as_thing_lines;
						// теперь мы должны перерисовать выбранный объект в новом режиме
						if(ogl_view::what_selected.GetObject())
						{
							ogl_view::what_selected.GetObject()->ReDraw();
							UpdateAllViews();
						}					
					}	*/	
					//снова ищем точку пересечения указателя мыши с объектами Open GL
					if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
							pt3))
					{
//printf("if(calc_select_line 2\n");
						// и если мы опять попали мышью по объекту
						if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
						{
//printf("if (this->IsSelected 2\n");
							ogl_view::what_selected.PrintInfo();
							if( ogl_view::what_selected.m_selected_objects_element_type 
								== WhatSelected::selected_objects_element_type::sel_point
								&& ogl_view::what_selected.GetObject())
							{	
//printf("if (m_selected_objects_element_type == sel_point\n");
								if(ogl_view::what_selected.GetObject()->IsPrimitive3())
								{
//printf("if (this->IsPrimitive3()\n");
									Primitive3D<CPoint3> * primitive3 
										= dynamic_cast<Primitive3D<CPoint3>*>
										(ogl_view::what_selected.GetObject());

									if (primitive3)
									{
//printf("if (primitive3)\n");
										if (ogl_view::what_selected.GetIndex() > -1 
											&& 
											ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
										{
//printf("if GetIndex() CPOINT3_FLAG_HIDE\n");
											//edit_point = &primitive3->GetViewPoint(ogl_view::what_selected.GetIndex());
											edit_point = &primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
											/*
											CPoint3& ptd = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
											// HIDE POINT - включаем 3-й бит 
											// в пользовательских данных point 
											ptd.flag |= CPOINT3_FLAG_HIDE;
											ogl_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
											Line3D::s_line3d_draw_mode = old_line3d_draw_mode;

//printf("pre ReDraw %s\n", Object::ObjectTypeToString(ogl_view::what_selected.GetObject()->GetObjectType()));

											ogl_view::what_selected.GetObject()->ReDraw();
											UpdateAllViews();*/
											return;
										}
									}
								}
							}
						}
					}
					// если режим отображения линий с шариками - то меняем этот режим 
					/*if (old_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
					{
						Line3D::s_line3d_draw_mode = old_line3d_draw_mode;
						// теперь мы должны перерисовать выбранный объект в новом режиме
						if(ogl_view::what_selected.GetObject())
						{
							ogl_view::what_selected.GetObject()->ReDraw();
							UpdateAllViews();
						}					
					}	*/			
				}
			}
		}
		if (ogl_view::state == mouse_tool::state::Up)
		{
//printf("edit_tool::Line Up\n");
			if( ogl_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_point
				&& ogl_view::what_selected.GetObject())
			{
				if (edit_point)
				{
					if(ogl_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(ogl_view::what_selected.GetObject());

						if (primitive3)
						{
							if (ogl_view::what_selected.GetIndex() > -1 
								&& 
								ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								
								if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
										pt3))
								{
												
									pt3.z = m_zd_zoom_center + pt3.z / this->m_zoomZ;
									pt3.y = m_yd_zoom_center + pt3.y / this->m_zoomY;
									pt3.x = m_xd_zoom_center + pt3.x / this->m_zoomX;

									if(this->CorrectDrawingPoint(ogl_view::what_selected.GetObject(), 
										pt3))
									{
										*edit_point = pt3;
										primitive3->Zoom(ogl_view::what_selected.GetIndex(),
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);
									}
								}
/*
								CPoint3& ptd = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
								// UN HIDE POINT - выключаем 3-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE;
								ogl_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
*/
								ogl_view::what_selected.GetObject()->ReDraw();

								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}
		//if (ogl_view::what_to_edit == edit_tool::what_to_edit::Line_by_add_new_point)
		//{
		//printf("edit_tool::Line_by_add_new_point\n");
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;


		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_line
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									printf("to_edit = true\n");
									to_edit_line = true;
									to_insert = true;
									//edit_point = &primitive3->GetViewPoint(ogl_view::what_selected.GetIndex());
									/*
									CPoint3& ptd = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
									// HIDE LINE - включаем 4-й бит 
									// в пользовательских данных point 
									ptd.flag |= CPOINT3_FLAG_HIDE_LINE;
									ogl_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
									//Line3D::s_line3d_draw_mode = old_line3d_draw_mode;

*/
									ogl_view::what_selected.GetObject()->ReDraw();
									UpdateAllViews();
									return;
								}
							}
						}
					}
				}
			}
		}
		if (ogl_view::state == mouse_tool::state::Up)
		{
			if( ogl_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_line
				&& ogl_view::what_selected.GetObject())
			{
				if (to_edit_line)
				{
					if(ogl_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(ogl_view::what_selected.GetObject());

						if (primitive3)
						{
							if (ogl_view::what_selected.GetIndex() > -1 
								&& 
								ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								bool can_disable_depth_test = Object::CanDisableDepthTest();
								/*if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
										pt3))
								{
									pt3.z = m_zd_zoom_center + pt3.z / this->m_zoomZ;
									pt3.y = m_yd_zoom_center + pt3.y / this->m_zoomY;
									pt3.x = m_xd_zoom_center + pt3.x / this->m_zoomX;
									if(	this->CorrectDrawingPoint(ogl_view::what_selected.GetObject(), pt3))
									{
										//*edit_point = pt3;
										primitive3->Insert(ogl_view::what_selected.GetIndex()+1,pt3);
										primitive3->Zoom(ogl_view::what_selected.GetIndex()+1,
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);
									}

								}

								/*CPoint3& ptd = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
								// UN HIDE LINE - выключаем 4-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
								ogl_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
*/
								ogl_view::what_selected.GetObject()->ReDraw();
								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}


	}

	/*if (ogl_view::what_to_edit == edit_tool::Line_cut_by_double_new_point_on_bond)
	{
		printf("edit_tool::Line_cut_by_double_new_point_on_bond\n");
	}*/
	if (ogl_view::what_to_edit == edit_tool::Line_cut_by_select_and_delete_bond)
	{
		//printf("edit_tool::Line_cut_by_select_and_delete_bond\n");

		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;

		CPoint3 pt3;

		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_line
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
										if (pob && pob->IsClosed())
										{
											if (ogl_view::what_selected.GetIndex() > 0)
											{
												if (pob->UnClose(ogl_view::what_selected.GetIndex()))
												{
													pob->ReDraw();
                                                    
													UpdateAllViews();
													return;
												}
											}
										}
										if (pob && (!pob->IsClosed()) && ogl_view::what_selected.GetObject()->GetObjectList() && ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (ogl_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												if (ogl_view::what_selected.GetIndex() > 0)
												{
													//----------------------------------------
													Line3D line(this);
													pvect->AddMsg(&line);
													for (unsigned int i = 0; 
														i <= ogl_view::what_selected.GetIndex() && 
														i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(ogl_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(ogl_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().SetLayer(ogl_view::what_selected.GetObject()->GetLayer());
													pvect->GetLastMsg().Select(false);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												if (pob->GetPointsNumber() - (ogl_view::what_selected.GetIndex()+1) > 1)
												{
													//----------------------------------------
													Line3D line2(this);
													pvect->AddMsg(&line2);
													for (unsigned int i = ogl_view::what_selected.GetIndex()+1; i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(ogl_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(ogl_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().SetLayer(ogl_view::what_selected.GetObject()->GetLayer());

													pvect->GetLastMsg().Select(false);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												ogl_view::what_selected.GetObject()->GetObjectList()->Init(*pvect, ogl_view::what_selected.GetObject()->GetObjectList()->GetParent());

												ogl_view::what_selected.GetObject()->m_bChecked = false;
												TreeView_MySetCheckState(this->hwndTV, 
													ogl_view::what_selected.GetObject()->myTreeItem, 
													ogl_view::what_selected.GetObject()->m_bChecked);
					
																		
												ogl_view::what_selected.
													EraseSelectedObject<Line3D>
													(hwndTV,Object::object_type::line3d);
						
												UpdateAllViews();
												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (ogl_view::what_to_edit == edit_tool::Line_cut_by_select_and_double_point)
	{
		//printf("edit_tool::Line_cut_by_select_and_double_point\n");
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;

		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
										if (pob && ogl_view::what_selected.GetObject()->GetObjectList() && ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (ogl_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												if (ogl_view::what_selected.GetIndex() > 0)
												{
													//----------------------------------------
													Line3D line(this);
													pvect->AddMsg(&line);
													for (unsigned int i = 0; 
														i <= ogl_view::what_selected.GetIndex() && 
														i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(ogl_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(ogl_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().Select(true);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												if (pob->GetPointsNumber() - (ogl_view::what_selected.GetIndex()+1) > 1)
												{
													//----------------------------------------
													Line3D line2(this);
													pvect->AddMsg(&line2);
													for (unsigned int i = ogl_view::what_selected.GetIndex()+1; i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(ogl_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(ogl_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().Select(false);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												ogl_view::what_selected.GetObject()->GetObjectList()->Init(*pvect, ogl_view::what_selected.GetObject()->GetObjectList()->GetParent());

												ogl_view::what_selected.GetObject()->m_bChecked = false;
												TreeView_MySetCheckState(this->hwndTV, 
													ogl_view::what_selected.GetObject()->myTreeItem, 
													ogl_view::what_selected.GetObject()->m_bChecked);

																		
												ogl_view::what_selected.
													EraseSelectedObject<Line3D>
													(hwndTV,Object::object_type::line3d);
						
					
												UpdateAllViews();
												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}



	if (ogl_view::what_to_edit == edit_tool::what_to_edit::Lines_connect)
	{
		//printf("edit_tool::Line_connect\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
//printf("edit_tool::Line_connect Down\n");
			this->connect_lines[0] = NULL;
			this->connect_vect_lines[0] = NULL;
			this->connect_lines_ind[0] = -1;

			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
										this->connect_lines[0] = pob;

										if (pob && ogl_view::what_selected.GetObject()->GetObjectList() && ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (ogl_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[0] = pvect;
												this->connect_lines_ind[0] = ogl_view::what_selected.GetIndex();



												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (ogl_view::state == mouse_tool::state::Up)
		{
//printf("edit_tool::Line_connect Up\n");
			this->connect_lines[1] = NULL;
			this->connect_vect_lines[1] = NULL;
			this->connect_lines_ind[1] = -1;

			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
										this->connect_lines[1] = pob;

										if (pob && ogl_view::what_selected.GetObject()->GetObjectList() && ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (ogl_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[1] = pvect;
												this->connect_lines_ind[1] = ogl_view::what_selected.GetIndex();


												
											}
										}
									}
								}
							}
						}
					}
				}
			}
/*printf("edit_tool::Line_connect 2\n");//*/
/*printf("this->connect_lines[0] 0x%08x\n"
		"this->connect_vect_lines[0] 0x%08x\n"
		"this->connect_lines_ind[0] %d\n"
		,
				this->connect_lines[0],
				this->connect_vect_lines[0],
				this->connect_lines_ind[0]
				);
printf("this->connect_lines[1] 0x%08x\n"
		"this->connect_vect_lines[1] 0x%08x\n"
		"this->connect_lines_ind[1] %d\n"
		,
				this->connect_lines[1],
				this->connect_vect_lines[1],
				this->connect_lines_ind[1]
				);//*/

			if (this->connect_lines[0] && this->connect_lines[1] &&
				this->connect_vect_lines[0] && this->connect_vect_lines[1])
			{
//printf("edit_tool::Line_connect 3\n");
				if (this->connect_lines[0] == this->connect_lines[1])
				{		
					if(
						(this->connect_lines_ind[0] == 0 && this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						||
						(this->connect_lines_ind[1] == 0 && this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						)
					{
						if(this->connect_lines[0]->GetPointsNumber() > 2)
						{
							this->connect_lines[0]->PushBack(this->connect_lines[0]->GetDocumentPoint(0));
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
						}
					}
				}
				if (this->connect_lines[0] != this->connect_lines[1])
				{
//printf("edit_tool::Line_connect 4\n");
					if(
						(this->connect_lines_ind[0] == 0 || this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						&&
						(this->connect_lines_ind[1] == 0 || this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						)
					{
//printf("edit_tool::Line_connect 5\n");
						// нулевую линию сливаем к первой

						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = 0; i < (int)this->connect_lines[0]->GetPointsNumber(); i++)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}

							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_tool::Line_connect 6\n");
							return;

						}						
						
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = (int)this->connect_lines[0]->GetPointsNumber()-1; i >=0; i--)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}
							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_tool::Line_connect 7\n");
							return;
						}
						// первую линию сливаем к нулевой 
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == 0)
						{
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
//printf("edit_tool::Line_connect 8\n");
							return;
						}						
						
						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == 0)
						{
							this->connect_lines[0]->Reverse();
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_tool::Line_connect 9\n");
							return;
						}
						
					}
				}
			}
		}


	}


	to_edit_line = false;
	edit_point = NULL;
}



void project::EditMotionEvent(graphics_view * gv, vector<iGLu> & names)
{
	if (ogl_view::button == mouse_tool::Right) return;	// the right button is for popup menus...

	i32s mouse[2] =
	{
		gv->current_tool->latest_x,
		gv->current_tool->latest_y
	};
//	double epsilon = 0.000001;

	if (ogl_view::what_to_edit == edit_tool::what_to_edit::Line)
	{
		//if (ogl_view::what_to_edit == edit_tool::what_to_edit::Line_by_moving_existing_point)
		//{
		//printf("edit_tool::Line\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		
		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
//printf("edit_tool::Line Down\n");
			if( ogl_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_point
				&& ogl_view::what_selected.GetObject())
			{
//printf("sel_point\n");
				if (edit_point)
				{
//printf("edit_point\n");
					if(ogl_view::what_selected.GetObject()->IsPrimitive3())
					{
//printf("IsPrimitive3\n");
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(ogl_view::what_selected.GetObject());

						if (primitive3)
						{
//printf("primitive3\n");
							if (ogl_view::what_selected.GetIndex() > -1 
								&& 
								ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
//printf("GetIndex() = %d\n", ogl_view::what_selected.GetIndex());
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								CPoint3 pt3;
								if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
										pt3))
								{
//printf("calc_sel_line");
									pt3.z = m_zd_zoom_center + pt3.z / this->m_zoomZ;
									pt3.y = m_yd_zoom_center + pt3.y / this->m_zoomY;
									pt3.x = m_xd_zoom_center + pt3.x / this->m_zoomX;
									if(	this->CorrectDrawingPoint(ogl_view::what_selected.GetObject(), pt3))
									{
//printf("CorrectDrawingPoint");
										*edit_point = pt3;
										primitive3->Zoom(ogl_view::what_selected.GetIndex(),
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);
									}
								}

								/*CPoint3& ptd = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
								// UN HIDE POINT - выключаем 3-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE;
								ogl_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;*/

								ogl_view::what_selected.GetObject()->ReDraw();

								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}
		//if (ogl_view::what_to_edit == edit_tool::what_to_edit::Line_by_add_new_point)
		//{
		//printf("edit_tool::Line_by_add_new_point\n");
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;


		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
//printf("Down2\n");
			if( ogl_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_line
				&& ogl_view::what_selected.GetObject())
			{
				if (to_edit_line)
				{
					if(ogl_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(ogl_view::what_selected.GetObject());

						if (primitive3)
						{
							if (ogl_view::what_selected.GetIndex() > -1 
								&& 
								ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								/*bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}*/
								CPoint3 pt3;
								if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
										pt3))
								{
									pt3.z = m_zd_zoom_center + pt3.z / this->m_zoomZ;
									pt3.y = m_yd_zoom_center + pt3.y / this->m_zoomY;
									pt3.x = m_xd_zoom_center + pt3.x / this->m_zoomX;
									if(	this->CorrectDrawingPoint(ogl_view::what_selected.GetObject(), pt3))
									{
										//*edit_point = pt3;
										if(to_insert)
										{
											primitive3->Insert(ogl_view::what_selected.GetIndex()+1,pt3);
											to_insert = false;
										}
										else
										{
											primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex()+1) = pt3;
										}
										primitive3->Zoom(ogl_view::what_selected.GetIndex()+1,
											this->m_zoomX, this->m_zoomY, this->m_zoomZ,
												m_xd_zoom_center,
												m_yd_zoom_center,
												m_zd_zoom_center);

									}
								}
/*
								CPoint3& ptd = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());
								// UN HIDE LINE - выключаем 4-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
								ogl_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;
*/
								ogl_view::what_selected.GetObject()->ReDraw();
								//Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}


	}

	/*if (ogl_view::what_to_edit == edit_tool::Line_cut_by_double_new_point_on_bond)
	{
		printf("edit_tool::Line_cut_by_double_new_point_on_bond\n");
	}*/
#if 0
	if (ogl_view::what_to_edit == edit_tool::what_to_edit::Lines_connect)
	{
		//printf("edit_tool::Line_connect\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		ogl_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (ogl_view::state == mouse_tool::state::Down)
		{
//printf("edit_tool::Line_connect Down\n");
			this->connect_lines[0] = NULL;
			this->connect_vect_lines[0] = NULL;
			this->connect_lines_ind[0] = -1;

			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
										this->connect_lines[0] = pob;

										if (pob && ogl_view::what_selected.GetObject()->GetObjectList() && ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (ogl_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[0] = pvect;
												this->connect_lines_ind[0] = ogl_view::what_selected.GetIndex();



												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (ogl_view::state == mouse_tool::state::Up)
		{
//printf("edit_tool::Line_connect Up\n");
			this->connect_lines[1] = NULL;
			this->connect_vect_lines[1] = NULL;
			this->connect_lines_ind[1] = -1;

			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									printf("to_edit = true\n");

									if (ogl_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(ogl_view::what_selected.GetObject());
										this->connect_lines[1] = pob;

										if (pob && ogl_view::what_selected.GetObject()->GetObjectList() && ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (ogl_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(ogl_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[1] = pvect;
												this->connect_lines_ind[1] = ogl_view::what_selected.GetIndex();


												
											}
										}
									}
								}
							}
						}
					}
				}
			}
/*printf("edit_tool::Line_connect 2\n");//*/
/*printf("this->connect_lines[0] 0x%08x\n"
		"this->connect_vect_lines[0] 0x%08x\n"
		"this->connect_lines_ind[0] %d\n"
		,
				this->connect_lines[0],
				this->connect_vect_lines[0],
				this->connect_lines_ind[0]
				);
printf("this->connect_lines[1] 0x%08x\n"
		"this->connect_vect_lines[1] 0x%08x\n"
		"this->connect_lines_ind[1] %d\n"
		,
				this->connect_lines[1],
				this->connect_vect_lines[1],
				this->connect_lines_ind[1]
				);//*/

			if (this->connect_lines[0] && this->connect_lines[1] &&
				this->connect_vect_lines[0] && this->connect_vect_lines[1])
			{
//printf("edit_tool::Line_connect 3\n");
				if (this->connect_lines[0] == this->connect_lines[1])
				{		
					if(
						(this->connect_lines_ind[0] == 0 && this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						||
						(this->connect_lines_ind[1] == 0 && this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						)
					{
						if(this->connect_lines[0]->GetPointsNumber() > 2)
						{
							this->connect_lines[0]->PushBack(this->connect_lines[0]->GetDocumentPoint(0));
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
						}
					}
				}
				if (this->connect_lines[0] != this->connect_lines[1])
				{
//printf("edit_tool::Line_connect 4\n");
					if(
						(this->connect_lines_ind[0] == 0 || this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						&&
						(this->connect_lines_ind[1] == 0 || this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						)
					{
//printf("edit_tool::Line_connect 5\n");
						// нулевую линию сливаем к первой

						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = 0; i < (int)this->connect_lines[0]->GetPointsNumber(); i++)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}

							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_tool::Line_connect 6\n");
							return;

						}						
						
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = (int)this->connect_lines[0]->GetPointsNumber()-1; i >=0; i--)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}
							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_tool::Line_connect 7\n");
							return;
						}
						// первую линию сливаем к нулевой 
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == 0)
						{
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
//printf("edit_tool::Line_connect 8\n");
							return;
						}						
						
						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == 0)
						{
							this->connect_lines[0]->Reverse();
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_tool::Line_connect 9\n");
							return;
						}
						
					}
				}
			}
		}


	}


#endif
}

#if 0
void project::SelectEvent(graphics_view *, vector<iGLu> & names)
{
	if (names[0] == GLNAME_MD_TYPE1)
	{
		atom * ref = (atom *) names[1];
		bool selected = (ref->flags & ATOMFLAG_SELECTED);
		
		if (ogl_view::select_mode == select_tool::Residue || ogl_view::select_mode == select_tool::Chain)
		{
			if (ref_civ == NULL)
			{
				bool update = Question("Group information about chains/residues is needed for this operation.\nIs it OK to update group information?\n");
				if (!update) return;
				
				UpdateChains();
			}
			
			bool no_info = false;
			if (ref->id[1] == NOT_DEFINED) no_info = true;
			if (ogl_view::select_mode == select_tool::Residue && ref->id[2] == NOT_DEFINED) no_info = true;
			
			if (no_info)
			{
				Message("Sorry, no chain/residue information available for this atom.");
				return;
			}
		}
		
		if (ogl_view::select_mode == select_tool::Molecule)
		{
			if (!IsGroupsClean()) UpdateGroups();
		}
		
		iter_al it1;
		iter_al range1[2];
		iter_al range2[2];
		
		if (selected) cout << "de";
		switch (ogl_view::select_mode)
		{
			case select_tool::Atom:
			ref->flags ^= ATOMFLAG_SELECTED;
			cout << "selected atom " << ref->index << " (atomtype = " << hex << ref->atmtp << dec << ")." << endl;
			break;
			
			case select_tool::Residue:
			GetRange(1, ref->id[1], range1);		// get the chain!!!
			GetRange(2, range1, ref->id[2], range2);	// get the residue!!!
			for (it1 = range2[0];it1 != range2[1];it1++)
			{
				if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
				else (* it1).flags |= (ATOMFLAG_SELECTED);
			}
			
			cout << "selected residue " << ref->id[2] << " from chain " << ref->id[1] << "." << endl;
			break;
			
			case select_tool::Chain:
			GetRange(1, ref->id[1], range1);		// get the chain!!!
			for (it1 = range1[0];it1 != range1[1];it1++)
			{
				if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
				else (* it1).flags |= (ATOMFLAG_SELECTED);
			}
			
			cout << "selected chain " << ref->id[1] << "." << endl;
			break;
			
			case select_tool::Molecule:
			if (IsGroupsSorted())	// if atom_list is sorted, a quicker method based on model::GetRange() is used.
			{
				GetRange(0, ref->id[0], range1);		// get the molecule!!!
				for (it1 = range1[0];it1 != range1[1];it1++)
				{
					if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
					else (* it1).flags |= (ATOMFLAG_SELECTED);
				}
			}
			else
			{
				for (it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
				{
					if ((* it1).id[0] != ref->id[0]) continue;
					
					if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
					else (* it1).flags |= (ATOMFLAG_SELECTED);
				}
			}
			
			cout << "selected molecule " << ref->id[0] << "." << endl;
			break;
		}
		
		UpdateAllGraphicsViews();
	}
}
#endif
//#endif

void project::SelectEvent(graphics_view *, vector<iGLu> & names)
{
	if (names[0] == GLNAME_MD_TYPE1)
	{
		Object * ref = (Object *) names[1];
#if 1
#else
		bool selected = (ref->flags & ATOMFLAG_SELECTED);
		
		if (ogl_view::select_mode == select_tool::Residue || ogl_view::select_mode == select_tool::Chain)
		{
			if (ref_civ == NULL)
			{
				bool update = Question("Group information about chains/residues is needed for this operation.\nIs it OK to update group information?\n");
				if (!update) return;
				
				UpdateChains();
			}
			
			bool no_info = false;
			if (ref->id[1] == NOT_DEFINED) no_info = true;
			if (ogl_view::select_mode == select_tool::Residue && ref->id[2] == NOT_DEFINED) no_info = true;
			
			if (no_info)
			{
				Message("Sorry, no chain/residue information available for this atom.");
				return;
			}
		}
		
		if (ogl_view::select_mode == select_tool::Molecule)
		{
			if (!IsGroupsClean()) UpdateGroups();
		}
		
		iter_al it1;
		iter_al range1[2];
		iter_al range2[2];
		
		if (selected) cout << "de";
		switch (ogl_view::select_mode)
		{
			case select_tool::Atom:
			ref->flags ^= ATOMFLAG_SELECTED;
			cout << "selected atom " << ref->index << " (atomtype = " << hex << ref->atmtp << dec << ")." << endl;
			break;
			
			case select_tool::Residue:
			GetRange(1, ref->id[1], range1);		// get the chain!!!
			GetRange(2, range1, ref->id[2], range2);	// get the residue!!!
			for (it1 = range2[0];it1 != range2[1];it1++)
			{
				if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
				else (* it1).flags |= (ATOMFLAG_SELECTED);
			}
			
			cout << "selected residue " << ref->id[2] << " from chain " << ref->id[1] << "." << endl;
			break;
			
			case select_tool::Chain:
			GetRange(1, ref->id[1], range1);		// get the chain!!!
			for (it1 = range1[0];it1 != range1[1];it1++)
			{
				if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
				else (* it1).flags |= (ATOMFLAG_SELECTED);
			}
			
			cout << "selected chain " << ref->id[1] << "." << endl;
			break;
			
			case select_tool::Molecule:
			if (IsGroupsSorted())	// if atom_list is sorted, a quicker method based on model::GetRange() is used.
			{
				GetRange(0, ref->id[0], range1);		// get the molecule!!!
				for (it1 = range1[0];it1 != range1[1];it1++)
				{
					if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
					else (* it1).flags |= (ATOMFLAG_SELECTED);
				}
			}
			else
			{
				for (it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
				{
					if ((* it1).id[0] != ref->id[0]) continue;
					
					if (selected) (* it1).flags &= (~ATOMFLAG_SELECTED);
					else (* it1).flags |= (ATOMFLAG_SELECTED);
				}
			}
			
			cout << "selected molecule " << ref->id[0] << "." << endl;
			break;
		}
#endif
		UpdateAllGraphicsViews();
	}
}

void project::SelectEvent(graphics_view * gv)
{
	if (ogl_view::button == mouse_tool::Right) return;	// the right button is for popup menus...
//printf("project::SelectEvent\n");

	i32s mouse[2] =
	{
		gv->current_tool->latest_x,
		gv->current_tool->latest_y
	};
	if (ogl_view::state == mouse_tool::Down)
	{
		if (ogl_view::select_mode == select_tool::select_mode::Object)
		{
			ogl_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_no_element;
			CPoint3 pt3;
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if(ogl_view::what_selected.GetObject())
					{		
						if (ogl_view::what_selected.GetObject()->m_lParam & OBJECT_FLAG_SELECTED_BIT)
							// NOT SELECTED OBJECT - выключаем 2-й бит 
							// в пользовательских данных объекта
							ogl_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_SELECTED_BIT;
						else
							// SELECTED OBJECT - включаем 2-й бит 
							// в пользовательских данных объекта 
							ogl_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_SELECTED_BIT;

						ogl_view::what_selected.GetObject()->ReDraw();
						UpdateAllViews();
					}
				}
			}
		}

		if (ogl_view::select_mode == select_tool::select_mode::Objects_with_the_same_ID)
		{
//printf("if (ogl_view::select_mode == select_tool::select_mode::Objects_with_the_same_ID)\n");
			ogl_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_no_element;
			CPoint3 pt3;
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{
//printf("if (calc_select_line)\n");
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
//printf("if (IsSelected)\n");
					ogl_view::what_selected.PrintInfo();
					if(ogl_view::what_selected.GetObject())
					{
//printf("if (ogl_view::what_selected.GetObject()) type = %s\n", 
//	Object::ObjectTypeToString(ogl_view::what_selected.GetObject()->GetObjectType()));

						Object::SetObjectUserID_forCompare(
							ogl_view::what_selected.GetObject()->GetUserID());
//printf("if (ogl_view::what_selected.GetObject()) id = %d\n", 
//	ogl_view::what_selected.GetObject()->GetUserID());

						this->EnumObjects(0, 
							ogl_view::what_selected.GetObject()->m_lParam, NULL, 
							&Object::IsTheSameUserID,
							Select_Object);

						UpdateAllViews();
					}
				}
			}
		}

		if (ogl_view::select_mode == select_tool::select_mode::Objects_with_the_same_name)
		{
			ogl_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_no_element;
			CPoint3 pt3;
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if(ogl_view::what_selected.GetObject())
					{
						Object::SetObjectName_forCompare(
							ogl_view::what_selected.GetObject()->GetName());

						this->EnumObjects(0, 
							ogl_view::what_selected.GetObject()->m_lParam, NULL, 
							&Object::IsTheSameName,
							Select_Object);

						UpdateAllViews();
					}
				}
			}
		}

		if (ogl_view::select_mode == select_tool::select_mode::point_of_primitive)
		{
			ogl_view::what_selected.m_what_to_select = 
				WhatSelected::selected_objects_element_type::sel_point;
			CPoint3 pt3;
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					pt3))
			{
				if (this->IsSelected(pt3,this->m_sphere_radius,ogl_view::what_selected))
				{
					ogl_view::what_selected.PrintInfo();
					if( ogl_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& ogl_view::what_selected.GetObject())
					{	
						if(ogl_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(ogl_view::what_selected.GetObject());

							if (primitive3)
							{
								if (ogl_view::what_selected.GetIndex() > -1 
									&& 
									ogl_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									CPoint3& pt = primitive3->GetDocumentPoint(ogl_view::what_selected.GetIndex());

									if (pt.flag & CPOINT3_FLAG_SELECTED)
										// UN SELECTED POINT - выключаем 2-й бит 
										// в пользовательских данных point
										pt.flag &= ~CPOINT3_FLAG_SELECTED;
									else
										// SELECT OBJECT - включаем 2-й бит 
										// в пользовательских данных point 
										pt.flag |= CPOINT3_FLAG_SELECTED;

									ogl_view::what_selected.GetObject()->ReDraw();
									UpdateAllViews();
								}
							}
						}
					}
				}
			}
		}
	}
}


void project::MeasureEvent(graphics_view * gv, vector<iGLu> & names)
{
//printf("project::MeasureEvent\n");
	char mbuff1[256];
	ostrstream str1(mbuff1, sizeof(mbuff1));

	i32s mouse[2] =
	{
		gv->current_tool->latest_x,
		gv->current_tool->latest_y
	};
	if (ogl_view::state == mouse_tool::Down)
	{
		if (mt_a1 == NULL)
		{
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					mt_pt1))
			{
				this->mt_pt1_doc = this->ZoomInv(mt_pt1);
				mt_a1 = &mt_pt1_doc;
				printf("mt_a1 = [%f %f %f]\n", 
					mt_a1->x,
					mt_a1->y,
					mt_a1->z);
				return;
			}
			// this must be OK.
			/*str1 << "charge: " << ref->charge << endl << ends;
// my measure
const fGL * p1 = mt_a1->GetCRD(0);
cout << "el = " << mt_a1->el.GetSymbol() << " " << mt_a1->el.GetAtomicNumber() << " x = " << p1[0] << " y = " << p1[1] << " z = " << p1[2] << endl;
			PrintToLog(mbuff1);*/


		}
		else if (mt_a1 != NULL && mt_a2 == NULL)
		{
			//if (mt_a1 == ref) { mt_a1->flags &= (~ATOMFLAG_SELECTED); mt_a1 = NULL; return; }
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					mt_pt2))
			{
				this->mt_pt2_doc = this->ZoomInv(mt_pt2);
				mt_a2 = &mt_pt2_doc;
				printf("mt_a2 = [%f %f %f]\n", 
					mt_a2->x,
					mt_a2->y,
					mt_a2->z);	

				double dxy = Distance_xy(*mt_a1, *mt_a2);
				double d = Distance(*mt_a1, *mt_a2);
				printf("dx = %f dy = %f dz = %f\n", 
					mt_a2->x - mt_a1->x,
					mt_a2->y - mt_a1->y,
					mt_a2->z - mt_a1->z);
				printf("dxy = %f\n", dxy);
				printf("d = %f\n", d);
				//return;
			}
			/*mt_a2 = ref;	// this must be OK.
			
			iter_al itX;
for (itX = atom_list.begin();itX != atom_list.end();itX++) if (& (* itX) == mt_a1) break; if (itX == atom_list.end()) goto reset_all;
			
			const fGL * p1 = mt_a1->GetCRD(0);
			const fGL * p2 = mt_a2->GetCRD(0);

			

// my measure
cout  << "el = " << mt_a2->el.GetSymbol() << " " << mt_a2->el.GetAtomicNumber() << " x = " << p2[0] << " y = " << p2[1] << " z = " << p2[2] << endl;
			
			v3d<fGL> v1(p1, p2);
			fGL len = v1.len();
			
			str1 << "distance: " << len << " nm" << endl << ends;
			PrintToLog(mbuff1);*/
		}
		else if (mt_a1 != NULL && mt_a2 != NULL && mt_a3 == NULL)
		{
			if(calc_select_line(mouse[0], mouse[1], gv->size[1], //текущая высота окна.
					mt_pt3))
			{
				//mt_a3 = &mt_pt3;
				this->mt_pt3_doc = this->ZoomInv(mt_pt3);
				mt_a3 = &mt_pt3_doc;
				printf("mt_a3 = [%f %f %f]\n", 
					mt_a3->x,
					mt_a3->y,
					mt_a3->z);	
				return;
			}

			/*if (mt_a1 == ref) { mt_a1->flags &= (~ATOMFLAG_SELECTED); mt_a1 = mt_a2; mt_a2 = NULL; return; }
			else if (mt_a2 == ref) { mt_a2->flags &= (~ATOMFLAG_SELECTED); mt_a2 = NULL; return; }
			
			mt_a3 = ref;	// this must be OK.
			
			iter_al itX;
for (itX = atom_list.begin();itX != atom_list.end();itX++) if (& (* itX) == mt_a1) break; if (itX == atom_list.end()) goto reset_all;
for (itX = atom_list.begin();itX != atom_list.end();itX++) if (& (* itX) == mt_a2) break; if (itX == atom_list.end()) goto reset_all;
			
			const fGL * p1 = mt_a1->GetCRD(0);
			const fGL * p2 = mt_a2->GetCRD(0);
			const fGL * p3 = mt_a3->GetCRD(0);
			
// my measure
cout  << "el = " << mt_a3->el.GetSymbol() << " " << mt_a3->el.GetAtomicNumber() << " x = " << p3[0] << " y = " << p3[1] << " z = " << p3[2] << endl;
			v3d<fGL> v1(p2, p1);
			v3d<fGL> v2(p2, p3);
			fGL ang = v1.ang(v2) * 180.0 / M_PI;
			
			str1 << "angle: " << ang << " deg" << endl << ends;
			PrintToLog(mbuff1);*/
		}
		else
		{
			/*if (mt_a1 == ref) { mt_a1->flags &= (~ATOMFLAG_SELECTED); mt_a1 = mt_a2; mt_a2 = mt_a3; mt_a3 = NULL; return; }
			else if (mt_a2 == ref) { mt_a2->flags &= (~ATOMFLAG_SELECTED); mt_a2 = mt_a3; mt_a3 = NULL; return; }
			else if (mt_a3 == ref) { mt_a3->flags &= (~ATOMFLAG_SELECTED); mt_a3 = NULL; return; }
			
			const fGL * p1 = mt_a1->GetCRD(0);
			const fGL * p2 = mt_a2->GetCRD(0);
			const fGL * p3 = mt_a3->GetCRD(0);
			const fGL * p4 = ref->GetCRD(0);
			
			v3d<fGL> v1(p2, p1);
			v3d<fGL> v2(p2, p3);
			v3d<fGL> v3(p3, p4);
			fGL tor = v1.tor(v2, v3) * 180.0 / M_PI;
			
// my measure
cout  << "el = " << ref->el.GetSymbol() << " " << ref->el.GetAtomicNumber() << " x = " << p4[0] << " y = " << p4[1] << " z = " << p4[2] << endl;

			str1 << "torsion: " << tor << " deg " << endl << ends;
			PrintToLog(mbuff1);
			
			mt_a1->flags &= (~ATOMFLAG_SELECTED);
			mt_a2->flags &= (~ATOMFLAG_SELECTED);
			mt_a3->flags &= (~ATOMFLAG_SELECTED);
			ref->flags &= (~ATOMFLAG_SELECTED);*/
			
			goto reset_all;
		}		
	}
#if 0
	// PLEASE NOTE!!! we use always the 1st coordinate set here...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	// we can be sure that "ref" is always up-to-date but the stored pointers
	// mt_a1/2/3 can be invalid ; so check them before use. reset if problems.
	
	if (names[0] == GLNAME_MD_TYPE1)
	{
		atom * ref = (atom *) names[1];
		ref->flags ^= ATOMFLAG_SELECTED;
		UpdateAllGraphicsViews();
		
		if (mt_a1 == NULL)
		{
			mt_a1 = ref;	// this must be OK.
			str1 << "charge: " << ref->charge << endl << ends;
// my measure
const fGL * p1 = mt_a1->GetCRD(0);
cout << "el = " << mt_a1->el.GetSymbol() << " " << mt_a1->el.GetAtomicNumber() << " x = " << p1[0] << " y = " << p1[1] << " z = " << p1[2] << endl;
			PrintToLog(mbuff1);


		}
		else if (mt_a1 != NULL && mt_a2 == NULL)
		{
			if (mt_a1 == ref) { mt_a1->flags &= (~ATOMFLAG_SELECTED); mt_a1 = NULL; return; }
			
			mt_a2 = ref;	// this must be OK.
			
			iter_al itX;
for (itX = atom_list.begin();itX != atom_list.end();itX++) if (& (* itX) == mt_a1) break; if (itX == atom_list.end()) goto reset_all;
			
			const fGL * p1 = mt_a1->GetCRD(0);
			const fGL * p2 = mt_a2->GetCRD(0);

			

// my measure
cout  << "el = " << mt_a2->el.GetSymbol() << " " << mt_a2->el.GetAtomicNumber() << " x = " << p2[0] << " y = " << p2[1] << " z = " << p2[2] << endl;
			
			v3d<fGL> v1(p1, p2);
			fGL len = v1.len();
			
			str1 << "distance: " << len << " nm" << endl << ends;
			PrintToLog(mbuff1);
		}
		else if (mt_a1 != NULL && mt_a2 != NULL && mt_a3 == NULL)
		{
			if (mt_a1 == ref) { mt_a1->flags &= (~ATOMFLAG_SELECTED); mt_a1 = mt_a2; mt_a2 = NULL; return; }
			else if (mt_a2 == ref) { mt_a2->flags &= (~ATOMFLAG_SELECTED); mt_a2 = NULL; return; }
			
			mt_a3 = ref;	// this must be OK.
			
			iter_al itX;
for (itX = atom_list.begin();itX != atom_list.end();itX++) if (& (* itX) == mt_a1) break; if (itX == atom_list.end()) goto reset_all;
for (itX = atom_list.begin();itX != atom_list.end();itX++) if (& (* itX) == mt_a2) break; if (itX == atom_list.end()) goto reset_all;
			
			const fGL * p1 = mt_a1->GetCRD(0);
			const fGL * p2 = mt_a2->GetCRD(0);
			const fGL * p3 = mt_a3->GetCRD(0);
			
// my measure
cout  << "el = " << mt_a3->el.GetSymbol() << " " << mt_a3->el.GetAtomicNumber() << " x = " << p3[0] << " y = " << p3[1] << " z = " << p3[2] << endl;
			v3d<fGL> v1(p2, p1);
			v3d<fGL> v2(p2, p3);
			fGL ang = v1.ang(v2) * 180.0 / M_PI;
			
			str1 << "angle: " << ang << " deg" << endl << ends;
			PrintToLog(mbuff1);
		}
		else
		{
			if (mt_a1 == ref) { mt_a1->flags &= (~ATOMFLAG_SELECTED); mt_a1 = mt_a2; mt_a2 = mt_a3; mt_a3 = NULL; return; }
			else if (mt_a2 == ref) { mt_a2->flags &= (~ATOMFLAG_SELECTED); mt_a2 = mt_a3; mt_a3 = NULL; return; }
			else if (mt_a3 == ref) { mt_a3->flags &= (~ATOMFLAG_SELECTED); mt_a3 = NULL; return; }
			
			const fGL * p1 = mt_a1->GetCRD(0);
			const fGL * p2 = mt_a2->GetCRD(0);
			const fGL * p3 = mt_a3->GetCRD(0);
			const fGL * p4 = ref->GetCRD(0);
			
			v3d<fGL> v1(p2, p1);
			v3d<fGL> v2(p2, p3);
			v3d<fGL> v3(p3, p4);
			fGL tor = v1.tor(v2, v3) * 180.0 / M_PI;
			
// my measure
cout  << "el = " << ref->el.GetSymbol() << " " << ref->el.GetAtomicNumber() << " x = " << p4[0] << " y = " << p4[1] << " z = " << p4[2] << endl;

			str1 << "torsion: " << tor << " deg " << endl << ends;
			PrintToLog(mbuff1);
			
			mt_a1->flags &= (~ATOMFLAG_SELECTED);
			mt_a2->flags &= (~ATOMFLAG_SELECTED);
			mt_a3->flags &= (~ATOMFLAG_SELECTED);
			ref->flags &= (~ATOMFLAG_SELECTED);
			
			goto reset_all;
		}
		
		return;
	}
	
#endif
	reset_all:
	
	mt_a1 = mt_a2 = mt_a3 = NULL;
	UpdateAllViews();
}
#if 0
void project::DoFormula()
{
  double molweight = 0.0;
  int i;
  char buffer[1024];
  ostrstream str(buffer, sizeof(buffer));

  int count[ELEMENT_SYMBOLS];
  // These are the atomic numbers of the elements in alphabetical order.
  const int alphabetical[ELEMENT_SYMBOLS] = {
   89, 47, 13, 95, 18, 33, 85, 79, 5, 56, 4, 107, 83, 97, 35, 6, 20, 48,
   58, 98, 17, 96, 27, 24, 55, 29, 105, 66, 68, 99, 63, 9, 26, 100, 87, 31,
   64, 32, 1, 2, 72, 80, 67, 108, 53, 49, 77, 19, 36, 57, 3, 103, 71, 101,
   12, 25, 42, 109, 7, 11, 41, 60, 10, 28, 102, 93, 8, 76, 15, 91, 82, 46, 
   61, 84, 59, 78, 94, 88, 37, 75, 104, 45, 86, 44, 16, 51, 21, 34, 106, 14, 
   62, 50, 38, 73, 65, 43, 52, 90, 22, 81, 69, 92, 110, 23, 74, 54, 39, 70, 
   30, 40 };
  int index;

  for (i = 0; i < ELEMENT_SYMBOLS; i++)
    {
      count[i] = 0;
    }

  iter_al it2 = atom_list.begin();
  while (it2 != atom_list.end())
    {
      iter_al it3 = it2++;
      count[(* it3).el.GetAtomicNumber() - 1]++;
      molweight += (* it3).mass;
    }
  
  for (i = 0; i < ELEMENT_SYMBOLS; i++)
    {
      index = alphabetical[i] - 1;
      if (count[index] > 1)
	{
	  str << (element(index + 1)).GetSymbol() << count[index] << " ";
	}
      else if (count[index] == 1)
	{
	  str << (element(index + 1)).GetSymbol();
	}
    }

  str << endl;
  str << "MW: " << molweight << ends;
  Message(buffer);
}
#endif
void project::DoEnergyPlot1D(i32s inda, i32s indb, i32s indc, i32s indd, i32s div1, fGL start1, fGL end1, i32s optsteps)
{
	// 2003-11-17 : for IC modification and structure refinement, make a temporary molecular mechanics model.
#if 0
	i32s curr_eng_index = 0;	// if current setup is molecular mechanics, get the eng class...
	setup * tmpsu1 = GetCurrentSetup(); setup1_mm * tmpsu2 = dynamic_cast<setup1_mm *>(tmpsu1);
	if (tmpsu2 != NULL) curr_eng_index = GetCurrentSetup()->GetCurrEngIndex();
	
	model * tmpmdl = new model();	// the default setup here will be molecular mechanics!
	vector<atom *> av; vector<atom *> av_tmp;
	
	for (iter_al it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
	{
		atom newatm((* it1).el, (* it1).GetCRD(0), tmpmdl->GetCRDSetCount());
		tmpmdl->Add_Atom(newatm);
		
		av.push_back(& (* it1));
		av_tmp.push_back(& tmpmdl->GetLastAtom());
	}
	{
	for (iter_bl it1 = GetBondsBegin();it1 != GetBondsEnd();it1++)
	{
		i32u ind1 = 0;
		while (ind1 < av.size() && av[ind1] != (* it1).atmr[0]) ind1++;
		if (ind1 == av.size()) { cout << "fatal error! atom #1 not found." << endl; exit(EXIT_FAILURE); }
		
		i32u ind2 = 0;
		while (ind2 < av.size() && av[ind2] != (* it1).atmr[1]) ind2++;
		if (ind2 == av.size()) { cout << "fatal error! atom #2 not found." << endl; exit(EXIT_FAILURE); }
		
		bond newbnd(av_tmp[ind1], av_tmp[ind2], (* it1).bt);
		tmpmdl->AddBond(newbnd);
	}
	}
	engine * tmpeng = tmpmdl->GetCurrentSetup()->CreateEngineByIndex(curr_eng_index);
	
	// the temporary model is now ok, continue...
	
	engine * eng = GetCurrentSetup()->GetCurrentEngine();
	if (!eng) eng = GetCurrentSetup()->CreateEngineByIndex(GetCurrentSetup()->GetCurrEngIndex());
	
	i32s molnum = 0; i32s in_crdset = 0;
	
	i32s atmi1[4] = { inda, indb, indc, indd };
	atom * atmr1[4]; f64 range1[2];
	range1[0] = M_PI * start1 / 180.0;
	range1[1] = M_PI * end1 / 180.0;

	for (i32s n1 = 0;n1 < 4;n1++)
	{
		iter_al it1;
		
		it1 = tmpmdl->FindAtomByIndex(atmi1[n1]);
		if (it1 == tmpmdl->GetAtomsEnd()) { PrintToLog("ERROR : atom not found!\n"); return; }
		atmr1[n1] = & (* it1);
	}
	
// must call SortGroups() here because intcrd needs it ; however that might change the indices?!?!?! note that we convert to pointers above...
// must call SortGroups() here because intcrd needs it ; however that might change the indices?!?!?! note that we convert to pointers above...
// must call SortGroups() here because intcrd needs it ; however that might change the indices?!?!?! note that we convert to pointers above...
	if (!tmpmdl->IsGroupsClean()) tmpmdl->UpdateGroups();		// for internal coordinates...
	if (!tmpmdl->IsGroupsSorted()) tmpmdl->SortGroups(true);	// for internal coordinates...
	
	intcrd * tmpic = new intcrd((* tmpmdl), molnum, in_crdset);
	i32s ict1 = tmpic->FindTorsion(atmr1[1], atmr1[2]);
if (ict1 < 0) { PrintToLog("ERROR : could not find ic.\n"); return; }
	
	v3d<fGL> v1a(atmr1[1]->GetCRD(in_crdset), atmr1[0]->GetCRD(in_crdset));
	v3d<fGL> v1b(atmr1[1]->GetCRD(in_crdset), atmr1[2]->GetCRD(in_crdset));
	v3d<fGL> v1c(atmr1[2]->GetCRD(in_crdset), atmr1[3]->GetCRD(in_crdset));
	f64 oldt1 = v1a.tor(v1b, v1c);
	
	i32s fft1 = tmpeng->FindTorsion(atmr1[0], atmr1[1], atmr1[2], atmr1[3]);
if (ict1 < 0) { PrintToLog("ERROR : could not find tor-term.\n"); return; }
#endif
	
	const char * tit = "tor(deg)";
	const char * s1 = "tor(deg)"; const char * sv = "E(kJ/mol)";
	plot1d_view * plot = AddPlot1DView(PLOT_USERDATA_STRUCTURE, tit, s1, sv, true);

#if 0
	f64 tor1 = range1[0];
	{
	for (i32s s1 = 0; s1 < (div1 + 1);s1++)
	{
		tmpic->SetTorsion(ict1, tor1 - oldt1);
		tmpic->UpdateCartesian();
		
		CopyCRD(tmpmdl, tmpeng, 0);					// lock_local_structure needs coordinates!!!
		tmpeng->SetTorsionConstraint(fft1, tor1, 5000.0, true);
		
		// optimize...
		
		geomopt * opt = new geomopt(tmpeng, 100, 0.025, 10.0);		// optimal settings?!?!?
		
		for (i32s n1 = 0;n1 < optsteps;n1++)
		{
			opt->TakeCGStep(conjugate_gradient::Newton2An);
			if (!(n1 % 50)) cout << n1 << " " << opt->optval << " " << opt->optstp << endl;
		}
		
		CopyCRD(tmpeng, tmpmdl, 0);
		tmpmdl->CenterCRDSet(0, true);
		delete opt;
		
		for (/*i32u*/ n1 = 0;n1 < av_tmp.size();n1++)
		{
			const fGL * tmpcrd = av_tmp[n1]->GetCRD(0);
			av[n1]->SetCRD(0, tmpcrd[0], tmpcrd[1], tmpcrd[2]);
		}
		
		// compute energy for final structure...
		
		f64 value;
		CopyCRD(this, eng, 0);
		eng->Compute(0); value = eng->energy;
		
		// ...and add it to the plot.
		
		void * udata = convert_cset_to_plotting_udata(this, 0);
		plot->AddData(180.0 * tor1 / M_PI, value, udata);
		
		char mbuff1[256];
		strstream str1(mbuff1, sizeof(mbuff1));
		str1 << "tor = " << (180.0 * tor1 / M_PI) << " deg, energy = " << value << " kJ/mol." << endl << ends;
		PrintToLog(mbuff1);
		
		tor1 += (range1[1] - range1[0]) / (f64) div1;
	}
	}
	delete tmpic;
	delete tmpeng;
	delete tmpmdl;
#endif
	// the "eng" object is the setup->current_eng object, so there's no need to delete it...
	plot->SetCenterAndScale();
	plot->Update();
}

void project::DoEnergyPlot2D(i32s inda, i32s indb, i32s indc, i32s indd, i32s div1, fGL start1, fGL end1, i32s indi, i32s indj, i32s indk, i32s indl, i32s div2, fGL start2, fGL end2, i32s optsteps)
{
	// 2003-11-17 : for IC modification and structure refinement, make a temporary molecular mechanics model.
#if 0
	i32s curr_eng_index = 0;	// if current setup is molecular mechanics, get the eng class...
	setup * tmpsu1 = GetCurrentSetup(); setup1_mm * tmpsu2 = dynamic_cast<setup1_mm *>(tmpsu1);
	if (tmpsu2 != NULL) curr_eng_index = GetCurrentSetup()->GetCurrEngIndex();
	
	model * tmpmdl = new model();	// the default setup here will be molecular mechanics!
	vector<atom *> av; vector<atom *> av_tmp;
	
	for (iter_al it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
	{
		atom newatm((* it1).el, (* it1).GetCRD(0), tmpmdl->GetCRDSetCount());
		tmpmdl->Add_Atom(newatm);
		
		av.push_back(& (* it1));
		av_tmp.push_back(& tmpmdl->GetLastAtom());
	}
	{
	for (iter_bl it1 = GetBondsBegin();it1 != GetBondsEnd();it1++)
	{
		i32u ind1 = 0;
		while (ind1 < av.size() && av[ind1] != (* it1).atmr[0]) ind1++;
		if (ind1 == av.size()) { cout << "fatal error! atom #1 not found." << endl; exit(EXIT_FAILURE); }
		
		i32u ind2 = 0;
		while (ind2 < av.size() && av[ind2] != (* it1).atmr[1]) ind2++;
		if (ind2 == av.size()) { cout << "fatal error! atom #2 not found." << endl; exit(EXIT_FAILURE); }
		
		bond newbnd(av_tmp[ind1], av_tmp[ind2], (* it1).bt);
		tmpmdl->AddBond(newbnd);
	}
	}
	engine * tmpeng = tmpmdl->GetCurrentSetup()->CreateEngineByIndex(curr_eng_index);
	
	// the temporary model is now ok, continue...
	
	engine * eng = GetCurrentSetup()->GetCurrentEngine();
	if (!eng) eng = GetCurrentSetup()->CreateEngineByIndex(GetCurrentSetup()->GetCurrEngIndex());
	
	i32s molnum = 0; i32s in_crdset = 0;
	
	i32s atmi1[4] = { inda, indb, indc, indd };
	atom * atmr1[4]; f64 range1[2];
	range1[0] = M_PI * start1 / 180.0;
	range1[1] = M_PI * end1 / 180.0;
	
	i32s atmi2[4] = { indi, indj, indk, indl };
	atom * atmr2[4]; f64 range2[2];
	range2[0] = M_PI * start2 / 180.0;
	range2[1] = M_PI * end2 / 180.0;
	
	for (i32s n1 = 0;n1 < 4;n1++)
	{
		iter_al it1;
		
		it1 = tmpmdl->FindAtomByIndex(atmi1[n1]);
		if (it1 == tmpmdl->GetAtomsEnd()) { PrintToLog("ERROR : tor1 atom not found!\n"); return; }
		atmr1[n1] = & (* it1);
		
		it1 = tmpmdl->FindAtomByIndex(atmi2[n1]);
		if (it1 == tmpmdl->GetAtomsEnd()) { PrintToLog("ERROR : tor2 atom not found!\n"); return; }
		atmr2[n1] = & (* it1);
	}
	
// must call SortGroups() here because intcrd needs it ; however that might change the indices?!?!?! note that we convert to pointers above...
// must call SortGroups() here because intcrd needs it ; however that might change the indices?!?!?! note that we convert to pointers above...
// must call SortGroups() here because intcrd needs it ; however that might change the indices?!?!?! note that we convert to pointers above...
	if (!tmpmdl->IsGroupsClean()) tmpmdl->UpdateGroups();		// for internal coordinates...
	if (!tmpmdl->IsGroupsSorted()) tmpmdl->SortGroups(true);	// for internal coordinates...
	
	intcrd * tmpic = new intcrd((* tmpmdl), molnum, in_crdset);
	i32s ict1 = tmpic->FindTorsion(atmr1[1], atmr1[2]);
if (ict1 < 0) { PrintToLog("ERROR : could not find ic for tor1.\n"); return; }
	i32s ict2 = tmpic->FindTorsion(atmr2[1], atmr2[2]);
if (ict2 < 0) { PrintToLog("ERROR : could not find ic for tor2.\n"); return; }
	
	v3d<fGL> v1a(atmr1[1]->GetCRD(in_crdset), atmr1[0]->GetCRD(in_crdset));
	v3d<fGL> v1b(atmr1[1]->GetCRD(in_crdset), atmr1[2]->GetCRD(in_crdset));
	v3d<fGL> v1c(atmr1[2]->GetCRD(in_crdset), atmr1[3]->GetCRD(in_crdset));
	f64 oldt1 = v1a.tor(v1b, v1c);
	
	v3d<fGL> v2a(atmr2[1]->GetCRD(in_crdset), atmr2[0]->GetCRD(in_crdset));
	v3d<fGL> v2b(atmr2[1]->GetCRD(in_crdset), atmr2[2]->GetCRD(in_crdset));
	v3d<fGL> v2c(atmr2[2]->GetCRD(in_crdset), atmr2[3]->GetCRD(in_crdset));
	f64 oldt2 = v2a.tor(v2b, v2c);
	
	i32s fft1 = tmpeng->FindTorsion(atmr1[0], atmr1[1], atmr1[2], atmr1[3]);
if (ict1 < 0) { PrintToLog("ERROR : could not find tor-term for tor1.\n"); return; }
	i32s fft2 = tmpeng->FindTorsion(atmr2[0], atmr2[1], atmr2[2], atmr2[3]);
if (ict2 < 0) { PrintToLog("ERROR : could not find tor-term for tor2.\n"); return; }
#endif

	const char * s1 = "tor1(deg)"; const char * s2 = "tor2(deg)"; const char * sv = "E(kJ/mol)";
	plot2d_view * plot = AddPlot2DView(PLOT_USERDATA_STRUCTURE, s1, s2, sv, true);
#if 0
	f64 tor1 = range1[0];
	{
	for (i32s s1 = 0;s1 < (div1 + 1);s1++)
	{
		f64 tor2 = range2[0];
		for (i32s s2 = 0;s2 < (div2 + 1);s2++)
		{
			tmpic->SetTorsion(ict1, tor1 - oldt1);
			tmpic->SetTorsion(ict2, tor2 - oldt2);
			tmpic->UpdateCartesian();
			
			CopyCRD(tmpmdl, tmpeng, 0);					// lock_local_structure needs coordinates!!!
			tmpeng->SetTorsionConstraint(fft1, tor1, 5000.0, true);
			tmpeng->SetTorsionConstraint(fft2, tor2, 5000.0, true);
			
			// optimize...
			
			geomopt * opt = new geomopt(tmpeng, 100, 0.025, 10.0);		// optimal settings?!?!?
			{
			for (i32s n1 = 0;n1 < optsteps;n1++)
			{
				opt->TakeCGStep(conjugate_gradient::Newton2An);
				if (!(n1 % 50)) cout << n1 << " " << opt->optval << " " << opt->optstp << endl;
			}
			}
			CopyCRD(tmpeng, tmpmdl, 0);
			tmpmdl->CenterCRDSet(0, true);
			delete opt;
			
			for (i32u n1 = 0;n1 < av_tmp.size();n1++)
			{
				const fGL * tmpcrd = av_tmp[n1]->GetCRD(0);
				av[n1]->SetCRD(0, tmpcrd[0], tmpcrd[1], tmpcrd[2]);
			}
			
			// compute energy for final structure...
			
			f64 value;
			CopyCRD(this, eng, 0);
			eng->Compute(0); value = eng->energy;
			
			// ...and add it to the plot.
			
			void * udata = convert_cset_to_plotting_udata(this, 0);
			plot->AddData(180.0 * tor1 / M_PI, 180.0 * tor2 / M_PI, value, udata);
			
			char mbuff1[256];
			strstream str1(mbuff1, sizeof(mbuff1));
			str1 << "tor1 = " << (180.0 * tor1 / M_PI) << " deg, tor2 = " << (180.0 * tor2 / M_PI) << " deg, energy = " << value << " kJ/mol." << endl << ends;
			PrintToLog(mbuff1);
			
			tor2 += (range2[1] - range2[0]) / (f64) div2;
		}
		
		tor1 += (range1[1] - range1[0]) / (f64) div1;
	}
	}
	delete tmpic;
	delete tmpeng;
	delete tmpmdl;
#endif
	// the "eng" object is the setup->current_eng object, so there's no need to delete it...
	
	plot->SetCenterAndScale();
	plot->Update();
}
#if 0
void project::DoTransitionStateSearch(f64 deltae, f64 initfc)
{
Message("BUG notice : TSS and libmopac7 seem to have\nsome compatibility problems in versions >= 1.90\nsince untraceable segmentation faults occur...\n\ngcc-3.3 or libf2c changes??? 20050608 TH");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	transition_state_search * tss = new transition_state_search(this, deltae, initfc);
	if (tss->InitFailed()) { delete tss; return; }
	
	char txtbuff[256]; ostrstream txts1(txtbuff, sizeof(txtbuff));
	txts1 << "r-energy = " << tss->GetE(0) << "   " << "p-energy = " << tss->GetE(1) << "   ";
	txts1 << (tss->GetE(0) < tss->GetE(1) ? "r" : "p") << " is lower " << fabs(tss->GetE(0) - tss->GetE(1));
	txts1 << endl << ends; PrintToLog(txtbuff); cout << txtbuff;
	
	f64 erl = tss->GetE(0); f64 epl = tss->GetE(1);
	
	const char * s1 = "rc"; const char * sv = "E(kJ/mol)";
	rcp_view * plot = AddReactionCoordinatePlotView(PLOT_USERDATA_STRUCTURE, s1, sv, true);
	
	for (i32u n1 = 0;n1 < tss->patoms.size();n1++) plot->AddPAtom(tss->patoms[n1]);
	for (/*i32u*/ n1 = 0;n1 < tss->rbonds.size();n1++) plot->AddRBond(tss->rbonds[n1]);
	for (/*i32u*/ n1 = 0;n1 < tss->pbonds.size();n1++) plot->AddPBond(tss->pbonds[n1]);
	
	void * udata;
	
	// add the initial structures...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	udata = convert_cset_to_plotting_udata(this, 0);
	plot->AddData(tss->GetP(0), tss->GetE(0), udata);
	
	udata = convert_cset_to_plotting_udata(this, 1);
	plot->AddData(tss->GetP(1), tss->GetE(1), udata);
	
	// loop...
	// ^^^^^^^
	
	i32s prev_not_stored[2] = { false, false };
	while (true)
	{
		tss->Run(prev_not_stored);
		
		ostrstream txts2(txtbuff, sizeof(txtbuff));
		txts2 << "r-energy = " << tss->GetE(0) << "   " << "p-energy = " << tss->GetE(1) << "   ";
		txts2 << (tss->GetE(0) < tss->GetE(1) ? "r" : "p") << " is lower " << fabs(tss->GetE(0) - tss->GetE(1)) << "   ";
		
		if (tss->GetR(0) && tss->GetR(1))
		{
			txts2 << "READY!" << endl << ends; PrintToLog(txtbuff);
			break;
		}
		
		bool update[2] = { !tss->GetR(0), !tss->GetR(1) };
		if (tss->GetE(1) < erl) update[0] = false;
		if (tss->GetE(0) < epl) update[1] = false;
		
		if (!update[0] && !update[1])	// this is a deadlock situation, fix it...
		{
////////////////////////////////////////////////////////////////
//cout << (i32s) update[0] << (i32s) update[1] << " ";
//cout << (i32s) tss->GetR(0) << (i32s) tss->GetR(1) << "   ";
//cout << "DEADLOCK!!!" << endl; int rr;cin>>rr;
////////////////////////////////////////////////////////////////
			if (!tss->GetR(0) && tss->GetR(1)) update[0] = true;
			if (tss->GetR(0) && !tss->GetR(1)) update[1] = true;
			if (!update[0] && !update[1])
			{
				f64 delta1 = erl - tss->GetE(1);
				f64 delta2 = epl - tss->GetE(0);
				i32s uuu = (delta1 > delta2 ? 0 : 1);	// update the bigger one...
				update[uuu] = true;
			}
		}
		
		txts2 << (i32s) update[0] << (i32s) update[1] << " ";
		txts2 << (i32s) tss->GetR(0) << (i32s) tss->GetR(1);
		txts2 << endl << ends; PrintToLog(txtbuff); cout << txtbuff;
		
		tss->UpdateTargets(update);
		
		if (update[0])
		{
			udata = convert_cset_to_plotting_udata(this, 0);
			plot->AddData(tss->GetP(0), tss->GetE(0), udata);
			
			erl = tss->GetE(0);
		}
		
		if (update[1])
		{
			udata = convert_cset_to_plotting_udata(this, 1);
			plot->AddData(tss->GetP(1), tss->GetE(1), udata);
			
			epl = tss->GetE(1);
		}
		
		prev_not_stored[0] = !update[0];
		prev_not_stored[1] = !update[1];
	}
	
	delete tss;
	
	// create an approximate TS as an average of the two structures.
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	for (iter_al it1 = GetAtomsBegin();it1 != GetAtomsEnd();it1++)
	{
		const fGL * crdr = (* it1).GetCRD(0);
		const fGL * crdp = (* it1).GetCRD(1);
		
		fGL x = (crdr[0] + crdp[0]) / 2.0;
		fGL y = (crdr[1] + crdp[1]) / 2.0;
		fGL z = (crdr[2] + crdp[2]) / 2.0;
		
		(* it1).SetCRD(0, x, y, z);
	}
	
	PopCRDSets(1);		// remove the 2nd crd-set that is no longer needed.
	
	// refine the approximate TS using stationary state search...
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	DoStationaryStateSearch(100);
	f64 ts_e = GetCurrentSetup()->GetCurrentEngine()->energy;
	
	// add the final estimate of TS, and finish the plot.
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	udata = convert_cset_to_plotting_udata(this, 0);
	plot->AddData(0, ts_e, udata);
	
	plot->SortDataAndCalcRC();
	plot->SetCenterAndScale();
	plot->Update();
}
void project::DoStationaryStateSearch(i32s steps)
{
	engine * eng = GetCurrentSetup()->GetCurrentEngine();
	if (eng == NULL) GetCurrentSetup()->CreateCurrentEngine();
	eng = GetCurrentSetup()->GetCurrentEngine();
	if (eng == NULL) return;
	
	char mbuff1[256];
	ostrstream str1(mbuff1, sizeof(mbuff1));
	str1 << "Starting Stationary State Search ";
	str1 << "(setup = " << GetCurrentSetup()->GetClassName();
	str1 << ", engine = " << GetCurrentSetup()->GetEngineName(GetCurrentSetup()->GetCurrEngIndex());
	str1 << ")." << endl << ends;
	PrintToLog(mbuff1);
	
	CopyCRD(this, eng, 0);
	
	// use a small default steplength; also setting maximum steplength is important!!!
	stationary_state_search * sss = new stationary_state_search(eng, 25, 1.0e-7, 1.0e-5);
	
	char buffer[1024];
	PrintToLog("Cycle    Gradient       Step\n");
	
	i32s n1 = 0;	// n1 counts the number of steps...
	while (true)
	{
		sss->TakeCGStep(conjugate_gradient::Simple);
		
		sprintf(buffer, "%4d %10.4e %10.4e \n", n1, sss->optval, sss->optstp);
		
		PrintToLog(buffer);
		
		bool terminate = false;
		if (n1 >= steps)
		{
			terminate = true;
			PrintToLog("the nsteps termination test was passed.\n");
		}
		
		if (!(n1 % 10) || terminate)
		{
			CopyCRD(eng, this, 0);
			CenterCRDSet(0, true);
			
			UpdateAllGraphicsViews(true);
		}
		
		if (terminate) break;		// exit the loop here!!!
		
		n1++;	// update the number of steps...
	}
	
	delete sss;
	
// we will not delete current_eng here, so that we can draw plots using it...
	
	// above, CopyCRD was done eng->mdl and then CenterCRDSet() was done for mdl.
	// this might cause that old coordinates remain in eng object, possibly affecting plots.
	// here we sync the coordinates and other plotting data in the eng object.
	
	CopyCRD(this, eng, 0);
	SetupPlotting();
}
#endif
void project::OrbitObject(graphics_view * gv, const fGL * ang)
{
	if (gv)
	{


//in class dummy_object
	//friend class project;// my test insert for project::OrbitObject

/*		gv->cam->GetLocDataRW()->ydir[0] = 0.0;
		gv->cam->GetLocDataRW()->ydir[1] = 0.0;
		gv->cam->GetLocDataRW()->ydir[2] = 1.0;

		gv->cam->GetLocDataRW()->zdir[0] = 0.0;
		gv->cam->GetLocDataRW()->zdir[1] = 1.0;
		gv->cam->GetLocDataRW()->zdir[2] = 0.0;

		gv->cam->GetLocDataRW()->zdir[0] = ang[2];
*/
		//gv->cam->SetModelView();
		//gv->cam->RotateObject(ang,*gv->cam);
		gv->cam->OrbitObject(ang, *gv->cam, 0);
		UpdateGraphicsViews(gv->cam);
		UpdateAllGraphicsViews();




		printf("gv->cam->GetLocData()->ydir[0] = %f\n",
			gv->cam->GetLocData()->ydir[0]);
		printf("gv->cam->GetLocData()->ydir[1] = %f\n",
			gv->cam->GetLocData()->ydir[1]);
		printf("gv->cam->GetLocData()->ydir[2] = %f\n",
			gv->cam->GetLocData()->ydir[2]);

		printf("gv->cam->GetLocData()->zdir[0] = %f\n",
			gv->cam->GetLocData()->zdir[0]);
		printf("gv->cam->GetLocData()->zdir[1] = %f\n",
			gv->cam->GetLocData()->zdir[1]);
		printf("gv->cam->GetLocData()->zdir[2] = %f\n",
			gv->cam->GetLocData()->zdir[2]);

		printf("gv->cam->GetLocData()->crd[0] = %f\n",
			gv->cam->GetLocData()->crd[0]);
		printf("gv->cam->GetLocData()->crd[1] = %f\n",
			gv->cam->GetLocData()->crd[1]);
		printf("gv->cam->GetLocData()->crd[2] = %f\n",
			gv->cam->GetLocData()->crd[2]);
		printf("gv->cam->GetLocData()->crd[3] = %f\n",
			gv->cam->GetLocData()->crd[3]);	}
}

/*################################################################################################*/

dummy_project::dummy_project(graphics_class_factory * p1) : project(* p1)
{
}

dummy_project::~dummy_project(void)
{
}

/*################################################################################################*/

void color_mode_element::GetColor4(const void * dd, i32s cs, fGL * pp)
{
//	atom * ref = (atom *) dd;
//	const fGL * color = ref->el.GetColor();
//	pp[0] = color[0]; pp[1] = color[1]; pp[2] = color[2]; pp[3] = 1.0;
}

void color_mode_secstruct::GetColor4(const void * dd, i32s cs, fGL * pp)
{
#if 0
	atom * ref = (atom *) dd;
	model * mdl = ref->GetModel();
	
	pp[0] = 0.0; pp[1] = 0.0; pp[2] = 1.0; pp[3] = 0;	// loop
	
	if (mdl == NULL || mdl->ref_civ == NULL) return;
	if (ref->id[1] < 0 || ref->id[2] < 0) return;
	
	vector<chn_info> & ci_vector = (* mdl->ref_civ);
	const char * tmptab = ci_vector[ref->id[1]].GetSecStrStates();
	if (tmptab == NULL) return;
	char state = tmptab[ref->id[2]];
	
	switch (state)
	{
		case '4':
		pp[0] = 1.0; pp[1] = 0.0; pp[2] = 0.0;		// helix
		return;
		
		case 'S':
		pp[0] = 0.0; pp[1] = 1.0; pp[2] = 0.0;		// strand
		return;
	}
#endif
}

void color_mode_hydphob::GetColor4(const void * dd, i32s cs, fGL * pp)
{
#if 0
	atom * ref = (atom *) dd;
	model * mdl = ref->GetModel();
	
	pp[0] = 0.0; pp[1] = 0.5; pp[2] = 0.0; pp[3] = 0;	// default...
	
	if (mdl == NULL || mdl->ref_civ == NULL) return;
	if (ref->id[1] < 0 || ref->id[2] < 0) return;
	
	vector<chn_info> & ci_vector = (* mdl->ref_civ);
	const char * tmptab = ci_vector[ref->id[1]].GetSequence();
	
	if (tmptab == NULL) return;
	char state = tmptab[ref->id[2]];
	
	
	switch (state)
	{
		case 'A':
		case 'G':
		pp[0] = 0.0; pp[1] = 1.0; pp[2] = 0.0;		// ala/gly
		return;
		
		case 'V':
		case 'F':
		case 'I':
		case 'L':
		case 'P':
		case 'M':
		pp[0] = 1.0; pp[1] = 0.0; pp[2] = 0.0;		// hydrophobic
		return;
		
		case 'D':
		case 'E':
		case 'K':
		case 'R':
		pp[0] = 0.2; pp[1] = 0.2; pp[2] = 1.0;		// charged
		return;
		
		case 'S':
		case 'T':
		case 'Y':
		case 'C':
		case 'N':
		case 'Q':
		case 'H':
		case 'W':
		pp[0] = 0.0; pp[1] = 1.0; pp[2] = 2.0;		// polar
		return;
	}
#endif
}

/*################################################################################################*/

transparent_primitive::transparent_primitive(void)
{
	owner = NULL; data = NULL;
	z_distance = 0.0;
}

transparent_primitive::transparent_primitive(void * p1, transparent_primitive_data & p2)
{
	owner = p1; data = & p2;
	z_distance = 0.0;
}

transparent_primitive::transparent_primitive(const transparent_primitive & p1)
{
	owner = p1.owner; data = p1.data;
	z_distance = p1.z_distance;
}

transparent_primitive::~transparent_primitive(void)
{
}

bool transparent_primitive::TestOwner(void * p1) const
{
	return (owner == p1);
}

transparent_primitive_data * transparent_primitive::GetData(void) const
{
	return data;
}

void transparent_primitive::UpdateDistance(const fGL * crd_c, const fGL * zdir)
{
	fGL crd_p[3];
	crd_p[0] = data->midpoint[0] - crd_c[0];
	crd_p[1] = data->midpoint[1] - crd_c[1];
	crd_p[2] = data->midpoint[2] - crd_c[2];
	
	// if we mark the vector from crd_c to crd_p as v1, and angle between v1 and zdir as angle
	// alpha, we have
	//
	//	zdist = cos(alpha) * |v1|			, where |v1| = length of v1. since
	//
	//	cos(alpha) = ip(v1,zdir) / (|zdir| * |v1|)	, we have
	//
	//	zdist = ip(v1,zdir) / |zdir|			, and if zdir is a unit vector,
	//
	//	zdist = ip(v1,zdir)
	
	z_distance = crd_p[0] * zdir[0] + crd_p[1] * zdir[1] + crd_p[2] * zdir[2];
}

bool transparent_primitive::operator<(const transparent_primitive & p1) const
{
	return (z_distance > p1.z_distance);	// inverted order...
}

/*################################################################################################*/

transparent_primitive_data::transparent_primitive_data(void)
{
}

transparent_primitive_data::~transparent_primitive_data(void)
{
}

/*################################################################################################*/

tpd_tri_3c::tpd_tri_3c(fGL * c1, fGL * p1, fGL * c2, fGL * p2, fGL * c3, fGL * p3)
{
	color[0] = c1;
	color[1] = c2;
	color[2] = c3;
	
	point[0] = p1;
	point[1] = p2;
	point[2] = p3;
	
	UpdateMP();
}

tpd_tri_3c::~tpd_tri_3c(void)
{
}

void tpd_tri_3c::Render(void)
{
	glBegin(GL_TRIANGLES);
	
	glColor4fv(color[0]);
	glVertex3fv(point[0]);
	
	glColor4fv(color[1]);
	glVertex3fv(point[1]);
	
	glColor4fv(color[2]);
	glVertex3fv(point[2]);
	
	glEnd();	// GL_TRIANGLES
}

void tpd_tri_3c::UpdateMP(void)
{
	midpoint[0] = (point[0][0] + point[1][0] + point[2][0]) / 3.0;
	midpoint[1] = (point[0][1] + point[1][1] + point[2][1]) / 3.0;
	midpoint[2] = (point[0][2] + point[1][2] + point[2][2]) / 3.0;
}

/*################################################################################################*/

tpd_quad_4c::tpd_quad_4c(fGL * c1, fGL * p1, fGL * c2, fGL * p2, fGL * c3, fGL * p3, fGL * c4, fGL * p4)
{
	color[0] = c1;
	color[1] = c2;
	color[2] = c3;
	color[3] = c4;
	
	point[0] = p1;
	point[1] = p2;
	point[2] = p3;
	point[3] = p4;
	
	UpdateMP();
}

tpd_quad_4c::~tpd_quad_4c(void)
{
}

void tpd_quad_4c::Render(void)
{
	glBegin(GL_QUADS);
	
	glColor4fv(color[0]);
	glVertex3fv(point[0]);
	
	glColor4fv(color[1]);
	glVertex3fv(point[1]);
	
	glColor4fv(color[2]);
	glVertex3fv(point[2]);
	
	glColor4fv(color[3]);
	glVertex3fv(point[3]);
	
	glEnd();	// GL_QUADS
}

void tpd_quad_4c::UpdateMP(void)
{
	midpoint[0] = (point[0][0] + point[1][0] + point[2][0] + point[3][0]) / 4.0;
	midpoint[1] = (point[0][1] + point[1][1] + point[2][1] + point[3][1]) / 4.0;
	midpoint[2] = (point[0][2] + point[1][2] + point[2][2] + point[3][2]) / 4.0;
}

/*################################################################################################*/

// eof
