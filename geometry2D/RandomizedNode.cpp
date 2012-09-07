//#pragma once

#include "StdAfx.h"

namespace geometry2D
{
	/*
Конструктор присваивает новому узлу RandomizedNode случайное значение приоритета, используя стандартную функцию языка C++ rand, которая генерирует случайное число в пределах от 0 до RAND_MAX :
*/
template<class T>
RandomizedNode<T>::RandomizedNode(T v, int seed) :
  BraidedNode<T>(v)
{
  if (seed != -1) srand(seed);
  _priority = (rand() % 32767) / 32767.f;
  _parent = NULL;
}
/*
Наибольший интерес представляют компонентные функции класса RandomizedNode, объявленные как private (собственные). Первые две выполняют два вида ротации — правую и левую. Правая ротация является локальной операцией, которая изменяет форму дерева поиска, оставляя неизменным порядок следования элементов — до и после выполнения операции предшественник и последователь для каждого узла остаются без изменения. Правая ротация для узла у приводит к повороту поддерева с корнем в узле у вокруг связи от узла у к его левому потомку х (рис. 2). Операция выполняется путем изменения небольшого числа связей: связь с левым потомком узла у заменяется на связь с поддеревом T2, связь с правым потомком узла х заменяется на связь с узлом у, а связь с узлом у (от его предка) заменяется на связь с узлом х.

Компонентная функция rotateRight выполняет правую ротацию для текущего узла, который играет роль узла у. При этом узел х должен быть левым потомком узла у. Для надежности предполагается, что предок узла у существует, поскольку головной узел должен иметь минимальный приоритет — ни одного другого узла не должно быть на уровне головного узла, поэтому все остальные узлы должны иметь своего предка.
*/
template<class T> void RandomizedNode<T>::rotateRight(void)
{
  RandomizedNode<T> *y = this;
  RandomizedNode<T> *x = y->lchild();
  RandomizedNode<T> *p = y->parent();
  y->_lchild = x->rchild();
  if (y->lchild() != NULL)
    y->lchild()->_parent = y;
  if (p->rchild() == y)
    p->_rchild = x;
  else
    p->_lchild = x; 
  x->_parent = p;
  x->_rchild = y;
  y->_parent = x;
}
/*
Действие компонентной функции rotateLeft для левой ротации также показано на рис. 2 и она определяется симметрично:
*/
template<class T> void RandomizedNode<T>::rotateLeft(void)
{
  RandomizedNode<T> *x = this;
  RandomizedNode<T> *y = x->rchild();
  RandomizedNode<T> *p = x->parent();
  x->_rchild = y->lchild();
  if (x->rchild() != NULL)
    x->rchild()->_parent = x;
  if (p->lchild() == x)
    p->_lchild = y;
  else
    p->_rchild = y;
  y->_parent = p;
  y->_lchild = x;
  x->_parent = y;
}
/*
Компонентная функция bubbleUp переносит текущий узел вверх по направлению к корню путем многократных ротаций до тех пор, пока приоритет текущего узла не станет больше или равным, чем у его предка. Функция применяется в тех случаях, когда элемент в дереве случайного поиска располагается ниже, чем это следует в соответствии со значением его приоритета. Отметим, что ротация применяется к предку текущего узла.
*/
template<class T> void RandomizedNode<T>::bubbleUp(void)
{
  RandomizedNode<T> *p = parent();
  if (priority() < p->priority() ) {
    if (p->lchild() == this)
      p->rotateRight();
     else
       p->rotateLeft();
     bubbleUp();
  }
}
/*
Компонентная функция bubbleDown переносит текущий узел вниз по направлению к внешним узлам дерева путем многократных ротаций до тех пор, пока приоритет текущего узла не станет меньше или равным приоритетам обоих его потомков. Для ротации ее направление (вправо или влево) зависит от того, какой из потомков текущего узла имеет меньший приоритет. Если, например, приоритет левого потомка меньше, то правая ротация переносит левый потомок вверх на один уровень, а текущий узел перемещается на один уровень вниз. Каждому внешнему узлу приписывается приоритет 2.0, достаточно большой, чтобы ошибочно не переместить его вверх. Функция bubbleDown применяется в тех случаях, когда элемент в дереве случайного поиска располагается выше, чем это следует в соответствии со значением его приоритета. Эта функция будет использована впоследствии для удаления элемента из дерева поиска.
*/
template<class T> void RandomizedNode<T>::bubbleDown(void)
{
  float lcPriority = lchild() ? lchild()->priority () : 2.f;
  float rcPriority = rchild() ? rchild()->priority () : 2.f;
  float minPriority = (lcPriority < rcPriority) ? lcPriority : rcPriority;
  if (priority () <= minPriority)
    return;
  if (lcPriority < rcPriority)
    rotateRight();
  else
    rotateLeft();
  bubbleDown();
}
/*
Общедоступные компонентные функции rchild, Ichild, next, prev и parent определяют связи текущего узла с его правым и левым потомками, с последующим и предшествующим узлами и с предком соответственно:
*/
template<class T>
RandomizedNode<T>* RandomizedNode<T>::rchild(void)
{
	
  return (RandomizedNode<T>*) _rchild;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::lchild(void)
{
  return (RandomizedNode<T>*) _lchild;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::next(void)
{
  return ( RandomizedNode<T>*) _next;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::prev(void)
{
  return (RandomizedNode<T>*)_prev;
}

template<class T>
RandomizedNode<T> * RandomizedNode<T>::parent(void)
{
  return (RandomizedNode<T>* ) _parent ;
}
/*
Компонентная функция priority возвращает приоритет текущего узла:
*/
template<class T>
float RandomizedNode<T>::priority(void)
{
  return _priority;
}


} //namespace