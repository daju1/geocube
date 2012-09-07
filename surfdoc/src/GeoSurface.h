#pragma once
#include "object.h"
#include "objectList.h"
#include "points.h"
#include "Line3D.h"
#include "Poligon3D.h"
#include "Surface3D.h"
#include "Grid.h"

#define SURFACE_ORDER_LIST_ITEM_VERSION 1
#define SURFACE_BLANK_ORDER_LIST_ITEM_VERSION 1
#define SURFACE_BLANK_FUNCTIONS_LIST_ITEM_VERSION 1

struct surface_order_list_item
{
	DWORD version;
	bool check;
	long id_surf;
	BYTE podoshva;
//		long id_ige;
//		string ige;
	string my_name;
	bool check2;
	Grid * grid;// грид подошвы геоэлемента

	surface_order_list_item()
	{
		version = SURFACE_ORDER_LIST_ITEM_VERSION;
		check = false;
		id_surf = -1;
		my_name = "";
		podoshva = 0;
//			id_ige = -1;
//			ige = "";
		check2 = false;
		grid = NULL;

	}
	surface_order_list_item(bool _check, long _id_surf, BYTE _podoshva, 
		//long _id_ige, string _ige, 
		string name)
	{
		version = SURFACE_ORDER_LIST_ITEM_VERSION;
		check = _check;
		id_surf = _id_surf;
		podoshva = _podoshva;
//			id_ige = _id_ige;
//			ige = _ige;
		my_name = name;
		check2 = false;
		grid = NULL;
	}
	void Serialize(Archive& ar);

	friend Archive& operator <<(Archive& ar, surface_order_list_item * ob);
	friend Archive& operator >>(Archive& ar, surface_order_list_item *& ob);
};

struct surface_blank_functions_list_item
{
	DWORD version;
	//long id_item;
	long id_surf_obj;
	long id_surf_param;
	BYTE id_blank_fun;

	string name_surf_obj;
	string name_surf_param;

	surface_blank_functions_list_item()
	{
		version = SURFACE_BLANK_FUNCTIONS_LIST_ITEM_VERSION;
		//id_item = -1;
		id_surf_obj = -1;
		id_surf_param = -1;
		id_blank_fun = 0;
		name_surf_obj = "";
		name_surf_param = "";
	}

	surface_blank_functions_list_item(/*long _id_item,*/ long _id_surf_obj, long _id_surf_param, BYTE _id_blank_fun)
	{
		version = SURFACE_BLANK_FUNCTIONS_LIST_ITEM_VERSION;
		
		//id_item = _id_item;
		id_surf_obj = _id_surf_obj;
		id_surf_param = _id_surf_param;
		id_blank_fun = _id_blank_fun;
		name_surf_obj = "";
		name_surf_param = "";
	}
	void Serialize(Archive& ar);

	friend Archive& operator <<(Archive& ar, surface_blank_functions_list_item * ob);
	friend Archive& operator >>(Archive& ar, surface_blank_functions_list_item *& ob);


	static std::string get_blank_function_name(long id)
	{
		switch (id)
		{
		case 1:
			return "BlankAbove";
		case 2:
			return "BlankUnder";
		}
		return "";
	}
};






struct surface_blank_order_list_item
{
	DWORD version;
	//бланковать ли меня вообще
	bool check_blank_me;
	//бланковать ли меня, продвигаясь вверх по списку
	bool check_blank_me_up;
	//при бланковании вверх отрезать ли то что выше опорных гридов, иначе отрезать то что ниже
	bool check_blank_me_up_above;
	
	//бланковать ли меня, продвигаясь вниз по списку
	bool check_blank_me_down;
	//при бланковании вниз отрезать ли то что выше опорных гридов, иначе отрезать то что ниже
	bool check_blank_me_down_above;

	// бланковать ли с помощью меня другие гриды, бланкующиеся вверх
	bool check_blank_by_me_up;

	// бланковать ли с помощью меня другие гриды, бланкующиеся вниз
	bool check_blank_by_me_down;

	long id_surf;
	BYTE podoshva;
	string my_name;

	surface_blank_order_list_item()
	{
		version = SURFACE_BLANK_ORDER_LIST_ITEM_VERSION;

		//бланковать ли меня вообще
		check_blank_me = true;
		//бланковать ли меня, продвигаясь вверх по списку
		check_blank_me_up = true;
		//при бланковании вверх отрезать ли то что выше опорных гридов, иначе отрезать то что ниже
		check_blank_me_up_above = true;
		
		//бланковать ли меня, продвигаясь вниз по списку
		check_blank_me_down = false;
		//при бланковании вниз отрезать ли то что выше опорных гридов, иначе отрезать то что ниже
		check_blank_me_down_above = false;

		// бланковать ли с помощью меня другие гриды, бланкующиеся вверх
		check_blank_by_me_up = true;
		// бланковать ли с помощью меня другие гриды, бланкующиеся вниз
		check_blank_by_me_down = false;

		id_surf = -1;
		podoshva = 0;
		my_name = "";
	}

