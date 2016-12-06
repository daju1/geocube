// Surface3D.cpp: implementation of the Surface3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SurfDoc.h"
//#include "raporto.h"
#include "DrawScene.h"
#include "colormap.h"
#include "DrawScene.h"
#include "..\..\winplot\src\winplot.h"
#include "distance3d.h"
#include ".\surface3d.h"
//#include "errorexit.h"

#include <vector>
#include <algorithm>
#include <functional>      // For greater<int>( )

#include "logger/Logger.h"

extern bool getNorm(double v1[3], double v2[3], double out[3]);
//Surface3D * Surface3D::me = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HINSTANCE hInst;   // текущий экземпляр
Surface3D::draw_mode Surface3D::s_draw_mode = Surface3D::as_quads;
surf_edge::edge_cutting::sort_mode surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;

size_t Surface3D::s_N_quad = 4;
bool Surface3D::s_do_not_build_blank_polygones_on_continue_lines = true;

Surface3D::Surface3D()
{
	Init();
	OnCreate();
}

Surface3D::Surface3D(SurfDoc * pSurfDoc)
{
	Init();
	m_pSurfDoc			= pSurfDoc;
	OnCreate();
}
void Surface3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::surface3d;
	this->m_object_version = 2;
	this->m_max_object_version = 2;
}
void Surface3D::Init()
{
//	this->m_izolines.OnCreate();
	m_nColormap			= 0;
	m_bInverseColormap	= false;
	m_bLocalColormap	= true;
	m_bUseColormap		= true;

	m_pSurfDoc = NULL;
 	m_bQuad = true;
	
	vQuadCutting.OnCreate(0);
	vxyz.OnCreate(0);

	APalette::InitPalette(&this->m_palette, this->m_nColormap);
}
bool Surface3D::IsTheSameSize(CubeSize & cube_size)
{
	if (cube_size.Defined())
	{
		if (this->GetPointsNumber())
		{
			double epsilon = 1e-2;

			SURFER7GRIDSECTION gridSection;

			gridSection.nRow = m_leny;
			gridSection.nCol = m_lenx;

			gridSection.xLL = this->GetDocumentPoint(0).x;
			gridSection.yLL = this->GetDocumentPoint(0).y;

			gridSection.xSize  = this->GetDocumentPoint(1).x - this->GetDocumentPoint(0).x;
			gridSection.ySize  = this->GetDocumentPoint(m_lenx).y - this->GetDocumentPoint(0).y;

			gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
			gridSection.Rotation = 0.0;// not currently used;

			bool ans = false;
			switch(this->m_zflag)
			{
			case 3:
			case 0:
				{
					ans =
						gridSection.nRow		== cube_size.nRow  && // number of rows in the grid       (Ny)
						gridSection.nCol		== cube_size.nCol  && // number of columns in the grid    (Nx)
						fabs (gridSection.xLL - cube_size.xLL) < epsilon   && // X coordinate of the lower left corner of the grid
						fabs (gridSection.yLL - cube_size.yLL) < epsilon   && // Y coordinate of the lower left corner of the grid
						fabs (gridSection.xSize - cube_size.xSize) < epsilon && // spacing between adjacent nodes in the X direction (between columns)
						fabs (gridSection.ySize	- cube_size.ySize) < epsilon; // spacing between adjacent nodes in the Y direction (between rows)
				}
				break;
			case 1: // x - z
				{
					ans =
						gridSection.nRow		== cube_size.nRow  && // number of rows in the grid       (Ny)
						gridSection.nCol		== cube_size.nPag  && // number of columns in the grid    (Nx)
						fabs (gridSection.xLL - cube_size.zLL) < epsilon   && // X coordinate of the lower left corner of the grid
						fabs (gridSection.yLL - cube_size.yLL) < epsilon   && // Y coordinate of the lower left corner of the grid
						fabs (gridSection.xSize - cube_size.zSize) < epsilon && // spacing between adjacent nodes in the X direction (between columns)
						fabs (gridSection.ySize	- cube_size.ySize) < epsilon; // spacing between adjacent nodes in the Y direction (between rows)
				}
				break;
			case 2: // y - z
				{
					ans =
						gridSection.nRow		== cube_size.nPag  && // number of rows in the grid       (Ny)
						gridSection.nCol		== cube_size.nCol  && // number of columns in the grid    (Nx)
						fabs (gridSection.xLL - cube_size.xLL) < epsilon   && // X coordinate of the lower left corner of the grid
						fabs (gridSection.yLL - cube_size.zLL) < epsilon   && // Y coordinate of the lower left corner of the grid
						fabs (gridSection.xSize - cube_size.xSize) < epsilon && // spacing between adjacent nodes in the X direction (between columns)
						fabs (gridSection.ySize	- cube_size.zSize) < epsilon; // spacing between adjacent nodes in the Y direction (between rows)
				}
				break;
			}


			/*if (!ans)
			{
				1;
			}*/
			return ans;

		}
	}
	return false;
}
bool Surface3D::MakeGridSection(LPSURFER7GRIDSECTION gridSection, bool to_allocate)
{
	size_t i;
	if (this->GetPointsNumber())
	{
		if (to_allocate)
		{
			gridSection->nRow = m_leny;
			gridSection->nCol = m_lenx;

			gridSection->xLL = this->GetDocumentPoint(0).x;
			gridSection->yLL = this->GetDocumentPoint(0).y;

			gridSection->xSize  = this->GetDocumentPoint(1).x - this->GetDocumentPoint(0).x;
			gridSection->ySize  = this->GetDocumentPoint(m_lenx).y - this->GetDocumentPoint(0).y;

			gridSection->BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
			gridSection->Rotation = 0.0;// not currently used;
		}

		bool start = true;
		for(i = 0; i < this->GetPointsNumber(); i++)
		{
			if (start)
			{
				gridSection->zMin = this->GetDocumentPoint(i).z;
				gridSection->zMax = this->GetDocumentPoint(i).z;
				start = false;
			}
			else
			{
				if(gridSection->zMin > this->GetDocumentPoint(i).z) gridSection->zMin = this->GetDocumentPoint(i).z;
				if(gridSection->zMax < this->GetDocumentPoint(i).z) gridSection->zMax = this->GetDocumentPoint(i).z;
			}
		}

		if (to_allocate)
			gridSection->z = AllocDoubleMat(gridSection->nRow, gridSection->nCol);

		i = 0;
		//for (long r = 0; r < pGrid->gridSection.nRow; r++)
		for(UINT r = 0; r < m_leny; r++)
		{
			//for (long c = 0; c < pGrid->gridSection.nCol; c++)
			for(UINT c = 0; c < m_lenx; c++)
			{
				if (!this->GetDocumentPoint(i).bVisible)
				{
					gridSection->z[r][c] = gridSection->BlankValue;
				}
				else
				{
					gridSection->z[r][c] = this->GetDocumentPoint(i).z;
				}
				i++;
			}
		}
		return true;
	}
	return false;

}

void Surface3D::Init(short zflag, LPSURFER7GRIDSECTION gridSection, COLORREF color)
{		
	m_zflag = zflag;
	m_leny = gridSection->nRow;
	m_lenx = gridSection->nCol;

	m_color = color;

	Free();
	AllocPoints(m_leny*m_lenx);

	UINT i = 0;
	//for (long r = 0; r < pGrid->gridSection.nRow; r++)
	for(UINT r = 0; r < m_leny; r++)
	{
		//for (long c = 0; c < pGrid->gridSection.nCol; c++)
		for(UINT c = 0; c < m_lenx; c++)
		{
			CPoint3 pt;
			pt.bVisible = true;

			pt.x = gridSection->xLL + c * gridSection->xSize;
			pt.y = gridSection->yLL + r * gridSection->ySize;
			pt.z = gridSection->z[r][c];
			if (gridSection->z[r][c] == gridSection->BlankValue)
			{
				pt.bVisible = false;
				// on blanked bit
				pt.flag |= CPOINT3_FLAG_BLANKED;
			}
			if (gridSection->z[r][c] > gridSection->zMax)
			{
				pt.bVisible = false;
				pt.z = gridSection->zMin;
			}
			m_vvPoints[i] = pt;
			m_vdPoints[i] = pt;
			i++;
		}
	}
	/*this->UpdateExtremums();	*/
}
void Surface3D::Init(int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible, COLORREF color )
{
printf("Surface3D::Init\n");
	if (x.GetDims() == 1 && y.GetDims() == 1)
	{
		bool use_visible = true;

		if (x.Length() * y.Length() != z.Length())
		{
			MessageBox(0,"x.Length() * y.Length() != z.Length()", "AddSurf",0);
			return;
		}
		if (visible.Length() != z.Length())
		{
			use_visible = false;
		}

		UINT len = z.Length(),
			lenx = x.Length(),
			leny = y.Length();

		CPoint3 pt;
		m_lenx = lenx;
		m_leny = leny;
		m_color = color;

		m_zflag = zflag;

		m_ptMax.x = x.Max();
		m_ptMax.y = y.Max();
		m_ptMax.z = z.Max();

		m_ptMin.x = x.Min();
		m_ptMin.y = y.Min();
		m_ptMin.z = z.Min();

		Free();
		AllocPoints(leny*lenx);

		int i = 0;
		for(UINT iy = 0; iy < leny; iy++)
		{
			for(UINT ix = 0; ix < lenx; ix++)
			{

				pt.x = (double)x[ix];
				pt.y = (double)y[iy];
				pt.z = (double)z(iy,ix);

				pt.bVisible = use_visible ? (visible(iy,ix) != 0.0 ? true : false) : true;

				m_vvPoints[i] = pt;
				m_vdPoints[i] = pt;
				i++;
			}
		}
	}
	if (x.GetDims() == 2 && y.GetDims() == 2)
	{
		bool use_visible = true;

		if (y.Length() != z.Length() || x.Length() != z.Length()
			|| x.GetSize(0) != z.GetSize(0) || y.GetSize(0) != z.GetSize(0)
			|| x.GetSize(1) != z.GetSize(1) || y.GetSize(1) != z.GetSize(1))
		{
			MessageBox(0,"x.GetSize() != y.GetSize() != z.GetSize()", "AddSurf",0);
			return;
		}
		if (visible.Length() != z.Length())
		{
			use_visible = false;
		}


		UINT len = z.Length(),
			lenx = z.GetSize(1),
			leny = z.GetSize(0);


		CPoint3 pt;
		m_lenx = lenx;
		m_leny = leny;
		m_color = color;

		m_zflag = zflag;

		m_ptMax.x = x.Max();
		m_ptMax.y = y.Max();
		m_ptMax.z = z.Max();

		m_ptMin.x = x.Min();
		m_ptMin.y = y.Min();
		m_ptMin.z = z.Min();


		Free();
		AllocPoints(leny*lenx);

		int i = 0;
		for(UINT iy = 0; iy < leny; iy++)
		{
			for(UINT ix = 0; ix < lenx; ix++)
			{

				pt.x = (double)x(iy,ix);
				pt.y = (double)y(iy,ix);
				pt.z = (double)z(iy,ix);

				pt.bVisible = use_visible ? (visible(iy,ix) != 0.0 ? true : false) : true;
				m_vvPoints[i] = pt;
				m_vdPoints[i] = pt;
				i++;
			}
		}

	}
printf("Surface3D::Init end\n");
}

BOOL Surface3D::GetPoint(int iy,int ix, CPoint3 *pt)
{
	int i = iy * m_lenx + ix;
	if(i < GetPointsNumber())
	{
		*pt = m_vdPoints[i];
		return TRUE;
	}
	else
		return FALSE;

}
Surface3D::~Surface3D()
{
//	MessageBox(0,"~Surface3D()","",0);
}

HTREEITEM Surface3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
	char szItemText[1024]; // label text of tree-view item 
	sprintf(szItemText, "zflag = %d nx = %d ny = %d color = %u %u %u ", m_zflag, m_lenx, m_leny
		, GetRValue(m_color)
		, GetGValue(m_color)
		, GetBValue(m_color)
	);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}

void Surface3D::Drawing()
{
	bool razlomy_as_one_surface = true;
	if (m_pSurfDoc)
	{
		double mean_norm[3];
		mean_norm[0] = 0;
		mean_norm[1] = 0;
		mean_norm[2] = 0;
		for(int nsurf = 0; nsurf <= (razlomy_as_one_surface || m_zflag == 0 ? 0 : 2); nsurf++)
		{
			if (nsurf == 1)
			{
				Scale(mean_norm);
				mean_norm[0]*=m_pSurfDoc->m_razlomThickness*m_pSurfDoc->m_zoomXY;
				mean_norm[1]*=m_pSurfDoc->m_razlomThickness*m_pSurfDoc->m_zoomXY;
				mean_norm[2]*=m_pSurfDoc->m_razlomThickness*m_pSurfDoc->m_zoomXY;
			}
			/// drawing of contour triangles
	//		m_pSurfDoc->m_DrawListArray.glNewList();

			if (m_lenx > 0 && m_leny > 0)
			{


				//====== Размеры изображаемого объекта
				UINT	nx = m_lenx-1,
						ny = m_leny-1;

		#ifdef TEST_CONTUR
				vdouble points;
				points.resize(nx+1, ny+1, 0.0);
		#endif
				double d1[3],d2[3],norm[3];
				//====== Захват памяти под динамические массивы
				VERT *Vert = new VERT[(nx+1)*(ny+1)];
				QUAD *Quad = new QUAD[nx*ny];
	/*			if (m_pSurfDoc->m_bEnableDither)
				{
					for (UINT y=0, i=0;  y<=ny;  y++)
					{
						//====== Цикл прохода вдоль оси X
						for (UINT x=0;  x<=nx;  x++, i++)
						{
							Vert[i].n = CPoint3(0.,0.,0.);
						}
					}
				}*/
				int q = 0;

				/// drawing of contour triangles
				//  glBegin (GL_TRIANGLES);

				PRIMITIVE_POINTS_PTR(CPoint3) ptv;
				PRIMITIVE_POINTS_PTR(CPoint3) ptd;

				ptv = m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
				ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;


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
							nx + 1,	// Индекс узла с большим Z

							k = j+1,			// Индекс узла по диагонали
							n = i+1; 			// Индекс узла справа

						//=== Выбор координат 4-х вершин из контейнера
						double
							xi = ptv[i].x,
							yi = ptv[i].y,
							zi = ptv[i].z,

							xj = ptv[j].x,
							yj = ptv[j].y,
							zj = ptv[j].z,

							xk = ptv[k].x,
							yk = ptv[k].y,
							zk = ptv[k].z,

							xn = ptv[n].x,
							yn = ptv[n].y,
							zn = ptv[n].z;

						bool 
							bi = ptv[i].bVisible,
							bj = ptv[j].bVisible,
							bk = ptv[k].bVisible,
							bn = ptv[n].bVisible;

						if(nsurf == 1)
						{
							xi += mean_norm[0];
							yi += mean_norm[1];
							zi += mean_norm[2];

							xj += mean_norm[0];
							yj += mean_norm[1];
							zj += mean_norm[2];

							xk += mean_norm[0];
							yk += mean_norm[1];
							zk += mean_norm[2];

							xn += mean_norm[0];
							yn += mean_norm[1];
							zn += mean_norm[2];
						}
						if(nsurf == 2)
						{
							xi -= mean_norm[0];
							yi -= mean_norm[1];
							zi -= mean_norm[2];

							xj -= mean_norm[0];
							yj -= mean_norm[1];
							zj -= mean_norm[2];

							xk -= mean_norm[0];
							yk -= mean_norm[1];
							zk -= mean_norm[2];

							xn -= mean_norm[0];
							yn -= mean_norm[1];
							zn -= mean_norm[2];
						}

		//fprintf(stream, "i = %d xi = %lf, yi = %lf zi = %lf bi = %d\n", i, xi, yi, zi, int(bi));
		//fprintf(stream, "j = %d xj = %lf, yj = %lf zj = %lf bj = %d\n", j, xj, yj, zj, int(bj));
		//fprintf(stream, "k = %d xk = %lf, yk = %lf zk = %lf bk = %d\n", k, xk, yk, zk, int(bk));
		//fprintf(stream, "n = %d xn = %lf, yn = %lf zn = %lf bn = %d\n\n", n, xn, yn, zn, int(bn));
		//fprintf(stream, "%d%d%d%d\t", int(bi), int(bj), int(bk), int(bn));

						int nb = int(bi) + int(bj) + int(bk) + int(bn);
						// i	n
						//
						// j	k
						
						double
							zdi = ptd[i].z,
							zdj = ptd[j].z,
							zdk = ptd[k].z,
							zdn = ptd[n].z;
							
						if(nb == 4)
						{						
							//glColor3f (0.2f, 0.8f, 1.f);
							if (m_zflag == 0)
							{
								// (xi, yi, zi);
								Vert[i].v = CPoint3(xi,yi,zi);
								Vert[j].v = CPoint3(xj,yj,zj);
								Vert[k].v = CPoint3(xk,yk,zk);
								Vert[n].v = CPoint3(xn,yn,zn);
							}
							if (m_zflag == 1)
							{
								// (zi, yi, xi);
								Vert[i].v = CPoint3(zi,yi,xi);
								Vert[j].v = CPoint3(zj,yj,xj);
								Vert[k].v = CPoint3(zk,yk,xk);
								Vert[n].v = CPoint3(zn,yn,xn);
							}
							if (m_zflag == 2)
							{
								// (xi, zi, yi);
								Vert[i].v = CPoint3(xi,zi,yi);
								Vert[j].v = CPoint3(xj,zj,yj);
								Vert[k].v = CPoint3(xk,zk,yk);
								Vert[n].v = CPoint3(xn,zn,yn);
							}

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

							// i	n
							//
							// j	k

							Vert[i].c = this->GetColor(zdi);
							Vert[j].c = this->GetColor(zdj);
							Vert[k].c = this->GetColor(zdk);
							Vert[n].c = this->GetColor(zdn);


							q++;
						}
		#if DISVISIBLE_AS_ALPHA
						else if (true)
						{						
							//glColor3f (0.2f, 0.8f, 1.f);
							if (m_zflag == 0)
							{
								// (xi, yi, zi);
								Vert[i].v = CPoint3(xi,yi,zi);
								Vert[j].v = CPoint3(xj,yj,zj);
								Vert[k].v = CPoint3(xk,yk,zk);
								Vert[n].v = CPoint3(xn,yn,zn);
							}
							if (m_zflag == 1)
							{
								// (zi, yi, xi);
								Vert[i].v = CPoint3(zi,yi,xi);
								Vert[j].v = CPoint3(zj,yj,xj);
								Vert[k].v = CPoint3(zk,yk,xk);
								Vert[n].v = CPoint3(zn,yn,xn);
							}
							if (m_zflag == 2)
							{
								// (xi, zi, yi);
								Vert[i].v = CPoint3(xi,zi,yi);
								Vert[j].v = CPoint3(xj,zj,yj);
								Vert[k].v = CPoint3(xk,zk,yk);
								Vert[n].v = CPoint3(xn,zn,yn);
							}

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

							// i	n
							//
							// j	k
							BYTE aInvisible = DISVISIBLE_ALPHA;

							if (bi) Vert[i].c = this->GetColor(zdi);
							else	Vert[i].c = RGBA(255,255,255,aInvisible);
							if (bj) Vert[j].c = this->GetColor(zdj);
							else	Vert[j].c = RGBA(255,255,255,aInvisible);
							if (bk) Vert[k].c = this->GetColor(zdk);
							else	Vert[k].c = RGBA(255,255,255,aInvisible);
							if (bn) Vert[n].c = this->GetColor(zdn);
							else	Vert[n].c = RGBA(255,255,255,aInvisible);					

							q++;
						}
		#endif

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

								if (m_zflag == 0)
								{
	/*								if (m_pSurfDoc->m_bEnableDither)
										Vert[i].n += CPoint3(norm[0],norm[1],norm[2]);
									else*/
										Vert[i].n = CPoint3(norm[0],norm[1],norm[2]);
								}
								if (m_zflag == 1)
									Vert[i].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[i].n = CPoint3(norm[2],norm[1],norm[0]);
		#ifdef TEST_CONTUR
								if (m_zflag == 0)
									points(x,y) = points(x,y) + 1.0;
		#endif
								if (nsurf == 0 && m_zflag != 0)
								{
									mean_norm[0] += norm[0];
									mean_norm[1] += norm[1];
									mean_norm[2] += norm[2];
								}

								d1[0] = xi-xj;
								d1[1] = yi-yj;
								d1[2] = zi-zj;

								d2[0] = xj-xk;
								d2[1] = yj-yk;
								d2[2] = zj-zk;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали

								if (m_zflag == 0)
								{
									/*if (m_pSurfDoc->m_bEnableDither)
										Vert[j].n += CPoint3(norm[0],norm[1],norm[2]);
									else*/
										Vert[j].n = CPoint3(norm[0],norm[1],norm[2]);
								}
								if (m_zflag == 1)
									Vert[j].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[j].n = CPoint3(norm[2],norm[1],norm[0]);
		#ifdef TEST_CONTUR
								if (m_zflag == 0)
									points(x+1,y) = points(x+1,y) + 1.0;
		#endif


								if (nsurf == 0 && m_zflag != 0)
								{
									mean_norm[0] += norm[0];
									mean_norm[1] += norm[1];
									mean_norm[2] += norm[2];
								}

								d1[0] = xj-xk;
								d1[1] = yj-yk;
								d1[2] = zj-zk;

								d2[0] = xk-xn;
								d2[1] = yk-yn;
								d2[2] = zk-zn;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали

								if (m_zflag == 0)
								{
									/*if (m_pSurfDoc->m_bEnableDither)
										Vert[k].n += CPoint3(norm[0],norm[1],norm[2]);
									else*/
										Vert[k].n = CPoint3(norm[0],norm[1],norm[2]);
								}
								if (m_zflag == 1)
									Vert[k].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[k].n = CPoint3(norm[2],norm[1],norm[0]);
		#ifdef TEST_CONTUR
								if (m_zflag == 0)
									points(x+1,y+1) = points(x+1,y+1) + 1.0;
		#endif
								if (nsurf == 0 && m_zflag != 0)
								{
									mean_norm[0] += norm[0];
									mean_norm[1] += norm[1];
									mean_norm[2] += norm[2];
								}

								d1[0] = xk-xn;
								d1[1] = yk-yn;
								d1[2] = zk-zn;

								d2[0] = xn-xi;
								d2[1] = yn-yi;
								d2[2] = zn-zi;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали

								if (m_zflag == 0)
								{
									/*if (m_pSurfDoc->m_bEnableDither)
										Vert[n].n += CPoint3(norm[0],norm[1],norm[2]);
									else*/
										Vert[n].n = CPoint3(norm[0],norm[1],norm[2]);
								}
								if (m_zflag == 1)
									Vert[n].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[n].n = CPoint3(norm[2],norm[1],norm[0]);
		#ifdef TEST_CONTUR
								if (m_zflag == 0)
									points(x,y+1) = points(x,y+1) + 1.0;
		#endif


								if (nsurf == 0 && m_zflag != 0)
								{
									mean_norm[0] += norm[0];
									mean_norm[1] += norm[1];
									mean_norm[2] += norm[2];
								}
							}

							if(nb == 4 && nsurf == 2)
							{
								d1[0] = 2*mean_norm[0];
								d1[1] = 2*mean_norm[1];
								d1[2] = 2*mean_norm[2];

								d2[0] = xi-xj;
								d2[1] = yi-yj;
								d2[2] = zi-zj;

								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								if (m_zflag == 0)
									Vert[i].n = CPoint3(norm[0],norm[1],norm[2]);
								if (m_zflag == 1)
									Vert[i].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[i].n = CPoint3(norm[2],norm[1],norm[0]);


								d2[0] = xj-xk;
								d2[1] = yj-yk;
								d2[2] = zj-zk;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали

								if (m_zflag == 0)
									Vert[j].n = CPoint3(norm[0],norm[1],norm[2]);
								if (m_zflag == 1)
									Vert[j].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[j].n = CPoint3(norm[2],norm[1],norm[0]);


								d2[0] = xk-xn;
								d2[1] = yk-yn;
								d2[2] = zk-zn;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали

								if (m_zflag == 0)
									Vert[k].n = CPoint3(norm[0],norm[1],norm[2]);
								if (m_zflag == 1)
									Vert[k].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[k].n = CPoint3(norm[2],norm[1],norm[0]);


								d2[0] = xn-xi;
								d2[1] = yn-yi;
								d2[2] = zn-zi;
								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								if (m_zflag == 0)
									Vert[n].n = CPoint3(norm[0],norm[1],norm[2]);
								if (m_zflag == 1)
									Vert[n].n = CPoint3(norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									Vert[n].n = CPoint3(norm[2],norm[1],norm[0]);
							}
							// i	n
							//
							// j	k
							if (false && nb == 3 /*&& bDrawContourTrias*/)
							{
								glEnd();
								//glBegin (GL_TRIANGLES);
								glBegin (GL_POLYGON);
									 
								if (bj && bi && bn)  // 0-j 1-i 2-n
								{
									d1[0] = xn-xi;
									d1[1] = yn-yi;
									d1[2] = zn-zi;

									d2[0] = xi-xj;
									d2[1] = yi-yj;
									d2[2] = zi-zj;
								}

								if (bk && bj && bi)  // 0-k 1-j 2-i
								{
									d1[0] = xi-xj;
									d1[1] = yi-yj;
									d1[2] = zi-zj;

									d2[0] = xj-xk;
									d2[1] = yj-yk;
									d2[2] = zj-zk;
								}

								if (bn && bk && bj)  // 0-n 1-k 2-j
								{
									d1[0] = xj-xk;
									d1[1] = yj-yk;
									d1[2] = zj-zk;

									d2[0] = xk-xn;
									d2[1] = yk-yn;
									d2[2] = zk-zn;
								}

								if (bi && bn && bk)  // 0-i 1-n 2-k
								{
									d1[0] = xk-xn;
									d1[1] = yk-yn;
									d1[2] = zk-zn;

									d2[0] = xn-xi;
									d2[1] = yn-yi;
									d2[2] = zn-zi;
								}

								getNorm(d1,d2,norm);
								//====== Задание вектора нормали
								if (m_zflag == 0)
									glNormal3dv (norm);
								if (m_zflag == 1)
									glNormal3d (norm[0],norm[2],norm[1]);
								if (m_zflag == 2)
									glNormal3d (norm[2],norm[1],norm[0]);

								if(bi)
								{
									//glColor3f (0.2f, 0.8f, 1.f);
									if (m_zflag == 0)
										glVertex3d (xi, yi, zi);
									if (m_zflag == 1)
										glVertex3d (zi, yi, xi);
									if (m_zflag == 2)
										glVertex3d (xi, zi, yi);
		#ifdef TEST_CONTUR
									points(x,y) = points(x,y) + 1.0;
		#endif
								}
								if (bj)
								{								
									//glColor3f (0.6f, 0.7f, 1.f);
									if (m_zflag == 0)
										glVertex3d (xj, yj, zj);
									if (m_zflag == 1)
										glVertex3d (zj, yj, xj);
									if (m_zflag == 2)
										glVertex3d (xj, zj, yj);
		#ifdef TEST_CONTUR
									points(x+1,y) = points(x+1,y) + 1.0;
		#endif
								}
								if (bk)
								{
									//glColor3f (0.7f, 0.9f, 1.f);
									if (m_zflag == 0)
										glVertex3d (xk, yk, zk);
									if (m_zflag == 1)
										glVertex3d (zk, yk, xk);
									if (m_zflag == 2)
										glVertex3d (xk, zk, yk);
		#ifdef TEST_CONTUR
									points(x+1,y+1) = points(x+1,y+1) + 1.0;
		#endif
								}
								if (bn)
								{
									//glColor3f (0.7f, 0.8f, 1.f);
									if (m_zflag == 0)
										glVertex3d (xn, yn, zn);
									if (m_zflag == 1)
										glVertex3d (zn, yn, xn);
									if (m_zflag == 2)
										glVertex3d (xn, zn, yn);
		#ifdef TEST_CONTUR
									points(x,y+1) = points(x,y+1) + 1.0;
		#endif
								}
							}
						}
						else /*if (!m_bQuad)*/
						//====== Ветвь создания цепочки четырехугольников
						{
							if (bn && bj)
							{
		#ifndef DRAW_ELEMENTS

								//glColor3f (0.9f, 0.9f, 1.0f);
								if (m_zflag == 0)
									glVertex3d (xn, yn, zn);
								if (m_zflag == 1)
									glVertex3d (zn, yn, xn);
								if (m_zflag == 2)
									glVertex3d (xn, zn, yn);
								//glColor3f (0.5f, 0.8f, 1.0f);
								if (m_zflag == 0)
									glVertex3d (xj, yj, zj);
								if (m_zflag == 1)
									glVertex3d (zj, yj, xj);
								if (m_zflag == 2)
									glVertex3d (xj, zj, yj);
		#endif
							}
						}
					}

				}
				//====== Закрываем блок команд GL_QUADS
					// close drawing of contour triangels	
		//		glEnd();
		//		glEndList();


		#ifdef TEST_CONTUR
				s++;
				char fname[63];
				sprintf(fname, "d://points%02d.txt",s);
				points.Write(fname,"wt", "points in the surf", true);
				vdouble contur;
				contur.resize(nx+1, ny+1, 0.0);
				for( UINT x = 1; x < nx;  x++)
				{
					for( UINT y = 1; y < ny;  y++)
					{
						contur(x,y);
						int nonzeros = 
							int(points(x  ,y  ) > 0 ) +
							int(points(x-1,y-1) > 0 ) +
							int(points(x  ,y-1) > 0 ) +
							int(points(x+1,y-1) > 0 ) +
							int(points(x+1,y  ) > 0 ) +
							int(points(x+1,y+1) > 0 ) +
							int(points(x  ,y+1) > 0 ) +
							int(points(x-1,y+1) > 0 ) +
							int(points(x-1,y  ) > 0 ) ;
						if(nonzeros > 0 && nonzeros < 9 && points(x,y) > 0 )
							contur(x,y) = 1.0;


					}
				}
				sprintf(fname, "d://contur%02d.txt",s);
				contur.Write(fname,"wt", "contur in the surf", true);
		#endif

		//fprintf(stream, "begin\n");
	/*			if (m_pSurfDoc->m_bEnableDither)
				{
					for (y=0, i=0;  y<=ny;  y++)
					{
						//====== Цикл прохода вдоль оси X
						for (UINT x=0;  x<=nx;  x++, i++)
						{
							norm[0] = Vert[i].n.x ;
							norm[1] = Vert[i].n.y ;
							norm[2] = Vert[i].n.z ;
			//fprintf(stream, "i = %d xi = %lf, yi = %lf zi = %lf\n", i, Vert[i].n.x, Vert[i].n.y, Vert[i].n.z);
			//fclose(stream);stream = fopen("D:\\DrawSurfs.txt","at");
							if (Scale(norm))
							{
								Vert[i].n.x = norm[0] ;
								Vert[i].n.y = norm[1] ;
								Vert[i].n.z = norm[2] ;
			//fprintf(stream, "i = %d xi = %lf, yi = %lf zi = %lf\n", i, Vert[i].n.x, Vert[i].n.y, Vert[i].n.z);
			//fclose(stream);stream = fopen("D:\\DrawSurfs.txt","at");
							}
			//fprintf(stream, "\n");
			//fclose(stream);stream = fopen("D:\\DrawSurfs.txt","at");
						}
					}
				}*/
		//fprintf(stream, "end\n");
				//====== Задание адресов трех массивов (вершин,
				//====== нормалей и цветов),
				//====== а также шага перемещения по ним
				glVertexPointer(3, GL_PRECISION, sizeof(VERT), &Vert->v);
				glNormalPointer(GL_PRECISION, sizeof(VERT), &Vert->n);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT),
																&Vert->c);
		//WriteRaporto("Surface3D pre glNewList\n");
				//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
				//====== Установка режима заполнения
				//====== внутренних точек полигонов
				GLint oldPolygonMode[2];
				glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
				glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

				//WriteRaporto("Surface3D post glNewList\n");

				//====== Формирование списка рисующих команд
				if (!m_bQuad)
					glDrawElements(GL_QUAD_STRIP, 4*q/*nx*ny*4*/,
										GL_UNSIGNED_INT, Quad);
				else
					glDrawElements(GL_QUADS, 4*q/*nx*ny*4*/,
										GL_UNSIGNED_INT, Quad);

				glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
				//glEndList();
				
				//== Освобождение памяти, так как список сформирован
				delete [] Vert;
				delete [] Quad;
			}
		}
	}
}

double Surface3D::GridVolume()
{
	double volume = 0.0;
	//====== Размеры изображаемого объекта
	UINT	nx = m_lenx-1,
			ny = m_leny-1;

/*	CPoint3 *ptv;
	CPoint3 *ptd;
	ptv = m_vvPoints;
	ptd = m_vdPoints;*/

	double xSize = this->GetDocumentPoint(1).x - this->GetDocumentPoint(0).x;
	double ySize = this->GetDocumentPoint(m_lenx).y - this->GetDocumentPoint(0).y;


	PRIMITIVE_POINTS_PTR(CPoint3) ptv;
	PRIMITIVE_POINTS_PTR(CPoint3) ptd;

	ptv = m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
	ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;


	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT y=0, i=0;  y<ny;  y++, i++)
	{
		//====== Цикл прохода вдоль оси X
		for (UINT x=0;  x<nx;  x++, i++)
		{
			// i, j, k, n - 4 индекса вершин примитива при
			// обходе в направлении против часовой стрелки

			int	j = i + 
				nx + 1,	// Индекс узла с большим Z

				k = j+1,			// Индекс узла по диагонали
				n = i+1; 			// Индекс узла справа

			//=== Выбор координат 4-х вершин из контейнера

			bool 
				bi = ptv[i].bVisible,
				bj = ptv[j].bVisible,
				bk = ptv[k].bVisible,
				bn = ptv[n].bVisible;

			int nb = int(bi) + int(bj) + int(bk) + int(bn);

			CPoint3 pt3;

			pt3.x = (ptd[i].x + ptd[j].x + ptd[k].x + ptd[n].x ) / 4;
			pt3.y = (ptd[i].y + ptd[j].y + ptd[k].y + ptd[n].y ) / 4;
			pt3.z = (ptd[i].z + ptd[j].z + ptd[k].z + ptd[n].z ) / 4;

			if (bi && bj && bk && bn)
			{
				volume += xSize * ySize * pt3.z;
			}
			else if (3 == nb)
			{
				volume += 0.75 * xSize * ySize * pt3.z;
			}
			else if (2 == nb)
			{
				volume += 0.5 * xSize * ySize * pt3.z;
			}
			else if (1 == nb)
			{
				volume += 0.25 * xSize * ySize * pt3.z;
			}
		}
	}
	return volume;
}

