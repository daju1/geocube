// BrokenPlane3D.cpp: implementation of the BrokenPlane3D class.
//
//////////////////////////////////////////////////////////////////////
#include <afxdisp.h>         // MFC core and standard components
#include "../../acad_connect/myacad.h"

#include "../../surfdefs.h" //for OG_DOUBLE_PRECISION

#include "afxdb.h"
#include "../../lab/lab/SetGrMain.h"
#include "../../lab/lab/SetUmPoz.h"
#include "../../lab/lab/labdoc.h"

#include "stdafx.h"
#include "BrokenPlane3D.h"
#include "..\..\commonOG.h"
#include "SurfDoc.h"
#include ".\brokenplane3d.h"
#include "distance3D.h"
#include "winsurftree.h"

#if 0
#if OG_DOUBLE_PRECISION 
extern double Distance(CPoint3 pt1, CPoint3 pt2);
extern double Distance_xy(CPoint3 pt1, CPoint3 pt2);
extern double Distance(CPoint2 pt1, CPoint2 pt2);
extern double Distance(CPoint2 pt1, CPoint3 pt2);
#else // float precision
extern float Distance(CPoint3 pt1, CPoint3 pt2);
extern float Distance_xy(CPoint3 pt1, CPoint3 pt2);
extern float Distance(CPoint2 pt1, CPoint2 pt2);
extern float Distance(CPoint2 pt1, CPoint3 pt2);
#endif /*OG_DOUBLE_PRECISION*/
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SSaveProfData BrokenPlane3D::sprData;

extern HINSTANCE hInst;								// current instance

CString GetIGEName(CDatabase * database, long id_obj, long id_ige);

double BrokenPlane3D::m_w = 1.0;
BrokenPlane3D::BrokenPlane3D()
{
	m_pSurfDoc = NULL;
	this->m_profile3D = NULL;
	OnCreate();
}
BrokenPlane3D::BrokenPlane3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	this->m_profile3D = NULL;
	OnCreate();
}
void BrokenPlane3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::broken_plane3d;
	this->m_object_version = 2;
	this->m_max_object_version = 2;

	m_nCuts = 0;
	m_nSurfs = 0;
	m_nFaults = 0;
	m_nCatches = 0;
	m_nSloi = 0;
	m_nDrills = 0;
}
BrokenPlane3D::BrokenPlane3D(const BrokenPlane3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
BrokenPlane3D& BrokenPlane3D::operator=(const BrokenPlane3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}
BrokenPlane3D::~BrokenPlane3D()
{

}

int GetVerticalPlaneFromTwoPoints(
								  CPoint2 &pt1, CPoint2 &pt2, //input
								  double &a, double &b, double &c, double &d)//output
{
	double epsilon = 1e-16;
	double x1 = pt1.x;
	double y1 = pt1.y;

	double x2 = pt2.x;
	double y2 = pt2.y;

	bool dxz = (fabs (x2 - x1) < epsilon);
	bool dyz = (fabs (y2 - y1) < epsilon);


	if (dxz && dyz)
	{
		//printf("GetVerticalPlaneFromTwoPoints x1 = %f x2 = %f y1 = %f y2 = %f\n", x1,x2,y1,y2);
		//printf("GetVerticalPlaneFromTwoPoints return -1\n");
		return -1;
	}
	c = 0.0;
	if (fabs (x1 - x2) < epsilon)
	{
		b = 0.0;
		a = 1.0;
		d = -x1;
	}
	else if (fabs(y1 - y2) < epsilon)
	{
		a = 0.0;
		b = 1.0;
		d = -y1;
	}
	else
	{
		if (fabs(x1-x2) > fabs(y2-y1))
		{
			b = 1.0;
			a = (y2-y1) / (x1-x2);
		}
		else
		{
			a = 1.0;
			b = (x1-x2) / (y2-y1);
		}
		d = -(a*x1+b*y1);
	}
	return 0;

}
bool BrokenPlane3D::Init_broken_plane(vector<long> * pv_ID_KT, vector<double> &xMap, vector<double> &yMap)
{
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if ( xMap.size() != yMap.size() )
	{
		char str[255];
		sprintf(str, "xMap.size(%d) != yMap.size(%d)", xMap.size(), yMap.size());
		MessageBox(0,str, "AddMapBlnProfile",0);
		return false;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int i, len = xMap.size();
	m_nCuts = len - 1;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if(len < 2)
	{
		char str[255];
		sprintf(str, "xMap.size(%d) < 2", xMap.size());
		MessageBox(0,str, "AddMapBlnProfile",0);
		m_nCuts = 0;
		return false;
	}
	//=====================================================================
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	this->m_broken_lines.clear();
	m_pointsDrillSloi.clear();
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	m_nDrills = len;
	m_pointsDrillSloi.resize(len);
	for (i = 0;i < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE();i++)
	{
		m_pointsDrillSloi[i].resize(0);
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	CPoint2 pt2;
	m_vMapBlnProfiles.resize(0);
	for (i = 0; i < len; i++)
	{
		pt2.x = xMap[i];
		pt2.y = yMap[i];
		m_vMapBlnProfiles.push_back(pt2);
	}


	m_drills.clear();
	m_drills.resize(m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE());
	if (pv_ID_KT)
	{
		for (int n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE() 
			&& n_drill < pv_ID_KT->size(); n_drill++)
		{
			m_drills[n_drill].m_id_kt = pv_ID_KT->operator [](n_drill);
		}
	}

	m_drills_line_left.clear();
	m_drills_line_right.clear();

	m_pointsDrillSloi_left.clear();
	m_pointsDrillSloi_right.clear();

	m_drills_line_left.resize(len);
	m_drills_line_right.resize(len);

	m_pointsDrillSloi_left.resize(len);
	m_pointsDrillSloi_right.resize(len);
	for (i = 0; i < len; i++)
	{
		m_pointsDrillSloi_left[i].resize(0);
		m_pointsDrillSloi_right[i].resize(0);

		m_drills_line_left[i].Free();
		m_drills_line_right[i].Free();
	}

	this->m_SurfLineIntersectPoints.clear();
	this->m_SurfLineIntersectPoints.resize(m_nCuts);
	for (i = 0; i < m_nCuts; i++)
	{
		this->m_SurfLineIntersectPoints[i].clear();
	}

	return true;
}
void BrokenPlane3D::Cutting()
{
	if (m_pSurfDoc)
	{
		//m_nSurfs = m_pSurfDoc->m_surfaces.msgSize();
		m_nSurfs = 0;
		for (vector<surface_order_list_item *>::iterator 
			it = GeoSurface::surface_order_list.begin();
			it != GeoSurface::surface_order_list.end(); it++)
		{
			if ((*it) && (*it)->check)
				m_nSurfs++;
		}
		
		
		m_nSloi = m_nSurfs - 1;

		m_nFaults = m_pSurfDoc->m_faults.msgSize();

		this->m_nCatches = m_pSurfDoc->m_geo_catches.msgSize();


		if (m_nDrills > 0)
		{
			m_pointsDrillSloi[0].resize(m_nSurfs);
			m_pointsDrillSloi_left[0].resize(m_nSurfs);
			m_pointsDrillSloi_right[0].resize(m_nSurfs);

			for(int n_surf = 0; n_surf < m_nSurfs; n_surf++)
			{
				m_pointsDrillSloi_left[0][n_surf].InitDoc(this->m_pSurfDoc);
				m_pointsDrillSloi_right[0][n_surf].InitDoc(this->m_pSurfDoc);
			}
		}

		m_broken_lines.		resize(m_nSurfs);
		for(int n_surf = 0; n_surf < m_nSurfs; n_surf++)
		{
			m_broken_lines[n_surf].m_lines.resize(m_nCuts);
		}
		//-----------------------------------------------------------
		// готовим вектор ломанных линий для проекций разломов на ломанный разрез - 
		// с запасом (на всякий случай) хотя в реальности каждый разлом может 
		// и не пересекать каждое сечение ломанного разреза
		// поэтому надо иметь ввиду что в реальности будет много пустых объектов, 
		// которые можно фильтровать и не показывать в дереве
		m_broken_fault_lines.		resize(m_nFaults);
		for(int n_fault = 0; n_fault < m_nFaults; n_fault++)
		{
			m_broken_fault_lines[n_fault].m_lines.resize(m_nCuts);
		}
		//-----------------------------------------------------------
		m_broken_catch_lines.		resize(m_nCatches);
		for(int n_catch = 0; n_catch < m_nCatches; n_catch++)
		{
			m_broken_catch_lines[n_catch].m_lines.resize(m_nCuts);
		}
		//-----------------------------------------------------------

		for(int i1 = 0, i2 = 1; i2 < m_nDrills; i1++, i2++)
		{
			double a, b, c, d;
			if( 
				i2 < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE() )
			{
				//получаем уравнение вертикальной плоскости, проходящей через две точки
				GetVerticalPlaneFromTwoPoints(
					m_vMapBlnProfiles[i1], 
					m_vMapBlnProfiles[i2], //input
					a, b, c, d);//output

				m_pointsDrillSloi[i2].	resize(m_nSurfs);
				m_pointsDrillSloi_left[i2].resize(m_nSurfs);
				m_pointsDrillSloi_right[i2].resize(m_nSurfs);

				double z_min = this->m_pSurfDoc->m_cube_size.zLL;
				double z_max = this->m_pSurfDoc->m_cube_size.zMax();

				double x1 = m_vMapBlnProfiles[i1].x;
				double y1 = m_vMapBlnProfiles[i1].y;

				double x2 = m_vMapBlnProfiles[i2].x;
				double y2 = m_vMapBlnProfiles[i2].y;

				double dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
				double part_1_right = BrokenPlane3D::m_w / dist;
				double part_2_left  = (dist - BrokenPlane3D::m_w) / dist;

				double x1_right = x1 + part_1_right * (x2 - x1);
				double y1_right = y1 + part_1_right * (y2 - y1);

				double x2_left = x1 + part_2_left * (x2 - x1);
				double y2_left = y1 + part_2_left * (y2 - y1);

				this->m_drills_line_right[i1].PushBack(CPoint3(x1_right, y1_right, z_min));
				this->m_drills_line_right[i1].PushBack(CPoint3(x1_right, y1_right, z_max));

				this->m_drills_line_left[i2].PushBack(CPoint3(x2_left, y2_left, z_min));
				this->m_drills_line_left[i2].PushBack(CPoint3(x2_left, y2_left, z_max));



				for(int n_surf = 0; n_surf < m_nSurfs; n_surf++)
				{
					m_pointsDrillSloi_left[i2][n_surf].InitDoc(this->m_pSurfDoc);
					m_pointsDrillSloi_right[i2][n_surf].InitDoc(this->m_pSurfDoc);
				}

				m_pSurfDoc->CutSurfs(a,b,c,d,
					false,//to draw tria and poligones
					true,//positive
					2,   //short type_of_cutline
					i1,  //cutting_number
					&(m_vMapBlnProfiles[i1]), 
					&(m_vMapBlnProfiles[i2]),
					(void *)this);
							
				m_pSurfDoc->CutFaults(a,b,c,d,
					false,//to draw tria and poligones
					true,//positive
					3,   //short type_of_cutline
					i1,  //cutting_number
					&(m_vMapBlnProfiles[i1]), 
					&(m_vMapBlnProfiles[i2]),
					(void *)this);
							
				m_pSurfDoc->CutGeoCatches(a,b,c,d,
					false,//to draw tria and poligones
					true,//positive
					7,   //short type_of_cutline
					i1,  //cutting_number
					&(m_vMapBlnProfiles[i1]), 
					&(m_vMapBlnProfiles[i2]),
					(void *)this);
							
//				m_pSurfDoc->CutAndDisvisible(
//				true, //positive
//				a,b,c,d);
			}
		}
		Build();
		m_broken_catch_lines_ObjectList.Init1(m_broken_catch_lines, this);
		m_broken_fault_lines_ObjectList.Init1(m_broken_fault_lines, this);
		m_broken_lines_ObjectList.Init1(m_broken_lines, this);
		m_pointsDrillSloi_ObjectList.Init2(m_pointsDrillSloi, this);
		m_polySloi_ObjectList.Init1(m_polySloi, this);
		m_drills_ObjectList.Init1(m_drills, this);

		m_drills_line_left_ObjectList.Init1(m_drills_line_left, this);
		m_drills_line_right_ObjectList.Init1(m_drills_line_right, this);

		m_pointsDrillSloi_left_ObjectList.Init2(m_pointsDrillSloi_left, this);
		m_pointsDrillSloi_right_ObjectList.Init2(m_pointsDrillSloi_right, this);

		m_SurfLineIntersectPoints_ObjectList.Init2_SurfLineIntersectPoint(this->m_SurfLineIntersectPoints, this);


	}
}
void BrokenPlane3D::InitPoint(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 pt)
{
	m_pointsDrillSloi[cutting_number][surf_number].Init(pSurfDoc, pt);
}

void BrokenPlane3D::InitLine(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 *pts, int len, const char *name, long _id_umpoz, long _id_surf, long _id_ige, BYTE _podoshva, COLORREF color)
{
	m_broken_lines[surf_number].m_lines[cutting_number].InitDoc(pSurfDoc);
	m_broken_lines[surf_number].m_lines[cutting_number].InitPoints(pts, len, color );
	m_broken_lines[surf_number].m_lines[cutting_number].SetName(name);

	m_broken_lines[surf_number].m_lines[cutting_number].id_surf  = _id_surf;
	m_broken_lines[surf_number].m_lines[cutting_number].id_umpoz = _id_umpoz;
	m_broken_lines[surf_number].m_lines[cutting_number].id_ige   = _id_ige;

	m_broken_lines[surf_number].m_lines[cutting_number].podoshva = _podoshva;

	printf("BrokenPlane3D::InitLine name = %s %s\n", name, m_broken_lines[surf_number].m_lines[cutting_number].GetName().c_str());

}

void BrokenPlane3D::InitFault(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 *pts, int len, const char *name, long _id_umpoz, long _id_surf, long _id_ige, BYTE _podoshva, COLORREF color)
{
	m_broken_fault_lines[surf_number].m_lines[cutting_number].InitDoc(pSurfDoc);
	m_broken_fault_lines[surf_number].m_lines[cutting_number].InitPoints(pts, len, color );
	m_broken_fault_lines[surf_number].m_lines[cutting_number].SetName(name);

	m_broken_fault_lines[surf_number].m_lines[cutting_number].id_surf = _id_surf;
	m_broken_fault_lines[surf_number].m_lines[cutting_number].id_umpoz = _id_umpoz;
	m_broken_fault_lines[surf_number].m_lines[cutting_number].id_ige = _id_ige;
	m_broken_fault_lines[surf_number].m_lines[cutting_number].podoshva = _podoshva;
}

void BrokenPlane3D::InitCatch(SurfDoc *pSurfDoc, UINT cutting_number, UINT surf_number, CPoint3 *pts, int len, const char *name, long _id_umpoz, long _id_surf, long _id_ige, BYTE _podoshva, COLORREF color)
{
	m_broken_catch_lines[surf_number].m_lines[cutting_number].InitDoc(pSurfDoc);
	m_broken_catch_lines[surf_number].m_lines[cutting_number].InitPoints(pts, len, color );
	m_broken_catch_lines[surf_number].m_lines[cutting_number].SetName(name);

	m_broken_catch_lines[surf_number].m_lines[cutting_number].id_surf = _id_surf;
	m_broken_catch_lines[surf_number].m_lines[cutting_number].id_umpoz = _id_umpoz;

	m_broken_catch_lines[surf_number].m_lines[cutting_number].id_ige = _id_ige;
	m_broken_catch_lines[surf_number].m_lines[cutting_number].podoshva = _podoshva;
}
void BrokenPlane3D::AddPointToPoligon_Back(CPoint3 pt, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
						, int i_poligon
#endif
					   )
{
#if USE_UNVISIBLE_CUTTING
	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return;
#endif

	this->m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																[i_poligon]
#endif
																			.PushBack(pt);
}
void BrokenPlane3D::AddPointToPoligon_Front(CPoint3 pt, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
						, int i_poligon
#endif
					   )
{
#if USE_UNVISIBLE_CUTTING
	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return;
#endif

	this->m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																[i_poligon]
#endif
																			.Insert(0, pt);
}
bool BrokenPlane3D::AddPointToPoligon(int n_cut_point, int n_surf_point, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
						, int i_poligon
#endif
					   )
{
#if USE_UNVISIBLE_CUTTING
	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return false;
#endif

	CPoint3 pt;
	//add 1-st point
	if(m_pointsDrillSloi[n_cut_point][n_surf_point].GetPointsNumber() > 0)
	{
		pt = m_pointsDrillSloi[n_cut_point][n_surf_point].m_vdPoints[0];
		if (pt.bVisible) 
		{
			this->m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																	[i_poligon]
#endif
																				.PushBack(pt);

			return true;
		}
	}
	return false;
}

void BrokenPlane3D::AddLineToPoligon(int n_cut_line, int n_surf_line, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
						, int i_poligon
#endif
					   )
{
printf("AddLineToPoligon\nn_cut_line %d, n_surf_line %d, n_cut_poligon %d, n_surf_poligon%d\n",
	n_cut_line, n_surf_line, n_cut_poligon, n_surf_poligon);

	if (n_cut_line < 0 || n_surf_line < 0)
		return;

#if USE_UNVISIBLE_CUTTING
	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return;
#endif

	CPoint3 
		pt,
		last_poly_point,
		last_line_point,
		first_line_point;
	// добавляем линию, 
	// но сначала определяем прямой или обратный порядок добавления линии 
	// а на случай если в полигоне или в линии нет точек 
	// инициализируем флаг порядка добавления линии
	bool reverse = false;
	if (
		m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																	[i_poligon]
#endif
																				.GetPointsNumber() > 0 &&
		m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() > 0)
	{
		last_poly_point		= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																				[i_poligon]
#endif		
																							.GetLastDocumentPoint();
		first_line_point	= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetFirstDocumentPoint();
		last_line_point		= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetLastDocumentPoint();
		double distance_to_last  = Distance_xy(last_poly_point, last_line_point);
		double distance_to_first = Distance_xy(last_poly_point, first_line_point);
		reverse = distance_to_last < distance_to_first;

printf(
	   "distance_to_last %f\n"
	   "distance_to_first %f\n"
	   "reverse = %d\n", 
	   distance_to_last,
	   distance_to_first,
	   reverse );

	}
	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()-1; i >= 0; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																	[i_poligon]
#endif
																			.PushBack(pt);
			}
		}
	}
	else
	{
		for (int i = 0; i < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber(); i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																	[i_poligon]
#endif
																				.PushBack(pt);
			}
		}
	}
}
#if USE_UNVISIBLE_CUTTING
int BrokenPlane3D::GetLineVisiblePartsNumber(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2)
{
	if (n_cut_line < 0 || n_surf_line < 0)
		return 0;

	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return 0;

	int VisibleParts = 0;
	bool b = false;

	for (int i = i1_min; i <= i1_max; ++i)
	{
		if (m_broken_lines[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i).bVisible)
		{
			if (!b)
			{
				VisibleParts++;
				b = true;
			}
		}
		else
		{
			b = false;
		}
	}
	return VisibleParts;
}

bool BrokenPlane3D::GetLineVisiblePart(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int i_visible_part,
									 int & i_start, int & i_finish)
{
	if (n_cut_line < 0 || n_surf_line < 0)
		return false;

	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return false;

	int VisibleParts = 0;
	bool b = false;
	int found_part_state = 0;

	for (int i = i1_min; i <= i1_max; ++i)
	{
		if (m_broken_lines[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i).bVisible)
		{
			if (!b)
			{
				if (i_visible_part == VisibleParts)
				{
					found_part_state = 1;
					i_start = i;
				}
				VisibleParts++;
				b = true;
			}
		}
		else
		{
			b = false;
			if (found_part_state == 1)
			{
				found_part_state = 2;
				i_finish = i - 1;
			}
		}
	}
	return found_part_state == 2;
}

int BrokenPlane3D::GetLineVisiblePartsNumber(int n_cut_line, int n_surf_line)
{
	if (n_cut_line < 0 || n_surf_line < 0)
		return 0;


	int VisibleParts = 0;
	bool b = false;

	for (int i = 0; i < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber(); ++i)
	{
		if (m_broken_lines[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i).bVisible)
		{
			if (!b)
			{
				VisibleParts++;
				b = true;
			}
		}
		else
		{
			b = false;
		}
	}
	return VisibleParts;
}



bool BrokenPlane3D::GetLineVisiblePart(int n_cut_line, int n_surf_line, 
									 int i_visible_part,
									 int & i_start, int & i_finish)
{
	if (n_cut_line < 0 || n_surf_line < 0)
		return false;

	int VisibleParts = 0;
	bool b = false;
	int found_part_state = 0;

	for (int i = 0; i < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber(); ++i)
	{
		if (m_broken_lines[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i).bVisible)
		{
			if (!b)
			{
				if (i_visible_part == VisibleParts)
				{
					found_part_state = 1;
					i_start = i;
				}
				VisibleParts++;
				b = true;
			}
			else
			{
				if (found_part_state == 1)
				{
					if (i_visible_part == VisibleParts - 1)
					{
						if (i == m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() - 1)
						{
							found_part_state = 2;
							i_finish = i;
						}
					}
				}
			}
		}
		else
		{
			b = false;
			if (found_part_state == 1)
			{
				found_part_state = 2;
				i_finish = i - 1;
			}
		}

	}
	return found_part_state == 2;
}

int BrokenPlane3D::AddLineToPoligon_Back(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int n_cut_poligon, int n_surf_poligon
									, int i_poligon
									, int & added
									 )
{
	added = 0;

	if (n_cut_line < 0 || n_surf_line < 0)
		return -1;

	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return -1;

	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return -1;


	CPoint3 
		pt,
		last_poly_point,
		last_line_point,
		first_line_point;
	// добавляем линию, 
	// но сначала определяем прямой или обратный порядок добавления линии 
	// а на случай если в полигоне или в линии нет точек 
	// инициализируем флаг порядка добавления линии
	bool reverse = false;
	if (
		m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																[i_poligon]
																			.GetPointsNumber() > 0 &&
		m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() > 0 &&
		i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()
		)
	{
		last_poly_point		= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																				[i_poligon]
																							.GetLastDocumentPoint();
		first_line_point	= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_min + 1);
		last_line_point		= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_max);
		double distance_to_last  = Distance_xy(last_poly_point, last_line_point);
		double distance_to_first = Distance_xy(last_poly_point, first_line_point);
		reverse = distance_to_last < distance_to_first;
	}
	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = i1_max ; i > i1_min; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].PushBack(pt);
				++added;
			}
		}
	}
	else
	{
		for (int i = i1_min + 1; i <= i1_max; i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].PushBack(pt);
				++added;
			}
		}
	}
	return reverse;
}
int BrokenPlane3D::AddLineToPoligon_Back(bool reverse,
										 int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int n_cut_poligon, int n_surf_poligon
									, int i_poligon
									, int & added
									 )
{
	added = 0;

	if (n_cut_line < 0 || n_surf_line < 0)
		return -1;

	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return -1;

	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return -1;


	CPoint3 pt;

	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = i1_max ; i > i1_min; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].PushBack(pt);
				++added;
			}
		}
	}
	else
	{
		for (int i = i1_min + 1; i <= i1_max; i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].PushBack(pt);
				++added;
			}
		}
	}
	return reverse;
}

bool BrokenPlane3D::AddLineToPoligon_Back(int n_cut_line, int n_surf_line, 
									 int i1, bool nearest_part_from_the_point, CPoint3 pt,
									 int n_cut_poligon, int n_surf_poligon
									, int i_poligon
									 )
{
	CPoint3
		last_line_point,
		first_line_point;
	first_line_point = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetFirstDocumentPoint();
	last_line_point	 = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetLastDocumentPoint();
	double distance_to_last  = Distance_xy(pt, last_line_point);
	double distance_to_first = Distance_xy(pt, first_line_point);

	bool add_part_from_begin_of_line = nearest_part_from_the_point ?
		distance_to_last > distance_to_first : distance_to_last < distance_to_first;

	int added = 0;

	if (add_part_from_begin_of_line)
	{
		AddLineToPoligon_Back(n_cut_line, n_surf_line, 
			-1,	i1,
			n_cut_poligon, n_surf_poligon
			, i_poligon
			, added
			);
	}
	else
	{
		AddLineToPoligon_Back(n_cut_line, n_surf_line, 
			i1,	m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()-1,
			n_cut_poligon, n_surf_poligon
			, i_poligon
			, added
			);
	}
	return add_part_from_begin_of_line;
}
#else
void BrokenPlane3D::AddLineToPoligon_Back(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int n_cut_poligon, int n_surf_poligon
									 )
{
	if (n_cut_line < 0 || n_surf_line < 0)
		return;


	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return;


	CPoint3 
		pt,
		last_poly_point,
		last_line_point,
		first_line_point;
	// добавляем линию, 
	// но сначала определяем прямой или обратный порядок добавления линии 
	// а на случай если в полигоне или в линии нет точек 
	// инициализируем флаг порядка добавления линии
	bool reverse = false;
	if (
		m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																			.GetPointsNumber() > 0 &&
		m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() > 0 &&
		i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()
		)
	{
		last_poly_point		= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																							.GetLastDocumentPoint();
		first_line_point	= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_min + 1);
		last_line_point		= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_max);
		double distance_to_last  = Distance_xy(last_poly_point, last_line_point);
		double distance_to_first = Distance_xy(last_poly_point, first_line_point);
		reverse = distance_to_last < distance_to_first;
	}
	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = i1_max ; i > i1_min; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																			.PushBack(pt);
			}
		}
	}
	else
	{
		for (int i = i1_min + 1; i <= i1_max; i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																			.PushBack(pt);
			}
		}
	}
}
bool BrokenPlane3D::AddLineToPoligon_Back(int n_cut_line, int n_surf_line, 
									 int i1, bool nearest_part_from_the_point, CPoint3 pt,
									 int n_cut_poligon, int n_surf_poligon
									 )
{
	CPoint3
		last_line_point,
		first_line_point;
	first_line_point = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetFirstDocumentPoint();
	last_line_point	 = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetLastDocumentPoint();
	double distance_to_last  = Distance_xy(pt, last_line_point);
	double distance_to_first = Distance_xy(pt, first_line_point);

	bool add_part_from_begin_of_line = nearest_part_from_the_point ?
		distance_to_last > distance_to_first : distance_to_last < distance_to_first;

	if (add_part_from_begin_of_line)
	{
		AddLineToPoligon_Back(n_cut_line, n_surf_line, 
			-1,	i1,
			n_cut_poligon, n_surf_poligon
			);
	}
	else
	{
		AddLineToPoligon_Back(n_cut_line, n_surf_line, 
			i1,	m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()-1,
			n_cut_poligon, n_surf_poligon
			);
	}
	return add_part_from_begin_of_line;
}
#endif
#if USE_UNVISIBLE_CUTTING
int BrokenPlane3D::AddLineToPoligon_Front(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int n_cut_poligon, int n_surf_poligon
									, int i_poligon
									, int & added
									 )
{
	added = 0;

	if (n_cut_line < 0 || n_surf_line < 0)
		return -1;

	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return -1;


	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return -1;


	CPoint3 
		pt,
		first_poly_point,
		last_line_point,
		first_line_point;
	// добавляем линию, 
	// но сначала определяем прямой или обратный порядок добавления линии 
	// а на случай если в полигоне или в линии нет точек 
	// инициализируем флаг порядка добавления линии
	bool reverse = false;
	if (
		m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].GetPointsNumber() > 0 &&
		m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() > 0 &&
		i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()
		)
	{
		first_poly_point	= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].GetFirstDocumentPoint();
		first_line_point	= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_min + 1);
		last_line_point		= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_max);
		double distance_to_last  = Distance_xy(first_poly_point, last_line_point);
		double distance_to_first = Distance_xy(first_poly_point, first_line_point);
		reverse = distance_to_last < distance_to_first;
	}
	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = i1_max ; i > i1_min; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].Insert(0, pt);
				++added;
			}
		}
	}
	else
	{
		for (int i = i1_min + 1; i <= i1_max; i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].Insert(0, pt);
				++added;
			}
		}
	}

	return reverse;
}

int BrokenPlane3D::AddLineToPoligon_Front(bool reverse, 
														int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int n_cut_poligon, int n_surf_poligon
									, int i_poligon
									, int & added
									 )
{
	added = 0;

	if (n_cut_line < 0 || n_surf_line < 0)
		return -1;

	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return -1;


	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return -1;


	CPoint3 pt;
	// добавляем линию, 
	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = i1_max ; i > i1_min; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].Insert(0, pt);
				++added;
			}
		}
	}
	else
	{
		for (int i = i1_min + 1; i <= i1_max; i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon][i_poligon].Insert(0, pt);
				++added;
			}
		}
	}

	return reverse;
}

bool BrokenPlane3D::AddLineToPoligon_Front(int n_cut_line, int n_surf_line, 
									 int i1, bool nearest_part_from_the_point, CPoint3 pt,
									 int n_cut_poligon, int n_surf_poligon
									, int i_poligon
									 )
{
	CPoint3 
		last_line_point,
		first_line_point;
	first_line_point = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetFirstDocumentPoint();
	last_line_point	 = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetLastDocumentPoint();
	double distance_to_last  = Distance_xy(pt, last_line_point);
	double distance_to_first = Distance_xy(pt, first_line_point);

	bool add_part_from_begin_of_line = nearest_part_from_the_point ?
		distance_to_last > distance_to_first : distance_to_last < distance_to_first;

	int added = 0;
	if (add_part_from_begin_of_line)
	{
		AddLineToPoligon_Front(n_cut_line, n_surf_line, 
			-1,	i1,
			n_cut_poligon, n_surf_poligon
			, i_poligon, added
			);
	}
	else
	{
		AddLineToPoligon_Front(n_cut_line, n_surf_line, 
			i1,	m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()-1,
			n_cut_poligon, n_surf_poligon
			, i_poligon, added
			);
	}
	return add_part_from_begin_of_line;
}

