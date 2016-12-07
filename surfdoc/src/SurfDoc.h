#if !defined(AFX_SURFDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_)
#define AFX_SURFDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_

#include "grid.h"


#include "../../commonOG.h"
#include "palette.h"
#include "..\..\array\src\sorting.h"
#include "..\..\wintools\src\listfun.h"
#include "..\..\array\src\vect.h"


#include "DrawListArray.h"
#include "ThePoint3D.h"
#include "Line3D.h"
#include "Poligon3D.h"
#include "Surface3D.h"
#include "GeoSurface.h"
#include ".\geocatch.h"
#include "Well_3D.h"
#include "String3D.h"
#include "BrokenPlane3D.h"
#include "Sphere3D.h"
#include "Triangle3D.h"
#include "TriangulatedGrid3D.h"
#include "BlnProfile3D.h"
#include "GridProfile3D.h"
#include "Bmp3D.h"
#include "BmpProfile3D.h"
#include "../../surfdefs.h"
#include ".\griddata.h"
#include ".\collection.h"
#include ".\autoprofilebuilding.h"
#include ".\fastcollection.h"
#include ".\cube.h"
#include ".\GeoElement.h"
#include "BuroNabivSvaj.h"


#include "layer.h"
#include "../../laboratory/src/lab.h"

#include "../../tools/src/listviewtab.h"


#define USE_LISTVIEW_STANDART_LL 1
#if USE_LISTVIEW_STANDART_LL
#define ListViewTabLL ListViewTab
#else
#define ListViewTabLL ListViewTab2
#endif


#define USE_LISTVIEW_STANDART_KL 0
#if USE_LISTVIEW_STANDART_KL
#define ListViewTabKL ListViewTab
#else
#define ListViewTabKL ListViewTab2
#endif

#define USE_LISTVIEW_STANDART_WDL 0
#if USE_LISTVIEW_STANDART_WDL
#define ListViewTabWDL ListViewTab
#else
#define ListViewTabWDL ListViewTab2
#endif

#define USE_LISTVIEW_STANDART_SO 0
#if USE_LISTVIEW_STANDART_SO
#define ListViewTabSO ListViewTab
#else
#define ListViewTabSO ListViewTab2
#endif

#define USE_LISTVIEW_STANDART_SBO 0
#if USE_LISTVIEW_STANDART_SBO
#define ListViewTabSBO ListViewTab
#else
#define ListViewTabSBO ListViewTab2
#endif


#define USE_LISTVIEW_STANDART_SBF 1
#if USE_LISTVIEW_STANDART_SBF
#define ListViewTabSBF ListViewTab
#else
#define ListViewTabSBF ListViewTab2
#endif


#define USE_LISTVIEW_STANDART_SLM 0
#if USE_LISTVIEW_STANDART_SLM
#define ListViewTabSLM ListViewTab
#else
#define ListViewTabSLM ListViewTab2
#endif

#define USE_LISTVIEW_STANDART_SEGM 0
#if USE_LISTVIEW_STANDART_SEGM
#define ListViewTabSEGM ListViewTab
#else
#define ListViewTabSEGM ListViewTab2
#endif


#define USE_LISTVIEW_STANDART_LLL 1
#if USE_LISTVIEW_STANDART_LLL
#define ListViewTabLLL ListViewTab
#else
#define ListViewTabLLL ListViewTab2
#endif

#define USE_LISTVIEW_STANDART_LEL 1
#if USE_LISTVIEW_STANDART_LEL
#define ListViewTabLEL ListViewTab
#else
#define ListViewTabLEL ListViewTab2
#endif


#define USE_LISTVIEW_STANDART_LXL 1
#if USE_LISTVIEW_STANDART_LXL
#define ListViewTabLXL ListViewTab
#else
#define ListViewTabLXL ListViewTab2
#endif


#define USE_LISTVIEW_STANDART_WSL 1
#if USE_LISTVIEW_STANDART_WSL
#define ListViewTabWSL ListViewTab
#else
#define ListViewTabWSL ListViewTab2
#endif

//#if DFX_LAYER_FROM_OBJECT
#include <dime/convert/convert.h>
//#endif

#include <map>
using namespace std ;

struct TData3D
{
	//===== Порядок в нормализованном представлении числа
	int Power;
	//===== Флаг оси X
	int axesFlag;
	double
		//======= Экстремумы
		Min, Max,
		//======= Множитель (10 в степени Power)
		Factor,
		//======= Шаг вдоль оси (мантисса)
		Step,
		//======= Реальный шаг
		dStep,
		//======= Первая и последняя координаты (мантиссы)
		Start, End,
		//======= Первая и последняя координаты
		dStart, dEnd;
};

class CGrid;

class CLabDoc;
#define USE_SURF_IGE_MAPPING 1
class SurfDoc : public Object
{
protected:
	CLabDoc * m_pLabDoc;
	long id_obj;

public:
	void Set_ID_OBJ(long id){id_obj = id;}
	long Get_ID_OBJ(){return id_obj;}
	CLabDoc * GetLabDoc() const {return  m_pLabDoc;}
	bool SaveGriddataToDB();
	bool SaveZoomToDB();
	bool SaveCubeSizeToDB();
	bool UndefineCubeSizeInDB();

	static SSaveProfData sprData;
	void InitLabDoc(CLabDoc * pLabDoc){m_pLabDoc = pLabDoc;}

