#pragma once

#include "Object.h"
class GeoObject : public Object
{
public:
	void SetLayer(const Layer* layer){this->SetLayer_NonVirtual(layer);}
	//##########################################################
	// pure virtual functions
	virtual bool UpdateExtremums(){return false;}
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean){}
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d){}
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z){}

	virtual bool ColorDialog(){return false;}
	virtual COLORREF GetColor(){return 0;}
	virtual void SetColor(COLORREF color){}

	virtual bool IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws){return false;}

	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM, LPARAM, void * ) ){}

		virtual void ReDraw(){}
		virtual void Draw(){}

	virtual void DrawGDIplus(Graphics& graphics, map_view * ){}

	virtual bool SaveAs(){return false;}
	virtual bool SaveAsBln(FILE * stream){return false;}
	virtual bool SaveAsDat(FILE * stream){return false;}
};
