#pragma once
#include "./BraidedNode.h"

#include <vector>
using namespace std;
void DoMyMethod(vector<double> & X,
				vector<double> & Y,
				vector<double> & signal,
				string name);

#include "./../array/src/sparse_row_element.h"


#ifdef _MSC_VER
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
#endif
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

  /*
  Конструкторы и деструкторы
  Конструктор класса BraidedSearchTree инициализирует элементы данных cmp для функции сравнения и root для пустого дерева, представленного в виде изолированного головного узла:
  */



  BraidedSearchTree<T>(int (*c) (T, T) ) : cmp(c)
  {
    win = root = new BraidedNode<T> (NULL);
  }
  /*
  Деструктор класса удаляет дерево целиком, обращаясь к деструктору головного узла:
  */

  virtual ~BraidedSearchTree<T> (void)
  {
    if (root) delete root;
    root = NULL;
  }

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

#ifdef _MSC_VER
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
#endif
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



/*
Использование ленты


Элемент данных win описывает окно для дерева — т. е. элемент
win указывает на узел, над которым располагается окно.
Компонентные функции next и prew перемещают окно на
следующую или предыдущую позиции. Если окно находится
в головной позиции, то функция next перемещает его на
первую позицию, а функция prew — на последнюю позицию.
Обе функции возвращают ссылку на элемент в новой позиции
окна:
*/
template<class T>  T BraidedSearchTree<T>::next (void)
{
win = win->next();
return win->val;
}

template<class T> T BraidedSearchTree<T>::prev(void)
{
win = win->prev();
return win->val;
}
/*
Компонентная функция val возвращает ссылку на элемент внутри окна. Если окно находится в головной позиции, то возвращается значение NULL.
*/
template<class T> T BraidedSearchTree<T>::val (void)
{
return win->val;
}
/*
Симметричный обход выполняется путем прохода по ленте от первой позиции до последней, применяя функцию visit для каждого элемента на своем пути:
*/
template<class T>
void BraidedSearchTree<T>::inorder (void (*visit) (T, void * ), void * p )
{
BraidedNode<T> *n = root->next();
while (n != root) {
(*visit)(n->val, p);
n = n->next();
}
}
/*
Компонентные функции isFirst, isLast и isHead возвращают значение TRUE (истина), если окно находится в первой, последней или головной позициях соответственно.
*/
template<class T> bool BraidedSearchTree<T>::isFirst (void)
{
return (win == root->next() ) && (root != root->next ());
}

template<class T> bool BraidedSearchTree<T>::isLast (void)
{
return (win == root->prev() ) && (root != root->next() );
}

template<class T> bool BraidedSearchTree<T>::isHead (void)
{
return   (win == root);
}
/*
Функция isEmpty возвращает значение TRUE (истина) только если текущее дерево пусто и состоит только из одиночного головного узла:
*/
template<class T> bool BraidedSearchTree<T>::isEmpty ()
{
return   (root == root->next() );
}


/*
Поиск

Для поиска элемента используется компонентная функция find. Эта функция аналогична функции SearchTree::find за исключением того, что она начинает свой поиск с root->rchild(), фактического корня. Если элемент найден, то окно устанавливается на этом элементе.
*/

template<class T> T BraidedSearchTree<T>::find (T val)
{
BraidedNode<T> *n = root->rchild();
if (_find (val, n))
    return (n ? n->val : NULL);
return NULL;
}
template<class T> bool BraidedSearchTree<T>::_find (T val, BraidedNode<T> *& n)
{
while (n) {
int result = (*cmp) (val, n->val);
if (result < 0)
  n = n->lchild();
else if (result > 0)
  n = n->rchild();
else {
  win=n;
  return true;
}
}
return false;
}

/*
Наименьший элемент в связанном дереве поиска располагается в первой позиции ленты. Компонентная функция findMin перемещает окно на этот наименьший элемент и возвращает указатель на элемент. Если дерево поиска пусто, то возвращается NULL :
*/
template<class T> T BraidedSearchTree<T>::findMin (void)
{
win = root->next ();
return win->val;
}
template<class T> T BraidedSearchTree<T>::findMax (void)
{
win = root->prev ();
return win->val;
}

