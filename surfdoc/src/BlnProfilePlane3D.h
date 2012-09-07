// BlnProfilePlane3D.h: interface for the BlnProfilePlane3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLNPROFILEPLANE3D_H__563A3C51_EE68_416B_B145_1757C1700FAC__INCLUDED_)
#define AFX_BLNPROFILEPLANE3D_H__563A3C51_EE68_416B_B145_1757C1700FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"
#include "points.h"
#include "..\..\array\src\vect.h"
#include "ProfileAttachPoint.h"

class Profile3D;

// прересечение профилей
class ProfileIntersection
{
public:
	double x,y;// мировые координаты пересечения профилей 
	double min_z, max_z;
	double xv, yv; //GL координаты пересечения профилей
	double min_zv, max_zv;

	vector<double> z; // мировые координаты пересечения линий
	vector<double> zv; // GL координаты координаты пересечения линий

	string name; // имя пересекаемого профиля из класса Object

	vector<string> names; // имена пересекаемых линий
	vector<COLORREF> colors;

	ProfileIntersection();
	ProfileIntersection(const ProfileIntersection & pi);
	ProfileIntersection& operator=(const ProfileIntersection & pi);
	virtual ~ProfileIntersection();

	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void Drawing();
		
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);

	static bool s_draw_lines_z;
	static bool s_draw_lines_names;
	static bool s_draw_profile_name;

	void Init(const ProfileIntersection &pi)
	{
		this->x			= pi.x;
		this->y			= pi.y;
		this->xv		= pi.xv;
		this->yv		= pi.yv;

		this->min_z		= pi.min_z;
		this->max_z		= pi.max_z;
		this->min_zv	= pi.min_zv;
		this->max_zv	= pi.max_zv;

		this->z.resize(pi.z.size());
		this->zv.resize(pi.zv.size());
		this->names.resize(pi.names.size());
		this->colors.resize(pi.colors.size());

		for(size_t i = 0; i < pi.z.size(); i++)
		{
			this->z[i] = pi.z[i];
		}
		for(size_t i = 0; i < pi.zv.size(); i++)
		{
			this->zv[i] = pi.zv[i];
		}
		for(size_t i = 0; i < pi.names.size(); i++)
		{
			this->names[i] = pi.names[i].c_str();
		}
		for(size_t i = 0; i < pi.colors.size(); i++)
		{
			this->colors[i] = pi.colors[i];
		}

		this->name		= pi.name;
	}
};
#define BlnProfilePlane3D_npages 1
class BlnProfilePlane3D : public Object
{
	friend class SurfDoc;
	void Drawing();
public:
	vect<ProfileIntersection> m_intersections;
	// это полупрозрачные ломаные плоскости в трёхмерном пространстве, 
	// символизирующие расположение ломанного листа разреза
	vect<CPoint3> 
		m_vdplaneBlnProfiles,
		m_vvplaneBlnProfiles;

	int m_alpha; // коэффициент прозрачности

	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();

	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);

	virtual bool UpdateExtremums(){return false;}
	bool UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max);

	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );

	void SetLayer(const Layer* layer);

	void Init(const BlnProfilePlane3D& bp)
	{	
		printf("Init(BlnProfilePlane3D& bp)\n");
		this->m_intersections			= bp.m_intersections;

		this->m_alpha					= bp.m_alpha;

		// Objects' vectors

		this->m_vdplaneBlnProfiles		= bp.m_vdplaneBlnProfiles;
		this->m_vvplaneBlnProfiles		= bp.m_vvplaneBlnProfiles;

	}
	bool SaveAs()
	{
		return false;
	}
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
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}
	BlnProfilePlane3D& BlnProfilePlane3D::operator=(const BlnProfilePlane3D& bp);


	BlnProfilePlane3D();
	BlnProfilePlane3D(const BlnProfilePlane3D & bp);
	virtual ~BlnProfilePlane3D();

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	void OnCreate(void);

	void Build(CPoint2 pt2min, CPoint2 pt2max, int lenMapAttach, ProfileAttachPoint * ptpa);
	void Build(CPoint2 pt2min, CPoint2 pt2max, vector<ProfileAttachPoint> & ptpa);

	///*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BlnProfilePlane3D& ob);
	friend Archive& operator >>(Archive& ar, BlnProfilePlane3D& ob);
	bool Projection(CPoint3& in, CPoint3& out);
	bool Projection_old(CPoint3& in, CPoint3& out);
	void clear(void);

	//#####################################################
	// вынести в статические члены класса
	static double step_x,  step_y,  step_z;
	static double first_x, first_y, first_z;
	static double last_x, last_y, last_z;
	//static bool noth_vertical_coordinate_priorirty;
	static bool use_grid_on_plane, to_draw_x_vertical, to_draw_y_vertical, to_draw_gorizontal;
	//#####################################################
protected:

	// Массив описаний страниц блокнота
	PROPSHEETPAGE   psheetPage[BlnProfilePlane3D_npages];

	// Заголовок блокнота
	PROPSHEETHEADER psheetHeader;

	// Идентификаторы страниц блокнота
	HPROPSHEETPAGE hPage[BlnProfilePlane3D_npages];
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
//	static Cube4D * me;
	static BOOL CALLBACK DlgProcDrawModes( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );	
	static int GetAlphaSliderNum(HWND hwnd, UINT& nID);	
	static BOOL CALLBACK DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam );
};

#endif // !defined(AFX_BLNPROFILEPLANE3D_H__563A3C51_EE68_416B_B145_1757C1700FAC__INCLUDED_)
