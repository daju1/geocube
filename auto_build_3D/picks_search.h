#ifndef PEAKS_SEARCH_H
#define PEAKS_SEARCH_H


#include "stdafx.h"
#include "..\surfdoc\src\autoprofilebuilding.h"
//�������������� ������ � ����
#define _USE_MIN_IN_WINDOW_ 1

#include "./../array/src/LocalExtremumsFiltering.h"

#define COLLECTION FastCollection

#define _USE_WINSURF_ 0
#define _USE_WINSURF_ON_CONSOL_ 0
#define _DRAW_LINES_OF_GRAPHICS_ 0

#if _USE_WINSURF_

#if _USE_WINSURF_ON_CONSOL_
//for WinSurf
#include "../wintools/src/win32_app.h"
#include "../wintools/src/utility.h"
#include "../wintools/src/winsurf.h"
//end for WinSurf
#endif /*_USE_WINSURF_ON_CONSOL*/


#endif
class korr_point
{
public:
	double x;
	double y;
	double z;

	double korr_k;  // ����������� �������������� ����������
	double korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
	double korr_k3; // ����������� ������������ ��������������
	korr_point()
	{
		korr_k  = 0.0;
		korr_k2 = 0.0;
		korr_k3 = 0.0;
	}
};
//������� �������������� �������������
class vert_korr_points
{
public:
	int iFile;
	vector<korr_point> vkp;
	vert_korr_points()
	{
		iFile = -1;
	}
	~vert_korr_points()
	{
	}
};

class profile_interval
{
public:
	Layer * layer;
	int iFile;
	size_t i1;//������ ������� �������� ��������� �������� �������
	size_t i2;//������ ���������� �������� ��������� �������� �������
	char dir[4096];//���������� ��� ������ �����������

};

struct auto_build_parametrs
{
	// �������� �� ������� � ����
	bool use_min;
	bool use_max;
	bool use_min_max;

	// ��� �� ������� �������� �� windows_cicle
	bool use_min_2;
	bool use_max_2;
	bool use_min_max_2;

	bool use_whole_directory;
	bool use_num_col;	//������������ �� ������ �������
	int  tcols;			// ����� ������������� �������: 2 ���� XY 3 ���� XYZ
	bool use_time_colomn; // ��� ��� �� ������������� ��������� ������� �������
	char num_col_filename[1024];
	//######################################################
	bool use_window_cycles_algorithm_1;
	bool use_window_cycles_algorithm_dima;
	//######################################################
	bool use_locals;
	enum locals_algorithms
	{
		the_simple					= 0,
		on_the_second_derivatives	= 1
	}; 
	locals_algorithms locals_algorithms_type;
	//######################################################
	bool use_window_cycles_after_locals;
	bool use_window_cycles_algorithm_1_after_locals;
	bool use_window_cycles_algorithm_dima_after_locals;
	//######################################################
	//######################################################
	//��������� ���������� �� �������
	size_t start_j1;// = 1;//��������� ������� ���������� ��� ������ �������
	size_t start_j2;// = 0;//��������� ������� ���������� ��� window_cycles_after_locals
	// �������� ������ "�������" �� ���� ������
	// �� ����� �������� ������ �� �������� � "�������",
	// ������� ����� ����������� ���� �������
	// ��� ������ ��������, ��� ������ ������� ����� �������
	double quantil_naklony;// = 0.50;

	// �������� ������ ����� �������� �� �� ��������
	// �������� ������ ��������� ����������� ������ �����������
	// ���� �������� ������ ����� 0,5 �� �� �������� ��� ������������ ����� ��������
	// ��� ������ �������� ������ ��� ������ ����� �������� �� ���������������,
	// ��� ����� �� ��������� ���� ���� ������ ����� ��������
	double peregib_krutizna_quantil;// = 0.40;
	bool allow_sd_limit_quantil;// = true;
	//######################################################
	//######################################################
	//��������� ���������� �������� ��� ��������������� ����������� ��������
	enum gradient_type
	{
		the_dividitial				= 0,
		the_differential			= 1
	}; 
	gradient_type m_gradient_type;
	double limit_dima;// = 0.8, 
	double limit_1;//= 0.9;
	double minimum_of_signal;// = 0.1;
				

