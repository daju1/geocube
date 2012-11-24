// Cube4D.cpp: implementation of the Cube4D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SurfDoc.h"
//#include "raporto.h"
#include "DrawScene.h"
#include "colormap.h"
#include "DrawScene.h"
#include "..\..\winplot\src\winplot.h"
#include "..\..\array\src\matrixes.h"
#include "distance3d.h"
#include ".\cube.h"
#include ".\iso.h"
//#include "errorexit.h"
#include "prsht.h"

#include <vector>
#include <algorithm>
#include <functional>      // For greater<int>( )

extern void getNorm(double v1[3], double v2[3], double out[3]);
//Cube4D * Cube4D::me = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HINSTANCE hInst;   // текущий экземпляр
//Cube4D::draw_mode Cube4D::s_draw_mode = Cube4D::draw_mode::one_isosurface;
Cube4D::draw_mode Cube4D::s_draw_mode = Cube4D::draw_mode::many_isosurfaces;
SSaveProfData Cube4D::sprData;



#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"

Cube4D::Cube4D()
{
	Init();
	OnCreate();
}

Cube4D::Cube4D(SurfDoc * pSurfDoc)
{
	Init();
	m_pSurfDoc			= pSurfDoc;
	OnCreate();
}
void Cube4D::OnCreate(void)
{
	this->m_object_type = Object::object_type::cube4d;
	this->m_object_version = 2;
	this->m_max_object_version = 2;
}
void Cube4D::Init()
{
//	this->m_izolines.OnCreate();
	m_nColormap			= 0;
	m_bInverseColormap	= false;
	m_bUseColormap		= true;

	m_pSurfDoc = NULL;
	
	vQuadCutting.OnCreate(0);
	vxyz.OnCreate(0);

	APalette::InitPalette(&this->m_palette, this->m_nColormap);

#if !CUBE4D_AS_PRIMITIVE

	this->m_color = 0;
	this->m_alpha = 125;

	this->m_opacity = 0.5;
	this->m_isolevel = 0.0;
	this->m_nIsolevels = 10;
	this->m_isolevels.resize(m_nIsolevels, 0.0);
	this->m_iso_ind = 0;
	

	this->lattice.grid4Section.nPag = 0;
	this->lattice.grid4Section.nRow = 0;
	this->lattice.grid4Section.nCol = 0;
#if 1
	this->lattice.grid4Section.v = NULL;
#else
	this->lattice.grid4Section.v = Alloc3DMat<double>(this->lattice.grid4Section.nPag, this->lattice.grid4Section.nRow, this->lattice.grid4Section.nCol);
	for(long p = 0; p < this->lattice.grid4Section.nPag; p++)
	{
		for(long r = 0; r < this->lattice.grid4Section.nRow; r++)
		{
			for(long c = 0; c < this->lattice.grid4Section.nCol; c++)
			{
				this->lattice.grid4Section.v[p][r][c] = 0.0;
			}
		}
	}
#endif

	this->m_min_isolevel = 0.0;
	this->m_max_isolevel = 0.0;
	this->m_step_isolevel = 1.0;
#endif

	draw_as_one_isosurface		= false;
	draw_as_many_isosurfaces	= true;
	draw_as_scatter_plot		= false;
	draw_as_image				= false;
	draw_as_contours			= false;
	draw_as_vol_render			= false;


}
void Cube4D::Init(const Cube4D &ob)
{
	m_palette			= ob.m_palette;
	m_nColormap			= ob.m_nColormap;

	m_bUseColormap		= ob.m_bUseColormap;
	m_bInverseColormap	= ob.m_bInverseColormap;

	m_pSurfDoc			= ob.m_pSurfDoc;

#if CUBE4D_AS_PRIMITIVE
	m_leny				= ob.m_leny;
	m_lenx				= ob.m_lenx;
	m_lenz				= ob.m_lenz;


	this->m_vMax		= ob.m_vMax;
	this->m_vMin		= ob.m_vMin;
#else
	m_color				= ob.m_color;
	m_alpha				= ob.m_alpha;

	m_opacity			= ob.m_opacity;
	m_isolevel			= ob.m_isolevel;
	m_nIsolevels		= ob.m_nIsolevels;
	m_isolevels			= ob.m_isolevels;
	m_iso_ind			= ob.m_iso_ind;

	m_min_isolevel		= ob.m_min_isolevel;
	m_max_isolevel		= ob.m_max_isolevel;
	m_step_isolevel		= ob.m_step_isolevel;

	
	lattice				= ob.lattice;	
	if(ob.lattice.grid4Section.v)
	{
		this->lattice.grid4Section.v = Alloc3DMat<double>(this->lattice.grid4Section.nPag, this->lattice.grid4Section.nRow, this->lattice.grid4Section.nCol);
		for(long p = 0; p < this->lattice.grid4Section.nPag; p++)
		{
			for(long r = 0; r < this->lattice.grid4Section.nRow; r++)
			{
				for(long c = 0; c < this->lattice.grid4Section.nCol; c++)
				{
					this->lattice.grid4Section.v[p][r][c] = ob.lattice.grid4Section.v[p][r][c];
				}
			}
		}
	}
	else
	{
		this->lattice.grid4Section.v = NULL;
	}

#endif

	draw_as_one_isosurface		= ob.draw_as_one_isosurface;
	draw_as_many_isosurfaces	= ob.draw_as_many_isosurfaces;
	draw_as_scatter_plot		= ob.draw_as_scatter_plot;
	draw_as_image				= ob.draw_as_image;
	draw_as_contours			= ob.draw_as_contours;
	draw_as_vol_render			= ob.draw_as_vol_render;

}
#if CUBE4D_AS_PRIMITIVE
bool Cube4D::MakeGridSection(LPSURFER7GRID4SECTION grid4Section)
{
	if (this->GetPointsNumber())
	{
		grid4Section->nRow = m_leny;
		grid4Section->nCol = m_lenx;
		grid4Section->nPag = m_lenz;

		grid4Section->xLL = this->GetDocumentPoint(0).x;
		grid4Section->yLL = this->GetDocumentPoint(0).y;
		grid4Section->zLL = this->GetDocumentPoint(0).z;

		grid4Section->xSize  = this->GetDocumentPoint(1).x - this->GetDocumentPoint(0).x;
		grid4Section->ySize  = this->GetDocumentPoint(m_lenx).y - this->GetDocumentPoint(0).y;
		grid4Section->zSize  = this->GetDocumentPoint(m_lenx*m_lenx).z - this->GetDocumentPoint(0).z;

		grid4Section->BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		grid4Section->Rotation = 0.0;// not currently used;

		bool start = true;
		for(size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			if (start)
			{
				grid4Section->vMin = this->GetDocumentPoint(i).v;
				grid4Section->vMax = this->GetDocumentPoint(i).v;
				start = false;
			}
			else
			{
				if(grid4Section->vMin > this->GetDocumentPoint(i).v) grid4Section->vMin = this->GetDocumentPoint(i).v;
				if(grid4Section->vMax < this->GetDocumentPoint(i).v) grid4Section->vMax = this->GetDocumentPoint(i).v;
			}
		}

		grid4Section->v = Alloc3DMat<double>(grid4Section->nPag, grid4Section->nRow, grid4Section->nCol);

		i = 0;
		//for (long r = 0; r < pGrid->gridSection.nRow; r++)
		for(UINT p = 0; p < m_lenz; p++)
		{
			for(UINT r = 0; r < m_leny; r++)
			{
				//for (long c = 0; c < pGrid->gridSection.nCol; c++)
				for(UINT c = 0; c < m_lenx; c++)
				{
					if (!this->GetDocumentPoint(i).bVisible)
					{
						grid4Section->v[p][r][c] = grid4Section->BlankValue;
					}
					else
					{
						grid4Section->v[p][r][c] = this->GetDocumentPoint(i).v;
					}
					i++;
				}
			}
		}
		return true;
	}
	return false;

}
#endif
#if CUBE4D_AS_PRIMITIVE
void Cube4D::Init(LPSURFER7GRID4SECTION grid4Section, COLORREF color)
{		
printf("Cube4D::Init %ld %ld %ld\n", grid4Section->nPag, grid4Section->nRow, grid4Section->nCol);
	m_leny = grid4Section->nRow;
	m_lenx = grid4Section->nCol;
	m_lenz = grid4Section->nPag;
printf("Cube4D::Init %u %u %u\n", m_lenz, m_leny, m_lenx);

	this->m_vMin = grid4Section->vMin;
	this->m_vMax = grid4Section->vMax;

	m_color = color;
printf("Cube4D::Init\n");

	Free();
	AllocPoints(m_lenz*m_leny*m_lenx);
printf("Cube4D::Init\n");

	UINT i = 0;
	//for (long r = 0; r < pGrid->gridSection.nRow; r++)
	for(UINT p = 0; p < m_lenz; p++)
	{
printf("Cube4D::Init %u %u\n", p, m_lenz);
		for(UINT r = 0; r < m_leny; r++)
		{
//printf("Cube4D::Init		%ud %ud\n", r, m_leny);
			//for (long c = 0; c < pGrid->gridSection.nCol; c++)
			for(UINT c = 0; c < m_lenx; c++)
			{
				CPoint4 pt;
				pt.bVisible = true;

				pt.x = grid4Section->xLL + c * grid4Section->xSize;
				pt.y = grid4Section->yLL + r * grid4Section->ySize;
				pt.z = grid4Section->zLL + p * grid4Section->zSize;
				pt.v = grid4Section->v[p][r][c];
//printf("%f\t", pt.v);
				if (grid4Section->v[p][r][c] > grid4Section->vMax)
				{
					pt.bVisible = false;
					pt.v = grid4Section->vMin;
				}
				m_vvPoints[i] = pt;
				m_vdPoints[i] = pt;
				i++;
			}
		}
	}
	/*this->UpdateExtremums();	*/
}


