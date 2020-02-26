#if !defined(_VDOUBLE_H)
#define _VDOUBLE_H

#define PI		3.14159265358979323846
#define SD      (sizeof(double)) // - проверить для данного компьютера
//#define COPY_CONSTR false
#define MEMORY_ERROR /*AfxMessageBox("Error using vdouble: not enough memory\n");*/return vdouble(0);
#define MEMORY_ERROR0 /*AfxMessageBox( "Error using vdouble: not enough memory\n");*/return;
#define MEMORY_ERROR2 /*AfxMessageBox( "Error using vdouble: not enough memory\n");*/return 1.0e300;

#define  DEBUGGING false
#include <cfloat>
#include "complex.h"
#include <math.h>
#include "Vector.h"


#include "stdafx.h"

double Median(double *p, int len); // Возврашает среднее арифметическое элементов вектора
double Quantil(double qu, double *p, int len); 
double Median_sort(double *p, int n); // Возврашает среднее арифметическое элементов вектора


extern Vector<int> sequence(int i1, int i2); // Возвращает последовательность целых чисел от i1 до i2
extern double **AllocDoubleMat (int rows, int cols);
extern int **AllocIntegerMat (int rows, int cols);
extern double ***AllocDouble3DMat (int npages, int nrows, int ncols);
extern int ***AllocInteger3DMat (int npages, int nrows, int ncols);
extern void FreeDouble3DMat(double *** v);
extern void FreeInteger3DMat(int *** v);

extern void FreeDoubleMat(double ** v);
extern void FreeIntegerMat(int ** v);

class vdouble;


vdouble inline operator+(const vdouble& ob1, const vdouble& ob2);
vdouble inline operator+(const double& a, const vdouble& ob2);
vdouble inline operator+(const vdouble& ob1, const double& a);

vdouble inline operator-(const vdouble& ob1, const vdouble& ob2);
vdouble inline operator-(const double& a, const vdouble& ob2);
vdouble inline operator-(const vdouble& ob1, const double& a);
/*
vdouble inline operator^(vdouble& ob1, vdouble& ob2);
vdouble inline operator^(const double& a, vdouble& ob2);
vdouble inline operator^(vdouble& ob1, const double& a);
	*/
vdouble inline pow(const vdouble& ob1, const vdouble& ob2);
vdouble inline pow(const double& a, const vdouble& ob2);
vdouble inline pow(const vdouble& ob1, const double& a);

vdouble inline operator*(const vdouble& ob1, const vdouble& ob2);
vdouble inline operator*(const double& a, const vdouble& ob2);
vdouble inline operator*(const vdouble& ob1, const double& a);

vdouble inline operator/(const vdouble& ob1, const vdouble& ob2);
vdouble inline operator/(const double& a, const vdouble& ob2);
vdouble inline operator/(const vdouble& ob1, const double& a);

//vdouble inline operator,(vdouble& ob1, vdouble& ob2);
//vdouble inline operator,(const double& a, vdouble& ob2);
//vdouble inline operator,(vdouble& ob1, const double& a);



	
vdouble inline operator+(const vdouble& ob);
vdouble inline operator-(const vdouble& ob);

vdouble inline log(const vdouble& ob);
vdouble inline log10(const vdouble& ob);
vdouble inline abs(const vdouble& ob);

vdouble inline acos(const vdouble& ob);
vdouble inline asin(const vdouble& ob);
vdouble inline atan(const vdouble& ob);
vdouble inline atan2(const vdouble& x, const vdouble& y);

vdouble inline cos(const vdouble& ob);
vdouble inline cosh(const vdouble& ob);
vdouble inline sin(const vdouble& ob);
vdouble inline sinh(const vdouble& ob);
vdouble inline tan(const vdouble& ob);
vdouble inline tanh(const vdouble& ob);
vdouble inline exp(const vdouble& ob);
vdouble inline sqrt(const vdouble& ob);

vdouble inline floor(const vdouble& ob);
vdouble inline ceil(const vdouble& ob);

vdouble inline linterp(const vdouble& x, const vdouble& y, vdouble& xx);
bool inline hist(vdouble& v, vdouble&  n, vdouble& x);
bool inline hist(vdouble& v, int N, vdouble&  n, vdouble& x);
bool inline hist2(vdouble& v1, vdouble& v2,int n1, int n2, vdouble&  n, vdouble& x1, vdouble& x2);
bool inline covar(vdouble& t,vdouble& v1, vdouble& v2,  vdouble& tcov, vdouble& cov);

Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2);
Vector<bool> inline operator>(const double& a, vdouble& ob);
Vector<bool> inline operator>(vdouble& ob, const double& a);

Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2);
Vector<bool> inline operator>=(const double& a, vdouble& ob);
Vector<bool> inline operator>=(vdouble& ob, const double& a);

Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2);
Vector<bool> inline operator<(const double& a, vdouble& ob);
Vector<bool> inline operator<(vdouble& ob, const double& a);

Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2);
Vector<bool> inline operator<=(const double& a, vdouble& ob);
Vector<bool> inline operator<=(vdouble& ob, const double& a);

Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2);
Vector<bool> inline operator==(const double& a, vdouble& ob);
Vector<bool> inline operator==(vdouble& ob, const double& a);

Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2);
Vector<bool> inline operator!=(const double& a, vdouble& ob);
Vector<bool> inline operator!=(vdouble& ob, const double& a);
	
vdouble inline fliplr(vdouble& ob);

void inline operator<<(vdouble& ob, const double& a);
void inline operator>>(const double& a, vdouble& ob);

#define VDOUBLE_MAX_DIMS				3

vdouble dsequence(double d0, double dstep, double dend);
vdouble dsequence(double d0, long Len, double dend);
vdouble dsequence(double d0, double dstep, long Len);

//#include <exception>
struct LagerStruct;
class vdouble // Класс массива вещественных чисел double
{
	friend class CGraph;
	friend class LagerModel;
private:
	int m_length; // Длина вектора
	int m_dims;
//	Vector<int> m_size;
	int m_size[VDOUBLE_MAX_DIMS];
	bool m_isgorizontal; // Флаг горизонтальности
	double *pD; // Указатель на одномерный массив вещественных 
			// чисел double
public:
	int GetSize(int dim);
	int GetDims();
	void Sequence(double d0, double dstep, double dend);
	void ReverseCovariation(vdouble& v1, vdouble& v2, int len);
	void Covariation(vdouble& v1, vdouble& v2, int len);
	static int m_nMaxDims;
	int idwt(int J, Vector<int>& ts, Vector<int>&  tau, vdouble &rh, vdouble &s);
	int idwt(int J, Vector<int>& new_t, int left, int right, vdouble &rh,Vector<int>& ts, vdouble &s, bool isLow);
	int dwt(int J, Vector<int>& t,
		 int left_h, int right_h, vdouble &dh,  
		 Vector<int>& ts, vdouble &s);
        int idwt(
				  int left, int right,
				  vdouble &rh, 
				  vdouble &s);
	int dwt(Vector<int>& t, Vector<int>& tsd, vdouble&dh, vdouble&s);
//	int dwt(int j, vdouble &dh, vdouble &dg, vdouble &s, vdouble &d);
	int b_reconstructor(vdouble& b, vdouble& tt, vdouble& xx, double t0); 	// реконструкция коэффициентов числителя передаточной функции 
			// по  известному знаменателю (*this)  
			// а также по отклику на delta - импульс в момент t0

	void Rand(double minBorder, double maxBorder);
	double FirstLocalMinFrom(int j);
	double FirstLocalMaxFrom(int j);
//	Vector<int> Size(){return m_size;}
	static unsigned int m_nConstructions; // Число раз выполнения конструкторов
	static unsigned int m_nDestructions; // Число раз выполнения деструкторов
	static size_t m_szMemory; // объём выделенной динамической памяти

