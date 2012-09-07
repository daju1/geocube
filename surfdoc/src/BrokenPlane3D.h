// BrokenPlane3D.h: interface for the BrokenPlane3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROKENPLANE3D_H__4B1446DE_5859_44C4_8B42_7713D68FDBBE__INCLUDED_)
#define AFX_BROKENPLANE3D_H__4B1446DE_5859_44C4_8B42_7713D68FDBBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../surfdefs.h"

#include "ObjectList.h"
#include "ThePoint3D.h"
#include "Line3D.h"
#include "Poligon3D.h"
#include "Well_3D.h"
#include "BrokenPoligon3D.h"
#include "BrokenLine3D.h"
#include "../../tools/src/filedlg.h"


class BlnProfile3D;
struct AutoCADRazrezParam
{
	double init_v_scale;
	double init_g_scale;
	double init_hatch_scale;

	bool insert_dxf;

	bool draw_poligones;
	bool poligones_fill;
	bool skip_unchecked_poligones;


	bool draw_sloi_lines;
	bool draw_faults;
	bool draw_catches;

	bool draw_wells;
	bool draw_wells2;

	bool draw_colomn;
	bool draw_scale_line;

	double v_scale;
	double g_scale;
	double hatch_scale;
};

struct SurfLineIntersectPoint 
{
	int i_surf1;//номер продлеваемой линии
	bool back;//направление продлевания линии относительно внутренней нумерации точек в линии
	double dist_to_end;//расстояние от края продлеваемой линии до данной точки пересечения линий

	//индексы точек одна видимая другая невидимая
	int i1_1;
	int i2_1;

	int i_surf2;//номер пересекаемой линии
	int i1_2;//индексы точек пересекаемого отрезка
	int i2_2;
	int unvisibles, dst_to_vis;// число невидимых точек и расстояние в точках до ближайшей видимой точки на пересекаемой линии

	bool with_krovlja;

	ThePoint3D point;

	SurfLineIntersectPoint() : point(ThePoint3D()), i_surf1(-1), i_surf2(-1), with_krovlja(false)
	{

	}

	//при сортировке по возрастанию в начале отсортированного вектора должен оказаться объект 
	//с наименьшим dist_to_end, но если dist_to_end одинаково то с наибольшим i_surf2
	bool operator< (const SurfLineIntersectPoint& rhs)
	{
		if (fabs (this->dist_to_end - rhs.dist_to_end) < 1e-6)
		{
			return this->i_surf2 > rhs.i_surf2;
		}
		return this->dist_to_end < rhs.dist_to_end;
	}

	void Init(const SurfLineIntersectPoint& bp)
	{	
		this->i_surf1		= bp.i_surf1;
		this->back			= bp.back;
		this->dist_to_end   = bp.dist_to_end;

		this->i1_1			= bp.i1_1;
		this->i2_1			= bp.i2_1;

		this->i_surf2		= bp.i_surf2;
		this->i1_2			= bp.i1_2;
		this->i2_2			= bp.i2_2;
		this->unvisibles    = bp.unvisibles;
		this->dst_to_vis    = bp.dst_to_vis;

		this->with_krovlja  = bp.with_krovlja;

		this->point			= bp.point;
	}
	SurfLineIntersectPoint(const SurfLineIntersectPoint &ob)
	{
		this->Init(ob);
	}
	SurfLineIntersectPoint& operator=(const SurfLineIntersectPoint& ob)
	{
		if (this == &ob)
		{
			return *this;
		}

		this->Init(ob);

		return *this;
	}
};

struct previouse_line
{
	int i_surf;
	int was_reverse;
	int i1;

	int ip1,ip2;// опорные точки крайнего вектора полигона
	CPoint3 p1, p2;
	// вектор на отрезке из предыдущей линии
	CPoint3 p;

	// next line
	int i_surf_next;
	int in1,in2;
	int unv, dst;

