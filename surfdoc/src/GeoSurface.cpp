#include "../../surfer_connect/StdAfx.h"
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT
#include "../../lab/lab/labdoc.h"
#include "StdAfx.h"
#include ".\geosurface.h"
#include ".\surfdoc.h"
#include "winsurftree.h"
#include "logger/Logger.h"

extern HINSTANCE hInst;								// current instance


vector<surface_order_list_item *> GeoSurface::surface_order_list;
vector<surface_blank_order_list_item *> GeoSurface::surface_blank_order_list;// old version - do not use this!
vector<surface_blank_functions_list_item *> GeoSurface::surface_blank_functions_list;
bool GeoSurface::s_bInverse_order_in_the_tree = false;

GeoSurface::GeoSurface()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

GeoSurface::GeoSurface(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;
	this->m_surface.InitDoc(pSurfDoc);
//	this->m_blank_line.Init(pSurfDoc);
	OnCreate();
}
#define GEOSURFACE_VERSION 5
void GeoSurface::OnCreate(void)
{
	this->m_object_type = Object::object_type::geo_surface;
	this->m_object_version = GEOSURFACE_VERSION;
	this->m_max_object_version = GEOSURFACE_VERSION;

	m_blank_lines.OnCreate();
	m_cutFault_lines.OnCreate();
	m_izo_lines.OnCreate();
	m_cutplane_lines.OnCreate();
	m_cutplane_polygones.OnCreate();
	m_blank_polygones.OnCreate();

	this->m_blank_polygon_matrix.clear();

	id_umpoz = 0;
	id_surf = -1;
	id_ige = -1;
	podoshva = 0;
}

GeoSurface::GeoSurface(const GeoSurface & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
GeoSurface& GeoSurface::operator=(const GeoSurface& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

GeoSurface::~GeoSurface(void)
{
	ClearBlankPolygonMatrix();
}
bool GeoSurface::UpdateExtremums()
{
	if (this->m_surface.UpdateExtremums())
	{
		m_ptMax = this->m_surface.GetMax();
		m_ptMin = this->m_surface.GetMin();
		return true;
	}
	return false;
}
void GeoSurface::ClearCutlinesPolygones()
{
	this->m_cutplane_polygones.clear();
	this->m_cutplane_polygones_ObjectList.clear();
	this->m_cutplane_lines.clear();
	this->m_cutplane_lines_ObjectList.clear();
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
}
void GeoSurface::ZoomViewCutlinesPolygones(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}

}
void GeoSurface::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	this->m_surface.Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);	
	
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}

	this->ZoomViewCutlinesPolygones(zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);	

	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}

	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->Zoom(
					zoomX,zoomY,zoomZ, 
					x_mean,
					y_mean,
					z_mean
					);
			}
		}
	}
}

bool GeoSurface::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);

	
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blank_lines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}

	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_cutplane_lines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_cutplane_polygones.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}

	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_izo_lines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_cutFault_lines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blank_polygones.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}

	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				if ((*it2)->IsSelected(
					selected_view_pt, search_radius, ws	))
				{
					return true;
				}
			}
		}
	}

	if (this->m_surface.IsSelected(
				selected_view_pt, search_radius, ws	))
	{
		return true;
	}

	return false;
}

void GeoSurface::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	this->m_surface.EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
	
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}

	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
			}
		}
	}
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}

}
void GeoSurface::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
	this->m_surface.SetLayer(layer);;
	
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_lines.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->SetLayer(layer);
			}
		}
	}
}
void GeoSurface::DrawBlankLines()
{

	if (this->m_pSurfDoc) this->AddBlankLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().Draw();
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::ReDrawBlankLines()
{
	if (this->m_pSurfDoc) this->AddBlankLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().ReDraw();
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::DrawIzoLines()
{
	if (this->m_pSurfDoc) this->AddIzoLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().Draw();
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::ReDrawIzoLines()
{
	if (this->m_pSurfDoc) this->AddIzoLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().ReDraw();
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::DrawCutFaultLines()
{
	if (this->m_pSurfDoc) this->AddCutFaultLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().Draw();
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::ReDrawCutFaultLines()
{
	if (this->m_pSurfDoc) this->AddCutFaultLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().ReDraw();
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::DrawCutPlaneLines()
{
	if (this->m_pSurfDoc) this->AddCatPlaneLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_lines.GetCurrentMsg().Draw();
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::ReDrawCutPlaneLines()
{
	if (this->m_pSurfDoc) this->AddCatPlaneLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_lines.GetCurrentMsg().ReDraw();
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::DrawBlankPolygones()
{
	if (this->m_pSurfDoc) this->AddBlankPolygonesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().Draw();
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->Draw();
			}
		}
	}
}

void GeoSurface::ReDrawBlankPolygones()
{
	if (this->m_pSurfDoc) this->AddBlankPolygonesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().ReDraw();
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->ReDraw();
			}
		}
	}
}
void GeoSurface::DrawCutPolygones()
{
	if (this->m_pSurfDoc) this->AddCutPlanePolygonesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().Draw();
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}
}

void GeoSurface::ReDrawCutPolygones()
{
	if (this->m_pSurfDoc) this->AddCutPlanePolygonesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().ReDraw();
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}
}

void GeoSurface::AddBlankLinesItem(HWND hwndTV, HTREEITEM h2)
{
	HTREEITEM h3 = AddObjectListItem(hwndTV, "Blank Lines", &this->m_blank_lines_ObjectList, h2); 
	//=============================================================
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::AddIzoLinesItem(HWND hwndTV, HTREEITEM h2)
{
	//=============================================================
	HTREEITEM h3 = AddObjectListItem(hwndTV, "Izolines", &this->m_izo_lines_ObjectList, h2); 
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::AddCutFaultLinesItem(HWND hwndTV, HTREEITEM h2)
{
	//=============================================================
	this->m_cutFault_lines_ObjectList.m_bChecked = false;
	HTREEITEM h3 = AddObjectListItem(hwndTV, "Cutlines", &this->m_cutFault_lines_ObjectList, h2); 
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
}
void GeoSurface::AddCatPlaneLinesItem(HWND hwndTV, HTREEITEM h2)
{
	//=============================================================
	HTREEITEM h3 = AddObjectListItem(hwndTV, "CutPlaneLines", &this->m_cutplane_lines_ObjectList, h2); 
	if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
	//=============================================================
}
void GeoSurface::AddCutPlanePolygonesItem(HWND hwndTV, HTREEITEM h2)
{
	HTREEITEM h3 = AddObjectListItem(hwndTV, "cut_polygones", &this->m_cutplane_polygones_ObjectList, h2); 
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}
}
void GeoSurface::AddBlankPolygonesItem(HWND hwndTV, HTREEITEM h2)
{
	//=============================================================
	HTREEITEM h3 = AddObjectListItem(hwndTV, "blank_polygones", &this->m_blank_polygones_ObjectList, h2); 
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}
	//=============================================================
	
	h3 = AddObjectListItem(hwndTV, "blank_polygon_matrix", &this->m_blank_polygon_matrix_ObjectList, h2); 
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->AddItem_ToTree(hwndTV, h3);
			}
		}
	}
}
HTREEITEM GeoSurface::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
// printf("GeoSurface::AddItem_ToTree(HTREEITEM h1 = 0x%08x)\n", h1);
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	sprintf(szItemText, "\"%s\" id_surf=%d id_ige=%d id_umpoz=%d", this->GetName().c_str(), this->id_surf, this->id_ige, this->id_umpoz);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	this->m_surface.AddItem_ToTree(hwndTV, h2);
// printf("GeoSurface::AddItem_ToTree(return h2 = 0x%08x)\n", h2);
	/*//=============================================================
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "Blank Lines", &this->m_blank_lines_ObjectList, h2); 
		do
		{
			this->m_blank_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	//=============================================================
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "Izolines", &this->m_izo_lines_ObjectList, h2); 
		do
		{
			this->m_izo_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
	//=============================================================
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "Cutlines", &this->m_cutFault_lines_ObjectList, h2); 
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}

	//	removed to 
	//	void GeoSurface::DrawCutPlaneLines()
	//	{
	//		AddCatPlaneLinesItem(this->m_pSurfDoc->hwndTV, this->myTreeItem, this);
	//		if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	//		{
	//			do
	//			{
	//				this->m_cutplane_lines.GetCurrentMsg().Draw();
	//			}
	//			while(this->m_cutplane_lines.IncrementCurrentMsg());
	//		}
	//	}
	//	as AddCatPlaneLinesItem()
	//=============================================================
	/*if (this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "CutPlaneLines", &this->m_cutplane_lines_ObjectList, h2); 
		do
		{
			AddLineItem(hwndTV,
				h3,
				&this->m_cutplane_lines.GetCurrentMsg());
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}*/
	/*//=============================================================
	if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "cut_polygones", &this->m_cutplane_polygones_ObjectList, h2); 
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}
	//=============================================================
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		HTREEITEM h3 = AddObjectListItem(hwndTV, "blank_polygones", &this->m_blank_polygones_ObjectList, h2); 
		do
		{
			this->m_blank_polygones.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}*/
	//=============================================================
	return h2;
}
void GeoSurface::Draw()
{
	/*if(this->m_pSurfDoc)
	{
		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
		this->AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->parentTreeItem);

		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->m_surface.myTreeItem);
		this->m_surface.AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	}*/
	this->m_surface.Draw();

	this->DrawBlankLines();
	this->DrawIzoLines();
	this->DrawCutFaultLines();
	this->DrawCutPlaneLines();
	this->DrawBlankPolygones();
	this->DrawCutPolygones();
}

