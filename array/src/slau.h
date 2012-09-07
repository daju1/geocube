
#if !defined(_SLAU_H_)
#define _SLAU_H_

#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "../../surfdoc/src/archive.h"


#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std ;

template <class T> class sparse_row_element
{
public:
	size_t col;
	T val; 
	sparse_row_element(size_t c, T v) : col(c), val(v){}
	sparse_row_element(int ) : col(0), val(0.0){}
	//sparse_row_element(const sparse_row_element & r) : col(r.col), val(r.val){}
	virtual ~sparse_row_element(){}
};

class sparse_row_simple : public std::vector<sparse_row_element<double> >
{
public:
	bool put(size_t j, double a)
	{
		if (a == 0.0)
			return false;
		sparse_row_element<double> tmp(j,a);
		this->push_back(tmp);
		return true;
	}
	double ScalarProduct(vector<double>& x)
	{
		double product = 0.0;
		//size_t x_size = x.size();
		vector<sparse_row_element<double> >::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			//size_t c = (*it).col;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				product += (*it).val * x[(*it).col];
			//}
		}
		return product;
	}
	void CorrelationCoefficient(vector<double> & x, double & k, double & Cov)
	{
		size_t len = 0;
		double 
			sum1 = 0.0,
			sum2 = 0.0;

		//for (size_t i = 0; i < len; i++)
		//{
		//	sum1 += v1[i];
		//	sum2 += v2[i];
		//}

		//double product = 0.0;
		//size_t x_size = x.size();
		vector<sparse_row_element<double> >::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			//size_t c = (*it).col;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				//product += (*it).val * x[(*it).col];
				sum1 += (*it).val;
				sum2 += x[(*it).col];
				++len;
			//}
		}

		double 
			mean1 = sum1 / len,
			mean2 = sum2 / len;

		double 
			sigma1 = 0.0,
			sigma2 = 0.0;

		Cov = 0.0;

		//for (i = 0; i < len; i++)
		//{
		//	sigma1 += (v1[i] - mean1)*(v1[i] - mean1);
		//	sigma2 += (v2[i] - mean2)*(v2[i] - mean2);
		//	Cov += (v1[i] - mean1)*(v2[i] - mean2);
		//}
		for(it = this->begin(); it != this->end(); it++)
		{
			//size_t c = (*it).col;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				//product += (*it).val * x[(*it).col];
				sigma1 += ((*it).val - mean1) * ((*it).val - mean1);
				sigma2 += (x[(*it).col] - mean2) * (x[(*it).col] - mean2);
				Cov += ((*it).val - mean1)*(x[(*it).col] - mean2);
			//}
		}
		k = Cov/sqrt(sigma1*sigma2);
	}



	
	void Reconstruct_b_by_my_as_part_of_symmetric_matrix_row(vector <double> & b_rec, long r, vector<double>& x)
	{
		//size_t x_size = x.size();
		vector<sparse_row_element<double> >::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			size_t c = (*it).col;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
				b_rec[r] += (*it).val * x[c];
			if (r != c)
			{
				//if (r < x_size)
					b_rec[c] += (*it).val * x[r];
			}			
		}
	}
	
		
	double ScalarProduct_fast(sparse_row_simple & r2)
	{
		double product = 0.0;

		std::vector<sparse_row_element<double> >::iterator n1 = this->begin();
		std::vector<sparse_row_element<double> >::iterator n2 = r2.begin();

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
	}
	friend Archive& operator <<(Archive& ar, sparse_row_simple& ob);
	friend Archive& operator >>(Archive& ar, sparse_row_simple& ob);

	void InverseSave(Archive& ar)
	{
		long cc;
		double value;
		vector<sparse_row_element<double> >::reverse_iterator it;
		for(it = this->rbegin(); it != this->rend(); it++)
		{
			long cc = long((*it).col);
			double value = (*it).val;
			ar << cc;
			ar << value;
		}
		//признак конца записи
		cc = -1;
		value = 0.0;
		ar << cc;
		ar << value;

	}
};