	previouse_line() : i_surf(-1), was_reverse(-1), i1(-1), ip1(-1), ip2(-1) , i_surf_next(-1), in1(-1), in2(-1), unv(0), dst(0)
		, p1(CPoint3())
		, p2(CPoint3())
		, p(CPoint3())
	{}
};

class BrokenPlane3D : public Object
{
	friend class SurfDoc;
	BlnProfile3D * m_profile3D;
public:
	void InitPrifile3D(BlnProfile3D * on){m_profile3D = on;}

	void clear();

	PLANE_MEMBERS_VECTOR<BrokenLine3D>							m_broken_lines;
	ObjectList													m_broken_lines_ObjectList;

	PLANE_MEMBERS_VECTOR<BrokenLine3D>							m_broken_fault_lines;
	ObjectList													m_broken_fault_lines_ObjectList;

	PLANE_MEMBERS_VECTOR<BrokenLine3D>							m_broken_catch_lines;
	ObjectList													m_broken_catch_lines_ObjectList;

	PLANE_MEMBERS_VECTOR<PLANE_MEMBERS_VECTOR<ThePoint3D> >		m_pointsDrillSloi;
	ObjectList													m_pointsDrillSloi_ObjectList;

	PLANE_MEMBERS_VECTOR<BrokenPoligon3D>						m_polySloi;
	ObjectList													m_polySloi_ObjectList;

	PLANE_MEMBERS_VECTOR<COLORREF> 								m_colorsSloi;

	PLANE_MEMBERS_VECTOR<Well_3D>								m_drills;
	ObjectList													m_drills_ObjectList;


	PLANE_MEMBERS_VECTOR<Line3D>								m_drills_line_left;
	ObjectList													m_drills_line_left_ObjectList;

	PLANE_MEMBERS_VECTOR<Line3D>								m_drills_line_right;
	ObjectList													m_drills_line_right_ObjectList;

	PLANE_MEMBERS_VECTOR<PLANE_MEMBERS_VECTOR<ThePoint3D> >		m_pointsDrillSloi_left;
	ObjectList													m_pointsDrillSloi_left_ObjectList;
	PLANE_MEMBERS_VECTOR<PLANE_MEMBERS_VECTOR<ThePoint3D> >		m_pointsDrillSloi_right;
	ObjectList													m_pointsDrillSloi_right_ObjectList;

	std::vector<std::vector<SurfLineIntersectPoint> >		m_SurfLineIntersectPoints;
	ObjectList													m_SurfLineIntersectPoints_ObjectList;

	static double m_w;// расстояние на котором надо рисовать m_drills_line_left и m_drills_line_right от m_drills



	// профиль заданный на карте в виде блн файла в координатах карты
	PLANE_MEMBERS_VECTOR<CPoint2>								m_vMapBlnProfiles;


	int GetLineVisiblePartsNumber(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2);
	bool GetLineVisiblePart(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int i_visible_part,
									 int & i_start, int & i_finish);

	int GetLineVisiblePartsNumber(int n_cut_line, int n_surf_line);
	bool GetLineVisiblePart(int n_cut_line, int n_surf_line, 
									 int i_visible_part,
									 int & i_start, int & i_finish);



	void AddPointToPoligon_Back(CPoint3 pt, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
					   , int i_poligon
#endif
					   );
	void AddPointToPoligon_Front(CPoint3 pt, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
					   , int i_poligon
#endif
					   );
	bool AddPointToPoligon(int n_cut_point, int n_surf_point, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
					   , int i_poligon
#endif
					   );
	void AddLineToPoligon(int n_cut_line, int n_surf_line, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
					   , int i_poligon
#endif
					   );

	int AddLineToPoligon_Back(int n_cut_line, int n_surf_line, 
		int i1_1, int i1_2,
		int n_cut_poligon, int n_surf_poligon
		, int i_poligon
		, int & added
		);

