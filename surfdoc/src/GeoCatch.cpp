#include "StdAfx.h"
#include ".\geocatch.h"
#include "surfdoc.h"
#include "winsurftree.h"

void GetPlaneFrom3Points(CPoint3 p[3], double& A, double& B, double& C, double& D)
{
	//A = (p2.y-p1.y)*(p3.z-p1.z) - (p3.y-p1.y)*(p2.z-p1.z);
	//B = (p2.z-p1.z)*(p3.x-p1.x) - (p3.z-p1.z)*(p2.x-p1.x);
	//C = (p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y);
	A = (p[1].y-p[0].y)*(p[2].z-p[0].z) - (p[2].y-p[0].y)*(p[1].z-p[0].z);
	B = (p[1].z-p[0].z)*(p[2].x-p[0].x) - (p[2].z-p[0].z)*(p[1].x-p[0].x);
	C = (p[1].x-p[0].x)*(p[2].y-p[0].y) - (p[2].x-p[0].x)*(p[1].y-p[0].y);
	D = - A*p[0].x - B*p[0].y - C*p[0].z;
}

GeoCatch::GeoCatch()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

GeoCatch::GeoCatch(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;
//	this->m_surface.Init(pSurfDoc);
//	this->m_blank_line.Init(pSurfDoc);
	OnCreate();
}
void GeoCatch::OnCreate(void)
{
	this->m_object_type = Object::object_type::geo_catch;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
	this->N = 50;

	m_faults.OnCreate();
	m_surfaces.OnCreate();
	m_gorizont_planes.OnCreate();
	m_base_points.OnCreate();
}
GeoCatch::~GeoCatch(void)
{
}

GeoCatch::GeoCatch(const GeoCatch & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
GeoCatch& GeoCatch::operator=(const GeoCatch& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}
bool GeoCatch::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	if(this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			if(m_gorizont_planes.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_gorizont_planes.GetCurrentMsg().GetMax());
				vptmin.push_back(m_gorizont_planes.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void GeoCatch::ZoomViewCutlinesPolygones(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().ZoomViewCutlinesPolygones(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().ZoomViewCutlinesPolygones(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().ZoomViewCutlinesPolygones(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
}
void GeoCatch::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
}
bool GeoCatch::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);

	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_surfaces.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_faults.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_gorizont_planes.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_base_points.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
	return false;
}

void GeoCatch::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}

void GeoCatch::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
}

void GeoCatch::DrawCutPlaneLines()
{
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().DrawCutPlaneLines();
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}	
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().DrawCutPlaneLines();
		}
		while(this->m_faults.IncrementCurrentMsg());
	}	
	if(this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().DrawCutPlaneLines();
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
}

HTREEITEM GeoCatch::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	size_t	
		n_surfs = this->m_surfaces.msgSize(),
		n_faults = this->m_faults.msgSize(),
		n_gorizs = this->m_gorizont_planes.msgSize(),	
		n_points = this->m_base_points.msgSize();	

	sprintf_s(szItemText, 1024, "Geo Catch n_surfs = %d n_faults = %d n_gorizs = %d points = %d", n_surfs, n_faults, n_gorizs, n_points);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	HTREEITEM h3 = AddObjectListItem(hwndTV, "Surfaces", &this->m_surfaces_ObjectList, h2); 
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().AddItem_ToTree(hwndTV,	h3);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	//=============================================================
	//=============================================================
	h3 = AddObjectListItem(hwndTV, "Faults", &this->m_faults_ObjectList, h2); 
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	//=============================================================
	//=============================================================
	h3 = AddObjectListItem(hwndTV, "Gorizont Planes", &this->m_gorizont_planes_ObjectList, h2); 
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	//=============================================================
	//=============================================================
	h3 = AddObjectListItem(hwndTV, "Base points", &this->m_base_points_ObjectList, h2); 
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().AddItem_ToTree(hwndTV, h3, "");
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
	return h2;
}

void GeoCatch::Draw()
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().Draw();
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().Draw();
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().Draw();
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().Draw();
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
}

void GeoCatch::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().ReDraw();
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().ReDraw();
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().ReDraw();
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().ReDraw();
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
}

void GeoCatch::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "GeoCatch" , 0);
}

