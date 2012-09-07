// Surface3D.h: interface for the Surface3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACE3D_H__3FB4AD5B_375A_4D38_A1F4_EAF8C2C747DA__INCLUDED_)
#define AFX_SURFACE3D_H__3FB4AD5B_375A_4D38_A1F4_EAF8C2C747DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "palette.h"
#include "ObjectList.h"
#include "..\..\array\src\vect.h"
#include "../../surfdefs.h"
#include "Grid.h"

class GeoSurface;

struct QuadCutting
{
	short bCutted;
	short nLines;
//	CPoint3 start_point;
//	CPoint3 finish_point;
	int start_neighbour_row;
	int start_neighbour_col;

	int finish_neighbour_row;
	int finish_neighbour_col;

	int q1,
		q2, 
		q3, 
		q4;
};
class SurfDoc;

#define Surface3D_npages 2

class surf_edge
{
public:
	struct edge_cutting
	{
		double x,y;
		double r,c;
		enum CutDirection {up,down,left,right};
		// направление, в котором расположена видимая часть поверхности
		CutDirection m_cutDirectionOfVisible;
		// направление, в котором растут номера точек линии бланкования
		CutDirection m_cutDirectionOfLine;
		int line_number;
		int line_point_number1;
		int line_point_number2;
		double distance_from_start_of_line;

		// этот флаг нужен для того, чтобы обозначить отличие собственно линии бланкования 
		// от её продолжения прямой линией. Это нам нужно, чтобы на продолжении линии 
		// бланкования не строить полигонов 
		bool this_is_continue_line;//

		enum sort_mode {by_c, by_r};
		static sort_mode s_sort_mode;
		bool operator<(const edge_cutting& rhs)
		{
			switch(s_sort_mode)
			{
			case sort_mode::by_c:
				return c < rhs.c;
			case sort_mode::by_r:
				return r < rhs.r;
			}
		}
		bool operator>(const edge_cutting& rhs)
		{
			switch(s_sort_mode)
			{
			case sort_mode::by_c:
				return c > rhs.c;
			case sort_mode::by_r:
				return r > rhs.r;
			}
		}
	};
	vector<edge_cutting> vec;
	bool bSorted;
	/*int bCutted;
	double x,y;*/
	surf_edge()
	{
		bSorted=false;
	}

};
struct blank_polygon_point
{
	CPoint3 pt;
	int line_number;
	double distance_from_start_of_line;
	int line_point_number1;
};
class Surface3D : public Primitive3D <CPoint3>
{
	APalette m_palette;
	UINT m_nColormap;

	bool m_bUseColormap;
	bool m_bLocalColormap;
	bool m_bInverseColormap;

	bool	m_bQuad; // Флаг использования GL_QUAD
	double FindCuttingOfSurfaceEdgesWithBlankLine(
		int line_number,
		Line3D& blankline, 
		bool to_continue_line_to_borders, 
		vector<surf_edge>* vse_gor, 
		vector<surf_edge>* vse_ver,
		size_t nx,
		size_t ny,
		double x00,
		double y00,

		double x0n,
		double y0n,

		double xn0,
		double yn0,

		double xnn,
		double ynn,
		
		//размер площадки в метрах
		double Dx,
		double Dy,

		//длина ребра клетки в долях единицы
		double dx_dc,
		double dx_dr,

		double dy_dc,
		double dy_dr
		);
	bool Surface3D::DetermineVisibleFlagOfFirstGridPoint(
		Line3D& blankline,
		CPoint3 * base_point,
		double x00,
		double y00,
		bool& bVisible00
	);
	void BlankTheGrid(
		size_t nx,	size_t ny,
		vector<surf_edge>& vse_gor, 
		vector<surf_edge>& vse_ver,
		bool& bVisible00);
	void BlankPolygonFilling(
		GeoSurface & rGeoSurface,
		size_t nx,	size_t ny,
		vector<surf_edge>& vse_gor,
        vector<surf_edge>& vse_ver);
	void BlankPolygonFilling(GeoSurface & rGeoSurface,
		size_t nx,	size_t ny,
		vector<vector<surf_edge> >& v_vse_gor, 
		vector<vector<surf_edge> >& v_vse_ver);
	bool CollectBlankPolygonQuadPoints(vector<blank_polygon_point>& blank_polygon_points,
		UINT r, UINT c, 
		size_t nx,
		size_t ny,
		vector<surf_edge>& vse_gor, 
		vector<surf_edge>& vse_ver,
		bool bi, double xi, double yi, double zi,
		bool bj, double xj, double yj, double zj,
		bool bk, double xk, double yk, double zk,
		bool bn, double xn, double yn, double zn);
	virtual void Drawing();
public:

