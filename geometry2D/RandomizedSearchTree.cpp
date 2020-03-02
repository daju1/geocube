#pragma once
#include "StdAfx.h"
namespace geometry2D
{
	/*
Конструкторы и деструкторы 

 

 

Конструктор RandomizedsearchTree инициализирует новое дерево случайного поиска, представляемое изолированным головным узлом с минимальным приоритетом, равным -1,0:
*/

/*
Деструктор удаляет дерево поиска:
*/
template<class T>
RandomizedSearchTree<T>::~RandomizedSearchTree<T> (void)
{
  delete root;
}

 
/*
  Использование ленты 

 

 

Компонентные функции next, prev, val, inorder, isFirst, isLast, isHead и is Empty определяются подобно их аналогам в классе

BraidedSearchTree : */
template<class T> T RandomizedSearchTree<T>::next (void)
{
  win = win->next();
  return win->val;
}

template<class T> T RandomizedSearchTree<T>::prev (void)
{
  win = win->prev();
  return win->val;
}

template<class T> T RandomizedSearchTree<T>::val (void)
{
  return win->val;
}

template<class T>
void RandomizedSearchTree<T>::inorder (void (*visit) (T, void * ), void * p )
{
  RandomizedNode<T> *n = root->next();
  while (n != root) {
    (*visit) (n->val, p);
    n = n->next();
  }
}

template<class T>
bool RandomizedSearchTree<T>::isFirst (void)
{
  return (win == root->next() ) && (root != root->next ( ) );
}

template<class T>
bool RandomizedSearchTree<T>::isLast (void)
{
  return (win == root->prev() ) && (root != root->next() );
}

template<class T>
bool RandomizedSearchTree<T>::isHead (void)
{
  return (win == root);
}

template<class T>
bool RandomizedSearchTree<T>::isEmpty (void)
{
  return (root == root->next() );
}

