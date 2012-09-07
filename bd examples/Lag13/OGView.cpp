// OGView.cpp : implementation of the COGView class
//

#include "stdafx.h"
#include "Graphs.h"

#include "OGDoc.h"
#include "OGView.h"

#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
u_int COGView::s_nViews = 0;
extern CGraphsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COGView
#define Line3d(x1,y1,z1,x2,y2,z2)		\
	glBegin(GL_LINES);				\
		glVertex3d ((x1),(y1),(z1));		\
		glVertex3d ((x2),(y2),(z2));		\
	glEnd();
#define Line3f(x1,y1,z1,x2,y2,z2)		\
	glBegin(GL_LINES);				\
		glVertex3f ((x1),(y1),(z1));		\
		glVertex3f ((x2),(y2),(z2));		\
	glEnd();

/////////////////////////////////////////////////////////////////////////////
// COGView

IMPLEMENT_DYNCREATE(COGView, CView)

BEGIN_MESSAGE_MAP(COGView, CView)
	//{{AFX_MSG_MAP(COGView)
//	ON_WM_WINDOWPOSCHANGING(/*OnWindowPosChanging*/)
//	ON_WM_WINDOWPOSCHANGED(/*OnWindowPosChanged*/)
	ON_WM_SETFOCUS()
	ON_WM_MOVE()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_COMMAND(ID_ANIMATE_STOP, AnimateStop)
	ON_COMMAND(ID_ANIMATE_GRAPHIC, AnimateGraphic)
	ON_COMMAND(ID_EDIT_BACKGROUND, OnEditBackground)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_COMMAND(ID_VIEW_QUAD, OnViewQuad)
	ON_UPDATE_COMMAND_UI(ID_VIEW_QUAD, OnUpdateViewQuad)
	ON_COMMAND(ID_VIEW_FILL, OnViewFill)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FILL, OnUpdateViewFill)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PROPERTIES, OnUpdateEditProperties)
	ON_WM_KEYDOWN()
//	ON_COMMAND(WM_USER + 10, OnDraw)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGView construction/destruction

COGView::COGView()
{
	//EnterCriticalSection( &theApp.cs );

	m_nView = s_nViews;
	s_nViews++;

	m_pDlg = 0;
	//====== Контекст передачи пока отсутствует
	m_hRC = 0;

	//====== Начальный разворот изображения
	m_AngleX = 35.f;
	m_AngleY = 20.f;

	//====== Угол зрения для матрицы проекции
	m_AngleView = 45.f;

	//====== Начальный цвет фона
	m_BkClr = RGB(0, 0, 96);

	// Начальный режим заполнения внутренних точек полигона
	m_FillMode = GL_FILL;



	//== Начальные значения квантов смещения (для анимации)
	m_dx = m_dy = 0.f;

	//====== Мышь не захвачена
	m_bCaptured = false;
	//====== Правая кнопка не была нажата
	m_bRightButton = false;
	//====== Рисуем четырехугольниками
	m_bQuad = true;

	//====== Начальный значения параметров освещения
	m_LightParam[0] = 50;	// X position
	m_LightParam[1] = 80;	// Y position
	m_LightParam[2] = 100;	// Z position
	m_LightParam[3] = 15;	// Ambient light
	m_LightParam[4] = 70;	// Diffuse light
	m_LightParam[5] = 100;	// Specular light
	m_LightParam[6] = 100;	// Ambient material
	m_LightParam[7] = 100;	// Diffuse material
	m_LightParam[8] = 40;	// Specular material
	m_LightParam[9] = 70;	// Shininess material
	m_LightParam[10] = 0;	// Emission material

	//LeaveCriticalSection( &theApp.cs );

}

COGView::~COGView()
{
}

BOOL COGView::PreCreateWindow(CREATESTRUCT& cs)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Добавляем биты стиля, нужные OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	//LeaveCriticalSection( &theApp.cs );

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COGView drawing

