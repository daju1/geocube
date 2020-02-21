#pragma once
#include "StdAfx.h"

namespace geometry2D
{
	/*
Конструктор класса BraidedNode явно инициализирует базовый класс TreeNode по своему списку инициализации, а базовый класс Node инициализируется неявно, поскольку его конструктор не имеет параметров:
*/
template<class T> BraidedNode<T>::BraidedNode<T> (T val) : 
  TreeNode<T> (val)
{
}

template<class T> BraidedNode<T>::BraidedNode<T>(BraidedNode<T>& n) : TreeNode<T>(n.val)
{
	_lchild = n._lchild ? new BraidedNode<T>(*n.lchild()) : NULL;
	_rchild = n._rchild ? new BraidedNode<T>(*n.rchild()) : NULL;

	//printf("BraidedNode<T>::BraidedNode(BraidedNode<T>& n) this = 0x%08x\n", this);
	//printf("BraidedNode<T>::BraidedNode(BraidedNode<T>& n) val  = 0x%08x\n", val);
	//printf("BraidedNode<T>::BraidedNode(BraidedNode<T>& n) this->_lchild = 0x%08x\n", this->_lchild);
	//printf("BraidedNode<T>::BraidedNode(BraidedNode<T>& n) this->_rchild = 0x%08x\n", this->_rchild);
}
/*
Компонентные функции rchild, lchild, next и prev устанавливают четыре ссылки для текущего узла — первые два для дерева поиска, а последние два — для ленты:
*/
template<class T>
BraidedNode<T> *BraidedNode<T>::rchild (void)
{
  return (BraidedNode<T> *)this->_rchild;
}

template<class T>
BraidedNode<T> *BraidedNode<T>::lchild (void)
{
  return (BraidedNode<T> *) this->_lchild;
}

template<class T>
BraidedNode<T> *BraidedNode<T>::next (void)
{
  return (BraidedNode<T> *)_next;
}

template<class T>
BraidedNode<T> *BraidedNode<T>::prev (void)
{
  return (BraidedNode<T> *)_prev;
}


} //namespace