void GeoSurface::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	/*if(this->m_pSurfDoc)
	{
		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
		this->AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->parentTreeItem);

		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->m_surface.myTreeItem);
		this->m_surface.AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	}*/
	this->m_surface.ReDraw();

	this->ReDrawBlankLines();
	this->ReDrawIzoLines();
	this->ReDrawCutFaultLines();
	this->ReDrawCutPlaneLines();
	this->ReDrawBlankPolygones();
	this->ReDrawCutPolygones();
}

void GeoSurface::ReDrawWithoutTree()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	/*if(this->m_pSurfDoc)
	{
		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
		this->AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->parentTreeItem);

		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->m_surface.myTreeItem);
		this->m_surface.AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->myTreeItem);
	}*/
	this->m_surface.ReDrawWithoutTree();

	this->ReDrawBlankLines();
	this->ReDrawIzoLines();
	this->ReDrawCutFaultLines();
	this->ReDrawCutPlaneLines();
	this->ReDrawBlankPolygones();
	this->ReDrawCutPolygones();
}

BOOL CALLBACK DlgProc_GeoSurface_PropertiesDialog( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static GeoSurface * lpGeoSurface;
		
	char str[128];

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpGeoSurface = (GeoSurface *)lParam;
			//**************************************
			// #############################################################
			// #############################################################

			if (lpGeoSurface)
			{
				switch(lpGeoSurface->podoshva)
				{
				case 1:
					{
						CheckRadioButton(hDlg, IDC_RADIO_PODOSHVA_1, IDC_RADIO_PODOSHVA_3, IDC_RADIO_PODOSHVA_1);
					}
					break;
				case 2:
					{
						CheckRadioButton(hDlg, IDC_RADIO_PODOSHVA_1, IDC_RADIO_PODOSHVA_3, IDC_RADIO_PODOSHVA_2);
					}
					break;
				default:
					{
						CheckRadioButton(hDlg, IDC_RADIO_PODOSHVA_1, IDC_RADIO_PODOSHVA_3, IDC_RADIO_PODOSHVA_3);
					}
					break;
				}
			}
		
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{		
		case IDC_RADIO_PODOSHVA_1:
			{
				if (lpGeoSurface)
				{
					lpGeoSurface->SetPodoshva(1);
				}
			}
			break;
		case IDC_RADIO_PODOSHVA_2:
			{
				if (lpGeoSurface)
				{
					lpGeoSurface->SetPodoshva(2);
				}
			}
			break;
		case IDOK:
			EndDialog( hDlg, IDCANCEL );
			break;
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}







void GeoSurface::PropertiesDialog()
{
	HANDLE hDialog = LoadResource( hInst,										
		FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_GEOSURFACE_PROPERTY_DIALOG),
														RT_DIALOG ) );	

	LPVOID lpDialog = LockResource( hDialog );						
	HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, 
		this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL,
		(DLGPROC)::DlgProc_GeoSurface_PropertiesDialog,
		(LPARAM)this );
						
	ShowWindow(hDlg, SW_SHOW);
}

void GeoSurface::SetPodoshva(BYTE p)
{
	this->podoshva = p;
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		this->m_pSurfDoc->GetLabDoc()->GridDataSurfacesSetPodoshva(
			this->m_pSurfDoc->Get_ID_OBJ(), 
			this->id_surf,
			p);
	}
}
bool GeoSurface::ColorDialog(void)
{
	return false;
}

COLORREF GeoSurface::GetColor(void)
{
	return COLORREF();
}

void GeoSurface::SetColor(COLORREF color)
{
}

void GeoSurface::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	this->m_surface.CutAndDisvisible(positive, a, b, c, d);
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}	
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
	/*if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}*/
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->CutAndDisvisible(positive, a, b, c, d);
			}
		}
	}
}

void GeoSurface::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	this->m_surface.CutXYZandDisvisible(subcube_number, X, Y, Z);
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_lines.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	if (this->m_izo_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_izo_lines.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_izo_lines.IncrementCurrentMsg());
	}
	if (this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutFault_lines.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}	
	/*if (this->m_cutplane_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_cutplane_polygones.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_cutplane_polygones.IncrementCurrentMsg());
	}*/
	if (this->m_blank_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_blank_polygones.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_blank_polygones.IncrementCurrentMsg());
	}
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->CutXYZandDisvisible(subcube_number, X, Y, Z);
			}
		}
	}
}
void GeoSurface::AddIzoLine(CPoint3* pts, int len, COLORREF color )
{
	Line3D line(this->m_pSurfDoc);
	m_izo_lines.AddMsg(&line);
	m_izo_lines.GetLastMsg().InitPoints(pts, len, color);
	m_izo_lines.GetLastMsg().SetLayer(this->GetLayer());
	m_izo_lines_ObjectList.Init(m_izo_lines, this);
}
void GeoSurface::AddCutFaultLine(CPoint3* pts, int len, COLORREF color )
{
	Line3D line(this->m_pSurfDoc);
	m_cutFault_lines.AddMsg(&line);
	m_cutFault_lines.GetLastMsg().InitPoints(pts, len, color);
	m_cutFault_lines.GetLastMsg().SetLayer(this->GetLayer());
	m_cutFault_lines_ObjectList.Init(m_cutFault_lines, this);
}
void GeoSurface::AddCutPlaneLine(CPoint3* pts, int len, COLORREF color )
{
	Line3D line(this->m_pSurfDoc);
	m_cutplane_lines.AddMsg(&line);
	m_cutplane_lines.GetLastMsg().InitPoints(pts, len, color);
	m_cutplane_lines.GetLastMsg().SetLayer(this->GetLayer());
	m_cutplane_lines.GetCurrentMsg().SetName(this->GetName().c_str());
	m_cutplane_lines_ObjectList.Init(m_cutplane_lines, this);
}