	vdouble(); // Конструктор по умолчанию - создаёт объект вектора нулевой длины
	vdouble(const vdouble& src); // Конструктор копирования - создаёт объект вектора нулевой длины
	vdouble(int _length);// Конструктор - создаёт объект вектора заданной длины
	vdouble(double array[], int _length/* = sizeof(array)/sizeof(double)*/);// Конструктор - создаёт объект по массиву чисел double
	vdouble(double& array, int _length/* = sizeof(array)/sizeof(double)*/);// Конструктор - создаёт объект по массиву чисел double
	vdouble(int _length, const double& ra);// Конструктор - создаёт объект вектора заданной длины, присваивая всем элементам задаваемое значение
	int _printf(const char *name, bool asIntegers = false);//
	int Save(const char * filename);//
	int Write(const char * filename, const char *mode, const char *name , bool asIntegers = false);//
	int Load(const char * filename);//

	vdouble(int rows, int cols); // Конструктор двумерной матрицы
	vdouble(int rows, int cols, int tabs); // Конструктор трёхмерной матрицы
	vdouble(Vector<int>& vsize); // Конструктор многомерной матрицы

	void resize(int _length);// 
	void resize(int _length, const double& ra);// 
	void resize(int rows, int cols); // 
	void resize(int rows, int cols, const double& ra); // двумерной матрицы
	void resize(int rows, int cols, int tabs); // 
	void resize(Vector<int>& vsize); // 

	virtual ~vdouble(); // Деструктор выполняет освобождение памяти
	void OnDestroy(); // Деструктор выполняет освобождение памяти

	friend vdouble inline zeros(int _length);// Создаёт вектор заданной длины из нулей
	friend vdouble inline ones(int _length); // Создаёт вектор заданной длины из единиц

	int Length(){return m_length;} // Возвращает длину вектора
	bool IsGorizontal(){return m_isgorizontal;} // Возвращает флаг горизонтальности
	
	void disp(); // Выводит значения элементов в консольное окно
	void dispWithIndex();
	void dispSquareMatrix();// Выводит значения элементов квадратной матрицы в консольное окно

	char* disp_str();
	char* dispMatrix_str();
	
	bool is_zeros(); // Истина, если все элементы - равны нулю
	bool is_zeros(const double& epsilon);// Истина, если модуль всех элементов не превышает epsilon

    double& operator[](int index) const; // Возвращает элемент по заданному индексу
	vdouble operator[](Vector<int>& ind); // Возвращает вектор-отрезок по заданныму массиву индексов
	vdouble operator()(Vector<int>& vrows, Vector<int>& vcols);
//	vdouble vdouble::operator[](Vector<Vector<int> >& ind); // Возвращает массив-отрезок по заданныму массиву индексов по каждой размерности
	double& operator()(int index); // Возвращает элемент по заданному индексу

	double& operator()(int row,int col); // Возвращает элемент двумерной матрицы по заданному индексу
	double& operator()(int row, int col, int tab); // Возвращает элемент трёхмерной матрицы по заданным индексам строки и столбца
	double& operator()(Vector<int>& indexes); // Возвращает элемент трёхмерной матрицы по заданным индексам строки и столбца

	vdouble& operator=(const vdouble& rhs); // Перегруженный оператор присваивания
	vdouble& operator=(const double& ra);
	vdouble& SummingFrom(int i0, vdouble& rhs);// // Поэлементное суммирование с вектором аргумента с присваиванием начиная с указанного номера элемента
	vdouble& operator+=(const vdouble& rhs);// Поэлементное суммирование с вектором аргумента с присваиванием
	vdouble& operator+=(const double& ra);
	
	vdouble& operator-=(const vdouble& rhs);// Поэлементное вычитание вектора аргумента с присваиванием
	vdouble& operator-=(const double& ra);
	
	vdouble& operator*=(const vdouble& rhs);// Поэлементное умножение на вектор аргумента с присваиванием
	vdouble& operator*=(const double& ra);
	
	vdouble& operator/=(const vdouble& rhs);// Поэлементное деление на вектор аргумента с присваиванием
	vdouble& operator/=(const double& ra);// Деление на вещественное число с присваиванием

