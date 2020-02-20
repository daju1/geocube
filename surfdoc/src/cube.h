// Cube4D.h: interface for the Cube4D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBE3D_H__3FB4AD5B_375A_4D38_A1F4_EAF8C2C747DA__INCLUDED_)
#define AFX_CUBE3D_H__3FB4AD5B_375A_4D38_A1F4_EAF8C2C747DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "palette.h"
#include "ObjectList.h"
#include "../../array/src/vect.h"
#include "../../surfdefs.h"
#include "Grid.h"


class SurfDoc;

#define CUBE4D_AS_PRIMITIVE 0

#define Cube4D_npages 5

class Cube4D
#if CUBE4D_AS_PRIMITIVE
	: public Primitive3D <CPoint4>
#else
	: public Object
#endif
{
	APalette m_palette;
	UINT m_nColormap;

	bool m_bUseColormap;
	bool m_bInverseColormap;

#if CUBE4D_AS_PRIMITIVE
	double  m_vMax, m_vMin;
#endif

	void DrawingOfManyIsoSurfaces();
	void DrawingOfOneIsoSurface();
	void DrawingAsScatterPlot();

	virtual void Drawing();

	//void DrawGDIplusOfOneIsoSurface(gdiplus_map_view * v, Profile3D * on);
	//void DrawGDIplusOfManyIsoSurfaces(gdiplus_map_view * v, Profile3D * on);
	//void DrawGDIplusAsScatterPlot(gdiplus_map_view * v, Profile3D * on);

public:
	//void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);
	void ScaleIsolevels();
	void UpdateIsolevels(bool);
#if CUBE4D_AS_PRIMITIVE
	unsigned int m_leny; //grid4Section->nRow
	unsigned int m_lenx; //grid4Section->nCol
	unsigned int m_lenz; //grid4Section->nPag
#else
	int m_alpha;
	double m_opacity;
	double m_isolevel;

	double m_min_isolevel;
	double m_max_isolevel;
	double m_step_isolevel;

	size_t m_nIsolevels;
	vector<double> m_isolevels;
	size_t m_iso_ind; 

	COLORREF m_color;
	Grid4 lattice;
#endif
	enum draw_mode {one_isosurface = 10, many_isosurfaces = 20, vol_render = 30};
	static draw_mode s_draw_mode;
	static SSaveProfData sprData;
	
	bool draw_as_one_isosurface;
	bool draw_as_many_isosurfaces;
	bool draw_as_scatter_plot;
	bool draw_as_image;
	bool draw_as_contours;
	bool draw_as_vol_render;

protected:
	// Массив описаний страниц блокнота
	PROPSHEETPAGE   psheetPage[Cube4D_npages];

	// Заголовок блокнота
	PROPSHEETHEADER psheetHeader;

	// Идентификаторы страниц блокнота
	HPROPSHEETPAGE hPage[Cube4D_npages];
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
//	static Cube4D * me;
	static int GetAlphaSliderNum(HWND hwnd, UINT& nID);	
	static INT_PTR CALLBACK DlgProcDrawModes( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );	
	static INT_PTR CALLBACK DlgProcIsosurfaces( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );	
	static INT_PTR CALLBACK DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK  DlgProcSurfPalette( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );
	static int GetCutsPlaneSliderNum(HWND hwnd, UINT& nID);
	static INT_PTR CALLBACK DlgProcCubeCutsPlane( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );

	static int CALLBACK Cube4D::PropSheetProc(HWND hwndDlg,
								   UINT uMsg,
								   LPARAM lParam);

	void Init(const Cube4D& ob);

public:
	void Init();
#if CUBE4D_AS_PRIMITIVE
	bool MakeGridSection(LPSURFER7GRID4SECTION grid4Section);
#else
	void SetLayer(const Layer* layer)
	{
		this->SetLayer_NonVirtual(layer);
	}
	virtual bool ColorDialog(void)
	{
		return ChooseSurfColor(NULL, m_color) == 0;
	}
	virtual COLORREF GetColor(void)
	{		
		return this->m_color;
	}
	virtual void SetColor(COLORREF color)
	{
		m_color = color;
	}
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) )
	{
		if ((this->*condition_fun)())
		{
			(* callback_fun)(this, wParam, lParam, p);
		}
	}
	virtual void Draw()
	{
		m_nglListNumber = DrawListArray::glNewList();
		Drawing();
		glEndList();
	}
	virtual void ReDraw(void);
	bool SaveAs();
	bool SaveAsBln(FILE * stream)
	{		
		return false;
	}	
	bool SaveAsDat(FILE * stream)
	{		
		return false;
	}
