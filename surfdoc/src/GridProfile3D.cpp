// GridProfile3D.cpp: implementation of the GridProfile3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridProfile3D.h"
#include "SurfDoc.h"
#include "winsurftree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GridProfile3D::GridProfile3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

GridProfile3D::GridProfile3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}

void GridProfile3D::OnCreate(void)
{
	//this->m_bIsPrimitive = false;
	this->m_object_type = Object::object_type::grid_profile3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_vdGridProfiles.OnCreate();
	this->m_vvGridProfiles.OnCreate();
	this->m_vGridProfileMapAttaches.OnCreate();
	this->m_vGridProfiles.OnCreate();
}

GridProfile3D::GridProfile3D(const GridProfile3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
GridProfile3D& GridProfile3D::operator=(const GridProfile3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}
GridProfile3D::~GridProfile3D()
{

}
//#if FAST_GRID_LOADING
//int GridProfile3D::AddGridProfile(Grid *pgrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile)
//{
//	return AddGridProfile( pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible, xMap, yMap, xProfile );
//}
//#else
int GridProfile3D::AddGridProfile(CGrid *pCGrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile)
{
	return AddGridProfile( pCGrid->xi, pCGrid->yi, pCGrid->zi, pCGrid->visible, xMap, yMap, xProfile );
}
//#endif /*FAST_GRID_LOADING*/

int GridProfile3D::AddGridProfile(vdouble &x, vdouble &y, vdouble &z, vdouble &visible, vdouble &xMap, vdouble &yMap, vdouble &xProfile)
{
	UINT i;
printf("GridProfile3D::AddGridProfile\n");
	if (x.GetDims() == 1 && y.GetDims() == 1)
	{
		bool use_visible = true;

		if (x.Length() * y.Length() != z.Length())
		{
			MessageBox(0,"x.Length() * y.Length() != z.Length()", 
				"AddGridProfile",0);
			return -1;
		}
		if (visible.Length() != z.Length())
		{
			use_visible = false;
		}

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		if (xMap.Length() != yMap.Length() || xMap.Length() != xProfile.Length() || xMap.Length() != xProfile.Length() )
		{
			char str[255];
			sprintf(str, "xMap.Length(%d) != yMap.Length(%d) != xProfile.Length(%d)", xMap.Length(), yMap.Length(), xProfile.Length());
			MessageBox(0,"x.Length() * y.Length() != z.Length()", 
				"AddGridProfile",0);
			return -1;
		}
		UINT lenMapAttach = xMap.Length();
		ProfileAttachPoint* ptpa;
		ptpa = (ProfileAttachPoint*)HeapAlloc(GetProcessHeap(), 
			HEAP_ZERO_MEMORY, 
			lenMapAttach*sizeof(ProfileAttachPoint));
		for(i = 0; i < lenMapAttach; i++)
		{
			ptpa[i].xMap		= xMap[i];
			ptpa[i].yMap		= yMap[i];
			ptpa[i].xProfile	= xProfile[i];
			ptpa[i].bAttached	= true;
		}
		m_vGridProfileMapAttaches.AddMsg(ptpa, lenMapAttach);
		if(ptpa) HeapFree(GetProcessHeap(), 0, ptpa);
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		UINT len = z.Length(),
			lenx = x.Length(),
			leny = y.Length();

		int vect_count;

		vect_count = m_vGridProfiles.CreateNewVect();

		CPoint3 pt;
		m_GridProfilesXSize = lenx;
		m_GridProfilesYSize = leny;


		CPoint3* pts;
		pts = (CPoint3*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, leny*lenx*sizeof(CPoint3));
		i = 0;
		for(UINT iy = 0; iy < leny; iy++)
		{
			for(UINT ix = 0; ix < lenx; ix++)
			{

				pt.x = (double)x[ix];
				pt.y = (double)y[iy];
				pt.z = (double)z(iy,ix);

				pt.bVisible = use_visible ? (visible(iy,ix) != 0.0 ? true : false) : true;
				pts[i] = pt;
				i++;
			}
		}
		m_vGridProfiles.AddMsgToLastVect(pts, leny*lenx);
		if(pts) HeapFree(GetProcessHeap(), 0, pts);
		return 0;
	}
	if (x.GetDims() == 2 && y.GetDims() == 2)
	{
		bool use_visible = true;

		if (y.Length() != z.Length() || x.Length() != z.Length()
			|| x.GetSize(0) != z.GetSize(0) || y.GetSize(0) != z.GetSize(0)
			|| x.GetSize(1) != z.GetSize(1) || y.GetSize(1) != z.GetSize(1))
		{
			MessageBox(0,"x.GetSize() != y.GetSize() != z.GetSize()", 
				"AddGridProfile",0);
			return -1;
		}
		if (visible.Length() != z.Length())
		{
			use_visible = false;
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		if (xMap.Length() != yMap.Length() || xMap.Length() != xProfile.Length() || xMap.Length() != xProfile.Length() )
		{
			char str[255];
			sprintf(str, "xMap.Length(%d) != yMap.Length(%d) != xProfile.Length(%d)", xMap.Length(), yMap.Length(), xProfile.Length());
			MessageBox(0,"x.Length() * y.Length() != z.Length()", 
				"AddGridProfile",0);
			return -1;
		}
		UINT lenMapAttach = xMap.Length();
		ProfileAttachPoint* ptpa;
		ptpa = (ProfileAttachPoint*)HeapAlloc(GetProcessHeap(), 
			HEAP_ZERO_MEMORY, 
			lenMapAttach*sizeof(ProfileAttachPoint));
		for(UINT i = 0; i < lenMapAttach; i++)
		{
			ptpa[i].xMap		= xMap[i];
			ptpa[i].yMap		= yMap[i];
			ptpa[i].xProfile	= xProfile[i];
			ptpa[i].bAttached	= true;
		}
		m_vGridProfileMapAttaches.AddMsg(ptpa, lenMapAttach);
		if(ptpa) HeapFree(GetProcessHeap(), 0, ptpa);
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


		UINT len = z.Length(),
			lenx = z.GetSize(1),
			leny = z.GetSize(0);


		int vect_count = m_vGridProfiles.CreateNewVect();
		CPoint3 pt;
		m_GridProfilesXSize = lenx;
		m_GridProfilesYSize = leny;

		CPoint3* pts;
		pts = (CPoint3*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, leny*lenx*sizeof(CPoint3));
		i = 0;
		for(UINT iy = 0; iy < leny; iy++)
		{
			for(UINT ix = 0; ix < lenx; ix++)
			{
				pt.x = (double)x(iy,ix);
				pt.y = (double)y(iy,ix);
				pt.z = (double)z(iy,ix);

				pt.bVisible = use_visible ? (visible(iy,ix) != 0.0 ? true : false) : true;
				pts[i] = pt;
				i++;
			}
		}
		m_vGridProfiles.AddMsgToLastVect(pts, leny*lenx);
		if(pts) HeapFree(GetProcessHeap(), 0, pts);
		return 0;
	}
	return -1;
}
extern int __cdecl compareProfileAttachX( const void *arg1, const void *arg2 );
extern void ProfileAttaching(double xProfile, int& ipoint, int lenMapAttach, ProfileAttachPoint *ptpa, double& xMap, double& yMap );

void GridProfile3D::ConvertGridProfilesTo3D()
{
printf("GridProfile3D::ConvertGridProfilesTo3D\n");

	bool start = true;
	double minv, maxv;
	// clear
	m_vvGridProfiles.clear();
	m_vdGridProfiles.clear();
	// профиль из линий блн файлов
//	if( m_vGridProfiles.SetCurrentVectOnFirst() &&
//		m_vGridProfileMapAttaches.SetCurrentMsgOnFirst())
//	{
//		do
//		{
			int lenMapAttach = m_vGridProfileMapAttaches.GetCurrentMsgLen();
			ProfileAttachPoint *ptpa;
			ptpa = m_vGridProfileMapAttaches.GetCurrentMsgPtr();
			// sort on x using Quicksort algorithm:
			qsort( (void *)ptpa, (size_t)lenMapAttach, sizeof(ProfileAttachPoint), compareProfileAttachX );
			// 
			if(	m_vGridProfiles.SetCurrentMsgOnFirst() )
			{
				do
				{
					int len = m_vGridProfiles.GetCurrentMsgLen();
					CPoint3 *pt3;
					pt3 = m_vGridProfiles.GetCurrentMsgPtr();
					CPoint4 *pt4;
					pt4 = (CPoint4*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len*sizeof(CPoint4));
					////////////////////////////////////////
					// номер интервала в массиве привязок профиля к карте
					int ipoint = 0;
					for(int i = 0; i < len; i++)
					{
						// глубину берём без всяких преобразований из блн файла
						pt4[i].z = pt3[i].y;
						pt4[i].v = pt3[i].z;
						pt4[i].bVisible = pt3[i].bVisible;
						double f = pt4[i].v;
						if (start)
						{
							min_grid_profile_v = 
								max_grid_profile_v = f;
							start = false;
						}
						else
						{
							if (min_grid_profile_v > f)
								min_grid_profile_v = f;
							if (max_grid_profile_v < f)
								max_grid_profile_v = f;
						}
						if (i == 0)
						{
							minv = maxv = f;
						}
						else
						{
							if (minv > f)
								minv = f;
							if (maxv < f)
								maxv = f;
						}
						// берём горизонтальную координату профиля из блн файла
						double xProfile = pt3[i].x;
						// преобразовываем эту координату в горизонтальные координаты xMap yMap в системе координат карты 
						ProfileAttaching(xProfile, ipoint, lenMapAttach, ptpa, pt4[i].x, pt4[i].y );
					}
					m_vvGridProfiles.AddMsg(pt4, len);
					m_vdGridProfiles.AddMsg(pt4, len);
					max_grid_profile_v = maxv,
					min_grid_profile_v = minv;

					if(pt4) HeapFree(GetProcessHeap(), 0, pt4);
				}
				while(m_vGridProfiles.IncrementCurrentMsg() );
			}
//		}
//		while(m_vGridProfiles.IncrementCurrentVect() && 
//			m_vGridProfileMapAttaches.IncrementCurrentMsg());
//	}
}

bool GridProfile3D::UpdateExtremums()
{
	bool extremums_not_defined = true;
	double f;
	if (m_vdGridProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = m_vdGridProfiles.GetCurrentMsgLen();
			CPoint4 pt, *ppt;
			ppt = m_vdGridProfiles.GetCurrentMsgPtr();
			for (int ipoint = 0; ipoint < len; ipoint++)
			{							
				pt = ppt[ipoint];
				if (pt.bVisible)
				{
					if (extremums_not_defined)
					{
						extremums_not_defined = false;
						// real x
						f = pt.x;
						m_ptMax.x = f;
						m_ptMin.x = f;
						// real y
						f = pt.y;
						m_ptMax.y = f;
						m_ptMin.y = f;
						// real z
						f = pt.z;
						m_ptMax.z = f;
						m_ptMin.z = f;
					}
					else
					{
						// real x
						f = pt.x;
						if (m_ptMax.x < f) m_ptMax.x = f;
						if (m_ptMin.x > f) m_ptMin.x = f;
						// real y
						f = pt.y;
						if (m_ptMax.y < f) m_ptMax.y = f;
						if (m_ptMin.y > f) m_ptMin.y = f;
						// real z
						f = pt.z;
						if (m_ptMax.z < f) m_ptMax.z = f;
						if (m_ptMin.z > f) m_ptMin.z = f;
					}
				}
			}
		}
		while(m_vdGridProfiles.IncrementCurrentMsg());
	}
	printf("GridProfile3D::UpdateExtremums [%f %f %f %f %f %f]\n ", 
		m_ptMin.x, m_ptMin.y, m_ptMin.z,
		m_ptMax.x, m_ptMax.y, m_ptMax.z 
		);
	return !extremums_not_defined;
}
void GridProfile3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
}
void GridProfile3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
}

