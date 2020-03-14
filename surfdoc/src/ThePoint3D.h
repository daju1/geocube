// ThePoint3D.h: interface for the ThePoint3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THEPOINT3D_H__BBD9DE68_2E5E_4DD2_9508_393C122718C8__INCLUDED_)
#define AFX_THEPOINT3D_H__BBD9DE68_2E5E_4DD2_9508_393C122718C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"

class SurfDoc;

class ThePoint3D  : public Primitive3D <CPoint3>
{
	void Drawing();
protected:
	void Init(const ThePoint3D& ob);
public:
	long id_point; //идентификатор точки при сохранения гриддаты в базу
	void Init(SurfDoc * pSurfDoc, CPoint3 pt);
	virtual void PropertiesDialog();
	ThePoint3D();
	ThePoint3D(SurfDoc * pSurfDoc);
	virtual ~ThePoint3D();

	void OnCreate(void);

	ThePoint3D(const ThePoint3D& ob);
	ThePoint3D& operator=(const ThePoint3D& ob);

	bool OnProfile(Profile3D * on);
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);


	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s);
#endif
	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, ThePoint3D& ob);
	friend Archive& operator >>(Archive& ar, ThePoint3D& ob);
	static GLfloat point_size;
};

#endif // !defined(AFX_THEPOINT3D_H__BBD9DE68_2E5E_4DD2_9508_393C122718C8__INCLUDED_)
