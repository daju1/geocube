// Profile3D.cpp: implementation of the Profile3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Profile3D.h"
#include "..\..\commonOG.h"
#include "SurfDoc.h"
#include ".\blnprofile3d.h"
#include ".\Archive.h"
#include ".\whatselected.h"
#include "winsurftree.h"


int GetVerticalPlaneFromTwoPoints(
								  CPoint2 &pt1, CPoint2 &pt2, //input
								  double &a, double &b, double &c, double &d);//output
#define MY_CPOINT CPoint3
#include "Profile_Projection.h"
#pragma warning (disable:4005)
#define MY_CPOINT CPoint4
#pragma warning (default:4005)
#include "Profile_Projection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Profile3D::Profile3D() : ptpa(&m_vProfileMapAttaches)
{
	this->object_version = 4;
	OnCreate();
}


void Profile3D::OnCreate(void)
{
	this->m_xLimits_CubeProjection_loaded = false;
	this->m_xMin_CubeProjection = -DBL_MAX;
	this->m_xMax_CubeProjection = DBL_MAX;
	this->m_xMin_CubeProjection_NonStretched = -DBL_MAX;
	this->m_xMax_CubeProjection_NonStretched = DBL_MAX;

	this->m_acad_scale_x_loaded		= false;
	this->m_x1w						= 0.0;
	this->m_x1a						= 0.0;
	this->m_x2w						= 1.0;
	this->m_x2a						= 1.0;
	this->m_acad_scale_x			= (this->m_x2a - this->m_x1a) / (this->m_x2w - this->m_x1w);

	this->m_acad_scale_y_loaded		= false;
	this->m_z1w						= 0.0;
	this->m_y1a						= 0.0;
	this->m_z2w						= 1.0;
	this->m_y2a						= 1.0;
	this->m_acad_scale_y			= (this->m_y2a - this->m_y1a) / (this->m_z2w - this->m_z1w);
}

void Profile3D::SetAcadYscale(double z1w, double y1a, double z2w, double y2a)
{
	this->m_acad_scale_y_loaded		= true;
	this->m_z1w						= z1w;
	this->m_y1a						= y1a;
	this->m_z2w						= z2w;
	this->m_y2a						= y2a;
	this->m_acad_scale_y			= (this->m_y2a - this->m_y1a) / (this->m_z2w - this->m_z1w);
}

void Profile3D::SetAcadXscale(double x1w, double x1a, double x2w, double x2a)
{
	this->m_acad_scale_x_loaded		= true;
	this->m_x1w						= x1w;
	this->m_x1a						= x1a;
	this->m_x2w						= x2w;
	this->m_x2a						= x2a;
	this->m_acad_scale_x			= (this->m_x2a - this->m_x1a) / (this->m_x2w - this->m_x1w);
}
void Profile3D::SetXLimitsCubeProjection(double xMin, double xMax)
{
	this->m_xLimits_CubeProjection_loaded = true;
	this->m_xMin_CubeProjection = xMin;
	this->m_xMax_CubeProjection = xMax;

	this->Calculate_NonStretched_XLimitsCubeProjection();
}
void Profile3D::Calculate_NonStretched_XLimitsCubeProjection()
{
	this->CalculateProfileMapAttachesNonStretched();

	vector<ProfileAttachPoint> * pa = this->ptpa;

	CPoint2 profile_xMin; profile_xMin.y = 0.0; profile_xMin.x = this->m_xMin_CubeProjection;
	CPoint2 profile_xMax; profile_xMax.y = 0.0; profile_xMax.x = this->m_xMax_CubeProjection;	

	this->ptpa = &m_vProfileMapAttaches;

	CPoint3 pt3_xMin; this->Convert2D_To_3D(profile_xMin, pt3_xMin );
	CPoint3 pt3_xMax; this->Convert2D_To_3D(profile_xMax, pt3_xMax );	

	this->ptpa = &m_vProfileMapAttachesNonStretched;

	double dist_to_plane;
	this->Projection(pt3_xMin, profile_xMin, dist_to_plane);//Convert3D_To_2D
	this->Projection(pt3_xMax, profile_xMax, dist_to_plane);//Convert3D_To_2D

	this->ptpa = pa;

	this->m_xMin_CubeProjection_NonStretched = profile_xMin.x;
	this->m_xMax_CubeProjection_NonStretched = profile_xMax.x;
}

