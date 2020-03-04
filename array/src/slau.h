
#if !defined(_SLAU_H_)
#define _SLAU_H_
#if defined (_MSC_VER) && !defined (QT_PROJECT)
#include <windows.h>
#else
#include <mywindows.h>
#endif

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std ;

#include "sparse_row.h"
#include "sparse_row_simple.h"
#include "sparse_row_map.h"

#if SPARSE_ROW_EX
void SaveMatrixMinMaxCol(vector<sparse_row>& a, char * dat_file);
#endif

template <class T>
T Mean(vector<T>& v) // Возврашает сумму квадратов элементов вектора
{
    T _Mean = 0;
    typename vector<T>::iterator it;
    for(it = v.begin(); it != v.end(); it++)
	{
		_Mean += (*it);
	}
	_Mean /= v.size();
	return _Mean;
}

template <class T>
T Disp(vector<T>& v) // Возврашает сумму квадратов элементов вектора
{
	T _Mean = Mean(v);
	T _Disp = 0.0, tmp;
    typename vector<T>::iterator it;
    for(it = v.begin(); it != v.end(); it++)
	{
		tmp = (*it) - _Mean;
		_Disp += tmp*tmp;
	}
	// несмещённая оценка Дисперсии
	_Disp /= v.size() - 1;
	return _Disp;
}

template <class T>
T Sum(vector<T>& v) // Возврашает сумму элементов вектора
{
    T _Sum = 0;
    typename vector<T>::iterator it;
    for(it = v.begin(); it != v.end(); it++)
	{
		_Sum += (*it);
	}
	return _Sum;
}

template <class T>
T SquareSum(vector<T>& v) // Возврашает сумму квадратов элементов вектора
{
    T _SquareSum = 0;
    typename vector<T>::iterator it;
    for(it = v.begin(); it != v.end(); it++)
	{
		_SquareSum += (*it) * (*it);
	}
	return _SquareSum;
}

template <class T>
T SquareSum(vector<T>& v1, vector<T>& v2) // Возврашает сумму квадратов элементов вектора

{
	T _SquareSum = 0;	
    typename vector<T>::iterator it1;
    typename vector<T>::iterator it2;
	for(it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end() && it2 != v2.end(); it1++, it2++)
	{
		_SquareSum += ((*it1)+(*it2)) * ((*it1)+(*it2));
	}
	return _SquareSum;
}

template <class T>
T ScalarProduct(vector<T>& v1, vector<T>& v2)// Возврашает скалярное произведение векторов
{
	T _ScalarProduct = 0;	
    typename vector<T>::iterator it1;
    typename vector<T>::iterator it2;
	for(it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end() && it2 != v2.end(); it1++, it2++)
	{
		_ScalarProduct += (*it1) * (*it2);
	}
	return _ScalarProduct;
}

void print_slau(vector<vector<double> >& a,
     vector<double>& b, char *);
void print_slau(vector<sparse_row>& a,
     vector<double>& b, char * s);
bool lesgausssolve(vector<vector<double> > a,
     int n,
     vector<double> b,
     vector<double>& x,
     double epsilon);
// здесь число строк может быть больше числа столбцов на случай, 
// если имеются линейно-зависимые строки
bool lesgausssolve(vector<vector<double> > a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon);
// здесь число строк может быть больше числа столбцов на случай, 
// если имеются линейно-зависимые строки
// матрица может быть переопределена
// на каждой итерации ищется максимальный по модулю элемент
bool lesgausssolve_find_max(vector<vector<double> > a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon);

bool lesgausssolve(vector<sparse_row> a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon);

bool lesgausssolve_find_max(vector<sparse_row> a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon);

bool lesgausssolve_find_max_norm(vector<vector<double> > a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon);

bool Tichonov(vector<vector<sparse_row_element<double> > > & A,
						  size_t cols,
						  vector<double> & b,
						  vector<double> & x, bool AlphaNonZero);

bool SLAU(vector<vector<sparse_row_element<double> > > & A,
						  size_t cols,
						  vector<double> & b,
						  vector<double> & x);
// накладываем дополнительные условия на решение системы уравнений
bool SLAU(vector<sparse_row > & A,
		  size_t cols,
		  vector<double> & b,
		  vector<double> & x, 
		  void (*pSlauAdditionalConditions)(
		  vector<double> & x,
		  double & add_F,
		  vector<double> & add_dFdx,
		  vector<double> & add_d2Fdx2,
		  void * _param),
		  void * _param);
