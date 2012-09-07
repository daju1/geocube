#include "./stdafx.h"

#define SOURCE_COORDINATES_3D 1
#define SOURCE_COORDINATES_3D_ICOL_J1_J2 1

void GetLocalExtremums(vector<double>& in, vector<size_t> * vi_lock_min, vector<size_t> * vi_lock_max);
void GetLocalExtremums(vector<double>& in, vector<size_t>& vi_in,
					   vector<size_t> * vi_lock_min, vector<size_t> * vi_lock_max);
void Filtration(vector<double>& in, 
				vector<vector<size_t> >& vvi_lock_min, 
				vector<vector<size_t> >& vvi_lock_max);
// Вычисление локальных экстремумов, как точек перегиба
// точки перегиба - это точки локальных экстремумов во второй производной
// Точка перегиба, которая соответствует локальному минимуму,
// определяется как локальный максимум второй производной
// Точка перегиба, которая соответствует локальному максимуму,
// определяется как локальный минимум второй производной
void GetLocalExtremums(
#if SOURCE_COORDINATES_3D
					   vector<double>& X, 
					   vector<double>& Y, 
#else
					   vector<double>& t, 
#endif
					   
					   vector<double>& in, vector<size_t>& vi_in,
					   vector<size_t> * vi_lock_min, vector<size_t> * vi_lock_max);
void Filtration(bool allow_sd_limit, double quantil, 

#if SOURCE_COORDINATES_3D
				vector<double>& X, 
				vector<double>& Y, 
#else
				vector<double>& t, 
#endif
				
				vector<double>& in, 
				vector<vector<size_t> >& vvi_lock_min, 
				vector<vector<size_t> >& vvi_lock_max);