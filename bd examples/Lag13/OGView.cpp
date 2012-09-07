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
	//====== �������� �������� ���� �����������
	m_hRC = 0;

	//====== ��������� �������� �����������
	m_AngleX = 35.f;
	m_AngleY = 20.f;

	//====== ���� ������ ��� ������� ��������
	m_AngleView = 45.f;

	//====== ��������� ���� ����
	m_BkClr = RGB(0, 0, 96);

	// ��������� ����� ���������� ���������� ����� ��������
	m_FillMode = GL_FILL;



	//== ��������� �������� ������� �������� (��� ��������)
	m_dx = m_dy = 0.f;

	//====== ���� �� ���������
	m_bCaptured = false;
	//====== ������ ������ �� ���� ������
	m_bRightButton = false;
	//====== ������ ������������������
	m_bQuad = true;

	//====== ��������� �������� ���������� ���������
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
	//====== ��������� ���� �����, ������ OpenGL
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

	//======= ��������� ���������� ���������
	SetLight();

	//====== ������������ ������� �������������
	glTranslatef(m_xTrans,m_yTrans,m_zTrans);
	glRotatef (m_AngleX, 1.0f, 0.0f, 0.0f );
	glRotatef (m_AngleY, 0.0f, 1.0f, 0.0f );

	//====== ����� �������� ������ �� ������
	for (int s = 0; s < pDoc->m_nSurfs; s++)
	{
		glCallList(m_nView * 4 + 1 + s);
	}
//	glCallList(m_nView * 4 + 2 + s);
//	glCallList(m_nView * 4 + 3 + s);

	//====== ������������ �������
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
	//====== ���������� ������� �� ���������
#if 1
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
#endif
	pDoc->DefaultGraphic();
	//====== ��������� �������� ������������ ������ �����
	//====== ����� ����� �� ���������� ������ �������
	m_zTrans = -1.5f*pDoc->m_fRangeX;
	m_xTrans = m_yTrans = 0.f;

	InitOG();
	//LeaveCriticalSection( &theApp.cs );
	return 0;
}

