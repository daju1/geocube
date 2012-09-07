// Profile3D.h: interface for the Profile3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILE3D_H__5FBD2C80_3091_4D81_939B_7B99135ABC18__INCLUDED_)
#define AFX_PROFILE3D_H__5FBD2C80_3091_4D81_939B_7B99135ABC18__INCLUDED_

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

#define PROFILE_ATTACH_VECT 0

class Profile3D
{
	DWORD object_version;//версия объекта - потомка от класса Object
protected:

	// X limits for cube projections
	double m_xMin_CubeProjection;
	double m_xMax_CubeProjection;

	double m_xMin_CubeProjection_NonStretched;
	double m_xMax_CubeProjection_NonStretched;

	bool  m_xLimits_CubeProjection_loaded;

	// ACAD X scale
	double m_x1w;
	double m_x1a;
	double m_x2w;
	double m_x2a;
	double m_acad_scale_x;
	bool m_acad_scale_x_loaded;

	// ACAD Y scale
	double m_z1w;
	double m_y1a;
	double m_z2w;
	double m_y2a;
	double m_acad_scale_y;
	bool m_acad_scale_y_loaded;

public:
	bool GetAcadYscaleLoaded(){return m_acad_scale_y_loaded;}

	void SetAcadYscale(double z1w, double y1a, double z2w, double y2a);
	void SetAcadXscale(double x1w, double x1a, double x2w, double x2a);

	bool GetXLimitsCubeProjectionLoaded(){return m_xLimits_CubeProjection_loaded;}
	


	void SetXLimitsCubeProjection(double xMin, double xMax);
	void Calculate_NonStretched_XLimitsCubeProjection();

	// точка привязки профиля к карте
	// массив таких точек привязки 
	// необходим для функции перевода
	// горизонтальной координаты профиля xProfile
	// в координаты карты xMap yMap

	vector<ProfileAttachPoint> m_vProfileMapAttaches;
	vector<ProfileAttachPoint> m_vProfileMapAttachesNonStretched;
	vector<ProfileAttachPoint> * ptpa;
	void CalculateProfileMapAttachesNonStretched(double xstart = 0.0);
	void SetNonStretched_ProfileMapAttaches();
	void SetStretched_ProfileMapAttaches();

	
	int CreateAttaches(vector<double> &xMap, vector<double> &yMap, vector<double> &xProfile);

	
	bool Projection(CPoint3& in, CPoint2& profile, double & dist_to_plane);//Convert3D_To_2D
	bool Projection(CPoint4& in, CPoint2& profile, double & dist_to_plane);//Convert3D_To_2D
	bool Projection(CPoint3& in, CPoint2& profile, double & dist_to_plane, int & interval);//Convert3D_To_2D
	bool Projection(CPoint4& in, CPoint2& profile, double & dist_to_plane, int & interval);//Convert3D_To_2D
	bool Convert2D_To_3D(CPoint2 profile, CPoint3 & pt3 );

	size_t AddBrokePoints(Primitive3D<CPoint3> * primitive, 
		size_t ipoint, 
		CPoint2 p1, CPoint2 p2, 
		int interval1, int interval2);
	size_t AddBrokePoints(Primitive3D<CPoint4> * primitive, 
		size_t ipoint,
		CPoint2 p1, CPoint2 p2, 
		int interval1, int interval2);

	void Init(const Profile3D& bp)
	{
		this->object_version						= bp.object_version;
			
		// X limits for cube projections
		this->m_xMin_CubeProjection					= bp.m_xMin_CubeProjection;
		this->m_xMax_CubeProjection					= bp.m_xMax_CubeProjection;

		this->m_xMin_CubeProjection_NonStretched	= bp.m_xMin_CubeProjection_NonStretched;
		this->m_xMax_CubeProjection_NonStretched	= bp.m_xMax_CubeProjection_NonStretched;

		this->m_xLimits_CubeProjection_loaded		= bp.m_xLimits_CubeProjection_loaded;

		// ACAD X scale
		this->m_x1w									= bp.m_x1w;
		this->m_x1a									= bp.m_x1a;
		this->m_x2w									= bp.m_x2w;
		this->m_x2a									= bp.m_x2a;
		this->m_acad_scale_x						= bp.m_acad_scale_x;
		this->m_acad_scale_x_loaded					= bp.m_acad_scale_x_loaded;

		// ACAD Y scale
		this->m_acad_scale_y_loaded					= bp.m_acad_scale_y_loaded;
		this->m_acad_scale_y						= bp.m_acad_scale_y;
		this->m_z1w									= bp.m_z1w;
		this->m_y1a									= bp.m_y1a;
		this->m_z2w									= bp.m_z2w;
		this->m_y2a									= bp.m_y2a;


		m_vProfileMapAttaches						= bp.m_vProfileMapAttaches;
		m_vProfileMapAttachesNonStretched			= bp.m_vProfileMapAttachesNonStretched;

	}

	Profile3D& Profile3D::operator=(const Profile3D& bp);

	Profile3D();
	Profile3D(const Profile3D & bp);

	virtual ~Profile3D();

	bool EditAttaches();
	void PrintAttaches();

	void OnCreate(void);

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Profile3D& ob);
	friend Archive& operator >>(Archive& ar, Profile3D& ob);

};
int __cdecl compareProfileAttachX( const void *arg1, const void *arg2 );
void ProfileAttaching(double xProfile, // на вход подаём координату по профилю
					  int& ipoint, 
					  int lenMapAttach, ProfileAttachPoint *ptpa, // используем массив привязок профиля
					  double& xMap, double& yMap );
void ProfileAttaching(double xProfile, // на вход подаём координату по профилю
					  int& ipoint, 
					  vector<ProfileAttachPoint> & vpa, // используем массив привязок профиля
					  double& xMap, double& yMap );
void ProfileMapAttaches_vect2vector(vect<ProfileAttachPoint> & vectPAP, vector<ProfileAttachPoint> & vectorPAP);
void ProfileMapAttaches_vector2vect(vector<ProfileAttachPoint> & vectorPAP, vect<ProfileAttachPoint> & vectPAP);
void BlnProfiles_vector2vect(vector<vector<CPoint2> > & vectorBlnProfiles, vect<CPoint2> & vectBlnProfiles);
void BlnProfiles_vect2vector(vect<CPoint2> & vectBlnProfiles, vector<vector<CPoint2> > & vectorBlnProfiles);

#endif // !defined(AFX_BLNPROFILE3D_H__5FBD2C80_3091_4D81_939B_7B99135ABC18__INCLUDED_)