#else
void BrokenPlane3D::AddLineToPoligon_Front(int n_cut_line, int n_surf_line, 
									 int i1_1, int i1_2,
									 int n_cut_poligon, int n_surf_poligon
									 )
{
	if (n_cut_line < 0 || n_surf_line < 0)
		return;


	int i1_min = min(i1_1, i1_2);
	int i1_max = max(i1_1, i1_2);

	if (!(i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()))
		return;


	CPoint3 
		pt,
		first_poly_point,
		last_line_point,
		first_line_point;
	// добавляем линию, 
	// но сначала определяем прямой или обратный порядок добавления линии 
	// а на случай если в полигоне или в линии нет точек 
	// инициализируем флаг порядка добавления линии
	bool reverse = false;
	if (
		m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																.GetPointsNumber() > 0 &&
		m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() > 0 &&
		i1_min + 1 < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() &&
		i1_max < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()
		)
	{
		first_poly_point	= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																								.GetFirstDocumentPoint();
		first_line_point	= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_min + 1);
		last_line_point		= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetDocumentPoint(i1_max);
		double distance_to_last  = Distance_xy(first_poly_point, last_line_point);
		double distance_to_first = Distance_xy(first_poly_point, first_line_point);
		reverse = distance_to_last < distance_to_first;
	}
	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = i1_max ; i > i1_min; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																				.Insert(0, pt);
			}
		}
	}
	else
	{
		for (int i = i1_min + 1; i <= i1_max; i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
																				.Insert(0, pt);
			}
		}
	}
}
bool BrokenPlane3D::AddLineToPoligon_Front(int n_cut_line, int n_surf_line, 
									 int i1, bool nearest_part_from_the_point, CPoint3 pt,
									 int n_cut_poligon, int n_surf_poligon
									 )
{
	CPoint3 
		last_line_point,
		first_line_point;
	first_line_point = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetFirstDocumentPoint();
	last_line_point	 = m_broken_lines[n_surf_line].m_lines[n_cut_line].GetLastDocumentPoint();
	double distance_to_last  = Distance_xy(pt, last_line_point);
	double distance_to_first = Distance_xy(pt, first_line_point);

	bool add_part_from_begin_of_line = nearest_part_from_the_point ?
		distance_to_last > distance_to_first : distance_to_last < distance_to_first;

	if (add_part_from_begin_of_line)
	{
		AddLineToPoligon_Front(n_cut_line, n_surf_line, 
			-1,	i1,
			n_cut_poligon, n_surf_poligon
			);
	}
	else
	{
		AddLineToPoligon_Front(n_cut_line, n_surf_line, 
			i1,	m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber()-1,
			n_cut_poligon, n_surf_poligon
			);
	}
	return add_part_from_begin_of_line;
}

#endif
void BrokenPlane3D::ClosePoligonByLine(int n_cut_line, int n_surf_line, int imd1, int imd2, 
					   int n_cut_poligon, int n_surf_poligon
#if USE_UNVISIBLE_CUTTING
						, int i_poligon
#endif
					   )
{
	if (n_cut_line < 0 || n_surf_line < 0 || imd1 < 0 || imd2 < 0)
		return;

#if USE_UNVISIBLE_CUTTING
	if (i_poligon >= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon].Size())
		return;
#endif

	CPoint3 
		pt,
		first_poly_point,
		last_line_point,
		first_line_point;
	// добавляем линию, 
	// но сначала определяем прямой или обратный порядок добавления линии 
	// а на случай если в полигоне или в линии нет точек 
	// инициализируем флаг порядка добавления линии
	bool reverse = false;
	if (
		m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
															[i_poligon]
#endif
																	.GetPointsNumber() > 0 &&
		m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber() > 0)
	{
		first_poly_point		= m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																						[i_poligon]
#endif
																								.GetFirstDocumentPoint();
		first_line_point	= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetFirstDocumentPoint();
		last_line_point		= m_broken_lines	[n_surf_line].m_lines[n_cut_line].GetLastDocumentPoint();
		double distance_to_last  = Distance_xy(first_poly_point, last_line_point);
		double distance_to_first = Distance_xy(first_poly_point, first_line_point);
		reverse = distance_to_last > distance_to_first;
	}

	// добавляем верхнюю линию
	if (reverse)
	{
		for (int i = imd1; i >= 0; i--)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																	[i_poligon]
#endif
																			.PushBack(pt);
			}
		}
	}
	else
	{
		for (int i = imd2; i < m_broken_lines[n_surf_line].m_lines[n_cut_line].GetPointsNumber(); i++)
		{
			pt = m_broken_lines[n_surf_line].m_lines[n_cut_line].m_vdPoints[i];
			if (pt.bVisible) 
			{
				m_polySloi[n_surf_poligon].m_poligones[n_cut_poligon]
#if USE_UNVISIBLE_CUTTING
																	[i_poligon]
#endif
																			.PushBack(pt);
			}
		}
	}
}

double min_distance_to_line(Line3D * pline, CPoint3 pt, int & imd)
{
	double min_dist = DBL_MAX;
	imd = -1;
	if(pline)
	{
		for (size_t i = 0; i < pline->GetPointsNumber(); i++)
		{
			if (pline->m_vdPoints[i].bVisible)
			{
				double dist = Distance(pt, pline->m_vdPoints[i]);
				if (min_dist > dist)
				{
					min_dist = dist;
					imd = i;
				}
			}
		}
	}
	return min_dist;
}
struct order
{
	int n_cut_point;
	int n_surf_point;
	int n_cut_line;
	int n_surf_line;
};

void BrokenPlane3D::GetWellLineIntersection(
	int n_cut, int n_surf, 
	int i_start, int i_finish,
	bool & not_reversed_line,
	int & i1_1, int & i1_2, 
	bool & add_first_pointsDrillSloi,
	bool & add_second_pointsDrillSloi)
{							
	not_reversed_line = true;
	{
		CPoint3 
			finish_line_point,
			start_line_point;

		CPoint2 left_point = m_vMapBlnProfiles[n_cut];

		if (
			m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0 &&
			i_start < m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() &&
			i_finish < m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber()
			)
		{
			start_line_point	= m_broken_lines[n_surf].m_lines[n_cut].GetDocumentPoint(i_start);
			finish_line_point	= m_broken_lines[n_surf].m_lines[n_cut].GetDocumentPoint(i_finish);
			double distance_to_start  = Distance(left_point, start_line_point);
			double distance_to_finish = Distance(left_point, finish_line_point);
			not_reversed_line = distance_to_finish > distance_to_start;
		}
	}

	if (m_pointsDrillSloi_right[n_cut][n_surf].GetPointsNumber() > 0)
	{
		if (m_pointsDrillSloi_right[n_cut][n_surf].id_point >= i_start && 
			m_pointsDrillSloi_right[n_cut][n_surf].id_point <= i_finish)
		{
			i1_1 = not_reversed_line ?
				max(m_pointsDrillSloi_right[n_cut][n_surf].id_point, i_start) :
				min(m_pointsDrillSloi_right[n_cut][n_surf].id_point, i_finish);
			add_first_pointsDrillSloi = true;
		}
		else i1_1 = not_reversed_line ? i_start : i_finish;
	}
	else i1_1 = not_reversed_line ? i_start : i_finish;

	if (m_pointsDrillSloi_left[n_cut+1][n_surf].GetPointsNumber() > 0)
	{
		if (m_pointsDrillSloi_left[n_cut+1][n_surf].id_point >= i_start && 
			m_pointsDrillSloi_left[n_cut+1][n_surf].id_point <= i_finish)
		{
			i1_2 = not_reversed_line ?
				min(m_pointsDrillSloi_left[n_cut+1][n_surf].id_point, i_finish) :
				max(m_pointsDrillSloi_left[n_cut+1][n_surf].id_point, i_start);
			add_second_pointsDrillSloi = true;
		}
		else i1_2 = not_reversed_line ? i_finish : i_start;
	}
	else i1_2 = not_reversed_line ? i_finish : i_start;
}

bool InBorders(CPoint3 pt_1, CPoint3 pt_2, CPoint3 pti)
{
	double x1 = pt_1.x;
	double y1 = pt_1.y;
	double z1 = pt_1.z;

	double x2 = pt_2.x;
	double y2 = pt_2.y;
	double z2 = pt_2.z;

	double minx = min(x1,x2);
	double maxx = max(x1,x2);

	double miny = min(y1,y2);
	double maxy = max(y1,y2);

	double minz = min(z1,z2);
	double maxz = max(z1,z2);

	bool in_borders = 
		pti.x >= minx && pti.x <= maxx &&
		pti.y >= miny && pti.y <= maxy &&
		pti.z >= minz && pti.z <= maxz;

	return in_borders;
}

bool BrokenPlane3D::AddingLineToPoligon( bool Front,
	previouse_line & prev_line,
	std::map<int, int> & slips,	
	int & slip_to_add,
	int _i_surf_left,//номер добавляемой линии
	int _i1_left,//первая точка добавляемой линии - сперва это точка пересечения с вертикальной линией потом начиная со второй итерации это точка из m_SurfLineIntersectPoints
	CPoint3 _pt_1,
	int n_cut, 
	int n_surf_poligon,
	int i_poligon,
	int & __i_surf_left,
	int & __i1_left)
{
	__i_surf_left = -1;
	__i1_left = -1;

	int unv = 0, dst = 0;


	// первая точка добавляемой линии
	int _i1_1 = _i1_left;
	// ищем вторую точку добавляемой линии как ближайшую к первой точке точку пересечения
	int _i1_2 = -1;
	CPoint3 _pt_2;

	int slip = 0;
	slip_to_add = -1;
	for (std::vector<SurfLineIntersectPoint>::iterator it = 
		this->m_SurfLineIntersectPoints[n_cut].begin();
		it != this->m_SurfLineIntersectPoints[n_cut].end(); 
	it++, slip++)
	{
		std::map<int, int>::iterator found = slips.find(slip);
		if (found == slips.end())// если точка пересечения ещё не добавлена в полигон
		{
			int povorot = 0;
			int _povorot = 0;
			if (prev_line.was_reverse > -1 
				&& prev_line.i_surf > -1 && prev_line.i_surf < m_broken_lines.Size()
				&& prev_line.i_surf_next > -1 && prev_line.i_surf_next < m_broken_lines.Size()

				&& prev_line.ip1 > -1 && prev_line.ip2 > -1
				&& prev_line.ip1 < m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetPointsNumber()
				&& prev_line.ip2 < m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetPointsNumber()

				&& prev_line.in1 > -1 && prev_line.in2 > -1
				&& prev_line.in1 < m_broken_lines[prev_line.i_surf_next].m_lines[n_cut].GetPointsNumber()
				&& prev_line.in2 < m_broken_lines[prev_line.i_surf_next].m_lines[n_cut].GetPointsNumber()
				
				)// ищем векторное произведение
			{				
				//m_polySloi[prev_line.i_surf].m_poligones[n_cut][i_poligon];

				//CPoint3 p1 = m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetDocumentPoint(prev_line.ip1);
				//CPoint3 p2 = m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetDocumentPoint(prev_line.ip2);

				CPoint3 n1 = m_broken_lines[prev_line.i_surf_next].m_lines[n_cut].GetDocumentPoint(prev_line.in1);
				CPoint3 n2 = m_broken_lines[prev_line.i_surf_next].m_lines[n_cut].GetDocumentPoint(prev_line.in2);

				// строим вектора на отрезках из предыдущей линии и следующей линии 
				//CPoint3 p = p2 - p1;
				CPoint3 n = n2 - n1;
				CPoint3 _n = (*it).point.GetFirstDocumentPoint() - _pt_1;

				//Находим их векторное произведение - оно будет перпендикулярно плоскости профиля
				CPoint3 vp1; vp1.InitAsVectorProduct(prev_line.p, n);
				CPoint3 _vp1; _vp1.InitAsVectorProduct(prev_line.p, _n);

				//вектор направлений вдоль профиля
				CPoint3 dir (
					m_vMapBlnProfiles[n_cut+1].x - m_vMapBlnProfiles[n_cut].x,
					m_vMapBlnProfiles[n_cut+1].y - m_vMapBlnProfiles[n_cut].y,
					0.0);

				// Находим второе векторное произведение - 
				// оно будет либо вертикально вверх, либо вертикально вниз
				// если вверх то мы в точке пересечения линий имеем поворот вправо
				// если вниз, - то влево
				CPoint3 vp2; vp2.InitAsVectorProduct(dir, vp1);
				CPoint3 _vp2; _vp2.InitAsVectorProduct(dir, _vp1);

				if (vp2.z > 0)
					povorot = 1;//поворот вправо
				else
					povorot = -1;		

				if (_vp2.z > 0)
					_povorot = 1;//поворот вправо
				else
					_povorot = -1;				
			}

			// если добавляемая линия - продлеваемая линия 
			if ((*it).i_surf1 == _i_surf_left)
			{				
				if (prev_line.unv > 0
					|| ((*it).i1_1 >= prev_line.in1 && (*it).i1_1 <= prev_line.in2)
					)// если по номерам точек не определишься 
					
				{
					// опираемся на точки пересечения линий
					if (Front)// движемся по часовой стрелке
					{
						if (_povorot == -1) //поворот влево
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}
					}
					else
					{
						if (_povorot == 1) //поворот вправо
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}
					}
				}
				else
				{
					if (Front)
					{

						if (povorot == 1 //если предыдущая добавленная линия ограничена точкой пересечения с поворотом вправо по росту нумерации точек в тогда следующей (а теперь уже в текущей) линии
							&& (*it).i1_1 < prev_line.in2)// а исследуемая сейчас точка пересечения по нумерации точек меньше prev_line.in2 точки пересечения добавленной на предыдущей итерации
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;// значит это не то что нужно
						}

						if (povorot == -1 //если предыдущая добавленная линия ограничена точкой пересечения с поворотом влево по росту нумерации точек в тогда следующей (а теперь уже в текущей) линии
							&& (*it).i1_1 > prev_line.in2)// а исследуемая сейчас точка пересечения по нумерации точек больше prev_line.in2 точки пересечения добавленной на предыдущей итерации
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;// значит это не то что нужно			
						}
					}
					else
					{
						if (povorot == -1 
							&& (*it).i1_1 < prev_line.in2)
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}

						if (povorot == 1 
							&& (*it).i1_1 > prev_line.in2)
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}
					}
				}

				if (_i1_2 == -1)
				{
					_i1_2 = (*it).i1_1;
					_pt_2 = (*it).point.GetDocumentPoint(0);

					__i_surf_left = (*it).i_surf2;
					__i1_left = (*it).i1_2;

					slip_to_add = slip;

					unv = (*it).unvisibles;
					dst = (*it).dst_to_vis;

				}
				else
				{
					//if (labs((*it).i1_1 - _i1_1) < labs(_i1_2 - _i1_1)) //  условие ближайшей к первой точке точки пересечения
					if (Distance_xy((*it).point.GetDocumentPoint(0), _pt_1) < Distance_xy(_pt_2, _pt_1)) //  условие ближайшей к первой точке точки пересечения
					{
						_i1_2 = (*it).i1_1;
						_pt_2 = (*it).point.GetDocumentPoint(0);

						__i_surf_left = (*it).i_surf2;
						__i1_left = (*it).i1_2;

						slip_to_add = slip;

						unv = (*it).unvisibles;
						dst = (*it).dst_to_vis;
					}
				}
			}
			// если добавляемая линия - пересекаемая линия 								
			if ((*it).i_surf2 == _i_surf_left)
			{
				if ((*it).unvisibles > 0 
					|| ((*it).i1_2 >= prev_line.in1 && (*it).i1_2 <= prev_line.in2)
					)// если по номерам точек не определишься 
				{
					// опираемся на точки пересечения линий
					if (Front)// движемся по часовой стрелке
					{
						if (_povorot == -1) //поворот влево
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}
					}
					else
					{
						if (_povorot == 1) //поворот вправо
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}
					}
				}
				else
				{
					if (Front)
					{
						if (povorot == 1 //если предыдущая добавленная линия ограничена точкой пересечения с поворотом вправо по росту нумерации точек в тогда следующей (а теперь уже в текущей) линии
							&& (*it).i1_2 < prev_line.in2)// а исследуемая сейчас точка пересечения по нумерации точек меньше prev_line.in2 точки пересечения добавленной на предыдущей итерации
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;// значит это не то что нужно
						}

						if (povorot == -1 //если предыдущая добавленная линия ограничена точкой пересечения с поворотом влево по росту нумерации точек в тогда следующей (а теперь уже в текущей) линии
							&& (*it).i1_2 > prev_line.in2)// а исследуемая сейчас точка пересечения по нумерации точек больше prev_line.in2 точки пересечения добавленной на предыдущей итерации
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;// значит это не то что нужно
						}
					}
					else
					{
						if (povorot == -1 
							&& (*it).i1_2 < prev_line.in2)
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}

						if (povorot == 1 
							&& (*it).i1_2 > prev_line.in2)
						{
							slips.insert(std::map<int, int>::value_type(slip, -2));//если точку нельзя добавлять в полигон, запоминаем её чтобы повторным ходом она случайно туда не попала
							continue;
						}
					}
				}
				
				if (_i1_2 == -1)
				{
					_i1_2 = (*it).i1_2;
					_pt_2 = (*it).point.GetDocumentPoint(0);

					__i_surf_left = (*it).i_surf1;
					__i1_left = (*it).i1_1;

					slip_to_add = slip;

					unv = (*it).unvisibles;
					dst = (*it).dst_to_vis;
				}
				else
				{
					//if (labs((*it).i1_2 - _i1_1) < labs(_i1_2 - _i1_1)) //  условие ближайшей к первой точке точки пересечения
					if (Distance_xy((*it).point.GetDocumentPoint(0), _pt_1) < Distance_xy(_pt_2, _pt_1)) //  условие ближайшей к первой точке точки пересечения
					{
						_i1_2 = (*it).i1_2;
						_pt_2 = (*it).point.GetDocumentPoint(0);

						__i_surf_left = (*it).i_surf1;
						__i1_left = (*it).i1_1;

						slip_to_add = slip;

						unv = (*it).unvisibles;
						dst = (*it).dst_to_vis;
					}
				}
			}
		}
	}


	if (_i1_2 > -1)
	{
		int reverse = -1;
		int added = 0;
		if (Front)
		{
			reverse = AddLineToPoligon_Front(n_cut, _i_surf_left, 
				_i1_1,	_i1_2,
				n_cut, n_surf_poligon, i_poligon, added);
		}
		else
		{
			reverse = AddLineToPoligon_Back(n_cut, _i_surf_left, 
				_i1_1,	_i1_2,
				n_cut, n_surf_poligon, i_poligon, added);
		}

		prev_line.was_reverse = reverse;
		prev_line.i_surf = _i_surf_left;
		if (reverse > -1)//условие того, что линия всё-таки добавлена в полигон
		{
			if (added > 1)
			{
				prev_line.i1 = reverse == 1 
					? min(_i1_1, _i1_2) // если точки добавлялись реверсивно, то последняя добаленная в полигон точка prev_line.i1 + 1, предпоследняя prev_line.i1 + 2
					: max(_i1_1, _i1_2);// иначе последняя добаленная в полигон точка prev_line.i1, предпоследняя prev_line.i1 - 1
				
				// опорные точки крайнего вектора полигона
				prev_line.ip1 = reverse == 1 ? prev_line.i1 + 2 : prev_line.i1 - 1;
				prev_line.ip2 = reverse == 1 ? prev_line.i1 + 1 : prev_line.i1;

				prev_line.p1 = m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetDocumentPoint(prev_line.ip1);
				prev_line.p2 = m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetDocumentPoint(prev_line.ip2);

				// строим вектор на отрезке из предыдущей линии
				prev_line.p = prev_line.p2 - prev_line.p1;
			}
		}


		if (slip_to_add > -1 
			&& slip_to_add < this->m_SurfLineIntersectPoints[n_cut].size() 
			&& this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.GetPointsNumber() > 0)
		{

			if (Front)
			{
				AddPointToPoligon_Front(this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.m_vdPoints[0],
					n_cut, n_surf_poligon, i_poligon);
			}
			else
			{
				AddPointToPoligon_Back(this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.m_vdPoints[0],
					n_cut, n_surf_poligon, i_poligon);
			}

			int i_slip = slips.size();

			slips.insert(std::map<int, int>::value_type(slip_to_add, i_slip));


			if (added < 2)
			{
				prev_line.i1 = -1;
				prev_line.ip1 = -1;
				prev_line.ip2 = -1;

				prev_line.p1 = _pt_1;
				prev_line.p2 = this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.m_vdPoints[0];

				// строим вектор на отрезке из предыдущей линии
				prev_line.p = prev_line.p2 - prev_line.p1;
			}

			if (__i1_left > -1 && __i_surf_left > -1)
			{
				prev_line.i_surf_next = __i_surf_left;
				// опорные точки вектора на линии, пересекающей полигон
				prev_line.in1 = __i1_left;
				prev_line.in2 = prev_line.in1 + 1;

				prev_line.unv = unv;
				prev_line.dst = dst;
			}

		}


		return true;
	}	
	return false;
}

int BrokenPlane3D::LeftWalk(int & one_right_n_cut, bool & found_above_right_n_cut, 
							 std::map<int, int> & slips, int & last_added_slip, 
							 int & _i_surf_left, int & _i1_left,
							 int n_cut, int n_surf, int i_poligon, int n_surf_poligon, int n_surf_do_not_add,
							 bool like_podoshva, bool add_first_pointsDrillSloi
							 )
{
	_i_surf_left = n_surf;
	_i1_left = -1;
	CPoint3 _pt_left;
	last_added_slip = -1;

	//if (add_first_pointsDrillSloi)
	// ищем какая из вышележащих линий имеет точку пересечения с первой слева вспомогательной вертикальной линией
	while (!found_above_right_n_cut && one_right_n_cut <= n_surf)
	{
		found_above_right_n_cut = 
			(m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].GetPointsNumber() > 0);
		if (!found_above_right_n_cut)
			one_right_n_cut++;
	}

	if (like_podoshva && add_first_pointsDrillSloi && found_above_right_n_cut)
	{
		// добавляем в полигон точку пересечения вышележащей линии с первой слева вспомогательной линией
		AddPointToPoligon_Front(m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].m_vdPoints[0],
			n_cut, n_surf_poligon, i_poligon);

		_i_surf_left = n_surf-one_right_n_cut;
		_i1_left = m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].id_point;
		_pt_left = m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].m_vdPoints[0];
	}							

	previouse_line prev_line_left;

	// если добавлена точка пересечения вышележащей линии с первой слева вспомогательной линией
	if (like_podoshva && add_first_pointsDrillSloi && found_above_right_n_cut)
	{
		int __i_surf_left = -1;
		int __i1_left = -1;
		int slip_to_add = -1;

		int n = 0; 
		while (_i_surf_left != n_surf_do_not_add && 
			AddingLineToPoligon(true,
			prev_line_left,
			slips, slip_to_add,
			_i_surf_left, _i1_left, _pt_left,
			n_cut, n_surf_poligon, i_poligon,
			__i_surf_left, __i1_left))
		{
			_i_surf_left = __i_surf_left;
			_i1_left     = __i1_left;

			if (slip_to_add > -1) 
			{
				last_added_slip = slip_to_add;
				_pt_left = this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.GetDocumentPoint(0);
			}

			__i_surf_left = -1;
			__i1_left = -1;

			if (++n > 10)
				break;
		}
	}
	return -1;
}



int BrokenPlane3D::RightWalk(int & one_left_n_cut_plus_1, bool & found_above_left_n_cut_plus_1, 
							  std::map<int, int> & slips, int & last_added_slip,
							  int & _i_surf_right, int & _i1_right,
							  int n_cut, int n_surf, int i_poligon, int n_surf_poligon, int n_surf_do_not_add,
							  bool like_podoshva, bool add_second_pointsDrillSloi)
{
	_i_surf_right = n_surf;
	_i1_right = -1;
	CPoint3 _pt_right;
	last_added_slip = -1;

	//if (add_second_pointsDrillSloi)
	// ищем какая из вышележаших линий имеет точку пересечения со второй вспомогательной вертикальной линией
	while (!found_above_left_n_cut_plus_1 && one_left_n_cut_plus_1 <= n_surf)
	{
		found_above_left_n_cut_plus_1 = 
			(m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].GetPointsNumber() > 0);
		if (!found_above_left_n_cut_plus_1)
			one_left_n_cut_plus_1++;
	}

	if (like_podoshva && add_second_pointsDrillSloi && found_above_left_n_cut_plus_1)
	{
		// добавляем в полигон точку пересечения вышележащей линии со второй вспомогательной линией
		AddPointToPoligon_Back(m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].m_vdPoints[0],
			n_cut, n_surf_poligon, i_poligon);

		_i_surf_right = n_surf-one_left_n_cut_plus_1;
		_i1_right = m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].id_point;
		_pt_right = m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].m_vdPoints[0];
	}

	previouse_line prev_line_right;
	// если добавлена точка пересечения вышележащей линии со второй вспомогательной линией
	if (like_podoshva && add_second_pointsDrillSloi && found_above_left_n_cut_plus_1)
	{
		int __i_surf_right = -1;
		int __i1_right = -1;
		int slip_to_add = -1;

		int n = 0;
		while (_i_surf_right != n_surf_do_not_add && 
			AddingLineToPoligon(false,
			prev_line_right,
			slips, slip_to_add,
			_i_surf_right, _i1_right, _pt_right,
			n_cut, n_surf_poligon, i_poligon,
			__i_surf_right, __i1_right))
		{
			_i_surf_right  = __i_surf_right;
			_i1_right      = __i1_right;

			if (slip_to_add > -1) 
			{
				last_added_slip = slip_to_add;
				_pt_right = this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.GetDocumentPoint(0);
			}

			__i_surf_right = -1;
			__i1_right     = -1;

			if (++n > 10)
				break;
		}
	}
	return -1;
}



void BrokenPlane3D::MiddleWalk(int i1_1, int i1_2,
							  std::map<int, int> & slips, int & last_added_slip,
							  int n_cut, int n_surf, int i_poligon, int n_surf_poligon, int n_surf_do_not_add,
							  bool add_first_pointsDrillSloi, bool add_second_pointsDrillSloi
							   )
{
	if (!add_first_pointsDrillSloi && !add_second_pointsDrillSloi)
	{
		int i1_min = min(i1_1, i1_2);
		int i1_max = max(i1_1, i1_2);

		CPoint3 
			last_line_point,
			first_line_point;

		CPoint2 left_point = m_vMapBlnProfiles[n_cut];


		// добавляем линию, 
		// но сначала определяем прямой или обратный порядок добавления линии 
		// а на случай если в полигоне или в линии нет точек 
		// инициализируем флаг порядка добавления линии
		bool force_reverse = false;
		if (
			m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0 &&
			i1_min + 1 < m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() &&
			i1_max < m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber()
			)
		{
			first_line_point	= m_broken_lines	[n_surf].m_lines[n_cut].GetDocumentPoint(i1_min + 1);
			last_line_point		= m_broken_lines	[n_surf].m_lines[n_cut].GetDocumentPoint(i1_max);
			double distance_to_last  = Distance(left_point, last_line_point);
			double distance_to_first = Distance(left_point, first_line_point);
			// устанавливаем порядок добавления точек справа налево
			force_reverse = distance_to_last > distance_to_first;
		}

		int added = 0;
		// добавляем в полигон точки текущей линии
		int reverse = AddLineToPoligon_Front(force_reverse, n_cut, n_surf, i1_1, i1_2, n_cut, n_surf_poligon, i_poligon, added);

		previouse_line prev_line;
		prev_line.was_reverse = reverse;
		prev_line.i_surf = n_surf;
		if (reverse > -1)//условие того, что линия всё-таки добавлена в полигон
		{
			if (added > 1)
			{
				prev_line.i1 = reverse == 1 
					? min(i1_1, i1_2) // если точки добавлялись реверсивно, то последняя добаленная в полигон точка prev_line.i1 + 1, предпоследняя prev_line.i1 + 2
					: max(i1_1, i1_2);// иначе последняя добаленная в полигон точка prev_line.i1, предпоследняя prev_line.i1 - 1
				
				// опорные точки крайнего вектора полигона
				prev_line.ip1 = reverse == 1 ? prev_line.i1 + 2 : prev_line.i1 - 1;
				prev_line.ip2 = reverse == 1 ? prev_line.i1 + 1 : prev_line.i1;

				prev_line.p1 = m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetDocumentPoint(prev_line.ip1);
				prev_line.p2 = m_broken_lines[prev_line.i_surf].m_lines[n_cut].GetDocumentPoint(prev_line.ip2);

				// строим вектор на отрезке из предыдущей линии
				prev_line.p = prev_line.p2 - prev_line.p1;

				if (true)
				{
					int _i_surf_left = -1;
					int _i1_left = -1;
					CPoint3 _pt_left;


					CPoint3 _pt_1 = prev_line.p2, _pt_2;
					// Определяем SurfLineIntersectPoint как ближайшую к _pt_1 при условии, что текущаяя линия - продлеваемая линия

					int slip = 0, slip_found = -1;
					for (std::vector<SurfLineIntersectPoint>::iterator it = 
						this->m_SurfLineIntersectPoints[n_cut].begin();
						it != this->m_SurfLineIntersectPoints[n_cut].end(); 
					it++, slip++)
					{
						// если current линия - продлеваемая линия 
						if ((*it).i_surf1 == n_surf)
						{
							if (_i_surf_left == -1)
							{
								_pt_2 = (*it).point.GetDocumentPoint(0);
								_i_surf_left = (*it).i_surf2;
								_i1_left = (*it).i1_2;

								slip_found = slip;

							}
							else
							{
								if (Distance_xy((*it).point.GetDocumentPoint(0), _pt_1) < Distance_xy(_pt_2, _pt_1)) //  условие ближайшей к первой точке точки пересечения
								{
									_pt_2 = (*it).point.GetDocumentPoint(0);

									_i_surf_left = (*it).i_surf2;
									_i1_left = (*it).i1_2;

									slip_found = slip;
								}
							}
						}
					}

					if (_i1_left > -1 && _i_surf_left > -1)
					{
						prev_line.i_surf_next = _i_surf_left;
						// опорные точки вектора на линии, пересекающей полигон
						prev_line.in1 = _i1_left;
						prev_line.in2 = prev_line.in1 + 1;
					}

					if (_i_surf_left > -1)
					{
						_pt_left = _pt_2;


						int __i_surf_left = -1;
						int __i1_left = -1;
						int slip_to_add = -1;

						int n = 0; 
						while (AddingLineToPoligon(true,
							prev_line,
							slips, slip_to_add,
							_i_surf_left, _i1_left, _pt_left,
							n_cut, n_surf_poligon, i_poligon,
							__i_surf_left, __i1_left))
						{
							_i_surf_left = __i_surf_left;
							_i1_left     = __i1_left;


							if (slip_to_add > -1) 
							{
								last_added_slip = slip_to_add;
								_pt_left = this->m_SurfLineIntersectPoints[n_cut][slip_to_add].point.GetDocumentPoint(0);
							}

							__i_surf_left = -1;
							__i1_left = -1;

							if (_i_surf_left == n_surf_do_not_add)
								break;

							if (++n > 10)
								break;
						}
					}
				}
			}
		}
	}
}