void GeoSurface::SavingAsRazrez_of_CutPlaneLines(FILE *fd, 
												 SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
	if(this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			//this->m_cutplane_lines.GetCurrentMsg().SetName(this->GetName().c_str());
			this->m_cutplane_lines.GetCurrentMsg().SavingAsRazrez(fd,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
}
bool GeoSurface::SavingAsRazrez_of_CutPlaneLines(dimeModel * model,  dimeBlock * block, 
												 SSaveProfData &sprData,
												 double a, double b, double c, double d,
												 double minX, double minY, double minZ,
												 double maxX, double maxY, double maxZ)
{
	bool status = false;
	if(this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			//this->m_cutplane_lines.GetCurrentMsg().SetName(this->GetName().c_str());
			if (this->m_cutplane_lines.GetCurrentMsg().SavingAsRazrez(model,block,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}

	printf("GeoSurface::SavingAsRazrez_of_CutPlaneLines end status = %d\n", status);
	return status;
}
void GeoSurface::BlankingOfBlankLines(CPoint3 * base_point, CPoint3& ptMax, CPoint3& ptMin)
{
	// vector of pointers to blank lines
	vector<Line3D *> p_blank_lines;
	p_blank_lines.resize(0);
    if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blank_lines.GetCurrentMsg().m_bChecked)
			{
				Line3D * p_blank_line = &this->m_blank_lines.GetCurrentMsg();
				p_blank_lines.push_back(p_blank_line);
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	printf("p_blank_lines.size() = %d\n", p_blank_lines.size());

	for(size_t iline = 0; iline < p_blank_lines.size(); iline++)
	{
		printf("iline = %d\n", iline);

		Line3D * p_blank_line = p_blank_lines[iline];

		if (this->m_blank_lines.SetCurrentMsgOnFirst())
		{
			do
			{
				if(this->m_blank_lines.GetCurrentMsg().m_bChecked)
				{
					Line3D * p_line = &this->m_blank_lines.GetCurrentMsg();
					printf("p_line->GetPointsNumber() = %d\n", 
						p_line->GetPointsNumber());
					if (p_line && p_blank_line && p_line != p_blank_line)
					{
						for( size_t i = 0; i < p_line->GetPointsNumber(); i++)
						{
							int rez;
							if (this->m_surface.m_zflag == 0)
							{
								rez = p_blank_line->WhatSidesOfTwoPoint(0, 
									(*base_point), 
									p_line->GetDocumentPoint(i));
							}
							else
							{
								rez = p_blank_line->WhatSidesOfTwoPoint(this->m_surface.m_zflag, 
									(*base_point).ConvertTo(this->m_surface.m_zflag), 
									p_line->GetDocumentPoint(i).ConvertTo(this->m_surface.m_zflag));
							}
							/*if (rez == -1)printf("%d pt1 [%f %f %f] pt12 [%f %f %f] rez = %d\n", i, 
								(*base_point).ConvertTo(this->m_surface.m_zflag).x,
								(*base_point).ConvertTo(this->m_surface.m_zflag).y,
								(*base_point).ConvertTo(this->m_surface.m_zflag).z,

								p_line->GetDocumentPoint(i).ConvertTo(this->m_surface.m_zflag).x,
								p_line->GetDocumentPoint(i).ConvertTo(this->m_surface.m_zflag).y,
								p_line->GetDocumentPoint(i).ConvertTo(this->m_surface.m_zflag).z,

								rez
								);*/

							if (rez == -1)
								p_line->GetDocumentPoint(i).bVisible = false;
						}
					}
				}
			}
			while(this->m_blank_lines.IncrementCurrentMsg());
		}
	}
	// вытираем все невидимые точки
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blank_lines.GetCurrentMsg().m_bChecked)
			{
				this->m_blank_lines.GetCurrentMsg().EraseAllUnvisible();				
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	// удаляем все отключенные и пустые объекты линий бланкования
	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
e_start_of_blank_lines_cicle:
			if(!this->m_blank_lines.GetCurrentMsg().m_bChecked
				||
				this->m_blank_lines.GetCurrentMsg().GetPointsNumber() < 2)
			{
				if(this->m_blank_lines.EraseCurrentMsg())
						goto e_start_of_blank_lines_cicle;
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
		this->m_blank_lines_ObjectList.Init(this->m_blank_lines, this);		
	}
	p_blank_lines.resize(0);
	// ищем максимум и минимум x,y
	vector<CPoint3> vptmax,vptmin;

	if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_blank_lines.GetCurrentMsg().GetPointsNumber())
			{
				if(this->m_blank_lines.GetCurrentMsg().UpdateExtremums())
				{
					vptmax.push_back(this->m_blank_lines.GetCurrentMsg().GetMax());
					vptmin.push_back(this->m_blank_lines.GetCurrentMsg().GetMin());
				}
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	bool start = true;
	for( int i = 0; i< vptmax.size() && i < vptmin.size(); i++)
	{
		CPoint3 ptmax, ptmin;
		ptmax = vptmax[i];
		ptmin = vptmin[i];
		if (start)
		{
			start = false;
			// real x
			ptMax.x = ptmax.x;
			ptMin.x = ptmin.x;
			// real y
			ptMax.y = ptmax.y;
			ptMin.y = ptmin.y;
			// real z
			ptMax.z = ptmax.z;
			ptMin.z = ptmin.z;
		}
		else
		{
			// real x
			if (ptMax.x < ptmax.x) ptMax.x = ptmax.x;
			if (ptMin.x > ptmin.x) ptMin.x = ptmin.x;
			// real y
			if (ptMax.y < ptmax.y) ptMax.y = ptmax.y;
			if (ptMin.y > ptmin.y) ptMin.y = ptmin.y;
			// real z
			if (ptMax.z < ptmax.z) ptMax.z = ptmax.z;
			if (ptMin.z > ptmin.z) ptMin.z = ptmin.z;
		}
	}
	vptmin.clear();
	vptmax.clear();

}
bool GeoSurface::ProjectBlankLinesOnSurface()
{
	bool result = false;

    if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blank_lines.GetCurrentMsg().m_bChecked)
			{
				Line3D * p_blank_line = &this->m_blank_lines.GetCurrentMsg();
				size_t len = p_blank_line->GetPointsNumber();

				for (size_t i = 0; i < len; i++)
				{
					double x = p_blank_line->GetDocumentPoint(i).x;
					double y = p_blank_line->GetDocumentPoint(i).y;
					double z = p_blank_line->GetDocumentPoint(i).z;

					double r;

					this->m_surface.Projection(x, y, z, // координаты точки в пространстве
						r, // выход - расстояние от точки до поверхности
						&p_blank_line->GetDocumentPoint(i)); // координаты точки проекции на поверхности
				}
				result = true;
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
	return result;
}
void GeoSurface::BlankWithOwnBlankLines(bool toPresetAllVisible, bool to_continue_line_to_borders, CPoint3 * base_point)
{
	if (toPresetAllVisible)
	{
		for (size_t i = 0; i < this->m_surface.GetPointsNumber(); i++)
		{
			this->m_surface.m_vdPoints[i].bVisible = true;
		}
	}
#if 0
	// vector of pointers to blank lines
	vector<Line3D *> p_blank_lines;
	p_blank_lines.resize(0);
    if (this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_blank_lines.GetCurrentMsg().m_bChecked)
			{
				Line3D * p_blank_line = &this->m_blank_lines.GetCurrentMsg();
				p_blank_lines.push_back(p_blank_line);
			}
		}
		while(this->m_blank_lines.IncrementCurrentMsg());
	}
#endif
#if 1		
	this->m_surface.Blank(
			this->m_blank_lines, 
			to_continue_line_to_borders, 
			*this, 
			base_point);
#else
	printf("p_blank_lines.size() = %d\n", p_blank_lines.size());

	for(size_t iline = 0; iline < p_blank_lines.size(); iline++)
	{
		printf("iline = %d\n", iline);

		Line3D * p_blank_line = p_blank_lines[iline];
		this->m_surface.Blank(
			*p_blank_line, 
			to_continue_line_to_borders, 
			(void *) this, 
			base_point);
	}
#endif
	this->Zooming();
	this->ReDraw();
}
void GeoSurface::MakeQuadBlankPolygons(
	vector<blank_polygon_point>& blank_polygon_points)
{
/*printf("MakeQuadBlankPolygons\n" );
printf("blank_polygon_points.size() = %u\n", blank_polygon_points.size());
for (size_t ii = 0; ii < blank_polygon_points.size(); ii++)
{
	printf("[%f %f %f %d]\n", 
		blank_polygon_points[ii].pt.x,
		blank_polygon_points[ii].pt.y,
		blank_polygon_points[ii].pt.z,
		blank_polygon_points[ii].pt.bVisible
		);
}*/
	// разделение полигонов по признаку номера  линии - 
	// разделяются непересекающиеся линии, имеющие разные номера
	vector<blank_polygon_point>::iterator iter;
	// до тех пор пока не исчерпаем весь массив
	while(blank_polygon_points.size() > 0)
	{
		// сначала ищем номер линии, отличный от -1
		int current_line_number;
		//здесь формируем полигон
		Poligon3D poly(this->m_pSurfDoc);
		poly.Init((Surface3D*) &this->m_surface);
		poly.SetColor(this->m_surface.m_color);
		//***********************************
		iter = blank_polygon_points.begin();
		do
		{
			current_line_number = (*iter).line_number;
			poly.PushBack((*iter).pt); iter = blank_polygon_points.erase(iter);
		}
		while(iter != blank_polygon_points.end() && current_line_number < 0);
		// теперь мы поместили в полигон первую точку, имеющую номер линии
		bool to_push_coner_points = true;
		while (iter != blank_polygon_points.end())
		{
			if ((*iter).line_number < 0)
			{
				if (to_push_coner_points)
				{
					poly.PushBack((*iter).pt); iter = blank_polygon_points.erase(iter);
				}
				else
					iter++;
			}
			else
			{
				if ((*iter).line_number == current_line_number)
				{
					to_push_coner_points = true;
					poly.PushBack((*iter).pt); iter = blank_polygon_points.erase(iter);
				}
				else
				{
					to_push_coner_points = false;
					iter++;
				}
			}
		}
/*
printf("poly.GetPointsNumber() = %u\n", poly.GetPointsNumber());
for (size_t ii = 0; ii < poly.GetPointsNumber(); ii++)
{
	printf("[%f %f %f %d]\n", 
		poly.GetDocumentPoint(ii).x,
		poly.GetDocumentPoint(ii).y,
		poly.GetDocumentPoint(ii).z,
		poly.GetDocumentPoint(ii).bVisible
		);
}*/
		if(poly.GetPointsNumber()>2) 
		{
			//if (pGeoSurface) 
			//{
				this->m_blank_polygones.AddMsg(&poly);
				this->m_blank_polygones_ObjectList.Init(this->m_blank_polygones, this);
			//}
			//else
			//	this->m_pSurfDoc->AddPoligon(poly);
		}
	}
}

void GeoSurface::AddBlankLine(int inside)
{
	Line3D line(this->m_pSurfDoc);

	if (inside == 0)
		// заливка внутри - включаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam |= OBJECT_FLAG_INSIDE_BLANK_BIT;
	else
		// заливка снаружи - выключаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam &= ~OBJECT_FLAG_INSIDE_BLANK_BIT;

	m_blank_lines.AddMsg(&line);
	m_blank_lines_ObjectList.Init(m_blank_lines, this);
}
void GeoSurface::AddBlankLine(int inside, CPoint3* pts, int len, COLORREF color )
{
	Line3D line(this->m_pSurfDoc);

	if (inside == 0)
		// заливка внутри - включаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam |= OBJECT_FLAG_INSIDE_BLANK_BIT;
	else
		// заливка снаружи - выключаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam &= ~OBJECT_FLAG_INSIDE_BLANK_BIT;

	this->m_blank_lines.AddMsg(&line);
	this->m_blank_lines.GetLastMsg().InitPoints(pts, len, color);
	this->m_blank_lines.GetLastMsg().SetLayer(this->GetLayer());
	this->m_blank_lines_ObjectList.Init(this->m_blank_lines, this);
}
void GeoSurface::AddBlankLine(int inside, Line3D &line)
{
	line.Init(this->m_pSurfDoc);

	if (inside == 0)
		// заливка внутри - включаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam |= OBJECT_FLAG_INSIDE_BLANK_BIT;
	else
		// заливка снаружи - выключаем первый бит 
		// в пользовательских данных объекта линии бланкования
		line.m_lParam &= ~OBJECT_FLAG_INSIDE_BLANK_BIT;

	m_blank_lines.AddMsg(&line);
	m_blank_lines_ObjectList.Init(m_blank_lines, this);
}
bool GeoSurface::LoadBlankBln(void)
{
	char lpstrFile[1024];
	if (OpenFileDlg(NULL, "Golden Software Blanking (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
	{
		vector<vector<vector<double> > > vvvd;
		vector<int> vinside;
		if (0 == ReadBlnFile(lpstrFile, &vvvd, &vinside))
		{
			if (this)
			{
				for(size_t nline = 0; nline < vvvd.size(); nline++)
				{
					this->AddBlankLine(vinside[nline]);
					for (size_t npoint = 0; npoint < vvvd[nline].size(); npoint++)
					{
						CPoint3 pt(0.0,0.0,0.0,true);
						for (size_t ndim = 0; ndim < vvvd[nline][npoint].size(); ndim++)
						{
							switch(ndim)
							{
							case 0:
								pt.x = vvvd[nline][npoint][ndim];
								break;
							case 1:
								pt.y = vvvd[nline][npoint][ndim];
								break;
							case 2:
								pt.z = vvvd[nline][npoint][ndim];
								break;
							}
						}
						if(this->m_blank_lines.SetCurrentMsgOnLast())
						{
							this->m_blank_lines.GetCurrentMsg().PushBack(pt);
						}
					}
				}
				return true;
			}
		}		
	}
	return false;
}
bool GeoSurface::BlankAbove(GeoSurface & geo_surf)
{
	INFO("BlankAbove()");
	short type_of_cutline = 4;

	int cutting_number = 0;
	int surf_number = 0;
	bool toDrawPolygon = false;
	
	bool positive = true;

	this->m_surface.Cutting(&geo_surf.m_surface, type_of_cutline, cutting_number, surf_number, toDrawPolygon, positive, 
		this
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
#else
		, &this->m_blank_polygon_matrix_ObjectList
      , &this->m_blank_polygon_matrix
#endif
#else
		, &this->m_blank_polygones_ObjectList
		, &this->m_blank_polygones
#endif
		);
	INFO("BlankAbove() pre CutLine()");

	this->m_surface.CutLine(type_of_cutline, 0, (void *) NULL, *this, surf_number );

	bool result = this->m_surface.BlankAbove(geo_surf.m_surface
#if ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
      , 0
#else
      , &this->m_blank_polygon_matrix
#endif
      );
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
	this->m_blank_polygon_matrix_ObjectList.Init2_std_vector_std_vector_ptr(this->m_blank_polygon_matrix, this);
#endif
#endif
	INFO("BlankAbove() end");
	return result;
}
bool GeoSurface::BlankUnder(GeoSurface & geo_surf)
{
	INFO("BlankUnder()");
	short type_of_cutline = 4;

	int cutting_number = 0;
	int surf_number = 0;
	bool toDrawPolygon = false;
	
	bool positive = false;

	this->m_surface.Cutting(&geo_surf.m_surface, type_of_cutline, cutting_number, surf_number, toDrawPolygon, positive, 
		this
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
#else
		, &this->m_blank_polygon_matrix_ObjectList
      , &this->m_blank_polygon_matrix
#endif
#else
		&this->m_blank_polygones_ObjectList, &this->m_blank_polygones
#endif
		);
	this->m_surface.CutLine(type_of_cutline, 0, (void *) NULL, *this, surf_number );

    bool result = this->m_surface.BlankUnder(geo_surf.m_surface
#if ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
      , 0
#else
      , &this->m_blank_polygon_matrix
#endif
       );
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
	this->m_blank_polygon_matrix_ObjectList.Init2_std_vector_std_vector_ptr(this->m_blank_polygon_matrix, this);
#endif
#endif
	return result;
}
bool GeoSurface::Blank()
{
	if (this->LoadBlankBln())
	{
		this->m_surface.Blank(this->m_blank_lines, false, *this, NULL);
		this->Zooming();
		this->ReDraw();
		return true;
	}
	return false;
}

bool GeoSurface::BlankOnBasePoint(CPoint3& base_point)
{
	if (this->LoadBlankBln())
	{
		this->m_surface.Blank(this->m_blank_lines, false, *this, & base_point);
		this->Zooming();
		this->ReDraw();
		return true;
	}
	return false;
}


void GeoSurface::CopyCutlinesToBlankLines()
{
	if(this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_cutFault_lines.GetCurrentMsg().m_bChecked)
				this->m_blank_lines.AddMsg(&this->m_cutFault_lines.GetCurrentMsg());
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
	this->m_blank_lines_ObjectList.Init(this->m_blank_lines, this);
}


void GeoSurface::CopyCutPlaneLinesToBlankLines()
{
	if(this->m_cutplane_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_cutplane_lines.GetCurrentMsg().m_bChecked)
				this->m_blank_lines.AddMsg(&this->m_cutplane_lines.GetCurrentMsg());
		}
		while(this->m_cutplane_lines.IncrementCurrentMsg());
	}
	this->m_blank_lines_ObjectList.Init(this->m_blank_lines, this);
}


void GeoSurface::BlankWithOwnCutlines()
{
	printf("GeoSurface::BlankWithOwnCutlines\n"); 
#if 1
	this->m_surface.Blank(this->m_cutFault_lines, true, *this, NULL);
#else
	if(this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_cutFault_lines.GetCurrentMsg().m_bChecked)
				this->m_surface.Blank(this->m_cutFault_lines.GetCurrentMsg(), 
					true, this, NULL);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
#endif
	this->Zooming();
	this->ReDraw();
}
void GeoSurface::BlankWithOwnCutlinesOnBasePoint(CPoint3& base_point)
{
	printf("GeoSurface::BlankWithOwnCutlinesOnBasePoint(CPoint3& base_point [%f %f %f])\n", 
		base_point.x, 
		base_point.y, 
		base_point.z 
		);
#if 1
	this->m_surface.Blank(this->m_cutFault_lines, true, *this, &base_point);
#else
	if(this->m_cutFault_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_cutFault_lines.GetCurrentMsg().m_bChecked)
				this->m_surface.Blank(this->m_cutFault_lines.GetCurrentMsg(), 
					true, this, &base_point);
		}
		while(this->m_cutFault_lines.IncrementCurrentMsg());
	}
#endif
	this->Zooming();
	this->ReDraw();
}

