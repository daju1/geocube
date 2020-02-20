#pragma once

#include <vector>
using namespace std;

void DoMyMethod(vector<double> & X,
				vector<double> & Y,
				vector<double> & signal,
				string name);

class sparse_row;
// получить граф в виде полной структуры смежности 
// или нижней структуры смежности 
// ( в зависимости от значения переменной  bool to_form_full_structure ) 
// из симметричной положительно определённой матрицы. 
// Формат получаемого графа в виде вектора разреженных строк

bool Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag);

// теперь полученный граф преобразуем к форме хранения XADJ, ADJNCY
// этой же функцией можно преобразовывать и матрицу

bool Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values);

// обратное преобразование графа в форму vector<sparse_row>
// этой же функцией можно преобразовывать и матрицу

bool Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G);

// определить ширину ленты матрицы

int Get_Band_Len(vector<sparse_row> & m, vector<int> & beta);

// определить ширину фронта матрицы

int Get_Front_Width(vector<sparse_row> & m, vector<int> & omega);

// получить граф в виде полной структуры смежности 
// или нижней структуры смежности 
// ( в зависимости от значения переменной  bool to_form_full_structure ) 
// из симметричной положительно определённой матрицы. 
// Формат получаемого графа в виде вектора разреженных строк

bool Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag);

// теперь полученный граф преобразуем к форме хранения XADJ, ADJNCY
// этой же функцией можно преобразовывать и матрицу

bool Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values);

// обратное преобразование графа в форму vector<sparse_row>
// этой же функцией можно преобразовывать и матрицу

bool Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G);

// определить ширину ленты матрицы

size_t Get_Band_Len(vector<sparse_row> & m, vector<size_t> & beta);

// определить ширину фронта матрицы

size_t Get_Front_Width(vector<sparse_row> & m, vector<size_t> & omega);

// преобразование симметричной положительно определённой матрицы 
// в верхнетреугольный множитель Холесского
// на вход подаётся верхнетреугольная часть симметричной положительно определённой матрицы
// функция разрушает исходные данные

bool Holesski(vector<sparse_row> & m);
bool Holesski3(vector<sparse_row> & m);
bool Holesski(char * fn_min_sq_mat, char * fn_Lt, char * dir);
bool Holesski3(const char * fn_min_sq_mat, const char * fn_Lt, char * dir, long j_start, double alpha);
bool Holesski3_in_operative_memory(char * fn_min_sq_mat, char * fn_Lt, char * dir, double alpha);
// 
// Дальше этой функцией решаем треугольную систему уравнений 
// с верхнетреугольным множителем Холесского
// 

bool tria_solve_of_down (vector<sparse_row> t,
	vector<double> b, vector<double>& x);
// 
// Дальше этой функцией решаем треугольную систему уравнений 
// с верхнетреугольным множителем Холесского
// 

bool tria_solve_of_up (vector<sparse_row> & t,
	vector<double>& b, vector<double>& x);


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

namespace geometry2D
{
	/*
При реализации двоичных деревьев, основанной на точечном представлении, узлы являются объектами класса TreeNode.
*/
template<class T> class SearchTree;
template<class T> class BraidedSearchTree;
//template<class T> class sparse_row_element;
//class sparse_row : public template<class T> class BraidedSearchTree <T>;
//class sparse_row : public BraidedSearchTree <sparse_row_element<double> * >; 

template<class T> class TreeNode {
 protected:
  TreeNode  *_lchild;
  TreeNode  *_rchild;
  T val;
 public:
	 T Val(){return val;} // my test
  TreeNode(T);
  TreeNode(TreeNode& n);
  virtual ~TreeNode(void);
  friend class SearchTree<T>;        // возможные пополнения
  friend class BraidedSearchTree<T>; // структуры
  friend class sparse_row; // структуры

	friend void ::DoMyMethod(vector<double> & X,
				vector<double> & Y,
				vector<double> & signal,
				string name);


	// получить граф в виде полной структуры смежности 
	// или нижней структуры смежности 
	// ( в зависимости от значения переменной  bool to_form_full_structure ) 
	// из симметричной положительно определённой матрицы. 
	// Формат получаемого графа в виде вектора разреженных строк

	friend bool ::Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag);

	// теперь полученный граф преобразуем к форме хранения XADJ, ADJNCY
	// этой же функцией можно преобразовывать и матрицу

	friend bool ::Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values);

	// обратное преобразование графа в форму vector<sparse_row>
	// этой же функцией можно преобразовывать и матрицу

	//friend bool ::Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G);

	// определить ширину ленты матрицы

	friend int ::Get_Band_Len(vector<sparse_row> & m, vector<int> & beta);

	// определить ширину фронта матрицы

	friend int ::Get_Front_Width(vector<sparse_row> & m, vector<int> & omega);




	// преобразование симметричной положительно определённой матрицы 
	// в верхнетреугольный множитель Холесского
	// на вход подаётся верхнетреугольная часть симметричной положительно определённой матрицы
	// функция разрушает исходные данные

	friend bool ::Holesski(vector<sparse_row> & m);
	friend bool ::Holesski3(vector<sparse_row> & m);
	friend bool ::Holesski(char * fn_min_sq_mat, char * fn_Lt, char * dir);
	friend bool ::Holesski3(const char * fn_min_sq_mat, const char * fn_Lt, char * dir, long j_start, double alpha);
	friend bool ::Holesski3_in_operative_memory(char * fn_min_sq_mat, char * fn_Lt, char * dir, double alpha);

	// 
	// Дальше этой функцией решаем треугольную систему уравнений 
	// с верхнетреугольным множителем Холесского
	// 

	friend bool ::tria_solve_of_down (vector<sparse_row> t,
		vector<double> b, vector<double>& x);
	// 
	// Дальше этой функцией решаем треугольную систему уравнений 
	// с верхнетреугольным множителем Холесского
	// 

	friend bool ::tria_solve_of_up (vector<sparse_row> & t,
		vector<double>& b, vector<double>& x);



	friend bool ::SLAU_excl(size_t prec_eqns,
			   vector<sparse_row > & a,
			   size_t cols, vector<double> & alpha,
			   vector<double> & b,
			   vector<double> & sol);

	friend bool ::Tichonov(size_t cols,
		vector<sparse_row> & A,
		vector<double> & b,
		vector<double> & x,
		bool AlphaNonZero);


	friend bool ::Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  vector<double> & valpha);


};
/*
Элементы данных _lchild и _rchild обозначают связи текущего узла с левым и правым потомками соответственно, а элемент данных val содержит сам элемент.
*/
} // namespace

#include "./TreeNode.cpp"
