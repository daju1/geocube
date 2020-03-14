#pragma once
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include "Object.h"
#include "ObjectList.h"
#endif
#include "GeoSurface.h"
#include "ThePoint3D.h"

class GeoCatch : public Object
{
	friend class SurfDoc;
	// шаг сетки или число делений
	long N;
public:
	vect<GeoSurface>	m_surfaces;
	ObjectList			m_surfaces_ObjectList;

	vect<GeoSurface>	m_faults;
	ObjectList			m_faults_ObjectList;

	vect<GeoSurface>	m_gorizont_planes;
	ObjectList			m_gorizont_planes_ObjectList;

	vect<ThePoint3D>	m_base_points;
	ObjectList			m_base_points_ObjectList;


	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	void Cut(double a, double b, double c, double d, 
		bool toDrawPoligones, bool positive, 
		short type_of_cutline, int cutting_number, 
		CPoint2* pt1, CPoint2* pt2 , void * pBrokenPlane);

	void SavingAsRazrez_of_CutPlaneLines(FILE *fd, SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);

	bool SavingAsRazrez_of_CutPlaneLines(dimeModel * model,  dimeBlock * block, SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);

	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	void DrawCutPlaneLines();

	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void ZoomViewCutlinesPolygones(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();

	void Init(const GeoCatch& bp)
	{			
		this->m_surfaces				= bp.m_surfaces;
		this->m_surfaces_ObjectList.Init(this->m_surfaces, this);

		this->m_faults					= bp.m_faults;
		this->m_faults_ObjectList.Init(this->m_faults, this);

		this->m_gorizont_planes			= bp.m_gorizont_planes;
		this->m_gorizont_planes_ObjectList.Init(this->m_gorizont_planes, this);

		this->m_base_points				= bp.m_base_points;
		this->m_base_points_ObjectList.Init(this->m_base_points, this);
	}
	bool SaveAs()
	{
		return false;
	}
	bool SaveAsDat(FILE * stream)
	{
		return false;
	}
	bool SaveAsBln(FILE * stream)
	{
		return false;
	}
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws);

	GeoCatch& GeoCatch::operator=(const GeoCatch& bp);

	GeoCatch();
	GeoCatch(const GeoCatch & bp);
	GeoCatch(SurfDoc* pSurfDoc);
	virtual ~GeoCatch();

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	void OnCreate(void);
	void ClearCutlinesPolygones();
	void Blank(Line3D& blankline, bool to_continue_line_to_borders, CPoint3 * base_point);
		
	size_t GetPointsNumber(){return 0;}

	// добавляем горизонтальную плоскость (ГНК, ГВК или НВК) в объект ловушки - на основании базовой точки, принадлежащей поверхности искомого горизонтального контакта
	bool InitGorizontPlane(CPoint3& base_point);

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, GeoCatch& ob);
	friend Archive& operator >>(Archive& ar, GeoCatch& ob);
	bool BlankLastGorizontPlane(void);
	void BlankingOfGorizontPlaneBlankLines(void);
};