	int AddLineToPoligon_Back(bool reverse,
		int n_cut_line, int n_surf_line, 
		int i1_1, int i1_2,
		int n_cut_poligon, int n_surf_poligon
		, int i_poligon
		, int & added
		);

	bool AddLineToPoligon_Back(int n_cut_line, int n_surf_line, 
		int i1, bool nearest_part_from_the_point, CPoint3 pt,
		int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
		, int i_poligon
#endif
		);

	int AddLineToPoligon_Front(int n_cut_line, int n_surf_line, 
		int i1_1, int i1_2,
		int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
		, int i_poligon
#endif
		, int & added
		);

	int AddLineToPoligon_Front(bool reverse, int n_cut_line, int n_surf_line, 
		int i1_1, int i1_2,
		int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
		, int i_poligon
#endif
		, int & added
		);

	bool AddLineToPoligon_Front(int n_cut_line, int n_surf_line, 
		int i1, bool nearest_part_from_the_point, CPoint3 pt,
		int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
		, int i_poligon
#endif
		);

	void GetWellLineIntersection(
		int n_cut, int n_surf, 
		int i_start, int i_finish,
		bool & not_reversed_line,
		int & i1_1, int & i1_2, 
		bool & add_first_pointsDrillSloi,
		bool & add_second_pointsDrillSloi);

	bool AddingLineToPoligon( 
		bool Front,
		previouse_line & prev_line,
		std::map<int, int> & slips,
		int & slip_to_add,
		int _i_surf_left,
		int _i1_left,
		CPoint3 _pt_1,
		int n_cut,
		int n_surf_poligon,
		int i_poligon,
		int & __i_surf_left,
		int & __i1_left);

	int LeftWalk(int & one_right_n_cut, bool & found_above_right_n_cut, 
		std::map<int, int> & slips, int & last_added_slip,
		int & _i_surf_left, int & _i1_left,
		int n_cut, int n_surf, int i_poligon, int n_surf_poligon, int n_surf_do_not_add,
		bool like_podoshva, bool add_first_pointsDrillSloi);

	int RightWalk(int & one_left_n_cut_plus_1, bool & found_above_left_n_cut_plus_1, 
		std::map<int, int> & slips, int & last_added_slip,
		int & _i_surf_right, int & _i1_right,
		int n_cut, int n_surf, int i_poligon, int n_surf_poligon, int n_surf_do_not_add,
		bool like_podoshva, bool add_second_pointsDrillSloi);

	void MiddleWalk(int i1_1, int i1_2,
		std::map<int, int> & slips, int & last_added_slip,
		int n_cut, int n_surf, int i_poligon, int n_surf_poligon, int n_surf_do_not_add,
		bool add_first_pointsDrillSloi, bool add_second_pointsDrillSloi);

	void ClosePoligonByLine(int n_cut_line, int n_surf_line, int imd1, int imd2, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
					, int i_poligon
#endif
					);
	void AutoCADRazres(const char * profile_name);
	void AutoCADRazres(AutoCADRazrezParam param);
	void AutoCADColomn(AutoCADRazrezParam param);
	void AutoCADPolyigon(MyAcad & m_acad, Poligon3D & poli, AutoCADRazrezParam & param, 
					 int n_sloi, int n_cut, double xProfile, string hatchacad, double angle, double scale);

	void SaveAsRazres();
	void SavingAsRazrez(FILE * bln, Poligon3D & poli, int n_sloi, int n_cut, double xProfile);
	void InitLine (SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 *pts, int len, const char *name, long _id_umpoz, long _id_surf, long _id_ige, BYTE _podoshva, COLORREF color);
	void InitFault(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 *pts, int len, const char *name, long _id_umpoz, long _id_surf, long _id_ige, BYTE _podoshva, COLORREF color);
	void InitCatch(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 *pts, int len, const char *name, long _id_umpoz, long _id_surf, long _id_ige, BYTE _podoshva, COLORREF color);
	void InitPoint(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 pt);
	void Cutting();
	bool Init_broken_plane (vector<long> * pv_ID_KT, vector<double> &xMap, vector<double> &yMap);
	int m_nCuts;
	int m_nSurfs;
	int m_nFaults;
	int m_nCatches;
	int m_nSloi;
	int m_nDrills;

