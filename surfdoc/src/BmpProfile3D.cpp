// BmpProfile3D.cpp: implementation of the BmpProfile3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BmpProfile3D.h"
#include "SurfDoc.h"
#include "texture.h"
#include "distance3D.h"
#include ".\bmpprofile3d.h"
#include "winsurftree.h"

double MaxOfVector(vector<double>&v)
{
	double ans = -DBL_MAX;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (ans < v[i]) ans = v[i];
	}
	return ans;
}
double MinOfVector(vector<double>&v)
{
	double ans = DBL_MAX;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (ans > v[i]) ans = v[i];
	}
	return ans;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BmpProfile3D::BmpProfile3D()
{
	OnCreate();
}
BmpProfile3D::BmpProfile3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}

void BmpProfile3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::bmp_profile3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_alpha_plane = 50;
}

BmpProfile3D::BmpProfile3D(const BmpProfile3D & bp)
{
//	OnCreate();
	dynamic_cast<Object*>(this)->Init(bp);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(bp);
	dynamic_cast<Bmp3D*  >(this)->Init(bp);
	this->Init(bp);
}
BmpProfile3D& BmpProfile3D::operator=(const BmpProfile3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(bp);
	dynamic_cast<Bmp3D*  >(this)->Init(bp);
	this->Init(bp);

	return *this;
}

BmpProfile3D::~BmpProfile3D()
{

}

bool BmpProfile3D::LoadGLTexture(char * filename, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile)									// Load Bitmaps And Convert To Textures
{
	printf("BmpProfile3D::LoadGLTexture\n");
	bool Status=false;									// Status Indicator
	if (xMap.size() == yMap.size() && 
		xMap.size() >= 2 &&
		zProfile.size() == 2 
		)
	{
		printf("Bmp3D::LoadGLTexture filename = %s\n", filename);
		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (UploadImage ( filename, texture[0] , &sizeX, &sizeY ))
		{
			Status=true;								// Set The Status To TRUE
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// заполн€ем массив прив€зок профил€ к карте
			UINT lenMapAttach = xMap.size();
			ProfileAttachPoint* ptpa;
			ptpa = new ProfileAttachPoint[lenMapAttach];
			double xProfile = 0.0;
			m_vxTexCoord.resize(0);
			for(UINT i = 0; i < lenMapAttach; i++)
			{
				m_vxTexCoord.push_back(xProfile);
				ptpa[i].xMap		= xMap[i];
				ptpa[i].yMap		= yMap[i];
				ptpa[i].xProfile	= xProfile;
				ptpa[i].bAttached	= true;
				// переход€ к следующей точке излома пересчитываем 
				// координату начальной точки излома в координатах профил€ 
				if (i < lenMapAttach - 1)
					xProfile += Distance(
						CPoint2(xMap[i  ],yMap[i  ]), 
						CPoint2(xMap[i+1],yMap[i+1])
						);
			}
			for(UINT i = 0; i < lenMapAttach; i++)
			{
				m_vxTexCoord[i] /= m_vxTexCoord.back();
			}
			//m_vBlnProfileMapAttaches.AddMsg(ptpa, lenMapAttach);
			//this->Build(CPoint2(xmin,ymin), CPoint2(xmax,ymax), lenMapAttach, ptpa);
			//int planelen = 2*lenMapAttach;
			//Free();
			for (int ima = 0; ima < lenMapAttach; ima++)
			{
				CPoint3 pt;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				pt.bVisible	= true;
				pt.x			= ptpa[ima].xMap;
				pt.y			= ptpa[ima].yMap;
				pt.z			= MinOfVector(zProfile);
				this->PushBack(pt);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				pt.bVisible	= true;
				pt.x			= ptpa[ima].xMap;
				pt.y			= ptpa[ima].yMap;
				pt.z			= MaxOfVector(zProfile);
				this->PushBack(pt);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}

			//CPoint3 * pt3plane = new CPoint3[planelen];
			//if (pt3plane) delete[] pt3plane;
			if(ptpa) delete[] ptpa;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/*
			AllocPoints(4);

			CPoint3 pt;
			// складываем данные в документ
			// letf and bottom of picture
			pt.x = xMap[0];//start of profile
			pt.y = yMap[0];//start of profile
			pt.z = zProfile[0];//bottom
			pt.bVisible = true;
			m_vdPoints[0] = pt;
			m_vvPoints[0] = pt;
printf("0 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);
			// складываем данные в документ
			// right and bottom of picture
			pt.x = xMap[1];//end of profile
			pt.y = yMap[1];//end of profile
			pt.z = zProfile[0];//bottom
			pt.bVisible = true;
			m_vdPoints[1] = pt;
			m_vvPoints[1] = pt;
printf("1 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);

			// складываем данные в документ
			// right and top of texture
			pt.x = xMap[1];//end of profile
			pt.y = yMap[1];//end of profile
			pt.z = zProfile[1];//top
			pt.bVisible = true;
			m_vdPoints[2] = pt;
			m_vvPoints[2] = pt;
printf("2 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);

			// складываем данные в документ
			// left and top of picture
			pt.x = xMap[0];//start of profile
			pt.y = yMap[0];//start of profile
			pt.z = zProfile[1];//top
			pt.bVisible = true;
			m_vdPoints[3] = pt;
			m_vvPoints[3] = pt;
printf("3 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);*/
		}
	}
	return Status;										// Return The Status
}

