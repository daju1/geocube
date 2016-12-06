// Poligon3D.cpp: implementation of the Poligon3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Poligon3D.h"
#include "DrawScene.h"
#include ".\poligon3d.h"
#include "winsurftree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Poligon3D::Poligon3D()
{
	m_pSurfDoc = NULL;
	m_pSurface = NULL;
	OnCreate();
}
Poligon3D::Poligon3D(SurfDoc * pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	m_pSurface = NULL;
	OnCreate();
}
#define POLYGON_VERSION 2
void Poligon3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::poligon3d;
	this->m_object_version = POLYGON_VERSION;
	this->m_max_object_version = POLYGON_VERSION;
	id_umpoz = 0;
}

Poligon3D::~Poligon3D()
{
	m_pSurfDoc = NULL;
	m_pSurface = NULL;

}


void Poligon3D::Init(Surface3D * pSurface)
{
	m_pSurface = pSurface;
}

void Poligon3D::Init(vdouble &x, vdouble &y, vdouble &z, COLORREF color)
{
	if (x.Length() == y.Length() && y.Length() == z.Length())
	{
		m_ptMax.x = x.Max();
		m_ptMax.y = y.Max();
		m_ptMax.z = z.Max();

		m_ptMin.x = x.Min();
		m_ptMin.y = y.Min();
		m_ptMin.z = z.Min();

		Free();
		AllocPoints(z.Length());

		m_color = color;
		CPoint3 pt;
		// складываем данные в документ
		for(size_t i = 0; i < GetPointsNumber(); i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;
			m_vdPoints[i] = pt;
			m_vvPoints[i] = pt;
		}
	}
}
HTREEITEM Poligon3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	// Add the item to the tree-view control
	sprintf(szItemText, "len = %d color = %u", GetPointsNumber(), m_color);	
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
}
extern bool getNorm(double v1[3], double v2[3], double out[3]);
extern GLuint	texture[];			// Storage For One Texture ( NEW )

#include <sstream>
using std::stringstream;

// DEBUG //
//stringstream ss;

GLdouble vertices[4096][6];               // arrary to store newly created vertices (x,y,z,r,g,b) by combine callback
int vertexIndex = 0;                    // array index for above array incremented inside combine callback

///////////////////////////////////////////////////////////////////////////////
// GLU_TESS CALLBACKS
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessBeginCB(GLenum which)
{
    glBegin(which);

    // DEBUG //
//    ss << "glBegin(" << getPrimitiveType(which) << ");\n";
}



void CALLBACK tessEndCB()
{
    glEnd();

    // DEBUG //
//    ss << "glEnd();\n";
}



void CALLBACK tessVertexCB(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble*)data;

    glVertex3dv(ptr);

    // DEBUG //
//    ss << "  glVertex3d(" << *ptr << ", " << *(ptr+1) << ", " << *(ptr+2) << ");\n";
}



///////////////////////////////////////////////////////////////////////////////
// draw a vertex with color
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessVertexCB2(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble*)data;

    glColor3dv(ptr+3);
    glVertex3dv(ptr);

    // DEBUG //
//    ss << "  glColor3d(" << *(ptr+3) << ", " << *(ptr+4) << ", " << *(ptr+5) << ");\n";
//    ss << "  glVertex3d(" << *ptr << ", " << *(ptr+1) << ", " << *(ptr+2) << ");\n";
}