#else
void Cube4D::Init(LPSURFER7GRID4SECTION grid4Section, COLORREF color)
{		
printf("Cube4D::Init %ld %ld %ld\n", grid4Section->nPag, grid4Section->nRow, grid4Section->nCol);
	
	this->lattice.grid4Section.nRow = grid4Section->nRow;
	this->lattice.grid4Section.nCol = grid4Section->nCol;
	this->lattice.grid4Section.nPag = grid4Section->nPag;

	this->lattice.grid4Section.vMin = grid4Section->vMin;
	this->lattice.grid4Section.vMax = grid4Section->vMax;

	this->lattice.grid4Section.xLL = grid4Section->xLL; // X coordinate of the lower left corner of the grid
	this->lattice.grid4Section.yLL = grid4Section->yLL; // Y coordinate of the lower left corner of the grid
	this->lattice.grid4Section.zLL = grid4Section->zLL; // Y coordinate of the lower left corner of the grid
	this->lattice.grid4Section.xSize = grid4Section->xSize; // spacing between adjacent nodes in the X direction (between columns)
	this->lattice.grid4Section.ySize = grid4Section->ySize; // spacing between adjacent nodes in the Y direction (between rows)
	this->lattice.grid4Section.zSize = grid4Section->zSize; // spacing between adjacent nodes in the Y direction (between rows)
	this->lattice.grid4Section.vMin = DBL_MAX; // minimum V value within the grid
	this->lattice.grid4Section.vMax = -DBL_MAX; // maximum V value within the grid
	this->lattice.grid4Section.Rotation = grid4Section->Rotation; // not currently used
	this->lattice.grid4Section.BlankValue = grid4Section->BlankValue; // nodes are blanked if greater or equal to this value

	m_color = color;
printf("Cube4D::Init\n");

	//Free();
	Free3DMat<double>(this->lattice.grid4Section.v);
	//AllocPoints(m_lenz*m_leny*m_lenx);
	this->lattice.grid4Section.v = Alloc3DMat<double>(this->lattice.grid4Section.nPag, this->lattice.grid4Section.nRow, this->lattice.grid4Section.nCol);
printf("Cube4D::Init\n");

	for(long p = 0; p < this->lattice.grid4Section.nPag; p++)
	{
		for(long r = 0; r < this->lattice.grid4Section.nRow; r++)
		{
//printf("Cube4D::Init		%ud %ud\n", r, m_leny);
			for(long c = 0; c < this->lattice.grid4Section.nCol; c++)
			{
				this->lattice.grid4Section.v[p][r][c] = grid4Section->v[p][r][c];

				if (this->lattice.grid4Section.v[p][r][c] != BLANK_VALUE)
				{
					if (this->lattice.grid4Section.vMin > this->lattice.grid4Section.v[p][r][c]) this->lattice.grid4Section.vMin = this->lattice.grid4Section.v[p][r][c];
					if (this->lattice.grid4Section.vMax < this->lattice.grid4Section.v[p][r][c]) this->lattice.grid4Section.vMax = this->lattice.grid4Section.v[p][r][c];
				}
			}
		}
	}
printf("this->lattice.grid4Section.vMax = %f\n", this->lattice.grid4Section.vMax);
printf("this->lattice.grid4Section.vMin = %f\n", this->lattice.grid4Section.vMin);

	//this->m_min_isolevel = this->lattice.grid4Section.vMin;
	//this->m_max_isolevel = this->lattice.grid4Section.vMax;
	//this->m_step_isolevel = (this->m_max_isolevel - this->m_min_isolevel) / this->m_nIsolevels;

	this->ScaleIsolevels();
	this->UpdateIsolevels(true);
}
void Cube4D::InitThin(LPSURFER7GRID4SECTION grid4Section, COLORREF color)
{		
printf("Cube4D::Init %ld %ld %ld\n", grid4Section->nPag, grid4Section->nRow, grid4Section->nCol);
	
	this->lattice.grid4Section.nRow = grid4Section->nRow == 1 ? 2 : grid4Section->nRow;
	this->lattice.grid4Section.nCol = grid4Section->nCol == 1 ? 2 : grid4Section->nCol;
	this->lattice.grid4Section.nPag = grid4Section->nPag == 1 ? 2 : grid4Section->nPag;

	//this->lattice.grid4Section.vMin = grid4Section->vMin;
	//this->lattice.grid4Section.vMax = grid4Section->vMax;

	this->lattice.grid4Section.xLL = grid4Section->xLL; // X coordinate of the lower left corner of the grid
	this->lattice.grid4Section.yLL = grid4Section->yLL; // Y coordinate of the lower left corner of the grid
	this->lattice.grid4Section.zLL = grid4Section->zLL; // Y coordinate of the lower left corner of the grid
	this->lattice.grid4Section.xSize = grid4Section->xSize; // spacing between adjacent nodes in the X direction (between columns)
	this->lattice.grid4Section.ySize = grid4Section->ySize; // spacing between adjacent nodes in the Y direction (between rows)
	this->lattice.grid4Section.zSize = grid4Section->zSize; // spacing between adjacent nodes in the Y direction (between rows)
	this->lattice.grid4Section.vMin = DBL_MAX; // minimum V value within the grid
	this->lattice.grid4Section.vMax = -DBL_MAX; // maximum V value within the grid
	this->lattice.grid4Section.Rotation = grid4Section->Rotation; // not currently used
	this->lattice.grid4Section.BlankValue = grid4Section->BlankValue; // nodes are blanked if greater or equal to this value
#if 0
	if (this->lattice.grid4Section.xSize == 0.0)
		this->lattice.grid4Section.xSize = this->lattice.grid4Section.ySize;
	if (this->lattice.grid4Section.ySize == 0.0)
		this->lattice.grid4Section.ySize = this->lattice.grid4Section.xSize;
	if (this->lattice.grid4Section.zSize == 0.0)
		this->lattice.grid4Section.zSize = max (this->lattice.grid4Section.xSize, this->lattice.grid4Section.ySize) ;
#else
	if (this->lattice.grid4Section.xSize == 0.0)
		this->lattice.grid4Section.xSize = 1.0;
	if (this->lattice.grid4Section.ySize == 0.0)
		this->lattice.grid4Section.ySize = 1.0;
	if (this->lattice.grid4Section.zSize == 0.0)
		this->lattice.grid4Section.zSize = 1.0;
#endif

	m_color = color;
printf("Cube4D::Init\n");

	//Free();
	Free3DMat<double>(this->lattice.grid4Section.v);
	//AllocPoints(m_lenz*m_leny*m_lenx);
	this->lattice.grid4Section.v = Alloc3DMat<double>(this->lattice.grid4Section.nPag, this->lattice.grid4Section.nRow, this->lattice.grid4Section.nCol);
	Zero3DMat<double>(this->lattice.grid4Section.v, this->lattice.grid4Section.nPag, this->lattice.grid4Section.nRow, this->lattice.grid4Section.nCol);
printf("Cube4D::Init\n");

	for(long p = 0; p < this->lattice.grid4Section.nPag; p++)
	{
		for(long r = 0; r < this->lattice.grid4Section.nRow; r++)
		{
//printf("Cube4D::Init		%ud %ud\n", r, m_leny);
			for(long c = 0; c < this->lattice.grid4Section.nCol; c++)
			{
				if (p < grid4Section->nPag && r < grid4Section->nRow && c < grid4Section->nCol)
				{
					this->lattice.grid4Section.v[p][r][c] = grid4Section->v[p][r][c];

					if (this->lattice.grid4Section.v[p][r][c] != BLANK_VALUE)
					{
						if (this->lattice.grid4Section.vMin > this->lattice.grid4Section.v[p][r][c]) this->lattice.grid4Section.vMin = this->lattice.grid4Section.v[p][r][c];
						if (this->lattice.grid4Section.vMax < this->lattice.grid4Section.v[p][r][c]) this->lattice.grid4Section.vMax = this->lattice.grid4Section.v[p][r][c];
					}
				}
			}
		}
	}
	if (this->lattice.grid4Section.vMin > 0.0) this->lattice.grid4Section.vMin = 0.0;
	if (this->lattice.grid4Section.vMax < 0.0) this->lattice.grid4Section.vMax = 0.0;

printf("this->lattice.grid4Section.vMax = %f\n", this->lattice.grid4Section.vMax);
printf("this->lattice.grid4Section.vMin = %f\n", this->lattice.grid4Section.vMin);

	//this->m_min_isolevel = this->lattice.grid4Section.vMin;
	//this->m_max_isolevel = this->lattice.grid4Section.vMax;
	//this->m_step_isolevel = (this->m_max_isolevel - this->m_min_isolevel) / this->m_nIsolevels;

	this->ScaleIsolevels();
	this->UpdateIsolevels(true);
}
#endif
void gScaleCubeIsolevels (double span, double& step)
{
	//===== Переменная span определяет диапазон изменения
	//===== значаний одной из координат точек графика
	//===== Вычисляем порядок числа, описывающего диапазон
	int power = int(floor(log10(span)));
	//===== Множитель (zoom factor)
	double factor = pow(10.0, (double)power);
	//===== Мантисса диапазона (теперь 1 < span < 10)
	span /= factor;


	//===== Выбираем стандартный шаг сетки
	if (span<1.99)
		step=.2;
	else if (span<2.49)
		step=.25;
	else if (span<4.99)
		step=.5;
	else if (span<10.)
		step= 1.;
	else
		step = 5.;

	//===== Возвращаем реальный шаг сетки (step*10^power)
	step *= factor; 
}



void Cube4D::ScaleIsolevels()
{
printf("Cube4D::ScaleIsolevels()\n");

	double Max = this->lattice.grid4Section.vMax;
	double Min = this->lattice.grid4Section.vMin;
	//===== С пустой последовательностью не работаем

	//===== Максимальная амплитуда двух экстремумов 
	double ext = max(fabs(Min),fabs(Max));
#if 0
	//===== Искусственно увеличиваем порядок экстремума
	//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
	//===== не переходя к экспоненцеальной форме чисел 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	double Power = int(floor(power/7.));
#else
	double power = ext > 0.? log10(ext) : 0.;	
	double Power = int(floor(power/7.));
#endif


	//===== Если число не укладывается в этот диапазон
	if (Power != 0)
		//===== то мы восстанавливаем значение порядка
		Power = int(floor(power)) - 3;
	//===== Реальный множитель
	double Factor = pow(10.,Power);


	//===== Диапазон изменения мантиссы
	double span = (Max - Min)/Factor;
	//===== Если он нулевой,
	if (span == 0.)
		span = 0.5; // то искусственно раздвигаем график

	//===== Подбираем стандартный шаг для координатной сетки
	double Step;
	gScaleCubeIsolevels (span, Step);

printf("Cube4D::ScaleIsolevels() Step = %f %e\n", Step, Step);

	//===== Шаг с учетом искусственных преобразований
	double dStep = Step * Factor;
printf("Cube4D::ScaleIsolevels() dStep = %f %e\n", dStep, dStep);

	//===== Начальная линия сетки должна быть кратна шагу
	//===== и быть меньше минимума
	//double dStart = dStep * int(floor(Min/dStep));
	double dStart = dStep * int(ceil(Min/dStep));
	double Start = dStart/Factor;
printf("Cube4D::ScaleIsolevels() dStart = %f\n", dStart);
printf("Cube4D::ScaleIsolevels() Start = %f\n", Start);
printf("Cube4D::ScaleIsolevels() Min/Factor + span - Step - 1e-10 = %f\n", 
	   Min/Factor + span - Step - 1e-10);

double nn = (Min/Factor + span - Step - 1e-10 - Start) / Step;
printf("Cube4D::ScaleIsolevels() nn = %f\n", nn);

if (nn != nn)
{
	return;
}
if (nn > 1000)
{
	return;
}

	if (Step == 0.0)
	{
		printf("warning : Step == 0.0 \n\t\tCube4D::ScaleIsolevels()\n\n");
		return;
	}

	double End;
#if 1
	//===== Вычисляем последнюю линию сетки
	//for (double End = Start;
	//	End < Min/Factor + span-1e-10;  
	//	End += Step)
	//	;	
	for (End = Start;
		End < Min/Factor + span - Step - 1e-10;  
		End += Step)
		;
#else
		End = Start 
			+ int( ((Max-Start)/data.Factor - 1e-10) / data.Step+1)
			* data.Step;
#endif
	double dEnd = End*Factor;

	//for (double x = dStart; x <= dEnd;x += dStep){}

	this->m_min_isolevel = dStart;
	this->m_max_isolevel = dEnd;
	this->m_step_isolevel = dStep;
	this->m_nIsolevels  = (dEnd - dStart) / dStep + 1;
printf("Cube4D::ScaleIsolevels() end\n");
}


void Cube4D::Produce3DSurferGrid7_YZ(double plane[4], SURFER7GRIDSECTION & grid)
{
	long p,r,c,R,C;
	double x,y,z;
	double pp, cc, rr;
	grid.BlankValue = BLANK_VALUE;
	grid.Rotation = 0.0;
	//else if (fabs(plane[0]) >= fabs(plane[1]) && fabs(plane[0]) >= fabs(plane[2]))
	if (fabs(plane[0]) > 1e-16 && fabs(lattice.grid4Section.xSize) > 1e-16)
	{
		// доминирует направление вдоль оси X
		if (grid.nCol == lattice.grid4Section.nRow && grid.nRow == lattice.grid4Section.nPag && grid.z)
		{
		}
		else
		{
			FreeDoubleMat(grid.z);
			grid.nRow = lattice.grid4Section.nPag;
			grid.nCol = lattice.grid4Section.nRow;
			grid.z = AllocDoubleMat(grid.nRow, grid.nCol);
		}
		grid.xLL = lattice.grid4Section.yLL;
		grid.yLL = lattice.grid4Section.zLL;
		grid.xSize = lattice.grid4Section.ySize;
		grid.ySize = lattice.grid4Section.zSize;
		for(r = 0; r < lattice.grid4Section.nRow; r++)
		{
			y = lattice.grid4Section.yLL + r * lattice.grid4Section.ySize;
			C = r;
			for(p = 0; p < lattice.grid4Section.nPag; p++)
			{
				R = p;
				z = lattice.grid4Section.zLL + p * lattice.grid4Section.zSize;
				x = -(plane[1]*y+plane[2]*z+plane[3])/plane[0];
				cc = (x-lattice.grid4Section.xLL) / lattice.grid4Section.xSize;
				if (cc < 0.0 || cc > lattice.grid4Section.nCol-1)
					grid.z[R][C] = BLANK_VALUE;
				else
				{
					if (
						(lattice.grid4Section.v[p][r][long(floor(cc))] == BLANK_VALUE)
						||
						(lattice.grid4Section.v[p][r][long(ceil(cc))] ==  BLANK_VALUE)
						)
					{
						grid.z[R][C] = BLANK_VALUE;
					}
					else
					{
						grid.z[R][C] = lattice.grid4Section.v[p][r][long(floor(cc))] + (cc - floor(cc)) * 
							(lattice.grid4Section.v[p][r][long(ceil(cc))] - lattice.grid4Section.v[p][r][long(floor(cc))]);
					}
				}
			}
		}	
	}
	::UpdateExtremums(grid);
}

void Cube4D::Produce3DSurferGrid7_XZ(double plane[4], SURFER7GRIDSECTION & grid)
{
	long p,r,c,R,C;
	double x,y,z;
	double pp, cc, rr;
	grid.BlankValue = BLANK_VALUE;
	grid.Rotation = 0.0;
	//else if (fabs(plane[1]) >= fabs(plane[0]) && fabs(plane[1]) >= fabs(plane[2]))
	if (fabs(plane[1]) > 1e-16 && fabs(lattice.grid4Section.ySize) > 1e-16)
	{
		// доминирует направление вдоль оси Y
		if (grid.nCol == lattice.grid4Section.nCol && grid.nRow == lattice.grid4Section.nPag && grid.z)
		{
		}
		else
		{
			FreeDoubleMat(grid.z);
			grid.nRow = lattice.grid4Section.nPag;
			grid.nCol = lattice.grid4Section.nCol;
			grid.z = AllocDoubleMat(grid.nRow, grid.nCol);
		}

		grid.xLL = lattice.grid4Section.xLL;
		grid.yLL = lattice.grid4Section.zLL;
		grid.xSize = lattice.grid4Section.xSize;
		grid.ySize = lattice.grid4Section.zSize;

		for(c = 0; c < lattice.grid4Section.nCol; c++)
		{
			x = lattice.grid4Section.xLL + c * lattice.grid4Section.xSize;
			C = c;
			for(p = 0; p < lattice.grid4Section.nPag; p++)
			{
				R = p;
				z = lattice.grid4Section.zLL + p * lattice.grid4Section.zSize;
				y = -(plane[0]*x+plane[2]*z+plane[3])/plane[1];
				rr = (y-lattice.grid4Section.yLL) / lattice.grid4Section.ySize;

				if (rr < 0.0 || rr > lattice.grid4Section.nRow-1) 
				{
					grid.z[R][C] = BLANK_VALUE;
				}
				else
				{
					if (
						(lattice.grid4Section.v[p][long(floor(rr))][c] == BLANK_VALUE)
						||
						(lattice.grid4Section.v[p][long(ceil(rr))][c] == BLANK_VALUE)
						)
					{
						grid.z[R][C] = BLANK_VALUE;
					}
					else
					{
						grid.z[R][C] = lattice.grid4Section.v[p][long(floor(rr))][c] + (rr - floor(rr)) * 
							(lattice.grid4Section.v[p][long(ceil(rr))][c] - lattice.grid4Section.v[p][long(floor(rr))][c]);
					}
				}
			}
		}		
	}
	::UpdateExtremums(grid);
}
void Cube4D::Produce3DSurferGrid7_XY(double plane[4], SURFER7GRIDSECTION & grid)
{
	long p,r,c,R,C;
	double x,y,z;
	double pp, cc, rr;
	grid.BlankValue = BLANK_VALUE;
	grid.Rotation = 0.0;
	//if (fabs(plane[2]) >= fabs(plane[0]) && fabs(plane[2]) >= fabs(plane[1]))
	if (fabs(plane[2]) > 1e-16 && fabs(lattice.grid4Section.zSize) > 1e-16)
	{
		// доминирует направление вдоль оси Z
		if (grid.nCol == lattice.grid4Section.nCol && grid.nRow == lattice.grid4Section.nRow && grid.z)
		{
		}
		else
		{
			FreeDoubleMat(grid.z);
			grid.nRow = lattice.grid4Section.nRow;
			grid.nCol = lattice.grid4Section.nCol;
			grid.z = AllocDoubleMat(grid.nRow, grid.nCol);
		}
		grid.xLL = lattice.grid4Section.xLL;
		grid.yLL = lattice.grid4Section.yLL;
		grid.xSize = lattice.grid4Section.xSize;
		grid.ySize = lattice.grid4Section.ySize;
		for(r = 0; r < lattice.grid4Section.nRow; r++)
		{
			y = lattice.grid4Section.yLL + r * lattice.grid4Section.ySize;
			R = r;
			for(c = 0; c < lattice.grid4Section.nCol; c++)
			{
				C = c;
				x = lattice.grid4Section.xLL + c * lattice.grid4Section.xSize;
				z = -(plane[0]*x+plane[1]*y+plane[3])/plane[2];
				pp = (z-lattice.grid4Section.zLL) / lattice.grid4Section.zSize;
				if (pp < 0.0 || pp > lattice.grid4Section.nPag-1) 
					grid.z[R][C] = BLANK_VALUE;
				else 
				{
					if(
						(lattice.grid4Section.v[long(floor(pp))][r][c] == BLANK_VALUE)
						||
						(lattice.grid4Section.v[long(ceil(pp))][r][c] == BLANK_VALUE)
						)
					{
						grid.z[R][C] = BLANK_VALUE;
					}
					else
					{
						grid.z[R][C] = lattice.grid4Section.v[long(floor(pp))][r][c] + (pp - floor(pp)) * 
							(lattice.grid4Section.v[long(ceil(pp))][r][c] - lattice.grid4Section.v[long(floor(pp))][r][c]);
					}
				}
			}
		}
	}
	::UpdateExtremums(grid);
}
int Cube4D::Produce3DSurferGrid7(double plane[4], SURFER7GRIDSECTION & grid)
{
	// определяем преимущественное направление вектора нормали к плоскости
	if (fabs(plane[2]) >= fabs(plane[0]) && fabs(plane[2]) >= fabs(plane[1]))
	{
		// доминирует направление вектора нормали вдоль оси Z
		this->Produce3DSurferGrid7_XY(plane, grid);
		return 3;
	}
	else if (fabs(plane[0]) >= fabs(plane[1]) && fabs(plane[0]) >= fabs(plane[2]))
	{
		// доминирует направление вектора нормали вдоль оси X
		this->Produce3DSurferGrid7_YZ(plane, grid);
		return 1;
	}
	else if (fabs(plane[1]) >= fabs(plane[0]) && fabs(plane[1]) >= fabs(plane[2]))
	{
		// доминирует направление вектора нормали вдоль оси Y
		this->Produce3DSurferGrid7_XZ(plane, grid);
		return 2;
	}
	return 0;
}