	bool FindIntersection(bool back, int i1_1, int i2_1,
		int n_cut, int n_surf1, int n_surf2,
		std::vector<SurfLineIntersectPoint> & vslip);

	void Build();
	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();

	void Init(const BrokenPlane3D& bp)
	{		

		this->m_nCatches			= bp.m_nCatches;
		this->m_broken_catch_lines	= bp.m_broken_catch_lines;
		this->m_broken_catch_lines_ObjectList.Init1(this->m_broken_catch_lines, this);


		this->m_nCuts				= bp.m_nCuts;
		this->m_nDrills				= bp.m_nDrills;
		this->m_nSloi				= bp.m_nSloi;
		this->m_nSurfs				= bp.m_nSurfs;
		this->m_nFaults				= bp.m_nFaults;

		// Objects' vectors
		this->m_colorsSloi			= bp.m_colorsSloi;

		this->m_drills				= bp.m_drills;
		this->m_drills_ObjectList.Init1(this->m_drills, this);

		this->m_drills_line_left	= bp.m_drills_line_left;
		this->m_drills_line_left_ObjectList.Init1(this->m_drills_line_left, this);

		this->m_drills_line_right	= bp.m_drills_line_right;
		this->m_drills_line_right_ObjectList.Init1(this->m_drills_line_right, this);

		this->m_broken_lines		= bp.m_broken_lines;
		this->m_broken_lines_ObjectList.Init1(this->m_broken_lines, this);

		this->m_broken_fault_lines	= bp.m_broken_fault_lines;
		this->m_broken_fault_lines_ObjectList.Init1(this->m_broken_fault_lines, this);

		this->m_pointsDrillSloi		= bp.m_pointsDrillSloi;
		this->m_pointsDrillSloi_ObjectList.Init2(this->m_pointsDrillSloi, this);

		this->m_pointsDrillSloi_left	= bp.m_pointsDrillSloi_left;
		this->m_pointsDrillSloi_left_ObjectList.Init2(this->m_pointsDrillSloi_left, this);

		this->m_pointsDrillSloi_right	= bp.m_pointsDrillSloi_right;
		this->m_pointsDrillSloi_right_ObjectList.Init2(this->m_pointsDrillSloi_right, this);

		this->m_SurfLineIntersectPoints = bp.m_SurfLineIntersectPoints;
		this->m_SurfLineIntersectPoints_ObjectList.Init2_SurfLineIntersectPoint(this->m_SurfLineIntersectPoints, this);




		this->m_polySloi			= bp.m_polySloi;
		this->m_polySloi_ObjectList.Init1(this->m_polySloi, this);

		// CPoint2
		this->m_vMapBlnProfiles		= bp.m_vMapBlnProfiles;
		this->m_profile3D			= bp.m_profile3D;
		this->m_pSurfDoc			= bp.m_pSurfDoc;

	}
	bool SaveAs()
	{
		BrokenPlane3D::SaveAsRazres();
		return true;;
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
			WhatSelected& ws);

	BrokenPlane3D& BrokenPlane3D::operator=(const BrokenPlane3D& bp);


	BrokenPlane3D();
	BrokenPlane3D(const BrokenPlane3D & bp);
	BrokenPlane3D(SurfDoc* pSurfDoc);
	virtual ~BrokenPlane3D();

	void OnCreate(void);

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BrokenPlane3D& ob);
	friend Archive& operator >>(Archive& ar, BrokenPlane3D& ob);

	static SSaveProfData sprData;
};

#endif // !defined(AFX_BROKENPLANE3D_H__4B1446DE_5859_44C4_8B42_7713D68FDBBE__INCLUDED_)
