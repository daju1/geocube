// Well_3D.h: interface for the Well_3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRILL_3D_H__446F8BA8_EDA9_42C6_AECC_2F9A8FCF8080__INCLUDED_)
#define AFX_DRILL_3D_H__446F8BA8_EDA9_42C6_AECC_2F9A8FCF8080__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"
#include "../../tools/src/readfile.h"
#include "../../array/src/vect.h"

#include ".\WellElement.h"

class SurfDoc;
class gdiplus_map_view;

struct karotazh_extrapolate_down
{
	bool to_extrapolate_down;
	enum extrapolate_down_method
	{
		none = 0,
		with_lowest_value,
		continue_interpolation
	};
	extrapolate_down_method m_extrapolate_down_method; 
	double extrapolation_len;
	karotazh_extrapolate_down()
	{
		to_extrapolate_down = false;
		m_extrapolate_down_method = extrapolate_down_method::none;
		extrapolation_len = 0.0;
	}
	karotazh_extrapolate_down(extrapolate_down_method method, double len)
	{
		to_extrapolate_down			= true;
		m_extrapolate_down_method	= method;
		extrapolation_len			= len;
	}
};

struct karotazh_slice
{
	vector <double> vx,vy,vv;
	double z;
	karotazh_slice(double _z) : z(_z) {}
};

#define KAROTAZH_LIST_ITEM_VERSION 3

struct karotazh_list_item
{

	// project for version 3
	double scale_2d;// on GDIplus view
	enum draw_mode_2d {right = 1, left = 2, both = 3} ;
	draw_mode_2d m_draw_mode_2d;
	bool disp_point_values_2d;


	int index;

	DWORD version;

	string name;
	double vmin, vmax;
	COLORREF color;
	int alpha;
	bool checked;

	double scale;
	bool logarithmic_scale;
	bool scale_from_zero;// or scale from vmin ?
	bool disp_point_values;

	karotazh_list_item()
	{
		m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
		scale_2d = 1.0;

		index = -1;

		version = KAROTAZH_LIST_ITEM_VERSION;
		name = "";
		vmax = -DBL_MAX;
		vmin = DBL_MAX;

		color = RGBA(0,0,255,125);
		alpha = 125;
		checked = true;

		scale = 0.1;
		logarithmic_scale = false;
		scale_from_zero = false;
		disp_point_values = false;
	}	

	karotazh_list_item(int ind)
	{
		m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
		scale_2d = 1.0;

		index = ind;

		version = KAROTAZH_LIST_ITEM_VERSION;
		name = "";
		vmax = -DBL_MAX;
		vmin = DBL_MAX;

		color = RGBA(0,0,255,125);
		alpha = 125;
		checked = true;

		scale = 0.1;
		logarithmic_scale = false;
		scale_from_zero = false;
		disp_point_values = false;
	}	
	karotazh_list_item(int ind, const char * fn)
	{
		m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
		scale_2d = 1.0;

		index = ind;

		version = KAROTAZH_LIST_ITEM_VERSION;
		name = fn;
		vmax = -DBL_MAX;
		vmin = DBL_MAX;

		color = RGBA(0,0,255,125);
		alpha = 125;
		checked = true;

		scale = 0.1;
		logarithmic_scale = false;
		scale_from_zero = false;
		disp_point_values = false;
	}	
	
	karotazh_list_item(int ind, const char * fn, COLORREF c)
	{
		m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
		scale_2d = 1.0;

		index = ind;

		version = KAROTAZH_LIST_ITEM_VERSION;
		name = fn;
		vmax = -DBL_MAX;
		vmin = DBL_MAX;

		color = c;
		alpha = 125;
		checked = true;

		scale = 0.1;
		logarithmic_scale = false;
		scale_from_zero = false;
		disp_point_values = false;
	}

	karotazh_list_item(const karotazh_list_item & item)
	{
		m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
		scale_2d = 1.0;

		index = item.index;

		version = item.version;
		name = item.name;
		vmax = item.vmax;
		vmin = item.vmin;

		color = item.color;
		alpha = item.alpha;
		checked = item.checked;

		scale = item.scale;
		logarithmic_scale = item.logarithmic_scale;
		scale_from_zero = item.scale_from_zero;
		disp_point_values = item.disp_point_values;
	}

	friend Archive& operator <<(Archive& ar, karotazh_list_item& ob);
	friend Archive& operator >>(Archive& ar, karotazh_list_item& ob);
};

class Karotazh : public Primitive3D<CPoint4>
{
	int m_index;
	double m_min_v, m_max_v;