void GeoSurface::ClearBlankLines()
{
	m_blank_lines.clear();
	m_blank_lines_ObjectList.clear();
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
}
LRESULT CALLBACK DlgProcSurfIzolines2( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static GeoSurface * pGeoSurface;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			pGeoSurface = (GeoSurface *)lParam;
//			lpSurfDlgMem->pSurfDoc->SetIzolines();

		
			char str[1023];
//			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_izo_start);
//			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_START, str);

			sprintf(str,"%lf",pGeoSurface->m_pSurfDoc->m_izo_step);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_STEP, str);

//			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_izo_end);
//			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_END, str);

//			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_part);
//			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_PART, str);

			sprintf(str,"%lf",pGeoSurface->m_pSurfDoc->m_zd_min);
			SetDlgItemText(hDlg, IDC_STATIC_SURF_ZMIN, str);

			sprintf(str,"%lf",pGeoSurface->m_pSurfDoc->m_zd_max);
			SetDlgItemText(hDlg, IDC_STATIC_SURF_ZMAX, str);


			SetDlgItemInt(hDlg,IDC_EDIT_SURF_IZO_ANGLE_LOCAL_MIN, 1, false);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_COS_BORDER, "-0.99");

			
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				char str[1023];

				GetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_STEP,str,1022);
				double v = atof (str);
				if (v > 0.0)
					pGeoSurface->m_pSurfDoc->m_izo_step = v;
				else
					MessageBox(0, "Enter a valid value of step", "Izolines dialog", 0);
								
				pGeoSurface->izolines();

				pGeoSurface->Zooming();
				pGeoSurface->ReDraw();

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(pGeoSurface->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(pGeoSurface->m_pSurfDoc->hSurfWnd,&rect, true);

			}
			break;
		
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