Profile3D::Profile3D(const Profile3D & bp) : ptpa(&m_vProfileMapAttaches)
{
	this->Init(bp);
}
Profile3D& Profile3D::operator=(const Profile3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	this->Init(bp);

	return *this;
}
Profile3D::~Profile3D()
{
}
int Profile3D::CreateAttaches(vector<double> &xMap, vector<double> &yMap, vector<double> &xProfile)
{
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if (xMap.size() != yMap.size() || xMap.size() != xProfile.size() || xMap.size() != xProfile.size() )
	{
		char str[255];
		sprintf(str, "xMap.size(%d) != yMap.size(%d) != xProfile.size(%d)", xMap.size(), yMap.size(), xProfile.size());
		MessageBox(0,str, "AddBlnProfile",0);
		return -1;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	UINT lenMapAttach = xMap.size();

	m_vProfileMapAttaches.resize(lenMapAttach);
	for(UINT i = 0; i < lenMapAttach; i++)
	{
		m_vProfileMapAttaches[i].xMap		= xMap[i];
		m_vProfileMapAttaches[i].yMap		= yMap[i];
		m_vProfileMapAttaches[i].xProfile	= xProfile[i];
		m_vProfileMapAttaches[i].bAttached	= true;
	}
	this->CalculateProfileMapAttachesNonStretched();

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	return 0;
}

void Profile3D::CalculateProfileMapAttachesNonStretched(double xstart)
{
	size_t lenMapAttach = m_vProfileMapAttaches.size();
	//m_vProfileMapAttachesNonStretched = m_vProfileMapAttaches;
	m_vProfileMapAttachesNonStretched.resize(lenMapAttach);
	if (lenMapAttach > 0)
	{
		m_vProfileMapAttachesNonStretched[0].xProfile = xstart;
		m_vProfileMapAttachesNonStretched[0].xMap = m_vProfileMapAttaches[0].xMap;
		m_vProfileMapAttachesNonStretched[0].yMap = m_vProfileMapAttaches[0].yMap;
		m_vProfileMapAttachesNonStretched[0].bAttached = m_vProfileMapAttaches[0].bAttached;
		for (size_t i = 1; i < lenMapAttach; i++)
		{
			double d = 
				sqrt(
				pow(m_vProfileMapAttaches[i].xMap - m_vProfileMapAttaches[i-1].xMap, 2.0) + 
				pow(m_vProfileMapAttaches[i].yMap - m_vProfileMapAttaches[i-1].yMap, 2.0) 
				);
			m_vProfileMapAttachesNonStretched[i].xProfile = m_vProfileMapAttachesNonStretched[i-1].xProfile + d;
			m_vProfileMapAttachesNonStretched[i].xMap = m_vProfileMapAttaches[i].xMap;
			m_vProfileMapAttachesNonStretched[i].yMap = m_vProfileMapAttaches[i].yMap;
			m_vProfileMapAttachesNonStretched[i].bAttached = m_vProfileMapAttaches[i].bAttached;

		}
	}
}
void Profile3D::SetNonStretched_ProfileMapAttaches()
{
	printf("Profile3D::SetNonStretched_ProfileMapAttaches()\n");
	ptpa = &m_vProfileMapAttachesNonStretched;
}
void Profile3D::SetStretched_ProfileMapAttaches()
{
	printf("Profile3D::SetStretched_ProfileMapAttaches()\n");
	ptpa = &m_vProfileMapAttaches;
}



void BlnProfiles_vector2vect(vector<vector<CPoint2> > & vectorBlnProfiles, vect<CPoint2> & vectBlnProfiles)
{
	vectBlnProfiles.clear();
	for (size_t n = 0; n < vectorBlnProfiles.size(); n++)
	{
		size_t m = vectorBlnProfiles[n].size();
		CPoint2 * pp = new CPoint2[m];
		for (size_t i = 0; i < m; i++)
		{
			pp[i].x = vectorBlnProfiles[n][i].x;
			pp[i].y = vectorBlnProfiles[n][i].y;
			pp[i].bVisible = true;
		}

		vectBlnProfiles.AddMsg(pp,2);
		delete [] pp;
	}
}
void BlnProfiles_vect2vector(vect<CPoint2> & vectBlnProfiles, vector<vector<CPoint2> > & vectorBlnProfiles)
{
	vectorBlnProfiles.clear();
	if (vectBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			vectorBlnProfiles.push_back(vector<CPoint2>());
			

			size_t len = vectBlnProfiles.GetCurrentMsgLen();
			CPoint2 *pt2;
			pt2 = vectBlnProfiles.GetCurrentMsgPtr();
			for(size_t i = 0; i < len; i++)
			{
				double x = pt2[i].x;
				double y = pt2[i].y;

				vectorBlnProfiles.back().push_back(CPoint2(x,y));
			}
		}
		while(vectBlnProfiles.IncrementCurrentMsg() );
	}
}
void ProfileMapAttaches_vector2vect(vector<ProfileAttachPoint> & vectorPAP, vect<ProfileAttachPoint> & vectPAP)
{
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	vectPAP.clear();
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	size_t lenMapAttach = vectorPAP.size();
	ProfileAttachPoint* ptpa;
	ptpa = (ProfileAttachPoint*)HeapAlloc(GetProcessHeap(), 
		HEAP_ZERO_MEMORY, 
		lenMapAttach*sizeof(ProfileAttachPoint));
	for(UINT i = 0; i < lenMapAttach; i++)
	{
		ptpa[i].xMap		= vectorPAP[i].xMap;
		ptpa[i].yMap		= vectorPAP[i].yMap;
		ptpa[i].xProfile	= vectorPAP[i].xProfile;
		ptpa[i].bAttached	= vectorPAP[i].bAttached;
	}
	vectPAP.AddMsg(ptpa, lenMapAttach);
	if(ptpa) HeapFree(GetProcessHeap(), 0, ptpa);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}