void GridProfile3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
/*
	if (this->m_bln_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_polygones.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_bln_polygones.IncrementCurrentMsg());
	}*/
	if (m_vdGridProfiles.SetCurrentMsgOnFirst() 
		&& m_vvGridProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = m_vdGridProfiles.GetCurrentMsgLen();
			CPoint4 *ptv, *ptd;
			ptd = m_vdGridProfiles.GetCurrentMsgPtr();
			ptv = m_vvGridProfiles.GetCurrentMsgPtr();
			for (int ipoint = 0; ipoint < len; ipoint++)
			{							
				ptv[ipoint].bVisible = ptd[ipoint].bVisible;

				ptv[ipoint].z = 
					zoomZ * (ptd[ipoint].z - z_mean);
				ptv[ipoint].y = 
					zoomY * (ptd[ipoint].y - y_mean);
				ptv[ipoint].x = 
					zoomX * (ptd[ipoint].x - x_mean);
			}
		}
		while(m_vdGridProfiles.IncrementCurrentMsg()
			&& m_vvGridProfiles.IncrementCurrentMsg());
	}
}
void GridProfile3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
void GridProfile3D::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
}
HTREEITEM GridProfile3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	UINT	nx = this->m_GridProfilesXSize,
			ny = this->m_GridProfilesYSize;
	// Add the item to the tree-view control
	sprintf(szItemText, "nx = %d ny = %d ", nx, ny);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}