	// ������ ���������� ������������� �����
	bool use_repeat_points;// = false; // ���� ������, �� �� �� ��������� ������ ���������� ������������� �����, 
	// ����� - ��������� ������ �� ��������� �����������:
	int n;// = 1;//����� ������� ������� ( ����� 0 � ����)

	//��������� ��������� ����� ����
	// ������������ ����
	double win_velonsity;// = 0.9;

	//######################################################
	//######################################################
	double k;

	//������������ �������� "�����" �� ���-������
	bool use_min_max_sticks;


	int delim;
};
//void auto_build_parametrs_Init();

// ����������� ������� ������� �������
struct anten_direction
{
	double ax, ay, az;
	anten_direction()
	{
		ax = 0.0;
		ay = 0.0;
		az = 0.0;	
	}	
	anten_direction(double _ax, double _ay, double _az)
	{
		ax = _ax;
		ay = _ay;
		az = _az;	
	}
	void Init(double _ax, double _ay, double _az)
	{
		ax = _ax;
		ay = _ay;
		az = _az;	
	}
	void Norm()
	{
		double m = 1.0 / sqrt(ax*ax + ay*ay + az*az);
		ax *= m;
		ay *= m;
		az *= m;
	}
	void InitAsVectorProduct(anten_direction & a, anten_direction & b)
	{
		ax = a.ay * b.az - a.az * b.ay;
		ay = a.az * b.ax - a.ax * b.az;
		az = a.ax * b.ay - a.ay * b.ax;
	}
};

void WriteDescription(FILE* stream, auto_build_parametrs & ab);

class AutoBuildProfile;

bool AutoBuildProfile_main(
						   bool consol, 
						   AutoBuildProfile * p_auto_build_profile, 
						   auto_build_parametrs& ab
						   );
bool ReadColomnNumbers(
					   auto_build_parametrs& ab,
					   vector<bool>& use_col,
					   int& num_col,
					   int delim);
#if 0
bool BuildProfile(vector<vector<vector<vector<korr_point> > > >& vvvvkp,
				  char * sz_path_to_file, char * current_directory,
				  bool consol, 
				  AutoBuildProfile * p_auto_build_profile,
				  auto_build_parametrs& ab,
				  int& cols,
				  vector<bool>& use_col,
				  int num_col,
				  int delim
				  );
#endif
/*
bool BuildingProfile(vector<vector<vector<vector<korr_point> > > >& vvvvkp,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<vector<double> >& v, 
					 vector<vector<double> >& w, 
					 vector<double>& X, 
					 vector<double>& Y,
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int rows, int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename
				  );
*/
bool BuildingProfile2(vector<vector<vector<vector<korr_point> > > >& vvvvkp,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<vector<double> >& v, 
					 vector<vector<double> >& w, 
					 vector<double>& X, 
					 vector<double>& Y,
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int rows, int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename
				  );

void Window_Cycle(auto_build_parametrs::gradient_type m_gradient_type,
				  double limit_dima, double limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				  size_t icol, //����� �������
#endif

#if SOURCE_COORDINATES_3D
					vector<double>& X, 
					vector<double>& Y, 
#else
					vector<double>& t, 
#endif				  
				  vector<double>& in, 				  

				  size_t start_window_len,
				  size_t end_window_len,
				  //size_t step_vindow_len,
				  double win_velonsity,
				  
				  bool use_repeat_points,  int n,//����� ������� ������� ( ����� 0 � ����)
				  double minimum_of_signal, 
				   
				  double k,	
				  int delim,
#if _USE_WINSURF_

				  SurfDoc * doc, 				  
				  COLLECTION * pcollection_pda,	
				  COLLECTION * pcollection_nda,
				  COLLECTION * pcollection_pa,
				  COLLECTION * pcollection_na,
#endif
				  FILE * stream_common_razez_positive_dima,
				  FILE * stream_common_razez_negative_dima,
				  FILE * stream_common_razez_positive,
				  FILE * stream_common_razez_negative

				  );