void ProfileMapAttaches_vect2vector(vect<ProfileAttachPoint> & vectPAP, vector<ProfileAttachPoint> & vectorPAP)
{
	vectorPAP.clear();
	if ( vectPAP.SetCurrentMsgOnFirst())
	{
		do
		{
			size_t len = vectPAP.GetCurrentMsgLen();
			ProfileAttachPoint* ptpa = vectPAP.GetCurrentMsgPtr();
			vectorPAP.resize(len);
			//=============================================
			for (size_t i = 0; i < len; i++)
			{	
				vectorPAP[i] = ptpa[i];
			}
		}
		while( vectPAP.IncrementCurrentMsg());
	}
}
int __cdecl compareProfileAttachX( const void *arg1, const void *arg2 )
{
   /* Compare X: */
   double 
	   x1 = (( ProfileAttachPoint* ) arg1)->xProfile,
	   x2 = (( ProfileAttachPoint* ) arg2)->xProfile;
   if (x1 < x2)
	   return -1;
   if (x1 == x2)
	   return 0;
   if (x1 > x2)
	   return 1;
   return 0;
}
void ProfileAttaching(double xProfile, // на вход подаём координату по профилю
					  int& ipoint, 
					  vector<ProfileAttachPoint> & ptpa, // используем массив привязок профиля
					  double& xMap, double& yMap ) // на выходе получаем координаты этой точки на карте
{
	int lenMapAttach = (int)ptpa.size();

	bool more, less;
	// проверяем попадает ли заданная горизонтальная координата 
	// в текущий интервал массива привязок профиля к карте
	do 
	{
		// проверяем не выходит ли индекс интервала 
		// в массиве привязок за пределы определяемые 
		// длиной массива привязок
		if (ipoint >= 0 && ipoint < lenMapAttach - 1)
		{
			// проверяем попадает ли заданная горизонтальная координата 
			// в текущий интервал массива привязок профиля к карте
			if (xProfile >= ptpa[ipoint].xProfile)
				more = true;
			else
				more = false;

			if (xProfile <= ptpa[ipoint+1].xProfile)
				less = true;
			else
				less = false;

			// если заданная горизонтальная координата не попадает в текущий интервал массива привязок, изменяем индекс интервала в массиве привязок
			if (!less)
				ipoint++;
			if (!more)
				ipoint--;
		}
		// ЕСЛИ ВСЁ ЖЕ ИНДЕКС ИНТЕРВАЛА ВЫШЕЛ ЗА ГРАНИЦЫ ДЛИНЫ МАССИВА ПРИВЯЗОК
		else
		{
			if (ipoint < 0)
			{
				if (xProfile < ptpa[0].xProfile)
				{
					// если заданная горизонтальная координата
					// меньше минимальной горизонтальной координаты 
					// из массива привязок, то выходим из цикла 
					// потому что будем использовать для интерполяции 
					// направление первого интервала в массиве привязок
					break;
				}
				else
				{
					// иначе увеличиваем индекс интервала
					ipoint = 0;
					more = true; 
					less = false;
				}
			}
			if (ipoint >= lenMapAttach - 1)
			{
				if (xProfile > ptpa[lenMapAttach - 1].xProfile)
				{
					// если заданная горизонтальная координата
					// больше максимальной горизонтальной координаты 
					// из массива привязок, то выходим из цикла 
					// потому что будем использовать для интерполяции 
					// направление последнего интервала в массиве привязок
					break;
				}
				else
				{
					// иначе уменьшаем индекс интервала
					ipoint = 0;
					more = false; 
					less = true;
				}
			}
		}

		// СНОВА
		// проверяем не выходит ли индекс интервала 
		// в массиве привязок за пределы определяемые 
		// длиной массива привязок
		if (ipoint >= 0 && ipoint < lenMapAttach - 1)
		{
		}
		// если индекс вышел за пределы - выходим из цикла while
		else
			break;
	}
	// ДО ТЕХ ПОР ПОКА НЕ ВЫБЕРЕМ НОМЕР НУЖНОГО НАМ ИНТЕРВАЛА МАССИВА ПРИВЯЗОК 
	// ИЛИ НЕ ВЫЙДЕМ ЗА ПРЕДЕЛЫ ИНТЕРВАЛА
	while (!more || !less);

	// проверяем не выходит ли индекс интервала 
	// в массиве привязок за пределы определяемые 
	// длиной массива привязок
	if (ipoint >= 0 && ipoint < lenMapAttach - 1)
	{
		double part = (xProfile - ptpa[ipoint].xProfile) / (ptpa[ipoint+1].xProfile - ptpa[ipoint].xProfile);
		xMap = ptpa[ipoint].xMap + part * (ptpa[ipoint+1].xMap - ptpa[ipoint].xMap);
		yMap = ptpa[ipoint].yMap + part * (ptpa[ipoint+1].yMap - ptpa[ipoint].yMap);

	}
	// ЕСЛИ ВСЁ ЖЕ ИНДЕКС ИНТЕРВАЛА ВЫШЕЛ ЗА ГРАНИЦЫ ДЛИНЫ МАССИВА ПРИВЯЗОК
	else
	{
		if (ipoint < 0)
		{
			// если заданная горизонтальная координата
			// меньше минимальной горизонтальной координаты 
			// из массива привязок, то  
			// будем использовать для интерполяции 
			// направление первого интервала в массиве привязок
			double part = (xProfile - ptpa[0].xProfile) / (ptpa[1].xProfile - ptpa[0].xProfile);
			xMap = ptpa[0].xMap + part * (ptpa[1].xMap - ptpa[0].xMap);
			yMap = ptpa[0].yMap + part * (ptpa[1].yMap - ptpa[0].yMap);

		}
		if (ipoint >= lenMapAttach - 1)
		{
			// если заданная горизонтальная координата
			// больше максимальной горизонтальной координаты 
			// из массива привязок, то  
			// будем использовать для интерполяции 
			// направление последнего интервала в массиве привязок
			double part = (xProfile - ptpa[lenMapAttach - 2].xProfile) / (ptpa[lenMapAttach - 1].xProfile - ptpa[lenMapAttach - 2].xProfile);
			xMap = ptpa[lenMapAttach - 2].xMap + part * (ptpa[lenMapAttach - 1].xMap - ptpa[lenMapAttach - 2].xMap);
			yMap = ptpa[lenMapAttach - 2].yMap + part * (ptpa[lenMapAttach - 1].yMap - ptpa[lenMapAttach - 2].yMap);
		}
	}
}
void ProfileAttaching(double xProfile, // на вход подаём координату по профилю
					  int& ipoint, 
					  int lenMapAttach, ProfileAttachPoint *ptpa, // используем массив привязок профиля
					  double& xMap, double& yMap ) // на выходе получаем координаты этой точки на карте
{
	bool more, less;
	// проверяем попадает ли заданная горизонтальная координата 
	// в текущий интервал массива привязок профиля к карте
	do 
	{
		// проверяем не выходит ли индекс интервала 
		// в массиве привязок за пределы определяемые 
		// длиной массива привязок
		if (ipoint >= 0 && ipoint < lenMapAttach - 1)
		{
			// проверяем попадает ли заданная горизонтальная координата 
			// в текущий интервал массива привязок профиля к карте
			if (xProfile >= ptpa[ipoint].xProfile)
				more = true;
			else
				more = false;

			if (xProfile <= ptpa[ipoint+1].xProfile)
				less = true;
			else
				less = false;

			// если заданная горизонтальная координата не попадает в текущий интервал массива привязок, изменяем индекс интервала в массиве привязок
			if (!less)
				ipoint++;
			if (!more)
				ipoint--;
		}
		// ЕСЛИ ВСЁ ЖЕ ИНДЕКС ИНТЕРВАЛА ВЫШЕЛ ЗА ГРАНИЦЫ ДЛИНЫ МАССИВА ПРИВЯЗОК
		else
		{
			if (ipoint < 0)
			{
				if (xProfile < ptpa[0].xProfile)
				{
					// если заданная горизонтальная координата
					// меньше минимальной горизонтальной координаты 
					// из массива привязок, то выходим из цикла 
					// потому что будем использовать для интерполяции 
					// направление первого интервала в массиве привязок
					break;
				}
				else
				{
					// иначе увеличиваем индекс интервала
					ipoint = 0;
					more = true; 
					less = false;
				}
			}
			if (ipoint >= lenMapAttach - 1)
			{
				if (xProfile > ptpa[lenMapAttach - 1].xProfile)
				{
					// если заданная горизонтальная координата
					// больше максимальной горизонтальной координаты 
					// из массива привязок, то выходим из цикла 
					// потому что будем использовать для интерполяции 
					// направление последнего интервала в массиве привязок
					break;
				}
				else
				{
					// иначе уменьшаем индекс интервала
					ipoint = 0;
					more = false; 
					less = true;
				}
			}
		}

		// СНОВА
		// проверяем не выходит ли индекс интервала 
		// в массиве привязок за пределы определяемые 
		// длиной массива привязок
		if (ipoint >= 0 && ipoint < lenMapAttach - 1)
		{
		}
		// если индекс вышел за пределы - выходим из цикла while
		else
			break;
	}
	// ДО ТЕХ ПОР ПОКА НЕ ВЫБЕРЕМ НОМЕР НУЖНОГО НАМ ИНТЕРВАЛА МАССИВА ПРИВЯЗОК 
	// ИЛИ НЕ ВЫЙДЕМ ЗА ПРЕДЕЛЫ ИНТЕРВАЛА
	while (!more || !less);

	// проверяем не выходит ли индекс интервала 
	// в массиве привязок за пределы определяемые 
	// длиной массива привязок
	if (ipoint >= 0 && ipoint < lenMapAttach - 1)
	{
		double part = (xProfile - ptpa[ipoint].xProfile) / (ptpa[ipoint+1].xProfile - ptpa[ipoint].xProfile);
		xMap = ptpa[ipoint].xMap + part * (ptpa[ipoint+1].xMap - ptpa[ipoint].xMap);
		yMap = ptpa[ipoint].yMap + part * (ptpa[ipoint+1].yMap - ptpa[ipoint].yMap);

	}
	// ЕСЛИ ВСЁ ЖЕ ИНДЕКС ИНТЕРВАЛА ВЫШЕЛ ЗА ГРАНИЦЫ ДЛИНЫ МАССИВА ПРИВЯЗОК
	else
	{
		if (ipoint < 0)
		{
			// если заданная горизонтальная координата
			// меньше минимальной горизонтальной координаты 
			// из массива привязок, то  
			// будем использовать для интерполяции 
			// направление первого интервала в массиве привязок
			double part = (xProfile - ptpa[0].xProfile) / (ptpa[1].xProfile - ptpa[0].xProfile);
			xMap = ptpa[0].xMap + part * (ptpa[1].xMap - ptpa[0].xMap);
			yMap = ptpa[0].yMap + part * (ptpa[1].yMap - ptpa[0].yMap);

		}
		if (ipoint >= lenMapAttach - 1)
		{
			// если заданная горизонтальная координата
			// больше максимальной горизонтальной координаты 
			// из массива привязок, то  
			// будем использовать для интерполяции 
			// направление последнего интервала в массиве привязок
			double part = (xProfile - ptpa[lenMapAttach - 2].xProfile) / (ptpa[lenMapAttach - 1].xProfile - ptpa[lenMapAttach - 2].xProfile);
			xMap = ptpa[lenMapAttach - 2].xMap + part * (ptpa[lenMapAttach - 1].xMap - ptpa[lenMapAttach - 2].xMap);
			yMap = ptpa[lenMapAttach - 2].yMap + part * (ptpa[lenMapAttach - 1].yMap - ptpa[lenMapAttach - 2].yMap);
		}
	}
}