HTREEITEM BmpProfile3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	sprintf(szItemText, "%d x %d", SizeX(), SizeY());
	// Add the item to the tree-view control
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
extern bool getNorm(double v1[3], double v2[3], double out[3]);
#if 0
void BmpProfile3D::Draw()
{
	if (m_pSurfDoc)
	{
		m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
		//====== ”становка режима заполнени€
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);

		glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
glBindTexture(GL_TEXTURE_2D, texture[0]);

		size_t len = this->GetPointsNumber();
		glBegin(GL_QUADS);
		for (size_t i = 0; i < len; i++)
		{
			double d1[3],d2[3],norm[3];

			//====== ќбход вершин осуществл€етс€
			//====== в направлении против часовой стрелки
			int i_minus_1 = i-1;
			int i_plus_1  = i+1;

			if(i == 0)
			{
				i_minus_1 = len-1;
			}
			if (i == len-1)
			{
				i_plus_1  = 0;
			}
			d1[0] = m_vvPoints[i_minus_1].x-m_vvPoints[i].x;
			d1[1] = m_vvPoints[i_minus_1].y-m_vvPoints[i].y;
			d1[2] = m_vvPoints[i_minus_1].z-m_vvPoints[i].z;

			d2[0] = m_vvPoints[i].x-m_vvPoints[i_plus_1].x;
			d2[1] = m_vvPoints[i].y-m_vvPoints[i_plus_1].y;
			d2[2] = m_vvPoints[i].z-m_vvPoints[i_plus_1].z;

			getNorm(d1,d2,norm);
			//====== «адание вектора нормали

			if (m_vvPoints[i].bVisible)
			{
				glNormal3dv (norm);
				{
	//				glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha); 
					glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
	//				glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_alpha); 
				}
				switch(i)
				{
				case 0:
					{
						glTexCoord2f(0.0f, 1.0f);//letf and bottom of picture (0.0, 0.0)
					}
					break;
				case 1:
					{
						glTexCoord2f(1.0f, 1.0f);//right and bottom of picture (1.0, 0.0)
					}
					break;
				case 2:
					{
						glTexCoord2f(1.0f, 0.0f);//right and top of texture (1.0, 1.0)
					}
					break;
				case 3:
					{
						glTexCoord2f(0.0f, 0.0f);//left and top of picture (0.0, 1.0)
					}
					break;
				}
				glVertex3d (m_vvPoints[i].x, m_vvPoints[i].y, m_vvPoints[i].z);
			}
		}
		glEnd();
glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
		glEndList();
	}
}
#else
#if 1
void BmpProfile3D::Drawing()
{
	if (m_pSurfDoc)
	{
		//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
		//====== ”становка режима заполнени€
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);

		glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		size_t len = this->GetPointsNumber();
		//=============================================
		for (int i = 0; i < len - 3; i+=2)
		{							
			glBegin(GL_QUADS);
			//===== ¬ычисление вектора нормали
			double d1[3], d2[3], norm[3];
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//i+1	i+3
			//i		i+2
			//i
			d1[0] = this->GetViewPoint(i+2).x-this->GetViewPoint(i).x;
			d1[1] = this->GetViewPoint(i+2).y-this->GetViewPoint(i).y;
			d1[2] = this->GetViewPoint(i+2).z-this->GetViewPoint(i).z;

			d2[0] = this->GetViewPoint(i).x-this->GetViewPoint(i+1).x;
			d2[1] = this->GetViewPoint(i).y-this->GetViewPoint(i+1).y;
			d2[2] = this->GetViewPoint(i).z-this->GetViewPoint(i+1).z;

			getNorm(d1,d2,norm);
			glNormal3dv (norm);	
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			//glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glColor4ub (255, 255, 255, (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glTexCoord2f(m_vxTexCoord[i/2],1.0);//bottom of picture;
			glVertex3f( this->GetViewPoint(i).x,  this->GetViewPoint(i).y, this->GetViewPoint(i).z );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//i+1	i+3
			//i		i+2
			//i+1
			d1[0] = this->GetViewPoint(i).x-this->GetViewPoint(i+1).x;
			d1[1] = this->GetViewPoint(i).y-this->GetViewPoint(i+1).y;
			d1[2] = this->GetViewPoint(i).z-this->GetViewPoint(i+1).z;

			d2[0] = this->GetViewPoint(i+1).x-this->GetViewPoint(i+3).x;
			d2[1] = this->GetViewPoint(i+1).y-this->GetViewPoint(i+3).y;
			d2[2] = this->GetViewPoint(i+1).z-this->GetViewPoint(i+3).z;

			getNorm(d1,d2,norm);
			glNormal3dv (norm);	
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glColor4ub (255, 255, 255, (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glTexCoord2f(m_vxTexCoord[i/2],0.0);//top of picture
			glVertex3f( this->GetViewPoint(i+1).x,  this->GetViewPoint(i+1).y, this->GetViewPoint(i+1).z );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//i+1	i+3
			//i		i+2
			//i+3
			d1[0] = this->GetViewPoint(i+1).x-this->GetViewPoint(i+3).x;
			d1[1] = this->GetViewPoint(i+1).y-this->GetViewPoint(i+3).y;
			d1[2] = this->GetViewPoint(i+1).z-this->GetViewPoint(i+3).z;

			d2[0] = this->GetViewPoint(i+3).x-this->GetViewPoint(i+2).x;
			d2[1] = this->GetViewPoint(i+3).y-this->GetViewPoint(i+2).y;
			d2[2] = this->GetViewPoint(i+3).z-this->GetViewPoint(i+2).z;

			getNorm(d1,d2,norm);
			glNormal3dv (norm);	
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glColor4ub (255, 255, 255, (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glTexCoord2f( m_vxTexCoord[i/2+1],0.0);//top of picture
			glVertex3f( this->GetViewPoint(i+3).x,  this->GetViewPoint(i+3).y, this->GetViewPoint(i+3).z );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//i+1	i+3
			//i		i+2
			//i+2
			d1[0] = this->GetViewPoint(i+3).x-this->GetViewPoint(i+2).x;
			d1[1] = this->GetViewPoint(i+3).y-this->GetViewPoint(i+2).y;
			d1[2] = this->GetViewPoint(i+3).z-this->GetViewPoint(i+2).z;

			d2[0] = this->GetViewPoint(i+2).x-this->GetViewPoint(i).x;
			d2[1] = this->GetViewPoint(i+2).y-this->GetViewPoint(i).y;
			d2[2] = this->GetViewPoint(i+2).z-this->GetViewPoint(i).z;

			getNorm(d1,d2,norm);
			glNormal3dv (norm);	
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glColor4ub (255, 255, 255, (GLubyte)m_pSurfDoc->m_alpha_plane); 
			glTexCoord2f(m_vxTexCoord[i/2+1],1.0);//bottom of picture;
			glVertex3f( this->GetViewPoint(i+2).x,  this->GetViewPoint(i+2).y, this->GetViewPoint(i+2).z );
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
		//glEndList();
	}
}
#else
void BmpProfile3D::Draw()
{
	if (m_pSurfDoc)
	{
		//====== Ќастройка OpenGL на использование массивов
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		if (m_pSurfDoc->m_bFlatShading)
			glShadeModel (GL_FLAT);
		else
			glShadeModel (GL_SMOOTH);

		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
		int len = this->GetPointsNumber();
		//====== «ахват пам€ти под динамические массивы
		VERT_TEX *Vert = new VERT_TEX[len];
		QUAD *Quad = new QUAD[(len/2)-1];
		int q;
		//=============================================
		for (int i = 0; i < len - 1; i+=2)
		{							
			//===== ¬ычисление вектора нормали
			double d1[3], d2[3], norm[3];
			d1[0] = this->GetViewPoint(i+1).x-this->GetViewPoint(i).x;
			d1[1] = this->GetViewPoint(i+1).y-this->GetViewPoint(i).y;
			d1[2] = this->GetViewPoint(i+1).z-this->GetViewPoint(i).z;

			d2[0] = this->GetViewPoint(i).x-this->GetViewPoint(i+2).x;
			d2[1] = this->GetViewPoint(i).y-this->GetViewPoint(i+2).y;
			d2[2] = this->GetViewPoint(i).z-this->GetViewPoint(i+2).z;

			getNorm(d1,d2,norm);
			CPoint3 n = CPoint3(norm[0],norm[1],norm[2]);
				
			COLORREF  planeColor = RGBA (255,255,255, (GLubyte)m_pSurfDoc->m_alpha_plane); 
			//COLORREF  planeColor = RGBA (255,255,255, 50); 

			Vert[i].c	= planeColor;
			Vert[i+1].c = planeColor;

			//====== «адание вектора нормали
			Vert[i].n	= n;
			Vert[i+1].n = n;
			Vert[i].v	= this->GetViewPoint(i);
			Vert[i+1].v = this->GetViewPoint(i+1);

			Vert[i].t = CPoint2(m_vxTexCoord[i/2],1.0);//bottom of picture
			Vert[i+1].t = CPoint2(m_vxTexCoord[i/2],0.0);//top of picture
/*
			if( i == len - 4)
			{
				Vert[i+2].n	= n;
				Vert[i+3].n = n;
				Vert[i+2].v = this->GetViewPoint(i+2);
				Vert[i+3].v = this->GetViewPoint(i+3);
				Vert[i+2].c	= planeColor;
				Vert[i+3].c = planeColor;
			}
*/
			q = i/2;
			Quad[q].i1 = i;
			Quad[q].i2 = i+1;
			Quad[q].i3 = i+3;
			Quad[q].i4 = i+2;

		}
		//====== «адание адресов трех массивов (вершин,
		//====== нормалей и цветов),
		//====== а также шага перемещени€ по ним
		glVertexPointer(3, GL_PRECISION, sizeof(VERT_TEX), &Vert->v);
		glNormalPointer(GL_PRECISION, sizeof(VERT_TEX), &Vert->n);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT_TEX),
														&Vert->c);
		glTexCoordPointer(
			2, //The number of coordinates per array element. The value of size must be 1, 2, 3, or 4. 
			GL_PRECISION, //The data type of each texture coordinate in the array using the following symbolic constants: GL_SHORT, GL_INT, GL_FLOAT, and GL_DOUBLE
			sizeof(VERT_TEX), //The byte offset between consecutive array elements. When stride is zero, the array elements are tightly packed in the array
			&Vert->t);

		q = len/2-1;
		//====== ‘ормирование списка рисующих команд
		glDrawElements(GL_QUADS, 4*q,
							GL_UNSIGNED_INT, Quad);
		glEndList();
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		
		//== ќсвобождение пам€ти, так как список сформирован
		delete [] Vert;
		delete [] Quad;
	}
}
#endif
#endif
void BmpProfile3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "BmpProfile3D" , 0);

}

bool BmpProfile3D::ColorDialog(void)
{
	return false;
}

COLORREF BmpProfile3D::GetColor(void)
{
	return COLORREF();
}

void BmpProfile3D::SetColor(COLORREF color)
{
}

DWORD BmpProfile3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, BmpProfile3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	//dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	ar << *dynamic_cast<Bmp3D *>(&ob);
	DWORD version = ob.m_object_version;
	switch (version)
	{
	case 1:
		{
			ar << ob.m_alpha_plane;
			ar << ob.m_vxTexCoord;
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
Archive& operator >>(Archive& ar, BmpProfile3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	//dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	ar >> *dynamic_cast<Bmp3D *>(&ob);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_alpha_plane;
			ar >> ob.m_vxTexCoord;
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