int calc_n_slips(std::map<int,int> & slips)
{
	int cnt = 0;
	for(std::map<int,int>::iterator it = slips.begin();
		it != slips.end(); ++it)
	{
		if((*it).second != -2)
		{
			++cnt;
		}
	}
	return cnt;
}


bool BrokenPlane3D::FindIntersection(bool back, int i1_1, int i2_1,
					  int n_cut, int n_surf1, int n_surf2,
					  std::vector<SurfLineIntersectPoint> & vslip)
{
	for (int i = 0; i < 8; ++i)
	{
		int _i1_1 = i1_1 + (back ? +i : -i);
		int _i2_1 = i2_1 + (back ? +i : -i);

		if (
			_i1_1 >= 0 && _i1_1 < this->m_broken_lines[n_surf1].m_lines[n_cut].GetPointsNumber() &&
			_i2_1 >= 0 && _i2_1 < this->m_broken_lines[n_surf1].m_lines[n_cut].GetPointsNumber())
		{
			CPoint3 pt_1 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(_i1_1);
			CPoint3 pt_2 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(_i2_1);

			if (i > 0 && (!pt_1.bVisible || !pt_2.bVisible))
			{
				return false;
			}

			CPoint3 pti; int i1_2, i2_2; int unvisibles, dst_to_vis;
			if (this->m_broken_lines[n_surf2].m_lines[n_cut].FindIntersection(this->m_profile3D, 
				pt_1, pt_2, pti, i1_2, i2_2, unvisibles, dst_to_vis)
				//(unvisibles < 2) - with this works as first version of FindIntersection() function
				&& ((unvisibles < 2) || (unvisibles == 2 && dst_to_vis < 24))
				)
			{								
				double distance_pt_1 = Distance(pt_1, pti);
				double distance_pt_2 = Distance(pt_2, pti);
				bool in_borders = InBorders(pt_1, pt_2, pti);

				if (i > 0 && !in_borders)
					continue;

				if (!in_borders)
				{
					if (back)
					{
						if (distance_pt_1 > distance_pt_2)
							continue;
					}
					else
					{
						if (distance_pt_1 < distance_pt_2)
							continue;
					}
				}



				vslip.push_back(SurfLineIntersectPoint());

				vslip.back().i_surf1 = n_surf1;
				vslip.back().i1_1 = _i1_1;
				vslip.back().i2_1 = _i2_1;

				vslip.back().back = back;
				vslip.back().dist_to_end = in_borders ? 0.0 : (back ? distance_pt_1 : distance_pt_2);

				vslip.back().i_surf2 = n_surf2;
				vslip.back().i1_2 = i1_2;
				vslip.back().i2_2 = i2_2;
				vslip.back().unvisibles = unvisibles;
				vslip.back().dst_to_vis = dst_to_vis;

				vslip.back().point.Init(this->m_pSurfDoc, pti);	
				return true;
			}
		}
	}
	return false;
}

void BrokenPlane3D::Build()
{
	int n_cut, n_surf, n_drill, n_fault, n_catch;
	CPoint3 pt;
	//***********************************************************************
	// fill drill points
	//m_drills.clear();
	//m_drills.resize(m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE());
	// this removed into Init_broken_plane
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		if (m_pSurfDoc)
		{
			m_drills[n_drill].InitDoc(m_pSurfDoc);
			m_drills_line_left[n_drill].InitDoc(m_pSurfDoc);
			m_drills_line_right[n_drill].InitDoc(m_pSurfDoc);
		}
		else
			MessageBox(0, "fill drill points !m_pSurfDoc", "BrokenPlane3D::Build", 0);

		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_drill].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			if(m_pointsDrillSloi[n_drill][n_surf].GetPointsNumber() > 0)
			{
				pt = m_pointsDrillSloi[n_drill][n_surf].m_vdPoints[0];
				m_drills[n_drill].PushBack(pt);
			}
		}
	}


	for (n_surf = 0; n_surf < m_nSurfs; ++n_surf)
	{
		for (n_cut = 0; n_cut < m_nCuts; ++n_cut)
		{
			for (int _i2 = 1; _i2 < this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber();)
			{
				int _i1 = _i2 - 1;

				CPoint3 pt_1 = this->m_broken_lines[n_surf].m_lines[n_cut].GetDocumentPoint(_i1);
				CPoint3 pt_2 = this->m_broken_lines[n_surf].m_lines[n_cut].GetDocumentPoint(_i2);

				// на границах клеток линии содержат вертикальные ступеньки
				if (Distance_xy(pt_1, pt_2) < 1e-32)
				{
					this->m_broken_lines[n_surf].m_lines[n_cut].ErasePoint(_i2);
				}
				else
					++_i2;
			}
		}
	}

	//***********************************************************************
	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			if (this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0)
			{

				if (this->m_drills_line_right[n_cut].GetPointsNumber() > 1)
				{
					CPoint3 pt_0 = this->m_drills_line_right[n_cut].GetDocumentPoint(0);
					CPoint3 pt_1 = this->m_drills_line_right[n_cut].GetDocumentPoint(1);
					
					CPoint3 pti; int i1, i2; int unvisibles, dst_to_vis;
					if (this->m_broken_lines[n_surf].m_lines[n_cut].FindIntersection(this->m_profile3D, 
						pt_0, pt_1, pti, i1, i2, unvisibles, dst_to_vis) && unvisibles < 2)
					{
						m_pointsDrillSloi_right[n_cut][n_surf].PushBack(pti);
						m_pointsDrillSloi_right[n_cut][n_surf].id_point = i1;
					}
				}
				if (this->m_drills_line_left[n_cut+1].GetPointsNumber() > 1)
				{
					CPoint3 pt_0 = this->m_drills_line_left[n_cut+1].GetDocumentPoint(0);
					CPoint3 pt_1 = this->m_drills_line_left[n_cut+1].GetDocumentPoint(1);
					
					CPoint3 pti; int i1, i2; int unvisibles, dst_to_vis;
					if (this->m_broken_lines[n_surf].m_lines[n_cut].FindIntersection(this->m_profile3D, 
						pt_0, pt_1, pti, i1, i2, unvisibles, dst_to_vis) && unvisibles < 2)
					{
						m_pointsDrillSloi_left[n_cut+1][n_surf].PushBack(pti);
						m_pointsDrillSloi_left[n_cut+1][n_surf].id_point = i1;
					}
				}
			}
		}
		this->m_broken_lines[n_surf].m_lines_ObjectList.Init1(m_broken_lines[n_surf].m_lines, &this->m_broken_lines[n_surf]);
	}
#if HAVE_EXTRA_VISIBLE_BLN_PROFILE_LINES
	//***********************************************************************
	for (n_cut = 0; n_cut < m_nCuts; n_cut++)
	{
		for (int n_surf1 = 0; n_surf1 < m_nSurfs; n_surf1++)
		{
			if (this->m_broken_lines[n_surf1].m_lines[n_cut].GetPointsNumber() > 0)
			{
				for (size_t i2_1 = 1;  i2_1 < this->m_broken_lines[n_surf1].m_lines[n_cut].GetPointsNumber(); i2_1++)
				{
					size_t i1_1 = i2_1-1;

					bool b1 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i1_1).bVisible;
					bool b2 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i2_1).bVisible;

					bool to_find_intersection = false;
					if (b1 || b2)						
					{
						to_find_intersection = true;
					}

					if (to_find_intersection)
					{
						bool found_intersection = false;

						CPoint3 pt_1 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i1_1);
						CPoint3 pt_2 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i2_1);

						// сюда складываем все точки пересечения
						std::vector<SurfLineIntersectPoint> vslip;
						vslip.clear();

						for (int n_surf2 = n_surf1-1; n_surf2 >= 0; n_surf2--)
						{
							CPoint3 pti; int i1_2, i2_2; int unvisibles, dst_to_vis;
							if (this->m_broken_lines[n_surf2].m_lines[n_cut].FindIntersection(this->m_profile3D, 
								pt_1, pt_2, pti, i1_2, i2_2, unvisibles, dst_to_vis)
								//(unvisibles < 2) - with this works as first version of FindIntersection() function
								///&& ((unvisibles < 2) || (unvisibles == 2 && dst_to_vis < 24))
								&& (unvisibles < 2)
								)
							{								

								if (InBorders(pt_1, pt_2, pti))
								{			
									double distance_pt_1 = Distance(pt_1, pti);
									double distance_pt_2 = Distance(pt_2, pti);

									vslip.push_back(SurfLineIntersectPoint());

									vslip.back().i_surf1 = n_surf1;
									vslip.back().i1_1 = i1_1;
									vslip.back().i2_1 = i2_1;

//									vslip.back().back = back;
									vslip.back().dist_to_end = min( distance_pt_1, distance_pt_2 );

									vslip.back().i_surf2 = n_surf2;
									vslip.back().i1_2 = i1_2;
									vslip.back().i2_2 = i2_2;
									vslip.back().unvisibles = unvisibles;
									vslip.back().dst_to_vis = dst_to_vis;

									vslip.back().point.Init(this->m_pSurfDoc, pti);
								}

							}
						}

						if (vslip.size() > 1)
						{
							// сортируем их в соответствии с правилом, заложенном в операторе меньше:
							// при сортировке по возрастанию в начале отсортированного вектора должен оказаться объект 
							// с наименьшим dist_to_end, но если dist_to_end одинаково то с наибольшим i_surf2

							std::sort(vslip.begin(), vslip.end());
						}

						// берём первый элемент списка
						if (vslip.size() > 0)
						{
							if (!(n_cut < this->m_SurfLineIntersectPoints.size()))
							{
								char str[1024];
								sprintf(str, "m_SurfLineIntersectPoints.size()=%d n_cut=%d", m_SurfLineIntersectPoints.size(), n_cut);
								MessageBox(0,str,"",0);
							}
							this->m_SurfLineIntersectPoints[n_cut].push_back(SurfLineIntersectPoint());

							this->m_SurfLineIntersectPoints[n_cut].back().i_surf1     = vslip[0].i_surf1;
							this->m_SurfLineIntersectPoints[n_cut].back().i1_1        = vslip[0].i1_1;
							this->m_SurfLineIntersectPoints[n_cut].back().i2_1        = vslip[0].i2_1;

							this->m_SurfLineIntersectPoints[n_cut].back().back        = vslip[0].back;
							this->m_SurfLineIntersectPoints[n_cut].back().dist_to_end = vslip[0].dist_to_end;

							this->m_SurfLineIntersectPoints[n_cut].back().i_surf2     = vslip[0].i_surf2;
							this->m_SurfLineIntersectPoints[n_cut].back().i1_2        = vslip[0].i1_2;
							this->m_SurfLineIntersectPoints[n_cut].back().i2_2        = vslip[0].i2_2;

							this->m_SurfLineIntersectPoints[n_cut].back().unvisibles  = vslip[0].unvisibles;
							this->m_SurfLineIntersectPoints[n_cut].back().dst_to_vis  = vslip[0].dst_to_vis;

							BYTE _podoshva = this->m_broken_lines[vslip[0].i_surf2].podoshva;
							this->m_SurfLineIntersectPoints[n_cut].back().with_krovlja = _podoshva == 2;

							this->m_SurfLineIntersectPoints[n_cut].back().point.Init(this->m_pSurfDoc, vslip[0].point.m_vdPoints[0]);

							found_intersection = true;
						}
						vslip.clear();
					}
				}
			}
		}
	}
	//***********************************************************************
#else
	//***********************************************************************
	for (n_cut = 0; n_cut < m_nCuts; n_cut++)
	{
		for (int n_surf1 = 0; n_surf1 < m_nSurfs; n_surf1++)
		{
			if (this->m_broken_lines[n_surf1].m_lines[n_cut].GetPointsNumber() > 0)
			{
				for (size_t i2_1 = 1;  i2_1 < this->m_broken_lines[n_surf1].m_lines[n_cut].GetPointsNumber(); i2_1++)
				{
					size_t i1_1 = i2_1-1;

					bool b1 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i1_1).bVisible;
					bool b2 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i2_1).bVisible;

					bool to_find_intersection = false;
					bool back;//направление продлевания линии относительно нумерации точек в этой линии
					if (!b1 && b2)						
					{
						to_find_intersection = true;
						back = true;
					}

					if (b1 && !b2)						
					{
						to_find_intersection = true;
						back = false;
					}

					if (to_find_intersection)
					{
						bool found_intersection = false;

						// сюда складываем все точки пересечения
						std::vector<SurfLineIntersectPoint> vslip;
						vslip.clear();

						for (int n_surf2 = n_surf1-1; n_surf2 >= 0; n_surf2--)
						{
#if 1
							this->FindIntersection(back, i1_1, i2_1, n_cut, n_surf1, n_surf2, vslip);
#else
							CPoint3 pt_1 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i1_1);
							CPoint3 pt_2 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i2_1);

							CPoint3 pti; int i1_2, i2_2; int unvisibles, dst_to_vis;
							if (this->m_broken_lines[n_surf2].m_lines[n_cut].FindIntersection(this->m_profile3D, 
								pt_1, pt_2, pti, i1_2, i2_2, unvisibles, dst_to_vis)
								//(unvisibles < 2) - with this works as first version of FindIntersection() function
								&& ((unvisibles < 2) || (unvisibles == 2 && dst_to_vis < 24))
								)
							{								
								double distance_pt_1 = Distance(pt_1, pti);
								double distance_pt_2 = Distance(pt_2, pti);
								bool in_borders = InBorders(pt_1, pt_2, pti);

								if (!in_borders)
								{
									if (back)
									{
										if (distance_pt_1 > distance_pt_2)
											continue;
									}
									else
									{
										if (distance_pt_1 < distance_pt_2)
											continue;
									}
								}

					

								vslip.push_back(SurfLineIntersectPoint());

								vslip.back().i_surf1 = n_surf1;
								vslip.back().i1_1 = i1_1;
								vslip.back().i2_1 = i2_1;

								vslip.back().back = back;
								vslip.back().dist_to_end = back ? distance_pt_1 : distance_pt_2;

								vslip.back().i_surf2 = n_surf2;
								vslip.back().i1_2 = i1_2;
								vslip.back().i2_2 = i2_2;
								vslip.back().unvisibles = unvisibles;
								vslip.back().dst_to_vis = dst_to_vis;

								vslip.back().point.Init(this->m_pSurfDoc, pti);								
							}
#endif
						}

						if (vslip.size() > 1)
						{
							// сортируем их в соответствии с правилом, заложенном в операторе меньше:
							// при сортировке по возрастанию в начале отсортированного вектора должен оказаться объект 
							// с наименьшим dist_to_end, но если dist_to_end одинаково то с наибольшим i_surf2

							std::sort(vslip.begin(), vslip.end());
						}

						// берём первый элемент списка
						if (vslip.size() > 0)
						{
							if (!(n_cut < this->m_SurfLineIntersectPoints.size()))
							{
								char str[1024];
								sprintf(str, "m_SurfLineIntersectPoints.size()=%d n_cut=%d", m_SurfLineIntersectPoints.size(), n_cut);
								MessageBox(0,str,"",0);
							}
							this->m_SurfLineIntersectPoints[n_cut].push_back(SurfLineIntersectPoint());

							this->m_SurfLineIntersectPoints[n_cut].back().i_surf1     = vslip[0].i_surf1;
							this->m_SurfLineIntersectPoints[n_cut].back().i1_1        = vslip[0].i1_1;
							this->m_SurfLineIntersectPoints[n_cut].back().i2_1        = vslip[0].i2_1;

							this->m_SurfLineIntersectPoints[n_cut].back().back        = vslip[0].back;
							this->m_SurfLineIntersectPoints[n_cut].back().dist_to_end = vslip[0].dist_to_end;

							this->m_SurfLineIntersectPoints[n_cut].back().i_surf2     = vslip[0].i_surf2;
							this->m_SurfLineIntersectPoints[n_cut].back().i1_2        = vslip[0].i1_2;
							this->m_SurfLineIntersectPoints[n_cut].back().i2_2        = vslip[0].i2_2;

							this->m_SurfLineIntersectPoints[n_cut].back().unvisibles  = vslip[0].unvisibles;
							this->m_SurfLineIntersectPoints[n_cut].back().dst_to_vis  = vslip[0].dst_to_vis;

							BYTE _podoshva = this->m_broken_lines[vslip[0].i_surf2].podoshva;
							this->m_SurfLineIntersectPoints[n_cut].back().with_krovlja = _podoshva == 2;

							this->m_SurfLineIntersectPoints[n_cut].back().point.Init(this->m_pSurfDoc, vslip[0].point.m_vdPoints[0]);

							found_intersection = true;
						}


						vslip.clear();

						BYTE podoshva = this->m_broken_lines[n_surf1].podoshva;
						if (!found_intersection && podoshva == 1)//	продлеваем только подошву, кровлю не продлеваем!!!
						{
							CPoint3 pt_1 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i1_1);
							CPoint3 pt_2 = this->m_broken_lines[n_surf1].m_lines[n_cut].GetDocumentPoint(i2_1);

							if (this->m_drills_line_right[n_cut].GetPointsNumber() > 1)
							{	
								CPoint3 pti; int i1, i2; int unvisibles, dst_to_vis;
								if (this->m_drills_line_right[n_cut].FindIntersection(this->m_profile3D, 
									pt_1, pt_2, pti, i1, i2, unvisibles, dst_to_vis) && unvisibles == 0)
								{
									bool to_push_back = m_pointsDrillSloi_right[n_cut][n_surf1].GetPointsNumber() == 0;

									if (!InBorders(pt_1, pt_2, pti))
									{
										double distance_pt_1 = Distance(pt_1, pti);
										double distance_pt_2 = Distance(pt_2, pti);

										if (back)
										{
											if (distance_pt_1 > distance_pt_2)
												to_push_back = false;
										}
										else
										{
											if (distance_pt_1 < distance_pt_2)
												to_push_back = false;
										}
									}
									if (to_push_back)
									{
										m_pointsDrillSloi_right[n_cut][n_surf1].PushBack(pti);
										m_pointsDrillSloi_right[n_cut][n_surf1].id_point = i1_1;
									}
								}
							}
							if (this->m_drills_line_left[n_cut+1].GetPointsNumber() > 1)
							{							
								CPoint3 pti; int i1, i2; int unvisibles, dst_to_vis;
								if (this->m_drills_line_left[n_cut+1].FindIntersection(this->m_profile3D, 
									pt_1, pt_2, pti, i1, i2, unvisibles, dst_to_vis) && unvisibles == 0)
								{
									bool to_push_back = m_pointsDrillSloi_left[n_cut+1][n_surf1].GetPointsNumber() == 0;

									if (!InBorders(pt_1, pt_2, pti))
									{
										double distance_pt_1 = Distance(pt_1, pti);
										double distance_pt_2 = Distance(pt_2, pti);

										if (back)
										{
											if (distance_pt_1 > distance_pt_2)
												to_push_back = false;
										}
										else
										{
											if (distance_pt_1 < distance_pt_2)
												to_push_back = false;
										}
									}
									if (to_push_back)
									{
										m_pointsDrillSloi_left[n_cut+1][n_surf1].PushBack(pti);
										m_pointsDrillSloi_left[n_cut+1][n_surf1].id_point = i1_1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//***********************************************************************
#endif

	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			if (this->m_broken_lines[n_surf].m_lines[n_cut].GetName().size())
			{
				this->m_broken_lines[n_surf].n_surf = n_surf;
				string name = this->m_broken_lines[n_surf].m_lines[n_cut].GetName();
				this->m_broken_lines[n_surf].SetName(name);
			}
		}
	}

	// init faults object list
	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			if (this->m_broken_fault_lines[n_fault].m_lines[n_cut].GetName().size())
			{
				string name = this->m_broken_fault_lines[n_fault].m_lines[n_cut].GetName();
				this->m_broken_fault_lines[n_fault].SetName(name);
			}
		}
		this->m_broken_fault_lines[n_fault].m_lines_ObjectList.Init1(m_broken_fault_lines[n_fault].m_lines, &this->m_broken_fault_lines[n_fault]);
	}
	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			if (this->m_broken_catch_lines[n_catch].m_lines[n_cut].GetName().size())
			{
				string name = this->m_broken_catch_lines[n_catch].m_lines[n_cut].GetName();
				this->m_broken_catch_lines[n_catch].SetName(name);
			}
		}
		this->m_broken_catch_lines[n_catch].m_lines_ObjectList.Init1(m_broken_catch_lines[n_catch].m_lines, &this->m_broken_catch_lines[n_catch]);
	}

	//***********************************************************************
	vector<order> vo;
	vo.resize(4);
	vector<order>::iterator itr;
	//***********************************************************************
	// fill poligons
