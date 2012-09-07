
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GEOCUBE_MODULE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GEOCUBE_MODULE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef GEOCUBE_MODULE_EXPORTS
#define GEOCUBE_MODULE_API __declspec(dllexport)
#else
#define GEOCUBE_MODULE_API __declspec(dllimport)
#endif

// This class is exported from the geocube_module.dll
class GEOCUBE_MODULE_API CGeocube_module {
public:
	CGeocube_module(void);
	// TODO: add your methods here.
};

extern GEOCUBE_MODULE_API int nGeocube_module;

#include <windows.h>
#include <string>
#include <map>
#include <vector>
using namespace std;

GEOCUBE_MODULE_API int fnGeocube_module(void);

GEOCUBE_MODULE_API WPARAM dll_WinSurf();
GEOCUBE_MODULE_API WPARAM dll_StartWinSurfLoop();

class win_project;
class win_app;
class CLabDoc;

#include<atltime.h>
struct wells_draw_list_item;
#include "wells_draw_list_item_draw_mode_2d.h"
struct CubeSize;
#include <lab_numbers_reset_items.h>

class GEOCUBE_MODULE_API dll_win_project
{
	CLabDoc * m_pLabDoc;
public:

	win_app * app;
	win_project * w_project;
	win_project * w_project_window;
	win_project * w_project_window_less;
	dll_win_project(CLabDoc * pLabDoc);
	~dll_win_project();

	bool dll_WinSurf();
	void delete_Window_WinProject();

	void CreateWindowLess_WinProject();
	void ReCreateWindowLess_WinProject();

	void SetWindowLess_WinProject();
	void SetWindow_WinProject();

	bool Have_WinProject_Window();
	bool Have_WinProject_WindowLess();

	void LabNumberResetting(vector<lab_numbers_reset_item> & lab_numbers_reset_items);


	void LabExcludedList(HWND hWndParent);
	void LabLayerPropertyWindow(HWND hWndParent, long id_ige, long x, long y);
	void LabLayerNormatives(int type, long id_ige);
	void LabLayerChastnye(long id_ige);

	wells_draw_list_item * AddWellsDraw(int WellElement_type_t, bool check, float width,  bool to_end_of_vector, wells_draw_list_item_draw_mode_2d drawmode2d);

	void Set_ID_OBJ(long id_obj);

	void dll_win_project::DrawWells();
	void dll_win_project::AddWell(long id_kt, const char * name, long kt_idtyp, double X, double Y, double ustje, double zaboj, long id_bur_type, long d_bur, std::string data_bur, 
		wells_draw_list_item * wdli_podoshva_lito, 
		wells_draw_list_item * wdli_podoshva_ige, 
		wells_draw_list_item * wdli_hydro);
	
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

	void ApplyProps();

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

	void ApplyZriz();

	void Cilce0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
		double h, double d,
		double m_kolca,
		double m_grunta,
		double m_grunta_zamoch,
		double m_grunta_posle,
		double m_grunta_vysush);

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
		unsigned char id_method, unsigned char bStat, unsigned char bStatV);
	
	void ApplyCompress(bool use_compression3);

	void AddNewWellColomn_LaboratoryAnalizes_FromDB_2();


	
	void AddGranular(long id_kt, long id_prob, long id_gran, const char * gran_name, double val);
	void ApplyGranular();

	void ParseTrialIndications();

	void AfterExportFromDB(double _pressure_interval_01_02_0);

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
		double Kg, double Kf, double Bg, double Bf, double shtanga_d);

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


	void Lito0(long id_kt, long id_ige, double h0, double h1);
	void IGE0(long id_ige, long id_gr,
		const char * ige,
		double mk, double mkz,
		const char * strat, const char * desc0);
	void Lito(long id_kt, long id_ige, double h0, double h1);
	void IGE(long id_ige, long id_gr,
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

	void Rozrizy(
		long id_rozriz, const char * nomer, BYTE has_dxf, const char * fn_dxf,
		BYTE acad_yscale_loaded,
		double z1w, double y1a, double z2w, double y2a
		);
	void Rozriz(long id_rozriz, long npp, long id_kt, double dxf_x);
	void ApplyRozriz();

	void Voda(long id_kt, long horizont,
		double hv_z, double hv_v,
		SYSTEMTIME dv);
	void ApplyVoda();

	void MySurfer_skip_next_alert();
	void MySurfer_set_next_alert();

	void GridDataUsedAlg(long id_surf, BYTE /*use_surfer*/ griddata_app, long id_alg);
	void GridDataSurfaces(long id_surf, const char * nazva, BYTE podoshva, BYTE r, BYTE g, BYTE b, short z_flag, long id_umpoz, long id_ige);
	void GridData(long id_surf, long id_point,
		double x, double y, double z);
	void ApplyGridData();

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

	void SurfacesAutoBlank();

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

};