void Cube4D::Projection(Karotazh& karotazh)
{
	//if (well
	for (vector<CPoint4>::iterator it = karotazh.m_vdPoints.begin(); it != karotazh.m_vdPoints.end(); it++)
	{
		CPoint3 pt;
		pt.x = (*it).x;
		pt.y = (*it).y;
		pt.z = (*it).z;

		double v;
		if(this->Projection(pt,v))
		{
			printf("karotazh.v = %f\tprojection v = %f\t delta = %f\n", (*it).v, v, (*it).v - v);
		}
		else
			printf("karotazh.v = %f\tprojection false\n", (*it).v);

	}
}

bool Cube4D::Projection(CPoint3 & pt, double & v)
{
	// x = lattice.grid4Section.xLL + c * lattice.grid4Section.xSize;
	// y = lattice.grid4Section.yLL + r * lattice.grid4Section.ySize;
	// z = lattice.grid4Section.zLL + p * lattice.grid4Section.pSize;

	double cc = (pt.x - lattice.grid4Section.xLL) / lattice.grid4Section.xSize;
	double rr = (pt.y - lattice.grid4Section.yLL) / lattice.grid4Section.ySize;
	double pp = (pt.z - lattice.grid4Section.zLL) / lattice.grid4Section.zSize;

	if (cc < 0.0 || cc > lattice.grid4Section.nCol-1) return false;
	if (rr < 0.0 || rr > lattice.grid4Section.nRow-1) return false;
	if (pp < 0.0 || pp > lattice.grid4Section.nPag-1) return false;		

	long r,c,p;
	r = floor(rr);	c = floor(cc);	p = floor(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = floor(rr);	c = floor(cc);	p = ceil(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = floor(rr);	c = ceil(cc);	p = floor(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = ceil(rr);	c = floor(cc);	p = floor(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = floor(rr);	c = ceil(cc);	p = ceil(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = ceil(rr);	c = floor(cc);	p = ceil(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = ceil(rr);	c = ceil(cc);	p = floor(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;
	r = ceil(rr);	c = ceil(cc);	p = ceil(pp);
	if(lattice.grid4Section.v[p][r][c] == BLANK_VALUE) return false;


	double vv[6];

	r = floor(rr);
	c = floor(cc);
	vv[0] = lattice.grid4Section.v[long(floor(pp))][r][c] + (pp - floor(pp)) * 
					(lattice.grid4Section.v[long(ceil(pp))][r][c] - lattice.grid4Section.v[long(floor(pp))][r][c]);
	r = floor(rr);
	c = ceil(cc);
	vv[1] = lattice.grid4Section.v[long(floor(pp))][r][c] + (pp - floor(pp)) * 
					(lattice.grid4Section.v[long(ceil(pp))][r][c] - lattice.grid4Section.v[long(floor(pp))][r][c]);

	
	vv[2] = vv[0] + (cc - floor(cc)) * (vv[1] - vv[0]);

	r = ceil(rr);
	c = floor(cc);
	vv[3] = lattice.grid4Section.v[long(floor(pp))][r][c] + (pp - floor(pp)) * 
					(lattice.grid4Section.v[long(ceil(pp))][r][c] - lattice.grid4Section.v[long(floor(pp))][r][c]);
	r = ceil(rr);
	c = ceil(cc);
	vv[4] = lattice.grid4Section.v[long(floor(pp))][r][c] + (pp - floor(pp)) * 
					(lattice.grid4Section.v[long(ceil(pp))][r][c] - lattice.grid4Section.v[long(floor(pp))][r][c]);
	
	
	vv[5] = vv[3] + (cc - floor(cc)) * (vv[4] - vv[3]);
	
	v = vv[2] + (rr - floor(rr)) * (vv[5] - vv[2]);

	return true;
}




#if CUBE4D_AS_PRIMITIVE

BOOL Cube4D::GetPoint(int iz, int iy, int ix, CPoint4 *pt)
{
	int i = 
		iz * m_leny * m_lenx 
		+ 
		iy * m_lenx
		+ 
		ix;
	if(i < GetPointsNumber())
	{
		*pt = m_vdPoints[i];
		return TRUE;
	}
	else
		return FALSE;

}
#endif
Cube4D::~Cube4D()
{
//	MessageBox(0,"~Cube4D()","",0);
}

HTREEITEM Cube4D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
printf("Cube4D::AddItem_ToTree(HTREEITEM h1 = 0x%08x)\t\"%s\"\n", h1, this->GetName().c_str());
   char szItemText[4098]; // label text of tree-view item 
#if CUBE4D_AS_PRIMITIVE
	sprintf(szItemText, "nx = %d ny = %d nz = %d color = %u", m_lenx, m_leny, m_lenz, m_color);
#else
	//sprintf(szItemText, "color = %u", m_color);
	sprintf(szItemText, "%s", this->GetName().c_str());
#endif
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
void Cube4D::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_CUBE_SAVEAS3DGRID, "&Save As 3D grid" );
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
#endif /*!VIEW_ONLY_VERSION*/
}
bool Cube4D::SaveAs()
{
	bool status = false;
	DWORD nFilterIndex = 0;
	char file[2048];
	file[0] = '\0';
	strcpy(file, this->name.c_str());
	if (SaveFileDlg(this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL, file,
		"Cube 3D grid(*.cub)\0*.cub\0"
		"VTK(*.vtk)\0*.vtk\0"
		"IsoSurface 3D Dxf(*.dxf)\0*.dxf\0"
		"Golden Surfer XY clices (*.grd)\0*.grd\0"
		"Golden Surfer XZ clices (*.grd)\0*.grd\0"
		"Golden Surfer YZ clices (*.grd)\0*.grd\0"
		"All files \0*.*\0", nFilterIndex) == S_OK)
	{	
		switch(nFilterIndex)
		{
		case 1:
			status = SaveAs3DGrid(file);
			break;
		case 2:
			status = SaveAsVTK(file);
			break;
		case 3:
			status = SaveAsDxf_OfOneIsoSurface(file);
			break;
		case 4:
			status = SaveAsSurferClices(1);
			break;
		case 5:
			status = SaveAsSurferClices(2);
			break;
		case 6:
			status = SaveAsSurferClices(3);
			break;
		}
		
	}
	return status;
}
void Cube4D::Produce3DSurferGrid7_XY(long pp, SURFER7GRIDSECTION & grid)
{
	long r,c,R,C;
	grid.BlankValue = BLANK_VALUE;
	grid.Rotation = 0.0;
	//if (fabs(plane[2]) >= fabs(plane[0]) && fabs(plane[2]) >= fabs(plane[1]))
	{
		// доминирует направление вдоль оси Z
		if (grid.nCol == lattice.grid4Section.nCol && grid.nRow == lattice.grid4Section.nRow)
		{
		}
		else
		{
			FreeDoubleMat(grid.z);
			grid.nRow = lattice.grid4Section.nRow;
			grid.nCol = lattice.grid4Section.nCol;
			grid.z = AllocDoubleMat(grid.nRow, grid.nCol);
		}
		grid.xLL = lattice.grid4Section.xLL;
		grid.yLL = lattice.grid4Section.yLL;
		grid.xSize = lattice.grid4Section.xSize;
		grid.ySize = lattice.grid4Section.ySize;
		for(r = 0; r < lattice.grid4Section.nRow; r++)
		{
			R = r;
			for(c = 0; c < lattice.grid4Section.nCol; c++)
			{
				C = c;
				if (pp < 0 || pp > lattice.grid4Section.nPag-1) 
					grid.z[R][C] = BLANK_VALUE;
				else 
				{
					grid.z[R][C] = lattice.grid4Section.v[pp][r][c];
				}
			}
		}
	}
	::UpdateExtremums(grid);
}
void Cube4D::Produce3DSurferGrid7_XZ(long rr, SURFER7GRIDSECTION & grid)
{
	long p,c,R,C;
	grid.BlankValue = BLANK_VALUE;
	grid.Rotation = 0.0;
	//else if (fabs(plane[1]) >= fabs(plane[0]) && fabs(plane[1]) >= fabs(plane[2]))
	{
		// доминирует направление вдоль оси Y
		if (grid.nCol == lattice.grid4Section.nCol && grid.nRow == lattice.grid4Section.nPag)
		{
		}
		else
		{
			FreeDoubleMat(grid.z);
			grid.nRow = lattice.grid4Section.nPag;
			grid.nCol = lattice.grid4Section.nCol;
			grid.z = AllocDoubleMat(grid.nRow, grid.nCol);
		}
		grid.xLL = lattice.grid4Section.xLL;
		grid.yLL = lattice.grid4Section.zLL;
		grid.xSize = lattice.grid4Section.xSize;
		grid.ySize = lattice.grid4Section.zSize;
		for(c = 0; c < lattice.grid4Section.nCol; c++)
		{
			C = c;
			for(p = 0; p < lattice.grid4Section.nPag; p++)
			{
				R = p;
				if (rr < 0 || rr > lattice.grid4Section.nRow-1) 
					grid.z[R][C] = BLANK_VALUE;
				else
				{
					grid.z[R][C] = lattice.grid4Section.v[p][rr][c];
				}
			}
		}		
	}
	::UpdateExtremums(grid);
}
void Cube4D::Produce3DSurferGrid7_YZ(long cc, SURFER7GRIDSECTION & grid)
{
	long p,r,R,C;
	grid.BlankValue = BLANK_VALUE;
	grid.Rotation = 0.0;
	//else if (fabs(plane[0]) >= fabs(plane[1]) && fabs(plane[0]) >= fabs(plane[2]))
	{
		// доминирует направление вдоль оси X
		if (grid.nCol == lattice.grid4Section.nRow && grid.nRow == lattice.grid4Section.nPag)
		{
		}
		else
		{
			FreeDoubleMat(grid.z);
			grid.nRow = lattice.grid4Section.nPag;
			grid.nCol = lattice.grid4Section.nRow;
			grid.z = AllocDoubleMat(grid.nRow, grid.nCol);
		}
		grid.xLL = lattice.grid4Section.yLL;
		grid.yLL = lattice.grid4Section.zLL;
		grid.xSize = lattice.grid4Section.ySize;
		grid.ySize = lattice.grid4Section.zSize;
		for(r = 0; r < lattice.grid4Section.nRow; r++)
		{
			C = r;
			for(p = 0; p < lattice.grid4Section.nPag; p++)
			{
				R = p;
				if (cc < 0 || cc > lattice.grid4Section.nCol-1)
					grid.z[R][C] = BLANK_VALUE;
				else
				{
					grid.z[R][C] = lattice.grid4Section.v[p][r][cc];	
				}
			}
		}	
	}
	::UpdateExtremums(grid);
}
bool Cube4D::SaveAsSurferClices(int nProjection)
{

	static Grid grid;// грид для построения и сохранения разреза куба

	TCHAR lpstrFile[4098];	
	char my_name[1024]; sprintf(my_name, this->GetName().c_str());
	char * p = NULL; 	
	p = strrchr (my_name,'/');
	if (p == NULL)
	{
		p = strrchr (my_name,'\\');
		if (p == NULL) 
			p = my_name;
		else
			p++;					
	}
	else
		p++;

	char projection[8];
	switch (nProjection)
	{
	case 1:
		{
			sprintf (projection, "XY\0");
		}
		break;
	case 2:
		{
			sprintf (projection, "XZ\0");
		}
		break;
	case 3:
		{
			sprintf (projection, "YZ\0");
		}
		break;
	}

	sprintf(lpstrFile, "%s\\slice_%s_of_%s", directory, 
		projection, p);

	TCHAR filter[] =    
			TEXT("Surfer 7 (*.grd)\0*.grd\0")
            TEXT("All Files (*.*)\0*.*\0");

	DWORD nFilterIndex = 0;

	if (SaveProfDlg(0, lpstrFile, filter, nFilterIndex, Cube4D::sprData) != S_OK)
		return false;

	switch(nProjection)
	{
	case 1:
		{
			return SaveAsSurferClicesXY(lpstrFile, grid);	
		}
		break;
	case 2:
		{
			return SaveAsSurferClicesXZ(lpstrFile, grid);	
		}
		break;
	case 3:
		{
			return SaveAsSurferClicesYZ(lpstrFile, grid);	
		}
		break;
	}
	return true;
}

bool Cube4D::SaveAsSurferClicesXY(const char * outfile, Grid & grid)
{
	TCHAR lpstrFile[4098];
	for (long pp = 0; pp < lattice.grid4Section.nPag; pp++)
	{
		double z = this->lattice.grid4Section.zLL + pp * this->lattice.grid4Section.zSize; 
		sprintf(lpstrFile, "%s_z=%f_%02d.grd", outfile, z, pp);
		this->Produce3DSurferGrid7_XY(pp, grid.gridSection);
		SaveAsSurfer7Grid(lpstrFile, &grid);
	}
	return true;
}
bool Cube4D::SaveAsSurferClicesXZ(const char * outfile, Grid & grid)
{
	TCHAR lpstrFile[4098];
	for (long rr = 0; rr < lattice.grid4Section.nRow; rr++)
	{
		double y = lattice.grid4Section.yLL + rr * lattice.grid4Section.ySize;
		sprintf(lpstrFile, "%s_y=%f_%02d.grd", outfile, y, rr);
		this->Produce3DSurferGrid7_XZ(rr, grid.gridSection);
		SaveAsSurfer7Grid(lpstrFile, &grid);
	}
	return true;
}
bool Cube4D::SaveAsSurferClicesYZ(const char * outfile, Grid & grid)
{
	TCHAR lpstrFile[4098];
	for (long cc = 0; cc < lattice.grid4Section.nCol; cc++)
	{
		double x = lattice.grid4Section.xLL + cc * lattice.grid4Section.xSize;
		sprintf(lpstrFile, "%s_x=%f_%02d.grd", outfile, x, cc);
		this->Produce3DSurferGrid7_YZ(cc, grid.gridSection);
		SaveAsSurfer7Grid(lpstrFile, &grid);
	}
	return true;
}

bool Cube4D::SaveAsSurferClicesXZ(const char * outfile, Grid & grid, double x_t_povorot, double cos_ugol)
{
	TCHAR lpstrFile[4098];
	for (long rr = 0; rr < lattice.grid4Section.nRow; rr++)
	{
		double y = lattice.grid4Section.yLL + rr * lattice.grid4Section.ySize;
		sprintf(lpstrFile, "%s_y=%f_%02d_prj.grd", outfile, y, rr);
		this->Produce3DSurferGrid7_XZ(rr, grid.gridSection);

		grid.gridSection.xLL += x_t_povorot;
		grid.gridSection.xSize *= cos_ugol;

		SaveAsSurfer7Grid(lpstrFile, &grid);
	}
	return true;
}
bool Cube4D::SaveAsSurferClicesYZ(const char * outfile, Grid & grid, double y_t_povorot, double cos_ugol)
{
	TCHAR lpstrFile[4098];
	for (long cc = 0; cc < lattice.grid4Section.nCol; cc++)
	{
		double x = lattice.grid4Section.xLL + cc * lattice.grid4Section.xSize;
		sprintf(lpstrFile, "%s_x=%f_%02d_prj.grd", outfile, x, cc);
		this->Produce3DSurferGrid7_YZ(cc, grid.gridSection);

		grid.gridSection.xLL += y_t_povorot;
		grid.gridSection.xSize *= cos_ugol;
						
		SaveAsSurfer7Grid(lpstrFile, &grid);
	}
	return true;
}

bool Cube4D::SaveAsDxf_OfOneIsoSurface(const char * outfile)
{			
	bool view = false;
	int answer = MessageBox(0, "Save in document coordinates - Yes\nSave in view coordinates - No", "Cube4D::SaveAsDxf_OfOneIsoSurface()", MB_YESNOCANCEL);
	switch (answer)
	{
	case IDYES:
		{
			view = false;
		}
		break;	
	case IDNO:
		{
			view = true;
		}
		break;
	default :
		return false;
	}

	char * p = (char *)strrchr(outfile, '.');
	if(p && view) sprintf(p, "%s\0", "_view.dxf");

	double mu = (m_isolevel - this->lattice.grid4Section.vMin)/(this->lattice.grid4Section.vMax - this->lattice.grid4Section.vMin);
	int alpha = int(255.0);
	COLORREF c = this->m_palette.GetColor(mu);		
	
	bool useblock = false;
	char layername[1024];

	//sprintf(layername, "isosurface_of_level_%f\0", m_isolevel);
	sprintf(layername, "isosurface\0", m_isolevel);
	return IzoSurface_save_as_3D_dxf(outfile, useblock, layername,  m_isolevel, &this->lattice, c, view);
}

bool Cube4D::SaveAsGrid_OfOneIsoSurface(const char * outfile)
{			
	bool go_up = false;
	int answer = MessageBox(0, "Save in go up mode (recommended) - Yes\nSave in go down mode - No", "Cube4D::SaveAsGrid_OfOneIsoSurface()", MB_YESNOCANCEL);
	switch (answer)
	{
	case IDYES:
		{
			go_up = true;
		}
		break;	
	case IDNO:
		{
			go_up = false;
		}
		break;
	default :
		return false;
	}

	char * p = (char *)strrchr(outfile, '.');
	if(p) sprintf(p, "%s\0", go_up ? "_go_up.grd" : "_go_down.grd");

	double mu = (m_isolevel - this->lattice.grid4Section.vMin)/(this->lattice.grid4Section.vMax - this->lattice.grid4Section.vMin);
	int alpha = int(255.0);
	COLORREF c = this->m_palette.GetColor(mu);		

	Grid grid;

	grid.faultSection.nTraces = 0;
	grid.faultSection.nVertices = 0;
	grid.faultSection.traces = NULL;
	grid.faultSection.vertexes = NULL;

	grid.gridSection.BlankValue = BLANK_VALUE;
	grid.gridSection.Rotation = 0;

	grid.gridSection.xLL = this->lattice.grid4Section.xLL;
	grid.gridSection.yLL = this->lattice.grid4Section.yLL;

	grid.gridSection.xSize = this->lattice.grid4Section.xSize;
	grid.gridSection.ySize = this->lattice.grid4Section.ySize;

	grid.gridSection.nCol = this->lattice.grid4Section.nCol;
	grid.gridSection.nRow = this->lattice.grid4Section.nRow;

	grid.gridSection.z = AllocDoubleMat(grid.gridSection.nRow, grid.gridSection.nCol);
	

	if(go_up)
	{
		for(long r = 0; r < this->lattice.grid4Section.nRow; r++)
		{
			for(long c = 0; c < this->lattice.grid4Section.nCol; c++)
			{				
				grid.gridSection.z[r][c] = BLANK_VALUE;

				for(long p1 = 0, p2 = 1; p2 < this->lattice.grid4Section.nPag; p1++, p2++)
				{	

					double v1 = this->lattice.grid4Section.v[p1][r][c];
					double v2 = this->lattice.grid4Section.v[p2][r][c];				
					double z1 = this->lattice.grid4Section.zLL + p1 * this->lattice.grid4Section.zSize;
					double z2 = this->lattice.grid4Section.zLL + p2 * this->lattice.grid4Section.zSize;

					if (v1 != BLANK_VALUE && v2 != BLANK_VALUE)
					{
						if (m_isolevel >= min(v1,v2) && m_isolevel <= max(v1,v2))
						{
							double mu, z;
							//z2 > z1
							if (v2 > v1)
							{                            
								mu = (m_isolevel - v1) / (v2 - v1);
								z = z1 + mu * (z2 - z1);
							}
							else
							{
								mu = (m_isolevel - v2) / (v1 - v2);
								z = z2 - mu * (z2 - z1);
							}
							grid.gridSection.z[r][c] = z;
							break;
						}
					}
				}
			}
		}
	}
	else
	{
		for(long r = 0; r < this->lattice.grid4Section.nRow; r++)
		{
			for(long c = 0; c < this->lattice.grid4Section.nCol; c++)
			{				
				grid.gridSection.z[r][c] = BLANK_VALUE;

				for(long p1 = this->lattice.grid4Section.nPag - 2, 
					p2 = this->lattice.grid4Section.nPag - 1; 
					p1 >= 0; p1--, p2--)
				{	

					double v1 = this->lattice.grid4Section.v[p1][r][c];
					double v2 = this->lattice.grid4Section.v[p2][r][c];				
					double z1 = this->lattice.grid4Section.zLL + p1 * this->lattice.grid4Section.zSize;
					double z2 = this->lattice.grid4Section.zLL + p2 * this->lattice.grid4Section.zSize;

					if (v1 != BLANK_VALUE && v2 != BLANK_VALUE)
					{
						if (m_isolevel >= min(v1,v2) && m_isolevel <= max(v1,v2))
						{
							double mu, z;
							//z2 > z1
							if (v2 > v1)
							{                            
								mu = (m_isolevel - v1) / (v2 - v1);
								z = z1 + mu * (z2 - z1);
							}
							else
							{
								mu = (m_isolevel - v2) / (v1 - v2);
								z = z2 - mu * (z2 - z1);
							}
							grid.gridSection.z[r][c] = z;
							break;
						}
					}
				}
			}
		}
	}
	::UpdateExtremums(grid.gridSection);

	::SaveAsSurfer7Grid(outfile, &grid);
	
	FreeDoubleMat(grid.gridSection.z);

}

bool Cube4D::SaveAsVTK(const char * file)
{
	int answer = MessageBox(0, "Save in document coordinates - Yes\nSave in view coordinates - No", "Cube4D::SaveAsVTK()", MB_YESNOCANCEL);
	bool view;
	switch (answer)
	{
	case IDYES:
		{
			view = false;
		}
		break;	
	case IDNO:
		{
			view = true;
		}
		break;
	default :
		return false;
	}
	char * p = (char *)strrchr(file, '.');
	if(p && view) sprintf(p, "%s\0", "_view.vtk");

#if CUBE4D_AS_PRIMITIVE

	Grid4* grid = new Grid4;
	if (this->MakeGridSection(&grid->grid4Section))
	{
		::SaveAsVTK(file, grid);
		// free 
		if (grid->grid4Section.v) 
		{
			Free3DMat<double>(grid->grid4Section.v);
			grid->grid4Section.v = NULL;
		}
	}
	if (grid) delete grid;
#else
	if (::SaveAsVTK(file, &lattice, view) == 0)
		return true;
	else
		return false;
#endif

}
bool Cube4D::SaveAs3DGrid(const char * file)
{
	
#if CUBE4D_AS_PRIMITIVE

	Grid4* grid = new Grid4;
	if (this->MakeGridSection(&grid->grid4Section))
	{
		::SaveAsSurfer7Grid4(file, grid);
		// free 
		if (grid->grid4Section.v) 
		{
			Free3DMat<double>(grid->grid4Section.v);
			grid->grid4Section.v = NULL;
		}
	}
	if (grid) delete grid;
#else
	if (::SaveAsSurfer7Grid4(file, &lattice) == 0)
		return true;
	else
		return false;
#endif

}
#if CUBE4D_AS_PRIMITIVE

void Cube4D::Drawing()
{
	if (m_pSurfDoc)
	{
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());
		if (m_lenx > 0 && m_leny > 0 && m_lenz > 0)
		{


			//====== Размеры изображаемого объекта
			UINT	nx = m_lenx-1,
					ny = m_leny-1,
					nz = m_lenz-1;

			int q = 0;

			/// drawing of contour triangles
			//  glBegin (GL_TRIANGLES);

			PRIMITIVE_POINTS_PTR(CPoint4) ptv;
			PRIMITIVE_POINTS_PTR(CPoint4) ptd;

			ptv = m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
			ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

			double delta_v = this->m_vMax - this->m_vMin;

			//grid4Section->xSize  = this->GetDocumentPoint(1).x - this->GetDocumentPoint(0).x;
			//grid4Section->ySize  = this->GetDocumentPoint(m_lenx).y - this->GetDocumentPoint(0).y;
			//grid4Section->zSize  = this->GetDocumentPoint(m_lenx*m_lenx).z - this->GetDocumentPoint(0).z;

			double xSize  = this->GetViewPoint(1).x - this->GetViewPoint(0).x;
			double ySize  = this->GetViewPoint(m_lenx).y - this->GetViewPoint(0).y;
			double zSize  = this->GetViewPoint(m_lenx*m_lenx).z - this->GetViewPoint(0).z;

			for (UINT z=0, i=0;  z<m_lenz;  z++)
			{
				for (UINT y=0;  y<m_leny;  y++)
				{
					//====== Цикл прохода вдоль оси X
					for (UINT x=0;  x<m_lenx;  x++)
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
							vi = ptv[i].v;

						bool 
							bi = ptv[i].bVisible;

						if (bi)
						{

							double vdi = ptd[i].v;

							COLORREF sphereColor = m_color;
							if (m_pSurfDoc->m_bUseColormapOnSurf)
							{


								/*UINT color_i;
								int palette_len = m_pSurfDoc->m_palette.GetLen()-1;

								if (m_pSurfDoc->m_bInverseColormap)
								{
									color_i = UINT(0.5+(m_vMax - vdi) / (delta_v) * double(palette_len)); 

								}
								else
								{
									color_i = UINT(0.5+(vdi - m_vMin) / (delta_v) * double(palette_len)); 
								}

								sphereColor = m_pSurfDoc->m_palette.GetColor(color_i);*/

								sphereColor = this->GetColor(vdi);
							}
#if 1
							GLfloat radius = m_pSurfDoc->m_sphere_radius;
							radius *= (vdi - m_vMin) / (delta_v);
							radius += 0.01*m_pSurfDoc->m_sphere_radius;

							//radius = xSize;

							double mu = (vdi - m_vMin) / (delta_v);

							double alpha = 255 * mu;

	                        
							glPointSize(radius);
							glBegin(GL_POINTS);
							glColor4ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor), (GLubyte)alpha); 

							glVertex3d (xi, 
								yi, 
								zi);
							
							glEnd();
#else
							glColor3ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor)); 

							GLUquadricObj* pSphere = gluNewQuadric();
							gluQuadricDrawStyle(pSphere, GLU_FILL);
							glPushMatrix();//перейдём к новым координатам, сохранив старые
							
							glTranslated(
								xi, 
								yi, 
								zi
								);

							double radius = m_pSurfDoc->m_sphere_radius;

							radius *= (vdi - m_vMin) / (delta_v);

							radius += 0.01*m_pSurfDoc->m_sphere_radius;


							gluSphere(pSphere, 
								radius, 
								m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
								m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
								) ;//рисуем сферу 
							glPopMatrix(); //возвращаемся к старым координатам 
							gluDeleteQuadric(pSphere);
#endif
						}
						i++;
					}
				}
			}




#if 0
			VERT *Vert = new VERT[(nx+1)*(ny+1)];
			QUAD *Quad = new QUAD[nx*ny];
			//====== Цикл прохода по слоям изображения (ось Z)
			for (UINT z=0, i=0;  z<nz;  z++, i++)
			{
				for (UINT y=0;  y<ny;  y++, i++)
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


						int nb = int(bi) + int(bj) + int(bk) + int(bn);
						// i	n
						//
						// j	k

					}
				}
			}


			//====== Задание адресов трех массивов (вершин,
			//====== нормалей и цветов),
			//====== а также шага перемещения по ним
			glVertexPointer(3, GL_PRECISION, sizeof(VERT), &Vert->v);
			glNormalPointer(GL_PRECISION, sizeof(VERT), &Vert->n);
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT),
															&Vert->c);
	//WriteRaporto("Cube4D pre glNewList\n");
			//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
			//====== Установка режима заполнения
			//====== внутренних точек полигонов
			GLint oldPolygonMode[2];
			glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
			glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

			//WriteRaporto("Cube4D post glNewList\n");

			//====== Формирование списка рисующих команд
			//if (!m_bQuad)
			//	glDrawElements(GL_QUAD_STRIP, 4*q/*nx*ny*4*/,
			//						GL_UNSIGNED_INT, Quad);
			//else
				glDrawElements(GL_QUADS, 4*q/*nx*ny*4*/,
									GL_UNSIGNED_INT, Quad);

			glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
			//glEndList();
			
			//== Освобождение памяти, так как список сформирован
			delete [] Vert;
			delete [] Quad;