//	bool reverse;
	CPoint3 
		last_poly_point,
		last_line_point,
		first_line_point;
	m_polySloi.clear();
	if( m_nSurfs < 2)
	{
		printf("BrokenPlane3D::Build() m_nSurfs = %d\nreturn\n", m_nSurfs);
		return;
	}
	m_polySloi.resize(m_nSurfs - 1);
	m_colorsSloi.resize( m_pointsDrillSloi[0].PLANE_MEMBERS_VECTOR_SIZE() - 1);

	for (n_surf = m_nSurfs - 1; n_surf > 0; n_surf--)
	{
		int n_surf_poligon = n_surf-1;
		m_polySloi[n_surf_poligon].m_poligones.resize( m_nCuts );
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			if (m_broken_lines[n_surf].m_lines[n_cut].id_umpoz < 0)
			{
				//-1 relief
				//-2 hydro
				//-3 razlomy - faults TODO - need to init id_umpoz = -3 for faults

				continue;
			}

#if USE_UNVISIBLE_CUTTING
			if (!(m_broken_lines[n_surf].m_lines[n_cut].GetVisiblePointsNumber() > 0))
#else
			if (!(m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0))
#endif
				continue;



			int one = 1;
			bool found_above_line = false;
			while (!found_above_line && one <= n_surf)
			{
#if USE_UNVISIBLE_CUTTING
				found_above_line = (m_broken_lines[n_surf-one].m_lines[n_cut].GetVisiblePointsNumber() > 0);
#else
				found_above_line = (m_broken_lines[n_surf-one].m_lines[n_cut].GetPointsNumber() > 0);
#endif
				if (!found_above_line)
					one++;
			}

			if (!found_above_line)
				continue;



			//if (this->m_broken_lines[n_surf].m_lines[n_cut].id_ige > -1)
			//{
			//	m_polySloi[n_surf_poligon].id_ige = this->m_broken_lines[n_surf].m_lines[n_cut].id_ige;
			//}
				
			m_polySloi[n_surf_poligon].id_ige = this->m_broken_lines[n_surf].id_ige;

			BYTE podoshva = 0;
			if (this->m_broken_lines[n_surf].m_lines[n_cut].podoshva != 0)
			{
				//podoshva == 2 ? "кровля" : "подошва"
				podoshva = this->m_broken_lines[n_surf].m_lines[n_cut].podoshva;
			}
			podoshva = this->m_broken_lines[n_surf].podoshva;


			if (this->m_broken_lines[n_surf].m_lines[n_cut].GetName().size())
			{
				string name = this->m_broken_lines[n_surf].m_lines[n_cut].GetName();
				this->m_polySloi[n_surf_poligon].SetName(name);
#if USE_UNVISIBLE_CUTTING
#else
				m_polySloi[n_surf].m_poligones[n_cut].SetName(name);
#endif
			}

			m_polySloi[n_surf_poligon].id_umpoz = this->m_broken_lines[n_surf].id_umpoz;
#if USE_UNVISIBLE_CUTTING
#else
			
			m_polySloi[n_surf_poligon].m_poligones[n_cut].id_umpoz = m_polySloi[n_surf_poligon].id_umpoz;

			m_polySloi[n_surf_poligon].m_poligones[n_cut].InitDoc(m_pSurfDoc);
			m_polySloi[n_surf_poligon].m_poligones[n_cut].SetColor(this->m_broken_lines[n_surf].m_lines[n_cut].GetColor());
			m_polySloi[n_surf_poligon].m_poligones[n_cut].SetAlpha(50);


#endif


#if 1
			// TODO - организовать элемент управления, 
			//который бы позволял пользователю менять свойство подошва у геоповерхности
			//	чтобы пользователь мог назначить кровлю линзы

			// 1 - надо провести две вспомогательные вертикальные линии в плоскости разреза на расстоянии w 
			// от скважин верхняя и нижняя точка линий 
			// 2 - если это подошва ищем от линии подошвы те точки 
			//которые выходят за пределы вспомогательных вертикальных линий
			//заносим в полигон
			// 3 ищем пересечения линий всех вышележащих линий слоёв а также вспомогательных вертикальных линий
			//     с лучём образованным крайней и предкрайней точками линии подошвы
			//заносим в полигон ближайшую к крайней точку пересечения, если она не ближе к предкрайней
			//если мы занесли в полигон точку пересечения со вспомогательной линией
#if USE_UNVISIBLE_CUTTING
			//if (podoshva == 1) // если текущая линия - подошва
			{
				int VisiblePartsNumber = GetLineVisiblePartsNumber(n_cut, n_surf);
				for (int i_visible_part = 0; i_visible_part < VisiblePartsNumber; i_visible_part++)
				{
					int i_start, i_finish;
					if (GetLineVisiblePart(n_cut, n_surf, 
										i_visible_part,
										i_start, i_finish))
					{
						int i_poligon = m_polySloi[n_surf_poligon].m_poligones[n_cut].Size();
						m_polySloi[n_surf_poligon].m_poligones[n_cut].push_back(Poligon3D());

						if (this->m_broken_lines[n_surf].m_lines[n_cut].GetName().size())
						{
							string name = this->m_broken_lines[n_surf].m_lines[n_cut].GetName();
							if (i_poligon < m_polySloi[n_surf_poligon].m_poligones[n_cut].Size())
							{
								m_polySloi[n_surf_poligon].m_poligones[n_cut][i_poligon].SetName(name);
							}
						}
						if (i_poligon < m_polySloi[n_surf_poligon].m_poligones[n_cut].Size())
						{
							m_polySloi[n_surf_poligon].m_poligones[n_cut][i_poligon].id_umpoz = m_polySloi[n_surf_poligon].id_umpoz;

							m_polySloi[n_surf_poligon].m_poligones[n_cut][i_poligon].InitDoc(m_pSurfDoc);
							m_polySloi[n_surf_poligon].m_poligones[n_cut][i_poligon].SetColor(this->m_broken_lines[n_surf].m_lines[n_cut].GetColor());
							m_polySloi[n_surf_poligon].m_poligones[n_cut][i_poligon].SetAlpha(50);
						}

						bool not_reversed_line = true;
						int i1_1, i1_2;
						bool 
							add_first_pointsDrillSloi = false,
							add_second_pointsDrillSloi = false;

						GetWellLineIntersection(
							n_cut, n_surf, 
							i_start, i_finish,
							not_reversed_line,
							i1_1, i1_2, 
							add_first_pointsDrillSloi,
							add_second_pointsDrillSloi);

						if (podoshva == 1) // если текущая линия - подошва
						{
							if (add_first_pointsDrillSloi)
							{
								// добавляем в полигон точку пересечения текущей линии с первой слева вспомогательной линией
								AddPointToPoligon_Back(m_pointsDrillSloi_right[n_cut][n_surf].m_vdPoints[0],
									n_cut, n_surf_poligon, i_poligon);
							}

							if (add_first_pointsDrillSloi || add_second_pointsDrillSloi)
							{
								int added = 0;
								bool force_reverse = !not_reversed_line;
								// добавляем в полигон точки текущей линии, попавшие между двумя вспомогательными вертикальными линиями
								AddLineToPoligon_Back(force_reverse, n_cut, n_surf, i1_1, i1_2, n_cut, n_surf_poligon, i_poligon, added);
							}


							if (add_second_pointsDrillSloi)
							{
								// добавляем в полигон точку пересечения текущей линии со второй вспомогательной линией
								AddPointToPoligon_Back(m_pointsDrillSloi_left[n_cut+1][n_surf].m_vdPoints[0],
									n_cut, n_surf_poligon, i_poligon);
							}
						}
						else //кровля
						{
							if (add_first_pointsDrillSloi && add_second_pointsDrillSloi)//если кровля вся между скважинами
							{
								// добавляем в полигон точку пересечения текущей линии с первой слева вспомогательной линией
								AddPointToPoligon_Back(m_pointsDrillSloi_right[n_cut][n_surf].m_vdPoints[0],
									n_cut, n_surf_poligon, i_poligon);
					
								int added = 0;
								// добавляем в полигон точки текущей линии, попавшие между двумя вспомогательными вертикальными линиями
								AddLineToPoligon_Back(n_cut, n_surf, i1_1, i1_2, n_cut, n_surf_poligon, i_poligon, added);
					
								// добавляем в полигон точку пересечения текущей линии со второй вспомогательной линией
								AddPointToPoligon_Back(m_pointsDrillSloi_left[n_cut+1][n_surf].m_vdPoints[0],
									n_cut, n_surf_poligon, i_poligon);
							}
						}

						bool like_podoshva = 
							(podoshva == 1) // если текущая линия - подошва
							||
							(
								(podoshva != 1) //кровля
								&&
								(add_first_pointsDrillSloi && add_second_pointsDrillSloi)//если кровля вся между скважинами
							);

						// номера точек пересечения, которые уже вошли в состав текущего полигона
						int n_slips = 0, n_slips_current = 0, n_slips_under_linza = 0;
						std::map<int, int> slips;
						int last_added_slip = -1;

						int n_surf_do_not_add = n_surf;



						bool _add_first_pointsDrillSloi = add_first_pointsDrillSloi,
							_add_second_pointsDrillSloi = add_second_pointsDrillSloi;


						int _n_surf = n_surf;
						int n_surf_up_left  = -1;
						bool found_above_right_n_cut = false;

						bool to_walk = false;
						bool was_linza = false;
						do
						{
							int one_right_n_cut = 1;
							found_above_right_n_cut = false;

							int _i_surf_left, _i1_left;
							LeftWalk(one_right_n_cut, 
								found_above_right_n_cut, 
								slips, last_added_slip,
								_i_surf_left, _i1_left,
								n_cut, _n_surf, i_poligon, n_surf_poligon, n_surf_do_not_add,
								like_podoshva, _add_first_pointsDrillSloi);

							n_surf_up_left = _n_surf - one_right_n_cut;

							to_walk = false;
							if (last_added_slip > -1 
								&& this->m_SurfLineIntersectPoints[n_cut][last_added_slip].with_krovlja
								&& this->m_broken_lines[_i_surf_left].podoshva == 2)
							{
								_n_surf = _i_surf_left;
								int _VisiblePartsNumber = GetLineVisiblePartsNumber(n_cut, _n_surf);
								for (int _i_visible_part = 0; _i_visible_part < _VisiblePartsNumber; _i_visible_part++)
								{
									int _i_start, _i_finish;
									if (GetLineVisiblePart(n_cut, _n_surf, 
														_i_visible_part,
														_i_start, _i_finish))
									{

										bool _not_reversed_line;
										int _i1_1, _i1_2;

										GetWellLineIntersection(
											n_cut, _n_surf, 
											_i_start, _i_finish,
											_not_reversed_line,
											_i1_1, _i1_2, 
											_add_first_pointsDrillSloi,
											_add_second_pointsDrillSloi);

										if (_add_first_pointsDrillSloi)
										{
											int added = 0;
											bool _force_reverse = _not_reversed_line;
											// добавляем в полигон точки текущей линии, попавшие между двумя вспомогательными вертикальными линиями
											AddLineToPoligon_Front(_force_reverse, n_cut, _n_surf, _i1_1, _i1_2, n_cut, n_surf_poligon, i_poligon, added);

											to_walk = true;
											was_linza = true;

											int n = calc_n_slips(slips);
											n_slips_under_linza += n - n_slips_current;
											n_slips_current = n;
										}
									}
								}
							}
						}
						while (to_walk);


						// erase last added slip
						if (last_added_slip > -1)
						{
							slips.erase(last_added_slip);							
							++n_slips;	
						}
						n_slips_current = calc_n_slips(slips);

						_n_surf = n_surf;

						int n_surf_up_right  = -1;
						bool found_above_left_n_cut_plus_1 = false;
						do
						{
							int one_left_n_cut_plus_1 = 1;
							found_above_left_n_cut_plus_1 = false;

							int _i_surf_right, _i1_right;
							RightWalk(one_left_n_cut_plus_1, 
								found_above_left_n_cut_plus_1, 
								slips, last_added_slip,
								_i_surf_right, _i1_right,
								n_cut, _n_surf, i_poligon, n_surf_poligon, n_surf_do_not_add,
								like_podoshva, _add_second_pointsDrillSloi);

							n_surf_up_right = _n_surf - one_left_n_cut_plus_1;
							
 							
							to_walk = false;
							if (last_added_slip > -1 
								&& this->m_SurfLineIntersectPoints[n_cut][last_added_slip].with_krovlja
								&& this->m_broken_lines[_i_surf_right].podoshva == 2)
							{
								_n_surf = _i_surf_right;
								int _VisiblePartsNumber = GetLineVisiblePartsNumber(n_cut, _n_surf);
								for (int _i_visible_part = 0; _i_visible_part < _VisiblePartsNumber; _i_visible_part++)
								{
									int _i_start, _i_finish;
									if (GetLineVisiblePart(n_cut, _n_surf, 
														_i_visible_part,
														_i_start, _i_finish))
									{

										bool _not_reversed_line;
										int _i1_1, _i1_2;

										GetWellLineIntersection(
											n_cut, _n_surf, 
											_i_start, _i_finish,
											_not_reversed_line,
											_i1_1, _i1_2, 
											_add_first_pointsDrillSloi,
											_add_second_pointsDrillSloi);

										if (_add_second_pointsDrillSloi)
										{
											int added = 0;
											bool _force_reverse = !_not_reversed_line;
											// добавляем в полигон точки текущей линии, попавшие между двумя вспомогательными вертикальными линиями
											AddLineToPoligon_Back(_force_reverse, n_cut, _n_surf, _i1_1, _i1_2, n_cut, n_surf_poligon, i_poligon, added);

											to_walk = true;
											was_linza = true;

											int n = calc_n_slips(slips);
											n_slips_under_linza += n - n_slips_current;
											n_slips_current = n;
										}
									}
								}
							}
						}
 						while (to_walk);
                       
						MiddleWalk(i1_1, i1_2,
							slips, last_added_slip,
							n_cut, n_surf, i_poligon, n_surf_poligon, n_surf_do_not_add,
							add_first_pointsDrillSloi, add_second_pointsDrillSloi);

						//n_slips += slips.size();
						for(std::map<int,int>::iterator fnd = slips.begin();
							fnd != slips.end(); ++fnd)
						{
							if((*fnd).second != -2)
							{
								++n_slips;
							}
						}

						// если с обеими вспомогательными линиями имеет пересечение одна и та же вышележащая линия
						if (//add_first_pointsDrillSloi && add_second_pointsDrillSloi && // исключаем условие на случай если текущая линия не дотянулась до хоть одной из вертикальных вспомогательных линий 
							like_podoshva && 
							n_surf_up_left > -1 && n_surf_up_right > -1 &&
							found_above_right_n_cut && found_above_left_n_cut_plus_1
							&& n_surf_up_left == n_surf_up_right
							&& (n_surf_up_left == n_surf - one || was_linza ) //  и если она - ближайшая к текущей вышележащая линия
							&& n_slips - n_slips_under_linza == 0 ) // и если не были добавлены линии с помощью AddingLineToPoligon()
						{
							int added = 0;
							// добавляем в полигон точки вышележащей линии, попавшие между двумя вспомогательными вертикальными линиями
							AddLineToPoligon_Back(n_cut, n_surf_up_left, 
								m_pointsDrillSloi_right[n_cut][n_surf_up_left].id_point,
								m_pointsDrillSloi_left[n_cut+1][n_surf_up_right].id_point,
								n_cut, n_surf_poligon, i_poligon, added);
						}
					}
				}
			}
#else

			
			if (podoshva == 1) // если текущая линия - подошва
			{
				if (m_pointsDrillSloi_right[n_cut][n_surf].GetPointsNumber() &&
                    m_pointsDrillSloi_left[n_cut+1][n_surf].GetPointsNumber())
					// если текущая линия пересекается с обеими вспомогательными линиями
				{
					// добавляем в полигон точку пересечения текущей линии с первой слева вспомогательной линией
					AddPointToPoligon_Back(m_pointsDrillSloi_right[n_cut][n_surf].m_vdPoints[0],
						n_cut, n_surf_poligon);

					// добавляем в полигон точки текущей линии, попавшие между двумя вспомогательными вертикальными линиями
					AddLineToPoligon_Back(n_cut, n_surf, 
						m_pointsDrillSloi_right[n_cut][n_surf].id_point,
						m_pointsDrillSloi_left[n_cut+1][n_surf].id_point,
						n_cut, n_surf_poligon);

					// добавляем в полигон точку пересечения текущей линии со второй вспомогательной линией
					AddPointToPoligon_Back(m_pointsDrillSloi_left[n_cut+1][n_surf].m_vdPoints[0],
						n_cut, n_surf_poligon);



					// ищем какая из вышележащих линий имеет точку пересечения с первой слева вспомогательной вертикальной линией
					int one_right_n_cut = 1;
					bool found_above_right_n_cut = false;
					while (!found_above_right_n_cut && one_right_n_cut <= n_surf)
					{
						found_above_right_n_cut = 
							(m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].GetPointsNumber() > 0);
						if (!found_above_right_n_cut)
							one_right_n_cut++;
					}

					// ищем какая из вышележаших линий имеет точку пересечения со второй вспомогательной вертикальной линией
					int one_left_n_cut_plus_1 = 1;
					bool found_above_left_n_cut_plus_1 = false;
					while (!found_above_left_n_cut_plus_1 && one_left_n_cut_plus_1 <= n_surf)
					{
						found_above_left_n_cut_plus_1 = 
							(m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].GetPointsNumber() > 0);
						if (!found_above_left_n_cut_plus_1)
							one_left_n_cut_plus_1++;
					}

					// если с обеими вспомогательными линиями имеет пересечение одна и та же вышележащая линия
					if (found_above_right_n_cut && found_above_left_n_cut_plus_1
						&& one_right_n_cut == one_left_n_cut_plus_1
						&& one_right_n_cut == one) //  и если она - ближайшая к текущей вышележащая линия
					{
						// добавляем в полигон точку пересечения вышележащей линии со второй вспомогательной линией
						AddPointToPoligon_Back(m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].m_vdPoints[0],
							n_cut, n_surf_poligon);

						// добавляем в полигон точки вышележащей линии, попавшие между двумя вспомогательными вертикальными линиями
						AddLineToPoligon_Back(n_cut, n_surf-one_right_n_cut, 
							m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].id_point,
							m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].id_point,
							n_cut, n_surf_poligon);

						// добавляем в полигон точку пересечения вышележащей линии с первой слева вспомогательной линией
						AddPointToPoligon_Back(m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].m_vdPoints[0],
							n_cut, n_surf_poligon);

					}
					// если ближайшая к текущей вышележащая линия 
					// пересекается со второй вспомогательной вертикальной линией 
					else if (found_above_right_n_cut && found_above_left_n_cut_plus_1
						&& one_right_n_cut > one_left_n_cut_plus_1) 
					{
						// добавляем в полигон точку пересечения вышележащей линии со второй вспомогательной линией
						AddPointToPoligon_Back(m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].m_vdPoints[0],
							n_cut, n_surf_poligon);

						// добавляем в полигон точки вышележащей линии, начиная от 
						// второй вспомогательной линии
						if (m_pointsDrillSloi[n_cut+1][n_surf-one_left_n_cut_plus_1].GetPointsNumber() > 0)
						{
							bool nearest_part_from_the_point = false;
							CPoint3 pt = m_pointsDrillSloi[n_cut+1][n_surf-one_left_n_cut_plus_1].GetFirstDocumentPoint();
							bool add_part_from_begin_of_line = 
								AddLineToPoligon_Back(n_cut, n_surf-one_left_n_cut_plus_1, 
									 m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].id_point, 
									 nearest_part_from_the_point, pt,
									 n_cut, n_surf_poligon);				

							// берём две крайние точки вышележащей линии 
							if (m_broken_lines[n_surf-one_left_n_cut_plus_1].m_lines[n_cut].GetPointsNumber() > 1)
							{
                                CPoint3 pt_0, pt_1;
								if (add_part_from_begin_of_line)
								{
                                    pt_0 = m_broken_lines[n_surf-one_left_n_cut_plus_1].m_lines[n_cut].GetFirstDocumentPoint();
									pt_1 = m_broken_lines[n_surf-one_left_n_cut_plus_1].m_lines[n_cut].GetSecondDocumentPoint();
								}
								else
								{
                                    pt_0 = m_broken_lines[n_surf-one_left_n_cut_plus_1].m_lines[n_cut].GetPreLastDocumentPoint();
									pt_1 = m_broken_lines[n_surf-one_left_n_cut_plus_1].m_lines[n_cut].GetLastDocumentPoint();
								}

								// ищем пересечение с ещё более вышележащей линией, выходящей
								// на противоположную вспомогательную вертикальную линию
						
								CPoint3 pti; int i1, i2;
								if (this->m_broken_lines[n_surf-one_right_n_cut].m_lines[n_cut].FindIntersection(this->m_profile3D, 
									pt_0, pt_1, pti, i1, i2))
								{
									// добавляем в полигон эту точку пересечения
									AddPointToPoligon_Back(pti,
										n_cut, n_surf_poligon);

									AddLineToPoligon_Back(n_cut, n_surf-one_right_n_cut, 
										m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].id_point, i1, 
										n_cut, n_surf_poligon);	

									AddPointToPoligon_Back(m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].m_vdPoints[0],
										n_cut, n_surf_poligon);

								}
							}
						}
					}
					// если ближайшая к текущей вышележащая линия 
					// пересекается с первой слева вспомогательной вертикальной линией 
					else if (found_above_right_n_cut && found_above_left_n_cut_plus_1
						&& one_right_n_cut < one_left_n_cut_plus_1) 
					{
						// добавляем в полигон точку пересечения вышележащей линии с первой слева вспомогательной линией
						AddPointToPoligon_Front(m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].m_vdPoints[0],
							n_cut, n_surf_poligon);

						// добавляем в полигон точки вышележащей линии, начиная от
						//первой слева вспомогательной линиии
						if (m_pointsDrillSloi[n_cut][n_surf-one_right_n_cut].GetPointsNumber() > 0)
						{
							bool nearest_part_from_the_point = false;
							CPoint3 pt = m_pointsDrillSloi[n_cut][n_surf-one_right_n_cut].GetFirstDocumentPoint();
							bool add_part_from_begin_of_line = 
								AddLineToPoligon_Front(n_cut, n_surf-one_right_n_cut, 
									 m_pointsDrillSloi_right[n_cut][n_surf-one_right_n_cut].id_point, 
									 nearest_part_from_the_point, pt,
									 n_cut, n_surf_poligon);				

							// берём две крайние точки вышележащей линии 
							if (m_broken_lines[n_surf-one_right_n_cut].m_lines[n_cut].GetPointsNumber() > 1)
							{
                                CPoint3 pt_0, pt_1;
								if (add_part_from_begin_of_line)
								{
                                    pt_0 = m_broken_lines[n_surf-one_right_n_cut].m_lines[n_cut].GetFirstDocumentPoint();
									pt_1 = m_broken_lines[n_surf-one_right_n_cut].m_lines[n_cut].GetSecondDocumentPoint();
								}
								else
								{
                                    pt_0 = m_broken_lines[n_surf-one_right_n_cut].m_lines[n_cut].GetPreLastDocumentPoint();
									pt_1 = m_broken_lines[n_surf-one_right_n_cut].m_lines[n_cut].GetLastDocumentPoint();
								}

								// ищем пересечение с ещё более вышележащей линией, выходящей
								// на противоположную вспомогательную вертикальную линию
						
								CPoint3 pti; int i1, i2;
								if (this->m_broken_lines[n_surf-one_left_n_cut_plus_1].m_lines[n_cut].FindIntersection(this->m_profile3D, 
									pt_0, pt_1, pti, i1, i2))
								{
									// добавляем в полигон эту точку пересечения
									AddPointToPoligon_Front(pti,
										n_cut, n_surf_poligon);

									AddLineToPoligon_Front(n_cut, n_surf-one_left_n_cut_plus_1, 
										m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].id_point, i1, 
										n_cut, n_surf_poligon);	

									AddPointToPoligon_Front(m_pointsDrillSloi_left[n_cut+1][n_surf-one_left_n_cut_plus_1].m_vdPoints[0],
										n_cut, n_surf_poligon);

								}
							}
						}
					}
				}
			}
#endif
#else

			//прямой порядок обхода - против часовой стрелке
			//*****************************************************************
			vo[0].n_cut_point	= n_cut;
			vo[0].n_surf_point	= n_surf;
			vo[0].n_cut_line	= n_cut;
			vo[0].n_surf_line	= n_surf;
			//-----------------------------------------------------------
			vo[1].n_cut_point	= n_cut+1;
			vo[1].n_surf_point	= n_surf;
			vo[1].n_cut_line	= -1;
			vo[1].n_surf_line	= -1;
			//-----------------------------------------------------------
			vo[2].n_cut_point	= n_cut+1;
			vo[2].n_surf_point	= n_surf-one;
			vo[2].n_cut_line	= n_cut;
			vo[2].n_surf_line	= n_surf-one;
			//-----------------------------------------------------------
			vo[3].n_cut_point	= n_cut;
			vo[3].n_surf_point	= n_surf-one;
			vo[3].n_cut_line	= -1;
			vo[3].n_surf_line	= -1;
			//*****************************************************************



			//считаем количество опорных точек на скважинах
			int n_pds = 0;
			for(itr = vo.begin(); itr != vo.end(); itr++)
			{
				if (this->m_pointsDrillSloi[(*itr).n_cut_point][(*itr).n_surf_point].GetPointsNumber())
				{
					n_pds++;
				}			
			}
			switch (n_pds)
			{
			case 3:
				{
					//сперва ищем опорную точку, которой не хватает
					//пустую - потому что она выклинилась
					
					int n_cut_point_empty = -1;
					int n_surf_point_empty = -1;//номер выклинивающейся поверхности
					for (itr = vo.begin(); itr != vo.end(); itr++) 
					{
						if (!this->m_pointsDrillSloi[(*itr).n_cut_point][(*itr).n_surf_point].GetPointsNumber())
						{
							n_cut_point_empty = (*itr).n_cut_point;
							n_surf_point_empty = (*itr).n_surf_point;

							break;
						}						
					}
					// затем ищем соответствую ей лежащую на одной (выклинивающейся) поверхности полную точку
					
					int n_cut_point_not_empty;
					if (n_cut_point_empty == n_cut)
					{
						// пустая точка слева
						// значит полная справа
						n_cut_point_not_empty = n_cut+1;
					}
					else
					{
						// пустая точка справа
						// значит полная слева
						n_cut_point_not_empty = n_cut;
					}
					if (n_surf_point_empty == n_surf)
					{
						// пустая точка снизу
						// выклинивается верхняя линия полигона
					}
					else
					{
						// пустая точка сверху
						// выклинивается нижняя линия полигона
					}

					if (this->m_pointsDrillSloi[n_cut_point_not_empty][n_surf_point_empty].GetPointsNumber())
					{
						CPoint3 pt_not_empty = this->m_pointsDrillSloi[n_cut_point_not_empty][n_surf_point_empty].GetFirstDocumentPoint();
						CPoint3 
							pt,
							last_line_point,
							first_line_point;
						// исследуем линию, которая находится на выклинивающейся поверхности
						// определяем прямой или обратный порядок линии 

						size_t nel = m_broken_lines[n_surf_point_empty].m_lines[n_cut].GetPointsNumber();
						if (nel > 1)
						{
							first_line_point	= m_broken_lines	[n_surf_point_empty].m_lines[n_cut].GetFirstDocumentPoint();
							last_line_point		= m_broken_lines	[n_surf_point_empty].m_lines[n_cut].GetLastDocumentPoint();
							double distance_to_last  = Distance(pt_not_empty, last_line_point);
							double distance_to_first = Distance(pt_not_empty, first_line_point);
							bool reverse = distance_to_last < distance_to_first;

							// вместо пустой точки мы получили точку на конце линии
							// это точка предшествующая непосредственному выклиниванию
							CPoint3 pt_at_end_of_line = reverse ? first_line_point : last_line_point;
							
							CPoint3 second_line_point	= m_broken_lines	[n_surf_point_empty].m_lines[n_cut].GetDocumentPoint(1);
							CPoint3 pre_last_line_point	= m_broken_lines	[n_surf_point_empty].m_lines[n_cut].GetDocumentPoint(nel-2);
							
							CPoint3 pt_pre_end_of_line = reverse ? second_line_point : pre_last_line_point;

							// если выше и ниже выклинивающейся поверхности 
							// есть другие поверхности
							// с непустыми линиями

							// соседняя верхняя поверхность
							bool have_nearest_above_line = n_surf_point_empty > one - 1 &&
								m_broken_lines[n_surf_point_empty - one].m_lines[n_cut].GetPointsNumber() > 0;

							// соседняя нижняя поверхность
							bool have_nearest_under_line = n_surf_point_empty < m_nSurfs - 1 && 								
								m_broken_lines[n_surf_point_empty + 1].m_lines[n_cut].GetPointsNumber() > 0;


							if (true)
							{
								// сравниваем расстояние от этой точки на конце линии
								// т.е. от точки предшествующей непосредственному выклиниванию
								// до соседней верхней поверхности
								// и до соседней верхней поверхности
								// чтобы определить в какую сторону выклинивается наша поверхность

								Line3D * above_line = have_nearest_above_line ? 
									&m_broken_lines[n_surf_point_empty - one].m_lines[n_cut] : NULL;
								Line3D * under_line = have_nearest_under_line ?
									&m_broken_lines[n_surf_point_empty + 1].m_lines[n_cut] : NULL;

								int imd_in_above_line1;
								int imd_in_under_line1;

								double dist_to_above_line = min_distance_to_line(above_line, pt_at_end_of_line, imd_in_above_line1);
								double dist_to_under_line = min_distance_to_line(under_line, pt_at_end_of_line, imd_in_under_line1);
								
								int imd_in_above_line2 = imd_in_above_line1;
								int imd_in_under_line2 = imd_in_under_line1;

								if (dist_to_above_line < dist_to_under_line)
								{
									// выклинивание наверх
								}
								else
								{
									// выклинивание вниз
								}

								// трёхугольный или пяти угольный полигон???
								if (n_surf_point_empty == n_surf)
								{
									// пустая точка снизу
									// выклинивается нижняя линия полигона
									if (dist_to_above_line < dist_to_under_line)
									{
										// нижняя линия полигона
										// выклинивается наверх
										// трёхугольный полигон
										if (have_nearest_above_line)
										{
											AddPointToPoligon(n_cut_point_not_empty, n_surf - one, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_not_empty, n_surf, 
												n_cut, n_surf_poligon);
											AddLineToPoligon(n_cut, n_surf, 
												n_cut, n_surf_poligon);

											CPoint3 pti; int i1, i2;
											if (above_line && above_line->FindIntersection(this->m_profile3D, 
												pt_pre_end_of_line, pt_at_end_of_line, pti, i1, i2))
											{
												this->AddPointToPoligon(pti, n_cut, n_surf_poligon);
												imd_in_above_line1 = i1;
												imd_in_above_line2 = i2;
											}

											ClosePoligonByLine(n_cut, n_surf - one, imd_in_above_line1, imd_in_above_line2,
												n_cut, n_surf_poligon);
										}
									}
									else
									{
										// нижняя линия полигона
										// выклинивается вниз
										// пяти угольный полигон
										if (have_nearest_under_line)
										{
											AddPointToPoligon(n_cut_point_empty, n_surf + 1, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_empty, n_surf - one, 
												n_cut, n_surf_poligon);
											AddLineToPoligon(n_cut, n_surf - one, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_not_empty, n_surf - one, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_not_empty, n_surf, 
												n_cut, n_surf_poligon);
											AddLineToPoligon(n_cut, n_surf, 
												n_cut, n_surf_poligon);

											CPoint3 pti; int i1, i2;
											if (under_line && under_line->FindIntersection(this->m_profile3D, 
												pt_pre_end_of_line, pt_at_end_of_line, pti, i1, i2))
											{
												this->AddPointToPoligon(pti, n_cut, n_surf_poligon);
												imd_in_under_line1 = i1;
												imd_in_under_line2 = i2;
											}

											ClosePoligonByLine(n_cut, n_surf + 1, imd_in_under_line1, imd_in_under_line2,
												n_cut, n_surf_poligon);
										}
									}
								}
								else
								{
									// n_surf_point_empty == n_surf - one
									// пустая точка сверху
									// выклинивается верхняя линия полигона
									if (dist_to_above_line < dist_to_under_line)
									{
										// верхняя линия полигона
										// выклинивается наверх
										// пяти угольный полигон
										if (have_nearest_above_line)
										{
											AddPointToPoligon(n_cut_point_empty, n_surf_point_empty - one, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_empty, n_surf_point_empty + 1, 
												n_cut, n_surf_poligon);
											AddLineToPoligon(n_cut, n_surf_point_empty + 1, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_not_empty, n_surf_point_empty + 1, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_not_empty, n_surf_point_empty, 
												n_cut, n_surf_poligon);
											AddLineToPoligon(n_cut, n_surf_point_empty, 
												n_cut, n_surf_poligon);

											CPoint3 pti; int i1, i2;
											if (above_line && above_line->FindIntersection(this->m_profile3D, 
												pt_pre_end_of_line, pt_at_end_of_line, pti, i1, i2))
											{
												this->AddPointToPoligon(pti, n_cut, n_surf_poligon);
												imd_in_above_line1 = i1;
												imd_in_above_line2 = i2;
											}

											ClosePoligonByLine(n_cut, n_surf_point_empty - one, imd_in_above_line1, imd_in_above_line2,
												n_cut, n_surf_poligon);
										}

									}
									else
									{
										// верхняя линия полигона
										// выклинивается вниз
										// трёхугольный полигон
										if (have_nearest_under_line)
										{
											AddPointToPoligon(n_cut_point_not_empty, n_surf_point_empty + 1, 
												n_cut, n_surf_poligon);
											AddPointToPoligon(n_cut_point_not_empty, n_surf_point_empty, 
												n_cut, n_surf_poligon);
											AddLineToPoligon(n_cut, n_surf_point_empty, 
												n_cut, n_surf_poligon);

											CPoint3 pti; int i1, i2;
											if (under_line && under_line->FindIntersection(this->m_profile3D, 
												pt_pre_end_of_line, pt_at_end_of_line, pti, i1, i2))
											{
												this->AddPointToPoligon(pti, n_cut, n_surf_poligon);
												imd_in_under_line1 = i1;
												imd_in_under_line2 = i2;
											}

											ClosePoligonByLine(n_cut, n_surf_point_empty + 1, imd_in_under_line1, imd_in_under_line2,
												n_cut, n_surf_poligon);
										}
									}
								}
							}
						}
					}
				}
				break;
			case 4:
				{
					itr = vo.begin();
					int i = 0;
					while(itr != vo.end() && 
						!this->m_pointsDrillSloi[(*itr).n_cut_point][(*itr).n_surf_point].GetPointsNumber())
					{
						//WriteRaporto("itr++\n");
						itr++;
					}
					if (itr != vo.end())
					{
						for( i = 0; i < 4; i++, itr++)
						{
							if (itr == vo.end())
								itr = vo.begin();

							AddPointToPoligon((*itr).n_cut_point, (*itr).n_surf_point, 
								n_cut, n_surf_poligon);
							AddLineToPoligon((*itr).n_cut_line, (*itr).n_surf_line, 
								n_cut, n_surf_poligon);

						}
					}
				}
				break;
			}
#endif
		}
#if USE_UNVISIBLE_CUTTING
		m_polySloi[n_surf_poligon].m_poligones_ObjectList.Init_std_vector_Vector(m_polySloi[n_surf_poligon].m_poligones, &this->m_polySloi[n_surf_poligon]);
#else
		m_polySloi[n_surf_poligon].m_poligones_ObjectList.Init1(m_polySloi[n_surf_poligon].m_poligones, &this->m_polySloi[n_surf_poligon]);
#endif
	}

}


bool BrokenPlane3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	int  n_drill;

	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		if(m_drills[n_drill].UpdateExtremums())
		{
			vptmax.push_back(m_drills[n_drill].GetMax());
			vptmin.push_back(m_drills[n_drill].GetMin());
		}
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void BrokenPlane3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	int n_cut, n_surf, n_drill, n_fault, n_catch;
	for (n_cut = 0; n_cut < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_cut][n_surf].CutAndDisvisible(positive, a, b, c, d);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_cut][n_surf].CutAndDisvisible(positive, a, b, c, d);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_cut][n_surf].CutAndDisvisible(positive, a, b, c, d);
		}
	}




	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].CutAndDisvisible(positive, a, b, c, d);
		}
	}

	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].CutAndDisvisible(positive, a, b, c, d);
		}
	}

	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].CutAndDisvisible(positive, a, b, c, d);
		}
	}

	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].CutAndDisvisible(positive, a, b, c, d);
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].CutAndDisvisible(positive, a, b, c, d);
		}
#endif
	}
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].CutAndDisvisible(positive, a, b, c, d);
	}
}
void BrokenPlane3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	int n_cut, n_surf, n_drill, n_fault, n_catch;

	for (n_cut = 0; n_cut < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_cut][n_surf].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_cut][n_surf].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_cut][n_surf].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}




	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}

	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}

	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}

	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].CutXYZandDisvisible(subcube_number, X, Y, Z);
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
#endif
	}
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].CutXYZandDisvisible(subcube_number, X, Y, Z);
	}
}
void BrokenPlane3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	int n_cut, n_surf, n_drill, n_fault, n_catch;

	for (n_cut = 0; n_cut < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_cut][n_surf].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_cut][n_surf].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_cut][n_surf].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}



	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}

	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}

	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}

	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].Zoom(
					zoomX,zoomY,zoomZ, 
					x_mean,y_mean,z_mean
					);
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
#endif
	}
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
	}
}

void BrokenPlane3D::clear()
{
	int n_cut, n_surf, n_drill, n_fault, n_catch;
	for (n_cut = 0; n_cut < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_pointsDrillSloi[n_cut].clear();
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_pointsDrillSloi_right[n_cut].clear();
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_pointsDrillSloi_left[n_cut].clear();
	}


	/*m_pointsDrillSloi.clear();*/

	for (n_surf = 0; n_surf < this->m_broken_lines.Size(); n_surf++)
	{
		this->m_broken_lines[n_surf].m_lines.clear();
	}
	this->m_broken_lines.clear();
	m_nSurfs = 0;

	for (n_fault = 0; n_fault < this->m_broken_fault_lines.Size(); n_fault++)
	{
		this->m_broken_fault_lines[n_fault].m_lines.clear();
	}
	m_nFaults = 0;

	for (n_catch = 0; n_catch < this->m_broken_catch_lines.Size(); n_catch++)
	{
		this->m_broken_catch_lines[n_catch].m_lines.clear();
	}
	m_broken_catch_lines.clear();
	m_nCatches = 0;

	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
		m_polySloi[n_surf].m_poligones.clear();
	}
	m_polySloi.clear();

//	m_drills.clear();
}
void BrokenPlane3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	int n_cut, n_surf, n_drill, n_fault, n_catch;
	for (n_cut = 0; n_cut < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_cut][n_surf].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_cut][n_surf].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_cut][n_surf].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}



	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		this->m_broken_lines[n_surf].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}

	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		this->m_broken_fault_lines[n_fault].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}

	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		this->m_broken_catch_lines[n_catch].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}


	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
		m_polySloi[n_surf].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