bool GeoCatch::ColorDialog(void)
{
	return false;
}

COLORREF GeoCatch::GetColor(void)
{
	return COLORREF();
}

void GeoCatch::SetColor(COLORREF color)
{
}

void GeoCatch::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}	
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}

	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}

	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}
}

void GeoCatch::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{

	if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}	

	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}

	if (this->m_base_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_base_points.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_base_points.IncrementCurrentMsg());
	}

}

void GeoCatch::Cut(double a, double b, double c, double d, 
				  bool toDrawPoligones, bool positive, 
				  short type_of_cutline, int cutting_number, 
		CPoint2* pt1, CPoint2* pt2 , void * pBrokenPlane)
{
//printf("GeoCatch::Cut()\n");

		int surf_number = 0;
	/*if (this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			m_surfaces.GetCurrentMsg().m_surface.Cutting(a, b, c, d, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, (void *) &m_surfaces.GetCurrentMsg());

			m_surfaces.GetCurrentMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  (void *) &m_surfaces.GetCurrentMsg(), surf_number );
			surf_number++;
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			m_faults.GetCurrentMsg().m_surface.Cutting(a, b, c, d, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, (void *) &m_faults.GetCurrentMsg());
			m_faults.GetCurrentMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  (void *) &m_faults.GetCurrentMsg(), surf_number );

			surf_number++;
		}
		while(m_faults.IncrementCurrentMsg());
	}*/
//printf("GeoCatch::Cut() pre this->m_gorizont_planes.SetCurrentMsgOnFirst()\n");
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
//printf("GeoCatch::Cut() if this->m_gorizont_planes.SetCurrentMsgOnFirst()\n");
		do
		{
//printf("GeoCatch::Cut() do this->m_gorizont_planes.GetCurrentMsg() type_of_cutline %d, cutting_number %d, surf_number %d\n", type_of_cutline, cutting_number, surf_number);
			this->m_gorizont_planes.GetCurrentMsg().m_surface.Cutting(a, b, c, d, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, 
				&m_gorizont_planes.GetCurrentMsg(), 
				&m_gorizont_planes.GetCurrentMsg().m_blank_polygon_matrix, 
				&m_gorizont_planes.GetCurrentMsg().m_cutplane_polygones_ObjectList,
				&m_gorizont_planes.GetCurrentMsg().m_cutplane_polygones);
			this->m_gorizont_planes.GetCurrentMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  
				m_gorizont_planes.GetCurrentMsg(), surf_number );

			surf_number++;
		}
		while(m_gorizont_planes.IncrementCurrentMsg());
	}
