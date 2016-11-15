// SurfDoc.cpp : implementation of the SurfDoc class
//

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

#include <iostream>

#define TRACE              printf

#include "stdafx.h"
#include ".\surfdoc.h"
//#include "raporto.h"
#include "drawscene.h"
#include "..\..\dct\src\DelaunayTriangulation.h"
#include "distance3d.h"
#include ".\whatselected.h"
#include "../../mylicense.h"
//u_int SurfDoc::s_nDocs = 0;
#include "../../array/src/interp.h"
#include "../../array/src/matrixes.h"
#include "../../wintools/src/project.h"
#include "../../lab/lab/labdoc.h"
#include "../../wintools/src/listfun.h"


#include "../surfer_connect/mysurfer.h"
#include "logger/Logger.h"

extern int ChooseSurfColor(HWND hwndOwner, COLORREF& color);
extern void sortrows21(vdouble& x, vdouble& y, vdouble& z);
extern float **AllocFloatMat (int size1, int size2) ;
extern void FreeFloatMat(float ** v);
extern HINSTANCE hInst;   // текущий экземпляр
extern LPCSTR colormaps[];
extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);
extern char directory[];
extern HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex);
extern char szPath[];

SSaveProfData SurfDoc::sprData;

//#include <atlconv.h>

/////////////////////////////////////////////////////////////////////////////
// SurfDoc construction/destruction
void SurfDoc::InitSurfDoc (Vector<vdouble> &vx, Vector<vdouble> &vy, Vector<vdouble> &vz
				  /*, LPSTR sTitle, LPSTR sX, LPSTR sY*/)
{
	if (vx.Size() != vy.Size() ||
		vx.Size() != vz.Size() ||
		vy.Size() != vz.Size())
	{
		char s[63];
		sprintf(s, "vx.Size(%d) != vy.Size(%d) != vz.Size(%d) ", vx.Size(), vy.Size(), vz.Size() );
		MessageBox(0,s, "SurfDoc", 0);
		return;
	}

	for (int iv = 0; iv < vx.Size(); iv++)
	{
		if (vz[iv].GetDims() == 2)
		{
			vdouble visible;
			visible.resize(vy[iv].Length(), vx[iv].Length(), 1.0);
			long id_surf = this->GetIDSurfForNewGridDataOrSurface();
			BYTE podoshva = 0;
			AddSurf(id_surf, podoshva, 0,vx[iv],vy[iv],vz[iv], visible);
		}
		else
		{
			AddLine(vx[iv],vy[iv],vz[iv], 0);
		}
	}
	ZoomView(false);
	this->Draw();
}
void
SurfDoc::InitSurfDoc(Vector<int>& lines_break_indexes, vdouble& x, vdouble& y, vdouble& z)
{
	if (x.Length() == y.Length() && y.Length() == z.Length())
	{
		int len = x.Length();
		CPoint3 * pt3;
		pt3 = new CPoint3[len];
		for (int i = 0; i < len; i++)
		{
			pt3[i] = CPoint3(x[i], y[i], z[i]);
		}
		int i0 = 0;
		for (int j = 0; j < lines_break_indexes.Size(); j++)
		{
			if (lines_break_indexes[j] < len)
			{
				this->AddLine(pt3+i0, lines_break_indexes[j] - i0,0);
				i0 = lines_break_indexes[j];
			}

		}
	}
	ZoomView(false);
	this->Draw();
}
void
SurfDoc::InitSurfDoc(vector<cut_of_line>& line_cutting_vector, 
			int ix, int iy,
			vector<vector<double> >& data)
{
	int cols = (int)data.size();
	if ( ix < cols && iy < cols && ix >= 0 && iy >= 0)
	{
		int len = (int)data[ix].size();
		CPoint3 * pt3;
		pt3 = new CPoint3[len];
		int nparam = cols - iy-1;
		DrawListArray::SetParametersNumber(nparam);
		vector<COLORREF> vcolor;
		vcolor.resize(nparam);
		for (int n = 0; n < nparam; n++)
		{
			switch (n%3)
			{
			case 0:
				vcolor[n] = RGB(255,0,0);
				break;
			case 1:
				vcolor[n] = RGB(0,255,0);
				break;
			case 2:
				vcolor[n] = RGB(0,0,255);
				break;
			}
		}

#if 0
		for (int col = iy + 1; col < cols; col++)
		{
			//###################################################################
			for (int i = 0; i < len; i++)
			{
				pt3[i] = CPoint3(data[ix][i], data[iy][i], data[col][i]);
			}
			for (int j = 0; j < line_cutting_vector.size(); j++)
			{
				this->AddLine(
					pt3+line_cutting_vector[j].i_start, 
					line_cutting_vector[j].i_finish - line_cutting_vector[j].i_start,
					0);
			}
			//###################################################################
		}
#else
		for (size_t j = 0; j < line_cutting_vector.size(); j++)
		{
			//###################################################################
			for (int col = iy + 1; col < cols; col++)
			{
				/*for (int i = 0; i < len; i++)
				{
					pt3[i] = CPoint3(data[ix][i], data[iy][i], data[col][i]);
				}*/
				for (int i = line_cutting_vector[j].i_start; i < line_cutting_vector[j].i_finish; i++)
				{
					pt3[i] = CPoint3(data[ix][i], data[iy][i], data[col][i]);
				}
				this->AddLine(
					pt3+line_cutting_vector[j].i_start, 
					line_cutting_vector[j].i_finish - line_cutting_vector[j].i_start,
					vcolor[col - (iy + 1)]
					);
			}
			//###################################################################
		}
#endif
		delete[] pt3;
	}
	ZoomView(false);
	this->Draw();
}
void SurfDoc::InitSurfDoc(vector<int>& lines_break_indexes, vector<double>& x, vector<double>& y, vector<double>& z)
{
	if (x.size() == y.size() && y.size() == z.size())
	{
		int len = (int)x.size();
		CPoint3 * pt3;
		pt3 = new CPoint3[len];
		for (int i = 0; i < len; i++)
		{
			pt3[i] = CPoint3(x[i], y[i], z[i]);
		}
		int i0 = 0;
		for (size_t j = 0; j < lines_break_indexes.size(); j++)
		{
			if (lines_break_indexes[j] < len)
			{
				this->AddLine(pt3+i0, lines_break_indexes[j] - i0,0);
				i0 = lines_break_indexes[j];
			}

		}
		delete[] pt3;
	}
	ZoomView(false);
	this->Draw();
}
void SurfDoc::InitSurfDoc(vector<cut_of_line>& line_cutting_vector, vector<double>& x, vector<double>& y, vector<double>& z)
{
	if (x.size() == y.size() && y.size() == z.size())
	{
		int len = (int)x.size();
		int nparam = 1;
		DrawListArray::SetParametersNumber(nparam);
		CPoint3 * pt3;
		pt3 = new CPoint3[len];
		for (int i = 0; i < len; i++)
		{
			pt3[i] = CPoint3(x[i], y[i], z[i]);
		}
		for (size_t j = 0; j < line_cutting_vector.size(); j++)
		{
			this->AddLine(
				pt3+line_cutting_vector[j].i_start, 
				line_cutting_vector[j].i_finish - line_cutting_vector[j].i_start,
				0);
		}
		delete[] pt3;
	}
	ZoomView(false);
	this->Draw();
}


void
SurfDoc::InitSurfDoc(vector<double>& x, vector<double>& y, vector<double>& z, int type)
{

	switch (type)
	{
	case 0:
		AddLine(x,y,z, 0);
		break;
	case 1:
		AddSpheres(x,y,z, 255);
		break;
	} 
 
 	ZoomView(false);
	this->Draw();
}


void
SurfDoc::InitSurfDoc(vdouble& x, vdouble& y, vdouble& z, int type)
{
 
 	if (z.GetDims() == 2)
 	{
 		vdouble visible;
 		visible.resize(y.Length(), x.Length(), 1.0);
		long id_surf = this->GetIDSurfForNewGridDataOrSurface();
		BYTE podoshva = 0;
 		AddSurf(id_surf, podoshva, 0,x,y,z, visible);
 	}
 	else
 	{
		switch (type)
		{
		case 0:
			AddLine(x,y,z, 0);
			break;
		case 1:
			AddSpheres(x,y,z, 255);
			break;
		}
 	}
 
 	ZoomView(false);
	this->Draw();
}

GeoSurface * SurfDoc::FindGeoSurface(const char * name)
{	
	GeoSurface * found  = NULL;
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( strcmp(this->m_surfaces.GetCurrentMsg().GetName().c_str(), name)  == 0)
			{
				found = &this->m_surfaces.GetCurrentMsg();
				break;
			}
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	return found;
}
GeoSurface * SurfDoc::FindGeoSurface(long id_surf)
{	
	GeoSurface * found  = NULL;
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_surfaces.GetCurrentMsg().id_surf == id_surf)
			{
				found = &this->m_surfaces.GetCurrentMsg();
				return found;
			}
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_faults.GetCurrentMsg().id_surf == id_surf)
			{
				found = &this->m_faults.GetCurrentMsg();
				return found;
			}
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	return found;
}
GridData * SurfDoc::FindGridData(long id_surf)
{	
	GridData * found  = NULL;
	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_grid_data.GetCurrentMsg().id_surf == id_surf)
			{
				found = &this->m_grid_data.GetCurrentMsg();
				break;
			}

		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}
	return found;
}
GeoSurface * SurfDoc::FindGeoSurface(int index_surf)
{	
	GeoSurface * found  = NULL;
	int index_s = -1;
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			index_s++;
			if (index_s == index_surf)
			{
				found = &this->m_surfaces.GetCurrentMsg();
				break;
			}

		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	return found;
}
Cube4D * SurfDoc::FindCube(int index_cub)
{	
	Cube4D * cube = NULL;
	int index_c = -1;
	if (m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			index_c++;
			if (index_c == index_cub)
			{
				cube = &m_cubes.GetCurrentMsg();
				break;
			}
		}
		while (m_cubes.IncrementCurrentMsg());
	}
	return cube;
}
void SurfDoc::LoadSurfEngGeoElementMappingFile()
{
	if (OpenFileDlg(this->hSurfWnd, "Surf Key mapping files (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
	{
		vector<vector<cell> > * pdata = new vector<vector<cell> >;
		vector<string> * pnames_of_colomns = new vector<string>;
		char* filename = new char[256];

		int delim = '\t';

		if (1 == ReadCellFile(this->hSurfWnd, szPath, filename, pdata, pnames_of_colomns, delim ))
		{
			if (pnames_of_colomns->size() >= 2)
			{			
				surf_eng_geo_element_mapping.clear();

				char str0[512];
				char str1[512];	
				for (size_t n = 0; n < pdata->size(); n++)
				{
					strcpy(str0,pdata->operator [](n).operator [](0).str.c_str());
					strcpy(str1,pdata->operator [](n).operator [](1).str.c_str());
					// deleting ""
					char * p0 = str0;
					char * p1 = str1;
					while ( (*p0) == '"') p0++;
					while ( (*p1) == '"') p1++;
					while (p0[strlen(p0)-1] == '"') p0[strlen(p0)-1] = '\0';
					while (p1[strlen(p1)-1] == '"') p1[strlen(p1)-1] = '\0';
					long id_surf = -1;
					GeoSurface * surf = this->FindGeoSurface(p0);
					if (surf)
					{
						id_surf = surf->id_surf;
					}
					BYTE podoshva = 1;
					surf_eng_geo_element_mapping.insert(surf_eng_geo_element_mapping.begin(),key_grid(id_surf, podoshva, p0, p1));
				}
				for (size_t k1 = 0; k1 < surf_eng_geo_element_mapping.size(); k1++)
				{
					printf("surf = \"%s\"\tkey = \"%s\"\n", surf_eng_geo_element_mapping[k1].surfname.c_str(), surf_eng_geo_element_mapping[k1].key.c_str());
				}
				/*                "pod surf" "key"
				kgs.push_back(key_grid("7", "7"));
				kgs.push_back(key_grid("6", "6"));
				kgs.push_back(key_grid("5", "5"));
				kgs.push_back(key_grid("3", "3"));
				kgs.push_back(key_grid("4", "4"));
				kgs.push_back(key_grid("3'","3"));
				kgs.push_back(key_grid("0", "0")); //relief
				*/
			}
		}
	}
}
/*void SurfDoc::PrintSurfEngGeoElementMapping()
{
	printf("SurfDoc::PrintSurfGeoElementMapping()\n");
	for (size_t k1 = 0; k1 < surf_eng_geo_element_mapping.size(); k1++)
	{
		printf("surf = \"%s\"\tkey = \"%s\"\n", surf_eng_geo_element_mapping[k1].surfname.c_str(), surf_eng_geo_element_mapping[k1].key.c_str());
	}
}*/
bool SurfDoc::GetIGEkey(string podoshva_surfname, string & out_key)
{
	if(!this->surf_eng_geo_element_mapping.size())
	{
		printf("SurfDoc::GetIGEkey(string podoshva_surfname = %s, string & out_key);\n", podoshva_surfname.c_str());
		printf("warning: this->surf_eng_geo_element_mapping.size() == 0\n");
	}
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::engineer_geological);
	if (colomn) 
	{
		for (size_t k = 0; k < this->surf_eng_geo_element_mapping.size(); k++)
		{
			if (0 == strcmp(podoshva_surfname.c_str(), this->surf_eng_geo_element_mapping[k].surfname.c_str()))
			{
				out_key = this->surf_eng_geo_element_mapping[k].key;
				return true;
			}
		}
	}
	printf("SurfDoc::GetIGEkey(string podoshva_surfname = %s, out_key not found!!!)\n", podoshva_surfname.c_str());
	if (set_well_elements_ige_keys_show_error_message_box)
	{
		set_well_elements_ige_keys_show_error_message_box = false;


		printf("surf_eng_geo_element_mapping list:\n");
		for (size_t k = 0; k < this->surf_eng_geo_element_mapping.size(); k++)
		{
			printf("%d surfname = %s key = %s\n", k,
				this->surf_eng_geo_element_mapping[k].surfname.c_str(),
				this->surf_eng_geo_element_mapping[k].key.c_str());
		}



		char str[4096];
		sprintf(str, 
			"SurfDoc::GetIGEkey(string podoshva_surfname = %s, out_key not found\n"
			"this->surf_eng_geo_element_mapping.size() = %u", 
			podoshva_surfname.c_str(),
			this->surf_eng_geo_element_mapping.size()
			);
		MessageBox(this->hSurfWnd, str, "GetIGEkey", MB_OK | MB_ICONEXCLAMATION);
	}
	return false;
}
EngineerGeoElement * SurfDoc::FindEngineerGeoElement(string key)
{
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::engineer_geological);
	if (colomn) 
	{
		GeoElement * elem = colomn->FindGeoElement(key);
		EngineerGeoElement * eng = dynamic_cast<EngineerGeoElement *>(elem);
		return eng;
	}
	return NULL;
}
void SurfDoc::SetColorFromIGE()
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().SetColorFromIGE();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::SetWellElementsIGEkeys()
{
	if (need_to_set_wel_element_ige_keys)
	{
		if (this->m_drills.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_drills.GetCurrentMsg().SetWellElementsIGEkeys();
			}
			while(this->m_drills.IncrementCurrentMsg());
		}
	}
}

void SurfDoc::LoadSurfLithoGeoElementMappingFile()
{
	if (OpenFileDlg(this->hSurfWnd, "Surf Key mapping files (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
	{
		vector<vector<cell> > * pdata = new vector<vector<cell> >;
		vector<string> * pnames_of_colomns = new vector<string>;
		char* filename = new char[256];

		int delim = '\t';

		if (1 == ReadCellFile(this->hSurfWnd, szPath, filename, pdata, pnames_of_colomns, delim ))
		{
			if (pnames_of_colomns->size() >= 2)
			{			
				surf_litho_geo_element_mapping.clear();

				char str0[512];
				char str1[512];	
				for (size_t n = 0; n < pdata->size(); n++)
				{
					strcpy(str0,pdata->operator [](n).operator [](0).str.c_str());
					strcpy(str1,pdata->operator [](n).operator [](1).str.c_str());
					// deleting ""
					char * p0 = str0;
					char * p1 = str1;
					while ( (*p0) == '"') p0++;
					while ( (*p1) == '"') p1++;
					while (p0[strlen(p0)-1] == '"') p0[strlen(p0)-1] = '\0';
					while (p1[strlen(p1)-1] == '"') p1[strlen(p1)-1] = '\0';
					long id_surf = -1;
					GeoSurface * surf = this->FindGeoSurface(p0);
					if (surf)
					{
						id_surf = surf->id_surf;
					}
					BYTE podoshva = 1;
					surf_litho_geo_element_mapping.insert(surf_litho_geo_element_mapping.begin(),key_grid(id_surf, podoshva, p0,p1));
				}
				for (size_t k1 = 0; k1 < surf_litho_geo_element_mapping.size(); k1++)
				{
					printf("surf = \"%s\"\tkey = \"%s\"\n", surf_litho_geo_element_mapping[k1].surfname.c_str(), surf_litho_geo_element_mapping[k1].key.c_str());
				}
				/*                "pod surf" "key"
				kgs.push_back(key_grid("7", "7"));
				kgs.push_back(key_grid("6", "6"));
				kgs.push_back(key_grid("5", "5"));
				kgs.push_back(key_grid("3", "3"));
				kgs.push_back(key_grid("4", "4"));
				kgs.push_back(key_grid("3'","3"));
				kgs.push_back(key_grid("0", "0")); //relief
				*/
			}
		}					  
	}
}
/*void SurfDoc::PrintSurfLithoGeoElementMapping()
{
	printf("SurfDoc::PrintSurfLithoGeoElementMapping()\n");
	for (size_t k1 = 0; k1 < surf_litho_geo_element_mapping.size(); k1++)
	{
		printf("surf = \"%s\"\tkey = \"%s\"\n", surf_litho_geo_element_mapping[k1].surfname.c_str(), surf_litho_geo_element_mapping[k1].key.c_str());
	}
}*/
bool SurfDoc::GetLithoKey(string podoshva_surfname, string & out_key)
{
	if(!this->surf_litho_geo_element_mapping.size())
	{
		printf("SurfDoc::GetLithoKey(string podoshva_surfname = %s, string & out_key);\n", podoshva_surfname.c_str());
		printf("warning: this->surf_litho_geo_element_mapping.size() == 0\n");
	}
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::lithological);
	if (colomn) 
	{
		for (size_t k = 0; k < this->surf_litho_geo_element_mapping.size(); k++)
		{
			if (0 == strcmp(podoshva_surfname.c_str(), this->surf_litho_geo_element_mapping[k].surfname.c_str()))
			{
				out_key = this->surf_litho_geo_element_mapping[k].key;
				return true;
			}
		}
	}
	printf("SurfDoc::GetLithoKey(string podoshva_surfname = %s, out_key not found!!!)\n", podoshva_surfname.c_str());
	if (set_well_elements_litho_keys_show_error_message_box)
	{
		set_well_elements_litho_keys_show_error_message_box = false;
		char str[4096];
		sprintf(str, 
			"SurfDoc::GetLithoKey(string podoshva_surfname = %s, out_key not found\n"
			"this->surf_litho_geo_element_mapping.size() = %u", 
			podoshva_surfname.c_str(),
			this->surf_litho_geo_element_mapping.size()
			);
		MessageBox(this->hSurfWnd, str, "GetLithoKey", MB_OK | MB_ICONEXCLAMATION);
	}
	return false;
}
LithoGeoElement * SurfDoc::FindLithoGeoElement(string key)
{
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::lithological);
	if (colomn) 
	{
		GeoElement * elem = colomn->FindGeoElement(key);
		LithoGeoElement * lith = dynamic_cast<LithoGeoElement *>(elem);
		return lith;
	}
	return NULL;
}
int SurfDoc::LithoPodoshvaHowMany(string geo_element_key)
{
	int n_max = 0;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			int n = this->m_drills.GetCurrentMsg().LithoPodoshvaHowMany(geo_element_key);
			if (n_max < n)
			{
				n_max = n;
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	return n_max;
}
void SurfDoc::UstjaToReliefGriddata()
{
	COLORREF color = RGB(0,0,0);

	GridData * pGridData = this->CreateNewGridData();
	long id_surf = pGridData->id_surf;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().UstjaToReliefGriddata(pGridData, color);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	pGridData->SetColor(color);
	pGridData->id_umpoz = -1;

	char sname [32];
	sprintf(sname, "Рельеф");

	pGridData->SetName(sname);

	BYTE podoshva = 0;
	string ige_key = "0";

	this->AddSurfIgeMappingItem(id_surf, podoshva, sname, ige_key.c_str());
	this->AddSurfIgeMappingItemToDB(id_surf, ige_key.c_str());

	pGridData->GrDtSaveToDB(0);

	this->Zoom<GridData>(this->m_grid_data);
	ReDrawGridData(this);
	this->UpdateAllViews();
}

void SurfDoc::LithoPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().LithoPodoshvaToGridData(isurf, podoshva, geo_element_key, pData, reverse);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
int SurfDoc::IGEPodoshvaHowMany(string geo_element_key)
{
	int n_max = 0;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			int n = this->m_drills.GetCurrentMsg().IGEPodoshvaHowMany(geo_element_key);
			if (n_max < n)
			{
				n_max = n;
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	return n_max;
}
void SurfDoc::IGEZabojToGridData(string geo_element_key, GridData * pData)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().IGEZabojToGridData(geo_element_key, pData);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}

void SurfDoc::IGEPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().IGEPodoshvaToGridData(isurf, podoshva, geo_element_key, pData, reverse);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::HydroProjavlenieHowMany(map<long, long> &gorizonts, bool ust)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().HydroProjavlenieHowMany(gorizonts, ust);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::HydroProjavlenieToGridData(long horizont, bool ust, GridData * pData)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().HydroProjavlenieToGridData(horizont, ust, pData);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::SetColorFromLitho()
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().SetColorFromLitho();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::SetWellElementsLithoKeys()
{
	if (need_to_set_wel_element_litho_keys)
	{
		if (this->m_drills.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_drills.GetCurrentMsg().SetWellElementsLithoKeys();
			}
			while(this->m_drills.IncrementCurrentMsg());
		}
	}
}

/*void SurfDoc::GeoSurfaces_BlankAbove_By_SurfEngGeoElementMapping()
{
	for (size_t k1 = 0; k1 < surf_eng_geo_element_mapping.size(); k1++)
	{
		GeoSurface * surf1 = this->FindGeoSurface(surf_eng_geo_element_mapping[k1].surfname.c_str());
		if (surf1)
		{
			for (size_t k2 = k1+1; k2 < surf_eng_geo_element_mapping.size(); k2++)
			{
				GeoSurface * surf2 = this->FindGeoSurface(surf_eng_geo_element_mapping[k2].surfname.c_str());
				if (surf2)
				{
					if (!surf1->BlankAbove(*surf2))
					{
						char str[1024];
						sprintf(str, "if (!surf1(\"%s\")->BlankAbove(*surf2(\"%s\")))", surf1->GetName().c_str(), surf2->GetName().c_str());
						MessageBox(0,str,"AddGeoCube",0);
					}
				}
			}
		}
	}
}*/
void SurfDoc::FillGrids_On_SurfEngGeoElementMapping()
{
#if 1
	for (vector<surface_order_list_item *>::reverse_iterator 
		rit = GeoSurface::surface_order_list.rbegin();
		rit != GeoSurface::surface_order_list.rend(); rit++)
	{
		if( (*rit) && (*rit)->check)
		{
			(*rit)->grid = NULL;
			GeoSurface * surf = this->FindGeoSurface((*rit)->id_surf);
			if (!surf)
			{
				surf = this->FindGeoSurface((*rit)->my_name.c_str());
			}
			if (surf)
			{
				Grid * pgrid = new Grid;
				if (pgrid)
				{
					if (surf->m_surface.MakeGridSection(&pgrid->gridSection)
						&& surf->MakeFaultSection(&pgrid->faultSection))
					{
						(*rit)->grid = pgrid;
					}
				}
			}
		}
	}
#else
	for (size_t k = 0; k < surf_eng_geo_element_mapping.size(); k++)
	{
		surf_eng_geo_element_mapping[k].grid = NULL;
		GeoSurface * surf = this->FindGeoSurface(surf_eng_geo_element_mapping[k].surfname.c_str());
		if (surf)
		{
			Grid * pgrid = new Grid;
			if (pgrid)
			{
				if (surf->m_surface.MakeGridSection(&pgrid->gridSection)
					&& surf->MakeFaultSection(&pgrid->faultSection))
				{
					surf_eng_geo_element_mapping[k].grid = pgrid;
				}
			}
		}
	}
#endif
}
void SurfDoc::FreeGrids_On_SurfEngGeoElementMapping()
{
#if 1
	for (vector<surface_order_list_item *>::reverse_iterator 
		rit = GeoSurface::surface_order_list.rbegin();
		rit != GeoSurface::surface_order_list.rend(); rit++)
	{
		if( (*rit) && (*rit)->check)
		{
			FreeGrid((*rit)->grid);
		}
	}
#else
	for (size_t k = 0; k < surf_eng_geo_element_mapping.size(); k++)
	{
		FreeGrid(surf_eng_geo_element_mapping[k].grid);
	}
#endif
}
Cube4D * SurfDoc::AddGeoCube(bool full_geo_cube_filling, 
							 LabTrialValueType & vt, LabNormatives::type lab_normatives_type)
{	
//	GeoSurfaces_BlankAbove_By_SurfEngGeoElementMapping();
	FillGrids_On_SurfEngGeoElementMapping();
	Cube4D * cube = this->AddingGeoCube(full_geo_cube_filling, surf_eng_geo_element_mapping, vt, lab_normatives_type);
	if (!cube)
	{
		MessageBox(0,"!this->AddingGeoCube","AddGeoCube",0);
	}
	FreeGrids_On_SurfEngGeoElementMapping();
	return cube;
}
Cube4D * SurfDoc::AddGeoCube(bool full_geo_cube_filling, 
							 EngineerGeoElement::ValueType value_type, 
							 EngineerGeoElement::GroundDescriptionType ground_description_type,
							 EngineerGeoElement::StrengthDescriptionType strength_description_type)
{	
// 	старая версия не работает с базой
//	GeoSurfaces_BlankAbove_By_SurfEngGeoElementMapping();
	FillGrids_On_SurfEngGeoElementMapping();
	Cube4D * cube = this->AddingGeoCube(full_geo_cube_filling, surf_eng_geo_element_mapping, value_type, ground_description_type, strength_description_type);
	if (!cube)
	{
		MessageBox(0,"!this->AddingGeoCube","AddGeoCube",0);
	}
	FreeGrids_On_SurfEngGeoElementMapping();
	return cube;
}

string FindIGEKey(long id_surf, vector<key_grid> & kgs)
{
	for (size_t k = 0; k < kgs.size(); k++)
	{
		if(id_surf == kgs[k].id_surf)
			return kgs[k].key;
	}
	return "";
}

Cube4D * SurfDoc::AddingGeoCube(bool full_geo_cube_filling, 
								vector<key_grid> & kgs, 
								EngineerGeoElement::ValueType value_type, 	
								EngineerGeoElement::GroundDescriptionType ground_description_type,
								EngineerGeoElement::StrengthDescriptionType strength_description_type)
{
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::engineer_geological);

#if 1
	for (vector<surface_order_list_item *>::reverse_iterator 
		rit = GeoSurface::surface_order_list.rbegin();
		rit != GeoSurface::surface_order_list.rend(); rit++)
	{
		if( (*rit) && (*rit)->check)
		{
			string ige_key = FindIGEKey((*rit)->id_surf, kgs);
			GeoElement * element = NULL;                    
			if (colomn)
			{
				element = colomn->FindGeoElement(ige_key);
			}
			EngineerGeoElement * eng = NULL;
			if(element)
				eng = dynamic_cast<EngineerGeoElement *>(element);

			if (eng)
			{
				eng->ToPrintIfAny();
			}
		}
	}
#else
	for (size_t k = 0; k < kgs.size(); k++)
	{
		GeoElement * element = NULL;                    
		if (colomn)
		{
			element = colomn->FindGeoElement(kgs[k].key);
		}
		EngineerGeoElement * eng = NULL;
		if(element)
			eng = dynamic_cast<EngineerGeoElement *>(element);

		if (eng)
		{
			eng->ToPrintIfAny();
		}
	}
#endif
	if (this->m_cube_size.Defined())
	{
		Grid4 grid4;
		if(!grid4.grid4Section.InitSize(this->m_cube_size)) return NULL;
		grid4.grid4Section.v = Alloc3DMat<double>(grid4.grid4Section.nPag, grid4.grid4Section.nRow, grid4.grid4Section.nCol);
		
		for (long c = 0; c < grid4.grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid4.grid4Section.nRow; r++)
			{	
				for (long p = 0; p < grid4.grid4Section.nPag; p++)                    
				{					
					grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
				}
			}
		}
		for (long c = 0; c < grid4.grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid4.grid4Section.nRow; r++)
			{
				vector <key_z> vkeyz;
#if 1
				for (vector<surface_order_list_item *>::reverse_iterator 
					rit = GeoSurface::surface_order_list.rbegin();
					rit != GeoSurface::surface_order_list.rend(); rit++)
				{
					if( (*rit) && (*rit)->check)
					{
						string ige_key = FindIGEKey((*rit)->id_surf, kgs);
						if ((*rit)->grid && (*rit)->grid->gridSection.z[r][c] != BLANK_VALUE)
							vkeyz.push_back(key_z(ige_key, (*rit)->grid->gridSection.z[r][c]));
					}
				}
#else
				for (size_t k = 0; k < kgs.size(); k++)
				{
					if (kgs[k].grid && kgs[k].grid->gridSection.z[r][c] != BLANK_VALUE)
						vkeyz.push_back(key_z(kgs[k].key, kgs[k].grid->gridSection.z[r][c]));
				}
#endif
				for (size_t k1 = 0, k2 = 1; k2 < vkeyz.size(); k1++, k2++)
				{
					GeoElement * element = NULL;                    
					if (colomn)
					{
						element = colomn->FindGeoElement(vkeyz[k1].key);
					}
					EngineerGeoElement * eng = NULL;
					if(element)
						eng = dynamic_cast<EngineerGeoElement *>(element);

					double z1 = vkeyz[k1].z;
					double z2 = vkeyz[k2].z;

					if (z1 > z2)
					{
						char str[1024];
						sprintf(str, "(z1 %f (\"%s\") > z2 %f (\"%s\") [%d %d]", 
							z1, vkeyz[k1].key.c_str(), 
							z2, vkeyz[k2].key.c_str(),
							r,c);
						MessageBox(0, str, "AddGeoCube", MB_OK);
						//return false;
					}

					long p1 =  long(ceil ((z1 - grid4.grid4Section.zLL) / grid4.grid4Section.zSize));
					long p2 =  long(floor((z2 - grid4.grid4Section.zLL) / grid4.grid4Section.zSize));
					
					for (long p = p1; p <= p2; p++)                    
					{				
						if (p >= 0 && p < grid4.grid4Section.nPag)
						{
							if (eng)
							{
								if (eng->GetGround())
								{
									if (!(eng && eng->GetValue(value_type, ground_description_type, strength_description_type, grid4.grid4Section.v[p][r][c])))
									{
										if ( full_geo_cube_filling )
										{			
											char str[1024];
											sprintf(str, "EngGeoElem \"%s\"\nCan not get value of type \"%d\"", vkeyz[k1].key.c_str(), value_type);
											MessageBox(0, str, "AddGeoCube", MB_OK);
											return NULL;
										}
									}
								}
								else
								{
									//eng->

								}
							}
						}
					}
				}	
			}
		}

		char name[1024];
		sprintf(name, "%s_%s_%s", 
			EngineerGeoElement::ValueTypeToString(value_type),
			EngineerGeoElement::GroundDescriptionTypeToString(ground_description_type),
			EngineerGeoElement::ValueTypeIsStrength(value_type) ? 
			EngineerGeoElement::StrengthDescriptionTypeToString(strength_description_type) : "");

		
		Cube4D * cube = this->AddCube(&grid4, name, 0);
		if (cube)
		{
			cube->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
			cube->Draw();
			cube->AddItem_ToTree(this->hwndTV, m_cubes_ObjectList.myTreeItem);
		}
		return cube;
	}
	return NULL;
}

Cube4D * SurfDoc::AddingGeoCube(bool full_geo_cube_filling, 
								vector<key_grid> & kgs, 
								LabTrialValueType & vt, LabNormatives::type lab_normatives_type)
{
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::engineer_geological);

#if 1
	for (vector<surface_order_list_item *>::reverse_iterator 
		rit = GeoSurface::surface_order_list.rbegin();
		rit != GeoSurface::surface_order_list.rend(); rit++)
	{
		if( (*rit) && (*rit)->check)
		{
			string ige_key = FindIGEKey((*rit)->id_surf, kgs);
			GeoElement * element = NULL;                    
			if (colomn)
			{
				element = colomn->FindGeoElement(ige_key);
			}
			EngineerGeoElement * eng = NULL;
			if(element)
				eng = dynamic_cast<EngineerGeoElement *>(element);

			if (eng)
			{
				eng->ToPrintIfAny();
			}
		}
	}
#else
	for (size_t k = 0; k < kgs.size(); k++)
	{
		GeoElement * element = NULL;                    
		if (colomn)
		{
			element = colomn->FindGeoElement(kgs[k].key);
		}
		EngineerGeoElement * eng = NULL;
		if(element)
			eng = dynamic_cast<EngineerGeoElement *>(element);

		if (eng)
		{
			eng->ToPrintIfAny();
		}
	}
#endif
	if (this->m_cube_size.Defined())
	{
		Grid4 grid4;
		if(!grid4.grid4Section.InitSize(this->m_cube_size)) return NULL;
		grid4.grid4Section.v = Alloc3DMat<double>(grid4.grid4Section.nPag, grid4.grid4Section.nRow, grid4.grid4Section.nCol);
		
		for (long c = 0; c < grid4.grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid4.grid4Section.nRow; r++)
			{	
				for (long p = 0; p < grid4.grid4Section.nPag; p++)                    
				{					
					grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
				}
			}
		}
		for (long c = 0; c < grid4.grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid4.grid4Section.nRow; r++)
			{
				vector <key_z> vkeyz;
#if 1
				for (vector<surface_order_list_item *>::reverse_iterator 
					rit = GeoSurface::surface_order_list.rbegin();
					rit != GeoSurface::surface_order_list.rend(); rit++)
				{
					if( (*rit) && (*rit)->check)
					{
						string ige_key = FindIGEKey((*rit)->id_surf, kgs);
						if ((*rit)->grid && (*rit)->grid->gridSection.z[r][c] != BLANK_VALUE)
							vkeyz.push_back(key_z(ige_key, (*rit)->grid->gridSection.z[r][c]));
					}
				}
#else
				for (size_t k = 0; k < kgs.size(); k++)
				{
					if (kgs[k].grid && kgs[k].grid->gridSection.z[r][c] != BLANK_VALUE)
						vkeyz.push_back(key_z(kgs[k].key, kgs[k].grid->gridSection.z[r][c]));
				}
#endif
				for (size_t k1 = 0, k2 = 1; k2 < vkeyz.size(); k1++, k2++)
				{
					GeoElement * element = NULL;                    
					if (colomn)
					{
						element = colomn->FindGeoElement(vkeyz[k1].key);
					}
					EngineerGeoElement * eng = NULL;
					if(element)
						eng = dynamic_cast<EngineerGeoElement *>(element);

					double z1 = vkeyz[k1].z;
					double z2 = vkeyz[k2].z;

					if (z1 > z2)
					{
						char str[1024];
						sprintf(str, "(z1 %f (\"%s\") > z2 %f (\"%s\") [%d %d]", 
							z1, vkeyz[k1].key.c_str(), 
							z2, vkeyz[k2].key.c_str(),
							r,c);
						MessageBox(0, str, "AddGeoCube", MB_OK);
						//return false;
					}

					long p1 =  long(ceil ((z1 - grid4.grid4Section.zLL) / grid4.grid4Section.zSize));
					long p2 =  long(floor((z2 - grid4.grid4Section.zLL) / grid4.grid4Section.zSize));
					
					for (long p = p1; p <= p2; p++)                    
					{				
						if (p >= 0 && p < grid4.grid4Section.nPag)
						{
							if (!(eng && eng->GetValue(vt, lab_normatives_type, grid4.grid4Section.v[p][r][c])))
							{
								if ( full_geo_cube_filling )
								{			
									char str[1024];
									sprintf(str, "EngGeoElem \"%s\"\nCan not get value of type \"%s\"", vkeyz[k1].key.c_str(), vt.GetValueTypeString());
									MessageBox(0, str, "AddGeoCube", MB_OK);
									return NULL;
								}
							}
						}
					}
				}	
			}
		}

		char name[1024];
		sprintf(name, "%s %s", vt.GetValueTypeString(), LabNormatives::TypeToString(lab_normatives_type));

		
		Cube4D * cube = this->AddCube(&grid4, name, 0);
		if (cube)
		{
			cube->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
			cube->Draw();
			cube->AddItem_ToTree(this->hwndTV, m_cubes_ObjectList.myTreeItem);
		}
		return cube;
	}
	return NULL;
}

GeoColomn * SurfDoc::FindGeoColomn(GeoElement::type t)
{
	if (this->m_geo_colomns.find(t) != this->m_geo_colomns.end())
		return &m_geo_colomns[t];

	return NULL;
}

GeoColomn * SurfDoc::AddGeoColomn(GeoElement::type t)
{
	if (this->m_geo_colomns.find(t) != this->m_geo_colomns.end())
		return &m_geo_colomns[t];

	return this->AddNewGeoColomn(t);
}

GeoColomn * SurfDoc::AddNewGeoColomn(GeoElement::type t)
{
	this->m_geo_colomns.insert(map<GeoElement::type, GeoColomn>::value_type(t,GeoColomn(t, this)));
	this->m_geo_colomns_ObjectList.Init_std_map(this->m_geo_colomns, this);
	return &m_geo_colomns[t];
}
void SurfDoc::FillLayerList()
{
	m_LayersListViewTab.clear();

	m_LayersListViewTab.AddRow(LPARAM(0), &m_defaut_layer.bChecked);
#if USE_LISTVIEW_STANDART_LL 
	m_LayersListViewTab.SetItemString(0,0,m_defaut_layer.GetName());
#else
	m_LayersListViewTab.SetItemString(0,0,"");
	m_LayersListViewTab.SetItemString(0,1,m_defaut_layer.GetName());
#endif

	size_t r = 1;
	for (map<int, Layer>::iterator i_layer = m_layers.begin(); i_layer != m_layers.end(); i_layer++, r++)
	{
		m_LayersListViewTab.AddRow(LPARAM(0), &i_layer->second.bChecked);
#if USE_LISTVIEW_STANDART_LL 
		m_LayersListViewTab.SetItemString(r,0,i_layer->second.GetName());
#else
		m_LayersListViewTab.SetItemString(r,0,"");
		m_LayersListViewTab.SetItemString(r,1,i_layer->second.GetName());
#endif
	}
}
void SurfDoc::UpdateLayersNames()
{
printf("SurfDoc::UpdateLayersNames()\n");
#if USE_LISTVIEW_STANDART_LL 
	m_defaut_layer.SetName(m_LayersListViewTab.GetItemString(0,0));
#else
	m_defaut_layer.SetName(m_LayersListViewTab.GetItemString(0,1));
#endif

	size_t r = 1;
	for (map<int, Layer>::iterator i_layer = m_layers.begin(); i_layer != m_layers.end(); i_layer++, r++)
	{
#if USE_LISTVIEW_STANDART_LL 
		i_layer->second.SetName(m_LayersListViewTab.GetItemString(r,0));
#else
		i_layer->second.SetName(m_LayersListViewTab.GetItemString(r,1));
#endif
	}
}


int SurfDoc::GetIDForNewLayer()
{
	int id, maxid = -1;
	bool start = true;
	for (map<int,Layer>::iterator it = this->m_layers.begin(); it != this->m_layers.end(); it++)
	{
		id = it->first;
		if (start)
		{
			maxid = id;
			start = false;
		}
		else
		{
			if (maxid < id) maxid = id;
		}
	}
	id = maxid + 1;
	return id;
}
Layer* SurfDoc::FindLayer(char * name)
{
	Layer * found = NULL;
	for (map<int, Layer>::iterator i_layer = m_layers.begin(); i_layer != m_layers.end(); i_layer++)
	{
		if (strcmp(i_layer->second.GetName().c_str(), name) == 0)
		{
			found = &i_layer->second;
			return found;
		}
	}
	return found;
}
	

Layer* SurfDoc::AddNewLayer(char * name)
{
	char str[255];

	int id = this->GetIDForNewLayer();

	if (name)
		sprintf(str, "%s", name);
	else
		sprintf(str, "Layer %d", id);

	m_layers.insert(map<int,Layer>::value_type(id, Layer(id, str)));

	m_LayersListViewTab.AddRow(LPARAM(0), NULL);
	size_t r = m_LayersListViewTab.Rows()-1;
	sprintf(str, "%d", id);
#if USE_LISTVIEW_STANDART_LL 
	m_LayersListViewTab.SetItemString(r,0,m_layers[id].GetName());
#else
	m_LayersListViewTab.SetItemString(r,0,str);
	m_LayersListViewTab.SetItemString(r,1,m_layers[id].GetName());
#endif

	return &m_layers[id];
}
Layer* SurfDoc::GetLayerPtr(int id)
{
	if (id < 0)
	{
		return &this->m_defaut_layer;
	}
	else
	{
		if (this->m_layers.find(id) != this->m_layers.end())
			return &this->m_layers[id];
	}
	return NULL;
}
void Find_LayerPtr(Object * pOb, WPARAM, LPARAM, void * p)
{
	if (pOb)
	{
		SurfDoc * doc = reinterpret_cast<SurfDoc *>(p);
		if (doc)
		{
			int id = pOb->GetLayerID();
			pOb->SetLayer_NonVirtual(doc->GetLayerPtr(id));
		}
	}
}
void SurfDoc::InitObjectsLayerPointers()
{
printf("SurfDoc::InitObjectsLayerPointers()\n");
	this->EnumObjects(0, 0, (void*) this, 
		&Object::ReturnTrue,
		Find_LayerPtr);
}
void SurfDoc::SetSelectedLayer(Layer* layer)
{
	m_selected_layer = layer;
#pragma warning( disable : 4313 )
	printf("SurfDoc::SetSelectedLayer this->m_selected_layer = 0x%08x\n", this->m_selected_layer);
#pragma warning( default : 4313 )
}

void SurfDoc::OnCreate(bool to_init_palette_on_create)
{
	need_to_set_wel_element_litho_keys = true;
	need_to_set_wel_element_ige_keys = true;

	m_pLabDoc = NULL;
	id_obj = -1;

	this->m_object_type = Object::object_type::surf_doc;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	m_wdli_primitive = this->AddWellsDraw(WellElement::type::primitive_ref, true, 40.f, true, wells_draw_list_item::draw_mode_2d::both);
	m_wdli_laboratory = NULL;

	m_selected_layer	= NULL;
	m_pLineForDraw		= NULL;
	m_pGridDataForDraw	= NULL;

	m_Spheres_max_z = -DBL_MAX;
	m_Spheres_min_z = DBL_MAX;

	if(to_init_palette_on_create)
		DrawListArray::OnCreate(this);

	m_zoomCoefXY = 1.0;
	m_zoomCoefXYZ = 1.0;

	m_alpha = 255;
	m_alpha_plane = 50;
	m_alpha_gdiplus_profiles = 50;

	m_sphere_radius = 0.02;
	m_sphere_slices = 4; //The number of subdivisions around the z-axis (similar to lines of longitude). 
	m_sphere_stacks = 4; //The number of subdivisions along the z-axis (similar to lines of latitude). 

	m_cut_plane_d[0] = 1.0;
	m_cut_plane_d[1] = 1.0;
	m_cut_plane_d[2] = 0.0;
	m_cut_plane_d[3] = 0.0;

	m_cut_plane_v[0] = 1.0;
	m_cut_plane_v[1] = 1.0;
	m_cut_plane_v[2] = 0.0;
	m_cut_plane_v[3] = 0.0;

	this->m_bFastCutting = true;

	this->m_objects.OnCreate();
	this->m_collections.OnCreate();
	{
		m_geo_colomns_ObjectList.SetName("Geo Colomns");
#if DFX_LAYER_FROM_OBJECT
		m_dxfConverters_ObjectList.SetName("dxfConverters");
#endif
		m_objects_ObjectList.SetName("objects");
		m_collections_ObjectList.SetName("collections");
		m_auto_build_profiles_ObjectList.SetName("auto_build_profiles");
		m_cubes_ObjectList.SetName("cubes");
		m_grid_data_ObjectList.SetName("grid_data");
		m_geo_catches_ObjectList.SetName("geo_catches");
		m_surfaces_ObjectList.SetName("surfaces");
		m_faults_ObjectList.SetName("faults");
		m_drills_ObjectList.SetName("drills");
		m_lines_ObjectList.SetName("lines");
		m_cutlines_ObjectList.SetName("cutlines");
		m_blanklines_ObjectList.SetName("blanklines");
		m_strings_ObjectList.SetName("strings");
		m_polygones_ObjectList.SetName("polygones");
		m_spheres_ObjectList.SetName("spheres");
		m_points_ObjectList.SetName("points");
		m_triangles_ObjectList.SetName("triangles");
		m_bitmaps_ObjectList.SetName("bitmaps");
		m_bmp_profiles_ObjectList.SetName("bmp_profiles");
		m_brokenPlanes_ObjectList.SetName("brokenPlanes");
		m_tria_grid_ObjectList.SetName("tria_grid");
	}


	m_surfaces.OnCreate(0);
	m_faults.OnCreate(0);
	m_geo_catches.OnCreate(0);
	m_grid_data.OnCreate(0);
	m_cubes.OnCreate(0);
#if DFX_LAYER_FROM_OBJECT
	m_dxfConverters.OnCreate(0);
#endif
	m_auto_build_profiles.OnCreate(0);
	m_lines.OnCreate(0); 
	m_drills.OnCreate(0);
	m_cutlines.OnCreate(0);
	m_blanklines.OnCreate(0);
	m_strings.OnCreate(0);
	m_polygones.OnCreate(0);
	m_spheres.OnCreate(0);
	m_points.OnCreate(0);
	m_triangles.OnCreate(0);
	m_bitmaps.OnCreate(0);
	m_bmp_profiles.OnCreate(0);

//	m_vdSpherePoints.OnCreate(0);
//	m_vvSpherePoints.OnCreate(0);

//	m_vSphereColor.OnCreate(0);
	
#if BROKEN_PLANE_VECTOR_TYPE
	m_brokenPlanes.OnCreate(0);
#endif
	m_tria_grid.OnCreate(0);

	m_bln_profiles.OnCreate(0);
	m_grid_profiles.OnCreate(0);

//	m_vdTriangles.OnCreate(0);
//	m_vvTriangles.OnCreate(0);
//	m_vTrianglesColor.OnCreate(0);

//	m_vvPoligonPoints.OnCreate(0);
//	m_vdPoligonPoints.OnCreate(0);
//	m_vPoligonColor.OnCreate(0);
#if 0
	vQuadCutting.OnCreate(0);

	vxyz.OnCreate(0);
#endif

	// ДВУХМЕРНЫЕ ПРОФИЛИ ПОМЕЩЁННЫЕ В ТРЁХМЕРНЫЙ КУБ
	// профиль из вертикально расположенного грида
//	m_vGridProfiles.OnCreate(0);
//	m_vvGridProfiles.OnCreate(0);
//	m_vdGridProfiles.OnCreate(0);
	// профиль из линий блн файлов
	this->m_bln_profiles.OnCreate(0);
//	m_vGridProfileMapAttaches.OnCreate(0);

//	m_vGridProfilesXSize.OnCreate(0);
//	m_vGridProfilesYSize.OnCreate(0);

//	m_vmax_grid_profile_v.OnCreate(0);
//	m_vmin_grid_profile_v.OnCreate(0);

	m_nColormap			= 0;
	m_bInverseColormap	= false;
	m_bLocalColormap	= true;
	m_bUseColormapOnSurf= false;

				
	m_bDrawStatusString = true;
	
	m_bFlatShading		= true;

	m_bEqialZoomXYZ		= false;
	m_bEqialZoomXY		= true;

	mGridProfilesDirection = GRID_POFILE_DIRECTION_NORTH;

	if (to_init_palette_on_create)
		APalette::InitPalette(&this->m_palette, this->m_nColormap);

	m_razlomThickness = 0.1;

	m_izo_step = 100;

	m_bDrawCutPlane = false;
	m_bDrawXYZCutPlanes = false;
	m_bDrawCube = false;

	m_bDrawGeoid = true;
	m_bDrawGeoid = false;

	//====== Начальный значения параметров освещения
	m_LightParam[0] = 70;	// X position
	m_LightParam[1] = 100;	// Y position
	m_LightParam[2] = 100;	// Z position
	m_LightParam[3] = 5;	// Ambient light
	m_LightParam[4] = 90;	// Diffuse light
	m_LightParam[5] = 100;	// Specular light
	m_LightParam[6] = 100;	// Ambient material
	m_LightParam[7] = 100;	// Diffuse material
	m_LightParam[8] = 60;	// Specular material *
	m_LightParam[9] = 31;	// Shininess material *
	m_LightParam[10] = 0;	// Emission material

	m_DataX.axesFlag = 0;
	m_DataY.axesFlag = 1;
	m_DataZ.axesFlag = 2;

}
SurfDoc::SurfDoc(bool to_init_palette_on_create) : m_laboratory(this, 0.1)
{
	m_pLabDoc = NULL;
//	printf("SurfDoc()\n");
	OnCreate(to_init_palette_on_create);
}

SurfDoc::~SurfDoc()
{
	m_geo_colomns.clear();
	m_geo_colomns_ObjectList.clear();



	this->m_objects.clear();
	this->m_objects_ObjectList.clear();
	this->m_collections.clear();
	this->m_collections_ObjectList.clear();

	m_surfaces.clear();
	m_surfaces_ObjectList.clear();

	m_faults.clear();
	m_faults_ObjectList.clear();

	m_geo_catches.clear();
	m_geo_catches_ObjectList.clear();

	m_grid_data.clear();
	m_grid_data_ObjectList.clear();

	m_cubes.clear();
	m_cubes_ObjectList.clear();

#if DFX_LAYER_FROM_OBJECT
	m_dxfConverters.clear();
	m_dxfConverters_ObjectList.clear();
#endif
	m_auto_build_profiles.clear();
	m_auto_build_profiles_ObjectList.clear();

	m_lines.clear(); 
	m_lines_ObjectList.clear(); 

	m_drills.clear();
	m_drills_ObjectList.clear();

	m_cutlines.clear();
	m_cutlines_ObjectList.clear();

	m_blanklines.clear();
	m_blanklines_ObjectList.clear();

	m_strings.clear();
	m_strings_ObjectList.clear();

	m_polygones.clear();
	m_polygones_ObjectList.clear();

	m_spheres.clear();
	m_spheres_ObjectList.clear();

	m_points.clear();
	m_points_ObjectList.clear();

	m_triangles.clear();
	m_triangles_ObjectList.clear();

	m_bitmaps.clear();
	m_bitmaps_ObjectList.clear();

	m_bmp_profiles.clear();	
	m_bmp_profiles_ObjectList.clear();

#if BROKEN_PLANE_VECTOR_TYPE
	m_brokenPlanes.clear();
#endif
	m_brokenPlanes_ObjectList.clear();

	m_tria_grid.clear();
	m_tria_grid_ObjectList.clear();

	m_bln_profiles.clear();
	m_bln_profiles_ObjectList.clear();

	m_grid_profiles.clear();
	m_grid_profiles_ObjectList.clear();

	this->m_bln_profiles.clear();
	this->m_bln_profiles_ObjectList.clear();

//	m_DrawListArray.glDeleteLists();
}
inline void MinMax (double d, double& Min, double& Max)
{
	//====== Корректируем переданные по ссылке параметры
	if (d > Max)
		Max = d;			// Претендент на максимум
	else if (d < Min)
		Min = d;			// Претендент на минимум
}

/////////////////////////////////////////////////////////////////////////////
// SurfDoc commands

void SurfDoc::SetLight()
{
	//====== Обе поверхности изображения участвуют
	//====== при вычислении цвета пикселов
	//====== при учете параметров освещения
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);

	//====== Позиция источника освещения
	//====== зависит от размеров объекта
#if 1
	float fPos[] =
	{
		(float)(m_xv_max+m_xv_min)/2.f + (m_LightParam[0]-50)*(float)(m_xv_max - m_xv_min)/10,
		(float)(m_yv_max+m_yv_min)/2.f + (m_LightParam[1]-50)*(float)(m_yv_max - m_yv_min)/10,
		(float)(m_zv_max+m_zv_min)/2.f + (m_LightParam[2]-50)*(float)(m_zv_max - m_zv_min)/10,
		1.f
	};
#else
	float fPos[] =
	{
		(m_LightParam[0]-50)*(float)m_fRangeX/100,
		(m_LightParam[1]-50)*(float)m_fRangeY/100,
		(m_LightParam[2]-50)*(float)m_fRangeZ/100,
		1.f
	};
#endif
//	glLightfv(GL_LIGHT0, GL_POSITION, fPos);
//printf("SetLight fPos = [%f %f %f %f]\n",fPos[0], fPos[1], fPos[2], fPos[3]);

	//====== Интенсивность окружающего освещения
	float f = m_LightParam[3]/100.f;
	float fAmbient[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbient);
//printf("SetLight fAmbient = [%f %f %f %f]\n",fAmbient[0], fAmbient[1], fAmbient[2], fAmbient[3]);

	//====== Интенсивность рассеянного света
	f = m_LightParam[4]/100.f;	
	float fDiffuse[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffuse);
//printf("SetLight fDiffuse = [%f %f %f %f]\n",fDiffuse[0], fDiffuse[1], fDiffuse[2], fDiffuse[3]);

	//====== Интенсивность отраженного света
	f = m_LightParam[5]/100.f;
	float fSpecular[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecular);

	//====== Отражающие свойства материала
	//====== для разных компонент света
	f = m_LightParam[6]/100.f;
	float fAmbMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbMat);

	f = m_LightParam[7]/100.f;
	float fDifMat[4] = { f, f, f, 1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDifMat);

	f = m_LightParam[8]/100.f;
	float fSpecMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fSpecMat);

	//====== Блесткость материала
	float fShine = 128 * m_LightParam[9]/100.f;
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShine);

	//====== Излучение света материалом
	f = m_LightParam[10]/100.f;
	float fEmission[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, fEmission);
	//LeaveCriticalSection( &theApp.cs );
}
void SurfDoc::AddSpheresAsCollection(vdouble &x, vdouble &y, vdouble &z, COLORREF color, char * name )
{
	if (x.Length() == y.Length() && y.Length() == z.Length())
	{
		this->CreateNewCollection();
		if(name) this->m_collections.GetLastMsg().SetName(name);
		int len = z.Length();

		double max_z = z.Max();
		double min_z = z.Min();
		if (m_Spheres_max_z < max_z) m_Spheres_max_z = max_z;
		if (m_Spheres_min_z > min_z) m_Spheres_min_z = min_z;
		CPoint3 pt;
		// складываем данные в документ
		for(int i = 0; i < len; i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;

			Sphere3D sphere(this);
			//m_spheres.AddMsg(&sphere);
			//m_spheres.GetLastMsg().InitPoint(pt, color);
			sphere.InitPoint(pt, color);
			this->AddObjectToLastCollection(&sphere);
		}
	}
	m_spheres_ObjectList.Init(m_spheres, this);
}

void SurfDoc::AddSpheresAsCollection(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color, char * name )
{
	if (x.size() == y.size() && y.size() == z.size())
	{
		this->CreateNewCollection();
		if(name) this->m_collections.GetLastMsg().SetName(name);
		int len = (int)z.size();

		vector<double>::iterator max_itr = max_element(z.begin(),z.end());
		vector<double>::iterator min_itr = min_element(z.begin(),z.end());

		double max_z = *max_itr;
		double min_z = *min_itr;

		if (m_Spheres_max_z < max_z) m_Spheres_max_z = max_z;
		if (m_Spheres_min_z > min_z) m_Spheres_min_z = min_z;
		CPoint3 pt;
		// складываем данные в документ
		for(int i = 0; i < len; i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;

			Sphere3D sphere(this);
			//m_spheres.AddMsg(&sphere);
			//m_spheres.GetLastMsg().InitPoint(pt, color);
			sphere.InitPoint(pt, color);
			this->AddObjectToLastCollection(&sphere);
		}
	}
	m_spheres_ObjectList.Init(m_spheres, this);
}

void SurfDoc::AddSpheres(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color )
{
	if (x.size() == y.size() && y.size() == z.size())
	{
		int len = (int)z.size();

		vector<double>::iterator max_itr = max_element(z.begin(),z.end());
		vector<double>::iterator min_itr = min_element(z.begin(),z.end());

		double max_z = *max_itr;
		double min_z = *min_itr;

		if (m_Spheres_max_z < max_z) m_Spheres_max_z = max_z;
		if (m_Spheres_min_z > min_z) m_Spheres_min_z = min_z;
		CPoint3 pt;
		// складываем данные в документ
		for(int i = 0; i < len; i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;

			Sphere3D sphere(this);
			m_spheres.AddMsg(&sphere);
			m_spheres.GetLastMsg().InitPoint(pt, color);
		}
	}
	m_spheres_ObjectList.Init(m_spheres, this);
}
void SurfDoc::AddSpheres(vdouble &x, vdouble &y, vdouble &z, COLORREF color )
{
	if (x.Length() == y.Length() && y.Length() == z.Length())
	{
		int len = z.Length();

		double max_z = z.Max();
		double min_z = z.Min();
		if (m_Spheres_max_z < max_z) m_Spheres_max_z = max_z;
		if (m_Spheres_min_z > min_z) m_Spheres_min_z = min_z;
		CPoint3 pt;
		// складываем данные в документ
		for(int i = 0; i < len; i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;

			Sphere3D sphere(this);
			m_spheres.AddMsg(&sphere);
			m_spheres.GetLastMsg().InitPoint(pt, color);
		}
	}
	m_spheres_ObjectList.Init(m_spheres, this);
}
void SurfDoc::AddSphere(double x, double y, double z, COLORREF color )
{
	Sphere3D sphere(this);
	m_spheres.AddMsg(&sphere);
	CPoint3 pt;
		pt.x = x;
		pt.y = y;
		pt.z = z;
		pt.bVisible = true;
	m_spheres.GetLastMsg().InitPoint(pt, color);
	m_spheres_ObjectList.Init(m_spheres, this);

	if (m_Spheres_max_z < z) m_Spheres_max_z = z;
	if (m_Spheres_min_z > z) m_Spheres_min_z = z;
}
void SurfDoc::AddSphere(const double *  crd, COLORREF color )
{
	Sphere3D sphere(this);
	m_spheres.AddMsg(&sphere);
	CPoint3 pt;
		pt.x = crd[0];
		pt.y = crd[1];
		pt.z = crd[2];
		pt.bVisible = true;
	m_spheres.GetLastMsg().InitPoint(pt, color);
	m_spheres_ObjectList.Init(m_spheres, this);

	if (m_Spheres_max_z < pt.z) m_Spheres_max_z = pt.z;
	if (m_Spheres_min_z > pt.z) m_Spheres_min_z = pt.z;
}
void SurfDoc::AddSphere(CPoint3 pt, COLORREF color )
{
	Sphere3D sphere(this);
	m_spheres.AddMsg(&sphere);

	pt.bVisible = true;

	m_spheres.GetLastMsg().InitPoint(pt, color);
	m_spheres_ObjectList.Init(m_spheres, this);

	double z = pt.z;
	if (m_Spheres_max_z < z) m_Spheres_max_z = z;
	if (m_Spheres_min_z > z) m_Spheres_min_z = z;
}
void SurfDoc::AddBitmap()
{
	Bmp3D bitmap(this);
	m_bitmaps.AddMsg(&bitmap);


	m_bitmaps.GetLastMsg().LoadGLTexture();
	m_bitmaps_ObjectList.Init(m_bitmaps, this);
}

void SurfDoc::AddPoint(CPoint3 pt, COLORREF color )
{
	ThePoint3D point(this);
	m_points.AddMsg(&point);

	pt.bVisible = true;

	m_points.GetLastMsg().InitPoint(pt, color);
	m_points_ObjectList.Init(m_points, this);
}
void SurfDoc::AddPoints(CPoint3* pts, int len, COLORREF color )
{
	for(int i = 0; i < len; i++)
	{
		ThePoint3D point(this);
		m_points.AddMsg(&point);
		m_points.GetLastMsg().InitPoint(pts[i], color);
	}
	m_points_ObjectList.Init(m_points, this);
}

void SurfDoc::AddCutLine(vdouble &x, vdouble &y, vdouble &z, COLORREF color )
{
	Line3D line(this);
	m_cutlines.AddMsg(&line);
	m_cutlines.GetLastMsg().Init(x,y,z,color);	
	m_cutlines_ObjectList.Init(m_cutlines, this);
}

void SurfDoc::AddBlankLine(int inside)
{
	Line3D line(this);

	if (inside == 0)
		// заливка внутри - включаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam |= OBJECT_FLAG_INSIDE_BLANK_BIT;
	else
		// заливка снаружи - выключаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam &= ~OBJECT_FLAG_INSIDE_BLANK_BIT;

	m_blanklines.AddMsg(&line);
	m_blanklines_ObjectList.Init(m_blanklines, this);
}

void SurfDoc::AddLine(vdouble &x, vdouble &y, vdouble &z, COLORREF color )
{
	Line3D line(this);
	m_lines.AddMsg(&line);
	m_lines.GetLastMsg().Init(x,y,z,color);
	m_lines_ObjectList.Init(m_lines, this);
}
void SurfDoc::AddLine(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color )
{
	Line3D line(this);
	m_lines.AddMsg(&line);
	m_lines.GetLastMsg().Init(x,y,z,color);
	m_lines_ObjectList.Init(m_lines, this);
}
void SurfDoc::AddPoligon(CPoint3* pts, int len, COLORREF color )
{
	Poligon3D poly(this);
	this->m_polygones.AddMsg(&poly);
	this->m_polygones.GetLastMsg().InitPoints(pts, len, color);
	this->m_polygones_ObjectList.Init(this->m_polygones, this);
}
void SurfDoc::AddPoligon(Poligon3D& poly)
{
//	poly.m_pSurfDoc=this;
	this->m_polygones.AddMsg(&poly);
	this->m_polygones_ObjectList.Init(this->m_polygones, this);
}
Line3D* SurfDoc::AddLine()
{
	Line3D line(this);
	m_lines.AddMsg(&line);
	m_lines_ObjectList.Init(m_lines, this);
	if (this->m_lines.SetCurrentMsgOnLast())
		return &m_lines.GetCurrentMsg();
	else
		return NULL;
}
void SurfDoc::AddLine(COLORREF color)
{
	Line3D line(this);
	m_lines.AddMsg(&line);
	m_lines.GetLastMsg().m_color = color;
	m_lines_ObjectList.Init(m_lines, this);
}
void SurfDoc::AddCutLine()
{
	Line3D line(this);
	m_cutlines.AddMsg(&line);
	m_cutlines_ObjectList.Init(m_cutlines, this);
}
void SurfDoc::AddCutLine(COLORREF color)
{
	Line3D line(this);
	m_cutlines.AddMsg(&line);
	m_cutlines.GetLastMsg().m_color = color;
	m_cutlines_ObjectList.Init(m_cutlines, this);
}
void SurfDoc::AddLine(CPoint3* pts, int len, COLORREF color )
{
	Line3D line(this);
	m_lines.AddMsg(&line);
	m_lines.GetLastMsg().InitPoints(pts, len, color);
	m_lines_ObjectList.Init(m_lines, this);
}
void SurfDoc::AddCutLine(CPoint3* pts, int len, COLORREF color )
{
	Line3D line(this);
	m_cutlines.AddMsg(&line);
	m_cutlines.GetLastMsg().InitPoints(pts, len, color);
	m_cutlines_ObjectList.Init(m_cutlines, this);
}


size_t SurfDoc::AddSurf(long id_surf, BYTE podoshva, int zflag, vdouble &x, vdouble &y, vdouble &z)
{
	vdouble visible;
	visible.resize(x.Length(),1.0);
	return AddSurf(id_surf, podoshva, zflag, x,y,z,visible );
}
size_t SurfDoc::AddSurf(long id_surf, BYTE podoshva, int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible )
{
	COLORREF color = RGB(125, 204, 255);
	return AddSurf(id_surf, podoshva, zflag, x,y,z,visible,color );
}

void SurfDoc::AddWells(vector<vector<cell> > * pdrills)
{
	vector<vector<cell> >::iterator Iter;
	for ( Iter = pdrills->begin(); Iter != pdrills->end(); Iter++)
	{
		Well_3D drill(this);
		m_drills.AddMsg(&drill);
		m_drills.GetLastMsg().ReinitWellColomnsPointers();
		m_drills.GetLastMsg().WellInit1(Iter);
	}
	m_drills_ObjectList.Init(m_drills, this);
}
bool FindWellID(LPDRILLSDLGDATA lpDrillsDlgMem, vector<vector<cell> >::iterator & Iter_vect_cell, string & well_id)
{
	// find Well ID
	bool well_id_found = false;
	vector<int>::iterator iter_types_col;
	vector<cell>::iterator iter_cell;

	for(iter_types_col = lpDrillsDlgMem->types_of_colomns->begin(),	iter_cell = Iter_vect_cell->begin(); 
		iter_types_col != lpDrillsDlgMem->types_of_colomns->end(),	iter_cell != Iter_vect_cell->end(); 
		iter_types_col++, iter_cell++)
	{
		cell temp = *iter_cell;
		switch (*iter_types_col)
		{
		case WELL_COLOMN_TYPE_NOT_USED:// this colomn not used
			break;
		case WELL_COLOMN_TYPE_WELL_ID: //well ID value
			well_id = temp.str;
			well_id_found = true;
			break;
		case WELL_COLOMN_TYPE_X://X
			break;
		case WELL_COLOMN_TYPE_Y://Y
			break;
		case WELL_COLOMN_TYPE_USTJE_ALT://ustje altitude
			break;
		case WELL_COLOMN_TYPE_SLOI_PODOSHVA_ALT://sloi podoshva altitude WellColomn * w_colomn = this->AddWellColomn(WellElement::type::IGE_podoshva);w_colomn->check_draw = true;w_colomn->draw_width = 4.f;
		case WELL_COLOMN_TYPE_SLOI_PODOSHVA_GLUBINA://sloi podoshva glubina
		case WELL_COLOMN_TYPE_SLOI_MOSCHNOST:
			break;
		case WELL_COLOMN_TYPE_ZABOJ_ALTITUDE://zaboj altitude
			break;
		case WELL_COLOMN_TYPE_ZABOJ_GLUBINA://zaboj glubina
			break;
		case WELL_COLOMN_TYPE_KAROTAZH:// karotazh
			break;
		case WELL_COLOMN_TYPE_HYDRO_PROJAVLENIE_UST: //WellElement::type::hydro_projavlenie
		case WELL_COLOMN_TYPE_HYDRO_PROJAVLENIE_POJAV: //WellElement::type::hydro_projavlenie
			break;
		}
	}
	return well_id_found;

}
void SurfDoc::AddWells(LPDRILLSDLGDATA lpDrillsDlgMem, bool fill_well_colomn, bool is_ige)
{
	vector<vector<cell> >::iterator Iter_vect_cell;
	vector<int>::iterator check_iter; 
	vector<cell> * karotazh_glubin = NULL;

	wells_draw_list_item * wdli_podoshva = NULL;
	wells_draw_list_item * wdli_hydro = NULL;
	if (fill_well_colomn)
	{
		bool podoshva = false;
		bool hydro = false;
		for( vector<int>::iterator iter_types_col = lpDrillsDlgMem->types_of_colomns->begin(); 
			iter_types_col != lpDrillsDlgMem->types_of_colomns->end(); iter_types_col++)
		{
			switch (*iter_types_col)
			{
			case WELL_COLOMN_TYPE_NOT_USED:// this colomn not used
				break;
			case WELL_COLOMN_TYPE_WELL_ID: //well ID value
				break;
			case WELL_COLOMN_TYPE_X://X
				break;
			case WELL_COLOMN_TYPE_Y://Y
				break;
			case WELL_COLOMN_TYPE_USTJE_ALT://ustje altitude
				break;
			case WELL_COLOMN_TYPE_SLOI_PODOSHVA_ALT://sloi podoshva altitude WellColomn * w_colomn = this->AddWellColomn(WellElement::type::IGE_podoshva);w_colomn->check_draw = true;w_colomn->draw_width = 4.f;
			case WELL_COLOMN_TYPE_SLOI_PODOSHVA_GLUBINA://sloi podoshva glubina
			case WELL_COLOMN_TYPE_SLOI_MOSCHNOST:
				podoshva = true;
				break;
			case WELL_COLOMN_TYPE_ZABOJ_ALTITUDE://zaboj altitude
				break;
			case WELL_COLOMN_TYPE_ZABOJ_GLUBINA://zaboj glubina
				break;
			case WELL_COLOMN_TYPE_KAROTAZH:// karotazh
				break;
			case WELL_COLOMN_TYPE_HYDRO_PROJAVLENIE_UST: //WellElement::type::hydro_projavlenie
			case WELL_COLOMN_TYPE_HYDRO_PROJAVLENIE_POJAV: //WellElement::type::hydro_projavlenie
				hydro = true;
				break;
			}
		}
		if (podoshva)
		{
			if (is_ige)
				wdli_podoshva = AddWellsDraw(WellElement::type::IGE_podoshva, true, 20.f, false, wells_draw_list_item::draw_mode_2d::left);
			else
				wdli_podoshva = AddWellsDraw(WellElement::type::litho_podoshva, true, 30.f, false, wells_draw_list_item::draw_mode_2d::right);
		}
		if (hydro) wdli_hydro = AddWellsDraw(WellElement::type::hydro_projavlenie, true, 60.f, true, wells_draw_list_item::draw_mode_2d::both);
	}

	for (
		Iter_vect_cell = lpDrillsDlgMem->pdrills->begin(), check_iter = lpDrillsDlgMem->checking_of_rows->begin(); 
		Iter_vect_cell != lpDrillsDlgMem->pdrills->end() && check_iter != lpDrillsDlgMem->checking_of_rows->end(); 
	Iter_vect_cell++, check_iter++)
	{
		if( (*check_iter) != 2)
		{
			if(karotazh_glubin == NULL)
			{
				karotazh_glubin = &(*Iter_vect_cell);

				AddKarotazh(lpDrillsDlgMem->filename);

			}
			continue;
		}

		// find Well ID
		// то же что и 
		// Номер выработки
		// в форме заполнения Excel для КТ
		string well_id; 
		bool well_id_found = FindWellID(lpDrillsDlgMem, Iter_vect_cell, well_id);
		Well_3D * found_well = NULL;
		if (well_id_found)
			found_well = this->FindWell(well_id.c_str());

		if (found_well)
		{
			if (!found_well->WellInit2(Iter_vect_cell, 
				karotazh_glubin,
				lpDrillsDlgMem->types_of_colomns,
				lpDrillsDlgMem->pnames_of_colomns,
				lpDrillsDlgMem->colors_of_sloi,
				lpDrillsDlgMem->filename, 
				wdli_podoshva, is_ige,
				wdli_hydro,
				true
				//false
				)
				)
				return;
		}
		else
		{
			Well_3D drill(this);
			if (!drill.WellInit2(Iter_vect_cell, 
				karotazh_glubin,
				lpDrillsDlgMem->types_of_colomns,
				lpDrillsDlgMem->pnames_of_colomns,
				lpDrillsDlgMem->colors_of_sloi,
				lpDrillsDlgMem->filename,
				wdli_podoshva, is_ige,
				wdli_hydro,
				true)
				)
				return;
			m_drills.AddMsg(&drill);
			m_drills.GetLastMsg().ReinitWellColomnsPointers();
		}
	}
	m_drills_ObjectList.Init(m_drills, this);
}
int SurfDoc::GetIndexForNewKarotazh()
{
#if 0 //KAROTAZH_LIST_AS_MAP
	int id, maxid = -1;
	bool start = true;
	for (map<int,karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin(); it != Well_3D::karotazh_list.end(); it++)
	{
		id = it->first;
		if (start)
		{
			maxid = id;
			start = false;
		}
		else
		{
			if (maxid < id) maxid = id;
		}
	}
	id = maxid + 1;
	return id;
#else
	return(int)Well_3D::karotazh_list.size();
#endif
}
void SurfDoc::UpdateWellDrawListNames()
{
	size_t r = 0;
	for (vector<wells_draw_list_item *>::iterator it = Well_3D::wells_draw_list.begin();
		it != Well_3D::wells_draw_list.end(); it++, r++)
	{
		if (*it)
		{
			(*it)->my_name = this->m_WellsDrawListViewTab.GetItemString(r,0);
			(*it)->draw_width = atof(this->m_WellsDrawListViewTab.GetItemString(r,1).c_str());
		}
	}
}
void SurfDoc::UpdateLabLayersListNames()
{
	size_t r = 0;
	/*for (vector<wells_draw_list_item *>::iterator it = Well_3D::wells_draw_list.begin();
		it != Well_3D::wells_draw_list.end(); it++, r++)
	{
		if (*it)
		{
			(*it)->my_name = this->m_WellsDrawListViewTab.GetItemString(r,0);
			(*it)->draw_width = atof(this->m_WellsDrawListViewTab.GetItemString(r,1).c_str());
		}
	}*/
}
void SurfDoc::UpdateWellDrawListWidth()
{
	char str[512];
	size_t r = 0;
	for (vector<wells_draw_list_item *>::iterator it = Well_3D::wells_draw_list.begin();
		it != Well_3D::wells_draw_list.end(); it++, r++)
	{
		if (*it)
		{
			sprintf(str, "%0.1f\0", (*it)->draw_width);
			this->m_WellsDrawListViewTab.SetItemString(r, 1, str);
		}
	}
}
void SurfDoc::WellsDrawList_MoveItemUp(int context_menu_item)
{
	if (context_menu_item > 0 && context_menu_item < (int)Well_3D::wells_draw_list.size())
	{
		wells_draw_list_item * temp = Well_3D::wells_draw_list[context_menu_item];
		Well_3D::wells_draw_list[context_menu_item] = Well_3D::wells_draw_list[context_menu_item-1];
		Well_3D::wells_draw_list[context_menu_item-1] = temp;

		this->m_WellsDrawListViewTab.MoveItemUp(context_menu_item);

		if ( Well_3D::wells_draw_list[context_menu_item] && Well_3D::wells_draw_list[context_menu_item-1])
		{
			float width = Well_3D::wells_draw_list[context_menu_item]->draw_width;
			Well_3D::wells_draw_list[context_menu_item]->draw_width = Well_3D::wells_draw_list[context_menu_item-1]->draw_width;
			Well_3D::wells_draw_list[context_menu_item-1]->draw_width = width;

			this->UpdateWellDrawListWidth();
		}
	}
}

void SurfDoc::WellsDrawList_MoveItemDown(int context_menu_item)
{
	if (context_menu_item > -1 && context_menu_item < int(Well_3D::wells_draw_list.size())-1)
	{
		wells_draw_list_item * temp = Well_3D::wells_draw_list[context_menu_item];
		Well_3D::wells_draw_list[context_menu_item] = Well_3D::wells_draw_list[context_menu_item+1];
		Well_3D::wells_draw_list[context_menu_item+1] = temp;
		
		this->m_WellsDrawListViewTab.MoveItemDown(context_menu_item);

		if ( Well_3D::wells_draw_list[context_menu_item] && Well_3D::wells_draw_list[context_menu_item+1])
		{
			float width = Well_3D::wells_draw_list[context_menu_item]->draw_width;
			Well_3D::wells_draw_list[context_menu_item]->draw_width = Well_3D::wells_draw_list[context_menu_item+1]->draw_width;
			Well_3D::wells_draw_list[context_menu_item+1]->draw_width = width;
			
			this->UpdateWellDrawListWidth();
		}	
	}
}

wells_draw_list_item * SurfDoc::AddWellsDraw(WellElement::type t, bool check, float width,  bool to_end_of_vector, wells_draw_list_item::draw_mode_2d drawmode2d)
{
	int id = (int)Well_3D::wells_draw_list.size();
	wells_draw_list_item * wdli = new wells_draw_list_item(t, check, width, id, WellElement::WellElementTypeToString(t), drawmode2d);
	
	if (to_end_of_vector)
		Well_3D::wells_draw_list.push_back(wdli);
	else
		Well_3D::wells_draw_list.insert(Well_3D::wells_draw_list.begin(), wdli);

	this->m_WellsDrawListViewTab.AddRow(LPARAM(0), &wdli->check_draw);
	return wdli;
}

void SurfDoc::UpdateWellColomnsByWellsDraw()
{
	//m_wdli_primitive;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().UpdateWellColomnsByWellsDraw();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}

void SurfDoc::ClearSurfIgeMappingItem(long id_surf)
{
	vector<key_grid>::iterator it = this->surf_eng_geo_element_mapping.begin();
	while (it !=  this->surf_eng_geo_element_mapping.end())
	{
		if (id_surf == (*it).id_surf)
		{
			this->surf_eng_geo_element_mapping.erase(it);
			break;
		}
		it++;
	}
}
void SurfDoc::ClearSurfLitoMappingItem(long id_surf)
{
	vector<key_grid>::iterator it = this->surf_litho_geo_element_mapping.begin();
	while (it !=  this->surf_litho_geo_element_mapping.end())
	{
		if (id_surf == (*it).id_surf)
		{
			this->surf_litho_geo_element_mapping.erase(it);
			break;
		}
		it++;
	}
}

void SurfDoc::AddSurfIgeMappingItem(long id_surf, BYTE podoshva, const char * surf_name, const char * ige_key)
{
	this->surf_eng_geo_element_mapping.push_back(key_grid(id_surf, podoshva, surf_name, ige_key));
}
void SurfDoc::AddSurfIgeMappingItemToDB(long id_surf, const char * ige_key)
{
	if (this->m_pLabDoc)
	{
		long id_ige = -1;
		bool id_ige_found = false;
		for (vector<IGE_Data>::iterator it_ige = m_db_ige.data.begin();
			it_ige != m_db_ige.data.end(); it_ige++)
		{
			if ((*it_ige).ige_filled)
			{
				if (!strcmp( (*it_ige).ige.ige.c_str(), ige_key))
				{
					id_ige = (*it_ige).ige.id_ige;
					id_ige_found = true;
					break;
				}
			}
		}
		//if(id_ige_found)
			this->m_pLabDoc->AddSurfIgeMappingItem(id_obj, id_surf, id_ige);
	}
}
void SurfDoc::AddSurfLitoMappingItem(long id_surf, BYTE podoshva, const char * surf_name, const char * ige_key)
{
	this->surf_litho_geo_element_mapping.push_back(key_grid(id_surf, podoshva, surf_name, ige_key));
}
void SurfDoc::AddSurfLitoMappingItemToDB(long id_surf, const char * ige_key)
{
	if (this->m_pLabDoc)
	{
		long id_ige = -1;
		bool id_ige_found = false;
		for (vector<IGE_Data>::iterator it_ige = m_db_ige0.data.begin();
			it_ige != m_db_ige0.data.end(); it_ige++)
		{
			if ((*it_ige).ige_filled)
			{
				if (!strcmp( (*it_ige).ige.ige.c_str(), ige_key))
				{
					id_ige = (*it_ige).ige.id_ige;
					id_ige_found = true;
					break;
				}
			}
		}
		//if(id_ige_found)
			this->m_pLabDoc->AddSurfLitoMappingItem(id_obj, id_surf, id_ige);
	}
}

void SurfDoc::SurfIgeMapping(long id_surf, long id_ige)
{
	string surf = "";
	string ige = "";
	BYTE podoshva = 0;
	bool ige_found = false;

	for (map<long, db_griddata_surf>::iterator it = this->m_db_griddata.datas.begin();
		it != this->m_db_griddata.datas.end(); it++)
	{
		if (id_surf == (*it).first && (*it).second.data2_filled)
		{
			surf = (*it).second.data2.nazva;
			podoshva = (*it).second.data2.podoshva;
			break;
		}
	}

	for (vector<IGE_Data>::iterator it_ige = m_db_ige.data.begin();
		it_ige != m_db_ige.data.end(); it_ige++)
	{
		if ((*it_ige).ige_filled)
		{
			if ( (*it_ige).ige.id_ige == id_ige)
			{
				ige = (*it_ige).ige.ige;
				ige_found = true;
				break;
			}
		}
	}

	//if (/*podoshva == 1 &&*/ ige_found)
		this->surf_eng_geo_element_mapping.push_back(key_grid(id_surf, podoshva, surf, ige));
}
void SurfDoc::SurfLitoMapping(long id_surf, long id_ige)
{
	string surf = "";
	string ige = "";
	BYTE podoshva = 0;
	bool ige_found = false;

	for (map<long, db_griddata_surf>::iterator it = this->m_db_griddata.datas.begin();
		it != this->m_db_griddata.datas.end(); it++)
	{
		if (id_surf == (*it).first && (*it).second.data2_filled)
		{
			surf = (*it).second.data2.nazva;
			podoshva = (*it).second.data2.podoshva;
			break;
		}
	}


	for (vector<IGE_Data>::iterator it_ige = m_db_ige0.data.begin();
		it_ige != m_db_ige0.data.end(); it_ige++)
	{
		if ((*it_ige).ige_filled)
		{
			if ( (*it_ige).ige.id_ige == id_ige)
			{
				ige = (*it_ige).ige.ige;
				ige_found = true;
				break;
			}
		}
	}

	//if (/*podoshva == 1 &&*/ ige_found)
		this->surf_litho_geo_element_mapping.push_back(key_grid(id_surf, podoshva, surf, ige));
}

void SurfDoc::SurfacesOrder(long npp, BYTE check, long id_surf, BYTE podoshva, BYTE check2)
{
	//long id = npp;
	surface_order_list_item * wdli = new surface_order_list_item(check, id_surf, podoshva, "");
	GeoSurface::surface_order_list.push_back(wdli);
	this->m_SurfacesOrderListViewTab.AddRow(LPARAM(0), &wdli->check);
}
void SurfDoc::SurfacesBlankOrder(long npp, long id_surf, BYTE podoshva, 
	BYTE check_blank_me,
	BYTE check_blank_me_up,
	BYTE check_blank_me_up_above,
	BYTE check_blank_me_down, 
	BYTE check_blank_me_down_above,
	BYTE check_blank_by_me_up,
	BYTE check_blank_by_me_down
	)
{
	//long id = npp;
	surface_blank_order_list_item * wdli = new surface_blank_order_list_item(id_surf, podoshva, "");
	GeoSurface::surface_blank_order_list.push_back(wdli);
	wdli->check_blank_me = check_blank_me;
	wdli->check_blank_me_up = check_blank_me_up;
	wdli->check_blank_me_up_above = check_blank_me_up_above;
	wdli->check_blank_me_down = check_blank_me_down;
	wdli->check_blank_me_down_above = check_blank_me_down_above;
	wdli->check_blank_by_me_up = check_blank_by_me_up;
	wdli->check_blank_by_me_down = check_blank_by_me_down;

	this->m_SurfacesBlankOrderListViewTab.AddRow(LPARAM(0), &wdli->check_blank_me);
}

void SurfDoc::SurfacesBlankFuntions(/*long id_item, */long id_surf_obj, long id_surf_param, BYTE id_blank_fun)
{
	surface_blank_functions_list_item * wdli = new surface_blank_functions_list_item(/*id_item, */id_surf_obj, id_surf_param, id_blank_fun);
	GeoSurface::surface_blank_functions_list.push_back(wdli);
	this->m_SurfacesBlankFunctionsListViewTab.AddRow(LPARAM(0), NULL);
}



void SurfDoc::ApplySurfacesOrder()
{
	//имена поверхностей прописываем в списках перечисления поверхностей
	//ищем по построенным поверхностям

	
	for (vector<surface_blank_functions_list_item *>::iterator 
		it = GeoSurface::surface_blank_functions_list.begin();
		it != GeoSurface::surface_blank_functions_list.end(); it++)
	{
		this->InitSurfaceBlankFinctionNames(*it);
	}

	for (vector<surface_blank_order_list_item *>::iterator 
		it = GeoSurface::surface_blank_order_list.begin();
		it != GeoSurface::surface_blank_order_list.end(); it++)
	{
		if ((*it))
		{
			//this->FindGridData(id_surf);
			GeoSurface * found = this->FindGeoSurface((*it)->id_surf);
			if (found)
			{
				(*it)->my_name = found->GetName();
			}
		}
	}

	for (vector<surface_order_list_item *>::iterator 
		it = GeoSurface::surface_order_list.begin();
		it != GeoSurface::surface_order_list.end(); it++)
	{
		if ((*it))
		{
			//this->FindGridData(id_surf);
			GeoSurface * found = this->FindGeoSurface((*it)->id_surf);
			if (found)
			{
				(*it)->my_name = found->GetName();
			}
//			FindIGE((*it)->id_surf);
		}
	}

}

void SurfDoc::SurfaceOrderList_UpdateCheckings()
{
	if (this->m_pLabDoc)
	{
		for (vector<surface_order_list_item *>::iterator it = GeoSurface::surface_order_list.begin();
			it != GeoSurface::surface_order_list.end(); it++)
		{
			if ((*it))
			{
				this->m_pLabDoc->SurfaceOrderList_UpdateChecking(id_obj, (*it)->id_surf, (*it)->check);
			}
		}
	}
}
void SurfDoc::SurfaceBlankOrderList_UpdateCheckings()
{
	if (this->m_pLabDoc)
	{
		for (vector<surface_blank_order_list_item *>::iterator it = GeoSurface::surface_blank_order_list.begin();
			it != GeoSurface::surface_blank_order_list.end(); it++)
		{
			if ((*it))
			{
				this->m_pLabDoc->SurfaceBlankOrderList_UpdateChecking(id_obj, (*it)->id_surf, (*it));
			}
		}
	}
}
void SurfDoc::SurfaceOrderList_MoveItemUp(int context_menu_item)
{
	if (context_menu_item > 0 && context_menu_item < (int)GeoSurface::surface_order_list.size())
	{
		surface_order_list_item * temp = GeoSurface::surface_order_list[context_menu_item];
		GeoSurface::surface_order_list[context_menu_item] = GeoSurface::surface_order_list[context_menu_item-1];
		GeoSurface::surface_order_list[context_menu_item-1] = temp;

		this->m_SurfacesOrderListViewTab.MoveItemUp(context_menu_item);
		if (this->m_pLabDoc)
		{
			long npp = context_menu_item + 1;
			this->m_pLabDoc->SurfaceOrderList_MoveItemUp(this->id_obj, npp);
		}
	}
}

void SurfDoc::SurfaceOrderList_MoveItemDown(int context_menu_item)
{
	if (context_menu_item > -1 && context_menu_item < int(GeoSurface::surface_order_list.size())-1)
	{
		surface_order_list_item * temp = GeoSurface::surface_order_list[context_menu_item];
		GeoSurface::surface_order_list[context_menu_item] = GeoSurface::surface_order_list[context_menu_item+1];
		GeoSurface::surface_order_list[context_menu_item+1] = temp;
		
		this->m_SurfacesOrderListViewTab.MoveItemDown(context_menu_item);	
		if (this->m_pLabDoc)
		{
			long npp = context_menu_item + 1;
			this->m_pLabDoc->SurfaceOrderList_MoveItemDown(this->id_obj, npp);
		}
	}
}
template <class T>
T* Find_ID_SURF(long id_surf, vector<T *> & list)
{
	for (vector<T *>::iterator it = list.begin();
		it != list.end(); it++)
	{
		if ((*it) && (*it)->id_surf == id_surf)
		{
			return (*it);
		}
	}
	return NULL;
}

surface_order_list_item * SurfDoc::AddSurfaceOrder(bool check, long id_surf, BYTE podoshva, const char * name, bool to_end_of_vector)
{
	surface_order_list_item * wdli = Find_ID_SURF(id_surf, 
		GeoSurface::surface_order_list);
	if (wdli) return wdli;

	wdli = new surface_order_list_item(check, id_surf, podoshva, name);
	
	if (to_end_of_vector)
		GeoSurface::surface_order_list.push_back(wdli);
	else
		GeoSurface::surface_order_list.insert(GeoSurface::surface_order_list.begin(), wdli);

	this->m_SurfacesOrderListViewTab.AddRow(LPARAM(0), &wdli->check);
	if (this->m_pLabDoc)
	{
		long npp = (long)GeoSurface::surface_order_list.size();
		bool check2 = false;
		this->m_pLabDoc->AddSurfacesOrderItem(this->id_obj, npp, BYTE(check), id_surf, podoshva, BYTE(check2));
	}
	return wdli;
}

void SurfDoc::SurfaceBlankFunctionsList_SwapItemSurfaces(int context_menu_item)
{
	if (context_menu_item >= 0 && context_menu_item < (int)GeoSurface::surface_blank_functions_list.size())
	{
		surface_blank_functions_list_item * item =
			GeoSurface::surface_blank_functions_list[context_menu_item];
		if (item && item->id_blank_fun != 0)
		{
			BYTE new_id_blank_fun = item->id_blank_fun == 1 ? 2 : 1;
			CString str;
			str.Format(
				"Вы действительно хотите поменять местами\n"
				"поверхности в функции бланкования\n"
				"поверхности %s id_surf = %d\n"
				"с помощью поверхности %s id_surf = %d\n",
				item->name_surf_obj.c_str(),
				item->id_surf_obj,
				item->name_surf_param.c_str(),
				item->id_surf_param);

			if (IDYES == MessageBox(this->hSurfWnd, str, "Изменение функции бланкования", MB_YESNO))
			{
				if (this->m_pLabDoc)
				{
					this->m_pLabDoc->SurfaceBlankFunctionsList_SwapItemSurfaces(
						this->id_obj, item->id_surf_obj, item->id_surf_param, item->id_blank_fun);
				}

				long id_surf_obj = item->id_surf_obj;
				long id_surf_param = item->id_surf_param;
				string name_surf_obj = item->name_surf_obj;
				string name_surf_param = item->name_surf_param;

				item->id_surf_obj = id_surf_param;
				item->id_surf_param = id_surf_obj;

				item->name_surf_obj = name_surf_param;
				item->name_surf_param = name_surf_obj;
			}

			this->m_SurfacesBlankFunctionsListViewTab.SetItemString(context_menu_item, 0,
				item->name_surf_obj);

			this->m_SurfacesBlankFunctionsListViewTab.SetItemString(context_menu_item, 1,
				item->name_surf_param);
		
		}
	}
}
void SurfDoc::SurfaceBlankFunctionsList_SwapItemMethod(int context_menu_item)
{
	if (context_menu_item >= 0 && context_menu_item < (int)GeoSurface::surface_blank_functions_list.size())
	{
		surface_blank_functions_list_item * item = GeoSurface::surface_blank_functions_list[context_menu_item];
		if (item && item->id_blank_fun != 0)
		{
			BYTE new_id_blank_fun = item->id_blank_fun == 1 ? 2 : 1;
			CString str;
			str.Format("Вы действительно хотите изменить метод бланкования\n"
				"поверхности %s id_surf = %d\n"
				"с помощью поверхности %s id_surf = %d\n"
				"с метода %s\n"
				"на метод %s",
				item->name_surf_obj.c_str(),
				item->id_surf_obj,
				item->name_surf_param.c_str(),
				item->id_surf_param,
				surface_blank_functions_list_item::get_blank_function_name(item->id_blank_fun).c_str(),
				surface_blank_functions_list_item::get_blank_function_name(new_id_blank_fun).c_str());

			if (IDYES == MessageBox(this->hSurfWnd, str, "Изменение функции бланкования", MB_YESNO))
			{
				if (this->m_pLabDoc)
				{
					this->m_pLabDoc->SurfaceBlankFunctionsList_SwapItemMethod(
						this->id_obj, item->id_surf_obj, item->id_surf_param, item->id_blank_fun);
				}
				item->id_blank_fun = item->id_blank_fun == 1 ? 2 : 1;
			}

			this->m_SurfacesBlankFunctionsListViewTab.SetItemString(context_menu_item, 2,
				surface_blank_functions_list_item::get_blank_function_name(new_id_blank_fun));
		
		}
	}
}


void SurfDoc::SurfaceBlankOrderList_MoveItemUp(int context_menu_item)
{
	if (context_menu_item > 0 && context_menu_item < (int)GeoSurface::surface_blank_order_list.size())
	{
		surface_blank_order_list_item * temp = GeoSurface::surface_blank_order_list[context_menu_item];
		GeoSurface::surface_blank_order_list[context_menu_item] = GeoSurface::surface_blank_order_list[context_menu_item-1];
		GeoSurface::surface_blank_order_list[context_menu_item-1] = temp;

		this->m_SurfacesBlankOrderListViewTab.MoveItemUp(context_menu_item);
		if (this->m_pLabDoc)
		{
			long npp = context_menu_item + 1;
			this->m_pLabDoc->SurfaceBlankOrderList_MoveItemUp(this->id_obj, npp);
		}
	}
}

void SurfDoc::SurfaceBlankOrderList_MoveItemDown(int context_menu_item)
{
	if (context_menu_item > -1 && context_menu_item < int(GeoSurface::surface_blank_order_list.size())-1)
	{
		surface_blank_order_list_item * temp = GeoSurface::surface_blank_order_list[context_menu_item];
		GeoSurface::surface_blank_order_list[context_menu_item] = GeoSurface::surface_blank_order_list[context_menu_item+1];
		GeoSurface::surface_blank_order_list[context_menu_item+1] = temp;
		
		this->m_SurfacesBlankOrderListViewTab.MoveItemDown(context_menu_item);
		if (this->m_pLabDoc)
		{
			long npp = context_menu_item + 1;
			this->m_pLabDoc->SurfaceBlankOrderList_MoveItemDown(this->id_obj, npp);
		}
	}
}



surface_blank_order_list_item * SurfDoc::AddSurfaceBlankOrder(long id_surf, BYTE podoshva, const char * name, bool to_end_of_vector)
{
	surface_blank_order_list_item * wdli = Find_ID_SURF<surface_blank_order_list_item>(id_surf, 
		GeoSurface::surface_blank_order_list);
	if (wdli) return wdli;

	wdli = new surface_blank_order_list_item(id_surf, podoshva, name);
	
	if (to_end_of_vector)
		GeoSurface::surface_blank_order_list.push_back(wdli);
	else
		GeoSurface::surface_blank_order_list.insert(GeoSurface::surface_blank_order_list.begin(), wdli);

	this->m_SurfacesBlankOrderListViewTab.AddRow(LPARAM(0), &wdli->check_blank_me);
	if (this->m_pLabDoc)
	{
		long npp = (long)GeoSurface::surface_blank_order_list.size();
		bool check2 = false;
		this->m_pLabDoc->AddSurfacesBlankOrderItem(this->id_obj, npp, id_surf, podoshva, wdli);
	}
	return wdli;
}

template <class T>
T* Find_ID_SURF(long id_surf_obj, long id_surf_param, vector<T *> & list)
{
	for (vector<T *>::iterator it = list.begin();
		it != list.end(); it++)
	{
		if ((*it) && (*it)->id_surf_obj == id_surf_obj && (*it)->id_surf_param == id_surf_param)
		{
			return (*it);
		}
	}
	return NULL;
}
void SurfDoc::InitSurfaceBlankFinctionNames(surface_blank_functions_list_item * item)
{
	if (item)
	{
		GeoSurface * found_obj = this->FindGeoSurface(item->id_surf_obj);
		if (found_obj)
		{
			char str[1024];
			sprintf(str, "%d %s\0", item->id_surf_obj, found_obj->GetName().c_str());
			//item->name_surf_obj = found_obj->GetName();
			item->name_surf_obj = str;
		}

		GeoSurface * found_param = this->FindGeoSurface(item->id_surf_param);
		if (found_param)
		{
			char str[1024];
			sprintf(str, "%d %s\0", item->id_surf_param, found_param->GetName().c_str());
			//item->name_surf_param = found_param->GetName();
			item->name_surf_param = str;
		}
	}
}
surface_blank_functions_list_item * SurfDoc::AddSurfaceBlankFunction(long id_surf_obj, long id_surf_param, BYTE id_blank_fun)
{
	surface_blank_functions_list_item * wdli = Find_ID_SURF<surface_blank_functions_list_item>(id_surf_obj, id_surf_param, 
		GeoSurface::surface_blank_functions_list);
	if (wdli) return wdli;

	wdli = new surface_blank_functions_list_item(/*-1, */id_surf_obj, id_surf_param, id_blank_fun);
				
	this->InitSurfaceBlankFinctionNames(wdli);

	GeoSurface::surface_blank_functions_list.push_back(wdli);

	this->m_SurfacesBlankFunctionsListViewTab.AddRow(LPARAM(0), NULL);
	size_t r = this->m_SurfacesBlankFunctionsListViewTab.Rows()-1;
	this->m_SurfacesBlankFunctionsListViewTab.SetItemString(r,0,wdli->name_surf_obj);
	this->m_SurfacesBlankFunctionsListViewTab.SetItemString(r,1,wdli->name_surf_param);
	this->m_SurfacesBlankFunctionsListViewTab.SetItemString(r,2, 
		surface_blank_functions_list_item::get_blank_function_name(wdli->id_blank_fun));
	
	if (this->m_pLabDoc)
	{
		//long npp = (long)GeoSurface::surface_blank_functions_list.size();
		this->m_pLabDoc->AddSurfacesBlankFunctionsItem(this->id_obj, id_surf_obj, id_surf_param, id_blank_fun);
	}
	return wdli;
}



void SurfDoc::DeleteSurfaceBlankFunction(long r)
{
	if (r > -1 && r < GeoSurface::surface_blank_functions_list.size())
	{
		vector<surface_blank_functions_list_item *>::iterator to_erase = 
			r + GeoSurface::surface_blank_functions_list.begin();

		if (to_erase != GeoSurface::surface_blank_functions_list.end())
		{
			CString str;
			str.Format("Вы действительно хотите удалить\n"
				"функцию бланкования\n",
				"поверхности %s id_surf = %d\n"
				"с помощью поверхности %s id_surf = %d\n"
				"с метода %s\n"
				"на метод %s",
				(*to_erase)->name_surf_obj.c_str(),
				(*to_erase)->id_surf_obj,
				(*to_erase)->name_surf_param.c_str(),
				(*to_erase)->id_surf_param,
				surface_blank_functions_list_item::get_blank_function_name((*to_erase)->id_blank_fun).c_str());

			if (IDYES == MessageBox(this->hSurfWnd, str, "Удаление функций бланкования", MB_YESNO))
			{
				BYTE id_blank_fun = (*to_erase)->id_blank_fun;
				long id_surf_obj = (*to_erase)->id_surf_obj;
				long id_surf_param = (*to_erase)->id_surf_param;

				GeoSurface::surface_blank_functions_list.erase(to_erase);
				this->m_SurfacesBlankFunctionsListViewTab.EraseRow(r);

				if (this->m_pLabDoc)
				{
					this->m_pLabDoc->DeleteSurfacesBlankFunctionsItem(
						this->id_obj, id_surf_obj, id_surf_param, id_blank_fun);
				}
			}
		}
	}
}



int SurfDoc::AddKarotazh(const char * name, COLORREF color, bool if_exist_add_new)
{
	int kar_index = Well_3D::GetKarotazhIndex(name);

	if (kar_index == -1 || if_exist_add_new)
	{
		kar_index = (int)Well_3D::karotazh_list.size();
		Well_3D::karotazh_list.push_back(karotazh_list_item(kar_index,name, color));
		this->m_KarotazhListViewTab.AddRow(LPARAM(0), &Well_3D::karotazh_list[kar_index].checked);
	}
	return kar_index;
}



double SurfDoc::GetWellW()
{
	double w = 1.0;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			w = this->m_drills.GetCurrentMsg().GetW();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	return w;
}



void SurfDoc::SetWellW(double w)
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().SetW(w);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}



Well_3D * SurfDoc::FindWell(long id_kt)
{
	Well_3D * found  = NULL;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( this->m_drills.GetCurrentMsg().GetIdKt() == id_kt)
			{
				found = &this->m_drills.GetCurrentMsg();
				break;
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	return found;
}



Well_3D * SurfDoc::FindWell(const char * well_id)
{
	Well_3D * found  = NULL;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			const char * id = this->m_drills.GetCurrentMsg().GetIDString();
			const char * p = id;
			size_t m = strlen(well_id);
			size_t n = strlen(id);
			const char * p0 = strchr (id, '\"');
			const char * p1 = strrchr (id, '\"');
			if (p0)
			{
				++p;
				--n;
			}
			if (p1)
			{
				--n;
			}
			if ( m == n && strncmp(p, well_id, n)  == 0)
			{
				found = &this->m_drills.GetCurrentMsg();
				break;
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	return found;
}



void SurfDoc::WellsSaveToDB()
{
	if (this->Get_ID_OBJ() == -1)
	{
		AfxMessageBox("Not Saved!!!\nID_OBJ == -1");
		return;
	}
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().WellsSaveToDB();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}



void SurfDoc::TestSvai()
{
	printf("SurfDoc::TestSvai()\n");
	int index = AddKarotazh("TestSvai", RGBA(0,0,255,125));

	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	index = AddKarotazh("RA", RGBA(0,0,255,125));

	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	index = AddKarotazh("fuh", RGBA(0,0,255,125));

	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().TestSvai();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}



void SurfDoc::DetermineDeformationModul()
{
	printf("SurfDoc::DetermineDeformationModul()\n");
	int index = AddKarotazh(DEFORMATION_MODUL_KAR_NAME, RGBA(0,0,255,125));

	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().DetermineDeformationModul();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::DeterminePesokGlinaFromPCK()
{
	printf("SurfDoc::DeterminePesokGlinaFromPCK()\n");

	wells_draw_list_item * wdli_issand = NULL;
	wdli_issand = AddWellsDraw(WellElement::type::isSand_podoshva, true, 50.f, true, wells_draw_list_item::draw_mode_2d::both);

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().DeterminePesokGlinaFromPCK(wdli_issand);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
#include "../../array/src/spline3.h"
#include "../../winplot/src/winplot.h"
void SurfDoc::DetermineUdelnoeSceplenie()
{
#if 0
	vector<vector<double> > xx(2), yy(2);



	ap::real_1d_array x;
	ap::real_1d_array y;

	int n = 6;
		

	if (n < 1) return;

	x.setbounds(0, n);
	y.setbounds(0, n);
	
	double vqs[] = {1.5, 3, 5, 8, 15, 27.5, 50};
	double vc[] = {0.0005, 0.001, 0.002, 0.003, 0.004, 0.005, 0.006};
//double vc[] = {28, 30, 32, 34, 36, 37, 38};//vfi
	for (size_t i = 0; i < 7; i++)
	{
		x(i) = vqs[i];
		y(i) = vc[i];
		xx[0].push_back(x(i));
		yy[0].push_back(y(i));

		printf("x(%u) = %f y(%u) = %f\n", i, x(i), i, y(i));
	}

#if 0
	int diffn = 2;
	double boundl = 0.0;
	double boundr = 0.0;
#else
	int diffn = 1;
	double boundl = (y(1) - y(0)) / (x(1) - x(0));
	double boundr = (y(n) - y(n-1)) / (x(n) - x(n-1));
#endif
	ap::real_2d_array ctbl;
	spline3buildtable(n,diffn,x,y,boundl,boundr,ctbl);
	
	
	for (double qs = 0; qs <= 100; qs += 0.1)
	{

			double c = spline3interpolate(n, ctbl, qs);


			xx[1].push_back(qs);
			yy[1].push_back(c);

	}
	WinPlot(xx,yy);

	return;
#else
	printf("SurfDoc::DetermineUdelnoeSceplenie()\n");
	int index = AddKarotazh(UDELNOE_SCEPLENIE_KAR_NAME, RGBA(0,0,255,125));

	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().DetermineUdelnoeSceplenie();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
#endif
}
void SurfDoc::DetermineUdolVnutrennegoTrenia()
{
	printf("SurfDoc::DetermineUdolVnutrennegoTrenia()\n");
	int index = AddKarotazh(UGOL_VNUTRENNEGO_TRENIA_KAR_NAME, RGBA(0,0,255,125));
	
	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().DetermineUdolVnutrennegoTrenia();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}

void SurfDoc::TestPesokOrGlina()
{
	printf("SurfDoc::TestPesokOrGlina()\n");
	int index = AddKarotazh(TEST_PESOK_OR_GLINA_KAR_NAME, RGBA(255,125,0,125));

	Well_3D::karotazh_list[index].vmin = DBL_MAX;
	Well_3D::karotazh_list[index].vmax = -DBL_MAX;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().TestPesokOrGlina();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}

void SurfDoc::TestDublicateWells()
{
	printf("SurfDoc::TestDublicateWells()\n");

	int nw = 0;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			nw++;
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	if (!nw)
		return;

	Well_3D ** wells = 
		(Well_3D **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		nw * sizeof (Well_3D*));
	int iw = 0;
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			wells[iw++] = &this->m_drills.GetCurrentMsg();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	for (int iw1 = 0; iw1 < nw; iw1++)
	{
		for (int iw2 = iw1+1; iw2 < nw; iw2++)
		{
			if (strcmp(wells[iw1]->GetIDString(), wells[iw2]->GetIDString()) == 0)
			{
				printf("Dublicate wells # %d and # %d\t\t\"%s\" and \"%s\"\n", iw1, iw2, wells[iw1]->GetIDString(), wells[iw2]->GetIDString());
			}	
			CPoint3 u1,u2;
			if (wells[iw1]->GetUstje(u1) && wells[iw2]->GetUstje(u2))
			{
				if (u1.x == u2.x && u1.y == u2.y)
				{
					printf("Dublicate wells coordinate # %d and # %d\t\"%s\" and \"%s\"\t[x = %f y = %f]", iw1, iw2, wells[iw1]->GetIDString(), wells[iw2]->GetIDString(), u1.x, u1.y);
				}
			}
		}
	}
	HeapFree( GetProcessHeap(), 0, wells );
}
int SurfDoc::ParseZondInputFileLine(char* szBuff, int type_line, bool starting_parsing, int &i_point, int &n_zond_points, vector<string> & zond_points_names, int &i_glubina)
{
	static int i_zond_point = 0;

	//printf("ParseZondFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);
	//printf(szBuff);
	switch(type_line)
	{
	case 1:
		{
			//name of object
			this->m_laboratory.object_name = szBuff;
			return 1;
		}
		break;
	case 2:
		{
			//  archive number
			this->m_laboratory.id_obj = atoi(szBuff);
			return 1;
		}
		break;
	case 3:
		{
			printf(szBuff);
			//12 1 1024 1016 1023 1008 1001 1002 1003 1004 1005 1007 1015 1020
			int delim = ' ';
			// разделитель пробел
			// количество точек зондирования (<= 100)
			// признак печати графика 1- печатать график, 2 - не печатать
			// номера точек зондирования (целые числа) занимают несколько строк в зависимости от их количества
			char * p = NULL;
			if (starting_parsing)
			{
				n_zond_points = atoi(szBuff);
				printf("n_zond_points = %d\n",	n_zond_points);

				p = strchr(szBuff, delim); 
				if(p)
				{
					int to_print_grafik = atoi(p);
					printf("to_print_grafik = %d\n",	to_print_grafik);
				}
				i_zond_point = 0;
			}	
			else
				p = szBuff;
			for (; i_zond_point < n_zond_points; i_zond_point++)
			{
				//if(p)printf("strlen(p) = %d p = \"%s\"\n", strlen(p), p);
				if(p && strlen(p) > 2)
				{
					p = strchr(++p, delim); 
					if(p && strlen(p) > 2)
					{
						int n_tochka = atoi(p);
						char * p2 = strchr(p+1, delim); 
						if (!p2) p2 = strchr(p+1, '\n');
						char tmp[128];
						if (p2)
						{
							strncpy(tmp, p+1, p2-p-1);
							tmp[p2-p-1] = '\0';
						}
						else
						{
							strcpy(tmp, p+1);
							tmp[strlen(p+1)] = '\0';
						}
							
						printf("n_tochka = %d = \"%s\"\n",	n_tochka, tmp);
						zond_points_names.push_back(tmp);

					}
					else
						return 0;
				}
				else
					return 0;
			}
			return 1;
		}
		break;
	case 4:
		{
			int res = 1;
			printf(szBuff);
			//  договор (8 символов)
			// тип установки (8 символов)
			// (допускается 832-5 832-7 979 59)
			// К1 постоянная динамометра для установок С-979, СП-59 или
			// тарировочный коэффициент для РСК для установки С-832
			// К2 постоянная маноометра для установок С-979, СП-59 или
			// тарировочный коэффициент к РСб для установки С-832
			// договор и тип установки набиваются без разделителей
			// После К1 записывается запятая, после К2 - запятая
			// max размер К1 и К2 F5.2, запятая после К1 и К2 ставится, если 
			// число занимает менее 5 знаков

			char tmp[9];
			strncpy(tmp, szBuff, 8);
			tmp[8] = '\0';
			printf("dogovor = \"%s\"\n", tmp);

			this->m_laboratory.contract = tmp;

			strncpy(tmp, szBuff+8, 8);
			tmp[8] = '\0';
			printf("ustanovka = \"%s\"\n", tmp);

			string ust_name = tmp;


			if (strncmp(tmp, "832-7", 5) == 0)
				res = 2;
			if (strncmp(tmp, "832-5", 5) == 0)
				printf ("pika-5!!!\n");

			char * p = szBuff + 16;

			double K1 = atof(p);
			p = strchr(p, ',');
			if (p)
			{
				double K2 = atof(p+1);

				// только что загружно имя установки
				// передаём его в скважины
				for (vector<string>::iterator it = zond_points_names.begin();
					it != zond_points_names.end(); it++)
				{
					Well_3D * pwell = this->FindWell((*it).c_str());
					if(pwell)
					{
						pwell->m_stat_zond.data2.ust_name = ust_name;
						pwell->m_stat_zond.data2.Kg = K1;
						pwell->m_stat_zond.data2.Kf = K2;
						pwell->m_stat_zond.data2.ParseUstName();
						pwell->m_stat_zond.data2_filled = true;
						pwell->m_stat_zond.data1_filled = true;
					}
					else
					{
						char err[1024];
						sprintf(err, "Well \"%s\" not found", (*it).c_str());
						MessageBox(0,err, "ReadZondInputFile", 0);
						return 0;
					}
				}
			}

			return res;
		}
		break;
	case 5:
		{
			// разделитель пробел
			// К3 "место нуля" для каждой точки зондирования для установок 
			// С-979, СП-59 или для установок С-832 : значение 5 или 7
			return 1;
		}
		break;
	case 6:
		{
			int delim = ' ';
			// разделитель пробел
			// К4 ростверк в метрах для каждой точки зондирования
			// (должен быть кратен 0.2м)
			char * p = szBuff;
			for (vector<string>::iterator it = zond_points_names.begin();
				it != zond_points_names.end(); it++)
			{
				double rostverk = 0.0;
				if(p)
				{
					rostverk = atof(p);
					p = strchr(++p, delim); 
				}
				else
					return 0;

				Well_3D * pwell = this->FindWell((*it).c_str());
				if(pwell)
				{
					pwell->m_palja.data2.rostverk = rostverk;
					CPoint3 ustje;
					if (pwell->GetUstje(ustje))
					{
						pwell->m_palja.data2.pz = ustje.z - rostverk;
						pwell->m_palja.data1_filled = true;
						//pwell->m_palja.data2_filled = true;
					}
				}
				else
				{
					char err[1024];
					sprintf(err, "Well \"%s\" not found", (*it).c_str());
					MessageBox(0,err, "ReadZondInputFile", 0);
					return 0;
				}
			}


			return 1;
		}
		break;
	case 7:
		{
			int delim = ' ';
			// разделитель пробел
			// начальная глубина для каждой точки зондирования
			// (должна быть кратна 0.2)
			char * p = szBuff;
			for (vector<string>::iterator it = zond_points_names.begin();
				it != zond_points_names.end(); it++)
			{
				double begin_zond_glyb = 0.0;
				if(p)
				{
					begin_zond_glyb = atof(p);
					p = strchr(++p, delim); 
				}
				else
					return 0;

				Well_3D * pwell = this->FindWell((*it).c_str());
				if(pwell)
				{
					pwell->m_stat_zond.data2.nach_glyb = begin_zond_glyb;
					CPoint3 ustje;
					if (pwell->GetUstje(ustje))
					{
					}
				}
				else
				{
					char err[1024];
					sprintf(err, "Well \"%s\" not found", (*it).c_str());
					MessageBox(0,err, "ReadZondInputFile", 0);
					return 0;
				}
			}


			return 1;
		}
		break;
	case 8:
		{
			int delim = ' ';
			// разделитель пробел
			// только для С-832 (пика 7)
			// К5 "место нуля" при расчёте РСК для каждой точки 

			//  589.2498003. 43131-01 90 01 стр. 227
			char * p = szBuff;
			for (vector<string>::iterator it = zond_points_names.begin();
				it != zond_points_names.end(); it++)
			{
				double Bg = 0.0;
				if(p)
				{
					Bg = atof(p);
					p = strchr(++p, delim); 
				}
				else
					return 0;

				Well_3D * pwell = this->FindWell((*it).c_str());
				if(pwell)
				{
					pwell->m_stat_zond.data2.Bg = Bg;
				}
				else
				{
					char err[1024];
					sprintf(err, "Well \"%s\" not found", (*it).c_str());
					MessageBox(0,err, "ReadZondInputFile", 0);
					return 0;
				}
			}
			return 1;
		}
		break;
	case 9:
		{
			int delim = ' ';
			// разделитель пробел
			// только для С-832 (пика 7)
			// К6 "место нуля" при расчёте РСБ для каждой точки 
			char * p = szBuff;
			for (vector<string>::iterator it = zond_points_names.begin();
				it != zond_points_names.end(); it++)
			{
				double Bf = 0.0;
				if(p)
				{
					Bf = atof(p);
					p = strchr(++p, delim); 
				}
				else
					return 0;

				Well_3D * pwell = this->FindWell((*it).c_str());
				if(pwell)
				{
					pwell->m_stat_zond.data2.Bf = Bf;
				}
				else
				{
					char err[1024];
					sprintf(err, "Well \"%s\" not found", (*it).c_str());
					MessageBox(0,err, "ReadZondInputFile", 0);
					return 0;
				}
			}
			return 1;
		}
		break;
	case 10:
		{
			printf(szBuff);
			// последующие строки для каждой точки разделитель пробел
			// показания динамометра и манометра для каждого шага (шаг постоянный 0,2м) 
			// при этом показание динамометра должно быть целым числом
			// Это можно делать с помощью коэффициента К1, а манометра с точкой
			// глубина не вводится, предполагается, что показания начинаются с глубины 0,2 м
			// с шагом 0,2
			// но не более чем до 25м (40м)
			//  признак конца данных по скважине два нуля
			int delim = ' ';
			char * p = szBuff;

			if (starting_parsing)
			{
				i_glubina = 0;
			}	

			while(true)
			{
				//if(p)printf("strlen(p) = %d p = \"%s\"\n", strlen(p), p);
				if(p && strlen(p) > 2)
				{
					int dynamometr = atoi(p);

					p = strchr(++p, delim); 
					if(p && strlen(p) > 2)
					{
						double manometr = atof(p);

						p = strchr(++p, delim);

						double glubina = i_glubina * 0.2;

						printf("glubina = %f\tdynamometr = %d\tmanometr = %f\n", glubina, dynamometr, manometr);
						
						Well_3D * pwell = this->FindWell(zond_points_names[i_point].c_str());
						if(pwell)
						{
							StatZondData1 data;
							data.npp = i_glubina + 1;//начиная с 1
							data.h = pwell->m_stat_zond.data2.nach_glyb + glubina;
							data.dh = i_glubina ? 0.2 : 0.0;
							data.typgr = 0;
							data.q0 = 0.1 * dynamometr;// перевод из тс/м2
							data.f0 = 10.0 * manometr;// перевод из тс/м2
							data.fsr = 0.5 * (pwell->m_stat_zond.data1.size() ? pwell->m_stat_zond.data1.back().f0 + data.f0: 0.0);
							data.bStat = 1;
							pwell->m_stat_zond.Add(data);
							pwell->m_stat_zond.data2.glyb = data.h;
						}
						else
						{
							char err[1024];
							sprintf(err, "Well \"%s\" not found", zond_points_names[i_point].c_str());
							MessageBox(0,err, "ReadZondInputFile", 0);
							return 0;
						}

						i_glubina++;

						if (dynamometr == 0 && manometr == 0.0)
							return 1;
					}
					else
						return 0;
				}
				else
					return 0;
			}
		}
		break;
	case 11:
		{
			printf(szBuff);
			// глубины подошв песчаных и пылевато-глиистых грунтов
			// обязательно на первом месте подошва песчаного грунта
			// если его нет, набивается начальная глубина, если начальная глубина 
			// 0 набивать 0. (с точкой)
			int delim = ' ';
			char * p = szBuff;

			double current_glubina = 0.0;
			
			int n = 1;
			int nn = 1;

			while(true)
			{
				//if(p)printf("strlen(p) = %d p = \"%s\"\n", strlen(p), p);
				if(p && strlen(p) > 2)
				{
					double glubina_podoshvy = atof(p);
					bool pesok = (bool)((n%2) != 0);
					
					const char * pes = "pesok\0";
					const char * glin = "glina\0";
					printf("glubina_podoshvy = %f of %s grunt\n", glubina_podoshvy, pesok ? pes : glin);
	
					/*if (current_well_to_add_karotazhy_from_zond)
					{
						current_well_to_add_karotazhy_from_zond->PutPesokOrGlinaPodosnva(pesok, glubina_podoshvy);
					}*/

					Well_3D * pwell = this->FindWell(zond_points_names[i_point].c_str());
					if(pwell)
					{
						//pwell->PutPesokOrGlinaPodosnva(pesok, glubina_podoshvy);

						if (glubina_podoshvy > current_glubina )
						{
							for (vector<StatZondData1>::iterator it = pwell->m_stat_zond.data1.begin();
								it != pwell->m_stat_zond.data1.end(); it++)
							{
								if (nn == 1)
								{
									if ( (*it).h >= current_glubina && (*it).h <= glubina_podoshvy)
									{
										if (pesok)
											(*it).typgr = 1;
										else
											(*it).typgr = 2;
									}
								}
								else
								{
									if ( (*it).h > current_glubina && (*it).h <= glubina_podoshvy)
									{
										if (pesok)
											(*it).typgr = 1;
										else
											(*it).typgr = 2;
									}
								}
							}
							nn++;
						}
						current_glubina = glubina_podoshvy;
					}
					else
					{
						char err[1024];
						sprintf(err, "Well \"%s\" not found", zond_points_names[i_point].c_str());
						MessageBox(0,err, "ReadZondInputFile", 0);
						return 0;
					}

					p = strchr(++p, delim); 
					n++;
				}
				else
					break;
			}
			return 1;
		}
		break;
	default:
		return 3;
	}
	return -1;
}

bool SurfDoc::ReadZondInputFile(char *file)
{
	printf("SurfDoc::ReadZondInputFile(\"%s\")\n",file);

	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line
	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"SurfDoc::ReadZondInputFile()", 0);
		return false;
	}

	FILE *stream;
	if ((stream = fopen(file,"rt")) == NULL)
	{
		char errstr[2048];
		sprintf(errstr, "SurfDoc::ReadZondInputFile:fopen(%s)", file);
		ErrorExit(errstr);
		return false;
	}

	char * ch;

	int type_line = 1;
	bool starting_parsing = true;
	bool propusk_8_9_strok = true;

	int n_zond_points = 0;
	int i_glubina = 0;
	int i_point = 0;
	vector<string> zond_points_names;
	zond_points_names.clear();


	while (!feof(stream))
	{		
		ch = fgets(szBuff,n,stream);		
		
		if( ch != NULL && strlen(szBuff) > 1)
		{
			int res = ParseZondInputFileLine(szBuff, type_line, starting_parsing, i_point, n_zond_points, zond_points_names, i_glubina);

			if (res == -1 || res == 1 || res == 2)
			{
				starting_parsing = true;

				type_line++;

				if(propusk_8_9_strok && type_line == 8)
				{
					type_line = 10;
				}
				if (type_line == 12)
				{
					printf("i_point = %d\n", i_point );
					i_point++;

					if (i_point < n_zond_points)
						type_line = 10;
					else
						break;
				}
				if (res == 2)
					propusk_8_9_strok = false;
			}
			else if (res == 0)
			{
				// continue parsing
				starting_parsing = false;
			}
			else if (res == 3)
			{
				break;
			}
		}
		else 
		{
			break;
		}
		printf("type_line = %d\n", type_line);
	}

	//printf("SurfDoc::ReadZondFile() end\n");

	fclose(stream);
	return true;
}



int SurfDoc::ParseZondOutputFileLine(char* szBuff, int type_line)
{
	//printf("ParseZondFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);
	//printf(szBuff);
	switch(type_line)
	{
	case 1:
		{
				//int rez = sscanf(szBuff,"%lf\t%lf\t%lf", &X, &Y, &Z);
			char dogovor[32];
			char tochka[32];
			char ustanovka[32];
			double K1,K2;
			int rez = sscanf(szBuff,(const char *)"    результаты обработки статического зондирования договор %s точка %s установка %s K1= %lf K2= %lf", 
				dogovor, tochka, ustanovka, &K1, &K2);
			//printf("rez = %d\n", rez);
			if (rez == 5 && rez != EOF)
			{
				printf("dogovor = %s\n", dogovor);
				printf("tochka = %s\n", tochka);
				printf("ustanovka = %s\n", ustanovka);
				printf("K1 = %f\n", K1);
				printf("K2 = %f\n", K2);
				return 1;
			}
			else
			{
				char * f = strstr(szBuff,"точка");
				if (f)
				{
					printf(" f = %s\n",f);
					printf(f);
					return 1;
				}
				else
				{
					//printf(szBuff + 74);
					strncpy(tochka, szBuff + 74, 8); tochka[8] = '\0';
					char * p = strchr(tochka, ' ');
					if (p) *p = '\0';
					printf("tochka = \"%s\"\n", tochka);
					if (strlen(tochka) == 0)
						return 3;
					
					current_well_to_add_karotazhy_from_zond = this->FindWell(tochka);

					//printf("current_well_to_add_karotazhy_from_zond = %x\n", current_well_to_add_karotazhy_from_zond);

					if(!current_well_to_add_karotazhy_from_zond)
					{
						char str[4095];
						sprintf(str, "tochka = \"%s\" well not found", tochka);
											
						MessageBox(0,str,"SurfDoc::ParseZondFileLine",0);
					}




					return 1;
				}
			}
		}
		break;
	case 2:
		{
			  //"  подошвы песчаных и пыл.-глинистых грунтов(м)"
			// глубины подошв песчаных и пылевато-глинистых грунтов
			// обязательно на первом месте подошва песчаного грунта,
			// если его (песчаного грунта) нет, набивается начальная глубина
			// если начальная глубина 0, набивать 0. (с точкой)
			return -1;
		}
		break;
	case 3:
		{
			printf(szBuff);
			//       .0     2.4     2.8     5.4     6.0    11.4    14.0
			//положение конца чисел 9 17 25 33 41
			// 1+8 = 9
			// 9+8 = 17
			//17+8 = 25
			//25+8 = 33
			//33+8 = 41
			char tmp[9];
			int n = 1;
			while ((int)strlen(szBuff) >= 1 + 8*n)
			{
				strncpy(tmp, szBuff + 1 + 8*(n-1), 8);
				tmp[8] = '\0';
				double glubina_podoshvy = atof(tmp);
				bool pesok = (bool)((n%2) != 0);
				/*
				const char * pes = "pesok\0";
				const char * glin = "glina\0";
				printf("tmp = %s\tglubina_podoshvy = %f of %s grunt\n", tmp, glubina_podoshvy, pesok ? pes : glin);
*/
				if (current_well_to_add_karotazhy_from_zond)
				{
					current_well_to_add_karotazhy_from_zond->PutPesokOrGlinaPodosnvaOld(pesok, glubina_podoshvy);
				}
				n++;
			}
			return 1;
		}
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		{
			/*
 ------------------------------------------------------------------------------------------------------------------------
 :глуб :показ:показ:     :     :         график сопротивления грунта по боковой поверхности рсб(Tс/M2)            :рсб/ :
 :точки:дн-ра:мн-ра: рск : рсб :   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30  32  34  36  38  40  :рск  :
 :набл :     :     :     :     :---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+--:     :
 : (м) :     :     :Tс/м2:тс/м2:           график удельного сопротивления грунта рск(Tс/м2)                       :     :
 :     :     :     :     :     :  100 200 300 400 500 600 700 800 90010001100120013001400150016001700180019002000 :     :
 :-----:-----:-----:-----:-----:---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+--:-----:
			*/
			
			return -1;
		}
		break;
	case 11:
		{
			// :   .2     1    .0   10.    .1 .                                                                                    .010
			 
			//                               ...график рск ,***график рсб,ооо-общие

			char * f = strstr(szBuff,"...");
			if (!f)
			{
				printf(szBuff);

				char sglubina[32];
				char sdinamometr[32];
				char smanometr[32];
				char spck[32];
				char spcb[32];

				strncpy(sglubina,		szBuff + 2,  5);	sglubina[5] = '\0';
				strncpy(sdinamometr,	szBuff + 8,  5);	sdinamometr[5] = '\0';
				strncpy(smanometr,		szBuff + 14, 5);	smanometr[5] = '\0';
				strncpy(spck,			szBuff + 20, 5);	spck[5] = '\0';
				strncpy(spcb,			szBuff + 26, 5);	spcb[5] = '\0';

				printf("sglubina = \"%s\"\n", sglubina);
				printf("sdinamometr = \"%s\"\n", sdinamometr);
				printf("smanometr = \"%s\"\n", smanometr);
				printf("spck = \"%s\"\n", spck);
				printf("spcb = \"%s\"\n", spcb);

				double glubina			= atof(sglubina);
				double dinamometr		= atof(sdinamometr);
				double manometr			= atof(smanometr);
				double pck				= atof(spck);
				double pcb				= atof(spcb);

#define USE_DB_PSK_EDINICY 1

#if USE_DB_PSK_EDINICY
				pck /= 100; // переводим в МПА !!!
#endif
				printf("glubina = %f dinamometr = %f manometr = %f pck = %f pcb = %f\n", glubina, dinamometr, manometr, pck, pcb);

				int kar_index;

				if (current_well_to_add_karotazhy_from_zond)
				{
					kar_index = Well_3D::GetKarotazhIndex(DYNAMOMETR_KAR_NAME);
					current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, dinamometr, glubina);

					kar_index = Well_3D::GetKarotazhIndex(MANOMETR_KAR_NAME);
					current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, manometr, glubina);

					kar_index = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
					current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, pck, glubina);

					kar_index = Well_3D::GetKarotazhIndex(PCB_KAR_NAME);
					current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, pcb, glubina);

					kar_index = Well_3D::GetKarotazhIndex(PCB_PCK_KAR_NAME);
					current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, pcb/pck, glubina);

				}
				else
				{
					printf("!current_well_to_add_karotazhy_from_zond\n");
				}

				return 0;
			}
			else
			{
				return 1;
			}
		}
		break;
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		{
			/*
 договOр 151/07   установка 832-5   
  точка зондирования 1024    ростверк      .0
  несущая способность свай  (тс)  
 oт начальной глубины зондирования       
 ----------------------------------------------
 :глуб:          сечение свай                 :
 : M  : 20*20 : 25*25 : 30*30 : 35*35 : 40*40 :
 ----------------------------------------------
 */
			return -1;
		}
		break;
	case 20:
		{
			// :  1.:   8.92  14.81   23.16    32.64   42.51:
				
			int kar_index;

//			if (current_well_to_add_karotazhy_from_zond)
			{
				
				char sglubina[32];
				strncpy(sglubina,	szBuff + 2,  4);	sglubina[4] = '\0';
				double glubina			= atof(sglubina);
				
//printf("glubina = %f\n", glubina);

				if (strlen(szBuff) > 7+7-2)
				{
					char s20x20[32];
					strncpy(s20x20,		szBuff + 7,  7);	s20x20[7] = '\0';
					double v = atof(s20x20);
//printf("20x20 = %f\n", v);
					kar_index = Well_3D::GetKarotazhIndex(SVAI_20_20_KAR_NAME);
					if (current_well_to_add_karotazhy_from_zond) current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, v, glubina);
				}

				if (strlen(szBuff) > 15+7-2)
				{
					char s25x25[32];
					strncpy(s25x25,		szBuff + 15, 7);	s25x25[7] = '\0';
					double v = atof(s25x25);
//printf("25x25 = %f\n", v);
					kar_index = Well_3D::GetKarotazhIndex(SVAI_25_25_KAR_NAME);
					if (current_well_to_add_karotazhy_from_zond) current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, v, glubina);
				}

				if (strlen(szBuff) > 23+7-2)
				{
					char s30x30[32];
					strncpy(s30x30,		szBuff + 23, 7);	s30x30[7] = '\0';
					double v = atof(s30x30);
//printf("30x30 = %f\n", v);
					kar_index = Well_3D::GetKarotazhIndex(SVAI_30_30_KAR_NAME);
					if (current_well_to_add_karotazhy_from_zond) current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, v, glubina);
				}

				if (strlen(szBuff) > 31+7-2)
				{
					char s35x35[32];
					strncpy(s35x35,		szBuff + 31, 7);	s35x35[7] = '\0';
					double v = atof(s35x35);
//printf("35x35 = %f\n", v);
					kar_index = Well_3D::GetKarotazhIndex(SVAI_35_35_KAR_NAME);
					if (current_well_to_add_karotazhy_from_zond) current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, v, glubina);
				}

				if (strlen(szBuff) > 39+7-2)
				{
					char s40x40[32];
					strncpy(s40x40,		szBuff + 39, 7);	s40x40[7] = '\0';
					double v = atof(s40x40);
//printf("40x40 = %f\n", v);
					kar_index = Well_3D::GetKarotazhIndex(SVAI_40_40_KAR_NAME);
					if (current_well_to_add_karotazhy_from_zond) current_well_to_add_karotazhy_from_zond->AddPointToKarotazh(kar_index, v, glubina);
				}
			}
			return 0;

		}
		break;
	}
	return -1;
}

bool SurfDoc::ReadZondOutputFile(char *file)
{
	current_well_to_add_karotazhy_from_zond = NULL;


	{
		AddKarotazh(DYNAMOMETR_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(MANOMETR_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(PCK_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(PCB_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(PCB_PCK_KAR_NAME, RGBA(0,0,255,125));

		AddKarotazh(SVAI_20_20_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_25_25_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_30_30_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_35_35_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_40_40_KAR_NAME, RGBA(0,0,255,125));

	}

	printf("SurfDoc::ReadZondFile(\"%s\")\n",file);

	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line
	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"importExcelCommonFileParam()", 0);
		return false;
	}

	FILE *stream;
	if ((stream = fopen(file,"rt")) == NULL)
	{
		char errstr[2048];
		sprintf(errstr, "SurfDoc::ReadZondFile:fopen(%s)", file);
		ErrorExit(errstr);
		return false;
	}

	char * ch;
//	size_t bytes_line;
	
	int type_line = 1;

	while (!feof(stream))
	{
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			int res = ParseZondOutputFileLine(szBuff, type_line);
			if (res == -1 || res == 1 || res == 2)
				type_line++;
			else if (res == 0)
			{
			}
			else if (res == 3)
			{
				break;
			}
		}
		else 
		{
			//printf("strlen(szBuff) = %u, type_line = %d\n", strlen(szBuff), type_line);
			if (strlen(szBuff) <= 1 && type_line == 20)
			type_line = 1;
		}
	}

	//printf("SurfDoc::ReadZondFile() end\n");

	fclose(stream);
	return true;
}


int SurfDoc::ParseZond_CorrectInput_FileLine(char* szBuff, int type_line, bool starting_parsing, int &n_zond_points, int &i_glubina, vector<string> & zond_points_names)
{
	static int i_zond_point = 0;

	//printf("ParseZondFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);
	//printf(szBuff);
	switch(type_line)
	{
	case 1:
		{
			//name of object
			return 1;
		}
		break;
	case 2:
		{
			//  archive number
			return 1;
		}
		break;
	case 3:
		{
			printf(szBuff);
			//12 1 1024 1016 1023 1008 1001 1002 1003 1004 1005 1007 1015 1020
			int delim = ' ';
			// разделитель пробел
			// количество точек зондирования (<= 100)
			// признак печати графика 1- печатать график, 2 - не печатать
			// номера точек зондирования (целые числа) занимают несколько строк в зависимости от их количества
			char * p = NULL;
			if (starting_parsing)
			{
				n_zond_points = atoi(szBuff);
				printf("n_zond_points = %d\n",	n_zond_points);

				p = strchr(szBuff, delim); 
				if(p)
				{
					int to_print_grafik = atoi(p);
					printf("to_print_grafik = %d\n",	to_print_grafik);
				}
				i_zond_point = 0;
			}	
			else
				p = szBuff;
			for (; i_zond_point < n_zond_points; i_zond_point++)
			{
				//if(p)printf("strlen(p) = %d p = \"%s\"\n", strlen(p), p);
				if(p && strlen(p) > 2)
				{
					p = strchr(++p, delim); 
					if(p && strlen(p) > 2)
					{
						int n_tochka = atoi(p);
						char * p2 = strchr(p+1, delim); 
						if (!p2) p2 = strchr(p+1, '\n');
						char tmp[128];
						if (p2)
						{
							strncpy(tmp, p+1, p2-p-1);
							tmp[p2-p-1] = '\0';
						}
						else
						{
							strcpy(tmp, p+1);
							tmp[strlen(p+1)] = '\0';
						}
							
						printf("n_tochka = %d = \"%s\"\n",	n_tochka, tmp);
						zond_points_names.push_back(tmp);

					}
					else
						return 0;
				}
				else
					return 0;
			}
			return 1;
		}
		break;
	case 4:
		{
			printf(szBuff);
			//  договор (8 символов)
			// тип установки (8 символов)
			// (допускается 832-5 832-7 979 59)
			// К1 постоянная динамометра для установок С-979, СП-59 или
			// тарировочный коэффициент для РСК для установки С-832
			// К2 постоянная маноометра для установок С-979, СП-59 или
			// тарировочный коэффициент к РСб для установки С-832
			// договор и тип установки набиваются без разделителей
			// После К1 записывается запятая, после К2 - запятая
			// max размер К1 и К2 F5.2, запятая после К1 и К2 ставится, если 
			// число занимает менее 5 знаков

			char tmp[9];
			strncpy(tmp, szBuff, 8);
			tmp[8] = '\0';
			printf("dogovor = \"%s\"\n", tmp);

			strncpy(tmp, szBuff+8, 8);
			tmp[8] = '\0';
			printf("ustanovka = \"%s\"\n", tmp);

			if (strncmp(tmp, "832-7", 5) == 0)
				return 2;
			if (strncmp(tmp, "832-5", 5) == 0)
				printf ("pika-5!!!\n");
			return 1;
		}
		break;
	case 5:
		{
			// разделитель пробел
			// К3 "место нуля" для каждой точки зондирования для установок 
			// С-979, СП-59 или для установок С-832 : значение 5 или 7
			return 1;
		}
		break;
	case 6:
		{
			// разделитель пробел
			// К4 ростверк в метрах для каждой точки зондирования
			// (должен быть кратен 0.2м)
			return 1;
		}
		break;
	case 7:
		{
			// разделитель пробел
			// начальная глубина для каждой точки зондирования
			// (должна быть кратна 0.2)
			return 1;
		}
		break;
	case 8:
		{
			// разделитель пробел
			// только для С-832 (пика 7)
			// К5 "место нуля" при расчёте РСК для каждой точки 

			//  589.2498003. 43131-01 90 01 стр. 227
			return 1;
		}
		break;
	case 9:
		{
			// разделитель пробел
			// только для С-832 (пика 7)
			// К6 "место нуля" при расчёте РСБ для каждой точки 
			return 1;
		}
		break;
	case 10:
		{
			printf(szBuff);
			// последующие строки для каждой точки разделитель пробел
			// показания динамометра и манометра для каждого шага (шаг постоянный 0,2м) 
			// при этом показание динамометра должно быть целым числом
			// Это можно делать с помощью коэффициента К1, а манометра с точкой
			// глубина не вводится, предполагается, что показания начинаются с глубины 0,2 м
			// с шагом 0,2
			// но не более чем до 25м (40м)
			//  признак конца данных по скважине два нуля
			int delim = ' ';
			char * p = szBuff;

			if (starting_parsing)
			{
				i_glubina = 0;
			}	

			while(true)
			{
				//if(p)printf("strlen(p) = %d p = \"%s\"\n", strlen(p), p);
				if(p && strlen(p) > 2)
				{
					int dynamometr = atoi(p);

					p = strchr(++p, delim); 
					if(p && strlen(p) > 2)
					{
						double manometr = atof(p);

						p = strchr(++p, delim);
						i_glubina++;

						double glubina = i_glubina * 0.2;

						printf("glubina = %f\tdynamometr = %d\tmanometr = %f\n", glubina, dynamometr, manometr);

						if (dynamometr == 0 && manometr == 0.0)
							return 1;
					}
					else
						return 0;
				}
				else
					return 0;
			}
		}
		break;
	case 11:
		{
			printf(szBuff);
			// глубины подошв песчаных и пылевато-глиистых грунтов
			// обязательно на первом месте подошва песчаного грунта
			// если его нет, набивается начальная глубина, если начальная глубина 
			// 0 набивать 0. (с точкой)
			int delim = ' ';
			char * p = szBuff;
			
			int n = 1;

			while(true)
			{
				//if(p)printf("strlen(p) = %d p = \"%s\"\n", strlen(p), p);
				if(p && strlen(p) > 2)
				{
					double glubina_podoshvy = atof(p);
					bool pesok = (bool)((n%2) != 0);
					
					const char * pes = "pesok\0";
					const char * glin = "glina\0";
					printf("glubina_podoshvy = %f of %s grunt\n", glubina_podoshvy, pesok ? pes : glin);
	
					/*if (current_well_to_add_karotazhy_from_zond)
					{
						current_well_to_add_karotazhy_from_zond->PutPesokOrGlinaPodosnva(pesok, glubina_podoshvy);
					}*/
					p = strchr(++p, delim); 
					n++;
				}
				else
					break;
			}
			return 1;
		}
		break;
	default:
		return 3;
	}
	return -1;
}

bool SurfDoc::ReadZond_CorrectInput_File(char *file)
{
	printf("SurfDoc::ReadZondInputFile(\"%s\")\n",file);

	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line
	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"importExcelCommonFileParam()", 0);
		return false;
	}

	FILE *stream;
	if ((stream = fopen(file,"rt")) == NULL)
	{
		char errstr[2048];
		sprintf(errstr, "SurfDoc::ReadZondInputFile:fopen(%s)", file);
		ErrorExit(errstr);
		return false;
	}

	char out_file[4098];
	sprintf(out_file, "%s.crtd\0", file);
	printf("out_file = \"%s\"\n", out_file);

	FILE * out;
	if ((out = fopen(out_file,"wt")) == NULL)
	{
		fclose(stream);
		printf("!out\n");

		char errstr[2048];
		sprintf(errstr, "SurfDoc::ReadZondInputFile:fopen(%s)", out_file);
		ErrorExit(errstr);
		return false;
	}

	char * ch;

	int type_line = 1;
	bool starting_parsing = true;
	bool propusk_8_9_strok = true;

	int n_zond_points = 0;
	int i_glubina = 0;
	int n_point = 0;
	vector<string> zond_points_names;
	zond_points_names.clear();

	while (!feof(stream))
	{
		
		ch = fgets(szBuff,n,stream);		


		
		if( ch != NULL && strlen(szBuff) > 1)
		{
			if (type_line == 11)
			{				
				Well_3D * pwell = this->FindWell(zond_points_names[n_point].c_str());
				if(pwell)
				{
					pwell->ResetPesokGlinaCheredovanie();
					pwell->WritePesokGlinaCheredovanie(out);
				}
				else
				{
					char err[1024];
					sprintf(err, "Well \"%s\" not found", zond_points_names[n_point].c_str());
					fprintf(out, "%s", szBuff);
					MessageBox(0,err, "ReadZondInputFile", 0);
				}
			}
			else
			{
				fprintf(out, "%s", szBuff);
			}
			int res = ParseZond_CorrectInput_FileLine(szBuff, type_line, starting_parsing, n_zond_points, i_glubina, zond_points_names);

			if (res == -1 || res == 1 || res == 2)
			{
				starting_parsing = true;

				type_line++;

				if(propusk_8_9_strok && type_line == 8)
				{
					type_line = 10;
				}
				if (type_line == 12)
				{
					printf("n_point = %d\n", n_point );
					n_point++;

					if (n_point < n_zond_points)
						type_line = 10;
					else
						break;
				}
				if (res == 2)
					propusk_8_9_strok = false;
			}
			else if (res == 0)
			{
				// continue parsing
				starting_parsing = false;
			}
			else if (res == 3)
			{
				break;
			}
		}
		else 
		{
			break;
		}
		printf("type_line = %d\n", type_line);
	}

	//printf("SurfDoc::ReadZondFile() end\n");

	fclose(stream);
	if(out) fclose(out);
	return true;
}

LabLayer * SurfDoc::AddNewLabLayer(long id_ige, const char * id, const char * layer_number, const char * fn)
{
	//{				
		//3,3,11000,
		//идентификационный номер, номер слоя, схема испытания
		LabLayer * lablayer = new LabLayer(&this->m_laboratory, fn);
		this->m_laboratory.m_layers.push_back(lablayer);

		//p = ParsingLabInputFileLine(p, out); 
		//if (p) 
			this->m_laboratory.m_layers.back()->id_ige = id_ige;
			this->m_laboratory.m_layers.back()->ID = id;
		//printf("m_lablayer->ID = %s\n", m_lablayer->ID.c_str());
		//p = ParsingLabInputFileLine(p, out); 
		//if (p)
			this->m_laboratory.m_layers.back()->layer_number = layer_number;

		//printf("m_lablayer->layer_number = %s\n", m_lablayer->layer_number.c_str());
		//p = ParsingLabInputFileLine(p, out); 
		//if (p)
		{
			this->m_laboratory.m_layers.back()->experiments_scheme = "00001";
			this->m_laboratory.m_layers.back()->ParseExperimentsScheme();
			//m_lablayer->PrintfProperties();
		}
		//return 1;
	//}
#if USE_LAB_LAYER_FRACTIONS
	//{
		{
			LabExperiment * m_lab_experiment = this->m_laboratory.m_layers.back()->AddNewLabExperiment(LabExperiment::type::fractions);
			FractionsLabExperiment * fractions = dynamic_cast<FractionsLabExperiment *>(m_lab_experiment);

			if(fractions)
			{
				//p = ParsingLabInputFileLine(p, out); 
				//if (p) 
					fractions->n_fractions = 10;
				//printf("fractions->n_fractions = %d\n", fractions->n_fractions);
				
				//if (fractions->n_fractions)
				{
					fractions->fractions_diameters = new double[fractions->n_fractions];
					//for (int i = 0; i < fractions->n_fractions; i++)
					{
						//p = ParsingLabInputFileLine(p, out); 
						//if (p) 
							//fractions->fractions_diameters[i] = atof(out);
						//printf("fractions->fractions_diameters[%d] = %f\n", i, fractions->fractions_diameters[i]);
							
						
						fractions->fractions_diameters[0] = 10.;
						fractions->fractions_diameters[1] = 2.;
						fractions->fractions_diameters[2] = 1.;
						fractions->fractions_diameters[3] = 0.5;
						fractions->fractions_diameters[4] = 0.25;
						fractions->fractions_diameters[5] = 0.1;
						fractions->fractions_diameters[6] = 0.05;
						fractions->fractions_diameters[7] = 0.01;
						fractions->fractions_diameters[8] = 0.005;
						fractions->fractions_diameters[9] = 0.005;
					}
				}
			}
		}
	//}
#endif

	return lablayer;
}
LRESULT CALLBACK DlgProcLabExcludedList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void SurfDoc::LabExcludedList(HWND hWndParent)
{
	// modeless dialog
	HANDLE hDialog = LoadResource( hInst,
		FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_LAB_EXCLUDED_LIST),
		RT_DIALOG ) );
	LPVOID lpDialog = LockResource( hDialog );
	HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWndParent,
		(DLGPROC)DlgProcLabExcludedList,
		(LPARAM) this );
	ShowWindow(hDlg, SW_SHOW);
}
void SurfDoc::LabLayerPropertyWindow(HWND hWndParent, long id_ige, long x, long y)
{
	LabLayer * p1 = this->m_laboratory.FindLabLayer(id_ige);
	if (p1)
	{
		this->m_laboratory.SelectLabObject(x, y, p1, hWndParent);
	}
}

void SurfDoc::LabLayerChastnye(long id_ige)
{
	LabLayer * p1 = this->m_laboratory.FindLabLayer(id_ige);
	if (p1)
	{
		p1->Passport_chastnye();
	}
}

void SurfDoc::LabLayerNormatives(int type, long id_ige)
{	
	LabLayer * p1 = this->m_laboratory.FindLabLayer(id_ige);
	if (p1)
	{
		p1->Passport_normatives(type);
	}
}


void SurfDoc::AddNewWellColomn_LaboratoryAnalizes_FromDB(long id_obj, const char * contract, const char * object_name)
{

	lab_errors.clear();

	if (!m_wdli_laboratory)
		m_wdli_laboratory = this->AddWellsDraw(WellElement::type::laboratory_analizes, true, 15.f, false, wells_draw_list_item::draw_mode_2d::both);
	
	
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().AddNewWellColomn_LaboratoryAnalizes();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	m_laboratory.contract = contract;
	m_laboratory.id_obj = id_obj;
	m_laboratory.object_name = object_name;

	for (vector<IGE_Data>::iterator it_ige = this->m_db_ige.data.begin();
		it_ige != this->m_db_ige.data.end(); it_ige++)
	{
		if ((*it_ige).ige_filled && (*it_ige).grunt_filled)
		{
			string ige = (*it_ige).ige.ige;
			char str_id_ige[64];
			sprintf(str_id_ige, "%d", (*it_ige).ige.id_ige);
			long id_ige = (*it_ige).ige.id_ige;
			LabLayer * lab_layer = this->AddNewLabLayer(id_ige, str_id_ige, ige.c_str(), (*it_ige).grunt.nazva_r.c_str());
				//string key = (*it_ige).ige.ige;
			EngineerGeoElement * _ige = this->FindEngineerGeoElement(ige);
			if (_ige)
			{
				_ige->SetLabLayer(lab_layer);
			}
		}
	}	

	this->AddNewLabLayer(-1, "-1", "NO_IGE", "Не определённый ИГЭ");
}


void SurfDoc::AddPrGrunt(long id_obj, long id_kt, const char * kt_name, long kt_idtyp, long id_prob, double depth,
						 long lab_n, long id_kodprob, long id_gr, const char * soil_name, const char * grunt_name,
						 long id_ige)
{
	LabLayer * lab_layer = FindLabLayer(id_kt, depth);

	if(!lab_layer)
	{
		lab_layer = FindLabLayer(id_ige);
		if (!lab_layer)
			lab_layer = FindLabLayer("-1");//"NO_IGE"
	}

	if (lab_layer)
	{
		LabNumber * m_lab_number = lab_layer->AddNewLabNumber();
		if (m_lab_number)
		{
			m_lab_number->AddPrGrunt(id_obj, id_kt, kt_name, kt_idtyp, id_prob, depth,
				lab_n, id_kodprob, id_gr, soil_name, grunt_name, id_ige);
		}
	}
}

LabLayer * SurfDoc::FindLabLayer(long id_kt, double depth)
{
	Well_3D * well = this->FindWell(id_kt);
	if (well)
	{
		if (well->m_db_lito.data_filled)
		{
			for (vector<db_lito_data>::iterator it_lito = well->m_db_lito.data1.begin();
				it_lito != well->m_db_lito.data1.end(); it_lito++)
			{
				if (depth <=(*it_lito).h1 && depth > (*it_lito).h0)
				{

					for (vector<IGE_Data>::iterator it_ige = this->m_db_ige.data.begin();
						it_ige != this->m_db_ige.data.end(); it_ige++)
					{
						if ((*it_ige).ige_filled && (*it_ige).ige.id_ige == (*it_lito).id_ige)
						{
							for (vector<LabLayer *>::iterator it_layer = this->m_laboratory.m_layers.begin();
								it_layer != this->m_laboratory.m_layers.end(); it_layer++)
							{
								char id_ige[64];
								sprintf(id_ige, "%d", (*it_ige).ige.id_ige);
								if ((*it_layer) && !strcmp((*it_layer)->ID.c_str(), id_ige))
								{
									return (*it_layer);
								}
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}
LabLayer * SurfDoc::FindLabLayer(const char * id)
{
	for (vector<LabLayer *>::iterator it_layer = this->m_laboratory.m_layers.begin();
		it_layer != this->m_laboratory.m_layers.end(); it_layer++)
	{
		if ((*it_layer) 
			&& 
			!strcmp((*it_layer)->ID.c_str(), id)
			)
		{
			return (*it_layer);
		}
	}
	return NULL;
}
LabLayer * SurfDoc::FindLabLayer(long id_ige)
{
	for (vector<LabLayer *>::iterator it_layer = this->m_laboratory.m_layers.begin();
		it_layer != this->m_laboratory.m_layers.end(); it_layer++)
	{
		if ((*it_layer) && (*it_layer)->id_ige == id_ige)
		{
			return (*it_layer);
		}
	}
	return NULL;
}
void SurfDoc::OnViewPropertywindowwithPlot() 
{
	HWND hWnd = this->hSurfWnd;
	if (Laboratory::context_with_plot)
	{
		Laboratory::context_with_plot = false;
        
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
	  		ID_LAB_CONTEXTWITHPLOT,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		Laboratory::context_with_plot = true; 
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXTWITHPLOT,
			MF_BYCOMMAND | MF_CHECKED);
	}

	m_laboratory.ReCreateContextWindow();
}

void SurfDoc::OnViewPropertywindowwithResults() 
{
	HWND hWnd = this->hSurfWnd;
	if (LabNumber::context_with_results)
	{
		LabNumber::context_with_results = false;
        
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXTWITHRESULTS,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		LabNumber::context_with_results = true; 
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXTWITHRESULTS,
			MF_BYCOMMAND | MF_CHECKED);
	}
	
	m_laboratory.ReCreateContextWindow();	
}
void SurfDoc::OnViewPropertywindowwithLabnumbertriallist() 
{
	HWND hWnd = this->hSurfWnd;
	if (LabLayer::context_with_lab_number_trial_list)
	{
		LabLayer::context_with_lab_number_trial_list = false;
        
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		LabLayer::context_with_lab_number_trial_list = true; 
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST,
			MF_BYCOMMAND | MF_CHECKED);
	}
	
	m_laboratory.ReCreateContextWindow();
}

void SurfDoc::OnViewPropertywindowwithNormatives() 
{
	HWND hWnd = this->hSurfWnd;
	if (LabLayer::context_with_normatives)
	{
		LabLayer::context_with_normatives = false;
        
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ),
			ID_LAB_CONTEXTWITHNORMATIVES,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		LabLayer::context_with_normatives = true; 
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXTWITHNORMATIVES,
			MF_BYCOMMAND | MF_CHECKED);
	}
	
	m_laboratory.ReCreateContextWindow();	
}

void SurfDoc::OnViewPropertywindowwithCorrelation() 
{
	HWND hWnd = this->hSurfWnd;
	if (LabLayer::context_with_korrelation)
	{
		LabLayer::context_with_korrelation = false;
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ),            
			ID_LAB_CONTEXTWITHKORRELATION,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		LabLayer::context_with_korrelation = true; 
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ),
			ID_LAB_CONTEXTWITHKORRELATION,
			MF_BYCOMMAND | MF_CHECKED);
	}

	m_laboratory.ReCreateContextWindow();
}
void SurfDoc::OnViewPropertywindowwithNormativesbyallexperiences() 
{
	HWND hWnd = this->hSurfWnd;
	if (LabLayer::context_with_normatives_by_all_experiences)
	{
		LabLayer::context_with_normatives_by_all_experiences = false;
        
	  
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		LabLayer::context_with_normatives_by_all_experiences = true; 
		
		CheckMenuItem(GetMenu( ::GetParent( hWnd ) ), 
			ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES,
			MF_BYCOMMAND | MF_CHECKED);
	}

	m_laboratory.ReCreateContextWindow();
}

bool SurfDoc::Get_Laboratory_context_with_plot()
{
	return Laboratory::context_with_plot;
}
bool SurfDoc::Get_LabNumber_context_with_results()
{
	return LabNumber::context_with_results;
}
bool SurfDoc::Get_LabLayer_context_with_lab_number_trial_list()
{
	return LabLayer::context_with_lab_number_trial_list;
}
bool SurfDoc::Get_LabLayer_context_with_normatives()
{
	return LabLayer::context_with_normatives;
}
bool SurfDoc::Get_LabLayer_context_with_korrelation()
{
	return LabLayer::context_with_korrelation;
}
bool SurfDoc::Get_LabLayer_context_with_normatives_by_all_experiences()
{
	return LabLayer::context_with_normatives_by_all_experiences;
}

void SurfDoc::AddProp(
	long id_kt, long id_prob, 
	long id_vyprob, long id_param, const char * param_name, double val, unsigned char bStat
	)
{
	//char lab_number_ID[128]; 
	//sprintf(lab_number_ID, "%ld", lab_n);
	//LabNumber * m_lab_number = this->m_laboratory.m_layers.back()->FindLabNumber(lab_number_ID);

	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddProp(id_vyprob, id_param, param_name, val);	
	}
}


void SurfDoc::ApplyParams()
{
	this->m_laboratory.ApplyParams();
}

void SurfDoc::Zriz_tbl(
	long id_kt, long id_prob, long id_vyprob, long id_kolca, 	
	double sigma, double tau, 
	double w_do, double ro_do, 
	double w_po_upl, double ro_po_upl, 
	double w_after, double ro_after, unsigned char bStat
	)
{
	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddZriz_tbl(id_vyprob, id_kolca,
			sigma, tau, w_do, ro_do, w_po_upl, ro_po_upl, w_after, ro_after, bStat);
	}
}

void SurfDoc::Zriz0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
	double h, double d, double dh_po_upl,
	double m_kolca,
	double m_grunta,
	double m_grunta_zamoch,
	double m_grunta_posle_uplot,
	double m_grunta_posle,
	double m_grunta_vysush)
{
	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddZriz0(id_vyprob, id_kolca, id_phys_vyprob,
				h, d, dh_po_upl,
				m_kolca,
				m_grunta,
				m_grunta_zamoch,
				m_grunta_posle_uplot,
				m_grunta_posle,
				m_grunta_vysush);
	}
}

void SurfDoc::Zriz(
	long id_kt, long id_prob, long id_vyprob, 	
	long id_hid, long id_shema, long id_stan, double tgfi, double c, double d, double h, unsigned char bStat
	)
{
	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddZriz(id_vyprob,
			id_hid, id_shema, id_stan, tgfi, c, d, h, bStat);
	}
}

void SurfDoc::ApplyZriz()
{
	this->m_laboratory.ApplyZriz();
}


void SurfDoc::Compress(
	long id_kt, long id_prob, long id_vyprob, 	
	double sigma, double dh1, double dh2, unsigned char voda, unsigned char bStat
	)
{
	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddCompress(id_vyprob,
			sigma, dh1, dh2, voda, bStat);
	}
}
void SurfDoc::Cilce0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
	double h, double d,
	double m_kolca,
	double m_grunta,
	double m_grunta_zamoch,
	double m_grunta_posle,
	double m_grunta_vysush)
{
	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddCilce0(id_vyprob, id_kolca, id_phys_vyprob,
			h, d, 
			m_kolca,
			m_grunta,
			m_grunta_zamoch,
			m_grunta_posle,
			m_grunta_vysush);
	}
}
void SurfDoc::Compress(
	long id_kt, long id_prob, long id_vyprob, 	
	double h, double d, 
	double es_l1, double es_r1, double es_l2, double es_r2,
	double nju, double nju_z,
	double m01, double E1, double m02, double E2,
	double m01v, double E1v, double m02v, double E2v,
	unsigned char id_method, unsigned char bStat, unsigned char bStatV
	)
{
	LabNumber * m_lab_number = this->m_laboratory.FindLabNumber(id_kt, id_prob);
	if (!m_lab_number)
	{
		LabLayer * lab_layer = FindLabLayer("-1");// "NO_IGE"
		if (lab_layer)
		{
			m_lab_number = lab_layer->AddNewLabNumber();
			m_lab_number->id_kt = id_kt;
			m_lab_number->id_prob = id_prob;
		}
	}

	if (m_lab_number)
	{
		m_lab_number->AddCompress(id_vyprob,
			h, d, 
			es_l1, es_r1, es_l2, es_r2,
			nju, nju_z,
			m01, E1, m02, E2,
			m01v, E1v, m02v, E2v,
			id_method, bStat, bStatV);
	}
}
void SurfDoc::ApplyCompress(bool use_compression3)
{
	this->m_laboratory.ApplyCompress(use_compression3);
}

void SurfDoc::ParseTrialIndications()
{
	this->m_laboratory.ParseTrialIndications();
}

void SurfDoc::AfterExportFromDB(double _pressure_interval_01_02_0)
{
	this->m_laboratory.Init(_pressure_interval_01_02_0);
	this->m_laboratory.ReCalcProperties(true, true);
	this->m_laboratory.FillLabParameters();
	this->m_laboratory.Normatives();
}
void SurfDoc::PtStZond(
	long id_kt, long id_ust, double glyb,
	const char * ust_name,
	long typ_zond, long n_shema,
	double Kg, double Kf, double Bg, double Bf, double shtanga_d
	)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "PtStZond", 0);
	}
	else
	{
		well->AddPtStZond(id_ust, glyb, 
			ust_name,
			typ_zond,
			n_shema,
			Kg, Kf, Bg, Bf, shtanga_d);
	}
}
void SurfDoc::StZond(
	long id_kt, long npp, long typgr,
	double h, double q0, double f0, 
	double dh, double fsr, 
	unsigned char bStat,
	long id_ige, double pck
	)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "StZond", 0);
	}
	else
	{
		well->AddStZond(
			npp, typgr,
			h, q0, f0, 
			dh, fsr,
			bStat,
			id_ige, pck);
	}
}



void SurfDoc::PCK2FizResults(long id_kt, long npp, long id_calc_param, double param)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "PCK2FizResults", 0);
	}
	else
	{
		well->AddPCK2FizResults(npp, id_calc_param, param);
	}
}
void SurfDoc::PCK2Fiz_CalcParams(long id_calc_param, const char * calc_param, const char * desc)
{
	PCK2FizParamsData data;
	data.id_calc_param = id_calc_param;
	data.calc_param = calc_param;
	data.desc = desc;

	this->m_pck2fiz_params.Add(data);
}
void SurfDoc::ApplyStZond()
{
	for (vector<PCK2FizParamsData>::iterator it = this->m_pck2fiz_params.datas.begin();
		it != this->m_pck2fiz_params.datas.end(); it++)
	{
		AddKarotazh((*it).calc_param.c_str(), RGBA(0,0,255,125));
	}

	{
		AddKarotazh(DYNAMOMETR_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(MANOMETR_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(PCK_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(PCB_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(PCB_PCK_KAR_NAME, RGBA(0,0,255,125));

		AddKarotazh(SVAI_20_20_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_25_25_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_30_30_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_35_35_KAR_NAME, RGBA(0,0,255,125));
		AddKarotazh(SVAI_40_40_KAR_NAME, RGBA(0,0,255,125));

	}

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().ApplyStZond();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}

void SurfDoc::Palja(
	long id_kt,
	double h, double qc, double beta1, double Rs, double fs, double beta2, double f, double RsA, double fhu, double Fu)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "Palja", 0);
	}
	else
	{
		well->Palja(h, qc, beta1, Rs, fs, beta2, f, RsA, fhu, Fu);
	}
}
void SurfDoc::PtPalja(
	long id_kt, long id_typ,
	double pereriz_x, double pereriz_y, double A, double u, double glyb, double RsA, double fhu, double pz,
	long id_snip, double Fu)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "PtPalja", 0);
	}
	else
	{
		well->PtPalja(id_typ, pereriz_x, pereriz_y, A, u, glyb, RsA, fhu, pz, id_snip, Fu);
	}
}
void SurfDoc::ApplyPalja()
{
	AddKarotazh(PALJA_DB_KAR_NAME, RGBA(0,0,255,125));

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().ApplyPalja();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::Rozrizy(
	long id_rozriz, const char * nomer, BYTE has_dxf, const char * fn_dxf,
	BYTE acad_yscale_loaded,
	double z1w, double y1a, double z2w, double y2a
	)
{
	db_rozrizy_data data;
	data.id_rozriz				= id_rozriz;
	data.nomer					= nomer;
	data.has_dxf				= has_dxf;
	data.fn_dxf					= fn_dxf;
	data.acad_yscale_loaded		= acad_yscale_loaded;
	data.z1w					= z1w;
	data.y1a					= y1a;
	data.z2w					= z2w;
	data.y2a					= y2a;
	this->m_db_rozrizy.Add(id_rozriz, data);
}
void SurfDoc::Rozriz(long id_rozriz, long npp, long id_kt, double dxf_x)
{
	db_rozriz_data data;
	data.id_rozriz		= id_rozriz;
	data.npp			= npp;
	data.id_kt			= id_kt;
	data.dxf_x			= dxf_x;
	this->m_db_rozrizy.Add(id_rozriz, data);
}
void SurfDoc::ApplyRozriz()
{
	this->UpdateExtremums();

	string dir = "";
	bool need_dxf_dir = false;
	bool dxf_dir_selected = false;
	for (map<long, DB_rozriz>::iterator itr = this->m_db_rozrizy.rozrizy.begin();
		itr != this->m_db_rozrizy.rozrizy.end(); itr++)
	{
		if ((*itr).second.name_filled && (*itr).second.name.has_dxf)
			need_dxf_dir = true;
	}
	if(need_dxf_dir)
	{
		AfxMessageBox("Сейчас Вам нужно будет выбрать один из DXF разрезов\nчтобы указать директорию в которой лежат все файлы из списка");


#if 0

		TCHAR filter[4098];
		wsprintf(filter, TEXT(".dxf"),
			this->m_excel_stat_zond.ext.c_str());

		//CFileDialog dlg(TRUE, ".stz.xls", "*.stz.xls");
		CFileDialog dlg(TRUE, filter, filter);
		if (dlg.DoModal() == IDCANCEL) return;
		CString path = dlg.GetPathName();
#else
		char fn_dxf[4098];		
		sprintf(fn_dxf, "\0");

		TCHAR filter[4098];
		wsprintf(filter, TEXT("DXF files (*.dxf)%%*.dxf%%All Files (*.*)%%*.*%%\0"));

		// Replace occurrences of '%' string separator 
		// with '\0'. 

		for (int i=0; filter[i]!='\0'; i++) 
		{
			if (filter[i] == '%') 
					filter[i] = '\0'; 
		}	
		if (S_OK == OpenFileDlg(NULL, filter, fn_dxf))
		{
			CString path = fn_dxf;
#endif
			int iflash = path.ReverseFind('\\');
			dir = path.Left(iflash);
			dxf_dir_selected = true;
		}
	}

	//bool load_acad_yscale;
	bool acad_yscale_loaded;
	double z1w, y1a;
	double z2w, y2a;

	//load_acad_yscale = false;
	acad_yscale_loaded = false;
	z1w						= 0.0;
	y1a						= 0.0;
	z2w						= 1.0;
	y2a						= 1.0;

	for (map<long, DB_rozriz>::iterator itr = this->m_db_rozrizy.rozrizy.begin();
		itr != this->m_db_rozrizy.rozrizy.end(); itr++)
	{
		long id_rozriz = (*itr).first;//id_rozriz	vector<double> xMap, yMap, xProfile, yProfile, xAcadYscale, yAcadYscale;
		if ((*itr).second.kt_points.size() > 1)
		{

			BYTE has_dxf = dxf_dir_selected && (*itr).second.name.has_dxf;

			vector<double> xMap, yMap, xProfile, yProfile;
			vector<long> v_ID_KT;

			//load_acad_yscale = false;
			acad_yscale_loaded = (*itr).second.name.acad_yscale_loaded;
			z1w						= 0.0;
			y1a						= 0.0;
			z2w						= 1.0;
			y2a						= 1.0;

			if (acad_yscale_loaded)
			{
				z1w	= (*itr).second.name.z1w;
				y1a	= (*itr).second.name.y1a;
				z2w	= (*itr).second.name.z2w;
				y2a	= (*itr).second.name.y2a;
			}



			double xprofile = 0.0;
			CPoint3 ustje, pre;
			char str[4096], s[128];
			if((*itr).second.name_filled)
				sprintf(str, "%s", (*itr).second.name.nomer.c_str());//
			else
				sprintf(str, "id_rozriz = %d", (*itr).first);//

			char * p1, *p2;
			p1 = str;
			bool go = true, not_first = false;

			double x_profile_start = 0.0;
			double x_profile_finish = 0.0;
			int i = 0;
			for (map<long, db_rozriz_data>::iterator itp = (*itr).second.kt_points.begin();
				itp != (*itr).second.kt_points.end(); itp++)
			{
				(*itp).first;//npp;
				(*itp).second.id_kt;
				(*itp).second.npp;
				(*itp).second.id_rozriz;
				(*itp).second.dxf_x;

				if (!i)
				{
					x_profile_start = (*itp).second.dxf_x;
				}
				else
				{
					x_profile_finish = (*itp).second.dxf_x;
				}
				i++;
			}
			double x_profile_range = x_profile_finish - x_profile_start;
			for (map<long, db_rozriz_data>::iterator itp = (*itr).second.kt_points.begin();
				itp != (*itr).second.kt_points.end(); itp++)
			{
				(*itp).first;//npp;
				(*itp).second.id_kt;
				(*itp).second.npp;
				(*itp).second.id_rozriz;

				v_ID_KT.push_back((*itp).second.id_kt);

				Well_3D * well = this->FindWell((*itp).second.id_kt);
				if (well && well->GetUstje(ustje))
				{		
					if (not_first)
					{
						xprofile += Distance(pre.x, pre.y, ustje.x, ustje.y);
					}
					not_first = true;
					pre = ustje;

					xMap.push_back(ustje.x);
					yMap.push_back(ustje.y);
					if (fabs(x_profile_range) > 1e-8 && has_dxf)
						xProfile.push_back((*itp).second.dxf_x);
					else
						xProfile.push_back(xprofile);
				}
				else
					printf("Warning: Well\"%s\" not found!!!\n", s);
			}
			string fn = (*itr).second.name.fn_dxf;
			string filename = dir + "\\" + fn + ".dxf";
			if (this->AddNewBlnProfile_db(has_dxf ? filename.c_str() : NULL, str, &v_ID_KT, false, xMap, yMap, xProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a, true, id_rozriz) == 0)
			{
				this->ConvertBlnProfilesTo3D(false);
			}
			acad_yscale_loaded = false;

			xMap.clear();
			yMap.clear();
			xProfile.clear();
		}
	}
	if (this->m_cube_size.Defined())
	{
		double x = 0.0;
		//double epsilon = DBL_MIN;//not works
		double epsilon = 1e-3;
		vector<double> xMap, yMap, xProfile;

		xMap.push_back(this->m_cube_size.xLL+epsilon);
		yMap.push_back(this->m_cube_size.yLL+epsilon);
		xProfile.push_back(x);

		xMap.push_back(this->m_cube_size.xMax()-epsilon);
		yMap.push_back(this->m_cube_size.yLL+epsilon);
		x += this->m_cube_size.xMax() - this->m_cube_size.xLL - 2.0*epsilon;
		xProfile.push_back(x);

		xMap.push_back(this->m_cube_size.xMax()-epsilon);
		yMap.push_back(this->m_cube_size.yMax()-epsilon);
		x += this->m_cube_size.yMax() - this->m_cube_size.yLL - 2.0*epsilon;
		xProfile.push_back(x);

		xMap.push_back(this->m_cube_size.xLL+epsilon);
		yMap.push_back(this->m_cube_size.yMax()-epsilon);
		x += this->m_cube_size.xMax() - this->m_cube_size.xLL - 2.0*epsilon;
		xProfile.push_back(x);

		xMap.push_back(this->m_cube_size.xLL+epsilon);
		yMap.push_back(this->m_cube_size.yLL+epsilon);
		x += this->m_cube_size.yMax() - this->m_cube_size.yLL - 2.0*epsilon;
		xProfile.push_back(x);

		if (this->AddNewBlnProfile_db(NULL, "border", NULL, false, xMap, yMap, xProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a, true, -1, false) == 0)
		{
			this->ConvertBlnProfilesTo3D(false);
		}
	}

	// init of zoomCoefZ_XY
	this->ZoomView();
	this->Draw();

}
void SurfDoc::Lito0(
	long id_kt, long id_ige, double h0,	double h1
	)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "Lito0", 0);
	}
	else
	{
		well->Lito0(
			id_ige, h0,	h1);
	}
}
void SurfDoc::IGE0(
	long id_ige, 
	long id_gr,
	const char * ige,
	double mk, 
	double mkz,
	const char * strat, 
	const char * desc0)
{
	ige_data data;
	data.id_ige		= id_ige;
	data.id_gr		= id_gr;
	data.ige		= ige;
	data.mk			= mk;
	data.mkz		= mkz;
	data.strat		= strat;
	data.desc0		= desc0;

	m_db_ige0.Add(data);
}
void SurfDoc::Lito(
	long id_kt, long id_ige, double h0,	double h1
	)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "Lito", 0);
	}
	else
	{
		well->Lito(
			id_ige, h0,	h1);
	}
}
void SurfDoc::IGE(
	long id_ige, 
	long id_gr,
	const char * ige,
	double mk, 
	double mkz,
	const char * strat, 
	const char * desc0)
{
	ige_data data;
	data.id_ige		= id_ige;
	data.id_gr		= id_gr;
	data.ige		= ige;
	data.mk			= mk;
	data.mkz		= mkz;
	data.strat		= strat;
	data.desc0		= desc0;

	m_db_ige.Add(data);
}
void SurfDoc::Grunty(
	long id_gr,
	const char * nazva_u, 
	const char * nazva_r,
	long typgr, 
	long typgr_pck, 
	long id_normatyv, 
	long id_grcons, 
	long id_uklad, 
	long id_nju, 
	long id_grmain, 
	long id_umpoz, 
	long id_genezis)
{
	grunt_data data;
	data.id_gr			= id_gr;
	data.nazva_u		= nazva_u;
	data.nazva_r		= nazva_r;
	data.typgr			= typgr;
	data.typgr_pck		= typgr_pck;
	data.id_normatyv	= id_normatyv;
	data.id_grcons		= id_grcons;
	data.id_uklad		= id_uklad;
	data.id_nju			= id_nju;
	data.id_grmain		= id_grmain;
	data.id_umpoz		= id_umpoz;
	data.id_genezis		= id_genezis;

	m_db_ige.Add(data);
	m_db_ige0.Add(data);

}

void SurfDoc::Genezis(long id_genezis,
	const char * nazva_u, const char * nazva_r,
	long id_normatyv, long id_grmain,
	const char * index,
	BYTE r, BYTE g, BYTE b)
{
	genezis_data data;

	data.id_genezis = id_genezis;
	data.nazva_u = nazva_u;
	data.nazva_r = nazva_r;
	data.id_normatyv = id_normatyv;
	data.id_grmain = id_grmain;
	data.index = index;
	data.r = r;
	data.g = g;
	data.b = b;

	this->m_db_genezis.Add(id_genezis, data);
}
void SurfDoc::UmPoz(long id_umpoz,
	const char * umpoz, const char * hatchacad,
	double angle, double scale)
{
	umpoz_data data;
	data.id_umpoz = id_umpoz;
	data.umpoz = umpoz;
	data.hatchacad = hatchacad;
	data.angle = angle;
	data.scale = scale;

	this->m_db_umpoz.Add(id_umpoz, data);
}

void SurfDoc::ApplyLito()
{
	need_to_set_wel_element_litho_keys = false;
	need_to_set_wel_element_ige_keys = false;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().ApplyLito_well_ige_podoshva();
			m_drills.GetCurrentMsg().ApplyLito_well_lito_podoshva();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}


	GeoColomn * geo_colomn_eng = this->AddGeoColomn(GeoElement::type::engineer_geological);
	if (geo_colomn_eng)
	{
		for (vector<IGE_Data>::iterator it_ige = m_db_ige.data.begin();
			it_ige != m_db_ige.data.end(); it_ige++)
		{
			if ((*it_ige).ige_filled)
			{
				long id_key = (*it_ige).ige.id_ige;
				string key = (*it_ige).ige.ige;
				GeoElement * elem = geo_colomn_eng->AddEmptyGeoElement(key.c_str(), CGround::ground_type::Undefined_ground, id_key);
				if (elem)
				{
					elem->SetName((*it_ige).grunt.nazva_r);
					elem->InitDoc(this);

					if ((*it_ige).grunt_filled)
					{
						elem->id_umpoz = (*it_ige).grunt.id_umpoz;

						bool color_from_genezis = false;
						if(color_from_genezis)
						{
							long id_genezis = (*it_ige).grunt.id_genezis;
							map<long, genezis_data>::iterator found_genezis = this->m_db_genezis.data1.find(id_genezis);
							if (found_genezis != this->m_db_genezis.data1.end())
							{
								BYTE r = (*found_genezis).second.r;
								BYTE g = (*found_genezis).second.g;
								BYTE b = (*found_genezis).second.b;

								elem->SetColor(RGB(r,g,b));

							}
						}
						else
						{
							for (map<long, db_griddata_surf>::iterator it = this->m_db_griddata.datas.begin();
								it != this->m_db_griddata.datas.end(); it++)
							{
								//long id_surf = (*it).first;
								COLORREF color = 0;
								if ((*it).second.data2_filled)
								{
									if ((*it).second.data2.id_ige == id_key)
									{
										color = RGB((*it).second.data2.r, (*it).second.data2.g, (*it).second.data2.b);
										elem->SetColor(color);
									}
								}	
							}
						}
					}	
				}
			}
		}
	}

	GeoColomn * geo_colomn_lito = this->AddGeoColomn(GeoElement::type::lithological);				  

	if (geo_colomn_lito)
	{
		for (vector<IGE_Data>::iterator it_ige = m_db_ige0.data.begin();
			it_ige != m_db_ige0.data.end(); it_ige++)
		{
			if ((*it_ige).ige_filled)
			{
				string key = (*it_ige).ige.ige;
				long id_key = (*it_ige).ige.id_ige;
				GeoElement * elem = geo_colomn_lito->AddEmptyGeoElement(key.c_str(), CGround::ground_type::Undefined_ground, id_key);
				if (elem)
				{
					elem->SetName((*it_ige).grunt.nazva_r);
					elem->InitDoc(this);
					if ((*it_ige).grunt_filled)
					{
						long id_genezis = (*it_ige).grunt.id_genezis;
						map<long, genezis_data>::iterator found_genezis = this->m_db_genezis.data1.find(id_genezis);
						if (found_genezis != this->m_db_genezis.data1.end())
						{
							BYTE r = (*found_genezis).second.r;
							BYTE g = (*found_genezis).second.g;
							BYTE b = (*found_genezis).second.b;

							elem->SetColor(RGB(r,g,b));

							elem->id_umpoz = (*it_ige).grunt.id_umpoz;
						}
					}	
				}				
			}
		}
	}

	GeoColomn * geo_colomn_faults = this->AddGeoColomn(GeoElement::type::faults);
	if (geo_colomn_faults)
	{
		long id_key = 1;
		string key = "faults";

		GeoElement * elem = geo_colomn_faults->AddEmptyGeoElement(key.c_str(), CGround::ground_type::Undefined_ground, id_key);

		FaultGeoElement * faults_elem = dynamic_cast<FaultGeoElement *>(elem);

		if (elem && faults_elem)
		{
			elem->SetName(key.c_str());
			elem->InitDoc(this);

			BYTE r = 255;
			BYTE g = 0;
			BYTE b = 0;

			elem->SetColor(RGB(r,g,b));
		}	
	}


	TreeView_DeleteMyItem(this->hwndTV,this->m_geo_colomns_ObjectList.myTreeItem);
	AddGeoColomnsToTree(this->hwndTV, this);

}
void SurfDoc::Voda(long id_kt, long horizont,
	double hv_z, double hv_v,
	SYSTEMTIME dv)
{
	Well_3D * well = this->FindWell(id_kt);
	if (!well)
	{
		char str[1024];
		sprintf(str, "Well with id_kt = %d not found", id_kt);
		MessageBox(0, str, "Voda", 0);
	}
	else
	{
		well->Voda(horizont, hv_z, hv_v, dv);
	}
}
void SurfDoc::ApplyVoda()
{
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().ApplyVoda();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	GeoColomn * geo_colomn_hydro = this->AddGeoColomn(GeoElement::type::hydro_geological);
	if (geo_colomn_hydro)
	{
		for (long id = 1; id <= 2; id++)
		{
			if (id)
			{
				long id_key = id;
				string key = "";
				switch(id_key)
				{
				case 1://з'явився
					{
						key = "poyav";
					}
					break;
				case 2://встановився
					{
						key = "ust";
					}
					break;
				}
				GeoElement * elem = geo_colomn_hydro->AddEmptyGeoElement(key.c_str(), CGround::ground_type::Undefined_ground, id_key);

				HydroGeoElement * hydro_elem = dynamic_cast<HydroGeoElement *>(elem);

				if (elem && hydro_elem)
				{
					elem->SetName(key.c_str());
					elem->InitDoc(this);

					BYTE r = 0;
					BYTE g = 0;
					BYTE b = 255;

					elem->SetColor(RGB(r,g,b));
					switch(id_key)
					{
					case 1:
						{
							hydro_elem->ustanovlen = false;
						}
						break;
					case 2:
						{
							hydro_elem->ustanovlen = true;
						}
						break;
					}
				}				

			}
		}
	}

}


void SurfDoc::AddGranular(long id_kt, long id_prob, long id_gran, const char * gran_name, double val)
{
	for (vector<LabLayer *>::iterator it_l = this->m_laboratory.m_layers.begin();
		it_l != this->m_laboratory.m_layers.end(); it_l++)
	{
		LabLayer * lablayer = (*it_l);
		if (lablayer)
		{
			for (vector<LabNumber*>::iterator it_n = lablayer->lab_numbers.begin();
				it_n != lablayer->lab_numbers.end(); it_n++)
			{
				LabNumber * labnumer = (*it_n);
				if (labnumer)
				{
					if (labnumer->id_kt == id_kt && labnumer->id_prob == id_prob)
					{
						labnumer->AddGranular(id_gran, gran_name, val);
						return;
					}
				}
			}
		}
	}
}
void SurfDoc::ApplyGranular()
{
	this->m_laboratory.ApplyGranular();
}

void SurfDoc::AddNewWellColomn_LaboratoryAnalizes_FromDB_2()
{

	lab_errors.clear();

	for (vector<LabLayer *>::iterator it_l = this->m_laboratory.m_layers.begin();
		it_l != this->m_laboratory.m_layers.end(); it_l++)
	{
		LabLayer * lablayer = (*it_l);
		if (lablayer)
		{
			//lablayer->ID;
			//lablayer->layer_number;

			for (vector<LabNumber*>::iterator it_n = lablayer->lab_numbers.begin();
				it_n != lablayer->lab_numbers.end(); it_n++)
			{
				LabNumber * labnumer = (*it_n);
				if (labnumer)
				{
					//

					/*switch(labnumer->m_mine_working_type)
					{
					case LabNumber::mine_working_type::hole:
						{
							{
								char s[128];
								sprintf(s, "%s\0", lablayer->layer_number.c_str());
#if !CHAR_LAYER_NUMBER_ID
								OemToChar(s,s);	
#endif
								
								error_of_add_new_well_colomn_laboratory_analizes err;
								err.m_mine_working_type = LabNumber::mine_working_type::hole;
								err.lab_layer_number = s;
								err.labnumer_ID = labnumer->ID;								
								err.mine_working_number = labnumer->mine_working_number;
								err.depth = labnumer->depth;

								lab_errors.push_back(err);
							}
						}
						break;
					case LabNumber::mine_working_type::well:
						{*/
							// номер выработки,
							Well_3D * well = this->FindWell(labnumer->id_kt);
							if (!well)
							{
								char s[128];
								sprintf(s, "%s\0", lablayer->layer_number.c_str());
#if !CHAR_LAYER_NUMBER_ID
								OemToChar(s,s);
#endif
								char str [1024];
								sprintf(str, 
									"Ошибка добавления лабораторного анализа к скважинной колонке!\n"
									"Номер лабораторного слоя %s\n"
									"Для лабораторного номера %s\n" 
									"Не найдена скважина %s\n"
									"Анализ загружен в память но не будет отображаться в 3D и на профилях"
									,
									s, labnumer->ID.c_str(), labnumer->mine_working_number.c_str());
								MessageBox(0, str,"Ошибка добавления лабораторного анализа", 0);
								
								error_of_add_new_well_colomn_laboratory_analizes err;
								err.m_mine_working_type = labnumer->m_mine_working_type;
								err.lab_layer_number = s;
								err.labnumer_ID = labnumer->ID;								
								err.mine_working_number = labnumer->mine_working_number;
								err.depth = labnumer->depth;
								lab_errors.push_back(err);		
							}

							CPoint3 ustje;

							if (well && well->GetUstje(ustje))
							{
								WellColomn * wc = well->FindWellColomn(WellElement::type::laboratory_analizes);
								if (wc)
								{
									char well_element_id[4098];
									sprintf(well_element_id, "%s depth %f\0", labnumer->ID.c_str(), labnumer->depth);
									while (well_element_id[strlen(well_element_id)-1] == '0')
										well_element_id[strlen(well_element_id)-1] = '\0';
									if (well_element_id[strlen(well_element_id)-1] == '.')
										well_element_id[strlen(well_element_id)-1] = '\0';

									WellElement * welem = wc->FindWellElement(well_element_id);
									if (!welem)
									{
										welem = wc->AddNewWellElement(well_element_id);
									}
									else
									{
										char warning[4098];
										sprintf(warning, "Лабораторный элемент %s уже существует в колонке скважины %s", well_element_id, labnumer->mine_working_number.c_str());
										MessageBox(0, warning, "Warning", 0);
									}

									Well_Laboratory_Analize * wlab = dynamic_cast<Well_Laboratory_Analize *>(welem);
									if (wlab)
									{
										wlab->InitByLabNumber(labnumer, ustje.z);
									}
								}
								else
									MessageBox(0,"!wc","AddNewWellColomn_LaboratoryAnalizes_FromDB_2",0);

							}
							else
							{
								//MessageBox(0,"!(well && well->GetUstje(ustje))","AddNewWellColomn_LaboratoryAnalizes_FromDB_2",0);
							}
						/*}
						break;
					}*/
				}
			}
		}
	}

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().ReDraw();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

}
void SurfDoc::AddNewWellColomn_LaboratoryAnalizes()
{

	lab_errors.clear();

	if (!m_wdli_laboratory)
		m_wdli_laboratory = this->AddWellsDraw(WellElement::type::laboratory_analizes, true, 15.f, false, wells_draw_list_item::draw_mode_2d::both);
	
	
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().AddNewWellColomn_LaboratoryAnalizes();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	for (vector<LabLayer *>::iterator it_l = this->m_laboratory.m_layers.begin();
		it_l != this->m_laboratory.m_layers.end(); it_l++)
	{
		LabLayer * lablayer = (*it_l);
		if (lablayer)
		{
			//lablayer->ID;
			//lablayer->layer_number;

			for (vector<LabNumber*>::iterator it_n = lablayer->lab_numbers.begin();
				it_n != lablayer->lab_numbers.end(); it_n++)
			{
				LabNumber * labnumer = (*it_n);
				if (labnumer)
				{
					//

					/*switch(labnumer->m_mine_working_type)
					{
					case LabNumber::mine_working_type::hole:
						{
							{
								char s[128];
								sprintf(s, "%s\0", lablayer->layer_number.c_str());
#if !CHAR_LAYER_NUMBER_ID
								OemToChar(s,s);	
#endif								
								error_of_add_new_well_colomn_laboratory_analizes err;
								err.m_mine_working_type = LabNumber::mine_working_type::hole;
								err.lab_layer_number = s;
								err.labnumer_ID = labnumer->ID;								
								err.mine_working_number = labnumer->mine_working_number;
								err.depth = labnumer->depth;

								lab_errors.push_back(err);
							}
						}
						break;
					case LabNumber::mine_working_type::well:
						{*/
							// номер выработки,
							Well_3D * well = this->FindWell(labnumer->mine_working_number.c_str());
							if (!well)
							{
								char s[128];
								sprintf(s, "%s\0", lablayer->layer_number.c_str());
#if !CHAR_LAYER_NUMBER_ID
								OemToChar(s,s);
#endif

								char str [1024];
								sprintf(str, 
									"Ошибка добавления лабораторного анализа к скважинной колонке!\n"
									"Номер лабораторного слоя %s\n"
									"Для лабораторного номера %s\n" 
									"Не найдена скважина %s\n"
									"Анализ загружен в память но не будет отображаться в 3D и на профилях"
									,
									s, labnumer->ID.c_str(), labnumer->mine_working_number.c_str());
								//MessageBox(0, str,"Ошибка добавления лабораторного анализа", 0);
								
								error_of_add_new_well_colomn_laboratory_analizes err;
								err.m_mine_working_type = labnumer->m_mine_working_type;
								err.lab_layer_number = s;
								err.labnumer_ID = labnumer->ID;								
								err.mine_working_number = labnumer->mine_working_number;
								err.depth = labnumer->depth;
								lab_errors.push_back(err);		
							}

							CPoint3 ustje;

							if (well && well->GetUstje(ustje))
							{
								WellColomn * wc = well->FindWellColomn(WellElement::type::laboratory_analizes);
								if (wc)
								{
									char well_element_id[4098];
									sprintf(well_element_id, "%s depth %f\0", labnumer->ID.c_str(), labnumer->depth);
									while (well_element_id[strlen(well_element_id)-1] == '0')
										well_element_id[strlen(well_element_id)-1] = '\0';
									if (well_element_id[strlen(well_element_id)-1] == '.')
										well_element_id[strlen(well_element_id)-1] = '\0';

									WellElement * welem = wc->FindWellElement(well_element_id);
									if (!welem)
									{
										welem = wc->AddNewWellElement(well_element_id);
									}
									else
									{
										char warning[4098];
										sprintf(warning, "Лабораторный элемент %s уже существует в колонке скважины %s", well_element_id, labnumer->mine_working_number.c_str());
										MessageBox(0, warning, "Warning", 0);
									}

									Well_Laboratory_Analize * wlab = dynamic_cast<Well_Laboratory_Analize *>(welem);
									if (wlab)
									{
										wlab->InitByLabNumber(labnumer, ustje.z);
									}
								}
							}
						/*}
						break;
					}*/
				}
			}
		}
	}
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().ReDraw();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}




void SurfDoc::AddKarotazhy(LPDRILLSDLGDATA lpDrillsDlgMem, bool fill_well_colomn)
{
	vector<vector<cell> >::iterator Iter_vect_cell;
	vector<int>::iterator check_iter; 


	vector<cell> * karotazh_glubin = NULL;
	COLORREF karotazh_color = RGBA(0,0,255,125);
	
	for ( 
		Iter_vect_cell = lpDrillsDlgMem->pdrills->begin(), check_iter = lpDrillsDlgMem->checking_of_rows->begin(); 
		Iter_vect_cell != lpDrillsDlgMem->pdrills->end() && check_iter != lpDrillsDlgMem->checking_of_rows->end(); 
	Iter_vect_cell++, check_iter++)
	{
		if( (*check_iter) != 2)
		{
			if(karotazh_glubin == NULL)
			{
				karotazh_glubin = &(*Iter_vect_cell);
				if (0 == ChooseSurfColor(this->hSurfWnd, karotazh_color)){}

				AddKarotazh(lpDrillsDlgMem->filename, karotazh_color);

			}
			continue;
		}

		// find Well ID
		string well_id; 
		bool well_id_found = FindWellID(lpDrillsDlgMem, Iter_vect_cell, well_id);
		Well_3D * found_well = NULL;
		if (well_id_found)
			found_well = this->FindWell(well_id.c_str());

		if (found_well)
		{
			if (!found_well->WellInit2(Iter_vect_cell, 
				karotazh_glubin,
				lpDrillsDlgMem->types_of_colomns,
				lpDrillsDlgMem->pnames_of_colomns,
				lpDrillsDlgMem->colors_of_sloi,
				lpDrillsDlgMem->filename, 
				NULL, false, NULL,
				false
				))
				return;
		}
		else
		{
			Well_3D drill(this);
			if (!drill.WellInit2(Iter_vect_cell, 
				karotazh_glubin,
				lpDrillsDlgMem->types_of_colomns,
				lpDrillsDlgMem->pnames_of_colomns,
				lpDrillsDlgMem->colors_of_sloi,
				lpDrillsDlgMem->filename, 
				NULL, false, NULL,
				true
				))
				return;
			m_drills.AddMsg(&drill);
			m_drills.GetLastMsg().ReinitWellColomnsPointers();
		}
	}
	m_drills_ObjectList.Init(m_drills, this);
}


void SurfDoc::GetKarotazhCube(int index, double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz)
{
	minx = DBL_MAX; 
	miny = DBL_MAX; 
	minz = DBL_MAX;
	
	maxx = -DBL_MAX;
	maxy = -DBL_MAX;
	maxz = -DBL_MAX;

	if (index < 0) return;

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().GetKarotazhCube(index, minx, miny, minz, maxx, maxy, maxz);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}
void SurfDoc::KarotazhSaveAsDat(int index)
{
	TCHAR lpstrFile[256]; lpstrFile[0] = '\0';
	
	TCHAR filter[] =    
		TEXT("Golden Software Data (*.dat)\0*.dat\0")
		TEXT("All Files (*.*)\0*.*\0");

	//sprintf(lpstrFile, "%s\\razrez", directory);
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
	{
		this->KarotazhSaveAsDat(index,lpstrFile);
	}
}
void SurfDoc::KarotazhSaveAsDat(int index, const char * fn)
{
	FILE * stream = fopen(fn, "wt");
	if (stream)
	{
		if (this->m_drills.SetCurrentMsgOnFirst())
		{
			do
			{
//				fprintf(stream, "%s\n", this->m_drills.GetCurrentMsg().GetIDString());

				Karotazh * karotazh = this->m_drills.GetCurrentMsg().GetKarotazh(index);
				if (karotazh)
				{
					karotazh->SaveAsDat(stream);
				}
			}
			while(this->m_drills.IncrementCurrentMsg());
		}
		fclose(stream);
	}
}
bool SurfDoc::GetAcadYscaleLoaded()
{
	bool res = true;
	if(this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			res = res && this->m_bln_profiles.GetCurrentMsg().GetAcadYscaleLoaded();
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}
	return res;
}
void PrintDoProfileScript(FILE * bas);
void PrintMainProfilesScript(FILE * bas, vector<string> & prof_names_in_fun);
void SurfDoc::SavingOfCubeProjectionGrid(const char * outdir, int index_cub, int make_grids_vnahljost, bool convert_to_acad_yscale, bool non_stretched_xscale)
{
	char script_dir[4098];
	char script_fn[4098];
	char srf_dir[4098];
	char dxf_dir[4098];

	sprintf(script_dir, "%s\\scripts\0", outdir);
	if (CheckMyLicense()) CreateDirectory(script_dir,NULL);

	sprintf(srf_dir, "%s\\srf\0", outdir);
	if (CheckMyLicense()) CreateDirectory(srf_dir,NULL);

	sprintf(dxf_dir, "%s\\dxf\0", outdir);
	if (CheckMyLicense()) CreateDirectory(dxf_dir,NULL);


	sprintf(script_fn, "%s\\DoProfiles.bas\0", script_dir);

	FILE * bas = fopen(script_fn, "wt");

	if (bas) PrintDoProfileScript(bas);


	vector<string> prof_names_in_fun;

	if(this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			char prof_name_in_fun[1024];
			this->m_bln_profiles.GetCurrentMsg().SavingOfCubeProjectionGrid(bas, outdir, index_cub, make_grids_vnahljost, convert_to_acad_yscale, non_stretched_xscale, prof_name_in_fun);
			prof_names_in_fun.push_back(prof_name_in_fun);
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}
	PrintMainProfilesScript(bas, prof_names_in_fun);
	if (bas) fclose(bas);
}

void SurfDoc::InterpolateKarotazhCube3(int index)//, double minx, double miny, double minz, double maxx, double maxy, double maxz, double dx, double dy, double dz)
{
	Grid grid;
	if(!grid.gridSection.InitSize(this->m_cube_size, 0)) return;

	Grid4 grid4;
	if(!grid4.grid4Section.InitSize(this->m_cube_size)) return;
	grid4.grid4Section.v = Alloc3DMat<double>(grid4.grid4Section.nPag, grid4.grid4Section.nRow, grid4.grid4Section.nCol);

	////vector<karotazh_slice> vks;
	//double z; long p;
	//for (z = grid4.grid4Section.zLL, p = 0; p < grid4.grid4Section.nPag; z += grid4.grid4Section.zSize, p++)
	//{
	//	vks.push_back( karotazh_slice(z));
	//}
	vector<double> vx,vy,vz;
	vector<double> vx_kar,vy_kar;
	vector<double> vxk,vyk,vzk,vvk;
	CPoint3 pt3;

	//cout << "Karotazh::linterp_method [1,2]?" << endl;
	//cout << "1 - linear" << endl;
	//cout << "2 - spline" << endl;
	//int intmeth = 1;
	//cin >> intmeth;
	//Karotazh::linterp_method int_meth;
	/*switch(intmeth)
	{
	case 1:
		int_meth = Karotazh::linterp_method::linear;
		break;
	case 2:
		int_meth = Karotazh::linterp_method::spline;
		break;
	}*/
/*
    karotazh_extrapolate_down ked;
	bool to_extrapolate_down = false;
	cout << "to_extrapolate_down [0,1]?" << endl;
	cin >> to_extrapolate_down;

	if (to_extrapolate_down)
	{
		ked.to_extrapolate_down = true;
		//karotazh_extrapolate_down::extrapolate_down_method extr_down_method = karotazh_extrapolate_down::extrapolate_down_method::none;
		int extr_down_method = 0;
		cout << "extrapolate_down_method [0, 1, 2]?" << endl;
		cout << "0 - none" << endl;
		cout << "1 - with_lowest_value" << endl;
		cout << "2 - continue_interpolation" << endl;
		cin >> extr_down_method;
		ked.m_extrapolate_down_method = karotazh_extrapolate_down::extrapolate_down_method(extr_down_method);
		double extrapolation_len = 0.0;
		cout << "extrapolation_len?" << endl;
		cin >> extrapolation_len;
		ked.extrapolation_len = extrapolation_len;

	}*/


	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().PutKarotazhPoints(index, vxk, vyk, vzk, vvk);
			if(this->m_drills.GetCurrentMsg().GetUstje(pt3))
			{
				vx.push_back(pt3.x);vy.push_back(pt3.y);vz.push_back(pt3.z);
				this->AddSphere(pt3,0);

				if (this->m_drills.GetCurrentMsg().GetKarotazh(index))
				{
					vx_kar.push_back(pt3.x);
					vy_kar.push_back(pt3.y);
				}
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}

	int ( *griddata_fun_for_surf)(HWND, vector<double>&, vector<double>&, vector<double>&,  Grid *, void *, bool);
	//int ( *griddata_fun_for_cube)(HWND, vector<double>&, vector<double>&, vector<double>&,  Grid *, void *, bool);

	int griddata_fun_number_for_surf = 0;
	//int griddata_fun_number_for_cube = 0;
	
	cout << "griddata_fun_number_for_surf [0,1,2,3,4,5]" << endl;
	cout << "0 - griddata_v4" << endl;
	cout << "1 - griddata_v4 with GreenFun" << endl;
	cout << "2 - griddata_2 with any dist_fun" << endl;
	cout << "3 - griddata_3 with triangulation and interpolation" << endl;
	cout << "4 - griddata_3 with triangulation and interpolation with default parameters" << endl;
	cout << "5 - griddata_3 with triangulation and interpolation with default parameters use contour" << endl;
	cin >> griddata_fun_number_for_surf;

	//cout << "griddata_fun_number_for_cube [0,1,2,3,4,5]" << endl;
	//cin >> griddata_fun_number_for_cube;

	griddata_3_param param3_for_surf;                                  
	FillDefaultParam(param3_for_surf);	
	//griddata_3_param param3_for_cube;                                  
	//FillDefaultParam(param3_for_cube);	

/*d:\C++\Lag\Win32\Win32_89.76\surfdoc\src\SurfDoc.cpp(1668) : error C2440: '=' : 
cannot convert from 
'int (__cdecl *)(HWND,std::vector<_Ty> &,std::vector<_Ty> &,std::vector<_Ty> &,Grid *,vdouble *,vdouble *,vdouble *,bool)' 
to 
'int (__cdecl *)(HWND,std::vector<_Ty> &,std::vector<_Ty> &,std::vector<_Ty> &,Grid *,void *,bool)'*/


	void * _param_for_surf = NULL;
	//void * _param_for_cube = NULL;
	switch (griddata_fun_number_for_surf)
	{
	case 0:
		griddata_fun_for_surf = griddata;
		break;
	case 1:
		griddata_fun_for_surf = griddata_v4;
		break;
	case 2:
		griddata_fun_for_surf = griddata_2;
		break;
	case 3:
		_param_for_surf = NULL;
		griddata_fun_for_surf = griddata_3;
		break;
	case 4:
		param3_for_surf.use_contour = false;
		_param_for_surf = &param3_for_surf;									  
		griddata_fun_for_surf = griddata_3;
		break;
	case 5:
		param3_for_surf.use_contour = true;
		_param_for_surf = &param3_for_surf;									  
		griddata_fun_for_surf = griddata_3;
		break;
	default:
		return ;
	}

	/*switch (griddata_fun_number_for_cube)
	{
	case 0:
		griddata_fun_for_cube = griddata;
		break;
	case 1:
		griddata_fun_for_cube = griddata_v4;
		break;
	case 2:
		griddata_fun_for_cube = griddata_2;
		break;
	case 3:
		_param_for_cube = NULL;
		griddata_fun_for_cube = griddata_3;
		break;
	case 4:
		param3_for_cube.use_contour = false;
		_param_for_cube = &param3_for_cube;									  
		griddata_fun_for_cube = griddata_3;
		break;
	case 5:
		param3_for_cube.use_contour = true;
		_param_for_cube = &param3_for_cube;									  
		griddata_fun_for_cube = griddata_3;
		break;
	default:
		return ;
	}*/
#if 0
	if (griddata_fun_number_for_surf == 4 || griddata_fun_number_for_surf == 5)
	{
		cout << "param3_for_surf.slau_method [0,1] ?" << endl;
		cout << "0 - SLAU9" << endl;
		cout << "1 - SLAU_excl" << endl;
		cin >> param3_for_surf.slau_method;
	}
#endif
	/*if (griddata_fun_number_for_cube == 4 || griddata_fun_number_for_cube == 5)
	{
		cout << "param3_for_cube.slau_method [0,1] ?" << endl;
		cout << "0 - SLAU9" << endl;
		cout << "1 - SLAU_excl" << endl;
		cin >> param3_for_cube.slau_method;
	}*/
	
	param3_for_surf.m_len_biss_type = griddata_3_param::len_biss_type::min_edges_len;
	//param3_for_cube.m_len_biss_type = griddata_3_param::len_biss_type::min_edges_len;

	int filter_grid_min_max_surf = 0;
	//int filter_grid_min_max_cube = 0;

	double surf_part_of_range_low = 0.0;
	double surf_part_of_range_high = 0.0;

	//double cube_part_of_range_low = 0.0;
	//double cube_part_of_range_high = 0.0;

	cout << "FilterGridMinMax Surf [0,1]?" << endl;
	cin >> filter_grid_min_max_surf;

	if (filter_grid_min_max_surf) 
	{
		cout << "surf_part_of_range_low [0.0]?" << endl;
		cin >> surf_part_of_range_low;
		cout << "surf_part_of_range_high [0.0]?" << endl;
		cin >> surf_part_of_range_high;
	}

	/*cout << "FilterGridMinMax Cube [0,1]?" << endl;
	cin >> filter_grid_min_max_cube;

	if (filter_grid_min_max_cube) 
	{
		cout << "cube_part_of_range_low [0.0]?" << endl;
		cin >> cube_part_of_range_low;
		cout << "cube_part_of_range_high [0.0]?" << endl;
		cin >> cube_part_of_range_high;
	}*/

	bool to_blank_with_loaded_Contour = false;
	bool to_blank_with_Triangulation_Contour = false;
	cout << "to_blank_with_Triangulation_Contour [0,1]?" << endl;
	cin >> to_blank_with_Triangulation_Contour;

	bool use_biss = false; 
	double len_biss = 0.0;

	if (to_blank_with_Triangulation_Contour)
	{
		cout << "use_biss on blank_with_Triangulation_Contour [0,1]?" << endl;
		cin >> use_biss;

		if (use_biss)
		{
			cout << "enter len_biss?" << endl;
			cin >> len_biss;
		}
	}
	else
	{
		cout << "to_blank_with_loaded_Contour [0,1]?" << endl;
		cin >> to_blank_with_loaded_Contour;
	}


	griddata_fun_for_surf(NULL, vx, vy, vz, &grid, _param_for_surf, true);
	if (filter_grid_min_max_surf) FilterGridMinMax(vz, &grid, surf_part_of_range_low, surf_part_of_range_high);

	long id_surf = this->GetIDSurfForNewGridDataOrSurface();
	BYTE podoshva = 0; long id_ige = -1;
	this->AddSurf(id_surf, podoshva, id_ige, 0, &grid);


	if (to_blank_with_Triangulation_Contour)
	{

		Line3D blankline;
		CPoint3 base_point;


		if (getTriangulationContour(vx_kar, vy_kar, param3_for_surf.ftf, use_biss, len_biss,  &blankline, &base_point) == 1)
		{
			int inside = 0;

			m_surfaces.GetLastMsg().AddBlankLine(inside, blankline);
			m_surfaces.GetLastMsg().m_surface.Blank(m_surfaces.GetLastMsg().m_blank_lines.GetLastMsg(), false, m_surfaces.GetLastMsg(), &base_point);

			m_surfaces.GetLastMsg().m_surface.MakeGridSection(&grid.gridSection);
		}
	}
	else
	{
		if(to_blank_with_loaded_Contour)
		{
			m_surfaces.GetLastMsg().Blank();
			m_surfaces.GetLastMsg().m_surface.MakeGridSection(&grid.gridSection);
		}
	}
//	SaveAsSurfer7Grid(file_grd, &grid);


	bool to_allocate = false;
	griddata4(0, vxk, vyk, vzk, vvk, 
			 &grid4, NULL, to_allocate);

	//vector<karotazh_slice>::iterator it;
	long p;
	for (/*it = vks.begin(),*/ p = 0; /*it != vks.end() && */p < grid4.grid4Section.nPag; /*it++,*/ p++)
	{
		/*if ((*it).vx.size() < 4)
		{
			for (long c = 0; c < grid4.grid4Section.nCol; c++)
			{
				for (long r = 0; r < grid4.grid4Section.nRow; r++)
				{
					grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
				}	
			}
			continue;
		}*/
		//griddata_fun_for_cube(NULL, (*it).vx, (*it).vy, (*it).vv, &grid_temp, _param_for_cube, to_allocate);
		//if (filter_grid_min_max_cube) FilterGridMinMax((*it).vv, &grid_temp, cube_part_of_range_low, cube_part_of_range_high);
				
		double z_p = grid4.grid4Section.zLL + p*grid4.grid4Section.zSize;
		for (long c = 0; c < grid4.grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid4.grid4Section.nRow; r++)
			{
				if (grid.gridSection.z[r][c] == BLANK_VALUE)
				{
					grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
				}
				else
				{
					if (z_p > grid.gridSection.z[r][c])
					{
						grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
					}
					/*else
					{
						grid4.grid4Section.v[p][r][c] = grid_temp.gridSection.z[r][c];
					}*/
				}
			}
		}
		//to_allocate = false;
	}

	this->AddCube(&grid4, Well_3D::karotazh_list[index].name.c_str(), RGB(0,0,0));

	if (grid4.grid4Section.v) Free3DMat<double>(grid4.grid4Section.v);

//	FreeDoubleMat(grid_temp.gridSection.z);
	FreeDoubleMat(grid.gridSection.z);


}
void SurfDoc::InterpolateKarotazhCube(int index, 
									  bool divide_cube_on_1_25, 
									  Karotazh::linterp_method int_meth,
									  karotazh_extrapolate_down ked, 
									  
									  long griddata_app, 
									  long griddata_fun_number,
									  
									  bool filter_grid_min_max_cube_2d,
									  bool filter_grid_min_max_cube_3d,
                                      
									  bool to_blank_with_Triangulation_Contour,
									  bool use_biss, double len_biss,
									  bool to_blank_with_loaded_Contour)
{
	if (index < 0) return;

	//здесь вычисляем грид
	Grid grid;
	if(!grid.gridSection.InitSize(this->m_cube_size, 0)) return ;

	Grid grid_temp = grid;

	Grid4 grid4;
	if(!grid4.grid4Section.InitSize(this->m_cube_size)) return ;
	grid4.grid4Section.v = Alloc3DMat<double>(grid4.grid4Section.nPag, grid4.grid4Section.nRow, grid4.grid4Section.nCol);

	vector<karotazh_slice> vks;
	double z; long p;
	for (z = grid4.grid4Section.zLL, p = 0; p < grid4.grid4Section.nPag; z += grid4.grid4Section.zSize, p++)
	{
		vks.push_back( karotazh_slice(z));
	}
	vector<double> vx,vy,vz;
	vector<double> vx_kar,vy_kar;
	vector<double> vxk,vyk,vzk,vvk;
	CPoint3 pt3;



	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().PutKarotazhPoints(index, vxk, vyk, vzk, vvk);
			this->m_drills.GetCurrentMsg().PutKarotazhSlicesPoint(int_meth, index, vks, ked);
			if(this->m_drills.GetCurrentMsg().GetUstje(pt3))
			{
				vx.push_back(pt3.x);vy.push_back(pt3.y);vz.push_back(pt3.z);
				this->AddSphere(pt3,0);

				if (this->m_drills.GetCurrentMsg().GetKarotazh(index))
				{
					vx_kar.push_back(pt3.x);
					vy_kar.push_back(pt3.y);
				}
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
#if 0
	int ( *griddata_fun_for_surf)(HWND, vector<double>&, vector<double>&, vector<double>&,  Grid *, void *, bool);
	int ( *griddata_fun_for_cube)(HWND, vector<double>&, vector<double>&, vector<double>&,  Grid *, void *, bool);

	int griddata_fun_number_for_surf = 0;
	int griddata_fun_number_for_cube = 0;
	
	cout << "griddata_fun_number_for_surf [0,1,2,3,4,5]" << endl;
	cout << "0 - griddata_v4" << endl;
	cout << "1 - griddata_v4 with GreenFun" << endl;
	cout << "2 - griddata_2 with any dist_fun" << endl;
	cout << "3 - griddata_3 with triangulation and interpolation" << endl;
	cout << "4 - griddata_3 with triangulation and interpolation with default parameters" << endl;
	cout << "5 - griddata_3 with triangulation and interpolation with default parameters use contour" << endl;
	cin >> griddata_fun_number_for_surf;

	cout << "griddata_fun_number_for_cube [0,1,2,3,4,5]" << endl;
	cin >> griddata_fun_number_for_cube;

	griddata_3_param param3_for_surf;                                  
	FillDefaultParam(param3_for_surf);	
	griddata_3_param param3_for_cube;                                  
	FillDefaultParam(param3_for_cube);	

/*d:\C++\Lag\Win32\Win32_89.76\surfdoc\src\SurfDoc.cpp(1668) : error C2440: '=' : 
cannot convert from 
'int (__cdecl *)(HWND,std::vector<_Ty> &,std::vector<_Ty> &,std::vector<_Ty> &,Grid *,vdouble *,vdouble *,vdouble *,bool)' 
to 
'int (__cdecl *)(HWND,std::vector<_Ty> &,std::vector<_Ty> &,std::vector<_Ty> &,Grid *,void *,bool)'*/


	void * _param_for_surf = NULL;
	void * _param_for_cube = NULL;
	switch (griddata_fun_number_for_surf)
	{
	case 0:
		griddata_fun_for_surf = griddata;
		break;
	case 1:
		griddata_fun_for_surf = griddata_v4;
		break;
	case 2:
		griddata_fun_for_surf = griddata_2;
		break;
	case 3:
		_param_for_surf = NULL;
		griddata_fun_for_surf = griddata_3;
		break;
	case 4:
		param3_for_surf.use_contour = false;
		_param_for_surf = &param3_for_surf;									  
		griddata_fun_for_surf = griddata_3;
		break;
	case 5:
		param3_for_surf.use_contour = true;
		_param_for_surf = &param3_for_surf;									  
		griddata_fun_for_surf = griddata_3;
		break;
	default:
		return ;
	}

	switch (griddata_fun_number_for_cube)
	{
	case 0:
		griddata_fun_for_cube = griddata;
		break;
	case 1:
		griddata_fun_for_cube = griddata_v4;
		break;
	case 2:
		griddata_fun_for_cube = griddata_2;
		break;
	case 3:
		_param_for_cube = NULL;
		griddata_fun_for_cube = griddata_3;
		break;
	case 4:
		param3_for_cube.use_contour = false;
		_param_for_cube = &param3_for_cube;									  
		griddata_fun_for_cube = griddata_3;
		break;
	case 5:
		param3_for_cube.use_contour = true;
		_param_for_cube = &param3_for_cube;									  
		griddata_fun_for_cube = griddata_3;
		break;
	default:
		return ;
	}
#if 0
	if (griddata_fun_number_for_surf == 4 || griddata_fun_number_for_surf == 5)
	{
		cout << "param3_for_surf.slau_method [0,1] ?" << endl;
		cout << "0 - SLAU9" << endl;
		cout << "1 - SLAU_excl" << endl;
		cin >> param3_for_surf.slau_method;
	}
	if (griddata_fun_number_for_cube == 4 || griddata_fun_number_for_cube == 5)
	{
		cout << "param3_for_cube.slau_method [0,1] ?" << endl;
		cout << "0 - SLAU9" << endl;
		cout << "1 - SLAU_excl" << endl;
		cin >> param3_for_cube.slau_method;
	}
#endif
	param3_for_surf.m_len_biss_type = griddata_3_param::len_biss_type::min_edges_len;
	param3_for_cube.m_len_biss_type = griddata_3_param::len_biss_type::min_edges_len;

	//int filter_grid_min_max_surf = 0;
	double surf_part_of_range_low = 0.0;
	double surf_part_of_range_high = 0.0;
#endif

	double cube_part_of_range_low_2d = 0.0;
	double cube_part_of_range_high_2d = 0.0;

#if 0
	//double cube_part_of_range_low_3d = 0.0;
	//double cube_part_of_range_high_3d = 0.0;

	//cout << "FilterGridMinMax Surf [0,1]?" << endl;
	//cin >> filter_grid_min_max_surf;

	if (filter_grid_min_max_surf) 
	{
		cout << "surf_part_of_range_low [0.0]?" << endl;
		cin >> surf_part_of_range_low;
		cout << "surf_part_of_range_high [0.0]?" << endl;
		cin >> surf_part_of_range_high;
	}

	if (filter_grid_min_max_cube_2d) 
	{
		cout << "cube_part_of_range_low_2d [0.0]?" << endl;
		cin >> cube_part_of_range_low_2d;
		cout << "cube_part_of_range_high_2d [0.0]?" << endl;
		cin >> cube_part_of_range_high_2d;
	}
#endif

	double maxv = -DBL_MAX;
	double minv = DBL_MAX;

	if (filter_grid_min_max_cube_3d) 
	{
		for (size_t i = 0; i < vvk.size(); i++)
		{
			if (maxv < vvk[i]) maxv = vvk[i];
			if (minv > vvk[i]) minv = vvk[i];
		}
	}
#if 1
	bool to_allocate0 = true;
	griddata_dialog dlg0(to_allocate0, this, NULL, NULL, (griddata_dialog::griddata_application)griddata_app, NULL, false, true,
		&grid, &vx, &vy, &vz);
		dlg0.InitGriddataDialog(NULL, false);
		dlg0.griddata_fun_number = griddata_fun_number;//id_alg;
		dlg0.may_quit_surfer = false;
		dlg0.OkButtonHandler(NULL);
#else
	griddata_fun_for_surf(NULL, vx, vy, vz, &grid, _param_for_surf, true);
	if (filter_grid_min_max_surf) FilterGridMinMax(vz, &grid, surf_part_of_range_low, surf_part_of_range_high);
#endif

	long id_surf = this->GetIDSurfForNewGridDataOrSurface();
	BYTE podoshva = 0; long id_ige = -1;
	this->AddSurf(id_surf, podoshva, id_ige, 0, &grid);


	if (to_blank_with_Triangulation_Contour)
	{

		Line3D blankline;
		CPoint3 base_point;

		int ftf = 0; //[0,1,2]

		if (getTriangulationContour(vx_kar, vy_kar, ftf, use_biss, len_biss,  &blankline, &base_point) == 1)
		{
			int inside = 0;

			if (this->m_cube_size.Defined())
			{
				for (size_t i = 0; i < blankline.GetPointsNumber(); i++)
					blankline.GetDocumentPoint(i).z = this->m_cube_size.zMax();
			}

			m_surfaces.GetLastMsg().AddBlankLine(inside, blankline);
			m_surfaces.GetLastMsg().m_surface.Blank(m_surfaces.GetLastMsg().m_blank_lines.GetLastMsg(), false, m_surfaces.GetLastMsg(), &base_point);

			m_surfaces.GetLastMsg().m_surface.MakeGridSection(&grid.gridSection);
		}
	}
	else
	{
		if(to_blank_with_loaded_Contour)
		{
			m_surfaces.GetLastMsg().Blank();
			m_surfaces.GetLastMsg().m_surface.MakeGridSection(&grid.gridSection);
		}
	}



	bool to_allocate = true;


	vector<karotazh_slice>::iterator it;
	for (it = vks.begin(), p = 0; it != vks.end() && p < grid4.grid4Section.nPag; it++, p++)
	{
		if ((*it).vx.size() < 4)
		{
			for (long c = 0; c < grid4.grid4Section.nCol; c++)
			{
				for (long r = 0; r < grid4.grid4Section.nRow; r++)
				{
					grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
				}	
			}
			continue;
		}
#if 0
		griddata_fun_for_cube(NULL, (*it).vx, (*it).vy, (*it).vv, &grid_temp, _param_for_cube, to_allocate);
#else
		griddata_dialog dlg(to_allocate, this, NULL, NULL, (griddata_dialog::griddata_application)griddata_app, NULL, false, true, 
			&grid_temp, &(*it).vx, &(*it).vy, &(*it).vv);
		dlg.InitGriddataDialog(NULL, false);
		dlg.griddata_fun_number = griddata_fun_number;//id_alg;
		if (p < grid4.grid4Section.nPag - 1)
			dlg.may_quit_surfer = false;
		dlg.OkButtonHandler(NULL);

#endif
		if (filter_grid_min_max_cube_2d) FilterGridMinMax((*it).vv, &grid_temp, cube_part_of_range_low_2d, cube_part_of_range_high_2d);
		for (long c = 0; c < grid4.grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid4.grid4Section.nRow; r++)
			{
				if (grid.gridSection.z[r][c] == BLANK_VALUE)
				{
					grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
				}
				else
				{
					if ((*it).z > grid.gridSection.z[r][c])
					{
						grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
					}
					else
					{
						grid4.grid4Section.v[p][r][c] = grid_temp.gridSection.z[r][c];
					}
				}
			}
		}
		to_allocate = false;
	}
		
	if (filter_grid_min_max_cube_3d) 
		FilterCubeMinMax(&grid4, minv, maxv);

	if (divide_cube_on_1_25)
		MultiplyCube(&grid4, 1.0/1.25);

	this->AddCube(&grid4, Well_3D::karotazh_list[index].name.c_str(), RGB(0,0,0));

	if (grid4.grid4Section.v) Free3DMat<double>(grid4.grid4Section.v);

	FreeDoubleMat(grid_temp.gridSection.z);
	FreeDoubleMat(grid.gridSection.z);


}
void SurfDoc::ProjectionKarotazhCube(int index_kar, int index_cub)
{
	printf("ProjectionKarotazhCube(int index_kar = %d int index_cub = %d)\n", index_kar, index_cub);
	if (index_kar < 0) return;
	if (index_cub < 0) return;

	Cube4D * cube = this->FindCube(index_cub);
	if (!cube) 
	{
		printf("!cube\n");
		return;
	}

	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().KarotazhProjection(index_kar, *cube);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
}

void SurfDoc::UpdateKarotazhNames(bool & update2Dview, bool & update3Dview)
{
	double scale_2d;
	double scale_3d;
	update2Dview = false;
	update3Dview = false;
	size_t r = 0;
	for (vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
		it != Well_3D::karotazh_list.end(); it++, r++)
	{
		(*it).name = this->m_KarotazhListViewTab.GetItemString(r,0);

		scale_2d = atof(this->m_KarotazhListViewTab.GetItemString(r,1).c_str());
		if ((*it).scale_2d != scale_2d)
		{
			(*it).scale_2d = scale_2d;
			update2Dview = true;
		}

		scale_3d = atof(this->m_KarotazhListViewTab.GetItemString(r,5).c_str());
		if ((*it).scale != scale_3d)
		{
			(*it).scale = scale_3d;
			update3Dview = true;
		}
	}
}


void SurfDoc::UpdateWaterSaturation()
{
	size_t r = 0;
	GeoColomn * colomn = this->FindGeoColomn(GeoElement::type::engineer_geological);
	if (colomn) 
	{
		for (map<string, GeoElement*>::iterator it = colomn->geo_elements.begin(); it != colomn->geo_elements.end(); it++, r++)
		{		
			if (it->second)
			{
				GeoElement::type t = it->second->m_type;
				
				if (t != colomn->m_type)
				{
					printf("warning: element type  = \"%s\" (%d) not eqial colomn type = \"%s\"(%d)\n",
						GeoElement::GeoElementTypeToString(t), int(t),
						GeoElement::GeoElementTypeToString(colomn->m_type), int(colomn->m_type)
						);
				}

				char str[1024];
				GeoElement * geo = it->second;
				EngineerGeoElement * eng = dynamic_cast<EngineerGeoElement *>(geo);
				if (eng)
				{
					string s = this->m_WaterSaturationListViewTab.GetItemString(r,0);

					if (strlen(s.c_str()) && ISNUM(s.c_str()))
					{					
						double v = atof(s.c_str());
						if(eng->SetValue(EngineerGeoElement::ValueType::degree_of_moisture,
							EngineerGeoElement::GroundDescriptionType::normative,
							EngineerGeoElement::StrengthDescriptionType::simple, 
							v))
						{
						}
					}
				}
			}
		}
	}
}
bool linterp(int n, double* vx, double* vy, double x, double &y)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           py: given Y-Axis data
	//           px: given X-Axis data
	//
	//          x: point on X-Axis to be interpolated
	//
	//      output:
	//
	//          y: interpolated value at point "x"

	if (n < 2) return false;

	int j = 1;
	while (j < n-1 && vx[j] < x)
	{
			j++;
	}
	double mu = (x-vx[j-1])/(vx[j]-vx[j-1]);
	y = vy[j-1]+mu*(vy[j]-vy[j-1]);

	return true;
}

bool linterp_integral(int n, double* vx, double* vy, double x1, double x2, double &integral)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           py: given Y-Axis data
	//           px: given X-Axis data
	//
	//          x: point on X-Axis to be interpolated
	//
	//      output:
	//
	//          y: interpolated value at point "x"

	if (n < 2) return false;

	// j1 j2 - номера интервалов

	int j1 = 1;
	while (j1 < n-1 && vx[j1] < x1)
	{
			j1++;
	}
	
	int j2 = 1;
	while (j2 < n-1 && vx[j2] < x2)
	{
			j2++;
	}

	double mu1 = (x1-vx[j1-1])/(vx[j1]-vx[j1-1]);
	double mu2 = (x2-vx[j2-1])/(vx[j2]-vx[j2-1]);

	double y1 = vy[j1-1]+mu1*(vy[j1]-vy[j1-1]);
	double y2 = vy[j2-1]+mu2*(vy[j2]-vy[j2-1]);

	integral = 0;

	if (j1 > j2)
	{
	}
	else if (j1 == j2)
	{
		integral += 0.5 * (x2 - x1) * (y1 + y2);
	}
	else // j2 > j1
	{
		int j_first = x1 < vx[0] ? 0 : j1;
		int j_last = x2 > vx[n-1] ? j2 : j2-1;
		// суммируем промежуточные интервалы
		for(int j = j_first; j < j_last; j++)
		{
			integral += 0.5 * (vx[j+1] - vx[j]) * (vy[j+1] + vy[j]);
		}		
		// хвосты
		integral += 0.5 * (vx[j_first] - x1) * (y1 + vy[j_first]);
		integral += 0.5 * (x2 - vx[j_last]) * (y2 + vy[j_last]);
	}
	//printf("integral = %f\tx1 = %f\tx2 = %f\tj1 = %d j2 = %d\n", integral, x1, x2, j1, j2);
	return true;
}

double TestCorrectFiValue_Sand(double fi)
{
	if(fi < 23.0) fi = 23.0;
	if(fi > 40.0) fi = 40.0;
	return fi;
}
void GetAlpha12(double fi, double & alpha1, double & alpha2)
{
	fi = TestCorrectFiValue_Sand(fi);

	double vfi[]     = {  23,   25,   27,   29,   31,   33,    35,    37,    39};
	double valpha1[] = { 9.5, 12.6, 17.3, 24.4, 34.6, 48.6,  71.3, 108.0, 163.0};
	double valpha2[] = {18.6, 24.8, 32.8, 45.5, 64.0, 87.6, 127.0, 185.0, 260.0};

	int n = sizeof(vfi)/sizeof(double);
	linterp(n, vfi, valpha1, fi, alpha1);
	linterp(n, vfi, valpha2, fi, alpha2);
}
bool inline linterp2(int nx, double* vx, int ny, double* vy, double ** zz, double x, double y, double &z)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           py: given Y-Axis data
	//           px: given X-Axis data
	//
	//          x: point on X-Axis to be interpolated
	//
	//      output:
	//
	//          y: interpolated value at point "x"

	//printf("linterp2 nx = %d ny = %d\n", nx, ny);
	//printf("linterp2 x = %f y = %f\n", x, y);

	if (nx < 2) return false;
	if (ny < 2) return false;

	int jx = 1;
	while (jx < nx-1 && vx[jx] < x)
	{
			jx = jx+1;
	}

	int jy = 1;
	while (jy < ny-1 && vy[jy] < y)
	{
			jy = jy+1;
	}

	//printf("linterp2 jx = %d jy = %d\n", jx, jy);

	double mu_x = (x-vx[jx-1])/(vx[jx]-vx[jx-1]);
	double mu_y = (y-vy[jy-1])/(vy[jy]-vy[jy-1]);

	//printf("linterp2 mu_x = %f mu_y = %f\n", mu_x, mu_y);

	//cout << zz[jy-1][jx-1] << "    " << zz[jy-1][jx] << endl;
	//cout << zz[jy  ][jx-1] << "    " << zz[jy  ][jx] << endl;

	double zx_1 = zz[jy-1][jx-1] + mu_y * (zz[jy][jx-1] - zz[jy-1][jx-1]);
	double zx   = zz[jy-1][jx  ] + mu_y * (zz[jy][jx  ] - zz[jy-1][jx  ]);
	
	double z1 = zx_1 + mu_x * (zx - zx_1);

	double zy_1 = zz[jy-1][jx-1] + mu_x * (zz[jy-1][jx] - zz[jy-1][jx-1]);
	double zy   = zz[jy  ][jx-1] + mu_x * (zz[jy  ][jx] - zz[jy  ][jx-1]);
	
	double z2 = zy_1 + mu_y * (zy - zy_1);

	z = 0.5 * (z1 + z2);

	//printf("linterp2 zx_1 = %f zx = %f\n", zx_1, zx);


	//printf("linterp2 z = %f\n", z);

	return true;
}
void GetAlpha3(double fi, double h_per_d, double & alpha3)
{	
	fi = TestCorrectFiValue_Sand(fi);
	//printf("void GetAlpha3(double fi %f, double h_per_d %f, double & alpha3)\n", fi, h_per_d);
	double vh_per_d[] = { 4.0, 5.0, 7.5, 10.0, 12.5, 15.0,  17.5, 20.0, 22.5, 25.0};
	double vfi[] = 
		{  23,   25,   27,   29,   31,   33,   35,   37,   39};
	double malpha3[10][9] = {
		{0.78, 0.79, 0.80, 0.82, 0.84, 0.85, 0.85, 0.85, 0.87},
		{0.75, 0.76, 0.77, 0.79, 0.81, 0.82, 0.83, 0.84, 0.85},
		{0.68, 0.70, 0.71, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84},
		{0.62, 0.65, 0.67, 0.70, 0.73, 0.75, 0.77, 0.79, 0.81},
		{0.58, 0.61, 0.68, 0.67, 0.70, 0.73, 0.75, 0.78, 0.80},
		{0.55, 0.58, 0.61, 0.65, 0.68, 0.71, 0.73, 0.76, 0.79},
		{0.51, 0.55, 0.58, 0.62, 0.66, 0.69, 0.72, 0.75, 0.78},
		{0.49, 0.53, 0.57, 0.61, 0.65, 0.68, 0.72, 0.75, 0.78},
		{0.46, 0.51, 0.55, 0.60, 0.64, 0.67, 0.71, 0.74, 0.77},
		{0.44, 0.49, 0.54, 0.59, 0.63, 0.67, 0.70, 0.74, 0.77}
	};
	const int nfi = sizeof(vfi)/sizeof(double); //9
	const int nh_per_d = sizeof(vh_per_d)/sizeof(double);//10

	double ** zz = AllocDoubleMat(nh_per_d, nfi);
	for (int r = 0; r < nh_per_d; r++)
	{
		for (int c = 0; c < nfi; c++)
		{
			zz[r][c] = malpha3[r][c];
		}
	}

	if (h_per_d > 25)
		h_per_d = 25;

	linterp2(nfi, vfi, nh_per_d, vh_per_d, zz, fi, h_per_d, alpha3);
	FreeDoubleMat(zz);

}


void GetAlpha4(double fi, double d, double & alpha4)
{	
	fi = TestCorrectFiValue_Sand(fi);

	double vd[] = { 0.8, 4.0 };
	double vfi[] = 
		{  23,   25,   27,   29,   31,   33,   35,   37,   39};
	double malpha4[2][9] = {
		{0.34, 0.31, 0.29, 0.27, 0.26, 0.25, 0.24, 0.23, 0.22},
		{0.25, 0.24, 0.23, 0.22, 0.21, 0.20, 0.19, 0.18, 0.17}
	};
	const int nfi = sizeof(vfi)/sizeof(double); //9
	const int nd = sizeof(vd)/sizeof(double);//2

	double ** zz = AllocDoubleMat(nd, nfi);
	for (int r = 0; r < nd; r++)
	{
		for (int c = 0; c < nfi; c++)
		{
			zz[r][c] = malpha4[r][c];
		}
	}

	if (d < 0.8) d = 0.8;

	linterp2(nfi, vfi, nd, vd, zz, fi, d, alpha4);
	FreeDoubleMat(zz);

}



bool GetClayR(double IL, double h, double & R)
{		
	if (IL > 0.4 && h > 20) 
	{
		//printf("Warning: GetClayR interpolation (IL (%f) > 0.4 && h (%f) > 20) h Setted to 20\n", IL,h);
		h = 20;
	}
	double vh[] = { 3, 5, 7, 10, 12, 15, 18, 20, 30, 40 };
	double vIL[] = 
		{  0.0,  0.1,  0.2,  0.3,  0.4,  0.5,  0.6};
#if 1
	// по Снипу - 85
	double mR[10][7] = {
		{  850,  750,  650,  500,  400,  300,  250},
		{ 1000,  850,  750,  650,  500,  400,  350},
		{ 1150, 1000,  850,  750,  600,  500,  450},
		{ 1350, 1200, 1050,  950,  800,  700,  600},
		{ 1550, 1400, 1250, 1100,  950,  800,  700},
		{ 1800, 1650, 1500, 1300, 1100, 1000,  800},
		{ 2100, 1900, 1700, 1500, 1300, 1150,  950},
		{ 2300, 2100, 1900, 1650, 1450, 1250, 1050},
		{ 3300, 3000, 2600, 2300, 2000,    0,    0},
		{ 4500, 4000, 3500, 3000, 2500,    0,    0}
	};
#else
	// редакция О.А.Крамаренко
	double mR[10][7] = {
		{  850,  750,  650,  500,  400,  300,  250},
		{ 1000,  850,  750,  650,  500,  400,  350},
		{ 1150, 1000,  850,  750,  600,  500,  450},
		{ 1350, 1200, 1050,  950,  800,  700,  600},
		{ 1550, 1400, 1250, 1100,  950,  800,  700},
		{ 1800, 1650, 1500, 1300, 1100, 1000,  800},
		{ 2100, 1900, 1700, 1500, 1300, 1150,  950},
		{ 2300, 2100, 1900, 1650, 1450, 1250, 1050},
		{ 3300, 3000, 2600, 2300, 2000, 1350, 1100},
		{ 4500, 4000, 3500, 3000, 2500, 1450, 1150}
	};
#endif
	const int nIL = sizeof(vIL)/sizeof(double); //7
	const int nh = sizeof(vh)/sizeof(double);//10

	double ** zz = AllocDoubleMat(nh, nIL);
	for (int r = 0; r < nh; r++)
	{
		for (int c = 0; c < nIL; c++)
		{
			zz[r][c] = mR[r][c];
		}
	}

	linterp2(nIL, vIL, nh, vh, zz, IL, h, R);
	FreeDoubleMat(zz);

	return true;

}

bool GetGammaCF(BuroNabivSvaj::SvaiType svai_type, double v_custom_gamma_cf[4], CGround::ground_type ground_type, double & gamma_cf)
{
	bool res = false;
	switch(svai_type)
	{
	case BuroNabivSvaj::SvaiType::nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::nabivn_vibroshtampovan:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.9;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.9;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.9;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.9;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::burov_betonir_bez_vody_ili_s_obsadnoj_truboj:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::burov_betonir_pod_vodoj_ili_pod_glin_rr:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::svai_obolochki_pogr_vibrir_s_vyemkoj_grunta:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 1.0;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.9;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::svai_stolby:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.7;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.6;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = 0.9;
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = 0.8;
					res = true;
				}
				break;
			}
		}
		break;
	case BuroNabivSvaj::SvaiType::custom:
		{
			switch(ground_type)
			{
			case CGround::Sand:
				{
					gamma_cf = v_custom_gamma_cf[0];
					res = true;
				}
				break;
			case CGround::SandyLoam:
				{
					gamma_cf = v_custom_gamma_cf[1];
					res = true;
				}
				break;
			case CGround::Loam:
				{
					gamma_cf = v_custom_gamma_cf[2];
					res = true;
				}
				break;
			case CGround::Clay:
				{
					gamma_cf = v_custom_gamma_cf[3];
					res = true;
				}
				break;
			}
		}
		break;
	default:
		return false;
	}
	return res;
}




bool Get_f_i_clay(double h, double IL, const CGround::ground_type current_ground_type, bool increase_if_not_porosty, double e, double & f_i)
{
	double vh[] = {1, 2, 3, 4, 5, 6, 8, 10, 15, 20, 25, 30, 35 };
	double vIL[] = 
		{0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
	double mf[13][9] = {
		{ 35,  23,  15,  12,   8,   4,   4,   3,   2},
		{ 42,  30,  21,  17,  12,   7,   5,   4,   4},
		{ 48,  35,  25,  20,  14,   8,   7,   6,   5},
		{ 53,  38,  27,  22,  16,   9,   8,   7,   5},
		{ 56,  40,  29,  24,  17,  10,   8,   7,   6},
		{ 58,  42,  31,  25,  18,  10,   8,   7,   6},
		{ 62,  44,  33,  26,  19,  10,   8,   7,   6},
		{ 65,  46,  34,  27,  19,  10,   8,   7,   6},
		{ 72,  51,  38,  28,  20,  11,   8,   7,   6},
		{ 79,  56,  41,  30,  20,  12,   8,   7,   6},
		{ 86,  61,  44,  32,  20,  12,   8,   7,   6},
		{ 93,  66,  47,  34,  21,  12,   9,   8,   7},
		{100,  70,  50,  36,  22,  13,   9,   8,   7}
	};
	const int nIL = sizeof(vIL)/sizeof(double); //9
	const int nh = sizeof(vh)/sizeof(double);//13

	double ** zz = AllocDoubleMat(nh, nIL);
	for (int r = 0; r < nh; r++)
	{
		for (int c = 0; c < nIL; c++)
		{
			zz[r][c] = mf[r][c];
		}
	}

	linterp2(nIL, vIL, nh, vh, zz, IL, h, f_i);
	FreeDoubleMat(zz);
	
	if(increase_if_not_porosty)
	{
		switch(current_ground_type)
		{
		case CGround::SandyLoam:
		case CGround::Loam:
			{
				if (e < 0.5) f_i *= 1.15;
			}
			break;
		case CGround::Clay:
			{
				if (e < 0.6) f_i *= 1.15;
			}
			break;
		}
	}
	return true;
}
bool Get_f_i_clay(double h1, double h2, double IL, const CGround::ground_type current_ground_type, bool increase_if_not_porosty, double e, double & f_i_h)
{
	double vh[] = {1, 2, 3, 4, 5, 6, 8, 10, 15, 20, 25, 30, 35 };
	double vIL[] = 
		{0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
	double mf[13][9] = {
		{ 35,  23,  15,  12,   8,   4,   4,   3,   2},
		{ 42,  30,  21,  17,  12,   7,   5,   4,   4},
		{ 48,  35,  25,  20,  14,   8,   7,   6,   5},
		{ 53,  38,  27,  22,  16,   9,   8,   7,   5},
		{ 56,  40,  29,  24,  17,  10,   8,   7,   6},
		{ 58,  42,  31,  25,  18,  10,   8,   7,   6},
		{ 62,  44,  33,  26,  19,  10,   8,   7,   6},
		{ 65,  46,  34,  27,  19,  10,   8,   7,   6},
		{ 72,  51,  38,  28,  20,  11,   8,   7,   6},
		{ 79,  56,  41,  30,  20,  12,   8,   7,   6},
		{ 86,  61,  44,  32,  20,  12,   8,   7,   6},
		{ 93,  66,  47,  34,  21,  12,   9,   8,   7},
		{100,  70,  50,  36,  22,  13,   9,   8,   7}
	};
	const int nIL = sizeof(vIL)/sizeof(double); //9
	const int nh = sizeof(vh)/sizeof(double);//13

	/*double ** zz = AllocDoubleMat(nh, nIL);
	for (int r = 0; r < nh; r++)
	{
		for (int c = 0; c < nIL; c++)
		{
			zz[r][c] = mf[r][c];
		}
	}

	linterp2(nIL, vIL, nh, vh, zz, IL, h, f_i);
	FreeDoubleMat(zz);*/

	double * vf = new double [nh];
	for (int r = 0; r < nh; r++)
	{
		linterp(nIL, vIL, mf[r], IL, vf[r]);
	}
	linterp_integral(nh,vh,vf,h1,h2,f_i_h);

	if(increase_if_not_porosty)
	{
		switch(current_ground_type)
		{
		case CGround::SandyLoam:
		case CGround::Loam:
			{
				if (e < 0.5) f_i_h *= 1.15;
			}
			break;
		case CGround::Clay:
			{
				if (e < 0.6) f_i_h *= 1.15;
			}
			break;
		}
	}
	return true;
}
bool Get_f_i_sand(double h, CSandGround::sand_type sandtype, bool increase_if_dense, CSandGround::sand_strength sandstrength, double & f_i)
{
	bool res = false;
	double vh[] = {   1,  2,  3,  4,  5,  6,  8, 10, 15, 20, 25, 30,  35};
	double vf1[] = { 35, 42, 48, 53, 56, 58, 62, 65, 72, 79, 86, 93, 100};
	double vf2[] = { 23, 30, 35, 38, 40, 42, 44, 46, 51, 56, 61, 66,  70};
	double vf3[] = { 15, 21, 25, 27, 29, 31, 33, 34, 38, 41, 44, 47,  50};

	int n = sizeof(vh)/sizeof(double);

	switch(sandtype)
	{
	case CSandGround::sand_type::gravelic:			// Гравелистые
	case CSandGround::sand_type::coarse_grained:	// Крупные
	case CSandGround::sand_type::medium_grained:	// Средней крупности
		{
			linterp(n, vh, vf1, h, f_i);
			res = true;
		}
		break;
	case CSandGround::sand_type::small_grained:		// Мелкие
		{
			linterp(n, vh, vf2, h, f_i);
			res = true;
		}
		break;
	case CSandGround::sand_type::powdered:			// Пылеватые
		{
			linterp(n, vh, vf3, h, f_i);
			res = true;
		}
		break;
	}
	if (increase_if_dense && sandstrength == CSandGround::sand_strength::dense)
	{
		f_i *= 1.3;
	}
	return res;

}
bool Get_f_i_sand(double h1, double h2, CSandGround::sand_type sandtype, bool increase_if_dense, CSandGround::sand_strength sandstrength, double & f_i_h)
{
	bool res = false;
	double vh[] = {   1,  2,  3,  4,  5,  6,  8, 10, 15, 20, 25, 30,  35};
	double vf1[] = { 35, 42, 48, 53, 56, 58, 62, 65, 72, 79, 86, 93, 100};
	double vf2[] = { 23, 30, 35, 38, 40, 42, 44, 46, 51, 56, 61, 66,  70};
	double vf3[] = { 15, 21, 25, 27, 29, 31, 33, 34, 38, 41, 44, 47,  50};

	int n = sizeof(vh)/sizeof(double);

	switch(sandtype)
	{
	case CSandGround::sand_type::gravelic:			// Гравелистые
	case CSandGround::sand_type::coarse_grained:	// Крупные
	case CSandGround::sand_type::medium_grained:	// Средней крупности
		{
			linterp_integral(n, vh, vf1, h1, h2, f_i_h);
			res = true;
		}
		break;
	case CSandGround::sand_type::small_grained:		// Мелкие
		{
			linterp_integral(n, vh, vf2, h1, h2, f_i_h);
			res = true;
		}
		break;
	case CSandGround::sand_type::powdered:			// Пылеватые
		{
			linterp_integral(n, vh, vf3, h1, h2, f_i_h);
			res = true;
		}
		break;
	}
	if (increase_if_dense && sandstrength == CSandGround::sand_strength::dense)
	{
		f_i_h *= 1.3;
	}
	return res;

}
Cube4D * SurfDoc::SuspendedInWaterSpecificGravity(
							   int index_cub_specific_gravity_of_ground_particles,
							   int index_cub_porosity_factor)
{
	printf(
		"SurfDoc::SuspendedInWaterSpecificGravity\n"
		"index_cub_specific_gravity_of_ground_particles = %d\n"
		"index_cub_porosity_factor = %d\n"
		,
		index_cub_specific_gravity_of_ground_particles,
		index_cub_porosity_factor);

	if (index_cub_specific_gravity_of_ground_particles < 0) return NULL;
	if (index_cub_porosity_factor < 0) return NULL;

	if (!this->m_cube_size.Defined())
	{
		printf("!this->m_cube_size.Defined()\n");
		return NULL;
	}


	Cube4D * cube_specific_gravity_of_ground_particles = this->FindCube(index_cub_specific_gravity_of_ground_particles);
	if (!cube_specific_gravity_of_ground_particles) 
	{
		printf("!cube_specific_gravity_of_ground_particles\n");
		return NULL;
	}
	if(!cube_specific_gravity_of_ground_particles->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
	{
		printf("!cube_specific_gravity_of_ground_particles IsTheSameSize(this->m_cube_size)\n");
		this->m_cube_size.Printf();
		cube_specific_gravity_of_ground_particles->lattice.grid4Section.Printf();
		return NULL;
	}

	Cube4D * cube_porosity_factor = this->FindCube(index_cub_porosity_factor);
	if (!cube_porosity_factor) 
	{
		printf("!cube_porosity_factor\n");
		return NULL;
	}
	if(!cube_porosity_factor->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
	{
		printf("!cube_porosity_factor IsTheSameSize(this->m_cube_size)\n");
		this->m_cube_size.Printf();
		cube_porosity_factor->lattice.grid4Section.Printf();
		return NULL;
	}

	printf("Start\n");

	Grid4 grid4;
	if(!grid4.grid4Section.InitSize(this->m_cube_size)) return NULL;
	grid4.grid4Section.v = Alloc3DMat<double>(grid4.grid4Section.nPag, grid4.grid4Section.nRow, grid4.grid4Section.nCol);

	for (long c = 0; c < this->m_cube_size.nCol; c++)
	{
		for (long r = 0; r < this->m_cube_size.nRow; r++)
		{	
			for (long p = 0; p < this->m_cube_size.nPag; p++)                    
			{					
				grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
			}
		}
	}

	for (long c = 0; c < this->m_cube_size.nCol; c++)
	{
printf("c = %d %d\n", c, this->m_cube_size.nCol);
		for (long r = 0; r < this->m_cube_size.nRow; r++)
		{	
			for (long p = 0; p < this->m_cube_size.nPag; p++)                    
			{	

				if (cube_porosity_factor && cube_porosity_factor->lattice.grid4Section.v[p][r][c] != BLANK_VALUE
					&&
					cube_specific_gravity_of_ground_particles && cube_specific_gravity_of_ground_particles->lattice.grid4Section.v[p][r][c] != BLANK_VALUE)
				{
					double e = cube_porosity_factor->lattice.grid4Section.v[p][r][c];
					double gamma_s = cube_specific_gravity_of_ground_particles ->lattice.grid4Section.v[p][r][c];
					double gamma_w = 9.8; // удельный вес воды кН/м3
					grid4.grid4Section.v[p][r][c] = (gamma_s-gamma_w) / (1.0 + e);
				}
			}
		}
	}

	char cube_name[4098];
	
	sprintf(cube_name, "SuspendedInWaterSpecificGravity, кН/м3\0");
	Cube4D * cube = this->AddCube(&grid4, cube_name, 0);
	if (cube)
	{
		cube->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
		cube->Draw();
		cube->AddItem_ToTree(this->hwndTV, m_cubes_ObjectList.myTreeItem);
	}
	return cube;
}
bool SurfDoc::SuspendedInWaterSpecificGravity()
{
	if (!this->m_cube_size.Defined())
	{
		printf("!this->m_cube_size.Defined()\n");
		return NULL;
	}

	printf("Start\n");

	GeoColomn * colomn = FindGeoColomn(GeoElement::type::engineer_geological);
	if (!colomn) 
	{
		printf("!colomn\n");
		return NULL;
	}
	for (map<string, GeoElement*>::iterator it = colomn->geo_elements.begin(); it != colomn->geo_elements.end(); it++)
	{		
		if (it->second)
		{		
			if (it->second->m_type == GeoElement::type::engineer_geological)
			{
				EngineerGeoElement * eng = dynamic_cast<EngineerGeoElement *>(it->second);
					
				if (eng)
				{	
					double e;
					bool e_determined = false;
					double gamma_s;
					bool gamma_s_determined = false;
					double gamma_w = 9.8; // удельный вес воды кН/м3
					

					if (eng->GetValue(EngineerGeoElement::ValueType::natural_constitution_porosity_factor,
						EngineerGeoElement::GroundDescriptionType::normative,
						EngineerGeoElement::StrengthDescriptionType::simple,
						e))
					{
						e_determined = true;
					}			

					if (eng->GetValue(EngineerGeoElement::ValueType::specific_gravity_of_ground_particles,
						EngineerGeoElement::GroundDescriptionType::normative,
						EngineerGeoElement::StrengthDescriptionType::simple,
						gamma_s))
					{
						gamma_s_determined = true;
					}			

					if ( e_determined && gamma_s_determined )
					{
						double gamma_susp_in_wat = (gamma_s-gamma_w) / (1.0 + e);
						if (eng->SetValue(EngineerGeoElement::ValueType::specific_gravity_of_suspended_in_water_ground,
							EngineerGeoElement::GroundDescriptionType::normative,
							EngineerGeoElement::StrengthDescriptionType::simple,
							gamma_susp_in_wat))
						{
						}		
					}	
				}
			}
		}
	}
}
bool DetermineSpecificGravity(GeoColomn * colomn, vector <key_z> & vkeyz, int k1, bool use_water_saturation, double & gamma_)
{
	GeoElement * elem = NULL;                    
	EngineerGeoElement * en = NULL;
	if (colomn) elem = colomn->FindGeoElement(vkeyz[k1].key);
	if (elem) en = dynamic_cast<EngineerGeoElement *>(elem);
	if (en)
	{
		 
		bool gamma_determined = false;
		bool WaterSaturation_Checked = en->WaterSaturation_Checked;
		bool ws;

		if	(use_water_saturation && WaterSaturation_Checked)
		{
			LabTrialValueType vt;
			vt.is_result = true;
			vt.m_indication = LabTrial::indication::physical;
			vt.m_lablayer = en->GetLabLayer();
			vt.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_specific_gravity_of_suspended_in_water_ground;
			
			if (en->GetValue(vt, LabNormatives::type::raschotn_95, gamma_))
			{
				gamma_determined = true;
			}
			ws = true;
		}
		else
		{
			LabTrialValueType vt;
			vt.is_result = true;
			vt.m_indication = LabTrial::indication::physical;
			vt.m_lablayer = en->GetLabLayer();
			vt.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_specific_gravity_of_ground;
			
			if (en->GetValue(vt, LabNormatives::type::raschotn_95, gamma_))
			{
				gamma_determined = true;
			}
			ws = false;
		}
		if (!gamma_determined)
		{
			if	(use_water_saturation && WaterSaturation_Checked)
			{
				if (en->GetValue(EngineerGeoElement::ValueType::specific_gravity_of_suspended_in_water_ground,
					EngineerGeoElement::GroundDescriptionType::calculated_on_carry_ability,
					EngineerGeoElement::StrengthDescriptionType::simple,
					gamma_))
				{
					gamma_determined = true;
				}
			}
			else
			{
				if (en->GetValue(EngineerGeoElement::ValueType::specific_gravity_of_ground,
					EngineerGeoElement::GroundDescriptionType::calculated_on_carry_ability,
					EngineerGeoElement::StrengthDescriptionType::simple,
					gamma_))
				{
					gamma_determined = true;
				}
			}
		}
		if (gamma_determined)
		{
			return true;
		}
		else
		{
			if (en->to_print_repeating_warning)
			{
				char str[1024];
				sprintf(str, "Warning: ИГЭ %s удельный вес %s не определён!!!\n", 
					en->GetKey().c_str(),
					ws ? "водонасыщенного " : "");
				AfxMessageBox(str);
				en->to_print_repeating_warning = false;
			}
		}
	}
	else
	{
		printf("Warning: k1 %d specific_gravity_of_ground not determined!!!\n", k1);
	}
	return false;
}
CSandGround::sand_type SandSoilsClass2sand_type(FractionsLabTrialResults::SandSoilsClass sand_soil_class)
{
	CSandGround::sand_type sandtype = CSandGround::sand_type::undefined_sand_type;
	switch(sand_soil_class)
	{
	case FractionsLabTrialResults::SandSoilsClass::valunnyj_or_glubovuj:
		//return "Крупнообломочный валунный (глыбовый)";
	case FractionsLabTrialResults::SandSoilsClass::galechnikovyj_or_schebenistyj:
		//return "Крупнообломочный галечниковый (щебенистый)";
	case FractionsLabTrialResults::SandSoilsClass::gravijnyj_or_dresvyanyj:
		//return "Крупнообломочный гравийный (дресвяной)";

	case FractionsLabTrialResults::SandSoilsClass::gravelistyj:
		//return "Песок гравелистый";
		{
			sandtype = CSandGround::sand_type::gravelic;// Гравелистые
		}
		break;
	case FractionsLabTrialResults::SandSoilsClass::krupnyj:
		//return "Песок крупный";
		{
			sandtype = CSandGround::sand_type::coarse_grained;// крупные
		}
		break;
	case FractionsLabTrialResults::SandSoilsClass::srednej_krupnosti:
		//return "Песок средней крупности";
		{
			sandtype = CSandGround::sand_type::medium_grained;// Средней крупности
		}
		break;
	case FractionsLabTrialResults::SandSoilsClass::melkij:
		//return "Песок мелкий";
		{
			sandtype = CSandGround::sand_type::small_grained;// Мелкие
		}
		break;
	case FractionsLabTrialResults::SandSoilsClass::pylevatyj:
		//return "Песок пылеватый";
		{
			sandtype = CSandGround::sand_type::powdered;// Пылеватые
		}
		break;

	//default:
		//return "";
	}
	return sandtype;
}
CSandGround::sand_strength OcenkaPlotnostiSlozheniaPeska(CSandGround::sand_type sandtype, double e)
{
	CSandGround::sand_strength sandstrength = CSandGround::sand_strength::undefined_sand_strength;
	switch(sandtype)
	{
	case CSandGround::sand_type::gravelic:			// Гравелистые
	case CSandGround::sand_type::coarse_grained:	// Крупные
	case CSandGround::sand_type::medium_grained:	// Средней крупности
		{
			if (e < 0.55)
			{
				sandstrength = CSandGround::sand_strength::dense;
			}
			else if (e >= 0.55 && e <= 0.7)
			{
				sandstrength = CSandGround::sand_strength::medium_dense;
			}
			else if (e > 0.7)
			{
				sandstrength = CSandGround::sand_strength::looses;
			}
		}
		break;
	case CSandGround::sand_type::small_grained:		// Мелкие
		{
			if (e < 0.6)
			{
				sandstrength = CSandGround::sand_strength::dense;
			}
			else if (e >= 0.6 && e <= 0.75)
			{
				sandstrength = CSandGround::sand_strength::medium_dense;
			}
			else if (e > 0.75)
			{
				sandstrength = CSandGround::sand_strength::looses;
			}
		}
		break;
	case CSandGround::sand_type::powdered:			// Пылеватые
		{
			if (e < 0.6)
			{
				sandstrength = CSandGround::sand_strength::dense;
			}
			else if (e >= 0.6 && e <= 0.8)
			{
				sandstrength = CSandGround::sand_strength::medium_dense;
			}
			else if (e > 0.8)
			{
				sandstrength = CSandGround::sand_strength::looses;
			}
		}
		break;
	}
	return sandstrength;
}
bool DetermineBokSceplenieIntegral(double h1, double h2, BuroNabivSvaj::SvaiType svai_type, double v_custom_gamma_cf[4], GeoColomn * colomn, vector <key_z> & vkeyz, int k1, bool use_water_saturation, bool increase_fi_if_dense_sand, bool increase_fi_if_not_porosty_clay, double & integral_gamma_cf_fi_hi)
{
	GeoElement * elem = NULL;                    
	EngineerGeoElement * en = NULL;
	if (colomn) elem = colomn->FindGeoElement(vkeyz[k1].key);
	if (elem) en = dynamic_cast<EngineerGeoElement *>(elem);
	if (en)
	{
		const CGround::ground_type current_ground_type = en->GetGroungType();
		double gamma_cf ;
		bool determined_gamma_cf = GetGammaCF(svai_type, v_custom_gamma_cf, current_ground_type, gamma_cf);

		double f_i_h;
		bool determined_f_i_h = false;

		bool WaterSaturation_Checked = en->WaterSaturation_Checked;
		switch(current_ground_type)
		{
		case CGround::Sand:
			{
				FractionsLabTrialResults::SandSoilsClass sand_soil_class = en->GetSandSoilClass();

				CSandGround::sand_type sandtype = CSandGround::sand_type::undefined_sand_type;
				CSandGround::sand_strength sandstrength = CSandGround::sand_strength::undefined_sand_strength;

				if (sand_soil_class != FractionsLabTrialResults::SandSoilsClass::undefined_sand_soil)
				{
					sandtype = SandSoilsClass2sand_type(sand_soil_class);
					double e;
					double e_determined = en->GetNormativePorostyFactor(e);
					if (e_determined && sandtype != CSandGround::sand_type::undefined_sand_type)
					{
						sandstrength = OcenkaPlotnostiSlozheniaPeska(sandtype, e);
						
						determined_f_i_h = Get_f_i_sand(h1, h2, sandtype, increase_fi_if_dense_sand, sandstrength, f_i_h);
						f_i_h *= 0.1; //  перевод из кПа в тс/м^2
					}
				}				
				else
				{				
					CSand * sand = en->GetSand();
					if(sand)
					{
						sandtype = sand->CSandGround::GetSandType();
						sandstrength = sand->CSandGround::GetSandStrength();

						determined_f_i_h = Get_f_i_sand(h1, h2, sandtype, increase_fi_if_dense_sand, sandstrength, f_i_h);
						f_i_h *= 0.1; //  перевод из кПа в тс/м^2

						//printf("sand f_i_h = %f\n", f_i_h);
					}
				}
				if (sandtype == CSandGround::sand_type::undefined_sand_type)
				{
					if (en->to_print_repeating_warning)
					{
						char str[1024];
						sprintf(str, "Warning: ИГЭ %s тип песка по крупности не определён!!!\n", 
							en->GetKey().c_str());
						MessageBox(0, str, "DetermineBokSceplenieIntegral", 0);
						en->to_print_repeating_warning = false;
					}
				}
				if(sandstrength == CSandGround::sand_strength::undefined_sand_strength)
				{
					if (en->to_print_repeating_warning)
					{
						char str[1024];
						sprintf(str, "Warning: ИГЭ %s тип песка по плотности не определён!!!\n", 
							en->GetKey().c_str());
						MessageBox(0, str, "DetermineBokSceplenieIntegral", 0);
						en->to_print_repeating_warning = false;
					}
				}
			}
			break;
		case CGround::SandyLoam:
		case CGround::Loam:
		case CGround::Clay:
			{
				double e;
				double e_determined = en->GetNormativePorostyFactor(e);

				double IL;
				double IL_determined = en->GetNormativeFluidityIndex(use_water_saturation && WaterSaturation_Checked, IL);

				if (IL_determined && e_determined)
				{
					determined_f_i_h = Get_f_i_clay(h1, h2, IL, current_ground_type, increase_fi_if_not_porosty_clay, e, f_i_h);
					f_i_h *= 0.1; //  перевод из кПа в тс/м^2
					//printf("clay f_i_h = %f\n", f_i_h);
				}
			}
			break;
		}
		 

		if (determined_f_i_h & determined_gamma_cf)
		{
			integral_gamma_cf_fi_hi = gamma_cf * f_i_h;
			return true;
		}
		else
		{
			if (en->to_print_repeating_warning)
			{
				char str[1024];
				sprintf(str, "Warning: ИГЭ %s интеграл бокового сцепления не определён!!!\n", 
					en->GetKey().c_str());
				AfxMessageBox(str);
				en->to_print_repeating_warning = false;
			}
		}
	}
	else
	{
		string skey = vkeyz[k1].key;
		printf("Warning: k1 %d BokSceplenieIntegral not determined!!!\n", k1);
	}
	return false;
}

Cube4D * SurfDoc::SvaiBuroNabivnie(
							   int index_cub_internal_friction_angle,
							   bool use_cub_specific_gravity_of_ground,
							   int index_cub_specific_gravity_of_ground,
							   int index_surface_of_relief,
							   int index_surface_of_rostverk,
							   bool use_rostverk_altituda,
							   double rostverk_altituda,
							   bool use_cub_fluidity_index,
							   int index_cub_fluidity_index,
							   double d,
							   BuroNabivSvaj::SvaiType svai_type, 
							   double v_custom_gamma_cf[4],
							   BuroNabivSvaj::ParamType result_type, 
							   bool use_water_saturation,
							   int index_cub_specific_gravity_of_suspended_in_water_ground,
							   int index_cub_fluidity_index_of_water_saturated_ground,
							   double gamma_k,
							   bool decrease_clay_R_if_porosty,
							   bool increase_fi_if_dense_sand,
							   bool increase_fi_if_not_porosty_clay)
{
	printf(
		"SurfDoc::SvaiBuroNabivnie\n"
		"index_cub_internal_friction_angle = %d\n"
		"index_cub_specific_gravity_of_ground = %d\n"
		"index_surface_of_relief = %d\n"
		"index_surface_of_rostverk = %d\n"
		"index_cub_fluidity_index = %d\n"
		"use_water_saturation = %d\n"
		"index_cub_specific_gravity_of_suspended_in_water_ground = %d\n"
		"index_cub_fluidity_index_of_water_saturated_ground = %d\n"
		,
		index_cub_internal_friction_angle,
		index_cub_specific_gravity_of_ground,
		index_surface_of_relief,
		index_surface_of_rostverk,
		index_cub_fluidity_index,
		use_water_saturation,
		index_cub_specific_gravity_of_suspended_in_water_ground,
		index_cub_fluidity_index_of_water_saturated_ground		
		);

	if (index_cub_internal_friction_angle < 0) return NULL;
	if (use_cub_specific_gravity_of_ground && index_cub_specific_gravity_of_ground < 0) return NULL;
	if (index_surface_of_relief < 0) return NULL;
	if (index_surface_of_rostverk < 0 && !use_rostverk_altituda) return NULL;
	if (use_cub_fluidity_index && index_cub_fluidity_index < 0) return NULL;

	if (use_water_saturation)
	{
		if (use_cub_specific_gravity_of_ground && index_cub_specific_gravity_of_suspended_in_water_ground < 0) return NULL;
		if (use_cub_fluidity_index && index_cub_fluidity_index_of_water_saturated_ground < 0) return NULL;
	}

	if (!this->m_cube_size.Defined())
	{
		printf("!this->m_cube_size.Defined()\n");
		return NULL;
	}


	Cube4D * cube_internal_friction_angle = this->FindCube(index_cub_internal_friction_angle);
	if (!cube_internal_friction_angle) 
	{
		printf("!cube_internal_friction_angle\n");
		return NULL;
	}
	if(!cube_internal_friction_angle->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
	{
		printf("!cube_internal_friction_angle IsTheSameSize(this->m_cube_size)\n");
		this->m_cube_size.Printf();
		cube_internal_friction_angle->lattice.grid4Section.Printf();
		return NULL;
	}

	Cube4D * cube_specific_gravity_of_ground = this->FindCube(index_cub_specific_gravity_of_ground);
	if (use_cub_specific_gravity_of_ground)
	{
		if (!cube_specific_gravity_of_ground) 
		{
			printf("!cube_specific_gravity_of_ground\n");
			return NULL;
		}
		if(!cube_specific_gravity_of_ground->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
		{
			printf("!cube_specific_gravity_of_ground IsTheSameSize(this->m_cube_size)\n");
			this->m_cube_size.Printf();
			cube_specific_gravity_of_ground->lattice.grid4Section.Printf();
			return NULL;
		}
	}

	GeoSurface * surf_of_relief = NULL;
	Grid * grid_of_relief = NULL;

	surf_of_relief = this->FindGeoSurface(index_surface_of_relief);
	if (!surf_of_relief ) 
	{
		printf("!surf_of_relief \n");
		return NULL;
	}
	grid_of_relief = new Grid;
	if (!
		(grid_of_relief 
		&& surf_of_relief->m_surface.MakeGridSection(&grid_of_relief->gridSection)
		&& surf_of_relief->MakeFaultSection(&grid_of_relief->faultSection))
		)
	{
		printf("!Make grid_of_relief \n");
		if (grid_of_relief)
			delete grid_of_relief;
		return NULL;
	}
	double epsilon = 1.0E-6;
	if(!grid_of_relief->gridSection.IsTheSameSize(this->m_cube_size, epsilon))
	{
		printf("!grid_of_relief IsTheSameSize(this->m_cube_size)\n");
		this->m_cube_size.Printf();
		grid_of_relief->gridSection.Printf();


		if (grid_of_relief)
			delete grid_of_relief;
		return NULL;
	}

	GeoSurface * surf_of_rostverk = NULL;
	Grid * grid_of_rostverk = NULL;
	if(!use_rostverk_altituda)
	{
		surf_of_rostverk = this->FindGeoSurface(index_surface_of_rostverk);
		if (!surf_of_rostverk ) 
		{
			printf("!surf_of_rostverk \n");
			return NULL;
		}
		grid_of_rostverk = new Grid;
		if (!
			(grid_of_rostverk 
			&& surf_of_rostverk->m_surface.MakeGridSection(&grid_of_rostverk->gridSection)
			&& surf_of_rostverk->MakeFaultSection(&grid_of_rostverk->faultSection))
			)
		{
			printf("!Make grid_of_rostverk \n");
			if (grid_of_rostverk)
				delete grid_of_rostverk;
			return NULL;
		}
		if(!grid_of_rostverk->gridSection.IsTheSameSize(this->m_cube_size, epsilon))
		{
			printf("!grid_of_rostverk IsTheSameSize(this->m_cube_size)\n");
			this->m_cube_size.Printf();
			grid_of_rostverk->gridSection.Printf();


			if (grid_of_rostverk)
				delete grid_of_rostverk;
			return NULL;
		}
	}	
	Cube4D * cube_fluidity_index = this->FindCube(index_cub_fluidity_index);
	if (use_cub_fluidity_index)
	{
		if (!cube_fluidity_index) 
		{
			printf("!cube_fluidity_index\n");
			return NULL;
		}
		if(!cube_fluidity_index->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
		{
			printf("!cube_fluidity_index IsTheSameSize(this->m_cube_size)\n");
			this->m_cube_size.Printf();
			cube_fluidity_index->lattice.grid4Section.Printf();
			return NULL;
		}
	}

	Cube4D * cub_specific_gravity_of_suspended_in_water_ground = NULL;
	Cube4D * cub_fluidity_index_of_water_saturated_ground = NULL;
	if (use_water_saturation)
	{
		cub_specific_gravity_of_suspended_in_water_ground = this->FindCube(index_cub_specific_gravity_of_suspended_in_water_ground);
		if (use_cub_specific_gravity_of_ground)
		{
			if (!cub_specific_gravity_of_suspended_in_water_ground) 
			{
				printf("!cub_specific_gravity_of_suspended_in_water_ground\n");
				return NULL;
			}
			if(!cub_specific_gravity_of_suspended_in_water_ground->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
			{
				printf("!cub_specific_gravity_of_suspended_in_water_ground IsTheSameSize(this->m_cube_size)\n");
				this->m_cube_size.Printf();
				cub_specific_gravity_of_suspended_in_water_ground->lattice.grid4Section.Printf();
				return NULL;
			}
		}

		cub_fluidity_index_of_water_saturated_ground = this->FindCube(index_cub_fluidity_index_of_water_saturated_ground);
		if (use_cub_fluidity_index)
		{
			if (!cub_fluidity_index_of_water_saturated_ground) 
			{
				printf("!cub_fluidity_index_of_water_saturated_ground\n");
				return NULL;
			}
			if(!cub_fluidity_index_of_water_saturated_ground->lattice.grid4Section.IsTheSameSize(this->m_cube_size))
			{
				printf("!cub_fluidity_index_of_water_saturated_ground IsTheSameSize(this->m_cube_size)\n");
				this->m_cube_size.Printf();
				cub_fluidity_index_of_water_saturated_ground->lattice.grid4Section.Printf();
				return NULL;
			}
		}
	}
		
	GeoColomn * colomn = FindGeoColomn(GeoElement::type::engineer_geological);
	if (!colomn) 
	{
		printf("!colomn\n");
		return NULL;
	}

	double A = (M_PI*d*d/4);
	double u = M_PI * d;

	printf("Start A = %f u = %f\n", A, u);
//	GeoSurfaces_BlankAbove_By_SurfEngGeoElementMapping();
	FillGrids_On_SurfEngGeoElementMapping();

	Grid4 grid4;
	if(!grid4.grid4Section.InitSize(this->m_cube_size)) return NULL;
	grid4.grid4Section.v = Alloc3DMat<double>(grid4.grid4Section.nPag, grid4.grid4Section.nRow, grid4.grid4Section.nCol);

	for (long c = 0; c < this->m_cube_size.nCol; c++)
	{
		for (long r = 0; r < this->m_cube_size.nRow; r++)
		{	
			for (long p = 0; p < this->m_cube_size.nPag; p++)                    
			{					
				grid4.grid4Section.v[p][r][c] = BLANK_VALUE;
			}
		}
	}
				
	vector<key_grid> & kgs = this->surf_eng_geo_element_mapping;

#if 1
	for (vector<surface_order_list_item *>::reverse_iterator 
		rit = GeoSurface::surface_order_list.rbegin();
		rit != GeoSurface::surface_order_list.rend(); rit++)
	{
		if( (*rit) && (*rit)->check)
		{
			string ige_key = FindIGEKey((*rit)->id_surf, kgs);
			GeoElement * element = NULL;                    
			if (colomn)
			{
				element = colomn->FindGeoElement(ige_key);
			}
			EngineerGeoElement * eng = NULL;
			if(element)
				eng = dynamic_cast<EngineerGeoElement *>(element);

			if (eng)
			{
				eng->to_print_repeating_warning = true;
			}
		}
	}
#else
	for (size_t k = 0; k < this->_surf_eng_geo_element_mapping.size(); k++)
	{
		GeoElement * element = NULL;                    
		if (colomn)
		{
			element = colomn->FindGeoElement(this->surf_eng_geo_element_mapping[k].key);
		}
		EngineerGeoElement * eng = NULL;
		if(element)
			eng = dynamic_cast<EngineerGeoElement *>(element);

		if (eng)
		{
			eng->to_print_repeating_warning = true;
		}
	}
#endif

	for (long c = 0; c < this->m_cube_size.nCol; c++)
	{
printf("c = %d %d\n", c, this->m_cube_size.nCol);
		for (long r = 0; r < this->m_cube_size.nRow; r++)
		{	
			///ростверк
			double rostverk_alt;
			bool got_rostverk_alt = false;
			if(use_rostverk_altituda)
			{
				got_rostverk_alt = true;
				rostverk_alt = rostverk_altituda;				
			}
			else
			{
				if(grid_of_rostverk->gridSection.z[r][c] != BLANK_VALUE)
				{
					rostverk_alt = grid_of_rostverk->gridSection.z[r][c];
					got_rostverk_alt = true;
				}
			}


			// природный рельеф

			double relief_alt;
			bool got_relief_alt = false;

			if(grid_of_relief->gridSection.z[r][c] != BLANK_VALUE)
			{
				relief_alt = grid_of_relief->gridSection.z[r][c];
				got_relief_alt = true;
			}


			if (got_rostverk_alt && got_relief_alt)
			{				
				long p_relief = long(floor((relief_alt - this->m_cube_size.zLL) / this->m_cube_size.zSize));

				if (p_relief > this->m_cube_size.nPag - 1)
					p_relief = this->m_cube_size.nPag - 1;

				long p_rostverk = long(floor((rostverk_alt - this->m_cube_size.zLL) / this->m_cube_size.zSize));

				if (p_rostverk > this->m_cube_size.nPag - 1)
					p_rostverk = this->m_cube_size.nPag - 1;

				vector <key_z> vkeyz;
#if 1
				for (vector<surface_order_list_item *>::reverse_iterator 
					rit = GeoSurface::surface_order_list.rbegin();
					rit != GeoSurface::surface_order_list.rend(); rit++)
				{
					if( (*rit) && (*rit)->check)
					{
						string ige_key = FindIGEKey((*rit)->id_surf, kgs);
						if ((*rit)->grid && (*rit)->grid->gridSection.z[r][c] != BLANK_VALUE)
							vkeyz.push_back(key_z(ige_key, (*rit)->grid->gridSection.z[r][c]));
					}
				}
#else
				for (size_t k = 0; k < kgs.size(); k++)
				{
					//printf("k = %d kgs[k].key = %s surfname = %s\t", k, kgs[k].key.c_str(), kgs[k].surfname.c_str());
					if (kgs[k].grid && kgs[k].grid->gridSection.z[r][c] != BLANK_VALUE)
					{
						vkeyz.push_back(key_z(kgs[k].key, kgs[k].grid->gridSection.z[r][c]));
						//printf("z = %f\n", kgs[k].grid->gridSection.z[r][c]); 
					}
					//else
					//	printf("\n");
				}
#endif

				double sum_gamma_h = 0.0;
				double sum_gamma_cf_fi_hi = 0.0;
				for (long p = this->m_cube_size.nPag-1; p >= 0 ; p--)//движение сверху вниз по кубу                    
				{	
					double z = this->m_cube_size.zLL + p * this->m_cube_size.zSize;
					double h = relief_alt - z;

					GeoElement * element = NULL;                    
					EngineerGeoElement * eng = NULL;
					bool eng_not_found = true;
					double gamma_ = 0.0;// specific_gravity of ground (if water saturated then suspended in water)
					if (!use_cub_specific_gravity_of_ground) sum_gamma_h = 0.0;
					for (int k2 = vkeyz.size()-1, k1 = k2-1; k1 >= 0 && eng_not_found; k1--, k2--)//движение сверху вниз по ИГЭ
					{
						double z1 = vkeyz[k1].z;
						double z2 = vkeyz[k2].z;

						if (z1 > z2)
						{
							char str[1024];
							sprintf(str, "(z1 %f (\"%s\") > z2 %f (\"%s\") [%d %d]", 
								z1, vkeyz[k1].key.c_str(), 
								z2, vkeyz[k2].key.c_str(),
								r,c);
							MessageBox(0, str, "SvaiBuroNabivnie", MB_OK);
						}
						else // z2 > z1
						{
							if ( z > z1 && z <= z2)
							{
								if (colomn)
									element = colomn->FindGeoElement(vkeyz[k1].key);

								if (element)
									eng = dynamic_cast<EngineerGeoElement *>(element);	

								eng_not_found = false;

								if (!use_cub_specific_gravity_of_ground)
								{
									if(DetermineSpecificGravity(colomn, vkeyz, k1, use_water_saturation, gamma_))
									{
										sum_gamma_h += gamma_ * (z2 - z);
									}
								}
							}
							else
							{
								if (!use_cub_specific_gravity_of_ground)
								{
									double _gamma_;
									if(DetermineSpecificGravity(colomn, vkeyz, k1, use_water_saturation,  _gamma_))
									{
										sum_gamma_h += _gamma_ * (z2 - z1);
									}
								}
							}
						}
					}

					switch(result_type)
					{
					case BuroNabivSvaj::ParamType::h:
						{
							if (h >= 0)
								grid4.grid4Section.v[p][r][c] = h;
						}
						break;		
					case BuroNabivSvaj::ParamType::h_from_rostverk:
						{
							if ((rostverk_alt - z) >= 0)
								grid4.grid4Section.v[p][r][c] = rostverk_alt - z;
						}
						break;	
					case BuroNabivSvaj::ParamType::V:
						{
							if ((rostverk_alt - z) >= 0)
								grid4.grid4Section.v[p][r][c] = (rostverk_alt - z) * A;
						}
						break;	
					default:
						{
							double R = 0.0;
							bool determined_R = false;
							if (svai_type == BuroNabivSvaj::SvaiType::nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom)
							{
								MessageBox(0,"BuroNabivSvaj::SvaiType::nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom\nyet not realised","SvaiBuroNabivnie",0);
								return NULL;
							}
							else
							{
								if (eng && (eng->GetGround() || eng->GetLabLayer()))
								{
									bool WaterSaturation_Checked = eng->WaterSaturation_Checked;
									if (use_cub_specific_gravity_of_ground)
									{		
										if (
											((!(use_water_saturation && WaterSaturation_Checked)) ? (cube_specific_gravity_of_ground && cube_specific_gravity_of_ground->lattice.grid4Section.v[p][r][c] != BLANK_VALUE) : true)
											&&
											((use_water_saturation && WaterSaturation_Checked) ? (cub_specific_gravity_of_suspended_in_water_ground && cub_specific_gravity_of_suspended_in_water_ground->lattice.grid4Section.v[p][r][c] != BLANK_VALUE) : true)
											)			
										{
											gamma_ = 
												(use_water_saturation && WaterSaturation_Checked) ?
												cub_specific_gravity_of_suspended_in_water_ground->lattice.grid4Section.v[p][r][c]
												:
												cube_specific_gravity_of_ground->lattice.grid4Section.v[p][r][c];
															
											if (p < p_relief)  
											{
												sum_gamma_h += gamma_ * this->m_cube_size.zSize;
											}
										}
									}
									if (result_type == BuroNabivSvaj::ParamType::gamma_)
									{
										grid4.grid4Section.v[p][r][c] = gamma_;
									}
									if (result_type == BuroNabivSvaj::ParamType::sum_gamma_h)
									{
										grid4.grid4Section.v[p][r][c] = sum_gamma_h;
									}
									CGround::ground_type current_ground_type = eng->GetGroungType();
									switch(current_ground_type)
									{
									case CGround::Sand:
										{
											if (cube_internal_friction_angle && cube_internal_friction_angle->lattice.grid4Section.v[p][r][c] != BLANK_VALUE)
											{
												double h_per_d = h/d;
												double fi = cube_internal_friction_angle->lattice.grid4Section.v[p][r][c];
												double alpha1;
												double alpha2;
												GetAlpha12(fi, alpha1, alpha2);
												double alpha3;
												GetAlpha3(fi, h_per_d, alpha3);

												double alpha4;
												GetAlpha4(fi, d, alpha4);
												
												switch(result_type)
												{
												case BuroNabivSvaj::ParamType::h_per_d:
													{
														grid4.grid4Section.v[p][r][c] = h_per_d;
													}
													break;													
												case BuroNabivSvaj::ParamType::alpha1:
													{
														grid4.grid4Section.v[p][r][c] = alpha1;
													}
													break;
												case BuroNabivSvaj::ParamType::alpha2:
													{
														grid4.grid4Section.v[p][r][c] = alpha2;
													}
													break;
												case BuroNabivSvaj::ParamType::alpha3:
													{
														grid4.grid4Section.v[p][r][c] = alpha3;
													}
													break;
												case BuroNabivSvaj::ParamType::alpha4:
													{
														grid4.grid4Section.v[p][r][c] = alpha4;
													}
													break;
												default:
													{
														if (
															result_type != BuroNabivSvaj::ParamType::f_i 
															&&
															result_type != BuroNabivSvaj::ParamType::gamma_cf
															&&
															result_type != BuroNabivSvaj::ParamType::integral_gamma_cf_fi_hi
															&&
															result_type != BuroNabivSvaj::ParamType::sum_gamma_cf_fi_hi
															&&
															result_type != BuroNabivSvaj::ParamType::u_sum_gamma_cf_fi_hi
															)
														{
															R = 0.75 * alpha4 * (alpha1 * gamma_ * d + alpha2 * alpha3 * sum_gamma_h);
															R *= 0.1; //  перевод из кПа в тс/м^2
															determined_R = true;
								                            
															switch(result_type)
															{

															case BuroNabivSvaj::ParamType::R:
																{
																	grid4.grid4Section.v[p][r][c] = R;
																}
																break;
															case BuroNabivSvaj::ParamType::RA:
																{
																	grid4.grid4Section.v[p][r][c] = R * A;
																}
																break;
															}
														}
													}
													break;
												}
											}
										}
										break;
									case CGround::SandyLoam:
									case CGround::Loam:
									case CGround::Clay:
										{
											if (
												result_type != BuroNabivSvaj::ParamType::h_per_d 
												&&
												result_type != BuroNabivSvaj::ParamType::alpha1 
												&&
												result_type != BuroNabivSvaj::ParamType::alpha2 
												&&
												result_type != BuroNabivSvaj::ParamType::alpha3 
												&&
												result_type != BuroNabivSvaj::ParamType::alpha4 
												&&
												result_type != BuroNabivSvaj::ParamType::f_i 
												&&
												result_type != BuroNabivSvaj::ParamType::gamma_cf
												&&
												result_type != BuroNabivSvaj::ParamType::integral_gamma_cf_fi_hi
												&&
												result_type != BuroNabivSvaj::ParamType::sum_gamma_cf_fi_hi
												&&
												result_type != BuroNabivSvaj::ParamType::u_sum_gamma_cf_fi_hi
												)
											{											

												double e; 
												double e_determined = eng->GetNormativePorostyFactor(e);												


												double IL;
												bool IL_determined = false;
												if (use_cub_fluidity_index)
												{		
													if(
														((!(use_water_saturation && WaterSaturation_Checked)) ? (cube_fluidity_index && cube_fluidity_index->lattice.grid4Section.v[p][r][c] != BLANK_VALUE) : true)
														&&
														((use_water_saturation && WaterSaturation_Checked) ? (cub_fluidity_index_of_water_saturated_ground && cub_fluidity_index_of_water_saturated_ground->lattice.grid4Section.v[p][r][c] != BLANK_VALUE) : true)
														)
													{
														IL = 
															(use_water_saturation && WaterSaturation_Checked) ?
															cub_fluidity_index_of_water_saturated_ground->lattice.grid4Section.v[p][r][c]
															:
															cube_fluidity_index->lattice.grid4Section.v[p][r][c];
															IL_determined = true;
													}
												}
												else
												{													
													IL_determined = eng->GetNormativeFluidityIndex(use_water_saturation && WaterSaturation_Checked, IL);
												}


												if (IL_determined && GetClayR(IL, h, R) && e_determined)
												{
													if (decrease_clay_R_if_porosty && e > 0.6)
													{
														//R *= 1.0 - 0.4 * ((e - 0.6) / (1.1 - 0.6));
														R *= 1.0 - 0.8 * (e - 0.6);
													}

													R *= 0.1; //  перевод из кПа в тс/м^2
													determined_R = true;
													switch(result_type)
													{
													case BuroNabivSvaj::ParamType::R:
														{
															grid4.grid4Section.v[p][r][c] = R;
														}
														break;
													case BuroNabivSvaj::ParamType::RA:
														{
															grid4.grid4Section.v[p][r][c] = R * A;
														}
														break;
													}
												}
											}
										}
										break;		
									}
								}
								else
								{
									//printf("c = %d r = %d p = %d z = %f determine_gamma_\t!(eng %x && eng->GetGround() %x)\n", c,r,p,z, eng, eng ? eng->GetGround() : 0);
								}
							}
							if (
								result_type == BuroNabivSvaj::ParamType::f_i ||
								result_type == BuroNabivSvaj::ParamType::gamma_cf ||
								result_type == BuroNabivSvaj::ParamType::integral_gamma_cf_fi_hi ||
								result_type == BuroNabivSvaj::ParamType::sum_gamma_cf_fi_hi ||
								result_type == BuroNabivSvaj::ParamType::u_sum_gamma_cf_fi_hi ||
								result_type == BuroNabivSvaj::ParamType::RA_plus_u_sum_gamma_cf_fi_hi ||
								result_type == BuroNabivSvaj::ParamType::gamma_c ||
								result_type == BuroNabivSvaj::ParamType::Fd ||
								result_type == BuroNabivSvaj::ParamType::Fd_per_V ||
								result_type == BuroNabivSvaj::ParamType::N ||
								result_type == BuroNabivSvaj::ParamType::N_per_V
								)
							{

								double gamma_c = 0.8;
								bool determined_gamma_c = false;
								if (eng && (eng->GetGround() || eng->GetLabLayer()))
								{
									const CGround::ground_type current_ground_type = eng->GetGroungType();

									switch(current_ground_type)
									{
									case CGround::Sand:
										{
											gamma_c = 1.0;
											determined_gamma_c = true;
										}
										break;
									case CGround::SandyLoam:
									case CGround::Loam:
									case CGround::Clay:
										{
											// степень влажности                                           .69	
											//bool degree_of_moisture_defined = eng->GetGround()->normative_description.degree_of_moisture_defined;
											//double degree_of_moisture = eng->GetGround()->normative_description.degree_of_moisture;
											//if (degree_of_moisture_defined)

											bool WaterSaturation_Checked = eng->WaterSaturation_Checked;

											if (use_water_saturation && WaterSaturation_Checked)
											{
												gamma_c = 0.8;
												determined_gamma_c = true;
											}
											else
											{
												double degree_of_moisture;
												if (eng->GetNormativeDegreeOfMoisture(degree_of_moisture))
												{													
													if (degree_of_moisture < 0.9)
														gamma_c = 1.0;
													else
														gamma_c = 0.8;

													determined_gamma_c = true;
												}
											}
										}
										break;
									}
								}
								else
								{
									//printf("c = %d r = %d p = %d z = %f determine_gamma_c\t!(eng %x && eng->GetGround() %x)\n", c,r,p,z, eng, eng ? eng->GetGround() : 0);
								}
								double f_i;
								double gamma_cf; 
								bool determined_f_i = false;
								bool determined_gamma_cf = false;
								if (eng && (eng->GetGround() || eng->GetLabLayer()))
								{
									bool WaterSaturation_Checked = eng->WaterSaturation_Checked;

									const CGround::ground_type current_ground_type = eng->GetGroungType();
									determined_gamma_cf = GetGammaCF(svai_type, v_custom_gamma_cf, current_ground_type, gamma_cf);

									switch(current_ground_type)
									{
									case CGround::Sand:
										{
											FractionsLabTrialResults::SandSoilsClass sand_soil_class = eng->GetSandSoilClass();
											CSandGround::sand_type sandtype = CSandGround::sand_type::undefined_sand_type;
											CSandGround::sand_strength sandstrength = CSandGround::sand_strength::undefined_sand_strength;

											if (sand_soil_class != FractionsLabTrialResults::SandSoilsClass::undefined_sand_soil)
											{
												sandtype = SandSoilsClass2sand_type(sand_soil_class);
												
												double e;
												double e_determined = eng->GetNormativePorostyFactor(e);
												if (e_determined && sandtype != CSandGround::sand_type::undefined_sand_type)
												{
													sandstrength = OcenkaPlotnostiSlozheniaPeska(sandtype, e);
													determined_f_i = Get_f_i_sand(h, sandtype, increase_fi_if_dense_sand, sandstrength, f_i);

													f_i *= 0.1; //  перевод из кПа в тс/м^2
												}
											}				
											else
											{	
												CSand * sand = eng->GetSand();
												if(sand)
												{
													sandtype = sand->CSandGround::GetSandType();
													sandstrength = sand->CSandGround::GetSandStrength();
													determined_f_i = Get_f_i_sand(h, sandtype, increase_fi_if_dense_sand, sandstrength, f_i);

													f_i *= 0.1; //  перевод из кПа в тс/м^2
												}
											}
											if (sandtype == CSandGround::sand_type::undefined_sand_type)
											{
												if (eng->to_print_repeating_warning)
												{
													char str[1024];
													sprintf(str, "Warning: ИГЭ %s тип песка по крупности не определён!!!\n", 
														eng->GetKey().c_str());
																			
													MessageBox(0, str, "Сваи буронабивные", 0);

													eng->to_print_repeating_warning = false;
												}
											}
											if(sandstrength == CSandGround::sand_strength::undefined_sand_strength)
											{
												if (eng->to_print_repeating_warning)
												{
													char str[1024];
													sprintf(str, "Warning: ИГЭ %s тип песка по плотности не определён!!!\n", 
														eng->GetKey().c_str());
													MessageBox(0, str, "Сваи буронабивные", 0);
													eng->to_print_repeating_warning = false;
												}
											}
										}
										break;
									case CGround::SandyLoam:
									case CGround::Loam:
									case CGround::Clay:
										{
											double e;
											double e_determined = eng->GetNormativePorostyFactor(e);

											double IL;
											bool IL_determined = false;
											if (use_cub_fluidity_index)
											{		
												if(
													((!(use_water_saturation && WaterSaturation_Checked)) ? (cube_fluidity_index && cube_fluidity_index->lattice.grid4Section.v[p][r][c] != BLANK_VALUE) : true)
													&&
													((use_water_saturation && WaterSaturation_Checked) ? (cub_fluidity_index_of_water_saturated_ground && cub_fluidity_index_of_water_saturated_ground->lattice.grid4Section.v[p][r][c] != BLANK_VALUE) : true)
													)
												{
													IL = 
														(use_water_saturation && WaterSaturation_Checked) ?
														cub_fluidity_index_of_water_saturated_ground->lattice.grid4Section.v[p][r][c]
														:
														cube_fluidity_index->lattice.grid4Section.v[p][r][c];
														IL_determined = true;
												}
											}
											else
											{
												IL_determined = eng->GetNormativeFluidityIndex(use_water_saturation && WaterSaturation_Checked, IL);
											}											
												
											if (IL_determined && e_determined)
											{
												determined_f_i = Get_f_i_clay(h, IL, current_ground_type, increase_fi_if_not_porosty_clay, e, f_i);
												
												f_i *= 0.1; //  перевод из кПа в тс/м^2
											}
										}
										break;
									}
								}	
								else
								{
									//printf("c = %d r = %d p = %d z = %f determine_f_i_gamma_cf\t!(eng %x && eng->GetGround() %x)\n", c,r,p,z, eng, eng ? eng->GetGround() : 0);
								}
								if (use_cub_fluidity_index)
								{
									if (p == p_rostverk && determined_gamma_cf && determined_f_i)
									{
										sum_gamma_cf_fi_hi += gamma_cf * f_i * (rostverk_alt - (this->m_cube_size.zLL + p_rostverk * this->m_cube_size.zSize));
									}									
									if (p < p_rostverk && determined_gamma_cf && determined_f_i)
									{
										sum_gamma_cf_fi_hi += gamma_cf * f_i * this->m_cube_size.zSize;
									}	

									//else
									//{
										//if (!(determined_gamma_cf && determined_f_i))
										//{
										//	if (!determined_gamma_cf)
										//	{
										//		printf("!determined_gamma_cf\tc = %d r = %d p = %d z = %f\n", c,r,p,z);
										//	}
										//	if (!determined_f_i)
										//	{
										//		printf("!determined_f_i\tc = %d r = %d p = %d z = %f\n", c,r,p,z);
										//	}
										//}
									//}
								}
								else
								{									
									sum_gamma_cf_fi_hi = 0.0;
									bool en_not_found = true;
									bool rostverk_found = false;
									if ( rostverk_alt > z )
									{		
										for (int k2 = vkeyz.size()-1, k1 = k2-1; k1 >= 0 && en_not_found; k1--, k2--)//движение сверху вниз по ИГЭ
										{
											double z1 = vkeyz[k1].z;
											double z2 = vkeyz[k2].z;

											if (z1 > z2)
											{
												char str[1024];
												sprintf(str, "(z1 %f (\"%s\") > z2 %f (\"%s\") [%d %d]", 
													z1, vkeyz[k1].key.c_str(), 
													z2, vkeyz[k2].key.c_str(),
													r,c);
												MessageBox(0, str, "SvaiBuroNabivnie", MB_OK);
											}
											else // z2 > z1 --> h2 < h1 - for integral надо менять местами
											{
												if ( z > z1 && z <= z2) en_not_found = false;

												double integral_gamma_cf_fi_hi;
												bool determined_integral_gamma_cf_fi_hi = false;
												if ( rostverk_alt > z1 && rostverk_alt <= z2)
												{ 
													if ( z > z1 && z <= z2)
													{	
														if (DetermineBokSceplenieIntegral(relief_alt - rostverk_alt, relief_alt - z, svai_type, v_custom_gamma_cf, colomn, vkeyz, k1, use_water_saturation, increase_fi_if_dense_sand, increase_fi_if_not_porosty_clay, integral_gamma_cf_fi_hi))
														{
															sum_gamma_cf_fi_hi += integral_gamma_cf_fi_hi;
															determined_integral_gamma_cf_fi_hi = true;
														}
													}
													else
													{	
														if (DetermineBokSceplenieIntegral(relief_alt - rostverk_alt, relief_alt - z1, svai_type, v_custom_gamma_cf, colomn, vkeyz, k1, use_water_saturation, increase_fi_if_dense_sand, increase_fi_if_not_porosty_clay, integral_gamma_cf_fi_hi))
														{
															sum_gamma_cf_fi_hi += integral_gamma_cf_fi_hi;
															determined_integral_gamma_cf_fi_hi = true;
														}
													}
													rostverk_found = true;
												}
												else
												{
													if (rostverk_found)
													{
														if ( z > z1 && z <= z2)
														{	
															if (DetermineBokSceplenieIntegral(relief_alt - z2, relief_alt - z, svai_type, v_custom_gamma_cf, colomn, vkeyz, k1, use_water_saturation, increase_fi_if_dense_sand, increase_fi_if_not_porosty_clay, integral_gamma_cf_fi_hi))
															{
																sum_gamma_cf_fi_hi += integral_gamma_cf_fi_hi;
																determined_integral_gamma_cf_fi_hi = true;
															}
														}
														else
														{
															if (DetermineBokSceplenieIntegral(relief_alt - z2, relief_alt - z1, svai_type, v_custom_gamma_cf, colomn, vkeyz, k1, use_water_saturation, increase_fi_if_dense_sand, increase_fi_if_not_porosty_clay, integral_gamma_cf_fi_hi))
															{
																sum_gamma_cf_fi_hi += integral_gamma_cf_fi_hi;
																determined_integral_gamma_cf_fi_hi = true;
															}
														}
													}
												}
												if ( result_type == BuroNabivSvaj::ParamType::integral_gamma_cf_fi_hi)
												{
													if (determined_integral_gamma_cf_fi_hi)
														grid4.grid4Section.v[p][r][c] = integral_gamma_cf_fi_hi;
												}												
											}
										}
									}
								}
								switch(result_type)
								{
								case BuroNabivSvaj::ParamType::f_i:
									{
										if (determined_f_i)
											grid4.grid4Section.v[p][r][c] = f_i;
									}
									break;	
								case BuroNabivSvaj::ParamType::gamma_cf:
									{
										if (determined_gamma_cf)
											grid4.grid4Section.v[p][r][c] = gamma_cf;
									}
									break;	
								case BuroNabivSvaj::ParamType::sum_gamma_cf_fi_hi:
									{
										if (sum_gamma_cf_fi_hi > 0.0)
											grid4.grid4Section.v[p][r][c] = sum_gamma_cf_fi_hi;
									}
									break;	

								case BuroNabivSvaj::ParamType::u_sum_gamma_cf_fi_hi:
									{
										if (sum_gamma_cf_fi_hi > 0.0)
											grid4.grid4Section.v[p][r][c] = u * sum_gamma_cf_fi_hi;
									}
									break;	
								case BuroNabivSvaj::ParamType::RA_plus_u_sum_gamma_cf_fi_hi:
									{
										if (determined_R && rostverk_alt > z )
											grid4.grid4Section.v[p][r][c] = R * A + u * sum_gamma_cf_fi_hi;
									}
									break;	
								case BuroNabivSvaj::ParamType::gamma_c:
									{
										if (determined_gamma_c)
											grid4.grid4Section.v[p][r][c] = gamma_c;
									}
									break;
								case BuroNabivSvaj::ParamType::Fd:
									{
										if (determined_R && determined_gamma_c && rostverk_alt > z )
											grid4.grid4Section.v[p][r][c] = gamma_c * (R * A + u * sum_gamma_cf_fi_hi);
									}
									break;
								case BuroNabivSvaj::ParamType::Fd_per_V:
									{
										if (determined_R && determined_gamma_c && rostverk_alt > z )
											grid4.grid4Section.v[p][r][c] = gamma_c * (R * A + u * sum_gamma_cf_fi_hi) / ((rostverk_alt - z) * A);
									}
									break;
								case BuroNabivSvaj::ParamType::N:
									{
										if (determined_R && determined_gamma_c && rostverk_alt > z )
											grid4.grid4Section.v[p][r][c] = gamma_c * (R * A + u * sum_gamma_cf_fi_hi) / gamma_k;
									}
									break;
								case BuroNabivSvaj::ParamType::N_per_V:
									{
										if (determined_R && determined_gamma_c && rostverk_alt > z )
											grid4.grid4Section.v[p][r][c] = gamma_c * (R * A + u * sum_gamma_cf_fi_hi) / (gamma_k * (rostverk_alt - z) * A);
									}
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	char cube_name[4098];
	switch(result_type)
	{
	case BuroNabivSvaj::ParamType::h_per_d:
	case BuroNabivSvaj::ParamType::V:
	case BuroNabivSvaj::ParamType::alpha4:
		{
			sprintf(cube_name, "%s  d=%1.1f", 
				BuroNabivSvaj::ParamTypeToString(result_type), 
				d);
		}
		break;
	case BuroNabivSvaj::ParamType::h:
	case BuroNabivSvaj::ParamType::h_from_rostverk:
	case BuroNabivSvaj::ParamType::alpha1:
	case BuroNabivSvaj::ParamType::alpha2:
	case BuroNabivSvaj::ParamType::alpha3:
		{
			sprintf(cube_name, "%s", BuroNabivSvaj::ParamTypeToString(result_type));
		}
		break;
	case BuroNabivSvaj::ParamType::gamma_:
	case BuroNabivSvaj::ParamType::sum_gamma_h:
		{
			sprintf(cube_name, "%s  water_sat=%d", 
				BuroNabivSvaj::ParamTypeToString(result_type), 
				use_water_saturation);
		}
		break;
	case BuroNabivSvaj::ParamType::R:
		{
			if (use_rostverk_altituda)
			{
				sprintf(cube_name, "%s  %s  d=%1.1f  water_sat=%d rostverk = %0.1f cub_fluid=%d cub_grav=%d decr_clay_R=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation, 
					rostverk_altituda,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty);
			}
			else
			{
				sprintf(cube_name, "%s  %s  d=%1.1f  water_sat=%d cub_fluid=%d cub_grav=%d decr_clay_R=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty);
			}
		}
		break;
	case BuroNabivSvaj::ParamType::RA:
		{
			if (use_rostverk_altituda)
			{
				sprintf(cube_name, "%s  %s  d=%1.1f  water_sat=%d rostverk = %0.1f cub_fluid=%d cub_grav=%d decr_clay_R=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation, 
					rostverk_altituda,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty);
			}
			else
			{
				sprintf(cube_name, "%s  %s  d=%1.1f  water_sat=%d cub_fluid=%d cub_grav=%d decr_clay_R=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty);
			}
		}
		break;
	case BuroNabivSvaj::ParamType::f_i:
		{
			sprintf(cube_name, "%s  water_sat=%d cub_fluid=%d incr_fi_sand=%d incr_fi_clay=%d", 
				BuroNabivSvaj::ParamTypeToString(result_type), 
				use_water_saturation,
				use_cub_fluidity_index, 
				increase_fi_if_dense_sand, 
				increase_fi_if_not_porosty_clay);
		}
		break;
	case BuroNabivSvaj::ParamType::sum_gamma_cf_fi_hi:
	case BuroNabivSvaj::ParamType::u_sum_gamma_cf_fi_hi:
		{
			if (use_rostverk_altituda)
			{
				sprintf(cube_name, "%s  %s  water_sat=%d rostverk = %0.1f cub_fluid=%d cub_grav=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					use_water_saturation,
					rostverk_altituda,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground, 
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);			
			}
			else
			{
				sprintf(cube_name, "%s  %s  water_sat=%d cub_fluid=%d cub_grav=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					use_water_saturation,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground, 
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
		}
		break;
	case BuroNabivSvaj::ParamType::RA_plus_u_sum_gamma_cf_fi_hi:
		{
			if (use_rostverk_altituda)
			{
				sprintf(cube_name, "%s  %s  d=%1.1f water_sat=%d rostverk = %0.1f cub_fluid=%d cub_grav=%d decr_clay_R=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation, 
					rostverk_altituda,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty,
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
			else
			{
				sprintf(cube_name, "%s  %s  d=%1.1f water_sat=%d cub_fluid=%d cub_grav=%d decr_clay_R=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty,
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
		}
		break;
	case BuroNabivSvaj::ParamType::gamma_c:
		{
			sprintf(cube_name, "%s  water_sat=%d", 
				BuroNabivSvaj::ParamTypeToString(result_type), 
				use_water_saturation);
		}
		break;
	case BuroNabivSvaj::ParamType::Fd:
	case BuroNabivSvaj::ParamType::Fd_per_V:
		{
			if (use_rostverk_altituda)
			{
				sprintf(cube_name, "%s  %s  d=%1.1f water_sat=%d rostverk = %0.1f cub_fluid=%d cub_grav=%d decr_clay_R=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					rostverk_altituda,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty,
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
			else
			{
				sprintf(cube_name, "%s  %s  d=%1.1f water_sat=%d cub_fluid=%d cub_grav=%d decr_clay_R=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty,
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
		}
		break;
	case BuroNabivSvaj::ParamType::N:
	case BuroNabivSvaj::ParamType::N_per_V:
		{
			if (use_rostverk_altituda)
			{
				sprintf(cube_name, "%s  %s  d=%1.1f  water_sat=%d rostverk = %0.1f gamma_k = %1.1f cub_fluid=%d cub_grav=%d decr_clay_R=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					rostverk_altituda,
					gamma_k,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty,
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
			else
			{
				sprintf(cube_name, "%s  %s  d=%1.1f  water_sat=%d gamma_k = %1.1f cub_fluid=%d cub_grav=%d decr_clay_R=%d incr_fi_sand=%d incr_fi_clay=%d", 
					BuroNabivSvaj::ParamTypeToString(result_type), 
					BuroNabivSvaj::SvaiTypeToString(svai_type, v_custom_gamma_cf),
					d, 
					use_water_saturation,
					gamma_k,
					use_cub_fluidity_index,
					use_cub_specific_gravity_of_ground,
					decrease_clay_R_if_porosty,
					increase_fi_if_dense_sand, 
					increase_fi_if_not_porosty_clay);
			}
		}
		break;
	default:
		{
			sprintf(cube_name, "%s", BuroNabivSvaj::ParamTypeToString(result_type));
		}
	}

	Cube4D * cube = this->AddCube(&grid4, cube_name, 0);
	if (cube)
	{
		cube->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
		cube->Draw();
		cube->AddItem_ToTree(this->hwndTV, m_cubes_ObjectList.myTreeItem);
		project* pr = dynamic_cast<project*>(this);
		if(pr)pr->UpdateAllViews();
	}
	if (grid_of_relief )
		delete grid_of_relief;
	if (grid_of_rostverk )
		delete grid_of_rostverk;

	FreeGrids_On_SurfEngGeoElementMapping();

	return cube;
}
#if !VIEW_ONLY_VERSION
bool SurfDoc::AddAutoBuildProfile()
{
	AutoBuildProfile auto_build_profile(this);
	this->m_auto_build_profiles.AddMsg(&auto_build_profile);
	//this->m_auto_build_profiles.GetLastMsg().m_surface.Init();
	//this->m_auto_build_profiles.GetLastMsg().SetName(szPath);
	if (this->m_auto_build_profiles.GetLastMsg().init())
	{
		this->m_auto_build_profiles_ObjectList.Init(this->m_auto_build_profiles, this);

		//this->m_auto_build_profiles.GetLastMsg().Zooming();
		//this->m_auto_build_profiles.GetLastMsg().Draw();
		return true;
	}
	else
	{
		this->m_auto_build_profiles.EraseLastMsg();
		return false;
	}
}

bool SurfDoc::AddAutoBuildProfile1()
{
	AutoBuildProfile auto_build_profile(this);
	this->m_auto_build_profiles.AddMsg(&auto_build_profile);
	//this->m_auto_build_profiles.GetLastMsg().m_surface.Init();
	//this->m_auto_build_profiles.GetLastMsg().SetName(szPath);
	if (this->m_auto_build_profiles.GetLastMsg().init1())
	{
		this->m_auto_build_profiles_ObjectList.Init(this->m_auto_build_profiles, this);

		//this->m_auto_build_profiles.GetLastMsg().Zooming();
		//this->m_auto_build_profiles.GetLastMsg().Draw();
		return true;
	}
	else
	{
		this->m_auto_build_profiles.EraseLastMsg();
		return false;
	}
}

#endif /*#if !VIEW_ONLY_VERSION*/


size_t SurfDoc::AddSurf(long id_surf, BYTE podoshva, int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible, COLORREF color )
{
	size_t ret = 0;
	if (zflag == 0)
	{
		GeoSurface surface(this);
		ret = m_surfaces.AddMsg(&surface);
		m_surfaces.GetLastMsg().m_surface.Init(zflag,x,y,z,visible,color);
		m_surfaces.GetLastMsg().SetName(szPath);
		m_surfaces_ObjectList.Init(m_surfaces, this);

		m_surfaces.GetLastMsg().id_surf = id_surf;
		m_surfaces.GetLastMsg().podoshva = podoshva;

		this->AddSurfaceOrder(true, id_surf, podoshva, szPath, true);
		this->AddSurfaceBlankOrder(id_surf, podoshva, szPath, true);
	}
	if (zflag == 1 || zflag == 2 || zflag == 3)
	{
		if (zflag == 3) 
			zflag = 0;

		GeoSurface surface(this);
		ret = m_faults.AddMsg(&surface);
		m_faults.GetLastMsg().m_surface.Init(zflag,x,y,z,visible,color);
		m_faults.GetLastMsg().SetName(szPath);
		m_faults_ObjectList.Init(m_faults, this);
	}
	return ret;
}


/*void SurfDoc::AddGeoSurf(int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible, COLORREF color )
{
	if (zflag == 0)
	{
		GeoSurface surface(this);
		m_geo_surfaces.AddMsg(&surface);
		m_geo_surfaces.GetLastMsg().Init(zflag,x,y,z,visible,color);
		m_geo_surfaces_ObjectList.Init(m_geo_surfaces);
	}
	if (zflag == 1 || zflag == 2)
	{
		GeoSurface surface(this);
		m_geo_faults.AddMsg(&surface);
		m_geo_faults.GetLastMsg().Init(zflag,x,y,z,visible,color);
		m_geo_faults_ObjectList.Init(m_geo_faults);
	}
}*/

void SurfDoc::AddString(CPoint3 pt, char *s, COLORREF color, double vshift )
{
	String3D str(this);
	m_strings.AddMsg(&str);
	m_strings.GetLastMsg().Init(pt, s, color, vshift);
	m_strings_ObjectList.Init(m_strings, this);
}
bool SurfDoc::SetExtremums_ByKarotazhy(double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz)
{
	int index = -1;
	vector<CPoint3> vptmax,vptmin;
	for (vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
					it != Well_3D::karotazh_list.end(); it++)
	{
		index++;
		double min_x, min_y, min_z, max_x, max_y, max_z;
		this->GetKarotazhCube(index, min_x, min_y, min_z, max_x, max_y, max_z);
		if (min_x != DBL_MAX && min_y != DBL_MAX && min_z != DBL_MAX &&
			max_x != -DBL_MAX && max_y != -DBL_MAX && max_z != -DBL_MAX)
		{
			vptmax.push_back(CPoint3(max_x,max_y,max_z));
			vptmin.push_back(CPoint3(min_x,min_y,min_z));
		}
	}			
	// temp cube object
	Cube4D cube;
	bool result = cube.Object::UpdateExtremums(vptmax, vptmin);
	if (result)
	{
		minx = cube.GetMin().x ;
		miny = cube.GetMin().y ;
		minz = cube.GetMin().z ;
		
		maxx = cube.GetMax().x ;
		maxy = cube.GetMax().y ;
		maxz = cube.GetMax().z ;
	}

	return result;

}
bool SurfDoc::SetExtremums_ByGriddata(double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz)
{
	vector<CPoint3> vptmax,vptmin;
	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_grid_data.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_grid_data.GetCurrentMsg().GetMax());
				vptmin.push_back(m_grid_data.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}
	// temp cube object
	Cube4D cube;
	bool result = cube.Object::UpdateExtremums(vptmax, vptmin);
	if (result)
	{
		minx = cube.GetMin().x ;
		miny = cube.GetMin().y ;
		minz = cube.GetMin().z ;
		
		maxx = cube.GetMax().x ;
		maxy = cube.GetMax().y ;
		maxz = cube.GetMax().z ;
	}

	return result;

}
#if 0
void SurfDoc::AddSurf(SURFER7GRID grid, vdouble& visible){}
#endif

bool SurfDoc::UpdateExtremums()
{
printf( "UpdateExtremums\n");

	vector<CPoint3> vptmax,vptmin;
	// ищем экстремумы по всем векторам из документов линий и поверхностей

	int i = 0;

	if (this->m_cube_size.Defined())
	{
		vptmax.push_back(CPoint3(this->m_cube_size.xMax(), this->m_cube_size.yMax(), this->m_cube_size.zMax()));
		vptmin.push_back(CPoint3(this->m_cube_size.xLL, this->m_cube_size.yLL, this->m_cube_size.zLL));
	}


	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_objects.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_objects.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_objects.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_collections.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_collections.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_collections.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	//*****************************************************************
	if (this->m_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_polygones.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_polygones.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_polygones.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_polygones.IncrementCurrentMsg());
	}

	if (this->m_triangles.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_triangles.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_triangles.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_triangles.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_triangles.IncrementCurrentMsg());
	}


	if (this->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_spheres.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_spheres.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_spheres.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_spheres.IncrementCurrentMsg());
	}

printf("UpdateExtremums pre m_bitmaps\n");
	if (this->m_bitmaps.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_bitmaps.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_bitmaps.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_bitmaps.GetCurrentMsg().GetMin());

/*				CPoint3 pt3 = this->m_bitmaps.GetCurrentMsg().GetMin();
printf("minx = %f miny = %f minz = %f\n", pt3.x, pt3.y, pt3.z);
				pt3 = this->m_bitmaps.GetCurrentMsg().GetMax();
printf("maxx = %f maxy = %f maxz = %f\n", pt3.x, pt3.y, pt3.z);*/
			}
		}
		while(this->m_bitmaps.IncrementCurrentMsg());
	}
printf("UpdateExtremums post m_bitmaps\n");

printf("UpdateExtremums pre m_bmp_profiles\n");
	if (this->m_bmp_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_bmp_profiles.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_bmp_profiles.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_bmp_profiles.GetCurrentMsg().GetMin());

				/*CPoint3 pt3 = this->m_bmp_profiles.GetCurrentMsg().GetMin();
printf("minx = %f miny = %f minz = %f\n", pt3.x, pt3.y, pt3.z);
				pt3 = this->m_bmp_profiles.GetCurrentMsg().GetMax();
printf("maxx = %f maxy = %f maxz = %f\n", pt3.x, pt3.y, pt3.z);*/
			}
		}
		while(this->m_bmp_profiles.IncrementCurrentMsg());
	}
printf("UpdateExtremums post m_bmp_profiles\n");

	if (this->m_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_points.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_points.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_points.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_points.IncrementCurrentMsg());
	}

	if (this->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_tria_grid.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_tria_grid.GetCurrentMsg().GetMax());
				vptmin.push_back(m_tria_grid.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_tria_grid.IncrementCurrentMsg());
	}


#if BROKEN_PLANE_VECTOR_TYPE
	if (this->m_brokenPlanes.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_brokenPlanes.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_brokenPlanes.GetCurrentMsg().GetMax());
				vptmin.push_back(m_brokenPlanes.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_brokenPlanes.IncrementCurrentMsg());
	}
#else
	vector<BrokenPlane3D>::iterator iter_bp;
	for (iter_bp = this->m_brokenPlanes.begin(); iter_bp != this->m_brokenPlanes.end();iter_bp++)
	{
		if (iter_bp->UpdateExtremums())
		{
			vptmax.push_back(iter_bp->GetMax());
			vptmin.push_back(iter_bp->GetMin());
		}
	}
#endif

	if (this->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_cutlines.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_cutlines.GetCurrentMsg().GetMax());
				vptmin.push_back(m_cutlines.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_cutlines.IncrementCurrentMsg());
	}
/*
	if (this->m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_blanklines.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_blanklines.GetCurrentMsg().GetMax());
				vptmin.push_back(m_blanklines.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_blanklines.IncrementCurrentMsg());
	}
*/
	if (this->m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_strings.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_strings.GetCurrentMsg().GetMax());
				vptmin.push_back(m_strings.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_strings.IncrementCurrentMsg());
	}
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_drills.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_drills.GetCurrentMsg().GetMax());
				vptmin.push_back(m_drills.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_lines.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_lines.GetCurrentMsg().GetMax());
				vptmin.push_back(m_lines.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_lines.IncrementCurrentMsg());
	}


	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_grid_data.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_grid_data.GetCurrentMsg().GetMax());
				vptmin.push_back(m_grid_data.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}

	if (this->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_cubes.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_cubes.GetCurrentMsg().GetMax());
				vptmin.push_back(m_cubes.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_cubes.IncrementCurrentMsg());
	}


#if DFX_LAYER_FROM_OBJECT
	if (this->m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_dxfConverters.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_dxfConverters.GetCurrentMsg().GetMax());
				vptmin.push_back(m_dxfConverters.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_dxfConverters.IncrementCurrentMsg());
	}
#endif
	if (this->m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_auto_build_profiles.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_auto_build_profiles.GetCurrentMsg().GetMax());
				vptmin.push_back(m_auto_build_profiles.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_auto_build_profiles.IncrementCurrentMsg());
	}
	if (this->m_grid_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_grid_profiles.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_grid_profiles.GetCurrentMsg().GetMax());
				vptmin.push_back(m_grid_profiles.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_grid_profiles.IncrementCurrentMsg());
	}

	if (this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_bln_profiles.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_bln_profiles.GetCurrentMsg().GetMax());
				vptmin.push_back(m_bln_profiles.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}

	// исходя из того что алгоритмы построения поверхностей иногда зашкаливают в "небеса"
	// не учитываем поверхности при расчёте экстремумов, если экстремумы можно расчитать по другим объектам
	if (vptmax.size() == 0 || vptmin.size() == 0)
	{
		// а если таки кроме поверхностей в модели ничего нет, тогда рискуем и ищем экстремумы на основании поверхностей 
		printf("UpdateExtremums pre m_surfaces\n");
		if (this->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{
				if (m_surfaces.GetCurrentMsg().UpdateExtremums())
				{
					vptmax.push_back(m_surfaces.GetCurrentMsg().GetMax());
					vptmin.push_back(m_surfaces.GetCurrentMsg().GetMin());

	/*CPoint3 pt3 = this->m_surfaces.GetCurrentMsg().GetMin();
	printf("minx = %f miny = %f minz = %f\n", pt3.x, pt3.y, pt3.z);
	pt3 = this->m_surfaces.GetCurrentMsg().GetMax();
	printf("maxx = %f maxy = %f maxz = %f\n", pt3.x, pt3.y, pt3.z);*/
				}
			}
			while(this->m_surfaces.IncrementCurrentMsg());
		}
	printf("UpdateExtremums post m_surfaces\n");
		if (this->m_faults.SetCurrentMsgOnFirst())
		{
			do
			{
				if (m_faults.GetCurrentMsg().UpdateExtremums())
				{
					vptmax.push_back(m_faults.GetCurrentMsg().GetMax());
					vptmin.push_back(m_faults.GetCurrentMsg().GetMin());
				}
			}
			while(this->m_faults.IncrementCurrentMsg());
		}
		if (this->m_geo_catches.SetCurrentMsgOnFirst())
		{
			do
			{
				if (m_geo_catches.GetCurrentMsg().UpdateExtremums())
				{
					vptmax.push_back(m_geo_catches.GetCurrentMsg().GetMax());
					vptmin.push_back(m_geo_catches.GetCurrentMsg().GetMin());
				}
			}
			while(this->m_geo_catches.IncrementCurrentMsg());
		}
	}



	bool result = this->Object::UpdateExtremums(vptmax, vptmin);

	if(!result)
	{
		m_fRangeY = 1.0;
		m_fRangeX = 1.0;
		m_fRangeZ = 1.0;

		m_xd_min = 0 ;
		m_yd_min = 0 ;
		m_zd_min = 0 ;

		m_xd_max = 1.0 ;
		m_yd_max = 1.0 ;
		m_zd_max = 1.0 ;

		return false;
	}


	//?????====== Вычисление размаха изображаемого объекта
	m_fRangeY = double(this->m_ptMax.y - this->m_ptMin.y);
	m_fRangeX = double(this->m_ptMax.x - this->m_ptMin.x);
	m_fRangeZ = double(this->m_ptMax.z - this->m_ptMin.z);


	m_xd_min = this->m_ptMin.x ;
	m_yd_min = this->m_ptMin.y ;
	m_zd_min = this->m_ptMin.z ;

	m_xd_max = this->m_ptMax.x ;
	m_yd_max = this->m_ptMax.y ;
	m_zd_max = this->m_ptMax.z ;

	return result;

printf( "UpdateExtremums end\n");
}
void SurfDoc::ClearCutlinesPolygones()
{
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().ClearCutlinesPolygones();
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().ClearCutlinesPolygones();
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if(this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_geo_catches.GetCurrentMsg().ClearCutlinesPolygones();
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}
}
void SurfDoc::ZoomViewCutlinesPolygones()
{
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().ZoomViewCutlinesPolygones(
						m_zoomX,m_zoomY,m_zoomZ, 
						m_xd_zoom_center,
						m_yd_zoom_center,
						m_zd_zoom_center
						);	
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}	
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().ZoomViewCutlinesPolygones(
						m_zoomX,m_zoomY,m_zoomZ, 
						m_xd_zoom_center,
						m_yd_zoom_center,
						m_zd_zoom_center
						);	
		}
		while(this->m_faults.IncrementCurrentMsg());
	}	
	if(this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_geo_catches.GetCurrentMsg().ZoomViewCutlinesPolygones(
						m_zoomX,m_zoomY,m_zoomZ, 
						m_xd_zoom_center,
						m_yd_zoom_center,
						m_zd_zoom_center
						);	
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}
}


void SurfDoc::DrawCutPlaneLines()
{
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().DrawCutPlaneLines();
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}	
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().DrawCutPlaneLines();
		}
		while(this->m_faults.IncrementCurrentMsg());
	}	
	if(this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_geo_catches.GetCurrentMsg().DrawCutPlaneLines();
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}
}
void SurfDoc::Cutting()
{
	if (this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_profiles.GetCurrentMsg().Cutting();
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}
	this->ZoomView();
	this->UpdateAllViews();
}
void SurfDoc::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{


	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	//************************************************************
	if (this->m_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_polygones.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_polygones.IncrementCurrentMsg());
	}

	if (this->m_triangles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_triangles.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_triangles.IncrementCurrentMsg());
	}

	if (this->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_spheres.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_spheres.IncrementCurrentMsg());
	}

	if (this->m_bitmaps.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bitmaps.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_bitmaps.IncrementCurrentMsg());
	}


	if (this->m_bmp_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bmp_profiles.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_bmp_profiles.IncrementCurrentMsg());
	}

	if (this->m_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_points.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_points.IncrementCurrentMsg());
	}

	if (this->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			m_tria_grid.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_tria_grid.IncrementCurrentMsg());
	}


#if BROKEN_PLANE_VECTOR_TYPE
	if (this->m_brokenPlanes.SetCurrentMsgOnFirst())
	{
		do
		{
			m_brokenPlanes.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_brokenPlanes.IncrementCurrentMsg());
	}
#else
	vector<BrokenPlane3D>::iterator iter_bp;
	for (iter_bp = this->m_brokenPlanes.begin(); iter_bp != this->m_brokenPlanes.end();iter_bp++)
	{
		 iter_bp->Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
	}
#endif
	if (this->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cutlines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_cutlines.IncrementCurrentMsg());
	}
	if (this->m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_blanklines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_blanklines.IncrementCurrentMsg());
	}
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	if (this->m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			m_strings.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_strings.IncrementCurrentMsg());
	}
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}

	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			m_surfaces.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}

	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			m_faults.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}

	if (this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			m_geo_catches.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}		
	
	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			m_grid_data.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}
	
	if (this->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cubes.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_cubes.IncrementCurrentMsg());
	}

#if DFX_LAYER_FROM_OBJECT
	if (this->m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			m_dxfConverters.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_dxfConverters.IncrementCurrentMsg());
	}
#endif
	if (this->m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			m_auto_build_profiles.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_auto_build_profiles.IncrementCurrentMsg());
	}

	if (this->m_grid_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			m_grid_profiles.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_grid_profiles.IncrementCurrentMsg());
	}

	if (this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_profiles.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}


}


void SurfDoc::ZoomView(bool started)
{
printf( "ZoomView\n");
	if(!UpdateExtremums())
		return;
//MessageBox(0, "2", "ZoomView", 0);
	//====== Подготовка к циклу пробега по буферу
	//====== и процессу масштабирования
	double xd = 0, yd = 0, zd = 0, xv, yv, zv;
	Document2ViewCoordinates(xd, yd, zd, xv, yv, zv, started);

	m_xd_zoom_center = (m_xd_min + m_xd_max) / 2.0;
	m_yd_zoom_center = (m_yd_min + m_yd_max) / 2.0;
	m_zd_zoom_center = (m_zd_min + m_zd_max) / 2.0;

	this->Zoom(m_zoomX, m_zoomY, m_zoomZ, 
		m_xd_zoom_center, m_yd_zoom_center, m_zd_zoom_center);

	m_xv_min = m_zoomX * (m_xd_min - m_xd_zoom_center);
	m_yv_min = m_zoomY * (m_yd_min - m_yd_zoom_center);
	m_zv_min = m_zoomZ * (m_zd_min - m_zd_zoom_center);

	m_xv_max = m_zoomX * (m_xd_max - m_xd_zoom_center);
	m_yv_max = m_zoomY * (m_yd_max - m_yd_zoom_center);
	m_zv_max = m_zoomZ * (m_zd_max - m_zd_zoom_center);
printf( "ZoomView end\n");
}
#include "drawscene.h"
extern void InitSphere(int nlist, int alpha);

void SurfDoc::Draw()
{
	printf("SurfDoc::Draw()\n");
							
	

	this->InitObjectsLayerPointers();
	this->FillLayerList();

	DrawListArray::glDeleteLists();

	// http:gamedev.ru -> nehe.com.ru
	// ramazanoff@univer.kharkov.ua

	//====== Включаемаем необходимость учета света
	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем необходимость учета света
	//====== Включаемаем необходимость учета света
	
	
	TreeView_DeleteAllItems(this->hwndTV);

	AddGeoColomnsToTree(this->hwndTV, this);

	DrawCollections(this);
	DrawObjects(this);

	DrawCubes(this);
	DrawSurfs(this);
	DrawFaults(this);
	DrawGeoCatches(this);
	DrawGridData(this);
	DrawAutoBuildProfiles(this);
#if DFX_LAYER_FROM_OBJECT
	DrawDxf(this);
#endif
	DrawTriangles(this );
	DrawPolygones(this );

	DrawBrokenPlanes(this);
	DrawTriaGrid(this);

	DrawGridProfiles(this);
	DrawBlnProfiles(this);

	DrawDrills(this);
	DrawLines(this);
	DrawCutLines(this);
	DrawBlankLines(this);
	DrawSpheres(this);
	DrawPoints(this);
	DrawBitmaps(this);
	DrawBmpProfiles(this);

	DrawStrings(this);

	if (this->m_bDrawGeoid)
		InitSphere(4, this->m_alpha);

	if (this->m_bDrawCube)
		DrawCube(this);

	if (this->m_bDrawCutPlane )
	{
		DrawCutPlane(this);
	}
	if (this->m_bDrawXYZCutPlanes )
	{
		DrawXYZCutPlanes(this);
	}
//	printf("DrawScene 1\n");
//	this->m_DrawListArray.BuildListArray();
//	printf("DrawScene 2\n");
//	InitTreeViewItems(this->hwndTV, this);
	printf("SurfDoc::Draw() end\n");
}


void SurfDoc::UpdateAllViews()
{
	project * prj = dynamic_cast<project *>(this);
	if(prj)
	{
		prj->UpdateAllViews();
	}
}
void SurfDoc::UpdateAllGraphicsViews()
{
	project * prj = dynamic_cast<project *>(this);
	if(prj)
	{
		prj->UpdateAllGraphicsViews();
	}
}
void SurfDoc::UpdateAllMapViews()
{
	project * prj = dynamic_cast<project *>(this);
	if(prj)
	{
		prj->UpdateAllMapViews();
	}
}
void SurfDoc::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) )
{
	//*********************************************************************************
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	//*********************************************************************************
	if (this->m_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_polygones.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_polygones.IncrementCurrentMsg());
	}

	if (this->m_triangles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_triangles.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_triangles.IncrementCurrentMsg());
	}

	if (this->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_spheres.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_spheres.IncrementCurrentMsg());
	}

	if (this->m_bitmaps.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bitmaps.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_bitmaps.IncrementCurrentMsg());
	}


	if (this->m_bmp_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bmp_profiles.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_bmp_profiles.IncrementCurrentMsg());
	}

	if (this->m_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_points.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_points.IncrementCurrentMsg());
	}

	if (this->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			m_tria_grid.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_tria_grid.IncrementCurrentMsg());
	}


#if BROKEN_PLANE_VECTOR_TYPE
	if (this->m_brokenPlanes.SetCurrentMsgOnFirst())
	{
		do
		{
			m_brokenPlanes.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_brokenPlanes.IncrementCurrentMsg());
	}
#else
	vector<BrokenPlane3D>::iterator iter_bp;
	for (iter_bp = this->m_brokenPlanes.begin(); iter_bp != this->m_brokenPlanes.end();iter_bp++)
	{
		 iter_bp->.EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
	}
#endif
	if (this->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cutlines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_cutlines.IncrementCurrentMsg());
	}
	if (this->m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_blanklines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_blanklines.IncrementCurrentMsg());
	}
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	if (this->m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			m_strings.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_strings.IncrementCurrentMsg());
	}
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}

	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			m_surfaces.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}

	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			m_faults.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}

	if (this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			m_geo_catches.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}


	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			m_grid_data.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}

	if (this->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cubes.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_cubes.IncrementCurrentMsg());
	}

#if DFX_LAYER_FROM_OBJECT
	if (this->m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			m_dxfConverters.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_dxfConverters.IncrementCurrentMsg());
	}
#endif
	if (this->m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			m_auto_build_profiles.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_auto_build_profiles.IncrementCurrentMsg());
	}

	if (this->m_grid_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			m_grid_profiles.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_grid_profiles.IncrementCurrentMsg());
	}

	if (this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_profiles.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}


	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
bool SurfDoc::IsSelectedGridDataPoint(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws, GridData *&pGridData)
{

	// последний чтобы точки не мешали выбирать другие объекты
	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_grid_data.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				pGridData = &this->m_grid_data.GetCurrentMsg();
				return true;
			}
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}
	return false;
}

bool SurfDoc::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);
	// первый чаще всего редактируем блн профили
	if (this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bln_profiles.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}



	//*****************************************************************************
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_objects.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws))
			{
				return true;
			}
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_collections.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws))
			{
				return true;
			}
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	//*****************************************************************************
	if (this->m_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_polygones.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws))
			{
				return true;
			}
		}
		while(this->m_polygones.IncrementCurrentMsg());
	}

	if (this->m_triangles.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_triangles.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_triangles.IncrementCurrentMsg());
	}

	if (this->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_spheres.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_spheres.IncrementCurrentMsg());
	}

	if (this->m_bitmaps.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bitmaps.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_bitmaps.IncrementCurrentMsg());
	}


	if (this->m_bmp_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bmp_profiles.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_bmp_profiles.IncrementCurrentMsg());
	}

	if (this->m_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_points.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_points.IncrementCurrentMsg());
	}

	if (this->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_tria_grid.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_tria_grid.IncrementCurrentMsg());
	}


#if BROKEN_PLANE_VECTOR_TYPE
	if (this->m_brokenPlanes.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_brokenPlanes.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_brokenPlanes.IncrementCurrentMsg());
	}
#else
	vector<BrokenPlane3D>::iterator iter_bp;
	for (iter_bp = this->m_brokenPlanes.begin(); iter_bp != this->m_brokenPlanes.end();iter_bp++)
	{
			if(iter_bp->IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
	}
#endif
	if (this->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_cutlines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_cutlines.IncrementCurrentMsg());
	}
	if (this->m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blanklines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_blanklines.IncrementCurrentMsg());
	}
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_drills.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	if (this->m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_strings.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_strings.IncrementCurrentMsg());
	}
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_lines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_lines.IncrementCurrentMsg());
	}

	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_surfaces.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}

	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_faults.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_faults.IncrementCurrentMsg());
	}

	if (this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_geo_catches.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}

#if DFX_LAYER_FROM_OBJECT
	if (this->m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_dxfConverters.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_dxfConverters.IncrementCurrentMsg());
	}
#endif
	if (this->m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_auto_build_profiles.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_auto_build_profiles.IncrementCurrentMsg());
	}

	if (this->m_grid_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_grid_profiles.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_grid_profiles.IncrementCurrentMsg());
	}

	// последний чтобы точки не мешали выбирать другие объекты
	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_grid_data.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}

	if (this->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_cubes.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_cubes.IncrementCurrentMsg());
	}

	return false;
}


void SurfDoc::ClearObjects()
{
	TreeView_DeleteMyItem(this->hwndTV, m_objects_ObjectList.myTreeItem);
	m_objects.clear();
	m_objects_ObjectList.clear();
	this->ZoomView();
}


void SurfDoc::ClearCollections()
{
	TreeView_DeleteMyItem(this->hwndTV, m_collections_ObjectList.myTreeItem);
	m_collections.clear();
	m_collections_ObjectList.clear();
	this->ZoomView();
}


void SurfDoc::ClearSurf()
{
	TreeView_DeleteMyItem(this->hwndTV, m_surfaces_ObjectList.myTreeItem);
	m_surfaces.clear();
	m_surfaces_ObjectList.clear();
	this->ZoomView();

	GeoSurface::surface_order_list.clear();
	GeoSurface::surface_blank_order_list.clear();

	if (this->m_pLabDoc)
	{
		if (IDYES == MessageBox(0, "Удалить также ссылки на поверхности из списков очерёдности в базе данных", "ClearSurf", MB_YESNO))
		{
			this->m_pLabDoc->ClearSurfacesOrder(this->id_obj);
			this->m_pLabDoc->ClearSurfacesBlankOrder(this->id_obj);
			this->m_pLabDoc->ClearGridDataUsedAlgorothms(this->id_obj);
		}
	}
}


void SurfDoc::ClearFaults()
{
	TreeView_DeleteMyItem(this->hwndTV, m_faults_ObjectList.myTreeItem);
	m_faults.clear();
	m_faults_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearGeoCatches()
{
	TreeView_DeleteMyItem(this->hwndTV, m_geo_catches_ObjectList.myTreeItem);
	m_geo_catches.clear();
	m_geo_catches_ObjectList.clear();
	this->ZoomView();
}
#if DFX_LAYER_FROM_OBJECT

void SurfDoc::ClearDxf()
{
	TreeView_DeleteMyItem(this->hwndTV, m_dxfConverters_ObjectList.myTreeItem);
	m_dxfConverters.clear();
	m_dxfConverters_ObjectList.clear();
	this->ZoomView();
}
#endif

void SurfDoc::ClearGridData()
{
	TreeView_DeleteMyItem(this->hwndTV, m_grid_data_ObjectList.myTreeItem);
	m_grid_data.clear();
	m_grid_data_ObjectList.clear();
	this->ZoomView();

	if (this->m_pLabDoc)
	{
		if (IDYES == MessageBox(0, "Удалить также гриддату и из базы данных", "ClearGridData", MB_YESNO))
		{
			this->m_pLabDoc->ClearGridData(this->id_obj);
			this->m_pLabDoc->ClearSurfIgeMapping(this->id_obj);	
			this->m_pLabDoc->ClearSurfLitoMapping(this->id_obj);	
		}
	}
	this->surf_eng_geo_element_mapping.clear();
	this->surf_litho_geo_element_mapping.clear();
}


void SurfDoc::ClearGeoColomns()
{
	TreeView_DeleteMyItem(this->hwndTV, m_geo_colomns_ObjectList.myTreeItem);
	m_geo_colomns.clear();
	m_geo_colomns_ObjectList.clear();
}

void SurfDoc::ClearCubes()
{
	TreeView_DeleteMyItem(this->hwndTV, m_cubes_ObjectList.myTreeItem);
	m_cubes.clear();
	m_cubes_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearAutoBuildProfiles()
{
	TreeView_DeleteMyItem(this->hwndTV, m_auto_build_profiles_ObjectList.myTreeItem);
	m_auto_build_profiles.clear();
	m_auto_build_profiles_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearTriangles()
{
	TreeView_DeleteMyItem(this->hwndTV, m_triangles_ObjectList.myTreeItem);
	m_triangles.clear();
	m_triangles_ObjectList.clear();
//	this->ZoomView();
}
void SurfDoc::ClearPoligones()
{
	TreeView_DeleteMyItem(this->hwndTV, m_polygones_ObjectList.myTreeItem);
	this->m_polygones.clear();
	this->m_polygones_ObjectList.clear();
//	this->ZoomView();
}

void SurfDoc::AddTriangle(CPoint3 v1, CPoint3 v2, CPoint3 v3, COLORREF color)
{
printf("SurfDoc::AddTriangle\n");
	Triangle3 tri;
	tri.v1 = v1;
	tri.v2 = v2;
	tri.v3 = v3;

	printf( "[%f %f %f %d]\n", v1.x, v1.y, v1.z, v1.bVisible);
	printf( "[%f %f %f %d]\n", v2.x, v2.y, v2.z, v2.bVisible);
	printf( "[%f %f %f %d]\n", v3.x, v3.y, v3.z, v3.bVisible);

	Triangle3D poly(this);
	m_triangles.AddMsg(&poly);
//	m_triangles.GetLastMsg().InitDoc((SurfDoc * )this);
	m_triangles.GetLastMsg().Init(tri,color);
	m_triangles_ObjectList.Init(m_triangles, this);
}
void SurfDoc::AddPoligon(vdouble &vx, vdouble &vy, vdouble &vz, COLORREF color)
{
	Poligon3D poly(this);
	m_polygones.AddMsg(&poly);
	m_polygones.GetLastMsg().Init(vx,vy,vz,color);
	m_polygones_ObjectList.Init(m_polygones, this);
}
void SurfDoc::ClearCutLines()
{
printf("SurfDoc::ClearCutLines()\n");
	TreeView_DeleteMyItem(this->hwndTV, m_cutlines_ObjectList.myTreeItem);
	m_cutlines.clear();
	m_cutlines_ObjectList.clear();
//	this->ZoomView();
}
void SurfDoc::ClearBlankLines()
{
printf("SurfDoc::ClearBlankLines()\n");
	TreeView_DeleteMyItem(this->hwndTV, m_blanklines_ObjectList.myTreeItem);
	m_blanklines.clear();
	m_blanklines_ObjectList.clear();
//	this->ZoomView();
}
void SurfDoc::ClearLines()
{
printf("SurfDoc::ClearLines()\n");
	TreeView_DeleteMyItem(this->hwndTV, m_lines_ObjectList.myTreeItem);
	m_lines.clear();
	m_lines_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearStrings()
{
	TreeView_DeleteMyItem(this->hwndTV, m_strings_ObjectList.myTreeItem);
	m_strings.clear();
	m_strings_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearBlnProfiles()
{
	TreeView_DeleteMyItem(this->hwndTV, this->m_bln_profiles_ObjectList.myTreeItem);
	this->m_bln_profiles.clear();
	this->m_bln_profiles_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearDrills()
{
	TreeView_DeleteMyItem(this->hwndTV, m_drills_ObjectList.myTreeItem);
	m_drills.clear();
	m_drills_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearKarotazhList()
{
	Well_3D::karotazh_list.clear();
	this->ZoomView();
}

void SurfDoc::ClearKarotazhy()
{
	Well_3D::karotazh_list.clear();
	if (this->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_drills.GetCurrentMsg().ClearKarotazhy();
		}
		while(this->m_drills.IncrementCurrentMsg());
	}
	this->ZoomView();
}

void SurfDoc::ClearSpheres()
{
	TreeView_DeleteMyItem(this->hwndTV, m_spheres_ObjectList.myTreeItem);
	m_spheres.clear();
	m_spheres_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearBitmaps()
{
	TreeView_DeleteMyItem(this->hwndTV, m_bitmaps_ObjectList.myTreeItem);
	m_bitmaps.clear();
	m_bitmaps_ObjectList.clear();
	this->ZoomView();
}
void SurfDoc::ClearBmpProfiles()
{
	TreeView_DeleteMyItem(this->hwndTV, m_bmp_profiles_ObjectList.myTreeItem);
	m_bmp_profiles.clear();
	m_bmp_profiles_ObjectList.clear();
	this->ZoomView();
}

void SurfDoc::ClearPoints()
{
	TreeView_DeleteMyItem(this->hwndTV, m_points_ObjectList.myTreeItem);
	m_points.clear();
	m_points_ObjectList.clear();
	this->ZoomView();
}

Cube4D * SurfDoc::AddCube(Grid4 *pgrid)
{
	return AddCube(pgrid, szPath, RGB(255,255,0));
}
Cube4D * SurfDoc::AddCube(Grid4 *pgrid, COLORREF color)
{
	return AddCube(pgrid, szPath, color);
}
Cube4D * SurfDoc::AddCube(Grid4 *pgrid, const char * name, COLORREF color)
{
	if (pgrid)
	{
		Cube4D cube(this);
		m_cubes.AddMsg(&cube);
		m_cubes.GetLastMsg().Init(&pgrid->grid4Section,color);
		m_cubes.GetLastMsg().SetName(name);
		m_cubes_ObjectList.Init(m_cubes, this);
		return &m_cubes.GetLastMsg();
	}
	return NULL;
}
Cube4D * SurfDoc::AddThinCube(Grid4 *pgrid)
{
	return AddThinCube(pgrid, szPath, RGB(255,255,0));
}
Cube4D * SurfDoc::AddThinCube(Grid4 *pgrid, COLORREF color)
{
	return AddThinCube(pgrid, szPath, color);
}
Cube4D * SurfDoc::AddThinCube(Grid4 *pgrid, const char * name, COLORREF color)
{
	if (pgrid)
	{
		Cube4D cube(this);
		m_cubes.AddMsg(&cube);
		m_cubes.GetLastMsg().InitThin(&pgrid->grid4Section,color);
		m_cubes.GetLastMsg().SetName(name);
		m_cubes_ObjectList.Init(m_cubes, this);
		return &m_cubes.GetLastMsg();
	}
	return NULL;
}
#if FAST_GRID_LOADING

size_t SurfDoc::AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, Grid *pgrid)
{
	//AddSurf(zflag, pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible );
	return AddSurf(id_surf, podoshva, id_ige, zflag, pgrid, RGB(255,255,0));
}
size_t SurfDoc::AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, Grid *pgrid, COLORREF color)
{
	return AddSurf(id_surf, podoshva, id_ige, zflag, pgrid, color, szPath);
}
size_t SurfDoc::AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, Grid *pgrid, COLORREF color, const char * name)
{
	size_t ret = 0;
	//AddSurf(zflag,pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible, color );		
	if (zflag == 0)
	{
		GeoSurface surface(this);
		ret = m_surfaces.AddMsg(&surface);
		m_surfaces.GetLastMsg().Init(id_surf, podoshva, id_ige, zflag,pgrid,color);
		m_surfaces.GetLastMsg().SetName(name);
		m_surfaces_ObjectList.Init(m_surfaces, this);

		this->AddSurfaceOrder(true, id_surf, podoshva, name, true);
		this->AddSurfaceBlankOrder(id_surf, podoshva, name, true);
	}
	if (zflag == 1 || zflag == 2 || zflag == 3)
	{
		if (zflag == 3) 
			zflag = 0;

		GeoSurface surface(this);
		ret = m_faults.AddMsg(&surface);
		m_faults.GetLastMsg().Init(id_surf, podoshva, -1, zflag,pgrid,color);
		m_faults.GetLastMsg().SetName(name);
		m_faults_ObjectList.Init(m_faults, this);
	}
	return ret;
}

#else

void SurfDoc::AddSurf(int zflag, CGrid *pCGrid)
{
	AddSurf(zflag, pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible );
}
void SurfDoc::AddSurf(int zflag, CGrid *pCGrid, COLORREF color)
{
	AddSurf(zflag,pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible, color );
}
#endif
int SurfDoc::GetExtremums(double& fMinX, double& fMaxX, double& fMinY, double& fMaxY,double& fMinZ, double& fMaxZ )
{
	// ищем экстремумы по всем векторам из документов линий и поверхностей
	fMinX = 	m_xd_min ;
	fMinY = 	m_yd_min ;
	fMinZ = 	m_zd_min ;

	fMaxX = 	m_xd_max ;
	fMaxY = 	m_yd_max ;
	fMaxZ = 	m_zd_max ;

	return 0;
}


int SurfDoc::Document2ViewCoordinates(double xd, double yd, double zd, double &xv, double &yv, double &zv, bool started)
{
	//?????====== Вычисление размаха изображаемого объекта
	double	range, zoomX, zoomY, zoomZ;
	//====== Масштабирование ординат
	range = 4.f;
	zoomZ = m_zd_max > m_zd_min ? range/(m_zd_max-m_zd_min)
									 : 1.f;
	//====== Масштабирование ординат
	range = 4.f;
	zoomY = m_yd_max > m_yd_min ? range/(m_yd_max-m_yd_min)
									 : 1.f;
	//====== Масштабирование ординат
	range = 4.f;
	zoomX = m_xd_max > m_xd_min ? range/(m_xd_max-m_xd_min)
									 : 1.f;

	double minZoom = zoomZ;
	if (minZoom > zoomX) minZoom = zoomX;
	if (minZoom > zoomY) minZoom = zoomY;
	
	if (m_bEqialZoomXYZ)
	{
		m_zoomX = minZoom;
		m_zoomY = minZoom;
		m_zoomZ = minZoom;
	}
	else if (m_bEqialZoomXY)
	{
		m_zoomX = minZoom;
		m_zoomY = minZoom;

		if (started)
			m_zoomZ = m_zoomCoefXYZ * m_zoomX;
	}
	else
	{
		m_zoomX = minZoom;
		m_zoomY = m_zoomX * m_zoomCoefXY;
		m_zoomZ = m_zoomX * m_zoomCoefXYZ;
	}

	m_zoomXY = m_zoomX;

	xv = m_zoomX * (xd - m_xd_zoom_center);
	yv = m_zoomY * (yd - m_yd_zoom_center);
	zv = m_zoomZ * (zd - m_zd_zoom_center);


	return 0;
}
int SurfDoc::Document2ViewXCoordinates(double xd, double &xv)
{
	double yd = 0, zd = 0, yv, zv;
	return Document2ViewCoordinates(xd, yd, zd, xv, yv, zv);
}

int SurfDoc::Document2ViewYCoordinates(double yd, double &yv)
{
	double xd = 0, zd = 0, xv, zv;
	return Document2ViewCoordinates(xd, yd, zd, xv, yv, zv);
}

int SurfDoc::Document2ViewZCoordinates(double zd, double &zv)
{
	double xd = 0, yd = 0, xv, yv;
	return Document2ViewCoordinates(xd, yd, zd, xv, yv, zv);
}

int compareX( const void *arg1, const void *arg2 )
{
   /* Compare X: */
   double 
	   x1 = (( CPoint3* ) arg1)->x,
	   x2 = (( CPoint3* ) arg2)->x;
   if (x1 < x2)
	   return -1;
   if (x1 == x2)
	   return 0;
   if (x1 > x2)
	   return 1;
   return 0;
}

int compareY( const void *arg1, const void *arg2 )
{
   /* Compare Y: */
   double 
	   y1 = (( CPoint3* ) arg1)->y,
	   y2 = (( CPoint3* ) arg2)->y;
   if (y1 < y2)
	   return -1;
   if (y1 == y2)
	   return 0;
   if (y1 > y2)
	   return 1;
   return 0;
}

int compareZ( const void *arg1, const void *arg2 )
{
   /* Compare X: */
   double 
	   z1 = (( CPoint3* ) arg1)->z,
	   z2 = (( CPoint3* ) arg2)->z;
   if (z1 < z2)
	   return -1;
   if (z1 == z2)
	   return 0;
   if (z1 > z2)
	   return 1;
   return 0;
}


void SurfDoc::CutProfile(double a, double b, double c, double d, bool toDrawPoligones, bool positive, bool useCutLines )
{
#if 0
	this->ClearTriangles();
	this->ClearPoligones();

	if (
		
		this->m_vGridProfiles.SetCurrentVectOnFirst() &&
		this->m_vGridProfilesXSize.SetCurrentMsgOnFirst() &&
		this->m_vGridProfilesYSize.SetCurrentMsgOnFirst() && 
		this->m_vmax_grid_profile_v.SetCurrentMsgOnFirst() &&
		this->m_vmin_grid_profile_v.SetCurrentMsgOnFirst()
		)
	{
		int s = 0;
		do
		{
			COLORREF color = m_vSurfColor.GetCurrentMsg();
			this->CreateNewTrianglesLayer(color);
			//====== Размеры изображаемого объекта
			UINT	nx = this->m_vGridProfilesXSize.GetCurrentMsg()-1,
					ny = this->m_vGridProfilesYSize.GetCurrentMsg()-1;
			int zflag = this->m_vzflag.GetCurrentMsg();


			int len = m_vGridProfiles.GetCurrentVect().GetCurrentMsgLen();
			CPoint3 *ptd;
			ptd = m_vGridProfiles.GetCurrentVect().GetCurrentMsgPtr();
			Cutting(ny, nx, len, ptd, a, b, c, d, toDrawPoligones, positive, useCutLines, color);
			s++;
		}
		while(this->m_vGridProfiles.IncrementCurrentVect()
			&& this->m_vGridProfilesXSize.IncrementCurrentMsg()
			&& this->m_vGridProfilesYSize.IncrementCurrentMsg()
			&& this->m_vmax_grid_profile_v.IncrementCurrentMsg()
			&& this->m_vmin_grid_profile_v.IncrementCurrentMsg()
			);
	}
	CutLine( useCutLines );
#endif
}
void SurfDoc::CutSave(bool toDrawTriaAndPoligones, bool positive)
{
//	m_cutlines.clear();
//	CutSurfs(m_a, m_b, m_c, m_d,toDrawTriaAndPoligones, positive , 1, 0);
	CutlineSaveAsRazres(
		m_cut_plane_d[0],	
		m_cut_plane_d[1],
		m_cut_plane_d[2],
		m_cut_plane_d[3]);
}
void SurfDoc::Cut(bool toDrawTriaAndPoligones, bool positive)
{
printf("SurfDoc::Cut()\n");
	CutSurfs(
		m_cut_plane_d[0],	
		m_cut_plane_d[1],
		m_cut_plane_d[2],
		m_cut_plane_d[3], 
		toDrawTriaAndPoligones, positive, 1, 0);
	CutFaults(
		m_cut_plane_d[0],	
		m_cut_plane_d[1],
		m_cut_plane_d[2],
		m_cut_plane_d[3], 
		toDrawTriaAndPoligones, positive, 1, 0);
	CutGeoCatches(
		m_cut_plane_d[0],	
		m_cut_plane_d[1],
		m_cut_plane_d[2],
		m_cut_plane_d[3], 
		toDrawTriaAndPoligones, positive, 1, 0);
printf("SurfDoc::Cut) end\n");
}
void SurfDoc::CutSurfs(double a, double b, double c, double d, 
				  bool toDrawPoligones, bool positive, 
				  short type_of_cutline, int cutting_number, 
		CPoint2* pt1, CPoint2* pt2 , void * pBrokenPlane)
{
//printf("SurfDoc::CutSurfs()\n");
	this->ClearTriangles();
	this->ClearPoligones();
#if 1
	int surf_number = 0;
	for (vector<surface_order_list_item *>::iterator 
		it = GeoSurface::surface_order_list.begin();
		it != GeoSurface::surface_order_list.end(); it++)
	{
		if ((*it) && (*it)->check)
		{
			GeoSurface * current = this->FindGeoSurface((*it)->id_surf);
			if (current)
			{
				current->m_surface.Cutting(a, b, c, d, 
					toDrawPoligones, positive, 
					type_of_cutline, cutting_number, surf_number, 
					pt1, pt2, pBrokenPlane, 
					current, &current->m_blank_polygon_matrix,
					&current->m_cutplane_polygones_ObjectList, &current->m_cutplane_polygones);
				
				current->m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  *current, surf_number );
				if (pBrokenPlane) 
				{
					if ( surf_number < ((BrokenPlane3D *) pBrokenPlane)->m_broken_lines.Size() )
					{
						((BrokenPlane3D *) pBrokenPlane)->m_broken_lines[surf_number].id_umpoz = current->id_umpoz;
						((BrokenPlane3D *) pBrokenPlane)->m_broken_lines[surf_number].id_ige = current->id_ige;
						((BrokenPlane3D *) pBrokenPlane)->m_broken_lines[surf_number].podoshva = current->podoshva;
						//((BrokenPlane3D *) pBrokenPlane)->m_polySloi[surf_number].id_umpoz = current->id_umpoz;
					}
				}
				surf_number++;
			}
		}
	}
#else
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		int surf_number = 0;
		do
		{
			m_surfaces.GetCurrentMsg().m_surface.Cutting(a, b, c, d, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, (void *) &m_surfaces.GetCurrentMsg());

			m_surfaces.GetCurrentMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  (void *) &m_surfaces.GetCurrentMsg(), surf_number );

			((BrokenPlane3D *) pBrokenPlane)->m_broken_lines[surf_number].id_umpoz = m_surfaces.GetCurrentMsg().id_umpoz;
			//((BrokenPlane3D *) pBrokenPlane)->m_polySloi[surf_number].id_umpoz = m_surfaces.GetCurrentMsg().id_umpoz;
			
			surf_number++;
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
#endif
//	CutLine( type_of_cutline, cutting_number, pBrokenPlane );
//printf("SurfDoc::CutSurfs() end\n");
}

void SurfDoc::CutFaults(double a, double b, double c, double d, 
				  bool toDrawPoligones, bool positive, 
				  short type_of_cutline, int cutting_number, 
		CPoint2* pt1, CPoint2* pt2 , void * pBrokenPlane)
{
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		int surf_number = 0;
		do
		{
			m_faults.GetCurrentMsg().m_surface.Cutting(a, b, c, d, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, 
				&m_faults.GetCurrentMsg(), 
				&m_faults.GetCurrentMsg().m_blank_polygon_matrix,
				&m_faults.GetCurrentMsg().m_cutplane_polygones_ObjectList, 
				&m_faults.GetCurrentMsg().m_cutplane_polygones);
			m_faults.GetCurrentMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  m_faults.GetCurrentMsg(), surf_number );

			surf_number++;
		}
		while(m_faults.IncrementCurrentMsg());
	}
}



void SurfDoc::CutGeoCatches(double a, double b, double c, double d, 
				  bool toDrawPoligones, bool positive, 
				  short type_of_cutline, int cutting_number, 
		CPoint2* pt1, CPoint2* pt2 , void * pBrokenPlane)
{
	if (this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			m_geo_catches.GetCurrentMsg().Cut(a, b, c, d, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, 
				pt1, pt2, pBrokenPlane);
		}
		while(m_geo_catches.IncrementCurrentMsg());
	}
}
	//minimums needs
bool SurfDoc::GetExtremums_of_Surfaces_and_Faults(
	double& minX, double& minY, double& minZ,
	double& maxX, double& maxY, double& maxZ,
	bool use_only_cutplane_lines)
{

	vector<CPoint3> vptmax,vptmin;
	if (use_only_cutplane_lines)
	{
		if(this->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{
				if(this->m_surfaces.GetCurrentMsg().m_cutplane_lines.SetCurrentMsgOnFirst())
				{
					do
					{
						if(this->m_surfaces.GetCurrentMsg().m_cutplane_lines.GetCurrentMsg().UpdateExtremums())
						{
							vptmax.push_back(this->m_surfaces.GetCurrentMsg().m_cutplane_lines.GetCurrentMsg().GetMax());
							vptmin.push_back(this->m_surfaces.GetCurrentMsg().m_cutplane_lines.GetCurrentMsg().GetMin());
						}
					}
					while(this->m_surfaces.GetCurrentMsg().m_cutplane_lines.IncrementCurrentMsg());
				}		
			}
			while(this->m_surfaces.IncrementCurrentMsg());
		}
		if(this->m_faults.SetCurrentMsgOnFirst())
		{
			do
			{
				if(this->m_faults.GetCurrentMsg().m_cutplane_lines.SetCurrentMsgOnFirst())
				{
					do
					{
						if(this->m_faults.GetCurrentMsg().m_cutplane_lines.GetCurrentMsg().UpdateExtremums())
						{
							vptmax.push_back(this->m_faults.GetCurrentMsg().m_cutplane_lines.GetCurrentMsg().GetMax());
							vptmin.push_back(this->m_faults.GetCurrentMsg().m_cutplane_lines.GetCurrentMsg().GetMin());
						}
					}
					while(this->m_faults.GetCurrentMsg().m_cutplane_lines.IncrementCurrentMsg());
				}
			}
			while(this->m_faults.IncrementCurrentMsg());
		}
	}
	else
	{
		if(this->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{

				if(this->m_surfaces.GetCurrentMsg().m_surface.UpdateExtremums())
				{
					vptmax.push_back(this->m_surfaces.GetCurrentMsg().m_surface.GetMax());
					vptmin.push_back(this->m_surfaces.GetCurrentMsg().m_surface.GetMin());
				}
	
			}
			while(this->m_surfaces.IncrementCurrentMsg());
		}
		if(this->m_faults.SetCurrentMsgOnFirst())
		{
			do
			{
				if(this->m_faults.GetCurrentMsg().m_surface.UpdateExtremums())
				{
					vptmax.push_back(this->m_faults.GetCurrentMsg().m_surface.GetMax());
					vptmin.push_back(this->m_faults.GetCurrentMsg().m_surface.GetMin());
				}
			}
			while(this->m_faults.IncrementCurrentMsg());
		}
	}
	bool extremums_not_defined = true;
	for( size_t i = 0; i< vptmax.size() && i < vptmin.size(); i++)
	{
		CPoint3 ptmax, ptmin;
		ptmax = vptmax[i];
		ptmin = vptmin[i];

		if (extremums_not_defined)
		{
			extremums_not_defined = false;
			// real x
			maxX = ptmax.x;
			minX = ptmin.x;
			// real y
			maxY = ptmax.y;
			minY = ptmin.y;
			// real z
			maxZ = ptmax.z;
			minZ = ptmin.z;
		}
		else
		{
			// real x
			if (maxX < ptmax.x) maxX = ptmax.x;
			if (minX > ptmin.x) minX = ptmin.x;
			// real y
			if (maxY < ptmax.y) maxY = ptmax.y;
			if (minY > ptmin.y) minY = ptmin.y;
			// real z
			if (maxZ < ptmax.z) maxZ = ptmax.z;
			if (minZ > ptmin.z) minZ = ptmin.z;
		}
	}
	vptmin.clear();
	vptmax.clear();
	return !extremums_not_defined;
}

#include <dime/dxfwriter.h>
bool SurfDoc::CutlineSaveAsDxfRazres(dimeModel * model,  dimeBlock * block, SSaveProfData &sprData,
									 double a, double b, double c, double d,
									 double minX, double minY, double minZ,
									 double maxX, double maxY, double maxZ)
{
	if (!model) return false;
	bool status = false;	

	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( this->m_surfaces.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(model,block,SurfDoc::sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( this->m_faults.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(model,block,SurfDoc::sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if(this->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_geo_catches.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(model,block,SurfDoc::sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_geo_catches.IncrementCurrentMsg());
	}
	printf("SurfDoc::CutlineSaveAsDxfRazres end status = %d\n", status);
	return status;
}




void SurfDoc::CutlineSaveAsRazres(double a, double b, double c, double d )
{
#if VIEW_ONLY_VERSION
	MessageBox(0, "This function is not acessed in the View Only Version", "View Only Version of Geo Surf Cube", MB_OK | MB_ICONEXCLAMATION);
#else
	//minimums needs
	double minX, minY, minZ;
	double maxX, maxY, maxZ;
	if(GetExtremums_of_Surfaces_and_Faults(
		minX, minY, minZ,
		maxX, maxY, maxZ,
		true))
	{
		TCHAR lpstrFile1[1024];
		TCHAR lpstrFile2[1024];
		TCHAR lpstrFile3[1024];
		TCHAR filter[] =    
			TEXT("AutoCAD DXF(*.dxf)\0*.dxf\0")
			TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
			TEXT("All Files (*.*)\0*.*\0");

		DWORD nFilterIndex = 0;

		//sprintf(lpstrFile1, "%s\\sloi", directory);
		sprintf(lpstrFile1, "%s\\slice[%f_%f_%f_%f]_of_%s", directory, a,b,c,d,"sloi");
		if (SaveProfDlg(0, lpstrFile1, filter, nFilterIndex, SurfDoc::sprData) != S_OK)
			return;

		if (nFilterIndex == 1)
		{
			cutline_save_as_dxf_razrez(this, lpstrFile1, false, &SurfDoc::sprData, a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
			return;
		}

		//sprintf(lpstrFile2, "%s\\faults", directory);
		sprintf(lpstrFile2, "%s\\slice[%f_%f_%f_%f]_of_%s", directory, a,b,c,d,"faults");
		if (SaveProfDlg(0, lpstrFile2, filter, nFilterIndex, SurfDoc::sprData) != S_OK)
			return;
		//sprintf(lpstrFile3, "%s\\geo_catches", directory);
		sprintf(lpstrFile3, "%s\\slice[%f_%f_%f_%f]_of_%s", directory, a,b,c,d,"geo_catches");
		if (SaveProfDlg(0, lpstrFile3, filter, nFilterIndex, SurfDoc::sprData) != S_OK)
			return;



		FILE *bln1, *bln2, *bln3;
		bln1 = fopen(lpstrFile1,"wt");
		if (!bln1)
		{
			char str[255];
			sprintf(str, "Can not create file %s", lpstrFile1);
			MessageBox(0, str, "Cutline Save As Razres", MB_OK);
			return;
		}
		bln2 = fopen(lpstrFile2,"wt");
		if (!bln2)
		{
			fclose(bln1);
			char str[255];
			sprintf(str, "Can not create file %s", lpstrFile2);
			MessageBox(0, str, "Cutline Save As Razres", MB_OK);
			return;
		}
		bln3 = fopen(lpstrFile3,"wt");
		if (!bln3)
		{
			fclose(bln1);
			fclose(bln2);
			char str[255];
			sprintf(str, "Can not create file %s", lpstrFile3);
			MessageBox(0, str, "Cutline Save As Razres", MB_OK);
			return;
		}	
		
		//  3d линии
		/*if (this->m_cutlines.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_cutlines.GetCurrentMsg().SavingAsRazrez(bln,nFilterIndex,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
			}
			while(this->m_cutlines.IncrementCurrentMsg());
		}*/	
		if(this->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_surfaces.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(bln1,SurfDoc::sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
			}
			while(this->m_surfaces.IncrementCurrentMsg());
		}
		if(this->m_faults.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_faults.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(bln2,SurfDoc::sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
			}
			while(this->m_faults.IncrementCurrentMsg());
		}
		if(this->m_geo_catches.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_geo_catches.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(bln3,SurfDoc::sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
			}
			while(this->m_geo_catches.IncrementCurrentMsg());
		}
		fclose(bln1);
		fclose(bln2);
		fclose(bln3);
	}
	else
		MessageBox(0, "Extremums not found", "CutlineSaveAsRazres", MB_OK);

#endif //!VIEW_ONLY_VERSION
}

#if 0
{
	double x0,y0,d;int j;
	// динамический массив для перечисления неизвестного пока числа линий
	vect<Trace> traces;
	traces.OnCreate();
	Trace trace;

	// ФОРМИРУЕМ ДВУМЕРНУЮ МАТРИЦУ РАССТОЯНИЙ МЕЖДУ ТОЧКАМИ
	float **md0;			
	md0 = AllocFloatMat (len0, len0);
	for (i = 0; i< len0; i++)
	{
		for(j = 0; j < len0; j++)
		{
			md0[i][j] = Distance(points0[i],points0[j]);
		}
	}
	// ФОРМИРУЕМ МАССИВ ИНДЕКСОВ
	Vector<int> indices0;
	indices0.resize(len0);
	for (i = 0; i < len0; i++)
	{
		indices0[i] = i;
	}

	int i0 = 0;
	// удаляем дублирующие точки из массива индексов
	for (i0 = 0; i0 < indices0.Size(); i0++)
	{
		for (i = i0+1; i < indices0.Size(); i++)
		{
			d = md0[indices0[i0]][indices0[i]];
			if(d == 0.f)
			{
				// удаляем дублирующие точки
				indices0.DeleteElement(i);
				i--;
			}
		}
	}
	// ПОЛУЧАЕМ ТАКИМ ОБРАЗОМ ЧИСЛО НЕДУБЛИРУЮЩИХСЯ ТОЧЕК
	int len = indices0.Size();
	CPoint3f * points1 = new CPoint3f[len];
	CPoint3f * points2 = new CPoint3f[len];

	for(i = 0; i < len; i++)
	{
		points1[i] = points0[indices0[i]];
	}

	if (maxX-minX > maxY-minY)
	{
		// sort on x using Quicksort algorithm:
		qsort( (void *)points1, (size_t)len, sizeof(CPoint3f), compareX );
	}
	else
	{
		// sort on y using Quicksort algorithm:
		qsort( (void *)points1, (size_t)len, sizeof(CPoint3f), compareY );
	}

	float **md,*vsumd, maxsumd;
	int i_maxsumd;
	vsumd = (float *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		len * sizeof (float));

	md = AllocFloatMat (len, len);

	for (i = 0; i < len; i++)
	{
		vsumd[i] = 0.f;
		for(j = 0; j < len; j++)
		{
			md[i][j] = Distance(points1[i],points1[j]);
			vsumd[i] += md[i][j];
		}
		if (i == 0)
		{
			maxsumd = vsumd[i];
			i_maxsumd = i;
		}
		else
		{
			if (maxsumd < vsumd[i])
			{
				maxsumd = vsumd[i];
				i_maxsumd = i;
			}
		}
	}

	Vector<int> indices;
	indices.resize(len);

	for (i = 0; i < len; i++)
	{
		indices[i] = i;
	}

	trace.iFirst = 0;// перечисляем первую линию
	trace.nPts	 = 0;

	int i1 = i_maxsumd,
		i2 = 0;
	if (len > 0)
	{
		points2[i2] = points1[i1];i2++;
		indices.DeleteElement(i1);
		trace.nPts++;
		do
		{
			//find min nonzero d and its index
			float 
				mind,d;
			int i_mind;
			j = 0;
			for (i = 0; i < indices.Size(); i++)
			{
				d = md[i1][indices[i]];
				if(d > 0.f)
				{
					if (j == 0)
					{
						mind = d;
						i_mind = i;
					}
					else
					{
						if (mind > d) 
						{
							mind = d;
							i_mind = i;
						}
					}							
					j++;
				}
			}
			if(indices.Size() == 0)
				break;
			i1 = indices[i_mind];

			// из исходного вектора в результирующий заносим 
			// следующую ближайшую точку

			if (mind < m_part*Diagonal)
			{
				trace.nPts++;
			}
			else
			{
				traces.AddMsg(&trace);
				trace.iFirst=i2;
				trace.nPts = 1;
			}

			points2[i2] = points1[i1];i2++;
			indices.DeleteElement(i_mind);
			if(indices.Size() == 0)
				break;
		}
		while(true);
		traces.AddMsg(&trace);
	}

	if (md0) FreeFloatMat(md0);
	if (md) FreeFloatMat(md);
	if (vsumd) HeapFree( GetProcessHeap(), 0, vsumd);

	int len2 = i2;
	vdouble 
		xline,
		yline,
		zline;

	if (traces.SetCurrentMsgOnFirst())
	{
		do
		{
			trace = traces.GetCurrentMsg();
			bool toClose = false;

			float from_start_to_end_distance = 
				Distance(
				points2[trace.iFirst],
				points2[trace.iFirst + trace.nPts - 1]);

			float max_distance_from_first = 0.f, distance_from_first;

			for (int j = 1; j < trace.nPts; j++)
			{
				distance_from_first = Distance(
				points2[trace.iFirst],
				points2[trace.iFirst + j]);

				if(distance_from_first > max_distance_from_first)
					max_distance_from_first = distance_from_first;
			}

			if (from_start_to_end_distance < m_part*Diagonal &&
				from_start_to_end_distance < max_distance_from_first)
				toClose = true;

			xline.resize(trace.nPts+int(toClose));
			yline.resize(trace.nPts+int(toClose));
			zline.resize(trace.nPts+int(toClose));
			for(i = 0; i < trace.nPts; i++)
			{
				xline[i] = points2[trace.iFirst+i].x;
				yline[i] = points2[trace.iFirst+i].y;
				zline[i] = points2[trace.iFirst+i].z;
			}
			if(toClose)
			{
				i = trace.nPts;
				xline[i] = points2[trace.iFirst].x;
				yline[i] = points2[trace.iFirst].y;
				zline[i] = points2[trace.iFirst].z;
			}
			if ( useCutLines )
				AddCutLine(xline,yline, zline,0);
			else
				AddLine(xline,yline, zline,0);
		}
		while(traces.IncrementCurrentMsg());
	}
}
#endif


void SurfDoc::ClearIzolines()
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		int surf_number = 0;
		do
		{
			TreeView_DeleteMyItem(this->hwndTV, 
				m_surfaces.GetCurrentMsg().m_izo_lines_ObjectList.myTreeItem);
			m_surfaces.GetCurrentMsg().m_izo_lines.clear();
			m_surfaces.GetCurrentMsg().m_izo_lines_ObjectList.clear();
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
}
void SurfDoc::Izolines()
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		int surf_number = 0;
		do
		{
			int cutting_number = 0;
			double izo_start = m_izo_step * ceil(m_surfaces.GetCurrentMsg().m_surface.GetMin().z / m_izo_step);
			double izo_end   = m_izo_step * floor(m_surfaces.GetCurrentMsg().m_surface.GetMax().z / m_izo_step);
			for (double  z_level = izo_start; z_level <= izo_end; z_level += m_izo_step)
			{
				m_surfaces.GetCurrentMsg().m_surface.Cutting(0.0,0.0,1.0,-z_level, 
					false, true, 
					5, cutting_number, surf_number, 
					NULL,NULL, (void*) NULL, 
					&m_surfaces.GetCurrentMsg(), 
					&m_surfaces.GetCurrentMsg().m_blank_polygon_matrix, 
					&m_surfaces.GetCurrentMsg().m_cutplane_polygones_ObjectList,
					&m_surfaces.GetCurrentMsg().m_cutplane_polygones);

				m_surfaces.GetCurrentMsg().m_surface.CutLine( 5, cutting_number, (void *) NULL, m_surfaces.GetCurrentMsg(), surf_number );
				cutting_number++;
			}
			surf_number++;
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
}
void SurfDoc::CutAndDisvisible(bool positive)
{
	CutAndDisvisible(positive, 
		m_cut_plane_d[0],	
		m_cut_plane_d[1],
		m_cut_plane_d[2],
		m_cut_plane_d[3]);
}
void SurfDoc::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	//*****************************************************************
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	//*****************************************************************
	// do unvisible m_tria_grid
	if (this->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_tria_grid.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_tria_grid.IncrementCurrentMsg());
	}

	// do unvisible points
	if (m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			m_surfaces.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_surfaces.IncrementCurrentMsg());
	}

	if (m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			m_faults.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_faults.IncrementCurrentMsg());
	}

	if (m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			m_geo_catches.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_geo_catches.IncrementCurrentMsg());
	}

	if (m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			m_grid_data.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_grid_data.IncrementCurrentMsg());
	}

	if (m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cubes.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_cubes.IncrementCurrentMsg());
	}


#if DFX_LAYER_FROM_OBJECT
	if (m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			m_dxfConverters.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_dxfConverters.IncrementCurrentMsg());
	}
#endif
	if (m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			m_auto_build_profiles.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_auto_build_profiles.IncrementCurrentMsg());
	}
	// do unvisible lines
	if (m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_lines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_lines.IncrementCurrentMsg());
	}

	// do unvisible cutlines
	if (m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cutlines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_cutlines.IncrementCurrentMsg());
	}

	// do unvisible cutlines
	if (m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_blanklines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_blanklines.IncrementCurrentMsg());
	}

	// do unvisible drills
	if (m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_drills.IncrementCurrentMsg());
	}
	// do unvisible strings
	if (m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			m_strings.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(m_strings.IncrementCurrentMsg());
	}
}

void SurfDoc::GetMinMaxDPlaneCoef(bool bFastCutting, 
								  double &min_d, double &max_d
								  )
{
	double d[8];
	if (bFastCutting)
	{
		d[0] = 
			- (
			m_cut_plane_v[0]*m_xv_min +
			m_cut_plane_v[1]*m_yv_min +
			m_cut_plane_v[2]*m_zv_min);

		d[1] = 
			- (
			m_cut_plane_v[0]*m_xv_max +
			m_cut_plane_v[1]*m_yv_min +
			m_cut_plane_v[2]*m_zv_min);

		d[2] = 
			- (
			m_cut_plane_v[0]*m_xv_min +
			m_cut_plane_v[1]*m_yv_max +
			m_cut_plane_v[2]*m_zv_min);

		d[3] = 
			- (
			m_cut_plane_v[0]*m_xv_min +
			m_cut_plane_v[1]*m_yv_min +
			m_cut_plane_v[2]*m_zv_max);

		d[4] = 
			- (
			m_cut_plane_v[0]*m_xv_min +
			m_cut_plane_v[1]*m_yv_max +
			m_cut_plane_v[2]*m_zv_max);

		d[5] = 
			- (
			m_cut_plane_v[0]*m_xv_max +
			m_cut_plane_v[1]*m_yv_min +
			m_cut_plane_v[2]*m_zv_max);

		d[6] = 
			- (
			m_cut_plane_v[0]*m_xv_max +
			m_cut_plane_v[1]*m_yv_max +
			m_cut_plane_v[2]*m_zv_min);

		d[7] = 
			- (
			m_cut_plane_v[0]*m_xv_max +
			m_cut_plane_v[1]*m_yv_max +
			m_cut_plane_v[2]*m_zv_max);
	}
	else
	{
		d[0] = 
			- (
			m_cut_plane_d[0]*m_xd_min +
			m_cut_plane_d[1]*m_yd_min +
			m_cut_plane_d[2]*m_zd_min);

		d[1] = 
			- (
			m_cut_plane_d[0]*m_xd_max +
			m_cut_plane_d[1]*m_yd_min +
			m_cut_plane_d[2]*m_zd_min);

		d[2] = 
			- (
			m_cut_plane_d[0]*m_xd_min +
			m_cut_plane_d[1]*m_yd_max +
			m_cut_plane_d[2]*m_zd_min);

		d[3] = 
			- (
			m_cut_plane_d[0]*m_xd_min +
			m_cut_plane_d[1]*m_yd_min +
			m_cut_plane_d[2]*m_zd_max);

		d[4] = 
			- (
			m_cut_plane_d[0]*m_xd_min +
			m_cut_plane_d[1]*m_yd_max +
			m_cut_plane_d[2]*m_zd_max);

		d[5] = 
			- (
			m_cut_plane_d[0]*m_xd_max +
			m_cut_plane_d[1]*m_yd_min +
			m_cut_plane_d[2]*m_zd_max);

		d[6] = 
			- (
			m_cut_plane_d[0]*m_xd_max +
			m_cut_plane_d[1]*m_yd_max +
			m_cut_plane_d[2]*m_zd_min);

		d[7] = 
			- (
			m_cut_plane_d[0]*m_xd_max +
			m_cut_plane_d[1]*m_yd_max +
			m_cut_plane_d[2]*m_zd_max);	
	}

	min_d = d[0];
	max_d = d[0];
	for (int i = 1; i < 8; i++)
	{
		if(min_d>d[i]) min_d=d[i];
		if(max_d<d[i]) max_d=d[i];
	}

}

void SurfDoc::InitXYZCutsPlanes()
{
	if( m_X >= m_xd_max || m_X <= m_xd_min)
		m_X = m_xd_zoom_center;
	if( m_Y >= m_yd_max || m_Y <= m_yd_min)
		m_Y = m_yd_zoom_center;
	if( m_Z >= m_zd_max || m_Z <= m_zd_min)
		m_Z = m_zd_zoom_center;
}

void SurfDoc::CutXYZandDisvisible(int subcube_number)
{
	this->CutXYZandDisvisible(subcube_number, m_X, m_Y, m_Z);
}
void SurfDoc::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	//*******************************************************************
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	//*******************************************************************

	// do unvisible m_tria_grid
	if (this->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_tria_grid.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(this->m_tria_grid.IncrementCurrentMsg());
	}

	if (m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			m_surfaces.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_surfaces.IncrementCurrentMsg());
	}

	if (m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			m_faults.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_faults.IncrementCurrentMsg());
	}

	if (m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			m_geo_catches.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_geo_catches.IncrementCurrentMsg());
	}


	if (m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			m_grid_data.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_grid_data.IncrementCurrentMsg());
	}

	if (m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cubes.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_cubes.IncrementCurrentMsg());
	}



#if DFX_LAYER_FROM_OBJECT

	if (m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			m_dxfConverters.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_dxfConverters.IncrementCurrentMsg());
	}
#endif
	if (m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			m_auto_build_profiles.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_auto_build_profiles.IncrementCurrentMsg());
	}

	if (m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_lines.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_lines.IncrementCurrentMsg());
	}
	if (m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_cutlines.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_cutlines.IncrementCurrentMsg());
	}
	if (m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			m_blanklines.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_blanklines.IncrementCurrentMsg());
	}
	if (m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			m_drills.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_drills.IncrementCurrentMsg());
	}
	if (m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			m_strings.GetCurrentMsg().CutXYZandDisvisible(subcube_number,  X,  Y,  Z);
		}
		while(m_strings.IncrementCurrentMsg());
	}
}


/*
void SurfDoc::SetIzolines()
{
	if(m_izo_step < 0)
	{
		m_izo_step = 100;
		m_izo_start = m_izo_step * ceil(m_zd_min / m_izo_step);
		m_izo_end   = m_izo_step * floor(m_zd_max / m_izo_step);

		if (m_izo_start - m_izo_end == 0.0)
		{
			double range = m_zd_max-m_zd_min;
			m_izo_step = pow(10., floor(log10(range))-1);
			m_izo_start = m_izo_step * ceil(m_zd_min / m_izo_step);
			m_izo_end   = m_izo_step * floor(m_zd_max / m_izo_step);
		}
	}
}
*/


//===== Внешняя функция нормировки мантисс шагов сетки
void gScale3D (double span, double& step)
{
	//===== Переменная span определяет диапазон изменения
	//===== значаний одной из координат точек графика
	//===== Вычисляем порядок числа, описывающего диапазон
	int power = int(floor(log10(span)));
	//===== Множитель (zoom factor)
	double factor = pow(10.0, (double)power);
	//===== Мантисса диапазона (теперь 1 < span < 10)
	span /= factor;


	//===== Выбираем стандартный шаг сетки
	if (span<1.99)
		step=.2;
	else if (span<2.49)
		step=.25;
	else if (span<4.99)
		step=.5;
	else if (span<10.)
		step= 1.;
	else
		step = 5.;

	//===== Возвращаем реальный шаг сетки (step*10^power)
	step *= factor; 
}



void SurfDoc::Scale (TData3D& data)
{
	//===== С пустой последовательностью не работаем

	switch (data.axesFlag)
	{
	case 0: // X
		{
			data.Min = m_xd_min;
			data.Max = m_xd_max;
		}
		break;
	case 1: // Y
		{
			data.Min = m_yd_min;
			data.Max = m_yd_max;
		}
		break;
	case 2: // Z
		{
			data.Min = m_zd_min;
			data.Max = m_zd_max;
		}
		break;
	}


	//===== Максимальная амплитуда двух экстремумов 
	double ext = max(fabs(data.Min),fabs(data.Max));
#if 0
	//===== Искусственно увеличиваем порядок экстремума
	//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
	//===== не переходя к экспоненцеальной форме чисел 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	data.Power = int(floor(power/7.));
#else
	double power = ext > 0.? log10(ext) : 0.;	
	data.Power = int(floor(power/7.));
#endif


	//===== Если число не укладывается в этот диапазон
	if (data.Power != 0)
		//===== то мы восстанавливаем значение порядка
		data.Power = int(floor(power)) - 3;
	//===== Реальный множитель
	data.Factor = pow(10.,data.Power);


	//===== Диапазон изменения мантиссы
	double span = (data.Max - data.Min)/data.Factor;
	//===== Если он нулевой,
	if (span == 0.)
		span = 0.5; // то искусственно раздвигаем график

	//===== Подбираем стандартный шаг для координатной сетки
	gScale3D (span, data.Step);


	//===== Шаг с учетом искусственных преобразований
	data.dStep = data.Step * data.Factor;

	//===== Начальная линия сетки должна быть кратна шагу
	//===== и быть меньше минимума
	data.dStart = data.dStep * int(floor(data.Min/data.dStep));
	data.Start = data.dStart/data.Factor;


	if (data.Step == 0.0)
	{
		printf("warning : data.Step == 0.0 \n\t\tSurfDoc::Scale (TData3D& data)\n\n");
		return;
	}

#if 1
	//===== Вычисляем последнюю линию сетки
	for (data.End = data.Start;
		data.End < data.Min/data.Factor + span-1e-10;  
		data.End += data.Step)
		;
#else
		data.End = data.Start 
			+ int( ((data.Max-data.Start)/data.Factor - 1e-10) / data.Step+1)
			* data.Step;
#endif
	data.dEnd = data.End*data.Factor;
}


void SurfDoc::MakeLabel(int axesFlag, double v, char* s, char *spower)
{
	double step;
	int iPower;

	switch (axesFlag)
	{
	case 0: // X
		{
			step = m_DataX.Step;
			iPower = m_DataX.Power;
		}
		break;
	case 1: // Y
		{
			step = m_DataY.Step;
			iPower = m_DataY.Power;
		}
		break;
	case 2: // Z
		{
			step = m_DataZ.Step;
			iPower = m_DataZ.Power;
		}
		break;
	}
	//====== Сначала делаем грубую прикидку
	//====== Пробуем поместиться в 20 позиций
	//====== Выясняем порядок шага сетки,
	//====== переворачивая его знак (трюк)
	int nDigits = int(ceil(-log10(step)));
	//====== Если все изменения происходят до запятой,
	//====== то цифры после запятой нас не интересуют
	if (nDigits <= 0)
		nDigits = -1;
	else
	{
		//if (axesFlag == 0 || axesFlag == 1 || axesFlag == 3)
			//nDigits++
			//;	// Эстетическая добавка
	}

	if (nDigits <= 0)
	{
		wsprintf(s,"%c%d\0",
			 v<0.0?'-':' ', 
			 int(fabs(v)) 
			);
	}
	else
	{
		wsprintf(s,"%c%d.%d\0",
			 v<0.0?'-':' ', 
			 int(fabs(v)), 
			 int(pow(10.,nDigits)*(fabs(v)-double(int(fabs(v)))))
			);
	}


	//====== Справа оставляем минимум разрядов
	sprintf (spower, "");

	//====== Нужен ли порядок?
	if (iPower != 0)
	{
		//====== Нужен, если не поместились в (10^-3, 10^+4)
		sprintf (spower, "*10^%d\0",iPower);
	}
}



void SurfDoc::ConvertBlnProfilesTo3D(bool create_layers)
{
	if(this->m_bln_profiles.SetCurrentMsgOnLast())
	{
		this->m_bln_profiles.GetCurrentMsg().ConvertBlnProfilesTo3D(create_layers);

	}
}

void SurfDoc::SetLastBlnProfileAcadYscale(double z1w, double y1a, double z2w, double y2a)
{
	printf("SurfDoc::SetLastBlnProfileAcadYscale(double z1w = %f, double y1a = %f, double z2w = %f, double y2a = %f)\n", z1w, y1a, z2w, y2a);
	if(this->m_bln_profiles.SetCurrentMsgOnLast())
	{
		this->m_bln_profiles.GetCurrentMsg().SetAcadYscale(z1w, y1a, z2w, y2a);
	}
}
extern int __cdecl compareProfileAttachX( const void *arg1, const void *arg2 );
extern void ProfileAttaching(double xProfile, int& ipoint, int lenMapAttach, ProfileAttachPoint *ptpa, double& xMap, double& yMap );

void SurfDoc::ConvertGridProfilesTo3D()
{
	if(this->m_grid_profiles.SetCurrentMsgOnLast())
	{
		this->m_grid_profiles.GetCurrentMsg().ConvertGridProfilesTo3D();
	}
}
/*#if FAST_GRID_LOADING
int SurfDoc::AddGridProfile(Grid *pgrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile)
{
	GridProfile3D grid_profile(this);
	this->m_grid_profiles.AddMsg(&grid_profile);
	if (0 == this->m_grid_profiles.GetLastMsg().AddGridProfile(pgrid, xMap, yMap, xProfile ))
	{
		this->m_grid_profiles_ObjectList.Init(this->m_bln_profiles, this);
		return 0;
	}
	else
	{
		this->m_grid_profiles.EraseLastMsg();
		return -1;
	}
}

#else*/
int SurfDoc::AddGridProfile(CGrid *pCGrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile)
{
	GridProfile3D grid_profile(this);
	this->m_grid_profiles.AddMsg(&grid_profile);
	if (0 == this->m_grid_profiles.GetLastMsg().AddGridProfile( pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible, xMap, yMap, xProfile ))
	{
		this->m_grid_profiles_ObjectList.Init(this->m_bln_profiles, this);
		return 0;
	}
	else
	{
		this->m_grid_profiles.EraseLastMsg();
		return -1;
	}
}
//#endif /*FAST_GRID_LOADING*/
int SurfDoc::AddGridProfile(vdouble &x, vdouble &y, vdouble &z, vdouble &visible, vdouble &xMap, vdouble &yMap, vdouble &xProfile)
{
	GridProfile3D grid_profile(this);
	this->m_grid_profiles.AddMsg(&grid_profile);
	if (0 == this->m_grid_profiles.GetLastMsg().AddGridProfile(x, y, z, visible, xMap, yMap, xProfile))
	{
		this->m_grid_profiles_ObjectList.Init(this->m_bln_profiles, this);
		return 0;
	}
	else
	{
		this->m_grid_profiles.EraseLastMsg();
		return -1;
	}
}
int SurfDoc::AddMapBlnProfile(vector<double> &xMap, vector<double> &yMap, int inside)
{
//WriteRaporto("AddMapBlnProfile 0\n");
	BrokenPlane3D bp3D(this);
	if (inside == 0)
		// заливка внутри - включаем первый бит 
		// в пользовательских данных объекта линии бланкования
		bp3D.m_lParam |= OBJECT_FLAG_INSIDE_BLANK_BIT;
	else
		// заливка снаружи - выключаем первый бит 
		// в пользовательских данных объекта линии бланкования
		bp3D.m_lParam &= ~OBJECT_FLAG_INSIDE_BLANK_BIT;

#if BROKEN_PLANE_VECTOR_TYPE
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_brokenPlanes.AddMsg(&bp3D);
	m_brokenPlanes.GetLastMsg().Init_broken_plane(NULL, xMap, yMap);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#else
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_brokenPlanes.push_back(bp3D);
	m_brokenPlanes.back().Init(xMap, yMap);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
	m_brokenPlanes_ObjectList.Init(m_brokenPlanes, this);
//WriteRaporto("AddMapBlnProfile end\n");
	return 0;
}
void SurfDoc::CutMapBlnProfile()
{
#if BROKEN_PLANE_VECTOR_TYPE
	if (m_brokenPlanes.SetCurrentMsgOnLast())
	{
		m_brokenPlanes.GetCurrentMsg().Cutting();
	}
#else
	m_brokenPlanes.back().Cutting();
#endif
	ZoomView();
}
void SurfDoc::CutMapBlnProfileSave()
{
#if BROKEN_PLANE_VECTOR_TYPE
	if (m_brokenPlanes.SetCurrentMsgOnLast())
	{
		m_brokenPlanes.GetCurrentMsg().SaveAsRazres();
	}
#else
	m_brokenPlanes.back().SaveAsRazres();
#endif
}

int SurfDoc::AddBitmap(char *lpstrFile, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile)
{
	printf("SurfDoc::AddBitmap\n");
	Bmp3D bitmap(this);
	m_bitmaps.AddMsg(&bitmap);

	if (this->m_bitmaps.GetLastMsg().LoadGLTexture(lpstrFile, xMap, yMap, zProfile))
	{
		this->m_bitmaps_ObjectList.Init(this->m_bitmaps, this);
		return 0;
	}
	else
	{
		this->m_bitmaps.EraseLastMsg();
		return -1;
	}
}

int SurfDoc::AddBmpProfile(char *lpstrFile, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile)
{
	printf("SurfDoc::AddBmpProfile\n");
	BmpProfile3D bmp(this);
	m_bmp_profiles.AddMsg(&bmp);

	if (this->m_bmp_profiles.GetLastMsg().LoadGLTexture(lpstrFile, xMap, yMap, zProfile))
	{
		this->m_bmp_profiles_ObjectList.Init(this->m_bmp_profiles, this);
		return 0;
	}
	else
	{
		this->m_bmp_profiles.EraseLastMsg();
		return -1;
	}
}
int SurfDoc::AddBitmap(char *lpstrFile, vector<double> &xMap, vector<double> &yMap, double zElev)
{
	printf("SurfDoc::AddBitmap\n");
	Bmp3D bitmap(this);
	m_bitmaps.AddMsg(&bitmap);

	if (this->m_bitmaps.GetLastMsg().LoadGLTexture(lpstrFile, xMap, yMap, zElev))
	{
		this->m_bitmaps_ObjectList.Init(this->m_bitmaps, this);
		return 0;
	}
	else
	{
		this->m_bitmaps.EraseLastMsg();
		return -1;
	}
}


int SurfDoc::AddNewBlnProfile_db(const char *lpstrFile, const char * name, vector<long> * pv_ID_KT, bool to_add_new_rozriz, vector<double> xMap, vector<double> yMap, vector<double> xProfile, bool acad_yscale_loaded, double z1w, double y1a, double z2w, double y2a, bool checked_plane, long id_rozriz, bool to_add_hvosty)
{
	BlnProfile3D bln_profile(this);
	bln_profile.m_plane.m_bChecked = checked_plane;

	this->m_bln_profiles.AddMsg(&bln_profile);
	if (to_add_hvosty)
	{
		//здесь надо найти пересечение хвостов разреза с границами площадки или по длине интерполяции информации
		int len = xMap.size();
		if (len > 1)
		{	
			if(this->m_cube_size.Defined())
			{
				// отрезок между скважинами
				double dx2 = xMap[len-1] - xMap[len-2];
				double dy2 = yMap[len-1] - yMap[len-2];
				double dist2 = sqrt(dx2*dx2 + dy2*dy2);

				double add_len2 = DBL_MAX;

				// 
				if (fabs(dx2) > DBL_MIN)
				{
					double d_x = 0.0;
					if (dx2 > 0.0)
					{
						d_x = this->m_cube_size.xMax() - xMap[len-1];
					}
					else
					{
						d_x = -(xMap[len-1] - this->m_cube_size.xLL);
					}
					double add_len = (d_x / dx2) * dist2;
					if (add_len2 > add_len) add_len2 = add_len;
				}
				if (fabs(dy2) > DBL_MIN)
				{
					double d_y = 0.0;
					if (dy2 > 0.0)
					{
						d_y = this->m_cube_size.yMax() - yMap[len-1];
					}
					else
					{
						d_y = -(yMap[len-1] - this->m_cube_size.yLL);
					}
					double add_len = (d_y / dy2) * dist2;
					if (add_len2 > add_len) add_len2 = add_len;
				}

				//add_len2 *= 0.9; // to not be zero next


				//по длине интерполяции информации
				//if (add_len2 > 5) add_len2 = 5;

				double px2 = (add_len2 / dist2) * dx2;
				double py2 = (add_len2 / dist2) * dy2;

				xMap.push_back(xMap[len-1] + px2);
				yMap.push_back(yMap[len-1] + py2);
				xProfile.push_back(xProfile[len-1] + add_len2);
				if (pv_ID_KT) pv_ID_KT->push_back(-1);



				////
				double dx1 = xMap[1] - xMap[0];
				double dy1 = yMap[1] - yMap[0];
				double dist1 = sqrt(dx1*dx1 + dy1*dy1);

				double add_len1 = DBL_MAX;

				if (fabs(dx1) > DBL_MIN)
				{
					double d_x = 0.0;
					if (dx1 > 0.0)
					{
						d_x = xMap[0] - this->m_cube_size.xLL;
					}
					else
					{
						d_x = -(this->m_cube_size.xMax() - xMap[0]);
					}
					double add_len = (d_x / dx1) * dist1;
					if (add_len1 > add_len) add_len1 = add_len;
				}
				if (fabs(dy1) > DBL_MIN)
				{
					double d_y = 0.0;
					if (dy1 > 0.0)
					{
						d_y = yMap[0] - this->m_cube_size.yLL;
					}
					else
					{
						d_y = -(this->m_cube_size.yMax() - yMap[0]);
					}
					double add_len = (d_y / dy1) * dist1;
					if (add_len1 > add_len) add_len1 = add_len;
				}

				//add_len1 *= 0.9; // to not be zero next

				//по длине интерполяции информации
				//if (add_len1 > 5) add_len1 = 5;




				double px1 = (add_len1 / dist1) * dx1;
				double py1 = (add_len1 / dist1) * dy1;

				xMap.insert(xMap.begin(), xMap[0] - px1);
				yMap.insert(yMap.begin(), yMap[0] - py1);
				xProfile.insert(xProfile.begin(), xProfile[0] - add_len1);
				if (pv_ID_KT) pv_ID_KT->insert(pv_ID_KT->begin(), -1);
			}
		}
	}
	if (0 == this->m_bln_profiles.GetLastMsg().AddBlnProfile(lpstrFile, name, pv_ID_KT, xMap, yMap, xProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a))
	{
		this->m_bln_profiles_ObjectList.Init(this->m_bln_profiles, this);

		if (this->m_pLabDoc && pv_ID_KT && to_add_new_rozriz)
		{
			id_rozriz = this->m_pLabDoc->AddNewRozriz(
				this->Get_ID_OBJ(),
				name, "", acad_yscale_loaded, z1w,y1a,z2w,y2a, false, NULL, *pv_ID_KT);
		}	

		this->m_bln_profiles.GetLastMsg().id_rozriz = id_rozriz;

		return 0;
	}
	else
	{
		this->m_bln_profiles.EraseLastMsg();
		return -1;
	}

}


int SurfDoc::AddBlnProfile(const char *lpstrFile, const char * name, vector<double> &xMap, vector<double> &yMap, vector<double> &xProfile, bool acad_yscale_loaded, double z1w, double y1a, double z2w, double y2a)
{
	if (this->m_bln_profiles.SetCurrentMsgOnLast())
	{
		return this->m_bln_profiles.GetCurrentMsg().AddBlnProfile(lpstrFile, name, NULL, xMap, yMap, xProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a);
	}
	else
	{
		return -1;
	}
}

int SurfDoc::AddNewBlnProfile(const char *lpstrFile, const char * name, int ProfileDirection, double f)
{
	BlnProfile3D bln_profile(this);
	this->m_bln_profiles.AddMsg(&bln_profile);
	if (0 == this->m_bln_profiles.GetLastMsg().AddBlnProfile(lpstrFile, name, ProfileDirection, f))
	{
		this->m_bln_profiles_ObjectList.Init(this->m_bln_profiles, this);
		return 0;
	}
	else
	{
		this->m_bln_profiles.EraseLastMsg();
		return -1;
	}
}


int SurfDoc::AddBlnProfile(const char *lpstrFile, const char * name, int ProfileDirection, double f)
{
	if (this->m_bln_profiles.SetCurrentMsgOnLast())
	{
		return this->m_bln_profiles.GetCurrentMsg().
			AddBlnProfile(lpstrFile, name, ProfileDirection, f);
	}
	else
	{
		return -1;
	}
}

void SurfDoc::IzolinesSaveAs()
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
                         TEXT("Golden Software Data (*.dat)\0*.dat\0")
                         TEXT("All Files (*.*)\0*.*\0");

	sprintf(lpstrFile, "%s\\izolines", directory);
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return;
	FILE *bln;
	bln = fopen(lpstrFile,"wt");
	//  3d линии
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().SavingAsDatOrBln(bln, nFilterIndex);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	fclose(bln);
}


void SurfDoc::AngleLocalMin(int n, double cos_boder)
{
	if(this->m_lines.SetCurrentMsgOnFirst() )
	{
		do
		{
			this->m_lines.GetCurrentMsg().AngleLocalMin(n, cos_boder);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
}

void SurfDoc::SpheresSaveAs()
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     
                         TEXT("Golden Software Data (*.dat)\0*.dat\0")
                         TEXT("All Files (*.*)\0*.*\0");

	sprintf(lpstrFile, "%s\\points", directory);
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return;
	FILE *dat;
	dat = fopen(lpstrFile,"wt");
	//  3d линии
	if (m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			size_t len = m_spheres.GetCurrentMsgLen();
			Sphere3D * ptr = m_spheres.GetCurrentMsgPtr();

			for (size_t i = 0; i < len; i++)
			{			
				fprintf(dat, "%lf, %lf, %lf\n", 
					ptr[i].GetFirstDocumentPoint().x, 
					ptr[i].GetFirstDocumentPoint().y, 
					ptr[i].GetFirstDocumentPoint().z);
			}
		}
		while(m_spheres.IncrementCurrentMsg());
	}
	fclose(dat);

}

void SurfDoc::CutlinesSaveAs()
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
                         TEXT("Golden Software Data (*.dat)\0*.dat\0")
                         TEXT("All Files (*.*)\0*.*\0");

	sprintf(lpstrFile, "%s\\izolines", directory);
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return;
	FILE *bln;
	bln = fopen(lpstrFile,"wt");
	//  3d линии
	if (this->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			size_t len = m_cutlines.GetCurrentMsg().GetPointsNumber();
			if (nFilterIndex == 1)
			{
				if (len)
					fprintf(bln, "%d, %d\n", len, 0);
			}
			for (size_t i = 0; i < len; i++)
			{			
				fprintf(bln, "%lf, %lf, %lf\n", 
					m_cutlines.GetCurrentMsg().GetDocumentPoint(i).x, 
					m_cutlines.GetCurrentMsg().GetDocumentPoint(i).y, 
					m_cutlines.GetCurrentMsg().GetDocumentPoint(i).z);
			}
		}
		while(this->m_cutlines.IncrementCurrentMsg());
	}
	fclose(bln);
}

void SurfDoc::UpdateZofSpheres(UINT len, int *z)
{
	UINT i = 0;
	if (this->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			if( i < len)
			{
				this->m_spheres.GetCurrentMsg().GetFirstDocumentPoint().z = z[i];
				i++;
			}
			else return;
		}
		while(this->m_spheres.IncrementCurrentMsg());
	}
}

typedef Well_3D * WELL_PTR  ;
void add_edge(int i, void * p, long i1, long i2, vector<int>* indexes)
{
	SurfDoc * pSurfDoc = reinterpret_cast<SurfDoc*> (p);
printf( "add_edge(i = %d int i1 = %d, int i2 = %d)\n", i, i1, i2);	
//printf( "pSurfDoc->m_drills_ObjectList.size() = %d)\n", pSurfDoc->m_drills_ObjectList.size());	

	int sz1 = indexes->size();
	if(i1 >= sz1 || i2 >= sz1)
	{
		printf("(i1 %d >= sz1 %d || i2 %d >= sz1 %d) -> return from add_edge \n", i1, sz1, i2, sz1);
		return;
	}
	i1 = (*indexes)[i1];
	i2 = (*indexes)[i2];
	int sz2 = pSurfDoc->m_drills_ObjectList.size();
	if(i1 >= sz2 || i2 >= sz2)
	{
		printf("(i1 %d >= sz2 %d || i2 %d >= sz2 %d) -> return from add_edge \n", i1, sz2, i2, sz2);
		return;
	}

	Well_3D ** pwell = new WELL_PTR[2];

	pwell[0] = dynamic_cast<Well_3D *>(pSurfDoc->m_drills_ObjectList[i1]);
	pwell[1] = dynamic_cast<Well_3D *>(pSurfDoc->m_drills_ObjectList[i2]);

	CPoint3 * pt = new CPoint3[2];
	if (i < 0)
	{
		for (size_t i = 1; i < pwell[0]->GetPointsNumber(); i++)
		{
			if(
				pwell[0]->GetPointsNumber()>i &&
				pwell[1]->GetPointsNumber()>i )
			{
				pt[0] = pwell[0]->GetDocumentPoint(i);
				pt[1] = pwell[1]->GetDocumentPoint(i);	
					
				COLORREF color;
				if (pwell[0]->GetColorSize() > i)
					color = pwell[0]->GetColor(i);
				else
					color = RGB(255,0,0);
				
				if (pt[0].bVisible && pt[1].bVisible)  
				{
					//pSurfDoc->AddLine(pt,2,color);
				}
				else
				{
					if (pt[0].bVisible && !pt[1].bVisible)
					{
						bool bVyklin = false;
						for (size_t j = i; j < pwell[1]->GetPointsNumber(); j++)
						{
							if (pwell[1]->GetDocumentPoint(j).bVisible){
								bVyklin = true;
								break;
							}
						}
						if (bVyklin)
						{
							color = pwell[0]->GetColor(i);
							pSurfDoc->AddSphere(
								(pt[0].x + pt[1].x)/2.0,
								(pt[0].y + pt[1].y)/2.0,
								pt[0].z,
								color);

							pt[1].x = (pt[0].x + pt[1].x)/2.0;
							pt[1].y = (pt[0].y + pt[1].y)/2.0;
							pt[1].z = pt[0].z;
							pt[1].bVisible = true;
							pSurfDoc->AddCutLine(pt,2,color);
						}
					}
					if (!pt[0].bVisible && pt[1].bVisible)
					{
						bool bVyklin = false;
						for (size_t j = i; j < pwell[0]->GetPointsNumber(); j++)
						{
							if (pwell[0]->GetDocumentPoint(j).bVisible){
								bVyklin = true;
								break;
							}
						}
						if (bVyklin)
						{
							color = pwell[1]->GetColor(i);
							pSurfDoc->AddSphere(
								(pt[0].x + pt[1].x)/2.0,
								(pt[0].y + pt[1].y)/2.0,
								pt[1].z,
								color);

							pt[0].x = (pt[0].x + pt[1].x)/2.0;
							pt[0].y = (pt[0].y + pt[1].y)/2.0;
							pt[0].z = pt[1].z;
							pt[0].bVisible = true;
							pSurfDoc->AddCutLine(pt,2,color);

						}
					}
				}
			}
		}
	}
	else
	{
		if(
			pwell[0]->GetPointsNumber()>(size_t)i &&
			pwell[1]->GetPointsNumber()>(size_t)i )
		{
			//bool tolsch_filter = false;
			double tolsch_deviation = -1.0;
			if (i > 2)
			{
				if (pwell[0]->GetDocumentPoint(i).bVisible
					&& pwell[0]->GetDocumentPoint(i-1).bVisible
					&& pwell[1]->GetDocumentPoint(i).bVisible
					&& pwell[1]->GetDocumentPoint(i-1).bVisible
					)
				{
					double h0 = pwell[0]->GetDocumentPoint(i-1).z - pwell[0]->GetDocumentPoint(i).z;
					double h1 = pwell[1]->GetDocumentPoint(i-1).z - pwell[1]->GetDocumentPoint(i).z;
					tolsch_deviation = fabs (h1-h0) / fabs (h1+h0);
					/*if (tolsch_deviation < 0.1)
					{
						tolsch_filter = true;
					}*/
				}
			}
			double glub_deviation = -1.0;
			double glub_deviation_x = 0.0;
			double glub_deviation_y = 0.0;
			if (i > 1)
			{
				if (pwell[0]->GetDocumentPoint(i).bVisible
					&& pwell[1]->GetDocumentPoint(i).bVisible
					)
				{
					double h0 = pwell[0]->GetDocumentPoint(i).z;
					double h1 = pwell[1]->GetDocumentPoint(i).z;
					double dist_xy = Distance_xy(pwell[0]->GetDocumentPoint(i), pwell[1]->GetDocumentPoint(i));
					// уклонение глубины подошвы текущего слоя
					glub_deviation = fabs (h1-h0) / fabs(dist_xy);
					glub_deviation_x = (h1-h0) / (pwell[1]->GetDocumentPoint(i).x - pwell[0]->GetDocumentPoint(i).x );
					glub_deviation_y = (h1-h0) / (pwell[1]->GetDocumentPoint(i).y - pwell[0]->GetDocumentPoint(i).y );
					/*if (tolsch_deviation < 0.1)
					{
						tolsch_filter = true;
					}*/
				}

			}
			pt[0] = pwell[0]->GetDocumentPoint(i);
			pt[1] = pwell[1]->GetDocumentPoint(i);	

			COLORREF color;
			if (pwell[0]->GetColorSize() > i)
				color = pwell[0]->GetColor(i);
			else
				color = RGB(255,0,0);
			
			if (pt[0].bVisible && pt[1].bVisible)  
			{
				//if (tolsch_filter)
				pSurfDoc->m_tria_grid.GetLastMsg().AddLine(i1,i2,pt,2,color);
				pSurfDoc->m_tria_grid.GetLastMsg().m_lines.GetLastMsg().tolsch_deviation = tolsch_deviation;
				pSurfDoc->m_tria_grid.GetLastMsg().m_lines.GetLastMsg().glub_deviation_x = glub_deviation_x;
				pSurfDoc->m_tria_grid.GetLastMsg().m_lines.GetLastMsg().glub_deviation_y = glub_deviation_y;
				pSurfDoc->m_tria_grid.GetLastMsg().m_lines.GetLastMsg().glub_deviation = glub_deviation;
				pSurfDoc->m_tria_grid.GetLastMsg().m_lines.GetLastMsg().delta_x = pwell[1]->GetDocumentPoint(i).x - pwell[0]->GetDocumentPoint(i).x;
				pSurfDoc->m_tria_grid.GetLastMsg().m_lines.GetLastMsg().delta_y = pwell[1]->GetDocumentPoint(i).y - pwell[0]->GetDocumentPoint(i).y;
			}
		}
	}
	delete[] pt;
	delete[] pwell;
}


void add_tria(int i, void * p, long i1, long i2, long i3, vector<int>* indexes)
{
	SurfDoc * pSurfDoc = reinterpret_cast<SurfDoc*> (p);
	printf( "add_tria(int i1 = %d, int i2 = %d, int i3 = %d)\n", i1, i2, i3);

	int sz1 = int(indexes->size());
	if(i1 >= sz1 || i2 >= sz1 || i3 >= sz1)
	{
		printf("(i1 %d >= sz1 %d || i2 %d >= sz1 %d || i3 %d >= sz1 %d) -> return from add_tria \n", i1, sz1, i2, sz1, i3, sz1);
		return;
	}
	i1 = (*indexes)[i1];
	i2 = (*indexes)[i2];
	i3 = (*indexes)[i3];
	int sz2 = (int)pSurfDoc->m_drills_ObjectList.size();
	if(i1 >= sz2 || i2 >= sz2 || i3 >= sz2)
	{
		printf("(i1 %d >= sz2 %d || i2 %d >= sz2 %d || i3 %d >= sz2 %d) -> return from add_tria \n", i1, sz2, i2, sz2, i3, sz2);
		return;
	}

	Well_3D * pwell_1 = dynamic_cast<Well_3D *>(pSurfDoc->m_drills_ObjectList[i1]);
	Well_3D * pwell_2 = dynamic_cast<Well_3D *>(pSurfDoc->m_drills_ObjectList[i2]);
	Well_3D * pwell_3 = dynamic_cast<Well_3D *>(pSurfDoc->m_drills_ObjectList[i3]);

	CPoint3 * pt = new CPoint3[3];
	if (i < 0)
	{
		for (int i = 1; i < (int)pwell_1->GetPointsNumber(); i++)
		{
			if(
				pwell_1->GetPointsNumber()>i &&
				pwell_2->GetPointsNumber()>i &&
				pwell_3->GetPointsNumber()>i )
			{
				pt[0] = pwell_1->GetDocumentPoint(i);
				pt[1] = pwell_2->GetDocumentPoint(i);	
				pt[2] = pwell_3->GetDocumentPoint(i);	

				COLORREF color;
				if (pwell_1->GetColorSize() > i)
					color = pwell_1->GetColor(i);
				else
					color = RGB(255,0,0);

				if (pt[0].bVisible && pt[1].bVisible && pt[2].bVisible) 
					pSurfDoc->AddPoligon(pt,3,color);

			}
		}
	}
	else
	{
		if(
			pwell_1->GetPointsNumber()>i &&
			pwell_2->GetPointsNumber()>i &&
			pwell_3->GetPointsNumber()>i )
		{
			pt[0] = pwell_1->GetDocumentPoint(i);
			pt[1] = pwell_2->GetDocumentPoint(i);	
			pt[2] = pwell_3->GetDocumentPoint(i);	

			COLORREF color;
			if (pwell_1->GetColorSize() > i)
				color = pwell_1->GetColor(i);
			else
				color = RGB(255,0,0);

			if (pt[0].bVisible && pt[1].bVisible && pt[2].bVisible) 
			{
				//pSurfDoc->AddPoligon(pt,3,color);
				pSurfDoc->m_tria_grid.GetLastMsg().AddTriangle(i1,i2,i3, pt[0], pt[1], pt[2], color);
			}
		}
	}
	delete[] pt;
}
void SurfDoc::WellsEdgesTriangulationPerSloj()
{
	this->m_drills_ObjectList.Init(this->m_drills, this);
	vector<double> vx,vy;
	vector<int> indexes;
	if (this->m_drills_ObjectList.size() > 0)
	{

		//НАДО получить максимальное количество точек в скважинах
		size_t maxPointsNumber = 0;
		for (int i = 0; i < this->m_drills_ObjectList.size(); i++)
		{
			Well_3D * pwell = dynamic_cast<Well_3D *>(this->m_drills_ObjectList[i]);
			size_t n = pwell->GetPointsNumber();
			if (maxPointsNumber < n) maxPointsNumber = n;
		}



		Well_3D * pw = dynamic_cast<Well_3D *>(this->m_drills_ObjectList[0]);
		//for (int sloj = 1; sloj < pw->GetPointsNumber(); sloj++)
		for (int sloj = 1; sloj < maxPointsNumber; sloj++)
		{
			vx.clear();
			vy.clear();
			indexes.clear();
			for (int i = 0; i < this->m_drills_ObjectList.size(); i++)
			{
				Well_3D * pwell = dynamic_cast<Well_3D *>(this->m_drills_ObjectList[i]);
				double x = pwell->GetFirstDocumentPoint().x;
				double y = pwell->GetFirstDocumentPoint().y;

				if(pwell->GetPointsNumber() > sloj && pwell->GetDocumentPoint(sloj).bVisible)
				{
					vx.push_back(x);
					vy.push_back(y);
					indexes.push_back(i);
				}
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			TriangulatedGrid3D tg3D(this);
			m_tria_grid.AddMsg(&tg3D);
			//m_tria_grid.GetLastMsg().Init(xMap, yMap);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//======================================================
			//======================================================
			//======================================================
			DelaunayTriangulation dct;

			// Delaunay Triangulation of well coordinates
			if (vx.size() > 1) dct.work(vx, vy, sloj, (void *)this, add_edge, &indexes);
			if (vx.size() > 2) dct.work(vx, vy, sloj, (void *)this, add_tria, &indexes);
			//======================================================
			//======================================================
			//======================================================
		}
	}
	m_tria_grid_ObjectList.Init(m_tria_grid, this);
}

void SurfDoc::WellsTriasTriangulation()
{
	this->m_drills_ObjectList.Init(this->m_drills, this);
	vector<double> vx,vy;
	vector<int> indexes;
	if (this->m_drills_ObjectList.size() > 0)
	{
		Well_3D * pw = dynamic_cast<Well_3D *>(this->m_drills_ObjectList[0]);
		for (int sloj = 1; sloj < pw->GetPointsNumber(); sloj++)
		{
			vx.clear();
			vy.clear();
			indexes.clear();
			for (int i = 0; i < this->m_drills_ObjectList.size(); i++)
			{
				Well_3D * pwell = dynamic_cast<Well_3D *>(this->m_drills_ObjectList[i]);
				double x = pwell->GetFirstDocumentPoint().x;
				double y = pwell->GetFirstDocumentPoint().y;

				if(pwell->GetPointsNumber() > sloj && pwell->GetDocumentPoint(sloj).bVisible)
				{
					vx.push_back(x);
					vy.push_back(y);
					indexes.push_back(i);
				}
			}

			//======================================================
			//======================================================
			//======================================================
			DelaunayTriangulation dct;

			// Delaunay Triangulation of well coordinates
			dct.work(vx, vy, sloj, (void *)this, add_tria, &indexes);
			//======================================================
			//======================================================
			//======================================================
		}
	}
}
void SurfDoc::WellsEdgesTriangulation()
{
	this->m_drills_ObjectList.Init(this->m_drills, this);
	vector<double> vx,vy;
	vector<int> indexes;
	for (int i = 0; i < this->m_drills_ObjectList.size(); i++)
	{
		Well_3D * pwell = dynamic_cast<Well_3D *>(this->m_drills_ObjectList[i]);
		double x = pwell->GetFirstDocumentPoint().x;
		double y = pwell->GetFirstDocumentPoint().y;

		vx.push_back(x);
		vy.push_back(y);
		indexes.push_back(i);
	}

	//======================================================
	//======================================================
	//======================================================
	DelaunayTriangulation dct;

	// Delaunay Triangulation of well coordinates
	if (vx.size() > 1) dct.work(vx, vy, -1, (void *)this, add_edge, &indexes);
	//======================================================
	//======================================================
	//======================================================
}
void SurfDoc::BlnProfilesIntersectionsBuild()
{
	vector<BlnProfile3D *> p_bln_profiles;p_bln_profiles.clear();
	if (this->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			//if (this->m_bln_profiles.GetCurrentMsg().IsCheckedEx())
			//{
				this->m_bln_profiles.GetCurrentMsg().m_plane.m_intersections.clear();
				BlnProfile3D * profile = &this->m_bln_profiles.GetCurrentMsg();
				p_bln_profiles.push_back(profile);

			//}
		}
		while(this->m_bln_profiles.IncrementCurrentMsg());
	}

	for (size_t iprofile = 0; iprofile < p_bln_profiles.size(); iprofile++)
	{
		BlnProfile3D * profile = p_bln_profiles[iprofile];

		if (this->m_bln_profiles.SetCurrentMsgOnFirst())
		{
			do
			{
				//if (this->m_bln_profiles.GetCurrentMsg().IsCheckedEx())
				//{
					BlnProfile3D * profile2 = &this->m_bln_profiles.GetCurrentMsg();
					if (profile && profile2 && profile != profile2)
					{
						profile->BuildIntersection(profile2);
						profile->m_plane.ReDraw();
					}
				//}
			}
			while(this->m_bln_profiles.IncrementCurrentMsg());
		}
	}
}


void SurfDoc::SurfacesFaultsCutlines(void)
{	
	short type_of_cutline = 4;
	bool toDrawPolygon = true;
	bool positive = true;
	if (this->m_surfaces.SetCurrentMsgOnFirst() && this->m_surfaces_ObjectList.m_bChecked)
	{
		int surf_number = 0;
		do
		{
			if (m_surfaces.GetCurrentMsg().m_bChecked)
			{
				if (this->m_faults.SetCurrentMsgOnFirst() && this->m_faults_ObjectList.m_bChecked)
				{
					int fault_number = 0;
					do
					{
						if (this->m_faults.GetCurrentMsg().m_bChecked)
						{
							m_surfaces.GetCurrentMsg().ClearBlankPolygonMatrix();

							m_surfaces.GetCurrentMsg().m_surface.Cutting(&this->m_faults.GetCurrentMsg().m_surface, 
								type_of_cutline, fault_number, surf_number, toDrawPolygon, positive,
								&m_surfaces.GetCurrentMsg(), 
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
								&m_surfaces.GetCurrentMsg().m_blank_polygon_matrix_ObjectList,
								&m_surfaces.GetCurrentMsg().m_blank_polygon_matrix
#else
								&m_surfaces.GetCurrentMsg().m_blank_polygones_ObjectList,
								&m_surfaces.GetCurrentMsg().m_blank_polygones
#endif								
								);
							fault_number++;
						}
					}
					while(this->m_faults.IncrementCurrentMsg());
				}
				m_surfaces.GetCurrentMsg().m_surface.CutLine(type_of_cutline, 0, (void *) NULL, m_surfaces.GetCurrentMsg(), surf_number );
				surf_number++;
			}
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
}

void SurfDoc::SurfacesAutoBlank(void)
{
   INFO("SurfacesAutoBlank()");
	if (!this->m_cube_size.Defined())
	{
		MessageBox(0, "Размер куба не был определён в базе\nПоэтому автобланкование поверхностей не было выполнено\nОпределите размерность куба", "SurfDoc::SurfacesAutoBlank", 0);
	}
	else
	{
		this->NoBlank(false);
		//this->LoadBlankBln();
      //INFOFMT("order_by = %s", % (const char *)order_by);



		for (vector<surface_blank_functions_list_item *>::iterator
			it = GeoSurface::surface_blank_functions_list.begin();
			it != GeoSurface::surface_blank_functions_list.end(); it++)
		{
			if ((*it))
			{
				GeoSurface * surf_obj = this->FindGeoSurface((*it)->id_surf_obj);
				GeoSurface * surf_param = this->FindGeoSurface((*it)->id_surf_param);
				if(surf_obj)
				{
					if (!surf_obj->m_surface.IsTheSameSize(this->m_cube_size))
					{
						CString s;
						s.Format("Геоповерхнность %s не соразмерна кубу\nВыполнение функции SurfacesAutoBlank прервано",
							surf_obj->GetName().c_str());
						AfxMessageBox(s);
						return ;
					}
				}
				if(surf_param)
				{
					if (!surf_param->m_surface.IsTheSameSize(this->m_cube_size))
					{
						CString s;
						s.Format("Геоповерхнность %s не соразмерна кубу\nВыполнение функции SurfacesAutoBlank прервано",
							surf_param->GetName().c_str());
						AfxMessageBox(s);
						return ;
					}
				}
			}
		}

		for (vector<surface_blank_functions_list_item *>::iterator
			it = GeoSurface::surface_blank_functions_list.begin();
			it != GeoSurface::surface_blank_functions_list.end(); it++)
		{
			if ((*it))
			{
				GeoSurface * surf_obj = this->FindGeoSurface((*it)->id_surf_obj);
				GeoSurface * surf_param = this->FindGeoSurface((*it)->id_surf_param);
				if (surf_obj && surf_param)
				{
					switch((*it)->id_blank_fun)
					{
					case 1:
						surf_obj->BlankAbove(*surf_param);
						break;
					case 2:
						surf_obj->BlankUnder(*surf_param);
						break;
					}
				}
			}
		}




      INFO("SurfacesAutoBlank() return;");

		return;

		for (vector<surface_blank_order_list_item *>::iterator it = GeoSurface::surface_blank_order_list.begin();
			it != GeoSurface::surface_blank_order_list.end(); it++)
		{
			if ((*it))
			{
				GeoSurface * geo_surf = this->FindGeoSurface((*it)->id_surf);
				if(geo_surf)
				{
					if (!geo_surf->m_surface.IsTheSameSize(this->m_cube_size))
					{
						CString s;
						s.Format("Геоповерхнность %s не соразмерна кубу\nВыполнение функции SurfacesAutoBlank прервано",
							geo_surf->GetName().c_str());
						AfxMessageBox(s);
						return ;
					}
				}
			}
		}
		// Аналогично функции
		//void SurfDoc::GeoSurfaces_BlankAbove_By_SurfEngGeoElementMapping()
		//{
		//for (size_t k1 = 0; k1 < GeoSurface::surface_blank_order_list.size(); k1++)
		for (vector<surface_blank_order_list_item *>::reverse_iterator rit1 = GeoSurface::surface_blank_order_list.rbegin();
			rit1 != GeoSurface::surface_blank_order_list.rend(); rit1++)
		{
			if ((*rit1) && (*rit1)->check_blank_me)
			{
				GeoSurface * surf1 = this->FindGeoSurface((*rit1)->id_surf);
				if (surf1)
				{
					if ((*rit1)->check_blank_me_up)
					{
						//for (size_t k2 = k1+1; k2 < GeoSurface::surface_blank_order_list.size(); k2++)
						for (vector<surface_blank_order_list_item *>::reverse_iterator rit2 = rit1 + 1;
							rit2 != GeoSurface::surface_blank_order_list.rend(); rit2++)
						{
							if ((*rit2) && (*rit2)->check_blank_by_me_up)
							{
								GeoSurface * surf2 = this->FindGeoSurface((*rit2)->id_surf);
								if (surf2)
								{
									if ((*rit1)->check_blank_me_up_above)
									{
										if (!surf1->BlankAbove(*surf2))
										{
											char str[1024];
											sprintf(str, "if (!surf1(\"%s\")->BlankAbove(*surf2(\"%s\")))", 
												surf1->GetName().c_str(), 
												surf2->GetName().c_str());
											MessageBox(0,str,"SurfacesAutoBlank",0);
										}
									}
									else
									{
										if (!surf1->BlankUnder(*surf2))
										{
											char str[1024];
											sprintf(str, "if (!surf1(\"%s\")->BlankUnder(*surf2(\"%s\")))", 
												surf1->GetName().c_str(), 
												surf2->GetName().c_str());
											MessageBox(0,str,"SurfacesAutoBlank",0);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		//}
		for (vector<surface_blank_order_list_item *>::iterator it1 = GeoSurface::surface_blank_order_list.begin();
			it1 != GeoSurface::surface_blank_order_list.end(); it1++)
		{
			if ((*it1) && (*it1)->check_blank_me)
			{
				GeoSurface * surf1 = this->FindGeoSurface((*it1)->id_surf);
				if (surf1)
				{
					if ((*it1)->check_blank_me_down)
					{
						//for (size_t k2 = k1+1; k2 < GeoSurface::surface_blank_order_list.size(); k2++)
						for (vector<surface_blank_order_list_item *>::iterator it2 = it1 + 1;
							it2 != GeoSurface::surface_blank_order_list.end(); it2++)
						{
							if ((*it2) && (*it2)->check_blank_by_me_down)
							{
								GeoSurface * surf2 = this->FindGeoSurface((*it2)->id_surf);
								if (surf2)
								{
									if ((*it1)->check_blank_me_up_above)
									{
										if (!surf1->BlankAbove(*surf2))
										{
											char str[1024];
											sprintf(str, "if (!surf1(\"%s\")->BlankAbove(*surf2(\"%s\")))", 
												surf1->GetName().c_str(), 
												surf2->GetName().c_str());
											MessageBox(0,str,"SurfacesAutoBlank",0);
										}
									}
									else
									{
										if (!surf1->BlankUnder(*surf2))
										{
											char str[1024];
											sprintf(str, "if (!surf1(\"%s\")->BlankUnder(*surf2(\"%s\")))", 
												surf1->GetName().c_str(), 
												surf2->GetName().c_str());
											MessageBox(0,str,"SurfacesAutoBlank",0);
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

void SurfDoc::SurfacesBlank(void)
{
	//this->NoBlank(false);
	this->LoadBlankBln();
	if (this->m_surfaces.SetCurrentMsgOnFirst() && this->m_surfaces_ObjectList.m_bChecked)
	{
		int surf_number = 0;
		do
		{
			if (m_surfaces.GetCurrentMsg().m_bChecked)
			{
#if 1
				m_surfaces.GetCurrentMsg().m_surface.Blank(this->m_blanklines, false, m_surfaces.GetCurrentMsg(), NULL);
#else
				if(this->m_blanklines.SetCurrentMsgOnFirst())
				{
					do
					{
						m_surfaces.GetCurrentMsg().m_surface.Blank(this->m_blanklines.GetCurrentMsg(), false, &m_surfaces.GetCurrentMsg(), NULL);
					}
					while(this->m_blanklines.IncrementCurrentMsg());
				}	
#endif
				surf_number++;
			}
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
}

void SurfDoc::FaultsBlank(void)
{
	this->LoadBlankBln();
	// это вынести в отдельную функцию бланкования разломов
	if (this->m_faults.SetCurrentMsgOnFirst() && this->m_faults_ObjectList.m_bChecked)
	{
		int fault_number = 0;
		do
		{
			if (m_faults.GetCurrentMsg().m_bChecked)
			{
				if(this->m_blanklines.SetCurrentMsgOnFirst())
				{
					do
					{
						Line3D fault_blank_line = this->m_blanklines.GetCurrentMsg();
						for (int i = 0; i < fault_blank_line.GetPointsNumber(); i++)
						{
							fault_blank_line.GetDocumentPoint(i).Convert(m_faults.GetCurrentMsg().m_surface.m_zflag);
						}
						m_faults.GetCurrentMsg().m_surface.Blank(fault_blank_line, false, m_faults.GetCurrentMsg(), NULL);
					}
					while(this->m_blanklines.IncrementCurrentMsg());
				}				
				fault_number++;
			}
		}
		while(m_faults.IncrementCurrentMsg());
	}
}

void SurfDoc::BrokenPlanesBlank(void)
{
	if (this->m_surfaces.SetCurrentMsgOnFirst() && this->m_surfaces_ObjectList.m_bChecked)
	{
		int surf_number = 0;
		do
		{
			if (m_surfaces.GetCurrentMsg().m_bChecked)
			{				
				if(this->m_brokenPlanes.SetCurrentMsgOnFirst())
				{
					do
					{
						size_t bp_len = this->m_brokenPlanes.GetCurrentMsg().m_vMapBlnProfiles.Size();
						Line3D blank_line;
						if (this->m_brokenPlanes.GetCurrentMsg().m_lParam & OBJECT_FLAG_INSIDE_BLANK_BIT)
							blank_line.m_lParam |= OBJECT_FLAG_INSIDE_BLANK_BIT;
						else
							blank_line.m_lParam &= ~OBJECT_FLAG_INSIDE_BLANK_BIT;


						for (size_t i = 0; i < bp_len; i++)
						{
							CPoint3 pt3;
							CPoint2 pt2 = this->m_brokenPlanes.GetCurrentMsg().m_vMapBlnProfiles[i];
							pt3.x = pt2.x;
							pt3.y = pt2.y;
							pt3.z = 0.0;
							blank_line.PushBack(pt3);
						}

						m_surfaces.GetCurrentMsg().m_surface.Blank(blank_line,true, m_surfaces.GetCurrentMsg(), NULL);
					}
					while(this->m_brokenPlanes.IncrementCurrentMsg());
				}
				surf_number++;
			}
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
}

void SurfDoc::LoadBlankBln(void)
{
	char lpstrFile[1024];
	if (OpenFileDlg(this->hSurfWnd, "Golden Software Blanking (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
	{
		vector<vector<vector<double> > > vvvd;
		vector<int> vinside;
		if (0 == ReadBlnFile(lpstrFile, &vvvd, &vinside))
		{
			if (this)
			{
				for(size_t nline = 0; nline < vvvd.size(); nline++)
				{
					this->AddBlankLine(vinside[nline]);
					for (size_t npoint = 0; npoint < vvvd[nline].size(); npoint++)
					{
						CPoint3 pt(0.0,0.0,0.0,true);
						for (size_t ndim = 0; ndim < vvvd[nline][npoint].size(); ndim++)
						{
							switch(ndim)
							{
							case 0:
								pt.x = vvvd[nline][npoint][ndim];
								break;
							case 1:
								pt.y = vvvd[nline][npoint][ndim];
								break;
							case 2:
								pt.z = vvvd[nline][npoint][ndim];
								break;
							}
						}
						if(this->m_blanklines.SetCurrentMsgOnLast())
						{
							this->m_blanklines.GetCurrentMsg().PushBack(pt);
						}
					}
				}
			}
		}
	}
}

void SurfDoc::NoBlank(bool toClearBlankLines)
{
	if (this->m_surfaces.SetCurrentMsgOnFirst() && this->m_surfaces_ObjectList.m_bChecked)
	{
		do
		{
			if (m_surfaces.GetCurrentMsg().m_bChecked)
			{
				m_surfaces.GetCurrentMsg().NoBlank();
			}
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst() && this->m_faults_ObjectList.m_bChecked)
	{
		do
		{
			if (m_faults.GetCurrentMsg().m_bChecked)
			{
				m_faults.GetCurrentMsg().NoBlank();
			}
		}
		while(m_faults.IncrementCurrentMsg());
	}
	if(toClearBlankLines) this->ClearBlankLines();
}

void SurfDoc::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "SurfDoc" , 0);
}

bool SurfDoc::ColorDialog(void)
{
	return false;
}

COLORREF SurfDoc::GetColor(void)
{
	return COLORREF();
}

void SurfDoc::SetColor(COLORREF color)
{
}

void SurfDoc::AddObject(Object * object)
{
printf("SurfDoc::AddObject\n");
	if (object)
	{
		this->m_objects.AddMsg(object);
		this->m_objects_ObjectList.Init(this->m_objects, this);
	}
}

Collection* SurfDoc::CreateNewCollection(void)
{
	// готовим объект 
	Collection collection(this);
	this->m_collections.AddMsg(&collection);		
	this->m_collections_ObjectList.Init(this->m_collections, this);
	return &this->m_collections.GetLastMsg();
}

bool SurfDoc::AddObjectToLastCollection(Object * object)
{
	if (object)
	{
		if (this->m_collections.SetCurrentMsgOnLast())
		{
			this->m_collections.GetCurrentMsg().AddObject(object);
			this->m_collections.GetCurrentMsg().m_objects_ObjectList.Init(this->m_collections.GetCurrentMsg().m_objects, &this->m_collections.GetCurrentMsg());
			return true;
		}
	}
	return false;
}

bool SurfDoc::AddObjectToCurrentCollection(Object * object)
{
	if (object)
	{
		if (this->m_collections.CheckCurrentMsg())
		{
			this->m_collections.GetCurrentMsg().AddObject(object);
			this->m_collections.GetCurrentMsg().m_objects_ObjectList.Init(this->m_collections.GetCurrentMsg().m_objects, &this->m_collections.GetCurrentMsg());
			return true;
		}
	}
	return false;
}

GeoCatch * SurfDoc::CreateNewGeoCatch(void)
{
	// готовим объект геологической ловушки
	GeoCatch geo_catch(this);
	this->m_geo_catches.AddMsg(&geo_catch);		
	this->m_geo_catches_ObjectList.Init(this->m_geo_catches, this);
	return &m_geo_catches.GetLastMsg();
}
long SurfDoc::GetIDSurfForNewGridDataOrSurface(void)
{
	long id_surf = 0;
	if (this->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{		
			long id = m_grid_data.GetCurrentMsg().id_surf;
			if (id_surf < id)
				id_surf = id;
		}
		while(this->m_grid_data.IncrementCurrentMsg());
	}
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{		
			long id = m_surfaces.GetCurrentMsg().id_surf;
			if (id_surf < id)
				id_surf = id;
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	return ++id_surf;
}
GridData * SurfDoc::CreateNewGridData(long id_surf)
{
	// готовим объект GridData
	GridData grid_data(this);
	grid_data.id_surf = id_surf < 0 ? GetIDSurfForNewGridDataOrSurface() : id_surf;
	this->m_grid_data.AddMsg(&grid_data);		
	this->m_grid_data_ObjectList.Init(this->m_grid_data, this);
	return &m_grid_data.GetLastMsg();
}


Cube4D * SurfDoc::CreateNewCube(void)
{
	printf("SurfDoc::CreateNewCube\n");
	// готовим объект GridData
	Cube4D cube(this);
	this->m_cubes.AddMsg(&cube);		
	this->m_cubes_ObjectList.Init(this->m_cubes, this);
	return &m_cubes.GetLastMsg();
}
#include <dime/Model.h>

bool SurfDoc::LoadAndScaleDxf_onXY()
{
	char infile[1024];
	char outfile[1024];
	char blnfile[1024];
	if (OpenFileDlg(0, "AutoCAD DXF (*.dxf)\0*.dxf\0All files \0*.*\0", infile) == S_OK)
	{
		printf("infile = %s\n",  infile);

		dimeModel model; 
		dxfConverter converter;
		bool res_load = dxfConverter::Loading(model, infile);
		if (res_load && OpenFileDlg(0, "Scale Y BLN (*.bln)\0*.bln\0All files \0*.*\0", blnfile) == S_OK)
		{	

		printf("blnfile = %s\n",  blnfile);

		vdouble x, y;
			int inside;
			if ( 0 == ReadBlnFile(blnfile, x, y, inside))
			{
				double x1w = x(0), x1a = y(0);
				double y1w = x(1), y1a = y(1);
				double x2w = x(2), x2a = y(2);
				double y2w = x(3), y2a = y(3);
				bool res_scale = converter.XYScaling(model, x1w, x1a, x2w, x2a, y1w, y1a, y2w, y2a);
				DWORD nFilterIndex;
				sprintf(outfile, "\0");
				if (res_scale && SaveFileDlg(0,outfile, "AutoCAD DXF (*.dxf)\0*.dxf\0All files \0*.*\0", nFilterIndex) == S_OK)
				{
					return dxfConverter::Saving(model, outfile);
				}
			}
		}
	}
	return false;
}
bool SurfDoc::LoadAndScaleDxf_onY()
{
	char infile[1024];
	char outfile[1024];
	char blnfile[1024];
	if (OpenFileDlg(0, "AutoCAD DXF (*.dxf)\0*.dxf\0All files \0*.*\0", infile) == S_OK)
	{
		printf("infile = %s\n",  infile);

		dimeModel model; 
		dxfConverter converter;
		bool res_load = dxfConverter::Loading(model, infile);
		if (res_load && OpenFileDlg(0, "Scale Y BLN (*.bln)\0*.bln\0All files \0*.*\0", blnfile) == S_OK)
		{	

		printf("blnfile = %s\n",  blnfile);

		vdouble x, y;
			int inside;
			if ( 0 == ReadBlnFile(blnfile, x, y, inside))
			{
				double z1w = x(0), y1a = y(0);
				double z2w = x(1), y2a = y(1);
				bool res_scale = converter.YScaling(model, z1w, y1a, z2w, y2a);
				DWORD nFilterIndex;
				sprintf(outfile, "\0");
				if (res_scale && SaveFileDlg(0,outfile, "AutoCAD DXF (*.dxf)\0*.dxf\0All files \0*.*\0", nFilterIndex) == S_OK)
				{
					return dxfConverter::Saving(model, outfile);
				}
			}
		}
	}
	return false;
}
#if DFX_LAYER_FROM_OBJECT

void SurfDoc::CreateNewDxf(void)
{
	printf("SurfDoc::CreateNewDxf\n");
	// готовим объект dxfConverter
	dxfConverter converter(this);
	this->m_dxfConverters.AddMsg(&converter);		
	this->m_dxfConverters_ObjectList.Init(this->m_dxfConverters, this);
}

bool SurfDoc::InitLastDxf(void)
{
	if (this->m_dxfConverters.SetCurrentMsgOnLast())
	{
		return this->m_dxfConverters.GetCurrentMsg().Load();
	}
	return false;
}
#endif
#if !VIEW_ONLY_VERSION
void SurfDoc::CreateNewAutoBuildProfile(void)
{
	printf("SurfDoc::CreateNewAutoBuildProfile\n");
	// готовим объект AutoBuildProfile
	AutoBuildProfile ob(this);
	this->m_auto_build_profiles.AddMsg(&ob);		
	this->m_auto_build_profiles_ObjectList.Init(this->m_auto_build_profiles, this);
}
#endif

bool SurfDoc::InitGeoCatch_GorizontPlane(void)
{
	if (this->m_geo_catches.SetCurrentMsgOnLast()
		&& this->m_spheres.SetCurrentMsgOnLast())
	{
		return this->m_geo_catches.GetCurrentMsg().InitGorizontPlane(
			this->m_spheres.GetCurrentMsg().GetFirstDocumentPoint());
	}
	return false;
}
void SurfDoc::BlankingOfGeoCatchBlankLines(void)
{
	if (this->m_geo_catches.SetCurrentMsgOnLast())
	{
		this->m_geo_catches.GetCurrentMsg().BlankingOfGorizontPlaneBlankLines();
	}
}

void SurfDoc::BlankGeoCatchGorizontPlane(void)
{
	if (this->m_geo_catches.SetCurrentMsgOnLast())
	{
		this->m_geo_catches.GetCurrentMsg().BlankLastGorizontPlane();
	}
}

CPoint3 SurfDoc::ZoomInv(CPoint3& pt_view)
{
	CPoint3 pt_doc;				
	pt_doc.bVisible = pt_view.bVisible;
	pt_doc.z = m_zd_zoom_center + pt_view.z / this->m_zoomZ;
	pt_doc.y = m_yd_zoom_center + pt_view.y / this->m_zoomY;
	pt_doc.x = m_xd_zoom_center + pt_view.x / this->m_zoomX;
	return pt_doc;
}

bool SurfDoc::SerializeFileBlock(FileBlockInfo& fbi, Archive& ar)
{
	switch(fbi.blockType)
	{
	case 5:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						// layers
						ar << this->m_defaut_layer;
						ar << this->m_layers;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						// layers
						ar >> this->m_defaut_layer;												
						if (Archive::OpenFileAsImport)
							ar.ReadStdMapAsImport(this->m_layers);
						else
							ar >> this->m_layers;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 10:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						// zoom params
						ar << this->m_bEqialZoomXYZ;
						ar << this->m_bEqialZoomXY;

						ar << this->m_zoomCoefXYZ;
						ar << this->m_zoomCoefXY;
						ar << this->m_zoomXY;

						ar << this->m_zoomX;
						ar << this->m_zoomY;
						ar << this->m_zoomZ;

						ar << this->m_xd_zoom_center;
						ar << this->m_yd_zoom_center;
						ar << this->m_zd_zoom_center;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						// zoom params
						ar >> this->m_bEqialZoomXYZ;
						ar >> this->m_bEqialZoomXY;

						ar >> this->m_zoomCoefXYZ;
						ar >> this->m_zoomCoefXY;
						ar >> this->m_zoomXY;

						ar >> this->m_zoomX;
						ar >> this->m_zoomY;
						ar >> this->m_zoomZ;

						ar >> this->m_xd_zoom_center;
						ar >> this->m_yd_zoom_center;
						ar >> this->m_zd_zoom_center;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 20:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar << this->m_xd_min;
						ar << this->m_yd_min;
						ar << this->m_zd_min;
			            
						ar << this->m_xd_max;
						ar << this->m_yd_max;
						ar << this->m_zd_max;
			            
						ar << this->m_xv_min;
						ar << this->m_yv_min;
						ar << this->m_zv_min;
						
						ar << this->m_xv_max;
						ar << this->m_yv_max;
						ar << this->m_zv_max;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar >> this->m_xd_min;
						ar >> this->m_yd_min;
						ar >> this->m_zd_min;
			            
						ar >> this->m_xd_max;
						ar >> this->m_yd_max;
						ar >> this->m_zd_max;
			            
						ar >> this->m_xv_min;
						ar >> this->m_yv_min;
						ar >> this->m_zv_min;
						
						ar >> this->m_xv_max;
						ar >> this->m_yv_max;
						ar >> this->m_zv_max;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 25:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 2:
					{
						ar << this->m_alpha_gdiplus_profiles;
					}
				case 1:
					{
						ar << this->m_bDrawStatusString;
						ar << this->m_bDrawGeoid;
						ar << this->m_bDrawCube;


						ar << this->m_bDrawCutPlane;
						for (int i=0; i < 4; i++)
						{
							ar << this->m_cut_plane_v[i];
							ar << this->m_cut_plane_d[i];
						}
						

						ar << this->m_bDrawXYZCutPlanes;
						ar << this->m_X;
						ar << this->m_Y;
						ar << this->m_Z;

						ar << this->m_sphere_radius;		            
						ar << this->m_sphere_slices;
						ar << this->m_sphere_stacks;		            
						
						ar << this->m_razlomThickness;

						ar << this->m_palette;

						ar << this->m_nColormap;
						ar << this->m_bInverseColormap;
						ar << this->m_bLocalColormap;
						ar << this->m_bUseColormapOnSurf;

						ar << this->m_bFlatShading;

						
						ar << this->m_alpha_plane;
						ar << this->m_alpha;

						ar << this->m_fRangeX;
						ar << this->m_fRangeY;
						ar << this->m_fRangeZ;

						ar << this->m_bFastCutting;

						int surface_draw_mode = Surface3D::s_draw_mode;
						ar << surface_draw_mode;

						int line_draw_mode = Line3D::s_line3d_draw_mode;
						ar << line_draw_mode;

						//ar.Write((unsigned char *)this->m_LightParam, 11*sizeof(int));
						for(int i = 0; i < 11; i++)
							ar << this->m_LightParam[i];				
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 2:
					{
						ar >> this->m_alpha_gdiplus_profiles;
					}
				case 1:
					{
						ar >> this->m_bDrawStatusString;
						ar >> this->m_bDrawGeoid;
						ar >> this->m_bDrawCube;


						ar >> this->m_bDrawCutPlane;
						for (int i=0; i < 4; i++)
						{
							ar >> this->m_cut_plane_v[i];
							ar >> this->m_cut_plane_d[i];
						}

						ar >> this->m_bDrawXYZCutPlanes;
						ar >> this->m_X;
						ar >> this->m_Y;
						ar >> this->m_Z;

						ar >> this->m_sphere_radius;		            
						ar >> this->m_sphere_slices;
						ar >> this->m_sphere_stacks;		            
						
						ar >> this->m_razlomThickness;

						ar >> this->m_palette;

						ar >> this->m_nColormap;
						ar >> this->m_bInverseColormap;
						ar >> this->m_bLocalColormap;
						ar >> this->m_bUseColormapOnSurf;

						ar >> this->m_bFlatShading;

						
						ar >> this->m_alpha_plane;
						ar >> this->m_alpha;

						ar >> this->m_fRangeX;
						ar >> this->m_fRangeY;
						ar >> this->m_fRangeZ;

						ar >> this->m_bFastCutting;

						int surface_draw_mode;
						ar >> surface_draw_mode;
						Surface3D::s_draw_mode = (Surface3D::draw_mode)surface_draw_mode;

						int line_draw_mode;
						ar >> line_draw_mode;
						Line3D::s_line3d_draw_mode = (Line3D::line3d_draw_mode)line_draw_mode;
						if (Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
						{

							CheckMenuItem(GetMenu( ::GetParent( this->hSurfWnd ) ), 
								ID_VIEW_LINES_DRAW_MODE,
								MF_BYCOMMAND | MF_CHECKED);
						}
						else
						{

							CheckMenuItem(GetMenu( ::GetParent( this->hSurfWnd ) ), 
								ID_VIEW_LINES_DRAW_MODE,
								MF_BYCOMMAND | MF_UNCHECKED);
						}
						//ar.Read((unsigned char *)this->m_LightParam, 11*sizeof(int));
						for(int i = 0; i < 11; i++)
							ar >> this->m_LightParam[i];
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 28:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar << GridData::line_to_interpolate_points;
						ar << GridData::s_number_line_interpolated_points;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar >> GridData::line_to_interpolate_points;
						ar >> GridData::s_number_line_interpolated_points;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 30:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 3:
					{
						ar.m_use_object_version = 0;
						ar << this->m_auto_build_profiles;	ar << this->m_auto_build_profiles_ObjectList;
					}
					// do not break!!!
				case 2:
					{
						ar.m_use_object_version = 0;
						ar << this->m_grid_data;	ar << this->m_grid_data_ObjectList;
						ar << this->m_objects;		ar << this->m_objects_ObjectList;
						ar << this->m_collections;	ar << this->m_collections_ObjectList;
					}
					// do not break!!!
				case 1:
					{
						ar.m_use_object_version = 0;

						ar << this->m_surfaces;		ar << this->m_surfaces_ObjectList;
						ar << this->m_faults;		ar << this->m_faults_ObjectList;
						ar << this->m_geo_catches;	ar << this->m_geo_catches_ObjectList;

						ar.m_use_object_version = 0;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 3:
					{
						ar >> this->m_auto_build_profiles;		ar >> this->m_auto_build_profiles_ObjectList;		this->m_auto_build_profiles_ObjectList.Init(this->m_auto_build_profiles, this);
					}
					// do not break!!!				
				case 2:
					{
						ar >> this->m_grid_data;		ar >> this->m_grid_data_ObjectList;		this->m_grid_data_ObjectList.Init(this->m_grid_data, this);
						ar >> this->m_objects;			ar >> this->m_objects_ObjectList;		this->m_objects_ObjectList.Init(this->m_objects, this);
						ar >> this->m_collections;		ar >> this->m_collections_ObjectList;	this->m_collections_ObjectList.Init(this->m_collections, this);
					}
					// do not break!!!
				case 1:
					{
						ar >> this->m_surfaces;			ar >> this->m_surfaces_ObjectList;		this->m_surfaces_ObjectList.Init(this->m_surfaces, this);
						ar >> this->m_faults;			ar >> this->m_faults_ObjectList;		this->m_faults_ObjectList.Init(this->m_faults, this);
						ar >> this->m_geo_catches;		ar >> this->m_geo_catches_ObjectList;	this->m_geo_catches_ObjectList.Init(this->m_geo_catches, this);
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
#if DFX_LAYER_FROM_OBJECT
	case 32://DXF only
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar.m_use_object_version = 0;
						ar << this->m_dxfConverters;	ar << this->m_dxfConverters_ObjectList;
					}
					// do not break!!!
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar >> this->m_dxfConverters;	ar >> this->m_dxfConverters_ObjectList; this->m_dxfConverters_ObjectList.Init(this->m_dxfConverters, this);
					}
					// do not break!!!
				default:
					{
						return false;
					}
				}
			}
		}
		break;
#endif
	case 35: // cubes
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 2:
					{
						ar << this->m_cube_size;
					}
				case 1:
					{
						ar.m_use_object_version = 0;
						ar << this->m_cubes;	ar << this->m_cubes_ObjectList;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 2:
					{
						ar >> this->m_cube_size;
					}
				case 1:
					{
						ar >> this->m_cubes;		ar >> this->m_cubes_ObjectList;		this->m_cubes_ObjectList.Init(this->m_cubes, this);
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 37:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 3:
					{
						ar << GeoSurface::surface_order_list;
						ar << GeoSurface::surface_blank_order_list;
					}
				case 2:
					{
						ar << surf_eng_geo_element_mapping;
					}
				case 1:
					{
						ar << this->m_geo_colomns;	ar << this->m_geo_colomns_ObjectList;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 3:
					{
						ar >> GeoSurface::surface_order_list;
						ar >> GeoSurface::surface_blank_order_list;
					}
				case 2:
					{
						ar >> surf_eng_geo_element_mapping;
					}
				case 1:
					{
						ar >> this->m_geo_colomns;		ar >> this->m_geo_colomns_ObjectList;		this->m_geo_colomns_ObjectList.Init_std_map(this->m_geo_colomns, this);
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 40:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar.m_use_object_version = 0;

						ar << this->m_points;		ar << this->m_points_ObjectList;
						ar << this->m_spheres;		ar << this->m_spheres_ObjectList;
						ar << this->m_lines;		ar << this->m_lines_ObjectList;
						ar << this->m_cutlines;		ar << this->m_cutlines_ObjectList;

						ar << this->m_triangles;	ar << this->m_triangles_ObjectList;
						ar << this->m_polygones;	ar << this->m_polygones_ObjectList;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar >> this->m_points;		ar >> this->m_points_ObjectList;	this->m_points_ObjectList.Init(this->m_points, this);
						ar >> this->m_spheres;		ar >> this->m_spheres_ObjectList;	this->m_spheres_ObjectList.Init(this->m_spheres, this);
						ar >> this->m_lines;		ar >> this->m_lines_ObjectList;		this->m_lines_ObjectList.Init(this->m_lines, this);
						ar >> this->m_cutlines;		ar >> this->m_cutlines_ObjectList;	this->m_cutlines_ObjectList.Init(this->m_cutlines, this);

						ar >> this->m_triangles;	ar >> this->m_triangles_ObjectList;	this->m_triangles_ObjectList.Init(this->m_triangles, this);
						ar >> this->m_polygones;	ar >> this->m_polygones_ObjectList;	this->m_polygones_ObjectList.Init(this->m_polygones, this);
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 50://Wells
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 5:
					{
						ar <<  Well_3D::wells_draw_list;
					}
				case 4:
					{
						double karotazh_scale_2d = Karotazh::s_scale_2d;
						ar << karotazh_scale_2d;

						bool disp_point_values_2d = Karotazh::s_disp_point_values_2d;
						ar << disp_point_values_2d;

					}
				case 3:
					{

						int karotazh_slices = Karotazh::slices;
						ar << karotazh_slices;

						int karotazh_stacks = Karotazh::stacks;
						ar << karotazh_stacks;

						int karotazh_alpha = Karotazh::s_alpha;
						ar << karotazh_alpha;

						bool karotazh_checked = Karotazh::s_checked;
						ar << karotazh_checked;

						bool disp_point_values = Karotazh::s_disp_point_values;
						ar << disp_point_values;

						double karotazh_scale = Karotazh::s_scale;
						ar << karotazh_scale;

						bool karotazh_logarithmic_scale = Karotazh::s_logarithmic_scale;
						ar << karotazh_logarithmic_scale;

						bool scale_from_zero = Karotazh::s_scale_from_zero;
						ar << scale_from_zero;


						ar <<  Well_3D::karotazh_list;
					}
				case 2:
					{
						int sloj_number_to_save = Well_3D::s_sloj_number_to_save;
						ar << sloj_number_to_save;

						bool use_sloj_names = Well_3D::s_use_sloj_names;
						ar << use_sloj_names;

						bool show_all_sloi = Well_3D::s_show_all_sloi;
						ar << show_all_sloi;
					}
				case 1:
					{
						ar.m_use_object_version = 0;

						ar << this->m_drills;		ar << this->m_drills_ObjectList;
						ar << this->m_tria_grid;	ar << this->m_tria_grid_ObjectList;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 5:
					{
						ar >> Well_3D::wells_draw_list;
					}
				case 4:
					{
						double karotazh_scale_2d;
						ar >> karotazh_scale_2d;
						Karotazh::s_scale_2d = karotazh_scale_2d;

						bool disp_point_values_2d;
						ar >> disp_point_values_2d;
						Karotazh::s_disp_point_values_2d = disp_point_values_2d;

					}
				case 3:
					{
						int karotazh_slices;
						ar >> karotazh_slices;
						Karotazh::slices = karotazh_slices;

						int karotazh_stacks;
						ar >> karotazh_stacks;
						Karotazh::stacks = karotazh_stacks;

						int karotazh_alpha;
						ar >> karotazh_alpha; 
						Karotazh::s_alpha = karotazh_alpha;

						bool karotazh_checked;
						ar >> karotazh_checked;
						Karotazh::s_checked = karotazh_checked;

						bool disp_point_values;
						ar >> disp_point_values;
						Karotazh::s_disp_point_values = disp_point_values;

						double karotazh_scale;
						ar >> karotazh_scale;
						Karotazh::s_scale = karotazh_scale;

						bool karotazh_logarithmic_scale;
						ar >> karotazh_logarithmic_scale;
						Karotazh::s_logarithmic_scale = karotazh_logarithmic_scale;

						bool scale_from_zero;
						ar >> scale_from_zero;
						Karotazh::s_scale_from_zero = scale_from_zero;


						if(Archive::OpenFileAsImport)
						{
							ar.ReadStdVectorAsImport(Well_3D::karotazh_list);
						}
						else
						{
							ar >> Well_3D::karotazh_list;
						}

					}
				case 2:
					{
						int sloj_number_to_save;						
						ar >> sloj_number_to_save;
						Well_3D::s_sloj_number_to_save = sloj_number_to_save;

						bool use_sloj_names; 
						ar >> use_sloj_names;
						Well_3D::s_use_sloj_names = use_sloj_names;

						bool show_all_sloi;						
						ar >> show_all_sloi;
						Well_3D::s_show_all_sloi = show_all_sloi;
					}
				case 1:
					{
						ar >> this->m_drills;		ar >> this->m_drills_ObjectList;		this->m_drills_ObjectList.Init(this->m_drills, this);
						ar >> this->m_tria_grid;	ar >> this->m_tria_grid_ObjectList;		this->m_tria_grid_ObjectList.Init(this->m_tria_grid, this);
												
						if (fbi.blockVersion >= 5)
							this->UpdateWellColomnsByWellsDraw();

					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 60:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar.m_use_object_version = 0;

						ar << this->m_blanklines;		ar << this->m_blanklines_ObjectList;
						ar << this->m_strings;			ar << this->m_strings_ObjectList;

						ar << this->m_bln_profiles;		ar << this->m_bln_profiles_ObjectList;
						ar << this->m_brokenPlanes;		ar << this->m_brokenPlanes_ObjectList;
						ar << this->m_bitmaps;			ar << this->m_bitmaps_ObjectList;
						ar << this->m_bmp_profiles;		ar << this->m_bmp_profiles_ObjectList;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar.m_use_object_version = 0;

						ar >> this->m_blanklines;		ar >> this->m_blanklines_ObjectList;		this->m_blanklines_ObjectList.Init(this->m_blanklines, this);
						ar >> this->m_strings;			ar >> this->m_strings_ObjectList;			this->m_strings_ObjectList.Init(this->m_strings, this);

						ar >> this->m_bln_profiles;		ar >> this->m_bln_profiles_ObjectList;		this->m_bln_profiles_ObjectList.Init(this->m_bln_profiles, this);
						ar >> this->m_brokenPlanes;		ar >> this->m_brokenPlanes_ObjectList;		this->m_brokenPlanes_ObjectList.Init(this->m_brokenPlanes, this);
						ar >> this->m_bitmaps;			ar >> this->m_bitmaps_ObjectList;			this->m_bitmaps_ObjectList.Init(this->m_bitmaps, this);
						ar >> this->m_bmp_profiles;		ar >> this->m_bmp_profiles_ObjectList;		this->m_bmp_profiles_ObjectList.Init(this->m_bmp_profiles, this);
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	case 70:
		{
			if (ar.IsStoring())
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar.m_use_object_version = 0;

						ar << this->m_blanklines;				ar << this->m_blanklines_ObjectList;
						ar << this->m_strings;					ar << this->m_strings_ObjectList;
						
						ar << this->mGridProfilesDirection;	
						ar << this->max_grid_profiles_v;	
						ar << this->min_grid_profiles_v;	

						ar << this->m_grid_profiles;			ar << this->m_grid_profiles_ObjectList;
					}
					break;
				default:
					{
						return false;
					}
				}
			}
			else
			{
				switch(fbi.blockVersion)
				{
				case 1:
					{
						ar.m_use_object_version = 0;

						ar >> this->m_blanklines;			ar >> this->m_blanklines_ObjectList;		this->m_blanklines_ObjectList.Init(this->m_blanklines, this);
						ar >> this->m_strings;				ar >> this->m_strings_ObjectList;			this->m_strings_ObjectList.Init(this->m_strings, this);
						
						ar >> this->mGridProfilesDirection;
						ar >> this->max_grid_profiles_v;
						ar >> this->min_grid_profiles_v;

						ar >> this->m_grid_profiles;		ar >> this->m_grid_profiles_ObjectList;		this->m_grid_profiles_ObjectList.Init(this->m_grid_profiles, this);
					}
					break;
				default:
					{
						return false;
					}
				}
			}
		}
		break;
	default:
		{
			return false;
		}
	}
	return true;
}
DWORD SurfDoc::Serialize(Archive& ar)
{
	printf("SurfDoc::Serialize(Archive& ar)\n");
	//header
	if (ar.IsStoring())
	{
		// Записываем
		long headerID = 0x42522017;
		ar << headerID;

		long headerSize = 4;
		ar << headerSize;

		long Version = 4;
		ar << Version;
	}
	else
	{
		long headerID;
		ar >> headerID;
		if (headerID != 0x42522017)
		{
			throw "This is not Surf Document";
		}

		long headerSize;
		ar >> headerSize;

		long Version;
		ar >> Version;
	}
	this->Object::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
	return 0;
}
Archive& operator <<(Archive& ar, SurfDoc& ob)
{
	DWORD version = ob.m_object_version;

	switch (version)
	{
	case 1:
		{
			FileBlockInfo fbi;
#if DFX_LAYER_FROM_OBJECT
			long block_types[]		= {5, 10, 20, 25, 28, 30, /*32,*/ 35, 37, 40, 50, 60, 70};
			long block_version[]	= {1,  1,  1,  1,  1,  3, /* 1,*/  2,  3,  1,  5,  1,  1};
#else
			long block_types[]		= {5, 10, 20, 25, 28, 30, 35, 37, 40, 50, 60, 70};
			long block_version[]	= {1,  1,  1,  1,  1,  3,  2,  3,  1,  5,  1,  1};
			//long block_version[]	= {1,  1,  1,  1,  1,  3,  2,  3,  1,  5,  1,  1};// чтобы сохранять для просмотрщика
#endif
			DWORD fileSize_from_previousBlock = ar.GetFileSize();
			if (fileSize_from_previousBlock == 0xffffffff)
			{
				printf ("warning: can not set block size\n");
				fbi.m_toSetBlockSizes = false;
			}
			int nBlock = sizeof(block_types) / sizeof(long);
			for (int i = 0; i < nBlock; i++)
			{
				fbi.InitFileBlockHeader(block_types[i],block_version[i]);
				ar << fbi;
				if (ob.SerializeFileBlock(fbi,ar))
				{
					DWORD current_fileSize = ar.GetFileSize();
					if (current_fileSize == 0xffffffff)
					{
						printf ("warning: can not set block size\n");
						fbi.m_toSetBlockSizes = false;
					}
					DWORD blockSize = ar.GetFileSize();
					if( fbi.m_toSetBlockSizes)
					{
						ar.ReWrite((unsigned char *)&blockSize, fbi.m_blockSize_filePointer, sizeof(DWORD));
					}
				}
				else 
				{
					throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
				}
			}
			ar << fbi.fileEndID;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, SurfDoc& ob)
{
//	printf("Archive& operator >>(Archive& ar, SurfDoc& ob)\n");
	//printf("ob.m_object_version = %d\n", ob.m_object_version);
	switch (ob.m_object_version)
	{
	case 1:
		{
			FileBlockInfo fbi;
			// пока могу читать заголовки блоков
			while(ar.ReadFileBlockHeader(fbi))
			{
				char str[1024];
				sprintf(str, "fbi.blockStartID %d, fbi.blockType %d, fbi.blockVersion %d, fbi.blockSize %d", fbi.blockStartID, fbi.blockType, fbi.blockVersion, fbi.blockSize);
				//MessageBox(0, str, "Archive& operator >>(Archive& ar, SurfDoc& ob)", 0);
				// читаю блоки данных
				if (!ob.SerializeFileBlock(fbi,ar))
				{
					// а если не моге, то есть если не знаю как блок файла данного типа и данной версии 
					sprintf(str, "!!!!!!!!!!!\n\ncannot read file block type = %ld, version = %ld, fbi.blockSize = %d\n", fbi.blockType, fbi.blockVersion, fbi.blockSize);
					printf(str);
					//MessageBox(0, str, "Archive& operator >>(Archive& ar, SurfDoc& ob)", 0);
					if (fbi.blockSize != 0)
					{
						// пробую пропустить этот блок
						// если известен его размер
						DWORD sizeof_fbi = 3*sizeof(LONG) + sizeof(DWORD);
						long bytes_to_seek = (long) fbi.blockSize - (long) sizeof_fbi;
						ar.GetFile()->Seek(bytes_to_seek, FILE_CURRENT);
					}
					else
						// иначе делать нечего - вызываем исключение
						throw "Can not read the file";
				}
				else
				{
					sprintf(str, "read file block type = %ld, version = %ld, fbi.blockSize = %d\n", fbi.blockType, fbi.blockVersion, fbi.blockSize);
					//MessageBox(0, str, "Archive& operator >>(Archive& ar, SurfDoc& ob)", 0);
				}
			}
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, SurfDoc& ob) end\n");
	return ar;
}

bool SurfDoc::SaveFile(LPCTSTR filename, int nBufSize,  void* buff)
{
	if (!CheckMyLicense())
	{
		MessageBox(0, "Unable to open file" , filename, MB_OK);
		return false;
	} 
	AFile f;
	if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
	{
		if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Unable to open file" , filename, MB_OK);
			return false;
		}
	}
	current_filename = filename;
	Archive ar( &f, Archive::store, nBufSize, buff );
//						  ar.m_max_object_version = 1;
/*	switch(nFilterIndex)
	{
	case 1:
		ar.m_use_primitive_version = 1;
		break;
	}*/
	// Serialize SurfDoc here
	try
	{
		this->Serialize(ar);
	}
	catch(VersionException& ve)
	{
		
		MessageBox(this->hSurfWnd, ve.Explane().c_str(), "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		// How to delete file???
		///f.SeekToBegin();
		return false;
	}
	catch(const char * c)
	{
		MessageBox(this->hSurfWnd, c, "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}	
	catch( bad_alloc &ba)
	{
		MessageBox(this->hSurfWnd, ba.what(), "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		printf(ba.what());
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
		return false;
	}
	catch(...)
	{
		MessageBox(this->hSurfWnd, "Unknown error", "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		return false;

	}
	ar.Close();
	f.Close();
	return true;
}

bool SurfDoc::OpenCubeFile(LPCTSTR filename, int nBufSize,  void* buff)
{
	//pFileName = fileNameBuf;
	AFile f;
	if( !f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) {
		MessageBox(0, "Unable to open file" , filename, MB_OK);
		return false;
	}
	current_filename = filename;
	Archive ar( &f, Archive::load, nBufSize, buff );
	// Serialize SurfDoc here
	try
	{
		ar.pDocument = (void*)this;
		Grid4 grid;
		ar >> grid;
		this->AddCube(&grid, filename, RGB(0,0,0));

		//this->Serialize(ar);

		this->InitObjectsLayerPointers();
		this->FillLayerList();

		this->ZoomView();   
		this->Draw();
		//====== 
		/*RECT rect;
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd,&rect, true);*/
	}
	catch(VersionException& ve)
	{
		
		MessageBox(this->hSurfWnd, ve.Explane().c_str(), "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		// How to delete file???
		///f.SeekToBegin();
		ar.Close();
		f.Close();
		return false;
	}
	catch(const char * c)
	{
		MessageBox(this->hSurfWnd, c, "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		ar.Close();
		f.Close();
		return false;
	}						  
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		ar.Close();
		f.Close();
		return false;
	}
	catch(...)
	{
		MessageBox(this->hSurfWnd, "Unknown error", "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		ar.Close();
		f.Close();
		return false;
	}
	ar.Close();
	f.Close();
	return true;
}

bool SurfDoc::OpenFile(LPCTSTR filename, int nBufSize,  void* buff, bool AsImport)
{
	Archive::OpenFileAsImport = AsImport;
	//pFileName = fileNameBuf;
	AFile f;
	if( !f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) {
		MessageBox(0, "Unable to open file" , filename, MB_OK);
		return false;
	}
	current_filename = filename;
	Archive ar( &f, Archive::load, nBufSize, buff );
	// Serialize SurfDoc here
	try
	{
		ar.pDocument = (void*)this;

		this->Serialize(ar);

		this->InitObjectsLayerPointers();
		this->FillLayerList();

		this->ZoomView();   
		this->Draw();
		//====== 
		/*RECT rect;
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd,&rect, true);*/
	}
	catch(VersionException& ve)
	{
		
		MessageBox(this->hSurfWnd, ve.Explane().c_str(), "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		// How to delete file???
		///f.SeekToBegin();
		ar.Close();
		f.Close();
		return false;
	}
	catch(const char * c)
	{
		MessageBox(this->hSurfWnd, c, "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		ar.Close();
		f.Close();
		return false;
	}						  
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		ar.Close();
		f.Close();
		return false;
	}
	catch(...)
	{
		MessageBox(this->hSurfWnd, "Unknown error", "SurfDoc Serialize Error", MB_OK | MB_ICONEXCLAMATION);
		ar.Close();
		f.Close();
		return false;
	}
	ar.Close();
	f.Close();
	return true;
}
bool SurfDoc::IsThisLineForDraw(Object *pObject)
{
	Line3D * pline = dynamic_cast<Line3D*>(pObject);
	if(pline && pline == this->m_pLineForDraw)
		return true;
	else
		return false;
}
bool SurfDoc::IsThisGridDataForDraw(Object *pObject)
{
	GridData * pGridData = dynamic_cast<GridData*>(pObject);
	if(pGridData && pGridData == this->m_pGridDataForDraw)
		return true;
	else
		return false;
}
bool SurfDoc::SaveGriddataToDB()
{
	if (this->m_pLabDoc)
	{
		if (this->m_grid_data.SetCurrentMsgOnFirst())
		{
			do
			{
				m_grid_data.GetCurrentMsg().GrDtSaveToDB(0);
			}
			while(this->m_grid_data.IncrementCurrentMsg());
		}
		return true;
	}
	return false;
}
bool SurfDoc::SaveZoomToDB()
{
	if (this->m_pLabDoc)
	{
		this->m_pLabDoc->DefineZoom(id_obj, this->m_zoomCoefXYZ, this->m_zoomCoefXY);
		return true;
	}
	return false;
}
bool SurfDoc::UndefineCubeSizeInDB()
{
	if (this->m_pLabDoc)
	{
		if (!this->m_cube_size.Defined())
		{
			this->m_pLabDoc->UnDefineCubeSize(id_obj);
			return true;
		}
	}
	return false;
}
bool SurfDoc::SaveCubeSizeToDB()
{
	if (this->m_pLabDoc)
	{
		if (this->m_cube_size.Defined())
		{
			this->m_pLabDoc->DefineCubeSize(id_obj, this->m_cube_size);
			return true;
		}
	}
	return false;
}


void SurfDoc::DefineCubeSize(CubeSize & cube_size)
{
	this->m_cube_size.Define(cube_size);
}
void SurfDoc::DefineZoom(double zoomCoefXYZ, double zoomCoefXY)
{
	this->m_zoomCoefXYZ = zoomCoefXYZ;
	this->m_zoomCoefXY  = zoomCoefXY;
}

void SurfDoc::GridDataSurfaces(long id_surf, const char * nazva,
	BYTE podoshva, BYTE r, BYTE g, BYTE b, 
	short z_flag, long id_umpoz, long id_ige)
{
	db_griddata_surfaces_item data;

	data.id_surf = id_surf;
	data.nazva = nazva;
	data.podoshva = podoshva;
	data.r = r;
	data.g = g;
	data.b = b;
	data.z_flag = z_flag;
	data.id_umpoz = id_umpoz;
	data.id_ige = id_ige;

	m_db_griddata.Add(id_surf, data);

}

void SurfDoc::DBGridData(long id_surf, long id_point,
	double x, double y, double z)
{
	db_griddata_item data;

	data.id_surf = id_surf;
	data.id_point = id_point;
	data.x = x;
	data.y = y;
	data.z = z;

	m_db_griddata.Add(id_surf, data);;
}
void SurfDoc::ApplyDBGridData()
{
	for (map<long, db_griddata_surf>::iterator it = this->m_db_griddata.datas.begin();
		it != this->m_db_griddata.datas.end(); it++)
	{
		long id_surf = (*it).first;
		GridData * pGridData = this->CreateNewGridData(id_surf);
		COLORREF color = 0;
		if ((*it).second.data2_filled)
		{
			pGridData->SetName((*it).second.data2.nazva);
			pGridData->podoshva = (*it).second.data2.podoshva;
			color = RGB((*it).second.data2.r, (*it).second.data2.g, (*it).second.data2.b);
			pGridData->SetColor(color);
			pGridData->z_flag = (*it).second.data2.z_flag;
			pGridData->id_umpoz = (*it).second.data2.id_umpoz;
			pGridData->id_ige = (*it).second.data2.id_ige;
		}
		for (map<long, db_griddata_item>::iterator it1 = (*it).second.data1.begin();
			it1 != (*it).second.data1.end(); it1++)
		{
			//pGridData->AddInput()
			long id_point = (*it1).first;
			CPoint3 pt;
			pt.x = (*it1).second.x;
			pt.y = (*it1).second.y;
			pt.z = (*it1).second.z;

			ThePoint3D point(this);
			pGridData->m_input_points.AddMsg(&point);
			pGridData->m_input_points.GetLastMsg().InitPoints(&pt, 1, color);
			pGridData->m_input_points.GetLastMsg().id_point = id_point;
			pGridData->m_input_points_ObjectList.Init(pGridData->m_input_points, pGridData);
			
		}
	}
}
void SurfDoc::MySurfer_skip_next_alert()
{
	MySurfer::skip_next_alert = true;
}

void SurfDoc::MySurfer_set_next_alert()
{
	MySurfer::skip_next_alert = false;
	MySurfer::alert = true;
}
void SurfDoc::GridDataUsedAlg(long id_surf, BYTE griddata_app, long id_alg)
{
	GridData * found = this->FindGridData(id_surf);
	if (found)
	{		
		//bool useSurfer = use_surfer == 2;
		//griddata_application grddt_app = use_surfer;
		bool to_allocate = true;
		griddata_dialog dlg(to_allocate, this, found, NULL, (griddata_dialog::griddata_application)griddata_app, NULL, false, true);
		dlg.InitGriddataDialog(NULL, false);
		dlg.griddata_fun_number = id_alg;
		dlg.OkButtonHandler(NULL);
	}
}

void SurfDoc::RebuildByGridData_IfNeed()
{			
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			GeoSurface * pGeoSurface = &m_surfaces.GetCurrentMsg();
			if (pGeoSurface)
			{
				GridData * pGridData = this->FindGridData(pGeoSurface->id_surf);
				if (pGridData)
				{
					if (pGridData->built == 2)
					{
						//bool useSurfer = ;

						bool to_allocate = true;
						griddata_dialog dlg(to_allocate, this, pGridData, NULL, (griddata_dialog::griddata_application)pGridData->griddata_app, pGeoSurface, false, true);
						dlg.InitGriddataDialog(NULL, false);
						dlg.griddata_fun_number = pGridData->griddata_fun_number;
						dlg.OkButtonHandler(NULL);

						pGridData->built = 1;
					}
				}

			}
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
}