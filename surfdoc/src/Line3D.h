// Line3D.h: interface for the CLine3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE3D_H__10FF4F25_555D_45B2_A796_FC7F0F416DD6__INCLUDED_)
#define AFX_LINE3D_H__10FF4F25_555D_45B2_A796_FC7F0F416DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"

class SurfDoc;
class vdouble;
class BlnProfile3D;
class gdiplus_map_view;
class dimeModel;
class dimeBlock;
class CrdTranslator;

class Line3D  : public Primitive3D <CPoint3>
{
protected:
public:
	long id_ige;
	long id_umpoz;
	long id_surf;//идентификатор для зранения поверхности в базе
	// поскольку поверхность в базе может храниться толко в виде гриддаты
	// поэтому только гриддата может назначить id_surf отличный от -1
	BYTE podoshva;

	GLfloat m_LineWidth;
	virtual void PropertiesDialog();
	void SavingAsDatOrBln(FILE *fd, DWORD nFilterIndex = 0);
	bool SaveAsDxf(dimeModel * model, dimeBlock * block, CrdTranslator * translator);
	void AngleLocalMin(int n, double cos_boder);
	void Init(vdouble &x, vdouble &y, vdouble &z, COLORREF color);
	void Init(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color);
	Line3D();
	Line3D(SurfDoc * pSurfDoc);
	virtual ~Line3D();

	void Init(const Line3D& ob);
	Line3D(const Line3D& ob);
	Line3D& operator=(const Line3D& ob);
#ifdef _MSC_VER
	void Drawing(void);
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v , Profile3D * on, int alpha);
#endif
	void SavingAsRazrez(FILE *fd, 
		SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);

	bool SavingAsRazrez(dimeModel * model,  dimeBlock * block,  
		SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);

	int WhatSidesOfTwoPoint(short zflag, CPoint3& pt1, CPoint3& pt2);

	void OnCreate(void);

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Line3D& ob);
	friend Archive& operator >>(Archive& ar, Line3D& ob);
	bool GetLineLength(double& ans);
#ifdef _MSC_VER
	virtual bool IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws);

	bool IsSelectedDoc(CPoint3 selected_doc_pt, 
		double search_radius,
		double & dist_to_object,
		WhatSelected& ws);
		
	bool IsSelectedLine(gdiplus_map_view * gv, Profile3D * on, int mouse_x, int mouse_y, double & dist_to_line, WhatSelected& ws);
	bool FindIntersection(Profile3D * on, CPoint3 pt1, CPoint3 pt2, CPoint3 & pt3, int & i1, int & i2, int & unvisibles, int & dst_to_vis);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
#endif
	enum line3d_draw_mode {as_thing_lines = 10, as_lines_with_spheres = 20};
	static line3d_draw_mode s_line3d_draw_mode;
#ifdef _MSC_VER
	//void FreeMiddlePoints();
	void FillContextMenu(HMENU& hMenu);

	virtual void PrintfProperties(vector<fmtstr> & text);
	virtual void PrintfProperties(vector<LabData> & labdata);
#endif

};


#endif // !defined(AFX_LINE3D_H__10FF4F25_555D_45B2_A796_FC7F0F416DD6__INCLUDED_)