//printf("GeoCatch::Cut() end\n");
}
void GeoCatch::SavingAsRazrez_of_CutPlaneLines(FILE *fd, SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(fd,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(fd,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if(this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(fd,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ);
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
}
bool GeoCatch::SavingAsRazrez_of_CutPlaneLines(dimeModel * model,  dimeBlock * block, SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
	bool status = false;
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( this->m_surfaces.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(model,block,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( this->m_faults.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(model,block,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if(this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			if ( this->m_gorizont_planes.GetCurrentMsg().SavingAsRazrez_of_CutPlaneLines(model,block,sprData,a,b,c,d,minX,minY,minZ,maxX,maxY,maxZ))
				status = true;
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
	return status;
}
void GeoCatch::ClearCutlinesPolygones()
{
	if(this->m_surfaces.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_surfaces.GetCurrentMsg().ClearCutlinesPolygones();
		}
		while(this->m_surfaces.IncrementCurrentMsg());
	}
	if(this->m_faults.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_faults.GetCurrentMsg().ClearCutlinesPolygones();
		}
		while(this->m_faults.IncrementCurrentMsg());
	}
	if(this->m_gorizont_planes.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_gorizont_planes.GetCurrentMsg().ClearCutlinesPolygones();
		}
		while(this->m_gorizont_planes.IncrementCurrentMsg());
	}
}
void GeoCatch::Blank(Line3D& blankline, bool to_continue_line_to_borders, CPoint3 * base_point)
{
	if (this->m_surfaces.SetCurrentMsgOnFirst() && this->m_surfaces_ObjectList.m_bChecked)
	{
		int surf_number = 0;
		do
		{
			if (m_surfaces.GetCurrentMsg().m_bChecked)
			{
				//if(this->m_blanklines.SetCurrentMsgOnFirst())
				//{
				//	do
				//	{
						m_surfaces.GetCurrentMsg().m_surface.Blank(blankline,to_continue_line_to_borders, m_surfaces.GetCurrentMsg(), base_point);
				//	}
				//	while(this->m_blanklines.IncrementCurrentMsg());
				//}				
				surf_number++;
			}
		}
		while(m_surfaces.IncrementCurrentMsg());
	}
	if (this->m_gorizont_planes.SetCurrentMsgOnFirst() && this->m_gorizont_planes_ObjectList.m_bChecked)
	{
		int surf_number = 0;
		do
		{
			if (m_gorizont_planes.GetCurrentMsg().m_bChecked)
			{
				//if(this->m_blanklines.SetCurrentMsgOnFirst())
				//{
				//	do
				//	{
						m_gorizont_planes.GetCurrentMsg().m_surface.Blank(blankline,to_continue_line_to_borders, m_surfaces.GetCurrentMsg(), base_point);
				//	}
				//	while(this->m_blanklines.IncrementCurrentMsg());
				//}				
				surf_number++;
			}
		}
		while(m_gorizont_planes.IncrementCurrentMsg());
	}
	// это вынести в отдельную функцию бланкования разломов
	if (this->m_faults.SetCurrentMsgOnFirst() && this->m_faults_ObjectList.m_bChecked)
	{
		int fault_number = 0;
		do
		{
			if (m_faults.GetCurrentMsg().m_bChecked)
			{
				//if(this->m_blanklines.SetCurrentMsgOnFirst())
				//{
				//	do
				//	{
						Line3D fault_blank_line = blankline;
						for (int i = 0; i < fault_blank_line.GetPointsNumber(); i++)
						{
							fault_blank_line.GetDocumentPoint(i).Convert(m_faults.GetCurrentMsg().m_surface.m_zflag);
						}
						m_faults.GetCurrentMsg().m_surface.Blank(fault_blank_line, false, m_faults.GetCurrentMsg(), NULL);
				//	}
				//	while(this->m_blanklines.IncrementCurrentMsg());
				//}				
				fault_number++;
			}
		}
		while(m_faults.IncrementCurrentMsg());
	}
}
// добавляем горизонтальную плоскость (ГНК, ГВК или НВК) в объект ловушки - на основании базовой точки, принадлежащей поверхности искомого горизонтального контакта
bool GeoCatch::InitGorizontPlane(CPoint3& base_point)
{
	if(this->m_pSurfDoc)
	{
		// Из документа надо взять минимумі и максимумі по горизонтальнім направлениям:
		double minX, minY, minZ;
		double maxX, maxY, maxZ;
		if (this->m_pSurfDoc->GetExtremums_of_Surfaces_and_Faults(
			minX, minY, minZ,
			maxX, maxY, maxZ,
			false))
		{
			// готовим объект для горизонтальной поверхности
			GeoSurface geo_surf(this->m_pSurfDoc);
			this->m_gorizont_planes.AddMsg(&geo_surf);
			ThePoint3D point;
			this->m_base_points.AddMsg(&point);
			this->m_base_points.GetLastMsg().Init(this->m_pSurfDoc, base_point);
			// высоту извлекаем из базовой точки
			double z_level = base_point.z;
			// готовим равномерную сетку
			vdouble x = dsequence(minX,this->N,maxX);
			vdouble y = dsequence(minY,this->N,maxY);

			vdouble xx;
			vdouble yy;
			vdouble zz;
 			vdouble visible;

			meshgrid(x,y,xx,yy);
			//инициализируем горизонтальную координату сетки
			zz.resize(xx.GetSize(0), yy.GetSize(0),  z_level);
			//zz.Rand(z_level-1, z_level+1);

 			visible.resize(y.Length(), x.Length(), 1.0);

			// инициализируем горизонтальную плоскость и добавляем её в массив горизонтальных плоскостей

			COLORREF color = RGB(0,0,255);
			this->m_gorizont_planes.GetLastMsg().m_surface.Init(0,xx,yy,zz,visible,color);
			this->m_gorizont_planes_ObjectList.Init(this->m_gorizont_planes, this);
#if 1
			// теперь мы получили геоповерхность в виде горизонтальной плоскости
			// ищем теперь линии пересечения этой плоской геоповерхности со всеми
			// объектами Surfaces_and_Faults из документа
			// результаты складываем сюда:
			// this->m_gorizont_planes.GetLastMsg().m_blank_lines;
			short type_of_cutline = 6;
			int surf_number = 0;
			if(this->m_pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
			{
				int cutting_number = 0;
				do
				{
					this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.Cutting(
						0.0,0.0,1.0,-z_level, 
						false, true, 
						type_of_cutline, cutting_number, surf_number, 
						NULL,NULL, (void*) NULL, 
						&this->m_pSurfDoc->m_surfaces.GetCurrentMsg(),
						&this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_blank_polygon_matrix,
						&this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_cutplane_polygones_ObjectList,
						&this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_cutplane_polygones);
					
					this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.CutLine( 
						type_of_cutline, cutting_number, (void *) NULL, 
						m_gorizont_planes.GetCurrentMsg(), surf_number );

					surf_number++;
				}
				while(this->m_pSurfDoc->m_surfaces.IncrementCurrentMsg());
			}
			if(this->m_pSurfDoc->m_faults.SetCurrentMsgOnFirst())
			{
				int cutting_number = 0;
				do
				{
					this->m_pSurfDoc->m_faults.GetCurrentMsg().m_surface.Cutting(
						0.0,0.0,1.0,-z_level, 
						false, true, 
						type_of_cutline, cutting_number, surf_number, 
						NULL,NULL, (void*) NULL, 
						&this->m_pSurfDoc->m_faults.GetCurrentMsg(),
						&this->m_pSurfDoc->m_faults.GetCurrentMsg().m_blank_polygon_matrix,
						&this->m_pSurfDoc->m_faults.GetCurrentMsg().m_cutplane_polygones_ObjectList,
						&this->m_pSurfDoc->m_faults.GetCurrentMsg().m_cutplane_polygones);
					
					this->m_pSurfDoc->m_faults.GetCurrentMsg().m_surface.CutLine( 
						type_of_cutline, cutting_number, (void *) NULL,
						m_gorizont_planes.GetCurrentMsg(), surf_number );

					surf_number++;

				}
				while(this->m_pSurfDoc->m_faults.IncrementCurrentMsg());
			}
							
			this->m_gorizont_planes.GetLastMsg().m_surface.CutLine(type_of_cutline, 0, (void *) NULL, 
				this->m_gorizont_planes.GetCurrentMsg(), surf_number );
#else
			// теперь мы получили геоповерхность в виде горизонтальной плоскости
			// ищем теперь линии пересечения этой плоской геоповерхности со всеми
			// объектами Surfaces_and_Faults из документа
			// результаты складываем сюда:
			// this->m_gorizont_planes.GetLastMsg().m_blank_lines;
			short type_of_cutline = 6;
			int surf_number = 0;
			if(this->m_pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
			{
				int cutting_number = 0;
				do
				{
					if(this->m_gorizont_planes.GetLastMsg().m_surface.Cutting(
						&this->m_pSurfDoc->m_surfaces.GetCurrentMsg().m_surface,
						type_of_cutline,
						cutting_number,
						surf_number))
					{
						// если горизонтальная плоскость и 
						// this->m_pSurfDoc->m_surfaces.GetCurrentMsg()
						// пересекаются в пространстве
						// копируем this->m_pSurfDoc->m_surfaces.GetCurrentMsg()
						// в ловушку
						// this->m_surfaces.AddMsg(&this->m_pSurfDoc->m_surfaces.GetCurrentMsg());

					}
					cutting_number++;
				}
				while(this->m_pSurfDoc->m_surfaces.IncrementCurrentMsg());
			}
			if(this->m_pSurfDoc->m_faults.SetCurrentMsgOnFirst())
			{
				int cutting_number = 0;
				do
				{
					if(this->m_gorizont_planes.GetLastMsg().m_surface.Cutting(
						&this->m_pSurfDoc->m_faults.GetCurrentMsg().m_surface,
						type_of_cutline,
						cutting_number,
						surf_number))
					{
						// если горизонтальная плоскость и 
						// this->m_pSurfDoc->m_faults.GetCurrentMsg()
						// пересекаются в пространстве
						// копируем this->m_pSurfDoc->m_faults.GetCurrentMsg()
						// в ловушку
						// this->m_faults.AddMsg(&this->m_pSurfDoc->m_faults.GetCurrentMsg());

					}
					cutting_number++;
				}
				while(this->m_pSurfDoc->m_faults.IncrementCurrentMsg());
			}
							
			this->m_gorizont_planes.GetLastMsg().m_surface.CutLine(type_of_cutline, 0, (void *) NULL, 
				(void*)&this->m_gorizont_planes.GetCurrentMsg(), surf_number );
#endif
			return true;
		}
		else
			MessageBox(0, "Extremums not found", "InitGorizontPlane", MB_OK);
	}
	return false;
}
void GeoCatch::BlankingOfGorizontPlaneBlankLines(void)
{
	if (this->m_gorizont_planes.SetCurrentMsgOnLast() 
		&& this->m_base_points.SetCurrentMsgOnLast())
	{
		CPoint3 ptMax, ptMin;
		this->m_gorizont_planes.GetCurrentMsg().BlankingOfBlankLines(
			&this->m_base_points.GetCurrentMsg().GetFirstDocumentPoint(), ptMax, ptMin);

			// высоту извлекаем из базовой точки
			double z_level =this->m_base_points.GetCurrentMsg().GetFirstDocumentPoint().z;
			// готовим равномерную сетку
			vdouble x = dsequence(ptMin.x,this->N,ptMax.x);
			vdouble y = dsequence(ptMin.y,this->N,ptMax.y);

			vdouble xx;
			vdouble yy;
			vdouble zz;
 			vdouble visible;

			meshgrid(x,y,xx,yy);
			//инициализируем горизонтальную координату сетки
			zz.resize(xx.GetSize(0), yy.GetSize(0),  z_level);
			//zz.Rand(z_level-1, z_level+1);

 			visible.resize(y.Length(), x.Length(), 1.0);

			// инициализируем горизонтальную плоскость и добавляем её в массив горизонтальных плоскостей

			COLORREF color = RGB(0,0,255);
			this->m_gorizont_planes.GetCurrentMsg().m_surface.Init(0,xx,yy,zz,visible,color);
			this->m_gorizont_planes_ObjectList.Init(this->m_gorizont_planes, this);	
	}
}
bool GeoCatch::BlankLastGorizontPlane(void)
{
	// теперь проводим бланкование нашей горизонтальной плоскости исходя из 
	// полученного массива линий сечения 
	// и опираясь на базовую точку

	if (this->m_gorizont_planes.SetCurrentMsgOnLast() 
		&& this->m_base_points.SetCurrentMsgOnLast())
	{
		this->m_gorizont_planes.GetCurrentMsg().BlankWithOwnBlankLines(
			true, true, &this->m_base_points.GetCurrentMsg().GetFirstDocumentPoint());
		return true;
	}
	return false;
}
DWORD GeoCatch::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, GeoCatch& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 1:
		{
			ar << ob.m_surfaces;			ar << ob.m_surfaces_ObjectList;

			ar << ob.m_faults;				ar << ob.m_faults_ObjectList;

			ar << ob.m_gorizont_planes;		ar << ob.m_gorizont_planes_ObjectList;

			ar << ob.m_base_points;			ar << ob.m_base_points_ObjectList;

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
Archive& operator >>(Archive& ar, GeoCatch& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_surfaces;				ar >> ob.m_surfaces_ObjectList;
			ob.m_surfaces_ObjectList.Init(ob.m_surfaces, &ob);

			ar >> ob.m_faults;					ar >> ob.m_faults_ObjectList;
			ob.m_faults_ObjectList.Init(ob.m_faults, &ob);

			ar >> ob.m_gorizont_planes;			ar >> ob.m_gorizont_planes_ObjectList;
			ob.m_gorizont_planes_ObjectList.Init(ob.m_gorizont_planes, &ob);
						
			ar >> ob.m_base_points;				ar >> ob.m_base_points_ObjectList;
			ob.m_base_points_ObjectList.Init(ob.m_base_points, &ob);
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
	return ar;
}





