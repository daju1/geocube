#pragma once
#include "StdAfx.h"

namespace geometry2D
{

	/*
������������ � ����������� 

 

 

����������� ������ BraidedSearchTree �������������� �������� ������ cmp ��� ������� ��������� � root ��� ������� ������, ��������������� � ���� �������������� ��������� ����:

template<class T>
BraidedSearchTree<T>::BraidedSearchTree (int (*�) (T, T) ) :
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
���������� ������ ������� ������ �������, ��������� � ����������� ��������� ����:
*/
template<class T>
BraidedSearchTree<T>::~BraidedSearchTree<T> (void)
{			
	if (root) delete root;	root = NULL;
}

 /*
������������� ����� 

 
������� ������ win ��������� ���� ��� ������ � �. �. ������� 
win ��������� �� ����, ��� ������� ������������� ����.
������������ ������� next � prew ���������� ���� �� 
��������� ��� ���������� �������. ���� ���� ��������� 
� �������� �������, �� ������� next ���������� ��� �� 
������ �������, � ������� prew � �� ��������� �������. 
��� ������� ���������� ������ �� ������� � ����� �������
����:
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
������������ ������� val ���������� ������ �� ������� ������ ����. ���� ���� ��������� � �������� �������, �� ������������ �������� NULL.
*/
template<class T> T BraidedSearchTree<T>::val (void)
{
  return win->val;
}
/*
������������ ����� ����������� ����� ������� �� ����� �� ������ ������� �� ���������, �������� ������� visit ��� ������� �������� �� ����� ����:
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
������������ ������� isFirst, isLast � isHead ���������� �������� TRUE (������), ���� ���� ��������� � ������, ��������� ��� �������� �������� ��������������.
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
������� isEmpty ���������� �������� TRUE (������) ������ ���� ������� ������ ����� � ������� ������ �� ���������� ��������� ����:
*/
template<class T> bool BraidedSearchTree<T>::isEmpty ()
{
  return   (root == root->next() );
}

 
/*
  ����� 
 
��� ������ �������� ������������ ������������ ������� find. ��� ������� ���������� ������� SearchTree::find �� ����������� ����, ��� ��� �������� ���� ����� � root->rchild(), ������������ �����. ���� ������� ������, �� ���� ��������������� �� ���� ��������. 
*/

template<class T> T BraidedSearchTree<T>::find (T val)
{
	BraidedNode<T> *n = root->rchild();
	if (_find (val, n))           
		return (n ? n->val : NULL);
	return NULL;
}
template<class T> BOOL BraidedSearchTree<T>::_find (T val, BraidedNode<T> *& n)
{
  while (n) {
    int result = (*cmp) (val, n->val);
    if (result < 0)
      n = n->lchild();
    else if (result > 0)
	  n = n->rchild();
	else {
      win=n;
      return TRUE;
    }
  }
  return FALSE;
}

/*
���������� ������� � ��������� ������ ������ ������������� � ������ ������� �����. ������������ ������� findMin ���������� ���� �� ���� ���������� ������� � ���������� ��������� �� �������. ���� ������ ������ �����, �� ������������ NULL :
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

  ��������� ��������� 

 

 

����� ������� ������ ���� ������ � ��� ���������� ������� ��� � ������ ������, ��� � � �����. ���� ����� ������� ���������� ����� ��������, �� ��� ����� �� ���������� ���������������� ������ � �����. ���� ������� ���������� ������ ��������, �� �� ���������� �������������� ������ � �����. ���������� ������� insert ��������� � �������� SearchTree: : insert �� ����������� ��������������� ��������� ������ ���� � �����. ������ ������� ��������, ��� � ������� insert ��� ������������� �������� ��������� � ������ ������, ��������� �������� ���� ������������ ������. ������� ����������� ���� ��� ������ ��� ��������� ��������� � ���������� ��������� �a �������, ���� ��������� ��������� �������.
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

  �������� ��������� 

 

 

������������ ������� remove ������� �������, ����������� � ���� � ���������� ���� � ���������� �������:
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
	//�������� ������� �� ���� ���������� ����� ������� ������ _remove()
	BraidedNode<T> * n = _find(val);
	if(n)
		_remove(n);
#endif
}
/*
������� val, ���������� ��������, � ��������� n �� ������ ������ ������, � ������� ��������� ���� �������, ���������� � �������� ���������� ����������� ������� _remove. ��� ������� �������� ������� ������ ������� � ��� �� ������ � ������ SearchTree. ������ ��� ������ �� ��������� ������� ������ �������, �������, ������ ���� ������ ��� �� ������ ������, ��� � �� �����:
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
  else {                         // ������ 1
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
    else if (n->_rchild == NULL) { // ������ 2
      BraidedNode<T> *old = (BraidedNode<T>*)n;
      if (win == old)
        win = old->prev();
      n = old->lchild();
	  old->_lchild = NULL;
      old->Node::remove();
      delete old;
	  return true;
    }
    else  {                       // ������ 3
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
	else {                         // ������ 1
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
		{ // ������ 2
			BraidedNode<T> *old = (BraidedNode<T>*)n;
			if (win == old)
				win = old->prev();
			n = old->lchild();
			old->_lchild = NULL;
			old->Node::remove();
			delete old;
		}
		else  
		{                       // ������ 3
			BraidedNode<T> *m = ( (BraidedNode<T>*)n)->next();
			n->val = m->val;
			_remove(m);
		}
	}
}
*/
/*
�������, ��� ������� _remove ���������� ����� ��� ������ ������������� ���� n � ������ 3, ����� ���������� �������� ���� ����� ��� �������� �������. ������� �����, ��� �������� n �������� ������� �� ��� TreeNode*, � �� �� ��� BraidedNode*. ��� ���������� ������, ��� n ��������� �� ������, ���������� � ������ ����, ����������� ��������, � ��� ������ ����� ��� TreeNode*. ���� �� ������ ����� ��������� n ��� �������� ��� BraidedNode*, �� ��� ���� �� ��������� ������ �� ��������� ������. ��� ���� ���� ������ � ���� ������ ���� �� ����������.

������������ ������� removeMin ������� �� ������ ���������� ������� � ���������� ��������� �� ����, ������� ���������� �������� NULL, ���� ������ �����. ���� ���� ��������� ��������� ���������� �������, �� ���� ������������ � �������� �������, � ���� ������ ��� �������� ��� ���������:
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
