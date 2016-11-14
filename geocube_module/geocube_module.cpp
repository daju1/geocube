// geocube_module.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "geocube_module.h"


//#include "./../surfdoc/src/Object.h"
//#include "./../surfdoc/src/SurfDoc.h"
//#include "../../wintools/src/winsurf.h"
//#include "../../wintools/src/utility.h"
//#include "../../laboratory/src/lab.h"
//#include "../../wintools/src/win32_app.h"
//#include "../../wintools/src/win32_project.h"
//#include "./../laboratory/src/lab.h"
//#include "../../test/test_lib/lab.h"






#include "./../wintools/src/winsurf.h"
#include "./../wintools/src/utility.h"
#include "./../wintools/src/win32_app.h"
#include "./../wintools/src/win32_project.h"


// Обеспечить общий доступ к данным для всех приложений, использующих DLL. 
//....................................
#pragma data_seg( ".GLOBALS" )
int nProcessCount = 0;
int nThreadCount = 0;
#pragma data_seg()

HINSTANCE hInst;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstDLL, 
					DWORD dwNotification,
					LPVOID lpReserved )
{
   switch(dwNotification)
   {
      case DLL_PROCESS_ATTACH :
		  {
			  // Здесь помещается код инициализации. Ранее 
			  // это была функция LibMain 16-разрядной DLL. 
			  //..................................................
			  hInst = hInstDLL;
			  nProcessCount++;
			  return( TRUE );
		  }
		  break;

      case DLL_PROCESS_DETACH :
		  {
			  // Здесь помещается код завершения. Ранее 
			  // это была функция WEP 16-разрядной DLL. 
			  //................................................
			  nProcessCount--;
		  }
		  break;

      case DLL_THREAD_ATTACH :
		  {
			  // Здесь помещается специальный код инициализации 
			  // для новых потоков.
			  // В результате DLL может самостоятельно               
			  // обеспечить защиту потоков.
			  //.......................................................
			  nThreadCount++;
		  }
		  break;

      case DLL_THREAD_DETACH :
		  {
			  // Здесь помещается код завершения для потоков.
			  //............................................              
			  nThreadCount--;
		  }
		  break;
   }
   return( FALSE );
}

// This is an example of an exported variable
GEOCUBE_MODULE_API int nGeocube_module=0;

// This is an example of an exported function.
GEOCUBE_MODULE_API int fnGeocube_module(void)
{
	return 42;
}


// This is the constructor of a class that has been exported.
// see geocube_module.h for the class definition
CGeocube_module::CGeocube_module()
{ 
	return; 
}

GEOCUBE_MODULE_API WPARAM dll_WinSurf()
{
	return WinSurf();
}

GEOCUBE_MODULE_API WPARAM dll_StartWinSurfLoop()
{
	return StartWinSurfLoop();
}





dll_win_project::dll_win_project(CLabDoc * pLabDoc) : w_project(this->w_project_window)
{
	this->m_pLabDoc = pLabDoc;
	app = NULL;
	w_project_window = NULL;
	w_project_window_less = NULL;
	w_project = NULL;
}
dll_win_project::~dll_win_project()
{
	if (app) delete app;
}
bool dll_win_project::dll_WinSurf()
{
	//singleton_cleaner<win_app> app_cleaner;
	app = win_app::GetInstance();  
	//app_cleaner.SetInstance(app);
	if (app && app->GetWinProject())
	{
		app->GetWinProject()->SetApp(app);
		this->w_project_window = app->GetWinProject();
		w_project = this->w_project_window;
		if (this->w_project_window)
		{
			this->w_project_window->InitLabDoc(this->m_pLabDoc);
			ShowWindow(this->w_project_window->hSurfWnd, 1);
		}
		//return StartWinSurfLoop();
		return true;
	}
	else
	{
		this->w_project_window = NULL;
		w_project = this->w_project_window;
		return false;
	}
}
void dll_win_project::delete_Window_WinProject()
{
	DestroyWindow(this->w_project_window->hSurfWnd);
	if (app) delete app;
	app = NULL;
	this->w_project_window = NULL;
	this->w_project = NULL;
}


