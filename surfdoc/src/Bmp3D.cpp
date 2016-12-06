// Bmp3D.cpp: implementation of the Bmp3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bmp3D.h"
#include "..\..\array\src\vdouble.h"
#include "SurfDoc.h"
#include "..\..\tools\src\filedlg.h"
#include  "texture.h"
#include "winsurftree.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern GLuint	texture[];			// Storage For One Texture ( NEW )

/*AUX_RGBImageRec * Bmp3D::LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}*/
bool Bmp3D::LoadGLTexture()									// Load Bitmaps And Convert To Textures
{
	bool Status=false;									// Status Indicator
	char filename[1024];
	if (OpenFileDlg(NULL, "JPEG (*.jpg)\0*.jpg\0Bitmap (*.bmp)\0*.bmp\0All files \0*.*\0", filename) == S_OK)
	{
		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (UploadImage ( filename, texture[0], &sizeX, &sizeY ))
		//if (image=LoadBMP(filename))
		{
			Status=true;									// Set The Status To TRUE

			//glGenTextures(1, &texture[0]);					// Create The Texture

			// Typical Texture Generation Using Data From The Bitmap

			//glBindTexture(GL_TEXTURE_2D, texture[0]);

			// Изменение размеров текстуры проводится с помощью команды
			// void gluScaleImage(GLenum format, GLint widthin, GL heightin, GLenum typein, const void *datain, GLint widthout, GLint heightout, GLenum typeout, void *dataout)
			
			//В качестве значения параметра format обычно используется значение 
			//GL_RGB или GL_RGBA, определяющее формат хранения информации. 
			//Параметры widthin, heightin, widhtout, heightout определяют 
			//размеры входного и выходного изображений, а с помощью typein 
			//и typeout задается тип элементов массивов, расположенных по 
			//адресам datain и dataout. Как и обычно, то может быть тип
			//GL_UNSIGNED_BYTE, GL_SHORT, GL_INT и так далее. Результат 
			//своей работы функция заносит в область памяти, на которую 
			//указывает параметр dataout.
/*

#if 0
			// Изменение размеров текстуры проводится с помощью команды
			// void gluScaleImage(GLenum format, GLint widthin, GL heightin, GLenum typein, const void *datain, GLint widthout, GLint heightout, GLenum typeout, void *dataout)
	
			AUX_RGBImageRec* image2;
			image2 = new AUX_RGBImageRec;
			image2->sizeX = 2048;
			image2->sizeY = 2048;
			image2->data = (unsigned char*) malloc(3*sizeof(unsigned char)*
				image2->sizeX*image2->sizeY);


			gluScaleImage(
				GL_RGB, 
				image->sizeX, image->sizeY, 
				GL_UNSIGNED_BYTE, image->data, 
				image2->sizeX, image2->sizeY, 
				GL_UNSIGNED_BYTE, image2->data);

			//В качестве значения параметра format обычно используется значение 
			//GL_RGB или GL_RGBA, определяющее формат хранения информации. 
			//Параметры widthin, heightin, widhtout, heightout определяют 
			//размеры входного и выходного изображений, а с помощью typein 
			//и typeout задается тип элементов массивов, расположенных по 
			//адресам datain и dataout. Как и обычно, то может быть тип
			//GL_UNSIGNED_BYTE, GL_SHORT, GL_INT и так далее. Результат 
			//своей работы функция заносит в область памяти, на которую 
			//указывает параметр dataout.



			glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				image2->sizeX, image2->sizeY, 
				0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);
#else
			//генерирует текстуры всех уровней детализации. 
			//Также эта функция не требует, чтобы размер изображения 
			//был кратен степени двойки. Она сама сожмет/растянет изображение 
			//подходящим образом, хотя возможно окажется, что и не вполне подходящим.
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
                  image->sizeX,
                  image->sizeY,
                  GL_RGB, GL_UNSIGNED_BYTE,
                  image->data);
#endif
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
*/		
			Free();
			AllocPoints(4);

			CPoint3 pt;
			// складываем данные в документ
			pt.x = 0;
			pt.y = 0;
			pt.z = 0;
			pt.bVisible = true;
			m_vdPoints[0] = pt;
			m_vvPoints[0] = pt;

			// складываем данные в документ
			pt.x = sizeX;
			pt.y = 0;
			pt.z = 0;
			pt.bVisible = true;
			m_vdPoints[1] = pt;
			m_vvPoints[1] = pt;

			// складываем данные в документ
			pt.x = sizeX;
			pt.y = sizeY;
			pt.z = 0;
			pt.bVisible = true;
			m_vdPoints[2] = pt;
			m_vvPoints[2] = pt;

			// складываем данные в документ
			pt.x = 0;
			pt.y = sizeY;
			pt.z = 0;
			pt.bVisible = true;
			m_vdPoints[3] = pt;
			m_vvPoints[3] = pt;

/*
			if (image)									// If Texture Exists
			{
				if (image->data)							// If Texture Image Exists
				{
					free(image->data);					// Free The Texture Image Memory
				}

				free(image);								// Free The Image Structure
			}*/
		}
	}

	return Status;										// Return The Status
}


 
bool Bmp3D::LoadGLTexture(char * filename, vector<double> &xMap, vector<double> &yMap, double z)									// Load Bitmaps And Convert To Textures
{
	printf("Bmp3D::LoadGLTexture\n");
	bool Status=false;									// Status Indicator
	if (xMap.size() == yMap.size() && xMap.size() == 2)
	{
		printf("Bmp3D::LoadGLTexture filename = %s\n", filename);
		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (UploadImage ( filename, texture[0] , &sizeX, &sizeY ))
		{
			Status=true;									// Set The Status To TRUE

			Free();
			AllocPoints(4);

			CPoint3 pt;
			// складываем данные в документ
			// letf and bottom of picture
			pt.x = xMap[0];//left
			pt.y = yMap[0];//bottom
			pt.z = z;
			pt.bVisible = true;
			m_vdPoints[0] = pt;
			m_vvPoints[0] = pt;
printf("0 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);
			// складываем данные в документ
			// right and bottom of picture
			pt.x = xMap[1];//right
			pt.y = yMap[0];//bottom
			pt.z = z;
			pt.bVisible = true;
			m_vdPoints[1] = pt;
			m_vvPoints[1] = pt;
printf("1 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);

			// складываем данные в документ
			// right and top of texture
			pt.x = xMap[1];//right
			pt.y = yMap[1];//top
			pt.z = z;
			pt.bVisible = true;
			m_vdPoints[2] = pt;
			m_vvPoints[2] = pt;
printf("2 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);

			// складываем данные в документ
			// left and top of picture
			pt.x = xMap[0];//left
			pt.y = yMap[1];//top
			pt.z = z;
			pt.bVisible = true;
			m_vdPoints[3] = pt;
			m_vvPoints[3] = pt;
printf("3 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);
		}
	}
	return Status;										// Return The Status
}


bool Bmp3D::LoadGLTexture(char * filename, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile)									// Load Bitmaps And Convert To Textures
{
	printf("Bmp3D::LoadGLTexture\n");
	bool Status=false;									// Status Indicator
	if (xMap.size() == yMap.size() && xMap.size() == zProfile.size() && xMap.size() == 2)
	{
		printf("Bmp3D::LoadGLTexture filename = %s\n", filename);
		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (UploadImage ( filename, texture[0] , &sizeX, &sizeY ))
		{
			Status=true;									// Set The Status To TRUE

			Free();
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
printf("3 pt.x = %f pt.y = %f pt.z = %f\n", pt.x, pt.y, pt.z);
		}
	}
	return Status;										// Return The Status
}


Bmp3D::Bmp3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
Bmp3D::Bmp3D(SurfDoc * pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
void Bmp3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::bmp3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
Bmp3D::~Bmp3D()
{

}
HTREEITEM Bmp3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
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

void Bmp3D::Drawing()
{
	if (m_pSurfDoc)
	{

#if 0
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);

		m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glRasterPos2d(-4.5,-3);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelZoom(1.0, 1.0);
		glDrawPixels(image->sizeX, image->sizeY, 
			GL_RGB, GL_UNSIGNED_BYTE,
			image->data);
		glEndList();
#else
		//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
		//====== Установка режима заполнения
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
			d1[0] = m_vvPoints[i_minus_1].x-m_vvPoints[i].x;
			d1[1] = m_vvPoints[i_minus_1].y-m_vvPoints[i].y;
			d1[2] = m_vvPoints[i_minus_1].z-m_vvPoints[i].z;

			d2[0] = m_vvPoints[i].x-m_vvPoints[i_plus_1].x;
			d2[1] = m_vvPoints[i].y-m_vvPoints[i_plus_1].y;
			d2[2] = m_vvPoints[i].z-m_vvPoints[i_plus_1].z;

			getNorm(d1,d2,norm);
			//====== Задание вектора нормали

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
		//glEndList();
#endif
	}
}


void Bmp3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "Bmp3D" , 0);
}

void Bmp3D::Init(const Bmp3D& ob)
{
	this->m_pSurfDoc = ob.m_pSurfDoc;
}

Bmp3D::Bmp3D(const Bmp3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

Bmp3D& Bmp3D::operator=(const Bmp3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD Bmp3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, Bmp3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (version)
	{
	case 1:
		{
			ar << ob.sizeX;
			ar << ob.sizeY;
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
Archive& operator >>(Archive& ar, Bmp3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.sizeX;
			ar >> ob.sizeY;
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

