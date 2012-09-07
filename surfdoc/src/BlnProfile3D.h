// BlnProfile3D.h: interface for the BlnProfile3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLNPROFILE3D_H__5FBD2C80_3091_4D81_939B_7B99135ABC18__INCLUDED_)
#define AFX_BLNPROFILE3D_H__5FBD2C80_3091_4D81_939B_7B99135ABC18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectList.h"
#include "points.h"
#include "Line3D.h"
#include "Poligon3D.h"
#include "BlnProfilePlane3D.h"
#include "BrokenPoligon_3D.h"
#include "ProfileAttachPoint.h"

class gdiplus_map_view;
class CrdTranslator;

#include "Profile3D.h"

#include <dime/Basic.h>
#include <dime/util/Linear.h>
#include "Grid.h"
#include "BrokenPlane3D.h"

class BlnProfile3D  : public Object, public Profile3D
{
	friend class SurfDoc;
	Grid m_grid;// грид для DrawGDIplus
	BrokenPlane3D m_broken_plane;//для DrawGDIplus


public:

	long id_rozriz;

	void Cutting();
	void SaveAsRazres(){m_broken_plane.SaveAsRazres();}
	void AutoCADRazres(){m_broken_plane.AutoCADRazres(this->name.c_str());}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// профиль из линий 3-х блн файлов: 
	// 1 файл - собственно оцифрованный профиль (разрез)
	// + 2 файла с точками привязки профиля: 
	// на карте и на разрезе
	//vect<CPoint2> m_vBlnProfiles;//массив двумерных линий оцифрованных на разрезе в координатах разреза
	vector<vector<CPoint2> > m_vectorBlnProfiles;//массив двумерных линий оцифрованных на разрезе в координатах разреза
	//тот же массив, но в трёхмерном пространстве
	vector<string> m_names;
	vector<COLORREF> m_colors;

	vect<Line3D>	m_bln_lines;
	ObjectList		m_bln_lines_ObjectList;

//	vect<Poligon3D>	m_bln_polygones;
//	ObjectList		m_bln_polygones_ObjectList;

	vect<BrokenPoligon_3D>	m_brkn_poligons;
	ObjectList				m_brkn_poligons_ObjectList;

	// а это полупрозрачные ломаные плоскости в трёхмерном пространстве, 
	// символизирующие расположение ломанного листа разреза
	BlnProfilePlane3D m_plane;
	int m_alpha_plane; // коэффициент прозрачности

	
	int AddBlnProfile(const char *lpstrFile, const char * name, vector<long> * pv_ID_KT, vector<double> &xMap, vector<double> &yMap, vector<double> &xProfile, bool acad_yscale_loaded, double z1w, double y1a, double z2w, double y2a);
	int ReadBln(const char *lpstrFile);
	int ReadDxf(const char *lpstrFile);
	bool YScaling();
	bool GetExtremums2D( bool useAttaches, double& minx, double& maxx, double& miny, double& maxy, int ProfileDirection);
	int AddBlnProfile(const char *lpstrFile, const char * name, int ProfileDirection, double f);

	void ConvertBlnProfilesTo3D(bool create_layers);	

	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view *);
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Cube4D * cube);
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );

	void SetLayer(const Layer* layer);

	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();
	bool UpdateExtremums(CPoint2 & profile_min, CPoint2 & profile_max);

	void Init(const BlnProfile3D& bp)
	{		
		m_colors						= bp.m_colors;
		this->m_names					= bp.m_names;
		this->m_plane					= bp.m_plane;
		this->m_plane.SetParent(this);
		this->m_alpha_plane				= bp.m_alpha_plane;

		// Objects' vectors
		this->m_bln_lines				= bp.m_bln_lines;
		this->m_bln_lines_ObjectList.Init(this->m_bln_lines, this);

		this->m_brkn_poligons			= bp.m_brkn_poligons;
		this->m_brkn_poligons_ObjectList.Init(this->m_brkn_poligons, this);

		this->m_vectorBlnProfiles			= bp.m_vectorBlnProfiles;

		this->id_rozriz						= bp.id_rozriz;
	}
	virtual bool SaveAsDxf(dimeModel * model, dimeBlock * block, CrdTranslator * translator);
	//bool SaveAsDxf(char * outfile, CrdTranslator * translator);
	bool SaveAsBln(char * outfile, CrdTranslator * translator);
	bool SaveAsManyBlnFiles(char * outfile, CrdTranslator * translator);
	bool SaveAs();
	bool SaveAsDat(FILE * stream)
	{
		return false;
	}

	bool SaveAsBln(FILE * stream)
	{
		return false;
	}
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws);
	bool IsSelectedDoc(CPoint3 selected_doc_pt, 
		double search_radius,
		double & dist_to_object,
		WhatSelected& ws);
	bool IsSelectedGridDataPoint(gdiplus_map_view * gv, int mouse_x, int mouse_y, double & dist_to_line, WhatSelected& ws, GridData *&pGridData);
	bool IsSelectedLine(gdiplus_map_view * gv, int mouse_x, int mouse_y, double & dist_to_line, WhatSelected& ws);
	bool IsSelectedWell(gdiplus_map_view * gv, int mouse_x, int mouse_y, double & dist_to_well, WhatSelected& ws);

	BlnProfile3D& BlnProfile3D::operator=(const BlnProfile3D& bp);

	BlnProfile3D();
	BlnProfile3D(const BlnProfile3D & bp);
	BlnProfile3D(SurfDoc* pSurfDoc);
	virtual ~BlnProfile3D();

	int ClearFromDB(bool msg);

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	void FillContextMenu(HMENU& hMenu);
	Line3D * AddLine();
	void AddBrokePointsToLines();
	//bool EditAttaches();
	//void PrintAttaches();

  void setFillmode(const bool fillmode);

  void addLine(const dimeVec3f &v0, const dimeVec3f &v1,
	  const char * layername, const int colidx,
	  const dimeMatrix * const matrix = NULL);

  void addPoint(const dimeVec3f &v,
	  const char * layername, const int colidx,
		const dimeMatrix * const matrix = NULL);

  void addTriangle(const dimeVec3f &v0,
		   const dimeVec3f &v1,
		   const dimeVec3f &v2,
		   const char * layername, const int colidx,
		   const dimeMatrix * const matrix = NULL);
  void addQuad(const dimeVec3f &v0,
	       const dimeVec3f &v1,
	       const dimeVec3f &v2,
	       const dimeVec3f &v3,
		   const char * layername, const int colidx,
	       const dimeMatrix * const matrix = NULL);

  bool fillmode;

	void ProduceGDIMap();
	void ProduceMap();

	void SavingOfCubeProjectionGrid();
	void SavingOfCubeProjectionGrid(const char * outdir, int index_cub, int make_grids_vnahljost, bool convert_to_acad_yscale, bool non_stretched_xscale);
	void SavingOfCubeProjectionGrid(FILE * bas, const char * outdir, int index_cub, int make_grids_vnahljost, bool convert_to_acad_yscale, bool non_stretched_xscale, char * prof_name_in_fun);
	static BOOL CALLBACK BlnProfile3D::DlgProcSavingOfCubeProjectionGrid( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );

	void OnCreate(void);
	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BlnProfile3D& ob);
	friend Archive& operator >>(Archive& ar, BlnProfile3D& ob);

	bool BuildIntersection(BlnProfile3D * profile);

	static SSaveProfData sprData;
};

#endif // !defined(AFX_BLNPROFILE3D_H__5FBD2C80_3091_4D81_939B_7B99135ABC18__INCLUDED_)