#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
void SourcesCoordinates_Calcule_AndSave(size_t icol, size_t j1, size_t j2,
										size_t level, // ������� ����������	
										double x1, double y1, 
										double x2, double y2,
										double k, FILE * stream, int delim, double r_ , double max_, 
										double& x, double& y, double& z);
#else
void SourcesCoordinates_Calcule_AndSave(
										double x1, double y1, 
										double x2, double y2,
										double k, FILE * stream, int delim, double r_ , double max_, 
										double& x, double& y, double& z);
#endif
#else
void SourcesCoordinates_Calcule_AndSave(double t1, double t2, double k, FILE * stream, int delim, double r_ , double max_, double& x, double& y);
#endif


void MakeLinePointPair(
#if SOURCE_COORDINATES_3D
				 vector<double>& X, 
				 vector<double>& Y, 
#else
				 vector<double>& t, 
#endif
				 vector<double> v, 
				 size_t i1, size_t i2,	
				 double x, double y, 
#if SOURCE_COORDINATES_3D
				 double z,
#endif
				 char *name, COLORREF color
				 , COLLECTION * pcollection_,
				 SurfDoc* doc
				);


void OutputDimaAlgorithm(double limit_dima,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						 size_t icol, //����� �������
						 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
						 vector<double>& X, 
						 vector<double>& Y, 
#else
						 vector<double>& t, 
#endif
						 vector<double>& in,
						 vector<size_t>& vi_max_grad, vector<size_t>& vi_min_grad,
						 vector<double>& v_max_grad, vector<double>& v_min_grad,
						 
						 double k,	
						 int delim,
#if _USE_WINSURF_

						 SurfDoc * doc, 
						 COLLECTION * pcollection_nda,
						 COLLECTION * pcollection_pda,
#endif
						 FILE * stream_com_raz_pos,
						 FILE * stream_com_raz_neg
						 );


void OutputFirstAlgorithm(double limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						 size_t icol, //����� �������
						 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
						 vector<double>& X, 
						 vector<double>& Y, 
#else
						 vector<double>& t, 
#endif
						 vector<double>& in,
						 vector<size_t>& vi_max_grad, vector<size_t>& vi_min_grad,
						 vector<double>& v_max_grad, vector<double>& v_min_grad,
						 
						 double k,	
						 int delim,
#if _USE_WINSURF_

						 SurfDoc * doc, 
						 COLLECTION * pcollection_na,
						 COLLECTION * pcollection_pa,
#endif
						 FILE * stream_com_raz_pos,
						 FILE * stream_com_raz_neg

						 );

void Window_Cycle_Of_Signal_which_Done_By_Indexes(
	auto_build_parametrs::gradient_type m_gradient_type,
	double limit_dima, double limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
		size_t icol, //����� �������
#endif

#if SOURCE_COORDINATES_3D
		vector<double>& X, 
		vector<double>& Y, 
#else
		vector<double>& t, 
#endif
	
		vector<double>& v,
		 vector<size_t>& vi,
		 double win_velonsity,
		 
		 bool use_repeat_points,  int n,//����� ������� ������� ( ����� 0 � ����)
		 double minimum_of_signal, 

		 double k,	
		 int delim,

		 size_t level_of_signal, 
		 char * name_suffics,

#if _USE_WINSURF_
		 SurfDoc * doc, 
		 Collection * pcurrent_colomn_graphics_collection,
#endif
		 FILE * stream_com_raz_pos_dima_,
		 FILE * stream_com_raz_neg_dima_,
		 FILE * stream_com_raz_pos_,
		 FILE * stream_com_raz_neg_
		 );