#endif
		}
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
	}
}

#else
/*void Cube4D::DrawGDIplusOfOneIsoSurface(gdiplus_map_view * v, Profile3D * on)
{
}
void Cube4D::DrawGDIplusOfManyIsoSurfaces(gdiplus_map_view * v, Profile3D * on)
{
}
void Cube4D::DrawGDIplusAsScatterPlot(gdiplus_map_view * v, Profile3D * on)
{
}
void Cube4D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{	
	if (this->draw_as_one_isosurface)
		DrawGDIplusOfOneIsoSurface(v, on);
	if (this->draw_as_many_isosurfaces)
		DrawGDIplusOfManyIsoSurfaces(v, on);
	if (this->draw_as_scatter_plot)
		DrawGDIplusAsScatterPlot(v, on);
#if 0
	fGL x1; fGL y1;
	fGL x2; fGL y2;

	Graphics graphics(v->GetHDC());
	v->PreConvertingFromWorldToScreen();


	COLORREF line_color = RGB(0,255,0);							


	Color gdi_color(255, GetRValue(line_color),GetGValue(line_color),GetBValue(line_color));
	Pen      pen(gdi_color);

	double dist_to_plane;
	CPoint2 profile;

	//Convert3D_To_2D
	on->Projection(CPoint3(x,y,min_z), profile, dist_to_plane);
	v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
	//if (to_fill_circles&& !(m_vdPoints[0].flag & CPOINT3_FLAG_HIDE)) 
	//	FillCircle(&graphics, x1, y1, r, gdi_color);
		
	//Convert3D_To_2D
	on->Projection(CPoint3(x,y,max_z), profile, dist_to_plane);
	v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);
	//if (to_fill_circles && !(m_vdPoints[i1].flag & CPOINT3_FLAG_HIDE)) 
	//	FillCircle(&graphics, x2, y2, r, gdi_color);
		
	graphics.DrawLine(&pen, x1, y1, x2, y2);

			
	SolidBrush  brush(Color(255, 0, 0, 255));
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

	wchar_t str[256];
	wsprintfW(str, L"%s\0", this->name.c_str());								
	PointF      pointF(x1 - 0.5*font.GetHeight(&graphics) * wcslen(str), y1 - font.GetHeight(&graphics)/2);                                    
	graphics.DrawString(str, -1, &font, pointF, &brush);


	double r = 5;
	for(size_t i = 0; i < this->zv.size(); i++)
	{
		COLORREF color = this->colors[i];
		Color gdicolor(255, GetRValue(color),GetGValue(color),GetBValue(color));

		
		float _x,_y;
					//Convert3D_To_2D
					on->Projection(CPoint3(x,y,this->z[i]), profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, _x, _y);
					FillCircle(&graphics, _x, _y, r, gdicolor);
		if (true)
		{
			wchar_t buff[256];
			wsprintfW(buff, L"%s\0", this->names[i].c_str());								
			PointF      pointF(_x - 0.5*font.GetHeight(&graphics) * wcslen(str), _y - font.GetHeight(&graphics)/2);                                    
			graphics.DrawString(str, -1, &font, pointF, &brush);
		}
	}
#endif
}

*/
void Cube4D::Drawing()
{
	printf("Cube4D::Drawing()\n");
#if 0
	switch(Cube4D::s_draw_mode)
	{
	case Cube4D::draw_mode::one_isosurface:
		DrawingOfOneIsoSurface();
		break;
	case Cube4D::draw_mode::many_isosurfaces:
		DrawingOfManyIsoSurfaces();
		break;
	}
#else
	if (this->draw_as_one_isosurface)
		DrawingOfOneIsoSurface();
	if (this->draw_as_many_isosurfaces)
		DrawingOfManyIsoSurfaces();
	if (this->draw_as_scatter_plot)
		DrawingAsScatterPlot();
#endif
}
void Cube4D::DrawingOfManyIsoSurfaces()
{
	printf("Cube4D::DrawingOfManyIsoSurfaces()\n");
	//if (m_pSurfDoc)
	{
			
		glEnable(GL_LIGHTING);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		/*if (m_pSurfDoc->m_bFlatShading)
			glShadeModel (GL_FLAT);
		else*/
			glShadeModel (GL_SMOOTH);

		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
printf("this->lattice.grid4Section.vMax = %f\n", this->lattice.grid4Section.vMax);
printf("this->lattice.grid4Section.vMin = %f\n", this->lattice.grid4Section.vMin);

//for (double n = 0.0; n <= Nmax; n += 1.0)
		for(vector<double>::reverse_iterator riter = this->m_isolevels.rbegin(); riter != this->m_isolevels.rend(); riter++)
		{
			double mu = (*riter - m_min_isolevel)/(m_max_isolevel - m_min_isolevel);
			int alpha = int(m_opacity * mu * 255.0);
			COLORREF c = this->m_palette.GetColorWithAlpha(mu, alpha);
			DrawIzoSurface(*riter, &this->lattice, c);
		}
		
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
	}
}