extern HINSTANCE hInst;
void GeoSurface::SetName(string s)
{
//	GridData * pGridData = NULL;
//	if (this->m_pSurfDoc && (pGridData = this->m_pSurfDoc->FindGridData(this->id_surf)))
//	{	
//		pGridData->SetName(s);
//	}
//	else
		this->Object::SetName(s);
}

bool GeoSurface::RebuildByGridData()
{							
	if (this->m_pSurfDoc)
	{
		GridData * pGridData = NULL;
		/*if (this->m_pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
		{
			do
			{
				//if (0 == strcmp(this->GetName().c_str(),
				//	this->m_pSurfDoc->m_grid_data.GetCurrentMsg().GetName().c_str()))
				if (this->id_surf == this->m_pSurfDoc->m_grid_data.GetCurrentMsg().id_surf)
				{
					pGridData = &this->m_pSurfDoc->m_grid_data.GetCurrentMsg();
				}

			}
			while(this->m_pSurfDoc->m_grid_data.IncrementCurrentMsg());
		}

		if (!pGridData)*/
			pGridData = this->m_pSurfDoc->FindGridData(id_surf);

		if (pGridData)
		{
			//bool useSurfer = IDYES == MessageBox(0, "Хотите ли вы использовать стандартные алгоритмы Surfer?", "GeoSurface::RebuildByGridData()", MB_YESNO);
			bool to_allocate = true;
			griddata_dialog(to_allocate, this->m_pSurfDoc, pGridData, this->m_pSurfDoc->hSurfWnd, griddata_dialog::griddata_application::unknown, this, false, false);
		}
		else
		{
			char str[1024];
			sprintf(str, "Соответствующий GridData для %s на найден", this->GetName().c_str());
			MessageBox(0, str, "GeoSurface::RebuildByGridData()", MB_OK);
		}

	}
	return false;
}
bool GeoSurface::Izolines()
{							
	HANDLE hDialog = LoadResource( hInst,
		FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_IZOLINES),
		RT_DIALOG ) );
    
	LPVOID lpDialog = LockResource( hDialog );
	HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, m_pSurfDoc->hSurfWnd,
		(DLGPROC)DlgProcSurfIzolines2,
		(LPARAM)this );
	ShowWindow(hDlg, SW_SHOW);
	return false;
}
bool GeoSurface::izolines()
{
	int surf_number = 0;
	int cutting_number = 0;
	double izo_start = this->m_pSurfDoc->m_izo_step * ceil(m_surface.GetMin().z / this->m_pSurfDoc->m_izo_step);
	double izo_end   = this->m_pSurfDoc->m_izo_step * floor(m_surface.GetMax().z / this->m_pSurfDoc->m_izo_step);
	for (double  z_level = izo_start; z_level <= izo_end; z_level += this->m_pSurfDoc->m_izo_step)
	{
		m_surface.Cutting(0.0,0.0,1.0,-z_level, 
			false, true, 
			5, cutting_number, surf_number, 
			NULL, NULL, (void*) NULL, 
			this, 
			&this->m_blank_polygon_matrix,
			&this->m_blank_polygones_ObjectList, 
			&this->m_cutplane_polygones);

		m_surface.CutLine( 5, cutting_number, (void *) NULL, *this, surf_number );
		cutting_number++;
	}
	return true;
}