	surface_blank_order_list_item(long _id_surf, BYTE _podoshva, string name)
	{
		version = SURFACE_BLANK_ORDER_LIST_ITEM_VERSION;

		//бланковать ли меня вообще
		check_blank_me = true;
		//бланковать ли меня, продвигаясь вверх по списку
		check_blank_me_up = true;
		//при бланковании вверх отрезать ли то что выше опорных гридов, иначе отрезать то что ниже
		check_blank_me_up_above = true;
		
		//бланковать ли меня, продвигаясь вниз по списку
		check_blank_me_down = false;
		//при бланковании вниз отрезать ли то что выше опорных гридов, иначе отрезать то что ниже
		check_blank_me_down_above = false;

		// бланковать ли с помощью меня другие гриды, бланкующиеся вверх
		check_blank_by_me_up = true;
		// бланковать ли с помощью меня другие гриды, бланкующиеся вниз
		check_blank_by_me_down = false;


		id_surf = _id_surf;
		podoshva = _podoshva;
		my_name = name;
	}
	void Serialize(Archive& ar);

	friend Archive& operator <<(Archive& ar, surface_blank_order_list_item * ob);
	friend Archive& operator >>(Archive& ar, surface_blank_order_list_item *& ob);
};






class GeoSurface :	public Object
{
	friend class SurfDoc;
public:
	long id_ige;
	long id_umpoz;
	long id_surf;//идентификатор для зранения поверхности в базе
	// поскольку поверхность в базе может храниться толко в виде гриддаты
	// поэтому только гриддата может назначить id_surf отличный от -1
	BYTE podoshva;
	int ClearFromDB(bool msg);
	void ClearFromOrderLists();

	void SetPodoshva(BYTE p);




	Surface3D		m_surface;
	// граничная линия при бланковании
	vect<Line3D>	m_blank_lines;
	ObjectList		m_blank_lines_ObjectList;
	// линия сечения плоскостью
	vect<Line3D>	m_cutplane_lines;
	ObjectList		m_cutplane_lines_ObjectList;
	//изолинии
	vect<Line3D>	m_izo_lines;
	ObjectList		m_izo_lines_ObjectList;

	// линии пересечения с разломами или другими поверхностями
	vector<Vertex> m_vertices;
	vector<Trace> m_traces;
	bool MakeFaultSection(LPSURFER7FAULTSECTION faultSection);

	vect<Line3D>	m_cutFault_lines;
	ObjectList		m_cutFault_lines_ObjectList;

	//полигоны украшающие кромку сечения плоскостью
	vect<Poligon3D>	m_cutplane_polygones;
	ObjectList		m_cutplane_polygones_ObjectList;

	//полигоны украшающие кромку обрезания граничной линией при бланковании
	vect<Poligon3D>	m_blank_polygones;
	ObjectList		m_blank_polygones_ObjectList;

	std::vector<std::vector<Poligon3D *> > m_blank_polygon_matrix;
	ObjectList		m_blank_polygon_matrix_ObjectList;

	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	void SavingAsRazrez_of_CutPlaneLines(FILE *fd,
		SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);
	bool SavingAsRazrez_of_CutPlaneLines(dimeModel * model,  dimeBlock * block,
		SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);

	void DrawBlankLines();
	void DrawIzoLines();
	void DrawCutFaultLines();
	void DrawCutPlaneLines();
	void DrawBlankPolygones();
	void DrawCutPolygones();
	virtual void Draw();

