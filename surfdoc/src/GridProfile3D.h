// GridProfile3D.h: interface for the GridProfile3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDPROFILE3D_H__12236D94_8AF0_438B_8897_2B31D4A49C49__INCLUDED_)
#define AFX_GRIDPROFILE3D_H__12236D94_8AF0_438B_8897_2B31D4A49C49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"
#include "points.h"
#include "../../array/src/vect.h"
#include "../../array/src/Vdouble.h"
#include "Grid.h"
#include "ProfileAttachPoint.h"

class GridProfile3D : public Object
{
	friend class SurfDoc;
	void Drawing();
public:
	// ДВУХМЕРНЫЕ ПРОФИЛИ ПОМЕЩЁННЫЕ В ТРЁХМЕРНЫЙ КУБ
	// профиль из вертикально расположенного грида
	vect<CPoint3> m_vGridProfiles;
	vect<CPoint4> m_vvGridProfiles;
	vect<CPoint4> m_vdGridProfiles;

	UINT	m_GridProfilesXSize;		// Текущий размер грида вдоль X
	UINT	m_GridProfilesYSize;		// Текущий размер грида вдоль Y
	// точка привязки профиля к карте
	// массив таких точек привязки 
	// необходим для функции перевода
	// горизонтальной координаты профиля xPrifile
	// в координаты карты xMap yMap
	vect<ProfileAttachPoint> m_vGridProfileMapAttaches;
	double 
		max_grid_profile_v,
		min_grid_profile_v;

	int AddGridProfile(vdouble &x, vdouble &y, vdouble &z, vdouble& visible, vdouble &xMap, vdouble &yMap, vdouble &xProfile);
//#if FAST_GRID_LOADING
//	int AddGridProfile(Grid *pgrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile);
//#else
	int AddGridProfile(CGrid *pCGrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile);
//#endif
	void ConvertGridProfilesTo3D();
	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();

	void Init(const GridProfile3D& bp)
	{			
		this->m_GridProfilesXSize		= bp.m_GridProfilesXSize;
		this->m_GridProfilesYSize		= bp.m_GridProfilesYSize;

		this->m_vGridProfileMapAttaches = bp.m_vGridProfileMapAttaches;
		this->m_vGridProfiles			= bp.m_vGridProfiles;
		this->m_vvGridProfiles			= bp.m_vvGridProfiles;
		this->m_vdGridProfiles			= bp.m_vdGridProfiles;

		this->max_grid_profile_v		= bp.max_grid_profile_v;
		this->min_grid_profile_v		= bp.min_grid_profile_v;

		// Objects' vectors
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
	GridProfile3D& GridProfile3D::operator=(const GridProfile3D& bp);

	GridProfile3D();
	GridProfile3D(const GridProfile3D & bp);
	GridProfile3D(SurfDoc* pSurfDoc);
	virtual ~GridProfile3D();

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	void OnCreate(void);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");


	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, GridProfile3D& ob);
	friend Archive& operator >>(Archive& ar, GridProfile3D& ob);

};

#endif // !defined(AFX_GRIDPROFILE3D_H__12236D94_8AF0_438B_8897_2B31D4A49C49__INCLUDED_)