	void Init(const Karotazh& ob);
	void OnCreate(void);
protected:
	friend class Well_3D;
	virtual void Drawing();
public:
	Karotazh();
	Karotazh(const Karotazh& ob);
	Karotazh& operator=(const Karotazh& ob);
	Karotazh(SurfDoc * pSurfDoc);
	Karotazh(SurfDoc * pSurfDoc, const char * _name);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}
	virtual void PropertiesDialog();
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	virtual bool UpdateExtremums();
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);

	void GetKarotazhCube(double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz);
	enum linterp_method {linear, spline};
	void PutKarotazhSlicesPoint(Karotazh::linterp_method int_meth, vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked);
	void PutKarotazhSlicesPoint_Spline(vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked);
	void PutKarotazhSlicesPoint_Linear(vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked);
	void PutKarotazhPoints(vector<double> & vxk, vector<double> & vyk, vector<double> & vzk, vector<double> & vvk);

	double Zoom_GDIplus(double vd);
	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Karotazh& ob);
	friend Archive& operator >>(Archive& ar, Karotazh& ob);

	static int slices;
	static int stacks;

	static int s_alpha;
	static bool s_checked;
	static bool s_disp_point_values;
	static bool s_disp_point_values_2d;
	static double s_scale;
	static double s_scale_2d;
	static bool s_logarithmic_scale;
	static bool s_scale_from_zero;

	bool SaveAsDat(FILE * stream);

	void PrintfProperties(vector<fmtstr> & text);

};
#include <GdiplusEnums.h>
struct grunt_tolscha
{
	//long m_id_ige;
	double m_h_pod;
	long m_typgr;
	//bool m_Qs_determined;
	//double Qs;
};
class Well_3D : public Primitive3D <CPoint3>
{
	GLuint m_nglListNumber_Primitive;
	virtual void Drawing();

	friend class project;

	vector<WellColomn> well_colomns;
	//map<WellElement::type, WellColomn> well_colomns;

public:

	static bool draw2d_center;
	static COLORREF center_color;
	static DashStyle dashStyle;
	static float dashOffset;

	bool IsWellElement(const WellElement * p1);

	void ReinitWellColomnsPointers();
	WellColomn * FindWellColomn(WellElement::type t);
	//WellColomn * AddWellColomn(WellElement::type t);
	void AddNewWellColomn_LaboratoryAnalizes();
	int AddNewWellColomn(WellElement::type t, wells_draw_list_item * wdli);
	void UpdateWellColomnsByWellsDraw();

	int GetColorSize(){return (int)m_vColor.size();}
	COLORREF GetColor(int i){if(i >= 0 && i < (int)m_vColor.size()) return m_vColor[i]; else return 0;}
	string GetSlojName(int i){if(i >= 0 && i < (int)m_vstrSloiNames.size()) return m_vstrSloiNames[i]; else return string();}
	string GetWellID(){return sID;}
	virtual void PropertiesDialog();

	void PrintfProperties(vector<LabData> & labdata);
	void PrintfProperties(vector<fmtstr> & text);
	void FillContextMenu(HMENU& hMenu);


	const char * GetIDString()
	{
#if USE_STRING_IN_THE_CELL
		return sID.c_str();
#else
		return sID;
#endif
	}
	Well_3D::Well_3D();
	Well_3D(SurfDoc * pSurfDoc);
	virtual ~Well_3D();
	void WellInit(long id_kt, const char * name, long kt_idtyp, double X, double Y, double ustje, double zaboj, long id_bur_type, long d_bur, string data_bur);
	void WellInit1(vector<vector<cell> >::iterator pdrills);
	bool WellInit2(vector<vector<cell> >::iterator pdrill,
		vector<cell> * karotazh_glubin,
		vector<int> * types_of_colomns,
		vector<string> * pnames_of_colomns,
		vector<COLORREF> * colors_of_sloi,
		char* filename,
		wells_draw_list_item * wdli_podoshva, bool is_ige,
		wells_draw_list_item * wdli_hydro,
		bool to_realloc);

	void Insert(size_t i_where, CPoint3 pt);
	void ErasePoint(size_t i);
	void ResetPesokGlinaCheredovanie();
	void WritePesokGlinaCheredovanie(FILE * out);
	bool PutPesokOrGlinaPodosnvaOld(bool is_pesok, double glubina_podoshvy);
	bool PutPesokOrGlinaPodosnva(bool is_pesok, double glubina_podoshvy, WellColomn * w_colomn_issand);
	bool IsPesokOrGlina(double z, bool & is_pesok);
	bool GetTypGrunt_from_db_lito(double glubina_ot_ustja, long & typgr);
	bool GetTypGrunt_from_db_lito(double glubina_ot_ustja_0, double glubina_ot_ustja_1, 
										bool & have_bound_in_the_interval, 
										double & glubina_ot_ustja_of_bound_in_the_interval,
										long & typgr_0, long & typgr_1, 
										long & typgr);