bool Profile3D::Convert2D_To_3D(CPoint2 profile, CPoint3 & pt3 )
{
	// sort on x using Quicksort algorithm:
	// qsort( (void *)ptpa, (size_t)lenMapAttach, sizeof(ProfileAttachPoint), compareProfileAttachX );
	// преобразовываем эту координату в горизонтальные координаты xMap yMap в системе координат карты 
	int ipoint = 0;
	ProfileAttaching(profile.x, ipoint, *ptpa, pt3.x, pt3.y );
	// глубину берём без всяких преобразований из блн файла
	pt3.z = profile.y;
	pt3.bVisible = profile.bVisible;
	return true;
}

#if PROFILE_ATTACH_VECT

void Profile3D::PrintAttaches()
{
	printf("Profile3D::PrintAttaches\n");
	if (m_vBlnProfileMapAttaches.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = m_vBlnProfileMapAttaches.GetCurrentMsgLen();
			printf("Attach Len = %d\n", len);
			ProfileAttachPoint *pt2;
			pt2 = m_vBlnProfileMapAttaches.GetCurrentMsgPtr();
			for(int i = 0; i < len; i++)
			{
				printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
			}
		}
		while(m_vBlnProfileMapAttaches.IncrementCurrentMsg() );
	}
	printf("Profile3D::Print Plane Attaches\n");