/*

Включение элементов





Новый элемент должен быть внесен в его правильной позиции как в дерево поиска, так и в ленту. Если новый элемент становится левым потомком, то тем самым он становится предшественником предка в ленте. Если элемент становится правым потомком, то он становится последователем предка в ленте. Реализация функции insert одинакова с функцией SearchTree: : insert за исключением дополнительного включения нового узла в ленту. Однако следует заметить, что в функции insert нет необходимости проверки включения в пустое дерево, поскольку головной узел присутствует всегда. Функция располагает окно над только что внесенным элементом и возвращает указатель нa элемент, если включение произошло успешно.
*/
template<class T> T BraidedSearchTree<T>::insert(T val)
{
int result = 1;
BraidedNode<T> *p = root;
BraidedNode<T> *n = root->rchild();
while (n) {
p = n;
result = (*cmp) (val, p->val);
if (result < 0)
  n = p->lchild();
else if (result > 0)
  n = p->rchild();
else
  return NULL;
}
win = new BraidedNode<T>(val);
if (result < 0) {
p->_lchild = win;
p->prev()->Node::insert(win);
} else {
p->_rchild = win;
p->Node::insert(win);
}
return val;
}

/*

Удаление элементов





Компонентная функция remove удаляет элемент, находящийся в окне и перемещает окно в предыдущую позицию:
*/
template<class T> bool BraidedSearchTree<T>::remove(void)
{
if (win != root)
return _remove(win->val, root->_rchild);
return false;
}
template<class T> bool BraidedSearchTree<T>::remove(T val)
{
#if 1
return _remove(val, root->_rchild);
#else
//ускорить функцию за счёт применения более быстрой версии _remove()
BraidedNode<T> * n = _find(val);
if(n)
    _remove(n);
#endif
}
/*
Элемент val, подлежащий удалению, и указатель n на корень дерева поиска, в котором находится этот элемент, передаются в качестве параметров собственной функции _remove. Эта функция работает подобно своему аналогу с тем же именем в классе SearchTree. Однако при работе со связанным деревом поиска элемент, конечно, должен быть удален как из дерева поиска, так и из ленты:
*/

template<class T>
bool BraidedSearchTree<T>::_remove(T val, TreeNode<T>* &n)
{
if (n == NULL)
    return false;
int result = (*cmp) (val, n->val);
if (result < 0)
return _remove(val, n->_lchild);
else if (result > 0)
return _remove(val, n->_rchild);
else {                         // случай 1
if (n->_lchild == NULL) {
  BraidedNode<T> *old = (BraidedNode<T>*)n;
  if (win == old)
    win = old->prev();
  n = old->rchild();
  old->_rchild = NULL;
  old->Node::remove();
  delete old;
  return true;
}
else if (n->_rchild == NULL) { // случай 2
  BraidedNode<T> *old = (BraidedNode<T>*)n;
  if (win == old)
    win = old->prev();
  n = old->lchild();
  old->_lchild = NULL;
  old->Node::remove();
  delete old;
  return true;
}
else  {                       // случай 3
  BraidedNode<T> *m = ( (BraidedNode<T>*)n)->next();
  n->val = m->val;
  return _remove(m->val, n->_rchild);
}
}
return false;
}
/*
template<class T>
void BraidedSearchTree<T>::_remove(TreeNode<T>* &n)
{
if (n == NULL)
    return;
else {                         // случай 1
    if (n->_lchild == NULL)
    {
        BraidedNode<T> *old = (BraidedNode<T>*)n;
        if (win == old)
            win = old->prev();
        n = old->rchild();
        old->_rchild = NULL;
        old->Node::remove();
        delete old;
    }
    else if (n->_rchild == NULL)
    { // случай 2
        BraidedNode<T> *old = (BraidedNode<T>*)n;
        if (win == old)
            win = old->prev();
        n = old->lchild();
        old->_lchild = NULL;
        old->Node::remove();
        delete old;
    }
    else
    {                       // случай 3
        BraidedNode<T> *m = ( (BraidedNode<T>*)n)->next();
        n->val = m->val;
        _remove(m);
    }
}
}
*/
/*
Заметим, что функция _remove использует ленту для поиска последователя узла n в случае 3, когда подлежащий удалению узел имеет два непустых потомка. Отметим также, что параметр n является ссылкой на тип TreeNode*, а не на тип BraidedNode*. Это происходит потому, что n указывает на ссылку, хранящуюся в предке узла, подлежащего удалению, а эта ссылка имеет тип TreeNode*. Если бы вместо этого параметру n был присвоен тип BraidedNode*, то это была бы ошибочная ссылка на анонимный объект. При этом поле ссылки в узле предка было бы недоступно.

Компонентная функция removeMin удаляет из дерева наименьший элемент и возвращает указатель на него, функция возвращает значение NULL, если дерево пусто. Если окно содержало удаляемый наименьший элемент, то окно перемещается в головную позицию, в ином случае оно остается без изменения:
*/
template<class T> T BraidedSearchTree<T>::removeMin(void)
{
#if 1
T val = root->next()->val;
if (root != root->next() )
_remove(val, root->_rchild);
return val;
#else
BraidedNode<T> * m = root->next();
T val = m->val;
if (root != root->next() )
    _remove(m);
return val;
#endif
}


} //namespace