	Karotazh * AddKarotazh(int kar_index);
	Karotazh * GetKarotazh(int kar_index);
	bool AddPointToKarotazh(int kar_index, double value, double glubina);
	
	void WellsSaveToDB();
	void TestSvai();
	void TestSvai2();
	bool FindIntegralPCB(Karotazh * karotazh_pcb, CPoint3 & ustje, double glubina, double & fh);

	bool FindIntegralPCB(double glubina_rostverka, double glubina_ot_ustja, double & fh, long id_snip, bool razbivka_na_tolschi, long typ_grunt_1_zond_type, double & beta2, double & fs);

	static bool ZondFirstTypeMyMethod;
	bool FindIntegralPCB_1_select_method(long id_snip, 
								 bool razbivka_na_tolschi, long typ_grunt_1_zond_type, 
								 vector<grunt_tolscha> & v_grunt_tolscha,
								 double typgr_1_sum_tolshina,
								 double typgr_2_sum_tolshina,
								 double glubina_rostverka, double glubina_ot_ustja, 
								 double & fh, double & beta2, double & fs);
	bool FindIntegralPCB_1_my_method_grunt_type_by_IGE(bool razbivka_na_tolschi, long typ_grunt_1_zond_type, double glubina_rostverka, double glubina_ot_ustja, double & fh, double & beta2, double & fs);
	bool FindIntegralPCB_1_my_method_grunt_type_by_stat_zond_table(bool razbivka_na_tolschi, long typ_grunt_1_zond_type, double glubina_rostverka, double glubina_ot_ustja, double & fh, double & beta2, double & fs);
	bool FindIntegralPCB_1(long id_snip, long typgr, bool use_typgr_part, double typgr_1_part, double typgr_2_part, double glubina_rostverka, double glubina_ot_ustja, double & fh, double & beta2, double & fs);
	bool FindIntegralPCB_23_by_fsr_tab(double glubina_rostverka, double glubina_ot_ustja, double & fh, long id_snip);
	bool FindIntegralPCB_23_by_integral(double glubina_rostverka, double glubina_ot_ustja, double & fh, long id_snip);


	int WriteZondInput_FileLine(FILE * out, char* szBuff, int type_line);
	void SaveAsZondInput();

	void EraseSloi();
	void DeterminePesokGlinaFromPCK(wells_draw_list_item * wdli_issand);
	void DetermineDeformationModul();
	void DetermineUdelnoeSceplenie();
	void DetermineUdolVnutrennegoTrenia();
	void TestPesokOrGlina();
	
	void Init(const Well_3D& ob);
	int CompareWellID(Well_3D& ob);
	Well_3D(const Well_3D& ob);
	Well_3D& operator=(const Well_3D& ob);
	void OnCreate(void);
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	virtual bool Well_3D::SaveAsDat(FILE * stream);
	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, Well_3D& ob);
	friend Archive& operator >>(Archive& ar, Well_3D& ob);

	virtual bool UpdateExtremums();
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual void Draw();
	virtual void ReDraw(void);
	virtual void OnPaint();
	void OnPaintPrimitive();

	void SetWellElementsIGEkeys();
	void SetColorFromIGE();
	void IGEZabojToGridData(string geo_element_key, GridData * pData);
	void IGEPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse);
	int IGEPodoshvaHowMany(string geo_element_key);

	void SetWellElementsLithoKeys();
	void SetColorFromLitho();
	void LithoPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse);
	int  LithoPodoshvaHowMany(string geo_element_key);

	void HydroProjavlenieToGridData(long horizont, bool ust, GridData * pData);
	void HydroProjavlenieHowMany(map<long, long> &gorizonts, bool ust);

	void UstjaToReliefGriddata(GridData * pData, COLORREF color);

	static float width_karotazh;

	WellColomn * Well_3D::FindWellColomn(int wdli_id);

	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on);
	void DrawGDIplus_Primitive(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, wells_draw_list_item * wdli);
	
	
	void Draw_Primitive(wells_draw_list_item * wdli);
	void ReDraw_Primitive(wells_draw_list_item * wdli);
	void Drawing_Primitive(wells_draw_list_item * wdli);

	bool OnProfile(Profile3D * on);
	bool IsSelectedWell(gdiplus_map_view * gv, Profile3D * on, int mouse_x, int mouse_y, double & dist_to_line_object, WhatSelected& ws);

	void GetKarotazhCube(int index, double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz);
	void PutKarotazhSlicesPoint(Karotazh::linterp_method int_meth, int index, vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked);
	void PutKarotazhPoints(int index, vector<double> & vxk, vector<double> & vyk, vector<double> & vzk, vector<double> & vvk);
	void KarotazhProjection(int index, Cube4D & cube);

	bool GetUstje(CPoint3 & pt3);
	bool GetZaboj(CPoint3 & pt3);
	void SetZaboj(double altituda);
	bool GetZaboj(double & altituda);


	static vector<wells_draw_list_item *> wells_draw_list;
	static vector<karotazh_list_item> karotazh_list;
	
	void ClearKarotazhy();

	static int GetKarotazhIndex(const char * name);

	static int s_sloj_number_to_save;
	static bool s_use_sloj_names;
	static bool s_show_all_sloi;

	static long zab_svai_id_snip;
