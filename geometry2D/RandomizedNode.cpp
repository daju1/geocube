//#pragma once

#include "StdAfx.h"

namespace geometry2D
{
	/*
����������� ����������� ������ ���� RandomizedNode ��������� �������� ����������, ��������� ����������� ������� ����� C++ rand, ������� ���������� ��������� ����� � �������� �� 0 �� RAND_MAX :
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
���������� ������� ������������ ������������ ������� ������ RandomizedNode, ����������� ��� private (�����������). ������ ��� ��������� ��� ���� ������� � ������ � �����. ������ ������� �������� ��������� ���������, ������� �������� ����� ������ ������, �������� ���������� ������� ���������� ��������� � �� � ����� ���������� �������� �������������� � ������������� ��� ������� ���� �������� ��� ���������. ������ ������� ��� ���� � �������� � �������� ��������� � ������ � ���� � ������ ����� �� ���� � � ��� ������ ������� � (���. 2). �������� ����������� ����� ��������� ���������� ����� ������: ����� � ����� �������� ���� � ���������� �� ����� � ���������� T2, ����� � ������ �������� ���� � ���������� �� ����� � ����� �, � ����� � ����� � (�� ��� ������) ���������� �� ����� � ����� �.

������������ ������� rotateRight ��������� ������ ������� ��� �������� ����, ������� ������ ���� ���� �. ��� ���� ���� � ������ ���� ����� �������� ���� �. ��� ���������� ��������������, ��� ������ ���� � ����������, ��������� �������� ���� ������ ����� ����������� ��������� � �� ������ ������� ���� �� ������ ���� �� ������ ��������� ����, ������� ��� ��������� ���� ������ ����� ������ ������.
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
�������� ������������ ������� rotateLeft ��� ����� ������� ����� �������� �� ���. 2 � ��� ������������ �����������:
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
������������ ������� bubbleUp ��������� ������� ���� ����� �� ����������� � ����� ����� ������������ ������� �� ��� ���, ���� ��������� �������� ���� �� ������ ������ ��� ������, ��� � ��� ������. ������� ����������� � ��� �������, ����� ������� � ������ ���������� ������ ������������� ����, ��� ��� ������� � ������������ �� ��������� ��� ����������. �������, ��� ������� ����������� � ������ �������� ����.
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
������������ ������� bubbleDown ��������� ������� ���� ���� �� ����������� � ������� ����� ������ ����� ������������ ������� �� ��� ���, ���� ��������� �������� ���� �� ������ ������ ��� ������ ����������� ����� ��� ��������. ��� ������� �� ����������� (������ ��� �����) ������� �� ����, ����� �� �������� �������� ���� ����� ������� ���������. ����, ��������, ��������� ������ ������� ������, �� ������ ������� ��������� ����� ������� ����� �� ���� �������, � ������� ���� ������������ �� ���� ������� ����. ������� �������� ���� ������������� ��������� 2.0, ���������� �������, ����� �������� �� ����������� ��� �����. ������� bubbleDown ����������� � ��� �������, ����� ������� � ������ ���������� ������ ������������� ����, ��� ��� ������� � ������������ �� ��������� ��� ����������. ��� ������� ����� ������������ ������������ ��� �������� �������� �� ������ ������.
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
������������� ������������ ������� rchild, Ichild, next, prev � parent ���������� ����� �������� ���� � ��� ������ � ����� ���������, � ����������� � �������������� ������ � � ������� ��������������:
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
������������ ������� priority ���������� ��������� �������� ����:
*/
template<class T>
float RandomizedNode<T>::priority(void)
{
  return _priority;
}


} //namespace