#endif
	}
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
	}

	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}

}
void BrokenPlane3D::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	int n_cut, n_surf, n_drill, n_fault, n_catch;
	for (n_cut = 0; n_cut < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_cut][n_surf].SetLayer(layer);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_cut][n_surf].SetLayer(layer);
		}
	}

	for (n_cut = 0; n_cut < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_cut].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_cut][n_surf].SetLayer(layer);
		}
	}


	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		this->m_broken_lines[n_surf].SetLayer(layer);
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].SetLayer(layer);
		}
	}

	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		this->m_broken_fault_lines[n_fault].SetLayer(layer);
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].SetLayer(layer);
		}
	}

	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		this->m_broken_catch_lines[n_catch].SetLayer(layer);
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].SetLayer(layer);
		}
	}


	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
		m_polySloi[n_surf].SetLayer(layer);
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].SetLayer(layer);
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].SetLayer(layer);
		}
#endif
	}
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].SetLayer(layer);
	}
}
HTREEITEM BrokenPlane3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	sprintf(szItemText, "BrokenPlane");
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	{
		int n_cut, n_surf, n_drill, n_point;

		// Add the item to the tree-view control

		sprintf(szItemText, "Points");
		pObject = dynamic_cast<Object *> (&this->m_pointsDrillSloi_ObjectList);
		HTREEITEM h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		for (n_point = 0; n_point < this->m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
		{
			for (n_surf = 0; n_surf < this->m_pointsDrillSloi[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
			{
				char s[1024]; sprintf(s, "n_point=%d n_surf=%d ", n_point, n_surf);
				this->m_pointsDrillSloi[n_point][n_surf].AddItem_ToTree(hwndTV, h3, s);
			}
		}

		sprintf(szItemText, "Points_left");
		pObject = dynamic_cast<Object *> (&this->m_pointsDrillSloi_left_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		for (n_point = 0; n_point < this->m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
		{
			for (n_surf = 0; n_surf < this->m_pointsDrillSloi_left[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
			{
				char s[1024]; sprintf(s, "n_point=%d n_surf=%d ", n_point, n_surf);
				this->m_pointsDrillSloi_left[n_point][n_surf].AddItem_ToTree(hwndTV, h3, s);
			}
		}

		sprintf(szItemText, "Points_right");
		pObject = dynamic_cast<Object *> (&this->m_pointsDrillSloi_right_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		for (n_point = 0; n_point < this->m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
		{
			for (n_surf = 0; n_surf < this->m_pointsDrillSloi_right[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
			{
				char s[1024]; sprintf(s, "n_point=%d n_surf=%d ", n_point, n_surf);
				this->m_pointsDrillSloi_right[n_point][n_surf].AddItem_ToTree(hwndTV, h3, s);
			}
		}

		sprintf(szItemText, "SurfLineIntersectPoint");
		pObject = dynamic_cast<Object *> (&this->m_SurfLineIntersectPoints_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		for (n_cut = 0; n_cut < this->m_SurfLineIntersectPoints.size(); n_cut++)
		{
			for (n_point = 0; n_point < this->m_SurfLineIntersectPoints[n_cut].size(); n_point++)
			{
				char s[1024]; sprintf(s, "n_cut=%2d unv=%d dst=%d back=%d i_surf1=%2d i1_1=%4d i2_1=%4d i_surf2=%2d i1_2=%4d i2_2=%4d ", 

					n_cut,					
					this->m_SurfLineIntersectPoints[n_cut][n_point].unvisibles,
					this->m_SurfLineIntersectPoints[n_cut][n_point].dst_to_vis,
					this->m_SurfLineIntersectPoints[n_cut][n_point].back,

					this->m_SurfLineIntersectPoints[n_cut][n_point].i_surf1,
					this->m_SurfLineIntersectPoints[n_cut][n_point].i1_1,
					this->m_SurfLineIntersectPoints[n_cut][n_point].i2_1,

					this->m_SurfLineIntersectPoints[n_cut][n_point].i_surf2,
					this->m_SurfLineIntersectPoints[n_cut][n_point].i1_2,
					this->m_SurfLineIntersectPoints[n_cut][n_point].i2_2
					);
				this->m_SurfLineIntersectPoints[n_cut][n_point].point.AddItem_ToTree(hwndTV, h3, s);
			}
		}


		// Add the item to the tree-view control
		sprintf(szItemText, "Broken Lines faults");
		pObject = dynamic_cast<Object *> (&this->m_broken_fault_lines_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);

		for (n_surf = 0; n_surf < this->m_broken_fault_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			this->m_broken_fault_lines[n_surf].AddItem_ToTree(hwndTV, h3);
		}	

		// Add the item to the tree-view control
		sprintf(szItemText, "Broken Lines catches");
		pObject = dynamic_cast<Object *> (&this->m_broken_catch_lines_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);

		for (n_surf = 0; n_surf < this->m_broken_catch_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			this->m_broken_catch_lines[n_surf].AddItem_ToTree(hwndTV, h3);
		}	


		// Add the item to the tree-view control
		sprintf(szItemText, "Broken Lines Sloi");
		pObject = dynamic_cast<Object *> (&this->m_broken_lines_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);

		for (n_surf = 0; n_surf < this->m_broken_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			this->m_broken_lines[n_surf].AddItem_ToTree(hwndTV, h3);
		}
		// Add the item to the tree-view control
		sprintf(szItemText, "Broken Polygones Sloi");
		pObject = dynamic_cast<Object *> (&this->m_polySloi_ObjectList);
		//pObject->m_bChecked = false;
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);

		for (n_surf = 0; n_surf < this->m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			this->m_polySloi[n_surf].AddItem_ToTree(hwndTV, h3);
		}

		// Add the item to the tree-view control
		sprintf(szItemText, "Drills");
		pObject = dynamic_cast<Object *> (&this->m_drills_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		for (n_drill = 0; n_drill < this->m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
		{
			// Add the item to the tree-view control
			sprintf(szItemText, "n_drill = %d ", n_drill);			
			Object * pObject = dynamic_cast<Object *> (&this->m_drills[n_drill]);
			// Add the item to the tree-view control. 
			AddItemToTree(hwndTV, szItemText, pObject, h3); 
		}

		// Add the item to the tree-view control
		sprintf(szItemText, "Drills_left_line");
		pObject = dynamic_cast<Object *> (&this->m_drills_line_left_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		for (n_drill = 0; n_drill < this->m_drills_line_left.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
		{
			// Add the item to the tree-view control
			sprintf(szItemText, "n_drill = %d ", n_drill);			
			Object * pObject = dynamic_cast<Object *> (&this->m_drills_line_left[n_drill]);
			// Add the item to the tree-view control. 
			AddItemToTree(hwndTV, szItemText, pObject, h3); 
		}

		// Add the item to the tree-view control
		sprintf(szItemText, "Drills_right_line");
		pObject = dynamic_cast<Object *> (&this->m_drills_line_right_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		for (n_drill = 0; n_drill < this->m_drills_line_right.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
		{
			// Add the item to the tree-view control
			sprintf(szItemText, "n_drill = %d ", n_drill);			
			Object * pObject = dynamic_cast<Object *> (&this->m_drills_line_right[n_drill]);
			// Add the item to the tree-view control. 
			AddItemToTree(hwndTV, szItemText, pObject, h3); 
		}



	}
	return h2;
}
void BrokenPlane3D::Draw()
{
	int n_cut, n_surf, n_drill, n_point, n_fault, n_catch;
	for (n_point = 0; n_point < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_point][n_surf].Draw();
		}
	}

	for (n_point = 0; n_point < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_point][n_surf].Draw();
		}
	}

	for (n_point = 0; n_point < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_point][n_surf].Draw();
		}
	}



	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].Draw();
		}
	}	
	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].Draw();
		}
	}

	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].Draw();
		}
	}
#if 1
	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].Draw();
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].Draw();
		}
#endif
	}
#endif
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].Draw();
	}
}
void BrokenPlane3D::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	int n_cut, n_surf, n_drill, n_point, n_fault, n_catch;

	for (n_point = 0; n_point < m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi[n_point][n_surf].ReDraw();
		}
	}

	for (n_point = 0; n_point < m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_right[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_right[n_point][n_surf].ReDraw();
		}
	}

	for (n_point = 0; n_point < m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_pointsDrillSloi_left[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			m_pointsDrillSloi_left[n_point][n_surf].ReDraw();
		}
	}




	for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_lines[n_surf].m_lines[n_cut].ReDraw();
		}
	}	
	for (n_fault = 0; n_fault < m_nFaults; n_fault++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_fault_lines[n_fault].m_lines[n_cut].ReDraw();
		}
	}
	for (n_catch = 0; n_catch < m_nCatches; n_catch++)
	{
		for (n_cut = 0; n_cut < m_nCuts; n_cut++)
		{
			this->m_broken_catch_lines[n_catch].m_lines[n_cut].ReDraw();
		}
	}

#if 1

	for (n_surf = 0; n_surf < m_polySloi.PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
	{
#if USE_UNVISIBLE_CUTTING
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.size(); n_cut++)
		{
			for (size_t i = 0; i < m_polySloi[n_surf].m_poligones[n_cut].Size(); i++)
			{
				m_polySloi[n_surf].m_poligones[n_cut][i].ReDraw();
			}
		}
#else
		for (n_cut = 0; n_cut < m_polySloi[n_surf].m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
		{
			m_polySloi[n_surf].m_poligones[n_cut].ReDraw();
		}
#endif
	}
#endif
	for (n_drill = 0; n_drill < m_drills.PLANE_MEMBERS_VECTOR_SIZE(); n_drill++)
	{
		m_drills[n_drill].ReDraw();
	}
}
size_t BrokenPlane3D::GetPointsNumber()
{
	return m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE();
}


//extern HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex);

COleSafeArray MakeVerticesList(short export_coordinate_type, vector<CPoint3> & vpt3, double v_scale, double g_scale)
{
	size_t nPoints = vpt3.size();
	COleSafeArray myOleSafeVerticesList;
	double* pOriginalVertices = new double[3*nPoints];
	for (size_t i = 0; i < nPoints; i++)
	{
		//pOriginalVertices[3*i + 0] = g_scale * vpt2[i].x;//x
		//pOriginalVertices[3*i + 1] = v_scale * vpt2[i].y;//y
		switch(export_coordinate_type)
		{
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				//pOriginalVertices[3*i + 0] = g_scale * vpt2[i].x;//x
				//pOriginalVertices[3*i + 1] = v_scale * vpt2[i].y;//y
			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{
				pOriginalVertices[3*i + 0] = g_scale * vpt3[i].y;//x
				pOriginalVertices[3*i + 1] = v_scale * vpt3[i].z;//y
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				pOriginalVertices[3*i + 0] = g_scale * vpt3[i].x;//x
				pOriginalVertices[3*i + 1] = v_scale * vpt3[i].z;//y
			}
			break;
		}
		pOriginalVertices[3*i + 2] = 0;
	}
	myOleSafeVerticesList.CreateOneDim(VT_R8, 3*nPoints, pOriginalVertices); 
	delete[] pOriginalVertices;
	return myOleSafeVerticesList;
}
COleSafeArray MakeVerticesList(vector<CPoint2> & vpt2, double v_scale, double g_scale)
{
	size_t nPoints = vpt2.size();
	COleSafeArray myOleSafeVerticesList;
	double* pOriginalVertices = new double[3*nPoints];
	for (size_t i = 0; i < nPoints; i++)
	{
		pOriginalVertices[3*i + 0] = g_scale * vpt2[i].x;//x
		pOriginalVertices[3*i + 1] = v_scale * vpt2[i].y;//y
		pOriginalVertices[3*i + 2] = 0;
	}
	myOleSafeVerticesList.CreateOneDim(VT_R8, 3*nPoints, pOriginalVertices); 
	delete[] pOriginalVertices;
	return myOleSafeVerticesList;
}
#include <dime/Layer.h>
enum PatternType
{
	//The PatternType constant values are as follows:
	acHatchPatternTypePredefined = 1,
	//Selects the pattern name from those defined in the acad.pat file.
	acHatchPatternTypeUserDefined,
	//Defines a pattern of lines using the current linetype.
	acHatchPatternTypeCustomDefined
	//Selects the pattern name from a PAT other than the acad.pat file.
};
/*
acad.pat
;;
;;WenGeo
;;
*alevrolit
0, 0,1, 0,2
60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547
120,0,0,3.4641,2,1.1547,-4.6188,1.1547
60 ,3.4641,0,3.4641,2,-6.6282,.3
120,3.4641,0,3.4641,2,.2,-6.7282
*argilit
0,0,1,0,2
135,0,.3,0,2.8284,2,-3.6569
*brechkia
0,   0,-1, -1.732051,3, .57735,-2.309401,.57735
60,  0,  0, -1.732051,3, -2.309401, 1.154701
120, 0,  0, -1.732051,3, -2.309401, 1.154701
0,   0,1, 0,3,1
*dolomit
0, 0,0, 0,2
90,0,0,2,4,2,-2
90,.5,0,2,4,2,-2
*galka
45,.85,.75,0,2.121320344,.424264068,-1.697056275
45,1.85,.45,0,2.121320344,.424264068,-1.697056275
135,1.15,.45,0,2.121320344,.424264068,-1.697056275
135,2.15,.75,0,2.121320344,.424264068,-1.697056275
0,1.15,.45,1.5,1.5,.7,-2.3
0,1.15,1.05,1.5,1.5,.7,-2.3
*glmor
0,2.346926627,2.869551813,5,5,0.306146746,-9.693853254
0,2.346926627,2.130448187,5,5,0.306146746,-9.693853254
45,2.130448187,2.653073373,0,7.071067812,0.306146746,-6.764921066
45,2.653073373,2.130448187,0,7.071067812,0.306146746,-6.764921066
135,2.869551813,2.653073373,0,7.071067812,0.306146746,-6.764921066
135,2.346926627,2.130448187,0,7.071067812,0.306146746,-6.764921066
90,2.130448187,2.346926627,5,5,0.306146746,-9.693853254
90,2.869551813,2.346926627,5,5,0.306146746,-9.693853254
0,-0.076536686,0.184775907,5,5,0.153073373,-9.846926627
0,-0.076536686,-0.184775907,5,5,0.153073373,-9.846926627
45,-0.184775907,0.076536686,0,7.071067812,0.153073373,-6.917994439
45,0.076536686,-0.184775907,0,7.071067812,0.153073373,-6.917994439
135,0.184775907,0.076536686,0,7.071067812,0.153073373,-6.917994439
135,-0.076536686,-0.184775907,0,7.071067812,0.153073373,-6.917994439
90,-0.184775907,-0.076536686,5,5,0.153073373,-9.846926627
90,0.184775907,-0.076536686,5,5,0.153073373,-9.846926627
0,-0.184775907,0,0,10,-0.369551813,9.630448187
0,0,1.25,0,5
0,2.130448187,2.5,0,10,-0.739103626,9.260896374
0,-5.184775907,5,0,10,-0.369551813,9.630448187
0,0,3.75,0,5
0,7.130448187,7.5,0,10,-0.739103626,9.260896374
*granit
0 ,-.325,0,1,1,.65,-1.35
90,0,-.325,1,1,.65,-1.35
*gravelit
0,0,0,5.774,1,.5774,-1.1547,.5774
60,0,0,1.4434,-.5,-3.4641,1.1547
120,0,0,3.1754,-.5,-3.4641,1.1547
*gravij
0,0,.43301,1.732051,3,-.25,.5, -2.714102
0,0,-.43301,1.732051,3,-.25,.5, -2.714102
60,0,0,1.732051,3, .5,-2.964102
60,1,0,1.732051,3,-2.964102,.5
120,0,0,1.732051,3,-2.964102,.5
120,1,0,1.732051,3,.5,-2.964102
*jorstva
0,   0,-1, -1.732051,3, .57735,-2.309401,.57735
60,  0,  0, -1.732051,3, -2.309401, 1.154701
120, 0,  0, -1.732051,3, -2.309401, 1.154701
*kamin
0,.57735,1,2.3094,2,1.1547,-5.7735,1.1547,-1.1547
60,0,0,-2.886751,1,1.1547,-2.3094,1.1547,-4.6188
120,0,0,-6.3508,1,-4.6188,1.1547,-2.3094,1.1547,-9.2376
330,0,0,13,.57735,2,-20,2,-8
*konglomerat
0, 0,1, 0,2
60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547
120,0,0,3.4641,2,1.1547,-4.6188,1.1547
30,2.598,0,2,3.4641,1,-3
30,4.3301,0,2,3.4641,-3,1
150,2.5980,0,2,3.4641,-3,1
150,4.3301,0,2,3.4641,1,-3
*krejda
0, 0,0, 0,.8
90,0,0,.8,1,.8,-.8
*les
90,0,0,1,1.2,-.4,1.6
*mergel
0,0,0,0,.2
45,0,0,0,.28284,.28284,-.28284
*mul
0,0,1.55,0,1.5
45,1.05,2.1,0,2.121320344,.424264068,-1.697056275
45,1.65,2.1,0,2.121320344,.424264068,-1.697056275
135,1.65,2.1,0,2.121320344,.424264068,-1.697056275
*nasup
45, 0,0, 0,1.25
135,0,0, 0,1.25
45,.85,.75,0,2.121320344,.424264068,-1.697056275
45,1.85,.45,0,2.121320344,.424264068,-1.697056275
135,1.15,.45,0,2.121320344,.424264068,-1.697056275
135,2.15,.75,0,2.121320344,.424264068,-1.697056275
0,1.15,.45,1.5,1.5,.7,-2.3
0,1.15,1.05,1.5,1.5,.7,-2.3
*nasup_glina
0,0,0,1,.5,2,-.7
120,0,0,0,1,10
*nasup_pisok
0,.215685,0,1.13137,1.13137,-.3,.1,-.731371
45,0,0,0,.8,10
135,0,0,0,.8,10
*pisok_gravij
0,1.4962,.5,2,2,.076536686,-1.923463314
0,.4962,1.5,2,2,.076536686,-1.923463314
0,.461731657,.592387953,1,	1,.076536686,-1.923463314
0,.461731657,.407612047,1,1,.076536686,-1.923463314
45,.407612047,.538268343,0,1.414213562,.076536686,-1.337676876
45,.538268343,.407612047,0,1.414213562,.076536686,-1.337676876
135,.592387953,.538268343,0,1.414213562,.076536686,-1.337676876
135,.461731657,.407612047,	0,1.414213562,.076536686,-1.337676876
90,.407612047,.461731657,1,1,.076536686,-1.923463314
90,.592387953,.461731657,1,1,.076536686,-1.923463314
*pisok_krup
45,0,0,0,1,.05,-1
*piskovyk
0, 0,1, 0,2
0,-.05,0,3.4641,2,.1,-1.28564
60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547
120,0,0,3.4641,2,1.1547,-4.6188,1.1547
*roslyna
0,0,0,1.5,2,1.2,-1.8
0,.2,-.3,1.5,2,.8,-2.2
0,.4,-.6,1.5,2,.4,-2.6
90,.6,-1.3,2,1.5,1,-3
53.13,1.3,-1.08,-1.8,2.4,1.3,-1.2
53.13,1.7,-1.3,-1.8,2.4,1.3,-1.2
53.13,2.1,-1.52,-1.8,2.4,1.3,-1.2
*roslynaPND
0,0,0,1.5,2,1.2,-1.8
0,.2,-.3,1.5,2,.8,-2.2
0,.4,-.6,1.5,2,.4,-2.6
90,.6,-1.3,2,1.5,1,-3
*sapropel
45,1.05,2.1,0,2.121320344,.424264068,-1.697056275
45,1.65,2.1,0,2.121320344,.424264068,-1.697056275
135,1.65,2.1,0,2.121320344,.424264068,-1.697056275
45,1.05,2.4,0,2.121320344,.424264068,-1.697056275
45,1.65,2.4,0,2.121320344,.424264068,-1.697056275
135,1.65,2.4,0,2.121320344,.424264068,-1.697056275
*shebin
0,   0,-1, 2.309401, 4, -.57735, 3.464102, -.57735
60,  0,  0, 2.309401, 4, 3.464102, -1.154701
120, 0,  0, 2.309401, 4, 3.464102, -1.154701
*slanec_glina
0,0,0,1,1,2,-2
135,0,0,0,1.41421,1.41421,-1.41421
*suglmore
0,0,0,0,10
0,4.04329142,7.30969883,10,10,1.91341716,-18.08658284
0,4.04329142,2.69030117,10,10,1.91341716,-18.08658284
225,4.04329142,7.30969883,0,14.14214,1.91341716,-12.22872
45,5.95671,2.69030117,0,14.14214,1.91341716,-12.22872
135,7.30969883,5.95670858,0,14.14214,1.91341716,-12.22872
135,4.04329142,2.69030117,0,14.14214,1.91341716,-12.22872
90,2.69030117,4.04329142,10,10,1.91341716,-18.08658284
90,7.30969883,4.04329142,10,10,1.91341716,-18.08658284
*supismor
0,0,0,0,10,7.5,-2.5
0,4.04329142,7.30969883,10,10,1.91341716,-18.08658284
0,4.04329142,2.69030117,10,10,1.91341716,-18.08658284
225,4.04329142,7.30969883,0,14.14214,1.91341716,-12.22872
45,5.95671,2.69030117,0,14.14214,1.91341716,-12.22872
135,7.30969883,5.95670858,0,14.14214,1.91341716,-12.22872
135,4.04329142,2.69030117,0,14.14214,1.91341716,-12.22872
90,2.69030117,4.04329142,10,10,1.91341716,-18.08658284
90,7.30969883,4.04329142,10,10,1.91341716,-18.08658284
*supismorPND
0, 0 ,0, 0, 1, .5, -.5
0, 0,.125,0,1, .5, -.5
*supispidmor
0, 0 ,0, 0, 1, .5, -.5
*torf_sylno
0,0,0,0,1.5
90,.75,0,0,1.5
45,.75,0,0,2.121320344
135,-.75,0,0,2.121320344
*torf_seredno
0,0,0,0,1.5
90,.75,0,0,1.5
45,0,.5,0,2.121320344,.424264068,-1.697056275
135,0,.5,0,2.121320344,.424264068,-1.697056275
*torf_slabo
0,0,0,0,1.5
90,.75,0,0,1.5
45,1.05,2.1,0,2.121320344,.424264068,-1.697056275
45,1.65,2.1,0,2.121320344,.424264068,-1.697056275
135,1.65,2.1,0,2.121320344,.424264068,-1.697056275
*valun
0,.57735,1,0,2,1.1547,-1.1547
60,0,0,-2.886751,1,1.1547,-2.3094,1.1547,-4.6188
120,0,0,2.886751,1,-4.6188,1.1547,-2.3094,1.1547
*VBK
0,0,0,0,4,1,-.5,1.5
0,0,1,0,4,1,-.5
0,0,-1,0,4,1,-.5
0,1,1.25,0,4,.5,-2.5
0,1,-1.25,0,4,.5,-2.5
90,1,-1.25,4,3,2.5,-1.5
90,1.5,-1.25,4,3,2.5,-1.5
90,2.5,.75,4,3,2.5,-1.5
0,2.5,.75,0,4,.5,-2.5
0,2.5,3.25,0,4,.5,-2.5
90,3,.75,4,3,2.5,-1.5
0,0,2,0,4,2.5,-.5
;;end WenGeo

*/

/*
acadiso.pat
;;
;;WenGeo
;;
*alevrolit
0, 0,1, 0,2
60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547
120,0,0,3.4641,2,1.1547,-4.6188,1.1547
60 ,3.4641,0,3.4641,2,-6.6282,.3
120,3.4641,0,3.4641,2,.2,-6.7282
*argilit
0,0,1,0,2
135,0,.3,0,2.8284,2,-3.6569
*brechkia
0,   0,-1, -1.732051,3, .57735,-2.309401,.57735
60,  0,  0, -1.732051,3, -2.309401, 1.154701
120, 0,  0, -1.732051,3, -2.309401, 1.154701
0,   0,1, 0,3,1
*dolomit
0, 0,0, 0,2
90,0,0,2,4,2,-2
90,.5,0,2,4,2,-2
*galka
45,.85,.75,0,2.121320344,.424264068,-1.697056275
45,1.85,.45,0,2.121320344,.424264068,-1.697056275
135,1.15,.45,0,2.121320344,.424264068,-1.697056275
135,2.15,.75,0,2.121320344,.424264068,-1.697056275
0,1.15,.45,1.5,1.5,.7,-2.3
0,1.15,1.05,1.5,1.5,.7,-2.3
*glmor
0,2.346926627,2.869551813,5,5,0.306146746,-9.693853254
0,2.346926627,2.130448187,5,5,0.306146746,-9.693853254
45,2.130448187,2.653073373,0,7.071067812,0.306146746,-6.764921066
45,2.653073373,2.130448187,0,7.071067812,0.306146746,-6.764921066
135,2.869551813,2.653073373,0,7.071067812,0.306146746,-6.764921066
135,2.346926627,2.130448187,0,7.071067812,0.306146746,-6.764921066
90,2.130448187,2.346926627,5,5,0.306146746,-9.693853254
90,2.869551813,2.346926627,5,5,0.306146746,-9.693853254
0,-0.076536686,0.184775907,5,5,0.153073373,-9.846926627
0,-0.076536686,-0.184775907,5,5,0.153073373,-9.846926627
45,-0.184775907,0.076536686,0,7.071067812,0.153073373,-6.917994439
45,0.076536686,-0.184775907,0,7.071067812,0.153073373,-6.917994439
135,0.184775907,0.076536686,0,7.071067812,0.153073373,-6.917994439
135,-0.076536686,-0.184775907,0,7.071067812,0.153073373,-6.917994439
90,-0.184775907,-0.076536686,5,5,0.153073373,-9.846926627
90,0.184775907,-0.076536686,5,5,0.153073373,-9.846926627
0,-0.184775907,0,0,10,-0.369551813,9.630448187
0,0,1.25,0,5
0,2.130448187,2.5,0,10,-0.739103626,9.260896374
0,-5.184775907,5,0,10,-0.369551813,9.630448187
0,0,3.75,0,5
0,7.130448187,7.5,0,10,-0.739103626,9.260896374
*granit
0 ,-.325,0,1,1,.65,-1.35
90,0,-.325,1,1,.65,-1.35
*gravelit
0,0,0,5.774,1,.5774,-1.1547,.5774
60,0,0,1.4434,-.5,-3.4641,1.1547
120,0,0,3.1754,-.5,-3.4641,1.1547
*gravij
0,0,.43301,1.732051,3,-.25,.5, -2.714102
0,0,-.43301,1.732051,3,-.25,.5, -2.714102
60,0,0,1.732051,3, .5,-2.964102
60,1,0,1.732051,3,-2.964102,.5
120,0,0,1.732051,3,-2.964102,.5
120,1,0,1.732051,3,.5,-2.964102
*jorstva
0,   0,-1, -1.732051,3, .57735,-2.309401,.57735
60,  0,  0, -1.732051,3, -2.309401, 1.154701
120, 0,  0, -1.732051,3, -2.309401, 1.154701
*kamin
0,.57735,1,2.3094,2,1.1547,-5.7735,1.1547,-1.1547
60,0,0,-2.886751,1,1.1547,-2.3094,1.1547,-4.6188
120,0,0,-6.3508,1,-4.6188,1.1547,-2.3094,1.1547,-9.2376
330,0,0,13,.57735,2,-20,2,-8
*konglomerat
0, 0,1, 0,2
60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547
120,0,0,3.4641,2,1.1547,-4.6188,1.1547
30,2.598,0,2,3.4641,1,-3
30,4.3301,0,2,3.4641,-3,1
150,2.5980,0,2,3.4641,-3,1
150,4.3301,0,2,3.4641,1,-3
*krejda
0, 0,0, 0,.8
90,0,0,.8,1,.8,-.8
*les
90,0,0,1,1.2,-.4,1.6
*mergel
0,0,0,0,.2
45,0,0,0,.28284,.28284,-.28284
*mul
0,0,1.55,0,1.5
45,1.05,2.1,0,2.121320344,.424264068,-1.697056275
45,1.65,2.1,0,2.121320344,.424264068,-1.697056275
135,1.65,2.1,0,2.121320344,.424264068,-1.697056275
*nasup
45, 0,0, 0,1.25
135,0,0, 0,1.25
45,.85,.75,0,2.121320344,.424264068,-1.697056275
45,1.85,.45,0,2.121320344,.424264068,-1.697056275
135,1.15,.45,0,2.121320344,.424264068,-1.697056275
135,2.15,.75,0,2.121320344,.424264068,-1.697056275
0,1.15,.45,1.5,1.5,.7,-2.3
0,1.15,1.05,1.5,1.5,.7,-2.3
*nasup_glina
0,0,0,1,.5,2,-.7
120,0,0,0,1,10
*nasup_pisok
0,.215685,0,1.13137,1.13137,-.3,.1,-.731371
45,0,0,0,.8,10
135,0,0,0,.8,10
*pisok_gravij
0,1.4962,.5,2,2,.076536686,-1.923463314
0,.4962,1.5,2,2,.076536686,-1.923463314
0,.461731657,.592387953,1,	1,.076536686,-1.923463314
0,.461731657,.407612047,1,1,.076536686,-1.923463314
45,.407612047,.538268343,0,1.414213562,.076536686,-1.337676876
45,.538268343,.407612047,0,1.414213562,.076536686,-1.337676876
135,.592387953,.538268343,0,1.414213562,.076536686,-1.337676876
135,.461731657,.407612047,	0,1.414213562,.076536686,-1.337676876
90,.407612047,.461731657,1,1,.076536686,-1.923463314
90,.592387953,.461731657,1,1,.076536686,-1.923463314
*pisok_krup
45,0,0,0,1,.05,-1
*piskovyk
0, 0,1, 0,2
0,-.05,0,3.4641,2,.1,-1.28564
60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547
120,0,0,3.4641,2,1.1547,-4.6188,1.1547
*roslyna
0,0,0,1.5,2,1.2,-1.8
0,.2,-.3,1.5,2,.8,-2.2
0,.4,-.6,1.5,2,.4,-2.6
90,.6,-1.3,2,1.5,1,-3
53.13,1.3,-1.08,-1.8,2.4,1.3,-1.2
53.13,1.7,-1.3,-1.8,2.4,1.3,-1.2
53.13,2.1,-1.52,-1.8,2.4,1.3,-1.2
*roslynaPND
0,0,0,1.5,2,1.2,-1.8
0,.2,-.3,1.5,2,.8,-2.2
0,.4,-.6,1.5,2,.4,-2.6
90,.6,-1.3,2,1.5,1,-3
*sapropel
45,1.05,2.1,0,2.121320344,.424264068,-1.697056275
45,1.65,2.1,0,2.121320344,.424264068,-1.697056275
135,1.65,2.1,0,2.121320344,.424264068,-1.697056275
45,1.05,2.4,0,2.121320344,.424264068,-1.697056275
45,1.65,2.4,0,2.121320344,.424264068,-1.697056275
135,1.65,2.4,0,2.121320344,.424264068,-1.697056275
*shebin
0,   0,-1, 2.309401, 4, -.57735, 3.464102, -.57735
60,  0,  0, 2.309401, 4, 3.464102, -1.154701
120, 0,  0, 2.309401, 4, 3.464102, -1.154701
*slanec_glina
0,0,0,1,1,2,-2
135,0,0,0,1.41421,1.41421,-1.41421
*suglmore
0,0,0,0,10
0,4.04329142,7.30969883,10,10,1.91341716,-18.08658284
0,4.04329142,2.69030117,10,10,1.91341716,-18.08658284
225,4.04329142,7.30969883,0,14.14214,1.91341716,-12.22872
45,5.95671,2.69030117,0,14.14214,1.91341716,-12.22872
135,7.30969883,5.95670858,0,14.14214,1.91341716,-12.22872
135,4.04329142,2.69030117,0,14.14214,1.91341716,-12.22872
90,2.69030117,4.04329142,10,10,1.91341716,-18.08658284
90,7.30969883,4.04329142,10,10,1.91341716,-18.08658284
*supismor
0,0,0,0,10,7.5,-2.5
0,4.04329142,7.30969883,10,10,1.91341716,-18.08658284
0,4.04329142,2.69030117,10,10,1.91341716,-18.08658284
225,4.04329142,7.30969883,0,14.14214,1.91341716,-12.22872
45,5.95671,2.69030117,0,14.14214,1.91341716,-12.22872
135,7.30969883,5.95670858,0,14.14214,1.91341716,-12.22872
135,4.04329142,2.69030117,0,14.14214,1.91341716,-12.22872
90,2.69030117,4.04329142,10,10,1.91341716,-18.08658284
90,7.30969883,4.04329142,10,10,1.91341716,-18.08658284
*supismorPND
0, 0 ,0, 0, 1, .5, -.5
0, 0,.125,0,1, .5, -.5
*supispidmor
0, 0 ,0, 0, 1, .5, -.5
*torf_sylno
0,0,0,0,1.5
90,.75,0,0,1.5
45,.75,0,0,2.121320344
135,-.75,0,0,2.121320344
*torf_seredno
0,0,0,0,1.5
90,.75,0,0,1.5
45,0,.5,0,2.121320344,.424264068,-1.697056275
135,0,.5,0,2.121320344,.424264068,-1.697056275
*torf_slabo
0,0,0,0,1.5
90,.75,0,0,1.5
45,1.05,2.1,0,2.121320344,.424264068,-1.697056275
45,1.65,2.1,0,2.121320344,.424264068,-1.697056275
135,1.65,2.1,0,2.121320344,.424264068,-1.697056275
*valun
0,.57735,1,0,2,1.1547,-1.1547
60,0,0,-2.886751,1,1.1547,-2.3094,1.1547,-4.6188
120,0,0,2.886751,1,-4.6188,1.1547,-2.3094,1.1547
*VBK
0,0,0,0,4,1,-.5,1.5
0,0,1,0,4,1,-.5
0,0,-1,0,4,1,-.5
0,1,1.25,0,4,.5,-2.5
0,1,-1.25,0,4,.5,-2.5
90,1,-1.25,4,3,2.5,-1.5
90,1.5,-1.25,4,3,2.5,-1.5
90,2.5,.75,4,3,2.5,-1.5
0,2.5,.75,0,4,.5,-2.5
0,2.5,3.25,0,4,.5,-2.5
90,3,.75,4,3,2.5,-1.5
0,0,2,0,4,2.5,-.5
;;end WenGeo
*/

