// Poligon3D.h: interface for the Poligon3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLIGON3D_H__D18268B3_663D_45FC_ADA7_45FFE825BC75__INCLUDED_)
#define AFX_POLIGON3D_H__D18268B3_663D_45FC_ADA7_45FFE825BC75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"

class SurfDoc;
class Surface3D;
class vdouble;
class win_gdiplus_view;
class BlnProfile3D;

class Poligon3D : public Primitive3D <CPoint3>
{
	Surface3D * m_pSurface;
	virtual void Drawing();
public:
	long id_umpoz;
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);
	virtual void PropertiesDialog();
	void Init(vdouble &x, vdouble &y, vdouble &z, COLORREF color);
	void Init(Surface3D * pSurface);
	Poligon3D();
	Poligon3D(SurfDoc * pSurfDoc);
	virtual ~Poligon3D();

	void Init(const Poligon3D& ob);
	Poligon3D(const Poligon3D& ob);
	Poligon3D& operator=(const Poligon3D& ob);

	void OnCreate(void);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Poligon3D& ob);
	friend Archive& operator >>(Archive& ar, Poligon3D& ob);
};

#endif // !defined(AFX_POLIGON3D_H__D18268B3_663D_45FC_ADA7_45FFE825BC75__INCLUDED_)