void LocalsMaker(
				 double quantil_naklony, 
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				 size_t icol, //����� �������
				 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
				 vector<double>& X, 
				 vector<double>& Y, 
#else
				 vector<double>& t, 
#endif
				 vector<double>& in,
				 vector<size_t>& vi,
				 double k,	
				 int delim,
#if _USE_WINSURF_
				 SurfDoc * doc, 
				 COLLECTION * pcollection_,
				 COLORREF color,
#endif
				 FILE *stream_less,
				 FILE *stream_more
				 );


void SticksMaker(
				 double quantil_naklony, 
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				 size_t icol, //����� �������
				 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
				 vector<double>& X, 
				 vector<double>& Y, 
#else
				 vector<double>& t, 
#endif
				 vector<double>& in,
				 vector<size_t>& vi,
				 double k,	
				 int delim,
#if _USE_WINSURF_
				 SurfDoc * doc, 
				 COLLECTION * pcollection_,
				 COLORREF color,
#endif
				 FILE *stream_less,
				 FILE *stream_more
				 );


void DoVerticalAutoCorrelation(int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
							   int step,
							   int wlen,// = 10;//����� ���� ����������
							   //Collection * pcollection,
							   vector<vert_korr_points> * vvkp, 
							   vector<profile_interval> & profile_intervals,
							   vector<string> * pnames_of_colomns,
							   vector<size_t>& original_col_numbers, 
							   size_t c1, size_t c2,
							   int reverse1, int reverse2,
							   int delim);
void DoVerticalCorrelation(int wlen,// = 100;//����� ���� ����������
						   Collection * pcollection,
						   vector<vert_korr_points> * vvkp, 
						   vector<profile_interval> & profile_intervals,
						   vector<string> * pnames_of_colomns,
						   vector<size_t>& original_col_numbers, 
						   size_t c1, size_t c2,
						   int reverse1, int reverse2,
						   int delim);

void DoGorizontalCorrilation(double k,
							 int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
							 int step,
							 vector<vert_korr_points> * vvkp,
							 vector<vector<double> >& v, 
#if SOURCE_COORDINATES_3D
							 vector<double>& X, 
							 vector<double>& Y, 
#else
							 vector<double>& t, 
#endif
							 vector<string> * pnames_of_colomns,
							 vector<size_t>& original_col_numbers, 
							 int rows, size_t c1, size_t c2,
							 int reverse1, int reverse2,
							 int delim);

bool ReadProfileFile( 
				  char * sz_path_to_file, char * current_directory, char* filename, 
				  bool consol, 
				  AutoBuildProfile * p_auto_build_profile,
				  auto_build_parametrs& ab,
				  int& rows, int& cols,
				  vector<bool>& use_col,
				  vector<size_t>& original_col_numbers,
				  vector<string> * pnames_of_colomns,
				  vector<vector<double> >& v,
				  vector<vector<double> >& w,
#if SOURCE_COORDINATES_3D
				  vector<double>& X,
				  vector<double>& Y,
				  vector<double>& Z,
#else
				  vector<double>& t,
#endif
				  int num_col,
				  int delim);

bool BuildingProfile(vector<vector<vector<vert_korr_points> > >& vvvvkp,
					 vector<profile_interval> & profile_intervals,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<vector<double> >& v, 
					 vector<vector<double> >& w, 
#if SOURCE_COORDINATES_3D
					 vector<double>& X, 
					 vector<double>& Y, 
#else
					 vector<double>& t, 
#endif		
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int rows, int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename,
					 bool is_reverse,
					 int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
					 int step, 
					 int wlen_auto
				  );
bool BuildingProfile2(vector<vector<vector<vert_korr_points> > >& vvvvkp,
					  vector<profile_interval> & profile_intervals,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename,
					 bool is_reverse,
					 int wlen
				  );


void BuildGrid(short crd_type,// 0 - x, 1 - y, 2 - profile_len
			   short value_type,// 1 - korr_k;  // ����������� �������������� ����������
								// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
								// 3 - korr_k3; // ����������� ������������ ��������������
			   Collection * pcollection,
			   vector<vert_korr_points> * vvkp,
			   vector<profile_interval> & profile_intervals,
			   vector<string> * pnames_of_colomns,
			   vector<size_t>& original_col_numbers, 
			   double xSize, double ySize, double max_glubina, 
			   size_t c1, size_t c2,
			   int reverse1, int reverse2);

