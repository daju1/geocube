#pragma once
#include "StdAfx.h"
namespace geometry2D
{
	/*
������������ � ����������� 

 

 

����������� RandomizedsearchTree �������������� ����� ������ ���������� ������, �������������� ������������� �������� ����� � ����������� �����������, ������ -1,0:
*/
template<class T> RandomizedSearchTree<T>::RandomizedSearchTree<T>(int (*c) (T, T), int seed):cmp(c)
{
  win = root = new RandomizedNode<T> (NULL, seed); 
  root->_priority = -1.0;
}
/*
���������� ������� ������ ������:
*/
template<class T>
RandomizedSearchTree<T>::~RandomizedSearchTree<T> (void)
{
  delete root;
}

 
/*
  ������������� ����� 

 

 

������������ ������� next, prev, val, inorder, isFirst, isLast, isHead � is Empty ������������ ������� �� �������� � ������

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

  ����� 

 

 

������������ ������� find � findMin ����������� ����� ������� �� �������� � ������ BraidedSearchTree :
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
������ �� ������ ����� �������� ������ locate. ��� ��������� � ������� locate � ���������� val ������������ ���������� ������� � ������, ������� �� ������, ��� �������� val. ���� � ������ ������������ ������� �� ��������� val, �� ������������ �������� val. ���� ������ �������� ���, �� ������������ �������� ������, ��� val, ���� �� � ������ � ������ �������� ���, �� ������������ NULL.

��� ���������� ���� �������� ����� ����������� ���� �� ������ ������ �� �������� val. �� ���� ����������� ���� ������������ ��������� (����� ������) ���� b, � ������� ������������ ������ � ���� b �������� ����� ������ �����, ������������ �� ���� ������, ��� �������� ������ ������� ����� ����� �� ���� ������. ���� � ������ ��������� �������� val, �� ��� ������ ������������. � ��������� ������, ���� �� �� ������ �������� val � ������ � ���� ������ ����������� �� ������� ���� � �� ������������ �������, ����������� � ���� b.

�������� ����������� ������������ �������� locate, � ������� ���� ������������ �� ������������ ������� � ������������ ���� �������.
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
����� �� ������� ���������� ���������� ���������? �� ������ ��������, ���� �������� val ����� ��������� � ������. �� �����������, ��� ������ �������� � ������ ���, ������� ����� �������� val ����������� �� ������� ����. ��������� ��������� n ������������� �� ��������� ������, �������� b ���������� �� ���������� �������, ������� ������ ���� ���������, ������������ � ��������� � ������ � ���� n. ����� ������, ��� ��� ������� ����������� ������. ������ ���, ����� � �������� ������ � ���� n �� ��������� �� ����� �����, ������� ���������� �����������, ��������� ������ ������� � ����� ��������� ���� n ������ �������� � ���� n. ��� �������� � ���� n �� ������ ����� ������������ b ��������, ������� n, ��������������� �������, ���������: (1) ������ ������� � ������ ��������� ���� n ������ ��������, ����������� � n � (2) �������, ���������� � ���� n ������, ��� �������, �� ������� ��������� �������� b �� ��� ���������. �, �������, ����� n ��������� �� ������� ����, �� b ����� ���������� ��������� � ������, ������� ������ ������ ������� ��������, ������� ����� �������� �������� ������� ����, ����� ������� ��������� ����� � val.
 

  ��������� ��������� 

 

 

��� �������� ������ �������� � ������ ���������� ������ ������� ������ ������� ����, � �������� �� ����������� (���� 1), � ����� ����� ��� ��������� �� ������ �� ����������� � ����� � ������������ � ��� ����������� (���� 2). ������������ ������� insert ������� ������� val � ������� ������ ���������� ������ � ����� ���������� ���� �� ���� ������� � ���������� ��������� �� ���� �������:
*/
template<class T> T RandomizedSearchTree<T>::insert (T val)
{
                                          // ���� 1
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
                                          //  ���� 2
  win->bubbleUp ();
  return val;
}
/*
 

  �������� ��������� 

 

 

������������ ������� remove ������� ������� � ���� � ����� ���������� ���� � �������������� �������. ������������ ������� removeMin (������� ���������� ������� � ���������� ���. ���� ���� ���������� �� ���� ��������, �� ��� ������������ � �������� �������:
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
��� ��� ������� �������� �� ���������� ������������ 
������� _remove. ��� �������� ���� n ������� _remove 
����������� ��������� ���� n �� 1.5 � ����� �������� 
��� ���� �� ��� ���, ���� �� �� ������ ������� �����. 
��������� 1.5 ��������� ��������� ������ �������� � 
������, �� ������, ��� ��������� ������� ����� (2.0). 
����� ����� ������� ������� ���� n �� ������ ���������� 
������. ���� ���� ���� �� ����, ���������� ��������, 
�� ���� ������������ �� �������������� �������. 
�������� ����������� � ���� ������� _remove, 
������� ������� ���� n �� ������� ������ ������.
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
�� ���. 3, ���� ��� ������������� �� (�) �� (�), �������� �������� �������� 6 �� ������ ������� ������ ������, ��� �������� ��������� ��� �������� �� 1.5. ������� �������� ������� �������� �������� �������� 6 � ������ (�), ��������� ������ � ����� ������� ������� �������.

��� �������� ������ ������ ������������ ������� remove, �������, ��� �������� �� ��������, ������� ��� �� ������ ���������� ������. ���� ���� ��������� �� ��������, ���������� ��������, �� ���� ������������ � ���������� �������, � ��������� ������ ���� �� ������������:
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