// здесь итерационный алгоритм подстройки 
// подстраивается весь вектор сразу
bool SLAU(vector<sparse_row > & A,
		  size_t cols,
		  vector<double> & b,
		  bool to_init,
		  bool rand_not_zero_init,
		  int	maxq, 
		  vector<double> & x,
		  bool echo);
bool SLAU_block(vector<sparse_row > & A,
		  size_t cols, size_t  block_size,
		  vector<double> & b,
		  vector<double> & x);
// здесь итерационный алгоритм подстройки 
// подстраивается вектор поэлементно
bool SLAU2(vector<sparse_row > & A,
						  size_t cols,
						  vector<double> & b,
						  bool to_init,
						  bool rand_not_zero_init,
						  vector<double> & x);
size_t GetRealColsNumber(vector<sparse_row > & A,
						 size_t cols);

// решение разреженной системы методом наименьших квадратов 
// с последующим применением разложения Холесского
bool SLAU3(vector<sparse_row > & a,
		  size_t cols,
		  vector<double> & b,
		  vector<double> & x);
bool SLAU3(vector<sparse_row_simple > & a,
		  size_t cols,
		  vector<double> & b,
		  vector<double> & x);
// тут мы пытаемся "задавить" те элементы решения для которых (i%nk > lc)
// путём избирательного введения регуляризационного коэффициента 
// прибавляя этот коэффициент к тем диагональным элементам 
// квадратной положительно определённой симметричной матрицы 
// наименьших квадратов, которые соответствуют тем элементам решения
// которые мы хотим "задавить" то есть уменьшить в модуле

// это мы используем для того, чтобы уменьшить влияние 
// тех коэффициентов полинома, которые имеют вторую и третью степень
// чтобы уменьшить "раздувание" грида

bool SLAU4(vector<sparse_row > & a,
		  size_t cols, size_t nk, size_t lc,
		  vector<double> & b,
		  vector<double> & x);
#if SPARSE_ROW_EX
// тут мы при построении матрицы наименьших квадратов
// уменьшаем роль тех строк в исходном уравнении vector<sparse_row > & a,
// которые отвечают за первую и вторую производную

bool SLAU5(vector<sparse_row > & a,
		  size_t cols,
		  vector<double> b,
		  vector<double> & x);
#endif
// здесь мы добиваемся минимизации расстояния от каждой nk точки решения 
// до значений вектора base_points_z
bool SLAU6(vector<sparse_row > & a,
		  size_t cols, size_t nc, vector<double> & base_points_z,
		  vector<double> & b,
		  vector<double> & x);
#if SPARSE_ROW_EX
// тут мы при построении матрицы наименьших квадратов
// уменьшаем роль тех строк в исходном уравнении vector<sparse_row > & a,
// которые отвечают за первую и вторую производную (as in SLAU5)
// и добиваемся минимизации расстояния от каждой nk точки решения 
// до значений вектора base_points_z (as in SLAU6)
// SLAU7 = SLAU5 + SLAU6
bool SLAU7(vector<sparse_row > & a,
		  size_t cols, size_t nk, vector<double> & base_points_z,
		  vector<double> & b,
		  vector<double> & x);
#endif

// здесь необходимо задавать первое приближение вектора решения
// (это могут быть коэффициенты, обеспечивающие линейную интерполяцию)
// и регуляризационный коэффициент alpha, с помощью которого данный алгоритм 
// будет приближать конечное решение к исходному
// (в нашем случае мы будем стараться приближаться к линейной интерполяции)
bool SLAU8(vector<sparse_row > & a,
		  size_t cols, double alpha,
		  vector<double> & b,
		  vector<double> & sol);

// тоже, но регуляризационный коэффициент в виде вектора соразмерного вектору решения, 
// для того, чтобы более гибко подходить к вопросу приближиния
bool SLAU9(vector<sparse_row > & a,
		  size_t cols, vector<double> & alpha,
		  vector<double> & b,
		  vector<double> & sol);

// перебираем все точные уравнения
// из каждого точного уравнения последнюю значимую переменную решения выражаем через остальные
// и исключаем из всех остальных строк уравнений