	string current_filename;
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = NULL){return NULL;}

	// набор колонок гео элементов в документе
	map<GeoElement::type, GeoColomn>	m_geo_colomns;
	ObjectList							m_geo_colomns_ObjectList;

	GeoColomn * AddNewGeoColomn(GeoElement::type t);
	GeoColomn * AddGeoColomn(GeoElement::type t);
	GeoColomn * FindGeoColomn(GeoElement::type t);

	void ClearGeoColomns();

	CubeSize m_cube_size;

	Cube4D * AddGeoCube(bool full_geo_cube_filling, 
		EngineerGeoElement::ValueType value_type, 	
		EngineerGeoElement::GroundDescriptionType ground_description_type,
		EngineerGeoElement::StrengthDescriptionType strength_description_type);

	Cube4D * AddingGeoCube(bool full_geo_cube_filling, 
		vector<key_grid> & kgs, 
		EngineerGeoElement::ValueType value_type, 	
		EngineerGeoElement::GroundDescriptionType ground_description_type,
		EngineerGeoElement::StrengthDescriptionType strength_description_type);

	Cube4D * AddGeoCube(bool full_geo_cube_filling, 
		LabTrialValueType & vt, LabNormatives::type lab_normatives_type);

	Cube4D * AddingGeoCube(bool full_geo_cube_filling, 
		vector<key_grid> & kgs, 
		LabTrialValueType & vt, LabNormatives::type lab_normatives_type);
private:
	friend LRESULT CALLBACK DlgProcSurfLithoMappingList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	friend LRESULT CALLBACK DlgProcSurfEnGeoMappingList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
#if USE_SURF_IGE_MAPPING 
	vector<key_grid> surf_litho_geo_element_mapping;
	vector<key_grid> surf_eng_geo_element_mapping;
#endif
public:
	void LoadSurfEngGeoElementMappingFile();
	//void PrintSurfEngGeoElementMapping();

	//void GeoSurfaces_BlankAbove_By_SurfEngGeoElementMapping();
	void FillGrids_On_SurfEngGeoElementMapping();
	void FreeGrids_On_SurfEngGeoElementMapping();

	void LoadSurfLithoGeoElementMappingFile();
	//void PrintSurfLithoGeoElementMapping();

	void UstjaToReliefGriddata();
	void LoadReliefGriddata();



	void SetColorFromLitho();
	bool need_to_set_wel_element_litho_keys;
	void SetWellElementsLithoKeys();
	bool GetLithoKey(string podoshva_surfname, string & out_key);
	void LithoPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse);
	int LithoPodoshvaHowMany(string geo_element_key);
	LithoGeoElement * FindLithoGeoElement(string key);

	void SetColorFromIGE();
	bool need_to_set_wel_element_ige_keys;
	void SetWellElementsIGEkeys();
	bool GetIGEkey(string podoshva_surfname, string & out_key);
	void IGEZabojToGridData(string geo_element_key, GridData * pData);
	void IGEPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse);
	int IGEPodoshvaHowMany(string geo_element_key);
	EngineerGeoElement * FindEngineerGeoElement(string key);
	EngineerGeoElement * FindEngineerGeoElement(long id_ige);

	bool set_well_elements_ige_keys_show_error_message_box;
	bool set_well_elements_litho_keys_show_error_message_box;

	void HydroProjavlenieToGridData(long horizont, bool ust, GridData * pData);
	void HydroProjavlenieHowMany(map<long, long> &gorizonts, bool ust);

	//====== Массив вершин поверхности
#if DFX_LAYER_FROM_OBJECT
	vect<dxfConverter>					m_dxfConverters;
	ObjectList							m_dxfConverters_ObjectList;
