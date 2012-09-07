// GLMan.cpp: implementation of the CGLMan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLMan.h"
#include <algorithm>
using namespace std;

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLMan::CGLMan()
{
//m_dLeft=-10.0;
//	m_dTop=10.0;
//	m_dRight=10.0;
//	m_dBottom=-10.0;
//	m_dZNear=30.0;
//	m_dZFar=1000.0;
//	m_dDist=10.0;

//	m_bPicking=false;
}

CGLMan::~CGLMan()
{

}

#if 0
void CGLMan::SetViewVolume()
{
	//in case, there exist many OpenGL windows
	//this code should work

	//projection mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum(m_dLeft, m_dRight, m_dBottom, m_dTop, m_dZNear, m_dZFar);
	//glOrtho(m_dLeft, m_fRight, m_fBottom, m_fTop, znear, zfar);

	glTranslated(0,0,-m_dZNear-m_dDist);

    //model view mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



}




// Enable OpenGL
void CGLMan::EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC )
{
  PIXELFORMATDESCRIPTOR pfd;
  int iFormat;

  // get the device context (DC)
  *hDC = GetDC( hWnd );

  // set the pixel format for the DC
  ZeroMemory( &pfd, sizeof( pfd ) );
  pfd.nSize = sizeof( pfd );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
    PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  pfd.iLayerType = PFD_MAIN_PLANE;


  iFormat = ChoosePixelFormat( *hDC, &pfd );
  SetPixelFormat( *hDC, iFormat, &pfd );

  // create and enable the render context (RC)
  *hRC = wglCreateContext( *hDC );
  wglMakeCurrent( *hDC, *hRC );



  	//gl setting
    glDrawBuffer(GL_BACK);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);

}


// Disable OpenGL

VOID CGLMan::DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
  wglMakeCurrent( NULL, NULL );
  wglDeleteContext( hRC );
  ReleaseDC( hWnd, hDC );
}

void CGLMan::KeepAspectRatio(int cx, int cy)
{
   if (cy==0) return; 
    else m_dAR=((double) cx)/ ((double)cy);


	//3d
	double height = m_dTop-m_dBottom;
    double width =  height*m_dAR; //control width from height
	double cenx=(m_dLeft+ m_dRight) / 2.;
	double ceny=(m_dTop+ m_dBottom) /2.;

	//클리핑 영역 설정 
	m_dLeft=cenx - width/2.;
	m_dRight=cenx + width/2.;
	m_dTop = ceny + height/2.;
	m_dBottom= ceny - height/2.; 


}
#endif
void CGLMan::StartUpdate()
{
	m_hOldDC = wglGetCurrentDC();
	m_hOldRC = wglGetCurrentContext();
	wglMakeCurrent( m_hDC, m_hRC );

}

void CGLMan::EndUpdate()
{
	wglMakeCurrent( m_hOldDC, m_hOldRC );
}
#if 0
void CGLMan::SaveMatrix()
{
	//backup matrix
	glGetDoublev(GL_PROJECTION_MATRIX, m_dvPro); //get projection matrix
	glGetDoublev(GL_MODELVIEW_MATRIX, m_dvMod); //get modelview matrix
}

void CGLMan::LoadMatrix()
{
	//RESTORE MATRIX
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(m_dvPro);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m_dvMod);

}

void CGLMan::SetViewVolumeOrtho()
{

	//projection mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(m_dLeft, m_dRight, m_dBottom, m_dTop, -m_dZFar, m_dZFar);
    //model view mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void CGLMan::RenderScene()
{

	// OpenGL animation code goes here

//	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
				 (float)GetGValue(color)/255.0f,
				 (float)GetBValue(color)/255.0f,
				 1.0);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | 
    GL_STENCIL_BUFFER_BIT);
	int error=glGetError();

	glEnable(GL_COLOR_MATERIAL);
	glColor3d(1,0.5,0);
	error=glGetError();
	TRACE("GL ERROR %x\n" ,error);
	glutSolidSphere(10, 20, 20);
}