	friend vdouble inline operator+(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator+(const double& a, vdouble& ob2);
	friend vdouble inline operator+(vdouble& ob1, const double& a);

	friend vdouble inline operator-(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator-(const double& a, vdouble& ob2);
	friend vdouble inline operator-(vdouble& ob1, const double& a);
/*
	friend vdouble inline operator^(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator^(const double& a, vdouble& ob2);
	friend vdouble inline operator^(vdouble& ob1, const double& a);
	*/
	friend vdouble inline pow(vdouble& ob1, vdouble& ob2);
	friend vdouble inline pow(const double& a, vdouble& ob2);
	friend vdouble inline pow(vdouble& ob1, const double& a);

    friend vdouble inline operator*(const vdouble& ob1, const vdouble& ob2);
    friend vdouble inline operator*(const double& a, const vdouble& ob2);
    friend vdouble inline operator*(const vdouble& ob1, const double& a);

	friend vdouble inline operator/(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator/(const double& a, vdouble& ob2);
	friend vdouble inline operator/(vdouble& ob1, const double& a);

//	friend vdouble inline operator,(vdouble& ob1, vdouble& ob2);
//	friend vdouble inline operator,(const double& a, vdouble& ob2);
//	friend vdouble inline operator,(vdouble& ob1, const double& a);
static vdouble append(vdouble& ob1, vdouble& ob2)
{
	int i, len1 = ob1.m_length;
	int len = len1 + ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(i=0;i<len1;i++)
	{
		*(pr+i) = *(pv1+i);
	}
	for(i=len1; i<len; i++)
	{
		*(pr+i) = *(pv2+i);
	}
	tempOb.m_dims = ob1.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob1.m_size[d];
	return tempOb;
}
//3
static vdouble append(const double& a, vdouble& ob)
{
	int len = ob.m_length + 1;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	*pr = a;
	for(int i=1;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//5
static vdouble append(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb=vdouble(len+1);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	*(pr+len) = a;
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}	
	friend vdouble inline operator+(vdouble& ob);
	friend vdouble inline operator-(vdouble& ob);

	friend vdouble inline log(vdouble& ob);
	friend vdouble inline log10(vdouble& ob);
	friend vdouble inline abs(vdouble& ob);

	friend vdouble inline acos(vdouble& ob);
	friend vdouble inline asin(vdouble& ob);
	friend vdouble inline atan(vdouble& ob);
	friend vdouble inline atan2(vdouble& x, vdouble& y);

	friend vdouble inline cos(vdouble& ob);
	friend vdouble inline cosh(vdouble& ob);
	friend vdouble inline sin(vdouble& ob);
	friend vdouble inline sinh(vdouble& ob);
	friend vdouble inline tan(vdouble& ob);
	friend vdouble inline tanh(vdouble& ob);
	friend vdouble inline exp(vdouble& ob);
	friend vdouble inline sqrt(vdouble& ob);

	friend vdouble inline floor(vdouble& ob);
	friend vdouble inline ceil(vdouble& ob);

	friend vdouble inline linterp(vdouble& x, vdouble& y, vdouble& xx);
	friend bool inline hist(vdouble& v, vdouble&  n, vdouble& x);
	friend bool inline hist(vdouble& v, int N, vdouble&  n, vdouble& x);
	friend bool inline hist2(vdouble& v1, vdouble& v2,int n1, int n2, vdouble&  n, vdouble& x1, vdouble& x2);
	friend bool inline covar(vdouble& t,vdouble& v1, vdouble& v2,  vdouble& tcov, vdouble& cov);

	friend Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator>(const double& a, vdouble& ob);
	friend Vector<bool> inline operator>(vdouble& ob, const double& a);

	friend Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator>=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator>=(vdouble& ob, const double& a);

	friend Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator<(const double& a, vdouble& ob);
	friend Vector<bool> inline operator<(vdouble& ob, const double& a);

	friend Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator<=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator<=(vdouble& ob, const double& a);

	friend Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator==(const double& a, vdouble& ob);
	friend Vector<bool> inline operator==(vdouble& ob, const double& a);

	friend Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator!=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator!=(vdouble& ob, const double& a);
	
	friend vdouble inline fliplr(vdouble& ob);

	friend void inline operator<<(vdouble& ob, const double& a);
	friend void inline operator>>(const double& a, vdouble& ob);

//	friend void inline operator<<(CArchive& ar, vdouble& v);
//	friend void inline operator>>(CArchive& ar, vdouble& v);

	friend vdouble inline conv(vdouble& v1, vdouble& v2);
	friend vdouble dsequence(double d0, double dstep, double dend);
	friend vdouble dsequence(double d0, long Len, double dend);
	friend vdouble dsequence(double d0, double dstep, long Len);
//	friend int SaveAsSurferGrid7(char gridfilename[], vdouble& xi, vdouble& yi, vdouble& zi, vdouble& visible);

	void Resetting(); // Обнуляет все элементы вектора
    double& End() const; // Возвращает последний элемент вектора
    double& End(int n) const; // Возвращает n- ый элемент вектора с конца
		// n < 0
	vdouble Select(Vector<int>& indexes); // Возвращает новый вектор, выбирая элементы из данного вектора
	vdouble Select(Vector<bool>& vbl); // Возвращает новый вектор, выбирая элементы из данного вектора
	void LocalMaximums(vdouble& LocMax, Vector<int>& indexes); // Формирует вектор локальных максимумов и целочисленный вектор их индексов
	void LocalMaximums(int n, vdouble& LocMax, Vector<int>& indexes);// Формирует вектор локальных максимумов и целочисленный вектор их индексов
	void LocalMaximumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes);// Формирует вектор локальных максимумов и целочисленный вектор их индексов

	void LocalMinimums(vdouble& LocMin, Vector<int>& indexes);// Формирует вектор локальных минимумов и целочисленный вектор их индексов
	void LocalMinimums(int n, vdouble& LocMin, Vector<int>& indexes);// Формирует вектор локальных минимумов и целочисленный вектор их индексов
	void LocalMinimumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes);// Формирует вектор локальных максимумов и целочисленный вектор их индексов
	bool IsEndLocalMin(int n = 3);
	bool IsEndLocalMax(int n = 3);
	bool IsEndDecreaseDown(int n = 3);
	bool IsEndGrowUp(int n = 3);

	double Max(); // Возвращает мaксимальный элемент вектора
	double Max(int iFirst, int iLast); // Возвращает мaксимальный элемент вектора
	double Min(); // Возвращает минимальный элемент вектора
	double MinPositive(); // Возвращает минимальный положительный элемент вектора
	double Min(int iFirst, int iLast); // Возвращает минимальный элемент вектора
	double MaxFrom(int j);
	double MinFrom(int j);
	double MaxFromTo(int i1, int i2); // Возвращает минимальный элемент вектора
	double MinFromTo(int i1, int i2); // Возвращает минимальный элемент вектора
	double MaxAbs(); // Возвращает мaксимальный по абсолютному значению элемент вектора
	double MinAbs(); // Возвращает минимальный по абсолютному значению элемент вектора
	double Mean(); // Возврашает среднее арифметическое элементов вектора
	double Mean(int realElementsNumber); // Возврашает среднее арифметическое realElementsNumber элементов вектора
	double Median(); // Возврашает среднее арифметическое элементов вектора
	double Median_sort(); // Возврашает среднее арифметическое элементов вектора
	double Root_mean_square_Dismissal(); // Возврашает среднеквадратичное отклонение
	double Sum(); // Возврашает сумму элементов вектора
	double SquareSum(); // Возврашает сумму квадратов элементов вектора
	double SquareSumFrom(int i0); // Возврашает сумму квадратов элементов вектора, начиная с i0
	void push_back(double a);// Добавляет элемент в конец вектора
	void push_front(double a); // Добавляет элемент в начало вектора
	void DeleteEnd(); // Удаляет 1 последний элемент вектора
	void DeleteEnd(int n); // Удаляет n последних элементов вектора
	void DeleteElement(int index); // Удаляет index-ный элемент вектора
	void DeleteElements(Vector<bool>& vbl); // Удаляет элементы вектора
	void DeleteAll(); // Удаляет все элементы вектора

	vdouble CumMeanSquareSum();// Возврашает вектор кумулятивных квадратичных сумм, усреднённых по номеру элемента с извлечением корня
	vdouble CumMeanSquareSumFrom(int i0);// Возврашает вектор кумулятивных квадратичных сумм, усреднённых по номеру элемента с извлечением корня, начиная с i0
	vdouble CumSum(); // Возврашает вектор кумулятивных сумм
	vdouble CumMeanSum(); // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента
	vdouble CumMeanSumFrom(int i0); // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента, начиная с i0
    vdouble DiffVector() const;// Вектор конечных разностей (возвращает вектор на 1 короче)
    vdouble SumVector() const;//Вектор конечных сумм (сумм в соседних точках) - возвр. вект. на 1 короче
    double Trapz(const vdouble& t); // Интегрирование методом трапеций на неравномерной временной сетке

    double ScalarProduct(const vdouble& rhs); // Возвращает скалярное произведение на вектор в аргументе
    double ScalarProductFrom(int i0, const vdouble& rhs); // Возвращает скалярное произведение на вектор в аргументе начиная с указанного номера элемента
    void FourierTransform(const vdouble& t, vdouble& omega, vdouble& A, vdouble& fi ); // Фурье преобразование

	//============ Функции Лаггер - спектральных преобразований ============
	vdouble vLagerPolynom(int n);
	double LagerAlphaDeterm(int maxOrder, double tend, double EnergyPart = 0.95);
	double LagerAlphaDeterminition(double& tend, double& EnergyPart);
	vdouble LagerQuotients(int i0, vdouble& t, LagerStruct& lgstr, int flag_of_Inf, Vector<vdouble>& koefs, char * sNumDen, char* sRoots); // Вычисление коэффициентов Лагерра

	double LagerDeterminant(); // Вычисляет детерминант системы уравнений используя вектор коэффициентов Лагерра
        double LagerDeterminant(double alpha, double beta, vdouble& alphai, vdouble& flip_betai, vdouble& num, vdouble& den);// Вычисляет детерминант системы уравнений используя вектор коэффициентов Лагерра, а также коэффициенты передаточной ф-ции
	int InvLaplace(vdouble& num, vdouble& den, vdouble& t, vdouble& f_rekonstr, Vector<vdouble>& koefs, char* sRoots); // Обратное преобразование Лаплапса для дроби полиномов

	//============ Функции Линейной алгебры ============
	vdouble MatrixProduct(vdouble& x);// Матричное произведение матрицы размера R x C на вертикальный вектор длиной C 
										// возвращает вектор длиной R
	vdouble MatrixWithMatrixProduct(vdouble& x); // Матричное произведение матрицы размера R1 x C1 на матрицу размера R2 x C2 причём C1 = R2
	vdouble TransponedMatrixProduct(vdouble& x);// Матричное произведение матрицы размера R x C на вертикальный вектор длиной R 
										// возвращает вектор длиной C
	vdouble VectorsToMatrixProduct(vdouble& gor); // Матричное произведение вертикального вектора длиной R
												// на горизонтальный вектор длиной C 
												// возвращает матрицу размером R x C
	vdouble TichonovOld(vdouble& b);
	vdouble Tichonov(vdouble& b, bool AlphaNonZero = true); // Решение системы линейных уравнений методом регуляризации Тихонова
	int pinv(vdouble& pinvMatrix);// Псевдообращение матрицы
	vdouble LinearInterp(vdouble &t);
	vdouble LinearInterp();

	void EMA(vdouble& t, vdouble& tau, vdouble& ema, int nPoint); //Экспоненциальная скользящая средняя
	void NEMA(vdouble& t, vdouble& tau, 
		vdouble& ema,  vdouble& nema, int nPoints); //Нормированная Экспоненциальная скользящая средняя
/*	void Derivatives(vdouble& t, 
		double dt,
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		vdouble& tau, 
		vdouble& ma, vdouble& d1, vdouble& d2, 
		int nPoint, int interp_order, 
		bool uniform,
		bool isEnd = false, int nPredict = 0);// Первая и вторая производная
	void Derivative(vdouble& t, 
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		double& ma, double& d1, double& d2, // скользящая средняя и первая и вторая производная
		int interp_order);
	int Derivatives(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		vdouble& tDeriv, // вектор шкалы времени для производной - выходной параметр
		vdouble& DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
		int& i1, int& i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
		int interp_order, // порядок интерполяционного полинома
		int deriv_order, // порядок высшей производной
		int nPoints, // число точек временного окна
		double& qt, // коэффициент растяжки полиномов по оси времени - передаётся из прежде вызванной функции Derivatives
		bool uniform);// флаг равномерности временной сетки
	int Derivative(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		vdouble& tDeriv, // вектор шкалы времени для производной - выходной параметр
		vdouble& DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
		int& i1, int& i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
		int interp_order, // порядок интерполяционного полинома
		int deriv_order, // порядок высшей производной
		int nPoints, // число точек временного окна
		double& qt); // коэффициент растяжки полиномов по оси времени - передаётся из прежде вызванной функции Derivatives
	int diff_Wp(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		int denom_order, // порядок знаменателя передаточной функции
		int nPoints, // число точек временного окна для вычисления производной
		bool uniform, // флаг равномерной временной шкалы
		vdouble& denom, // коэффициенты знаменателя передаточной функции
		vdouble& num, // коэффициенты числителя передаточной функции
		vdouble& f_reconstr, // реконструированный сигнал
		double& er_deriv, // ошибка разложения сигнала по базису его производных
		double& er_reconstr);// ошибка реконтрукции сигнала*/
	double det(); // Детерминант
	void sls_det(vdouble& b, vdouble& x, double& _det, bool PrivateDesigion = false);//Решение линейной системы уравнений методом Гаусса
//	vdouble A(int j); // Алгебраическое дополнение

	vdouble PolynomDerivative();//Возвращает вектор полинома первой производной
	vdouble PolynomSumming(vdouble& v); // Суммирование полиномов
	void PolynomDivide(const vdouble& divisor, vdouble& quotient, vdouble& remainder);// Производит деление на полином
	int PolynomDivideIntoThree_member(double& b, double c);// Производит деление полинома на трёхчлен, в котором второй коэффициент b подлежит определению,
	int PolynomRootsSimple(vdouble& prs, vdouble& D);// Вычленяет кратные корни, получая полином с простыми корнями и соответствующий множитель
	int PolynomGreatestCommonDivider(vdouble& v, vdouble& divider);// Наибольший общий делитель двух полиномов
	double PolynomValue(const double& a);// Возвращает значение полинома для заданной точки
	complex PolynomValue(complex& z);// Возвращает значение полинома для заданной точки
	vdouble PolynomValues(vdouble& a);// Возвращает массив значений полинома для заданного массива точек 
	Vector<double> PolynomDerivativesValue(const double& a, int N = 0);// Возвращает значение полинома и его производных порядка до N включительно для заданной точки. Если N = 0, вычисляет производные всех возможных порядков. Обобщенный метод Горнера
	Vector<vdouble> PolynomDerivativesValues(vdouble& a, int N = 0);//Возвращает массивы значений полинома и его производных порядка до N включительно для заданного массива точек. Если N = 0, вычисляет производные всех возможных порядков.  Обобщенный метод Горнера
	vdouble PolynomSubsVariable(const double& a);// Производит замену переменной y = x - a 
//	double MaxAbsRoots();// Максимальный модуль корней полинома
//	double MinAbsRoots();// Минимальный модуль корней полинома
	int roots(vdouble& dr, Vector<complex>& cr, Vector<int>& order_dr, Vector<int>& order_cr);// Вычисляет корни действительного полинома - действительные и комплексные, отдельно - кратные
	int Lobachevski_Greffe_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& epsilon_control = 1.0e-2);//Вычисляет действительные и комплексные корни действительного полинома методом Лобачевского - Греффе (для полиномов с вычленёнными кратными корнями)
	int Bernulli_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& depsilon = 1.0e-8);//Вычисляет действительные и комплексные корни действительного полинома методом Бернулли (для полиномов с вычленёнными кратными корнями)
	int BernulliMinRealRoot(vdouble& dr, const double& depsilon = 1.0e-8);
	int PolynomNewtonRoot(complex& z, const double& epsilon = 1.0e-14);// Уточнение комплексного корня 
	int PolynomNewtonRoot(double& dr, const double& epsilon = 1.0e-16);// Уточнение действительного корня
	int TranscendentNewtonRoot(double& x, double k, vdouble& v, const double& epsilon = 1.0e-16);// Уточнение решения трансцендентного уравнения this->PolynomValue(x) * exp(k * x) + v.PolynomValue(x) = 0.0;
	int PolynomLinaThree_memberDivider(double& p, double& q); // нахождение квадратичного делителя заданного многочлена методом Лина
	int PolynomLinaDivider(vdouble& d); // нахождение делителя любой степени заданного многочлена методом Лина
	double MaxAbsRoots(); // Возвращает максимально возможный модуль корня полинома
	double MinAbsRoots(); // Возвращает минимально возможный модуль корня полинома
	int WaveletDecomposition(vdouble* t,
	  int wf, // флаг вейвлета
	  int order, // порядок вейвлета
	  int orderBiorthogonalDecomposition, // порядок вейвлета
	  int maxLevel, // максимальный уровенть разложения
	  Vector<Vector<int> >& vtau_s_ind, 
	  Vector<vdouble>& vtau_s,
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_d_ind, 
	  Vector<vdouble>& vtau_d,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_S_ind, 
	  Vector<vdouble>& vtau_S,
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<Vector<int> >& vtau_F_ind,
	  Vector<vdouble>& vtau_F,
	  Vector<vdouble>& vFast); // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	int WaveletDecomposition(vdouble* t,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int left_h,
	  int right_h,
	  int left_g,
	  int right_g,
	  int maxLevel, // максимальный уровенть разложения
	  Vector<Vector<int> >& vtau_s_ind, 
	  Vector<vdouble>& vtau_s,
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_d_ind, 
	  Vector<vdouble>& vtau_d,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_S_ind, 
	  Vector<vdouble>& vtau_S,
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<Vector<int> >& vtau_F_ind,
	  Vector<vdouble>& vtau_F,
	  Vector<vdouble>& vFast); // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	int WaveletDecomposition1(vdouble* t,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int left_h,
	  int right_h,
	  int left_g,
	  int right_g,
	  int maxLevel, // максимальный уровенть разложения
	  Vector<Vector<int> >& vtau_s_ind, 
	  Vector<vdouble>& vtau_s,
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_d_ind, 
	  Vector<vdouble>& vtau_d,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_S_ind, 
	  Vector<vdouble>& vtau_S,
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<Vector<int> >& vtau_F_ind,
	  Vector<vdouble>& vtau_F,
	  Vector<vdouble>& vFast); // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