///////////////////////////////////////////////////////////////////////////////
// Combine callback is used to create a new vertex where edges intersect.
// In this function, copy the vertex data into local array and compute the
// color of the vertex. And send it back to tessellator, so tessellator pass it
// to vertex callback function.
//
// newVertex: the intersect point which tessellator creates for us
// neighborVertex[4]: 4 neighbor vertices to cause intersection (given from 3rd param of gluTessVertex()
// neighborWeight[4]: 4 interpolation weights of 4 neighbor vertices
// outData: the vertex data to return to tessellator
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData)
{
    // copy new intersect vertex to local array
    // Because newVertex is temporal and cannot be hold by tessellator until next
    // vertex callback called, it must be copied to the safe place in the app.
    // Once gluTessEndPolygon() called, then you can safly deallocate the array.
    vertices[vertexIndex][0] = newVertex[0];
    vertices[vertexIndex][1] = newVertex[1];
    vertices[vertexIndex][2] = newVertex[2];
#if 0
    // compute vertex color with given weights and colors of 4 neighbors
    // the neighborVertex[4] must hold required info, in this case, color.
    // neighborVertex was actually the third param of gluTessVertex() and is
    // passed into here to compute the color of the intersect vertex.
    vertices[vertexIndex][3] = neighborWeight[0] * neighborVertex[0][3] +   // red
                               neighborWeight[1] * neighborVertex[1][3] +
                               neighborWeight[2] * neighborVertex[2][3] +
                               neighborWeight[3] * neighborVertex[3][3];
    vertices[vertexIndex][4] = neighborWeight[0] * neighborVertex[0][4] +   // green
                               neighborWeight[1] * neighborVertex[1][4] +
                               neighborWeight[2] * neighborVertex[2][4] +
                               neighborWeight[3] * neighborVertex[3][4];
    vertices[vertexIndex][5] = neighborWeight[0] * neighborVertex[0][5] +   // blue
                               neighborWeight[1] * neighborVertex[1][5] +
                               neighborWeight[2] * neighborVertex[2][5] +
                               neighborWeight[3] * neighborVertex[3][5];
#endif

    // return output data (vertex coords and others)
    *outData = vertices[vertexIndex];   // assign the address of new intersect vertex

    ++vertexIndex;  // increase index for next vertex
}



void CALLBACK tessErrorCB(GLenum errorCode)
{
    const GLubyte *errorStr;

    errorStr = gluErrorString(errorCode);
    cerr << "[ERROR]: " << errorStr << endl;
}

#include "../../array/src/matrixes.h"

void Poligon3D::Drawing( )
{
	vertexIndex = 0;  
	//http://www.songho.ca/opengl/gl_tessellation.html

	if (m_pSurfDoc)
	{
		size_t len = this->GetPointsNumber();
		double d1[3],d2[3],norm[3];
#if 1
		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		if (m_pSurface)
			glPolygonMode(GL_FRONT_AND_BACK, m_pSurface->GetFillMode());
		else
			glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());




		GLUtesselator *tess = gluNewTess(); // create a tessellator
		if(!tess) return;  // failed to create tessellation object, return 0

		// define concave quad data (vertices only)
		//  0    2
		//  \ \/ /
		//   \3 /
		//    \/
		//    1
	    //GLdouble quad1[4][3] = { {-1,3,0}, {0,0,0}, {1,3,0}, {0,2,0} };

		GLdouble ** quad1 = Alloc2DMat<GLdouble>(len,3);
		for (size_t i = 0; i < len; i++)
		{
			quad1[i][0] = m_vvPoints[i].x;
			quad1[i][1] = m_vvPoints[i].y;
			quad1[i][2] = m_vvPoints[i].z;
		}

		// register callback functions
		gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
		gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
		gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
		gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);
		gluTessCallback(tess, GLU_TESS_COMBINE, (void (__stdcall*)(void))tessCombineCB);

		// tessellate and compile a concave quad into display list
		// gluTessVertex() takes 3 params: tess object, pointer to vertex coords,
		// and pointer to vertex data to be passed to vertex callback.
		// The second param is used only to perform tessellation, and the third
		// param is the actual vertex data to draw. It is usually same as the second
		// param, but It can be more than vertex coord, for example, color, normal
		// and UV coords which are needed for actual drawing.
		// Here, we are looking at only vertex coods, so the 2nd and 3rd params are
		// pointing same address.


		// Pay attention to winding rules if multiple contours are overlapped.
		// The winding rules determine which parts of polygon will be filled(interior)
		// or not filled(exterior). For each enclosed region partitioned by multiple
		// contours, tessellator assigns a winding number to the region by using
		// given winding rule. The default winding rule is GLU_TESS_WINDING_ODD,
		// but, here we are using non-zero winding rule to fill the middle area.
		// BTW, the middle region will not be filled with the odd winding rule.
		gluTessProperty(tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);

	    //glNewList(id, GL_COMPILE);
		if (m_pSurface && m_vdPoints.size())
		{
			COLORREF color = m_pSurface->GetColor(m_vdPoints[0].z);
			glColor4ub (GetRValue(color), GetGValue(color), GetBValue(color), (GLubyte)m_pSurface->m_alpha); 
		}
		else
		{
			glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha); 
		}
		gluTessBeginPolygon(tess, 0);                   // with NULL data
			gluTessBeginContour(tess);

			for (size_t i = 0; i < len; i++)
			{
				//====== Обход вершин осуществляется
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
				if (!(m_vvPoints[i].flag & CPOINT3_FLAG_NONORMAL))
				{
					d1[0] = m_vvPoints[i_minus_1].x-m_vvPoints[i].x;
					d1[1] = m_vvPoints[i_minus_1].y-m_vvPoints[i].y;
					d1[2] = m_vvPoints[i_minus_1].z-m_vvPoints[i].z;

					d2[0] = m_vvPoints[i].x-m_vvPoints[i_plus_1].x;
					d2[1] = m_vvPoints[i].y-m_vvPoints[i_plus_1].y;
					d2[2] = m_vvPoints[i].z-m_vvPoints[i_plus_1].z;

					getNorm(d1,d2,norm);
				}
				//if (m_vvPoints[i].bVisible)
				//{
					//====== Задание вектора нормали
					glNormal3dv (norm);
					gluTessVertex(tess, quad1[i], quad1[i]);

				//}
			}

        gluTessEndContour(tess);
		gluTessEndPolygon(tess);
		//glEndList();

		gluDeleteTess(tess);        // delete after tessellation

		Free2DMat(quad1);
