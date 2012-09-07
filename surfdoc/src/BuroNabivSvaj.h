#pragma once
#include <windows.h>
class SurfDoc;
class Svaj
{
	enum SvaiType
	{
		undefined = 0,
		zabivn,
		buro_nabiv,
		type_3,
		type_4,
		last
	};
	static const char * SvaiTypeToString(Svaj::SvaiType svai_type);
};
class ZabivnSvaj
{
public:
	enum ParamType
	{
		none = 0,
		h,
		h_from_rostverk,
		V,
		R,
		RA,
		f_i,
		gamma_cf,
		sum_gamma_cf_fi_hi,
		u_sum_gamma_cf_fi_hi,
		RA_plus_u_sum_gamma_cf_fi_hi,
		gamma_c,
		Fd,
		Fd_per_V,
		N,
		N_per_V,
		end
	};
	static const char * ParamTypeToString(ZabivnSvaj::ParamType param_type);
	enum SvaiType
	{
		undefined = 0,
		last
	};
	static const char * SvaiTypeToString(ZabivnSvaj::SvaiType svai_type);
};
#define BuroNabivSvaj_npages 2

class BuroNabivSvaj
{
public:
	enum ParamType
	{
		none = 0,
		h,
		h_per_d,
		h_from_rostverk,
		V,
		alpha1,
		alpha2,
		alpha3,
		alpha4,
		gamma_,
		sum_gamma_h,
		R,
		RA,
		f_i,
		gamma_cf,
		integral_gamma_cf_fi_hi,
		sum_gamma_cf_fi_hi,
		u_sum_gamma_cf_fi_hi,
		RA_plus_u_sum_gamma_cf_fi_hi,
		gamma_c,
		Fd,
		Fd_per_V,
		N,
		N_per_V,
		end
	};
	static const char * ParamTypeToString(BuroNabivSvaj::ParamType param_type);
	enum SvaiType
	{
		undefined = 0,
		nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom,
		nabivn_vibroshtampovan,
		burov_betonir_bez_vody_ili_s_obsadnoj_truboj,
		burov_betonir_pod_vodoj_ili_pod_glin_rr,
		burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom,
		buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik,
		svai_obolochki_pogr_vibrir_s_vyemkoj_grunta,
		svai_stolby,
		buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj,
		custom,
		last
	};
	static const char * SvaiTypeToString(BuroNabivSvaj::SvaiType svai_type, double v_custom_gamma_cf[4]);
	static const char * SvaiTypeToString(BuroNabivSvaj::SvaiType svai_type);

	// Массив описаний страниц блокнота
	PROPSHEETPAGE   psheetPage[BuroNabivSvaj_npages];

	// Заголовок блокнота
	PROPSHEETHEADER psheetHeader;

	// Идентификаторы страниц блокнота
	HPROPSHEETPAGE hPage[BuroNabivSvaj_npages];

	static BOOL CALLBACK DlgProcAdditionals( HWND hDlg, UINT uMsg,
								WPARAM wParam, LPARAM lParam );
	static BOOL CALLBACK DlgProcSvaiBuroNabivnie( HWND hDlg, UINT uMsg,
								WPARAM wParam, LPARAM lParam );
	static int CALLBACK PropSheetProc(HWND hwndDlg,
									UINT uMsg,
									LPARAM lParam);
	void Dialog(SurfDoc * doc);

	SurfDoc * pSurfDoc;


	int index_cub_internal_friction_angle;
	int index_cub_specific_gravity_of_ground;
	int index_surface_of_relief;
	int index_surface_of_rostverk;
	int index_cub_fluidity_index;

	bool use_rostverk_altituda;

	bool use_water_saturation;
	int index_cub_specific_gravity_of_suspended_in_water_ground;
	int index_cub_fluidity_index_of_water_saturated_ground;


	BuroNabivSvaj::ParamType s_buro_nabiv_svaj_param_type; 
	BuroNabivSvaj::SvaiType s_buro_nabiv_svaj_svai_type; 
	int index_buro_nabiv_svaj_param_type;
	int index_buro_nabiv_svaj_svai_type;

	bool use_cub_specific_gravity_of_ground;
	bool use_cub_fluidity_index;

	double d, gamma_k, rostverk_altituda;
	void Apply();
	bool EnableApply();

	bool decrease_clay_R_if_porosty;
	bool increase_fi_if_dense_sand;
	bool increase_fi_if_not_porosty_clay;

	double v_custom_gamma_cf[4];

};
inline BuroNabivSvaj::ParamType operator++( BuroNabivSvaj::ParamType &rs, int )
{
   return rs = (BuroNabivSvaj::ParamType)(rs + 1);
}
inline BuroNabivSvaj::SvaiType operator++( BuroNabivSvaj::SvaiType &rs, int )
{
   return rs = (BuroNabivSvaj::SvaiType)(rs + 1);
}