/*
	int vdouble::WaveletDecomposition(int wf, // флаг вейвлета
	  int order, // порядок вейвлета
	  int& maxLevel, // максимальный уровенть разложения
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vs); // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
*/
};

struct LagerStruct
{
	double alpha; // alpha - параметр обобщённого полинома Лагерра
	double beta; // beta - параметр обобщённого полинома Лагерра
	double epsilon; // Максимальный модуль детерминанта фундаментальной системы уравнений
	int maxOrder; // Максимально допустимый порядок
	bool bIncludeRealRoots;

	vdouble vQ;// Коэффициенты разложения по Лаггерам
	vdouble alphai; // Промежуточный числитель
	vdouble flip_betai; // Промежуточный знаменатель (обращённый)
	vdouble num;// Числитель передаточной функции
	vdouble den;// Знаменатель передаточной функции
	double error;// Ошибка реконструкции
	double fund_det;// детерминант фундаментальной системы уравнений

};


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
int WaveletEpsilon(
	  int& wf, // флаг вейвлета
	  int& order, // порядок вейвлета
	  int& m_wOrderBiorthogonalDecomposition,
	  double& wEpsilon,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g);

int WaveletGetLeftRight(
	  int& wf, // флаг вейвлета
	  int& order, // порядок вейвлета
	  int& orderBiorthogonalDecomposition,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g);