#else
		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		if (m_pSurface)
			glPolygonMode(GL_FRONT_AND_BACK, m_pSurface->GetFillMode());
		else
			glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

		double d1[3],d2[3],norm[3];
		double norm_center[3];
			
		glBegin(GL_POLYGON);

		for (size_t i = 0; i < len; i++)
		{
			//====== Обход вершин осуществляется
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
			if (!(m_vvPoints[i].flag & CPOINT3_FLAG_NONORMAL))
			{
				d1[0] = m_vvPoints[i_minus_1].x-m_vvPoints[i].x;
				d1[1] = m_vvPoints[i_minus_1].y-m_vvPoints[i].y;
				d1[2] = m_vvPoints[i_minus_1].z-m_vvPoints[i].z;

				d2[0] = m_vvPoints[i].x-m_vvPoints[i_plus_1].x;
				d2[1] = m_vvPoints[i].y-m_vvPoints[i_plus_1].y;
				d2[2] = m_vvPoints[i].z-m_vvPoints[i_plus_1].z;

				getNorm(d1,d2,norm);
			}
			//====== Задание вектора нормали

			if (m_vvPoints[i].bVisible)
			{
				glNormal3dv (norm);
				if (m_pSurface)
				{
					COLORREF color = m_pSurface->GetColor(m_vdPoints[i].z);
					glColor4ub (GetRValue(color), GetGValue(color), GetBValue(color), (GLubyte)m_pSurface->m_alpha); 
				}
				else
				{
					glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha); 
				}
				glVertex3d (m_vvPoints[i].x, m_vvPoints[i].y, m_vvPoints[i].z);

			}
		}
		
		glEnd();

		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);

