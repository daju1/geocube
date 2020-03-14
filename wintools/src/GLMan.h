// GLMan.h: interface for the CGLMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLMAN_H__CDFE1CE9_7436_45F0_A77A_DB412FC1C03F__INCLUDED_)
#define AFX_GLMAN_H__CDFE1CE9_7436_45F0_A77A_DB412FC1C03F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <gl\gl.h>
#include <gl\glu.h>
//#include "glut.h"

class  CGLMan  
{
public:
	void SaveBitmap(char* name);

//	GLuint SelectEntity(int x, int y);
//	virtual void SetLight(void); // child can change this
//	virtual void RenderScene(void);
//	virtual void SetViewVolumeOrtho(void);
//	virtual void SetViewVolume();

//	void LoadMatrix(void);
//	void SaveMatrix(void);
	void EndUpdate(void);
	void StartUpdate(void);
//	void KeepAspectRatio(int cx,int cy);
	HDC m_hDC; // device context , WM_DESTROY, use ReleaseDC
	HGLRC m_hRC; // GL rendering context

	// multiple rendering context
	HDC m_hOldDC ;
	HGLRC m_hOldRC; 

//	double m_dLeft,m_dTop;
//	double m_dRight,m_dBottom;
//	double m_dZNear, m_dZFar;

//	double m_dDist; // distance from near plane and point (0,0,0)
//	int m_nWndX, m_nWndY;
//	double m_dAR; // aspect ratio
//	int m_nvVP[4]; // viewport

	
	// matrix
//	double m_dvPro[16]; // project
//	double m_dvMod[16]; // modelview
//	int m_bPicking;


	
//	virtual void EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC );
//	virtual void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC );

	// drawing tools
//	void DrawAxis(double height);
//	void DrawNet(double xsize, double zsize, double xstep, double zstep);

	CGLMan();
	virtual ~CGLMan();

};
#endif

#endif // !defined(AFX_GLMAN_H__CDFE1CE9_7436_45F0_A77A_DB412FC1C03F__INCLUDED_)