void Cube4D::DrawingOfOneIsoSurface()
{
	printf("Cube4D::DrawingOfOneIsoSurface()\n");
	//if (m_pSurfDoc)
	{
			
		glEnable(GL_LIGHTING);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		/*if (m_pSurfDoc->m_bFlatShading)
			glShadeModel (GL_FLAT);
		else*/
			glShadeModel (GL_SMOOTH);

		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//printf("this->lattice.grid4Section.vMax = %f\n", this->lattice.grid4Section.vMax);
//printf("this->lattice.grid4Section.vMin = %f\n", this->lattice.grid4Section.vMin);
		
		//int alpha = int(mu * 255.0);
			
		double mu = (m_isolevel - this->lattice.grid4Section.vMin)/(this->lattice.grid4Section.vMax - this->lattice.grid4Section.vMin);
		int alpha = int(255.0);
		COLORREF c = this->m_palette.GetColorWithAlpha(mu, alpha);		
		DrawIzoSurface(m_isolevel, &this->lattice, c);
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
	}
}

void Cube4D::DrawingAsScatterPlot()
{
	if (m_pSurfDoc)
	{			
		for (long p = 0; p < lattice.grid4Section.nPag; p++)
		{
			for (long r = 0; r < lattice.grid4Section.nRow; r++)
			{
				for (long c = 0; c < lattice.grid4Section.nCol; c++)
				{
					if (lattice.grid4Section.v[p][r][c] != BLANK_VALUE)
					{
						double x = lattice.grid4Zoom.xLL + c * lattice.grid4Zoom.xSize;
						double y = lattice.grid4Zoom.yLL + r * lattice.grid4Zoom.ySize;
						double z = lattice.grid4Zoom.zLL + p * lattice.grid4Zoom.zSize;
						{
							//glPointSize(1.0);
							glPointSize(ThePoint3D::point_size);
							//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
							
							glBegin(GL_POINTS);
							//glColor3ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)); 
							glColor3ub (255,0,0); 
							//glVertex3fv((* it1).GetCRD(n1));

							glVertex3d (x, y, z);

							glEnd();
							
							//glPopName(); glPopName();
						}

						char str[1024];
						sprintf(str, "%f\0", lattice.grid4Section.v[p][r][c]);
						int j = strlen(str)-1;
						while (j > 0 && str[j] == '0') str[j--] = '\0';


						// label color
						COLORREF color = RGB(0,0,255);
						::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку
						// sprintf(str, "X %s", spower);
						// move 
						glRasterPos3d(x,y,z); 
						// set up for a string-drawing display List call 
						// Display a string 
						glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
						// Draw the characters in a string 
						glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}					
				}
			}
		}
	}
}

void Cube4D::ReDraw(void)
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
#endif
#if CUBE4D_AS_PRIMITIVE
void Cube4D::DrawQuadsNumbers()
{
	//====== Размеры изображаемого объекта
	UINT	nx = m_lenx-1,
			ny = m_leny-1,
			nz = m_lenz-1;

/*	CPoint3 *ptv;
	CPoint3 *ptd;
	ptv = m_vvPoints;
	ptd = m_vdPoints;*/

	PRIMITIVE_POINTS_PTR(CPoint4) ptv;
	PRIMITIVE_POINTS_PTR(CPoint4) ptd;

	ptv = m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
	ptd = m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;


	//====== Цикл прохода по слоям изображения (ось Z)
	for (UINT z=0, i=0;  z<nz;  z++, i++)
	{
		for (UINT y=0;  y<ny;  y++, i++)
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

				if (bi || bj || bk | bn)
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
}

#endif
COLORREF Cube4D::GetColor(double v)
{
	COLORREF surfColor;
	//if (this->m_pSurfDoc && this->m_pSurfDoc->m_bUseColormapOnSurf)
	if (m_bUseColormap)
	{
		double color;
		double delta_v;

#if CUBE4D_AS_PRIMITIVE
		delta_v = m_vMax - m_vMin;
		//*********************************
		if (m_bInverseColormap)
		{
			color = (m_vMax - v) / (delta_v); 
		}
		else
		{
			color = (v - m_vMin) / (delta_v); 
		}
#else
		delta_v = this->lattice.grid4Section.vMax - this->lattice.grid4Section.vMin;
		if (m_bInverseColormap)
		{
			color = (this->lattice.grid4Section.vMax - v) / (delta_v); 
		}
		else
		{
			color = (v - this->lattice.grid4Section.vMin) / (delta_v); 
		}
#endif


		surfColor = m_palette.GetColorWithAlpha(color,
							(GLubyte)m_alpha);
	}
	else
		surfColor = RGBA (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color), 
		(GLubyte)m_alpha); 

	return surfColor;

}
void Cube4D::UpdateIsolevels(bool update_one)
{
	this->m_isolevels.resize(this->m_nIsolevels);
	
	//double mu;
	//this->m_min_isolevel = this->lattice.grid4Section.vMin;
	//this->m_max_isolevel = this->lattice.grid4Section.vMax;
	//this->m_step_isolevel = (m_max_isolevel - m_min_isolevel) / m_nIsolevels;

	double v_range = m_max_isolevel - m_min_isolevel;


	for(size_t i = 0; i < this->m_nIsolevels; i++)
	{
		//mu = double(i)/double(this->m_nIsolevels);
		this->m_isolevels[i] = m_min_isolevel + i * this->m_step_isolevel;
	}
	if (this->m_iso_ind >= this->m_nIsolevels)
	{
		this->m_iso_ind = this->m_nIsolevels > 0 ? this->m_nIsolevels - 1 : 0;
	}

	if(update_one)
		this->m_isolevel = m_min_isolevel + 0.5 * v_range;
}
int Cube4D::GetAlphaSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
	switch (GetDlgCtrlID(hwnd))
	{
	//====== Выясняем идентификатор окна справа
	case IDC_SLIDER_CUBE_ISOLEVEL:
		nID = IDC_EDIT_CUBE_ISOLEVEL;
		return 0;
	case IDC_SLIDER_CUBE_ISOSURFACES_OPACITY:
		nID = IDC_EDIT_CUBE_ISOSURFACES_OPACITY;
		return 1;
	case IDC_SLIDER_CUBE_ISOLEVEL2:
		nID = IDC_EDIT_CUBE_ISOLEVEL2;
		return 2;
	case IDC_SLIDER_CUBE_ALPHA:
		nID = IDC_EDIT_CUBE_ALPHA;
		return 3;
	}
	return 0;
}