#endif
	vect<Object, ObjectItem<Object> >	m_objects;
	ObjectList							m_objects_ObjectList;

	vect<Collection>					m_collections;
	ObjectList							m_collections_ObjectList;

	vect<AutoBuildProfile>				m_auto_build_profiles;
	ObjectList							m_auto_build_profiles_ObjectList;

	vect<Cube4D>	m_cubes;
	ObjectList		m_cubes_ObjectList;

	vect<GridData>	m_grid_data;
	ObjectList		m_grid_data_ObjectList;

	vect<GeoCatch>	m_geo_catches;
	ObjectList		m_geo_catches_ObjectList;

	vect<GeoSurface> m_surfaces;
	ObjectList		m_surfaces_ObjectList;

	vect<GeoSurface> m_faults;
	ObjectList		m_faults_ObjectList;

	vect<Well_3D>	m_drills;
	ObjectList		m_drills_ObjectList;

	vect<Line3D>	m_lines;
	ObjectList		m_lines_ObjectList;

	vect<Line3D>	m_cutlines;
	ObjectList		m_cutlines_ObjectList;

	vect<Line3D>	m_blanklines;
	ObjectList		m_blanklines_ObjectList;

	vect<String3D>	m_strings;
	ObjectList		m_strings_ObjectList;

	vect<Poligon3D> m_polygones;
	ObjectList		m_polygones_ObjectList;

	vect<Sphere3D>	m_spheres;
	ObjectList		m_spheres_ObjectList;

	vect<ThePoint3D>m_points;
	ObjectList		m_points_ObjectList;

	vect<Triangle3D>m_triangles;
	ObjectList		m_triangles_ObjectList;

	vect<Bmp3D>		m_bitmaps;
	ObjectList		m_bitmaps_ObjectList;

	vect<BmpProfile3D>		m_bmp_profiles;
	ObjectList		m_bmp_profiles_ObjectList;

	BROKEN_PLANE_VECTOR<BrokenPlane3D> 
					m_brokenPlanes;
	ObjectList		m_brokenPlanes_ObjectList;

	vect<TriangulatedGrid3D>
					m_tria_grid;
	ObjectList		m_tria_grid_ObjectList;


	double m_Spheres_max_z;
	double m_Spheres_min_z;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	vect<GridProfile3D>	m_grid_profiles;
	ObjectList			m_grid_profiles_ObjectList;


	int mGridProfilesDirection;
	double 
		max_grid_profiles_v,
		min_grid_profiles_v;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	APalette m_palette;

	UINT m_nColormap;
	bool m_bInverseColormap;
	bool m_bLocalColormap;
	bool m_bUseColormapOnSurf;

	bool m_bFlatShading;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	vect<BlnProfile3D>	m_bln_profiles;
	ObjectList			m_bln_profiles_ObjectList;

	DB_rozrizy m_db_rozrizy;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	double 
		m_zoomX,
		m_zoomY,
		m_zoomZ;
	bool m_bDrawStatusString;				

	HWND hwndTV, hSurfWnd;
	ListViewTabLL m_LayersListViewTab;
	ListViewTabKL m_KarotazhListViewTab;
	ListViewTabWDL m_WellsDrawListViewTab;
	ListViewTabLLL m_LabLayersListViewTab;
	ListViewTabLEL m_LabErrorsListViewTab;
	ListViewTabLXL m_LabExcludedListViewTab;
	ListViewTabWSL m_WaterSaturationListViewTab;


	ListViewTabSO m_SurfacesOrderListViewTab;
	ListViewTabSBO m_SurfacesBlankOrderListViewTab;
	ListViewTabSBF m_SurfacesBlankFunctionsListViewTab;

	ListViewTabSLM m_SurfLithoMappingListViewTab;
	ListViewTabSEGM m_SurfEnGeoMappingListViewTab;

	Layer				m_defaut_layer;
	map<int, Layer>		m_layers;
protected:
	Layer*				m_selected_layer;
	Line3D*				m_pLineForDraw;
	GridData*			m_pGridDataForDraw;
public:
	void SetGridDataForDraw(GridData* pGridData){m_pGridDataForDraw = pGridData;}
	void SetLineForDraw(Line3D* pLine){m_pLineForDraw = pLine;}
	bool IsThisGridDataForDraw(Object *pObject);
	bool IsThisLineForDraw(Object *pObject);
	void SetSelectedLayer(Layer* layer);
	const Layer* GetSelectedLayer() const {return m_selected_layer;}

	bool		m_bEqialZoomXYZ;
	bool		m_bEqialZoomXY;

	double		m_zoomCoefXYZ;
	double		m_zoomCoefXY;
	double		m_zoomXY;

	double m_sphere_radius;
	int m_sphere_slices; //The number of subdivisions around the z-axis (similar to lines of longitude). 
	int m_sphere_stacks; //The number of subdivisions along the z-axis (similar to lines of latitude). 

	GLdouble
		m_cut_plane_v[4],
		m_cut_plane_d[4];

	double 
		m_izo_step,

		m_X,
		m_Y,
		m_Z,

		m_xd_zoom_center,
		m_yd_zoom_center,
		m_zd_zoom_center,

		m_xd_min,
		m_yd_min,
		m_zd_min,

		m_xd_max,
		m_yd_max,
		m_zd_max,

		m_xv_min,
		m_yv_min,
		m_zv_min,

		m_xv_max,
		m_yv_max,
		m_zv_max;
	
	bool		m_bFastCutting;

	bool		m_bDrawGeoid;
	bool		m_bDrawCube;
	bool		m_bDrawCutPlane;
	bool		m_bDrawXYZCutPlanes;

	double		m_razlomThickness;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	int m_alpha;
	int m_alpha_plane; // коэффициент прозрачности
	int m_alpha_gdiplus_profiles; // коэффициент прозрачности


	GLdouble	m_fRangeX;		// Размер объекта вдоль X
	GLdouble	m_fRangeY;		// Размер объекта вдоль Y
	GLdouble	m_fRangeZ;		// Размер объекта вдоль Z

	// View:

	int			m_LightParam[11];// Параметры освещения

