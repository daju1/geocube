// Triangle3D.h: interface for the Triangle3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE3D_H__373701C1_B7F6_41B0_B6BB_5C59096C4851__INCLUDED_)
#define AFX_TRIANGLE3D_H__373701C1_B7F6_41B0_B6BB_5C59096C4851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"
class SurfDoc;

class Triangle3D : public Primitive3D <CPoint3>
{
	virtual void Drawing();
public:
	virtual void PropertiesDialog();
	void Init(Triangle3& tri, COLORREF color);

	Triangle3D();
	Triangle3D(SurfDoc * pSurfDoc);
	virtual ~Triangle3D();

	void Init(const Triangle3D& ob);
	Triangle3D(const Triangle3D& ob);
	Triangle3D& operator=(const Triangle3D& ob);

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
	friend Archive& operator <<(Archive& ar, Triangle3D& ob);
	friend Archive& operator >>(Archive& ar, Triangle3D& ob);
};

#endif // !defined(AFX_TRIANGLE3D_H__373701C1_B7F6_41B0_B6BB_5C59096C4851__INCLUDED_)