void AddCircle(MyAcad & m_acad, CPoint2 pt2, double Radius, COLORREF color, double v_scale, double g_scale, bool to_fill, COLORREF fill_color)
{
	Radius *= min(v_scale, g_scale);
	try
	{

		COleSafeArray myOleSafe_insertion_point;
		double* pOriginalVertices = new double[3];
		pOriginalVertices[0] = g_scale * pt2.x;//x
		pOriginalVertices[1] = v_scale * pt2.y;//y
		pOriginalVertices[2] = 0;
		myOleSafe_insertion_point.CreateOneDim(VT_R8, 3, pOriginalVertices); 
		delete[] pOriginalVertices;

		LPDISPATCH pCircle = m_acad.m_model_space.AddCircle(myOleSafe_insertion_point, Radius);
		if(pCircle)
		{
			IAcadCircle m_circle;
			m_circle.AttachDispatch(pCircle);

			m_circle.SetColor(dimeLayer::RGBToColor(color));


			if (to_fill)
			{
				BOOL Associativity = TRUE;
				LPDISPATCH pHatch = m_acad.m_model_space.AddHatch(acHatchPatternTypePredefined, "SOLID", Associativity);
				if(pHatch)
				{
					IAcadHatch m_hatch;
					m_hatch.AttachDispatch(pHatch);
					COleSafeArray myLoop;
					try
					{
						int colindex = dimeLayer::RGBToColor(fill_color);
						m_hatch.SetColor(colindex);

						m_hatch.SetAssociativeHatch(true);


						myLoop.CreateOneDim(VT_DISPATCH, 1, &pCircle); 
						m_hatch.AppendOuterLoop(COleVariant(myLoop));
						m_hatch.Evaluate();
						m_acad.m_document.Regen(1);
					}
					catch (CException* pe)
					{
						// catch errors from WinINet 
						TCHAR szErr[4098]; 
						pe->GetErrorMessage(szErr, 4098); 
						AfxMessageBox(szErr);
						pe->Delete();
					}						

					//m_hatch.AppendInnerLoop();
					myLoop.Detach();
					m_hatch.ReleaseDispatch();
				}
			}
			m_circle.ReleaseDispatch();
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}


void AddText(MyAcad & m_acad, LPCTSTR TextString, CPoint2 pt2, double Height, COLORREF color, double v_scale, double g_scale)
{
	Height *= min(v_scale, g_scale);
	try
	{

		COleSafeArray myOleSafe_insertion_point;
		double* pOriginalVertices = new double[3];
		pOriginalVertices[0] = g_scale * pt2.x;//x
		pOriginalVertices[1] = v_scale * pt2.y;//y
		pOriginalVertices[2] = 0;
		myOleSafe_insertion_point.CreateOneDim(VT_R8, 3, pOriginalVertices); 
		delete[] pOriginalVertices;

		LPDISPATCH pText = m_acad.m_model_space.AddText(TextString, myOleSafe_insertion_point, Height);
		if(pText)
		{
			IAcadText m_text;
			m_text.AttachDispatch(pText);

			m_text.SetColor(dimeLayer::RGBToColor(color));
			m_text.ReleaseDispatch();
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void AddText(MyAcad & m_acad, LPCTSTR TextString, CPoint2 pt2, CPoint3 pt3, double Height, COLORREF color, double v_scale, double g_scale)
{
	Height *= min(v_scale, g_scale);
	try
	{

		COleSafeArray myOleSafe_insertion_point;
		double* pOriginalVertices = new double[3];

		pOriginalVertices[0] = g_scale * pt2.x;//x
		pOriginalVertices[1] = v_scale * pt2.y;//y

		switch(BrokenPlane3D::sprData.export_coordinate_type)
		{
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				pOriginalVertices[0] = g_scale * pt2.x;//x
				pOriginalVertices[1] = v_scale * pt2.y;//y
			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{
				pOriginalVertices[0] = g_scale * pt3.y;//x
				pOriginalVertices[1] = v_scale * pt3.z;//y
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				pOriginalVertices[0] = g_scale * pt3.x;//x
				pOriginalVertices[1] = v_scale * pt3.z;//y
			}
			break;
		}


		pOriginalVertices[2] = 0;
		myOleSafe_insertion_point.CreateOneDim(VT_R8, 3, pOriginalVertices); 
		delete[] pOriginalVertices;

		LPDISPATCH pText = m_acad.m_model_space.AddText(TextString, myOleSafe_insertion_point, Height);
		if(pText)
		{
			IAcadText m_text;
			m_text.AttachDispatch(pText);

			m_text.SetColor(dimeLayer::RGBToColor(color));
			m_text.ReleaseDispatch();
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}


void AddPolyLine(MyAcad & m_acad, vector<CPoint2> & vpt2, bool to_close, COLORREF color, double v_scale, double g_scale)
{
	try
	{
		COleSafeArray myOleSafeVerticesList = MakeVerticesList(vpt2, v_scale, g_scale);				
		LPDISPATCH pPolyline = m_acad.m_model_space.AddPolyline(myOleSafeVerticesList);
		if(pPolyline)
		{
			IAcadPolyline m_poly_line;
			m_poly_line.AttachDispatch(pPolyline);
			if (to_close)
				m_poly_line.SetClosed(TRUE);
			m_poly_line.SetColor(dimeLayer::RGBToColor(color));
			m_poly_line.ReleaseDispatch();
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}
void AddPolyLine(MyAcad & m_acad, short export_coordinate_type, vector<CPoint3> & vpt3, bool to_close, COLORREF color, double v_scale, double g_scale)
{
	try
	{
		COleSafeArray myOleSafeVerticesList = MakeVerticesList(export_coordinate_type, vpt3, v_scale, g_scale);				
		LPDISPATCH pPolyline = m_acad.m_model_space.AddPolyline(myOleSafeVerticesList);
		if(pPolyline)
		{
			IAcadPolyline m_poly_line;
			m_poly_line.AttachDispatch(pPolyline);
			if (to_close)
				m_poly_line.SetClosed(TRUE);
			m_poly_line.SetColor(dimeLayer::RGBToColor(color));
			m_poly_line.ReleaseDispatch();
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}



void AddPolyLine(MyAcad & m_acad, vector<CPoint2> & vpt2, vector<CPoint3> & vpt3, bool to_close, COLORREF color, double v_scale, double g_scale)
{
	switch(BrokenPlane3D::sprData.export_coordinate_type)
	{
	case SAVE_PROFILE_WITH_PROFILE_LEN:
		{
			if (vpt2.size())
			{
				AddPolyLine(m_acad, vpt2, to_close, color, v_scale, g_scale);	
			}
		}
		break;
	case SAVE_PROFILE_WITH_NORTH_PROJECTION:
		{
			if (vpt3.size())
			{
				AddPolyLine(m_acad, SAVE_PROFILE_WITH_NORTH_PROJECTION, vpt3, to_close, color, v_scale, g_scale);	
			}
		}
		break;
	case SAVE_PROFILE_WITH_EAST_PROJECTION:
		{
			if (vpt3.size())
			{
				AddPolyLine(m_acad, SAVE_PROFILE_WITH_EAST_PROJECTION, vpt3, to_close, color, v_scale, g_scale);	
			}
		}
		break;
	}
}

void AddHatchPolyLine(MyAcad & m_acad, vector<CPoint2> & vpt2, COLORREF color, string hatchacad, double angle, double scale, double v_scale, double g_scale)
{
	int colindex = dimeLayer::RGBToColor(color);
	int colindex0 = dimeLayer::RGBToColor(0);
	try
	{
		COleSafeArray myOleSafeVerticesList = MakeVerticesList(vpt2, v_scale, g_scale);				
		LPDISPATCH pPolyline = m_acad.m_model_space.AddPolyline(myOleSafeVerticesList);
		if(pPolyline)
		{
			IAcadPolyline m_poly_line;
			m_poly_line.AttachDispatch(pPolyline);
			try
			{
				m_poly_line.SetClosed(TRUE);
				m_poly_line.SetColor(colindex0);

				if (hatchacad.size())
				{
					BOOL Associativity = TRUE;
					LPCTSTR PatternName = hatchacad.c_str();
					LPDISPATCH pHatch = m_acad.m_model_space.AddHatch(acHatchPatternTypePredefined, PatternName, Associativity);
					if(pHatch)
					{
						//AfxMessageBox("if(pHatch)");
						IAcadHatch m_hatch;
						m_hatch.AttachDispatch(pHatch);
						COleSafeArray myLoop;
						try
						{
							m_hatch.SetColor(colindex);

							m_hatch.SetAssociativeHatch(true);
							m_hatch.SetPatternScale(scale);
							m_hatch.SetPatternAngle(PI * angle / 180.0);


							myLoop.CreateOneDim(VT_DISPATCH, 1, &pPolyline); 
							m_hatch.AppendOuterLoop(COleVariant(myLoop));
							m_hatch.Evaluate();
							m_acad.m_document.Regen(1);
						}
						catch (CException* pe)
						{
							// catch errors from WinINet 
							TCHAR szErr[4098]; 
							pe->GetErrorMessage(szErr, 4098); 
							AfxMessageBox(szErr);
							pe->Delete();
						}						

						//m_hatch.AppendInnerLoop();
						myLoop.Detach();
						m_hatch.ReleaseDispatch();
					}
					else
					{
						AfxMessageBox("!!! if(pHatch)");
					}
				}
				m_poly_line.ReleaseDispatch();
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				AfxMessageBox(hatchacad.c_str());
				pe->Delete();
			}
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		AfxMessageBox(hatchacad.c_str());
		pe->Delete();
	}
}

void AddHatchPolyLine(MyAcad & m_acad, short export_coordinate_type, vector<CPoint3> & vpt3, COLORREF color, string hatchacad, double angle, double scale, double v_scale, double g_scale)
{
	int colindex = dimeLayer::RGBToColor(color);
	int colindex0 = dimeLayer::RGBToColor(0);
	try
	{
		COleSafeArray myOleSafeVerticesList = MakeVerticesList(export_coordinate_type, vpt3, v_scale, g_scale);				
		LPDISPATCH pPolyline = m_acad.m_model_space.AddPolyline(myOleSafeVerticesList);
		if(pPolyline)
		{
			IAcadPolyline m_poly_line;
			m_poly_line.AttachDispatch(pPolyline);
			try
			{
				m_poly_line.SetClosed(TRUE);
				m_poly_line.SetColor(colindex0);

				if (hatchacad.size())
				{
					BOOL Associativity = TRUE;
					LPCTSTR PatternName = hatchacad.c_str();
					LPDISPATCH pHatch = m_acad.m_model_space.AddHatch(acHatchPatternTypePredefined, PatternName, Associativity);
					if(pHatch)
					{
						//AfxMessageBox("if(pHatch)");
						IAcadHatch m_hatch;
						m_hatch.AttachDispatch(pHatch);
						COleSafeArray myLoop;
						try
						{
							m_hatch.SetColor(colindex);
							m_hatch.SetAssociativeHatch(true);
							m_hatch.SetPatternScale(scale);
							m_hatch.SetPatternAngle(PI * angle / 180.0);

							myLoop.CreateOneDim(VT_DISPATCH, 1, &pPolyline); 
							m_hatch.AppendOuterLoop(COleVariant(myLoop));
							m_hatch.Evaluate();
							m_acad.m_document.Regen(1);
						}
						catch (CException* pe)
						{
							// catch errors from WinINet 
							TCHAR szErr[4098]; 
							pe->GetErrorMessage(szErr, 4098); 
							AfxMessageBox(szErr);
							pe->Delete();
						}						

						//m_hatch.AppendInnerLoop();
						myLoop.Detach();
						m_hatch.ReleaseDispatch();
					}
					else
					{
						AfxMessageBox("!!! if(pHatch)");
					}
				}
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				AfxMessageBox(hatchacad.c_str());
				pe->Delete();
			}
			m_poly_line.ReleaseDispatch();
		}
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		AfxMessageBox(hatchacad.c_str());
		pe->Delete();
	}
}

bool GetMeanXY(vector<CPoint2> vpt2, CPoint2 &mean_pt2)
{
	mean_pt2.x = 0.0;
	mean_pt2.y = 0.0;
	if (vpt2.size() > 0)
	{
		for (vector<CPoint2>::iterator it = vpt2.begin();
			it != vpt2.end(); it++)
		{
			mean_pt2.x += (*it).x;
			mean_pt2.y += (*it).y;
		}
		mean_pt2.x /= vpt2.size();
		mean_pt2.y /= vpt2.size();
		return true;
	}
	return false;
}

void BrokenPlane3D::AutoCADColomn(AutoCADRazrezParam param)
{
	vector<CPoint2> vpt;
	vpt.push_back(CPoint2(0,  0));
	vpt.push_back(CPoint2(0, 0.9));
	vpt.push_back(CPoint2(3, 0.9));
	vpt.push_back(CPoint2(3, 0));

	MyAcad m_acad;
	m_acad.AcadOleLoad();
	if (m_acad.IsApplicationDispatch())
	{
		try
		{
			m_acad.AcadOleExecute(NULL);

			SetGrMain setGrMain(&this->m_pSurfDoc->GetLabDoc()->m_database);
			if ( setGrMain.Open(CRecordset::dynaset) )
			{
				SetUmPoz setUmPoz(&this->m_pSurfDoc->GetLabDoc()->m_database);	
				setUmPoz.m_strFilter.Format("");
				setUmPoz.m_strSort.Format("");
				if ( setUmPoz.Open(CRecordset::dynaset) )
				{
					int j = 0;

					if (!setGrMain.IsBOF()) 
					{
						setGrMain.MoveFirst( );
						while(!setGrMain.IsEOF()) 
						{

							//ID_GRMAIN = setGrMain.m_ID_GRMAIN;
							//TYPGR = setGrMain.m_TYPGR;
							//TYPGR_PCK = setGrMain.m_TYPGR_PCK;
							//ID_GRCONS = setGrMain.m_ID_GRCONS;
							//ID_NJU = setGrMain.m_ID_NJU;
							//ID_NORMATYV = setGrMain.m_ID_NORMATYV;
							long ID_UMPOZ = setGrMain.m_ID_UMPOZ;
							CString GrMainNazvaR = setGrMain.m_NAZVA_R;
							CString GrMainNazvaU = setGrMain.m_NAZVA_U;

							if (!setUmPoz.IsBOF())
							{
								setUmPoz.MoveFirst();
								while (!setUmPoz.IsEOF())
								{
									if (setUmPoz.m_ID_UMPOZ == ID_UMPOZ)
									{
										string hatchacad = setUmPoz.m_HATCHACAD;
										double angle = setUmPoz.m_Angle;
										double scale = setUmPoz.m_Scale * param.hatch_scale;

										vector<CPoint2> vpt2;
										for (int i = 0; i < 4; i++)
										{
											vpt2.push_back(CPoint2(vpt[i].x, vpt[i].y + 1.0*j));
										}
										COLORREF color = 0;
										AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale, param.v_scale, param.g_scale);

										double Height_lin = 0.50;
										AddText(m_acad, GrMainNazvaR.GetBuffer(), CPoint2(4, 1.0*j+0.15), Height_lin, color, param.v_scale, param.g_scale);

										break;
									}
									setUmPoz.MoveNext();
								}
							}

							setGrMain.MoveNext();
							j++;
						}
					}
				}
			}

			//m_acad.m_document.SaveAs(lpstrFile, COleVariant(long(12)));
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		m_acad.AcadOleRelease();
	}
	else
		printf("!!!!! m_acad.IsApplicationDispatch()\n");
}



BOOL CALLBACK DlgProcAutoCADRazres( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static BrokenPlane3D * lpBrokenPlane3D;
	static AutoCADRazrezParam param;
		
	char str[128];


	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpBrokenPlane3D = (BrokenPlane3D *)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_DRAW_POLIGONES, true);
			//CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_DRAW_FAULTS, true);
			CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_POLIGONES_FILL, true);
			CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_SKIP_UNCHECKED_POLIGONES, true);
			CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_DRAW_SLOI_LINES, true);
			CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_DRAW_WELLS2, true);
			CheckDlgButton(hDlg, IDC_CHECK_AUTOCAD_DRAW_COLOMN, true);


			param.init_v_scale = 1.0;
			param.init_g_scale = 1.0;
			param.init_hatch_scale = 0.1;

			char str[1024];

			sprintf(str, "%f", param.init_v_scale);
			DeleteEndZeros(str);
			SetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_V_SCALE, str);

			sprintf(str, "%f", param.init_g_scale);
			DeleteEndZeros(str);
			SetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_G_SCALE, str);

			sprintf(str, "%f", param.init_hatch_scale);
			DeleteEndZeros(str);
			SetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_HATCH_SCALE, str);			
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{		
		case IDC_BUTTON_GRUNTS_COLOMN:
			{

				GetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_V_SCALE, str, 127);
				param.v_scale = atof(str);
				GetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_HATCH_SCALE, str, 127);
				param.g_scale = atof(str);

				GetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_HATCH_SCALE, str, 127);
				param.hatch_scale = atof(str);

				lpBrokenPlane3D->AutoCADColomn(param);
			}
			break;
		case IDOK:
			{

				param.insert_dxf      = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_INSERT_DXF) == BST_CHECKED;
				param.draw_poligones  = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_POLIGONES) == BST_CHECKED;
				param.poligones_fill  = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_POLIGONES_FILL) == BST_CHECKED;

				param.skip_unchecked_poligones  = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_SKIP_UNCHECKED_POLIGONES) == BST_CHECKED;
				

				param.draw_sloi_lines = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_SLOI_LINES) == BST_CHECKED;
				param.draw_faults     = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_FAULTS) == BST_CHECKED;
				param.draw_catches    = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_GEOCATCHES) == BST_CHECKED;

				param.draw_wells      = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_WELLS) == BST_CHECKED;
				param.draw_wells2     = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_WELLS2) == BST_CHECKED;

				param.draw_colomn     = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_COLOMN) == BST_CHECKED;
				param.draw_scale_line = IsDlgButtonChecked( hDlg, IDC_CHECK_AUTOCAD_DRAW_SCALE_LINE) == BST_CHECKED;

				
				GetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_V_SCALE, str, 127);
				param.v_scale = atof(str);
				GetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_G_SCALE, str, 127);
				param.g_scale = atof(str);

				GetDlgItemText(hDlg, IDC_EDIT_AUTOCAD_HATCH_SCALE, str, 127);
				param.hatch_scale = atof(str);

				lpBrokenPlane3D->AutoCADRazres(param);	
			}
			break;
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}





void BrokenPlane3D::AutoCADRazres(const char * profile_name)
{
	this->SetName(profile_name);

	HANDLE hDialog = LoadResource( hInst,										
		FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_AUTOCAD_RAZREZ),
		RT_DIALOG ) );				

	LPVOID lpDialog = LockResource( hDialog );						
	HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog,
		this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL,
		(DLGPROC)::DlgProcAutoCADRazres,
		(LPARAM)this );
						
	ShowWindow(hDlg, SW_SHOW);
}


void BrokenPlane3D::AutoCADPolyigon(MyAcad & m_acad, Poligon3D & poli, AutoCADRazrezParam & param, 
					 int n_sloi, int n_cut, double xProfile, string hatchacad, double angle, double scale)
{
	// число точек в текущем полигоне плюс одна
	int len = poli.GetPointsNumber();
	bool bChecked = poli.m_bChecked;
	bool to_skip = param.skip_unchecked_poligones && !bChecked;
	if (len > 1 && !to_skip)
	{
		bool to_close = true;
		vector<CPoint2> vpt2;
		switch(BrokenPlane3D::sprData.export_coordinate_type)
		{
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				CPoint2 pt2 = this->m_vMapBlnProfiles[n_cut]; 
				for (int i = 0; i < poli.GetPointsNumber(); i++)
				{
					CPoint3 pt3 = poli.GetDocumentPoint(i);
					vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
				}

			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{
				for (int i = 0; i < poli.GetPointsNumber(); i++)
				{
					CPoint3 pt3 = poli.GetDocumentPoint(i);
					vpt2.push_back(CPoint2(pt3.y, pt3.z));
				}
				//if (hatchacad.size())
				//	AddHatchPolyLine(m_acad, vpt2, poli.GetColor(), hatchacad, angle, scale, param.v_scale, param.g_scale);
				//else
				//	AddPolyLine(m_acad, vpt2, to_close, poli.GetColor(), param.v_scale, param.g_scale);
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				for (int i = 0; i < poli.GetPointsNumber(); i++)
				{
					CPoint3 pt3 = poli.GetDocumentPoint(i);
					vpt2.push_back(CPoint2(pt3.x, pt3.z));
				}
				//if (hatchacad.size())
				//	AddHatchPolyLine(m_acad, vpt2, poli.GetColor(), hatchacad, angle, scale, param.v_scale, param.g_scale);
				//else
				//	AddPolyLine(m_acad, vpt2, to_close, poli.GetColor(), param.v_scale, param.g_scale);
			}
			break;
		}						
		if (param.draw_poligones)
		{
			if (hatchacad.size() && param.poligones_fill)
				AddHatchPolyLine(m_acad, vpt2, poli.GetColor(), hatchacad, angle, scale, param.v_scale, param.g_scale);
			else
				AddPolyLine(m_acad, vpt2, to_close, poli.GetColor(), param.v_scale, param.g_scale);
		}
		CPoint2 mean_pt2;
		if (GetMeanXY(vpt2, mean_pt2))
		{
			char str[4098];
			str[0] = '\0';
			bool ige_found = false;

			long id_ige = this->m_polySloi[n_sloi].id_ige;
			/*if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
			{
				long id_obj = this->m_pSurfDoc->Get_ID_OBJ();								
				CString ige = GetIGEName(&this->m_pSurfDoc->GetLabDoc()->m_database, id_obj, id_ige);
				ige_found = ige.GetLength() > 0;
				if (ige_found)
				{
					sprintf(str, "%s\0", (const char *)ige);
				}
			}
			else if (this->m_pSurfDoc)*/
			{
				for (vector<IGE_Data>::iterator it_ige = this->m_pSurfDoc->m_db_ige.data.begin();
					it_ige != this->m_pSurfDoc->m_db_ige.data.end(); it_ige++)
				{
					if ((*it_ige).ige_filled)
					{
						if ((*it_ige).ige.id_ige == id_ige)
						{
							ige_found = true;
							sprintf(str, "%s\0", (*it_ige).ige.ige.c_str());
							break;
						}
					}
				}
			}


			if (id_ige > -1 && ige_found)
			{

				double Height_lin = 0.7;
				COLORREF color = 0;

				AddCircle(m_acad, mean_pt2, Height_lin, color, param.v_scale, param.g_scale, true, RGB(255, 255, 255)); 

				AddText(m_acad, str, 
					CPoint2(mean_pt2.x - (0.3 * strlen(str) * Height_lin), 
					mean_pt2.y - (0.5 * Height_lin)*min(param.v_scale,param.g_scale)), 
					Height_lin, color, param.v_scale, param.g_scale);
			}
		}						
	}

}