// Implementation
public:
	//===== Данные, характеризующие данные вдоль осей
	TData3D m_DataX, m_DataY, m_DataZ;
	//===== Заполнение TData для любой из осей
	void Scale(TData3D& data);
	//===== Подготовка цифровой метки на оси
	void MakeLabel(int axesFlag, double v, char* s, size_t len_s, char *spower, size_t len_spower);
	void SurfDoc::InitSurfDoc(vdouble& x, vdouble& y, vdouble& z, int type = 0);
	void SurfDoc::InitSurfDoc(vector<double>& x, vector<double>& y, vector<double>& z, int type = 0);
	void SurfDoc::InitSurfDoc(Vector<int>& lines_break_indexes, vdouble& x, vdouble& y, vdouble& z);
	void SurfDoc::InitSurfDoc(vector<int>& lines_break_indexes, vector<double>& x, vector<double>& y, vector<double>& z);
	void SurfDoc::InitSurfDoc (Vector<vdouble> &vx, Vector<vdouble> &vy, Vector<vdouble> &vz
					  /*, LPSTR sTitle, LPSTR sX, LPSTR sY*/);
	void SurfDoc::InitSurfDoc(vector<cut_of_line>& line_cutting_vector, vector<double>& x, vector<double>& y, vector<double>& z);
	void SurfDoc::InitSurfDoc(vector<cut_of_line>& line_cutting_vector, 
				int ix, int iy,
				vector<vector<double> >& data);
	void SetLight();
	SurfDoc(bool = true);
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
	bool IsSelectedGridDataPoint(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws, GridData *&pGridData);

	virtual void Draw();
	virtual void ReDraw(){}
	void UpdateAllViews();
	void UpdateAllGraphicsViews();
	void UpdateAllMapViews();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	void SetLayer(const Layer* layer){this->SetLayer_NonVirtual(layer);}
	void DrawCutPlaneLines();
	void WellsTriasTriangulation();
	void WellsEdgesTriangulation();
	void WellsEdgesTriangulationPerSloj();
	void CutMapBlnProfileSave();
	void CutMapBlnProfile();
	void UpdateZofSpheres(UINT len, int* z);
	void CutlinesSaveAs();
	void SpheresSaveAs();
	void AngleLocalMin(int n, double cos_boder);
	void IzolinesSaveAs();
	int AddNewBlnProfile_db(const char *lpstrFile, const char * name, vector<long> * pv_ID_KT, bool to_add_new_rozriz, vector<double> xMap, vector<double> yMap, vector<double> xProfile, bool acad_yscale_loaded, double z1w, double y1a, double z2w, double y2a, bool checked_plane = false, long id_rozriz = -1, bool to_add_hvosty = true);
	int AddBlnProfile(const char *lpstrFile, const char * name, vector<double> &xMap, vector<double> &yMap, vector<double> &xProfile, bool acad_yscale_loaded, double z1w, double y1a, double z2w, double y2a);
	int AddNewBlnProfile(const char *lpstrFile, const char * name, int ProfileDirection, double f);
	int AddBlnProfile(const char *lpstrFile, const char * name, int ProfileDirection, double f);
	int AddMapBlnProfile(vector<double> &xMap, vector<double> &yMap, int inside);
	int AddGridProfile(vdouble &x, vdouble &y, vdouble &z, vdouble& visible, vdouble &xMap, vdouble &yMap, vdouble &xProfile);
//#if FAST_GRID_LOADING
//	int AddGridProfile(Grid *pgrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile);
//#else
	int AddGridProfile(CGrid *pCGrid, vdouble &xMap, vdouble &yMap, vdouble &xProfile);
//#endif
	void ConvertGridProfilesTo3D();
	void ConvertBlnProfilesTo3D(bool create_layers);
	void SetLastBlnProfileAcadYscale(double z1w, double y1a, double z2w, double y2a);
	void ClearCutLines();
	void AddPoligon(vdouble& vx,vdouble& vy, vdouble& vz, COLORREF color);
	void AddPoligon(CPoint3* pts, int len, COLORREF color );
	void AddPoligon(Poligon3D& poly);
	void ClearPoligones();
	void AddTriangle(CPoint3 v1,CPoint3 v2,CPoint3 v3, COLORREF color);
	void ClearTriangles();
	void Izolines();
	void ClearIzolines();
	void GetMinMaxDPlaneCoef(bool bFastCutting, double& min_d, double& max_d);
	void CutXYZandDisvisible(int subcube_number);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	void InitXYZCutsPlanes();
	void OnCreate(bool to_init_palette_on_create);
	void FillLayerList();
	void UpdateLayersNames();
	void UpdateKarotazhNames(bool & update2Dview, bool & update3Dview);
	void UpdateWellDrawListNames();
	void UpdateLabLayersListNames();
	void UpdateWellDrawListWidth();
	void UpdateWaterSaturation();
	int GetIDForNewLayer();
	Layer* SurfDoc::FindLayer(char * name);
	Layer* AddNewLayer(char * name = NULL);
	Layer* GetLayerPtr(int id);
	void InitObjectsLayerPointers();

	bool GetExtremums_of_Surfaces_and_Faults(
		double& minX, double& minY, double& minZ,
		double& maxX, double& maxY, double& maxZ,
		bool use_only_cutplane_lines);
	void CutlineSaveAsRazres(double a, double b, double c, double d );
	bool CutlineSaveAsDxfRazres(dimeModel * model,  dimeBlock * block, SSaveProfData &sprData,
		double a, double b, double c, double d,
		double minX, double minY, double minZ,
		double maxX, double maxY, double maxZ);
	void CutAndDisvisible(bool positive);
	void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	void CutSave(bool toDrawTriaAndPoligones, bool positive);
	void Cut(bool toDrawTriaAndPoligones, bool positive);
	void CutSurfs(double a, double b, double c, double d, 
		bool toDrawTriaAndPoligones, bool positive, 
		short type_of_cutline, int cutting_number,
		CPoint2* pt1 = NULL, CPoint2* pt2 = NULL//две точки, 
		//ограничивающие линию прамолинейного участка ломанного разреза
		, void * pBrokenPlane = NULL);
	void CutFaults(double a, double b, double c, double d, 
		bool toDrawTriaAndPoligones, bool positive, 
		short type_of_cutline, int cutting_number,
		CPoint2* pt1 = NULL, CPoint2* pt2 = NULL//две точки, 
		//ограничивающие линию прамолинейного участка ломанного разреза
		, void * pBrokenPlane = NULL);
	void CutGeoCatches(double a, double b, double c, double d, 
		bool toDrawTriaAndPoligones, bool positive, 
		short type_of_cutline, int cutting_number,
		CPoint2* pt1 = NULL, CPoint2* pt2 = NULL//две точки, 
		//ограничивающие линию прамолинейного участка ломанного разреза
		, void * pBrokenPlane = NULL);
	void CutProfile(double a, double b, double c, double d, bool toDrawTriaAndPoligones, bool positive, bool useCutLines );
	void Cutting();
	int Document2ViewCoordinates(double xd, double yd, double zd, double& xv, double& yv, double& zv, bool started = true);
	int Document2ViewXCoordinates(double xd, double& xv);
	int Document2ViewYCoordinates(double yd, double& yv);
	int Document2ViewZCoordinates(double zd, double& zv);
	void ClearBmpProfiles();
	void ClearBitmaps();
	void ClearSpheres();
	void ClearPoints();
	void AddSpheres(vdouble &x, vdouble &y, vdouble &z, COLORREF color );
	void AddSpheresAsCollection(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color, char * name );
	void AddSpheres(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color );
	void AddSpheresAsCollection(vdouble &x, vdouble &y, vdouble &z, COLORREF color, char * name );
	void AddSphere(CPoint3 pt, COLORREF color );
	void AddPoint(CPoint3 pt, COLORREF color );
	void AddPoints(CPoint3* pts, int len, COLORREF color );
	void AddSphere(double x, double y, double z, COLORREF color );
	void AddSphere(const double * crd, COLORREF color );
	void AddBitmap();
	int AddBitmap(char *lpstrFile, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile);
	int AddBitmap(char *lpstrFile, vector<double> &xMap, vector<double> &yMap, double zElev);

	int AddBmpProfile(char *lpstrFile, vector<double> &xMap, vector<double> &yMap, vector<double> &zProfile);

	int GetExtremums(double& minX, double& maxX, double& minY, double& maxY,double& minZ, double& maxZ );
	
	Cube4D * AddCube(Grid4 *pgrid);
	Cube4D * AddCube(Grid4 *pgrid, COLORREF color);
	Cube4D * AddCube(Grid4 *pgrid, const char * name, COLORREF color);

	Cube4D * AddThinCube(Grid4 *pgrid);
	Cube4D * AddThinCube(Grid4 *pgrid, COLORREF color);
	Cube4D * AddThinCube(Grid4 *pgrid, const char * name, COLORREF color);

