// Bmp3D.h: interface for the Bmp3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMP3D_H__5BDF9CA3_180D_4A9B_8116_BD24AC493B65__INCLUDED_)
#define AFX_BMP3D_H__5BDF9CA3_180D_4A9B_8116_BD24AC493B65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library
#endif
#include "Primitive3D.h"

class SurfDoc;
class vdouble;

typedef struct tagRECT_3D
{
    CPoint3    left;
    CPoint3    top;
    CPoint3    right;
    CPoint3    bottom;
} RECT_3D, *PRECT_3D, NEAR *NPRECT_3D, FAR *LPRECT_3D;


class Bmp3D  : public Primitive3D <CPoint3> 
{
	friend class BmpProfile3D;
	//AUX_RGBImageRec* image;
	GLint sizeX, sizeY;

	GLuint	texture[1];			// Storage For One Texture
	virtual void Drawing();
public:
	//AUX_RGBImageRec *LoadBMP(char *Filename);				// Loads A Bitmap Image
	bool LoadGLTexture();
	bool LoadGLTexture(char * filename, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile);
	bool LoadGLTexture(char * filename, vector<double> &xMap, vector<double> &yMap, double z);// Load Bitmaps And Convert To Textures;
	virtual void PropertiesDialog();
	GLint SizeX(){return sizeX;} 
	GLint SizeY(){return sizeY;} 

	void OnCreate(void);

	Bmp3D();
	Bmp3D(SurfDoc * pSurfDoc);
	virtual ~Bmp3D();

	void Init(const Bmp3D& ob);
	Bmp3D(const Bmp3D& ob);
	Bmp3D& operator=(const Bmp3D& ob);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Bmp3D& ob);
	friend Archive& operator >>(Archive& ar, Bmp3D& ob);
};

#endif // !defined(AFX_BMP3D_H__5BDF9CA3_180D_4A9B_8116_BD24AC493B65__INCLUDED_)