void Surface3D::DrawQuadsNumbers()
{
	//====== Размеры изображаемого объекта
	UINT	nx = m_lenx-1,
			ny = m_leny-1;

/*	CPoint3 *ptv;
	CPoint3 *ptd;
	ptv = m_vvPoints;
	ptd = m_vdPoints;*/

	PRIMITIVE_POINTS_PTR(CPoint3) ptv;
	PRIMITIVE_POINTS_PTR(CPoint3) ptd;

	ptv = m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
	ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;


	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT y=0, i=0;  y<ny;  y++, i++)
	{
		//====== Цикл прохода вдоль оси X
		for (UINT x=0;  x<nx;  x++, i++)
		{
			// i, j, k, n - 4 индекса вершин примитива при
			// обходе в направлении против часовой стрелки

			int	j = i + 
				nx + 1,	// Индекс узла с большим Z

				k = j+1,			// Индекс узла по диагонали
				n = i+1; 			// Индекс узла справа

			//=== Выбор координат 4-х вершин из контейнера

			bool 
				bi = ptv[i].bVisible,
				bj = ptv[j].bVisible,
				bk = ptv[k].bVisible,
				bn = ptv[n].bVisible;

			if (bi || bj || bk || bn)
//			if (bi && bj && bk && bn)
			{
				// подписываем номера клеток
				CPoint3 pt3;

				pt3.x = (ptd[i].x + ptd[j].x + ptd[k].x + ptd[n].x ) / 4;
				pt3.y = (ptd[i].y + ptd[j].y + ptd[k].y + ptd[n].y ) / 4;
				pt3.z = (ptd[i].z + ptd[j].z + ptd[k].z + ptd[n].z ) / 4;

				char s[255];
				sprintf(s, "%d %d\0", y,x);
				this->m_pSurfDoc->AddString(pt3,s,RGB(0,0,255),0.0);
			}
		}
	}
}

COLORREF Surface3D::GetColor(double z)
{
	COLORREF surfColor;
	if (this->m_pSurfDoc && this->m_pSurfDoc->m_bUseColormapOnSurf && m_zflag == 0)
	//if (m_bUseColormap)
	{
		double color;
		double delta_z;

		if (m_bLocalColormap)
		{
			double maxz = GetMax().z;
			double minz = GetMin().z;									
			delta_z = maxz - minz;
			//*********************************
			if (m_bInverseColormap)
			{
				color = (maxz - z) / (delta_z); 
			}
			else
			{
				color = (z - minz) / (delta_z); 
			}
		}
		else
		{
			double 
				maxzforallsurfs = m_pSurfDoc->m_zd_max, 
				minzforallsurfs = m_pSurfDoc->m_zd_min;

			delta_z = m_pSurfDoc->m_zd_max - m_pSurfDoc->m_zd_min;
			//*********************************
			if (m_bInverseColormap)
			{
				color = (maxzforallsurfs - z) / (delta_z); 
			}
			else
			{
				color = (z - minzforallsurfs) / (delta_z); 
			}
		}
		surfColor = m_palette.GetColorWithAlpha(color,
							(GLubyte)m_alpha);
	}
	else
		surfColor = RGBA (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color), 
		(GLubyte)m_alpha); 

	return surfColor;

}
int Surface3D::GetAlphaSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
	switch (GetDlgCtrlID(hwnd))
	{
	//====== Выясняем идентификатор окна справа
	case IDC_SLIDER_SURF_ALPHA:
		nID = IDC_EDIT_SURF_ALPHA;
		return 0;
	case IDC_SLIDER_SURF_ALPHA_PLANE:
		nID = IDC_EDIT_SURF_ALPHA_PLANE;
		return 1;
	}
	return 0;
}

BOOL CALLBACK Surface3D::DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static Surface3D * me;
	static int m_Pos[11]; 			// Массив позиций ползунков
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	


			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (Surface3D *)lPage->lParam;

			char str[1023];
			sprintf(str,"%d",me->m_alpha);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA, str);

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-описатель окна активного ползунка
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== Определяем индекс в массиве позиций ползунков
				int num = GetAlphaSliderNum(hwnd, nID);
				int delta, newPos;

				//====== Анализируем код события
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// Управление мышью
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// Клавиша Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// Клавиша End
					delta = +255;
					goto New_Pos;
				case SB_LINELEFT:			// Клавиша <-
					delta = -1;
					goto New_Pos;
				case SB_LINERIGHT:			// Клавиша ->
					delta = +1;
					goto New_Pos;
				case SB_PAGELEFT:			// Клавиша PgUp
					delta = -20;
					goto New_Pos;
				case SB_PAGERIGHT:			// Клавиша PgDn
					delta = +20;
					goto New_Pos;

				New_Pos:						// Общая ветвь
					//====== Устанавливаем новое значение регулятора
					newPos = m_Pos[num] + delta;
					//====== Ограничения
					m_Pos[num] = newPos<0 ? 0 : newPos>255 ? 255 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				//====== Синхронизируем параметр lp и
				//====== устанавливаем его в положение nPos
				switch (num)
				{
				case 0:
					me->m_alpha = m_Pos[num];
					break;
				}


				//====== Синхронизируем текстовый аналог позиции
				char s[1024];
				sprintf (s,"%d",me->m_alpha);
				sprintf (s,"%d",m_Pos[num]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				// init of zoomCoefZ_XY
				//me->m_pSurfDoc->ZoomView();
				me->m_pSurfDoc->Draw();
				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				//=== Добываем Windows-описатель окна ползунка
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA_PLANE);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== Проход по всем регулировкам
				//for (int i=0; i<2; i++)
					//====== Заполняем транспортный массив pPos
					m_Pos[0] = me->m_alpha;

				//====== Массив идентификаторов ползунков
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_ALPHA,
				};

				//====== Цикл прохода по всем регуляторам
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== Добываем Windows-описатель окна ползунка
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== Определяем его идентификатор
					int num = Surface3D::GetAlphaSliderNum(hwnd, nID);

					// Требуем установить ползунок в положение m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					char s[1024];
					//====== Готовим текстовый аналог текущей позиции
					sprintf (s,"%d",m_Pos[i]);
					//====== Помещаем текст в окно справа от ползунка
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);
				}
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA,str,1022);
				int alpha = atoi (str);
				if (alpha >= 0.0)
					me->m_alpha = alpha;
				else
					MessageBox(0, "Enter a valid value", "Alpha dialog", 0);

//				GetDlgItemText(hDlg, IDC_EDIT_SURF_RAZLOM_THICKNESS,str,1022);
//				double thickness = atof (str);
				//if (thickness >= 0.0)
//					me->m_pSurfDoc->m_razlomThickness = thickness;
				//else
				//	MessageBox(0, "Enter a valid value", "Alpha dialog", 0);

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

				
				// init of zoomCoefZ_XY
				me->m_pSurfDoc->ZoomView();


				me->m_pSurfDoc->Draw();

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);

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

 
BOOL CALLBACK  Surface3D::DlgProcSurfPalette( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
//	static LPSURFDLGDATA lpSurfDlgMem;
	static Surface3D * me;
    TCHAR tchBuffer[MAX_PATH]; 
    static HWND hListBox; 
    TEXTMETRIC tm; 
    int y; 
    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 
	LONG itemdata;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (Surface3D *)lPage->lParam;

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_INVERSE_COLORMAP,
				me->m_bInverseColormap ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_LOCAL_COLORMAP,
				me->m_bLocalColormap ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			SendMessage(hDlg,WM_COMMAND,INIT_COMBO_IDC_COMBO_SURF_COLORMAP,0);
            hListBox = GetDlgItem(hDlg, IDC_LIST_SURF_CREATE_PALETTE); 
 
            wpOrigListBoxProc2 = (WNDPROC) SetWindowLongPtr(hListBox, 
				GWLP_WNDPROC, (LONG_PTR) ListBoxPaletteSubclassProc); 

			SendMessage(hDlg, WM_COMMAND, INIT_SURF_PALETTE, 0);
		}
		break;
	case WM_MEASUREITEM:
		{ 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            // Set the height of the List box items. 
            lpmis->itemHeight = YBITMAP2; 
		}
		break;
	case WM_DRAWITEM: 
		{
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
 
            // If there are no List box items, skip this message. 
            if (lpdis->itemID == -1) 
            { 
                break; 
            } 
            // Draw the bitmap and text for the List box item. Draw a 
            // rectangle around the bitmap if it is selected. 
 
            switch (lpdis->itemAction) 
            { 
			case ODA_SELECT:
			case ODA_FOCUS:
            case ODA_DRAWENTIRE: 
				{ 
                    // Display the bitmap associated with the item. 
 
                    itemdata = SendMessage(lpdis->hwndItem, 
                        LB_GETITEMDATA, lpdis->itemID, (LPARAM) 0); 

					HBRUSH brush =  CreateSolidBrush(
					  (COLORREF) itemdata   // brush color value
					);
					FillRect(lpdis->hDC, &lpdis->rcItem, brush);
					DeleteObject(brush);

                    // Display the text associated with the item. 
 
                    SendMessage(lpdis->hwndItem, LB_GETTEXT, 
                        lpdis->itemID, (LPARAM) tchBuffer); 
 
                    GetTextMetrics(lpdis->hDC, &tm); 
 
                    y = (lpdis->rcItem.bottom + lpdis->rcItem.top - 
                        tm.tmHeight) / 2;
						
 
                    TextOut(lpdis->hDC, 
                        2, 
                        y, 
                        tchBuffer, 
                        strlen(tchBuffer)); 						
 
                    // Is the item selected? 
 
                    if (lpdis->itemState & ODS_SELECTED) 
                    { 
                        // Draw a rectangle around bitmap to indicate 
                        // the selection. 
 
                        DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
                    } 
				}
                break; 
 
            } 
		}
		break;
 
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case INIT_SURF_PALETTE:
			{				
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0); 
				// with each List box item. 
				char item_str[255];
				int palette_len = me->m_palette.GetLen();
				int j = 0;
				if (me->m_bInverseColormap)
				{
					for (UINT r = palette_len - 1, j = 0; j < palette_len ; r--, j++)
					{
						sprintf(item_str, "%d", j);
						COLORREF itemcolor = me->m_palette.GetColor(r);
						AddCheckedPaletteItem(hListBox, 
							item_str, LONG(itemcolor));
					}
				}
				else
				{
					for (UINT r = 0; r < palette_len; r++)
					{
						sprintf(item_str, "%d", r);
						COLORREF itemcolor = me->m_palette.GetColor(r);
						AddCheckedPaletteItem(hListBox, 
							item_str, LONG(itemcolor));
					}
				}
				SetFocus(hListBox); 
				SendMessage(hListBox, LB_SETCURSEL, 0, 0); 
			}
			break;
		case IDC_BUTTON_INTERPOLATE:
			{
				LONG itemdata = SendMessage(hListBox, LB_GETITEMDATA, 0, 0);
				me->m_palette.InitFirst(COLORREF (itemdata) ); 
				LONG count_of_items = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				itemdata = SendMessage(hListBox, LB_GETITEMDATA, count_of_items - 1, 0);
				me->m_palette.InitLast(COLORREF (itemdata) ); 
				me->m_palette.Interpolate();
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);	
			}
			break;
		case IDC_BUTTON_SURF_PALETTE_APPLY:
			{
				LONG count_of_items = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				me->m_palette.Free();
				me->m_palette.Allocate(count_of_items);
				for ( int i = 0; i < count_of_items; i++)
				{
					LONG itemdata = SendMessage(hListBox, LB_GETITEMDATA, i, 0);
					me->m_palette.InitItem(i,COLORREF (itemdata) );
				}
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);	
			}
			break;
		case IDC_BUTTON_SURF_PALETTE_PLOT:
			{
				int len = me->m_palette.GetLen();
				Vector<vdouble> vx(3), vy(3);
				for (int iv = 0; iv < 3; iv++)
				{
					vx[iv].resize(len);
					vy[iv].resize(len);
					for ( UINT i = 0; i < len; i++)
					{
						COLORREF color = me->m_palette.GetColor(i);
						vx[iv][i] = i;
						switch (iv)
						{
						case 0:
							vy[iv][i] = GetRValue(color);
							break;
						case 1:
							vy[iv][i] = GetGValue(color);
							break;
						case 2:
							vy[iv][i] = GetBValue(color);
							break;
						}
					}
				}
				WinPlot(vx,vy);
			}
			break;
		case IDC_BUTTON_SURF_PALETTE_EXTRACT:
			{
				if (me->m_palette.GetLen() < 2048)
				{
					me->m_palette.Extract(2);
					SendMessage(hDlg, WM_COMMAND, IDOK, 1);
					char str[255];
					sprintf(str, "palette length = %d", me->m_palette.GetLen());
					SetDlgItemText(hDlg,IDC_STATIC_SURF_PALETTE_LEN, str);
				}
			}
			break;
		case IDC_CHECK_SURF_LOCAL_COLORMAP:
			{
				me->m_bLocalColormap = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_LOCAL_COLORMAP) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);
			}
			break;
		case IDC_CHECK_SURF_INVERSE_COLORMAP:
			{
				me->m_bInverseColormap = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_INVERSE_COLORMAP) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);
			}
			break;
		case IDC_COMBO_SURF_COLORMAP:
			{
				int nColormap = 
					SendDlgItemMessage( hDlg, IDC_COMBO_SURF_COLORMAP, 
					CB_GETCURSEL,0,(LPARAM)0 );
				if (nColormap >= 0 && nColormap < 21)
				{
					me->m_nColormap = UINT(nColormap);

					char str[255];
					sprintf(str, "%u", me->m_nColormap);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_N_COLORMAP, str);

					//SendMessage(hDlg, WM_COMMAND, IDOK, 0);					
				}
			}
			break;
		case INIT_COMBO_IDC_COMBO_SURF_COLORMAP:
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_COLORMAP, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				for (int i = 0; i < 21; i++)
				{					
					SendDlgItemMessage( hDlg, 
						IDC_COMBO_SURF_COLORMAP, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)colormap_strings[i]);
				}
				
				SendDlgItemMessage( hDlg, 
					IDC_COMBO_SURF_COLORMAP, CB_SETCURSEL, 0, me->m_nColormap);
			}
			break;
		case IDOK:
			{
				if (lParam != 1)
					APalette::InitPalette(&me->m_palette, me->m_nColormap);

				SendMessage(hDlg, WM_COMMAND, INIT_SURF_PALETTE, 0);
				me->m_pSurfDoc->ZoomView();
				
				me->m_pSurfDoc->Draw();

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);

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

void Surface3D::PropertiesDialog()
{
    // Ensure that the common control DLL is loaded. 
	// InitCommonControls(); 
	// Инициализируем страницы блокнота  
	psheetPage[0].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[0].hInstance = hInst;
//	psheetPage[0].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[0].pszIcon = NULL;
	psheetPage[0].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_SURF_ALPHA);
	psheetPage[0].pfnDlgProc = Surface3D::DlgProcSurfAlpha;
	psheetPage[0].pszTitle = "Alpha";
	psheetPage[0].lParam = (LPARAM)this;

	// Добавляем страницу в блокнот, сохраняя ее
	// идентификатор в массиве hPage
	hPage[0] = CreatePropertySheetPage(&psheetPage[0]);

	psheetPage[1].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[1].hInstance = hInst;
//	psheetPage[1].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[1].pszIcon = NULL;
	psheetPage[1].dwFlags = PSP_USETITLE /*| PSP_USEICONID*/;
	psheetPage[1].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_SURF_PALETTE);
	psheetPage[1].pfnDlgProc = Surface3D::DlgProcSurfPalette;
	psheetPage[1].pszTitle = "Palette";
	psheetPage[1].lParam = (LPARAM)this;
	hPage[1] = CreatePropertySheetPage(&psheetPage[1]);

#if 0
	psheetPage[2].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[2].hInstance = hInst;
//	psheetPage[2].pszIcon = MAKEINTRESOURCE(IDI_KEYWORD);
	psheetPage[2].dwFlags = PSP_USETITLE /*| PSP_USEICONID*/;
	psheetPage[2].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG3);
	psheetPage[2].pfnDlgProc = DlgProc3;
	psheetPage[2].pszTitle = "Keyword";
	psheetPage[2].lParam = 0;
	hPage[2] = CreatePropertySheetPage(&psheetPage[2]);
#endif

	// Инициализируем заголовок блокнота
	psheetHeader.dwSize = sizeof(PROPSHEETHEADER);
	psheetHeader.hInstance = hInst;
	psheetHeader.pszIcon = MAKEINTRESOURCE(IDI_APPICONSM);
//	psheetHeader.dwFlags = PSH_MODELESS | PSH_USEICONID;
	psheetHeader.dwFlags = PSH_USEICONID;
	psheetHeader.hwndParent = this->m_pSurfDoc->hwndTV;
	psheetHeader.hwndParent = this->m_pSurfDoc->hSurfWnd;
	psheetHeader.hwndParent = NULL;
	psheetHeader.pszCaption = "Surface Properties";
	psheetHeader.nPages = 
	sizeof(psheetPage) / sizeof(PROPSHEETPAGE);
	psheetHeader.phpage = (HPROPSHEETPAGE FAR  *)&hPage[0];

	// Создаем и отображаем блокнот
	PropertySheet(&psheetHeader);

	//For a modeless property sheet, your message loop should use 
	//PSM_ISDIALOGMESSAGE to pass messages to the property sheet dialog box. 
	//Your message loop should use PSM_GETCURRENTPAGEHWND to determine when 
	//to destroy the dialog box. When the user clicks the OK or Cancel button, 
	//PSM_GETCURRENTPAGEHWND returns NULL. You can then use the DestroyWindow 
	//function to destroy the dialog box.


}
//====== Операция присвоения
Surface3D& Surface3D::operator=(const Surface3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

Surface3D::Surface3D(const Surface3D &ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

void Surface3D::Init(const Surface3D &ob)
{
	m_palette			= ob.m_palette;
	m_nColormap			= ob.m_nColormap;

	m_bUseColormap		= ob.m_bUseColormap;
	m_bLocalColormap	= ob.m_bLocalColormap;
	m_bInverseColormap	= ob.m_bInverseColormap;

	m_bQuad				= ob.m_bQuad; // Флаг использования GL_QUAD
	m_pSurfDoc			= ob.m_pSurfDoc;

	m_zflag				= ob.m_zflag;
	m_leny				= ob.m_leny;
	m_lenx				= ob.m_lenx;
}
bool Surface3D::UpdateExtremums()
{
	bool start = true;
				
	switch (this->m_zflag)
	{
	case 0:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				if (m_vdPoints[ipoint].bVisible)
				{
					if (start)
					{
						m_ptMin.x = m_ptMax.x = m_vdPoints[ipoint].x;
						m_ptMin.y = m_ptMax.y = m_vdPoints[ipoint].y;
						m_ptMin.z = m_ptMax.z = m_vdPoints[ipoint].z;
						start = false;
					}
					else
					{
						if (m_ptMin.x > m_vdPoints[ipoint].x) m_ptMin.x = m_vdPoints[ipoint].x;
						if (m_ptMax.x < m_vdPoints[ipoint].x) m_ptMax.x = m_vdPoints[ipoint].x;

						if (m_ptMin.y > m_vdPoints[ipoint].y) m_ptMin.y = m_vdPoints[ipoint].y;
						if (m_ptMax.y < m_vdPoints[ipoint].y) m_ptMax.y = m_vdPoints[ipoint].y;

						if (m_ptMin.z > m_vdPoints[ipoint].z) m_ptMin.z = m_vdPoints[ipoint].z;
						if (m_ptMax.z < m_vdPoints[ipoint].z) m_ptMax.z = m_vdPoints[ipoint].z;
					}
				}
			}
		}
		break;
	case 1:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				if (m_vdPoints[ipoint].bVisible)
				{
					if (start)
					{
						m_ptMin.x = m_ptMax.x = m_vdPoints[ipoint].z;
						m_ptMin.y = m_ptMax.y = m_vdPoints[ipoint].y;
						m_ptMin.z = m_ptMax.z = m_vdPoints[ipoint].x;
						start = false;
					}
					else
					{
						if (m_ptMin.x > m_vdPoints[ipoint].z) m_ptMin.x = m_vdPoints[ipoint].z;
						if (m_ptMax.x < m_vdPoints[ipoint].z) m_ptMax.x = m_vdPoints[ipoint].z;

						if (m_ptMin.y > m_vdPoints[ipoint].y) m_ptMin.y = m_vdPoints[ipoint].y;
						if (m_ptMax.y < m_vdPoints[ipoint].y) m_ptMax.y = m_vdPoints[ipoint].y;

						if (m_ptMin.z > m_vdPoints[ipoint].x) m_ptMin.z = m_vdPoints[ipoint].x;
						if (m_ptMax.z < m_vdPoints[ipoint].x) m_ptMax.z = m_vdPoints[ipoint].x;
					}
				}
			}
		}
		break;
	case 2:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				if (m_vdPoints[ipoint].bVisible)
				{
					if (start)
					{
						m_ptMin.x = m_ptMax.x = m_vdPoints[ipoint].x;
						m_ptMin.y = m_ptMax.y = m_vdPoints[ipoint].z;
						m_ptMin.z = m_ptMax.z = m_vdPoints[ipoint].y;
						start = false;
					}
					else
					{
						if (m_ptMin.x > m_vdPoints[ipoint].x) m_ptMin.x = m_vdPoints[ipoint].x;
						if (m_ptMax.x < m_vdPoints[ipoint].x) m_ptMax.x = m_vdPoints[ipoint].x;

						if (m_ptMin.y > m_vdPoints[ipoint].z) m_ptMin.y = m_vdPoints[ipoint].z;
						if (m_ptMax.y < m_vdPoints[ipoint].z) m_ptMax.y = m_vdPoints[ipoint].z;

						if (m_ptMin.z > m_vdPoints[ipoint].y) m_ptMin.z = m_vdPoints[ipoint].y;
						if (m_ptMax.z < m_vdPoints[ipoint].y) m_ptMax.z = m_vdPoints[ipoint].y;
					}
				}
			}
		}
		break;
	}
	return !start;
}
void Surface3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	switch (this->m_zflag)
	{
	case 0:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

				m_vvPoints[ipoint].x = 
					zoomX * (m_vdPoints[ipoint].x - x_mean);
				m_vvPoints[ipoint].y = 
					zoomY * (m_vdPoints[ipoint].y - y_mean);
				m_vvPoints[ipoint].z = 
					zoomZ * (m_vdPoints[ipoint].z - z_mean);
			}
		}
		break;
	case 1:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

				m_vvPoints[ipoint].x = 
					zoomZ * (m_vdPoints[ipoint].x - z_mean);
				m_vvPoints[ipoint].y = 
					zoomY * (m_vdPoints[ipoint].y - y_mean);
				m_vvPoints[ipoint].z = 
					zoomX * (m_vdPoints[ipoint].z - x_mean);
			}
		}
		break;
	case 2:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

				m_vvPoints[ipoint].x = 
					zoomX * (m_vdPoints[ipoint].x - x_mean);
				m_vvPoints[ipoint].y = 
					zoomZ * (m_vdPoints[ipoint].y - z_mean);
				m_vvPoints[ipoint].z = 
					zoomY * (m_vdPoints[ipoint].z - y_mean);
			}
		}
		break;
	}
}
void Surface3D::ZoomInv(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	switch (this->m_zflag)
	{
	case 0:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
				m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
				m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
				m_vdPoints[ipoint].z = z_mean + m_vvPoints[ipoint].z / zoomZ;
			}
		}
		break;
	case 1:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
				m_vdPoints[ipoint].x = z_mean + m_vvPoints[ipoint].x / zoomZ;
				m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
				m_vdPoints[ipoint].z = x_mean + m_vvPoints[ipoint].z / zoomX;
			}
		}
		break;
	case 2:
		{
			for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
			{							
				m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
				m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
				m_vdPoints[ipoint].y = z_mean + m_vvPoints[ipoint].y / zoomY;
				m_vdPoints[ipoint].z = y_mean + m_vvPoints[ipoint].z / zoomY;
			}
		}
		break;
	}
}
void Surface3D::ZoomInv(unsigned int ipoint, double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	switch (this->m_zflag)
	{
	case 0:
		{
			if (ipoint < m_nPoints && ipoint >= 0 )
			{							
				m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
				m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
				m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
				m_vdPoints[ipoint].z = z_mean + m_vvPoints[ipoint].z / zoomZ;
			}
		}
		break;
	case 1:
		{
			if (ipoint < m_nPoints && ipoint >= 0 )
			{							
				m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
				m_vdPoints[ipoint].x = z_mean + m_vvPoints[ipoint].x / zoomZ;
				m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
				m_vdPoints[ipoint].z = x_mean + m_vvPoints[ipoint].z / zoomX;
			}
		}
		break;
	case 2:
		{
			if (ipoint < m_nPoints && ipoint >= 0 )
			{							
				m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
				m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
				m_vdPoints[ipoint].y = z_mean + m_vvPoints[ipoint].y / zoomY;
				m_vdPoints[ipoint].z = y_mean + m_vvPoints[ipoint].z / zoomY;
			}
		}
		break;
	}
}
bool QuadSquareInterpolation(short zflag,// flag of direction of normal to base of the quad 0-z, 1-x, 2-y
	CPoint3& pti, CPoint3& ptj, CPoint3& ptk, CPoint3& ptn, // input points of 4 quad's vertexes
	double& A, double& B, double& C, double& D)// output koefficints of square intepolation
{
	double epsilon = 0.01;
	//Алгоритм двумерной интерполяции
	vdouble M,Z;
	M.resize(4,4);
	Z.resize(4);


	M(0,0) = pti.x * pti.y;
	M(1,0) = ptj.x * ptj.y;
	M(2,0) = ptk.x * ptk.y;
	M(3,0) = ptn.x * ptn.y;

	M(0,1) = pti.x;
	M(1,1) = ptj.x;
	M(2,1) = ptk.x;
	M(3,1) = ptn.x;

	M(0,2) = pti.y;
	M(1,2) = ptj.y;
	M(2,2) = ptk.y;
	M(3,2) = ptn.y;

	M(0,3) = 1.0;
	M(1,3) = 1.0;
	M(2,3) = 1.0;
	M(3,3) = 1.0;
	
	Z[0] = pti.z;
	Z[1] = ptj.z;
	Z[2] = ptk.z;
	Z[3] = ptn.z;



#if 1
	vdouble ABCD;
	double det;
	M.sls_det(Z, ABCD, det, false);
#else
#if 0
	vdouble pinvM;					
	M.pinv(pinvM);
	vdouble ABCD = pinvM.MatrixProduct(Z);
#else
	vdouble ABCD = M.Tichonov(Z);
#endif
#endif
	if (ABCD.Length() == 4)
	{
		A = ABCD[0];
		B = ABCD[1];
		C = ABCD[2];
		D = ABCD[3];

		vdouble ztest = M.MatrixProduct(ABCD);
		if (ztest.Length() == 4)
		{
			double Zerror = 
			fabs(Z[0] - ztest[0])+
			fabs(Z[1] - ztest[1])+
			fabs(Z[2] - ztest[2])+
			fabs(Z[3] - ztest[3]);

			if (Zerror > epsilon)
			{
				char *str, *sM , *sZ, *sABCD;
				sM = M.dispMatrix_str();
				sZ = Z.disp_str();
				sABCD = ABCD.disp_str();
				size_t len_str = strlen(sM) + strlen(sZ) + strlen(sABCD) + 1024;
				str = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len_str*sizeof(char));


				if (sM && sZ && str && sABCD)
				{
					sprintf(str, "Zerror = %lf\nABCD.Length() == 4\nM.Length() = %d\nZ.Length() = %d\nM = %s \nZ = %s \nABCD = %s", Zerror, M.Length(), Z.Length(), sM, sZ, sABCD);
					//MessageBox(0, str, "Cut", 0);
					printf("Cut:\n%s\n",str);
					if (str) HeapFree(GetProcessHeap(), 0, str);
					if (sZ) HeapFree(GetProcessHeap(), 0, sZ);
					if (sM) HeapFree(GetProcessHeap(), 0, sM);
					if (sABCD) HeapFree(GetProcessHeap(), 0, sABCD);
				}
				else
				{
					char s[255];
					sprintf(s, "ABCD.Length(%d) != 4\nM.Length() = %d\nZ.Length() = %d\n", ABCD.Length(), M.Length(), Z.Length());
					MessageBox(0, s, "Cut", 0);
				}
				return false;
			}
			else
				return true;
		}
		else
		{
			char str[255];
			sprintf(str, "ztest.Length(%d) != 4\nM.Length() = %d\nABCD.Length() = %d", ztest.Length(), M.Length(), ABCD.Length());
			MessageBox(0, str, "Cut", 0);
			return false;
		}
		return true;

	}
	else
	{
		char *str, *sM , *sZ, *sABCD;
		sM = M.dispMatrix_str();
		sZ = Z.disp_str();
		sABCD = ABCD.disp_str();
		size_t len_str = strlen(sM) + strlen(sZ) + strlen(sABCD) + 1024;
		str = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len_str*sizeof(char));


		if (sM && sZ && str && sABCD)
		{
			sprintf(str, "ABCD.Length(%d) != 4\nM.Length() = %d\nZ.Length() = %d\nM = %s \nZ = %s \nABCD = %s", ABCD.Length(), M.Length(), Z.Length(), sM, sZ, sABCD);
			MessageBox(0, str, "Cut", 0);
			if (str) HeapFree(GetProcessHeap(), 0, str);
			if (sZ) HeapFree(GetProcessHeap(), 0, sZ);
			if (sM) HeapFree(GetProcessHeap(), 0, sM);
			if (sABCD) HeapFree(GetProcessHeap(), 0, sABCD);
		}
		else
		{
			char s[255];
			sprintf(s, "ABCD.Length(%d) != 4\nM.Length() = %d\nZ.Length() = %d\n", ABCD.Length(), M.Length(), Z.Length());
			MessageBox(0, s, "Cut", 0);
		}
		return false;
	}										
	return false;
}




