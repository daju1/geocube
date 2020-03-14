#pragma once
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include "Object.h"
#include "ObjectList.h"
#endif
#include "points.h"
#include "ThePoint3D.h"
struct CubeSize;

class gdiplus_map_view;

class GridData;
class GridData : public Object
{
	bool m_to_draw_here;
	COLORREF m_color;
public:
	short z_flag;
	//not jet serialised
	short built;// 0 -was not built, 1 - was built, 2 - need to rebuild
	long griddata_fun_number;
	short griddata_app;//griddata_fun_class;/// = useSurfer;
	//not jet serialised




	long id_umpoz;
	long id_surf;
	long id_ige;
	BYTE podoshva;

	bool GrDtSaveToDB(BYTE podosva);
	int ClearFromDB(bool msg);
	int ClearPointFromDB(bool msg, long id_point);
	static size_t s_number_line_interpolated_points;
	static bool line_to_interpolate_points;
	static BOOL CALLBACK GridData::DlgProc( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK GridData::DlgProcGriddata(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	ThePoint3D * FindThePoint3D(long id_point);

	vect<ThePoint3D>	m_input_points;
	ObjectList			m_input_points_ObjectList;
	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual void Draw();
	virtual void ReDraw();
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer);
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();
	void Init(const GridData& bp)
	{			
		// Objects' vectors
		this->m_input_points				= bp.m_input_points;
		this->m_input_points_ObjectList.Init(this->m_input_points, this);
		this->m_color						= bp.m_color;
		this->m_to_draw_here				= bp.m_to_draw_here;

		this->id_surf						= bp.id_surf;
		this->id_umpoz						= bp.id_umpoz;

		this->id_ige						= bp.id_ige;
		this->podoshva						= bp.podoshva;

		this->built							= bp.built;
		this->griddata_fun_number			= bp.griddata_fun_number;
		this->griddata_app					= bp.griddata_app;/// = use_surfer;

		this->z_flag						= bp.z_flag;
	}
	bool SaveAs();
	bool SaveAsDat(FILE * stream)
	{
		return false;
	}
	bool SaveAsBln(FILE * stream)
	{
		return false;
	}

	bool IsSelectedGridDataPoint(gdiplus_map_view * gv, Profile3D * on, int mouse_x, int mouse_y, double & dist_to_line_object, WhatSelected& ws);

	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws);
	GridData& GridData::operator=(const GridData& bp);
	GridData(const GridData & bp);
	GridData(SurfDoc* pSurfDoc);
	GridData(void);
	virtual ~GridData(void);

	ThePoint3D * AddInput(CPoint3 &pt, COLORREF color);
	void AddInput(Primitive3D<CPoint3> * primitive);

	void AddLineToInput(Line3D * line);
	void AddLineToInput_with_interpolation(Line3D * line);
	void AddLineToInput_without_interpolation(Line3D * line);

	void AddDataFromDatFile();

	size_t GetPointsNumber(){return 0;}

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);


	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");


	void OnCreate(void);
	friend Archive& operator <<(Archive& ar, GridData& ob);
	friend Archive& operator >>(Archive& ar, GridData& ob);
	//bool griddata_by_surfer(void);
	bool griddata(void);
	bool griddata_old(void);
	bool griddata(CubeSize & cube_size);
	void FillContextMenu(HMENU& hMenu);

	void SetToDraw();
	void UnsetToDraw();

	virtual void SetName(string s);

	short DetermineRazlomZflag();
	void SetColorFromIGE();

};
struct Grid;
class griddata_dialog
{
public:
	enum griddata_application
	{
		unknown = 0,
		gstat_dll = 1,
		surfer_ole,
		this_app
	};
	bool may_quit_surfer;

	friend LRESULT CALLBACK GridData::DlgProcGriddata(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
private:

	
	HWND		hWnd;

	Grid           * m_grid; 
	vector<double> * m_pvx;
	vector<double> * m_pvy;
	vector<double> * m_pvz;

	bool & m_to_allocate;
	SurfDoc*	m_pSurfDoc;
	GridData*   m_pGridData;
	griddata_application m_griddata_application;
	GeoSurface * m_pGeoSurface;
	bool		m_do_loop;
	bool		m_unvisible;

	bool this_is_razlom;

	bool have_dat_file;

	char dat_path[4096];
	char grd_path[4096];

	char msk_path[4096];
	char eas_path[4096];
	char cmd_path[4096];
	char log_path[4096];
	char est_path[4096];
	char variogram_str[1024];

	//char eas_filename[1024];
	char dat_filename[1024];
	char grd_filename[1024];

	vector<double> VX, VY, VZ;// векторы для построения гридов

	void write_surfer_anscii_mask_file(short zflag);
	//void WriteTempCmd_001();
	void WriteTempCmd_002();
	bool ParseLog();
	void WriteTempCmd_003();
	void WriteTempEas();

	void WriteTempDat();
	void InitVectors();

	bool ApplyGstatDll();
	bool SurferGridData(HWND hDlg, short zflag);
	void LoadGrid(Grid * grid);


	void Start_my(HWND hDlg);
	void Start_surfer(HWND hDlg);	
	void Start_gstat(HWND hDlg);	

	void InitDialog_my(HWND hDlg);
	void InitDialog_surfer(HWND hDlg);	
	void InitDialog_gstat(HWND hDlg);	
	
	void RadioButtonHandler(HWND hDlg, int id_group, int id);
	void GridDataFunComboHandler(HWND hDlg);
	void OkButtonHandler_my(HWND hDlg, short zflag);
	void OkButtonHandler_surfer(HWND hDlg, short zflag);
	void OkButtonHandler_gstat(HWND hDlg);
public:



	void InitGriddataDialog(HWND hDlg, bool first_time);
	long griddata_fun_number;
	void OkButtonHandler(HWND hDlg);

	griddata_dialog(bool & to_allocate, SurfDoc *, GridData *, HWND , griddata_application grddt_app, GeoSurface * pGeoSurface, bool do_loop, bool unvisible
		, Grid * pgrid = NULL, vector<double> * pvx = NULL, vector<double> * pvy = NULL, vector<double> * pvz = NULL);
	virtual ~griddata_dialog(void);
	static string temp_directory;

};


