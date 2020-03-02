#pragma once

#include "./BraidedNode.h"

namespace geometry2D
{
/*
”злы в дереве случайного поиска ¤вл¤ютс¤ объектами шаблона класса RandomizedNode:
*/

template<class T> class RandomizedSearchTree;

template<class T>
class RandomizedNode : public BraidedNode<T> {
 protected :
  RandomizedNode<T> *_parent;
  float _priority;
  void rotateRight (void);
  void rotateLeft (void);
  void bubbleUp (void);
  void bubbleDown (void);
 public :
  RandomizedNode<T> ( T v, int seed = -1);
  RandomizedNode<T> *lchild(void);
  RandomizedNode<T> *rchild(void);
  RandomizedNode<T> *next (void);
  RandomizedNode<T> *prev (void);
  RandomizedNode<T> *parent (void);
  float priority (void);
  friend class RandomizedSearchTree<T>;
};
/*
 ласс RandomizedNode наследует п¤ть элементов данных из его базового класса: val, _lchild, _rchild, _prev и _next. ¬ класс включены два дополнительных элемента данных: _parent, который указывает на узел-предок текущего узла, и _priority, приоритет текущего узла.
*/

} //namespace

#include "RandomizedNode.cpp"