void BuildGrid(char * file_grd,
			   vector<double> &vX,			
			   vector<double> &vY,			
			   vector<double> &vZ,			
			   vector<double> &vK,			
			   double xSize, double ySize, double max_glubina, 
			   Collection * pcollection
			   );

void
GetProfileDirection(vector<double> & X,
					vector<double> & Y,
					vector<double> & Z,
					double & min__x, double & min__y, double & min__z,
					double & max__x, double & max__y, double & max__z,
					double & delta__x, 
					double & delta__y);

struct MyMethodsData
{
	long increaser_pw;
	double k_oslablenie;
	// ��������� ����� � ��������
	int pw_rcd;

	char fn_operator_spm[4096];
    char fn_operator_wav[4098];
	char fn_min_sq_mat[4098];
	char fn_Lt[4098];
	// Nr ����� S ������������� �� ���������
	// Nc ����� S ������������� �� �����������
	long Nr, Nc;
	long rows; // ����� ����� � ������������� ��������� �� ���������
	long cols; // ����� ����� � ������������� ��������� �� �����������
	double x0; double y0; // ������ �������
	double z0;// ��������� ������ �����������
	// ��� ����� ������� �� X � �� Y
	// ��� ����� ������������� ��������� �� z (�������)
	double delta_x; double delta_y; double delta_z; 
	// ������ ������� �� X � �� Y
	double delta__x; double delta__y;
};

struct sourse_power_model
{
	double w0,w05,w1,w2;
	sourse_power_model()
	{
		w0 = w05 = w1 = w2 = 0.0;
	}
	double Apply(double hi)
	{
		return (w0 + w05 * sqrt(hi) + w1 * hi + w2 * hi * hi);
	}
};

struct MyMethodsData3
{
	long increaser_pw;
	double k_oslablenie;
	int smoof_power;

	int iter_save;

	//===========================
	int noise_color;
	double nju_min, nju_max;//Hz
	double ro;//Om*m
	//===========================

	// ������� ��������� �������������� ��������
	double pw_dnp;// = 2;

	bool use_norm_w; // ������������� ���� � ������� sols_mean
	bool use_norm_k;
	double norm_k_part;
	bool use_norm_k_on_every_iteration;
	int wave_type;

	double dXYZ_part;// �� ������ �������� �� ���� �� ������ ������� �� ������������������� �������, � ����� ���

    //����������� ��������, ������� �������� � �������� ������ ������    
	//double min_value = 0.03;
	double min_value;// = 1e-16;

	// dx/DZ=dy/DZ (for example 2)
	double dx_and_dy_per_DZ;
	bool granicy_kak_glubina;

	sourse_power_model spm;

	// ��������� ������� � �����
	int pw_pcd;

	char fn_operator_spm[4096];
	char fn_operator_transponed[4096];
    char fn_operator_wav[4098];
	char fn_min_sq_mat[4098];
	char fn_Lt[4098];

	vector<string> fnames_Lt;
	bool to_calculi_holesski;// else calculi LUP

	bool save_min_sq_grid;
	bool save_operator_grid;

	vector<string> fnames_L;
	vector<string> fnames_U;
	vector<string> fnames_P;

	int alpha_mode;

	int n_alpha;// ����� ����� �������������
	vector<double> v_alpha;// = 0.001;
	double alpha_min_sq;// = 0.001;
//	double alpha_holesski;// = 0.001;
	long j_start;// = 0;

	// Nr ����� S ������������� �� ���������
	// Nc ����� S ������������� �� �����������
	long Nr, Nc, Np;
	long rows; // ����� ����� � ������������� ��������� �� ���������
	long cols; // ����� ����� � ������������� ��������� �� �����������
	long pages;
	double x0; double y0; // ������ �������
	double z0;// ��������� ������ �����������
	double z_min;// ��������� ������ ������� ����
	// ��� ����� ������� �� X � �� Y
	// ��� ����� ������������� ��������� �� z (�������)
	double delta_x; double delta_y; double delta_z; 
	// ������ ������� �� X � �� Y
	double delta__x; double delta__y; double delta__z;

