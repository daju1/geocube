#pragma once
#include ".\object.h"
#include ".\collection.h"
#include ".\fastcollection.h"
#include "../../auto_build_3D/picks_search.h"
//#include "AutoBuildProfileDlg.h"

class AutoBuildProfile :
	public Object
{
public:
	static struct auto_build_parametrs	ab;
	static void auto_build_parametrs_Init();
	static void auto_build_parametrs_Init1();

	vect<Collection>					m_collections;
	ObjectList							m_collections_ObjectList;
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
	void Init(const AutoBuildProfile& bp)
	{
		// Objects' vectors
		this->m_collections				= bp.m_collections;
		this->m_collections_ObjectList.Init(this->m_collections, this);

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
			WhatSelected& ws);
	AutoBuildProfile& AutoBuildProfile::operator=(const AutoBuildProfile& bp);
	AutoBuildProfile(const AutoBuildProfile & bp);
	AutoBuildProfile(SurfDoc* pSurfDoc);

//	void AddInput(Primitive3D<CPoint3> * primitive);
	size_t GetPointsNumber(){return 0;}

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);


	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");


	void OnCreate(void);
	friend Archive& operator <<(Archive& ar, AutoBuildProfile& ob);
	friend Archive& operator >>(Archive& ar, AutoBuildProfile& ob);

	AutoBuildProfile(void);
	virtual ~AutoBuildProfile(void);

#if !VIEW_ONLY_VERSION
	bool init();
	bool init1();
#endif /*!VIEW_ONLY_VERSION*/
	Collection* CreateNewCollection(void);

};