void GeoSurface::ClearBlankPolygonMatrix()
{
	for (std::vector<std::vector<Poligon3D *> >::iterator it1 = this->m_blank_polygon_matrix.begin(); 
		it1 != this->m_blank_polygon_matrix.end(); ++it1)
	{
		for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
		{
			if ((*it2))
			{
				(*it2)->Free();
				delete (*it2);
			}
		}
	}

	this->m_blank_polygon_matrix.clear();
	this->m_blank_polygon_matrix_ObjectList.Init2_std_vector_std_vector_ptr(this->m_blank_polygon_matrix, this);
}

bool GeoSurface::NoBlank()
{
	this->m_surface.NoBlank();
	this->m_blank_polygones.clear();
	this->m_blank_polygones_ObjectList.Init(this->m_blank_polygones, this);

	ClearBlankPolygonMatrix();
		


//	this->ClearBlankLines();

	this->Zooming();
	this->ReDraw();

	return true;
}

bool GeoSurface::MakeFaultSection(LPSURFER7FAULTSECTION faultSection)
{
	faultSection->traces = NULL;
	faultSection->vertexes = NULL;
	// инициализация линий разломов
	faultSection->nTraces = this->m_traces.size();
	if (faultSection->nTraces)
	{
		faultSection->traces = new Trace[faultSection->nTraces];
		for (long n = 0; n < faultSection->nTraces; n++)
		{
			faultSection->traces[n] = this->m_traces[n];
		}
	}

	faultSection->nVertices = this->m_vertices.size();
	if (faultSection->nVertices)
	{
		faultSection->vertexes = new Vertex[faultSection->nVertices];
		for (long n = 0; n < faultSection->nVertices; n++)
		{
			faultSection->vertexes[n] = this->m_vertices[n];
		}
	}
	return true;
}
bool GeoSurface::SaveBlankLines()
{
	bool status = false;
	TCHAR lpstrFile[256]; lpstrFile[0] = '\0';
	TCHAR filter[] =     TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
						TEXT("All Files (*.*)\0*.*\0");

	//sprintf(lpstrFile, "%s\\razrez", directory);
	sprintf(lpstrFile, "%s blank", this->name.c_str());
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return status;

	FILE *stream;
	stream = fopen(lpstrFile,"wt");
	if (!stream)
	{
		return status;
	}
	vector<Object *>::iterator iter;

	if(this->m_blank_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			status = this->m_blank_lines.GetCurrentMsg().SaveAsBln(stream);
		}
		while (this->m_blank_lines.IncrementCurrentMsg());
	}

	fclose (stream);
	return status;
}
void GeoSurface::SaveAsSurfer7Grid()
{
	DWORD nFilterIndex = 0;
	char file[2048];
	file[0] = '\0';
	strcpy(file, this->name.c_str());
	if (SaveFileDlg(this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL, file,
		"Surfer 7 (*.grd)\0*.grd\0All files \0*.*\0", nFilterIndex) == S_OK)
	{	
		Grid* pGrid = new Grid;
		if (pGrid && this->m_surface.MakeGridSection(&pGrid->gridSection)
			&& this->MakeFaultSection(&pGrid->faultSection))
		{
			::SaveAsSurfer7Grid(file, pGrid);
			// free 
			FreeGrid(pGrid);
		}
	}
}

void GeoSurface::GridVolume()
{
	double volume = this->m_surface.GridVolume();
	printf ("GridVolume of \"%s\" is %f m^3\n", this->GetName().c_str(), volume);
}

void GeoSurface::Init(long _id_surf, BYTE _podoshva, long _id_ige, short zflag, Grid * pgrid, COLORREF color)
{
	this->id_ige = _id_ige;
	this->id_surf = _id_surf;
	this->podoshva = _podoshva;
	// инициализация массива грида
	this->m_surface.Init(zflag, &pgrid->gridSection, color);
	// инициализация линий разломов
	this->m_traces.resize(pgrid->faultSection.nTraces);
	for (long n = 0; n < pgrid->faultSection.nTraces; n++)
	{
		this->m_traces[n] = pgrid->faultSection.traces[n];
	}

	this->m_vertices.resize(pgrid->faultSection.nVertices);
	for (long n = 0; n < pgrid->faultSection.nVertices; n++)
	{
		this->m_vertices[n] = pgrid->faultSection.vertexes[n];
	}
}

void GeoSurface::BuildSurfacesCutlines(void)
{	
	if (this->m_pSurfDoc)
	{
		short type_of_cutline = 4;
			
		int fault_number = 0;
		int surf_number = 0;

		bool toDrawPolygon = true;
		bool positive = true;

		this->ClearBlankPolygonMatrix();


		if (this->m_pSurfDoc->m_faults.SetCurrentMsgOnFirst() 
			&& this->m_pSurfDoc->m_faults_ObjectList.m_bChecked)
		{
			do
			{
				if (this->m_pSurfDoc->m_faults.GetCurrentMsg().IsCheckedEx()
					&& this != &this->m_pSurfDoc->m_faults.GetCurrentMsg())
				{

					this->m_surface.Cutting(&this->m_pSurfDoc->m_faults.GetCurrentMsg().m_surface, 
						type_of_cutline, fault_number, surf_number, toDrawPolygon, positive,
						this
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
						, &this->m_blank_polygon_matrix_ObjectList, &this->m_blank_polygon_matrix
#endif
#else
						, &this->m_blank_polygones_ObjectList, &this->m_blank_polygones
#endif
						);
					fault_number++;
				}
			}
			while(this->m_pSurfDoc->m_faults.IncrementCurrentMsg());
		}

		//this->m_surface.CutLine(type_of_cutline, 0, (void *) NULL, (void*)this, surf_number );

		if (this->m_pSurfDoc->m_surfaces.SetCurrentMsgOnFirst() 
			&& this->m_pSurfDoc->m_surfaces_ObjectList.m_bChecked)
		{
			do
			{
				if (this->m_pSurfDoc->m_surfaces.GetCurrentMsg().IsCheckedEx()
					&& this != &this->m_pSurfDoc->m_surfaces.GetCurrentMsg())
				{
					this->m_surface.Cutting(&this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_surface, 
						type_of_cutline, fault_number, surf_number, toDrawPolygon, positive,
						this
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
						, &this->m_blank_polygon_matrix_ObjectList, &this->m_blank_polygon_matrix
#endif
#else
						, &this->m_blank_polygones_ObjectList, &this->m_blank_polygones
#endif
						);
					fault_number++;
				}
			}
			while(this->m_pSurfDoc->m_surfaces.IncrementCurrentMsg());
		}
		this->m_surface.CutLine(type_of_cutline, 0, (void *) NULL, *this, surf_number );

		this->Zooming();
		this->ReDraw();
	}
}