#if 0
	if ( 
		this->m_plane.m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
		&&
		this->m_plane.m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			int len = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgLen();
		
			printf("Plane Attach Len = %d\n", len);

			CPoint3 *ptv;
			CPoint3 *ptd;
			ptv = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			ptd = this->m_plane.m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			//=============================================
			for (int i = 0; i /*+ 2*/ < len - 1; i+=2)
			{	
				printf("i   = %d x = %f y = %f z = %f\n", i,  ptd[i  ].x, ptd[i].y, ptd[i].z);
				printf("i+1 = %d x = %f y = %f z = %f\n", i+1,ptd[i+1].x, ptd[i+1].y, ptd[i+1].z);
				//printf("i+2 = %d x = %f y = %f z = %f\n", i+2,ptd[i+2].x, ptd[i+2].y, ptd[i+2].z);
				//printf("i+3 = %d x = %f y = %f z = %f\n", i+3,ptd[i+3].x, ptd[i+3].y, ptd[i+3].z);
			}
		}
		while( 
			this->m_plane.m_vvplaneBlnProfiles.IncrementCurrentMsg()
			&&
			this->m_plane.m_vdplaneBlnProfiles.IncrementCurrentMsg()
			);
	}
	//return NULL;
#endif
}

bool Profile3D::EditAttaches()
{
	if (m_vBlnProfileMapAttaches.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = m_vBlnProfileMapAttaches.GetCurrentMsgLen();
			ProfileAttachPoint *pt2;
			pt2 = m_vBlnProfileMapAttaches.GetCurrentMsgPtr();
			for(int i = 0; i < len; i++)
			{
			}
		}
		while(m_vBlnProfileMapAttaches.IncrementCurrentMsg() );
	}

	bool result = false;
