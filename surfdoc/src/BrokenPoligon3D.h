// BrokenPoligon3D.h: interface for the BrokenPoligon3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROKENPOLIGON3D_H__3F38F43C_D4B9_4CC0_96B3_8FC4B5A43831__INCLUDED_)
#define AFX_BROKENPOLIGON3D_H__3F38F43C_D4B9_4CC0_96B3_8FC4B5A43831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../surfdefs.h"

#include "ObjectList.h"
#include "Poligon3D.h"

class BrokenPoligon3D : public Object 
{
	friend class SurfDoc;
public:
	long id_ige;
	long id_umpoz;
#if USE_UNVISIBLE_CUTTING
	std::vector<PLANE_MEMBERS_VECTOR<Poligon3D> >				m_poligones;
#else
	PLANE_MEMBERS_VECTOR<Poligon3D>								m_poligones;
#endif
	ObjectList													m_poligones_ObjectList;

	int m_nDrills;
	int m_nCuts;

	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();

	void Init(const BrokenPoligon3D& bp)
	{			
		this->m_nCuts				= bp.m_nCuts;
		this->m_nDrills				= bp.m_nDrills;

		// Objects' vectors
		this->m_poligones			= bp.m_poligones;
#if USE_UNVISIBLE_CUTTING
		this->m_poligones_ObjectList.Init_std_vector_Vector(this->m_poligones, this);
#else
		this->m_poligones_ObjectList.Init1(this->m_poligones, this);
#endif
		this->id_umpoz				= bp.id_umpoz;
		this->id_ige				= bp.id_ige;
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
	BrokenPoligon3D& BrokenPoligon3D::operator=(const BrokenPoligon3D& bp);


	BrokenPoligon3D();
	BrokenPoligon3D(const BrokenPoligon3D & bp);
	BrokenPoligon3D(SurfDoc* pSurfDoc);
	virtual ~BrokenPoligon3D();

	void OnCreate(void);

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BrokenPoligon3D& ob);
	friend Archive& operator >>(Archive& ar, BrokenPoligon3D& ob);

};

#endif // !defined(AFX_BROKENPOLIGON3D_H__3F38F43C_D4B9_4CC0_96B3_8FC4B5A43831__INCLUDED_)