void Surface3D::Cutting(double a, double b, double c, double d, 
					  bool toDrawPoligones, bool positive, 
					  short type_of_cutline, int cutting_number, int surf_number,					  
					  CPoint2* pt1, CPoint2* pt2 //две точки, 
					  //ограничивающие линию прамолинейного участка ломанного разреза
					  , void * pBrokenPlane, GeoSurface * pGeoSurface, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix,
					  ObjectList * cutplane_polygones_ObjectList, 
					  vect<Poligon3D> * cutplane_polygones)
{	
	this->m_N_quad = Surface3D::s_N_quad;
printf("Surface3D::Cutting()\n");
	//====== Размеры изображаемого объекта
	UINT	nx = m_lenx-1,
			ny = m_leny-1;

	PRIMITIVE_POINTS_PTR(CPoint3) ptd;
	ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

	double min_x,max_x,min_y,max_y;
	if (pt1 && pt2)
	{
		min_x = min(pt1->x,pt2->x);
		max_x = max(pt1->x,pt2->x);
		min_y = min(pt1->y,pt2->y);
		max_y = max(pt1->y,pt2->y);
	}
	//==========================================================
	//==========================================================
	//==========================================================
	//=== НАЧИНАЕМ ФОРМИРОВАНИЕ ВЕКТОРА ТОЧЕК СЕЧЕНИЯ КЛЕТОК ===
	//==========================================================
	//==========================================================
	//==========================================================
	{
		vxyz.CreateNewVect();
		// инициализируем Вектор для клеточных сечений
		VXYZ_VECTOR<VXYZ_VECTOR< CPoint3> > vvp;
		vxyz.GetLastVect().AddMsg(&vvp);
		vxyz.GetLastVect().SetVectorData(nx);
		// резервируем память для всех клеток в этом векторе
		vxyz.GetLastVect().GetLastMsg().resize(nx*ny);
		for (int q = 0; q < vxyz.GetLastVect().GetLastMsg().VXYZ_VECTOR_SIZE(); q++)
		{
			vxyz.GetLastVect().GetLastMsg()[q].resize(0);
		}
	}
	//==========================================================
	//==========================================================
	//==========================================================
	vQuadCutting.CreateNewVect();
	// инициализируем Вектор для клеточных сечений
	Vector <QuadCutting>  vqc;
	vQuadCutting.GetLastVect().AddMsg(&vqc);
	// резервируем память для всех клеток в этом векторе
	vQuadCutting.GetLastVect().GetLastMsg().resize(nx*ny);
	for (int q = 0; q < vxyz.GetLastVect().GetLastMsg().VXYZ_VECTOR_SIZE(); q++)
	{
		vQuadCutting.GetLastVect().GetLastMsg()[q].bCutted = 0;
	}
	//==========================================================
	//==========================================================
	//==========================================================


	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT row_quad=0, i=0;  row_quad<ny;  row_quad++, i++)
	{
		//====== Связанные полигоны начинаются

		//====== Цикл прохода вдоль оси X
		for (UINT col_quad=0;  col_quad<nx;  col_quad++, i++)
		{
			// i, j, k, n - 4 индекса вершин примитива при
			// обходе в направлении против часовой стрелки

			int	j = i + nx + 1,	// Индекс узла с большим Z

				k = j+1,			// Индекс узла по диагонали
				n = i+1; 			// Индекс узла справа

			//=== Выбор координат 4-х вершин из контейнера
			double 
				xi,yi,zi,
				xj,yj,zj,
				xk,yk,zk,
				xn,yn,zn;

			if (m_zflag == 0)
			{
				xi = ptd[i].x,
				yi = ptd[i].y,
				zi = ptd[i].z,

				xj = ptd[j].x,
				yj = ptd[j].y,
				zj = ptd[j].z,

				xk = ptd[k].x,
				yk = ptd[k].y,
				zk = ptd[k].z,

				xn = ptd[n].x,
				yn = ptd[n].y,
				zn = ptd[n].z;
			}
			if (m_zflag == 1) // x <-> z
			{
				xi = ptd[i].z,
				yi = ptd[i].y,
				zi = ptd[i].x,

				xj = ptd[j].z,
				yj = ptd[j].y,
				zj = ptd[j].x,

				xk = ptd[k].z,
				yk = ptd[k].y,
				zk = ptd[k].x,

				xn = ptd[n].z,
				yn = ptd[n].y,
				zn = ptd[n].x;
			}
			if (m_zflag == 2) // y <-> z
			{
				xi = ptd[i].x,
				yi = ptd[i].z,
				zi = ptd[i].y,

				xj = ptd[j].x,
				yj = ptd[j].z,
				zj = ptd[j].y,

				xk = ptd[k].x,
				yk = ptd[k].z,
				zk = ptd[k].y,

				xn = ptd[n].x,
				yn = ptd[n].z,
				zn = ptd[n].y;
			}
/*
			if (// условие
#if 1
				true
#else
				!(pt1 && pt2) // или неломанный разрез
				|| 
				(
				(pt1 && pt2) // или если ломанный, 
				//то соответствует ли текущая клетка 
				//критерию нахождения внутри 
				//прямолинейного участка ломанного разреза
				&& 
				(
				(  xi >= min_x && xi <= max_x
				&& yi >= min_y && yi <= max_y)
				||
				(  xj >= min_x && xj <= max_x
				&& yj >= min_y && yj <= max_y)
				||
				(  xk >= min_x && xk <= max_x
				&& yk >= min_y && yk <= max_y)
				||
				(  xn >= min_x && xn <= max_x
				&& yn >= min_y && yn <= max_y)
				)
				//конец определения критерия
				)
#endif
				)
			{
*/
			bool 
				bi = ptd[i].bVisible,
				bj = ptd[j].bVisible,
				bk = ptd[k].bVisible,
				bn = ptd[n].bVisible;


			// растояние от точки до плоскости
			double ri = a*xi+b*yi+c*zi+d; 
			double rj = a*xj+b*yj+c*zj+d; 
			double rn = a*xn+b*yn+c*zn+d; 
			double rk = a*xk+b*yk+c*zk+d; 

#if 0
			// растояние между точками
			double rij = sqrt( (xi-xj)*(xi-xj) + (yi-yj)*(yi-yj) + (zi-zj)*(zi-zj) );
			double rin = sqrt( (xi-xn)*(xi-xn) + (yi-yn)*(yi-yn) + (zi-zn)*(zi-zn) );
			double rik = sqrt( (xi-xk)*(xi-xk) + (yi-yk)*(yi-yk) + (zi-zk)*(zi-zk) );

			double rjk = sqrt( (xj-xk)*(xj-xk) + (yj-yk)*(yj-yk) + (zj-zk)*(zj-zk) );							
			double rkn = sqrt( (xk-xn)*(xk-xn) + (yk-yn)*(yk-yn) + (zk-zn)*(zk-zn) );
			double rni = sqrt( (xn-xi)*(xn-xi) + (yn-yi)*(yn-yi) + (zn-zi)*(zn-zi) );
#endif
			// гипотенуза
			double ci_j = /*rij **/ fabs(ri) / (fabs(ri) + fabs(rj));
			double ci_n = /*rin **/ fabs(ri) / (fabs(ri) + fabs(rn));
			double ci_k = /*rik **/ fabs(ri) / (fabs(ri) + fabs(rk));
			
			double cj_k = /*rjk **/ fabs(rj) / (fabs(rj) + fabs(rk));
			double ck_n = /*rkn **/ fabs(rk) / (fabs(rk) + fabs(rn));
			double cn_i = /*rni **/ fabs(rn) / (fabs(rn) + fabs(ri));


			double 
				// координаты точки пересечения плоскости и поверхности относительно листа
				// lxy,lz,
				// координаты точки пересечения плоскости и поверхности относительно куба
				x,y,z;
			CPoint3 v[4];

			CPoint3 vv[4];
			bool 
				doTri = false,
				// какие ребра пересекаются с плоскостью
				b1 = false,
				b2 = false,
				b3 = false,
				b4 = false
#if USE_UNVISIBLE_CUTTING
				,

				// какие видимые ребра пересекаются с плоскостью
				bv1 = false,
				bv2 = false,
				bv3 = false,
				bv4 = false
#endif		
				;

			int ivertex=0;
			int iv=0;

			// ищем точки пересечения рёбер с плоскостью			
			if( ri * rj <= 0.0
#if !USE_UNVISIBLE_CUTTING
				&& bi && bj
#endif
				)
			{
				x = xi + (xj-xi)*ci_j/*/rij*/;
				y = yi + (yj-yi)*ci_j/*/rij*/;
				z = zi + (zj-zi)*ci_j/*/rij*/;

				v[ivertex].x = x;
				v[ivertex].y = y;
				v[ivertex].z = z;
				ivertex++;

				vv[iv].x = x;
				vv[iv].y = y;
				vv[iv].z = z;						

				b1 = true;
#if USE_UNVISIBLE_CUTTING
				if (bi && bj)
				{
					bv1 = true;
				}
#endif
			}
			iv++;
			if( rj * rk <= 0.0
#if !USE_UNVISIBLE_CUTTING
				&& bj && bk
#endif
				)
			{
				x = xj + (xk-xj)*cj_k/*/rjk*/;
				y = yj + (yk-yj)*cj_k/*/rjk*/;
				z = zj + (zk-zj)*cj_k/*/rjk*/;

				v[ivertex].x = x;
				v[ivertex].y = y;
				v[ivertex].z = z;
				ivertex++;

				vv[iv].x = x;
				vv[iv].y = y;
				vv[iv].z = z;

				b2 = true;
#if USE_UNVISIBLE_CUTTING
				if (bj && bk)
				{
					bv2 = true;
				}
#endif
			}
			iv++;
			if( rk * rn <= 0.0
#if !USE_UNVISIBLE_CUTTING
				&& bk && bn
#endif
				)
			{
				x = xk + (xn-xk)*ck_n/*/rkn*/;
				y = yk + (yn-yk)*ck_n/*/rkn*/;
				z = zk + (zn-zk)*ck_n/*/rkn*/;

				v[ivertex].x = x;
				v[ivertex].y = y;
				v[ivertex].z = z;
				ivertex++;

				vv[iv].x = x;
				vv[iv].y = y;
				vv[iv].z = z;
				
				b3 = true;
#if USE_UNVISIBLE_CUTTING
				if (bk && bn)
				{
					bv3 = true;
				}
#endif
			}
			iv++;
			if( ri * rn <= 0.0
#if !USE_UNVISIBLE_CUTTING
				&& bi && bn
#endif
				)
			{
				x = xi + (xn-xi)*ci_n/*/rin*/;
				y = yi + (yn-yi)*ci_n/*/rin*/;
				z = zi + (zn-zi)*ci_n/*/rin*/;

				v[ivertex].x = x;
				v[ivertex].y = y;
				v[ivertex].z = z;
				ivertex++;
											
				vv[iv].x = x;
				vv[iv].y = y;
				vv[iv].z = z;
				
				b4 = true;
#if !USE_UNVISIBLE_CUTTING
				if (bi && bn)
				{
					bv4 = true;
				}
#endif
			}
			iv++;							

			double 
				A,
				B,
				C,
				D;

			double minx = xi;
			if (xj < minx) minx = xj;
			if (xk < minx) minx = xk;
			if (xn < minx) minx = xn;

			double maxx = xi;
			if (xj > maxx) maxx = xj;
			if (xk > maxx) maxx = xk;
			if (xn > maxx) maxx = xn;

			double miny = yi;
			if (yj < miny) miny = yj;
			if (yk < miny) miny = yk;
			if (yn < miny) miny = yn;

			double maxy = yi;
			if (yj > maxy) maxy = yj;
			if (yk > maxy) maxy = yk;
			if (yn > maxy) maxy = yn;

			double minz = zi;
			if (zj < minz) minz = zj;
			if (zk < minz) minz = zk;
			if (zn < minz) minz = zn;

			double maxz = zi;
			if (zj > maxz) maxz = zj;
			if (zk > maxz) maxz = zk;
			if (zn > maxz) maxz = zn;

//			bool find_point_projection = false;
			bool find_point_projection1 = false;
			bool find_point_projection2 = false;

/*			if (pt1 && !pt2)//если задан указатель 
				//только на одну лишь двумерную точку, 
				//значит нам требуется отыскать 
				//лишь проекцию этой точки на поверхность
			{
				find_point_projection = 
					pt1->x >= minx && 
					pt1->x <= maxx && 
					pt1->y >= miny && 
					pt1->y <= maxy ; 
			}*/

			if (pt1)//если задан указатель 
				//только на одну лишь двумерную точку, 
				//значит нам требуется отыскать 
				//лишь проекцию этой точки на поверхность
			{
				find_point_projection1 = 
					pt1->x >= minx && 
					pt1->x <= maxx && 
					pt1->y >= miny && 
					pt1->y <= maxy ; 
			}

			if (pt2)//если задан указатель 
				//только на одну лишь двумерную точку, 
				//значит нам требуется отыскать 
				//лишь проекцию этой точки на поверхность
			{
				find_point_projection2 = 
					pt2->x >= minx && 
					pt2->x <= maxx && 
					pt2->y >= miny && 
					pt2->y <= maxy ; 
			}
			if (ivertex || find_point_projection1 || find_point_projection2)
			{
				QuadSquareInterpolation(m_zflag,
					ptd[i],  
					ptd[j],  
					ptd[k],  
					ptd[n],  
					A,B,C,D);
			}
			QuadCutting quadCutting;
			quadCutting.bCutted = 0;
			quadCutting.nLines = 0;
			int quad = row_quad*nx + col_quad;			
			vQuadCutting.GetLastVect().GetLastMsg()[quad] = quadCutting;
			
			// i	n
			//
			// j	k
			if (bi && bj && bk && bn) 
			{
				if (type_of_cutline == 2 && m_zflag == 0)
				{
					if(find_point_projection1)
					{
						//printf("if(find_point_projection1)\n");
						CutTheQuad( 
#if USE_UNVISIBLE_CUTTING
							true,
#endif									
							cutting_number, surf_number, quad,A,B,C,D,pt1,1, pBrokenPlane);
					}
					if(find_point_projection2)
					{
						//printf("if(find_point_projection2)\n");
						CutTheQuad( 
#if USE_UNVISIBLE_CUTTING
							true,
#endif		
							cutting_number, surf_number, quad,A,B,C,D,pt2,2, pBrokenPlane);
					}
				}
			}
			if (ivertex)
			{
				// i |	n
				// -	-
				// j |	k
				if (b1 && b2 && b3 && b4) //ri * rj && rj * rk
				{

					QuadCutting quadCutting;
					quadCutting.bCutted = 2;
					quadCutting.nLines = 2;
					int quad = row_quad*nx + col_quad;			
					vQuadCutting.GetLastVect().GetLastMsg()[quad] = quadCutting;

					int npts = 4;
					vxyz.GetLastVect().GetLastMsg()[quad].resize(npts);
					for (int i = 0; i < npts; i++)
					{
						vxyz.GetLastVect().GetLastMsg()[quad][i] = vv[i];
#if USE_UNVISIBLE_CUTTING
						vxyz.GetLastVect().GetLastMsg()[quad][i].bVisible = bv1 && bv2 && bv3 && bv4;
#endif		
					}

				}
					
#if USE_UNVISIBLE_CUTTING
				bool bvisible = bi && bj && bk && bn;
#endif		
				Poligon3D * blank_polygon = NULL;
				if (blank_polygon_matrix 
					&& row_quad < (*blank_polygon_matrix).size() 
					&& col_quad < (*blank_polygon_matrix)[0].size()
					)
				{
					if ((*blank_polygon_matrix)[row_quad][col_quad])
					{
						blank_polygon = (*blank_polygon_matrix)[row_quad][col_quad];
					}
				}

				// i	n
				// -
				// j |	k	
				if (b1 && b2 && !b3 && !b4) //ri * rj && rj * rk
				{
					if(rj != 0.0)
					{
						if (
							positive && (rk < 0.0 && rn < 0.0 && ri < 0.0)
							||
							!positive && (rk > 0.0 && rn > 0.0 && ri > 0.0)
							)
						{
							vdouble 
								v_x(5),
								v_y(5),
								v_z(5);

							v_x[0] = vv[0].x;
							v_y[0] = vv[0].y;
							v_z[0] = vv[0].z;

							v_x[1] = vv[1].x;
							v_y[1] = vv[1].y;
							v_z[1] = vv[1].z;

							v_x[2] = xk;
							v_y[2] = yk;
							v_z[2] = zk;

							v_x[3] = xn;
							v_y[3] = yn;
							v_z[3] = zn;

							v_x[4] = xi;
							v_y[4] = yi;
							v_z[4] = zi;

							quadCutting.bCutted = 1;
							quadCutting.nLines = 1;
//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
							quadCutting.start_neighbour_row		= row_quad;
							quadCutting.start_neighbour_col		= col_quad-1;
//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
							quadCutting.finish_neighbour_row	= row_quad+1;
							quadCutting.finish_neighbour_col	= col_quad;

							if ((pt1 && pt2))
							{
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif											
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									max(minx, min_x), 
									min(maxx, max_x),
									max(miny, min_y),
									min(maxy, max_y),
									minz, maxz, 
									toDrawPoligones, cutplane_polygones);
							}
							else
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif	
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									minx, maxx, miny, maxy, minz, maxz, 
									toDrawPoligones, cutplane_polygones);
						}
						else
						{
							if (
								positive && (rj < 0.0)
								||
								!positive && (rj > 0.0)
								)

							{
								vdouble 
									v_x(3),
									v_y(3),
									v_z(3);

								v_x[0] = vv[0].x;
								v_y[0] = vv[0].y;
								v_z[0] = vv[0].z;

								v_x[1] = vv[1].x;
								v_y[1] = vv[1].y;
								v_z[1] = vv[1].z;

								v_x[2] = xj;
								v_y[2] = yj;
								v_z[2] = zj;

								quadCutting.bCutted = 1;
								quadCutting.nLines = 1;
//								quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
								quadCutting.start_neighbour_row		= row_quad;
								quadCutting.start_neighbour_col		= col_quad-1;
//								quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
								quadCutting.finish_neighbour_row	= row_quad+1;
								quadCutting.finish_neighbour_col	= col_quad;

								if ((pt1 && pt2))
								{
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif										
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										max(minx, min_x), 
										min(maxx, max_x),
										max(miny, min_y),
										min(maxy, max_y),
										minz, maxz, 
										toDrawPoligones, cutplane_polygones);
								}
								else
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										minx, maxx, miny, maxy, minz, maxz, 
										toDrawPoligones, cutplane_polygones);

							}
						}
					}
				}

				// i	n
				//		-
				// j |	k
				if (b2 && b3 && !b1 && !b4) // rj * rk && rk * rn
				{
					if(rk != 0.0)
					{
						if (positive && (rn < 0.0 && ri < 0.0 && rj < 0.0)
							||
							!positive && (rn > 0.0 && ri > 0.0 && rj > 0.0)
							)

						{
							vdouble 
								v_x(5),
								v_y(5),
								v_z(5);


							v_x[0] = vv[1].x;
							v_y[0] = vv[1].y;
							v_z[0] = vv[1].z;

							v_x[1] = vv[2].x;
							v_y[1] = vv[2].y;
							v_z[1] = vv[2].z;

							v_x[2] = xn;
							v_y[2] = yn;
							v_z[2] = zn;

							v_x[3] = xi;
							v_y[3] = yi;
							v_z[3] = zi;

							v_x[4] = xj;
							v_y[4] = yj;
							v_z[4] = zj;

							quadCutting.bCutted = 1;
							quadCutting.nLines = 1;
//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
							quadCutting.start_neighbour_row		= row_quad+1;
							quadCutting.start_neighbour_col		= col_quad;
//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
							quadCutting.finish_neighbour_row	= row_quad;
							quadCutting.finish_neighbour_col	= col_quad+1;

							if ((pt1 && pt2))
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
								
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									max(minx, min_x), 
									min(maxx, max_x),
									max(miny, min_y),
									min(maxy, max_y),
									minz, maxz, 
									toDrawPoligones, cutplane_polygones);
							else
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
								
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									minx, maxx, miny, maxy, minz, maxz, 
									toDrawPoligones, cutplane_polygones);
						}
						else
						{
							if  (positive && (rk < 0.0)
								||
								!positive && (rk > 0.0)
								)
							{
								vdouble 
									v_x(3),
									v_y(3),
									v_z(3);

								v_x[0] = vv[1].x;
								v_y[0] = vv[1].y;
								v_z[0] = vv[1].z;

								v_x[1] = vv[2].x;
								v_y[1] = vv[2].y;
								v_z[1] = vv[2].z;

								v_x[2] = xk;
								v_y[2] = yk;
								v_z[2] = zk;

								quadCutting.bCutted = 1;
								quadCutting.nLines = 1;
//								quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
								quadCutting.start_neighbour_row		= row_quad+1;
								quadCutting.start_neighbour_col		= col_quad;
//								quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
								quadCutting.finish_neighbour_row	= row_quad;
								quadCutting.finish_neighbour_col	= col_quad+1;

								if ((pt1 && pt2))
									CutTheQuad(
									
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										max(minx, min_x), 
										min(maxx, max_x),
										max(miny, min_y),
										min(maxy, max_y),
										minz, maxz, 
										toDrawPoligones, cutplane_polygones);
								else
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										minx, maxx, miny, maxy, minz, maxz, 
										toDrawPoligones, cutplane_polygones);
							}
						}
					}
				}

				// i |	n
				//		-
				// j	k
				if (b3 && b4 && !b1 && !b2) //rk * rn && ri * rn
				{
					if(rn != 0.0)
					{
						if (positive && (ri < 0.0 && rj < 0.0 && rk < 0.0)
							||
							!positive && (ri > 0.0 && rj > 0.0 && rk > 0.0)
							)
						{
							vdouble 
								v_x(5),
								v_y(5),
								v_z(5);


							v_x[0] = vv[2].x;
							v_y[0] = vv[2].y;
							v_z[0] = vv[2].z;

							v_x[1] = vv[3].x;
							v_y[1] = vv[3].y;
							v_z[1] = vv[3].z;

							v_x[2] = xi;
							v_y[2] = yi;
							v_z[2] = zi;

							v_x[3] = xj;
							v_y[3] = yj;
							v_z[3] = zj;

							v_x[4] = xk;
							v_y[4] = yk;
							v_z[4] = zk;

							quadCutting.bCutted = 1;
							quadCutting.nLines = 1;
//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
							quadCutting.start_neighbour_row		= row_quad;
							quadCutting.start_neighbour_col		= col_quad+1;
//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
							quadCutting.finish_neighbour_row	= row_quad-1;
							quadCutting.finish_neighbour_col	= col_quad;

							if ((pt1 && pt2))
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									max(minx, min_x), 
									min(maxx, max_x),
									max(miny, min_y),
									min(maxy, max_y),
									minz, maxz, 
									toDrawPoligones, cutplane_polygones);
							else
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
								
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									minx, maxx, miny, maxy, minz, maxz, 
									toDrawPoligones, cutplane_polygones);
						}
						else
						{
							if (positive && (rn < 0.0)
								||
								!positive && (rn > 0.0)
								)

							{
								vdouble 
									v_x(3),
									v_y(3),
									v_z(3);

								v_x[0] = vv[2].x;
								v_y[0] = vv[2].y;
								v_z[0] = vv[2].z;

								v_x[1] = vv[3].x;
								v_y[1] = vv[3].y;
								v_z[1] = vv[3].z;

								v_x[2] = xn;
								v_y[2] = yn;
								v_z[2] = zn;

								quadCutting.bCutted = 1;
								quadCutting.nLines = 1;
//								quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
								quadCutting.start_neighbour_row		= row_quad;
								quadCutting.start_neighbour_col		= col_quad+1;
//								quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
								quadCutting.finish_neighbour_row	= row_quad-1;
								quadCutting.finish_neighbour_col	= col_quad;

								if ((pt1 && pt2))
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
									
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										max(minx, min_x), 
										min(maxx, max_x),
										max(miny, min_y),
										min(maxy, max_y),
										minz, maxz, 
										toDrawPoligones, cutplane_polygones);
								else
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
									
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										minx, maxx, miny, maxy, minz, maxz, 
										toDrawPoligones, cutplane_polygones);
							}
						}
					}
				}

				// i  |	n
				// -
				// j	k
				if (b1 && b4 && !b2 && !b3) //ri * rj && ri * rn 
				{
					if(ri != 0.0)
					{
						if (positive && (rn < 0.0 && rk < 0.0 && rj < 0.0)
							||
							!positive && (rn > 0.0 && rk > 0.0 && rj > 0.0)
							)
						{
							vdouble 
								v_x(5),
								v_y(5),
								v_z(5);

							v_x[0] = vv[0].x;
							v_y[0] = vv[0].y;
							v_z[0] = vv[0].z;

							v_x[1] = vv[3].x;
							v_y[1] = vv[3].y;
							v_z[1] = vv[3].z;

							v_x[2] = xn;
							v_y[2] = yn;
							v_z[2] = zn;

							v_x[3] = xk;
							v_y[3] = yk;
							v_z[3] = zk;

							v_x[4] = xj;
							v_y[4] = yj;
							v_z[4] = zj;

							quadCutting.bCutted = 1;
							quadCutting.nLines = 1;
//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
							quadCutting.start_neighbour_row		= row_quad;
							quadCutting.start_neighbour_col		= col_quad-1;
//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
							quadCutting.finish_neighbour_row	= row_quad-1;
							quadCutting.finish_neighbour_col	= col_quad;

							if ((pt1 && pt2))
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									max(minx, min_x), 
									min(maxx, max_x),
									max(miny, min_y),
									min(maxy, max_y),
									minz, maxz, 
									toDrawPoligones, cutplane_polygones);
							else
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif										
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									minx, maxx, miny, maxy, minz, maxz, 
									toDrawPoligones, cutplane_polygones);
						}
						else
						{
							if (positive && (ri < 0.0)
								||
								!positive && (ri > 0.0)
								)
							{
								vdouble 
									v_x(3),
									v_y(3),
									v_z(3);

								v_x[0] = vv[0].x;
								v_y[0] = vv[0].y;
								v_z[0] = vv[0].z;

								v_x[1] = vv[3].x;
								v_y[1] = vv[3].y;
								v_z[1] = vv[3].z;

								v_x[2] = xi;
								v_y[2] = yi;
								v_z[2] = zi;

								quadCutting.bCutted = 1;
								quadCutting.nLines = 1;
//								quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
								quadCutting.start_neighbour_row		= row_quad;
								quadCutting.start_neighbour_col		= col_quad-1;
//								quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
								quadCutting.finish_neighbour_row	= row_quad-1;
								quadCutting.finish_neighbour_col	= col_quad;

								if ((pt1 && pt2))
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif										
									
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										max(minx, min_x), 
										min(maxx, max_x),
										max(miny, min_y),
										min(maxy, max_y),
										minz, maxz, 
										toDrawPoligones, cutplane_polygones);
								else
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif										
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										minx, maxx, miny, maxy, minz, maxz, 
										toDrawPoligones, cutplane_polygones);
							}
						}
					}
				}

				// i	n
				// -	-
				// j	k
				if (b1 && b3 && !b2 && !b4) // ri * rj && rk * rn
				{
					if(true)
					{
						if (positive && (rk < 0.0 && rj < 0.0 )
							||
							!positive && (rk > 0.0 && rj > 0.0 )
							)
						{
							vdouble 
								v_x(4),
								v_y(4),
								v_z(4);

							v_x[0] = vv[0].x;
							v_y[0] = vv[0].y;
							v_z[0] = vv[0].z;

							v_x[1] = vv[2].x;
							v_y[1] = vv[2].y;
							v_z[1] = vv[2].z;

							v_x[2] = xk;
							v_y[2] = yk;
							v_z[2] = zk;

							v_x[3] = xj;
							v_y[3] = yj;
							v_z[3] = zj;

							quadCutting.bCutted = 1;
							quadCutting.nLines = 1;
//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
							quadCutting.start_neighbour_row		= row_quad;
							quadCutting.start_neighbour_col		= col_quad-1;
//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
							quadCutting.finish_neighbour_row	= row_quad;
							quadCutting.finish_neighbour_col	= col_quad+1;

							if ((pt1 && pt2))
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif										
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									max(minx, min_x), 
									min(maxx, max_x),
									max(miny, min_y),
									min(maxy, max_y),
									minz, maxz, 
									toDrawPoligones, cutplane_polygones);
							else
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif										
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									minx, maxx, miny, maxy, minz, maxz, 
									toDrawPoligones, cutplane_polygones);
						}
						else
						{
							if (positive && (rn < 0.0 && ri < 0.0 )
								||
								!positive && (rn > 0.0 && ri > 0.0 )
								)
							{
								vdouble 
									v_x(4),
									v_y(4),
									v_z(4);

								v_x[0] = vv[0].x;
								v_y[0] = vv[0].y;
								v_z[0] = vv[0].z;

								v_x[1] = vv[2].x;
								v_y[1] = vv[2].y;
								v_z[1] = vv[2].z;

								v_x[2] = xn;
								v_y[2] = yn;
								v_z[2] = zn;

								v_x[3] = xi;
								v_y[3] = yi;
								v_z[3] = zi;

								quadCutting.bCutted = 1;
								quadCutting.nLines = 1;
//								quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
								quadCutting.start_neighbour_row		= row_quad;
								quadCutting.start_neighbour_col		= col_quad-1;
//								quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
								quadCutting.finish_neighbour_row	= row_quad;
								quadCutting.finish_neighbour_col	= col_quad+1;

								if ((pt1 && pt2))
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif										
									
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										max(minx, min_x), 
										min(maxx, max_x),
										max(miny, min_y),
										min(maxy, max_y),
										minz, maxz, 
										toDrawPoligones, cutplane_polygones);
								else
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif										
									
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										minx, maxx, miny, maxy, minz, maxz, 
										toDrawPoligones, cutplane_polygones);
							}
						}
					}
				}

				// i |	n
				//
				// j |	k	
				if (b2 && b4 && !b1 && !b3) // rj * rk && ri * rn
				{
					if(true)
					{
						if (positive && (ri < 0.0 && rj < 0.0 )
							||
							!positive && (ri > 0.0 && rj > 0.0 )
							)
						{
							vdouble 
								v_x(4),
								v_y(4),
								v_z(4);


							v_x[0] = vv[1].x;
							v_y[0] = vv[1].y;
							v_z[0] = vv[1].z;

							v_x[1] = vv[3].x;
							v_y[1] = vv[3].y;
							v_z[1] = vv[3].z;

							v_x[2] = xi;
							v_y[2] = yi;
							v_z[2] = zi;

							v_x[3] = xj;
							v_y[3] = yj;
							v_z[3] = zj;

							quadCutting.bCutted = 1;
							quadCutting.nLines = 1;
//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
							quadCutting.start_neighbour_row		= row_quad+1;
							quadCutting.start_neighbour_col		= col_quad;
//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
							quadCutting.finish_neighbour_row	= row_quad-1;
							quadCutting.finish_neighbour_col	= col_quad;

							if ((pt1 && pt2))
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									max(minx, min_x), 
									min(maxx, max_x),
									max(miny, min_y),
									min(maxy, max_y),
									minz, maxz, 
									toDrawPoligones, cutplane_polygones);
							else
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									bvisible, blank_polygon,
#endif		
									quadCutting, quad, a, b, c, d, A, B, C, D, 
									v_x, v_y, v_z, 
									minx, maxx, miny, maxy, minz, maxz, 
									toDrawPoligones, cutplane_polygones);
						}
						else
						{
							if (positive && (rn < 0.0 && rk < 0.0 )
								||
								!positive && (rn > 0.0 && rk > 0.0 )
								)
							{
								vdouble 
									v_x(4),
									v_y(4),
									v_z(4);

								v_x[0] = vv[1].x;
								v_y[0] = vv[1].y;
								v_z[0] = vv[1].z;

								v_x[1] = vv[3].x;
								v_y[1] = vv[3].y;
								v_z[1] = vv[3].z;

								v_x[2] = xn;
								v_y[2] = yn;
								v_z[2] = zn;

								v_x[3] = xk;
								v_y[3] = yk;
								v_z[3] = zk;

								quadCutting.bCutted = 1;
								quadCutting.nLines = 1;
//								quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
								quadCutting.start_neighbour_row		= row_quad+1;
								quadCutting.start_neighbour_col		= col_quad;
//								quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
								quadCutting.finish_neighbour_row	= row_quad-1;
								quadCutting.finish_neighbour_col	= col_quad;

								if ((pt1 && pt2))
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										max(minx, min_x), 
										min(maxx, max_x),
										max(miny, min_y),
										min(maxy, max_y),
										minz, maxz, 
										toDrawPoligones, cutplane_polygones);
								else
									CutTheQuad(
#if USE_UNVISIBLE_CUTTING
										bvisible, blank_polygon,
#endif		
										quadCutting, quad, a, b, c, d, A, B, C, D, 
										v_x, v_y, v_z, 
										minx, maxx, miny, maxy, minz, maxz, 
										toDrawPoligones, cutplane_polygones);
							}
						}
					}
				}
			}
		}
	}
	if (toDrawPoligones && cutplane_polygones_ObjectList && pGeoSurface)
		cutplane_polygones_ObjectList->Init(*cutplane_polygones, pGeoSurface);
}



void Surface3D::CutTheQuad( 
#if USE_UNVISIBLE_CUTTING
						 bool bvisible,
#endif		
						   
						   UINT cutting_number, UINT surf_number, UINT quad,
						 double A, double B, double C, double D, 
						 CPoint2 *pt2, int pt_number, void * pBrokenPlane)
{
//printf("CutTheQuad 0 !!!!!!!!!!!!!!!!!! \n");
	CPoint3 pt;
	double X,Y,Z;
	X = pt2->x;
	Y = pt2->y;
	Z = A*X*Y + B*X + C*Y + D;

	pt.bVisible = true;
	pt.x = X;
	pt.y = Y;
	pt.z = Z;

	// первый индекс - номер промежутка между скважинами
	// второй индекс - номер поверхности
	if (pBrokenPlane)
	{
		switch(pt_number)
		{
		case 1:
			{
				//((BrokenPlane3D *) pBrokenPlane)->m_pointsDrillSloi[cutting_number][surf_number].Init(this, pt);
				((BrokenPlane3D *) pBrokenPlane)->InitPoint(this->m_pSurfDoc, cutting_number, surf_number, pt);
			}
			break;
		case 2:
			{
				//((BrokenPlane3D *) pBrokenPlane)->m_pointsDrillSloi[cutting_number+1][surf_number].Init(this, pt);
				((BrokenPlane3D *) pBrokenPlane)->InitPoint(this->m_pSurfDoc, cutting_number+1, surf_number, pt);
			}
			break;
		}
	}
//printf("CutTheQuad end!!!!!!!!!!!!!!!!!!\n");
}


#include "../../geometry2D/Point.h"
#include "../../geometry2D/Vertex.h"
#include "../../geometry2D/Edge.h"
#include "../../geometry2D/Polygon.h"
#include "../../geometry2D/PolygonEx.h"
#include "../../geometry2D/List.h"
#include "../../geometry2D/delaunay.h"
#include "../../geometry2D/belong.h"

#define INSIDE_ONLY 1

