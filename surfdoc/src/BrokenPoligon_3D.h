// BrokenPoligon_3D.h: interface for the BrokenPoligon_3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROKENPOLIGON_3D_H__332241CF_6195_44C4_A90A_642FB30AB013__INCLUDED_)
#define AFX_BROKENPOLIGON_3D_H__332241CF_6195_44C4_A90A_642FB30AB013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectList.h"
#include "Poligon3D.h"

class BrokenPoligon_3D  : public Object 
{
	friend class SurfDoc;
public:
	vect<Poligon3D> 											m_poligones;
	ObjectList													m_poligones_ObjectList;

	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);


	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();
	bool UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max);


	void Init(const BrokenPoligon_3D& bp)
	{
		// Objects' vectors
		this->m_poligones			= bp.m_poligones;
		this->m_poligones_ObjectList.Init(this->m_poligones, this);

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
	BrokenPoligon_3D& BrokenPoligon_3D::operator=(const BrokenPoligon_3D& bp);
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);

	BrokenPoligon_3D();
	BrokenPoligon_3D(const BrokenPoligon_3D & bp);
	BrokenPoligon_3D(SurfDoc* pSurfDoc);
	virtual ~BrokenPoligon_3D();

	void OnCreate(void);

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BrokenPoligon_3D& ob);
	friend Archive& operator >>(Archive& ar, BrokenPoligon_3D& ob);
};

#endif // !defined(AFX_BROKENPOLIGON_3D_H__332241CF_6195_44C4_A90A_642FB30AB013__INCLUDED_)