#if FAST_GRID_LOADING
	size_t AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, Grid* pgrid );
	size_t AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, Grid *pgrid, COLORREF color );
	size_t AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, Grid *pgrid, COLORREF color, const char * name);
#else
	size_t AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, CGrid* pCGrid );
	size_t AddSurf(long id_surf, BYTE podoshva, long id_ige, int zflag, CGrid *pCGrid, COLORREF color );
#endif
	void AddWells(vector<vector<cell> > * pdrills);
	void AddWells(LPDRILLSDLGDATA lpDrillsDlgMem, bool fill_well_colomn, bool is_eng);
	void AddKarotazhy(LPDRILLSDLGDATA lpDrillsDlgMem, bool fill_well_colomn);
	void GetKarotazhCube(int index, double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz);
	void InterpolateKarotazhCube3(int index);//, double minx, double miny, double minz, double maxx, double maxy, double maxz, double dx, double dy, double dz);
	void InterpolateKarotazhCube(int index, 
		bool divide_cube_on_1_25, 
		Karotazh::linterp_method int_meth, 
		karotazh_extrapolate_down ked,

		long griddata_app, 
		long griddata_fun_number,

		bool filter_grid_min_max_cube_2d, 
		bool filter_grid_min_max_cube_3d,
		
		bool to_blank_with_Triangulation_Contour,
		bool use_biss, double len_biss,
		bool to_blank_with_loaded_Contour);
	void ProjectionKarotazhCube(int index_kar, int index_cub);
	void KarotazhSaveAsDat(int index, const char * fn);
	void KarotazhSaveAsDat(int index);

	bool GetAcadYscaleLoaded();
	void SavingOfCubeProjectionGrid(const char * outdir, int index_cub, int make_grids_vnahljost, bool convert_to_acad_yscale, bool non_stretched_xscale);

	Cube4D * SvaiBuroNabivnie(
		int index_cub_internal_friction_angle,
		bool use_cub_specific_gravity_of_ground,
		int index_cub_specific_gravity_of_ground,
		int index_surface_of_relief,
		int index_surface_of_rostverk,
		bool use_rostverk_altituda,
		double rostverk_altituda,
		bool use_cub_fluidity_index,
		int index_cub_fluidity_index,
		double d,
		BuroNabivSvaj::SvaiType svai_type,
		double v_custom_gamma_cf[4], 
		BuroNabivSvaj::ParamType result_type,
		bool use_water_saturation,
		int index_cub_specific_gravity_of_suspended_in_water_ground,
		int index_cub_fluidity_index_of_water_saturated_ground,
		double gamma_k,
		bool decrease_clay_R_if_porosty,
		bool increase_fi_if_dense_sand,
		bool increase_fi_if_not_porosty_clay);

	Cube4D * SuspendedInWaterSpecificGravity(
		int index_cub_specific_gravity_of_ground_particles,
		int index_cub_porosity_factor);	
	bool SuspendedInWaterSpecificGravity();

	void WellsSaveToDB();
	void TestSvai();
	void TestDublicateWells();

	void DeterminePesokGlinaFromPCK();
	void DetermineDeformationModul();
	void DetermineUdelnoeSceplenie();
	void DetermineUdolVnutrennegoTrenia();
	void TestPesokOrGlina();

	// загрузка входных файлов статического зондирования
	bool ReadZondInputFile(char *file);
	int ParseZondInputFileLine(char* szBuff, int type_line, bool starting_parsing, int &i_point, int &n_zond_points, vector<string> & zond_points_names, int &i_glubina);
	// загрузка результатов обработки программой ZOND статического зондирования
	bool ReadZondOutputFile(char *file);
	int ParseZondOutputFileLine(char* szBuff, int type_line);
	// корректировка чередования глина - песок во входных файлах статического зондирования
	bool ReadZond_CorrectInput_File(char *file);
	int ParseZond_CorrectInput_FileLine(char* szBuff, int type_line, bool starting_parsing, int &n_zond_points, int &i_glubina, vector<string> & zond_points_names);

	// данные лабораторных анализов
	wells_draw_list_item * m_wdli_laboratory;
	void AddNewWellColomn_LaboratoryAnalizes();
	Laboratory m_laboratory;		
	vector<error_of_add_new_well_colomn_laboratory_analizes> lab_errors;

	LabLayer * AddNewLabLayer(long id_ige, const char * id, const char * layer_number, const char * fn);
	LabLayer * FindLabLayer(long id_kt, double depth);
	LabLayer * FindLabLayer(const char * id);
	LabLayer * FindLabLayer(long id_ige);

	void OnViewPropertywindowwithPlot();
	void OnViewPropertywindowwithResults();
	void OnViewPropertywindowwithLabnumbertriallist();
	void OnViewPropertywindowwithNormatives();
	void OnViewPropertywindowwithCorrelation();
	void OnViewPropertywindowwithNormativesbyallexperiences();

	bool Get_Laboratory_context_with_plot();
	bool Get_LabNumber_context_with_results();
	bool Get_LabLayer_context_with_lab_number_trial_list();
	bool Get_LabLayer_context_with_normatives();
	bool Get_LabLayer_context_with_korrelation();
	bool Get_LabLayer_context_with_normatives_by_all_experiences();


	void LabExcludedList(HWND hWndParent);
	void LabLayerPropertyWindow(HWND hWndParent, long id_ige, long x, long y);
	void LabLayerNormatives(int type, long id_ige);
	void LabLayerChastnye(long id_ige);

	void AddNewWellColomn_LaboratoryAnalizes_FromDB(long id_obj, const char * contract, const char * object_name);
	void AddPrGrunt(long id_obj, 
		long id_kt, const char * kt_name, long kt_idtyp, long id_prob, double depth,
		long lab_n, long id_kodprob, long id_gr, const char * soil_name, const char * grunt_name,
		long id_ige
		);

	void AddProp(
		long id_kt, long id_prob, 
		long id_vyprob, long id_param, const char * param_name, double val, unsigned char bStat
		);


	void Zriz_tbl(
		long id_kt, long id_prob, long id_vyprob, long id_kolca, 	
		double sigma, double tau, double w_do, double ro_do, double w_po_upl, double ro_po_upl, double w_after, double ro_after, unsigned char bStat
		);

	void Zriz0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
		double h, double d, double dh_po_upl,
		double m_kolca,
		double m_grunta,
		double m_grunta_zamoch,
		double m_grunta_posle_uplot,
		double m_grunta_posle,
		double m_grunta_vysush);

	void Zriz(
		long id_kt, long id_prob, long id_vyprob, 	
		long id_hid, long id_shema, long id_stan, double tgfi, double c, double d, double h, unsigned char bStat
		);

	void ApplyParams();
	void ApplyZriz();

	void Compress(
		long id_kt, long id_prob, long id_vyprob, 	
		double sigma, double dh1, double dh2, unsigned char voda, unsigned char bStat);
	void Compress(
		long id_kt, long id_prob, long id_vyprob, 	
		double h, double d, 
		double es_l1, double es_r1, double es_l2, double es_r2,
		double nju, double nju_z,
		double m01, double E1, double m02, double E2,
		double m01v, double E1v, double m02v, double E2v,
		unsigned char id_method, unsigned char bStat, unsigned char bStatV
		);

	void Cilce0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
		double h, double d,
		double m_kolca,
		double m_grunta,
		double m_grunta_zamoch,
		double m_grunta_posle,
		double m_grunta_vysush);

	void ApplyCompress(bool use_compression3);

	void ParseTrialIndications();
	void AfterExportFromDB(double _pressure_interval_01_02_0);


	void AddNewWellColomn_LaboratoryAnalizes_FromDB_2();

	void AddGranular(long id_kt, long id_prob, long id_gran, const char * gran_name, double val);
	void ApplyGranular();

	PCK2FizParams m_pck2fiz_params;

	void PCK2Fiz_CalcParams(long id_calc_param, const char * calc_param, const char * desc);
	void PCK2FizResults(long id_kt, long npp, long id_calc_param, double param);

	void StZond(
		long id_kt, long npp, long typgr,
		double h, double q0, double f0, 
		double dh, double fsr, 
		unsigned char bStat,
		long id_ige, double pck
		);
	void PtStZond(
		long id_kt, long id_ust, double glyb,
		const char * ust_name,
		long typ_zond, long n_shema,
		double Kg, double Kf, double Bg, double Bf, double shtanga_d
		);
	void ApplyStZond();

	void Palja(
		long id_kt,
		double h, 
		double qc, double beta1, double Rs, double fs, double beta2, double f,
		double RsA, double fhu, double Fu);
	void PtPalja(
		long id_kt, long id_typ,
		double pereriz_x, double pereriz_y, double A, double u, double glyb, double RsA, double fhu, double pz,
		long id_snip, double Fu);
	void ApplyPalja();

	void Rozrizy(
		long id_rozriz, const char * nomer, BYTE has_dxf, const char * fn_dxf,
		BYTE acad_yscale_loaded,
		double z1w, double y1a, double z2w, double y2a);
	void Rozriz(long id_rozriz, long npp, long id_kt, double dxf_x);
	void ApplyRozriz();

	db_IGE m_db_ige0;
	db_IGE m_db_ige;

	db_Genezis m_db_genezis;
	db_UmPoz m_db_umpoz;

	void Lito0(
		long id_kt, long id_ige, double h0,	double h1
		);
	void IGE0(
		long id_ige, long id_gr,
		const char * ige,
		double mk, double mkz,
		const char * strat, const char * desc0);
	void Lito(
		long id_kt, long id_ige, double h0,	double h1
		);
	void IGE(
		long id_ige, long id_gr,
		const char * ige,
		double mk, double mkz,
		const char * strat, const char * desc0);
	void Grunty(
		long id_gr,
		const char * nazva_u, const char * nazva_r,
		long typgr, long typgr_pck, long id_normatyv, long id_grcons, long id_uklad, long id_nju, long id_grmain, long id_umpoz, long id_genezis);
	void Genezis(long id_genezis,
		const char * nazva_u, const char * nazva_r,
		long id_normatyv, long id_grmain,
		const char * index,
		BYTE r, BYTE g, BYTE b);
	void UmPoz(long id_umpoz,
		const char * umpoz, const char * hatchacad,
		double angle, double scale);
	void ApplyLito();

	void Voda(long id_kt, long horizont,
		double hv_z, double hv_v,
		SYSTEMTIME dv);
	void ApplyVoda();

	void RebuildByGridData_IfNeed();

	void MySurfer_skip_next_alert();
	void MySurfer_set_next_alert();

	db_griddata m_db_griddata;
	void GridDataUsedAlg(long id_surf, BYTE griddata_app, long id_alg);
	void GridDataSurfaces(long id_surf, const char * nazva, BYTE podoshva, BYTE r, BYTE g, BYTE b, short z_flag, long id_umpoz, long id_ige);
	void DBGridData(long id_surf, long id_point,
		double x, double y, double z);
	void ApplyDBGridData();

	void SurfLitoMapping(long id_surf, long id_ige);
	void SurfIgeMapping(long id_surf, long id_ige);
	void SurfacesOrder(long npp, BYTE check, long id_surf, BYTE podoshva, BYTE check2);
	void SurfacesBlankOrder(long npp, long id_surf, BYTE podoshva, 
		BYTE check_blank_me,
		BYTE check_blank_me_up,
		BYTE check_blank_me_up_above,
		BYTE check_blank_me_down, 
		BYTE check_blank_me_down_above,
		BYTE check_blank_by_me_up,
		BYTE check_blank_by_me_down
		);
	void SurfacesBlankFuntions(/*long id_item, */long id_surf_obj, long id_surf_param, BYTE id_blank_fun);

	void ApplySurfacesOrder();

	void DefineCubeSize(CubeSize & cube_size);
	void DefineZoom(double zoomCoefXYZ, double zoomCoefXY);


	void AddSurfIgeMappingItem(long id_surf, BYTE podoshva, const char * surf_name, const char * ige_key);
	void AddSurfIgeMappingItemToDB(long id_surf, const char * ige_key);
	void AddSurfLitoMappingItem(long id_surf, BYTE podoshva, const char * surf_name, const char * ige_key);
	void AddSurfLitoMappingItemToDB(long id_surf, const char * ige_key);
	void ClearSurfIgeMappingItem(long id_surf);	
	void ClearSurfLitoMappingItem(long id_surf);	