void BrokenPlane3D::AutoCADRazres(AutoCADRazrezParam param)
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     
		TEXT("AutoCAD (*.dwg)\0*.dwg\0")
		TEXT("All Files (*.*)\0*.*\0");

	sprintf(lpstrFile, "razrez%s", this->GetName().c_str());
	DWORD nFilterIndex = 0;
	if (S_OK != SaveProfDlg(0, lpstrFile, filter, nFilterIndex, BrokenPlane3D::sprData))
		return;


	int n_cut, n_sloi, n_fault, n_catch;

	MyAcad m_acad;
	m_acad.AcadOleLoad();
	if (m_acad.IsApplicationDispatch())
	{
		try
		{

			char lpstrFile_dxf[1024];
			if (param.insert_dxf && OpenFileDlg(0, "AutoCAD DXF (*.dxf)\0*.dxf\0All files \0*.*\0", lpstrFile_dxf) == S_OK)
			{
				m_acad.AcadOleExecute(lpstrFile_dxf);
			}
			else
				m_acad.AcadOleExecute(NULL);



			long n_layouts = m_acad.m_layouts.GetCount();

			if (n_layouts)
			{
				LPDISPATCH pLayout = m_acad.m_layouts.Item(COleVariant(long(0)));
				if (pLayout)
				{
					VERIFY(pLayout);
					IAcadLayout m_layout;
					m_layout.AttachDispatch(pLayout);
					m_layout.ReleaseDispatch();
				}
			}

			long n_viewports = m_acad.m_viewports.GetCount();
			if (n_viewports)
			{
				LPDISPATCH pViewport = m_acad.m_viewports.Item(COleVariant(long(0)));
				if (pViewport)
				{
					VERIFY(pViewport);
					IAcadViewport m_viewport;
					m_viewport.AttachDispatch(pViewport);
					m_viewport.ReleaseDispatch();
				}
			}





			if (false)
			{			
	/*
				LPDISPATCH pPViewport = m_acad.m_document.GetActivePViewport();
				if (pPViewport)
				{
					VERIFY(pPViewport);
					IAcadPViewport m_pviewport;
					m_pviewport.AttachDispatch(pPViewport);
					m_pviewport.SetCustomScale(50);
					m_pviewport.ReleaseDispatch();
				}
	*/
				COleSafeArray myOleSafe_insertion_point;
				double* pOriginalVertices = new double[3];
				pOriginalVertices[0] = param.g_scale * 0;//pt2.x;//x
				pOriginalVertices[1] = param.v_scale * 0;//pt2.y;//y
				pOriginalVertices[2] = 0;
				myOleSafe_insertion_point.CreateOneDim(VT_R8, 3, pOriginalVertices); 
				delete[] pOriginalVertices;

				LPDISPATCH pPViewport = m_acad.m_paper_space.AddPViewport(myOleSafe_insertion_point, 100, 100);
				if (pPViewport)
				{
					VERIFY(pPViewport);
					IAcadPViewport m_pviewport;
					m_pviewport.AttachDispatch(pPViewport);
					m_pviewport.SetCustomScale(2);
					m_pviewport.ReleaseDispatch();
				}
			}



			if (true)//(nFilterIndex == 2)//Poligones as one file Golden Software Blanking
			{
				for (n_sloi = 0; n_sloi < m_nSloi; n_sloi++)
				{					
					if (param.skip_unchecked_poligones && !m_polySloi[n_sloi].m_poligones_ObjectList.m_bChecked)
					{
						continue;
					}

					// координата начальной скважины в координатах профиля
					double xProfile = 0.0;

					string hatchacad = "";
					double angle = 0.0;
					double scale = 0.0;
					long id_umpoz = m_polySloi[n_sloi].id_umpoz;
					map<long, umpoz_data>::iterator found_umpoz = this->m_pSurfDoc->m_db_umpoz.data1.find(id_umpoz);
					if (found_umpoz != this->m_pSurfDoc->m_db_umpoz.data1.end())
					{
						//(*found_umpoz).second.id_umpoz;
						//(*found_umpoz).second.umpoz;
						hatchacad	= (*found_umpoz).second.hatchacad;
						angle		= (*found_umpoz).second.angle;
						scale		= (*found_umpoz).second.scale;
					}	

					scale *= param.hatch_scale;

					/*char str[4096];
					sprintf(str, "hatchacad = %d %s", n_sloi, hatchacad.c_str());
					AfxMessageBox(str);*/

					for (n_cut = 0; n_cut < m_nCuts; n_cut++)
					{
#if USE_UNVISIBLE_CUTTING
						for (size_t i = 0; i < m_polySloi[n_sloi].m_poligones[n_cut].Size(); i++)
						{
							AutoCADPolyigon(m_acad, m_polySloi[n_sloi].m_poligones[n_cut][i], param, 
								n_sloi, n_cut, xProfile, hatchacad, angle, scale);
						}
#else
						AutoCADPolyigon(m_acad, m_polySloi[n_sloi].m_poligones[n_cut], param, 
							n_sloi, n_cut, xProfile, hatchacad, angle, scale);
#endif
						xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);
					}
				}
			}


			double dz = 1.0, // шаг масштабной линейки
				marg = 2.0; // поля от разреза до масштпбной линейки
			double Height_lin = 0.5 * dz; // выcота букв масштабной линейки

			double z_ceil = 100; // потолок
			double z_floor = 0; // пол области разреза

			// потолок и пол подвала
			double z_podval_ceil = 0;
			double z_podval_floor = 0;
					
			double h = 2*dz;//высота строки подвала
			double Height_podvh = dz; // выcота букв в подвале
			double Height_podv1 = dz; // выcота букв в подвале
			double Height_podv2 = dz; // выcота букв в подвале
			double Height_podv3 = dz; // выcота букв в подвале
			double Height_podv4 = dz; // выcота букв в подвале

			CPoint2 pt2_left_border, pt2_right_border;
			double xProfile_left_border, xProfile_right_border;


			if (true)//scale line and podval
			{
				COLORREF color = 0;
				// координата начальной скважины в координатах профиля
				double xProfile = 0.0;
				if (this->m_pSurfDoc && this->m_pSurfDoc->m_cube_size.Defined() && m_vMapBlnProfiles.Size() > 0)
				{
					// толщина масштабной линейки
					double w = 0.25 * param.init_g_scale / param.g_scale;

					// потолок и пол области разреза
					z_ceil = ceil(this->m_pSurfDoc->m_cube_size.zMax());
					z_floor = floor(this->m_pSurfDoc->m_cube_size.zLL);


					// крайне-левая (start) и крайне-правая(finish) точка разреза
					CPoint2 pt2_start;
					CPoint2 pt2_finish;

					pt2_start.x = FLT_MAX;
					pt2_start.y = FLT_MAX;

					pt2_finish.x = -FLT_MAX;
					pt2_finish.y = -FLT_MAX;

					for (int n_drill = 0; n_drill < m_nDrills; n_drill++)
					{
						if (pt2_start.x > m_vMapBlnProfiles[n_drill].x) pt2_start.x = m_vMapBlnProfiles[n_drill].x;
						if (pt2_start.y > m_vMapBlnProfiles[n_drill].y) pt2_start.y = m_vMapBlnProfiles[n_drill].y;

						if (pt2_finish.x < m_vMapBlnProfiles[n_drill].x) pt2_finish.x = m_vMapBlnProfiles[n_drill].x;
						if (pt2_finish.y < m_vMapBlnProfiles[n_drill].y) pt2_finish.y = m_vMapBlnProfiles[n_drill].y;
					}

					// here we will put 2D points
					vector<CPoint2> vpt2;
					// here we will put 3D points
					vector<CPoint3> vpt3;

					// максимальное число символов в цифровых значениях масштабной линейки
					size_t max_strlen = 0;
					char sz[256];
					for (double z = z_floor; z <= z_ceil; z += dz)
					{
						sprintf(sz, "%f", z);
						DeleteEndZeros(sz);

						size_t szln = strlen(sz);
						if (max_strlen < szln) 
							max_strlen = szln;
					}

					// сдвиг текста	относительно левого края профиля					
					double tsh = marg+2*w + max_strlen * Height_lin;

					// отрисовываем линейку и ставим цифровые метки
					for (double z = z_floor; z < z_ceil; z += dz)
					{
						bool to_close = true;

						vpt2.clear();
						vpt3.clear();

						vpt2.push_back(CPoint2(xProfile-marg-w, z));
						vpt3.push_back(CPoint3(pt2_start.x-marg-w, pt2_start.y-marg-w, z));

						vpt2.push_back(CPoint2(xProfile-marg-w, z+dz));
						vpt3.push_back(CPoint3(pt2_start.x-marg-w, pt2_start.y-marg-w, z+dz));

						vpt2.push_back(CPoint2(xProfile-marg, z+dz));
						vpt3.push_back(CPoint3(pt2_start.x-marg, pt2_start.y-marg, z+dz));

						vpt2.push_back(CPoint2(xProfile-marg, z));
						vpt3.push_back(CPoint3(pt2_start.x-marg, pt2_start.y-marg, z));

						AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);

						
						sprintf(sz, "%f", z);
						DeleteEndZeros(sz);
						AddText(m_acad, sz, CPoint2(xProfile-tsh, z-0.5*Height_lin), CPoint3(pt2_start.x-tsh, pt2_start.y-tsh, z-0.5*Height_lin), Height_lin, color, param.v_scale, param.g_scale);

					}	

					z = z_ceil;
					sprintf(sz, "%f", z);
					DeleteEndZeros(sz);
					AddText(m_acad, sz, CPoint2(xProfile-tsh, z-0.5*Height_lin), CPoint3(pt2_start.x-tsh, pt2_start.y-tsh, z), Height_lin, color, param.v_scale, param.g_scale);


					// крайне правая координата разреза
					double xProfile_right = xProfile;
					for (n_cut = 0; n_cut < m_nCuts; n_cut++)
					{		
						// переходя к следующей скважине пересчитываем 
						//координату начальной скважины в координатах профиля 
						xProfile_right += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);
					}




					//// podval
					// заголовки строк подвала
					vector<string> vs;
					vs.push_back("Наименование выработки");
					vs.push_back("Расстояние между выработками, м");
					vs.push_back("Абс. отметка устья, м");
					vs.push_back("Абс. отметка уст. уровня воды, м");


					// максимальное число символов в заголовках строк подвала
					size_t max_len = 0;
					for (vector<string>::iterator it = vs.begin();
						it != vs.end(); 
						it++)
					{
						size_t len = (*it).size();
						if (max_len < len) max_len = len;
					}



					
					double z = z_floor;
					double left = max_len * Height_podvh;

					// gorizontal lines
					for (int i = 0; i < 5; i++)
					{
						bool to_close = false;

						z -= h;
						if (i == 0) 
							z_podval_ceil = z;
						z_podval_floor = z;

						vpt2.clear();
						vpt3.clear();

						vpt2.push_back(CPoint2(xProfile-marg-w-left, z));
						vpt3.push_back(CPoint3(pt2_start.x-marg-w-left, pt2_start.y-marg-w-left, z));

						vpt2.push_back(CPoint2(xProfile_right+marg, z));
						vpt3.push_back(CPoint3(pt2_finish.x+marg, pt2_finish.y+marg, z));

						AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);

						if (i > 0)
						{
							AddText(m_acad, vs[i-1].c_str(), CPoint2(xProfile-marg-left + Height_podvh, z-0.5*Height_podvh+0.5*h), CPoint3(pt2_start.x-marg-left+Height_podvh, pt2_start.y-marg-left+Height_podvh, z-0.5*Height_podvh+0.5*h), Height_podvh, color, param.v_scale, param.g_scale);
						}
					}

					//vertical lines
					{
						bool to_close = false;

						pt2_left_border.x = pt2_start.x-marg-w-left;
						pt2_left_border.y = pt2_start.y-marg-w-left;

						pt2_right_border.x = pt2_finish.x+marg;
						pt2_right_border.y = pt2_finish.y+marg;
						
						xProfile_left_border = xProfile-marg-w-left;
						xProfile_right_border = xProfile_right+marg;

						vpt2.clear();
						vpt3.clear();
						vpt2.push_back(CPoint2(xProfile_left_border, z_podval_ceil));
						vpt2.push_back(CPoint2(xProfile_left_border, z_podval_floor));
						vpt3.push_back(CPoint3(pt2_left_border.x, pt2_left_border.y, z_podval_ceil));
						vpt3.push_back(CPoint3(pt2_left_border.x, pt2_left_border.y, z_podval_floor));
						AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);

						vpt2.clear();
						vpt3.clear();
						vpt2.push_back(CPoint2(xProfile-marg, z_podval_ceil));
						vpt2.push_back(CPoint2(xProfile-marg, z_podval_floor));
						vpt3.push_back(CPoint3(pt2_start.x-marg, pt2_start.y-marg, z_podval_ceil));
						vpt3.push_back(CPoint3(pt2_start.x-marg, pt2_start.y-marg, z_podval_floor));
						AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);

						vpt2.clear();
						vpt3.clear();
						vpt2.push_back(CPoint2(xProfile_right_border, z_podval_ceil));
						vpt2.push_back(CPoint2(xProfile_right_border, z_podval_floor));
						vpt3.push_back(CPoint3(pt2_right_border.x, pt2_right_border.y, z_podval_ceil));
						vpt3.push_back(CPoint3(pt2_right_border.x, pt2_right_border.y, z_podval_floor));
						AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);
					}
				}
			}

			if (true)// nazva
			{
				CPoint2 pt_center;
				pt_center.x = pt2_left_border.x + pt2_right_border.x;
				pt_center.y = pt2_left_border.y + pt2_right_border.y;						 						
				double xCenter = 0.5 * (xProfile_left_border + xProfile_right_border);

				COLORREF color = 0;

				char sz[1024];
			
				double z = z_ceil + h;
				sprintf(sz, "%s", this->GetName().c_str());
				size_t len = strlen(sz);
				double tsh = 0.5 * Height_podvh * len;
				AddText(m_acad, sz, CPoint2(xCenter-tsh, z), 
					CPoint3(pt_center.x-tsh, pt_center.y-tsh, z), 
					Height_podvh, color, param.v_scale, param.g_scale);
	

				if (this->m_pSurfDoc)
				{
					z = z_ceil + 2 * h;
					sprintf(sz, "%s", this->m_pSurfDoc->GetName().c_str());
					len = strlen(sz);
					tsh = 0.5 * Height_podvh * len;
					AddText(m_acad, sz, CPoint2(xCenter-tsh, z), 
						CPoint3(pt_center.x-tsh, pt_center.y-tsh, z), 
						Height_podvh, color, param.v_scale, param.g_scale);
				}

			}


			if (true)//wells
			{
				COLORREF color = 0;
				// координата начальной скважины в координатах профиля
				double xProfile = 0.0;
				for (int n_drill = 0; n_drill < m_nDrills; n_drill++)
				{		
					bool to_close = false;

					// here we will put 2D points
					vector<CPoint2> vpt2;
					// here we will put 3D points
					vector<CPoint3> vpt3;

					long ID_KT = this->m_drills[n_drill].GetIdKt();

					double _dist = 0;
					double x_dist = 0;
					double y_dist = 0;

					if (n_drill < m_nDrills - 1)
					{
						_dist = Distance(m_vMapBlnProfiles[n_drill], m_vMapBlnProfiles[n_drill+1]);
						x_dist = fabs(m_vMapBlnProfiles[n_drill].x - m_vMapBlnProfiles[n_drill+1].x);
						y_dist = fabs(m_vMapBlnProfiles[n_drill].y - m_vMapBlnProfiles[n_drill+1].y);
					}

					if (ID_KT != -1 && this->m_pSurfDoc)
					{
						Well_3D * well = this->m_pSurfDoc->FindWell(ID_KT);
						if (well)
						{
							double w = 0.95 * BrokenPlane3D::m_w ;// * param.init_g_scale / param.g_scale;
							CPoint3 pt3;

							if (param.draw_wells)
							{
								to_close = false;

								vpt2.clear();
								vpt3.clear();
/*
								if (well->GetUstje(pt3))
								{
									vpt2.push_back(CPoint2(xProfile, pt3.z));
									vpt3.push_back(pt3);
								}							
*/
								if (well->GetZaboj(pt3))
								{
									vpt2.push_back(CPoint2(xProfile, pt3.z));
									vpt3.push_back(pt3);

									pt3.z = z_podval_ceil;
									vpt2.push_back(CPoint2(xProfile, z_podval_ceil));
									vpt3.push_back(pt3);

									AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);
								}


								if (well->GetUstje(pt3))
								{
									vpt2.clear();
									vpt3.clear();
									vpt2.push_back(CPoint2(xProfile+w, pt3.z));
									vpt3.push_back(CPoint3(pt3.x+w, pt3.y+w, pt3.z));
									vpt2.push_back(CPoint2(xProfile-w, pt3.z));
									vpt3.push_back(CPoint3(pt3.x-w, pt3.y-w, pt3.z));
									AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);
								}							

								if (well->GetZaboj(pt3))
								{
									vpt2.clear();
									vpt3.clear();
									vpt2.push_back(CPoint2(xProfile+w, pt3.z));
									vpt3.push_back(CPoint3(pt3.x+w, pt3.y+w, pt3.z));
									vpt2.push_back(CPoint2(xProfile-w, pt3.z));
									vpt3.push_back(CPoint3(pt3.x-w, pt3.y-w, pt3.z));
									AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);
								}
							}	

							if (param.draw_wells2)
							{
								to_close = true;

								double g = w ;//* param.init_g_scale/param.g_scale;


								vpt2.clear();
								vpt3.clear();

								if (well->GetUstje(pt3))
								{
									vpt2.push_back(CPoint2(xProfile+g, pt3.z));
									vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z));
									vpt2.push_back(CPoint2(xProfile-g, pt3.z));
									vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z));
								}							

								if (well->GetZaboj(pt3))
								{
									vpt2.push_back(CPoint2(xProfile-g, pt3.z));
									vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z));
									vpt2.push_back(CPoint2(xProfile+g, pt3.z));
									vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z));
								}
								AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);

#if 0
								if (well->GetUstje(pt3))
								{
									to_close = false;

									UINT i1, i2, i_last_visible = -1;
									i1 = 1;//first posible point
									// on enter in the cycle 
									// check if first point is vivible
									while(!well->m_vdPoints[i1].bVisible && i1 + 1 < well->GetPointsNumber())
									{
										i1++;
									}
									if (well->m_vdPoints[i1].bVisible)
									{
										i_last_visible = i1;
										i2 = i1 + 1; 
										while (i2 < well->GetPointsNumber())
										{
											// test if the second point is visible
											while(!well->m_vdPoints[i2].bVisible && i2 + 1 < well->GetPointsNumber())
											{
												i2++;
											}
											if (well->m_vdPoints[i2].bVisible)
											{
												i_last_visible = i2;

												pt3.z = well->m_vdPoints[i2].z;

												vpt2.clear();
												vpt3.clear();
												vpt2.push_back(CPoint2(xProfile+w, pt3.z));
												vpt3.push_back(CPoint3(pt3.x+w, pt3.y+w, pt3.z));
												vpt2.push_back(CPoint2(xProfile-w, pt3.z));
												vpt3.push_back(CPoint3(pt3.x-w, pt3.y-w, pt3.z));
												AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);

												if (true)//(Well_3D::s_use_sloj_names)
												{
													int i_sloj = i2;
													//printf("this->m_vstrSloiNames.size() = %d i_sloj = %d\n", this->m_vstrSloiNames.size(), i_sloj);
													if (i_sloj > 0 && i_sloj < well->m_vstrSloiNames.size())
													{									
														//Convert3D_To_2D
														//on->Projection(m_vdPoints[i2], profile, dist_to_plane);
														//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
														//if(dist_to_plane != 0.0) return;				
														
														//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
														//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
														//====== Наносим цифровую метку устья
														//SolidBrush  brush(Color(255, 0, 0, 255));
														//FontFamily  fontFamily(L"Times New Roman");
														//Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

														//const size_t wlen = 2 + 2 * strlen(well->m_vstrSloiNames[i_sloj].c_str());
														//WCHAR * wb = new WCHAR[wlen];
														//MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, well->m_vstrSloiNames[i_sloj].c_str(), -1, wb, wlen );
														//graphics.DrawString(wb, -1, &font, PointF(x1, y1), &brush);
														//delete wb;
														//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
														//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
														double Height_lin = 0.250;
														AddText(m_acad, 
															well->m_vstrSloiNames[i_sloj].c_str(), 
															CPoint2(xProfile+w, pt3.z), 
															Height_lin, color, param.v_scale, param.g_scale);
													}
												}


#if 0
												if(well->m_vvPoints[i1].bVisible && well->m_vvPoints[i2].bVisible)
												{
													COLORREF color = well->m_vColor[i2];

													//Convert3D_To_2D
													on->Projection(m_vdPoints[i1], profile, dist_to_plane);
													v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

													//Convert3D_To_2D
													on->Projection(m_vdPoints[i2], profile, dist_to_plane);
													v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

													Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
													Pen   pen(gdi_color);
														
													if (!wdli)
													{
														pen.SetWidth(width);
														graphics.DrawLine(&pen, x1, y1, x2, y2);
													}
													else
													{
														Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
														Pen   pen_border(border_color);
														switch(wdli->m_draw_mode_2d)
														{
														case wells_draw_list_item::left:
															{
																pen.SetWidth(0.5*width);	
																graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
																if(wdli->draw2d_border)
																	graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	

															}
															break;
														case wells_draw_list_item::draw_mode_2d::right:
															{
																pen.SetWidth(0.5*width);	
																graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
																if(wdli->draw2d_border)
																	graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
															}
															break;
														case wells_draw_list_item::draw_mode_2d::both:
															{
																pen.SetWidth(width);	
																graphics.DrawLine(&pen, x1, y1, x2, y2);	
																if(wdli->draw2d_border)
																{
																	graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
																	graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
																}
															}
															break;
														}

													}



													UINT i_sphere = i2;

													/*if (i_sphere == Well_3D::s_sloj_number_to_save
														|| Well_3D::s_show_all_sloi)// или если показываем все слои
													{
														//отметим слой для сохранения в виде шариков

														COLORREF sphereColor = well->m_vColor[i_sphere];
														Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
														Pen      sphere_pen(gdi_color);
													

														//Convert3D_To_2D
														on->Projection(m_vdPoints[i_sphere], profile, dist_to_plane);
														v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
														FillCircle(&graphics, x1, y1, r, sphere_color);							
														DrawCircle(&graphics, x1, y1, r, Color(255, 0,0,0));							
													}*/

													if (Well_3D::s_use_sloj_names)
													{
														int i_sloj = i2;
														//printf("this->m_vstrSloiNames.size() = %d i_sloj = %d\n", this->m_vstrSloiNames.size(), i_sloj);
														if (i_sloj > 0 && i_sloj < well->m_vstrSloiNames.size())
														{									
															//Convert3D_To_2D
															on->Projection(m_vdPoints[i2], profile, dist_to_plane);
															v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
															if(dist_to_plane != 0.0) return;				
															
															//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
															//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
															//====== Наносим цифровую метку устья
															SolidBrush  brush(Color(255, 0, 0, 255));
															FontFamily  fontFamily(L"Times New Roman");
															Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

															const size_t wlen = 2 + 2 * strlen(this->m_vstrSloiNames[i_sloj].c_str());
															WCHAR * wb = new WCHAR[wlen];
															MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->m_vstrSloiNames[i_sloj].c_str(), -1, wb, wlen );
															graphics.DrawString(wb, -1, &font, PointF(x1, y1), &brush);
															delete wb;
															//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
															//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
														}
													}
												}
#endif
											}
											i1 = i2; i2 = i1 + 1;
										}
								#if 0
										if(i_last_visible > 0)
										{
											if(this->m_vdPoints[0].bVisible && this->m_vdPoints[i_last_visible].bVisible)
											{
												if(this->m_vvPoints[0].bVisible && this->m_vvPoints[i_last_visible].bVisible)
												{
													COLORREF color;
													if (i_last_visible+1 == this->GetPointsNumber())
														color = this->m_vColor[0];
													else
														color = this->m_vColor[i_last_visible+1];

													Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
													Pen      pen(gdi_color);							
													pen.SetWidth(Well_3D::primitive_width);	

													//Convert3D_To_2D
													on->Projection(m_vdPoints[i_last_visible], profile, dist_to_plane);
													v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

													//Convert3D_To_2D
													on->Projection(m_vdPoints[0], profile, dist_to_plane);//zaboj altitude
													v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

													graphics.DrawLine(&pen, x1, y1, x2, y2);						}
											}
										}
								#endif
									}
								}