bool GeoSurface::SetColorFromCurrentWellsSloj()
{
	if (this->m_surface.SetColorFromCurrentWellsSloj())
	{
		this->ReDraw();
		return true;
	}
	return false;
}

void GeoSurface::SetColorFromIGE()
{
	if (!this->m_pSurfDoc)
		return;

	EngineerGeoElement * eng = this->m_pSurfDoc->FindEngineerGeoElement(this->id_ige);
	if(!eng)
		return;

	COLORREF color = eng->GetColor();
	this->m_surface.SetColor(color);
}

void GeoSurface::FillContextMenu(HMENU& hMenu)
{

	this->Object::FillContextMenu(hMenu);
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACESAVEASSURFER7GRID, "&Save As Surfer 7 grid" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFASE_GEOSURFACESAVEBLANKLINES, "&Save Blank Lines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFASE_GEOSURFACEIZOLINES, "&IzoLines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFASE_GRIDVOLUME, "&Grid Volume" );
	
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACELOADBLANKLINES, "&Load Blank Lines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANK, "&Blank" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANKONBASEPOINT, "&Blank on base point" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACECOPYCUTLINESTOBLANKLINES, "&Copy Cutlines to Blank Lines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACECOPYCUTPLANELINESTOBLANKLINES, "&Copy Cut Plane Lines to Blank Lines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANKOFBLANKLINES, "&Blank of Blank Lines (on base point)" );


	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANKWITHOWNBLANKLINES, "&Blank with own blank lines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANKWITHOWNBLANKLINESONBASEPOINT, "&Blank with own blank lines on base point" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANKWITHOWNCUTLINES, "&Blank with own cutlines" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBLANKWITHOWNCUTLINESONBASEPOINT, "&Blank with own cutlines on base point" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );

	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACENOBLANK, "&NoBlank" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACEBUILDCUTLINES, "Build &Cutlines" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );

		
	AppendMenu( hMenu, MFT_STRING, ID_TREE_SETCOLORFROMCURRENTWELLSSLOJ, "Set Color From Current Wells Sloj" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFASE_PROJECTBLANKLINESONSURFACE, "Project blank lines on surface" );
	
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOSURFACE_REBUILDBYGRIDDATA, "Rebuild by griddata" );
#endif /*!VIEW_ONLY_VERSION*/
}
Archive& operator <<(Archive& ar, std::vector<Poligon3D *>& v)
{
	ar << v.size();

	bool allocated = false;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i])
		{
			allocated = true; 
			ar << allocated;
			ar << (*v[i]);
		}
		else
		{
			allocated = false;
			ar << allocated;
		}
	}
	return ar;
}
Archive& operator >>(Archive& ar, std::vector<Poligon3D *>& v)
{
	size_t len;
	ar >> len;

	v.resize(len);

	bool allocated = false;
	for (size_t i = 0; i < v.size(); i++)
	{
		ar >> allocated;
		if (allocated)
		{
			v[i] = new Poligon3D;
			ar >> (*v[i]);
		}
		else
		{
			v[i] = NULL;
		}
	}
	return ar;
}