void Surface3D::CutTheQuad(
#if USE_UNVISIBLE_CUTTING
							bool bvisible, Poligon3D * blank_polygon,
#endif								   
							QuadCutting& quadCutting, UINT quad,
							double a, double b, double c, double d, 
							double A, double B, double C, double D, 
							vdouble &v_x, vdouble &v_y, vdouble &v_z, 
							double minx, double maxx, 
							double miny, double maxy, 
							double minz, double maxz, 
							bool toDrawPolygon, 
							vect<Poligon3D> * cutplane_polygones)
{
	double epsilon = 0.000001;
	int len = v_x.Length();
	double 
		distance3_0,
		distance2_1;
	bool use2as1;
	double X,Y,Z;

	if (len == 4)
	{
		distance3_0 = sqrt(
			(v_x[3] - v_x[0])*(v_x[3] - v_x[0]) +
			(v_y[3] - v_y[0])*(v_y[3] - v_y[0]) +
			(v_z[3] - v_z[0])*(v_z[3] - v_z[0]) 
			);
		distance2_1 = sqrt(
			(v_x[2] - v_x[1])*(v_x[2] - v_x[1]) +
			(v_y[2] - v_y[1])*(v_y[2] - v_y[1]) +
			(v_z[2] - v_z[1])*(v_z[2] - v_z[1]) 
			);
		use2as1 = distance2_1 > distance3_0;
	}


	if (toDrawPolygon && cutplane_polygones && bvisible)
	{
		Poligon3D poly(this->m_pSurfDoc);
		cutplane_polygones->AddMsg(&poly);
		cutplane_polygones->GetLastMsg().Init( (Surface3D *) this);
		cutplane_polygones->GetLastMsg().SetColor(m_color);
		switch(len)
		{
		case 3:
			{
				// first point of polygon	
				CPoint3 pt;
				pt.bVisible = true;
				pt.x = v_x[2];
				pt.y = v_y[2];
				pt.z = v_z[2];
				cutplane_polygones->GetLastMsg().PushBack(pt);
				pt.x = v_x[0];
				pt.y = v_y[0];
				pt.z = v_z[0];
				cutplane_polygones->GetLastMsg().PushBack(pt);
			}
			break;
		case 4:
			{
				// first point of polygon	
				CPoint3 pt;
				pt.bVisible = true;
				if (use2as1)
				{
					pt.x = v_x[2];
					pt.y = v_y[2];
					pt.z = v_z[2];
					cutplane_polygones->GetLastMsg().PushBack(pt);
				}
				pt.x = v_x[3];
				pt.y = v_y[3];
				pt.z = v_z[3];
				cutplane_polygones->GetLastMsg().PushBack(pt);
				pt.x = v_x[0];
				pt.y = v_y[0];
				pt.z = v_z[0];	
				cutplane_polygones->GetLastMsg().PushBack(pt);
			}
			break;
		case 5:
			{
				// first point of polygon	
				CPoint3 pt;
				pt.bVisible = true;
				pt.x = v_x[3];
				pt.y = v_y[3];
				pt.z = v_z[3];
				cutplane_polygones->GetLastMsg().PushBack(pt);
				pt.x = v_x[4];
				pt.y = v_y[4];
				pt.z = v_z[4];
				cutplane_polygones->GetLastMsg().PushBack(pt);
				pt.x = v_x[0];
				pt.y = v_y[0];
				pt.z = v_z[0];
				cutplane_polygones->GetLastMsg().PushBack(pt);
			}
			break;
		}
	}
	//НАЧИНАЕМ ФОРМИРОВАНИЕ ВЕКТОРА ТОЧЕК СЕЧЕНИЯ ТЕКУЩЕЙ КЛЕТКИ




	vQuadCutting.GetLastVect().GetLastMsg()[quad] = quadCutting;

	CPoint3 pt;
	pt.flag |= CPOINT3_FLAG_NONORMAL;
	vect <CPoint3> vpt3;
	vpt3.OnCreate(0);


	//int sign;
	double step;
	//int N = 4;

	// если это включить, то появляется деффект при изображении полигонов
	bool fill_polygon = bvisible;
//	bool fill_polygon = false;


	if (m_zflag == 0)
	{
		geometry2D::Polygon p;
		if (blank_polygon)
		{
			for (int i = 0; i < blank_polygon->GetPointsNumber(); ++i)
			{
				p.insert(geometry2D::Point(
					blank_polygon->GetDocumentPoint(i).x,
					blank_polygon->GetDocumentPoint(i).y,
					i)
				);
			}
		}



		if (fabs(v_x[1]-v_x[0]) >= fabs(v_y[1]-v_y[0]) )
		{
			//sign = v_x[1] < v_x[0] ? -1 : +1;
			//step = sign*(maxx - minx) / N;
			step = (v_x[1] - v_x[0]) / m_N_quad;
			for (int ix = 0; ix <= m_N_quad; ix++)
			{			 
				X = v_x[0]+step*(ix+1);

				Y = - ((B*c+a)*X + (D*c+d))/((A*c)*X + (C*c+b));
				Z = A*X*Y + B*X + C*Y + D;
				if (X >= minx && 
					X <= maxx && 
					Y >= miny && 
					Y <= maxy && 
					Z >= minz && Z <= maxz)
				{
					geometry2D::Point a(X,Y);
					if ( p.size() > 0 )
					{
						int result = pointInPolygon(a, p);
						if (result == geometry2D::INSIDE
#if INSIDE_ONLY
							|| result == geometry2D::BOUNDARY
#endif
							)
							pt.bVisible = true;
						else
							pt.bVisible = false;
					}
					else
						pt.bVisible = true;

					
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.AddMsg(&pt);
					//AddSphere(X,Y,Z,RGB(255,0,0));
					if (fill_polygon && toDrawPolygon && cutplane_polygones)
					{
						// interpolated points of polygon	
						cutplane_polygones->GetLastMsg().PushBack(pt);
					}
				}
			}
		}
		else
		{
			//sign = v_y[1] < v_y[0] ? -1 : +1;
			//step = sign*(maxy - miny) / N;
			step = (v_y[1] - v_y[0]) / m_N_quad;
			for (int iy = 0; iy <= m_N_quad; iy++)
			{
				Y = v_y[0]+step*(iy+1);


				X = - ((C*c+b)*Y + (D*c+d))/((A*c)*Y + (B*c+a));
				Z = A*X*Y + B*X + C*Y + D;
				if (X >= minx &&
					X <= maxx && 
					Y >= miny && 
					Y <= maxy && 
					Z >= minz && 
					Z <= maxz)
				{
					geometry2D::Point a(X,Y);
					if ( p.size() > 0 )
					{
						int result = pointInPolygon(a, p);
						if (result == geometry2D::INSIDE
#if INSIDE_ONLY
							|| result == geometry2D::BOUNDARY
#endif
							)
							pt.bVisible = true;
						else
							pt.bVisible = false;
					}
					else
					{
						pt.bVisible = true;
					}

					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.AddMsg(&pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
					if (fill_polygon && toDrawPolygon && cutplane_polygones)
					{
						// interpolated points of polygon	
						cutplane_polygones->GetLastMsg().PushBack(pt);
					}
				}
			}
		}
	}

	if (m_zflag == 1)
	{
		geometry2D::Polygon p;
		if (blank_polygon)
		{
			for (int i = 0; i < blank_polygon->GetPointsNumber(); ++i)
			{
				p.insert(geometry2D::Point(
					blank_polygon->GetDocumentPoint(i).z,
					blank_polygon->GetDocumentPoint(i).y,
					i)
				);
			}
		}

		if (fabs(v_z[1]-v_z[0]) >= fabs(v_y[1]-v_y[0]) )
		{
			//sign = v_z[1] < v_z[0] ? -1 : +1;
			//step = sign*(maxx - minx) / N;
			step = (v_z[1] - v_z[0]) / m_N_quad;
			for (int iz = 0; iz <= m_N_quad; iz++)
			{			 
				Z = v_z[0]+step*(iz+1);
				Y = - ((B*a+c)*Z + (D*a+d))/((A*a)*Z + (C*a+b));
				X = A*Z*Y + B*Z + C*Y + D;

				if (X >= minx && 
					X <= maxx && 
					Y >= miny && 
					Y <= maxy && 
					Z >= minz && 
					Z <= maxz)
				{
					geometry2D::Point a(Z, Y);
					if (p.size() > 0)
					{
						int result = pointInPolygon(a, p);
						if (result == geometry2D::INSIDE
#if INSIDE_ONLY
							|| result == geometry2D::BOUNDARY
#endif
							)
							pt.bVisible = true;
						else
							pt.bVisible = false;
					}
					else
						pt.bVisible = true;

					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.AddMsg(&pt);
					//AddSphere(X,Y,Z,RGB(255,0,0));
					if (fill_polygon && toDrawPolygon && cutplane_polygones)
					{
						// interpolated points of polygon	
						cutplane_polygones->GetLastMsg().PushBack(pt);
					}
				}
			}
		}
		else
		{
			//sign = v_y[1] < v_y[0] ? -1 : +1;
			//step = sign*(maxy - miny) / N;
			step = (v_y[1] - v_y[0]) / m_N_quad;
			for (int iy = 0; iy <= m_N_quad; iy++)
			{
				Y = v_y[0]+step*(iy+1);
				Z = - ((C*a+b)*Y + (D*a+d))/((A*a)*Y + (B*a+c));
				X = A*Z*Y + B*Z + C*Y + D;

				if (X >= minx &&
					X <= maxx && 
					Y >= miny && 
					Y <= maxy && 
					Z >= minz && 
					Z <= maxz)
				{
					geometry2D::Point a(Z, Y);
					if ( p.size() )
					{
						int result = pointInPolygon(a, p);
						if (result == geometry2D::INSIDE 
#if INSIDE_ONLY
							|| result == geometry2D::BOUNDARY
#endif
							)
							pt.bVisible = true;
						else
							pt.bVisible = false;
					}
					else
					{
						pt.bVisible = true;
					}

					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.AddMsg(&pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
					if (fill_polygon && toDrawPolygon && cutplane_polygones)
					{
						// interpolated points of polygon	
						cutplane_polygones->GetLastMsg().PushBack(pt);
					}
				}
			}
		}
	}

	if (m_zflag == 2)
	{
		geometry2D::Polygon p;
		if (blank_polygon)
		{
			for (int i = 0; i < blank_polygon->GetPointsNumber(); ++i)
			{
				p.insert(geometry2D::Point(
					blank_polygon->GetDocumentPoint(i).x,
					blank_polygon->GetDocumentPoint(i).z,
					i)
				);
			}
		}
		if (fabs(v_x[1]-v_x[0]) >= fabs(v_z[1]-v_z[0]) )
		{
			//sign = v_x[1] < v_x[0] ? -1 : +1;
			//step = sign*(maxx - minx) / N;
			step = (v_x[1] - v_x[0]) / m_N_quad;
			for (int ix = 0; ix <= m_N_quad; ix++)
			{			 
				X = v_x[0]+step*(ix+1);
				Z = - ((B*b+a)*X + (D*b+d))/((A*b)*X + (C*b+c));
				Y = A*X*Z + B*X + C*Z + D;

				if (X >= minx && 
					X <= maxx && 
					Y >= miny && 
					Y <= maxy && 
					Z >= minz && Z <= maxz)
				{
					geometry2D::Point a(X, Z);
					if ( p.size() )
					{
						int result = pointInPolygon(a, p);
						if (result == geometry2D::INSIDE 
#if INSIDE_ONLY
							|| result == geometry2D::BOUNDARY
#endif
							)
							pt.bVisible = true;
						else
							pt.bVisible = false;
					}
					else
					{
						pt.bVisible = true;
					}

					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.AddMsg(&pt);
					//AddSphere(X,Y,Z,RGB(255,0,0));
					if (fill_polygon && toDrawPolygon && cutplane_polygones)
					{
						// interpolated points of polygon	
						cutplane_polygones->GetLastMsg().PushBack(pt);
					}
				}
			}
		}
		else
		{
			//sign = v_z[1] < v_z[0] ? -1 : +1;
			//step = sign*(maxy - miny) / N;
			step = (v_z[1] - v_z[0]) / m_N_quad;
			for (int iz = 0; iz <= m_N_quad; iz++)
			{
				Z = v_z[0]+step*(iz+1);
				X = - ((C*b+c)*Z + (D*b+d))/((A*b)*Z + (B*b+a));
				Y = A*X*Z + B*X + C*Z + D;

				if (X >= minx &&
					X <= maxx && 
					Y >= miny && 
					Y <= maxy && 
					Z >= minz && 
					Z <= maxz)
				{
					geometry2D::Point a(X, Z);
					if ( p.size() )
					{
						int result = pointInPolygon(a, p);
						if (result == geometry2D::INSIDE 
#if INSIDE_ONLY
							|| result == geometry2D::BOUNDARY
#endif
							)
							pt.bVisible = true;
						else
							pt.bVisible = false;
					}
					else
					{
						pt.bVisible = true;
					}

					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.AddMsg(&pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
					if (fill_polygon && toDrawPolygon && cutplane_polygones)
					{
						// interpolated points of polygon	
						cutplane_polygones->GetLastMsg().PushBack(pt);
					}
				}
			}
		}
	}

	int npts = vpt3.msgSize();
//printf("CutTheQuad npts = %d\n", npts);
	int i = 0;
	if (vpt3.SetCurrentMsgOnFirst() )
	{
		vxyz.GetLastVect().GetLastMsg()[quad].resize(npts);
		do 
		{
			vxyz.GetLastVect().GetLastMsg()[quad][i] = vpt3.GetCurrentMsg();
			if (!blank_polygon)
			{
				vxyz.GetLastVect().GetLastMsg()[quad][i].bVisible = bvisible;
			}
			i++;
		}
		while (vpt3.IncrementCurrentMsg());//  && i < npts);
	}
	vpt3.clear();

	if (toDrawPolygon && cutplane_polygones && bvisible)
	{
		switch(len)
		{
		case 3:
			{
				// last points of polygon	
				CPoint3 pt;
				for(int i = 1; i <= 1; i++)
				{
					pt.bVisible = true;
					pt.x = v_x[i];
					pt.y = v_y[i];
					pt.z = v_z[i];
					cutplane_polygones->GetLastMsg().PushBack(pt);
				}
			}
			break;
		case 4:
			{
				// last points of polygon	
				CPoint3 pt;
				for(int i = 1; i <= (use2as1 ? 1 : 2); i++)
				{
					pt.bVisible = true;
					pt.x = v_x[i];
					pt.y = v_y[i];
					pt.z = v_z[i];
					cutplane_polygones->GetLastMsg().PushBack(pt);
				}
			}
			break;
		case 5:
			{
				// last points of polygon	
				CPoint3 pt;
				for(int i = 1; i <= 2; i++)
				{
					pt.bVisible = true;
					pt.x = v_x[i];
					pt.y = v_y[i];
					pt.z = v_z[i];
					cutplane_polygones->GetLastMsg().PushBack(pt);
				}
			}
			break;
		}
	}
}


double Surface3D::FindCuttingOfSurfaceEdgesWithBlankLine(
	int line_number,
	Line3D& blankline, 
	bool to_continue_line_to_borders, 
	vector<surf_edge>* vse_gor, 
	vector<surf_edge>* vse_ver,
	size_t nx,
	size_t ny,
	double x00,
	double y00,

	double x0n,
	double y0n,

	double xn0,
	double yn0,

	double xnn,
	double ynn,
	
	//размер площадки в метрах
	double Dx,
	double Dy,

	//длина ребра клетки в долях единицы
	double dx_dc,
	double dx_dr,

	double dy_dc,
	double dy_dr
	)
{
	//bool test = true;
	bool test = false;
//***********************************************************************
	bool closed_blankline = 
		blankline.GetFirstDocumentPoint().x == blankline.GetLastDocumentPoint().x &&
		blankline.GetFirstDocumentPoint().y == blankline.GetLastDocumentPoint().y &&
		blankline.GetFirstDocumentPoint().z == blankline.GetLastDocumentPoint().z
		;	

	size_t blanklen = blankline.GetPointsNumber();

	(*vse_gor).resize(this->m_leny*nx);
	(*vse_ver).resize(ny*this->m_lenx);

	// координаты точек линии бланкования в долях единицы
	vector<double> vdx, vdy;
	vdx.resize(blanklen);
	vdy.resize(blanklen);
	switch(this->m_zflag)
	{
	case 0:
		{
			for (size_t i = 0; i < blanklen; i++)
			{
				CPoint3 pt = blankline.GetDocumentPoint(i);
				// координата точки линии бланкования в долях единицы
				vdx[i] = (pt.x-x00)/(xnn-x00);
				vdy[i] = (pt.y-y00)/(ynn-y00);
			}
		}
		break;
	case 1:
		{
			for (size_t i = 0; i < blanklen; i++)
			{
				CPoint3 pt = blankline.GetDocumentPoint(i);
				// координата точки линии бланкования в долях единицы
				vdx[i] = (pt.z-x00)/(xnn-x00);
				vdy[i] = (pt.y-y00)/(ynn-y00);
			}
		}
		break;
	case 2:
		{
			for (size_t i = 0; i < blanklen; i++)
			{
				CPoint3 pt = blankline.GetDocumentPoint(i);
				// координата точки линии бланкования в долях единицы
				vdx[i] = (pt.x-x00)/(xnn-x00);
				vdy[i] = (pt.z-y00)/(ynn-y00);
			}
		}
		break;
	}

	double distance_from_start_of_line_for_r1_c1 = 0;

	for (size_t i = 0; i < blanklen - 1; i++)
	{		
		//координата точки бланкования в индексах поверхности
		//r = dx_dr == 0.0 ? dy / dy_dr : dx / dx_dr;
		//c = dx_dc == 0.0 ? dy / dy_dc : dx / dx_dc;
		double r1,c1,r2,c2;
		r1 = dx_dr == 0.0 ? vdy[i] / dy_dr : vdx[i] / dx_dr;
		c1 = dx_dc == 0.0 ? vdy[i] / dy_dc : vdx[i] / dx_dc;

		r2 = dx_dr == 0.0 ? vdy[i+1] / dy_dr : vdx[i+1] / dx_dr;
		c2 = dx_dc == 0.0 ? vdy[i+1] / dy_dc : vdx[i+1] / dx_dc;

		double cut_len = sqrt((r2-r1)*(r2-r1) + (c2-c1)*(c2-c1));

		// ищем те рёбра которые пересекаются отрезком заданным в этих двух точках		
		// blanking(double r1, double c1, double r2, double c2)

		double minr = min(r1,r2);
		double maxr = max(r1,r2);

		double minc = min(c1,c2);
		double maxc = max(c1,c2);

		// с нулевым индексом номера первого и последнего пересекаемого ребра 
		// нужны нам для того, чтобы обозначить отличие собственно линии бланкования 
		// от её продолжения прямой линией это нам нужно, чтобы на продолжении линии 
		// бланкования не строить полигонов 

		double
			// номер первого пересекаемого ребра
			/*r_start_0 = */r_start = ceil(minr), // vertical
			/*c_ctart_0 = */c_start = ceil(minc), // gorizontal
			// номер последнего пересеаемого ребра
			/*r_end_0 = */r_end = floor(maxr), // vertical
			/*c_end_0 = */c_end = floor(maxc); // gorizontal

		double delta_c = c2-c1;
		double delta_r = r2-r1;
		
		bool this_is_continue_line = false;

		if (to_continue_line_to_borders && !closed_blankline)
		{
			if (i == 0)
			{
				if (r1<r2)
					r_start = 0;
				else
					r_end = ny;

				if (c1<c2)
					c_start = 0;
				else
					c_end = nx;

				this_is_continue_line = true;
			}
			if (i == int(blanklen)-2)
			{
				if (r2<r1)
					r_start = 0;
				else
					r_end = ny;

				if (c2<c1)
					c_start = 0;
				else
					c_end = nx;

				this_is_continue_line = true;
			}
		}

		for (double r = r_start; r<=r_end; r+=1.0)
		{
			if (delta_r == 0.0)
			{
				//уникальный случай, когда 
				//линия бланкования совпадает 
				//с ребром на участке от minc до maxc - 
				//горизонтальное совпадение
				MessageBox(0, "delta_r == 0.0", "Blank",0);
			}
			else
			{
				double c = c1+(r-r1)*delta_c/delta_r;
				//printf("r = %f\tc = %f\n",r,c);
				if (r >= 0.0 && r < this->m_leny
					&& c >=0.0 && c < nx)
				{
					//vse_gor.resize(this->m_leny*nx);
					size_t j = int(r)*nx + int(c);
					double x = x00+Dx*(c*dx_dc+r*dx_dr);
					double y = y00+Dy*(c*dy_dc+r*dy_dr);
//					vse_gor[j].bCutted++;
//					vse_gor[j].x = x;
//					vse_gor[j].y = y;
							


					surf_edge::edge_cutting ec;
					ec.x = x;
					ec.y = y;
					ec.r = r;
					ec.c = c;
					ec.line_number = line_number;
					ec.line_point_number1 = i;
					ec.line_point_number2 = i+1;

					ec.this_is_continue_line = this_is_continue_line;

					if (delta_r > 0.0)
						ec.m_cutDirectionOfLine = surf_edge::edge_cutting::up;
					else
						ec.m_cutDirectionOfLine = surf_edge::edge_cutting::down;
										
					//*************************************************************
					double len_rc_r1c1 = sqrt((r-r1)*(r-r1) + (c-c1)*(c-c1));
					if (to_continue_line_to_borders && !closed_blankline && i == 0)
					{
						double len_rc_r2c2 = sqrt((r-r2)*(r-r2) + (c-c2)*(c-c2));
						if(len_rc_r2c2 > cut_len)
						{
							ec.distance_from_start_of_line = 
								distance_from_start_of_line_for_r1_c1 - len_rc_r1c1;
						}
						else
						{
							ec.distance_from_start_of_line = 
								distance_from_start_of_line_for_r1_c1 + len_rc_r1c1;
						}
					}
					else
					{
						ec.distance_from_start_of_line = 
							distance_from_start_of_line_for_r1_c1 + len_rc_r1c1;
					}
					//*************************************************************
					(*vse_gor)[j].vec.push_back(ec);

					if (test)
					{
						//printf("vse_gor[j].vec.back().x = %f vse_gor[j].vec.back().y = %f\n",vse_gor[j].x,vse_gor[j].y);
						CPoint3 projection_pt;
						double r;
						if(this->Projection((*vse_gor)[j].vec.back().x, (*vse_gor)[j].vec.back().y, 0.0, r, &projection_pt))
						{
							this->m_pSurfDoc->AddSphere(projection_pt,0.0);
						}	
					}
				}
			}
		}

		for (double c = c_start; c<=c_end; c+=1.0)
		{
			if (delta_c == 0.0)
			{
				//уникальный случай, когда 
				//линия бланкования совпадает 
				//с ребром на участке от minc до maxc - 
				//горизонтальное совпадение
				MessageBox(0, "delta_c == 0.0", "Blank",0);
			}
			else
			{
				double r = r1+(c-c1)*delta_r/delta_c;
				//printf("r = %f\tc = %f\n",r,c);
				if (r >= 0.0 && r < ny
					&& c >=0.0 && c < this->m_lenx)
				{
					//vse_ver.resize(ny*this->m_lenx);
					size_t j = int(r)*this->m_lenx + int(c);
					double x = x00+Dx*(c*dx_dc+r*dx_dr);
					double y = y00+Dy*(c*dy_dc+r*dy_dr);
//					vse_ver[j].bCutted++;

//					vse_ver[j].x = x;
//					vse_ver[j].y = y;

					surf_edge::edge_cutting ec;
					ec.x = x;
					ec.y = y;
					ec.r = r;
					ec.c = c;
					ec.line_number = line_number;
					ec.line_point_number1 = i;
					ec.line_point_number2 = i+1;

					ec.this_is_continue_line = this_is_continue_line;

					if (delta_c > 0.0)
						ec.m_cutDirectionOfLine = surf_edge::edge_cutting::right;
					else
						ec.m_cutDirectionOfLine = surf_edge::edge_cutting::left;

					//*************************************************************
					double len_rc_r1c1 = sqrt((r-r1)*(r-r1) + (c-c1)*(c-c1));
					if (to_continue_line_to_borders && !closed_blankline && i == 0)
					{
						double len_rc_r2c2 = sqrt((r-r2)*(r-r2) + (c-c2)*(c-c2));
						if(len_rc_r2c2 > cut_len)
						{
							ec.distance_from_start_of_line = 
								distance_from_start_of_line_for_r1_c1 - len_rc_r1c1;
						}
						else
						{
							ec.distance_from_start_of_line = 
								distance_from_start_of_line_for_r1_c1 + len_rc_r1c1;
						}
					}
					else
					{
						ec.distance_from_start_of_line = 
							distance_from_start_of_line_for_r1_c1 + len_rc_r1c1;
					}
					//*************************************************************
					(*vse_ver)[j].vec.push_back(ec);
					if (test)
					{
						//printf("vse_ver[j].vec.back().x = %f vse_ver[j].vec.back().y = %f\n",vse_ver[j].vec.back().x,vse_ver[j].vec.back().y);
						CPoint3 projection_pt;
						double r;
						if(this->Projection((*vse_ver)[j].vec.back().x, (*vse_ver)[j].vec.back().y, 0.0, r, &projection_pt))
						{
							this->m_pSurfDoc->AddSphere(projection_pt,0.0);
						}
					}
				}
			}
		}
		distance_from_start_of_line_for_r1_c1 += cut_len;
	}
	return distance_from_start_of_line_for_r1_c1;
    //***********************************************************************
}
bool Surface3D::DetermineVisibleFlagOfFirstGridPoint(
	Line3D& blankline,
	CPoint3 * base_point,
	double x00,
	double y00,
	bool& bVisible00
)
{
	printf ("DetermineVisibleFlagOfFirstGridPoint\n");
//	int inside = blankline.m_lParam & OBJECT_FLAG_INSIDE_BLANK_BIT ? 0 : 1;
//	printf ("inside = %d\n", inside);
	// inside
	// 0 - inside is visible
	// 1 - outside is visible

	// start visible flag bVisible - the visible flag of first point
	// false - the first point is outside
	// true  - the first point is inside
	// изначально мы думаем, что точка 00 лежит вне контура линии бланкования
	// поэтому если инсайд == 0, что означает нужно внтри онтура сделать видимой
	// то мы точку делаем невидимой
//	bVisible00 = !(inside == 0);
	// now we must test where is the first point
	// inside or outside of blank contour
	bool closed_blankline = 
		blankline.GetFirstDocumentPoint().x == blankline.GetLastDocumentPoint().x &&
		blankline.GetFirstDocumentPoint().y == blankline.GetLastDocumentPoint().y &&
		blankline.GetFirstDocumentPoint().z == blankline.GetLastDocumentPoint().z 
		;	

	size_t blanklen = blankline.GetPointsNumber();

	printf("bVisible00 = %d\n", bVisible00);
	if (base_point)
	{
		// ??????????????????????????
		int rez = blankline.WhatSidesOfTwoPoint(this->m_zflag, this->GetSurfDocPoint(0,0), (*base_point).ConvertTo(this->m_zflag));
		switch(rez)
		{
		case -1:
			{
				bVisible00 = !base_point->bVisible;
			}
			break;
		case +1:
			{
				bVisible00 = base_point->bVisible;
			}
			break;
		case +2: // обе точки сели на линию
		case +4: // вторая точка села на линию
			MessageBox(0, "Опорная выбрана неудачно - \nона попала на линию бланкования - \nВыберите другую опорную точку", "Blank error", 0);
			return false;
		case +3: // первая точка села на линию
			MessageBox(0, "Первая точка сетки - \пересекается с линией бланкования - \nИзмените линию бланкования или опорную сетку", "Blank error", 0);
			return false;
		}
	}
	else
	{
		if (closed_blankline)
		{
printf("closed_blankline bVisible00 = %d\n", bVisible00);

			double 
				angle1,
				angle2, 
				dangle=0.0, 
				sum_dangle=0.0;

			double mult = 1.999999999;

			int i,j,q;

			for (q = 0; q < blanklen; q++)
			{
				/*CPoint3 pts[2];
				pts[0] = CPoint3(x00,y00,0.0, true);
				pts[1] = blankline.GetDocumentPoint(q);
				this->m_pSurfDoc->AddLine(pts,2,RGB(0,0,0));
*/
				if(q > 0)
				{
					angle1 = angle2;
				}	
				switch(this->m_zflag)
				{
				case 0:
					{
						angle2 = atan2(
							blankline.GetDocumentPoint(q).y - y00, 
							blankline.GetDocumentPoint(q).x - x00);	
					}
					break;
				case 1:
					{
						angle2 = atan2(
							blankline.GetDocumentPoint(q).y - y00, 
							blankline.GetDocumentPoint(q).z - x00);	
					}
					break;
				case 2:
					{
						angle2 = atan2(
							blankline.GetDocumentPoint(q).z - y00, 
							blankline.GetDocumentPoint(q).x - x00);	
					}
					break;
				}
//char s[255];
//sprintf(s, "q = %d angle = %f = %2.1f", q, angle2, angle2/PI*180);
//this->m_pSurfDoc->AddString(blankline.GetDocumentPoint(q),s,RGB(0,0,0),0.0);
				if(q > 0)
				{
					dangle = angle2 - angle1;
					//если мы пересекаем угол +-180
					if (angle1 * angle2 < 0.0 && fabs(angle1)+fabs(angle2) > PI)
					{
						// корректируем
						//printf("angle1 * angle2 %f < 0 dangle = %f \n", angle1 * angle2, dangle);
						if (dangle >  0.0)
						{
							//printf("dangle >  0.0)\n");
							dangle -= 2.0*PI;
						}
						else
							if (dangle <  0.0)
							{
								//printf("dangle <  0.0)\n");
								dangle += 2.0*PI;
							}
					}
					sum_dangle += dangle;
				}
//printf("%d sum_dangle = %f, dangle = %f, angle1 = %f, angle2 = %f\n", q, 
//	   sum_dangle, dangle, angle1, angle2);

			}  
			//если мы сделали полный оборот, меняем флаг видимости
			if (
				fabs(sum_dangle - 2.0*PI) < 0.001 
				|| 
				fabs(sum_dangle + 2.0*PI) < 0.001
				)
			{
				// change start visible flag
				bVisible00 ^= true;
				printf("change start visible flag\n");
			}
			printf(
				"bVisible00 = %d sum_dangle = %f sum_dangle - 2.0*PI = %f sum_dangle + 2.0*PI = %f\n", 
				bVisible00, sum_dangle, sum_dangle - 2.0*PI, sum_dangle + 2.0*PI);
		}
		else
		{
			if (IDYES == MessageBox(0, 
				"линией бланкования не замкнута и не имеет опорной точки - \n"
				"Если Вы хотите вручню выбрать флаг видимости начальной точки грида\n"
				"тогда нажмите ДА\n"
				"иначе - нажмите НЕТ и измените линию бланкования или опорную сетку", 
				"Blank error", MB_YESNO))
			{
				char str[1024];
				sprintf(str, "координаты начальной точки грида [%f %f %f]\n"
					"Нажмите ДА если эта точка должна остаться видимой\n"
					"Нажмите НЕТ если эта точка должна остаться невидимой\n"
					, 
					this->GetSurfDocPoint(0,0).x,
					this->GetSurfDocPoint(0,0).y, 
					this->GetSurfDocPoint(0,0).z);

				if (IDYES == MessageBox(0, str, 
					"Select 00 point visible flag", MB_YESNO))
				{
					bVisible00 = true;
				}
				else
				{
					bVisible00 = false;
				}
				return true;
			}
			else
				return false;
		}
	}
	return true;

}
void Surface3D::BlankTheGrid(
							 size_t nx,	size_t ny,
							 vector<surf_edge>& vse_gor, 
							 vector<surf_edge>& vse_ver,
							 bool& bVisible)
{
printf("BlankTheGrid\n");

	int r, c;
	bool bVisible00 = bVisible;
//bool test = true;
	//bool test = Line3D::s_line3d_draw_mode;
	bool test2 = false;
	bool test1 = false;
	// проход по горизонтальным рёбрам
	bool forward = true;
	//if (false)// неотлаженный пока вариант прохода по другому (длинные хода по вертикалям и коротие хода по горизонталям) маршруту 
	if (true)
	{
	if(test1) this->m_pSurfDoc->AddLine();
	for (r = 0; r < this->m_leny; r++)
	{		
		if (forward)
		{
			for (c = 1; c < this->m_lenx; c++)
			{
				int j = r*nx + c-1;//номер ребра
				int jj = r*this->m_lenx + c;//номер узла
				// sort vec by increasing r or c coordinate fo determine m_cutDirectionOfVisible
				// sorting mode - by c
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;
				std::sort(vse_gor[j].vec.begin(), vse_gor[j].vec.end());
				vse_gor[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::iterator iter = vse_gor[j].vec.begin();
					iter != vse_gor[j].vec.end(); iter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::right;
					}
					else
					{
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::left;
					}
					if (test2)
					{
						double r;CPoint3 projection_pt;
						if(this->Projection((*iter).x, (*iter).y, 0.0, r, &projection_pt))
						{
							this->m_pSurfDoc->AddSphere(projection_pt, RGB(0,0,0));							
						}	
						else
							this->m_pSurfDoc->AddSphere(
							(*iter).x,(*iter).y,0.0, RGB(0,0,0));
					}

				}
				this->m_vdPoints[jj].bVisible &= bVisible;
				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);

						//char s[255];
						//sprintf(s, "vse_gor[%d]\0", j);
						//this->m_pSurfDoc->AddString(pt,s,RGB(0,0,255),0.0);
					}
				}
			}
			// переход на строку вверх
			if (r < ny)
			{
				int j = (r)*this->m_lenx + nx;//номер ребра
				int jj = (r+1)*this->m_lenx+nx;//номер узла
				// sorting mode - by r
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_r;
				std::sort(vse_ver[j].vec.begin(), vse_ver[j].vec.end());
				vse_ver[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::iterator iter = vse_ver[j].vec.begin();
					iter != vse_ver[j].vec.end(); iter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::up;
					}
					else
					{
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::down;
					}
					if (test2)
					{
						double r;CPoint3 projection_pt;
						if(this->Projection((*iter).x, (*iter).y, 0.0, r, &projection_pt))
						{
							this->m_pSurfDoc->AddSphere(projection_pt, RGB(0,0,0));							
						}	
						else
							this->m_pSurfDoc->AddSphere(
							(*iter).x,(*iter).y,0.0, RGB(0,0,0));
					}

				}
				this->m_vdPoints[jj].bVisible &= bVisible;

				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
						//char s[255];
						//sprintf(s, "vse_ver[%d]\0", j);
						//this->m_pSurfDoc->AddString(pt,s,RGB(0,0,255),0.0);
					}
				}
			}
			// реверс
			forward = false;
		}
		else // !forward
		{
            for (int c = this->m_lenx-2; c >= 0; c--)
			{
				int j = r*nx + c;//номер ребра
				int jj = r*this->m_lenx+c;//номер узла
				// sorting mode - by c
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;
				std::sort(vse_gor[j].vec.begin(), vse_gor[j].vec.end());
				vse_gor[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::reverse_iterator riter = vse_gor[j].vec.rbegin();
					riter != vse_gor[j].vec.rend(); riter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*riter).m_cutDirectionOfVisible = surf_edge::edge_cutting::left;
					}
					else
					{
						(*riter).m_cutDirectionOfVisible = surf_edge::edge_cutting::right;
					}
					if (test2)
					{
						double r;CPoint3 projection_pt;
						if(this->Projection((*riter).x, (*riter).y, 0.0, r, &projection_pt))
						{
							this->m_pSurfDoc->AddSphere(projection_pt, RGB(0,0,0));							
						}	
						else
							this->m_pSurfDoc->AddSphere(
							(*riter).x,(*riter).y,0.0, RGB(0,0,0));
					}

				}
				this->m_vdPoints[jj].bVisible &= bVisible;
									
				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
						//char s[255];
						//sprintf(s, "vse_gor[%d]\0", j);
						//this->m_pSurfDoc->AddString(pt,s,RGB(0,0,255),0.0);
					}
				}
			}
			// переход на строку вверх
			if (r < ny)
			{
				int j = (r)*this->m_lenx + 0;
				int jj = (r+1)*this->m_lenx+0;//номер узла
				// sorting mode - by r
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_r;
				std::sort(vse_ver[j].vec.begin(), vse_ver[j].vec.end());
				vse_ver[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::iterator iter = vse_ver[j].vec.begin();
					iter != vse_ver[j].vec.end(); iter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::up;
					}
					else
					{
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::down;
					}
					if (test2)
					{
						double r;CPoint3 projection_pt;
						if(this->Projection((*iter).x, (*iter).y, 0.0, r, &projection_pt))
						{
							this->m_pSurfDoc->AddSphere(projection_pt, RGB(0,0,0));							
						}	
						else
							this->m_pSurfDoc->AddSphere(
							(*iter).x,(*iter).y,0.0, RGB(0,0,0));
					}

				}
				this->m_vdPoints[jj].bVisible &= bVisible;
									
				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
						//char s[255];
						//sprintf(s, "vse_ver[%d]\0", j);
						//this->m_pSurfDoc->AddString(pt,s,RGB(0,0,255),0.0);
					}
				}
			}
			// реверс
			forward = true;
		}
	}
	}
	else
	{
 	if(test1) this->m_pSurfDoc->AddLine();
   // проход по вертикальным рёбрам
	printf("nx = %d ny = %d this->GetPointsNumber() = %u\n", nx,ny, this->GetPointsNumber());
	printf("vse_ver.size() = %d\n", vse_ver.size());
	printf("vse_gor.size() = %d\n", vse_gor.size());
	for (c = 0; c < this->m_lenx; c++)
	{
		printf ("c = %d\n", c);
		if (forward)
		{
			for (r = 1; r < this->m_leny; r++)
			{
				int j = (r-1)*this->m_lenx + c;//номер ребра
				int jj = r*this->m_lenx+c;//номер узла
				printf("r = %d j = %d jj = %d\n", r, j, jj);
//				int j = r*nx + c-1;//номер ребра
//				int jj = r*this->m_lenx + c;//номер узла
				// sort vec by increasing r or c coordinate fo determine m_cutDirectionOfVisible
				// sorting mode - by r
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_r;
				std::sort(vse_ver[j].vec.begin(), vse_ver[j].vec.end());
				vse_ver[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::iterator iter = vse_ver[j].vec.begin();
					iter != vse_ver[j].vec.end(); iter++)
				{
					// change bVisible flag
					bVisible ^= true;
					printf("change bVisible flag = %d\n", bVisible);
					if (bVisible)
					{						
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::up;
					}
					else
					{
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::down;
					}
				}
				this->m_vdPoints[jj].bVisible &= bVisible;
				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
					}
				}
			}
			// переход на колонку вправо
			printf("on col to right\n");
			if (c < nx)
			{
//				int j = r*nx + c-1;//номер ребра
//				int jj = r*this->m_lenx + c;//номер узла
				int j = (r-1)*this->m_lenx + nx;//номер ребра
				int jj = (r+1)*this->m_lenx+nx;//номер узла
				// sorting mode - by c
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;
				std::sort(vse_gor[j].vec.begin(), vse_gor[j].vec.end());
				vse_gor[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::iterator iter = vse_gor[j].vec.begin();
					iter != vse_gor[j].vec.end(); iter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::right;
					}
					else
					{
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::left;
					}
				}
				this->m_vdPoints[jj].bVisible &= bVisible;

				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
					}
				}
			}
			// реверс
			forward = false;
		}
		else // !forward
		{
            for (int r = this->m_leny-2; r >= 0; r--)
			{
				int j = r*nx + c;//номер ребра
				int jj = r*this->m_lenx+c;//номер узла
				// sorting mode - by r
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_r;
				std::sort(vse_ver[j].vec.begin(), vse_ver[j].vec.end());
				vse_ver[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::reverse_iterator riter = vse_ver[j].vec.rbegin();
					riter != vse_ver[j].vec.rend(); riter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*riter).m_cutDirectionOfVisible = surf_edge::edge_cutting::down;
					}
					else
					{
						(*riter).m_cutDirectionOfVisible = surf_edge::edge_cutting::up;
					}
				}
				this->m_vdPoints[jj].bVisible &= bVisible;
									
				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
					}
				}
			}
			// переход на колонку вправо
			if (c < nx)
			{
				int j = (r)*this->m_lenx + 0;
				int jj = (r+1)*this->m_lenx+0;//номер узла
				// sorting mode - by c
				surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;
				std::sort(vse_gor[j].vec.begin(), vse_gor[j].vec.end());
				vse_gor[j].bSorted = true;
				for (vector<surf_edge::edge_cutting>::iterator iter = vse_gor[j].vec.begin();
					iter != vse_gor[j].vec.end(); iter++)
				{
					// change bVisible flag
					bVisible ^= true;
					if (bVisible)
					{						
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::right;
					}
					else
					{
						(*iter).m_cutDirectionOfVisible = surf_edge::edge_cutting::left;
					}
				}
				this->m_vdPoints[jj].bVisible &= bVisible;
									
				if (test1)
				{
					if(m_pSurfDoc->m_lines.SetCurrentMsgOnLast())
					{
						CPoint3 pt;
						pt = this->m_vdPoints[jj];
						pt.bVisible = true;
						m_pSurfDoc->m_lines.GetCurrentMsg().PushBack(pt);
					}
				}
			}
			// реверс
			forward = true;
		}
	}
	}
	if (this->GetPointsNumber())
		this->m_vdPoints[0].bVisible &= bVisible00;
}

