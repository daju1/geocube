#pragma once
#include "RandomizedNode.h"

namespace geometry2D
{

/*
������� ���������� ������ �������������� � ���� �������� ������ RandomizedSearchTree. �� ������ ���������� ������ ������ ���������� ����� BraidedSearchTree: ������� ������ root ��������� �� �������� ����, win ������������ ����, � ������� cmp ��������� �� ������� ��������� ��������.
*/
template<class T> class RandomizedSearchTree {
 private :
  RandomizedNode<T> *root;       // �������� ���� 
  RandomizedNode<T> *win;        // ���� 
  int (*cmp) (T,T);	             // ������� ���������
  void _remove(RandomizedNode<T>*);
 public :
  RandomizedSearchTree (int (*) (T,T) , int = -1);
  ~RandomizedSearchTree (void);
  T next (void);
  T prev(void);
  void inorder (void (*) (T, void * ), void * );
  T val (void);
  bool isFirst (void);
  bool isLast (void);
  bool isHead(void);
  bool isEmpty (void);
  T find (T);
  T findMin (void);
  T locate (T);
  T insert (T);
  void remove (void);
  T remove (T);
  T removeMin (void);
};


} //namespace

#include "RandomizedSearchTree.cpp"