DWORD GeoSurface::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
	return 0;
}
Archive& operator <<(Archive& ar, GeoSurface& ob)
{
//printf("Archive& operator <<(Archive& ar, GeoSurface& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 5:
		{
			ar << ob.m_blank_polygon_matrix; ar << ob.m_blank_polygon_matrix_ObjectList;
		}
	case 4:
		{
			ar << ob.id_ige;
		}
	case 3:
		{
			ar << ob.id_umpoz;
			ar << ob.id_surf;
			ar << ob.podoshva;
		}
	case 2:
		{
			ar << ob.m_traces;
			ar << ob.m_vertices;
		}
		// do not break here!!!
	case 1:
		{
			ar << ob.m_surface;
			// Objects' vectors
			ar << ob.m_blank_lines;				ar << ob.m_blank_lines_ObjectList;
			ar << ob.m_izo_lines;				ar << ob.m_izo_lines_ObjectList;
			ar << ob.m_cutFault_lines;			ar << ob.m_cutFault_lines_ObjectList;
			ar << ob.m_cutplane_lines;			ar << ob.m_cutplane_lines_ObjectList;
			ar << ob.m_cutplane_polygones;		ar << ob.m_cutplane_polygones_ObjectList;
			ar << ob.m_blank_polygones;			ar << ob.m_blank_polygones_ObjectList;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, GeoSurface& ob)
{
//printf("Archive& operator >>(Archive& ar, GeoSurface& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 5:
		{
			ar >> ob.m_blank_polygon_matrix; ar >> ob.m_blank_polygon_matrix_ObjectList;
			ob.m_blank_polygon_matrix_ObjectList.Init2_std_vector_std_vector_ptr(
				ob.m_blank_polygon_matrix, &ob);
		}
	case 4:
		{
			ar >> ob.id_ige;
		}
	case 3:
		{
			ar >> ob.id_umpoz;
			ar >> ob.id_surf;
			ar >> ob.podoshva;
		}
	case 2:
		{
			ar >> ob.m_traces;
			ar >> ob.m_vertices;
		}
		// do not break here!!!
	case 1:
		{
			ob.m_object_version = GEOSURFACE_VERSION;

			ar >> ob.m_surface;
			ob.m_surface.SetParent(&ob);
			// Objects' vectors
			ar >> ob.m_blank_lines;				ar >> ob.m_blank_lines_ObjectList;
			ob.m_blank_lines_ObjectList.Init(ob.m_blank_lines, &ob);

			ar >> ob.m_izo_lines;				ar >> ob.m_izo_lines_ObjectList;
			ob.m_izo_lines_ObjectList.Init(ob.m_izo_lines, &ob);

			ar >> ob.m_cutFault_lines;			ar >> ob.m_cutFault_lines_ObjectList;
			ob.m_cutFault_lines_ObjectList.Init(ob.m_cutFault_lines, &ob);

			ar >> ob.m_cutplane_lines;			ar >> ob.m_cutplane_lines_ObjectList;
			ob.m_cutplane_lines_ObjectList.Init(ob.m_cutplane_lines, &ob);

			ar >> ob.m_cutplane_polygones;		ar >> ob.m_cutplane_polygones_ObjectList;
			ob.m_cutplane_polygones_ObjectList.Init(ob.m_cutplane_polygones, &ob);
			if(ob.m_cutplane_polygones.SetCurrentMsgOnFirst())
			{
				do
				{
					ob.m_cutplane_polygones.GetCurrentMsg().Init((Surface3D*)&ob.m_surface);
				}
				while(ob.m_cutplane_polygones.IncrementCurrentMsg());
			}

			ar >> ob.m_blank_polygones;			ar >> ob.m_blank_polygones_ObjectList;
			ob.m_blank_polygones_ObjectList.Init(ob.m_blank_polygones, &ob);
			if(ob.m_blank_polygones.SetCurrentMsgOnFirst())
			{
				do
				{
					ob.m_blank_polygones.GetCurrentMsg().Init((Surface3D*)&ob.m_surface);
				}
				while(ob.m_blank_polygones.IncrementCurrentMsg());
			}


			for (std::vector<std::vector<Poligon3D *> >::iterator it1 = ob.m_blank_polygon_matrix.begin(); 
				it1 != ob.m_blank_polygon_matrix.end(); ++it1)
			{
				for (std::vector<Poligon3D *>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
				{
					if ((*it2))
					{
						(*it2)->Init((Surface3D*)&ob.m_surface);
					}
				}
			}

		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, GeoSurface& ob) end\n");
	return ar;
}
void surface_order_list_item::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << version;

		switch (version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				//ar << ???;
			}
		case 1:
			{
				ar << this->check;

				ar << this->id_surf;
				ar << this->podoshva;

				ar << this->my_name;
				ar << this->check2;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> version;
		switch (version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				//ar >> ???;
			}
		case 1:
			{
				ar >> this->check;

				ar >> this->id_surf;
				ar >> this->podoshva;


				ar >> this->my_name;
				ar >> this->check2;
				this->grid = NULL;

				version = WELLS_DRAW_LIST_ITEM_VERSION;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}


Archive& operator <<(Archive& ar, surface_order_list_item * it)
{
	bool allocated = false;

	if (it)
	{
		allocated = true;
		ar << allocated;
		if (it) it->Serialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, surface_order_list_item *& it)
{
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		it = new surface_order_list_item;
		if (it) it->Serialize(ar);
	}
	else
	{
		it = NULL;
	}
	return ar;
}

void surface_blank_order_list_item::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << version;

		switch (version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				//ar << ???;
			}
		case 1:
			{
				ar << this->check_blank_me;
				ar << this->check_blank_me_up;
				ar << this->check_blank_me_up_above;
				ar << this->check_blank_me_down;
				ar << this->check_blank_me_down_above;
				ar << this->check_blank_by_me_up;
				ar << this->check_blank_by_me_down;

				ar << this->id_surf;
				ar << this->podoshva;
				ar << this->my_name;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> version;
		switch (version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				//ar >> ???;
			}
		case 1:
			{
				ar >> this->check_blank_me;
				ar >> this->check_blank_me_up;
				ar >> this->check_blank_me_up_above;
				ar >> this->check_blank_me_down;
				ar >> this->check_blank_me_down_above;
				ar >> this->check_blank_by_me_up;
				ar >> this->check_blank_by_me_down;

				ar >> this->id_surf;
				ar >> this->podoshva;
				ar >> this->my_name;
				version = WELLS_DRAW_LIST_ITEM_VERSION;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}


Archive& operator <<(Archive& ar, surface_blank_order_list_item * it)
{
	bool allocated = false;

	if (it)
	{
		allocated = true;
		ar << allocated;
		if (it) it->Serialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, surface_blank_order_list_item *& it)
{
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		it = new surface_blank_order_list_item;
		if (it) it->Serialize(ar);
	}
	else
	{
		it = NULL;
	}
	return ar;
}

void surface_blank_functions_list_item::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << version;

		switch (version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				//ar << ???;
			}
		case 1:
			{
				//ar << this->id_item;
				ar << this->id_surf_obj;
				ar << this->id_surf_param;
				ar << this->id_blank_fun;
				ar << name_surf_obj;
				ar << name_surf_param;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> version;
		switch (version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				//ar >> ???;
			}
		case 1:
			{
				//ar >> this->id_item;
				ar >> this->id_surf_obj;
				ar >> this->id_surf_param;
				ar >> this->id_blank_fun;
				ar >> name_surf_obj;
				ar >> name_surf_param;

				version = SURFACE_BLANK_FUNCTIONS_LIST_ITEM_VERSION;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}


Archive& operator <<(Archive& ar, surface_blank_functions_list_item * it)
{
	bool allocated = false;

	if (it)
	{
		allocated = true;
		ar << allocated;
		if (it) it->Serialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, surface_blank_functions_list_item *& it)
{
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		it = new surface_blank_functions_list_item;
		if (it) it->Serialize(ar);
	}
	else
	{
		it = NULL;
	}
	return ar;
}

int GeoSurface::ClearFromDB(bool msg)
{
	int ans = IDYES;
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		bool to_clear = true;
		if (msg)
		{
			ans = MessageBox(0, "Удалить ссылку на поверхность также в списках очерёдности в базе данных?", "GeoSurface::ClearFromDB", MB_YESNOCANCEL);
			to_clear = IDYES == ans;
		}
		if (to_clear)
		{
			long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
			this->m_pSurfDoc->GetLabDoc()->ClearSurfacesOrderItem(id_obj, id_surf);	
			this->m_pSurfDoc->GetLabDoc()->ClearSurfacesBlankOrderItem(id_obj, id_surf);	
			this->m_pSurfDoc->GetLabDoc()->ClearGridDataUsedAlgorothm(id_obj, id_surf);	
		}
	}
	return ans;
}
surface_order_list_item * Find_ID_SURF(long id_surf, vector<surface_order_list_item *> & list);
template <class T> void Clear_ID_SURF_FromOrderList(long id_surf, vector<T *> & list)
{
	T * soli = NULL;
	vector<T *>::iterator it = list.begin();
	for ( ; it != list.end(); it++)
	{
		if ((*it) && (*it)->id_surf == id_surf)
		{
			soli = (*it);
			break;
		}
	}
	if (it != list.end())
	{
		list.erase(it);
		if (soli)
		{
			delete soli;
		}
	}
}
void GeoSurface::ClearFromOrderLists()
{
	Clear_ID_SURF_FromOrderList<surface_order_list_item >(id_surf, GeoSurface::surface_order_list);
	Clear_ID_SURF_FromOrderList<surface_blank_order_list_item >(id_surf, GeoSurface::surface_blank_order_list);
}


void GeoSurface_PrintfProperties(GeoSurface * ob, vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "GeoSurface");
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "id_surf = %d", ob->id_surf);
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "id_umpos = %d", ob->id_umpoz);
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "\"%s\"", ob->GetName().c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	for (size_t ipoint = 0; ipoint < ob->m_surface.GetPointsNumber(); ipoint++)
	{		
		sprintf(str, "%d", ipoint);
		text.push_back(fmtstr(str, NULL, false, true));


		sprintf(str, "%f", ob->m_surface.m_vdPoints[ipoint].x); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		sprintf(str, "%f", ob->m_surface.m_vdPoints[ipoint].y); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		sprintf(str, "%f", ob->m_surface.m_vdPoints[ipoint].z); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));
	}
}

void GeoSurface::PrintfProperties(vector<fmtstr> & text)
{
	GeoSurface_PrintfProperties(this, text);
}


void GeoSurface::PrintfProperties(vector<LabData> & labdata)
{
	labdata.push_back(LabData());
	GeoSurface_PrintfProperties(this, labdata.back().text);
}