private:
	Well_3D * current_well_to_add_karotazhy_from_zond;
public:
	int GetIndexForNewKarotazh();
	int AddKarotazh(const char * name, COLORREF color = RGBA(0,0,255,125), bool if_exist_add_new = false);
	
	void SurfaceOrderList_UpdateCheckings();
	void SurfaceOrderList_MoveItemUp(int context_menu_item);
	void SurfaceOrderList_MoveItemDown(int context_menu_item);
	surface_order_list_item * AddSurfaceOrder(bool check, long id_surf, BYTE podoshva, const char * name, bool to_end_of_vector);
	

	void SurfaceBlankFunctionsList_SwapItemSurfaces(int context_menu_item);
	void SurfaceBlankFunctionsList_SwapItemMethod(int context_menu_item);

	void SurfaceBlankOrderList_UpdateCheckings();
	void SurfaceBlankOrderList_MoveItemUp(int context_menu_item);
	void SurfaceBlankOrderList_MoveItemDown(int context_menu_item);
	surface_blank_order_list_item * AddSurfaceBlankOrder(long id_surf, BYTE podoshva, const char * name, bool to_end_of_vector);
	
	void InitSurfaceBlankFinctionNames(surface_blank_functions_list_item * item);
	surface_blank_functions_list_item * AddSurfaceBlankFunction(long id_surf_obj, long id_surf_param, BYTE id_blank_fun);
	void DeleteSurfaceBlankFunction(long r);
	
	void WellsDrawList_MoveItemUp(int context_menu_item);
	void WellsDrawList_MoveItemDown(int context_menu_item);
	wells_draw_list_item * AddWellsDraw(WellElement::type t, bool check, float width,  bool to_end_of_vector, wells_draw_list_item::draw_mode_2d drawmode2d);
	wells_draw_list_item * m_wdli_primitive;
	void UpdateWellColomnsByWellsDraw();

	void   SetWellW(double w);
	double GetWellW();
	
	Well_3D * FindWell(long id_kt);
	Well_3D * FindWell(const char * name);
	GridData * FindGridData(long id_surf);
	GeoSurface * FindGeoSurface(const char * name);
	GeoSurface * FindGeoSurface(int index);
	GeoSurface * FindGeoSurface(long id_surf);
	Cube4D * FindCube(int index);




	void ClearObjects();
	void ClearCollections();

	void ClearStrings();
	void ClearBlnProfiles();

	void ClearLines();
	void ClearBlankLines();
	void ClearDrills();
	void ClearKarotazhList();
	void ClearKarotazhy();
	void ClearSurf();
	void ClearFaults();
	void ClearGeoCatches();
	void ClearGridData();
	void ClearCubes();