BOOL CALLBACK Cube4D::DlgProcDrawModes( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{


static Cube4D * me;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (Cube4D *)lPage->lParam;
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_ISOSURFACE,
				me->draw_as_one_isosurface ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_MANY_ISOSURFACES,
				me->draw_as_many_isosurfaces ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_SCATTER_PLOT,
				me->draw_as_scatter_plot ? BST_CHECKED : BST_UNCHECKED );			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			char str[4098];
			sprintf(str, "vMin = %f\n", me->lattice.grid4Section.vMin);
			SetDlgItemText(hDlg, IDC_STATIC_VMIN, str);
			sprintf(str, "vMax = %f\n", me->lattice.grid4Section.vMax);
			SetDlgItemText(hDlg, IDC_STATIC_VMAX, str);
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_SCATTER_PLOT:
			{
				me->draw_as_scatter_plot = IsDlgButtonChecked( hDlg, IDC_CHECK_SCATTER_PLOT) == BST_CHECKED;
				PropSheet_Changed(::GetParent(hDlg),hDlg);


				//me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				//RECT rect;
				//GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				//InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
			}
			break;
		case IDC_CHECK_ISOSURFACE:
			{
				me->draw_as_one_isosurface = IsDlgButtonChecked( hDlg, IDC_CHECK_ISOSURFACE) == BST_CHECKED;
				PropSheet_Changed(::GetParent(hDlg),hDlg);
				//me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				//RECT rect;
				//GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				//InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
			}
			break;
		case IDC_CHECK_MANY_ISOSURFACES:
			{
				me->draw_as_many_isosurfaces = IsDlgButtonChecked( hDlg, IDC_CHECK_MANY_ISOSURFACES) == BST_CHECKED;
				PropSheet_Changed(::GetParent(hDlg),hDlg);
				//me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				//RECT rect;
				//GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				//InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
			}
			break;
		}
		break;	
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						printf("PSN_APPLY\n");
						me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						RECT rect;
						GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
	default :	
		return( FALSE );
	}
	return( TRUE );
}

BOOL CALLBACK Cube4D::DlgProcIsosurfaces( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static Cube4D * me;
	static int m_Pos[11]; 			// Массив позиций ползунков
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (Cube4D *)lPage->lParam;

			char str[1023];
			sprintf(str,"%f",me->m_isolevel);
			SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOLEVEL, str);

			sprintf(str,"%f",me->m_opacity);
			SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOSURFACES_OPACITY, str);

			sprintf(str,"%u",me->m_nIsolevels);
			SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOSURFACES_NUMBER, str);			

			sprintf(str,"%f",me->m_min_isolevel);
			SetDlgItemText(hDlg, IDC_EDIT_ISOSURFACE_MIN, str);			

			sprintf(str,"%f",me->m_max_isolevel);
			SetDlgItemText(hDlg, IDC_EDIT_ISOSURFACE_MAX, str);			

			sprintf(str,"%f",me->m_step_isolevel);
			SetDlgItemText(hDlg, IDC_EDIT_ISOSURFACE_STEP, str);				
			
			
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_CUBE_ISO_COMBO ,0);			
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
					delta = -1000;
					goto New_Pos;
				case SB_RIGHT:				// Клавиша End
					delta = +1000;
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
					m_Pos[num] = newPos<0 ? 0 : newPos>1000 ? 1000 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}


				double v_range = me->lattice.grid4Section.vMax - me->lattice.grid4Section.vMin;
				double mu;
					
				char s[1024];
				//====== Синхронизируем параметр lp и
				//====== устанавливаем его в положение nPos
				switch (num)
				{
				case 0:
					{
						mu = double(m_Pos[num]) / 1000.0;
						me->m_isolevel = mu * v_range + me->lattice.grid4Section.vMin;
						//====== Синхронизируем текстовый аналог позиции
						sprintf (s, "%f", me->m_isolevel);
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
					break;
				case 1:
					{
						me->m_opacity = double(m_Pos[num]) / 1000.0;
						//====== Синхронизируем текстовый аналог позиции
						sprintf (s, "%f", me->m_opacity);
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
					break;
				case 2:
					{
						mu = double(m_Pos[num]) / 1000.0;
						me->m_isolevels[me->m_iso_ind] = mu * v_range + me->lattice.grid4Section.vMin;
						//====== Синхронизируем текстовый аналог позиции
						sprintf (s, "%f", me->m_isolevels[me->m_iso_ind]);
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
					break;
				}

				me->ReDraw();
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
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_CUBE_ISOLEVEL);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 1000)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);

				hwnd = GetDlgItem(hDlg, IDC_SLIDER_CUBE_ISOLEVEL2);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 1000)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);

				hwnd = GetDlgItem(hDlg, IDC_SLIDER_CUBE_ISOSURFACES_OPACITY);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 1000)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== Проход по всем регулировкам
				//for (int i=0; i<2; i++)
					//====== Заполняем транспортный массив pPos
				double v_range = me->lattice.grid4Section.vMax - me->lattice.grid4Section.vMin;
				double mu = (me->m_isolevel - me->lattice.grid4Section.vMin) / v_range;
					
				m_Pos[0] = int(mu*1000.0);					
				m_Pos[1] = int(me->m_opacity*1000.0);					
				mu = (me->m_isolevels[me->m_iso_ind] - me->lattice.grid4Section.vMin) / v_range;
				m_Pos[2] = int(mu*1000.0);

				//====== Массив идентификаторов ползунков
				UINT IDs[] = 
				{
					IDC_SLIDER_CUBE_ISOLEVEL,
					IDC_SLIDER_CUBE_ISOSURFACES_OPACITY,
					IDC_SLIDER_CUBE_ISOLEVEL2
				};

				//====== Цикл прохода по всем регуляторам
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== Добываем Windows-описатель окна ползунка
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== Определяем его идентификатор
					int num = Cube4D::GetAlphaSliderNum(hwnd, nID);

					// Требуем установить ползунок в положение m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					char s[1024];
					switch (num)
					{
					case 0:
						{
							//====== Синхронизируем текстовый аналог позиции
							sprintf (s, "%f", me->m_isolevel);
							SetDlgItemText(hDlg, nID, (LPCTSTR)s);
						}
						break;
					case 1:
						{
							//====== Синхронизируем текстовый аналог позиции
							sprintf (s, "%f", me->m_opacity);
							SetDlgItemText(hDlg, nID, (LPCTSTR)s);
						}
						break;
					case 2:
						{
							//====== Синхронизируем текстовый аналог позиции
							sprintf (s, "%f", me->m_isolevels[me->m_iso_ind]);
							SetDlgItemText(hDlg, nID, (LPCTSTR)s);
						}
						break;
					}
				}
			}
			break;
		case IDC_INIT_CUBE_ISO_COMBO :
			{							
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_ISOLEVEL_INDEX, CB_RESETCONTENT,0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				char str[64];
				for (size_t i = 0; i < me->m_isolevels.size(); i++)
				{
					sprintf(str, "%u", i);
					SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_ISOLEVEL_INDEX, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)str);
				}
				SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_ISOLEVEL_INDEX, CB_SETCURSEL,
					me->m_iso_ind, (LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDC_COMBO_CUBE_ISOLEVEL_INDEX :
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->m_iso_ind = SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_ISOLEVEL_INDEX, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);
			}
			break;
		case IDC_BUTTON_CUBE_ISOSURFACES_NUMBER:
			{
				char str[1023];
				

				GetDlgItemText(hDlg, IDC_EDIT_ISOSURFACE_MIN, str,1022);
				me->m_min_isolevel = atof (str);
				
				GetDlgItemText(hDlg, IDC_EDIT_ISOSURFACE_MAX, str,1022);
				me->m_max_isolevel = atof (str);
				
				GetDlgItemText(hDlg, IDC_EDIT_ISOSURFACE_STEP, str,1022);
				me->m_step_isolevel = atof (str);
				
				int n = ( me->m_max_isolevel - me->m_min_isolevel) / me->m_step_isolevel;
				sprintf(str, "%d\0", n);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOSURFACES_NUMBER, str);
				
				if (n >= 0)
				{
					if (me->m_nIsolevels != size_t(n))
					{
						me->m_nIsolevels = size_t(n);
						me->UpdateIsolevels(false);
						SendMessage(hDlg,WM_COMMAND,IDC_INIT_CUBE_ISO_COMBO ,0);	
					}
				}
				else
				{
					sprintf(str, "%u", me->m_nIsolevels);
					SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOSURFACES_NUMBER, str);
				}

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
				me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
			}
			break;
		case IDC_BUTTON_ISOSURFACE_SAVE:
			{
				bool status = false;
				DWORD nFilterIndex = 0;
				char file[2048];
				file[0] = '\0';
				sprintf(file, "%s_izolevel_%f\0", me->name.c_str(), me->m_isolevel);
				if (SaveFileDlg(me->m_pSurfDoc ? me->m_pSurfDoc->hSurfWnd : NULL, file,
					"IsoSurface 3D Dxf(*.dxf)\0*.dxf\0"
					"IsoSurface Grid (*.grd)\0*.grd\0"
					"All files \0*.*\0", nFilterIndex) == S_OK)
				{	
					switch(nFilterIndex)
					{
					case 1:
						status = me->SaveAsDxf_OfOneIsoSurface(file);
						break;
					case 2:
						status = me->SaveAsGrid_OfOneIsoSurface(file);
						break;
					}
					
				}
				return status;			
			}
			break;
		case IDOK :
			{
				char str[1023];

				GetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOLEVEL,str,1022);
				double level = atof (str);
				if(level >= me->lattice.grid4Section.vMin && level <= me->lattice.grid4Section.vMax)
					me->m_isolevel = level;
				else
				{
					if (level < me->lattice.grid4Section.vMin)
					{
						me->m_isolevel = me->lattice.grid4Section.vMin;
					}					
					if (level > me->lattice.grid4Section.vMax)
					{
						me->m_isolevel = me->lattice.grid4Section.vMin;
					}
					sprintf(str, "%f", me->m_isolevel);
					SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOLEVEL, str);
				}


				GetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOSURFACES_OPACITY,str,1022);
				double opacity = atof (str);
				if (opacity >= 0.0 && opacity <= 1.0)
					me->m_opacity = opacity;
				else
				{
					if (opacity < 0.0)
					{
						me->m_opacity = 0.0;
					}					
					if (opacity > 1.0)
					{
						me->m_opacity = 1.0;
					}
					sprintf(str, "%f", me->m_opacity);
					SetDlgItemText(hDlg, IDC_EDIT_CUBE_ISOSURFACES_OPACITY, str);
				}

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);	
				me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);

			}
			break;
		}
		break;
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						//printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						//printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						//printf("PSN_APPLY\n");
						me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						RECT rect;
						GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						//printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						//printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						//printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						//printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						//printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						//printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						//printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						//printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						//printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						//printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
	default :
			return( FALSE );
	}
	return( TRUE );
}

BOOL CALLBACK Cube4D::DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static Cube4D * me;
	static int m_Pos[11]; 			// Массив позиций ползунков
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	


			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (Cube4D *)lPage->lParam;

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
				case 2:
					me->m_alpha = m_Pos[num];
					break;
				}


				//====== Синхронизируем текстовый аналог позиции
				char s[1024];
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
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_CUBE_ALPHA);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== Проход по всем регулировкам
				//for (int i=0; i<2; i++)
					//====== Заполняем транспортный массив pPos
					m_Pos[2] = me->m_alpha;

				//====== Массив идентификаторов ползунков
				UINT IDs[] = 
				{
					IDC_SLIDER_CUBE_ALPHA,
				};

				//====== Цикл прохода по всем регуляторам
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== Добываем Windows-описатель окна ползунка
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== Определяем его идентификатор
					int num = Cube4D::GetAlphaSliderNum(hwnd, nID);

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
		}
		break;
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						//printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						//printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						//printf("PSN_APPLY\n");
						me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						RECT rect;
						GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						//printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						//printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						//printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						//printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						//printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						//printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						//printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						//printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						//printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						//printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

 
BOOL CALLBACK  Cube4D::DlgProcSurfPalette( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
//	static LPSURFDLGDATA lpSurfDlgMem;
	static Cube4D * me;
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
			me = (Cube4D *)lPage->lParam;

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_INVERSE_COLORMAP,
				me->m_bInverseColormap ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//			CheckDlgButton( hDlg, IDC_CHECK_SURF_LOCAL_COLORMAP,
//				me->m_bLocalColormap ? BST_CHECKED : BST_UNCHECKED );
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
/*		case IDC_CHECK_SURF_LOCAL_COLORMAP:
			{
				me->m_bLocalColormap = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_LOCAL_COLORMAP) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);
			}
			break;*/
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
		}
		break;
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						//printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						//printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						//printf("PSN_APPLY\n");
						me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						RECT rect;
						GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						//printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						//printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						//printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						//printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						//printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						//printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						//printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						//printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						//printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						//printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}