void COGView::OnDraw(CDC* pDC)
{
	//EnterCriticalSection( &theApp.cs );
#if 1
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
#endif
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//======= Установка параметров освещения
	SetLight();

	//====== Формирование матрицы моделирования
	glTranslatef(m_xTrans,m_yTrans,m_zTrans);
	glRotatef (m_AngleX, 1.0f, 0.0f, 0.0f );
	glRotatef (m_AngleY, 0.0f, 1.0f, 0.0f );

	//====== Вызов рисующих команд из списка
	for (int s = 0; s < pDoc->m_nSurfs; s++)
	{
		glCallList(m_nView * 4 + 1 + s);
	}
//	glCallList(m_nView * 4 + 2 + s);
//	glCallList(m_nView * 4 + 3 + s);

	//====== Переключение буферов
	SwapBuffers(m_hdc);


}

/////////////////////////////////////////////////////////////////////////////
// COGView printing

BOOL COGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COGView diagnostics

#ifdef _DEBUG
void COGView::AssertValid() const
{
	//EnterCriticalSection( &theApp.cs );
	CView::AssertValid();
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::Dump(CDumpContext& dc) const
{
	//EnterCriticalSection( &theApp.cs );
	CView::Dump(dc);
	//LeaveCriticalSection( &theApp.cs );
}

COGDoc* COGView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COGDoc)));
	return (COGDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COGView message handlers

BOOL COGView::OnEraseBkgnd(CDC* pDC) 
{
	RefreshOG(true);
	Invalidate(FALSE);
	return TRUE;
	
//	return CView::OnEraseBkgnd(pDC);
}

int COGView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//EnterCriticalSection( &theApp.cs );
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//====== Подготовка графика по умолчанию
#if 1
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
#endif
	pDoc->DefaultGraphic();
	//====== Начальное смещение относительно центра сцены
	//====== Сдвиг назад на полуторный размер объекта
	m_zTrans = -1.5f*pDoc->m_fRangeX;
	m_xTrans = m_yTrans = 0.f;

	InitOG();
	//LeaveCriticalSection( &theApp.cs );
	return 0;
}

void COGView::OnDestroy(void)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Останавливаем таймер анимации
	KillTimer(m_nView * 2+1);
#if 0

	//====== Отсоединяем кнтекст от потока
	wglMakeCurrent(0, 0);
#endif
	//====== Удаляем контекст
	if (m_hRC)
	{
		wglDeleteContext(m_hRC);
		m_hRC = 0;
	}
	CView::OnDestroy();
	//LeaveCriticalSection( &theApp.cs );
}


void COGView::OnSize(UINT nType, int cx, int cy)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Вызов родительской версии
	CView::OnSize(nType, cx, cy);

	RefreshOG(false);
	//====== Вычисление диспропорций окна
	double dAspect = cx<=cy ? double(cy)/cx 
								 : double(cx)/cy;

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	//====== Установка режима перспективной проекции
	gluPerspective (m_AngleView, dAspect, 0.01, 10000.);

	//====== Установка прямоугольника просмотра
