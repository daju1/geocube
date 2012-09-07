// String3D.cpp: implementation of the String3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "String3D.h"
//#include "raporto.h"
#include "SurfDoc.h"
#include ".\string3d.h"
#include "winsurftree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

String3D::String3D()
{
	m_pSurfDoc = 0;
	OnCreate();
}
String3D::String3D(SurfDoc * pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
void String3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::string3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
String3D::~String3D()
{

}

void String3D::Init(CPoint3 pt, char *s, COLORREF color, double vshift)
{
	Free();
	AllocPoints(1);
	m_vvPoints[0] = pt;
	m_vdPoints[0] = pt;
	str = s;
	m_vshift = vshift;
	m_color = color;
}

HTREEITEM String3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	if(this->GetPointsNumber())
	{
		CPoint3 pt = this->GetFirstDocumentPoint();
		sprintf(szItemText, "%f,%f,%f \"%s\"", 
			pt.x, pt.y, pt.z, this->GetString());
	}
	else
		sprintf(szItemText, "%s", this->GetString());
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
void String3D::Drawing()
{
	if (m_pSurfDoc)
	{	
		if (GetPointsNumber() > 0 && m_vvPoints[0].bVisible)
		{
			glColor3ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)); 
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//====== Наносим метку 
			// move 
			glRasterPos3d(m_vvPoints[0].x, m_vvPoints[0].y, m_vvPoints[0].z + m_vshift ); 
			// set up for a string-drawing display List call 
			// Display a string 
			glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
			// Draw the characters in a string 
			glCallLists(strlen(this->str.c_str()), GL_UNSIGNED_BYTE, this->str.c_str()); 
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
	}
}

void String3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "String3D" , 0);

}

void String3D::Init(const String3D& ob)
{
	this->m_pSurfDoc	= ob.m_pSurfDoc;
	this->m_vshift		= ob.m_vshift;
	this->str			= ob.str;//string
}

String3D::String3D(const String3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

String3D& String3D::operator=(const String3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD String3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, String3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (version)
	{
	case 1:
		{
			ar << ob.m_vshift;
			ar << ob.str;
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
Archive& operator >>(Archive& ar, String3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_vshift;
			ar >> ob.str;
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

