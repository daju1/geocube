#pragma once
#include "StdAfx.h"

namespace geometry2D
{

	/*
Конструкторы и деструкторы 

 

 

Конструктор класса BraidedSearchTree инициализирует элементы данных cmp для функции сравнения и root для пустого дерева, представленного в виде изолированного головного узла:

template<class T>
BraidedSearchTree<T>::BraidedSearchTree (int (*с) (T, T) ) :
  cmp(c)
{
  win = root = new BraidedNode<T> (NULL);
}
*/
template<class T>
BraidedSearchTree<T>::BraidedSearchTree<T>(int (*c) (T, T) ) : cmp(c)
{
	win = root = new BraidedNode<T> (NULL);
}
/*
Деструктор класса удаляет дерево целиком, обращаясь к деструктору головного узла:
*/
template<class T>
BraidedSearchTree<T>::~BraidedSearchTree<T> (void)
{			
	if (root) delete root;	root = NULL;
}

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