// решаем вторую систему из неточных строк 
// и неисключёных неизвестных методом Холесского

// затем из точных уравненй исключаем sol2 - решение второй системы из неточных строк
// перенося их в правую часть и получаем новую систему, 
// для решения точных уравнений методом Гаусса

// первый параметр - число точных уравнений, которые идут в свписке уравнений первыми
// этот метод используется в построении плавной поверхности, натянутой на триангуляционные точки
// он хорош тем, что в результате получается поверхность точно проходящая через опорные точки
// (в отличие от предыдущего метода SLAU9)
// так как мы уравнения прохождения через опорные точки объявляем точными уравнениями

bool SLAU_excl(size_t prec_eqns,
			   vector<sparse_row > & a,
			   size_t cols, vector<double> & alpha,
			   vector<double> & b,
			   vector<double> & sol);

bool Tichonov(size_t cols, vector<sparse_row> & A,						  
						  vector<double> & b,
						  vector<double> & x, bool AlphaNonZero);
bool Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  vector<double> & valpha);
#if SPARSE_ROW_EX

//  то же, но используется так же увеличенный вес уравнений, отвечающих 
bool SLAU10(vector<sparse_row > & a,
		  size_t cols, vector<double> & alpha,
		  vector<double> & b,
		  vector<double> & sol);
#endif

// решение разреженной системы методом наименьших квадратов 
// с последующим применением разложения Холесского
// однако к диагональным элементам разлагаемой матрицы 
// приплюсовывается alpha. Таким образом осуществляется 
// регуляризация Тихонова - то есть к функционалу 
// прибавляется сумма квадратов вектора решения, умноженная на alpha
bool SLAU_Tichonov(vector<sparse_row > & a,
		  size_t cols, double alpha,
		  vector<double> & b,
		  vector<double> & sol);

// метод Тихонова для полной матрицы
bool Tichonov(vector<vector<double> > & A,
						  size_t cols, double alpha, // регуляризационный коэффициент						  		
						  bool rand_not_zero_init,
						  int maxq,
						  vector<double> & b,
						  vector<double> & x);


void SaveSparseMatrixAsDat(vector<sparse_row > & m, const char *name);
void SaveSparseMatrixAsGrid(vector<sparse_row > & m, size_t cols, const char *name);
#if defined (_MSC_VER) && !defined (QT_PROJECT)
void SparseStructureToMetafile(char * fn_spm, char * fn_emf = NULL);
#endif
bool solve_using_Holesski_tria_matrixes(vector<sparse_row > L, vector<double> & B, vector<double> & x);
bool tria_solve_of_down_and_up(const char * fn_Lt, vector<double> b, vector<double> & sol);
bool tria_solve_of_down_and_up(const char * fn_L, const char * fn_U, vector<double> b, vector<double> & sol);

void Transponate(vector<sparse_row > & a, size_t cols, vector<sparse_row> & at);
void Transponate(vector<sparse_row_simple > & a, size_t cols, vector<sparse_row_simple> & at);
void Transponate(vector<sparse_row_map > & a, size_t cols, vector<sparse_row_map> & at);

#define BUFF_SIZE 1024

template <class T> bool StoreMatrix(char * filename, vector<T>& m, long cols)
{
	char buff[BUFF_SIZE];
/*	TCHAR filter[] =     
		TEXT("Sparse Martix File (*.smf)\0*.smf\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(filename, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, filename, filter, nFilterIndex) == S_OK)*/
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Store martix\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		long rows = m.size();

		ar << rows;
		ar << cols;

		for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}
		ar.Close();
		f.Close();

	}
	return true;
}

template <class T> void LoadMatrix(char * filename, vector<T>& m, long & cols)
{
	char buff[BUFF_SIZE];

	AFile f;
	if( f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) 
	{
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			//ar.ReadString(str2, 255);
			//ar.Read((unsigned char*)m2,sizeof(m2));
			long _cols, _rows;
			ar >> _rows;
			ar >> _cols;

			m.resize(_rows);
			for (long r = 0; r < _rows; r++)
			{
				ar >> m[r];
			}
			cols = _cols;
		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
/*		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}*/
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	else
	{
		MessageBox(0, "Load Matrix\nUnable to open file" , filename, MB_OK);
	}


}

#endif