void Surface3D::BlankPolygonFilling(GeoSurface & rGeoSurface,
						 size_t nx,	size_t ny,
						 vector<surf_edge>& vse_gor, 
						 vector<surf_edge>& vse_ver)
{
	//bool test = true;
	//bool test = false;

	PRIMITIVE_POINTS_PTR(CPoint3) ptd;
	ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT r=0, i=0;  r<ny;  r++, i++)
	{
		//====== Связанные полигоны начинаются
		//====== на каждой полосе вновь

		//====== Цикл прохода вдоль оси X
		for (UINT c=0;  c<nx;  c++, i++)
		{
			// i, j, k, n - 4 индекса вершин примитива при
			// обходе в направлении против часовой стрелки

			int	j = i + 
				nx + 1,	// Индекс узла с большим Z

				k = j+1,			// Индекс узла по диагонали
				n = i+1; 			// Индекс узла справа

			// а эти координаты - уже реальные - они получены путём перевода с использованием this->m_zflag
			double 
				xi,yi,zi,
				xj,yj,zj,
				xk,yk,zk,
				xn,yn,zn;

			bool 
				bi = ptd[i].bVisible,
				bj = ptd[j].bVisible,
				bk = ptd[k].bVisible,
				bn = ptd[n].bVisible;	
				
			int nb = int(bi) + int(bj) + int(bk) + int(bn);

			if (nb != 4 && nb > 0 &&
				// получаем координаты клетки на текущей (моей) поверхности
				this->GetDocumentCoordinates(i, xi, yi, zi, bi ) &&
				this->GetDocumentCoordinates(j, xj, yj, zj, bj ) &&
				this->GetDocumentCoordinates(k, xk, yk, zk, bk ) &&
				this->GetDocumentCoordinates(n, xn, yn, zn, bn ) 
				)
			{
/*printf("\n");
printf("\n");
printf("i %u, xi %f, yi %f, zi %f, bi %d \n", i, xi, yi, zi, bi );
printf("j %u, xj %f, yj %f, zj %f, bj %d \n", j, xj, yj, zj, bj );
printf("k %u, xk %f, yk %f, zk %f, bk %d \n", k, xk, yk, zk, bk );
printf("n %u, xn %f, yn %f, zn %f, bn %d \n", n, xn, yn, zn, bn );
printf("\n");*/
				vector<blank_polygon_point> blank_polygon_points;
				blank_polygon_points.resize(0);
				if(CollectBlankPolygonQuadPoints(blank_polygon_points,
					r, c, nx, ny,
					vse_gor, 
					vse_ver,
					bi, xi, yi, zi,
					bj, xj, yj, zj,
					bk, xk, yk, zk,
					bn, xn, yn, zn))	
					rGeoSurface.MakeQuadBlankPolygons(blank_polygon_points);
			}
		}
	}			
}


void Surface3D::BlankPolygonFilling(GeoSurface & rGeoSurface,
	size_t nx,	size_t ny,
	vector<vector<surf_edge> >& v_vse_gor, 
	vector<vector<surf_edge> >& v_vse_ver)
{
	//bool test = true;
	//bool test = false;
printf("Blank start of polygones filling\n");
	PRIMITIVE_POINTS_PTR(CPoint3) ptd;
	ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT r=0, i=0;  r<ny;  r++, i++)
	{
		//====== Связанные полигоны начинаются
		//====== на каждой полосе вновь

		//====== Цикл прохода вдоль оси X
		for (UINT c=0;  c<nx;  c++, i++)
		{
			// i, j, k, n - 4 индекса вершин примитива при
			// обходе в направлении против часовой стрелки

			int	j = i + 
				nx + 1,	// Индекс узла с большим Z

				k = j+1,			// Индекс узла по диагонали
				n = i+1; 			// Индекс узла справа

			// а эти координаты - уже реальные - они получены путём перевода с использованием this->m_zflag
			double 
				xi,yi,zi,
				xj,yj,zj,
				xk,yk,zk,
				xn,yn,zn;

			bool 
				bi = ptd[i].bVisible,
				bj = ptd[j].bVisible,
				bk = ptd[k].bVisible,
				bn = ptd[n].bVisible;	
				
			int nb = int(bi) + int(bj) + int(bk) + int(bn);

			if (nb != 4 && nb > 0 &&
				// получаем координаты клетки на текущей (моей) поверхности
				this->GetDocumentCoordinates(i, xi, yi, zi, bi ) &&
				this->GetDocumentCoordinates(j, xj, yj, zj, bj ) &&
				this->GetDocumentCoordinates(k, xk, yk, zk, bk ) &&
				this->GetDocumentCoordinates(n, xn, yn, zn, bn ) 
				)
			{
				vector<vector<surf_edge> >::iterator g_iter = v_vse_gor.begin();
				vector<vector<surf_edge> >::iterator v_iter = v_vse_ver.begin();
/*
			MakeBlankPolygon(
					r, c, nx, ny,
					vse_gor, 
					vse_ver,
					bi, xi, yi, zi,
					bj, xj, yj, zj,
					bk, xk, yk, zk,
					bn, xn, yn, zn,
					pGeoSurface);		*/		
			}
		}
	}			
}
bool Surface3D::CollectBlankPolygonQuadPoints(
	vector<blank_polygon_point>& blank_polygon_points,
		UINT r, UINT c, 
		size_t nx,
		size_t ny,
		vector<surf_edge>& vse_gor, 
		vector<surf_edge>& vse_ver,
		bool bi, double xi, double yi, double zi,
		bool bj, double xj, double yj, double zj,
		bool bk, double xk, double yk, double zk,
		bool bn, double xn, double yn, double zn)
{
/*printf("CollectBlankPolygonQuadPoints r %u c %u\n", r,c );
printf("xi %f, yi %f, zi %f, bi %d \n", xi, yi, zi, bi );
printf("xj %f, yj %f, zj %f, bj %d \n", xj, yj, zj, bj );
printf("xk %f, yk %f, zk %f, bk %d \n", xk, yk, zk, bk );
printf("xn %f, yn %f, zn %f, bn %d \n", xn, yn, zn, bn );
printf("blank_polygon_points.size() = %u\n", blank_polygon_points.size());*/
	bool test = false;
	// МАТЕМАТИЧЕСКИ
	// i	n
	//
	// j	k

	// ВИЗУАЛЬНО
	// j	k
	//
	// i	n					

	
	CPoint3 projection_pt;
	blank_polygon_point bp_pt;

	//projection_pt.flag |= CPOINT3_FLAG_NONORMAL;

	if (bi)
	{
//		poly.PushBack(CPoint3(xi,yi,zi,true));
		bp_pt.pt = CPoint3(xi,yi,zi,true);
		bp_pt.line_number = -1;
		blank_polygon_points.push_back(bp_pt);
		if (test)
		{
			char s[255];
			sprintf(s, "i\0");
			this->m_pSurfDoc->AddString(CPoint3(xi,yi,zi,true),s,RGB(0,0,255),0.0);
		}
	}

	int I = (r)*this->m_lenx + c;//номер ребра
	if (!vse_ver[I].bSorted)
	{
		// sorting mode - by r
		surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_r;
		std::sort(vse_ver[I].vec.begin(), vse_ver[I].vec.end());
		vse_ver[I].bSorted = true;
	}
	for (vector<surf_edge::edge_cutting>::iterator iter = vse_ver[I].vec.begin();
		iter != vse_ver[I].vec.end(); iter++)
	{
		// не строим полигонов, если это не линия бланкования а её продолжение
		if ((*iter).this_is_continue_line 
			&& s_do_not_build_blank_polygones_on_continue_lines) return false; 

		double r;
		//if(this->Projection(vse_ver[I].x, vse_ver[I].y, 0.0, r, &projection_pt))
		bool projection_result = false;
		switch(this->m_zflag)
		{
		case 0:
				projection_result = this->Projection((*iter).x, (*iter).y, 0.0, r, &projection_pt);
			break;
		case 1:
				projection_result = this->Projection(0.0, (*iter).y, (*iter).x, r, &projection_pt);
			break;
		case 2:
				projection_result = this->Projection((*iter).x, 0.0, (*iter).y, r, &projection_pt);
			break;
		}
		if(projection_result)
		{
//			poly.PushBack(projection_pt);	

			bp_pt.pt							= projection_pt;
			bp_pt.line_number					= (*iter).line_number;
			bp_pt.line_point_number1			= (*iter).line_point_number1;
			bp_pt.distance_from_start_of_line	= (*iter).distance_from_start_of_line;
			blank_polygon_points.push_back(bp_pt);

			if(test) this->m_pSurfDoc->AddSphere(projection_pt, RGB(255,0,0));
		}					
	}

	if (bj)
	{
//		poly.PushBack(CPoint3(xj,yj,zj,true));
		bp_pt.pt = CPoint3(xj,yj,zj,true);
		bp_pt.line_number = -1;
		blank_polygon_points.push_back(bp_pt);
		if (test)
		{
			char s[255];
			sprintf(s, "j\0");
			this->m_pSurfDoc->AddString(CPoint3(xj,yj,zj,true),s,RGB(0,0,255),0.0);
		}
	}
	
	I = (r+1)*nx + c;//номер ребра
	if (!vse_gor[I].bSorted)
	{
		// sorting mode - by c
		surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;
		std::sort(vse_gor[I].vec.begin(), vse_gor[I].vec.end());
		vse_gor[I].bSorted = true;
	}
	for (vector<surf_edge::edge_cutting>::iterator iter = vse_gor[I].vec.begin();
		iter != vse_gor[I].vec.end(); iter++)
	{
		// не строим полигонов, если это не линия бланкования а её продолжение
		if ((*iter).this_is_continue_line 
			&& s_do_not_build_blank_polygones_on_continue_lines) return false; 

		double r;
		//if(this->Projection(vse_gor[I].x, vse_gor[I].y, 0.0, r, &projection_pt))
		bool projection_result = false;
		switch(this->m_zflag)
		{
		case 0:
				projection_result = this->Projection((*iter).x, (*iter).y, 0.0, r, &projection_pt);
			break;
		case 1:
				projection_result = this->Projection(0.0, (*iter).y, (*iter).x, r, &projection_pt);
			break;
		case 2:
				projection_result = this->Projection((*iter).x, 0.0, (*iter).y, r, &projection_pt);
			break;
		}
		if(projection_result)
		{
//			poly.PushBack(projection_pt);	

			bp_pt.pt							= projection_pt;
			bp_pt.line_number					= (*iter).line_number;
			bp_pt.line_point_number1			= (*iter).line_point_number1;
			bp_pt.distance_from_start_of_line	= (*iter).distance_from_start_of_line;
			blank_polygon_points.push_back(bp_pt);

			if(test) this->m_pSurfDoc->AddSphere(projection_pt, RGB(255,0,0));
		}					
	}


	if (bk)
	{
//		poly.PushBack(CPoint3(xk,yk,zk,true));
		bp_pt.pt = CPoint3(xk,yk,zk,true);
		bp_pt.line_number = -1;
		blank_polygon_points.push_back(bp_pt);
		if (test)
		{
			char s[255];
			sprintf(s, "k\0");
			this->m_pSurfDoc->AddString(CPoint3(xk,yk,zk,true),s,RGB(0,0,255),0.0);
		}
	}

	I = (r)*this->m_lenx + c+1;//номер ребра
	if (!vse_ver[I].bSorted)
	{
		// sorting mode - by r
		surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_r;
		std::sort(vse_ver[I].vec.begin(), vse_ver[I].vec.end());
		vse_ver[I].bSorted = true;
	}
	for (vector<surf_edge::edge_cutting>::reverse_iterator riter = vse_ver[I].vec.rbegin();
		riter != vse_ver[I].vec.rend(); riter++)
	{
		// не строим полигонов, если это не линия бланкования а её продолжение
		if ((*riter).this_is_continue_line 
			&& s_do_not_build_blank_polygones_on_continue_lines) return false; 

		double r;
		//if(this->Projection(vse_ver[I].x, vse_ver[I].y, 0.0, r, &projection_pt))
		bool projection_result = false;
		switch(this->m_zflag)
		{
		case 0:
				projection_result = this->Projection((*riter).x, (*riter).y, 0.0, r, &projection_pt);
			break;
		case 1:
				projection_result = this->Projection(0.0, (*riter).y, (*riter).x, r, &projection_pt);
			break;
		case 2:
				projection_result = this->Projection((*riter).x, 0.0, (*riter).y, r, &projection_pt);
			break;
		}
		if(projection_result)
		{
//			poly.PushBack(projection_pt);		

			bp_pt.pt							= projection_pt;
			bp_pt.line_number					= (*riter).line_number;
			bp_pt.line_point_number1			= (*riter).line_point_number1;
			bp_pt.distance_from_start_of_line	= (*riter).distance_from_start_of_line;
			blank_polygon_points.push_back(bp_pt);

			if(test) this->m_pSurfDoc->AddSphere(projection_pt, RGB(255,0,0));
		}					
	}
	if (bn)
	{
//		poly.PushBack(CPoint3(xn,yn,zn,true));
		bp_pt.pt = CPoint3(xn,yn,zn,true);
		bp_pt.line_number = -1;
		blank_polygon_points.push_back(bp_pt);
		if (test)
		{
			char s[255];
			sprintf(s, "n\0");
			this->m_pSurfDoc->AddString(CPoint3(xn,yn,zn,true),s,RGB(0,0,255),0.0);
		}
	}

	I = r*nx + c;//номер ребра
	if (!vse_gor[I].bSorted)
	{
		// sorting mode - by c
		surf_edge::edge_cutting::s_sort_mode = surf_edge::edge_cutting::by_c;
		std::sort(vse_gor[I].vec.begin(), vse_gor[I].vec.end());
		vse_gor[I].bSorted = true;
	}
	for (vector<surf_edge::edge_cutting>::reverse_iterator riter = vse_gor[I].vec.rbegin();
		riter != vse_gor[I].vec.rend(); riter++)
	{
		// не строим полигонов, если это не линия бланкования а её продолжение
		if ((*riter).this_is_continue_line 
			&& s_do_not_build_blank_polygones_on_continue_lines) return false; 

		double r;
		//if(this->Projection(vse_gor[I].x, vse_gor[I].y, 0.0, r, &projection_pt))
		bool projection_result = false;
		switch(this->m_zflag)
		{
		case 0:
				projection_result = this->Projection((*riter).x, (*riter).y, 0.0, r, &projection_pt);
			break;
		case 1:
				projection_result = this->Projection(0.0, (*riter).y, (*riter).x, r, &projection_pt);
			break;
		case 2:
				projection_result = this->Projection((*riter).x, 0.0, (*riter).y, r, &projection_pt);
			break;
		}
		if(projection_result)
		{
//			poly.PushBack(projection_pt);	

			bp_pt.pt							= projection_pt;
			bp_pt.line_number					= (*riter).line_number;
			bp_pt.line_point_number1			= (*riter).line_point_number1;
			bp_pt.distance_from_start_of_line	= (*riter).distance_from_start_of_line;
			blank_polygon_points.push_back(bp_pt);

			if(test) this->m_pSurfDoc->AddSphere(projection_pt, RGB(255,0,0));
		}					
	}
	return true;
}

void Surface3D::Blank(Line3D& blankline, bool to_continue_line_to_borders, GeoSurface & pGeoSurface, CPoint3 * base_point)
{
	printf("Blank\n");
	size_t nx = this->m_lenx - 1;
	size_t ny = this->m_leny - 1;

	//Координаты 4-х углов поверхности
	// n0	nn
	// 
	// 00	0n
	double x00 = this->GetSurfDocPoint(0,0).x;
	double y00 = this->GetSurfDocPoint(0,0).y;
	//if (test)
	//{
/*
char s[255];
sprintf(s, "00");
this->m_pSurfDoc->AddString(this->GetSurfDocPoint(0,0),s,RGB(255,0,0),0.0);
	*///}
	double x0n = this->GetSurfDocPoint(0,nx).x;
	double y0n = this->GetSurfDocPoint(0,nx).y;
//sprintf(s, "0n");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(0,nx),s,RGB(255,0,0),0.0);

	double xn0 = this->GetSurfDocPoint(ny,0).x;
	double yn0 = this->GetSurfDocPoint(ny,0).y;
//sprintf(s, "n0");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(ny,0),s,RGB(255,0,0),0.0);

	double xnn = this->GetSurfDocPoint(ny,nx).x;
	double ynn = this->GetSurfDocPoint(ny,nx).y;
//sprintf(s, "nn");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(ny,nx),s,RGB(255,0,0),0.0);
	
	//размер площадки в метрах
	double Dx = xnn - x00;
	double Dy = ynn - y00;

	//длина ребра клетки в долях единицы
	double dx_dc = (x0n-x00)/(xnn-x00)/nx;
	double dx_dr = (xn0-x00)/(xnn-x00)/ny;

	double dy_dc = (y0n-y00)/(ynn-y00)/nx;
	double dy_dr = (yn0-y00)/(ynn-y00)/ny;

	vector<surf_edge> 
		vse_gor, vse_ver;
	int line_number = 0;

	double line_len = FindCuttingOfSurfaceEdgesWithBlankLine(
		line_number,
		blankline, 
		to_continue_line_to_borders, 
		&vse_gor, 
		&vse_ver,
		nx,		ny,
		x00,	y00,
		x0n,	y0n,
		xn0,	yn0,
		xnn,	ynn,		
		//размер площадки в метрах
		Dx,		Dy,
		//длина ребра клетки в долях единицы
		dx_dc,	dx_dr,
		dy_dc,	dy_dr
		);

	int inside = blankline.m_lParam & OBJECT_FLAG_INSIDE_BLANK_BIT ? 0 : 1;
	printf ("inside = %d\n", inside);
	// inside
	// 0 - inside is visible
	// 1 - outside is visible

	// start visible flag bVisible - the visible flag of first point
	// false - the first point is outside
	// true  - the first point is inside
	// изначально мы думаем, что точка 00 лежит вне контура линии бланкования
	// поэтому если инсайд == 0, что означает нужно внтри онтура сделать видимой
	// то мы точку делаем невидимой
	bool bVisible00 = !(inside == 0);

	if (!DetermineVisibleFlagOfFirstGridPoint(
		blankline,
		base_point,
		x00, y00,bVisible00))
	{
		return;
	}

	BlankTheGrid(
		nx,	ny,
		vse_gor, 
		vse_ver,
		bVisible00);

	BlankPolygonFilling(
		pGeoSurface,
		nx,	ny,
		vse_gor,
        vse_ver);

	printf("Blank end\n");
}

//fprintf("i = %d xi = %lf, yi = %lf zi = %lf bi = %d\n", i, xi, yi, zi, int(bi));
//fprintf("j = %d xj = %lf, yj = %lf zj = %lf bj = %d\n", j, xj, yj, zj, int(bj));
//fprintf("k = %d xk = %lf, yk = %lf zk = %lf bk = %d\n", k, xk, yk, zk, int(bk));
//fprintf("n = %d xn = %lf, yn = %lf zn = %lf bn = %d\n\n", n, xn, yn, zn, int(bn));
//fprintf("%d%d%d%d\t", int(bi), int(bj), int(bk), int(bn));
bool Surface3D::BlankAbove(Surface3D & surf, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix)
{
	bool res1 = false;
	bool res2 = true;

	if (this->m_zflag == surf.m_zflag)
	{
		if (this->m_lenx == surf.m_lenx && this->m_leny == surf.m_leny)
		{
			for (unsigned int ix = 0; ix < this->m_lenx; ix++)
			{
				for (unsigned int iy = 0; iy < this->m_leny; iy++)
				{
					if (this->GetSurfDocPoint(iy,ix).x == surf.GetSurfDocPoint(iy,ix).x
						&&
						this->GetSurfDocPoint(iy,ix).y == surf.GetSurfDocPoint(iy,ix).y)
					{
						if (this->GetSurfDocPoint(iy,ix).flag & CPOINT3_FLAG_BLANKED || 
							surf.GetSurfDocPoint(iy,ix).flag & CPOINT3_FLAG_BLANKED)
							continue;

						if (this->GetSurfDocPoint(iy,ix).z > surf.GetSurfDocPoint(iy,ix).z)
						{
							this->GetSurfDocPoint(iy,ix).bVisible = false;
							if (blank_polygon_matrix && ix < this->m_lenx - 1 && iy < this->m_leny - 1)
							{
								if ((*blank_polygon_matrix)[iy][ix])
								{
									if (this->GetSurfDocPoint(iy  , ix  ).z >= surf.GetSurfDocPoint(iy  , ix  ).z &&
										this->GetSurfDocPoint(iy+1, ix  ).z >= surf.GetSurfDocPoint(iy+1, ix  ).z &&
										this->GetSurfDocPoint(iy,   ix+1).z >= surf.GetSurfDocPoint(iy,   ix+1).z &&
										this->GetSurfDocPoint(iy+1, ix+1).z >= surf.GetSurfDocPoint(iy+1, ix+1).z)
									{
										(*blank_polygon_matrix)[iy][ix]->Free();
										delete (*blank_polygon_matrix)[iy][ix];
										(*blank_polygon_matrix)[iy][ix] = NULL;
									}
								}
							}
						}
						res1 = true;
					}
					else
					{
						res2 = false;
					}
				}
			}
		}
	}
	else
	{
		for (size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			if (this->GetDocumentPoint(i).flag & CPOINT3_FLAG_BLANKED) continue;

			double x, y, z;
			bool visible;
			this->GetDocumentCoordinates(i, x, y, z, visible);
			double r; CPoint3 pt;
			if (surf.Projection(x, y, z, r, &pt))
			{
				if (r > 0.0)
					this->GetDocumentPoint(i).bVisible = false;
			}
		}
	}
	return res1 && res2;
}

bool Surface3D::BlankUnder(Surface3D & surf, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix)
{
	bool res1 = false;
	bool res2 = true;

	if (this->m_zflag == surf.m_zflag)
	{
		if (this->m_lenx == surf.m_lenx && this->m_leny == surf.m_leny)
		{
			for (unsigned int ix = 0; ix < this->m_lenx; ix++)
			{
				for (unsigned int iy = 0; iy < this->m_leny; iy++)
				{
					if (this->GetSurfDocPoint(iy,ix).x == surf.GetSurfDocPoint(iy,ix).x
						&&
						this->GetSurfDocPoint(iy,ix).y == surf.GetSurfDocPoint(iy,ix).y)
					{
						if (this->GetSurfDocPoint(iy,ix).flag & CPOINT3_FLAG_BLANKED || 
							surf.GetSurfDocPoint(iy,ix).flag & CPOINT3_FLAG_BLANKED)
							continue;

						if (this->GetSurfDocPoint(iy,ix).z < surf.GetSurfDocPoint(iy,ix).z)
						{
							this->GetSurfDocPoint(iy,ix).bVisible = false;

							if (blank_polygon_matrix && ix < this->m_lenx - 1 && iy < this->m_leny - 1)
							{
								if ((*blank_polygon_matrix)[iy][ix])
								{
									if (
										this->GetSurfDocPoint(iy , ix).z   <= surf.GetSurfDocPoint(iy,  ix).z && 
										this->GetSurfDocPoint(iy+1,ix).z   <= surf.GetSurfDocPoint(iy+1,ix).z && 
										this->GetSurfDocPoint(iy,  ix+1).z <= surf.GetSurfDocPoint(iy,  ix+1).z && 
										this->GetSurfDocPoint(iy+1,ix+1).z <= surf.GetSurfDocPoint(iy+1,ix+1).z)
									{
										(*blank_polygon_matrix)[iy][ix]->Free();
										delete (*blank_polygon_matrix)[iy][ix];
										(*blank_polygon_matrix)[iy][ix] = NULL;
									}
								}
							}
						}
						res1 = true;
					}
					else
					{
						res2 = false;
					}
				}
			}
		}
	}
	else
	{
		for (size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			if (this->GetDocumentPoint(i).flag & CPOINT3_FLAG_BLANKED) continue;

			double x, y, z;
			bool visible;
			this->GetDocumentCoordinates(i, x, y, z, visible);
			double r; CPoint3 pt;
			if (surf.Projection(x, y, z, r, &pt))
			{
				if (r < 0.0)
					this->GetDocumentPoint(i).bVisible = false;
			}
		}
	}
	return res1 && res2;
}

void Surface3D::Blank(vect<Line3D>& blanklines, bool to_continue_line_to_borders, GeoSurface & rGeoSurface, CPoint3 * base_point)
{
	//printf("Blank(vect<Line3D>& blanklines, bool to_continue_line_to_borders, void * pGeoSurface, CPoint3 * base_point)\n");
	size_t nx = this->m_lenx - 1;
	size_t ny = this->m_leny - 1;

	//Координаты 4-х углов поверхности
	// n0	nn
	// 
	// 00	0n
	double x00 = this->GetSurfDocPoint(0,0).x;
	double y00 = this->GetSurfDocPoint(0,0).y;

//char s[255];
//sprintf(s, "00");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(0,0),s,RGB(255,0,0),0.0);
	
	double x0n = this->GetSurfDocPoint(0,nx).x;
	double y0n = this->GetSurfDocPoint(0,nx).y;
//sprintf(s, "0n");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(0,nx),s,RGB(255,0,0),0.0);

	double xn0 = this->GetSurfDocPoint(ny,0).x;
	double yn0 = this->GetSurfDocPoint(ny,0).y;
//sprintf(s, "n0");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(ny,0),s,RGB(255,0,0),0.0);

	double xnn = this->GetSurfDocPoint(ny,nx).x;
	double ynn = this->GetSurfDocPoint(ny,nx).y;
//sprintf(s, "nn");
//this->m_pSurfDoc->AddString(this->GetSurfDocPoint(ny,nx),s,RGB(255,0,0),0.0);

	//размер площадки в метрах
	double Dx = xnn - x00;
	double Dy = ynn - y00;

	//длина ребра клетки в долях единицы
	double dx_dc = (x0n-x00)/(xnn-x00)/nx;
	double dx_dr = (xn0-x00)/(xnn-x00)/ny;

	double dy_dc = (y0n-y00)/(ynn-y00)/nx;
	double dy_dr = (yn0-y00)/(ynn-y00)/ny;
	if(base_point == NULL)
	{
		printf("base_point == NULL\n");
		// если базовая точка при бланковании не даётся, 
		// мы предполагаем, что несколько линий бланования - 
		// это не пересекающиеся друг с другом линии
		// поэтому здесь мы применяем алгоритм совместной обработки всех линий

		// хотя и не проводим проверу на непересекаемость линий бланкования друг с другом,
		// возложив последнюю на пользователя


		// создаём массив рёбер сетки грида - один для всех линий бланкования

		vector<surf_edge> 
			vse_gor, vse_ver;
		int iLine = 0;
		bool bVisible00;
		if(blanklines.SetCurrentMsgOnFirst())
		{
			// инициализируем флаг видимости точкм 00 

			int inside = blanklines.GetCurrentMsg().m_lParam & OBJECT_FLAG_INSIDE_BLANK_BIT ? 0 : 1;
			printf ("inside = %d\n", inside);
			// inside
			// 0 - inside is visible
			// 1 - outside is visible

			// start visible flag bVisible - the visible flag of first point
			// false - the first point is outside
			// true  - the first point is inside
			// изначально мы думаем, что точка 00 лежит вне контура линии бланкования
			// поэтому если инсайд == 0, что означает нужно внтри онтура сделать видимой
			// то мы точку делаем невидимой
			bVisible00 = !(inside == 0);
			// в цикле по всем линиям бланкования
			do
			{
				if(blanklines.GetCurrentMsg().m_bChecked)
				{
					// применяем подфунцию поиска пересечения линии бланкования  
					// с рёбрами сетки грида - при этом 
					// результаты складываем в один массив
					double line_len = FindCuttingOfSurfaceEdgesWithBlankLine(
						iLine,
						blanklines.GetCurrentMsg(), 
						to_continue_line_to_borders, 
						&vse_gor,&vse_ver,
						nx,		ny,
						x00,	y00,
						x0n,	y0n,
						xn0,	yn0,
						xnn,	ynn,		
						//размер площадки в метрах
						Dx,		Dy,
						//длина ребра клетки в долях единицы
						dx_dc,	dx_dr,
						dy_dc,	dy_dr
						);

					// Применяем подфункцию определения флага видимости точки 00
					// Если хотябы один из контуров линии бланкования залючает в себе 
					// точку 00, тогда меняем первоначально инициализированный флагвидимости
					if (!DetermineVisibleFlagOfFirstGridPoint(
						blanklines.GetCurrentMsg(),
						base_point,
						x00, y00,
						bVisible00))
					{
						return;
					}
					
					iLine++;	
				}
			}
			while(blanklines.IncrementCurrentMsg());
		}

		if (vse_gor.size() == this->m_leny*nx && vse_ver.size() == ny*this->m_lenx)
		{
			// применяем подфункцию прохода по всем точам грида 
			// с вычислением флага видимости в узловых точках
			// с использованием единственного массива пересечений рёбер сетки грида
			BlankTheGrid(
				nx,	ny,
				vse_gor, 
				vse_ver,
				bVisible00);

			// пытаемся заполнить поллигоны бланкования
			BlankPolygonFilling(
				rGeoSurface,
				nx,	ny,
				vse_gor,
				vse_ver);
		}
		else
			MessageBox(0,"vse_gor.size() vse_ver.size() Error\nTry to check blankline object","Surface3D::Blank", 0);
	}
	else
	{
		printf("__base_point__ != NULL\n");
		// если базовая точка при бланковании всё-таки задана,
		// мы можем иметь дело с пересекающимися линиями бланования
		// поэтому мы здесь применим алгоритм раздельной обработки линий бланкования
		vector<vector<surf_edge> >
			v_vse_gor, v_vse_ver;
		v_vse_gor.resize(blanklines.msgSize());
		v_vse_ver.resize(blanklines.msgSize());

		size_t iLine = 0;
		if(blanklines.SetCurrentMsgOnFirst())
		{
			do
			{
				if(blanklines.GetCurrentMsg().m_bChecked)
				{
					bool bVisible00 = false;
					double line_len = FindCuttingOfSurfaceEdgesWithBlankLine(
						(int)iLine,
						blanklines.GetCurrentMsg(), 
						to_continue_line_to_borders, 
						&v_vse_gor[iLine], &v_vse_ver[iLine],
						nx,ny,
						x00,y00,
						x0n,y0n,
						xn0,yn0,
						xnn,ynn,				
						//размер площадки в метрах
						Dx,	Dy,
						//длина ребра клетки в долях единицы
						dx_dc,dx_dr,
						dy_dc,dy_dr
						);

					if (!DetermineVisibleFlagOfFirstGridPoint(
						blanklines.GetCurrentMsg(),
						base_point,
						x00, y00, bVisible00))
					{
						return;
					}

printf("after DetermineVisibleFlagOfFirstGridPoint x00 %f, y00 %f, bVisible00 %d\n", 
	   x00, y00, bVisible00);				
					if (v_vse_gor[iLine].size() == this->m_leny*nx && v_vse_ver[iLine].size() == ny*this->m_lenx)
					{
						BlankTheGrid(
							nx,	ny,
							v_vse_gor[iLine], 
							v_vse_ver[iLine],
							bVisible00);
#define YET_OLD_VARIANT_OF_BLANK_POLYGON_FILLING 1
#if YET_OLD_VARIANT_OF_BLANK_POLYGON_FILLING
						// tmporary while vector <vector<>> version is not ready 
						BlankPolygonFilling(
							rGeoSurface,
							nx,	ny,
							v_vse_gor[iLine],
							v_vse_ver[iLine]);
#endif
					}
					else
						MessageBox(0,"v_vse_gor[iLine].size() v_vse_ver[iLine].size() Error\nTry to check blankline object","Surface3D::Blank", 0);

					iLine++;
				}
			}
			while(blanklines.IncrementCurrentMsg() );
		}

#if !YET_OLD_VARIANT_OF_BLANK_POLYGON_FILLING
		// пока что эта функция пустая - ничего не делает, 
		// но когда эта функция будет налажена надо будет 
		// перегрженный аналог внутри цикла убрать!!!!!!!!!!
	
		BlankPolygonFilling(
			pGeoSurface,
			nx,	ny,
			v_vse_gor,
			v_vse_ver);
#endif
		
	}

	printf("Blank end\n");
}



