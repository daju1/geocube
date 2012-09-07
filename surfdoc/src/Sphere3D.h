#if !defined(AFX_SPHERE3D_H__BBD9DE68_2E5E_4DD2_9508_393C122718C8__INCLUDED_)
#define AFX_SPHERE3D_H__BBD9DE68_2E5E_4DD2_9508_393C122718C8__INCLUDED_

#pragma once

#include "Primitive3D.h"

class SurfDoc;

class Sphere3D: public Primitive3D <CPoint3>
{
	virtual void Drawing();
protected:
	void Init(const Sphere3D& ob);
public:
	void Init(SurfDoc * pSurfDoc, CPoint3 pt);
	virtual void PropertiesDialog();
	Sphere3D(void);
	virtual ~Sphere3D(void);
	Sphere3D(const Sphere3D& ob);
	Sphere3D(SurfDoc *pSurfDoc);
	Sphere3D& operator=(const Sphere3D& ob);

	void OnCreate(void);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Sphere3D& ob);
	friend Archive& operator >>(Archive& ar, Sphere3D& ob);
};

#endif