int Cube4D::GetCutsPlaneSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
	switch (GetDlgCtrlID(hwnd))
	{
	//====== Выясняем идентификатор окна справа
	case IDC_SLIDER_CUT_PLANE:
		nID = IDC_EDIT_SURF_CUTS_PLANE_D;
		return 0;
	}
	return 0;
}
BOOL CALLBACK Cube4D::DlgProcCubeCutsPlane( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	//static LPSURFCUTSPLANEDLGDATA lpSurfCutsPlaneDlgMem;
	static Cube4D * me;
	static double m_Pos[11]; 			// Массив позиций ползунков
	static unsigned int lastCommand;
	static double min_Dd, max_Dd;
	static double min_Dv, max_Dv;
	
	static Grid grid;// грид для построения и сохранения разреза куба
	

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			//lpSurfCutsPlaneDlgMem = (LPSURFCUTSPLANEDLGDATA)lParam;
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (Cube4D *)lPage->lParam;

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_ONE_PLANE_CUTTING_CONTROLS,0);

			SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,0);
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_CUTS_SLIDER,0);

			lastCommand = IDC_BUTTON_SURF_CUTS_PLANE;
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
				int num = GetCutsPlaneSliderNum(hwnd, nID);
				double delta, newPos;

				//====== Анализируем код события
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// Управление мышью
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// Клавиша Home
					delta = -100;
					goto New_Pos;
				case SB_RIGHT:				// Клавиша End
					delta = +100;
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
					m_Pos[num] = newPos<0 ? 0 : newPos>20000.0 ? 20000.0 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}


				//*****************************************************
				GLdouble * cut_plane;
				
				cut_plane = me->m_pSurfDoc->m_cut_plane_v;

				//*****************************************************
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);

				//====== Синхронизируем параметр lp и
				//====== устанавливаем его в положение nPos
				double mu = m_Pos[num]/20000.0;
				me->m_pSurfDoc->m_cut_plane_v[3] =  mu * (max_Dv - min_Dv) + min_Dv;
				me->m_pSurfDoc->m_cut_plane_d[3] =  mu * (max_Dd - min_Dd) + min_Dd;

				//====== Синхронизируем текстовый аналог позиции
				char s[1024];
				sprintf (s,"%lf",cut_plane[3]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				if (me->m_pSurfDoc->m_cut_plane_d[0] == 0.0 && 
					me->m_pSurfDoc->m_cut_plane_d[1] == 0.0 &&
					me->m_pSurfDoc->m_cut_plane_d[2] != 0.0)
				{
					sprintf (s,"%lf",- me->m_pSurfDoc->m_cut_plane_d[3] / me->m_pSurfDoc->m_cut_plane_d[2]);
					SetDlgItemText(hDlg, IDC_EDIT_CUBE_GORIZONTAL_CUTTING_ALTITUDE, (LPCTSTR)s);
				}
				//====== Перерисовываем Вид с учетом изменений
#if 0
				SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,1);
				SendMessage(hDlg,WM_COMMAND,lastCommand,0);
#else
				SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,0);
#endif				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_ONE_PLANE_CUTTING_CONTROLS:
			{
				char str[255];
				//*****************************************************
				GLdouble * cut_plane;
				cut_plane = me->m_pSurfDoc->m_cut_plane_v;
				//*****************************************************

				sprintf(str,"%f", cut_plane[0]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_A,str);

				sprintf(str,"%f", cut_plane[1]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_B,str);

				sprintf(str,"%f", cut_plane[2]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_C,str);

				sprintf(str,"%f", cut_plane[3]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);

				me->m_pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);
				
				sprintf(str, "interval of Dv = [%lf %lf]", min_Dv, max_Dv);
				SetDlgItemText(hDlg, IDC_STATIC_MIN_MAX_D, str);

				sprintf(str, "interval of Dd = [%lf %lf]", min_Dd, max_Dd);
				SetDlgItemText(hDlg, IDC_STATIC_MIN_MAX_DD, str);

				//*****************************************************
			}
			break;
		case IDC_INIT_SURF_CUTS_SLIDER :
			{					
				//*****************************************************
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(false,min_Dd, max_Dd);
				//*****************************************************
				GLdouble * cut_plane;
				cut_plane = me->m_pSurfDoc->m_cut_plane_v;
				//*****************************************************
				//=== Добываем Windows-описатель окна ползунка
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_CUT_PLANE);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 20000)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== Проход по всем регулировкам
				for (int i=0; i<1; i++)
					//====== Заполняем транспортный массив pPos
					m_Pos[i] = 20000.0*(cut_plane[3] - min_Dv) / (max_Dv - min_Dv);
				//====== Массив идентификаторов ползунков
				UINT IDs[] = 
				{
					IDC_SLIDER_CUT_PLANE
				};

				//====== Цикл прохода по всем регуляторам
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== Добываем Windows-описатель окна ползунка
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== Определяем его идентификатор
					int num = GetCutsPlaneSliderNum(hwnd, nID);

					// Требуем установить ползунок в положение m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE, (LPARAM)m_Pos[i]);

					if (i == 0)
					{
						char s[1024];
						//====== Готовим текстовый аналог текущей позиции
						sprintf (s, "%8.3f", cut_plane[3]);
						//====== Помещаем текст в окно справа от ползунка
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
				}
			}
			break;
		case IDC_BUTTONCUBE_GORIZONTAL_CUTTING_APPLY:
			{
				char str[1024];
				GetDlgItemText(hDlg, IDC_EDIT_CUBE_GORIZONTAL_CUTTING_ALTITUDE, str, 1022);
				double z = atof(str);


				me->m_pSurfDoc->m_cut_plane_d[0] = 0.0;
				me->m_pSurfDoc->m_cut_plane_v[0] = 0.0;

				sprintf(str, "%f", me->m_pSurfDoc->m_cut_plane_v[0]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_A,str);

				me->m_pSurfDoc->m_cut_plane_d[1] = 0.0;
				me->m_pSurfDoc->m_cut_plane_v[1] = 
					me->m_pSurfDoc->m_cut_plane_d[1] / me->m_pSurfDoc->m_zoomCoefXY;

				sprintf(str, "%f", me->m_pSurfDoc->m_cut_plane_v[1]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_B,str);

				me->m_pSurfDoc->m_cut_plane_d[2] = me->m_pSurfDoc->m_cut_plane_d[2] >= 0.0 ? 1.0 : -1.0;
				me->m_pSurfDoc->m_cut_plane_v[2] = 
					me->m_pSurfDoc->m_cut_plane_d[2] / me->m_pSurfDoc->m_zoomCoefXYZ;

				sprintf(str, "%f", me->m_pSurfDoc->m_cut_plane_v[2]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_C,str);

				me->m_pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);

				if(me->m_pSurfDoc->m_cut_plane_d[2] >= 0.0)
				{
					if (z < -max_Dd) z = -max_Dd;
					if (z > -min_Dd) z = -min_Dd;
				}
				else
				{
					if (z > max_Dd) z = max_Dd;
					if (z < min_Dd) z = min_Dd;
				}


				sprintf(str, "%f", z);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_GORIZONTAL_CUTTING_ALTITUDE, str);

				me->m_pSurfDoc->m_cut_plane_d[3] = -z*me->m_pSurfDoc->m_cut_plane_d[2];

				double mu = (me->m_pSurfDoc->m_cut_plane_d[3] - min_Dd) / (max_Dd - min_Dd);

				me->m_pSurfDoc->m_cut_plane_v[3] =
					min_Dv + mu * (max_Dv - min_Dv);

				sprintf(str, "%f", me->m_pSurfDoc->m_cut_plane_v[3]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);

				me->m_pSurfDoc->m_bDrawCutPlane = true;

				DrawCutPlane(me->m_pSurfDoc);

				//if (lParam == 0)
				{
					SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_CUTS_SLIDER,0);
					//====== Перерисовываем Вид с учетом изменений
					RECT rect;
					GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
					InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
				}

			}
			break;
		case IDC_BUTTONCUBE_GORIZONTAL_CUTTING_SAVE:
			{
				if (me->m_pSurfDoc->m_cut_plane_d[0] == 0.0 && 
					me->m_pSurfDoc->m_cut_plane_d[1] == 0.0 &&
					me->m_pSurfDoc->m_cut_plane_d[2] != 0.0
					)
				{
					TCHAR lpstrFile[1024];	
					char my_name[1024]; sprintf(my_name, me->GetName().c_str());
					char * p = NULL; 	
					p = strrchr (my_name,'/');
					if (p == NULL)
					{
						p = strrchr (my_name,'\\');
						if (p == NULL) 
							p = my_name;
						else
							p++;					
					}
					else
						p++;				

					sprintf(lpstrFile, "%s\\gor_slice_alt=%f_of_%s", directory, 
						- me->m_pSurfDoc->m_cut_plane_d[3] / me->m_pSurfDoc->m_cut_plane_d[2],
						p);

					TCHAR filter[] =    
						TEXT("Surfer 7 (*.grd)\0*.grd\0")
						TEXT("All Files (*.*)\0*.*\0");

					DWORD nFilterIndex = 0;

					if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
						return 0;
							
					me->Produce3DSurferGrid7_XY(me->m_pSurfDoc->m_cut_plane_d, grid.gridSection);	
		
					SaveAsSurfer7Grid(lpstrFile, &grid);
				}

			}
			break;
		case IDC_BUTTON_DRAW_SURF_CUTS_PLANE :
			{
				char str[1024];
				GLdouble * cut_plane;
				cut_plane = me->m_pSurfDoc->m_cut_plane_v;

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_A,str,1022);
				cut_plane[0] = atof (str);
				me->m_pSurfDoc->m_cut_plane_d[0] = cut_plane[0];

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_B,str,1022);
				cut_plane[1] = atof (str);
				me->m_pSurfDoc->m_cut_plane_d[1] = cut_plane[1]*me->m_pSurfDoc->m_zoomCoefXY;

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_C,str,1022);
				cut_plane[2] = atof (str);
				me->m_pSurfDoc->m_cut_plane_d[2] = cut_plane[2]*me->m_pSurfDoc->m_zoomCoefXYZ;

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str,1022);
				cut_plane[3] = atof (str);

				me->m_pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				me->m_pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);
					
				double mu = (cut_plane[3] - min_Dv) / (max_Dv - min_Dv);
				
				me->m_pSurfDoc->m_cut_plane_d[3] =
					min_Dd + mu * (max_Dd - min_Dd);
					

				if (cut_plane[3] > max_Dv)
				{
					cut_plane[3] = 
						(min_Dv + max_Dv) / 2.0 +
						(max_Dv - min_Dv) * 0.0;
					sprintf(str,"%lf", cut_plane[3]);
					SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);
				}
				if (cut_plane[3] < min_Dv)
				{
					cut_plane[3] = 
						(min_Dv + max_Dv) / 2.0 -
						(max_Dv - min_Dv) * 0.0;
					sprintf(str,"%lf",cut_plane[3]);
					SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);
				}

				sprintf(str, "interval of Dv = [%lf %lf]", min_Dv, max_Dv);	
				SetDlgItemText(hDlg, IDC_STATIC_MIN_MAX_D, str);

				sprintf(str, "interval of Dd = [%lf %lf]", min_Dd, max_Dd);	
				SetDlgItemText(hDlg, IDC_STATIC_MIN_MAX_DD, str);


				me->m_pSurfDoc->m_bDrawCutPlane = true;
				DrawCutPlane(me->m_pSurfDoc);

				if (lParam == 0)
				{
					SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_CUTS_SLIDER,0);
					//====== Перерисовываем Вид с учетом изменений
					RECT rect;
					GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
					InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
				}
			}
			break;
		case IDC_BUTTON_ERASE_SURF_CUTS_PLANE :
			{			
				glDeleteLists(FIRST_HARD_LIST+2,1);
				me->m_pSurfDoc->m_bDrawCutPlane = false;

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);

			}
			break;
		case IDC_BUTTON_SURF_CUTS_PLANE_SAVE:
			{
				TCHAR lpstrFile[1024];	
				char my_name[1024]; sprintf(my_name, me->GetName().c_str());
				char * p = NULL; 	
				p = strrchr (my_name,'/');
				if (p == NULL)
				{
					p = strrchr (my_name,'\\');
					if (p == NULL) 
						p = my_name;
					else
						p++;					
				}
				else
					p++;				

				sprintf(lpstrFile, "%s\\slice[%f_%f_%f_%f]_of_%s", directory, 
					me->m_pSurfDoc->m_cut_plane_d[0],
					me->m_pSurfDoc->m_cut_plane_d[1],
					me->m_pSurfDoc->m_cut_plane_d[2],
					me->m_pSurfDoc->m_cut_plane_d[3],
					p);

				TCHAR filter[] =    
					 TEXT("Surfer 7 (*.grd)\0*.grd\0")
                     TEXT("All Files (*.*)\0*.*\0");

				DWORD nFilterIndex = 0;

				if (SaveProfDlg(0, lpstrFile, filter, nFilterIndex, Cube4D::sprData) != S_OK)
					return 0;

				switch(Cube4D::sprData.export_coordinate_type)
				{
				case SAVE_PROFILE_3D_XYZ:
					{
						MessageBox(0,"Saving in this projection is imposible\nSelect another projection", "Cube4D Cut Save", MB_OK);
						return 0;
					}
					break;
				case SAVE_PROFILE_WITH_PROFILE_LEN:
					{
						MessageBox(0,"Saving in this projection is not jet realized\nSelect another projection", "Cube4D Cut Save", MB_OK);
						return 0;
					}
					break;
				case SAVE_PROFILE_AUTO_SELECT_PROJECTION:
					{
						me->Produce3DSurferGrid7(me->m_pSurfDoc->m_cut_plane_d, grid.gridSection);	
					}
					break;
				case SAVE_PROFILE_WITH_NORTH_PROJECTION:
					{
						me->Produce3DSurferGrid7_YZ(me->m_pSurfDoc->m_cut_plane_d, grid.gridSection);	
					}
					break;
				case SAVE_PROFILE_WITH_EAST_PROJECTION:
					{
						me->Produce3DSurferGrid7_XZ(me->m_pSurfDoc->m_cut_plane_d, grid.gridSection);	
					}
					break;
				case SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION:
					{
						me->Produce3DSurferGrid7_XY(me->m_pSurfDoc->m_cut_plane_d, grid.gridSection);	
					}
					break;
				}

				SaveAsSurfer7Grid(lpstrFile, &grid);

			}
			break;
		case IDC_BUTTON_SURF_CUTS_PLANE:
			{
//				GLdouble * cut_plane ;
				//if (me->m_pSurfDoc->m_bFastCutting)
				//{
					//====== Перерисовываем Вид с учетом изменений
					RECT rect;
					GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
					InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
				/*}
				else
				{
					//cut_plane = me->m_pSurfDoc->m_cut_plane_d;
					me->m_pSurfDoc->ClearCutlinesPolygones();
					me->m_pSurfDoc->Cut(false,true);
					//me->m_pSurfDoc->ZoomView();				
					me->m_pSurfDoc->ZoomViewCutlinesPolygones();
					//DrawScene(me->m_pSurfDoc);
					me->m_pSurfDoc->DrawCutPlaneLines();
					//====== Перерисовываем Вид с учетом изменений
					RECT rect;
					GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
					InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
				}*/
		
				lastCommand = IDC_BUTTON_SURF_CUTS_PLANE;

			}
			break;
	
		}
		break;
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						//printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						//printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						//printf("PSN_APPLY\n");
						me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						RECT rect;
						GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						//printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						//printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						//printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						//printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						//printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						//printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						//printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						//printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						//printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						//printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