#endif
	void InitThin(LPSURFER7GRID4SECTION grid4Section, COLORREF color);
	void Init(LPSURFER7GRID4SECTION grid4Section, COLORREF color);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	void FillContextMenu(HMENU& hMenu);

	bool SaveAs3DGrid(const char * file);
	bool SaveAsVTK(const char * file);
	bool SaveAsDxf_OfOneIsoSurface(const char * outfile);
	bool SaveAsGrid_OfOneIsoSurface(const char * outfile);

	bool SaveAsSurferClices(int nProjection);

	bool SaveAsSurferClicesXY(const char * outfile, Grid & grid);
	bool SaveAsSurferClicesYZ(const char * outfile, Grid & grid);
	bool SaveAsSurferClicesXZ(const char * outfile, Grid & grid);

	bool SaveAsSurferClicesYZ(const char * outfile, Grid & grid, double y_t_povorot, double cos_ugol);
	bool SaveAsSurferClicesXZ(const char * outfile, Grid & grid, double x_t_povorot, double cos_ugol);

	void Produce3DSurferGrid7_XY(long pp, SURFER7GRIDSECTION & grid);
	void Produce3DSurferGrid7_XZ(long rr, SURFER7GRIDSECTION & grid);
	void Produce3DSurferGrid7_YZ(long cc, SURFER7GRIDSECTION & grid);

	Cube4D& operator=(const Cube4D& ob);
	Cube4D (const Cube4D& ob);
	virtual void PropertiesDialog();
	COLORREF GetColor(double z);
	void DrawQuadsNumbers();
	Cube4D::Cube4D();
	Cube4D(SurfDoc * pSurfDoc);
	BOOL GetPoint(int iz, int iy, int ix, CPoint4 *pt);
	virtual ~Cube4D();
#if CUBE4D_AS_PRIMITIVE
	bool GetDocumentCoordinates(UINT i, double& x, double& y, double& z, double& v, bool& b )
	{
		if (i>0 && i < this->GetPointsNumber())
		{
			PRIMITIVE_POINTS_PTR(CPoint4) ptd;
			ptd = this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			b = ptd[i].bVisible;

			x = ptd[i].x;
			y = ptd[i].y;
			z = ptd[i].z;
			v = ptd[i].v;
			return true;

		}
		return false;
	}
	
	CPoint4& GetSurfDocPoint(size_t p, size_t r, size_t c)
	{
		size_t i = this->m_lenx*this->m_leny*p + this->m_lenx*r + c;
		return m_vdPoints[i];
	}
#endif

	bool GetQuadIndex(
		double x, double y, double z,
		int& ix, int& iy, int& iz);



	virtual bool UpdateExtremums();
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void ZoomInv(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void ZoomInv(unsigned int ipoint, double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//используются функциями Cut
	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);

	// массив точек сечения плоскостью каждой клетки каждой поверхности
	// самый внешний вект = контейнер для характеристик каждой поверхности
	// первый вложенный вектор = массив для каждой клетки текущей поверхности
	// второй вложенный вектор = массив точек сечения плоскостью текущей клетки текущей поверхности
	vect<VXYZ_VECTOR <VXYZ_VECTOR <CPoint3> > > vxyz; 
	// самый внешний вект = контейнер для характеристик каждой поверхности
	// вложенный вектор = массив для каждой клетки текущей поверхности
	// структура QuadCutting, характеризуящая каждую клетку 
	// содержит информацию о номерах соседних клеток, 
	// из которых приходит и 
	// в которые уходит линия сечения клетки плоскостью
	vect<Vector <QuadCutting> > vQuadCutting;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



	int Produce3DSurferGrid7(double cut_plane_d[4], SURFER7GRIDSECTION & gridSection);
	void Produce3DSurferGrid7_YZ(double cut_plane_d[4], SURFER7GRIDSECTION & gridSection);
	void Produce3DSurferGrid7_XZ(double cut_plane_d[4], SURFER7GRIDSECTION & gridSection);
	void Produce3DSurferGrid7_XY(double cut_plane_d[4], SURFER7GRIDSECTION & gridSection);
	
	void Projection(Karotazh& karotazh);
	bool Projection(CPoint3 & pt, double & v);
	
		
	void OnCreate(void);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Cube4D& ob);
	friend Archive& operator >>(Archive& ar, Cube4D& ob);
};

#endif // !defined(AFX_SURFACE3D_H__3FB4AD5B_375A_4D38_A1F4_EAF8C2C747DA__INCLUDED_)