void dll_win_project::CreateWindowLess_WinProject()
{
	w_project_window_less = new win_project();
	w_project = this->w_project_window_less;

}
void dll_win_project::ReCreateWindowLess_WinProject()
{
	if (w_project_window_less != NULL) delete w_project_window_less;
	w_project_window_less = new win_project();
	w_project = this->w_project_window_less;
}

void dll_win_project::SetWindowLess_WinProject()
{
	w_project = this->w_project_window_less;
}

void dll_win_project::SetWindow_WinProject()
{
	w_project = this->w_project_window;
}

bool dll_win_project::Have_WinProject_Window()
{
	return w_project_window != NULL;
}

bool dll_win_project::Have_WinProject_WindowLess()
{
	return w_project_window_less != NULL;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void dll_win_project::LabNumberResetting(vector<lab_numbers_reset_item> & lab_numbers_reset_items)
{
	if (this->w_project_window_less)
	{
		this->w_project_window_less->LabNumberResetting(lab_numbers_reset_items);
	}
}

void dll_win_project::LabExcludedList(HWND hWndParent)
{
	if (this->w_project)
	{
		this->w_project->LabExcludedList(hWndParent);
	}
}

void dll_win_project::LabLayerPropertyWindow(HWND hWndParent, long id_ige, long x, long y)
{
	if (this->w_project)
	{
		this->w_project->LabLayerPropertyWindow(hWndParent, id_ige, x, y);
	}
}
void dll_win_project::LabLayerChastnye(long id_ige)
{
	if (this->w_project)
	{
		this->w_project->LabLayerChastnye(id_ige);
	}
}	

void dll_win_project::LabLayerNormatives(int type, long id_ige)
{
	if (this->w_project)
	{
		this->w_project->LabLayerNormatives(type, id_ige);
	}
}



void dll_win_project::AddWell(long id_kt, const char * name, long kt_idtyp, double X, double Y, double ustje, double zaboj, long id_bur_type, long d_bur, string data_bur,
							  	wells_draw_list_item * wdli_podoshva_lito, 
							  	wells_draw_list_item * wdli_podoshva_ige, 
								wells_draw_list_item * wdli_hydro)
{
	if (this->w_project)
	{
		if (!this->w_project->FindWell(id_kt))
		{
			Well_3D drill(this->w_project);
			this->w_project->m_drills.AddMsg(&drill);
			this->w_project->m_drills.GetLastMsg().ReinitWellColomnsPointers();

			int i_colomn_podoshva_lito = -1;
			int i_colomn_podoshva_ige = -1;
			int i_colomn_hydro_projavlenie = -1;

			if (wdli_podoshva_lito)
				i_colomn_podoshva_lito = this->w_project->m_drills.GetLastMsg().AddNewWellColomn(WellElement::type::litho_podoshva, wdli_podoshva_lito);
			if (wdli_podoshva_ige)
				i_colomn_podoshva_ige = this->w_project->m_drills.GetLastMsg().AddNewWellColomn(WellElement::type::IGE_podoshva, wdli_podoshva_ige);
			if (wdli_hydro)
				i_colomn_hydro_projavlenie = this->w_project->m_drills.GetLastMsg().AddNewWellColomn(WellElement::type::hydro_projavlenie, wdli_hydro);

/*
			WellColomn * w_colomn_podoshva_lito = NULL;
			WellColomn * w_colomn_podoshva_ige = NULL;
			WellColomn * w_colomn_hydro_projavlenie = NULL;
			if (i_colomn_podoshva_lito > -1)
				w_colomn_podoshva_lito = &well.well_colomns[i_colomn_podoshva_lito];
			if (i_colomn_podoshva_ige > -1)
				w_colomn_podoshva_ige = &well.well_colomns[i_colomn_podoshva_ige];
			if (i_colomn_hydro_projavlenie > -1)
				w_colomn_hydro_projavlenie = &well.well_colomns[i_colomn_hydro_projavlenie];
*/

			this->w_project->m_drills.GetLastMsg().WellInit(id_kt, name, kt_idtyp, X, Y, ustje, zaboj, id_bur_type, d_bur, data_bur);
		}
	}
}
void dll_win_project::Set_ID_OBJ(long id_obj)
{
	if (this->w_project)
	{
		return this->w_project->Set_ID_OBJ(id_obj);
	}
}

wells_draw_list_item * dll_win_project::AddWellsDraw(int WellElement_type_t, bool check, float width,  bool to_end_of_vector, wells_draw_list_item_draw_mode_2d drawmode2d)
{
	if (this->w_project)
	{
		return this->w_project->AddWellsDraw(WellElement::type(WellElement_type_t), check, width,  to_end_of_vector, (wells_draw_list_item::draw_mode_2d)drawmode2d);
	}
	return NULL;
}

void dll_win_project::DrawWells()
{
	if (this->w_project)
	{
		this->w_project->m_drills_ObjectList.Init(this->w_project->m_drills, this->w_project);
		this->w_project->ZoomView();
		//this->w_project->Draw();
		//this->w_project->UpdateAllViews();
	}
}

void dll_win_project::AddNewWellColomn_LaboratoryAnalizes_FromDB(long id_obj, const char * contract, const char * object_name)
{
	if (this->w_project)
	{
		this->w_project->AddNewWellColomn_LaboratoryAnalizes_FromDB(id_obj, contract, object_name);
	}
}

void dll_win_project::AddPrGrunt(long id_obj, long id_kt, const char * kt_name, long kt_idtyp, long id_prob, double depth,
								 long lab_n, long id_kodprob, long id_gr, const char * soil_name, const char * grunt_name,
								 long id_ige)
{
	if (this->w_project)
	{
		this->w_project->AddPrGrunt(id_obj, 
			id_kt, kt_name, kt_idtyp, id_prob, depth,
			lab_n, id_kodprob, id_gr, soil_name, grunt_name,
			id_ige);	
	}
}
void dll_win_project::AddProp(
	long id_kt, long id_prob, 
	long id_vyprob, long id_param, const char * param_name, double val, unsigned char bStat
	)
{
	if (this->w_project)
	{
		this->w_project->AddProp(
				id_kt,
				id_prob, id_vyprob,
				id_param, param_name, val, bStat);	
	}
}

void dll_win_project::Zriz_tbl(
	long id_kt, long id_prob, long id_vyprob, long id_kolca, 	
	double sigma, double tau, double w_do, double ro_do, double w_po_upl, double ro_po_upl, double w_after, double ro_after, unsigned char bStat
	)
{
	if (this->w_project)
	{
		this->w_project->Zriz_tbl(
				id_kt,
				id_prob, id_vyprob, id_kolca, 
				sigma, tau, w_do, ro_do, w_po_upl, ro_po_upl, w_after, ro_after, bStat);	
	}
}
void dll_win_project::Zriz0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
	double h, double d, double dh_po_upl,
	double m_kolca,
	double m_grunta,
	double m_grunta_zamoch,
	double m_grunta_posle_uplot,
	double m_grunta_posle,
	double m_grunta_vysush)
{
	if (this->w_project)
	{
		this->w_project->Zriz0(
				id_kt, id_prob, id_vyprob, id_kolca, id_phys_vyprob,
				h, d, dh_po_upl,
				m_kolca,
				m_grunta,
				m_grunta_zamoch,
				m_grunta_posle_uplot,
				m_grunta_posle,
				m_grunta_vysush);	
	}
}

