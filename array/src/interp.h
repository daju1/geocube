#if !defined(_INTERP_H_)
#define _INTERP_H_

#include <vector>
using namespace std;

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#else
#include "mywindows.h"
#endif

class vdouble;
struct Grid;
struct Grid4;

int cubicInterp3(int nx, int ny, int nz, double ***x,double ***y,double ***z,double ***v, 
				 int nxi, int nyi, int nzi, double ***xi,double ***yi,double ***zi,double ***F,double ExtrapVal);
int cubicInterp2(int nx, int ny, double **x,double **y,double **z, 
				 int nxi, int nyi, double **xi,double **yi,double **zi,double ExtrapVal);
int linearInterp2(int nx, int ny, double **x,double **y,double **z, 
				 int nxi, int nyi, double **xi,double **yi,double **zi,double ExtrapVal);

struct prostranstven_index
{
	long ii;
	long jj;
	long k;
	double x;
	double y;
	double z;
};
enum points_sort_mode
{
    point_with_distance_points_sort_mode_by_dist,
    point_with_distance_points_sort_mode_by_angle
};
struct point_with_distance
{	
	double x;
	double y;
	double z;
	double dist;
	double angle;



	static points_sort_mode s_points_sort_mode;
#if 1
	bool operator<(const point_with_distance& rhs)
	{
		switch(point_with_distance::s_points_sort_mode)
		{
                case point_with_distance_points_sort_mode_by_dist:
			return dist < rhs.dist;
                case point_with_distance_points_sort_mode_by_angle:
			return angle < rhs.angle;
		}
	}
	bool operator>(const point_with_distance& rhs)
	{
		switch(point_with_distance::s_points_sort_mode)
		{
                case point_with_distance_points_sort_mode_by_dist:
			return dist > rhs.dist;
                case point_with_distance_points_sort_mode_by_angle:
			return angle > rhs.angle;
		}
	}
#else
	bool inline operator<(const point_with_distance& rhs)
	{
		return dist < rhs.dist;
	}
	bool inline operator>(const point_with_distance& rhs)
	{
		return dist > rhs.dist;
	}
#endif
};
struct griddata_2_param
{
	size_t max_len;
	int dist_fun_number;
	double pw;
	double add_pw;
	double delta_phi;
};
void FillDefaultParam(griddata_2_param &param);

struct finite_element_par
{
	bool add_non_fault;
	double alpha_non_fault;
	bool add_first_der_n;
	double alpha_der_n;
	//???????????? ??????????
	bool add_first_der_x_or_y;
	bool add_first_der_x;
	bool add_first_der_y;
	double alpha_der_xy;

};

enum len_biss_type
{
    griddata_3_param_len_biss_type_user_defined = 0,
    griddata_3_param_len_biss_type_min_edges_len,
    griddata_3_param_len_biss_type_mean_edges_len,
    griddata_3_param_len_biss_type_median_edges_len,
    griddata_3_param_len_biss_type_max_edges_len
};
struct griddata_3_param
{
	bool use_contour;
	// ???????? ???????????????????????????????? ???????????????????????? "????????????" ?????????????????????????? ?? ???????????????????????? ????????????
	// 0 - ???????????????????????????????? ???? ????????????????????
	// 1 - ???????????????????????????????? ???? "????????????????" ??????????????????
	// 2 - ???????????????????????????????? ???? ?????????? ???????????????? ??????????????????
	// ??.??. 3 - ???????????????????????????????? ???? "????????????????????????" ??????????????????
	int ftf; // filtering of triangulation flag

	// ?????????????? ????????????????????????:
	// ???????????????????? ??????????????????????????
	int order_t;// = 3;
	// ?? ?????????????????? ??????????????????
	int order_c;// = 3;

	// ?????????????????????????????????? ???????????????????????? alpha, ?? ?????????????? ?????????????? 
	// ???? ?????????? ?????????????????? ???????????????????????? ?? ???????????????? ????????????????????????

	// alpha ?? ?????????? ???????????????????????? ???? ???????????????????????? ???????????????????????? ?? ?????????????? ???????????????? 
	//		(???????? ?????????????????????? ?????????? "????????????????????????" ?????????????????????? ?????????? ????????????????)
	// alpha ?? ???????????????? ???????????????????????? ???? ???????????????????????? ???????????????????????? ?? ???????????? ???????????????? 
	//		(???????? ?????????????????????? ?????????? "????????????????????????" ?????????????????? ????????????????)

	// ?????? ???????????????????????? ?????????????????? ?? ???????????????????? ??????????????????????????
	double alpha_t0;// = 0.1;
	double alpha_t1;// = 0.0;	
	double alpha_tn;// = 0.1;	


	// ?????? ???????????????????????? ?????????????????? ?? ?????????????????? ??????????????????
	double alpha_c0;// = 0.1;
	double alpha_c1;// = 0.0;
	double alpha_cn;// = 0.1;

    // ?????????????????????? ???????????????? ??????????????????????
	// ???????? ????????, ?????????????????????? ???? ????????????????????
	// ???????? ??????????????????????????, ???????????????????? ?????????????????????? ???? ???????????? "?????????????????????? ????????????????", ?????????? dij ???????????????????? ???????????? ????????
	// ???????? ??????????????????????????, ?????????? ???? ???????????? ?????????????????? ???????????????????? ???????????????????? ???????????????????????????????? ???????????????? ?????? ???????????? ?????????????????? ???? ?????????????????? ?? ?????????????? ??????????
	long dij;// = 1;
	//double row_weight;// = 1.0;

	finite_element_par fep;
	finite_element_par fepbc;

	int slau_method; // = 1; SLAU9(0), SLAU_excl(1)


	len_biss_type m_len_biss_type;
	double len_biss;


};

void FillDefaultParam(griddata_3_param &param);

//int griddata(HWND hwndParent, vdouble& x, vdouble& y, vdouble& z, vdouble& xi, vdouble& yi, vdouble& zi);
int griddata_v4(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void * _param, bool to_allocate = true);
int griddata_2(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void * _param, bool to_allocate = true);
int griddata_3(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void * _param, bool to_allocate = true);
int griddata(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid,
			 vdouble * xi, vdouble * yi, vdouble * zi, bool to_allocate = true);
int griddata(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void *, bool to_allocate = true);
int griddata4(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, vector<double>& v, 
			 Grid4 * grid, void *, bool to_allocate);
void MultiplyCube(Grid4 * grid, const double m);
void FilterGridMinMax(vector<double>& z, Grid * grid, double part_of_range_low, double part_of_range_high);
void FilterGridMinMax(vector<double>& v, Grid4 * grid, double part_of_range_low, double part_of_range_high);
void FilterCubeMinMax(Grid4 * grid, double minv, double maxv);
class Line3D;
class CPoint3;
int getTriangulationContour(vector<double>& x, vector<double>& y, int ftf, bool use_biss, double len_biss, Line3D * outline, CPoint3 * base_point );

int correct_dublicate(vector<double>& x, vector<double>& y, vector<double>& z);
#endif //_INTERP_H_
