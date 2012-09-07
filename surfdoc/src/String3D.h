// String3D.h: interface for the String3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRING3D_H__213CD39A_C8E5_49EB_B1C8_81BA683CC2D8__INCLUDED_)
#define AFX_STRING3D_H__213CD39A_C8E5_49EB_B1C8_81BA683CC2D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"

class SurfDoc;

class String3D : public Primitive3D <CPoint3>
{
	double m_vshift;//вертикальный сдвиг
	string str;
	virtual void Drawing();
public:
	virtual void PropertiesDialog();
	const char * GetString()
	{
		return str.c_str();
	}
	void Init(CPoint3 pt, char * s, COLORREF color, double vshift = 0.0);
	String3D::String3D();
	String3D(SurfDoc * pSurfDoc);
	virtual ~String3D();

	void Init(const String3D& ob);
	String3D(const String3D& ob);
	String3D& operator=(const String3D& ob);
	void OnCreate(void);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, String3D& ob);
	friend Archive& operator >>(Archive& ar, String3D& ob);
};

#endif // !defined(AFX_STRING3D_H__213CD39A_C8E5_49EB_B1C8_81BA683CC2D8__INCLUDED_)