//##1
vdouble inline operator+(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr, "Error using operator+ : the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
//		fprintf(stderr, "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) + *(pv2+i);
	}
	tempOb.m_dims = ob2.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob2.m_size[d];
	return tempOb;
}

vdouble inline operator+(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) + a;
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}

vdouble inline operator+(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) + a;
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//1
vdouble inline operator-(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr, "Error using operator-: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
//		fprintf(stderr, "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) - *(pv2+i);
	}
	tempOb.m_dims = ob2.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob2.m_size[d];
	return tempOb;
}

//3

vdouble inline operator-(const double& a, vdouble& ob2)
{
	int len = ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob2.m_isgorizontal;
	double *pv, *pr; 
	pv = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a - *(pv+i);
	}
	tempOb.m_dims = ob2.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob2.m_size[d];

	return tempOb;
}

//5

vdouble inline operator-(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) - a;
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/*
//1
vdouble inline operator^(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,  "Error using operator^: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
//		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv1+i) , *(pv2+i) );
	}
	tempOb.m_dims = ob1.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob1.m_size[d];
	return tempOb;
}

//3
vdouble inline operator^(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(a,*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}

//5
vdouble inline operator^(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv+i),a);
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
*/
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble inline pow(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,  "Error using pow(): the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
//		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv1+i) , *(pv2+i) );
	}
	tempOb.m_dims = ob1.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob1.m_size[d];
	return tempOb;
}
//3
vdouble inline pow(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(a,*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//5
vdouble inline pow(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv+i),a);
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
///////////////////////////////
//1
vdouble inline operator*(const vdouble& ob1, const vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,  "Error using operator*: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
//		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	tempOb.m_dims = ob1.m_dims;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) * *(pv2+i) ;
	}
	tempOb.m_dims = ob2.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob2.m_size[d];
	return tempOb;
}

//3
vdouble inline operator*(const double& a, const vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a * *(pv+i);
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//4
vdouble inline operator*(const vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) =  *(pv+i) * a ;
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
///////////////////////////////
///////////////////////////////
//1
vdouble inline operator/(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,  "Error using operator/: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
//		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) / *(pv2+i) ;
	}
	tempOb.m_dims = ob1.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob1.m_size[d];
	return tempOb;
}
//3
vdouble inline operator/(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a / *(pv+i);
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//5
vdouble inline operator/(vdouble& ob, const double& a)
{
//	ob.WriteRaporto((CString)" operator/(vdouble& ob, const double& a) \t");
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) / a;
	}
//ob.WriteRaporto((CString)" operator/ End \n");
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
///////////////////////////////
///////////////////////////////
//1