void dll_win_project::Zriz(
	long id_kt, long id_prob, long id_vyprob, 	
	long id_hid, long id_shema, long id_stan, double tgfi, double c, double d, double h, unsigned char bStat
	)
{
	if (this->w_project)
	{
		this->w_project->Zriz(
				id_kt,
				id_prob, id_vyprob,
				id_hid, id_shema, id_stan, tgfi, c, d, h, bStat);	
	}
}

void dll_win_project::ApplyGranular()
{
	if (this->w_project)
	{
		this->w_project->ApplyGranular();	
	}
}
void dll_win_project::ApplyProps()
{
	if (this->w_project)
	{
		this->w_project->ApplyParams();	
	}
}

void dll_win_project::ApplyZriz()
{
	if (this->w_project)
	{
		this->w_project->ApplyZriz();	
	}
}
void dll_win_project::Compress(
	long id_kt, long id_prob, long id_vyprob, 	
	double sigma, double dh1, double dh2, unsigned char voda, unsigned char bStat
	)
{
	if (this->w_project)
	{
		this->w_project->Compress(
				id_kt,
				id_prob, id_vyprob,
				sigma, dh1, dh2, voda, bStat);	
	}
}
void dll_win_project::Cilce0(long id_kt, long id_prob, long id_vyprob, long id_kolca, long id_phys_vyprob,
	double h, double d,
	double m_kolca,
	double m_grunta,
	double m_grunta_zamoch,
	double m_grunta_posle,
	double m_grunta_vysush)
{
	if (this->w_project)
	{
		this->w_project->Cilce0(
			id_kt, id_prob, id_vyprob, id_kolca, id_phys_vyprob,
			10.0*h, 10.0*d, 
			m_kolca,
			m_grunta,
			m_grunta_zamoch,
			m_grunta_posle,
			m_grunta_vysush);
	}	
}
void dll_win_project::Compress(
	long id_kt, long id_prob, long id_vyprob, 	
	double h, double d, 
	double es_l1, double es_r1, double es_l2, double es_r2,
	double nju, double nju_z,
	double m01, double E1, double m02, double E2,
	double m01v, double E1v, double m02v, double E2v,
	unsigned char id_method, unsigned char bStat, unsigned char bStatV
	)
{
	if (this->w_project)
	{
		this->w_project->Compress(
				id_kt, id_prob, id_vyprob,
				h, d, 
				es_l1, es_r1, es_l2, es_r2,
				nju, nju_z,
				m01, E1, m02, E2,
				m01v, E1v, m02v, E2v,
				id_method, bStat, bStatV
				);	
	}
}
void dll_win_project::ApplyCompress(bool use_compression3)
{
	if (this->w_project)
	{
		this->w_project->ApplyCompress(use_compression3);	
	}
}
void dll_win_project::AddNewWellColomn_LaboratoryAnalizes_FromDB_2()
{
	if (this->w_project)
	{
		this->w_project->AddNewWellColomn_LaboratoryAnalizes_FromDB_2();
	}
}