class sparse_row_map : public std::map<size_t, double>
{
public:
	bool put(size_t j, double a)
	{
		if (a == 0.0)
			return false;
		this->insert(map<size_t, double>::value_type(j,a));
		return true;
	}
	double ScalarProduct(vector<double>& x)
	{
		double product = 0.0;
		//size_t x_size = x.size();
		map<size_t, double>::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			//size_t c = (*it).first;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				product += (*it).second * x[(*it).first];
			//}
		}
		return product;
	}
	void multip_equal (double x)
	{
		map<size_t, double>::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			(*it).second *= x;
		}
	}

	void multip_equal (vector<double>& x)
	{
		//size_t x_size = x.size();
		map<size_t, double>::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			//size_t c = (*it).first;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				//this->val().val *= x[this->val().col];
				(*it).second *= x[(*it).first];
			//}
		}
	}
	double Sum()
	{
		double sum = 0.0;
		map<size_t, double>::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			sum += (*it).second;
		}
		return sum;
	}
	double SumExcludeColomn(size_t col)
	{
		double sum = 0.0;
		map<size_t, double>::iterator it;
		for(it = this->begin(); it != this->end(); it++)
		{
			if (col != (*it).first)
			{
				sum += (*it).second;
			}
		}
		return sum;
	}
	bool replace(size_t j, double a)
	{
		std::map<size_t, double>::iterator found = this->find(j);
		if (found != this->end())
		{
			(*found).second = a;
		}
		else
		{
			this->put(j, a);
		}
		return true;
	}


	friend Archive& operator <<(Archive& ar, sparse_row_map& ob);
	friend Archive& operator >>(Archive& ar, sparse_row_map& ob);

};

#include "../../geometry2D/BraidedSearchTree.h"
using namespace geometry2D;
int cmpCol (sparse_row_element<double> e1,sparse_row_element<double> e2);
#define SPARSE_ROW_EX 0
//#define SparseRowDictionary RandomizedSearchTree
#define SparseRowDictionary BraidedSearchTree
class sparse_row : public SparseRowDictionary <sparse_row_element<double>  >
{
public:
#if SPARSE_ROW_EX
	int _order;
	double _weight; // вес строки при решении уравнения методом наименьших квадратов
	size_t min_col;
	size_t max_col;
#endif


	void swap(sparse_row & r)
	{
		BraidedNode<sparse_row_element<double> > * tmp_root = this->root;    // головной узел
		BraidedNode<sparse_row_element<double> > * tmp_win  = this->win;     // текущее окно
		this->root = r.root;
		this->win  = r.win;

		r.root = tmp_root;
		r.win  = tmp_win;		
	}

	sparse_row() : BraidedSearchTree<sparse_row_element<double> >(cmpCol){
#if SPARSE_ROW_EX
		min_col = 0;max_col = 0;_order = 0;_weight = 1.0;
#endif
	}


	//sparse_row (sparse_row & r) : BraidedSearchTree<sparse_row_element<double> >(r){}

	sparse_row (const sparse_row & tree) : BraidedSearchTree<sparse_row_element<double> >(tree.cmp)
	{
		this->BraidedSearchTree<sparse_row_element<double> >::Init(tree);
#if SPARSE_ROW_EX
		min_col = tree.min_col;
		max_col = tree.max_col;
		_order   = tree._order;
		_weight   = tree._weight;
#endif	
	}

	sparse_row& operator= (const sparse_row & tree)
	{
		if (this == &tree)
		{
			return *this;
		}

		this->BraidedSearchTree<sparse_row_element<double> >::Init(tree);
#if SPARSE_ROW_EX
		min_col = tree.min_col;
		max_col = tree.max_col;
		_order   = tree._order;
		_weight   = tree._weight;
#endif
		return *this;
	}
#if SPARSE_ROW_EX
	void FindMinCol()
	{
		this->min_col = this->findMin().col;
	}
	void FindMaxCol()
	{
		this->max_col = this->findMax().col;
	}
#endif
	/*bool operator< (sparse_row & r)
	{
		return this->min_col < r.min_col;
	}

	bool operator> (sparse_row & r)
	{
		return this->min_col > r.min_col;
	}*/

	void multip_equal (double x)
	{
		for(this->first();!this->isHead(); this->next())
		{
			this->win->val.val *= x;
		}
	}

	void multip_equal (vector<double>& x)
	{
		//size_t x_size = x.size();
		for(this->first();!this->isHead(); this->next())
		{
			//size_t c = this->val().col;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				//this->val().val *= x[this->val().col];
				this->win->val.val *= x[this->val().col];
			//}
		}
	}