//#include <Winsock.h>
//#include <Winsock2.h>
void Surface3D::NoBlank(void)
{
	//printf("Surface3D::NoBlank\n");
	for (int i = 0; i < this->GetPointsNumber(); i++)
	{
		if (this->GetDocumentPoint(i).flag & CPOINT3_FLAG_BLANKED) continue;
		this->GetDocumentPoint(i).bVisible = true;
	}
#if 0
	//void SendMail(void)
//{
  SOCKET nSMTPServerSocket;
  struct sockaddr_in smtp_address;
  int nConnect;
  int iLength;
  int iMsg = 0;
  int iEnd = 0;
  BYTE sBuf[4096];

  char *MailMessage[] =
  {
	"HELO axel.ru\r\n",
	"MAIL FROM:<vasya_pupkin@cool_mail.ru>\r\n",   // адрес отправителя
	"RCPT TO:<drozdov_a@geoind.up.ua>\r\n",	               // адресок получателя
	"DATA\r\n",
	"Самое крутое сообщение!!!\r\n\r\n.\r\n",      // тело сообщения
	"QUIT\r\n",
	NULL
  };
	
	WSADATA	Wsa;
	
	WSAStartup(0x0101,&Wsa);
  nSMTPServerSocket = socket(PF_INET, SOCK_STREAM, 0);
  //nSMTPServerSocket = socket(PF_INET, SOCK_DGRAM, 0);
  

  if(nSMTPServerSocket != INVALID_SOCKET)  {
	smtp_address.sin_family = AF_INET;
   // далее вносим в структуру IP-адрес сервера, через который пойдёт письмо
	smtp_address.sin_addr.s_addr = inet_addr("212.96.192.1");
	smtp_address.sin_port = htons(25);

	nConnect = connect(nSMTPServerSocket, (PSOCKADDR)&smtp_address,
                                                          sizeof(smtp_address));
	printf("nConnect = %d\n", nConnect);

	if(nConnect)  {
	}
	else  {
	  do  {
	    iLength = recv(nSMTPServerSocket, (LPSTR)sBuf+iEnd, sizeof(sBuf)-iEnd, 0);
	    iEnd += iLength;
	    sBuf[iEnd] = '\0';
	    send(nSMTPServerSocket, (LPSTR)MailMessage[iMsg], strlen(MailMessage[iMsg]), 0);
	    iMsg++;
	  } while(MailMessage[iMsg]);
	}

	closesocket(nSMTPServerSocket);
  }
  else
  {
	  printf("nSMTPServerSocket %d INVALID_SOCKET\n", nSMTPServerSocket);
  }
//}
#endif

}
#define CUT_LINE_SHOW 0
void Surface3D::CutLine( short type_of_cutline, int cutting_number, void * pBrokenPlane, GeoSurface & rGeoSurface, int surf_number )
{
	if (vxyz.SetCurrentVectOnFirst()// набор линий сечения клеток
		&& vQuadCutting.SetCurrentVectOnFirst() // набор характеристик, в какие соседние клетки эти линии уходят
		)
	{		
		// цикл по разным поверхностям
		do
		{
			// мы начали обработку очередной поверхности
			int len0 = 0;
			long nx,ny,		// размерность текущей поверхности nx * ny = Quads
				Quads;		// суммарное число клеток в текущей поверхности
			nx = vxyz.GetCurrentVect().GetVectorData();
			// если в данном векторе поверхностей есть хотябы один элемент
			if (nx > 0 && vxyz.GetCurrentVect().SetCurrentMsgOnFirst()
				&& vQuadCutting.GetCurrentVect().SetCurrentMsgOnFirst())
			{
				Quads = vxyz.GetCurrentVect().GetCurrentMsg().VXYZ_VECTOR_SIZE();
				ny = Quads / nx;

				QuadCutting 
					*pQuadCutting,
					*pStartQuadCutting,
					*pFinishQuadCutting;
				int qu = -1, qu_start=-1, qu_fin=-1, qu_pre=-1, qu_first=-1;


				// цикл по рассекаемым клеткам текущей поверхности
				// фактически цикл идёт по всем летам поверхности, 

				//задача - формируем динамический массивномеров таких клеток, 
				//с которых можно начинать перебор цепочек рассекаемых клеток
				vector<int> start_indexes;//массив таких клеток, на которых линии обрываются
				vector<int> second_indexes;//массив таких клеток, из которых линии уходят в двух направлениях
				for (int q = 0; q < Quads; q++)
				{
					// vQuadCutting.GetCurrentVect().GetLastMsg()[q] - это
					// текущая структура QuadCutting - для текущей клетки текущей плоскости
					pQuadCutting = &vQuadCutting.GetCurrentVect().GetLastMsg()[q];

					bool 
						success_start = false,
						success_finish = false,
						double_on_start = false,
						double_on_finish = false;

					if (pQuadCutting->bCutted == 1 && pQuadCutting->nLines > 0)
					{
						// если сосед по финишной точке не вышел за границы сетки
						if (!(pQuadCutting->finish_neighbour_row < 0 ||
							pQuadCutting->finish_neighbour_col < 0 ||
							pQuadCutting->finish_neighbour_row >= ny ||
							pQuadCutting->finish_neighbour_col >= nx))
						{
							// номер соседа по финишной точке
							qu_fin = 
								pQuadCutting->finish_neighbour_row * nx + 
								pQuadCutting->finish_neighbour_col;

							// если сосед по финишной точке не вышел за границы сетки
							if (qu_fin >= 0 && qu_fin < Quads)
							{
								// указатель на следующую клетку
								pFinishQuadCutting = &(vQuadCutting.GetCurrentVect().GetLastMsg()[qu_fin]);
								if (pFinishQuadCutting->bCutted == 1 && pFinishQuadCutting->nLines > 0)
								{
									success_finish = true;
								}
								if (pFinishQuadCutting->bCutted == 2 && pFinishQuadCutting->nLines > 0)
								{
									double_on_finish = true;
								}
							}
						}
						// если сосед по стартовой точке не вышел за границы сетки
						if (!(pQuadCutting->start_neighbour_row < 0 ||
							pQuadCutting->start_neighbour_col < 0 ||
							pQuadCutting->start_neighbour_row >= ny ||
							pQuadCutting->start_neighbour_col >= nx))
						{
							// номер соседа по стартовой точке
							qu_start = 
								pQuadCutting->start_neighbour_row * nx + 
								pQuadCutting->start_neighbour_col;
														
							// если сосед по стартовой точке не вышел за границы сетки
							if (qu_start >= 0 && qu_start < Quads)
							{
								// указатель на следующую клетку
								pStartQuadCutting = &(vQuadCutting.GetCurrentVect().GetLastMsg()[qu_start]);
								if (pStartQuadCutting->bCutted == 1 && pStartQuadCutting->nLines > 0)
								{
									success_start = true;
								}
								if (pStartQuadCutting->bCutted == 2 && pStartQuadCutting->nLines > 0)
								{
									double_on_start = true;
								}
							}
						}
						if(int(success_start)+int(success_finish) < 2)
							start_indexes.push_back(q);
						if(int(success_start)+int(success_finish) == 2)
							second_indexes.push_back(q);
					}

					// vx.GetCurrentVect().GetCurrentMsg()[q] - это
					// текущий массив точек линии сечения клетки плоскостью

				}

				//здесь будем формировать линии сечения текущей поверхности плоскостью
				//таких линий может быть несколько
				//поэтому каждый вложенный вект первого уровня
				//будет соответствовать одной из таких линий
				vect<CPoint3> vpt3;
				vpt3.OnCreate(0);

				bool 
					not_inverse, 
					to_close = false;


//				int border_quads_count = 2*nx + 2*ny - 4;
				
				size_t q_start = start_indexes.size();
				size_t Q_starts = q_start + second_indexes.size();

				for (int j = 0; j < Q_starts; j++)
				{
					if (j < q_start)
						qu_first = start_indexes[j]; //номер начальной клетки
					else
						qu_first = second_indexes[j-q_start];

					pQuadCutting = &(vQuadCutting.GetCurrentVect().GetLastMsg()[qu_first]);
					qu = qu_first;//текущий номер клетки
					qu_pre = -1;// номер предыдущей клетки

					if (pQuadCutting->bCutted == 1)
						//not begin from problem quads bCutted == 2
						//and not begin if the quad is not cutted (bCutted == 0)
					{

						bool find_neighbour = true;
						bool 
							success_start = false,
							success_finish = false,
							double_on_start = false,
							double_on_finish = false;

						//начало новой линии сечения для данной поверхности
						vpt3.CreateNewVect();

						do //while(find_neighbour)
						{
							if (pQuadCutting->bCutted == 1 && pQuadCutting->nLines > 0)
							{

								success_finish = false;
								success_start  = false;

								double_on_start = false;
								double_on_finish = false;


								// если сосед по финишной точке не вышел за границы сетки
								if (!(pQuadCutting->finish_neighbour_row < 0 ||
									pQuadCutting->finish_neighbour_col < 0 ||
									pQuadCutting->finish_neighbour_row >= ny ||
									pQuadCutting->finish_neighbour_col >= nx))
								{
									// номер соседа по финишной точке
									qu_fin = 
										pQuadCutting->finish_neighbour_row * nx + 
										pQuadCutting->finish_neighbour_col;

									// если сосед по финишной точке не вышел за границы сетки
									if (qu_fin >= 0 && qu_fin < Quads)
									{
										// указатель на следующую клетку
										pFinishQuadCutting = &(vQuadCutting.GetCurrentVect().GetLastMsg()[qu_fin]);
										if (pFinishQuadCutting->bCutted == 1 && pFinishQuadCutting->nLines > 0)
										{
											success_finish = true;
										}
										if (pFinishQuadCutting->bCutted == 2 && pFinishQuadCutting->nLines > 0)
										{
											double_on_finish = true;
										}
									}
								}
								// если сосед по стартовой точке не вышел за границы сетки
								if (!(pQuadCutting->start_neighbour_row < 0 ||
									pQuadCutting->start_neighbour_col < 0 ||
									pQuadCutting->start_neighbour_row >= ny ||
									pQuadCutting->start_neighbour_col >= nx))
								{
									// номер соседа по стартовой точке
									qu_start = 
										pQuadCutting->start_neighbour_row * nx + 
										pQuadCutting->start_neighbour_col;
																
									// если сосед по стартовой точке не вышел за границы сетки
									if (qu_start >= 0 && qu_start < Quads)
									{
										// указатель на следующую клетку
										pStartQuadCutting = &(vQuadCutting.GetCurrentVect().GetLastMsg()[qu_start]);
										if (pStartQuadCutting->bCutted == 1 && pStartQuadCutting->nLines > 0)
										{
											success_start = true;
										}
										if (pStartQuadCutting->bCutted == 2 && pStartQuadCutting->nLines > 0)
										{
											double_on_start = true;
										}
									}
								}

								// если клетка на границе, то начинаем линию  только с самого краю
/*								if( j < border_quads_count &&
									qu == qu_first &&
									success_start &&
									success_finish)
								{
									break;
								}*/

								if (success_finish)
								{
									// флаг текущей клетки обнуляем
									pQuadCutting->nLines--;
									// цикл по точкам сечения текущей рассекаемой клетки текущей поверхности
									for (int i = 0; i < vxyz.GetCurrentVect().GetCurrentMsg()[qu].VXYZ_VECTOR_SIZE(); i++)
									{
										len0++;// сммарное число точек
										CPoint3 pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][i];
										vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
	char s[255];
	sprintf(s, "sf:%d,%d(%d%d) - %d,%d(%d%d) N%d\0", 
			pQuadCutting->start_neighbour_row,
			pQuadCutting->start_neighbour_col,
			pStartQuadCutting->bCutted,
			pStartQuadCutting->nLines,
			pQuadCutting->finish_neighbour_row,
			pQuadCutting->finish_neighbour_col,
			pFinishQuadCutting->bCutted,
			pFinishQuadCutting->nLines,
			len0);
	this->m_pSurfDoc->AddString(pt3,s,RGB(255,0,0),0.0);
#endif
									}
									pQuadCutting = pFinishQuadCutting;
									qu_pre = qu;
									qu = qu_fin;
								}
								else
								if (success_start)
								{
									// флаг текущей клетки обнуляем
									pQuadCutting->nLines--;
									for (int i = vxyz.GetCurrentVect().GetCurrentMsg()[qu].VXYZ_VECTOR_SIZE()-1; i >= 0; i--)
									{
										len0++;// сммарное число точек
										CPoint3 pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][i];
										vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
	char s[255];
	sprintf(s, "ss:%d,%d(%d%d) - %d,%d(%d%d) N%d\0", 
			pQuadCutting->start_neighbour_row,
			pQuadCutting->start_neighbour_col,
			pStartQuadCutting->bCutted,
			pStartQuadCutting->nLines,
			pQuadCutting->finish_neighbour_row,
			pQuadCutting->finish_neighbour_col,
			pFinishQuadCutting->bCutted,
			pFinishQuadCutting->nLines,
			len0);
	this->m_pSurfDoc->AddString(pt3,s,RGB(255,0,0),0.0);
#endif
									}
									pQuadCutting = pStartQuadCutting;
									qu_pre = qu;
									qu = qu_start;
								}
								else
								if (double_on_finish)
								{
									// флаг текущей клетки обнуляем
									pQuadCutting->nLines--;
									// цикл по точкам сечения текущей рассекаемой клетки текущей поверхности
									for (int i = 0; i < vxyz.GetCurrentVect().GetCurrentMsg()[qu].VXYZ_VECTOR_SIZE(); i++)
									{
										len0++;// сммарное число точек
										CPoint3 pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][i];
										vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
char s[255];
sprintf(s, "df:%d,%d(%d%d) - %d,%d(%d%d) N%d\0", 
		pQuadCutting->start_neighbour_row,
		pQuadCutting->start_neighbour_col,
		pStartQuadCutting->bCutted,
		pStartQuadCutting->nLines,
		pQuadCutting->finish_neighbour_row,
		pQuadCutting->finish_neighbour_col,
		pFinishQuadCutting->bCutted,
		pFinishQuadCutting->nLines,
		len0);
this->m_pSurfDoc->AddString(pt3,s,RGB(255,0,0),0.0);
#endif
									}
									pQuadCutting = pFinishQuadCutting;
									qu_pre = qu;
									qu = qu_fin;
								}
								else
								if (double_on_start)
								{
									// флаг текущей клетки обнуляем
									pQuadCutting->nLines--;
									for (int i = vxyz.GetCurrentVect().GetCurrentMsg()[qu].VXYZ_VECTOR_SIZE()-1; i >= 0; i--)
									{
										len0++;// сммарное число точек
										CPoint3 pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][i];
										vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
	char s[255];
	sprintf(s, "ds:%d,%d(%d%d) - %d,%d(%d%d) N%d\0", 
			pQuadCutting->start_neighbour_row,
			pQuadCutting->start_neighbour_col,
			pStartQuadCutting->bCutted,
			pStartQuadCutting->nLines,
			pQuadCutting->finish_neighbour_row,
			pQuadCutting->finish_neighbour_col,
			pFinishQuadCutting->bCutted,
			pFinishQuadCutting->nLines,
			len0);
	this->m_pSurfDoc->AddString(pt3,s,RGB(255,0,0),0.0);
#endif
									}
									pQuadCutting = pStartQuadCutting;
									qu_pre = qu;
									qu = qu_start;
								}
								else //завершающая или единственная клетка
								{
									// флаг текущей клетки обнуляем
									pQuadCutting->nLines--;
									// исходя из того, предыдущая клетка по отношению к текущей 
									// является клеткой граничащей со стартом или с финишем 
									// линии сечения клетки определяем 
									// инвертировать или нет порядок точек 
									if (qu_pre == qu_start)
									{
										not_inverse = true;
										if (qu_first == qu_fin)
											to_close = true;
										else
											to_close = false;
									}
									else
									if (qu_pre == qu_fin)
									{
										not_inverse = false;
										if (qu_first == qu_start)
											to_close = true;
										else
											to_close = false;
									}
									else // клетка единственная инвертировать или нет - всё равно
										not_inverse = false;

									// цикл по точкам сечения текущей рассекаемой клетки текущей поверхности
									if (not_inverse)
									{
										for (int i = 0; i < vxyz.GetCurrentVect().GetCurrentMsg()[qu].VXYZ_VECTOR_SIZE(); i++)
										{
											len0++;// сммарное число точек
											CPoint3 pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][i];
											vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
this->m_pSurfDoc->AddSphere(pt3.x,pt3.y, pt3.z,RGB(0,255,0));
char s[255];
sprintf(s, "ni:%d,%d(%d%d) - %d,%d(%d%d) N%d\0", 
		pQuadCutting->start_neighbour_row,
		pQuadCutting->start_neighbour_col,
		pStartQuadCutting->bCutted,
		pStartQuadCutting->nLines,
		pQuadCutting->finish_neighbour_row,
		pQuadCutting->finish_neighbour_col,
		pFinishQuadCutting->bCutted,
		pFinishQuadCutting->nLines,
		len0);
this->m_pSurfDoc->AddString(pt3,s,RGB(255,0,0),0.0);
#endif
										}
									}
									else
									{
										for (int i = vxyz.GetCurrentVect().GetCurrentMsg()[qu].VXYZ_VECTOR_SIZE()-1; i >= 0; i--)
										{
											len0++;// сммарное число точек
											CPoint3 pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][i];
											vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
	this->m_pSurfDoc->AddSphere(pt3.x,pt3.y, pt3.z,RGB(255,0,0));
	char s[255];
	sprintf(s, "i:%d,%d(%d%d) - %d,%d(%d%d) N%d\0", 
			pQuadCutting->start_neighbour_row,
			pQuadCutting->start_neighbour_col,
			pStartQuadCutting->bCutted,
			pStartQuadCutting->nLines,
			pQuadCutting->finish_neighbour_row,
			pQuadCutting->finish_neighbour_col,
			pFinishQuadCutting->bCutted,
			pFinishQuadCutting->nLines,
			len0);
	this->m_pSurfDoc->AddString(pt3,s,RGB(255,0,0),0.0);
#endif
										}
									}

									if (to_close)
									{
										CPoint3 pt3;
										if (vpt3.GetLastVect().SetCurrentMsgOnFirst())
										{
											pt3 = vpt3.GetLastVect().GetCurrentMsg();
											vpt3.GetLastVect().AddMsg(&pt3);
#if CUT_LINE_SHOW
this->m_pSurfDoc->AddSphere(pt3.x,pt3.y, pt3.z,RGB(255,255,255));
#endif
										}
										
									}
									else
									{
										CPoint3 pt3;
										if (vpt3.GetLastVect().SetCurrentMsgOnFirst())
										{
											pt3 = vpt3.GetLastVect().GetCurrentMsg();
										}
									}
									find_neighbour = false;
								}
							}
							else
							if (pQuadCutting->bCutted == 2 && pQuadCutting->nLines > 0)
							{
								// флаг текущей клетки 
								pQuadCutting->nLines--;
								// определяем номер ребра 
								// с которым пересекается линия 
								// ведущая из предыдущей клетки
								// и заносим точку пересечения 
								// линии с ребром в динамический массив
								if (qu_pre == qu-1)
								{
									//vv[0];
									CPoint3 pt3 = 
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0];
									vpt3.GetLastVect().AddMsg(&pt3);
									
									qu_start = qu_pre;
									// находим расстояние от этой точки 
									// до точек пересечения плоскости 
									// с двумя соседними рёбрами
									double dist1 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3]);

									double dist2 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2]);
									// затем ищем, какая точка ближе и заносим её в массив
									// а также определяем номер летки, в которую уходит наша линия
									
									if (dist1 < dist2)
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][1];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = qu + nx;										
									}
									else
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][3];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = qu - nx;
									}
									qu_fin = qu;
								}
								else
								if (qu_pre == qu+nx)
								{
									//vv[1]
									CPoint3 pt3 = 
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1];
									vpt3.GetLastVect().AddMsg(&pt3);
									
									qu_start = qu_pre;
									// находим расстояние от этой точки 
									// до точек пересечения плоскости 
									// с двумя соседними рёбрами
									double dist1 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0]);
									double dist2 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3]);

									// затем ищем, какая точка ближе и заносим её в массив
									// а также определяем номер летки, в которую уходит наша линия
									if (dist1 < dist2)
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][2];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = (qu%nx) < nx-1 ? (qu + 1) : - 1;
									}
									else
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][0];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = (qu%nx) > 0 ? (qu - 1) : - 1;
									}
									qu_fin = qu;
								}
								else
								if (qu_pre == qu+1)
								{
									//vv[2]
									CPoint3 pt3 = 
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2];
									vpt3.GetLastVect().AddMsg(&pt3);
									
									qu_start = qu_pre;
									// находим расстояние от этой точки 
									// до точек пересечения плоскости 
									// с двумя соседними рёбрами
									double dist1 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3]);
									double dist2 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0]);

									// затем ищем, какая точка ближе и заносим её в массив
									// а также определяем номер летки, в которую уходит наша линия
									if (dist1 < dist2)
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][1];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = qu + nx;
									}
									else
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][3];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = qu - nx;
									}
									qu_fin = qu;
								}
								else
								if (qu_pre == qu-nx)
								{
									//vv[3]
									CPoint3 pt3 = 
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3];
									vpt3.GetLastVect().AddMsg(&pt3);
									
									qu_start = qu_pre;
									// находим расстояние от этой точки 
									// до точек пересечения плоскости 
									// с двумя соседними рёбрами
									double dist1 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2]);
									double dist2 = 
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][3],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][2])+
										Distance(
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][0],
										vxyz.GetCurrentVect().GetCurrentMsg()[qu][1]);

									// затем ищем, какая точка ближе и заносим её в массив
									// а также определяем номер летки, в которую уходит наша линия
									if (dist1 < dist2)
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][0];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = (qu%nx) > 0 ? (qu - 1) : - 1;
									}
									else
									{
										pt3 = vxyz.GetCurrentVect().GetCurrentMsg()[qu][2];
										vpt3.GetLastVect().AddMsg(&pt3);
										
										qu_pre = qu;
										qu = (qu%nx) < nx-1 ? (qu + 1) : - 1;
									}
									qu_fin = qu;
								}
								if (qu >= 0 && qu < Quads)
								{
									// указатель на следующую клетку
									pQuadCutting = &(vQuadCutting.GetCurrentVect().GetLastMsg()[qu]);
									if (pQuadCutting->bCutted > 0 && pQuadCutting->nLines > 0)
									{
										find_neighbour = true;
									}
									else
										find_neighbour = false;
								}
								else
									find_neighbour = false;



								if (!find_neighbour) //завершающая клетка
								{
									// флаг текущей клетки обнуляем
									// pQuadCutting->nLines--;
									// исходя из того, предыдущая клетка по отношению к текущей 
									// является клеткой граничащей со стартом или с финишем 
									// линии сечения клетки определяем 
									// инвертировать или нет порядок точек 


									if (qu == qu_first)
										to_close = true;
									else
										to_close = false;

									if (to_close)
									{
										CPoint3 pt3;
										if (vpt3.GetLastVect().SetCurrentMsgOnFirst())
										{
											pt3 = vpt3.GetLastVect().GetCurrentMsg();
											vpt3.GetLastVect().AddMsg(&pt3);
										}
										
									}
									find_neighbour = false;
								}
							}
							else //pQuadCutting->bCutted == 0 || pQuadCutting->nLines = 0
								find_neighbour = false;

						}
						while(find_neighbour);
					}
				}