void dll_win_project::AddGranular(long id_kt, long id_prob, long id_gran, const char * gran_name, double val)
{
	if (this->w_project)
	{
		this->w_project->AddGranular(id_kt, id_prob, id_gran, gran_name, val);
	}
}


void dll_win_project::ParseTrialIndications()
{
	if (this->w_project)
	{
		this->w_project->ParseTrialIndications();
	}
}

void dll_win_project::AfterExportFromDB(double _pressure_interval_01_02_0)
{
	if (this->w_project)
	{
		this->w_project->AfterExportFromDB(_pressure_interval_01_02_0);
	}
}
void dll_win_project::PCK2Fiz_CalcParams(long id_calc_param, const char * calc_param, const char * desc)
{
	if (this->w_project)
	{
		this->w_project->PCK2Fiz_CalcParams(id_calc_param, calc_param, desc);
	}
}

void dll_win_project::PCK2FizResults(long id_kt, long npp, long id_calc_param, double param)
{
	if (this->w_project)
	{
		this->w_project->PCK2FizResults(id_kt, npp, id_calc_param, param);
	}
}

void dll_win_project::StZond(
	long id_kt, long npp, long typgr,
	double h, double q0, double f0, 
	double dh, double fsr, 
	unsigned char bStat,
	long id_ige, double pck
	)
{
	if (this->w_project)
	{
		this->w_project->StZond(
			id_kt, npp, typgr,
			h, q0, f0, 
			dh, fsr, bStat,
			id_ige, pck);	
	}
}
void dll_win_project::PtStZond(
	long id_kt, long id_ust, double glyb,
	const char * ust_name,
	long typ_zond, long n_shema,
	double Kg, double Kf, double Bg, double Bf, double shtanga_d)
{
	if (this->w_project)
	{
		this->w_project->PtStZond(
			id_kt, id_ust, glyb,
			ust_name,
			typ_zond,
			n_shema,
			Kg, Kf, Bg, Bf, shtanga_d);	
	}
}