extern bool getNorm(double v1[3], double v2[3], double out[3]);
void GridProfile3D::Draw()
{
	m_nglListNumber = DrawListArray::glNewList();
	Drawing();
	glEndList();
}

void GridProfile3D::ReDraw(void)
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);

	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
		::glNewList(m_nglListNumber, GL_COMPILE);
	}
	else
		m_nglListNumber = DrawListArray::glNewList();

	Drawing();
	glEndList();
}
void GridProfile3D::Drawing()
{
	if (this->m_pSurfDoc)
	{

		bool m_bQuad = true;

		//====== Настройка OpenGL на использование массивов
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		double delta_v;
		if (!m_pSurfDoc->m_bLocalColormap)
		{
			delta_v = 
				m_pSurfDoc->max_grid_profiles_v - m_pSurfDoc->min_grid_profiles_v;
		}
		if (m_vvGridProfiles.SetCurrentMsgOnFirst())
		{


				//====== Установка режима заполнения
				//====== внутренних точек полигонов
	//			glPolygonMode(GL_FRONT_AND_BACK, FillMode);

				//====== Размеры изображаемого объекта
				UINT	nx = m_GridProfilesXSize-1,
						ny = m_GridProfilesYSize-1;

				//====== Захват памяти под динамические массивы
				VERT *Vert = new VERT[(nx+1)*(ny+1)];
				QUAD *Quad = new QUAD[nx*ny];
				int q = 0;


				CPoint4 *ptv;
				ptv = m_vvGridProfiles.GetCurrentMsgPtr();
				double maxv = max_grid_profile_v;
				double minv = min_grid_profile_v;
				if (m_pSurfDoc->m_bLocalColormap)
				{
					delta_v = 
						maxv - minv;
				}
				//====== Цикл прохода по слоям изображения (ось Z)
				for (UINT y=0, i=0;  y<ny;  y++, i++)
				{
					//====== Связанные полигоны начинаются
					//====== на каждой полосе вновь

					//====== Цикл прохода вдоль оси X
					for (UINT x=0;  x<nx;  x++, i++)
					{
						// i, j, k, n - 4 индекса вершин примитива при
						// обходе в направлении против часовой стрелки

						int	j = i + 
							m_GridProfilesXSize,	// Индекс узла с большим Z

							k = j+1,			// Индекс узла по диагонали
							n = i+1; 			// Индекс узла справа

						//=== Выбор координат 4-х вершин из контейнера

						double
							xi = ptv[i].x,
							yi = ptv[i].y,
							zi = ptv[i].z,
							vi = ptv[i].v,

							xj = ptv[j].x,
							yj = ptv[j].y,
							zj = ptv[j].z,
							vj = ptv[j].v,

							xk = ptv[k].x,
							yk = ptv[k].y,
							zk = ptv[k].z,
							vk = ptv[k].v,

							xn = ptv[n].x,
							yn = ptv[n].y,
							zn = ptv[n].z,
							vn = ptv[n].v;

						bool 
							bi = ptv[i].bVisible,
							bj = ptv[j].bVisible,
							bk = ptv[k].bVisible,
							bn = ptv[n].bVisible;


	//fprintf(stream, "i = %d xi = %lf, yi = %lf zi = %lf vi = %lf bi = %d\n", i, xi, yi, zi, vi, int(bi));
	//fprintf(stream, "j = %d xj = %lf, yj = %lf zj = %lf vj = %lf bj = %d\n", j, xj, yj, zj, vj, int(bj));
	//fprintf(stream, "k = %d xk = %lf, yk = %lf zk = %lf vk = %lf bk = %d\n", k, xk, yk, zk, vk, int(bk));
	//fprintf(stream, "n = %d xn = %lf, yn = %lf zn = %lf vn = %lf bn = %d\n\n", n, xn, yn, zn, vn, int(bn));

	//fprintf(stream, "%d%d%d%d\t", int(bi), int(bj), int(bk), int(bn));

						int nb = int(bi) + int(bj) + int(bk) + int(bn);

						// i	n
						//
						// j	k
						double d1[3],d2[3],norm[3];

						//COLORREF surfColor = pSurfDoc->m_vSurfColor.GetCurrentMsg();
						UINT
							color_i,
							color_j,
							color_k,
							color_n;
						int palette_len = m_pSurfDoc->m_palette.GetLen()-1;

						if (m_pSurfDoc->m_bLocalColormap)
						{
							if (m_pSurfDoc->m_bInverseColormap)
							{
								color_i = UINT(0.5+(maxv-vi) / (delta_v) * double(palette_len)); 
								color_j = UINT(0.5+(maxv-vj) / (delta_v) * double(palette_len)); 
								color_k = UINT(0.5+(maxv-vk) / (delta_v) * double(palette_len)); 
								color_n = UINT(0.5+(maxv-vn) / (delta_v) * double(palette_len)); 
							}
							else
							{
								color_i = UINT(0.5+(vi - minv) / (delta_v) * double(palette_len)); 
								color_j = UINT(0.5+(vj - minv) / (delta_v) * double(palette_len)); 
								color_k = UINT(0.5+(vk - minv) / (delta_v) * double(palette_len)); 
								color_n = UINT(0.5+(vn - minv) / (delta_v) * double(palette_len)); 
							}
						}
						else
						{
							if (m_pSurfDoc->m_bInverseColormap)
							{
								color_i = UINT(0.5+(m_pSurfDoc->max_grid_profiles_v-vi) / (delta_v) * double(palette_len)); 
								color_j = UINT(0.5+(m_pSurfDoc->max_grid_profiles_v-vj) / (delta_v) * double(palette_len)); 
								color_k = UINT(0.5+(m_pSurfDoc->max_grid_profiles_v-vk) / (delta_v) * double(palette_len)); 
								color_n = UINT(0.5+(m_pSurfDoc->max_grid_profiles_v-vn) / (delta_v) * double(palette_len)); 
							}
							else
							{
								color_i = UINT(0.5+(vi - m_pSurfDoc->min_grid_profiles_v) / (delta_v) * double(palette_len)); 
								color_j = UINT(0.5+(vj - m_pSurfDoc->min_grid_profiles_v) / (delta_v) * double(palette_len)); 
								color_k = UINT(0.5+(vk - m_pSurfDoc->min_grid_profiles_v) / (delta_v) * double(palette_len)); 
								color_n = UINT(0.5+(vn - m_pSurfDoc->min_grid_profiles_v) / (delta_v) * double(palette_len)); 
							}
						}

							
						if(nb == 4)
						{						
							Vert[i].v = CPoint3(xi,yi,zi);
							Vert[j].v = CPoint3(xj,yj,zj);
							Vert[k].v = CPoint3(xk,yk,zk);
							Vert[n].v = CPoint3(xn,yn,zn);

							if (m_bQuad)
							{
								Quad[q].i1 = i;
								Quad[q].i2 = j;
								Quad[q].i3 = k;
								Quad[q].i4 = n;

							}
							else
							{
								Quad[q].i1 = i;
								Quad[q].i2 = n;
								Quad[q].i3 = j;
								Quad[q].i4 = k;
							}
	#if 0
							Vert[i].c = RGBA (
								BYTE(int(pPaletteValues[ColsP*color_i+0])),
								BYTE(int(pPaletteValues[ColsP*color_i+1])),
								BYTE(int(pPaletteValues[ColsP*color_i+2])),
								(GLubyte)pSurfDoc->m_alpha);
							Vert[j].c = RGBA (
								BYTE(int(pPaletteValues[ColsP*color_j+0])),
								BYTE(int(pPaletteValues[ColsP*color_j+1])),
								BYTE(int(pPaletteValues[ColsP*color_j+2])),
								(GLubyte)pSurfDoc->m_alpha);
							Vert[k].c = RGBA (
								BYTE(int(pPaletteValues[ColsP*color_k+0])),
								BYTE(int(pPaletteValues[ColsP*color_k+1])),
								BYTE(int(pPaletteValues[ColsP*color_k+2])),
								(GLubyte)pSurfDoc->m_alpha);
							Vert[n].c = RGBA (
								BYTE(int(pPaletteValues[ColsP*color_n+0])),
								BYTE(int(pPaletteValues[ColsP*color_n+1])),
								BYTE(int(pPaletteValues[ColsP*color_n+2])),
								(GLubyte)pSurfDoc->m_alpha);
	#else
							Vert[i].c = m_pSurfDoc->m_palette.GetColorWithAlpha(color_i,
								(GLubyte)m_pSurfDoc->m_alpha);
							Vert[j].c = m_pSurfDoc->m_palette.GetColorWithAlpha(color_j,
								(GLubyte)m_pSurfDoc->m_alpha);
							Vert[k].c = m_pSurfDoc->m_palette.GetColorWithAlpha(color_k,
								(GLubyte)m_pSurfDoc->m_alpha);
							Vert[n].c = m_pSurfDoc->m_palette.GetColorWithAlpha(color_n,
								(GLubyte)m_pSurfDoc->m_alpha);
	#endif
							q++;
						}

						//char str[255];
						//sprintf(str,"%d,%d,%d,%d",GetRValue(surfColor),GetGValue(surfColor),GetBValue(surfColor), (GLubyte)pSurfDoc->m_alpha);
						//MessageBox(0,str,"glColor4ub", 0);

						//char str[255];
						//sprintf(str, "color = %d,%d,%d", GetRValue(surfColor),GetGValue(surfColor),GetBValue(surfColor)); 
						//MessageBox(0,str, "", 0);


						// Ветвь создания несвязанных четырехугольников
						if (m_bQuad)
						{

							//====== Обход вершин осуществляется
							//====== в направлении против часовой стрелки
							if(nb == 4)
							{
								d1[0] = xn-xi;
								d1[1] = yn-yi;
								d1[2] = zn-zi;

								d2[0] = xi-xj;
								d2[1] = yi-yj;
								d2[2] = zi-zj;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								Vert[i].n = CPoint3(norm[0],norm[1],norm[2]);


								d1[0] = xi-xj;
								d1[1] = yi-yj;
								d1[2] = zi-zj;

								d2[0] = xj-xk;
								d2[1] = yj-yk;
								d2[2] = zj-zk;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								Vert[j].n = CPoint3(norm[0],norm[1],norm[2]);

								d1[0] = xj-xk;
								d1[1] = yj-yk;
								d1[2] = zj-zk;

								d2[0] = xk-xn;
								d2[1] = yk-yn;
								d2[2] = zk-zn;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								Vert[k].n = CPoint3(norm[0],norm[1],norm[2]);

								d1[0] = xk-xn;
								d1[1] = yk-yn;
								d1[2] = zk-zn;

								d2[0] = xn-xi;
								d2[1] = yn-yi;
								d2[2] = zn-zi;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								Vert[n].n = CPoint3(norm[0],norm[1],norm[2]);
							}

							// i	n
							//
							// j	k
						}
						else /*if (!m_bQuad)*/
						//====== Ветвь создания цепочки четырехугольников
						{
							if (bn && bj)
							{
							}
						}
					}
					//====== Закрываем блок команд GL_QUAD_STRIP
	//fprintf(stream, "\n");
				}
				//====== Закрываем блок команд GL_QUADS

				//====== Задание адресов трех массивов (вершин,
				//====== нормалей и цветов),
				//====== а также шага перемещения по ним
				glVertexPointer(3, GL_PRECISION, sizeof(VERT), &Vert->v);
				glNormalPointer(GL_PRECISION, sizeof(VERT), &Vert->n);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT),
																&Vert->c);
	//WriteRaporto("DrawGridProfiles pre glNewList\n");
				//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
	//WriteRaporto("DrawGridProfiles post glNewList\n");
				//====== Формирование списка рисующих команд
				if (!m_bQuad)
					glDrawElements(GL_QUAD_STRIP, 4*q/*nx*ny*4*/,
										GL_UNSIGNED_INT, Quad);
				else
					glDrawElements(GL_QUADS, 4*q/*nx*ny*4*/,
										GL_UNSIGNED_INT, Quad);
				//glEndList();
				
				//== Освобождение памяти, так как список сформирован
				delete [] Vert;
				delete [] Quad;
		}

	}
}
size_t GridProfile3D::GetPointsNumber()
{
	return 1;
printf("GridProfile3D::GetPointsNumber() %d\n", this->m_vGridProfiles.msgSize());
	return this->m_vGridProfiles.msgSize();// FIX error in the BrokenPlane3D::UpdateExtremums() and remove this line
}

void GridProfile3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "GridProfile3D" , 0);
}

bool GridProfile3D::ColorDialog(void)
{
	return false;
}

COLORREF GridProfile3D::GetColor(void)
{
	return COLORREF();
}

void GridProfile3D::SetColor(COLORREF color)
{
}
DWORD GridProfile3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, GridProfile3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 1:
		{
			ar << ob.m_GridProfilesXSize;
			ar << ob.m_GridProfilesYSize;

			ar << ob.m_vGridProfileMapAttaches;
			ar << ob.m_vGridProfiles;
			ar << ob.m_vvGridProfiles;
			ar << ob.m_vdGridProfiles;

			ar << ob.max_grid_profile_v;
			ar << ob.min_grid_profile_v;

			// Objects' vectors
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
Archive& operator >>(Archive& ar, GridProfile3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_GridProfilesXSize;
			ar >> ob.m_GridProfilesYSize;

			ar >> ob.m_vGridProfileMapAttaches;
			ar >> ob.m_vGridProfiles;
			ar >> ob.m_vvGridProfiles;
			ar >> ob.m_vdGridProfiles;

			ar >> ob.max_grid_profile_v;
			ar >> ob.min_grid_profile_v;

			// Objects' vectors
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