#if 0
	if ( 
		this->m_plane.m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
		&&
		this->m_plane.m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			int len = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgLen();
		
			printf("Plane Attach Len = %d\n", len);

			CPoint3 *ptv;
			CPoint3 *ptd;
			ptv = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			ptd = this->m_plane.m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			//=============================================
			for (int i = 0; i < len - 1; i+=2)
			{	
				printf("i   = %d x = %f y = %f z = %f\n", i,  ptd[i  ].x, ptd[i].y, ptd[i].z);
				printf("i+1 = %d x = %f y = %f z = %f\n", i+1,ptd[i+1].x, ptd[i+1].y, ptd[i+1].z);

				cout << "Do you want to correct this? (y/n)" << endl << ends;
				char yn;
				cin >> yn;
				if (yn == 'y' || yn == 'Y')
				{
					cout << "What coordinate do you want to correct? (x/y/z)" << endl << ends;
					char xyz;
					cin >> xyz;
					if (xyz == 'x' || xyz == 'X')
					{
						cout << "Enter new X coordinate" << endl << ends;
						double x;
						cin >> x;
						ptd[i  ].x = x;
						ptd[i+1].x = x;
						result = true;
					}

					if (xyz == 'y' || xyz == 'Y')
					{
						cout << "Enter new Y coordinate" << endl << ends;
						double y;
						cin >> y;
						ptd[i  ].y = y;
						ptd[i+1].y = y;
						result = true;
					}

					if (xyz == 'z' || xyz == 'Z')
					{
						printf("i   = %d x = %f y = %f z = %f\n", i,  ptd[i  ].x, ptd[i].y, ptd[i].z);
						cout << "Do you want to correct this Y coordinate? (y/n)" << endl << ends;
						cin >> yn;
						if (yn == 'y' || yn == 'Y')
						{
							cout << "Enter new Z coordinate" << endl << ends;
							double z;
							cin >> z;
							ptd[i  ].z = z;
							result = true;
						}
						printf("i+1 = %d x = %f y = %f z = %f\n", i+1,ptd[i+1].x, ptd[i+1].y, ptd[i+1].z);
						cout << "Do you want to correct this Y coordinate? (y/n)" << endl << ends;
						cin >> yn;
						if (yn == 'y' || yn == 'Y')
						{
							cout << "Enter new Z coordinate" << endl << ends;
							double z;
							cin >> z;
							ptd[i+1].z = z;
							result = true;
						}					
					}
				}
			}
		}
		while( 
			this->m_plane.m_vvplaneBlnProfiles.IncrementCurrentMsg()
			&&
			this->m_plane.m_vdplaneBlnProfiles.IncrementCurrentMsg()
			);
	}
	if (result)
	{
		this->PrintAttaches();
		this->m_plane.Zooming();
		this->m_plane.ReDraw();
	}