//	glViewport(0, 0, cx, cy);

	//LeaveCriticalSection( &theApp.cs );
}
void COGView::SetLight()
{
#if 1
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
#endif
	//====== Обе поверхности изображения участвуют
	//====== при вычислении цвета пикселов
	//====== при учете параметров освещения
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);

	//====== Позиция источника освещения
	//====== зависит от размеров объекта
	float fPos[] =
	{
		(m_LightParam[0]-50)*pDoc->m_fRangeX/100,
		(m_LightParam[1]-50)*pDoc->m_fRangeY/100,
		(m_LightParam[2]-50)*pDoc->m_fRangeZ/100,
		1.f
	};
	glLightfv(GL_LIGHT0, GL_POSITION, fPos);

	//====== Интенсивность окружающего освещения
	float f = m_LightParam[3]/100.f;
	float fAmbient[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbient);

	//====== Интенсивность рассеянного света
	f = m_LightParam[4]/100.f;	
	float fDiffuse[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffuse);

	//====== Интенсивность отраженного света
	f = m_LightParam[5]/100.f;
	float fSpecular[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecular);

	//====== Отражающие свойства материала
	//====== для разных компонент света
	f = m_LightParam[6]/100.f;
	float fAmbMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbMat);

	f = m_LightParam[7]/100.f;
	float fDifMat[4] = { f, f, f, 1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDifMat);

	f = m_LightParam[8]/100.f;
	float fSpecMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fSpecMat);

	//====== Блесткость материала
	float fShine = 128 * m_LightParam[9]/100.f;
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShine);

	//====== Излучение света материалом
	f = m_LightParam[10]/100.f;
	float fEmission[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, fEmission);
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::SetBkColor()
{
	//EnterCriticalSection( &theApp.cs );
	//====== Расщепление цвета на три компоненты
	GLclampf red	= GetRValue(m_BkClr)/255.f,
			 green	= GetGValue(m_BkClr)/255.f,
			 blue	= GetBValue(m_BkClr)/255.f;
	//====== Установка цвета фона (стирания) окна
	glClearColor (red, green, blue, 0.f);

	//====== Непосредственное стирание
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::DrawScene()
{
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//EnterCriticalSection( &theApp.cs );
	//====== Создание списка рисующих команд
	for (int s = 0; s < pDoc->m_nSurfs; s++)
	{
		/// ???????!!!!!!!!!!!!!
		glNewList(m_nView * 4 + 1 + s, GL_COMPILE);

		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		glPolygonMode(GL_FRONT_AND_BACK, m_FillMode);

		//====== Размеры изображаемого объекта
		UINT	nx = pDoc->m_vxSize[s]-1,
				nz = pDoc->m_vySize[s]-1;

		//====== Выбор способа создания полигонов
		if (m_bQuad)
			glBegin (GL_QUADS);

		//====== Цикл прохода по слоям изображения (ось Z)
		for (UINT z=0, i=0;  z<nz;  z++, i++)
		{
			//====== Связанные полигоны начинаются
			//====== на каждой полосе вновь
			if (!m_bQuad)
				glBegin(GL_QUAD_STRIP);

			//====== Цикл прохода вдоль оси X
			for (UINT x=0;  x<nx;  x++, i++)
			{
				// i, j, k, n - 4 индекса вершин примитива при
				// обходе в направлении против часовой стрелки

				int	j = i + pDoc->m_vxSize[s],	// Индекс узла с большим Z
					k = j+1,			// Индекс узла по диагонали
					n = i+1; 			// Индекс узла справа

				//=== Выбор координат 4-х вершин из контейнера
				float
					xi = pDoc->m_vcPointsSurf[s][i].x,
					yi = pDoc->m_vcPointsSurf[s][i].y,
					zi = pDoc->m_vcPointsSurf[s][i].z,

					xj = pDoc->m_vcPointsSurf[s][j].x,
					yj = pDoc->m_vcPointsSurf[s][j].y,
					zj = pDoc->m_vcPointsSurf[s][j].z,

					xk = pDoc->m_vcPointsSurf[s][k].x,
					yk = pDoc->m_vcPointsSurf[s][k].y,
					zk = pDoc->m_vcPointsSurf[s][k].z,

					xn = pDoc->m_vcPointsSurf[s][n].x,
					yn = pDoc->m_vcPointsSurf[s][n].y,
					zn = pDoc->m_vcPointsSurf[s][n].z,

					//=== Координаты векторов боковых сторон
					ax = xi-xn,
					ay = yi-yn,

					by = yj-yi,
					bz = zj-zi,

					//====== Вычисление вектора нормали
					vx = ay*bz,
					vy = -bz*ax,
					vz = ax*by,

					//====== Модуль нормали
					v  = float(sqrt(vx*vx + vy*vy + vz*vz));
				
				//====== Нормировка вектора нормали
				vx /= v;
				vy /= v;
				vz /= v;

				//====== Задание вектора нормали
				glNormal3f (vx,vy,vz);

				// Ветвь создания несвязанных четырехугольников
				if (m_bQuad)
				{
					//====== Обход вершин осуществляется
					//====== в направлении против часовой стрелки
					glColor3f (0.2f, 0.8f, 1.f);
					glVertex3f (xi, yi, zi);
					glColor3f (0.6f, 0.7f, 1.f);
					glVertex3f (xj, yj, zj);
					glColor3f (0.7f, 0.9f, 1.f);
					glVertex3f (xk, yk, zk);
					glColor3f (0.7f, 0.8f, 1.f);
					glVertex3f (xn, yn, zn);
				}
				else
				//====== Ветвь создания цепочки четырехугольников
				{
					glColor3f (0.9f, 0.9f, 1.0f);
					glVertex3f (xn, yn, zn);
					glColor3f (0.5f, 0.8f, 1.0f);
					glVertex3f (xj, yj, zj);
				}
			}
			//====== Закрываем блок команд GL_QUAD_STRIP
			if (!m_bQuad)
				glEnd();
		}
		//====== Закрываем блок команд GL_QUADS
		if (m_bQuad)
			glEnd();
		glEndList();
	}
//return;
	glNewList(m_nView * 4 + 2 + s, GL_COMPILE);
	if (pDoc->m_cPoints2.Size() > 1)
	{
		float
			max_x = pDoc->m_cPoints2[0].x,
			max_y = pDoc->m_cPoints2[0].y,
			max_z = pDoc->m_cPoints2[0].z,

			min_x = pDoc->m_cPoints2[0].x,
			min_y = pDoc->m_cPoints2[0].y,
			min_z = pDoc->m_cPoints2[0].z;


		for (int i0 = 1; i0 < pDoc->m_cPoints2.Size(); i0++)
		{
			max_x = max_x > pDoc->m_cPoints2[i0].x ? max_x : pDoc->m_cPoints2[i0].x;
			max_y = max_y > pDoc->m_cPoints2[i0].y ? max_y : pDoc->m_cPoints2[i0].y;
			max_z = max_z > pDoc->m_cPoints2[i0].z ? max_z : pDoc->m_cPoints2[i0].z;
			min_x = min_x < pDoc->m_cPoints2[i0].x ? min_x : pDoc->m_cPoints2[i0].x;
			min_y = min_y < pDoc->m_cPoints2[i0].y ? min_y : pDoc->m_cPoints2[i0].y;
			min_z = min_z < pDoc->m_cPoints2[i0].z ? min_z : pDoc->m_cPoints2[i0].z;
		}

//		Line3f(0., 0., 0., max_x, 0., 0.);
//		Line3f(0., 0., 0., 0., max_y, 0.);
//		Line3f(0., 0., 0., 0., 0., max_z);

		Line3f(min_x, min_y, min_z, max_x, min_y, min_z);
		Line3f(min_x, max_y, min_z, max_x, max_y, min_z);
		Line3f(min_x, min_y, min_z, min_x, max_y, min_z);
		Line3f(max_x, min_y, min_z, max_x, max_y, min_z);

		Line3f(min_x, min_y, max_z, max_x, min_y, max_z);
		Line3f(min_x, max_y, max_z, max_x, max_y, max_z);
		Line3f(min_x, min_y, max_z, min_x, max_y, max_z);
		Line3f(max_x, min_y, max_z, max_x, max_y, max_z);

		Line3f(min_x, min_y, min_z, min_x, min_y, max_z);
		Line3f(min_x, max_y, min_z, min_x, max_y, max_z);
		Line3f(max_x, min_y, min_z, max_x, min_y, max_z);
		Line3f(max_x, max_y, min_z, max_x, max_y, max_z);
	}
	//====== Закрываем список команд OpenGL
	glEndList();

	glNewList(m_nView * 4 + 3 + s, GL_COMPILE);
	for (int i0 = 0, i1 = 1 ; i1 < pDoc->m_cPoints2.Size(); i0++, i1++)
	{
		Line3f(pDoc->m_cPoints2[i0].x, pDoc->m_cPoints2[i0].y, pDoc->m_cPoints2[i0].z,
			pDoc->m_cPoints2[i1].x, pDoc->m_cPoints2[i1].y, pDoc->m_cPoints2[i1].z);
	}
	glEndList();
	//LeaveCriticalSection( &theApp.cs );
}


void COGView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== Останавливаем таймер
	KillTimer(m_nView * 2 +1);

	//====== Обнуляем кванты перемещения
	m_dx = 0.f;
	m_dy = 0.f;

	//====== Захватываем сообщения мыши,
	//====== направляя их в свое окно
	SetCapture();
	//====== Запоминаем факт захвата
	m_bCaptured = true;
	//====== Запоминаем координаты курсора
	m_pt = point;
	
///	CView::OnLButtonDown(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== Запоминаем факт нажатия правой кнопки
	m_bRightButton = true;

	//====== Воспроизводим реакцию на левую кнопку
	OnLButtonDown(nFlags, point);
	
//	CView::OnRButtonDown(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== Если был захват,
	if (m_bCaptured)
	{
		//=== то анализируем желаемый квант перемещения
		//=== на превышение порога чувствительности
		if (fabs(m_dx) > 0.5f || fabs(m_dy) > 0.5f)
			//=== Включаем режим постоянного вращения
			SetTimer(m_nView * 2 + 1,33,0);
		else
			//=== Выключаем режим постоянного вращения
			KillTimer(m_nView * 2 +1);

		//====== Снимаем флаг захвата мыши
		m_bCaptured = false;
		//====== Отпускаем сообщения мыши
		ReleaseCapture();
	}
	
//	CView::OnLButtonUp(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== Правая кнопка отпущена
	m_bRightButton = false;
	//====== Снимаем флаг захвата мыши
	m_bCaptured = false;
	//====== Отпускаем сообщения мыши
	ReleaseCapture();
	
//	CView::OnRButtonUp(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnMouseMove(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	if (m_bCaptured)		// Если был захват,
	{
		// Вычисляем компоненты желаемой скорости вращения
		m_dy = float(point.y - m_pt.y)/40.f;
		m_dx = float(point.x - m_pt.x)/40.f;

		//====== Если одновременно была нажата Ctrl,
		if (nFlags & MK_CONTROL)
		{
			//=== Изменяем коэффициенты сдвига изображения
			m_xTrans += m_dx;
			m_yTrans -= m_dy;
		}
		else
		{
			//====== Если была нажата правая кнопка
			if (m_bRightButton)
				//====== Усредняем величину сдвига
				m_zTrans += (m_dx + m_dy)/2.f;
			else
			{
				//====== Иначе, изменяем углы поворота
				m_AngleX += m_dy;
				m_AngleY += m_dx;
			}
		}
		//=== В любом случае запоминаем новое положение мыши
		m_pt = point;
		Invalidate(FALSE);
	}
	
//	CView::OnMouseMove(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnTimer(UINT nIDEvent) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== Если это был наш таймер
	if (nIDEvent==m_nView * 2 +1)
	{
		//====== Увеличиваем углы поворота
		m_AngleX += m_dy;
		m_AngleY += m_dx;
		//====== Ограничители роста углов
		if (m_AngleX > 360)
			m_AngleX -= 360;
		if (m_AngleX <-360)
			m_AngleX += 360;

		if (m_AngleY > 360)
			m_AngleY -= 360;
		if (m_AngleY <-360)
			m_AngleY += 360;

		//====== Просим перерисовать окно
		RefreshOG(false);
//		RefreshOG(true);
		Invalidate(FALSE);
	}
	else 
	{ 
		if (nIDEvent==m_nView * 2 + 2)
		{
			COGDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			pDoc->AnimateGraphic();

			DrawScene();
			RefreshOG(false);
	//		RefreshOG(true);
			Invalidate(FALSE);
		}
		else
			//=== Каркас приложения обработает другие таймеры
			CView::OnTimer(nIDEvent);

	}
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnEditBackground() 
{
	//EnterCriticalSection( &theApp.cs );
	//====== Создаем объект диалогового класса
	CColorDialog dlg(m_BkClr);
	//====== Устанавливаем бит стиля
	dlg.m_cc.Flags |= CC_FULLOPEN;
	//====== Запускаем диалог и выбираем результат
	if (dlg.DoModal()==IDOK)
	{
		m_BkClr = dlg.m_cc.rgbResult;
		//====== Изменяем цвет фона
		SetBkColor();
		Invalidate(FALSE);
	}
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnEditProperties (void)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Если диалог еще не открыт
	if (!m_pDlg)
	{
		//=== Создаем его и запускаем в немодальном режиме
		m_pDlg = new CPropDlg(this);
		m_pDlg->Create(IDD_PROP, this);
	}
	else
	{
		// Иначе, переводим фокус в окно существующего диалога
		m_pDlg->SetActiveWindow();
	}
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::OnViewQuad() 
{
	//EnterCriticalSection( &theApp.cs );
	// Инвертируем признак стиля задания четырехугольников
	m_bQuad = ! m_bQuad;

	//====== Заново создаем изображение
	DrawScene();
	Invalidate(FALSE);
	UpdateWindow();
	//LeaveCriticalSection( &theApp.cs );
	
}

void COGView::OnUpdateViewQuad(CCmdUI* pCmdUI) 
{
	//====== Вставляем или убираем маркер (пометку)
	pCmdUI->SetCheck(m_bQuad==true);
	
}

void COGView::OnViewFill() 
{
	//EnterCriticalSection( &theApp.cs );
	//=== Переключаем режим заполнения четырехугольника
	m_FillMode = m_FillMode==GL_FILL ? GL_LINE : GL_FILL;

	//====== Заново создаем изображение
	DrawScene();
	Invalidate(FALSE);
	UpdateWindow();
	//LeaveCriticalSection( &theApp.cs );
	
}

void COGView::OnUpdateViewFill(CCmdUI* pCmdUI) 
{
	//====== Вставляем или убираем маркер выбора
	pCmdUI->SetCheck(m_FillMode==GL_FILL);
	
}
void COGView::GetLightParams(int *pPos)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Проход по всем регулировкам
	for (int i=0; i<11; i++)
		//====== Заполняем транспортный массив pPos
		pPos[i] = m_LightParam[i];
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::SetLightParam (short lp, int nPos)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Синхронизируем параметр lp и
	//====== устанавливаем его в положение nPos
	m_LightParam[lp] = nPos;

	//====== Перерисовываем Вид с учетом изменений
	Invalidate(FALSE);
	//LeaveCriticalSection( &theApp.cs );
}


void COGView::OnUpdateEditProperties(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_pDlg != 0);
	
}

void COGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	CString s;
//	s.Format("nChar = %i\n nRepCnt = %i\n nFlags = %i", nChar, nRepCnt, nFlags);

//	AfxMessageBox(s);

	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COGView::OnSetFocus(CWnd* pOldWnd) 
{
//	if (this == (COGView*)pOldWnd)
//		return;

	//EnterCriticalSection( &theApp.cs );
	CView::OnSetFocus(pOldWnd);
	RefreshOG(true);
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::OnKillFocus(CWnd* pNewWnd) 
{
//	if (this == (COGView*)pNewWnd)
//		return;
	CView::OnKillFocus(pNewWnd);
	RefreshOG(true);
}

void COGView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
	RefreshOG(true);
	Invalidate(FALSE);
}
void COGView::OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	AfxMessageBox("OnWindowPosChanged");
	RefreshOG(true);
	Invalidate(FALSE);

}
void COGView::OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	AfxMessageBox("OnWindowPosChanging");
	RefreshOG(true);
	Invalidate(FALSE);

}
void COGView::InitOG()
{
	PIXELFORMATDESCRIPTOR pfd =	// Описатель формата
	{
		sizeof(PIXELFORMATDESCRIPTOR),// Размер структуры
		1,							// Номер версии
		PFD_DRAW_TO_WINDOW |	// Поддержка GDI
		PFD_SUPPORT_OPENGL |	// Поддержка OpenGL
		PFD_DOUBLEBUFFER,		// Двойная буферизация
		PFD_TYPE_RGBA,			// Формат RGBA, не палитра
		24, 						// Количество плоскостей
		 							// в каждом буфере цвета
		24,	0,						// Для компоненты Red
		24,	0,						// Для компоненты Green
		24,	0,						// Для компоненты Blue
		24,	0,						// Для компоненты Alpha
		0,							// Количество плоскостей
									// буфера Accumulation
		0,			 				// То же для компоненты Red
		0,			 				// для компоненты Green
		0,							// для компоненты Blue
		0,							// для компоненты Alpha
		32, 						// Глубина Z-буфера
		0,							// Глубина буфера Stencil
		0,							// Глубина буфера Auxiliary
		0,				 			// Теперь игнорируется
		0,							// Количество плоскостей
		0,							// Теперь игнорируется
		0,							// Цвет прозрачной маски
		0							// Теперь игнорируется
	};

	//====== Добываем дежурный контекст
	m_hdc = ::GetDC(GetSafeHwnd());

	//====== Просим выбрать ближайший совместимый формат
	int iD = ChoosePixelFormat(m_hdc, &pfd);
	if ( !iD )
	{
		MessageBox("ChoosePixelFormat::Error");
		return ;
	}

	//====== Пытаемся установить этот формат
	if ( !SetPixelFormat (m_hdc, iD, &pfd) )
	{
		MessageBox("SetPixelFormat::Error");
		return ;
	}

	//====== Пытаемся создать контекст передачи OpenGL
	if ( !(m_hRC = wglCreateContext (m_hdc)))
	{
		MessageBox("wglCreateContext::Error");
		return;
	}

	//====== Пытаемся выбрать его в качестве текущего
	if ( !wglMakeCurrent (m_hdc, m_hRC))
	{
		MessageBox("wglMakeCurrent::Error");
		return ;
	}

	//====== Теперь можно посылать команды OpenGL
	glEnable(GL_LIGHTING);			// Будет освещение
	//====== Будет только один источник света
	glEnable(GL_LIGHT0);
	//====== Необходимо учитывать глубину (ось Z)
	glEnable(GL_DEPTH_TEST);
	//====== Необходимо учитывать цвет материала поверхности
	glEnable(GL_COLOR_MATERIAL);

	//====== Устанавливаем цвет фона
	SetBkColor();

	//====== Создаем изображение и запоминаем в списке
	DrawScene();

}