#if DFX_LAYER_FROM_OBJECT
	void ClearDxf();
#endif
	void ClearAutoBuildProfiles();
	bool SetExtremums_ByGriddata(double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz);
	bool SetExtremums_ByKarotazhy(double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz);

	virtual bool UpdateExtremums();
	void ZoomView(bool started = true);
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	void ZoomViewCutlinesPolygones();
	void ClearCutlinesPolygones();
#if !VIEW_ONLY_VERSION
	bool AddAutoBuildProfile();
	bool AddAutoBuildProfile1();
#endif
	size_t AddSurf(long id_surf, BYTE podoshva, int zflag, vdouble& x, vdouble& y, vdouble&z);
	size_t AddSurf(long id_surf, BYTE podoshva, int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible );
	size_t AddSurf(long id_surf, BYTE podoshva, int zflag, vdouble &x, vdouble &y, vdouble &z, vdouble& visible, COLORREF color );
	Line3D* AddLine();
	void AddLine(COLORREF color);
	void AddCutLine();
	void AddBlankLine(int inside);
	void AddCutLine(COLORREF color);
	void AddLine(vdouble& x, vdouble& y, vdouble&z, COLORREF color );
	void AddLine(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color );
	void AddLine(CPoint3* pts, int len, COLORREF color );
	void AddString(CPoint3 pt, char *s, COLORREF color = 0, double vshift = 0.0);
	void AddCutLine(CPoint3* pts, int len, COLORREF color );
	void AddCutLine(vdouble& x, vdouble& y, vdouble&z, COLORREF color );
	virtual ~SurfDoc();

	void SurfacesAutoBlank(void);

	void BlnProfilesIntersectionsBuild();
	void SurfacesFaultsCutlines(void);
	void SurfacesBlank(void);
	void FaultsBlank(void);
	void BrokenPlanesBlank(void);
	void LoadBlankBln(void);
	void NoBlank(bool toClearBlankLines);

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);

	void AddObject(Object * object);
	Collection* CreateNewCollection(void);
	bool AddObjectToLastCollection(Object * object);
	bool AddObjectToCurrentCollection(Object * object);

	long GetIDSurfForNewGridDataOrSurface(void);

	bool InitGeoCatch_GorizontPlane(void);
	GeoCatch * CreateNewGeoCatch(void);
	GridData * CreateNewGridData(long id_surf = -1);
	Cube4D * CreateNewCube(void);

	bool LoadAndScaleDxf_onXY();
	bool LoadAndScaleDxf_onY();