void dll_win_project::Palja(
	long id_kt,
	double h, double qc, double beta1, double Rs, double fs, double beta2, double f, double RsA, double fhu, double Fu)
{
	if (this->w_project)
	{
		this->w_project->Palja(
			id_kt,
			h, qc, beta1, Rs, fs, beta2, f, RsA, fhu, Fu);
	}
}
void dll_win_project::PtPalja(
	long id_kt, long id_typ,
	double pereriz_x, double pereriz_y, double A, double u, double glyb, double RsA, double fhu, double pz,
	long id_snip, double Fu)
{
	if (this->w_project)
	{
		this->w_project->PtPalja(
			id_kt, id_typ,
			pereriz_x, pereriz_y, A, u, glyb, RsA, fhu, pz, id_snip, Fu);
	}
}
void dll_win_project::ApplyPalja()
{
	if (this->w_project)
	{
		this->w_project->ApplyPalja();	
	}
}
void dll_win_project::ApplyStZond()
{
	if (this->w_project)
	{
		this->w_project->ApplyStZond();	
	}
}
void dll_win_project::Lito0(
	long id_kt, long id_ige, double h0,	double h1
	)
{
	if (this->w_project)
	{
		this->w_project->Lito0(id_kt, id_ige, h0, h1);	
	}
}

void dll_win_project::Lito(
	long id_kt, long id_ige, double h0,	double h1
	)
{
	if (this->w_project)
	{
		this->w_project->Lito(id_kt, id_ige, h0, h1);	
	}
}

void dll_win_project::IGE(
	long id_ige, long id_gr,
	const char * ige,
	double mk, double mkz,
	const char * strat, const char * desc0)
{
	if (this->w_project)
	{
		this->w_project->IGE(id_ige, id_gr, ige, mk, mkz, strat, desc0);	
	}
}

void dll_win_project::IGE0(
	long id_ige, long id_gr,
	const char * ige,
	double mk, double mkz,
	const char * strat, const char * desc0)
{
	if (this->w_project)
	{
		this->w_project->IGE0(id_ige, id_gr, ige, mk, mkz, strat, desc0);	
	}
}