void COGView::OnDestroy(void)
{
	//EnterCriticalSection( &theApp.cs );
	//====== ������������� ������ ��������
	KillTimer(m_nView * 2+1);
#if 0

	//====== ����������� ������� �� ������
	wglMakeCurrent(0, 0);
#endif
	//====== ������� ��������
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
	//====== ����� ������������ ������
	CView::OnSize(nType, cx, cy);

	RefreshOG(false);
	//====== ���������� ������������ ����
	double dAspect = cx<=cy ? double(cy)/cx 
								 : double(cx)/cy;

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	//====== ��������� ������ ������������� ��������
	gluPerspective (m_AngleView, dAspect, 0.01, 10000.);

	//====== ��������� �������������� ���������
//	glViewport(0, 0, cx, cy);

	//LeaveCriticalSection( &theApp.cs );
}
void COGView::SetLight()
{
#if 1
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
#endif
	//====== ��� ����������� ����������� ���������
	//====== ��� ���������� ����� ��������
	//====== ��� ����� ���������� ���������
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);

	//====== ������� ��������� ���������
	//====== ������� �� �������� �������
	float fPos[] =
	{
		(m_LightParam[0]-50)*pDoc->m_fRangeX/100,
		(m_LightParam[1]-50)*pDoc->m_fRangeY/100,
		(m_LightParam[2]-50)*pDoc->m_fRangeZ/100,
		1.f
	};
	glLightfv(GL_LIGHT0, GL_POSITION, fPos);

	//====== ������������� ����������� ���������
	float f = m_LightParam[3]/100.f;
	float fAmbient[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbient);

	//====== ������������� ����������� �����
	f = m_LightParam[4]/100.f;	
	float fDiffuse[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffuse);

	//====== ������������� ����������� �����
	f = m_LightParam[5]/100.f;
	float fSpecular[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecular);

	//====== ���������� �������� ���������
	//====== ��� ������ ��������� �����
	f = m_LightParam[6]/100.f;
	float fAmbMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbMat);

	f = m_LightParam[7]/100.f;
	float fDifMat[4] = { f, f, f, 1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDifMat);

	f = m_LightParam[8]/100.f;
	float fSpecMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fSpecMat);

	//====== ���������� ���������
	float fShine = 128 * m_LightParam[9]/100.f;
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShine);

	//====== ��������� ����� ����������
	f = m_LightParam[10]/100.f;
	float fEmission[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, fEmission);
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::SetBkColor()
{
	//EnterCriticalSection( &theApp.cs );
	//====== ����������� ����� �� ��� ����������
	GLclampf red	= GetRValue(m_BkClr)/255.f,
			 green	= GetGValue(m_BkClr)/255.f,
			 blue	= GetBValue(m_BkClr)/255.f;
	//====== ��������� ����� ���� (��������) ����
	glClearColor (red, green, blue, 0.f);

	//====== ���������������� ��������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::DrawScene()
{
	COGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//EnterCriticalSection( &theApp.cs );
	//====== �������� ������ �������� ������
	for (int s = 0; s < pDoc->m_nSurfs; s++)
	{
		/// ???????!!!!!!!!!!!!!
		glNewList(m_nView * 4 + 1 + s, GL_COMPILE);

		//====== ��������� ������ ����������
		//====== ���������� ����� ���������
		glPolygonMode(GL_FRONT_AND_BACK, m_FillMode);

		//====== ������� ������������� �������
		UINT	nx = pDoc->m_vxSize[s]-1,
				nz = pDoc->m_vySize[s]-1;

		//====== ����� ������� �������� ���������
		if (m_bQuad)
			glBegin (GL_QUADS);

		//====== ���� ������� �� ����� ����������� (��� Z)
		for (UINT z=0, i=0;  z<nz;  z++, i++)
		{
			//====== ��������� �������� ����������
			//====== �� ������ ������ �����
			if (!m_bQuad)
				glBegin(GL_QUAD_STRIP);

			//====== ���� ������� ����� ��� X
			for (UINT x=0;  x<nx;  x++, i++)
			{
				// i, j, k, n - 4 ������� ������ ��������� ���
				// ������ � ����������� ������ ������� �������

				int	j = i + pDoc->m_vxSize[s],	// ������ ���� � ������� Z
					k = j+1,			// ������ ���� �� ���������
					n = i+1; 			// ������ ���� ������

				//=== ����� ��������� 4-� ������ �� ����������
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

					//=== ���������� �������� ������� ������
					ax = xi-xn,
					ay = yi-yn,

					by = yj-yi,
					bz = zj-zi,

					//====== ���������� ������� �������
					vx = ay*bz,
					vy = -bz*ax,
					vz = ax*by,

					//====== ������ �������
					v  = float(sqrt(vx*vx + vy*vy + vz*vz));
				
				//====== ���������� ������� �������
				vx /= v;
				vy /= v;
				vz /= v;

				//====== ������� ������� �������
				glNormal3f (vx,vy,vz);

				// ����� �������� ����������� �����������������
				if (m_bQuad)
				{
					//====== ����� ������ ��������������
					//====== � ����������� ������ ������� �������
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
				//====== ����� �������� ������� �����������������
				{
					glColor3f (0.9f, 0.9f, 1.0f);
					glVertex3f (xn, yn, zn);
					glColor3f (0.5f, 0.8f, 1.0f);
					glVertex3f (xj, yj, zj);
				}
			}
			//====== ��������� ���� ������ GL_QUAD_STRIP
			if (!m_bQuad)
				glEnd();
		}
		//====== ��������� ���� ������ GL_QUADS
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
	//====== ��������� ������ ������ OpenGL
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
	//====== ������������� ������
	KillTimer(m_nView * 2 +1);

	//====== �������� ������ �����������
	m_dx = 0.f;
	m_dy = 0.f;

	//====== ����������� ��������� ����,
	//====== ��������� �� � ���� ����
	SetCapture();
	//====== ���������� ���� �������
	m_bCaptured = true;
	//====== ���������� ���������� �������
	m_pt = point;
	
///	CView::OnLButtonDown(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== ���������� ���� ������� ������ ������
	m_bRightButton = true;

	//====== ������������� ������� �� ����� ������
	OnLButtonDown(nFlags, point);
	
//	CView::OnRButtonDown(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== ���� ��� ������,
	if (m_bCaptured)
	{
		//=== �� ����������� �������� ����� �����������
		//=== �� ���������� ������ ����������������
		if (fabs(m_dx) > 0.5f || fabs(m_dy) > 0.5f)
			//=== �������� ����� ����������� ��������
			SetTimer(m_nView * 2 + 1,33,0);
		else
			//=== ��������� ����� ����������� ��������
			KillTimer(m_nView * 2 +1);

		//====== ������� ���� ������� ����
		m_bCaptured = false;
		//====== ��������� ��������� ����
		ReleaseCapture();
	}
	
//	CView::OnLButtonUp(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== ������ ������ ��������
	m_bRightButton = false;
	//====== ������� ���� ������� ����
	m_bCaptured = false;
	//====== ��������� ��������� ����
	ReleaseCapture();
	
//	CView::OnRButtonUp(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnMouseMove(UINT nFlags, CPoint point) 
{
	//EnterCriticalSection( &theApp.cs );
	if (m_bCaptured)		// ���� ��� ������,
	{
		// ��������� ���������� �������� �������� ��������
		m_dy = float(point.y - m_pt.y)/40.f;
		m_dx = float(point.x - m_pt.x)/40.f;

		//====== ���� ������������ ���� ������ Ctrl,
		if (nFlags & MK_CONTROL)
		{
			//=== �������� ������������ ������ �����������
			m_xTrans += m_dx;
			m_yTrans -= m_dy;
		}
		else
		{
			//====== ���� ���� ������ ������ ������
			if (m_bRightButton)
				//====== ��������� �������� ������
				m_zTrans += (m_dx + m_dy)/2.f;
			else
			{
				//====== �����, �������� ���� ��������
				m_AngleX += m_dy;
				m_AngleY += m_dx;
			}
		}
		//=== � ����� ������ ���������� ����� ��������� ����
		m_pt = point;
		Invalidate(FALSE);
	}
	
//	CView::OnMouseMove(nFlags, point);
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnTimer(UINT nIDEvent) 
{
	//EnterCriticalSection( &theApp.cs );
	//====== ���� ��� ��� ��� ������
	if (nIDEvent==m_nView * 2 +1)
	{
		//====== ����������� ���� ��������
		m_AngleX += m_dy;
		m_AngleY += m_dx;
		//====== ������������ ����� �����
		if (m_AngleX > 360)
			m_AngleX -= 360;
		if (m_AngleX <-360)
			m_AngleX += 360;

		if (m_AngleY > 360)
			m_AngleY -= 360;
		if (m_AngleY <-360)
			m_AngleY += 360;

		//====== ������ ������������ ����
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
			//=== ������ ���������� ���������� ������ �������
			CView::OnTimer(nIDEvent);

	}
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnEditBackground() 
{
	//EnterCriticalSection( &theApp.cs );
	//====== ������� ������ ����������� ������
	CColorDialog dlg(m_BkClr);
	//====== ������������� ��� �����
	dlg.m_cc.Flags |= CC_FULLOPEN;
	//====== ��������� ������ � �������� ���������
	if (dlg.DoModal()==IDOK)
	{
		m_BkClr = dlg.m_cc.rgbResult;
		//====== �������� ���� ����
		SetBkColor();
		Invalidate(FALSE);
	}
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::OnEditProperties (void)
{
	//EnterCriticalSection( &theApp.cs );
	//====== ���� ������ ��� �� ������
	if (!m_pDlg)
	{
		//=== ������� ��� � ��������� � ����������� ������
		m_pDlg = new CPropDlg(this);
		m_pDlg->Create(IDD_PROP, this);
	}
	else
	{
		// �����, ��������� ����� � ���� ������������� �������
		m_pDlg->SetActiveWindow();
	}
	//LeaveCriticalSection( &theApp.cs );
}
void COGView::OnViewQuad() 
{
	//EnterCriticalSection( &theApp.cs );
	// ����������� ������� ����� ������� �����������������
	m_bQuad = ! m_bQuad;

	//====== ������ ������� �����������
	DrawScene();
	Invalidate(FALSE);
	UpdateWindow();
	//LeaveCriticalSection( &theApp.cs );
	
}

void COGView::OnUpdateViewQuad(CCmdUI* pCmdUI) 
{
	//====== ��������� ��� ������� ������ (�������)
	pCmdUI->SetCheck(m_bQuad==true);
	
}

void COGView::OnViewFill() 
{
	//EnterCriticalSection( &theApp.cs );
	//=== ����������� ����� ���������� ����������������
	m_FillMode = m_FillMode==GL_FILL ? GL_LINE : GL_FILL;

	//====== ������ ������� �����������
	DrawScene();
	Invalidate(FALSE);
	UpdateWindow();
	//LeaveCriticalSection( &theApp.cs );
	
}

void COGView::OnUpdateViewFill(CCmdUI* pCmdUI) 
{
	//====== ��������� ��� ������� ������ ������
	pCmdUI->SetCheck(m_FillMode==GL_FILL);
	
}
void COGView::GetLightParams(int *pPos)
{
	//EnterCriticalSection( &theApp.cs );
	//====== ������ �� ���� ������������
	for (int i=0; i<11; i++)
		//====== ��������� ������������ ������ pPos
		pPos[i] = m_LightParam[i];
	//LeaveCriticalSection( &theApp.cs );
}

void COGView::SetLightParam (short lp, int nPos)
{
	//EnterCriticalSection( &theApp.cs );
	//====== �������������� �������� lp �
	//====== ������������� ��� � ��������� nPos
	m_LightParam[lp] = nPos;

	//====== �������������� ��� � ������ ���������
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
	PIXELFORMATDESCRIPTOR pfd =	// ��������� �������
	{
		sizeof(PIXELFORMATDESCRIPTOR),// ������ ���������
		1,							// ����� ������
		PFD_DRAW_TO_WINDOW |	// ��������� GDI
		PFD_SUPPORT_OPENGL |	// ��������� OpenGL
		PFD_DOUBLEBUFFER,		// ������� �����������
		PFD_TYPE_RGBA,			// ������ RGBA, �� �������
		24, 						// ���������� ����������
		 							// � ������ ������ �����
		24,	0,						// ��� ���������� Red
		24,	0,						// ��� ���������� Green
		24,	0,						// ��� ���������� Blue
		24,	0,						// ��� ���������� Alpha
		0,							// ���������� ����������
									// ������ Accumulation
		0,			 				// �� �� ��� ���������� Red
		0,			 				// ��� ���������� Green
		0,							// ��� ���������� Blue
		0,							// ��� ���������� Alpha
		32, 						// ������� Z-������
		0,							// ������� ������ Stencil
		0,							// ������� ������ Auxiliary
		0,				 			// ������ ������������
		0,							// ���������� ����������
		0,							// ������ ������������
		0,							// ���� ���������� �����
		0							// ������ ������������
	};

	//====== �������� �������� ��������
	m_hdc = ::GetDC(GetSafeHwnd());

	//====== ������ ������� ��������� ����������� ������
	int iD = ChoosePixelFormat(m_hdc, &pfd);
	if ( !iD )
	{
		MessageBox("ChoosePixelFormat::Error");
		return ;
	}

	//====== �������� ���������� ���� ������
	if ( !SetPixelFormat (m_hdc, iD, &pfd) )
	{
		MessageBox("SetPixelFormat::Error");
		return ;
	}

	//====== �������� ������� �������� �������� OpenGL
	if ( !(m_hRC = wglCreateContext (m_hdc)))
	{
		MessageBox("wglCreateContext::Error");
		return;
	}

	//====== �������� ������� ��� � �������� ��������
	if ( !wglMakeCurrent (m_hdc, m_hRC))
	{
		MessageBox("wglMakeCurrent::Error");
		return ;
	}

	//====== ������ ����� �������� ������� OpenGL
	glEnable(GL_LIGHTING);			// ����� ���������
	//====== ����� ������ ���� �������� �����
	glEnable(GL_LIGHT0);
	//====== ���������� ��������� ������� (��� Z)
	glEnable(GL_DEPTH_TEST);
	//====== ���������� ��������� ���� ��������� �����������
	glEnable(GL_COLOR_MATERIAL);

	//====== ������������� ���� ����
	SetBkColor();

	//====== ������� ����������� � ���������� � ������
	DrawScene();

}

void COGView::RefreshOG(bool isfull)
{
	//====== �������� ������� ��� � �������� ��������
	if ( !wglMakeCurrent (m_hdc, m_hRC))
	{
		MessageBox("wglMakeCurrent::Error");
		return ;
	}

	//====== ������ ����� �������� ������� OpenGL
	glEnable(GL_LIGHTING);			// ����� ���������
	//====== ����� ������ ���� �������� �����
	glEnable(GL_LIGHT0);
	//====== ���������� ��������� ������� (��� Z)
	glEnable(GL_DEPTH_TEST);
	//====== ���������� ��������� ���� ��������� �����������
	glEnable(GL_COLOR_MATERIAL);

	//====== ������������� ���� ����
	SetBkColor();

	//====== ������� ����������� � ���������� � ������
//	DrawScene();
	if (!isfull)
		return;

	CRect r;

	//===== ������ ������� ���� �������
	GetWindowRect(&r);
	int cy = r.Height();
	int cx = r.Width();

		//====== ���������� ������������ ����
	double dAspect = cx<=cy ? double(cy)/cx 
								 : double(cx)/cy;

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	//====== ��������� ������ ������������� ��������
	gluPerspective (m_AngleView, dAspect, 0.01, 10000.);

	//====== ��������� �������������� ���������
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
