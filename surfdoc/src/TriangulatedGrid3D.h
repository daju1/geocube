// TriangulatedGrid3D.h: interface for the TriangulatedGrid3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGULATEDGRID3D_H__FAF8F669_46ED_4176_AE68_E2FD47F8EF1B__INCLUDED_)
#define AFX_TRIANGULATEDGRID3D_H__FAF8F669_46ED_4176_AE68_E2FD47F8EF1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectList.h"
#include "Line3D.h"
#include "Triangle3D.h"
#include "InterWellsLine3D.h"

class TriangulatedGrid3D : public Object
{
	friend class SurfDoc;
public:

	// таблица перевода локальных (для текущей сетки) индексов скважин
	// в глобальные (для документа m_pSurfDoc) индексы скважин
	vector<int>													m_indexes;

	vect<InterWellsLine3D>										m_lines;
	vect<TWO>													m_ii_lines;
	ObjectList													m_lines_ObjectList;

	vect<Triangle3D>											m_trias;
	vect<TRIA>													m_ii_trias;
	ObjectList													m_trias_ObjectList;

	TriangulatedGrid3D();
	virtual ~TriangulatedGrid3D();
	virtual void PropertiesDialog();

	void OnCreate(void);
	void AddLine(int i1, int i2, CPoint3* pts, int len, COLORREF color);
	void AddTriangle(int i1, int i2, int i3, CPoint3 v1, CPoint3 v2, CPoint3 v3, COLORREF color);
	virtual void Draw();
	virtual void ReDraw();
	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();
	size_t GetPointsNumber();

	void Init(const TriangulatedGrid3D& ob)
	{			
		this->m_indexes				= ob.m_indexes;

		// Objects' vectors

		this->m_lines				= ob.m_lines;
		this->m_ii_lines			= ob.m_ii_lines;
		this->m_lines_ObjectList.Init(this->m_lines, this);

		this->m_trias				= ob.m_trias;
		this->m_ii_trias			= ob.m_ii_trias;
		this->m_trias_ObjectList.Init(this->m_trias, this);

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
	TriangulatedGrid3D& TriangulatedGrid3D::operator=(const TriangulatedGrid3D& bp);


	TriangulatedGrid3D(const TriangulatedGrid3D & bp);
	TriangulatedGrid3D(SurfDoc* pSurfDoc);
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, TriangulatedGrid3D& ob);
	friend Archive& operator >>(Archive& ar, TriangulatedGrid3D& ob);

};

#endif // !defined(AFX_TRIANGULATEDGRID3D_H__FAF8F669_46ED_4176_AE68_E2FD47F8EF1B__INCLUDED_)