/*
vdouble inline operator,(vdouble& ob1, vdouble& ob2)
{
	int len1 = ob1.m_length;
	int len = len1 + ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len1;i++)
	{
		*(pr+i) = *(pv1+i);
	}
	for(i=len1; i<len; i++)
	{
		*(pr+i) = *(pv2+i);
	}
	tempOb.m_dims = ob1.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob1.m_size[d];
	return tempOb;
}
//3
vdouble inline operator,(const double& a, vdouble& ob)
{
	int len = ob.m_length + 1;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	*pr = a;
	for(int i=1;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//5
vdouble inline operator,(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb=vdouble(len+1);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	*(pr+len) = a;
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}*/

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline operator+(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = +(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline operator-(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = -(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
vdouble inline log(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = log(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline log10(vdouble& ob)
{
	int i, len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;


	double nonZeroMin;
	bool wasInit = false;

	for(i = 0; i < len; i++)
	{
		if(!wasInit)
		{
			if(*(pv+i) > 0)
			{
				nonZeroMin = *(pv+i);
				wasInit = true;
			}
		}
		else
		{
			if(*(pv+i) > 0)
			{
				nonZeroMin = *(pv+i) < nonZeroMin ? *(pv+i) : nonZeroMin;
			}
		}
	}
	if (!wasInit)
		nonZeroMin = 0.1;

	double log10_nonZeroMin = log10(nonZeroMin);

	for(i = 0; i < len; i++)
	{
		if(*(pv+i) > 0)
		{
			*(pr+i) = log10(*(pv+i));
		}
		else
		{
			*(pr+i) = log10_nonZeroMin;
		}
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline abs(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = fabs(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline acos(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = acos(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline asin(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = asin(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline atan(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = atan(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////

vdouble inline atan2(vdouble& x, vdouble& y)
{
	int len = x.m_length;
	if (len != y.m_length)
	{
//		fprintf(stderr,  "Error using atan2: the lengthes of the vectors must be the same\n");
		return vdouble(0);

	}
	if (x.m_isgorizontal != y.m_isgorizontal)
	{
//		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=x.m_isgorizontal;
	double *px, *py, *pr; 
	px = x.pD;
	py = y.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = atan2(*(px+i) , *(py+i));
	}
	tempOb.m_dims = x.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = x.m_size[d];
	return tempOb;
}

//////////////////////////////////////////////////////////////
vdouble inline cos(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = cos(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline cosh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = cosh(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sin(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sin(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sinh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sinh(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline tan(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = tan(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline tanh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = tanh(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sqrt(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sqrt(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
vdouble inline exp(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = ::exp(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline floor(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = floor(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline ceil(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = ceil(*(pv+i));
	}
	tempOb.m_dims = ob.m_dims;
	for (int d = 0; d < tempOb.m_dims; d++)
		tempOb.m_size[d] = ob.m_size[d];
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,"Error using vdouble operator>(vdouble& ob1, vdouble& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) > (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator>(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a > (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) > a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,"Error using vdouble operator>=(vdouble& ob1, vdouble& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) >= (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator>=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a >= (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) >= a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,"Error using vdouble operator<(vdouble& ob1, vdouble& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) < (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator<(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a < (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator<(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) < a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,"Error using vdouble operator<=(vdouble& ob1, vdouble& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) <= (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator<=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a <= (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator<=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) <= a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,"Error using vdouble operator==(vdouble& ob1, vdouble& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) == (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator==(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a == (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator==(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) == a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
//		fprintf(stderr,"Error using vdouble operator!=(vdouble& ob1, vdouble& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) != (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator!=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a != (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator!=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) != a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
vdouble inline fliplr(vdouble& ob)
{
	vdouble v;
	int len = ob.m_length;
	v.resize(len);
	double *pv, *pob;
	pv = v.pD;
	pob = ob.pD + len - 1;
	for (int i = 0; i < len; i++)
	{
		*(pv + i) = *pob;
		pob--;
	}
	return v;
}
//////////////////////////////////////////////////////////////
void inline operator<<(vdouble& ob, const double& a)
{
	int len_1 = ob.m_length - 1;
	if ( len_1 < 0)
		return;
	double *pv, *pr; 
	pv = ob.pD + 1;
	pr = ob.pD;
	for (int i = 0; i < len_1; i++)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr + len_1) = a;
}
void inline operator>>(const double& a, vdouble& ob)
{
	int len_1 = ob.m_length - 1;
	if ( len_1 < 0)
		return;
	double *pv, *pr; 
	pv = ob.pD - 1;
	pr = ob.pD;
	for (int i = len_1; i > 0; i--)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr) = a;
}
vdouble inline conv(vdouble& v1, vdouble& v2)
{
	int len, len1, len2, i, j, milen, malen;
	double *pc, *pci, *pmai, *pmi, *pma;
	len1 = v1.m_length;
	len2 = v2.m_length;

	len = len1 + len2 - 1;
	if (len < 0)
		len = 0;

	vdouble c = vdouble(len); pc = c.pD;

	bool bl = len1 <= len2;

	pmi = bl ? v1.pD : v2.pD;
	pma = bl ? v2.pD : v1.pD;
	milen = bl ? len1 : len2;
	malen = bl ? len2 : len1;

	for (i = 0; i < milen; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = 0; j <= i; j++)
			*pci += *(pmi + j) * *(pmai - j);
	}
	for (i = milen; i < malen; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = 0; j < milen; j++)
			*pci += *(pmi + j) * *(pmai - j);
	}
	for (i = malen; i < len; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = i - malen +1; j < milen; j++) 
			*pci += *(pmi + j) * *(pmai - j);
	}
	return c;
	
}
vdouble inline linterp(vdouble& x, vdouble& y, vdouble& xx)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           y: given Y-Axis data
	//           x: given X-Axis data
	//
	//          xx: points on X-Axis to be interpolated
	//
	//      output:
	//
	//          yy: interpolated values at points "xx"

	// R. Y. Chiang & M. G. Safonov 9/18/1988
	// Copyright 1988-2004 The MathWorks, Inc.
	//       $Revision: 1.7.4.3 $
	// All Rights Reserved.
	// ------------------------------------------------------------------

	int nx = x.m_length;
	int nxx = xx.m_length;
	vdouble yy;
	yy.resize(nxx);
	if (xx[0] < x[0])
	{
		TCHAR errstr[255];
		stprintf_s(errstr, 255, _T("You must have min(x = %f) <= min(xx = %f).."), x[0], xx[0]);
		MessageBox(0,errstr,_T("linterp"),0);
		return vdouble();
	}	
	if (xx[nxx-1] > x[nx-1])
	{
		TCHAR errstr[255];
		stprintf_s(errstr, 255, _T("You must have max(xx = %f) <= max(x = %f).."), xx[nxx-1], x[nx-1]);
		MessageBox(0,errstr,_T("linterp"),0);
		return vdouble();
	}
	//
	int j = 1;
	for (int i = 0; i < nxx; i++)
	{
	   while (/*j < nx-1 &&*/ x[j] < xx[i])
	   {
			 j = j+1;
	   }
	   double alfa = (xx[i]-x[j-1])/(x[j]-x[j-1]);
	   yy[i] = y[j-1]+alfa*(y[j]-y[j-1]);
	}
	//
	// ------ End of INTERP.M % RYC/MGS %
	return yy;
}
int inline linterp(int nx, double* px, double* py, int nxx, double* pxx, double* pyy)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           py: given Y-Axis data
	//           px: given X-Axis data
	//
	//          pxx: points on X-Axis to be interpolated
	//
	//      output:
	//
	//          pyy: interpolated values at points "xx"

	// R. Y. Chiang & M. G. Safonov 9/18/1988
	// Copyright 1988-2004 The MathWorks, Inc.
	//       $Revision: 1.7.4.3 $
	// All Rights Reserved.
	// ------------------------------------------------------------------

	//int nx = x.m_length;
	//int nxx = xx.m_length;
	//vdouble yy;
	//yy.resize(nxx);
	/*if (xx[0] < x[0])
	{
		char errstr[255];
		sprintf(errstr, "You must have min(x = %f) <= min(xx = %f)..", x[0], xx[0]);
		MessageBox(0,errstr,"linterp",0);
		return vdouble();
	}	
	if (xx[nxx-1] > x[nx-1])
	{
		char errstr[255];
		sprintf(errstr, "You must have max(xx = %f) <= max(x = %f)..", xx[nxx-1], x[nx-1]);
		MessageBox(0,errstr,"linterp",0);
		return vdouble();
	}*/
	//
	int j = 1;
	for (int i = 0; i < nxx; i++)
	{
	   while (j < nx-1 && px[j] < pxx[i])
	   {
			 j = j+1;
	   }
	   double alfa = (pxx[i]-px[j-1])/(px[j]-px[j-1]);
	   pyy[i] = py[j-1]+alfa*(py[j]-py[j-1]);
	}
	//
	// ------ End of INTERP.M % RYC/MGS %
	return 1;
}
int inline linterp(int nx, double* py, int nxx, double* pyy)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           py: given Y-Axis data
	//           px: given X-Axis data
	//
	//          pxx: points on X-Axis to be interpolated
	//
	//      output:
	//
	//          pyy: interpolated values at points "xx"

	// R. Y. Chiang & M. G. Safonov 9/18/1988
	// Copyright 1988-2004 The MathWorks, Inc.
	//       $Revision: 1.7.4.3 $
	// All Rights Reserved.
	// ------------------------------------------------------------------

	//int nx = x.m_length;
	//int nxx = xx.m_length;
	//vdouble yy;
	//yy.resize(nxx);
	/*if (xx[0] < x[0])
	{
		char errstr[255];
		sprintf(errstr, "You must have min(x = %f) <= min(xx = %f)..", x[0], xx[0]);
		MessageBox(0,errstr,"linterp",0);
		return vdouble();
	}	
	if (xx[nxx-1] > x[nx-1])
	{
		char errstr[255];
		sprintf(errstr, "You must have max(xx = %f) <= max(x = %f)..", xx[nxx-1], x[nx-1]);
		MessageBox(0,errstr,"linterp",0);
		return vdouble();
	}*/
	//=========================================
	//double* px = new double[nx];
	double step_x = (1.0 - 0.0) / (nx - 1);
	//for (int j = 0; j < nx; j++)
	//{
	//	px[j] = 0.0 + j * step_x;
	//}
	//=========================================
	//double* pxx = new double[nxx];
	double step_xx = (1.0 - 0.0) / (nxx - 1);
	//for (int i = 0; i < nxx; i++)
	//{
	//	pxx[i] = 0.0 + i * step_xx;
	//}
	//=========================================
	int j = 1;
	for (int i = 0; i < nxx; i++)
	{
	   //while (j < nx-1 && px[j] < pxx[i])
	   while (j < nx-1 && j * step_x < i * step_xx)
	   {
			 j = j+1;
	   }
	   //double alfa = (pxx[i]-px[j-1])/(px[j]-px[j-1]);
	   double alfa = (i*step_xx - (j-1)*step_x)/(step_x);
	   pyy[i] = py[j-1]+alfa*(py[j]-py[j-1]);
	}
	//=========================================
	// ------ End of INTERP.M % RYC/MGS %
	return 1;
}
int inline meshgrid(vdouble x, vdouble y,
			 vdouble &xx, vdouble &yy)
{

	//%MESHGRID   X and Y arrays for 3-D plots.
	//%   [X,Y] = MESHGRID(x,y) transforms the domain specified by vectors
	//%   x and y into arrays X and Y that can be used for the evaluation
	//%   of functions of two variables and 3-D surface plots.
	//%   The rows of the output array X are copies of the vector x and
	//%   the columns of the output array Y are copies of the vector y.
	//%
	//%   [X,Y] = MESHGRID(x) is an abbreviation for [X,Y] = MESHGRID(x,x).
	//%   [X,Y,Z] = MESHGRID(x,y,z) produces 3-D arrays that can be used to
	//%   evaluate functions of three variables and 3-D volumetric plots.
	//%
	//%   For example, to evaluate the function  x*exp(-x^2-y^2) over the 
	//%   range  -2 < x < 2,  -2 < y < 2,
	//%
	//%       [X,Y] = meshgrid(-2:.2:2, -2:.2:2);
	//%       Z = X .* exp(-X.^2 - Y.^2);
	//%       mesh(Z)
	//%
	//%   MESHGRID is like NDGRID except that the order of the first two input
	//%   and output arguments are switched (i.e., [X,Y,Z] = MESHGRID(x,y,z)
	//%   produces the same result as [Y,X,Z] = NDGRID(y,x,z)).  Because of
	//%   this, MESHGRID is better suited to problems in cartesian space,
	//%   while NDGRID is better suited to N-D problems that aren't spatially
	//%   based.  MESHGRID is also limited to 2-D or 3-D.
	//%
	//%   Class support for inputs x, y, z:
	//%      float: double, single
	//%
	//%   See also SURF, SLICE, NDGRID.

	//%   J.N. Little 1-30-92, CBM 2-11-92.
	//%   Copyright 1984-2004 The MathWorks, Inc. 
	//%   $Revision: 5.14.4.2 $  $Date: 2004/03/02 21:47:07 $

	// if nargout<3, % 2-D array case

	int nx = x.Length();
	int ny = y.Length();
#if 1
	xx.resize(ny,nx);
	yy.resize(ny,nx);

	for (int r = 0; r < ny; r++)
	{
		for (int c = 0; c < nx; c++)
		{
			xx(r,c) = x[c];
			yy(r,c) = y[r];
		}
	}
#else
	xx.resize(ny,nx);
	yy.resize(ny,nx);

	for (int r = 0; r < nx; r++)
	{
		for (int c = 0; c < ny; c++)
		{
			xx(c,r) = x[r];
			yy(c,r) = y[c];
		}
	}
#endif
	return 0;
}

int inline meshgrid(int nx, int ny, double *x, double *y,
			 double **xx, double **yy)
{

	//%MESHGRID   X and Y arrays for 3-D plots.
	//%   [X,Y] = MESHGRID(x,y) transforms the domain specified by vectors
	//%   x and y into arrays X and Y that can be used for the evaluation
	//%   of functions of two variables and 3-D surface plots.
	//%   The rows of the output array X are copies of the vector x and
	//%   the columns of the output array Y are copies of the vector y.
	//%
	//%   [X,Y] = MESHGRID(x) is an abbreviation for [X,Y] = MESHGRID(x,x).
	//%   [X,Y,Z] = MESHGRID(x,y,z) produces 3-D arrays that can be used to
	//%   evaluate functions of three variables and 3-D volumetric plots.
	//%
	//%   For example, to evaluate the function  x*exp(-x^2-y^2) over the 
	//%   range  -2 < x < 2,  -2 < y < 2,
	//%
	//%       [X,Y] = meshgrid(-2:.2:2, -2:.2:2);
	//%       Z = X .* exp(-X.^2 - Y.^2);
	//%       mesh(Z)
	//%
	//%   MESHGRID is like NDGRID except that the order of the first two input
	//%   and output arguments are switched (i.e., [X,Y,Z] = MESHGRID(x,y,z)
	//%   produces the same result as [Y,X,Z] = NDGRID(y,x,z)).  Because of
	//%   this, MESHGRID is better suited to problems in cartesian space,
	//%   while NDGRID is better suited to N-D problems that aren't spatially
	//%   based.  MESHGRID is also limited to 2-D or 3-D.
	//%
	//%   Class support for inputs x, y, z:
	//%      float: double, single
	//%
	//%   See also SURF, SLICE, NDGRID.

	//%   J.N. Little 1-30-92, CBM 2-11-92.
	//%   Copyright 1984-2004 The MathWorks, Inc. 
	//%   $Revision: 5.14.4.2 $  $Date: 2004/03/02 21:47:07 $

	// if nargout<3, % 2-D array case
	for (int r = 0; r < ny; r++)
	{
		for (int c = 0; c < nx; c++)
		{

			xx[r][c] = x[c];
			yy[r][c] = y[r];
		}
	}
	return 0;
}
int inline meshgrid(int nx, int ny, int nz, double *x, double *y, double *z, 
			 double ***xx, double ***yy, double ***zz)
{

	//%MESHGRID   X and Y arrays for 3-D plots.
	//%   [X,Y] = MESHGRID(x,y) transforms the domain specified by vectors
	//%   x and y into arrays X and Y that can be used for the evaluation
	//%   of functions of two variables and 3-D surface plots.
	//%   The rows of the output array X are copies of the vector x and
	//%   the columns of the output array Y are copies of the vector y.
	//%
	//%   [X,Y] = MESHGRID(x) is an abbreviation for [X,Y] = MESHGRID(x,x).
	//%   [X,Y,Z] = MESHGRID(x,y,z) produces 3-D arrays that can be used to
	//%   evaluate functions of three variables and 3-D volumetric plots.
	//%
	//%   For example, to evaluate the function  x*exp(-x^2-y^2) over the 
	//%   range  -2 < x < 2,  -2 < y < 2,
	//%
	//%       [X,Y] = meshgrid(-2:.2:2, -2:.2:2);
	//%       Z = X .* exp(-X.^2 - Y.^2);
	//%       mesh(Z)
	//%
	//%   MESHGRID is like NDGRID except that the order of the first two input
	//%   and output arguments are switched (i.e., [X,Y,Z] = MESHGRID(x,y,z)
	//%   produces the same result as [Y,X,Z] = NDGRID(y,x,z)).  Because of
	//%   this, MESHGRID is better suited to problems in cartesian space,
	//%   while NDGRID is better suited to N-D problems that aren't spatially
	//%   based.  MESHGRID is also limited to 2-D or 3-D.
	//%
	//%   Class support for inputs x, y, z:
	//%      float: double, single
	//%
	//%   See also SURF, SLICE, NDGRID.

	//%   J.N. Little 1-30-92, CBM 2-11-92.
	//%   Copyright 1984-2004 The MathWorks, Inc. 
	//%   $Revision: 5.14.4.2 $  $Date: 2004/03/02 21:47:07 $

	//else  % 3-D array case
#if 0
	double ***xx, double ***yy, double ***zz; 
	xx = AllocDouble3DMat (nz, ny, nx);
	yy = AllocDouble3DMat (nz, ny, nx);
	zz = AllocDouble3DMat (nz, ny, nx);
#endif
	for (int p = 0; p < nz; p++)
	{
		for (int r = 0; r < ny; r++)
		{
			for (int c = 0; c < nx; c++)
			{
				xx[p][r][c] = x[c];
				yy[p][r][c] = y[r];
				zz[p][r][c] = z[p];
			}
		}
	}
	return 0;
}

#if 0
Спасибо, всё открылось. 

По поводу господина Севастьянова я Вам, Григорий Иванович, задавал важный вопрос, на который Вы, почему-то, не ответили.Ответьте, пожалуйста, обязательно хотя бы в этот раз:

Какое отношение имеет Севастьянов к Трезвому движению?
а) является ли сам лично Севастьянов трезвенником?
б) что делает Севастьянов для утверждения трезвости в нашей стране?
в) или может он только лишь использует трезвеннические издания как площадку для пропаганды своих политических откровенно-националистических взглядов?

Григорий Иванович, спрашиваю Вас лично. А если и в этот раз не ответите, то спрошу публично.

С уважением, 
Алексей.


#endif

void inline localevaluate ( int npages, int nrows, int ncols, 
					double *** X, double *** x, int iter)
{
	//function X = localevaluate(x,iter)
	//switch iter
	// case 0
	//  X = ((2-x).*x-1).*x;
	// case 1
	//  X = (3*x-5).*x.*x+2;
	// case 2
	//  X = ((4-3*x).*x+1).*x;
	// case 3
	//  X = (x-1).*x.*x;
	//end
	int p, r, c;
	switch (iter)
	{
	case 0:
		{
			for (p = 0; p < npages; p++)
			{
				for (r = 0; r < nrows; r++)
				{
					for (c = 0; c < ncols; c++)
					{
						// case 0
						//  X = ((2-x).*x-1).*x;
						 X[p][r][c] = 
							 ((2. - x[p][r][c]) * x[p][r][c] - 1.)
							 * x[p][r][c];			
					}
				}
			}
		}
		break;
	case 1:
		{
			for (p = 0; p < npages; p++)
			{
				for (r = 0; r < nrows; r++)
				{
					for (c = 0; c < ncols; c++)
					{
						// case 1
						//  X = (3*x-5).*x.*x+2;
						 X[p][r][c] = 
							 (3.*x[p][r][c] - 5.) * x[p][r][c] * x[p][r][c] + 2.0;			
					}
				}
			}
		}
		break;
	case 2:
		{
			for (p = 0; p < npages; p++)
			{
				for (r = 0; r < nrows; r++)
				{
					for (c = 0; c < ncols; c++)
					{
						// case 2
						//  X = ((4-3*x).*x+1).*x;
						 X[p][r][c] = 
							 ((4. - 3.*x[p][r][c]) * x[p][r][c] + 1.0) * x[p][r][c];			
					}
				}
			}
		}
		break;
	case 3:
		{
			for (p = 0; p < npages; p++)
			{
				for (r = 0; r < nrows; r++)
				{
					for (c = 0; c < ncols; c++)
					{
						// case 3
						//  X = (x-1).*x.*x;
						 X[p][r][c] = 
							 (x[p][r][c] - 1.) * x[p][r][c] * x[p][r][c];			
					}
				}
			}
		}
		break;
	}
}



bool inline hist(vdouble& v, vdouble&  n, vdouble& x)
{

	double 
		mi = x[0],
		ma = x.End();
	
	int N = x.Length();

	if (n.Length() != N)
		n.resize(N, 0.0);

	int j;

	for (int i = 1; i < v.Length(); i++)
	{
		j = int( (v[i] - mi) / (ma-mi) * (N-1) );
		if (j >= 0 && j < N)
			n(j) = n(j) + 1.0;
	}
	return true;
}
bool inline hist(vdouble& v, int N, vdouble&  n, vdouble& x)
{

	double epsilon = 0.000001,
		ma = v.Max(),
		mi = v.Min(),

		
		dx = ( ma - mi )/( N );
	
	x = dsequence(-epsilon+mi + .5*dx, dx, ma + epsilon - .5*dx);
	if (x.m_length != N)
	{
		TCHAR str[250];
		stprintf_s( str, 250, _T("x1.m_length%d ~= N%d"),x.m_length, N);
		MessageBox(0, str,_T("hist2"),0);
		return false;
	}

	n.resize(N, 0.0);

	int j;

	for (int i = 1; i < v.Length(); i++)
	{
		j = int( (v[i] - mi) / (ma-mi) * (N-1) );
		n(j) = n(j) + 1.0;
	}
	return true;
}
bool inline hist2(vdouble& v1, vdouble& v2,int n1, int n2, vdouble&  n, vdouble& x1, vdouble& x2)
{

	if (v1.m_length != v2.m_length)
	{
		MessageBox(0, _T("length(v1)~=length(v2)"),_T("hist2"),0);
		return false;
	}

	double epsilon = 0.000001,
		ma1 = v1.Max(),
		mi1 = v1.Min(),

		ma2 = v2.Max(),
		mi2 = v2.Min(),
		
		dx1 = ( ma1 - mi1 )/( n1 ),
		dx2 = ( ma2 - mi2 )/( n2 );
	
	x1 = dsequence(-epsilon+mi1 + .5*dx1, dx1, ma1 + epsilon - .5*dx1);
	x2 = dsequence(-epsilon+mi2 + .5*dx2, dx2, ma2 + epsilon - .5*dx2);
	if (x1.m_length != n1)
	{
		TCHAR str[250];
		stprintf_s( str, 250, _T("x1.m_length%d ~= n1%d"),x1.m_length, n1);
		MessageBox(0, str,_T("hist2"),0);
		return false;
	}
	if (x2.m_length != n2)
	{
		TCHAR str[250];
		stprintf_s( str, 250, _T("x2.m_length%d ~= n2%d"),x2.m_length, n2);
		MessageBox(0, str,_T("hist2"),0);
		return false;
	}

	n.resize(n2,n1, 0.0);

	int i1,i2;

	for (int i = 1; i < v1.Length(); i++)
	{
		i1 = 1 + int( (v1[i] - mi1) / (ma1-mi1) * (n1-1) );
		i2 = 1 + int( (v2[i] - mi2) / (ma2-mi2) * (n2-1) );
		n(i2,i1) = n(i2,i1)+1;
	}
	return true;
}
bool inline covar(vdouble& t,vdouble& v1, vdouble& v2,  vdouble& tcov, vdouble& cov)
{
	int Len = v1.Length(),
		L = Len/4;
	double dt = t.DiffVector().Min();
    vdouble C;
	double mean1 = v1.Mean();
	double mean2 = v2.Mean();

    vdouble v1_centred = v1 - mean1;
    vdouble v2_fliped = fliplr(v2);
    vdouble v2_fliped_and_centred = v2_fliped - mean2;

    C = conv(v1_centred, v2_fliped_and_centred);

    Vector<int>  K1_indexes = sequence(Len-1, Len-2+L);

    vdouble K1 = C[K1_indexes];
    vdouble K2_seq = dsequence(double(Len-L), 1.0, double(Len-1));
    vdouble K2=fliplr(K2_seq);
#if 1

	cov  = K1/K2;
#else
    vdouble D1, D2;
	D1 = conv(v1-mean1, fliplr(v1)-mean1);
	D2 = conv(v2-mean2, fliplr(v2)-mean2);
	vdouble sigma1=sqrt(D1[sequence(Len-1, Len-2+L)]/K2);
	vdouble sigma2=sqrt(D2[sequence(Len-1, Len-2+L)]/K2);
	cov  = K1/K2/sigma1/sigma2;
#endif
	tcov = dsequence(0.0, dt, dt*(L-1));
	return true;

}

/*
void inline operator<<(CArchive& ar, vdouble& v)
{
	ar << v.m_length;
	ar << v.m_dims;
	for (int dim = 0; dim < v.m_dims; dim++)
		ar << v.m_size[dim];

	double *vpD;
	vpD = v.pD;

	for (int i = 0; i < v.m_length; i++)
		ar << *(vpD + i);

}
void inline operator>>(CArchive& ar, vdouble& v)
{
	ar >> v.m_length;
	ar >> v.m_dims;
	v.m_size = Vector<int>(v.m_dims);
	for (int dim = 0; dim < v.m_dims; dim++)
		ar >> v.m_size[dim];

	vdouble::m_nConstructions++;

	if ((v.pD = (double*)malloc(v.m_length*SD)) == NULL && v.m_length != 0)
	{
		v.m_length = 0;
		AfxMessageBox("operator>>(CArchive& ar, vdouble& v) - Not enough memory");
		AfxThrowMemoryException();
		return;
	}
	vdouble::m_szMemory +=v.m_length*SD;
	v.m_isgorizontal=true;

	double *vpD;
	vpD = v.pD;

	for (int i = 0; i < v.m_length; i++)
		ar >> *(vpD + i);

}
*/
//##2
#endif /*_VDOUBLE_*/