void CGLMan::SetLight()
{
	// Set the material color to follow the current color
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	//glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
	glEnable(GL_COLOR_MATERIAL);


	float ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	float diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
    float specular[] = { 1.0, 1.0, 1.0, 0.0 };

    float position[] = { -10, 10, 10,  0 };
    float lmodel_ambient[] = { 0.7f, 0.7f, 0.7f, 0.0f };
    float local_view[] = { 0.0 };

    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

   
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

GLuint CGLMan::SelectEntity(int x, int y)
{
	//confirm rendering context
	wglMakeCurrent(m_hDC, m_hRC);

	//depth comparison
	GLuint depth= (GLuint) ~0;
	GLuint z1,z2;

	GLuint buffer[200]; //select buffer
	int hits, viewport[4];
	int chosen=NULL;

	glSelectBuffer(200,buffer); //set up the selction buffer
	glGetIntegerv(GL_VIEWPORT, viewport);

	TRACE("Gl Get Error %x \n",(int)glGetError());
		

	glRenderMode(GL_SELECT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix(x,viewport[3]-y,2, 2, viewport);
	glMultMatrixd(m_dvPro);
	glMatrixMode(GL_MODELVIEW);

	m_bPicking=true;
	RenderScene(); //select mode is true
	m_bPicking=false;
	hits=glRenderMode(GL_RENDER);


	if (hits<=0) TRACE("nothing is selected \n");
	else if (hits>=1) {
		int i;
		int p=0; //base pointer
		int number=0;

			BOOL GOT;

	   		for (i=0;i<hits;i++) {
			number=buffer[p]; 
			z1= buffer[p+1];
			z2= buffer[p+2];

			GOT=FALSE;
			if (z1<depth) {depth=z1;GOT=TRUE;}
			if (z2<depth) {depth=z2;GOT=TRUE;}

			p+= 2 + number ;
			if (GOT) chosen=buffer[p];			
				
			p++; //move to the next hit list
			}




		//buffer [0]: number of names in the name stack
		//buffer [1]: minimum z , [2]: maximum z, 
		//buffer [3] : 1st chosen number
		//buffer [4]: 2nd chosen  [5]: 3rd chosen ..etc.. ->
		//int name_number=buffer[0];
		//int id=buffer [ (name_number-1) + 3 ] ;
		//char scr[100];
		//sprintf(scr,"number %d \n",id );
		//afxDump<<scr<<'\n';
		//chosen=id; // id를 선택하였다 
	} //end of else


	//원 화면 복귀 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixd(m_dvPro);
	glMatrixMode(GL_MODELVIEW);

	return chosen;

}


void CGLMan::DrawAxis(double height)
{
	double height2= height*0.5;
	double base=height2*0.1;
	
	//begin
	GLUquadricObj* obj=gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricNormals(obj,GLU_SMOOTH);

	glColor4d(1,1,0,0.5);
	glutSolidCube(base*2);

	//draw Z
	glColor4d(0,0,1,0.5);
	glPushMatrix();
	glTranslated(0,0,base);
	gluCylinder(obj,base,base, height, 4, 1); 
	glTranslated(0,0,height);
	gluCylinder(obj,base*2,0, height2, 4, 1); 
	glPopMatrix();

	//draw Y
	glColor4d(0,1,0,0.5);
	glPushMatrix();
	glRotated(90, -1, 0, 0);
	glTranslated(0,0,base);
	gluCylinder(obj,base,base, height, 4, 1); 
	glTranslated(0,0,height);
	gluCylinder(obj,base*2,0, height2, 4, 1); 
	glPopMatrix();

	//draw X
	glColor4d(1,0,0,0.5);
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(0,0,base);
	gluCylinder(obj,base,base, height, 4, 1); 
	glTranslated(0,0,height);
	gluCylinder(obj,base*2,0, height2, 4, 1); 
	glPopMatrix();


	gluDeleteQuadric(obj);
	//end

}

//draw basic grids
// no color material setting here
void CGLMan::DrawNet(double xsize, double zsize, double xstep, double zstep)
{

	//adjust xsize , zsize
	if (xstep<0.0000001 || zstep<0.0000001) return; //avoid too small grid
	int countx= (int)xsize/xstep;
	int countz= (int)zsize/zstep;

	//okay
	xsize= (double)countx * xstep;
	zsize= (double)countz * zstep;



	glPushMatrix();

	double x,z;
	
	//main line
	//glDisable(GL_LINE_STIPPLE);
	int c=0;
	glLineWidth(2);
	// middle
	c=0;
	for (x=0; x<=xsize; x+=xstep) {
		if ( c++%5 == 0 ) {
			glLineWidth(2);
		}
		else {
			glLineWidth(1);
		}
			glBegin(GL_LINES);
		glVertex3d(x, 0, -zsize);
		glVertex3d(x, 0,  zsize);
		glEnd();
		
	}

	c=0;
	for (x=0; x>=-xsize; x-=xstep) {
			if ( c++%5 == 0 ) {
			glLineWidth(2);
		}
		else {
			glLineWidth(1);
		}
			glBegin(GL_LINES);
		glVertex3d(x, 0, -zsize);
		glVertex3d(x, 0,  zsize);
		glEnd();
	}

	c=0;
	for (z=0; z<=zsize; z+=zstep) {
			if ( c++%5 == 0 ) {
			glLineWidth(2);
		}
		else {
			glLineWidth(1);
		}
		glBegin(GL_LINES);
		glVertex3d(-xsize, 0, z);
		glVertex3d( xsize, 0, z);
		glEnd();
	}
	
	c=0;
	for (z=0; z>=-zsize; z-=zstep) {
		if ( c++%5 == 0 ) {
			glLineWidth(2);
		}
		else {
			glLineWidth(1);
		}
		glBegin(GL_LINES);
		glVertex3d(-xsize, 0, z);
		glVertex3d( xsize, 0, z);
		glEnd();
	}




	//major line
	glLineWidth(3);
	// big
	glBegin(GL_LINES);
	glVertex3d(0, 0, -zsize);
	glVertex3d(0, 0,  zsize);
	glVertex3d(-xsize, 0, 0);
	glVertex3d( xsize, 0, 0);
	glLineWidth(1);

	glEnd();
	
	
	glPopMatrix();	

}
#endif
//  save OpenGL back buffer to the disk directly
void CGLMan::SaveBitmap(char* name) 
{
	int i;

	glReadBuffer(GL_BACK); //  designate buffer to read

	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	char* buffer=NULL;   
	int width=vp[2]; 
	int height=vp[3]; 
	//int size=(width+1)*(height+1)*3;
	int size=(width+1)*(height+1)*4;

	//  get memory
	buffer=new char[size]; //  Red , Green , Blue -> RGB
	if (buffer==NULL) throw "memory cannot be gained";

	//  read pixels to buffer
	//  GL_BGR_EXT has compatibility problem.
	//  so use GL_RGB
	//  swap Red, Blue values..

	//  problem code
	//  FIRE GL 1000 Pro works very well, though
	// glReadPixels(0,0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);

	//  standard code
	//glReadPixels(0,0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glReadPixels(0,0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	/*for (i=0;i<size;i+=3) {
		swap(*(buffer+i), *(buffer+i+2));
	}*/
	
	for (i=0;i<size;i+=4) {
		swap(*(buffer+i), *(buffer+i+2));
	}

	//  write to disk

	FILE* file=fopen(name, "wb");
	if (file==NULL) throw "Cannot open file to save bitmap!";

	//  write header
	BITMAPFILEHEADER	hdr; //  file header
	BITMAPINFOHEADER	bi;  //  info header
	//  set up info header
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= width;
	bi.biHeight 		= height;
	bi.biPlanes 		= 1;
	//bi.biBitCount		= 24;
	bi.biBitCount		= 32;
	bi.biCompression	= BI_RGB;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	//  set up file header
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	//  is always "BM"
	hdr.bfSize		=  sizeof( hdr ) + sizeof(bi) + size;
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + bi.biSize );

	//  write to disk
	fwrite(&hdr, sizeof(hdr), 1, file); //  file header
	fwrite(&bi, sizeof(bi), 1, file); //  info header

	//  write body

	for (i=0;i<size;i++)
		fputc(buffer[i], file);
	printf("Wrote %d Characters to \"%s\"\n", size, name);
	fclose(file);

	//  free memory
	delete buffer;
}