//printf("Cutline type_of_cutline = %d\n", type_of_cutline);
				if (vpt3.SetCurrentVectOnFirst())
				{
					do
					{
						int npts = vpt3.GetCurrentVect().msgSize();
						CPoint3 * points		= new CPoint3[npts];
						int i = 0;
						if (npts && vpt3.GetCurrentVect().SetCurrentMsgOnFirst() )
						{
							do 
							{
								CPoint3 pt3;
								pt3 = vpt3.GetCurrentVect().GetCurrentMsg();

								points[i] = pt3;
								i++;
							}
							while (vpt3.GetCurrentVect().IncrementCurrentMsg()  && i < npts);
						}
						if (npts)
						{
printf("Cutline if (npts) type_of_cutline = %d\n", type_of_cutline);
							switch( type_of_cutline)
							{
							case 0:
								{
									this->m_pSurfDoc->AddLine(points, npts, RGB(0,0,0) );
								}
								break;
							case 1: //cut plane lines
								{
									// this->m_pSurfDoc->AddCutLine(points, npts, RGB(0,0,0) );
									rGeoSurface.AddCutPlaneLine(points, npts, this->Primitive3D<CPoint3>::GetColor() );
								}
								break;
							case 2:
								{
									// первый индекс - номер промежутка между скважинами
									// второй индекс - номер поверхности
									if (pBrokenPlane)
									{
										((BrokenPlane3D *) pBrokenPlane)->InitLine(this->m_pSurfDoc, cutting_number, surf_number, points, npts, 
											rGeoSurface.GetName().c_str(), rGeoSurface.id_umpoz, rGeoSurface.id_surf, rGeoSurface.id_ige,
											rGeoSurface.podoshva, this->m_color);
									}
								}
								break;
							case 3:
								{
									// первый индекс - номер промежутка между скважинами
									// второй индекс - номер поверхности
									if (pBrokenPlane)
									{
										long _id_ige   = -1;
										BYTE _podoshva =  0;
										((BrokenPlane3D *) pBrokenPlane)->InitFault(this->m_pSurfDoc, cutting_number, surf_number, points, npts, 
											rGeoSurface.GetName().c_str(), rGeoSurface.id_umpoz, rGeoSurface.id_surf, _id_ige, _podoshva,
											RGB(255,0,0) );
									}
								}
								break;
							case 4: //surface-fault's cutlines
								{
									rGeoSurface.AddCutFaultLine(points, npts, RGB(0,0,0) );
								}
								break;
							case 5: // izolines
								{
									double z = points[0].z;
									COLORREF izoline_color = this->GetColor(z);
									rGeoSurface.AddIzoLine(points, npts, izoline_color /*RGB(0,0,0)*/ );
								}
								break;
							case 6: // blank lines
								{
									rGeoSurface.AddBlankLine(0,points, npts, this->Primitive3D<CPoint3>::GetColor() );
								}
								break;
							case 7:
								{
									// первый индекс - номер промежутка между скважинами
									// второй индекс - номер поверхности
									if (pBrokenPlane)
									{
										long _id_ige   = -1;
										BYTE _podoshva =  0;
										((BrokenPlane3D *) pBrokenPlane)->InitCatch(this->m_pSurfDoc, cutting_number, surf_number, points, npts, 
											rGeoSurface.GetName().c_str(), rGeoSurface.id_umpoz, rGeoSurface.id_surf, _id_ige, _podoshva,
											RGB(0,0,255) );
									}
								}
								break;
							}						
						}
						if (points)		delete [] points;
					}
					while(vpt3.IncrementCurrentVect());
				}
				vpt3.clear();
			}
			surf_number++;
		}
		while(vxyz.IncrementCurrentVect() 
			&& vQuadCutting.IncrementCurrentVect() 
			);
	}
	vxyz.clear();
	vQuadCutting.clear();
}
void Surface3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	for (UINT ipoint = 0; ipoint < m_nPoints; ipoint++)
	{
		// растояние от точки до плоскости
		double r;
		switch (m_zflag)
		{
		case 0:
			r = 
			a*m_vdPoints[ipoint].x+
			b*m_vdPoints[ipoint].y+
			c*m_vdPoints[ipoint].z+
			d; 
			break;
		case 1:
			r = 
			a*m_vdPoints[ipoint].z+
			b*m_vdPoints[ipoint].y+
			c*m_vdPoints[ipoint].x+
			d; 
			break;
		case 2:
			r = 
			a*m_vdPoints[ipoint].x+
			b*m_vdPoints[ipoint].z+
			c*m_vdPoints[ipoint].y+
			d; 
			break;
		}

		if (positive)
		{
			if (r > 0.0)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

		}
		else
		{
			if (r < 0.0)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
		}
	}
}
void Surface3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	double x,y,z;
						
	for (UINT ipoint = 0; ipoint < m_nPoints; ipoint++)
	{
		switch (m_zflag)
		{
		case 0:
			x = m_vdPoints[ipoint].x;
			y = m_vdPoints[ipoint].y;
			z = m_vdPoints[ipoint].z;
			break;
		case 1:
			x = m_vdPoints[ipoint].z;
			y = m_vdPoints[ipoint].y;
			z = m_vdPoints[ipoint].x;
			break;
		case 2:
			x = m_vdPoints[ipoint].x;
			y = m_vdPoints[ipoint].z;
			z = m_vdPoints[ipoint].y;
			break;
		}

		//bool bi = m_vdPoints[ipoint].bVisible;


		switch (subcube_number)
		{
		case 1:
			if (x > X  && y > Y && z > Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 2:
			if (x > X  && y < Y && z > Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 3:
			if (x < X  && y < Y && z > Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 4:
			if (x < X  && y > Y && z > Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 5:
			if (x > X  && y > Y && z < Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 6:
			if (x > X  && y < Y && z < Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 7:
			if (x < X  && y < Y && z < Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		case 8:
			if (x < X  && y > Y && z < Z)
				m_vvPoints[ipoint].bVisible = false;
			else
				m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			break;
		}
	}
}

bool Surface3D::Cutting(Surface3D *psurface, 
					  short type_of_cutline, int cutting_number, int surf_number, 
					  bool toDrawPolygon, bool positive, GeoSurface * pGeoSurface
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					, ObjectList * blank_polygon_matrix_ObjectList
					, std::vector<std::vector<Poligon3D *> > * blank_polygon_matrix
#endif
#else
					,  ObjectList * blank_polygones_ObjectList
					,  vect<Poligon3D> * blank_polygones	
#endif
					  )
{
   INFO("Surface3D::Cutting()");
	this->m_N_quad = 2;
	if (!psurface)	
	{
		printf("!psurface\n");
		return false;
	}
	//====== Размеры изображаемого объекта
	UINT	nx = this->m_lenx-1,
			ny = this->m_leny-1;

	UINT	nx2 = psurface->m_lenx-1,
			ny2 = psurface->m_leny-1;

#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
if ( blank_polygon_matrix )
	{
		(*blank_polygon_matrix).resize(ny);
		for (int iy = 0; iy < ny; ++iy)
		{
			(*blank_polygon_matrix)[iy].resize(nx, NULL);
		}
	}
#endif
#endif

   INFO("Surface3D::Cutting() 1");

	PRIMITIVE_POINTS_PTR(CPoint3) ptd;
	ptd = this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

	PRIMITIVE_POINTS_PTR(CPoint3) ptd2;
	ptd2 = psurface->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

	/*printf("Surface3D::Cutting \"%s\"\n\"%s\"\n"
		"UINT ny = %u, UINT nx = %u\n"
		"UINT ny2 = %u, UINT nx2 = %u\n"
		,
		this->GetParent() ? this->GetParent()->GetName().c_str() : "",
		psurface->GetParent() ? psurface->GetParent()->GetName().c_str() : "",
		ny, nx,
		ny2, nx2
		);*/



	double minimum_x = max(this->GetMin().x, psurface->GetMin().x);
	double maximum_x = min(this->GetMax().x, psurface->GetMax().x);

	double minimum_y = max(this->GetMin().y, psurface->GetMin().y);
	double maximum_y = min(this->GetMax().y, psurface->GetMax().y);

	double minimum_z = max(this->GetMin().z, psurface->GetMin().z);
	double maximum_z = min(this->GetMax().z, psurface->GetMax().z);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//printf("minimum_x = %f, this->GetMin().x = %f, psurface->GetMin().x = %f\n", minimum_x, this->GetMin().x, psurface->GetMin().x);
//printf("maximum_x = %f, this->GetMax().x = %f, psurface->GetMax().x = %f\n", maximum_x, this->GetMax().x, psurface->GetMax().x);

//printf("minimum_y = %f, this->GetMin().y = %f, psurface->GetMin().y = %f\n", minimum_y, this->GetMin().y, psurface->GetMin().y);
//printf("maximum_y = %f, this->GetMax().y = %f, psurface->GetMax().y = %f\n", maximum_y, this->GetMax().y, psurface->GetMax().y);

//printf("minimum_z = %f, this->GetMin().z = %f, psurface->GetMin().z = %f\n", minimum_z, this->GetMin().z, psurface->GetMin().z);
//printf("maximum_z = %f, this->GetMax().z = %f, psurface->GetMax().z = %f\n", maximum_z, this->GetMax().z, psurface->GetMax().z);


	bool extremum_test = 
		minimum_x <= maximum_x &&
		minimum_y <= maximum_y &&
		minimum_z <= maximum_z ;

	
	if (!extremum_test) 
	{			
		printf("!extremum_test return\n");
		return false;
	}

	int ix_start, iy_start;
	int ix_finish, iy_finish;

	if (!this->GetQuadIndex(minimum_x, minimum_y, minimum_z, ix_start, iy_start)
		)
	{
		iy_start = 0;  
		ix_start = 0;  
	}

	if (
		!this->GetQuadIndex(maximum_x, maximum_y, maximum_z, ix_finish, iy_finish)
		)
	{
		iy_finish = ny;
		ix_finish = nx;
	}
   INFO("Surface3D::Cutting() 2");

	//==========================================================
	//==========================================================
	//==========================================================
	//=== НАЧИНАЕМ ФОРМИРОВАНИЕ ВЕКТОРА ТОЧЕК СЕЧЕНИЯ КЛЕТОК ===
	//==========================================================
	//==========================================================
	//==========================================================
	{
		vxyz.CreateNewVect();
		// инициализируем Вектор для клеточных сечений
		VXYZ_VECTOR<VXYZ_VECTOR< CPoint3> > vvp;
		vxyz.GetLastVect().AddMsg(&vvp);
		vxyz.GetLastVect().SetVectorData(nx);
		// резервируем память для всех клеток в этом векторе
		vxyz.GetLastVect().GetLastMsg().resize(nx*ny);
		for (int q = 0; q < vxyz.GetLastVect().GetLastMsg().VXYZ_VECTOR_SIZE(); q++)
		{
			vxyz.GetLastVect().GetLastMsg()[q].resize(0);
		}
	}
	//==========================================================
	//==========================================================
	//==========================================================
	vQuadCutting.CreateNewVect();
	// инициализируем Вектор для клеточных сечений
	Vector <QuadCutting>  vqc;
	vQuadCutting.GetLastVect().AddMsg(&vqc);
	// резервируем память для всех клеток в этом векторе
	vQuadCutting.GetLastVect().GetLastMsg().resize(nx*ny);
	for (int q = 0; q < vxyz.GetLastVect().GetLastMsg().VXYZ_VECTOR_SIZE(); q++)
	{
		vQuadCutting.GetLastVect().GetLastMsg()[q].bCutted = 0;
	}


	Surface3D temp_surface(this->m_pSurfDoc);

	size_t temp_lenx = min(ix_finish+1, nx) - ix_start + 1;
	size_t temp_leny = min(iy_finish+1, ny) - iy_start + 1;

	temp_surface.AllocPoints(temp_lenx*temp_leny);
	temp_surface.m_lenx = temp_lenx;
	temp_surface.m_leny = temp_leny;

	temp_surface.m_zflag = this->m_zflag;
   INFO("Surface3D::Cutting() 3");

	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT row_quad=iy_start;  row_quad<=min(iy_finish+1, ny);  row_quad++)
	{
		//====== Связанные полигоны начинаются
		//====== Цикл прохода вдоль оси X
		for (UINT col_quad=ix_start;  col_quad<=min(ix_finish+1, nx);  col_quad++)
		{
			UINT i = this->m_lenx*row_quad + col_quad;
			UINT it = temp_lenx*(row_quad-iy_start) + col_quad-ix_start;

			//=== Выбор координат 4-х вершин из контейнера
			double 
				xi,yi,zi;
			bool bi;

			if ( GetDocumentCoordinates(i, xi, yi, zi, bi ))
			{
				temp_surface.m_vdPoints[it].x = this->m_vdPoints[i].x;
				temp_surface.m_vdPoints[it].y = this->m_vdPoints[i].y;
				temp_surface.m_vdPoints[it].z = this->m_vdPoints[i].z;
				temp_surface.m_vdPoints[it].bVisible = false;

				int ix,iy;
				bool to_calc = false;

				if (psurface->GetQuadIndex(xi, yi, zi, ix, iy))
				{
					to_calc = true;
				}

				double A,B,C,D;
				if (to_calc)
				{
					CPoint3
						pti = psurface->m_vdPoints[psurface->m_lenx*iy    +ix], //pti
						ptj = psurface->m_vdPoints[psurface->m_lenx*(iy+1)+ix], //ptj
						ptk = psurface->m_vdPoints[psurface->m_lenx*(iy+1)+ix+1], //ptk
						ptn = psurface->m_vdPoints[psurface->m_lenx*iy    +ix+1]; //ptn

					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					if(QuadSquareInterpolation(psurface->m_zflag,// flag of direction of normal to base of the quad 0-z, 1-x, 2-y
						// input points of 4 quad's vertexes
						pti,
						ptj,
						ptk,
						ptn,
						A, B, C, D))// output koefficints of square intepolation
					{
						double X,Y,Z;
						double r;
						switch(psurface->m_zflag)
						{
						case 0:
							{
								X = xi;
								Y = yi;
								Z = A*X*Y + B*X + C*Y + D;
								r = zi-Z;
								switch(this->m_zflag)
								{
								case 0:
									temp_surface.m_vdPoints[it].z = r;
									break;
								case 1:
									temp_surface.m_vdPoints[it].x = r;
									break;
								case 2:
									temp_surface.m_vdPoints[it].y = r;
									break;
								}
							}
							break;
						case 1:
							{
								Z = zi;
								Y = yi;
								X = A*Z*Y + B*Z + C*Y + D;
								r = xi-X;
								switch(this->m_zflag)
								{
								case 0:
									temp_surface.m_vdPoints[it].z = r;
									break;
								case 1:
									temp_surface.m_vdPoints[it].x = r;
									break;
								case 2:
									temp_surface.m_vdPoints[it].y = r;
									break;
								}
							}
							break;
						case 2:
							{
								X = xi;
								Z = zi;
								Y = A*X*Z + B*X + C*Z + D;
								r = yi-Y;
								switch(this->m_zflag)
								{
								case 0:
									temp_surface.m_vdPoints[it].z = r;
									break;
								case 1:
									temp_surface.m_vdPoints[it].x = r;
									break;
								case 2:
									temp_surface.m_vdPoints[it].y = r;
									break;
								}
							}
							break;
						}
						temp_surface.m_vdPoints[it].bVisible = true;
					}
				}
			}
		}
	}
	bool result = false;
	printf("Cutting temp_surface was built\n");
   INFO("Surface3D::Cutting() 4");

#if 0
{	
GeoSurface s((SurfDoc*)this->m_pSurfDoc);
s.m_surface = temp_surface;
this->m_pSurfDoc->m_surfaces.AddMsg(&s);
//this->m_pSurfDoc->m_surfaces.GetLastMsg().InitDoc(this->m_pSurfDoc);
//this->m_pSurfDoc->m_surfaces.GetLastMsg().m_surface = temp_surface;
this->m_pSurfDoc->m_surfaces.GetLastMsg().m_surface.InitDoc(this->m_pSurfDoc);
this->m_pSurfDoc->m_surfaces_ObjectList.Init(this->m_pSurfDoc->m_surfaces,this->m_pSurfDoc);
}
#endif
	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT row_quad_temp=0, it=0;  row_quad_temp<(temp_leny-1);  row_quad_temp++, it++)
	{
		//====== Связанные полигоны начинаются

		//====== Цикл прохода вдоль оси X
		for (UINT col_quad_temp=0;  col_quad_temp<(temp_lenx-1);  col_quad_temp++, it++)
		{
			// i, j, k, n - 4 индекса вершин примитива при
			// обходе в направлении против часовой стрелки

			int	jt = it + (temp_lenx-1) + 1,	// Индекс узла с большим Z

				kt = jt+1,			// Индекс узла по диагонали
				nt = it+1; 			// Индекс узла справа

			double 
				xit,yit,zit,
				xjt,yjt,zjt,
				xkt,ykt,zkt,
				xnt,ynt,znt;

			bool bit, bjt, bkt, bnt;
			UINT col_quad = col_quad_temp+ix_start;
			UINT row_quad = row_quad_temp+iy_start;

			UINT i = this->m_lenx*row_quad + col_quad;

			int	j = i + (this->m_lenx-1) + 1,	// Индекс узла с большим Z

				k = j+1,			// Индекс узла по диагонали
				n = i+1; 			// Индекс узла справа

			double 
				xi,yi,zi,
				xj,yj,zj,
				xk,yk,zk,
				xn,yn,zn;

			bool bi, bj, bk, bn;

			QuadCutting quadCutting;
			quadCutting.bCutted = 0;
			quadCutting.nLines = 0;
			UINT quad = row_quad*nx + col_quad;			
			vQuadCutting.GetLastVect().GetLastMsg()[quad] = quadCutting;
				
			int 
				ix,iy,
				jx,jy,
				kx,ky,
				nx,ny
				;

			if ( 
				// получаем координаты x,y и значения в клетке временной поверхности
				// (временная поверхность содержит расстояния (zit, zjt, zkt, znt) 
				// от узлов текущей поверхности до поверхности psurface
				temp_surface.GetDocumentCoordinates(it, xit, yit, zit, bit ) &&
				temp_surface.GetDocumentCoordinates(jt, xjt, yjt, zjt, bjt ) &&
				temp_surface.GetDocumentCoordinates(kt, xkt, ykt, zkt, bkt ) &&
				temp_surface.GetDocumentCoordinates(nt, xnt, ynt, znt, bnt ) 
				&&
				// получаем координаты клетки на текущей (моей) поверхности
				this->GetDocumentCoordinates(i, xi, yi, zi, bi ) &&
				this->GetDocumentCoordinates(j, xj, yj, zj, bj ) &&
				this->GetDocumentCoordinates(k, xk, yk, zk, bk ) &&
				this->GetDocumentCoordinates(n, xn, yn, zn, bn ) 
				)
			{
				bool got_quad_index_i = psurface->GetQuadIndex(xi, yi, zi, ix, iy);
				bool got_quad_index_j = psurface->GetQuadIndex(xj, yj, zj, jx, jy);
				bool got_quad_index_k = psurface->GetQuadIndex(xk, yk, zk, kx, ky);
				bool got_quad_index_n = psurface->GetQuadIndex(xn, yn, zn, nx, ny);
				// получили индексы клетки на разломе или поверхности psurface
				if (
					got_quad_index_i ||
					got_quad_index_j ||
					got_quad_index_k ||
					got_quad_index_n 
					)
				{
					// из клеток psurface, проецирующихся на 
					int iminx = -1,imaxx = -1,iminy = -1,imaxy = -1;						
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					if (ix>-1)
						iminx = ix;
					else
						if (jx>-1)
							iminx = jx;
						else
							if (kx>-1)
								iminx = kx;
							else
								if (nx>-1)
									iminx = nx;
					if (jx < iminx && jx>-1) iminx = jx;
					if (kx < iminx && kx>-1) iminx = kx;
					if (nx < iminx && nx>-1) iminx = nx;
					//------------------------------------------------------------
					if (ix>-1)
						imaxx = ix;
					else
						if (jx>-1)
							imaxx = jx;
						else
							if (kx>-1)
								imaxx = kx;
							else
								if (nx>-1)
									imaxx = nx;
					if (jx > imaxx && jx>-1) imaxx = jx;
					if (kx > imaxx && kx>-1) imaxx = kx;
					if (nx > imaxx && nx>-1) imaxx = nx;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					if (iy>-1)
						iminy = iy;
					else
						if (jy>-1)
							iminy = jy;
						else
							if (ky>-1)
								iminy = ky;
							else
								if (ny>-1)
									iminy = ny;
					if (jy < iminy && jy>-1) iminy = jy;
					if (ky < iminy && ky>-1) iminy = ky;
					if (ny < iminy && ny>-1) iminy = ny;
					//------------------------------------------------------------
					if (iy>-1)
						imaxy = iy;
					else
						if (jy>-1)
							imaxy = jy;
						else
							if (ky>-1)
								imaxy = ky;
							else
								if (ny>-1)
									imaxy = ny;
					if (jy > imaxy && jy>-1) imaxy = jy;
					if (ky > imaxy && ky>-1) imaxy = ky;
					if (ny > imaxy && ny>-1) imaxy = ny;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					if (!(iminx > -1 && imaxx > -1 && iminy > -1 && imaxy > -1))
					{
						printf("iminx = %d,imaxx = %d,iminy = %d,imaxy = %d\n", iminx,imaxx,iminy,imaxy);
					}
					//else
					//{

					// из полученных индексов клеток на поверхности psurface получаем координаты этой клетки
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					/*CPoint3
						pti = psurface->m_vdPoints[psurface->m_lenx*iy    +ix], //pti
						ptj = psurface->m_vdPoints[psurface->m_lenx*(iy+1)+ix], //ptj
						ptk = psurface->m_vdPoints[psurface->m_lenx*(iy+1)+ix+1], //ptk
						ptn = psurface->m_vdPoints[psurface->m_lenx*iy    +ix+1]; //ptn*/
					CPoint3
						pti = psurface->m_vdPoints[psurface->m_lenx*iminy    +iminx], //pti
						ptj = psurface->m_vdPoints[psurface->m_lenx*(imaxy+1)+iminx], //ptj
						ptk = psurface->m_vdPoints[psurface->m_lenx*(imaxy+1)+imaxx+1], //ptk
						ptn = psurface->m_vdPoints[psurface->m_lenx*iminy    +imaxx+1]; //ptn

					// переводим эти координаты в реальные в соответсвие с его m_zflag
					CPoint3 ptI = pti.ConvertTo(psurface->m_zflag);
					CPoint3 ptJ = ptj.ConvertTo(psurface->m_zflag);
					CPoint3 ptK = ptk.ConvertTo(psurface->m_zflag);
					CPoint3 ptN = ptn.ConvertTo(psurface->m_zflag);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					//теперь надо проверить дополнительное условие того, что клетки пересекаются -
					// ищем экстремумы клеток и проводим экстремум тест
					CPoint3 
						this_pt_min,
						this_pt_max,
						psurface_pt_min,
						psurface_pt_max;

					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					this_pt_min.x = xi;
					if (xj < this_pt_min.x) this_pt_min.x = xj;
					if (xk < this_pt_min.x) this_pt_min.x = xk;
					if (xn < this_pt_min.x) this_pt_min.x = xn;

					this_pt_max.x = xi;
					if (xj > this_pt_max.x) this_pt_max.x = xj;
					if (xk > this_pt_max.x) this_pt_max.x = xk;
					if (xn > this_pt_max.x) this_pt_max.x = xn;

					this_pt_min.y = yi;
					if (yj < this_pt_min.y) this_pt_min.y = yj;
					if (yk < this_pt_min.y) this_pt_min.y = yk;
					if (yn < this_pt_min.y) this_pt_min.y = yn;

					this_pt_max.y = yi;
					if (yj > this_pt_max.y) this_pt_max.y = yj;
					if (yk > this_pt_max.y) this_pt_max.y = yk;
					if (yn > this_pt_max.y) this_pt_max.y = yn;

					this_pt_min.z = zi;
					if (zj < this_pt_min.z) this_pt_min.z = zj;
					if (zk < this_pt_min.z) this_pt_min.z = zk;
					if (zn < this_pt_min.z) this_pt_min.z = zn;

					this_pt_max.z = zi;
					if (zj > this_pt_max.z) this_pt_max.z = zj;
					if (zk > this_pt_max.z) this_pt_max.z = zk;
					if (zn > this_pt_max.z) this_pt_max.z = zn;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					psurface_pt_min.x = ptI.x;
					if (ptJ.x < psurface_pt_min.x) psurface_pt_min.x = ptJ.x;
					if (ptK.x < psurface_pt_min.x) psurface_pt_min.x = ptK.x;
					if (ptN.x < psurface_pt_min.x) psurface_pt_min.x = ptN.x;

					psurface_pt_max.x = ptI.x;
					if (ptJ.x > psurface_pt_max.x) psurface_pt_max.x = ptJ.x;
					if (ptK.x > psurface_pt_max.x) psurface_pt_max.x = ptK.x;
					if (ptN.x > psurface_pt_max.x) psurface_pt_max.x = ptN.x;

					psurface_pt_min.y = ptI.y;
					if (ptJ.y < psurface_pt_min.y) psurface_pt_min.y = ptJ.y;
					if (ptK.y < psurface_pt_min.y) psurface_pt_min.y = ptK.y;
					if (ptN.y < psurface_pt_min.y) psurface_pt_min.y = ptN.y;

					psurface_pt_max.y = ptI.y;
					if (ptJ.y > psurface_pt_max.y) psurface_pt_max.y = ptJ.y;
					if (ptK.y > psurface_pt_max.y) psurface_pt_max.y = ptK.y;
					if (ptN.y > psurface_pt_max.y) psurface_pt_max.y = ptN.y;

					psurface_pt_min.z = ptI.z;
					if (ptJ.z < psurface_pt_min.z) psurface_pt_min.z = ptJ.z;
					if (ptK.z < psurface_pt_min.z) psurface_pt_min.z = ptK.z;
					if (ptN.z < psurface_pt_min.z) psurface_pt_min.z = ptN.z;

					psurface_pt_max.z = ptI.z;
					if (ptJ.z > psurface_pt_max.z) psurface_pt_max.z = ptJ.z;
					if (ptK.z > psurface_pt_max.z) psurface_pt_max.z = ptK.z;
					if (ptN.z > psurface_pt_max.z) psurface_pt_max.z = ptN.z;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//проводим экстремум тест
					double minimum_x = max(this_pt_min.x, psurface_pt_min.x);
					double maximum_x = min(this_pt_max.x, psurface_pt_max.x);

					double minimum_y = max(this_pt_min.y, psurface_pt_min.y);
					double maximum_y = min(this_pt_max.y, psurface_pt_max.y);

					double minimum_z = max(this_pt_min.z, psurface_pt_min.z);
					double maximum_z = min(this_pt_max.z, psurface_pt_max.z);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					//Здесь пытаемся найти пересечения рёбер текущей поверзности с поверхностью psurface
					//эти координаты аналогичны координатам пересечения временной поверхности с плоскостью z=0
					// растояние от точки до плоскости
					//double ri = zit;//a*xi+b*yi+c*zi+d; 
					//double rj = zjt;//a*xj+b*yj+c*zj+d; 
					//double rn = znt;//a*xn+b*yn+c*zn+d; 
					//double rk = zkt;//a*xk+b*yk+c*zk+d; 
					// растояние между точками
					double rij = sqrt( (xi-xj)*(xi-xj) + (yi-yj)*(yi-yj) + (zi-zj)*(zi-zj) );
					double rin = sqrt( (xi-xn)*(xi-xn) + (yi-yn)*(yi-yn) + (zi-zn)*(zi-zn) );
					double rik = sqrt( (xi-xk)*(xi-xk) + (yi-yk)*(yi-yk) + (zi-zk)*(zi-zk) );

					double rjk = sqrt( (xj-xk)*(xj-xk) + (yj-yk)*(yj-yk) + (zj-zk)*(zj-zk) );							
					double rkn = sqrt( (xk-xn)*(xk-xn) + (yk-yn)*(yk-yn) + (zk-zn)*(zk-zn) );
					double rni = sqrt( (xn-xi)*(xn-xi) + (yn-yi)*(yn-yi) + (zn-zi)*(zn-zi) );

					// гипотенуза
					double ci_j = rij * fabs(zit) / (fabs(zit) + fabs(zjt));
					double ci_n = rin * fabs(zit) / (fabs(zit) + fabs(znt));
					double ci_k = rik * fabs(zit) / (fabs(zit) + fabs(zkt));
					
					double cj_k = rjk * fabs(zjt) / (fabs(zjt) + fabs(zkt));
					double ck_n = rkn * fabs(zkt) / (fabs(zkt) + fabs(znt));
					double cn_i = rni * fabs(znt) / (fabs(znt) + fabs(zit));


					double 
						// координаты точки пересечения плоскости и поверхности относительно листа
						// lxy,lz,
						// координаты точки пересечения плоскости и поверхности относительно куба
						x,y,z;
					//CPoint3 v[4];

					CPoint3 vv[4];


					// i 	n
					//
					// j 	k
					bool 
						b1 = false,
						b2 = false,
						b3 = false,
						b4 = false;
					int ivertex=0;
					int iv=0;
					// ищем точки пересечения рёбер с psurface			
					if( zit * zjt <= 0.0 && bi && bj && bit && bjt)
					{
						x = xi + (xj-xi)*ci_j/rij;
						y = yi + (yj-yi)*ci_j/rij;
						z = zi + (zj-zi)*ci_j/rij;

						//v[ivertex].x = x;
						//v[ivertex].y = y;
						//v[ivertex].z = z;
						ivertex++;

						vv[iv].x = x;
						vv[iv].y = y;
						vv[iv].z = z;	
						b1 = true;
					}
					iv++;
					if( zjt * zkt <= 0.0 && bj && bk && bjt && bkt)
					{
						x = xj + (xk-xj)*cj_k/rjk;
						y = yj + (yk-yj)*cj_k/rjk;
						z = zj + (zk-zj)*cj_k/rjk;

						//v[ivertex].x = x;
						//v[ivertex].y = y;
						//v[ivertex].z = z;
						ivertex++;

						vv[iv].x = x;
						vv[iv].y = y;
						vv[iv].z = z;
						b2 = true;
					}
					iv++;
					if( zkt * znt <= 0.0 && bk && bn && bkt && bnt)
					{
						x = xk + (xn-xk)*ck_n/rkn;
						y = yk + (yn-yk)*ck_n/rkn;
						z = zk + (zn-zk)*ck_n/rkn;

						//v[ivertex].x = x;
						//v[ivertex].y = y;
						//v[ivertex].z = z;
						ivertex++;

						vv[iv].x = x;
						vv[iv].y = y;
						vv[iv].z = z;
						b3 = true;
					}
					iv++;
					if( zit * znt <= 0.0 && bi && bn && bit && bnt)
					{
						x = xi + (xn-xi)*ci_n/rin;
						y = yi + (yn-yi)*ci_n/rin;
						z = zi + (zn-zi)*ci_n/rin;

						//v[ivertex].x = x;
						//v[ivertex].y = y;
						//v[ivertex].z = z;
						ivertex++;
													
						vv[iv].x = x;
						vv[iv].y = y;
						vv[iv].z = z;
						b4 = true;
					}	
					iv++;
					if (ivertex)
					{
						double A1, B1, C1, D1;
						double A2, B2, C2, D2;								
						bool bQSI1 = QuadSquareInterpolation(this->m_zflag,// flag of direction of normal to base of the quad 0-z, 1-x, 2-y
							// input points of 4 quad's vertexes
							this->GetDocumentPoint(i),
							this->GetDocumentPoint(j),
							this->GetDocumentPoint(k),
							this->GetDocumentPoint(n),                           
							A1, B1, C1, D1);// output koefficints of square intepolation
						bool bQSI2 = QuadSquareInterpolation(psurface->m_zflag,// flag of direction of normal to base of the quad 0-z, 1-x, 2-y
							// input points of 4 quad's vertexes
							pti,
							ptj,
							ptk,
							ptn,                                
							A2, B2, C2, D2);// output koefficints of square intepolation
						if (bQSI1 && bQSI2)
						{
							result = true;

							CPoint3* start_point_of_line  =  NULL;
							CPoint3* finish_point_of_line =  NULL;	

							std::vector<CPoint3> v_v;

							// i 4	n
							// 1	3
							// j 2	k

							// i |	n
							// -	-
							// j |	k
							//if (b1 && b2 && b3 && b4)
							// i	n
							// -
							// j |	k
							if (b1 && b2 && !b3 && !b4) //ri * rj && rj * rk
							{
								if(zjt != 0.0)
								{
									if (
										positive && (zkt < 0.0 && znt < 0.0 && zit < 0.0)
										||
										!positive && (zkt > 0.0 && znt > 0.0 && zit > 0.0)
										)
									{
										//5
										v_v.resize(5);
										v_v[0] = vv[0];
										v_v[1] = vv[1];
										v_v[2] = CPoint3(xk,yk,zk);
										v_v[3] = CPoint3(xn,yn,zn);
										v_v[4] = CPoint3(xi,yi,zi);
									}
									else
									{
										if (
											positive && (zjt < 0.0)
											||
											!positive && (zjt > 0.0)
											)
										{
											//3
											v_v.resize(3);
											v_v[0] = vv[0];
											v_v[1] = vv[1];
											v_v[2] = CPoint3(xj,yj,zj);
										}
									}

									start_point_of_line = &vv[0];
									finish_point_of_line = &vv[1];	


									quadCutting.bCutted = 1;
									quadCutting.nLines = 1;
		//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
									quadCutting.start_neighbour_row		= row_quad;
									quadCutting.start_neighbour_col		= col_quad-1;
		//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
									quadCutting.finish_neighbour_row	= row_quad+1;
									quadCutting.finish_neighbour_col	= col_quad;
								}
							}
							// i	n
							//		-
							// j |	k
							if (b2 && b3 && !b1 && !b4) // zjt * zkt && zkt * znt
							{
								if(zkt != 0.0)
								{
									if (positive && (znt < 0.0 && zit < 0.0 && zjt < 0.0)
										||
										!positive && (znt > 0.0 && zit > 0.0 && zjt > 0.0)
										)
									{
										//5
										v_v.resize(5);
										v_v[0] = vv[1];
										v_v[1] = vv[2];
										v_v[2] = CPoint3(xn,yn,zn);
										v_v[3] = CPoint3(xi,yi,zi);
										v_v[4] = CPoint3(xj,yj,zj);
									}
									else
									{
										if  (positive && (zkt < 0.0)
											||
											!positive && (zkt > 0.0)
											)
										{
											//3
											v_v.resize(3);
											v_v[0] = vv[1];
											v_v[1] = vv[2];
											v_v[2] = CPoint3(xk,yk,zk);
										}
									}

									start_point_of_line = &vv[1];
									finish_point_of_line = &vv[2];

									quadCutting.bCutted = 1;
									quadCutting.nLines = 1;
		//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
									quadCutting.start_neighbour_row		= row_quad+1;
									quadCutting.start_neighbour_col		= col_quad;
		//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
									quadCutting.finish_neighbour_row	= row_quad;
									quadCutting.finish_neighbour_col	= col_quad+1;
								}
							}
							// i |	n
							//		-
							// j	k
							if (b3 && b4 && !b1 && !b2) //zkt * znt && zit * znt
							{
								if(znt != 0.0)
								{
									if (positive && (zit < 0.0 && zjt < 0.0 && zkt < 0.0)
										||
										!positive && (zit > 0.0 && zjt > 0.0 && zkt > 0.0)
										)
									{
										//5
										v_v.resize(5);
										v_v[0] = vv[2];
										v_v[1] = vv[3];
										v_v[2] = CPoint3(xi,yi,zi);
										v_v[3] = CPoint3(xj,yj,zj);
										v_v[4] = CPoint3(xk,yk,zk);
									}
									else
									{
										if (positive && (znt < 0.0)
											||
											!positive && (znt > 0.0)
											)
										{
											//3
											v_v.resize(3);
											v_v[0] = vv[2];
											v_v[1] = vv[3];
											v_v[2] = CPoint3(xn,yn,zn);
										}
									}

									start_point_of_line = &vv[2];
									finish_point_of_line = &vv[3];

									quadCutting.bCutted = 1;
									quadCutting.nLines = 1;
		//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
									quadCutting.start_neighbour_row		= row_quad;
									quadCutting.start_neighbour_col		= col_quad+1;
		//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
									quadCutting.finish_neighbour_row	= row_quad-1;
									quadCutting.finish_neighbour_col	= col_quad;
								}

							}
							// i  |	n
							// -
							// j	k
							if (b1 && b4 && !b2 && !b3) //zit * zjt && zit * znt 
							{
								if(zit != 0.0)
								{
									if (positive && (znt < 0.0 && zkt < 0.0 && zjt < 0.0)
										||
										!positive && (znt > 0.0 && zkt > 0.0 && zjt > 0.0)
										)
									{
										//5
										v_v.resize(5);
										v_v[0] = vv[0];
										v_v[1] = vv[3];
										v_v[2] = CPoint3(xn,yn,zn);
										v_v[3] = CPoint3(xk,yk,zk);
										v_v[4] = CPoint3(xj,yj,zj);
									}
									else
									{
										if (positive && (zit < 0.0)
											||
											!positive && (zit > 0.0)
											)
										{
											//3
											v_v.resize(3);
											v_v[0] = vv[0];
											v_v[1] = vv[3];
											v_v[2] = CPoint3(xi,yi,zi);
										}
									}
									start_point_of_line = &vv[0];
									finish_point_of_line = &vv[3];	

									quadCutting.bCutted = 1;
									quadCutting.nLines = 1;
		//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
									quadCutting.start_neighbour_row		= row_quad;
									quadCutting.start_neighbour_col		= col_quad-1;
		//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
									quadCutting.finish_neighbour_row	= row_quad-1;
									quadCutting.finish_neighbour_col	= col_quad;
								}

							}
							// i	n
							// -	-
							// j	k
							if (b1 && b3 && !b2 && !b4) // zit * zjt && zkt * znt
							{
								if(true)
								{
									if (positive && (zkt < 0.0 && zjt < 0.0 )
										||
										!positive && (zkt > 0.0 && zjt > 0.0 )
										)
									{
										//4
										v_v.resize(4);
										v_v[0] = vv[0];
										v_v[1] = vv[2];
										v_v[2] = CPoint3(xk,yk,zk);
										v_v[3] = CPoint3(xj,yj,zj);
									}
									else
									{
										if (positive && (znt < 0.0 && zit < 0.0 )
											||
											!positive && (znt > 0.0 && zit > 0.0 )
											)
										{
											//4
											v_v.resize(4);
											v_v[0] = vv[0];
											v_v[1] = vv[2];
											v_v[2] = CPoint3(xn,yn,zn);
											v_v[3] = CPoint3(xi,yi,zi);
										}
									}

									start_point_of_line = &vv[0];
									finish_point_of_line = &vv[2];	

									quadCutting.bCutted = 1;
									quadCutting.nLines = 1;
		//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
									quadCutting.start_neighbour_row		= row_quad;
									quadCutting.start_neighbour_col		= col_quad-1;
		//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
									quadCutting.finish_neighbour_row	= row_quad;
									quadCutting.finish_neighbour_col	= col_quad+1;
								}
							}
							// i |	n
							//
							// j |	k
							if (b2 && b4 && !b1 && !b3) // zjt * zkt && zit * znt
							{
								if(true)
								{
									if (positive && (zit < 0.0 && zjt < 0.0 )
										||
										!positive && (zit > 0.0 && zjt > 0.0 )
										)
									{
										//4
										v_v.resize(4);
										v_v[0] = vv[1];
										v_v[1] = vv[3];
										v_v[2] = CPoint3(xi,yi,zi);
										v_v[3] = CPoint3(xj,yj,zj);
									}
									else
									{
										if (positive && (znt < 0.0 && zkt < 0.0 )
											||
											!positive && (znt > 0.0 && zkt > 0.0 )
											)
										{
											//4
											v_v.resize(4);
											v_v[0] = vv[1];
											v_v[1] = vv[3];
											v_v[2] = CPoint3(xn,yn,zn);
											v_v[3] = CPoint3(xk,yk,zk);
										}
									}

									start_point_of_line = &vv[1];
									finish_point_of_line = &vv[3];	

									quadCutting.bCutted = 1;
									quadCutting.nLines = 1;
		//							quadCutting.start_point				= CPoint3(v_x[0],v_y[0],v_z[0]);
									quadCutting.start_neighbour_row		= row_quad+1;
									quadCutting.start_neighbour_col		= col_quad;
		//							quadCutting.finish_point			= CPoint3(v_x[1],v_y[1],v_z[1]);
									quadCutting.finish_neighbour_row	= row_quad-1;
									quadCutting.finish_neighbour_col	= col_quad;
								}

							}
							if (start_point_of_line && finish_point_of_line)
								CutTheQuad(
#if USE_UNVISIBLE_CUTTING
									true,
#endif
									quadCutting, quad,
									A1, B1, C1, D1, 
									psurface->m_zflag,
									A2, B2, C2, D2, 
									v_v,
									minimum_x,
									maximum_x,
									minimum_y,
									maximum_y,
									minimum_z,
									maximum_z,
									start_point_of_line, finish_point_of_line,
									toDrawPolygon
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
#else
									, (*blank_polygon_matrix)[row_quad][col_quad]
#endif
#else
									, blank_polygones
#endif
									);
						}
					}
				}
			}
		}
	}
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
//	if (toDrawPolygon && blank_polygon_matrix_ObjectList && blank_polygon_matrix)
//		blank_polygon_matrix_ObjectList->Init2_std_vector_std_vector_ptr(*blank_polygon_matrix, pGeoSurface);
#else
	if (toDrawPolygon && blank_polygones_ObjectList && blank_polygones)
		blank_polygones_ObjectList->Init(*blank_polygones, pGeoSurface);
#endif
   INFO("Surface3D::Cutting() end");

	return result;
}

void Surface3D::CutTheQuad(

#if USE_UNVISIBLE_CUTTING
						 bool bvisible,
#endif							   
						 QuadCutting& quadCutting, UINT quad,
						 double A1, double B1, double C1, double D1, 
						 short zflag2,
						 double A2, double B2, double C2, double D2, 
						 std::vector<CPoint3> & v_v,
						 double minimum_x,
						 double maximum_x,
						 double minimum_y,
						 double maximum_y,
						 double minimum_z,
						 double maximum_z,
						 CPoint3* start_point_of_line,
						 CPoint3* finish_point_of_line,
						 bool toDrawPolygon
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
						, Poligon3D * & blank_polygon
#endif
#else
						, vect<Poligon3D> * blank_polygones
#endif
						 )
{
	double epsilon = 0.000001;
	double X,Y,Z;

	//НАЧИНАЕМ ФОРМИРОВАНИЕ ВЕКТОРА ТОЧЕК СЕЧЕНИЯ ТЕКУЩЕЙ КЛЕТКИ

	vQuadCutting.GetLastVect().GetLastMsg()[quad] = quadCutting;

	// если это включить, то появляется деффект при изображении полигонов
	bool fill_polygon = false;

	int len = v_v.size();
	bool use2as1;
	if (len == 4)
	{
		double distance3_0 = Distance(v_v[3], v_v[0]);
		double distance2_1 = Distance(v_v[2], v_v[1]);
		use2as1 = distance2_1 > distance3_0;
	}

#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
	if (toDrawPolygon)
	{
		blank_polygon = new Poligon3D(this->m_pSurfDoc);
		blank_polygon->Init( (Surface3D *) this);
		blank_polygon->SetColor(m_color);

		switch(len)
		{
		case 3:
			{
				// first point of polygon	
				blank_polygon->PushBack(v_v[2]);
				blank_polygon->PushBack(v_v[0]);//start point of line

			}
			break;
		case 4:
			{
				// first point of polygon	
				CPoint3 pt;
				pt.bVisible = true;
				if (use2as1)
				{
					blank_polygon->PushBack(v_v[2]);
				}
				blank_polygon->PushBack(v_v[3]);
				blank_polygon->PushBack(v_v[0]);//start point of line
			}
			break;
		case 5:
			{
				// first point of polygon	
				blank_polygon->PushBack(v_v[3]);
				blank_polygon->PushBack(v_v[4]);
				blank_polygon->PushBack(v_v[0]);//start point of line
			}
			break;
		}
	}
#endif
#else
	if (toDrawPolygon && blank_polygones)
	{
		Poligon3D poly(this->m_pSurfDoc);
		blank_polygones->AddMsg(&poly);
		blank_polygones->GetLastMsg().Init( (Surface3D *) this);
		blank_polygones->GetLastMsg().SetColor(m_color);

		switch(len)
		{
		case 3:
			{
				// first point of polygon	
				blank_polygones->GetLastMsg().PushBack(v_v[2]);
				blank_polygones->GetLastMsg().PushBack(v_v[0]);//start point of line

			}
			break;
		case 4:
			{
				// first point of polygon	
				CPoint3 pt;
				pt.bVisible = true;
				if (use2as1)
				{
					blank_polygones->GetLastMsg().PushBack(v_v[2]);
				}
				blank_polygones->GetLastMsg().PushBack(v_v[3]);
				blank_polygones->GetLastMsg().PushBack(v_v[0]);//start point of line
			}
			break;
		case 5:
			{
				// first point of polygon	
				blank_polygones->GetLastMsg().PushBack(v_v[3]);
				blank_polygones->GetLastMsg().PushBack(v_v[4]);
				blank_polygones->GetLastMsg().PushBack(v_v[0]);//start point of line
			}
			break;
		}
	}
#endif


	CPoint3 pt;
	std::vector <CPoint3> vpt3;
	int sign;
	double step;
	//int N = 4;
	if (m_zflag == 0 && zflag2 == 0)
	{
		double delta_y = fabs(finish_point_of_line->y - start_point_of_line->y);
		double delta_x = fabs(finish_point_of_line->x - start_point_of_line->x);
		if (delta_y > delta_x)//простирание линии вдоль оси Y
		{
			step = (finish_point_of_line->y - start_point_of_line->y) / m_N_quad;
			for (size_t iy = 0; iy < m_N_quad; iy++)				
			{
				Y = start_point_of_line->y+step*(iy+0.5);
				
				X = - ( (C1 - C2)*Y + (D1 - D2) )
					/
					( (A1 - A2)*Y + (B1 - B2));
	            
				Z = A1*X*Y + B1*X + C1*Y + D1;

				if (X >= minimum_x &&
					X <= maximum_x && 
					Y >= minimum_y && 
					Y <= maximum_y && 
					Z >= minimum_z && 
					Z <= maximum_z)
				{
					pt.bVisible = true;
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.push_back(pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					if (fill_polygon && toDrawPolygon && blank_polygon)
					{
						// interpolated points of polygon	
						blank_polygon->PushBack(pt);
					}
#endif
#else
					if (fill_polygon && toDrawPolygon && blank_polygones)
					{
						// interpolated points of polygon	
						blank_polygones->GetLastMsg().PushBack(pt);
					}
#endif
				}
			}
		}
		else//простирание линии вдоль оси X
		{
			step = (finish_point_of_line->x - start_point_of_line->x) /m_N_quad;
			for (size_t ix = 0; ix < m_N_quad; ix++)				
			{
				X = start_point_of_line->x+step*(ix+0.5);
				
				Y = - ( (B1 - B2)*X + (D1 - D2) )
					/
					( (A1 - A2)*X + (C1 - C2));
	            
				Z = A1*X*Y + B1*X + C1*Y + D1;

				if (X >= minimum_x &&
					X <= maximum_x && 
					Y >= minimum_y && 
					Y <= maximum_y && 
					Z >= minimum_z && 
					Z <= maximum_z)
				{
					pt.bVisible = true;
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.push_back(pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					if (fill_polygon && toDrawPolygon && blank_polygon)
					{
						// interpolated points of polygon	
						blank_polygon->PushBack(pt);
					}
#endif
#else
					if (fill_polygon && toDrawPolygon && blank_polygones)
					{
						// interpolated points of polygon	
						blank_polygones->GetLastMsg().PushBack(pt);
					}
#endif
				}
			}
		}

	}

	if (m_zflag == 0 && zflag2 == 1)
	{
		step = (finish_point_of_line->y - start_point_of_line->y) / m_N_quad;
		for (size_t iy = 0; iy < m_N_quad; iy++)
		{
			Y = start_point_of_line->y+step*(iy+0.5);
			
			X = - (C1*A2*Y*Y + (D1*A2 + C1*B2 + C2)*Y + (D1*B2 + D2))
				/
				(A1*A2*Y*Y + (A1*B2 + B1*A2)*Y + (B1*B2 - 1.0));
            
			Z = A1*X*Y + B1*X + C1*Y + D1;

			if (X >= minimum_x &&
				X <= maximum_x && 
				Y >= minimum_y && 
				Y <= maximum_y && 
				Z >= minimum_z && 
				Z <= maximum_z)
			{
				pt.bVisible = true;
				pt.x = X;
				pt.y = Y;
				pt.z = Z;
				//====================================
				vpt3.push_back(pt);
				//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
				if (fill_polygon && toDrawPolygon && blank_polygon)
				{
					// interpolated points of polygon	
					blank_polygon->PushBack(pt);
				}
#endif
#else
				if (fill_polygon && toDrawPolygon && blank_polygones)
				{
					// interpolated points of polygon	
					blank_polygones->GetLastMsg().PushBack(pt);
				}
#endif
			}
		}
	}

	if (m_zflag == 0 && zflag2 == 2)
	{
		step = (finish_point_of_line->x - start_point_of_line->x) / m_N_quad;
		for (size_t ix = 0; ix < m_N_quad; ix++)
		{
			X = start_point_of_line->x+step*(ix+0.5);
			
			Y = - (B1*A2*X*X + (D1*A2 + B1*C2 + B2)*X + (D1*C2 + D2))
				/
				(A1*A2*X*X + (C1*A2 + A1*C2)*X + (C1*C2 - 1.0));
            
			Z = A1*X*Y + B1*X + C1*Y + D1;


			if (X >= minimum_x &&
				X <= maximum_x && 
				Y >= minimum_y && 
				Y <= maximum_y && 
				Z >= minimum_z && 
				Z <= maximum_z)
			{
				pt.bVisible = true;
				pt.x = X;
				pt.y = Y;
				pt.z = Z;
				//====================================
				vpt3.push_back(pt);
				//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
				if (fill_polygon && toDrawPolygon && blank_polygon)
				{
					// interpolated points of polygon	
					blank_polygon->PushBack(pt);
				}
#endif
#else
				if (fill_polygon && toDrawPolygon && blank_polygones)
				{
					// interpolated points of polygon	
					blank_polygones->GetLastMsg().PushBack(pt);
				}
#endif
			}
		}
	}

	if (m_zflag == 1 && zflag2 == 0)
	{
		step = (finish_point_of_line->y - start_point_of_line->y) / m_N_quad;
		for (size_t iy = 0; iy < m_N_quad; iy++)
		{
			Y = start_point_of_line->y+step*(iy+0.5);
			
			X = - (C2*A1*Y*Y + (D2*A1 + C2*B1 + C1)*Y + (D2*B1 + D1))
				/
				(A2*A1*Y*Y + (A2*B1 + B2*A1)*Y + (B2*B1 - 1.0));
            
			Z = A2*X*Y + B2*X + C2*Y + D2;

			if (X >= minimum_x &&
				X <= maximum_x && 
				Y >= minimum_y && 
				Y <= maximum_y && 
				Z >= minimum_z && 
				Z <= maximum_z)
			{
				pt.bVisible = true;
				pt.x = X;
				pt.y = Y;
				pt.z = Z;
				//====================================
				vpt3.push_back(pt);
				//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
				if (fill_polygon && toDrawPolygon && blank_polygon)
				{
					// interpolated points of polygon	
					blank_polygon->PushBack(pt);
				}
#endif
#else
				if (fill_polygon && toDrawPolygon && blank_polygones)
				{
					// interpolated points of polygon	
					blank_polygones->GetLastMsg().PushBack(pt);
				}
#endif
			}
		}

	}

	if (m_zflag == 1 && zflag2 == 1)
	{
		double delta_y = fabs(finish_point_of_line->y - start_point_of_line->y);
		double delta_z = fabs(finish_point_of_line->z - start_point_of_line->z);
		if (delta_y > delta_z)//простирание линии вдоль оси Y
		{
			step = (finish_point_of_line->y - start_point_of_line->y) / m_N_quad;
			for (size_t iy = 0; iy < m_N_quad; iy++)				
			{
				Y = start_point_of_line->y+step*(iy+0.5);
				
				Z = - ( (C1 - C2)*Y + (D1 - D2) )
					/
					( (A1 - A2)*Y + (B1 - B2));
	            
				X = A1*Z*Y + B1*Z + C1*Y + D1;

				if (X >= minimum_x &&
					X <= maximum_x && 
					Y >= minimum_y && 
					Y <= maximum_y && 
					Z >= minimum_z && 
					Z <= maximum_z)
				{
					pt.bVisible = true;
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.push_back(pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					if (fill_polygon && toDrawPolygon && blank_polygon)
					{
						// interpolated points of polygon	
						blank_polygon->PushBack(pt);
					}
#endif
#else
					if (fill_polygon && toDrawPolygon && blank_polygones)
					{
						// interpolated points of polygon	
						blank_polygones->GetLastMsg().PushBack(pt);
					}
#endif
				}
			}
		}
		else//простирание линии вдоль оси Z
		{
			step = (finish_point_of_line->z - start_point_of_line->z) / m_N_quad;
			for (size_t iz = 0; iz < m_N_quad; iz++)				
			{
				Z = start_point_of_line->z+step*(iz+0.5);
				
				Y = - ( (B1 - B2)*Z + (D1 - D2) )
					/
					( (A1 - A2)*Z + (C1 - C2));
	            
				X = A1*Z*Y + B1*Z + C1*Y + D1;

				if (X >= minimum_x &&
					X <= maximum_x && 
					Y >= minimum_y && 
					Y <= maximum_y && 
					Z >= minimum_z && 
					Z <= maximum_z)
				{
					pt.bVisible = true;
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.push_back(pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					if (fill_polygon && toDrawPolygon && blank_polygon)
					{
						// interpolated points of polygon	
						blank_polygon->PushBack(pt);
					}
#endif
#else
					if (fill_polygon && toDrawPolygon && blank_polygones)
					{
						// interpolated points of polygon	
						blank_polygones->GetLastMsg().PushBack(pt);
					}
#endif
				}
			}
		}
	}

	if (m_zflag == 1 && zflag2 == 2)
	{
		step = (finish_point_of_line->z - start_point_of_line->z) / m_N_quad;
		for (size_t iz = 0; iz < m_N_quad; iz++)
		{
			Z = start_point_of_line->z+step*(iz+0.5);
			
			Y = - (B1*A2*Z*Z + (D1*A2 + B1*B2 + C2)*Z + (D1*B2 + D2))
				/
				(A1*A2*Z*Z + (C1*A2 + A1*B2)*Z + (C1*B2 - 1.0));
            
			X = A1*Z*Y + B1*Z + C1*Y + D1;


			if (X >= minimum_x &&
				X <= maximum_x && 
				Y >= minimum_y && 
				Y <= maximum_y && 
				Z >= minimum_z && 
				Z <= maximum_z)
			{
				pt.bVisible = true;
				pt.x = X;
				pt.y = Y;
				pt.z = Z;
				//====================================
				vpt3.push_back(pt);
				//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
				if (fill_polygon && toDrawPolygon && blank_polygon)
				{
					// interpolated points of polygon	
					blank_polygon->PushBack(pt);
				}
#endif
#else
				if (fill_polygon && toDrawPolygon && blank_polygones)
				{
					// interpolated points of polygon	
					blank_polygones->GetLastMsg().PushBack(pt);
				}
#endif
			}
		}
	}

	if (m_zflag == 2 && zflag2 == 0)
	{
		step = (finish_point_of_line->x - start_point_of_line->x) / m_N_quad;
		for (size_t ix = 0; ix < m_N_quad; ix++)
		{
			X = start_point_of_line->x+step*(ix+0.5);
			
			Y = - (B2*A1*X*X + (D2*A1 + B2*C1 + B1)*X + (D2*C1 + D1))
				/
				(A2*A1*X*X + (C2*A1 + A2*C1)*X + (C2*C1 - 1.0));
            
			Z = A2*X*Y + B2*X + C2*Y + D2;


			if (X >= minimum_x &&
				X <= maximum_x && 
				Y >= minimum_y && 
				Y <= maximum_y && 
				Z >= minimum_z && 
				Z <= maximum_z)
			{
				pt.bVisible = true;
				pt.x = X;
				pt.y = Y;
				pt.z = Z;
				//====================================
				vpt3.push_back(pt);
				//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
				if (fill_polygon && toDrawPolygon && blank_polygon)
				{
					// interpolated points of polygon	
					blank_polygon->PushBack(pt);
				}
#endif
#else
				if (fill_polygon && toDrawPolygon && blank_polygones)
				{
					// interpolated points of polygon	
					blank_polygones->GetLastMsg().PushBack(pt);
				}
#endif
			}
		}

	}

	if (m_zflag == 2 && zflag2 == 1)
	{
		step = (finish_point_of_line->z - start_point_of_line->z) / m_N_quad;
		for (size_t iz = 0; iz < m_N_quad; iz++)
		{
			Z = start_point_of_line->z+step*(iz+0.5);			

			X = - (A2*C1*Z*Z + (A2*D1 + C2*C1 + B2)*Z + (C2*D1 + D2))
				/
				(A2*A1*Z*Z + (A2*B1 + C2*A1)*Z + (C2*B1 - 1.0));            

			Y = A1*X*Z + B1*X + C1*Z + D1;

			if (X >= minimum_x &&
				X <= maximum_x && 
				Y >= minimum_y && 
				Y <= maximum_y && 
				Z >= minimum_z && 
				Z <= maximum_z)
			{
				pt.bVisible = true;
				pt.x = X;
				pt.y = Y;
				pt.z = Z;
				//====================================
				vpt3.push_back(pt);
				//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
				if (fill_polygon && toDrawPolygon && blank_polygon)
				{
					// interpolated points of polygon	
					blank_polygon->PushBack(pt);
				}
#endif
#else
				if (fill_polygon && toDrawPolygon && blank_polygones)
				{
					// interpolated points of polygon	
					blank_polygones->GetLastMsg().PushBack(pt);
				}
#endif
			}
		}
	}

	if (m_zflag == 2 && zflag2 == 2)
	{
		//double delta_z = maximum_z - minimum_z;
		//double delta_x = maximum_x - minimum_x;
		double delta_z = fabs(finish_point_of_line->z - start_point_of_line->z);
		double delta_x = fabs(finish_point_of_line->x - start_point_of_line->x);
		if (delta_z > delta_x)//простирание линии вдоль оси Z
		{
			step = (finish_point_of_line->z - start_point_of_line->z) / m_N_quad;
			for (size_t iz = 0; iz < m_N_quad; iz++)				
			{
				Z = start_point_of_line->z+step*(iz+0.5);
				
				X = - ( (C1 - C2)*Z + (D1 - D2) )
					/
					( (A1 - A2)*Z + (B1 - B2));
	            
				Y = A1*X*Z + B1*X + C1*Z + D1;

				if (X >= minimum_x &&
					X <= maximum_x && 
					Y >= minimum_y && 
					Y <= maximum_y && 
					Z >= minimum_z && 
					Z <= maximum_z)
				{
					pt.bVisible = true;
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.push_back(pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					if (fill_polygon && toDrawPolygon && blank_polygon)
					{
						// interpolated points of polygon	
						blank_polygon->PushBack(pt);
					}
#endif
#else
					if (fill_polygon && toDrawPolygon && blank_polygones)
					{
						// interpolated points of polygon	
						blank_polygones->GetLastMsg().PushBack(pt);
					}
#endif
				}
			}
		}
		else//простирание линии вдоль оси X
		{
			step = (finish_point_of_line->x - start_point_of_line->x) / m_N_quad;
			for (size_t ix = 0; ix < m_N_quad; ix++)				
			{
				X = start_point_of_line->x+step*(ix+0.5);
				
				Z = - ( (B1 - B2)*X + (D1 - D2) )
					/
					( (A1 - A2)*X + (C1 - C2));
	            
				Y = A1*X*Z + B1*X + C1*Z + D1;

				if (X >= minimum_x &&
					X <= maximum_x && 
					Y >= minimum_y && 
					Y <= maximum_y && 
					Z >= minimum_z && 
					Z <= maximum_z)
				{
					pt.bVisible = true;
					pt.x = X;
					pt.y = Y;
					pt.z = Z;
					//====================================
					vpt3.push_back(pt);
					//AddSphere(X,Y,Z,RGB(0,255,0));
#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
					if (fill_polygon && toDrawPolygon && blank_polygon)
					{
						// interpolated points of polygon	
						blank_polygon->PushBack(pt);
					}
#endif
#else
					if (fill_polygon && toDrawPolygon && blank_polygones)
					{
						// interpolated points of polygon	
						blank_polygones->GetLastMsg().PushBack(pt);
					}
#endif
				}
			}
		}
	}

	int npts = vpt3.size();
	vxyz.GetLastVect().GetLastMsg()[quad].resize(npts);
	for (int i = 0; i < npts; ++i)
	{
		vxyz.GetLastVect().GetLastMsg()[quad][i] = vpt3[i];
#if USE_UNVISIBLE_CUTTING
		vxyz.GetLastVect().GetLastMsg()[quad][i].bVisible = bvisible;
#endif
	}

#if USE_BLANK_POLYGON_MATRIX_ON_CUTTING
#if !ZERO_BLANK_POLYGON_MATRIX_ON_CUTTING
	if (toDrawPolygon && blank_polygon)
	{
		switch(len)
		{
		case 3:
			{
				// last points of polygon	
				blank_polygon->PushBack(v_v[1]);
			}
			break;
		case 4:
			{
				// last points of polygon	
				for(int i = 1; i <= (use2as1 ? 1 : 2); i++)
				{
					blank_polygon->PushBack(v_v[i]);
				}
			}
			break;
		case 5:
			{
				// last points of polygon	
				for(int i = 1; i <= 2; i++)
				{
					blank_polygon->PushBack(v_v[i]);
				}
			}
			break;
		}
	}
#endif
#else
	if (toDrawPolygon && blank_polygones)
	{
		switch(len)
		{
		case 3:
			{
				// last points of polygon	
				blank_polygones->GetLastMsg().PushBack(v_v[1]);
			}
			break;
		case 4:
			{
				// last points of polygon	
				for(int i = 1; i <= (use2as1 ? 1 : 2); i++)
				{
					blank_polygones->GetLastMsg().PushBack(v_v[i]);
				}
			}
			break;
		case 5:
			{
				// last points of polygon	
				for(int i = 1; i <= 2; i++)
				{
					blank_polygones->GetLastMsg().PushBack(v_v[i]);
				}
			}
			break;
		}
	}
#endif
}
bool Surface3D::GetQuadIndex(
	double x, double y, double z,
	int& ix, int& iy)
{
	ix = iy = -1;
	double x00 = this->GetFirstDocumentPoint().x;
	double y00 = this->GetFirstDocumentPoint().y;

	double xnn = this->GetLastDocumentPoint().x;
	double ynn = this->GetLastDocumentPoint().y;

	switch(this->m_zflag)
	{
	case 0:
		if (x >= x00 &&	x < xnn &&
			y >= y00 &&	y < ynn)
		{
			ix = int((x - x00) / (xnn - x00) * (this->m_lenx-1));
			iy = int((y - y00) / (ynn - y00) * (this->m_leny-1));
			return true;
		}
		break;
	case 1:
		if (z >= x00 &&	z < xnn &&
			y >= y00 &&	y < ynn)
		{
			ix = int((z - x00) / (xnn - x00) * (this->m_lenx-1));
			iy = int((y - y00) / (ynn - y00) * (this->m_leny-1));
			return true;
		}
		break;
	case 2:
		if (x >= x00 &&	x < xnn &&
			z >= y00 &&	z < ynn)
		{
			ix = int((x - x00) / (xnn - x00) * (this->m_lenx-1));
			iy = int((z - y00) / (ynn - y00) * (this->m_leny-1));
			return true;
		}
		break;
	}

	return false;
}

bool Surface3D::Projection(double x, double y, double z, // координаты точки в пространстве
	double& r, // выход - расстояние от точки до поверхности
	CPoint3 *pt) // координаты точки проекции на поверхности
{
	int ix,iy;
	double A,B,C,D;
	if (this->GetQuadIndex(x, y, z, ix, iy))
	{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		CPoint3
			pti = this->m_vdPoints[this->m_lenx*iy    +ix], //pti
			ptj = this->m_vdPoints[this->m_lenx*(iy+1)+ix], //ptj
			ptk = this->m_vdPoints[this->m_lenx*(iy+1)+ix+1], //ptk
			ptn = this->m_vdPoints[this->m_lenx*iy    +ix+1]; //ptn

		/*CPoint3 ptI = pti.ConvertTo(this->m_zflag);
		CPoint3 ptJ = ptj.ConvertTo(this->m_zflag);
		CPoint3 ptK = ptk.ConvertTo(this->m_zflag);
		CPoint3 ptN = ptn.ConvertTo(this->m_zflag);*/
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		if (!QuadSquareInterpolation(this->m_zflag,// flag of direction of normal to base of the quad 0-z, 1-x, 2-y
			// input points of 4 quad's vertexes
			pti,
			ptj,
			ptk,
			ptn,
			A, B, C, D))// output koefficints of square intepolation
			return false;
				
		double X,Y,Z;
		switch(this->m_zflag)
		{
		case 0:
			{
				X = x;
				Y = y;
				Z = A*X*Y + B*X + C*Y + D;
				r = z-Z;
			}
			break;
		case 1:
			{
				Z = z;
				Y = y;
				X = A*Z*Y + B*Z + C*Y + D;
				r = x-X;
			}
			break;
		case 2:
			{
				X = x;
				Z = z;
				Y = A*X*Z + B*X + C*Z + D;
				r = y-Y;
			}
			break;
		}	

		pt->x=X;
		pt->y=Y;
		pt->z=Z;
		pt->bVisible = true;
		return true;
	}
	return false;
}
//extern int ImportSurfer7Grid(Grid* pgrid);


DWORD Surface3D::Serialize(Archive& ar)
{
	printf("Surface3D::Serialize(Archive& ar)\n");
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
Archive& operator <<(Archive& ar, Surface3D& ob)
{
//printf("Archive& operator <<(Archive& ar, Surface3D& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (version)
	{
	case 2:
		{
			ar << ob.m_palette;
		}
		//do not break here !!!
	case 1:
		{
			ar << ob.m_bInverseColormap;
			ar << ob.m_bLocalColormap;
			ar << ob.m_bQuad;
			ar << ob.m_bUseColormap;
			ar << ob.m_lenx;
			ar << ob.m_leny;
			ar << ob.m_nColormap;
			ar << ob.m_zflag;
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
Archive& operator >>(Archive& ar, Surface3D& ob)
{
//printf("Archive& operator >>(Archive& ar, Surface3D& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 2:
		{
//printf("Archive& operator >>(Archive& ar, Surface3D& ob) 2\n");

			ar >> ob.m_palette;
//printf("Archive& operator >>(Archive& ar, Surface3D& ob) 2 end\n");
		}
		//do not break here !!!
	case 1:
		{
			ob.m_object_version = 2;

//printf("Archive& operator >>(Archive& ar, Surface3D& ob) 1\n");
			ar >> ob.m_bInverseColormap;
			ar >> ob.m_bLocalColormap;
			ar >> ob.m_bQuad;
			ar >> ob.m_bUseColormap;
			ar >> ob.m_lenx;
			ar >> ob.m_leny;
			ar >> ob.m_nColormap;
			ar >> ob.m_zflag;
		}
		break;

	default:
		{
//printf("Archive& operator >>(Archive& ar, Surface3D& ob) default!!!\n");
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, Surface3D& ob) end\n");
	return ar;
}



#if 0
/*
Writing a program that communicates with AutoCAD by means of the DXF mechanism 
appears more difficult than it actually is. The DXF format makes it easy to ignore 
information you don't need, while reading the information you do need.
The following example is a Microsoft BASIC™ program that reads a DXF file 
and extracts all the line entities from the drawing (ignoring lines that 
appear inside blocks). It displays the endpoints of these lines on the 
screen. This program is an example of how simple a DXF-reading program can be.

1000  REM
1010  REM Extract lines from DXF file
1020  REM
1030  G1% = 0
1040  LINE INPUT "DXF file name: "; A$
1050  OPEN "i", 1, A$ + ".dxf"
1060  REM
1070  REM Ignore until section start encountered
1080  REM
1090  GOSUB 2000
1100  IF G% <> 0 THEN 1090
1110  IF S$ <> "SECTION" THEN 1090 
1120  GOSUB 2000
1130  REM
1140  REM Skip unless ENTITIES section
1150  REM
1160  IF S$ <> "ENTITIES" THEN 1090
1170  REM
1180  REM Scan until end of section, processing LINEs

1190  REM
1200  GOSUB 2000
1210  IF G% = 0 AND S$ = "ENDSEC" THEN 2200
1220  IF G% = 0 AND S$ = "LINE" THEN GOSUB 1400 : GOTO 1210
1230  GOTO 1200
1400  REM
1410  REM Accumulate LINE entity groups
1420  REM
1430  GOSUB 2000
1440  IF G% = 10 THEN X1 = X : Y1 = Y : Z1 = Z
1450  IF G% = 11 THEN X2 = X : Y2 = Y : Z2 = Z
1460  IF G% = 0 THEN PRINT "Line from
 (";X1;",";Y1;",";Z1;") to (";X2;",";Y2;",";Z2;")":RETURN
1470  GOTO 1430
2000  REM
2010  REM Read group code and following value

2020  REM For X coordinates, read Y and possibly Z also
2030  REM
2040  IF G1% < 0 THEN G% = -G1% : G1% = 0 ELSE INPUT #1, G%
2050  IF G% < 10 OR G% = 999 THEN LINE INPUT #1, S$ : RETURN
2060  IF G% >= 38 AND G% <= 49 THEN INPUT #1, V : RETURN
2080  IF G% >= 50 AND G% <= 59 THEN INPUT #1, A : RETURN
2090  IF G% >= 60 AND G% <= 69 THEN INPUT #1, P% : RETURN
2100  IF G% >= 70 AND G% <= 79 THEN INPUT #1, F% : RETURN
2110  IF G% >= 210 AND G% <= 219 THEN 2130
2115  IF G% >= 1000 THEN LINE INPUT #1, T$ : RETURN

2120  IF G% >= 20 THEN PRINT "Invalid group code";G% : STOP
2130  INPUT #1, X
2140  INPUT #1, G1%
2150  IF G1% <> (G%+10) THEN PRINT "Invalid Y coord code";
 G1% : STOP
2160  INPUT #1, Y 
2170  INPUT #1, G1%
2180  IF G1% <> (G%+20) THEN G1% = -G1% ELSE INPUT #1, Z
2190  RETURN

2200  CLOSE 1

Writing a program that constructs a DXF file poses different problems. 
You must maintain consistency within the drawing, although with AutoCAD 
you can omit many items in a DXF file and still obtain a usable drawing. 
The entire HEADER section can be omitted if you don't set header variables. 
Any of the tables in the TABLES section can be omitted if you don't need 
to make entries, and the entire TABLES section can be dropped if nothing 
in it is required. If you define any linetypes in the LTYPE table, this 
table must appear before the LAYER table. If no block definitions are 
used in the drawing, the BLOCKS section can be omitted. If present, the 
BLOCKS section must appear before the ENTITIES section. Within the ENTITIES 
section, you can reference layer names even though you haven't defined them 
in the LAYER table. Such layers are automatically created with color 7 and the 
CONTINUOUS linetype. The EOF item must be present at the end of file.

The following Microsoft BASIC program constructs a DXF file representing a polygon with a specified number of sides, leftmost origin point, and side length. This program supplies only the ENTITIES section of the DXF file and places all entities generated on the default layer 0. Because this program doesn't create the drawing header, the drawing limits, extents, and current view will be invalid after performing a DXFIN on the drawing generated by this program. You can do a ZOOM Extents to fill the screen with the drawing generated. Then adjust the limits manually.

1000  REM
1010  REM Polygon generator
1020  REM
1030  LINE INPUT "Drawing (DXF) file name: "; A$
1040  OPEN "o", 1, A$ + ".dxf"
1050  PRINT #1, 0
1060  PRINT #1, "SECTION"
1070  PRINT #1, 2
1080  PRINT #1, "ENTITIES"
1090  PI = ATN(1) * 4
1100  INPUT "Number of sides for polygon: "; S%
1110  INPUT "Starting point (X,Y): "; X, Y
1120  INPUT "Polygon side: "; D
1130  A1 = (2 * PI) / S%
1140  A = PI / 2
1150  FOR I% = 1 TO S%
1160  PRINT #1, 0
1170  PRINT #1, "LINE"

1180  PRINT #1, 8
1190  PRINT #1, "0"
1200  PRINT #1, 10
1210  PRINT #1, X
1220  PRINT #1, 20
1230  PRINT #1, Y
1240  PRINT #1, 30
1250  PRINT #1, 0.0
1260  NX = D * COS(A) + X
1270  NY = D * SIN(A) + Y
1280  PRINT #1, 11
1290  PRINT #1, NX
1300  PRINT #1, 21
1310  PRINT #1, NY
1320  PRINT #1, 31
1330  PRINT #1, 0.0
1340  X = NX
1350  Y = NY
1360  A = A + A1
1370  NEXT I%
1380  PRINT #1, 0
1390  PRINT #1, "ENDSEC"
1400  PRINT #1, 0
1410  PRINT #1, "EOF"

1420  CLOSE 1

As long as a properly formatted item appears on the line on which the data is expected, DXFIN accepts it. (Of course, string items should not have leading spaces unless these are intended to be part of the string.) This program takes advantage of this flexibility in input format and does not generate a file exactly like one generated by AutoCAD.
In the case of an error in using DXFIN TO load, AutoCAD reports the error with a message indicating the nature of the error and the last line processed in the dxf file before the error was detected. This may not be the line on which the error occurred, especially in the case of errors such as the omission of required groups. 
*/
#endif
