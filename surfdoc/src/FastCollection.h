#pragma once
#include "Primitive3D.h"
#include "object.h"
#include "objectlist.h"
#include "..\..\array\src\vect.h"

class FastCollection :
	public Object
{
public:
	vect<Primitive3D<CPoint3>, ObjectItem<Primitive3D<CPoint3> > >	
		m_objects;
	ObjectList							
		m_objects_ObjectList;

	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);

	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();
	void Init(const FastCollection& bp)
	{			
		// Objects' vectors
		this->m_objects				= bp.m_objects;
		this->m_objects_ObjectList.Init(this->m_objects, this);
	}
	bool SaveAs();
	bool SaveAsDat(FILE * stream);
	bool SaveAsBln(FILE * stream);

	void FillContextMenu(HMENU& hMenu);

	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws);
	FastCollection& FastCollection::operator=(const FastCollection& bp);
	FastCollection(const FastCollection & bp);
	FastCollection(SurfDoc* pSurfDoc);
	FastCollection(void);
	~FastCollection(void);

	Object * AddObject(Primitive3D<CPoint3> * object);
	void InitObjectList();

	size_t GetPointsNumber(){return 0;}

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	void OnCreate(void);
	friend Archive& operator <<(Archive& ar, FastCollection& ob);
	friend Archive& operator >>(Archive& ar, FastCollection& ob);
};