#if DFX_LAYER_FROM_OBJECT
	void CreateNewDxf(void);
	bool InitLastDxf(void);
#endif
#if !VIEW_ONLY_VERSION
	void CreateNewAutoBuildProfile(void);
#endif

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, SurfDoc& ob);
	friend Archive& operator >>(Archive& ar, SurfDoc& ob);

	bool SerializeFileBlock(FileBlockInfo& fbi, Archive& ar);

	void BlankGeoCatchGorizontPlane(void);
	bool SaveFile(LPCTSTR filename, int nBufSize,  void* buff);
	bool OpenFile(LPCTSTR filename, int nBufSize,  void* buff, bool AsImport);
	bool OpenCubeFile(LPCTSTR filename, int nBufSize,  void* buff);

	void BlankingOfGeoCatchBlankLines(void);

	CPoint3 ZoomInv(CPoint3& pt_view);

	template <class T> void Zoom(vect<T> & v) ;

};
template <class T> void SurfDoc::Zoom(vect<T> & v) 
{
	if (v.SetCurrentMsgOnFirst())
	{
		do
		{
			v.GetCurrentMsg().Zoom(
				m_zoomX,m_zoomY,m_zoomZ, 
				m_xd_zoom_center,
				m_yd_zoom_center,
				m_zd_zoom_center
				);
		}
		while(v.IncrementCurrentMsg());
	}
};

bool GetGammaCF(BuroNabivSvaj::SvaiType svai_type, double v_custom_gamma_cf[4], CGround::ground_type ground_type, double & gamma_cf);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_)