void COGView::RefreshOG(bool isfull)
{
	//====== Пытаемся выбрать его в качестве текущего
	if ( !wglMakeCurrent (m_hdc, m_hRC))
	{
		MessageBox("wglMakeCurrent::Error");
		return ;
	}

	//====== Теперь можно посылать команды OpenGL
	glEnable(GL_LIGHTING);			// Будет освещение
	//====== Будет только один источник света
	glEnable(GL_LIGHT0);
	//====== Необходимо учитывать глубину (ось Z)
	glEnable(GL_DEPTH_TEST);
	//====== Необходимо учитывать цвет материала поверхности
	glEnable(GL_COLOR_MATERIAL);

	//====== Устанавливаем цвет фона
	SetBkColor();

	//====== Создаем изображение и запоминаем в списке
//	DrawScene();
	if (!isfull)
		return;

	CRect r;

	//===== Узнаем размеры окна диалога
	GetWindowRect(&r);
	int cy = r.Height();
	int cx = r.Width();

		//====== Вычисление диспропорций окна
	double dAspect = cx<=cy ? double(cy)/cx 
								 : double(cx)/cy;

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	//====== Установка режима перспективной проекции
	gluPerspective (m_AngleView, dAspect, 0.01, 10000.);

	//====== Установка прямоугольника просмотра
	glViewport(0, 0, cx, cy);

}

void COGView::AnimateGraphic()
{
	SetTimer(m_nView * 2 + 2,33,0);
}

void COGView::AnimateStop()
{
	KillTimer(m_nView * 2 + 2);
}