#endif
	return result;
}

#else
void Profile3D::PrintAttaches()
{
	printf("BlnProfile3D::PrintAttaches\n");

	size_t len = m_vProfileMapAttaches.size();
	printf("Attach Len = %d\n", len);
	vector<ProfileAttachPoint> & pt2 = m_vProfileMapAttaches;
	for(size_t i = 0; i < len; i++)
	{
		printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
	}

	cout << "m_acad_scale_y_loaded = " << this->m_acad_scale_y_loaded << endl;
	if (this->m_acad_scale_y_loaded)
	{
		cout << "m_z1w = " << m_z1w << "\t";
		cout << "m_y1a = " << m_y1a << endl;
		cout << "m_z2w = " << m_z2w << "\t";
		cout << "m_y2a = " << m_y2a << endl;
		cout << "m_acad_scale_y = " << m_acad_scale_y << endl;
	}
}
bool Profile3D::EditAttaches()
{
	printf("BlnProfile3D::EditAttaches\n");

	size_t len = m_vProfileMapAttaches.size();
	printf("Attach Len = %d\n", len);
	vector<ProfileAttachPoint> & pt2 = m_vProfileMapAttaches;
	for(size_t i = 0; i < len; i++)
	{
		printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
	}
	bool reenter_xProfile = false;
	cout << "reenter xProfile [0,1]?" << endl;
	cin >> reenter_xProfile;

	if (reenter_xProfile)
	{
		for(size_t i = 0; i < len; i++)
		{
			printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
			bool reenter_xProfile_i = false;
			cout << "reenter xProfile[" << i << "]? ";
			cin >> reenter_xProfile_i;
			if (reenter_xProfile_i)
			{
				cout << "old xProfile[" << i << "] = " << pt2[i].xProfile << " new xProfile[" << i << "] = ? ";
				cin >> pt2[i].xProfile;
			}
			cout << endl;	
		}			
		cout << endl;
		for(size_t i = 0; i < len; i++)
		{
			printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
		}
	}
	this->CalculateProfileMapAttachesNonStretched();
	return true;
}
#endif
DWORD Profile3D::Serialize(Archive& ar)
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