int CALLBACK Cube4D::PropSheetProc(HWND hwndDlg,
								   UINT uMsg,
								   LPARAM lParam)
{
	//printf("Cube4D::PropSheetProc HWND hwndDlg = %x, UINT uMsg = %d, LPARAM lParam %d)\n", hwndDlg, uMsg, lParam);
	switch (uMsg)
	{
	case PSCB_PRECREATE:
		{
			//Indicates that the property sheet is about to be created. The hwndDlg parameter is NULL, and the lParam parameter is the address of a dialog template in memory. This template is in the form of a DLGTEMPLATE or DLGTEMPLATEEX structure followed by one or more DLGITEMTEMPLATE structures. 
		}
		break;
	case PSCB_INITIALIZED:
		{
			//Indicates that the property sheet is being initialized. The lParam value is zero for this message. 

		}
		break;
	case 3://PSCB_BUTTONPRESSED:
		{
			switch (lParam)
			{
			case PSBTN_OK:
				{
					DestroyWindow(hwndDlg);
				}
				break;
			case PSBTN_CANCEL:
				{
					DestroyWindow(hwndDlg);
				}
				break;			
			case PSBTN_APPLYNOW:
				{
					//DestroyWindow(hwndDlg);
				}
				break;
			case PSBTN_FINISH:
				{
					DestroyWindow(hwndDlg);
				}
				break;
			}
		}
		break;
	}
	return 0;
}

void Cube4D::PropertiesDialog()
{
    // Ensure that the common control DLL is loaded. 
	// InitCommonControls(); 
	// Инициализируем страницы блокнота  


	psheetPage[0].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[0].hInstance = hInst;
//	psheetPage[0].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[0].pszIcon = NULL;
	psheetPage[0].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_CUBE_DRAW_MODES);
	psheetPage[0].pfnDlgProc = Cube4D::DlgProcDrawModes;
	psheetPage[0].pszTitle = "Draw Modes";
	psheetPage[0].lParam = (LPARAM)this;
	// Добавляем страницу в блокнот, сохраняя ее
	// идентификатор в массиве hPage
	hPage[0] = CreatePropertySheetPage(&psheetPage[0]);


	psheetPage[1].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[1].hInstance = hInst;
//	psheetPage[1].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[1].pszIcon = NULL;
	psheetPage[1].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[1].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_CUBE_ISOSURFACES);
	psheetPage[1].pfnDlgProc = Cube4D::DlgProcIsosurfaces;
	psheetPage[1].pszTitle = "Isosurfaces";
	psheetPage[1].lParam = (LPARAM)this;
	hPage[1] = CreatePropertySheetPage(&psheetPage[1]);

	psheetPage[2].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[2].hInstance = hInst;
//	psheetPage[2].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[2].pszIcon = NULL;
	psheetPage[2].dwFlags = PSP_USETITLE /*| PSP_USEICONID*/;
	psheetPage[2].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_SURF_PALETTE);
	psheetPage[2].pfnDlgProc = Cube4D::DlgProcSurfPalette;
	psheetPage[2].pszTitle = "Palette";
	psheetPage[2].lParam = (LPARAM)this;
	hPage[2] = CreatePropertySheetPage(&psheetPage[2]);
	
	psheetPage[3].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[3].hInstance = hInst;
//	psheetPage[3].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[3].pszIcon = NULL;
	psheetPage[3].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[3].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_CUBE_ALPHA);
	psheetPage[3].pfnDlgProc = Cube4D::DlgProcSurfAlpha;
	psheetPage[3].pszTitle = "Alpha";
	psheetPage[3].lParam = (LPARAM)this;
	hPage[3] = CreatePropertySheetPage(&psheetPage[3]);

	psheetPage[4].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[4].hInstance = hInst;
//	psheetPage[4].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[4].pszIcon = NULL;
	psheetPage[4].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[4].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_CUBE_CUTS_PLANE);
	psheetPage[4].pfnDlgProc = Cube4D::DlgProcCubeCutsPlane;
	psheetPage[4].pszTitle = "Cut's Plane";
	psheetPage[4].lParam = (LPARAM)this;
	hPage[4] = CreatePropertySheetPage(&psheetPage[4]);


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
	psheetHeader.dwFlags = PSH_USEICONID;
	psheetHeader.dwFlags = PSH_DEFAULT | PSH_MODELESS;// | PSH_USECALLBACK;
	//psheetHeader.pfnCallback = Cube4D::PropSheetProc;
	psheetHeader.hwndParent = this->m_pSurfDoc->hwndTV;
	psheetHeader.hwndParent = this->m_pSurfDoc->hSurfWnd;
	psheetHeader.pszCaption = "Cube Properties";
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
Cube4D& Cube4D::operator=(const Cube4D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
#if CUBE4D_AS_PRIMITIVE
	dynamic_cast<Primitive3D<CPoint4>*  >(this)->Init(ob);
#endif
	this->Init(ob);

	return *this;
}

Cube4D::Cube4D(const Cube4D &ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
#if CUBE4D_AS_PRIMITIVE
	dynamic_cast<Primitive3D<CPoint4>*  >(this)->Init(ob);
#endif
	this->Init(ob);
}


#if CUBE4D_AS_PRIMITIVE

bool Cube4D::UpdateExtremums()
{
	bool start = true;				

	for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
	{							
		if (m_vdPoints[ipoint].bVisible)
		{
			if (start)
			{
				m_ptMin.x = m_ptMax.x = m_vdPoints[ipoint].x;
				m_ptMin.y = m_ptMax.y = m_vdPoints[ipoint].y;
				m_ptMin.z = m_ptMax.z = m_vdPoints[ipoint].z;

				this->m_vMax = this->m_vMin = m_vdPoints[ipoint].v;
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
				
				if (m_vMin > m_vdPoints[ipoint].v) m_vMin = m_vdPoints[ipoint].v;
				if (m_vMax < m_vdPoints[ipoint].v) m_vMax = m_vdPoints[ipoint].v;
			}
		}
	}

	return !start;
}
#else
bool Cube4D::UpdateExtremums()
{
	m_ptMin.x = m_ptMax.x = this->lattice.grid4Section.xLL;
	m_ptMin.y = m_ptMax.y = this->lattice.grid4Section.yLL;
	m_ptMin.z = m_ptMax.z = this->lattice.grid4Section.zLL;


	double x = this->lattice.grid4Section.xLL + (this->lattice.grid4Section.nCol - 1) * this->lattice.grid4Section.xSize;
	double y = this->lattice.grid4Section.yLL + (this->lattice.grid4Section.nRow - 1) * this->lattice.grid4Section.ySize;
	double z = this->lattice.grid4Section.zLL + (this->lattice.grid4Section.nPag - 1) * this->lattice.grid4Section.zSize;
	
	if (m_ptMin.x > x) m_ptMin.x = x;
	if (m_ptMax.x < x) m_ptMax.x = x;

	if (m_ptMin.y > y) m_ptMin.y = y;
	if (m_ptMax.y < y) m_ptMax.y = y;

	if (m_ptMin.z > z) m_ptMin.z = z;
	if (m_ptMax.z < z) m_ptMax.z = z;	

	return true;
}
#endif
#if CUBE4D_AS_PRIMITIVE
void Cube4D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
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
#else
void Cube4D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	this->lattice.grid4Zoom.xLL = zoomX * (this->lattice.grid4Section.xLL-x_mean);
	this->lattice.grid4Zoom.xSize = zoomX * this->lattice.grid4Section.xSize;
	
	this->lattice.grid4Zoom.yLL = zoomY * (this->lattice.grid4Section.yLL-y_mean);
	this->lattice.grid4Zoom.ySize = zoomY * this->lattice.grid4Section.ySize;
	
	this->lattice.grid4Zoom.zLL = zoomZ * (this->lattice.grid4Section.zLL-z_mean);
	this->lattice.grid4Zoom.zSize = zoomZ * this->lattice.grid4Section.zSize;	
}
#endif
#if CUBE4D_AS_PRIMITIVE
void Cube4D::ZoomInv(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	for (unsigned int ipoint = 0; ipoint < m_nPoints; ipoint++)
	{							
		m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
		m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
		m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
		m_vdPoints[ipoint].z = z_mean + m_vvPoints[ipoint].z / zoomZ;
	}

}
void Cube4D::ZoomInv(unsigned int ipoint, double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (ipoint < m_nPoints && ipoint >= 0 )
	{							
		m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
		m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
		m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
		m_vdPoints[ipoint].z = z_mean + m_vvPoints[ipoint].z / zoomZ;
	}
}
#endif
#if CUBE4D_AS_PRIMITIVE
void Cube4D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	for (UINT ipoint = 0; ipoint < m_nPoints; ipoint++)
	{
		// растояние от точки до плоскости
		double r = 
			a*m_vdPoints[ipoint].x+
			b*m_vdPoints[ipoint].y+
			c*m_vdPoints[ipoint].z+
			d; 

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
void Cube4D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	double x,y,z;
						
	for (UINT ipoint = 0; ipoint < m_nPoints; ipoint++)
	{

		x = m_vdPoints[ipoint].x;
		y = m_vdPoints[ipoint].y;
		z = m_vdPoints[ipoint].z;

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


#else
void Cube4D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
}
void Cube4D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
}


#endif
#if CUBE4D_AS_PRIMITIVE
bool Cube4D::GetQuadIndex(
	double x, double y, double z,
	int& ix, int& iy, int& iz)
{
	ix = iy = iz = -1;
	double x00 = this->GetFirstDocumentPoint().x;
	double y00 = this->GetFirstDocumentPoint().y;
	double z00 = this->GetFirstDocumentPoint().z;

	double xnn = this->GetLastDocumentPoint().x;
	double ynn = this->GetLastDocumentPoint().y;
	double znn = this->GetLastDocumentPoint().z;


	if (x >= x00 &&	x < xnn &&
		y >= y00 &&	y < ynn &&
		z >= z00 &&	z < znn
		)
	{
		ix = int((x - x00) / (xnn - x00) * (this->m_lenx-1));
		iy = int((y - y00) / (ynn - y00) * (this->m_leny-1));
		iz = int((z - z00) / (znn - z00) * (this->m_lenz-1));
		return true;
	}
	return false;
}


#endif
DWORD Cube4D::Serialize(Archive& ar)
{
	printf("Cube4D::Serialize(Archive& ar)\n");
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
Archive& operator <<(Archive& ar, Cube4D& ob)
{
//printf("Archive& operator <<(Archive& ar, Cube4D& ob)\n");
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 2:
		{
			ar << ob.m_min_isolevel;
			ar << ob.m_max_isolevel;
			ar << ob.m_step_isolevel;
		}
	case 1:
		{
			ar << ob.m_palette;
			ar << ob.m_bInverseColormap;
			ar << ob.m_bUseColormap;
			ar << ob.m_nColormap;

			ar << ob.draw_as_one_isosurface;
			ar << ob.draw_as_many_isosurfaces;
			ar << ob.draw_as_scatter_plot;
			ar << ob.draw_as_image;
			ar << ob.draw_as_contours;
			ar << ob.draw_as_vol_render;

			ar << ob.m_color;
			ar << ob.m_alpha;
			ar << ob.m_opacity;
			ar << ob.m_isolevel;
			ar << ob.m_nIsolevels;

			ar << ob.m_isolevels;
			ar << ob.m_iso_ind;

			ar << ob.lattice;
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
Archive& operator >>(Archive& ar, Cube4D& ob)
{
//printf("Archive& operator >>(Archive& ar, Cube4D& ob)\n");
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 2:
		{
			ar >> ob.m_min_isolevel;
			ar >> ob.m_max_isolevel;
			ar >> ob.m_step_isolevel;
		}
	case 1:
		{
			ar >> ob.m_palette;
			ar >> ob.m_bInverseColormap;
			ar >> ob.m_bUseColormap;
			ar >> ob.m_nColormap;

			ar >> ob.draw_as_one_isosurface;
			ar >> ob.draw_as_many_isosurfaces;
			ar >> ob.draw_as_scatter_plot;
			ar >> ob.draw_as_image;
			ar >> ob.draw_as_contours;
			ar >> ob.draw_as_vol_render;
			
			ar >> ob.m_color;
			ar >> ob.m_alpha;
			ar >> ob.m_opacity;
			ar >> ob.m_isolevel;
			ar >> ob.m_nIsolevels;

			ar >> ob.m_isolevels;
			ar >> ob.m_iso_ind;

			ar >> ob.lattice;


			if ( ob.m_object_version == 1)
			{
				ob.m_object_version = 2;

				ob.m_min_isolevel = ob.lattice.grid4Section.vMin;
				ob.m_max_isolevel = ob.lattice.grid4Section.vMax;
				ob.m_step_isolevel = (ob.m_max_isolevel - ob.m_min_isolevel) / ob.m_nIsolevels;
			}

		}
		break;

	default:
		{
//printf("Archive& operator >>(Archive& ar, Cube4D& ob) default!!!\n");
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, Cube4D& ob) end\n");
	return ar;
}
