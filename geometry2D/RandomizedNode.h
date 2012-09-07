#pragma once

#include "./braidednode.h"

namespace geometry2D
{
/*
���� � ������ ���������� ������ �������� ��������� ������� ������ RandomizedNode:
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
����� RandomizedNode ��������� ���� ��������� ������ �� ��� �������� ������: val, _lchild, _rchild, _prev � _next. � ����� �������� ��� �������������� �������� ������: _parent, ������� ��������� �� ����-������ �������� ����, � _priority, ��������� �������� ����.
*/

} //namespace

#include "RandomizedNode.cpp"