void dll_win_project::Grunty(
	long id_gr,
	const char * nazva_u, const char * nazva_r,
	long typgr, long typgr_pck, long id_normatyv, long id_grcons, long id_uklad, long id_nju, long id_grmain, long id_umpoz, long id_genezis)
{
	if (this->w_project)
	{
		this->w_project->Grunty(id_gr,
				nazva_u, nazva_r,
				typgr, typgr_pck, id_normatyv, id_grcons, id_uklad, id_nju, id_grmain, id_umpoz, id_genezis);	
	}
}
void dll_win_project::Genezis(long id_genezis,
	const char * nazva_u, const char * nazva_r,
	long id_normatyv, long id_grmain,
	const char * index,
	BYTE r, BYTE g, BYTE b)
{
	if (this->w_project)
	{
		this->w_project->Genezis(id_genezis,
			nazva_u, nazva_r,
			id_normatyv, id_grmain,
			index,
			r, g, b);
	}
}
void dll_win_project::UmPoz(long id_umpoz,
	const char * umpoz, const char * hatchacad,
	double angle, double scale)
{
	if (this->w_project)
	{
		this->w_project->UmPoz(id_umpoz,
			umpoz, hatchacad,
			angle, scale);
	}
}
void dll_win_project::ApplyLito()
{
	if (this->w_project)
	{
		this->w_project->ApplyLito();
	}
}
void dll_win_project::Rozrizy(
	long id_rozriz, const char * nomer, BYTE has_dxf, const char * fn_dxf,
	BYTE acad_yscale_loaded,
	double z1w, double y1a, double z2w, double y2a
	)
{
	if (this->w_project)
	{
		this->w_project->Rozrizy(id_rozriz, nomer, has_dxf, fn_dxf, acad_yscale_loaded,
			z1w, y1a, z2w, y2a);	
	}
}
void dll_win_project::Rozriz(
	long id_rozriz, long npp, long id_kt, double dxf_x
	)
{
	if (this->w_project)
	{
		this->w_project->Rozriz(id_rozriz, npp, id_kt, dxf_x);
	}
}
void dll_win_project::ApplyRozriz()
{
	if (this->w_project)
	{
		this->w_project->ApplyRozriz();
	}
}

void dll_win_project::Voda(long id_kt, long horizont,
	double hv_z, double hv_v,
	SYSTEMTIME dv)
{
	if (this->w_project)
	{
		this->w_project->Voda(id_kt, horizont, hv_z, hv_v, dv);	
	}
}
void dll_win_project::ApplyVoda()
{
	if (this->w_project)
	{
		this->w_project->ApplyVoda();
	}
}
void dll_win_project::GridDataSurfaces(long id_surf, const char * nazva,
	BYTE podoshva, BYTE r, BYTE g, BYTE b, short z_flag, long id_umpoz, long id_ige)
{
	if (this->w_project)
	{
		this->w_project->GridDataSurfaces(id_surf, nazva, podoshva, r, g, b, z_flag, id_umpoz, id_ige);
	}
}

void dll_win_project::MySurfer_skip_next_alert()
{
	if (this->w_project)
	{
		this->w_project->MySurfer_skip_next_alert();
	}
}

void dll_win_project::GridDataUsedAlg(long id_surf, BYTE griddata_app, long id_alg)
{
	if (this->w_project)
	{
		//и по заданныи алгоритмам формируем поверхности 
		this->w_project->GridDataUsedAlg(id_surf, griddata_app, id_alg);;	
	}
}
void dll_win_project::MySurfer_set_next_alert()
{
	if (this->w_project)
	{
		this->w_project->MySurfer_set_next_alert();
	}
}

void dll_win_project::GridData(long id_surf, long id_point,
	double x, double y, double z)
{
	if (this->w_project)
	{
		this->w_project->DBGridData(id_surf, id_point, x, y, z);;	
	}
}
void dll_win_project::ApplyGridData()
{
	if (this->w_project)
	{
		this->w_project->ApplyDBGridData();
	}
}
void dll_win_project::SurfLitoMapping(long id_surf, long id_ige)
{
	if (this->w_project)
	{
		this->w_project->SurfLitoMapping(id_surf, id_ige);
	}
}
void dll_win_project::SurfIgeMapping(long id_surf, long id_ige)
{
	if (this->w_project)
	{
		this->w_project->SurfIgeMapping(id_surf, id_ige);
	}
}
void dll_win_project::SurfacesOrder(long npp, BYTE check, long id_surf, BYTE podoshva, BYTE check2)
{
	if (this->w_project)
	{
		this->w_project->SurfacesOrder(npp, check, id_surf, podoshva, check2);
	}
}
void dll_win_project::SurfacesBlankOrder(long npp, long id_surf, BYTE podoshva,
		BYTE check_blank_me,
		BYTE check_blank_me_up,
		BYTE check_blank_me_up_above,
		BYTE check_blank_me_down,
		BYTE check_blank_me_down_above,
		BYTE check_blank_by_me_up,
		BYTE check_blank_by_me_down
	)
{
	if (this->w_project)
	{
		this->w_project->SurfacesBlankOrder(npp, id_surf, podoshva,
			check_blank_me,
			check_blank_me_up,
			check_blank_me_up_above,
			check_blank_me_down,
			check_blank_me_down_above,
			check_blank_by_me_up,
			check_blank_by_me_down);
	}
}