	bool to_povorot;
	bool need_crd_projection;
	//  ��������� ����� ������ ������� ���������� �������
	double vX0;
	double vY0;
	double ugol;


	bool have_pereopredelen_system;

};

#include ".\..\array\src\wav.h"

struct Wavelet2D
{
	//WF_DAUBECHIES
	//WF_SYMLETS
	//WF_COIFLETS

	// Selection of wavelet R
	int wf_r;// = WF_COIFLETS; // ���� ��������
	int order_r;// = 1; // ������� ��������
	int orderBiorthogonalDecomposition_r;// = 0; // ������� ��������
	vdouble dh_r, dg_r, rh_r, rg_r;
	int left_g_r, right_g_r, left_h_r, right_h_r;
	
	int wf_c;// = WF_COIFLETS; // ���� ��������
	int order_c;// = 1; // ������� ��������
	int orderBiorthogonalDecomposition_c;// = 0; // ������� ��������	
	vdouble dh_c, dg_c, rh_c, rg_c;	
	int left_g_c, right_g_c, left_h_c, right_h_c;
};

struct Wavelet3D
{
	//WF_DAUBECHIES
	//WF_SYMLETS
	//WF_COIFLETS

	// Selection of wavelet R
	int wf_r;// = WF_COIFLETS; // ���� ��������
	int order_r;// = 1; // ������� ��������
	int orderBiorthogonalDecomposition_r;// = 0; // ������� ��������
	vdouble dh_r, dg_r, rh_r, rg_r;
	int left_g_r, right_g_r, left_h_r, right_h_r;
	
	int wf_c;// = WF_COIFLETS; // ���� ��������
	int order_c;// = 1; // ������� ��������
	int orderBiorthogonalDecomposition_c;// = 0; // ������� ��������	
	vdouble dh_c, dg_c, rh_c, rg_c;	
	int left_g_c, right_g_c, left_h_c, right_h_c;
	
	int wf_p;// = WF_COIFLETS; // ���� ��������
	int order_p;// = 1; // ������� ��������
	int orderBiorthogonalDecomposition_p;// = 0; // ������� ��������	
	vdouble dh_p, dg_p, rh_p, rg_p;	
	int left_g_p, right_g_p, left_h_p, right_h_p;
};

void DoMyMethod2(FILE * description, 
				 MyMethodsData& mmd,				 
				 auto_build_parametrs& ab,
				 vector<double> & X,
				 vector<double> & Y,
				 vector<double> & Z, // ��������� ��������� - ����� �������
				 vector<double> & signal,
				 string name);

