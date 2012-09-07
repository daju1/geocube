// BrokenLine3D.h: interface for the BrokenLine3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROKENLINE3D_H__5C92ECF4_E199_492D_8250_AF07EFA79F13__INCLUDED_)
#define AFX_BROKENLINE3D_H__5C92ECF4_E199_492D_8250_AF07EFA79F13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectList.h"
#include "Line3D.h"

class BrokenLine3D   : public Object 
{
	friend class SurfDoc;
public:
	long id_umpoz;
	long id_ige;
	BYTE podoshva;

	PLANE_MEMBERS_VECTOR<Line3D> 								m_lines;
	ObjectList													m_lines_ObjectList;

	long m_nDrills;
	long m_nCuts;

	long n_surf;

	size_t GetPointsNumber();
	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();


	void Init(const BrokenLine3D& bp)
	{			
		this->n_surf				= bp.n_surf;
		this->m_nCuts				= bp.m_nCuts;
		this->m_nDrills				= bp.m_nDrills;

		// Objects' vectors
		this->m_lines				= bp.m_lines;
		this->m_lines_ObjectList.Init1(this->m_lines, this);
		this->id_umpoz				= bp.id_umpoz;
		this->id_ige				= bp.id_ige;
		this->podoshva				= bp.podoshva;
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
	BrokenLine3D& BrokenLine3D::operator=(const BrokenLine3D& bp);


	BrokenLine3D();
	BrokenLine3D(const BrokenLine3D & bp);
	BrokenLine3D(SurfDoc* pSurfDoc);
	virtual ~BrokenLine3D();

	void OnCreate(void);

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BrokenLine3D& ob);
	friend Archive& operator >>(Archive& ar, BrokenLine3D& ob);
};

#endif // !defined(AFX_BROKENLINE3D_H__5C92ECF4_E199_492D_8250_AF07EFA79F13__INCLUDED_)
