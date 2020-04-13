// AutoBuildProfileDlg.cpp: implementation of the AutoBuildProfileDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <cderr.h>
#endif
#include <vector>
using namespace std;

#include "../../alglib-3.1.0/cpp/src/specialfunctions.h"
#include "Grid.h"

#if !VIEW_ONLY_VERSION
#include "AutoBuildProfileDlg.h"
#include "../../array/src/sorting.h"
#include "../../tools/src/filedlg.h"
#include "../../array/src/Vdouble.h"
#include "../../array/src/interp.h"
#include "../../array/src/matrixes.h"
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include "../../winplot/src/winplot.h"
#include "../../wintools/src/winsurf.h"
#include "../../resource.h"
#include "SurfDoc.h"
#include "../mylicense.h"
#else
#include <QDateTime>
#include <QFileDialog>
#include <QDebug>
#endif

#include "../../auto_build_3D/picks_search.h"
#include "./../array/src/slau.h"
#include "cube.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HINSTANCE hInst;   // текущий экземпляр
//extern char directory[];
extern char szPath[];
extern char dir_out[];


bool FormMinSquareMatrix(char * fn_operator_wav, char * fn_min_sq_mat, double alpha);
void ErrorOfInverseProblemSolving(bool to_print, char * fn_operator, vector<double> & b, vector<double> & sol, string name, vector <double> & b_rec);

bool FillingTheMatrix3D(double smoof_power,
					  double k_oslablenie,// коэффициент ослабления
					  double k, // отношение глубины источника к полной (два плеча) длине аномалии
					  vector<SparseRow> * m,
					  char * filename,
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  double pw_dnp,
					  int wave_type
					  );
bool FillingTheMatrix3D_with_napravlennosty_diagramm(
	double k_oslablenie,// коэффициент ослабления
	vector<SparseRow> * m,
	char * filename,
	long rows, long cols, long pages,
	double x0, double y0, double z0,
	double delta_x, double delta_y, double delta_z,
	vector<double> & X,
	vector<double> & Y,
	vector<double> & Z,
	vector<vector<anten_direction> > & A,
	double pw_dnp,// степень диаграммы направленности приёмника
	double min_value,		
	int wave_type,
	sourse_power_model spm
	);
bool FillingTheMatrix3D_with_napravlennosty_diagramm_assume_tgdelta_much_more_than_one(
	int noise_color,
	double omega_min,
	double omega_max,
	double sigma,
	vector<SparseRow> * m,
	char * filename,
	long rows, long cols, long pages,
	double x0, double y0, double z0,
	double delta_x, double delta_y, double delta_z,
	vector<double> & X,
	vector<double> & Y,
	vector<double> & Z,
	vector<vector<anten_direction> > & A,
	double pw_dnp,// степень диаграммы направленности приёмника
	double min_value,
	int wave_type,
	sourse_power_model spm
	);
bool FillingTheMatrix3D_with_napravlennosty_diagramm(
					  double k_oslablenie,// коэффициент ослабления
					  char * filename,
					  double **** m,// указатель на три матрицы njuX, njuY, njuZ
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  vector<vector<anten_direction> > & A,
					  double pw_dnp,// степень диаграммы направленности приёмника
					  double min_value,
					  int wave_type,
					  sourse_power_model spm
					  );

void FillingTheMatrix3D_with_napravlennosty_diagramm_dipol(
	double k_oslablenie,// коэффициент ослабления
	double **** m,// указатель на три матрицы njuXr, njuYr, njuZr
	double **** R,// указатель на три матрицы rx, ry, rz
	long rows, long cols, long pages,
	double x0, double y0, double z0,
	double delta_x, double delta_y, double delta_z,
	vector<double> & X,
	vector<double> & Y,
	vector<double> & Z,
	vector<vector<anten_direction> > & A,
	double pw_dnp,// степень диаграммы направленности приёмника
	double min_value,
	int wave_type,
	sourse_power_model spm
					  );

double nju_phi_calc(double beta, double omega, 
					double rx, double ry, double rz, 
					double ax, double ay, double az);

void ddet_dbeta_domega_div_det(double beta, double omega, 
					double rx, double ry, double rz, 
					double ax, double ay, double az,

					double & ddet_dbeta_div_det,
					double & ddet_domega_div_det,
					double & d2det_dbeta2_div_det,
					double & d2det_domega2_div_det
					);

bool Dipol(int use_newton, 
		   int type, // тип прямой задачи
		   long cols,
		   bool apply_dgdni,		   
		   bool apply_dgdKTi,
		   bool apply_dgdep,
		   bool apply_dgdbeta,
		   bool apply_dgdomega,
		   bool apply_B,
		   vector<string> &names_of_colomns,
		   vector<size_t> &original_col_numbers,
		   int nFilesInDirectory,
		   vector<double> &vX,
		   vector<double> &vY,
		   vector<double> &vZ,
		   vector<vector<double> > &W,
		   vector<vector<anten_direction> > & A,
		   bool init_by_lamp,
		   // массив коэффициентов симметризации
		   vector<vector<double> > & S,
		   MyMethodsData3 &mmd3,
		   double DZ,
		   char * common_directory);
bool Lamp(int use_newton, int type, // тип прямой задачи
		   long cols,
		   bool apply_dgdni,		   
		   bool apply_dgdKTi,
		   bool apply_dgdep,
		   bool apply_B,
		   vector<string> &names_of_colomns,
		   vector<size_t> &original_col_numbers,
		   int nFilesInDirectory,
		   vector<double> &vX,
		   vector<double> &vY,
		   vector<double> &vZ,
		   vector<vector<double> > &W,
		   vector<vector<anten_direction> > & A,
		   bool only_init,
		   // массив коэффициентов симметризации
		   vector<vector<double> > & S,
		   MyMethodsData3 &mmd3,
		   double DZ,
		   char * common_directory);

template <class T> bool StoreMatrix(const char * filename, vector<T>& m, long cols);
template <class T> void LoadMatrix(const char * filename, vector<T>& m, long & cols);
void SparseStructureToSurferGrid(const char * fn_spm, char * fn_grd);

bool InverseProblem_Solving (bool to_print, const char * fn_operator_transponed, 
							 const char * fn_min_sq_mat,
							 const char * fn_Lt, 
							 vector<double> b, vector<double> & sol, double alpha, vector<double> sol_mean);
bool InverseProblem_Solving (bool to_print, const char * fn_operator_transponed, 
							 const char * fn_min_sq_mat, 
							 const char * fn_L, 
							 const char * fn_U, 
							 const char * fn_P, 
							 vector<double> b, vector<double> & sol, double alpha, vector<double> sol_mean);
void UseOneOfMyMethods3W_preparing(int type, // тип прямой задачи
					   int & ans_OP,
					   double z0, double z_min, double & DZ,
					   int & cols,
					   MyMethodsData3 & mmd3,					   
					   Wavelet3D & w3,
					   auto_build_parametrs & ab
					   );

void UseOneOfMyMethods3W(int type, // тип прямой задачи
					   bool granicy_kak_glubina, 
					   int & ans_OP,
					   double z0, double z_min,
					   int & cols,
					   MyMethodsData3 & mmd3,
					   Wavelet3D & w3,
					   auto_build_parametrs & ab,
					   vector<double> & X,
					   vector<double> & Y,
					   vector<double> & Z, // альтитуда измерений - полёта самолёта
					   vector<vector<anten_direction> > & A,
					   vector<double> & vModul,
					   vector<vector<double> > & v,
					   vector<string> & names_of_colomns,
					   vector<size_t> & original_col_numbers,

					   vector<vector <double> > & rec_signals,
					   vector <double> & rec_modul
					   );

bool Holesski3_in_operative_memory(char * fn_min_sq_mat, char * fn_Lt, char * dir, double alpha);
bool LUP_in_operative_memory(const char * fn_min_sq_mat, const char * fn_L, const char * fn_U, const char * fn_P, const char * dir, double alpha);

Grid4 * CreateProfileGrid3D( MyMethodsData3 & mmd );

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
WNDPROC wpOrigAutoBuildProfileWndProc; 

LRESULT APIENTRY AutoBuildProfileWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 

    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
    if (uMsg == WM_PAINT ) 
	{
		AutoBuildProfileDlg * dlg = 
			(AutoBuildProfileDlg *)GetWindowLongPtr(hwnd,GWLP_USERDATA);
		if (dlg) dlg->m_plotWnd.OnPaint(hwnd);
	} 
    return CallWindowProc(wpOrigAutoBuildProfileWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 


LRESULT CALLBACK DlgProcAutoBuildProfile( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static AutoBuildProfileDlg * auto_build_dlg;

	switch( uMsg )
		
	{
    case WM_INITDIALOG :
		{
			auto_build_dlg = reinterpret_cast<AutoBuildProfileDlg *>(lParam);
			if(auto_build_dlg)
			{
				auto_build_dlg->hDlg = hDlg;
				auto_build_dlg->OnInitDialog();
			}
		}
		break;
    case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_RADIO1:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.locals_algorithms_type = the_simple;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), false);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), false);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), false);
				}
			}
			break;
		case IDC_RADIO2:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.locals_algorithms_type = on_the_second_derivatives;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), true);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), true);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), true);
				}
			}
			break;
		case IDC_RADIO4:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.m_gradient_type = the_dividitial;
				}
			}
			break;
		case IDC_RADIO5:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.m_gradient_type = the_differential;
				}
			}
			break;		
		case IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.allow_sd_limit_quantil = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL) == BST_CHECKED;
					EnableWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), auto_build_dlg->m_ab.allow_sd_limit_quantil);
				}
			}
			break;

		case IDC_CHECK_POVTOR_ZAPRET:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_repeat_points = IsDlgButtonChecked( hDlg, IDC_CHECK_POVTOR_ZAPRET) 
						!= BST_CHECKED;
					EnableWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_POVTOR_ZAPRET), !auto_build_dlg->m_ab.use_repeat_points);
				}
			}
			break;
		case IDC_CHECK_TIME_COLOMN:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_time_colomn = IsDlgButtonChecked( hDlg, IDC_CHECK_TIME_COLOMN) == BST_CHECKED;
				}
			}
			break;
		case IDC_CHECK_USE_NUM_COL:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_num_col = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_NUM_COL) == BST_CHECKED;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_NUM_COLOMNS), auto_build_dlg->m_ab.use_num_col);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_BUTTON_BROSE_NUM_COLOMNS), auto_build_dlg->m_ab.use_num_col);
					
					if (auto_build_dlg->m_ab.use_num_col)
					{
						TCHAR str[4096];
						stprintf_s(str, 4096, _T("%s"), auto_build_dlg->m_ab.num_col_filename);
						SetDlgItemText(auto_build_dlg->hDlg, IDC_EDIT_NUM_COLOMNS, str);
					}
						
					auto_build_dlg->num_col_file_selected = false;
				}
			}
			break;
		case IDC_CHECK_USE_WHOLE_DIRECTORY:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_whole_directory = 
						IsDlgButtonChecked( hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY) == BST_CHECKED;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_DIRECTORY2), 
						auto_build_dlg->m_ab.use_whole_directory);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_LIST2), 
						auto_build_dlg->m_ab.use_whole_directory);
				}
			}
			break;
		case IDC_COMBO_DELIMITER:
			{								
				if(auto_build_dlg) 
				{
					switch(SendDlgItemMessage( hDlg, 
						IDC_COMBO_DELIMITER,
						CB_GETCURSEL,0,(LPARAM)0 ))
					{
					case 0:
						auto_build_dlg->m_ab.delim = ',';
						break;
					case 1:
						auto_build_dlg->m_ab.delim = ';';
						break;
					case 2:
						auto_build_dlg->m_ab.delim = '\t';
						break;
					case 3:
						auto_build_dlg->m_ab.delim = ' ';
						break;
					}
				}
			}
			break;
		case IDC_CHECK_USE_LOCALS:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->ShowWindows_RelatedWith_CheckUseLocals();
				}
			}
			break;
		case IDC_CHECK_DIMA_AFTER_LOCALS:
		case IDC_CHECK_1_AFTER_LOCALS:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->ShowWindows_RelatedWith_Windows_Cycles2();
				}			
			}
			// do not break here!!!
		case IDC_CHECK_DIMA:
		case IDC_CHECK_1:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->ShowWindows_RelatedWith_Windows_Cycles();
				}
			}
			break;
		case IDC_BUTTON_BROSE_NUM_COLOMNS:
			{
				if(auto_build_dlg) 
				{
                    auto_build_dlg->OnButtonBrowseNumColomn();
				}
			}
			break;

		case IDOK :
			{
				if (auto_build_dlg) auto_build_dlg->OnButtonOK();
			}
			break;
		case IDCANCEL :
			{
//				hDlgModeless = NULL;
				EndDialog( hDlg, IDCANCEL );
			}
			break;
		}
		break;
		case WM_DESTROY :
			{
				if (auto_build_dlg) auto_build_dlg->OnDestroy();
			}
			break;
		default :
			return( FALSE );
	}
	return( TRUE );
}

LRESULT CALLBACK DlgProcAutoBuildProfile1( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static AutoBuildProfileDlg1 * auto_build_dlg;

	switch( uMsg )
		
	{
    case WM_INITDIALOG :
		{
			auto_build_dlg = reinterpret_cast<AutoBuildProfileDlg1 *>(lParam);
			if(auto_build_dlg)
			{
				auto_build_dlg->hDlg = hDlg;
				auto_build_dlg->OnInitDialog();
			}
		}
		break;
    case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_RADIO1:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.locals_algorithms_type = the_simple;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), false);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), false);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), false);
				}
			}
			break;
		case IDC_RADIO2:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.locals_algorithms_type = on_the_second_derivatives;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), true);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), true);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), true);
				}
			}
			break;
		case IDC_RADIO4:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.m_gradient_type = the_dividitial;
				}
			}
			break;
		case IDC_RADIO5:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.m_gradient_type = the_differential;
				}
			}
			break;		
		case IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.allow_sd_limit_quantil = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL) == BST_CHECKED;
					EnableWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), auto_build_dlg->m_ab.allow_sd_limit_quantil);
				}
			}
			break;

		case IDC_CHECK_POVTOR_ZAPRET:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_repeat_points = IsDlgButtonChecked( hDlg, IDC_CHECK_POVTOR_ZAPRET) 
						!= BST_CHECKED;
					EnableWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_POVTOR_ZAPRET), !auto_build_dlg->m_ab.use_repeat_points);
				}
			}
			break;
		case IDC_CHECK_TIME_COLOMN:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_time_colomn = IsDlgButtonChecked( hDlg, IDC_CHECK_TIME_COLOMN) == BST_CHECKED;
				}
			}
			break;
		case IDC_CHECK_USE_NUM_COL:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_num_col = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_NUM_COL) == BST_CHECKED;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_EDIT_NUM_COLOMNS), auto_build_dlg->m_ab.use_num_col);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_BUTTON_BROSE_NUM_COLOMNS), auto_build_dlg->m_ab.use_num_col);
					
					if (auto_build_dlg->m_ab.use_num_col)
					{
						TCHAR str[4096];
						stprintf_s(str, 4096, _T("%s"), auto_build_dlg->m_ab.num_col_filename);
						SetDlgItemText(auto_build_dlg->hDlg, IDC_EDIT_NUM_COLOMNS, str);
					}
						
					auto_build_dlg->num_col_file_selected = false;
				}
			}
			break;
		case IDC_CHECK_USE_WHOLE_DIRECTORY:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->m_ab.use_whole_directory = 
						IsDlgButtonChecked( hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY) == BST_CHECKED;
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_DIRECTORY2), 
						auto_build_dlg->m_ab.use_whole_directory);
					ShowWindow(GetDlgItem(auto_build_dlg->hDlg, IDC_LIST2), 
						auto_build_dlg->m_ab.use_whole_directory);
				}
			}
			break;
		case IDC_COMBO_DELIMITER:
			{								
				if(auto_build_dlg) 
				{
					switch(SendDlgItemMessage( hDlg, 
						IDC_COMBO_DELIMITER,
						CB_GETCURSEL,0,(LPARAM)0 ))
					{
					case 0:
						auto_build_dlg->m_ab.delim = ',';
						break;
					case 1:
						auto_build_dlg->m_ab.delim = ';';
						break;
					case 2:
						auto_build_dlg->m_ab.delim = '\t';
						break;
					case 3:
						auto_build_dlg->m_ab.delim = ' ';
						break;
					}
				}
			}
			break;
		case IDC_CHECK_USE_LOCALS:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->ShowWindows_RelatedWith_CheckUseLocals();
				}
			}
			break;
		case IDC_CHECK_DIMA_AFTER_LOCALS:
		case IDC_CHECK_1_AFTER_LOCALS:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->ShowWindows_RelatedWith_Windows_Cycles2();
				}			
			}
			// do not break here!!!
		case IDC_CHECK_DIMA:
		case IDC_CHECK_1:
			{
				if(auto_build_dlg) 
				{
					auto_build_dlg->ShowWindows_RelatedWith_Windows_Cycles();
				}
			}
			break;
		case IDC_BUTTON_BROSE_NUM_COLOMNS:
			{
				if(auto_build_dlg) 
				{
                    auto_build_dlg->OnButtonBrowseNumColomn();
				}
			}
			break;

		case IDOK :
			{
				if (auto_build_dlg) auto_build_dlg->OnButtonOK();
			}
			break;
		case IDCANCEL :
			{
//				hDlgModeless = NULL;
				EndDialog( hDlg, IDCANCEL );
			}
			break;
		}
		break;
		case WM_DESTROY :
			{
				if (auto_build_dlg) auto_build_dlg->OnDestroy();
			}
			break;
		default :
			return( FALSE );
	}
	return( TRUE );
}
#endif
//коэффициент корреляции
bool CorrelationCoefficient(vector<double> & v1, vector<double> & v2, double & k, double & Cov)
{
	size_t i, len = v1.size();

	if (len != v2.size())
		return false;

	double 
		sum1 = 0.0,
		sum2 = 0.0;

	for (i = 0; i < len; i++)
	{
		sum1 += v1[i];
		sum2 += v2[i];
	}

	double 
		mean1 = sum1 / len,
		mean2 = sum2 / len;

	double 
		sigma1 = 0.0,
		sigma2 = 0.0;

	Cov = 0.0;

	for (i = 0; i < len; i++)
	{
		sigma1 += (v1[i] - mean1)*(v1[i] - mean1);
		sigma2 += (v2[i] - mean2)*(v2[i] - mean2);
		Cov += (v1[i] - mean1)*(v2[i] - mean2);
	}

	k = Cov/sqrt(sigma1*sigma2);

	return true;
}


bool CorrelationProblem(const char * fn_operator_transponed, vector<double> & signal, vector<double> & v_korr, vector<double> & v_cov);


AutoBuildProfileDlg::AutoBuildProfileDlg(bool _consol, AutoBuildProfile * auto_build_profile, auto_build_parametrs& ab) : m_ab(ab)
{
	p_auto_build_profile = auto_build_profile;
	consol = _consol;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	DialogBoxParam( 
	   hInst, 
	   MAKEINTRESOURCE(IDD_DIALOG_AUTO_BUILD_PROFILE), 
	   NULL,
	   (DLGPROC)DlgProcAutoBuildProfile,
	   (LPARAM)this);
#endif

}

AutoBuildProfileDlg::~AutoBuildProfileDlg()
{

}
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
void AutoBuildProfileDlg::OnInitDialog()
{
	TCHAR str[1024];
	///////////////////////////////////////////////
	stprintf_s(str, 1024, _T("%f"), this->m_ab.k);
	SetDlgItemText(this->hDlg, IDC_EDIT_GLUBINA_K, str);
	///////////////////////////////////////////////
	stprintf_s(str, 1024, _T("%f"), this->m_ab.quantil_naklony);
	SetDlgItemText(this->hDlg, IDC_EDIT_NAKLON_QUANTIL, str);
	///////////////////////////////////////////////
	stprintf_s(str,1024,  _T("%f"), this->m_ab.peregib_krutizna_quantil);
	SetDlgItemText(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL, str);
	///////////////////////////////////////////////
	stprintf_s(str, 1024, _T("%f"), this->m_ab.win_velonsity);
	SetDlgItemText(this->hDlg, IDC_EDIT_WIN_STEP_VELONSITY, str);
	///////////////////////////////////////////////
	stprintf_s(str, 1024, _T("%f"), this->m_ab.minimum_of_signal);
	SetDlgItemText(this->hDlg, IDC_EDIT_MINIMUM_OF_SIGNAL, str);
	///////////////////////////////////////////////
	stprintf_s(str, 1024, _T("%f"), this->m_ab.limit_dima);
	SetDlgItemText(this->hDlg, IDC_EDIT_LIMIT_DIMA, str);
	///////////////////////////////////////////////
	stprintf_s(str, 1024, _T("%f"), this->m_ab.limit_1);
	SetDlgItemText(this->hDlg, IDC_EDIT_LIMIT_1, str);
	///////////////////////////////////////////////

	stprintf_s(str, 1024, _T("%d"), this->m_ab.n);
	SetDlgItemText(this->hDlg, IDC_EDIT_POVTOR_ZAPRET, str);
	///////////////////////////////////////////////

	

	
	

	
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_DIMA, this->m_ab.use_window_cycles_algorithm_dima);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_1, this->m_ab.use_window_cycles_algorithm_1);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_LOCALS, this->m_ab.use_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_DIMA_AFTER_LOCALS, this->m_ab.use_window_cycles_algorithm_dima_after_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_1_AFTER_LOCALS, this->m_ab.use_window_cycles_algorithm_1_after_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL, this->m_ab.allow_sd_limit_quantil);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_POVTOR_ZAPRET, !this->m_ab.use_repeat_points);
	EnableWindow(GetDlgItem(this->hDlg, IDC_EDIT_POVTOR_ZAPRET), !this->m_ab.use_repeat_points);
	///////////////////////////////////////////////
	
	CheckDlgButton(this->hDlg, IDC_CHECK_TIME_COLOMN, this->m_ab.use_time_colomn);
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_NUM_COL, this->m_ab.use_num_col);
	ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_NUM_COLOMNS), this->m_ab.use_num_col);
	ShowWindow(GetDlgItem(this->hDlg, IDC_BUTTON_BROSE_NUM_COLOMNS), this->m_ab.use_num_col);
	stprintf_s(str, 1024, _T("%s"), this->m_ab.num_col_filename);
	SetDlgItemText(this->hDlg, IDC_EDIT_NUM_COLOMNS, str);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY, this->m_ab.use_whole_directory);
	ShowWindow(GetDlgItem(this->hDlg, IDC_DIRECTORY2), 
		this->m_ab.use_whole_directory);
	ShowWindow(GetDlgItem(this->hDlg, IDC_LIST2), 
		this->m_ab.use_whole_directory);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN, this->m_ab.use_min);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MAX, this->m_ab.use_max);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN_MAX, this->m_ab.use_min_max);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN2, this->m_ab.use_min_2);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MAX2, this->m_ab.use_max_2);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN_MAX2, this->m_ab.use_min_max_2);
	///////////////////////////////////////////////

	switch (this->m_ab.m_gradient_type)
	{
	case the_dividitial:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO4,
				IDC_RADIO6,
				IDC_RADIO4);
		}
		break;
	case the_differential:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO4,
				IDC_RADIO6,
				IDC_RADIO5);
		}
		break;
	}


	this->ShowWindows_RelatedWith_CheckUseLocals();
	this->ShowWindows_RelatedWith_Windows_Cycles();
	


	for(size_t j = 0; j < 3; j++)
	{
		stprintf_s(str, 1024, _T("%u"), j);
		SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J , CB_ADDSTRING, 0, (LPARAM)str);
		SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2, CB_ADDSTRING, 0, (LPARAM)str);
	}

	SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J , CB_SETCURSEL, this->m_ab.start_j1, (LPARAM)0 );
	SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2, CB_SETCURSEL, this->m_ab.start_j2, (LPARAM)0 );

	num_col_file_selected = false;



			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)",");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)";");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"tabulation");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"space");
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_SETCURSEL,
				0,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    // Retrieve the handle to the Map control. 
    this->m_plotWnd.hwnd = GetDlgItem(hDlg, IDC_STATIC_AUTOBUILD_PROFILE); 

    // Subclass the edit control. 
    wpOrigAutoBuildProfileWndProc = (WNDPROC) SetWindowLongPtr(this->m_plotWnd.hwnd, 
        GWLP_WNDPROC, (LONG_PTR) AutoBuildProfileWndSubclassProc); 

	SetWindowLongPtr(this->m_plotWnd.hwnd, GWLP_USERDATA,(LONG_PTR)this);



}

void AutoBuildProfileDlg::OnButtonOK()
{
	char str[125];
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_GLUBINA_K, str, 124);
	this->m_ab.k = atof(str);
printf("this->m_ab.k = %f\n", this->m_ab.k);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_NAKLON_QUANTIL, str, 124);
	this->m_ab.quantil_naklony = atof(str);
printf("this->m_ab.quantil_naklony = %f\n", this->m_ab.quantil_naklony);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL, str, 124);
	this->m_ab.peregib_krutizna_quantil = atof(str);
printf("this->m_ab.peregib_krutizna_quantil = %f\n", this->m_ab.peregib_krutizna_quantil);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_WIN_STEP_VELONSITY, str, 124);
	this->m_ab.win_velonsity = atof(str);
printf("this->m_ab.win_velonsity = %f\n", this->m_ab.win_velonsity);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_MINIMUM_OF_SIGNAL, str, 124);
	this->m_ab.minimum_of_signal = atof(str);
printf("this->m_ab.minimum_of_signal = %f\n", this->m_ab.minimum_of_signal);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_LIMIT_DIMA, str, 124);
	this->m_ab.limit_dima = atof(str);
printf("this->m_ab.limit_dima = %f\n", this->m_ab.limit_dima);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_LIMIT_1, str, 124);
	this->m_ab.limit_1 = atof(str);
printf("this->m_ab.limit_1 = %f\n", this->m_ab.limit_1);
	///////////////////////////////////////////////


	GetDlgItemText(this->hDlg,IDC_EDIT_POVTOR_ZAPRET, str, 124);
	this->m_ab.n = atoi(str);
printf("this->m_ab.n = %d\n", this->m_ab.n);
	///////////////////////////////////////////////




	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima = IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_dima = %d\n", this->m_ab.use_window_cycles_algorithm_dima);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1 = IsDlgButtonChecked( hDlg, IDC_CHECK_1) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_1 = %d\n", this->m_ab.use_window_cycles_algorithm_1);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_dima_after_locals = %d\n", this->m_ab.use_window_cycles_algorithm_dima_after_locals);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_1_after_locals = %d\n", this->m_ab.use_window_cycles_algorithm_1_after_locals);

	///////////////////////////////////////////////
	this->m_ab.use_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_locals = %d\n", this->m_ab.use_locals);
	///////////////////////////////////////////////
	this->m_ab.allow_sd_limit_quantil = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL) == BST_CHECKED;
printf("this->m_ab.allow_sd_limit_quantil = %d\n", this->m_ab.allow_sd_limit_quantil);
	///////////////////////////////////////////////


	///////////////////////////////////////////////
	this->m_ab.use_repeat_points = IsDlgButtonChecked( hDlg, IDC_CHECK_POVTOR_ZAPRET) 
		!= BST_CHECKED;
printf("this->m_ab.use_repeat_points = %d\n", this->m_ab.use_repeat_points);
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	this->m_ab.use_max = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MAX) == BST_CHECKED;
printf("this->m_ab.use_max = %d\n", m_ab.use_max);
	///////////////////////////////////////////////
	this->m_ab.use_max_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MAX2) == BST_CHECKED;
printf("this->m_ab.use_max_2 = %d\n", m_ab.use_max_2);
	///////////////////////////////////////////////
	this->m_ab.use_min = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN) == BST_CHECKED;
printf("this->m_ab.use_min = %d\n", m_ab.use_min);
	///////////////////////////////////////////////
	this->m_ab.use_min_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN2) == BST_CHECKED;
printf("this->m_ab.use_min_2 = %d\n", m_ab.use_min_2);
	///////////////////////////////////////////////
	this->m_ab.use_min_max = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN_MAX) == BST_CHECKED;
printf("this->m_ab.use_min_max = %d\n", m_ab.use_min_max);
	///////////////////////////////////////////////
	this->m_ab.use_min_max_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN_MAX2) == BST_CHECKED;
printf("this->m_ab.use_min_max_2 = %d\n", m_ab.use_min_max_2);
	///////////////////////////////////////////////


	this->m_ab.start_j1 = SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J ,	CB_GETCURSEL,0,(LPARAM)0 );
	this->m_ab.start_j2 = SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2,	CB_GETCURSEL,0,(LPARAM)0 );
printf("this->m_ab.start_j1 = %d\n", this->m_ab.start_j1);
printf("this->m_ab.start_j2 = %d\n", this->m_ab.start_j2);


	if (this->m_ab.use_num_col && !num_col_file_selected)
	{
		MessageBox(hDlg, "Вы не выбрали имя файла с номерами колонок","AutoBuildProfileDlg",0);
		return;
	}

	if (this->m_ab.use_whole_directory)
	{
		UseWholeDirectory();
	}
	else
	{
		//AutoBuildProfile_main(consol, p_auto_build_profile, this->m_ab);
	}
}

void AutoBuildProfileDlg::ShowWindows_RelatedWith_Windows_Cycles2()
{
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////	
	int ids[] = {
		IDC_CHECK_LOCAL_MAX2,
			IDC_CHECK_LOCAL_MIN2,
			IDC_CHECK_LOCAL_MIN_MAX2,
			IDC_STATIC_INPUT_LOCALS
	};
	bool show = 
		this->m_ab.use_window_cycles_algorithm_1_after_locals ||
		this->m_ab.use_window_cycles_algorithm_dima_after_locals;

	for (size_t i = 0; i < sizeof(ids)/sizeof(int); i++)
	{
		ShowWindow(GetDlgItem(this->hDlg, ids[i]), show);
	}	
}
void AutoBuildProfileDlg::ShowWindows_RelatedWith_Windows_Cycles()
{
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1 = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_1) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////	
	int ids[] = {
		IDC_EDIT_LIMIT_DIMA,
			IDC_EDIT_LIMIT_1,
			IDC_STATIC_LIMIT,
			IDC_STATIC_MIN_SIGNAL,
			IDC_EDIT_MINIMUM_OF_SIGNAL,
			IDC_CHECK_POVTOR_ZAPRET,
			IDC_STATIC_POVTOR_ZAPRET, 
			IDC_EDIT_POVTOR_ZAPRET, 
			IDC_STATIC_WIN_LEN_PARAM,
			IDC_EDIT_WIN_STEP_VELONSITY,
			IDC_STATIC_WIN_STEP_VELONSITY,
			IDC_COMBO_START_WINDOW_LEN,
			IDC_STATIC_START_WINDOW_LEN,
			IDC_COMBO_END_WINDOW_LEN,
			IDC_STATIC_END_WINDOW_LEN,
			IDC_STATIC_GRADIENT_TYPE,
			IDC_RADIO4,
			IDC_RADIO5		
	};
	bool show = 
		this->m_ab.use_window_cycles_algorithm_1 ||
		this->m_ab.use_window_cycles_algorithm_1_after_locals ||
		this->m_ab.use_window_cycles_algorithm_dima ||
		this->m_ab.use_window_cycles_algorithm_dima_after_locals;

	for (size_t i = 0; i < sizeof(ids)/sizeof(int); i++)
	{
		ShowWindow(GetDlgItem(this->hDlg, ids[i]), show);
	}
}

void AutoBuildProfileDlg::ShowWindows_RelatedWith_CheckUseLocals()
{
	this->m_ab.use_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_USE_LOCALS) == BST_CHECKED;

	int ids[] = {
		IDC_EDIT_NAKLON_QUANTIL,
			IDC_STATIC_NAKLON_QUANTIL,
			IDC_COMBO_LOCALS_START_J,
			IDC_STATIC_LOCALS_START_J,
			IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL,
			IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL,
			IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL,
			IDC_RADIO1,
			IDC_RADIO2,

			IDC_STATIC_LOCALS_OUTPUT,
			IDC_CHECK_LOCAL_MAX, 
			IDC_CHECK_LOCAL_MIN,
			IDC_CHECK_LOCAL_MIN_MAX
	};

	for (size_t i = 0; i < sizeof(ids)/sizeof(int); i++)
	{
		ShowWindow(GetDlgItem(this->hDlg, ids[i]), this->m_ab.use_locals);
	}
		
	switch (this->m_ab.locals_algorithms_type)
	{
	case the_simple:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO1,
				IDC_RADIO3,
				IDC_RADIO1);

			ShowWindow(GetDlgItem(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), false);
			ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), false);
			ShowWindow(GetDlgItem(this->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), false);
		}

		break;
	case on_the_second_derivatives:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO1,
				IDC_RADIO3,
				IDC_RADIO2);

			ShowWindow(GetDlgItem(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), true && this->m_ab.use_locals);
			ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), true && this->m_ab.use_locals);
			ShowWindow(GetDlgItem(this->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), true && this->m_ab.use_locals);
		}
		break;
	}
	EnableWindow(GetDlgItem(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), 
		this->m_ab.allow_sd_limit_quantil && this->m_ab.use_locals);

}
#endif
void AutoBuildProfileDlg::OnButtonBrowseNumColomn()
{
	if (::OpenFileDlg(hDlg, 
		"Data (*.dat)\0*.dat\0"
		"CSV (*.csv)\0*.csv\0"
		"All files \0*.*\0") == S_OK)

	{
		strcpy(this->m_ab.num_col_filename,::szPath);
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		SetDlgItemText(this->hDlg, IDC_EDIT_NUM_COLOMNS, this->m_ab.num_col_filename);
#endif
		num_col_file_selected = true;
	}
}

void AutoBuildProfileDlg::OnDestroy()
{

}

AutoBuildProfileDlg1::AutoBuildProfileDlg1(bool _consol, AutoBuildProfile * auto_build_profile, auto_build_parametrs& ab) : m_ab(ab)
{
	p_auto_build_profile = auto_build_profile;
	consol = _consol;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	DialogBoxParam( 
	   hInst, 
	   MAKEINTRESOURCE(IDD_DIALOG_AUTO_BUILD_PROFILE1), 
	   NULL,
	   (DLGPROC)DlgProcAutoBuildProfile1,
	   (LPARAM)this);
#endif

}

AutoBuildProfileDlg1::~AutoBuildProfileDlg1()
{

}
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
void AutoBuildProfileDlg1::OnInitDialog()
{
	CheckRadioButton( hDlg, 
		IDC_RADIO_SPUSK,
		IDC_RADIO_NEWTON_MODIFIED, 
		IDC_RADIO_SPUSK);

	CheckRadioButton( hDlg, 
		IDC_RADIO_parallel_to_profile_antenn_normal_X,
		IDC_RADIO_parallel_to_profile_antenn_normal_Y, 
		IDC_RADIO_parallel_to_profile_antenn_normal_X);

	//IDC_CHECK_to_set_mean_of_profiles_to_zero
	//IDC_CHECK_to_set_mean_value_to_profile
	//IDC_CHECK_to_recenter_profiles
	CheckDlgButton(this->hDlg, IDC_CHECK_to_set_mean_of_profiles_to_zero, false);
	CheckDlgButton(this->hDlg, IDC_CHECK_to_set_mean_value_to_profile, false);
	CheckDlgButton(this->hDlg, IDC_CHECK_to_recenter_profiles, false);

	CheckDlgButton(this->hDlg, IDC_CHECK_apply_dgdni, true);
	CheckDlgButton(this->hDlg, IDC_CHECK_apply_dgdKTi, true);
	CheckDlgButton(this->hDlg, IDC_CHECK_apply_dgdbeta, true);

	//Enter Do you need coordinate preobrazovanie
	//IDC_CHECK_to_povorot
	CheckDlgButton(this->hDlg, IDC_CHECK_to_povorot, true);

	//Do you need coordinate projection output?
	//IDC_CHECK_need_crd_projection
	CheckDlgButton(this->hDlg, IDC_CHECK_need_crd_projection, true);

	//IDC_RADIO_TYPE_1
	CheckRadioButton( hDlg, 
		IDC_RADIO_TYPE_1,
		IDC_RADIO_TYPE_2, 
		IDC_RADIO_TYPE_1);

	CheckRadioButton( hDlg, 
		IDC_RADIO_LAMP,
		IDC_RADIO_DIPOL, 
		IDC_RADIO_DIPOL);

	//IDC_EDIT_Altitude_z0
	SetDlgItemText(this->hDlg, IDC_EDIT_Altitude_z0, "130");

	//IDC_EDIT_Altitude_z_min
	SetDlgItemText(this->hDlg, IDC_EDIT_Altitude_z_min, "-2870");

	//cout << "Enter dx/DZ=dy/DZ (for example 2)" << endl;
	//IDC_EDIT_dx_and_dy_per_DZ
	SetDlgItemText(this->hDlg, IDC_EDIT_dx_and_dy_per_DZ, "2.0");

	//cout << "Enter granicy_kak_glubina?  0 - no 1 - yes" << endl;
	//IDC_CHECK_granicy_kak_glubina
	CheckDlgButton(this->hDlg, IDC_CHECK_granicy_kak_glubina, false);

	//IDC_EDIT_ROWS
	SetDlgItemText(this->hDlg, IDC_EDIT_ROWS, "30");

	//IDC_EDIT_COLS
	SetDlgItemText(this->hDlg, IDC_EDIT_COLS, "30");

	//IDC_EDIT_PAGES
	SetDlgItemText(this->hDlg, IDC_EDIT_PAGES, "30");

	//IDC_EDIT_ITER_SAVE
	SetDlgItemText(this->hDlg, IDC_EDIT_ITER_SAVE, "100");

	//cout << "Enter k_oslablenie (po naprjazhonnosti polja, for example 0.00023025 -> 1.999 dB/km by power), (m^-1)" << endl;
	//IDC_EDIT_k_oslablenie
	SetDlgItemText(this->hDlg, IDC_EDIT_k_oslablenie, "0.00023025");


/*	char str[1024];
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.k);
	SetDlgItemText(this->hDlg, IDC_EDIT_GLUBINA_K, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.quantil_naklony);
	SetDlgItemText(this->hDlg, IDC_EDIT_NAKLON_QUANTIL, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.peregib_krutizna_quantil);
	SetDlgItemText(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.win_velonsity);
	SetDlgItemText(this->hDlg, IDC_EDIT_WIN_STEP_VELONSITY, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.minimum_of_signal);
	SetDlgItemText(this->hDlg, IDC_EDIT_MINIMUM_OF_SIGNAL, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.limit_dima);
	SetDlgItemText(this->hDlg, IDC_EDIT_LIMIT_DIMA, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.limit_1);
	SetDlgItemText(this->hDlg, IDC_EDIT_LIMIT_1, str);
	///////////////////////////////////////////////

	sprintf(str, "%d", this->m_ab.n);
	SetDlgItemText(this->hDlg, IDC_EDIT_POVTOR_ZAPRET, str);
	///////////////////////////////////////////////

	

	
	

	
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_DIMA, this->m_ab.use_window_cycles_algorithm_dima);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_1, this->m_ab.use_window_cycles_algorithm_1);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_LOCALS, this->m_ab.use_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_DIMA_AFTER_LOCALS, this->m_ab.use_window_cycles_algorithm_dima_after_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_1_AFTER_LOCALS, this->m_ab.use_window_cycles_algorithm_1_after_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL, this->m_ab.allow_sd_limit_quantil);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_POVTOR_ZAPRET, !this->m_ab.use_repeat_points);
	EnableWindow(GetDlgItem(this->hDlg, IDC_EDIT_POVTOR_ZAPRET), !this->m_ab.use_repeat_points);
	///////////////////////////////////////////////
	
	CheckDlgButton(this->hDlg, IDC_CHECK_TIME_COLOMN, this->m_ab.use_time_colomn);
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_NUM_COL, this->m_ab.use_num_col);
	ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_NUM_COLOMNS), this->m_ab.use_num_col);
	ShowWindow(GetDlgItem(this->hDlg, IDC_BUTTON_BROSE_NUM_COLOMNS), this->m_ab.use_num_col);
	sprintf(str, "%s", this->m_ab.num_col_filename);
	SetDlgItemText(this->hDlg, IDC_EDIT_NUM_COLOMNS, str);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY, this->m_ab.use_whole_directory);
	ShowWindow(GetDlgItem(this->hDlg, IDC_DIRECTORY2), 
		this->m_ab.use_whole_directory);
	ShowWindow(GetDlgItem(this->hDlg, IDC_LIST2), 
		this->m_ab.use_whole_directory);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN, this->m_ab.use_min);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MAX, this->m_ab.use_max);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN_MAX, this->m_ab.use_min_max);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN2, this->m_ab.use_min_2);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MAX2, this->m_ab.use_max_2);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN_MAX2, this->m_ab.use_min_max_2);
	///////////////////////////////////////////////

	switch (this->m_ab.m_gradient_type)
	{
	case auto_build_parametrs::gradient_type::the_dividitial:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO4,
				IDC_RADIO6,
				IDC_RADIO4);
		}
		break;
	case auto_build_parametrs::gradient_type::the_differential:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO4,
				IDC_RADIO6,
				IDC_RADIO5);
		}
		break;
	}


	this->ShowWindows_RelatedWith_CheckUseLocals();
	this->ShowWindows_RelatedWith_Windows_Cycles();
	


	for(size_t j = 0; j < 3; j++)
	{
		sprintf(str, "%u", j);
		SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J , CB_ADDSTRING, 0, (LPARAM)str);
		SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2, CB_ADDSTRING, 0, (LPARAM)str);
	}

	SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J , CB_SETCURSEL, this->m_ab.start_j1, (LPARAM)0 );
	SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2, CB_SETCURSEL, this->m_ab.start_j2, (LPARAM)0 );

	num_col_file_selected = false;

*/

			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)",");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)";");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"tabulation");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"space");
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_SETCURSEL,
				0,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    // Retrieve the handle to the Map control. 
    this->m_plotWnd.hwnd = GetDlgItem(hDlg, IDC_STATIC_AUTOBUILD_PROFILE); 

    // Subclass the edit control. 
    wpOrigAutoBuildProfileWndProc = (WNDPROC) SetWindowLongPtr(this->m_plotWnd.hwnd, 
        GWLP_WNDPROC, (LONG_PTR) AutoBuildProfileWndSubclassProc); 

	SetWindowLongPtr(this->m_plotWnd.hwnd, GWLP_USERDATA,(LONG_PTR)this);



}
#endif
void AutoBuildProfileDlg1::OnButtonOK()
{
    //char str[125];
	///////////////////////////////////////////////
/*	GetDlgItemText(this->hDlg,IDC_EDIT_GLUBINA_K, str, 124);
	this->m_ab.k = atof(str);
printf("this->m_ab.k = %f\n", this->m_ab.k);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_NAKLON_QUANTIL, str, 124);
	this->m_ab.quantil_naklony = atof(str);
printf("this->m_ab.quantil_naklony = %f\n", this->m_ab.quantil_naklony);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL, str, 124);
	this->m_ab.peregib_krutizna_quantil = atof(str);
printf("this->m_ab.peregib_krutizna_quantil = %f\n", this->m_ab.peregib_krutizna_quantil);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_WIN_STEP_VELONSITY, str, 124);
	this->m_ab.win_velonsity = atof(str);
printf("this->m_ab.win_velonsity = %f\n", this->m_ab.win_velonsity);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_MINIMUM_OF_SIGNAL, str, 124);
	this->m_ab.minimum_of_signal = atof(str);
printf("this->m_ab.minimum_of_signal = %f\n", this->m_ab.minimum_of_signal);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_LIMIT_DIMA, str, 124);
	this->m_ab.limit_dima = atof(str);
printf("this->m_ab.limit_dima = %f\n", this->m_ab.limit_dima);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_LIMIT_1, str, 124);
	this->m_ab.limit_1 = atof(str);
printf("this->m_ab.limit_1 = %f\n", this->m_ab.limit_1);
	///////////////////////////////////////////////


	GetDlgItemText(this->hDlg,IDC_EDIT_POVTOR_ZAPRET, str, 124);
	this->m_ab.n = atoi(str);
printf("this->m_ab.n = %d\n", this->m_ab.n);
	///////////////////////////////////////////////




	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima = IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_dima = %d\n", this->m_ab.use_window_cycles_algorithm_dima);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1 = IsDlgButtonChecked( hDlg, IDC_CHECK_1) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_1 = %d\n", this->m_ab.use_window_cycles_algorithm_1);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_dima_after_locals = %d\n", this->m_ab.use_window_cycles_algorithm_dima_after_locals);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_1_after_locals = %d\n", this->m_ab.use_window_cycles_algorithm_1_after_locals);

	///////////////////////////////////////////////
	this->m_ab.use_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_locals = %d\n", this->m_ab.use_locals);
	///////////////////////////////////////////////
	this->m_ab.allow_sd_limit_quantil = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL) == BST_CHECKED;
printf("this->m_ab.allow_sd_limit_quantil = %d\n", this->m_ab.allow_sd_limit_quantil);
	///////////////////////////////////////////////


	///////////////////////////////////////////////
	this->m_ab.use_repeat_points = IsDlgButtonChecked( hDlg, IDC_CHECK_POVTOR_ZAPRET) 
		!= BST_CHECKED;
printf("this->m_ab.use_repeat_points = %d\n", this->m_ab.use_repeat_points);
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	this->m_ab.use_max = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MAX) == BST_CHECKED;
printf("this->m_ab.use_max = %d\n", m_ab.use_max);
	///////////////////////////////////////////////
	this->m_ab.use_max_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MAX2) == BST_CHECKED;
printf("this->m_ab.use_max_2 = %d\n", m_ab.use_max_2);
	///////////////////////////////////////////////
	this->m_ab.use_min = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN) == BST_CHECKED;
printf("this->m_ab.use_min = %d\n", m_ab.use_min);
	///////////////////////////////////////////////
	this->m_ab.use_min_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN2) == BST_CHECKED;
printf("this->m_ab.use_min_2 = %d\n", m_ab.use_min_2);
	///////////////////////////////////////////////
	this->m_ab.use_min_max = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN_MAX) == BST_CHECKED;
printf("this->m_ab.use_min_max = %d\n", m_ab.use_min_max);
	///////////////////////////////////////////////
	this->m_ab.use_min_max_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN_MAX2) == BST_CHECKED;
printf("this->m_ab.use_min_max_2 = %d\n", m_ab.use_min_max_2);
	///////////////////////////////////////////////


	this->m_ab.start_j1 = SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J ,	CB_GETCURSEL,0,(LPARAM)0 );
	this->m_ab.start_j2 = SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2,	CB_GETCURSEL,0,(LPARAM)0 );
printf("this->m_ab.start_j1 = %d\n", this->m_ab.start_j1);
printf("this->m_ab.start_j2 = %d\n", this->m_ab.start_j2);

*/
	if (this->m_ab.use_num_col && !num_col_file_selected)
	{
		MessageBox(hDlg, "Вы не выбрали имя файла с номерами колонок","AutoBuildProfileDlg",0);
		return;
	}

	if (this->m_ab.use_whole_directory)
	{
		UseWholeDirectory();
	}
	else
	{
		//AutoBuildProfile_main(consol, p_auto_build_profile, this->m_ab);
	}
}
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
void AutoBuildProfileDlg1::ShowWindows_RelatedWith_Windows_Cycles2()
{
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////	
	int ids[] = {
		IDC_CHECK_LOCAL_MAX2,
			IDC_CHECK_LOCAL_MIN2,
			IDC_CHECK_LOCAL_MIN_MAX2,
			IDC_STATIC_INPUT_LOCALS
	};
	bool show = 
		this->m_ab.use_window_cycles_algorithm_1_after_locals ||
		this->m_ab.use_window_cycles_algorithm_dima_after_locals;

	for (size_t i = 0; i < sizeof(ids)/sizeof(int); i++)
	{
		ShowWindow(GetDlgItem(this->hDlg, ids[i]), show);
	}	
}
void AutoBuildProfileDlg1::ShowWindows_RelatedWith_Windows_Cycles()
{
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1 = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_1) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
	///////////////////////////////////////////////	
	int ids[] = {
		IDC_EDIT_LIMIT_DIMA,
			IDC_EDIT_LIMIT_1,
			IDC_STATIC_LIMIT,
			IDC_STATIC_MIN_SIGNAL,
			IDC_EDIT_MINIMUM_OF_SIGNAL,
			IDC_CHECK_POVTOR_ZAPRET,
			IDC_STATIC_POVTOR_ZAPRET, 
			IDC_EDIT_POVTOR_ZAPRET, 
			IDC_STATIC_WIN_LEN_PARAM,
			IDC_EDIT_WIN_STEP_VELONSITY,
			IDC_STATIC_WIN_STEP_VELONSITY,
			IDC_COMBO_START_WINDOW_LEN,
			IDC_STATIC_START_WINDOW_LEN,
			IDC_COMBO_END_WINDOW_LEN,
			IDC_STATIC_END_WINDOW_LEN,
			IDC_STATIC_GRADIENT_TYPE,
			IDC_RADIO4,
			IDC_RADIO5		
	};
	bool show = 
		this->m_ab.use_window_cycles_algorithm_1 ||
		this->m_ab.use_window_cycles_algorithm_1_after_locals ||
		this->m_ab.use_window_cycles_algorithm_dima ||
		this->m_ab.use_window_cycles_algorithm_dima_after_locals;

	for (size_t i = 0; i < sizeof(ids)/sizeof(int); i++)
	{
		ShowWindow(GetDlgItem(this->hDlg, ids[i]), show);
	}
}

void AutoBuildProfileDlg1::ShowWindows_RelatedWith_CheckUseLocals()
{
	this->m_ab.use_locals = 
		IsDlgButtonChecked( hDlg, IDC_CHECK_USE_LOCALS) == BST_CHECKED;

	int ids[] = {
		IDC_EDIT_NAKLON_QUANTIL,
			IDC_STATIC_NAKLON_QUANTIL,
			IDC_COMBO_LOCALS_START_J,
			IDC_STATIC_LOCALS_START_J,
			IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL,
			IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL,
			IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL,
			IDC_RADIO1,
			IDC_RADIO2,

			IDC_STATIC_LOCALS_OUTPUT,
			IDC_CHECK_LOCAL_MAX, 
			IDC_CHECK_LOCAL_MIN,
			IDC_CHECK_LOCAL_MIN_MAX
	};

	for (size_t i = 0; i < sizeof(ids)/sizeof(int); i++)
	{
		ShowWindow(GetDlgItem(this->hDlg, ids[i]), this->m_ab.use_locals);
	}
		
	switch (this->m_ab.locals_algorithms_type)
	{
	case the_simple:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO1,
				IDC_RADIO3,
				IDC_RADIO1);

			ShowWindow(GetDlgItem(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), false);
			ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), false);
			ShowWindow(GetDlgItem(this->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), false);
		}

		break;
	case on_the_second_derivatives:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO1,
				IDC_RADIO3,
				IDC_RADIO2);

			ShowWindow(GetDlgItem(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), true && this->m_ab.use_locals);
			ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), true && this->m_ab.use_locals);
			ShowWindow(GetDlgItem(this->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), true && this->m_ab.use_locals);
		}
		break;
	}
	EnableWindow(GetDlgItem(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), 
		this->m_ab.allow_sd_limit_quantil && this->m_ab.use_locals);

}
#endif
void AutoBuildProfileDlg1::OnButtonBrowseNumColomn()
{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	if (::OpenFileDlg(hDlg, 
		_T("Data (*.dat)\0*.dat\0")
		_T("CSV (*.csv)\0*.csv\0")
		_T("All files \0*.*\0"), this->m_ab.num_col_filename) == S_OK)

	{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		strcpy(this->m_ab.num_col_filename,::szPath);
		SetDlgItemText(this->hDlg, IDC_EDIT_NUM_COLOMNS, this->m_ab.num_col_filename);
#endif
		num_col_file_selected = true;
	}
#else
	QString dir = QDir("../data/rovno/rovno_u001/").absolutePath();
	QString file = "Colomn_list_vertical.dat";
	sprintf(this->m_ab.num_col_filename, "%s/%s", dir.toStdString().c_str(), file.toStdString().c_str());
    num_col_file_selected = true;
#endif
}

void AutoBuildProfileDlg1::OnDestroy()
{

}

void GetMinMaxXYOfData(
				   vector<double> & X,
				   vector<double> & Y,
				   
				   double & min_X,
				   double & max_X,
				   double & min_Y, 
				   double & max_Y
  
				   )
{
	min_X = DBL_MAX;
	max_X = -DBL_MAX;
	min_Y = DBL_MAX;
	max_Y = -DBL_MAX;

    for (size_t i = 0; i < X.size(); i++)
	{
		if (min_X > X[i]) min_X = X[i];
		if (min_Y > Y[i]) min_Y = Y[i];

		if (max_X < X[i]) max_X = X[i];
		if (max_Y < Y[i]) max_Y = Y[i];
	}
}
void GetPartOfData(
				   double min_x,
				   double max_x,
				   double min_y, 
				   double max_y,

				   vector<double> & X,
				   vector<double> & Y,
				   vector<double> & Z, // альтитуда измерений - полёта самолёта
				   vector<vector<anten_direction> > & A,
				   vector<double> & vModul,
				   vector<vector<double> > & v,
				   
				   vector<double> & pX,
				   vector<double> & pY,
				   vector<double> & pZ, // альтитуда измерений - полёта самолёта
				   vector<vector<anten_direction> > & pA,
				   vector<double> & pvModul,
				   vector<vector<double> > & pv,

				   vector<long> & pInd
				   
				   )
{

	pX.clear();
	pY.clear();
	pZ.clear();
	pvModul.clear();
	pv.clear();

	pInd.clear();


	size_t cols = v.size();
	pv.resize(cols);
	pA.resize(3);

	for (long i = 0; i < X.size(); i++)
	{
		if (X[i] > min_x && X[i] < max_x && 
			Y[i] > min_y && Y[i] < max_y)
		{
			pX.push_back(X[i]);
			pY.push_back(Y[i]);
			pZ.push_back(Z[i]);

			pvModul.push_back(vModul[i]);
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				pv[c].push_back(v[c][i]);
			}
			for (short a = 0; a < 3; a++)
			{
				pA[a].push_back(A[a][i]);
			}

			pInd.push_back(i);
		}
	}
}
void GetPartOfData(double p_min, // 0.45
				   double p_max, // 0.55
				   vector<double> & X,
				   vector<double> & Y,
				   vector<double> & Z, // альтитуда измерений - полёта самолёта
				   vector<vector<anten_direction> > & A,
				   vector<double> & vModul,
				   vector<vector<double> > & v,
				   
				   vector<double> & pX,
				   vector<double> & pY,
				   vector<double> & pZ, // альтитуда измерений - полёта самолёта
				   vector<vector<anten_direction> > & pA,
				   vector<double> & pvModul,
				   vector<vector<double> > & pv
				   
				   )
{
	double min_X = DBL_MAX;
	double max_X = -DBL_MAX;
	double min_Y = DBL_MAX;
	double max_Y = -DBL_MAX;
	for (int i = 0; i < X.size(); i++)
	{
		if (min_X > X[i]) min_X = X[i];
		if (min_Y > Y[i]) min_Y = Y[i];

		if (max_X < X[i]) max_X = X[i];
		if (max_Y < Y[i]) max_Y = Y[i];
	}

	double _min_X = min_X + p_min * (max_X - min_X);
	double _max_X = min_X + p_max * (max_X - min_X);

	double _min_Y = min_Y + p_min * (max_Y - min_Y);
	double _max_Y = min_Y + p_max * (max_Y - min_Y);

	size_t cols = v.size();
	pv.resize(cols);
	pA.resize(3);

	for (int i = 0; i < X.size(); i++)
	{
		if (X[i] > _min_X && X[i] < _max_X && 
			Y[i] > _min_Y && Y[i] < _max_Y)
		{
			pX.push_back(X[i]);
			pY.push_back(Y[i]);
			pZ.push_back(Z[i]);

			pvModul.push_back(vModul[i]);
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				pv[c].push_back(v[c][i]);
			}
			for (short a = 0; a < 3; a++)
			{
				pA[a].push_back(A[a][i]);
			}
		}
	}
}
void GetPartOfData(int frec, // 1 2 .. 10 ...
				   vector<double> & X,
				   vector<double> & Y,
				   vector<double> & Z, // альтитуда измерений - полёта самолёта
				   vector<vector<anten_direction> > & A,
				   vector<double> & vModul,
				   vector<vector<double> > & v,
				   
				   vector<double> & pX,
				   vector<double> & pY,
				   vector<double> & pZ, // альтитуда измерений - полёта самолёта
				   vector<vector<anten_direction> > & pA,
				   vector<double> & pvModul,
				   vector<vector<double> > & pv
				   
				   )
{
	size_t cols = v.size();
	pv.resize(cols);
	pA.resize(3);

	for (int i = 0; i < X.size(); i++)
	{
		if (i%frec == 0)
		{
			pX.push_back(X[i]);
			pY.push_back(Y[i]);
			pZ.push_back(Z[i]);

			pvModul.push_back(vModul[i]);
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				pv[c].push_back(v[c][i]);
			}
			for (short a = 0; a < 3; a++)
			{
				pA[a].push_back(A[a][i]);
			}
		}
	}
}

void GetPartOfData_with_mean(int frec, // 1 2 .. 10 ...
                   vector<double> & X,
                   vector<double> & Y,
                   vector<double> & Z, // альтитуда измерений - полёта самолёта
                   vector<vector<anten_direction> > & A,
                   vector<double> & vModul,
                   vector<vector<double> > & v,

                   vector<double> & pX,
                   vector<double> & pY,
                   vector<double> & pZ, // альтитуда измерений - полёта самолёта
                   vector<vector<anten_direction> > & pA,
                   vector<double> & pvModul,
                   vector<vector<double> > & pv

                   )
{
   size_t cols = v.size();
   pv.resize(cols);
   pA.resize(3);

   size_t X_size = X.size();

   for (int i = 0; i < X_size; i++)
   {
      if (i%frec == frec / 2)
      {
         pX.push_back(X[i]);
         pY.push_back(Y[i]);
         pZ.push_back(Z[i]);

         int j0 = i - frec/2;
         if (j0 < 0)
            j0 = 0;

         int j1 = j0 + frec;
         if (j1 >= X_size)
            j1 = X_size - 1;

         double meanModule = 0.0;
         for (int j = j0; j < j1; ++j)
         {
            meanModule += vModul[j];
         }
         meanModule /= frec;

         pvModul.push_back(meanModule);
         for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
         {
            double mean_v = 0.0;
            for (int j = j0; j < j1; ++j)
            {
               mean_v += v[c][j];
            }
            mean_v /= frec;
            pv[c].push_back(mean_v);
         }
         for (short a = 0; a < 3; a++)
         {
            pA[a].push_back(A[a][i]);
         }
      }
   }
}
void SaveCubesAndSlices(const char * common_directory,
						Grid4 *** cubes, MyMethodsData3 & mmd3, 
						const char * file,
						const char * name,
						int cc, int i_alpha, 
						bool to_reduce_x, bool to_reduce_y)
{
	double min_v = DBL_MAX;
	double max_v = -DBL_MAX;

	double v_value;

	//vector<double> sol(cubes[cc][i_alpha]->grid4Section.nCol * cubes[cc][i_alpha]->grid4Section.nRow * cubes[cc][i_alpha]->grid4Section.nPag);

	for (long _pp = 0; _pp < cubes[cc][i_alpha]->grid4Section.nPag; _pp++)
	{
		for (long _cc = 0; _cc < cubes[cc][i_alpha]->grid4Section.nCol; _cc++)
		{
			for (long _rr = 0; _rr < cubes[cc][i_alpha]->grid4Section.nRow; _rr++)
			{
				v_value = cubes[cc][i_alpha]->grid4Section.v[_pp][_rr][_cc];
				if (v_value != BLANK_VALUE)
				{
					if (max_v < v_value) max_v = v_value;
					if (min_v > v_value) min_v = v_value;

					// индекс в строке матрицы оператора прямой задачи
					//long i = rr_ * mmd.cols + cc_;
					long i = _pp * mmd3.rows * mmd3.cols + _rr * mmd3.cols + _cc;
					//sol[i] = v_value;
				}
			}
		}
	}
	cubes[cc][i_alpha]->grid4Section.vMax = max_v;
	cubes[cc][i_alpha]->grid4Section.vMin = min_v;
	
	//-----------------------------------

	SaveAsSurfer7Grid4(file, cubes[cc][i_alpha]);




	// 	======================================================
    Cube4D a_cube;
	a_cube.Init(&cubes[cc][i_alpha]->grid4Section, (COLORREF)0);

	char slice_dir[4098];

	if (to_reduce_x || to_reduce_y)
	{
		sprintf(slice_dir, "%s", common_directory);		
	}
	for (int nProjection = 1; nProjection <=3; nProjection++)
	{									
		switch (nProjection)
		{
		case 1:
			{
				//sprintf (projection, "XY\0");
				if (to_reduce_x || to_reduce_y)
					continue;
			}
			break;
		case 2:
			{
				//sprintf (projection, "XZ\0");
				if (to_reduce_x)
					continue;
			}
			break;
		case 3:
			{
				//sprintf (projection, "YZ\0");
				if (to_reduce_y)
					continue;
			}
			break;
		}
		static Grid grid;// грид для построения и сохранения разреза куба
		
		char lpstrFile[4098];


		char projection[8];
		switch (nProjection)
		{
		case 1:
			{
				sprintf (projection, "XY\0");
			}
			break;
		case 2:
			{
				sprintf (projection, "XZ\0");
			}
			break;
		case 3:
			{
				sprintf (projection, "YZ\0");
			}
			break;
		}

		if (!(to_reduce_x || to_reduce_y))
		{
            sprintf(slice_dir, "%s/slices_%s_of_%s", common_directory,
				projection, name);
			char * p;
			while (p=strchr (slice_dir,'\"'))
			{
				*p = '_';
			}

			int n = 0;
			while (!CreateDirectory(slice_dir,NULL))
			{
                sprintf(slice_dir, "%s/slices_%s_of_%s(%d)", common_directory,
					projection, name, n++);
				char * p;
				while (p=strchr (slice_dir,'\"'))
				{
					*p = '_';
				}
			}
		}

        sprintf(lpstrFile, "%s/slice_%s_of_%s", slice_dir,
			projection, name);

		switch(nProjection)
		{
		case 1:
			{
				a_cube.SaveAsSurferClicesXY(lpstrFile, grid);	
			}
			break;
		case 2:
			{
				if (mmd3.to_povorot && mmd3.need_crd_projection && to_reduce_y) 
					a_cube.SaveAsSurferClicesXZ(lpstrFile, grid, mmd3.vX0, cos(mmd3.ugol));	
				a_cube.SaveAsSurferClicesXZ(lpstrFile, grid);	
			}
			break;
		case 3:
			{
				if (mmd3.to_povorot && mmd3.need_crd_projection && to_reduce_x) 
					a_cube.SaveAsSurferClicesYZ(lpstrFile, grid, mmd3.vY0, cos(mmd3.ugol));	
				a_cube.SaveAsSurferClicesYZ(lpstrFile, grid);	
			}
			break;
		}
	}
}


void SaveCubesAndSlices(const char * common_directory,
						const char * method_name,
						Grid4 *** cubes, MyMethodsData3 & mmd3, 
						vector<string> & new_names_of_colomns,
						int cc, int i_alpha, 
						bool to_reduce_x, bool to_reduce_y)
{
	char file[2048];
    sprintf(file, "%s/%s_of_%s_alpha=%01e.cub",
		common_directory, method_name,
		new_names_of_colomns[cc].c_str(),
		mmd3.v_alpha[i_alpha]);
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	char name[4098];
	sprintf(name, "%s_of_%s_alpha=%01e.cub", 
		method_name,
		new_names_of_colomns[cc].c_str(), 
		mmd3.v_alpha[i_alpha]);
		
	while (p=strchr (name,'\"'))
	{
		*p = '_';
	}
	SaveCubesAndSlices(common_directory, cubes, mmd3, file, name, 
		cc, i_alpha, to_reduce_x, to_reduce_y);
}
void SaveCubesAndSlices(const char * common_directory,
						const char * method_name,
						Grid4 *** cubes, MyMethodsData3 & mmd3, 
						const char * cube_name,
						int cc, int i_cube, 
						bool to_reduce_x, bool to_reduce_y)
{
	char file[2048];
    sprintf(file, "%s/%s_%s.cub",
		common_directory, method_name, cube_name);
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	char name[4098];
	sprintf(name, "%s_%s.cub", 
		method_name, cube_name);
		
	while (p=strchr (name,'\"'))
	{
		*p = '_';
	}
	SaveCubesAndSlices(common_directory, cubes, mmd3, file, name, 
		cc, i_cube, to_reduce_x, to_reduce_y);
}


void SavingIteration(vector<short> & va, int iteration, const char * folder_name,
					 bool apply_log10,
					 bool apply_bln,
					vector<double> & KTi, const char * cube_name_KTi,
                    vector<double> & ni, const char * cube_name_ni,
                    vector<vector<double> > & C,
                    vector<vector<double> > & W,
					int da,
					const char * DirName,
					const char * method_name,
					Grid4 *** cubes, MyMethodsData3 & mmd3, 
					bool to_reduce_x, bool to_reduce_y)
{
	short a, ia;  
	int cc = 0;
	if (cubes)
	{
		for(long c = 0; c < mmd3.cols; c++)
		{
			for(long r = 0; r < mmd3.rows; r++)
			{
				for(long P = 0; P < mmd3.pages; P++)
				{
					// индекс в строке матрицы оператора прямой задачи
					long i = P * mmd3.rows * mmd3.cols + r * mmd3.cols + c;
					// rows = 1, cols = 1, i = p
					if (apply_log10)
					{
						cubes[cc][0]->grid4Section.v[P][r][c] = log10(KTi[i]);
						cubes[cc][1]->grid4Section.v[P][r][c] = log10(ni[i]);
					}
					else
					{
						cubes[cc][0]->grid4Section.v[P][r][c] = KTi[i];
						cubes[cc][1]->grid4Section.v[P][r][c] = ni[i];
					}
				}
			}
		}
		cc = 0;
		int i_cube = 0; 
		SaveCubesAndSlices(DirName,
			method_name,
			cubes, mmd3, 
			cube_name_KTi,
			cc, i_cube, to_reduce_x, to_reduce_y);

		i_cube = 1; 
		SaveCubesAndSlices(DirName,
			method_name,
			cubes, mmd3, 
			cube_name_ni,
			cc, i_cube, to_reduce_x, to_reduce_y);

	}
	if (apply_bln)
	{

		char bln_name[1024];
		char name[2048];
		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; 
		
			sprintf(name, "%s_%c", method_name, 'x'+ a);

            sprintf(bln_name, "%s/origin_%s.bln", DirName, name);
			char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
			FILE * bln = fopen (bln_name, "wt");
			if(bln)
			{
				fprintf(bln, "%d,%d, origin\n", W[a+da].size(), 0);
				for(size_t i = 0; i < W[a].size(); i++)
				{
					fprintf(bln, "%f,%f\n", double(i), double(W[a+da][i]));
				}	
				fclose(bln);
			}
			
            sprintf(bln_name, "%s/reconstr_%s.bln", DirName, name);
			while (p=strchr (bln_name,'\"')){*p = '_';}
			bln = fopen (bln_name, "wt");
			if(bln)
			{
                fprintf(bln, "%d,%d, reconstr\n", C[a].size(), 0);
                for(size_t i = 0; i < C[a].size(); i++)
				{
					fprintf(bln, "%f,%f\n", double(i), double(C[a][i]));
				}
				fclose(bln);
			}
		}
	}
}



void ApplyIteration(long c_apply,
					double one,
					bool apply_dgdep, 
					bool apply_dgdni,
					vector<short> & va,

					long operator_cols,

					vector<double> & ni_A,
					vector<double> & KTi_A,
					double * Ep,

					vector<double> & dGdni_A,
					vector<double> & d2Gdni2_A,
					vector<double> & dGdKTi_A,
					vector<double> & d2GdKTi2_A,
					vector<double> & dGdEp,
					vector<double> & d2GdEp2,

					vector<double> & ni_B,
					vector<double> & KTi_B,
					double * k,

					vector<double> & dGdni_B,
					vector<double> & d2Gdni2_B,
					vector<double> & dGdKTi_B,
					vector<double> & d2GdKTi2_B,
					vector<double> & dGdk,
					vector<double> & d2Gdk2

					)
{
	short a, ia;
	double good_part = 0.2;
	double divider = operator_cols;

	long c0 = 0, cmax = -1;
	if (c_apply < 0)
	{
		c0 = 0;
		cmax = operator_cols;
		divider = operator_cols;
	}
	else
	{
		if (c_apply < operator_cols)
		{
			c0 = c_apply;
			cmax = c_apply + 1;
			divider = double(operator_cols) / 5.0;
		}
	}

	for (long c = c0; c < cmax; c++)
	{
		if (fabs(d2GdKTi2_A[c]) > FLT_MIN)
		{
			double kti_c_A  = KTi_A[c];
			double dkti_c_A  = one * dGdKTi_A[c] / d2GdKTi2_A[c] / divider;// / operator_rows;

			if (fabs(dkti_c_A) < good_part * fabs(kti_c_A))
				KTi_A[c] -= dkti_c_A;
			else
				KTi_A[c] -= (dkti_c_A / fabs(dkti_c_A)) * good_part * fabs(kti_c_A);

			if (KTi_A[c] < FLT_MIN) KTi_A[c] = FLT_MIN;
		}
		if (fabs(d2GdKTi2_B[c]) > FLT_MIN)
		{
			double kti_c_B  = KTi_B[c];
			double dkti_c_B  = one * dGdKTi_B[c] / d2GdKTi2_B[c] / divider;// / operator_rows;

			if (fabs(dkti_c_B) < good_part * fabs(kti_c_B))
				KTi_B[c] -= dkti_c_B;
			else
				KTi_B[c] -= (dkti_c_B / fabs(dkti_c_B)) * good_part * fabs(kti_c_B);

			if (KTi_B[c] < FLT_MIN) KTi_B[c] = FLT_MIN;
		}

		if (apply_dgdni && fabs(d2Gdni2_A[c]) > FLT_MIN)
		{
			double ni_c_A = ni_A[c];
			double dni_c_A = one * dGdni_A[c] / d2Gdni2_A[c] / divider;// / operator_rows;

			if (fabs(dni_c_A) < good_part * fabs(ni_c_A))
				ni_A[c] -= dni_c_A;
			else
				ni_A[c] -= (dni_c_A / fabs(dni_c_A)) * good_part * fabs(ni_c_A);

			if (ni_A[c] < FLT_MIN) ni_A[c] = FLT_MIN;
		}

		if (apply_dgdni && fabs(d2Gdni2_B[c]) > FLT_MIN)
		{
			double ni_c_B = ni_B[c];
			double dni_c_B = one * dGdni_B[c] / d2Gdni2_B[c] / divider;// / operator_rows;

			if (fabs(dni_c_B) < good_part * fabs(ni_c_B))
				ni_B[c] -= dni_c_B;
			else
				ni_B[c] -= (dni_c_B / fabs(dni_c_B)) * good_part * fabs(ni_c_B);

			if (ni_B[c] < FLT_MIN) ni_B[c] = FLT_MIN;
		}

	}

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		if (apply_dgdep && fabs(d2GdEp2[a]) > FLT_MIN)
		{
			double epa = Ep[a];
			double depa = one * dGdEp[a] / d2GdEp2[a] / va.size();// / operator_cols / operator_rows;

			if (fabs(depa) < good_part * fabs(epa))
				Ep[a] -= depa;
			else
				Ep[a] -= (depa / fabs(depa)) * good_part * fabs(epa);

			if (Ep[a] < FLT_MIN) Ep[a] = FLT_MIN;
		}
		if (apply_dgdep && fabs(d2Gdk2[a]) > FLT_MIN)
		{
			double ka = k[a];
			double dka = one * dGdk[a] / d2Gdk2[a] / va.size();// / operator_cols / operator_rows;

			if (fabs(dka) < good_part * fabs(ka))
				k[a] -= dka;
			else
				k[a] -= (dka / fabs(dka)) * good_part * fabs(ka);

			if (k[a] < FLT_MIN) k[a] = FLT_MIN;
		}

	}




}


void ApplyIteration_dipol(long c_apply,
					double one,
					bool apply_dgdep, 
					bool apply_dgdni,
					bool apply_dgdbeta,
					bool apply_dgdomega,
					vector<short> & va,

					long operator_cols,

					vector<double> & ni_A,
					vector<double> & KTi_A,
					vector<double> & beta_A,
					vector<double> & omega_A,
					double * Ep,

					vector<double> & dGdni_A,
					vector<double> & d2Gdni2_A,
					vector<double> & dGdKTi_A,
					vector<double> & d2GdKTi2_A,
					vector<double> & dGdbeta_A,
					vector<double> & d2Gdbeta2_A,
					vector<double> & dGdomega_A,
					vector<double> & d2Gdomega2_A,
					vector<double> & dGdEp,
					vector<double> & d2GdEp2,

					vector<double> & ni_B,
					vector<double> & KTi_B,
					vector<double> & beta_B,
					vector<double> & omega_B,
					double * k,

					vector<double> & dGdni_B,
					vector<double> & d2Gdni2_B,
					vector<double> & dGdKTi_B,
					vector<double> & d2GdKTi2_B,
					vector<double> & dGdbeta_B,
					vector<double> & d2Gdbeta2_B,
					vector<double> & dGdomega_B,
					vector<double> & d2Gdomega2_B,
					vector<double> & dGdk,
					vector<double> & d2Gdk2

					)
{
	short a, ia;
	double good_part = 0.2;
	double divider = operator_cols;

	long c0 = 0, cmax = -1;
	if (c_apply < 0)
	{
		c0 = 0;
		cmax = operator_cols;
		divider = operator_cols;
	}
	else
	{
		if (c_apply < operator_cols)
		{
			c0 = c_apply;
			cmax = c_apply + 1;
			divider = double(operator_cols) / 5.0;
		}
	}

	for (long c = c0; c < cmax; c++)
	{
		if (fabs(d2GdKTi2_A[c]) > FLT_MIN)
		{
			double kti_c_A  = KTi_A[c];
			double dkti_c_A  = one * dGdKTi_A[c] / d2GdKTi2_A[c] / divider;// / operator_rows;

			if (fabs(dkti_c_A) < good_part * fabs(kti_c_A))
				KTi_A[c] -= dkti_c_A;
			else
				KTi_A[c] -= (dkti_c_A / fabs(dkti_c_A)) * good_part * fabs(kti_c_A);

			if (KTi_A[c] < FLT_MIN) KTi_A[c] = FLT_MIN;
		}
		if (fabs(d2GdKTi2_B[c]) > FLT_MIN)
		{
			double kti_c_B  = KTi_B[c];
			double dkti_c_B  = one * dGdKTi_B[c] / d2GdKTi2_B[c] / divider;// / operator_rows;

			if (fabs(dkti_c_B) < good_part * fabs(kti_c_B))
				KTi_B[c] -= dkti_c_B;
			else
				KTi_B[c] -= (dkti_c_B / fabs(dkti_c_B)) * good_part * fabs(kti_c_B);

			if (KTi_B[c] < FLT_MIN) KTi_B[c] = FLT_MIN;
		}

		if (apply_dgdni && fabs(d2Gdni2_A[c]) > FLT_MIN)
		{
			double ni_c_A = ni_A[c];
			double dni_c_A = one * dGdni_A[c] / d2Gdni2_A[c] / divider;// / operator_rows;

			if (fabs(dni_c_A) < good_part * fabs(ni_c_A))
				ni_A[c] -= dni_c_A;
			else
				ni_A[c] -= (dni_c_A / fabs(dni_c_A)) * good_part * fabs(ni_c_A);

			if (ni_A[c] < FLT_MIN) ni_A[c] = FLT_MIN;
		}

		if (apply_dgdni && fabs(d2Gdni2_B[c]) > FLT_MIN)
		{
			double ni_c_B = ni_B[c];
			double dni_c_B = one * dGdni_B[c] / d2Gdni2_B[c] / divider;// / operator_rows;

			if (fabs(dni_c_B) < good_part * fabs(ni_c_B))
				ni_B[c] -= dni_c_B;
			else
				ni_B[c] -= (dni_c_B / fabs(dni_c_B)) * good_part * fabs(ni_c_B);

			if (ni_B[c] < FLT_MIN) ni_B[c] = FLT_MIN;
		}

		if (apply_dgdbeta && fabs(d2Gdbeta2_A[c]) > FLT_MIN)
		{
			double beta_c_A = beta_A[c];
			double dbeta_c_A = one * dGdbeta_A[c] / d2Gdbeta2_A[c] / divider;// / operator_rows;

			if (fabs(dbeta_c_A) < good_part * fabs(beta_c_A))
				beta_A[c] -= dbeta_c_A;
			else
				beta_A[c] -= (dbeta_c_A / fabs(dbeta_c_A)) * good_part * fabs(beta_c_A);

			if (beta_A[c] < FLT_MIN) beta_A[c] = FLT_MIN;
		}

		if (apply_dgdbeta && fabs(d2Gdbeta2_B[c]) > FLT_MIN)
		{
			double beta_c_B = beta_B[c];
			double dbeta_c_B = one * dGdbeta_B[c] / d2Gdbeta2_B[c] / divider;// / operator_rows;

			if (fabs(dbeta_c_B) < good_part * fabs(beta_c_B))
				beta_B[c] -= dbeta_c_B;
			else
				beta_B[c] -= (dbeta_c_B / fabs(dbeta_c_B)) * good_part * fabs(beta_c_B);

			if (beta_B[c] < FLT_MIN) beta_B[c] = FLT_MIN;
		}

		if (apply_dgdomega && fabs(d2Gdomega2_A[c]) > FLT_MIN)
		{
			double omega_c_A = omega_A[c];
			double domega_c_A = one * dGdomega_A[c] / d2Gdomega2_A[c] / divider;// / operator_rows;

			if (fabs(domega_c_A) < good_part * fabs(omega_c_A))
				omega_A[c] -= domega_c_A;
			else
				omega_A[c] -= (domega_c_A / fabs(domega_c_A)) * good_part * fabs(omega_c_A);

			if (omega_A[c] < FLT_MIN) omega_A[c] = FLT_MIN;
		}

		if (apply_dgdomega && fabs(d2Gdomega2_B[c]) > FLT_MIN)
		{
			double omega_c_B = omega_B[c];
			double domega_c_B = one * dGdomega_B[c] / d2Gdomega2_B[c] / divider;// / operator_rows;

			if (fabs(domega_c_B) < good_part * fabs(omega_c_B))
				omega_B[c] -= domega_c_B;
			else
				omega_B[c] -= (domega_c_B / fabs(domega_c_B)) * good_part * fabs(omega_c_B);

			if (omega_B[c] < FLT_MIN) omega_B[c] = FLT_MIN;
		}


	}

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		if (apply_dgdep && fabs(d2GdEp2[a]) > FLT_MIN)
		{
			double epa = Ep[a];
			double depa = one * dGdEp[a] / d2GdEp2[a] / va.size();// / operator_cols / operator_rows;

			if (fabs(depa) < good_part * fabs(epa))
				Ep[a] -= depa;
			else
				Ep[a] -= (depa / fabs(depa)) * good_part * fabs(epa);

			if (Ep[a] < FLT_MIN) Ep[a] = FLT_MIN;
		}
		if (apply_dgdep && fabs(d2Gdk2[a]) > FLT_MIN)
		{
			double ka = k[a];
			double dka = one * dGdk[a] / d2Gdk2[a] / va.size();// / operator_cols / operator_rows;

			if (fabs(dka) < good_part * fabs(ka))
				k[a] -= dka;
			else
				k[a] -= (dka / fabs(dka)) * good_part * fabs(ka);

			if (k[a] < FLT_MIN) k[a] = FLT_MIN;
		}

	}
}


struct IterationParam
{
	bool apply;
	double one;
	double min_d2;

	vector<double> * param;
	vector<double> * dGdparam;
	vector<double> * d2Gdparam2;
};

void ApplyIteration_dipol(int use_newton,
						  double one,
						  double min_d2,

					long operator_cols,

					vector<double> * param,
					vector<double> * dGdparam,
					vector<double> * d2Gdparam2

					)
{
	double good_part = 0.2;
	double divider = operator_cols;

	switch(use_newton)
	{
	case 0://spusk
		{
			for (long c = 0; c < operator_cols; c++)
			{
				double param_c  = (*param)[c];
				double dparam_c  = one * (*dGdparam)[c];// / divider;// / operator_rows;

				if (fabs(dparam_c) < good_part * fabs(param_c))
					(*param)[c] -= dparam_c;
				else
					(*param)[c] -= (dparam_c / fabs(dparam_c)) * good_part * fabs(param_c);

				if ((*param)[c] < FLT_MIN) (*param)[c] = FLT_MIN;
				
			}

		}
		break;
	case 1://newton
		{
			for (long c = 0; c < operator_cols; c++)
			{
				if (fabs((*d2Gdparam2)[c]) > FLT_MIN)
				{
					double param_c  = (*param)[c];
					double dparam_c  = one * (*dGdparam)[c] / (*d2Gdparam2)[c];// / divider;// / operator_rows;

					if (fabs(dparam_c) < good_part * fabs(param_c))
						(*param)[c] -= dparam_c;
					else
						(*param)[c] -= (dparam_c / fabs(dparam_c)) * good_part * fabs(param_c);

					if ((*param)[c] < FLT_MIN) (*param)[c] = FLT_MIN;
				}				
			}
		}
		break;
	case 2://modified newton
		{
			for (long c = 0; c < operator_cols; c++)
			{
				double d2_div = (*d2Gdparam2)[c] > min_d2 ? (*d2Gdparam2)[c] : min_d2 ;

				double param_c  = (*param)[c];
				double dparam_c  = one * (*dGdparam)[c] / d2_div;// / divider;// / operator_rows;

				if (fabs(dparam_c) < good_part * fabs(param_c))
					(*param)[c] -= dparam_c;
				else
					(*param)[c] -= (dparam_c / fabs(dparam_c)) * good_part * fabs(param_c);

				if ((*param)[c] < FLT_MIN) (*param)[c] = FLT_MIN;
				
			}

		}
		break;
	}
}

void ApplyIteration_dipol(double one,

					vector<short> & va,

					double * Ep,
					vector<double> & dGdEp,
					vector<double> & d2GdEp2,

					double * k,
					vector<double> & dGdk,
					vector<double> & d2Gdk2
					)
{
	short a, ia;
	double good_part = 0.2;



	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		if (fabs(d2GdEp2[a]) > FLT_MIN)
		{
			double epa = Ep[a];
			double depa = one * dGdEp[a] / d2GdEp2[a] / va.size();// / operator_cols / operator_rows;

			if (fabs(depa) < good_part * fabs(epa))
				Ep[a] -= depa;
			else
				Ep[a] -= (depa / fabs(depa)) * good_part * fabs(epa);

			if (Ep[a] < FLT_MIN) Ep[a] = FLT_MIN;
		}
		if (fabs(d2Gdk2[a]) > FLT_MIN)
		{
			double ka = k[a];
			double dka = one * dGdk[a] / d2Gdk2[a] / va.size();// / operator_cols / operator_rows;

			if (fabs(dka) < good_part * fabs(ka))
				k[a] -= dka;
			else
				k[a] -= (dka / fabs(dka)) * good_part * fabs(ka);

			if (k[a] < FLT_MIN) k[a] = FLT_MIN;
		}

	}
}



void CalcDerivatives(long c_apply,
					bool apply_dgdep, 
					bool apply_dgdni,
					vector<short> & va,

					long operator_rows,
					long operator_cols,
					
					double *** p_A,
					double *** W_p_A,

					vector<double> & ni_A,
					vector<double> & KTi_A,
					double * Ep,
					
					vector<vector<double> > & Er_A,
					vector<vector<double> > & S,

					vector<double> & dGdni_A,
					vector<double> & d2Gdni2_A,
					vector<double> & dGdKTi_A,
					vector<double> & d2GdKTi2_A,
					vector<double> & dGdEp,
					vector<double> & d2GdEp2,

					vector<vector<double> > & temp_A,
					vector<vector<double> > & temp52_A,
					
					double *** p_B,
					double *** W_p_B,

					vector<double> & ni_B,
					vector<double> & KTi_B,
					double * k,
					double * s,

					vector<vector<double> > & Er_B,

					vector<double> & dGdni_B,
					vector<double> & d2Gdni2_B,
					vector<double> & dGdKTi_B,
					vector<double> & d2GdKTi2_B,
					vector<double> & dGdk,
					vector<double> & d2Gdk2,
					vector<vector<double> > & temp_B,
					vector<vector<double> > & temp52_B
					 
					 )
{						
	short a, ia;
	
	long c0 = 0, cmax = -1;
	if (c_apply < 0)
	{
		c0 = 0;
		cmax = operator_cols;
	}
	else
	{
		if (c_apply < operator_cols)
		{
			c0 = c_apply;
			cmax = c_apply + 1;
		}
	}
	const double one_per_sqrt_pi = 1.0 / sqrt(PI);
	const double two_per_sqrt_pi = 2.0 / sqrt(PI);
	const double four_per_sqrt_pi = 4.0 / sqrt(PI);

	double W_p_a_r_c_S_a_r_A;// = W_p[a][r][c];
	double W_p_a_r_c_S_a_r_B;// = W_p[a][r][c];
	//double dGdni_abs_sub_A = 0.0;
	//double d2Gdni2_abs_sub_A = 0.0;
	//double dGdni_abs_sub_B = 0.0;
	//double d2Gdni2_abs_sub_B = 0.0;
	if (apply_dgdni)
	{
		for (long c = c0; c < cmax; c++)
		{
			dGdni_A[c] = 0.0;
			d2Gdni2_A[c] = 0.0;
			dGdni_B[c] = 0.0;
			d2Gdni2_B[c] = 0.0;
			for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
			
				for (long r = 0; r < operator_rows; r++)
				{
					W_p_a_r_c_S_a_r_A = S[a][r] * W_p_A[a][r][c];
					dGdni_A[c] += W_p_a_r_c_S_a_r_A * Er_A[a][r];
					d2Gdni2_A[c] += W_p_a_r_c_S_a_r_A * W_p_a_r_c_S_a_r_A;

					W_p_a_r_c_S_a_r_B = s[a] * S[a][r] * W_p_B[a][r][c];
					dGdni_B[c] += W_p_a_r_c_S_a_r_B * Er_B[a][r];
					d2Gdni2_B[c] += W_p_a_r_c_S_a_r_B * W_p_a_r_c_S_a_r_B;
				}
			}
			//double agdni_c = dGdni[c];
			//double ag2dni2_c = d2Gdni2[c];

			//dGdni_abs_sub_A += fabs(dGdni_A[c]);
			//d2Gdni2_abs_sub_A += fabs(d2Gdni2_A[c]);
			//dGdni_abs_sub_B += fabs(dGdni_B[c]);
			//d2Gdni2_abs_sub_B += fabs(d2Gdni2_B[c]);
		}
	}
	//double dGdEp_abs_sub_A = 0.0;
	//double d2GdEp2_abs_sub_A = 0.0;
	//double dGdk_abs_sub_B = 0.0;
	//double d2Gdk2_abs_sub_B = 0.0;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		if (apply_dgdep)
		{
			dGdEp[a] = 0.0;
			d2GdEp2[a] = 0.0;

			dGdk[a] = 0.0;
			d2Gdk2[a] = 0.0;

			for (long r = 0; r < operator_rows; r++)
			{
				double tmp_A = 0.0;
				double tmp_B = 0.0;
				for (long c = 0; c < operator_cols; c++)
				{
					double _p_A = p_A[a][r][c];
					double _p_B = p_B[a][r][c];
					tmp_A += ni_A[c] * pow(_p_A, 1.5) * exp(-_p_A);
					tmp_B += ni_B[c] * pow(_p_B, 1.5) * exp(-_p_B);
				}
				tmp_A *= S[a][r];
				tmp_B *= S[a][r];
				d2GdEp2[a] += tmp_A * tmp_A;
				d2Gdk2[a] += tmp_B * tmp_B;
			}
			d2GdEp2[a] *= four_per_sqrt_pi;
			d2Gdk2[a] *= s[a] * four_per_sqrt_pi;
		}
		for (long c = c0; c < cmax; c++)
		{
			temp_A[a][c] = 0.0;
			temp52_A[a][c] = 0.0;
			temp_B[a][c] = 0.0;
			temp52_B[a][c] = 0.0;
			for (long r = 0; r < operator_rows; r++)
			{
				double _p_A = p_A[a][r][c];
				temp_A[a][c] += pow(_p_A, 1.5) * exp(-_p_A) * Er_A[a][r] * S[a][r];
				temp52_A[a][c] += pow(_p_A, 2.5) * exp(-_p_A) * Er_A[a][r] * S[a][r];

				double _p_B = p_B[a][r][c];
				temp_B[a][c] += pow(_p_B, 1.5) * exp(-_p_B) * Er_B[a][r] * S[a][r];
				temp52_B[a][c] += pow(_p_B, 2.5) * exp(-_p_B) * Er_B[a][r] * S[a][r];
			}
			//double temp_a_c = temp[a][c];
			temp_A[a][c] *= ni_A[c];
			temp52_A[a][c] *= ni_A[c];

			temp_B[a][c] *= ni_B[c];
			temp52_B[a][c] *= ni_B[c];
			//temp_a_c = temp[a][c];

			if (apply_dgdep)
			{
				dGdEp[a] += temp_A[a][c];
				d2GdEp2[a] += 2.0 * temp52_A[a][c] - temp_A[a][c];

				dGdk[a] += temp_B[a][c];
				d2Gdk2[a] += 2.0 * temp52_B[a][c] - temp_B[a][c];
			}

		}
		if (apply_dgdep)
		{
			dGdEp[a] *= -two_per_sqrt_pi / Ep[a];
			d2GdEp2[a] *= one_per_sqrt_pi / (Ep[a] * Ep[a]);
			
			dGdk[a] *= - s[a] * two_per_sqrt_pi / k[a];
			d2Gdk2[a] *= s[a] * one_per_sqrt_pi / (k[a] * k[a]);
			
			//double adgep_a = dGdEp[a];
			//double ad2gep2_a = d2GdEp2[a];

			//dGdEp_abs_sub_A += fabs(dGdEp[a]);
			//d2GdEp2_abs_sub_A += fabs(d2GdEp2[a]);

			//dGdk_abs_sub_B += fabs(dGdk[a]);
			//d2Gdk2_abs_sub_B += fabs(d2Gdk2[a]);
		}
	}

	//double dGdKTi_abs_sub_A = 0.0;
	//double d2GdKTi2_abs_sub_A = 0.0;
	//double dGdKTi_abs_sub_B = 0.0;
	//double d2GdKTi2_abs_sub_B = 0.0;
	for (long c = c0; c < cmax; c++)
	{
		dGdKTi_A[c] = 0.0;
		d2GdKTi2_A[c] = 0.0;
		dGdKTi_B[c] = 0.0;
		d2GdKTi2_B[c] = 0.0;
		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
			double tmp2_A = 0.0;
			double tmp2_B = 0.0;
			for (long r = 0; r < operator_rows; r++)
			{
				double _p_A = p_A[a][r][c];
				double tmp_A = pow(_p_A, 1.5) * exp(-_p_A) * S[a][r];
				tmp2_A += tmp_A * tmp_A;

				double _p_B = p_B[a][r][c];
				double tmp_B = pow(_p_B, 1.5) * exp(-_p_B) * S[a][r];
				tmp2_B += tmp_B * tmp_B;
			}
			tmp2_A *= ni_A[c] * ni_A[c];
			tmp2_B *= s[a] * s[a] * ni_B[c] * ni_B[c];
			d2GdKTi2_A[c] += tmp2_A;
			d2GdKTi2_B[c] += tmp2_B;
		}
		d2GdKTi2_A[c] *= four_per_sqrt_pi;
		d2GdKTi2_B[c] *= four_per_sqrt_pi;
		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены						
			dGdKTi_A[c] +=  temp_A[a][c];	
			d2GdKTi2_A[c] += 2.0 * temp52_A[a][c] - 5.0 * temp_A[a][c];	
			dGdKTi_B[c] +=  s[a] * temp_B[a][c];	
			d2GdKTi2_B[c] += s[a] * (2.0 * temp52_B[a][c] - 5.0 * temp_B[a][c]);	
		}
		dGdKTi_A[c] *= two_per_sqrt_pi / KTi_A[c];
		d2GdKTi2_A[c] *= one_per_sqrt_pi / (KTi_A[c] * KTi_A[c]);
		dGdKTi_B[c] *= two_per_sqrt_pi / KTi_B[c];
		d2GdKTi2_B[c] *= one_per_sqrt_pi / (KTi_B[c] * KTi_B[c]);


		//double adgkt_c = dGdKTi[c];
		//double ad2gkt2_c = d2GdKTi2[c];
		//double ktic = KTi[c];

		//dGdKTi_abs_sub_A += fabs(dGdKTi_A[c]);
		//d2GdKTi2_abs_sub_A += fabs(d2GdKTi2_A[c]);

		//dGdKTi_abs_sub_B += fabs(dGdKTi_B[c]);
		//d2GdKTi2_abs_sub_B += fabs(d2GdKTi2_B[c]);
	}


	/*
	printf ("dGdKTi_abs_sub = %f %e\tdGdni_abs_sub = %f\tdGdEp_abs_sub = %f\n",
		dGdKTi_abs_sub, dGdKTi_abs_sub, dGdni_abs_sub, dGdEp_abs_sub);
	printf ("d2GdKTi2_abs_sub = %f %e\td2Gdni2_abs_sub = %f\td2GdEp2_abs_sub = %f\n",
		d2GdKTi2_abs_sub, d2GdKTi2_abs_sub, d2Gdni2_abs_sub, d2GdEp2_abs_sub);
	
	printf ("dKTi_abs_sub = %f %e\tdni_abs_sub = %f\tdEp_abs_sub = %f\n",
		dGdKTi_abs_sub/d2GdKTi2_abs_sub, 
		dGdKTi_abs_sub/d2GdKTi2_abs_sub, 
		dGdni_abs_sub/d2Gdni2_abs_sub,
		dGdEp_abs_sub/d2GdEp2_abs_sub);
		*/
	///
}

void CalcDerivatives_dipol(long c_apply, long apply_B,
					bool apply_dgdep, 
					bool apply_dgdni,
					vector<short> & va,

					long operator_rows,
					long operator_cols,

					double pw,
					double *** R,// указатель на три матрицы rx, ry, rz
					vector<vector<anten_direction> > & A,
					
					double *** p_A,
					double *** W_p_A,

					vector<double> & ni_A,
					vector<double> & KTi_A,
					vector<double> & beta_A,
					vector<double> & omega_A,
					double * Ep,
					
					vector<vector<double> > & Er_A,
					vector<vector<double> > & S,

					vector<double> & dGdni_A,
					vector<double> & d2Gdni2_A,
					vector<double> & dGdKTi_A,
					vector<double> & d2GdKTi2_A,
					vector<double> & dGdbeta_A,
					vector<double> & d2Gdbeta2_A,
					vector<double> & dGdomega_A,
					vector<double> & d2Gdomega2_A,
					vector<double> & dGdEp,
					vector<double> & d2GdEp2,

					vector<vector<double> > & temp_A,
					vector<vector<double> > & temp52_A,
					
					double *** p_B,
					double *** W_p_B,

					vector<double> & ni_B,
					vector<double> & KTi_B,
					vector<double> & beta_B,
					vector<double> & omega_B,
					double * k,
					double * s,

					vector<vector<double> > & Er_B,

					vector<double> & dGdni_B,
					vector<double> & d2Gdni2_B,
					vector<double> & dGdKTi_B,
					vector<double> & d2GdKTi2_B,
					vector<double> & dGdbeta_B,
					vector<double> & d2Gdbeta2_B,
					vector<double> & dGdomega_B,
					vector<double> & d2Gdomega2_B,
					vector<double> & dGdk,
					vector<double> & d2Gdk2,
					vector<vector<double> > & temp_B,
					vector<vector<double> > & temp52_B
					 )
{
	short a, ia;
	
	long c0 = 0, cmax = -1;
	if (c_apply < 0)
	{
		c0 = 0;
		cmax = operator_cols;
	}
	else
	{
		if (c_apply < operator_cols)
		{
			c0 = c_apply;
			cmax = c_apply + 1;
		}
	}
	const double one_per_sqrt_pi = 1.0 / sqrt(PI);
	const double two_per_sqrt_pi = 2.0 / sqrt(PI);
	const double four_per_sqrt_pi = 4.0 / sqrt(PI);

	double W_p_a_r_c_S_a_r_A;// = W_p[a][r][c];
	double W_p_a_r_c_S_a_r_B;// = W_p[a][r][c];
	//double dGdni_abs_sub_A = 0.0;
	//double d2Gdni2_abs_sub_A = 0.0;
	//double dGdni_abs_sub_B = 0.0;
	//double d2Gdni2_abs_sub_B = 0.0;
	if (apply_dgdni)
	{
		for (long c = c0; c < cmax; c++)
		{
			dGdni_A[c] = 0.0;
			d2Gdni2_A[c] = 0.0;
			dGdni_B[c] = 0.0;
			d2Gdni2_B[c] = 0.0;
			for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
			
				for (long r = 0; r < operator_rows; r++)
				{
					W_p_a_r_c_S_a_r_A = S[a][r] * W_p_A[a][r][c];
					dGdni_A[c] += W_p_a_r_c_S_a_r_A * Er_A[a][r];
					d2Gdni2_A[c] += W_p_a_r_c_S_a_r_A * W_p_a_r_c_S_a_r_A;
                }
                if (apply_B){
                for (long r = 0; r < operator_rows; r++)
                {

					W_p_a_r_c_S_a_r_B = s[a] * S[a][r] * W_p_B[a][r][c];
					dGdni_B[c] += W_p_a_r_c_S_a_r_B * Er_B[a][r];
					d2Gdni2_B[c] += W_p_a_r_c_S_a_r_B * W_p_a_r_c_S_a_r_B;
				}
                }
			}
			//double agdni_c = dGdni[c];
			//double ag2dni2_c = d2Gdni2[c];

			//dGdni_abs_sub_A += fabs(dGdni_A[c]);
			//d2Gdni2_abs_sub_A += fabs(d2Gdni2_A[c]);
			//dGdni_abs_sub_B += fabs(dGdni_B[c]);
			//d2Gdni2_abs_sub_B += fabs(d2Gdni2_B[c]);
		}
	}


	//double dGdEp_abs_sub_A = 0.0;
	//double d2GdEp2_abs_sub_A = 0.0;
	//double dGdk_abs_sub_B = 0.0;
	//double d2Gdk2_abs_sub_B = 0.0;

	double ax, ay, az;
	double rx, ry, rz;

	double ddet_dbeta_div_det_A;
	double ddet_domega_div_det_A;				
	double ddet_dbeta_div_det_B;
	double ddet_domega_div_det_B;				

	double d2det_dbeta2_div_det_A;
	double d2det_domega2_div_det_A;				
	double d2det_dbeta2_div_det_B;
	double d2det_domega2_div_det_B;				

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		if (apply_dgdep)
		{
			dGdEp[a] = 0.0;
			d2GdEp2[a] = 0.0;

			dGdk[a] = 0.0;
			d2Gdk2[a] = 0.0;

			for (long r = 0; r < operator_rows; r++)
			{
				double tmp_A = 0.0;
				double tmp_B = 0.0;
				for (long c = 0; c < operator_cols; c++)
				{
					double _p_A = p_A[a][r][c];
					tmp_A += ni_A[c] * pow(_p_A, 1.5) * exp(-_p_A);
                }
                if (apply_B) {
                for (long c = 0; c < operator_cols; c++)
                {
                    double _p_B = p_B[a][r][c];
                    tmp_B += ni_B[c] * pow(_p_B, 1.5) * exp(-_p_B);
				}
                }
				tmp_A *= S[a][r];
                d2GdEp2[a] += tmp_A * tmp_A;
                if (apply_B) {
				tmp_B *= S[a][r];
                d2Gdk2[a] += tmp_B * tmp_B;
                }
			}
			d2GdEp2[a] *= four_per_sqrt_pi;
			d2Gdk2[a] *= s[a] * four_per_sqrt_pi;
		}
		for (long c = c0; c < cmax; c++)
		{
			temp_A[a][c] = 0.0;
			temp52_A[a][c] = 0.0;
            if (apply_B) {
			temp_B[a][c] = 0.0;
			temp52_B[a][c] = 0.0;
            }

			dGdbeta_A[c] = 0.0;
			d2Gdbeta2_A[c] = 0.0;
            if (apply_B) {
			dGdbeta_B[c] = 0.0;
			d2Gdbeta2_B[c] = 0.0;
            }

			dGdomega_A[c] = 0.0;
			d2Gdomega2_A[c] = 0.0;
            if (apply_B) {
			dGdomega_B[c] = 0.0;
			d2Gdomega2_B[c] = 0.0;
            }

			for (long r = 0; r < operator_rows; r++)
			{
				ax = A[a][r].ax;
				ay = A[a][r].ay;
				az = A[a][r].az;

				rx = R[0][r][c];
				ry = R[1][r][c];
				rz = R[2][r][c];

				ddet_dbeta_domega_div_det(beta_A[c], omega_A[c], 
					rx, ry, rz, 
					ax, ay, az,

					ddet_dbeta_div_det_A,
					ddet_domega_div_det_A,
					d2det_dbeta2_div_det_A,
					d2det_domega2_div_det_A
					);

                if (apply_B) {

				ddet_dbeta_domega_div_det(beta_B[c], omega_B[c], 
					rx, ry, rz, 
					ax, ay, az,

					ddet_dbeta_div_det_B,
					ddet_domega_div_det_B,
					d2det_dbeta2_div_det_B,
					d2det_domega2_div_det_B
					);
                }

				double _p_A = p_A[a][r][c];
				double tmp_A = pow(_p_A, 1.5) * exp(-_p_A) * S[a][r];
				double tmpe_A = tmp_A * Er_A[a][r];
				temp_A[a][c] += tmpe_A;
				temp52_A[a][c] += pow(_p_A, 2.5) * exp(-_p_A) * Er_A[a][r] * S[a][r];



				dGdbeta_A[c] += tmpe_A * ddet_dbeta_div_det_A;
				dGdomega_A[c] += tmpe_A * ddet_domega_div_det_A;

				d2Gdbeta2_A[c] += two_per_sqrt_pi * pw * ni_A[c] * pow (tmp_A * ddet_dbeta_div_det_A, 2.0);
				d2Gdomega2_A[c] += two_per_sqrt_pi * pw * ni_A[c] * pow (tmp_A * ddet_domega_div_det_A, 2.0);

				d2Gdbeta2_A[c] += tmpe_A * d2det_dbeta2_div_det_A;
				d2Gdomega2_A[c] += tmpe_A * d2det_domega2_div_det_A;

				d2Gdbeta2_A[c] += (temp52_A[a][c] - (1.5 + (1.0 / pw)) * tmpe_A) * pw * ddet_dbeta_div_det_A * ddet_dbeta_div_det_A;
				d2Gdomega2_A[c] += (temp52_A[a][c] - (1.5 + (1.0 / pw)) * tmpe_A) * pw * ddet_domega_div_det_A * ddet_domega_div_det_A;

                if (apply_B) {
                double _p_B = p_B[a][r][c];
                double tmp_B = pow(_p_B, 1.5) * exp(-_p_B) * S[a][r];
                double tmpe_B = tmp_B * Er_B[a][r];
                temp_B[a][c] += tmpe_B;
                temp52_B[a][c] += pow(_p_B, 2.5) * exp(-_p_B) * Er_B[a][r] * S[a][r];
                dGdbeta_B[c] += s[a] * tmpe_B * ddet_dbeta_div_det_B;
                dGdomega_B[c] += s[a] * tmpe_B * ddet_domega_div_det_B;
                d2Gdbeta2_B[c] += two_per_sqrt_pi * pw * ni_B[c] * pow (s[a] * tmp_B * ddet_dbeta_div_det_B, 2.0);
                d2Gdomega2_B[c] += two_per_sqrt_pi * pw * ni_B[c] * pow (s[a] * tmp_B * ddet_domega_div_det_B, 2.0);
                d2Gdbeta2_B[c] += s[a] * tmpe_B * d2det_dbeta2_div_det_B;
                d2Gdomega2_B[c] += s[a] * tmpe_B * d2det_domega2_div_det_B;
                d2Gdbeta2_B[c] += s[a] * (temp52_B[a][c] - (1.5 + (1.0 / pw)) * tmpe_B) * pw * ddet_dbeta_div_det_B * ddet_dbeta_div_det_B;
                d2Gdomega2_B[c] += s[a] * (temp52_B[a][c] - (1.5 + (1.0 / pw)) * tmpe_B) * pw * ddet_domega_div_det_B * ddet_domega_div_det_B;
                }
			}
			//double temp_a_c = temp[a][c];
			temp_A[a][c] *= ni_A[c];
			temp52_A[a][c] *= ni_A[c];

            if (apply_B) {
			temp_B[a][c] *= ni_B[c];
			temp52_B[a][c] *= ni_B[c];
            }
			//temp_a_c = temp[a][c];

			if (apply_dgdep)
			{
				dGdEp[a] += temp_A[a][c];
				d2GdEp2[a] += 2.0 * temp52_A[a][c] - temp_A[a][c];

                if (apply_B) {
				dGdk[a] += temp_B[a][c];
				d2Gdk2[a] += 2.0 * temp52_B[a][c] - temp_B[a][c];
                }
			}

		}
		if (apply_dgdep)
		{
			dGdEp[a] *= -two_per_sqrt_pi / Ep[a];
			d2GdEp2[a] *= one_per_sqrt_pi / (Ep[a] * Ep[a]);
			
			dGdk[a] *= - s[a] * two_per_sqrt_pi / k[a];
			d2Gdk2[a] *= s[a] * one_per_sqrt_pi / (k[a] * k[a]);
			
			//double adgep_a = dGdEp[a];
			//double ad2gep2_a = d2GdEp2[a];

			//dGdEp_abs_sub_A += fabs(dGdEp[a]);
			//d2GdEp2_abs_sub_A += fabs(d2GdEp2[a]);

			//dGdk_abs_sub_B += fabs(dGdk[a]);
			//d2Gdk2_abs_sub_B += fabs(d2Gdk2[a]);
		}
	}

	//double dGdKTi_abs_sub_A = 0.0;
	//double d2GdKTi2_abs_sub_A = 0.0;
	//double dGdKTi_abs_sub_B = 0.0;
	//double d2GdKTi2_abs_sub_B = 0.0;
	for (long c = c0; c < cmax; c++)
	{
		dGdKTi_A[c] = 0.0;
		d2GdKTi2_A[c] = 0.0;
		dGdKTi_B[c] = 0.0;
		d2GdKTi2_B[c] = 0.0;

		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
			double tmp2_A = 0.0;
			double tmp2_B = 0.0;
			for (long r = 0; r < operator_rows; r++)
			{
				double _p_A = p_A[a][r][c];
				double tmp_A = pow(_p_A, 1.5) * exp(-_p_A) * S[a][r];
				tmp2_A += tmp_A * tmp_A;
            }
            if (apply_B) {
            for (long r = 0; r < operator_rows; r++)
            {

				double _p_B = p_B[a][r][c];
				double tmp_B = pow(_p_B, 1.5) * exp(-_p_B) * S[a][r];
				tmp2_B += tmp_B * tmp_B;
                }
			}
			tmp2_A *= ni_A[c] * ni_A[c];
            d2GdKTi2_A[c] += tmp2_A;
            if (apply_B) {
			tmp2_B *= s[a] * s[a] * ni_B[c] * ni_B[c];
            d2GdKTi2_B[c] += tmp2_B;
            }
		}
		d2GdKTi2_A[c] *= four_per_sqrt_pi;
        if (apply_B) {
		d2GdKTi2_B[c] *= four_per_sqrt_pi;
        }
		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены						
			dGdKTi_A[c] +=  temp_A[a][c];	
            d2GdKTi2_A[c] += 2.0 * temp52_A[a][c] - 5.0 * temp_A[a][c];
            if (apply_B) {
			dGdKTi_B[c] +=  s[a] * temp_B[a][c];	
			d2GdKTi2_B[c] += s[a] * (2.0 * temp52_B[a][c] - 5.0 * temp_B[a][c]);
            }
		}
		dGdKTi_A[c] *= two_per_sqrt_pi / KTi_A[c];
		d2GdKTi2_A[c] *= one_per_sqrt_pi / (KTi_A[c] * KTi_A[c]);
        if (apply_B) {
		dGdKTi_B[c] *= two_per_sqrt_pi / KTi_B[c];
		d2GdKTi2_B[c] *= one_per_sqrt_pi / (KTi_B[c] * KTi_B[c]);
        }


		dGdbeta_A[c] *= two_per_sqrt_pi * pw * ni_A[c];
		dGdomega_A[c] *= two_per_sqrt_pi * pw * ni_A[c];
		d2Gdbeta2_A[c] *= two_per_sqrt_pi * pw * ni_A[c];
		d2Gdomega2_A[c] *= two_per_sqrt_pi * pw * ni_A[c];

        if (apply_B) {
        dGdbeta_B[c] *= two_per_sqrt_pi * pw * ni_B[c];
        dGdomega_B[c] *= two_per_sqrt_pi * pw * ni_B[c];
        d2Gdbeta2_B[c] *= two_per_sqrt_pi * pw * ni_B[c];
        d2Gdomega2_B[c] *= two_per_sqrt_pi * pw * ni_B[c];
        }
        /*
		d2Gdbeta2_A[c] = 1.0;
		d2Gdbeta2_B[c] = 1.0;

		d2Gdomega2_A[c] = 1.0;
		d2Gdomega2_B[c] = 1.0;
*/
		//double adgkt_c = dGdKTi[c];
		//double ad2gkt2_c = d2GdKTi2[c];
		//double ktic = KTi[c];

		//dGdKTi_abs_sub_A += fabs(dGdKTi_A[c]);
		//d2GdKTi2_abs_sub_A += fabs(d2GdKTi2_A[c]);

		//dGdKTi_abs_sub_B += fabs(dGdKTi_B[c]);
		//d2GdKTi2_abs_sub_B += fabs(d2GdKTi2_B[c]);
	}


	/*
	printf ("dGdKTi_abs_sub = %f %e\tdGdni_abs_sub = %f\tdGdEp_abs_sub = %f\n",
		dGdKTi_abs_sub, dGdKTi_abs_sub, dGdni_abs_sub, dGdEp_abs_sub);
	printf ("d2GdKTi2_abs_sub = %f %e\td2Gdni2_abs_sub = %f\td2GdEp2_abs_sub = %f\n",
		d2GdKTi2_abs_sub, d2GdKTi2_abs_sub, d2Gdni2_abs_sub, d2GdEp2_abs_sub);
	
	printf ("dKTi_abs_sub = %f %e\tdni_abs_sub = %f\tdEp_abs_sub = %f\n",
		dGdKTi_abs_sub/d2GdKTi2_abs_sub, 
		dGdKTi_abs_sub/d2GdKTi2_abs_sub, 
		dGdni_abs_sub/d2Gdni2_abs_sub,
		dGdEp_abs_sub/d2GdEp2_abs_sub);
		*/
	///
}

void ForwordOperatorApply_dipol(long c_apply, bool apply_B,
						  double & GA,
						  double & GB,
						  vector<short> & va,
						  double *** m, // три матрицы njuX, njuY, njuZ
						  double *** R,// указатель на три матрицы rx, ry, rz
						  vector<vector<anten_direction> > & A,
						  vector<vector<double> > & W,
                          
						  long operator_rows,
						  long operator_cols,

						  double *** p_A,
						  double *** W_p_A,
						  
						  vector<double> & ni_A,
						  vector<double> & KTi_A,
						  vector<double> & beta_A,
						  vector<double> & omega_A,
						  double * Ep,
#if 0
						  vector<vector<vector<double> > > & CJI_A,
#else
                          double*** CJI_A,
#endif
						  vector<vector<double> > & C_A,
						  vector<vector<double> > & Er_A,
						  vector<vector<double> > & S,

						  double *** p_B,
						  double *** W_p_B,
						  
						  vector<double> & ni_B,
						  vector<double> & KTi_B,
						  vector<double> & beta_B,
						  vector<double> & omega_B,
						  
						  double * k,
						  double * s,
						  double * mean_B_B,
#if 0
						  vector<vector<vector<double> > > & CJI_B,
#else
                          double*** CJI_B,
#endif
						  vector<vector<double> > & C_B,
						  vector<vector<double> > & Er_B

						  )
{
	short a, ia;

	long c0 = 0, cmax = -1;
	if (c_apply < 0)
	{
		c0 = 0;
		cmax = operator_cols;
	}
	else
	{
		if (c_apply < operator_cols)
		{
			c0 = c_apply;
			cmax = c_apply + 1;
		}
	}
	//double W_P(double p)
	//{
	//	return 1.0 + 2.0 * sqrt (p / PI) * exp(-p) - alglib::errorfunction(sqrt(P));
	//}

	double ax, ay, az;
	double rx, ry, rz;

	double nju_phi_min = DBL_MAX;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			ax = A[a][r].ax;
			ay = A[a][r].ay;
			az = A[a][r].az;

			for (long c = c0; c < cmax; c++)
			{
				rx = R[0][r][c];
				ry = R[1][r][c];
				rz = R[2][r][c];
				//double ktic = KTi[c], epa = Ep[a], marc = m[a][r][c];
				// коэффициент выхода диаграммы направленности
				double nju_phi_A = nju_phi_calc(beta_A[c], omega_A[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_A > DBL_MIN && nju_phi_A < nju_phi_min)
					nju_phi_min = nju_phi_A;

                if (apply_B){

				// коэффициент выхода диаграммы направленности
				double nju_phi_B = nju_phi_calc(beta_B[c], omega_B[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_B > DBL_MIN && nju_phi_B < nju_phi_min)
					nju_phi_min = nju_phi_B;
                }
			}
		}
	}

	double zero_substitution = 0.9 * nju_phi_min;

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			ax = A[a][r].ax;
			ay = A[a][r].ay;
			az = A[a][r].az;

			for (long c = c0; c < cmax; c++)
			{
				rx = R[0][r][c];
				ry = R[1][r][c];
				rz = R[2][r][c];
				//double ktic = KTi[c], epa = Ep[a], marc = m[a][r][c];
				// коэффициент выхода диаграммы направленности
				double nju_phi_A = nju_phi_calc(beta_A[c], omega_A[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_A < zero_substitution)
					nju_phi_A = zero_substitution;

				double _p_A = Ep[a] / (m[a][r][c] * nju_phi_A * KTi_A[c]);
				p_A[a][r][c] = _p_A;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_A[a][r][c] = alglib::errorfunctionc(sqrt(_p_A)) + 2.0 * sqrt (_p_A / PI) * exp(-_p_A);
				//double W_p_a_r_c_A = W_p_A[a][r][c];
				CJI_A[a][r][c] = S[a][r] * ni_A[c] * W_p_A[a][r][c];

                if (apply_B){
				
				// коэффициент выхода диаграммы направленности
				double nju_phi_B = nju_phi_calc(beta_B[c], omega_B[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_B < zero_substitution)
					nju_phi_B = zero_substitution;

				double _p_B = k[a] * W[a+6][r] / (m[a][r][c] * nju_phi_B * KTi_B[c]);
				p_B[a][r][c] = _p_B;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_B[a][r][c] = alglib::errorfunctionc(sqrt(_p_B)) + 2.0 * sqrt (_p_B / PI) * exp(-_p_B);
				//double W_p_a_r_c_B = W_p_B[a][r][c];
				CJI_B[a][r][c] = S[a][r] * ni_B[c] * W_p_B[a][r][c];
                }
			}
		}
	}


	size_t W_size = W.size();
	double mean_CB[3];

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		mean_CB[a] = 0.0;
		for (long r = 0; r < operator_rows; r++)
		{
			// Выход оператора прямой задачи
			C_A[a][r] = 0.0;
            if (apply_B) {
			C_B[a][r] = 0.0;
            }
			for (long c = 0; c < operator_cols; c++)
			{
				//double nic = ni[c], W_p_a_r_c = W_p[a][r][c];
				//C_A[a][r] += S[a][r] * ni_A[c] * W_p_A[a][r][c];
				//C_B[a][r] += S[a][r] * ni_B[c] * W_p_B[a][r][c];
				C_A[a][r] += CJI_A[a][r][c];
            }
            if (apply_B) {
                for (long c = 0; c < operator_cols; c++)
                {
                    C_B[a][r] += CJI_B[a][r][c];
                }
			}							
			//double car = C[a][r], war = W[a][r];
			//size_t W_a_size = W[a].size();
            if (apply_B) {
			mean_CB[a] += C_B[a][r];
            }
		}
        if (apply_B) {
		mean_CB[a] /= operator_rows;
		if (mean_CB[a] != 0.0)
			s[a] = mean_B_B[a] / mean_CB[a];
		else
			s[a] = 0.0;
        }

		//поправка Выхода оператора прямой задачи
		for (long r = 0; r < operator_rows; r++)
		{
			// Невязка
			Er_A[a][r] = C_A[a][r] - W[a][r];//режим А
        }
        if (apply_B) {
            for (long r = 0; r < operator_rows; r++){
                C_B[a][r] *= s[a];
                Er_B[a][r] = C_B[a][r] - W[a+3][r];//режим B
            }
		}
	}

	GA = 0.0;
	GB = 0.0;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			//if(r == operator_rows - 1)
			//{
			//	double sad = 0;
			//}
			double ear_A = Er_A[a][r];
			GA += Er_A[a][r] * Er_A[a][r];
        }
        if (apply_B) {
        for (long r = 0; r < operator_rows; r++)
        {
            double ear_B = Er_B[a][r];
            GB += Er_B[a][r] * Er_B[a][r];
		}
        }
	}
	GA /= 2.0;
    if (apply_B) {
	GB /= 2.0;
    }

}

void ForwordOperatorApply(long c_apply,
						  double & GA,
						  double & GB,
						  vector<short> & va,
						  double *** m, // три матрицы njuX, njuY, njuZ
						  vector<vector<double> > & W,
                          
						  long operator_rows,
						  long operator_cols,

						  double *** p_A,
						  double *** W_p_A,
						  
						  vector<double> & ni_A,
						  vector<double> & KTi_A,
						  double * Ep,

						  vector<vector<vector<double> > > & CJI_A,
						  vector<vector<double> > & C_A,
						  vector<vector<double> > & Er_A,
						  vector<vector<double> > & S,

						  double *** p_B,
						  double *** W_p_B,
						  
						  vector<double> & ni_B,
						  vector<double> & KTi_B,
						  
						  double * k,
						  double * s,
						  double * mean_B_B,
						  
						  vector<vector<vector<double> > > & CJI_B,
						  vector<vector<double> > & C_B,
						  vector<vector<double> > & Er_B

						  )
{
	short a, ia;

	long c0 = 0, cmax = -1;
	if (c_apply < 0)
	{
		c0 = 0;
		cmax = operator_cols;
	}
	else
	{
		if (c_apply < operator_cols)
		{
			c0 = c_apply;
			cmax = c_apply + 1;
		}
	}
	//double W_P(double p)
	//{
	//	return 1.0 + 2.0 * sqrt (p / PI) * exp(-p) - alglib::errorfunction(sqrt(P));
	//}

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			for (long c = c0; c < cmax; c++)
			{
				//double ktic = KTi[c], epa = Ep[a], marc = m[a][r][c];

				double _p_A = Ep[a] / (m[a][r][c] * KTi_A[c]);
				p_A[a][r][c] = _p_A;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_A[a][r][c] = alglib::errorfunctionc(sqrt(_p_A)) + 2.0 * sqrt (_p_A / PI) * exp(-_p_A);
				//double W_p_a_r_c_A = W_p_A[a][r][c];
				CJI_A[a][r][c] = S[a][r] * ni_A[c] * W_p_A[a][r][c];
				
				double _p_B = k[a] * W[a+6][r] / (m[a][r][c] * KTi_B[c]);
				p_B[a][r][c] = _p_B;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_B[a][r][c] = alglib::errorfunctionc(sqrt(_p_B)) + 2.0 * sqrt (_p_B / PI) * exp(-_p_B);
				//double W_p_a_r_c_B = W_p_B[a][r][c];
				CJI_B[a][r][c] = S[a][r] * ni_B[c] * W_p_B[a][r][c];
			}
		}
	}


	size_t W_size = W.size();
	double mean_CB[3];

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		mean_CB[a] = 0.0;
		for (long r = 0; r < operator_rows; r++)
		{
			// Выход оператора прямой задачи
			C_A[a][r] = 0.0;
			C_B[a][r] = 0.0;
			for (long c = 0; c < operator_cols; c++)
			{
				//double nic = ni[c], W_p_a_r_c = W_p[a][r][c];
				//C_A[a][r] += S[a][r] * ni_A[c] * W_p_A[a][r][c];
				//C_B[a][r] += S[a][r] * ni_B[c] * W_p_B[a][r][c];
				C_A[a][r] += CJI_A[a][r][c];
				C_B[a][r] += CJI_B[a][r][c];
			}							
			//double car = C[a][r], war = W[a][r];
			//size_t W_a_size = W[a].size();
			mean_CB[a] += C_B[a][r];
		}
		mean_CB[a] /= operator_rows;
		s[a] = mean_B_B[a] / mean_CB[a];

		//поправка Выхода оператора прямой задачи
		for (long r = 0; r < operator_rows; r++)
		{
			C_B[a][r] *= s[a];
			// Невязка
			Er_A[a][r] = C_A[a][r] - W[a][r];//режим А
			Er_B[a][r] = C_B[a][r] - W[a+3][r];//режим B
		}
	}

	GA = 0.0;
	GB = 0.0;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			//if(r == operator_rows - 1)
			//{
			//	double sad = 0;
			//}
			double ear_A = Er_A[a][r];
			double ear_B = Er_B[a][r];
			GA += Er_A[a][r] * Er_A[a][r];
			GB += Er_B[a][r] * Er_B[a][r];
		}
	}
	GA /= 2.0;
	GB /= 2.0;

}
//теперь предполагаем, что мощность источников:
// 1) постоянна по всей глубине - не зависит от глубины

//double IX(double b, double sqw)
//{
	//mIs_X_hi_w_Ihi = -3/8/b^2/sqw^2/hi+hi*Ei(1,2*hi*b*sqw)-7/12/exp(hi*b*sqw)^2/b/sqw+1/12/exp(hi*b*sqw)^2*hi+1/3*b^2*sqw^2*hi^3*Ei(1,2*hi*b*sqw)-1/6*b*sqw/exp(hi*b*sqw)^2*hi^2+3/8/b^2/sqw^2/hi/exp(hi*b*sqw)^2
//}

//double IZ(double b, double sqw)
//{
	//mIs_Z_hi_w_Ihi = -1/4/b^2/sqw^2/hi+2*hi*Ei(1,2*hi*b*sqw)-5/6/exp(hi*b*sqw)^2/b/sqw-1/6/exp(hi*b*sqw)^2*hi-2/3*b^2*sqw^2*hi^3*Ei(1,2*hi*b*sqw)+1/3*b*sqw/exp(hi*b*sqw)^2*hi^2+1/4/b^2/sqw^2/hi/exp(hi*b*sqw)^2
//}

// 2) пропорциональна корню из глубины
//mIs_X_hi_w_Ihi = -3/4/b^2/sqw^2/hi^(1/2)+10/21/b/sqw*pi^(1/2)*2^(1/2)/(b*sqw)^(1/2)*erf(2^(1/2)*(b*sqw)^(1/2)*hi^(1/2))+2/3*hi^(3/2)*Ei(1,2*hi*b*sqw)-17/42*hi^(1/2)/exp(hi*b*sqw)^2/b/sqw+1/14*hi^(3/2)/exp(hi*b*sqw)^2+2/7*b^2*sqw^2*hi^(7/2)*Ei(1,2*hi*b*sqw)-1/7*b*sqw*hi^(5/2)/exp(hi*b*sqw)^2+3/4/b^2/sqw^2/hi^(1/2)/exp(hi*b*sqw)^2
//mIs_Z_hi_w_Ihi = -1/2/b^2/sqw^2/hi^(1/2)+8/21/b/sqw*pi^(1/2)*2^(1/2)/(b*sqw)^(1/2)*erf(2^(1/2)*(b*sqw)^(1/2)*hi^(1/2))+4/3*hi^(3/2)*Ei(1,2*hi*b*sqw)-11/21*hi^(1/2)/exp(hi*b*sqw)^2/b/sqw-1/7*hi^(3/2)/exp(hi*b*sqw)^2-4/7*b^2*sqw^2*hi^(7/2)*Ei(1,2*hi*b*sqw)+2/7*b*sqw*hi^(5/2)/exp(hi*b*sqw)^2+1/2/b^2/sqw^2/hi^(1/2)/exp(hi*b*sqw)^2


//теперь предполагаем, что мощность источников:
// 1) постоянна по всей глубине - не зависит от глубины
//mIs_X_hi_w_Ihi = 4/3/b/sqw
//mIs_Z_hi_w_Ihi = 4/3/b/sqw

// sqrt(hi)
//mIs_X_hi_w_Ihi = 10/21/b/sqw*pi^(1/2)*2^(1/2)/(b*sqw)^(1/2)
//mIs_Z_hi_w_Ihi =  8/21/b/sqw*pi^(1/2)*2^(1/2)/(b*sqw)^(1/2)

void AutoBuildProfileDlg0::UseWholeDirectory()
{
	if(this->OpenFileDialog())
	{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		SetDlgItemText(hDlg,IDC_DIRECTORY2, this->directory);
		strcpy(this->szPath,this->directory);
        strcat(this->szPath, "/" );
		strcat(this->szPath, this->m_files_in_dir.szFileFilter);
		DlgDirList( hDlg, this->szPath, IDC_LIST2, IDC_DIRECTORY2,
						DDL_READWRITE );

        if (IDOK == MessageBox( hDlg, this->szPath, "Directory Selected",
					MB_OKCANCEL | MB_ICONINFORMATION ))
#endif

		{
			HandlingOfInputFiles();
		}
	}
}
void
UsingOneOfMyMethods3W(int type, // тип прямой задачи
					   bool granicy_kak_glubina, 
					   int & ans_OP,
					   double z0, double z_min,
					   int & cols,
					   MyMethodsData3 & mmd3,					   
					   Wavelet3D & w3,
					   auto_build_parametrs& ab,
					   vector<double> & pX,
					   vector<double> & pY,
					   vector<double> & pZ, // альтитуда измерений - полёта самолёта
					   vector<vector<anten_direction> > & pA,
					   vector<double> & pModul,
					   vector<vector<double> > & pW,
					   vector<string> & names_of_colomns,
					   vector<size_t> & original_col_numbers,
					   bool to_test_algorithm_by_reconstructed_signal,
					   char * common_directory_iX_iY,					   
					   int nFilesInDirectory)
{
    sprintf(dir_out, "%s/common_raz_of_%d_files", common_directory_iX_iY, nFilesInDirectory);
	int n = 0;
	while (!CreateDirectory(dir_out,NULL))
	{
        sprintf(dir_out, "%s/common_raz_of_%d_files(%d)", common_directory_iX_iY, nFilesInDirectory, n++);
	}

		vector<vector <double> > rec_signals;
		vector <double> rec_modul;
							// for debug ///////////////////////////////////////////////
							size_t len_w = 0, size_w = pW.size();
							if (size_w) len_w = pW[0].size();
							// for debug ///////////////////////////////////////////////
		UseOneOfMyMethods3W(type, granicy_kak_glubina,ans_OP, z0,z_min,cols, mmd3, w3, ab, pX, pY, pZ, pA, pModul, pW, names_of_colomns, original_col_numbers,
			rec_signals, rec_modul);

		if (to_test_algorithm_by_reconstructed_signal)
		{
			// а теперь подаём на вход реконструированный сигнал
            sprintf(dir_out, "%s/common_rec_of_%d_files", common_directory_iX_iY, nFilesInDirectory);
			int n = 0;
			while (!CreateDirectory(dir_out,NULL))
			{
                sprintf(dir_out, "%s/common_rec_of_%d_files(%d)", common_directory_iX_iY, nFilesInDirectory, n++);
			}

			vector<vector <double> > rec_signals2;
			vector <double> rec_modul2;

			// for debug ///////////////////////////////////////////////			
			size_t rec_signals_len = 0, rec_signals_size = rec_signals.size();
			if(rec_signals_size) 
				rec_signals_len = rec_signals[0].size();
			// for debug ///////////////////////////////////////////////

			UseOneOfMyMethods3W(-type, granicy_kak_glubina,ans_OP, z0, z_min, cols, mmd3, w3, ab, pX, pY, pZ, pA, rec_modul, rec_signals, names_of_colomns, original_col_numbers,
				rec_signals2, rec_modul2);

			// а теперь подаём на вход реконструированный сигнал
            /*sprintf(dir_out, "%s/common_rec2_of_%d_files", common_directory, this->m_files_in_dir.nFilesInDirectory);
			n = 0;
			while (!CreateDirectory(dir_out,NULL))
			{
                sprintf(dir_out, "%s/common_rec2_of_%d_files(%d)", common_directory, this->m_files_in_dir.nFilesInDirectory, n++);
			}

			vector<vector <double> > rec_signals3;
			vector <double> rec_modul3;
			UseOneOfMyMethods(type, cols,ab,pX,pY,pZ,rec_modul2,rec_signals2,names_of_colomns,original_col_numbers,
				rec_signals3, rec_modul3);*/
		}

}
#define USE_MY_METHOD 1
bool AutoBuildProfileDlg::HandlingOfInputFiles()
{
#if 1
	AutoBuildProfile::ab.tcols = 3;
#else
	int answer = MessageBox(0, "2 - X,Y (Yes) or 3 X,Y,Z(No)", "How Many Geo coordinate colomns&", MB_YESNOCANCEL);
	switch (answer)
	{
	case IDYES:
		{
			AutoBuildProfile::ab.tcols = 2;
		}
		break;	
	case IDNO:
		{
			AutoBuildProfile::ab.tcols = 3;
		}
		break;
	default :
		return false;
	}
#endif

#if !USE_MY_METHOD
	bool is_reverse = false;
	int shoulder = 50;// плечо -  длина окна - это два плеча плюс один
	int step = 5;
	int wlen_base = 20;
	int wlen_auto = 10;

	cout << "Enter is_reverse[0/1]:" << endl;
	cin  >> is_reverse;

	cout << "Enter shoulder[50]:" << endl;
	cin  >> shoulder;

	cout << "Enter step[5]:" << endl;
	cin  >> step;

	cout << "Enter wlen_base[20]:" << endl;
	cin  >> wlen_base;

	cout << "Enter wlen_auto[10]:" << endl;
	cin  >> wlen_auto;
#else			
#endif

	//int delim = ',';
	int num_col = -1;
	//##############################################################
	//блок чтения файла с нумерами колонок
	vector<bool> use_col;
	if (!ReadColomnNumbers(AutoBuildProfile::ab,use_col,num_col,AutoBuildProfile::ab.delim))
	{
		return false;
	}

    char common_directory[4096];
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
    SYSTEMTIME time;
    GetLocalTime(&time);
    sprintf(common_directory, "%s/%d-%02d-%02d_%02d_%02d_%02d", this->directory, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute,time.wSecond);
#else
    QDateTime time = QDateTime::currentDateTime();
    sprintf(common_directory, "%s/%d-%02d-%02d_%02d_%02d_%02d", this->directory, time.date().year(), time.date().month(), time.date().day(), time.time().hour(), time.time().minute(),time.time().second());
#endif
    printf("common_directory = %s\n\n",common_directory);

	if (!CreateDirectory(common_directory,NULL))
	{
		char err_str[4096];
		sprintf(err_str, "Directory \"%s\" creation failed !!!", common_directory);
		MessageBox(0, err_str, "HandlingOfInputFiles", 0);
		return false;
	}
	char common_directory_iX_iY[4096];

	//**********************************************
	//формируем файл описания режима работы
	char filename_description[4096];
    sprintf(filename_description, "%s/description1.txt", common_directory);
	FILE *stream;
	stream = fopen(filename_description,"wt");
	if (stream)
	{
		WriteDescription(stream, AutoBuildProfile::ab);
		fclose(stream);
	}
	//**********************************************

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	this->m_files_in_dir.nFilesInDirectory = SendDlgItemMessage( hDlg, IDC_LIST2, LB_GETCOUNT, 0, 0);
	//память не освобождена!!!!
	this->m_files_in_dir.vFileNameLengthes = (int *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( int ) *  this->m_files_in_dir.nFilesInDirectory);
	this->m_files_in_dir.vFileNames = (char **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( char * ) *  this->m_files_in_dir.nFilesInDirectory);
#else
#endif
	int cols;
	vector<string> names_of_colomns;
	vector<size_t> original_col_numbers;
	vector<vector<vector<vert_korr_points> > > vvvvkp;
	vvvvkp.clear();

	vector<profile_interval> profile_intervals;
	profile_intervals.clear();

#if USE_MY_METHOD
	vector<vector<anten_direction> > A;
	vector<vector<double> > W;
	vector<vector<vector<double> > > vW;
	vector<double> vX,vY,vZ, vModul;
#endif

	stream = fopen(filename_description,"at");
	if (stream)
	{
		fprintf(stream, "Loading files\n\n");
		fclose(stream);
	}

	//Программная реализация трёх-антенной прямой задачи требует договора о том, 
	//как производить соответствие между антеннами на самолёте и логическими 
	//антеннами AX(1,0,0), AY(0,1,0) и AZ(0,0,1).
	
	//Допустим, что прибор под именем X записывает в базу данных ту антенну, 
	//нормаль которой направлена вдоль направления полёта самолёта. Тогда условие 
	//необходимости замены обозначений антенн не возникает, если самолёт летит 
	//вдоль широты, но такая необходимость замены обозначений антенн возникает, 
	//если самолёт летит вдоль долготы. 
	
	//Если вдоль направления полёта самолёта закреплена нормаль антенны Y, 
	//тогда наоборот условие необходимости замены обозначений антенн не возникает, 
	//если самолёт летит вдоль долготы, но возникает, если самолёт летит вдоль широты. 

	int when_to_swap = 0;


	char parallel_to_profile_antenn_normal = 'x';
	///////////////////////////////////
	cout << "Enter normal of which antenn X or Y is parallel to profile (or to fly of airplane)" << endl;
	cin >> parallel_to_profile_antenn_normal;

	switch (parallel_to_profile_antenn_normal)
	{
	case 'X':
	case 'x':
		{
			when_to_swap = 0;
		}
		break;
	case 'Y':
	case 'y':
		{
			when_to_swap = 1;
		}
		break;
	default:
		{
			MessageBox(0, "Вы не определили нормаль какой антены парралельна профилю", "Ошибка ввода", 0);
			return false;
		}
	}

	int use_time_col = AutoBuildProfile::ab.use_time_colomn;

	vector <string> fnames;

	for (int iFile = 0; iFile < this->m_files_in_dir.nFilesInDirectory; iFile++)
	{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		this->m_files_in_dir.vFileNameLengthes[iFile] = SendDlgItemMessage( hDlg, 
			IDC_LIST2, LB_GETTEXTLEN, (WPARAM) iFile, 0)+1;
		this->m_files_in_dir.vFileNames[iFile] = (char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( char ) * this->m_files_in_dir.vFileNameLengthes[iFile]);

		if (LB_ERR!=SendDlgItemMessage( hDlg, 
			IDC_LIST2, LB_GETTEXT, (WPARAM) iFile, (LPARAM)(this->m_files_in_dir.vFileNames[iFile])))
#else
#endif
		{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
			char sz_path_of_file[4096];			
            sprintf(sz_path_of_file, "%s/%s", this->directory, this->m_files_in_dir.vFileNames[iFile]);
#else
			const char* sz_path_of_file = this->m_files_in_dir.vFileNames[iFile];
#endif
			printf("this->directory = %s\n this->m_files_in_dir.vFileNames[iFile] = %s\n sz_path_of_file = %s\n\n",this->directory,  this->m_files_in_dir.vFileNames[iFile], sz_path_of_file);

			int rows;

			char filename[256];
			vector<vector<double> > v;
			vector<vector<double> > w;

#if SOURCE_COORDINATES_3D
			vector<double> X;
			vector<double> Y;
			vector<double> Z;
#else
			vector<double> t;
#endif

			if (!ReadProfileFile( 
					sz_path_of_file, directory, filename, 
					consol, 
					p_auto_build_profile,
					AutoBuildProfile::ab,
					rows, cols,
					use_col,
					original_col_numbers,
					&names_of_colomns,
					v,
					w,
#if SOURCE_COORDINATES_3D
					X,
					Y,
					Z,
#else
					t,
#endif
					num_col,
					AutoBuildProfile::ab.delim))
			{
				return false;
			}
#if USE_MY_METHOD

			stream = fopen(filename_description,"at");
			if (stream)
			{
				fprintf(stream, "%s\n", this->m_files_in_dir.vFileNames[iFile]);
			}

			fnames.push_back(this->m_files_in_dir.vFileNames[iFile]);

			vector<double> vvv(rows, 0.0);
			
			for (size_t r = 0; r < rows; r++)
			{	
				for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
				{
					vvv[r] += v[c][r]*v[c][r];
				}
				vvv[r] = sqrt(vvv[r]);
			}

			double min__x, min__y, min__z;
			double max__x, max__y, max__z;
			double delta__x;
			double delta__y;

			GetProfileDirection(X, Y, Z,
				min__x, min__y, min__z,
				max__x, max__y, max__z,
				delta__x, delta__y);

			if (stream)
			{
				fprintf(stream, "delta__x = %f  delta__y = %f\n", delta__x, delta__y);
			}


			if (iFile == 0)
			{
				W.resize(cols);
				A.resize(3);
			}

			// отдельно будем складывать профиля
			// чтобы потом отцентрировать каждый
			vW.push_back(vector<vector<double> > () );
			vW.back().resize(cols);

			// если delta__x оказывается меньше delta__y, 
			// то есть если профиль является субмеридиональным, 
			// тогда производится автоматическая замена сигнала антенн.

			bool to_swap;
			if (when_to_swap == 0)
			{
				//Допустим, что прибор под именем X записывает в базу данных ту антенну, 
				//нормаль которой направлена вдоль направления полёта самолёта. Тогда условие 
				//необходимости замены обозначений антенн не возникает, если самолёт летит 
				//вдоль широты (delta__x > delta__y), но такая необходимость замены обозначений антенн возникает, 
				//если самолёт летит вдоль долготы (delta__x < delta__y). 
				to_swap = delta__x < delta__y;	
			}
			else 
			{
				//Если вдоль направления полёта самолёта закреплена нормаль антенны Y, 
				//тогда наоборот условие необходимости замены обозначений антенн не возникает, 
				//если самолёт летит вдоль долготы, но возникает, если самолёт летит вдоль широты. 
				to_swap = delta__x > delta__y;
			}

			if (to_swap)
			{
				if (cols >=2)
				{
					printf("swapping of parameters %s and %s on profile %s\n", 
						names_of_colomns[original_col_numbers[0]].c_str(), 
						names_of_colomns[original_col_numbers[1]].c_str(), 
						this->m_files_in_dir.vFileNames[iFile]);

					if (stream)
					{
						fprintf(stream, "меняем антены X и Y\n");
						fprintf(stream, "swapping of parameters %s and %s on profile %s\n", 
							names_of_colomns[original_col_numbers[0]].c_str(), 
							names_of_colomns[original_col_numbers[1]].c_str(), 
							this->m_files_in_dir.vFileNames[iFile]);
					}
				}

				if (cols >=5)
				{
					printf("swapping of parameters %s and %s on profile %s\n", 
						names_of_colomns[original_col_numbers[3]].c_str(), 
						names_of_colomns[original_col_numbers[4]].c_str(), 
						this->m_files_in_dir.vFileNames[iFile]);

					if (stream)
					{
						fprintf(stream, "меняем антены X2 и Y2\n");
						fprintf(stream, "swapping of parameters %s and %s on profile %s\n", 
							names_of_colomns[original_col_numbers[3]].c_str(), 
							names_of_colomns[original_col_numbers[4]].c_str(), 
							this->m_files_in_dir.vFileNames[iFile]);
					}
				}

				if (cols >=8)
				{
					printf("swapping of parameters %s and %s on profile %s\n", 
						names_of_colomns[original_col_numbers[6]].c_str(), 
						names_of_colomns[original_col_numbers[7]].c_str(), 
						this->m_files_in_dir.vFileNames[iFile]);

					if (stream)
					{
						fprintf(stream, "меняем антены X3 и Y3\n");
						fprintf(stream, "swapping of parameters %s and %s on profile %s\n", 
							names_of_colomns[original_col_numbers[6]].c_str(), 
							names_of_colomns[original_col_numbers[7]].c_str(), 
							this->m_files_in_dir.vFileNames[iFile]);
					}
				}

				
				//считаем по y
				//grid->gridSection.xLL = min__y;
				//grid->gridSection.xSize = delta_y;

				for (size_t r = 0; r < rows; r++)
				{
					anten_direction adX, adY, adZ, adV;
					if (r == 0)
					{
						adX.Init(X[r+1] - X[r], Y[r+1] - Y[r], Z[r+1] - Z[r]);
					}
					else if (r == rows - 1)
					{
						adX.Init(X[r] - X[r-1], Y[r] - Y[r-1], Z[r] - Z[r-1]);
					}
					else
					{
						adX.Init(X[r+1] - X[r-1], Y[r+1] - Y[r-1], Z[r+1] - Z[r-1]);
					}
					adX.Norm();

					adV.Init(0.0, 0.0, 1.0);

					adY.InitAsVectorProduct(adX, adV);
					adY.Norm();

					adZ.InitAsVectorProduct(adX, adY);
					adZ.Norm();
					
					if (when_to_swap == 0)
					{
						A[0].push_back(adY);
						A[1].push_back(adX);
						A[2].push_back(adZ);
					}
					else
					{
						A[0].push_back(adX);
						A[1].push_back(adY);
						A[2].push_back(adZ);
					}

					vX.push_back(X[r]);
					vY.push_back(Y[r]);
					vZ.push_back(Z[r]);
					vModul.push_back(vvv[r]);
					
					for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
					{
						size_t C = c;

						// меняем антены X и Y
						if (c == 0) C = 1;
						else if (c == 1) C = 0;

						// меняем антены X2 и Y2
						else if (c == 3) C = 4;
						else if (c == 4) C = 3;

						// меняем антены X3 и Y3
						else if (c == 6) C = 7;
						else if (c == 7) C = 6;

						W[c].push_back(v[C][r]);
						vW.back().operator [](c).push_back(v[C][r]);
					}	
				}
			}
			else
			{
				//считаем по x
				//grid->gridSection.xLL = min__x;
				//grid->gridSection.xSize = delta_x;

				for (size_t r = 0; r < rows; r++)
				{
					anten_direction adX, adY, adZ, adV;
					if (r == 0)
					{
						adX.Init(X[r+1] - X[r], Y[r+1] - Y[r], Z[r+1] - Z[r]);
					}
					else if (r == rows - 1)
					{
						adX.Init(X[r] - X[r-1], Y[r] - Y[r-1], Z[r] - Z[r-1]);
					}
					else
					{
						adX.Init(X[r+1] - X[r-1], Y[r+1] - Y[r-1], Z[r+1] - Z[r-1]);
					}
					adX.Norm();

					adV.Init(0.0, 0.0, 1.0);

					adY.InitAsVectorProduct(adX, adV);
					adY.Norm();

					adZ.InitAsVectorProduct(adX, adY);
					adZ.Norm();
					
					if (when_to_swap == 0)
					{
						A[0].push_back(adX);
						A[1].push_back(adY);
						A[2].push_back(adZ);
					}
					else
					{
						A[0].push_back(adY);
						A[1].push_back(adX);
						A[2].push_back(adZ);
					}

					vX.push_back(X[r]);
					vY.push_back(Y[r]);
					vZ.push_back(Z[r]);
					vModul.push_back(vvv[r]);

					for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
					{
						W[c].push_back(v[c][r]);
						vW.back().operator [](c).push_back(v[c][r]);
					}	
				}
			}
#else
			if (!BuildingProfile(vvvvkp,
				profile_intervals,
				consol, 
				p_auto_build_profile,
				AutoBuildProfile::ab,
				v, w, X, Y,
				&names_of_colomns, original_col_numbers, 
				rows, cols, 
				AutoBuildProfile::ab.delim, common_directory, filename,
				is_reverse, shoulder, step, wlen_auto))
			{
				return false;
			}

#endif
			
			if (stream)
			{
				fprintf(stream, "\n");
				fclose(stream);
			}
		}
        //else
        //{
        //}
    }

	// центруем сигналы по каждому профилю отдельно
	// а затем прибавляем общую среднюю

	int n_profiles = vW.size();
	vector <double> mean(cols), disp(cols);
	vector <vector <double> > profile_mean(n_profiles);
	vector <vector <double> > profile_disp(n_profiles);

	for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
	{
		mean[c] = Mean(W[c]); 
		disp[c] = Disp(W[c]); 
	}	

	for (int n_prof = 0; n_prof < n_profiles; n_prof++)
	{
		profile_mean[n_prof].resize(cols);
		profile_disp[n_prof].resize(cols);
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			profile_mean[n_prof][c] = Mean(vW[n_prof][c]); 
			profile_disp[n_prof][c] = Disp(vW[n_prof][c]); 
		}
	}

	char means_name[1024];
    sprintf(means_name, "%s/means.txt", common_directory);
	//char * p; while (p=strchr (means_name,'\"')){*p = '_';}
	FILE * means = fopen (means_name, "wt");
	if(means)
	{
		fprintf(means, "where");
		printf("where");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(means, ",mean(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
			printf(",mean(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
		}	
		fprintf(means, "\n");
		printf("\n");

		fprintf(means, "all_object");
		printf("all_object");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(means, ",%f", mean[c]);
			printf(",%f", mean[c]);
		}	
		fprintf(means, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(means, "%s", fnames[n_prof].c_str());
			printf("%s", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(means, ",%f", profile_mean[n_prof][c]);
				printf(",%f", profile_mean[n_prof][c]);
			}
			fprintf(means, "\n");
			printf("\n");
		}
		fprintf(means, "\n");
		printf("\n");
	}


	if(means)
	{
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(means, "mean(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				mean[c]);
			printf("mean(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				mean[c]);
		}	
		fprintf(means, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(means, "%s\n", fnames[n_prof].c_str());
			printf("%s\n", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(means, "mean(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_mean[n_prof][c]);
				printf("mean(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_mean[n_prof][c]);
			}
		}
		fprintf(means, "\n");
		printf("\n");

		fclose(means);

	}


	char disps_name[1024];
    sprintf(disps_name, "%s/disps.txt", common_directory);
	//char * p; while (p=strchr (disps_name,'\"')){*p = '_';}
	FILE * disps = fopen (disps_name, "wt");
	if(disps)
	{
		fprintf(disps, "where");
		printf("where");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(disps, ",disp(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
			printf(",disp(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
		}	
		fprintf(disps, "\n");
		printf("\n");

		fprintf(disps, "all_object");
		printf("all_object");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(disps, ",%f", disp[c]);
			printf(",%f", disp[c]);
		}	
		fprintf(disps, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(disps, "%s", fnames[n_prof].c_str());
			printf("%s", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(disps, ",%f", profile_disp[n_prof][c]);
				printf(",%f", profile_disp[n_prof][c]);
			}
			fprintf(disps, "\n");
			printf("\n");
		}
		fprintf(disps, "\n");
		printf("\n");
	}


	if(disps)
	{
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(disps, "disp(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				disp[c]);
			printf("disp(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				disp[c]);
		}	
		fprintf(disps, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(disps, "%s\n", fnames[n_prof].c_str());
			printf("%s\n", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(disps, "disp(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_disp[n_prof][c]);
				printf("disp(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_disp[n_prof][c]);
			}
		}
		fprintf(disps, "\n");
		printf("\n");

		fclose(disps);

	}


	bool to_set_mean_of_profiles_to_zero = false;
	cout << "Enter to_set_mean_of_profiles_to_zero 0 1 ?" << endl;
	cin >> to_set_mean_of_profiles_to_zero;


	if (to_set_mean_of_profiles_to_zero)
	{
		bool to_set_mean_value_to_profile = false;
		cout << "Enter to_set_mean_value_to_profile 0 1 ?" << endl;
		cin >> to_set_mean_value_to_profile;
		if (to_set_mean_value_to_profile)
		{
			for (int n_prof = 0; n_prof < n_profiles; n_prof++)
			{
				for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
				{
					for (int i = 0; i < vW[n_prof][c].size(); i++)
					{
						vW[n_prof][c][i] = mean[c];
					}
				}
			}
		}
		else
		{
			for (int n_prof = 0; n_prof < n_profiles; n_prof++)
			{
				for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
				{
					for (int i = 0; i < vW[n_prof][c].size(); i++)
					{
						vW[n_prof][c][i] -= profile_mean[n_prof][c];
					}
				}
			}
		}
	}
	else
	{
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				for (int i = 0; i < vW[n_prof][c].size(); i++)
				{
					vW[n_prof][c][i] += mean[c] - profile_mean[n_prof][c];
				}
			}
		}	
	}



	bool to_recenter_profiles = false;
	cout << "Enter to_recenter_profiles 0 1 ?" << endl;
	cin >> to_recenter_profiles;

	if (to_recenter_profiles || to_set_mean_of_profiles_to_zero)
	{
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			int r = 0;
			for (int n_prof = 0; n_prof < n_profiles; n_prof++)
			{
				for (int i = 0; i < vW[n_prof][c].size(); i++)
				{
					W[c][r] = vW[n_prof][c][i];
					r++;
				}
			}
		}
	}

	
	// здесь исключить близкие точки
	// если матрица оператора прямой задачи 
	// содержит практически одинаковые строки, 
	// то это означает плохую обусловленность матрицы. 
	// Для улучшения обусловленности матрицы необходмо 
	// исключить из рассмотрения такие пары измерений, 
	// расстояние между которыми меньше, скажем половины шага измерения
	vector<double> vLen;
	for (int i = 0; i < vX.size()-1; i++)
	{
		double len = sqrt (pow(vX[i+1]-vX[i],2.0) + pow(vY[i+1]-vY[i],2.0));
		vLen.push_back(len);
	}
	std::sort(vLen.begin(), vLen.end());
	double step = vLen[vLen.size()/2];
	double limit = vLen[0];

	printf ("step = %f\n", step);
	printf ("vLen[0] = %f\n", vLen[0]);
	printf ("vLen[end] = %f\n", vLen[vLen.size()-1]);

	map<int,double> to_exclude;

	for (int i1 = 0; i1 < vX.size()-1; i1++)
	{
		for (int i2 = i1+1; i2 < vX.size()-1; i2++)
		{
			double len = sqrt (pow(vX[i1]-vX[i2],2.0) + pow(vY[i1]-vY[i2],2.0));
			if (len < limit) 
			{
				to_exclude.insert(map<int,double>::value_type(i1,len));
				to_exclude.insert(map<int,double>::value_type(i2,len));
			}
		}
	}

	/*for (map<int, int>::iterator it = to_exclude.begin();
		it != to_exclude.end(); it++)
	{
		printf ("to_exclude = %d\n", (*it).first);
	}
*/

	printf ("vX.size() = %d\n", vX.size());
	printf ("to_exclude.size() = %d\n", to_exclude.size());

	for (map<int, double>::reverse_iterator r_it = to_exclude.rbegin();
		r_it != to_exclude.rend(); r_it++)
	{
		printf ("to_exclude = %d\t%f\n", (*r_it).first, (*r_it).second);
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			vector<double>::iterator it_w_c = W[c].begin() + (*r_it).first;
			W[c].erase(it_w_c);
		}	

		vector<double>::iterator it_vx = vX.begin() + (*r_it).first;
		vX.erase(it_vx);

		vector<double>::iterator it_vy = vY.begin() + (*r_it).first;
		vY.erase(it_vy);

		vector<double>::iterator it_vz = vZ.begin() + (*r_it).first;
		vZ.erase(it_vz);
	}
	printf ("vX.size() = %d\n", vX.size());

	MyMethodsData3 mmd3;
	mmd3.to_povorot = false;
	mmd3.need_crd_projection = false;

	if (n_profiles == 1)
	{
		cout << "Enter Do you need coordinate preobrazovanie" << endl;
		cin >> mmd3.to_povorot;

		if (mmd3.to_povorot)
		{	
			cout << "Enter Do you need coordinate projection output?" << endl << 
				"(1 - yes, 0 - output will be in profile length)" << endl;
			cin >> mmd3.need_crd_projection;
			


			//ищем уравнение прямой в виде
			// ax+by+c=0

			// определяем профиль является субширотным или субмериодиональным
			double profile_dx = fabs(vX[0] - vX.back());
			double profile_dy = fabs(vY[0] - vY.back());

			if (profile_dx > profile_dy)
			{
				//субширотный
				//ищем уравнение прямой в виде
				//y=Ax+B, где A=-a/b B=-c/b b!=0

				double xy = ScalarProduct(vX, vY);
				double xx = SquareSum(vX);
				double sx = Sum(vX);
				double sy = Sum(vY);
				double n = vX.size();

				double D = n*xx-sx*sx;
				double DA = n*xy-sy*sx;
				double DB = xx*sy-sx*xy;

				double A = DA/D;
				double B = DB/D;

				double b = 1.0, a = -A, c = -B;

				printf ("A = %f B = %f\n", A,B);
				printf ("a = %f b = %f c = %f\n", a,b,c);

				mmd3.ugol = atan(A);
				printf("ugol = %f %f\n", mmd3.ugol, mmd3.ugol/PI*180);
			}
			else
			{
				//субмериодиональный
				//ищем уравнение прямой в виде
				//x=Ay+B, где A=-b/a B=-c/a a!=0

				double xy = ScalarProduct(vX, vY);
				double yy = SquareSum(vY);
				double sx = Sum(vX);
				double sy = Sum(vY);
				double n = vX.size();

				double D = n*yy-sy*sy;
				double DA = n*xy-sy*sx;
				double DB = yy*sx-sy*xy;

				double A = DA/D;
				double B = DB/D;

				double a = 1.0, b = -A, c = -B;
				printf ("A = %f B = %f\n", A,B);
				printf ("a = %f b = %f c = %f\n", a,b,c);

				mmd3.ugol = -atan(A);
				printf("ugol = %f %f\n", mmd3.ugol, mmd3.ugol/PI*180);
			}

			mmd3.ugol*=-1.0;


			if (profile_dx > profile_dy)
			{
				printf("subshirotny\n");
				//субширотный
				//уравнение прямой в виде
				//y=Ax+B, где A=-a/b B=-c/b b!=0

				//ищем начальную точку в как ту у которой минимальный икс
				vector<double>::iterator it_min_vx = min_element(vX.begin(), vX.end());
				if (it_min_vx != vX.end())
				{
					mmd3.vX0 = *it_min_vx;
					unsigned long shift = &(*it_min_vx) - &(*vX.begin());
					cout << "shift " << shift << endl;
					mmd3.vY0 = *((double *)(&(*vY.begin()) + shift));
					printf ("vY0 = %f", mmd3.vY0);
				}
			}
			else
			{
				//субмериодиональный
				//уравнение прямой в виде
				//x=Ay+B, где A=-b/a B=-c/a a!=0

				//ищем начальную точку в как ту у которой минимальный игрек
				vector<double>::iterator it_min_vy = min_element(vY.begin(), vY.end());
				if (it_min_vy != vY.end())
				{
					mmd3.vY0 = *it_min_vy;
					unsigned long shift = &(*it_min_vy) - &(*vY.begin());
					cout << "shift = " << shift << endl;
					mmd3.vX0 = *((double *)(&(*vX.begin()) + shift));
					printf ("vX0 = %f", mmd3.vX0);
				}
			}

			char bln_name[1024];

            sprintf(bln_name, "%s/new_XY.bln", common_directory);
			//char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
			FILE * bln = fopen (bln_name, "wt");
			if(bln)
			{
				fprintf(bln, "%d,%d, new_XY\n", vX.size(), 0);
			}

			for (int i = 0; i < vX.size(); i++)
			{
				double x_new = (vX[i] - mmd3.vX0)*cos(mmd3.ugol) - (vY[i] - mmd3.vY0)*sin(mmd3.ugol);
				double y_new = (vX[i] - mmd3.vX0)*sin(mmd3.ugol) + (vY[i] - mmd3.vY0)*cos(mmd3.ugol);

				vX[i] = x_new;
				vY[i] = y_new;

				if (true)
				{
					if (profile_dx > profile_dy)
					{
						vY[i] = 0.0;
					}
					else
					{
						vX[i] = 0.0;
					}
				}
				
				if(bln)
				{				
					fprintf(bln, "%f,%f\n", vX[i], vY[i]);
				}
			}
			if(bln)
			{
				fclose(bln);
			}
		}
	}
#if USE_MY_METHOD
	
	sprintf(dir_out, "%s\0", common_directory);
				
	int type = 0; // тип прямой задачи
	cout << "Enter type of prjamoj zadachi" << endl;
	cout << "0 - simple" << endl;
	cout << "1 - with diagramm of 3 antenns and nonpolarized sources" << endl;
	cout << "2 - --//-- and with assumption that tg delta much more than one" << endl;
	cin >> type;

	int ans_OP = 0;//MessageBox(0, "Calculy(Yes) or Load(No) Forward Operator", "Select operator!!!", MB_YESNO);
	cout << "Select operator!!!" << endl;
	cout << "Enter:" << endl;
	cout << "Calculy(1) or Load(0) Forward Operator" << endl;
	int ans_op = 0;
	cin >> ans_op;
	if (ans_op) ans_OP = IDYES;
	else ans_OP = IDNO;

	double z0 = 0.0, z_min = 0.0, DZ = 0.0;

	if (ans_OP == IDYES)
	{
		cout << "Enter Altitude z0, (m)" << endl;
		cin >> z0;
		cout << "z0 = " << z0 << " m" << endl;

		cout << "Enter Altitude z_min, (m)" << endl;
		cin >> z_min;
		cout << "z_min = " << z_min << " m" << endl;

		DZ = z0 - z_min;
		cout << "DZ = " << DZ << " m" << endl;
	}


	///////////////////////////////////
	int to_get_part_of_data;
	cout << "Enter Do you want GetPartOfData?  0 - no 1 - geometrical 2 - frec 3 - many pieces 4 - by one colomn" << endl;
	cin >> to_get_part_of_data;

	Wavelet3D w3;
	UseOneOfMyMethods3W_preparing(type, ans_OP, z0, z_min, DZ, cols, mmd3, w3, AutoBuildProfile::ab);


	if (to_get_part_of_data)
	{
		bool to_test_algorithm_by_reconstructed_signal;
		cout << "Enter Do you want to_test_algorithm_by_reconstructed_signal? 1 - yes 0 - no" << endl;
		cin >> to_test_algorithm_by_reconstructed_signal;
		
		//тестируем на уменьшенной площади
		vector<double> pX, pY, pZ, pModul;
		vector<vector<anten_direction> > pA;
		vector<vector<double> > pW;

		switch(to_get_part_of_data)
		{
		case 1:
			{
				double p_min =  0.45;
				double p_max =  0.55;

				cout << "Enter p_min? [0.45]" << endl;
				cin >> p_min;

				cout << "Enter p_max? [0.55]" << endl;
				cin >> p_max;

                sprintf(common_directory_iX_iY, "%s/part_of_object_%f_%f", common_directory, p_min, p_max);
				if (!CreateDirectory(common_directory_iX_iY, NULL))
				{
				}

				GetPartOfData(p_min, p_max,
					vX,vY,vZ, A, vModul, W,
					pX,pY,pZ,pA, pModul,pW);

				UsingOneOfMyMethods3W(type, // тип прямой задачи
					   mmd3.granicy_kak_glubina, 
					   ans_OP, 
					   z0, z_min,
					   cols, 
					   mmd3,w3,AutoBuildProfile::ab,
					   pX, pY, pZ, pA, pModul, pW,
					   names_of_colomns,
					   original_col_numbers,
					   to_test_algorithm_by_reconstructed_signal,
					   common_directory_iX_iY,					   
					   this->m_files_in_dir.nFilesInDirectory);

			}
			break;
		case 2:
			{
				int frec = 1;

				cout << "To get each frec? [1 2 .. 10 ... ]" << endl;
				cin >> frec;


                sprintf(common_directory_iX_iY, "%s/whole_object_with_frec=%d", common_directory, frec);
				if (!CreateDirectory(common_directory_iX_iY, NULL))
				{
				}

				GetPartOfData(frec,
					vX,vY,vZ, A, vModul, W,
					pX,pY,pZ,pA, pModul,pW);

				UsingOneOfMyMethods3W(type, // тип прямой задачи
					   mmd3.granicy_kak_glubina, 
					   ans_OP, z0, z_min,
					   cols, 
					   mmd3, w3, AutoBuildProfile::ab,
					   pX, pY, pZ, pA, pModul, pW,
					   names_of_colomns,
					   original_col_numbers,
					   to_test_algorithm_by_reconstructed_signal,
					   common_directory_iX_iY,					   
					   this->m_files_in_dir.nFilesInDirectory);
			}
			break;
		case 3:
			{				   
				double min_X, max_X, min_Y, max_Y;				
				GetMinMaxXYOfData(vX, vY, min_X, max_X, min_Y, max_Y);

				double 
					DX = max_X - min_X, 
					DY = max_Y - min_Y; 

				double xy_z_m = 2;

				double dx = DZ * xy_z_m;
				double dy = DZ * xy_z_m;

				int nX = (DX - 2 * int(mmd3.granicy_kak_glubina)*DZ) / dx;
				int nY = (DY - 2 * int(mmd3.granicy_kak_glubina)*DZ) / dy;

				cout << "nX = " << nX << endl;
				cout << "nY = " << nY << endl;

				for (int iX = 0; iX < nX; iX++)
				{
					for (int iY = 0; iY < nY; iY++)
					{
						double min_x = min_X + (iX) * dx;
						double max_x = min_X + (iX + 1) * dx + 2*DZ*int(mmd3.granicy_kak_glubina);

						double min_y = min_Y + (iY) * dy;
						double max_y = min_Y + (iY + 1) * dy + 2*DZ*int(mmd3.granicy_kak_glubina);

						// массив индексов урезанных массивов pX, pY, pZ, pModul,pW
						// в индексации первоначальных массивов vX, vY, vZ, vModul, W
						vector <long> pInd;

						GetPartOfData(min_x, max_x, min_y, max_y,
							 vX, vY, vZ,  A, vModul,  W,
							 pX, pY, pZ, pA, pModul, pW,
							 pInd);

						size_t len_pX = pX.size();

	
						char common_directory_iX_iY[4096];			
                        sprintf(common_directory_iX_iY, "%s/iX=%03d_iY=%03d",
							common_directory, iX, iY);			
						printf("common_directory_iX_iY = %s\n\n",common_directory_iX_iY);
						printf("len_pX = %d\n\n",len_pX);
						if (len_pX >= 128)
						{
							double min__x, min__y, min__z;
							double max__x, max__y, max__z;
							double delta__x;
							double delta__y;
							
							GetProfileDirection(pX, pY, pZ,
								min__x, min__y, min__z,
								max__x, max__y, max__z,
								delta__x, delta__y);

							if (delta__x > 0.5 * (dx+2*DZ*int(mmd3.granicy_kak_glubina)) 
								&& delta__y > 0.5 * (dy+2*DZ*int(mmd3.granicy_kak_glubina)))
							{			
								
								if (!CreateDirectory(common_directory_iX_iY,NULL))
								{
								}

								UsingOneOfMyMethods3W(type, // тип прямой задачи
									mmd3.granicy_kak_glubina, 
									ans_OP, z0, z_min,
									cols, mmd3, w3, AutoBuildProfile::ab,
									pX, pY, pZ, pA, pModul, pW,
									names_of_colomns,
									original_col_numbers,
									to_test_algorithm_by_reconstructed_signal,
									common_directory_iX_iY,					   
									this->m_files_in_dir.nFilesInDirectory);
							}
						}
					}
				}
			}
			break;
		case 4:
			{				   
                //sprintf(common_directory_iX_iY, "%s/whole_object_by_colomns", common_directory);
				//if (!CreateDirectory(common_directory_iX_iY, NULL))
				//{
				//}

				double min_X, max_X, min_Y, max_Y;				
				GetMinMaxXYOfData(vX, vY, min_X, max_X, min_Y, max_Y);

				double 
					DX = max_X - min_X, 
					DY = max_Y - min_Y; 



				double dx = DZ * mmd3.dx_and_dy_per_DZ;
				double dy = DZ * mmd3.dx_and_dy_per_DZ;


				mmd3.delta__x = DX - dx * int (mmd3.granicy_kak_glubina);
				mmd3.delta__y = DY - dy * int (mmd3.granicy_kak_glubina);
				mmd3.delta__z = mmd3.z0 - mmd3.z_min;


				// на случай редукции к двумерному случаю
				bool to_reduce_x = (DX - dx) < 0.0;
				bool to_reduce_y = (DY - dy) < 0.0;

				if (to_reduce_x) {mmd3.cols = 1; mmd3.delta__x = 0.0;}
				if (to_reduce_y) {mmd3.rows = 1; mmd3.delta__y = 0.0;}

				mmd3.x0 = to_reduce_x ? (min_X+max_X)/2.0 : min_X + 0.5 * dx * int (mmd3.granicy_kak_glubina);
				mmd3.y0 = to_reduce_y ? (min_Y+max_Y)/2.0 : min_Y + 0.5 * dy * int (mmd3.granicy_kak_glubina);

				mmd3.delta_x = to_reduce_x ? 0.0 : mmd3.delta__x / (mmd3.cols - 1);
				mmd3.delta_y = to_reduce_y ? 0.0 : mmd3.delta__y / (mmd3.rows - 1);

				vector<string> new_names_of_colomns;
				int cols_3 = cols / 3;//2
				new_names_of_colomns.resize(cols_3);

				if (false)
				{
					long min_len_pX = LONG_MAX;
					long max_len_pX = LONG_MIN;
					for (int c = 0; c < mmd3.cols; c++)
					{
						for (int r = 0; r < mmd3.rows; r++)
						{
							double center_x = mmd3.x0 + c * mmd3.delta_x;
							double center_y = mmd3.y0 + r * mmd3.delta_y;

							double min_x = center_x - 0.5 * dx;
							double max_x = center_x + 0.5 * dx;

							double min_y = center_y - 0.5 * dy;
							double max_y = center_y + 0.5 * dy;

							// массив индексов урезанных массивов pX, pY, pZ, pModul,pW
							// в индексации первоначальных массивов vX, vY, vZ, vModul, W
							vector<long> __pInd;

							GetPartOfData(min_x, max_x, min_y, max_y,
								vX, vY, vZ,  A, vModul,  W,
								pX, pY, pZ, pA, pModul, pW,
								__pInd);

							long len_pX = pX.size();

							if (min_len_pX > len_pX) min_len_pX = len_pX;
							if (max_len_pX < len_pX) max_len_pX = len_pX;
		
							//char common_directory_iX_iY[4096];			
                            //sprintf(dir_out, "%s/c=%03d_r=%03d", common_directory, c, r);
							//printf("common_directory_iX_iY = %s\n\n",common_directory_iX_iY);
							printf("len_pX = %d mmd3.pages = %d\n\n",len_pX, mmd3.pages);
						}
					}

					mmd3.pages = type > 0 ? max_len_pX * 3 : max_len_pX;
					//mmd3.pages = type > 0 ? min_len_pX * 3 : min_len_pX;
				}

				//mmd3.delta_z = mmd3.delta__z / (mmd3.pages - 1);// это неверно!!!
				// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
				mmd3.delta_z = mmd3.delta__z / mmd3.pages;
	

				typedef  Grid4 * GRID_POINTER;
				typedef  GRID_POINTER * GRID_2_POINTER;

				// корреляционные кубы

				Grid4 *** _cubes = new GRID_2_POINTER[cols_3];
				for (int cc = 0; cc < cols_3; cc++)
				{
					_cubes[cc] = new GRID_POINTER[2];
					for (int i_alpha = 0; i_alpha < 2; i_alpha++)
					{
						// Грид по размеру геологической структуры
						_cubes[cc][i_alpha] = CreateProfileGrid3D(mmd3);
						Zero3DMat<double>(_cubes[cc][i_alpha]->grid4Section.v, _cubes[cc][i_alpha]->grid4Section.nPag, _cubes[cc][i_alpha]->grid4Section.nRow, _cubes[cc][i_alpha]->grid4Section.nCol);
						Fill3DMatByValue<double>(BLANK_VALUE, _cubes[cc][i_alpha]->grid4Section.v, _cubes[cc][i_alpha]->grid4Section.nPag, _cubes[cc][i_alpha]->grid4Section.nRow, _cubes[cc][i_alpha]->grid4Section.nCol);
					}
				}

				// кубы для решения обратной задачи

				Grid4 *** cubes = new GRID_2_POINTER[cols_3];

				for (int cc = 0; cc < cols_3; cc++)
				{
					for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
					{			
						new_names_of_colomns[cc] += 
							names_of_colomns[original_col_numbers[c]];
						new_names_of_colomns[cc] += "_";
					}
					cubes[cc] = new GRID_POINTER[mmd3.n_alpha];
					for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
					{
						// Грид по размеру геологической структуры
						cubes[cc][i_alpha] = CreateProfileGrid3D(mmd3);
						Zero3DMat<double>(cubes[cc][i_alpha]->grid4Section.v, cubes[cc][i_alpha]->grid4Section.nPag, cubes[cc][i_alpha]->grid4Section.nRow, cubes[cc][i_alpha]->grid4Section.nCol);
						Fill3DMatByValue<double>(BLANK_VALUE, cubes[cc][i_alpha]->grid4Section.v, cubes[cc][i_alpha]->grid4Section.nPag, cubes[cc][i_alpha]->grid4Section.nRow, cubes[cc][i_alpha]->grid4Section.nCol);
					}
				}



				bool only_korr_matrix = false;
				cout << "only_korr_matrix?  0 - no 1 - yes" << endl;
				cin >> only_korr_matrix;

				bool set_c0_r0 = false;
				cout << "Enter set_c0_r0?  0 - no 1 - yes" << endl;
				cin >> set_c0_r0;


				int c0 = 0, r0 = 0;

				if (set_c0_r0)
				{
					cout << "Enter c0?" << endl;
					cin >> c0;

					cout << "Enter r0?" << endl;
					cin >> r0;

					for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
					{
						for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
						{
							char file[2048];
							sprintf(file, "MyMethod3__of_%s_alpha=%e.cub", new_names_of_colomns[cc].c_str(), mmd3.v_alpha[i_alpha]);
							char * p;
							while (p=strchr (file,'\"'))
							{
								*p = '_';
							}
							
							if (OpenFileDlg(NULL, "Cube 3D grid(*.cub)\0*.cub\0All files \0*.*\0", 
								file) == S_OK)
							{
								//здесь load грид
								if (0 == ImportSurfer7Grid4(file, cubes[cc][i_alpha]))
								{
								}
							}
						}
					}
				}
				else
				{
				}

				// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
				vector<vector<vector<double> > >  sols_mean(mmd3.pages);
				double z_min = mmd3.z0 - mmd3.pages * mmd3.delta_z;
				//for (long p = 0; p < mmd3.pages; p++)
				//	zi = z_min + p * mmd3.delta_z;

				/*int nX = (DX - 2 * DZ) / step_x;
				int nY = (DY - 2 * DZ) / step_y;

				cout << "nX = " << nX << endl;
				cout << "nY = " << nY << endl;*/

				vector<vector<vector<double> > > new_vv;

				// матрицы реконструированных сигналов
				vector<vector<vector <sparse_row_map> > > MRECs;
				// число строк в этой матрице определяется длиной сигнала
				switch(type)
				{
				case 0:
					{
						MRECs.resize(cols);
						sols_mean.resize(cols);
						for (int cc = 0; cc < cols; cc++)
						{
							MRECs[cc].resize(mmd3.n_alpha);
							sols_mean[cc].resize(mmd3.n_alpha);
							for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
							{
								MRECs[cc][i_alpha].resize(vX.size());
								sols_mean[cc][i_alpha].resize(mmd3.pages);
								for(long p = 0; p < mmd3.pages; p++)
								{
									// индекс в строке матрицы оператора прямой задачи
									//i = p * rows * cols + r * cols + C;
									// rows = 1, cols = 1, i = p
									//cubes[cc][i_alpha]->grid4Section.v[p][r][c] = sol[p];
									double hi = mmd3.z0 - z_min - p * mmd3.delta_z;
									sols_mean[cc][i_alpha][p] = mmd3.spm.Apply(hi);
								}

							}
						}
					}
					break;
				case 1:
				case 2:
					{
						MRECs.resize(cols_3);
						sols_mean.resize(cols_3);
						for (int cc = 0; cc < cols_3; cc++)
						{
							MRECs[cc].resize(mmd3.n_alpha);
							sols_mean[cc].resize(mmd3.n_alpha);
							for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
							{
								MRECs[cc][i_alpha].resize(vX.size()*3);
								sols_mean[cc][i_alpha].resize(mmd3.pages);
								for(long p = 0; p < mmd3.pages; p++)
								{
									// индекс в строке матрицы оператора прямой задачи
									//i = p * rows * cols + r * cols + C;
									// rows = 1, cols = 1, i = p
									//cubes[cc][i_alpha]->grid4Section.v[p][r][c] = sol[p];
									double hi = mmd3.z0 - z_min - p * mmd3.delta_z;
									sols_mean[cc][i_alpha][p] = mmd3.spm.Apply(hi);
								}
							}
						}
					}
					break;
				}
				//а число колонок - соответствует числу светящихся столбов

				// массив индексов урезанных массивов pX, pY, pZ, pModul,pW
				// в индексации первоначальных массивов vX, vY, vZ, vModul, W
				vector<vector <long> > v_pInd;


				size_t light_colomn_number = 0;

				for (int c = c0; c < mmd3.cols; c++)
				{
					for (int r = r0; r < mmd3.rows; r++)
					{

						double center_x = mmd3.x0 + c * mmd3.delta_x;
						double center_y = mmd3.y0 + r * mmd3.delta_y;

						double min_x = center_x - 0.5 * dx;
						double max_x = center_x + 0.5 * dx;

						double min_y = center_y - 0.5 * dy;
						double max_y = center_y + 0.5 * dy;

						// массив индексов урезанных массивов pX, pY, pZ, pModul,pW
						// в индексации первоначальных массивов vX, vY, vZ, vModul, W
						v_pInd.push_back(vector<long>());

						GetPartOfData(min_x, max_x, min_y, max_y,
							 vX, vY, vZ,  A, vModul,  W,
							 pX, pY, pZ, pA, pModul, pW,
							 v_pInd.back());

						size_t len_pX = pX.size();
	
						//char common_directory_iX_iY[4096];			
                        //sprintf(dir_out, "%s/c=%03d_r=%03d", common_directory, c, r);
						//printf("common_directory_iX_iY = %s\n\n",common_directory_iX_iY);
						printf("len_pX = %d mmd3.pages = %d\n", len_pX, mmd3.pages);

						//if (len_pX * (type > 0 ? 2 : 1) >= mmd3.pages)
						{
							double min__x, min__y, min__z;
							double max__x, max__y, max__z;
							double delta__x;
							double delta__y;
							
							GetProfileDirection(pX, pY, pZ,
								min__x, min__y, min__z,
								max__x, max__y, max__z,
								delta__x, delta__y);

							if (!to_reduce_x) printf("delta__x = %f 0.5*dx = %f\n", delta__x, 0.5*dx);
							if (!to_reduce_y) printf("delta__y = %f 0.5*dy = %f\n", delta__y, 0.5*dy);
							printf("\n");

							//if ((to_reduce_x || delta__x > 0.5 * dx) && (to_reduce_y || delta__y > 0.5 * dy))
							if (true)
							{			
									
								//if (!CreateDirectory(common_directory_iX_iY,NULL))
								//{
								//}

								//UsingOneOfMyMethods3W(type, // тип прямой задачи
								//	granicy_kak_glubina, 
								//	ans_OP, z0, z_min,
								//	cols, mmd3, w3, AutoBuildProfile::ab,
								//	pX, pY, pZ, pModul, pW,
								//	names_of_colomns,
								//	original_col_numbers,
								//	to_test_algorithm_by_reconstructed_signal,
								//	common_directory_iX_iY,					   
								//	this->m_files_in_dir.nFilesInDirectory);

                                //sprintf(dir_out, "%s/common_raz_of_%d_files", common_directory_iX_iY, this->m_files_in_dir.nFilesInDirectory);
								//int n = 0;
                                sprintf(dir_out, "%s/c=%03d_r=%03d", common_directory, c, r);
								while (!CreateDirectory(dir_out,NULL))
								{
                                //	sprintf(dir_out, "%s/common_raz_of_%d_files(%d)", common_directory_iX_iY, this->m_files_in_dir.nFilesInDirectory, n++);
								}


									

								// начало расчётного блока
								//DoMyMethod3W(type, granicy_kak_glubina, description, mmd3, w3, ab,X,Y,Z, to_fill_matrix);
								if (/*to_fill_matrix*/true)
								{
                                    sprintf(mmd3.fn_operator_spm, "%s/operator.spm", dir_out);
                                    sprintf(mmd3.fn_operator_transponed, "%s/operator_transponed.spm", dir_out);

									//int smoof_power = 1024;
									//int smoof_power = 4096;
									//int smoof_power = 8;
									int smoof_power = mmd3.smoof_power;

									smoof_power /= 2;
									smoof_power *= 2;

									printf ("mmd3.fn_operator_spm = %s\n", mmd3.fn_operator_spm);
									//fprintf (description, "smoof_power = %d\n", smoof_power);

									printf("Filling of matrix\n");
									// формируем матрицу оператора прямой задачи, 
									// число строк равно длине сигнала 
									// (или суммарной длине нескольких сигналов - 
									// нескольких профилей на одной или, ещё лучше, на разных высотах)
									// на вход оператора подаётся геологическая структура 
									// источников геополяритонного сигнала
									// на выходе оператора имеем мощность излучения (сигнал) на профилях
									switch(type)
									{
									case 0:
										{
											FillingTheMatrix3D(smoof_power, mmd3.k_oslablenie, AutoBuildProfile::ab.k, NULL, mmd3.fn_operator_spm, 
												/*mmd.rows*/1, /*mmd.cols*/1, mmd3.pages,
												/*mmd.x0*/center_x, /*mmd.y0*/center_y, mmd3.z0,
												mmd3.delta_x, mmd3.delta_y, mmd3.delta_z,
												pX, pY, pZ, mmd3.pw_dnp, mmd3.wave_type);
										}
										break;
									case 1:
										{
											FillingTheMatrix3D_with_napravlennosty_diagramm(
												mmd3.k_oslablenie, 
												NULL, mmd3.fn_operator_spm, 
												/*mmd.rows*/1, /*mmd.cols*/1, mmd3.pages,
												/*mmd.x0*/center_x, /*mmd.y0*/center_y, mmd3.z0,
												mmd3.delta_x, mmd3.delta_y, mmd3.delta_z,
												pX, pY, pZ, pA,
												mmd3.pw_dnp,
												mmd3.min_value,
												mmd3.wave_type, 
												mmd3.spm);
										}
										break;
									case 2:
										{
											FillingTheMatrix3D_with_napravlennosty_diagramm_assume_tgdelta_much_more_than_one(
												mmd3.noise_color,
												2.0*PI*mmd3.nju_min,//omega_min
												2.0*PI*mmd3.nju_max,//omega_max
												1.0/mmd3.ro,//sigma
												NULL, mmd3.fn_operator_spm, 
												/*mmd.rows*/1, /*mmd.cols*/1, mmd3.pages,
												/*mmd.x0*/center_x, /*mmd.y0*/center_y, mmd3.z0,
												mmd3.delta_x, mmd3.delta_y, mmd3.delta_z,
												pX, pY, pZ, pA, 
												mmd3.pw_dnp,
												mmd3.min_value,
												mmd3.wave_type, 
												mmd3.spm);
										}
										break;
									}

									/*Grid4 * cube = ShowCube(mmd);
									char fn[1024]; 
                                    sprintf(fn, "%s/cube.cub",
										dir_out);
									SaveAsSurfer7Grid4(fn, cube);*/
								}
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
								if (!CheckMyLicense()) continue;        
#endif
								{
									vector<sparse_row_map> m;
									long _cols;
									LoadMatrix<sparse_row_map>(mmd3.fn_operator_spm, m, _cols);
									vector<sparse_row_map> at;
									Transponate(m, _cols, at);

									long transponed_cols = m.size(); //rows;

									StoreMatrix<sparse_row_map>(mmd3.fn_operator_transponed, at, transponed_cols);

									at.clear();
								}
								
								if (true)
								{
									// считаем коэффициенты корреляции между оператором прямой задачи 
									// и сигналом
									switch (type)
									{
									case 0:
										{
											/*rec_signals.resize(cols);
											for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
											{
												//printf_vector(v[c])
												DoInverseAndFillGrid3W(mmd3, w3, v[c], names_of_colomns[original_col_numbers[c]], rec_signals[c]);
											}	
											DoInverseAndFillGrid3W(mmd3, w3, vModul, "modul", rec_modul);*/
										}
										break;
									case 1:
									case 2:
										{
											vector<vector<double> > _new_v;
											//vector<string> new_names_of_colomns;
											int cols_3 = cols / 3;//2
											_new_v.resize(cols_3);
											//new_names_of_colomns.resize(cols_3);

											// for debug ///////////////////////////////////////////////
											size_t len_v = 0, size_v = pW.size();
											if (size_v) len_v = pW[0].size();
											// for debug ///////////////////////////////////////////////

											for (int cc = 0; cc < cols_3; cc++)
											{
												for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
												{								
													for (int i = 0; i < pX.size(); i++)
													{
														double value_v_c_i = pW[c][i];
														_new_v.operator [](cc).push_back(value_v_c_i);
													}
													//new_names_of_colomns[cc] += 
													//	names_of_colomns[original_col_numbers[c]];
													//new_names_of_colomns[cc] += "_";
												}
											}

											


											for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
											{
												//rec_signals[cc].resize(mmd3.n_alpha);
												//rec_signals2[cc].resize(mmd3.n_alpha);
												//for (int i_cube = 0; i_cube < 2; i_cube++)
												

												vector<double> v_korr, v_cov;

												if ( CorrelationProblem(mmd3.fn_operator_transponed, 
													/*signal*/_new_v.operator [](cc), 
													v_korr, 
													v_cov))
												{

													for(long p = 0; p < mmd3.pages; p++)
													{
														// индекс в строке матрицы оператора прямой задачи
														//i = p * rows * cols + r * cols + C;
														// rows = 1, cols = 1, i = p
														_cubes[cc][0]->grid4Section.v[p][r][c] = v_korr[p];
														_cubes[cc][1]->grid4Section.v[p][r][c] = v_cov[p];
													}
												}
												
												if (!to_reduce_x && !to_reduce_y && r == mmd3.rows - 1)
												{
													int i_cube = 0;
													SaveCubesAndSlices(dir_out,
														"korr",
														_cubes, mmd3, new_names_of_colomns,
														cc, i_cube, to_reduce_x, to_reduce_y);
													//i_cube = 1;
													//SaveCubesAndSlices(dir_out,
													//	"cov",
													//	_cubes, mmd3, new_names_of_colomns,
													//	cc, i_cube, to_reduce_x, to_reduce_y);
												}
											
											}	

											//
										}
										break;
									}

								}


								//printf("The matrix is filled!!!\n");

								char fn_grd[4098];
								if (mmd3.save_operator_grid)
								{
									//SparseStructureToMetafile(mmd3.fn_operator_spm, "operator_struct.emf");
									//SparseStructureToMetafile(mmd3.fn_operator_transponed, "operator_transponed_struct.emf");
																		

									if (mmd3.save_operator_grid)
									{
                                        sprintf(fn_grd, "%s/operator.grd", dir_out);
										SparseStructureToSurferGrid(mmd3.fn_operator_spm, fn_grd);
									}
                                    //sprintf(fn_grd, "%s/operator.emf", dir_out);
									//SparseStructureToMetafile(mmd3.fn_operator_spm, fn_grd);

									if (mmd3.save_operator_grid)
									{
                                        sprintf(fn_grd, "%s/operator_transponed.grd", dir_out);
										SparseStructureToSurferGrid(mmd3.fn_operator_transponed, fn_grd);
									}
								}

								if (only_korr_matrix)
									continue;

								if (true)
								{
                                    //sprintf(mmd3.fn_min_sq_mat, "%s/op_wav_min_sq_%f.spm", dir_out, mmd3.alpha_min_sq);
                                    sprintf(mmd3.fn_min_sq_mat, "%s/op_min_sq.spm", dir_out);
									//if (!FormMinSquareMatrix(mmd3.fn_operator_wav, mmd3.fn_min_sq_mat, mmd3.alpha_min_sq))
									if (!FormMinSquareMatrix(mmd3.fn_operator_transponed, mmd3.fn_min_sq_mat, 0.0))
									{
										printf("Error while FormMinSquareMatrix()\n");
										continue;
										//return false;
									}
																		
									if (mmd3.save_min_sq_grid)
									{
                                        sprintf(fn_grd, "%s/op_min_sq.grd", dir_out);
										SparseStructureToSurferGrid(mmd3.fn_min_sq_mat, fn_grd);
									}

								}

								mmd3.fnames_Lt.resize(mmd3.n_alpha);
								mmd3.fnames_L.resize(mmd3.n_alpha);
								mmd3.fnames_U.resize(mmd3.n_alpha);
								mmd3.fnames_P.resize(mmd3.n_alpha);
								for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
								{
									if (mmd3.to_calculi_holesski)
									{
								#if 0
										//SparseStructureToMetafile(mmd3.fn_min_sq_mat);
										SparseStructureToMetafile(mmd3.fn_min_sq_mat, "min_sq_mat_struct.emf");
								#endif
										char fn_Lt[4098];
                                        sprintf(fn_Lt, "%s/Lt_alpha=%01e.spm", dir_out, mmd3.v_alpha[i_alpha]);
										mmd3.fnames_Lt[i_alpha] = fn_Lt;
								#if 1
										if (!Holesski3(mmd3.fn_min_sq_mat, mmd3.fnames_Lt[i_alpha].c_str(), dir_out, mmd3.j_start, mmd3.v_alpha[i_alpha]))
										{
											printf("Error while Holesski3()\n");
											continue;
											//return false;
										}
								#else
										// BUG do not work!!!
										if (!Holesski3_in_operative_memory(mmd3.fn_min_sq_mat, mmd3.fn_Lt, dir_out))
										{
											printf("Error while Holesski3()\n");
											continue;
											//return false;
										}
								#endif
									}
									else
									{
										char fn[4098];

                                        sprintf(fn, "%s/L_alpha=%01e.spm", dir_out, mmd3.v_alpha[i_alpha]);
										mmd3.fnames_L[i_alpha] = fn;										
                                        sprintf(fn, "%s/U_alpha=%01e.spm", dir_out, mmd3.v_alpha[i_alpha]);
										mmd3.fnames_U[i_alpha] = fn;										
                                        sprintf(fn, "%s/P_alpha=%01e.ind", dir_out, mmd3.v_alpha[i_alpha]);
										mmd3.fnames_P[i_alpha] = fn;
										
										if (!LUP_in_operative_memory(mmd3.fn_min_sq_mat, 
											mmd3.fnames_L[i_alpha].c_str(), 
											mmd3.fnames_U[i_alpha].c_str(), 
											mmd3.fnames_P[i_alpha].c_str(), 
											dir_out, 
											mmd3.v_alpha[i_alpha]))
										{
											printf("Error while Holesski3()\n");
											continue;
											//return false;
										}
									}
								}

								switch (type)
								{
								case 0:
									{
										/*rec_signals.resize(cols);
										for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
										{
											//printf_vector(v[c])
											DoInverseAndFillGrid3W(mmd3, w3, v[c], names_of_colomns[original_col_numbers[c]], rec_signals[c]);
										}	
										DoInverseAndFillGrid3W(mmd3, w3, vModul, "modul", rec_modul);*/
									}
									break;
								case 1:
								case 2:
									{
										//vector<vector<double> > new_v;
										new_vv.push_back(vector<vector<double> >());
										//vector<string> new_names_of_colomns;
										int cols_3 = cols / 3;//2
										new_vv.back().resize(cols_3);
										//new_names_of_colomns.resize(cols_3);

										// for debug ///////////////////////////////////////////////
										size_t len_v = 0, size_v = pW.size();
										if (size_v) len_v = pW[0].size();
										// for debug ///////////////////////////////////////////////

										for (int cc = 0; cc < cols_3; cc++)
										{
											for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
											{								
												for (int i = 0; i < pX.size(); i++)
												{
													double value_v_c_i = pW[c][i];
													new_vv.back().operator [](cc).push_back(value_v_c_i);
												}
												//new_names_of_colomns[cc] += 
												//	names_of_colomns[original_col_numbers[c]];
												//new_names_of_colomns[cc] += "_";
											}
										}

										


										vector<vector<vector <double> > > rec_signals;
										rec_signals.resize(cols_3);

										vector<vector<vector <double> > > rec_signals2;
										rec_signals2.resize(cols_3);

										for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
										{
											rec_signals[cc].resize(mmd3.n_alpha);
											rec_signals2[cc].resize(mmd3.n_alpha);
											for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
											{
												if (/*iverse problem solving*/!mmd3.use_norm_w)
												{
													printf("Start of solve the inverse problem\n");
													
													// находим решение обратной задачи
													vector<double> sol(/*Ns*/mmd3.pages);
													//#if SPARSE_OUT_W
													if (mmd3.to_calculi_holesski)
													{
														if (!InverseProblem_Solving(false, mmd3.fn_operator_transponed, 
															mmd3.fn_min_sq_mat,
															mmd3.fnames_Lt[i_alpha].c_str(), 
															/*signal*/new_vv.back().operator [](cc), sol, mmd3.v_alpha[i_alpha], sols_mean[cc][i_alpha]))
														{
														}
													}
													else // LUP
													{
														if (!InverseProblem_Solving(false, mmd3.fn_operator_transponed, 
															mmd3.fn_min_sq_mat, 
															mmd3.fnames_L[i_alpha].c_str(), 
															mmd3.fnames_U[i_alpha].c_str(), 
															mmd3.fnames_P[i_alpha].c_str(), 
															/*signal*/new_vv.back().operator [](cc), sol, mmd3.v_alpha[i_alpha], sols_mean[cc][i_alpha]))
														{
														}
													}
													//#endif
													printf("The inverse problem is solved!!!\n");

												
													for(long p = 0; p < mmd3.pages; p++)
													{
														// индекс в строке матрицы оператора прямой задачи
														//i = p * rows * cols + r * cols + C;
														// rows = 1, cols = 1, i = p
														cubes[cc][i_alpha]->grid4Section.v[p][r][c] = sol[p];
													}
													ErrorOfInverseProblemSolving(true, mmd3.fn_operator_spm, /*signal*/new_vv.back().operator [](cc), sol, new_names_of_colomns[cc], rec_signals[cc][i_alpha]);
													printf("Error of the inverse problem is calculed!!!\n\n");

								
													for (int i_ind = 0;i_ind < v_pInd.back().size(); i_ind++)
													{
														long ind = v_pInd.back().operator [](i_ind);
														int i = i_ind;

														MRECs[cc][i_alpha][ind].replace(size_t(light_colomn_number), rec_signals[cc][i_alpha][i]);
														i += v_pInd.back().size(); ind += vX.size();
														MRECs[cc][i_alpha][ind].replace(size_t(light_colomn_number), rec_signals[cc][i_alpha][i]);
														i += v_pInd.back().size(); ind += vX.size();
														MRECs[cc][i_alpha][ind].replace(size_t(light_colomn_number), rec_signals[cc][i_alpha][i]);
													}
											

													if (false)
													{
														printf("Start of solve the inverse problem by reconstructed signal\n");
														
														// находим решение обратной задачи
														vector<double> sol2(/*Ns*/mmd3.pages);
														//#if SPARSE_OUT_W
														if (mmd3.to_calculi_holesski)
														{
															if (!InverseProblem_Solving(false, mmd3.fn_operator_transponed, 
																mmd3.fn_min_sq_mat, 
																mmd3.fnames_Lt[i_alpha].c_str(), 
																rec_signals[cc][i_alpha], sol2, mmd3.v_alpha[i_alpha], sols_mean[cc][i_alpha]))
															{
															}
														}
														else
														{
															if (!InverseProblem_Solving(false, mmd3.fn_operator_transponed, 
																mmd3.fn_min_sq_mat, 
																mmd3.fnames_L[i_alpha].c_str(), 
																mmd3.fnames_U[i_alpha].c_str(), 
																mmd3.fnames_P[i_alpha].c_str(), 
																rec_signals[cc][i_alpha], sol2, mmd3.v_alpha[i_alpha], sols_mean[cc][i_alpha]))
															{
															}
														}
														//#endif
														printf("The inverse problem  by reconstructed signal is solved!!!\n");
													
														for(long p = 0; p < mmd3.pages; p++)
														{
															// индекс в строке матрицы оператора прямой задачи
															//i = p * rows * cols + r * cols + C;
															// rows = 1, cols = 1, i = p
														//	cubes2[cc][i_alpha]->grid4Section.v[p][r][c] = sol2[p];
														}
														ErrorOfInverseProblemSolving(true, mmd3.fn_operator_spm, /*signal*/rec_signals[cc][i_alpha], sol2, new_names_of_colomns[cc], rec_signals2[cc][i_alpha]);
														printf("Error of the inverse problem by reconstructed signal is calculed!!!\n\n");

													}
												}
												else
												{
													for(long p = 0; p < mmd3.pages; p++)
													{
														// индекс в строке матрицы оператора прямой задачи
														//i = p * rows * cols + r * cols + C;
														// rows = 1, cols = 1, i = p
														cubes[cc][i_alpha]->grid4Section.v[p][r][c] = sols_mean[cc][i_alpha][p];
													}
													ErrorOfInverseProblemSolving(true, mmd3.fn_operator_spm, /*signal*/new_vv.back().operator [](cc), sols_mean[cc][i_alpha], new_names_of_colomns[cc], rec_signals[cc][i_alpha]);
													printf("Error of the inverse problem is calculed!!!\n\n");

								
													for (int i_ind = 0;i_ind < v_pInd.back().size(); i_ind++)
													{
														long ind = v_pInd.back().operator [](i_ind);
														int i = i_ind;

														MRECs[cc][i_alpha][ind].replace(size_t(light_colomn_number), rec_signals[cc][i_alpha][i]);
														i += v_pInd.back().size(); ind += vX.size();
														MRECs[cc][i_alpha][ind].replace(size_t(light_colomn_number), rec_signals[cc][i_alpha][i]);
														i += v_pInd.back().size(); ind += vX.size();
														MRECs[cc][i_alpha][ind].replace(size_t(light_colomn_number), rec_signals[cc][i_alpha][i]);
													}
												}


												if (!to_reduce_x && !to_reduce_y && r == mmd3.rows - 1)
												{
													SaveCubesAndSlices(dir_out,
														"LC0",
														cubes, mmd3, new_names_of_colomns,
														cc, i_alpha, to_reduce_x, to_reduce_y);
												}
											}
										}	

										//
									}
									break;
								}
								
							}
							//else
							//{
							//	printf("!!!	!((to_reduce_x || delta__x > 0.5 * dx) && (to_reduce_y || delta__y > 0.5 * dy))\n\n");
							//}
						}
						light_colomn_number++;
					}					
					r0 = 0;
				}

				char DirName[4098];
                sprintf(DirName, "%s/korr", common_directory);
				if (!CreateDirectory(DirName,NULL))
				{
				}

				for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
				{
					int i_cube = 0;
					SaveCubesAndSlices(DirName,
						"korr",
						_cubes, mmd3, new_names_of_colomns,
						cc, i_cube, to_reduce_x, to_reduce_y);
				}

				if (!only_korr_matrix)
				{
					//
					printf("Save the razrez matrix\n");

                    sprintf(DirName, "%s/LC1", common_directory);
					if (!CreateDirectory(DirName,NULL))
					{
					}
					for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
					{
						for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
						{
							SaveCubesAndSlices(DirName,
								"LC1",
								cubes, mmd3, new_names_of_colomns,
								cc, i_alpha, to_reduce_x, to_reduce_y);
						}
					}
					printf("Yes!!!\n");




					// матрицы реконструированных сигналов
					// число строк в этой матрице определяется длиной сигнала
					switch(type)
					{
					case 0:
						{
							for (int cc = 0; cc < cols; cc++)
							{
								for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
								{
									//MRECs[cc][i_alpha].resize(vX.size());
								}
							}
						}
						break;
					case 1:
					case 2:
						{
							vector<vector<double> > new_V;
							new_V.resize(cols_3);

							// for debug ///////////////////////////////////////////////
							size_t len_v = 0, size_v = W.size();
							if (size_v) len_v = W[0].size();
							// for debug ///////////////////////////////////////////////

							for (int cc = 0; cc < cols_3; cc++)
							{
								for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
								{								
									for (int i = 0; i < vX.size(); i++)
									{
										double value_v_c_i = W[c][i];
										new_V[cc].push_back(value_v_c_i);
									}
									//new_names_of_colomns[cc] += 
									//	names_of_colomns[original_col_numbers[c]];
									//new_names_of_colomns[cc] += "_";
								}
							}

							char file_name[1024];
							char name[2048];
							char method_name[512];
							sprintf(method_name, "LC2");
							sprintf(name, "norm_k_%s", 	method_name);

                            sprintf(file_name, "%s/%s.txt", DirName, name);
							//char * p; while (p=strchr (file_name,'\"')){*p = '_';}
							FILE * file = fopen (file_name, "wt");
							for (int cc = 0; cc < cols_3; cc++)
							{
								for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
								{
									double norm_k = 1.0;
									//bool use_norm_k = true;
									if(true)
									{
										// производим построчное суммирование матрицы реконструированных сигналов,
										vector<double> SXYZ(MRECs[cc][i_alpha].size());
										vector<double> DXYZ(MRECs[cc][i_alpha].size());
										for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
										{
											// получаем таким образом вектор суммарного реконструированного сигнала 
											// от всех светящихся столбов
											SXYZ[mrec_r] = MRECs[cc][i_alpha][mrec_r].Sum();
											// отнимаем этот вектор из вектора исходного сигнала
											DXYZ[mrec_r] = new_V[cc][mrec_r] - SXYZ[mrec_r];
										}

										double mean_SXYZ = Mean(SXYZ);
										double mean_new_V_cc = Mean(new_V[cc]);
										if(mean_SXYZ != 0.0)
											norm_k = mmd3.norm_k_part * mean_new_V_cc / mean_SXYZ;									
										
										double error = sqrt(SquareSum(DXYZ) / new_V[cc].size());
										double signal = sqrt(SquareSum(new_V[cc]) / new_V[cc].size());
										printf("Summary norm_k = %f error: e = %f b = %f e/b = %f%%\n", norm_k, error, signal, 100.0 * error/signal );
																
										if(file)
										{
											fprintf(file, "%s i_alpha = %d norm_k = %f\n", new_names_of_colomns[cc].c_str(), i_alpha, norm_k);
										}							
				
										if (true)
										{

											char bln_name[1024];
											char name[2048];
											char method_name[512];
											sprintf(method_name, "LC1");
											sprintf(name, "%s_of_%s_alpha=%01e.cub", 
												method_name,
												new_names_of_colomns[cc].c_str(), 
												mmd3.v_alpha[i_alpha]);

                                            sprintf(bln_name, "%s/origin_%s.bln", DirName,
												name);
											char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
											FILE * bln = fopen (bln_name, "wt");
											if(bln)
											{
												fprintf(bln, "%d,%d, origin\n", new_V[cc].size(), 0);
												for(size_t i = 0; i < new_V[cc].size(); i++)
												{
													fprintf(bln, "%f,%f\n", double(i), double(new_V[cc][i]));
												}	
												fclose(bln);
											}
											
                                            sprintf(bln_name, "%s/reconstr_%s.bln", DirName, name);
											while (p=strchr (bln_name,'\"')){*p = '_';}
											bln = fopen (bln_name, "wt");
											if(bln)
											{
												fprintf(bln, "%d,%d, reconstr\n", SXYZ.size(), 0);
												for(size_t i = 0; i < SXYZ.size(); i++)
												{
													fprintf(bln, "%f,%f\n", double(i), double(SXYZ[i]));
												}
												fclose(bln);
											}
										}
										

									}
									//MRECs[cc][i_alpha]
									//vector<sparse_row_map> m;
									char fn_transponed_mrec[4098];
									sprintf(fn_transponed_mrec, 
                                        "%s/mrec_transponed_cc=%d_i_alpha=%d.spm",
										dir_out, cc, i_alpha);

									char fn_mrec[4098];
									sprintf(fn_mrec, 
                                        "%s/mrec_cc=%d_i_alpha=%d.spm",
										dir_out, cc, i_alpha);
									{
										long __cols = light_colomn_number;
										//LoadMatrix(mmd3.fn_operator_spm, m, __cols);
										vector<sparse_row_map> at;
										Transponate(MRECs[cc][i_alpha], __cols, at);

										long __transponed_cols = MRECs[cc][i_alpha].size(); //rows;



										StoreMatrix<sparse_row_map>(fn_mrec, MRECs[cc][i_alpha], __cols);
										StoreMatrix<sparse_row_map>(fn_transponed_mrec, at, __transponed_cols);

										at.clear();
									}

									//printf("The matrix is filled!!!\n");
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
									if (!CheckMyLicense()) continue;        
#endif
									char fn_mrec_min_sq[4098];
									if (/*to_calculi_min_sq_mat*/true)
									{
										char fn_grd[4098];

										sprintf(fn_grd, 
                                            "%s/mrec_transponed_cc=%d_i_alpha=%d.grd",
											dir_out, cc, i_alpha);
										SparseStructureToSurferGrid(fn_transponed_mrec, fn_grd);
                                        //sprintf(fn_grd, "%s/operator.emf", dir_out);
										//SparseStructureToMetafile(mmd3.fn_operator_spm, fn_grd);

										if (!mmd3.use_norm_k)
										{
											sprintf(fn_mrec_min_sq, 
                                                "%s/mrec_min_sq_cc=%d_i_alpha=%d.spm",
												dir_out, cc, i_alpha);
											if (!FormMinSquareMatrix(fn_transponed_mrec, 
												fn_mrec_min_sq, 0.0))
											{
												printf("Error while FormMinSquareMatrix()\n");
												continue;
												//return false;
											}
											sprintf(fn_grd, 
                                                "%s/mrec_min_sq_cc=%d_i_alpha=%d.grd",
												dir_out, cc, i_alpha);
											SparseStructureToSurferGrid(fn_mrec_min_sq, fn_grd);
										}
										
										char fn_mrec_Lt[4098];
										if (/*to_calculi_holesski*/!mmd3.use_norm_k)
										{

                                            sprintf(fn_mrec_Lt, "%s/mrec_Lt_cc=%d_i_alpha=%d.spm",
												dir_out, cc, i_alpha);
											//mmd3.fnames_Lt[i_alpha] = fn_Lt;

											if (!Holesski3(fn_mrec_min_sq, 
												fn_mrec_Lt, dir_out, 0, 0.0))
											{
												printf("Error while Holesski3()\n");
												continue;
												//return false;
											}

										}
										if (mmd3.use_norm_k)
										{													
											//size_t __light_colomn_number = 0;
											for (int c = 0; c < mmd3.cols; c++)
											{
												for (int r = 0; r < mmd3.rows; r++)
												{
													for(long p = 0; p < mmd3.pages; p++)
													{
														// 
														cubes[cc][i_alpha]->grid4Section.v[p][r][c] *= 
															norm_k;
													}
													//__light_colomn_number++;
												}
											}
											for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
											{
												MRECs[cc][i_alpha][mrec_r].multip_equal(norm_k);
											}
											if (mmd3.use_norm_w)
											{
												for(long p = 0; p < mmd3.pages; p++)
												{
													sols_mean[cc][i_alpha][p] *= norm_k;
												}
											}
										}
										else//inverse mrec
										{
											// находим вектор нормировочных коэффициентов для всех всетящихся столбцов
											vector<double> sol_norm_k(light_colomn_number);
											vector<double> sol_norm_k_mean(light_colomn_number, 0.0);
											//#if SPARSE_OUT_W
											if (!InverseProblem_Solving(false, fn_transponed_mrec, 
												fn_mrec_min_sq, 
												fn_mrec_Lt, 
												/*signal*/new_V[cc], sol_norm_k,
												0.0, sol_norm_k_mean))
											{
											}
											//#endif
											printf("The mrec inverse problem is solved!!!\n");							

														
											size_t __light_colomn_number = 0;
											for (int c = 0; c < mmd3.cols; c++)
											{
												for (int r = 0; r < mmd3.rows; r++)
												{
													for(long p = 0; p < mmd3.pages; p++)
													{
														// 
														cubes[cc][i_alpha]->grid4Section.v[p][r][c] *= 
															sol_norm_k[__light_colomn_number];
													}
													__light_colomn_number++;
												}
											}
											
											vector<double> mrec_rec_signal;
											ErrorOfInverseProblemSolving(true, fn_mrec,
												/*signal*/new_V[cc], sol_norm_k, "mrec", mrec_rec_signal);
											printf("Error of the mrec inverse problem is calculed!!!\n\n");


											for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
											{
												MRECs[cc][i_alpha][mrec_r].multip_equal(sol_norm_k);
											}
										}
									}
									//mmd3.fnames_Lt.resize(mmd3.n_alpha);
								}
							}

							if(file)
							{
								fclose(file);
							}						
                            sprintf(DirName, "%s/LC2", common_directory);
							if (!CreateDirectory(DirName,NULL))
							{
							}
							for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
							{
								for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
								{
									SaveCubesAndSlices(DirName,
										"LC2",
										cubes, mmd3, new_names_of_colomns,
										cc, i_alpha, to_reduce_x, to_reduce_y);

									if(true)
									{
										// производим построчное суммирование матрицы реконструированных сигналов,
										vector<double> SXYZ(MRECs[cc][i_alpha].size());
										vector<double> DXYZ(MRECs[cc][i_alpha].size());
										for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
										{
											// получаем таким образом вектор суммарного реконструированного сигнала 
											// от всех светящихся столбов
											SXYZ[mrec_r] = MRECs[cc][i_alpha][mrec_r].Sum();
											// отнимаем этот вектор из вектора исходного сигнала
											DXYZ[mrec_r] = new_V[cc][mrec_r] - SXYZ[mrec_r];
										}

										double norm_k2 = 1.0;

										double mean_SXYZ = Mean(SXYZ);
										double mean_new_V_cc = Mean(new_V[cc]);
										if(mean_SXYZ != 0.0)
											norm_k2 = mean_new_V_cc / mean_SXYZ;									
										
										double error = sqrt(SquareSum(DXYZ) / new_V[cc].size());
										double signal = sqrt(SquareSum(new_V[cc]) / new_V[cc].size());
										printf("Summary norm_k2 = %f error: e = %f b = %f e/b = %f%%\n", norm_k2, error, signal, 100.0 * error/signal );
																	
				
										if (true)
										{

											char bln_name[1024];
											char name[2048];
											char method_name[512];
											sprintf(method_name, "LC2");
											sprintf(name, "%s_of_%s_alpha=%01e.cub", 
												method_name,
												new_names_of_colomns[cc].c_str(), 
												mmd3.v_alpha[i_alpha]);

                                            sprintf(bln_name, "%s/origin_%s.bln", DirName,
												name);
											char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
											FILE * bln = fopen (bln_name, "wt");
											if(bln)
											{
												fprintf(bln, "%d,%d, origin\n", new_V[cc].size(), 0);
												for(size_t i = 0; i < new_V[cc].size(); i++)
												{
													fprintf(bln, "%f,%f\n", double(i), double(new_V[cc][i]));
												}	
												fclose(bln);
											}
											
                                            sprintf(bln_name, "%s/reconstr_%s.bln", DirName, name);
											while (p=strchr (bln_name,'\"')){*p = '_';}
											bln = fopen (bln_name, "wt");
											if(bln)
											{
												fprintf(bln, "%d,%d, reconstr\n", SXYZ.size(), 0);
												for(size_t i = 0; i < SXYZ.size(); i++)
												{
													fprintf(bln, "%f,%f\n", double(i), double(SXYZ[i]));
												}
												fclose(bln);
											}
										}						

									}

								}
							}
							char iter_file[4098];
                            sprintf(iter_file, "%s/iterations.txt", common_directory);
							FILE * iter_txt = fopen (iter_file, "wt");
							if (iter_txt)
							{
								fprintf(iter_txt, "iterations");
								for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
								{
									for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
									{
										fprintf(iter_txt, ",error_of_%s_alpha=%e", new_names_of_colomns[cc].c_str(), mmd3.v_alpha[i_alpha]);
									}
								}
								fprintf(iter_txt, "\n");
								fclose(iter_txt);
							}
							vector<vector<double> > last_errors;
							vector<vector<unsigned int> > increse_errors;
							vector<vector<bool> > to_calc;
											
							switch(type)
							{
							case 0:
								{
									last_errors.resize(cols);
									increse_errors.resize(cols);
									to_calc.resize(cols);
									for (int cc = 0; cc < cols; cc++)
									{
										last_errors[cc].resize(mmd3.n_alpha, DBL_MAX);
										increse_errors[cc].resize(mmd3.n_alpha, 0);
										to_calc[cc].resize(mmd3.n_alpha, true);
									}
								}
								break;
							case 1:
							case 2:
								{
									last_errors.resize(cols_3);
									increse_errors.resize(cols_3);
									to_calc.resize(cols_3);
									for (int cc = 0; cc < cols_3; cc++)
									{
										last_errors[cc].resize(mmd3.n_alpha, DBL_MAX);
										increse_errors[cc].resize(mmd3.n_alpha, 0);
										to_calc[cc].resize(mmd3.n_alpha, true);
									}
								}
								break;
							}

							for (int iteration = 1; iteration <= 10000; iteration++)
							{
								char method_name[512];
								sprintf(method_name, "LC_iter=%03d",iteration);
                                sprintf(DirName, "%s/%s", common_directory, method_name);
								if (iteration%mmd3.iter_save == 0)
								{
									if (!CreateDirectory(DirName,NULL))
									{
									}
								}
								iter_txt = fopen (iter_file, "at");
								if (iter_txt)
								{
									fprintf(iter_txt, "%d", iteration);
								}
								bool to_break = true;
								for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
								{
									for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
									{	
										if (to_calc[cc][i_alpha])
										{
											to_break = false;
											//в цикле для каждого свет. столба 
											size_t ___light_colomn_number = 0;
											for (int c = 0; c < mmd3.cols; c++)
											{
												for (int r = 0; r < mmd3.rows; r++)
												{
													// производим построчное суммирование матрицы реконструированных сигналов,
													// исключая из этого суммирования текущую колонку,
													// соответствующую номеру текщего светящегося столба

													vector<double> sXYZ(MRECs[cc][i_alpha].size());
													vector<double> dXYZ(MRECs[cc][i_alpha].size());
													for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
													{
														// получаем таким образом вектор суммарного реконструированного сигнала 
														// от всех светящихся столбов кроме текущего реконструированного столба
														sXYZ[mrec_r] = MRECs[cc][i_alpha][mrec_r].SumExcludeColomn(___light_colomn_number);
														// отнимаем этот вектор из вектора исходного сигнала
														dXYZ[mrec_r] = new_V[cc][mrec_r] - sXYZ[mrec_r];
													}
													// извлекаем из этой разности dXYZ с помощью текущего вектора индексов pInd вектор pXYZ (аналог new_v)
													vector<double> pXYZ(3*v_pInd[___light_colomn_number].size());
													for (int i_ind = 0;i_ind < v_pInd[___light_colomn_number].size(); i_ind++)
													{
														long ind = v_pInd[___light_colomn_number].operator [](i_ind);
														int i = i_ind;

														pXYZ[i] = mmd3.dXYZ_part * dXYZ[ind];
														i += v_pInd[___light_colomn_number].size(); ind += vX.size();
														pXYZ[i] = mmd3.dXYZ_part * dXYZ[ind];
														i += v_pInd[___light_colomn_number].size(); ind += vX.size();
														pXYZ[i] = mmd3.dXYZ_part * dXYZ[ind];
													}
													// к которому с помощью метода наименьших квадратов приближаем 
													// сигнал текущего столба
													if (true)
													{
														//printf("Start of solve the inverse problem\n");
														
														// находим решение обратной задачи
														vector<double> sol(/*Ns*/mmd3.pages);
														//#if SPARSE_OUT_W
                                                        sprintf(dir_out, "%s/c=%03d_r=%03d", common_directory, c, r);
                                                        sprintf(mmd3.fn_operator_spm, "%s/operator.spm", dir_out);
                                                        sprintf(mmd3.fn_operator_transponed, "%s/operator_transponed.spm", dir_out);
                                                        sprintf(mmd3.fn_min_sq_mat, "%s/op_min_sq.spm", dir_out);
														if (mmd3.to_calculi_holesski)
														{
																				
															char fn_Lt[4098];
                                                            sprintf(fn_Lt, "%s/Lt_alpha=%01e.spm", dir_out, mmd3.v_alpha[i_alpha]);
															mmd3.fnames_Lt[i_alpha] = fn_Lt;

															if (!InverseProblem_Solving(false, mmd3.fn_operator_transponed, 
																mmd3.fn_min_sq_mat, 
																mmd3.fnames_Lt[i_alpha].c_str(), 
																/*signal*/pXYZ, sol, mmd3.v_alpha[i_alpha], sols_mean[cc][i_alpha]))
															{
															}
														}
														else
														{
															char fn[4098];

                                                            sprintf(fn, "%s/L_alpha=%01e.spm", dir_out, mmd3.v_alpha[i_alpha]);
															mmd3.fnames_L[i_alpha] = fn;										
                                                            sprintf(fn, "%s/U_alpha=%01e.spm", dir_out, mmd3.v_alpha[i_alpha]);
															mmd3.fnames_U[i_alpha] = fn;										
                                                            sprintf(fn, "%s/P_alpha=%01e.ind", dir_out, mmd3.v_alpha[i_alpha]);
															mmd3.fnames_P[i_alpha] = fn;

															if (!InverseProblem_Solving(false, mmd3.fn_operator_transponed, 
																mmd3.fn_min_sq_mat, 
																mmd3.fnames_L[i_alpha].c_str(), 
																mmd3.fnames_U[i_alpha].c_str(), 
																mmd3.fnames_P[i_alpha].c_str(), 
																/*signal*/pXYZ, sol, mmd3.v_alpha[i_alpha], sols_mean[cc][i_alpha]))
															{
															}
														}
														//#endif
														//printf("The inverse problem is solved!!!\n");

													
														for(long p = 0; p < mmd3.pages; p++)
														{
															// индекс в строке матрицы оператора прямой задачи
															// i = p * rows * cols + r * cols + C;
															// rows = 1, cols = 1, i = p
															cubes[cc][i_alpha]->grid4Section.v[p][r][c] = sol[p];
														}
														vector<double> ___rec_signal;
														ErrorOfInverseProblemSolving(false, mmd3.fn_operator_spm, /*signal*/pXYZ, sol, new_names_of_colomns[cc], 
															___rec_signal);
														//printf("Error of the inverse problem is calculed!!!\n\n");
														if (false)
														{
															char bln_name[1024];
															char name[2048];
															sprintf(name, "iter=%d_r=%d_c=%d_of_%s_i_alpha=%d", 
																iteration,
																r,c,
																new_names_of_colomns[cc].c_str(), 
																i_alpha);

                                                            sprintf(bln_name, "%s/sol_%s.bln", DirName,
																name);
															char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
															FILE * bln = fopen (bln_name, "wt");
															if(bln)
															{
																fprintf(bln, "%d,%d, sol\n", sol.size(), 0);
																for(size_t i = 0; i < sol.size(); i++)
																{
																	fprintf(bln, "%f,%f\n", double(i), double(sol[i]));
																}	
																fclose(bln);
															}
															
                                                            sprintf(bln_name, "%s/sol_mean_%s.bln", DirName, name);
															while (p=strchr (bln_name,'\"')){*p = '_';}
															bln = fopen (bln_name, "wt");
															if(bln)
															{
																fprintf(bln, "%d,%d, reconstr\n", sols_mean[cc][i_alpha].size(), 0);
																for(size_t i = 0; i < sols_mean[cc][i_alpha].size(); i++)
																{
																	fprintf(bln, "%f,%f\n", double(i), double(sols_mean[cc][i_alpha][i]));
																}
																fclose(bln);
															}
													
                                                            sprintf(bln_name, "%s/origin_pXYZ_%s.bln", DirName,
																name);
															while (p=strchr (bln_name,'\"')){*p = '_';}
															bln = fopen (bln_name, "wt");
															if(bln)
															{
																fprintf(bln, "%d,%d, origin_pXYZ\n", pXYZ.size(), 0);
																for(size_t i = 0; i < pXYZ.size(); i++)
																{
																	fprintf(bln, "%f,%f\n", double(i), double(pXYZ[i]));
																}	
																fclose(bln);
															}
															
                                                            sprintf(bln_name, "%s/reconstr_%s.bln", DirName, name);
															while (p=strchr (bln_name,'\"')){*p = '_';}
															bln = fopen (bln_name, "wt");
															if(bln)
															{
																fprintf(bln, "%d,%d, reconstr\n", ___rec_signal.size(), 0);
																for(size_t i = 0; i < ___rec_signal.size(); i++)
																{
																	fprintf(bln, "%f,%f\n", double(i), double(___rec_signal[i]));
																}
																fclose(bln);
															}
														}

														size_t ___rec_signal_size = ___rec_signal.size();
														size_t v_pInd_size = v_pInd.size();
														size_t v_pInd_light_colomn_number_size = v_pInd[___light_colomn_number].size();
														size_t mrecs_cc_i_alpha_size = MRECs[cc][i_alpha].size();
													
														for (int i_ind = 0;i_ind < v_pInd[___light_colomn_number].size(); i_ind++)
														{
															long ind = v_pInd[___light_colomn_number].operator [](i_ind);
															int i = i_ind;

															MRECs[cc][i_alpha][ind].replace(size_t(___light_colomn_number), ___rec_signal[i]);
															i += v_pInd[___light_colomn_number].size(); ind += vX.size();
															MRECs[cc][i_alpha][ind].replace(size_t(___light_colomn_number), ___rec_signal[i]);
															i += v_pInd[___light_colomn_number].size(); ind += vX.size();
															MRECs[cc][i_alpha][ind].replace(size_t(___light_colomn_number), ___rec_signal[i]);
														}
													

													}
													___light_colomn_number++;
												}
											}
									
											// производим построчное суммирование матрицы реконструированных сигналов,
											vector<double> SXYZ(MRECs[cc][i_alpha].size());
											vector<double> DXYZ(MRECs[cc][i_alpha].size());
											for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
											{
												// получаем таким образом вектор суммарного реконструированного сигнала 
												// от всех светящихся столбов
												SXYZ[mrec_r] = MRECs[cc][i_alpha][mrec_r].Sum();
												// отнимаем этот вектор из вектора исходного сигнала
												DXYZ[mrec_r] = new_V[cc][mrec_r] - SXYZ[mrec_r];
											}

											double norm_k = 1.0;
									
									

											double mean_SXYZ = Mean(SXYZ);
											double mean_new_V_cc = Mean(new_V[cc]);
											if(mean_SXYZ != 0.0)
												norm_k = mean_new_V_cc / mean_SXYZ;		

														
											
											double error = sqrt(SquareSum(DXYZ) / new_V[cc].size());
											double signal = sqrt(SquareSum(new_V[cc]) / new_V[cc].size());

											double error_normed = 100.0 * error/signal;
											printf("iter %d norm_k = %f err: e = %f b = %f e/b = %f%%\n", iteration, norm_k, error, signal, error_normed);
											
											if (iter_txt)
											{
												fprintf(iter_txt, ",%f", error_normed);
											}

											if (error_normed > last_errors[cc][i_alpha])
												increse_errors[cc][i_alpha]++;
											else
												increse_errors[cc][i_alpha] = 0;

											if (increse_errors[cc][i_alpha] > 10)
												to_calc[cc][i_alpha] = false;


											last_errors[cc][i_alpha] = error_normed;


																		
											if (iteration%mmd3.iter_save == 0)
											{
												sprintf(method_name, "LC_iter=%03d_err=%f",iteration,100.0*error/signal);
												SaveCubesAndSlices(DirName,
													method_name,
													cubes, mmd3, new_names_of_colomns,
													cc, i_alpha, to_reduce_x, to_reduce_y);

												if (true)
												{

													char bln_name[1024];
													char name[2048];
													sprintf(name, "%s_of_%s_alpha=%01e.cub", 
														method_name,
														new_names_of_colomns[cc].c_str(), 
														mmd3.v_alpha[i_alpha]);

                                                    sprintf(bln_name, "%s/origin_%s.bln", DirName,
														name);
													char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
													FILE * bln = fopen (bln_name, "wt");
													if(bln)
													{
														fprintf(bln, "%d,%d, origin\n", new_V[cc].size(), 0);
														for(size_t i = 0; i < new_V[cc].size(); i++)
														{
															fprintf(bln, "%f,%f\n", double(i), double(new_V[cc][i]));
														}	
														fclose(bln);
													}
													
                                                    sprintf(bln_name, "%s/reconstr_%s.bln", DirName, name);
													while (p=strchr (bln_name,'\"')){*p = '_';}
													bln = fopen (bln_name, "wt");
													if(bln)
													{
														fprintf(bln, "%d,%d, reconstr\n", SXYZ.size(), 0);
														for(size_t i = 0; i < SXYZ.size(); i++)
														{
															fprintf(bln, "%f,%f\n", double(i), double(SXYZ[i]));
														}
														fclose(bln);
													}
												}
											}
											if (mmd3.use_norm_k_on_every_iteration)
										{													
											norm_k -= 1.0;
											norm_k /= 1000.0;// * light_colomn_number;
											norm_k += 1.0;

											for (int c = 0; c < mmd3.cols; c++)
											{
												for (int r = 0; r < mmd3.rows; r++)
												{
													for(long p = 0; p < mmd3.pages; p++)
													{
														// 
														cubes[cc][i_alpha]->grid4Section.v[p][r][c] *= 
															norm_k;
													}
												}
											}
											for (int mrec_r = 0; mrec_r < MRECs[cc][i_alpha].size(); mrec_r++)
											{
												MRECs[cc][i_alpha][mrec_r].multip_equal(norm_k);
											}
										}
										}
										else
										{
											if (iter_txt)
											{
												fprintf(iter_txt, ", ");
											}
										}
									}					
								}
								if (iter_txt)
								{
									fprintf(iter_txt, "\n");
									fclose(iter_txt);
								}
								if (to_break)
									break;
							}
						}
						break;
					}
					//а число колонок - соответствует числу светящихся столбов
					

				}



				for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
				{
					for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
					{
						Free3DMat<double>(cubes[cc][i_alpha]->grid4Section.v);
						delete cubes[cc][i_alpha];
					}
					delete cubes[cc];
				}

				delete cubes;


				for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
				{
					for (int i_alpha = 0; i_alpha < 2; i_alpha ++)
					{
						Free3DMat<double>(_cubes[cc][i_alpha]->grid4Section.v);
						delete _cubes[cc][i_alpha];
					}
					delete _cubes[cc];
				}

				delete _cubes;

			}
			break;
		case 5:
			{
				
			}
			break;
#if 0
		case 7:// iteration algorithm
			{
				bool only_init = false;
				// массив коэффициентов симметризации
				vector<vector<double> > S(3);

				bool use_newton = true;

				Lamp(use_newton,
					type, // тип прямой задачи
					cols,
					apply_dgdni,
					apply_dgdKTi,
					apply_dgdep,
					apply_B,
					names_of_colomns,
					original_col_numbers,
					this->m_files_in_dir.nFilesInDirectory,
					vX,
					vY,
					vZ,
					W,
					A,
					only_init,
					S,
					mmd3,
					DZ,
					common_directory);
			}
			break;
#endif
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		case 8:
			{
#ifdef _DEBUG
				HMODULE hGstat = LoadLibrary("gstat_d.dll");
#else
				HMODULE hGstat = LoadLibrary("gstat.dll");
#endif

					if (hGstat!=NULL)
	{

		//void __declspec(dllexport) parse_gstatrc(void);
		//int __declspec(dllexport) gstat_main(int argc, char *argv[]);
		typedef  int (MEGS1)(int, char *argv[]);
		//typedef  void (MEGS2)(void);

		MEGS1* me1=NULL;
		//MEGS2* me2=NULL;

		me1=(MEGS1*)::GetProcAddress((HMODULE)hGstat,"gstat_main");
		//me2=(MEGS2*)::GetProcAddress((HMODULE)hGstat,"parse_gstatrc");
		
		//if (me1!=NULL && me2 != NULL)
		if (me1!=NULL)
		{
		printf ("fun loaded\n");
			int argc=2;
			int result;

			typedef char* PTR_CHAR;
			char ** argv = new PTR_CHAR[argc];
#ifdef _DEBUG
			argv[0] = "gstat_d.dll";
#else
			argv[0] = "gstat.dll";
#endif
			argv[1] = "ex001.cmd";
			result=(*me1)(argc, argv);
		}
		else cout << "Error Load function" << endl;

		printf ("dll loaded\n");
		::FreeLibrary(hGstat); 
	}
	else cout << "error load Dll" << endl;

				/*char *argv[1024];
				sprintf (*argv, "ex001.cmd");
				//gstat_main(1, "ex001.cmd");
				gstat_main(1, argv);

				void parse_gstatrc(void);
				
				parse_gstatrc();*/

	HINSTANCE hModule=NULL;
	typedef  BOOL (WINAPI MESS)(UINT);
	MESS* me=NULL;
	hModule=::LoadLibrary("user32.dll");
	if (hModule!=NULL)
	{
		me=(MESS*)::GetProcAddress((HMODULE)hModule,"MessageBeep");
		if (me!=NULL)
		{
			UINT type=1;
			BOOL result;
			result=(*me)(type);
		}
		else cout << "Error Load function" << endl;
		::FreeLibrary(hModule); 
	}
	else cout << "error load Dll" << endl;


			}
			break;
#endif
			//write eas
		case 9:
			{
				/*
% write_eas : writes a GEO EAS formatted file into Matlab.
%
% Call write_eas(filename,data,header,title);
%
% filename [string]
% data [ndata,natts] 
% header [structure{natts}] : header values for data columns
% title [string] : optional title for EAS file
%
% TMH (tmh@gfy.ku.dk)
%
function write_eas(filename,data,header,line1);
  
  if nargin<1,
    help write_eas;
    return;
  end
  
  if nargin==1,
    data=filename;
    filename='dummy.eas';;
    mgstat_verbose(sprintf('%s : Filename not set, using ''%s''.',mfilename,filename),0)
  end
 
  if nargin<3,
    for i=1:size(data,2);
      header{i}=sprintf('col%d, unknown',i);
    end
  end
  
  if nargin<4,
    line1=sprintf('Data written by mGstat %s',date);
  end
  
  nd=size(data,2);
  
  fid=fopen(filename,'w');
  
  fprintf(fid,'%s\n',line1);
  fprintf(fid,'%d\n',nd);
  for ih=1:nd,
    fprintf(fid,'%s\n',header{ih});
  end
  
  if size(data,2)==1
      fprintf(fid,'%18.12g\n',data(:));
  elseif size(data,2)==2
      d=data';
      fprintf(fid,'%18.12g   %18.12g\n',d(:));
  elseif size(data,2)==3
      d=data';
      fprintf(fid,'%18.12g   %18.12g   %18.12g\n',d(:));
  elseif size(data,2)==4
      d=data';
      fprintf(fid,'%18.12g   %18.12g   %18.12g   %18.12g\n',d(:));
  elseif size(data,2)==5
      d=data';
      fprintf(fid,'%18.12g   %18.12g   %18.12g   %18.12g   %18.12g\n',d(:));
  else
      
      for id=1:size(data,1),
          %fprintf(fid,'%7.4g   %7.4g   %7.4g ',data(id,:));
          fprintf(fid,'%18.12g   %18.12g   %18.12g ',data(id,:));
          fprintf(fid,'\n');
      end
  end
  fclose(fid);
  
  
  
  return*/
  
 
				char eas_filename[4098];
				sprintf (eas_filename, "dummy.eas");

				
				char line1[1024];
				sprintf(line1, "Data written by mGstat");

				int nd = 3 + cols;



				FILE * stream = fopen(eas_filename, "wt");
				if (stream)
				{
					fprintf(stream,"%s\n",line1);
					fprintf(stream,"%d\n",nd);
					//header
					fprintf(stream,"X\n");
					fprintf(stream,"Y\n");
					fprintf(stream,"Z\n");
					for(size_t C = 0; C < cols; C++) // для каждой колонки - суть для каждого параметра
					{
						fprintf(stream, "%s\n", names_of_colomns[original_col_numbers[C]].c_str());
					}	
					size_t rows = vX.size();
					for (size_t R = 0; R < rows; R++)
					{
						fprintf(stream, "%18.12g   %18.12g   %18.12g", 
							vX[R],vY[R],vZ[R]);

						for(size_t C = 0; C < cols; C++) // для каждой колонки - суть для каждого параметра
						{
							fprintf(stream, "   %18.12g", W[C][R]);
						}	
						fprintf(stream, "\n");
					}
				}						   
			}
			break;

		case 10: //write dat
			{
				TCHAR lpstrFile[256]; lpstrFile[0] = '\0';
				
				TCHAR filter[] =    
					TEXT("Golden Software Data (*.dat)\0*.dat\0")
					TEXT("All Files (*.*)\0*.*\0");

				DWORD nFilterIndex = 0;
				if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
				{
					FILE * stream = fopen(lpstrFile, "wt");
					if (stream)
					{
						size_t rows = vX.size();
						for (size_t R = 0; R < rows; R++)
						{
							fprintf(stream, "%lf, %lf, %lf", 
								vX[R],vY[R],vZ[R]);

							for(size_t C = 0; C < cols; C++) // для каждой колонки - суть для каждого параметра
							{
								fprintf(stream, ", %lf", W[C][R]);
							}	
							fprintf(stream, "\n");
						}
					}						
				}
			}
			break;
#if 0
		case 11:// iteration algorithm
			{			
				// массив коэффициентов симметризации
				vector<vector<double> > S(3);

				bool init_by_lamp = true;
				cout << "Enter init_by_lamp" << endl;
				cin >> init_by_lamp;

				bool use_newton = true;

				if (init_by_lamp)
				{
					bool only_init = true;
					Lamp(use_newton,
						type, // тип прямой задачи
						cols,
						names_of_colomns,
						original_col_numbers,
						this->m_files_in_dir.nFilesInDirectory,
						vX,
						vY,
						vZ,
						W,
						A,
						only_init,
						S,
						mmd3,
						DZ,
						common_directory);
				}


				Dipol(use_newton,
					type, // тип прямой задачи
					cols,
					names_of_colomns,
					original_col_numbers,
					this->m_files_in_dir.nFilesInDirectory,
					vX,
					vY,
					vZ,
					W,
					A,
					init_by_lamp,
					S,
					mmd3,
					DZ,
					common_directory);
			}
			break;
		case 12:
			{
				int frec = 1;

				cout << "To get each frec? [1 2 .. 10 ... ]" << endl;
				cin >> frec;

				GetPartOfData(frec,
					vX,vY,vZ, A, vModul, W,
					pX,pY,pZ,pA, pModul,pW);	

				// массив коэффициентов симметризации
				vector<vector<double> > S(3);

				bool init_by_lamp = true;
				cout << "Enter init_by_lamp" << endl;
				cin >> init_by_lamp;

				bool use_newton = true;

				if (init_by_lamp)
				{
					bool only_init = true;

					Lamp(use_newton,
						type, // тип прямой задачи
						cols,
						names_of_colomns,
						original_col_numbers,
						this->m_files_in_dir.nFilesInDirectory,
						pX,
						pY,
						pZ,
						pW,
						pA,
						only_init,
						S,
						mmd3,
						DZ,
						common_directory);
				}


				Dipol(use_newton,
					type, // тип прямой задачи
					cols,
					names_of_colomns,
					original_col_numbers,
					this->m_files_in_dir.nFilesInDirectory,
					pX,
					pY,
					pZ,
					pW,
					pA,
					init_by_lamp,
					S,
					mmd3,
					DZ,
					common_directory);
			}
			break;
		case 13:
			{
				int frec = 1;

				cout << "To get each frec? [1 2 .. 10 ... ]" << endl;
				cin >> frec;

				GetPartOfData(frec,
					vX,vY,vZ, A, vModul, W,
					pX,pY,pZ,pA, pModul,pW);	

				bool only_init = false;
				// массив коэффициентов симметризации
				vector<vector<double> > S(3);

				bool use_newton = true;

				Lamp(use_newton,
					type, // тип прямой задачи
					cols,
					names_of_colomns,
					original_col_numbers,
					this->m_files_in_dir.nFilesInDirectory,
					pX,
					pY,
					pZ,
					pW,
					pA,
					only_init,
					S,
					mmd3,
					DZ,
					common_directory);
			}
			break;
#endif
		}
	}
	else
	{
        sprintf(common_directory_iX_iY, "%s/whole_object", common_directory, this->m_files_in_dir.nFilesInDirectory);
		if (!CreateDirectory(common_directory_iX_iY, NULL))
		{
		}

		vector<vector <double> > rec_signals;
		vector <double> rec_modul;
		UseOneOfMyMethods3W(type, 
			mmd3.granicy_kak_glubina,
			ans_OP, z0, z_min, cols,
			mmd3, w3, AutoBuildProfile::ab, vX, vY, vZ, A, vModul,W,names_of_colomns,original_col_numbers,
			rec_signals, rec_modul);
	}

#else
	if (!BuildingProfile2(vvvvkp,profile_intervals,
		consol, 
		p_auto_build_profile,
		AutoBuildProfile::ab,
		&names_of_colomns,
		original_col_numbers, 
		cols, 
		AutoBuildProfile::ab.delim, 
		directory,
		filename,
		is_reverse,
		wlen_base
		))
	{
		return false;
	}
#endif

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	Beep(200, 1000);
#endif
    MessageBox(NULL, "OK!!!", "AutoBuildProfileDlg::HandlingOfInputFiles",0);

	return true;
}

bool AutoBuildProfileDlg1::HandlingOfInputFiles()
{

	AutoBuildProfile::ab.tcols = 3;



	//int delim = ',';
	int num_col = -1;
	//##############################################################
	//блок чтения файла с нумерами колонок
	vector<bool> use_col;
	if (!ReadColomnNumbers(AutoBuildProfile::ab,use_col,num_col,AutoBuildProfile::ab.delim))
	{
		return false;
	}

    char common_directory[4096];
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
    SYSTEMTIME time;
	GetLocalTime(&time);
    sprintf(common_directory, "%s/%d-%02d-%02d_%02d_%02d_%02d", this->directory, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute,time.wSecond);
#else
    QDateTime time = QDateTime::currentDateTime();
    sprintf(common_directory, "%s/%d-%02d-%02d_%02d_%02d_%02d", this->directory, time.date().year(), time.date().month(), time.date().day(), time.time().hour(), time.time().minute(),time.time().second());
#endif
	printf("common_directory = %s\n\n",common_directory);

	if (!CreateDirectory(common_directory,NULL))
	{
		char err_str[4096];
		sprintf(err_str, "Directory \"%s\" creation failed !!!", common_directory);
		MessageBox(0, err_str, "HandlingOfInputFiles", 0);
		return false;
	}
	char common_directory_iX_iY[4096];

	//**********************************************
	//формируем файл описания режима работы
	char filename_description[4096];
    sprintf(filename_description, "%s/description1.txt", common_directory);
	FILE *stream;
	stream = fopen(filename_description,"wt");
	if (stream)
	{
		WriteDescription(stream, AutoBuildProfile::ab);
		fclose(stream);
	}
	//**********************************************

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	this->m_files_in_dir.nFilesInDirectory = SendDlgItemMessage( hDlg, IDC_LIST2, LB_GETCOUNT, 0, 0);
	//память не освобождена!!!!
	this->m_files_in_dir.vFileNameLengthes = (int *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( int ) *  this->m_files_in_dir.nFilesInDirectory);
	this->m_files_in_dir.vFileNames = (char **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( char * ) *  this->m_files_in_dir.nFilesInDirectory);
#else
    // TODO
#endif
	int cols;
	vector<string> names_of_colomns;
	vector<size_t> original_col_numbers;
	vector<vector<vector<vert_korr_points> > > vvvvkp;
	vvvvkp.clear();

	vector<profile_interval> profile_intervals;
	profile_intervals.clear();

#if USE_MY_METHOD
	vector<vector<anten_direction> > A;
	vector<vector<double> > W;
	vector<vector<vector<double> > > vW;
	vector<double> vX,vY,vZ, vModul;
#endif

	stream = fopen(filename_description,"at");
	if (stream)
	{
		fprintf(stream, "Loading files\n\n");
		fclose(stream);
	}

	//Программная реализация трёх-антенной прямой задачи требует договора о том, 
	//как производить соответствие между антеннами на самолёте и логическими 
	//антеннами AX(1,0,0), AY(0,1,0) и AZ(0,0,1).
	
	//Допустим, что прибор под именем X записывает в базу данных ту антенну, 
	//нормаль которой направлена вдоль направления полёта самолёта. Тогда условие 
	//необходимости замены обозначений антенн не возникает, если самолёт летит 
	//вдоль широты, но такая необходимость замены обозначений антенн возникает, 
	//если самолёт летит вдоль долготы. 
	
	//Если вдоль направления полёта самолёта закреплена нормаль антенны Y, 
	//тогда наоборот условие необходимости замены обозначений антенн не возникает, 
	//если самолёт летит вдоль долготы, но возникает, если самолёт летит вдоль широты. 

	int when_to_swap = 0;


	//char parallel_to_profile_antenn_normal = 'x';
	///////////////////////////////////
	//cout << "Enter normal of which antenn X or Y is parallel to profile (or to fly of airplane)" << endl;
	//cin >> parallel_to_profile_antenn_normal;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_parallel_to_profile_antenn_normal_X))
	{
		when_to_swap = 0;
	}
	else
	{
		when_to_swap = 1;
	}
#else
    // TODO
    when_to_swap = 0;
#endif


	int use_time_col = AutoBuildProfile::ab.use_time_colomn;

	vector <string> fnames;

	for (int iFile = 0; iFile < this->m_files_in_dir.nFilesInDirectory; iFile++)
	{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		this->m_files_in_dir.vFileNameLengthes[iFile] = SendDlgItemMessage( hDlg, 
			IDC_LIST2, LB_GETTEXTLEN, (WPARAM) iFile, 0)+1;
		this->m_files_in_dir.vFileNames[iFile] = (char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( char ) * this->m_files_in_dir.vFileNameLengthes[iFile]);

		if (LB_ERR!=SendDlgItemMessage( hDlg, 
			IDC_LIST2, LB_GETTEXT, (WPARAM) iFile, (LPARAM)(this->m_files_in_dir.vFileNames[iFile])))
#else
        // TODO
#endif
		{
//#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#if 1
			char sz_path_of_file[4096];
            sprintf(sz_path_of_file, "%s/%s", this->directory, this->m_files_in_dir.vFileNames[iFile]);
#else
			const char* sz_path_of_file = this->m_files_in_dir.vFileNames[iFile];
#endif
			printf("this->directory = %s\n this->m_files_in_dir.vFileNames[iFile] = %s\n sz_path_of_file = %s\n\n",this->directory,  this->m_files_in_dir.vFileNames[iFile], sz_path_of_file);

			int rows;

			char filename[256];
			vector<vector<double> > v;
			vector<vector<double> > w;

#if SOURCE_COORDINATES_3D
			vector<double> X;
			vector<double> Y;
			vector<double> Z;
#else
			vector<double> t;
#endif

			if (!ReadProfileFile( 
					sz_path_of_file, directory, filename, 
					consol, 
					p_auto_build_profile,
					AutoBuildProfile::ab,
					rows, cols,
					use_col,
					original_col_numbers,
					&names_of_colomns,
					v,
					w,
#if SOURCE_COORDINATES_3D
					X,
					Y,
					Z,
#else
					t,
#endif
					num_col,
					AutoBuildProfile::ab.delim))
			{
				return false;
			}
#if USE_MY_METHOD

			stream = fopen(filename_description,"at");
			if (stream)
			{
				fprintf(stream, "%s\n", this->m_files_in_dir.vFileNames[iFile]);
			}

			fnames.push_back(this->m_files_in_dir.vFileNames[iFile]);

			vector<double> vvv(rows, 0.0);
			
			for (size_t r = 0; r < rows; r++)
			{	
				for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
				{
					vvv[r] += v[c][r]*v[c][r];
				}
				vvv[r] = sqrt(vvv[r]);
			}

			double min__x, min__y, min__z;
			double max__x, max__y, max__z;
			double delta__x;
			double delta__y;

			GetProfileDirection(X, Y, Z,
				min__x, min__y, min__z,
				max__x, max__y, max__z,
				delta__x, delta__y);

			if (stream)
			{
				fprintf(stream, "delta__x = %f  delta__y = %f\n", delta__x, delta__y);
			}


			if (iFile == 0)
			{
				W.resize(cols);
				A.resize(3);
			}

			// отдельно будем складывать профиля
			// чтобы потом отцентрировать каждый
			vW.push_back(vector<vector<double> > () );
			vW.back().resize(cols);

			// если delta__x оказывается меньше delta__y, 
			// то есть если профиль является субмеридиональным, 
			// тогда производится автоматическая замена сигнала антенн.

			bool to_swap;
			if (when_to_swap == 0)
			{
				//Допустим, что прибор под именем X записывает в базу данных ту антенну, 
				//нормаль которой направлена вдоль направления полёта самолёта. Тогда условие 
				//необходимости замены обозначений антенн не возникает, если самолёт летит 
				//вдоль широты (delta__x > delta__y), но такая необходимость замены обозначений антенн возникает, 
				//если самолёт летит вдоль долготы (delta__x < delta__y). 
				to_swap = delta__x < delta__y;	
			}
			else 
			{
				//Если вдоль направления полёта самолёта закреплена нормаль антенны Y, 
				//тогда наоборот условие необходимости замены обозначений антенн не возникает, 
				//если самолёт летит вдоль долготы, но возникает, если самолёт летит вдоль широты. 
				to_swap = delta__x > delta__y;
			}

			if (to_swap)
			{
				if (cols >=2)
				{
					printf("swapping of parameters %s and %s on profile %s\n", 
						names_of_colomns[original_col_numbers[0]].c_str(), 
						names_of_colomns[original_col_numbers[1]].c_str(), 
						this->m_files_in_dir.vFileNames[iFile]);

					if (stream)
					{
						fprintf(stream, "меняем антены X и Y\n");
						fprintf(stream, "swapping of parameters %s and %s on profile %s\n", 
							names_of_colomns[original_col_numbers[0]].c_str(), 
							names_of_colomns[original_col_numbers[1]].c_str(), 
							this->m_files_in_dir.vFileNames[iFile]);
					}
				}

				if (cols >=5)
				{
					printf("swapping of parameters %s and %s on profile %s\n", 
						names_of_colomns[original_col_numbers[3]].c_str(), 
						names_of_colomns[original_col_numbers[4]].c_str(), 
						this->m_files_in_dir.vFileNames[iFile]);

					if (stream)
					{
						fprintf(stream, "меняем антены X2 и Y2\n");
						fprintf(stream, "swapping of parameters %s and %s on profile %s\n", 
							names_of_colomns[original_col_numbers[3]].c_str(), 
							names_of_colomns[original_col_numbers[4]].c_str(), 
							this->m_files_in_dir.vFileNames[iFile]);
					}
				}

				if (cols >=8)
				{
					printf("swapping of parameters %s and %s on profile %s\n", 
						names_of_colomns[original_col_numbers[6]].c_str(), 
						names_of_colomns[original_col_numbers[7]].c_str(), 
						this->m_files_in_dir.vFileNames[iFile]);

					if (stream)
					{
						fprintf(stream, "меняем антены X3 и Y3\n");
						fprintf(stream, "swapping of parameters %s and %s on profile %s\n", 
							names_of_colomns[original_col_numbers[6]].c_str(), 
							names_of_colomns[original_col_numbers[7]].c_str(), 
							this->m_files_in_dir.vFileNames[iFile]);
					}
				}

				
				//считаем по y
				//grid->gridSection.xLL = min__y;
				//grid->gridSection.xSize = delta_y;

				for (size_t r = 0; r < rows; r++)
				{
					anten_direction adX, adY, adZ, adV;
					if (r == 0)
					{
						adX.Init(X[r+1] - X[r], Y[r+1] - Y[r], Z[r+1] - Z[r]);
					}
					else if (r == rows - 1)
					{
						adX.Init(X[r] - X[r-1], Y[r] - Y[r-1], Z[r] - Z[r-1]);
					}
					else
					{
						adX.Init(X[r+1] - X[r-1], Y[r+1] - Y[r-1], Z[r+1] - Z[r-1]);
					}
					adX.Norm();

					adV.Init(0.0, 0.0, 1.0);

					adY.InitAsVectorProduct(adX, adV);
					adY.Norm();

					adZ.InitAsVectorProduct(adX, adY);
					adZ.Norm();
					
					if (when_to_swap == 0)
					{
						A[0].push_back(adY);
						A[1].push_back(adX);
						A[2].push_back(adZ);
					}
					else
					{
						A[0].push_back(adX);
						A[1].push_back(adY);
						A[2].push_back(adZ);
					}

					vX.push_back(X[r]);
					vY.push_back(Y[r]);
					vZ.push_back(Z[r]);
					vModul.push_back(vvv[r]);
					
					for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
					{
						size_t C = c;

						// меняем антены X и Y
						if (c == 0) C = 1;
						else if (c == 1) C = 0;

						// меняем антены X2 и Y2
						else if (c == 3) C = 4;
						else if (c == 4) C = 3;

						// меняем антены X3 и Y3
						else if (c == 6) C = 7;
						else if (c == 7) C = 6;

						W[c].push_back(v[C][r]);
						vW.back().operator [](c).push_back(v[C][r]);
					}	
				}
			}
			else
			{
				//считаем по x
				//grid->gridSection.xLL = min__x;
				//grid->gridSection.xSize = delta_x;

				for (size_t r = 0; r < rows; r++)
				{
					anten_direction adX, adY, adZ, adV;
					if (r == 0)
					{
						adX.Init(X[r+1] - X[r], Y[r+1] - Y[r], Z[r+1] - Z[r]);
					}
					else if (r == rows - 1)
					{
						adX.Init(X[r] - X[r-1], Y[r] - Y[r-1], Z[r] - Z[r-1]);
					}
					else
					{
						adX.Init(X[r+1] - X[r-1], Y[r+1] - Y[r-1], Z[r+1] - Z[r-1]);
					}
					adX.Norm();

					adV.Init(0.0, 0.0, 1.0);

					adY.InitAsVectorProduct(adX, adV);
					adY.Norm();

					adZ.InitAsVectorProduct(adX, adY);
					adZ.Norm();
					
					if (when_to_swap == 0)
					{
						A[0].push_back(adX);
						A[1].push_back(adY);
						A[2].push_back(adZ);
					}
					else
					{
						A[0].push_back(adY);
						A[1].push_back(adX);
						A[2].push_back(adZ);
					}

					vX.push_back(X[r]);
					vY.push_back(Y[r]);
					vZ.push_back(Z[r]);
					vModul.push_back(vvv[r]);

					for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
					{
						W[c].push_back(v[c][r]);
						vW.back().operator [](c).push_back(v[c][r]);
					}	
				}
			}
#else
			if (!BuildingProfile(vvvvkp,
				profile_intervals,
				consol, 
				p_auto_build_profile,
				AutoBuildProfile::ab,
				v, w, X, Y,
				&names_of_colomns, original_col_numbers, 
				rows, cols, 
				AutoBuildProfile::ab.delim, common_directory, filename,
				is_reverse, shoulder, step, wlen_auto))
			{
				return false;
			}

#endif
			
			if (stream)
			{
				fprintf(stream, "\n");
				fclose(stream);
			}
		}
        //else
        //{
        //}
	}

	// центруем сигналы по каждому профилю отдельно
	// а затем прибавляем общую среднюю

	int n_profiles = vW.size();
	vector <double> mean(cols), disp(cols);
	vector <vector <double> > profile_mean(n_profiles);
	vector <vector <double> > profile_disp(n_profiles);

	for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
	{
		mean[c] = Mean(W[c]); 
		disp[c] = Disp(W[c]); 
	}	

	for (int n_prof = 0; n_prof < n_profiles; n_prof++)
	{
		profile_mean[n_prof].resize(cols);
		profile_disp[n_prof].resize(cols);
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			profile_mean[n_prof][c] = Mean(vW[n_prof][c]); 
			profile_disp[n_prof][c] = Disp(vW[n_prof][c]); 
		}
	}

	char means_name[1024];
    sprintf(means_name, "%s/means.txt", common_directory);
	//char * p; while (p=strchr (means_name,'\"')){*p = '_';}
	FILE * means = fopen (means_name, "wt");
	if(means)
	{
		fprintf(means, "where");
		printf("where");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(means, ",mean(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
			printf(",mean(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
		}	
		fprintf(means, "\n");
		printf("\n");

		fprintf(means, "all_object");
		printf("all_object");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(means, ",%f", mean[c]);
			printf(",%f", mean[c]);
		}	
		fprintf(means, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(means, "%s", fnames[n_prof].c_str());
			printf("%s", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(means, ",%f", profile_mean[n_prof][c]);
				printf(",%f", profile_mean[n_prof][c]);
			}
			fprintf(means, "\n");
			printf("\n");
		}
		fprintf(means, "\n");
		printf("\n");
	}


	if(means)
	{
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(means, "mean(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				mean[c]);
			printf("mean(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				mean[c]);
		}	
		fprintf(means, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(means, "%s\n", fnames[n_prof].c_str());
			printf("%s\n", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(means, "mean(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_mean[n_prof][c]);
				printf("mean(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_mean[n_prof][c]);
			}
		}
		fprintf(means, "\n");
		printf("\n");

		fclose(means);

	}


	char disps_name[1024];
    sprintf(disps_name, "%s/disps.txt", common_directory);
	//char * p; while (p=strchr (disps_name,'\"')){*p = '_';}
	FILE * disps = fopen (disps_name, "wt");
	if(disps)
	{
		fprintf(disps, "where");
		printf("where");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(disps, ",disp(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
			printf(",disp(%s)", 
				names_of_colomns[original_col_numbers[c]].c_str());
		}	
		fprintf(disps, "\n");
		printf("\n");

		fprintf(disps, "all_object");
		printf("all_object");
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(disps, ",%f", disp[c]);
			printf(",%f", disp[c]);
		}	
		fprintf(disps, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(disps, "%s", fnames[n_prof].c_str());
			printf("%s", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(disps, ",%f", profile_disp[n_prof][c]);
				printf(",%f", profile_disp[n_prof][c]);
			}
			fprintf(disps, "\n");
			printf("\n");
		}
		fprintf(disps, "\n");
		printf("\n");
	}


	if(disps)
	{
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			fprintf(disps, "disp(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				disp[c]);
			printf("disp(%s) = %f\n", 
				names_of_colomns[original_col_numbers[c]].c_str(), 
				disp[c]);
		}	
		fprintf(disps, "\n");
		printf("\n");
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			fprintf(disps, "%s\n", fnames[n_prof].c_str());
			printf("%s\n", fnames[n_prof].c_str());
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				fprintf(disps, "disp(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_disp[n_prof][c]);
				printf("disp(%s) = %f\n", 
					names_of_colomns[original_col_numbers[c]].c_str(), 
					profile_disp[n_prof][c]);
			}
		}
		fprintf(disps, "\n");
		printf("\n");

		fclose(disps);

	}


    bool to_set_mean_of_profiles_to_zero = false;

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
    to_set_mean_of_profiles_to_zero = IsDlgButtonChecked( hDlg, IDC_CHECK_to_set_mean_of_profiles_to_zero) == BST_CHECKED;
	//cout << "Enter to_set_mean_of_profiles_to_zero 0 1 ?" << endl;
	//cin >> to_set_mean_of_profiles_to_zero;
#else
    // TODO
    to_set_mean_of_profiles_to_zero = false;
#endif

	


	if (to_set_mean_of_profiles_to_zero)
	{
        bool to_set_mean_value_to_profile = false;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
        to_set_mean_value_to_profile =
			IsDlgButtonChecked( hDlg, IDC_CHECK_to_set_mean_value_to_profile) == BST_CHECKED;
		//cout << "Enter to_set_mean_value_to_profile 0 1 ?" << endl;
		//cin >> to_set_mean_value_to_profile;
#else
        // TODO
        to_set_mean_value_to_profile = false;
#endif
		
		if (to_set_mean_value_to_profile)
		{
			for (int n_prof = 0; n_prof < n_profiles; n_prof++)
			{
				for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
				{
					for (int i = 0; i < vW[n_prof][c].size(); i++)
					{
						vW[n_prof][c][i] = mean[c];
					}
				}
			}
		}
		else
		{
			for (int n_prof = 0; n_prof < n_profiles; n_prof++)
			{
				for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
				{
					for (int i = 0; i < vW[n_prof][c].size(); i++)
					{
						vW[n_prof][c][i] -= profile_mean[n_prof][c];
					}
				}
			}
		}
	}
	else
	{
		for (int n_prof = 0; n_prof < n_profiles; n_prof++)
		{
			for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
			{
				for (int i = 0; i < vW[n_prof][c].size(); i++)
				{
					vW[n_prof][c][i] += mean[c] - profile_mean[n_prof][c];
				}
			}
		}	
	}



    bool to_recenter_profiles = false;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
    to_recenter_profiles =
		IsDlgButtonChecked( hDlg, IDC_CHECK_to_recenter_profiles) == BST_CHECKED;
	//cout << "Enter to_recenter_profiles 0 1 ?" << endl;
	//cin >> to_recenter_profiles;
#else
    // TODO
    to_recenter_profiles = false;
#endif

	if (to_recenter_profiles || to_set_mean_of_profiles_to_zero)
	{
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			int r = 0;
			for (int n_prof = 0; n_prof < n_profiles; n_prof++)
			{
				for (int i = 0; i < vW[n_prof][c].size(); i++)
				{
					W[c][r] = vW[n_prof][c][i];
					r++;
				}
			}
		}
	}

	
	// здесь исключить близкие точки
	// если матрица оператора прямой задачи 
	// содержит практически одинаковые строки, 
	// то это означает плохую обусловленность матрицы. 
	// Для улучшения обусловленности матрицы необходмо 
	// исключить из рассмотрения такие пары измерений, 
	// расстояние между которыми меньше, скажем половины шага измерения
	vector<double> vLen;
	for (int i = 0; i < vX.size()-1; i++)
	{
		double len = sqrt (pow(vX[i+1]-vX[i],2.0) + pow(vY[i+1]-vY[i],2.0));
		vLen.push_back(len);
	}
	std::sort(vLen.begin(), vLen.end());
	double step = vLen[vLen.size()/2];
	double limit = vLen[0];

	printf ("step = %f\n", step);
	printf ("vLen[0] = %f\n", vLen[0]);
	printf ("vLen[end] = %f\n", vLen[vLen.size()-1]);

	map<int,double> to_exclude;

	for (int i1 = 0; i1 < vX.size()-1; i1++)
	{
		for (int i2 = i1+1; i2 < vX.size()-1; i2++)
		{
			double len = sqrt (pow(vX[i1]-vX[i2],2.0) + pow(vY[i1]-vY[i2],2.0));
			if (len < limit) 
			{
				to_exclude.insert(map<int,double>::value_type(i1,len));
				to_exclude.insert(map<int,double>::value_type(i2,len));
			}
		}
	}

	/*for (map<int, int>::iterator it = to_exclude.begin();
		it != to_exclude.end(); it++)
	{
		printf ("to_exclude = %d\n", (*it).first);
	}
*/

	printf ("vX.size() = %d\n", vX.size());
	printf ("to_exclude.size() = %d\n", to_exclude.size());

	for (map<int, double>::reverse_iterator r_it = to_exclude.rbegin();
		r_it != to_exclude.rend(); r_it++)
	{
		printf ("to_exclude = %d\t%f\n", (*r_it).first, (*r_it).second);
		for(size_t c = 0; c < cols; c++) // для каждой колонки - суть для каждого параметра
		{
			vector<double>::iterator it_w_c = W[c].begin() + (*r_it).first;
			W[c].erase(it_w_c);
		}	

		vector<double>::iterator it_vx = vX.begin() + (*r_it).first;
		vX.erase(it_vx);

		vector<double>::iterator it_vy = vY.begin() + (*r_it).first;
		vY.erase(it_vy);

		vector<double>::iterator it_vz = vZ.begin() + (*r_it).first;
		vZ.erase(it_vz);
	}
	printf ("vX.size() = %d\n", vX.size());

	MyMethodsData3 mmd3;
	mmd3.to_povorot = false;
	mmd3.need_crd_projection = false;

	if (n_profiles == 1)
	{
		//cout << "Enter Do you need coordinate preobrazovanie" << endl;
		//cin >> mmd3.to_povorot;
        mmd3.to_povorot = true;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
        mmd3.to_povorot =
			IsDlgButtonChecked( hDlg, IDC_CHECK_to_povorot) == BST_CHECKED;
#else
        // TODO
        mmd3.to_povorot = true;
#endif

		if (mmd3.to_povorot)
		{	
			//cout << "Enter Do you need coordinate projection output?" << endl << 
			//	"(1 - yes, 0 - output will be in profile length)" << endl;
			//cin >> mmd3.need_crd_projection;
            mmd3.need_crd_projection = true;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
            mmd3.need_crd_projection =
				IsDlgButtonChecked( hDlg, IDC_CHECK_need_crd_projection) == BST_CHECKED;
#else
            // TODO
            mmd3.need_crd_projection = true;
#endif



			//ищем уравнение прямой в виде
			// ax+by+c=0

			// определяем профиль является субширотным или субмериодиональным
			double profile_dx = fabs(vX[0] - vX.back());
			double profile_dy = fabs(vY[0] - vY.back());

			if (profile_dx > profile_dy)
			{
				//субширотный
				//ищем уравнение прямой в виде
				//y=Ax+B, где A=-a/b B=-c/b b!=0

				double xy = ScalarProduct(vX, vY);
				double xx = SquareSum(vX);
				double sx = Sum(vX);
				double sy = Sum(vY);
				double n = vX.size();

				double D = n*xx-sx*sx;
				double DA = n*xy-sy*sx;
				double DB = xx*sy-sx*xy;

				double A = DA/D;
				double B = DB/D;

				double b = 1.0, a = -A, c = -B;

				printf ("A = %f B = %f\n", A,B);
				printf ("a = %f b = %f c = %f\n", a,b,c);

				mmd3.ugol = atan(A);
				printf("ugol = %f %f\n", mmd3.ugol, mmd3.ugol/PI*180);
			}
			else
			{
				//субмериодиональный
				//ищем уравнение прямой в виде
				//x=Ay+B, где A=-b/a B=-c/a a!=0

				double xy = ScalarProduct(vX, vY);
				double yy = SquareSum(vY);
				double sx = Sum(vX);
				double sy = Sum(vY);
				double n = vX.size();

				double D = n*yy-sy*sy;
				double DA = n*xy-sy*sx;
				double DB = yy*sx-sy*xy;

				double A = DA/D;
				double B = DB/D;

				double a = 1.0, b = -A, c = -B;
				printf ("A = %f B = %f\n", A,B);
				printf ("a = %f b = %f c = %f\n", a,b,c);

				mmd3.ugol = -atan(A);
				printf("ugol = %f %f\n", mmd3.ugol, mmd3.ugol/PI*180);
			}

			mmd3.ugol*=-1.0;


			if (profile_dx > profile_dy)
			{
				printf("subshirotny\n");
				//субширотный
				//уравнение прямой в виде
				//y=Ax+B, где A=-a/b B=-c/b b!=0

				//ищем начальную точку в как ту у которой минимальный икс
				vector<double>::iterator it_min_vx = min_element(vX.begin(), vX.end());
				if (it_min_vx != vX.end())
				{
					mmd3.vX0 = *it_min_vx;
					unsigned long shift = &(*it_min_vx) - &(*vX.begin());
					cout << "shift " << shift << endl;
					mmd3.vY0 = *((double *)(&(*vY.begin()) + shift));
					printf ("vY0 = %f", mmd3.vY0);
				}
			}
			else
			{
				//субмериодиональный
				//уравнение прямой в виде
				//x=Ay+B, где A=-b/a B=-c/a a!=0

				//ищем начальную точку в как ту у которой минимальный игрек
				vector<double>::iterator it_min_vy = min_element(vY.begin(), vY.end());
				if (it_min_vy != vY.end())
				{
					mmd3.vY0 = *it_min_vy;
					unsigned long shift = &(*it_min_vy) - &(*vY.begin());
					cout << "shift = " << shift << endl;
					mmd3.vX0 = *((double *)(&(*vX.begin()) + shift));
					printf ("vX0 = %f", mmd3.vX0);
				}
			}

			char bln_name[1024];

            sprintf(bln_name, "%s/new_XY.bln", common_directory);
			//char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
			FILE * bln = fopen (bln_name, "wt");
			if(bln)
			{
				fprintf(bln, "%d,%d, new_XY\n", vX.size(), 0);
			}

			for (int i = 0; i < vX.size(); i++)
			{
				double x_new = (vX[i] - mmd3.vX0)*cos(mmd3.ugol) - (vY[i] - mmd3.vY0)*sin(mmd3.ugol);
				double y_new = (vX[i] - mmd3.vX0)*sin(mmd3.ugol) + (vY[i] - mmd3.vY0)*cos(mmd3.ugol);

				vX[i] = x_new;
				vY[i] = y_new;

				if (true)
				{
					if (profile_dx > profile_dy)
					{
						vY[i] = 0.0;
					}
					else
					{
						vX[i] = 0.0;
					}
				}
				
				if(bln)
				{				
					fprintf(bln, "%f,%f\n", vX[i], vY[i]);
				}
			}
			if(bln)
			{
				fclose(bln);
			}
		}
	}
	
	sprintf(dir_out, "%s\0", common_directory);
				
	int type = 0; // тип прямой задачи
	//cout << "Enter type of prjamoj zadachi" << endl;
	//cout << "0 - simple" << endl;
	//cout << "1 - with diagramm of 3 antenns and nonpolarized sources" << endl;
	//cout << "2 - --//-- and with assumption that tg delta much more than one" << endl;
	//cin >> type;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	if (IsDlgButtonChecked(hDlg, IDC_RADIO_TYPE_1) == BST_CHECKED)
		type = 1;
	else 
		type = 2;
#else
    // TODO
    type = 1;
#endif

	double z0 = 0.0, z_min = 0.0, DZ = 0.0;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	char str[128];
	GetDlgItemText(this->hDlg, IDC_EDIT_Altitude_z0, str, 127);
	z0 = atof(str);
	cout << "z0 = " << z0 << " m" << endl;

	GetDlgItemText(this->hDlg, IDC_EDIT_Altitude_z_min, str, 127);
	z_min = atof(str);
	cout << "z_min = " << z_min << " m" << endl;
#else
    // TODO
    z0   = 130;
    z_min = -2870;
#endif

	DZ = z0 - z_min;
	cout << "DZ = " << DZ << " m" << endl;

	
	double inv_k_oslablenie;	

//	if (ans_OP == IDYES)
//	{
		// enter parameters
//		mmd3.increaser_pw = 2;

//		cout << "Do you want reenter increaser_pw = " << mmd3.increaser_pw << "?\n";

//		char answer;
//		cin >> answer;
//		if (answer == 'y' || answer == 'Y')
//		{
//			cout << "increaser_pw?\n";
//			cin >> mmd3.increaser_pw;
//		}
		
		// отношение строк и столбцов	
//		mmd3.pw_pcd = 2;
//		cout << "pw_pcd pages/cols deviation pw = " << mmd3.pw_pcd << "\n";
//		cout << "Do you want reenter pw_pcd pages/cols deviation pw (0,1,2,...)?\n";
//		cin >> answer;
//		if (answer == 'y' || answer == 'Y')
//		{
//			cout << "Enter pw_pcd pages/cols deviation pw?\n";
//			cin >> mmd3.pw_pcd;
//		}

		//////////////////////////////////
//#if 1
		mmd3.z0 = z0;
		mmd3.z_min = z_min;
//#else
//		cout << "Enter Altitude z0, (m)" << endl;
//		cin >> mmd3.z0;
//		cout << "z0 = " << mmd3.z0 << " m" << endl;
//
//		cout << "Enter Altitude z_min, (m)" << endl;
//		cin >> mmd3.z_min;
//		cout << "z_min = " << mmd3.z_min << " m" << endl;
//#endif
		mmd3.k_oslablenie = 0.0; inv_k_oslablenie = 0.0;
		if (type == 0 || type == 1)
		{
		}
		else if (type == 2)
		{
			cout << "Enter noise color: 1 blue, 2 blue-white 3 white 4 pink-white" << endl;
			cin >> mmd3.noise_color;
			cout << "Enter nju_min Hz" << endl;
			cin >> mmd3.nju_min;
			cout << "Enter nju_max Hz" << endl;
			cin >> mmd3.nju_max;
		}
		//cout << "Enter wave_type 0 - plane wave 1 - spherical wave" << endl;
		//cin >> mmd3.wave_type;
		mmd3.wave_type = 1;

		//cout << "Enter pw_dnp - power or diargamm napravlennosty priyomnika (2 recommended)" << endl;
		//cin >> mmd3.pw_dnp;
		mmd3.pw_dnp = 2;

		//cout << "Enter min_value (small positive, for example from 1e-16 to 0.03)" << endl;
		//cin >> mmd3.min_value;
		mmd3.min_value = 0.0;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		//cout << "Enter dx/DZ=dy/DZ (for example 2)" << endl;
		//cin >> mmd3.dx_and_dy_per_DZ;
		GetDlgItemText(this->hDlg, IDC_EDIT_dx_and_dy_per_DZ, str, 127);
        mmd3.dx_and_dy_per_DZ = atof(str);
#else
        // TODO
        mmd3.dx_and_dy_per_DZ = 2.0;
#endif

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		//cout << "Enter granicy_kak_glubina?  0 - no 1 - yes" << endl;
		mmd3.granicy_kak_glubina = IsDlgButtonChecked(hDlg, IDC_CHECK_granicy_kak_glubina) == BST_CHECKED;
#else
        mmd3.granicy_kak_glubina = false;
#endif


// here calculi operator  by mean[c]
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		//cout << "Enter rows" << endl;
		//cin >> mmd3.rows;
		GetDlgItemText(this->hDlg, IDC_EDIT_ROWS, str, 127);
		mmd3.rows = atoi(str);

		//cout << "Enter cols" << endl;
		//cin >> mmd3.cols;
		GetDlgItemText(this->hDlg, IDC_EDIT_COLS, str, 127);
		mmd3.cols = atoi(str);

		//cout << "Enter pages" << endl;
		//cin >> mmd3.pages;
		GetDlgItemText(this->hDlg, IDC_EDIT_PAGES, str, 127);
		mmd3.pages = atoi(str);

		//cout << "Enter iter_save" << endl;
		//cin >> mmd3.iter_save;
		GetDlgItemText(this->hDlg, IDC_EDIT_ITER_SAVE, str, 127);
		mmd3.iter_save = atoi(str);
#else
        mmd3.rows = 30;
        mmd3.cols = 30;
        mmd3.pages = 30;
        mmd3.iter_save = 100;
#endif

		//cout << "Parameters of power distribution model (w0 w05 w1 w2)" << endl;
		//cout << "number means W ~ w0*h^0 + w05*h^0.5 + w1*h^1 + w2*h^2" << endl;
		//cout << "recomended w0 = 1 w05 = 0 w1 = 0 w2 = 0" << endl;
		//cout << "Enter w0" << endl;
		//cin >> mmd3.spm.w0;
		mmd3.spm.w0 = 1.0;

		//cout << "Enter w05" << endl;
		//cin >> mmd3.spm.w05;
		mmd3.spm.w05 = 0.0;

		//cout << "Enter w1" << endl;
		//cin >> mmd3.spm.w1;
		mmd3.spm.w1 = 0.0;

		//cout << "Enter w2" << endl;
		//cin >> mmd3.spm.w2;
		mmd3.spm.w2 = 0.0;



		if (type == 0 || type == 1)
		{
		#if 1
			mmd3.k_oslablenie = 0.0;
			//cout << "Enter k_oslablenie (po naprjazhonnosti polja, for example 0.00023025 -> 1.999 dB/km by power), (m^-1)" << endl;
			//cin >> mmd3.k_oslablenie;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
			GetDlgItemText(this->hDlg, IDC_EDIT_k_oslablenie, str, 127);
			mmd3.k_oslablenie = atof(str);
#else
            // TODO
            mmd3.k_oslablenie = 0.00023025;
#endif
			inv_k_oslablenie = 1.0 / mmd3.k_oslablenie;
		#else
			inv_k_oslablenie = 100;
			cout << "Enter inv_k_oslablenie, m" << endl;
			cin >> inv_k_oslablenie;
			mmd3.k_oslablenie = 1.0 / inv_k_oslablenie;
		#endif
			cout << "inv_k_oslablenie = " << inv_k_oslablenie << " m" << endl;
			cout << "k_oslablenie (po polju) = " << mmd3.k_oslablenie << " m^-1" << endl;
			cout << "k_oslablenie (po moschnosti) = " << mmd3.k_oslablenie * mmd3.pw_dnp   << " m^-1" << endl;
			
			cout << "k_oslablenie (po polju) = " << 1000. * mmd3.k_oslablenie / (0.1 * log(10.)) << " dB/km" << endl;
			cout << "k_oslablenie (po moschnosti) = " << 1000. * mmd3.k_oslablenie * mmd3.pw_dnp / (0.1 * log(10.)) << " dB/km" << endl;
			
		}
		else if (type == 2)
		{
			cout << "Enter ro Om*m" << endl;
			cin >> mmd3.ro;
		}

		


		// save parameters
//		char filename_parameters[4096];
//		sprintf(filename_parameters, "%s/parameters.par3", dir_out);
//		SaveParameters (filename_parameters, mmd3);


	//**********************************************
	//формируем файл описания режима работы
//	char filename_description[4096];
    sprintf(filename_description, "%s/description.txt", dir_out);
	FILE * description = fopen(filename_description,"wt");

	//**********************************************

	if (description)
	{
		fprintf(description, "Altitude z0 = %f m\n", mmd3.z0);
		fprintf(description, "Altitude z_min = %f m\n", mmd3.z_min);
		fprintf(description, "inv_k_oslablenie = %f m\n", inv_k_oslablenie);
		fprintf(description, "k_oslablenie = %f m^-1\n", mmd3.k_oslablenie);
		//fprintf(description, "ab.k = %f\n", ab.k);
		fprintf(description, "have_pereopredelen_system = %d\n", mmd3.have_pereopredelen_system);

		fprintf(description, "\n");
		fprintf(description, "noise_color = %d\n", mmd3.noise_color);
		switch (mmd3.noise_color)
		{
		case 1://blue
			{
				fprintf(description, "noise_color = blue\n");
			}
			break;
		case 2://blue-white
			{
				fprintf(description, "noise_color = blue-white\n");
			}
			break;
		case 3://white
			{
				fprintf(description, "noise_color = white\n");
			}
			break;
		case 4://pink-white
			{
				fprintf(description, "noise_color = pink-white\n");
			}
			break;
		}
		fprintf(description, "ro = %f\n", mmd3.ro);
		fprintf(description, "nju_min = %f\n", mmd3.nju_min);
		fprintf(description, "nju_max = %f\n\n", mmd3.nju_max);

		fprintf(description, "pw_dnp = %f\n", mmd3.pw_dnp);
		fprintf(description, "min_value = %e\n\n", mmd3.min_value);

		fprintf(description, "dx_and_dy_per_DZ = %f\n", mmd3.dx_and_dy_per_DZ);
		fprintf(description, "granicy_kak_glubina = %d\n", mmd3.granicy_kak_glubina);

		fprintf(description, "rows = %d\n", mmd3.rows);
		fprintf(description, "cols = %d\n", mmd3.cols);
		fprintf(description, "pages = %d\n", mmd3.pages);

		fprintf(description, "w0 = %f\n", mmd3.spm.w0);
		fprintf(description, "w05 = %f\n", mmd3.spm.w05);
		fprintf(description, "w1 = %f\n", mmd3.spm.w1);
		fprintf(description, "w2 = %f\n", mmd3.spm.w2);



		


		fprintf(description, "wave_type = %d\n", mmd3.wave_type);

		switch (mmd3.wave_type)
		{
		case 0:
			{
				fprintf(description, "wave_type = plane\n");
			}
			break;
		case 1:
			{
				fprintf(description, "wave_type = spherical\n");
			}
			break;
		}
		fclose(description);
	}

//	cout << "Enter j_start > 0 - if previous calculations of Holesski were broken" << endl;
//	cout << "Else Enter j_start = 0" << endl;
//	cin >> mmd3.j_start;
//}

	bool lamp = true;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	if (IsDlgButtonChecked(hDlg, IDC_RADIO_LAMP) == BST_CHECKED)
		lamp = true;
	else 
		lamp = false;
#else
    // TODO
    lamp = false;
#endif

	//тестируем на уменьшенной площади
	vector<double> pX, pY, pZ, pModul;
	vector<vector<anten_direction> > pA;
	vector<vector<double> > pW;

    bool to_frec = false;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
    to_frec = IsDlgButtonChecked(hDlg, IDC_CHECK_FREC) == BST_CHECKED;
#else
    // TODO
    to_frec = false;
#endif

    int use_newton = 0;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	if (IsDlgButtonChecked(hDlg, IDC_RADIO_SPUSK) == BST_CHECKED) 
	{
		use_newton = 0;
	}
	if (IsDlgButtonChecked(hDlg, IDC_RADIO_NEWTON) == BST_CHECKED) 
	{
		use_newton = 1;
	}
	if (IsDlgButtonChecked(hDlg, IDC_RADIO_NEWTON_MODIFIED) == BST_CHECKED) 
	{
		use_newton = 2;
	}
#else
    // TODO
    use_newton = 1;
#endif

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	bool apply_dgdni = IsDlgButtonChecked(hDlg, IDC_CHECK_apply_dgdni) == BST_CHECKED;	   
	bool apply_dgdKTi = IsDlgButtonChecked(hDlg, IDC_CHECK_apply_dgdKTi) == BST_CHECKED;
	bool apply_dgdep = IsDlgButtonChecked(hDlg, IDC_CHECK_apply_dgdep) == BST_CHECKED;
	bool apply_dgdbeta = IsDlgButtonChecked(hDlg, IDC_CHECK_apply_dgdbeta) == BST_CHECKED;
	bool apply_dgdomega = IsDlgButtonChecked(hDlg, IDC_CHECK_apply_dgdomega) == BST_CHECKED;
	bool apply_B = IsDlgButtonChecked(hDlg, IDC_CHECK_apply_B) == BST_CHECKED;
#else
    // TODO
    bool apply_dgdni    = true;
    bool apply_dgdKTi   = true;
    bool apply_dgdep    = false;
    bool apply_dgdbeta  = true;
    bool apply_dgdomega = false;
    bool apply_B        = false;
#endif

	if (lamp)
	{
		if (to_frec)
		{
			int frec = 1;

			//cout << "To get each frec? [1 2 .. 10 ... ]" << endl;
			//cin >> frec;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
			GetDlgItemText(this->hDlg, IDC_EDIT_frec, str, 127);
			frec = atoi(str);
#else
            // TODO
            frec = 8;
#endif

			GetPartOfData(frec,
				vX,vY,vZ, A, vModul, W,
				pX,pY,pZ,pA, pModul,pW);	

			bool only_init = false;
			// массив коэффициентов симметризации
			vector<vector<double> > S(3);

			Lamp(use_newton,
				type, // тип прямой задачи
				cols,
				apply_dgdni,
				apply_dgdKTi,
				apply_dgdep,
				apply_B,
				names_of_colomns,
				original_col_numbers,
				this->m_files_in_dir.nFilesInDirectory,
				pX,
				pY,
				pZ,
				pW,
				pA,
				only_init,
				S,
				mmd3,
				DZ,
				common_directory);
		}
		else
		{
			bool only_init = false;
			// массив коэффициентов симметризации
			vector<vector<double> > S(3);

			Lamp(use_newton,
				type, // тип прямой задачи
				cols,
				apply_dgdni,
				apply_dgdKTi,
				apply_dgdep,
				apply_B,
				names_of_colomns,
				original_col_numbers,
				this->m_files_in_dir.nFilesInDirectory,
				vX,
				vY,
				vZ,
				W,
				A,
				only_init,
				S,
				mmd3,
				DZ,
				common_directory);
		}
	}
	else
	{
		if (to_frec)
		{
			int frec = 1;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
			//cout << "To get each frec? [1 2 .. 10 ... ]" << endl;
			//cin >> frec;
			GetDlgItemText(this->hDlg, IDC_EDIT_frec, str, 127);
			frec = atoi(str);
#else
            // TODO
            frec = 8;
#endif
			GetPartOfData(frec,
				vX,vY,vZ, A, vModul, W,
				pX,pY,pZ,pA, pModul,pW);	

			// массив коэффициентов симметризации
			vector<vector<double> > S(3);
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
			bool init_by_lamp = IsDlgButtonChecked(hDlg, IDC_CHECK_TO_INIT_BY_LAMP) == BST_CHECKED;
			//cout << "Enter init_by_lamp" << endl;
			//cin >> init_by_lamp;
#else
            // TODO
            bool init_by_lamp = false;
#endif

			

			if (init_by_lamp)
			{
				bool only_init = true;

				Lamp(use_newton,
					type, // тип прямой задачи
					cols,
					apply_dgdni,
					apply_dgdKTi,
					apply_dgdep,
					apply_B,
					names_of_colomns,
					original_col_numbers,
					this->m_files_in_dir.nFilesInDirectory,
					pX,
					pY,
					pZ,
					pW,
					pA,
					only_init,
					S,
					mmd3,
					DZ,
					common_directory);
			}


			Dipol(use_newton,
				type, // тип прямой задачи
				cols,

				apply_dgdni,
				apply_dgdKTi,
				apply_dgdep,
				apply_dgdbeta,
				apply_dgdomega,
				apply_B,

				names_of_colomns,
				original_col_numbers,
				this->m_files_in_dir.nFilesInDirectory,
				pX,
				pY,
				pZ,
				pW,
				pA,
				init_by_lamp,
				S,
				mmd3,
				DZ,
				common_directory);
		}
		else
		{
			// массив коэффициентов симметризации
			vector<vector<double> > S(3);
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
			bool init_by_lamp = IsDlgButtonChecked(hDlg, IDC_CHECK_TO_INIT_BY_LAMP) == BST_CHECKED;
#else
            // TODO
            bool init_by_lamp = false;
#endif

			if (init_by_lamp)
			{
				bool only_init = true;
				Lamp(use_newton,
					type, // тип прямой задачи
					cols,
					apply_dgdni,
					apply_dgdKTi,
					apply_dgdep,
					apply_B,
					names_of_colomns,
					original_col_numbers,
					this->m_files_in_dir.nFilesInDirectory,
					vX,
					vY,
					vZ,
					W,
					A,
					only_init,
					S,
					mmd3,
					DZ,
					common_directory);
			}


			Dipol(use_newton,
				type, // тип прямой задачи
				cols,
				apply_dgdni,
				apply_dgdKTi,
				apply_dgdep,
				apply_dgdbeta,
				apply_dgdomega,
				apply_B,
				names_of_colomns,
				original_col_numbers,
				this->m_files_in_dir.nFilesInDirectory,
				vX,
				vY,
				vZ,
				W,
				A,
				init_by_lamp,
				S,
				mmd3,
				DZ,
				common_directory);
		}
	}


#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	Beep(200, 1000);
#endif
    MessageBox(NULL, "OK!!!", "AutoBuildProfileDlg::HandlingOfInputFiles",0);

	return true;
}

bool Dipol(int use_newton,
		   int type, // тип прямой задачи
		   long cols,
		   bool apply_dgdni,		   
		   bool apply_dgdKTi,
		   bool apply_dgdep,
		   bool apply_dgdbeta,
		   bool apply_dgdomega,
		   bool apply_B,
		   vector<string> &names_of_colomns,
		   vector<size_t> &original_col_numbers,
		   int nFilesInDirectory,
		   vector<double> &vX,
		   vector<double> &vY,
		   vector<double> &vZ,
		   vector<vector<double> > &W,
		   vector<vector<anten_direction> > & A,
		   bool init_by_lamp,
		   // массив коэффициентов симметризации
		   vector<vector<double> > & S,
		   MyMethodsData3 &mmd3,
		   double DZ,
		   char * common_directory)
{
#ifdef QT_DEBUG
    //apply_B = true;
#endif
#if 1
    //sprintf(common_directory_iX_iY, "%s/whole_object_by_colomns", common_directory);
	//if (!CreateDirectory(common_directory_iX_iY, NULL))
	//{
	//}

	double min_X, max_X, min_Y, max_Y;				
	GetMinMaxXYOfData(vX, vY, min_X, max_X, min_Y, max_Y);

	double 
		DX = max_X - min_X, 
		DY = max_Y - min_Y; 



/*
	cout << "apply_dgdni" << endl;
	cin >> apply_dgdni;
	cout << "apply_dgdep" << endl;
	cin >> apply_dgdep;
	cout << "apply_dgdbeta" << endl;
	cin >> apply_dgdbeta;
	cout << "apply_dgdomega" << endl;
	cin >> apply_dgdomega;
*/


	double dx = DZ * mmd3.dx_and_dy_per_DZ;
	double dy = DZ * mmd3.dx_and_dy_per_DZ;


	mmd3.delta__x = DX - dx * int (mmd3.granicy_kak_glubina);
	mmd3.delta__y = DY - dy * int (mmd3.granicy_kak_glubina);
	mmd3.delta__z = mmd3.z0 - mmd3.z_min;


	// на случай редукции к двумерному случаю
	bool to_reduce_x = (DX - dx) < 0.0;
	bool to_reduce_y = (DY - dy) < 0.0;

	if (nFilesInDirectory == 1)
	{
		if (DX < DY)
		{
			to_reduce_x = true;
			to_reduce_y = false;
		}
		else
		{
			to_reduce_x = false;
			to_reduce_y = true;
		}
	}
	else
	{
		to_reduce_x = false;
		to_reduce_y = false;
	}


	if (to_reduce_x && to_reduce_y)
	{
		char err_str[2048];
		sprintf(err_str, 
			"to_reduce_x && to_reduce_y\n"
			"DX = %f DY = %f DZ = %f\n"
			"mmd3.dx_and_dy_per_DZ = %f\n"
			"dx = dy = %f"
			"nFilesInDirectory = %d"
			,
			DX, DY, DZ, 
			mmd3.dx_and_dy_per_DZ,
			dx,
			nFilesInDirectory);
		MessageBox(NULL, err_str, "Error", MB_OK);
		return false;
	}

	if (to_reduce_x) {mmd3.cols = 1; mmd3.delta__x = 0.0;}
	if (to_reduce_y) {mmd3.rows = 1; mmd3.delta__y = 0.0;}


	mmd3.x0 = to_reduce_x ? (min_X+max_X)/2.0 : min_X + 0.5 * dx * int (mmd3.granicy_kak_glubina);
	mmd3.y0 = to_reduce_y ? (min_Y+max_Y)/2.0 : min_Y + 0.5 * dy * int (mmd3.granicy_kak_glubina);

	mmd3.delta_x = to_reduce_x ? 0.0 : mmd3.delta__x / (mmd3.cols - 1);
	mmd3.delta_y = to_reduce_y ? 0.0 : mmd3.delta__y / (mmd3.rows - 1);



	vector<string> new_names_of_colomns;
	int cols_3 = cols / 3;//2
	new_names_of_colomns.resize(cols_3);

	//mmd3.delta_z = mmd3.delta__z / (mmd3.pages - 1);// это неверно!!!
	// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
	mmd3.delta_z = mmd3.delta__z / mmd3.pages;


	double *** R;// rx,ry,rz

	double *** m;// три матрицы njuXr, njuYr, njuZr
	printf("Filling of matrix\n");
	// формируем матрицу оператора прямой задачи, 
	// число строк равно длине сигнала 
	// (или суммарной длине нескольких сигналов - 
	// нескольких профилей на одной или, ещё лучше, на разных высотах)
	// на вход оператора подаётся геологическая структура 
	// источников геополяритонного сигнала
	// на выходе оператора имеем мощность излучения (сигнал) на профилях

	if (type == 1)
	{
		FillingTheMatrix3D_with_napravlennosty_diagramm_dipol(
			mmd3.k_oslablenie, 
			&m, &R,
			mmd3.rows, mmd3.cols, mmd3.pages,
			mmd3.x0, mmd3.y0, mmd3.z0,
			mmd3.delta_x, mmd3.delta_y, mmd3.delta_z,
			vX, vY, vZ, A,
			mmd3.pw_dnp,
			mmd3.min_value,
			mmd3.wave_type, 
			mmd3.spm);
	}
	else
	{
		MessageBox(NULL, "type should be 1", "Error", MB_OK);
		return false;
	}

	/*Grid4 * cube = ShowCube(mmd);
	char fn[1024]; 
    sprintf(fn, "%s/cube.cub",
		dir_out);
	SaveAsSurfer7Grid4(fn, cube);*/

	double *** p_A;
	double *** W_p_A;

    double *** p_B = NULL;
    double *** W_p_B = NULL;

	long signal_len = vX.size(); // длина сигнала 
	long operator_rows = signal_len; // длина сигнала 
	long operator_cols = mmd3.rows * mmd3.cols * mmd3.pages;

	p_A = Alloc3DMat<double>(3, operator_rows, operator_cols);
	W_p_A = Alloc3DMat<double>(3, operator_rows, operator_cols);

    if (apply_B){
        p_B = Alloc3DMat<double>(3, operator_rows, operator_cols);
        W_p_B = Alloc3DMat<double>(3, operator_rows, operator_cols);
    }


	double max_m = -DBL_MAX;
	double min_m = DBL_MAX;

	double max_Ep = -DBL_MAX;
	double min_Ep = DBL_MAX;

	vector<double> vmax_m(operator_cols, -DBL_MAX);
	vector<double> vmin_m(operator_cols, DBL_MAX);
	double mean_m = 0.0;

	short a, ia;  vector<short> va;
	va.push_back(0);//x
	va.push_back(1);//y
	va.push_back(2);//z
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	//for (int a = 0; a < 3; a++)// перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			double _Ep = W[a+6][r];
			if (max_Ep < _Ep) max_Ep = _Ep;
			if (min_Ep > _Ep) min_Ep = _Ep;
			for (long c = 0; c < operator_cols; c++)
			{
				double _m = m[a][r][c];
				if (_m > DBL_MIN)
				{
					if (max_m < _m)
						max_m = _m;
				
					if (min_m > _m)
						min_m = _m;

					if (vmax_m[c] < _m)
						vmax_m[c] = _m;
				
					if (vmin_m[c] > _m)
						vmin_m[c] = _m;

					mean_m += _m;
				}
			}
		}
	}
	double zero_substitution = 0.9 * min_m;
	printf("zero_substitution = %e\n", zero_substitution);
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			for (long c = 0; c < operator_cols; c++)
			{
				double & _m = m[a][r][c];
				if (_m <= DBL_MIN)
				{
					_m = zero_substitution;
					mean_m += _m;
				}
			}
		}
	}

	mean_m /= va.size() * operator_rows * operator_cols;
    printf("mean_m = %e\n", mean_m);

	double max_b = -DBL_MAX;
	double min_b = DBL_MAX;


	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			double _b = W[a][r];//режим А
			if (max_b < _b)
				max_b = _b;
			if (min_b > _b)
				min_b = _b;
		}
	}

	// считаем коэффициенты корреляции между оператором прямой задачи 
	// и сигналом
	vector<double> k_corr(operator_cols, 0.0);
	vector<double> k_cov(operator_cols, 0.0);
	for (long c = 0; c < operator_cols; c++) //длина геологической структуры
	{
		vector<double> v_m(operator_rows * va.size());
		vector<double> v_s(operator_rows * va.size());

		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
			for (long r = 0; r < operator_rows; r++) // длина сигнала по одной антене
			{
				double _m = m[a][r][c];
				double _signal = W[a][r];

				v_m[operator_rows * ia + r] = _m;
				v_s[operator_rows * ia + r] = _signal;
			}
		}
		//рассчитываем коэффициент корреляции k_corr[c] для текущего элемента геологической структуры;
		double k, Cov;
		if (CorrelationCoefficient(v_s, v_m, k, Cov))
		{
			k_corr[c] = k;
			k_cov[c] = Cov;
		}
	}

	// инициализируем векторы решения
	double Ep[3] = {1.0, 1.0, 1.0};
	double k[3] = {1.0, 1.0, 1.0};
	double s[3] = {1.0, 1.0, 1.0};
//				double init_KT = 0.2 / min_m;  //эта иициализация к значению init_KT = 10e+16 причём KT не подстраивается за обозримое количество итераций
	//double init_KT = 0.2 / mean_m; эта инициализация привела к тому что суммарный выход оператора прямой задачи стал равен нулю но тут могла быть ошибка так как в mean_m вместо вреднего вычислялась сумма, что вело к значительному занижению значения init_KT
	//double init_KT = 0.2; // слишком мала "температура" -> суммарный выход оператора прямой задачи стал равен нулю
	double init_KT = 0.2*1e6;
	//init_KT = 0.2 / mean_m;
	init_KT = 10.0 / max_m;// это значит, что минимальный р будет равен 0.1
	vector<double> KTi_A(operator_cols, init_KT);
    vector<double> KTi_B;
    if (apply_B){
        KTi_B.resize(operator_cols, init_KT);
    }
	if (false)
	{
		// эта инициализация "копирует" рельефные и краевые эффекты оператора прямой задачи
		for (long c = 0; c < operator_cols; c++) KTi_A[c] = 0.2 / vmin_m[c];
	}
		
	// эта инициализация равномерна по глубине, т.к. использует макс. m, который 
	// для каждой геоточки соответсвует направлению вертикально вверх
	// кроме того это означает, что минимальный р равен 0.1
	
	// mode_A
	for (long c = 0; c < operator_cols; c++) KTi_A[c] = 10.0 / vmax_m[c];
	// mode_B
    if (apply_B){
	for (long c = 0; c < operator_cols; c++) KTi_B[c] = 10.0 * min_Ep / vmax_m[c];
    }


	//beta и omega – углы в сферической системе координат, дающие ориентацию излучающего диполя в пространстве
	//beta - отклонение вектора диполя от вертикали
	//omega - азимут наклона диполя (угол между направлением на север и направлением диполя, отсчитываемый по часовой стрелке)

    printf("before init\n");

	vector<double> beta_A(operator_cols, 0.0);
    vector<double> beta_B;

	vector<double> omega_A(operator_cols, 0.0);
    vector<double> omega_B;
    if (apply_B){
        beta_B.resize(operator_cols, 0.0);
        omega_B.resize(operator_cols, 0.0);
    }

	//случайная инициализация
	for (long c = 0; c < operator_cols; c++)
	{
		beta_A[c] = 0.5 * PI * ((double)rand()/(double)RAND_MAX);
        omega_A[c] = 2.0 * PI * ((double)rand()/(double)RAND_MAX);
        if (apply_B){
		beta_B[c] = 0.5 * PI * ((double)rand()/(double)RAND_MAX);
		omega_B[c] = 2.0 * PI * ((double)rand()/(double)RAND_MAX);
        }
	}
#if 1
	//послойная инициализация
	for (long rr = 0; rr < mmd3.rows; rr++)
	{
		for (long cc = 0; cc < mmd3.cols; cc++)
		{
			for (long pp = 0; pp < mmd3.pages; pp++)
			{
				long c = pp * mmd3.rows * mmd3.cols + rr * mmd3.cols + cc;

				switch (pp%3)
				{
				case 0:
					{
						beta_A[c] = 0.0;
                        omega_A[c] = 0.0;
                        if (apply_B){
						beta_B[c] = 0.0;
						omega_B[c] = 0.0;
                        }
					}
					break;
				case 1:
					{
						beta_A[c] = 0.5 * PI;
						omega_A[c] = 0.0;
                        if (apply_B){
						omega_B[c] = 0.0;
                        beta_B[c] = 0.5 * PI;
                        }
                    }
					break;
				case 2:
					{
						beta_A[c] = 0.5 * PI;
						omega_A[c] = 0.5 * PI;
                        if (apply_B){
						omega_B[c] = 0.5 * PI;
                        beta_B[c] = 0.5 * PI;
                        }
                    }
					break;
				}
			}
		}
	}

	//послойная инициализация
	for (long rr = 0; rr < mmd3.rows; rr++)
	{
		for (long cc = 0; cc < mmd3.cols; cc++)
		{
			for (long pp = 0; pp < mmd3.pages; pp++)
			{
				long c = pp * mmd3.rows * mmd3.cols + rr * mmd3.cols + cc;

				switch (pp%3)
				{
				case 0:
					{
						beta_A[c] = 0.0;
                        omega_A[c] = 0.0;
                        if (apply_B){
                        beta_B[c] = 0.0;
						omega_B[c] = 0.0;
                        }
					}
					break;
				case 1:
					{
						beta_A[c] = 0.25 * PI;
                        omega_A[c] = 0.25 * PI;
                        if (apply_B){
                        beta_B[c] = 0.25 * PI;
						omega_B[c] = 0.25 * PI;
                        }
					}
					break;
				case 2:
					{
						beta_A[c] = 0.25 * PI;
                        omega_A[c] = 0.75 * PI;
                        if (apply_B){
                        beta_B[c] = 0.25 * PI;
						omega_B[c] = 0.75 * PI;
                        }
					}
					break;
				}
			}
		}
	}

	//послойная инициализация
	for (long rr = 0; rr < mmd3.rows; rr++)
	{
		for (long cc = 0; cc < mmd3.cols; cc++)
		{
			for (long pp = 0; pp < mmd3.pages; pp++)
			{
				long c = pp * mmd3.rows * mmd3.cols + rr * mmd3.cols + cc;

				switch (pp%2)
				{
				case 0:
					{
						beta_A[c] = 0.25 * PI;
                        omega_A[c] = 0.25 * PI;
                        if (apply_B){
                        beta_B[c] = 0.25 * PI;
						omega_B[c] = 0.25 * PI;
                        }
					}
					break;
				case 1:
					{
						beta_A[c] = 0.25 * PI;
                        omega_A[c] = 0.75 * PI;
                        if (apply_B){
                        beta_B[c] = 0.25 * PI;
						omega_B[c] = 0.75 * PI;
                        }
					}
					break;
				}
			}
		}
	}
#endif
#if 0
	//вертикально вверх инициализация
	for (long c = 0; c < operator_cols; c++)
	{
		beta_A[c] = 0.0;
        omega_A[c] = 0.0;
        if (apply_B){
        beta_B[c] = 0.0;
		omega_B[c] = 0.0;
        }
	}
#endif

    printf("after init\n");

	double ax, ay, az;
	double rx, ry, rz;

    printf("calc nju_phi_min");

	double nju_phi_min = DBL_MAX;
    for (ia = 0; ia < va.size(); ia++) {
        printf("\nia = %d\n", ia);
        a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
            printf("ia = %d r = %d operator_rows = %d\r", ia, r, operator_rows);

            ax = A[a][r].ax;
			ay = A[a][r].ay;
			az = A[a][r].az;

			for (long c = 0; c < operator_cols; c++)
			{
				rx = R[0][r][c];
				ry = R[1][r][c];
				rz = R[2][r][c];

				// коэффициент выхода диаграммы направленности
				double nju_phi_A = nju_phi_calc(beta_A[c], omega_A[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_A > DBL_MIN && nju_phi_A < nju_phi_min)
					nju_phi_min = nju_phi_A;

                if (apply_B){

				// коэффициент выхода диаграммы направленности
				double nju_phi_B = nju_phi_calc(beta_B[c], omega_B[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_B > DBL_MIN && nju_phi_B < nju_phi_min)
					nju_phi_min = nju_phi_B;
                }

			}
		}
	}

    printf("\nnju_phi_min = %e\n", nju_phi_min);
    printf("zero_substitution = %e\n", zero_substitution);

	zero_substitution = 0.9 * nju_phi_min;
    printf("zero_substitution = %e\n", zero_substitution);

    printf("fill operators p_A and W_p_A");

    for (ia = 0; ia < va.size(); ia++) {
        printf("\nia = %d\n", ia);
        a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
            printf("ia = %d r = %d operator_rows = %d\r", ia, r, operator_rows);

			ax = A[a][r].ax;
			ay = A[a][r].ay;
			az = A[a][r].az;

			for (long c = 0; c < operator_cols; c++)
			{
				rx = R[0][r][c];
				ry = R[1][r][c];
				rz = R[2][r][c];

				// коэффициент выхода диаграммы направленности
				double nju_phi_A = nju_phi_calc(beta_A[c], omega_A[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_A < zero_substitution)
					nju_phi_A = zero_substitution;


				//double ktic = KTi[c], epa = Ep[a], marc = m[a][r][c];

				// mode_A
				double _p_A = Ep[a] / (m[a][r][c] * nju_phi_A * KTi_A[c]);
				p_A[a][r][c] = _p_A;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_A[a][r][c] = alglib::errorfunctionc(sqrt(_p_A)) + 2.0 * sqrt (_p_A / PI) * exp(-_p_A);
				//double W_p_a_r_c = W_p[a][r][c]; double inv_W = 1.0 / W_p_a_r_c;
				
				//if (W_p_A[a][r][c] != W_p_A[a][r][c] || W_p_A[a][r][c] == 0)
				//{
                //    printf("nju_phi_A[%d][%d][%d] = %f _p_A=%f W_p_A=%f\n", a, r, c, nju_phi_A, _p_A, W_p_A[a][r][c]);
				//	printf("Ep[a]=%f m[a][r][c]=%e nju_phi_A=%e KTi_A[c]=%f\n", Ep[a], m[a][r][c], nju_phi_A, KTi_A[c]);
				//	printf("ax=%f, ay=%f, az=%f, rx=%f, ry=%f, rz=%f\n", ax, ay, az, rx, ry, rz);
				//}
                if (apply_B){
				// коэффициент выхода диаграммы направленности
				double nju_phi_B = nju_phi_calc(beta_B[c], omega_B[c], 
					rx, ry, rz, 
					ax, ay, az);

				if (nju_phi_B < zero_substitution)
					nju_phi_B = zero_substitution;

				// mode_B
				double _p_B = k[a] * W[a+6][r] / (m[a][r][c] * nju_phi_B * KTi_B[c]);
				p_B[a][r][c] = _p_B;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
                W_p_B[a][r][c] = alglib::errorfunctionc(sqrt(_p_B)) + 2.0 * sqrt (_p_B / PI) * exp(-_p_B);
				//double W_p_a_r_c = W_p[a][r][c]; double inv_W = 1.0 / W_p_a_r_c;
                }
			}
		}
	}
    printf("\np_B and W_p_B filled\n");
#if 0
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			for (long c = 0; c < operator_cols; c++)
			{
                double ktic = KTi_A[c];
                //double epa = Ep_A[a];
                //double marc = m_A[a][r][c];
                printf("ktic = %f\r", ktic);

			}
		}
	}
    printf("\n");
#endif

	// Выход оператора прямой задачи
    printf("alloc operators outputs C_A and CJI_A");
#if 0
    vector<vector<vector<double> > > CJI_A(3);
    vector<vector<vector<double> > > CJI_B(3);
    for (ia = 0; ia < va.size(); ia++) {
        printf("\nia = %d\n", ia);
        a = va[ia]; // перебираем 3 антены
        if (!init_by_lamp)
            S[a].resize(operator_rows, 0.0);

        CJI_A[a].resize(operator_rows);
        if (apply_B){
        CJI_B[a].resize(operator_rows);
        }

        for (long r = 0; r < operator_rows; r++) // длина сигнала
        {
            printf("ia = %d r = %d operator_rows = %d\r", ia, r, operator_rows);
            try{
                CJI_A[a][r].resize(operator_cols, 0.0);
                if (apply_B){
                CJI_B[a][r].resize(operator_cols, 0.0);
                }
            }
            catch(...)
            {
                printf("\nresize fault\n");
            }
        }
    }
#else
    double *** CJI_A;
    double *** CJI_B = 0;

    CJI_A = Alloc3DMat<double>(3, operator_rows, operator_cols);
    if (apply_B){
        CJI_B = Alloc3DMat<double>(3, operator_rows, operator_cols);
    }

#endif

	vector<vector<double> > C_A(3);
	vector<vector<double> > C_B(3);

    for (ia = 0; ia < va.size(); ia++) {
        printf("\nia = %d\n", ia);
        a = va[ia]; // перебираем 3 антены
		if (!init_by_lamp) 
			S[a].resize(operator_rows, 0.0);
		C_A[a].resize(operator_rows, 0.0);

        if (apply_B){
		C_B[a].resize(operator_rows, 0.0);
        }
	}

	// init ni
    printf("\ninit ni operator_rows=%d operator_cols=%d\n", operator_rows, operator_cols);

	double sum_C_a_r_A = 0.0;//суммарный выход оператора прямой задачи
	double sum_W_a_r_A = 0.0;//сумма векторов правых членов

	double sum_C_a_r_B = 0.0;//суммарный выход оператора прямой задачи
	double sum_W_a_r_B = 0.0;//сумма векторов правых членов

	double mean_B_A[3];
	double mean_B_B[3];
			
    for (ia = 0; ia < va.size(); ia++) {
    printf("\ninit ni ia = %d\n", ia);
        a = va[ia]; // перебираем 3 антены
		mean_B_A[a] = 0.0;
        if (apply_B){
		mean_B_B[a] = 0.0;
        }
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
            printf("init ni ia = %d r = %d\r", ia, r);

			// Выход оператора прямой задачи
			C_A[a][r] = 0.0;
            if (apply_B){
			C_B[a][r] = 0.0;
            }
			for (long c = 0; c < operator_cols; c++)
			{
				if (W_p_A[a][r][c] != W_p_A[a][r][c])
				{
					printf("W_p_A[%d][%d][%d] = %f\n", a, r, c, W_p_A[a][r][c]);
				}
				//double W_p_a_r_c = W_p[a][r][c];
				C_A[a][r] += W_p_A[a][r][c];
                if (apply_B){
				C_B[a][r] += W_p_B[a][r][c];
                }
			}
			//if (C_A[a][r] != C_A[a][r])
			//{
			//	printf("C_A[%d][%d] = %f\n", a, r, C_A[a][r]);
			//}
			double car_A = C_A[a][r], war_A = W[a][r];
            double car_B, war_B;
            if (apply_B){
            car_B = C_B[a][r], war_B = W[a+3][r];
            }

			mean_B_A[a] += war_A;
            if (apply_B){
			mean_B_B[a] += war_B;
            }


			sum_C_a_r_A += car_A;
			sum_W_a_r_A += war_A;

            if (apply_B){
			sum_C_a_r_B += car_B;
			sum_W_a_r_B += war_B;
            }
		}
		mean_B_A[a] /= operator_rows;
        if (apply_B){
		mean_B_B[a] /= operator_rows;
        }
	}

	double init_ni_A = sum_W_a_r_A / sum_C_a_r_A;
	double init_ni_B = sum_W_a_r_B / sum_C_a_r_B;

	printf("init_ni_A = sum_W_a_r_A(%f) / sum_C_a_r_A(%f) = %f\n", sum_W_a_r_A , sum_C_a_r_A, init_ni_A);
	printf("init_ni_A = %f\n", init_ni_A);

	printf("init_ni_B = sum_W_a_r_B(%f) / sum_C_a_r_B(%f) = %f\n", sum_W_a_r_B , sum_C_a_r_B, init_ni_B);
	printf("init_ni_B = %f\n", init_ni_B);

	if (sum_C_a_r_A == 0.0)
	{
		MessageBox(0, "Сумарный выход прямой задачи равен нулю!","Инициализация не верна", MB_OK);
		return false;

	}
    if (apply_B && sum_C_a_r_B == 0.0)
	{
		MessageBox(0, "Сумарный выход прямой задачи равен нулю!","Инициализация не верна", MB_OK);
		return false;

	}


	vector<double> ni_A(operator_cols, init_ni_A);
    vector<double> ni_B;
    if (apply_B){
    ni_B.resize(operator_cols, init_ni_B);
    }



	// Невязка
	vector<vector<double> > Er_A(3);
	vector<vector<double> > Er_B(3);
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		Er_A[a].resize(operator_rows);
        if (apply_B){
		Er_B[a].resize(operator_rows);
        }
	}

	char DirName[4098];
    sprintf(DirName, "%s/init", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}

	if (!init_by_lamp)
	{
		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		
			for (long r = 0; r < operator_rows; r++)
			{
				// Выход оператора прямой задачи
				C_A[a][r] = 0.0;
                if (apply_B){
				C_B[a][r] = 0.0;
                }
				for (long c = 0; c < operator_cols; c++)
				{
					//double nic = ni[c], W_p_a_r_c = W_p[a][r][c];
					C_A[a][r] += ni_A[c] * W_p_A[a][r][c];
                }
                if (apply_B){
                    for (long c = 0; c < operator_cols; c++)
                    {
                        C_B[a][r] += ni_B[c] * W_p_B[a][r][c];
                    }
                }
				// инициализация коэффициента симметризации
				if (C_A[a][r] != 0)
					S[a][r] = mean_B_A[a] / C_A[a][r]; // здесь иницивлизация не работает в том случае если имеются нулевые C_A[a][r]
				else
				{
					MessageBox(0, "иницивлизация не работает имеются нулевые C_A[a][r]", "", 0);
					return false;
				}
				//S[a][r] = 
				//	sqrt(mean_B_A[0]*mean_B_A[0] + mean_B_A[1]*mean_B_A[1] + mean_B_A[2]*mean_B_A[2]) 
				//	/ sqrt(C_A[0][r]*C_A[0][r] + C_A[1][r]*C_A[1][r] + C_A[2][r]*C_A[2][r]);
			}
		}


		SavingIteration(va, 0, "init",
			true,//bool apply_log10,
			true,// apply_bln,
			KTi_A, "log10_KTi_A",
			ni_A, "log10_ni_A",
			C_A, W,	0,// int da,
			DirName,
			"initial_C",//const char * method_name,
			NULL, mmd3, 
			to_reduce_x, to_reduce_y);
	}
    if (apply_B){

	SavingIteration(va, 0, "init",
		true,//bool apply_log10,
		true,// apply_bln,
		KTi_B, "log10_KTi_B",
		ni_B, "log10_ni_B",
		S, W, 3,// int da,
		DirName,
		"initial_S",//const char * method_name,
		NULL, mmd3, 
		to_reduce_x, to_reduce_y);
    }

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			// пересчёт выхода оператора прямой задачи с учётом коэффициента симметризации
			C_A[a][r] = 0.0;
            if (apply_B){
			C_A[a][r] = 0.0;
            }
			for (long c = 0; c < operator_cols; c++)
			{
				//double nic = ni[c], W_p_a_r_c = W_p[a][r][c];
				C_A[a][r] += S[a][r] * ni_A[c] * W_p_A[a][r][c];
                if (apply_B){
				C_B[a][r] += S[a][r] * ni_B[c] * W_p_B[a][r][c];
                }

				//if (C_A[a][r] != C_A[a][r])
				//{
				//	printf("C_A[%d][%d]=%f S[a][r]=%f ni_A[c]=%f W_p_A[%d][%d][%d]=%e\n",
				//		a, r, C_A[a][r], S[a][r], ni_A[c], a, r, c, W_p_A[a][r][c]);
				//}
			}
			//double car = C[a][r], war = W[a][r];
			//size_t W_a_size = W[a].size();
			// Невязка
			Er_A[a][r] = C_A[a][r] - W[a][r];//режим А
            if (apply_B){
			Er_B[a][r] = C_B[a][r] - W[a+3][r];//режим B
            }
		}
	}

	const double one_per_sqrt_pi = 1.0 / sqrt(PI);
	const double two_per_sqrt_pi = 2.0 / sqrt(PI);
	const double four_per_sqrt_pi = 4.0 / sqrt(PI);

			
	vector<double> dGdni_A(operator_cols);
	vector<double> d2Gdni2_A(operator_cols);

	vector<double> dGdni_B(operator_cols);
	vector<double> d2Gdni2_B(operator_cols);
    if (apply_B){
        dGdni_B.resize(operator_cols);
        d2Gdni2_B.resize(operator_cols);
    }

	vector<double> dGdKTi_A(operator_cols);
	vector<double> d2GdKTi2_A(operator_cols);

	vector<double> dGdKTi_B(operator_cols);
	vector<double> d2GdKTi2_B(operator_cols);
    if (apply_B){
        dGdKTi_B.resize(operator_cols);
        d2GdKTi2_B.resize(operator_cols);
    }

	vector<double> dGdbeta_A(operator_cols);
	vector<double> d2Gdbeta2_A(operator_cols);

	vector<double> dGdbeta_B(operator_cols);
	vector<double> d2Gdbeta2_B(operator_cols);
    if (apply_B){
        dGdbeta_B.resize(operator_cols);
        d2Gdbeta2_B.resize(operator_cols);
    }

	vector<double> dGdomega_A(operator_cols);
	vector<double> d2Gdomega2_A(operator_cols);

	vector<double> dGdomega_B(operator_cols);
	vector<double> d2Gdomega2_B(operator_cols);
    if (apply_B){
        dGdomega_B.resize(operator_cols);
        d2Gdomega2_B.resize(operator_cols);
    }



	vector<double> dGdEp(3);
	vector<double> d2GdEp2(3);

	vector<double> dGdk(3);
	vector<double> d2Gdk2(3);

	vector<vector<double> > temp_A(3);
	vector<vector<double> > temp52_A(3);
	vector<vector<double> > temp_B(3);
	vector<vector<double> > temp52_B(3);
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		temp_A[a].resize(operator_cols);
		temp52_A[a].resize(operator_cols);

        if (apply_B){
		temp_B[a].resize(operator_cols);
		temp52_B[a].resize(operator_cols);
        }
	}



	char file_name[1024];
	char name[2048];
	char method_name[512];
	sprintf(method_name, "MXW_Sj");
	sprintf(name, "norm_k_%s", 	method_name);



	
    /*sprintf(DirName, "%s/maxwell_iters", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}
    sprintf(DirName, "%s/MX", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}*/

	char iter_file[4098];
    sprintf(iter_file, "%s/iterations.txt", common_directory);
	FILE * iter_txt = fopen (iter_file, "wt");
	if (iter_txt)
	{
		fprintf(iter_txt, "iterations,nparam,one");
		fprintf(iter_txt, ",GA,errorA,EpX,EpY,EpZ");
		fprintf(iter_txt, ",GB,errorB,kX,kY,kZ, sX,sY,sZ");
		/*for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
		{
			for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
			{
				fprintf(iter_txt, ",error_of_%s_alpha=%e", new_names_of_colomns[cc].c_str(), mmd3.v_alpha[i_alpha]);
			}
		}*/
		fprintf(iter_txt, "\n");
		fclose(iter_txt);
	}

	typedef  Grid4 * GRID_POINTER;
	typedef  GRID_POINTER * GRID_2_POINTER;
	Grid4 *** cubes = new GRID_2_POINTER[cols_3];

	for (int cc = 0; cc < cols_3; cc++)
	{
		for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
		{			
			new_names_of_colomns[cc] += 
				names_of_colomns[original_col_numbers[c]];
			new_names_of_colomns[cc] += "_";
		}
		cubes[cc] = new GRID_POINTER[4];
		for (int i_cube = 0; i_cube < 4; i_cube++)
		{
			// Грид по размеру геологической структуры
			cubes[cc][i_cube] = CreateProfileGrid3D(mmd3);
			Zero3DMat<double>(cubes[cc][i_cube]->grid4Section.v, cubes[cc][i_cube]->grid4Section.nPag, cubes[cc][i_cube]->grid4Section.nRow, cubes[cc][i_cube]->grid4Section.nCol);
			Fill3DMatByValue<double>(BLANK_VALUE, cubes[cc][i_cube]->grid4Section.v, cubes[cc][i_cube]->grid4Section.nPag, cubes[cc][i_cube]->grid4Section.nRow, cubes[cc][i_cube]->grid4Section.nCol);
		}
	}
	double MA = 0.0;
	double MB = 0.0;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			//if(r == operator_rows - 1)
			//{
			//	double sad = 0;
			//}
			//double ear = Er[a][r];
			MA += W[a][r] * W[a][r];
            if (apply_B){
			MB += W[a+3][r] * W[a+3][r];
            }
		}
	}
	MA /= 2.0;
    if (apply_B){
	MB /= 2.0;
    }

	
	
	double sqrt_MA = sqrt(2.0 * MA / operator_rows);
	double sqrt_MB = sqrt(2.0 * MB / operator_rows);

	SavingIteration(va, 0, "init",
		true,//bool apply_log10,
		true,// apply_bln,
		KTi_A, "log10_KTi_A",
		ni_A, "log10_ni_A",
		C_A, W,	0,// int da,
		DirName,
		"MXWA_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);
    if (apply_B){
	SavingIteration(va, 0, "init",
		true,//bool apply_log10,
		true,// apply_bln,
		KTi_B, "log10_KTi_B",
		ni_B, "log10_ni_B",
		C_B, W,	3,// int da,
		DirName,
		"MXWB_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);
    }

	SavingIteration(va, 0, "init",
		false,//bool apply_log10,
		false,// apply_bln,
		beta_A, "beta_A",
		omega_A, "omega_A",
		C_A, W,	0,// int da,
		DirName,
		"MXWB_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);

    if (apply_B){

	SavingIteration(va, 0, "init",
		false,//bool apply_log10,
		false,// apply_bln,
		beta_B, "beta_B",
		omega_B, "omega_B",
		C_B, W,	0,// int da,
		DirName,
		"MXWB_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);
    }

    sprintf(DirName, "%s/korr", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}
	SavingIteration(va, 0, "korr",
		false,//bool apply_log10,
		false,// apply_bln,
		k_corr, "k_corr",
		k_cov, "k_cov",
		C_A,
		W,
		0,// int da,
		DirName,
		"MXW_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);


	double GA_pre = DBL_MAX;
	double GB_pre = DBL_MAX;
	double one = 1.0;
	double min_d2 = 1.0;

//	cout << "Enter one" << endl;
//	cin >> one;

//	cout << "Enter min_d2" << endl;
//	cin >> min_d2;

	vector<IterationParam> iteration_params(8);

	iteration_params[0].apply = apply_dgdni;
	iteration_params[0].one = one;
	iteration_params[0].min_d2 = min_d2;
	iteration_params[0].param = &ni_A;
	iteration_params[0].dGdparam = &dGdni_A;
	iteration_params[0].d2Gdparam2 = &d2Gdni2_A;

	iteration_params[1].apply = apply_dgdKTi;
	iteration_params[1].one = one;
	iteration_params[1].min_d2 = min_d2;
	iteration_params[1].param = &KTi_A;
	iteration_params[1].dGdparam = &dGdKTi_A;
	iteration_params[1].d2Gdparam2 = &d2GdKTi2_A;

	iteration_params[2].apply = apply_dgdbeta;
	iteration_params[2].one = one;
	iteration_params[2].min_d2 = min_d2;
	iteration_params[2].param = &beta_A;
	iteration_params[2].dGdparam = &dGdbeta_A;
	iteration_params[2].d2Gdparam2 = &d2Gdbeta2_A;

	iteration_params[3].apply = apply_dgdomega;
	iteration_params[3].one = one;
	iteration_params[3].min_d2 = min_d2;
	iteration_params[3].param = &omega_A;
	iteration_params[3].dGdparam = &dGdomega_A;
	iteration_params[3].d2Gdparam2 = &d2Gdomega2_A;

	iteration_params[4].apply = apply_dgdni && apply_B;
	iteration_params[4].one = one;
	iteration_params[4].min_d2 = min_d2;
	iteration_params[4].param = &ni_B;
	iteration_params[4].dGdparam = &dGdni_B;
	iteration_params[4].d2Gdparam2 = &d2Gdni2_B;

	iteration_params[5].apply = apply_dgdKTi && apply_B;
	iteration_params[5].one = one;
	iteration_params[5].min_d2 = min_d2;
	iteration_params[5].param = &KTi_B;
	iteration_params[5].dGdparam = &dGdKTi_B;
	iteration_params[5].d2Gdparam2 = &d2GdKTi2_B;

	iteration_params[6].apply = apply_dgdbeta && apply_B;
	iteration_params[6].one = one;
	iteration_params[6].min_d2 = min_d2;
	iteration_params[6].param = &beta_B;
	iteration_params[6].dGdparam = &dGdbeta_B;
	iteration_params[6].d2Gdparam2 = &d2Gdbeta2_B;

	iteration_params[7].apply = apply_dgdomega && apply_B;
	iteration_params[7].one = one;
	iteration_params[7].min_d2 = min_d2;
	iteration_params[7].param = &omega_B;
	iteration_params[7].dGdparam = &dGdomega_B;
	iteration_params[7].d2Gdparam2 = &d2Gdomega2_B;

	vector<double> param_reserve(operator_cols);


	//bool apply_cycle = false;

		double GA = 0.0;
		double GB = 0.0;
		long c_apply = -1;

        ForwordOperatorApply_dipol(c_apply, apply_B,

			GA, GB, va, m, // три матрицы njuX, njuY, njuZ
			R, A,
			W,
	            
			operator_rows, operator_cols,

			p_A,  W_p_A,  ni_A,  KTi_A, beta_A, omega_A, 
			Ep, CJI_A,  C_A,  Er_A,  S,

			p_B,  W_p_B,  ni_B,  KTi_B, beta_B, omega_B,
			k, s,  mean_B_B,				  
			CJI_B,  C_B,  Er_B

			);

	double sqrt_GA = sqrt(2.0 * GA / operator_rows);
	double sqrt_GB = sqrt(2.0 * GB / operator_rows);
	double errorA = 100.0 * (sqrt_GA / sqrt_MA);
	double errorB = 100.0 * (sqrt_GB / sqrt_MB);

    printf ("%d\tGA = %f\terrA=%e\tEp = %f\t%f\t%f\n", 0, GA, errorA, Ep[0], Ep[1], Ep[2]);
    printf ("%d\tGB = %f\terrB=%e\tk = %f\t%f\t%f\n", 0, GB, errorB, k[0], k[1], k[2]);
	printf ("%d\ts = %f\t%f\t%f\n", 0, s[0], s[1], s[2]);

	iter_txt = fopen (iter_file, "at");
	if (iter_txt)
	{
		fprintf(iter_txt, "%d,%d", 0, -1 );
        fprintf(iter_txt, ",%e", 0.0);
        fprintf(iter_txt, ",%f,%e,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
        fprintf(iter_txt, ",%f,%e,%f,%f,%f", GB, errorB, k[0],  k[1],  k[2]);
		fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);
		fprintf(iter_txt, "\n");
		fclose(iter_txt);
	}	


	GA_pre = GA;
	GB_pre = GB;

	int n_bad_iterations = 0;
	for (int iteration = 1; iteration < 1000000; iteration++)
	{

		//if (iteration > 1) apply_cycle = true;

		char method_name[512];
		sprintf(method_name, "MX_iter=%05d", iteration);
        sprintf(DirName, "%s/%s", common_directory, method_name);
		if (iteration%mmd3.iter_save == 0)
		{
			if (!CreateDirectory(DirName,NULL))
			{
			}
		}
		
		for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
		{
		}

        long n_params = 8;
        if (false == apply_B)
            n_params = 4;

        for (long n_param = 0;
            n_param < n_params;
            n_param++)
        {
            if (iteration_params[n_param].apply) {
                printf ("n_param=%ld one=%e min_d2=%f\n",
                        n_param,
                        iteration_params[n_param].one,
                        iteration_params[n_param].min_d2);
            }
        }

#if 1
		//long n_param_pre = 2;
		//long n_param_pre = 7;
		for (long n_param = 0; 
            n_param < n_params;
			n_param++)
		{
			if (!iteration_params[n_param].apply) continue;

            CalcDerivatives_dipol(c_apply, apply_B, apply_dgdep, apply_dgdni, va,
				operator_rows, operator_cols, 
				mmd3.pw_dnp, R, A,  						
				p_A, W_p_A,
				ni_A, KTi_A, beta_A, omega_A, Ep,						
				Er_A, S,
				dGdni_A, d2Gdni2_A, dGdKTi_A, d2GdKTi2_A,
				dGdbeta_A, d2Gdbeta2_A, dGdomega_A, d2Gdomega2_A,
				dGdEp, d2GdEp2,
				temp_A, temp52_A, 
				p_B, W_p_B,
				ni_B, KTi_B, beta_B, omega_B, k, s,
				Er_B,
				dGdni_B, d2Gdni2_B, dGdKTi_B, d2GdKTi2_B, 
				dGdbeta_B, d2Gdbeta2_B, dGdomega_B, d2Gdomega2_B, 
				dGdk, d2Gdk2,					
				temp_B, temp52_B					 
			);

			for (long c = 0; c < operator_cols; c++)
				param_reserve[c] = (*iteration_params[n_param].param).operator [](c);


			ApplyIteration_dipol(use_newton,
				iteration_params[n_param].one, 
				iteration_params[n_param].min_d2,
				operator_cols, 
				iteration_params[n_param].param,
				iteration_params[n_param].dGdparam,
				iteration_params[n_param].d2Gdparam2);

			GA = 0.0;
			GB = 0.0;

            ForwordOperatorApply_dipol(c_apply, apply_B,

				GA, GB, va, m, // три матрицы njuX, njuY, njuZ
				R, A,
				W,
		            
				operator_rows, operator_cols,

				p_A,  W_p_A,  ni_A,  KTi_A, beta_A, omega_A, 
				Ep, CJI_A,  C_A,  Er_A,  S,

				p_B,  W_p_B,  ni_B,  KTi_B, beta_B, omega_B,
				k, s,  mean_B_B,				  
				CJI_B,  C_B,  Er_B

				);



			bool we_have_bad_iteration = 
				n_param < 4 ?
				GA > GA_pre:
				GB > GB_pre;


			if (we_have_bad_iteration)
			{
				double sqrt_GA = sqrt(2.0 * GA / operator_rows);
                double errorA = 100.0 * (sqrt_GA / sqrt_MA);

                double sqrt_GB = 0.0;
                double errorB = 0.0;
                if (apply_B)
                {
                    sqrt_GB = sqrt(2.0 * GB / operator_rows);
                    errorB = 100.0 * (sqrt_GB / sqrt_MB);
                }

                printf ("bad%d\tGA = %f\terrA=%e\tEp = %f\t%f\t%f\n", iteration, GA, errorA, Ep[0], Ep[1], Ep[2]);
                printf ("bad%d\tGB = %f\terrB=%e\tk = %f\t%f\t%f\n", iteration, GB, errorB, k[0], k[1], k[2]);
				printf ("bad%d\ts = %f\t%f\t%f\n", iteration, s[0], s[1], s[2]);

				iter_txt = fopen (iter_file, "at");
				if (iter_txt)
				{
                    fprintf(iter_txt, "bad%d,%ld", iteration, n_param);
					fprintf(iter_txt, ",%e", iteration_params[n_param].one);
                    fprintf(iter_txt, ",%f,%e,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
                    fprintf(iter_txt, ",%f,%e,%f,%f,%f", GB, errorB, k[0],  k[1],  k[2]);
					fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);
					fprintf(iter_txt, "\n");
					fclose(iter_txt);
				}	

				/*
				ApplyIteration_dipol(-iteration_params[n_param].one, 
					iteration_params[n_param].min_d2,
					operator_cols, 
					iteration_params[n_param].param,
					iteration_params[n_param].dGdparam,
					iteration_params[n_param].d2Gdparam2);
					*/
				for (long c = 0; c < operator_cols; c++)
					(*iteration_params[n_param].param).operator [](c) = param_reserve[c];


				GA = 0.0;
				GB = 0.0;

                ForwordOperatorApply_dipol(c_apply, apply_B,

					GA, GB, va, m, // три матрицы njuX, njuY, njuZ
					R, A,
					W,
			            
					operator_rows, operator_cols,

					p_A,  W_p_A,  ni_A,  KTi_A, beta_A, omega_A, 
					Ep, CJI_A,  C_A,  Er_A,  S,

					p_B,  W_p_B,  ni_B,  KTi_B, beta_B, omega_B,
					k, s,  mean_B_B,				  
					CJI_B,  C_B,  Er_B

					);

				iteration_params[n_param].one *= 0.1;
				n_bad_iterations++;	

			}
			else
			{
				if (iteration_params[n_param].one < 1.0)
					iteration_params[n_param].one *= 1.1;
				n_bad_iterations = 0;

				if (n_param < 4)
                    GA_pre = GA;
				else
					GB_pre = GB;
			}

			double sqrt_GA = sqrt(2.0 * GA / operator_rows);
            double errorA = 100.0 * (sqrt_GA / sqrt_MA);

            double sqrt_GB = 0.0;
            double errorB = 0.0;
            if (apply_B) {
                sqrt_GB = sqrt(2.0 * GB / operator_rows);
                errorB = 100.0 * (sqrt_GB / sqrt_MB);
            }

            printf ("%d\tGA = %f\terrA=%e\tEp = %f\t%f\t%f\n", iteration, GA, errorA, Ep[0], Ep[1], Ep[2]);
            printf ("%d\tGB = %f\terrB=%e\tk = %f\t%f\t%f\n", iteration, GB, errorB, k[0], k[1], k[2]);
			printf ("%d\ts = %f\t%f\t%f\n", iteration, s[0], s[1], s[2]);


			iter_txt = fopen (iter_file, "at");
			if (iter_txt)
			{
                fprintf(iter_txt, "%d,%ld", iteration, n_param);
				fprintf(iter_txt, ",%e", iteration_params[n_param].one);
                fprintf(iter_txt, ",%f,%e,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
                fprintf(iter_txt, ",%f,%e,%f,%f,%f", GB, errorB, k[0],  k[1],  k[2]);
				fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);
				fprintf(iter_txt, "\n");
				fclose(iter_txt);
			}			


			//n_param_pre = n_param;


		}
#else

		for (long c_apply = (apply_cycle ? 0 : -1); 
			c_apply < (apply_cycle ? operator_cols : 0); 
			c_apply++)
		{
			//printf ("c_apply = %d\n", c_apply);
			double GA = 0.0;
			double GB = 0.0;

            ForwordOperatorApply_dipol(c_apply, apply_B,

				GA, GB, va, m, // три матрицы njuX, njuY, njuZ
				R, A,
				W,
	                
				operator_rows, operator_cols,

				p_A,  W_p_A,  ni_A,  KTi_A, beta_A, omega_A, 
				Ep, CJI_A,  C_A,  Er_A,  S,

				p_B,  W_p_B,  ni_B,  KTi_B, beta_B, omega_B,
				k, s,  mean_B_B,				  
				CJI_B,  C_B,  Er_B

				);

			if (apply_cycle ? c_apply == operator_cols - 1 : true)
			{
				double sqrt_GA = sqrt(2.0 * GA / operator_rows);
				double sqrt_GB = sqrt(2.0 * GB / operator_rows);
				double errorA = 100.0 * (sqrt_GA / sqrt_MA);
				double errorB = 100.0 * (sqrt_GB / sqrt_MB);

				printf ("%d\tGA = %f\terrA=%f\tEp = %f\t%f\t%f\n", iteration, GA, errorA, Ep[0], Ep[1], Ep[2]);
				printf ("%d\tGB = %f\terrB=%f\tk = %f\t%f\t%f\n", iteration, GB, errorB, k[0], k[1], k[2]);
				printf ("%d\ts = %f\t%f\t%f\n", iteration, s[0], s[1], s[2]);


				if (GA > GA_pre && iteration > 1)
				{
					ApplyIteration_dipol(c_apply, -one,
						apply_dgdep, 
						apply_dgdni,
						apply_dgdbeta,
						apply_dgdomega,
						va,

						operator_cols,

						ni_A,
						KTi_A,
						beta_A,
						omega_A,
						Ep,

						dGdni_A,
						d2Gdni2_A,
						dGdKTi_A,
						d2GdKTi2_A,
						dGdbeta_A,
						d2Gdbeta2_A,
						dGdomega_A,
						d2Gdomega2_A,
						dGdEp,
						d2GdEp2,

						ni_B,
						KTi_B,
						beta_B,
						omega_B,
						k,
						dGdni_B,
						d2Gdni2_B,
						dGdKTi_B,
						d2GdKTi2_B,
						dGdbeta_B,
						d2Gdbeta2_B,
						dGdomega_B,
						d2Gdomega2_B,
						dGdk,
						d2Gdk2

						);


										
                    ForwordOperatorApply_dipol(c_apply, apply_B,
						GA,
						GB,
						va,
						m, // три матрицы njuX, njuY, njuZ
						R, A,
						W,
						
						operator_rows,
						operator_cols,
						
						p_A,
						W_p_A,
						
						ni_A,
						KTi_A,
						beta_A,
						omega_A,
						Ep,
						
						CJI_A,
						C_A,
						Er_A,
						S,
						
						p_B,
						W_p_B,
						
						ni_B,
						KTi_B,
						beta_B,
						omega_B,
						
						k,
						s,
						mean_B_B,
						
						CJI_B,
						C_B,
						Er_B
						);


					if (n_bad_iterations == 0)
					{
						sprintf(method_name, "MX_iter=%05d",iteration);
                        sprintf(DirName, "%s/%s", common_directory, method_name);
		
						if (!CreateDirectory(DirName,NULL))
						{
						}
				
						SavingIteration(va, iteration, "",
							true, //bool apply_log10,
							true, //bool apply_bln,
							KTi_A, "log10_KTi_A",
							ni_A, "log10_ni_A",
							C_A, W, 0, //int da
							DirName, //const char * common_directory,
							"MXWA_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							false, //bool apply_log10,
							false, //bool apply_bln,
							KTi_A, "KTi_A",
							ni_A, "ni_A",
							C_A, W,	0, //int da
							DirName, //const char * common_directory,
							"MXWA_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							false, //bool apply_log10,
							false, //bool apply_bln,
							beta_A, "beta_A",
							omega_A, "omega_A",
							C_A, W,	0, //int da
							DirName, //const char * common_directory,
							"MXWA_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							true, //bool apply_log10,
							true, //bool apply_bln,
							KTi_B, "log10_KTi_B",
							ni_B, "log10_ni_B",
							C_B, W, 3, //int da
							DirName, //const char * common_directory,
							"MXWB_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							false, //bool apply_log10,
							false, //bool apply_bln,
							KTi_B, "KTi_B",
							ni_B, "ni_B",
							C_B, W,	3, //int da
							DirName, //const char * common_directory,
							"MXWB_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							false, //bool apply_log10,
							false, //bool apply_bln,
							beta_B, "beta_B",
							omega_B, "omega_B",
							C_B, W,	3, //int da
							DirName, //const char * common_directory,
							"MXWB_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);
					}


					one *= 0.95;
					n_bad_iterations++;	

					if (n_bad_iterations > 10)
					{
						apply_cycle = true;
					}
				}
				else
				{
					n_bad_iterations = 0;
				}

				GA_pre = GA;
				GB_pre = GB;

				if (iter_txt)
				{
					fprintf(iter_txt, ",%f,%d", one, apply_cycle);
					fprintf(iter_txt, ",%f,%f,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
					fprintf(iter_txt, ",%f,%f,%f,%f,%f", GB, errorB, k[0], k[1], k[2]);
					fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);
				}
			}
				
            CalcDerivatives_dipol(c_apply, apply_B, apply_dgdep, apply_dgdni, va,
				operator_rows, operator_cols, 
				mmd3.pw_dnp, R, A,  						
				p_A, W_p_A,
				ni_A, KTi_A, beta_A, omega_A, Ep,						
				Er_A, S,
				dGdni_A, d2Gdni2_A, dGdKTi_A, d2GdKTi2_A,
				dGdbeta_A, d2Gdbeta2_A, dGdomega_A, d2Gdomega2_A,
				dGdEp, d2GdEp2,
				temp_A, temp52_A, 
				p_B, W_p_B,
				ni_B, KTi_B, beta_B, omega_B, k, s,
				Er_B,
				dGdni_B, d2Gdni2_B, dGdKTi_B, d2GdKTi2_B, 
				dGdbeta_B, d2Gdbeta2_B, dGdomega_B, d2Gdomega2_B, 
				dGdk, d2Gdk2,					
				temp_B, temp52_B					 
			);


			ApplyIteration_dipol(c_apply, one,	apply_dgdep, apply_dgdni, apply_dgdbeta, apply_dgdomega, va,
				operator_cols,
				ni_A, KTi_A, beta_A, omega_A, Ep,
				dGdni_A, d2Gdni2_A, dGdKTi_A, d2GdKTi2_A, dGdbeta_A, d2Gdbeta2_A, dGdomega_A, d2Gdomega2_A, dGdEp, d2GdEp2,
				ni_B, KTi_B, beta_B, omega_B, k,
				dGdni_B, d2Gdni2_B,	dGdKTi_B, d2GdKTi2_B, dGdbeta_B, d2Gdbeta2_B, dGdomega_B, d2Gdomega2_B, dGdk,	d2Gdk2
				);
		}
		
		if (iter_txt)
		{
			fprintf(iter_txt, "\n");
			fclose(iter_txt);
		}
#endif

		if (iteration%mmd3.iter_save == 0)
		{

			SavingIteration(va, iteration, "",
				true, //bool apply_log10,
				true, //bool apply_bln,
				KTi_A, "log10_KTi_A",
				ni_A, "log10_ni_A",
				C_A, W, 0, //int da
				DirName, //const char * common_directory,
				"MXWA", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				false, //bool apply_log10,
				false, //bool apply_bln,
				KTi_A, "KTi_A",
				ni_A, "ni_A",
				C_A, W,	0, //int da
				DirName, //const char * common_directory,
				"MXWA", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				false, //bool apply_log10,
				false, //bool apply_bln,
				beta_A, "beta_A",
				omega_A, "omega_A",
				C_A, W,	0, //int da
				DirName, //const char * common_directory,
				"MXWA", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				true, //bool apply_log10,
				false, //bool apply_bln,
				beta_A, "log10_beta_A",
				omega_A, "log10_omega_A",
				C_A, W,	0, //int da
				DirName, //const char * common_directory,
				"MXWA", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

            if (apply_B){

			SavingIteration(va, iteration, "",
				true, //bool apply_log10,
				true, //bool apply_bln,
				KTi_B, "log10_KTi_B",
				ni_B, "log10_ni_B",
				C_B, W, 3, //int da
				DirName, //const char * common_directory,
				"MXWB", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				false, //bool apply_log10,
				false, //bool apply_bln,
				KTi_B, "KTi_B",
				ni_B, "ni_B",
				C_B, W,	3, //int da
				DirName, //const char * common_directory,
				"MXWB", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				false, //bool apply_log10,
				false, //bool apply_bln,
				beta_B, "beta_B",
				omega_B, "omega_B",
				C_B, W,	3, //int da
				DirName, //const char * common_directory,
				"MXWB", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);
            }
		}

	}







	// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
	//vector<vector<vector<double> > >  sols_mean;
//				double z_min = mmd3.z0 - mmd3.pages * mmd3.delta_z;
	//for (long p = 0; p < mmd3.pages; p++)
	//	zi = z_min + p * mmd3.delta_z;




	//
	printf("Yes!!!\n");



	Free3DMat(m);
	Free3DMat(p_A);
    Free3DMat(W_p_A);
    if (apply_B){
	Free3DMat(p_B);
	Free3DMat(W_p_B);
    }

	for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
	{
		for (int i_cube = 0; i_cube < 2; i_cube ++)
		{
			Free3DMat<double>(cubes[cc][i_cube]->grid4Section.v);
			delete cubes[cc][i_cube];
		}
		delete cubes[cc];
	}

	delete cubes;
#endif
}






bool Lamp(int use_newton,
		  int type, // тип прямой задачи
		   long cols,
		   bool apply_dgdni,		   
		   bool apply_dgdKTi,
		   bool apply_dgdep,
		   bool apply_B,
		   vector<string> &names_of_colomns,
		   vector<size_t> &original_col_numbers,
		   int nFilesInDirectory,
		   vector<double> &vX,
		   vector<double> &vY,
		   vector<double> &vZ,
		   vector<vector<double> > &W,
		   vector<vector<anten_direction> > & A,
		   bool only_init,
		   // массив коэффициентов симметризации
		   vector<vector<double> > & S,
		   MyMethodsData3 &mmd3,
		   double DZ,
		   char * common_directory)
{		
#if 1
    //sprintf(common_directory_iX_iY, "%s/whole_object_by_colomns", common_directory);
	//if (!CreateDirectory(common_directory_iX_iY, NULL))
	//{
	//}

	double min_X, max_X, min_Y, max_Y;				
	GetMinMaxXYOfData(vX, vY, min_X, max_X, min_Y, max_Y);

	double 
		DX = max_X - min_X, 
		DY = max_Y - min_Y; 

/*
	bool apply_dgdep = false;
	bool apply_dgdni = false;

	cout << "apply_dgdni" << endl;
	cin >> apply_dgdni;
	cout << "apply_dgdep" << endl;
	cin >> apply_dgdep;
*/


	double dx = DZ * mmd3.dx_and_dy_per_DZ;
	double dy = DZ * mmd3.dx_and_dy_per_DZ;


	mmd3.delta__x = DX - dx * int (mmd3.granicy_kak_glubina);
	mmd3.delta__y = DY - dy * int (mmd3.granicy_kak_glubina);
	mmd3.delta__z = mmd3.z0 - mmd3.z_min;


	// на случай редукции к двумерному случаю
	bool to_reduce_x = (DX - dx) < 0.0;
	bool to_reduce_y = (DY - dy) < 0.0;

	if (nFilesInDirectory == 1)
	{
		if (DX < DY)
		{
			to_reduce_x = true;
			to_reduce_y = false;
		}
		else
		{
			to_reduce_x = false;
			to_reduce_y = true;
		}
	}
	else
	{
		to_reduce_x = false;
		to_reduce_y = false;
	}


	if (to_reduce_x && to_reduce_y)
	{
		char err_str[2048];
		sprintf(err_str, 
			"to_reduce_x && to_reduce_y\n"
			"DX = %f DY = %f DZ = %f\n"
			"mmd3.dx_and_dy_per_DZ = %f\n"
			"dx = dy = %f"
			"nFilesInDirectory = %d"
			,
			DX, DY, DZ, 
			mmd3.dx_and_dy_per_DZ,
			dx,
			nFilesInDirectory);
		MessageBox(NULL, err_str, "Error", MB_OK);
		return false;
	}

	if (to_reduce_x) {mmd3.cols = 1; mmd3.delta__x = 0.0;}
	if (to_reduce_y) {mmd3.rows = 1; mmd3.delta__y = 0.0;}


	mmd3.x0 = to_reduce_x ? (min_X+max_X)/2.0 : min_X + 0.5 * dx * int (mmd3.granicy_kak_glubina);
	mmd3.y0 = to_reduce_y ? (min_Y+max_Y)/2.0 : min_Y + 0.5 * dy * int (mmd3.granicy_kak_glubina);

	mmd3.delta_x = to_reduce_x ? 0.0 : mmd3.delta__x / (mmd3.cols - 1);
	mmd3.delta_y = to_reduce_y ? 0.0 : mmd3.delta__y / (mmd3.rows - 1);



	vector<string> new_names_of_colomns;
	int cols_3 = cols / 3;//2
	new_names_of_colomns.resize(cols_3);

	//mmd3.delta_z = mmd3.delta__z / (mmd3.pages - 1);// это неверно!!!
	// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
	mmd3.delta_z = mmd3.delta__z / mmd3.pages;

	double *** m;// три матрицы njuX, njuY, njuZ
	printf("Filling of matrix\n");
	// формируем матрицу оператора прямой задачи, 
	// число строк равно длине сигнала 
	// (или суммарной длине нескольких сигналов - 
	// нескольких профилей на одной или, ещё лучше, на разных высотах)
	// на вход оператора подаётся геологическая структура 
	// источников геополяритонного сигнала
	// на выходе оператора имеем мощность излучения (сигнал) на профилях

	if (type == 1)
	{
		FillingTheMatrix3D_with_napravlennosty_diagramm(
			mmd3.k_oslablenie, 
			NULL, &m, 
			mmd3.rows, mmd3.cols, mmd3.pages,
			mmd3.x0, mmd3.y0, mmd3.z0,
			mmd3.delta_x, mmd3.delta_y, mmd3.delta_z,
			vX, vY, vZ, A,
			mmd3.pw_dnp,
			mmd3.min_value,
			mmd3.wave_type, 
			mmd3.spm);
	}
	else
	{
		MessageBox(NULL, "type should be 1", "Error", MB_OK);
		return false;
	}

	/*Grid4 * cube = ShowCube(mmd);
	char fn[1024]; 
    sprintf(fn, "%s/cube.cub",
		dir_out);
	SaveAsSurfer7Grid4(fn, cube);*/

	double *** p_A;
	double *** W_p_A;

	double *** p_B;
	double *** W_p_B;

	long signal_len = vX.size(); // длина сигнала 
	long operator_rows = signal_len; // длина сигнала 
	long operator_cols = mmd3.rows * mmd3.cols * mmd3.pages;

	p_A = Alloc3DMat<double>(3, operator_rows, operator_cols);
	W_p_A = Alloc3DMat<double>(3, operator_rows, operator_cols);

	p_B = Alloc3DMat<double>(3, operator_rows, operator_cols);
	W_p_B = Alloc3DMat<double>(3, operator_rows, operator_cols);


	double max_m = -DBL_MAX;
	double min_m = DBL_MAX;

	double max_Ep = -DBL_MAX;
	double min_Ep = DBL_MAX;

	vector<double> vmax_m(operator_cols, -DBL_MAX);
	vector<double> vmin_m(operator_cols, DBL_MAX);
	double mean_m = 0.0;

	short a, ia;  vector<short> va;
	va.push_back(0);//x
	va.push_back(1);//y
	va.push_back(2);//z
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	//for (int a = 0; a < 3; a++)// перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			double _Ep = W[a+6][r];
			if (max_Ep < _Ep) max_Ep = _Ep;
			if (min_Ep > _Ep) min_Ep = _Ep;
			for (long c = 0; c < operator_cols; c++)
			{
				double _m = m[a][r][c];
				if (_m > DBL_MIN)
				{
					if (max_m < _m)
						max_m = _m;
				
					if (min_m > _m)
						min_m = _m;

					if (vmax_m[c] < _m)
						vmax_m[c] = _m;
				
					if (vmin_m[c] > _m)
						vmin_m[c] = _m;

					mean_m += _m;
				}
			}
		}
	}
	const double zero_substitution = 0.9 * min_m;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			for (long c = 0; c < operator_cols; c++)
			{
				double & _m = m[a][r][c];
				if (_m <= DBL_MIN)
				{
					_m = zero_substitution;
					mean_m += _m;
				}
			}
		}
	}

	mean_m /= va.size() * operator_rows * operator_cols;


	double max_b = -DBL_MAX;
	double min_b = DBL_MAX;


	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			double _b = W[a][r];//режим А
			if (max_b < _b)
				max_b = _b;
			if (min_b > _b)
				min_b = _b;
		}
	}

	// считаем коэффициенты корреляции между оператором прямой задачи 
	// и сигналом
	vector<double> k_corr(operator_cols, 0.0);
	vector<double> k_cov(operator_cols, 0.0);
	for (long c = 0; c < operator_cols; c++) //длина геологической структуры
	{
		vector<double> v_m(operator_rows * va.size());
		vector<double> v_s(operator_rows * va.size());

		for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
			for (long r = 0; r < operator_rows; r++) // длина сигнала по одной антене
			{
				double _m = m[a][r][c];
				double _signal = W[a][r];

				v_m[operator_rows * ia + r] = _m;
				v_s[operator_rows * ia + r] = _signal;
			}
		}
		//рассчитываем коэффициент корреляции k_corr[c] для текущего элемента геологической структуры;
		double k, Cov;
		if (CorrelationCoefficient(v_s, v_m, k, Cov))
		{
			k_corr[c] = k;
			k_cov[c] = Cov;
		}
	}

	// инициализируем векторы решения
	double Ep[3] = {1.0, 1.0, 1.0};
	double k[3] = {1.0, 1.0, 1.0};
	double s[3] = {1.0, 1.0, 1.0};
//				double init_KT = 0.2 / min_m;  //эта иициализация к значению init_KT = 10e+16 причём KT не подстраивается за обозримое количество итераций
	//double init_KT = 0.2 / mean_m; эта инициализация привела к тому что суммарный выход оператора прямой задачи стал равен нулю но тут могла быть ошибка так как в mean_m вместо вреднего вычислялась сумма, что вело к значительному занижению значения init_KT
	//double init_KT = 0.2; // слишком мала "температура" -> суммарный выход оператора прямой задачи стал равен нулю
	double init_KT = 0.2*1e6;
	//init_KT = 0.2 / mean_m;
	init_KT = 10.0 / max_m;// это значит, что минимальный р будет равен 0.1
	vector<double> KTi_A(operator_cols, init_KT);
	vector<double> KTi_B(operator_cols, init_KT);
	if (false)
	{
		// эта инициализация "копирует" рельефные и краевые эффекты оператора прямой задачи
		for (long c = 0; c < operator_cols; c++) KTi_A[c] = 0.2 / vmin_m[c];
	}
		
	// эта инициализация равномерна по глубине, т.к. использует макс. m, который 
	// для каждой геоточки соответсвует направлению вертикально вверх
	// кроме того это означает, что минимальный р равен 0.1
	
	// mode_A
	for (long c = 0; c < operator_cols; c++) KTi_A[c] = 10.0 / vmax_m[c];
	// mode_B
	for (long c = 0; c < operator_cols; c++) KTi_B[c] = 10.0 * min_Ep / vmax_m[c];





	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			for (long c = 0; c < operator_cols; c++)
			{
				//double ktic = KTi[c], epa = Ep[a], marc = m[a][r][c];

				// mode_A
				double _p_A = Ep[a] / (m[a][r][c] * KTi_A[c]);
				p_A[a][r][c] = _p_A;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_A[a][r][c] = alglib::errorfunctionc(sqrt(_p_A)) + 2.0 * sqrt (_p_A / PI) * exp(-_p_A);
				//double W_p_a_r_c = W_p[a][r][c]; double inv_W = 1.0 / W_p_a_r_c;
				
				// mode_B
				double _p_B = k[a] * W[a+6][r] / (m[a][r][c] * KTi_B[c]);
				p_B[a][r][c] = _p_B;
				//W_p[a][r][c] = 1.0 + 2.0 * sqrt (_p / PI) * exp(-_p) - alglib::errorfunction(sqrt(_p));
				W_p_B[a][r][c] = alglib::errorfunctionc(sqrt(_p_B)) + 2.0 * sqrt (_p_B / PI) * exp(-_p_B);
				//double W_p_a_r_c = W_p[a][r][c]; double inv_W = 1.0 / W_p_a_r_c;
			}
		}
	}

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			for (long c = 0; c < operator_cols; c++)
			{
				//double ktic = KTi[c], epa = Ep[a], marc = m[a][r][c];

			}
		}
	}
	

	// Выход оператора прямой задачи
	vector<vector<double> > C_A(3);
	vector<vector<vector<double> > > CJI_A(3);
	vector<vector<double> > C_B(3);
	vector<vector<vector<double> > > CJI_B(3);

	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		S[a].resize(operator_rows, 0.0);
		C_A[a].resize(operator_rows, 0.0);
		CJI_A[a].resize(operator_rows);

		C_B[a].resize(operator_rows, 0.0);
		CJI_B[a].resize(operator_rows);

		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			CJI_A[a][r].resize(operator_cols, 0.0);
			CJI_B[a][r].resize(operator_cols, 0.0);
		}

	}

	// init ni
    printf("init ni\n");

	double sum_C_a_r_A = 0.0;//суммарный выход оператора прямой задачи
	double sum_W_a_r_A = 0.0;//сумма векторов правых членов

	double sum_C_a_r_B = 0.0;//суммарный выход оператора прямой задачи
	double sum_W_a_r_B = 0.0;//сумма векторов правых членов

	double mean_B_A[3];
	double mean_B_B[3];
			
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		mean_B_A[a] = 0.0;
		mean_B_B[a] = 0.0;
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			// Выход оператора прямой задачи
			C_A[a][r] = 0.0;
			C_B[a][r] = 0.0;
			for (long c = 0; c < operator_cols; c++)
			{
				//double W_p_a_r_c = W_p[a][r][c];
				C_A[a][r] += W_p_A[a][r][c];
				C_B[a][r] += W_p_B[a][r][c];
			}
			double car_A = C_A[a][r], war_A = W[a][r];
			double car_B = C_B[a][r], war_B = W[a+3][r];

			mean_B_A[a] += war_A;
			mean_B_B[a] += war_B;


			sum_C_a_r_A += car_A;
			sum_W_a_r_A += war_A;

			sum_C_a_r_B += car_B;
			sum_W_a_r_B += war_B;
		}
		mean_B_A[a] /= operator_rows;
		mean_B_B[a] /= operator_rows;
	}

	double init_ni_A = sum_W_a_r_A / sum_C_a_r_A;
	double init_ni_B = sum_W_a_r_B / sum_C_a_r_B;

	printf("init_ni_A = sum_W_a_r_A(%f) / sum_C_a_r_A(%f) = %f\n", sum_W_a_r_A , sum_C_a_r_A, init_ni_A);
	printf("init_ni_A = %f\n", init_ni_A);

	printf("init_ni_B = sum_W_a_r_B(%f) / sum_C_a_r_B(%f) = %f\n", sum_W_a_r_B , sum_C_a_r_B, init_ni_B);
	printf("init_ni_B = %f\n", init_ni_B);

	if (sum_C_a_r_A == 0.0)
	{
		MessageBox(0, "Сумарный выход прямой задачи равен нулю!","Инициализация не верна", MB_OK);
		return false;

	}
	if (sum_C_a_r_B == 0.0)
	{
		MessageBox(0, "Сумарный выход прямой задачи равен нулю!","Инициализация не верна", MB_OK);
		return false;

	}


	vector<double> ni_A(operator_cols, init_ni_A);
	vector<double> ni_B(operator_cols, init_ni_B);
	// Невязка
	vector<vector<double> > Er_A(3);
	vector<vector<double> > Er_B(3);
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
		Er_A[a].resize(operator_rows);
		Er_B[a].resize(operator_rows);
	}


	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++)
		{
			// Выход оператора прямой задачи
			C_A[a][r] = 0.0;
			C_B[a][r] = 0.0;
			for (long c = 0; c < operator_cols; c++)
			{
				//double nic = ni[c], W_p_a_r_c = W_p[a][r][c];
				C_A[a][r] += ni_A[c] * W_p_A[a][r][c];
				C_B[a][r] += ni_B[c] * W_p_B[a][r][c];
			}
			// инициализация коэффициента симметризации
			S[a][r] = mean_B_A[a] / C_A[a][r];

			// пересчёт выхода оператора прямой задачи с учётом коэффициента симметризации
			C_A[a][r] = 0.0;
			C_A[a][r] = 0.0;
			for (long c = 0; c < operator_cols; c++)
			{
				//double nic = ni[c], W_p_a_r_c = W_p[a][r][c];
				C_A[a][r] += S[a][r] * ni_A[c] * W_p_A[a][r][c];
				C_B[a][r] += S[a][r] * ni_B[c] * W_p_B[a][r][c];
			}
			//double car = C[a][r], war = W[a][r];
			//size_t W_a_size = W[a].size();
			// Невязка
			Er_A[a][r] = C_A[a][r] - W[a][r];//режим А
			Er_B[a][r] = C_B[a][r] - W[a+3][r];//режим B
		}
	}

	if (only_init)
	{
		return true;
	}

	const double one_per_sqrt_pi = 1.0 / sqrt(PI);
	const double two_per_sqrt_pi = 2.0 / sqrt(PI);
	const double four_per_sqrt_pi = 4.0 / sqrt(PI);

			
	vector<double> dGdni_A(operator_cols);
	vector<double> d2Gdni2_A(operator_cols);

    vector<double> dGdni_B;
    vector<double> d2Gdni2_B;
    if (apply_B) {
        dGdni_B.resize(operator_cols);
        d2Gdni2_B.resize(operator_cols);
    }

	vector<double> dGdKTi_A(operator_cols);
	vector<double> d2GdKTi2_A(operator_cols);

    vector<double> dGdKTi_B;
    vector<double> d2GdKTi2_B;
    if (apply_B) {
        dGdKTi_B.resize(operator_cols);
        d2GdKTi2_B.resize(operator_cols);
    }

	vector<double> dGdEp(3);
	vector<double> d2GdEp2(3);

	vector<double> dGdk(3);
	vector<double> d2Gdk2(3);

	vector<vector<double> > temp_A(3);
	vector<vector<double> > temp52_A(3);
	vector<vector<double> > temp_B(3);
	vector<vector<double> > temp52_B(3);
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		temp_A[a].resize(operator_cols);
		temp52_A[a].resize(operator_cols);
        if (apply_B) {

		temp_B[a].resize(operator_cols);
		temp52_B[a].resize(operator_cols);
        }
	}



	char file_name[1024];
	char name[2048];
	char method_name[512];
	sprintf(method_name, "MXW_Sj");
	sprintf(name, "norm_k_%s", 	method_name);



	
	char DirName[4098];
    /*sprintf(DirName, "%s/maxwell_iters", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}
    sprintf(DirName, "%s/MX", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}*/

	char iter_file[4098];
    sprintf(iter_file, "%s/iterations.txt", common_directory);
	FILE * iter_txt = fopen (iter_file, "wt");
	if (iter_txt)
	{
		fprintf(iter_txt, "iterations, one");
		fprintf(iter_txt, ",GA,errorA,EpX,EpY,EpZ");
		fprintf(iter_txt, ",GB,errorB,kX,kY,kZ, sX,sY,sZ");
		/*for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
		{
			for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha ++)
			{
				fprintf(iter_txt, ",error_of_%s_alpha=%e", new_names_of_colomns[cc].c_str(), mmd3.v_alpha[i_alpha]);
			}
		}*/
		fprintf(iter_txt, "\n");
		fclose(iter_txt);
	}

	typedef  Grid4 * GRID_POINTER;
	typedef  GRID_POINTER * GRID_2_POINTER;
	Grid4 *** cubes = new GRID_2_POINTER[cols_3];

	for (int cc = 0; cc < cols_3; cc++)
	{
		for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
		{			
			new_names_of_colomns[cc] += 
				names_of_colomns[original_col_numbers[c]];
			new_names_of_colomns[cc] += "_";
		}
		cubes[cc] = new GRID_POINTER[2];
		for (int i_cube = 0; i_cube < 2; i_cube++)
		{
			// Грид по размеру геологической структуры
			cubes[cc][i_cube] = CreateProfileGrid3D(mmd3);
			Zero3DMat<double>(cubes[cc][i_cube]->grid4Section.v, cubes[cc][i_cube]->grid4Section.nPag, cubes[cc][i_cube]->grid4Section.nRow, cubes[cc][i_cube]->grid4Section.nCol);
			Fill3DMatByValue<double>(BLANK_VALUE, cubes[cc][i_cube]->grid4Section.v, cubes[cc][i_cube]->grid4Section.nPag, cubes[cc][i_cube]->grid4Section.nRow, cubes[cc][i_cube]->grid4Section.nCol);
		}
	}
	double MA = 0.0;
	double MB = 0.0;
	for (ia = 0; ia < va.size(); ia++) { a = va[ia]; // перебираем 3 антены
	
		for (long r = 0; r < operator_rows; r++) // длина сигнала 
		{
			//if(r == operator_rows - 1)
			//{
			//	double sad = 0;
			//}
			//double ear = Er[a][r];
			MA += W[a][r] * W[a][r];
			MB += W[a+3][r] * W[a+3][r];
		}
	}
	MA /= 2.0;
	MB /= 2.0;

	
	
	double sqrt_MA = sqrt(2.0 * MA / operator_rows);
	double sqrt_MB = sqrt(2.0 * MB / operator_rows);

    sprintf(DirName, "%s/init", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}

	SavingIteration(va, 0, "init",
		true,//bool apply_log10,
		true,// apply_bln,
		KTi_A, "log10_KTi_A",
		ni_A, "log10_ni_A",
		C_A, W,	0,// int da,
		DirName,
		"MXWA_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);

	SavingIteration(va, 0, "init",
		true,//bool apply_log10,
		true,// apply_bln,
		KTi_B, "log10_KTi_B",
		ni_B, "log10_ni_B",
		C_B, W,	3,// int da,
		DirName,
		"MXWB_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);

    sprintf(DirName, "%s/korr", common_directory);
	if (!CreateDirectory(DirName,NULL))
	{
	}
	SavingIteration(va, 0, "korr",
		false,//bool apply_log10,
		false,// apply_bln,
		k_corr, "k_corr",
		k_cov, "k_cov",
		C_A,
		W,
		0,// int da,
		DirName,
		"MXW_Sj",//const char * method_name,
		cubes, mmd3, 
		to_reduce_x, to_reduce_y);


	double GA_pre = DBL_MAX;
	double GB_pre = DBL_MAX;
	//double one = 1.0;


	vector<IterationParam> iteration_params(4);

	iteration_params[0].apply = apply_dgdni;
	iteration_params[0].one = 1;
	iteration_params[0].min_d2 = 1.0;
	iteration_params[0].param = &ni_A;
	iteration_params[0].dGdparam = &dGdni_A;
	iteration_params[0].d2Gdparam2 = &d2Gdni2_A;

	iteration_params[1].apply = apply_dgdKTi;
	iteration_params[1].one = 1;
	iteration_params[1].min_d2 = 1.0;
	iteration_params[1].param = &KTi_A;
	iteration_params[1].dGdparam = &dGdKTi_A;
	iteration_params[1].d2Gdparam2 = &d2GdKTi2_A;

	iteration_params[2].apply = apply_dgdni && apply_B;
	iteration_params[2].one = 1;
	iteration_params[2].min_d2 = 1.0;
	iteration_params[2].param = &ni_B;
	iteration_params[2].dGdparam = &dGdni_B;
	iteration_params[2].d2Gdparam2 = &d2Gdni2_B;

	iteration_params[3].apply = apply_dgdKTi && apply_B;
	iteration_params[3].one = 1;
	iteration_params[3].min_d2 = 1.0;
	iteration_params[3].param = &KTi_B;
	iteration_params[3].dGdparam = &dGdKTi_B;
	iteration_params[3].d2Gdparam2 = &d2GdKTi2_B;

	vector<double> param_reserve(operator_cols);

	double GA = 0.0;
	double GB = 0.0;
	long c_apply = -1;

	ForwordOperatorApply(c_apply,

		GA, GB, va, m, // три матрицы njuX, njuY, njuZ
		W,
	        
		operator_rows, operator_cols,

		p_A,  W_p_A,  ni_A,  KTi_A,  
		Ep, CJI_A,  C_A,  Er_A,  S,

		p_B,  W_p_B,  ni_B,  KTi_B, 
		k, s,  mean_B_B,				  
		CJI_B,  C_B,  Er_B

		);

	double sqrt_GA = sqrt(2.0 * GA / operator_rows);
	double sqrt_GB = sqrt(2.0 * GB / operator_rows);
	double errorA = 100.0 * (sqrt_GA / sqrt_MA);
	double errorB = 100.0 * (sqrt_GB / sqrt_MB);

    printf ("%d\tGA = %f\terrA=%e\tEp = %f\t%f\t%f\n", 0, GA, errorA, Ep[0], Ep[1], Ep[2]);
    printf ("%d\tGB = %f\terrB=%e\tk = %f\t%f\t%f\n", 0, GB, errorB, k[0], k[1], k[2]);
	printf ("%d\ts = %f\t%f\t%f\n", 0, s[0], s[1], s[2]);

	iter_txt = fopen (iter_file, "at");
	if (iter_txt)
	{
		fprintf(iter_txt, "%d,%d", 0, -1 );
        fprintf(iter_txt, ",%e", 0.0);
        fprintf(iter_txt, ",%f,%e,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
        fprintf(iter_txt, ",%f,%e,%f,%f,%f", GB, errorB, k[0],  k[1],  k[2]);
		fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);
		fprintf(iter_txt, "\n");
		fclose(iter_txt);
	}
	//bool apply_cycle = false;

	GA_pre = GA;
	GB_pre = GB;

	int n_bad_iterations = 0;
	for (int iteration = 1; iteration < 1000000; iteration++)
	{

		//if (iteration > 1) apply_cycle = true;

		char method_name[512];
		sprintf(method_name, "MX_iter=%05d",iteration);
        sprintf(DirName, "%s/%s", common_directory, method_name);
		if (iteration%mmd3.iter_save == 0)
		{
			if (!CreateDirectory(DirName,NULL))
			{
			}
		}
		
		for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
		{
		}

#if 1
		//printf ("c_apply = %d\n", c_apply);


		//long n_param_pre = 3;
		for (long n_param = 0; 
			n_param < 4; 
			n_param++)
		{
			if (!iteration_params[n_param].apply) continue;

			CalcDerivatives(c_apply, apply_dgdep, apply_dgdni, va,
				operator_rows, operator_cols,						
				p_A, W_p_A,
				ni_A, KTi_A, Ep,						
				Er_A, S,
				dGdni_A, d2Gdni2_A, dGdKTi_A, d2GdKTi2_A, dGdEp, d2GdEp2,
				temp_A, temp52_A, 
				p_B, W_p_B,
				ni_B, KTi_B, k, s,
				Er_B,
				dGdni_B, d2Gdni2_B, dGdKTi_B, d2GdKTi2_B, dGdk, d2Gdk2,					
				temp_B, temp52_B					 
			);

			for (long c = 0; c < operator_cols; c++)
				param_reserve[c] = (*iteration_params[n_param].param).operator [](c);

			ApplyIteration_dipol(
				use_newton,
				iteration_params[n_param].one, 
				iteration_params[n_param].min_d2,
				operator_cols, 
				iteration_params[n_param].param,
				iteration_params[n_param].dGdparam,
				iteration_params[n_param].d2Gdparam2);

			GA = 0.0;
			GB = 0.0;

			ForwordOperatorApply(c_apply,

				GA, GB, va, m, // три матрицы njuX, njuY, njuZ
				W,
		            
				operator_rows, operator_cols,

				p_A,  W_p_A,  ni_A,  KTi_A,  
				Ep, CJI_A,  C_A,  Er_A,  S,

				p_B,  W_p_B,  ni_B,  KTi_B, 
				k, s,  mean_B_B,				  
				CJI_B,  C_B,  Er_B

				);

			bool we_have_bad_iteration = 
				n_param < 2 ?
				GA > GA_pre :
				GB > GB_pre;

			if (we_have_bad_iteration)
			{
				double sqrt_GA = sqrt(2.0 * GA / operator_rows);
				double sqrt_GB = sqrt(2.0 * GB / operator_rows);
				double errorA = 100.0 * (sqrt_GA / sqrt_MA);
				double errorB = 100.0 * (sqrt_GB / sqrt_MB);

                printf ("bad%d\tGA = %f\terrA=%e\tEp = %f\t%f\t%f\n", iteration, GA, errorA, Ep[0], Ep[1], Ep[2]);
                printf ("%d\tGB = %f\terrB=%e\tk = %f\t%f\t%f\n", iteration, GB, errorB, k[0], k[1], k[2]);
				printf ("%d\ts = %f\t%f\t%f\n", iteration, s[0], s[1], s[2]);

				iter_txt = fopen (iter_file, "at");
				if (iter_txt)
				{
					fprintf(iter_txt, "bad%d, %d", iteration, n_param);		
					fprintf(iter_txt, ",%f", iteration_params[n_param].one);
                    fprintf(iter_txt, ",%f,%e,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
                    fprintf(iter_txt, ",%f,%e,%f,%f,%f", GB, errorB, k[0], k[1], k[2]);
					fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);		
					fprintf(iter_txt, "\n");
					fclose(iter_txt);
				}			
				/*ApplyIteration_dipol(
					-iteration_params[n_param].one, 
					iteration_params[n_param].min_d2,
					operator_cols, 
					iteration_params[n_param].param,
					iteration_params[n_param].dGdparam,
					iteration_params[n_param].d2Gdparam2);*/
								
				for (long c = 0; c < operator_cols; c++)
					(*iteration_params[n_param].param).operator [](c) = param_reserve[c];


				GA = 0.0;
				GB = 0.0;

				ForwordOperatorApply(c_apply,

					GA, GB, va, m, // три матрицы njuX, njuY, njuZ
					W,
			            
					operator_rows, operator_cols,

					p_A,  W_p_A,  ni_A,  KTi_A,  
					Ep, CJI_A,  C_A,  Er_A,  S,

					p_B,  W_p_B,  ni_B,  KTi_B, 
					k, s,  mean_B_B,				  
					CJI_B,  C_B,  Er_B

					);

				iteration_params[n_param].one *= 0.1;
				n_bad_iterations++;	
			}
			else
			{
				if (iteration_params[n_param].one < 1.0)
					iteration_params[n_param].one *= 1.1;
				n_bad_iterations = 0;

				if (n_param < 2)
                    GA_pre = GA;
				else
					GB_pre = GB;
			}

			double sqrt_GA = sqrt(2.0 * GA / operator_rows);
			double sqrt_GB = sqrt(2.0 * GB / operator_rows);
			double errorA = 100.0 * (sqrt_GA / sqrt_MA);
			double errorB = 100.0 * (sqrt_GB / sqrt_MB);

            printf ("%d\tGA = %f\terrA=%e\tEp = %f\t%f\t%f\n", iteration, GA, errorA, Ep[0], Ep[1], Ep[2]);
            printf ("%d\tGB = %f\terrB=%e\tk = %f\t%f\t%f\n", iteration, GB, errorB, k[0], k[1], k[2]);
			printf ("%d\ts = %f\t%f\t%f\n", iteration, s[0], s[1], s[2]);

			iter_txt = fopen (iter_file, "at");
			if (iter_txt)
			{
				fprintf(iter_txt, "%d, %d", iteration, n_param);		
				fprintf(iter_txt, ",%f", iteration_params[n_param].one);
                fprintf(iter_txt, ",%f,%e,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
                fprintf(iter_txt, ",%f,%e,%f,%f,%f", GB, errorB, k[0], k[1], k[2]);
				fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);		
				fprintf(iter_txt, "\n");
				fclose(iter_txt);
			}			
			
				


//			n_param_pre = n_param;
		}
#else

		for (long c_apply = (apply_cycle ? 0 : -1); 
			c_apply < (apply_cycle ? operator_cols : 0); 
			c_apply++)
		{

			//printf ("c_apply = %d\n", c_apply);
			double GA = 0.0;
			double GB = 0.0;

			ForwordOperatorApply(c_apply,

				GA, GB, va, m, // три матрицы njuX, njuY, njuZ
				W,
	                
				operator_rows, operator_cols,

				p_A,  W_p_A,  ni_A,  KTi_A,  
				Ep, CJI_A,  C_A,  Er_A,  S,

				p_B,  W_p_B,  ni_B,  KTi_B, 
				k, s,  mean_B_B,				  
				CJI_B,  C_B,  Er_B

				);

			if (apply_cycle ? c_apply == operator_cols - 1 : true)
			{
				double sqrt_GA = sqrt(2.0 * GA / operator_rows);
				double sqrt_GB = sqrt(2.0 * GB / operator_rows);
				double errorA = 100.0 * (sqrt_GA / sqrt_MA);
				double errorB = 100.0 * (sqrt_GB / sqrt_MB);

				printf ("%d\tGA = %f\terrA=%f\tEp = %f\t%f\t%f\n", iteration, GA, errorA, Ep[0], Ep[1], Ep[2]);
				printf ("%d\tGB = %f\terrB=%f\tk = %f\t%f\t%f\n", iteration, GB, errorB, k[0], k[1], k[2]);
				printf ("%d\ts = %f\t%f\t%f\n", iteration, s[0], s[1], s[2]);


				if (GA > GA_pre && iteration > 1)
				{
					ApplyIteration(c_apply, -one,
						apply_dgdep, 
						apply_dgdni,
						va,

						operator_cols,

						ni_A,
						KTi_A,
						Ep,

						dGdni_A,
						d2Gdni2_A,
						dGdKTi_A,
						d2GdKTi2_A,
						dGdEp,
						d2GdEp2,

						ni_B,
						KTi_B,
						k,
						dGdni_B,
						d2Gdni2_B,
						dGdKTi_B,
						d2GdKTi2_B,
						dGdk,
						d2Gdk2

						);


										
					ForwordOperatorApply(c_apply,
						GA,
						GB,
						va,
						m, // три матрицы njuX, njuY, njuZ
						W,
						
						operator_rows,
						operator_cols,
						
						p_A,
						W_p_A,
						
						ni_A,
						KTi_A,
						Ep,
						
						CJI_A,
						C_A,
						Er_A,
						S,
						
						p_B,
						W_p_B,
						
						ni_B,
						KTi_B,
						
						k,
						s,
						mean_B_B,
						
						CJI_B,
						C_B,
						Er_B
						);


					if (n_bad_iterations == 0)
					{
						sprintf(method_name, "MX_iter=%05d",iteration);
                        sprintf(DirName, "%s/%s", common_directory, method_name);
		
						if (!CreateDirectory(DirName,NULL))
						{
						}
				
						SavingIteration(va, iteration, "",
							true, //bool apply_log10,
							true, //bool apply_bln,
							KTi_A, "log10_KTi_A",
							ni_A, "log10_ni_A",
							C_A, W, 0, //int da
							DirName, //const char * common_directory,
							"MXWA_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							false, //bool apply_log10,
							false, //bool apply_bln,
							KTi_A, "KTi_A",
							ni_A, "ni_A",
							C_A, W,	0, //int da
							DirName, //const char * common_directory,
							"MXWA_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							true, //bool apply_log10,
							true, //bool apply_bln,
							KTi_B, "log10_KTi_B",
							ni_B, "log10_ni_B",
							C_B, W, 3, //int da
							DirName, //const char * common_directory,
							"MXWB_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);

						SavingIteration(va, iteration, "",
							false, //bool apply_log10,
							false, //bool apply_bln,
							KTi_B, "KTi_B",
							ni_B, "ni_B",
							C_B, W,	3, //int da
							DirName, //const char * common_directory,
							"MXWB_loc_min", //const char * method_name,
							cubes, mmd3, 
							to_reduce_x, to_reduce_y);
					}


					one *= 0.95;
					n_bad_iterations++;	

					//if (n_bad_iterations > 10)
					//{
					//	apply_cycle = true;
					//}
				}
				else
				{
					n_bad_iterations = 0;
				}

				GA_pre = GA;
				GB_pre = GB;

				if (iter_txt)
				{
					fprintf(iter_txt, ",%f", one);
					fprintf(iter_txt, ",%f,%f,%f,%f,%f", GA, errorA, Ep[0], Ep[1], Ep[2]);
					fprintf(iter_txt, ",%f,%f,%f,%f,%f", GB, errorB, k[0], k[1], k[2]);
					fprintf(iter_txt, ",%f,%f,%f", s[0], s[1], s[2]);
				}
			}
				
			CalcDerivatives(c_apply, apply_dgdep, apply_dgdni, va,
				operator_rows, operator_cols,						
				p_A, W_p_A,
				ni_A, KTi_A, Ep,						
				Er_A, S,
				dGdni_A, d2Gdni2_A, dGdKTi_A, d2GdKTi2_A, dGdEp, d2GdEp2,
				temp_A, temp52_A, 
				p_B, W_p_B,
				ni_B, KTi_B, k, s,
				Er_B,
				dGdni_B, d2Gdni2_B, dGdKTi_B, d2GdKTi2_B, dGdk, d2Gdk2,					
				temp_B, temp52_B					 
			);


			ApplyIteration(c_apply, one,	apply_dgdep, apply_dgdni, va,
				operator_cols,
				ni_A, KTi_A, Ep,
				dGdni_A, d2Gdni2_A, dGdKTi_A, d2GdKTi2_A, dGdEp, d2GdEp2,
				ni_B, KTi_B, k,
				dGdni_B, d2Gdni2_B,	dGdKTi_B, d2GdKTi2_B, dGdk,	d2Gdk2
				);
		}

		
		if (iter_txt)
		{
			fprintf(iter_txt, "\n");
			fclose(iter_txt);
		}
#endif
		if (iteration%mmd3.iter_save == 0)
		{

			SavingIteration(va, iteration, "",
				true, //bool apply_log10,
				true, //bool apply_bln,
				KTi_A, "log10_KTi_A",
				ni_A, "log10_ni_A",
				C_A, W, 0, //int da
				DirName, //const char * common_directory,
				"MXWA", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				false, //bool apply_log10,
				false, //bool apply_bln,
				KTi_A, "KTi_A",
				ni_A, "ni_A",
				C_A, W,	0, //int da
				DirName, //const char * common_directory,
				"MXWA", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				true, //bool apply_log10,
				true, //bool apply_bln,
				KTi_B, "log10_KTi_B",
				ni_B, "log10_ni_B",
				C_B, W, 3, //int da
				DirName, //const char * common_directory,
				"MXWB", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);

			SavingIteration(va, iteration, "",
				false, //bool apply_log10,
				false, //bool apply_bln,
				KTi_B, "KTi_B",
				ni_B, "ni_B",
				C_B, W,	3, //int da
				DirName, //const char * common_directory,
				"MXWB", //const char * method_name,
				cubes, mmd3, 
				to_reduce_x, to_reduce_y);
		}

	}







	// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
	//vector<vector<vector<double> > >  sols_mean;
//				double z_min = mmd3.z0 - mmd3.pages * mmd3.delta_z;
	//for (long p = 0; p < mmd3.pages; p++)
	//	zi = z_min + p * mmd3.delta_z;




	//
	printf("Yes!!!\n");



	Free3DMat(m);
	Free3DMat(p_A);
	Free3DMat(p_B);
	Free3DMat(W_p_A);
	Free3DMat(W_p_B);

	for (int cc = 0; cc < cols_3; cc++) // для каждой колонки - суть для каждого параметра
	{
		for (int i_cube = 0; i_cube < 2; i_cube ++)
		{
			Free3DMat<double>(cubes[cc][i_cube]->grid4Section.v);
			delete cubes[cc][i_cube];
		}
		delete cubes[cc];
	}

	delete cubes;
#endif
}

bool AutoBuildProfileDlg0::OpenFileDialog(void)
{
    HRESULT hr = S_OK;

	TCHAR filter[] =
		TEXT("Comma separated files (*.csv)\0*.csv\0")
		TEXT("Data files (*.dat*)\0*.dat\0")
		TEXT("Text files (*.txt)\0*.txt\0")
		;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
    OPENFILENAME ofn;       // common dialog box structure
    // Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.hInstance         = hInst;
   
//	ofn.lCustData         = (LPARAM)&this->oftcd;
//    ofn.lpfnHook          = DlgProcOpenFilesToCommon;
    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_OPEN_FILES_TO_COMMON);
	ofn.Flags = 
		OFN_PATHMUSTEXIST 
		| OFN_FILEMUSTEXIST
		| OFN_EXPLORER 
//		| OFN_ENABLETEMPLATE 
//		| OFN_ENABLEHOOK 
		| OFN_ALLOWMULTISELECT
		;

	if (GetOpenFileName(&ofn)==TRUE)
	{
		if (ofn.lpstrFile != NULL)
		{
			this->m_files_in_dir.nFilterIndex = ofn.nFilterIndex;
			switch(this->m_files_in_dir.nFilterIndex)
			{
			case 1:
				strcpy(this->m_files_in_dir.szFileFilter, "*.csv");
				break;
			case 2:
				strcpy(this->m_files_in_dir.szFileFilter, "*.dat");
				break;
			case 3:
				strcpy(this->m_files_in_dir.szFileFilter, "*.txt");
				break;
			}
			//strcpy(file, ofn.lpstrFile + ofn.nFileOffset);
			strcpy(this->directory, ofn.lpstrFile);
			if (ofn.nFileOffset > 1) this->directory[ofn.nFileOffset-1] = '\0';


		}
		return true;
	}
	else
	{
		DWORD dwErr = CommDlgExtendedError();
		LPVOID lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwErr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		char str[255];
		sprintf(str, "Ошибка создания окна выбора файла = %d", dwErr);


		::MessageBox(NULL, (LPCTSTR)lpMsgBuf, str, MB_OK);
		switch(dwErr)
		{
		case CDERR_DIALOGFAILURE :
			MessageBox(0,"The dialog box could not be created. ","CommDlgExtendedError",0);
			break;
		case CDERR_FINDRESFAILURE :
			MessageBox(0,"The common dialog box function failed to find a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_INITIALIZATION :
			MessageBox(0,"The common dialog box function failed during initialization. This error often occurs when sufficient memory is not available","CommDlgExtendedError",0);
			break;
		case CDERR_LOADRESFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_LOADSTRFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified string.","CommDlgExtendedError",0);
			break;
		case CDERR_LOCKRESFAILURE :
			MessageBox(0,"The common dialog box function failed to lock a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMALLOCFAILURE :
			MessageBox(0,"The common dialog box function was unable to allocate memory for internal structures.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMLOCKFAILURE :
			MessageBox(0,"The common dialog box function was unable to lock the memory associated with a handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHINSTANCE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding instance handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHOOK :
			MessageBox(0,"The ENABLEHOOK flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a pointer to a corresponding hook procedure.","CommDlgExtendedError",0);
			break;
		case CDERR_NOTEMPLATE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding template.","CommDlgExtendedError",0);
			break;
		case CDERR_REGISTERMSGFAIL :
			MessageBox(0,"The RegisterWindowMessage function returned an error code when it was called by the common dialog box function.","CommDlgExtendedError",0);
			break;
		case CDERR_STRUCTSIZE :
			MessageBox(0,"The lStructSize member of the initialization structure for the corresponding common dialog box is invalid.","CommDlgExtendedError",0);
			break;
		case FNERR_BUFFERTOOSMALL :
			short size;
			memcpy(&size, ofn.lpstrFile, 2);
			char str[1024];
			sprintf(str, "The buffer pointed to by the lpstrFile member of the OPENFILENAME structure is too small for the file name specified by the user. The first two bytes of the lpstrFile buffer contain an integer value specifying the size = %d, in TCHARs, required to receive the full name. ", size);
			MessageBox(0, str,"CommDlgExtendedError",0);
			break;
		case FNERR_INVALIDFILENAME :
			{
				char err_str[255];
				sprintf(err_str, "A file name is invalid.\n%s", ofn.lpstrFile );
				MessageBox(0,err_str,"CommDlgExtendedError",0);
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a list box failed because sufficient memory was not available.","CommDlgExtendedError",0);
			break;

		}
	}
	// Display the Open dialog box. 
	return false;
#else
#if 0
	QStringList files = QFileDialog::getOpenFileNames(
		NULL,
		"Select one or more files to open",
		QDir("../").absolutePath(),
		"Comma separated files (*.csv)");
#else
#if 0
	QStringList filters;
	filters << "Comma separated files (*.csv)"
		<< "Data files (*.dat)"
		<< "Text files (*.txt)"
		<< "Any files (*)";

	QFileDialog dialog(hDlg);
	dialog.setNameFilters(filters);
	dialog.setDirectory(QDir("../").absolutePath());
	dialog.setFileMode(QFileDialog::ExistingFiles);
	if (!dialog.exec())
		return false;

	QDir dir = dialog.directory();
	QString dirAbsPath = dir.absolutePath();
	std::string dir_abs_path = dirAbsPath.toStdString();
	strcpy(this->directory, dir_abs_path.c_str());

	QStringList files = dialog.selectedFiles();
#else
	QDir qdir = QDir("../data/rovno/rovno_u001/");
	QString dir = qdir.absolutePath();
	strcpy(this->directory, dir.toStdString().c_str());

	QStringList filters = QDir::nameFiltersFromString("*.csv");

    QStringList files = qdir.entryList(filters, QDir::Files, QDir::Name);
#endif
#endif
	if (files.size() > 0)
	{
		this->m_files_in_dir.nFilesInDirectory = files.size();
		//память не освобождена!!!!
		this->m_files_in_dir.vFileNameLengthes = (int*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(int) * this->m_files_in_dir.nFilesInDirectory);
		this->m_files_in_dir.vFileNames = (char**)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(char*) * this->m_files_in_dir.nFilesInDirectory);

		for (int iFile = 0; iFile < this->m_files_in_dir.nFilesInDirectory; iFile++)
		{
			this->m_files_in_dir.vFileNameLengthes[iFile] = files[iFile].size();
			this->m_files_in_dir.vFileNames[iFile] = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof(char) * this->m_files_in_dir.vFileNameLengthes[iFile]);
			strcpy(this->m_files_in_dir.vFileNames[iFile], files[iFile].toStdString().c_str());
		}
		return true;
	}
	return false;
#endif
}




#endif /*!VIEW_ONLY_VERSION*/