//#define SparseRow sparse_row
#define SparseRow sparse_row_simple
class operator_element
{
public:
	//j - ������ � ������� ���������, ���� � ����� ���������� ������� ������� V,W � ���������� �������� X,Y,Z
	//i - ������� � ������� ������ ������, ���� � ����� ����� ������� � ����� � ���������� ���������� � ����
	// ������ � ������ ������� ��������� ������ ������
	// for (p = 0; p < pages; p++) 
	//    for (r = 0; r < rows; r++) 
	//       for (C = 0; C < cols; C++) 
	//          i = p * rows * cols + r * cols + C;
	// zi = z_min + p * delta_z;
	// yi = y0 + r * delta_y;
	// xi = x0 + C * delta_x;
	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	// double z_min = z0 - pages * delta_z;
	static double Z0, Z_min, Pw_Dnp;
//	double Out(double ax, double ay, double ay)
//	{
//		// ���� ����� ������������ �� �������� � �������� � ������
//		double phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
//		// ����������� ������ ��������� ��������������
//		double phi_k = pow(sin(phi), pw_dnp);
//		return phi_k;
//	}
size_t col;
double val;
	double R;// ���������� �� ��������� �� ��������
	operator_element(size_t c, double v) : col(c), val(v){}
	operator_element() : col(0), val(0.0){}
	//operator_element(const operator_element & r) : col(r.col), val(r.val){}
	virtual ~operator_element(){}
};
class OperatorRow : public std::vector<operator_element>
{
public:
	bool put(size_t j, double a)
	{
		if (a == 0.0)
			return false;
		operator_element tmp(j,a);
		this->push_back(tmp);
		return true;
	}
	/*double ScalarProduct(vector<double>& x)
	{
		double product = 0.0;
		//size_t x_size = x.size();
		vector<operator_element >::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			//size_t c = (*it).col;
			//if (c < x_size)//����� ��������, ����� ���������� ������������� ���������
			//{
				product += (*it).val * x[(*it).col];
			//}
		}
		return product;
	}
	
	void Reconstruct_b_by_my_as_part_of_symmetric_matrix_row(vector <double> & b_rec, long r, vector<double>& x)
	{
		//size_t x_size = x.size();
		vector<operator_element>::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			size_t c = (*it).col;
			//if (c < x_size)//����� ��������, ����� ���������� ������������� ���������
				b_rec[r] += (*it).val * x[c];
			if (r != c)
			{
				//if (r < x_size)
					b_rec[c] += (*it).val * x[r];
			}			
		}
	}
	
		
	double ScalarProduct_fast(OperatorRow & r2)
	{
		double product = 0.0;

		std::vector<operator_element >::iterator n1 = this->begin();
		std::vector<operator_element >::iterator n2 = r2.begin();

		while( n1 != this->end() && n2 != r2.end() )
		{
			size_t c1 = (*n1).col;
			size_t c2 = (*n2).col;

			if (c1 == c2)
			{
				product += (*n1).val * (*n2).val;

				n1++;
				n2++;
				continue;
			}
			if (c1 < c2)
			{
				n1++;
			}
			else
			{
				n2++;
			}
		}
		return product;
	}*/
	friend Archive& operator <<(Archive& ar, operator_element& ob);
	friend Archive& operator >>(Archive& ar, operator_element& ob);

	/*void InverseSave(Archive& ar)
	{
		long cc;
		double value;
		vector<operator_element >::reverse_iterator it;
		for(it = this->rbegin(); it != this->rend(); it++)
		{
			long cc = long((*it).col);
			double value = (*it).val;
			ar << cc;
			ar << value;
		}
		//������� ����� ������
		cc = -1;
		value = 0.0;
		ar << cc;
		ar << value;

	}*/
};


void DoMyMethod3(FILE * description,
				 double k_oslablenie,
				 auto_build_parametrs& ab,
				 vector<double> & X,
				 vector<double> & Y,
				 vector<double> & Z, // ��������� ��������� - ����� �������
				 double z0,// ��������� ������ �����������
				 vector<double> & signal,
				 string name);


void DoMyMethod2W(FILE * description, 
				  MyMethodsData& mmd,
				  Wavelet2D& w2,
				  auto_build_parametrs& ab,
				  vector<double> & X,
				  vector<double> & Y,
				  vector<double> & Z, // ��������� ��������� - ����� �������
				  //string name,
				  bool to_fill_matrix);

void DoInverseAndFillGrid2W(MyMethodsData& mmd,
							Wavelet2D& w2,
							vector<double> & signal,
							string name
							);
#define WITH_2D 0

void UseOneOfMyMethods(int type, // ��� ������ ������
					   bool granicy_kak_glubina,
#if WITH_2D
					   bool use_only_2D,
#endif
					   int & cols,
					   auto_build_parametrs& ab,
					   vector<double> & X,
					   vector<double> & Y,
					   vector<double> & Z, // ��������� ��������� - ����� �������
					   vector<vector<anten_direction> > & A,
					   vector<double> & vModul,
					   vector<vector<double> > & v,
					   vector<string> & names_of_colomns,
					   vector<size_t> & original_col_numbers,

					   vector<vector <double> > & rec_signals,
					   vector <double> & rec_modul
					   );

#endif /*PEAKS_SEARCH_H*/