private:
	vector<COLORREF> m_vColor;// may be do static ????
	vector<string>   m_vstrSloiNames;
	short m_type;
#if USE_STRING_IN_THE_CELL
	string	sID;
#else
	char sID[CELL_S_N_CHARS];
#endif
	vect<Karotazh> m_karotazhy;
friend class SurfDoc;
friend class CListRaschetSvai;
friend class CDlgPalja;
friend class MyPalja;
friend class BrokenPlane3D;

	StatZond m_stat_zond;
	APalja m_palja;
	void CalcPalja(long id_typ, double pereriz_x, double pereriz_y, 
		double glubina_rostverka,
		long id_snip, bool razbivka_na_tolschi, long typ_grunt_1_zond_type, long id_method_FindMeanPCK, double step);

	long   m_id_kt;       // ID комплексной точки
	long   m_kt_idtyp;    //тип комплексной точки
	long   m_id_bur_type; // способ бурения
	long   m_d_bur;       // диаметр бурения
	string m_data_bur;    // дата бурения

	double m_w;           // ширина колодца скважины
public:
	long GetIdKt(){return m_id_kt;}

	PCK2FizResults m_pck2fiz_results;


	void AddPCK2FizResults(long npp, long id_calc_param, double param);

	void AddStZond(
		long npp, long typgr,
		double h, double q0, double f0, 
		double dh, double fsr, 
		unsigned char bStat,
		long id_ige, double pck
		);
	void AddPtStZond(
		long id_ust,
		double glyb,
		const char * ust_name,
		long typ_zond, long n_shema,
		double Kg, double Kf, double Bg, double Bf, double shtanga_d
		);
	void ApplyStZond();

	void Well_3D::Palja(
		double h, 
		double qc, double beta1, double Rs, double fs, double beta2, double f,
		double RsA, double fhu, double Fu);

	void Well_3D::PtPalja(
		long id_typ,
		double pereriz_x, double pereriz_y, double A, double u, double glyb, double RsA, double fhu, double pz,
		long id_snip, double Fu);
	void Well_3D::ApplyPalja();


	DB_Lito m_db_lito0;
	DB_Lito m_db_lito;
	void Lito0(long id_ige, double h0, double h1);
	void Lito (long id_ige, double h0, double h1);
	
	void Apply_Lito0();

	void ApplyLito_well_ige_podoshva();
	void ApplyLito_well_lito_podoshva();

	DB_Voda m_db_voda;
	void Voda(long horizont,
		double hv_z, double hv_v,
		SYSTEMTIME dv);
	void ApplyVoda();

	double GetW()        {return m_w;}
	void   SetW(double w){m_w = w;}
};

#define DYNAMOMETR_KAR_NAME "dynamometr"
#define MANOMETR_KAR_NAME "manometr"
#define PCK_KAR_NAME "pck"
#define PCB_KAR_NAME "pcb"
#define PCB_PCK_KAR_NAME "pcb_per_psk"

#define PALJA_DB_KAR_NAME "palja_db"

#define SVAI_20_20_KAR_NAME "svai_20x20"
#define SVAI_25_25_KAR_NAME "svai_25x25"
#define SVAI_30_30_KAR_NAME "svai_30x30"
#define SVAI_35_35_KAR_NAME "svai_35x35"
#define SVAI_40_40_KAR_NAME "svai_40x40"

#define DEFORMATION_MODUL_KAR_NAME "deformation_modul"
#define UDELNOE_SCEPLENIE_KAR_NAME "udelnoe_sceplenie"
#define UGOL_VNUTRENNEGO_TRENIA_KAR_NAME "udol_vnutrennego_trenia"

#define TEST_PESOK_OR_GLINA_KAR_NAME "pesok_minus1_glina1"

#endif // !defined(AFX_DRILL_3D_H__446F8BA8_EDA9_42C6_AECC_2F9A8FCF8080__INCLUDED_)