Archive& operator <<(Archive& ar, Profile3D& ob)
{

	ar << ob.object_version;
	DWORD version = ob.object_version;
//printf("Archive& operator <<(Archive& ar, Profile3D& ob) version = %d\n",version);

	switch (version)
	{
	case 4:
		{
			// X limits for cube projections
			ar << ob.m_xMin_CubeProjection;
			ar << ob.m_xMax_CubeProjection;
			ar << ob.m_xMin_CubeProjection_NonStretched;
			ar << ob.m_xMax_CubeProjection_NonStretched;
			ar << ob.m_xLimits_CubeProjection_loaded;

			// ACAD X scale
			ar << ob.m_x1w;
			ar << ob.m_x1a;
			ar << ob.m_x2w;
			ar << ob.m_x2a;
			ar << ob.m_acad_scale_x;
			ar << ob.m_acad_scale_x_loaded;
		}
	case 3:
		{
//printf("ar << ob.m_acad_scale_y_loaded = %d\n",ob.m_acad_scale_y_loaded);
			ar << ob.m_acad_scale_y_loaded;
			ar << ob.m_acad_scale_y;
			ar << ob.m_z1w;
			ar << ob.m_y1a;
			ar << ob.m_z2w;
			ar << ob.m_y2a;

		}
		//do not break;
	case 2:
		{
			ar << ob.m_vProfileMapAttaches;
		}
		break;
	case 1:
		{
			vect<ProfileAttachPoint> vBlnProfileMapAttaches;
			ProfileMapAttaches_vector2vect(ob.m_vProfileMapAttaches, vBlnProfileMapAttaches);
			ar << vBlnProfileMapAttaches;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, Object::object_type::bln_profile3d);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, Profile3D& ob)
{
	DWORD version;
	ar >> version;
//printf("Archive& operator >>(Archive& ar, Profile3D& ob) version = %d\n",version);
	switch (version)
	{
	case 4:
		{
			// X limits for cube projections
			ar >> ob.m_xMin_CubeProjection;
			ar >> ob.m_xMax_CubeProjection;
			ar >> ob.m_xMin_CubeProjection_NonStretched;
			ar >> ob.m_xMax_CubeProjection_NonStretched;
			ar >> ob.m_xLimits_CubeProjection_loaded;

			// ACAD X scale
			ar >> ob.m_x1w;
			ar >> ob.m_x1a;
			ar >> ob.m_x2w;
			ar >> ob.m_x2a;
			ar >> ob.m_acad_scale_x;
			ar >> ob.m_acad_scale_x_loaded;
		}
	case 3:
		{
			ar >> ob.m_acad_scale_y_loaded;
//printf("ar >> ob.m_acad_scale_y_loaded = %d\n",ob.m_acad_scale_y_loaded);
			ar >> ob.m_acad_scale_y;
			ar >> ob.m_z1w;
			ar >> ob.m_y1a;
			ar >> ob.m_z2w;
			ar >> ob.m_y2a;
		}
		//do not break;	case 2:
	case 2:
		{
			ar >> ob.m_vProfileMapAttaches;
			ob.CalculateProfileMapAttachesNonStretched();
		}
		break;
	case 1:
		{
			vect<ProfileAttachPoint> vBlnProfileMapAttaches;
			ar >> vBlnProfileMapAttaches;
			ProfileMapAttaches_vect2vector(vBlnProfileMapAttaches, ob.m_vProfileMapAttaches);
		}
		break;
	default:
		{
			throw VersionException(ob.object_version, VersionException::cannot_load, Object::object_type::bln_profile3d);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, Profile3D& ob) version = %d end\n",version);
	return ar;
}