void dll_win_project::SurfacesBlankFuntions(/*long id_item, */long id_surf_obj, long id_surf_param, BYTE id_blank_fun)
{
	if (this->w_project)
	{
		this->w_project->SurfacesBlankFuntions(//id_item, 
			id_surf_obj, id_surf_param, id_blank_fun);
	}
}

void dll_win_project::ApplySurfacesOrder()
{
	if (this->w_project)
	{
		this->w_project->ApplySurfacesOrder();	
	}
}
void dll_win_project::DefineCubeSize(CubeSize & cube_size)
{
	if (this->w_project)
	{
		this->w_project->DefineCubeSize(cube_size);	
	}
}
void dll_win_project::DefineZoom(double zoomCoefXYZ, double zoomCoefXY)
{
	if (this->w_project)
	{
		this->w_project->DefineZoom(zoomCoefXYZ, zoomCoefXY);	
	}
}
void dll_win_project::SurfacesAutoBlank()
{
	if (this->w_project)
	{
		this->w_project->SurfacesAutoBlank();	
	}
}
void dll_win_project::OnViewPropertywindowwithPlot()
{
	if (this->w_project)
	{
		this->w_project->OnViewPropertywindowwithPlot();	
	}
}
void dll_win_project::OnViewPropertywindowwithResults()
{
	if (this->w_project)
	{
		this->w_project->OnViewPropertywindowwithResults();	
	}
}
void dll_win_project::OnViewPropertywindowwithLabnumbertriallist()
{
	if (this->w_project)
	{
		this->w_project->OnViewPropertywindowwithLabnumbertriallist();	
	}
}
void dll_win_project::OnViewPropertywindowwithNormatives()
{
	if (this->w_project)
	{
		this->w_project->OnViewPropertywindowwithNormatives();	
	}
}
void dll_win_project::OnViewPropertywindowwithCorrelation()
{
	if (this->w_project)
	{
		this->w_project->OnViewPropertywindowwithCorrelation();	
	}
}
void dll_win_project::OnViewPropertywindowwithNormativesbyallexperiences()
{
	if (this->w_project)
	{
		this->w_project->OnViewPropertywindowwithNormativesbyallexperiences();	
	}
}

bool dll_win_project::Get_Laboratory_context_with_plot()
{
	if (this->w_project)
	{
		return this->w_project->Get_Laboratory_context_with_plot();	
	}
	return true;
}
bool dll_win_project::Get_LabNumber_context_with_results()
{
	if (this->w_project)
	{
		return this->w_project->Get_LabNumber_context_with_results();	
	}
	return true;
}
bool dll_win_project::Get_LabLayer_context_with_lab_number_trial_list()
{
	if (this->w_project)
	{
		return this->w_project->Get_LabLayer_context_with_lab_number_trial_list();	
	}
	return true;
}
bool dll_win_project::Get_LabLayer_context_with_normatives()
{
	if (this->w_project)
	{
		return this->w_project->Get_LabLayer_context_with_normatives();	
	}
	return true;
}
bool dll_win_project::Get_LabLayer_context_with_korrelation()
{
	if (this->w_project)
	{
		return this->w_project->Get_LabLayer_context_with_korrelation();	
	}
	return true;
}
bool dll_win_project::Get_LabLayer_context_with_normatives_by_all_experiences()
{
	if (this->w_project)
	{
		return this->w_project->Get_LabLayer_context_with_normatives_by_all_experiences();	
	}
	return true;
}

