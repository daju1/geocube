#pragma once
#include "./BraidedNode.h"

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

bool Tichonov(size_t cols, 
			  vector<sparse_row> & A,
			  vector<double> & b,
			  vector<double> & x,
			  bool AlphaNonZero);
bool Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  vector<double> & valpha);

namespace geometry2D
{
	/*
	Класс BraidedSearchTree 
	Шаблон класса BraidedSearchTree определяется следующим образом:
	*/
template<class T> class BraidedSearchTree {
 protected:
  BraidedNode<T> *root;    // головной узел
  BraidedNode<T> *win;     // текущее окно
  int (*cmp) (T,T);        // функция сравнения
  //void _remove(TreeNode<T> * &);
  bool _remove(T, TreeNode<T> * &);
  bool _find (T val, BraidedNode<T> *& );
 public:
  BraidedSearchTree (int(*) (T,T) );
  ~BraidedSearchTree (void);
  T next (void);
  T prev (void);
  void inorder (void(*) (T, void * ), void * );
  T val (void);
  bool isFirst (void);
  bool isLast (void);
  bool isHead (void);
  bool isEmpty (void);
  T find (T);
  T findMin (void);
  T findMax (void);
  T insert (T);
  bool remove (void);
  bool remove (T val);
  T removeMin (void);

protected:
	//BraidedSearchTree(){}
	void __inorder (BraidedNode<T> *n)
	{
		if (n) 
		{				
			__inorder (n->lchild());
			this->win = (BraidedNode<T> *)this->win->Node::insert((Node*)n);
			__inorder (n->rchild());
		}
	}
	void Init (const BraidedSearchTree<T> & tree)
	{
		this->cmp = tree.cmp;
		this->win = this->root = new BraidedNode<T>(NULL);
		
		if (tree.root && tree.root->rchild())
			this->root->_rchild = new BraidedNode<T>(*tree.root->rchild());
		
		this->__inorder(this->root->rchild());
	}
public:


	T first (void)
	{
		win = root->next();
		return win->val;        
	}

	T last (void)
	{
		win = root->prev();
		return win->val;        
	}



	BraidedSearchTree<T>& operator= (const BraidedSearchTree<T> & tree)
	{
		if (this == &tree)
		{
			return *this;
		}

		this->Init(tree);

		return *this;
	}

	BraidedSearchTree<T> (const BraidedSearchTree<T> & tree)
	{
		this->Init(tree);
	}

	// for class sparse_row : public BraidedSearchTree <sparse_row_element<double> * >
	double operator[](size_t i)
	{
		sparse_row_element<double> tmp(i,0.0);

		BraidedNode<sparse_row_element<double> > *n = root->rchild();
		if (_find (tmp, n))                 
			return (n->val.val);
		else
			return 0.0;
	}
	bool put(size_t j, double a)
	{
		if (a == 0.0)
			return false;
		sparse_row_element<double> tmp(j,a);
		int result = 1;
		BraidedNode<T> *p = root;
		BraidedNode<T> *n = root->rchild();
		while (n) { 
			p = n;
			result = (*cmp) (tmp, p->val);
			if (result < 0)
				n = p->lchild();
			else if (result > 0)
				n = p->rchild();
			else
			{
				return false;
			}
		}
		win = new BraidedNode<T>(tmp);
		if (result < 0) {
			p->_lchild = win;
			p->prev()->Node::insert(win);
		} else {
			p->_rchild = win;
			p->Node::insert(win);
		}
		return true;
	}
	bool replace(size_t j, double a)
	{
		sparse_row_element<double> tmp(j,a);
		int result = 1;
		BraidedNode<T> *p = root;
		BraidedNode<T> *n = root->rchild();
		while (n) { 
			p = n;
			result = (*cmp) (tmp, p->val);
			if (result < 0)
				n = p->lchild();
			else if (result > 0)
				n = p->rchild();
			else
			{
				p->val.val = tmp.val;
				return true;
			}
		}
		win = new BraidedNode<T>(tmp);
		if (result < 0) {
			p->_lchild = win;
			p->prev()->Node::insert(win);
		} else {
			p->_rchild = win;
			p->Node::insert(win);
		}
		return true;
	}
	T plus(size_t j, double a)
	{
		sparse_row_element<double> tmp(j,a);
		int result = 1;
		BraidedNode<T> *p = root;
		BraidedNode<T> *n = root->rchild();
		while (n) { 
			p = n;
			result = (*cmp) (tmp, p->val);
			if (result < 0)
				n = p->lchild();
			else if (result > 0)
				n = p->rchild();
			else
			{
				//return NULL;
				p->val.val += tmp.val;
				return p->val;
			}
		}
		win = new BraidedNode<T>(tmp);
		if (result < 0) {
			p->_lchild = win;
			p->prev()->Node::insert(win);
		} else {
			p->_rchild = win;
			p->Node::insert(win);
		}
		return win->val;
	}
	void _insert(BraidedNode<T> *n, T val)
	{
		int result = 1;
		BraidedNode<T> *p = root;
		//BraidedNode<T> *n = root->rchild();
		while (n) { 
			p = n;
			result = (*cmp) (val, p->val);
			if (result < 0)
				n = p->lchild();
			else if (result > 0)
				n = p->rchild();
			else
				return;
		}
		win = new BraidedNode<T>(val);
		if (result < 0) {
			p->_lchild = win;
			p->prev()->Node::insert(win);
		} else {
			p->_rchild = win;
			p->Node::insert(win);
		}
		return ;
	}

	double ScalarProduct_fast(BraidedSearchTree <T> /*sparse_row*/ & r2)
	{
		double product = 0.0;

		BraidedNode<T> *n1 = this->root->next();
		BraidedNode<T> *n2 = r2.root->next();

		while( n1 != this->root && n2 != r2.root )
		{
			size_t c1 = n1->val.col;
			size_t c2 = n2->val.col;

			if (c1 == c2)
			{
				product += n1->val.val * n2->val.val;

				n1 = n1->next();
				n2 = n2->next();
				continue;
			}
			if (c1 < c2)
			{
				n1 = n1->next();
			}
			else
			{
				n2 = n2->next();
			}
		}
		return product;
	}
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

	void plus_equal (double mult, BraidedSearchTree <T> /*sparse_row*/ & r)
	{
		BraidedNode<T> *n = this->root->next();
		BraidedNode<T> *m = r.root->next();
		while (n != this->root) {
			while (m != r.root)
			{
				if (m->val.col < n->val.col)
				{
					T tmp(m->val.col, mult * m->val.val);
					//insertion
					if (tmp.val != 0.0)
						this->_insert(n, tmp);
					m = m->next();
				}
				else
				{
					if (m->val.col == n->val.col)
					{
						n->val.val += mult * m->val.val;
						if (n->val.val == 0.0)
						{
							T tmp(n->val.col, 0.0);
							this->remove(tmp);                            
							n = this->win;
						}
						m = m->next();
						break;
					}
					else
					{
						break;
					}
				}
			}			
			n = n->next();
		}
	}
	void multip_equal (double a)
	{
		BraidedNode<T> *n = root->next();
		while (n != root) {
			n->val.val *= a;
			n = n->next();
		}
	}
	void divide_equal (double a)
	{
		BraidedNode<T> *n = root->next();
		while (n != root) {
			n->val.val /= a;
			n = n->next();
		}
	}
	void plus_equal (double a)
	{
		BraidedNode<T> *n = root->next();
		while (n != root) {
			n->val.val += a;
			n = n->next();
		}
	}
	void minus_equal (double a)
	{
		BraidedNode<T> *n = root->next();
		while (n != root) {
			n->val.val -= a;
			n = n->next();
		}
	}
		
	void clear()
	{
		if (root && root->_rchild) 
		{
			delete root->_rchild;
			root->_rchild = NULL;

			root->_prev = root;
			root->_next = root;
		}
	}
};

} //namespace


#include "./BraidedSearchTree.cpp"