 /*

  Поиск 

 

 

Компонентные функции find и findMin применяются также подобно их аналогам в классе BraidedSearchTree :
*/
template<class T> T RandomizedSearchTree<T>::find (T val)
{
  RandomizedNode<T> *n = root->rchild ( );
  while (n) {
    int result = (*cmp) (val, n->val);
    if (result < 0)
      n = n->lchild();
    else if (result > 0)
      n = n->rchild();
    else {
      win = n;
      return n->val;
    }
  }
  return NULL;
}

template<class T> T RandomizedSearchTree<T>::findMin (void)
{
  win = root->next();
  return win->val;
}
/*
Теперь мы введем новую операцию поиска locate. При обращении к функции locate с аргументом val возвращается наибольший элемент в дереве, который не больше, чем значение val. Если в дереве присутствует элемент со значением val, то возвращается значение val. Если такого значения нет, то возвращается значение меньше, чем val, если же в дереве и такого значения нет, то возвращается NULL.

Для выполнения этой операции будем отслеживать путь по дереву поиска до значения val. По мере продвижения вниз запоминается последний (самый нижний) узел b, в котором поворачиваем вправо — узел b является самым нижним узлом, обнаруженным на пути поиска, для которого правый потомок также лежит на пути поиска. Если в дереве находится значение val, то оно просто возвращается. В противном случае, если мы не найдем значение val в дереве — путь поиска завершается на внешнем узле — то возвращается элемент, запомненный в узле b.

Операция реализуется компонентной функцией locate, в которой окно перемещается на обнаруженный элемент и возвращается этот элемент.
*/
template<class T> T RandomizedSearchTree<T>::locate (T val)
{
  RandomizedNode<T> *b = root;
  RandomizedNode<T> *n = root->rchild();
  while (n) {
    int result = (*cmp) (val, n->val);
    if (result < 0)
      n = n->lchild();
    else if (result > 0) {
      b = n;
      n = n->rchild();
    } else {
      win = n;
      return win->val;
    }
  }
  win = b;
  return win->val;
}
/*
Каким же образом получается правильный результат? Он вполне очевиден, если значение val точно находится в дереве. Но предположим, что такого значения в дереве нет, поэтому поиск значения val завершается на внешнем узле. Поскольку указатель n сигнализирует об окончании поиска, значение b показывает на наибольший элемент, который меньше всех остальных, содержащихся в поддереве с корнем в узле n. Легко видеть, что это условие сохраняется всегда. Каждый раз, когда в процессе поиска в узле n мы переходим на левую ветвь, условие продолжает сохраняться, поскольку каждый элемент в левом поддереве узла n меньше элемента в узле n. При переходе в узле n на правую ветвь присваивание b значения, равного n, восстанавливает условие, поскольку: (1) каждый элемент в правом поддереве узла n больше элемента, хранящегося в n и (2) элемент, хранящийся в узле n больше, чем элемент, на который указывало значение b до его изменения. И, наконец, когда n указывает на внешний узел, то b будет наибольшим элементом в дереве, который меньше любого другого элемента, который может легально заменить внешний узел, среди которых находится также и val.
 

  Включение элементов 

 

 

Для внесения нового элемента в дерево случайного поиска сначала найдем внешний узел, к которому он принадлежит (этап 1), а затем будем его поднимать по дереву по направлению к корню в соответствии с его приоритетом (этап 2). Компонентная функция insert заносит элемент val в текущее дерево случайного поиска и затем перемещает окно на этот элемент и возвращает указатель на этот элемент:
*/
template<class T> T RandomizedSearchTree<T>::insert (T val)
{
                                          // этап 1
  int result = 1;
  RandomizedNode<T> *p = root;
  RandomizedNode<T> *n = root->rchild();
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
  win = new RandomizedNode<T>(val);
  win->_parent = p;
  if (result < 0) {
    p->_lchild = win;
    p->prev()->Node::insert(win);
  } else {
    p->_rchild = win;
    p->Node::insert(win);
  }
                                          //  этап 2
  win->bubbleUp ();
  return val;
}
/*
 

  Удаление элементов 

 

 

Компонентная функция remove удаляет элемент в окне и затем перемещает окно в предшествующую позицию. Компонентная функция removeMin (удаляет наименьший элемент и возвращает его. Если окно находилось на этом элементе, то оно перемещается в головную позицию:
*/
template<class T> void RandomizedSearchTree<T>::remove(void)
{
  if (win != root)
    _remove(win);
}

template<class T> T RandomizedSearchTree<T>::removeMin(void)
{
  T val = root->next()->val;
  if (root != root->next() )
    _remove(root->next());
  return val;
}
/*
Обе эти функции основаны на внутренней компонентной 
функции _remove. Для удаления узла n функция _remove 
увеличивает приоритет узла n до 1.5 и затем опускает 
его вниз до тех пор, пока он не станет внешним узлом. 
Приоритет 1.5 превышает приоритет любого элемента в 
дереве, но меньше, чем приоритет внешних узлов (2.0). 
После этого функция удаляет узел n из дерева случайного 
поиска. Если окно было на узле, подлежащем удалению, 
то окно перемещается на предшествующую позицию. 
Алгоритм реализуется в виде функции _remove, 
которая удаляет узел n из екущего дерева поиска.
*/
template<class T>
void RandomizedSearchTree<T>::_remove(RandomizedNode<T> *n)
{
  n->_priority = 1.5;
  n->bubbleDown();
  RandomizedNode<T> *p = n->parent();
  if (p->lchild() == n)
    p->_lchild = NULL;
  else
    p->_rchild = NULL;
  if (win == n)
    win = n->prev();
  n->Node::remove();
  delete n;
}
/*
На рис. 3, если его анализировать от (г) до (а), показано удаление элемента 6 из самого правого дерева поиска, для которого приоритет был увеличен до 1.5. Процесс удаления обратен процессу внесения элемента 6 в дерево (а), поскольку правая и левая ротации взаимно обратны.

Для удобства введем вторую компонентную функцию remove, которая, при передаче ей элемента, удаляет его из дерева случайного поиска. Если окно находится на элементе, подлежащем удалению, то окно перемещаетвя в предыдущую позицию, в противном случае окно не перемещается:
*/
template<class T> T RandomizedSearchTree<T>::remove (T val)
{
  T v = find (val);
  if (v) {
    remove();
    return v;
  }
  return NULL;
}

 

} //namespace