	void ReDrawBlankLines();
	void ReDrawIzoLines();
	void ReDrawCutFaultLines();
	void ReDrawCutPlaneLines();
	void ReDrawBlankPolygones();
	void ReDrawCutPolygones();
	virtual void ReDraw();
	virtual void ReDrawWithoutTree();

	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );

	void SetLayer(const Layer* layer);

	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void ZoomViewCutlinesPolygones(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void ClearCutlinesPolygones();
	virtual bool UpdateExtremums();

	void Init(long id_surf, BYTE podoshva, long id_ige, short zflag, Grid * pgrid, COLORREF color);

	void Init(const GeoSurface& bp)
	{			
		this->m_surface					= bp.m_surface;
		this->m_surface.SetParent(this);
		// Objects' vectors
		this->m_blank_lines				= bp.m_blank_lines;
		this->m_blank_lines_ObjectList.Init(this->m_blank_lines, this);

		this->m_izo_lines				= bp.m_izo_lines;
		this->m_izo_lines_ObjectList.Init(this->m_izo_lines, this);

		this->m_cutFault_lines				= bp.m_cutFault_lines;
		this->m_cutFault_lines_ObjectList.Init(this->m_cutFault_lines, this);

		this->m_cutplane_lines			= bp.m_cutplane_lines;
		this->m_cutplane_lines_ObjectList.Init(this->m_cutplane_lines, this);

		this->m_cutplane_polygones			= bp.m_cutplane_polygones;
		this->m_cutplane_polygones_ObjectList.Init(this->m_cutplane_polygones, this);

		this->m_blank_polygones			= bp.m_blank_polygones;
		this->m_blank_polygones_ObjectList.Init(this->m_blank_polygones, this);

		this->m_blank_polygon_matrix	= bp.m_blank_polygon_matrix;
		this->m_blank_polygon_matrix_ObjectList.Init2_std_vector_std_vector_ptr(this->m_blank_polygon_matrix, this);

		this->m_traces					= bp.m_traces;
		this->m_vertices				= bp.m_vertices;

		this->id_umpoz					= bp.id_umpoz;
		this->id_surf					= bp.id_surf;
		this->podoshva					= bp.podoshva;
		this->id_ige					= bp.id_ige;
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
	GeoSurface& GeoSurface::operator=(const GeoSurface& bp);

	GeoSurface();
	GeoSurface(const GeoSurface & bp);
	GeoSurface(SurfDoc* pSurfDoc);
	virtual ~GeoSurface();

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);

	void AddBlankLinesItem(HWND hwndTV, HTREEITEM h2);
	void AddIzoLinesItem(HWND hwndTV, HTREEITEM h2);
	void AddCutFaultLinesItem(HWND hwndTV, HTREEITEM h2);
	void AddCatPlaneLinesItem(HWND hwndTV, HTREEITEM h2);
	void AddCutPlanePolygonesItem(HWND hwndTV, HTREEITEM h2);
	void AddBlankPolygonesItem(HWND hwndTV, HTREEITEM h2);

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	void OnCreate(void);
	void AddIzoLine(CPoint3* pts, int len, COLORREF color );
	void AddCutFaultLine(CPoint3* pts, int len, COLORREF color );
	void AddCutPlaneLine(CPoint3* pts, int len, COLORREF color );
	bool ProjectBlankLinesOnSurface();
	void BlankWithOwnBlankLines(bool toPresetAllVisible, bool to_continue_line_to_borders, CPoint3 * base_point);
	void BlankingOfBlankLines(CPoint3 * base_point, CPoint3& ptMax, CPoint3& ptMin);

	void MakeQuadBlankPolygons(
		vector<blank_polygon_point>& blank_polygon_points);


	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, GeoSurface& ob);
	friend Archive& operator >>(Archive& ar, GeoSurface& ob);

	void FillContextMenu(HMENU& hMenu);

	bool SetColorFromCurrentWellsSloj();


	bool BlankAbove(GeoSurface & geo_surf);
	bool BlankUnder(GeoSurface & geo_surf);

	bool Blank();
	bool BlankOnBasePoint(CPoint3& base_point);
	void BlankWithOwnCutlines();
	void BlankWithOwnCutlinesOnBasePoint(CPoint3& base_point);
	void CopyCutlinesToBlankLines();
	void CopyCutPlaneLinesToBlankLines();

	bool RebuildByGridData();
	virtual void SetName(string s);


	bool Izolines();
	bool izolines();

	void ClearBlankPolygonMatrix();

	bool NoBlank();
	bool LoadBlankBln(void);
	void AddBlankLine(int inside);
	void AddBlankLine(int inside, Line3D &line);
	void AddBlankLine(int inside, CPoint3* pts, int len, COLORREF color );

	void ClearBlankLines();
	void BuildSurfacesCutlines(void);
	void SaveAsSurfer7Grid();
	bool SaveBlankLines();

	static vector<surface_order_list_item *> surface_order_list;
	static vector<surface_blank_order_list_item *> surface_blank_order_list;
	static vector<surface_blank_functions_list_item *> surface_blank_functions_list;

	static bool s_bInverse_order_in_the_tree;

	virtual void PrintfProperties(vector<fmtstr> & text);
	virtual void PrintfProperties(vector<LabData> & labdata);

};