#endif
								for(vector<wells_draw_list_item *>::reverse_iterator it = Well_3D::wells_draw_list.rbegin();it != Well_3D::wells_draw_list.rend(); it++)
								{
									if ( (*it) )
									{
										WellColomn * wc = well->FindWellColomn((*it)->id);
										double Height_lin = 0.50;
										if (wc)	wc->DrawAcad(m_acad, xProfile, w, Height_lin, color, param.v_scale, param.g_scale, well);
									}
								}
							}


							if (well->GetUstje(pt3))
							{
								to_close = false;

								char str[128];
								double tsh;
								size_t len;

								vpt2.clear();
								vpt3.clear();

								// отрисуем вертикальные рисочки во второй строке подвала
								double z = z_podval_ceil - 2*h;
								vpt2.push_back(CPoint2(xProfile, z));
								vpt3.push_back(CPoint3(pt3.x, pt3.y, z));

								z = z_podval_ceil - h;
								vpt2.push_back(CPoint2(xProfile, z));
								vpt3.push_back(CPoint3(pt3.x, pt3.y, z));

								AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);
								if (n_drill < m_nDrills - 1 && this->m_drills[n_drill+1].GetIdKt() != -1)
								{
									// расстояние между выработками во второй строке подвала
									long d = long(_dist * 100.0);
									double dd = double(d)/100.0;
									sprintf(str, "%f\0", dd);
									DeleteEndZeros(str);

									z = z_podval_ceil - 2*h;
									len = strlen(str);
									tsh = Height_podv2 * (0.5 * double(len) - 1.0);

									AddText(m_acad, 
										str, 
										CPoint2(xProfile + 0.5*_dist - tsh, 
											z - 0.5*Height_podv2 + 0.5*h), 
										CPoint3(pt3.x + 0.5*x_dist - tsh,
											pt3.y + 0.5*y_dist - tsh, 
											z - 0.5*Height_podv2 + 0.5*h), 
										Height_podv2, color, param.v_scale, param.g_scale);								
								}

								// наименование выработки в первой строке подвала
								string name = well->GetName();

								z = z_podval_ceil - h;
								len = name.size();
								tsh = Height_podv1 * (0.5 * double(len) - 1.0);

								AddText(m_acad, 
									name.c_str(), 
									CPoint2(xProfile - tsh, 
										z - 0.5*Height_podv1 + 0.5*h), 
									CPoint3(pt3.x - tsh,
										pt3.y - tsh, 
										z - 0.5*Height_podv1 + 0.5*h), 
									Height_podv1, color, param.v_scale, param.g_scale);

								//  абсолютная отметка устья в третьей строке
								sprintf(str, "%f", pt3.z);
								DeleteEndZeros(str);

								z = z_podval_ceil - 3*h;
								len = strlen(str);
								tsh = Height_podv3 * (0.5 * double(len) - 1.0);

								AddText(m_acad, 
									str, 
									CPoint2(xProfile - tsh, 
										z - 0.5*Height_podv3 + 0.5*h), 
									CPoint3(pt3.x - tsh,
										pt3.y - tsh, 
										z - 0.5*Height_podv3 + 0.5*h), 
									Height_podv3, color, param.v_scale, param.g_scale);

								// абсолютная отметка установившегося уровня воды
								int n_gorizonts = well->m_db_voda.data1.size();
								int n = 0;
								for (vector<db_voda_data>::iterator it = well->m_db_voda.data1.begin();
									it != well->m_db_voda.data1.end(); it++)
								{
									sprintf(str, "%f\0", pt3.z - (*it).hv_v);
									DeleteEndZeros(str);
									


									z = z_podval_ceil - 4*h;
									len = strlen(str);
									tsh = (Height_podv4/n_gorizonts) * (0.5 * double(len) - 1.0);

									AddText(m_acad, 
										str, 
										CPoint2(xProfile - tsh, 
											z - 0.5*(Height_podv4/n_gorizonts) + (0.5+n)*(h/n_gorizonts)), 
										CPoint3(pt3.x - tsh,
											pt3.y - tsh, 
											z - 0.5*(Height_podv4/n_gorizonts) + (0.5+n)*(h/n_gorizonts)), 
										(Height_podv4/n_gorizonts), color, param.v_scale, param.g_scale);

									n++;
								}

							}
						}
					}

					if (n_drill < m_nDrills - 1)
					{
						// переходя к следующей скважине пересчитываем 
						//координату начальной скважины в координатах профиля 
						xProfile += _dist;
					}
				}

			}





			int n_surf;
			CPoint3 pt3;
			bool reverse;
			CPoint3 
				next_drill_point,
				pre_drill_point,
				last_line_point,
				first_line_point;

			if (param.draw_sloi_lines)//(nFilterIndex == 3) //Sloi lines as one file Golden Software Blanking
			{
				bool to_close = false;
				for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
				{
					//string hatchacad = "";
					double angle = 0.0;
					double scale = 0.0;
					long id_umpoz = this->m_broken_lines[n_surf].id_umpoz;
					map<long, umpoz_data>::iterator found_umpoz = this->m_pSurfDoc->m_db_umpoz.data1.find(id_umpoz);
					if (found_umpoz != this->m_pSurfDoc->m_db_umpoz.data1.end())
					{
						//(*found_umpoz).second.id_umpoz;
						//(*found_umpoz).second.umpoz;
//						hatchacad	= (*found_umpoz).second.hatchacad;
						angle		= (*found_umpoz).second.angle;
						scale		= (*found_umpoz).second.scale;
					}

					scale *= param.hatch_scale;

					COLORREF color = 0;
					bool use_color_from_id_umpoz = false;
					long id_umpoz_for_color = 0;

					// координата начальной скважины в координатах профиля
					//char * name = NULL; //= this->m_broken_lines[n_surf].GetName().c_str();
					double xProfile = 0.0;
					for (n_cut = 0; n_cut < m_nCuts; n_cut++)
					{						
						// here we will put 2D points
						vector<CPoint2> vpt2;
						vpt2.resize(0);
						// here we will put 3D points
						vector<CPoint3> vpt3;
						vpt3.resize(0);

						//color = this->m_broken_lines[n_surf].m_lines[n_cut].GetColor();
						color = 0;
						switch (this->m_broken_lines[n_surf].m_lines[n_cut].id_umpoz)
						{							
						case -2://voda
							{
								use_color_from_id_umpoz = true;
								id_umpoz_for_color = -2;
							}
							break;
						}


						//name = (char*) this->m_broken_lines[n_surf].m_lines[n_cut].GetName().c_str();
						// число точек в текущем line
						CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
						//add 1-st point
						if(m_pointsDrillSloi[n_cut][n_surf].GetPointsNumber() > 0)
						{
							pt3 = m_pointsDrillSloi[n_cut][n_surf].m_vdPoints[0];
							if (pt3.bVisible)
							{
								vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
								vpt3.push_back(pt3);
							}
						}
						// добавляем верхнюю линию, 
						// но сначала определяем прямой или обратный порядок добавления линии 
						// а на случай если в полигоне или в линии нет точек 
						// инициализируем флаг порядка добавления линии
						reverse = false;
						bool determined = false;
						if (m_pointsDrillSloi[n_cut][n_surf].GetPointsNumber() > 0 &&
							this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0)
						{
							pre_drill_point		= m_pointsDrillSloi	[n_cut][n_surf].GetFirstDocumentPoint();
							first_line_point	= this->m_broken_lines[n_surf].m_lines[n_cut].GetFirstDocumentPoint();
							last_line_point		= this->m_broken_lines[n_surf].m_lines[n_cut].GetLastDocumentPoint();
							double distance_to_last  = Distance(pre_drill_point, last_line_point);
							double distance_to_first = Distance(pre_drill_point, first_line_point);
							reverse = distance_to_last < distance_to_first;
							determined = true;
						}
						else
						{
							if (m_pointsDrillSloi[n_cut+1][n_surf].GetPointsNumber() > 0 &&
								this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0)
							{
								next_drill_point	= m_pointsDrillSloi	[n_cut+1][n_surf].GetFirstDocumentPoint();
								first_line_point	= this->m_broken_lines[n_surf].m_lines[n_cut].GetFirstDocumentPoint();
								last_line_point		= this->m_broken_lines[n_surf].m_lines[n_cut].GetLastDocumentPoint();
								double distance_to_last  = Distance(next_drill_point, last_line_point);
								double distance_to_first = Distance(next_drill_point, first_line_point);
								reverse = distance_to_last > distance_to_first;

								determined = true;
							}
						}
						if (determined)
						{
							// добавляем линию
							if (reverse)
							{
								for (int i = this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber()-1; i >= 0; i--)
								{
									pt3 = this->m_broken_lines[n_surf].m_lines[n_cut].m_vdPoints[i];
									if (pt3.bVisible)
									{
										vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
										vpt3.push_back(pt3);
									}
								}
							}
							else
							{
								for (int i = 0; i < this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber(); i++)
								{
									pt3 = this->m_broken_lines[n_surf].m_lines[n_cut].m_vdPoints[i];
									if (pt3.bVisible)
									{
										vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
										vpt3.push_back(pt3);
									}
								}
							}
						}
						// переходя к следующей скважине пересчитываем 
						//координату начальной скважины в координатах профиля 
						xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);

				//add last point
				if(m_pointsDrillSloi[n_cut+1][n_surf].GetPointsNumber() > 0)
				{
					pt3 = m_pointsDrillSloi[n_cut+1][n_surf].m_vdPoints[0];
					if (pt3.bVisible)
					{
						vpt2.push_back(CPoint2(xProfile, pt3.z));
						vpt3.push_back(pt3);
					}
				}

				if (use_color_from_id_umpoz)
				{
					switch (id_umpoz_for_color)
					{
					case -2:
						{
							color = RGB(0,0,255);
						}
						break;
					}
				}
				switch(BrokenPlane3D::sprData.export_coordinate_type)
				{
				case SAVE_PROFILE_WITH_PROFILE_LEN:
					{
						if (vpt2.size())
						{		
							//fprintf(bln, "%d,%d \"%s\"\n", vpt2.size(), 0, name);
							//vector<CPoint2>::iterator itr;
							//for (itr = vpt2.begin(); itr != vpt2.end(); itr++)
							//{
							//	fprintf(bln, "%lf,%lf\n", itr->x, itr->y);
							//}

							//if (hatchacad.size())
							//	AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale);
							//else
								AddPolyLine(m_acad, vpt2, to_close, color, param.v_scale, param.g_scale);	
						}

					}
					break;
				case SAVE_PROFILE_WITH_NORTH_PROJECTION:
					{
						if (vpt3.size())
						{		
							/*fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
							vector<CPoint3>::iterator itr;
							for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->y, itr->z);
							}*/

							//if (hatchacad.size())
							//	AddHatchPolyLine(m_acad, SAVE_PROFILE_WITH_NORTH_PROJECTION, vpt3, color, hatchacad, angle, scale);
							//else
								AddPolyLine(m_acad, SAVE_PROFILE_WITH_NORTH_PROJECTION, vpt3, to_close, color, param.v_scale, param.g_scale);	
						}
					}
					break;
				case SAVE_PROFILE_WITH_EAST_PROJECTION:
					{
						if (vpt3.size())
						{		
							/*fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
							vector<CPoint3>::iterator itr;
							for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->x, itr->z);
							}*/

							//if (hatchacad.size())
							//	AddHatchPolyLine(m_acad, SAVE_PROFILE_WITH_EAST_PROJECTION, vpt3, color, hatchacad, angle, scale);
							//else
								AddPolyLine(m_acad, SAVE_PROFILE_WITH_EAST_PROJECTION, vpt3, to_close, color, param.v_scale, param.g_scale);	
						}
					}
					break;
				}
					}
				}
			}
			
			if (param.draw_faults)//(nFilterIndex == 4) //Faults as one file Golden Software Blanking
			{
				bool to_close = false;
				COLORREF color = RGB(255,0,0);
				for (n_fault = 0; n_fault < m_nFaults; n_fault++)
				{
					// координата начальной скважины в координатах профиля
					double xProfile = 0.0;
					for (n_cut = 0; n_cut < m_nCuts; n_cut++)
					{
						// here we will put 2D points
						vector<CPoint2> vpt2;
						vpt2.resize(0);
						// here we will put 3D points
						vector<CPoint3> vpt3;
						vpt3.resize(0);

						// число точек в текущем line
						CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
						// добавляем линию
						for (int i = 0; i < this->m_broken_fault_lines[n_fault].m_lines[n_cut].GetPointsNumber(); i++)
						{
							pt3 = this->m_broken_fault_lines[n_fault].m_lines[n_cut].m_vdPoints[i];
							if (pt3.bVisible)
							{
								vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
								vpt3.push_back(pt3);
							}
						}	
						// переходя к следующей скважине пересчитываем 
						// координату начальной скважины в координатах профиля 
						xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);

						//const char * name = this->m_broken_fault_lines[n_fault].m_lines[n_cut].GetName().c_str();

						switch(BrokenPlane3D::sprData.export_coordinate_type)
						{
						case SAVE_PROFILE_WITH_PROFILE_LEN:
							{
								if (vpt2.size())
								{		
									/*fprintf(bln, "%d,%d \"%s\"\n", vpt2.size(), 0, name);
									vector<CPoint2>::iterator itr;
									for (itr = vpt2.begin(); itr != vpt2.end(); itr++)
									{
										fprintf(bln, "%lf,%lf\n", itr->x, itr->y);
									}*/
																	
									//if (hatchacad.size())
									//	AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale);
									//else
										AddPolyLine(m_acad, vpt2, to_close, color, param.v_scale, param.g_scale);	

								}
							}
							break;
						case SAVE_PROFILE_WITH_NORTH_PROJECTION:
							{
								if (vpt3.size())
								{		
									/*fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
									vector<CPoint3>::iterator itr;
									for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
									{
										fprintf(bln, "%lf,%lf\n", itr->y, itr->z);
									}*/
									//if (hatchacad.size())
									//	AddHatchPolyLine(m_acad, SAVE_PROFILE_WITH_NORTH_PROJECTION, vpt3, color, hatchacad, angle, scale);
									//else
										AddPolyLine(m_acad, SAVE_PROFILE_WITH_NORTH_PROJECTION, vpt3, to_close, color, param.v_scale, param.g_scale);	
								}
							}
							break;
						case SAVE_PROFILE_WITH_EAST_PROJECTION:
							{
								if (vpt3.size())
								{		
									/*fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
									vector<CPoint3>::iterator itr;
									for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
									{
										fprintf(bln, "%lf,%lf\n", itr->x, itr->z);
									}*/
									//if (hatchacad.size())
									//	AddHatchPolyLine(m_acad, SAVE_PROFILE_WITH_EAST_PROJECTION, vpt3, color, hatchacad, angle, scale);
									//else
										AddPolyLine(m_acad, SAVE_PROFILE_WITH_EAST_PROJECTION, vpt3, to_close, color, param.v_scale, param.g_scale);	
								}
							}
							break;
						}
					}
				}
			}	

			if (param.draw_catches)//(nFilterIndex == 5) //Catches as one file Golden Software Blanking
			{
				bool to_close = false;
				COLORREF color = RGB(0,0,255);
				for (n_catch = 0; n_catch < m_nCatches; n_catch++)
				{
					// координата начальной скважины в координатах профиля
					double xProfile = 0.0;
					for (n_cut = 0; n_cut < m_nCuts; n_cut++)
					{
						// here we will put 2D points
						vector<CPoint2> vpt2;
						vpt2.resize(0);
						// here we will put 3D points
						vector<CPoint3> vpt3;
						vpt3.resize(0);

						// число точек в текущем line
						CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
						// добавляем линию
						for (int i = 0; i < this->m_broken_catch_lines[n_catch].m_lines[n_cut].GetPointsNumber(); i++)
						{
							pt3 = this->m_broken_catch_lines[n_catch].m_lines[n_cut].m_vdPoints[i];
							if (pt3.bVisible)
							{
								vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
								vpt3.push_back(pt3);
							}
						}	
						// переходя к следующей скважине пересчитываем 
						// координату начальной скважины в координатах профиля 
						xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);

						//const char * name = this->m_broken_catch_lines[n_fault].m_lines[n_cut].GetName().c_str();
						
						switch(BrokenPlane3D::sprData.export_coordinate_type)
						{
						case SAVE_PROFILE_WITH_PROFILE_LEN:
							{
								if (vpt2.size())
								{		
									/*fprintf(bln, "%d,%d \"%s\"\n", vpt2.size(), 0, name);
									vector<CPoint2>::iterator itr;
									for (itr = vpt2.begin(); itr != vpt2.end(); itr++)
									{
										fprintf(bln, "%lf,%lf\n", itr->x, itr->y);
									}*/
										
									AddPolyLine(m_acad, vpt2, to_close, color, param.v_scale, param.g_scale);	
								}
							}
							break;
						case SAVE_PROFILE_WITH_NORTH_PROJECTION:
							{
								if (vpt3.size())
								{		
									/*fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
									vector<CPoint3>::iterator itr;
									for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
									{
										fprintf(bln, "%lf,%lf\n", itr->y, itr->z);
									}*/
																			
									AddPolyLine(m_acad, SAVE_PROFILE_WITH_NORTH_PROJECTION, vpt3, to_close, color, param.v_scale, param.g_scale);	

								}
							}
							break;
						case SAVE_PROFILE_WITH_EAST_PROJECTION:
							{
								if (vpt3.size())
								{		
									/*fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
									vector<CPoint3>::iterator itr;
									for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
									{
										fprintf(bln, "%lf,%lf\n", itr->x, itr->z);
									}*/
																			
									AddPolyLine(m_acad, SAVE_PROFILE_WITH_EAST_PROJECTION, vpt3, to_close, color, param.v_scale, param.g_scale);	

								}
							}
							break;
						}
					}
				}
			}	

			if (param.draw_colomn)
			{
				double x_draw_colomn_0 = xProfile_right_border + marg;
				double y_draw_colomn_0 = z_podval_ceil;

				vector<CPoint2> vpt;
				vpt.push_back(CPoint2(0,  0));
				vpt.push_back(CPoint2(0, 0.9));
				vpt.push_back(CPoint2(3*param.init_g_scale/param.g_scale, 0.9));
				vpt.push_back(CPoint2(3*param.init_g_scale/param.g_scale, 0));


				GeoColomn * colomn = this->m_pSurfDoc->FindGeoColomn(GeoElement::type::engineer_geological);
				if (colomn) 
				{
					int j = 0;
					for (map<string, GeoElement*>::iterator it = colomn->geo_elements.begin(); it != colomn->geo_elements.end(); it++)
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
								long ID_UMPOZ = eng->id_umpoz;
								long id_ige = eng->GetKeyID();
								string ige = eng->GetKey();

								string GrMainNazvaR = "ИГЭ " + ige + " " + eng->GetName();

								SetUmPoz setUmPoz(&this->m_pSurfDoc->GetLabDoc()->m_database);	
								setUmPoz.m_strFilter.Format("");
								setUmPoz.m_strSort.Format("");
								if ( setUmPoz.Open(CRecordset::dynaset) )
								{					

									if (!setUmPoz.IsBOF())
									{
										setUmPoz.MoveFirst();
										while (!setUmPoz.IsEOF())
										{
											if (setUmPoz.m_ID_UMPOZ == ID_UMPOZ)
											{
												string hatchacad = setUmPoz.m_HATCHACAD;
												double angle = setUmPoz.m_Angle;
												double scale = setUmPoz.m_Scale * param.hatch_scale;

												vector<CPoint2> vpt2;
												for (int i = 0; i < 4; i++)
												{
													vpt2.push_back(CPoint2(x_draw_colomn_0 + vpt[i].x, y_draw_colomn_0 + vpt[i].y - 1.0*j));
												}
												COLORREF color = eng->GetColor();
												AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale, param.v_scale, param.g_scale);

												double Height_lin = 0.50;
												color = 0;
												AddText(m_acad, GrMainNazvaR.c_str(), CPoint2(x_draw_colomn_0 + 4*param.init_g_scale/param.g_scale, y_draw_colomn_0 - 1.0*j+0.15), Height_lin, color, param.v_scale, param.g_scale);

												break;
											}
											setUmPoz.MoveNext();
										}
									}
									j++;
							
								}					
							}
						}
					}
				}
			}

			m_acad.m_document.SaveAs(lpstrFile, COleVariant(long(12)));
/*

public enum AcSaveAsType
{
ac2000_dwg = 12,
ac2000_dxf = 13,
ac2000_Template = 14,
ac2004_dwg = 24,
ac2004_dxf = 25,
ac2004_Template = 26,
ac2007_dwg = 36,
ac2007_dxf = 37,
ac2007_Template = 38,
acNative = 36,
acR12_dxf = 1,
acR13_dwg = 4,
acR13_dxf = 5,
acR14_dwg = 8,
acR14_dxf = 9,
acR15_dwg = 12,
acR15_dxf = 13,
acR15_Template = 14,
acR18_dwg = 24,
acR18_dxf = 25,
acR18_Template = 26,
acUnknown = -1
}

*/
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		m_acad.AcadOleRelease();
	}
	else
		printf("!!!!! m_acad.IsApplicationDispatch()\n");
}


extern char directory[];

void BrokenPlane3D::SavingAsRazrez(FILE * bln, Poligon3D & poli, int n_sloi, int n_cut, double xProfile)
{
	// число точек в текущем полигоне плюс одна
	int len = poli.GetPointsNumber()
		+ 1;
	bool bChecked = poli.m_bChecked;
	if (bChecked && len > 1)
	{
		fprintf(bln, "%d,%d\n", len, 0);
		switch(BrokenPlane3D::sprData.export_coordinate_type)
		{
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
				for (int i = 0; i < poli.GetPointsNumber(); i++)
				{
					CPoint3 pt3 = poli.GetDocumentPoint(i);
					fprintf(bln, "%lf,%lf\n", xProfile + Distance(pt2,pt3), pt3.z);
				}
				CPoint3 pt3 = poli.GetFirstDocumentPoint();
				fprintf(bln, "%lf,%lf\n", xProfile + Distance(pt2,pt3), pt3.z);
			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{									
				for (int i = 0; i < poli.GetPointsNumber(); i++)
				{
					CPoint3 pt3 = poli.GetDocumentPoint(i);
					fprintf(bln, "%lf,%lf\n", pt3.y, pt3.z);
				}
				CPoint3 pt3 = poli.GetFirstDocumentPoint();
				fprintf(bln, "%lf,%lf\n", pt3.y, pt3.z);
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				for (int i = 0; i < poli.GetPointsNumber(); i++)
				{
					CPoint3 pt3 = poli.GetDocumentPoint(i);
					fprintf(bln, "%lf,%lf\n", pt3.x, pt3.z);
				}
				CPoint3 pt3 = poli.GetFirstDocumentPoint();
				fprintf(bln, "%lf,%lf\n", pt3.x, pt3.z);
			}
			break;
		}
	}
}

void BrokenPlane3D::SaveAsRazres()
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     
		TEXT("Poligones as many files Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("Poligones as one file Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("Sloi lines as one file Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("Faults as one file Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("Catches as one file Golden Software Blanking (*.bln)\0*.bln\0")
                         TEXT("All Files (*.*)\0*.*\0");

	sprintf(lpstrFile, "%s\\razrez", directory);
	DWORD nFilterIndex = 0;
	if (S_OK != SaveProfDlg(0, lpstrFile, filter, nFilterIndex, BrokenPlane3D::sprData))
		return;



	int n_cut, n_sloi, n_fault, n_catch;
	if (nFilterIndex == 1)//Poligones as many files Golden Software Blanking
	{
		char base_name[256];
		char name[256];
		strcpy(base_name, lpstrFile);
		char * p = strrchr(base_name, '.');
		if (p) *p = '\0';
		for (n_sloi = 0; n_sloi < m_nSloi; n_sloi++)
		{
			sprintf(name, "%s%02d.bln", base_name, n_sloi + 1);
			FILE *bln;
			bln = fopen(name,"wt");
			if (!bln)
			{
				char str[255];
				sprintf(str, "Can not create file %s", lpstrFile);
				MessageBox(0, str, "Cutline Save As Razres", MB_OK);
				return;
			}
			// координата начальной скважины в координатах профиля
			double xProfile = 0.0;
			for (n_cut = 0; n_cut < m_nCuts; n_cut++)
			{
#if USE_UNVISIBLE_CUTTING
				for (size_t i = 0; i < m_polySloi[n_sloi].m_poligones[n_cut].Size(); i++)
				{
					SavingAsRazrez(bln, m_polySloi[n_sloi].m_poligones[n_cut][i], n_sloi, n_cut, xProfile);
				}
#else
				SavingAsRazrez(bln, m_polySloi[n_sloi].m_poligones[n_cut], n_sloi, n_cut, xProfile);
#endif
				// переходя к следующей скважине пересчитываем 
				//координату начальной скважины в координатах профиля 
				xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);
			}
			fclose(bln);
		}
		return;
	}
	FILE *bln;
	bln = fopen(lpstrFile,"wt");
	if (!bln)
	{
		char str[255];
		sprintf(str, "Can not create file %s", lpstrFile);
		MessageBox(0, str, "Cutline Save As Razres", MB_OK);
		return;
	}
	if (nFilterIndex == 2)//Poligones as one file Golden Software Blanking
	{
		for (n_sloi = 0; n_sloi < m_nSloi; n_sloi++)
		{
			// координата начальной скважины в координатах профиля
			double xProfile = 0.0;
			for (n_cut = 0; n_cut < m_nCuts; n_cut++)
			{

#if USE_UNVISIBLE_CUTTING
				for (size_t i = 0; i < m_polySloi[n_sloi].m_poligones[n_cut].Size(); i++)
				{
					SavingAsRazrez(bln, m_polySloi[n_sloi].m_poligones[n_cut][i], n_sloi, n_cut, xProfile);
				}
#else
				SavingAsRazrez(bln, m_polySloi[n_sloi].m_poligones[n_cut], n_sloi, n_cut, xProfile);
#endif
				// переходя к следующей скважине пересчитываем 
				//координату начальной скважины в координатах профиля 
				xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);
			}
		}
	}
	int n_surf;
	CPoint3 pt3;
	bool reverse;
	CPoint3 
		next_drill_point,
		pre_drill_point,
		last_line_point,
		first_line_point;
	if (nFilterIndex == 3) //Sloi lines as one file Golden Software Blanking
	{
		for (n_surf = 0; n_surf < m_nSurfs; n_surf++)
		{
			// here we will put 2D points
			vector<CPoint2> vpt2;
			vpt2.resize(0);
			// here we will put 3D points
			vector<CPoint3> vpt3;
			vpt3.resize(0);
			// координата начальной скважины в координатах профиля
			char * name = NULL; //= this->m_broken_lines[n_surf].GetName().c_str();
			double xProfile = 0.0;
			for (n_cut = 0; n_cut < m_nCuts; n_cut++)
			{
				name = (char*) this->m_broken_lines[n_surf].m_lines[n_cut].GetName().c_str();
				// число точек в текущем line
				CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
				//add 1-st point
				if(m_pointsDrillSloi[n_cut][n_surf].GetPointsNumber() > 0)
				{
					pt3 = m_pointsDrillSloi[n_cut][n_surf].m_vdPoints[0];
					if (pt3.bVisible)
					{
						vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
						vpt3.push_back(pt3);
					}
				}
				// добавляем верхнюю линию, 
				// но сначала определяем прямой или обратный порядок добавления линии 
				// а на случай если в полигоне или в линии нет точек 
				// инициализируем флаг порядка добавления линии
				reverse = false;
				bool determined = false;
				if (m_pointsDrillSloi[n_cut][n_surf].GetPointsNumber() > 0 &&
					this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0)
				{
					pre_drill_point		= m_pointsDrillSloi	[n_cut][n_surf].GetFirstDocumentPoint();
					first_line_point	= this->m_broken_lines[n_surf].m_lines[n_cut].GetFirstDocumentPoint();
					last_line_point		= this->m_broken_lines[n_surf].m_lines[n_cut].GetLastDocumentPoint();
					double distance_to_last  = Distance(pre_drill_point, last_line_point);
					double distance_to_first = Distance(pre_drill_point, first_line_point);
					reverse = distance_to_last < distance_to_first;
					determined = true;

				}
				else
				{
					if (m_pointsDrillSloi[n_cut+1][n_surf].GetPointsNumber() > 0 &&
						this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber() > 0)
					{
						next_drill_point	= m_pointsDrillSloi	[n_cut+1][n_surf].GetFirstDocumentPoint();
						first_line_point	= this->m_broken_lines[n_surf].m_lines[n_cut].GetFirstDocumentPoint();
						last_line_point		= this->m_broken_lines[n_surf].m_lines[n_cut].GetLastDocumentPoint();
						double distance_to_last  = Distance(next_drill_point, last_line_point);
						double distance_to_first = Distance(next_drill_point, first_line_point);
						reverse = distance_to_last > distance_to_first;

						determined = true;

					}
				}
				if (determined)
				{
					// добавляем линию
					if (reverse)
					{
						for (int i = this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber()-1; i >= 0; i--)
						{
							pt3 = this->m_broken_lines[n_surf].m_lines[n_cut].m_vdPoints[i];
							if (pt3.bVisible)
							{
								vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
								vpt3.push_back(pt3);
							}
						}
					}
					else
					{
						for (int i = 0; i < this->m_broken_lines[n_surf].m_lines[n_cut].GetPointsNumber(); i++)
						{
							pt3 = this->m_broken_lines[n_surf].m_lines[n_cut].m_vdPoints[i];
							if (pt3.bVisible)
							{
								vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
								vpt3.push_back(pt3);
							}
						}
					}
				}
				// переходя к следующей скважине пересчитываем 
				//координату начальной скважины в координатах профиля 
				xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);
			}
			//add last point
			if(m_pointsDrillSloi[m_nCuts][n_surf].GetPointsNumber() > 0)
			{
				pt3 = m_pointsDrillSloi[m_nCuts][n_surf].m_vdPoints[0];
				if (pt3.bVisible)
				{
					vpt2.push_back(CPoint2(xProfile, pt3.z));
					vpt3.push_back(pt3);
				}
			}
			switch(BrokenPlane3D::sprData.export_coordinate_type)
			{
			case SAVE_PROFILE_WITH_PROFILE_LEN:
				{
					if (vpt2.size())
					{		
						fprintf(bln, "%d,%d \"%s\"\n", vpt2.size(), 0, name);
						vector<CPoint2>::iterator itr;
						for (itr = vpt2.begin(); itr != vpt2.end(); itr++)
						{
							fprintf(bln, "%lf,%lf\n", itr->x, itr->y);
						}
					}
				}
				break;
			case SAVE_PROFILE_WITH_NORTH_PROJECTION:
				{
					if (vpt3.size())
					{		
						fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
						vector<CPoint3>::iterator itr;
						for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
						{
							fprintf(bln, "%lf,%lf\n", itr->y, itr->z);
						}
					}
				}
				break;
			case SAVE_PROFILE_WITH_EAST_PROJECTION:
				{
					if (vpt3.size())
					{		
						fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
						vector<CPoint3>::iterator itr;
						for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
						{
							fprintf(bln, "%lf,%lf\n", itr->x, itr->z);
						}
					}
				}
				break;
			}
		}
	}
	
	if (nFilterIndex == 4) //Faults as one file Golden Software Blanking
	{
		for (n_fault = 0; n_fault < m_nFaults; n_fault++)
		{
			// координата начальной скважины в координатах профиля
			double xProfile = 0.0;
			for (n_cut = 0; n_cut < m_nCuts; n_cut++)
			{
				// here we will put 2D points
				vector<CPoint2> vpt2;
				vpt2.resize(0);
				// here we will put 3D points
				vector<CPoint3> vpt3;
				vpt3.resize(0);

				// число точек в текущем line
				CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
				// добавляем линию
				for (int i = 0; i < this->m_broken_fault_lines[n_fault].m_lines[n_cut].GetPointsNumber(); i++)
				{
					pt3 = this->m_broken_fault_lines[n_fault].m_lines[n_cut].m_vdPoints[i];
					if (pt3.bVisible)
					{
						vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
						vpt3.push_back(pt3);
					}
				}	
				// переходя к следующей скважине пересчитываем 
				// координату начальной скважины в координатах профиля 
				xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);

				const char * name = this->m_broken_fault_lines[n_fault].m_lines[n_cut].GetName().c_str();

				switch(BrokenPlane3D::sprData.export_coordinate_type)
				{
				case SAVE_PROFILE_WITH_PROFILE_LEN:
					{
						if (vpt2.size())
						{		
							fprintf(bln, "%d,%d \"%s\"\n", vpt2.size(), 0, name);
							vector<CPoint2>::iterator itr;
							for (itr = vpt2.begin(); itr != vpt2.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->x, itr->y);
							}
						}
					}
					break;
				case SAVE_PROFILE_WITH_NORTH_PROJECTION:
					{
						if (vpt3.size())
						{		
							fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
							vector<CPoint3>::iterator itr;
							for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->y, itr->z);
							}
						}
					}
					break;
				case SAVE_PROFILE_WITH_EAST_PROJECTION:
					{
						if (vpt3.size())
						{		
							fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
							vector<CPoint3>::iterator itr;
							for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->x, itr->z);
							}
						}
					}
					break;
				}
			}
		}
	}	
	if (nFilterIndex == 5) //Catches as one file Golden Software Blanking
	{
		for (n_catch = 0; n_catch < m_nCatches; n_catch++)
		{
			// координата начальной скважины в координатах профиля
			double xProfile = 0.0;
			for (n_cut = 0; n_cut < m_nCuts; n_cut++)
			{
				// here we will put 2D points
				vector<CPoint2> vpt2;
				vpt2.resize(0);
				// here we will put 3D points
				vector<CPoint3> vpt3;
				vpt3.resize(0);

				// число точек в текущем line
				CPoint2 pt2 = m_vMapBlnProfiles[n_cut]; 
				// добавляем линию
				for (int i = 0; i < this->m_broken_catch_lines[n_catch].m_lines[n_cut].GetPointsNumber(); i++)
				{
					pt3 = this->m_broken_catch_lines[n_catch].m_lines[n_cut].m_vdPoints[i];
					if (pt3.bVisible)
					{
						vpt2.push_back(CPoint2(xProfile + Distance(pt2,pt3), pt3.z));
						vpt3.push_back(pt3);
					}
				}	
				// переходя к следующей скважине пересчитываем 
				// координату начальной скважины в координатах профиля 
				xProfile += Distance(m_vMapBlnProfiles[n_cut], m_vMapBlnProfiles[n_cut+1]);

				const char * name = this->m_broken_catch_lines[n_fault].m_lines[n_cut].GetName().c_str();
				
				switch(BrokenPlane3D::sprData.export_coordinate_type)
				{
				case SAVE_PROFILE_WITH_PROFILE_LEN:
					{
						if (vpt2.size())
						{		
							fprintf(bln, "%d,%d \"%s\"\n", vpt2.size(), 0, name);
							vector<CPoint2>::iterator itr;
							for (itr = vpt2.begin(); itr != vpt2.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->x, itr->y);
							}
						}
					}
					break;
				case SAVE_PROFILE_WITH_NORTH_PROJECTION:
					{
						if (vpt3.size())
						{		
							fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
							vector<CPoint3>::iterator itr;
							for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->y, itr->z);
							}
						}
					}
					break;
				case SAVE_PROFILE_WITH_EAST_PROJECTION:
					{
						if (vpt3.size())
						{		
							fprintf(bln, "%d,%d \"%s\"\n", vpt3.size(), 0, name);
							vector<CPoint3>::iterator itr;
							for (itr = vpt3.begin(); itr != vpt3.end(); itr++)
							{
								fprintf(bln, "%lf,%lf\n", itr->x, itr->z);
							}
						}
					}
					break;
				}
			}
		}
	}	
	fclose(bln);

}

void BrokenPlane3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "BrokenPlane3D" , 0);

}

bool BrokenPlane3D::ColorDialog(void)
{
	return false;
}

COLORREF BrokenPlane3D::GetColor(void)
{
	return COLORREF();
}

void BrokenPlane3D::SetColor(COLORREF color)
{
}
bool BrokenPlane3D::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);
	return false;
}

DWORD BrokenPlane3D::Serialize(Archive& ar)
{
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
Archive& operator <<(Archive& ar, BrokenPlane3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 2:
		{
			ar << ob.m_nCatches;
			ar << ob.m_broken_catch_lines;	ar << ob.m_broken_catch_lines_ObjectList;
		}
		//do not break!!!
	case 1:
		{
			ar << ob.m_nCuts;
			ar << ob.m_nDrills;
			ar << ob.m_nSloi;
			ar << ob.m_nSurfs;
			ar << ob.m_nFaults;

			// Objects' vectors
			ar << ob.m_colorsSloi;
			ar << ob.m_drills;					ar << ob.m_drills_ObjectList;
			ar << ob.m_broken_lines;			ar << ob.m_broken_lines_ObjectList;
			ar << ob.m_broken_fault_lines;		ar << ob.m_broken_fault_lines_ObjectList;
			ar << ob.m_pointsDrillSloi;			ar << ob.m_pointsDrillSloi_ObjectList;
			ar << ob.m_polySloi;				ar << ob.m_polySloi_ObjectList;

			// CPoint2
			ar << ob.m_vMapBlnProfiles;

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
Archive& operator >>(Archive& ar, BrokenPlane3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 2:
		{
			ar >> ob.m_nCatches;
			ar >> ob.m_broken_catch_lines;	ar >> ob.m_broken_catch_lines_ObjectList;
			ob.m_broken_catch_lines_ObjectList.Init1(ob.m_broken_catch_lines, &ob);
		}
		//do not break!!!
	case 1:
		{
			if (ob.m_object_version == 1)
			{
				// for case 2
				ob.m_nCatches = 0;
				ob.m_broken_catch_lines.resize(0);
				ob.m_broken_catch_lines_ObjectList.Init1(ob.m_broken_catch_lines, &ob);

				ob.m_object_version = 2;
			}

			ar >> ob.m_nCuts;
			ar >> ob.m_nDrills;
			ar >> ob.m_nSloi;
			ar >> ob.m_nSurfs;
			ar >> ob.m_nFaults;

			// Objects' vectors
			ar >> ob.m_colorsSloi;

			ar >> ob.m_drills;					ar >> ob.m_drills_ObjectList;
			ob.m_drills_ObjectList.Init1(ob.m_drills, &ob);

			ar >> ob.m_broken_lines;			ar >> ob.m_broken_lines_ObjectList;
			ob.m_broken_lines_ObjectList.Init1(ob.m_broken_lines, &ob);

			ar >> ob.m_broken_fault_lines;		ar >> ob.m_broken_fault_lines_ObjectList;
			ob.m_broken_fault_lines_ObjectList.Init1(ob.m_broken_fault_lines, &ob);

			ar >> ob.m_pointsDrillSloi;			ar >> ob.m_pointsDrillSloi_ObjectList;
			ob.m_pointsDrillSloi_ObjectList.Init2(ob.m_pointsDrillSloi, &ob);

			ar >> ob.m_polySloi;				ar >> ob.m_polySloi_ObjectList;
			ob.m_polySloi_ObjectList.Init1(ob.m_polySloi, &ob);

			// CPoint2
			ar >> ob.m_vMapBlnProfiles;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
	return ar;
}