#endif
#if 0
		for (size_t i = 0; i < len; i++)
		{
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//====== Наносим цифровую метку
			char str[255];
            sprintf(str, "i = %d", i);
			// move 
			glRasterPos3d(m_vvPoints[i].x, m_vvPoints[i].y, m_vvPoints[i].z ); 
			// set up for a string-drawing display List call 
			// Display a string 
			glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
			// Draw the characters in a string 
			glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		glListBase(0);
#endif	


		if (Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
		{
			for (UINT i = 0; i < GetPointsNumber(); i++)
			{
				if(m_vvPoints[i].bVisible)
				{
					COLORREF sphereColor;
					double sphere_radius;
					if (m_vdPoints[i].flag & CPOINT3_FLAG_SELECTED
						||
						this->m_lParam & OBJECT_FLAG_SELECTED_BIT)
					{
						sphere_radius = m_pSurfDoc->m_sphere_radius;
						sphereColor = RGB(
							(255-GetRValue(m_color))/2,
							0/*(255-GetGValue(m_color))/2*/,
							(255-GetBValue(m_color))/2);
					}
					else
					{
						sphere_radius = m_pSurfDoc->m_sphere_radius;
						sphereColor = m_color;
					}
					if (!(m_vdPoints[i].flag & CPOINT3_FLAG_HIDE))
					{
						glColor3ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor)); 

						GLUquadricObj* pSphere = gluNewQuadric();
						gluQuadricDrawStyle(pSphere, GLU_FILL);
						glPushMatrix();//перейдём к новым координатам, сохранив старые
						
						glTranslated(
							m_vvPoints[i].x, 
							m_vvPoints[i].y, 
							m_vvPoints[i].z
							);

						gluSphere(pSphere, 
							sphere_radius, 
							m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
							m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
							) ;//рисуем сферу 
						glPopMatrix(); //возвращаемся к старым координатам 
						gluDeleteQuadric(pSphere);
					}
				}
			}
		}

	}
}


#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"
void Poligon3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{
	v->PreConvertingFromWorldToScreen();
	
	fGL x; fGL y;
	bool to_fill_circles = Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres
		||
		this->m_lParam & OBJECT_FLAG_SELECTED_BIT;
	
	fGL r = v->lines_points_radius;

	COLORREF color;
	if (this->m_lParam & OBJECT_FLAG_SELECTED_BIT)
	{
		color = RGB(
			(255-GetRValue(m_color))/2,
			0,
			(255-GetBValue(m_color))/2);
	}
	else
	{
		color = m_color;
	}

	Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
	Color gdi_color2(100, GetRValue(color),GetGValue(color),GetBValue(color));
	Pen      pen(gdi_color);

	double dist_to_plane;
	CPoint2 profile;

	PointF * points = new PointF[GetPointsNumber()];

	for (UINT i = 0; i < GetPointsNumber(); i++)
	{		
		//Convert3D_To_2D
		on->Projection(m_vdPoints[i], profile, dist_to_plane);	
		v->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);
		if (to_fill_circles && !(m_vdPoints[i].flag & CPOINT3_FLAG_HIDE)) 
			FillCircle(&graphics, x, y, r, gdi_color);			

		points[i] = PointF(x,y);
	}
	graphics.DrawPolygon(&pen, points, GetPointsNumber());
	// Create a SolidBrush object.
	SolidBrush brush(gdi_color2);
	graphics.FillPolygon(&brush, points, GetPointsNumber());//, FillModeAlternate,FillModeWinding

	delete[] points;
}

void Poligon3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "Poligon3D" , 0);
}

void Poligon3D::Init(const Poligon3D& ob)
{
	this->m_pSurface	= ob.m_pSurface;
	this->m_pSurfDoc	= ob.m_pSurfDoc;
	id_umpoz			= ob.id_umpoz;
}

Poligon3D::Poligon3D(const Poligon3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

Poligon3D& Poligon3D::operator=(const Poligon3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD Poligon3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, Poligon3D& ob)
{
//printf("Archive& operator <<(Archive& ar, Poligon3D& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);

	//DWORD old_primitive_version = ar.m_use_primitive_version;
	//ar.m_use_primitive_version = 3;
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	//ar.m_use_primitive_version = old_primitive_version;

	switch (version)
	{
	case 2:
		{
			ar << ob.id_umpoz;
		}
	case 1:
		{
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
Archive& operator >>(Archive& ar, Poligon3D& ob)
{
//printf("Archive& operator >>(Archive& ar, Poligon3D& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	ob.m_pSurface = NULL;
	switch (ob.m_object_version)
	{
	case 2:
		{
			ar >> ob.id_umpoz;
		}
	case 1:
		{
			ob.m_object_version = POLYGON_VERSION;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, Poligon3D& ob) end\n");
	return ar;
}

