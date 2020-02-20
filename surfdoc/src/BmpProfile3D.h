// BmpProfile3D.h: interface for the BmpProfile3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPPROFILE3D_H__743D0330_14DA_4347_BF3D_2A0064203B90__INCLUDED_)
#define AFX_BMPPROFILE3D_H__743D0330_14DA_4347_BF3D_2A0064203B90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"
#include "points.h"
#include "../../array/src/vect.h"
#include "Bmp3D.h"

// это полупрозрачные ломаные плоскости в трёхмерном пространстве, 
// символизирующие расположение ломанного листа разреза
class BmpProfile3D  : public Bmp3D 
{
	friend class SurfDoc;
	vector<double> m_vxTexCoord;
	virtual void Drawing();
public:

	int m_alpha_plane; // коэффициент прозрачности


    
	bool BmpProfile3D::LoadGLTexture(char * filename, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile);									// Load Bitmaps And Convert To Textures

	void Init(const BmpProfile3D& bp)
	{			
		this->m_alpha_plane				= bp.m_alpha_plane;
		this->m_vxTexCoord				= bp.m_vxTexCoord;
	}

	BmpProfile3D& BmpProfile3D::operator=(const BmpProfile3D& bp);


	BmpProfile3D();
	BmpProfile3D(const BmpProfile3D & bp);
	BmpProfile3D(SurfDoc* pSurfDoc);
	virtual ~BmpProfile3D();

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	void OnCreate(void);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, BmpProfile3D& ob);
	friend Archive& operator >>(Archive& ar, BmpProfile3D& ob);
};

#endif // !defined(AFX_BMPPROFILE3D_H__743D0330_14DA_4347_BF3D_2A0064203B90__INCLUDED_)