	unsigned short m_zflag;
	unsigned int m_leny;
	unsigned int m_lenx;

	enum draw_mode {as_quads = 10, as_tias = 20, as_trias2 = 30};
	static draw_mode s_draw_mode;
	static bool s_do_not_build_blank_polygones_on_continue_lines;

protected:
	// Массив описаний страниц блокнота
	PROPSHEETPAGE   psheetPage[Surface3D_npages];

	// Заголовок блокнота
	PROPSHEETHEADER psheetHeader;

	// Идентификаторы страниц блокнота
	HPROPSHEETPAGE hPage[Surface3D_npages];
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
//	static Surface3D * me;
	static int GetAlphaSliderNum(HWND hwnd, UINT& nID);	
	static BOOL CALLBACK DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );
	static BOOL CALLBACK  Surface3D::DlgProcSurfPalette( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );

	void Init(const Surface3D& ob);

public:
	void Init();
	bool IsTheSameSize(CubeSize & cube_size);
	bool MakeGridSection(LPSURFER7GRIDSECTION gridSection, bool to_allocate = true);
	void Init(short zflag, LPSURFER7GRIDSECTION gridSection, COLORREF color);
	void Init(int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible, COLORREF color);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	Surface3D& operator=(const Surface3D& ob);
	Surface3D (const Surface3D& ob);
	virtual void PropertiesDialog();
	COLORREF GetColor(double z);
	void DrawQuadsNumbers();
	Surface3D::Surface3D();
	Surface3D(SurfDoc * pSurfDoc);
	BOOL GetPoint(int iy,int ix, CPoint3 *pt);
	virtual ~Surface3D();
	bool GetDocumentCoordinates(UINT i, double& x, double& y, double& z, bool& b )
	{
		if (i>0 && i < this->GetPointsNumber())
		{
			PRIMITIVE_POINTS_PTR(CPoint3) ptd;
			ptd = this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			b = ptd[i].bVisible;
			if (m_zflag == 0)
			{
				x = ptd[i].x;
				y = ptd[i].y;
				z = ptd[i].z;
				return true;
			}
			if (m_zflag == 1) // x <-> z
			{
				x = ptd[i].z;
				y = ptd[i].y;
				z = ptd[i].x;
				return true;
			}
			if (m_zflag == 2) // y <-> z
			{
				x = ptd[i].x;
				y = ptd[i].z;
				z = ptd[i].y;
				return true;
			}
		}
		return false;
	}
	CPoint3& GetSurfDocPoint(size_t r, size_t c)
	{
		size_t i = this->m_lenx*r + c;
		return m_vdPoints[i];
	}
		
	CPoint3 GetMin_with_zflag()
	{
		CPoint3 pt;
		switch(this->m_zflag)
		{
		case 0:
			pt = this->m_ptMin;
			break;
		case 1:
			pt.x = this->m_ptMin.z;
			pt.y = this->m_ptMin.y;
			pt.z = this->m_ptMin.x;
			break;
		case 2:
			pt.x = this->m_ptMin.x;
			pt.y = this->m_ptMin.z;
			pt.z = this->m_ptMin.y;
			break;
		}
		return pt;
	}
	CPoint3 GetMax_with_zflag()
	{
		CPoint3 pt;
		switch(this->m_zflag)
		{
		case 0:
			pt = this->m_ptMax;
			break;
		case 1:
			pt.x = this->m_ptMax.z;
			pt.y = this->m_ptMax.y;
			pt.z = this->m_ptMax.x;
			break;
		case 2:
			pt.x = this->m_ptMax.x;
			pt.y = this->m_ptMax.z;
			pt.z = this->m_ptMax.y;
			break;
		}
		return pt;
	}

	bool GetQuadIndex(
		double x, double y, double z,
		int& ix, int& iy);/*
	{
		ix = iy = -1;
		switch(this->m_zflag)
		{
		case 0:
			if (x >= this->m_ptMin.x &&
				x < this->m_ptMax.x &&
				y >= this->m_ptMin.y &&
				y < this->m_ptMax.y)
			{
				ix = int((x - this->m_ptMin.x) / (this->m_ptMax.x - this->m_ptMin.x) * (this->m_lenx-1));
				iy = int((y - this->m_ptMin.y) / (this->m_ptMax.y - this->m_ptMin.y) * (this->m_leny-1));
				return true;
			}
			break;
		case 1:
			if (z >= this->m_ptMin.z &&
				z < this->m_ptMax.z &&
				y >= this->m_ptMin.y &&
				y < this->m_ptMax.y)
			{
				ix = int((z - this->m_ptMin.z) / (this->m_ptMax.z - this->m_ptMin.z) * (this->m_lenx-1));
				iy = int((y - this->m_ptMin.y) / (this->m_ptMax.y - this->m_ptMin.y) * (this->m_leny-1));
				return true;
			}
			break;
		case 2:
			if (x >= this->m_ptMin.x &&
				x < this->m_ptMax.x &&
				z >= this->m_ptMin.z &&
				z < this->m_ptMax.z)
			{
				ix = int((x - this->m_ptMin.x) / (this->m_ptMax.x - this->m_ptMin.x) * (this->m_lenx-1));
				iy = int((z - this->m_ptMin.z) / (this->m_ptMax.z - this->m_ptMin.z) * (this->m_leny-1));
				return true;
			}
			break;
		}

		return false;
	}*/

	bool Surface3D::Projection(double x, double y, double z, // координаты точки в пространстве
		double& r, // выход - расстояние от точки до поверхности
		CPoint3 *pt);

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
	static size_t s_N_quad; // число точек для интерполяции по клетке
	size_t m_N_quad; // число точек для интерполяции по клетке
	void Cutting(double a, double b, double c, double d, 
		bool toDrawPoligones, bool positive, 
		short type_of_cutline, int cutting_number, int surf_number,					  
		CPoint2* pt1, CPoint2* pt2 //две точки, 
		//ограничивающие линию прамолинейного участка ломанного разреза
		, void * pBrokenPlane, GeoSurface * pGeoSurface, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix,
		ObjectList * cutplane_polygones_ObjectList, vect<Poligon3D> * cutplane_polygones);

	void CutTheQuad( 
#if USE_UNVISIBLE_CUTTING
		bool bvisivle,
#endif		
		UINT cutting_number, UINT surf_number, UINT quad,
							double A, double B, double C, double D, 
							CPoint2 *pt2, int pt_number, void * pBrokenPlane);
	void CutTheQuad( 
#if USE_UNVISIBLE_CUTTING
		bool bvisivle, Poligon3D * blank_polygon,
#endif			
		QuadCutting& quadCutting, UINT quad,
							double a, double b, double c, double d, 
							double A, double B, double C, double D, 
							vdouble &v_x, vdouble &v_y, vdouble &v_z, 
							double minx, double maxx, 
							double miny, double maxy, 
							double minz, double maxz, 
							bool toDrawPolygon, vect<Poligon3D> * cutplane_polygones);
	void CutTheQuad(
#if USE_UNVISIBLE_CUTTING
		bool bvisivle,
#endif		
		QuadCutting& quadCutting, UINT quad,
							double A1, double B1, double C1, double D1, 
							short zflag2,
							double A2, double B2, double C2, double D2,
							std::vector<CPoint3> & v_v,
							double minimum_x,
							double maximum_x,
							double minimum_y,
							double maximum_y,
							double minimum_z,
							double maximum_z,
							CPoint3* start_point_of_line,
							CPoint3* finish_point_of_line,							
							bool toDrawPolygon, 
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
							Poligon3D * & blank_polygon
#else
							vect<Poligon3D> * blank_polygones
#endif
							);

	void CutLine( short type_of_cutline, int cutting_number, void * pBrokenPlane, GeoSurface & rGeoSurface, int surf_number );
	
	bool BlankAbove(Surface3D & surf, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix);
	bool BlankUnder(Surface3D & surf, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix);

	void Blank(Line3D& blankline, bool to_continue_line_to_borders, GeoSurface & rGeoSurface, CPoint3 * base_point);
	void Blank(vect<Line3D>& blanklines, bool to_continue_line_to_borders, GeoSurface & rGeoSurface, CPoint3 * base_point);
	bool Cutting(Surface3D *psurface, 
						short type_of_cutline, int cutting_number, int surf_number, 
						bool toDrawPolygon, bool positive, GeoSurface * pGeoSurface,
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
						ObjectList * blank_polygon_matrix_ObjectList,
						std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix
#else
						ObjectList * blank_polygones_ObjectList,
						vect<Poligon3D> * blank_polygones	
#endif
						);
	void NoBlank(void);
	void OnCreate(void);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Surface3D& ob);
	friend Archive& operator >>(Archive& ar, Surface3D& ob);
};

#endif // !defined(AFX_SURFACE3D_H__3FB4AD5B_375A_4D38_A1F4_EAF8C2C747DA__INCLUDED_)