	double ScalarProduct(vector<double>& x)
	{
		double product = 0.0;
		//size_t x_size = x.size();
		for(this->first();!this->isHead(); this->next())
		{
			//size_t c = this->val().col;
			//if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
			//{
				product += this->val().val * x[this->val().col];
			//}
		}
		return product;
	}
	double Sum()
	{
		double sum = 0.0;
		for(this->first();!this->isHead(); this->next())
		{
			sum += this->val().val;
		}
		return sum;
	}
	double SumExcludeColomn(size_t col)
	{
		double sum = 0.0;
		for(this->first();!this->isHead(); this->next())
		{
			if (col != this->val().col)
			{
				sum += this->val().val;
			}
		}
		return sum;
	}
	friend Archive& operator <<(Archive& ar, sparse_row& ob);
	friend Archive& operator >>(Archive& ar, sparse_row& ob);

	typedef BraidedNode<sparse_row_element<double> > * sparse_row_node_ptr;
	
	void SaveDissorted(Archive& ar)
	{
		size_t tree_size = 0;
		for(this->first();!this->isHead(); this->next())
		{
			tree_size++;
		}

		
		sparse_row_node_ptr * vn = new sparse_row_node_ptr[tree_size+1];
		memset(vn,0,(tree_size+1)*sizeof(sparse_row_node_ptr));

		vn[0] = this->root->rchild();	

		size_t i, i_first = 0, i_pre_last, i_last = 0;		

		while (vn[i_first])
		{
			i_pre_last = i_last;
			for (i = i_first; i <= i_pre_last; i++)
			{
				sparse_row_node_ptr lf = vn[i]->lchild();
				sparse_row_node_ptr rt = vn[i]->rchild();
				if (lf) vn [++i_last] = lf;
				if (rt) vn [++i_last] = rt;
			}
			i_first = i_pre_last+1;
		}
		
		long cc;
		double value;

		for (i = 0; i < tree_size; i++)
		{
			long cc = long(vn[i]->val.col);
			double value = vn[i]->val.val;
			ar << cc;
			ar << value;
		}

		cc = -1;
		value = 0.0;
		ar << cc;
		ar << value;

		delete [] vn;
	}

	void save_node (sparse_row_node_ptr n, Archive& ar)
	{
		if (n) 
		{				
			long cc = long(n->val.col);
			double value = n->val.val;
			ar << cc;
			ar << value;

			save_node (n->lchild(), ar);
			save_node (n->rchild(), ar);
		}
	}

	void SaveDissorted_recursive(Archive& ar)
	{
		sparse_row_node_ptr n = this->root->rchild();

		save_node(n, ar);

		long cc = -1;
		double value = 0.0;
		ar << cc;
		ar << value;
	}

	void InverseSortedSave(Archive& ar)
	{
		long cc;
		double value;
		for(this->last();!this->isHead(); this->prev())
		{
			long cc = long(this->val().col);
			double value = this->val().val;
			ar << cc;
			ar << value;
		}

		cc = -1;
		value = 0.0;
		ar << cc;
		ar << value;
	}
	/*
	BraidedNode<T> *n = root->rchild();
	if (_find (val, n)) 
	

	BOOL Find (size_t j)
{
  while (n) {
    int result = (*cmp) (val, n->val);
    if (result < 0)
      n = n->lchild();
    else if (result > 0)
	  n = n->rchild();
	else {
      win=n;
      return TRUE;
    }
  }
  return FALSE;
}*/
};

// Return whether first element is greater than the second
bool sparse_row_greater ( sparse_row elem1, sparse_row elem2 );
#if SPARSE_ROW_EX
void SaveMatrixMinMaxCol(vector<sparse_row>& a, char * dat_file);
#endif

template <class T>
T Mean(vector<T>& v) // Возврашает сумму квадратов элементов вектора
{
	T _Mean = 0;		
	for(vector<T>::iterator it = v.begin(); it != v.end(); it++)
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
	for(vector<T>::iterator it = v.begin(); it != v.end(); it++)
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
	for(vector<T>::iterator it = v.begin(); it != v.end(); it++)
	{
		_Sum += (*it);
	}
	return _Sum;
}

template <class T>
T SquareSum(vector<T>& v) // Возврашает сумму квадратов элементов вектора
{
	T _SquareSum = 0;		
	for(vector<T>::iterator it = v.begin(); it != v.end(); it++)
	{
		_SquareSum += (*it) * (*it);
	}
	return _SquareSum;
}

template <class T>
T SquareSum(vector<T>& v1, vector<T>& v2) // Возврашает сумму квадратов элементов вектора

{
	T _SquareSum = 0;	
	vector<T>::iterator it1;
	vector<T>::iterator it2;
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
	vector<T>::iterator it1;
	vector<T>::iterator it2;
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
void SparseStructureToMetafile(char * fn_spm, char * fn_emf = NULL);

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